#ifndef SIXTRACKLIB_COMMON_INTERNAL_TYPE_ARITHMETIC_HELPERS_H_
#define SIXTRACKLIB_COMMON_INTERNAL_TYPE_ARITHMETIC_HELPERS_H_

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && ( defined( __cplusplus ) )
    #include <cstdlib>
    #include <cstdint>
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_TYPE NS(Type_add_real_type)(
    SIXTRL_REAL_TYPE const lhs, SIXTRL_REAL_TYPE const rhs ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_TYPE NS(Type_subtract_real_type)(
    SIXTRL_REAL_TYPE const lhs, SIXTRL_REAL_TYPE const rhs ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_TYPE NS(Type_multiply_real_type)(
    SIXTRL_REAL_TYPE const lhs, SIXTRL_REAL_TYPE const rhs ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_TYPE NS(Type_divide_real_type)(
    SIXTRL_REAL_TYPE const lhs, SIXTRL_REAL_TYPE const rhs ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Type_add_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT result,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Type_add_inplace_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Type_subtract_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT result,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Type_subtract_inplace_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Type_multiply_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT result,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Type_multiply_inplace_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Type_divide_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT result,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Type_divide_inplace_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Type_add_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT result,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Type_add_inplace_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Type_subtract_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT result,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Type_subtract_inplace_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Type_multiply_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT result,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Type_multiply_inplace_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Type_divide_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT result,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Type_divide_inplace_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Type_add_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT result,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Type_add_inplace_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Type_subtract_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT result,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Type_subtract_inplace_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Type_multiply_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT result,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Type_multiply_inplace_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Type_divide_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT result,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Type_divide_inplace_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_begin,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_begin
) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* ******     Implementation of Inline Methods and Functions          ****** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_INLINE SIXTRL_REAL_TYPE NS(Type_add_real_type)(
    SIXTRL_REAL_TYPE const lhs, SIXTRL_REAL_TYPE const rhs ) SIXTRL_NOEXCEPT {
    return lhs + rhs; }

SIXTRL_INLINE SIXTRL_REAL_TYPE NS(Type_subtract_real_type)(
    SIXTRL_REAL_TYPE const lhs, SIXTRL_REAL_TYPE const rhs ) SIXTRL_NOEXCEPT {
    return lhs - rhs; }

SIXTRL_INLINE SIXTRL_REAL_TYPE NS(Type_multiply_real_type)(
    SIXTRL_REAL_TYPE const lhs, SIXTRL_REAL_TYPE const rhs ) SIXTRL_NOEXCEPT {
    return lhs * rhs; }

SIXTRL_INLINE SIXTRL_REAL_TYPE NS(Type_divide_real_type)(
    SIXTRL_REAL_TYPE const lhs, SIXTRL_REAL_TYPE const rhs ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( ( rhs > +( ( SIXTRL_REAL_TYPE )SIXTRL_REAL_TYPE_EPS ) ) ||
                   ( rhs < -( ( SIXTRL_REAL_TYPE )SIXTRL_REAL_TYPE_EPS ) ) );
    return lhs / rhs; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_UINT64_TYPE NS(Type_add_uint64_type)(
    SIXTRL_UINT64_TYPE const lhs, SIXTRL_UINT64_TYPE const rhs ) SIXTRL_NOEXCEPT
{ return lhs + rhs; }

SIXTRL_INLINE SIXTRL_UINT64_TYPE NS(Type_subtract_uint64_type)(
    SIXTRL_UINT64_TYPE const lhs, SIXTRL_UINT64_TYPE const rhs ) SIXTRL_NOEXCEPT
{ return ( lhs >= rhs ) ? lhs - rhs : rhs - lhs; }

SIXTRL_INLINE SIXTRL_UINT64_TYPE NS(Type_multiply_uint64_type)(
    SIXTRL_UINT64_TYPE const lhs, SIXTRL_UINT64_TYPE const rhs ) SIXTRL_NOEXCEPT
{ return lhs * rhs; }

SIXTRL_INLINE SIXTRL_UINT64_TYPE NS(Type_divide_uint64_type)(
    SIXTRL_UINT64_TYPE const lhs, SIXTRL_UINT64_TYPE const rhs
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( rhs != ( SIXTRL_UINT64_TYPE )0u );
    return lhs / rhs; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_INT64_TYPE NS(Type_add_int64_type)(
    SIXTRL_INT64_TYPE const lhs, SIXTRL_INT64_TYPE const rhs ) SIXTRL_NOEXCEPT {
    return lhs + rhs; }

SIXTRL_INLINE SIXTRL_INT64_TYPE NS(Type_subtract_int64_type)(
    SIXTRL_INT64_TYPE const lhs, SIXTRL_INT64_TYPE const rhs ) SIXTRL_NOEXCEPT {
    return lhs - rhs; }

SIXTRL_INLINE SIXTRL_INT64_TYPE NS(Type_multiply_int64_type)(
    SIXTRL_INT64_TYPE const lhs, SIXTRL_INT64_TYPE const rhs ) SIXTRL_NOEXCEPT {
    return lhs * rhs; }

SIXTRL_INLINE SIXTRL_INT64_TYPE NS(Type_divide_int64_type)(
    SIXTRL_INT64_TYPE const lhs, SIXTRL_INT64_TYPE const rhs ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( rhs != ( SIXTRL_INT64_TYPE )0u );
    return lhs / rhs; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(status_type) NS(Type_add_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT it,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( lhs_it != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++it )
            *it = *lhs_it - *rhs_it; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_add_inplace_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs_it  != SIXTRL_NULLPTR ) && ( rhs_it != SIXTRL_NULLPTR ) &&
        ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it ) *lhs_it -= *rhs_it;
    } return status; }


SIXTRL_INLINE NS(status_type) NS(Type_subtract_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT it,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( lhs_it != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++it )
            *it = *lhs_it - *rhs_it; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_subtract_inplace_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs_it  != SIXTRL_NULLPTR ) && ( rhs_it != SIXTRL_NULLPTR ) &&
        ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it ) *lhs_it -= *rhs_it;
    } return status; }

SIXTRL_INLINE NS(status_type) NS(Type_multiply_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT it,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( lhs_it != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++it )
            *it = *lhs_it * *rhs_it; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_multiply_inplace_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs_it  != SIXTRL_NULLPTR ) && ( rhs_it != SIXTRL_NULLPTR ) &&
        ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it ) *lhs_it *= *rhs_it;
    } return status; }

SIXTRL_INLINE NS(status_type) NS(Type_divide_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT it,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( lhs_it != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++it )
            *it = NS(Type_divide_real_type)( *lhs_it, *rhs_it ); }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_divide_inplace_real_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_REAL_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs_it  != SIXTRL_NULLPTR ) && ( rhs_it != SIXTRL_NULLPTR ) &&
        ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it ) {
            SIXTRL_ASSERT(
                ( *rhs_it > ( SIXTRL_REAL_TYPE )SIXTRL_REAL_TYPE_EPS ) ||
                ( *rhs_it < ( SIXTRL_REAL_TYPE )SIXTRL_REAL_TYPE_EPS ) );
            *lhs_it /= *rhs_it; }
    } return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(status_type) NS(Type_add_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT it,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( lhs_it != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++it )
            *it = NS(Type_add_uint64_type)( *lhs_it, *rhs_it ); }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_add_inplace_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs_it  != SIXTRL_NULLPTR ) && ( rhs_it != SIXTRL_NULLPTR ) &&
        ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it ) *lhs_it += *rhs_it;
    } return status; }


SIXTRL_INLINE NS(status_type) NS(Type_subtract_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT it,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( lhs_it != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++it )
            *it = NS(Type_subtract_uint64_type)( *lhs_it, *rhs_it ); }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_subtract_inplace_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs_it  != SIXTRL_NULLPTR ) && ( rhs_it != SIXTRL_NULLPTR ) &&
        ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
        {
            if( *lhs_it >= *rhs_it ) *lhs_it -= *rhs_it;
            else *lhs_it = *rhs_it - *lhs_it;
        } }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_multiply_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT it,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( lhs_it != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++it )
            *it = NS(Type_multiply_uint64_type)( *lhs_it, *rhs_it ); }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_multiply_inplace_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs_it  != SIXTRL_NULLPTR ) && ( rhs_it != SIXTRL_NULLPTR ) &&
        ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it ) *lhs_it *= *rhs_it;
    } return status; }

SIXTRL_INLINE NS(status_type) NS(Type_divide_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT it,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( lhs_it != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++it )
            *it = NS(Type_divide_uint64_type)( *lhs_it, *rhs_it ); }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_divide_inplace_uint64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_UINT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs_it  != SIXTRL_NULLPTR ) && ( rhs_it != SIXTRL_NULLPTR ) &&
        ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it ) {
            SIXTRL_ASSERT( *rhs_it != ( SIXTRL_UINT64_TYPE )0u );
            *lhs_it /= *rhs_it; }
    } return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(status_type) NS(Type_add_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT it,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( lhs_it != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++it )
            *it = NS(Type_add_int64_type)( *lhs_it, *rhs_it ); }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_add_inplace_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs_it  != SIXTRL_NULLPTR ) && ( rhs_it != SIXTRL_NULLPTR ) &&
        ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it ) *lhs_it += *rhs_it;
    } return status; }


SIXTRL_INLINE NS(status_type) NS(Type_subtract_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT it,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( lhs_it != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++it )
            *it = NS(Type_subtract_int64_type)( *lhs_it, *rhs_it ); }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_subtract_inplace_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs_it  != SIXTRL_NULLPTR ) && ( rhs_it != SIXTRL_NULLPTR ) &&
        ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it ) *lhs_it -= *rhs_it; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_multiply_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT it,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( lhs_it != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++it )
            *it = NS(Type_multiply_int64_type)( *lhs_it, *rhs_it ); }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_multiply_inplace_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs_it  != SIXTRL_NULLPTR ) && ( rhs_it != SIXTRL_NULLPTR ) &&
        ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it ) *lhs_it *= *rhs_it;
    } return status; }

SIXTRL_INLINE NS(status_type) NS(Type_divide_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT it,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( lhs_it != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++it )
            *it = NS(Type_divide_int64_type)( *lhs_it, *rhs_it ); }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Type_divide_inplace_int64_type_ranges)(
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_it,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE* SIXTRL_RESTRICT lhs_end,
    SIXTRL_DATAPTR_DEC SIXTRL_INT64_TYPE const* SIXTRL_RESTRICT rhs_it
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs_it  != SIXTRL_NULLPTR ) && ( rhs_it != SIXTRL_NULLPTR ) &&
        ( lhs_end != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        SIXTRL_ASSERT( ( uintptr_t )lhs_it <= ( uintptr_t )lhs_end );
        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it ) {
            SIXTRL_ASSERT( *rhs_it != ( SIXTRL_INT64_TYPE )0u );
            *lhs_it /= *rhs_it; }
    } return status; }

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_TYPE_ARITHMETIC_HELPERS_H_ */
