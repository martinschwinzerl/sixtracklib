#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/dipedge/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(DipoleEdge_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(DipoleEdge) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT { NS(DipoleEdge_track_particle)( p, elem ); }
