#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beamfields/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(SCCoasting_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT { NS(SCCoasting_track_particle)( p, sc ); }

void NS(SCQGaussProfile_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT sc
) SIXTRL_NOEXCEPT { NS(SCQGaussProfile_track_particle)( p, sc ); }

