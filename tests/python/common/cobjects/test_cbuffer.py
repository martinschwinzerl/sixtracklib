#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sixtracklib as st
import numpy as np

if __name__ == '__main__':
    buffer = st.CBuffer()
    slot_size = buffer.slot_size
    assert slot_size > 0
    assert slot_size == st.CObjects_default_slot_size()

    assert buffer.size == st.CBuffer.MIN_BUFFER_SIZE()
    assert buffer.capacity >= st.CBuffer.MIN_BUFFER_SIZE()
    assert buffer.base_address != 0
    assert buffer.n_slots == 0
    assert buffer.n_objects == 0
    assert buffer.n_pointers == 0
    assert buffer.n_garbage == 0

    if st.Testlib_enabled():
        obj1 = st.st_CObjTestNoPtrs( buffer )
        assert isinstance( obj1, st.st_CObjTestNoPtrs )
        assert buffer.n_pointers   == 0
        assert buffer.n_objects    == 1
        assert buffer.n_slots == obj1.cobj_required_num_bytes(
                    slot_size ) / slot_size
        prev_n_slots = buffer.n_slots

        obj1 = None
        obj2 = st.st_CObjTestNoPtrs.CREATE_NEW( buffer )
        assert isinstance( obj2, st.st_CObjTestNoPtrs )
        assert buffer.n_pointers   == 0
        assert buffer.n_objects    == 2
        assert buffer.n_slots == prev_n_slots + \
            obj2.cobj_required_num_bytes( slot_size ) / slot_size
        prev_n_slots = buffer.n_slots

        obj2 = None
        obj3 = st.st_CObjTestDataptrs( buffer, 10, 15 )
        assert isinstance( obj3, st.st_CObjTestDataptrs )
        assert obj3.b_capacity == 10
        assert obj3.b_length == obj3.b_capacity
        assert obj3.c_capacity == 15
        assert obj3.c_length == obj3.b_capacity
        assert obj3.cobj_required_num_bytes( slot_size ) > \
               st.st_CObjTestDataptrs.COBJ_RESERVED_HANDLE_SIZE( slot_size )
        assert buffer.n_pointers == st.st_CObjTestDataptrs.COBJ_NUM_DATAPTRS
        assert buffer.n_objects  == 3
        assert buffer.n_slots == prev_n_slots + \
            obj3.cobj_required_num_bytes( slot_size ) / slot_size

        obj3 = None
