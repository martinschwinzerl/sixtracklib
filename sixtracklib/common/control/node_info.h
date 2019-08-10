#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_H__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_info.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/architecture/architecture.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/controller_base.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE )

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_delete)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT node_info );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_node_store)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

// SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeStore) const*
// NS(NodeInfo_get_ptr_const_Node_store)(
//     const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

// SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeStore)* NS(NodeInfo_get_ptr_node_store)(
//     NS(NodeInfoBase)* SIXTRL_RESTRICT info );

// SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
// NS(NodeInfo_assign_to_node_store)( NS(NodeInfoBase)* SIXTRL_RESTRICT info,
//     NS(NodeStore)* SIXTRL_RESTRICT store );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId) const*
NS(NodeInfo_get_ptr_const_node_id)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId)* NS(NodeInfo_get_ptr_node_id)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_platform_id_t)
NS(NodeInfo_get_platform_id)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeInfo_set_platform_id)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    NS(node_platform_id_t) const platform_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_device_id_t)
NS(NodeInfo_get_device_id)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeInfo_set_device_id)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    NS(node_device_id_t) const device_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_id_t) NS(NodeInfo_get_arch_id)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_arch_string)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_arch_string)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_platform_name)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_platform_name)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_platform_name)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    const char *const SIXTRL_RESTRICT platform_name );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_device_name)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_device_name)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_device_name)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    const char *const SIXTRL_RESTRICT device_name );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_description)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_description)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_description)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    const char *const SIXTRL_RESTRICT description );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeInfo_get_max_selection_count)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_attached_to_any_controller)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_attached_to_controller)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const NS(ControllerBase) *const ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeInfo_get_num_attached_controllers)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_selected_by_any_controller)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_selected_by_controller)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeInfo_get_num_selecting_controllers)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_unique_id_string)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_unique_id_string)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_maps_to_same)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT other );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_maps_to_same_unique_id_string)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    char const* SIXTRL_RESTRICT unique_id_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeInfo_required_out_string_length)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_print)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    FILE* SIXTRL_RESTRICT output,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_print_out)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeInfo_to_string)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    NS(arch_size_t) const out_string_capacity, char* SIXTRL_RESTRICT out_str,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_H__ */
/* end: sixtracklib/common/control/node_info.h */
