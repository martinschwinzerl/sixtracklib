#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/opencl/control/argument.h"
#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/opencl/control/controller.h"
#include "sixtracklib/opencl/control/program_store.h"
#include "sixtracklib/common/generated/path.h"
#include "sixtracklib/common/cobjects/cbuffer.hpp"

TEST( CXXOpenCLControlArgument, NormalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using arg_type = st::OclArgument;
    using ctrl_type = st::OclController;
    using ctx_type = st::OclContext;
    using program_store_type = st::OclProgramStore;

    std::ostringstream a2str;
    a2str << ::NS(PATH_TO_BASE_DIR) << "tests/testdata/lhc_no_bb/"
          << "cobj_particles_elem_by_elem_pysixtrack.bin";
    std::string const path_to_cbuffer_dump = a2str.str();

    auto program_store = std::make_shared< program_store_type >();
    auto node_store = std::make_shared< st::OclNodeStore >();

    if( ( node_store.get() == nullptr ) || ( node_store->empty() ) )
    {
        std::cout << "No OpenCL nodes found -> skipping tests" << std::endl;
        return;
    }

    for( auto const& node_id : node_store->node_ids() )
    {
        st::CBuffer cbuffer( path_to_cbuffer_dump );

        ctx_type ctx( node_store, node_id );
        ctrl_type ctrl( node_id, ctx, program_store );
        arg_type argument( cbuffer.as_c_api(), ctrl );
    }
}
