#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_COMPARE_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_COMPARE_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_api.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_derived_api.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_init.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_convert.h"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/math_arithmetic.h"
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< RhsT >()  ||
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< LhsT >()  ||
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::XYShift_allow_type_conversion< LhsT, DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::XYShift_allow_type_conversion< RhsT, DiffT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_diff(
        SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT SIXTRL_UNUSED( diff ),
        SIXTRL_BE_ARGPTR_DEC const LhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( lhs ),
        SIXTRL_BE_ARGPTR_DEC const RhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( rhs ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< RhsT >()  &&
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< LhsT >()  &&
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< DiffT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_allow_type_conversion< LhsT, DiffT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_allow_type_conversion< RhsT, DiffT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_diff( SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        /* TODO: Implement "safe" arithmetic to prevent overflows */

        if( diff != SIXTRL_NULLPTR )
        {
            if( lhs != SIXTRL_NULLPTR )
            {
                if( st::XYShift_allow_conversion( diff, lhs ) )
                {
                    status = st::XYShift_convert( diff, lhs );
                }

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( rhs != SIXTRL_NULLPTR ) )
                {
                    status  = st::XYShift_subtract_from_dx(
                        diff, st::XYShift_dx( rhs ) );

                    status |= st::XYShift_subtract_from_dy(
                        diff, st::XYShift_dy( rhs ) );
                }
            }
            else if( rhs != SIXTRL_NULLPTR )
            {
                if( st::XYShift_allow_conversion( diff, rhs ) )
                {
                    status = st::XYShift_convert( diff, rhs );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status  = st::XYShift_change_sign_dx( diff );
                    status |= st::XYShift_change_sign_dy( diff );
                }
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class LhsT, class RhsT, typename cmp_result_t = typename
        SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::XYShiftTraits< LhsT >::real_t
                >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< LhsT >(),
        cmp_result_t >::type
    XYShift_compare(
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT /* lhs */,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /* rhs */
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    template< class LhsT, class RhsT, typename cmp_result_t =
         typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
             SIXTRL_CXX_NAMESPACE::XYShiftTraits< LhsT >::real_t
                 >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< LhsT >(),
        cmp_result_t >::type
    XYShift_compare(
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::TypeCompResultTraits< cmp_result_t > cmp_traits_t;
        cmp_result_t cmp_result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
        {
            cmp_result = st::Type_value_comp_result< typename XYShiftTraits< LhsT
                >::real_t, cmp_result_t, typename XYShiftTraits<
                    RhsT >::real_t >( st::XYShift_dx( lhs ),
                                      st::XYShift_dx( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result< typename XYShiftTraits< LhsT
                >::real_t, cmp_result_t, typename XYShiftTraits<
                    RhsT >::real_t >( st::XYShift_dy( lhs ),
                                      st::XYShift_dy( rhs ) );
        }
        else if( lhs != SIXTRL_NULLPTR )
        {
            cmp_result = cmp_traits_t::CMP_LHS_LARGER_RHS;
        }

        return cmp_result;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class LhsT, class RhsT, typename cmp_result_t =
        typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
        SIXTRL_CXX_NAMESPACE::XYShiftTraits< LhsT >::real_t >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< LhsT >(),
        cmp_result_t >::type
    XYShift_compare_with_tolerances(
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /*lhs*/,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /*rhs*/,
        typename TypeMethodParamTraits< typename XYShiftTraits< RhsT >::real_t
            >::const_argument_type /*rel_tol*/,
        typename TypeMethodParamTraits< typename XYShiftTraits< RhsT >::real_t
            >::const_argument_type /*abs_tol */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class LhsT, class RhsT, typename cmp_result_t =
        typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
        SIXTRL_CXX_NAMESPACE::XYShiftTraits< LhsT >::real_t >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< LhsT >(),
        cmp_result_t >::type
    XYShift_compare_with_tolerances(
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
        typename TypeMethodParamTraits< typename XYShiftTraits< RhsT >::real_t
            >::const_argument_type rel_tol,
        typename TypeMethodParamTraits< typename XYShiftTraits< RhsT >::real_t
            >::const_argument_type abs_tol )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::TypeCompResultTraits< cmp_result_t > cmp_traits_t;
        cmp_result_t cmp_result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
        {
            cmp_result = st::Type_value_comp_result< typename XYShiftTraits< LhsT
                >::real_t, cmp_result_t, typename XYShiftTraits<
                    RhsT >::real_t >( st::XYShift_dx( lhs ),
                                      st::XYShift_dx( rhs ),
                                      rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result< typename XYShiftTraits< LhsT
                >::real_t, cmp_result_t, typename XYShiftTraits<
                    RhsT >::real_t >( st::XYShift_dy( lhs ),
                                      st::XYShift_dy( rhs ),
                                      rel_tol, abs_tol );
        }
        else if( lhs != SIXTRL_NULLPTR )
        {
            cmp_result = cmp_traits_t::CMP_LHS_LARGER_RHS;
        }

        return cmp_result;
    }

    /* ********************************************************************* */
    /* LHS: NS(XYShift) */

    template< class RhsT >
    struct ObjDataComparisonHelper< ::NS(XYShift), RhsT,
        typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            SIXTRL_CXX_NAMESPACE::XYShiftTraits< ::NS(XYShift) >::real_t
                >::cmp_result_t,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::XYShift_is_type< RhsT >(), void >::type >
    {
        typedef ::NS(XYShift) LhsT;
        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
                    LhsT >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class RhsT, class DiffT >
    struct ObjDataDiffHelper< ::NS(XYShift), RhsT, DiffT,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::XYShift_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::XYShift_is_type< DiffT >(), void >::type >
    {
        typedef ::NS(Drift) LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t calculate(
            SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_diff( diff, lhs, rhs );
        }
    };

    /* --------------------------------------------------------------------- */
    /*  LHS: TXYShift< R, RAlign > */

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign, class RhsT >
    struct ObjDataComparisonHelper< SIXTRL_CXX_NAMESPACE::TXYShift< R, RAlign >,
        RhsT, typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::XYShiftTraits< SIXTRL_CXX_NAMESPACE::TXYShift<
                R, RAlign > >::real_t >::cmp_result_t,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::XYShift_is_type< RhsT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TXYShift< R, RAlign > LhsT;
        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
                    LhsT >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign, class RhsT,
              class DiffT >
    struct ObjDataDiffHelper< SIXTRL_CXX_NAMESPACE::TXYShift< R, RAlign >,
        RhsT, DiffT, typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::XYShift_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::XYShift_is_type< DiffT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TXYShift< R, RAlign > LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t calculate(
            SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_diff( diff, lhs, rhs );
        }
    };
}

template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(XYShift_diff)( SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_diff( diff, lhs, rhs );
}

template< class LhsT, class RhsT, typename cmp_result_t =
     typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
         SIXTRL_CXX_NAMESPACE::XYShiftTraits< LhsT >::real_t
             >::cmp_result_t >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t NS(XYShift_compare)(
    SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_compare<
        LhsT, RhsT, cmp_result_t >( lhs, rhs );
}


template< class LhsT, class RhsT, typename cmp_result_t =
    typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
    SIXTRL_CXX_NAMESPACE::XYShiftTraits< LhsT >::real_t >::cmp_result_t >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t
NS(XYShift_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::XYShiftTraits< RhsT >::real_t
            >::const_argument_type rel_tol,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::XYShiftTraits< RhsT >::real_t
            >::const_argument_type abs_tol )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_compare_with_tolerances<
        LhsT, RhsT, cmp_result_t >( lhs, rhs, rel_tol, abs_tol );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_diff)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT diff,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(XYShift_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(XYShift_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT rhs,
    NS(be_real_t) const rel_tol, NS(be_real_t) const abs_tol ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_diff)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT diff,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
    /* TODO: Implement "safe" arithmetic to prevent overflows */

    if( diff != SIXTRL_NULLPTR )
    {
        if( lhs != SIXTRL_NULLPTR )
        {
            if( NS(XYShift_allow_conversion)( diff, lhs ) )
            {
                status = NS(XYShift_convert)( diff, lhs );
            }

            if( ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) &&
                ( rhs != SIXTRL_NULLPTR ) )
            {
                status  = NS(XYShift_subtract_from_dx)( diff,
                                    NS(XYShift_dx)( rhs ) );

                status |= NS(XYShift_subtract_from_dy)( diff,
                                    NS(XYShift_dy)( rhs ) );
            }
        }
        else if( rhs != SIXTRL_NULLPTR )
        {
            if( NS(XYShift_allow_conversion)( diff, rhs ) )
            {
                status = NS(XYShift_convert)( diff, rhs );
            }

            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status  = NS(XYShift_change_sign_dx)( diff );
                status |= NS(XYShift_change_sign_dy)( diff );
            }
        }
    }

    return status;
}

SIXTRL_INLINE int NS(XYShift_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    int cmp_result = -1;

    if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
    {
        cmp_result = NS(Type_value_comp_result)(
                NS(XYShift_dx)( lhs ), NS(XYShift_dx)( rhs ) );

        if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
                NS(XYShift_dy)( lhs ), NS(XYShift_dy)( rhs ) );
    }
    else if( lhs != SIXTRL_NULLPTR )
    {
        cmp_result = +1;
    }

    return cmp_result;
}

SIXTRL_INLINE int NS(XYShift_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT rhs,
    NS(be_real_t) const rel_tol, NS(be_real_t) const abs_tol ) SIXTRL_NOEXCEPT
{
    int cmp_result = -1;

    if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
    {
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
                NS(XYShift_dx)( lhs ), NS(XYShift_dx)( rhs ),
                rel_tol, abs_tol );

        if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
                NS(XYShift_dy)( lhs ), NS(XYShift_dy)( rhs ),
                rel_tol, abs_tol );
    }
    else if( lhs != SIXTRL_NULLPTR )
    {
        cmp_result = +1;
    }

    return cmp_result;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_COMPARE_H__ */
