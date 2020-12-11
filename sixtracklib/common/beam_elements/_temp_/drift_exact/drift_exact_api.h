#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DRIFT_EXACT_API_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DRIFT_EXACT_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* default API: */

    template< class DriftExactT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_is_drift_exact< DriftExactT >(),
        typename TypeMethodParamTraits< typename DriftExactTraits<
            DriftExactT >::real_t >::value_type >::type
    DriftExact_default_length( SIXTRL_BE_ARGPTR_DEC const DriftExactT *const
        SIXTRL_RESTRICT /*elem*/ = SIXTRL_NULLPTR )
    {
        return typename TypeMethodParamTraits< typename DriftExactTraits< DriftExactT
            >::real_t >::value_type{ 0 };
    }

    template< class DriftExactT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_is_drift_exact< DriftExactT >(),
        arch_status_t >::type
    DriftExact_set_default_length( SIXTRL_BE_ARGPTR_DEC DriftExactT*
        SIXTRL_RESTRICT elem = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ObjData_is_drift_exact< DriftExactT >(),
                       "DriftExactT required to be a drift_exact class" );

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( elem != SIXTRL_NULLPTR )
        {
            elem->length = st::DriftExact_default_length( elem );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* getter API */

    template< class DriftExactT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename TypeMethodParamTraits<
        typename DriftExactTraits< DriftExactT >::real_t >::const_existing_type
    DriftExact_length( SIXTRL_BE_ARGPTR_DEC const DriftExactT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_is_drift_exact< DriftExactT >(),
            "DriftExactT is required to be a drift_exact class" );

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return elem->length;
    }

    /* setter API */

    template< class DriftExactT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t DriftExact_set_length(
        SIXTRL_BE_ARGPTR_DEC DriftExactT* SIXTRL_RESTRICT elem, RealArg length )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename DriftExactTraits< DriftExactT >::real_t dst_real_t;
        static_assert( st::ObjData_is_drift_exact< DriftExactT >(),
            "DriftExactT required to be a drift_exact class" );

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            status = st::Types_perform_assignment< src_real_t, dst_real_t >(
                elem->length, length );
        }

        return status;
    }

    /* init API: */

    template< class DriftExactT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftExactT*
    DriftExact_preset( SIXTRL_BE_ARGPTR_DEC DriftExactT* SIXTRL_RESTRICT elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        if( elem != SIXTRL_NULLPTR ) st::DriftExact_set_default_length( elem );
        return elem;
    }

    template< class DriftExactT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t DriftExact_init(
        SIXTRL_BE_ARGPTR_DEC DriftExactT* SIXTRL_RESTRICT elem )
    {
        return SIXTRL_CXX_NAMESPACE::DriftExact_set_default_length( elem );
    }

    template< class DriftExactT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t DriftExact_init_detailed(
        SIXTRL_BE_ARGPTR_DEC DriftExactT* SIXTRL_RESTRICT elem, RealArg length )
    {
        return SIXTRL_CXX_NAMESPACE::DriftExact_set_length( elem, length );
    }

    template< class DriftExactT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t DriftExact_init(
        SIXTRL_BE_ARGPTR_DEC DriftExactT* SIXTRL_RESTRICT elem, RealArg length )
    {
        return SIXTRL_CXX_NAMESPACE::DriftExact_init_detailed( elem, length );
    }
}

/* default API: */

template< class DriftExactT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
    typename SIXTRL_CXX_NAMESPACE::DriftExactTraits< DriftExactT >::real_t >::value_type
NS(DriftExact_default_length)( SIXTRL_BE_ARGPTR_DEC const DriftExactT *const
    SIXTRL_RESTRICT elem = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_default_length< DriftExactT >( elem );
}

template< class DriftExactT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(DriftExact_set_default_length)(
    SIXTRL_BE_ARGPTR_DEC DriftExactT* SIXTRL_RESTRICT elem = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_set_default_length( elem );
}

/* getter API */

template< class DriftExactT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::DriftExactTraits< DriftExactT >::real_t
            >::const_existing_type
NS(DriftExact_length)( SIXTRL_BE_ARGPTR_DEC const DriftExactT *const
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_length( elem );
}

/* setter API */

template< class DriftExactT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(DriftExact_set_length)( SIXTRL_BE_ARGPTR_DEC DriftExactT* SIXTRL_RESTRICT elem,
                      RealArg length )
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_set_length( elem, length );
}

/* init API: */

template< class DriftExactT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC DriftExactT*
NS(DriftExact_preset)( SIXTRL_BE_ARGPTR_DEC DriftExactT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_preset( elem );
}

template< class DriftExactT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(DriftExact_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC DriftExactT* SIXTRL_RESTRICT elem, RealArg length )
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_init_detailed( elem, length );
}

template< class DriftExactT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(DriftExact_init)(
    SIXTRL_BE_ARGPTR_DEC DriftExactT* SIXTRL_RESTRICT elem, RealArg length )
{
    return SIXTRL_CXX_NAMESPACE::DriftExact_init_detailed( elem, length );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* default API */

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(DriftExact_default_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(DriftExact_set_default_length)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

/* getter */

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(DriftExact_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

/* setter */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(DriftExact_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const length ) SIXTRL_NOEXCEPT;

/* init API: */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* NS(DriftExact_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(DriftExact_init)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(DriftExact_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const length ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* default API */

SIXTRL_INLINE NS(be_real_t) NS(DriftExact_default_length)( SIXTRL_BE_ARGPTR_DEC
    const NS(DriftExact) *const SIXTRL_RESTRICT /*elem*/ ) SIXTRL_NOEXCEPT
{
    return ( NS(be_real_t) )0;
}

SIXTRL_INLINE NS(arch_status_t) NS(DriftExact_set_default_length)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->length = NS(DriftExact_default_length)( elem );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* getter */

SIXTRL_INLINE NS(be_real_t) NS(DriftExact_length)( SIXTRL_BE_ARGPTR_DEC const
    NS(DriftExact) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return elem->length;
}

/* setter */

SIXTRL_INLINE NS(arch_status_t) NS(DriftExact_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const length ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->length = length;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* init API: */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* NS(DriftExact_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    if( elem != SIXTRL_NULLPTR ) NS(DriftExact_set_default_length)( elem );
    return elem;
}

SIXTRL_INLINE NS(arch_status_t) NS(DriftExact_init)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return NS(DriftExact_set_default_length)( elem );
}

SIXTRL_INLINE NS(arch_status_t) NS(DriftExact_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const length ) SIXTRL_NOEXCEPT
{
    return NS(DriftExact_set_length)( elem, length );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DRIFT_EXACT_API_H__ */
