#ifndef SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CUDA_TOOLS_H__
#define SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CUDA_TOOLS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/definitions.h"
#endif /* C++ */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cuda.h>
    #if defined( __cplusplus )
        #include <ostream>
        #include <stdexcept>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE )

SIXTRL_STATIC SIXTRL_HOST_FN void NS(Cuda_init_thread)(
    unsigned int const flags );

SIXTRL_STATIC SIXTRL_HOST_FN NS(status_t) NS(Cuda_curesult_to_status)(
    CUresult const result ) SIXTRL_NOEXCEPT;

#endif /* _GPUCODE */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_STATIC SIXTRL_HOST_FN std::ostream&
    CudaError_print_error_name(
        std::ostream& SIXTRL_RESTRICT_REF ostr, ::CUresult const err_code,
        std::string const& SIXTRL_RESTRICT_REF default_str = std::string{} );

    SIXTRL_STATIC SIXTRL_HOST_FN std::ostream&
    CudaError_print_error_description(
        std::ostream& SIXTRL_RESTRICT_REF ostr, ::CUresult const err_code,
        std::string const& SIXTRL_RESTRICT_REF default_str = std::string{} );
}
#endif /* C++ */

/* ------------------------------------------------------------------------ */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE )

SIXTRL_INLINE void NS(Cuda_init_thread)( unsigned int const flags )
{
    CUresult const ret = cuInit( flags );
    SIXTRL_ASSERT( ret == CUDA_SUCCESS );
    ( void )ret;
}

SIXTRL_INLINE NS(status_t) NS(Cuda_curesult_to_status)(
    CUresult const result ) SIXTRL_NOEXCEPT
{
    return ( result == CUDA_SUCCESS )
        ? ( NS(status_t) )SIXTRL_STATUS_SUCCESS
        : ( NS(status_t) )SIXTRL_STATUS_GENERAL_FAILURE;
}

#endif /* _GPUCODE */
#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE std::ostream& CudaError_print_error_name(
        std::ostream& SIXTRL_RESTRICT_REF ostr, ::CUresult const err_code,
        std::string const& SIXTRL_RESTRICT_REF default_str )
    {
        if( err_code != ::CUDA_SUCCESS )
        {
            char* error_name = nullptr;
            ::CUresult const ret = ::cuGetErrorName( err_code, &error_name );
            SIXTRL_ASSERT( ret == ::CUDA_SUCCESS );
            ( void )ret;

            if( error_name != nullptr )
            {
                ostr << error_name;
            }
            else
            {
                ostr << default_str;
            }
        }

        return ostr;
    }

    SIXTRL_INLINE std::ostream& CudaError_print_error_description(
        std::ostream& SIXTRL_RESTRICT_REF ostr, ::CUresult const err_code,
        std::string const& SIXTRL_RESTRICT_REF default_str )
    {
        if( err_code != ::CUDA_SUCCESS )
        {
            char* error_msg = nullptr;
            ::CUresult const ret = ::cuGetErrorString( err_code, &error_msg );
            SIXTRL_ASSERT( ret == ::CUDA_SUCCESS );
            ( void )ret;

            if( error_msg != nullptr )
            {
                ostr << error_msg;
            }
            else
            {
                ostr << default_str;
            }
        }

        return ostr;
    }
}
#endif /* C++ */

#endif /* SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CUDA_TOOLS_H__ */