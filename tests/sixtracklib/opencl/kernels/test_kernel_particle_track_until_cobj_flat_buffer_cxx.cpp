#include <cstddef>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/generated/path.h"
#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/opencl/control/program_store.h"

TEST( CXXOpenCLKernelsParticleTrackUntilCObFlatBuffer, RunTimeCompileKernel )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using ctx_type = st::OclContext;
    using prog_key_type = st::OclProgramKey;
    using program_item_type = st::OclRtcProgramItem;

    std::ostringstream a2str;
    a2str << ::NS(PATH_TO_BASE_DIR) << "tests/sixtracklib/opencl/control/"
          << "opencl.toml";

    st::OclProgramConfigStore program_configs;
    program_configs.update_from_file( a2str.str() );
    a2str.str( "" );

    std::string const program_name = "particle_track_until_cobj_flat_buffer.cl";
    a2str << ::NS(PATH_TO_BASE_DIR) << "sixtracklib/opencl/kernels/"
          << program_name;
    std::string const path_to_kernel_src = a2str.str();
    a2str.str( "" );

    a2str << SIXTRL_C99_NAMESPACE_PREFIX_STR
          << "Track_until_particle_cobj_flat_buffer_opencl";
    std::string const kernel_name = a2str.str();
    a2str.str( "" );

    auto node_store = std::make_shared< st::OclNodeStore >();
    SIXTRL_ASSERT( node_store.get() != nullptr );

    if( node_store->empty() )
    {
        std::cout << "No OpenCL nodes found -> skipping tests" << std::endl;
        return;
    }

    for( auto const& node_id : node_store->node_ids() )
    {
        auto ctx = std::make_shared< ctx_type >( node_store, node_id );
        ASSERT_TRUE( ctx->key().is_legal() );
        ASSERT_TRUE( ctx->key().num_devices == st::size_type{ 1 } );
        ASSERT_TRUE( ctx->key().contains_node_id( node_id ) );

        auto config = program_configs.find( prog_key_type{
            ctx->key(), program_name } );
        ASSERT_TRUE( config != nullptr );
        a2str << *config;

        program_item_type program_from_file;

        ASSERT_TRUE( program_from_file.create_from_source_file(
            *ctx, path_to_kernel_src ) == st::STATUS_SUCCESS );

        program_from_file.set_compile_flags( a2str.str() );
        a2str.str( "" );

        ASSERT_TRUE( st::STATUS_SUCCESS == program_from_file.build(
            *ctx, program_name ) );

        ASSERT_TRUE( program_from_file.is_compiled() );
        ASSERT_TRUE( program_from_file.num_kernels() == st::size_type{ 1 } );
        ASSERT_TRUE( program_from_file.kernel_name_str( 0 ).compare(
            kernel_name ) == 0 );
    }
}
