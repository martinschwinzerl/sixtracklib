#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/kernels/default_defines.h"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/track/track.h"
    #include "sixtracklib/common/track/track_config.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

__kernel void NS(Track_until_particle_cobj_flat_buffer_opencl)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    SIXTRL_UINT64_TYPE const pset_index,
    NS(particle_index_type) const line_start_at_element,
    NS(particle_index_type) const until_turn,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT lattice_buffer,
    SIXTRL_UINT64_TYPE const end_of_turn_marker_index,
    SIXTRL_UINT64_TYPE const line_start_index,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT config_buffer,
    SIXTRL_UINT64_TYPE const track_config_index,
    SIXTRL_UINT64_TYPE const slot_size )
{
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* pset =
        NS(Particles_from_cobj_flat_buffer)( pbuffer, pset_index, slot_size );

    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) p;
    NS(Particle_clear_before_copy_from_pset)( &p );

    NS(particles_num_type) const STRIDE = (
        NS(particles_num_type) )get_global_size( 0 );

    NS(particles_num_type) const NPARTICLES =
        NS(Particles_num_particles)( pset );

    NS(particles_num_type) idx = ( NS(particles_num_type) )get_global_id( 0 );

    for( ; idx < NPARTICLES ; idx += STRIDE )
    {
        NS(Particles_to_single_particle)( pset, idx, &p );
        NS(Track_particle_until_turn_eot_marker_cobj)( &p, until_turn,
            NS(CObjFlatBuffer_const_indices_begin)( lattice_buffer, slot_size ),
                end_of_turn_marker_index, line_start_index, line_start_at_element,
                    NS(TrackConfig_const_from_cobj_flat_buffer_save)(
                        config_buffer, track_config_index, slot_size ) );
        NS(Particles_from_single_particle)( pset, idx, &p );
    }
}
