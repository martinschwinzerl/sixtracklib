# sixtracklib/tests/sixtracklib/common/control/CMakeLists.txt

if( GTEST_FOUND )
    set( SIXTRACKL_COMMON_TESTS_DEPEND_ON_TRACKING_TESTDATA )

    set( UNIT_TEST_TARGETS )
    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    # ==========================================================================
    # test_debug_register_common_c99:

    add_executable( test_debug_register_common_c99
                    test_debug_register_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_debug_register_common_c99 )

    add_test( C99_CommonControlDebuggingRegisterTests
              test_debug_register_common_c99 )

    # ==========================================================================
    # test_node_id_common_c99:

    add_executable( test_node_id_common_c99 test_node_id_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_node_id_common_c99 )
    add_test( C99_CommonControlNodeIdTests test_node_id_common_c99 )

    # --------------------------------------------------------------------------
    # test_node_id_common_cxx:

    add_executable( test_node_id_common_cxx test_node_id_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_node_id_common_cxx )
    add_test( CXX_CommonControlNodeIdTests test_node_id_common_cxx )

    # ==========================================================================
    # test_arch_info_common_c99:

    add_executable( test_arch_info_common_c99 test_arch_info_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_arch_info_common_c99 )
    add_test( C99_CommonControlArchInfoTests test_arch_info_common_c99 )

    # --------------------------------------------------------------------------
    # test_arch_info_common_cxx:

    add_executable( test_arch_info_common_cxx test_arch_info_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_arch_info_common_cxx )
    add_test( CXX_CommonControlArchInfoTests test_arch_info_common_cxx )

    # ==========================================================================
    # test_kernel_config_key_common_c99:

    add_executable( test_kernel_config_key_common_c99
                    test_kernel_config_key_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_kernel_config_key_common_c99 )

    add_test( C99_CommonControlKernelConfigKeyTests
              test_kernel_config_key_common_c99 )

    # --------------------------------------------------------------------------
    # test_kernel_config_key_common_cxx:

    add_executable( test_kernel_config_key_common_cxx
                    test_kernel_config_key_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_kernel_config_key_common_cxx )

    add_test( CXX_CommonControlKernelConfigKeyTests
              test_kernel_config_key_common_cxx )

    # ==========================================================================
    # test_kernel_config_base_common_c99:

    add_executable( test_kernel_config_base_common_c99
                    test_kernel_config_base_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_kernel_config_base_common_c99 )

    add_test( C99_CommonControlKernelConfigBaseTests
              test_kernel_config_base_common_c99 )

    # --------------------------------------------------------------------------
    # test_kernel_config_base_common_cxx:

    add_executable( test_kernel_config_base_common_cxx
                    test_kernel_config_base_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_kernel_config_base_common_cxx )

    add_test( CXX_CommonControlKernelConfigBaseTests
              test_kernel_config_base_common_cxx )

    # ==========================================================================
    # test_kernel_config_store_common_c99:

    add_executable( test_kernel_config_store_common_c99
                    test_kernel_config_store_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_kernel_config_store_common_c99 )

    add_test( C99_CommonControlKernelConfigStoreTests
              test_kernel_config_store_common_c99 )

    set_property( TEST C99_CommonControlKernelConfigStoreTests
        APPEND PROPERTY DEPENDS C99_CommonControlKernelConfigBaseTests
                                C99_CommonControlKernelConfigKeyTests )


    # --------------------------------------------------------------------------
    # test_kernel_config_store_common_cxx:

    add_executable( test_kernel_config_store_common_cxx
                    test_kernel_config_store_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_kernel_config_store_common_cxx )

    add_test( CXX_CommonControlKernelStoreCommonTests
              test_kernel_config_store_common_cxx )

    set_property( TEST CXX_CommonControlKernelStoreCommonTests
        APPEND PROPERTY DEPENDS CXX_CommonControlKernelConfigBaseTests
                                CXX_CommonControlKernelConfigKeyTests )

    # ==========================================================================
    # test_kernel_set_base_common_c99:

    add_executable( test_kernel_set_base_common_c99
                    test_kernel_set_base_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_kernel_set_base_common_c99 )

    add_test( C99_CommonControlKernelSetBaseTests
              test_kernel_set_base_common_c99 )

    set_property( TEST C99_CommonControlKernelSetBaseTests
        APPEND PROPERTY DEPENDS C99_CommonControlKernelConfigStoreTests
                                C99_CommonControlKernelConfigBaseTests
                                C99_CommonControlKernelConfigKeyTests )

    # --------------------------------------------------------------------------
    # test_kernel_set_base_common_cxx:

    add_executable( test_kernel_set_base_common_cxx
                    test_kernel_set_base_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_kernel_set_base_common_cxx )

    add_test( CXX_CommonControlKernelSetBaseTests
              test_kernel_set_base_common_cxx )

    set_property( TEST CXX_CommonControlKernelSetBaseTests
        APPEND PROPERTY DEPENDS CXX_CommonControlKernelStoreCommonTests
                                CXX_CommonControlKernelConfigBaseTests
                                CXX_CommonControlKernelConfigKeyTests )

    # ==========================================================================
    # test_node_info_common_c99:

    add_executable( test_node_info_base_common_c99
                    test_node_info_base_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_node_info_base_common_c99 )
    add_test( C99_CommonControlNodeInfoBaseTests
              test_node_info_base_common_c99 )

    set_property( TEST C99_CommonControlNodeInfoBaseTests
        APPEND PROPERTY DEPENDS C99_CommonControlNodeIdTests )

    # --------------------------------------------------------------------------
    # test_node_id_common_cxx:

    add_executable( test_node_info_base_common_cxx
                    test_node_info_base_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_node_info_base_common_cxx )
    add_test( CXX_CommonControlNodeInfoBaseTests
              test_node_info_base_common_cxx )

    set_property( TEST CXX_CommonControlNodeInfoBaseTests
        APPEND PROPERTY DEPENDS CXX_CommonControlNodeIdTests )

    # ==========================================================================
    # test_node_controller_base_common_c99:

#     add_executable( test_node_controller_base_common_c99
#         test_node_controller_base_c99.cpp )

#     set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
#         test_node_controller_base_common_c99 )

#     add_test( C99_CommonNodeControllerBaseTests
#         test_node_controller_base_common_c99 )

    # --------------------------------------------------------------------------
    # test_node_controller_base_common_cxx:

#     add_executable( test_node_controller_base_common_cxx
#         test_node_controller_base_cxx.cpp )

#     set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
#         test_node_controller_base_common_cxx )

#     add_test( CXX_CommonNodeControllerBaseTests
#         test_node_controller_base_common_cxx )

    # *************************************************************************
    # Set all properties:

    if( UNIT_TEST_TARGETS )
        set_property(
            TARGET ${UNIT_TEST_TARGETS}
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

#end : sixtracklib/tests/sixtracklib/common/control/CMakeLists.txt
