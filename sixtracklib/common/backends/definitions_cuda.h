#ifndef SIXTRACKLIB_COMMON_BACKENDS_DEFINITIONS_CUDA_H__
#define SIXTRACKLIB_COMMON_BACKENDS_DEFINITIONS_CUDA_H__

#if defined( __APPLE__ ) && __APPLE__
    #include <TargetConditionals.h>
#endif /* defined( __APPLE__ ) */

#if defined( __CUDACC__ )
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* Handle includes */
    #if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
        #if defined( _GPUCODE )
            #define  SIXTRL_NO_SYSTEM_INCLUDES  1
        #endif /* defined( _GPUCODE ) */
    #endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES */
#endif /* defined( __CUDACC__ ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __APPLE__ ) && __APPLE__
        #include <TargetConditionals.h>
    #endif /* defined( __APPLE__ ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __CUDACC__ )
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* function and method keywords: */

    #if !defined( SIXTRL_EXTERN )
        #define SIXTRL_EXTERN
    #endif /* !defined( SIXTRL_EXTERN ) */

    #if !defined( SIXTRL_STATIC )
        #define SIXTRL_STATIC static
    #endif /* !defined( SIXTRL_STATIC ) */

    #if !defined( SIXTRL_INLINE )
        #define SIXTRL_INLINE inline
    #endif /* !defined( SIXTRL_INLINE ) */

    #if !defined( SIXTRL_KERNEL_FN )
        #define SIXTRL_KERNEL_FN __global__
    #endif /* !defined( SIXTRL_KERNEL_FN ) */

    #if !defined( SIXTRL_HOST_FN )
        #define SIXTRL_HOST_FN __host__
    #endif /* SIXTRL_HOST_FN */

    #if !defined( SIXTRL_DEVICE_FN )
        #define SIXTRL_DEVICE_FN __device__
    #endif /* SIXTRL_DEVICE_FN */

    #if !defined( SIXTRL_FN )
        #define SIXTRL_FN __host__ __device__
    #endif /* SIXTRL_FN */

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* default memory region decorators: */

    #if !defined( SIXTRL_ARGPTR_DEC )
        #define SIXTRL_ARGPTR_DEC_UNDEF
        #define SIXTRL_ARGPTR_DEC
    #endif /* defined( SIXTRL_ARGPTR_DEC ) */

    #if !defined( SIXTRL_DATAPTR_DEC )
        #define SIXTRL_DATAPTR_DEC_UNDEF
        #define SIXTRL_DATAPTR_DEC
    #endif /* defined( SIXTRL_DATAPTR_DEC ) */

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* variable and parameter keywords: */

     #if !defined( SIXTRL_STATIC_VAR )
        #define SIXTRL_STATIC_VAR
    #endif /* !defined( SIXTRL_STATIC_VAR ) */

    #if !defined( SIXTRL_PRIVATE_DEC )
        #define SIXTRL_PRIVATE_DEC __local__
    #endif /* !defined( SIXTRL_PRIVATE_DEC ) */

    #if !defined( SIXTRL_LOCAL_DEC )
        #define SIXTRL_SHARED_DEC __shared__
    #endif /* !defined( SIXTRL_LOCAL_DEC ) */

    #if !defined( SIXTRL_GLOBAL_DEC )
        #define SIXTRL_GLOBAL_DEC
    #endif /* !defined( SIXTRL_GLOBAL_DEC ) */

    #if !defined( SIXTRL_CONSTANT_DEC )
        #define SIXTRL_CONSTANT_DEC __constant__
    #endif /* !defined( SIXTRL_CONSTANT_DEC ) */

    #if !defined( SIXTRL_RESTRICT )
        #define SIXTRL_RESTRICT __restrict__
    #endif /* !defined( SIXTRL_RESTRICT ) */

    #if !defined( SIXTRL_RESTRICT_REF )
        #define SIXTRL_RESTRICT_REF __restrict__
    #endif /* !defined( SIXTRL_RESTRICT_REF ) */

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
    /* type definitions: */

    #if !defined( SIXTRL_REAL_TYPE )
        #define SIXTRL_REAL_TYPE double
    #endif /* !defined( SIXTRL_REAL_TYPE ) */

    #if !defined( SIXTRL_FLOAT_TYPE )
        #define SIXTRL_FLOAT_TYPE float
    #endif /* !defined( SIXTRL_FLOAT_TYPE ) */

    #if defined( WIN32 ) || defined( _WIN32 ) || \
        defined( __WIN32__ ) || defined( __NT__ )
        #if !defined( SIXTRL_UINT64_TYPE )
            #define SIXTRL_UINT64_TYPE unsigned long long int
        #endif /* !defined( SIXTRL_UINT64_TYPE ) */

        #if !defined( SIXTRL_INT64_TYPE )
            #define SIXTRL_INT64_TYPE long long int
        #endif /* !defined( SIXTRL_INT64_TYPE ) */

        #if !defined( SIXTRL_UINT32_TYPE )
            #define SIXTRL_UINT32_TYPE unsigned long int
        #endif /* !defined( SIXTRL_UINT32_TYPE ) */

        #if !defined( SIXTRL_INT32_TYPE )
            #define SIXTRL_INT32_TYPE long int
        #endif /* !defined( SIXTRL_INT32_TYPE ) */
    #elif defined( __APPLE__ ) && __APPLE__ && defined( TARGET_OS_MAC )
        #if !defined( SIXTRL_UINT64_TYPE )
            #define SIXTRL_UINT64_TYPE unsigned long long int
        #endif /* !defined( SIXTRL_UINT64_TYPE ) */

        #if !defined( SIXTRL_INT64_TYPE )
            #define SIXTRL_INT64_TYPE long long int
        #endif /* !defined( SIXTRL_INT64_TYPE ) */

        #if !defined( SIXTRL_UINT32_TYPE )
            #define SIXTRL_UINT32_TYPE unsigned long int
        #endif /* !defined( SIXTRL_UINT32_TYPE ) */

        #if !defined( SIXTRL_INT32_TYPE )
            #define SIXTRL_INT32_TYPE long int
        #endif /* !defined( SIXTRL_INT32_TYPE ) */
    #elif defined( __linux__ ) && __linux__
        #if !defined( SIXTRL_UINT64_TYPE )
            #define SIXTRL_UINT64_TYPE unsigned long int
        #endif /* !defined( SIXTRL_UINT64_TYPE ) */

        #if !defined( SIXTRL_INT64_TYPE )
            #define SIXTRL_INT64_TYPE long int
        #endif /* !defined( SIXTRL_INT64_TYPE ) */

        #if !defined( SIXTRL_UINT32_TYPE )
            #define SIXTRL_UINT32_TYPE unsigned int
        #endif /* !defined( SIXTRL_UINT32_TYPE ) */

        #if !defined( SIXTRL_INT32_TYPE )
            #define SIXTRL_INT32_TYPE int
        #endif /* !defined( SIXTRL_INT32_TYPE ) */
    #else
        #error "Unknown CUDA platform"
    #endif /* Os / platform */

    #if !defined( SIXTRL_UINT16_TYPE )
        #define SIXTRL_UINT16_TYPE unsigned short int
    #endif /* !defined( SIXTRL_UINT32_TYPE ) */

    #if !defined( SIXTRL_INT16_TYPE )
        #define SIXTRL_INT16_TYPE short int
    #endif /* !defined( SIXTRL_INT16_TYPE ) */

    #if !defined( SIXTRL_UINT8_TYPE )
        #define SIXTRL_UINT8_TYPE unsigned char
    #endif /* !defined( SIXTRL_UINT32_TYPE ) */

    #if !defined( SIXTRL_INT8_TYPE )
        #define SIXTRL_INT8_TYPE char
    #endif /* !defined( SIXTRL_INT8_TYPE ) */

    #if !defined( SIXTRL_SIZE_TYPE )
        #define SIXTRL_SIZE_TYPE  size_t
    #endif /* !defined( SIXTRL_SIZE_TYPE ) */

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* assert: */

    #if !defined (SIXTRL_ASSERT )
        #define SIXTRL_ASSERT( expr )
    #endif /* !defined( SIXTRL_ASSERT ) */

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* nullptr */

    #if !defined( SIXTRL_NULL_ADDR )
        #define SIXTRL_NULL_ADDR ( uintptr_t )NULL
    #endif /* !defined( SIXTRL_NULL_ADDR ) */

    #if !defined( SIXTRL_NULLPTR )
        #define SIXTRL_NULLPTR NULL
    #endif /* !defined( SIXTRL_NULLPTR ) */
#endif /* CUDA */
#endif /* SIXTRACKLIB_COMMON_BACKENDS_DEFINITIONS_CUDA_H__ */
