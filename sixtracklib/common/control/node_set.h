#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_SET_C99_H__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_SET_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_info.h"
    #include "sixtracklib/common/control/node_store.h"
    #include "sixtracklib/common/control/node_set.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeSetBase)* NS(NodeSet_new)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_set_id_t) NS(NodeSet_get_node_set_id)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeSet_set_node_set_id)(
    NS(NodeSetBase)* SIXTRL_RESTRICT set,
    NS(node_set_id_t) const node_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeSet_delete)(
    NS(NodeSetBase)* SIXTRL_RESTRICT set );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(NodeSet_get_num_nodes)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t) NS(NodeSet_get_min_node_index)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t) NS(NodeSet_get_max_node_index)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t) NS(NodeSet_get_node_index)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set, NS(arch_size_t) const nn );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId) const* NS(NodeSet_get_node_id)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set, NS(arch_size_t) const nn );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId) const*
NS(NodeSet_get_node_id_by_node_index)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_is_node_available)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    NS(node_index_t) const node_index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_uses_auto_select)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_is_selected)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    NS(node_index_t) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_can_select_node)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    NS(node_index_t) const index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_is_default)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    NS(node_index_t) const node_index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_supports_changing_node)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(NodeSet_supports_directly_changing_selected_node)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_can_change_from_node_to_node)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    NS(node_index_t) const current_node_idx,
    NS(node_index_t) const next_node_idx );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeSet_change_from_node_to_node)( NS(NodeSetBase)* SIXTRL_RESTRICT set,
    NS(node_index_t) const current_node_idx,
    NS(node_index_t) const next_node_idx );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_supports_unselecting_node)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_can_unselect_node)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    NS(node_index_t) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeSet_unselect_node)(
    NS(NodeSetBase)* SIXTRL_RESTRICT set, NS(node_index_t) const node_index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_is_sync_with_store)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeSet_sync_with_store)(
    NS(NodeSetBase)* SIXTRL_RESTRICT set );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(NodeSet_required_out_string_length)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeSet_print)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::FILE* SIXTRL_RESTRICT output );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeSet_print_out)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeSet_to_string)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    NS(arch_size_t) const out_str_capacity,
    char* SIXTRL_RESTRICT out_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeStore) const*
NS(NodeSet_get_ptr_const_node_store)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeStore)* NS(NodeSet_get_ptr_node_store)(
    NS(NodeSetBase)* SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_is_single_node_set)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );


/* ************************************************************************* */
/* NodeSetSingle: */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_is_node_set_single)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeSetSingle) const*
NS(NodeSet_as_const_node_set_single)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeSetSingle)* NS(NodeSet_as_node_set_single)(
    NS(NodeSetBase)* SIXTRL_RESTRICT ptr_node_set );

/* ------------------------------------------------------------------------ */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeSetSingle)* NS(NodeSetSingle_new)(
    NS(NodeStore)* SIXTRL_RESTRICT node_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t)
NS(NodeSet_get_selected_node_index)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId) const*
NS(NodeSet_get_selected_node_id)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeSet_select_node)(
    NS(NodeSetBase)* SIXTRL_RESTRICT set, NS(node_index_t) const node_index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_t)
NS(NodeSet_get_default_node_index)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId) const*
NS(NodeSet_get_default_node_id)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_has_default_node)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_can_change_to_node)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    NS(node_index_t) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(NodeSet_change_to_node)(
    NS(NodeSetBase)* SIXTRL_RESTRICT set, NS(node_index_t) const index );

#endif /* !defiend( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_SET_C99_H__ */
/* end: sixtracklib/common/control/node_set.h */
