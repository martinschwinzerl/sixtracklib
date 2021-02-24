#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/internal/math_qgauss.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_REAL_TYPE NS(Math_q_gauss_min_support_ext)(
    SIXTRL_REAL_TYPE const q, SIXTRL_REAL_TYPE const sqrt_beta ) SIXTRL_NOEXCEPT
{
    return NS(Math_q_gauss_min_support)( q, sqrt_beta );
}

SIXTRL_REAL_TYPE NS(Math_q_gauss_max_support_ext)(
    SIXTRL_REAL_TYPE const q, SIXTRL_REAL_TYPE const sqrt_beta ) SIXTRL_NOEXCEPT
{
    return NS(Math_q_gauss_max_support)( q, sqrt_beta );
}

SIXTRL_REAL_TYPE NS(Math_q_gauss_cq_ext)( SIXTRL_REAL_TYPE const q ) SIXTRL_NOEXCEPT
{
    return NS(Math_q_gauss_cq)( q );
}

SIXTRL_REAL_TYPE NS(Math_q_gauss_sqrt_beta_from_gauss_sigma_ext)(
    SIXTRL_REAL_TYPE const sigma ) SIXTRL_NOEXCEPT
{
    return NS(Math_q_gauss_sqrt_beta_from_gauss_sigma)( sigma );
}

SIXTRL_REAL_TYPE NS(Math_q_gauss_exp_q_ext)(
    SIXTRL_REAL_TYPE const x, SIXTRL_REAL_TYPE const q ) SIXTRL_NOEXCEPT
{
    return NS(Math_q_gauss_exp_q)( x, q );
}

SIXTRL_REAL_TYPE NS(Math_q_gauss_ext)( SIXTRL_REAL_TYPE const x,
    SIXTRL_REAL_TYPE const q, SIXTRL_REAL_TYPE const sqrt_beta,
    SIXTRL_REAL_TYPE const cq ) SIXTRL_NOEXCEPT
{
    return NS(Math_q_gauss)( x, q, sqrt_beta, cq );
}

SIXTRL_REAL_TYPE NS(Math_q_gauss_shifted_ext)( SIXTRL_REAL_TYPE const x,
    SIXTRL_REAL_TYPE const q, SIXTRL_REAL_TYPE const sqrt_beta,
    SIXTRL_REAL_TYPE const cq, SIXTRL_REAL_TYPE const mu ) SIXTRL_NOEXCEPT
{
    return NS(Math_q_gauss_shifted)( x, q, sqrt_beta, cq, mu );
}
