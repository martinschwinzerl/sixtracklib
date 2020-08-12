#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/cbuffer_view.h"
    #include "sixtracklib_base/cobjects/flat_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstring>
        #include <cstdio>
        #include <string>
        #include <utility>
    #endif /* !defined( C++ ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::CBufferView                         st_view_t;
        typedef st::CBufferView::size_type              st_size_t;
        typedef st::CBufferView::flags_t                st_flags_t;
        typedef st::CBufferView::address_t              st_addr_t;
        typedef st::CBufferView::status_t               st_status_t;
        typedef st::CBufferView::address_diff_t         st_diff_t;
    }

    st_size_t  constexpr CBufferView::DEFAULT_SLOT_SIZE;
    st_size_t  constexpr CBufferView::DEFAULT_HEADER_SIZE;
    st_size_t  constexpr CBufferView::BUFFER_MINIMAL_SIZE;
    st_addr_t  constexpr CBufferView::NULL_ADDRESS;

    st_flags_t constexpr CBufferView::FLAGS_NONE;
    st_flags_t constexpr CBufferView::FLAGS_ALLOW_REMAPPING;
    st_flags_t constexpr CBufferView::FLAGS_ALLOW_ALLOC;
    st_flags_t constexpr CBufferView::FLAGS_ALLOW_APPEND;
    st_flags_t constexpr CBufferView::FLAGS_ALLOW_REALLOC;
    st_flags_t constexpr CBufferView::FLAGS_FORCE_INIT;
    st_flags_t constexpr CBufferView::FLAGS_OWNS_STORED_DATA;
    st_flags_t constexpr CBufferView::FLAGS_SPECIAL_MEMORY;

    st_flags_t constexpr CBufferView::FLAGS_BASE_DEFAULT;

    /* --------------------------------------------------------------------- */

    st_diff_t st_view_t::address_to_offset(
        st_addr_t const address ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_slot_size > st_size_t{ 0 } );
        SIXTRL_ASSERT( this->base_address() % this->m_slot_size ==
                       st_size_t{ 0 } );

        return ( (   address >= this->base_address() ) &&
                 ( ( address % this->m_slot_size ) == st_addr_t{ 0 } ) )
             ? ( address - this->base_address() ) : st_addr_t{ 0 };
    }

    st_addr_t st_view_t::offset_to_address(
        st_diff_t const offset ) const SIXTRL_NOEXCEPT
    {
        if( ::NS(CObjFlatBuffer_check_addr_arithmetic)(
            this->base_address(), offset, this->m_slot_size ) )
        {
            return ::NS(CObjFlatBuffer_perform_addr_shift)(
                this->base_address(), offset, this->m_slot_size );
        }

        return st_view_t::NULL_ADDRESS;
    }


    st_addr_t CBufferView::aligned_base_addr(
        st_addr_t const raw_base_addr,
        st_size_t const raw_capacity,
        st_size_t alignment,
        SIXTRL_ARGPTR_DEC st_size_t* ptr_capacity,
        st_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        st_addr_t base_addr = st::COBJECTS_NULL_ADDRESS;
        st_size_t capacity  = st_size_t{ 0 };
        SIXTRL_ASSERT( slot_size > st_size_t{ 0 } );

        if( alignment == st_size_t{ 0 } )
        {
            alignment = slot_size;
        }
        else if( ( alignment % slot_size ) != st_size_t{ 0 } )
        {
            alignment = ::NS(CObjFlatBuffer_slot_based_size)(
                alignment, slot_size );
        }

        if( ( raw_base_addr != st::COBJECTS_NULL_ADDRESS ) &&
            ( alignment > st_size_t{ 0 } ) && ( raw_capacity >= alignment ) )
        {
            address_t const mis_align = raw_base_addr % alignment;
            base_addr = raw_base_addr;
            capacity  = raw_capacity;

            if( mis_align != address_t{ 0 } )
            {
                st_size_t const offset = alignment - mis_align;
                base_addr += offset;
                capacity  -= offset;
            }
        }

        if(  ptr_capacity != SIXTRL_NULLPTR )
        {
            *ptr_capacity = capacity;
        }

        return base_addr;
    }

    st_size_t st_view_t::required_buffer_length(
        st_size_t const max_num_slots,
        st_size_t const max_num_objects,
        st_size_t const max_num_pointers,
        st_size_t const max_num_garbage_ranges,
        st_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_predict_required_buffer_size)(
            max_num_objects, max_num_slots, max_num_pointers,
                max_num_garbage_ranges, slot_size );
    }

    /* ********************************************************************* */

    #if !defined( _GPUCODE )

    st_status_t CBuffer_to_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView const& SIXTRL_RESTRICT view,
        char const* SIXTRL_RESTRICT path_to_binary_dump )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( path_to_binary_dump != nullptr ) &&
            ( std::strlen( path_to_binary_dump ) > st_size_t{ 0 } ) &&
            (  view.size() > st_size_t{ 0 } ) && ( view.p_base() != nullptr ) &&
            ( !view.needs_remapping() ) )
        {
            ::FILE* fp = std::fopen( path_to_binary_dump, "wb" );

            if( fp != nullptr )
            {
                st_size_t const cnt = std::fwrite( view.p_base(),
                    sizeof( unsigned char ), view.size(), fp );

                if( cnt == view.size() ) status = st::STATUS_SUCCESS;

                std::fclose( fp );
                fp = nullptr;
            }
        }

        return status;
    }

    st_status_t CBuffer_to_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView const& SIXTRL_RESTRICT view,
        std::string const& SIXTRL_RESTRICT_REF path_to_binary_dump )
    {
        return st::CBuffer_to_file( view, path_to_binary_dump.c_str() );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    st_status_t CBuffer_to_file_normalized(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT view,
        char const* SIXTRL_RESTRICT path_to_binary_dump,
        st_addr_t const normalized_base_addr )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        st_addr_t const current_base_addr = view.base_address();

        if( ( path_to_binary_dump != SIXTRL_NULLPTR ) &&
            ( view.slot_size()   > st_size_t{ 0 } ) &&
            ( current_base_addr != st_addr_t{ 0 } ) &&
            ( current_base_addr % view.slot_size() == st_addr_t{ 0 } ) &&
            ( normalized_base_addr % view.slot_size() == st_addr_t{ 0 } ) &&
            ( view.allow_remap() ) )
        {
            st_diff_t const addr_diff =
                ( normalized_base_addr >= current_base_addr )
                    ? normalized_base_addr - current_base_addr
                    : -( static_cast< st_diff_t >(
                        current_base_addr - normalized_base_addr ) );

            status = ( addr_diff != st_diff_t{ 0 } )
                ? ::NS(CObjFlatBuffer_apply_addr_offset)(
                    view.p_base_begin(), addr_diff, view.slot_size() )
                : st::STATUS_SUCCESS;

            if( status == st::STATUS_SUCCESS )
            {
                st_diff_t cmp_addr_diff = st_diff_t{ 0 };

                status = ::NS(CObjFlatBuffer_base_addr_offset)( &cmp_addr_diff,
                            view.p_base_begin(), view.slot_size() );

                if( ( status == st::STATUS_SUCCESS ) &&
                    ( cmp_addr_diff != addr_diff ) )
                {
                    status = st::STATUS_GENERAL_FAILURE;
                }
            }

            if( status == st::STATUS_SUCCESS )
            {
                status = st::CBuffer_to_file( view, path_to_binary_dump );

                if( addr_diff != st_diff_t{ 0 } )
                {
                    status |= ::NS(CObjFlatBuffer_apply_addr_offset)(
                        view.p_base_begin(), -addr_diff, view.slot_size() );
                }
            }
            else
            {
                view.remap();
            }

            SIXTRL_ASSERT( ( status != st::STATUS_SUCCESS ) ||
                           ( !view.needs_remapping() ) );
        }

        return status;
    }

    st_status_t CBuffer_to_file_normalized(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT view,
        std::string const& SIXTRL_RESTRICT_REF path_to_binary_dump,
        st_addr_t const normalized_base_addr )
    {
        return st::CBuffer_to_file_normalized(
            view, path_to_binary_dump.c_str(), normalized_base_addr );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    st_status_t CBufferView_from_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT view,
        char const* SIXTRL_RESTRICT_REF path_to_binary_dump,
        SIXTRL_BUFFER_ARGPTR_DEC st_size_t* SIXTRL_RESTRICT ptr_requ_capacity )
    {
        st_status_t status = st::STATUS_SUCCESS;

        if( ( path_to_binary_dump != nullptr ) &&
            ( std::strlen( path_to_binary_dump ) > st_size_t{ 0 } ) &&
            ( view.slot_size() > st_size_t{ 0 } ) &&
            ( view.capacity() > st_size_t{ 0 } ) &&
            ( view.p_base() != nullptr ) &&
            ( view.allow_remap() ) && ( view.allow_allocate() ) )
        {
            st_size_t size_of_file = st_size_t{ 0 };
            ::FILE* fp = std::fopen( path_to_binary_dump, "rb" );

            if( fp != nullptr )
            {
                std::fseek( fp, 0, SEEK_END );
                long const temp_length = std::ftell( fp );
                std::fclose( fp );
                fp = nullptr;

                if( temp_length >= 0 )
                {
                    size_of_file = static_cast< st_size_t >( temp_length );
                    fp = std::fopen( path_to_binary_dump, "rb" );
                }
            }

            if( ( fp != nullptr ) &&
                ( size_of_file >= st_view_t::DEFAULT_HEADER_SIZE ) &&
                ( size_of_file <= view.capacity() ) )
            {
                st_size_t const cnt = std::fread( view.p_base(),
                    sizeof( unsigned char ), size_of_file, fp );

                if( cnt == size_of_file )
                {
                    status = view.remap();
                }
            }

            if( fp != nullptr )
            {
                std::fclose( fp );
                fp = nullptr;
            }

            if( ptr_requ_capacity != nullptr )
            {
                *ptr_requ_capacity = ::NS(CObjFlatBuffer_slot_based_size)(
                    size_of_file, view.slot_size() );
            }
        }

        return status;
    }

    st_status_t CBufferView_from_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT view,
        std::string const& SIXTRL_RESTRICT_REF path_to_binary_dump,
        SIXTRL_BUFFER_ARGPTR_DEC st_size_t* SIXTRL_RESTRICT ptr_requ_capacity )
    {
        return st::CBufferView_from_file( view, path_to_binary_dump.c_str(),
            ptr_requ_capacity );
    }

    #endif /* !defined( _GPUCODE ) */
}

#endif /* __cplusplus */
