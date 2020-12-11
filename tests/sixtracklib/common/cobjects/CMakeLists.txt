# sixtracklib/tests/sixtracklib/common/cobjects/CMakeLists.txt

if( GTEST_FOUND )
    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    set( UNIT_TEST_TARGETS )

    # ==========================================================================
    # test_cbuffer_view_common_cxx:

    add_executable( test_cbuffer_view_common_cxx test_cbuffer_view_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_cbuffer_view_common_cxx )
    add_test( CXX_Common_CObjects_CBufferView test_cbuffer_view_common_cxx )

    # ==========================================================================
    # test_cbuffer_cobjects_cxx:

    add_executable( test_cbuffer_cobjects_cxx test_cbuffer_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_cbuffer_cobjects_cxx )
    add_test( CXX_Common_CObjects_CBuffer test_cbuffer_cobjects_cxx )

    # ==========================================================================
    # test_cbuffer_objs_common_cxx:

    add_executable( test_cbuffer_objs_common_cxx test_cbuffer_objs_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_cbuffer_objs_common_cxx )
    add_test( CXX_Common_CObjects_CBuffer_Objs test_cbuffer_objs_common_cxx )

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

#end : sixtracklib/tests/sixtracklib/common/cobjects/CMakeLists.txt
