if( GTEST_FOUND )
    set( UNIT_TEST_TARGETS )
    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    # ==========================================================================
    # test_track_compare_sixtrack_common_c99:

    add_executable( test_track_compare_sixtrack_common_c99
        test_track_compare_sixtrack_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
        test_track_compare_sixtrack_common_c99 )

    add_test( C99_Common_Track_Compare_SixTrack
        test_track_compare_sixtrack_common_c99 )

    # ==========================================================================
    # test_track_compare_sixtrack_view_common_c99:

    add_executable( test_track_compare_sixtrack_view_common_c99
        test_track_compare_sixtrack_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
        test_track_compare_sixtrack_view_common_c99 )

    target_compile_definitions( test_track_compare_sixtrack_view_common_c99
        PRIVATE -DSIXTRL_USE_SINGLE_PARTICLE_ADAPTER=1 )

    add_test( C99_Common_Track_Compare_SixTrack_View
        test_track_compare_sixtrack_view_common_c99 )

    # ==========================================================================
    # test_track_compare_pysixtrack_common_c99:

    add_executable( test_track_compare_pysixtrack_common_c99
        test_track_compare_pysixtrack_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
        test_track_compare_pysixtrack_common_c99 )

    target_compile_definitions( test_track_compare_pysixtrack_common_c99
        PRIVATE -DSIXTRL_TRACK_SPACECHARGE=2 )

    add_test( C99_Common_Track_Compare_PySixTrack
        test_track_compare_pysixtrack_common_c99 )

    # ==========================================================================
    # test_track_compare_pysixtrack_common_c99:

    add_executable( test_track_compare_pysixtrack_view_common_c99
        test_track_compare_pysixtrack_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
        test_track_compare_pysixtrack_view_common_c99 )

    target_compile_definitions( test_track_compare_pysixtrack_view_common_c99
        PRIVATE -DSIXTRL_USE_SINGLE_PARTICLE_ADAPTER=1 )

    target_compile_definitions( test_track_compare_pysixtrack_view_common_c99
        PRIVATE -DSIXTRL_TRACK_SPACECHARGE=2 )

    add_test( C99_Common_Track_Compare_PySixTrack_View
        test_track_compare_pysixtrack_view_common_c99 )

    # ==========================================================================
    # test_track_until_turn_cmp_pysixtrack_common_c99:

    add_executable( test_track_until_turn_cmp_pysixtrack_common_c99
        test_track_cmp_track_until_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
        test_track_until_turn_cmp_pysixtrack_common_c99 )

    target_compile_definitions( test_track_until_turn_cmp_pysixtrack_common_c99
        PRIVATE -DSIXTRL_TRACK_SPACECHARGE=2 )

    add_test( C99_Common_Track_Compare_UntilTurn_PySixTrack
        test_track_until_turn_cmp_pysixtrack_common_c99 )

    # ==========================================================================
    # test_track_until_turn_cmp_pysixtrack_view_common_c99:

    add_executable( test_track_until_turn_cmp_pysixtrack_view_common_c99
        test_track_cmp_track_until_c99.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
        test_track_until_turn_cmp_pysixtrack_view_common_c99 )

    target_compile_definitions(
        test_track_until_turn_cmp_pysixtrack_view_common_c99
        PRIVATE -DSIXTRL_USE_SINGLE_PARTICLE_ADAPTER=1 )

    target_compile_definitions(
        test_track_until_turn_cmp_pysixtrack_view_common_c99
        PRIVATE -DSIXTRL_TRACK_SPACECHARGE=2 )

    add_test( C99_Common_Track_Compare_UntilTurn_PySixTrack_View
        test_track_until_turn_cmp_pysixtrack_view_common_c99 )

endif()

if( UNIT_TEST_TARGETS )
        set_property( TARGET ${UNIT_TEST_TARGETS} APPEND PROPERTY
            INCLUDE_DIRECTORIES $<BUILD_INTERFACE:${SIXTRACKL_GTEST_INCLUDE_DIRS}> )

        set_property( TARGET ${UNIT_TEST_TARGETS}
                      PROPERTY POSITION_INDEPENDENT_CODE ON )

        set_property( TARGET ${UNIT_TEST_TARGETS}
                      PROPERTY LINKER_LANGUAGE C )

        set_property( TARGET ${UNIT_TEST_TARGETS}
                      PROPERTY LINK_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES} )

        set_property( TARGET ${UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD 11 )
        set_property( TARGET ${UNIT_TEST_TARGETS}
                      PROPERTY CXX_STANDARD_REQUIRED ON )

        set_property( TARGET ${UNIT_TEST_TARGETS}
                      APPEND PROPERTY COMPILE_OPTIONS
                      ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )
endif()
