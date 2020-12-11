#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_CONVERT_COBJECTS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_CONVERT_COBJECTS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift.hpp"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_api.h"
    #include "sixtracklib/common/internal/obj_convert.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool XYShift_allow_type_conversion(
        SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( dst ) = SIXTRL_NULLPTR,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ( ( SIXTRL_CXX_NAMESPACE::XYShift_is_type< DstT >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::XYShift_is_type< SrcT >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                      typename XYShiftTraits< SrcT >::real_t,
                      typename XYShiftTraits< DstT >::real_t >() ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool XYShift_type_conv_can_requ_prepare(
        SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( dst ) = SIXTRL_NULLPTR,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return false;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool XYShift_requ_prepare_conversion(
        SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::XYShift_allow_type_conversion< SrcT, DstT >(),
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
    XYShift_prepare_conversion(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        store_backend_t src_store_be = STORAGE_BE_DEFAULT,
        store_backend_t dst_store_be = STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::XYShift_allow_type_conversion< SrcT, DstT >(),
            "conversion from SrcT to DstT is not allowed" );

        return ( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
                 ( src_store_be != STORAGE_BE_ILLEGAL ) &&
                 ( dst_store_be != STORAGE_BE_ILLEGAL ) )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool XYShift_allow_conversion(
        SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        return ( SIXTRL_CXX_NAMESPACE::XYShift_allow_type_conversion<
                    SrcT, DstT >() ) &&
               ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) &&
               ( src_store_be != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
               ( dst_store_be != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
    }

    template< class SrcT, class DstT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    XYShift_convert(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        Args&&... SIXTRL_UNUSED( conv_parameters ) )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::XYShift_allow_type_conversion< SrcT, DstT >(),
            "conversion from SrcT to DstT is not allowed" );

        SIXTRL_ASSERT( src != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( dst != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( src_store_be != st::STORAGE_BE_ILLEGAL );
        SIXTRL_ASSERT( dst_store_be != st::STORAGE_BE_ILLEGAL );

        SIXTRL_ASSERT( st::XYShift_allow_conversion(
            dst, src, src_store_be, dst_store_be ) );

        ( void )src_store_be;
        ( void )dst_store_be;

        return st::XYShift_set_dx( dst, st::XYShift_dx( src ) ) |
               st::XYShift_set_dy( dst, st::XYShift_dy( src ) );
    }

    /* ********************************************************************* */
    /* NS(XYShift): */

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        ::NS(XYShift), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(XYShift) SrcT;

        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::XYShift_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< ::NS(XYShift), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(XYShift) SrcT;

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
            return SIXTRL_CXX_NAMESPACE::XYShift_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t prepare(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_convert(
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
            return SIXTRL_CXX_NAMESPACE::XYShift_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }
    };

    /* ********************************************************************* */
    /* TXYShift< R, I, RAlign, IAlign >: */

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits< SIXTRL_CXX_NAMESPACE::TXYShift<
        R, RAlign >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TXYShift< R, RAlign > SrcT;
        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::XYShift_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter<
        SIXTRL_CXX_NAMESPACE::TXYShift< R, RAlign >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TXYShift< R, RAlign > SrcT;
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
            return SIXTRL_CXX_NAMESPACE::XYShift_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t prepare(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_convert(
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
            return SIXTRL_CXX_NAMESPACE::XYShift_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }
    };
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(XYShift_allow_type_conversion)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT
        SIXTRL_UNUSED( dst ) = SIXTRL_NULLPTR,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_allow_type_conversion< SrcT, DstT >();
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(XYShift_type_conv_can_requ_prepare)(
    SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( dst ) = SIXTRL_NULLPTR,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_type_conv_can_requ_prepare<
        SrcT, DstT >();
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(XYShift_requ_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_requ_prepare_conversion(
        dst, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_prepare_conversion< SrcT, DstT >(
                dst, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(XYShift_allow_conversion)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_allow_conversion< SrcT, DstT >(
        dst, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT, typename... Args >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_convert)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    Args&&... conv_parameters )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_convert( dst, src, src_store_be,
        dst_store_be, std::forward< Args >( conv_parameters )... );
}

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN bool NS(XYShift_allow_type_conversion)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(XYShift_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(XYShift_requ_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(XYShift_allow_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_convert)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE bool NS(XYShift_allow_type_conversion)( void ) SIXTRL_NOEXCEPT
{
    return true;
}

SIXTRL_INLINE bool NS(XYShift_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT
{
    return false;
}

SIXTRL_INLINE bool NS(XYShift_requ_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( NS(XYShift_allow_type_conversion)() );
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

    return false;
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    return ( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
        ( src_store_be != ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) &&
        ( dst_store_be != ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) )
        ? ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS
        : ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
}

SIXTRL_INLINE bool NS(XYShift_allow_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    return ( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
        ( src_store_be != ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) &&
        ( dst_store_be != ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_convert)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( src_store_be != (
        NS(store_backend_t ) )SIXTRL_STORAGE_BE_ILLEGAL );

    SIXTRL_ASSERT( dst_store_be != (
        NS(store_backend_t ) )SIXTRL_STORAGE_BE_ILLEGAL );

    SIXTRL_ASSERT( NS(XYShift_allow_conversion)(
        dst, src, src_store_be, dst_store_be ) );

    ( void )src_store_be;
    ( void )dst_store_be;

    return NS(XYShift_set_dx)( dst, NS(XYShift_dx)( src ) ) |
           NS(XYShift_set_dy)( dst, NS(XYShift_dy)( src ) );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_CONVERT_COBJECTS_H__ */
