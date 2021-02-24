#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sixtracklib as st
import numpy as np
from scipy.special import factorial

if __name__ == '__main__':
    EPS = float( 2.5e-16 )
    cbuffer = st.CBuffer()
    mp = st.st_Multipole( cbuffer )
    assert mp.order        == 0
    assert mp.max_order    >= 0
    assert mp.bal_length   == 2
    assert mp.bal_capacity >= 2
    assert np.allclose( mp.length, 0.0, 0.0, EPS )
    assert np.allclose( mp.hxl, 0.0, 0.0, EPS )
    assert np.allclose( mp.hyl, 0.0, 0.0, EPS )

    mp = None
    in_bal_values = np.array( [ 0.0, 0.0, 0.0, -0.1 ], dtype=np.float64 )
    mp = st.st_Multipole( cbuffer, 0.5, -0.25, 0.25, in_bal_values )
    assert mp.order        == 1
    assert mp.max_order    >= 1
    assert mp.bal_length   == 4
    assert mp.bal_capacity >= 4
    assert np.allclose( mp.length, 0.5, 0.0, EPS )
    assert np.allclose( mp.hxl, -0.25, 0.0, EPS )
    assert np.allclose( mp.hyl, +0.25, 0.0, EPS )
    for ii in range( 0, mp.bal_length ):
        assert np.allclose( mp.bal( ii ), in_bal_values[ ii ], 0.0, EPS )

    mp = None
    in_knl = np.array( [ 0.0, -0.1 ], dtype=np.float64 )
    in_ksl = np.array( [ 0.0,  0.0,  0.0,  0.01 ], dtype=np.float64 )
    mp = st.st_Multipole( cbuffer, 1.0, 0.0, -0.5, in_knl, in_ksl )
    assert mp.order == ( max( 1, max( len( in_knl ), len( in_ksl ) ) ) - 1 )
    assert mp.bal_length == 2 * max( len( in_knl ), len( in_ksl ) )
    assert mp.bal_capacity >= mp.bal_length
    assert np.allclose( mp.length, 1.0, 0.0, EPS )
    assert np.allclose( mp.hxl, +0.0, 0.0, EPS )
    assert np.allclose( mp.hyl, -0.5, 0.0, EPS )

    for ii in range( 0, len( in_knl ) ):
        assert np.allclose( mp.knl( ii ), in_knl[ ii ], 0.0, EPS )
        assert np.allclose( mp.bal( 2 * ii ) * factorial( ii, exact=True ),
                            in_knl[ ii ], 0.0, EPS )

    for ii in range( 0, len( in_ksl ) ):
        assert np.allclose( mp.ksl( ii ), in_ksl[ ii ], 0.0, EPS )
        assert np.allclose( mp.bal( 2 * ii + 1 ) * factorial( ii, exact=True ),
                            in_ksl[ ii ], 0.0, EPS )

    mp = None
    mp = st.st_Multipole( cbuffer, 1.0, 0.25, -0.25, None, order=2 )
    assert mp.order == 2
    assert mp.max_order == 2
    assert mp.bal_length == 6
    assert mp.bal_capacity == 6
    assert np.allclose( mp.length, 1.0, 0.0, EPS )
    assert np.allclose( mp.hxl, +0.25, 0.0, EPS )
    assert np.allclose( mp.hyl, -0.25, 0.0, EPS )
    for ii in range( 0, mp.bal_length ):
        assert np.allclose( mp.bal( ii ), 0.0, 0.0, EPS )

    mp = None
    in_knl = np.array( [ 0.0, -0.1 ], dtype=np.float64 )
    mp = st.st_Multipole( cbuffer, 0.4, -0.25, 0.25, knl=in_knl, ksl=None )
    assert mp.order == 1
    assert mp.max_order == 1
    assert mp.bal_length == 4
    assert mp.bal_capacity == 4
    assert np.allclose( mp.length, 0.4, 0.0, EPS )
    assert np.allclose( mp.hxl, -0.25, 0.0, EPS )
    assert np.allclose( mp.hyl, +0.25, 0.0, EPS )
    for ii in range( 0, len( in_knl ) ):
        assert np.allclose( mp.knl( ii ), in_knl[ ii ], 0.0, EPS )
        assert np.allclose( mp.bal( 2 * ii ) * factorial( ii, exact=True ),
                            in_knl[ ii ], 0.0, EPS )
    for ii in range( 0, mp.order + 1 ):
        assert np.allclose( mp.ksl( ii ), 0.0, 0.0, EPS )
        assert np.allclose( mp.bal( 2 * ii + 1 ), 0.0, 0.0, EPS )

    mp = None
    mp = st.st_Multipole.CREATE_NEW( cbuffer, 2 )
    assert mp.order == 2
    assert mp.max_order == 2
    assert mp.bal_length == 6
    assert mp.bal_capacity == 6
    assert np.allclose( mp.length, 0.0, 0.0, EPS )
    assert np.allclose( mp.hxl, 0.0, 0.0, EPS )
    assert np.allclose( mp.hyl, 0.0, 0.0, EPS )
    for ii in range( 0, mp.bal_length ):
        assert np.allclose( mp.bal( ii ), 0.0, 0.0, EPS )
