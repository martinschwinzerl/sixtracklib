#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/internal/default_compile_options.h"
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/be_drift/be_drift.h"
    #include "sixtracklib/common/be_drift/track.h"
    #include "sixtracklib/common/be_multipole/be_multipole.h"
    #include "sixtracklib/common/be_multipole/track.h"
    #include "sixtracklib/common/be_cavity/be_cavity.h"
    #include "sixtracklib/common/be_cavity/track.h"
    #include "sixtracklib/common/be_limit/track.h"    
    #include "benchmark/single_particle.h"
    #include "benchmark/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

__kernel void NS(DriftExact_track_opencl)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer_begin, 
    SIXTRL_INT64_T const pset_index,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT belems_buffer_begin,
    SIXTRL_INT64_T const belem_index, 
    SIXTRL_UINT64_T const slot_size ) SIXTRL_NOEXCEPT {
    
    typedef NS(particle_num_elements_t) nelem_t;
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* pset = 
        NS(Particles_managed_buffer_get_particles)( 
            pbuffer_begin, pset_index, slot_size );
        
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact) const* drift = 
    NS(DriftExact_const_from_managed_buffer)( 
        belems_buffer_begin, belem_index, slot_size );
        
    nelem_t const num_particles = NS(Particles_get_num_of_particles)( pset );
    nelem_t pidx = ( nelem_t )get_global_id( 0 );
    
    SIXTRL_ASSERT( pset  != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( drift != SIXTRL_NULLPTR );
    
    for( ; pidx < num_particles ; pidx += get_global_size( 0 ) )
    {
        if( NS(Particles_is_not_lost_value)( pset, pidx ) )
        {
            NS(Track_particle_drift_exact)( pset, pidx, drift );
        }
    }
}
    
__kernel void NS(Multipole_track_opencl)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer_begin, 
    SIXTRL_INT64_T const pset_index,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT belems_buffer_begin,
    SIXTRL_INT64_T const belem_index, 
    SIXTRL_UINT64_T const slot_size ) SIXTRL_NOEXCEPT {
    
    typedef NS(particle_num_elements_t) nelem_t;
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* pset = 
        NS(Particles_managed_buffer_get_particles)( 
            pbuffer_begin, pset_index, slot_size );
        
    SIXTRL_BE_ARGPTR_DEC NS(Multipole) const* mp = 
    NS(Multipole_const_from_managed_buffer)( 
        belems_buffer_begin, belem_index, slot_size );
        
    nelem_t const num_particles = NS(Particles_get_num_of_particles)( pset );
    nelem_t pidx = ( nelem_t )get_global_id( 0 );
    
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    
    for( ; pidx < num_particles ; pidx += get_global_size( 0 ) )
    {
        if( NS(Particles_is_not_lost_value)( pset, pidx ) )
        {
            NS(Track_particle_multipole)( pset, pidx, mp );
        }
    }
}

__kernel void NS(Particles_limit_global_opencl)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer_begin, 
    SIXTRL_INT64_T const pset_index,    
    SIXTRL_UINT64_T const slot_size ) SIXTRL_NOEXCEPT {
    
    typedef NS(particle_num_elements_t) nelem_t;
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* pset = 
        NS(Particles_managed_buffer_get_particles)( 
            pbuffer_begin, pset_index, slot_size );
        
    nelem_t const num_particles = NS(Particles_get_num_of_particles)( pset );
    nelem_t pidx = ( nelem_t )get_global_id( 0 );
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    
    for( ; pidx < num_particles ; pidx += get_global_size( 0 ) )
    {
        NS(Track_particle_limit_global)( pset, pidx );
    }
}

__kernel void NS(Cavity_track_opencl)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer_begin, 
    SIXTRL_INT64_T const pset_index,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT belems_buffer_begin,
    SIXTRL_INT64_T const belem_index, 
    SIXTRL_UINT64_T const slot_size ) SIXTRL_NOEXCEPT {
    
    typedef NS(particle_num_elements_t) nelem_t;
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* pset = 
        NS(Particles_managed_buffer_get_particles)( 
            pbuffer_begin, pset_index, slot_size );
        
    SIXTRL_BE_ARGPTR_DEC NS(Cavity) const* cavity = 
    NS(Cavity_const_from_managed_buffer)( belems_buffer_begin, belem_index, slot_size );
        
    nelem_t const num_particles = NS(Particles_get_num_of_particles)( pset );
    nelem_t pidx = ( nelem_t )get_global_id( 0 );
    
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( cavity != SIXTRL_NULLPTR );
    
    for( ; pidx < num_particles ; pidx += get_global_size( 0 ) )
    {
        if( NS(Particles_is_not_lost_value)( pset, pidx ) )
        {
            NS(Track_particle_cavity)( pset, pidx, cavity );
        }
    }
}

__kernel void NS(Particles_increment_at_element_id_opencl)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer_begin, 
    SIXTRL_INT64_T const pset_index,
    SIXTRL_UINT64_T const slot_size ) SIXTRL_NOEXCEPT {
    
    typedef NS(particle_num_elements_t) nelem_t;
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* pset = 
        NS(Particles_managed_buffer_get_particles)( 
            pbuffer_begin, pset_index, slot_size );
        
    nelem_t const num_particles = NS(Particles_get_num_of_particles)( pset );
    nelem_t pidx = ( nelem_t )get_global_id( 0 );
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    
    for( ; pidx < num_particles ; pidx += get_global_size( 0 ) )
    {
        if( NS(Particles_is_not_lost_value)( pset, pidx ) )
        {
            NS(Particles_increment_at_element_id_value)( pset, pidx );
        }
    }
}

__kernel void NS(Particles_end_of_turn_opencl)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer_begin, 
    SIXTRL_INT64_T const pset_index,
    SIXTRL_UINT64_T const slot_size ) SIXTRL_NOEXCEPT {
    
    typedef NS(particle_num_elements_t) nelem_t;
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* pset = 
        NS(Particles_managed_buffer_get_particles)( 
            pbuffer_begin, pset_index, slot_size );
        
    nelem_t const num_particles = NS(Particles_get_num_of_particles)( pset );
    nelem_t pidx = ( nelem_t )get_global_id( 0 );
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    
    for( ; pidx < num_particles ; pidx += get_global_size( 0 ) )
    {
        if( NS(Particles_is_not_lost_value)( pset, pidx ) )
        {
            NS(Particles_set_at_element_id_value)( pset, pidx, 0 );
            NS(Particles_increment_at_turn_value)( pset, pidx );
            NS(Particles_set_s_value)( pset, pidx, ( SIXTRL_REAL_T )0 );
        }
    }
}
