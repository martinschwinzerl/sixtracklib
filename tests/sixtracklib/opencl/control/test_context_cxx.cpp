#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/opencl/control/context.h"
#include "sixtracklib/opencl/control/controller.h"

TEST( CXXOpenCLControlContext, NormalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using ctrl_type = st::OclController;
    using ctx_type = st::OclContext;

    std::vector< st::NodeId > available_nodes;

    ASSERT_TRUE( st::STATUS_SUCCESS == ctrl_type::GET_AVAILABLE_NODES(
        available_nodes, nullptr, nullptr ) );

    if( available_nodes.empty() )
    {
        std::cout << "No OpenCL nodes found -> skipping tests" << std::endl;
        return;
    }

    for( auto const& node_id : available_nodes )
    {
        ctx_type ctx( node_id );
    }



}
