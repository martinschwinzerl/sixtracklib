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

namespace SIXTRL_CXX_NAMESPACE
{
    double Track_particles_until_belem_kernels(
        SIXTRL_CXX_NAMESPACE::ClContextBase* SIXTRL_RESTRICT ptr_ctx,
        SIXTRL_CXX_NAMESPACE::Buffer& SIXTRL_RESTRICT_REF pbuffer, 
        SIXTRL_CXX_NAMESPACE::Buffer& SIXTRL_RESTRICT_REF belements_buffer,
        std::vector< ::NS(object_type_id_t) > const& SIXTRL_RESTRICT_REF type_ids,
        uint64_t const until_turn, 
        SIXTRL_CXX_NAMESPACE::arch_kernel_id_t const drift_kernel_id,
        SIXTRL_CXX_NAMESPACE::arch_kernel_id_t const multipole_kernel_id,
        SIXTRL_CXX_NAMESPACE::arch_kernel_id_t const cavity_kernel_id,
        SIXTRL_CXX_NAMESPACE::arch_kernel_id_t const global_limit_kernel_id, 
        SIXTRL_CXX_NAMESPACE::arch_kernel_id_t const inc_elem_kernel_id, 
        SIXTRL_CXX_NAMESPACE::arch_kernel_id_t const end_of_turn_kernel_id );
    
}

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
        
    std::string const device_id = ( argc > 1 )
        ? std::string{ argv[ 1 ] } : std::string{ "0.0" };
    
    std::unique_ptr< context_t > ptr_ctx( new context_t );
    ptr_ctx->selectNode( device_id.c_str() );
    
    /* ====================================================================== */
    /* prepare kernels: */
    
    a2str << ::NS(PATH_TO_BASE_DIR) 
          << "examples/cxx/kernels/track_beam_elements.cl";
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
        
    kernel_id_t const drift_kernel_id = ptr_ctx->enableKernel( 
        std::string{ "st_DriftExact_track_opencl" }, program_id );
    SIXTRL_ASSERT( drift_kernel_id >= 0 );
    
    kernel_id_t const multipole_kernel_id = ptr_ctx->enableKernel( 
        std::string{ "st_Multipole_track_opencl" }, program_id );
    SIXTRL_ASSERT( multipole_kernel_id >= 0 );
    
    kernel_id_t const cavity_kernel_id = ptr_ctx->enableKernel( 
        std::string{ "st_Cavity_track_opencl" }, program_id );
    SIXTRL_ASSERT( cavity_kernel_id >= 0 );
    
    kernel_id_t const global_limit_kernel_id = ptr_ctx->enableKernel(
        std::string{ "st_Particles_limit_global_opencl" }, program_id );
    SIXTRL_ASSERT( global_limit_kernel_id >= 0 );
    
    kernel_id_t const inc_elem_kernel_id = ptr_ctx->enableKernel(
        std::string{ "st_Particles_increment_at_element_id_opencl" }, 
            program_id );
    SIXTRL_ASSERT( inc_elem_kernel_id >= 0 );
    
    kernel_id_t const end_of_turn_kernel_id = ptr_ctx->enableKernel(
        std::string{ "st_Particles_end_of_turn_opencl" }, program_id );
    SIXTRL_ASSERT( end_of_turn_kernel_id >= 0 );
    
    std::vector< double > track_times( NUM_REPETITIONS, 0.0 );
    
    /* load data from dumps: */        
    a2str << ::NS(PATH_TO_BASE_DIR) 
            << "examples/cxx/data/AMD_STL_profiling_FODOlattice.bin";
    st::Buffer lattice( a2str.str() );
        
    st_size_t const nelems = lattice.getNumObjects();
    std::vector< ::NS(object_type_id_t) > type_ids( 
        nelems, ::NS(OBJECT_TYPE_NONE) );
    
    for( st_size_t ii = st_size_t{ 0 } ; ii < nelems ; ++ii )
    {
        type_ids[ ii ] = ::NS(Object_get_type_id)( lattice[ ii ] );
    }        
    
    a2str.str( "" );
    a2str << ::NS(PATH_TO_BASE_DIR)
          << "examples/cxx/data/AMD_STL_profiling_particles.bin";
    
    for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_REPETITIONS ; ++ii )
    {        
        /* load data from dumps: */
                  
        st::Buffer pbuffer( a2str.str() );
        
        std::cout << "ii = " << std::setw( 3 ) << ii;
        double const elapsed_seconds = st::Track_particles_until_belem_kernels(
            ptr_ctx.get(), pbuffer, lattice, type_ids, UNTIL_TURN, 
            drift_kernel_id, multipole_kernel_id, cavity_kernel_id, 
            global_limit_kernel_id, inc_elem_kernel_id, end_of_turn_kernel_id );
        
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

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE double Track_particles_until_belem_kernels(
        SIXTRL_CXX_NAMESPACE::ClContextBase* SIXTRL_RESTRICT ptr_ctx,
        SIXTRL_CXX_NAMESPACE::Buffer& SIXTRL_RESTRICT_REF pbuffer, 
        SIXTRL_CXX_NAMESPACE::Buffer& SIXTRL_RESTRICT_REF belements_buffer, 
        std::vector< ::NS(object_type_id_t) > const& SIXTRL_RESTRICT_REF type_ids,
        uint64_t const until_turn, 
        SIXTRL_CXX_NAMESPACE::arch_kernel_id_t const drift_kernel_id,
        SIXTRL_CXX_NAMESPACE::arch_kernel_id_t const multipole_kernel_id,
        SIXTRL_CXX_NAMESPACE::arch_kernel_id_t const cavity_kernel_id,
        SIXTRL_CXX_NAMESPACE::arch_kernel_id_t const global_limit_kernel_id, 
        SIXTRL_CXX_NAMESPACE::arch_kernel_id_t const inc_elem_kernel_id, 
        SIXTRL_CXX_NAMESPACE::arch_kernel_id_t const end_of_turn_kernel_id ) {
        
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef ::NS(particle_index_t) index_t;
        typedef ::NS(particle_num_elements_t) npart_t;
        
        SIXTRL_ASSERT( ptr_ctx != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( type_ids.size() == belements_buffer.getNumObjects() );
        
        st::Particles const* pset = pbuffer.get< st::Particles >( 0 );
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        npart_t const num_particles = pset->getNumParticles();
        
        /* prepare arguments */
        st::ClArgument pbuffer_arg( pbuffer, ptr_ctx );
        st::ClArgument lattice_arg( belements_buffer, ptr_ctx );
        
        index_t const PSET_INDEX = index_t{ 0 };    
        uint64_t const SLOT_SIZE = pbuffer.getSlotSize();        
        
        ptr_ctx->assignKernelArgument( drift_kernel_id, 0, pbuffer_arg );
        ptr_ctx->assignKernelArgumentValue( drift_kernel_id, 1, PSET_INDEX );
        ptr_ctx->assignKernelArgument( drift_kernel_id, 2, lattice_arg );
        ptr_ctx->assignKernelArgumentValue( drift_kernel_id, 4, SLOT_SIZE );
        
        ptr_ctx->assignKernelArgument( multipole_kernel_id, 0, pbuffer_arg );
        ptr_ctx->assignKernelArgumentValue( multipole_kernel_id, 1, PSET_INDEX );
        ptr_ctx->assignKernelArgument( multipole_kernel_id, 2, lattice_arg );
        ptr_ctx->assignKernelArgumentValue( multipole_kernel_id, 4, SLOT_SIZE );
        
        ptr_ctx->assignKernelArgument( cavity_kernel_id, 0, pbuffer_arg );
        ptr_ctx->assignKernelArgumentValue( cavity_kernel_id, 1, PSET_INDEX );
        ptr_ctx->assignKernelArgument( cavity_kernel_id, 2, lattice_arg );
        ptr_ctx->assignKernelArgumentValue( cavity_kernel_id, 4, SLOT_SIZE );
        
        ptr_ctx->assignKernelArgument( global_limit_kernel_id, 0, pbuffer_arg );
        ptr_ctx->assignKernelArgumentValue( global_limit_kernel_id, 1, PSET_INDEX );
        ptr_ctx->assignKernelArgumentValue( global_limit_kernel_id, 2, SLOT_SIZE );
        
        ptr_ctx->assignKernelArgument( inc_elem_kernel_id, 0, pbuffer_arg );
        ptr_ctx->assignKernelArgumentValue( inc_elem_kernel_id, 1, PSET_INDEX );
        ptr_ctx->assignKernelArgumentValue( inc_elem_kernel_id, 2, SLOT_SIZE );
        
        ptr_ctx->assignKernelArgument( end_of_turn_kernel_id, 0, pbuffer_arg );
        ptr_ctx->assignKernelArgumentValue( end_of_turn_kernel_id, 1, PSET_INDEX );
        ptr_ctx->assignKernelArgumentValue( end_of_turn_kernel_id, 2, SLOT_SIZE );
        
        auto start_tracking = std::chrono::system_clock::now();
        
        for( uint64_t ii = uint64_t{ 0 } ; ii < until_turn ; ++ii )
        {
            st_size_t const num_elems = type_ids.size();
            std::cout << "at_turn = " << ii << std::endl;
            
            for( st_size_t jj = st_size_t{ 0 }; jj < num_elems ; ++jj )
            {
                ::NS(object_type_id_t) const type_id = type_ids[ jj ];
                
                switch( type_id )
                {
                    case ::NS(OBJECT_TYPE_DRIFT_EXACT):
                    {
                        ptr_ctx->assignKernelArgumentValue( 
                            drift_kernel_id, 3, jj );
                        ptr_ctx->runKernel( drift_kernel_id, num_particles );
                        ptr_ctx->runKernel( global_limit_kernel_id, num_particles );
                        ptr_ctx->runKernel( inc_elem_kernel_id, num_particles );
                        break;
                    }
                    
                    case ::NS(OBJECT_TYPE_MULTIPOLE):
                    {
                        ptr_ctx->assignKernelArgumentValue( 
                            multipole_kernel_id, 3, jj );
                        ptr_ctx->runKernel( multipole_kernel_id, num_particles );
                        ptr_ctx->runKernel( inc_elem_kernel_id, num_particles );
                        break;
                    }
                    
                    case ::NS(OBJECT_TYPE_CAVITY):
                    {
                        ptr_ctx->assignKernelArgumentValue( 
                            cavity_kernel_id, 3, jj );
                        ptr_ctx->runKernel( cavity_kernel_id, num_particles );
                        ptr_ctx->runKernel( inc_elem_kernel_id, num_particles );
                        break;
                    }
                };
            }
            
            ptr_ctx->runKernel( end_of_turn_kernel_id, num_particles );
        }
        
        auto finish_tracking = std::chrono::system_clock::now();        
        return std::chrono::duration_cast< std::chrono::duration< double > >(
                finish_tracking - start_tracking ).count();
    }
}
