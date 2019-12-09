#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_STATE_C99_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_STATE_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

typedef struct NS(ParticleSetState)
{
    NS(particle_num_elements_t) num_particles       SIXTRL_ALIGN( 8 );
    NS(particle_num_elements_t) num_lost_particles  SIXTRL_ALIGN( 8 );

    NS(particle_index_t)        min_particle_id     SIXTRL_ALIGN( 8 );
    NS(particle_index_t)        max_particle_id     SIXTRL_ALIGN( 8 );
    NS(particle_index_t)        min_at_element      SIXTRL_ALIGN( 8 );
    NS(particle_index_t)        max_at_element      SIXTRL_ALIGN( 8 );
    NS(particle_index_t)        min_at_turn         SIXTRL_ALIGN( 8 );
    NS(particle_index_t)        max_at_turn         SIXTRL_ALIGN( 8 );
}
NS(ParticleSetState);

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_preset)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_clear)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(object_type_id_t)
NS(ParticleSetState_type_id)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(ParticleSetState) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetState_num_dataptrs)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(ParticleSetState) *const SIXTRL_RESTRICT interpol );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetState_num_slots)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(ParticleSetState) *const SIXTRL_RESTRICT interpol,
    NS(buffer_size_t) const slot_size );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_num_elements_t)
NS(ParticleSetState_num_particles)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT states );

SIXTRL_STATIC SIXTRL_FN NS(particle_num_elements_t)
NS(ParticleSetState_num_lost_particles)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT states );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t)
NS(ParticleSetState_min_particle_id)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT states );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t)
NS(ParticleSetState_max_particle_id)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT states );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t)
NS(ParticleSetState_min_at_element)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT states );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t)
NS(ParticleSetState_max_at_element)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT states );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t) NS(ParticleSetState_min_at_turn)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState) *const
        SIXTRL_RESTRICT states );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t) NS(ParticleSetState_max_at_turn)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState) *const
        SIXTRL_RESTRICT states );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_num_particles)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states,
    NS(particle_num_elements_t) const num_particles );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_num_lost_particles)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states,
    NS(particle_num_elements_t) const num_lost_particles );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_min_particle_id)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states,
    NS(particle_index_t) const min_particle_id );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_max_particle_id)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states,
    NS(particle_index_t) const max_particle_id );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_min_at_element)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states,
    NS(particle_index_t) const min_at_element );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_max_at_element)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states,
    NS(particle_index_t) const max_at_element );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_min_at_turn)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states,
    NS(particle_index_t) const min_at_turn );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_max_at_turn)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states,
    NS(particle_index_t) const max_at_turn );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSetState_prepare)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSetState_init_from_particle_set)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT particles );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSetState_update_from_particle_set)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT particles );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSetState_merge)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT states,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState)
        *const SIXTRL_RESTRICT other );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState) const*
NS(ParticleSetState_const_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_from_obj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    NS(Object)* SIXTRL_RESTRICT obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState) const*
NS(ParticleSetState_const_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSetState_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState)
        *const SIXTRL_RESTRICT interpol, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSetState_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState)
        *const SIXTRL_RESTRICT interpol, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSetState_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState)
        *const SIXTRL_RESTRICT interpol );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState) const*
NS(ParticleSetState_const_from_buffer)(
    SIXTRL_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_from_buffer)(
    SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ParticleSetState_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(interpol_1d_int_t) const num_values,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(interpol_1d_int_t) const num_values );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(interpol_1d_real_t) const t0, NS(interpol_1d_real_t) const dt,
    NS(interpol_1d_int_t) const num_values,
    NS(buffer_addr_t) const values_begin_addr );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC const NS(ParticleSetState) *const
        SIXTRL_RESTRICT interpol );

#endif /* defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSetState_copy)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState)
        *const SIXTRL_RESTRICT source );

/* ------------------------------------------------------------------------- */


#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_STATE_C99_H__ */
