# sixtracklib/tests/sixtracklib/common/particles/CMakeLists.txt

if( GTEST_FOUND )

    set( UNIT_TEST_TARGETS )
    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    # **************************************************************************
    # New C++ Particles Implementation
    # **************************************************************************

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_particle_unit_common_cxx:

    add_executable( test_particle_unit_common_cxx test_particle_unit_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_particle_unit_common_cxx )
    add_test( CXX_Common_Particles_Particle  test_particle_unit_common_cxx )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_particle_unit_cobjects_common_cxx:

    add_executable( test_particle_unit_cobjects_common_cxx
                    test_particle_unit_cobjects_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_particle_unit_cobjects_common_cxx )

    add_test( CXX_Common_Particles_Particle_CObjects
              test_particle_unit_cobjects_common_cxx )

    set_property( TEST CXX_Common_Particles_Particle_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_Particles_Particle
                  CXX_Common_CObjects_CBufferView
                  CXX_Common_CObjects_CBuffer )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_particle_set_common_cxx:

    add_executable( test_particle_set_common_cxx test_particle_set_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_particle_set_common_cxx )
    add_test( CXX_Common_Particles_ParticleSet  test_particle_set_common_cxx )
    set_property( TEST CXX_Common_Particles_ParticleSet
                  APPEND PROPERTY DEPENDS CXX_Common_Particles_Particle )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_particle_set_particle_unit_common_cxx:

    add_executable( test_particle_set_particle_unit_common_cxx
                    test_particle_set_particle_unit_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_particle_set_particle_unit_common_cxx )

    add_test( CXX_Common_Particles_ParticleSet_To_Particle_Api
              test_particle_set_particle_unit_common_cxx )

    set_property( TEST CXX_Common_Particles_ParticleSet_To_Particle_Api
                  APPEND PROPERTY DEPENDS
                  CXX_Common_Particles_Particle
                  CXX_Common_Particles_ParticleSet )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_particle_set_cobjects_common_cxx:

    add_executable( test_particle_set_cobjects_common_cxx
                    test_particle_set_cobjects_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_particle_set_cobjects_common_cxx )

    add_test( CXX_Common_Particles_ParticleSet_CObjects
              test_particle_set_cobjects_common_cxx )

    set_property( TEST CXX_Common_Particles_ParticleSet_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_Particles_ParticleSet
                  CXX_Common_Particles_Particle
                  CXX_Common_CObjects_CBufferView
                  CXX_Common_CObjects_CBuffer )

    # **************************************************************************
    # New C Particles Implementation
    # **************************************************************************


    set_property( TARGET ${UNIT_TEST_TARGETS}
        APPEND PROPERTY INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${SIXTRACKL_GTEST_INCLUDE_DIRS}>
    )

    set_property( TARGET ${UNIT_TEST_TARGETS}
                  PROPERTY LINK_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES} )

    set_property( TARGET ${UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD 11 )
    set_property( TARGET ${UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD_REQUIRED ON )

    set_property( TARGET ${UNIT_TEST_TARGETS}
                  APPEND PROPERTY COMPILE_OPTIONS
                  ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

endif()

