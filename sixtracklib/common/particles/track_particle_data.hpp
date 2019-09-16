#ifndef SIXTRACKLIB_COMMON_PARTICLES_TRACK_PARTICLE_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLES_TRACK_PARTICLE_DATA_CXX_HPP__

#include <cstdlib>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"

#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/internal/math_constant_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename R, typename I,
        std::size_t RAlign = TypeStoreTraits< R >::StorageAlign(),
        std::size_t IAlign = TypeStoreTraits< I >::StorageAlign() >
    struct TrackParticleData
    {
        typedef R real_t;
        typedef I int_t;

        static SIXTRL_FN constexpr std::size_t
        RealAlignment() { return RAlign; }

        static SIXTRL_FN constexpr std::size_t
        IntegerAlignment() { return IAlign; }

        real_t q0             SIXTRL_ALIGN( RAlign );
        real_t mass0          SIXTRL_ALIGN( RAlign );
        real_t beta0          SIXTRL_ALIGN( RAlign );
        real_t gamma0         SIXTRL_ALIGN( RAlign );
        real_t p0c            SIXTRL_ALIGN( RAlign );

        real_t s              SIXTRL_ALIGN( RAlign );
        real_t x              SIXTRL_ALIGN( RAlign );
        real_t y              SIXTRL_ALIGN( RAlign );
        real_t px             SIXTRL_ALIGN( RAlign );
        real_t py             SIXTRL_ALIGN( RAlign );
        real_t zeta           SIXTRL_ALIGN( RAlign );

        real_t psigma         SIXTRL_ALIGN( RAlign );
        real_t delta          SIXTRL_ALIGN( RAlign );
        real_t rpp            SIXTRL_ALIGN( RAlign );
        real_t rvv            SIXTRL_ALIGN( RAlign );
        real_t chi            SIXTRL_ALIGN( RAlign );
        real_t charge_ratio   SIXTRL_ALIGN( RAlign );

        int_t  particle_id    SIXTRL_ALIGN( IAlign );
        int_t  at_element_id  SIXTRL_ALIGN( IAlign );
        int_t  at_turn        SIXTRL_ALIGN( IAlign );
        int_t  state          SIXTRL_ALIGN( IAlign );
    };

    template< typename R, typename I, std::size_t RAlign, std::size_t IAlign >
    typename TrackParticleData< R, I, RAlign, IAlign >::real_t
    TrackParticleData_get_energy(
        TrackParticleData< R, I, RAlign, IAlign > const& SIXTRL_RESTRICT_REF p )
    {
        return p.psigma * p.beta0 * p.p0c;
    }

    template< typename R, typename I, std::size_t RAlign, std::size_t IAlign >
    void TrackParticleData_set_energy(
        TrackParticleData< R, I, RAlign, IAlign >& SIXTRL_RESTRICT_REF p,
        typename TrackParticleData< R, I, RAlign, IAlign >::real_t
            const& SIXTRL_RESTRICT_REF energy_value )
    {
        typedef TrackParticleData< R, I, RAlign, IAlign > particle_data_t;
        typedef typename particle_data_t::real_t real_t;

        real_t const ptau_beta0 = ( p.beta0 * energy_value ) / p.p0c;
        real_t const beta0_squ  =  p.beta0 * p.beta0;
        real_t const beta0_plus_delta_beta0 = ptau_beta0 * ptau_beta0 +
            ptau_beta0 * MathConstants< real_t >::Two() + beta0_squ;

        p.psigma = ptau_beta0 / beta0_squ;
        p.delta  = ( beta0_plus_delta_beta0 - p.beta0 ) / p.beta0;
        p.rpp    = p.beta0 / beta0_plus_delta_beta0;
        p.rvv    = beta0_plus_delta_beta0 / ( p.beta0 + ptau_beta0 * p.beta0 );
    }

    /* --------------------------------------------------------------------- */

    template<>
    struct ObjDataStoreTraits< TrackParticleData< double, int64_t > >
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

    template< class R, class I, std::size_t RealAlign, std::size_t IntAlign >
    struct ObjDataTrackTraits< TrackParticleData< R, I, RealAlign, IntAlign > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_TRACK_PARTICLE;
        }
    };
}

#endif /* SIXTRACKLIB_COMMON_PARTICLES_TRACK_PARTICLE_DATA_CXX_HPP__ */

/* end: cxx/common/particles/track_particle_data.hpp */
