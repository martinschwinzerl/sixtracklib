#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_COMPARE_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_COMPARE_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_api.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_derived_api.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_init.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_convert.h"
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
        !SIXTRL_CXX_NAMESPACE::Multipole_is_type< RhsT >()  ||
        !SIXTRL_CXX_NAMESPACE::Multipole_is_type< LhsT >()  ||
        !SIXTRL_CXX_NAMESPACE::Multipole_is_type< DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion< LhsT, DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion< RhsT, DiffT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Multipole_diff( SIXTRL_BE_ARGPTR_DEC DiffT*
        SIXTRL_RESTRICT SIXTRL_UNUSED( diff ),
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
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< RhsT >()  &&
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< LhsT >()  &&
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< DiffT >() &&
        SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion< LhsT, DiffT >() &&
        SIXTRL_CXX_NAMESPACE::Multipole_allow_type_conversion< RhsT, DiffT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Multipole_diff( SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
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
                st::store_backend_t const src_store_be = st::STORAGE_BE_DEFAULT;
                st::store_backend_t const dst_store_be = st::STORAGE_BE_DEFAULT;

                status = st::Multipole_convert(
                    diff, lhs, src_store_be, dst_store_be );

                if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                    ( st::Multipole_requ_prepare_conversion(
                        diff, lhs, src_store_be, dst_store_be ) ) )
                {
                    status = st::Multipole_prepare_conversion(
                        diff, lhs, src_store_be, dst_store_be );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        status = st::Multipole_convert(
                            diff, lhs, src_store_be, dst_store_be );
                    }
                }

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( rhs != SIXTRL_NULLPTR ) )
                {
                    status = st::Multipole_subtract_from_length(
                        diff, st::Multipole_length( rhs ) );

                    status |= st::Multipole_subtract_from_hxl(
                        diff, st::Multipole_hxl( rhs ) );

                    status |= st::Multipole_subtract_from_hyl(
                        diff, st::Multipole_hyl( rhs ) );

                    status |= st::Multipole_subtract_from_bal(
                        diff, st::Multipole_const_bal_begin( rhs ) );

                    /* diff order after bal so that we can use order in the loop
                     * over all bal values */

                    status |= st::Multipole_subtract_from_order(
                        diff, st::Multipole_order( rhs ) );
                }
            }
            else if( rhs != SIXTRL_NULLPTR )
            {
                if( st::Multipole_allow_conversion( diff, rhs ) )
                {
                    status = st::Multipole_convert( diff, rhs );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status |= st::Multipole_change_sign_length( diff );
                    status |= st::Multipole_change_sign_hxl( diff );
                    status |= st::Multipole_change_sign_hyl( diff );
                    status |= st::Multipole_change_sign_bal( diff );
                    status |= st::Multipole_change_sign_order( diff );
                }
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class LhsT, class RhsT, typename cmp_result_t = typename
        SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::MultipoleTraits< LhsT >::real_t
                >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Multipole_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::Multipole_is_type< LhsT >(),
        cmp_result_t >::type
    Multipole_compare(
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT /* lhs */,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /* rhs */
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    template< class LhsT, class RhsT, typename cmp_result_t =
         typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
             SIXTRL_CXX_NAMESPACE::MultipoleTraits< LhsT >::real_t
                 >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< LhsT >(),
        cmp_result_t >::type
    Multipole_compare(
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef typename st::MultipoleTraits< LhsT >::real_t lhs_real_t;
        typedef typename st::TypeMethodParamTraits< typename
            st::MultipoleTraits< LhsT >::real_t >::const_pointer lhs_real_iter_t;

        typedef typename st::MultipoleTraits< RhsT >::real_t rhs_real_t;
        typedef typename st::TypeMethodParamTraits< typename
            st::MultipoleTraits< RhsT >::real_t >::const_pointer rhs_real_iter_t;

        typedef st::TypeCompResultTraits< cmp_result_t > cmp_traits_t;
        cmp_result_t cmp_result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
        {
            cmp_result = st::Type_value_comp_result<
                typename st::MultipoleTraits< LhsT >::order_t, cmp_result_t,
                typename st::MultipoleTraits< RhsT >::order_t >(
                    st::Multipole_order( lhs ), st::Multipole_order( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Multipole_length( lhs ),
                                   st::Multipole_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Multipole_hxl( lhs ),
                                  st::Multipole_hxl( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Multipole_hyl( lhs ),
                                  st::Multipole_hyl( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Multipole_hyl( lhs ),
                                  st::Multipole_hyl( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result_for_range<
                    lhs_real_iter_t, cmp_result_t, rhs_real_iter_t >(
                    st::Multipole_const_bal_begin( lhs ),
                    st::Multipole_const_bal_end( lhs ),
                    st::Multipole_const_bal_begin( rhs ) );
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
        SIXTRL_CXX_NAMESPACE::MultipoleTraits< LhsT >::real_t >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Multipole_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::Multipole_is_type< LhsT >(),
        cmp_result_t >::type
    Multipole_compare_with_tolerances(
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /*lhs*/,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /*rhs*/,
        typename TypeMethodParamTraits< typename MultipoleTraits< RhsT >::real_t
            >::const_argument_type /*rel_tol*/,
        typename TypeMethodParamTraits< typename MultipoleTraits< RhsT >::real_t
            >::const_argument_type /*abs_tol */ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class LhsT, class RhsT, typename cmp_result_t =
        typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
        SIXTRL_CXX_NAMESPACE::MultipoleTraits< LhsT >::real_t >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< LhsT >(),
        cmp_result_t >::type
    Multipole_compare_with_tolerances(
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
        typename TypeMethodParamTraits< typename MultipoleTraits< RhsT >::real_t
            >::const_argument_type rel_tol,
        typename TypeMethodParamTraits< typename MultipoleTraits< RhsT >::real_t
            >::const_argument_type abs_tol )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef typename st::MultipoleTraits< LhsT >::real_t lhs_real_t;
        typedef typename st::TypeMethodParamTraits< typename
            st::MultipoleTraits< LhsT > >::const_pointer lhs_real_iter_t;

        typedef typename st::MultipoleTraits< RhsT >::real_t rhs_real_t;
        typedef typename st::TypeMethodParamTraits< typename
            st::MultipoleTraits< RhsT > >::const_pointer rhs_real_iter_t;

        typedef st::TypeCompResultTraits< cmp_result_t > cmp_traits_t;
        cmp_result_t cmp_result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
        {
            cmp_result = st::Type_value_comp_result<
                typename st::MultipoleTraits< LhsT >::order_t, cmp_result_t,
                typename st::MultipoleTraits< RhsT >::order_t >(
                    st::Multipole_order( lhs ), st::Multipole_order( rhs ),
                        rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Multipole_length( lhs ),
                        st::Multipole_length( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Multipole_hxl( lhs ),
                        st::Multipole_hxl( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Multipole_hyl( lhs ),
                                  st::Multipole_hyl( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Multipole_hyl( lhs ),
                                  st::Multipole_hyl( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_iter_t,
                cmp_result_t, rhs_real_iter_t >(
                    st::Multipole_const_bal_begin( lhs ),
                    st::Multipole_const_bal_end( lhs ),
                    st::Multipole_const_bal_begin( rhs ) );
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
    #include "sixtracklib/common/beam_elements/multipole/multipole.hpp"
    #include "sixtracklib/common/beam_elements/multipole/multipole_vector.hpp"
#endif /* C++ */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* ********************************************************************* */
    /* LHS: NS(Multipole) */

    template< class RhsT >
    struct ObjDataComparisonHelper< ::NS(Multipole), RhsT,
        typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            SIXTRL_CXX_NAMESPACE::MultipoleTraits< ::NS(Multipole) >::real_t
                >::cmp_result_t,
        typename std::enable_if< SIXTRL_CXX_NAMESPACE::Multipole_is_type<
            RhsT >(), void >::type >
    {
        typedef ::NS(Multipole) LhsT;

        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
                    typename SIXTRL_CXX_NAMESPACE::MultipoleTraits<
                        LhsT >::real_t >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class RhsT, class DiffT >
    struct ObjDataDiffHelper< ::NS(Multipole), RhsT, DiffT,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< DiffT >(), void >::type >
    {
        typedef ::NS(Multipole) LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        calculate(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_diff( diff, lhs, rhs );
        }
    };

    /* --------------------------------------------------------------------- */
    /*  LHS: TMultipole< R, O, RAlign, OAlign > */

    template< class R, class O, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t OAlign, class RhsT >
    struct ObjDataComparisonHelper< SIXTRL_CXX_NAMESPACE::TMultipole< R, O,
            RAlign, OAlign >, RhsT,
        typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::MultipoleTraits<
                SIXTRL_CXX_NAMESPACE::TMultipole< R, O, RAlign, OAlign >
                    >::real_t >::cmp_result_t,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< RhsT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TMultipole< R, O, RAlign, OAlign > LhsT;
        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
                    typename SIXTRL_CXX_NAMESPACE::MultipoleTraits<
                        LhsT >::real_t >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class R, class O, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t OAlign,
              class RhsT, class DiffT >
    struct ObjDataDiffHelper< SIXTRL_CXX_NAMESPACE::TMultipole< R, O,
            RAlign, OAlign >, RhsT, DiffT, typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< DiffT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TMultipole< R, O, RAlign, OAlign > LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        calculate(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_diff( diff, lhs, rhs );
        }
    };

    /* --------------------------------------------------------------------- */
    /*  LHS: TVectorMultipole< R, O, RAlign, OAlign, Alloc > */

    template< class R, class O, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t OAlign, class Alloc, class RhsT >
    struct ObjDataComparisonHelper< SIXTRL_CXX_NAMESPACE::TVectorMultipole<
            R, O, RAlign, OAlign, Alloc >, RhsT,
        typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::MultipoleTraits<
                SIXTRL_CXX_NAMESPACE::TVectorMultipole<
                    R, O, RAlign, OAlign, Alloc > >::real_t >::cmp_result_t,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< RhsT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TVectorMultipole<
            R, O, RAlign, OAlign, Alloc > LhsT;
        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
                    typename SIXTRL_CXX_NAMESPACE::MultipoleTraits<
                        LhsT >::real_t >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class R, class O, SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t OAlign, class Alloc,
              class RhsT, class DiffT >
    struct ObjDataDiffHelper<
        SIXTRL_CXX_NAMESPACE::TVectorMultipole< R, O, RAlign, OAlign, Alloc >,
            RhsT, DiffT, typename std::enable_if<
                SIXTRL_CXX_NAMESPACE::Multipole_is_type< RhsT >() &&
                SIXTRL_CXX_NAMESPACE::Multipole_is_type< DiffT >(),
            void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TVectorMultipole<
                    R, O, RAlign, OAlign, Alloc > LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        calculate(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_diff( diff, lhs, rhs );
        }
    };
}

template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Multipole_diff)( SIXTRL_BE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
        SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
{
    return SIXTRL_CXX_NAMESPACE::Multipole_diff( diff, lhs, rhs );
}

template< class LhsT, class RhsT, typename cmp_result_t =
     typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
         SIXTRL_CXX_NAMESPACE::MultipoleTraits< LhsT >::real_t
             >::cmp_result_t >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t NS(Multipole_compare)(
    SIXTRL_BE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
{
    return SIXTRL_CXX_NAMESPACE::Multipole_compare<
        LhsT, RhsT, cmp_result_t >( lhs, rhs );
}


template< class LhsT, class RhsT, typename cmp_result_t =
    typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
    SIXTRL_CXX_NAMESPACE::MultipoleTraits< LhsT >::real_t >::cmp_result_t >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t
NS(Multipole_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::MultipoleTraits< RhsT >::real_t
            >::const_argument_type rel_tol,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::MultipoleTraits< RhsT >::real_t
            >::const_argument_type abs_tol )
{
    return SIXTRL_CXX_NAMESPACE::Multipole_compare_with_tolerances<
        LhsT, RhsT, cmp_result_t >( lhs, rhs, rel_tol, abs_tol );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Multipole_diff)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT diff,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(Multipole_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(Multipole_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs,
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

SIXTRL_INLINE NS(arch_status_t) NS(Multipole_diff)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT diff,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;
    /* TODO: Implement "safe" arithmetic to prevent overflows */

    if( diff != SIXTRL_NULLPTR )
    {
        if( lhs != SIXTRL_NULLPTR )
        {
            if( NS(Multipole_allow_conversion)( diff, lhs ) )
            {
                status = NS(Multipole_convert)( diff, lhs );
            }

            if( ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) &&
                ( rhs != SIXTRL_NULLPTR ) )
            {
                status  = NS(Multipole_subtract_from_length)( diff,
                                    NS(Multipole_length)( rhs ) );

                status |= NS(Multipole_subtract_from_hxl)( diff,
                                    NS(Multipole_hxl)( rhs ) );

                status |= NS(Multipole_subtract_from_hyl)( diff,
                                    NS(Multipole_hyl)( rhs ) );

                status |= NS(Multipole_subtract_from_bal)( diff,
                                    NS(Multipole_const_bal_begin)( rhs ) );
            }
        }
        else if( rhs != SIXTRL_NULLPTR )
        {
            if( NS(Multipole_allow_conversion)( diff, rhs ) )
            {
                status = NS(Multipole_convert)( diff, rhs );
            }

            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status  = NS(Multipole_change_sign_length)( diff );
                status |= NS(Multipole_change_sign_hxl)( diff );
                status |= NS(Multipole_change_sign_hxl)( diff );
                status |= NS(Multipole_change_sign_bal)( diff );
            }
        }
    }

    return status;
}

SIXTRL_INLINE int NS(Multipole_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    int cmp_result = -1;

    if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
    {
        cmp_result = NS(Type_value_comp_result_int64)(
            NS(Multipole_order)( lhs ), NS(Multipole_order)( rhs ) );

        if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
                NS(Multipole_length)( lhs ), NS(Multipole_length)( rhs ) );

        if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
                NS(Multipole_hxl)( lhs ), NS(Multipole_hxl)( rhs ) );

        if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
                NS(Multipole_hyl)( lhs ), NS(Multipole_hyl)( rhs ) );

        if( cmp_result == 0 )
            cmp_result = NS(Type_value_comp_result_for_range)(
                NS(Multipole_const_bal_begin)( lhs ),
                NS(Multipole_const_bal_end)( lhs ),
                NS(Multipole_const_bal_begin)( rhs ) );
    }
    else if( lhs != SIXTRL_NULLPTR )
    {
        cmp_result = +1;
    }

    return cmp_result;
}

SIXTRL_INLINE int NS(Multipole_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs,
    NS(be_real_t) const rel_tol, NS(be_real_t) const abs_tol ) SIXTRL_NOEXCEPT
{
    int cmp_result = -1;

    if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
    {
        cmp_result = NS(Type_value_comp_result_int64)(
            NS(Multipole_order)( lhs ), NS(Multipole_order)( rhs ) );

        if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
                NS(Multipole_length)( lhs ), NS(Multipole_length)( rhs ),
                    rel_tol, abs_tol );

        if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
                NS(Multipole_hxl)( lhs ), NS(Multipole_hxl)( rhs ),
                    rel_tol, abs_tol );

        if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
                NS(Multipole_hyl)( lhs ), NS(Multipole_hyl)( rhs ),
                    rel_tol, abs_tol );

        if( cmp_result == 0 )
            cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
                NS(Multipole_const_bal_begin)( lhs ),
                NS(Multipole_const_bal_end)( lhs ),
                NS(Multipole_const_bal_begin)( rhs ), rel_tol, abs_tol );
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
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_COMPARE_H__*/
