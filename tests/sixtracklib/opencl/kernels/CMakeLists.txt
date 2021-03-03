if( GTEST_FOUND )
    set( UNIT_TEST_TARGETS )
    set( SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} )

    # ==========================================================================
    # test_kernel_cobj_flat_buffer_remap_opencl_cxx:

    add_executable( test_kernel_cobj_flat_buffer_remap_opencl_cxx
        test_kernel_cobj_flat_buffer_remap_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
        test_kernel_cobj_flat_buffer_remap_opencl_cxx )

    add_test( CXX_OpenCL_Kernels_CObjFlatBufferRemap
        test_kernel_cobj_flat_buffer_remap_opencl_cxx )

    set_tests_properties( CXX_OpenCL_Kernels_CObjFlatBufferRemap
        PROPERTIES DEPENDS CXX_OpenCL_Control_RunTimeCompileProgramItem )

    # ==========================================================================
    # test_kernel_track_particle_until_turn_cobj_flat_buffer_opencl_cxx:

    add_executable(
        test_kernel_track_particle_until_turn_cobj_flat_buffer_opencl_cxx
        test_kernel_particle_track_until_cobj_flat_buffer_cxx.cpp )

    set( UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS}
        test_kernel_track_particle_until_turn_cobj_flat_buffer_opencl_cxx )

    add_test( CXX_OpenCL_Kernels_ParticleTrackUntilCobjFlatBuffer
        test_kernel_track_particle_until_turn_cobj_flat_buffer_opencl_cxx )

    set_tests_properties( CXX_OpenCL_Kernels_ParticleTrackUntilCobjFlatBuffer
        PROPERTIES DEPENDS CXX_OpenCL_Control_RunTimeCompileProgramItem )

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
