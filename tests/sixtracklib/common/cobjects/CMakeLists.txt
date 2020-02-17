# sixtracklib/tests/sixtracklib/common/cobjects/CMakeLists.txt

if( GTEST_FOUND )
    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    set( UNIT_TEST_TARGETS )

    # ==========================================================================
    # test_cbuffer_view_add_objects_cxx:

    add_executable( test_cbuffer_view_add_objects_cxx
                    test_cbuffer_view_add_objects.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_cbuffer_view_add_objects_cxx )

    add_test( CXX_Common_CObjects_CBufferView_AddObjectsTests
              test_cbuffer_view_add_objects_cxx )

    # ==========================================================================
    # test_cbuffer_view_load_objects_cxx:

    add_executable( test_cbuffer_view_load_objects_cxx
                    test_cbuffer_view_load_objects.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_cbuffer_view_load_objects_cxx )

    add_test( CXX_Common_CObjects_CBufferView_LoadObjectsTests
              test_cbuffer_view_load_objects_cxx )

    set_tests_properties( CXX_Common_CObjects_CBufferView_LoadObjectsTests
        PROPERTIES DEPENDS CXX_Common_CObjects_CBufferView_AddObjectsTests )


    # ==========================================================================
    # test_cbuffer_view_load_objects_cxx:

    add_executable( test_cbuffer_view_store_objects_cxx
                    test_cbuffer_view_store_objects.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_cbuffer_view_store_objects_cxx )

    add_test( CXX_Common_CObjects_CBufferView_StoreObjectsTests
              test_cbuffer_view_store_objects_cxx )

    set_tests_properties( CXX_Common_CObjects_CBufferView_StoreObjectsTests
        PROPERTIES DEPENDS CXX_Common_CObjects_CBufferView_AddObjectsTests )

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
