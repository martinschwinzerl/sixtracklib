#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_COMPARE_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_COMPARE_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/cavity.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_api.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_derived_api.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_init.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_convert.h"
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
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< RhsT >()  ||
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< LhsT >()  ||
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::Cavity_allow_type_conversion< LhsT, DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::Cavity_allow_type_conversion< RhsT, DiffT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_diff( SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT /*diff*/,
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT /*lhs*/,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /*rhs*/
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< RhsT >()  &&
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< LhsT >()  &&
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< DiffT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_allow_type_conversion< LhsT, DiffT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_allow_type_conversion< RhsT, DiffT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_diff( SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
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
                if( st::Cavity_allow_conversion( diff, lhs ) )
                {
                    status = st::Cavity_convert( diff, lhs );
                }

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( rhs != SIXTRL_NULLPTR ) )
                {
                    status = st::Cavity_subtract_from_voltage(
                        diff, st::Cavity_voltage( rhs ) );

                    status |= st::Cavity_subtract_from_frequency(
                        diff, st::Cavity_frequency( rhs ) );

                    status |= st::Cavity_subtract_from_lag(
                        diff, st::Cavity_lag( rhs ) );
                }
            }
            else if( rhs != SIXTRL_NULLPTR )
            {
                if( st::Cavity_allow_conversion( diff, rhs ) )
                {
                    status = st::Cavity_convert( diff, rhs );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status  = st::Cavity_change_sign_voltage( diff );
                    status |= st::Cavity_change_sign_frequency( diff );
                    status |= st::Cavity_change_sign_lag( diff );
                }
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class LhsT, class RhsT, typename cmp_result_t = typename
        SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::CavityTraits< LhsT >::real_t
                >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< LhsT >(),
        cmp_result_t >::type
    Cavity_compare(
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT /* lhs */,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /* rhs */
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    template< class LhsT, class RhsT, typename cmp_result_t =
         typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
             SIXTRL_CXX_NAMESPACE::CavityTraits< LhsT >::real_t
                 >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< LhsT >(),
        cmp_result_t >::type
    Cavity_compare(
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::CavityTraits< LhsT >::real_t lhs_real_t;
        typedef typename st::CavityTraits< RhsT >::real_t rhs_real_t;
        typedef st::TypeCompResultTraits< cmp_result_t > cmp_traits_t;
        cmp_result_t cmp_result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
        {
            cmp_result = st::Type_value_comp_result< lhs_real_t, cmp_result_t,
                rhs_real_t >( st::Cavity_voltage( lhs ),
                    st::Cavity_voltage( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result< lhs_real_t, cmp_result_t,
                rhs_real_t >( st::Cavity_frequency( lhs ),
                    st::Cavity_frequency( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result< lhs_real_t, cmp_result_t,
                rhs_real_t >( st::Cavity_lag( lhs ),
                    st::Cavity_lag( rhs ) );
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
        SIXTRL_CXX_NAMESPACE::CavityTraits< LhsT >::real_t >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::Cavity_is_type< LhsT >(),
        cmp_result_t >::type
    Cavity_compare_with_tolerances(
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /*lhs*/,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /*rhs*/,
        typename TypeMethodParamTraits< typename CavityTraits< RhsT >::real_t
            >::const_argument_type /*rel_tol*/,
        typename TypeMethodParamTraits< typename CavityTraits< RhsT >::real_t
            >::const_argument_type /*abs_tol */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class LhsT, class RhsT, typename cmp_result_t =
        typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
        SIXTRL_CXX_NAMESPACE::CavityTraits< LhsT >::real_t >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< LhsT >(),
        cmp_result_t >::type
    Cavity_compare_with_tolerances(
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
        typename TypeMethodParamTraits< typename CavityTraits< RhsT >::real_t
            >::const_argument_type rel_tol,
        typename TypeMethodParamTraits< typename CavityTraits< RhsT >::real_t
            >::const_argument_type abs_tol )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::CavityTraits< LhsT >::real_t lhs_real_t;
        typedef typename st::CavityTraits< RhsT >::real_t rhs_real_t;
        typedef st::TypeCompResultTraits< cmp_result_t > cmp_traits_t;
        cmp_result_t cmp_result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
        {
            cmp_result = st::Type_value_comp_result< lhs_real_t, cmp_result_t,
                rhs_real_t >( st::Cavity_voltage( lhs ),
                    st::Cavity_voltage( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result< lhs_real_t, cmp_result_t,
                rhs_real_t >( st::Cavity_frequency( lhs ),
                    st::Cavity_frequency( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result< lhs_real_t, cmp_result_t,
                rhs_real_t >( st::Cavity_lag( lhs ),
                    st::Cavity_lag( rhs ), rel_tol, abs_tol );
        }
        else if( lhs != SIXTRL_NULLPTR )
        {
            cmp_result = cmp_traits_t::CMP_LHS_LARGER_RHS;
        }

        return cmp_result;
    }

} /* namespace: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/cavity.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* ********************************************************************* */
    /* LHS: NS(Cavity) */

    template< class RhsT >
    struct ObjDataComparisonHelper< ::NS(Cavity), RhsT, typename
            SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
                SIXTRL_CXX_NAMESPACE::CavityTraits< ::NS(Cavity) >::real_t
                    >::cmp_result_t,
        typename std::enable_if< SIXTRL_CXX_NAMESPACE::Cavity_is_type< RhsT >(),
            void >::type >
    {
        typedef ::NS(Cavity) LhsT;
        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
                SIXTRL_CXX_NAMESPACE::CavityTraits< LhsT >::real_t
                    >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Cavity_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Cavity_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class RhsT, class DiffT >
    struct ObjDataDiffHelper< ::NS(Cavity), RhsT, DiffT,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::Cavity_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::Cavity_is_type< DiffT >(), void >::type >
    {
        typedef ::NS(Cavity) LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t calculate(
            SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Cavity_diff( diff, lhs, rhs );
        }
    };

    /* --------------------------------------------------------------------- */
    /*  LHS: TCavity< R, RAlign > */

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign, class RhsT >
    struct ObjDataComparisonHelper< SIXTRL_CXX_NAMESPACE::TCavity< R, RAlign >,
        RhsT, typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            typename SIXTRL_CXX_NAMESPACE::CavityTraits<
                SIXTRL_CXX_NAMESPACE::TCavity< R, RAlign > >::real_t
                    >::cmp_result_t,
            typename std::enable_if< SIXTRL_CXX_NAMESPACE::Cavity_is_type<
                RhsT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TCavity< R, RAlign > LhsT;
        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            typename SIXTRL_CXX_NAMESPACE::CavityTraits< LhsT >::real_t
                    >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Cavity_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Cavity_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign, class RhsT,
              class DiffT >
    struct ObjDataDiffHelper< SIXTRL_CXX_NAMESPACE::TCavity< R, RAlign >,
        RhsT, DiffT, typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::Cavity_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::Cavity_is_type< DiffT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TCavity< R, RAlign > LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t calculate(
            SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Cavity_diff( diff, lhs, rhs );
        }
    };
}

template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Cavity_diff)( SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_diff( diff, lhs, rhs );
}

template< class LhsT, class RhsT, typename cmp_result_t =
     typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
         SIXTRL_CXX_NAMESPACE::CavityTraits< LhsT >::real_t
             >::cmp_result_t >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t NS(Cavity_compare)(
    SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_compare<
        LhsT, RhsT, cmp_result_t >( lhs, rhs );
}


template< class LhsT, class RhsT, typename cmp_result_t =
    typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
    SIXTRL_CXX_NAMESPACE::CavityTraits< LhsT >::real_t >::cmp_result_t >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t
NS(Cavity_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::CavityTraits< RhsT >::real_t
            >::const_argument_type rel_tol,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::CavityTraits< RhsT >::real_t
            >::const_argument_type abs_tol )
{
    return SIXTRL_CXX_NAMESPACE::Cavity_compare_with_tolerances<
        LhsT, RhsT, cmp_result_t >( lhs, rhs, rel_tol, abs_tol );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Cavity_diff)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT diff,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(Cavity_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(Cavity_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT rhs,
    NS(be_real_t) const rel_tol, NS(be_real_t) const abs_tol ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_COMPARE_H__ */

SIXTRL_INLINE NS(arch_status_t) NS(Cavity_diff)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT diff,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
    /* TODO: Implement "safe" arithmetic to prevent overflows */

    if( diff != SIXTRL_NULLPTR )
    {
        if( lhs != SIXTRL_NULLPTR )
        {
            if( NS(Cavity_allow_conversion)( diff, lhs ) )
            {
                status = NS(Cavity_convert)( diff, lhs );
            }

            if( ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) &&
                ( rhs != SIXTRL_NULLPTR ) )
            {
                status  = NS(Cavity_subtract_from_voltage)(
                    diff, NS(Cavity_voltage)( rhs ) );

                status |= NS(Cavity_subtract_from_frequency)(
                    diff, NS(Cavity_frequency)( rhs ) );

                status |= NS(Cavity_subtract_from_lag)(
                    diff, NS(Cavity_lag)( rhs ) );
            }
        }
        else if( rhs != SIXTRL_NULLPTR )
        {
            if( NS(Cavity_allow_conversion)( diff, rhs ) )
            {
                status = NS(Cavity_convert)( diff, rhs );
            }

            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status  = NS(Cavity_change_sign_voltage)( diff );
                status |= NS(Cavity_change_sign_frequency)( diff );
                status |= NS(Cavity_change_sign_lag)( diff );
            }
        }
    }

    return status;
}

SIXTRL_INLINE int NS(Cavity_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    int cmp_result = -1;

    if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
    {
        cmp_result = NS(Type_value_comp_result)(
                NS(Cavity_voltage)( lhs ), NS(Cavity_voltage)( rhs ) );

        if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
                NS(Cavity_frequency)( lhs ), NS(Cavity_frequency)( rhs ) );

        if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
                NS(Cavity_lag)( lhs ), NS(Cavity_lag)( rhs ) );

    }
    else if( lhs != SIXTRL_NULLPTR )
    {
        cmp_result = +1;
    }

    return cmp_result;
}

SIXTRL_INLINE int NS(Cavity_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT rhs,
    NS(be_real_t) const rel_tol, NS(be_real_t) const abs_tol ) SIXTRL_NOEXCEPT
{
    int cmp_result = -1;

    if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
    {
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
                NS(Cavity_voltage)( lhs ), NS(Cavity_voltage)( rhs ),
                    rel_tol, abs_tol );

        if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
                NS(Cavity_frequency)( lhs ), NS(Cavity_frequency)( rhs ),
                    rel_tol, abs_tol );

        if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
                NS(Cavity_lag)( lhs ), NS(Cavity_lag)( rhs ),
                    rel_tol, abs_tol );
    }
    else if( lhs != SIXTRL_NULLPTR )
    {
        cmp_result = +1;
    }

    return cmp_result;
}
