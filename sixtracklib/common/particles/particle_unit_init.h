#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_INIT_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_INIT_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_unit.h"
    #include "sixtracklib/common/particles/particle_unit_api.h"
    #include "sixtracklib/common/particles/particle_unit_derived_api.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        template< class ParticleT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        Particle_preset_common( SIXTRL_PARTICLE_ARGPTR_DEC
            ParticleT* SIXTRL_RESTRICT p )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            static_assert(
                SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
                "ParticleT required to be legal particle unit class" );

            if( p != SIXTRL_NULLPTR )
            {
                status  = st::Particle_set_default_x( p );
                status |= st::Particle_set_default_px( p );
                status |= st::Particle_set_default_y( p );
                status |= st::Particle_set_default_py( p );
                status |= st::Particle_set_default_zeta( p );
                status |= st::Particle_set_default_delta( p );
                status |= st::Particle_set_default_psigma( p );
                status |= st::Particle_set_default_state( p );
                status |= st::Particle_set_default_at_element( p );
                status |= st::Particle_set_default_at_turn( p );
                status |= st::Particle_set_default_id( p );
                status |= st::Particle_set_default_s( p );
                status |= st::Particle_set_default_rvv( p );
                status |= st::Particle_set_default_rpp( p );
                status |= st::Particle_set_default_chi( p );
                status |= st::Particle_set_default_charge_ratio( p );
            }

            return status;
        }

        template< class ParticleT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        Particle_do_init_charge0_mass0_pc0(
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
            typename TypeMethodParamTraits< typename ParticleTraits<
                ParticleT >::real_t >::const_argument_type charge0,
            typename TypeMethodParamTraits< typename ParticleTraits<
                ParticleT >::real_t >::const_argument_type mass0,
            typename TypeMethodParamTraits< typename ParticleTraits<
                ParticleT >::real_t >::const_argument_type pc0 )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::Particle_is_type< ParticleT >(),
                "ParticleT required to be particle unit class" );

            typedef typename ParticleTraits< ParticleT >::real_t real_t;
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( st::Type_comp_all_more< real_t >( mass0, real_t{ 0 } ) ) &&
                ( st::Type_comp_all_more_or_equal< real_t >(
                    pc0, real_t{ 0 } ) ) &&
                ( st::Type_comp_all_more< real_t >( st::abs< real_t >(
                    charge0 ), real_t{ 0 } ) ) )
            {
                real_t const gamma0 = st::sqrt< real_t >(
                    pc0 * pc0 + mass0 * mass0 ) / mass0;

                real_t const beta0_squ = real_t{ 1 } -
                    real_t{ 1 } / ( gamma0 * gamma0 );

                SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                    gamma0, real_t{ 1 } ) );

                SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                    beta0_squ, real_t{ 0 } ) );

                real_t const beta0  = st::sqrt< real_t >( beta0_squ );

                status  = st::Particle_preset_common( p );
                status |= st::Particle_set_charge0( p, charge0 );
                status |= st::Particle_set_mass0( p, mass0 );
                status |= st::Particle_set_beta0( p, beta0 );
                status |= st::Particle_set_gamma0( p, gamma0 );
                status |= st::Particle_set_pc0( p, pc0 );
            }

            return status;
        }

        template< class ParticleT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        Particle_do_init_charge0_mass0_beta0(
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
            typename TypeMethodParamTraits< typename ParticleTraits<
                ParticleT >::real_t >::const_argument_type charge0,
            typename TypeMethodParamTraits< typename ParticleTraits<
                ParticleT >::real_t >::const_argument_type mass0,
            typename TypeMethodParamTraits< typename ParticleTraits<
                ParticleT >::real_t >::const_argument_type beta0 )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::Particle_is_type< ParticleT >(),
                "ParticleT required to be particle unit class" );

            typedef typename ParticleTraits< ParticleT >::real_t  real_t;
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( st::Type_comp_all_more< real_t >( mass0, real_t{ 0 } ) ) &&
                ( st::Type_comp_all_more_or_equal< real_t >(
                    beta0, real_t{ 0 } ) ) &&
                ( st::Type_comp_all_less_or_equal< real_t >(
                    beta0, real_t{ 1 } ) ) &&
                ( st::Type_comp_all_more< real_t >(
                    st::abs< real_t >( charge0 ), real_t{ 0 } ) ) )
            {
                real_t const gamma0 = real_t{ 1 } / st::sqrt< real_t >(
                    real_t{ 1 } - beta0 * beta0 );

                SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                    gamma0 * gamma0, real_t{ 1 } ) );

                real_t const pc0_squ = mass0 * mass0 * (
                    gamma0 * gamma0 - real_t{ 1 } );

                SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                    pc0_squ, real_t{ 0 } ) );

                real_t const pc0  = st::sqrt< real_t >( pc0_squ );

                status  = st::Particle_preset_common( p );
                status |= st::Particle_set_charge0( p, charge0 );
                status |= st::Particle_set_mass0( p, mass0 );
                status |= st::Particle_set_beta0( p, beta0 );
                status |= st::Particle_set_gamma0( p, gamma0 );
                status |= st::Particle_set_pc0( p, pc0 );
            }

            return status;
        }

        template< class ParticleT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        Particle_do_init_charge0_mass0_gamma0(
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
            typename TypeMethodParamTraits< typename ParticleTraits<
                ParticleT >::real_t >::const_argument_type charge0,
            typename TypeMethodParamTraits< typename ParticleTraits<
                ParticleT >::real_t >::const_argument_type mass0,
            typename TypeMethodParamTraits< typename ParticleTraits<
                ParticleT >::real_t >::const_argument_type gamma0 )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::Particle_is_type< ParticleT >(),
                "ParticleT required to be particle unit class" );

            typedef typename ParticleTraits< ParticleT >::real_t  real_t;
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( st::Type_comp_all_more< real_t >( mass0, real_t{ 0 } ) ) &&
                ( st::Type_comp_all_more_or_equal< real_t >(
                    gamma0, real_t{ 1 } ) ) &&
                ( st::Type_comp_all_more< real_t >(
                    st::abs< real_t >( charge0 ), real_t{ 0 } ) ) )
            {
                real_t const pc0_squ = mass0 * mass0 * (
                    gamma0 * gamma0 - real_t{ 1 } );

                SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                    pc0_squ, real_t{ 0 } ) );

                real_t const pc0  = st::sqrt< real_t >( pc0_squ );

                real_t const beta0_squ =
                    real_t{ 1 } - real_t{ 1 } / ( gamma0 * gamma0 );

                SIXTRL_ASSERT( st::Type_comp_all_more_or_equal< real_t >(
                    beta0_squ, real_t{ 0 } ) );

                real_t const beta0 = st::sqrt< real_t >( beta0_squ );

                status  = st::Particle_preset_common( p );
                status |= st::Particle_set_charge0( p, charge0 );
                status |= st::Particle_set_mass0( p, mass0 );
                status |= st::Particle_set_beta0( p, beta0 );
                status |= st::Particle_set_gamma0( p, gamma0 );
                status |= st::Particle_set_pc0( p, pc0 );
            }

            return status;
        }
    }

    /* --------------------------------------------------------------------- */
    /* init API: */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
    Particle_preset( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p
        ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
            "Particle_preset() called for illegal ParticleT class" );

        if( p != SIXTRL_NULLPTR )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef typename ParticleTraits< ParticleT >::real_t real_t;

            st::arch_status_t status = st::Particle_preset_common( p );

            status |= st::Particle_set_default_charge0( p );
            status |= st::Particle_set_default_mass0( p );
            status |= st::Particle_set_beta0( p, real_t{ 0 } );
            status |= st::Particle_set_gamma0( p, real_t{ 1 } );
            status |= st::Particle_set_pc0( p, real_t{ 0 } );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        return p;
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t Particle_init(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
            "Particle_init() called for illegal ParticleT class" );

        SIXTRL_CXX_NAMESPACE::Particle_preset( p );
        return ( p != SIXTRL_NULLPTR )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, typename Charge0Arg, typename Mass0Arg,
              typename Pc0Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticleTraits< ParticleT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticleTraits< ParticleT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Pc0Arg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_init_charge0_mass0_pc0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        Charge0Arg charge0, Mass0Arg mass0, Pc0Arg pc0 )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::Particle_do_init_charge0_mass0_pc0(
            p, charge0, mass0, pc0 );
    }

    template< class ParticleT, typename Charge0Arg, typename Mass0Arg,
              typename Pc0Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticleTraits< ParticleT >::real_t >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticleTraits< ParticleT >::real_t >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Pc0Arg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_init_charge0_mass0_pc0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        Charge0Arg in_charge0, Mass0Arg in_mass0, Pc0Arg in_pc0 )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be particle unit class" );

        typedef typename std::decay< Charge0Arg >::type charge0_real_t;
        typedef typename std::decay< Mass0Arg >::type   mass0_real_t;
        typedef typename std::decay< Pc0Arg >::type     pc0_real_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;

        real_t charge0;
        real_t mass0;
        real_t pc0;

        st::arch_status_t status = st::Types_perform_assignment<
            charge0_real_t, real_t >( charge0, in_charge0 );

        status |= st::Types_perform_assignment<
            mass0_real_t, real_t >( mass0, in_mass0 );

        status |= st::Types_perform_assignment<
            pc0_real_t, real_t >( pc0, in_pc0 );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = st::Particle_do_init_charge0_mass0_pc0(
                p, charge0, mass0, pc0 );
        }

        return status;
    }

    template< class ParticleT, typename Charge0Arg, typename Mass0Arg,
              typename Beta0Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticleTraits< ParticleT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticleTraits< ParticleT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Beta0Arg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_init_charge0_mass0_beta0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        Charge0Arg charge0, Mass0Arg mass0, Beta0Arg beta0 )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::Particle_do_init_charge0_mass0_beta0(
            p, charge0, mass0, beta0 );
    }

    template< class ParticleT, typename Charge0Arg, typename Mass0Arg,
              typename Beta0Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticleTraits< ParticleT >::real_t >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticleTraits< ParticleT >::real_t >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Beta0Arg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_init_charge0_mass0_beta0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        Charge0Arg in_charge0, Mass0Arg in_mass0, Beta0Arg in_beta0 )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be particle unit class" );

        typedef typename std::decay< Charge0Arg >::type charge0_real_t;
        typedef typename std::decay< Mass0Arg >::type   mass0_real_t;
        typedef typename std::decay< Beta0Arg >::type   beta0_real_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;

        real_t charge0;
        real_t mass0;
        real_t beta0;

        st::arch_status_t status = st::Types_perform_assignment<
            charge0_real_t, real_t >( charge0, in_charge0 );

        status |= st::Types_perform_assignment<
            mass0_real_t, real_t >( mass0, in_mass0 );

        status |= st::Types_perform_assignment<
            beta0_real_t, real_t >( beta0, in_beta0 );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = st::Particle_do_init_charge0_mass0_beta0(
                p, charge0, mass0, beta0 );
        }

        return status;
    }

    template< class ParticleT, typename Charge0Arg, typename Mass0Arg,
              typename Gamma0Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticleTraits< ParticleT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticleTraits< ParticleT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Gamma0Arg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_init_charge0_mass0_gamma0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        Charge0Arg charge0, Mass0Arg mass0, Gamma0Arg gamma0 )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::Particle_do_init_charge0_mass0_gamma0(
            p, charge0, mass0, gamma0 );
    }

    template< class ParticleT, typename Charge0Arg, typename Mass0Arg,
              typename Gamma0Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticleTraits< ParticleT >::real_t >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticleTraits< ParticleT >::real_t >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Gamma0Arg,
            typename ParticleTraits< ParticleT >::real_t >(),
        arch_status_t >::type
    Particle_init_charge0_mass0_gamma0(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        Charge0Arg in_charge0, Mass0Arg in_mass0, Gamma0Arg in_gamma0 )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_is_type< ParticleT >(),
            "ParticleT required to be particle unit class" );

        typedef typename std::decay< Charge0Arg >::type charge0_real_t;
        typedef typename std::decay< Mass0Arg >::type   mass0_real_t;
        typedef typename std::decay< Gamma0Arg >::type  gamma0_real_t;
        typedef typename ParticleTraits< ParticleT >::real_t real_t;

        real_t charge0;
        real_t mass0;
        real_t gamma0;

        st::arch_status_t status = st::Types_perform_assignment<
            charge0_real_t, real_t >( charge0, in_charge0 );

        status |= st::Types_perform_assignment<
            mass0_real_t, real_t >( mass0, in_mass0 );

        status |= st::Types_perform_assignment<
            gamma0_real_t, real_t >( gamma0, in_gamma0 );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = st::Particle_do_init_charge0_mass0_gamma0(
                p, charge0, mass0, gamma0 );
        }

        return status;
    }

    template< class ParticleT, typename XArg, typename PxArg, typename YArg,
        typename PyArg, typename ZetaArg, typename DeltaArg, typename StateArg,
        typename AtElemArg, typename AtTurnArg, typename ParticleIdArg,
        typename PSigmaArg, typename RppArg, typename RvvArg, typename ChiArg,
        typename ChargeRatioArg, typename Charge0Arg, typename Mass0Arg,
        typename Beta0Arg, typename Gamma0Arg, typename Pc0Arg, typename SArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t Particle_init_detailed(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        XArg x, PxArg px, YArg y, PyArg py, ZetaArg zeta, DeltaArg delta,
        StateArg state, AtElemArg at_element, AtTurnArg at_turn,
        ParticleIdArg id, PSigmaArg psigma, RppArg rpp, RvvArg rvv,
        ChiArg chi, ChargeRatioArg charge_ratio, Charge0Arg charge0,
        Mass0Arg mass0, Beta0Arg beta0, Gamma0Arg gamma0, Pc0Arg pc0, SArg s )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        st::arch_status_t status = ( p != SIXTRL_NULLPTR )
            ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;

        SIXTRL_ASSERT( p != SIXTRL_NULLPTR );

        static_assert(
            SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
            "Particle_init_detailed() called for illegal ParticleT class" );

        status |= st::Particle_set_x( p, x );
        status |= st::Particle_set_px( p, px );
        status |= st::Particle_set_y( p, y );
        status |= st::Particle_set_py( p, py );
        status |= st::Particle_set_zeta( p, zeta );
        status |= st::Particle_set_delta( p, delta );

        status |= st::Particle_set_state( p, state );
        status |= st::Particle_set_at_element( p, at_element );
        status |= st::Particle_set_at_turn( p, at_turn );
        status |= st::Particle_set_id( p, id );

        status |= st::Particle_set_psigma( p, psigma );
        status |= st::Particle_set_rpp( p, rpp );
        status |= st::Particle_set_rvv( p, rvv );
        status |= st::Particle_set_chi( p, chi );
        status |= st::Particle_set_charge_ratio( p, charge_ratio );

        status |= st::Particle_set_charge0( p, charge0 );
        status |= st::Particle_set_mass0( p, mass0 );
        status |= st::Particle_set_beta0( p, beta0 );
        status |= st::Particle_set_gamma0( p, gamma0 );
        status |= st::Particle_set_pc0( p, pc0 );

        status |= st::Particle_set_s( p, s );

        return status;
    }

    template< class ParticleT, typename XArg, typename PxArg, typename YArg,
        typename PyArg, typename ZetaArg, typename DeltaArg, typename StateArg,
        typename AtElemArg, typename AtTurnArg, typename ParticleIdArg,
        typename PSigmaArg, typename RppArg, typename RvvArg, typename ChiArg,
        typename ChargeRatioArg, typename Charge0Arg, typename Mass0Arg,
        typename Beta0Arg, typename Gamma0Arg, typename Pc0Arg, typename SArg >
    SIXTRL_STATIC SIXTRL_FN arch_status_t Particle_init(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        XArg x, PxArg px, YArg y, PyArg py, ZetaArg zeta, DeltaArg delta,
        StateArg state, AtElemArg at_element, AtTurnArg at_turn,
        ParticleIdArg id, PSigmaArg psigma, RppArg rpp, RvvArg rvv,
        ChiArg chi, ChargeRatioArg charge_ratio, Charge0Arg charge0,
        Mass0Arg mass0, Beta0Arg beta0, Gamma0Arg gamma0, Pc0Arg pc0, SArg s )
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
            "Particle_init() called for illegal ParticleT class" );

        return SIXTRL_CXX_NAMESPACE::Particle_init_detailed( p, x, px, y, py,
            zeta, delta, state, at_element, at_turn, id, psigma, rpp, rvv,
                chi, charge_ratio, charge0, mass0, beta0, gamma0, pc0, s );
    }

    template< class ParticleT, typename Charge0Arg, typename Mass0Arg,
              typename ArgT >
    SIXTRL_STATIC SIXTRL_FN arch_status_t Particle_init(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        Charge0Arg charge0, Mass0Arg mass0, ArgT arg,
        particle_init_flag_t const flag =
            ::NS(PARTICLE_INIT_CHARGE0_MASS0_BETA0) )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        static_assert(
            SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
            "Particle_init() called for illegal ParticleT class" );

        switch( flag )
        {
            case ::NS(PARTICLE_INIT_CHARGE0_MASS0_PC0):
            {
                status = st::Particle_init_charge0_mass0_pc0(
                    p, charge0, mass0, arg );
                break;
            }

            case ::NS(PARTICLE_INIT_CHARGE0_MASS0_BETA0):
            {
                status = st::Particle_init_charge0_mass0_beta0(
                    p, charge0, mass0, arg );
                break;
            }

            case ::NS(PARTICLE_INIT_CHARGE0_MASS0_GAMMA0):
            {
                status = st::Particle_init_charge0_mass0_gamma0(
                    p, charge0, mass0, arg );
                break;
            }

            default:
            {
                SIXTRL_ASSERT(
                    ( flag == ::NS(PARTICLE_INIT_CHARGE0_MASS0_PC0) ) ||
                    ( flag == ::NS(PARTICLE_INIT_CHARGE0_MASS0_BETA0) ) ||
                    ( flag == ::NS(PARTICLE_INIT_CHARGE0_MASS0_GAMMA0) ) );

                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }
        };

        return status;
    }

    /* ********************************************************************* */

    template< class ParticleT, store_backend_t StoreT >
    struct ObjDataInitialiser< ParticleT, StoreT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(), void
            >::type >
    {
        SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
        preset( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT obj )
        {
            return SIXTRL_CXX_NAMESPACE::Particle_preset( obj );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t init(
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT obj,
            Args&&... init_args )
        {
            return SIXTRL_CXX_NAMESPACE::Particle_init(
                obj, std::forward< Args >( init_args )... );
        }
    };
}


/* ------------------------------------------------------------------------- */
/* init API: */

template< class ParticleT >
SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
NS(Particle_preset)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p
    ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Particle_preset( p );
}

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_init)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Particle_init( p );
}

template< class ParticleT, typename Charge0Arg, typename Mass0Arg,
          typename Pc0Arg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_init_charge0_mass0_pc0)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    Charge0Arg charge0, Mass0Arg mass0, Pc0Arg pc0 )
{
    return SIXTRL_CXX_NAMESPACE::Particle_init_charge0_mass0_pc0(
        p, charge0, mass0, pc0 );
}

template< class ParticleT, typename Charge0Arg, typename Mass0Arg,
          typename Beta0Arg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_init_charge0_mass0_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    Charge0Arg charge0, Mass0Arg mass0, Beta0Arg beta0 )
{
    return SIXTRL_CXX_NAMESPACE::Particle_init_charge0_mass0_beta0(
        p, charge0, mass0, beta0 );
}

template< class ParticleT, typename Charge0Arg, typename Mass0Arg,
          typename Gamma0Arg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_init_charge0_mass0_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    Charge0Arg charge0, Mass0Arg mass0, Gamma0Arg gamma0 )
{
    return SIXTRL_CXX_NAMESPACE::Particle_init_charge0_mass0_gamma0(
        p, charge0, mass0, gamma0 );
}

template< class ParticleT, typename XArg, typename PxArg, typename YArg,
    typename PyArg, typename ZetaArg, typename DeltaArg, typename StateArg,
    typename AtElemArg, typename AtTurnArg, typename ParticleIdArg,
    typename PSigmaArg, typename RppArg, typename RvvArg, typename ChiArg,
    typename ChargeRatioArg, typename Charge0Arg, typename Mass0Arg,
    typename Beta0Arg, typename Gamma0Arg, typename Pc0Arg, typename SArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_init_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    XArg x, PxArg px, YArg y, PyArg py, ZetaArg zeta, DeltaArg delta,
    StateArg state, AtElemArg at_element, AtTurnArg at_turn, ParticleIdArg id,
    PSigmaArg psigma,  RppArg rpp, RvvArg rvv, ChiArg chi,
    ChargeRatioArg charge_ratio, Charge0Arg charge0, Mass0Arg mass0,
    Beta0Arg beta0, Gamma0Arg gamma0, Pc0Arg pc0, SArg s )
{
    return SIXTRL_CXX_NAMESPACE::Particle_init_detailed( p, x, px, y, py, zeta,
        delta, state, at_element, at_turn, id, psigma, rpp, rvv, chi,
            charge_ratio, charge0, mass0, beta0, gamma0, pc0, s );
}

template< class ParticleT, typename XArg, typename PxArg, typename YArg,
    typename PyArg, typename ZetaArg, typename DeltaArg, typename PSigmaArg,
    typename StateArg, typename AtElemArg, typename AtTurnArg,
    typename ParticleIdArg, typename SArg, typename RppArg, typename RvvArg,
    typename ChiArg, typename ChargeRatioArg, typename Charge0Arg,
    typename Mass0Arg, typename Beta0Arg, typename Gamma0Arg,
    typename Pc0Arg >
SIXTRL_STATIC SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t NS(Particle_init)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    XArg x, PxArg px, YArg y, PyArg py, ZetaArg zeta, DeltaArg delta,
    StateArg state, AtElemArg at_element, AtTurnArg at_turn, ParticleIdArg id,
    PSigmaArg psigma, RppArg rpp, RvvArg rvv, ChiArg chi,
    ChargeRatioArg charge_ratio, Charge0Arg charge0, Mass0Arg mass0,
    Beta0Arg beta0, Gamma0Arg gamma0, Pc0Arg pc0, SArg s )
{
    return SIXTRL_CXX_NAMESPACE::Particle_init( p, x, px, y, py, zeta, delta,
        state, at_element, at_turn, id, psigma, rpp, rvv, chi, charge_ratio,
            charge0, mass0, beta0, gamma0, pc0, s );
}

template< class ParticleT, typename Charge0Arg, typename Mass0Arg,
          typename ArgT >
SIXTRL_STATIC SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t NS(Particle_init)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    Charge0Arg charge0, Mass0Arg mass0, ArgT arg,
    SIXTRL_CXX_NAMESPACE::particle_init_flag_t const flag =
        ::NS(PARTICLE_INIT_CHARGE0_MASS0_BETA0) )
{
    return SIXTRL_CXX_NAMESPACE::Particle_init( p, charge0, mass0, arg, flag );
}

#endif /* C++ */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */


#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */


#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ------------------------------------------------------------------------- */
/* init */

SIXTRL_INLINE NS(arch_status_t) NS(Particle_preset_common)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( p != SIXTRL_NULLPTR )
    {
        status  = NS(Particle_set_default_x)( p );
        status |= NS(Particle_set_default_px)( p );
        status |= NS(Particle_set_default_y)( p );
        status |= NS(Particle_set_default_py)( p );
        status |= NS(Particle_set_default_zeta)( p );
        status |= NS(Particle_set_default_delta)( p );
        status |= NS(Particle_set_default_psigma)( p );
        status |= NS(Particle_set_default_state)( p );
        status |= NS(Particle_set_default_at_element)( p );
        status |= NS(Particle_set_default_at_turn)( p );
        status |= NS(Particle_set_default_id)( p );
        status |= NS(Particle_set_default_s)( p );
        status |= NS(Particle_set_default_rvv)( p );
        status |= NS(Particle_set_default_rpp)( p );
        status |= NS(Particle_set_default_chi)( p );
        status |= NS(Particle_set_default_charge_ratio)( p );
    }

    return status;
}

SIXTRL_INLINE SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* NS(Particle_preset)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    if( p != SIXTRL_NULLPTR )
    {
        NS(arch_status_t) status = NS(Particle_preset_common)( p );
        status |= NS(Particle_set_default_charge0)( p );
        status |= NS(Particle_set_default_mass0)( p );
        status |= NS(Particle_set_beta0)( p, ( NS(particle_real_t) )0 );
        status |= NS(Particle_set_gamma0)( p, ( NS(particle_real_t) )1 );
        status |= NS(Particle_set_pc0)( p, ( NS(particle_real_t) )0 );

        SIXTRL_ASSERT( status == ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    return p;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_init)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    NS(Particle_preset)( p );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_init_charge0_mass0_pc0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const charge0, NS(particle_real_t) const mass0,
    NS(particle_real_t) const pc0 ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( mass0 >= ( real_t )0 );
    SIXTRL_ASSERT( NS(abs)( charge0 ) >= ( real_t )0 );

    real_t const energy0   = NS(sqrt)( pc0 * pc0 + mass0 * mass0 );
    real_t const gamma0    = energy0 / mass0;
    real_t const beta0_squ = ( real_t )1 - ( real_t )1 / ( gamma0 * gamma0 );

    SIXTRL_ASSERT( gamma0    >= ( real_t )1 );
    SIXTRL_ASSERT( beta0_squ >= ( real_t )0 );

    NS(arch_status_t) status = NS(Particle_preset_common)( p );
    status |= NS(Particle_set_charge0)( p, charge0 );
    status |= NS(Particle_set_mass0)( p, mass0 );
    status |= NS(Particle_set_beta0)( p, NS(sqrt)( beta0_squ ) );
    status |= NS(Particle_set_gamma0)( p, gamma0 );
    status |= NS(Particle_set_pc0)( p, pc0 );

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_init_charge0_mass0_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const charge0, NS(particle_real_t) const mass0,
    NS(particle_real_t) const beta0 ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( mass0 >= ( real_t )0 );
    SIXTRL_ASSERT( NS(abs)( charge0 ) >= ( real_t )0 );
    SIXTRL_ASSERT( beta0 >= ( real_t )0 );
    SIXTRL_ASSERT( beta0 <= ( real_t )1 );

    real_t const gamma0  = ( real_t )1 / NS(sqrt)( ( real_t )1 - beta0 * beta0 );
    real_t const energy0 = gamma0 * mass0;
    real_t const pc0_squ = energy0 * energy0 - mass0 * mass0;

    SIXTRL_ASSERT( pc0_squ >= ( real_t )0 );

    NS(arch_status_t) status = NS(Particle_preset_common)( p );
    status |= NS(Particle_set_charge0)( p, charge0 );
    status |= NS(Particle_set_mass0)( p, mass0 );
    status |= NS(Particle_set_beta0)( p, beta0 );
    status |= NS(Particle_set_gamma0)( p, gamma0 );
    status |= NS(Particle_set_pc0)( p, NS(sqrt)( pc0_squ ) );

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_init_charge0_mass0_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const charge0, NS(particle_real_t) const mass0,
    NS(particle_real_t) const gamma0 ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( mass0 >= ( real_t )0 );
    SIXTRL_ASSERT( NS(abs)( charge0 ) >= ( real_t )0 );
    SIXTRL_ASSERT( gamma0 >= ( real_t )1 );

    real_t const   beta0_squ  = ( real_t )1 - ( real_t )1 / ( gamma0 * gamma0 );
    SIXTRL_ASSERT( beta0_squ >= ( real_t )0 );

    real_t const energy0 = gamma0 * mass0;
    real_t const pc0_squ = energy0 * energy0 - mass0 * mass0;
    SIXTRL_ASSERT( pc0_squ >= ( real_t )0 );

    NS(arch_status_t) status = NS(Particle_preset_common)( p );
    status |= NS(Particle_set_charge0)( p, charge0 );
    status |= NS(Particle_set_mass0)( p, mass0 );
    status |= NS(Particle_set_beta0)( p, NS(sqrt)( beta0_squ ) );
    status |= NS(Particle_set_gamma0)( p, gamma0 );
    status |= NS(Particle_set_pc0)( p, NS(sqrt)( pc0_squ ) );

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_init_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t)  const x,        NS(particle_real_t)  const px,
    NS(particle_real_t)  const y,        NS(particle_real_t)  const py,
    NS(particle_real_t)  const zeta,     NS(particle_real_t)  const delta,
    NS(particle_index_t) const state,    NS(particle_index_t) const at_element,
    NS(particle_index_t) const at_turn,  NS(particle_index_t) const id,
    NS(particle_real_t)  const psigma,   NS(particle_real_t)  const rpp,
    NS(particle_real_t)  const rvv,      NS(particle_real_t)  const chi,
    NS(particle_real_t)  const charge_ratio,
    NS(particle_real_t)  const charge0,  NS(particle_real_t)  const mass0,
    NS(particle_real_t)  const beta0,    NS(particle_real_t)  const gamma0,
    NS(particle_real_t)  const pc0,      NS(particle_real_t)  const s
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );

    NS(arch_status_t) status = NS(Particle_set_x)( p, x );
    status |= NS(Particle_set_px)( p, px );
    status |= NS(Particle_set_y)( p, y );
    status |= NS(Particle_set_py)( p, py );
    status |= NS(Particle_set_zeta)( p, zeta );
    status |= NS(Particle_set_delta)( p, delta );
    status |= NS(Particle_set_psigma)( p, psigma );

    status |= NS(Particle_set_state)( p, state );
    status |= NS(Particle_set_at_element)( p, at_element );
    status |= NS(Particle_set_at_turn)( p, at_turn );
    status |= NS(Particle_set_id)( p, id );

    status |= NS(Particle_set_s)( p, s );
    status |= NS(Particle_set_rvv)( p, rvv );
    status |= NS(Particle_set_rpp)( p, rpp );
    status |= NS(Particle_set_chi)( p, chi );
    status |= NS(Particle_set_charge_ratio)( p, charge_ratio );

    status |= NS(Particle_set_charge0)( p, charge0 );
    status |= NS(Particle_set_mass0)( p, mass0 );
    status |= NS(Particle_set_beta0)( p, beta0 );
    status |= NS(Particle_set_gamma0)( p, gamma0 );
    status |= NS(Particle_set_pc0)( p, pc0 );

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_INIT_H__ */
