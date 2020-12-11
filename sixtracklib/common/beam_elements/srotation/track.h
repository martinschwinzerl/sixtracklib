#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_TRACK_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_TRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/track/track_config.h"
    #include "sixtracklib/common/particles/particle_unit_api.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation_api.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleT, class SRotationT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() ||
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    SRotation_track(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT /* particle */,
        SIXTRL_BE_ARGPTR_DEC const SRotationT *const SIXTRL_RESTRICT /* elem */,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT /* track_config */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TRACK_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    SRotation_track(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const SRotationT *const SIXTRL_RESTRICT elem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT /*track_config*/ )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );

        typedef typename st::ParticleTraits< ParticleT >::real_t real_t;

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< typename
            st::SRotationTraits< SRotationT >::real_t >( st::SRotation_cos_z(
            elem ), typename st::SRotationTraits< SRotationT >::real_t{ -1 } ) );

        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< typename
            st::SRotationTraits< SRotationT >::real_t >( st::SRotation_cos_z(
            elem ), typename st::SRotationTraits< SRotationT >::real_t{ +1 } ) );

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< typename
            st::SRotationTraits< SRotationT >::real_t >( st::SRotation_sin_z(
            elem ), typename st::SRotationTraits< SRotationT >::real_t{ -1 } ) );

        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< typename
            st::SRotationTraits< SRotationT >::real_t >( st::SRotation_sin_z(
            elem ), typename st::SRotationTraits< SRotationT >::real_t{ +1 } ) );

        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< typename
            st::SRotationTraits< SRotationT >::real_t >( st::abs< typename
                st::SRotationTraits< SRotationT >::real_t >(
                st::SRotation_cos_z( elem ) * st::SRotation_cos_z( elem ) +
                st::SRotation_sin_z( elem ) * st::SRotation_sin_z( elem ) -
                typename st::SRotationTraits< SRotationT >::real_t{ 1 } ),
                std::numeric_limits< typename st::SRotationTraits< SRotationT
                    >::real_t >::epsilon() * typename st::SRotationTraits<
                        SRotationT >::real_t{ 10 } ) );

        /* x_rot = cos_z * x + sin_z * y */
        real_t temp = st::Particle_y( p );
        temp *= st::SRotation_sin_z( elem );

        real_t saved_coord   = st::Particle_x( p );
        real_t updated_coord = saved_coord;
        updated_coord *= st::SRotation_cos_z( elem );
        updated_coord += temp;
        st::arch_status_t status = st::Particle_set_x( p, updated_coord );

        /* y_rot = -sin_z * x + cos_z * y */
        temp  = saved_coord;
        temp *= st::SRotation_sin_z( elem );
        updated_coord  = st::Particle_y( p );
        updated_coord *= st::SRotation_cos_z( elem );
        updated_coord -= temp;
        status |= st::Particle_set_y( p, updated_coord );

        /* px_rot = cos_z * px + sin_z * py */
        temp = st::Particle_py( p );
        temp *= st::SRotation_sin_z( elem );

        saved_coord   = st::Particle_px( p );
        updated_coord = saved_coord;
        updated_coord *= st::SRotation_cos_z( elem );
        updated_coord += temp;
        status |= st::Particle_set_x( p, updated_coord );

        /* py_rot = -sin_z * px + cos_z * py */
        temp  = saved_coord;
        temp *= st::SRotation_sin_z( elem );
        updated_coord  = st::Particle_py( p );
        updated_coord *= st::SRotation_cos_z( elem );
        updated_coord -= temp;
        status |= st::Particle_set_py( p, updated_coord );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;

        return st::TRACK_SUCCESS;
    }
}

template< class ParticleT, class SRotationT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
    SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
    SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
    SIXTRL_CXX_NAMESPACE::track_status_t >::type
NS(SRotation_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const SRotationT *const SIXTRL_RESTRICT elem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
        SIXTRL_RESTRICT track_config )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_track( p, elem, track_config );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(SRotation_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT particle,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT elem,
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

SIXTRL_INLINE NS(track_status_t) NS(SRotation_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT elem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
            SIXTRL_RESTRICT /* track_config */ ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );

    typedef NS(particle_real_t) real_t;

    SIXTRL_ASSERT( NS(SRotation_cos_z)( elem ) >= ( NS(be_real_t) )-1 );
    SIXTRL_ASSERT( NS(SRotation_cos_z)( elem ) <= ( NS(be_real_t) )+1 );
    SIXTRL_ASSERT( NS(SRotation_sin_z)( elem ) >= ( NS(be_real_t) )-1 );
    SIXTRL_ASSERT( NS(SRotation_sin_z)( elem ) <= ( NS(be_real_t) )+1 );
    SIXTRL_ASSERT( NS(abs)(
        NS(SRotation_cos_z)( elem ) * NS(SRotation_cos_z)( elem ) +
        NS(SRotation_sin_z)( elem ) * NS(SRotation_sin_z)( elem ) -
        ( NS(be_real_t) )1 ) <= ( NS(be_real_t) )1e-14 );

    /* x_rot = cos_z * x + sin_z * y */
    real_t x_coord_rot = NS(Particle_x)( p ) * NS(SRotation_cos_z)( elem ) +
                         NS(Particle_y)( p ) * NS(SRotation_sin_z)( elem );

    /* y_rot = -sin_z * x + cos_z * y */
    NS(arch_status_t) status = NS(Particle_set_y)( p,
        NS(Particle_y)( p ) * NS(SRotation_cos_z)( elem ) -
        NS(Particle_x)( p ) * NS(SRotation_sin_z)( elem ) );

    status |= NS(Particle_set_x)( p, x_coord_rot );


    /* px_rot = cos_z * px + sin_z * py */
    x_coord_rot = NS(Particle_px)( p ) * NS(SRotation_cos_z)( elem ) +
                  NS(Particle_py)( p ) * NS(SRotation_sin_z)( elem );

    /* py_rot = -sin_z * px + cos_z * py */
    status |= NS(Particle_set_y)( p,
        NS(Particle_py)( p ) * NS(SRotation_cos_z)( elem ) -
        NS(Particle_px)( p ) * NS(SRotation_sin_z)( elem ) );

    status |= NS(Particle_set_px)( p, x_coord_rot );
    SIXTRL_ASSERT( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS );
    ( void )status;

    return ( NS(track_status_t) )SIXTRL_TRACK_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_TRACK_H__ */
