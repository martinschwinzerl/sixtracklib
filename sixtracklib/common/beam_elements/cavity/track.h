#ifndef SIXTRACKL_COMMON_BEAM_ELEMENTS_CAVITY_TRACK_C99_HEADER_H__
#define SIXTRACKL_COMMON_BEAM_ELEMENTS_CAVITY_TRACK_C99_HEADER_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/cavity.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN void NS(Cavity_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT cavity
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )
SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Cavity_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT cavity
) SIXTRL_NOEXCEPT;
#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */
/* =====        Implementation of Inline functions and methods         ===== */
/* ========================================================================= */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/physics_constants.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE void NS(Cavity_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT cavity
) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_type;
    real_type const phase = NS(MathConst_deg2rad)() * NS(Cavity_lag)( cavity ) -
        ( real_type )2. * NS(MathConst_pi)() * NS(Cavity_frequency)( cavity )
                        * NS(Particle_tau)( p ) / NS(PhysConst_clight)();
    NS(Particle_add_to_energy)( p,
        NS(Particle_charge)( p ) * NS(Cavity_voltage)( cavity ) * sin( phase ) );
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKL_COMMON_BEAM_ELEMENTS_CAVITY_TRACK_C99_HEADER_H__ */
