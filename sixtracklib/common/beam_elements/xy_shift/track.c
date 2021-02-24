#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/xy_shift/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(XYShift_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT { NS(XYShift_track_particle)( p, elem ); }
