#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_DERIVED_API_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_DERIVED_API_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/beam_elements/drift/drift_api.h"
    #include "sixtracklib/common/internal/math_arithmetic.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* --------------------------------------------------------------------- */
    /* length */

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_add_to_length( SIXTRL_BE_ARGPTR_DEC DriftT*
        SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
        RealArg SIXTRL_UNUSED( d_length ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_subtract_from_length(
        SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
        RealArg SIXTRL_UNUSED( d_length ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_scale_length(
        SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
        RealArg SIXTRL_UNUSED( c ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_change_sign_length( SIXTRL_BE_ARGPTR_DEC DriftT*
        SIXTRL_RESTRICT SIXTRL_UNUSED( elem ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename DriftTraits< DriftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_add_to_length( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
                         RealArg d_length )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->length += d_length;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename DriftTraits< DriftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_subtract_from_length(
        SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem, RealArg d_length )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->length -= d_length;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename DriftTraits< DriftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_scale_length( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
                        RealArg c )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->length *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_change_sign_length(
        SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->length = -( elem->length );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename DriftTraits< DriftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_add_to_length( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
                         RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename DriftTraits< DriftT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_length;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_length, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->length += d_length;
        }

        return status;
    }

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename DriftTraits< DriftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_subtract_from_length(
        SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename DriftTraits< DriftT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_length;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_length, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->length -= d_length;
        }

        return status;
    }

    template< class DriftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename DriftTraits< DriftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_scale_length( SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
                        RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename DriftTraits< DriftT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) elem->length *= c;
        }

        return status;
    }
}

template< class DriftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Drift_add_to_length)(
    SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem, RealArg d_length )
{
    return SIXTRL_CXX_NAMESPACE::Drift_add_to_length( elem, d_length );
}

template< class DriftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Drift_subtract_from_length)(
    SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem, RealArg d_length )
{
    return SIXTRL_CXX_NAMESPACE::Drift_subtract_from_length( elem, d_length );
}

template< class DriftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Drift_scale_length)(
    SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::Drift_scale_length( elem, c );
}

template< class DriftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Drift_change_sign_length)(
    SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Drift_change_sign_length( elem );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Drift_add_to_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_length ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Drift_subtract_from_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_length ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Drift_scale_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Drift_change_sign_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(arch_status_t) NS(Drift_add_to_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_length ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->length += d_length;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Drift_subtract_from_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_length ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->length -= d_length;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Drift_scale_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->length *= factor;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(Drift_change_sign_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->length = -( elem->length );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_DERIVED_API_H__ */
