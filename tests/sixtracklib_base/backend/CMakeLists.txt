if( GTEST_FOUND )
    set( UNIT_TEST_TARGETS )
    set( SIXTRACKLIB_BASE_TEST_LIBRARIES ${SIXTRACKLIB_BASE_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    add_executable( test_dlib_loader_posix_cxx test_dlib_loader_posix_cxx.cpp )
    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} test_dlib_loader_posix_cxx )
    add_test( CXX_Base_Backend_PosixDynLibLoader test_dlib_loader_posix_cxx )

    if( UNIT_TEST_TARGETS )
        # *********************************************************************
        # Set all properties:

        set_property( TARGET ${UNIT_TEST_TARGETS} APPEND PROPERTY
            INCLUDE_DIRECTORIES $<BUILD_INTERFACE:${SIXTRACKL_GTEST_INCLUDE_DIRS}> )

        set_property( TARGET ${UNIT_TEST_TARGETS}
                    PROPERTY LINK_LIBRARIES ${SIXTRACKLIB_BASE_TEST_LIBRARIES} )

        set_property( TARGET ${UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD 11 )
        set_property( TARGET ${UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD_REQUIRED ON )

        set_property( TARGET ${UNIT_TEST_TARGETS} APPEND PROPERTY COMPILE_OPTIONS
            ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
            ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )
    endif()
endif()
