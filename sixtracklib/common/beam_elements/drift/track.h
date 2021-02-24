#ifndef SIXTRACKL_COMMON_BEAM_ELEMENTS_DRIFT_TRACK_C99_HEADER_H__
#define SIXTRACKL_COMMON_BEAM_ELEMENTS_DRIFT_TRACK_C99_HEADER_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN void NS(Drift_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT drift
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(DriftExact_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT drift
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Drift_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT drift
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(DriftExact_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT drift
) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */
#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */
/* =====        Implementation of Inline functions and methods         ===== */
/* ========================================================================= */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/generated/config.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE void NS(Drift_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_type;
    real_type const length = ( real_type )NS(Drift_length)( elem );
    real_type const xp = NS(Particle_px)( p ) * NS(Particle_rpp)( p );
    real_type const yp = NS(Particle_py)( p ) * NS(Particle_rpp)( p );

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particle_beta0)( p ) >= ( real_type )0. );
    SIXTRL_ASSERT( NS(Particle_beta0)( p ) <= ( real_type )1. );

    NS(Particle_add_to_x)( p, xp * length );
    NS(Particle_add_to_y)( p, yp * length );
    NS(Particle_add_to_zeta)( p, length * ( NS(Particle_rvv)( p ) -
        ( ( real_type )1. + ( real_type )0.5 * ( xp * xp + yp * yp ) ) ) );

    #if defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
        ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
    NS(Particle_add_to_s)( p, length );
    #endif /* use s */
}

SIXTRL_INLINE void NS(DriftExact_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_type;
    real_type const length = ( real_type )NS(DriftExact_length)( elem );
    real_type const one_plus_delta = NS(Particle_delta)( p ) + ( real_type )1.;
    real_type const lpzi = length / sqrt( one_plus_delta * one_plus_delta -
        NS(Particle_px)( p ) * NS(Particle_px)( p ) -
        NS(Particle_py)( p ) * NS(Particle_py)( p ) );

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particle_beta0)( p ) > ( real_type )0. );
    SIXTRL_ASSERT( ( one_plus_delta * one_plus_delta ) >
                   ( NS(Particle_px)( p ) * NS(Particle_px)( p ) +
                     NS(Particle_py)( p ) * NS(Particle_py)( p ) ) );

    NS(Particle_add_to_x)( p, NS(Particle_px)( p ) * lpzi );
    NS(Particle_add_to_y)( p, NS(Particle_py)( p ) * lpzi );

    NS(Particle_add_to_zeta)( p,
        NS(Particle_rvv)( p ) * length - one_plus_delta * lpzi );

    #if defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
        ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
    NS(Particle_add_to_s)( p, length );
    #endif /* use s */
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKL_COMMON_BEAM_ELEMENTS_DRIFT_TRACK_C99_HEADER_H__ */
