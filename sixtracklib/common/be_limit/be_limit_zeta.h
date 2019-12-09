#ifndef SIXTRACKL_COMMON_BE_LIMIT_BE_LIMIT_ZETA_C99_H__
#define SIXTRACKL_COMMON_BE_LIMIT_BE_LIMIT_ZETA_C99_H__

#ifndef SIXTRACKLIB_COMMON_BE_TRICUB_C99_H__
#define SIXTRACKLIB_COMMON_BE_TRICUB_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <math.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
    #include "sixtracklib/common/particles/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* !defined( __cplusplus ) && !defined( _GPUCODE ) */

typedef struct NS(LimitZeta)
{
    NS(particle_real_t) min_zeta SIXTRL_ALIGN( 8 );
    NS(particle_real_t) max_zeta SIXTRL_ALIGN( 8 );
}
NS(LimitZeta);

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)*
NS(LimitZeta_preset)( SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* SIXTRL_RESTRICT l );

SIXTRL_STATIC SIXTRL_FN void NS(LimitZeta_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* SIXTRL_RESTRICT limit );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(LimitZeta_min_zeta)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit );

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(LimitZeta_max_zeta)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN void NS(LimitZeta_set_min_zeta)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* SIXTRL_RESTRICT limit,
    NS(particle_real_t) const min_zeta );

SIXTRL_STATIC SIXTRL_FN void NS(LimitZeta_set_max_zeta)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* SIXTRL_RESTRICT limit,
    NS(particle_real_t) const max_zeta );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(object_type_id_t) NS(LimitZeta_type_id)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t) NS(LimitZeta_num_dataptrs)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t) NS(LimitZeta_num_slots)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit,
    NS(buffer_size_t) const slot_size );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitZeta) const*
NS(LimitZeta_const_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)*
NS(LimitZeta_from_obj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitZeta) const*
NS(LimitZeta_const_from_managed_buffer)(
    SIXTRL_BE_ARGPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)*
NS(LimitZeta_from_managed_buffer)(
    SIXTRL_BE_ARGPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );


#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(LimitZeta) const*
NS(LimitZeta_const_from_buffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)*
NS(LimitZeta_from_buffer)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(LimitZeta_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit,
    NS(buffer_size_t) const slot_size );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(LimitZeta_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit,
    NS(buffer_size_t) const slot_size );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(LimitZeta_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(LimitZeta_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)*
NS(LimitZeta_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)*
NS(LimitZeta_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(particle_real_t) const min_zeta, NS(particle_real_t) const max_zeta );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)*
NS(LimitZeta_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit );

#endif /* !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(LimitZeta_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT src );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* !defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */

/* ************************************************************************* */


#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* !defined( __cplusplus ) && !defined( _GPUCODE ) */

typedef struct NS(LimitZeta)
{
    NS(particles_real_t) min_zeta SIXTRL_ALIGN( 8 );
    NS(particles_real_t) max_zeta SIXTRL_ALIGN( 8 );
}
NS(LimitZeta);

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)*
NS(LimitZeta_preset)( SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* SIXTRL_RESTRICT l )
{
    if( l != SIXTRL_NULLPTR ) NS(LimitZeta_clear)( l );
    return l;
}

SIXTRL_INLINE void NS(LimitZeta_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* SIXTRL_RESTRICT limit )
{
    SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    limit->min_zeta = ( NS(particle_real_t) )1e16;
    limit->max_zeta = ( NS(particle_real_t) )-1e16;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(LimitZeta_min_zeta)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit )
{
    SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    return limit->min_zeta;
}

SIXTRL_INLINE NS(particle_real_t) NS(LimitZeta_max_zeta)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit )
{
    SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    return limit->max_zeta;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE void NS(LimitZeta_set_min_zeta)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* SIXTRL_RESTRICT limit,
    NS(particle_real_t) const min_zeta )
{
    if( limit != SIXTRL_NULLPTR ) limit->min_zeta = min_zeta;
}

SIXTRL_INLINE void NS(LimitZeta_set_max_zeta)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* SIXTRL_RESTRICT limit,
    NS(particle_real_t) const max_zeta )
{
    if( limit != SIXTRL_NULLPTR ) limit->max_zeta = max_zeta;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(object_type_id_t) NS(LimitZeta_type_id)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit )
{
    ( void )limit;
    return NS(OBJECT_TYPE_LIMIT_ZETA);
}

SIXTRL_INLINE NS(buffer_size_t) NS(LimitZeta_num_dataptrs)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit )
{
    ( void )limit;
    return ( NS(buffer_size_t) )0u;
}

SIXTRL_INLINE NS(buffer_size_t) NS(LimitZeta_num_slots)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT limit,
    NS(buffer_size_t) const slot_size )
{
    ( void )limit;

    return NS(ManagedBuffer_get_slot_based_length)(
        sizeof( NS(LimitZeta) ), slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitZeta) const*
NS(LimitZeta_const_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const obj )
{
    return ( ( obj != SIXTRL_NULLPTR ) &&
             ( NS(Object_get_type_id)( obj ) == NS(OBJECT_TYPE_LIMIT_ZETA) ) &&
             ( NS(Object_get_size)( obj ) >= sizeof( NS(LimitZeta) ) ) )
        ? ( SIXTRL_BE_ARGPTR_DEC NS(LimitZeta) const* )(
                uintptr_t )NS(Object_get_begin_addr)( obj )
        : SIXTRL_NULLPTR;
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)*
NS(LimitZeta_from_obj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* obj )
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)*
        )NS(LimitZeta_const_from_obj_index)( obj );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitZeta) const*
NS(LimitZeta_const_from_managed_buffer)(
    SIXTRL_BE_ARGPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(LimitZeta_const_from_obj_index)(
        NS(ManagedBuffer_get_const_object)( buffer_begin, index, slot_size ) );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)*
NS(LimitZeta_from_managed_buffer)(
    SIXTRL_BE_ARGPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(LimitZeta_from_obj_index)(
        NS(ManagedBuffer_get_object)( buffer_begin, index, slot_size ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(LimitZeta_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitZeta)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitZeta) *const SIXTRL_RESTRICT src )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) )
    {
        if( dest != src )
        {
            dest->min_zeta = src->min_zeta;
            dest->max_zeta = src->max_zeta;
        }

        status = SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* !defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKL_COMMON_BE_LIMIT_BE_LIMIT_ZETA_C99_H__ */
