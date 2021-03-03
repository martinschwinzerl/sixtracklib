#ifndef SIXTRACKLIB_COMMON_PARTICLES_SINGLE_PARTICLE_H__
#define SIXTRACKLIB_COMMON_PARTICLES_SINGLE_PARTICLE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

struct NS(CBuffer);
struct NS(CObjIndex);
struct NS(Particles);

typedef SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) struct NS(SingleParticle)
{
    NS(particle_real_type)  x            SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  y            SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  px           SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  py           SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  zeta         SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  delta        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );

    NS(particle_index_type) state        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_index_type) at_element   SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_index_type) at_turn      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_index_type) id           SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );

    #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
               ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD == 1 )
    NS(particle_real_type)  psigma       SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    #endif /* defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */

    NS(particle_real_type)  rpp          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  rvv          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  chi          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  charge_ratio SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );

    NS(particle_real_type)  charge0      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  mass0        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  beta0        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  gamma0       SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  p0c          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );

    #if defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
               ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
    NS(particle_real_type) s             SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    #endif /* SIXTRL_PARTICLE_USE_S_FIELD */
}
NS(SingleParticle);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(SingleParticleView)
{
    NS(particles_addr_type) pset_addr SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_num_type)  index     SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(SingleParticleView);

#if defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) && \
           ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER == 1 )
    typedef NS(SingleParticleView) NS(Particle);
#else  /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    typedef NS(SingleParticle) NS(Particle);
#endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type)
NS(Particle_cobj_type_id)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(Particle_cobj_num_dataptrs)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(Particle_cobj_actual_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(Particle_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(Particle_cobj_required_num_bytes)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_ARGPTR_DEC NS(SingleParticleView)*
NS(SingleParticleView_preset)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(SingleParticleView)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SingleParticleView_clear)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(SingleParticleView)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SingleParticleView_init)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(SingleParticleView)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const pset_addr,
    NS(particle_index_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SingleParticleView_init_from_pset)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(SingleParticleView)* SIXTRL_RESTRICT p,
    SIXTRL_PARTICLES_ARGPTR_DEC const struct NS(Particles) *const
        SIXTRL_RESTRICT pset,
    NS(particle_index_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC struct NS(Particles) const*
NS(SingleParticleView_const_particles)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(SingleParticleView)
        *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC struct NS(Particles)*
NS(SingleParticleView_particles)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(SingleParticleView)
        *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
NS(Particle_preset)( SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particle_clear)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particle_clear_before_copy_from_pset)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particle_init)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
       NS(particle_real_type)  const x,    NS(particle_real_type)  const y,
    NS(particle_real_type)  const px,      NS(particle_real_type)  const py,
    NS(particle_real_type)  const zeta,    NS(particle_real_type)  const delta,
    NS(particle_index_type) const state,
    NS(particle_index_type) const at_element,
    NS(particle_index_type) const at_turn, NS(particle_index_type) const id,
    NS(particle_real_type)  const psigma,  NS(particle_real_type)  const rpp,
    NS(particle_real_type)  const rvv,     NS(particle_real_type)  const chi,
    NS(particle_real_type)  const charge_ratio,
    NS(particle_real_type)  const charge0, NS(particle_real_type)  const mass0,
    NS(particle_real_type)  const beta0,   NS(particle_real_type)  const gamma0,
    NS(particle_real_type)  const p0c,     NS(particle_real_type)  const s
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particle_init_from_charge0_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const third_param,
    NS(ParticleInitModeEnum) const init_mode,
    NS(particle_real_type) const delta ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_x)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) x ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) dx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_subtract_from_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) dx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) x_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_y)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) y ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_y ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_subtract_from_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_y ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) y_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_px)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) px ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_px ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_subtract_from_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_px ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) px_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_py)(
    void  ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) py ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_dy ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_subtract_from_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_py ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) py_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_zeta)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) zeta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_zeta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_subtract_from_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_zeta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) zeta_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_delta)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) delta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_update_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) delta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_delta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_subtract_from_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_delta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) delta_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_psigma)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) psigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_update_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) psigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_psigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_subtract_from_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_psigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) psigma_factor ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_rpp)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) rpp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) rpp_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_rvv)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) rvv ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) rvv_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_chi)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) chi ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) chi_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type)
    NS(Particle_default_charge_ratio)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) charge_ratio ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) charge_ratio_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_s)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) s ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_s ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_subtract_from_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_s ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_charge0)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) charge0 ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_mass0)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) mass0 ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_beta0)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) beta0 ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_gamma0)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) gamma0 ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_p0c)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_p0c)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_p0c)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) p0c ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particle_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particle_default_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) const particle_id ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particle_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particle_default_at_element)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) const at_element ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_increment_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particle_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particle_default_at_turn)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) const at_element ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_increment_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_finish_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) const start_at_element ) SIXTRL_NOEXCEPT;
/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particle_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particle_default_state)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) const at_element ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_is_active)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_is_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_is_not_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_mark_as_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_keep_active_if_not_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) const new_state ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_beta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_gamma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_charge)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_mass)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_mass_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_sigma)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) sigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_sigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_subtract_from_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_sigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) sigma_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_tau)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) tau ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_update_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const tau ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_tau ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_subtract_from_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_tau ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) tau_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_default_ptau)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_set_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const ptau ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_update_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const ptau ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const d_ptau ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_subtract_from_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const d_ptau ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_scale_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const ptau_factor ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_energy0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_update_energy0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const energy0 ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particle_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_update_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const energy ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_to_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const d_energy ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particle_copy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT source ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_particle)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle) const*
NS(Particle_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const
    struct NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    struct NS(CObjIndex)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle) const*
NS(Particle_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const index,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const index,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle) const*
NS(Particle_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT buf,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buf,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN void NS(Particle_calculate_difference)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(Particle_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Particle_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Particle_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Particle_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Particle_cobj_required_num_bytes_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle) const*
NS(Particle_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buf,
    NS(cobj_size_type) const index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particle_calculate_difference_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsTrivialHandleSizeTraits< ::NS(SingleParticle) >
    {
        #if ( defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) ) && \
                     ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD == 1 ) && \
            ( defined( SIXTRL_PARTICLE_USE_S_FIELD ) ) && \
                     ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
        static constexpr bool HAS_TRIVIAL_HANDLE_SIZE = true;
        #else /* actual handle size < reserved handle size */
        static constexpr bool HAS_TRIVIAL_HANDLE_SIZE = false;
        #endif /* SIXTRL_PARTICLE_USE_PSIGMA_FIELD &&
                  SIXTRL_PARTICLE_USE_S_FIELD */
    };

    template<> struct CObjectsTraits< ::NS(SingleParticle) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_SINGLE_PARTICLE;
    };

    template<> struct CObjectsReservedHandleSizeTraits< ::NS(SingleParticle) >
    {
        SIXTRL_FN static cobj_size_type HANDLE_SIZE(
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Particle_cobj_reserved_handle_size)( slot_size ); }
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_SINGLE_PARTICLE > {
            typedef ::NS(SingleParticle) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_helper.h"
    #include "sixtracklib/common/particles/particles.h"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/physics_constants.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE )
    #include "sixtracklib/common/particles/particle_cobj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(Particle_cobj_type_id)() SIXTRL_NOEXCEPT {
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return ( NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_SINGLE_PARTICLE;
    #else
    return ( NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_ILLEGAL;
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE NS(cobj_size_type) NS(Particle_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(Particle_cobj_actual_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
        if( slot_size == ( NS(cobj_size_type) )0u )
            slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
        NS(cobj_size_type) const num_bytes = NS(CObjFlatBuffer_slot_based_size)(
            sizeof( NS(SingleParticle) ), slot_size );
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
        NS(cobj_size_type) const num_bytes = ( NS(cobj_size_type) )0u;
        ( void )slot_size;
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return num_bytes; }

SIXTRL_INLINE NS(cobj_size_type) NS(Particle_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    NS(size_type) num_bytes = ( NS(size_type) )0u;
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
        if( slot_size == ( NS(cobj_size_type) )0u )
            slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
        num_bytes = NS(Particle_cobj_actual_handle_size)( slot_size );

        #if !defined( SIXTRL_PARTICLE_USE_S_FIELD ) || \
                    ( SIXTRL_PARTICLE_USE_S_FIELD != 1 )
            num_bytes += NS(CObjFlatBuffer_slot_based_size)(
                sizeof( NS(particle_real_type) ), slot_size );
        #endif /* !defined( SIXTRL_PARTICLE_USE_S_FIELD ) */

        #if !defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) || \
                    ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD != 1 )
            num_bytes += NS(CObjFlatBuffer_slot_based_size)(
                sizeof( NS(particle_real_type) ), slot_size );
        #endif /* !defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
        num_bytes = NS(Particle_cobj_actual_handle_size)( slot_size );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return num_bytes; }

SIXTRL_INLINE NS(cobj_size_type) NS(Particle_cobj_required_num_bytes)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( p ), NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( NS(Particle_cobj_num_dataptrs)() == ( NS(cobj_size_type) )0 );
    return NS(Particle_cobj_reserved_handle_size)( slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_PARTICLE_ARGPTR_DEC NS(SingleParticleView)*
NS(SingleParticleView_preset)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(SingleParticleView)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    if( p != SIXTRL_NULLPTR ) NS(SingleParticleView_clear)( p );
    return p; }

SIXTRL_INLINE NS(status_type) NS(SingleParticleView_clear)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(SingleParticleView)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return NS(SingleParticleView_init_from_pset)( p,
    SIXTRL_NULLPTR, ( NS(particles_num_type) )0u ); }

SIXTRL_INLINE NS(status_type) NS(SingleParticleView_init_from_pset)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(SingleParticleView)* SIXTRL_RESTRICT p,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    NS(particle_index_type) const index ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( p != SIXTRL_NULLPTR )
    {
        p->pset_addr = ( NS(particles_addr_type) )SIXTRL_NULL_ADDR;
        p->index = ( NS(particles_num_type) )0u;

        if( ( pset != SIXTRL_NULLPTR ) &&
            ( pset->max_num_particles > index ) )
        {
            p->pset_addr = ( NS(particles_addr_type) )( uintptr_t )pset;
            p->index = index;
            status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        }
        else if( ( pset == SIXTRL_NULLPTR ) &&
                 ( index == ( NS(particle_index_type) )0u ) )
        {
            status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        }
    }
    return status;
}

SIXTRL_INLINE NS(status_type) NS(SingleParticleView_init)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(SingleParticleView)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const pset_addr,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return NS(SingleParticleView_init_from_pset)( p,
        ( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* )(
            uintptr_t )pset_addr, index ); }

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const*
NS(SingleParticleView_const_particles)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(SingleParticleView)
        *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* )( uintptr_t
        )p->pset_addr; }

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(SingleParticleView_particles)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(SingleParticleView)
        *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* )( uintptr_t
        )p->pset_addr; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* NS(Particle_preset)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    if( p != SIXTRL_NULLPTR ) NS(Particle_clear)( p ); return p;
}

SIXTRL_INLINE NS(status_type) NS(Particle_clear)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return NS(Particle_init)( p,
        NS(Particle_default_x)(),       NS(Particle_default_y)(),
        NS(Particle_default_px)(),      NS(Particle_default_py)(),
        NS(Particle_default_zeta)(),    NS(Particle_default_delta)(),
        NS(Particle_default_state)(),   NS(Particle_default_at_element)(),
        NS(Particle_default_at_turn)(), NS(Particle_default_id)(),
        NS(Particle_default_psigma)(),  NS(Particle_default_rpp)(),
        NS(Particle_default_rvv)(),     NS(Particle_default_chi)(),
        NS(Particle_default_charge_ratio)(),
        NS(Particle_default_charge0)(), NS(Particle_default_mass0)(),
        NS(Particle_default_beta0)(),   NS(Particle_default_gamma0)(),
        NS(Particle_default_p0c)(),     NS(Particle_default_s)() );
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(SingleParticleView_clear)( p );

    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE NS(status_type) NS(Particle_clear_before_copy_from_pset)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(SingleParticleView_clear)( p );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE NS(status_type) NS(Particle_init)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type)  const x,       NS(particle_real_type)  const y,
    NS(particle_real_type)  const px,      NS(particle_real_type)  const py,
    NS(particle_real_type)  const zeta,    NS(particle_real_type)  const delta,
    NS(particle_index_type) const state,
    NS(particle_index_type) const at_element,
    NS(particle_index_type) const at_turn, NS(particle_index_type) const id,
    NS(particle_real_type)  const psigma,  NS(particle_real_type)  const rpp,
    NS(particle_real_type)  const rvv,     NS(particle_real_type)  const chi,
    NS(particle_real_type)  const charge_ratio,
    NS(particle_real_type)  const charge0, NS(particle_real_type)  const mass0,
    NS(particle_real_type)  const beta0,   NS(particle_real_type)  const gamma0,
    NS(particle_real_type)  const p0c,     NS(particle_real_type)  const s
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( p != SIXTRL_NULLPTR )
    {
        NS(Particle_set_x)( p, x );
        NS(Particle_set_y)( p, y );
        NS(Particle_set_px)( p, px );
        NS(Particle_set_py)( p, py );
        NS(Particle_set_zeta)( p, zeta );
        NS(Particle_set_delta)( p, delta );
        NS(Particle_set_state)( p, state );
        NS(Particle_set_at_element)( p, at_element );
        NS(Particle_set_at_turn)( p, at_turn );
        NS(Particle_set_id)( p, id );

        #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD == 1 )
        NS(Particle_set_psigma)( p, psigma );
        #endif /* defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */

        NS(Particle_set_rpp)( p, rpp );
        NS(Particle_set_rvv)( p, rvv );
        NS(Particle_set_chi)( p, chi );
        NS(Particle_set_charge_ratio)( p, charge_ratio );

        NS(Particle_set_charge0)( p, charge0 );
        NS(Particle_set_mass0)( p, mass0 );
        NS(Particle_set_beta0)( p, beta0 );
        NS(Particle_set_gamma0)( p, gamma0 );
        NS(Particle_set_p0c)( p, p0c );

        #if defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
        NS(Particle_set_s)( p, s );
        #endif /* SIXTRL_PARTICLE_USE_S_FIELD */
        status = SIXTRL_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(status_type) NS(Particle_init_from_charge0_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const third_param,
    NS(ParticleInitModeEnum) const init_mode,
    NS(particle_real_type) const delta ) SIXTRL_NOEXCEPT {

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( p == SIXTRL_NULLPTR ) return status;

    NS(Particle_set_charge0)( p, charge0 );
    NS(Particle_set_mass0)( p, mass0 );

    switch( init_mode )
    {
        case NS(PARTICLE_INIT_MODE_CHARGE0_MASS0_BETA0):
        {
            #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                        ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )

            NS(Particle_gamma0_p0c_from_charge0_mass0_beta0_impl)(
                charge0, mass0, third_param, &p->gamma0, &p->p0c );

            #else /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

            SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) gamma0 =
                ( NS(particle_real_type) )1.0;

            SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) p0c =
                ( NS(particle_real_type) )0.0;

            NS(Particle_gamma0_p0c_from_charge0_mass0_beta0_impl)(
                charge0, mass0, third_param, &gamma0, &p0c );

            NS(Particle_set_gamma0)( p, gamma0 );
            NS(Particle_set_p0c)( p, p0c );

            #endif /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

            NS(Particle_set_beta0)( p, third_param );
            break;
        }

        case NS(PARTICLE_INIT_MODE_CHARGE0_MASS0_GAMMA0):
        {
            #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                        ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )

            NS(Particle_beta0_p0c_from_charge0_mass0_gamma0_impl)(
                charge0, mass0, third_param, &p->beta0, &p->p0c );

            #else /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

            SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) beta0 =
                ( NS(particle_real_type) )0.0;

            SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) p0c =
                ( NS(particle_real_type) )0.0;

            NS(Particle_beta0_p0c_from_charge0_mass0_gamma0_impl)(
                charge0, mass0, third_param, &beta0, &p0c );

            NS(Particle_set_beta0)( p, beta0 );
            NS(Particle_set_p0c)( p, p0c );

            #endif /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

            NS(Particle_set_gamma0)( p, third_param );
            break;
        }

        case NS(PARTICLE_INIT_MODE_CHARGE0_MASS0_P0C):
        {

            #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                        ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )

            NS(Particle_beta0_gamma0_from_charge0_mass0_p0c_impl)(
                charge0, mass0, third_param, &p->beta0, &p->gamma0 );

            #else /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

            SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) beta0 =
                ( NS(particle_real_type) )0.0;

            SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) gamma0 =
                ( NS(particle_real_type) )1.0;

            NS(Particle_beta0_gamma0_from_charge0_mass0_p0c_impl)(
                charge0, mass0, third_param, &beta0, &gamma0 );

            NS(Particle_set_beta0)( p, beta0 );
            NS(Particle_set_gamma0)( p, gamma0 );

            #endif /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
            NS(Particle_set_p0c)( p, third_param );

            break;
        }

        default:
        {
            status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
        }
    };

    if( ( NS(Particle_beta0)(  p ) >= ( NS(particle_real_type) )0.0 ) &&
        ( NS(Particle_beta0)(  p ) <= ( NS(particle_real_type) )1.0 ) &&
        ( NS(Particle_gamma0)( p ) >= ( NS(particle_real_type) )1.0 ) &&
        ( NS(Particle_mass0)(  p ) >  ( NS(particle_real_type) )0.0 ) &&
        ( ( NS(Particle_charge0)(  p ) > ( NS(particle_real_type) )0.0 ) ||
          ( NS(Particle_charge0)(  p ) < ( NS(particle_real_type) )0.0 ) ) )
    {
        NS(Particle_update_delta)( p, delta );

        NS(Particle_set_x)( p, NS(Particle_default_x)() );
        NS(Particle_set_y)( p, NS(Particle_default_y)() );
        NS(Particle_set_px)( p, NS(Particle_default_px)() );
        NS(Particle_set_py)( p, NS(Particle_default_py)() );
        NS(Particle_set_zeta)( p, NS(Particle_default_zeta)() );

        NS(Particle_set_state)( p, NS(Particle_default_state)() );
        NS(Particle_set_at_element)( p, NS(Particle_default_at_element)() );
        NS(Particle_set_at_turn)( p, NS(Particle_default_at_turn)() );
        NS(Particle_set_id)( p, NS(Particle_default_id)() );
        NS(Particle_set_chi)( p, NS(Particle_default_chi)() );
        NS(Particle_set_charge_ratio)( p, NS(Particle_default_charge_ratio)() );
        NS(Particle_set_s)( p, NS(Particle_default_s)() );

        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }

    return status;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_x)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_real_type) )0.; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_x)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->x;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_x)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) x ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->x = x;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_x)( NS(SingleParticleView_particles)( p ), p->index, x );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_add_to_x)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_x ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->x += d_x;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_x)( NS(SingleParticleView_particles)(
        p ), p->index, d_x );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_subtract_from_x)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_x ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->x -= d_x;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_x)( NS(SingleParticleView_particles)(
        p ), p->index, -d_x );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_scale_x)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) x_factor ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->x *= x_factor;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_scale_x)( NS(SingleParticleView_particles)(
        p ), p->index, x_factor );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_y)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(particle_real_type) )0.;
}

SIXTRL_INLINE NS(particle_real_type) NS(Particle_y)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->y;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_y)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) y ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->y = y;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_y)( NS(SingleParticleView_particles)( p ), p->index, y );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_add_to_y)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_y ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->y += d_y;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_y)( NS(SingleParticleView_particles)(
        p ), p->index, d_y );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_subtract_from_y)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_y ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->y -= d_y;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_y)( NS(SingleParticleView_particles)(
        p ), p->index, -d_y );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_scale_y)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) y_factor ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->y *= y_factor;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_scale_y)( NS(SingleParticleView_particles)( p ),
        p->index, y_factor );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_px)() SIXTRL_NOEXCEPT
{
    return ( NS(particle_real_type) )0.;
}

SIXTRL_INLINE NS(particle_real_type) NS(Particle_px)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->px;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_px)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) px ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->px = px;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_px)( NS(SingleParticleView_particles)( p ), p->index, px );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_add_to_px)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_px ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->px += d_px;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_px)( NS(SingleParticleView_particles)(
        p ), p->index, d_px );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_subtract_from_px)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_px ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->px -= d_px;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_px)( NS(SingleParticleView_particles)(
        p ), p->index, -d_px );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_scale_px)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) px_factor ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->px *= px_factor;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_scale_px)( NS(SingleParticleView_particles)( p ),
        p->index, px_factor );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_py)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_real_type) )0.; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_py)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->py;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_py)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) py ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->py = py;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_py)( NS(SingleParticleView_particles)(
        p ), p->index, py );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_add_to_py)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_py ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->py += d_py;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_py)( NS(SingleParticleView_particles)(
        p ), p->index, d_py );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_subtract_from_py)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_py ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->py -= d_py;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_py)( NS(SingleParticleView_particles)(
        p ), p->index, -d_py );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_scale_py)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) py_factor ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->py *= py_factor;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_scale_py)( NS(SingleParticleView_particles)( p ),
        p->index, py_factor );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_zeta)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_real_type) )0.; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_zeta)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->zeta;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_zeta)( NS(SingleParticleView_const_particles)( p ),
        p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) zeta ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->zeta = zeta;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_zeta)( NS(SingleParticleView_particles)( p ),
        p->index, zeta );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_add_to_zeta)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_zeta ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->zeta += d_zeta;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_zeta)( NS(SingleParticleView_particles)( p ),
        p->index, d_zeta );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_subtract_from_zeta)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_zeta ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->zeta -= d_zeta;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_zeta)( NS(SingleParticleView_particles)( p ),
        p->index, -d_zeta );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_scale_zeta)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) zeta_factor ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->zeta *= zeta_factor;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_scale_zeta)( NS(SingleParticleView_particles)( p ),
        p->index, zeta_factor );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_delta)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_real_type) )0.; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_delta)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->delta;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_delta)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) delta ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->delta = delta;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_delta)( NS(SingleParticleView_particles)(
        p ), p->index, delta );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_add_to_delta)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_delta ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->delta += d_delta;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_delta)( NS(SingleParticleView_particles)(
        p ), p->index, d_delta );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_subtract_from_delta)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_delta ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->delta -= d_delta;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_delta)( NS(SingleParticleView_particles)(
        p ), p->index, -d_delta );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_scale_delta)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) delta_factor ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->delta *= delta_factor;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_scale_delta)( NS(SingleParticleView_particles)(
        p ), p->index, delta_factor );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_update_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) delta ) SIXTRL_NOEXCEPT {

    NS(particle_real_type) const delta_plus_one =
        delta + ( NS(particle_real_type) )1.;

    NS(particle_real_type) const beta0 = NS(Particle_beta0)( p );
    NS(particle_real_type) const delta_beta0 = delta * beta0;
    NS(particle_real_type) ptau_beta0_plus_one = delta_beta0 * delta_beta0;

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( beta0 >= ( NS(particle_real_type) )0. );
    SIXTRL_ASSERT( beta0 <= ( NS(particle_real_type) )1. );

    ptau_beta0_plus_one += ( NS(particle_real_type) )2.0  * delta_beta0 * beta0;
    ptau_beta0_plus_one += ( NS(particle_real_type) )1.0;

    SIXTRL_ASSERT( ptau_beta0_plus_one >= ( NS(particle_real_type) )0.0 );
    ptau_beta0_plus_one = NS(sqrt)( ptau_beta0_plus_one );
    SIXTRL_ASSERT( NS(abs)( delta_plus_one ) >= ( NS(particle_real_type) )0.0 );

    NS(Particle_set_delta)( p, delta );
    NS(Particle_set_rpp)( p, ( NS(particle_real_type) )1.0 / delta_plus_one );
    NS(Particle_set_rvv)( p, delta_plus_one / ptau_beta0_plus_one );

    #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
               ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD == 1 )
        NS(Particle_set_psigma)( p, NS(Particle_psigma_impl)( delta, beta0 ) );
    #endif /* defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type)
NS(Particle_default_psigma)( void ) SIXTRL_NOEXCEPT {
    return ( NS(particle_real_type) )0.; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
        #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD == 1 )
            return p->psigma;
        #else /* defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
            return NS(Particle_psigma_impl)(
                NS(Particle_delta)( p ), NS(Particle_beta0)( p ) );
        #endif /* !defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_psigma)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) psigma ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
        #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD == 1 )
            p->psigma = psigma;
        #else /* !defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
            ( void )psigma;
        #endif /* defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_psigma)( NS(SingleParticleView_particles)(
        p ), p->index, psigma );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_add_to_psigma)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_psigma ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
        #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD == 1 )
            p->psigma += d_psigma;
        #else /* !defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
            NS(Particle_update_psigma)( p, NS(Particle_psigma)( p ) + d_psigma );
        #endif /* defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_psigma)( NS(SingleParticleView_particles)(
        p ), p->index, d_psigma );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_subtract_from_psigma)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_psigma ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
        #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD == 1 )
            p->psigma -= d_psigma;
        #else /* !defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
            NS(Particle_update_psigma)( NS(Particle_psigma)( p ) - d_psigma );
        #endif /* !defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_psigma)( NS(SingleParticleView_particles)(
        p ), p->index, -d_psigma );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_scale_psigma)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) psigma_factor ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
        #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD == 1 )
            p->psigma *= psigma_factor;
        #else /* !defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
            NS(Particle_update_psigma)(
                NS(Particle_psigma)( p ) * psigma_factor );
        #endif /* !defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_scale_psigma)( NS(SingleParticleView_particles)(
        p ), p->index, psigma_factor );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_update_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) psigma ) SIXTRL_NOEXCEPT {
    typedef NS(particle_real_type) real_t;

    real_t const beta0 = NS(Particle_beta0)( p );
    real_t const ptau = psigma * beta0;
    real_t const ptau_beta0_plus_one = ptau * beta0 + ( real_t )1.0;
    real_t delta_plus_one = ptau * ptau + ( real_t )2.0 * psigma + ( real_t )1.0;

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( beta0 >= ( real_t )0 );
    SIXTRL_ASSERT( beta0 <= ( real_t )1 );
    SIXTRL_ASSERT( delta_plus_one >= ( real_t )0.0 );

    delta_plus_one = NS(sqrt)( delta_plus_one );

    SIXTRL_ASSERT( ptau_beta0_plus_one >= ( real_t )0.0 );
    SIXTRL_ASSERT( delta_plus_one > ( real_t )0.0 );

    NS(Particle_set_delta)( p, delta_plus_one - ( real_t )1.0 );
    NS(Particle_set_rpp)( p, ( real_t )1.0 / delta_plus_one );
    NS(Particle_set_rvv)( p, delta_plus_one / ptau_beta0_plus_one );
    NS(Particle_set_psigma)( p, psigma );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(particle_real_type)
NS(Particle_default_rpp)( void ) SIXTRL_NOEXCEPT {
    return ( NS(particle_real_type) )1.; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_rpp)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->rpp;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_rpp)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) rpp ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->rpp = rpp;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_rpp)( NS(SingleParticleView_particles)( p ), p->index, rpp );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_scale_rpp)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) rpp_factor ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->rpp *= rpp_factor;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_scale_rpp)( NS(SingleParticleView_particles)(
        p ), p->index, rpp_factor );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type)
NS(Particle_default_rvv)( void ) SIXTRL_NOEXCEPT {
    return ( NS(particle_real_type) )1.; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_rvv)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->rvv;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_rvv)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) rvv ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->rvv = rvv;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_rvv)( NS(SingleParticleView_particles)(
        p ), p->index, rvv );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_scale_rvv)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) rvv_factor ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->rvv *= rvv_factor;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_scale_rvv)( NS(SingleParticleView_particles)(
        p ), p->index, rvv_factor );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type)
NS(Particle_default_chi)( void ) SIXTRL_NOEXCEPT {
    return ( NS(particle_real_type) )1.; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_chi)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->chi;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_chi)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) chi ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->chi = chi;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_chi)( NS(SingleParticleView_particles)(
        p ), p->index, chi );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_scale_chi)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) chi_factor ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->chi *= chi_factor;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_scale_chi)( NS(SingleParticleView_particles)(
        p ), p->index, chi_factor );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type)
NS(Particle_default_charge_ratio)( void ) SIXTRL_NOEXCEPT {
    return ( NS(particle_real_type) )1.; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->charge_ratio;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_charge_ratio)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) charge_ratio ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->charge_ratio = charge_ratio;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_charge_ratio)( NS(SingleParticleView_particles)(
        p ), p->index, charge_ratio );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_scale_charge_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) charge_ratio_factor ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->charge_ratio *= charge_ratio_factor;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_scale_charge_ratio)( NS(SingleParticleView_particles)(
        p ), p->index, charge_ratio_factor );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_s)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_real_type) )0.; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_s)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
        #if defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
            return p->s;
        #else /* !defined( SIXTRL_PARTICLE_USE_S_FIELD ) */
            return NS(Particle_default_s)();
        #endif /* !defined( SIXTRL_PARTICLE_USE_S_FIELD ) */
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_s)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) s ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
        #if defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
            p->s = s;
        #else /* !defined( SIXTRL_PARTICLE_USE_S_FIELD ) */
            ( void )p;
            ( void )s;
        #endif /* !defined( SIXTRL_PARTICLE_USE_S_FIELD ) */
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_s)( NS(SingleParticleView_particles)( p ), p->index, s );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_add_to_s)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_s ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
        #if defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
            p->s += d_s;
        #else /* !defined( SIXTRL_PARTICLE_USE_S_FIELD ) */
            ( void )p;
            ( void )d_s;
        #endif /* !defined( SIXTRL_PARTICLE_USE_S_FIELD ) */
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_s)( NS(SingleParticleView_particles)( p ), p->index, d_s );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_subtract_from_s)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_s ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
        #if defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
            p->s -= d_s;
        #else /* !defined( SIXTRL_PARTICLE_USE_S_FIELD ) */
            ( void )p;
            ( void )d_s;
        #endif /* !defined( SIXTRL_PARTICLE_USE_S_FIELD ) */
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_add_to_s)( NS(SingleParticleView_particles)(
        p ), p->index, -d_s );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type)
NS(Particle_default_charge0)( void ) SIXTRL_NOEXCEPT {
    return NS(PhysConst_charge0)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->charge0;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_charge0)(
        NS(SingleParticleView_const_particles)( p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_charge0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) charge0 ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->charge0 = charge0;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_charge0)( NS(SingleParticleView_particles)(
        p ), p->index, charge0 );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type)
NS(Particle_default_mass0)( void ) SIXTRL_NOEXCEPT {
    return NS(PhysConst_mass_proton_ev)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->mass0;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_mass0)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) mass0 ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->mass0 = mass0;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_mass0)( NS(SingleParticleView_particles)(
        p ), p->index, mass0 );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_beta0)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_real_type) )0.0; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_beta0)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->beta0;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_beta0)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) beta0 ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( beta0 >= ( NS(particle_real_type) )0.0 );
    SIXTRL_ASSERT( beta0 <= ( NS(particle_real_type) )1.0 );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->beta0 = beta0;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_beta0)( NS(SingleParticleView_particles)(
        p ), p->index, beta0 );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_gamma0)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_real_type) )1.0; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_gamma0)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->gamma0;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_gamma0)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) gamma0 ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( gamma0 >= ( NS(particle_real_type) )1.0 );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->gamma0 = gamma0;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_gamma0)( NS(SingleParticleView_particles)(
        p ), p->index, gamma0 );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_p0c)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_real_type) )0.0; }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_p0c)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->p0c;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_p0c)(
        NS(SingleParticleView_const_particles)( p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_p0c)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) p0c ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
//     SIXTRL_ASSERT( p0c >= ( NS(particle_real_type) )1.0 );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->p0c = p0c;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_p0c)( NS(SingleParticleView_particles)( p ), p->index, p0c );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_index_type) NS(Particle_default_id)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MIN_LEGAL_ID; }

SIXTRL_INLINE NS(particle_index_type) NS(Particle_id)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->id;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_id)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) id ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( id >= ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MIN_LEGAL_ID );
    SIXTRL_ASSERT( id <= ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MAX_LEGAL_ID );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->id = id;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_id)( NS(SingleParticleView_particles)( p ), p->index, id );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_index_type) NS(Particle_default_at_element)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT; }

SIXTRL_INLINE NS(particle_index_type) NS(Particle_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->at_element;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_at_element)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) at_element ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( at_element >= ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT );
    SIXTRL_ASSERT( at_element <= ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->at_element = at_element;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_at_element)( NS(SingleParticleView_particles)(
        p ), p->index, at_element );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_increment_at_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    SIXTRL_ASSERT( p->at_element >= ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT );
    SIXTRL_ASSERT( p->at_element < ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT );
    ++p->at_element;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_increment_at_element)( NS(SingleParticleView_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_index_type) NS(Particle_default_at_turn)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN; }

SIXTRL_INLINE NS(particle_index_type) NS(Particle_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->at_turn;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_at_turn)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) at_turn ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( at_turn >= ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN );
    SIXTRL_ASSERT( at_turn <= ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->at_turn = at_turn;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_at_turn)( NS(SingleParticleView_particles)(
        p ), p->index, at_turn );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_increment_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    SIXTRL_ASSERT( p->at_turn >= ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN );
    SIXTRL_ASSERT( p->at_turn < ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN );
    ++p->at_turn;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_increment_at_turn)( NS(SingleParticleView_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_finish_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) const start_at_element ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( start_at_element >= ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT );
    SIXTRL_ASSERT( start_at_element <= ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    SIXTRL_ASSERT( p->at_turn >= ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN );
    SIXTRL_ASSERT( p->at_turn < ( NS(particle_index_type)
        )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN );
    ++p->at_turn;
    p->at_element = start_at_element;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_finish_turn)(
        NS(SingleParticleView_particles)( p ), p->index, start_at_element );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_index_type) NS(Particle_default_state)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_index_type) )1; }

SIXTRL_INLINE NS(particle_index_type) NS(Particle_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return p->state;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_state)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_set_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) state ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->state = state;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_set_state)( NS(SingleParticleView_particles)(
        p ), p->index, state );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE bool NS(Particle_is_active)( SIXTRL_PARTICLE_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return ( p->state == ( NS(particle_index_type) )1 );
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_is_active)( NS(SingleParticleView_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE bool NS(Particle_is_lost)( SIXTRL_PARTICLE_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return ( p->state != ( NS(particle_index_type) )1 );
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    return NS(Particles_is_lost)( NS(SingleParticleView_const_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE bool NS(Particle_is_not_lost)( SIXTRL_PARTICLE_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    return !NS(Particle_is_lost)( p ); }

SIXTRL_INLINE void NS(Particle_mark_as_lost)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    NS(Particle_set_state)( p, ( NS(particle_index_type) )0u ); }

SIXTRL_INLINE void NS(Particle_keep_active_if_not_lost)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_index_type) const new_state ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    p->state &= new_state;
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    NS(Particles_keep_active_if_not_lost)( NS(SingleParticleView_particles)(
        p ), p->index );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_mass_ratio)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return NS(Particle_mass_ratio_impl)(
    NS(Particle_charge_ratio)( p ), NS(Particle_chi)( p ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_beta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return NS(Particle_beta_impl)(
    NS(Particle_beta0)( p ), NS(Particle_rvv)( p ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_gamma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return NS(Particle_gamma_impl)(
    NS(Particle_beta0)( p ), NS(Particle_rvv)( p ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_charge)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return NS(Particle_charge_impl)(
    NS(Particle_charge_ratio)( p ), NS(Particle_charge0)( p ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_mass)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return NS(Particle_mass_impl)(
    NS(Particle_charge_ratio)( p ), NS(Particle_chi)( p ),
        NS(Particle_mass0)( p ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return NS(Particle_sigma_impl)(
    NS(Particle_zeta)( p ), NS(Particle_rvv)( p ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_sigma)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_real_type) )0.0; }

SIXTRL_INLINE void NS(Particle_set_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) sigma ) SIXTRL_NOEXCEPT { NS(Particle_set_zeta)( p,
        NS(Particle_zeta_from_sigma_impl)( sigma, NS(Particle_rvv)( p ) ) ); }

SIXTRL_INLINE void NS(Particle_add_to_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_sigma ) SIXTRL_NOEXCEPT {
    NS(Particle_set_sigma)( p, NS(Particle_sigma)( p ) + d_sigma ); }

SIXTRL_INLINE void NS(Particle_subtract_from_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) d_sigma ) SIXTRL_NOEXCEPT {
    NS(Particle_set_sigma)( p, NS(Particle_sigma)( p ) - d_sigma ); }

SIXTRL_INLINE void NS(Particle_scale_sigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) sigma_factor ) SIXTRL_NOEXCEPT {
    NS(Particle_set_sigma)( p, NS(Particle_sigma)( p ) * sigma_factor ); }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_tau)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return NS(Particle_tau_impl)( NS(Particle_zeta)( p ),
    NS(Particle_rvv)( p ), NS(Particle_beta0)( p ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_tau)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_real_type) )0.0; }

SIXTRL_INLINE void NS(Particle_set_tau)( SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)*
    SIXTRL_RESTRICT p, NS(particle_real_type) tau ) SIXTRL_NOEXCEPT {
    NS(Particle_set_zeta)( p, NS(Particle_zeta_from_tau_impl)(
        tau, NS(Particle_rvv)( p ), NS(Particle_beta0)( p ) ) ); }

SIXTRL_INLINE void NS(Particle_update_tau)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p, NS(particle_real_type) const tau
) SIXTRL_NOEXCEPT { NS(Particle_set_tau)( p, tau ); }

SIXTRL_INLINE void NS(Particle_add_to_tau)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p, NS(particle_real_type) d_tau
) SIXTRL_NOEXCEPT { NS(Particle_set_tau)( p, NS(Particle_tau)( p ) + d_tau ); }

SIXTRL_INLINE void NS(Particle_subtract_from_tau)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p, NS(particle_real_type) d_tau
) SIXTRL_NOEXCEPT { NS(Particle_set_tau)( p, NS(Particle_tau)( p ) - d_tau ); }

SIXTRL_INLINE void NS(Particle_scale_tau)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p, NS(particle_real_type) tau_factor
) SIXTRL_NOEXCEPT { NS(Particle_set_tau)(
        p, NS(Particle_tau)( p ) * tau_factor ); }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_ptau)( SIXTRL_PARTICLE_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    return NS(Particle_ptau_impl)(
        NS(Particle_delta)( p ), NS(Particle_beta0)( p ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particle_default_ptau)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particle_real_type) )0.0; }

SIXTRL_INLINE void NS(Particle_set_ptau)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particle)* SIXTRL_RESTRICT p, NS(particle_real_type) const ptau
) SIXTRL_NOEXCEPT {
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    NS(Particle_update_ptau_impl)( ptau, NS(Particle_beta0)( p ),
        &p->delta, &p->psigma, &p->rpp, &p->rvv );

    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) delta;
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) psigma;
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) rpp;
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) rvv;

    NS(Particle_update_ptau_impl)( ptau, NS(Particle_beta0)( p ),
        &delta, &psigma, &rpp, &rvv );

    NS(Particle_set_delta)( p, delta );
    NS(Particle_set_psigma)( p, psigma );
    NS(Particle_set_rpp)( p, rpp );
    NS(Particle_set_rvv)( p, rvv );

    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_update_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const ptau ) SIXTRL_NOEXCEPT {
    NS(Particle_set_ptau)( p, ptau ); }

SIXTRL_INLINE void NS(Particle_add_to_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const d_ptau ) SIXTRL_NOEXCEPT {
    NS(Particle_set_ptau)( p, NS(Particle_ptau)( p ) + d_ptau ); }

SIXTRL_INLINE void NS(Particle_subtract_from_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const d_ptau ) SIXTRL_NOEXCEPT {
    NS(Particle_set_ptau)( p, NS(Particle_ptau)( p ) - d_ptau ); }

SIXTRL_INLINE void NS(Particle_scale_ptau)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const ptau_factor ) SIXTRL_NOEXCEPT {
    NS(Particle_set_ptau)( p, NS(Particle_ptau)( p ) * ptau_factor ); }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_energy0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return NS(Particle_energy0_impl)(
    NS(Particle_mass0)( p ), NS(Particle_p0c)( p ) ); }

SIXTRL_INLINE void NS(Particle_update_energy0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const energy0 ) SIXTRL_NOEXCEPT { NS(Particle_set_p0c)(
        p, NS(Particle_p0c_from_energy0_mass0_impl)(
            energy0, NS(Particle_mass0)( p ) ) ); }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(particle_real_type) NS(Particle_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return NS(Particle_energy_impl)( NS(Particle_p0c)( p ),
    NS(Particle_mass0)( p ), NS(Particle_mass_ratio)( p ),
        NS(Particle_delta)( p ), NS(Particle_beta0)( p ) ); }

SIXTRL_INLINE void NS(Particle_add_to_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const d_energy ) SIXTRL_NOEXCEPT {
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    NS(Particle_add_to_energy_impl)( NS(Particle_energy0)( p ),
        NS(Particle_delta)( p ), NS(Particle_rvv)( p ),
        NS(Particle_beta0)( p ), d_energy, &p->zeta, &p->delta, &p->psigma,
        &p->rpp, &p->rvv );
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) delta;
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) psigma;
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) rpp;
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) rvv;
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) zeta =
        NS(Particle_zeta)( p );

    NS(Particle_add_to_energy_impl)( NS(Particle_energy0)( p ),
        NS(Particle_delta)( p ), NS(Particle_rvv)( p ), NS(Particle_beta0)( p ),
        d_energy, &zeta, &delta, &psigma, &rpp, &rvv );

    NS(Particle_set_zeta)( p, zeta );
    NS(Particle_set_delta)( p, delta );
    NS(Particle_set_psigma)( p, psigma );
    NS(Particle_set_rpp)( p, rpp );
    NS(Particle_set_rvv)( p, rvv );
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}

SIXTRL_INLINE void NS(Particle_update_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const energy ) SIXTRL_NOEXCEPT {
        NS(Particle_add_to_energy)( p,
            energy - NS(Particle_energy)( p ) ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(status_type) NS(Particle_copy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
        NS(Particle_set_x)( dest, NS(Particle_x)( src ) );
        NS(Particle_set_y)( dest, NS(Particle_y)( src ) );
        NS(Particle_set_px)( dest, NS(Particle_px)( src ) );
        NS(Particle_set_py)( dest, NS(Particle_py)( src ) );
        NS(Particle_set_zeta)( dest, NS(Particle_zeta)( src ) );
        NS(Particle_set_delta)( dest, NS(Particle_delta)( src ) );
        NS(Particle_set_state)( dest, NS(Particle_state)( src ) );
        NS(Particle_set_at_element)( dest, NS(Particle_at_element)( src ) );
        NS(Particle_set_at_turn)( dest, NS(Particle_at_turn)( src ) );
        NS(Particle_set_id)( dest, NS(Particle_id)( src ) );
        #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD  == 1 )
            NS(Particle_set_psigma)( dest, NS(Particle_psigma)( src ) );
        #endif /* defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */
        NS(Particle_set_rpp)( dest, NS(Particle_rpp)( src ) );
        NS(Particle_set_rvv)( dest, NS(Particle_rvv)( src ) );
        NS(Particle_set_chi)( dest, NS(Particle_chi)( src ) );
        NS(Particle_set_charge_ratio)( dest, NS(Particle_charge_ratio)( src ) );
        NS(Particle_set_charge0)( dest, NS(Particle_charge0)( src ) );
        NS(Particle_set_mass0)( dest, NS(Particle_mass0)( src ) );
        NS(Particle_set_beta0)( dest, NS(Particle_beta0)( src ) );
        NS(Particle_set_gamma0)( dest, NS(Particle_gamma0)( src ) );
        NS(Particle_set_p0c)( dest, NS(Particle_p0c)( src ) );
        #if defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
            NS(Particle_set_s)( dest, NS(Particle_s)( src ) );
        #endif /* defined( SIXTRL_PARTICLE_USE_S_FIELD ) */
        return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE bool NS(CObjIndex_is_particle)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
    return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(Particle_cobj_type_id)(), sizeof( NS(SingleParticle) ) ); }
    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
    ( void )obj;
    return false; }
    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle) const*
NS(Particle_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const
    NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle) const* elem = SIXTRL_NULLPTR;
    if( NS(CObjIndex_is_particle)( obj ) ) {
        elem = ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj ); }
    return elem; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
        )NS(Particle_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle) const*
NS(Particle_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const index, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(Particle_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, index, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const index, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(Particle_from_cobj_index)( NS(CObjFlatBuffer_index)(
        buffer, index, slot_size ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle) const*
NS(Particle_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buf,
    NS(size_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particle_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buf, index ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particle)*
NS(Particle_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buf,
    NS(size_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particle_from_cobj_index)( NS(CBuffer_index_at)( buf, index ) ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(Particle_calculate_difference)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT {
    NS(Particle_set_x)(  diff, NS(Particle_x)( lhs )  - NS(Particle_x)(  rhs ) );
    NS(Particle_set_y)(  diff, NS(Particle_y)( lhs )  - NS(Particle_y)(  rhs ) );
    NS(Particle_set_px)( diff, NS(Particle_px)( lhs ) - NS(Particle_px)( rhs ) );
    NS(Particle_set_py)( diff, NS(Particle_py)( lhs ) - NS(Particle_py)( rhs ) );

    NS(Particle_set_zeta)( diff,  NS(Particle_zeta)( lhs ) -
                                  NS(Particle_zeta)( rhs ) );

    NS(Particle_set_delta)( diff, NS(Particle_delta)( lhs ) -
                                  NS(Particle_delta)( rhs ) );

    NS(Particle_set_id)( diff, NS(Particle_id)( lhs ) - NS(Particle_id)( rhs ) );

    NS(Particle_set_at_element)( diff, NS(Particle_at_element)( lhs ) -
                                       NS(Particle_at_element)( rhs ) );

    NS(Particle_set_at_turn)( diff, NS(Particle_at_turn)( lhs ) -
                                    NS(Particle_at_turn)( rhs ) );

    NS(Particle_set_state)( diff, NS(Particle_state)( lhs ) -
                                  NS(Particle_state)( rhs ) );

    #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
               ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD  == 1 )
    NS(Particle_set_psigma)( diff, NS(Particle_psigma)( lhs ) -
                                   NS(Particle_psigma)( rhs ) );
    #endif /* defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */

    NS(Particle_set_rpp)( diff, NS(Particle_rpp)( lhs ) -
                                NS(Particle_rpp)( rhs ) );

    NS(Particle_set_rvv)( diff, NS(Particle_rvv)( lhs ) -
                                NS(Particle_rvv)( rhs ) );

    NS(Particle_set_chi)( diff, NS(Particle_chi)( lhs ) -
                                NS(Particle_chi)( rhs ) );

    NS(Particle_set_charge_ratio)( diff, NS(Particle_charge_ratio)( lhs ) -
                                         NS(Particle_charge_ratio)( rhs ) );

    NS(Particle_set_charge0)( diff, NS(Particle_charge0)( lhs ) -
                                    NS(Particle_charge0)( rhs ) );

    NS(Particle_set_mass0)( diff, NS(Particle_mass0)( lhs ) -
                                  NS(Particle_mass0)( rhs ) );

    NS(Particle_set_beta0)( diff, NS(Particle_beta0)( lhs ) -
                                  NS(Particle_beta0)( rhs ) );

    NS(Particle_set_gamma0)( diff, NS(Particle_gamma0)( lhs ) -
                                   NS(Particle_gamma0)( rhs ) );

    NS(Particle_set_p0c)( diff, NS(Particle_p0c)( lhs ) -
                                NS(Particle_p0c)( rhs ) );

    #if defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
               ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
    NS(Particle_set_s)( diff, NS(Particle_s)( lhs ) - NS(Particle_s)( rhs ) );
    #endif /* defined( SIXTRL_PARTICLE_USE_S_FIELD ) */
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_SINGLE_PARTICLE_H__ */
