if( GTEST_FOUND )
    set( UNIT_TEST_TARGETS )
    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    # ==========================================================================
    # test_context_opencl_cxx:

    add_executable( test_context_opencl_cxx test_context_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_context_opencl_cxx )
    add_test( CXX_OpenCL_Control_Context test_context_opencl_cxx )

    # ==========================================================================
    # test_controller_opencl_cxx:

    add_executable( test_controller_opencl_cxx test_controller_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_controller_opencl_cxx )
    add_test( CXX_OpenCL_Control_Controller test_controller_opencl_cxx )

    # ==========================================================================
    # test_rtc_program_item_opencl_cxx:

    add_executable( test_rtc_program_item_opencl_cxx
                    test_rtc_program_item_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_rtc_program_item_opencl_cxx )
    add_test( CXX_OpenCL_Control_RunTimeCompileProgramItem
              test_rtc_program_item_opencl_cxx )

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
        set_property( TARGET ${UNIT_TEST_TARGETS}
                      PROPERTY CXX_STANDARD_REQUIRED ON )

        set_property( TARGET ${UNIT_TEST_TARGETS}
                      APPEND PROPERTY COMPILE_OPTIONS
                      ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )
    endif()
endif()
