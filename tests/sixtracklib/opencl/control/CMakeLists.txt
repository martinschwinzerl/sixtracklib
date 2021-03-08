if( GTEST_FOUND )
    set( UNIT_TEST_TARGETS )
    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    # ==========================================================================
    # test_context_opencl_cxx:

    add_executable( test_node_store_opencl_cxx test_node_store_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_node_store_opencl_cxx )
    add_test( CXX_OpenCL_Control_NodeStore test_node_store_opencl_cxx )

    # ==========================================================================
    # test_context_opencl_cxx:

    add_executable( test_context_opencl_cxx test_context_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_context_opencl_cxx )
    add_test( CXX_OpenCL_Control_Context test_context_opencl_cxx )

    set_tests_properties( CXX_OpenCL_Control_Context PROPERTIES DEPENDS
                          CXX_OpenCL_Control_NodeStore )

    # ==========================================================================
    # test_controller_opencl_cxx:

    add_executable( test_controller_opencl_cxx test_controller_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_controller_opencl_cxx )
    add_test( CXX_OpenCL_Control_Controller test_controller_opencl_cxx )

    set_tests_properties( CXX_OpenCL_Control_Controller PROPERTIES DEPENDS
                          CXX_OpenCL_Control_Context )

    # ==========================================================================
    # test_program_config_opencl_cxx:

    add_executable( test_program_config_opencl_cxx test_program_config_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_program_config_opencl_cxx )
    add_test( CXX_OpenCL_Control_ProgramConfig  test_program_config_opencl_cxx )

    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/opencl_01.toml
                    ${CMAKE_CURRENT_BINARY_DIR}/opencl_01.toml COPYONLY )

    # ==========================================================================
    # test_rtc_program_item_opencl_cxx:

    add_executable( test_rtc_program_item_opencl_cxx
                    test_rtc_program_item_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_rtc_program_item_opencl_cxx )
    add_test( CXX_OpenCL_Control_RunTimeCompileProgramItem
              test_rtc_program_item_opencl_cxx )

    set_tests_properties( CXX_OpenCL_Control_RunTimeCompileProgramItem
                          PROPERTIES DEPENDS CXX_OpenCL_Control_Controller )

    # ==========================================================================
    # test_kernel_item_opencl_cxx:

    add_executable( test_kernel_item_opencl_cxx test_kernel_item_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_kernel_item_opencl_cxx )
    add_test( CXX_OpenCL_Control_KernelItem test_kernel_item_opencl_cxx )

    set_tests_properties( CXX_OpenCL_Control_KernelItem PROPERTIES
                          DEPENDS CXX_OpenCL_Control_RunTimeCompileProgramItem )

    # ==========================================================================
    # test_program_store_opencl_cxx:

    add_executable( test_program_store_opencl_cxx test_program_store_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_program_store_opencl_cxx )
    add_test( CXX_OpenCL_Control_ProgramStore test_program_store_opencl_cxx )
    set_tests_properties( CXX_OpenCL_Control_ProgramStore PROPERTIES
                          DEPENDS CXX_OpenCL_Control_Context
                          DEPENDS CXX_OpenCL_Control_Controller
                          DEPENDS CXX_OpenCL_Control_RunTimeCompileProgramItem )

    # ==========================================================================
    # test_argument_opencl_cxx:

    add_executable( test_argument_opencl_cxx test_argument_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_argument_opencl_cxx )
    add_test( CXX_OpenCL_Control_Argument test_argument_opencl_cxx )
    set_tests_properties( CXX_OpenCL_Control_Argument
                          PROPERTIES DEPENDS CXX_OpenCL_Control_ProgramStore )

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
