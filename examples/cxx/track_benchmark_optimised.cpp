#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

#include "sixtracklib/testlib.h"
#include "sixtracklib/sixtracklib.hpp"

int main( int argc, char* argv[] )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using context_t    = st::ClContextBase;
    using program_id_t = context_t::program_id_t;
    using kernel_id_t  = context_t::kernel_id_t;
    using st_size_t    = st::Buffer::size_type;

    st_size_t NUM_REPETITIONS = 3u;
    st_size_t NUM_PARTICLES = 50 * 1024;
    st_size_t TRACK_UNTIL_TURN = 1000;
    std::string device_id = std::string{ "0.0" };
    std::string path_to_lattice_data  = std::string{};
    std::string path_to_particle_data = std::string{};
    std::string path_to_output_data   = std::string{};

    if( argc >= 2 )
    {
        device_id = std::string{ argv[ 1 ] };

        if( argc >= 3 )
        {
            NUM_PARTICLES = std::stoi( argv[ 2 ] );

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
    else
    {
        std::cout << "Usage : " << argv[ 0 ] << " [DEVICE_ID]"
                  << " [NUM_PARTICLES] [TRACK_UNTIL_TURN]"
                  << " [PATH_TO_PARTICLE_DATA] [PATH_TO_LATTICE_DATA]"
                  << " [PATH_TO_OUTPUT_DATA]\r\n"
                  << std::endl;
    }

    std::ostringstream a2str;

    if( path_to_particle_data.empty() )
    {
        a2str << ::NS(PATH_TO_BASE_DIR)
              << "examples/cxx/data/AMD_STL_profiling_particles.bin";
        path_to_particle_data = a2str.str();
        a2str.str( "" );
    }

    if( path_to_lattice_data.empty() )
    {
        a2str << ::NS(PATH_TO_BASE_DIR)
              << "examples/cxx/data/AMD_STL_profiling_FODOlattice.bin";
        path_to_lattice_data = a2str.str();
        a2str.str( "" );
    }

    /* ====================================================================== */
    /* prepare kernel: */

    std::unique_ptr< context_t > ptr_ctx( new context_t );
    ptr_ctx->selectNode( device_id.c_str() );

    a2str << ::NS(PATH_TO_BASE_DIR)
          << "examples/cxx/kernels/track_single_particle.cl";
    std::string const path_to_program( a2str.str() );
    a2str.str( "" );

    a2str << "-D_GPUCODE=1"
          << " -I" << ::NS(PATH_TO_BASE_DIR)
          << " -I" << ::NS(PATH_TO_BASE_DIR) << "examples/cxx";

    std::string const compile_options( a2str.str() );
    a2str.str( "" );

    program_id_t const program_id = ptr_ctx->addProgramFile(
        path_to_program, compile_options );

    SIXTRL_ASSERT( program_id >= 0 );

    std::string kernel_name( "st_Track_single_particle_until_turn_opencl" );
    kernel_id_t const kernel_id = ptr_ctx->enableKernel(
        kernel_name, program_id );

    SIXTRL_ASSERT( kernel_id >= 0 );
    std::vector< double > track_times( NUM_REPETITIONS, 0.0 );
    track_times.clear();

    for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_REPETITIONS ; ++ii )
    {
        st::Buffer lattice( path_to_lattice_data );
        st::Buffer pbuffer_orig( path_to_particle_data );
        st::Particles* porig = pbuffer_orig.get< st::Particles >( 0 );
        st_size_t const norig = porig->getNumParticles();

        st::Buffer pbuffer;
        st::Particles* pset = pbuffer.createNew< st::Particles >( NUM_PARTICLES );

        for( st_size_t kk = 0u ; kk < NUM_PARTICLES ; ++kk )
        {
            st_size_t const jj = kk % norig;
            pset->copySingle( porig, jj, kk );
            pset->setParticleIdValue( kk, kk );
        }

        /* prepare arguments */
        st::ClArgument pbuffer_arg( pbuffer, ptr_ctx.get() );
        st::ClArgument lattice_arg( lattice, ptr_ctx.get() );

        uint64_t const SLOT_SIZE = pbuffer.getSlotSize();
        int64_t const UNTIL_TURN = TRACK_UNTIL_TURN;
        int64_t const PSET_INDEX = int64_t{ 0 };

        std::cout << "ii = " << std::setw( 3 ) << ii;

        ptr_ctx->assignKernelArgument( kernel_id, 0, pbuffer_arg );
        ptr_ctx->assignKernelArgumentValue( kernel_id, 1, PSET_INDEX );
        ptr_ctx->assignKernelArgument( kernel_id, 2, lattice_arg );
        ptr_ctx->assignKernelArgumentValue( kernel_id, 3, UNTIL_TURN );
        ptr_ctx->assignKernelArgumentValue( kernel_id, 4, SLOT_SIZE );

        auto start_tracking = std::chrono::system_clock::now();
        bool success = ptr_ctx->runKernel( kernel_id, NUM_PARTICLES );
        auto end_tracking = std::chrono::system_clock::now();

        pbuffer_arg.read( pbuffer );

        if( !success ) break;

        double const elapsed_seconds = std::chrono::duration_cast<
            std::chrono::duration< double > >(
                end_tracking - start_tracking ).count();

        std::cout << " | elapsed seconds: " << elapsed_seconds << std::endl;

        track_times.push_back( elapsed_seconds );


        if( track_times.size() == NUM_REPETITIONS )
        {
            pset = pbuffer.get< st::Particles >( 0 );

            /* ************************************************************** */
            /* Verify tracking results */

            uint64_t num_active_particles = 0u;
            uint64_t num_lost_particles = 0u;

            for( st_size_t kk = 0u ; kk < NUM_PARTICLES ; ++kk )
            {
                if( ( pset->getStateValue( kk ) == 1 ) &&
                    ( pset->getAtTurnValue( kk ) ==
                      static_cast< int64_t >( TRACK_UNTIL_TURN ) ) )
                {
                    ++num_active_particles;
                }
                else if( ( pset->getStateValue( kk ) != 1 ) &&
                    ( pset->getAtTurnValue( kk ) <
                      static_cast< int64_t >( TRACK_UNTIL_TURN ) ) )
                {
                    ++num_lost_particles;
                }
                else
                {
                    std::cerr << "illegal particle id = "
                              << pset->getParticleIdValue( kk )
                              << ", at_turn = " << pset->getAtTurnValue( kk )
                              << ", at_element = " << pset->getAtElementIdValue( kk )
                              << ", state = " << pset->getStateValue( kk ) << std::endl;
                }
            }

            std::cout << "-------------------------------------------------------\r\n"
                    << "num lost particles    : " << num_lost_particles   << "\r\n"
                    << "num active particles  : " << num_active_particles << "\r\n"
                    << std::endl;

            if( !path_to_output_data.empty() )
            {
                pbuffer.writeToFile( path_to_output_data );
            }
        }
    }

    std::sort( track_times.begin(), track_times.end() );
    std::cout << "\r\n"
              << "min tracking time    : " << track_times[ 0 ] << "\r\n"
              << "max tracking time    : " << track_times.back() << "\r\n"
              << "median tracking time : " << track_times[ NUM_REPETITIONS / 2 ]
              << "\r\n"
              << std::endl;
    return 0;
}
