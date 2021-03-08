#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/opencl/control/controller.h"
#include "sixtracklib/opencl/control/program_store.h"
#include "sixtracklib/common/generated/path.h"

TEST( CXXOpenCLControlProgramStore, NormalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using context_type       = st::OclContext;
    using program_store_type = st::OclProgramStore;
    using rtc_prog_item_type = st::OclRtcProgramItem;

    std::string const program_a_name = "a";

    std::ostringstream a2str;
    a2str << "-I" << ::NS(PATH_TO_SIXTRL_INCLUDE_DIR) << " -Werror";
    std::string const compile_options = a2str.str();

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
          << "SIXTRL_RESTRICT buffer,\r\n"
          << "        SIXTRL_UINT64_TYPE const slot_size )\r\n"
          << "{\r\n"
          << "    if( ( NS(cobj_size_type) )0u == ( NS(cobj_size_type) )get_global_id( 0 ) )\r\n"
          << "    {\r\n"
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

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    auto node_store = std::make_shared< st::OclNodeStore >();

    if( ( node_store.get() == nullptr ) || ( node_store->empty() ) )
    {
        std::cout << "No OpenCL nodes found -> skipping tests" << std::endl;
        return;
    }

    auto program_store = std::make_shared< program_store_type >();
    st::size_type expected_num_programs = st::size_type{ 0 };

    for( auto const& node_id : node_store->node_ids() )
    {
        context_type ctx( node_store, node_id );
        ASSERT_TRUE( ctx.key().is_legal() );
        ASSERT_TRUE( ctx.key().num_devices == st::size_type{ 1 } );
        ASSERT_TRUE( ctx.key().contains_node_id( node_id ) );

        ASSERT_TRUE( program_store->num_stored_items() == expected_num_programs );

        std::unique_ptr< rtc_prog_item_type > prog_a( new rtc_prog_item_type );
        auto prog_a_weak_ptr = prog_a.get();
        ASSERT_TRUE( prog_a_weak_ptr != nullptr );

        ASSERT_TRUE( st::STATUS_SUCCESS == prog_a->create_from_source(
            ctx, program_a_source ) );
        prog_a->set_compile_flags( compile_options );

        ASSERT_TRUE( st::STATUS_SUCCESS == prog_a->build( ctx, program_a_name ) );
        ASSERT_TRUE( prog_a->is_compiled() );
        ASSERT_TRUE( prog_a->num_kernels() == program_a_kernel_names.size() );

        for( st::size_type ii = 0u ; ii < program_a_kernel_names.size() ; ++ii )
        {
            ASSERT_TRUE( program_a_kernel_names[ ii ].compare(
                prog_a->kernel_name( ii ) ) == 0 );
        }

        auto const prog_a_key = prog_a->program_key();
        ASSERT_TRUE( prog_a_key.is_legal() );
        ASSERT_TRUE( prog_a_key.ctx_key == ctx.key() );
        ASSERT_TRUE( prog_a_key.name.compare( program_a_name ) == 0 );

        ASSERT_FALSE( program_store->is_stored( prog_a_key ) );
        ASSERT_FALSE( program_store_type::ILLEGAL_PROGRAM_ID !=
                      program_store->program_id( prog_a_key ) );

        auto const prog_a_id = program_store->store(
            prog_a_key, std::move( prog_a ) );

        ASSERT_TRUE( prog_a_id != program_store_type::ILLEGAL_PROGRAM_ID );
        ASSERT_TRUE( program_store->num_stored_items() ==
                     expected_num_programs + 1u );

        ++expected_num_programs;

        ASSERT_TRUE( program_store->is_stored( prog_a_id ) );
        ASSERT_TRUE( program_store->is_stored( prog_a_key ) );
        ASSERT_TRUE( prog_a_id == program_store->program_id( prog_a_key ) );

        ASSERT_TRUE( program_store->program_item( prog_a_id ) != nullptr );
        ASSERT_TRUE( program_store->program_item( prog_a_id ) == prog_a_weak_ptr );
        ASSERT_TRUE( program_store->program_item( prog_a_key ) == prog_a_weak_ptr );

        auto prog_a_stored_ptr = st::BackendObjBase_cast_to_derived<
            st::ProgramItemBase, rtc_prog_item_type >(
                program_store->program_item( prog_a_id ) );

        ASSERT_TRUE( prog_a_stored_ptr != nullptr );
        ASSERT_TRUE( prog_a_stored_ptr == prog_a_weak_ptr );
        ASSERT_TRUE( prog_a_stored_ptr->is_compiled() );
        ASSERT_TRUE( program_a_source.compare(
            prog_a_stored_ptr->source_code() ) == 0 );
        ASSERT_TRUE( prog_a_stored_ptr->num_kernels() ==
                    program_a_kernel_names.size() );

        for( st::size_type ii = 0u ; ii < program_a_kernel_names.size() ;
                ++ii )
        {
            ASSERT_TRUE( program_a_kernel_names[ ii ].compare(
                prog_a_stored_ptr->kernel_name( ii ) ) == 0 );
        }

        ASSERT_TRUE( prog_a_stored_ptr->program_key().is_legal() );
        ASSERT_TRUE( prog_a_stored_ptr->program_key().ctx_key == ctx.key() );
        ASSERT_TRUE( prog_a_stored_ptr->program_key().name.compare(
            program_a_name ) == 0 );

        std::unique_ptr< rtc_prog_item_type > prog_b( new rtc_prog_item_type );
        auto prog_b_weak_ptr = prog_b.get();
        ASSERT_TRUE( prog_b_weak_ptr != nullptr );

        ASSERT_TRUE( st::STATUS_SUCCESS == prog_b->create_from_source(
            ctx, program_b_source ) );
        prog_b->set_compile_flags( compile_options );

        ASSERT_TRUE( st::STATUS_SUCCESS == prog_b->build( ctx, program_b_name ) );
        ASSERT_TRUE( prog_b->is_compiled() );
        ASSERT_TRUE( prog_b->num_kernels() == program_b_kernel_names.size() );

        for( st::size_type ii = 0u ; ii < program_b_kernel_names.size() ; ++ii )
        {
            ASSERT_TRUE( program_b_kernel_names[ ii ].compare(
                prog_b->kernel_name( ii ) ) == 0 );
        }

        auto const prog_b_key = prog_b->program_key();
        ASSERT_TRUE( prog_b_key.is_legal() );
        ASSERT_TRUE( prog_b_key.ctx_key == ctx.key() );
        ASSERT_TRUE( prog_b_key.name.compare( program_b_name ) == 0 );

        ASSERT_FALSE( program_store->is_stored( prog_b_key ) );
        ASSERT_FALSE( program_store_type::ILLEGAL_PROGRAM_ID !=
                      program_store->program_id( prog_b_key ) );

        auto const prog_b_id = program_store->store(
            prog_b_key, std::move( prog_b ) );

        ASSERT_TRUE( prog_b_id != program_store_type::ILLEGAL_PROGRAM_ID );
        ASSERT_TRUE( program_store->num_stored_items() ==
                     expected_num_programs + 1u );

        ++expected_num_programs;

        ASSERT_TRUE( program_store->is_stored( prog_b_id ) );
        ASSERT_TRUE( program_store->is_stored( prog_b_key ) );
        ASSERT_TRUE( prog_b_id == program_store->program_id( prog_b_key ) );


        ASSERT_TRUE( program_store->program_item( prog_a_id ) != nullptr );
        ASSERT_TRUE( program_store->program_item( prog_b_id ) == prog_b_weak_ptr );
        ASSERT_TRUE( program_store->program_item( prog_b_key ) == prog_b_weak_ptr );

        auto prog_b_stored_ptr = st::BackendObjBase_cast_to_derived<
            st::ProgramItemBase, rtc_prog_item_type >(
                program_store->program_item( prog_b_id ) );

        ASSERT_TRUE( prog_b_stored_ptr != nullptr );
        ASSERT_TRUE( prog_b_stored_ptr == prog_b_weak_ptr );
        ASSERT_TRUE( prog_b_stored_ptr->is_compiled() );
        ASSERT_TRUE( program_b_source.compare(
            prog_b_stored_ptr->source_code() ) == 0 );
        ASSERT_TRUE( prog_b_stored_ptr->num_kernels() ==
                    program_b_kernel_names.size() );

        for( st::size_type ii = 0u ; ii < program_b_kernel_names.size() ;
                ++ii )
        {
            ASSERT_TRUE( program_b_kernel_names[ ii ].compare(
                prog_b_stored_ptr->kernel_name( ii ) ) == 0 );
        }

        ASSERT_TRUE( prog_b_stored_ptr->program_key().is_legal() );
        ASSERT_TRUE( prog_b_stored_ptr->program_key().ctx_key == ctx.key() );
        ASSERT_TRUE( prog_b_stored_ptr->program_key().name.compare(
            program_b_name ) == 0 );

//         auto removed_prog = program_store->remove( prog_a_key );
//
//         ASSERT_TRUE( removed_prog.get() != nullptr );
//         ASSERT_TRUE( removed_prog.get() == prog_a_weak_ptr );
//         ASSERT_TRUE( program_store->num_stored_items() ==
//                      expected_num_programs - 1u );
//         --expected_num_programs;
//
//         ASSERT_FALSE( program_store->is_stored( prog_a_id ) );
//         ASSERT_FALSE( program_store->is_stored( prog_a_key ) );
//
//         ASSERT_TRUE( program_store->program_item( prog_a_id ) ==
//                      nullptr );
//
//         ASSERT_TRUE( program_store->program_item( prog_a_key ) ==
//                      nullptr );
    }
}
