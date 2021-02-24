#ifndef SIXTRACKL_COMMON_BEAM_ELEMEMTNS_XY_SHIFT_XY_SHIFT_TRACK_C99_H__
#define SIXTRACKL_COMMON_BEAM_ELEMEMTNS_XY_SHIFT_XY_SHIFT_TRACK_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN void NS(XYShift_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT xy_shift
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )
    SIXTRL_EXTERN SIXTRL_HOST_FN void NS(XYShift_track_particle_ext)(
        SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const struct NS(XYShift) *const SIXTRL_RESTRICT e
    ) SIXTRL_NOEXCEPT;
#endif /* !defined( _GPUCODE ) */

/* ========================================================================= */

SIXTRL_INLINE void NS(XYShift_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    NS(Particle_subtract_from_x)( p,
        ( NS(particle_real_type) )NS(XYShift_dx)( elem ) );
    NS(Particle_subtract_from_y)( p,
        ( NS(particle_real_type) )NS(XYShift_dy)( elem ) ); }

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKL_COMMON_BEAM_ELEMEMTNS_XY_SHIFT_XY_SHIFT_TRACK_C99_H__ */
