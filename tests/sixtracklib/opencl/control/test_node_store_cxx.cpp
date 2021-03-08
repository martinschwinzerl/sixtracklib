#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/opencl/control/node_store.h"
#include "sixtracklib/opencl/control/context.h"

TEST( CXXOpenCLControlNodeStore, NormalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using node_store_type = st::OclNodeStore;

    std::vector< st::NodeId > available_nodes;

    ASSERT_TRUE( st::STATUS_SUCCESS == node_store_type::GET_AVAILABLE_NODES(
        available_nodes, nullptr, nullptr ) );

    if( available_nodes.empty() )
    {
        std::cout << "No OpenCL nodes found -> skipping tests" << std::endl;
        return;
    }

    node_store_type node_store;

    ASSERT_TRUE( node_store.num_nodes() == available_nodes.size() );

    for( auto const& node_id : available_nodes )
    {
        ASSERT_TRUE( node_store.has_node_id( node_id ) );
        ASSERT_TRUE( node_store.has_node_id(
            node_id.platform_id(), node_id.device_id() ) );

        ASSERT_TRUE( node_store.has_platform_id( node_id.platform_id() ) );
        ASSERT_TRUE( node_store.node_index( node_id ) !=
                     st::NodeId::ILLEGAL_PLATFORM_ID );
    }
}
