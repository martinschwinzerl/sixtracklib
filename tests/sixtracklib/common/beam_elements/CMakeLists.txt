if( GTEST_FOUND )

    set( UNIT_TEST_TARGETS )
    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    # ==========================================================================
    # test_be_beamfields_sc_coasting_common_c99:

    add_executable( test_be_beamfields_sc_coasting_common_c99
        test_sc_coasting_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
        test_be_beamfields_sc_coasting_common_c99 )

    add_test( C99_Common_BeamElements_BeamFields_SCCoasting
              test_be_beamfields_sc_coasting_common_c99 )

    # ==========================================================================
    # test_be_beamfields_sc_qgauss_common_c99:

    add_executable( test_be_beamfields_sc_qgauss_common_c99
        test_sc_qgauss_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
        test_be_beamfields_sc_qgauss_common_c99 )

    add_test( C99_Common_BeamElements_BeamFields_SCQGaussProfile
              test_be_beamfields_sc_qgauss_common_c99 )

    # ==========================================================================
    # test_be_cavity_common_c99:

    add_executable( test_be_cavity_common_c99    test_cavity_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}  test_be_cavity_common_c99 )
    add_test( C99_Common_BeamElements_Cavity     test_be_cavity_common_c99 )

    # ==========================================================================
    # test_be_dipedge_common_c99:

    add_executable( test_be_dipedge_common_c99   test_dipedge_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}  test_be_dipedge_common_c99 )
    add_test( C99_Common_BeamElements_DipoleEdge test_be_dipedge_common_c99 )

    # ==========================================================================
    # test_be_drift_common_c99:

    add_executable( test_be_drift_common_c99     test_drift_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}  test_be_drift_common_c99 )
    add_test( C99_Common_BeamElements_Drift      test_be_drift_common_c99 )

    # ==========================================================================
    # test_be_drift_exact_common_c99:

    add_executable( test_be_drift_exact_common_c99 test_drift_exact_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}  test_be_drift_exact_common_c99 )
    add_test( C99_Common_BeamElements_DriftExact test_be_drift_exact_common_c99 )

    # ==========================================================================
    # test_be_end_tracking_common_c99:

    add_executable( test_be_end_tracking_common_c99
                    test_end_tracking_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_end_tracking_common_c99 )

    add_test( C99_Common_BeamElements_EndTracking
              test_be_end_tracking_common_c99 )

    # ==========================================================================
    # test_be_limit_rect_common_c99:

    add_executable( test_be_limit_rect_common_c99 test_limit_rect_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}   test_be_limit_rect_common_c99 )
    add_test( C99_Common_BeamElements_LimitRect   test_be_limit_rect_common_c99 )

    # ==========================================================================
    # test_be_limit_ellipse_common_c99:

    add_executable( test_be_limit_ellipse_common_c99
                    test_limit_ellipse_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_limit_ellipse_common_c99 )

    add_test( C99_Common_BeamElements_LimitEllipse
              test_be_limit_ellipse_common_c99 )

    # ==========================================================================
    # test_be_limit_rect_ellipse_common_c99:

    add_executable( test_be_limit_rect_ellipse_common_c99
                    test_limit_rect_ellipse_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_be_limit_rect_ellipse_common_c99 )

    add_test( C99_Common_BeamElements_LimitRectEllipse
              test_be_limit_rect_ellipse_common_c99 )

    # ==========================================================================
    # test_be_monitor_common_c99:

    add_executable( test_be_monitor_common_c99    test_monitor_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}   test_be_monitor_common_c99 )
    add_test( C99_Common_BeamElements_BeamMonitor test_be_monitor_common_c99 )

    # ==========================================================================
    # test_be_multipole_common_c99:

    add_executable( test_be_multipole_common_c99  test_multipole_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}   test_be_multipole_common_c99 )
    add_test( C99_Common_BeamElements_MultiPole   test_be_multipole_common_c99 )

    # ==========================================================================
    # test_be_rf_multipole_common_c99:

#     add_executable( test_be_rf_multipole_common_c99 test_be_rf_multipole_c99.cpp )
#     set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_be_rf_multipole_common_c99 )
#     add_test( C99_Common_BeamElements_RFMultiPole test_be_rf_multipole_common_c99 )

    # ==========================================================================
    # test_be_srotation_common_c99:

    add_executable( test_be_srotation_common_c99  test_srotation_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}   test_be_srotation_common_c99 )
    add_test( C99_Common_BeamElements_SRotation   test_be_srotation_common_c99 )

    # ==========================================================================
    # test_be_xy_shift_common_c99:

    add_executable( test_be_xy_shift_common_c99   test_xy_shift_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}   test_be_xy_shift_common_c99 )
    add_test( C99_Common_BeamElements_XYShift     test_be_xy_shift_common_c99 )

    if( SIXTRACKL_ENABLE_DEMOTRACK )
        # ==========================================================================
        # test_be_demotrack_common_c99:

        add_executable( test_be_demotrack_common_c99 test_demotrack_c99.cpp )
        set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_be_demotrack_common_c99 )
        add_test( C99_Common_BeamElements_Demotrack test_be_demotrack_common_c99 )

        # ==========================================================================
        # test_be_demotrack_common_cxx:

        add_executable( test_be_demotrack_common_cxx test_demotrack_cxx.cpp )
        set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_be_demotrack_common_cxx )
        add_test( CXX_Common_BeamElements_Demotrack test_be_demotrack_common_cxx )

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

