#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"

    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/garbage_range.h"
    #include "sixtracklib/common/cobjects/address_manipulations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

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
        typedef st::CBufferView                         _view_t;
        typedef st::CBufferView::size_type              _size_t;
        typedef st::CBufferView::flags_t                _flags_t;
        typedef st::CBufferView::address_t              _addr_t;
        typedef st::CBufferView::status_t               _status_t;
        typedef st::CBufferView::address_diff_t         _diff_t;
    }

    _size_t  constexpr CBufferView::DEFAULT_SLOT_SIZE;
    _size_t  constexpr CBufferView::DEFAULT_HEADER_SIZE;
    _size_t  constexpr CBufferView::BUFFER_MINIMAL_SIZE;
    _addr_t  constexpr CBufferView::NULL_ADDRESS;

    _flags_t constexpr CBufferView::FLAGS_NONE;
    _flags_t constexpr CBufferView::FLAGS_ALLOW_REMAPPING;
    _flags_t constexpr CBufferView::FLAGS_ALLOW_ALLOC;
    _flags_t constexpr CBufferView::FLAGS_ALLOW_APPEND;
    _flags_t constexpr CBufferView::FLAGS_ALLOW_REALLOC;
    _flags_t constexpr CBufferView::FLAGS_FORCE_INIT;
    _flags_t constexpr CBufferView::FLAGS_OWNS_STORED_DATA;
    _flags_t constexpr CBufferView::FLAGS_SPECIAL_MEMORY;

    _flags_t constexpr CBufferView::FLAGS_BASE_DEFAULT;

    /* --------------------------------------------------------------------- */

    _diff_t _view_t::address_to_offset(
        _addr_t const address ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_slot_size > _size_t{ 0 } );
        SIXTRL_ASSERT( this->base_address() % this->m_slot_size ==
                       _size_t{ 0 } );

        return ( (   address >= this->base_address() ) &&
                 ( ( address % this->m_slot_size ) == _addr_t{ 0 } ) )
             ? ( address - this->base_address() ) : _addr_t{ 0 };
    }

    _addr_t _view_t::offset_to_address(
        _diff_t const offset ) const SIXTRL_NOEXCEPT
    {
        if( ::NS(CObjFlatBuffer_check_addr_arithmetic)(
            this->base_address(), offset, this->m_slot_size ) )
        {
            return ::NS(CObjFlatBuffer_perform_addr_shift)(
                this->base_address(), offset, this->m_slot_size );
        }

        return _view_t::NULL_ADDRESS;
    }

    /* ********************************************************************* */

    #if !defined( _GPUCODE )

    _status_t CBuffer_to_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView const& SIXTRL_RESTRICT view,
        char const* SIXTRL_RESTRICT path_to_binary_dump )
    {
        _status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( path_to_binary_dump != nullptr ) &&
            ( std::strlen( path_to_binary_dump ) > _size_t{ 0 } ) &&
            (  view.size() > _size_t{ 0 } ) && ( view.p_base() != nullptr ) &&
            ( !view.needs_remapping() ) )
        {
            ::FILE* fp = std::fopen( path_to_binary_dump, "wb" );

            if( fp != nullptr )
            {
                _size_t const cnt = std::fwrite( view.p_base(),
                    sizeof( unsigned char ), view.size(), fp );

                if( cnt == view.size() ) status = st::ARCH_STATUS_SUCCESS;

                std::fclose( fp );
                fp = nullptr;
            }
        }

        return status;
    }

    _status_t CBuffer_to_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView const& SIXTRL_RESTRICT view,
        std::string const& SIXTRL_RESTRICT_REF path_to_binary_dump )
    {
        return st::CBuffer_to_file( view, path_to_binary_dump.c_str() );
    }

    _status_t CBufferView_from_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT view,
        char const* SIXTRL_RESTRICT_REF path_to_binary_dump,
        SIXTRL_BUFFER_ARGPTR_DEC _size_t* SIXTRL_RESTRICT ptr_requ_capacity )
    {
        _status_t status = st::ARCH_STATUS_SUCCESS;

        if( ( path_to_binary_dump != nullptr ) &&
            ( std::strlen( path_to_binary_dump ) > _size_t{ 0 } ) &&
            ( view.slot_size() > _size_t{ 0 } ) &&
            ( view.capacity() > _size_t{ 0 } ) &&
            ( view.p_base() != nullptr ) &&
            ( view.allow_remap() ) && ( view.allow_allocate() ) )
        {
            _size_t size_of_file = _size_t{ 0 };
            ::FILE* fp = std::fopen( path_to_binary_dump, "rb" );

            if( fp != nullptr )
            {
                std::fseek( fp, 0, SEEK_END );
                long const temp_length = std::ftell( fp );
                std::fclose( fp );
                fp = nullptr;

                if( temp_length >= 0 )
                {
                    size_of_file = static_cast< _size_t >( temp_length );
                    fp = std::fopen( path_to_binary_dump, "rb" );
                }
            }

            if( ( fp != nullptr ) &&
                ( size_of_file >= _view_t::DEFAULT_HEADER_SIZE ) &&
                ( size_of_file <= view.capacity() ) )
            {
                _size_t const cnt = std::fread( view.p_base(),
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
                *ptr_requ_capacity = ::NS(ManagedBuffer_get_slot_based_length)(
                    size_of_file, view.slot_size() );
            }
        }

        return status;
    }

    _status_t CBufferView_from_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT view,
        std::string const& SIXTRL_RESTRICT_REF path_to_binary_dump,
        SIXTRL_BUFFER_ARGPTR_DEC _size_t* SIXTRL_RESTRICT ptr_requ_capacity )
    {
        return st::CBufferView_from_file( view, path_to_binary_dump.c_str(),
            ptr_requ_capacity );
    }

    #endif /* !defined( _GPUCODE ) */
}

#endif /* __cplusplus */
