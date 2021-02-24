#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_RFMULTIPOLE_TRACK_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_RFMULTIPOLE_TRACK_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/rf_multipole/rf_multipole.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN void NS(RFMultipole_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(RFMultipole_track_particle_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */
/* =====        Implementation of Inline functions and methods         ===== */
/* ========================================================================= */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/physics_constants.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE void NS(RFMultipole_track_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_type;
    real_type const k = ( real_type )2. * NS(MathConst_pi)() *
                        NS(RFMultipole_frequency)( mp ) /
                        NS(PhysConst_clight)();

    real_type const k_tau  = k * NS(Particle_tau)( p );
    real_type const charge = NS(Particle_charge0)( p ) *
                             NS(Particle_charge_ratio)( p ) *
                             NS(PhysConst_charge0)();

    real_type temp= NS(RFMultipole_lag)( mp ) * NS(MathConst_deg2rad)() - k_tau;
    real_type d_energy = charge * NS(RFMultipole_voltage)( mp ) * sin( temp );


    real_type d_px         = ( real_type )0.0;
    real_type d_py         = ( real_type )0.0;
    real_type d_ptr        = ( real_type )0.0;
    real_type z_re         = ( real_type )1.0;
    real_type z_im         = ( real_type )0.0;

    real_type bal_n        = ( real_type )0.0;
    real_type bal_s        = ( real_type )0.0;

    real_type cos_phase_n  = ( real_type )0.0;
    real_type cos_phase_s  = ( real_type )0.0;
    real_type sin_phase_n  = ( real_type )0.0;
    real_type sin_phase_s  = ( real_type )0.0;

    NS(be_order_type) const order = NS(RFMultipole_order)( mp );

    for( NS(be_order_type) jj = 0 ; jj <= order ; jj++ ) {
        temp = NS(MathConst_deg2rad)() * NS(RFMultipole_phase_n)(mp,jj) - k_tau;
        cos_phase_n = cos( temp );
        sin_phase_n = sin( temp );

        temp = NS(MathConst_deg2rad)() * NS(RFMultipole_phase_s)(mp,jj) - k_tau;
        cos_phase_s = cos( temp );
        sin_phase_s = sin( temp );

        bal_n  = NS(RFMultipole_bal)( mp, 2 * jj );
        bal_s  = NS(RFMultipole_bal)( mp, 2 * jj + 1 );

        d_px  += cos_phase_n * ( bal_n * z_re ) - cos_phase_s * ( bal_s * z_im );
        d_py  += cos_phase_s * ( bal_s * z_re ) + cos_phase_n * ( bal_n * z_im );

        temp   = z_re * NS(Particle_x)( p ) - z_im * NS(Particle_y)( p );
        z_im   = z_im * NS(Particle_x)( p ) + z_re * NS(Particle_y)( p );
        z_re   = temp;
        d_ptr += sin_phase_n * ( bal_n * z_re ) - sin_phase_s * ( bal_s * z_im );
    }

    d_energy -= charge * ( k * d_ptr * NS(Particle_p0c)( p ) );
    d_px *= -NS(Particle_chi)( p );
    d_py *=  NS(Particle_chi)( p );

    NS(Particle_add_to_px)( p, d_px );
    NS(Particle_add_to_py)( p, d_py );
    NS(Particle_add_to_energy)( p, d_energy );
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_RFMULTIPOLE_TRACK_C99_H__ */
