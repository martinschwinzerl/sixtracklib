#ifndef SIXTRACKLIB_COMMON_BACKENDS_DEFINITIONS_OPENCL_H__
#define SIXTRACKLIB_COMMON_BACKENDS_DEFINITIONS_OPENCL_H__

#if defined( _GPUCODE ) && defined( __OPENCL_C_VERSION__ )
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* OpenCL extensions */
    #if __OPENCL_VERSION__ <= CL_VERSION_1_1
        #pragma OPENCL EXTENSION cl_khr_fp64 : enable
    #endif

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* Handle includes */
    #if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
        #define  SIXTRL_NO_SYSTEM_INCLUDES  1
    #endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES */

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* function and method keywords: */

    #if !defined( SIXTRL_EXTERN )
        #define SIXTRL_EXTERN
    #endif /* !defined( SIXTRL_EXTERN ) */

    #if !defined( SIXTRL_STATIC )
        #define SIXTRL_STATIC
    #endif /* !defined( SIXTRL_STATIC ) */

    #if !defined( SIXTRL_INLINE )
        #define SIXTRL_INLINE inline
    #endif /* !defined( SIXTRL_INLINE ) */

    #if !defined( SIXTRL_KERNEL_FN )
        #define SIXTRL_KERNEL_FN __kernel
    #endif /* !defined( SIXTRL_KERNEL_FN ) */

    #if !defined( SIXTRL_HOST_FN )
        #define SIXTRL_HOST_FN
    #endif /* SIXTRL_HOST_FN */

    #if !defined( SIXTRL_DEVICE_FN )
        #define SIXTRL_DEVICE_FN
    #endif /* SIXTRL_DEVICE_FN */

    #if !defined( SIXTRL_FN )
        #define SIXTRL_FN
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
        #define SIXTRL_PRIVATE_DEC
    #endif /* !defined( SIXTRL_PRIVATE_DEC ) */

    #if !defined( SIXTRL_LOCAL_DEC )
        #define SIXTRL_SHARED_DEC __local
    #endif /* !defined( SIXTRL_LOCAL_DEC ) */

    #if !defined( SIXTRL_GLOBAL_DEC )
        #define SIXTRL_GLOBAL_DEC __global
    #endif /* !defined( SIXTRL_GLOBAL_DEC ) */

    #if !defined( SIXTRL_CONSTANT_DEC )
        #define SIXTRL_CONSTANT_DEC __constant
    #endif /* !defined( SIXTRL_CONSTANT_DEC ) */

    #if !defined( SIXTRL_RESTRICT )
        #define SIXTRL_RESTRICT restrict
    #endif /* !defined( SIXTRL_RESTRICT ) */

    #if !defined( SIXTRL_RESTRICT_REF )
        #define SIXTRL_RESTRICT_REF
    #endif /* !defined( SIXTRL_RESTRICT_REF ) */

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
    /* type definitions: */

    #if !defined( SIXTRL_REAL_TYPE )
        #define SIXTRL_REAL_TYPE double
    #endif /* !defined( SIXTRL_REAL_TYPE ) */

    #if !defined( SIXTRL_FLOAT_TYPE )
        #define SIXTRL_FLOAT_TYPE float
    #endif /* !defined( SIXTRL_FLOAT_TYPE ) */

    #if !defined( SIXTRL_UINT64_TYPE )
        #define SIXTRL_UINT64_TYPE unsigned long
    #endif /* !defined( SIXTRL_UINT64_TYPE ) */

    #if !defined( SIXTRL_INT64_TYPE )
        #define SIXTRL_INT64_TYPE long
    #endif /* !defined( SIXTRL_INT64_TYPE ) */

    #if !defined( SIXTRL_UINT32_TYPE )
        #define SIXTRL_UINT32_TYPE unsigned int
    #endif /* !defined( SIXTRL_UINT32_TYPE ) */

    #if !defined( SIXTRL_INT32_TYPE )
        #define SIXTRL_INT32_TYPE int
    #endif /* !defined( SIXTRL_INT32_TYPE ) */

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
        #define SIXTRL_NULL_ADDR 0u
    #endif /* !defined( SIXTRL_NULL_ADDR ) */

    #if !defined( SIXTRL_NULLPTR )
        #define SIXTRL_NULLPTR 0
    #endif /* !defined( SIXTRL_NULLPTR ) */
#endif /* GPU kernel / OpenCL */
#endif /* SIXTRACKLIB_COMMON_BACKENDS_DEFINITIONS_OPENCL_H__ */
