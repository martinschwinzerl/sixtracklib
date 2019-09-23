#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_TRACK_H_C99__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_TRACK_H_C99__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/track/definitions.h"
#include "sixtracklib/common/beam_elements/multipole/definitions.h"
#include "sixtracklib/common/beam_elements/multipole/multipole.h"
#include "sixtracklib/common/beam_elements/multipole/multipole_api.h"
#include "sixtracklib/common/particles/track_particle.h"
#include "sixtracklib/common/internal/objects_type_id.h"

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_INLINE NS(track_status_t) NS(Multipole_track)(
    NS(TrackParticle)* SIXTRL_RESTRICT particle,
    const NS(Multipole) *const SIXTRL_RESTRICT multipole )
{
    typedef NSTrackParticle)         particle_t;
    typedef NS(particle_real_t)      real_t;
    typedef NS(be_multipole_real_t)  mp_real_t;
    typedef NS(be_multipole_order_t) mp_order_t;

    SIXTRL_ASSERT( multipole != nullptr );
    SIXTRL_ASSERT( particle  != nullptr );

    mp_order_t index_x = NS(Multipole_get_order)( multipole ) * ( mp_order_t )2u;
    mp_order_t index_y = index_x + ( mp_order_t )1u;

    real_t dpx = NS(Multipole_get_const_bal)( multipole, index_x );
    real_t dpy = NS(Multipole_get_const_bal)( multipole, index_y );

    while( index_x >= ( mp_order_t )2u )
    {
        real_t zre = dpx * particle.x - dpy * particle.y;
        real_t zim = dpx * particle.y + dpy * particle.x;

        index_x -= 2;
        index_y -= 2;

        zre += NS(Multipole_get_const_bal)( multipole, index_x );
        zim += NS(Multipole_get_const_bal)( multipole, index_y );

        dpx = zre;
        dpy = zim;
    }

    dpx *= -particle->chi;
    dpy *=  particle->chi;

    if( ( multipole->hxl != ( real_t )0.0 ) ||
        ( multipole->hyl != ( real_t )0.0 ) )
    {
        real_t const hxlx = particle->x * multipole->hxl;
        real_t const hyly = particle->y * multipole->hyl;

        particle->zeta += particle->chi * ( hyly - hxlx );

        real_t const delta_plus_1 = particle->delta + ( real_t )1.0;

        dpx += delta_plus_1 * hxlx;
        dpy -= delta_plus_1 * hyly;

        if( multipole->length > ( real_t )0.0 )
        {
            real_t delta_p = particle->chi * hxlx;
            delta_p *= NS(Multipole_get_const_bal)( multipole, 0 );
            delta_p /= multipole->length;
            dpx -= delta_p;

            delta_p  = particle->chi * hyly;
            delta_p *= NS(Multipole_get_const_bal)( multipole, 1 );
            delta_p /= multipole->length;
            dpy += delta_p;
        }
    }

    particle->px += dpx;
    particle->py += dpy;

    return SIXTRL_TRACK_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_TRACK_H_C99__ */

/* end: sixtracklib/common/beam_elements/multipole/track.h */

