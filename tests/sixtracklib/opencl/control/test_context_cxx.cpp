#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/opencl/control/context.h"

TEST( CXXOpenCLControlContext, NormalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using node_store_type = st::OclNodeStore;
    using ctx_type = st::OclContext;

    auto node_store = std::make_shared< node_store_type >();
    SIXTRL_ASSERT( node_store.get() != nullptr );

    if( node_store->empty() )
    {
        std::cout << "No OpenCL nodes found -> skipping tests" << std::endl;
        return;
    }

    for( auto const& node_id : node_store->node_ids() )
    {
        ctx_type ctx( node_store, node_id );
    }
}
