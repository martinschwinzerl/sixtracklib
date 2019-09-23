#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROATION_TRACK_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROATION_TRACK_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/particles/track_particle.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(SRotation_track)(
    NS(TrackParticle)* SIXTRL_RESTRICT particle,
    SIXTRL_BE_ARGPTR_DEC const struct NS(SRotation)
        *const SIXTRL_RESTRICT srotation );

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */
/* =====        Implementation of Inline functions and methods         ===== */
/* ========================================================================= */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE int NS(SRotation_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srotation )
{
    typedef NS(particle_real_t) real_t;

    real_t const sin_z = NS(SRotation_get_sin_angle)( srotation );
    real_t const cos_z = NS(SRotation_get_cos_angle)( srotation );

    real_t const x  = NS(Particles_get_x_value)(  particles, index );
    real_t const y  = NS(Particles_get_y_value)(  particles, index );
    real_t const px = NS(Particles_get_px_value)( particles, index );
    real_t const py = NS(Particles_get_py_value)( particles, index );

    real_t const x_hat  =  cos_z * x  + sin_z * y;
    real_t const y_hat  = -sin_z * x  + cos_z * y;

    real_t const px_hat =  cos_z * px + sin_z * py;
    real_t const py_hat = -sin_z * px + cos_z * py;

    SIXTRL_ASSERT( NS(Particles_get_state_value)( particles, index ) ==
                  ( NS(particle_index_t) )1 );

    NS(Particles_set_x_value)(  particles, index, x_hat );
    NS(Particles_set_y_value)(  particles, index, y_hat );

    NS(Particles_set_px_value)( particles, index, px_hat );
    NS(Particles_set_py_value)( particles, index, py_hat );

    return 0;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROATION_TRACK_C99_H__ */
/* end: sixtracklib/common/beam_elements/srotation/track.h */
