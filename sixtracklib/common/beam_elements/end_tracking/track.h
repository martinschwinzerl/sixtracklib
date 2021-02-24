#ifndef SIXTRACKL_COMMON_BEAM_ELEMENTS_END_TRACKING_TRACK_C99_HEADER_H__
#define SIXTRACKL_COMMON_BEAM_ELEMENTS_END_TRACKING_TRACK_C99_HEADER_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/end_tracking/end_tracking.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN void NS(EndTracking_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )
SIXTRL_EXTERN SIXTRL_HOST_FN void NS(EndTracking_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;
#endif /* !defined( _GPUCODE ) */

SIXTRL_INLINE void NS(EndTracking_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( NS(Particle_is_active)( p ) );
    NS(Particle_set_at_element)( p, NS(EndTracking_next_at_element)( elem ) ); }

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKL_COMMON_BEAM_ELEMENTS_END_TRACKING_TRACK_C99_HEADER_H__ */
