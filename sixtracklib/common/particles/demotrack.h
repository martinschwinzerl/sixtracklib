#ifndef SIXTRACKLIB_COMMON_PARTICLES_DEMOTRACK_H__
#define SIXTRACKLIB_COMMON_PARTICLES_DEMOTRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <algorithm>
    #include <memory>
    #include <vector>
    #include <cstdio>
#endif /* !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

struct NS(Particles);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(DemotrackParticle)
{
    NS(particle_real_type)  x              SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  px             SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  y              SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  py             SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  zeta           SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  delta          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  rpp            SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  rvv            SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  psigma         SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  chi            SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  charge_ratio   SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  charge0        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  mass0          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  beta0          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  gamma0         SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type)  p0c            SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    SIXTRL_UINT64_TYPE      state          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    SIXTRL_UINT64_TYPE      at_element     SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_index_type) at_turn        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    SIXTRL_UINT64_TYPE      id             SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(DemotrackParticle);

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_ARGPTR_DEC NS(DemotrackParticle)*
NS(Demotrack_particle_preset)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(DemotrackParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Demotrack_particle_clear)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(DemotrackParticle)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Demotrack_particle_init)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(DemotrackParticle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const x, NS(particle_real_type) const px,
    NS(particle_real_type) const y, NS(particle_real_type) const py,
    NS(particle_real_type) const zeta, NS(particle_real_type) const delta,
    NS(particle_real_type) const rpp, NS(particle_real_type) const rvv,
    NS(particle_real_type) const psigma, NS(particle_real_type) const chi,
    NS(particle_real_type) const charge_ratio,
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const beta0, NS(particle_real_type) const gamma0,
    NS(particle_real_type) const p0c,
    SIXTRL_UINT64_TYPE const state, SIXTRL_UINT64_TYPE const at_element,
    NS(particle_index_type) const at_turn, SIXTRL_UINT64_TYPE const id
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Demotrack_particle_from_single_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(DemotrackParticle)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Demotrack_particle_to_single_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(DemotrackParticle) *const
        SIXTRL_RESTRICT src,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT dest
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Demotrack_particle_from_particles)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(DemotrackParticle)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT src,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Demotrack_particle_to_particles)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(DemotrackParticle) *const
        SIXTRL_RESTRICT src,
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT dest,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particles.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_INLINE SIXTRL_PARTICLE_ARGPTR_DEC NS(DemotrackParticle)*
NS(Demotrack_particle_preset)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(DemotrackParticle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    if( p != SIXTRL_NULLPTR ) NS(Demotrack_particle_clear)( p );
    return p;
}

SIXTRL_INLINE NS(status_type) NS(Demotrack_particle_clear)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(DemotrackParticle)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    return NS(Demotrack_particle_init)( p,
        NS(Particle_default_x)(), NS(Particle_default_px)(),
        NS(Particle_default_y)(), NS(Particle_default_py)(),
        NS(Particle_default_zeta)(), NS(Particle_default_delta)(),
        NS(Particle_default_rpp)(), NS(Particle_default_rvv)(),
        NS(Particle_default_psigma)(), NS(Particle_default_chi)(),
        NS(Particle_default_charge_ratio)(),
        NS(Particle_default_charge0)(),
        NS(Particle_default_mass0)(),
        NS(Particle_default_beta0)(),
        NS(Particle_default_gamma0)(),
        NS(Particle_default_p0c)(),
        ( SIXTRL_UINT64_TYPE )NS(Particle_default_id)(),
        ( SIXTRL_UINT64_TYPE )NS(Particle_default_at_element)(),
        NS(Particle_default_at_turn)(),
        ( SIXTRL_UINT64_TYPE )NS(Particle_default_state)() );
}

SIXTRL_INLINE NS(status_type) NS(Demotrack_particle_init)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(DemotrackParticle)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const x, NS(particle_real_type) const px,
    NS(particle_real_type) const y, NS(particle_real_type) const py,
    NS(particle_real_type) const zeta, NS(particle_real_type) const delta,
    NS(particle_real_type) const rpp, NS(particle_real_type) const rvv,
    NS(particle_real_type) const psigma, NS(particle_real_type) const chi,
    NS(particle_real_type) const charge_ratio,
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const beta0, NS(particle_real_type) const gamma0,
    NS(particle_real_type) const p0c,
    SIXTRL_UINT64_TYPE const state, SIXTRL_UINT64_TYPE const at_element,
    NS(particle_index_type) const at_turn, SIXTRL_UINT64_TYPE const id
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( p != SIXTRL_NULLPTR )
    {
        p->x            = x;
        p->px           = px;
        p->y            = y;
        p->py           = py;
        p->zeta         = zeta;
        p->delta        = delta;
        p->rpp          = rpp;
        p->rvv          = rvv;
        p->psigma       = psigma;
        p->chi          = chi;
        p->charge_ratio = charge_ratio;
        p->charge0      = charge0;
        p->mass0        = mass0;
        p->beta0        = beta0;
        p->gamma0       = gamma0;
        p->p0c          = p0c;

        p->state        = state;
        p->at_element   = at_element;
        p->at_turn      = at_turn;
        p->id           = id;

        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(status_type) NS(Demotrack_particle_from_single_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(DemotrackParticle)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    return NS(Demotrack_particle_init)( dest,
        NS(Particle_x)( src ), NS(Particle_px)( src ),
        NS(Particle_y)( src ), NS(Particle_py)( src ),
        NS(Particle_zeta)( src ), NS(Particle_delta)( src ),
        NS(Particle_rpp)( src ), NS(Particle_rvv)( src ),
        NS(Particle_psigma)( src ), NS(Particle_chi)( src ),
        NS(Particle_charge_ratio)( src ), NS(Particle_charge0)( src ),
        NS(Particle_mass0)( src ), NS(Particle_beta0)( src ),
        NS(Particle_gamma0)( src ), NS(Particle_p0c)( src ),
        ( NS(Particle_is_active)( src ) )
            ? ( SIXTRL_UINT64_TYPE )1u : ( SIXTRL_UINT64_TYPE )0u,
        ( NS(Particle_at_element)( src ) >= ( NS(particle_index_type) )0 )
            ? ( SIXTRL_UINT64_TYPE )NS(Particle_at_element)( src )
            : ( SIXTRL_UINT64_TYPE )0u,
        NS(Particle_at_turn)( src ),
        ( NS(Particle_id)( src ) >= ( NS(particle_index_type) )0 )
            ? ( SIXTRL_UINT64_TYPE )NS(Particle_id)( src )
            : ( SIXTRL_UINT64_TYPE )0u ); }

SIXTRL_INLINE NS(status_type) NS(Demotrack_particle_to_single_particle)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(DemotrackParticle) *const
        SIXTRL_RESTRICT src,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT dest
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( src != SIXTRL_NULLPTR )
    {
        status = NS(Particle_init)( dest,
            src->x, src->y, src->px, src->py, src->zeta, src->delta,
            ( NS(particle_index_type) )src->state,
            ( NS(particle_index_type) )src->at_element, src->at_turn,
            ( NS(particle_index_type) )src->id,
            src->psigma, src->rpp, src->rvv, src->chi, src->charge_ratio,
            src->charge0, src->mass0, src->beta0, src->gamma0, src->p0c,
            NS(Particle_default_s)() );
    }
    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(status_type) NS(Demotrack_particle_from_particles)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(DemotrackParticle)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT src,
    NS(particles_num_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Demotrack_particle_init)( dest,
        NS(Particles_x)( src, idx ), NS(Particles_px)( src, idx ),
        NS(Particles_y)( src, idx ), NS(Particles_py)( src, idx ),
        NS(Particles_zeta)( src, idx ), NS(Particles_delta)( src, idx ),
        NS(Particles_rpp)( src, idx ), NS(Particles_rvv)( src, idx ),
        NS(Particles_psigma)( src, idx ), NS(Particles_chi)( src, idx ),
        NS(Particles_charge_ratio)( src, idx ),
        NS(Particles_charge0)( src, idx ), NS(Particles_mass0)( src, idx ),
        NS(Particles_beta0)( src, idx ), NS(Particles_gamma0)( src, idx ),
        NS(Particles_p0c)( src, idx ),
        ( NS(Particles_is_active)( src, idx ) )
            ? ( SIXTRL_UINT64_TYPE )1u : ( SIXTRL_UINT64_TYPE )0u,
        ( NS(Particles_at_element)( src, idx ) >= ( NS(particle_index_type) )0 )
            ? ( SIXTRL_UINT64_TYPE )NS(Particles_at_element)( src, idx )
            : ( SIXTRL_UINT64_TYPE )0u,
        NS(Particles_at_turn)( src, idx ),
        ( NS(Particles_id)( src, idx ) >= ( NS(particle_index_type) )0 )
            ? ( SIXTRL_UINT64_TYPE )NS(Particles_id)( src, idx )
            : ( SIXTRL_UINT64_TYPE )0u );
}

SIXTRL_INLINE NS(status_type) NS(Demotrack_particle_to_particles)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(DemotrackParticle) *const
        SIXTRL_RESTRICT src,
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT dest,
    NS(particles_num_type) const idx  ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dest != SIXTRL_NULLPTR ) &&  ( src != SIXTRL_NULLPTR ) &&
        ( idx < NS(Particles_num_particles)( dest ) ) )
    {
        NS(Particles_set_charge0)( dest, idx, src->charge0 );
        NS(Particles_set_mass0)( dest, idx, src->mass0 );
        NS(Particles_set_beta0)( dest, idx, src->beta0 );
        NS(Particles_set_gamma0)( dest, idx, src->gamma0 );
        NS(Particles_set_p0c)( dest, idx, src->p0c );
        NS(Particles_set_s)( dest, idx, NS(Particle_default_s)() );
        NS(Particles_set_x)( dest, idx, src->x );
        NS(Particles_set_px)( dest, idx, src->px );
        NS(Particles_set_y)( dest, idx, src->y );
        NS(Particles_set_py)( dest, idx, src->py );
        NS(Particles_set_zeta)( dest, idx, src->zeta );
        NS(Particles_set_psigma)( dest, idx, src->psigma );
        NS(Particles_set_delta)( dest, idx, src->delta );
        NS(Particles_set_rpp)( dest, idx, src->rpp );
        NS(Particles_set_rvv)( dest, idx, src->rvv );
        NS(Particles_set_chi)( dest, idx, src->chi );
        NS(Particles_set_charge_ratio)( dest, idx, src->charge_ratio );
        NS(Particles_set_id)( dest, idx, src->id );
        NS(Particles_set_at_element)( dest, idx, src->at_element );
        NS(Particles_set_at_turn)( dest, idx, src->at_turn );
        NS(Particles_set_state)( dest, idx, src->state );

        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }

    return status;
}


#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_DEMOTRACK_H__ */
