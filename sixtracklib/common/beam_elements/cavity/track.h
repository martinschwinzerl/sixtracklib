#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_TRACK_C99_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_TRACK_C99_HPP__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/track/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"

#include "sixtracklib/common/beam_elements/cavity/cavity.h"
#include "sixtracklib/common/constants.h"
#include "sixtracklib/common/particles/track_particle.h"

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

NS(track_status_t) NS(Cavity_track)(
    NS(TrackParticle)* SIXTRL_RESTRICT particle,
    const NS(Cavity) *const SIXTRL_RESTRICT cavity )
{
    typedef NS(particle_real_t) real_t;
    SIXTRL_ASSERT( particle != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( cavity   != SIXTRL_NULLPTR );

    real_t const tau =
        particle->zeta / ( particle->beta0 * particle->rvv );

    real_t const phase =
        SIXTRL_DEG2RAD * cavity->lag -
        ( ( real_t )2.0 * SIXTRL_PI * tau * cavity->frequency ) /
            SIXTRL_C_LIGHT;

    real_t const delta_energy =
        particle->q0  * particle->charge_ratio *
        sin( phase ) * cavity->voltage );

    NS(Particle_add_energy)( particle, delta_energy );
    return SIXTRL_TRACK_SUCCESS;
}

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_TRACK_C99_HPP__ */

/* end: */
