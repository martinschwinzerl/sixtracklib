#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(Cavity_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT cavity
) SIXTRL_NOEXCEPT { NS(Cavity_track_particle)( p, cavity ); }

