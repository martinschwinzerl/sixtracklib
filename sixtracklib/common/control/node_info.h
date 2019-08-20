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
    #include "sixtracklib/common/control/node_store.h"
    #include "sixtracklib/common/control/node_set.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE )

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeInfoBase)* NS(NodeInfoBase_create)(
    NS(arch_id_t) const arch_id, NS(NodeStore)* SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeInfoBase)* NS(NodeInfoBase_new)(
    NS(NodeId)* SIXTRL_RESTRICT node_id,
    NS(NodeStore)* SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeInfoBase)* NS(NodeInfoBase_new_detailed)(
    NS(arch_id_t) const arch_id,
    const char *const SIXTRL_RESTRICT platform_name,
    const char *const SIXTRL_RESTRICT device_name,
    const char *const SIXTRL_RESTRICT description,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id,
    NS(NodeStore)* SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_delete)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT node_info );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_id_t) NS(NodeInfo_get_arch_id)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_arch_str)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_arch_str)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_node_store)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeStore) const*
NS(NodeInfo_get_ptr_const_node_store)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeStore)* NS(NodeInfo_get_ptr_node_store)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeInfo_assign_to_node_store)( NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    NS(NodeStore)* SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeInfo_detach_from_node_store)( NS(NodeInfoBase)* SIXTRL_RESTRICT info );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId) const*
NS(NodeInfo_get_ptr_const_node_id)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_id_t) NS(NodeInfo_get_arch_id)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_platform_id_t)
NS(NodeInfo_get_platform_id)( const NS(NodeInfoBase) *const SIXTRL_RESTRICT );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_device_id_t) NS(NodeInfo_get_device_id)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeInfo_set_platform_id)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    NS(node_platform_id_t) const platform_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeInfo_set_device_id)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT info, NS(node_device_id_t) const dev_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t) NS(NodeInfo_get_node_index)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_platform_name)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_platform_name_str)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeInfo_set_platform_name)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    const char *const SIXTRL_RESTRICT platform_name );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_device_name)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_device_name_str)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_device_name)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    const char *const SIXTRL_RESTRICT device_name );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_description)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_get_description_str)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_description)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    const char *const SIXTRL_RESTRICT description_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_unique_id_str)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_unique_id_str)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_maps_to_same_unique_id_str)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    char const* SIXTRL_RESTRICT unique_id_str );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(NodeInfo_maps_to_same_node_by_unique_id_str)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT other_info );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeInfo_get_max_attachement_count)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_attached_to_any_set)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeInfo_get_num_attached_sets)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_attached_to_set)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    NS(node_set_id_t) const set_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeInfo_get_max_selection_count)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_selected_by_any_set)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeInfo_get_num_selection_count)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_selected_by_set)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_default_for_set)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    NS(node_set_id_t) const node_set_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeInfo_get_required_out_string_length)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeInfo_get_required_out_string_length_for_set)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_print)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::FILE* SIXTRL_RESTRICT output );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_print_for_set)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::FILE* SIXTRL_RESTRICT output, NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_print_out)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_print_out_for_set)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeInfo_to_string)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    NS(arch_size_t) const out_str_capacity,
    char* SIXTRL_RESTRICT out_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeInfo_to_string_for_set)(
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    NS(arch_size_t) const out_str_capacity, char* SIXTRL_RESTRICT out_str,
    NS(node_set_id_t) const node_set_id );

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_H__ */
/* end: sixtracklib/common/control/node_info.h */
