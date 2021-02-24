#if defined( __cplusplus ) && !defined( _GPUCODE )
#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/address_manipulations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if !defined( _GPUCODE )
        #include <cstddef>
        #include <cstring>
        #include <cstdio>
        #include <string>
        #include <utility>
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::CBufferView                  st_view_type;
        typedef st::CBufferView::size_type       st_size_type;
        typedef st::CBufferView::flags_type      st_flags_type;
        typedef st::CBufferView::addr_type       st_addr_type;
        typedef st::CBufferView::status_type     st_status_type;
        typedef st::CBufferView::addr_diff_type  st_addr_diff_type;
    }

    st_size_type  constexpr CBufferView::DEFAULT_SLOT_SIZE;
    st_size_type  constexpr CBufferView::DEFAULT_HEADER_SIZE;
    st_size_type  constexpr CBufferView::BUFFER_MINIMAL_SIZE;
    st_addr_type  constexpr CBufferView::NULL_ADDRESS;

    st_flags_type constexpr CBufferView::FLAGS_NONE;
    st_flags_type constexpr CBufferView::FLAGS_ALLOW_REMAPPING;
    st_flags_type constexpr CBufferView::FLAGS_ALLOW_ALLOC;
    st_flags_type constexpr CBufferView::FLAGS_ALLOW_APPEND;
    st_flags_type constexpr CBufferView::FLAGS_ALLOW_REALLOC;
    st_flags_type constexpr CBufferView::FLAGS_FORCE_INIT;
    st_flags_type constexpr CBufferView::FLAGS_OWNS_STORED_DATA;
    st_flags_type constexpr CBufferView::FLAGS_SPECIAL_MEMORY;

    st_flags_type constexpr CBufferView::FLAGS_BASE_DEFAULT;

    /* --------------------------------------------------------------------- */

    st_addr_diff_type st_view_type::address_to_offset(
        st_addr_type const address ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_slot_size > st_size_type{ 0 } );
        SIXTRL_ASSERT( this->base_address() % this->m_slot_size ==
                       st_size_type{ 0 } );

        return ( (   address >= this->base_address() ) &&
                 ( ( address % this->m_slot_size ) == st_addr_type{ 0 } ) )
             ? ( address - this->base_address() ) : st_addr_type{ 0 };
    }

    st_addr_type st_view_type::offset_to_address(
        st_addr_diff_type const offset ) const SIXTRL_NOEXCEPT
    {
        if( ::NS(CObjFlatBuffer_check_addr_arithmetic)(
            this->base_address(), offset, this->m_slot_size ) )
        {
            return ::NS(CObjFlatBuffer_perform_addr_shift)(
                this->base_address(), offset, this->m_slot_size );
        }

        return st_view_type::NULL_ADDRESS;
    }


    st_addr_type CBufferView::aligned_base_addr(
        st_addr_type const raw_base_addr,
        st_size_type const raw_capacity, st_size_type alignment,
        SIXTRL_ARGPTR_DEC st_size_type* ptr_capacity,
        st_size_type const slot_size ) SIXTRL_NOEXCEPT {
        st_addr_type base_addr = st::COBJECTS_NULL_ADDRESS;
        st_size_type capacity  = st_size_type{ 0 };
        SIXTRL_ASSERT( slot_size > st_size_type{ 0 } );

        if( alignment == st_size_type{ 0 } ) alignment = slot_size;
        else if( ( alignment % slot_size ) != st_size_type{ 0 } )
        {
            alignment = ::NS(CObjFlatBuffer_slot_based_size)(
                alignment, slot_size );
        }

        if( ( raw_base_addr != st::COBJECTS_NULL_ADDRESS ) &&
            ( alignment > st_size_type{ 0 } ) && ( raw_capacity >= alignment ) )
        {
            st_addr_type const mis_align = raw_base_addr % alignment;
            base_addr = raw_base_addr;
            capacity  = raw_capacity;

            if( mis_align != st_addr_type{ 0 } )
            {
                st_size_type const offset = alignment - mis_align;
                base_addr += offset;
                capacity  -= offset;
            }
        }

        if(  ptr_capacity != SIXTRL_NULLPTR ) *ptr_capacity = capacity;
        return base_addr;
    }

    st_size_type st_view_type::required_buffer_length(
        st_size_type const max_num_slots,
        st_size_type const max_num_objects,
        st_size_type const max_num_pointers,
        st_size_type const max_num_garbage_ranges,
        st_size_type const slot_size ) SIXTRL_NOEXCEPT {
        return ::NS(CObjFlatBuffer_predict_required_buffer_size)(
            max_num_objects, max_num_slots, max_num_pointers,
                max_num_garbage_ranges, slot_size ); }

    /* ********************************************************************* */

    #if !defined( _GPUCODE )

    st_status_type CBuffer_to_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView const& SIXTRL_RESTRICT view,
        char const* SIXTRL_RESTRICT path_to_binary_dump ) {
        st_status_type status = st::STATUS_GENERAL_FAILURE;
        if( ( path_to_binary_dump != nullptr ) &&
            ( std::strlen( path_to_binary_dump ) > st_size_type{ 0 } ) &&
            (  view.size() > st_size_type{ 0 } ) &&
            ( view.p_base() != nullptr ) && ( !view.needs_remapping() ) ) {
            ::FILE* fp = std::fopen( path_to_binary_dump, "wb" );
            if( fp != nullptr ) {
                st_size_type const cnt = std::fwrite( view.p_base(),
                    sizeof( unsigned char ), view.size(), fp );

                if( cnt == view.size() ) status = st::STATUS_SUCCESS;
                std::fclose( fp );
                fp = nullptr;
            }
        }
        return status; }

    st_status_type CBuffer_to_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView const& SIXTRL_RESTRICT view,
        std::string const& SIXTRL_RESTRICT_REF path_to_binary_dump ) {
        return st::CBuffer_to_file( view, path_to_binary_dump.c_str() ); }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    st_status_type CBuffer_to_file_normalized(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT view,
        char const* SIXTRL_RESTRICT path_to_binary_dump,
        st_addr_type const normalized_base_addr ) {
        st_status_type status = st::STATUS_GENERAL_FAILURE;
        st_addr_type const current_base_addr = view.base_address();
        if( ( path_to_binary_dump != SIXTRL_NULLPTR ) &&
            ( view.slot_size()   > st_size_type{ 0 } ) &&
            ( current_base_addr != st_addr_type{ 0 } ) &&
            ( current_base_addr % view.slot_size() == st_addr_type{ 0 } ) &&
            ( normalized_base_addr % view.slot_size() == st_addr_type{ 0 } ) &&
            ( view.allow_remap() ) ) {
            st_addr_diff_type const addr_diff =
                ( normalized_base_addr >= current_base_addr )
                    ? normalized_base_addr - current_base_addr
                    : -( static_cast< st_addr_diff_type >(
                        current_base_addr - normalized_base_addr ) );
            status = ( addr_diff != st_addr_diff_type{ 0 } )
                ? ::NS(CObjFlatBuffer_apply_addr_offset)(
                    view.p_base_begin(), addr_diff, view.slot_size() )
                : st::STATUS_SUCCESS;

            if( status == st::STATUS_SUCCESS ) {
                st_addr_diff_type cmp_addr_diff = st_addr_diff_type{ 0 };
                status = ::NS(CObjFlatBuffer_base_addr_offset)( &cmp_addr_diff,
                            view.p_base_begin(), view.slot_size() );
                if( ( status == st::STATUS_SUCCESS ) &&
                    ( cmp_addr_diff != addr_diff ) ) {
                    status = st::STATUS_GENERAL_FAILURE; } }

            if( status == st::STATUS_SUCCESS ) {
                status = st::CBuffer_to_file( view, path_to_binary_dump );
                if( addr_diff != st_addr_diff_type{ 0 } ) {
                    status |= ::NS(CObjFlatBuffer_apply_addr_offset)(
                        view.p_base_begin(), -addr_diff, view.slot_size() ); } }
            else { view.remap(); }
            SIXTRL_ASSERT( ( status != st::STATUS_SUCCESS ) ||
                           ( !view.needs_remapping() ) );
        }
        return status; }

    st_status_type CBuffer_to_file_normalized(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT view,
        std::string const& SIXTRL_RESTRICT_REF path_to_binary_dump,
        st_addr_type const normalized_base_addr ) {
        return st::CBuffer_to_file_normalized(
            view, path_to_binary_dump.c_str(), normalized_base_addr ); }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    st_status_type CBufferView_from_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT view,
        char const* SIXTRL_RESTRICT_REF path_to_binary_dump,
        SIXTRL_BUFFER_ARGPTR_DEC st_size_type*
            SIXTRL_RESTRICT ptr_requ_capacity ) {
        st_status_type status = st::STATUS_SUCCESS;
        if( ( path_to_binary_dump != nullptr ) &&
            ( std::strlen( path_to_binary_dump ) > st_size_type{ 0 } ) &&
            ( view.slot_size() > st_size_type{ 0 } ) &&
            ( view.capacity() > st_size_type{ 0 } ) &&
            ( view.p_base() != nullptr ) &&
            ( view.allow_remap() ) && ( view.allow_allocate() ) ) {
            st_size_type size_of_file = st_size_type{ 0 };
            ::FILE* fp = std::fopen( path_to_binary_dump, "rb" );
            if( fp != nullptr ) {
                std::fseek( fp, 0, SEEK_END );
                long const temp_length = std::ftell( fp );
                std::fclose( fp );
                fp = nullptr;
                if( temp_length >= 0 ) {
                    size_of_file = static_cast< st_size_type >( temp_length );
                    fp = std::fopen( path_to_binary_dump, "rb" ); }
            }
            if( ( fp != nullptr ) &&
                ( size_of_file >= st_view_type::DEFAULT_HEADER_SIZE ) &&
                ( size_of_file <= view.capacity() ) ) {
                st_size_type const cnt = std::fread( view.p_base(),
                    sizeof( unsigned char ), size_of_file, fp );
                if( cnt == size_of_file ) status = view.remap(); }

            if( fp != nullptr ) {
                std::fclose( fp );
                fp = nullptr; }

            if( ptr_requ_capacity != nullptr )
                *ptr_requ_capacity = ::NS(CObjFlatBuffer_slot_based_size)(
                    size_of_file, view.slot_size() );
        }

        return status; }

    st_status_type CBufferView_from_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT view,
        std::string const& SIXTRL_RESTRICT_REF path_to_binary_dump,
        SIXTRL_BUFFER_ARGPTR_DEC st_size_type* SIXTRL_RESTRICT
            ptr_requ_capacity ) {
        return st::CBufferView_from_file( view, path_to_binary_dump.c_str(),
            ptr_requ_capacity ); }

    #endif /* !defined( _GPUCODE ) */
} /* end: SIXTRL_CXX_NAMESPACE */

/* ************************************************************************** */

SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* NS(CBufferView_new)(
    ::NS(cobj_addr_type) const base_addr, ::NS(cobj_size_type) const capacity ) {
    return new SIXTRL_CXX_NAMESPACE::CBufferView( base_addr,
        SIXTRL_CXX_NAMESPACE::CBufferView::DEFAULT_SLOT_SIZE, capacity,
            SIXTRL_CXX_NAMESPACE::CBufferView::FLAGS_BASE_DEFAULT ); }

SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)*
NS(CBufferView_new_detailed)( ::NS(cobj_addr_type) const base_addr,
    ::NS(cobj_size_type) const slot_size, ::NS(cobj_size_type) const capacity,
    ::NS(cobj_buffer_flags_type) const flags ) {
    return new SIXTRL_CXX_NAMESPACE::CBufferView(
        base_addr, slot_size, capacity, flags ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_BUFFER_ARGPTR_DEC void NS(CBuffer_delete)( SIXTRL_BUFFER_ARGPTR_DEC
    ::NS(CBufferView)* SIXTRL_RESTRICT view ) { delete view; }

/* ------------------------------------------------------------------------- */

::NS(cobj_size_type) NS(CBuffer_required_buffer_length)(
    ::NS(cobj_size_type) const max_num_slots,
    ::NS(cobj_size_type) const max_num_objects,
    ::NS(cobj_size_type) const max_num_pointers,
    ::NS(cobj_size_type) const max_num_garbage_ranges,
    ::NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return SIXTRL_CXX_NAMESPACE::CBufferView::required_buffer_length(
        max_num_slots, max_num_objects, max_num_pointers, max_num_garbage_ranges,
            slot_size ); }

::NS(cobj_addr_type) NS(CBuffer_aligned_base_addr)(
    ::NS(cobj_addr_type) const raw_base_addr,
    ::NS(cobj_size_type) const raw_capacity,
    ::NS(cobj_size_type) const alignment,
    ::NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC ::NS(cobj_size_type)* ptr_capacity ) SIXTRL_NOEXCEPT {
    return SIXTRL_CXX_NAMESPACE::CBufferView::aligned_base_addr( raw_base_addr,
        raw_capacity, alignment, ptr_capacity, slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

::NS(cobj_buffer_flags_type) NS(CBuffer_flags)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->flags() : ::NS(cobj_buffer_flags_type){ 0 }; }

bool NS(CBuffer_allow_remap)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( ( b != nullptr ) && ( b->allow_remap() ) ); }

bool NS(CBuffer_allow_allocate)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( ( b != nullptr ) && ( b->allow_allocate() ) ); }

bool NS(CBuffer_allow_realloc)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( ( b != nullptr ) && ( b->allow_realloc() ) ); }

bool NS(CBuffer_allow_append)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( ( b != nullptr ) && ( b->allow_append() ) ); }

bool NS(CBuffer_owns_stored_data)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( ( b != nullptr ) && ( b->owns_stored_data() ) ); }

bool NS(CBuffer_has_special_memory)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( ( b != nullptr ) && ( b->has_special_memory() ) ); }

/* -------------------------------------------------------------------------- */

::NS(cobj_size_type) NS(CBuffer_slot_size)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->slot_size() : ::NS(cobj_size_type){ 0 }; }

/* -------------------------------------------------------------------------- */

::NS(cobj_size_type) NS(CBuffer_size)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->size() : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_capacity)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->capacity() : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_size_header)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->size_header() : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_size_section_header)( SIXTRL_BUFFER_ARGPTR_DEC
        const SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b,
    ::NS(cobj_size_type) const sec_id ) SIXTRL_NOEXCEPT {
    return ( b != nullptr )
        ? b->size_section_header( sec_id ) : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_size_slots)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->size_slots() : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_size_objects)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->size_objects() : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_size_pointers)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->size_pointers() : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_size_garbage)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->size_garbage() : ::NS(cobj_size_type) { 0 }; }

::NS(cobj_size_type) NS(CBuffer_n_slots)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->n_slots() : ::NS(cobj_size_type) { 0 }; }

::NS(cobj_size_type) NS(CBuffer_n_objects)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->n_objects() : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_n_pointers)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->n_pointers() : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_n_garbage)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->n_garbage() : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_max_slots)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->max_slots() : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_max_objects)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->max_objects() : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_max_pointers)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->max_pointers() : ::NS(cobj_size_type){ 0 }; }

::NS(cobj_size_type) NS(CBuffer_max_garbage)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->max_garbage() : ::NS(cobj_size_type){ 0 }; }

/* -------------------------------------------------------------------------- */

::NS(cobj_addr_type) NS(CBuffer_begin_addr)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->begin_addr() : ::NS(COBJECTS_NULL_ADDRESS); }

::NS(cobj_addr_type) NS(CBuffer_end_addr)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->end_addr() : ::NS(COBJECTS_NULL_ADDRESS); }

::NS(cobj_addr_type) NS(CBuffer_begin_addr_slots)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->begin_addr_slots() : ::NS(COBJECTS_NULL_ADDRESS);
}

::NS(cobj_addr_type) NS(CBuffer_begin_addr_objects)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->begin_addr_objects() : ::NS(COBJECTS_NULL_ADDRESS);
}

::NS(cobj_addr_type) NS(CBuffer_begin_addr_pointers)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->begin_addr_pointers() : ::NS(COBJECTS_NULL_ADDRESS);
}

::NS(cobj_addr_type) NS(CBuffer_begin_addr_garbage)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->begin_addr_garbage() : ::NS(COBJECTS_NULL_ADDRESS);
}

::NS(cobj_addr_type) NS(CBuffer_end_addr_slots)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->end_addr_slots() : ::NS(COBJECTS_NULL_ADDRESS);
}

::NS(cobj_addr_type) NS(CBuffer_end_addr_objects)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->end_addr_objects() : ::NS(COBJECTS_NULL_ADDRESS);
}

::NS(cobj_addr_type) NS(CBuffer_end_addr_pointers)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->end_addr_pointers() : ::NS(COBJECTS_NULL_ADDRESS);
}

::NS(cobj_addr_type) NS(CBuffer_end_addr_garbage)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->end_addr_garbage() : ::NS(COBJECTS_NULL_ADDRESS);
}

/* -------------------------------------------------------------------------- */

::NS(cobj_addr_type) NS(CBuffer_base)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->base() : ::NS(COBJECTS_NULL_ADDRESS); }

::NS(cobj_addr_type) NS(CBuffer_base_address)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->base_address() : ::NS(COBJECTS_NULL_ADDRESS); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_base)( SIXTRL_BUFFER_ARGPTR_DEC
    const SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( b != nullptr ) ? b->p_base() : nullptr; }

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_base_begin)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_base_begin() : nullptr; }

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_base_end)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_base_begin() : nullptr; }


::NS(cobj_raw_pointer) NS(CBuffer_p_base_begin)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_base_begin() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_base_end)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_base_end() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_base)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_base() : nullptr; }

/* -------------------------------------------------------------------------- */

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_slots)( SIXTRL_BUFFER_ARGPTR_DEC
    const SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( b != nullptr ) ? b->p_slots() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_slots)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
        return ( b != nullptr ) ? b->p_slots() : nullptr; }

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_slots_begin)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_slots() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_slots_begin)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
        return ( b != nullptr ) ? b->p_slots() : nullptr; }

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_slots_end)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_slots_end() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_slots_end)( SIXTRL_BUFFER_ARGPTR_DEC
        SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_slots_end() : nullptr; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_objects)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_objects() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_objects)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_objects() : nullptr; }

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_objects_begin)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_objects() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_objects_begin)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_objects() : nullptr; }

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_objects_end)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_objects_end() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_objects_end)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_objects_end() : nullptr; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_pointers)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_pointers() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_pointers)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_pointers() : nullptr; }

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_pointers_begin)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_pointers() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_pointers_begin)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_pointers() : nullptr; }

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_pointers_end)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_pointers_end() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_pointers_end)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_pointers_end() : nullptr; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_garbage)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_garbage() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_garbage)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_garbage() : nullptr; }

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_garbage_begin)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_garbage() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_garbage_begin)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_garbage() : nullptr; }

::NS(cobj_raw_const_pointer) NS(CBuffer_p_const_garbage_end)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_garbage_end() : nullptr; }

::NS(cobj_raw_pointer) NS(CBuffer_p_garbage_end)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->p_garbage_end() : nullptr; }

/* -------------------------------------------------------------------------- */

::NS(cobj_obj_index_const_pointer) NS(CBuffer_const_objects_begin)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->objects_begin() : nullptr; }

::NS(cobj_obj_index_pointer) NS(CBuffer_objects_begin)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->objects_begin() : nullptr; }

::NS(cobj_obj_index_const_pointer) NS(CBuffer_const_objects_end)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->objects_end() : nullptr; }

::NS(cobj_obj_index_pointer) NS(CBuffer_objects_end)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->objects_end() : nullptr; }

::NS(cobj_obj_index_const_pointer) NS(CBuffer_const_index_at)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b, NS(cobj_size_type) const pos ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->index_at( pos ) : nullptr; }

::NS(cobj_obj_index_pointer) NS(CBuffer_index_at)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT b, NS(cobj_size_type) const pos ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->index_at( pos ) : nullptr; }

/* -------------------------------------------------------------------------- */

::NS(cobj_addr_diff_type) NS(CBuffer_address_to_offset)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b, NS(cobj_addr_type) const address ) SIXTRL_NOEXCEPT {
    return ( b != nullptr )
        ? b->address_to_offset( address )
        : ::NS(cobj_addr_diff_type){ 0 }; }

::NS(cobj_addr_type) NS(CBuffer_offset_to_address)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT b, NS(cobj_addr_diff_type) const offset ) SIXTRL_NOEXCEPT
    { return ( b != nullptr )
            ? b->offset_to_address( offset ) : ::NS(cobj_addr_type){ 0 }; }

/* -------------------------------------------------------------------------- */

bool NS(CBuffer_has_capacity_for_allocate)( SIXTRL_BUFFER_ARGPTR_DEC const
        SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b,
    ::NS(cobj_size_type) const max_num_slots,
    ::NS(cobj_size_type) const max_num_objects,
    ::NS(cobj_size_type) const max_num_pointers,
    ::NS(cobj_size_type) const max_num_garbage_ranges ) SIXTRL_NOEXCEPT {
    return ( ( b != nullptr ) && ( b->has_capacity_for_allocate( max_num_slots,
            max_num_objects, max_num_pointers, max_num_garbage_ranges ) ) ); }

bool NS(CBuffer_can_allocate)( SIXTRL_BUFFER_ARGPTR_DEC const
        SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b,
    ::NS(cobj_size_type) const max_num_slots,
    ::NS(cobj_size_type) const max_num_objects,
    ::NS(cobj_size_type) const max_num_pointers,
    ::NS(cobj_size_type) const max_num_garbage_ranges ) SIXTRL_NOEXCEPT {
    return ( ( b != nullptr ) && ( b->can_allocate( max_num_slots,
        max_num_objects, max_num_pointers, max_num_garbage_ranges ) ) ); }

::NS(cobj_status_type) NS(CBuffer_allocate)( SIXTRL_BUFFER_ARGPTR_DEC
        SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b,
    ::NS(cobj_size_type) const max_num_slots,
    ::NS(cobj_size_type) const max_num_objects,
    ::NS(cobj_size_type) const max_num_pointers,
    ::NS(cobj_size_type) const max_num_garbage_ranges ) SIXTRL_NOEXCEPT {
    return ( b != nullptr )
        ? b->allocate( max_num_slots, max_num_objects, max_num_pointers,
                max_num_garbage_ranges )
        : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

::NS(cobj_status_type) NS(CBuffer_reallocate)( SIXTRL_BUFFER_ARGPTR_DEC
        SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b,
    ::NS(cobj_size_type) const max_num_slots,
    ::NS(cobj_size_type) const max_num_objects,
    ::NS(cobj_size_type) const max_num_pointers,
    ::NS(cobj_size_type) const max_num_garbage_ranges ) SIXTRL_NOEXCEPT {
    return ( b != nullptr )
        ? b->reallocate( max_num_slots, max_num_objects, max_num_pointers,
                max_num_garbage_ranges )
        : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

/* -------------------------------------------------------------------------- */

bool NS(CBuffer_needs_remapping)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( ( b != nullptr ) && ( b->needs_remapping() ) ); }

bool NS(CBuffer_can_remap)( SIXTRL_BUFFER_ARGPTR_DEC const
    SIXTRL_CXX_NAMESPACE::CBufferView *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( ( b != nullptr ) && ( b->can_remap() ) ); }

::NS(cobj_status_type) NS(CBuffer_remap)( SIXTRL_BUFFER_ARGPTR_DEC
    SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != nullptr ) ? b->remap()
        : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

#endif /* __cplusplus */
