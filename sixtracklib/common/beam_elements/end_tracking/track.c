#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/end_tracking/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(EndTracking_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const
        SIXTRL_RESTRICT end_tracking ) SIXTRL_NOEXCEPT {
            NS(EndTracking_track_particle)( p, end_tracking ); }

