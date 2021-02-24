#ifndef SIXTRACKLIB_COMMON_COBJECTS_CBUFFER_CXX_HPP_
#define SIXTRACKLIB_COMMON_COBJECTS_CBUFFER_CXX_HPP_

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && c++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    struct CBuffer : public CBufferView
    {
        SIXTRL_FN explicit CBuffer(
            size_type const capacity = size_type{
                SIXTRL_CBUFFER_DEFAULT_MIN_BUFFER_SIZE },
            size_type const slot_size = size_type{
                SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE } );

        SIXTRL_FN CBuffer(
            size_type const max_n_slots,
            size_type const max_n_objects,
            size_type const max_n_pointers,
            size_type const max_n_garbage_ranges = size_type{ 0 },
            size_type const slot_size = size_type{
                SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE },
            flags_type const flags = flags_type{
                SIXTRL_CBUFFER_FLAGS_DEFAULT_BUFFER_FLAGS } );

        SIXTRL_FN explicit CBuffer(
            char const* SIXTRL_RESTRICT path_to_file,
            size_type const slot_size =
                size_type{ SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE } );

        SIXTRL_FN explicit CBuffer(
            std::string const& SIXTRL_RESTRICT_REF path_to_file,
            size_type const slot_size =
                size_type{ SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE } );

        SIXTRL_FN CBuffer( SIXTRL_CBUFFER_ARGPTR_DEC CBuffer const& ) = default;
        SIXTRL_FN CBuffer( SIXTRL_CBUFFER_ARGPTR_DEC CBuffer&& ) = default;

        SIXTRL_FN CBuffer( SIXTRL_CBUFFER_ARGPTR_DEC CBufferView const&
            SIXTRL_RESTRICT_REF orig ) : CBufferView( orig ) {}

        SIXTRL_FN CBuffer( SIXTRL_CBUFFER_ARGPTR_DEC CBufferView&& orig ) :
            CBufferView( std::move( orig ) ) {}

        SIXTRL_FN CBuffer( SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) const&
            SIXTRL_RESTRICT_REF orig ) : CBufferView( orig ) {}

        SIXTRL_FN CBuffer( SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)&& orig ) :
            CBufferView( std::move( orig ) ) {}

        SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC CBuffer&
        operator=( SIXTRL_CBUFFER_ARGPTR_DEC CBuffer const& ) = default;

        SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC CBuffer&
        operator=( SIXTRL_CBUFFER_ARGPTR_DEC CBufferView const& rhs ) {
            CBufferView::operator=( rhs );
            return *this; }

        SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC CBuffer&
        operator=( SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) const& rhs ) {
            CBufferView::operator=( rhs );
            return *this; }

        SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC CBuffer&
        operator=( SIXTRL_CBUFFER_ARGPTR_DEC CBuffer&& ) = default;

        SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC CBuffer& operator=(
            SIXTRL_CBUFFER_ARGPTR_DEC CBufferView&& rhs ) {
            CBufferView::operator=( std::move( rhs ) );
            return *this; }

        SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC CBuffer& operator=(
            SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)&& rhs ) {
            CBufferView::operator=( std::move( rhs ) );
            return *this; }

        SIXTRL_FN virtual ~CBuffer() = default;

        SIXTRL_FN status_type from_file(
            char const* SIXTRL_RESTRICT path_to_file );

        SIXTRL_FN status_type from_file(
            std::string const& SIXTRL_RESTRICT_REF path_to_file );

        SIXTRL_FN status_type to_file(
            char const* SIXTRL_RESTRICT path_to_file );

        SIXTRL_FN status_type to_file(
            std::string const& SIXTRL_RESTRICT_REF path_to_file );

        SIXTRL_FN status_type to_file_normalised(
            char const* SIXTRL_RESTRICT path_to_file,
            addr_type const normalised_base_addr );

        SIXTRL_FN status_type to_file_normalised(
            std::string const& SIXTRL_RESTRICT_REF path_to_file,
            addr_type const normalised_base_addr );
    };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_COBJECTS_CBUFFER_CXX_HPP_ */
