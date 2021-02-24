#ifndef SIXTRACKL_COMMON_BEAM_ELEMENTS_BEAMFIELDS_TRACK_C99_HEADER_H__
#define SIXTRACKL_COMMON_BEAM_ELEMENTS_BEAMFIELDS_TRACK_C99_HEADER_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beamfields/all_beamfields.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN void NS(SCCoasting_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(SCQGaussProfile_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )
SIXTRL_EXTERN SIXTRL_HOST_FN void NS(SCCoasting_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(SCQGaussProfile_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT;
#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */
/* =====        Implementation of Inline functions and methods         ===== */
/* ========================================================================= */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beamfields/definitions.h"
    #include "sixtracklib/common/beam_elements/beamfields/gauss_fields.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/physics_constants.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE void NS(SCCoasting_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT
{
    NS(particle_real_type) const charge_si =
        NS(PhysConst_charge0_si)() * NS(Particle_charge0)( p );

    SIXTRL_ARGPTR_DEC NS(be_real_type) Ex = ( NS(be_real_type) )0.0;
    SIXTRL_ARGPTR_DEC NS(be_real_type) Ey = ( NS(be_real_type) )0.0;

    NS(particle_real_type) fact_kick = NS(Particle_chi)( p ) *
        NS(SCCoasting_number_of_particles)( sc ) *
        NS(SCCoasting_length)( sc ) *
        charge_si * charge_si * NS(Particle_charge_ratio)( p ) *
        ( ( NS(particle_real_type) )1.0 - NS(Particle_beta0)( p ) *
            NS(Particle_beta)( p ) );

    SIXTRL_ASSERT( NS(Particle_is_active)( p ) );
    SIXTRL_ASSERT( NS(SCCoasting_circumference)( sc ) > ( NS(be_real_type) )0. );
    SIXTRL_ASSERT( NS(Particle_p0c)( p )  > ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( NS(Particle_beta)( p ) > ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( NS(Particle_beta)( p ) < ( NS(particle_real_type) )1.0 );

    fact_kick /= NS(SCCoasting_circumference)( sc ) *
                 NS(Particle_p0c)( p ) * NS(PhysConst_charge0_si)() *
                 NS(Particle_beta)( p );

    NS(BeamFields_calculate_gauss_components)(
        NS(Particle_x)( p ) - NS(SCCoasting_x_co)( sc ),
        NS(Particle_y)( p ) - NS(SCCoasting_y_co)( sc ),
        NS(SCCoasting_sigma_x)( sc ), NS(SCCoasting_sigma_y)( sc ),
        NS(SCCoasting_min_sigma_diff)( sc ), true /* skip_Gs */,
        &Ex, &Ey, SIXTRL_NULLPTR, SIXTRL_NULLPTR );

    NS(Particle_add_to_px)( p, fact_kick * Ex );
    NS(Particle_add_to_py)( p, fact_kick * Ey );
}

SIXTRL_INLINE void NS(SCQGaussProfile_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT
{
    SIXTRL_ARGPTR_DEC NS(be_real_type) Ex = ( NS(be_real_type) )0.0;
    SIXTRL_ARGPTR_DEC NS(be_real_type) Ey = ( NS(be_real_type) )0.0;

    NS(particle_real_type) const charge_si =
        NS(PhysConst_charge0_si)() * NS(Particle_charge0)( p );

    NS(particle_real_type) fact_kick = NS(Particle_chi)( p ) *
        NS(SCQGaussProfile_number_of_particles)( sc ) *
        NS(SCQGaussProfile_length)( sc ) *
        charge_si * charge_si * NS(Particle_charge_ratio)( p ) *
        /* ( 1 - beta0 * beta ) */
        ( ( NS(particle_real_type) )1.0 -
            NS(Particle_beta0)( p ) * NS(Particle_beta)( p ) );

    SIXTRL_ASSERT( NS(Particle_is_active)( p ) );
    SIXTRL_ASSERT( NS(SCQGaussProfile_bunchlength_rms)( sc ) >=
                   ( NS(be_real_type) )0. );
    SIXTRL_ASSERT( NS(Particle_p0c)( p )  > ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( NS(Particle_beta)( p ) > ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( NS(Particle_beta)( p ) < ( NS(particle_real_type) )1.0 );

    fact_kick *= NS(Math_q_gauss)( NS(Particle_sigma)( p ),
        NS(SCQGaussProfile_q_param)( sc ),
        NS(Math_q_gauss_sqrt_beta_from_gauss_sigma)(
            NS(SCQGaussProfile_bunchlength_rms)( sc ) ),
        NS(SCQGaussProfile_cq)( sc ) );

    fact_kick /= NS(Particle_p0c)( p ) * NS(PhysConst_charge0_si)() *
                 NS(Particle_beta)( p );

    NS(BeamFields_calculate_gauss_components)(
        NS(Particle_x)( p ) - NS(SCQGaussProfile_x_co)( sc ),
        NS(Particle_y)( p ) - NS(SCQGaussProfile_y_co)( sc ),
        NS(SCQGaussProfile_sigma_x)( sc ),
        NS(SCQGaussProfile_sigma_y)( sc ),
        NS(SCQGaussProfile_min_sigma_diff)( sc ), true /* skip_Gs */,
        &Ex, &Ey, SIXTRL_NULLPTR, SIXTRL_NULLPTR );

    NS(Particle_add_to_px)( p, fact_kick * Ex );
    NS(Particle_add_to_py)( p, fact_kick * Ey );
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKL_COMMON_BEAM_ELEMENTS_BEAMFIELDS_TRACK_C99_HEADER_H__ */

