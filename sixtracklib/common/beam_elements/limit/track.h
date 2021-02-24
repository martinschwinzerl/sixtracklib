#ifndef SIXTRL_COMMON_BE_LIMIT_TRACK_C99_H__
#define SIXTRL_COMMON_BE_LIMIT_TRACK_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/limit/limit_rect.h"
    #include "sixtracklib/common/beam_elements/limit/limit_ellipse.h"
    #include "sixtracklib/common/beam_elements/limit/limit_rect_ellipse.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN void NS(LimitRect_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(LimitEllipse_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(LimitRectEllipse_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(LimitGlobal_track_particle_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const x_min, NS(particle_real_type) const x_max,
    NS(particle_real_type) const y_min, NS(particle_real_type) const y_max
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(LimitGlobal_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(LimitRect_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(LimitEllipse_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(LimitRectEllipse_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(LimitGlobal_track_particle_detailed_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const x_min, NS(particle_real_type) const x_max,
    NS(particle_real_type) const y_min, NS(particle_real_type) const y_max
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(LimitGlobal_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

/* ========================================================================= */
/* =====        Implementation of Inline functions and methods         ===== */
/* ========================================================================= */

SIXTRL_INLINE void NS(LimitRect_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT {
    NS(particle_index_type) const updated_state = ( NS(particle_index_type) )(
        ( NS(Particle_x)( p ) >= NS(LimitRect_x_min)( limit ) ) &&
        ( NS(Particle_x)( p ) <= NS(LimitRect_x_max)( limit ) ) &&
        ( NS(Particle_y)( p ) >= NS(LimitRect_y_min)( limit ) ) &&
        ( NS(Particle_y)( p ) <= NS(LimitRect_y_max)( limit ) ) );

    NS(Particle_keep_active_if_not_lost)( p, updated_state );
}

SIXTRL_INLINE void NS(LimitEllipse_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT {
    NS(particle_real_type) const a_b_r_squ =
        NS(Particle_x)( p ) * NS(Particle_x)( p ) * NS(LimitEllipse_b_squ)( e ) +
        NS(Particle_y)( p ) * NS(Particle_y)( p ) * NS(LimitEllipse_a_squ)( e );

    NS(Particle_keep_active_if_not_lost)( p, ( NS(particle_index_type) )(
        a_b_r_squ <= NS(LimitEllipse_a_b_squ)( e ) ) );
}

SIXTRL_INLINE void NS(LimitRectEllipse_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT {
    NS(particle_index_type) const updated_state = (
        ( NS(Particle_x)( p ) >= -( NS(LimitRectEllipse_x_max)( limit ) ) ) &&
        ( NS(Particle_x)( p ) <= +( NS(LimitRectEllipse_x_max)( limit ) ) ) &&
        ( NS(Particle_y)( p ) >= -( NS(LimitRectEllipse_y_max)( limit ) ) ) &&
        ( NS(Particle_y)( p ) <= +( NS(LimitRectEllipse_y_max)( limit ) ) ) &&
        ( NS(LimitRectEllipse_a_b_squ)( limit ) >=
          ( NS(Particle_x)( p ) * NS(Particle_x)( p ) *
            NS(LimitRectEllipse_b_squ)( limit ) +
            NS(Particle_y)( p ) * NS(Particle_y)( p ) *
            NS(LimitRectEllipse_a_squ)( limit ) ) ) );

    NS(Particle_keep_active_if_not_lost)( p, updated_state );
}

SIXTRL_STATIC SIXTRL_FN void NS(LimitGlobal_track_particle_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const x_min, NS(particle_real_type) const x_max,
    NS(particle_real_type) const y_min, NS(particle_real_type) const y_max
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( x_min <= x_max );
    SIXTRL_ASSERT( y_min <= y_max );

    NS(Particle_keep_active_if_not_lost)( p, ( NS(particle_index_type) )(
            ( NS(Particle_x)( p ) >= x_min ) &&
            ( NS(Particle_x)( p ) <= x_max ) &&
            ( NS(Particle_y)( p ) >= y_min ) &&
            ( NS(Particle_y)( p ) <= y_max ) ) );
}

SIXTRL_INLINE void NS(LimitGlobal_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_type) real_type;
    NS(LimitGlobal_track_particle_detailed)( p,
        #if defined( SIXTRL_APERTURE_X_LIMIT )
        -( ( real_type )SIXTRL_APERTURE_X_LIMIT ),
           ( real_type )SIXTRL_APERTURE_X_LIMIT,
        #else /* defined( SIXTRL_APERTURE_X_LIMIT )  */
        ( real_type )-1.0, ( real_type )+1.0,
        #endif /* defined( SIXTRL_APERTURE_X_LIMIT ) */

        #if defined( SIXTRL_APERTURE_Y_LIMIT )
        -( ( real_type )SIXTRL_APERTURE_Y_LIMIT ),
           ( real_type )SIXTRL_APERTURE_Y_LIMIT
        #else /* defined( SIXTRL_APERTURE_Y_LIMIT )  */
        ( real_type )-1.0, ( real_type )+1.0
        #endif /* defined( SIXTRL_APERTURE_Y_LIMIT ) */
    );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, host */
#endif /* SIXTRL_COMMON_BE_LIMIT_TRACK_C99_H__ */
