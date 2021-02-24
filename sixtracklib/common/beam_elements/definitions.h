#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/beam_elements/cobj_type_ids_undef.h"
    #include "sixtracklib/common/beam_elements/cobj_type_ids.h"
    #include "sixtracklib/common/generated/config.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_BE_ARGPTR_DEC )
    #define SIXTRL_BE_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC )
        #define  SIXTRL_BE_ARGPTR_DEC SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC
    #elif defined( SIXTRL_ARGPTR_DEC )
        #define  SIXTRL_BE_ARGPTR_DEC SIXTRL_ARGPTR_DEC
    #else /* defined( SIXTRL_ARGPTR_DEC ) */
        #define  SIXTRL_BE_ARGPTR_DEC
    #endif /* defined( SIXTRL_ARGPTR_DEC ) */
#endif /* !defined( SIXTRL_BE_ARGPTR_DEC ) */

#if !defined( SIXTRL_BE_DATAPTR_DEC )
    #define SIXTRL_BE_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC )
        #define  SIXTRL_BE_ARGPTR_DEC SIXTRL_BUFFER_DATAPTR_ARGPTR_DEC
    #elif defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_BE_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else /* defined( SIXTRL_DATAPTR_DEC ) */
        #define  SIXTRL_BE_DATAPTR_DEC
    #endif /* defined( SIXTRL_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_BE_DATAPTR_DEC ) */



#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

typedef SIXTRL_REAL_TYPE        NS(be_real_type);
typedef SIXTRL_INT64_TYPE       NS(be_order_type);
typedef SIXTRL_UINT64_TYPE      NS(be_size_type);
typedef SIXTRL_INT64_TYPE       NS(be_int_type);
typedef SIXTRL_INT64_TYPE       NS(be_flags_type);
typedef NS(address_type)        NS(be_addr_type);
typedef NS(address_diff_type)   NS(be_addr_diff_type);

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE {
    typedef ::NS(be_real_type)       be_real_type;
    typedef ::NS(be_order_type)      be_order_type;
    typedef ::NS(be_size_type)       be_size_type;
    typedef ::NS(be_int_type)        be_int_type;
    typedef ::NS(be_flags_type)      be_flags_type;
    typedef ::NS(be_addr_type)       be_addr_type;
    typedef ::NS(be_addr_diff_type)  be_addr_diff_type;

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DEFINITIONS_H__ */
