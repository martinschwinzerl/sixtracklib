/////////////////////////////////////////////////////////////////////////////
//
// FILE NAME
//   ErrorFunctions.c
//
//   02/19/2015, 08/18/2015
//
// AUTHORS
//   Hannes Bartosik, Adrian Oeftiger
//
// DESCRIPTION
//   Error functions
//
/////////////////////////////////////////////////////////////////////////////

#ifndef SIXTACKLIB_COMMON_BE_BEAMFIELDS_FADDEEVA_CERN_HEADER_H__
#define SIXTACKLIB_COMMON_BE_BEAMFIELDS_FADDEEVA_CERN_HEADER_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/internal/math_functions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* !defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN void NS(BeamFields_cerrf)(
    NS(be_real_type) const in_real, NS(be_real_type) const in_imag,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT out_real,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT out_imag
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(BeamFields_cerrf_cern1970)(
    NS(be_real_type) const in_real, NS(be_real_type) const in_imag,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT out_real,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT out_imag
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(BeamFields_cerrf_cern1970_modified)(
    NS(be_real_type) const in_real, NS(be_real_type) const in_imag,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT out_real,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT out_imag
) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* !defined( __cplusplus ) && !defined( _GPUCODE ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
	#include <math.h>
#endif

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* !defined( __cplusplus ) && !defined( _GPUCODE ) */

/* From: be_beamfields/faddeeva_cern.h */

SIXTRL_INLINE void NS(BeamFields_cerrf)(
    NS(be_real_type) const in_real, NS(be_real_type) const in_imag,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT out_real,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT out_imag
) SIXTRL_NOEXCEPT
{
    NS(BeamFields_cerrf_cern1970)( in_real, in_imag, out_real, out_imag );
}

/* ************************************************************************** */

SIXTRL_INLINE void NS(BeamFields_cerrf_cern1970)(
    NS(be_real_type) const in_real, NS(be_real_type) const in_imag,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT out_real,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT out_imag
) SIXTRL_NOEXCEPT
{
    /* This function calculates the SIXTRL_REAL_T precision complex error fnct.
    based on the algorithm of the FORTRAN function written at CERN by K. Koelbig
    Program C335, 1970. See also M. Bassetti and G.A. Erskine, "Closed
    expression for the electric field of a two-dimensional Gaussian charge
    density", CERN-ISR-TH/80-06; */

    typedef NS(be_real_type) real_type;

    real_type const x = NS(abs)( in_real );
    real_type const y = NS(abs)( in_imag );

    int n, nc, nu;
    real_type h, q, Saux, Sx, Sy, Tn, Tx, Ty, Wx, Wy, xh, xl, yh;
    real_type Rx[ 33 ];
    real_type Ry[ 33 ];

    if( ( y < ( real_type )SIXTRL_FADDEEVA_CERN_Y_LIMIT ) &&
        ( x < ( real_type )SIXTRL_FADDEEVA_CERN_X_LIMIT ) )
    {
        real_type temp = ( real_type )1.0 - x /
            ( real_type )SIXTRL_FADDEEVA_CERN_X_LIMIT;

        q = ( ( real_type )1. - y / ( real_type )SIXTRL_FADDEEVA_CERN_Y_LIMIT );
        q *= NS(sqrt)( temp );
        h  = ( real_type )1.0 / ( ( real_type )3.2 * q );
        nc = 7 + ( int )( ( real_type )23.0 * q );
        xl = pow( h, ( real_type )( 1 - nc ) );
        xh = y + ( real_type )0.5 / h;
        yh = x;
        nu = 10 + ( int )( ( real_type )21.0 * q );
        Rx[ nu ] = ( real_type )0.0;
        Ry[ nu ] = ( real_type )0.0;
        for (n = nu; n > 0; n--){
            Tx = xh + n * Rx[ n ];
            Ty = yh - n * Ry[ n ];
            Tn = Tx * Tx + Ty * Ty;
            Rx[ n - 1 ] = ( real_type )0.5 * Tx / Tn;
            Ry[ n - 1 ] = ( real_type )0.5 * Ty / Tn;
            }
        /* .... */
        Sx = ( real_type )0.0;
        Sy = ( real_type )0.0;
        for( n = nc ; n > 0 ; n-- ){
            Saux = Sx + xl;
            Sx = Rx[ n - 1 ] * Saux - Ry[ n - 1 ] * Sy;
            Sy = Rx[ n - 1 ] * Sy   + Ry[ n - 1 ] * Saux;
            xl = h * xl;
        };

        Wx = ( real_type )SIXTRL_FADDEEVA_CERN_A_CONSTANT * Sx;
        Wy = ( real_type )SIXTRL_FADDEEVA_CERN_A_CONSTANT * Sy;
    }
    else
    {
        xh = y;
        yh = x;
        Rx[ 0 ] = ( real_type )0.0;
        Ry[ 0 ] = ( real_type )0.0;
        for( n = 9 ; n > 0 ; n-- ){
            Tx = xh + n * Rx[ 0 ];
            Ty = yh - n * Ry[ 0 ];
            Tn = Tx * Tx + Ty * Ty;
            Rx[ 0 ] = ( real_type )0.5 * Tx / Tn;
            Ry[ 0 ] = ( real_type )0.5 * Ty / Tn;
        };
        Wx = ( real_type )SIXTRL_FADDEEVA_CERN_A_CONSTANT * Rx[ 0 ];
        Wy = ( real_type )SIXTRL_FADDEEVA_CERN_A_CONSTANT * Ry[ 0 ];
    }

    if( y == ( real_type )0.0 ){ Wx = NS(exp)( -x * x ); }
    if( in_imag < ( real_type )0.0 )
    {
        Wx =   ( real_type )2.0 * NS(exp)(y * y - x * x) * NS(cos)(
                    ( real_type )2.0 * x * y ) - Wx;

        Wy = - ( real_type )2.0 * NS(exp)(y * y - x * x) * NS(sin)(
                    ( real_type )2.0 * x * y ) - Wy;

        if( in_real > ( real_type )0.0 )
        {
            Wy = -Wy;
        }
    }
    else if( in_real < ( real_type )0.0 )
    {
        Wy = -Wy;
    }

    *out_real = Wx;
    *out_imag = Wy;
}

SIXTRL_INLINE void NS(BeamFields_cerrf_cern1970_modified)(
    NS(be_real_type) const in_real, NS(be_real_type) const in_imag,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT out_real,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT out_imag
) SIXTRL_NOEXCEPT
{
    NS(BeamFields_cerrf_cern1970)( in_real, in_imag, out_real, out_imag );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* !defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTACKLIB_COMMON_BE_BEAMFIELDS_FADDEEVA_CERN_HEADER_H__ */

/* end: sixtracklib/common/be_beamfields/faddeeva_cern.h */
