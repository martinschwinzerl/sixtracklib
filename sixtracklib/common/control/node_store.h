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
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeStore)*
NS(NodeStore_get_global_ptr)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeStore) const*
NS(NodeStore_get_global_const_ptr)( void );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeStore)* NS(NodeStore_new)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeStore_delete)(
    NS(NodeStore)* SIXTRL_RESTRICT store );

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

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(NodeStore_get_num_platforms)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t)
NS(NodeStore_find_node_index_by_node_id)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    const NS(NodeId) *const SIXTRL_RESTRICT node_id );

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

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(NodeStore_get_total_num_nodes)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(NodeStore_get_num_nodes)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_get_num_nodes_for_platform)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id, NS(node_platform_id_t) const platform_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t)
NS(NodeStore_get_min_attached_node_index)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t)
NS(NodeStore_get_max_attached_node_index)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_get_num_nodes_for_set)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_get_num_selected_nodes_for_set)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_get_num_default_nodes_for_set)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_set_id_t) const node_set_id );

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
    NS(arch_size_t) const max_num_node_indices,
    NS(node_index_t)* SIXTRL_RESTRICT node_indices_begin,
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
NS(NodeStore_get_node_indices_for_set)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(arch_size_t) const max_num_node_indices,
    NS(node_index_t)* SIXTRL_RESTRICT node_indices_begin,
    NS(node_set_id_t) const node_set_id,
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

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_has_node_sets)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(NodeStore_get_num_node_sets)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_has_node_set)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_set_id_t) const set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_has_node_set_by_ptr)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(NodeSetBase)* SIXTRL_RESTRICT node_set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_set_id_t) NS(NodeStore_add_node_set)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(NodeSetBase)* SIXTRL_RESTRICT ptr_node_set_to_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeStore_remove_node_set)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_set_id_t) const set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_set_id_t) NS(NodeStore_get_node_set_id)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(NodeSetBase)* SIXTRL_RESTRICT node_set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeSetBase)* NS(NodeStore_get_ptr_node_set)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeSetBase) const*
NS(NodeStore_get_ptr_const_node_set_base)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_set_id_t) const node_set_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t) NS(NodeStore_add_node)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(NodeInfoBase)* SIXTRL_RESTRICT ptr_node_info_to_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeStore_remove_node)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeStore_attach_node_to_set)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index,
    NS(node_set_id_t) const set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_attach_all_architecture_nodes_to_set)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(arch_id_t) const arch_id, NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_detach_node_from_set)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index, NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_detach_all_nodes_from_set)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store, NS(node_set_id_t) const set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeStore_detach_node_from_all_sets)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_num_sets_attached_to_node)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_is_node_attached_to_any_set)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_is_node_attached_to_set)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index,
    NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(NodeStore_can_node_be_selected_by_set)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const index,
    NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_is_node_selected_by_set)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index, NS(node_set_id_t) const set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_is_node_selected_by_any_set)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_num_selecting_sets_for_node)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_is_node_default_for_set)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index, NS(node_set_id_t) const set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_is_node_default_for_any_set)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeStore_get_num_sets_having_node_as_default)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_index_t) const index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeStore_clear)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_UINT64_T
NS(NodeStore_get_sync_id_value)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeStore_is_sync_with)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    SIXTRL_UINT64_T const sync_id_value );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_C99_H__ */

/* end: sixtracklib/common/control/node_store.h */
