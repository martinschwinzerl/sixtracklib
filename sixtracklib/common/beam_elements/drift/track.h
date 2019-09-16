#ifndef SIXTRACKLIB_COMMON_BE_DRIFT_TRACK_C99_H__
#define SIXTRACKLIB_COMMON_BE_DRIFT_TRACK_C99_H__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/track/definitions.h"

#include "sixtracklib/common/particles/track_particle.h"
#include "sixtracklib/common/beam_elements/drift/drift.h"
#include "sixtracklib/common/beam_elements/drift/drift_exact.h"

NS(track_status_t) NS(Drift_track)( NS(TrackParticle)* SIXTRL_RESTRICT p,
    const NS(BeDrift) *const SIXTRL_RESTRICT_REF drift )
{
    typedef NS(be_drift_real_t) real_t;

    real_t const xp = p->px * p->rpp;
    real_t const yp = p->py * p->rpp;
    real_t const dzeta = p->rvv -
        ( ( xp * xp + yp * yp ) / ( real_t )2.0 + ( real_t )1.0 );

    p->x    += xp * drift->length;
    p->y    += yp * drift->length;
    p->s    += drift->length;
    p->zeta += dzeta * drift->length;

    return SIXTRL_TRACK_SUCCESS;
}

NS(track_status_t) NS(DriftExact_track)( NS(TrackParticle)* SIXTRL_RESTRICT p,
    const NS(BeDriftExact) *const SIXTRL_RESTRICT_REF drift )
{
    typedef NS(be_drift_real_t) real_t;
    typedef NS(particle_index_t) state_t;

    real_t const delta_plus_1  = p->delta + ( real_t )1.0;
    real_t const delta_plus_1_squ = delta_plus_1 * delta_plus_1;
    real_t const px_squ_py_squ = p->px * p->px +
                                    p->py * p->py;

    if( px_squ_py_squ > delta_plus_1_squ ) p->state = ( state_t )0;

    real_t const lpzi =
        drift->length / sqrt( delta_plus_1_squ - px_squ_py_squ );

    p->x    += p->px * lpzi;
    p->y    += p->py * lpzi;
    p->s    += drift->length;
    p->zeta += p->rvv * drift->length - delta_plus_1 * lpzi;

    return SIXTRL_TRACK_SUCCESS;
}

#endif /* SIXTRACKLIB_COMMON_BE_DRIFT_TRACK_C99_H__ */
/* end: */
