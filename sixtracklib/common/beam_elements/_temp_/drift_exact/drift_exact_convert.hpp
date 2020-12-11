#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DRIFT_EXACT_CONVERT_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DRIFT_EXACT_CONVERT_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact.h"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact.hpp"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact_api.h"
    #include "sixtracklib/common/internal/obj_convert.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool DriftExact_allow_type_conversion(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT
            /* dest */ = SIXTRL_NULLPTR,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const
            SIXTRL_RESTRICT /* src */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ( ( SIXTRL_CXX_NAMESPACE::ObjData_is_drift_exact< DstT >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::ObjData_is_drift_exact< SrcT >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                      typename DriftExactTraits< SrcT >::real_t,
                      typename DriftExactTraits< DstT >::real_t >() ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool DriftExact_allow_conversion(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        store_backend_t const src_store_be = STORAGE_BE_DEFAULT,
        store_backend_t const dst_store_be = STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        return (
            ( SIXTRL_CXX_NAMESPACE::DriftExact_allow_type_conversion<
                SrcT, DstT >( dst, src ) ) &&
            ( src_store_be != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
            ( dst_store_be != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
            ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) );
    }

    template< class SrcT, class DstT,
              store_backend_t SrcStoreT = STORAGE_BE_DEFAULT,
              store_backend_t DstStoreT = STORAGE_BE_DEFAULT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool DriftExact_requires_prepare_for_convert(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT /* dest */,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT /* src */
    ) SIXTRL_NOEXCEPT
    {
        return false;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t DriftExact_prepare_convert(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT /* dest */,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT /* src */,
        store_backend_t src_store_be = STORAGE_BE_DEFAULT,
        store_backend_t dst_store_be = STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::DriftExact_allow_type_conversion< SrcT, DstT >(),
            "conversion from SrcT to DstT is not allowed" );

        return ( ( src_store_be != STORAGE_BE_ILLEGAL ) &&
                 ( dst_store_be != STORAGE_BE_ILLEGAL ) )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t DriftExact_convert(
        SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        store_backend_t src_store_be = STORAGE_BE_DEFAULT,
        store_backend_t dst_store_be = STORAGE_BE_DEFAULT )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::DriftExact_allow_type_conversion< SrcT, DstT >(),
            "conversion from SrcT to DstT is not allowed" );

        SIXTRL_ASSERT( src != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( dst != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( src_store_be != st::STORAGE_BE_ILLEGAL );
        SIXTRL_ASSERT( dst_store_be != st::STORAGE_BE_ILLEGAL );

        ( void )src_store_be;
        ( void )dst_store_be;

        return st::DriftExact_set_length( dst, st::DriftExact_length( src ) );
    }

    /* ********************************************************************* */
    /* Allow ::NS(DriftExact) @ SrcStoreT ->
     *         DstT @ DstStoreT conversions ? */

    template< class DstT, store_backend_t SrcStoreT, store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        ::NS(DriftExact), DstT, SrcStoreT, DstStoreT >
    {
        static SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return
                ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                ( SIXTRL_CXX_NAMESPACE::DriftExact_allow_type_conversion<
                        ::NS(DriftExact), DstT >() );
        }
    };

    template< class DstT, store_backend_t SrcStoreT, store_backend_t DstStoreT >
    struct ObjDataConverter< ::NS(DriftExact), DstT, SrcStoreT, DstStoreT >
    {
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
            ::NS(DriftExact), DstT, SrcStoreT, DstStoreT >(),
           "Conversion from NS(DriftExact) @ SrcStoreT -> DstT @ DstStoreT "
           "not allowed" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t convert(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dest,
            SIXTRL_BE_ARGPTR_DEC const ::NS(DriftExact) *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::DriftExact_convert< ::NS(DriftExact), DstT >(
                dest, src, SrcStoreT, DstStoreT );
        }
    };

    /* ********************************************************************* */
    /* Allow TDriftExact< R, RAlign > @ SrcStoreT -> DstT @ DstStoreT conversions */

    template< class R, arch_size_t RAlign, class DstT,
              store_backend_t SrcStoreT, store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        TDriftExact< R, RAlign >, DstT, SrcStoreT, DstStoreT >
    {
        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return
                ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                ( SIXTRL_CXX_NAMESPACE::DriftExact_allow_type_conversion<
                        ::NS(DriftExact), DstT >() );
        }
    };

    template< class R, arch_size_t RAlign, class DstT,
              store_backend_t SrcStoreT, store_backend_t DstStoreT >
    struct ObjDataConverter< TDriftExact< R, RAlign >, DstT, SrcStoreT, DstStoreT >
    {
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
            TDriftExact< R, RAlign >, DstT, SrcStoreT, DstStoreT >(),
           "Conversion from TDriftExact< R, RAlign > @ SrcStoreT -> "
           "DstT @ DstT not allowed"
        );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t convert(
            SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dest,
            SIXTRL_BE_ARGPTR_DEC const TDriftExact< R, RAlign > *const
                SIXTRL_RESTRICT src )
        {
            return SIXTRL_CXX_NAMESPACE::DriftExact_convert< TDriftExact< R, RAlign >,
                DstT >( dest, src, SrcStoreT, DstStoreT );
        }
    };
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(DriftExact_allow_type_conversion)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT /* dest */ = SIXTRL_NULLPTR,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT /* src */
        = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_allow_type_conversion< SrcT, DstT >();
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(DriftExact_allow_conversion)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_allow_conversion< SrcT, DstT >(
        dst, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT,
        SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT =
              SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT =
              SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(DriftExact_requires_prepare_for_convert)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_requires_prepare_for_convert<
        SrcT, DstT, SrcStoreT, DstStoreT >( dest, src );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(DriftExact_prepare_convert)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_prepare_convert< SrcT, DstT >(
                dest, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(DriftExact_convert)(
    SIXTRL_BE_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT )
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_convert< SrcT, DstT >(
        dst, src, src_store_be, dst_store_be );
}

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN bool NS(DriftExact_allow_type_conversion)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(DriftExact_allow_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(DriftExact_requires_prepare_for_convert)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(DriftExact_prepare_convert)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(DriftExact_convert)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE bool NS(DriftExact_allow_type_conversion)( void ) SIXTRL_NOEXCEPT
{
    return true;
}

SIXTRL_INLINE bool NS(DriftExact_allow_conversion)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    return ( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
             ( src_store_be != ( NS(store_backend_t)
                 )SIXTRL_STORAGE_BE_ILLEGAL ) &&
             ( dst_store_be != ( NS(store_backend_t)
                 )SIXTRL_STORAGE_BE_ILLEGAL ) );
}

SIXTRL_INLINE bool NS(DriftExact_requires_prepare_for_convert)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT /*dest*/,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT /*src*/,
    NS(store_backend_t) const /*src_store_be*/,
    NS(store_backend_t) const /*dst_store_be*/ ) SIXTRL_NOEXCEPT
{
    return false;
}

SIXTRL_INLINE NS(arch_status_t) NS(DriftExact_prepare_convert)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT /*dest*/,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT /*src*/,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    return ( ( src_store_be != (
                NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) &&
             ( dst_store_be != (
                NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) )
        ? ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS
        : ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
}

SIXTRL_INLINE NS(arch_status_t) NS(DriftExact_convert)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( src_store_be != ( NS(store_backend_t
                    ) )SIXTRL_STORAGE_BE_ILLEGAL );

    SIXTRL_ASSERT( dst_store_be != ( NS(store_backend_t
                    ) )SIXTRL_STORAGE_BE_ILLEGAL );

    ( void )src_store_be;
    ( void )dst_store_be;

    return NS(DriftExact_set_length)( dst, NS(DriftExact_length)( src ) );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DRIFT_EXACT_CONVERT_HPP__ */
