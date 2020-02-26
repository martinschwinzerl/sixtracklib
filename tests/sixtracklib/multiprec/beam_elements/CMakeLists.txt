# ==============================================================================
# tests/sixtracklib/multiprec/beam_elements/CMakeLists.txt

set(   SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
     ${SIXTRACKL_GTEST_LIBRARIES} )

if( GTEST_FOUND )
    set( UNIT_TEST_TARGETS )

    # ==========================================================================
    # test_be_drift_multiprec_cxx:

    add_executable( test_be_drift_multiprec_cxx test_be_drift_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_be_drift_multiprec_cxx )
    add_test( CXX_Multiprec_BeamElements_Drift_Tests test_be_drift_multiprec_cxx )


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
