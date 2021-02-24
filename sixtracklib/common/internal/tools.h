#ifndef SIXTRACKLIB_COMMON_INTERNAL_TOOLS_H__
#define SIXTRACKLIB_COMMON_INTERNAL_TOOLS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN SIXTRL_UINT64_TYPE NS(greatest_common_divisor)(
    SIXTRL_UINT64_TYPE a, SIXTRL_UINT64_TYPE b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_UINT64_TYPE NS(least_common_multiple)(
    SIXTRL_UINT64_TYPE a, SIXTRL_UINT64_TYPE b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_INT64_TYPE NS(sign_int64)(
    SIXTRL_INT64_TYPE const a ) SIXTRL_NOEXCEPT;


/* ************************************************************************** */
/* ************************************************************************** */

SIXTRL_INLINE SIXTRL_UINT64_TYPE NS(greatest_common_divisor)(
    SIXTRL_UINT64_TYPE a, SIXTRL_UINT64_TYPE b ) SIXTRL_NOEXCEPT {
    while( ( a != ( SIXTRL_UINT64_TYPE )0u ) &&
           ( b != ( SIXTRL_UINT64_TYPE )0u ) ) {
        if( a == ( SIXTRL_UINT64_TYPE )0u ) return b;
        b %= a;

        if( b == ( SIXTRL_UINT64_TYPE )0u ) return a;
        a %= b; }
    return ( a > b ) ? a : b; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_UINT64_TYPE NS(least_common_multiple)(
    SIXTRL_UINT64_TYPE a, SIXTRL_UINT64_TYPE b ) SIXTRL_NOEXCEPT {
    SIXTRL_UINT64_TYPE const gcd = NS(greatest_common_divisor)( a, b );
    return ( gcd != ( SIXTRL_UINT64_TYPE )0u )
        ? ( ( a * b ) / gcd ) : ( SIXTRL_UINT64_TYPE )0u; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_INT64_TYPE NS(sign_int64)(
    SIXTRL_INT64_TYPE const val ) SIXTRL_NOEXCEPT {
        return ( val > 0 ) - ( val < 0 ); }

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_COMMON_INTERNAL_TOOLS_H__ */
