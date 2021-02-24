#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_DEFINITIONS_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_TESTLIB_ARGPTR_DEC )
    #define SIXTRL_TESTLIB_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC )
        #define  SIXTRL_TESTLIB_ARGPTR_DEC SIXTRL_ARGPTR_DEC
    #else /* defined( SIXTRL_ARGPTR_DEC ) */
        #define  SIXTRL_TESTLIB_ARGPTR_DEC
    #endif /* defined( SIXTRL_ARGPTR_DEC ) */
#endif /* !defined( SIXTRL_TESTLIB_ARGPTR_DEC ) */

#if !defined( SIXTRL_TESTLIB_DATAPTR_DEC )
    #define SIXTRL_TESTLIB_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_TESTLIB_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else /* defined( SIXTRL_DATAPTR_DEC ) */
        #define  SIXTRL_TESTLIB_DATAPTR_DEC
    #endif /* defined( SIXTRL_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_TESTLIB_DATAPTR_DEC ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

typedef SIXTRL_REAL_TYPE   NS(cobj_test_real_type);
typedef SIXTRL_INT64_TYPE  NS(cobj_test_int64_type);
typedef SIXTRL_UINT64_TYPE NS(cobj_test_uint64_type);
typedef NS(address_type)   NS(cobj_test_addr_type);

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(cobj_test_real_type)   cobj_test_real_type;
    typedef ::NS(cobj_test_uint64_type) cobj_test_uint64_type;
    typedef ::NS(cobj_test_int64_type)  cobj_test_int64_type;
    typedef ::NS(cobj_test_addr_type)   cobj_test_addr_type;
}
#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_DEFINITIONS_H__ */
