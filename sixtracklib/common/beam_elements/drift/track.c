#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(Drift_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT drift
) SIXTRL_NOEXCEPT { NS(Drift_track_particle)( p, drift ); }

void NS(DriftExact_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT drift
) SIXTRL_NOEXCEPT { NS(DriftExact_track_particle)( p, drift ); }
