#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_CONVERT_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_CONVERT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/definitions.h"
    #include "sixtracklib/common/internal/obj_convert.hpp"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs.hpp"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_api.h"
    #include "sixtracklib/common/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool TypeNoPtrs_allow_type_conversion(
        SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR
    ) SIXTRL_NOEXCEPT
    {
        return (
            ( SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< DstT >() ) &&
            ( SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< SrcT >() ) &&
            ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                typename TypeNoPtrsTraits< SrcT >::real_t,
                typename TypeNoPtrsTraits< DstT >::real_t >() ) &&
            ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                typename TypeNoPtrsTraits< SrcT >::int_t,
                typename TypeNoPtrsTraits< DstT >::int_t >() ) &&
            ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                typename TypeNoPtrsTraits< SrcT >::uchar_t,
                typename TypeNoPtrsTraits< DstT >::uchar_t >() ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    TypeNoPtrs_type_conv_can_requ_prepare(
        SIXTRL_BUFFER_DATAPTR_DEC const DstT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return false;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool
    TypeNoPtrs_requ_prepare_conversion(
        SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR,
        SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::tests::TypeNoPtrs_allow_type_conversion<
            SrcT, DstT >(), "Illegal type conversion" );

        SIXTRL_ASSERT( src_store_be != st::STORAGE_BE_ILLEGAL );
        SIXTRL_ASSERT( dst_store_be != st::STORAGE_BE_ILLEGAL );

        ( void )src_store_be;
        ( void )dst_store_be;

        return false;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    TypeNoPtrs_prepare_conversion(
        SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dest,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::tests::TypeNoPtrs_allow_type_conversion<
            SrcT, DstT >(), "Illegal type conversion" );

        return ( ( src != SIXTRL_NULLPTR ) && ( dest != SIXTRL_NULLPTR ) &&
                 ( src_store_be != st::STORAGE_BE_ILLEGAL ) &&
                 ( dst_store_be != st::STORAGE_BE_ILLEGAL ) )
            ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool TypeNoPtrs_allow_conversion(
        SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return (
            ( st::tests::TypeNoPtrs_allow_type_conversion< SrcT, DstT >() ) &&
            ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) &&
            ( src_store_be != st::STORAGE_BE_ILLEGAL ) &&
            ( dst_store_be != st::STORAGE_BE_ILLEGAL ) &&
            ( st::tests::TypeNoPtrs_c_length( dst ) ==
              st::tests::TypeNoPtrs_c_length( dst ) ) &&
            ( st::tests::TypeNoPtrs_const_c_begin( dst ) != SIXTRL_NULLPTR ) &&
            ( st::tests::TypeNoPtrs_const_c_begin( src ) != SIXTRL_NULLPTR ) );
    }

    template< class SrcT, class DstT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    TypeNoPtrs_convert(
        SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        Args&&... SIXTRL_UNUSED( conv_parameters ) )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( st::tests::TypeNoPtrs_allow_conversion(
            dst, src, src_store_be, dst_store_be ) )
        {
            status = st::tests::TypeNoPtrs_set_a(
                dst, st::tests::TypeNoPtrs_a( src ) );

            status |= st::tests::TypeNoPtrs_set_b(
                dst, st::tests::TypeNoPtrs_b( src ) );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::tests::TypeNoPtrs_const_c_begin(
                    src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::tests::TypeNoPtrs_const_c_begin(
                                dst ) != SIXTRL_NULLPTR )
                    ? st::tests::TypeNoPtrs_set_c( dst,
                        st::tests::TypeNoPtrs_const_c_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        return status;
    }

    } /* namespace: tests */

    /* ********************************************************************* */
    /* ::NS(TypeNoPtrs) */

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        ::NS(TypeNoPtrs), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(TypeNoPtrs) SrcT;

        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return
            ( SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_allow_type_conversion<
                SrcT, DstT >() ) &&
            ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
            ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< ::NS(TypeNoPtrs), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(TypeNoPtrs) SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_type_conversion_requ_no_prepare< SrcT,
                DstT, SrcStoreT, DstStoreT >(), "Should not require prepare" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeNoPtrs_requ_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t prepare(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeNoPtrs_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeNoPtrs_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }
    };

    /* ********************************************************************* */
    /* TTypeNoPtrs< R, I, U, RAlign, IAlign, UAlign > */

    template< class R, class I, class U,
              SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t IAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t UAlign, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        SIXTRL_CXX_NAMESPACE::tests::TTypeNoPtrs< R, I, U, RAlign, IAlign,
            UAlign >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::TTypeNoPtrs<
            R, I, U, RAlign, IAlign, UAlign > SrcT;

        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return
            ( SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_allow_type_conversion<
                SrcT, DstT >() ) &&
            ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
            ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class R, class I, class U,
              SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t IAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t UAlign, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< SIXTRL_CXX_NAMESPACE::tests::TTypeNoPtrs<
        R, I, U, RAlign, IAlign, UAlign >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::TTypeNoPtrs<
            R, I, U, RAlign, IAlign, UAlign > SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_type_conversion_requ_no_prepare< SrcT,
                DstT, SrcStoreT, DstStoreT >(), "Should not require prepare" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeNoPtrs_requ_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t prepare(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeNoPtrs_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeNoPtrs_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }
    };
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(TypeNoPtrs_allow_type_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC DstT*
        SIXTRL_RESTRICT SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_allow_type_conversion<
        SrcT, DstT >();
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool
NS(TypeNoPtrs_type_conv_can_requ_prepare)(
    SIXTRL_BUFFER_DATAPTR_DEC const DstT *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_type_conv_can_requ_prepare<
        SrcT, DstT >();
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool
NS(TypeNoPtrs_requ_prepare_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC const DstT *const
        SIXTRL_RESTRICT dest = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const
        SIXTRL_RESTRICT src = SIXTRL_NULLPTR,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_requ_prepare_conversion(
        dest, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_prepare_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_prepare_conversion<
        SrcT, DstT >( dest, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(TypeNoPtrs_allow_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_allow_conversion<
        SrcT, DstT >( dst, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT, typename... Args >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_convert)(
    SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    Args&&... conv_parameters )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_convert(
        dst, src, src_store_be, dst_store_be, std::forward< Args >(
            conv_parameters )... );
}

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN bool NS(TypeNoPtrs_allow_type_conversion)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(TypeNoPtrs_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(TypeNoPtrs_requ_prepare_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_prepare_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(TypeNoPtrs_allow_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_convert)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE bool NS(TypeNoPtrs_allow_type_conversion)( void ) SIXTRL_NOEXCEPT
{
    return true;
}

SIXTRL_INLINE bool NS(TypeNoPtrs_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT
{
    return true;
}

SIXTRL_INLINE bool NS(TypeNoPtrs_requ_prepare_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( NS(TypeNoPtrs_allow_type_conversion)() );

    SIXTRL_ASSERT( src_store_be != ( NS(store_backend_t)
        )SIXTRL_STORAGE_BE_ILLEGAL );

    SIXTRL_ASSERT( dst_store_be != ( NS(store_backend_t)
        )SIXTRL_STORAGE_BE_ILLEGAL );

    ( void )dest;
    ( void )src;
    ( void )src_store_be;
    ( void )dst_store_be;

    return false;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_prepare_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    ( void )dest;
    ( void )src;

    return ( ( src_store_be != (
                NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) &&
             ( dst_store_be != (
                NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) )
        ? ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS
        : ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
}

SIXTRL_INLINE bool NS(TypeNoPtrs_allow_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    return ( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
             ( NS(TypeNoPtrs_c_length)( dst ) ==
               NS(TypeNoPtrs_c_length)( src ) ) &&
             ( NS(TypeNoPtrs_const_c_begin)( dst ) != SIXTRL_NULLPTR ) &&
             ( NS(TypeNoPtrs_const_c_begin)( src ) != SIXTRL_NULLPTR ) &&
             ( src_store_be != ( NS(store_backend_t)
                 )SIXTRL_STORAGE_BE_ILLEGAL ) &&
             ( dst_store_be != ( NS(store_backend_t)
                 )SIXTRL_STORAGE_BE_ILLEGAL ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_convert)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( NS(TypeNoPtrs_allow_conversion)(
            dst, src, src_store_be, dst_store_be ) )
    {
        status  = NS(TypeNoPtrs_set_a)( dst, NS(TypeNoPtrs_a)( src ) );
        status |= NS(TypeNoPtrs_set_b)( dst, NS(TypeNoPtrs_b)( src ) );
        status |= NS(TypeNoPtrs_set_c)( dst,
            NS(TypeNoPtrs_const_c_begin)( src ) );
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_CONVERT_H__ */
