#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/cbuffer.h"
    #include "sixtracklib_base/cobjects/flat_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using this_t = SIXTRL_CXX_NAMESPACE::CBuffer;
        using view_t = SIXTRL_CXX_NAMESPACE::CBufferView;
    }

    constexpr CBuffer::flags_t CBuffer::FLAGS_CBUFFER_DEFAULT;

    CBuffer::CBuffer(
        this_t::size_type capacity, this_t::size_type const slot_size,
        this_t::flags_t const flags ) :
        view_t( this_t::NULL_ADDRESS, slot_size,
                this_t::size_type{ 0 }, flags ),
        m_raw_buffer(),
        m_realloc_factor_nominator(
            this_t::DEFAULT_REALLOC_FACTOR_NOMINATOR ),
        m_realloc_factor_denominator(
            this_t::DEFAULT_REALLOC_FACTOR_DENOMINATOR )
    {
        this_t::status_t const status = this->reserve( capacity );
        ( void )status;
    }

    CBuffer::CBuffer( CBufferView const& SIXTRL_RESTRICT view,
        this_t::flags_t const flags ) :
        view_t( this_t::NULL_ADDRESS, view.slot_size(),
                this_t::size_type{ 0 },
                flags | this_t::FLAGS_ALLOW_REMAPPING |
                this_t::FLAGS_ALLOW_REALLOC ),
        m_raw_buffer(),
        m_realloc_factor_nominator(
            this_t::DEFAULT_REALLOC_FACTOR_NOMINATOR ),
        m_realloc_factor_denominator(
            this_t::DEFAULT_REALLOC_FACTOR_DENOMINATOR )
    {
        this_t::status_t const status = this->from_view( view );
        ( void )status;
    }

    CBuffer::CBuffer(
        char const* SIXTRL_RESTRICT path_to_file,
        this_t::size_type const slot_size, this_t::flags_t const flags ) :
        view_t( this_t::NULL_ADDRESS, slot_size,
                this_t::size_type{ 0 },
                flags | this_t::FLAGS_ALLOW_REMAPPING |
                this_t::FLAGS_ALLOW_REALLOC ),
        m_raw_buffer(),
        m_realloc_factor_nominator(
            this_t::DEFAULT_REALLOC_FACTOR_NOMINATOR ),
        m_realloc_factor_denominator(
            this_t::DEFAULT_REALLOC_FACTOR_DENOMINATOR )
    {
        this_t::status_t const status = this->fromfile( path_to_file );
        ( void )status;
    }

    CBuffer::CBuffer( std::string const& SIXTRL_RESTRICT_REF path_to_file,
        this_t::size_type const slot_size, this_t::flags_t const flags ) :
        view_t( this_t::NULL_ADDRESS, slot_size,
                this_t::size_type{ 0 },
                flags | this_t::FLAGS_ALLOW_REMAPPING |
                this_t::FLAGS_ALLOW_REALLOC ),
        m_raw_buffer(),
        m_realloc_factor_nominator(
            this_t::DEFAULT_REALLOC_FACTOR_NOMINATOR ),
        m_realloc_factor_denominator(
            this_t::DEFAULT_REALLOC_FACTOR_DENOMINATOR )
    {
        this_t::status_t const status = this->fromfile( path_to_file );
        ( void )status;
    }

    CBuffer::CBuffer(
        this_t::size_type const max_num_slots,
        this_t::size_type const max_num_objects,
        this_t::size_type const max_num_pointers,
        this_t::size_type const max_num_garbage_ranges,
        this_t::size_type const slot_size,
        this_t::flags_t   const flags ) :
        view_t( this_t::NULL_ADDRESS, slot_size,
                this_t::size_type{ 0 },
                flags | this_t::FLAGS_ALLOW_REMAPPING |
                this_t::FLAGS_ALLOW_REALLOC ),
        m_raw_buffer(),
        m_realloc_factor_nominator(
            this_t::DEFAULT_REALLOC_FACTOR_NOMINATOR ),
        m_realloc_factor_denominator(
            this_t::DEFAULT_REALLOC_FACTOR_DENOMINATOR )
    {
        this_t::status_t const status = this->reserve( max_num_slots,
            max_num_objects, max_num_pointers, max_num_garbage_ranges );
        ( void )status;
    }


    /* --------------------------------------------------------------------- */

    this_t::status_t CBuffer::from_view(
        CBufferView const& SIXTRL_RESTRICT_REF view )
    {
        typedef this_t::size_type size_t;
        this_t::status_t status = st::STATUS_SUCCESS;

        if( ( this->allow_realloc() ) && ( this->allow_remap() ) &&
            ( view.capacity() > size_t{ 0 } ) &&
            ( view.slot_size() >  size_t{ 0 } ) &&
            ( ( view.slot_size() == this->slot_size() ) ||
              ( ( view.slot_size() > this->slot_size() ) &&
                ( view.slot_size() % this->slot_size() == size_t{ 0 } ) ) ) )
        {
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

    this_t::status_t CBuffer::from_flat_buffer(
        ::NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
        this_t::size_type const slot_size )
    {
        typedef this_t::size_type size_t;
        this_t::status_t status = st::STATUS_GENERAL_FAILURE;

        size_t const buffer_size = ::NS(CObjFlatBuffer_size)(
                buffer, slot_size );

        if( ( this->allow_realloc() ) && ( this->allow_remap() ) &&
            ( buffer != SIXTRL_NULLPTR ) && ( slot_size > size_t{ 0 } ) &&
            ( ( slot_size == this->slot_size() ) ||
              ( ( slot_size > this->slot_size() ) &&
                ( slot_size % this->slot_size() == size_t{ 0 } ) ) ) &&
            ( buffer_size > size_t{ 0 } ) )
        {
            status = this->reserve( buffer_size );

            if( status == st::STATUS_SUCCESS )
            {
                std::copy( buffer, buffer + buffer_size, this->p_base_begin() );
                status = this->remap();
            }
        }

        return status;
    }

    this_t::status_t CBuffer::fromfile(
        std::string const& SIXTRL_RESTRICT_REF path_to_file )
    {
        return this->fromfile( path_to_file.c_str() );
    }

    this_t::status_t CBuffer::fromfile(
        char const* SIXTRL_RESTRICT path_to_file )
    {
        typedef this_t::size_type size_t;
        this_t::status_t status = st::STATUS_GENERAL_FAILURE;

        view_t dummy_view( this_t::NULL_ADDRESS, this->slot_size(),
                this_t::size_type{ 0 }, this_t::FLAGS_BASE_DEFAULT );

        size_t requ_capacity = size_t{ 0 };
        st::CBufferView_from_file( dummy_view, path_to_file, &requ_capacity );

        if( requ_capacity == size_t{ 0 } ) return status;
        status = st::STATUS_SUCCESS;

        if( requ_capacity > this->capacity() )
        {
            status = this->reserve( requ_capacity );
        }

        if( status == st::STATUS_SUCCESS )
        {
            status = st::CBufferView_from_file( *this, path_to_file, nullptr );
        }

        return status;
    }

    this_t::status_t CBuffer::tofile(
        std::string const& SIXTRL_RESTRICT_REF path_to_file ) const
    {
        return this->tofile( path_to_file.c_str() );
    }

    this_t::status_t CBuffer::tofile(
        std::string const& SIXTRL_RESTRICT_REF path_to_file,
        this_t::address_t const normalized_base_addr )
    {
        return st::CBuffer_to_file_normalized(
            *this, path_to_file, normalized_base_addr );
    }

    this_t::status_t CBuffer::tofile(
        char const* SIXTRL_RESTRICT path_to_file ) const
    {
        return st::CBuffer_to_file( *this, path_to_file );
    }

    this_t::status_t CBuffer::tofile(
        char const* SIXTRL_RESTRICT path_to_file,
        this_t::address_t const normalized_base_addr )
    {
        return st::CBuffer_to_file_normalized(
            *this, path_to_file, normalized_base_addr );
    }

    /* --------------------------------------------------------------------- */

    this_t::status_t CBuffer::reserve( this_t::size_type new_capacity )
    {
        typedef this_t::address_t addr_t;
        typedef this_t::size_type size_t;

        this_t::status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( !this->allow_realloc() ) ||
            ( this->slot_size() == size_t{ 0 } ) ||
            ( this->m_realloc_factor_denominator == size_t{ 0 } ) ||
            ( this->m_realloc_factor_nominator == size_t{ 0 } ) ||
            ( this->m_realloc_factor_denominator >
              this->m_realloc_factor_nominator ) )
        {
            return status;
        }

        if( new_capacity < this_t::BUFFER_MINIMAL_SIZE )
        {
            new_capacity = this_t::BUFFER_MINIMAL_SIZE;
        }

        new_capacity = ::NS(CObjFlatBuffer_slot_based_size)(
            this->slot_size() + ( this->m_realloc_factor_nominator *
                new_capacity ) / this->m_realloc_factor_denominator,
                    this->slot_size() );

        status = st::STATUS_SUCCESS;
        size_t const current_capacity = this->capacity();
        if( current_capacity < new_capacity )
        {
            this_t::raw_buffer_t new_raw_buffer( new_capacity );

            addr_t const new_store_addr = static_cast< addr_t >(
                reinterpret_cast< std::uintptr_t >( new_raw_buffer.data() ) );
            SIXTRL_ASSERT( new_store_addr != addr_t{ 0 } );

            addr_t const remainder = new_store_addr % this->slot_size();
            addr_t const shift_addr = ( remainder == addr_t{ 0 } )
                ? addr_t{ 0 } : this->slot_size() - remainder;
            new_capacity = ( remainder == addr_t{ 0 } )
                ? new_capacity : new_capacity - this->slot_size();

            if( current_capacity < new_capacity )
            {
                status = st::STATUS_GENERAL_FAILURE;
                addr_t const base_addr = new_store_addr + shift_addr;

                if( ( current_capacity == size_t{ 0 } ) ||
                    ( this->allow_remap() ) )
                {
                    status = st::STATUS_SUCCESS;
                    if( current_capacity > size_t{ 0 } )
                    {
                        std::copy( this->p_base_begin(), this->p_base_end(),
                            reinterpret_cast< this_t::ptr_raw_data_t >(
                                static_cast< std::uintptr_t >( base_addr ) ) );
                    }
                }

                if( status == st::STATUS_SUCCESS )
                {
                    this->m_raw_buffer.swap( new_raw_buffer );
                    this->do_set_base_addr( base_addr );
                    this->do_set_capacity( new_capacity );

                    if( current_capacity == size_t{ 0 } )
                    {
                        status = ::NS(CObjFlatBuffer_init_empty)(
                            this->p_base_begin(), new_capacity,
                                this->slot_size() );
                    }
                    else
                    {
                        status = this->remap();
                    }
                }
            }
        }

        return status;
    }

    this_t::status_t CBuffer::reserve(
        this_t::size_type const max_num_slots,
        this_t::size_type const max_num_objects,
        this_t::size_type const max_num_pointers,
        this_t::size_type const max_num_garbage_ranges )
    {
        typedef this_t::size_type size_t;
        size_t const requ_capacity =
        ::NS(CObjFlatBuffer_calc_required_buffer_size)( this->p_base_begin(),
            max_num_slots, max_num_objects, max_num_pointers,
                max_num_garbage_ranges, this->slot_size() );

        this_t::status_t status = this->reserve( requ_capacity );

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

    this_t::status_t this_t::set_realloc_factor(
        this_t::size_type realloc_factor ) SIXTRL_NOEXCEPT
    {
        this_t::status_t status = st::STATUS_GENERAL_FAILURE;

        if( realloc_factor >= this_t::size_type{ 1 } )
        {
            this->m_realloc_factor_nominator = realloc_factor;
            this->m_realloc_factor_denominator = this_t::size_type{ 1 };
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    this_t::status_t CBuffer::set_realloc_factor_frac(
        this_t::size_type realloc_factor_nominator,
        this_t::size_type realloc_factor_denominator ) SIXTRL_NOEXCEPT
    {
        this_t::status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( realloc_factor_denominator > this_t::size_type{ 0 } ) &&
            ( realloc_factor_denominator <= realloc_factor_nominator ) )
        {
            this->m_realloc_factor_nominator = realloc_factor_nominator;
            this->m_realloc_factor_denominator = realloc_factor_denominator;
            status = st::STATUS_SUCCESS;
        }

        return status;
    }
}

#endif /* C++, Host */

