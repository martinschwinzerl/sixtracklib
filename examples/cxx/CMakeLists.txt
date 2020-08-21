# examples/cxx/CMakeLists.txt

message( STATUS "---- processing examples/cxx/CMakeLists.txt" )
set( EXAMPLE_LINK_LIBRARIES sixtrack )

add_subdirectory( cuda )

set( EXAMPLE_TARGETS )
set( EXAMPLE_CUDA_TARGETS )
set( EXAMPLE_OPENCL_TARGETS )

set( EXAMPLE_SOURCES_TO_INSTALL )

# set( EXAMPLE_LINK_LIBRARIES sixtrack_test sixtrack m dl )


add_executable( default_backends_cxx default_backends.cpp )
list( APPEND EXAMPLE_TARGETS default_backends_cxx )

# -----------------------------------------------------------------------------
# simple_drift_buffer_cxx:

# add_executable( simple_drift_buffer_cxx simple_drift_buffer.cpp )
# list( APPEND EXAMPLE_TARGETS simple_drift_buffer_cxx )

# -----------------------------------------------------------------------------
# track_job_cpu_cxx:

# add_executable( track_job_cpu_cxx track_job_cpu.cpp )
# list( APPEND EXAMPLE_TARGETS track_job_cpu_cxx )

# -----------------------------------------------------------------------------
# track_lhc_no_bb_cxx:

# add_executable( track_lhc_no_bb_cxx track_lhc_no_bb.cpp )
# list( APPEND EXAMPLE_TARGETS track_lhc_no_bb_cxx )

# if( SIXTRACKL_ENABLE_OPENCL )
    # -------------------------------------------------------------------------
    # track_job_cpu_cxx:

#     add_executable( track_job_cl_cxx track_job_cl.cpp )
#     list( APPEND EXAMPLE_TARGETS track_job_cl_cxx )

    # -------------------------------------------------------------------------
    # run_opencl_kernel_cxx:
#     add_executable( run_opencl_kernel_cxx run_opencl_kernel.cpp )
#     list( APPEND EXAMPLE_OPENCL_TARGETS run_opencl_kernel_cxx )

    # -------------------------------------------------------------------------
    # track_lhc_no_bb_opencl_cxx:
#     add_executable( track_lhc_no_bb_opencl_cxx track_lhc_no_bb_opencl.cpp )
#     list( APPEND EXAMPLE_OPENCL_TARGETS track_lhc_no_bb_opencl_cxx )


# endif()

# if( SIXTRACKL_ENABLE_CUDA )
#     add_executable( track_job_cuda_cxx track_job_cuda.cpp )
#     list( APPEND EXAMPLE_CUDA_TARGETS track_job_cuda_cxx )
# endif()

# ==============================================================================
# Common settings for all programs:

set( ALL_EXAMPLE_TARGETS ${EXAMPLE_TARGETS}  )
#      ${EXAMPLE_OPENCL_TARGETS} ${EXAMPLE_CUDA_TARGETS} )

if( ALL_EXAMPLE_TARGETS )
    set(  EXAMPLE_COMPILE_OPTIONS ${SIXTRACKLIB_CPU_FLAGS} )
    list( APPEND EXAMPLE_COMPILE_OPTIONS -Wall )
    list( APPEND EXAMPLE_COMPILE_OPTIONS -Werror )
    list( APPEND EXAMPLE_COMPILE_OPTIONS -pedantic )

    set_property( TARGET ${ALL_EXAMPLE_TARGETS} PROPERTY LINKER_LANGUAGE CXX )
    set_property( TARGET ${ALL_EXAMPLE_TARGETS} PROPERTY CXX_STANDARD 11 )
    set_property( TARGET ${ALL_EXAMPLE_TARGETS} PROPERTY CXX_STANDARD_REQUIRED ON )
    set_property( TARGET ${ALL_EXAMPLE_TARGETS}
                  APPEND PROPERTY COMPILE_OPTIONS ${EXAMPLE_COMPILE_OPTIONS} )

    set_property( TARGET ${ALL_EXAMPLE_TARGETS}
                  PROPERTY LINK_LIBRARIES ${EXAMPLE_LINK_LIBRARIES} )
endif()

# ==============================================================================
# Install :

# end: examples/cxx/CMakeLists.txt
