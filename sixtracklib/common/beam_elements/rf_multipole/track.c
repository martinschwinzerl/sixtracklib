#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/rf_multipole/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(RFMultipole_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT { NS(RFMultipole_track_particle)( p, elem ); }

