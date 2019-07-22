#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_C99_H__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/controller_base.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/node_info.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeStore)* NS(NodeStore_get_ptr)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeStore) const*
    NS(NodeStore_get_const_ptr)( void );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_get_num_architectures)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_has_architecture)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_get_architecture_ids)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_size_t) const max_num_arch_ids,
    NS(arch_id_t)* SIXTRL_RESTRICT arch_ids_begin,
    NS(arch_size_t)* SIXTRL_RESTRICT ptr_num_archs );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_has_platform)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id, NS(node_platform_id_t) const platform_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_has_platform_by_name)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id,
    char const* SIXTRL_RESTRICT platform_name_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_platform_id_t)
NS(NodeStore_get_platform_id_by_platform_name)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    char const* SIXTRL_RESTRICT platform_name_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(NodeStore_get_num_platforms)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_add_platform_name_mapping)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store, NS(arch_id_t) const arch_id,
    NS(node_platform_id_t) const platform_id,
    char const* SIXTRL_RESTRICT platform_name_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_get_num_of_controllers)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_get_num_controllers_by_architecture)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_has_controller)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t)
NS(NodeStore_find_node_index_by_node_id)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    const NS(NodeId) *const SIXTRL_RETRICT node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t)
NS(NodeStore_find_node_index_by_arch_platform_device_ids)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id, NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t)
NS(NodeStore_find_node_index_by_node_info)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT ptr_node_info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t) NS(NodeStore_find_node_index)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    char const* SIXTRL_RESTRICT node_id_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t)
NS(NodeStore_find_node_index_by_arch_node_id_str)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id,
    char const* SIXTRL_RESTRICT node_id_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(NodeStore_total_num_nodes)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(NodeStore_get_num_nodes)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_get_num_nodes_for_platform)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id, NS(node_platform_id_t) const platform_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_get_num_nodes_for_controller)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_get_all_node_indices)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_size_t) const max_num_node_indices,
    NS(node_index_t)* SIXTRL_RESTRICT node_indices_begin,
    NS(arch_size_t)* SIXTRL_RESTRICT ptr_num_node_indices );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_get_node_indices_for_architecture)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t)* SIXTRL_RESTRICT node_indices_begin,
    NS(arch_size_t) const max_num_node_indices,
    NS(arch_id_t) const arch_id,
    NS(arch_size_t)* SIXTRL_RESTRICT ptr_num_node_indices );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_get_node_indices_for_platform)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_size_t) const max_num_node_indices,
    NS(node_index_t)* SIXTRL_RESTRICT node_indices_begin,
    NS(arch_id_t) const arch_id, NS(node_platform_id_t) const platform_id,
    NS(arch_size_t)* SIXTRL_RESTRICT ptr_num_node_indices );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_get_node_indices_for_controller)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_size_t) const max_num_node_indices,
    NS(node_index_t)* SIXTRL_RESTRICT node_indices_begin,
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller,
    NS(arch_size_t)* SIXTRL_RESTRICT ptr_num_node_indices );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_is_node_available)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId) const*
NS(NodeStore_get_ptr_const_node_id)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeInfoBase) const*
NS(NodeStore_get_ptr_const_node_info_base)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeInfoBase) const*
NS(NodeStore_get_ptr_node_info_base)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store, NS(node_index_t) const index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_attach_node_to_controller)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index,
    NS(ControllerBase)* SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_attach_all_architecture_nodes_to_controller)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(ControllerBase)* SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_detach_node_from_controller)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index,
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_detach_all_nodes_from_controller)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_detach_all_nodes_by_architecture)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_detach_node_from_all_controllers)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_get_num_controllers_attached_to_node)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(NodeStore_is_node_attached_to_any_controller)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_is_node_attached_to_controller)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index,
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_mark_node_as_selected_by_controller)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index,
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_unselect_node_for_controller)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index,
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_is_node_selected_by_controller)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index,
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(NodeStore_is_node_selected_by_any_controller)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_get_num_selecting_controllers_for_node)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeStore_clear)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeStore_rebuild)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_check_lock)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    const NS(NodeStoreLock) *const SIXTRL_RESTRICT lock );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_C99_H__ */

/* end: sixtracklib/common/control/node_store.h */
