#include <cstddef>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/generated/path.h"
#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/opencl/control/controller.h"
#include "sixtracklib/opencl/control/program_store.h"

TEST( CXXOpenCLKernelsCobjFlatBufferRemap, RunTimeCompileKernel )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using ctrl_type = st::OclController;
    using ctx_type = st::OclContext;
    using program_item_type = st::OclRtcProgramItem;

    std::string const program_name = "cobj_flat_buffer_remap.cl";
    std::ostringstream a2str;
    a2str << ::NS(PATH_TO_BASE_DIR) << "sixtracklib/opencl/kernels/"
          << program_name;
    std::string const path_to_kernel_src = a2str.str();
    a2str.str( "" );

    a2str << "-I" << ::NS(PATH_TO_SIXTRL_INCLUDE_DIR) << " -Werror";
    std::string const compile_options = a2str.str();

    a2str.str( "" );
    a2str << SIXTRL_C99_NAMESPACE_PREFIX_STR << "CObjFlatBuffer_remap_opencl";
    std::string const kernel_name = a2str.str();

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
        auto ctx = std::make_shared< ctx_type >( node_id );
        ASSERT_TRUE( ctx->key().is_legal() );
        ASSERT_TRUE( ctx->key().num_devices == st::size_type{ 1 } );
        ASSERT_TRUE( ctx->key().contains_node_id( node_id ) );

        program_item_type program_from_file;

        ASSERT_TRUE( program_from_file.create_from_source_file(
            *ctx, path_to_kernel_src ) == st::STATUS_SUCCESS );

        program_from_file.set_compile_flags( compile_options );
        ASSERT_TRUE( st::STATUS_SUCCESS == program_from_file.build(
            *ctx, program_name ) );

        ASSERT_TRUE( program_from_file.is_compiled() );
        ASSERT_TRUE( program_from_file.num_kernels() == st::size_type{ 1 } );
        ASSERT_TRUE( program_from_file.kernel_name_str( 0 ).compare(
            kernel_name ) == 0 );
    }
}
