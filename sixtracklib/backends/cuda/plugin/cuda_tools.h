#ifndef SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CUDA_TOOLS_H__
#define SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CUDA_TOOLS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/definitions.h"
    #include "sixtracklib/backends/cuda/dlib.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
        ( SIXTRACKL_ENABLE_BACKEND_CUDA == 1 )
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

#if !defined( SIXTRL_CUDA_DRIVER_API_NOTHROW_CALL )
    #if defined( NDEBUG )
        #define SIXTRL_CUDA_DRIVER_API_NOTHROW_CALL( fn, args ) \
         do { ::CUresult const ret = fn args ; \
            SIXTRL_ASSERT( ret == ::CUDA_SUCCESS ); }while( 0 )
    #else
        #define SIXTRL_CUDA_DRIVER_API_NOTHROW_CALL( fn, args ) \
        do { ::CUresult const ret = fn args ; \
            if( ret != ::CUDA_SUCCESS ) { \
                std::ostringstream a2str; \
                if( ret == ::CUDA_ERROR_NOT_INITIALIZED ) { \
                    a2str << "error : failure during call to fn " \
                          << #fn << ": thread has not been initialized ->\r\n"\
                          << "error : ensure ::cuInit() is called for this " \
                          << "thread!";\
                } else if( ret == ::CUDA_ERROR_DEINITIALIZED ) { \
                    a2str << "info  : call to fn " << #fn \
                          << " happened after cuda driver had already been " \
                          << "shutdown -> \r\n" \
                          << "info  : call backend shutdown function"; \
                } else { \
                    a2str << "error : failure during call to fn " \
                          << #fn << ": "; \
                    SIXTRL_CXX_NAMESPACE::CudaError_print_error_name( \
                        a2str, ret, "unknown_error_name" ) << ": "; \
                    SIXTRL_CXX_NAMESPACE::CudaError_print_error_description( \
                        a2str, ret ); \
                    a2str << "\r\nerror code result = " << ret; \
                }\
                if( ret == ::CUDA_ERROR_DEINITIALIZED ) { \
                    std::cout << a2str.str() << std::endl; \
                } else { \
                    std::cerr << a2str.str() << std::endl; \
                    SIXTRL_ASSERT( ret == ::CUDA_SUCCESS ); } }\
        } while( 0 )
    #endif /* NDEBUG */
#endif /* !defined( SIXTRL_CUDA_DRIVER_API_NOTHROW_CALL ) */

#if !defined( SIXTRL_CUDA_DRIVER_API_CALL )
    #if defined( SIXTRL_CUDA_PLUGIN_EXCEPTION_ON_ERROR ) && \
        ( SIXTRL_CUDA_PLUGIN_EXCEPTION_ON_ERROR == 1 )

        #define SIXTRL_CUDA_DRIVER_API_CALL( fn, args ) \
        do {\
            ::CUresult const ret = fn args ; \
            if( ret != ::CUDA_SUCCESS ) { \
                std::ostringstream a2str; \
                if( ret == ::CUDA_ERROR_NOT_INITIALIZED ) { \
                    a2str << "error : failure during call to fn " \
                          << #fn << ": thread has not been initialized ->\r\n"\
                          << "error : ensure ::cuInit() is called for " \
                          << "this thread!";\
                } else if( ret == ::CUDA_ERROR_DEINITIALIZED ) { \
                    a2str << "info  : call to fn " << #fn \
                          << " happened after cuda driver had already been " \
                          << "shutdown -> \r\n" \
                          << "info  : call backend shutdown function"; \
                } else { \
                    a2str << "error : failure during call to fn " \
                          << #fn << ": "; \
                    SIXTRL_CXX_NAMESPACE::CudaError_print_error_name( \
                        a2str, ret, "unknown_error_name" ) << ": "; \
                    SIXTRL_CXX_NAMESPACE::CudaError_print_error_description( \
                        a2str, ret ); \
                    a2str << "\r\nerror code result = " << ret; } \
                throw std::runtime_error( a2str.str() ); } }while( 0 )
    #elif !defined( NDEBUG ) /* do not use exceptions but print minimal debug message */
        #define SIXTRL_CUDA_DRIVER_API_CALL( fn, args ) \
        do { ::CUresult const ret = fn args ; \
             if( ret != ::CUDA_SUCCESS ) {\
                 std::cerr << "error during call to fn " << #fn \
                           << ": error code = " << ret << std::endl; } \
             SIXTRL_ASSERT( ret == ::CUDA_SUCCESS ); }while( 0 )
    #else /* no exceptions and not in debug mode -> use SIXTRL_ASSERT to punt */
        #define SIXTRL_CUDA_DRIVER_API_CALL( fn, args ) \
        do { ::CUresult const ret = fn args ; \
             SIXTRL_ASSERT( ret == ::CUDA_SUCCESS ); }while( 0 )
    #endif /* use exceptions ? */
#endif /* !defined( SIXTRL_CUDA_DRIVER_API_CALL ) */


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
            char const* error_name = nullptr;
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
            char const* error_msg = nullptr;
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

#endif /* SIXTRACKLIB_ENABLE_BACKEND_CUDA */
#endif /* SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CUDA_TOOLS_H__ */
