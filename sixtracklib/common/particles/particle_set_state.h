#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_STATE_C99_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_STATE_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <limits.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
    #if !defined( _GPUCODE )
        #include "sixtracklib/commmon/buffer.h"
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t)
    NS(ParticleIndex_min_value)( void );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t)
    NS(ParticleIndex_max_value)( void );

/* ************************************************************************* */

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
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_clear)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(object_type_id_t)
NS(ParticleSetState_type_id)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetState_num_dataptrs)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(ParticleSetState_num_slots)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data,
    NS(buffer_size_t) const slot_size );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_num_elements_t)
NS(ParticleSetState_num_particles)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data );

SIXTRL_STATIC SIXTRL_FN NS(particle_num_elements_t)
NS(ParticleSetState_num_lost_particles)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t)
NS(ParticleSetState_min_particle_id)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t)
NS(ParticleSetState_max_particle_id)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t)
NS(ParticleSetState_min_at_element)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t)
NS(ParticleSetState_max_at_element)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t) NS(ParticleSetState_min_at_turn)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState) *const
        SIXTRL_RESTRICT pset_data );

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t) NS(ParticleSetState_max_at_turn)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState) *const
        SIXTRL_RESTRICT pset_data );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_num_particles)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_num_elements_t) const num_particles );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_num_lost_particles)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_num_elements_t) const num_lost_particles );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_min_particle_id)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_index_t) const min_particle_id );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_max_particle_id)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_index_t) const max_particle_id );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_min_at_element)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_index_t) const min_at_element );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_max_at_element)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_index_t) const max_at_element );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_min_at_turn)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_index_t) const min_at_turn );

SIXTRL_STATIC SIXTRL_FN void NS(ParticleSetState_set_max_at_turn)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_index_t) const max_at_turn );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSetState_prepare)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data );

SIXTRL_STATIC SIXTRL_FN bool NS(ParticleSetState_is_initialized)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState) *const SIXTRL_RESTRICT
        pset_data );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSetState_init_from_particle_set)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT particles,
    bool const include_lost_particles );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSetState_update_from_particle_set)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT particles,
    bool const include_lost_particles );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSetState_merge)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
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
        *const SIXTRL_RESTRICT pset_data, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSetState_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState)
        *const SIXTRL_RESTRICT pset_data, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSetState_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState)
        *const SIXTRL_RESTRICT pset_data );

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
    NS(pset_data_1d_int_t) const num_values,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(pset_data_1d_int_t) const num_values );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(particle_num_elements_t) const num_particles,
    NS(particle_num_elements_t) const num_lost_particles,
    NS(particle_index_t) const min_particle_id,
    NS(particle_index_t) const max_particle_id,
    NS(particle_index_t) const min_at_element,
    NS(particle_index_t) const max_at_element,
    NS(particle_index_t) const min_at_turn,
    NS(particle_index_t) const max_at_turn );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC const NS(ParticleSetState) *const
        SIXTRL_RESTRICT pset_data );

#endif /* defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSetState_copy)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState)
        *const SIXTRL_RESTRICT source );

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
        SIXTRACKLIB_ENABLE_MODULE_CUDA == 1 && defined( __CUDACC__ )
        #include <nppdefs.h>
    #endif /* defined( __CUDACC__ ) */

    #if !defined( _GPUCODE )
        #include <limits>
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(particle_index_t) NS(ParticleIndex_min_value)( void )
{
    #if defined( __cplusplus )
        #if defined( __CUDACC__ ) && \
            defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
                     SIXTRACKLIB_ENABLE_MODULE_CUDA == 1
            return NPP_MIN_64S;
        #elif !defined( _GPUCODE )
            return std::numeric_limits< ::NS(particle_index_t) >::min();
        #else /* No idea where we are here, best effort and hope for the best */
            return ::NS(particle_index_t){ -9223372036854775807LL - 1 };
        #endif /* C++ including Cuda and potentially OpenCL 2.x */
    #else /* !defined( __cplusplus ) */
        #if defined( _GPUCODE ) && defined( __OPENCL_VERSION__ ) && \
            defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
                     SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1
            return ( NS(particle_index_t) )( -9223372036854775807L - 1 );
        #else
            return INT64_MIN;
        #endif /* C99, including OpenCL 1.x */
    #endif /* !defined( __cplusplus ) */
}

SIXTRL_INLINE NS(particle_index_t) NS(ParticleIndex_max_value)( void )
{
    #if defined( __cplusplus )
        #if defined( __CUDACC__ ) && \
            defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
                     SIXTRACKLIB_ENABLE_MODULE_CUDA == 1
            return NPP_MAX_64S;
        #elif !defined( _GPUCODE )
            return std::numeric_limits< ::NS(particle_index_t) >::max();
        #else /* No idea where we are here, best effort and hope for the best */
            return ::NS(particle_index_t){ 9223372036854775807LL };
        #endif /* C++ including Cuda and potentially OpenCL 2.x */
    #else /* !defined( __cplusplus ) */
        #if defined( _GPUCODE ) && defined( __OPENCL_VERSION__ ) && \
            defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
                     SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1
            return ( NS(particle_index_t) )( 9223372036854775807L );
        #else
            return INT64_MAX;
        #endif /* C99, including OpenCL 1.x */
    #endif /* !defined( __cplusplus ) */
}

/* ************************************************************************* */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_preset)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data )
{
    if( pset_data != SIXTRL_NULLPTR )
    {
        NS(ParticleSetState_clear)( pset_data );
    }

    return pset_data;
}

SIXTRL_INLINE void NS(ParticleSetState_clear)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data )
{
    SIXTRL_ASSERT( pset_data != SIXTRL_NULLPTR );
    pset_data->num_particles = ( NS(particle_num_elements_t) )0u;
    pset_data->num_lost_particles = ( NS(particle_num_elements_t) )0u;

    pset_data->min_particle_id = NS(ParticleIndex_max_value)();
    pset_data->max_particle_id = NS(ParticleIndex_min_value)();
    pset_data->min_at_element  = NS(ParticleIndex_max_value)();
    pset_data->max_at_element  = NS(ParticleIndex_min_value)();
    pset_data->min_at_turn     = NS(ParticleIndex_max_value)();
    pset_data->max_at_turn     = NS(ParticleIndex_min_value)();
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(object_type_id_t)
NS(ParticleSetState_type_id)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data )
{
    ( void )pset_data;
    return NS(OBJECT_TYPE_PARTICLE_SET_STATE);
}

SIXTRL_INLINE NS(buffer_size_t)
NS(ParticleSetState_num_dataptrs)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data )
{
    ( void )pset_data;
    return ( NS(buffer_size_t) )0u;
}

SIXTRL_INLINE NS(buffer_size_t)
NS(ParticleSetState_num_slots)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data,
    NS(buffer_size_t) const slot_size )
{
    SIXTRL_ASSERT( slot_size > ( NS(buffer_size_t) )0u );

    NS(buffer_size_t) const obj_size = NS(ManagedBuffer_get_slot_based_length)(
        sizeof( NS(ParticleSetState) ), slot_size );

    NS(buffer_size_t) num_slots = obj_size / slot_size;

    if( ( num_slots * slot_size ) < obj_size ) ++num_slots;
    SIXTRL_ASSERT( ( num_slots * slot_size ) >= obj_size );

    return num_slots;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_num_elements_t)
NS(ParticleSetState_num_particles)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data )
{
    SIXTRL_ASSERT( pset_data != SIXTRL_NULLPTR );
    return pset_data->num_particles;
}

SIXTRL_INLINE NS(particle_num_elements_t)
NS(ParticleSetState_num_lost_particles)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data )
{
    SIXTRL_ASSERT( pset_data != SIXTRL_NULLPTR );
    return pset_data->num_lost_particles;
}

SIXTRL_INLINE NS(particle_index_t)
NS(ParticleSetState_min_particle_id)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data )
{
    SIXTRL_ASSERT( pset_data != SIXTRL_NULLPTR );
    return pset_data->min_particle_id;
}

SIXTRL_INLINE NS(particle_index_t)
NS(ParticleSetState_max_particle_id)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data )
{
    SIXTRL_ASSERT( pset_data != SIXTRL_NULLPTR );
    return pset_data->max_particle_id;
}

SIXTRL_INLINE NS(particle_index_t)
NS(ParticleSetState_min_at_element)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data )
{
    SIXTRL_ASSERT( pset_data != SIXTRL_NULLPTR );
    return pset_data->min_at_element;
}

SIXTRL_INLINE NS(particle_index_t)
NS(ParticleSetState_max_at_element)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(ParticleSetState) *const SIXTRL_RESTRICT pset_data )
{
    SIXTRL_ASSERT( pset_data != SIXTRL_NULLPTR );
    return pset_data->max_at_element;
}

SIXTRL_INLINE NS(particle_index_t) NS(ParticleSetState_min_at_turn)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState) *const
        SIXTRL_RESTRICT pset_data )
{
    SIXTRL_ASSERT( pset_data != SIXTRL_NULLPTR );
    return pset_data->min_at_turn;
}

SIXTRL_INLINE NS(particle_index_t) NS(ParticleSetState_max_at_turn)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState) *const
        SIXTRL_RESTRICT pset_data )
{
    SIXTRL_ASSERT( pset_data != SIXTRL_NULLPTR );
    return pset_data->min_at_turn;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(ParticleSetState_set_num_particles)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_num_elements_t) const num_particles )
{
    if( pset_data != SIXTRL_NULLPTR ) pset_data->num_particles = num_particles;
}

SIXTRL_INLINE void NS(ParticleSetState_set_num_lost_particles)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_num_elements_t) const num_lost_particles )
{
    if( pset_data != SIXTRL_NULLPTR )
        pset_data->num_lost_particles = num_lost_particles;
}

SIXTRL_INLINE void NS(ParticleSetState_set_min_particle_id)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_index_t) const min_particle_id )
{
    if( pset_data != SIXTRL_NULLPTR )
        pset_data->min_particle_id = min_particle_id;
}

SIXTRL_INLINE void NS(ParticleSetState_set_max_particle_id)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_index_t) const max_particle_id )
{
    if( pset_data != SIXTRL_NULLPTR )
        pset_data->max_particle_id  = max_particle_id;
}

SIXTRL_INLINE void NS(ParticleSetState_set_min_at_element)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_index_t) const min_at_element )
{
    if( pset_data != SIXTRL_NULLPTR )
        pset_data->min_at_element = min_at_element;
}

SIXTRL_INLINE void NS(ParticleSetState_set_max_at_element)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_index_t) const max_at_element )
{
    if( pset_data != SIXTRL_NULLPTR )
        pset_data->max_at_element = max_at_element;
}

SIXTRL_INLINE void NS(ParticleSetState_set_min_at_turn)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_index_t) const min_at_turn )
{
    if( pset_data != SIXTRL_NULLPTR ) pset_data->min_at_turn = min_at_turn;
}

SIXTRL_INLINE void NS(ParticleSetState_set_max_at_turn)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    NS(particle_index_t) const max_at_turn )
{
    if( pset_data != SIXTRL_NULLPTR ) pset_data->max_at_turn = max_at_turn;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSetState_prepare)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data )
{
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( pset_data != SIXTRL_NULLPTR )
    {
        NS(ParticleSetState_clear)( pset_data );
        status = NS(ARCH_STATUS_SUCCESS);
    }

    return status;
}

SIXTRL_INLINE bool NS(ParticleSetState_is_initialized)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState) *const SIXTRL_RESTRICT
        pset_data )
{
    return ( ( pset_data != SIXTRL_NULLPTR ) &&
             ( pset_data->min_particle_id <= pset_data->max_particle_id ) &&
             ( pset_data->min_at_element <= pset_data->max_at_element ) &&
             ( pset_data->min_at_turn <= pset_data->max_at_turn ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSetState_init_from_particle_set)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT particles,
    bool const include_lost_particles )
{
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( pset_data != SIXTRL_NULLPTR )
    {
        NS(ParticleSetState_clear)( pset_data );
        status = NS(ParticleSetState_update_from_particle_set)(
            pset_data, particles, include_lost_particles );
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSetState_update_from_particle_set)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT particles )
{
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( pset_data != SIXTRL_NULLPTR ) && ( particles != SIXTRL_NULLPTR ) )
    {
        NS(particle_num_elements_t) const nn =
            NS(Particles_get_num_of_particles)( particles );

        NS(particle_num_elements_t) ii = ( NS(particle_num_elements_t) )0u;

        status = NS(ARCH_STATUS_SUCCESS);
        pset_data->num_particles += nn;

        for( ; ii < nn ; ++ii )
        {
            bool const is_lost = NS(Particles_is_lost_value)( particles, ii );
            pset_data->num_lost_particles += ( NS(particle_index_t) )is_lost;

            if( ( !is_lost ) || ( include_lost_particles ) )
            {
                NS(particle_index_t) const particle_id =
                    NS(Particles_get_particle_id_value)( particles, ii );

                NS(particle_index_t) const at_element =
                    NS(Particles_get_at_element_id_value)( particles, ii );

                NS(particle_index_t) const at_turn =
                    NS(Particles_get_at_turn_value)( particles, ii );

                if( pset_data->min_particle_id > particle_id )
                    pset_data->min_particle_id = particle_id;

                if( pset_data->max_particle_id < particle_id )
                    pset_data->max_particle_id = particle_id;

                if( pset_data->min_at_element  < at_element )
                    pset_data->min_at_element  = at_element;

                if( pset_data->max_at_element  < at_element )
                    pset_data->max_at_element  = at_element;

                if( pset_data->min_at_turn < at_turn )
                    pset_data->min_at_turn = at_turn;

                if( pset_data->max_at_turn < at_turn )
                    pset_data->max_at_turn = at_turn;
            }
        }
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSetState_merge)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)* SIXTRL_RESTRICT pset_data,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState)
        *const SIXTRL_RESTRICT other )
{
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( pset_data != SIXTRL_NULLPTR )
    {
        status = NS(ARCH_STATUS_SUCCESS);

        if( other != SIXTRL_NULLPTR )
        {
            if( pset_data->min_particle_id > other->min_particle_id )
                pset_data->min_particle_id = other->min_particle_id;

            if( pset_data->max_particle_id < other->max_particle_id )
                pset_data->max_particle_id = other->max_particle_id;

            if( pset_data->min_at_element > other->min_at_element )
                pset_data->min_at_element = other->min_at_element;

            if( pset_data->max_at_element < other->max_at_element )
                pset_data->max_at_element = other->max_at_element;

            if( pset_data->min_at_turn > other->min_at_turn )
                pset_data->min_at_turn = other->min_at_turn;

            if( pset_data->max_at_turn < other->max_at_turn )
                pset_data->max_at_turn = other->max_at_turn;

            pset_data->num_particles += other->num_particles;
            pset_data->num_lost_particles += other->num_lost_particles;
        }
    }

    return status;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState) const*
NS(ParticleSetState_const_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT obj )
{
    return ( ( NS(Object_get_type_id)( obj ) ==
                NS(OBJECT_TYPE_PARTICLE_SET_STATE) ) &&
             ( NS(Object_get_size)( obj ) >= sizeof( NS(ParticleSetState) ) ) )
        ? ( SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState) const*
            )( uintptr_t )NS(Object_get_begin_addr)( obj )
        : SIXTRL_NULLPTR;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_from_obj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    NS(Object)* SIXTRL_RESTRICT obj )
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
        )NS(ParticleSetState_const_from_obj_index)( obj );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState) const*
NS(ParticleSetState_const_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(ParticleSetState_const_from_obj_index)(
        NS(ManagedBuffer_get_const_object)( pbuffer, index, slot_size ) );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(ParticleSetState)*
NS(ParticleSetState_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(ParticleSetState_from_obj_index)(
        NS(ManagedBuffer_get_object)( pbuffer, index, slot_size ) );
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSetState_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState)
        *const SIXTRL_RESTRICT pset_data, NS(buffer_size_t) const slot_size )
{
    SIXTRL_ASSERT( NS(ParticleSetState_num_dataptrs)( pset_data ) ==
        ( NS(buffer_size_t) )0u );

    ( void )pset_data;
    return NS(Buffer_set_attr_arrays_for_trivial_object)(
        offsets_begin, max_num_offsets, slot_size );
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSetState_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState)
        *const SIXTRL_RESTRICT pset_data, NS(buffer_size_t) const slot_size )
{
    SIXTRL_ASSERT( NS(ParticleSetState_num_dataptrs)( pset_data ) ==
        ( NS(buffer_size_t) )0u );

    ( void )pset_data;
    return NS(Buffer_set_attr_arrays_for_trivial_object)(
        sizes_begin, max_num_sizes, slot_size );
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSetState_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticleSetState)
        *const SIXTRL_RESTRICT pset_data )
{
    SIXTRL_ASSERT( NS(ParticleSetState_num_dataptrs)( pset_data ) ==
        ( NS(buffer_size_t) )0u );

    ( void )pset_data;
    return NS(Buffer_set_attr_arrays_for_trivial_object)(
        counts_begin, max_num_counts, SIXTRL_BUFFER_DEFAULT_SLOT_SIZE );
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_STATE_C99_H__ */
