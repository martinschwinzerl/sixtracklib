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
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE )

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_delete)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT node_info );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_node_id)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_owns_node_id)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId) const*
NS(NodeInfo_get_ptr_const_node_id)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId)* NS(NodeInfo_get_ptr_node_id)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_platform_id_t)
NS(NodeInfo_get_platform_id)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeInfo_set_platform_id)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    NS(node_platform_id_t) const platform_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_device_id_t)
NS(NodeInfo_get_device_id)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeInfo_set_device_id)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    NS(node_device_id_t) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodePlatformNodeIdPair) const*
NS(NodeInfo_get_const_platform_id_platform_id_pair)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodePlatformNodeIdPair)*
NS(NodeInfo_get_platform_id_platform_id_pair)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_controllers)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfo) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(NodeInfo_get_num_of_controllers)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfo) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_attached_to_controller)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfo) *const SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_node_index)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfo) *const SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t) NS(NodeInfo_get_node_index)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfo) *const SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeInfo_set_node_index)(
    SIXTRL_ARGPTR_DEC NS(NodeInfo)* SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_selected)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfo) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_selected_by_controller)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfo) *const SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_default)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfo) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_default_for_controller)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfo) *const SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ControllerBase) const*
NS(NodeInfo_get_const_selecting_controller)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfo) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeInfo_set_selected_controller)(
    SIXTRL_ARGPTR_DEC NS(NodeInfo)* SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeInfo_reset_selecting_controller)(
    SIXTRL_ARGPTR_DEC NS(NodeInfo)* SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeInfo_attach_to_controller)(
    SIXTRL_ARGPTR_DEC NS(NodeInfo)* SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeInfo_detach_from_controller)(
    SIXTRL_ARGPTR_DEC NS(NodeInfo)* SIXTRL_RESTRICT node,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ControllerBase) const*
NS(NodeInfo_get_const_controller)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfo) *const SIXTRL_RESTRICT node,
    NS(arch_size_t) const num_of_controller_in_sequence );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_id_t) NS(NodeInfo_get_arch_id)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_arch_string)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_arch_string)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_platform_name)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_platform_name)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_platform_name)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT platform_name );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_device_name)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_device_name)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_device_name)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT device_name );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_description)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_description)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_description)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT description );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_print)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    FILE* SIXTRL_RESTRICT output,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_print_out)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeInfo_get_required_output_str_length)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeInfo_convert_to_string)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    NS(arch_size_t) const out_string_capacity, char* SIXTRL_RESTRICT out_str,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller );

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_H__ */
/* end: sixtracklib/common/control/node_info.h */
