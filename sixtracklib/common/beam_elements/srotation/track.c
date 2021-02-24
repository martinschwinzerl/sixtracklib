#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(SRotation_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT { NS(SRotation_track_particle)( p, elem ); }
