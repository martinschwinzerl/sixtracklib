#ifndef SIXTRACKLIB_COMMON_BACKENDS_COMPILE_COMPABILITY_H__
#define SIXTRACKLIB_COMMON_BACKENDS_COMPILE_COMPABILITY_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/backends/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_UNUSED )
    #if defined( __cplusplus )
        #define SIXTRL_UNUSED( arg ) /* can be omitted -> nothing to do here! */
    #elif ( ( defined( __GNUC__ ) && ( __GNUC__ >= 3 ) ) ) || \
          ( defined( __clang__ ) )
        #define SIXTRL_UNUSED( arg ) arg __attribute__((unused))
    #else
        #define SIXTRL_UNUSED( arg ) arg
    #endif /* C++ / compiler */
#endif /* !defined( SIXTRL_UNUSED ) */

#if !defined( SIXTRL_RESTRICT )
    #if defined(__CUDACC__) // NVCC
        #define SIXTRL_RESTRICT __restrict__
    #elif defined( __STDC_VERSION__ ) && ( __STDC_VERSION__ >= 199901L )
        #define SIXTRL_RESTRICT restrict
    #elif defined(__GNUC__) || defined(__clang__) // GCC, CLANG
        #define SIXTRL_RESTRICT __restrict__
    #elif defined(__INTEL_COMPILER) // MSVC, INTEL
        #define SIXTRL_RESTRICT __restrict
    #elif defined(_MSC_VER)
        #define SIXTRL_RESTRICT __declspec(restrict)
    #else
        #error "Please provide a definition for SIXTRL_RESTRICT macro for your host compiler!"
    #endif /* SIXTRL_RESTRICT */
#endif /* !defined( SIXTRL_RESTRICT ) */

#if defined( __cplusplus ) && !defined( SIXTRL_RESTRICT_REF )
    #if defined(__CUDACC__) // NVCC
        #define SIXTRL_RESTRICT_REF __restrict__
    #elif defined(__GNUC__) || defined(__clang__) // GCC, CLANG
        #define SIXTRL_RESTRICT_REF __restrict__
    #elif defined(__INTEL_COMPILER) // MSVC, INTEL
        #define SIXTRL_RESTRICT_REF __restrict
    #elif defined(_MSC_VER)
        #define SIXTRL_RESTRICT_REF __declspec(restrict)
    #else
        #error "Please provide a definition for SIXTRL_RESTRICT_REF macro for your host compiler!"
    #endif /* SIXTRL_RESTRICT_REF */
#endif /* !defined( SIXTRL_RESTRICT_REF ) */

#if !defined( SIXTRL_ALIGN )
    #if defined(__CUDACC__) // NVCC
        #define SIXTRL_ALIGN(n) __align__((n))
    #elif defined(__GNUC__) || defined(__clang__) // GCC, CLANG
        #define SIXTRL_ALIGN(n) __attribute__((aligned((n))))
    #elif defined(__INTEL_COMPILER) // MSVC, INTEL
        #define SIXTRL_ALIGN(n) __declspec(align((n)))
    #elif defined(_MSC_VER)
        #define SIXTRL_ALIGN(n) __declspec(align((n)))
    #else
        #error "Please provide a definition for SIXTRL_ALIGN macro for your host compiler!"
    #endif /* SIXTRL_ALIGN */
#endif /* !defined( SIXTRL_ALIGN ) */

#if !defined( SIXTRL_FIELD_ALIGN )
    #if defined(__CUDACC__) // NVCC
        #define SIXTRL_FIELD_ALIGN(n) __align__((n))
    #elif defined(__GNUC__) || defined(__clang__) // GCC, CLANG
        #define SIXTRL_FIELD_ALIGN(n) __attribute__((aligned((n))))
    #elif defined(__INTEL_COMPILER) // MSVC, INTEL
        #define SIXTRL_FIELD_ALIGN(n) __declspec(align((n)))
    #elif defined(_MSC_VER)
        #define SIXTRL_FIELD_ALIGN(n)
    #else
        #error "Please provide a definition for SIXTRL_FIELD_ALIGN macro for your host compiler!"
    #endif /* SIXTRL_ALIGN */
#endif /* !defined( SIXTRL_FIELD_ALIGN ) */

#if !defined( SIXTRL_STRUCT_ALIGN )
    #if defined(__CUDACC__) // NVCC
        #define SIXTRL_STRUCT_ALIGN(n) __align__((n))
    #elif defined(__GNUC__) || defined(__clang__) // GCC, CLANG
        #define SIXTRL_STRUCT_ALIGN(n) __attribute__((aligned((n))))
    #elif defined(__INTEL_COMPILER) // MSVC, INTEL
        #define SIXTRL_STRUCT_ALIGN(n) __declspec(align((n)))
    #elif defined(_MSC_VER)
        #define SIXTRL_STRUCT_ALIGN(n) __declspec(align((n)))
    #else
        #error "Please provide a definition for SIXTRL_STRUCT_ALIGN macro for your host compiler!"
    #endif /* SIXTRL_ALIGN */
#endif /* !defined( SIXTRL_STRUCT_ALIGN ) */

/* -------------------------------------------------------------------------- */

#if !defined( SIXTRL_NULL_ADDR )
    #if defined( __CUDACC__ ) || defined( __CUDA_ARCH__ )
        #define SIXTRL_NULL_ADDR ( ( uintptr_t )NULL )
    #else
        #define SIXTRL_NULL_ADDR 0u
    #endif /*  !CUDA */
#endif /* !defined( SIXTRL_NULL_ADDR ) */

#if !defined( SIXTRL_NULLPTR )
    #if  defined( __cplusplus ) && __cplusplus >= 201103L && \
        !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )
        #define SIXTRL_NULLPTR nullptr
    #else
        #define SIXTRL_NULLPTR NULL
    #endif /* nullptr */
#endif /* !defined( SIXTRL_NULLPTR ) */

/* -------------------------------------------------------------------------- */

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

/* -------------------------------------------------------------------------- */

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
#endif /* SIXTRACKLIB_COMMON_BACKENDS_COMPILE_COMPABILITY_H__ */
