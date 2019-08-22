#ifndef SIXTRACKLIB_TESTS_COMMON_CONTROL_TEST_NODE_INFO_C99_H__
#define SIXTRACKLIB_TESTS_COMMON_CONTROL_TEST_NODE_INFO_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/control/node_info.hpp"
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++ */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TestNodeInfo_add_to_node_store)( NS(NodeStore)* SIXTRL_RESTRICT store,
        NS(arch_size_t) const num_nodes,
        NS(arch_id_t) const* arch_ids_begin,
        NS(node_platform_id_t) const* platform_ids_begin,
        NS(arch_size_t) const* max_atachment_cnt_begin,
        NS(arch_size_t) const* max_selection_cnt_begin,
        NS(node_index_t)* node_indices_begin );

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++ */

#endif /* SIXTRACKLIB_TESTS_COMMON_CONTROL_TEST_NODE_INFO_C99_H__ */

/* end: tests/sixtracklib/testlib/common/control/node_info.h */
