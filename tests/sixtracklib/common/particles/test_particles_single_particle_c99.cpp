#include <algorithm>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/common/particles/definitions.h"
#include "sixtracklib/common/particles/particles.h"
#include "sixtracklib/common/particles/particle.h"

#include "sixtracklib/common/cobjects/cobj_type_traits.h"
#include "sixtracklib/common/cobjects/cbuffer.h"
#include "sixtracklib/common/cobjects/cbuffer.hpp"

#include "sixtracklib/testlib.h"

TEST( C99CommonParticlesParticlesSingleParticle, CObjectsStoreAndRestore )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using particle_set_t  = ::NS(Particles);
    using npart_type      = ::NS(particles_num_type);
    using real_type       = ::NS(particle_real_type);
    using index_type      = ::NS(particle_index_type);
    using size_type       = ::NS(size_type);

    ASSERT_TRUE( st::CObjects_has_legal_id< particle_set_t >() );
    ASSERT_TRUE( st::CObjects_num_pointers< particle_set_t >() ==
                 size_type{ 21 } );

    ASSERT_TRUE( st::CObjects_type_id< particle_set_t >() ==
                 st::COBJECTS_TYPE_ID_PARTICLES_COLLECTION );

    ASSERT_TRUE(  st::CObjects_has_trivial_handle_size< particle_set_t >() );
    ASSERT_FALSE( st::CObjects_is_trivial_type< particle_set_t >() );

    /* --------------------------------------------------------------------- */

    static constexpr npart_type NUM_PARTICLES = npart_type{ 100000 };
    static constexpr real_type ACTIVE_TRESHOLD = real_type{ 0.1 };

    std::mt19937_64 prng( std::mt19937_64::result_type{ 20210212 } );

    std::uniform_real_distribution< real_type > x_dist(
        real_type{ -1e-5 }, real_type{ 1e-5 } );

    std::uniform_real_distribution< real_type > y_dist(
        real_type{ -1e-5 }, real_type{ 1e-5 } );

    std::uniform_real_distribution< real_type > px_dist(
        real_type{ -1e-6 }, real_type{ 1e-6 } );

    std::uniform_real_distribution< real_type > py_dist(
        real_type{ -1e-6 }, real_type{ 1e-6 } );

    std::uniform_real_distribution< real_type > zeta_dist(
        real_type{ -1e-2 }, real_type{ 1e-2 } );

    std::uniform_real_distribution< real_type > delta_dist(
        real_type{ -1e-6 }, real_type{ 1e-6 } );

    std::uniform_int_distribution< index_type > id_dist(
        index_type{ SIXTRL_PARTICLE_MIN_LEGAL_ID },
        index_type{ SIXTRL_PARTICLE_MAX_LEGAL_ID } );

    std::uniform_int_distribution< index_type > at_elem_dist(
        index_type{ SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT },
        index_type{ SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT } );

    std::uniform_int_distribution< index_type > at_turn_dist(
        index_type{ SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN },
        index_type{ SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN } );

    std::uniform_real_distribution< real_type > state_dist(
        real_type{ 0.0 }, real_type{ 1.0 } );

    std::uniform_int_distribution< size_type > num_mass0_dist(
        size_type{ 1 }, size_type{ 238 } );

    std::uniform_int_distribution< index_type > num_charge0_dist(
        index_type{ -20 }, index_type{ 20 } );

    std::uniform_real_distribution< real_type > charge_ratio_dist(
        real_type{ -1.0 }, real_type{ 1.0 } );

    std::uniform_real_distribution< real_type > mass_ratio_dist(
        real_type{ 0.8 }, real_type{ 1.0 } );

    std::uniform_real_distribution< real_type > s_dist(
        real_type{ 0.0 }, real_type{ 10000.0 } );

    std::uniform_real_distribution< real_type > beta0_dist(
        real_type{ 1e-3 }, real_type{ 1.0 } );

    std::uniform_real_distribution< real_type > gamma0_dist(
        real_type{ 1.0 }, real_type{ 1.0e5 } );

    std::uniform_real_distribution< real_type > p0c_dist(
        real_type{ 0.1 }, real_type{ 7.0e12 } );

    /* --------------------------------------------------------------------- */

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* cbuffer = ::NS(CBuffer_new)();

    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(Particles)* pset1 =
        ::NS(Particles_cbuffer_new)( cbuffer, NUM_PARTICLES );

    ASSERT_TRUE( pset1 != nullptr );
    ASSERT_TRUE( ::NS(Particles_max_num_particles)( pset1 ) == NUM_PARTICLES );
    ASSERT_TRUE( ::NS(Particles_num_particles)( pset1 ) == NUM_PARTICLES );

    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(Particles)* pset2 =
        ::NS(Particles_cbuffer_new)( cbuffer, NUM_PARTICLES );

    ASSERT_TRUE( pset2 != nullptr );
    ASSERT_TRUE( ::NS(Particles_max_num_particles)( pset2 ) == NUM_PARTICLES );
    ASSERT_TRUE( ::NS(Particles_num_particles)( pset2 ) == NUM_PARTICLES );

    pset1 = ::NS(Particles_from_cbuffer)( cbuffer, 0u );
    ASSERT_TRUE( pset1 != nullptr );
    ASSERT_TRUE( pset1 != pset2 );

    ASSERT_TRUE( ::NS(Particles_max_num_particles)( pset1 ) ==
                 ::NS(Particles_max_num_particles)( pset2 ) );

    ASSERT_TRUE( ::NS(Particles_num_particles)( pset1 ) ==
                 ::NS(Particles_num_particles)( pset2 ) );

    /* --------------------------------------------------------------------- */

    ASSERT_TRUE( st::STATUS_SUCCESS == st::testlib::Particles_init_random( pset1,
        prng, x_dist, y_dist, px_dist, py_dist, zeta_dist, delta_dist,
            state_dist, ACTIVE_TRESHOLD, at_elem_dist, at_turn_dist, id_dist,
                charge_ratio_dist, mass_ratio_dist, num_charge0_dist,
                    num_mass0_dist, beta0_dist, gamma0_dist, p0c_dist,
                        s_dist ) );

    for( npart_type ii = npart_type{ 0 } ; ii < NUM_PARTICLES ; ++ii )
    {
        SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle) p;

        #if defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) && \
                   ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER == 1 )
        ASSERT_TRUE( st::STATUS_SUCCESS ==
            ::NS(SingleParticleView_init_from_pset)( &p, pset1, ii ) );
        #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

        ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Particles_to_single_particle)(
            pset1, ii, &p ) );

        ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Particles_from_single_particle)(
            pset2, ii, &p ) );
    }

    ASSERT_TRUE( 0 == ::NS(Particles_compare)( pset1, pset2 ) );

    ASSERT_TRUE( st::STATUS_SUCCESS == st::testlib::Particles_init_random( pset1,
        prng, x_dist, y_dist, px_dist, py_dist, zeta_dist, delta_dist,
            state_dist, ACTIVE_TRESHOLD, at_elem_dist, at_turn_dist, id_dist,
                charge_ratio_dist, mass_ratio_dist, num_charge0_dist,
                    num_mass0_dist, beta0_dist, gamma0_dist, p0c_dist,
                        s_dist ) );

    ASSERT_TRUE( 0 != ::NS(Particles_compare)( pset1, pset2 ) );

    for( npart_type ii = npart_type{ 0 } ; ii < NUM_PARTICLES ; ++ii )
    {
        SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle) p;

        #if defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) && \
                   ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER == 1 )
        ASSERT_TRUE( st::STATUS_SUCCESS ==
            ::NS(SingleParticleView_init_from_pset)( &p, pset2, ii ) );
        #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

        ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Particles_to_single_particle)(
            pset2, ii, &p ) );

        ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Particles_from_single_particle)(
            pset1, ii, &p ) );
    }

    ASSERT_TRUE( 0 == ::NS(Particles_compare)( pset1, pset2 ) );

    /* --------------------------------------------------------------------- */
    /* cleanup */

    NS(CBuffer_delete)( cbuffer );
}
