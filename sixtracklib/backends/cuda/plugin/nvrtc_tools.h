#ifndef SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_NVRTC_TOOLS_H__
#define SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_NVRTC_TOOLS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/definitions.h"
    #include "sixtracklib/backends/cuda/dlib.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
        ( SIXTRACKL_ENABLE_BACKEND_CUDA == 1 )
        #include <nvrtc.h>
        #include <cuda.h>
    #endif /* cuda backend enabled */

    #if defined( __cplusplus )
        #include <iostream>
        #include <ostream>
        #include <sstream>
        #include <stdexcept>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
    ( SIXTRACKL_ENABLE_BACKEND_CUDA == 1 ) && \
    defined( SIXTRL_CUDA_PLUGIN_BUILT )

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_STATIC SIXTRL_HOST_FN std::ostream&
    NvrtcError_print_error_string(
        std::ostream& SIXTRL_RESTRICT_REF ostr, ::nvrtcResult const err_code,
        std::string const& SIXTRL_RESTRICT_REF default_str = std::string{} );
}
#endif /* C++ */


#if !defined( SIXTRL_NVRTC_NOTHROW_API_CALL )
    #if defined( NDEBUG )
        #define SIXTRL_NVRTC_NOTHROW_API_CALL( fn, args ) \
         do { ::nvrtcResult const ret = fn args ; \
            SIXTRL_ASSERT( ret == ::NVRTC_SUCCESS ); }while( 0 )
    #else
        #define SIXTRL_NVRTC_NOTHROW_API_CALL( fn, args ) \
        do { ::nvrtcResult const ret = fn args ; \
            if( ret != ::NVRTC_SUCCESS ) { \
                std::ostringstream a2str; \
                a2str << "error : failure during call to fn " \
                      << #fn << ": "; \
                SIXTRL_CXX_NAMESPACE::NvrtcError_print_error_string( \
                    a2str, ret, "NVRTC_ERROR unknown" ); \
                    a2str << ", error code result = " << ret; \
                    std::cerr << a2str.str() << std::endl; } \
            SIXTRL_ASSERT( ret == ::NVRTC_SUCCESS ); } while( 0 )
    #endif /* NDEBUG */
#endif /* !defined( SIXTRL_NVRTC_NOTHROW_API_CALL ) */

#if !defined( SIXTRL_NVRTC_API_CALL )
    #if defined( SIXTRL_CUDA_PLUGIN_EXCEPTION_ON_ERROR ) && \
        ( SIXTRL_CUDA_PLUGIN_EXCEPTION_ON_ERROR == 1 )

        #define SIXTRL_NVRTC_API_CALL( fn, args ) \
        do {\
            ::nvrtcResult const ret = fn args ; \
            if( ret != ::NVRTC_SUCCESS ) { \
                std::ostringstream a2str; \
                a2str << "error : failure during call to fn " \
                      << #fn << ": "; \
                SIXTRL_CXX_NAMESPACE::NvrtcError_print_error_string( \
                    a2str, ret, "NVRTC_ERROR unknown" ); \
                    a2str << ", error code result = " << ret; \
                throw std::runtime_error( a2str.str() ); } }while( 0 )
    #elif !defined( NDEBUG ) /* do not use exceptions but print minimal debug message */
        #define SIXTRL_NVRTC_API_CALL( fn, args ) \
        do { ::nvrtcResult const ret = fn args ; \
             if( ret != ::NVRTC_SUCCESS ) {\
                 std::cerr << "error during call to fn " << #fn \
                           << ": error code = " << ret << std::endl; } \
             SIXTRL_ASSERT( ret == ::NVRTC_SUCCESS ); }while( 0 )
    #else /* no exceptions and not in debug mode -> use SIXTRL_ASSERT to punt */
        #define SIXTRL_NVRTC_API_CALL( fn, args ) \
        do { ::nvrtcResult const ret = fn args ; \
             SIXTRL_ASSERT( ret == ::NVRTC_SUCCESS ); }while( 0 )
    #endif /* use exceptions ? */
#endif /* !defined( SIXTRL_CUDA_DRIVER_API_CALL ) */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!                    Inline Implementations                     !!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE std::ostream& NvrtcError_print_error_string(
        std::ostream& SIXTRL_RESTRICT_REF ostr, ::nvrtcResult const err_code,
        std::string const& SIXTRL_RESTRICT_REF default_str )
    {
        if( err_code != ::NVRTC_SUCCESS )
        {
            char const* error_name = ::nvrtcGetErrorString( err_code );
            if( error_name != nullptr ) { ostr << error_name; }
            else { ostr << default_str; }
        }

        return ostr;
    }
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_ENABLE_BACKEND_CUDA */
#endif /* SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_NVRTC_TOOLS_H__ */
