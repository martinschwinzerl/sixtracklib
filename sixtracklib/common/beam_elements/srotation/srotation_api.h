#ifndef SIXTRACKLIB_COMMON_BEAM_ELMENTS_SROTATION_SROTATION_API_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELMENTS_SROTATION_SROTATION_API_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #if !defined( SIXTRL_NO_INCLUDES )
        #include "sixtracklib/common/buffer.h"
    #endif /* !defined( SIXTRL_NO_INCLUDES ) */
    #include "sixtracklib/common/beam_elements/srotation/srotation.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t) NS(SRotation_get_num_dataptrs)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srotation );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t) NS(SRotation_get_num_slots)(
    SIXTRL_BE_ARGPTR_DEC  const NS(SRotation) *const SIXTRL_RESTRICT srot,
    NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(SRotation)* NS(SRotation_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT srotation );

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_T NS(SRotation_get_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srotation );

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_T NS(SRotation_get_angle)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srotation );

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_T NS(SRotation_get_cos_angle)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srotation );

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_T NS(SRotation_get_sin_angle)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srotation );

SIXTRL_STATIC SIXTRL_FN void NS(SRotation_set_angle)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT srotation,
    SIXTRL_REAL_T const angle );

SIXTRL_STATIC SIXTRL_FN void NS(SRotation_set_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT srotation,
    SIXTRL_REAL_T const angle_deg );

SIXTRL_STATIC SIXTRL_FN void NS(SRotation_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT srotation );

SIXTRL_STATIC SIXTRL_FN int NS(SRotation_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT source );

SIXTRL_STATIC SIXTRL_FN int  NS(SRotation_compare_values)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs );

SIXTRL_STATIC SIXTRL_FN int  NS(SRotation_compare_values_with_treshold)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs,
    SIXTRL_REAL_T const treshold );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(SRotation_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_dataptrs );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(SRotation)* NS(SRotation_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(SRotation)* NS(SRotation_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_REAL_T const angle );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(SRotation)*
NS(SRotation_add_detailed)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_REAL_T const cos_z, SIXTRL_REAL_T const sin_z );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(SRotation)*
NS(SRotation_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srotation );

#endif /* !defined( _GPUCODE ) */

/* ========================================================================= */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* */
/* *****          Implementation of C inline functions                   *** */
/* ************************************************************************* */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(buffer_size_t) NS(SRotation_get_num_dataptrs)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srotation )
{
    ( void )srotation;
    return ( NS(buffer_size_t) )0u;
}

SIXTRL_INLINE NS(buffer_size_t) NS(SRotation_get_num_slots)(
    SIXTRL_BE_ARGPTR_DEC  const NS(SRotation) *const SIXTRL_RESTRICT srot,
    NS(buffer_size_t) const slot_size )
{
    typedef NS(buffer_size_t) buf_size_t;
    typedef NS(SRotation)     beam_element_t;

    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;

    ( void )srot;

    buf_size_t extent = NS(ManagedBuffer_get_slot_based_length)(
        sizeof( beam_element_t ), slot_size );

    SIXTRL_ASSERT( ( slot_size == ZERO ) || ( ( extent % slot_size ) == ZERO ) );
    return ( slot_size > ZERO ) ? ( extent / slot_size ) : ( ZERO );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SRotation)* NS(SRotation_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT srotation )
{
    NS(SRotation_clear)( srotation );
    return srotation;
}

SIXTRL_INLINE SIXTRL_REAL_T NS(SRotation_get_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srotation )
{
    SIXTRL_REAL_T const RAD2DEG = ( SIXTRL_REAL_T )180.0 / M_PI;
    return RAD2DEG * NS(SRotation_get_angle)( srotation );
}

SIXTRL_INLINE SIXTRL_REAL_T NS(SRotation_get_angle)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srotation )
{
    SIXTRL_STATIC_VAR SIXTRL_REAL_T const ZERO = ( SIXTRL_REAL_T )0.0;
    SIXTRL_STATIC_VAR SIXTRL_REAL_T const ONE  = ( SIXTRL_REAL_T )1.0;

    #if !defined( NDEBUG ) && !defined( _GPUCODE )
    SIXTRL_STATIC_VAR SIXTRL_REAL_T const EPS  = ( SIXTRL_REAL_T )1e-6;
    #endif /* !defined( NDEBUG ) && !defined( _GPUCODE )*/

    SIXTRL_REAL_T const sin_z = ( srotation != SIXTRL_NULLPTR )
        ? srotation->sin_z : ZERO;

    SIXTRL_REAL_T const cos_z = ( srotation != SIXTRL_NULLPTR )
        ? srotation->cos_z : ONE;

    SIXTRL_REAL_T const angle = ( sin_z >= ZERO )
        ? acos( cos_z ) : -acos( cos_z );

    #if !defined( NDEBUG ) && !defined( _GPUCODE )
    SIXTRL_REAL_T const temp_sin_z = sin( angle );
    SIXTRL_REAL_T const delta      = temp_sin_z - srotation->sin_z;
    SIXTRL_ASSERT( fabs( delta ) < EPS );
    #endif /* !defined( NDEBUG ) && !defined( _GPUCODE ) */

    return angle;
}

SIXTRL_INLINE SIXTRL_REAL_T NS(SRotation_get_cos_angle)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srotation )
{
    SIXTRL_ASSERT( srotation != SIXTRL_NULLPTR );
    return srotation->cos_z;
}

SIXTRL_INLINE SIXTRL_REAL_T NS(SRotation_get_sin_angle)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srotation )
{
    SIXTRL_ASSERT( srotation != SIXTRL_NULLPTR );
    return srotation->sin_z;
}

SIXTRL_INLINE void NS(SRotation_set_angle)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT srotation,
    SIXTRL_REAL_T const angle )
{
    if( srotation != SIXTRL_NULLPTR )
    {
        srotation->cos_z = cos( angle );
        srotation->sin_z = sin( angle );
    }

    return;
}

SIXTRL_INLINE void NS(SRotation_set_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT srotation,
    SIXTRL_REAL_T const angle_deg )
{
    SIXTRL_STATIC_VAR SIXTRL_REAL_T const DEG2RAD =
        M_PI / ( SIXTRL_REAL_T )180.0;

    NS(SRotation_set_angle)( srotation, DEG2RAD * angle_deg );

    return;
}

SIXTRL_INLINE void NS(SRotation_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT srotation )
{
    if( srotation != SIXTRL_NULLPTR )
    {
        srotation->cos_z = ( SIXTRL_REAL_T )1;
        srotation->sin_z = ( SIXTRL_REAL_T )0;
    }

    return;
}

SIXTRL_INLINE int NS(SRotation_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT source )
{
    int success = -1;

    if( ( destination != SIXTRL_NULLPTR ) && ( source != SIXTRL_NULLPTR ) )
    {
        destination->cos_z = NS(SRotation_get_cos_angle)( source );
        destination->sin_z = NS(SRotation_get_sin_angle)( source );
        success = 0;
    }

    return success;
}

SIXTRL_INLINE int NS(SRotation_compare_values)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs )
{
    int compare_value = -1;

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        compare_value = 0;

        if( NS(SRotation_get_cos_angle)( lhs ) >
            NS(SRotation_get_cos_angle)( rhs ) )
        {
            compare_value = +1;
        }
        else if( NS(SRotation_get_cos_angle)( lhs ) <
                 NS(SRotation_get_cos_angle)( rhs ) )
        {
            compare_value = -1;
        }

        if( compare_value == 0 )
        {
            if( NS(SRotation_get_sin_angle)( lhs ) >
                NS(SRotation_get_sin_angle)( rhs ) )
            {
                compare_value = +1;
            }
            else if( NS(SRotation_get_sin_angle)( lhs ) <
                     NS(SRotation_get_sin_angle)( rhs ) )
            {
                compare_value = -1;
            }
        }
    }
    else if( lhs != SIXTRL_NULLPTR )
    {
        compare_value = +1;
    }

    return compare_value;
}

SIXTRL_INLINE int NS(SRotation_compare_values_with_treshold)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs,
    SIXTRL_REAL_T const treshold )
{
    typedef SIXTRL_REAL_T       real_t;

    SIXTRL_STATIC_VAR real_t const ZERO = ( real_t )0.0;

    int compare_value = -1;

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( treshold >= ZERO ) )
    {
        compare_value = 0;

        if( compare_value == 0 )
        {
            real_t const diff = NS(SRotation_get_cos_angle)( lhs ) -
                                NS(SRotation_get_cos_angle)( rhs );

            real_t const abs_diff = ( diff >= ZERO ) ? diff : -diff;

            if( abs_diff > treshold )
            {
                if( diff > ZERO )
                {
                    compare_value = +1;
                }
                else if( diff < ZERO )
                {
                    compare_value = -1;
                }
            }
        }

        if( compare_value == 0 )
        {
            real_t const diff = NS(SRotation_get_sin_angle)( lhs ) -
                                NS(SRotation_get_sin_angle)( rhs );

            real_t const abs_diff = ( diff >= ZERO ) ? diff : -diff;

            if( abs_diff > treshold )
            {
                if( diff > ZERO )
                {
                    compare_value = +1;
                }
                else if( diff < ZERO )
                {
                    compare_value = -1;
                }
            }
        }
    }
    else if( ( lhs != SIXTRL_NULLPTR ) && ( treshold >= ZERO ) )
    {
        compare_value = +1;
    }

    return compare_value;
}

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */


#endif /* SIXTRACKLIB_COMMON_BEAM_ELMENTS_SROTATION_SROTATION_API_C99_H__ */

/* end: sixtracklib/common/beam_elements/srotation/srotation_api.h */
