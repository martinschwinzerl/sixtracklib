#ifndef SIXTRL_COMMON_BEAM_ELEMENTS_DIPEDGE_TRACK_C99_H__
#define SIXTRL_COMMON_BEAM_ELEMENTS_DIPEDGE_TRACK_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/dipedge/dipedge.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN void NS(DipoleEdge_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(DipoleEdge) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )
    SIXTRL_EXTERN SIXTRL_HOST_FN void NS(DipoleEdge_track_particle_ext)(
        SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const NS(DipoleEdge) *const SIXTRL_RESTRICT elem
    ) SIXTRL_NOEXCEPT;
#endif /* !defined( _GPUCODE ) */

/* ========================================================================= */
/* =====        Implementation of Inline functions and methods         ===== */
/* ========================================================================= */

SIXTRL_INLINE void NS(DipoleEdge_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(DipoleEdge) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT {
    NS(Particle_add_to_px)( p, NS(DipoleEdge_r21)( e ) * NS(Particle_x)( p ) );
    NS(Particle_add_to_py)( p, NS(DipoleEdge_r43)( e ) * NS(Particle_y)( p ) );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, host */
#endif /* SIXTRL_COMMON_BEAM_ELEMENTS_DIPEDGE_TRACK_C99_H__ */
