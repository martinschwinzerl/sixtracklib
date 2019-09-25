# sixtracklib/tests/sixtracklib/common/buffer/CMakeLists.txt

# -----------------------------------------------------------------------------
# ---- Generate testdata:

if( GTEST_FOUND )
    set( UNIT_TEST_TARGETS )
    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    # --------------------------------------------------------------------------
    # test_mem_pool_common_c99:

    add_executable( test_mem_pool_common_c99      test_mem_pool_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}   test_mem_pool_common_c99 )
    add_test( C99_Common_MemPoolTests              test_mem_pool_common_c99 )

    # --------------------------------------------------------------------------
    # test_managed_buffer_common_c99:

    add_executable( test_managed_buffer_common_c99 test_managed_buffer_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_managed_buffer_common_c99 )
    add_test( C99_Common_ManagedBufferTest test_managed_buffer_common_c99 )

    # --------------------------------------------------------------------------
    # test_buffer_common_c99:

    add_executable( test_buffer_common_c99 test_buffer_c99.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_buffer_common_c99 )
    add_test( C99_Common_BufferTest test_buffer_common_c99 )

    # --------------------------------------------------------------------------
    # test_buffer_common_cxx:

    add_executable( test_buffer_common_cxx test_buffer_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_buffer_common_cxx )
    add_test( CXX_Common_BufferTest test_buffer_common_cxx )

    # ==========================================================================
    # test_buffer_string_object_common_c99:

    add_executable( test_buffer_string_object_common_c99
                    test_buffer_string_object_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_buffer_string_object_common_c99 )

    add_test( C99_Common_BufferStringObjectTests
              test_buffer_string_object_common_c99 )

    # -------------------------------------------------------------------------
    # test_buffer_string_object_common_cxx:

    add_executable( test_buffer_string_object_common_cxx
                    test_buffer_string_object_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
         test_buffer_string_object_common_cxx )

    add_test( CXX_Common_BufferStringObjectTests
              test_buffer_string_object_common_cxx )


    # ==========================================================================
    # test_buffer_toc_common_c99:

#     add_executable( test_buffer_toc_common_c99 test_buffer_toc_c99.cpp )
#     set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_buffer_toc_common_c99 )
#     add_test( C99_Common_BufferToCTests test_buffer_toc_common_c99 )

    # -------------------------------------------------------------------------
    # test_buffer_toc_common_cxx:

#     add_executable( test_buffer_toc_common_cxx test_buffer_toc_cxx.cpp )
#     set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_buffer_toc_common_cxx )
#     add_test( CXX_Common_BufferToCTests test_buffer_toc_common_cxx )

    # *************************************************************************
    # Set all properties:

    set_property(
        TARGET ${UNIT_TEST_TARGETS}
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

