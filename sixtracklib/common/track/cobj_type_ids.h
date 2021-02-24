#ifndef SIXTRACKLIB_COMMON_TRACK_COBJ_TYPE_IDS_H__
#define SIXTRACKLIB_COMMON_TRACK_COBJ_TYPE_IDS_H__

#if !defined( SIXTRL_COBJECTS_TYPE_ID_TRACK_CONFIG )
    #define SIXTRL_COBJECTS_TYPE_ID_TRACK_CONFIG 256
#endif /* !defined( SIXTRL_COBJECTS_TYPE_ID_TRACK_CONFIG ) */

#if !defined( SIXTRL_COBJECTS_TYPE_ID_ELEM_BY_ELEM_CONFIG )
    #define SIXTRL_COBJECTS_TYPE_ID_ELEM_BY_ELEM_CONFIG 257
#endif /* !defined( SIXTRL_COBJECTS_TYPE_ID_ELEM_BY_ELEM_CONFIG ) */

/* ========================================================================= */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

typedef enum NS(cobj_track_type_ids)
{
    NS(COBJECTS_TYPE_ID_TRACK_CONFIG) = SIXTRL_COBJECTS_TYPE_ID_TRACK_CONFIG,
    NS(COBJECTS_TYPE_ID_ELEM_BY_ELEM_CONFIG) = SIXTRL_COBJECTS_TYPE_ID_ELEM_BY_ELEM_CONFIG
}
NS(cobj_track_type_ids);

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST ::NS(cobj_obj_id_type)
        COBJECTS_TYPE_ID_TRACK_CONFIG = static_cast<
            ::NS(cobj_obj_id_type) >( SIXTRL_COBJECTS_TYPE_ID_TRACK_CONFIG );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST ::NS(cobj_obj_id_type)
        COBJECTS_TYPE_ID_ELEM_BY_ELEM_CONFIG = static_cast<
            ::NS(cobj_obj_id_type) >(
                SIXTRL_COBJECTS_TYPE_ID_ELEM_BY_ELEM_CONFIG );

} /* end : SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_TRACK_COBJ_TYPE_IDS_H__ */
