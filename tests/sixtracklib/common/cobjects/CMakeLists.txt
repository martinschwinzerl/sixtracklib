# sixtracklib/tests/sixtracklib/common/cobjects/CMakeLists.txt

if( GTEST_FOUND )
    set( UNIT_TEST_TARGETS )
    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    # ==========================================================================
    # test_assign_address_item_common_c99:

#     add_executable( test_assign_address_item_common_c99
#                     test_assign_address_item_c99.cpp )

#     set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
#          test_assign_address_item_common_c99 )

#     add_test( C99_Common_CObjects_AssignAddressItemTests
#               test_assign_address_item_common_c99 )

    # ==========================================================================
    # test_flat_common_cobjects_c99:

    add_executable( test_flat_common_cobjects_c99 test_flat_buffer_c99.cpp    )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_flat_common_cobjects_c99 )
    add_test( C99_Common_CObjects_FlatBuffer test_flat_common_cobjects_c99    )

    # ==========================================================================
    # test_cbuffer_common_cobjects_c99:

    add_executable( test_cbuffer_common_cobjects_c99 test_cbuffer_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_cbuffer_common_cobjects_c99 )
    add_test( C99_Common_CObjects_CBuffer test_cbuffer_common_cobjects_c99 )

    # ==========================================================================
    # test_cbuffer_common_cobjects_cxx:

    add_executable( test_cbuffer_common_cobjects_cxx test_cbuffer_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_cbuffer_common_cobjects_cxx )
    add_test( CXX_Common_CObjects_CBuffer test_cbuffer_common_cobjects_cxx )

    # --------------------------------------------------------------------------
    # test_buffer_common_cxx:

#     add_executable( test_buffer_common_cxx test_buffer_cxx.cpp )
#     set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_buffer_common_cxx )
#     add_test( CXX_Common_Buffer_BufferTests test_buffer_common_cxx )

    # ==========================================================================
    # test_buffer_string_object_common_c99:

#     add_executable( test_buffer_string_object_common_c99
#                     test_buffer_string_object_c99.cpp )

#     set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
#          test_buffer_string_object_common_c99 )

#     add_test( C99_Common_CObjects_BufferStringObjectTests
#               test_buffer_string_object_common_c99 )

    # -------------------------------------------------------------------------
    # test_buffer_string_object_common_cxx:

#     add_executable( test_buffer_string_object_common_cxx
#                     test_buffer_string_object_cxx.cpp )

#     set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
#          test_buffer_string_object_common_cxx )

#     add_test( CXX_Common_Buffer_BufferStringObjectTests
#               test_buffer_string_object_common_cxx )

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

#end : sixtracklib/tests/sixtracklib/common/control/CMakeLists.txt
