#ifndef SIXTRACKLIB_TESTLIB_COMMON_OBJS_TYPE_CONST_NUM_PTRS_DERIVED_API_H__
#define SIXTRACKLIB_TESTLIB_COMMON_OBJS_TYPE_CONST_NUM_PTRS_DERIVED_API_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_api.h"
    #include "sixtracklib/common/internal/math_arithmetic.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    /* a: */

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_add_to_a(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT /* obj */,
        RealArg /* d_a */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_subtract_from_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealArg /* d_a */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_scale_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealArg /* factor */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_change_sign_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /*obj*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_add_to_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
                         RealArg d_a )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return SIXTRL_CXX_NAMESPACE::Math_arithmetic_add_to< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t, RealArg >( obj->a, d_a );
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_subtract_from_a(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg d_a )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return SIXTRL_CXX_NAMESPACE::Math_arithmetic_subtract_from< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t, RealArg >( obj->a, d_a );
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_scale_a(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg factor )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return SIXTRL_CXX_NAMESPACE::Math_arithmetic_scale< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t, RealArg >( obj->a, factor );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_change_sign_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return SIXTRL_CXX_NAMESPACE::Math_arithmetic_change_sign< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                TypeT >::real_t >( obj->a );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* b */

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_add_to_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT /* obj */,
        RealIter /* d_b_begin */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_subtract_from_b( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealIter /* d_b_begin */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_scale_b( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealIter /* factors_begin */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_change_sign_b( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /*obj*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_add_to_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
        RealIter d_b_begin )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return st::Math_arithmetic_add_to(
            st::tests::TypeConstNumPtrs_b_begin( obj ),
            st::tests::TypeConstNumPtrs_b_end( obj ), d_b_begin );
    }

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_subtract_from_b( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, RealIter d_b_begin )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return st::Math_arithmetic_subtract_from(
            st::tests::TypeConstNumPtrs_b_begin( obj ),
            st::tests::TypeConstNumPtrs_b_end( obj ), d_b_begin );
    }

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_scale_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
        RealIter factors_begin )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return st::Math_arithmetic_add_to(
            st::tests::TypeConstNumPtrs_b_begin( obj ),
            st::tests::TypeConstNumPtrs_b_end( obj ), factors_begin );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_change_sign_b( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return st::Math_arithmetic_change_sign(
            st::tests::TypeConstNumPtrs_b_begin( obj ),
            st::tests::TypeConstNumPtrs_b_end( obj ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* c */

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_add_to_c(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT /* obj */,
        RealIter /* d_c_begin */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_subtract_from_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealIter /* d_c_begin */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_scale_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealIter /* factors_begin */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_change_sign_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /*obj*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_add_to_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
                         RealIter d_c_begin )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return st::Math_arithmetic_add_to(
            st::tests::TypeConstNumPtrs_c_begin( obj ),
            st::tests::TypeConstNumPtrs_c_end( obj ), d_c_begin );
    }

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_subtract_from_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, RealIter d_c_begin )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return st::Math_arithmetic_subtract_from(
            st::tests::TypeConstNumPtrs_c_begin( obj ),
            st::tests::TypeConstNumPtrs_c_end( obj ), d_c_begin );
    }

    template< class TypeT, typename RealIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_scale_c(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
        RealIter factors_begin )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return st::Math_arithmetic_add_to(
            st::tests::TypeConstNumPtrs_c_begin( obj ),
            st::tests::TypeConstNumPtrs_c_end( obj ), factors_begin );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_change_sign_c(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return st::Math_arithmetic_change_sign(
            st::tests::TypeConstNumPtrs_c_begin( obj ),
            st::tests::TypeConstNumPtrs_c_end( obj ) );
    }

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_add_to_a)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg d_a )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_add_to_a( obj, d_a );
}

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_subtract_from_a)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg d_a )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_subtract_from_a( obj, d_a );
}

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_scale_a)( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
    SIXTRL_RESTRICT obj, RealArg factor )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_scale_a( obj, factor );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_change_sign_a)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_change_sign_a( obj );
}

/* b */

template< class TypeT, typename RealIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_add_to_b)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    RealIter d_b_begin ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_add_to_b( obj, d_b_begin );
}

template< class TypeT, typename RealIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_subtract_from_b)( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
    SIXTRL_RESTRICT obj, RealIter d_b_begin ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_subtract_from_b( obj, d_b_begin );
}

template< class TypeT, typename RealIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_scale_b)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    RealIter factors_begin ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_scale_b( obj, factors_begin );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_change_sign_b)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_change_sign_b( obj );
}

/* c */

template< class TypeT, typename RealIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_add_to_c)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    RealIter d_c_begin ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_add_to_c( obj, d_c_begin );
}

template< class TypeT, typename RealIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_subtract_from_c)( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
    SIXTRL_RESTRICT obj, RealIter d_c_begin ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_subtract_from_c( obj, d_c_begin );
}

template< class TypeT, typename RealIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_scale_c)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    RealIter factors_begin ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_scale_c( obj, factors_begin );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_change_sign_c)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::tests::TypeConstNumPtrs_change_sign_c( obj );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_add_to_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const d_a ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_subtract_from_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const d_a ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_scale_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const factor ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_change_sign_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

/* b */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_add_to_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT b_values_begin ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_subtract_from_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT b_values_begin ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_scale_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT b_values_begin ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_change_sign_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT;

/* c */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_add_to_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT d_c_it ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_subtract_from_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT d_c_it ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_scale_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT factors_begin ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_change_sign_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_add_to_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const d_a ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a += d_a;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_subtract_from_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const d_a ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a -= d_a;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_scale_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const factor ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a *= factor;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_change_sign_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a = -( obj->a );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* b */

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_add_to_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT in_it ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* it =
        NS(TypeConstNumPtrs_b_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* end =
        NS(TypeConstNumPtrs_b_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( in_it != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it, ++in_it ) *it += *in_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_subtract_from_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT in_it ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* it =
        NS(TypeConstNumPtrs_b_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* end =
        NS(TypeConstNumPtrs_b_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( in_it != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it, ++in_it ) *it -= *in_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_scale_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT in_it) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* it =
        NS(TypeConstNumPtrs_b_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* end =
        NS(TypeConstNumPtrs_b_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( in_it != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it, ++in_it ) *it *= *in_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_change_sign_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* it =
        NS(TypeConstNumPtrs_b_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* end =
        NS(TypeConstNumPtrs_b_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it ) *it = -( *it );
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

/* c */

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_add_to_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT in_it ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* it =
        NS(TypeConstNumPtrs_c_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* end =
        NS(TypeConstNumPtrs_c_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( in_it != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it, ++in_it ) *it += *in_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_subtract_from_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT in_it ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* it =
        NS(TypeConstNumPtrs_c_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* end =
        NS(TypeConstNumPtrs_c_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( in_it != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it, ++in_it ) *it -= *in_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_scale_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t) const*
        SIXTRL_RESTRICT in_it) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* it =
        NS(TypeConstNumPtrs_c_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* end =
        NS(TypeConstNumPtrs_c_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( in_it != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it, ++in_it ) *it *= *in_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_change_sign_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* it =
        NS(TypeConstNumPtrs_c_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_real_t)* end =
        NS(TypeConstNumPtrs_c_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it ) *it = -( *it );
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_OBJS_TYPE_CONST_NUM_PTRS_DERIVED_API_H__ */
