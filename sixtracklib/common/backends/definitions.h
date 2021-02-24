#ifndef SIXTRACKLIB_COMMON_BACKENDS_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_BACKENDS_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/generated/namespace.h"
    #include "sixtracklib/common/backends/definitions_opencl.h"
    #include "sixtracklib/common/backends/definitions_cuda.h"
#endif /* !defined( SIXTRL_NO_INCLUDE ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cassert>
        #include <cstdint>
    #else /* !defined( __cplusplus ) */
        #include <assert.h>
        #include <stdint.h>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_DLIB_PLATFORM_UNDEFINED )
    #define SIXTRL_DLIB_PLATFORM_UNDEFINED 0
#endif /* !defined( SIXTRL_DLIB_PLATFORM_UNDEFINED ) */

#if !defined( SIXTRL_DLIB_PLATFORM_POSIX )
    #define SIXTRL_DLIB_PLATFORM_POSIX 1
#endif /* !defined( SIXTRL_DLIB_PLATFORM_POSIX ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/* function and method keywords: */

#if !defined( SIXTRL_EXTERN )
    #define SIXTRL_EXTERN extern
#endif /* !defined( SIXTRL_EXTERN ) */

#if !defined( SIXTRL_STATIC )
    #define SIXTRL_STATIC static
#endif /* !defined( SIXTRL_STATIC ) */

#if !defined( SIXTRL_INLINE )
    #define SIXTRL_INLINE inline
#endif /* !defined( SIXTRL_INLINE ) */

#if !defined( SIXTRL_KERNEL_FN )
    #define SIXTRL_KERNEL_FN
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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/* default memory region decorators: */

#if !defined( SIXTRL_ARGPTR_DEC )
    #define SIXTRL_ARGPTR_DEC_UNDEF
    #define SIXTRL_ARGPTR_DEC
#endif /* defined( SIXTRL_ARGPTR_DEC ) */

#if !defined( SIXTRL_DATAPTR_DEC )
    #define SIXTRL_DATAPTR_DEC_UNDEF
    #define SIXTRL_DATAPTR_DEC
#endif /* defined( SIXTRL_DATAPTR_DEC ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/* variable and parameter keywords: */

    #if !defined( SIXTRL_STATIC_VAR )
    #define SIXTRL_STATIC_VAR static
#endif /* !defined( SIXTRL_STATIC_VAR ) */

#if !defined( SIXTRL_PRIVATE_DEC )
    #define SIXTRL_PRIVATE_DEC
#endif /* !defined( SIXTRL_PRIVATE_DEC ) */

#if !defined( SIXTRL_LOCAL_DEC )
    #define SIXTRL_SHARED_DEC
#endif /* !defined( SIXTRL_LOCAL_DEC ) */

#if !defined( SIXTRL_GLOBAL_DEC )
    #define SIXTRL_GLOBAL_DEC
#endif /* !defined( SIXTRL_GLOBAL_DEC ) */

#if !defined( SIXTRL_CONSTANT_DEC )
    #define SIXTRL_CONSTANT_DEC
#endif /* !defined( SIXTRL_CONSTANT_DEC ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/* type definitions: */

#if !defined( SIXTRL_REAL_TYPE )
    #define SIXTRL_REAL_TYPE double
#endif /* !defined( SIXTRL_REAL_TYPE ) */

#if !defined( SIXTRL_FLOAT_TYPE )
    #define SIXTRL_FLOAT_TYPE float
#endif /* !defined( SIXTRL_FLOAT_TYPE ) */

#if !defined( SIXTRL_UINT64_TYPE )
    #define SIXTRL_UINT64_TYPE uint64_t
#endif /* !defined( SIXTRL_UINT64_TYPE ) */

#if !defined( SIXTRL_INT64_TYPE )
    #define SIXTRL_INT64_TYPE int64_t
#endif /* !defined( SIXTRL_INT64_TYPE ) */

#if !defined( SIXTRL_UINT32_TYPE )
    #define SIXTRL_UINT32_TYPE uint32_t
#endif /* !defined( SIXTRL_UINT32_TYPE ) */

#if !defined( SIXTRL_INT32_TYPE )
    #define SIXTRL_INT32_TYPE int32_t
#endif /* !defined( SIXTRL_INT32_TYPE ) */

#if !defined( SIXTRL_UINT16_TYPE )
    #define SIXTRL_UINT16_TYPE uint16_t
#endif /* !defined( SIXTRL_UINT32_TYPE ) */

#if !defined( SIXTRL_INT16_TYPE )
    #define SIXTRL_INT16_TYPE int16_t
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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/* assert: */

#if !defined (SIXTRL_ASSERT )
    #define SIXTRL_ASSERT( expr ) assert( expr )
#endif /* !defined( SIXTRL_ASSERT ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/* nullptr */

#if !defined( SIXTRL_NUM_ALIGN )
    #define SIXTRL_NULL_ADDR 0u
#endif /* !defined( SIXTRL_NULL_ADDR ) */

#if !defined( SIXTRL_NULLPTR )
    #define SIXTRL_NULLPTR NULL
#endif /* !defined( SIXTRL_NULLPTR ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

#if !defined( SIXTRL_DEFAULT_ALIGN )
    #define SIXTRL_DEFAULT_ALIGN 8u
#endif /* !defined( SIXTRL_DEFAULT_ALIGN ) */

/* -------------------------------------------------------------------------- */

#if !defined( SIXTRL_REAL_TYPE_EPS )
    #define SIXTRL_REAL_TYPE_EPS 2.22e-16
#endif /* !defined( SIXTRL_REAL_TYPE_EPS ) */

#if !defined( SIXTRL_FLOAT_TYPE_EPS )
    #define SIXTRL_FLOAT_TYPE_EPS 1.19e-07f
#endif /* !defined( SIXTRL_FLOAT_TYPE_EPS ) */

/* -------------------------------------------------------------------------- */

typedef SIXTRL_UINT64_TYPE NS(backend_id_type);
typedef SIXTRL_INT64_TYPE  NS(derived_class_id_type);
typedef SIXTRL_UINT64_TYPE NS(dlib_platform_type);

#if !defined( SIXTRL_DERIVED_CLASS_ID_NONE )
    #define SIXTRL_DERIVED_CLASS_ID_NONE -1
#endif /* !defined( SIXTRL_DERIVED_CLASS_ID_NONE ) */

#if !defined( SIXTRL_BACKEND_ID_NONE )
    #define SIXTRL_BACKEND_ID_NONE 0
#endif /* !defined( SIXTRL_BACKEND_ID_NONE ) */

#if !defined( SIXTRL_BACKEND_ID_CPU )
    #define SIXTRL_BACKEND_ID_CPU 1
#endif /* !defined( SIXTRL_BACKEND_ID_CPU ) */

#if !defined( SIXTRL_BACKEND_ID_OPENMP )
    #define SIXTRL_BACKEND_ID_OPENMP 2
#endif /* !defined( SIXTRL_BACKEND_ID_OPENMP ) */

#if !defined( SIXTRL_BACKEND_ID_OPENCL )
    #define SIXTRL_BACKEND_ID_OPENCL 3
#endif /* !defined( SIXTRL_BACKEND_ID_OPENCL ) */

#if !defined( SIXTRL_BACKEND_ID_CUDA )
    #define SIXTRL_BACKEND_ID_CUDA 4
#endif /* !defined( SIXTRL_BACKEND_ID_CUDA ) */

#if !defined( SIXTRL_BACKEND_ID_HIP )
    #define SIXTRL_BACKEND_ID_HIP 5
#endif /* !defined( SIXTRL_BACKEND_ID_HIP ) */

#if !defined( SIXTRL_BACKEND_ID_DPCPP )
    #define SIXTRL_BACKEND_ID_DPCPP 6
#endif /* !defined( SIXTRL_BACKEND_ID_DPCPP ) */

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(backend_id_type) const NS(BACKEND_ID_NONE) =
    ( NS(backend_id_type) )SIXTRL_BACKEND_ID_NONE;

SIXTRL_STATIC_VAR NS(backend_id_type) const NS(BACKEND_ID_CPU) =
    ( NS(backend_id_type) )SIXTRL_BACKEND_ID_CPU;

SIXTRL_STATIC_VAR NS(backend_id_type) const NS(BACKEND_ID_OPENMP) =
    ( NS(backend_id_type) )SIXTRL_BACKEND_ID_OPENMP;

SIXTRL_STATIC_VAR NS(backend_id_type) const NS(BACKEND_ID_OPENCL) =
    ( NS(backend_id_type) )SIXTRL_BACKEND_ID_OPENCL;

SIXTRL_STATIC_VAR NS(backend_id_type) const NS(BACKEND_ID_CUDA) =
    ( NS(backend_id_type) )SIXTRL_BACKEND_ID_CUDA;

SIXTRL_STATIC_VAR NS(backend_id_type) const NS(BACKEND_ID_HIP) =
    ( NS(backend_id_type) )SIXTRL_BACKEND_ID_HIP;

SIXTRL_STATIC_VAR NS(backend_id_type) const NS(BACKEND_ID_DPCPP) =
    ( NS(backend_id_type) )SIXTRL_BACKEND_ID_DPCPP;


SIXTRL_STATIC_VAR NS(derived_class_id_type) const NS(DERIVED_CLASS_ID_NONE) =
    ( NS(derived_class_id_type) )SIXTRL_DERIVED_CLASS_ID_NONE;


SIXTRL_STATIC_VAR NS(dlib_platform_type) const NS(DLIB_PLATFORM_UNDEFINED) =
    ( NS(dlib_platform_type) )SIXTRL_DLIB_PLATFORM_UNDEFINED;

SIXTRL_STATIC_VAR NS(dlib_platform_type) const NS(DLIB_PLATFORM_POSIX) =
    ( NS(dlib_platform_type) )SIXTRL_DLIB_PLATFORM_POSIX;

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(backend_id_type) backend_id_type;
    typedef ::NS(derived_class_id_type) derived_class_id_type;
    typedef ::NS(dlib_platform_type) dlib_platform_type;

    #if !defined( _GPUCODE )

    static constexpr backend_id_type BACKEND_ID_NONE =
        backend_id_type{ SIXTRL_BACKEND_ID_NONE };

    static constexpr backend_id_type BACKEND_ID_CPU =
        backend_id_type{ SIXTRL_BACKEND_ID_CPU };

    static constexpr backend_id_type BACKEND_ID_OPENMP =
        backend_id_type{ SIXTRL_BACKEND_ID_OPENMP };

    static constexpr backend_id_type BACKEND_ID_OPENCL =
        backend_id_type{ SIXTRL_BACKEND_ID_OPENCL };

    static constexpr backend_id_type BACKEND_ID_CUDA =
        backend_id_type{ SIXTRL_BACKEND_ID_CUDA };

    static constexpr backend_id_type BACKEND_ID_HIP =
        backend_id_type{ SIXTRL_BACKEND_ID_HIP };

    static constexpr backend_id_type BACKEND_ID_DPCPP =
        backend_id_type{ SIXTRL_BACKEND_ID_DPCPP };


    static constexpr derived_class_id_type DERIVED_CLASS_ID_NONE =
        derived_class_id_type{ SIXTRL_DERIVED_CLASS_ID_NONE };


    static constexpr dlib_platform_type DLIB_PLATFORM_UNDEFINED =
        dlib_platform_type{ SIXTRL_DLIB_PLATFORM_UNDEFINED };

    static constexpr dlib_platform_type DLIB_PLATFORM_POSIX =
        dlib_platform_type{ SIXTRL_DLIB_PLATFORM_POSIX };

    #endif /* !defined( _GPUCODE ) */

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* C++ */

/* -------------------------------------------------------------------------- */

#if !defined( SIXTRL_NO_INCLUDE )
    #include "sixtracklib/common/backends/compiler_compability.h"
#endif /* !defined( SIXTRL_NO_INCLUDE ) */

#endif /* SIXTRACKLIB_COMMON_BACKENDS_DEFINITIONS_H__ */
