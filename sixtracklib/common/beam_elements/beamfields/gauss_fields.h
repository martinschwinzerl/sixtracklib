#ifndef SIXTRACKL_COMMON_BE_BEAMFIELDS_GAUSS_FIELDS_H__
#define SIXTRACKL_COMMON_BE_BEAMFIELDS_GAUSS_FIELDS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && !defined( __cplusplus )
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && !defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN void NS(BeamFields_transv_field_gauss_circular)(
    NS(be_real_type) const sigma,
    NS(be_real_type) const Delta_x,
    NS(be_real_type) const Delta_y,
    NS(be_real_type) const x,
    NS(be_real_type) const y,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Ex_out,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Ey_out
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(BeamFields_transv_field_gauss_elliptic)(
    NS(be_real_type) const sigma_x,
    NS(be_real_type) const sigma_y,
    NS(be_real_type) const Delta_x,
    NS(be_real_type) const Delta_y,
    NS(be_real_type) const x,
    NS(be_real_type) const y,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Ex_out,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Ey_out
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(BeamFields_calculate_gauss_components)(
    NS(be_real_type) const x,
    NS(be_real_type) const y,
    NS(be_real_type) const sigma_x,
    NS(be_real_type) const sigma_y,
    NS(be_real_type) const min_sigma_diff,
    bool const skip_Gs,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Ex_ptr,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Ey_ptr,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Gx_ptr,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Gy_ptr
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ------------------------------------------------------------------------- */
/* Inline functions implementation */
/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beamfields/faddeeva_cern.h"
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/physics_constants.h"
#endif

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE void NS(BeamFields_transv_field_gauss_circular)(
    NS(be_real_type) const sigma,
    NS(be_real_type) const Delta_x,
    NS(be_real_type) const Delta_y,
    NS(be_real_type) const x,
    NS(be_real_type) const y,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Ex_out,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Ey_out ) SIXTRL_NOEXCEPT
{
    typedef NS(be_real_type) real_type;

    real_type const dx = x - Delta_x;
    real_type const dy = y - Delta_y;
    real_type const r_squ = dx * dx + dy * dy;

    real_type temp = ( real_type )2. * NS(MathConst_pi)() *
        NS(PhysConst_epsilon0)();

    SIXTRL_ASSERT( Ex_out != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( Ey_out != SIXTRL_NULLPTR );

    if( r_squ < ( NS(be_real_type) )SIXTRL_BE_BEAMFIELDS_R_SQU_THRESHOLD )
    {
        /* Linearised approximation for small r_squ */
        temp *= sigma;
        SIXTRL_ASSERT( ( real_type )SIXTRL_REAL_TYPE_EPS <= NS(abs)( temp ) );
        temp = NS(sqrt)( r_squ ) / temp;
    }
    else
    {
        temp *= r_squ;
        SIXTRL_ASSERT( ( real_type )SIXTRL_REAL_TYPE_EPS <= NS(abs)( temp ) );
        temp = ( ( real_type )1.0 - NS(exp)( ( real_type )-0.5 * r_squ /
                 ( sigma * sigma ) ) ) / temp;
    }

    *Ex_out = temp * dx;
    *Ey_out = temp * dy;
}

SIXTRL_INLINE void NS(BeamFields_transv_field_gauss_elliptic)(
    NS(be_real_type) const sigma_x,
    NS(be_real_type) const sigma_y,
    NS(be_real_type) const Delta_x,
    NS(be_real_type) const Delta_y,
    NS(be_real_type) const x,
    NS(be_real_type) const y,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Ex_out,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Ey_out
) SIXTRL_NOEXCEPT
{
    typedef NS(be_real_type) real_type;

    /* I always go to the first quadrant and then apply the signs a posteriori
     * numerically more stable
     * (see http://inspirehep.net/record/316705/files/slac-pub-5582.pdf) */

    real_type dx = x - Delta_x;
    real_type dy = y - Delta_y;

    real_type const sign_dx = NS(sign)( x - Delta_x );
    real_type const sign_dy = NS(sign)( y - Delta_y );
    real_type factBE = ( real_type )1.0 / ( ( real_type )2.0 *
            NS(MathConst_sqrt_pi)() * NS(PhysConst_epsilon0)() );

    real_type expBE  = dx * dx;

    dx *= sign_dx;
    dy *= sign_dy;

    SIXTRL_ASSERT( Ex_out != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( Ey_out != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( NS(abs)( sigma_x ) > ( real_type )SIXTRL_REAL_TYPE_EPS );
    SIXTRL_ASSERT( NS(abs)( sigma_y ) > ( real_type )SIXTRL_REAL_TYPE_EPS );
    SIXTRL_ASSERT( NS(abs)( ( real_type )2.0 * sigma_x * sigma_x ) >
                            ( real_type )SIXTRL_REAL_TYPE_EPS );
    SIXTRL_ASSERT( NS(abs)( ( real_type )2.0 * sigma_y * sigma_y ) >
                            ( real_type )SIXTRL_REAL_TYPE_EPS );

    expBE /= sigma_x * sigma_x;
    expBE += ( dy * dy ) / ( sigma_y * sigma_y );
    expBE /= ( real_type )2.0;
    expBE  = NS(exp)( -expBE );

    //printf("x = %.2e y = %.2e abx = %.2e aby = %.2e", xx, yy, abx, aby);

    if( sigma_x > sigma_y )
    {
        real_type const S = NS(sqrt)( ( real_type )2.0 * (
            sigma_x * sigma_x - sigma_y * sigma_y ) );

        SIXTRL_ARGPTR_DEC real_type w_zetaBE_re = ( real_type )0.0;
        SIXTRL_ARGPTR_DEC real_type w_zetaBE_im = ( real_type )0.0;
        SIXTRL_ARGPTR_DEC real_type w_etaBE_re  = ( real_type )0.0;
        SIXTRL_ARGPTR_DEC real_type w_etaBE_im  = ( real_type )0.0;

        SIXTRL_ASSERT(
            ( NS(abs)( sigma_x * S ) > ( real_type )SIXTRL_REAL_TYPE_EPS ) &&
            ( NS(abs)( sigma_y * S ) > ( real_type )SIXTRL_REAL_TYPE_EPS ) );

        /* factBE = 1. / ( 2. * epsilon0 * sqrt( pi ) * S ) */
        SIXTRL_ASSERT( NS(abs)( S ) > ( real_type )SIXTRL_REAL_TYPE_EPS );
        factBE /= S;

        /* w_zetaBE_re, w_zetaBE_im = wfun( |x - Delta_x|/S, |y - Delta_y|/S ) */
        NS(BeamFields_cerrf)( dx / S,  dy / S, &w_zetaBE_re, &w_zetaBE_im );

        /* w_etaBE_re, w_etaBE_im = wfun(
                    (sigma_y * |x - Delta_x|)/( sigma_x * S),
                    (sigma_x * |y - Delta_y|)/( sigma_y * S) ) */

        NS(BeamFields_cerrf)( ( dx * sigma_y ) / ( S * sigma_x ),
                              ( dy * sigma_x ) / ( S * sigma_y ),
                              &w_etaBE_re, &w_etaBE_im );

        *Ex_out = sign_dx * factBE * ( w_zetaBE_im - w_etaBE_im * expBE );
        *Ey_out = sign_dy * factBE * ( w_zetaBE_re - w_etaBE_re * expBE );
    }
    else if( sigma_x < sigma_y )
    {
        real_type const S = NS(sqrt)( ( real_type )2.0 * (
            sigma_y * sigma_y - sigma_x * sigma_x ) );

        SIXTRL_ARGPTR_DEC real_type w_zetaBE_re = ( real_type )0.0;
        SIXTRL_ARGPTR_DEC real_type w_zetaBE_im = ( real_type )0.0;
        SIXTRL_ARGPTR_DEC real_type w_etaBE_re  = ( real_type )0.0;
        SIXTRL_ARGPTR_DEC real_type w_etaBE_im  = ( real_type )0.0;

        SIXTRL_ASSERT(
            ( NS(abs)( sigma_x * S ) > ( real_type )SIXTRL_REAL_TYPE_EPS ) &&
            ( NS(abs)( sigma_y * S ) > ( real_type )SIXTRL_REAL_TYPE_EPS ) );

        /* factBE = 1. / ( 2. * epsilon0 * sqrt( pi ) * S ) */
        SIXTRL_ASSERT( NS(abs)( S ) > ( real_type )SIXTRL_REAL_TYPE_EPS );
        factBE /= S;

        /* w_zetaBE_re, w_zetaBE_im = wfun( |x - Delta_x|/S, |y - Delta_y|/S ) */
        NS(BeamFields_cerrf)( dy / S,  dx / S, &w_zetaBE_re, &w_zetaBE_im );

        /* w_etaBE_re, w_etaBE_im = wfun(
                    (sigma_y * |x - Delta_x|)/( sigma_x * S),
                    (sigma_x * |y - Delta_y|)/( sigma_y * S) ) */
        SIXTRL_ASSERT(
            ( NS(abs)( sigma_x * S ) > ( real_type )SIXTRL_REAL_TYPE_EPS ) &&
            ( NS(abs)( sigma_y * S ) > ( real_type )SIXTRL_REAL_TYPE_EPS ) );

        NS(BeamFields_cerrf)( ( dy * sigma_x ) / ( S * sigma_y ),
                              ( dx * sigma_y ) / ( S * sigma_x ),
                              &w_etaBE_re, &w_etaBE_im );

        *Ex_out = sign_dx * factBE * ( w_zetaBE_re - w_etaBE_re * expBE );
        *Ey_out = sign_dy * factBE * ( w_zetaBE_im - w_etaBE_im * expBE );
    }
    else
    {
        *Ex_out = ( real_type )0.0;
        *Ey_out = ( real_type )0.0;
    }
}

SIXTRL_INLINE void NS(BeamFields_calculate_gauss_components)(
    NS(be_real_type) const x,
    NS(be_real_type) const y,
    NS(be_real_type) const sigma_x,
    NS(be_real_type) const sigma_y,
    NS(be_real_type) const min_sigma_diff, bool const skip_Gs,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Ex_out,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Ey_out,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Gx_out,
    SIXTRL_ARGPTR_DEC NS(be_real_type)* SIXTRL_RESTRICT Gy_out ) SIXTRL_NOEXCEPT
{
    typedef NS(be_real_type) real_type;

    SIXTRL_ASSERT( Ex_out != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( Ey_out != SIXTRL_NULLPTR );

    if( NS(abs)( sigma_x - sigma_y ) < min_sigma_diff )
    {
        real_type const sigma = ( real_type )0.5 * ( sigma_x + sigma_y );

        if( skip_Gs )
        {
            NS(BeamFields_transv_field_gauss_circular)(
                sigma, ( real_type )0., ( real_type )0., x, y, Ex_out, Ey_out );

            if( Gx_out != SIXTRL_NULLPTR ) *Gx_out = ( real_type )0.0;
            if( Gy_out != SIXTRL_NULLPTR ) *Gy_out = ( real_type )0.0;
        }
        else
        {
            SIXTRL_ARGPTR_DEC real_type Ex = ( real_type )0.0;
            SIXTRL_ARGPTR_DEC real_type Ey = ( real_type )0.0;

            real_type const r_squ = x * x + y * y;
            real_type inv_rsqu_fact = ( real_type )0.5;
            real_type exp_factor = ( real_type )2.0 * sigma * sigma *
                NS(MathConst_pi)() * NS(PhysConst_epsilon0)();

            NS(BeamFields_transv_field_gauss_circular)(
                sigma, ( real_type )0., ( real_type )0., x, y, &Ex, &Ey );

            SIXTRL_ASSERT( Gx_out != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( Gy_out != SIXTRL_NULLPTR );

            SIXTRL_ASSERT( exp_factor > ( real_type )SIXTRL_REAL_TYPE_EPS );
            SIXTRL_ASSERT( ( real_type )2.0 * sigma * sigma >
                           ( real_type )SIXTRL_REAL_TYPE_EPS );
            SIXTRL_ASSERT( ( real_type )2.0 * r_squ >
                           ( real_type )SIXTRL_REAL_TYPE_EPS );

            inv_rsqu_fact /= r_squ; /* factor = 1.0 / ( 2.0 * r_squ ) */
            exp_factor = NS(exp)( -r_squ / (
                ( real_type )2.0 * sigma * sigma ) ) / exp_factor;

            *Gx_out = inv_rsqu_fact * (  y * Ey - x * Ex + x * x * exp_factor );
            *Gy_out = inv_rsqu_fact * (  x * Ex - y * Ey + y * y * exp_factor );

            *Ex_out = Ex;
            *Ey_out = Ey;
        }
    }
    else
    {
        if( skip_Gs )
        {
            NS(BeamFields_transv_field_gauss_elliptic)( sigma_x, sigma_y,
                ( real_type )0.0, ( real_type )0.0, x, y, Ex_out, Ey_out );

            if( Gx_out != SIXTRL_NULLPTR ) *Gx_out = ( real_type )0.0;
            if( Gy_out != SIXTRL_NULLPTR ) *Gy_out = ( real_type )0.0;
        }
        else
        {
            SIXTRL_ARGPTR_DEC real_type Ex = ( real_type )0.0;
            SIXTRL_ARGPTR_DEC real_type Ey = ( real_type )0.0;

            real_type inv_sig11_sig33 = ( real_type )0.5;
            real_type const denom = ( real_type )2.0 * NS(MathConst_pi)() *
                NS(PhysConst_epsilon0)();

            real_type const Sig_11 = sigma_x * sigma_x;
            real_type const Sig_33 = sigma_y * sigma_y;
            real_type const exp_factor = NS(exp)(
                -( x * x ) / ( ( real_type )2.0 * Sig_11 )
                -( y * y ) / ( ( real_type )2.0 * Sig_33 ) );

            SIXTRL_ASSERT( Gx_out != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( Gy_out != SIXTRL_NULLPTR );

            SIXTRL_ASSERT( denom > ( real_type )SIXTRL_REAL_TYPE_EPS );
            SIXTRL_ASSERT( ( real_type )2.0 * Sig_11 >
                           ( real_type )SIXTRL_REAL_TYPE_EPS );
            SIXTRL_ASSERT( ( real_type )2.0 * Sig_33 >
                           ( real_type )SIXTRL_REAL_TYPE_EPS );
            SIXTRL_ASSERT( ( real_type )2.0 * ( Sig_11 - Sig_33 ) >
                           ( real_type )SIXTRL_REAL_TYPE_EPS );

            SIXTRL_ASSERT( NS(abs)( sigma_x ) >
                           ( real_type )SIXTRL_REAL_TYPE_EPS );

            SIXTRL_ASSERT( NS(abs)( sigma_y ) >
                           ( real_type )SIXTRL_REAL_TYPE_EPS );

            NS(BeamFields_transv_field_gauss_elliptic)( sigma_x, sigma_y,
                ( real_type )0.0, ( real_type )0.0, x, y, &Ex, &Ey );

            inv_sig11_sig33 /= ( Sig_11 - Sig_33 );

            *Gx_out = -inv_sig11_sig33 * ( x * Ex + y * Ey + (
                ( sigma_y / sigma_x ) * exp_factor - ( real_type )1.0 ) / denom );

            *Gy_out =  inv_sig11_sig33 * ( x * Ex + y * Ey + (
                ( sigma_x / sigma_y ) * exp_factor - ( real_type )1.0 ) / denom );

            *Ex_out = Ex;
            *Ey_out = Ey;
        }
    }
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKL_COMMON_BE_BEAMFIELDS_GAUSS_FIELDS_H__ */
