#ifndef SIXTRACKLIB_COMMON_BE_DRIFT_TRACK_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_DRIFT_TRACK_CXX_HPP__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"
#include "sixtracklib/common/track/definitions.h"

#include "sixtracklib/common/beam_elements/drift/drift_traits.hpp"
#include "sixtracklib/common/beam_elements/drift/drift.hpp"
#include "sixtracklib/common/beam_elements/drift/drift_exact.hpp"
#include "sixtracklib/common/particles/track_particle.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace sixtrack_cxx
{
    template< class PData, class BeData >
    typename track_result_t< PData, BeData,
        SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT >::type
    Drift_track( TrackParticleInterface< PData >& SIXTRL_RESTRICT_REF particle,
        DriftInterface< BeData > const& SIXTRL_RESTRICT_REF drift )
    {
        typedef typename TrackParticleInterface< PData >::real_t real_t;

        real_t const xp = particle.px * particle.rpp;
        real_t const yp = particle.py * particle.rpp;
        real_t const dzeta = particle.rvv -
            ( ( xp * xp + yp * yp ) / ( real_t )2.0 + ( real_t )1.0 );

        particle.x    += xp * drift.length;
        particle.y    += yp * drift.length;
        particle.s    += drift.length;
        particle.zeta += dzeta * drift.length;

        return SIXTRL_CXX_NAMESPACE::TRACK_SUCCESS;
    }

    template< class PData, class BeData >
    typename track_result_t< PData, BeData,
        SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT_EXACT >::type
    DriftExact_track( TrackParticleInterface< PData >& SIXTRL_RESTRICT_REF particle,
        DriftExactInterface< BeData > const& SIXTRL_RESTRICT_REF drift )
    {
        typedef typename TrackParticleInterface< PData >::real_t real_t;
        typedef typename TrackParticleInterface< PData >::int_t  state_t;

        /* Brace yourself, we are in ADL territory */
        using std::sqrt;

        real_t const delta_plus_1  = particle.delta + ( real_t )1.0;
        real_t const delta_plus_1_squ = delta_plus_1 * delta_plus_1;
        real_t const px_squ_py_squ = particle.px * particle.px +
                                     particle.py * particle.py;

        /* Depending on the type, all sort of things can happen if the
         * argument of sqrt() in the calculation of lpzi gets negative.
         * TODO: Determine whether this is a recoverable error
         * TODO: Provide handlers for the different realizations of real_t */

        /* This is a nice-weather approach to handle this problem -> mark the
         * particle as lost as lpzi will become complex */
        if( px_squ_py_squ > delta_plus_1_squ ) particle.state = ( state_t )0;

        real_t const lpzi =
            drift.length / sqrt( delta_plus_1_squ - px_squ_py_squ );

        particle.x    += particle.px * lpzi;
        particle.y    += particle.py * lpzi;
        particle.s    += drift.length;
        particle.zeta += particle.rvv * drift.length - delta_plus_1 * lpzi;

        return SIXTRL_CXX_NAMESPACE::TRACK_SUCCESS;
    }
}

#endif /* SIXTRACKLIB_COMMON_BE_DRIFT_TRACK_CXX_HPP__ */
/* end: */
