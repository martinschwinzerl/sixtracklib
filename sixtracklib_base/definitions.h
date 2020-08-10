#ifndef SIXTRACKLIB_BASE_DEFINITIONS_H__
#define SIXTRACKLIB_BASE_DEFINITIONS_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cassert>
        #include <cstddef>
        #include <cstdlib>
        #include <cstring>
        #include <cstdint>
    #else
        #include <assert.h>
        #include <stddef.h>
        #include <stdlib.h>
        #include <string.h>
        #include <stdint.h>
    #endif /* __cplusplus */
#endif /* !defined( _GPUCODE ) || defined(__CUDACC__ ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/export.h"
    #include "sixtracklib_base/generated/namespace.h"
    #include "sixtracklib_base/internal/base_types.h"
    #include "sixtracklib_base/internal/namespace_defines.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_ARGPTR_DEC )
    #define SIXTRL_ARGPTR_DEC_UNDEF
    #define SIXTRL_ARGPTR_DEC
#endif /* defined( SIXTRL_ARGPTR_DEC ) */

#if !defined( SIXTRL_DATAPTR_DEC )
    #define SIXTRL_DATAPTR_DEC_UNDEF
    #define SIXTRL_DATAPTR_DEC
#endif /* defined( SIXTRL_DATAPTR_DEC ) */

#if !defined( SIXTRL_ALIGN_NUM )
    #define SIXTRL_ALIGN_NUM 8u
#endif /* !defined( SIXTRL_ALIGN_NUM ) */

#if !defined( SIXTRL_STATUS_SUCCESS )
    #define SIXTRL_STATUS_SUCCESS 0
#endif /* SIXTRL_STATUS_SUCCESS */

#if !defined( SIXTRL_STATUS_GENERAL_FAILURE )
    #define SIXTRL_STATUS_GENERAL_FAILURE -1
#endif /* SIXTRL_STATUS_GENERAL_FAILURE */

#if !defined( _GPUCODE )
    #if !defined (SIXTRL_ASSERT )
        #define SIXTRL_ASSERT( expr ) assert( ( expr ) )
    #endif /* !defined( SIXTRL_ASSERT ) */

    /* ---------------------------------------------------------------- */
    /* Type decorators -> these go in front of the SIXTRL_*_T type      */

    #if !defined( SIXTRL_PRIVATE_DEC )
        #define SIXTRL_PRIVATE_DEC
    #endif /* !defined( SIXTRL_PRIVATE_DEC ) */

    #if !defined( SIXTRL_LOCAL_DEC )
        #define SIXTRL_LOCAL_DEC
    #endif /* !defined( SIXTRL_LOCAL_DEC ) */

    #if !defined( SIXTRL_GLOBAL_DEC )
        #define SIXTRL_GLOBAL_DEC
    #endif /* !defined( SIXTRL_GLOBAL_DEC ) */

    #if !defined( SIXTRL_CONSTANT_DEC )
        #define SIXTRL_CONSTANT_DEC
    #endif /* !defined( SIXTRL_CONSTANT_DEC ) */

    /* ---------------------------------------------------------------- */
    /* extern, static, inline and restrict keywords: */

    #if !defined(SIXTRL_EXTERN)
        #if !defined( __cplusplus ) && !defined(_GPUCODE)
            #define SIXTRL_EXTERN extern
        #else
            #define SIXTRL_EXTERN
        #endif
    #endif

    #if !defined( SIXTRL_STATIC )
        #define SIXTRL_STATIC static
    #endif /* !defined( SIXTRL_STATIC ) */

    #if !defined( SIXTRL_STATIC_VAR )
            #define SIXTRL_STATIC_VAR static
    #endif /* !defined( SIXTRL_STATIC_VAR ) */

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    #if !defined( SIXTRL_INLINE )
        #define SIXTRL_INLINE inline
    #endif /* !defined( SIXTRL_INLINE ) */

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    #if defined( SIXTRL_RESTRICT )
        #undef  SIXTRL_RESTRICT
    #endif /* SIXTRL_RESTRICT */

    #if defined( SIXTRL_RESTRICT_REF )
        #undef  SIXTRL_RESTRICT_REF
    #endif /* SIXTRL_RESTRICT_REF */

    #ifdef __cplusplus

        #if ( ( defined( __clang__ ) ) || \
            ( ( ( defined( __GNUC__ ) ) && ( __GNUC__ >= 3 ) ) ) )

            #define SIXTRL_RESTRICT     __restrict__
            #define SIXTRL_RESTRICT_REF __restrict__

        #elif ( defined( _MSC_VER ) && _MSC_VER >= 1600 )

            #define SIXTRL_RESTRICT __restrict

        #endif /* ( defined( _MSC_VER ) && _MSC_VER >= 1600 ) */

    #else /* __cplusplus */

        #if ( ( defined( __clang__ ) ) || \
            ( ( ( defined( __GNUC__ ) ) && ( __GNUC__ >= 3 ) ) ) )

            #if ( __STDC_VERSION__ >= 199901L )
                #define SIXTRL_RESTRICT restrict /* TODO: Check if clang supports this! */
            #else
                #define SIXTRL_RESTRICT __restrict__
            #endif /* C99 support */

        #endif /* gcc/mingw or clang */

    #endif /*defined( __cplusplus ) */

    #ifndef SIXTRL_RESTRICT
        #define SIXTRL_RESTRICT
    #endif /* SIXTRL_RESTRICT */

    #ifndef SIXTRL_RESTRICT_REF
        #define SIXTRL_RESTRICT_REF
    #endif /* SIXTRL_RESTRICT_REF */

    /* ---------------------------------------------------------------- */
    /* kernel and restrict key word for kernel parameters: */

    #if !defined( SIXTRL_GPUKERNEL )
        #define SIXTRL_GPUKERNEL
    #endif /* !defined( SIXTRL_GPU_KERNEL ) */

    #if !defined( SIXTRL_GPUKERNEL_RESTRICT )
        #define   SIXTRL_GPUKERNEL_RESTRICT
    #endif /* !defined( SIXTRL_KERNELPARAM_RESTRICT ) */

    #if !defined( SIXTRL_GPUKERNEL_RESTRICT_REF )
        #define   SIXTRL_GPUKERNEL_RESTRICT_REF
    #endif /* !defined( SIXTRL_KERNELPARAM_RESTRICT_REF ) */

    /* ---------------------------------------------------------------- */
    /* Function header decorators:                                      */

    #if !defined( __CUDACC__ )

        #if !defined( SIXTRL_HOST_FN )
            #define   SIXTRL_HOST_FN
        #endif /* SIXTRL_HOST_FN */

        #if !defined( SIXTRL_DEVICE_FN )
            #define   SIXTRL_DEVICE_FN
        #endif /* SIXTRL_DEVICE_FN */

        #if !defined( SIXTRL_FN )
            #define   SIXTRL_FN
        #endif /* SIXTRL_FN */

    #else /* defined( __CUDACC__ ) */

        #if !defined( SIXTRL_HOST_FN)
            #define   SIXTRL_HOST_FN __host__
        #endif /* SIXTRL_HOST_FN */

        #if !defined( SIXTRL_DEVICE_FN )
            #define   SIXTRL_DEVICE_FN __device__
        #endif /* SIXTRL_DEVICE_FN */

        #if !defined( SIXTRL_FN )
            #define   SIXTRL_FN __host__ __device__
        #endif /* SIXTRL_FN */

    #endif /* defined( __CUDACC__ ) */

#endif /* !defined( _GPUCODE ) */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_ISFINITE )
    #if defined( __cplusplus ) && ( __cplusplus >= 201103L )
        #define SIXTRL_ISFINITE( x ) std::isfinite( x )
    #elif defined( __STDC_VERSION__ ) && ( __STDC_VERSION__ >= 199901L )
        #define SIXTRL_ISFINITE( x ) isfinite( x )
    #else
        #define SIXTRL_ISFINITE( x ) ( 1 )
    #endif /* defined( __cplusplus ) */
#endif /* defined( SIXTRL_ISFINITE ) */

/* ------------------------------------------------------------------------- */

#if defined(__CUDACC__) // NVCC
    #define SIXTRL_ALIGN(n) __align__((n))
#elif defined(__GNUC__) || defined(__clang__) // GCC, CLANG
    #define SIXTRL_ALIGN(n) __attribute__((aligned((n))))
#elif defined(_MSC_VER) || defined(__INTEL_COMPILER) // MSVC, INTEL
    #define SIXTRL_ALIGN(n) __declspec(align((n)))
#else
    #error "Please provide a definition for SIXTRL_ALIGN macro for your host compiler!"
#endif /* SIXTRL_ALIGN */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_NULLPTR )
    #if  defined( __cplusplus ) && __cplusplus >= 201103L && \
        !defined( __CUDACC__  )
        #define SIXTRL_NULLPTR nullptr

    #elif !defined( __cplusplus ) && defined( __CUDACC__ )
        #define SIXTRL_NULLPTR NULL
    #else
        #define SIXTRL_NULLPTR 0
    #endif /* nullptr */
#endif /* !defined( SIXTRL_NULLPTR ) */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_CONSTEXPR_OR_CONST ) || !defined( SIXTRL_CONSTEXPR ) || \
    !defined( SIXTRL_STATIC_CONSTEXPR_FN )
    #if defined( __cplusplus ) && ( __cplusplus >= 201103L )
        #if ( defined( __GNUC__  ) && ( ( __GNUC__ >= 5 ) || \
              ( ( __GNUC__ == 4  ) && ( __GNUC_MINOR__ >= 8 ) ) ) ) || \
            ( defined( __CUDACC__ ) && defined( CUDA_VERSION ) && \
                ( CUDA_VERSION >= 800 ) ) || \
            ( defined( _MSC_VER  ) && ( _MSC_VER >= 1900 ) ) || \
            ( defined( __clang__ ) && ( ( __clang_major__ > 3 ) || \
              ( ( __clang_major__ == 3 ) && ( __clang_minor__ >= 3 ) ) ) ) || \
            ( defined( __INTEL_COMPILER ) && ( __INTEL_COMPILER >= 14 ) )

            #if !defined( SIXTRL_CONSTEXPR_OR_CONST )
                #define SIXTRL_CONSTEXPR_OR_CONST constexpr
            #endif /* !defined( SIXTRL_CONSTEXPR_OR_CONST ) */

            #if !defined( SIXTRL_CONSTEXPR )
                #define SIXTRL_CONSTEXPR constexpr
            #endif /* !defined( SIXTRL_CONSTEXPR_OR_CONST ) */

            #if !defined( SIXTRL_STATIC_CONSTEXPR_FN )
                #define SIXTRL_STATIC_CONSTEXPR_FN static constexpr
            #endif /* !defined( SIXTRL_STATIC_CONSTEXPR_FN ) */

        #endif /* compilers */

    #endif /*  defined( __cplusplus ) && ( __cplusplus >= 201103L ) */

    #if !defined( SIXTRL_CONSTEXPR_OR_CONST )
        #define SIXTRL_CONSTEXPR_OR_CONST const
    #endif /* !defined( SIXTRL_CONSTEXPR_OR_CONST ) */

    #if !defined( SIXTRL_CONSTEXPR )
        #define SIXTRL_CONSTEXPR
    #endif /* !defined( SIXTRL_CONSTEXPR_OR_CONST ) */

    #if !defined( SIXTRL_STATIC_CONSTEXPR_FN )
        #define SIXTRL_STATIC_CONSTEXPR_FN static
    #endif /* !defined( SIXTRL_STATIC_CONSTEXPR_FN ) */

#endif /*!defined( SIXTRL_CONSTEXPR_OR_CONST )||!defined( SIXTRL_CONSTEXPR ) */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_NOEXCEPT ) || !defined( SIXTRL_NOEXCEPT_COND )
    #if defined( __cplusplus ) && ( __cplusplus >= 201103L )
        #if ( defined( __GNUC__   ) && ( ( __GNUC__ >= 5 ) || \
              ( ( __GNUC__ == 4   ) && ( __GNUC_MINOR__ >= 8 ) ) ) ) || \
            ( defined( __CUDACC__ ) && defined( CUDA_VERSION ) && \
                ( CUDA_VERSION >= 800 ) ) || \
            ( defined( _MSC_VER   ) && ( _MSC_VER >= 1900 ) ) || \
            ( defined( __clang__  ) && ( ( __clang_major__ > 3 ) || \
              ( ( __clang_major__ == 3 ) && ( __clang_minor__ >= 3 ) ) ) ) || \
            ( defined( __INTEL_COMPILER ) && ( __INTEL_COMPILER >= 14 ) )

            #if !defined( SIXTRL_NOEXCEPT )
                #define SIXTRL_NOEXCEPT noexcept
            #endif /* !defined( SIXTRL_NOEXCEPT ) */

            #if !defined( SIXTRL_NOEXCEPT_COND )
                #define SIXTRL_NOEXCEPT_COND( cond ) noexcept( ( cond ) )
            #endif /* !defined( SIXTRL_NOEXCEPT_COND ) */

        #endif /* compilers */

    #endif /*  defined( __cplusplus ) && ( __cplusplus >= 201103L ) */

    #if !defined( SIXTRL_NOEXCEPT )
        #define SIXTRL_NOEXCEPT
    #endif /* !defined( SIXTRL_NOEXCEPT ) */

    #if !defined( SIXTRL_NOEXCEPT_COND )
        #define SIXTRL_NOEXCEPT_COND( cond )
    #endif /* !defined( SIXTRL_NOEXCEPT_COND ) */
#endif /* !defined( SIXTRL_NOEXCEPT ) || !defined( SIXTRL_NOEXCEPT_COND ) */


#if !defined( _GPUCODE )
#if defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC_VAR const NS(status_t) NS(STATUS_SUCCESS) = (
    NS(status_t) )SIXTRL_STATUS_SUCCESS;

SIXTRL_STATIC_VAR const NS(status_t) NS(STATUS_GENERAL_FAILURE) = (
    NS(status_t) )SIXTRL_STATUS_GENERAL_FAILURE;

#if defined( __cplusplus )
}
#endif /* C++, Host */
#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    static SIXTRL_CONSTEXPR_OR_CONST status_t STATUS_SUCCESS = static_cast<
        status_t >( SIXTRL_STATUS_SUCCESS );

    static SIXTRL_CONSTEXPR_OR_CONST status_t STATUS_GENERAL_FAILURE =
        static_cast< status_t >( SIXTRL_STATUS_GENERAL_FAILURE );

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
#endif /* SIXTRACKLIB_BASE_DEFINITIONS_H__ */
