#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sixtracklib as st
import numpy as np
from scipy.special import factorial

if __name__ == '__main__':
    EPS = np.float64( 2e-16 )
    for ii in range( 0, 21 ):
        assert np.allclose( st.st_Math_factorial( ii ),
                            np.float64( factorial( ii, exact=True ) ),
                            np.float64( 0.0 ), EPS )

    for ii in range( 0, 21 ):
        assert np.allclose( st.st_Math_inv_factorial( ii ),
                            np.float64( 1. ) / np.float64( factorial( ii, exact=True ) ),
                            np.float64( 0.0 ), EPS )
