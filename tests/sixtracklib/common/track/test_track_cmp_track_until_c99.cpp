#include <algorithm>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/cobjects/cbuffer.h"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/particles/particle.h"
#include "sixtracklib/common/track/track.h"
#include "sixtracklib/common/generated/path.h"

#include "sixtracklib/testlib.h"

TEST( C99CommonTrackCmpTrackUntil, TrackUntil100LhcNoBB )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using pset_type = ::NS(Particles);
    using npart_type = st::particles_num_type;
    using real_type  = st::particle_real_type;
    using index_type = st::particle_index_type;
    using st_size_t  = st::cobj_size_type;

    /* TODO: Check why the zeta value is off by 1e-11! */
    static real_type const ABS_TOLERANCE = real_type{ 1e-10 };
    static real_type const REL_TOLERANCE = real_type{ 0. };

    std::ostringstream path;
    path << ::NS(PATH_TO_BASE_DIR) << "tests/testdata/lhc_no_bb/";
    std::string const path_to_testdata_dir = path.str();
    path << "cobj_lattice.bin";

    st::CBuffer lattice( path.str() );
    ASSERT_TRUE( !lattice.needs_remapping() );
    ASSERT_TRUE( lattice.num_objects() > st_size_t{ 0 } );
    ASSERT_TRUE( lattice.as_c_api() != nullptr );

    path.str( "" );
    path << path_to_testdata_dir << "cobj_initial_particles.bin";
    st::CBuffer track_pbuffer( path.str() );
    ASSERT_TRUE( !track_pbuffer.needs_remapping() );
    ASSERT_TRUE(  track_pbuffer.num_objects() > st_size_t{ 0 } );
    ASSERT_TRUE(  track_pbuffer.as_c_api() != nullptr );

    path.str( "" );
    path << path_to_testdata_dir << "cobj_particles_until_turn_100.bin";
    st::CBuffer cmp_pbuffer( path.str() );
    ASSERT_TRUE( !cmp_pbuffer.needs_remapping() );
    ASSERT_TRUE(  cmp_pbuffer.num_objects() > st_size_t{ 0 } );
    ASSERT_TRUE(  cmp_pbuffer.as_c_api() != nullptr );

    st::CBuffer diff_pbuffer( cmp_pbuffer.num_slots(), cmp_pbuffer.num_objects(),
        cmp_pbuffer.num_pointers(), cmp_pbuffer.num_garbage(),
            cmp_pbuffer.slot_size() );
    ASSERT_TRUE( diff_pbuffer.as_c_api() != nullptr );

    SIXTRL_TRACK_ARGPTR_DEC ::NS(TrackConfig)* config = nullptr;

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Track_testlib_until_turn_cbuffer)(
        track_pbuffer.as_c_api(), cmp_pbuffer.as_const_c_api(),
            lattice.as_c_api(), diff_pbuffer.as_c_api(),
            index_type{ 100 }, index_type{ 0 }, st_size_t{ 0 }, config ) );

    SIXTRL_ARGPTR_DEC st_size_t first_fail_pset_idx = st_size_t{ 0 };
    SIXTRL_ARGPTR_DEC npart_type first_fail_particle_idx = npart_type{ 0 };

    if( ::NS(Track_testlib_compare_all_particle_sets_cbuffer)(
            track_pbuffer.as_c_api(), cmp_pbuffer.as_c_api(), REL_TOLERANCE,
                ABS_TOLERANCE, &first_fail_pset_idx, &first_fail_particle_idx )
                    != st::STATUS_SUCCESS )
    {
        ASSERT_TRUE( first_fail_pset_idx < cmp_pbuffer.num_objects() );

        auto pset_cmp = cmp_pbuffer.get_const_object< pset_type >(
            first_fail_pset_idx );

        auto pset_track = track_pbuffer.get_const_object< pset_type >(
            first_fail_pset_idx );

        auto pset_diff = diff_pbuffer.get_const_object< pset_type >(
            first_fail_pset_idx );

        ASSERT_TRUE( pset_cmp   != nullptr );
        ASSERT_TRUE( pset_track != nullptr );
        ASSERT_TRUE( pset_diff  != nullptr );

        ASSERT_TRUE( ::NS(Particles_num_particles)( pset_track ) >
                     first_fail_particle_idx );

        ASSERT_TRUE( ::NS(Particles_num_particles)( pset_cmp ) >
                     first_fail_particle_idx );

        ASSERT_TRUE( ::NS(Particles_num_particles)( pset_diff ) >
                     first_fail_particle_idx );

        std::cout << "first_fail_elem_idx = " << first_fail_pset_idx << "\r\n";
        st::testlib::Particles_diff_to_stream( std::cout,
            *pset_cmp, *pset_track, *pset_diff, first_fail_particle_idx );

        ASSERT_TRUE( 0 == ::NS(Particles_compare_with_tolerances)(
            pset_cmp, pset_track, REL_TOLERANCE, ABS_TOLERANCE ) );

    }
}

TEST( C99CommonTrackCmpTrackUntil, TrackUntil100SIS100Coasting )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using pset_type = ::NS(Particles);
    using npart_type = st::particles_num_type;
    using real_type  = st::particle_real_type;
    using index_type = st::particle_index_type;
    using st_size_t  = st::cobj_size_type;

    /* TODO: Find out why the absolute difference is so large in this scenario
     *       -> given the distribution along the variables, the cerr / wfun
     *       implementation differences between SixTrackLib and pysixtrack
     *       may be the most likely explanatione */

    static real_type const ABS_TOLERANCE = real_type{ 1e-8 };
    static real_type const REL_TOLERANCE = real_type{ 0. };

    std::ostringstream path;
    path << ::NS(PATH_TO_BASE_DIR) << "tests/testdata/sis100_coasting/";
    std::string const path_to_testdata_dir = path.str();
    path << "cobj_lattice.bin";

    st::CBuffer lattice( path.str() );
    ASSERT_TRUE( !lattice.needs_remapping() );
    ASSERT_TRUE( lattice.num_objects() > st_size_t{ 0 } );
    ASSERT_TRUE( lattice.as_c_api() != nullptr );

    path.str( "" );
    path << path_to_testdata_dir << "cobj_initial_particles.bin";
    st::CBuffer track_pbuffer( path.str() );
    ASSERT_TRUE( !track_pbuffer.needs_remapping() );
    ASSERT_TRUE(  track_pbuffer.num_objects() > st_size_t{ 0 } );
    ASSERT_TRUE(  track_pbuffer.as_c_api() != nullptr );

    path.str( "" );
    path << path_to_testdata_dir << "cobj_particles_until_turn_100.bin";
    st::CBuffer cmp_pbuffer( path.str() );
    ASSERT_TRUE( !cmp_pbuffer.needs_remapping() );
    ASSERT_TRUE(  cmp_pbuffer.num_objects() > st_size_t{ 0 } );
    ASSERT_TRUE(  cmp_pbuffer.as_c_api() != nullptr );

    st::CBuffer diff_pbuffer( cmp_pbuffer.num_slots(), cmp_pbuffer.num_objects(),
        cmp_pbuffer.num_pointers(), cmp_pbuffer.num_garbage(),
            cmp_pbuffer.slot_size() );
    ASSERT_TRUE( diff_pbuffer.as_c_api() != nullptr );

    SIXTRL_TRACK_ARGPTR_DEC ::NS(TrackConfig)* config = nullptr;

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Track_testlib_until_turn_cbuffer)(
        track_pbuffer.as_c_api(), cmp_pbuffer.as_const_c_api(),
            lattice.as_c_api(), diff_pbuffer.as_c_api(),
            index_type{ 100 }, index_type{ 0 }, st_size_t{ 0 }, config ) );

    SIXTRL_ARGPTR_DEC st_size_t first_fail_pset_idx = st_size_t{ 0 };
    SIXTRL_ARGPTR_DEC npart_type first_fail_particle_idx = npart_type{ 0 };

    if( ::NS(Track_testlib_compare_all_particle_sets_cbuffer)(
            track_pbuffer.as_c_api(), cmp_pbuffer.as_c_api(), REL_TOLERANCE,
                ABS_TOLERANCE, &first_fail_pset_idx, &first_fail_particle_idx )
                    != st::STATUS_SUCCESS )
    {
        ASSERT_TRUE( first_fail_pset_idx < cmp_pbuffer.num_objects() );

        auto pset_cmp = cmp_pbuffer.get_const_object< pset_type >(
            first_fail_pset_idx );

        auto pset_track = track_pbuffer.get_const_object< pset_type >(
            first_fail_pset_idx );

        auto pset_diff = diff_pbuffer.get_const_object< pset_type >(
            first_fail_pset_idx );

        ASSERT_TRUE( pset_cmp   != nullptr );
        ASSERT_TRUE( pset_track != nullptr );
        ASSERT_TRUE( pset_diff  != nullptr );

        ASSERT_TRUE( ::NS(Particles_num_particles)( pset_track ) >
                     first_fail_particle_idx );

        ASSERT_TRUE( ::NS(Particles_num_particles)( pset_cmp ) >
                     first_fail_particle_idx );

        ASSERT_TRUE( ::NS(Particles_num_particles)( pset_diff ) >
                     first_fail_particle_idx );

        std::cout << "first_fail_elem_idx = " << first_fail_pset_idx << "\r\n";
        st::testlib::Particles_diff_to_stream( std::cout,
            *pset_cmp, *pset_track, *pset_diff, first_fail_particle_idx );

        ASSERT_TRUE( 0 == ::NS(Particles_compare_with_tolerances)(
            pset_cmp, pset_track, REL_TOLERANCE, ABS_TOLERANCE ) );

    }
}
