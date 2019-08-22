#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
   #include "sixtracklib/testlib/common/control/node_info.h"
   #include "sixtracklib/testlib/common/control/node_info.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
        #include <cstddef>
        #include <cstdlib>
#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_info.hpp"
    #include "sixtracklib/common/control/node_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

namespace st = SIXTRL_CXX_NAMESPACE;
namespace st_test = SIXTRL_CXX_NAMESPACE::tests;

::NS(arch_status_t) NS(TestNodeInfo_add_to_node_store)(
    ::NS(NodeStore)* SIXTRL_RESTRICT store,
    ::NS(arch_size_t) const num_nodes,
    ::NS(arch_id_t) const* arch_ids_begin,
    ::NS(node_platform_id_t) const* platform_ids_begin,
    ::NS(arch_size_t) const* max_atachment_cnt_begin,
    ::NS(arch_size_t) const* max_selection_cnt_begin,
    ::NS(node_index_t)* node_indices_begin )
{
    return ( store != nullptr )
        ? st_test::TestNodeInfo_add_to_node_store( *store, num_nodes,
            arch_ids_begin, platform_ids_begin, max_atachment_cnt_begin,
                max_selection_cnt_begin, node_indices_begin )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

#endif /* C++, Host */

/* end: tests/sixtracklib/testlib/common/control/node_info_c99.cpp */
