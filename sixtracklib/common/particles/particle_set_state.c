#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_set_state.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState) const*
NS(ParticleSetState_const_from_buffer)(
    SIXTRL_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index )
{
    return NS(ParticleSetState_const_from_obj_index)(
        NS(Buffer_get_const_object)( buffer, index ) );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_from_buffer)(
    SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index )
{
    return NS(ParticleSetState_from_obj_index)( NS(Buffer_get_object)(
        buffer, index ) );
}

/* ------------------------------------------------------------------------- */

bool NS(ParticleSetState_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(interpol_1d_int_t) const num_values,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs )
{
    NS(ParticleSetState) pset_state;
    NS(ParticleSetState_preset)( &pset_state );

    SIXTRL_ASSERT( ( NS(buffer_size_t) )0u ==
        NS(ParticleSetState_num_dataptrs)( &pset_state ) );
    ( void )ptr_requ_dataptrs;

    return NS(Buffer_can_add_trivial_object)( buffer, sizeof( pset_state ),
        ptr_requ_objects, ptr_requ_slots );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* NS(ParticleSetState_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(interpol_1d_int_t) const num_values )
{
    NS(ParticleSetState) pset_state;
    NS(ParticleSetState_preset)( &pset_state );

    SIXTRL_ASSERT( ( NS(buffer_size_t) )0u ==
        NS(ParticleSetState_num_dataptrs)( &pset_state ) );

    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* )( uintptr_t
        )NS(Object_get_begin_addr)( NS(Buffer_add_trivial_object)( buffer,
            &pset_state, sizeof( pset_state ),
                NS(ParticleSetState_type_id)( &pset_state ) ) );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* NS(ParticleSetState_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(particle_num_elements_t) const num_particles,
    NS(particle_num_elements_t) const num_lost_particles,
    NS(particle_index_t) const min_particle_id,
    NS(particle_index_t) const max_particle_id,
    NS(particle_index_t) const min_at_element,
    NS(particle_index_t) const max_at_element,
    NS(particle_index_t) const min_at_turn,
    NS(particle_index_t) const max_at_turn )
{
    NS(ParticleSetState) pset_state;
    NS(ParticleSetState_preset)( &pset_state );

    NS(ParticleSetState_set_num_particles)( &pset_state, num_particles );
    NS(ParticleSetState_set_num_lost_particles)(
        &pset_state, num_lost_particles );

    NS(ParticleSetState_set_min_particle_id)( &pset_state, min_particle_id );
    NS(ParticleSetState_set_max_particle_id)( &pset_state, max_particle_id );
    NS(ParticleSetState_set_min_at_element)( &pset_state, min_at_element );
    NS(ParticleSetState_set_max_at_element)( &pset_state, max_at_element );
    NS(ParticleSetState_set_min_at_turn)( &pset_state, min_at_turn );
    NS(ParticleSetState_set_max_at_turn)( &pset_state, max_at_turn );

    SIXTRL_ASSERT( ( NS(buffer_size_t) )0u ==
        NS(ParticleSetState_num_dataptrs)( &pset_state ) );

    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* )( uintptr_t
        )NS(Object_get_begin_addr)( NS(Buffer_add_trivial_object)( buffer,
            &pset_state, sizeof( pset_state ),
                NS(ParticleSetState_type_id)( &pset_state ) ) );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* NS(ParticleSetState_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC const NS(ParticleSetState) *const
        SIXTRL_RESTRICT orig )
{
    SIXTRL_ASSERT( ( NS(buffer_size_t) )0u ==
        NS(ParticleSetState_num_dataptrs)( pset_state ) );

    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* )( uintptr_t
        )NS(Object_get_begin_addr)( NS(Buffer_add_trivial_object)( buffer,
            pset_state, sizeof( NS(ParticleSetState) ),
                NS(ParticleSetState_type_id)( pset_state ) ) );
}
