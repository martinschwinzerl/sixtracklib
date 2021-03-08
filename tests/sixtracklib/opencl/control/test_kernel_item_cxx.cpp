#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/opencl/control/program_store.h"
#include "sixtracklib/opencl/control/kernel_item.h"
#include "sixtracklib/common/generated/path.h"

TEST( CXXOpenCLControlKernelItem, NormalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using context_type        = st::OclContext;
    using prog_item_type      = st::OclRtcProgramItem;
    using prog_key_type       = st::OclProgramKey;
    using kernel_item_type    = st::OclKernelItem;
    using st_size_t           = kernel_item_type::size_type;

    std::ostringstream a2str;
    a2str << ::NS(PATH_TO_BASE_DIR) << "tests/sixtracklib/opencl/control/"
          << "opencl.toml";

    st::OclProgramConfigStore program_configs;
    program_configs.update_from_file( a2str.str() );
    a2str.str( "" );

    std::string const program_a_name = "a";

    a2str.str( "" );
    a2str << SIXTRL_C99_NAMESPACE_PREFIX_STR << "CObjFlatBuffer_check_remap_opencl";
    std::string const kernel_a01_name = a2str.str();

    a2str.str( "" );
    a2str << SIXTRL_C99_NAMESPACE_PREFIX_STR << "CObjFlatBuffer_remap_opencl";
    std::string const kernel_a02_name = a2str.str();

    std::vector< std::string > const program_a_kernel_names = {
        kernel_a01_name, kernel_a02_name };

    a2str.str( "" );
    a2str << "#if !defined( SIXTRL_NO_INCLUDES )\r\n"
          << "    #include \"sixtracklib/opencl/kernels/default_defines.h\"\r\n"
          << "    #include \"sixtracklib/common/cobjects/flat_buffer.h\"\r\n"
          << "#endif /* !defined( SIXTRL_NO_INCLUDES ) */\r\n"
          << "\r\n"
          << "__kernel void NS(CObjFlatBuffer_check_remap_opencl)(\r\n"
          << "        SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* "
          << "SIXTRL_RESTRICT buffer,\r\n"
          << "        SIXTRL_UINT64_TYPE const dummy,\r\n"
          << "        SIXTRL_UINT64_TYPE const slot_size )\r\n"
          << "{\r\n"
          << "    ( void )dummy;\r\n"
          << "    if( ( NS(cobj_size_type) )0u == ( NS(cobj_size_type) )get_global_id( 0 ) )\r\n"
          << "    {\r\n"
          << "         SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );\r\n"
          << "         SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );\r\n"
          << "         SIXTRL_ASSERT( NS(CObjFlatBuffer_has_cbuffer_structure)(\r\n"
          << "             buffer, 0u, slot_size ) );\r\n"
          << "         if( NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) {\r\n"
          << "              printf( \"buffer needs remapping!\\r\\n\" ); }\r\n"
          << "     }\r\n"
          << "}\r\n\r\n"
          << "__kernel void NS(CObjFlatBuffer_remap_opencl)(\r\n"
          << "        SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* "
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
          << "             NS(CObjFlatBuffer_remap)( buffer, slot_size ); }\r\n"
          << "     }\r\n"
          << "}\r\n";

    std::string const program_a_source = a2str.str();

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    std::string const program_b_name = "b";
//     std::string const program_b_file = "b.cl";

    a2str.str( "" );
    a2str << SIXTRL_C99_NAMESPACE_PREFIX_STR
          << "CObjFlatBuffer_print_num_objects_opencl";
    std::string const kernel_b_name = a2str.str();
    std::vector< std::string > const program_b_kernel_names = { kernel_b_name };

    a2str.str( "" );
    a2str << "#if !defined( SIXTRL_NO_INCLUDES )\r\n"
          << "    #include \"sixtracklib/opencl/kernels/default_defines.h\"\r\n"
          << "    #include \"sixtracklib/common/cobjects/flat_buffer.h\"\r\n"
          << "#endif /* !defined( SIXTRL_NO_INCLUDES ) */\r\n"
          << "\r\n"
          << "__kernel void NS(CObjFlatBuffer_print_num_objects_opencl)(\r\n"
          << "        SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* "
          << "SIXTRL_RESTRICT buffer )\r\n"
          << "{\r\n"
          << "    if( ( NS(cobj_size_type) )0u == ( NS(cobj_size_type) )get_global_id( 0 ) )\r\n"
          << "    {\r\n"
          << "         NS(cobj_size_type) const slot_size = ( NS(cobj_size_type) )8u;\r\n"
          << "         SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );\r\n"
          << "         SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );\r\n"
          << "         SIXTRL_ASSERT( NS(CObjFlatBuffer_has_cbuffer_structure)(\r\n"
          << "             buffer, 0u, slot_size ) );\r\n"
          << "         SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) );\r\n"
          << "         printf( \"num_objects : %d\\r\\n\", \r\n"
          << "                 ( int )NS(CObjFlatBuffer_num_objects)( buffer, slot_size ) );\r\n"
          << "     }\r\n"
          << "}";

    std::string const program_b_source = a2str.str();
    a2str.str( "" );

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    auto node_store = std::make_shared< st::OclNodeStore >();

    if( ( node_store.get() == nullptr ) || ( node_store->empty() ) )
    {
        std::cout << "No OpenCL nodes found -> skipping tests" << std::endl;
        return;
    }

    for( auto const& node_id : node_store->node_ids() )
    {
        context_type ctx( node_store, node_id );
        ASSERT_TRUE( ctx.key().is_legal() );
        ASSERT_TRUE( ctx.key().num_devices == st::size_type{ 1 } );
        ASSERT_TRUE( ctx.key().contains_node_id( node_id ) );

        auto config = program_configs.find( prog_key_type{ ctx.key(), program_a_name } );
        ASSERT_TRUE( config != nullptr );
        a2str << *config;

        prog_item_type prog_a;

        ASSERT_TRUE( prog_a.create_from_source( ctx, program_a_source ) ==
                     st::STATUS_SUCCESS );
        prog_a.set_compile_flags( a2str.str() );
        ASSERT_TRUE( prog_a.build( ctx, program_a_name ) == st::STATUS_SUCCESS );
        a2str.str( "" );

        config = program_configs.find( prog_key_type{ ctx.key(), program_b_name } );
        ASSERT_TRUE( config != nullptr );
        a2str << *config;

        prog_item_type prog_b;
        ASSERT_TRUE( prog_b.create_from_source( ctx, program_b_source ) ==
                     st::STATUS_SUCCESS );
        prog_b.set_compile_flags( a2str.str() );
        ASSERT_TRUE( prog_b.build( ctx, program_b_name ) == st::STATUS_SUCCESS );
        a2str.str( "" );

        kernel_item_type kernel_a01;

        ASSERT_FALSE( kernel_a01.key().is_legal() );

        ASSERT_TRUE( st::STATUS_SUCCESS == kernel_a01.init(
            prog_a, 0, kernel_a01_name ) );

        ASSERT_TRUE( kernel_a01.key().is_legal() );
        ASSERT_TRUE( kernel_a01.key().program_id == 0 );
        ASSERT_TRUE( kernel_a01.key().name.compare( kernel_a01_name ) == 0 );
        ASSERT_TRUE( kernel_a01.key().options.empty() );
        ASSERT_TRUE( kernel_a01.num_kernel_args() == st_size_t{ 3 } );

        kernel_item_type kernel_a02;

        ASSERT_FALSE( kernel_a02.key().is_legal() );

        ASSERT_TRUE( st::STATUS_SUCCESS == kernel_a02.init(
            prog_a, 0, kernel_a02_name ) );

        ASSERT_TRUE( kernel_a02.key().is_legal() );
        ASSERT_TRUE( kernel_a02.key().program_id == 0 );
        ASSERT_TRUE( kernel_a02.key().name.compare( kernel_a02_name ) == 0 );
        ASSERT_TRUE( kernel_a02.key().options.empty() );
        ASSERT_TRUE( kernel_a02.num_kernel_args() == st_size_t{ 2 } );

        kernel_item_type kernel_b;

        ASSERT_FALSE( kernel_b.key().is_legal() );

        ASSERT_TRUE( st::STATUS_SUCCESS == kernel_b.init(
            prog_b, 1, kernel_b_name ) );

        ASSERT_TRUE( kernel_b.key().is_legal() );
        ASSERT_TRUE( kernel_b.key().program_id == 1 );
        ASSERT_TRUE( kernel_b.key().name.compare( kernel_b_name ) == 0 );
        ASSERT_TRUE( kernel_b.key().options.empty() );
        ASSERT_TRUE( kernel_b.num_kernel_args() == st_size_t{ 1 } );
    }
}
