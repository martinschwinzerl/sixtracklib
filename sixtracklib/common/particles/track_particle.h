#ifndef SIXTRACKLIB_COMMON_PARTICLES_TRACK_PARTICLE_C99_H__
#define SIXTRACKLIB_COMMON_PARTICLES_TRACK_PARTICLE_C99_H__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/particles/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"

#if defined( __cplusplus )

#include "sixtracklib/common/particles/particle_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

extern "C" {
#endif /* defined( __cplusplus ) */

typedef struct NS(TrackParticle)
{
    NS(particle_real_t)  q0             SIXTRL_ALIGN( 8 ); /* C */
    NS(particle_real_t)  mass0          SIXTRL_ALIGN( 8 ); /* eV */
    NS(particle_real_t)  beta0          SIXTRL_ALIGN( 8 ); /* nounit */
    NS(particle_real_t)  gamma0         SIXTRL_ALIGN( 8 ); /* nounit */
    NS(particle_real_t)  p0c            SIXTRL_ALIGN( 8 ); /* eV */

    NS(particle_real_t)  s              SIXTRL_ALIGN( 8 ); /* [m] */
    NS(particle_real_t)  x              SIXTRL_ALIGN( 8 ); /* [m] */
    NS(particle_real_t)  y              SIXTRL_ALIGN( 8 ); /* [m] */
    NS(particle_real_t)  px             SIXTRL_ALIGN( 8 ); /* Px/P0 */
    NS(particle_real_t)  py             SIXTRL_ALIGN( 8 ); /* Py/P0 */
    NS(particle_real_t)  zeta           SIXTRL_ALIGN( 8 ); /* */

    NS(particle_real_t)  psigma         SIXTRL_ALIGN( 8 ); /* (E-E0)/(beta0 P0c) */
    NS(particle_real_t)  delta          SIXTRL_ALIGN( 8 ); /* P/P0-1 = 1/rpp-1 */
    NS(particle_real_t)  rpp            SIXTRL_ALIGN( 8 ); /* ratio P0 /P */
    NS(particle_real_t)  rvv            SIXTRL_ALIGN( 8 ); /* ratio beta / beta0 */
    NS(particle_real_t)  chi            SIXTRL_ALIGN( 8 ); /* q/q0 * m/m0 */
    NS(particle_real_t)  charge_ratio   SIXTRL_ALIGN( 8 ); /* ratio q/q0 */

    NS(particle_index_t) particle_id    SIXTRL_ALIGN( 8 );
    NS(particle_index_t) at_element_id  SIXTRL_ALIGN( 8 );
    NS(particle_index_t) at_turn        SIXTRL_ALIGN( 8 );
    NS(particle_index_t) state          SIXTRL_ALIGN( 8 );
}
NS(TrackParticle);



#if defined( __cplusplus )
}

/* ------------------------------------------------------------------------- */

namespace SIXTRL_CXX_NAMESPACE
{
    ::NS(particle_real_t) TrackParticleData_get_energy(
        ::NS(TrackParticle) const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.psigma * p.beta0 * p.p0c;
    }

    void TrackParticleData_set_energy(
        ::NS(TrackParticle)& SIXTRL_RESTRICT_REF p,
        ::NS(particle_real_t) const energy_value ) SIXTRL_NOEXCEPT
    {
        typedef ::NS(particle_real_t) real_t;

        real_t const ptau_beta0 = ( p.beta0 * energy_value ) / p.p0c;
        real_t const beta0_squ  =  p.beta0 * p.beta0;
        real_t const beta0_plus_delta_beta0 =
            ptau_beta0 * ptau_beta0 + ptau_beta0 * real_t{ 2 } + beta0_squ;

        p.psigma = ptau_beta0 / beta0_squ;
        p.delta  = ( beta0_plus_delta_beta0 - p.beta0 ) / p.beta0;
        p.rpp    = p.beta0 / beta0_plus_delta_beta0;
        p.rvv    = beta0_plus_delta_beta0 / ( p.beta0 + ptau_beta0 * p.beta0 );
    }

    template<> struct ObjDataStoreTraits< ::NS(TrackParticle) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_TRACK_PARTICLE;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout()
        {
            return true;
        }
    };

    template<> struct ObjDataTrackTraits< ::NS(TrackParticle) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_TRACK_PARTICLE;
        }
    };

    template<> struct TrackParticleDataTraits< ::NS(TrackParticle) >
    {
        typedef ::NS(particle_real_t)   real_t;
        typedef ::NS(particle_index_t)  int_t;
    };
}

#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_TRACK_PARTICLE_C99_H__ */

/* end: sixtracklib/common/particles/track_particle.h */
