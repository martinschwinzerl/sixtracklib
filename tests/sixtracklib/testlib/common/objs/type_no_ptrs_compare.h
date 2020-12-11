#ifndef SIXTRACKLIB_TESTLIB_COMMON_OBJS_TYPE_NO_PTRS_COMP_H__
#define SIXTRACKLIB_TESTLIB_COMMON_OBJS_TYPE_NO_PTRS_COMP_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_api.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_convert.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_derived_api.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/math_arithmetic.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< LhsT >() ||
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename TypeNoPtrsTraits< RhsT >::real_t,
            typename TypeNoPtrsTraits< DiffT >::real_t >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename TypeNoPtrsTraits< LhsT >::real_t,
            typename TypeNoPtrsTraits< DiffT >::real_t >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename TypeNoPtrsTraits< RhsT >::int_t,
            typename TypeNoPtrsTraits< DiffT >::int_t >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename TypeNoPtrsTraits< RhsT >::int_t,
            typename TypeNoPtrsTraits< DiffT >::int_t >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename TypeNoPtrsTraits< RhsT >::uchar_t,
            typename TypeNoPtrsTraits< DiffT >::uchar_t >() ||
        !SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename TypeNoPtrsTraits< RhsT >::uchar_t,
            typename TypeNoPtrsTraits< DiffT >::uchar_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_diff(
        SIXTRL_BUFFER_DATAPTR_DEC DiffT* SIXTRL_RESTRICT /* diff */,
        SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT /* lhs */,
        SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT /* rhs */
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< LhsT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< DiffT >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename TypeNoPtrsTraits< RhsT >::real_t,
            typename TypeNoPtrsTraits< DiffT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename TypeNoPtrsTraits< LhsT >::real_t,
            typename TypeNoPtrsTraits< DiffT >::real_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename TypeNoPtrsTraits< RhsT >::int_t,
            typename TypeNoPtrsTraits< DiffT >::int_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename TypeNoPtrsTraits< RhsT >::int_t,
            typename TypeNoPtrsTraits< DiffT >::int_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename TypeNoPtrsTraits< RhsT >::uchar_t,
            typename TypeNoPtrsTraits< DiffT >::uchar_t >() &&
        SIXTRL_CXX_NAMESPACE::Types_same_allow_arithmetic<
            typename TypeNoPtrsTraits< RhsT >::uchar_t,
            typename TypeNoPtrsTraits< DiffT >::uchar_t >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_diff(
        SIXTRL_BUFFER_DATAPTR_DEC DiffT* SIXTRL_RESTRICT diff,
        SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
        SIXTRL_CXX_NAMESPACE::store_backend_t const diff_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const lhs_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const rhs_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( diff != SIXTRL_NULLPTR )
        {
            if( ( lhs  != SIXTRL_NULLPTR ) &&
                ( st::tests::TypeNoPtrs_allow_conversion(
                         diff, lhs, lhs_store_be, diff_store_be ) ) )
            {
                status = st::tests::TypeNoPtrs_convert(
                    diff, lhs, lhs_store_be, diff_store_be );
            }

            if( rhs  != SIXTRL_NULLPTR )
            {
                SIXTRL_ASSERT( st::tests::TypeNoPtrs_c_length( diff ) <=
                               st::tests::TypeNoPtrs_c_length( rhs ) );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status  = st::tests::TypeNoPtrs_subtract_from_a(
                        diff, st::tests::TypeNoPtrs_a( rhs ) );

                    status |= st::tests::TypeNoPtrs_subtract_from_b(
                        diff, st::tests::TypeNoPtrs_b( rhs ) );

                    status |= st::tests::TypeNoPtrs_subtract_from_c(
                        diff, st::tests::TypeNoPtrs_const_c_begin( rhs ) );
                }
                else if( st::tests::TypeNoPtrs_allow_conversion(
                        diff, rhs, rhs_store_be, diff_store_be ) )
                {
                    status = st::tests::TypeNoPtrs_convert(
                        diff, rhs, rhs_store_be, diff_store_be );

                    status |= st::tests::TypeNoPtrs_change_sign_a( diff );
                    status |= st::tests::TypeNoPtrs_change_sign_b( diff );
                    status |= st::tests::TypeNoPtrs_change_sign_c( diff );
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    template< class LhsT, class RhsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< LhsT >() ||
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< RhsT >(),
        typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            LhsT >::cmp_result_t >::type
    TypeNoPtrs_compare(
        SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT /* lhs */,
        SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT /* rhs */
    ) SIXTRL_NOEXCEPT
    {
        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            LhsT >::cmp_result_t cmp_result_t;
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    template< class LhsT, class RhsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< LhsT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< RhsT >(),
        typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            LhsT >::cmp_result_t >::type
    TypeNoPtrs_compare(
        SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef st::tests::TypeNoPtrsTraits< LhsT > lhs_traits_t;
        typedef st::tests::TypeNoPtrsTraits< RhsT > rhs_traits_t;

        typedef typename lhs_traits_t::real_t  lhs_real_t;
        typedef typename lhs_traits_t::int_t   lhs_int_t;
        typedef typename lhs_traits_t::uchar_t lhs_uchar_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename st::TypeMethodParamTraits<
            lhs_uchar_t >::const_pointer lhs_uchar_ptr_t;

        typedef typename rhs_traits_t::real_t  rhs_real_t;
        typedef typename rhs_traits_t::int_t   rhs_int_t;
        typedef typename rhs_traits_t::uchar_t rhs_uchar_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename st::TypeMethodParamTraits<
            rhs_uchar_t >::const_pointer rhs_uchar_ptr_t;

        typedef typename st::ObjDataLogicTypeTraits<
                    LhsT >::cmp_result_t cmp_result_t;

        typedef TypeCompResultTraits< cmp_result_t > cmp_traits_t;
        cmp_result_t result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
        {
            result = st::Type_value_comp_result< lhs_real_t, cmp_result_t,
                rhs_real_t >( st::tests::TypeNoPtrs_a( lhs ),
                              st::tests::TypeNoPtrs_a( rhs ) );

            if( result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            {
                result = st::Type_value_comp_result<
                    lhs_int_t, cmp_result_t, rhs_int_t >(
                        st::tests::TypeNoPtrs_b( lhs ),
                        st::tests::TypeNoPtrs_b( rhs ) );
            }

            if( result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            {
                result = st::Type_value_comp_result<
                    st::arch_size_t, cmp_result_t, st::arch_size_t >(
                        st::tests::TypeNoPtrs_c_length( lhs ),
                        st::tests::TypeNoPtrs_c_length( rhs ) );
            }

            if( result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            {
                result = st::Type_value_comp_result_for_range<
                    lhs_uchar_ptr_t, cmp_result_t, rhs_uchar_ptr_t >(
                        st::tests::TypeNoPtrs_const_c_begin( lhs ),
                        st::tests::TypeNoPtrs_const_c_end( lhs ),
                        st::tests::TypeNoPtrs_const_c_begin( rhs ) );
            }
        }
        else if( lhs != SIXTRL_NULLPTR )
        {
            result = cmp_traits_t::CMP_LHS_LARGER_RHS;
        }

        return result;
    }

    /* --------------------------------------------------------------------- */

    template< class LhsT, class RhsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< LhsT >() ||
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< RhsT >(),
        typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            LhsT >::cmp_result_t >::type
    TypeNoPtrs_compare(
        SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT /* lhs */,
        SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT /* rhs */,
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< RhsT >::real_t
                >::const_argument_type /*real_rel_tol*/,
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< RhsT >::real_t
                >::const_argument_type /*real_abs_tol*/ ) SIXTRL_NOEXCEPT
    {
        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            LhsT >::cmp_result_t cmp_result_t;
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    template< class LhsT, class RhsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< LhsT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< RhsT >(),
        typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            LhsT >::cmp_result_t >::type
    TypeNoPtrs_compare_with_tolerances(
        SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< RhsT >::real_t
                >::const_argument_type real_rel_tol,
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< RhsT >::real_t
                >::const_argument_type real_abs_tol ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef st::tests::TypeNoPtrsTraits< LhsT > lhs_traits_t;
        typedef st::tests::TypeNoPtrsTraits< RhsT > rhs_traits_t;

        typedef typename lhs_traits_t::real_t  lhs_real_t;
        typedef typename lhs_traits_t::int_t   lhs_int_t;
        typedef typename lhs_traits_t::uchar_t lhs_uchar_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename st::TypeMethodParamTraits<
            lhs_uchar_t >::const_pointer lhs_uchar_ptr_t;

        typedef typename rhs_traits_t::real_t  rhs_real_t;
        typedef typename rhs_traits_t::int_t   rhs_int_t;
        typedef typename rhs_traits_t::uchar_t rhs_uchar_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC typename st::TypeMethodParamTraits<
            rhs_uchar_t >::const_pointer rhs_uchar_ptr_t;

        typedef typename st::ObjDataLogicTypeTraits<
                    LhsT >::cmp_result_t cmp_result_t;

        typedef TypeCompResultTraits< cmp_result_t > cmp_traits_t;
        cmp_result_t result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
        {
            result = st::Type_value_comp_result< lhs_real_t, cmp_result_t,
                rhs_real_t >( st::tests::TypeNoPtrs_a( lhs ),
                              st::tests::TypeNoPtrs_a( rhs ),
                              real_rel_tol, real_abs_tol );

            if( result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            {
                result = st::Type_value_comp_result<
                    lhs_int_t, cmp_result_t, rhs_int_t >(
                        st::tests::TypeNoPtrs_b( lhs ),
                        st::tests::TypeNoPtrs_b( rhs ) );
            }

            if( result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            {
                result = st::Type_value_comp_result<
                    st::arch_size_t, cmp_result_t, st::arch_size_t >(
                        st::tests::TypeNoPtrs_c_length( lhs ),
                        st::tests::TypeNoPtrs_c_length( rhs ) );
            }

            if( result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            {
                result = st::Type_value_comp_result_for_range<
                    lhs_uchar_ptr_t, cmp_result_t, rhs_uchar_ptr_t >(
                        st::tests::TypeNoPtrs_const_c_begin( lhs ),
                        st::tests::TypeNoPtrs_const_c_end( lhs ),
                        st::tests::TypeNoPtrs_const_c_begin( rhs ) );
            }
        }
        else if( lhs != SIXTRL_NULLPTR )
        {
            result = cmp_traits_t::CMP_LHS_LARGER_RHS;
        }

        return result;
    }

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++ */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/type_no_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs.hpp"
#endif /* C++ */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* ******************************************************************** */
    /* Lhs: NS(TypeNoPtrs) */

    template< class RhsT >
    struct ObjDataComparisonHelper< ::NS(TypeNoPtrs), RhsT, typename
        SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits< ::NS(TypeNoPtrs)
            >::cmp_result_t, typename std::enable_if<
                SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< RhsT >(),
                void >::type >
    {
        typedef ::NS(TypeNoPtrs) LhsT;
        typedef typename TypeCompLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                LhsT >::real_t >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_compare( lhs, rhs );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                    LhsT >::real_t >::const_argument_type real_rel_tol,
            typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                    LhsT >::real_t >::const_argument_type real_abs_tol )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeNoPtrs_compare_with_tolerances(
                lhs, rhs, real_rel_tol, real_abs_tol );
        }
    };

    template< class RhsT, class DiffT >
    struct ObjDataDiffHelper< ::NS(TypeNoPtrs), RhsT, DiffT,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< DiffT >(),
            void >::type >
    {
        typedef ::NS(TypeNoPtrs) LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        calculate(
            SIXTRL_BUFFER_DATAPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_diff(
                diff, lhs, rhs );
        }
    };

    /* ******************************************************************** */
    /* Lhs: NS(TypeNoPtrs) */

    template< class R, class I, class U,
              SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t IAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t UAlign, class RhsT >
    struct ObjDataComparisonHelper< SIXTRL_CXX_NAMESPACE::tests::TTypeNoPtrs<
        R, I, U, RAlign, IAlign, UAlign >, RhsT, typename
        SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            SIXTRL_CXX_NAMESPACE::tests::TTypeNoPtrs< R, I, U, RAlign, IAlign,
                UAlign > >::cmp_result_t, typename std::enable_if<
                SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< RhsT >(),
                void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::TTypeNoPtrs< R, I, U, RAlign,
                IAlign, UAlign > LhsT;

        typedef typename TypeCompLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                LhsT >::real_t >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_compare( lhs, rhs );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                    LhsT >::real_t >::const_argument_type real_rel_tol,
            typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                    LhsT >::real_t >::const_argument_type real_abs_tol )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeNoPtrs_compare_with_tolerances(
                lhs, rhs, real_rel_tol, real_abs_tol );
        }
    };

    template< class R, class I, class U,
              SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t IAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t UAlign,
              class RhsT, class DiffT >
    struct ObjDataDiffHelper< SIXTRL_CXX_NAMESPACE::tests::TTypeNoPtrs<
            R, I, U, RAlign, IAlign, UAlign >, RhsT, DiffT,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< DiffT >(),
            void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::TTypeNoPtrs< R, I, U, RAlign,
                    IAlign, UAlign > LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
            SIXTRL_CXX_NAMESPACE::arch_status_t calculate(
            SIXTRL_BUFFER_DATAPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::tests::TypeNoPtrs_diff( diff, lhs, rhs );
        }
    };

} /* namespace: SIXTRL_CXX_NAMESPACE */

template< class LhsT, class RhsT, class DiffT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_diff)(
    SIXTRL_BUFFER_DATAPTR_DEC DiffT* SIXTRL_RESTRICT diff,
    SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
    SIXTRL_CXX_NAMESPACE::store_backend_t const diff_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const lhs_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const rhs_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_diff(
        diff, lhs, rhs, diff_store_be, lhs_store_be, rhs_store_be );
}

template< class LhsT, class RhsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits< LhsT >::cmp_result_t
NS(TypeNoPtrs_compare)(
    SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_compare( lhs, rhs );
}

template< class LhsT, class RhsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename
    SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits< LhsT >::cmp_result_t
NS(TypeNoPtrs_compare_with_tolerances)(
    SIXTRL_BUFFER_DATAPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_DATAPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< RhsT >::real_t
            >::const_argument_type real_rel_tol,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< RhsT >::real_t
            >::const_argument_type real_abs_tol ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_compare_with_tolerances(
        lhs, rhs, real_rel_tol, real_abs_tol );
}

#endif /* SIXTRL_CXX_NAMESPACE */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_diff)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT diff,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT rhs,
    NS(store_backend_t) const diff_store_be,
    NS(store_backend_t) const lhs_store_be,
    NS(store_backend_t) const rhs_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(TypeNoPtrs_compare)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(TypeNoPtrs_compare_with_tolerances)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT rhs,
    NS(test_objs_real_t) const real_rel_tol,
    NS(test_objs_real_t) const real_abs_tol ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */


#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_diff)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT diff,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT rhs,
    NS(store_backend_t) const diff_store_be,
    NS(store_backend_t) const lhs_store_be,
    NS(store_backend_t) const rhs_store_be ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( diff != SIXTRL_NULLPTR )
    {
        if( ( lhs  != SIXTRL_NULLPTR ) &&
            ( NS(TypeNoPtrs_allow_conversion)(
                     diff, lhs, lhs_store_be, diff_store_be ) ) )
        {
            status = NS(TypeNoPtrs_convert)(
                diff, lhs, lhs_store_be, diff_store_be );
        }

        if( ( rhs  != SIXTRL_NULLPTR ) &&
            ( NS(TypeNoPtrs_c_length)( diff ) <=
              NS(TypeNoPtrs_c_length)( rhs ) ) )
        {
            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status  = NS(TypeNoPtrs_subtract_from_a)(
                                diff, NS(TypeNoPtrs_a)( rhs ) );

                status |= NS(TypeNoPtrs_subtract_from_b)(
                                diff, NS(TypeNoPtrs_b)( rhs ) );

                status |= NS(TypeNoPtrs_subtract_from_c)(
                                diff, NS(TypeNoPtrs_const_c_begin)( rhs ) );
            }
            else if( NS(TypeNoPtrs_allow_conversion)(
                    diff, rhs, rhs_store_be, diff_store_be ) )
            {
                status = NS(TypeNoPtrs_convert)(
                    diff, rhs, rhs_store_be, diff_store_be );

                status |= NS(TypeNoPtrs_change_sign_a)( diff );
                status |= NS(TypeNoPtrs_change_sign_b)( diff );
                status |= NS(TypeNoPtrs_change_sign_c)( diff );
            }
        }
    }

    return status;
}

SIXTRL_INLINE int NS(TypeNoPtrs_compare)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    int result = +1;

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = NS(Type_value_comp_result)(
                    NS(TypeNoPtrs_a)( lhs ), NS(TypeNoPtrs_a)( rhs ) );

        if( ( result == 0 ) &&
            ( NS(TypeNoPtrs_b)( lhs ) != NS(TypeNoPtrs_b)( rhs ) ) )
        {
            result = ( NS(TypeNoPtrs_b)( lhs ) < NS(TypeNoPtrs_b)( rhs ) )
                ? -1 : +1;
        }

        if( ( result == 0 ) && ( NS(TypeNoPtrs_c_length)( lhs ) !=
              NS(TypeNoPtrs_c_length)( rhs ) ) )
        {
            result = ( NS(TypeNoPtrs_c_length)( lhs ) <
                       NS(TypeNoPtrs_c_length)( rhs ) ) ? -1 : +1;
        }

        if( result == 0 )
        {
            SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const* lhs_it =
                NS(TypeNoPtrs_const_c_begin)( lhs );

            SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const* lhs_end =
                NS(TypeNoPtrs_const_c_end)( lhs );

            SIXTRL_BUFFER_ARGPTR_DEC NS(test_objs_uchar_t) const* rhs_it =
                NS(TypeNoPtrs_const_c_begin)( rhs );

            SIXTRL_ASSERT( lhs_it  != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( lhs_end != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( rhs_it  != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( rhs_it  != lhs_it );

            while( ( result == 0 ) && ( lhs_it != lhs_end ) )
            {
                if( *lhs_it != *rhs_it )
                {
                    result = ( *lhs_it < *rhs_it ) ? -1 : +1;
                }

                ++lhs_it;
                ++rhs_it;
            }
        }
    }
    else if( lhs != SIXTRL_NULLPTR )
    {
        result = -1;
    }

    return result;
}

SIXTRL_INLINE int NS(TypeNoPtrs_compare_with_tolerances)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TypeNoPtrs) *const SIXTRL_RESTRICT rhs,
    NS(test_objs_real_t) const real_rel_tol,
    NS(test_objs_real_t) const real_abs_tol ) SIXTRL_NOEXCEPT
{
    int result = +1;

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = NS(Type_value_comp_result_with_tolerances)(
                    NS(TypeNoPtrs_a)( lhs ), NS(TypeNoPtrs_a)( rhs ),
                        real_rel_tol, real_abs_tol );

        if( ( result == 0 ) &&
            ( NS(TypeNoPtrs_b)( lhs ) != NS(TypeNoPtrs_b)( rhs ) ) )
        {
            result = ( NS(TypeNoPtrs_b)( lhs ) < NS(TypeNoPtrs_b)( rhs ) )
                ? -1 : +1;
        }

        if( ( result == 0 ) && ( NS(TypeNoPtrs_c_length)( lhs ) !=
              NS(TypeNoPtrs_c_length)( rhs ) ) )
        {
            result = ( NS(TypeNoPtrs_c_length)( lhs ) <
                       NS(TypeNoPtrs_c_length)( rhs ) ) ? -1 : +1;
        }

        if( result == 0 )
        {
            SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const* lhs_it =
                NS(TypeNoPtrs_const_c_begin)( lhs );

            SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const* lhs_end =
                NS(TypeNoPtrs_const_c_end)( lhs );

            SIXTRL_BUFFER_ARGPTR_DEC NS(test_objs_uchar_t) const* rhs_it =
                NS(TypeNoPtrs_const_c_begin)( rhs );

            SIXTRL_ASSERT( lhs_it  != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( lhs_end != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( rhs_it  != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( rhs_it  != lhs_it );

            while( ( result == 0 ) && ( lhs_it != lhs_end ) )
            {
                if( *lhs_it != *rhs_it )
                {
                    result = ( *lhs_it < *rhs_it ) ? -1 : +1;
                }

                ++lhs_it;
                ++rhs_it;
            }
        }
    }
    else if( lhs != SIXTRL_NULLPTR )
    {
        result = -1;
    }

    return result;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_OBJS_TYPE_NO_PTRS_COMP_H__ */
