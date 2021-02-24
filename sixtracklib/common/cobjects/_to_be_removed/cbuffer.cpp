#if defined( __cplusplus ) && !defined( _GPUCODE )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/cbuffer.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using this_type = st::CBuffer;
        using view_type = st::CBufferView;
    }

    constexpr CBuffer::flags_type CBuffer::FLAGS_CBUFFER_DEFAULT;

    CBuffer::CBuffer(
        this_type::size_type capacity, this_type::size_type const slot_size,
        this_type::flags_type const flags ) :
        view_type( this_type::NULL_ADDRESS, slot_size,
                this_type::size_type{ 0 }, flags ),
        m_raw_buffer() {
        this_type::status_type const status = this->reserve( capacity );
        SIXTRL_ASSERT( status == NS(STATUS_SUCCESS) );
        ( void )status; }

    CBuffer::CBuffer( CBufferView const& SIXTRL_RESTRICT view,
        this_type::flags_type const flags ) :
        view_type( this_type::NULL_ADDRESS, view.slot_size(),
                this_type::size_type{ 0 },
                flags | this_type::FLAGS_ALLOW_REMAPPING |
                this_type::FLAGS_ALLOW_REALLOC ),
        m_raw_buffer() {
        this_type::status_type const status = this->from_view( view );
        SIXTRL_ASSERT( status == NS(STATUS_SUCCESS) );
        ( void )status; }

    CBuffer::CBuffer( char const* SIXTRL_RESTRICT path_to_file,
        this_type::size_type const slot_size,
        this_type::flags_type const flags ) :
        view_type( this_type::NULL_ADDRESS, slot_size,
                this_type::size_type{ 0 },
                flags | this_type::FLAGS_ALLOW_REMAPPING |
                this_type::FLAGS_ALLOW_REALLOC ),
        m_raw_buffer() {
        this_type::status_type const status = this->fromfile( path_to_file );
        SIXTRL_ASSERT( status == NS(STATUS_SUCCESS) );
        ( void )status; }

    CBuffer::CBuffer( std::string const& SIXTRL_RESTRICT_REF path_to_file,
        this_type::size_type const slot_size,
        this_type::flags_type const flags ) :
        view_type( this_type::NULL_ADDRESS, slot_size,
                this_type::size_type{ 0 },
                flags | this_type::FLAGS_ALLOW_REMAPPING |
                this_type::FLAGS_ALLOW_REALLOC ),
        m_raw_buffer() {
        this_type::status_type const status = this->fromfile( path_to_file );
        SIXTRL_ASSERT( status == NS(STATUS_SUCCESS) );
        ( void )status; }

    CBuffer::CBuffer(
        this_type::size_type const max_num_slots,
        this_type::size_type const max_num_objects,
        this_type::size_type const max_num_pointers,
        this_type::size_type const max_num_garbage_ranges,
        this_type::size_type const slot_size,
        this_type::flags_type   const flags ) :
        view_type( this_type::NULL_ADDRESS, slot_size,
                this_type::size_type{ 0 },
                flags | this_type::FLAGS_ALLOW_REMAPPING |
                this_type::FLAGS_ALLOW_REALLOC ),
        m_raw_buffer() {
        this_type::status_type const status = this->reserve( max_num_slots,
            max_num_objects, max_num_pointers, max_num_garbage_ranges );
        SIXTRL_ASSERT( status == NS(STATUS_SUCCESS) );
        ( void )status; }


    this_type::status_type CBuffer::from_view(
        CBufferView const& SIXTRL_RESTRICT_REF view )
    {
        typedef this_type::size_type st_size_type;
        this_type::status_type status = st::STATUS_SUCCESS;

        if( ( this->allow_realloc() ) && ( this->allow_remap() ) &&
            ( view.capacity() > st_size_type{ 0 } ) &&
            ( view.slot_size() >  st_size_type{ 0 } ) &&
            ( ( view.slot_size() == this->slot_size() ) ||
              ( ( view.slot_size() > this->slot_size() ) &&
                ( view.slot_size() % this->slot_size() ==
                  st_size_type{ 0 } ) ) ) ) {
            status = this->reserve( view.capacity() );
            if( status == st::STATUS_SUCCESS )
            {
                SIXTRL_ASSERT( this->capacity() >= view.capacity() );
                std::copy( view.p_base_begin(), view.p_base_end(),
                           this->p_base_begin() );
                status = this->remap();
            }
        }
        return status;
    }

    this_type::status_type CBuffer::from_flat_buffer(
        ::NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
        this_type::size_type const slot_size )
    {
        typedef this_type::size_type st_size_type;
        this_type::status_type status = st::STATUS_GENERAL_FAILURE;

        st_size_type const buffer_size =
            ::NS(CObjFlatBuffer_size)( buffer, slot_size );

        if( ( this->allow_realloc() ) && ( this->allow_remap() ) &&
            ( buffer != SIXTRL_NULLPTR ) && ( slot_size > st_size_type{ 0 } ) &&
            ( ( slot_size == this->slot_size() ) ||
              ( ( slot_size > this->slot_size() ) &&
                ( slot_size % this->slot_size() == st_size_type{ 0 } ) ) ) &&
            ( buffer_size > st_size_type{ 0 } ) ) {
            status = this->reserve( buffer_size );
            if( status == st::STATUS_SUCCESS ) {
                std::copy( buffer, buffer + buffer_size, this->p_base_begin() );
                status = this->remap(); }
        }
        return status; }

    this_type::status_type CBuffer::fromfile(
        std::string const& SIXTRL_RESTRICT_REF path_to_file ) {
        return this->fromfile( path_to_file.c_str() ); }

    this_type::status_type CBuffer::fromfile(
        char const* SIXTRL_RESTRICT path_to_file ) {
        typedef this_type::size_type st_size_type;
        this_type::status_type status = st::STATUS_GENERAL_FAILURE;
        view_type dummy_view( this_type::NULL_ADDRESS, this->slot_size(),
                st_size_type{ 0 }, this_type::FLAGS_BASE_DEFAULT );
        st_size_type requ_capacity = st_size_type{ 0 };
        st::CBufferView_from_file( dummy_view, path_to_file, &requ_capacity );
        if( requ_capacity == st_size_type{ 0 } ) return status;
        status = ( requ_capacity > this->capacity() )
            ? this->reserve( requ_capacity ) : st::STATUS_SUCCESS;
        if( status == st::STATUS_SUCCESS )
            status = st::CBufferView_from_file( *this, path_to_file, nullptr );
        return status; }

    this_type::status_type CBuffer::tofile(
        std::string const& SIXTRL_RESTRICT_REF path_to_file ) const {
        return this->tofile( path_to_file.c_str() ); }

    this_type::status_type CBuffer::tofile(
        std::string const& SIXTRL_RESTRICT_REF path_to_file,
        this_type::addr_type const normalized_base_addr ) {
        return st::CBuffer_to_file_normalized(
            *this, path_to_file, normalized_base_addr ); }

    this_type::status_type CBuffer::tofile(
        char const* SIXTRL_RESTRICT path_to_file ) const {
        return st::CBuffer_to_file( *this, path_to_file ); }

    this_type::status_type CBuffer::tofile(
        char const* SIXTRL_RESTRICT path_to_file,
        this_type::addr_type const normalized_base_addr ) {
        return st::CBuffer_to_file_normalized(
            *this, path_to_file, normalized_base_addr ); }

    /* --------------------------------------------------------------------- */

    this_type::status_type CBuffer::reserve( this_type::size_type new_capacity )
    {
        typedef this_type::addr_type addr_type;
        typedef this_type::size_type st_size_type;

        this_type::status_type status = st::STATUS_GENERAL_FAILURE;

        if( ( !this->allow_realloc() ) ||
            ( this->slot_size() == st_size_type{ 0 } ) ||
            ( this->m_realloc_factor_denominator == st_size_type{ 0 } ) ||
            ( this->m_realloc_factor_nominator == st_size_type{ 0 } ) ||
            ( this->m_realloc_factor_denominator >
              this->m_realloc_factor_nominator ) )
        {
            return status;
        }

        if( new_capacity < this_type::BUFFER_MINIMAL_SIZE )
            new_capacity = this_type::BUFFER_MINIMAL_SIZE;

        new_capacity = ::NS(CObjFlatBuffer_slot_based_size)(
            this->slot_size() + ( this->m_realloc_factor_nominator *
                new_capacity ) / this->m_realloc_factor_denominator,
                    this->slot_size() );

        status = st::STATUS_SUCCESS;
        st_size_type const current_capacity = this->capacity();
        if( current_capacity < new_capacity ) {
            this_type::raw_buffer_type new_raw_buffer( new_capacity );

            addr_type const new_store_addr = static_cast< addr_type >(
                reinterpret_cast< std::uintptr_t >( new_raw_buffer.data() ) );
            SIXTRL_ASSERT( new_store_addr != addr_type{ 0 } );

            addr_type const remainder = new_store_addr % this->slot_size();
            addr_type const shift_addr = ( remainder == addr_type{ 0 } )
                ? addr_type{ 0 } : this->slot_size() - remainder;
            new_capacity = ( remainder == addr_type{ 0 } )
                ? new_capacity : new_capacity - this->slot_size();

            if( current_capacity < new_capacity ) {
                status = st::STATUS_GENERAL_FAILURE;
                addr_type const base_addr = new_store_addr + shift_addr;

                if( ( current_capacity == st_size_type{ 0 } ) ||
                    ( this->allow_remap() ) )
                {
                    status = st::STATUS_SUCCESS;
                    if( current_capacity > st_size_type{ 0 } )
                    {
                        std::copy( this->p_base_begin(), this->p_base_end(),
                            reinterpret_cast< this_type::raw_pointer >(
                                static_cast< std::uintptr_t >( base_addr ) ) );
                    }
                }

                if( status == st::STATUS_SUCCESS ) {
                    this->m_raw_buffer.swap( new_raw_buffer );
                    this->do_set_base_addr( base_addr );
                    this->do_set_capacity( new_capacity );

                    if( current_capacity == st_size_type{ 0 } ) {
                        status = ::NS(CObjFlatBuffer_init_empty)(
                            this->p_base_begin(), new_capacity,
                                this->slot_size() ); }
                    else { status = this->remap(); } }
            }
        }
        return status; }

    this_type::status_type CBuffer::reserve(
        this_type::size_type const max_num_slots,
        this_type::size_type const max_num_objects,
        this_type::size_type const max_num_pointers,
        this_type::size_type const max_num_garbage_ranges )
    {
        this_type::size_type const requ_capacity =
        ::NS(CObjFlatBuffer_calc_required_buffer_size)( this->p_base_begin(),
            max_num_slots, max_num_objects, max_num_pointers,
                max_num_garbage_ranges, this->slot_size() );

        this_type::status_type status = this->reserve( requ_capacity );

        if( status == st::STATUS_SUCCESS )
        {
            SIXTRL_ASSERT( this->has_capacity_for_allocate( max_num_slots,
                max_num_objects, max_num_pointers, max_num_garbage_ranges ) );

            status = this->reallocate( max_num_slots, max_num_objects,
               max_num_pointers, max_num_garbage_ranges );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    this_type::status_type CBuffer::set_realloc_factor(
        this_type::size_type realloc_factor ) SIXTRL_NOEXCEPT
    {
        this_type::status_type status = st::STATUS_GENERAL_FAILURE;

        if( realloc_factor >= this_type::size_type{ 1 } )
        {
            this->m_realloc_factor_nominator = realloc_factor;
            this->m_realloc_factor_denominator = this_type::size_type{ 1 };
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    this_type::status_type CBuffer::set_realloc_factor_frac(
        this_type::size_type realloc_factor_nominator,
        this_type::size_type realloc_factor_denominator ) SIXTRL_NOEXCEPT
    {
        this_type::status_type status = st::STATUS_GENERAL_FAILURE;

        if( ( realloc_factor_denominator > this_type::size_type{ 0 } ) &&
            ( realloc_factor_denominator <= realloc_factor_nominator ) )
        {
            this->m_realloc_factor_nominator = realloc_factor_nominator;
            this->m_realloc_factor_denominator = realloc_factor_denominator;
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

} /* end: SIXTRL_CXX_NAMESPACE */

/* ************************************************************************** */

SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer* NS(CBuffer_new)( void ){
    return new SIXTRL_CXX_NAMESPACE::CBuffer(
        SIXTRL_CXX_NAMESPACE::CBUFFER_MIN_SIZE,
        SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_CXX_NAMESPACE::CBuffer::FLAGS_CBUFFER_DEFAULT ); }

SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer*
NS(CBuffer_new_with_capacity)(
    ::NS(cobj_size_type) const capacity ) {
    return new SIXTRL_CXX_NAMESPACE::CBuffer( capacity,
        SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_CXX_NAMESPACE::CBuffer::FLAGS_CBUFFER_DEFAULT ); }

SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer*
NS(CBuffer_new_detailed)( ::NS(cobj_size_type) const capacity,
    ::NS(cobj_size_type) const slot_size,
    ::NS(cobj_buffer_flags_type) const flags ) {
    return new SIXTRL_CXX_NAMESPACE::CBuffer( capacity, slot_size, flags ); }

SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer*
NS(CBuffer_new_as_copy)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT view ) {
    return ( view != nullptr ) ? new SIXTRL_CXX_NAMESPACE::CBuffer( *view )
        : nullptr; }

SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer*
NS(CBuffer_new_as_copy_detailed)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT view,
    ::NS(cobj_buffer_flags_type) const flags ) {
    return ( view != nullptr )
        ? new SIXTRL_CXX_NAMESPACE::CBuffer( *view, flags )
        : nullptr; }

SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer* NS(CBuffer_new_fromfile)(
    char const* SIXTRL_RESTRICT path_to_file ) {
    return new SIXTRL_CXX_NAMESPACE::CBuffer( path_to_file ); }

SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer*
NS(CBuffer_new_fromfile_detailed)( char const* SIXTRL_RESTRICT path_to_file,
    ::NS(cobj_size_type) const slot_size,
    ::NS(cobj_buffer_flags_type) const flags ) {
    return new SIXTRL_CXX_NAMESPACE::CBuffer( path_to_file, slot_size, flags ); }

SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer*
NS(CBuffer_new_with_structure)(
    ::NS(cobj_size_type) const max_num_slots,
    ::NS(cobj_size_type) const max_num_objects,
    ::NS(cobj_size_type) const max_num_pointers,
    ::NS(cobj_size_type) const max_num_garbage_ranges,
    ::NS(cobj_size_type) const slot_size,
    ::NS(cobj_buffer_flags_type) const flags ) {
    return new SIXTRL_CXX_NAMESPACE::CBuffer( max_num_slots, max_num_objects,
        max_num_pointers, max_num_garbage_ranges, slot_size, flags ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(cobj_status_type) NS(CBuffer_from_view)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer*
        SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const SIXTRL_RESTRICT view ){
    return ( ( buffer != nullptr ) && ( view != nullptr ) )
        ? buffer->from_view( *view )
        : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

::NS(cobj_status_type) NS(CBuffer_from_flat_buffer)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer*
        SIXTRL_RESTRICT buffer,
    ::NS(cobj_raw_const_pointer) SIXTRL_RESTRICT flat_buffer_begin,
    ::NS(cobj_size_type) const slot_size ) {
    return ( buffer != nullptr )
        ? buffer->from_flat_buffer( flat_buffer_begin, slot_size )
        : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

::NS(cobj_status_type) NS(CBuffer_fromfile)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer* SIXTRL_RESTRICT
        buffer, char const* SIXTRL_RESTRICT path_to_file ) {
    return ( buffer != nullptr )
        ? buffer->fromfile( path_to_file )
        : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(cobj_status_type) NS(CBuffer_tofile)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer*
        SIXTRL_RESTRICT buffer, char const* SIXTRL_RESTRICT path_to_file ) {
    return ( buffer != nullptr )
        ? buffer->tofile( path_to_file )
        : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

::NS(cobj_status_type) NS(CBuffer_tofile_normalised)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer*
        SIXTRL_RESTRICT buffer,
    char const* SIXTRL_RESTRICT path_to_file,
    ::NS(cobj_addr_type) const normalized_base_addr ) {
    return ( buffer != nullptr )
        ? buffer->tofile( path_to_file, normalized_base_addr )
        : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

::NS(cobj_status_type) NS(CBuffer_set_realloc_factor)(
    SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBuffer)* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_type) const realloc_factor ) SIXTRL_NOEXCEPT {
    return ( buffer != nullptr )
        ? buffer->set_realloc_factor( realloc_factor )
        : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

::NS(cobj_status_type) NS(CBuffer_set_realloc_factor_detailed)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer* SIXTRL_RESTRICT b,
    ::NS(cobj_size_type) const realloc_nominator,
    ::NS(cobj_size_type) const realloc_denominator ) SIXTRL_NOEXCEPT {
    return ( b != nullptr )
        ? b->set_realloc_factor_frac( realloc_nominator, realloc_denominator )
        : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

#endif /* C++, Host */
