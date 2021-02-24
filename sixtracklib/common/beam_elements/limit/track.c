#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/limit/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(LimitRect_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { NS(LimitRect_track_particle)( p, limit ); }

void NS(LimitEllipse_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { NS(LimitEllipse_track_particle)( p, limit ); }

void NS(LimitRectEllipse_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { NS(LimitRectEllipse_track_particle)( p, limit ); }

void NS(LimitGlobal_track_particle_detailed_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const x_min, NS(particle_real_type) const x_max,
    NS(particle_real_type) const y_min, NS(particle_real_type) const y_max
) SIXTRL_NOEXCEPT { NS(LimitGlobal_track_particle_detailed)(
        p, x_min, x_max, y_min, y_max ); }

void NS(LimitGlobal_track_particle_ext)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
        NS(LimitGlobal_track_particle)( p ); }
