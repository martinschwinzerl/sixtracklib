# ==============================================================================
# tests/sixtracklib/multiprec/particles/CMakeLists.txt

if( GTEST_FOUND )
    set( SIXTRACKL_TEST_LIBRARIES
       ${SIXTRACKL_TEST_LIBRARIES} ${SIXTRACKL_GTEST_LIBRARIES} )

    set( UNIT_TEST_TARGETS )

    # ==========================================================================
    # test_particle_unit_multiprec_cxx:

    add_executable( test_particle_unit_multiprec_cxx
                    test_particle_unit_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_particle_unit_multiprec_cxx )

    add_test( CXX_Multiprec_Particles_Particle
              test_particle_unit_multiprec_cxx )

    set_property( TEST CXX_Multiprec_Particles_Particle
                  APPEND PROPERTY DEPENDS CXX_Common_Particles_Particle )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_particle_unit_cobjects_multiprec_cxx:

    add_executable( test_particle_unit_cobjects_multiprec_cxx
                    test_particle_unit_cobjects_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_particle_unit_cobjects_multiprec_cxx )

    add_test( CXX_Multiprec_Particles_Particle_CObjects
              test_particle_unit_cobjects_multiprec_cxx )

    set_property( TEST CXX_Multiprec_Particles_Particle_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_Particles_Particle
                  CXX_Common_Particles_Particle_CObjects
                  CXX_Multiprec_Particles_Particle )

    # ==========================================================================
    # ParticleSet:

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_particle_set_multiprec_cxx:

    add_executable( test_particle_set_multiprec_cxx
                    test_particle_set_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_particle_set_multiprec_cxx )

    add_test( CXX_Multiprec_Particles_ParticleSet
              test_particle_set_multiprec_cxx )

    set_property( TEST CXX_Multiprec_Particles_ParticleSet
                  APPEND PROPERTY DEPENDS
                  CXX_Common_Particles_Particle
                  CXX_Common_Particles_ParticleSet )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_particle_set_particle_unit_multiprec_cxx:

    add_executable( test_particle_set_particle_unit_multiprec_cxx
                    test_particle_set_particle_unit_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_particle_set_particle_unit_multiprec_cxx )

    add_test( CXX_Multiprec_Particles_ParticleSet_To_Particle_Api
              test_particle_set_particle_unit_multiprec_cxx )

    set_property( TEST CXX_Multiprec_Particles_ParticleSet_To_Particle_Api
                  APPEND PROPERTY DEPENDS
                  CXX_Common_Particles_Particle
                  CXX_Common_Particles_ParticleSet
                  CXX_Multiprec_Particles_Particle
                  CXX_Multiprec_Particles_ParticleSet )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_particle_set_cobjects_multiprec_cxx:

    add_executable( test_particle_set_cobjects_multiprec_cxx
                    test_particle_set_cobjects_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_particle_set_cobjects_multiprec_cxx )

    add_test( CXX_Multiprec_Particles_ParticleSet_CObjects
              test_particle_set_cobjects_multiprec_cxx )

    set_property( TEST CXX_Multiprec_Particles_ParticleSet_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_Particles_Particle
                  CXX_Common_Particles_ParticleSet
                  CXX_Multiprec_Particles_ParticleSet )

    # *************************************************************************

    if( UNIT_TEST_TARGETS )
        set_property(
            TARGET ${UNIT_TEST_TARGETS}
            APPEND PROPERTY INCLUDE_DIRECTORIES
            $<BUILD_INTERFACE:${SIXTRACKL_GTEST_INCLUDE_DIRS}>
        )

        set_property( TARGET ${UNIT_TEST_TARGETS} PROPERTY
            POSITION_INDEPENDENT_CODE ON )

        set_property( TARGET ${UNIT_TEST_TARGETS} PROPERTY LINKER_LANGUAGE C )
        set_property( TARGET ${UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD 11 )
        set_property( TARGET ${UNIT_TEST_TARGETS} PROPERTY
            CXX_STANDARD_REQUIRED ON )

        set_property( TARGET ${UNIT_TEST_TARGETS} APPEND PROPERTY
            COMPILE_OPTIONS ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

        set_property( TARGET ${UNIT_TEST_TARGETS} PROPERTY
            LINK_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES} )
    endif()
endif()
