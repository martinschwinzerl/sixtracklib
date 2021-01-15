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
    using st_size_t = st::Buffer::size_type;

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

        st::TrackJobCl job( device_id.c_str(), pbuffer, lattice );

        std::cout << "ii = " << std::setw( 3 ) << ii;

        auto start_tracking = std::chrono::system_clock::now();
        st::track( job, TRACK_UNTIL_TURN );
        auto end_tracking = std::chrono::system_clock::now();

        job.collectParticles();

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
