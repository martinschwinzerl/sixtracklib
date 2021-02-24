#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_HELPER_C99_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_HELPER_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if !defined( __cplusplus )
        #include <stdbool.h>
        #include <stddef.h>
        #include <stdlib.h>
    #else /* defined( __cplusplus ) */
        #include <cstddef>
        #include <cstdlib>
    #endif /* !defined( __cplusplus ) */
    #include <stdint.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN void
NS(Particle_beta0_gamma0_from_charge0_mass0_p0c_impl)(
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const p0c,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT beta0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT gamma0
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void
NS(Particle_gamma0_p0c_from_charge0_mass0_beta0_impl)(
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const beta0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT gamma0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT p0c
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void
NS(Particle_beta0_p0c_from_charge0_mass0_gamma0_impl)(
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const gamma0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT beta0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT p0c
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_sigma_impl)(
    NS(particle_real_type) const zeta,
    NS(particle_real_type) const rvv ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_zeta_from_sigma_impl)(
    NS(particle_real_type) const sigma,
    NS(particle_real_type) const rvv ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_tau_impl)(
    NS(particle_real_type) const zeta, NS(particle_real_type) const rvv,
    NS(particle_real_type) const beta0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_zeta_from_tau_impl)(
    NS(particle_real_type) const tau, NS(particle_real_type) const rvv,
    NS(particle_real_type) const beta0 ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_energy0_impl)(
    NS(particle_real_type) const mass0,
    NS(particle_real_type) const p0c ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type)
NS(Particle_p0c_from_energy0_mass0_impl)(
    NS(particle_real_type) const energy0,
    NS(particle_real_type) const mass0 ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  */

SIXTRL_STATIC SIXTRL_FN void NS(Particle_update_delta_impl)(
    NS(particle_real_type) const delta, NS(particle_real_type) const beta0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_delta,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_psigma,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rpp,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rvv
) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_energy_impl)(
    NS(particle_real_type) const p0c, NS(particle_real_type) const mass0,
    NS(particle_real_type) const mass_ratio, NS(particle_real_type) const delta,
    NS(particle_real_type) const beta0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_energy_impl)(
    NS(particle_real_type) const energy0, NS(particle_real_type) const delta,
    NS(particle_real_type) const rvv, NS(particle_real_type) const beta0,
    NS(particle_real_type) const d_energy,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_zeta,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_delta,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_psigma,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rpp,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rvv
) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_psigma_impl)(
    NS(particle_real_type) const delta,
    NS(particle_real_type) const beta0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_update_psigma_impl)(
    NS(particle_real_type) const psigma, NS(particle_real_type) const beta0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_delta,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_psigma,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rpp,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rvv
) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_ptau_impl)(
    NS(particle_real_type) const delta,
    NS(particle_real_type) const beta0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_update_ptau_impl)(
    NS(particle_real_type) const ptau, NS(particle_real_type) const beta0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT delta,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT psigma,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT rpp,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT rvv
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_beta_impl)(
    NS(particle_real_type) const beta0, NS(particle_real_type) const rvv
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_gamma_impl)(
    NS(particle_real_type) const beta0, NS(particle_real_type) const rvv
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_mass_ratio_impl)(
    NS(particle_real_type) const charge_ratio,
    NS(particle_real_type) const chi ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_charge_impl)(
    NS(particle_real_type) const charge_ratio,
    NS(particle_real_type) const charge0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_mass_impl)(
    NS(particle_real_type) const charge_ratio, NS(particle_real_type) const chi,
    NS(particle_real_type) const mass0 ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(Particles_copy_real_field_impl)(
    SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_real_type) const* SIXTRL_RESTRICT src,
    NS(particles_num_type) src_idx_begin,
    NS(particles_num_type) const src_idx_end,
    NS(particles_num_type) dst_idx_begin,
    NS(particles_num_type) const stride ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_copy_index_field_impl)(
    SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_index_type) const* SIXTRL_RESTRICT src,
    NS(particles_num_type) src_idx_begin,
    NS(particles_num_type) const src_idx_end,
    NS(particles_num_type) dst_idx_begin,
    NS(particles_num_type) const stride ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

// SIXTRL_STATIC SIXTRL_FN NS(particles_sort_flags)
// NS(Particle_compare_less_than_index_attribute_impl)(
//     NS(particle_index_type) const lhs_value,
//     NS(particle_index_type) const rhs_value,
//     NS(particles_sort_flags) const use_this_sort_flag ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================== */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/math_constants.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE void NS(Particle_beta0_gamma0_from_charge0_mass0_p0c_impl)(
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const p0c,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_beta0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_gamma0
) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_t;

    real_t gamma0 = ( real_t )0.0;
    real_t beta0  = ( real_t )0.0;

    if( ( mass0 > ( real_t )0.0 ) && ( p0c >= ( real_t )0.0 ) &&
        ( NS(abs)( charge0 ) > ( real_t )0.0 ) )
    {
        gamma0 = NS(sqrt)( p0c * p0c + mass0 * mass0 ) / mass0;
        beta0  = ( real_t )1.0 - ( real_t )1.0 / ( gamma0 * gamma0 );

        SIXTRL_ASSERT( beta0 > ( real_t )0.0 );
        beta0 = NS(sqrt)( beta0 );
    }

    if( ptr_beta0  != SIXTRL_NULLPTR ) *ptr_beta0 = beta0;
    if( ptr_gamma0 != SIXTRL_NULLPTR ) *ptr_gamma0 = gamma0;
}

SIXTRL_INLINE void NS(Particle_gamma0_p0c_from_charge0_mass0_beta0_impl)(
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const beta0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_gamma0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_p0c
) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_t;

    real_t gamma0 = ( real_t )0.0;
    real_t p0c = ( real_t )0.0;

    if( ( mass0 > ( real_t )0.0 ) && ( beta0 > ( real_t )0.0 ) &&
        ( NS(abs)( charge0 ) > ( real_t )0.0 ) )
    {
        gamma0 = ( real_t )1.0 / NS(sqrt)( ( real_t )1.0 - beta0 * beta0 );
        p0c = mass0 * mass0 + ( gamma0 * gamma0 - ( real_t )1.0 );

        SIXTRL_ASSERT( p0c > ( real_t )0.0 );
        p0c = NS(sqrt)( p0c );
    }

    if( ptr_gamma0 != SIXTRL_NULLPTR ) *ptr_gamma0 = gamma0;
    if( ptr_p0c != SIXTRL_NULLPTR ) *ptr_p0c = p0c;
}

SIXTRL_INLINE void NS(Particle_beta0_p0c_from_charge0_mass0_gamma0_impl)(
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const gamma0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_beta0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_p0c
) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_t;

    real_t beta0 = ( real_t )0.0;
    real_t p0c   = ( real_t )0.0;

    if( ( mass0 > ( real_t )0.0 ) && ( gamma0 > ( real_t )1.0 ) &&
        ( NS(abs)( charge0 ) > ( real_t )0.0 ) )
    {
        p0c = mass0 * mass0 * ( gamma0 * gamma0 - ( real_t )1.0 );

        if( p0c > ( real_t )0.0 )
        {
            p0c = NS(sqrt)( p0c );
            beta0 = ( real_t )1.0 - ( real_t )1.0 / ( gamma0 * gamma0 );
            SIXTRL_ASSERT( beta0 > ( real_t )0.0 );
            beta0 = NS(sqrt)( beta0 );
        }
    }

    if( ptr_beta0 != SIXTRL_NULLPTR ) *ptr_beta0 = beta0;
    if( ptr_p0c != SIXTRL_NULLPTR ) *ptr_p0c = p0c;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_sigma_impl)(
    NS(particle_real_type) const zeta,
    NS(particle_real_type) const rvv ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( rvv > ( NS(particle_real_type) )0.0 );
    return ( zeta / rvv );
}

SIXTRL_INLINE NS(particle_real_type) NS(Particle_zeta_from_sigma_impl)(
    NS(particle_real_type) const sigma,
    NS(particle_real_type) const rvv ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( rvv > ( NS(particle_real_type) )0.0 );
    return sigma * rvv;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_tau_impl)(
    NS(particle_real_type) const zeta, NS(particle_real_type) const rvv,
    NS(particle_real_type) const beta0 ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( beta0 >  ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( beta0 <= ( NS(particle_real_type) )1.0 );
    SIXTRL_ASSERT( rvv   >  ( NS(particle_real_type) )0.0 );
    return zeta / ( beta0 * rvv );
}

SIXTRL_INLINE NS(particle_real_type) NS(Particle_zeta_from_tau_impl)(
    NS(particle_real_type) const tau, NS(particle_real_type) const rvv,
    NS(particle_real_type) const beta0 ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( beta0 >  ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( beta0 <= ( NS(particle_real_type) )1.0 );
    SIXTRL_ASSERT( rvv   >  ( NS(particle_real_type) )0.0 );
    return tau * beta0 * rvv;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_energy0_impl)(
    NS(particle_real_type) const mass0,
    NS(particle_real_type) const p0c ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mass0 > ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( p0c > ( NS(particle_real_type) )0.0 );
    return NS(sqrt)( mass0 * mass0 + p0c * p0c );
}

SIXTRL_INLINE NS(particle_real_type) NS(Particle_p0c_from_energy0_mass0_impl)(
    NS(particle_real_type) const energy0,
    NS(particle_real_type) const mass0 ) SIXTRL_NOEXCEPT {
    NS(particle_real_type) const p0c_squ = energy0 * energy0 - mass0 * mass0;
    SIXTRL_ASSERT( p0c_squ > ( NS(particle_real_type) )0.0 );
    return NS(sqrt)( p0c_squ );
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  */

SIXTRL_INLINE void NS(Particle_update_delta_impl)(
    NS(particle_real_type) const delta, NS(particle_real_type) const beta0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_delta,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_psigma,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rpp,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rvv
) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_t;

    real_t const delta_beta0 = delta * beta0;
    real_t const delta_plus_one = delta + ( real_t )1.0;
    real_t ptau_beta0_plus_one = delta_beta0 * delta_beta0 +
        ( real_t )2.0 * delta_beta0 * beta0 + ( real_t )1.0;

    SIXTRL_ASSERT( ptr_delta  != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_psigma != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_rpp    != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_rvv    != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( NS(abs)( delta_plus_one ) > ( real_t )0.0 );
    SIXTRL_ASSERT( beta0 > ( real_t )0.0 );
    SIXTRL_ASSERT( beta0 < ( real_t )1.0 );
    SIXTRL_ASSERT( ptau_beta0_plus_one > ( real_t )0.0 );

    ptau_beta0_plus_one = NS(sqrt)( ptau_beta0_plus_one );

    *ptr_delta  = delta;
    *ptr_psigma = ( ptau_beta0_plus_one - ( real_t )1.0 ) / ( beta0 * beta0 );
    *ptr_rpp    = ( real_t )1.0 / delta_plus_one;
    *ptr_rvv    = delta_plus_one / ptau_beta0_plus_one;
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_energy_impl)(
    NS(particle_real_type) const p0c, NS(particle_real_type) const mass0,
    NS(particle_real_type) const mass_ratio, NS(particle_real_type) const delta,
    NS(particle_real_type) const beta0 ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p0c >        ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( mass0 >      ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( beta0 >      ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( beta0 <      ( NS(particle_real_type) )1.0 );
    SIXTRL_ASSERT( mass_ratio > ( NS(particle_real_type) )0.0 );

    return NS(sqrt)( p0c * p0c + mass0 * mass0 ) * mass_ratio +
           NS(Particle_psigma_impl)( delta, beta0 ) * p0c * beta0;
}

SIXTRL_INLINE void NS(Particle_add_to_energy_impl)(
    NS(particle_real_type) const energy0, NS(particle_real_type) const delta,
    NS(particle_real_type) const initial_rvv, NS(particle_real_type) const beta0,
    NS(particle_real_type) const d_energy,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_zeta,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_delta,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_psigma,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rpp,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rvv
) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_t;

    real_t ptau = ( real_t )0.0;
    real_t psigma = ( real_t )0.0;
    real_t temp = ( real_t )0.0; /* temp == delta_plus_one */
    real_t const delta_beta0 = delta * beta0;
    real_t ptau_beta0_plus_one = delta_beta0 * delta_beta0 +
        ( real_t )2.0 * delta_beta0 * beta0 + ( real_t )1.0;

    SIXTRL_ASSERT( ptr_zeta   != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_delta  != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_psigma != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_rpp != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_rvv != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( energy0 > ( real_t )0.0 );
    SIXTRL_ASSERT( NS(abs)( initial_rvv ) > ( real_t )SIXTRL_REAL_TYPE_EPS );

    SIXTRL_ASSERT( beta0 > ( real_t )0.0 );
    SIXTRL_ASSERT( beta0 < ( real_t )1.0 );
    SIXTRL_ASSERT( ptau_beta0_plus_one > ( real_t )0.0 );

    ptau_beta0_plus_one  = NS(sqrt)( ptau_beta0_plus_one );
    ptau_beta0_plus_one += d_energy / energy0;

    ptau   = ( ptau_beta0_plus_one - ( real_t )1.0 ) / beta0;
    psigma = ( ptau_beta0_plus_one - ( real_t )1.0 ) / ( beta0 * beta0 );

    /* ( delta + 1 ) = sqrt( ptau ^ 2 + 2 * psigma + 1 ) */
    temp = ptau * ptau + ( real_t )2.0 * psigma + ( real_t )1.0;

    SIXTRL_ASSERT( temp > ( real_t )0.0 );
    SIXTRL_ASSERT( ptau_beta0_plus_one > ( real_t )0.0 );
    temp = NS(sqrt)( temp );
    SIXTRL_ASSERT( temp >= ( real_t )0.0 );

    *ptr_delta  = temp - ( real_t )1.0;
    *ptr_psigma = psigma;
    *ptr_rpp    = ( real_t )1.0 / temp;

    /* rvv = (delta + 1)/(ptau * beta0 + 1) = temp/ptau_beta0_plus_one */
    temp /= ptau_beta0_plus_one;
    *ptr_rvv = temp;

    /* zeta = zeta * ( rvv / initial_rvv ) */
    *ptr_zeta *= ( temp / initial_rvv );
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_psigma_impl)(
    NS(particle_real_type) const delta,
    NS(particle_real_type) const beta0 ) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_t;

    real_t const delta_beta0 = delta * beta0;

    /* ptau * beta0 = sqrt( delta_beta0^2 + 2 * delta * beta0^2 + 1 ) - 1
     * ptau = psigma * beta0
     * --> psigma = ptau / beta0 = ( ptau * beta0 ) / beta0^2
     * --> psigma = ( sqrt( delta_beta0^2 + 2 * delta * beta0^2 + 1 ) - 1 )
     *            / beta0^2
     * --> psigma = ( sqrt( temp ) - 1.0 ) / beta0^2  with
     *     temp   = sqrt( delta_beta0^2 + 2 * delta * beta0^2 + 1 )  */

    real_t const temp = delta_beta0 * delta_beta0 +
        ( real_t )2.0 * delta_beta0 * beta0 + ( real_t )1.0;

    SIXTRL_ASSERT( beta0 >  ( real_t )0.0 );
    SIXTRL_ASSERT( beta0 <= ( real_t )1.0 );
    SIXTRL_ASSERT( temp  >  ( real_t )0.0 );

    return ( NS(sqrt)( temp ) - ( real_t )1.0 ) / ( beta0 * beta0 );
}

SIXTRL_INLINE void NS(Particle_update_psigma_impl)(
    NS(particle_real_type) const psigma, NS(particle_real_type) const beta0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_delta,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_psigma,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rpp,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rvv
) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_t;

    real_t const ptau = psigma * beta0;
    real_t const ptau_beta0_plus_one = ptau * beta0 + ( real_t )1.0;
    real_t delta_plus_one = ptau * ptau + ( real_t )2.0 * psigma + ( real_t )1.0;

    SIXTRL_ASSERT( ptr_delta  != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_psigma != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_rpp != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_rvv != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( beta0 >  ( real_t )0 );
    SIXTRL_ASSERT( beta0 <= ( real_t )1 );
    SIXTRL_ASSERT( delta_plus_one > ( real_t )0.0 );

    delta_plus_one = NS(sqrt)( delta_plus_one );

    SIXTRL_ASSERT( ptau_beta0_plus_one >= ( real_t )0.0 );
    *ptr_delta = delta_plus_one - ( real_t )1.0;
    *ptr_psigma = psigma;
    *ptr_rpp = ( real_t )1.0 / delta_plus_one;
    *ptr_rvv = delta_plus_one / ptau_beta0_plus_one;
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_ptau_impl)(
    NS(particle_real_type) const delta,
    NS(particle_real_type) const beta0 ) SIXTRL_NOEXCEPT {
    return NS(Particle_psigma_impl)( delta, beta0 ) * beta0;
}

SIXTRL_INLINE void NS(Particle_update_ptau_impl)(
    NS(particle_real_type) const ptau, NS(particle_real_type) const beta0,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_delta,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_psigma,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rpp,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT ptr_rvv
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( beta0 > ( NS(particle_real_type) )0.0 );
    NS(Particle_update_psigma_impl)( ptau / beta0, beta0,
        ptr_delta, ptr_psigma, ptr_rpp, ptr_rvv );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_beta_impl)(
    NS(particle_real_type) const beta0, NS(particle_real_type) const rvv
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( beta0 >= ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( beta0 <= ( NS(particle_real_type) )1.0 );
    return beta0 * rvv;
}

SIXTRL_INLINE NS(particle_real_type) NS(Particle_gamma_impl)(
    NS(particle_real_type) const beta0, NS(particle_real_type) const rvv
) SIXTRL_NOEXCEPT {
    NS(particle_real_type) const beta = beta0 * rvv;
    SIXTRL_ASSERT( beta0 >= ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( beta0 <= ( NS(particle_real_type) )1.0 );
    SIXTRL_ASSERT( beta  >= ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( beta  <  ( NS(particle_real_type) )1.0 );
    SIXTRL_ASSERT( ( NS(particle_real_type) )1.0 - beta * beta >
                   ( NS(particle_real_type) )0.0 );

    return ( NS(particle_real_type) )1.0 / NS(sqrt)(
           ( NS(particle_real_type) )1.0 - beta * beta );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_mass_ratio_impl)(
    NS(particle_real_type) const charge_ratio,
    NS(particle_real_type) const chi ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( NS(abs)( chi ) > ( NS(particle_real_type) )0. );
    return charge_ratio / chi; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_charge_impl)(
    NS(particle_real_type) const charge_ratio,
    NS(particle_real_type) const charge0 ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( NS(abs)( charge0 ) > ( NS(particle_real_type) )0.0 );
    return charge0 * charge_ratio; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_mass_impl)(
    NS(particle_real_type) const charge_ratio, NS(particle_real_type) const chi,
    NS(particle_real_type) const mass0 ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mass0 > ( NS(particle_real_type) )0.0 );
    return NS(Particle_mass_ratio_impl)( charge_ratio, chi ) * mass0; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(Particles_copy_real_field_impl)(
    SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_real_type)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_real_type) const* SIXTRL_RESTRICT src,
    NS(particles_num_type) src_idx,
    NS(particles_num_type) const src_idx_end,
    NS(particles_num_type) dst_idx,
    NS(particles_num_type) const stride ) SIXTRL_NOEXCEPT {

    SIXTRL_ASSERT( dest != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( src  != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( dest != src );
    SIXTRL_ASSERT( stride >= ( NS(particles_num_type) )1u );
    SIXTRL_ASSERT( src_idx <= src_idx_end );

    for( ; src_idx < src_idx_end ; src_idx += stride, dst_idx += stride )
    {
        dest[ dst_idx ] = src[ src_idx ];
    }
}

SIXTRL_INLINE void NS(Particles_copy_index_field_impl)(
    SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_index_type) const* SIXTRL_RESTRICT src,
    NS(particles_num_type) src_idx,
    NS(particles_num_type) const src_idx_end,
    NS(particles_num_type) dst_idx,
    NS(particles_num_type) const stride ) SIXTRL_NOEXCEPT {

    SIXTRL_ASSERT( dest != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( src  != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( dest != src );
    SIXTRL_ASSERT( stride >= ( NS(particles_num_type) )1u );
    SIXTRL_ASSERT( src_idx <= src_idx_end );

    for( ; src_idx < src_idx_end ; src_idx += stride, dst_idx += stride )
    {
        dest[ dst_idx ] = src[ src_idx ];
    }
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_HELPER_C99_H__ */
