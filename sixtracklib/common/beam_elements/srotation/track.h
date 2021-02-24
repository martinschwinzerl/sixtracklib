#ifndef SIXTRACKL_COMMON_BEAM_ELEMENTS_SROTATION_TRACK_C99_HEADER_H__
#define SIXTRACKL_COMMON_BEAM_ELEMENTS_SROTATION_TRACK_C99_HEADER_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/srotation.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN void NS(SRotation_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const struct NS(SRotation) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )
    SIXTRL_EXTERN SIXTRL_HOST_FN void NS(SRotation_track_particle_ext)(
        SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const struct NS(SRotation) *const SIXTRL_RESTRICT e
    ) SIXTRL_NOEXCEPT;
#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */
/* =====        Implementation of Inline functions and methods         ===== */
/* ========================================================================= */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE void NS(SRotation_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const struct NS(SRotation) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_type;

    real_type const sin_z = ( real_type )NS(SRotation_sin_z)( e );
    real_type const cos_z = ( real_type )NS(SRotation_cos_z)( e );

    real_type const x_hat  = cos_z * NS(Particle_x)( p ) +
                             sin_z * NS(Particle_y)( p );

    real_type const px_hat = cos_z * NS(Particle_px)( p ) +
                             sin_z * NS(Particle_py)( p );

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( e != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(abs)( cos_z ) <= ( real_type )1. );
    SIXTRL_ASSERT( NS(abs)( sin_z ) <= ( real_type )1. );
    SIXTRL_ASSERT( NS(Type_comp_all_are_close)(
        cos_z * cos_z + sin_z * sin_z, ( real_type)1.,
            ( real_type )0., ( real_type )1e-12 ) );

    NS(Particle_scale_y)( p, cos_z );
    NS(Particle_subtract_from_y)( p, sin_z * NS(Particle_x)( p ) );
    NS(Particle_set_x)( p, x_hat );

    NS(Particle_scale_py)( p, cos_z );
    NS(Particle_subtract_from_py)( p, sin_z * NS(Particle_px)( p ) );
    NS(Particle_set_px)( p, px_hat );
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKL_COMMON_BEAM_ELEMENTS_SROTATION_TRACK_C99_HEADER_H__ */
