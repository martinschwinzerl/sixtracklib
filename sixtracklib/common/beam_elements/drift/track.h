#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_TRACK_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_TRACK_H__

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
    /* --------------------------------------------------------------------- */
    /* Drift: track_type == SIXTRL_BE_DRIFT_TRACK_TYPE_SIMPLE */

    template< class ParticleT, class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(), track_status_t >::type
    Drift_track_simple(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const DriftT *const SIXTRL_RESTRICT elem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        typedef typename DriftTraits< DriftT >::real_t be_real_t;

        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( st::Drift_track_type( elem ) ==
                       st::BE_DRIFT_TRACK_TYPE_SIMPLE );

        SIXTRL_ASSERT( st::Type_comp_all_more(
            st::Particle_beta0( p ), real_t{ 0 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal(
            st::Particle_beta0( p ), real_t{ 1 } ) );

        real_t const xp = st::Particle_px( p ) * st::Particle_rpp( p );
        real_t const yp = st::Particle_py( p ) * st::Particle_rpp( p );
        be_real_t const L = st::Drift_length( elem );

        real_t d_zeta = xp * xp;
        d_zeta += yp * yp;
        d_zeta /= real_t{ -2 };
        d_zeta -= real_t{ 1 };
        d_zeta += st::Particle_rvv( p );
        /* delta_zeta = L * ( \beta/\beta0 - ( 1 + ( xp^2 + yp^2 ) / 2 ) ) */
        d_zeta *= L;

        st::Particle_add_to_x( p, xp * L );
        st::Particle_add_to_y( p, yp * L );
        st::Particle_add_to_s( p, L );
        st::Particle_add_to_zeta( p, d_zeta );

        if( NS(TrackConfig_global_aperture_check_enabled)( track_config, L ) )
        {
            NS(LimitGlobalAperture_perform_check)( p, track_config );
        }

        return st::TRACK_SUCCESS;
    }

    /* --------------------------------------------------------------------- */
    /* Drift: track_type == SIXTRL_BE_DRIFT_TRACK_TYPE_EXACT */

    template< class ParticleT, class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(), track_status_t >::type
    Drift_track_exact(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const DriftT *const SIXTRL_RESTRICT elem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        typedef typename DriftTraits< DriftT >::real_t be_real_t;

        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( st::Drift_track_type( elem ) ==
                       st::BE_DRIFT_TRACK_TYPE_EXACT );

        SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
            st::Particle_beta0( p ), real_t{ 0 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< real_t >(
            st::Particle_beta0( p ), real_t{ 1 } ) );

        real_t one_plus_delta = st::Particle_delta( p );
        one_plus_delta += real_t{ 1 };

        real_t temp = st::Particle_px( p );
        temp *= temp;

        real_t lpzi = st::Particle_py( p );
        lpzi *= lpzi;
        lpzi += temp;

        temp  = one_plus_delta;
        temp *= one_plus_delta;
        temp -= lpzi;

        SIXTRL_ASSERT( st::Type_comp_all_more< real_t >( temp, real_t{ 0 } ) );
        be_real_t const L = st::Drift_length( elem );
        st::Particle_add_to_s( p, L );

        lpzi  = real_t{ 1 };
        lpzi /= st::sqrt< real_t >( temp );
        lpzi *= L;

        temp  = lpzi;
        temp *= st::Particle_px( p );
        st::Particle_add_to_x( p, temp );

        temp  = lpzi;
        temp *= st::Particle_py( p );
        st::Particle_add_to_y( p, temp );

        temp  = lpzi;
        temp *= one_plus_delta;

        real_t d_zeta = st::Particle_rvv( p );
        d_zeta *= L;
        d_zeta -= temp;
        st::Particle_add_to_zeta( p, d_zeta );

        if( NS(TrackConfig_global_aperture_check_enabled)( track_config, L ) )
        {
            NS(LimitGlobalAperture_perform_check)( p, track_config );
        }

        return st::TRACK_SUCCESS;
    }

    /* --------------------------------------------------------------------- */
    /* Drift_track: */

    template< class ParticleT, class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() ||
        !SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
         SIXTRL_CXX_NAMESPACE::track_status_t >::type
    Drift_track(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
            SIXTRL_RESTRICT SIXTRL_UNUSED( p ),
        SIXTRL_BE_ARGPTR_DEC const DriftT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( belem ),
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( track_config ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TRACK_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
         SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
         SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
         SIXTRL_CXX_NAMESPACE::track_status_t >::type
    Drift_track(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const DriftT *const SIXTRL_RESTRICT elem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        st::track_status_t track_status = st::TRACK_STATUS_GENERAL_FAILURE;

        switch( st::Drift_track_type( elem ) )
        {
            case st::BE_DRIFT_TRACK_TYPE_SIMPLE:
            {
                track_status = st::Drift_track_simple( p, elem, track_config );
                break;
            }

            case st::BE_DRIFT_TRACK_TYPE_EXACT:
            {
                track_status = st::Drift_track_exact( p, elem, track_config );
                break;
            }

            default:
            {
                track_status = st::TRACK_STATUS_GENERAL_FAILURE;
            }
        };

        return track_status;
    }

}

template< class ParticleT, class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::track_status_t
NS(Drift_track_simple)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const DriftT *const SIXTRL_RESTRICT belem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config )
{
    return SIXTRL_CXX_NAMESPACE::Drift_track_simple( p, belem, track_config );
}

template< class ParticleT, class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::track_status_t
NS(Drift_track_exact)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const DriftT *const SIXTRL_RESTRICT belem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config )
{
    return SIXTRL_CXX_NAMESPACE::Drift_track_exact( p, belem, track_config );
}

template< class ParticleT, class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::track_status_t
NS(Drift_track)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const DriftT *const SIXTRL_RESTRICT belem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config )
{
    return SIXTRL_CXX_NAMESPACE::Drift_track( p, belem, track_config );
}

#endif /* C++ */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(Drift_track_simple)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT belem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(Drift_track_exact)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT belem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(Drift_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT belem,
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

SIXTRL_INLINE NS(track_status_t) NS(Drift_track_simple)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT elem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Drift_track_type)( elem ) == (
        NS(be_drift_track_type_t) )SIXTRL_BE_DRIFT_TRACK_TYPE_SIMPLE );

    SIXTRL_ASSERT( NS(Particle_beta0)( p ) >= ( real_t )0 );
    SIXTRL_ASSERT( NS(Particle_beta0)( p ) <= ( real_t )1 );

    real_t const xp = NS(Particle_px)( p ) * NS(Particle_rpp)( p );
    real_t const yp = NS(Particle_py)( p ) * NS(Particle_rpp)( p );

    NS(Particle_add_to_x)( p, xp * NS(Drift_length)( elem ) );
    NS(Particle_add_to_y)( p, yp * NS(Drift_length)( elem ) );
    NS(Particle_add_to_s)( p, NS(Drift_length)( elem ) );
    NS(Particle_add_to_zeta)( p, NS(Drift_length)( elem ) *
        ( NS(Particle_rvv)( p ) - ( real_t )1 - (
            ( xp * xp + yp * yp ) / ( real_t )2 ) ) );

    if( NS(TrackConfig_global_aperture_check_enabled)(
            track_config, NS(Drift_length)( elem ) ) )
    {
        NS(LimitGlobalAperture_perform_check)( p, track_config );
    }

    return ( NS(track_status_t) )SIXTRL_TRACK_SUCCESS;
}

SIXTRL_INLINE NS(track_status_t) NS(Drift_track_exact)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT elem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;
    typedef NS(be_real_t) be_real_t;

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Drift_track_type)( elem ) == ( NS(be_drift_track_type_t)
                       )SIXTRL_BE_DRIFT_TRACK_TYPE_EXACT );

    SIXTRL_ASSERT( NS(Particle_beta0)( p ) >= ( real_t )0 );
    SIXTRL_ASSERT( NS(Particle_beta0)( p ) <= ( real_t )1 );

    be_real_t const L = NS(Drift_length)( elem );
    real_t const one_plus_delta = NS(Particle_delta)( p ) + ( real_t )1;
    real_t const px = NS(Particle_px)( p );
    real_t const py = NS(Particle_py)( p );

    real_t lpzi = one_plus_delta * one_plus_delta - ( px * px + py * py );
    real_t d_zeta = NS(Particle_rvv)( p ) * L;

    SIXTRL_ASSERT( lpzi >= ( real_t )0 );

    lpzi    = L / NS(sqrt)( lpzi );
    d_zeta -= one_plus_delta * lpzi;

    NS(Particle_add_to_s)( p, L );
    NS(Particle_add_to_x)( p, lpzi * px );
    NS(Particle_add_to_y)( p, lpzi * py );
    NS(Particle_add_to_zeta)( p, d_zeta );

    if( NS(TrackConfig_global_aperture_check_enabled)( track_config, L ) )
    {
        NS(LimitGlobalAperture_perform_check)( p, track_config );
    }

    return ( NS(track_status_t) )SIXTRL_TRACK_SUCCESS;
}

SIXTRL_INLINE NS(track_status_t) NS(Drift_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT elem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    NS(track_status_t) track_status = ( NS(be_drift_track_type_t)
        )SIXTRL_TRACK_STATUS_GENERAL_FAILURE;

    switch( NS(Drift_track_type)( elem ) )
    {
        case SIXTRL_BE_DRIFT_TRACK_TYPE_SIMPLE:
        {
            track_status = NS(Drift_track_simple)( p, elem, track_config );
            break;
        }

        case SIXTRL_BE_DRIFT_TRACK_TYPE_EXACT:
        {
            track_status = NS(Drift_track_exact)( p, elem, track_config );
            break;
        }

        default:
        {
            track_status = ( NS(track_status_t)
                )SIXTRL_TRACK_STATUS_GENERAL_FAILURE;
        }
    };

    return track_status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_TRACK_H__ */
