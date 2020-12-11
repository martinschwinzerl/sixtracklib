#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_CONVERT_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_CONVERT_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_unit.h"
    #include "sixtracklib/common/particles/particle_unit.hpp"
    #include "sixtracklib/common/particles/particle_unit_api.h"
    #include "sixtracklib/common/internal/obj_convert.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool Particle_allow_type_conversion(
        SIXTRL_PARTICLE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( dst ) = SIXTRL_NULLPTR,
        SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ( ( SIXTRL_CXX_NAMESPACE::Particle_is_type< SrcT >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::Particle_is_type< DstT >() ) &&
                 ( ParticleTraits< DstT >::num_particles >=
                   ParticleTraits< SrcT >::num_particles ) &&
                 ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                     typename ParticleTraits< SrcT >::real_t,
                     typename ParticleTraits< DstT >::real_t >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                     typename ParticleTraits< SrcT >::index_t,
                     typename ParticleTraits< DstT >::index_t >() ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    Particle_type_conv_can_requ_prepare(
        SIXTRL_PARTICLE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
        SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return false;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool Particle_requ_prepare_conversion(
        SIXTRL_PARTICLE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_allow_type_conversion< SrcT, DstT >(),
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
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool Particle_allow_conversion(
        SIXTRL_PARTICLE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        store_backend_t const src_store_be = STORAGE_BE_DEFAULT,
        store_backend_t const dst_store_be = STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( ( st::Particle_allow_type_conversion< SrcT, DstT >() ) &&
                 ( src_store_be != st::STORAGE_BE_ILLEGAL ) &&
                 ( dst_store_be != st::STORAGE_BE_ILLEGAL ) &&
                 ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    Particle_prepare_conversion(
        SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dest,
        SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Particle_allow_type_conversion< SrcT, DstT >(),
            "conversion from SrcT to DstT is not allowed" );

        return ( ( src != SIXTRL_NULLPTR ) && ( dest != SIXTRL_NULLPTR ) &&
                 ( src_store_be != st::STORAGE_BE_ILLEGAL ) &&
                 ( dst_store_be != st::STORAGE_BE_ILLEGAL ) )
            ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SrcT, class DstT, typename... Args >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_allow_type_conversion< SrcT, DstT >(),
        arch_status_t >::type
    Particle_convert(
        SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT SIXTRL_UNUSED( dst ),
        SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( src ),
        SIXTRL_CXX_NAMESPACE::store_backend_t const SIXTRL_UNUSED(
            src_store_be ) = STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const SIXTRL_UNUSED(
            dst_store_be ) = STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SrcT, class DstT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_allow_type_conversion< SrcT, DstT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< SrcT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_impl_default< DstT >(),
        arch_status_t >::type
    Particle_convert(
        SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        Args&&... SIXTRL_UNUSED( conv_parameters ) )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        static_assert( st::Particle_allow_type_conversion< SrcT, DstT >(),
                       "illegal conversion" );

        SIXTRL_ASSERT( st::Particle_allow_conversion(
            dst, src, src_store_be, dst_store_be ) );

        status  = st::Particle_set_x( dst, st::Particle_x( src ) );
        status |= st::Particle_set_px( dst, st::Particle_px( src ) );
        status |= st::Particle_set_y( dst, st::Particle_y( src ) );
        status |= st::Particle_set_py( dst, st::Particle_py( src ) );
        status |= st::Particle_set_zeta( dst, st::Particle_zeta( src ) );
        status |= st::Particle_set_delta( dst, st::Particle_delta( src ) );
        status |= st::Particle_set_psigma(
                    dst, st::Particle_psigma( src ) );

        status |= st::Particle_set_state(
                    dst, st::Particle_state( src ) );
        status |= st::Particle_set_at_element(
                    dst, st::Particle_at_element( src ) );
        status |= st::Particle_set_at_turn(
                    dst, st::Particle_at_turn( src ) );
        status |= st::Particle_set_id( dst, st::Particle_id( src ) );

        status |= st::Particle_set_s( dst, st::Particle_s( src ) );
        status |= st::Particle_set_rvv( dst, st::Particle_rvv( src ) );
        status |= st::Particle_set_rpp( dst, st::Particle_rpp( src ) );
        status |= st::Particle_set_chi( dst, st::Particle_chi( src ) );
        status |= st::Particle_set_charge_ratio(
                    dst, st::Particle_charge_ratio( src ) );

        status |= st::Particle_set_charge0(
                    dst, st::Particle_charge0( src ) );

        status |= st::Particle_set_mass0( dst, st::Particle_mass0( src ) );
        status |= st::Particle_set_beta0( dst, st::Particle_beta0( src ) );

        status |= st::Particle_set_gamma0(
                    dst, st::Particle_gamma0( src ) );

        status |= st::Particle_set_pc0( dst, st::Particle_pc0( src ) );

        return status;
    }

    /* ********************************************************************* */
    /* NS(Particle): */

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        ::NS(Particle), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(Particle) SrcT;

        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::Particle_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< ::NS(Particle), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(Particle) SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_type_conversion_requ_no_prepare< SrcT,
                DstT, SrcStoreT, DstStoreT >(), "Should not require prepare" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_PARTICLE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t prepare(
            SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_PARTICLE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }
    };

    /* ********************************************************************* */
    /* TParticle< R, I, RAlign, IAlign >: */

    template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t IAlign, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits< SIXTRL_CXX_NAMESPACE::TParticle<
        R, I, RAlign, IAlign >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TParticle< R, I, RAlign, IAlign > SrcT;
        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::Particle_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t IAlign, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< SIXTRL_CXX_NAMESPACE::TParticle<
        R, I, RAlign, IAlign >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TParticle< R, I, RAlign, IAlign > SrcT;
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_type_conversion_requ_no_prepare< SrcT,
                DstT, SrcStoreT, DstStoreT >(), "Should not require prepare" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_PARTICLE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t prepare(
            SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_PARTICLE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }
    };
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(Particle_allow_type_conversion)(
    SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dest = SIXTRL_NULLPTR,
    SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
        src = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Particle_allow_type_conversion<
        SrcT, DstT >( dest, src );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(Particle_type_conv_can_requ_prepare)(
    SIXTRL_PARTICLE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
    SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Particle_type_conv_can_requ_prepare<
        SrcT, DstT >();
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(Particle_requ_prepare_conversion)(
    SIXTRL_PARTICLE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Particle_requ_prepare_conversion(
        dst, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_prepare_conversion)(
    SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_backend =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_backend =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Particle_prepare_conversion< SrcT, DstT >(
                dest, src, src_store_backend, dst_store_backend );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(Particle_allow_conversion)(
    SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_backend =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_backend =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Particle_allow_conversion< SrcT, DstT >(
        dst, src, src_store_backend, dst_store_backend );
}

template< class SrcT, class DstT, typename... Args >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_convert)(
    SIXTRL_PARTICLE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_backend =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_backend =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    Args&&... conv_parameters )
{
    return SIXTRL_CXX_NAMESPACE::Particle_convert< SrcT, DstT >(
        dst, src, src_store_backend, dst_store_backend,
            std::forward< Args >( conv_parameters )... );
}

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_allow_type_conversion)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_requ_prepare_conversion)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_backend,
    NS(store_backend_t) const dst_store_backend ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_prepare_conversion)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_backend,
    NS(store_backend_t) const dst_store_backend ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_allow_conversion)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_backend,
    NS(store_backend_t) const dst_store_backend ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_convert)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_backend,
    NS(store_backend_t) const dst_store_backend ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE bool NS(Particle_allow_type_conversion)( void ) SIXTRL_NOEXCEPT
{
    return true;
}

SIXTRL_INLINE bool NS(Particle_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT
{
    return false;
}

SIXTRL_INLINE bool NS(Particle_requ_prepare_conversion)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( NS(Particle_allow_type_conversion)() );
    SIXTRL_ASSERT( src != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( dst != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( src_store_be != ( NS(store_backend_t)
        )SIXTRL_STORAGE_BE_ILLEGAL );

    SIXTRL_ASSERT( dst_store_be != ( NS(store_backend_t)
        )SIXTRL_STORAGE_BE_ILLEGAL );

    ( void )src;
    ( void )dst;
    ( void )src_store_be;
    ( void )dst_store_be;

    return false;
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_prepare_conversion)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
        SIXTRL_RESTRICT SIXTRL_UNUSED( dest ),
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( src ),
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    return ( ( src_store_be != ( NS(store_backend_t)
                    )SIXTRL_STORAGE_BE_ILLEGAL ) &&
             ( dst_store_be != ( NS(store_backend_t)
                    )SIXTRL_STORAGE_BE_ILLEGAL ) )
        ? ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS
        : ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
}

SIXTRL_INLINE bool NS(Particle_allow_conversion)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    return ( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
             ( src_store_be != ( NS(store_backend_t)
                 )SIXTRL_STORAGE_BE_ILLEGAL ) &&
             ( dst_store_be != ( NS(store_backend_t)
                 )SIXTRL_STORAGE_BE_ILLEGAL ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(Particle_convert)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_backend,
    NS(store_backend_t) const dst_store_backend ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;

    SIXTRL_ASSERT( src_store_backend != ( NS(store_backend_t
                    ) )SIXTRL_STORAGE_BE_ILLEGAL );

    SIXTRL_ASSERT( dst_store_backend != ( NS(store_backend_t
                    ) )SIXTRL_STORAGE_BE_ILLEGAL );

    ( void )src_store_backend;
    ( void )dst_store_backend;

    status |= NS(Particle_set_x)(          dst, NS(Particle_x)( src ) );
    status |= NS(Particle_set_px)(         dst, NS(Particle_px)( src ) );
    status |= NS(Particle_set_y)(          dst, NS(Particle_y)( src ) );
    status |= NS(Particle_set_py)(         dst, NS(Particle_py)( src ) );
    status |= NS(Particle_set_zeta)(       dst, NS(Particle_delta)( src ) );
    status |= NS(Particle_set_delta)(      dst, NS(Particle_delta)( src ) );
    status |= NS(Particle_set_psigma)(     dst, NS(Particle_psigma)( src ) );

    status |= NS(Particle_set_state)(      dst, NS(Particle_state)( src ) );
    status |= NS(Particle_set_at_element)( dst, NS(Particle_at_element)( src ) );
    status |= NS(Particle_set_at_turn)(    dst, NS(Particle_at_turn)( src ) );
    status |= NS(Particle_set_id)(         dst, NS(Particle_id)( src ) );

    status |= NS(Particle_set_s)(          dst, NS(Particle_s)( src ) );
    status |= NS(Particle_set_rvv)(        dst, NS(Particle_rvv)( src ) );
    status |= NS(Particle_set_rpp)(        dst, NS(Particle_rpp)( src ) );
    status |= NS(Particle_set_chi)(        dst, NS(Particle_chi)( src ) );
    status |= NS(Particle_set_charge_ratio)( dst,
                NS(Particle_charge_ratio)( src ) );

    status |= NS(Particle_set_charge0)(    dst, NS(Particle_charge0)( src ) );
    status |= NS(Particle_set_mass0)(      dst, NS(Particle_mass0)( src ) );
    status |= NS(Particle_set_beta0)(      dst, NS(Particle_beta0)( src ) );
    status |= NS(Particle_set_gamma0)(     dst, NS(Particle_gamma0)( src ) );
    status |= NS(Particle_set_pc0)(        dst, NS(Particle_pc0)( src ) );

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_CONVERT_CXX_HPP__ */
