#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/opencl/control/controller.h"
#include "sixtracklib/opencl/control/program_store.h"

TEST( CXXOpenCLControlController, NormalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using ctrl_type = st::OclController;
    using ctx_type = st::OclContext;
    using program_store_type = st::OclProgramStore;

    std::vector< st::NodeId > available_nodes;

    ASSERT_TRUE( st::STATUS_SUCCESS == ctrl_type::GET_AVAILABLE_NODES(
        available_nodes, nullptr, nullptr ) );

    if( available_nodes.empty() )
    {
        std::cout << "No OpenCL nodes found -> skipping tests" << std::endl;
        return;
    }

    auto program_store = std::make_shared< program_store_type >();

    for( auto const& node_id : available_nodes )
    {
        auto ctx = std::make_shared< ctx_type >( node_id );
        ctrl_type ctrl( node_id, ctx, program_store );
        ASSERT_TRUE( ctrl.selected_node_id().compare( node_id ) == 0 );
        ASSERT_TRUE( ctrl.num_cmd_queues() == st::size_type{ 1 } );
        ASSERT_TRUE( ctrl.ptr_cmd_queue( 0u ) != nullptr );
    }



}
