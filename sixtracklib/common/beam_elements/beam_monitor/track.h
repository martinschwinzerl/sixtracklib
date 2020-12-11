#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_TRACK_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_TRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/track/track_config.h"
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/beam_elements/limit_global_aperture.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleT, class BeamMonitorT >
    SIXTRL_STATIC SIXTRL_FN track_status_t BeamMonitor_track(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT particle,
        SIXTRL_BE_ARGPTR_DEC const BeamMonitorT *const SIXTRL_RESTRICT belem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT;
}

#if !defined( _GPUCODE )
extern "C" {
#endif /* !defined( _GPUCODE ) */
#endif /* defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(BeamMonitor_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT particle,
    SIXTRL_BE_ARGPTR_DEC const NS(BeamMonitor) *const SIXTRL_RESTRICT drift,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* ****                        Implementation                           **** */
/* ************************************************************************* */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleT, class BeamMonitorT >
    SIXTRL_INLINE track_status_t BeamMonitor_track(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const BeamMonitorT *const SIXTRL_RESTRICT belem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT
#else /* defined( __cplusplus ) */
    SIXTRL_INLINE NS(track_status_t) NS(BeamMonitor_track)(
        SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const NS(BeamMonitor) *const SIXTRL_RESTRICT belem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT
#endif /* defined( __cplusplus ) */
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( belem != SIXTRL_NULLPTR );

        #if defined( __cplusplus )
        typedef typename SIXTRL_CXX_NAMESPACE::ParticleTraits<
                ParticleT >::index_t particle_index_t;

        typedef typename SIXTRL_CXX_NAMESPACE::BeamMonitorTraits<
                    BeamMonitorT >::particle_set_t particle_set_t;

        typedef typename SIXTRL_CXX_NAMESPACE::BeamMonitorTraits<
                    BeamMonitorT >::particle_index_t pset_index_t;

        #else /* !defined( __cplusplus ) */
        typedef NS(particle_index_t) particle_index_t;
        typedef NS(ParticleSet)      particle_set_t;
        typedef NS(particle_index_t) pset_index_t;

        #endif /* defined( __cplusplus ) */

        #if defined( __cplusplus )
        SIXTRL_ASSERT( SIXTRL_CXX_NAMESPACE::Type_comp_all_more(
            p->beta0, particle_real_t{ 0 } ) );

        SIXTRL_ASSERT( SIXTRL_CXX_NAMESPACE::Type_comp_all_less_or_equal(
            p->beta0, particle_real_t{ 1 } ) );

        #endif /* defined( __cplusplus ) */

        particle_real_t const xp = p->px * p->rpp;
        particle_real_t const yp = p->py * p->rpp;
        particle_real_t delta_zeta = xp * xp + yp * yp;

        delta_zeta /= ( be_real_t )-2;
        delta_zeta -= ( particle_real_t )1;
        delta_zeta += p->rvv;

        /* delta_zeta = L * ( \beta/\beta0 - ( 1 + ( xp^2 + yp^2 ) / 2 ) ) */
        delta_zeta *= belem->length;

        p->x    += xp * belem->length;
        p->y    += yp * belem->length;
        p->s    += belem->length;
        p->zeta += delta_zeta;

        if( NS(TrackConfig_global_aperture_check_enabled)(
                track_config, belem->length ) )
        {
            NS(LimitGlobalAperture_perform_check)( p, track_config );
        }

        return SIXTRL_TRACK_SUCCESS;
    }

#if defined( __cplusplus )
}

#if !defined( _GPUCODE )
extern "C" {
#endif /* !defined( _GPUCODE ) */

SIXTRL_INLINE ::NS(track_status_t) NS(BeamMonitor_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle)* SIXTRL_RESTRICT particle,
    SIXTRL_BE_ARGPTR_DEC const ::NS(BeamMonitor) *const SIXTRL_RESTRICT belem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig)
        *const SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::BeamMonitor_track( particle, belem, track_config );
}

#if !defined( _GPUCODE )
}
#endif /* !defined( _GPUCODE ) */
#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_TRACK_H__ */
