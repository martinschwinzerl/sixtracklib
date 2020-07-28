#ifndef SIXTRACKLIB_BASE_INTERNAL_BASE_TYPES_H__
#define SIXTRACKLIB_BASE_INTERNAL_BASE_TYPES_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/generated/namespace.h"
    #include "sixtracklib/base/internal/namespace_defines.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <cstdint>
    #else
        #include <stddef.h>
        #include <stdlib.h>
        #include <stdint.h>
    #endif /* __cplusplus */
#endif /* !SIXTRL_NO_SYSTEM_INCLUDES */

#if !defined( _GPUCODE )
    typedef int64_t NS(status_t);

    #if !defined( SIXTRL_SIZE_T )
        #define SIXTRL_SIZE_T  size_t
    #endif /* !defined( SIXTRL_SIZE_T ) */

    typedef SIXTRL_SIZE_T NS(size_t);

    #if !defined( SIXTRL_REAL_T )
        #define SIXTRL_REAL_T double
    #endif /* !defined( SIXTRL_REAL_T ) */

    typedef SIXTRL_REAL_T NS(real_t);

    #if !defined( SIXTRL_FLOAT_T )
        #define SIXTRL_FLOAT_T float
    #endif /* !defined( SIXTRL_FLOAT_T ) */

    typedef SIXTRL_FLOAT_T NS(float_t);

    #if !defined( SIXTRL_UINT64_T )
        #define SIXTRL_UINT64_T uint64_t
    #endif /* !defined( SIXTRL_UINT64_T ) */

    typedef SIXTRL_UINT64_T NS(uint64_t);

    #if !defined( SIXTRL_INT64_T )
        #define SIXTRL_INT64_T int64_t
    #endif /* !defined( SIXTRL_INT64_T ) */

    typedef SIXTRL_INT64_T NS(int64_t);

    #if !defined( SIXTRL_UINT32_T )
        #define SIXTRL_UINT32_T uint32_t
    #endif /* !defined( SIXTRL_UINT32_T ) */

    typedef SIXTRL_UINT32_T NS(uint32_t);

    #if !defined( SIXTRL_INT32_T )
        #define SIXTRL_INT32_T int
    #endif /* !defined( SIXTRL_INT32_T ) */

    typedef SIXTRL_INT32_T NS(int32_t);

    #if !defined( SIXTRL_UINT16_T )
        #define SIXTRL_UINT16_T uint16_t
    #endif /* !defined( SIXTRL_UINT16_T ) */

    typedef SIXTRL_UINT16_T NS(uint16_t);

    #if !defined( SIXTRL_INT16_T )
        #define SIXTRL_INT16_T int16_t
    #endif /* !defined( SIXTRL_INT16_T ) */

    typedef SIXTRL_INT16_T NS(int16_t);

    #if !defined( SIXTRL_UINT8_T )
        #define SIXTRL_UINT8_T uint8_t
    #endif /* !defined( SIXTRL_UINT8_T ) */

    typedef SIXTRL_UINT8_T NS(uint8_t);

    #if !defined( SIXTRL_INT8_T )
        #define SIXTRL_INT8_T int8_t
    #endif /* !defined( SIXTRL_INT8_T ) */

    typedef SIXTRL_INT8_T NS(int8_t);
#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(status_t)  status_t;
    typedef ::NS(size_t)    size_t;
} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
#endif /* SIXTRACKLIB_BASE_INTERNAL_BASE_TYPES_H__ */
