#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/monitor/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(Monitor_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT monitor
) SIXTRL_NOEXCEPT { NS(Monitor_track_particle)( p, monitor ); }

