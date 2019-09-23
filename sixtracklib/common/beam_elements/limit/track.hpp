#ifndef SIXTRACKLIB_COMMON_BE_LIMIT_TRACK_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_LIMIT_TRACK_CXX_HPP__

#include "sixtracklib/common/definitions.h"

#include "sixtracklib/common/beam_elements/limit/limit_traits.hpp"
#include "sixtracklib/common/beam_elements/limit/limit_rect.hpp"
#include "sixtracklib/common/beam_elements/limit/limit_ellipse.hpp"
#include "sixtracklib/common/particles/track_particle.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace SIXTRACK_CXX_NAMESPACE
{
    template< class PData, class BeData > typename track_result_t< PData,
        BeData, SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_RECT >::type
    LimitRect_track(
        TrackParticleInterface< PData >& SIXTRL_RESTRICT_REF particle,
        BeLimitRectInterface< BeData > const& SIXTRL_RESTRICT_REF limit )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::TrackParticleInterface< PData > particle_t;
        typedef typename particle_t::real_t real_t;

        typename particle_t::int_t state = particle.state;
        if( state == ( typename particle_t::int_t )0 ) return st::TRACK_SUCCESS;

        state &= ( particle.x >= ( real_t )limit.min_x );
        state &= ( particle.x <= ( real_t )limit.max_x );
        state &= ( particle.y >= ( real_t )limit.min_y );
        state &= ( particle.y <= ( real_t )limit.max_y );

        particle.state = state;
        return st::TRACK_SUCCESS;
    }

    template< class PData, class BeData > typename track_result_t< PData,
        BeData, SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_ELLIPSE >::type
    LimitEllipse_track(
        TrackParticleInterface< PData >& SIXTRL_RESTRICT_REF particle,
        BeLimitEllipseInterface< BeData > const& SIXTRL_RESTRICT_REF limit )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::TrackParticleInterface< PData > particle_t;
        typedef typename particle_t::real_t real_t;
        typedef typename particle_t::int_t  state_t;

        if( particle.state == ( state_t )0 ) return st::TRACK_SUCCESS;

        real_t temp = particle.x * particle.x * limit.b_squ;
        temp += particle.y * particle.y * limit.a_squ;

        particle.state &= ( state_t )( temp <= ( real_t )limit.a_b_squ );
        return st::TRACK_SUCCESS;
    }
}

#endif /* SIXTRACKLIB_COMMON_BE_LIMIT_TRACK_CXX_HPP__ */

/* end: sixtracklib/common/beam_elements/limit/track.hpp */
