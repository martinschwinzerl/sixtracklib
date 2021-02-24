#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sixtracklib as st
import numpy as np
import os
import argparse

if __name__ == '__main__':
    if not st.Demotrack_enabled():
        print( "demotrack not enabled -> " +
               "skipping demotrack data generation test" )
        pass

    parser = argparse.ArgumentParser()
    parser.add_argument( "path", help="path to testdata dir", type=str,
                         default="../tests/testdata" )
    args = parser.parse_args()

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    path_to_scenario = os.path.join( args.path, "lhc_no_bb" )
    if not os.path.isdir( path_to_scenario ):
        raise RuntimeError(
            f"path_to_scenario {path_to_scenario} not available ->" +
            "check path passed by CMake to this test" )

    path_to_cobj_lattice = os.path.join( path_to_scenario, "cobj_lattice.bin" )
    if not os.path.isfile( path_to_cobj_lattice ):
        raise RuntimeError(
            f"path_to_cobj_lattice {path_to_cobj_lattice} not available -> " +
            "consider re-running the testdata generators" )

    cbuffer = st.CBuffer( path_to_cobj_lattice )
    assert cbuffer.num_objects > 0
    assert st.Demotrack_belems_can_convert( cbuffer )

    predicted_num_slots = st.Demotrack_belems_requ_num_slots( cbuffer )
    assert predicted_num_slots > 0
    assert predicted_num_slots > cbuffer.num_objects

    dt_flat_buffer = st.Demotrack_belems_convert( cbuffer )
    assert isinstance( dt_flat_buffer, np.ndarray )
    assert len( dt_flat_buffer ) == predicted_num_slots
    assert st.Demotrack_belems_num_stored_objects( dt_flat_buffer ) == \
           cbuffer.num_objects

    slot_idx = 0
    for ii in range( 0, cbuffer.num_objects ):
        assert len( dt_flat_buffer ) > slot_idx
        dt_cobj_id = st.Demotrack_belems_type_id( dt_flat_buffer, slot_idx )
        assert dt_cobj_id != 0 # 0 == st_DEMOTRACK_BEAM_ELEM_UNDEFINED

        elem_num_slots = st.Demotrack_belems_requ_num_slots( dt_cobj_id )
        assert elem_num_slots > 1
        assert elem_num_slots + slot_idx <= len( dt_flat_buffer )
        slot_idx += elem_num_slots

