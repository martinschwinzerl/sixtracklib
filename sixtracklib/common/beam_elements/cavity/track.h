#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_TRACK_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_TRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/track/track_config.h"
    #include "sixtracklib/common/particles/particle_unit.h"
    #include "sixtracklib/common/particles/particle_unit_derived_api.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity.hpp"
    #include "sixtracklib/common/beam_elements/cavity/cavity_api.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/physics_constants.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleT, class CavityT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() ||
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    Cavity_track( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT /*p*/,
        SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT /*elem*/,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT /*track_config*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TRACK_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    Cavity_track( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT elem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT /*track_config*/ )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::ParticleTraits< ParticleT >::real_t real_t;

        real_t temp = real_t{ 2 };
        temp *= st::MathConst_pi_for_particle( p );
        temp *= st::PhysConst_clight_for_particle( p );
        temp *= st::Cavity_frequency( elem );
        temp *= st::Particle_tau( p );

        real_t phase = st::MathConst_deg2rad_for_particle( p );
        phase *= st::Cavity_lag( elem );
        phase -= temp;

        real_t d_energy = st::Particle_charge( p );
        d_energy *= st::Cavity_voltage( elem );
        d_energy *= st::sin< real_t >( phase );

        st::arch_status_t const status =
            st::Particle_add_to_energy( p, d_energy );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;

        return st::TRACK_SUCCESS;
    }
}

template< class ParticleT, class CavityT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_track)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const CavityT *const SIXTRL_RESTRICT elem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
        SIXTRL_RESTRICT track_config )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_track( p, elem, track_config );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(Cavity_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT particle,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT elem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(track_status_t) NS(Cavity_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT elem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT /*track_config*/ ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;

    real_t const phase = NS(MathConst_deg2rad)() * NS(Cavity_lag)( elem ) -
        ( real_t )2 * NS(MathConst_pi)() * NS(PhysConst_clight)() *
        NS(Cavity_frequency)( elem ) * NS(Particle_tau)( p );

    real_t const d_energy = NS(Particle_charge)( p ) *
        NS(Cavity_voltage)( elem ) * NS(sin)( phase );

    NS(arch_status_t) const status = NS(Particle_add_to_energy)( p, d_energy );
    SIXTRL_ASSERT( status == NS(ARCH_STATUS_SUCCESS) );
    ( void )status;

    return ( NS(track_status_t) )SIXTRL_TRACK_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_TRACK_H__ */
