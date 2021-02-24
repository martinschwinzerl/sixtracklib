#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLES_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLES_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particles.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/obj_convert.hpp"
    #include "sixtracklib/common/internal/obj_data_type_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ParticlesImplTraits< ::NS(Particles) >
    {
        static constexpr SIXTRL_CXX_NAMESPACE::particles_impl_type
            IMPLEMENTATION = SIXTRL_CXX_NAMESPACE::PARTICLES_IMPL_DEFAULT;
    };

    template<> struct ObjDataCApiTypeTraits< ::NS(Particles) >
    {
        typedef ::NS(Particles) c_api_type;
    };

    typedef ::NS(Particle) Particle;
}
#endif /* defined( __cplusplus ) */

/* ========================================================================== */
/* Type related helpers */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticlesT >
    static SIXTRL_FN constexpr bool Particles_is_type() SIXTRL_NOEXCEPT {
        return ( SIXTRL_CXX_NAMESPACE::ParticlesImplTraits< ParticlesT
            >::IMPLEMENTATION == SIXTRL_CXX_NAMESPACE::PARTICLE_IMPL_DEFAULT ); }

    template< class ParticlesT >
    static SIXTRL_FN constexpr bool Particles_is_default_impl() SIXTRL_NOEXCEPT {
        return ( SIXTRL_CXX_NAMESPACE::ParticlesImplTraits< ParticlesT
            >::IMPLEMENTATION == SIXTRL_CXX_NAMESPACE::PARTICLE_IMPL_DEFAULT ); }

    /* ---------------------------------------------------------------------- */
    /* conversions */

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool Particles_allow_type_conversion(
        SIXTRL_PARTICLES_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( dst ) = SIXTRL_NULLPTR,
        SIXTRL_PARTICLES_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ( ( SIXTRL_CXX_NAMESPACE::Particles_is_type< SrcT >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::Particles_is_type< DstT >() ) &&
                 ( ParticlesDimensionTraits< DstT >::DIMENSION >=
                   ParticlesDimensionTraits< SrcT >::DIMENSION ) &&
                 ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                     typename ParticlesTypeTraits< SrcT >::real_type,
                     typename ParticlesTypeTraits< DstT >::real_type >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                     typename ParticlesTypeTraits< SrcT >::index_type,
                     typename ParticlesTypeTraits< DstT >::index_type >() ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    Particles_type_conv_can_requ_prepare(
        SIXTRL_PARTICLES_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
        SIXTRL_PARTICLES_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return false;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool Particles_requ_prepare_conversion(
        SIXTRL_PARTICLES_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_PARTICLES_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_type const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_type const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_allow_type_conversion< SrcT, DstT >(),
                       "Illegal conversion" );

        SIXTRL_ASSERT( src != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( dst != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( src_store_be != st::STORAGE_BE_ILLEGAL );
        SIXTRL_ASSERT( dst_store_be != st::STORAGE_BE_ILLEGAL );

        ( void )src;
        ( void )dst;
        ( void )src_store_be;
        ( void )dst_store_be;

        return false;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool Particles_allow_conversion(
        SIXTRL_PARTICLES_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_PARTICLES_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_type const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_type const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( ( st::Particles_allow_type_conversion< SrcT, DstT >() ) &&
                 ( src_store_be != st::STORAGE_BE_ILLEGAL ) &&
                 ( dst_store_be != st::STORAGE_BE_ILLEGAL ) &&
                 ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::status_type
    Particles_prepare_conversion(
        SIXTRL_PARTICLES_ARGPTR_DEC DstT* SIXTRL_RESTRICT dest,
        SIXTRL_PARTICLES_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_type src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_type dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_allow_type_conversion< SrcT, DstT >(),
            "conversion from SrcT to DstT is not allowed" );

        return ( ( src != SIXTRL_NULLPTR ) && ( dest != SIXTRL_NULLPTR ) &&
                 ( src_store_be != st::STORAGE_BE_ILLEGAL ) &&
                 ( dst_store_be != st::STORAGE_BE_ILLEGAL ) )
            ? st::STATUS_SUCCESS : st::STATUS_GENERAL_FAILURE;
    }

    template< class SrcT, class DstT, typename... Args >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particles_allow_type_conversion< SrcT, DstT >(),
         SIXTRL_CXX_NAMESPACE::status_type >::type
    Particles_convert(
        SIXTRL_PARTICLES_ARGPTR_DEC DstT* SIXTRL_RESTRICT SIXTRL_UNUSED( dst ),
        SIXTRL_PARTICLES_ARGPTR_DEC const SrcT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( src ),
        SIXTRL_CXX_NAMESPACE::store_backend_type const SIXTRL_UNUSED(
            src_store_be ) = STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_type const SIXTRL_UNUSED(
            dst_store_be ) = STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
    }

    template< class SrcT, class DstT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particles_allow_type_conversion< SrcT, DstT >() &&
        SIXTRL_CXX_NAMESPACE::Particles_is_default_impl< SrcT >() &&
        SIXTRL_CXX_NAMESPACE::Particles_is_default_impl< DstT >(),
        status_type >::type
    Particles_convert(
        SIXTRL_PARTICLES_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_PARTICLES_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_type const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_type const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        Args&&... SIXTRL_UNUSED( conv_parameters ) )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_allow_type_conversion< SrcT, DstT >(),
                       "illegal conversion" );

        SIXTRL_ASSERT( st::Particles_allow_conversion(
            dst, src, src_store_be, dst_store_be ) );

        ( void )src_store_be;
        ( void )dst_store_be;

        ::NS(Particles_set_x)(         dst, ::NS(Particles_x)( src ) );
        ::NS(Particles_set_px)(         dst, ::NS(Particles_px)( src ) );
        ::NS(Particles_set_y)(          dst, ::NS(Particles_y)( src ) );
        ::NS(Particles_set_py)(         dst, ::NS(Particles_py)( src ) );
        ::NS(Particles_set_zeta)(       dst, ::NS(Particles_zeta)( src ) );
        ::NS(Particles_set_delta)(      dst, ::NS(Particles_delta)( src ) );
        ::NS(Particles_set_psigma)(     dst, ::NS(Particles_psigma)( src ) );

        ::NS(Particles_set_state)(      dst, ::NS(Particles_state)( src ) );
        ::NS(Particles_set_at_element)( dst, ::NS(Particles_at_element)( src ) );
        ::NS(Particles_set_at_turn)(    dst, ::NS(Particles_at_turn)( src ) );
        ::NS(Particles_set_id)(         dst, ::NS(Particles_id)( src ) );

        ::NS(Particles_set_s)(          dst, ::NS(Particles_s)( src ) );
        ::NS(Particles_set_rvv)(        dst, ::NS(Particles_rvv)( src ) );
        ::NS(Particles_set_rpp)(        dst, ::NS(Particles_rpp)( src ) );
        ::NS(Particles_set_chi)(        dst, ::NS(Particles_chi)( src ) );
        ::NS(Particles_set_charge_ratio)(
            dst, ::NS(Particles_charge_ratio)( src ) );

        ::NS(Particles_set_charge0)(    dst, ::NS(Particles_charge0)( src ) );
        ::NS(Particles_set_mass0)(      dst, ::NS(Particles_mass0)( src ) );
        ::NS(Particles_set_beta0)(      dst, ::NS(Particles_beta0)( src ) );
        ::NS(Particles_set_gamma0)(     dst, ::NS(Particles_gamma0)( src ) );
        ::NS(Particles_set_p0c)(        dst, ::NS(Particles_p0c)( src ) );

        return st::STATUS_SUCCESS;
    }

    /* ********************************************************************* */
    /* NS(Particle): */

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_type SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_type DstStoreT >
    struct ObjDataAllowConversionTraits<
        ::NS(Particle), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(Particle) SrcT;

        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::Particles_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_type SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_type DstStoreT >
    struct ObjDataConverter< ::NS(Particle), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(Particle) SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_type_conversion_requ_no_prepare< SrcT,
                DstT, SrcStoreT, DstStoreT >(), "Should not require prepare" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_PARTICLES_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLES_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particles_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::status_type prepare(
            SIXTRL_PARTICLES_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLES_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particles_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_PARTICLES_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLES_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particles_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::status_type attempt_conversion(
            SIXTRL_PARTICLES_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLES_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particles_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::status_type perform(
            SIXTRL_PARTICLES_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLES_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particles_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }
    };

    /* ---------------------------------------------------------------------- */
    /* initialization */

    template< class ParticlesT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN status_type Particles_init(
        SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_is_type< ParticlesT >(),
                       "Particles_init() called for illegal ParticlesT class" );

        return ( ::NS(Particles_preset)( p ) != SIXTRL_NULLPTR )
            ? st::STATUS_SUCCESS : st::STATUS_GENERAL_FAILURE;
    }

    template< class ParticlesT, typename Charge0Arg, typename Mass0Arg,
              typename P0cArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< P0cArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >(),
        SIXTRL_CXX_NAMESPACE::status_type >::type
    Particles_init_charge0_mass0_p0c(
        SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT* SIXTRL_RESTRICT p,
        Charge0Arg charge0, Mass0Arg mass0, P0cArg p0c )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_is_type< ParticlesT >(),
                       "ParticlesT required to be particle class" );

        typedef typename st::ParticlesTypeTraits< ParticlesT >::real_type real_type;
        SIXTRL_PARTICLE_DATAPTR_DEC real_type beta0  = real_type{ 0. };
        SIXTRL_PARTICLE_DATAPTR_DEC real_type gamma0 = real_type{ 1. };

        ::NS(Particles_preset)( p );
        ::NS(Particles_beta0_gamma0_from_charge0_mass0_p0c_impl)(
            charge0, mass0, p0c, &beta0, &gamma0 );

        ::NS(Particles_set_charge0)( p, charge0 );
        ::NS(Particles_set_mass0)( p, mass0 );
        ::NS(Particles_set_beta0)( p, beta0 );
        ::NS(Particles_set_gamma0)( p, gamma0 );
        ::NS(Particles_set_p0c)( p, p0c );

        return st::STATUS_SUCCESS;
    }

    template< class ParticlesT, typename Charge0Arg, typename Mass0Arg,
              typename P0cArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< P0cArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >(),
        SIXTRL_CXX_NAMESPACE::status_type >::type
    Particles_init_charge0_mass0_p0c(
        SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT* SIXTRL_RESTRICT p,
        Charge0Arg in_charge0, Mass0Arg in_mass0, P0cArg in_p0c )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_is_type< ParticlesT >(),
                       "ParticlesT required to be particle class" );

        typedef typename std::decay< Charge0Arg >::type charge0_real_type;
        typedef typename std::decay< Mass0Arg >::type   mass0_real_type;
        typedef typename std::decay< P0cArg >::type     p0c_real_type;
        typedef typename st::ParticlesTypeTraits< ParticlesT >::real_type real_type;

        real_type charge0;
        real_type mass0;
        real_type p0c;

        st::status_type status = st::Types_perform_assignment<
            charge0_real_type, real_type >( charge0, in_charge0 );

        status |= st::Types_perform_assignment<
            mass0_real_type, real_type >( mass0, in_mass0 );

        status |= st::Types_perform_assignment<
            p0c_real_type, real_type >( p0c, in_p0c );

        if( status == st::STATUS_SUCCESS )
        {
            SIXTRL_PARTICLE_DATAPTR_DEC real_type beta0 = real_type{ 0. };
            SIXTRL_PARTICLE_DATAPTR_DEC real_type gamma0 = real_type{ 0. };

            ::NS(Particles_preset)( p );
            ::NS(Particles_beta0_gamma0_from_charge0_mass0_p0c_impl)(
                charge0, mass0, p0c, &beta0, &gamma0 );

            ::NS(Particles_set_charge0)( p, charge0 );
            ::NS(Particles_set_mass0)( p, mass0 );
            ::NS(Particles_set_beta0)( p, beta0 );
            ::NS(Particles_set_gamma0)( p, gamma0 );
            ::NS(Particles_set_p0c)( p, p0c );
        }

        return status;
    }

    template< class ParticlesT, typename Charge0Arg, typename Mass0Arg,
              typename Beta0Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Beta0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >(),
        SIXTRL_CXX_NAMESPACE::status_type >::type
    Particles_init_charge0_mass0_beta0(
        SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT* SIXTRL_RESTRICT p,
        Charge0Arg charge0, Mass0Arg mass0, Beta0Arg beta0 )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_is_type< ParticlesT >(),
                       "ParticlesT required to be particle class" );

        typedef typename st::ParticlesTypeTraits< ParticlesT >::real_type real_type;
        SIXTRL_PARTICLE_DATAPTR_DEC real_type gamma0 = real_type{ 1. };
        SIXTRL_PARTICLE_DATAPTR_DEC real_type p0c  = real_type{ 0. };

        ::NS(Particles_preset)( p );
        ::NS(Particles_gamma0_p0c_from_charge0_mass0_beta0_impl)(
            charge0, mass0, beta0, &gamma0, &p0c );

        ::NS(Particles_set_charge0)( p, charge0 );
        ::NS(Particles_set_mass0)( p, mass0 );
        ::NS(Particles_set_beta0)( p, beta0 );
        ::NS(Particles_set_gamma0)( p, gamma0 );
        ::NS(Particles_set_p0c)( p, p0c );

        return st::STATUS_SUCCESS;
    }

    template< class ParticlesT, typename Charge0Arg, typename Mass0Arg,
              typename Beta0Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Beta0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >(),
        SIXTRL_CXX_NAMESPACE::status_type >::type
    Particles_init_charge0_mass0_beta0(
        SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT* SIXTRL_RESTRICT p,
        Charge0Arg in_charge0, Mass0Arg in_mass0, Beta0Arg in_beta0 )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_is_type< ParticlesT >(),
                       "ParticlesT required to be particle class" );

        typedef typename std::decay< Charge0Arg >::type charge0_real_type;
        typedef typename std::decay< Mass0Arg >::type   mass0_real_type;
        typedef typename std::decay< Beta0Arg >::type   beta0_real_type;
        typedef typename st::ParticlesTypeTraits< ParticlesT >::real_type real_type;

        real_type charge0;
        real_type mass0;
        real_type beta0;

        st::status_type status = st::Types_perform_assignment<
            charge0_real_type, real_type >( charge0, in_charge0 );

        status |= st::Types_perform_assignment<
            mass0_real_type, real_type >( mass0, in_mass0 );

        status |= st::Types_perform_assignment<
            beta0_real_type, real_type >( beta0, in_beta0 );

        if( status == st::STATUS_SUCCESS )
        {
            SIXTRL_PARTICLE_DATAPTR_DEC real_type gamma0 = real_type{ 1. };
            SIXTRL_PARTICLE_DATAPTR_DEC real_type p0c = real_type{ 0. };

            ::NS(Particles_preset)( p );
            ::NS(Particles_gamma0_p0c_from_charge0_mass0_beta0_impl)(
                charge0, mass0, beta0, &gamma0, &p0c );

            ::NS(Particles_set_charge0)( p, charge0 );
            ::NS(Particles_set_mass0)( p, mass0 );
            ::NS(Particles_set_beta0)( p, beta0 );
            ::NS(Particles_set_gamma0)( p, gamma0 );
            ::NS(Particles_set_p0c)( p, p0c );
        }

        return status;
    }

    template< class ParticlesT, typename Charge0Arg, typename Mass0Arg,
              typename Gamma0Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Gamma0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >(),
        SIXTRL_CXX_NAMESPACE::status_type >::type
    Particles_init_charge0_mass0_gamma0(
        SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT* SIXTRL_RESTRICT p,
        Charge0Arg charge0, Mass0Arg mass0, Gamma0Arg gamma0 )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_is_type< ParticlesT >(),
                       "ParticlesT required to be particle class" );

        typedef typename st::ParticlesTypeTraits< ParticlesT >::real_type real_type;
        SIXTRL_PARTICLE_DATAPTR_DEC real_type beta0 = real_type{ 0. };
        SIXTRL_PARTICLE_DATAPTR_DEC real_type p0c  = real_type{ 0. };

        ::NS(Particles_preset)( p );
        ::NS(Particles_beta0_p0c_from_charge0_mass0_gamma0_impl)(
            charge0, mass0, gamma0, &beta0, &p0c );

        ::NS(Particles_set_charge0)( p, charge0 );
        ::NS(Particles_set_mass0)( p, mass0 );
        ::NS(Particles_set_beta0)( p, beta0 );
        ::NS(Particles_set_gamma0)( p, gamma0 );
        ::NS(Particles_set_p0c)( p, p0c );

        return st::STATUS_SUCCESS;
    }

    template< class ParticlesT, typename Charge0Arg, typename Mass0Arg,
              typename Gamma0Arg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Gamma0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >(),
        SIXTRL_CXX_NAMESPACE::status_type >::type
    Particles_init_charge0_mass0_gamma0(
        SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT* SIXTRL_RESTRICT p,
        Charge0Arg in_charge0, Mass0Arg in_mass0, Gamma0Arg in_gamma0 )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_is_type< ParticlesT >(),
                       "ParticlesT required to be particle class" );

        typedef typename std::decay< Charge0Arg >::type charge0_real_type;
        typedef typename std::decay< Mass0Arg >::type   mass0_real_type;
        typedef typename std::decay< Gamma0Arg >::type   gamma0_real_type;
        typedef typename st::ParticlesTypeTraits< ParticlesT >::real_type real_type;

        real_type charge0;
        real_type mass0;
        real_type gamma0;

        st::status_type status = st::Types_perform_assignment<
            charge0_real_type, real_type >( charge0, in_charge0 );

        status |= st::Types_perform_assignment<
            mass0_real_type, real_type >( mass0, in_mass0 );

        status |= st::Types_perform_assignment<
            gamma0_real_type, real_type >( gamma0, in_gamma0 );

        if( status == st::STATUS_SUCCESS )
        {
            SIXTRL_PARTICLE_DATAPTR_DEC real_type beta0 = real_type{ 0. };
            SIXTRL_PARTICLE_DATAPTR_DEC real_type p0c = real_type{ 0. };

            ::NS(Particles_preset)( p );
            ::NS(Particles_beta0_p0c_from_charge0_mass0_gamma0_impl)(
                charge0, mass0, gamma0, &beta0, &p0c );

            ::NS(Particles_set_charge0)( p, charge0 );
            ::NS(Particles_set_mass0)( p, mass0 );
            ::NS(Particles_set_beta0)( p, beta0 );
            ::NS(Particles_set_gamma0)( p, gamma0 );
            ::NS(Particles_set_p0c)( p, p0c );
        }

        return status;
    }

    template< class ParticlesT, typename Arg1T, typename Arg2T, typename Arg3T >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::status_type
    Particles_init(
        SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT* SIXTRL_RESTRICT p,
        Arg1T arg1, Arg2T arg2, Arg3T arg3, particle_init_mode_type mode )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_is_type< ParticlesT >(),
                       "ParticlesT required to be particle class" );

        st::status_type status = st::STATUS_GENERAL_FAILURE;

        switch( mode )
        {
            case st::PARTICLE_INIT_CHARGE0_MASS0_BETA0:
            {
                status = st::Particles_init_charge0_mass0_beta0(
                    p, arg1, arg2, arg3 );
                break;
            }

            case st::PARTICLE_INIT_CHARGE0_MASS0_GAMMA0:
            {
                status = st::Particles_init_charge0_mass0_gamma0(
                    p, arg1, arg2, arg3 );
                break;
            }

            case st::PARTICLE_INIT_CHARGE0_MASS0_PC0:
            {
                status = st::Particles_init_charge0_mass0_p0c(
                    p, arg1, arg2, arg3 );
                break;
            }

            default: { status = st::STATUS_GENERAL_FAILURE; }
        };

        return status;
    }

    template< class ParticlesT, typename XArg, typename PxArg, typename YArg,
        typename PyArg, typename ZetaArg, typename DeltaArg, typename StateArg,
        typename AtElemArg, typename AtTurnArg, typename ParticleIdArg,
        typename PSigmaArg, typename RppArg, typename RvvArg, typename ChiArg,
        typename ChargeRatioArg, typename Charge0Arg, typename Mass0Arg,
        typename Beta0Arg, typename Gamma0Arg, typename P0cArg, typename SArg >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< XArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< PxArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< YArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< PyArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< ZetaArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< DeltaArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< StateArg,
            typename ParticlesTypeTraits< ParticlesT >::index_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< ParticleIdArg,
            typename ParticlesTypeTraits< ParticlesT >::index_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< AtElemArg,
            typename ParticlesTypeTraits< ParticlesT >::index_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< AtTurnArg,
            typename ParticlesTypeTraits< ParticlesT >::index_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< PSigmaArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< RppArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< RvvArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< ChiArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< ChargeRatioArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Beta0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Gamma0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< P0cArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< SArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >(),
        SIXTRL_CXX_NAMESPACE::status_type >::type
    Particles_init(
        SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT* SIXTRL_RESTRICT p,
        XArg x, PxArg px, YArg y, PyArg py, ZetaArg zeta, DeltaArg delta,
        StateArg state, AtElemArg at_element, AtTurnArg at_turn,
        ParticleIdArg id, PSigmaArg psigma, RppArg rpp, RvvArg rvv,
        ChiArg chi, ChargeRatioArg charge_ratio, Charge0Arg charge0,
        Mass0Arg mass0, Beta0Arg beta0, Gamma0Arg gamma0, P0cArg p0c, SArg s )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_is_type< ParticlesT >(),
                       "Particles_init() called for illegal ParticlesT class" );

        st::status_type status = st::STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            ::NS(Particles_set_x)( p, x );
            ::NS(Particles_set_px)( p, px );
            ::NS(Particles_set_y)( p, y );
            ::NS(Particles_set_py)( p, py );
            ::NS(Particles_set_zeta)( p, zeta );
            ::NS(Particles_set_delta)( p, delta );
            ::NS(Particles_set_state)( p, state );
            ::NS(Particles_set_at_element)( p, at_element );
            ::NS(Particles_set_at_turn)( p, at_turn );
            ::NS(Particles_set_id)( p, id );
            ::NS(Particles_set_psigma)( p, psigma );
            ::NS(Particles_set_rpp)( p, rpp );
            ::NS(Particles_set_rvv)( p, rvv );
            ::NS(Particles_set_chi)( p, chi );
            ::NS(Particles_set_charge_ratio)( p, charge_ratio );
            ::NS(Particles_set_charge0)( p, charge0 );
            ::NS(Particles_set_mass0)( p, mass0 );
            ::NS(Particles_set_beta0)( p, beta0 );
            ::NS(Particles_set_gamma0)( p, gamma0 );
            ::NS(Particles_set_p0c)( p, p0c );
            ::NS(Particles_set_s)( p, s );

            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    template< class ParticlesT, typename XArg, typename PxArg, typename YArg,
        typename PyArg, typename ZetaArg, typename DeltaArg, typename StateArg,
        typename AtElemArg, typename AtTurnArg, typename ParticleIdArg,
        typename PSigmaArg, typename RppArg, typename RvvArg, typename ChiArg,
        typename ChargeRatioArg, typename Charge0Arg, typename Mass0Arg,
        typename Beta0Arg, typename Gamma0Arg, typename P0cArg, typename SArg >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< XArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< PxArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< YArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< PyArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< ZetaArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< DeltaArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< StateArg,
            typename ParticlesTypeTraits< ParticlesT >::index_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< ParticleIdArg,
            typename ParticlesTypeTraits< ParticlesT >::index_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< AtElemArg,
            typename ParticlesTypeTraits< ParticlesT >::index_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< AtTurnArg,
            typename ParticlesTypeTraits< ParticlesT >::index_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< PSigmaArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< RppArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< RvvArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< ChiArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< ChargeRatioArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Charge0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Mass0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Beta0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< Gamma0Arg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< P0cArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< SArg,
            typename ParticlesTypeTraits< ParticlesT >::real_type >(),
        SIXTRL_CXX_NAMESPACE::status_type >::type
    Particles_init(
        SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT* SIXTRL_RESTRICT p,
        XArg x, PxArg px, YArg y, PyArg py, ZetaArg zeta, DeltaArg delta,
        StateArg state, AtElemArg at_element, AtTurnArg at_turn,
        ParticleIdArg id, PSigmaArg psigma, RppArg rpp, RvvArg rvv,
        ChiArg chi, ChargeRatioArg charge_ratio, Charge0Arg charge0,
        Mass0Arg mass0, Beta0Arg beta0, Gamma0Arg gamma0, P0cArg p0c, SArg s )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particles_is_type< ParticlesT >(),
                       "Particles_init() called for illegal ParticlesT class" );

        st::status_type status = st::STATUS_GENERAL_FAILURE;

        if( p != SIXTRL_NULLPTR )
        {
            typedef typename ParticlesTypeTraits<
                ParticlesT >::real_type real_type;

            typedef typename ParticlesTypeTraits<
                ParticlesT >::index_type index_type;

            real_type temp_real;

            status =  st::Types_perform_assignment< typename std::decay<
                XArg >::type, real_type >( temp_real, x );

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_x)( p, temp_real );

                status = st::Types_perform_assignment< typename std::decay<
                    PxArg >::type, real_type >( temp_real, px ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_px)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    YArg >::type, real_type >( temp_real, y ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_y)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    PyArg >::type, real_type >( temp_real, py ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_py)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    ZetaArg >::type, real_type >( temp_real, zeta ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_zeta)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    DeltaArg >::type, real_type >( temp_real, delta ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_delta)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    PSigmaArg >::type, real_type >( temp_real, psigma ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_psigma)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    RppArg >::type, real_type >( temp_real, rpp ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_rpp)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    RvvArg >::type, real_type >( temp_real, rvv ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_rvv)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    ChiArg >::type, real_type >( temp_real, chi ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_chi)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    ChargeRatioArg >::type, real_type >( temp_real, charge_ratio ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_charge_ratio)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    Charge0Arg >::type, real_type >( temp_real, charge0 ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_charge0)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    Mass0Arg >::type, real_type >( temp_real, mass0 ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_mass0)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    Beta0Arg >::type, real_type >( temp_real, beta0 ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_beta0)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    Gamma0Arg >::type, real_type >( temp_real, gamma0 ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_gamma0)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    P0cArg >::type, real_type >( temp_real, p0c ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_p0c)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    SArg >::type, real_type >( temp_real, s ); }

            index_type temp_index;

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_s)( p, temp_real );
                status = st::Types_perform_assignment< typename std::decay<
                    StateArg >::type, index_type >( temp_index, state ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_state)( p, temp_index );
                status = st::Types_perform_assignment< typename std::decay<
                    ParticleIdArg >::type, index_type >( temp_index, id ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_id)( p, temp_index );
                status = st::Types_perform_assignment< typename std::decay<
                    AtElemArg >::type, index_type >( temp_index, at_element ); }

            if( status == st::STATUS_SUCCESS ) {
                ::NS(Particles_set_at_element)( p, temp_index );
                status = st::Types_perform_assignment< typename std::decay<
                    AtTurnArg >::type, index_type >( temp_index, at_turn ); }

            if( status == st::STATUS_SUCCESS )
                ::NS(Particles_set_at_turn)( p, temp_index );
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class ParticlesT, store_backend_type StoreT >
    struct ObjDataInitialiser< ParticlesT, StoreT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particles_is_type< ParticlesT >(), void >::type >
    {
        static SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT*
        preset( SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT* SIXTRL_RESTRICT obj ) {
            return ::NS(Particles_preset)( obj ); }

        template< typename... Args >
        static SIXTRL_FN SIXTRL_CXX_NAMESPACE::status_type
        init( SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT* SIXTRL_RESTRICT obj,
              Args&&... init_args ) {
            return SIXTRL_CXX_NAMESPACE::Particles_init( obj,
                std::forward< Args >( init_args )... ); }
    };
}
#endif /* C++ */

/* ----------------------------------------------------------------------++++ */
/* cobjects */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<>
    struct ObjTypeIdDataTypeMap< cobj_obj_id_type,
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_SINGLE_PARTICLE >
    {
        typedef ::NS(SingleParticle) value_type;
    };

    template<>
    struct ObjDataTypeIdTraits< ::NS(SingleParticle), cobj_obj_id_type >
    {
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type<
        ::NS(SingleParticle) >(), "NS(SingleParticle) should be a C-API type" );

        static SIXTRL_FN constexpr cobj_obj_id_type TypeId() SIXTRL_NOEXCEPT {
            return SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_SINGLE_PARTICLE; }
    };
} /* end: SIXTRL_CXX_NAMESPACE */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

template< class ParticlesT >
static SIXTRL_FN constexpr ::NS(cobj_obj_id_type) NS(Particles_type_id)(
    SIXTRL_PARTICLES_ARGPTR_DEC const ParticlesT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( p ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT {
    static_assert( SIXTRL_CXX_NAMESPACE::Particles_is_type< ParticlesT >(),
        "Requires ParticlesT to be a Particle element" );
    return SIXTRL_CXX_NAMESPACE::ObjDataTypeIdTraits< ParticlesT,
        SIXTRL_CXX_NAMESPACE::cobj_obj_id_type >::TypeId(); }

template< class ParticlesT >
static SIXTRL_FN constexpr typename std::enable_if<
    SIXTRL_CXX_NAMESPACE::Particles_is_type< ParticlesT >(),
    ::NS(cobj_size_type) >::type
NS(Particles_cobjects_num_pointers)(
    SIXTRL_PARTICLES_ARGPTR_DEC const ParticlesT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( p ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT {
    return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< ParticlesT >(); }

template< class ParticlesT >
static SIXTRL_INLINE SIXTRL_FN ::NS(cobj_size_type)
NS(Particles_cobjects_required_num_bytes)(
    ::NS(cobj_size_type) const slot_size,
    SIXTRL_PARTICLES_ARGPTR_DEC const ParticlesT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT {
    namespace st = SIXTRL_CXX_NAMESPACE;
    static_assert( st::Particles_is_type< ParticlesT >(),
                    "Requires ParticlesT to be a Particle element" );
    return st::CObjElem_required_num_bytes< ParticlesT >( slot_size, p ); }

template< class ParticlesT >
static SIXTRL_INLINE SIXTRL_FN ::NS(cobj_size_type)
NS(Particles_cobjects_required_num_slots)(
    ::NS(cobj_size_type) const slot_size,
    SIXTRL_PARTICLES_ARGPTR_DEC const ParticlesT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT {
    namespace st = SIXTRL_CXX_NAMESPACE;
    static_assert( st::Particles_is_type< ParticlesT >(),
                    "Requires ParticlesT to be a Particle element" );
    return st::CObjElem_required_num_slots< ParticlesT >( slot_size, p ); }

template< class ParticlesT >
static SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT const*
NS(Particles_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    ::NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    namespace st = SIXTRL_CXX_NAMESPACE;
    static_assert( st::Particles_is_type< ParticlesT >(),
                    "Requires ParticlesT to be a Particle element" );
    return st::CObjElem_const_from_cobj_index< ParticlesT >(
        index_obj, slot_size ); }

template< class ParticlesT >
static SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT*
NS(Particles_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)* SIXTRL_RESTRICT obj,
    ::NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    namespace st = SIXTRL_CXX_NAMESPACE;
    static_assert( st::Particles_is_type< ParticlesT >(),
                    "Requires ParticlesT to be a Particle element" );
    return st::CObjElem_from_cobj_index< ParticlesT >( obj, slot_size ); }

template< class ParticlesT >
static SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT const*
NS(Particles_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_type) const pos_in_buffer,
    ::NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    namespace st = SIXTRL_CXX_NAMESPACE;
    static_assert( st::Particles_is_type< ParticlesT >(),
                    "Requires ParticlesT to be a Particle element" );
    return ::NS(Particles_const_from_cobj_index)(
        ::NS(CObjFlatBuffer_const_index)( buffer, pos_in_buffer, slot_size ) ); }

template< class ParticlesT >
static SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT*
NS(Particles_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_type) const pos_in_buffer,
    ::NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    namespace st = SIXTRL_CXX_NAMESPACE;
    static_assert( st::Particles_is_type< ParticlesT >(),
                    "Requires ParticlesT to be a Particle element" );
    return ::NS(Particles_from_cobj_index)( ::NS(CObjFlatBuffer_index)(
        buffer, pos_in_buffer, slot_size ) ); }

template< class ParticlesT >
static SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT const*
NS(Particles_const_from_cbuffer)( SIXTRL_BUFFER_ARGPTR_DEC const
        ::NS(CBufferView) *const SIXTRL_RESTRICT cbuffer,
    ::NS(cobj_size_type) const index ) SIXTRL_NOEXCEPT {
    namespace st = SIXTRL_CXX_NAMESPACE;
    static_assert( st::Particles_is_type< ParticlesT >(),
                    "Requires ParticlesT to be a Particle element" );
    return ( cbuffer != SIXTRL_NULLPTR )
        ? ::NS(Particles_const_from_cobj_index)( cbuffer->index_at( index ) )
        : SIXTRL_NULLPTR; }

template< class ParticlesT >
static SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC ParticlesT*
NS(Particles_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    ::NS(cobj_size_type) const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    static_assert( st::Particles_is_type< ParticlesT >(),
                    "Requires ParticlesT to be a Particle element" );
    return ( cbuffer != SIXTRL_NULLPTR )
        ? ::NS(Particles_from_cobj_index)( cbuffer->index_at( pos_in_buffer ) )
        : SIXTRL_NULLPTR;
}

#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLES_CXX_HPP__ */
