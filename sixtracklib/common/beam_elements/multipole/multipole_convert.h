#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_CONVERT_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_CONVERT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole.hpp"
    #include "sixtracklib/common/beam_elements/multipole/multipole_vector.hpp"
    #include "sixtracklib/common/beam_elements/multipole/multipole_api.h"
    #include "sixtracklib/common/internal/obj_convert.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )

#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class SrcMultipoleT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool Multipole_allow_type_conversion(
        SIXTRL_BE_ARGPTR_DEC const DstT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( dst ) = SIXTRL_NULLPTR,
        SIXTRL_BE_ARGPTR_DEC const SrcMultipoleT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR
    ) SIXTRL_NOEXCEPT
    {
        return (
            ( SIXTRL_CXX_NAMESPACE::Multipole_is_type< SrcMultipoleT >() ) &&
            ( SIXTRL_CXX_NAMESPACE::Multipole_is_type< SrcMultipoleT >() ) &&
            ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                typename MultipoleTraits< SrcMultipoleT >::real_t,
                typename MultipoleTraits< DstT >::real_t >() ) &&
            ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                typename MultipoleTraits< SrcMultipoleT >::order_t,
                typename MultipoleTraits< DstT >::order_t >() ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool Multipole_type_conv_can_requ_prepare(
        SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( dst ) = SIXTRL_NULLPTR,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return true;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool Multipole_requ_prepare_conversion(
        SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Multipole_allow_type_conversion< SrcT, DstT >(),
                       "Illegal conversion" );

        SIXTRL_ASSERT( src_store_be != st::STORAGE_BE_ILLEGAL );
        SIXTRL_ASSERT( dst_store_be != st::STORAGE_BE_ILLEGAL );

        ( void )src_store_be;
        ( void )dst_store_be;

        return ( ( ( !std::is_same< SrcT, DstT >::value ) ||
                   ( reinterpret_cast< std::uintptr_t >( src ) !=
                     reinterpret_cast< std::uintptr_t >( dst ) ) ) &&
                 ( st::Multipole_bal_capacity( dst ) <
                     st::Multipole_bal_length( src ) ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion< SrcT, DstT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Multipole_prepare_conversion(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT /*dst*/,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT /*src*/,
        SIXTRL_CXX_NAMESPACE::store_backend_t /*src_store_backend*/ =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t /*dst_store_backend*/ =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion< SrcT, DstT >() &&
        ( SIXTRL_CXX_NAMESPACE::Multipole_impl_default< DstT >() ||
          SIXTRL_CXX_NAMESPACE::Multipole_impl_std_vector< DstT >() ),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Multipole_prepare_conversion(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::MultipoleTraits< DstT >::order_t order_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
            ( src_store_be != st::STORAGE_BE_ILLEGAL ) &&
            ( dst_store_be != st::STORAGE_BE_ILLEGAL ) )
        {
            status = st::ARCH_STATUS_SUCCESS;
            order_t const src_bal_length = st::Multipole_bal_length( src );

            if( src_bal_length > st::Multipole_bal_capacity( dst ) )
            {
                status = st::Multipole_set_bal_capacity( dst, src_bal_length );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::Multipole_set_order(
                    dst, st::Multipole_order( src ) );
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool Multipole_allow_conversion(
        SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_backend =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_backend =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return (
            ( st::Multipole_allow_type_conversion< SrcT, DstT >() ) &&
            ( src_store_backend != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
            ( dst_store_backend != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
            ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) &&
            ( st::Multipole_bal_capacity( dst ) >=
              st::Multipole_bal_length( src ) ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class SrcT, class DstT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion< SrcT, DstT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
     Multipole_convert(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT SIXTRL_UNUSED( dst ),
        SIXTRL_BE_ARGPTR_DEC const SrcT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( src ),
        SIXTRL_CXX_NAMESPACE::store_backend_t SIXTRL_UNUSED( src_store_be ) =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t SIXTRL_UNUSED( dst_store_be ) =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        Args&&... SIXTRL_UNUSED( conv_parameters ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SrcT, class DstT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion< SrcT, DstT >() &&
        ( SIXTRL_CXX_NAMESPACE::Multipole_impl_default< DstT >() ||
          SIXTRL_CXX_NAMESPACE::Multipole_impl_std_vector< DstT >() ),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Multipole_convert(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        Args&&... SIXTRL_UNUSED( conv_parameters ) )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( st::Multipole_allow_conversion(
                dst, src, src_store_be, dst_store_be ) )
        {
            status  = st::Multipole_set_order(
                        dst, st::Multipole_order( src ) );

            status |= st::Multipole_set_length(
                        dst, st::Multipole_length( src ) );

            status |= st::Multipole_set_hxl(
                        dst, st::Multipole_hxl( src ) );

            status |= st::Multipole_set_hyl(
                        dst, st::Multipole_hyl( src ) );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::Multipole_const_bal_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status |= ( st::Multipole_const_bal_begin(
                            dst ) != SIXTRL_NULLPTR )
                    ? st::Multipole_set_bal( dst,
                            st::Multipole_const_bal_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        return status;
    }

    /* ********************************************************************* */
    /* ::NS(Multipole) */

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        ::NS(Multipole), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(Multipole) SrcT;

        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConversionTypesRequireNoPrepareTraits<
        ::NS(Multipole), DstT, SrcStoreT, DstStoreT >
    {
        static constexpr bool requires_no_prepare = false;
    };

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< ::NS(Multipole), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(Multipole) SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t prepare(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_params ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::Multipole_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_params )... );

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( st::Multipole_requ_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT ) ) )
            {
                status = st::Multipole_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::Multipole_convert( dst, src, SrcStoreT,
                        DstStoreT, std::forward< Args >( conv_params )... );
                }
            }

            return status;
        }
    };

    /* ********************************************************************* */
    /* TMultipole< R, O, RAlign, IAlign >: */

    template< class R, class O, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t OAlign, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits< SIXTRL_CXX_NAMESPACE::TMultipole<
        R, O, RAlign, OAlign >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TMultipole< R, O, RAlign, OAlign> SrcT;
        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class R, class O, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t OAlign, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConversionTypesRequireNoPrepareTraits<
        SIXTRL_CXX_NAMESPACE::TMultipole< R, O, RAlign, OAlign >, DstT,
            SrcStoreT, DstStoreT >
    {
        static constexpr bool requires_no_prepare = false;
    };

    template< class R, class O, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t OAlign, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< SIXTRL_CXX_NAMESPACE::TMultipole< R, O,
        RAlign, OAlign >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TMultipole< R, O, RAlign, OAlign > SrcT;
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t prepare(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_params ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::Multipole_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_params )... );

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( st::Multipole_requ_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT ) ) )
            {
                status = st::Multipole_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::Multipole_convert( dst, src, SrcStoreT,
                        DstStoreT, std::forward< Args >( conv_params )... );
                }
            }

            return status;
        }
    };

    /* ********************************************************************* */
    /* TVectorMultipole< R, O, RAlign, OAlign, Alloc > */

    template< class R, class O, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t OAlign, class Alloc, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits< SIXTRL_CXX_NAMESPACE::TVectorMultipole<
        R, O, RAlign, OAlign, Alloc >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TVectorMultipole<
            R, O, RAlign, OAlign, Alloc > SrcT;
        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class R, class O, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t OAlign, class Alloc, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConversionTypesRequireNoPrepareTraits<
        SIXTRL_CXX_NAMESPACE::TVectorMultipole< R, O, RAlign, OAlign, Alloc >,
            DstT, SrcStoreT, DstStoreT >
    {
        static constexpr bool requires_no_prepare = false;
    };

    template< class R, class O, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t OAlign, class Alloc, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< SIXTRL_CXX_NAMESPACE::TVectorMultipole<
        R, O, RAlign, OAlign, Alloc >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TVectorMultipole<
            R, O, RAlign, OAlign, Alloc > SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t prepare(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_prepare_conversion( dst, src,
                SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_parameters )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_params ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::Multipole_convert(
                dst, src, SrcStoreT, DstStoreT, std::forward< Args >(
                    conv_params )... );

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( st::Multipole_requ_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT ) ) )
            {
                status = st::Multipole_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::Multipole_convert( dst, src, SrcStoreT,
                        DstStoreT, std::forward< Args >( conv_params )... );
                }
            }

            return status;
        }
    };
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(Multipole_allow_type_conversion)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT
        SIXTRL_UNUSED( dst ) = SIXTRL_NULLPTR,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion< SrcT, DstT >();
}


template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(Multipole_type_conv_can_requ_prepare)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT
        SIXTRL_UNUSED( dst ) = SIXTRL_NULLPTR,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion< SrcT, DstT >();
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(Multipole_requ_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_prepare_conversion(
                dst, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Multipole_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_prepare_conversion(
                dst, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(Multipole_allow_conversion)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_backend =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_backend =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_allow_conversion< SrcT, DstT >(
        dst, src, src_store_backend, dst_store_backend );
}

template< class SrcT, class DstT, typename... Args >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Multipole_convert)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    Args&&... conv_parameters )
{
    return SIXTRL_CXX_NAMESPACE::Multipole_convert( dst, src, src_store_be,
        dst_store_be, std::forward< Args >( conv_parameters )... );
}

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C"  {
#endif /* C++, Hóst */

SIXTRL_STATIC SIXTRL_FN bool NS(Multipole_allow_type_conversion)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Multipole_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Multipole_requ_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Multipole_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Multipole_allow_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_backend,
    NS(store_backend_t) const dst_store_backend ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Multipole_convert)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_backend,
    NS(store_backend_t) const dst_store_backend ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Hóst */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C"  {
#endif /* C++, Hóst */

SIXTRL_INLINE bool NS(Multipole_allow_type_conversion)( void ) SIXTRL_NOEXCEPT
{
    return true;
}

SIXTRL_INLINE bool NS(Multipole_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT
{
    return true;
}

SIXTRL_INLINE bool NS(Multipole_requ_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( NS(Multipole_allow_type_conversion)() );

    SIXTRL_ASSERT( src_store_be != (
        NS(store_backend_t ) )SIXTRL_STORAGE_BE_ILLEGAL );

    SIXTRL_ASSERT( dst_store_be != (
        NS(store_backend_t ) )SIXTRL_STORAGE_BE_ILLEGAL );

    ( void )src_store_be;
    ( void )dst_store_be;

    return ( ( src != dst ) && ( NS(Multipole_bal_capacity)( dst ) <
                 NS(Multipole_bal_length)( src ) ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(Multipole_prepare_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
        ( src_store_be != ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) &&
        ( dst_store_be != ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) )
    {
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
        NS(be_order_t) const src_bal_length = NS(Multipole_bal_length)( src );

        if( src_bal_length > NS(Multipole_bal_capacity)( dst ) )
        {
            status = NS(Multipole_set_bal_capacity)( dst, src_bal_length );
        }

        if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
        {
            status = NS(Multipole_set_order)( dst, NS(Multipole_order)( src ) );
        }
    }

    return status;
}

SIXTRL_INLINE bool NS(Multipole_allow_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    return (
        ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
        ( src_store_be != ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) &&
        ( dst_store_be != ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) &&
        ( NS(Multipole_bal_capacity)( dst ) >=
          NS(Multipole_bal_length)( src ) ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(Multipole_convert)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( NS(Multipole_allow_conversion)(
            dst, src, src_store_be, dst_store_be ) )
    {
        status  = NS(Multipole_set_length)(
            dst, NS(Multipole_length)( src ) );
        status |= NS(Multipole_set_hxl)( dst, NS(Multipole_hxl)( src ) );
        status |= NS(Multipole_set_hyl)( dst, NS(Multipole_hyl)( src ) );
        status |= NS(Multipole_set_bal)(
            dst, NS(Multipole_const_bal_begin)( src ) );
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Hóst */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_CONVERT_H__ */
