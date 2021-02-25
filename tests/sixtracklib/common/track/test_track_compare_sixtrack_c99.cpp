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

TEST( C99CommonTrackCompareSixTrack, CompareLhcNoBB )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;
    using npart_type = st::particles_num_type;
    using real_type  = st::particle_real_type;

    static real_type const ABS_TOLERANCE = real_type{ 4e-14 };
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
    path << path_to_testdata_dir << "cobj_particles_sixtrack.bin";
    st::CBuffer cmp_buffer( path.str() );
    ASSERT_TRUE( !cmp_buffer.needs_remapping() );
    ASSERT_TRUE(  cmp_buffer.num_objects() > st_size_t{ 0 } );
    ASSERT_TRUE(  cmp_buffer.as_c_api() != nullptr );

    st::CBuffer track_pbuffer( cmp_buffer.num_slots(), cmp_buffer.num_objects(),
        cmp_buffer.num_pointers(), cmp_buffer.num_garbage(),
            cmp_buffer.slot_size() );
    ASSERT_TRUE( track_pbuffer.as_c_api() != nullptr );

    st::CBuffer diff_pbuffer( cmp_buffer.num_slots(), cmp_buffer.num_objects(),
        cmp_buffer.num_pointers(), cmp_buffer.num_garbage(),
            cmp_buffer.slot_size() );
    ASSERT_TRUE( diff_pbuffer.as_c_api() != nullptr );

    SIXTRL_TRACK_ARGPTR_DEC ::NS(TrackConfig)* config = nullptr;

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Track_sixtrack_sequ_by_sequ_cbuffer)(
        track_pbuffer.as_c_api(), cmp_buffer.as_const_c_api(),
            lattice.as_const_c_api(), diff_pbuffer.as_c_api(), config ) );

    ASSERT_TRUE( track_pbuffer.num_objects() + 1u ==
                 cmp_buffer.num_objects() );

    SIXTRL_ARGPTR_DEC st_size_t first_fail_elem_idx = 0u;
    SIXTRL_ARGPTR_DEC npart_type first_fail_pset_idx = 0u;

    if( st::STATUS_SUCCESS != ::NS(Track_testlib_compare_elem_by_elem_cbuffer)(
        track_pbuffer.as_const_c_api(), cmp_buffer.as_const_c_api(),
        REL_TOLERANCE, ABS_TOLERANCE, &first_fail_elem_idx,
            &first_fail_pset_idx ) )
    {
        ASSERT_TRUE( first_fail_elem_idx < track_pbuffer.num_objects() );

        auto pset_cmp = cmp_buffer.get_const_object< ::NS(Particles) >(
            first_fail_elem_idx + 1 );

        auto pset_track = track_pbuffer.get_const_object< ::NS(Particles) >(
            first_fail_elem_idx );

        auto pset_diff = diff_pbuffer.get_const_object< ::NS(Particles) >(
            first_fail_elem_idx );

        ASSERT_TRUE( pset_cmp   != nullptr );
        ASSERT_TRUE( pset_track != nullptr );
        ASSERT_TRUE( pset_diff  != nullptr );

        std::cout << "first_fail_elem_idx = " << first_fail_elem_idx << "\r\n";
        st::testlib::Particles_diff_to_stream( std::cout,
            *pset_cmp, *pset_track, *pset_diff, first_fail_pset_idx );

        ASSERT_TRUE( 0 == ::NS(Particles_compare_with_tolerances)(
            pset_cmp, pset_track, REL_TOLERANCE, ABS_TOLERANCE ) );
    }

    /* Test non-happy path */

    auto const changed_sequ_idx =
        ( track_pbuffer.num_objects() > st_size_t{ 2 } )
        ? track_pbuffer.num_objects() - st_size_t{ 2 } : st_size_t{ 0 };

    auto pset_track = track_pbuffer.get_object< ::NS(Particles) >( changed_sequ_idx );

    ASSERT_TRUE( pset_track != nullptr );
    npart_type const NUM_PARTICLES = ::NS(Particles_num_particles)( pset_track );
    ASSERT_TRUE( NUM_PARTICLES > npart_type{ 0 } );

    ::NS(Particles_add_to_x)( pset_track, NUM_PARTICLES - 1, real_type{ 0.5 } );

    ASSERT_TRUE( st::STATUS_SUCCESS !=
        ::NS(Track_testlib_compare_elem_by_elem_cbuffer)(
            track_pbuffer.as_const_c_api(), cmp_buffer.as_const_c_api(),
                REL_TOLERANCE, ABS_TOLERANCE, &first_fail_elem_idx,
                    &first_fail_pset_idx ) );

    ASSERT_TRUE( first_fail_elem_idx == changed_sequ_idx );
    ASSERT_TRUE( first_fail_pset_idx == NUM_PARTICLES -1 );
}
