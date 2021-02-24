#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sixtracklib as st
import numpy as np

if __name__ == '__main__':
    EPS = float( 2.5e-16 )
    cbuffer = st.CBuffer()
    p = st.st_SingleParticle( cbuffer )
    p.x = 1.0
    p.px = 0.0
    p.state = 1
    p.at_element = 42
    p.at_turn = 1000

    assert p.state == 1
    assert p.is_active
    assert not p.is_lost
    assert p.is_not_lost

    p.mark_as_lost()
    assert p.is_lost
    assert not p.is_active

    assert p.at_element == 42
    assert p.at_turn == 1000
    assert np.allclose( p.x, 1.0, 0.0, EPS )

