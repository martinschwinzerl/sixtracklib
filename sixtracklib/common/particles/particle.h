#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_C99_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #if defined( __cplusplus )
        #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

typedef struct NS(Particle)
{
    NS(particle_real_t) x             SIXTRL_ALIGN( 8 );
    NS(particle_real_t) px            SIXTRL_ALIGN( 8 );
    NS(particle_real_t) y             SIXTRL_ALIGN( 8 );
    NS(particle_real_t) py            SIXTRL_ALIGN( 8 );
    NS(particle_real_t) zeta          SIXTRL_ALIGN( 8 );
    NS(particle_real_t) delta         SIXTRL_ALIGN( 8 );
    NS(particle_real_t) psigma        SIXTRL_ALIGN( 8 );

    NS(particle_index_t) state        SIXTRL_ALIGN( 8 );
    NS(particle_index_t) at_element   SIXTRL_ALIGN( 8 );
    NS(particle_index_t) at_turn      SIXTRL_ALIGN( 8 );
    NS(particle_index_t) id           SIXTRL_ALIGN( 8 );

    NS(particle_real_t) s             SIXTRL_ALIGN( 8 );
    NS(particle_real_t) rvv           SIXTRL_ALIGN( 8 );
    NS(particle_real_t) rpp           SIXTRL_ALIGN( 8 );
    NS(particle_real_t) chi           SIXTRL_ALIGN( 8 );
    NS(particle_real_t) charge_ratio  SIXTRL_ALIGN( 8 );

    NS(particle_real_t) charge0       SIXTRL_ALIGN( 8 );
    NS(particle_real_t) mass0         SIXTRL_ALIGN( 8 );
    NS(particle_real_t) beta0         SIXTRL_ALIGN( 8 );
    NS(particle_real_t) gamma0        SIXTRL_ALIGN( 8 );
    NS(particle_real_t) pc0           SIXTRL_ALIGN( 8 );
}
NS(Particle);

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
NS(Particle_preset)( SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p )SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_pc0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_beta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_gamma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_mass_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_mass)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_charge)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_energy0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t) NS(Particle_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t) NS(Particle_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t) NS(Particle_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t) NS(Particle_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_not_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* ========================================================================== */

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const x ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_x ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const y ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_y ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const px ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_px ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_px ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const py ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_py ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_py ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const zeta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_zeta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_zeta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_delta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_delta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const psigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_psigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_psigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const s ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_s ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const rvv ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_rvv ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const rpp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_rpp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const chi ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_chi ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const charge_ratio ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_charge_ratio ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const charge0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const mass0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const beta0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const gamma0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_pc0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const pc0 ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const state ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const at_element ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_increment_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const at_element ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const at_turn ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_increment_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const at_turn ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const id ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

/* TODO: Implement Particle_set_energy() function */

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_energy ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

/* TODO: Implement a Particle_mark_as_lost() function which
 *       generates the state from a supplied logic_t expression */

SIXTRL_STATIC SIXTRL_FN void NS(Particle_mark_as_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;


#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if !defined( __cplusplus )
        #include <math.h>
    #else /* if defined( __cplusplus ) */
        #include <cmath>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus )
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && C++ */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataCApiTypeTraits< ::NS(Particle) >
    {
        typedef ::NS(Particle) c_api_t;
    };
}
#endif /* defined( __cplusplus ) */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */


SIXTRL_INLINE SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
NS(Particle_preset)( SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    if( p != SIXTRL_NULLPTR )
    {
        typedef NS(particle_real_t)  real_t;
        typedef NS(particle_index_t) index_t;

        NS(Particle_set_x)( p, ( real_t )0.0 );
        NS(Particle_set_px)( p, ( real_t )0.0 );
        NS(Particle_set_y)( p, ( real_t )0.0 );
        NS(Particle_set_py)( p, ( real_t )0.0 );
        NS(Particle_set_zeta)( p, ( real_t )0.0 );
        NS(Particle_set_delta)( p, ( real_t )0.0 );
        NS(Particle_set_psigma)( p, ( real_t )0.0 );

        NS(Particle_set_state)( p, ( index_t )1 );
        NS(Particle_set_at_element)( p, ( index_t )0 );
        NS(Particle_set_at_turn)( p, ( index_t )0 );
        NS(Particle_set_id)( p, ( index_t )0 );

        NS(Particle_set_s)( p, ( real_t )0 );
        NS(Particle_set_rvv)( p, ( real_t )1 );
        NS(Particle_set_rpp)( p, ( real_t )1 );
        NS(Particle_set_chi)( p, ( real_t )1 );
        NS(Particle_set_charge_ratio)( p, ( real_t )1 );

        /* TODO: Use physical constants here for presetting! */

        NS(Particle_set_charge0)( p, ( real_t )1 );
        NS(Particle_set_mass0)( p, ( real_t )0 );
        NS(Particle_set_beta0)( p, ( real_t )0 );
        NS(Particle_set_gamma0)( p, ( real_t )1 );
        NS(Particle_set_pc0)( p, ( real_t )0 );
    }

    return p;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->x;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->px;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->y;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->py;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->zeta;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->delta;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p )SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->psigma;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->s >= ( NS(particle_real_t) )0.0 );

    return p->s;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->rvv >= ( NS(particle_real_t) )0.0 );

    return p->rvv;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->rpp;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->chi;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->chi;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->charge0;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->mass0 >= ( NS(particle_real_t) )0.0 );
    return p->mass0;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->beta0 >= ( NS(particle_real_t) )0.0 );
    SIXTRL_ASSERT( p->beta0 <= ( NS(particle_real_t) )1.0 );

    return p->beta0;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->gamma0 >= ( NS(particle_real_t ) )1.0 );
    return p->gamma0;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_pc0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->pc0;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->rvv > ( NS(particle_real_t) )0.0 );
    return p->zeta / p->rvv;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->rvv   >  ( NS(particle_real_t) )0.0 );
    SIXTRL_ASSERT( p->beta0 >  ( NS(particle_real_t) )0.0 );
    SIXTRL_ASSERT( p->beta0 <= ( NS(particle_real_t) )1.0 );

    return p->zeta / ( p->rvv * p->beta0 );
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;

    #if defined( __cplusplus ) && !defined( _GPUCODE )
    using std::sqrt;
    #endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

    real_t const beta0       = NS(Particle_beta0)( p );
    real_t const delta_beta0 = NS(Particle_delta)( p ) * beta0;
    real_t const ptau_beta0  = sqrt( delta_beta0 * delta_beta0 +
        ( real_t )2.0 * delta_beta0 + ( real_t )1.0 ) - ( real_t )1.0;

    SIXTRL_ASSERT( beta0 >  ( real_t )0.0 );
    SIXTRL_ASSERT( beta0 <= ( real_t )1.0 );
    SIXTRL_ASSERT( ( ( real_t )2.0 * delta_beta0 >= ( real_t )0.0 ) ||
                   ( ( delta_beta0 * delta_beta0 + ( real_t )1.0 ) >=
                     ( real_t )-2.0 * delta_beta0 ) );

    return ptau_beta0 / beta0;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_beta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p )  SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->rvv * p->beta0;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_gamma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    #if defined( __cplusplus ) && !defined( _GPUCODE )
    using std::sqrt;
    #endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

    NS(particle_real_t) const beta = NS(Particle_beta)( p );

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( beta >= ( NS(particle_real_t) )0.0 );
    SIXTRL_ASSERT( beta <  ( NS(particle_real_t) )1.0 );

    return ( NS(particle_real_t) )1.0 / sqrt(
        ( NS(particle_real_t) )1.0 - beta * beta );
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_mass_ratio)( SIXTRL_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ( p->chi >= ( NS(particle_real_t) )+1e-16 ) ||
                   ( p->chi <= ( NS(particle_real_t) )-1e-16 ) );

    return p->charge_ratio / p->chi;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_mass)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    return NS(Particle_mass0)( p ) * NS(Particle_mass_ratio)( p );
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_charge)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    return NS(Particle_charge0)( p ) * NS(Particle_charge_ratio)( p );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_energy0)( SIXTRL_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    #if defined( __cplusplus ) && !defined( _GPUCODE )
    using std::sqrt;
    #endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return sqrt( p->pc0 * p->pc0 + p->mass0 * p->mass0 );
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    return ( NS(Particle_psigma)( p ) * NS(Particle_beta0)( p ) *
             NS(Particle_pc0)( p ) ) +
           ( NS(Particle_energy0)( p ) * NS(Particle_mass_ratio)( p ) );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_index_t) NS(Particle_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->id;
}

SIXTRL_INLINE NS(particle_index_t) NS(Particle_at_element)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->at_element;
}

SIXTRL_INLINE NS(particle_index_t) NS(Particle_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->at_turn;
}

SIXTRL_INLINE NS(particle_index_t) NS(Particle_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->state;
}

SIXTRL_INLINE bool NS(Particle_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( p->state != ( NS(particle_index_t) )1 );
}

SIXTRL_INLINE bool NS(Particle_not_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( p->state == ( NS(particle_index_t) )1 );
}

/* ========================================================================== */

SIXTRL_INLINE void NS(Particle_set_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const x ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->x = x;
}

SIXTRL_INLINE void NS(Particle_add_to_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_x ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->x += delta_x;
}

SIXTRL_INLINE void NS(Particle_set_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const y ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->y = y;
}

SIXTRL_INLINE void NS(Particle_add_to_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_y ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->y += delta_y;
}

SIXTRL_INLINE void NS(Particle_set_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const px ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->px = px;
}

SIXTRL_INLINE void NS(Particle_add_to_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_px ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->px += delta_px;
}

SIXTRL_INLINE void NS(Particle_scale_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_px ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->px *= factor_px;
}

SIXTRL_INLINE void NS(Particle_set_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const py ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->py = py;
}

SIXTRL_INLINE void NS(Particle_add_to_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_py ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->py += delta_py;
}

SIXTRL_INLINE void NS(Particle_scale_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_py ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->py *= factor_py;
}

SIXTRL_INLINE void NS(Particle_set_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const zeta ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->zeta = zeta;
}

SIXTRL_INLINE void NS(Particle_add_to_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_zeta ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->zeta += delta_zeta;
}

SIXTRL_INLINE void NS(Particle_scale_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_zeta ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->zeta *= factor_zeta;
}

SIXTRL_INLINE void NS(Particle_set_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->delta = delta;
}

SIXTRL_INLINE void NS(Particle_add_to_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_delta ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->delta += delta_delta;
}

SIXTRL_INLINE void NS(Particle_scale_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_delta ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->delta *= factor_delta;
}

SIXTRL_INLINE void NS(Particle_set_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const psigma ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->psigma = psigma;
}

SIXTRL_INLINE void NS(Particle_add_to_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_psigma ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->psigma += delta_psigma;
}

SIXTRL_INLINE void NS(Particle_scale_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_psigma ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->psigma *= factor_psigma;
}

SIXTRL_INLINE void NS(Particle_set_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const s ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->s = s;
}

SIXTRL_INLINE void NS(Particle_add_to_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_s ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->s += delta_s;
}

SIXTRL_INLINE void NS(Particle_set_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const rvv ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->rvv = rvv;
}

SIXTRL_INLINE void NS(Particle_scale_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_rvv ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->rvv *= factor_rvv;
}

SIXTRL_INLINE void NS(Particle_set_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const rpp ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->rpp = rpp;
}

SIXTRL_INLINE void NS(Particle_scale_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_rpp ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->rpp *= factor_rpp;
}

SIXTRL_INLINE void NS(Particle_set_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const chi ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->chi = chi;
}

SIXTRL_INLINE void NS(Particle_scale_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_chi ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->chi *= factor_chi;
}

SIXTRL_INLINE void NS(Particle_set_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const charge_ratio ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->charge_ratio = charge_ratio;
}

SIXTRL_INLINE void NS(Particle_scale_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const factor_charge_ratio ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->charge_ratio *= factor_charge_ratio;
}

SIXTRL_INLINE void NS(Particle_set_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const charge0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->charge0 = charge0;
}

SIXTRL_INLINE void NS(Particle_set_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const mass0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->mass0 = mass0;
}

SIXTRL_INLINE void NS(Particle_set_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const beta0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->beta0 = beta0;
}

SIXTRL_INLINE void NS(Particle_set_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const gamma0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->gamma0 = gamma0;
}

SIXTRL_INLINE void NS(Particle_set_pc0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const pc0 ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->pc0 = pc0;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

SIXTRL_INLINE void NS(Particle_set_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const state ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->state = state;
}

SIXTRL_INLINE void NS(Particle_set_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const at_element ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->at_element = at_element;
}

SIXTRL_INLINE void NS(Particle_increment_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const at_element ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    ++p->at_element;
}

SIXTRL_INLINE void NS(Particle_set_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const at_turn ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->at_turn = at_turn;
}

SIXTRL_INLINE void NS(Particle_increment_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const at_turn ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    ++p->at_turn;
}

SIXTRL_INLINE void NS(Particle_set_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_t) const id ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->id = id;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

/* TODO: Implement Particle_set_energy() function */

SIXTRL_INLINE void NS(Particle_add_to_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_energy ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;

    #if defined( __cplusplus ) && !defined( _GPUCODE )
    using std::sqrt;
    #endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

    real_t const beta0 = NS(Particle_beta0)( p );
    real_t const delta_beta0 = NS(Particle_delta)( p ) * beta0;

    real_t const ptau_beta0 = delta_energy / NS(Particle_energy0)( p )
        + sqrt( delta_beta0 * delta_beta0 + ( real_t )1.0 +
            ( real_t )2.0 * delta_beta0 * beta0 ) - ( real_t )1.0;

    real_t const ptau = ptau_beta0 / beta0;
    real_t const psigma = ptau / beta0;
    real_t const delta = sqrt( ptau * ptau +
        ( real_t )2.0 * psigma + ( real_t )1.0 ) - ( real_t )1.0;

    real_t const one_plus_delta = delta + ( real_t )1.0;
    real_t const rvv = one_plus_delta / ( ( real_t )1.0 + ptau_beta0 );

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->rvv   > ( real_t )1e-16 );
    SIXTRL_ASSERT( p->beta0 > ( real_t )0.0   );
    SIXTRL_ASSERT( ( delta_beta0 >= ( real_t )0.0 ) ||
                   ( ( delta_beta0 * delta_beta0 + ( real_t )1.0 ) >=
                     ( real_t )-2.0 * delta_beta0 * beta0 ) );
    SIXTRL_ASSERT( ( psigma >= ( real_t )0.0 ) ||
                   ( ( ptau * ptau + ( real_t )1.0 ) >=
                     ( real_t )-2.0 * psigma ) );

    SIXTRL_ASSERT( ( ( ptau_beta0 + ( real_t )1.0 ) > ( real_t )+1e-16 ) ||
                   ( ( ptau_beta0 + ( real_t )1.0 ) < ( real_t )-1e-16 ) );

    SIXTRL_ASSERT( ( one_plus_delta > ( real_t )+1e-16 ) ||
                   ( one_plus_delta < ( real_t )-1e-16 ) );

    p->delta  = delta;
    p->psigma = psigma;
    p->zeta  *= rvv / p->rvv;
    p->rvv    = rvv;
    p->rpp    = ( real_t )1.0 / one_plus_delta;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
/* TODO: Implement a Particle_mark_as_lost() function which
 *       generates the state from a supplied logic_t expression */

SIXTRL_INLINE void NS(Particle_mark_as_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->state = ( NS(particle_index_t) )0;
}

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_C99_H__ */
