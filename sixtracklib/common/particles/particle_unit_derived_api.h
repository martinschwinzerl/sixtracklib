#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_DERIVED_API_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_DERIVED_API_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_unit.h"
    #include "sixtracklib/common/particles/particle_unit_api.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_FN typename ParticleTraits< ParticleT >::real_t
    Particle_energy0( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
        SIXTRL_RESTRICT p );

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_FN typename ParticleTraits< ParticleT >::real_t
    Particle_energy( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
        SIXTRL_RESTRICT p );

    namespace
    {
        template< class ParticleT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        Particle_do_update_delta(
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
            typename TypeMethodParamTraits< typename ParticleTraits<
                 ParticleT >::real_t >::const_argument_type new_delta_value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::Particle_is_type< ParticleT >(),
                "ParticleT required to be a particle unit class" );

            typedef typename ParticleTraits< ParticleT >::real_t real_t;

            real_t delta_plus_one = new_delta_value;
            delta_plus_one += real_t{ 1 };

            SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
                st::abs< real_t >( delta_plus_one ), real_t{ 0 } ) );

            auto beta0 = st::Particle_beta0( p );
            SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
                beta0, real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< real_t >(
                beta0, real_t{ 1 } ) );

            real_t delta_beta0 = new_delta_value;
            delta_beta0 *= beta0;

            real_t temp = delta_beta0;
            temp *= beta0;
            temp *= real_t{ 2 };

            real_t ptau_beta0_plus_one = delta_beta0;
            ptau_beta0_plus_one *= delta_beta0;
            ptau_beta0_plus_one += temp;
            ptau_beta0_plus_one += real_t{ 1 };

            SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                    ptau_beta0_plus_one, real_t{ 0 } ) );

            ptau_beta0_plus_one = st::sqrt< real_t >( ptau_beta0_plus_one );

            st::arch_status_t status = st::Particle_set_delta(
                p, new_delta_value );

            /* temp == rpp = 1 / ( delta + 1 ) */
            temp  = real_t{ 1 };
            temp /= delta_plus_one;
            status |= st::Particle_set_rpp( p, temp );

            /* temp == rvv = ( delta + 1 ) / ptau * beta0 + 1 ) */
            temp  = delta_plus_one;
            temp /= ptau_beta0_plus_one;
            status |= st::Particle_set_rvv( p, temp );

            /* temp == psigma = ( ptau * beta0 ) / ( beta0 * beta0 ) */
            temp  = ptau_beta0_plus_one;
            temp -= real_t{ 1 };
            temp /= beta0;
            temp /= beta0;
            status |= st::Particle_set_psigma( p, temp );

            return status;
        }

        template< class ParticleT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        Particle_do_update_sigma( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
            SIXTRL_RESTRICT p, typename TypeMethodParamTraits< typename
                ParticleTraits< ParticleT >::real_t >::const_argument_type
                    sigma )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::Particle_is_type< ParticleT >(),
                "ParticleT required to be a particle unit class" );

            typedef typename ParticleTraits< ParticleT >::real_t real_t;

            SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
                    st::Particle_rvv( p ), real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
                    st::Particle_beta0( p ), real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< real_t >(
                    st::Particle_beta0( p ), real_t{ 1 } ) );

            real_t zeta = sigma;
            zeta *= st::Particle_rvv( p );
            return st::Particle_set_zeta( p, zeta );
        }

        template< class ParticleT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        Particle_do_update_psigma( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
            SIXTRL_RESTRICT p, typename TypeMethodParamTraits< typename
                ParticleTraits< ParticleT >::real_t >::const_argument_type
                    psigma )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::Particle_is_type< ParticleT >(),
                "ParticleT required to be a particle unit class" );

            typedef typename st::ParticleTraits< ParticleT >::real_t real_t;
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            auto beta0 = st::Particle_beta0( p );

            SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                beta0, real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< real_t >(
                beta0, real_t{ 1 } ) );

            real_t ptau = psigma;
            ptau *= beta0;

            real_t temp = psigma;
            temp *= real_t{ 2 };

            real_t delta_plus_one = ptau;
            delta_plus_one *= ptau;
            delta_plus_one += temp;
            delta_plus_one += real_t{ 1 };

            SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                delta_plus_one, real_t{ 0 } ) );

            delta_plus_one = st::sqrt< real_t >( delta_plus_one );

            SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
                delta_plus_one, real_t{ 0 } ) );

            real_t ptau_beta0_plus_one = ptau;
            ptau_beta0_plus_one *= beta0;
            ptau_beta0_plus_one += real_t{ 1 };

            SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                ptau_beta0_plus_one, real_t{ 0 } ) );

            status = st::Particle_set_psigma( p, psigma );

            /* temp == delta = ( delta + 1 ) - 1 */
            temp  = delta_plus_one;
            temp -= real_t{ 1 };

            status |= st::Particle_set_delta( p, temp );

            /* temp == rpp = 1 / ( delta + 1 ) */
            temp  = real_t{ 1 };
            temp /= delta_plus_one;
            status |= st::Particle_set_rpp( p, temp );

            /* rvv = ( delta + 1 ) / ( ptau * beta0 + 1 ) */
            delta_plus_one /= ptau_beta0_plus_one;
            status |= st::Particle_set_rvv( p, delta_plus_one );

            return status;
        }

        template< class ParticleT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        Particle_do_update_tau( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
            SIXTRL_RESTRICT p, typename TypeMethodParamTraits< typename
                ParticleTraits< ParticleT >::real_t >::const_argument_type tau )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::Particle_is_type< ParticleT >(),
                "ParticleT required to be a particle unit class" );

            typedef typename ParticleTraits< ParticleT >::real_t real_t;
            SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                st::Particle_beta0( p ), real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< real_t >(
                st::Particle_beta0( p ), real_t{ 1 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
                st::Particle_rvv( p ), real_t{ 0 } ) );

            /* zeta = beta0 * rvv * tau */
            real_t zeta = st::Particle_beta0( p );
            zeta *= st::Particle_rvv( p );
            zeta *= tau;

            return st::Particle_set_zeta( p, zeta );
        }

        template< class ParticleT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        Particle_do_update_ptau( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
            SIXTRL_RESTRICT p, typename TypeMethodParamTraits< typename
                ParticleTraits< ParticleT >::real_t >::const_argument_type ptau )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::Particle_is_type< ParticleT >(),
                "ParticleT required to be a particle unit class" );

            typedef typename ParticleTraits< ParticleT >::real_t real_t;

            auto beta0 = st::Particle_beta0( p );
            SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
                beta0, real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< real_t >(
                beta0, real_t{ 1 } ) );

            real_t psigma = ptau;
            psigma /= beta0;

            real_t ptau_beta0_plus_one = ptau;
            ptau_beta0_plus_one *= beta0;
            ptau_beta0_plus_one += real_t{ 1 };

            SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                st::abs< real_t >( ptau_beta0_plus_one ), real_t{ 0 } ) );

            real_t temp = psigma;
            temp *= real_t{ 2 };

            real_t delta_plus_one = ptau;
            delta_plus_one *= ptau;
            delta_plus_one += temp;
            delta_plus_one += real_t{ 1 };

            SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                delta_plus_one, real_t{ 0 } ) );

            delta_plus_one = st::sqrt< real_t >( delta_plus_one );
            SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
                delta_plus_one, real_t{ 0 } ) );

            st::arch_status_t status = st::Particle_set_psigma( p, psigma );

            /* rpp == temp = 1 / ( delta + 1 ) */
            temp  = real_t{ 1 };
            temp /= delta_plus_one;
            status |= st::Particle_set_rpp( p, temp );

            /* delta == temp = ( delta + 1 ) - 1 */
            temp  = delta_plus_one;
            temp -= real_t{ 1 };
            status |= st::Particle_set_delta( p, temp );

            /* rvv = ( delta + 1  ) / ( ptau * beta0 + 1 ) */
            delta_plus_one /= ptau_beta0_plus_one;
            status |= st::Particle_set_rvv( p, delta_plus_one );

            return status;
        }

        template< class ParticleT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        Particle_do_add_to_energy( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
            SIXTRL_RESTRICT p, typename TypeMethodParamTraits< typename
                 ParticleTraits< ParticleT >::real_t
                     >::const_argument_type d_energy )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::Particle_is_type< ParticleT >(),
                "ParticleT required to be a particle unit class" );

            typedef typename ParticleTraits< ParticleT >::real_t real_t;

            auto beta0 = st::Particle_beta0( p );
            SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
                beta0, real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< real_t >(
                beta0, real_t{ 1 } ) );

            real_t delta_beta0 = st::Particle_delta( p );
            delta_beta0 *= beta0;

            real_t temp = delta_beta0;
            temp *= beta0;
            temp *= real_t{ 2 };

            real_t ptau_beta0_plus_one = delta_beta0;
            ptau_beta0_plus_one *= delta_beta0;
            ptau_beta0_plus_one += temp;
            ptau_beta0_plus_one += real_t{ 1 };

            SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                ptau_beta0_plus_one, real_t{ 0 } ) );

            ptau_beta0_plus_one = st::sqrt< real_t >( ptau_beta0_plus_one );

            SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
                st::Particle_energy0( p ), real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                ( st::Particle_energy( p ) + d_energy ),
                    st::Particle_energy0( p ) ) );

            temp = d_energy;
            temp /= st::Particle_energy0( p );
            ptau_beta0_plus_one += temp;

            SIXTRL_ASSERT( st::Type_comp_all_more< real_t >( st::abs< real_t >(
                ptau_beta0_plus_one ), real_t{ 0 } ) );

            real_t ptau = ptau_beta0_plus_one;
            ptau -= real_t{ 1 };
            ptau /= beta0;

            real_t psigma = ptau;
            psigma /= beta0;

            temp  = psigma;
            temp *= real_t{ 2 };

            real_t delta_plus_one = ptau;
            delta_plus_one *= ptau;
            delta_plus_one += temp;
            delta_plus_one += real_t{ 1 };

            SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                delta_plus_one, real_t{ 0 } ) );

            delta_plus_one = st::sqrt< real_t >( delta_plus_one );
            SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
                delta_plus_one, real_t{ 0 } ) );

            st::arch_status_t status = st::Particle_set_psigma( p, psigma );

            temp  = real_t{ 1 };
            temp /= delta_plus_one;
            status |= st::Particle_set_rpp( p, temp );

            temp  = delta_plus_one;
            temp -= real_t{ 1 };
            status |= st::Particle_set_delta( p, temp );

            delta_plus_one /= ptau_beta0_plus_one;
            status |= st::Particle_set_rvv( p, delta_plus_one );

            return status;
        }
    }

    /* --------------------------------------------------------------------- */
    /* x */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_x( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_x */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_x( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_x */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_x( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_x(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_x )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->x += d_x;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_x(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_x )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->x -= d_x;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_x(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->x *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_x(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_x;
            status = st::Types_perform_assignment< src_t, real_t >( d_x, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->x += d_x;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_x(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_x;
            status = st::Types_perform_assignment< src_t, real_t >( d_x, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->x -= d_x;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_x(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->x *= c;
        }

        return status;
    }

    /* ---------------------------------------------------------------------- */
    /* px */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_px( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_px  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_px( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_px  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_px( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_px(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_px )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->px += d_px;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_px(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_px )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->px -= d_px;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_px(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->px *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_px(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_px;
            status = st::Types_perform_assignment< src_t, real_t >( d_px, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->px += d_px;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_px(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_px;
            status = st::Types_perform_assignment< src_t, real_t >( d_px, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->px -= d_px;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_px(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->px *= c;
        }

        return status;
    }

    /* ---------------------------------------------------------------------- */
    /* y */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_y( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_y  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_y( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_y  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_y( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_y(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_y )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->y += d_y;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_y(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_y )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->y -= d_y;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_y(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->y *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_y(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_y;
            status = st::Types_perform_assignment< src_t, real_t >( d_y, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->y += d_y;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_y(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_y;
            status = st::Types_perform_assignment< src_t, real_t >( d_y, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->y -= d_y;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_y(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->y *= c;
        }

        return status;
    }

    /* ---------------------------------------------------------------------- */
    /* py */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_py( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_py  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_py( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_py  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_py( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_py(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_py )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->py += d_py;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_py(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_py )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->py -= d_py;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_py(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->py *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_py(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_py;
            status = st::Types_perform_assignment< src_t, real_t >( d_py, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->py += d_py;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_py(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_py;
            status = st::Types_perform_assignment< src_t, real_t >( d_py, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->py -= d_py;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_py(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->py *= c;
        }

        return status;
    }

    /* ---------------------------------------------------------------------- */
    /* zeta */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_zeta( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_zeta  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_zeta( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_zeta  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_zeta( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_zeta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_zeta )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->zeta += d_zeta;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_zeta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_zeta )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->zeta -= d_zeta;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_zeta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->zeta *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_zeta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_zeta;
            status = st::Types_perform_assignment< src_t, real_t >( d_zeta, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->zeta += d_zeta;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_zeta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_zeta;
            status = st::Types_perform_assignment< src_t, real_t >( d_zeta, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->zeta -= d_zeta;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_zeta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->zeta *= c;
        }

        return status;
    }

    /* ---------------------------------------------------------------------- */
    /* delta */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_delta( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_delta  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_delta( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_delta  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_delta( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_delta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_delta )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->delta += d_delta;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_delta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_delta )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->delta -= d_delta;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_delta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->delta *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_delta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_delta;
            status = st::Types_perform_assignment< src_t, real_t >( d_delta, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->delta += d_delta;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_delta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_delta;
            status = st::Types_perform_assignment< src_t, real_t >( d_delta, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->delta -= d_delta;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_delta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->delta *= c;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* psigma */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_psigma( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_psigma */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_psigma( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_psigma */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_psigma( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_psigma(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_psigma )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->psigma += d_psigma;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_psigma(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_psigma )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->psigma -= d_psigma;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_psigma(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->psigma *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_psigma(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_psigma;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_psigma, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->psigma += d_psigma;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_psigma(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_psigma;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_psigma, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->psigma -= d_psigma;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_psigma(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->psigma *= c;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* rpp */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_rpp( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_rpp */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_rpp( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_rpp */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_rpp( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_rpp(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_rpp )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->rpp += d_rpp;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_rpp(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_rpp )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->rpp -= d_rpp;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_rpp(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->rpp *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_rpp(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_rpp;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_rpp, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->rpp += d_rpp;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_rpp(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_rpp;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_rpp, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->rpp -= d_rpp;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_rpp(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->rpp *= c;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* rvv */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_rvv( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_rvv */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_rvv( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_rvv */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_rvv( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_rvv(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_rvv )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->rvv += d_rvv;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_rvv(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_rvv )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->rvv -= d_rvv;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_rvv(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->rvv *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_rvv(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_rvv;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_rvv, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->rvv += d_rvv;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_rvv(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_rvv;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_rvv, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->rvv -= d_rvv;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_rvv(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->rvv *= c;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* chi */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_chi( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_chi */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_chi( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_chi */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_chi( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_chi(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_chi )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->chi += d_chi;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_chi(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_chi )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->chi -= d_chi;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_chi(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->chi *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_chi(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_chi;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_chi, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->chi += d_chi;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_chi(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_chi;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_chi, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->chi -= d_chi;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_chi(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->chi *= c;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* charge_ratio */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_charge_ratio( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_charge_ratio */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_charge_ratio( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_charge_ratio */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_charge_ratio( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_charge_ratio(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_charge_ratio )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->charge_ratio += d_charge_ratio;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_charge_ratio(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_charge_ratio )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->charge_ratio -= d_charge_ratio;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_charge_ratio(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->charge_ratio *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_charge_ratio(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_charge_ratio;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_charge_ratio, arg );
            if( status == st::ARCH_STATUS_SUCCESS )
                p->charge_ratio += d_charge_ratio;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_charge_ratio(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_charge_ratio;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_charge_ratio, arg );
            if( status == st::ARCH_STATUS_SUCCESS )
                p->charge_ratio -= d_charge_ratio;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_charge_ratio(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->charge_ratio *= c;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* charge0 */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_charge0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_charge0 */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_charge0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_charge0 */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_charge0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_charge0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_charge0 )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->charge0 += d_charge0;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_charge0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_charge0 )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->charge0 -= d_charge0;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_charge0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->charge0 *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_charge0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_charge0;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_charge0, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->charge0 += d_charge0;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_charge0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_charge0;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_charge0, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->charge0 -= d_charge0;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_charge0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->charge0 *= c;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* mass0 */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_mass0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_mass0 */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_mass0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_mass0 */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_mass0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_mass0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_mass0 )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->mass0 += d_mass0;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_mass0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_mass0 )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->mass0 -= d_mass0;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_mass0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->mass0 *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_mass0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_mass0;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_mass0, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->mass0 += d_mass0;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_mass0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_mass0;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_mass0, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->mass0 -= d_mass0;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_mass0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->mass0 *= c;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* beta0 */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_beta0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_beta0 */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_beta0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_beta0 */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_beta0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_beta0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_beta0 )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->beta0 += d_beta0;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_beta0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_beta0 )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->beta0 -= d_beta0;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_beta0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->beta0 *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_beta0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_beta0;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_beta0, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->beta0 += d_beta0;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_beta0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_beta0;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_beta0, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->beta0 -= d_beta0;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_beta0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->beta0 *= c;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* gamma0 */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_gamma0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_gamma0 */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_gamma0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_gamma0 */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_gamma0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_gamma0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_gamma0 )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->gamma0 += d_gamma0;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_gamma0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_gamma0 )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->gamma0 -= d_gamma0;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_gamma0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->gamma0 *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_gamma0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_gamma0;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_gamma0, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->gamma0 += d_gamma0;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_gamma0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_gamma0;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_gamma0, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->gamma0 -= d_gamma0;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_gamma0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->gamma0 *= c;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* pc0 */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_pc0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_pc0 */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_pc0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_pc0 */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_pc0( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_pc0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_pc0 )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->pc0 += d_pc0;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_pc0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_pc0 )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->pc0 -= d_pc0;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_pc0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->pc0 *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_pc0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_pc0;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_pc0, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->pc0 += d_pc0;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_pc0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_pc0;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_pc0, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->pc0 -= d_pc0;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_pc0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->pc0 *= c;
        }

        return status;
    }

    /* ---------------------------------------------------------------------- */
    /* s */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_s( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_s  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_s( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_s  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_scale_s( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* c  */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_s(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_s )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->s += d_s;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_s(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_s )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->s -= d_s;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_s(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->s *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_s(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_s;
            status = st::Types_perform_assignment< src_t, real_t >( d_s, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->s += d_s;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_subtract_from_s(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t d_s;
            status = st::Types_perform_assignment< src_t, real_t >( d_s, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->s -= d_s;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_scale_s(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->s *= c;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* state */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_state( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_state */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_state( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_state */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_add_to_state(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_state )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->state += d_state;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_subtract_from_state(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_state )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->state -= d_state;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_add_to_state(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::index_t index_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            index_t d_state;
            status = st::Types_perform_assignment< src_t, index_t >(
                d_state, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->state += d_state;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_subtract_from_state(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::index_t index_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            index_t d_state;
            status = st::Types_perform_assignment< src_t, index_t >(
                d_state, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->state -= d_state;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* at_element */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_at_element( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_at_element */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_at_element( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_at_element */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_add_to_at_element(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_at_element )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->at_element += d_at_element;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_subtract_from_at_element(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_at_element )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->at_element -= d_at_element;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_add_to_at_element(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::index_t index_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            index_t d_at_element;
            status = st::Types_perform_assignment< src_t, index_t >(
                d_at_element, arg );
            if( status == st::ARCH_STATUS_SUCCESS )
                p->at_element += d_at_element;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_subtract_from_at_element(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::index_t index_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            index_t d_at_element;
            status = st::Types_perform_assignment< src_t, index_t >(
                d_at_element, arg );
            if( status == st::ARCH_STATUS_SUCCESS )
                p->at_element -= d_at_element;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* at_turn */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_at_turn( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_at_turn */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_at_turn( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_at_turn */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_add_to_at_turn(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_at_turn )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->at_turn += d_at_turn;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_subtract_from_at_turn(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_at_turn )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->at_turn -= d_at_turn;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_add_to_at_turn(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::index_t index_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            index_t d_at_turn;
            status = st::Types_perform_assignment< src_t, index_t >(
                d_at_turn, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->at_turn += d_at_turn;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_subtract_from_at_turn(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::index_t index_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            index_t d_at_turn;
            status = st::Types_perform_assignment< src_t, index_t >(
                d_at_turn, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->at_turn -= d_at_turn;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* id */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_id( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_id */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_subtract_from_id( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */, RealArg /* d_id */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_add_to_id(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_id )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->id += d_id;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_subtract_from_id(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg d_id )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        p->id -= d_id;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_add_to_id(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::index_t index_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            index_t d_id;
            status = st::Types_perform_assignment< src_t, index_t >(
                d_id, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->id += d_id;
        }

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_subtract_from_id(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename ParticleTraits< ParticleT >::index_t index_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            index_t d_id;
            status = st::Types_perform_assignment< src_t, index_t >(
                d_id, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) p->id -= d_id;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* zeta */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
    Particle_update_zeta( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p, RealArg new_zeta_value  )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_set_zeta( p, new_zeta_value );
    }

    /* --------------------------------------------------------------------- */
    /* delta */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_update_delta( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /*p*/, RealArg /*new_delta_value*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic< RealArg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_update_delta( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p, RealArg new_delta_value )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_do_update_delta(
            p, new_delta_value );
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
         SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic< RealArg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_update_delta(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        RealArg in_delta )
    {
        typename ParticleTraits< ParticleT >::real_t delta;
        SIXTRL_CXX_NAMESPACE::arch_status_t status =
            SIXTRL_CXX_NAMESPACE::Types_perform_assignment<
                typename std::decay< RealArg >::type,
                typename ParticleTraits< ParticleT >::real_t >(
                    delta, in_delta );

        if( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
            status = SIXTRL_CXX_NAMESPACE::Particle_do_update_delta( p, delta );

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* sigma */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
        ParticleTraits< ParticleT >::real_t
    Particle_sigma(
        SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );

        SIXTRL_ASSERT( SIXTRL_CXX_NAMESPACE::Type_comp_all_more<
            typename ParticleTraits< ParticleT >::real_t >( st::Particle_rvv(
                p ), typename ParticleTraits< ParticleT >::real_t{ 0 } ) );

        SIXTRL_ASSERT( SIXTRL_CXX_NAMESPACE::Type_comp_all_more<
            typename ParticleTraits< ParticleT >::real_t >( st::Particle_beta0(
                p ), typename ParticleTraits< ParticleT >::real_t{ 0 } ) );

        SIXTRL_ASSERT( SIXTRL_CXX_NAMESPACE::Type_comp_all_less_or_equal<
            typename ParticleTraits< ParticleT >::real_t >( st::Particle_beta0(
                p ), typename ParticleTraits< ParticleT >::real_t{ 1 } ) );

        return st::Particle_zeta( p ) / st::Particle_rvv( p );
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_update_sigma( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /*p*/, RealArg /*sigma*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic< RealArg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_update_sigma( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p, RealArg sigma )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_do_update_sigma( p, sigma );
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic< RealArg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_update_sigma( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p, RealArg in_sigma )
    {
        typename ParticleTraits< ParticleT >::real_t sigma;
        SIXTRL_CXX_NAMESPACE::arch_status_t status =
            SIXTRL_CXX_NAMESPACE::Types_perform_assignment<
                typename std::decay< RealArg >::type,
                typename ParticleTraits< ParticleT >::real_t >(
                    sigma, in_sigma );

        if( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
            status = SIXTRL_CXX_NAMESPACE::Particle_do_update_sigma( p, sigma );

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* psigma */

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_update_psigma( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /*p*/, RealArg /*psigma*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Particle_update_psigma( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p, RealArg in_psigma )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename st::ParticleTraits< ParticleT >::real_t dst_real_t;

        dst_real_t psigma;
        st::arch_status_t status = st::Types_perform_assignment<
            src_real_t, dst_real_t >( psigma, in_psigma );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = st::Particle_do_update_psigma( p, psigma );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* tau */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename ParticleTraits<
        ParticleT >::real_t
    Particle_tau( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
        SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );

        typedef typename ParticleTraits< ParticleT >::real_t real_t;

        real_t beta = st::Particle_beta0( p );
        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
            beta, real_t{ 0 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< real_t >(
            beta, real_t{ 1 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
            st::Particle_rvv( p ), real_t{ 0 } ) );

        beta *= st::Particle_rvv( p );
        SIXTRL_ASSERT( st::Type_comp_all_more< real_t >( beta, real_t{ 0 } ) );

        return st::Particle_zeta( p ) / beta;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_update_tau( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /*p*/, RealArg /*tau*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_update_tau( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p, RealArg in_tau )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename st::ParticleTraits< ParticleT >::real_t dst_real_t;

        dst_real_t tau;
        st::arch_status_t status = st::Types_perform_assignment< src_real_t,
            dst_real_t >( tau, in_tau );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = st::Particle_do_update_tau( p, tau );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* ptau */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename ParticleTraits<
        ParticleT >::real_t
    Particle_ptau( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
        SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );

        typedef typename ParticleTraits< ParticleT >::real_t real_t;

        auto beta0 = st::Particle_beta0( p );
        SIXTRL_ASSERT( SIXTRL_CXX_NAMESPACE::Type_comp_all_more<
            real_t >( beta0, real_t{ 0 } ) );
        SIXTRL_ASSERT( SIXTRL_CXX_NAMESPACE::Type_comp_all_less_or_equal<
            real_t >( beta0, real_t{ 1 } ) );

        real_t inv_beta0 = real_t{ 1 };
        inv_beta0 /= beta0;

        /* ptau = sqrt( delta * delta + 2 * delta + 1/beta0^2 ) - 1/beta0 */
        auto delta = st::Particle_delta( p );
        real_t temp = delta;
        temp *= real_t{ 2 };

        real_t ptau_plus_inv_beta0 = delta;
        ptau_plus_inv_beta0 *= delta;
        ptau_plus_inv_beta0 += temp;

        temp =  inv_beta0;
        temp *= inv_beta0;
        ptau_plus_inv_beta0 += temp;

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
            ptau_plus_inv_beta0, real_t{ 0 } ) );

        ptau_plus_inv_beta0 = st::sqrt< real_t >( ptau_plus_inv_beta0 );
        return ptau_plus_inv_beta0 - inv_beta0;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_update_ptau( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /*p*/, RealArg /*ptau */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic< RealArg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_update_ptau(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg ptau )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_do_update_ptau( p, ptau );
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic< RealArg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_update_ptau( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p, RealArg in_ptau )
    {
        typename ParticleTraits< ParticleT >::real_t ptau;
        SIXTRL_CXX_NAMESPACE::arch_status_t status =
            SIXTRL_CXX_NAMESPACE::Types_perform_assignment<
                typename std::decay< RealArg >::type,
                typename ParticleTraits< ParticleT >::real_t >( ptau, in_ptau );

        if( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
            status =  SIXTRL_CXX_NAMESPACE::Particle_do_update_ptau( p, ptau );

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* beta */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename ParticleTraits<
        ParticleT >::real_t
    Particle_beta( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
        SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );

        SIXTRL_ASSERT( st::Type_comp_all_more< typename
            ParticleTraits< ParticleT >::real_t >( st::Particle_beta0( p ),
                typename ParticleTraits< ParticleT >::real_t{ 0 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< typename
            ParticleTraits< ParticleT >::real_t >( st::Particle_beta0( p ),
                typename ParticleTraits< ParticleT >::real_t{ 1 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< typename
            ParticleTraits< ParticleT >::real_t >( st::Particle_rvv( p ),
                typename ParticleTraits< ParticleT >::real_t{ 0 } ) );

        return st::Particle_beta0( p ) * st::Particle_rvv( p );
    }

    /* --------------------------------------------------------------------- */
    /* mass */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename ParticleTraits<
        ParticleT >::real_t
    Particle_mass_ratio( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
        SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );

        SIXTRL_ASSERT( st::Type_comp_all_more< typename ParticleTraits<
            ParticleT >::real_t >( st::Particle_mass0( p ), typename
                ParticleTraits< ParticleT >::real_t{ 0 } ) );

        SIXTRL_ASSERT( st::Type_comp_all_more< typename ParticleTraits<
            ParticleT >::real_t >( st::abs< typename ParticleTraits<
                ParticleT >::real_t >( st::Particle_charge0( p ) ), typename
                    ParticleTraits< ParticleT >::real_t{ 0 } ) );

        SIXTRL_ASSERT( st::Type_comp_all_more< typename ParticleTraits<
            ParticleT >::real_t >( st::abs< typename ParticleTraits<
                ParticleT >::real_t >( st::Particle_charge_ratio( p ) ),
                    typename ParticleTraits< ParticleT >::real_t{ 0 } ) );

        SIXTRL_ASSERT( st::Type_comp_all_more< typename ParticleTraits<
            ParticleT >::real_t >( st::abs< typename ParticleTraits<
                ParticleT >::real_t >( st::Particle_chi( p ) ),
                    typename ParticleTraits< ParticleT >::real_t{ 0 } ) );

        return st::Particle_charge_ratio( p ) / st::Particle_chi( p );
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
        ParticleTraits< ParticleT >::real_t
    Particle_mass( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
            SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );

        SIXTRL_ASSERT( st::Type_comp_all_more< typename ParticleTraits<
            ParticleT >::real_t >( st::Particle_mass0( p ), typename
                ParticleTraits< ParticleT >::real_t{ 0 } ) );

        return st::Particle_mass_ratio( p ) * st::Particle_mass0( p );
    }

    /* --------------------------------------------------------------------- */
    /* charge */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename ParticleTraits<
        ParticleT >::real_t
    Particle_charge( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
            SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );

        SIXTRL_ASSERT( st::Type_comp_all_more< typename ParticleTraits<
            ParticleT >::real_t >( st::abs< typename ParticleTraits<
                ParticleT >::real_t >( st::Particle_charge0( p ) ), typename
                    ParticleTraits< ParticleT >::real_t{ 0 } ) );

        return st::Particle_charge_ratio( p ) * st::Particle_charge0( p );
    }

    /* --------------------------------------------------------------------- */
    /* energy0 / energy / pc */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename ParticleTraits<
        ParticleT >::real_t
    Particle_energy0( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
        SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );

        typedef typename ParticleTraits< ParticleT >::real_t real_t;
        SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
            st::Particle_mass0( p ), real_t{ 0 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
            st::Particle_pc0( p ), real_t{ 0 } ) );

        real_t pc0_squ = st::Particle_pc0( p );
        pc0_squ *= pc0_squ;

        real_t energy0_squ = st::Particle_mass0( p );
        energy0_squ *= energy0_squ;
        energy0_squ += pc0_squ;

        return st::sqrt< real_t >( energy0_squ );
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename ParticleTraits<
        ParticleT >::real_t
    Particle_energy( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
        SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );
        typedef typename ParticleTraits< ParticleT >::real_t real_t;

        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
            st::Particle_beta0( p ), real_t{ 0 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< real_t >(
            st::Particle_beta0( p ), real_t{ 1 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
            st::Particle_pc0( p ), real_t{ 0 } ) );

        auto mass0 = st::Particle_mass0( p );
        SIXTRL_ASSERT( st::Type_comp_all_more< real_t >(
            st::Particle_mass0( p ), real_t{ 0 } ) );

        real_t temp = st::Particle_pc0( p );
        real_t E_squ = temp;
        E_squ *= temp;

        temp   = mass0;
        temp  *= mass0;
        E_squ += temp;

        E_squ  = st::sqrt< real_t >( E_squ );
        E_squ *= st::Particle_mass_ratio( p );

        temp   = st::Particle_pc0( p );
        temp  *= st::Particle_beta0( p );
        temp  *= st::Particle_psigma( p );

        return E_squ + temp;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_add_to_energy( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /*p*/, RealArg /*d_energy*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic< RealArg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_energy( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p, RealArg d_energy )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_do_add_to_energy( p, d_energy );
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic< RealArg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_add_to_energy( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p, RealArg in_d_energy )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typename ParticleTraits< ParticleT >::real_t d_energy;
        st::arch_status_t status = st::Types_perform_assignment<
                typename std::decay< RealArg >::type,
                typename ParticleTraits< ParticleT >::real_t >(
                    d_energy, in_d_energy );

        if( status == st::ARCH_STATUS_SUCCESS )
            status =  st::Particle_do_add_to_energy( p, d_energy );

        return status;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_update_energy( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /*p*/, RealArg /*energy*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic< RealArg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_update_energy( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p, RealArg energy )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );
        typedef typename ParticleTraits< ParticleT >::real_t real_t;

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
            energy, st::Particle_energy0( p ) ) );

        real_t d_energy = energy;
        d_energy -= st::Particle_energy( p );
        return st::Particle_add_to_energy( p, d_energy );
    }

    template< class ParticleT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic< RealArg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_update_energy( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p, RealArg in_energy )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );
        typedef typename ParticleTraits< ParticleT >::real_t real_t;

        real_t energy;
        st::arch_status_t status = st::Types_perform_assignment<
            typename std::decay< RealArg >::type, real_t >(
                energy, in_energy );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                energy, st::Particle_energy0( p ) ) );

            real_t d_energy = energy;
            d_energy -= st::Particle_energy( p );
            status = st::Particle_add_to_energy( p, d_energy );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* state */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool Particle_is_lost(
        SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );
        typedef typename ParticleTraits< ParticleT >::index_t index_t;

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< index_t >(
            st::Particle_state( p ), index_t{ 0 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< index_t >(
            st::Particle_state( p ), index_t{ 1 } ) );

        return st::Type_comp_all_not_equal< index_t >(
            st::Particle_state( p ), index_t{ 1 } );
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool Particle_is_not_lost(
        SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );
        typedef typename ParticleTraits< ParticleT >::index_t index_t;

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< index_t >(
            st::Particle_state( p ), index_t{ 0 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< index_t >(
            st::Particle_state( p ), index_t{ 1 } ) );

        return st::Type_comp_all_equal< index_t >(
            st::Particle_state( p ), index_t{ 1 } );
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool Particle_has_any_lost(
        SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );
        typedef typename ParticleTraits< ParticleT >::index_t index_t;

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< index_t >(
            st::Particle_state( p ), index_t{ 0 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< index_t >(
            st::Particle_state( p ), index_t{ 1 } ) );

        return st::Type_comp_any_not_equal< index_t >(
            st::Particle_state( p ), index_t{ 1 } );
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool Particle_has_any_not_lost(
        SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );
        typedef typename ParticleTraits< ParticleT >::index_t index_t;

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< index_t >(
            st::Particle_state( p ), index_t{ 0 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< index_t >(
            st::Particle_state( p ), index_t{ 1 } ) );

        return st::Type_comp_any_equal< index_t >(
            st::Particle_state( p ), index_t{ 1 } );
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t Particle_mark_as_lost(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be a particle unit class" );
        typedef typename ParticleTraits< ParticleT >::index_t index_t;

        SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< index_t >(
            st::Particle_state( p ), index_t{ 0 } ) );
        SIXTRL_ASSERT( st::Type_comp_all_less_or_equal< index_t >(
            st::Particle_state( p ), index_t{ 1 } ) );

        return st::Particle_set_state( p, index_t{ 0 } );
    }

    template< class ParticleT, typename IndexArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_update_state_if_not_lost(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT /* p */,
        IndexArg /* new_state */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename IndexArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Type_is_scalar< typename ParticleTraits<
            ParticleT >::index_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            IndexArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_update_state_if_not_lost(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        IndexArg new_state )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ParticleTraits< ParticleT >::index_t index_t;

        return ( st::Particle_state( p ) == index_t{ 1 } )
            ? ( st::Particle_set_state( p, new_state ) )
            : ( ( new_state == index_t{ 1 }  )
                ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE );
    }

    template< class ParticleT, typename IndexArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Type_is_scalar< typename ParticleTraits<
            ParticleT >::index_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            IndexArg, typename ParticleTraits< ParticleT >::index_t >(),
        arch_status_t >::type
    Particle_update_state_if_not_lost(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        IndexArg in_new_state )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ParticleTraits< ParticleT >::index_t index_t;

        index_t new_state;
        st::arch_status_t status = st::Types_perform_assignment<
            typename std::decay< IndexArg >::type, index_t >(
                new_state, in_new_state );

        if( ( st::ARCH_STATUS_SUCCESS == status ) &&
            ( st::Particle_state( p ) == index_t{ 1 } ) )
        {
            if( new_state != index_t{ 1 } )
            {
                status = st::Particle_set_state( p, new_state );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* at_element, at_turn */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_increment_at_element( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Type_is_scalar< typename ParticleTraits<
            ParticleT >::index_t >(), arch_status_t >::type
    Particle_increment_at_element( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p )
    {
        if( SIXTRL_CXX_NAMESPACE::Particle_is_not_lost( p ) )
        {
            SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
            ++p->at_element;
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }

        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_increment_at_turn( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT /* p */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Type_is_scalar< typename ParticleTraits<
            ParticleT >::index_t >(), arch_status_t >::type
    Particle_increment_at_turn( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( st::Particle_is_not_lost( p ) )
        {
            SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
            ++p->at_turn;
            status  = st::Particle_set_default_at_element( p );
            status |= st::Particle_set_default_s( p );
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticleT, typename IndexArg, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        arch_status_t >::type
    Particle_increment_at_turn_detailed(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT /* p */,
        IndexArg /* at_element */, RealArg /* s */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename IndexArg, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< ParticleT >() &&
        SIXTRL_CXX_NAMESPACE::Type_is_scalar< typename ParticleTraits<
            ParticleT >::index_t >(), arch_status_t >::type
    Particle_increment_at_turn_detailed(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        IndexArg at_element, RealArg s )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( st::Particle_is_not_lost( p ) )
        {
            SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
            ++p->at_turn;
            status  = st::Particle_set_at_element( p, at_element );
            status |= st::Particle_set_s( p, s );
        }

        return status;
    }
}

/* ------------------------------------------------------------------------- */
/* x */

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_add_to_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_x )
{
    return SIXTRL_CXX_NAMESPACE::Particle_add_to_x( p, d_x );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_subtract_from_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_x )
{
    return SIXTRL_CXX_NAMESPACE::Particle_subtract_from_x( p, d_x );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_scale_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::Particle_scale_x( p, c );
}

/* ------------------------------------------------------------------------- */
/* px */

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_add_to_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_px )
{
    return SIXTRL_CXX_NAMESPACE::Particle_add_to_px( p, d_px );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_subtract_from_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_px )
{
    return SIXTRL_CXX_NAMESPACE::Particle_subtract_from_x( p, d_px );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_scale_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::Particle_scale_px( p, c );
}

/* ------------------------------------------------------------------------- */
/* y */

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_add_to_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_y )
{
    return SIXTRL_CXX_NAMESPACE::Particle_add_to_y( p, d_y );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_subtract_from_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_y )
{
    return SIXTRL_CXX_NAMESPACE::Particle_subtract_from_x( p, d_y );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_scale_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::Particle_scale_y( p, c );
}

/* ------------------------------------------------------------------------- */
/* py */

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_add_to_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_py )
{
    return SIXTRL_CXX_NAMESPACE::Particle_add_to_py( p, d_py );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_subtract_from_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_py )
{
    return SIXTRL_CXX_NAMESPACE::Particle_subtract_from_x( p, d_py );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_scale_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::Particle_scale_py( p, c );
}

/* ------------------------------------------------------------------------- */
/* zeta */

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_add_to_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_zeta )
{
    return SIXTRL_CXX_NAMESPACE::Particle_add_to_zeta( p, d_zeta );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_subtract_from_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_zeta )
{
    return SIXTRL_CXX_NAMESPACE::Particle_subtract_from_x( p, d_zeta );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_scale_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::Particle_scale_zeta( p, c );
}

/* ------------------------------------------------------------------------- */
/* s */

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_add_to_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_s )
{
    return SIXTRL_CXX_NAMESPACE::Particle_add_to_s( p, d_s );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_subtract_from_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg d_s )
{
    return SIXTRL_CXX_NAMESPACE::Particle_subtract_from_x( p, d_s );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_scale_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::Particle_scale_s( p, c );
}

/* ------------------------------------------------------------------------- */
/* zeta */

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_update_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg zeta )
{
    return SIXTRL_CXX_NAMESPACE::Particle_update_zeta( p, zeta );
}

/* ------------------------------------------------------------------------- */
/* delta */

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_update_delta)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
    SIXTRL_RESTRICT p, RealArg delta )
{
    return SIXTRL_CXX_NAMESPACE::Particle_update_delta( p, delta );
}

/* ------------------------------------------------------------------------- */
/* sigma */

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::ParticleTraits< ParticleT >::real_t
NS(Particle_sigma)( SIXTRL_PARTICLE_ARGPTR_DEC const
    ParticleT *const SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_sigma( p );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_update_sigma)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
    SIXTRL_RESTRICT p, RealArg sigma )
{
    return SIXTRL_CXX_NAMESPACE::Particle_update_sigma( p, sigma );
}

/* ------------------------------------------------------------------------- */
/* psigma */

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_update_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg psigma )
{
    return SIXTRL_CXX_NAMESPACE::Particle_update_psigma( p, psigma );
}

/* ------------------------------------------------------------------------- */
/* tau */

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::ParticleTraits< ParticleT >::real_t
NS(Particle_tau)( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
    SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_tau( p );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_update_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg tau )
{
    return SIXTRL_CXX_NAMESPACE::Particle_update_tau( p, tau );
}

/* ------------------------------------------------------------------------- */
/* ptau */

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::ParticleTraits< ParticleT >::real_t
NS(Particle_ptau)( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
    SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_ptau( p );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_update_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p, RealArg ptau )
{
    return SIXTRL_CXX_NAMESPACE::Particle_update_ptau( p, ptau );
}

/* ------------------------------------------------------------------------- */
/* beta */

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::ParticleTraits< ParticleT >::real_t
NS(Particle_beta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_beta( p );
}

/* ------------------------------------------------------------------------- */
/* mass */

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::ParticleTraits< ParticleT >::real_t
NS(Particle_mass)( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
        SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_mass( p );
}

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::ParticleTraits< ParticleT >::real_t
NS(Particle_mass_ratio)( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
    SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_mass_ratio( p );
}

/* ------------------------------------------------------------------------- */
/* charge */

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::ParticleTraits< ParticleT >::real_t
NS(Particle_charge)( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
        SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_charge( p );
}

/* ------------------------------------------------------------------------- */
/* energy0 / energy / pc */

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::ParticleTraits< ParticleT >::real_t
NS(Particle_energy0)( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
    SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_energy0( p );
}

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::ParticleTraits< ParticleT >::real_t
NS(Particle_energy)( SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
        SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_energy( p );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_add_to_energy)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
    SIXTRL_RESTRICT p, RealArg d_energy )
{
    return SIXTRL_CXX_NAMESPACE::Particle_add_to_energy( p, d_energy );
}

template< class ParticleT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_update_energy)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
    SIXTRL_RESTRICT p, RealArg energy )
{
    return SIXTRL_CXX_NAMESPACE::Particle_update_energy( p, energy );
}

/* ------------------------------------------------------------------------- */
/* state */

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(Particle_is_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_is_lost( p );
}

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(Particle_is_not_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_is_not_lost( p );
}

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(Particle_has_any_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_has_any_lost( p );
}

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(Particle_has_any_not_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_has_any_not_lost( p );
}

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_mark_as_lost)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
    SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_mark_as_lost( p );
}

template< class ParticleT, typename IndexArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_update_state_if_not_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    IndexArg new_state )
{
    return SIXTRL_CXX_NAMESPACE::Particle_update_state_if_not_lost(
        p, new_state );
}

/* ------------------------------------------------------------------------- */
/* at_element, at_turn */

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_increment_at_element)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
    SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_increment_at_element( p );
}

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_increment_at_turn)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
    SIXTRL_RESTRICT p )
{
    return SIXTRL_CXX_NAMESPACE::Particle_increment_at_turn( p );
}

template< class ParticleT, typename IndexArg, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_increment_at_turn_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle)* SIXTRL_RESTRICT p,
    IndexArg at_element_value, RealArg s_value )
{
    return SIXTRL_CXX_NAMESPACE::Particle_increment_at_turn_detailed(
        p, at_element_value, s_value );
}

#endif /* C++ */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ------------------------------------------------------------------------- */
/* x */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_x ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_x ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_x ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* px */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_px ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_px ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* y */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_y ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_y ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* py */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_py ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_py ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* zeta */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_zeta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_zeta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* delta */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_delta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_delta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* psigma */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_psigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_psigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* rpp */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_rpp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_rpp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* rvv */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_rvv ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_rvv ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* chi */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_chi ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_chi ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* charge_ratio */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_charge_ratio ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Particle_subtract_from_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_charge_ratio ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* charge0 */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_charge0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_charge0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* mass0 */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_mass0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_mass0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* beta0 */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_beta0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_beta0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* gamma0 */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_gamma0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_gamma0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* pc0 */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_pc0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_pc0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_pc0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_pc0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_pc0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* s */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_s ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_s ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* state */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_state ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_state ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* at_element */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_at_element ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_at_element ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* at_turn */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_at_turn ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_at_turn ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* id */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_subtract_from_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_scale_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const c ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* zeta */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_update_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const zeta ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* delta */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_update_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* sigma */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_update_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const sigma ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* psigma */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_update_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const psigma ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* tau */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_update_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const tau ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* ptau */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_update_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const ptau ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* beta */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_beta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* mass */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_mass_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_mass)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* charge */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_charge)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* energy0 / energy / pc */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_energy0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_add_to_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_energy ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_update_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const energy ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* state */

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_is_lost)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_is_not_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_has_any_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_has_any_not_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_mark_as_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_update_state_if_not_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const state ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* at_element, at_turn */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_increment_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;


SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_increment_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;


SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(Particle_increment_at_turn_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const at_element, NS(particle_real_t) const s
) SIXTRL_NOEXCEPT;


#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ------------------------------------------------------------------------- */
/* x */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_x ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->x += d_x;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_x ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->x -= d_x;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->x *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* px */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_px ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->px += d_px;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_px ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->px -= d_px;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->px *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* y */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_y ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->y += d_y;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_y ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->y -= d_y;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->y *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* py */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_py ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->py += d_py;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_py ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->py -= d_py;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->py *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* zeta */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_zeta ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->zeta += d_zeta;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_zeta ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->zeta -= d_zeta;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->zeta *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* delta */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_delta ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->delta += d_delta;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_delta ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->delta -= d_delta;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->delta *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* psigma */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_psigma ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->psigma += d_psigma;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_psigma ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->psigma -= d_psigma;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->psigma *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* rpp */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_rpp ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->rpp += d_rpp;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_rpp ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->rpp -= d_rpp;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->rpp *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* rvv */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_rvv ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->rvv += d_rvv;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_rvv ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->rvv -= d_rvv;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->rvv *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* chi */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_chi ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->chi += d_chi;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_chi ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->chi -= d_chi;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->chi *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* charge_ratio */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_charge_ratio ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->charge_ratio += d_charge_ratio;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_charge_ratio ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->charge_ratio -= d_charge_ratio;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->charge_ratio *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* charge0 */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_charge0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->charge0 += d_charge0;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_charge0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->charge0 -= d_charge0;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->charge0 *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* mass0 */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_mass0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->mass0 += d_mass0;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_mass0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->mass0 -= d_mass0;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->mass0 *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* beta0 */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_beta0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->beta0 += d_beta0;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_beta0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->beta0 -= d_beta0;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->beta0 *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* gamma0 */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_gamma0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->gamma0 += d_gamma0;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_gamma0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->gamma0 -= d_gamma0;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->gamma0 *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* pc0 */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_pc0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_pc0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->pc0 += d_pc0;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_pc0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_pc0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->pc0 -= d_pc0;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_pc0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->pc0 *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* s */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_s ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->s += d_s;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const d_s ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->s -= d_s;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->s *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* state */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_state ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->state += d_state;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_state ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->state -= d_state;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->state *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* at_element */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_at_element ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->at_element += d_at_element;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_at_element ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->at_element -= d_at_element;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->at_element *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* at_turn */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_at_turn ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->at_turn += d_at_turn;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_at_turn ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->at_turn -= d_at_turn;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->at_turn *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* id */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_id ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->id += d_id;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_subtract_from_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const d_id ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->id -= d_id;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_scale_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const c ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->id *= c;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* zeta */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_update_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const zeta ) SIXTRL_NOEXCEPT
{
    return NS(Particle_set_zeta)( p, zeta );
}

/* ------------------------------------------------------------------------- */
/* delta */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_update_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->beta0 >= ( real_t )0 );
    SIXTRL_ASSERT( p->beta0 <= ( real_t )1 );

    real_t const delta_plus_one = delta + ( real_t )1;
    real_t const delta_beta0 = delta * p->beta0;

    real_t ptau_beta0_plus_one = delta_beta0 * delta_beta0;
    ptau_beta0_plus_one += ( real_t )2  * delta_beta0 * p->beta0;
    ptau_beta0_plus_one += ( real_t )1;

    SIXTRL_ASSERT( ptau_beta0_plus_one >= ( real_t )0 );
    ptau_beta0_plus_one = NS(sqrt)( ptau_beta0_plus_one );

    SIXTRL_ASSERT( NS(abs)( delta ) >= ( real_t )0 );

    p->delta   = delta;
    p->rpp     = ( real_t )1 / delta_plus_one; /* rpp = 1 / ( delta + 1 ) */
    p->rvv     = delta_plus_one / ptau_beta0_plus_one;
    p->psigma  = ptau_beta0_plus_one - ( real_t )1 / ( p->beta0 * p->beta0 );

    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* sigma */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->rvv   >= ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( p->beta0 >= ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( p->beta0 <= ( NS(particle_real_t) )1 );

    return p->zeta / p->rvv;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_update_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const sigma ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->rvv   >= ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( p->beta0 >= ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( p->beta0 <= ( NS(particle_real_t) )1 );

    p->zeta = p->rvv * sigma;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* psigma */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_update_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const psigma ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->beta0 >= ( real_t )0 );
    SIXTRL_ASSERT( p->beta0 <= ( real_t )1 );

    real_t const ptau = psigma * p->beta0;
    real_t one_plus_delta = ptau * ptau;
    one_plus_delta += ( real_t )2 * psigma;
    one_plus_delta += ( real_t )1;

    SIXTRL_ASSERT( one_plus_delta >= ( real_t )0 );
    one_plus_delta = NS(sqrt)( one_plus_delta );

    real_t ptau_beta0_plus_one = ptau * p->beta0;
    ptau_beta0_plus_one += ( real_t )1;

    SIXTRL_ASSERT( ptau_beta0_plus_one >= ( real_t )0 );
    SIXTRL_ASSERT( one_plus_delta      >= ( real_t )0 );

    p->delta  = one_plus_delta - ( real_t )1;
    p->psigma = psigma;
    p->rpp    = ( real_t )1 / one_plus_delta;
    p->rvv    = one_plus_delta / ptau_beta0_plus_one;

    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* tau */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_tau)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->rvv   >  ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( p->beta0 >  ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( p->beta0 <= ( NS(particle_real_t) )1 );

    return p->zeta / ( p->beta0 * p->rvv );
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_update_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const tau ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->rvv   >  ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( p->beta0 >  ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( p->beta0 <= ( NS(particle_real_t) )1 );

    p->zeta = tau * ( p->beta0 * p->rvv );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* ptau */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_ptau)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->beta0 >= ( real_t )0 );
    SIXTRL_ASSERT( p->beta0 <= ( real_t )1 );

    real_t const inv_beta0 = ( real_t )1 / p->beta0;
    real_t temp = p->delta * p->delta;
    temp += ( real_t )2 * p->delta;
    temp += inv_beta0 * inv_beta0;

    SIXTRL_ASSERT( temp >= ( real_t )0 );
    return NS(sqrt)( temp ) - inv_beta0;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_update_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const ptau ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->beta0 >= ( real_t )0 );
    SIXTRL_ASSERT( p->beta0 <= ( real_t )1 );

    real_t const psigma = ptau / p->beta0;
    real_t ptau_beta0_plus_one = ptau * p->beta0;
    real_t one_plus_delta = ptau * ptau;

    ptau_beta0_plus_one += ( real_t )1;
    one_plus_delta += ( real_t )2 * psigma;
    one_plus_delta += ( real_t )1;

    SIXTRL_ASSERT( one_plus_delta >= ( real_t )0 );
    SIXTRL_ASSERT( NS(abs)( ptau_beta0_plus_one ) >= ( real_t )0 );

    one_plus_delta = NS(sqrt)( one_plus_delta );
    SIXTRL_ASSERT( one_plus_delta > ( real_t )0 );

    p->delta  = one_plus_delta - ( real_t )1;
    p->psigma = psigma;
    p->rpp    = ( real_t )1 / one_plus_delta;
    p->rvv    = one_plus_delta / ptau_beta0_plus_one;

    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* beta */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_beta)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->beta0 >= ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( p->beta0 <= ( NS(particle_real_t) )1 );

    return p->beta0 * p->rvv;
}

/* ------------------------------------------------------------------------- */
/* mass */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_mass_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(abs)( p->charge_ratio ) > ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( NS(abs)( p->chi ) > ( NS(particle_real_t) )0 );

    return p->charge_ratio / p->chi;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_mass)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    return NS(Particle_mass_ratio)( p ) * NS(Particle_mass0)( p );
}

/* ------------------------------------------------------------------------- */
/* charge */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_charge)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT
{
    return NS(Particle_charge_ratio)( p ) * NS(Particle_charge0)( p );
}

/* ------------------------------------------------------------------------- */
/* energy0 / energy / pc */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_energy0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->mass0 >  ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( p->pc0   >= ( NS(particle_real_t) )0 );
    return NS(sqrt)( p->mass0 * p->mass0 + p->pc0 * p->pc0 );
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->beta0 >= ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( p->beta0 <= ( NS(particle_real_t) )1 );
    SIXTRL_ASSERT( p->mass0 >  ( NS(particle_real_t) )0 );
    SIXTRL_ASSERT( p->pc0   >= ( NS(particle_real_t) )0 );

    return NS(sqrt)( p->pc0 * p->pc0 + p->mass0 * p->mass0 ) *
           NS(Particle_mass_ratio)( p ) + p->pc0 * p->beta0 * p->psigma;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_add_to_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_energy ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->beta0 >= ( real_t )0 );
    SIXTRL_ASSERT( p->beta0 <= ( real_t )1 );

    real_t const delta_beta0 = p->delta * p->beta0;
    real_t ptau_beta0_plus_one = delta_beta0 * delta_beta0 +
        ( real_t )2 * delta_beta0 * p->beta0 + ( real_t )1;

    SIXTRL_ASSERT( ptau_beta0_plus_one >= ( real_t )0 );
    SIXTRL_ASSERT( NS(Particle_energy0)( p ) >= ( real_t )0 );
    SIXTRL_ASSERT( ( NS(Particle_energy)( p ) + delta_energy ) >=
                     NS(Particle_energy0)( p ) );

    ptau_beta0_plus_one = NS(sqrt)( ptau_beta0_plus_one );
    ptau_beta0_plus_one += delta_energy / NS(Particle_energy0)( p );

    SIXTRL_ASSERT( ptau_beta0_plus_one >= ( real_t )0 );

    real_t ptau = ptau_beta0_plus_one - ( real_t )1;
    ptau /= p->beta0;

    p->psigma = ptau / p->beta0;

    real_t delta_plus_one = ptau * ptau + ( real_t )2 * p->psigma + ( real_t )1;
    SIXTRL_ASSERT( delta_plus_one >= ( real_t )0 );

    delta_plus_one = NS(sqrt)( delta_plus_one );
    SIXTRL_ASSERT( delta_plus_one >= ( NS(particle_real_t) )0 );

    p->delta  = delta_plus_one - ( real_t )1;
    p->rpp    = ( real_t )1 / delta_plus_one;
    p->rvv    = delta_plus_one / ptau_beta0_plus_one;

    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_update_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const E ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( E >= NS(Particle_energy0)( p ) );
    return NS(Particle_add_to_energy)( p, E - NS(Particle_energy)( p ) );
}

/* ------------------------------------------------------------------------- */
/* state */

SIXTRL_INLINE bool NS(Particle_is_lost)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( p->state != ( NS(particle_index_t) )1 );
}

SIXTRL_INLINE bool NS(Particle_is_not_lost)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( p->state == ( NS(particle_index_t) )1 );
}

SIXTRL_INLINE bool NS(Particle_has_any_lost)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( p->state != ( NS(particle_index_t) )1 );
}

SIXTRL_INLINE bool NS(Particle_has_any_not_lost)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( p->state == ( NS(particle_index_t) )1 );
}

SIXTRL_INLINE void NS(Particle_mark_as_lost)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->state = ( NS(particle_index_t) )0;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_update_state_if_not_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const state ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->state &= state;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* at_element, at_turn */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_increment_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    if( NS(Particle_is_not_lost)( p ) )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        ++p->at_element;
        return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_increment_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( NS(Particle_is_not_lost)( p ) )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        ++p->at_turn;
        status  = NS(Particle_set_default_at_element)( p );
        status |= NS(Particle_set_default_s)( p );
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t)
NS(Particle_increment_at_turn_detailed)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p, NS(particle_index_t) const at_element,
    NS(particle_real_t) const s ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( NS(Particle_is_not_lost)( p ) )
    {
        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
        ++p->at_turn;
        status  = NS(Particle_set_at_element)( p, at_element );
        status |= NS(Particle_set_s)( p, s );
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_DERIVED_API_H__ */
