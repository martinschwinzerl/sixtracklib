#ifndef SIXTRACKLIB_COMMON_BE_DIPOLE_EDGE_TRACK_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_DIPOLE_EDGE_TRACK_CXX_HPP__

#include "sixtracklib/sixtracklib.hpp"

#include "sixtracklib/common/beam_elements/dipedge/dipedge.hpp"
#include "sixtracklib/common/beam_elements/dipedge/dipedge_traits.hpp"
#include "sixtracklib/common/particles/track_particle.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< class PData, class BeData >
    typename track_result_t< PData, BeData,
        SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DIPEDGE >::type
    DipoleEdge_track(
        TrackParticleInterface< PData >& SIXTRL_RESTRICT_REF particle,
        DipoleEdgeInterface< BeData > const& SIXTRL_RESTRICT_REF dipedge )
    {
        particle.px += particle.x * dipedge.r21;
        particle.py += particle.y * dipedge.r43;

        return SIXTRL_CXX_NAMESPACE::TRACK_SUCCESS;
    }
}

#endif /* SIXTRACKLIB_COMMON_BE_DIPOLE_EDGE_TRACK_CXX_HPP__ */

/* end: */
