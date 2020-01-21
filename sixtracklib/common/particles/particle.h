#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_C99_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #if defined( __cplusplus )
        #include <cmath>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/particle/definitions.h"
    #include "sixtracklib/common/internal/objects_type_id.h"

    #if defined( __cplusplus )
        #include "sixtracklib/common/internal/obj_type_traits.hpp"
        #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #endif /* defined( __cplusplus ) */
#endif /*
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

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_x)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_px)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_y)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_py)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_zeta)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_delta)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_psigma)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p )SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_s)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_rvv)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_rpp)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_chi)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_charge_ratio)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_charge0)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_mass0)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_beta0)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_gamma0)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_pc0)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_sigma)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_tau)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_ptau)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_beta)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_mass_ratio)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_energy0)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t) NS(Particle_energy)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_add_energy_to)(
    SIXTRL_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_energy ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SXITRL_STATIC SIXTRL_FN NS(particle_index_t) NS(Particle_id)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SXITRL_STATIC SIXTRL_FN NS(particle_index_t) NS(Particle_at_element)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SXITRL_STATIC SIXTRL_FN NS(particle_index_t) NS(Particle_at_turn)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SXITRL_STATIC SIXTRL_FN NS(particle_index_t) NS(Particle_state)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_is_lost)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particle_is_not_lost)(
    SIXTRL_ARGPTR_DEC const NS(Particle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particle_mark_as_lost)(
    SIXTRL_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template<> ObjDataTypeTraits< ::NS(Particle) >
    {
        typedef SIXTRL_CXX_NAMESPACE::object_type_id_t type_id_t;

        static SIXTRL_FN constexpr type_id_t ObjTypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_PARTICLES;
        }
    };

    template<> ObjDataStoreCApiTraits< ::NS(Particle) >
    {
        typedef ::NS(Particle) c_api_t;
    };
}

#endif /* defined( __cplusplus ) */

/* ------------------------------------------------------------------------- */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_x)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->x;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_px)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->px;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_y)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->y;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_py)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->py;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_zeta)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->zeta;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_delta)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->delta;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_psigma)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p )SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->psigma;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_s)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SXITRL_ASSERT( p->s >= ( NS(particle_real_t) )0.0 );

    return p->s;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_rvv)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SXITRL_ASSERT( p->rvv >= ( NS(particle_real_t) )0.0 );

    return p->rvv;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_rpp)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->rpp;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_chi)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->chi;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_charge_ratio)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->chi;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_charge0)( SIXTRL_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->charge0;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_mass0)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->mass0 >= ( NS(particle_real_t) )0.0 );
    return p->mass0;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_beta0)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->beta0 >= ( NS(particle_real_t) )0.0 );
    SIXTRL_ASSERT( p->beta0 <= ( NS(particle_real_t) )1.0 );

    return p->beta0;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_gamma0)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->gamma0 >= ( NS(particle_real_t ) )0.0 );
    return p->gamma0;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_pc0)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->pc0;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_sigma)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->rvv > ( NS(particle_real_t) )0.0 );
    return p->zeta / p->rvv;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_tau)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->rvv   >  ( real_t )0.0 );
    SIXTRL_ASSERT( p->beta0 >  ( real_t )0.0 );

    return p->zeta / ( p->rvv * NS(Particle_beta0)( p ) );
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_ptau)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;

    #if defined( __cplusplus ) && !defined( _GPUCODE )
    using std::sqrt;
    #endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

    real_t const beta0       = NS(Particle_beta0)( p );
    real_t const delta_beta0 = NS(Particle_delta)( p ) * beta0
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

SIXTRL_INLINE NS(particle_real_t) NS(Particle_beta)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p )  SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->rvv * p->beta0;
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_mass_ratio)( SIXTRL_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ( p->chi >= ( NS(particle_real_t) )+1e-16 ) ||
                   ( p->chi <= ( NS(particle_real_t) )-1e-16 ) );

    return p->charge_ratio / p->chi;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particle_energy0)( SIXTRL_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    #if defined( __cplusplus ) && !defined( _GPUCODE )
    using std::sqrt;
    #endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->mass0 >= ( NS(particle_real_t) )0.0 );
    SIXTRL_ASSERT( p->pc0   >= ( NS(particle_real_t) )0.0 );

    return sqrt( p->pc0 * p->pc0 + p->mass0 * p->mass0 );
}

SIXTRL_INLINE NS(particle_real_t) NS(Particle_energy)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    return ( NS(Particle_psigma)( p ) * NS(Paricle_beta0)( p ) *
             NS(Particle_pc0)( p ) ) +
           ( NS(Particle_energy0)( p ) * NS(Particle_mass_ratio)( p ) );
}

SIXTRL_INLINE void NS(Particle_add_energy_to)(
    SIXTRL_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_energy ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;

    #if defined( __cplusplus ) && !defined( _GPUCODE )
    using std::sqrt;
    #endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

    SIXTRL_STATIC_VAR real_t const ONE = ( real_t )1.0;

    real_t const beta0 = NS(Particle_beta0)( p );
    real_t const delta_beta0 = NS(Particle_delta)( p ) * beta0;

    real_t const ptau_beta0 = delta_energy / NS(Particle_energy0)( p )
        + sqrt( delta_beta0 * delta_beta0 + ONE +
            ( real_t )2.0 * delta_beta0 * beta0 ) - ONE;

    real_t const ptau = ptau_beta0 / beta0;
    real_t const psigma = ptau / beta0;
    real_t const delta = sqrt( ptau * ptau +
        ( real_t )2.0 * psigma + ONE ) - ONE;

    real_t const one_plus_delta = delta + ONE;
    real_t const rvv = one_plus_delta / ( ONE + ptau_beta0 );

    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( p->rvv   > ( real_t )1e-16 );
    SIXTRL_ASSERT( p->beta0 > ( real_t )0.0   );
    SIXTRL_ASSERT( ( delta_beta0 >= ( real_t )0.0 ) ||
                   ( ( delta_beta0 * delta_beta0 + ONE ) >=
                     ( real_t )-2.0 * delta_beta0 * beta0 ) );
    SIXTRL_ASSERT( ( psigma >= ( real_t )0.0 ) ||
                   ( ( ptau * ptau + ONE ) >= ( real_t )-2.0 * psigma ) );

    SIXTRL_ASSERT( ( ( ptau_beta0 + ONE ) > ( real_t )+1e-16 ) ||
                   ( ( ptau_beta0 + ONE ) < ( real_t )-1e-16 ) );

    SIXTRL_ASSERT( ( one_plus_delta > ( real_t )+1e-16 ) ||
                   ( one_plus_delta < ( real_t )-1e-16 ) );

    p->delta  = delta;
    p->psigma = psigma;
    p->zeta  *= rvv / p->rvv;
    p->rvv    = rvv;
    p->rpp    = ONE / one_plus_delta;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_index_t) NS(Particle_id)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->id;
}

SIXTRL_INLINE NS(particle_index_t) NS(Particle_at_element)( SIXTRL_ARGPTR_DEC
    const NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->at_element;
}

SIXTRL_INLINE NS(particle_index_t) NS(Particle_at_turn)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->at_turn;
}

SIXTRL_INLINE NS(particle_index_t) NS(Particle_state)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->state;
}

SIXTRL_INLINE bool NS(Particle_is_lost)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( p->state != ( NS(particle_index_t) )1 );
}

SIXTRL_INLINE bool NS(Particle_is_not_lost)( SIXTRL_ARGPTR_DEC const
    NS(Particle) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( p->state == ( NS(particle_index_t) )1 );
}

SIXTRL_INLINE void NS(Particle_mark_as_lost)(
    SIXTRL_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->state = ( NS(particle_index_t) )0;
}


#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_C99_H__ */
