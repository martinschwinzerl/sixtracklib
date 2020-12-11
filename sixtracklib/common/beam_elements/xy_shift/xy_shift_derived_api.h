#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_DERIVED_API_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_DERIVED_API_H__

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
    /* dx */

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_add_to_dx( SIXTRL_BE_ARGPTR_DEC XYShiftT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_dx */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_subtract_from_dx( SIXTRL_BE_ARGPTR_DEC XYShiftT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_dx */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_scale_dx( SIXTRL_BE_ARGPTR_DEC XYShiftT*
        SIXTRL_RESTRICT /* elem */, RealArg /* c */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_change_sign_dx( SIXTRL_BE_ARGPTR_DEC XYShiftT*
        SIXTRL_RESTRICT /* elem */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename XYShiftTraits< XYShiftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_add_to_dx( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
                         RealArg d_dx )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->dx += d_dx;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename XYShiftTraits< XYShiftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_subtract_from_dx(
        SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem, RealArg d_dx )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->dx -= d_dx;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename XYShiftTraits< XYShiftT >::real_t >(),
        arch_status_t >::type
    XYShift_scale_dx( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
                        RealArg c )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->dx *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_change_sign_dx(
        SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->dx = -( elem->dx );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename XYShiftTraits< XYShiftT >::real_t >(),
        arch_status_t >::type
    XYShift_add_to_dx( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
                         RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename XYShiftTraits< XYShiftT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_dx;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_dx, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->dx += d_dx;
        }

        return status;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename XYShiftTraits< XYShiftT >::real_t >(),
        arch_status_t >::type
    XYShift_subtract_from_dx(
        SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename XYShiftTraits< XYShiftT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_dx;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_dx, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->dx -= d_dx;
        }

        return status;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename XYShiftTraits< XYShiftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_scale_dx( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
                        RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename XYShiftTraits< XYShiftT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) elem->dx *= c;
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* dy */

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_add_to_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_dy */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_subtract_from_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT*
        SIXTRL_RESTRICT /* elem */, RealArg /* d_dy */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_scale_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT*
        SIXTRL_RESTRICT /* elem */, RealArg /* c */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_change_sign_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT*
        SIXTRL_RESTRICT /* elem */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename XYShiftTraits< XYShiftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_add_to_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
                         RealArg d_dy )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->dy += d_dy;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename XYShiftTraits< XYShiftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_subtract_from_dy(
        SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem, RealArg d_dy )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->dy -= d_dy;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename XYShiftTraits< XYShiftT >::real_t >(),
        arch_status_t >::type
    XYShift_scale_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
                        RealArg c )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->dy *= c;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_change_sign_dy(
        SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->dy = -( elem->dy );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename XYShiftTraits< XYShiftT >::real_t >(),
        arch_status_t >::type
    XYShift_add_to_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
                         RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename XYShiftTraits< XYShiftT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_dy;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_dy, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->dy += d_dy;
        }

        return status;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename XYShiftTraits< XYShiftT >::real_t >(),
        arch_status_t >::type
    XYShift_subtract_from_dy(
        SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem, RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename XYShiftTraits< XYShiftT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t d_dy;
            status = st::Types_perform_assignment< src_t, real_t >(
                d_dy, arg );

            if( status == st::ARCH_STATUS_SUCCESS ) elem->dy -= d_dy;
        }

        return status;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            RealArg, typename XYShiftTraits< XYShiftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_scale_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
                        RealArg arg )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_t;
        typedef typename XYShiftTraits< XYShiftT >::real_t real_t;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            real_t c;
            status = st::Types_perform_assignment< src_t, real_t >( c, arg );
            if( status == st::ARCH_STATUS_SUCCESS ) elem->dy *= c;
        }

        return status;
    }
}

/* dx */

template< class XYShiftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_add_to_dx)(
    SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem, RealArg d_dx )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_add_to_dx( elem, d_dx );
}

template< class XYShiftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_subtract_from_dx)(
    SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem, RealArg d_dx )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_subtract_from_dx( elem, d_dx );
}

template< class XYShiftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_scale_dx)(
    SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_scale_dx( elem, c );
}

template< class XYShiftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_change_sign_dx)(
    SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_change_sign_dx( elem );
}

/* dy */

template< class XYShiftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_add_to_dy)(
    SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem, RealArg d_dy )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_add_to_dy( elem, d_dy );
}

template< class XYShiftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_subtract_from_dy)(
    SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem, RealArg d_dy )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_subtract_from_dy( elem, d_dy );
}

template< class XYShiftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_scale_dy)(
    SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem, RealArg c )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_scale_dy( elem, c );
}

template< class XYShiftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_change_sign_dy)(
    SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_change_sign_dy( elem );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* dx */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_add_to_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_dx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_subtract_from_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_dx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_scale_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_change_sign_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

/* dy */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_add_to_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_dy ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_subtract_from_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_dy ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_scale_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_change_sign_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* dx */

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_add_to_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_dx ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dx += d_dx;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_subtract_from_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_dx ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dx -= d_dx;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_scale_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dx *= factor;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_change_sign_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dx = -( elem->dx );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* dy */

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_add_to_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_dy ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dy += d_dy;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_subtract_from_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const d_dy ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dy -= d_dy;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_scale_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const factor ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dy *= factor;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_change_sign_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dy = -( elem->dy );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_DERIVED_API_H__ */
