#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_TRACK_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_TRACK_CXX_HPP__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/track/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"

#include "sixtracklib/common/beam_elements/cavity/cavity_traits.hpp"
#include "sixtracklib/common/beam_elements/cavity/cavity.hpp"
#include "sixtracklib/common/internal/math_constant_traits.hpp"
#include "sixtracklib/common/internal/phys_constant_traits.hpp"
#include "sixtracklib/common/particles/track_particle.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< class PData, class BeData >
    typename track_result_t< PData, BeData,
            SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_CAVITY >::type
    Cavity_track( TrackParticleInterface< PData >& SIXTRL_RESTRICT_REF particle,
        CavityInterface< BeData > const& SIXTRL_RESTRICT_REF cavity )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef TrackParticleInterface< PData > particle_t;
        typedef typename particle_t::real_t     real_t;

        real_t const K_FACTOR = ( st::MathConstants< real_t >::Two() *
            st::MathConstants< real_t >::Pi() ) /
            st::PhysConstants< real_t >::C0();

        real_t const tau   = particle.zeta / ( particle.beta0 * particle.rvv );
        real_t const phase =
            st::MathConstants< real_t >::Deg2Rad() * cavity.lag -
            K_FACTOR * tau * cavity.frequency;

        particle.addEnergy( particle.q0  * particle.charge_ratio *
                sin( phase ) * cavity.voltage );

        return st::TRACK_SUCCESS;
    }
}

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_TRACK_CXX_HPP__ */

/* end: */
