#ifndef SIXTRACKLIB_TESTLIB_COMMON_OBJS_TYPE_NO_PTRS_DERIVED_API_H__
#define SIXTRACKLIB_TESTLIB_COMMON_OBJS_TYPE_NO_PTRS_DERIVED_API_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/type_no_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_api.h"
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
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_add_to_a(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT /* obj */,
        RealArg /* d_a */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_subtract_from_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealArg /* d_a */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_scale_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, RealArg /* factor */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_change_sign_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /*obj*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_add_to_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
                         RealArg d_a )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return SIXTRL_CXX_NAMESPACE::Math_arithmetic_add_to< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeT >::real_t,
                RealArg >( obj->a, d_a );
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_subtract_from_a(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg d_a )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return SIXTRL_CXX_NAMESPACE::Math_arithmetic_subtract_from< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeT >::real_t,
                RealArg >( obj->a, d_a );
    }

    template< class TypeT, typename RealArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_scale_a(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg factor )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return SIXTRL_CXX_NAMESPACE::Math_arithmetic_scale< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeT >::real_t,
                RealArg >( obj->a, factor );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_change_sign_a( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return SIXTRL_CXX_NAMESPACE::Math_arithmetic_change_sign< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeT
                >::real_t >( obj->a );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* b */

    template< class TypeT, typename IntArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_add_to_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT /* obj */,
        IntArg /* d_b */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename IntArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_subtract_from_b( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, IntArg /* d_b */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename IntArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_scale_b( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, IntArg /* factor */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_change_sign_b( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /*obj*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class TypeT, typename IntArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_add_to_b( SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
                         IntArg d_b )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return SIXTRL_CXX_NAMESPACE::Math_arithmetic_add_to< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeT >::int_t,
                IntArg >( obj->b, d_b );
    }

    template< class TypeT, typename IntArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_subtract_from_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, IntArg d_b )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return SIXTRL_CXX_NAMESPACE::Math_arithmetic_subtract_from< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeT >::int_t,
                IntArg >( obj->b, d_b );
    }

    template< class TypeT, typename IntArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_scale_b(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, IntArg factor )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return SIXTRL_CXX_NAMESPACE::Math_arithmetic_scale< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeT >::int_t,
                IntArg >( obj->b, factor );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_change_sign_b( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj )
    {
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return SIXTRL_CXX_NAMESPACE::Math_arithmetic_change_sign< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits< TypeT
                >::int_t >( obj->b );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* c */

    template< class TypeT, typename UCharIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_add_to_c(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT /* obj */,
        UCharIter /* d_c_begin */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename UCharIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_subtract_from_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, UCharIter /* d_c_begin */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename UCharIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_scale_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /* obj */, UCharIter /* factors_begin */ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_change_sign_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /*obj*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class TypeT, typename UCharIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_add_to_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
                         UCharIter d_c_begin )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return st::Math_arithmetic_add_to( st::tests::TypeNoPtrs_c_begin( obj ),
            st::tests::TypeNoPtrs_c_end( obj ), d_c_begin );
    }

    template< class TypeT, typename UCharIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_subtract_from_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj, UCharIter d_c_begin )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return st::Math_arithmetic_subtract_from(
            st::tests::TypeNoPtrs_c_begin( obj ),
            st::tests::TypeNoPtrs_c_end( obj ), d_c_begin );
    }

    template< class TypeT, typename UCharIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_scale_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
                        UCharIter factors_begin )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return st::Math_arithmetic_add_to( st::tests::TypeNoPtrs_c_begin( obj ),
            st::tests::TypeNoPtrs_c_end( obj ), factors_begin );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >() &&
        SIXTRL_CXX_NAMESPACE::TypeStoreTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeT >::uchar_t >::is_signed,
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_change_sign_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        return st::Math_arithmetic_change_sign(
            st::tests::TypeNoPtrs_c_begin( obj ),
            st::tests::TypeNoPtrs_c_end( obj ) );
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeT >() &&
        !SIXTRL_CXX_NAMESPACE::TypeStoreTraits< typename
            SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                TypeT >::uchar_t >::is_signed,
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeNoPtrs_change_sign_c( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /*obj*/ )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_add_to_a)( SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
                         RealArg d_a )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_add_to_a( obj, d_a );
}

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_subtract_from_a)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg d_a )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_subtract_from_a( obj, d_a );
}

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_scale_a)( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
    SIXTRL_RESTRICT obj, RealArg factor )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_scale_a( obj, factor );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_change_sign_a)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_change_sign_a( obj );
}

/* b */

template< class TypeT, typename IntArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_add_to_b)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, IntArg d_b )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_add_to_b( obj, d_b );
}

template< class TypeT, typename IntArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_subtract_from_b)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, IntArg d_b )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_subtract_from_b( obj, d_b );
}

template< class TypeT, typename IntArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_scale_b)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, IntArg factor )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_scale_b( obj, factor );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_change_sign_b)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_change_sign_b( obj );
}

/* c */

template< class TypeT, typename UCharIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_add_to_c)( SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    UCharIter d_c_begin ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_add_to_c(
        obj, d_c_begin );
}

template< class TypeT, typename UCharIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_subtract_from_c)( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
    SIXTRL_RESTRICT obj, UCharIter d_c_begin ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_subtract_from_c(
        obj, d_c_begin );
}

template< class TypeT, typename UCharIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_scale_c)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    UCharIter factors_begin ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_scale_c( obj, factors_begin );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_change_sign_c)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_change_sign_c( obj );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_add_to_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const d_a ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_subtract_from_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const d_a ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_scale_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const factor ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_change_sign_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

/* b */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_add_to_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_int_t) const d_b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_subtract_from_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_int_t) const d_b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_scale_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_int_t) const factor ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_change_sign_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT;

/* c */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_add_to_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const* d_c_it
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_subtract_from_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const* d_c_it
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_scale_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const* factor_it
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_change_sign_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_add_to_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const d_a ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a += d_a;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_subtract_from_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const d_a ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a -= d_a;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_scale_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const factor ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a *= factor;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_change_sign_a)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a = -( obj->a );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* b */

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_add_to_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_int_t) const d_b ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->b += d_b;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_subtract_from_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_int_t) const d_b ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->b -= d_b;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_scale_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_int_t) const factor ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->b *= factor;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_change_sign_b)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->b = -( obj->b );
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* c */

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_add_to_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const* d_c_it
) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t)* it =
        NS(TypeNoPtrs_c_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t)* end =
        NS(TypeNoPtrs_c_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( d_c_it != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it, ++d_c_it ) *it += *d_c_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_subtract_from_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const* d_c_it
) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t)* it =
        NS(TypeNoPtrs_c_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t)* end =
        NS(TypeNoPtrs_c_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( d_c_it != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it, ++d_c_it ) *it -= *d_c_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_scale_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const* factor_it
) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t)* it =
        NS(TypeNoPtrs_c_begin)( obj );

    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t)* end =
        NS(TypeNoPtrs_c_end)( obj );

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( factor_it != SIXTRL_NULLPTR ) )
    {
        for( ; it != end ; ++it, ++factor_it ) *it *= *factor_it;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_change_sign_c)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    ( void )obj;
    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_OBJS_TYPE_NO_PTRS_DERIVED_API_H__ */
