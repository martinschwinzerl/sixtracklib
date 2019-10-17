#include "sixtracklib/opencl/track_job_cl.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>
#include <utility>

#include <gtest/gtest.h>

#include "sixtracklib/common/buffer.hpp"
#include "sixtracklib/common/be_cavity/be_cavity.hpp"
#include "sixtracklib/common/be_drift/be_drift.hpp"
#include "sixtracklib/opencl/context.h"
#include "sixtracklib/testlib.hpp"

TEST( CXX_OpenCL_ClTrackJobUpdateBeamElementsRegionTest, BasicUsage )
{
    namespace st      = SIXTRL_CXX_NAMESPACE;
    namespace st_test = SIXTRL_CXX_NAMESPACE::tests;

    using buffer_t     = st::Buffer;
    using track_job_t  = st::TrackJobCl;
    using cavity_t     = st::Cavity;
    using status_t     = st::arch_status_t;
    using size_t       = track_job_t::size_type;

    /* Load lattice from binary dump */
    buffer_t lattice( ::NS(PATH_TO_BEAMBEAM_BEAM_ELEMENTS) );
    buffer_t pb( ::NS(PATH_TO_BEAMBEAM_PARTICLES_DUMP) );

    /* Prepare list for cavities */
    std::vector< size_t >   cavity_indices;
    std::vector< size_t >   cavity_offsets;
    std::vector< size_t >   cavity_lengths;
    std::vector< cavity_t > cavities;

    /* Find all offsets, lengths and initial cavity values */

    size_t const num_beam_elements = lattice.getNumObjects();

    for( size_t ii = size_t{ 0 } ; ii < num_beam_elements ; ++ii )
    {
        cavity_t const* ptr_cavity = lattice.get< cavity_t >( ii );

        if( ptr_cavity != nullptr )
        {
            cavity_indices.push_back( ii );
            cavity_lengths.push_back( sizeof( cavity_t ) );
            cavity_offsets.push_back( reinterpret_cast< uintptr_t >(
                ptr_cavity ) - lattice.getDataBeginAddr() );

            cavities.push_back( *ptr_cavity );
        }
    }

    size_t const num_cavities = cavities.size();
    ASSERT_TRUE( num_cavities > size_t{ 0 } );

    /* Initialize an OpenCL controller */

    track_job_t track_job( "0.0", pb, lattice );

    for( size_t ii = size_t{ 0 } ; ii < num_cavities ; ++ii )
    {
        size_t const idx = cavity_indices[ ii ];
        cavity_t const* ptr_orig_cavity = lattice.get< cavity_t >( idx );
        ASSERT_TRUE( ptr_orig_cavity != nullptr );

        cavity_t* ptr_cavity = &cavities[ ii ];
        ASSERT_TRUE( ptr_cavity != nullptr );
        ASSERT_TRUE( 0 == ::NS(Cavity_compare_values)(
            ptr_orig_cavity->getCApiPtr(), ptr_cavity->getCApiPtr() ) );

        ptr_cavity->voltage *= double{ 1.05 };

        if( ptr_cavity->voltage < double{ 1e-16 } )
                ptr_cavity->voltage += 1e3;

        ASSERT_TRUE( 0 != ::NS(Cavity_compare_values)(
            ptr_orig_cavity->getCApiPtr(), ptr_cavity->getCApiPtr() ) );

        status_t status = track_job.updateBeamElementsRegion(
            cavity_offsets[ ii ], sizeof( cavity_t ), ptr_cavity );

        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }

    /* Read back the values from the device to lattice */
    track_job.collectBeamElements();

    /* Compare the values with the expected state */
    for( size_t ii = size_t{ 0 } ; ii < num_cavities ; ++ii )
    {
        size_t const idx = cavity_indices[ ii ];
        cavity_t const* ptr_orig_cavity = lattice.get< cavity_t >( idx );
        ASSERT_TRUE( ptr_orig_cavity != nullptr );

        cavity_t* ptr_cavity = &cavities[ ii ];
        ASSERT_TRUE( ptr_cavity != nullptr );
        ASSERT_TRUE( 0 == ::NS(Cavity_compare_values)(
            ptr_orig_cavity->getCApiPtr(), ptr_cavity->getCApiPtr() ) );
    }

    /* Update all cavities again */
    std::vector< void const* > ptr_cavities_begins;

    for( size_t ii = size_t{ 0 } ; ii < num_cavities ; ++ii )
    {
        cavity_t* ptr_cavity = &cavities[ ii ];
        ASSERT_TRUE( ptr_cavity != nullptr );
        ptr_cavity->voltage /= double{ 1.05 };
        ptr_cavities_begins.push_back( ptr_cavity );
    }

    status_t status = track_job.updateBeamElementsRegions( num_cavities,
        cavity_offsets.data(), cavity_lengths.data(), ptr_cavities_begins.data() );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    /* Read back the modified lattice */
    track_job.collectBeamElements();

    /* Compare the values with the expected state */
    for( size_t ii = size_t{ 0 } ; ii < num_cavities ; ++ii )
    {
        size_t const idx = cavity_indices[ ii ];
        cavity_t const* ptr_orig_cavity = lattice.get< cavity_t >( idx );
        ASSERT_TRUE( ptr_orig_cavity != nullptr );

        cavity_t* ptr_cavity = &cavities[ ii ];
        ASSERT_TRUE( ptr_cavity != nullptr );
        ASSERT_TRUE( 0 == ::NS(Cavity_compare_values)(
            ptr_orig_cavity->getCApiPtr(), ptr_cavity->getCApiPtr() ) );
    }
}

/* end: tests/sixtracklib/opencl/test_track_job_update_region_cxx.cpp */
