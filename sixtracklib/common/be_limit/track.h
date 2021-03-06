#ifndef SIXTRL_COMMON_BE_LIMIT_TRACK_C99_H__
#define SIXTRL_COMMON_BE_LIMIT_TRACK_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/particles.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, host */

struct NS(LimitRect);
struct NS(LimitEllipse);

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(Track_particle_limit_rect)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx, SIXTRL_BE_ARGPTR_DEC
    const struct NS(LimitRect) *const SIXTRL_RESTRICT limit );

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(Track_particle_limit_ellipse)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx, SIXTRL_BE_ARGPTR_DEC
    const struct NS(LimitEllipse) *const SIXTRL_RESTRICT limit );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/be_limit/be_limit_rect.h"
    #include "sixtracklib/common/be_limit/be_limit_ellipse.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, host */

SIXTRL_INLINE NS(track_status_t) NS(Track_particle_limit_rect)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit )
{
    typedef NS(particle_real_t)  real_t;
    typedef NS(particle_index_t) index_t;

    real_t const x = NS(Particles_get_x_value)( particles, particle_idx );
    real_t const y = NS(Particles_get_y_value)( particles, particle_idx );

    index_t const new_state = ( index_t )(
        ( x >= NS(LimitRect_get_min_x)( limit ) ) &&
        ( x <= NS(LimitRect_get_max_x)( limit ) ) &&
        ( y >= NS(LimitRect_get_min_y)( limit ) ) &&
        ( y <= NS(LimitRect_get_max_y)( limit ) ) );

    NS(Particles_update_state_value_if_not_already_lost)(
        particles, particle_idx, new_state );

    return SIXTRL_TRACK_SUCCESS;
}

SIXTRL_INLINE NS(track_status_t) NS(Track_particle_limit_ellipse)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT limit )
{
    NS(particle_real_t) temp = NS(Particles_get_x_value)(
        particles, particle_idx );

    NS(particle_real_t) y_squ = NS(Particles_get_y_value)(
        particles, particle_idx );

    temp *= temp; /* temp = x² */
    temp *= NS(LimitEllipse_get_y_half_axis_squ)( limit ); /* temp = x² * b² */
    
    y_squ *= y_squ; /* y_squ = y² */
    y_squ *= NS(LimitEllipse_get_x_half_axis_squ)( limit ); /*y_squ = y² * a²*/

    temp += y_squ; /* temp = x² * b² + y² * a² */

    NS(Particles_update_state_value_if_not_already_lost)( particles,
        particle_idx, ( NS(particle_index_t) )( temp <=
            NS(LimitEllipse_get_half_axes_product_squ)( limit ) ) );

    return SIXTRL_TRACK_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, host */

#endif /* SIXTRL_COMMON_BE_LIMIT_TRACK_C99_H__ */

/* end: sixtracklib/common/be_limit/track.h */
