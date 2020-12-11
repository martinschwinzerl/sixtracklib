#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_COMPARE_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_COMPARE_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/srotation.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation_api.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation_derived_api.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation_init.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation_convert.h"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< RhsT >()  ||
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< LhsT >()  ||
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::SRotation_allow_type_conversion< LhsT, DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::SRotation_allow_type_conversion< RhsT, DiffT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_diff( SIXTRL_BE_ARGPTR_DEC DiffT*
            SIXTRL_RESTRICT SIXTRL_UNUSED( diff ),
        SIXTRL_BE_ARGPTR_DEC const LhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( lhs ),
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( rhs ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< RhsT >()  &&
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< LhsT >()  &&
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< DiffT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_allow_type_conversion< LhsT, DiffT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_allow_type_conversion< RhsT, DiffT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_diff( SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
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
                if( st::SRotation_allow_conversion( diff, lhs ) )
                {
                    status = st::SRotation_convert( diff, lhs );
                }

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( rhs != SIXTRL_NULLPTR ) )
                {
                    status  = st::SRotation_subtract_from_cos_z(
                        diff, st::SRotation_cos_z( rhs ) );

                    status |= st::SRotation_subtract_from_sin_z(
                        diff, st::SRotation_sin_z( rhs ) );
                }
            }
            else if( rhs != SIXTRL_NULLPTR )
            {
                if( st::SRotation_allow_conversion( diff, rhs ) )
                {
                    status = st::SRotation_convert( diff, rhs );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status  = st::SRotation_change_sign_cos_z( diff );
                    status |= st::SRotation_change_sign_sin_z( diff );
                }
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class LhsT, class RhsT, typename cmp_result_t = typename
        SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::SRotationTraits< LhsT >::real_t
                >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< LhsT >(),
        cmp_result_t >::type
    SRotation_compare(
        SIXTRL_BE_ARGPTR_DEC const LhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( lhs ),
        SIXTRL_BE_ARGPTR_DEC const RhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( rhs ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    template< class LhsT, class RhsT, typename cmp_result_t =
         typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
             SIXTRL_CXX_NAMESPACE::SRotationTraits< LhsT >::real_t
                 >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< LhsT >(),
        cmp_result_t >::type
    SRotation_compare(
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::SRotationTraits< LhsT >::real_t lhs_real_t;
        typedef typename st::SRotationTraits< RhsT >::real_t rhs_real_t;
        typedef st::TypeCompResultTraits< cmp_result_t > cmp_traits_t;
        cmp_result_t cmp_result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
        {
            cmp_result = st::Type_value_comp_result< lhs_real_t,
                cmp_result_t, rhs_real_t >(
                    st::SRotation_cos_z( lhs ), st::SRotation_cos_z( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >(
                        st::SRotation_sin_z( lhs ),
                        st::SRotation_sin_z( rhs ) );
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
        SIXTRL_CXX_NAMESPACE::SRotationTraits< LhsT >::real_t >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::SRotation_is_type< LhsT >(),
        cmp_result_t >::type
    SRotation_compare_with_tolerances(
        SIXTRL_BE_ARGPTR_DEC const RhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( lhs ),
        SIXTRL_BE_ARGPTR_DEC const RhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( rhs ),
        typename TypeMethodParamTraits< typename SRotationTraits< RhsT >::real_t
            >::const_argument_type SIXTRL_UNUSED( rel_tol ),
        typename TypeMethodParamTraits< typename SRotationTraits< RhsT >::real_t
            >::const_argument_type SIXTRL_UNUSED( abs_tol ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class LhsT, class RhsT, typename cmp_result_t =
        typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
        SIXTRL_CXX_NAMESPACE::SRotationTraits< LhsT >::real_t >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< LhsT >(),
        cmp_result_t >::type
    SRotation_compare_with_tolerances(
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
        typename TypeMethodParamTraits< typename SRotationTraits< RhsT >::real_t
            >::const_argument_type rel_tol,
        typename TypeMethodParamTraits< typename SRotationTraits< RhsT >::real_t
            >::const_argument_type abs_tol )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::SRotationTraits< LhsT >::real_t lhs_real_t;
        typedef typename st::SRotationTraits< RhsT >::real_t rhs_real_t;
        typedef st::TypeCompResultTraits< cmp_result_t > cmp_traits_t;
        cmp_result_t cmp_result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
        {
            cmp_result = st::Type_value_comp_result< lhs_real_t,
                cmp_result_t, rhs_real_t >(
                    st::SRotation_cos_z( lhs ), st::SRotation_cos_z( rhs ),
                    rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >(
                        st::SRotation_sin_z( lhs ),
                        st::SRotation_sin_z( rhs ), rel_tol, abs_tol );
        }
        else if( lhs != SIXTRL_NULLPTR )
        {
            cmp_result = cmp_traits_t::CMP_LHS_LARGER_RHS;
        }

        return cmp_result;
    }

    /* ********************************************************************* */
    /* LHS: NS(SRotation) */

    template< class RhsT >
    struct ObjDataComparisonHelper< ::NS(SRotation), RhsT,
        typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            SIXTRL_CXX_NAMESPACE::SRotationTraits< ::NS(SRotation) >::real_t
                >::cmp_result_t,
        typename std::enable_if< SIXTRL_CXX_NAMESPACE::SRotation_is_type<
            RhsT >(), void >::type >
    {
        typedef ::NS(SRotation) LhsT;
        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
                    SIXTRL_CXX_NAMESPACE::SRotationTraits< LhsT >::real_t
                        >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class RhsT, class DiffT >
    struct ObjDataDiffHelper< ::NS(SRotation), RhsT, DiffT,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::SRotation_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::SRotation_is_type< DiffT >(), void >::type >
    {
        typedef ::NS(SRotation) LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t calculate(
            SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_diff( diff, lhs, rhs );
        }
    };

    /* --------------------------------------------------------------------- */
    /*  LHS: TSRotation< R, RAlign > */

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign, class RhsT >
    struct ObjDataComparisonHelper<
        SIXTRL_CXX_NAMESPACE::TSRotation< R, RAlign >, RhsT,
        typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::SRotationTraits<
                SIXTRL_CXX_NAMESPACE::TSRotation< R, RAlign > >::real_t
                    >::cmp_result_t,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::SRotation_is_type< RhsT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TSRotation< R, RAlign > LhsT;
        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::SRotationTraits< LhsT >::real_t
                >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class R, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              class RhsT, class DiffT >
    struct ObjDataDiffHelper< SIXTRL_CXX_NAMESPACE::TSRotation< R, RAlign >,
        RhsT, DiffT, typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::SRotation_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::SRotation_is_type< DiffT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TSRotation< R, RAlign > LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t calculate(
            SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_diff( diff, lhs, rhs );
        }
    };
}

template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(SRotation_diff)( SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_diff( diff, lhs, rhs );
}

template< class LhsT, class RhsT, typename cmp_result_t =
     typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
         SIXTRL_CXX_NAMESPACE::SRotationTraits< LhsT >::real_t
             >::cmp_result_t >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t NS(SRotation_compare)(
    SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_compare<
        LhsT, RhsT, cmp_result_t >( lhs, rhs );
}


template< class LhsT, class RhsT, typename cmp_result_t =
    typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
    SIXTRL_CXX_NAMESPACE::SRotationTraits< LhsT >::real_t >::cmp_result_t >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t
NS(SRotation_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::SRotationTraits< RhsT >::real_t
            >::const_argument_type rel_tol,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::SRotationTraits< RhsT >::real_t
            >::const_argument_type abs_tol )
{
    return SIXTRL_CXX_NAMESPACE::SRotation_compare_with_tolerances<
        LhsT, RhsT, cmp_result_t >( lhs, rhs, rel_tol, abs_tol );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(SRotation_diff)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT diff,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(SRotation_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(SRotation_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs,
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

SIXTRL_INLINE NS(arch_status_t) NS(SRotation_diff)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT diff,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
    /* TODO: Implement "safe" arithmetic to prevent overflows */

    if( diff != SIXTRL_NULLPTR )
    {
        if( lhs != SIXTRL_NULLPTR )
        {
            if( NS(SRotation_allow_conversion)( diff, lhs ) )
            {
                status = NS(SRotation_convert)( diff, lhs );
            }

            if( ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) &&
                ( rhs != SIXTRL_NULLPTR ) )
            {
                status  = NS(SRotation_subtract_from_cos_z)( diff,
                                NS(SRotation_cos_z)( rhs ) );

                status |= NS(SRotation_subtract_from_sin_z)( diff,
                                NS(SRotation_sin_z)( rhs ) );
            }
        }
        else if( rhs != SIXTRL_NULLPTR )
        {
            if( NS(SRotation_allow_conversion)( diff, rhs ) )
            {
                status = NS(SRotation_convert)( diff, rhs );
            }

            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status  = NS(SRotation_change_sign_cos_z)( diff );
                status |= NS(SRotation_change_sign_sin_z)( diff );
            }
        }
    }

    return status;
}

SIXTRL_INLINE int NS(SRotation_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    int cmp_result = -1;

    if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
    {
        cmp_result = NS(Type_value_comp_result)(
                NS(SRotation_cos_z)( lhs ), NS(SRotation_cos_z)( rhs ) );

        if( cmp_result == 0 )
            cmp_result = NS(Type_value_comp_result)(
                NS(SRotation_sin_z)( lhs ), NS(SRotation_sin_z)( rhs ) );
    }
    else if( lhs != SIXTRL_NULLPTR )
    {
        cmp_result = +1;
    }

    return cmp_result;
}

SIXTRL_INLINE int NS(SRotation_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs,
    NS(be_real_t) const rel_tol, NS(be_real_t) const abs_tol ) SIXTRL_NOEXCEPT
{
    int cmp_result = -1;

    if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
    {
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
                NS(SRotation_cos_z)( lhs ), NS(SRotation_cos_z)( rhs ),
                    rel_tol, abs_tol );

        if( cmp_result == 0 )
            cmp_result = NS(Type_value_comp_result_with_tolerances)(
                NS(SRotation_sin_z)( lhs ), NS(SRotation_sin_z)( rhs ),
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

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_COMPARE_H__ */
