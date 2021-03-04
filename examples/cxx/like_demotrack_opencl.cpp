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

    if( ( !node_id.is_legal() ) || ( argc < 2 ) )
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

        std::vector< st::NodeId      > all_node_ids;
        std::vector< st::OclNodeInfo > all_node_infos;

        st::OclController::GET_AVAILABLE_NODES(
            all_node_ids, &all_node_infos, nullptr );

        for( auto const& node_info : all_node_infos )
        {
            node_info.to_stream( std::cout,
                st::NODE_ID_STR_FORMAT_BACKEND_STR, nullptr, &node_id );

            std::cout << "\r\n";
        }

        std::cout << std::endl;
        return 0;
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

    st::OclContext ctx( node_id );

    a2str << ::NS(PATH_TO_BASE_DIR) << "sixtracklib/opencl/kernels/";
    std::string const ocl_kernel_base_dir = a2str.str();
    std::string const remap_program_name = "cobj_flat_buffer_remap.cl";

    a2str << remap_program_name;
    std::string const path_remap_program = a2str.str();
    a2str.str( "" );

    st::OclRtcProgramItem remap_program;
    remap_program.set_compile_flags( flags );
    status  = remap_program.create_from_source_file( ctx, path_remap_program );
    status |= remap_program.build( ctx, remap_program_name );

    st::OclKernelItem remap_kernel;
    a2str  << SIXTRL_C99_NAMESPACE_STR << "CObjFlatBuffer_remap_opencl";
    std::string const remap_kernel_name = a2str.str();
    a2str.str( "" );

    status |= remap_kernel.init( remap_program, 0, remap_kernel_name );
    if( status != st::STATUS_SUCCESS )
    {
        std::cout << "unable to build remap program & kernel" << std::endl;
        return 0;
    }

    std::string const track_progam_name =
        "particle_track_until_cobj_flat_buffer.cl";
    a2str << ocl_kernel_base_dir << track_program_name;
    std::string const path_track_program = a2str.str();
    a2str.str( "" );








//     st::CBuffer pbuffer( path_to_particle_data );
//     st::CBuffer lattice( path_to_lattice_data );



}
