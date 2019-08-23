#ifndef SIXTRACKLIB_TESTS_COMMON_CONTROL_TEST_NODE_SET_C99_H__
#define SIXTRACKLIB_TESTS_COMMON_CONTROL_TEST_NODE_SET_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/control/node_set.hpp"

    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++ */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(TestNodeSetBase)* NS(TestNodeSetBase_create)(
    NS(NodeStore)* SIXTRL_RESTRICT store );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TestNodeSetBase_set_min_num_selectable_nodes)(
    NS(TestNodeSetBase)* SIXTRL_RESTRICT node_set,
    NS(arch_size_t) const min_sel_cnt );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TestNodeSetBase_set_max_num_selectable_nodes)(
    NS(TestNodeSetBase)* SIXTRL_RESTRICT node_set,
    NS(arch_size_t) const max_sel_cnt );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TestNodeSetBase_set_min_num_default_nodes)(
    NS(TestNodeSetBase)* SIXTRL_RESTRICT node_set,
    NS(arch_size_t) const min_default_cnt );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TestNodeSetBase_set_max_num_default_nodes)(
    NS(TestNodeSetBase)* SIXTRL_RESTRICT node_set,
    NS(arch_size_t) const max_default_cnt );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(TestNodeSetSingle)* NS(TestNodeSetSingle_create)(
    NS(NodeStore)* SIXTRL_RESTRICT store );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TestNodeSetSingle_set_min_num_selectable_nodes)(
    NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set,
    NS(arch_size_t) const min_sel_cnt );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TestNodeSetSingle_set_max_num_selectable_nodes)(
    NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set,
    NS(arch_size_t) const max_sel_cnt );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TestNodeSetSingle_set_min_num_default_nodes)(
    NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set,
    NS(arch_size_t) const min_default_cnt );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TestNodeSetSingle_set_max_num_default_nodes)(
    NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set,
    NS(arch_size_t) const min_default_cnt );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TestNodeSetSingle_set_can_directly_change_selected_node_flag)(
    NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set, bool const flag );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TestNodeSetSingle_set_can_unselect_node_flag)(
    NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set, bool const flag );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TestNodeSetSingle_set_use_auto_select_flag)(
    NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set, bool const flag );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TestNodeSetSingle_select_default_node)(
    NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set,
    NS(node_index_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TestNodeSetSingle_remove_default_node)(
    NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set );


#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++ */

#endif /* SIXTRACKLIB_TESTS_COMMON_CONTROL_TEST_NODE_SET_C99_H__ */

/* end: tests/sixtracklib/testlib/common/control/node_set.h */
