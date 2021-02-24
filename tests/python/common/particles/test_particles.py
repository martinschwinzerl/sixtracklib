#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sixtracklib as st
import numpy as np

if __name__ == '__main__':
    EPS = float( 2.5e-16 )
    cbuffer = st.CBuffer()
    pset1 = st.st_Particles( cbuffer, 100 )
    assert pset1.max_num_particles == 100
    assert pset1.num_particles == 100
    pset1 = None

    pset2 = st.st_Particles( cbuffer, 255 )
    pset2.set_num_particles( 100 )
    assert pset2.max_num_particles == 255
    assert pset2.num_particles == 100
    pset2 = None

    r_zeros = np.zeros( 100, dtype=np.float64 )
    pset3 = st.st_Particles( cbuffer,
        charge0=r_zeros, mass0=r_zeros, beta0=r_zeros, gamma0=r_zeros, p0c=r_zeros,
        s=r_zeros, x=np.linspace( -1.0e-5, +1.0e5, 100, dtype=np.float64 ),
        y=r_zeros, px=r_zeros, py=r_zeros, zeta=r_zeros, psigma=r_zeros,
        delta=r_zeros, rpp=np.ones( 100, dtype=np.float64 ), rvv=r_zeros,
        chi=np.ones( 100, dtype=np.float64 ),
        charge_ratio=np.ones( 100, dtype=np.float64 ),
        id=np.linspace( 0, 99, 100, dtype=np.int64 ),
        at_element=np.zeros( 100, dtype=np.int64 ),
        at_turn=np.zeros( 100, dtype=np.int64 ),
        state=np.ones( 100, dtype=np.int64 ) )
    assert pset3.max_num_particles == 100
    assert pset3.num_particles == 100

    pset1 = st.st_Particles.GET( cbuffer, 0 )
    pset2 = st.st_Particles.GET( cbuffer, 1 )
    assert pset1.max_num_particles == 100
    assert pset1.num_particles == pset2.num_particles



