# sixtracklib/tests/sixtracklib/common/beam_elements/CMakeLists.txt

set( SIXTRACKL_NEW_TEST_LIBRARIES sixtrack_cxx_be ${SIXTRACKL_TEST_LIBRARIES} )

if( GTEST_FOUND )

    set( UNIT_TEST_TARGETS )
    set( NEW_UNIT_TEST_TARGETS )

    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    set( SIXTRACKL_NEW_TEST_LIBRARIES ${SIXTRACKL_NEW_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    # **************************************************************************
    # New C++ Beam Elements Implementation
    # **************************************************************************

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # Drift:

    # test_drift_common_cxx:
    add_executable( test_drift_common_cxx test_drift_cxx.cpp )
    set( NEW_UNIT_TEST_TARGETS ${NEW_UNIT_TEST_TARGETS} test_drift_common_cxx )
    add_test( CXX_Common_BeamElements_Drift  test_drift_common_cxx )

    # test_drift_cobjects_common_cxx:
    add_executable( test_drift_cobjects_common_cxx
                    test_drift_cobjects_cxx.cpp )

    set( NEW_UNIT_TEST_TARGETS ${NEW_UNIT_TEST_TARGETS}
         test_drift_cobjects_common_cxx )

    add_test( CXX_Common_BeamElements_Drift_CObjects
              test_drift_cobjects_common_cxx )

    set_property( TEST CXX_Common_BeamElements_Drift_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_BeamElements_Drift
                  CXX_Common_CObjects_CBufferView
                  CXX_Common_CObjects_CBuffer )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # Multipole:

    # test_multipole_common_cxx:
    add_executable( test_multipole_common_cxx test_multipole_cxx.cpp )
    set( NEW_UNIT_TEST_TARGETS ${NEW_UNIT_TEST_TARGETS} test_multipole_common_cxx )
    add_test( CXX_Common_BeamElements_Multipole  test_multipole_common_cxx )

    # test_multipole_cobjects_common_cxx:
    add_executable( test_multipole_cobjects_common_cxx
                    test_multipole_cobjects_cxx.cpp )

    set( NEW_UNIT_TEST_TARGETS ${NEW_UNIT_TEST_TARGETS}
         test_multipole_cobjects_common_cxx )

    add_test( CXX_Common_BeamElements_Multipole_CObjects
              test_multipole_cobjects_common_cxx )

    set_property( TEST CXX_Common_BeamElements_Multipole_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_BeamElements_Multipole
                  CXX_Common_CObjects_CBufferView
                  CXX_Common_CObjects_CBuffer )


    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # Cavity:

    # test_cavity_common_cxx:
    add_executable( test_cavity_common_cxx test_cavity_cxx.cpp )
    set( NEW_UNIT_TEST_TARGETS ${NEW_UNIT_TEST_TARGETS} test_cavity_common_cxx )
    add_test( CXX_Common_BeamElements_Cavity  test_cavity_common_cxx )

    # test_cavity_cobjects_common_cxx:
    add_executable( test_cavity_cobjects_common_cxx
                    test_cavity_cobjects_cxx.cpp )

    set( NEW_UNIT_TEST_TARGETS ${NEW_UNIT_TEST_TARGETS}
         test_cavity_cobjects_common_cxx )

    add_test( CXX_Common_BeamElements_Cavity_CObjects
              test_cavity_cobjects_common_cxx )

    set_property( TEST CXX_Common_BeamElements_Cavity_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_BeamElements_Cavity
                  CXX_Common_CObjects_CBufferView
                  CXX_Common_CObjects_CBuffer )


    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # SRotation:

    # test_srotation_common_cxx:
    add_executable( test_srotation_common_cxx test_srotation_cxx.cpp )
    set( NEW_UNIT_TEST_TARGETS ${NEW_UNIT_TEST_TARGETS}
         test_srotation_common_cxx )
    add_test( CXX_Common_BeamElements_SRotation  test_srotation_common_cxx )

    # test_srotation_cobjects_common_cxx:
    add_executable( test_srotation_cobjects_common_cxx
                    test_srotation_cobjects_cxx.cpp )

    set( NEW_UNIT_TEST_TARGETS ${NEW_UNIT_TEST_TARGETS}
         test_srotation_cobjects_common_cxx )

    add_test( CXX_Common_BeamElements_SRotation_CObjects
              test_srotation_cobjects_common_cxx )

    set_property( TEST CXX_Common_BeamElements_SRotation_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_BeamElements_SRotation
                  CXX_Common_CObjects_CBufferView
                  CXX_Common_CObjects_CBuffer )

    # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    # XYShift:

    # test_xy_shift_common_cxx:
    add_executable( test_xy_shift_common_cxx test_xy_shift_cxx.cpp )
    set( NEW_UNIT_TEST_TARGETS ${NEW_UNIT_TEST_TARGETS}
         test_xy_shift_common_cxx )
    add_test( CXX_Common_BeamElements_XYShift  test_xy_shift_common_cxx )

    # test_xy_shift_cobjects_common_cxx:
    add_executable( test_xy_shift_cobjects_common_cxx
                    test_xy_shift_cobjects_cxx.cpp )

    set( NEW_UNIT_TEST_TARGETS ${NEW_UNIT_TEST_TARGETS}
         test_xy_shift_cobjects_common_cxx )

    add_test( CXX_Common_BeamElements_XYShift_CObjects
              test_xy_shift_cobjects_common_cxx )

    set_property( TEST CXX_Common_BeamElements_XYShift_CObjects
                  APPEND PROPERTY DEPENDS
                  CXX_Common_BeamElements_XYShift
                  CXX_Common_CObjects_CBufferView
                  CXX_Common_CObjects_CBuffer )


    # ==========================================================================
    # test_be_drift_common_c99:

    add_executable( test_be_drift_common_c99      test_be_drift_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}   test_be_drift_common_c99 )
    add_test( C99_CommonBeamElementDriftTests     test_be_drift_common_c99 )

    # --------------------------------------------------------------------------
    # test_be_drift_common_cxx:

    add_executable( test_be_drift_common_cxx    test_be_drift_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_be_drift_common_cxx )
    add_test( CXX_CommonBeamElementDriftTests   test_be_drift_common_cxx )

    # ==========================================================================
    # test_be_multipole_common_c99:

    add_executable( test_be_multipole_common_c99  test_be_multipole_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}   test_be_multipole_common_c99 )
    add_test( C99_CommonBeamElementMultiPoleTests test_be_multipole_common_c99 )

    # ==========================================================================
    # test_be_rf_multipole_common_c99:

    add_executable( test_be_rf_multipole_common_c99
            test_be_rf_multipole_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
            test_be_rf_multipole_common_c99 )

    add_test( C99_Common_BeamElements_RFMultiPoleTests
            test_be_rf_multipole_common_c99 )

    # ==========================================================================
    # test_be_xy_shift_common_c99:

    add_executable( test_be_xy_shift_common_c99   test_be_xy_shift_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}   test_be_xy_shift_common_c99 )
    add_test( C99_CommonBeamElementXYShiftTests   test_be_xy_shift_common_c99 )

    # ==========================================================================
    # test_be_srotation_common_c99:

    add_executable( test_be_srotation_common_c99  test_be_srotation_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}   test_be_srotation_common_c99 )
    add_test( C99_CommonBeamElementSRotationTests test_be_srotation_common_c99 )

    # ==========================================================================
    # test_be_cavity_common_c99:

    add_executable( test_be_cavity_common_c99   test_be_cavity_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_be_cavity_common_c99 )
    add_test( C99_CommonBeamElementCavityTests  test_be_cavity_common_c99 )

    # ==========================================================================
    # test_be_monitor_common_c99:

    add_executable( test_be_monitor_common_c99   test_be_monitor_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}  test_be_monitor_common_c99 )
    add_test( C99_CommonBeamMonitorTests         test_be_monitor_common_c99 )

    # ==========================================================================
    # test_be_limit_rect_common_c99:

    add_executable( test_be_limit_rect_common_c99  test_be_limit_rect_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_be_limit_rect_common_c99 )

    add_test( C99_CommonBeamElementLimitRectTests
              test_be_limit_rect_common_c99 )

    # --------------------------------------------------------------------------
    # test_be_limit_rect_common_cxx:

    add_executable( test_be_limit_rect_common_cxx  test_be_limit_rect_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_be_limit_rect_common_cxx )

    add_test( CXX_CommonBeamElementLimitRectTests
              test_be_limit_rect_common_cxx )

    # ==========================================================================
    # test_be_limit_ellipse_common_c99:

    add_executable( test_be_limit_ellipse_common_c99
                    test_be_limit_ellipse_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_limit_ellipse_common_c99 )

    add_test( C99_CommonBeamElementLimitEllipseTests
              test_be_limit_ellipse_common_c99 )

    # --------------------------------------------------------------------------
    # test_be_limit_ellipse_common_cxx:

    add_executable( test_be_limit_ellipse_common_cxx
                    test_be_limit_ellipse_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_limit_ellipse_common_cxx )

    add_test( CXX_CommonBeamElementLimitEllipseTests
              test_be_limit_ellipse_common_cxx )

    # ==========================================================================
    # test_be_dipedge_common_c99:

    add_executable( test_be_dipedge_common_c99     test_be_dipedge_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}    test_be_dipedge_common_c99 )
    add_test( C99_CommonBeamElementDipoleEdgeTests test_be_dipedge_common_c99 )

    # --------------------------------------------------------------------------
    # test_be_dipedge_common_cxx:

    add_executable( test_be_dipedge_common_cxx     test_be_dipedge_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}    test_be_dipedge_common_cxx )
    add_test( CXX_CommonBeamElementDipoleEdgeTests test_be_dipedge_common_cxx )

    # *************************************************************************
    # Set all properties:

    if( UNIT_TEST_TARGETS )

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

    if( NEW_UNIT_TEST_TARGETS )

        set_property( TARGET ${NEW_UNIT_TEST_TARGETS}
            APPEND PROPERTY INCLUDE_DIRECTORIES
            $<BUILD_INTERFACE:${SIXTRACKL_GTEST_INCLUDE_DIRS}>
        )

        set_property( TARGET ${NEW_UNIT_TEST_TARGETS}
                      PROPERTY LINK_LIBRARIES ${SIXTRACKL_NEW_TEST_LIBRARIES} )

        set_property( TARGET ${NEW_UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD 11 )
        set_property( TARGET ${NEW_UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD_REQUIRED ON )

        set_property( TARGET ${NEW_UNIT_TEST_TARGETS}
                      APPEND PROPERTY COMPILE_OPTIONS
                      ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

    endif()

endif()

