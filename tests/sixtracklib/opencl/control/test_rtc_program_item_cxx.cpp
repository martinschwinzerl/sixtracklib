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

TEST( CXXOpenCLControlRtcProgamItem, CompileDummyKernel )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using ctrl_type = st::OclController;
    using ctx_type = st::OclContext;
    using program_item_type = st::OclRtcProgramItem;

    std::string const program_name = "dummy.cl";

    std::ostringstream a2str;
    a2str << "-I" << ::NS(PATH_TO_SIXTRL_INCLUDE_DIR) << " -Werror";
    std::string const compile_options = a2str.str();

    a2str.str( "" );
    a2str << SIXTRL_C99_NAMESPACE_PREFIX_STR << "CObjFlatBuffer_check_remap";
    std::string const dummy_kernel_name = a2str.str();

    a2str.str( "" );
    a2str << "#if !defined( SIXTRL_NO_INCLUDES )\r\n"
          << "    #include \"sixtracklib/opencl/kernels/default_defines.h\"\r\n"
          << "    #include \"sixtracklib/common/cobjects/flat_buffer.h\"\r\n"
          << "#endif /* !defined( SIXTRL_NO_INCLUDES ) */\r\n"
          << "\r\n"
          << "__kernel void NS(CObjFlatBuffer_check_remap)(\r\n"
          << "        SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* "
          << "SIXTRL_RESTRICT buffer,\r\n"
          << "        SIXTRL_UINT64_TYPE const slot_size )\r\n"
          << "{\r\n"
          << "    if( ( NS(cobj_size_type) )0u == ( NS(cobj_size_type) )get_global_id( 0 ) )\r\n"
          << "    {\r\n"
          << "         SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );\r\n"
          << "         SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );\r\n"
          << "         SIXTRL_ASSERT( NS(CObjFlatBuffer_has_cbuffer_structure)(\r\n"
          << "             buffer, 0u, slot_size ) );\r\n"
          << "         if( NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) {\r\n"
          << "              printf( \"buffer needs remapping!\\r\\n\" ); }\r\n"
          << "     }\r\n"
          << "}";

    std::string const kernel_source_code = a2str.str();
    a2str.str( "" );

    a2str << "./" << program_name;
    std::string const path_to_program = a2str.str();

    std::ofstream write_to_this_file( path_to_program.c_str() );
    write_to_this_file << kernel_source_code << "\r\n";
    write_to_this_file.close();

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

        program_item_type program_from_source;

        ASSERT_TRUE( program_from_source.create_from_source(
            *ctx, kernel_source_code ) == st::STATUS_SUCCESS );

        program_from_source.set_compile_flags( compile_options );

        ASSERT_FALSE( program_from_source.is_compiled() );
        ASSERT_FALSE( program_from_source.created_from_file() );
        ASSERT_TRUE(  program_from_source.num_devices() == ctx->key().num_devices );

        ASSERT_TRUE( st::STATUS_SUCCESS == program_from_source.build(
            *ctx, program_name ) );

        ASSERT_TRUE( program_from_source.is_compiled() );
        ASSERT_TRUE( program_from_source.num_kernels() == st::size_type{ 1 } );
        ASSERT_TRUE( program_from_source.kernel_name_str( 0 ).compare(
                dummy_kernel_name ) == 0 );

        program_item_type program_from_file;

        ASSERT_TRUE( program_from_file.create_from_source_file(
            *ctx, path_to_program ) == st::STATUS_SUCCESS );

        program_from_file.set_compile_flags( compile_options );

        ASSERT_FALSE( program_from_file.is_compiled() );
        ASSERT_TRUE(  program_from_file.created_from_file() );
        ASSERT_TRUE(  program_from_file.num_devices() == ctx->key().num_devices );

        ASSERT_TRUE( st::STATUS_SUCCESS == program_from_file.build(
            *ctx, program_name ) );

        ASSERT_TRUE( program_from_file.is_compiled() );
        ASSERT_TRUE( program_from_file.num_kernels() == st::size_type{ 1 } );
        ASSERT_TRUE( program_from_file.kernel_name_str( 0 ).compare(
                dummy_kernel_name ) == 0 );
    }
}
