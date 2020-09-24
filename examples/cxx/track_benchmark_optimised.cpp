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

    std::ostringstream a2str;
        
    st_size_t const NUM_REPETITIONS = ( argc > 3 ) 
        ? std::stoull( argv[ 3 ] ) : uint64_t{ 10 };
        
    int64_t const UNTIL_TURN = ( argc > 2 )
        ? std::stoll( argv[ 2 ] ) : int64_t{ 20 };
        
    int64_t const PSET_INDEX = int64_t{ 0 };    
    
    std::string const device_id = ( argc > 1 )
        ? std::string{ argv[ 1 ] } : std::string{ "0.0" };
    
    std::unique_ptr< context_t > ptr_ctx( new context_t );
    ptr_ctx->selectNode( device_id.c_str() );
    
    /* ====================================================================== */
    /* prepare kernel: */
    
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
    
        st::Particles const* pset = pbuffer.get< st::Particles >( 0 );
        
        /* prepare arguments */
        st::ClArgument pbuffer_arg( pbuffer, ptr_ctx.get() );
        st::ClArgument lattice_arg( lattice, ptr_ctx.get() );
        
        uint64_t const SLOT_SIZE = pbuffer.getSlotSize();

        std::cout << "ii = " << std::setw( 3 ) << ii;
        
        ptr_ctx->assignKernelArgument( kernel_id, 0, pbuffer_arg );
        ptr_ctx->assignKernelArgumentValue( kernel_id, 1, PSET_INDEX );
        ptr_ctx->assignKernelArgument( kernel_id, 2, lattice_arg );
        ptr_ctx->assignKernelArgumentValue( kernel_id, 3, UNTIL_TURN );
        ptr_ctx->assignKernelArgumentValue( kernel_id, 4, SLOT_SIZE );
        
        auto start_tracking = std::chrono::system_clock::now();
        bool success = ptr_ctx->runKernel( kernel_id, pset->getNumParticles() );
        auto end_tracking = std::chrono::system_clock::now();
        
        if( !success ) break;
        
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
