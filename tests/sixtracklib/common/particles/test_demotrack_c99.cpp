#include <algorithm>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/particles/definitions.h"
#include "sixtracklib/common/particles/demotrack.h"
#include "sixtracklib/common/cobjects/cbuffer.h"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/generated/path.h"

#include "sixtracklib/testlib.h"

TEST( C99CommonParticlesDemotrack, CObjToDemotrackAndBack )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;
    using npart_type = st::particles_num_type;
    using dt_particle_type  = ::NS(DemotrackParticle);
    using dt_pset_type = std::vector< dt_particle_type >;

    std::ostringstream path;
    path << ::NS(PATH_TO_BASE_DIR)
         << "/tests/testdata/lhc_no_bb/cobj_particles_sixtrack.bin";

    st::CBuffer in_pset_buffer( path.str() );
    ASSERT_TRUE( !in_pset_buffer.needs_remapping() );
    ASSERT_TRUE( in_pset_buffer.num_objects() > st_size_t{ 0 } );
    ASSERT_TRUE( in_pset_buffer.as_c_api() != nullptr );

    std::vector< dt_pset_type > dt_psets_from_particles;
    dt_psets_from_particles.reserve( in_pset_buffer.num_objects() );

    std::vector< dt_pset_type > dt_psets_from_single;
    dt_psets_from_single.reserve( in_pset_buffer.num_objects() );

    st::CBuffer cmp_pset_buffer( in_pset_buffer.capacity() );

    for( st_size_t ii = 0u ; ii < in_pset_buffer.num_objects() ; ++ii )
    {
        auto in_pset = in_pset_buffer.get_const_object< ::NS(Particles) >( ii );
        ASSERT_TRUE( in_pset != nullptr );

        auto const NUM_PARTICLES = ::NS(Particles_num_particles)( in_pset );
        ASSERT_TRUE( NUM_PARTICLES > npart_type{ 0 } );

        auto cmp_pset = ::NS(Particles_cbuffer_new)(
            cmp_pset_buffer.as_c_api(), NUM_PARTICLES );
        ASSERT_TRUE( cmp_pset != nullptr );
        ASSERT_TRUE( cmp_pset != in_pset );

        dt_psets_from_particles.push_back( dt_pset_type(
            static_cast< st_size_t >( NUM_PARTICLES ), dt_particle_type{} ) );
        ASSERT_TRUE( dt_psets_from_particles.size() ==
                     cmp_pset_buffer.num_objects() );

        for( npart_type jj = npart_type{ 0 } ; jj < NUM_PARTICLES ; ++jj  )
        {
            auto& dt_pset = dt_psets_from_particles.back()[ jj ];

            ASSERT_TRUE( st::STATUS_SUCCESS ==
                ::NS(Demotrack_particle_clear)( &dt_pset ) );

            ASSERT_TRUE( ::NS(Demotrack_particle_from_particles)(
                &dt_pset, in_pset, jj ) == st::STATUS_SUCCESS );

            ASSERT_TRUE( ::NS(Demotrack_particle_to_particles)(
                &dt_pset, cmp_pset, jj ) == st::STATUS_SUCCESS );

            ::NS(Particles_set_s)( cmp_pset, jj,
                ::NS(Particles_s)( in_pset, jj ) );
        }

        for( npart_type jj = npart_type{ 0 } ; jj < NUM_PARTICLES ; ++jj  )
        {
            auto& dt_pset = dt_psets_from_particles.back()[ jj ];

            ASSERT_TRUE( st::STATUS_SUCCESS ==
                ::NS(Demotrack_particle_clear)( &dt_pset ) );

            ASSERT_TRUE( ::NS(Demotrack_particle_from_particles)(
                &dt_pset, in_pset, jj ) == st::STATUS_SUCCESS );

            ASSERT_TRUE( ::NS(Demotrack_particle_to_particles)(
                &dt_pset, cmp_pset, jj ) == st::STATUS_SUCCESS );

            ::NS(Particles_set_s)( cmp_pset, jj,
                ::NS(Particles_s)( in_pset, jj ) );
        }

        ASSERT_TRUE( ::NS(Particles_compare)( in_pset, cmp_pset ) == 0 );

        dt_psets_from_single.push_back( dt_pset_type(
            static_cast< st_size_t >( NUM_PARTICLES ), dt_particle_type{} ) );

        ASSERT_TRUE( dt_psets_from_single.size() ==
                     cmp_pset_buffer.num_objects() );

        for( npart_type jj = npart_type{ 0 } ; jj < NUM_PARTICLES ; ++jj  )
        {
            auto& dt_pset = dt_psets_from_single.back()[ jj ];

            ASSERT_TRUE( st::STATUS_SUCCESS ==
                ::NS(Demotrack_particle_clear)( &dt_pset ) );

            ASSERT_TRUE( ::NS(Demotrack_particle_to_particles)(
                &dt_pset, cmp_pset, jj ) == st::STATUS_SUCCESS );
        }

        ASSERT_TRUE( ::NS(Particles_compare)( in_pset, cmp_pset ) != 0 );


        for( npart_type jj = npart_type{ 0 } ; jj < NUM_PARTICLES ; ++jj  )
        {
            SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle) temp;
            ASSERT_TRUE( ::NS(Particle_clear)( &temp ) == st::STATUS_SUCCESS );
            ASSERT_TRUE( ::NS(Particles_to_single_particle)(
                in_pset, jj, &temp ) == st::STATUS_SUCCESS );

            auto& dt_pset = dt_psets_from_single.back()[ jj ];

            ASSERT_TRUE( st::STATUS_SUCCESS ==
                ::NS(Demotrack_particle_clear)( &dt_pset ) );

            ASSERT_TRUE( ::NS(Demotrack_particle_from_single_particle)(
                &dt_pset, &temp ) == st::STATUS_SUCCESS );

            ASSERT_TRUE( ::NS(Demotrack_particle_to_single_particle)(
                &dt_pset, &temp ) == st::STATUS_SUCCESS );

            ::NS(Particle_set_s)( &temp, ::NS(Particles_s)( in_pset, jj ) );

            ASSERT_TRUE( ::NS(Particles_from_single_particle)(
                cmp_pset, jj, &temp ) == st::STATUS_SUCCESS );
        }

        ASSERT_TRUE( ::NS(Particles_compare)( in_pset, cmp_pset ) == 0 );
    }

    ASSERT_TRUE( in_pset_buffer.num_objects() == cmp_pset_buffer.num_objects() );

    for( st_size_t ii = 0u ; ii < in_pset_buffer.num_objects() ; ++ii )
    {
        ASSERT_TRUE( 0 == ::NS(Particles_compare)(
            in_pset_buffer.get_const_object< ::NS(Particles) >( ii ),
            cmp_pset_buffer.get_const_object< ::NS(Particles) >( ii ) ) );
    }
}
