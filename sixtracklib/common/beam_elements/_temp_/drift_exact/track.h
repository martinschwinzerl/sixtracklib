#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXCAT_TRACK_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXCAT_TRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/track/track_config.h"
    #include "sixtracklib/common/particles/particle_unit.h"
    #include "sixtracklib/common/particles/particle_unit_api.h"
    #include "sixtracklib/common/particles/particle_unit_derived_api.h"
    #include "sixtracklib/common/beam_elements/limit_global_aperture.h"
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/beam_elements/drift/drift_api.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleT, class DriftExactT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ObjData_is_particle< ParticleT >() ||
        !SIXTRL_CXX_NAMESPACE::ObjData_is_drift_exact< DriftExactT >(),
         SIXTRL_CXX_NAMESPACE::track_status_t >::type
    DriftExact_track(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT /*p*/,
        SIXTRL_BE_ARGPTR_DEC const DriftExactT *const SIXTRL_RESTRICT /*belem*/,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT /*track_config*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TRACK_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, class DriftExactT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_is_particle< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_is_drift_exact< DriftExactT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    DriftExact_track(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const DriftExactT *const SIXTRL_RESTRICT elem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        typedef typename DriftExactTraits< DriftExactT >::real_t be_real_t;

        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );

        /* temp = px * px */
        real_t temp = st::Particle_px( p );
        temp *= st::Particle_px( p );

        /* temp = py * py + px * px */
        real_t lpzi = st::Particle_py( p );
        lpzi *= st::Particle_py( p );
        temp += lpzi;

        /* delta_plus_one = ( delta + 1 ) */
        real_t delta_plus_one = st::Particle_delta( p );
        delta_plus_one += real_t{ 1 };

        /* lpzi = ( delta_plus_one * delta_plus_one - ( px * px + py * py ) */
        lpzi  = delta_plus_one;
        lpzi *= delta_plus_one;
        lpzi -= temp;

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
            lpzi, real_t{ 0 } ) );

        lpzi = st::sqrt< real_t >( lpzi );

        SIXTRL_ASSERT( st::Type_comp_all_more< real_t >( lpzi, real_t{ 0 } ) );

        /* s += L */
        be_real_t const L = st::DriftExact_length( elem );
        st::arch_status_t status = st::Particle_add_to_s( p, L );

        /* lpzi = L / sqrt( ( delta + 1 )^2 - ( px^2 + py^2 ) ) */
        /* temp = ( delta + 1 ) * lpzi */
        temp = L;
        temp /= lpzi;
        lpzi  = temp;
        temp *= delta_plus_one;

        /* d_zeta = rvv * L - ( delta + 1 ) * lpzi */
        real_t d_zeta = st::Particle_rvv( p );
        d_zeta *= L;
        d_zeta -= temp;
        status |= st::Particle_add_to_zeta( p, d_zeta );

        /* x += lpzi * px */
        temp  = st::Particle_px( p );
        temp *= lpzi;
        status |= st::Particle_add_to_x( p, temp );

        /* y += lpzi * py */
        temp  = st::Particle_py( p );
        temp *= lpzi;
        status |= st::Particle_add_to_y( p, temp );

        if( ::NS(TrackConfig_global_aperture_check_enabled)( track_config, L ) )
        {
            status |= st::LimitGlobalAperture_perform_check( p, track_config );
        }

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        return st::TRACK_SUCCESS;
    }
}

template< class ParticleT, class DriftExactT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::track_status_t
NS(DriftExact_track)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const DriftExactT *const SIXTRL_RESTRICT belem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config )
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_track( p, belem, track_config );
}

#endif /* C++ */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(DriftExact_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT belem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* */
/* ****                        Implementation                           **** */
/* ************************************************************************* */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(track_status_t) NS(DriftExact_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT elem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;
    typedef NS(be_real_t) be_real_t;
    NS(arch_status_t) status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;

    real_t const delta_plus_one = NS(Particle_delta)( p ) + ( real_t )1;
    real_t lpzi = delta_plus_one * delta_plus_one -
                  NS(Particle_px)( p ) * NS(Particle_px)( p ) -
                  NS(Particle_py)( p ) * NS(Particle_py)( p );

    be_real_t const L = NS(DriftExact_length)( elem );
    status = NS(Particle_add_to_s)( p, L );

    SIXTRL_ASSERT( lpzi >= ( real_t )0 );
    lpzi = NS(sqrt)( lpzi );
    SIXTRL_ASSERT( lpzi > ( real_t )0 );
    lpzi = L / lpzi;

    status |= NS(Particle_add_to_x)( p, NS(Particle_px)( p ) * lpzi );
    status |= NS(Particle_add_to_y)( p, NS(Particle_py)( p ) * lpzi );
    status |= NS(Particle_add_to_zeta)(
        p, NS(Particle_rvv)( p ) * L - delta_plus_one * lpzi );

    if( NS(TrackConfig_global_aperture_check_enabled)( track_config, L ) )
    {
        status |= NS(LimitGlobalAperture_perform_check)( p, track_config );
    }

    SIXTRL_ASSERT( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS );
    return ( NS(track_status_t) ) SIXTRL_TRACK_SUCCESS;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXCAT_TRACK_H__ */
