#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_TRACK_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_TRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/track/track_config.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle_unit.h"
    #include "sixtracklib/common/particles/particle_unit_api.h"
    #include "sixtracklib/common/particles/particle_unit_derived_api.h"
    #include "sixtracklib/common/beam_elements/limit_global_aperture.h"
    #include "sixtracklib/common/beam_elements/multipole/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_api.h"
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleT, class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
        track_status_t >::type
    Multipole_track(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT belem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT /* track_config */ )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( belem != SIXTRL_NULLPTR );

        typedef typename st::MultipoleTraits< MultipoleT >::real_t  mp_real_t;
        typedef typename st::MultipoleTraits< MultipoleT >::order_t mp_order_t;
        typedef typename st::ParticleTraits< ParticleT >::real_t real_t;

        static_assert( st::Type_is_scalar< mp_real_t >(),
            "real type of the Multipole has to be scalar" );

        static_assert( st::Type_is_scalar< mp_order_t >(),
            "order type of the Multipole has to be scalar" );

        SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
            st::Particle_beta0( p ), real_t{ 0 } ) );

        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< real_t >(
            st::Particle_beta0( p ), real_t{ 1 } ) );

        mp_order_t index = mp_order_t{ 2 } * st::Multipole_order( belem );

        real_t delta_px = st::Multipole_bal( belem, index );
        real_t delta_py = st::Multipole_bal( belem, index + mp_order_t{ 1 } );

        while( index > mp_order_t{ 0 } )
        {
            real_t const saved_delta_px = delta_px;
            SIXTRL_ASSERT( index >= mp_order_t{ 2 } );
            index -= mp_order_t{ 2 };

            delta_px *= st::Particle_x( p );
            delta_px -= delta_py * st::Particle_y( p );
            delta_px += st::Multipole_bal( belem, index );

            delta_py *= st::Particle_x( p );
            delta_py += saved_delta_px * st::Particle_y( p );
            delta_py += st::Multipole_bal( belem, index + mp_order_t{ 1 } );
        }

        delta_px *= -st::Particle_chi( p );
        delta_py *=  st::Particle_chi( p );

        if( ( st::abs< mp_real_t >(
                st::Multipole_hxl( belem ) ) > mp_real_t{ 0 } ) ||
            ( st::abs< mp_real_t >(
                st::Multipole_hyl( belem ) ) > mp_real_t{ 0 } ) )
        {
            real_t hxlx = st::Particle_x( p );
            real_t hyly = st::Particle_y( p );
            real_t temp = st::Particle_chi( p );

            hxlx    *= st::Multipole_hxl( belem );
            hyly    *= st::Multipole_hyl( belem );
            temp    *= ( hyly - hxlx ); /* temp = p->chi * ( hyly - hxlx ) */
            st::Particle_zeta( p ) += temp;

            temp      = st::Particle_delta( p );
            temp     += real_t{ 1 }; /* temp = p->delta + 1 */
            delta_px += temp * st::Multipole_hxl( belem );
            delta_py -= temp * st::Multipole_hyl( belem );

            if( st::Multipole_length( belem ) > mp_real_t{ 0 } )
            {
                temp  = st::Particle_chi( p );
                temp *= st::Multipole_bal( belem, mp_order_t{ 1 } );
                temp *= hxlx;
                temp /= st::Multipole_length( belem );

                /* temp = chi * bal[ 1 ] * hxlx / length */
                delta_px -= temp;

                temp  = st::Particle_chi( p );
                temp *= st::Multipole_bal( belem, mp_order_t{ 0 } );
                temp *= hyly;
                temp /= st::Multipole_length( belem );

                /* temp = chi * bal[ 0 ] * hyly / length */
                delta_py  += temp;
            }
        }

        st::Particle_add_to_px( p, delta_px );
        st::Particle_add_to_py( p, delta_py );

        return SIXTRL_TRACK_SUCCESS;
    }

    template< class ParticleT, class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() ||
        !SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
        track_status_t >::type
    Multipole_track(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT /* p */,
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT /* belem */,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT /* track_config */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TRACK_STATUS_GENERAL_FAILURE;
    }
}

template< class ParticleT, class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Multipole_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT belem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
        SIXTRL_RESTRICT track_config )
{
    return SIXTRL_CXX_NAMESPACE::Multipole_track( p, belem, track_config );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(Multipole_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT particle,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT drift,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* ************************************************************************* */
/* ****                        Implementation                           **** */
/* ************************************************************************* */


#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(track_status_t) NS(Multipole_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT elem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
            SIXTRL_RESTRICT /* track_config */ ) SIXTRL_NOEXCEPT
{
    typedef NS(be_real_t)       mp_real_t;
    typedef NS(be_order_t)      mp_order_t;
    typedef NS(particle_real_t) real_t;

    mp_order_t index = ( mp_order_t )2 * NS(Multipole_order)( elem );
    real_t delta_px  = NS(Multipole_bal)( elem, index );
    real_t delta_py  = NS(Multipole_bal)( elem, index + 1 );

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particle_beta0)( p ) >= ( real_t )0 );
    SIXTRL_ASSERT( NS(Particle_beta0)( p ) <= ( real_t )1 );

    while( index > ( mp_order_t )0 )
    {
        real_t const saved_delta_px = delta_px;
        SIXTRL_ASSERT( index >= ( mp_order_t )2 );
        index -= 2;

        delta_px *= NS(Particle_x)( p );
        delta_px -= delta_py * NS(Particle_y)( p );
        delta_px += NS(Multipole_bal)( elem, index );

        delta_py *= NS(Particle_x)( p );
        delta_py += saved_delta_px * NS(Particle_y)( p );
        delta_py += NS(Multipole_bal)( elem, index + 1 );
    }

    delta_px *= -NS(Particle_chi)( p );
    delta_py *=  NS(Particle_chi)( p );

    if( ( NS(abs)( NS(Multipole_hxl)( elem ) ) > ( mp_real_t )0 ) ||
        ( NS(abs)( NS(Multipole_hyl)( elem ) ) > ( mp_real_t )0 ) )
    {
        real_t hxlx = NS(Particle_x)( p );
        real_t hyly = NS(Particle_y)( p );
        real_t temp = NS(Particle_chi)( p );

        hxlx    *= NS(Multipole_hxl)( elem );
        hyly    *= NS(Multipole_hyl)( elem );
        temp    *= ( hyly - hxlx ); /* temp = p->chi * ( hyly - hxlx ) */
        NS(Particle_add_to_zeta)( p, temp );

        temp = NS(Particle_delta)( p ) + ( real_t )1;
        delta_px += temp * NS(Multipole_hxl)( elem );
        delta_py -= temp * NS(Multipole_hyl)( elem );

        if( NS(Multipole_length)( elem ) > ( mp_real_t )0 )
        {
            temp  = NS(Particle_chi)( p ) * NS(Multipole_bal)( elem, 1 ) * hxlx;
            /* temp = chi * bal[ 1 ] * hxlx / length */
            temp /= NS(Multipole_length)( elem );
            delta_px -= temp;

            temp  = NS(Particle_chi)( p ) * NS(Multipole_bal)( elem, 0 ) * hyly;;
            /* temp = chi * bal[ 0 ] * hyly / length */
            temp /= NS(Multipole_length)( elem );
            delta_py  += temp;
        }
    }

    NS(Particle_add_to_px)( p, delta_px );
    NS(Particle_add_to_py)( p, delta_py );
    return SIXTRL_TRACK_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_TRACK_H__ */
