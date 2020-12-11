#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_CONVERT_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_CONVERT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/definitions.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs.hpp"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_api.h"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/obj_convert.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    TypeConstNumPtrs_allow_type_conversion(
        SIXTRL_BUFFER_DATAPTR_DEC const DstT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return (
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< DstT >() ) &&
        ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< SrcT >() ) &&
        ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
            typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                SrcT >::real_t,
            typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                DstT >::real_t >() ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    TypeConstNumPtrs_type_conv_can_requ_prepare(
        SIXTRL_BUFFER_DATAPTR_DEC const DstT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return true;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool
    TypeConstNumPtrs_requ_prepare_conversion(
        SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        static_assert( st::tests::TypeConstNumPtrs_allow_type_conversion<
                        SrcT, DstT >(), "Illegal conversion" );

        SIXTRL_ASSERT( src_store_be != st::STORAGE_BE_ILLEGAL );
        SIXTRL_ASSERT( dst_store_be != st::STORAGE_BE_ILLEGAL );

        SIXTRL_ASSERT( dst != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( src != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( st::tests::TypeConstNumPtrs_const_b_begin(
                            src ) != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( st::tests::TypeConstNumPtrs_const_c_begin(
                            src ) != SIXTRL_NULLPTR );

        ( void )src_store_be;
        ( void )dst_store_be;

        return ( ( ( !std::is_same< SrcT, DstT >::value ) ||
                   ( reinterpret_cast< std::uintptr_t >( dst ) !=
                     reinterpret_cast< std::uintptr_t >( src ) ) ) &&
                 ( ( st::tests::TypeConstNumPtrs_b_length( dst ) !=
                     st::tests::TypeConstNumPtrs_b_length( src ) ) ||
                   ( st::tests::TypeConstNumPtrs_c_length( dst ) !=
                     st::tests::TypeConstNumPtrs_c_length( src ) ) ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    TypeConstNumPtrs_prepare_conversion(
        SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t SIXTRL_UNUSED( src_store_be ) =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t SIXTRL_UNUSED( dst_store_be ) =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert(
            st::tests::TypeConstNumPtrs_allow_type_conversion< SrcT, DstT >(),
            "Convert from SrcT @ SrcStoreT -> DstT @ DstStoreT not allowed" );

        st::arch_status_t status = st::ARCH_STATUS_SUCCESS;

        auto const src_num_b_values =
            st::tests::TypeConstNumPtrs_b_length( src );

        auto const src_num_c_values =
            st::tests::TypeConstNumPtrs_c_length( src );

        if( st::tests::TypeConstNumPtrs_b_length( dst ) != src_num_b_values )
        {
            status = st::tests::TypeConstNumPtrs_set_num_b_values(
                dst, src_num_b_values );
        }

        if( ( ( status == st::ARCH_STATUS_SUCCESS ) ) &&
            ( st::tests::TypeConstNumPtrs_c_length( dst ) !=
              src_num_c_values ) )
        {
            status = st::tests::TypeConstNumPtrs_set_num_c_values(
                dst, src_num_c_values );
        }

        return status;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool
    TypeConstNumPtrs_allow_conversion(
        SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return (
            ( st::tests::TypeConstNumPtrs_allow_type_conversion<
                SrcT, DstT >( dst, src ) ) &&
            ( st::tests::TypeConstNumPtrs_b_length( dst ) ==
              st::tests::TypeConstNumPtrs_b_length( src ) ) &&
            ( st::tests::TypeConstNumPtrs_const_b_begin(
                dst ) != SIXTRL_NULLPTR ) &&
            ( st::tests::TypeConstNumPtrs_const_b_begin(
                src ) != SIXTRL_NULLPTR ) &&
            ( st::tests::TypeConstNumPtrs_c_length( dst ) ==
              st::tests::TypeConstNumPtrs_c_length( src ) ) &&
            ( st::tests::TypeConstNumPtrs_const_c_begin(
                dst ) != SIXTRL_NULLPTR ) &&
            ( st::tests::TypeConstNumPtrs_const_c_begin(
                src ) != SIXTRL_NULLPTR ) &&
            ( src_store_be != st::STORAGE_BE_ILLEGAL ) &&
            ( dst_store_be != st::STORAGE_BE_ILLEGAL ) );
    }

    template< class SrcT, class DstT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    TypeConstNumPtrs_convert(
        SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        Args&&... /*conv_parameters*/ )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( st::tests::TypeConstNumPtrs_allow_conversion(
                dst, src, src_store_be, dst_store_be ) )
        {
            status = st::tests::TypeConstNumPtrs_set_a( dst,
                            st::tests::TypeConstNumPtrs_a( src ) );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::tests::TypeConstNumPtrs_const_b_begin(
                    src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::tests::TypeConstNumPtrs_const_b_begin( dst )
                                != SIXTRL_NULLPTR )
                    ? st::tests::TypeConstNumPtrs_set_b( dst,
                            st::tests::TypeConstNumPtrs_const_b_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::tests::TypeConstNumPtrs_const_c_begin(
                    src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::tests::TypeConstNumPtrs_const_c_begin( dst )
                                != SIXTRL_NULLPTR )
                    ? st::tests::TypeConstNumPtrs_set_c( dst,
                            st::tests::TypeConstNumPtrs_const_c_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        return status;
    }

    } /* namespace: tests */

    /* ********************************************************************* */
    /* NS(TypeConstNumPtrs) : */

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        ::NS(TypeConstNumPtrs), DstT, SrcStoreT, DstStoreT, void >
    {
        typedef ::NS(TypeConstNumPtrs) SrcT;

        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return
            ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_allow_type_conversion<
                SrcT, DstT >() ) &&
            ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
            ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConversionTypesRequireNoPrepareTraits<
        ::NS(TypeConstNumPtrs), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(TypeConstNumPtrs) SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        constexpr static bool requires_no_prepare =
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_type_conv_can_requ_prepare<
                SrcT, DstT, SrcStoreT, DstStoreT >();
    };

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< ::NS(TypeConstNumPtrs), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(TypeConstNumPtrs) SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeConstNumPtrs_requ_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        prepare( SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
                 SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeConstNumPtrs_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeConstNumPtrs_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BUFFER_DATAPTR_DEC  DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC  const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeConstNumPtrs_convert( dst, src, SrcStoreT,
                DstStoreT, std::forward< Args >( conv_parameters )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_BUFFER_DATAPTR_DEC  DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC  const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_params ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::tests::TypeConstNumPtrs_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_params )... );

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( st::tests::TypeConstNumPtrs_requ_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT ) ) )
            {
                status = st::tests::TypeConstNumPtrs_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::tests::TypeConstNumPtrs_convert( dst, src,
                        SrcStoreT, DstStoreT, std::forward< Args >(
                            conv_params )... );
                }
            }

            return status;
        }
    };

    /* ********************************************************************* */
    /* TTypeConstNumPtrs< R, RAlign > : */

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs< R,RAlign >, DstT,
        SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs< R,RAlign > SrcT;

        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return
            ( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_allow_type_conversion<
                SrcT, DstT >() ) &&
            ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
            ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConversionTypesRequireNoPrepareTraits<
        SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs< R,RAlign >, DstT,
        SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs< R,RAlign > SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        constexpr static bool requires_no_prepare =
            !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_type_conv_can_requ_prepare<
                SrcT, DstT, SrcStoreT, DstStoreT >();
    };

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs<
        R,RAlign >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::TTypeConstNumPtrs< R,RAlign > SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeConstNumPtrs_requ_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t prepare(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeConstNumPtrs_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeConstNumPtrs_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BUFFER_DATAPTR_DEC  DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC  const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeConstNumPtrs_convert( dst, src, SrcStoreT,
                DstStoreT, std::forward< Args >( conv_parameters )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_BUFFER_DATAPTR_DEC  DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC  const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_params ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::tests::TypeConstNumPtrs_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_params )... );

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( st::tests::TypeConstNumPtrs_requ_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT ) ) )
            {
                status = st::tests::TypeConstNumPtrs_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::tests::TypeConstNumPtrs_convert( dst, src,
                        SrcStoreT, DstStoreT, std::forward< Args >(
                            conv_params )... );
                }
            }

            return status;
        }
    };

    /* ********************************************************************* */
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(TypeConstNumPtrs_allow_type_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dest = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT
        src = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_allow_type_conversion<
        SrcT, DstT >( dest, src );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool
NS(TypeConstNumPtrs_type_conv_can_requ_prepare)(
    SIXTRL_BUFFER_DATAPTR_DEC const DstT *const
        SIXTRL_RESTRICT dest = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const
        SIXTRL_RESTRICT src = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_type_conv_can_requ_prepare<
        SrcT, DstT >( dest, src );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool
NS(TypeConstNumPtrs_requ_prepare_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_requ_prepare_conversion(
        dest, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_prepare_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_prepare_conversion(
        dest, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(TypeConstNumPtrs_allow_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_allow_conversion(
        dst, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT, typename... Args >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_convert)(
    SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    Args&&... conv_parameters )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_convert( dst, src,
        src_store_be, dst_store_be, std::forward< Args >(
            conv_parameters )... );
}

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN bool NS(TypeConstNumPtrs_allow_type_conversion)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(TypeConstNumPtrs_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(TypeConstNumPtrs_requ_prepare_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(TypeConstNumPtrs_prepare_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(TypeConstNumPtrs_allow_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_convert)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT src,
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

SIXTRL_INLINE bool NS(TypeConstNumPtrs_allow_type_conversion)( void ) SIXTRL_NOEXCEPT
{
    return true;
}

SIXTRL_INLINE bool NS(TypeConstNumPtrs_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT
{
    return true;
}

SIXTRL_INLINE bool NS(TypeConstNumPtrs_requ_prepare_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( NS(TypeConstNumPtrs_allow_type_conversion)() );
    SIXTRL_ASSERT( src_store_be != (
        NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL );
    SIXTRL_ASSERT( dst_store_be != (
        NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL );

    SIXTRL_ASSERT( dst != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( src != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( NS(TypeConstNumPtrs_const_b_begin)(
                        src ) != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( NS(TypeConstNumPtrs_const_c_begin)(
                        src ) != SIXTRL_NULLPTR );

    ( void )src_store_be;
    ( void )dst_store_be;

    return ( ( dst != src ) && (
        ( NS(TypeConstNumPtrs_b_length)( dst ) !=
          NS(TypeConstNumPtrs_b_length)( src ) ) ||
        ( NS(TypeConstNumPtrs_const_b_begin)(
            dst ) == SIXTRL_NULLPTR ) ||
        ( NS(TypeConstNumPtrs_c_length)( dst ) !=
          NS(TypeConstNumPtrs_c_length)( src ) ) ||
        ( NS(TypeConstNumPtrs_const_c_begin)(
            dst ) != SIXTRL_NULLPTR ) ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_prepare_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;

    NS(test_objs_size_t) const src_num_b_values =
        NS(TypeConstNumPtrs_b_length)( src );

    NS(test_objs_size_t) const src_num_c_values =
        NS(TypeConstNumPtrs_c_length)( src );

    ( void )src_store_be;
    ( void )dst_store_be;

    if( NS(TypeConstNumPtrs_b_length)( dst ) != src_num_b_values )
    {
        status = NS(TypeConstNumPtrs_set_num_b_values)( dst, src_num_b_values );
    }

    if( ( ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) ) &&
        ( NS(TypeConstNumPtrs_c_length)( dst ) != src_num_c_values ) )
    {
        status = NS(TypeConstNumPtrs_set_num_c_values)( dst, src_num_c_values );
    }

    return status;
}

SIXTRL_INLINE bool NS(TypeConstNumPtrs_allow_conversion)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    return ( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
             ( NS(TypeConstNumPtrs_b_length)( dst ) ==
               NS(TypeConstNumPtrs_b_length)( src ) ) &&
             ( NS(TypeConstNumPtrs_c_length)( dst ) ==
               NS(TypeConstNumPtrs_c_length)( src ) ) &&
             ( NS(TypeConstNumPtrs_const_b_begin)( dst ) != SIXTRL_NULLPTR ) &&
             ( NS(TypeConstNumPtrs_const_b_begin)( src ) != SIXTRL_NULLPTR ) &&
             ( NS(TypeConstNumPtrs_const_c_begin)( dst ) != SIXTRL_NULLPTR ) &&
             ( NS(TypeConstNumPtrs_const_c_begin)( src ) != SIXTRL_NULLPTR ) &&
             ( src_store_be != ( NS(store_backend_t)
                 )SIXTRL_STORAGE_BE_ILLEGAL ) &&
             ( dst_store_be != ( NS(store_backend_t)
                 )SIXTRL_STORAGE_BE_ILLEGAL ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_convert)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT dst,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeConstNumPtrs) *const
        SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;

    if( NS(TypeConstNumPtrs_allow_conversion)(
            dst, src, src_store_be, dst_store_be ) )
    {
        status = NS(TypeConstNumPtrs_set_a)(
            dst, NS(TypeConstNumPtrs_a)( src ) );

        status |= NS(TypeConstNumPtrs_set_b)(
            dst, NS(TypeConstNumPtrs_const_b_begin)( src ) );

        status |= NS(TypeConstNumPtrs_set_c)(
            dst, NS(TypeConstNumPtrs_const_c_begin)( src ) );
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_CONVERT_H__ */
