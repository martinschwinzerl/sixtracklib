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

    path_to_cobj_pset = os.path.join(
        path_to_scenario, "cobj_initial_particles.bin" )
    if not os.path.isfile( path_to_cobj_pset ):
        raise RuntimeError(
            f"path_to_cobj_pset {path_to_cobj_pset} not available -> " +
            "consider re-running the testdata generators" )

    cbuffer = st.CBuffer( path_to_cobj_pset )
    cmp_buffer = st.CBuffer()
    assert cbuffer.num_objects > 0
    total_num_particles = 0
    for ii in range( 0, cbuffer.num_objects ):
        pset = st.st_Particles.GET( cbuffer, ii )
        assert pset.num_particles > 0
        total_num_particles += pset.num_particles
        cmp_pset = st.st_Particles( cmp_buffer, pset.num_particles )
        assert cmp_pset.num_particles == pset.num_particles

    assert total_num_particles > 0
    assert cmp_buffer.num_objects == cbuffer.num_objects
    dt_particles_buffer = st.st_DemotrackParticle.CREATE_ARRAY(
        total_num_particles, True )

    assert isinstance( dt_particles_buffer, np.ndarray )
    assert len( dt_particles_buffer ) == total_num_particles

    kk = 0
    dt_p = st.st_DemotrackParticle()

    for ii in range( 0, cbuffer.num_objects ):
        pset = st.st_Particles.GET( cbuffer, ii )
        cmp_pset = st.st_Particles.GET( cmp_buffer, ii )
        assert pset.num_particles == cmp_pset.num_particles
        for jj in range( 0, pset.num_particles ):
            assert 0 == dt_p.clear()
            assert 0 == dt_p.from_cobjects( pset, jj )
            assert 0 == dt_p.to_array( dt_particles_buffer, kk )
            kk += 1

            assert 0 == dt_p.to_cobjects( cmp_pset, jj )
            cmp_pset.set_s( jj, pset.s( jj ) )

    kk = 0
    for ii in range( 0, cbuffer.num_objects ):
        pset = st.st_Particles.GET( cbuffer, ii )
        cmp_pset = st.st_Particles.GET( cmp_buffer, ii )
        assert pset.num_particles == cmp_pset.num_particles
        for jj in range( 0, pset.num_particles ):
            assert 0 == dt_p.from_array( dt_particles_buffer, kk )
            kk += 1

            assert np.alltrue( pset.x( jj ) == cmp_pset.x( jj ) )
            assert np.alltrue( dt_p.x == pset.x( jj ) )

            assert np.alltrue( pset.y( jj ) == cmp_pset.y( jj ) )
            assert np.alltrue( dt_p.y == pset.y( jj ) )

            assert np.alltrue( pset.px( jj ) == cmp_pset.px( jj ) )
            assert np.alltrue( dt_p.px == pset.px( jj ) )

            assert np.alltrue( pset.py( jj ) == cmp_pset.py( jj ) )
            assert np.alltrue( dt_p.py == pset.py( jj ) )

            assert np.alltrue( pset.zeta( jj ) == cmp_pset.zeta( jj ) )
            assert np.alltrue( dt_p.zeta == pset.zeta( jj ) )

            assert np.alltrue( pset.delta( jj ) == cmp_pset.delta( jj ) )
            assert np.alltrue( dt_p.delta == pset.delta( jj ) )

            assert np.alltrue( pset.state( jj ) == cmp_pset.state( jj ) )
            assert np.alltrue( dt_p.state == pset.state( jj ) )

            assert np.alltrue( pset.at_element( jj ) ==
                               cmp_pset.at_element( jj ) )
            assert np.alltrue( dt_p.at_element == pset.at_element( jj ) )

            assert np.alltrue( pset.at_turn( jj ) == cmp_pset.at_turn( jj ) )
            assert np.alltrue( dt_p.at_turn == pset.at_turn( jj ) )

            assert np.alltrue( pset.id( jj ) == cmp_pset.id( jj ) )
            assert np.alltrue( dt_p.id == pset.id( jj ) )

            assert np.alltrue( pset.psigma( jj ) == cmp_pset.psigma( jj ) )
            assert np.alltrue( dt_p.psigma == pset.psigma( jj ) )

            assert np.alltrue( pset.rpp( jj ) == cmp_pset.rpp( jj ) )
            assert np.alltrue( dt_p.rpp == pset.rpp( jj ) )

            assert np.alltrue( pset.rvv( jj ) == cmp_pset.rvv( jj ) )
            assert np.alltrue( dt_p.rvv == pset.rvv( jj ) )

            assert np.alltrue( pset.chi( jj ) == cmp_pset.chi( jj ) )
            assert np.alltrue( dt_p.chi == pset.chi( jj ) )

            assert np.alltrue( pset.charge_ratio( jj ) ==
                               cmp_pset.charge_ratio( jj ) )
            assert np.alltrue( dt_p.charge_ratio == pset.charge_ratio( jj ) )

            assert np.alltrue( pset.charge0( jj ) == cmp_pset.charge0( jj ) )
            assert np.alltrue( dt_p.charge0 == pset.charge0( jj ) )

            assert np.alltrue( pset.mass0( jj ) == cmp_pset.mass0( jj ) )
            assert np.alltrue( dt_p.mass0 == pset.mass0( jj ) )

            assert np.alltrue( pset.beta0( jj ) == cmp_pset.beta0( jj ) )
            assert np.alltrue( dt_p.beta0 == pset.beta0( jj ) )

            assert np.alltrue( pset.gamma0( jj ) == cmp_pset.gamma0( jj ) )
            assert np.alltrue( dt_p.gamma0 == pset.gamma0( jj ) )

            assert np.alltrue( pset.p0c( jj ) == cmp_pset.p0c( jj ) )
            assert np.alltrue( dt_p.p0c == pset.p0c( jj ) )
            assert np.alltrue( pset.s( jj ) == cmp_pset.s( jj ) )

