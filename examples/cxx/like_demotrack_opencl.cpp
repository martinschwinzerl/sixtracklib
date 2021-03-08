#include "sixtracklib/sixtracklib.hpp"
#include "sixtracklib/testlib.h"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>

#include "like_demotrack_helpers.hpp"

int main( int argc, char* argv[] )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::size_type NUM_PARTICLES = 50 * 1024;
    st::particle_index_type TRACK_UNTIL_TURN = 100;

    std::ostringstream a2str;
    a2str << ::NS(PATH_TO_BASE_DIR) << "tests/testdata/lhc_no_bb/";
    std::string const base_data_dir = a2str.str();
    a2str << "cobj_initial_particles.bin";
    std::string path_to_particle_data = a2str.str();
    a2str.str( "" );

    a2str << base_data_dir << "cobj_lattice.bin";
    std::string path_to_lattice_data = a2str.str();
    a2str.str( "" );

    std::string node_id_str = std::string{};
    std::string path_to_output_data = std::string{};

    if( !::NS(OpenCL_enabled)() )
    {
        std::cout << "OpenCL disabled -> stopping\r\n" << std::endl;
        return 0;
    }

    auto node_store = std::make_shared< st::OclNodeStore >();
    SIXTRL_ASSERT( node_store.get() != nullptr );

    if( node_store->empty() )
    {
        std::cout << "No OpenCL nodes found -> skipping tests" << std::endl;
        return 0;
    }

    if( argc >= 2 )
    {
        node_id_str = argv[ 1 ];

        if( argc >= 3 )
        {
            NUM_PARTICLES = std::stoul( argv[ 2 ] );

            if( argc >= 4 )
            {
                TRACK_UNTIL_TURN = std::stoi( argv[ 3 ] );

                if( argc >= 5 )
                {
                    path_to_particle_data = std::string{ argv[ 4 ] };
                    if( path_to_particle_data.compare( "default" ) == 0 ) {
                        path_to_particle_data.clear(); }

                    if( argc >= 6 )
                    {
                        path_to_lattice_data = std::string{ argv[ 5 ] };
                        if( path_to_lattice_data.compare( "default" ) == 0 ) {
                            path_to_lattice_data.clear(); }

                        if( argc >= 7 )
                        {
                            path_to_output_data = std::string{ argv[ 6 ] };
                            if( path_to_output_data.compare( "none" ) == 0 ) {
                                path_to_output_data.clear(); }
                        }
                    }
                }
            }
        }
    }

    st::NodeId node_id( node_id_str );

    if( ( !node_id.is_legal() ) || ( argc < 2 ) ||
        ( !node_store->has_node_id( node_id ) ) )
    {
        std::cout << "Usage : " << argv[ 0 ] << "node_id_str "
                  << " [NUM_PARTICLES] [TRACK_UNTIL_TURN]"
                  << " [PATH_TO_PARTICLE_DATA] [PATH_TO_LATTICE_DATA]"
                  << " [PATH_TO_OUTPUT_DATA]\r\n"
                  << "\r\n"
                  << "Default / Selected Values : \r\n"
                  << "NUM_PARTICLES             : " << NUM_PARTICLES << "\r\n"
                  << "TRACK_UNTIL_TURN          : " << TRACK_UNTIL_TURN << "\r\n"
                  << "PATH_TO_PARTICLE_DATA     : " << path_to_particle_data << "\r\n"
                  << "PATH_TO_LATTICE_DATA      : " << path_to_lattice_data << "\r\n"
                  << "PATH_TO_OUTPUT_DATA       : " << path_to_output_data << "\r\n"
                  << std::endl;

        for( auto const& node_info : node_store->node_infos() )
        {
            node_info.to_stream( std::cout,
                st::NODE_ID_STR_FORMAT_BACKEND_STR, nullptr, &node_id );

            std::cout << "\r\n";
        }

        std::cout << std::endl;
        return 0;
    }

    st::OclProgramConfigStore config_options;
    if( st::STATUS_SUCCESS == config_options.update_from_file(
            std::string{ "./opencl.toml" } ) )
    {
        std::ifstream input_file( "./opencl.toml" );

        std::cout << "INFO :: read config options from input file ./opencl.toml"
                  << std::endl
                  << "INFO :: content of opencl.toml file:\r\n"
                  << input_file.rdbuf() << std::endl;
    }

    /* --------------------------------------------------------------------- */
    /* Prepare particles data */

    st::CBuffer in_pbuffer( path_to_particle_data );
    st::CBuffer pbuffer;
    st::cobj_size_type pset_idx = st::cobj_size_type{ 1 };

    st::status_type status = st::examples::Prepare_particle_data_cobj(
        in_pbuffer, pbuffer, NUM_PARTICLES, &pset_idx );

    if( status != st::STATUS_SUCCESS )
    {
        std::cout << "error :: unable to prepare particle data" << std::endl;
        return 0;
    }

    st::CBuffer config_buffer;

    /* --------------------------------------------------------------------- */
    /* Prepare lattice data */

    st::CBuffer lattice( path_to_lattice_data );
    st::size_type eot_marker_idx = st::size_type{ 0 };
    status = st::examples::Prepare_lattice_data_cobj( lattice, &eot_marker_idx );

    if( status != st::STATUS_SUCCESS )
    {
        std::cout << "error :: unable to prepare lattice data" << std::endl;
        return 0;
    }

    /* --------------------------------------------------------------------- */
    /* Create OpenCL structures */

    a2str << "-I" << ::NS(PATH_TO_SIXTRL_INCLUDE_DIR) << " -Werror";
    std::string const flags = a2str.str();
    a2str.str( "" );

    auto program_store = std::make_shared< st::OclProgramStore >();
    st::OclContext ctx( node_store, node_id );
    st::OclController controller( node_id, ctx, program_store );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* remap program -> move to Controller */

    st::OclRtcProgramItem remap_program;

    a2str << ::NS(PATH_TO_BASE_DIR) << "sixtracklib/opencl/kernels/";
    std::string const ocl_kernel_base_dir = a2str.str();
    std::string const remap_program_name = "cobj_flat_buffer_remap";

    a2str << remap_program_name << ".cl";
    std::string const path_remap_program = a2str.str();
    a2str.str( "" );

    a2str  << SIXTRL_C99_NAMESPACE_STR << "CObjFlatBuffer_remap_opencl";
    std::string const remap_kernel_name = a2str.str();
    a2str.str( "" );

    auto config = config_options.find(
        st::OclProgramKey{ ctx.key(), remap_program_name } );
    SIXTRL_ASSERT( config != nullptr );
    a2str << *config;

    remap_program.set_compile_flags( a2str.str() );
    a2str.str( "" );

    status  = remap_program.create_from_source_file( ctx, path_remap_program );
    status |= remap_program.build( ctx, remap_program_name );

    st::OclKernelItem remap_kernel;
    status |= remap_kernel.init( remap_program, 0, remap_kernel_name );

    if( status != st::STATUS_SUCCESS )
    {
        std::cout << "unable to build remap program & kernel" << std::endl;
        return 0;
    }

    ::size_t remap_max_wg_size = ::cl_uint{ 0 };
    ::cl_int ret = remap_kernel.cl_kernel().getWorkGroupInfo(
        controller.cl_selected_device(), CL_KERNEL_WORK_GROUP_SIZE,
            &remap_max_wg_size );

    if( ( ret != CL_SUCCESS ) || ( remap_max_wg_size == ::size_t{ 0 } ) )
    {
        std::cout << "unable to retrieve wg size for remap kernel" << std::endl;
        return 0;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* track program -> move to Controller */

    st::OclRtcProgramItem track_program;

    std::string const track_program_name =
        "particle_track_until_cobj_flat_buffer";

    a2str << ocl_kernel_base_dir << track_program_name << ".cl";
    std::string const path_track_program = a2str.str();
    a2str.str( "" );
    a2str << SIXTRL_C99_NAMESPACE_STR
           << "Track_until_particle_cobj_flat_buffer_opencl";
    std::string const track_kernel_name = a2str.str();
    a2str.str( "" );

    config = config_options.find(
        st::OclProgramKey{ ctx.key(), remap_program_name } );
    SIXTRL_ASSERT( config != nullptr );
    a2str << *config;

    track_program.set_compile_flags( a2str.str() );
    std::cout << "INFO :: compiling kernel: " << track_kernel_name << "\r\n"
              << "INFO :: compile flags   : " << a2str.str() << std::endl;
    a2str.str( "" );

    status  = track_program.create_from_source_file( ctx, path_track_program );
    status |= track_program.build( ctx, track_kernel_name );

    st::OclKernelItem track_kernel;
    status |= track_kernel.init( track_program, 1, track_kernel_name );

    if( status != st::STATUS_SUCCESS )
    {
        std::cout << "unable to build track program & kernel" << std::endl;
        return 0;
    }

    ::size_t track_max_wg_size = ::cl_uint{ 0 };
    ret = track_kernel.cl_kernel().getWorkGroupInfo(
        controller.cl_selected_device(), CL_KERNEL_WORK_GROUP_SIZE,
            &track_max_wg_size );

    if( ( ret != CL_SUCCESS ) || ( track_max_wg_size == ::size_t{ 0 } ) )
    {
        std::cout << "unable to retrieve wg size for remap kernel" << std::endl;
        return 0;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* Create buffers */

    st::OclArgument pbuffer_arg( pbuffer.as_c_api(), controller );
    st::OclArgument lattice_arg( lattice.as_c_api(), controller );
    st::OclArgument config_arg( config_buffer.as_c_api(), controller );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* remap buffers on the device side */

    auto& queue = controller.cmd_queue( 0u ).cl_command_queue();

    SIXTRL_UINT64_TYPE const slot_size_arg = pbuffer.slot_size();
    ret = remap_kernel.cl_kernel().setArg( 0, pbuffer_arg.cl_buffer() );
    ret = remap_kernel.cl_kernel().setArg( 1, slot_size_arg );

    ret = queue.enqueueNDRangeKernel( remap_kernel.cl_kernel(), cl::NullRange,
            cl::NDRange( remap_max_wg_size ), cl::NullRange );

    ret = queue.flush();

    if( ret != CL_SUCCESS )
    {
        std::cout << "Unable to remap particles buffer" << std::endl;
        return 0;
    }


    ret = remap_kernel.cl_kernel().setArg( 0, lattice_arg.cl_buffer() );
    ret = remap_kernel.cl_kernel().setArg( 1, slot_size_arg );

    ret = queue.enqueueNDRangeKernel(
        remap_kernel.cl_kernel(), cl::NullRange,
            cl::NDRange( remap_max_wg_size ), cl::NullRange );

    ret = queue.flush();

    if( ret != CL_SUCCESS )
    {
        std::cout << "Unable to remap lattices buffer" << std::endl;
        return 0;
    }


    ret = remap_kernel.cl_kernel().setArg( 0, config_arg.cl_buffer() );
    ret = remap_kernel.cl_kernel().setArg( 1, slot_size_arg );

    ret = queue.enqueueNDRangeKernel(
        remap_kernel.cl_kernel(), cl::NullRange,
            cl::NDRange( remap_max_wg_size ), cl::NullRange );

    ret = queue.flush();

    if( ret != CL_SUCCESS )
    {
        std::cout << "Unable to remap config_buffer" << std::endl;
        return 0;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* prepare tracking */

     std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n"
               << "OPENCL TIMING: \r\n";

    SIXTRL_UINT64_TYPE const pset_idx_arg = pset_idx;
    SIXTRL_INT64_TYPE  const line_start_at_element = 0;
    SIXTRL_INT64_TYPE  const until_turn_arg = TRACK_UNTIL_TURN;
    SIXTRL_UINT64_TYPE const eot_marker_idx_arg = eot_marker_idx;
    SIXTRL_UINT64_TYPE const line_start_index_arg = 0u;
    SIXTRL_UINT64_TYPE const track_config_idx_arg = 0u;

    ret = track_kernel.cl_kernel().setArg( 0, pbuffer_arg.cl_buffer() );
    ret = track_kernel.cl_kernel().setArg( 1, pset_idx_arg );
    ret = track_kernel.cl_kernel().setArg( 2, line_start_at_element );
    ret = track_kernel.cl_kernel().setArg( 3, until_turn_arg );
    ret = track_kernel.cl_kernel().setArg( 4, lattice_arg.cl_buffer() );
    ret = track_kernel.cl_kernel().setArg( 5, eot_marker_idx_arg );
    ret = track_kernel.cl_kernel().setArg( 6, line_start_index_arg );
    ret = track_kernel.cl_kernel().setArg( 7, config_arg.cl_buffer() );
    ret = track_kernel.cl_kernel().setArg( 8, track_config_idx_arg );
    ret = track_kernel.cl_kernel().setArg( 9, slot_size_arg );

    st::size_type num_blocks = NUM_PARTICLES / track_max_wg_size;
    if( num_blocks * track_max_wg_size < NUM_PARTICLES ) ++num_blocks;
    st::size_type const num_work_items = num_blocks * track_max_wg_size;

    std::cout << "track_kernel : max_wg_size    = " << track_max_wg_size << "\r\n"
              << "             : num_blocks     = " << num_blocks << "\r\n"
              << "             : num_work_items = " << num_work_items << "\r\n"
              << std::endl;

    queue.finish();

    auto t_start = std::chrono::steady_clock::now();

    cl::Event run_event;

    ret = queue.enqueueNDRangeKernel(
        track_kernel.cl_kernel(), cl::NullRange, cl::NDRange( num_work_items ),
            cl::NullRange, nullptr, &run_event );

    ret = queue.flush();

    run_event.wait();
    auto t_stop = std::chrono::steady_clock::now();

    double const t_opencl_elapsed = double{ 1e-6 } * std::chrono::duration_cast<
        std::chrono::microseconds >( t_stop - t_start ).count ();

    std::cout << "elapsed time : " << t_opencl_elapsed << " sec\r\n"
              << "             : " << t_opencl_elapsed / static_cast< double >(
                NUM_PARTICLES * TRACK_UNTIL_TURN ) << " sec / particle / turn\r\n"
              << std::endl;

    ret = queue.enqueueReadBuffer( pbuffer_arg.cl_buffer(), true, ::size_t{ 0 },
            pbuffer.size(), pbuffer.p_base_begin() );

    status = pbuffer.remap();

    if( !path_to_output_data.empty() )
    {
        pbuffer.to_file_normalised( path_to_output_data, 0x1000 );
    }

    return 0;
}
