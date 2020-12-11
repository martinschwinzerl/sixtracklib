#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_CONVERT_COBJECTS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_CONVERT_COBJECTS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/srotation.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation.hpp"
    #include "sixtracklib/common/beam_elements/srotation/srotation_api.h"
    #include "sixtracklib/common/internal/obj_convert.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool SRotation_allow_type_conversion(
        SIXTRL_BE_ARGPTR_DEC const DstT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR
    ) SIXTRL_NOEXCEPT
    {
        return ( ( SIXTRL_CXX_NAMESPACE::SRotation_is_type< DstT >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::SRotation_is_type< SrcT >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                      typename SRotationTraits< SrcT >::real_t,
                      typename SRotationTraits< DstT >::real_t >() ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool SRotation_type_conv_can_requ_prepare(
        SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return false;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool SRotation_requ_prepare_conversion(
        SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::SRotation_allow_type_conversion< SrcT, DstT >(),
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
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    SRotation_prepare_conversion(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::SRotation_allow_type_conversion< SrcT, DstT >(),
            "conversion from SrcT to DstT is not allowed" );

        return ( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
                 ( src_store_be != st::STORAGE_BE_ILLEGAL ) &&
                 ( dst_store_be != st::STORAGE_BE_ILLEGAL ) )
            ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool SRotation_allow_conversion(
        SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        store_backend_t const src_store_be = STORAGE_BE_DEFAULT,
        store_backend_t const dst_store_be = STORAGE_BE_DEFAULT
    ) SIXTRL_NOEXCEPT
    {
        return ( SIXTRL_CXX_NAMESPACE::SRotation_allow_type_conversion<
                     SrcT, DstT >( dst, src ) ) &&
               ( src_store_be != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
               ( dst_store_be != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
               ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR );
    }

    template< class SrcT, class DstT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t SRotation_convert(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        store_backend_t src_store_be = STORAGE_BE_DEFAULT,
        store_backend_t dst_store_be = STORAGE_BE_DEFAULT,
        Args&&... SIXTRL_UNUSED( conv_parameters ) )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::SRotation_allow_type_conversion< SrcT, DstT >(),
            "conversion from SrcT to DstT is not allowed" );

        SIXTRL_ASSERT( src != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( dst != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( src_store_be != st::STORAGE_BE_ILLEGAL );
        SIXTRL_ASSERT( dst_store_be != st::STORAGE_BE_ILLEGAL );

        ( void )src_store_be;
        ( void )dst_store_be;

        return st::SRotation_set_cos_z( dst, st::SRotation_cos_z( src ) ) |
               st::SRotation_set_sin_z( dst, st::SRotation_sin_z( src ) );
    }

    /* ********************************************************************* */
    /* NS(SRotation): */

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        ::NS(SRotation), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(SRotation) SrcT;

        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::SRotation_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< ::NS(SRotation), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(SRotation) SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_type_conversion_requ_no_prepare< SrcT,
                DstT, SrcStoreT, DstStoreT >(), "Should not require prepare" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t prepare(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }
    };

    /* ********************************************************************* */
    /* TSRotation< R, I, RAlign, IAlign >: */

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits< SIXTRL_CXX_NAMESPACE::TSRotation<
        R, RAlign >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TSRotation< R, RAlign > SrcT;
        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::SRotation_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter<
        SIXTRL_CXX_NAMESPACE::TSRotation< R, RAlign >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TSRotation< R, RAlign > SrcT;
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_type_conversion_requ_no_prepare< SrcT,
                DstT, SrcStoreT, DstStoreT >(), "Should not require prepare" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t prepare(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }
    };
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(SRotation_allow_type_conversion)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT
        SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_allow_type_conversion< SrcT, DstT >();
}


template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(SRotation_type_conv_can_requ_prepare)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT
        SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_allow_type_conversion< SrcT, DstT >();
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(SRotation_requ_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_prepare_conversion(
                dest, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_prepare_conversion(
                dest, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(SRotation_allow_conversion)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_backend =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_backend =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::SRotation_allow_conversion< SrcT, DstT >(
        dst, src, src_store_backend, dst_store_backend );
}

template< class SrcT, class DstT, typename... Args >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_convert)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_backend =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_backend =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    Args&&... conv_parameters )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_convert< SrcT, DstT >(
        dst, src, src_store_backend, dst_store_backend, std::forward< Args >(
            conv_parameters )... );
}

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN bool NS(SRotation_allow_type_conversion)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(SRotation_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(SRotation_requ_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(SRotation_allow_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_backend,
    NS(store_backend_t) const dst_store_backend ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_convert)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT src,
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

SIXTRL_INLINE bool NS(SRotation_allow_type_conversion)( void ) SIXTRL_NOEXCEPT
{
    return true;
}

SIXTRL_INLINE bool NS(SRotation_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT
{
    return false;
}

SIXTRL_INLINE bool NS(SRotation_requ_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( NS(SRotation_allow_type_conversion)() );

    SIXTRL_ASSERT( src != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( dst != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( src_store_be != ( NS(store_backend_t )
                        )SIXTRL_STORAGE_BE_ILLEGAL );

    SIXTRL_ASSERT( dst_store_be != ( NS(store_backend_t )
                        )SIXTRL_STORAGE_BE_ILLEGAL );

    ( void )src;
    ( void )dst;
    ( void )src_store_be;
    ( void )dst_store_be;

    return false;
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    return ( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
             ( src_store_be != ( NS(store_backend_t)
                 )SIXTRL_STORAGE_BE_ILLEGAL ) &&
             ( dst_store_be != ( NS(store_backend_t)
                 )SIXTRL_STORAGE_BE_ILLEGAL ) )
        ? ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS
        : ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
}


SIXTRL_INLINE bool NS(SRotation_allow_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_backend,
    NS(store_backend_t) const dst_store_backend ) SIXTRL_NOEXCEPT
{
    return ( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
             ( src_store_backend != ( NS(store_backend_t)
                 )SIXTRL_STORAGE_BE_ILLEGAL ) &&
             ( dst_store_backend != ( NS(store_backend_t)
                 )SIXTRL_STORAGE_BE_ILLEGAL ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_convert)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_backend,
    NS(store_backend_t) const dst_store_backend ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( src_store_backend != ( NS(store_backend_t
                    ) )SIXTRL_STORAGE_BE_ILLEGAL );

    SIXTRL_ASSERT( dst_store_backend != ( NS(store_backend_t
                    ) )SIXTRL_STORAGE_BE_ILLEGAL );

    ( void )src_store_backend;
    ( void )dst_store_backend;

    return NS(SRotation_set_cos_z)( dst, NS(SRotation_cos_z)( src ) ) |
           NS(SRotation_set_sin_z)( dst, NS(SRotation_sin_z)( src ) );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_CONVERT_COBJECTS_H__ */
