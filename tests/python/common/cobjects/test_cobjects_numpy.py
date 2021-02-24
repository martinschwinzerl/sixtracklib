#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sixtracklib as st
import numpy as np

if __name__ == '__main__':
    assert st.CObjects_numpy_1d_real_length( None ) == 0
    assert st.CObjects_numpy_1d_real_stride( None ) == 8
    assert not st.CObjects_numpy_1d_real_is_dense( None )
    assert st.CObjects_numpy_1d_real_base_addr( None ) == 0

    test_a = np.zeros( 42, dtype=np.float64 )
    assert st.CObjects_numpy_1d_real_length( test_a ) == len( test_a )
    assert st.CObjects_numpy_1d_real_stride( test_a ) == 8
    assert st.CObjects_numpy_1d_real_is_dense( test_a )
    assert st.CObjects_numpy_1d_real_base_addr( test_a ) != 0
