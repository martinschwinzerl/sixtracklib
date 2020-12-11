# ==============================================================================
# tests/sixtracklib/multiprec/beam_elements/CMakeLists.txt

set(   SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
     ${SIXTRACKL_GTEST_LIBRARIES} )

if( GTEST_FOUND )
    set( UNIT_TEST_TARGETS )

    # ==========================================================================
    # drift:

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_be_drift_multiprec_cxx:

    add_executable( test_be_drift_multiprec_cxx test_be_drift_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_be_drift_multiprec_cxx )
    add_test( CXX_Multiprec_BeamElements_Drift test_be_drift_multiprec_cxx )
    set_property( TEST CXX_Multiprec_BeamElements_Drift
                  APPEND PROPERTY DEPENDS CXX_Common_BeamElements_Drift )


    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_be_drift_cobjects_multiprec_cxx:

    add_executable( test_be_drift_cobjects_multiprec_cxx
                    test_be_drift_cobjects_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_drift_cobjects_multiprec_cxx )

    add_test( CXX_Multiprec_BeamElements_Drift_CObjects
              test_be_drift_cobjects_multiprec_cxx )

    set_property( TEST CXX_Multiprec_BeamElements_Drift_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_BeamElements_Drift
                  CXX_Common_BeamElements_Drift_CObjects
                  CXX_Common_CObjects_CBufferView
                  CXX_Common_CObjects_CBuffer
                  CXX_Multiprec_BeamElements_Drift )

    # ==========================================================================
    # multipole:

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_be_multipole_multiprec_cxx:

    add_executable( test_be_multipole_multiprec_cxx
                    test_be_multipole_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_multipole_multiprec_cxx )

    add_test( CXX_Multiprec_BeamElements_Multipole
              test_be_multipole_multiprec_cxx )

    set_property( TEST CXX_Multiprec_BeamElements_Multipole
                  APPEND PROPERTY DEPENDS CXX_Common_BeamElements_Multipole )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_be_multipole_cobjects_multiprec_cxx:

    add_executable( test_be_multipole_cobjects_multiprec_cxx
                    test_be_multipole_cobjects_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_multipole_cobjects_multiprec_cxx )

    add_test( CXX_Multiprec_BeamElements_Multipole_CObjects
              test_be_multipole_cobjects_multiprec_cxx )

    set_property( TEST CXX_Multiprec_BeamElements_Multipole_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_BeamElements_Multipole
                  CXX_Common_BeamElements_Multipole_CObjects
                  CXX_Common_CObjects_CBufferView
                  CXX_Common_CObjects_CBuffer
                  CXX_Multiprec_BeamElements_Multipole )

    # ==========================================================================
    # cavity:

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_be_cavity_multiprec_cxx:

    add_executable( test_be_cavity_multiprec_cxx test_be_cavity_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_cavity_multiprec_cxx )

    add_test( CXX_Multiprec_BeamElements_Cavity
              test_be_cavity_multiprec_cxx )

    set_property( TEST CXX_Multiprec_BeamElements_Cavity
                  APPEND PROPERTY DEPENDS CXX_Common_BeamElements_Cavity )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_be_cavity_cobjects_multiprec_cxx:

    add_executable( test_be_cavity_cobjects_multiprec_cxx
                    test_be_cavity_cobjects_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_cavity_cobjects_multiprec_cxx )

    add_test( CXX_Multiprec_BeamElements_Cavity_CObjects
              test_be_cavity_cobjects_multiprec_cxx )

    set_property( TEST CXX_Multiprec_BeamElements_Cavity_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_BeamElements_Cavity
                  CXX_Common_BeamElements_Cavity_CObjects
                  CXX_Common_CObjects_CBufferView
                  CXX_Common_CObjects_CBuffer
                  CXX_Multiprec_BeamElements_Cavity )

    # ==========================================================================
    # srotation:

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_be_srotation_multiprec_cxx:

    add_executable( test_be_srotation_multiprec_cxx test_be_srotation_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_srotation_multiprec_cxx )

    add_test( CXX_Multiprec_BeamElements_SRotation
              test_be_srotation_multiprec_cxx )

    set_property( TEST CXX_Multiprec_BeamElements_SRotation
                  APPEND PROPERTY DEPENDS CXX_Common_BeamElements_SRotation )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_be_srotation_cobjects_multiprec_cxx:

    add_executable( test_be_srotation_cobjects_multiprec_cxx
                    test_be_srotation_cobjects_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_srotation_cobjects_multiprec_cxx )

    add_test( CXX_Multiprec_BeamElements_SRotation_CObjects
              test_be_srotation_cobjects_multiprec_cxx )

    set_property( TEST CXX_Multiprec_BeamElements_SRotation_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_BeamElements_SRotation
                  CXX_Common_BeamElements_SRotation_CObjects
                  CXX_Common_CObjects_CBufferView
                  CXX_Common_CObjects_CBuffer
                  CXX_Multiprec_BeamElements_SRotation )

    # ==========================================================================
    # xy_shift:

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_be_xy_shift_multiprec_cxx:

    add_executable( test_be_xy_shift_multiprec_cxx test_be_xy_shift_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_xy_shift_multiprec_cxx )

    add_test( CXX_Multiprec_BeamElements_XYShift
              test_be_xy_shift_multiprec_cxx )

    set_property( TEST CXX_Multiprec_BeamElements_XYShift
                  APPEND PROPERTY DEPENDS CXX_Common_BeamElements_XYShift )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # test_be_xy_shift_cobjects_multiprec_cxx:

    add_executable( test_be_xy_shift_cobjects_multiprec_cxx
                    test_be_xy_shift_cobjects_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_xy_shift_cobjects_multiprec_cxx )

    add_test( CXX_Multiprec_BeamElements_XYShift_CObjects
              test_be_xy_shift_cobjects_multiprec_cxx )

    set_property( TEST CXX_Multiprec_BeamElements_XYShift_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_BeamElements_XYShift
                  CXX_Common_BeamElements_XYShift_CObjects
                  CXX_Common_CObjects_CBufferView
                  CXX_Common_CObjects_CBuffer
                  CXX_Multiprec_BeamElements_XYShift )

    # ==========================================================================

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
