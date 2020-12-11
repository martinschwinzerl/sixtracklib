#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_API_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/xy_shift/definitions.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift.h"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* dx: */

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename XYShiftTraits< XYShiftT >::real_t XYShift_default_dx(
        SIXTRL_BE_ARGPTR_DEC const XYShiftT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( elem ) = SIXTRL_NULLPTR )
    {
        return typename XYShiftTraits< XYShiftT >::real_t{ 0 };
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
        typename XYShiftTraits< XYShiftT >::real_t >::type
    XYShift_dx( SIXTRL_BE_ARGPTR_DEC const XYShiftT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::XYShift_is_type< XYShiftT >(),
            "XYShiftT required to be a xy-shift class" );

        return st::XYShift_default_dx< typename
            st::XYShiftTraits< XYShiftT >::real_t >( elem );
    }

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >(),
        typename TypeMethodParamTraits< typename XYShiftTraits<
            XYShiftT >::real_t >::const_existing_type >::type
    XYShift_dx( SIXTRL_BE_ARGPTR_DEC const XYShiftT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return elem->dx;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_set_dx(
        SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
        RealArg SIXTRL_UNUSED( dx_value ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename XYShiftTraits< XYShiftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_set_dx( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
        RealArg dx_value )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->dx = dx_value;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename XYShiftTraits< XYShiftT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename XYShiftTraits< XYShiftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_set_dx( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
        RealArg dx_value )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->dx = std::move( dx_value );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename XYShiftTraits< XYShiftT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename XYShiftTraits< XYShiftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_set_dx( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
        RealArg dx_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename st::XYShiftTraits< XYShiftT >::real_t dst_real_t;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return st::Types_perform_assignment< src_real_t, dst_real_t >(
            elem->dx, dx_value );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
    XYShift_set_default_dx( SIXTRL_BE_ARGPTR_DEC XYShiftT*
        SIXTRL_RESTRICT elem )
    {
        return SIXTRL_CXX_NAMESPACE::XYShift_set_dx( elem,
                    SIXTRL_CXX_NAMESPACE::XYShift_default_dx( elem ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* dy: */

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    typename XYShiftTraits< XYShiftT >::real_t XYShift_default_dy(
        SIXTRL_BE_ARGPTR_DEC const XYShiftT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( elem ) = SIXTRL_NULLPTR )
    {
        return typename XYShiftTraits< XYShiftT >::real_t{ 0 };
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
        typename XYShiftTraits< XYShiftT >::real_t >::type
    XYShift_dy( SIXTRL_BE_ARGPTR_DEC const XYShiftT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::XYShift_is_type< XYShiftT >(),
            "XYShiftT required to be a xy-shift class" );

        return st::XYShift_default_dy< typename
            st::XYShiftTraits< XYShiftT >::real_t >( elem );
    }

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >(),
        typename TypeMethodParamTraits< typename XYShiftTraits<
            XYShiftT >::real_t >::const_existing_type >::type
    XYShift_dy( SIXTRL_BE_ARGPTR_DEC const XYShiftT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return elem->dy;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
         SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_set_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
        RealArg SIXTRL_UNUSED( dy_value ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename XYShiftTraits< XYShiftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_set_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
                    RealArg dy_value )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->dy = dy_value;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename XYShiftTraits< XYShiftT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename XYShiftTraits< XYShiftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_set_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
                    RealArg dy_value )
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        elem->dy = std::move( dy_value );
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    template< class XYShiftT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_impl_default< XYShiftT >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
            typename std::decay< RealArg >::type,
            typename XYShiftTraits< XYShiftT >::real_t >() &&
        !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable<
            typename std::decay< RealArg >::type,
            typename XYShiftTraits< XYShiftT >::real_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_set_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
                    RealArg dy_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename std::decay< RealArg >::type src_real_t;
        typedef typename st::XYShiftTraits< XYShiftT >::real_t dst_real_t;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return st::Types_perform_assignment< src_real_t, dst_real_t >(
            elem->dy, dy_value );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
    XYShift_set_default_dy( SIXTRL_BE_ARGPTR_DEC XYShiftT*
        SIXTRL_RESTRICT elem )
    {
        return SIXTRL_CXX_NAMESPACE::XYShift_set_dy( elem,
                    SIXTRL_CXX_NAMESPACE::XYShift_default_dy( elem ) );
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* dx: */

template< class XYShiftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::XYShiftTraits< XYShiftT >::real_t
NS(XYShift_default_dx)( SIXTRL_BE_ARGPTR_DEC const XYShiftT *const
    SIXTRL_RESTRICT elem = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_default_dx( elem );
}

template< class XYShiftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::XYShiftTraits< XYShiftT >::real_t
NS(XYShift_dx)( SIXTRL_BE_ARGPTR_DEC const XYShiftT *const
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_dx( elem );
}

template< class XYShiftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_set_dx)( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
    RealArg dx_value  )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_set_dx( elem, dx_value );
}

template< class XYShiftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_set_default_dx)( SIXTRL_BE_ARGPTR_DEC XYShiftT*
    SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_set_default_dx( elem );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* dy: */

template< class XYShiftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::XYShiftTraits< XYShiftT >::real_t
NS(XYShift_default_dy)( SIXTRL_BE_ARGPTR_DEC const XYShiftT *const
    SIXTRL_RESTRICT elem = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_default_dy( elem );
}

template< class XYShiftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::XYShiftTraits< XYShiftT >::real_t NS(XYShift_dy)(
        SIXTRL_BE_ARGPTR_DEC const XYShiftT *const SIXTRL_RESTRICT elem
    ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::XYShift_dy( elem );
}

template< class XYShiftT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_set_dy)( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
    RealArg dy_value  )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_set_dy( elem, dy_value );
}

template< class XYShiftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_set_default_dy)( SIXTRL_BE_ARGPTR_DEC XYShiftT*
    SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_set_default_dy( elem );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* dx: */

SIXTRL_STATIC SIXTRL_FN NS(be_real_t)
NS(XYShift_default_dx)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(XYShift_dx)( SIXTRL_BE_ARGPTR_DEC
    const NS(XYShift) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_set_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const dx_value  ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_set_default_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* dy: */

SIXTRL_STATIC SIXTRL_FN NS(be_real_t)
NS(XYShift_default_dy)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(XYShift_dy)( SIXTRL_BE_ARGPTR_DEC
    const NS(XYShift) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_set_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const dy_value  ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_set_default_dy)(
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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* dx: */

SIXTRL_INLINE NS(be_real_t)
NS(XYShift_default_dx)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(be_real_t) )0;
}

SIXTRL_INLINE NS(be_real_t) NS(XYShift_dx)( SIXTRL_BE_ARGPTR_DEC
    const NS(XYShift) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return elem->dx;
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_set_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const dx_value  ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dx = dx_value;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_set_default_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dx = NS(XYShift_default_dx)();
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* dy: */

SIXTRL_INLINE NS(be_real_t) NS(XYShift_default_dy)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(be_real_t) )0;
}

SIXTRL_INLINE NS(be_real_t) NS(XYShift_dy)( SIXTRL_BE_ARGPTR_DEC
    const NS(XYShift) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return elem->dy;
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_set_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const dy_value  ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dy = dy_value;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_set_default_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dy = NS(XYShift_default_dy)();
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_API_H__ */
