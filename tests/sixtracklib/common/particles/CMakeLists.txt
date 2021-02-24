if( GTEST_FOUND )

    set( UNIT_TEST_TARGETS )
    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    # ==========================================================================
    # test_single_particle_common_c99:

    add_executable( test_single_particle_common_c99 test_single_particle_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_single_particle_common_c99 )
    add_test( C99_Common_Particles_SingleParticle test_single_particle_common_c99 )

    # ==========================================================================
    # test_particles_common_c99:

    add_executable( test_particles_common_c99     test_particles_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}   test_particles_common_c99 )
    add_test( C99_Common_Particles_Particles      test_particles_common_c99 )

    # ==========================================================================
    # test_particles_single_particle_common_c99:

    add_executable( test_particles_single_particle_common_c99
        test_particles_single_particle_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
        test_particles_single_particle_common_c99 )

    add_test( C99_Common_Particles_ParticlesSingleParticle
        test_particles_single_particle_common_c99 )

    # ==========================================================================
    # test_particles_single_particle_view_common_c99:

    add_executable( test_particles_single_particle_view_common_c99
        test_particles_single_particle_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
        test_particles_single_particle_view_common_c99 )

    target_compile_definitions(
        test_particles_single_particle_view_common_c99
        PRIVATE -DSIXTRL_USE_SINGLE_PARTICLE_ADAPTER=1 )

    add_test( C99_Common_Particles_ParticlesSingleParticle_View
        test_particles_single_particle_view_common_c99 )

    # ==========================================================================
    # test_particles_addr_common_c99:

#     add_executable( test_particles_addr_common_c99  test_drift_c99.cpp )
#     set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}  test_be_drift_common_c99 )
#     add_test( C99_Common_BeamElements_Drift      test_be_drift_common_c99 )

    if( SIXTRACKL_ENABLE_DEMOTRACK )
        # ==========================================================================
        # test_particles_demotrack_common_c99:

        add_executable( test_particles_demotrack_common_c99
            test_demotrack_c99.cpp )

        set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
            test_particles_demotrack_common_c99 )

        add_test( C99_Common_Particles_Demotrack
            test_particles_demotrack_common_c99 )

        # ==========================================================================
        # test_particles_demotrack_common_c99:

        add_executable( test_particles_demotrack_view_common_c99
            test_demotrack_c99.cpp )

        target_compile_definitions( test_particles_demotrack_view_common_c99
            PRIVATE -DSIXTRL_USE_SINGLE_PARTICLE_ADAPTER=1 )

        set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
            test_particles_demotrack_view_common_c99 )

        add_test( C99_Common_Particles_Demotrack
            test_particles_demotrack_view_common_c99 )

    endif()


    # *************************************************************************
    # Set all properties:

    set_property( TARGET ${UNIT_TEST_TARGETS} APPEND PROPERTY
        INCLUDE_DIRECTORIES $<BUILD_INTERFACE:${SIXTRACKL_GTEST_INCLUDE_DIRS}> )

    set_property( TARGET ${UNIT_TEST_TARGETS}
                  PROPERTY LINK_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES} )

    set_property( TARGET ${UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD 11 )
    set_property( TARGET ${UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD_REQUIRED ON )

    set_property( TARGET ${UNIT_TEST_TARGETS}
                  APPEND PROPERTY COMPILE_OPTIONS
                  ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

endif()

