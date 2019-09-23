#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_LIMIT_TRACK_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_LIMIT_TRACK_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/beam_elements/limit/limit_rect.h"
    #include "sixtracklib/common/beam_elements/limit/limit_ellipse.h"
    #include "sixtracklib/common/particles.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, host */

SIXTRL_INLINE NS(track_status_t) NS(LimitRect_track)(
    NS(TrackParticle)* SIXTRL_RESTRICT particle,
    const NS(LimitRect) *const SIXTRL_RESTRICT limit )
{
    typedef NS(particle_real_t)  real_t;
    typedef NS(particle_index_t) index_t;

    SIXTRL_ASSERT( particle != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );

    real_t const x = particle->x;
    real_t const y = particle->y;

    index_t const new_state = ( index_t )(
        ( x >= limit->min_x ) && ( x <= limit->max_x ) &&
        ( y >= limit->min_y ) && ( y <= limit->max_y ) );

    particle->state &= new_state;
    return SIXTRL_TRACK_SUCCESS;
}

SIXTRL_INLINE NS(track_status_t) NS(LimitEllipse_track)(
    NS(TrackParticle)* SIXTRL_RESTRICT particles,
    const NS(LimitEllipse) *const SIXTRL_RESTRICT limit )
{
    typedef NS(particle_real_t)  real_t;
    typedef NS(particle_index_t) state_t;

    SIXTRL_ASSERT( particle != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );

    real_t x_squ = particle->x * particle->x;
    real_t temp = particle->y * particle->y;
    temp  *= limit->a_squ;
    x_squ *= limit->b_squ;
    temp  += x_squ;

    particle->state &= ( state_t )( temp <= limit->a_b_squ );
    return SIXTRL_TRACK_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, host */


#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_LIMIT_TRACK_C99_H__ */

/* end: sixtracklib/common/beam_elements/limit/track.h */
