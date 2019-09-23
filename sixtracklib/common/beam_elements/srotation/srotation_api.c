#include "sixtracklib/common/beam_elements/srotation/srotation_api.h"
#include "sixtracklib/common/beam_elements/srotation/srotation.h"
#include "sixtracklib/common/beam_elements/buffer.h"


bool NS(SRotation_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_dataptrs )
{
    typedef NS(buffer_size_t) buf_size_t;

    buf_size_t const num_dataptrs =
        NS(SRotation_get_num_dataptrs)( SIXTRL_NULLPTR );

    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* sizes  = SIXTRL_NULLPTR;
    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* counts = SIXTRL_NULLPTR;

    return NS(Buffer_can_add_object)( buffer, sizeof( NS(SRotation) ),
        num_dataptrs, sizes, counts, requ_objects, requ_slots, requ_dataptrs );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(SRotation)* NS(SRotation_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer )
{
    typedef NS(buffer_size_t)  buf_size_t;
    typedef SIXTRL_REAL_T                           real_t;
    typedef NS(SRotation)                           elem_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC   elem_t*     ptr_to_elem_t;

    buf_size_t const num_dataptrs =
        NS(SRotation_get_num_dataptrs)( SIXTRL_NULLPTR );

    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* offsets = SIXTRL_NULLPTR;
    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* sizes   = SIXTRL_NULLPTR;
    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* counts  = SIXTRL_NULLPTR;

    elem_t temp_obj;
    temp_obj.cos_z = ( real_t )1.0;
    temp_obj.sin_z = ( real_t )0.0;

    return ( ptr_to_elem_t )( uintptr_t )NS(Object_get_begin_addr)(
        NS(Buffer_add_object)( buffer, &temp_obj, sizeof( elem_t ),
            NS(OBJECT_TYPE_SROTATION), num_dataptrs, offsets, sizes, counts ) );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(SRotation)* NS(SRotation_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_REAL_T const angle )
{
    typedef NS(buffer_size_t)  buf_size_t;
    typedef NS(SRotation)                           elem_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC   elem_t*     ptr_to_elem_t;

    buf_size_t const num_dataptrs =
        NS(SRotation_get_num_dataptrs)( SIXTRL_NULLPTR );

    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* offsets = SIXTRL_NULLPTR;
    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* sizes   = SIXTRL_NULLPTR;
    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* counts  = SIXTRL_NULLPTR;

    elem_t temp_obj;
    temp_obj.cos_z = cos( angle );
    temp_obj.sin_z = sin( angle );

    return ( ptr_to_elem_t )( uintptr_t )NS(Object_get_begin_addr)(
        NS(Buffer_add_object)( buffer, &temp_obj, sizeof( elem_t ),
            NS(OBJECT_TYPE_SROTATION), num_dataptrs, offsets, sizes, counts ) );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(SRotation)* NS(SRotation_add_detailed)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_REAL_T const cos_z, SIXTRL_REAL_T const sin_z )
{
    typedef NS(buffer_size_t)  buf_size_t;
    typedef NS(SRotation)                           elem_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC   elem_t*     ptr_to_elem_t;

    buf_size_t const num_dataptrs =
        NS(SRotation_get_num_dataptrs)( SIXTRL_NULLPTR );

    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* offsets = SIXTRL_NULLPTR;
    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* sizes   = SIXTRL_NULLPTR;
    SIXTRL_BUFFER_ARGPTR_DEC buf_size_t const* counts  = SIXTRL_NULLPTR;

    #if !defined( NDEBUG )
    typedef SIXTRL_REAL_T  real_t;

    real_t temp = ( real_t )1 - ( cos_z * cos_z + sin_z * sin_z );
    if( temp < ( real_t )0.0 ) temp = -temp;
    SIXTRL_ASSERT( temp < ( real_t )1e-12 );
    #endif /* !defined( NDEBUG ) */

    elem_t temp_obj;
    temp_obj.cos_z = cos_z;
    temp_obj.sin_z = sin_z;

    return ( ptr_to_elem_t )( uintptr_t )NS(Object_get_begin_addr)(
        NS(Buffer_add_object)( buffer, &temp_obj, sizeof( elem_t ),
            NS(OBJECT_TYPE_SROTATION), num_dataptrs, offsets, sizes, counts ) );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(SRotation)* NS(SRotation_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srot )
{
    return NS(SRotation_add_detailed)( buffer,
        NS(SRotation_get_cos_angle)( srot ),
        NS(SRotation_get_sin_angle)( srot ) );
}

/* end: sixtracklib/common/beam_elements/srotation/srotation_api.c */
