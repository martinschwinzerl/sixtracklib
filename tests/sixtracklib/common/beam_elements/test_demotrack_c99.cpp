#include <cstdint>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/cobjects/cbuffer.h"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/beam_elements/definitions.h"
#include "sixtracklib/common/beam_elements/demotrack.h"
#include "sixtracklib/common/generated/path.h"

#include "sixtracklib/testlib.h"

TEST( C99CommonBeamElementsDemotrack, ConvertLhcNoBBTestdata )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;
    using real_type  = st::be_real_type;

    std::ostringstream path;
    path << ::NS(PATH_TO_BASE_DIR)
         << "/tests/testdata/lhc_no_bb/cobj_lattice.bin";

    st::CBuffer lattice( path.str() );
    ASSERT_TRUE( !lattice.needs_remapping() );
    ASSERT_TRUE( lattice.num_objects() > st_size_t{ 0 } );
    ASSERT_TRUE( lattice.as_c_api() != nullptr );

    ASSERT_TRUE( ::NS(Demotrack_belems_can_convert_cobj_index_range)(
        ::NS(CBuffer_const_objects_begin)( lattice.as_c_api() ),
        ::NS(CBuffer_const_objects_end)( lattice.as_c_api() ) ) );

    st_size_t const requ_num_slots =
        ::NS(Demotrack_belems_requ_num_slots_for_cobj_index_range)(
            ::NS(CBuffer_const_objects_begin)( lattice.as_c_api() ),
            ::NS(CBuffer_const_objects_end)( lattice.as_c_api() ) );

    ASSERT_TRUE( requ_num_slots > st::size_type{ 0 } );

    std::vector< real_type > flat_buffer( requ_num_slots, double{ 0. } );

    ASSERT_TRUE( requ_num_slots ==
        ::NS(Demotrack_belems_cbuffer_to_flat_buffer_real)(
            flat_buffer.size(), flat_buffer.data(), lattice.as_c_api() ) );

    ASSERT_TRUE( lattice.num_objects() ==
        ::NS(Demotrack_belems_num_stored_objects)(
            flat_buffer.data(), flat_buffer.size() ) );

    st_size_t slot_idx = st_size_t{ 0 };

    for( st_size_t ii = 0u ; ii < lattice.num_objects() ; ++ii )
    {
        ASSERT_TRUE( slot_idx < flat_buffer.size() );

        ::NS(demotrack_belement_type) const dt_type_id =
            ::NS(Demotrack_belems_type_id_from_storage)(
                flat_buffer.data(), flat_buffer.size(), slot_idx );

        ASSERT_TRUE( dt_type_id != ::NS(DEMOTRACK_BEAM_ELEMENT_UNKNOWN) );

        st::cobj_obj_id_type const cobj_type_id = lattice.obj_typeid( ii );

        ASSERT_TRUE( cobj_type_id != st::COBJECTS_TYPE_ID_ILLEGAL );
        ASSERT_TRUE( cobj_type_id != st::COBJECTS_TYPE_ID_UNDEFINED );
        ASSERT_TRUE( dt_type_id ==
            ::NS(Demotrack_belems_type_id_from_cobj_type_id)( cobj_type_id ) );

        st_size_t const elem_num_slots =
            ::NS(Demotrack_belems_requ_num_slots_for_type_id)( dt_type_id );

        ASSERT_TRUE( elem_num_slots > st_size_t{ 0 } );
        ASSERT_TRUE( elem_num_slots + slot_idx <= flat_buffer.size() );
        slot_idx += elem_num_slots;
    }
}

