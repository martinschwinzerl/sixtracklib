#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

#include <gtest/gtest.h>

#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/opencl/control/controller.h"
#include "sixtracklib/opencl/control/program_store.h"

TEST( CXXOpenCLControlController, NormalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using ctrl_type = st::OclController;
    using program_store_type = st::OclProgramStore;
    using ctx_type = st::OclContext;

    auto node_store = std::make_shared< st::OclNodeStore >();
    auto program_store = std::make_shared< program_store_type >();

    if( ( node_store.get() == nullptr ) || ( node_store->empty() ) )
    {
        std::cout << "No OpenCL nodes found -> skipping tests" << std::endl;
        return;
    }

    for( auto const& node_id : node_store->node_ids() )
    {
        ctx_type ctx( node_store, node_id );
        ctrl_type ctrl( node_id, ctx, program_store );

        ASSERT_TRUE(  ctrl.selected_node_id().compare( node_id ) == 0 );
        ASSERT_TRUE( &ctrl.context() == &ctx );
        ASSERT_TRUE(  ctrl.num_cmd_queues() == st::size_type{ 1 } );
        ASSERT_TRUE(  ctrl.ptr_cmd_queue( 0u ) != nullptr );
    }

}
