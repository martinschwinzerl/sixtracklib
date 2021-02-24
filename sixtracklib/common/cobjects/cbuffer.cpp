#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/cbuffer.hpp"
    #include "sixtracklib/common/internal/file_tools.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <stdexcept>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && c++ */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using st_size_t   = st::CBuffer::size_type;
        using st_addr_t   = st::CBuffer::addr_type;
        using st_status_t = st::CBuffer::status_type;
        using st_flags_t  = st::CBufferView::flags_type;
    }

    constexpr st_size_t st::CBufferView::DEFAULT_SLOT_SIZE;
    constexpr st_size_t st::CBufferView::DEFAULT_HEADER_SIZE;
    constexpr st_size_t st::CBufferView::DEFAULT_MINIMAL_SIZE;

    constexpr st_addr_t st::CBufferView::NULL_ADDRESS;

    constexpr st_flags_t st::CBufferView::FLAGS_NONE;
    constexpr st_flags_t st::CBufferView::FLAGS_ALLOW_REMAPPING;
    constexpr st_flags_t st::CBufferView::FLAGS_ALLOW_ALLOC;
    constexpr st_flags_t st::CBufferView::FLAGS_ALLOW_REALLOC;
    constexpr st_flags_t st::CBufferView::FLAGS_ALLOW_APPEND;
    constexpr st_flags_t st::CBufferView::FLAGS_FORCE_INIT;
    constexpr st_flags_t st::CBufferView::FLAGS_OWNS_STORED_DATA;
    constexpr st_flags_t st::CBufferView::FLAGS_SPECIAL_MEMORY;
    constexpr st_flags_t st::CBufferView::FLAGS_STORAGE_IS_C_PTR;
    constexpr st_flags_t st::CBufferView::FLAGS_VIEW_DEFAULT;
    constexpr st_flags_t st::CBufferView::FLAGS_BUFFER_DEFAULT;

    /* ********************************************************************** */

    CBuffer::CBuffer( st_size_t const capacity, st_size_t const slot_size ) :
        st::CBufferView( st::COBJECTS_NULL_ADDRESS, capacity, slot_size,
            st::CBufferView::FLAGS_BUFFER_DEFAULT )
    {
    }

    CBuffer::CBuffer( char const* SIXTRL_RESTRICT path_to_file,
        size_type const slot_size ) :
        st::CBufferView( st::COBJECTS_NULL_ADDRESS,
            st::File_num_bytes( path_to_file,
                ::NS(CBuffer_min_buffer_size)( slot_size ) ), slot_size,
                    st::CBufferView::FLAGS_BUFFER_DEFAULT )
    {
        SIXTRL_ASSERT( ::NS(CBuffer_owns_stored_data)( this->as_c_api() ) );
        st_status_t const status = ::NS(CBuffer_from_file)(
            this->as_c_api(), path_to_file );
        if( status != st::STATUS_SUCCESS )
        {
            throw std::runtime_error( "unable to load from file" );
        }
    }

    CBuffer::CBuffer( st_size_t const max_n_slots, st_size_t const max_n_objects,
        st_size_t const max_n_pointers, st_size_t const max_n_garbage_ranges,
        st_size_t const slot_size, flags_type const flags ) :
        st::CBufferView( st::COBJECTS_NULL_ADDRESS,
            ::NS(CObjFlatBuffer_predict_required_buffer_size)(
                max_n_slots, max_n_objects, max_n_pointers, max_n_garbage_ranges,
                    slot_size ), slot_size, flags )
    {
        st_status_t const status = this->allocate(
            max_n_slots, max_n_objects, max_n_pointers, max_n_garbage_ranges );

        if( status != st::STATUS_SUCCESS )
        {
            throw std::runtime_error( "unable to init with given structure" );
        }
    }

    CBuffer::CBuffer( std::string const& SIXTRL_RESTRICT_REF path_to_file,
        st_size_t const slot_size ) :
        st::CBufferView( st::COBJECTS_NULL_ADDRESS,
            st::File_num_bytes( path_to_file, ::NS(CBuffer_min_buffer_size)(
                slot_size ) ), slot_size, st::CBufferView::FLAGS_BUFFER_DEFAULT )
    {
        SIXTRL_ASSERT( ::NS(CBuffer_owns_stored_data)( this->as_c_api() ) );
        st_status_t const status = ::NS(CBuffer_from_file)(
            this->as_c_api(), path_to_file.c_str() );

        if( status != st::STATUS_SUCCESS )
        {
            throw std::runtime_error( "unable to load from file" );
        }
    }

    st_status_t CBuffer::from_file( char const* SIXTRL_RESTRICT path_to_file ) {
        return ::NS(CBuffer_from_file)( this->as_c_api(), path_to_file ); }

    st_status_t CBuffer::from_file(
        std::string const& SIXTRL_RESTRICT_REF path_to_file ) {
        return ::NS(CBuffer_from_file)( this->as_c_api(), path_to_file.c_str() );
    }

    st_status_t CBuffer::to_file(
        char const* SIXTRL_RESTRICT path_to_file ) {
        return ::NS(CBuffer_to_file)( this->as_c_api(), path_to_file ); }

    st_status_t CBuffer::to_file(
        std::string const& SIXTRL_RESTRICT_REF path_to_file ) {
        return ::NS(CBuffer_to_file)( this->as_c_api(), path_to_file.c_str() );
    }

    st_status_t CBuffer::to_file_normalised(
        char const* SIXTRL_RESTRICT path_to_file,
        st_addr_t const normalised_base_addr ) {
        return ::NS(CBuffer_to_file_normalised)(
            this->as_c_api(), path_to_file, normalised_base_addr ); }

    st_status_t CBuffer::to_file_normalised(
        std::string const& SIXTRL_RESTRICT_REF path_to_file,
        st_addr_t const normalised_base_addr ) {
        return ::NS(CBuffer_to_file_normalised)(
            this->as_c_api(), path_to_file.c_str(), normalised_base_addr ); }
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
