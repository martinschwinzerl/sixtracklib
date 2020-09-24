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

    std::ostringstream a2str;
    
    st_size_t const NUM_REPETITIONS = ( argc > 3 ) 
        ? std::stoull( argv[ 3 ] ) : uint64_t{ 10 };
        
    int64_t const UNTIL_TURN = ( argc > 2 )
        ? std::stoll( argv[ 2 ] ) : int64_t{ 20 };
        
    std::string const device_id = ( argc > 1 )
        ? std::string{ argv[ 1 ] } : std::string{ "0.0" };
    
    std::vector< double > track_times( NUM_REPETITIONS, 0.0 );
    
    for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_REPETITIONS ; ++ii )
    {        
        /* load data from dumps: */        
        a2str << ::NS(PATH_TO_BASE_DIR) 
              << "examples/cxx/data/AMD_STL_profiling_FODOlattice.bin";
    
        st::Buffer lattice( a2str.str() );
        a2str.str( "" );
          
        a2str << ::NS(PATH_TO_BASE_DIR)
              << "examples/cxx/data/AMD_STL_profiling_particles.bin";
          
        st::Buffer pbuffer( a2str.str() );
        a2str.str( "" );
    
        st::TrackJobCl job( device_id.c_str(), pbuffer, lattice );
        
        std::cout << "ii = " << ii;
        
        auto start_tracking = std::chrono::system_clock::now();
        st::track( job, UNTIL_TURN );
        auto end_tracking = std::chrono::system_clock::now();
        
        double const elapsed_seconds = std::chrono::duration_cast<
            std::chrono::duration< double > >(
                end_tracking - start_tracking ).count();
                        
        std::cout << " | elapsed seconds: " << elapsed_seconds << std::endl;
        
        track_times[ ii ] = elapsed_seconds;
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
