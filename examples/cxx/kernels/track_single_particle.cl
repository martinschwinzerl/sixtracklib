#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/internal/default_compile_options.h"
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/particles.h"
    #include "benchmark/single_particle.h"
    #include "benchmark/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

__kernel void NS(Track_single_particle_until_turn_opencl)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* pbuffer_begin,
    SIXTRL_INT64_T const pset_index,  
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* elements_buffer_begin,
    SIXTRL_INT64_T const until_turn, 
    SIXTRL_UINT64_T const slot_size ) {
    
    typedef NS(particle_num_elements_t) nelements_t;
    nelements_t part_idx = ( nelements_t )get_global_id( 0 );
    nelements_t const num_particles = NS(Particles_get_num_of_particles)(
        NS(Particles_managed_buffer_get_particles)( 
            pbuffer_begin, pset_index, slot_size ) );
    
    for( ; part_idx < num_particles ; part_idx += get_global_size( 0 ) )
    {        
        NS(Track_single_particle_until_turn_impl)( pbuffer_begin, pset_index, 
            part_idx, elements_buffer_begin, until_turn, slot_size );
    }
}
