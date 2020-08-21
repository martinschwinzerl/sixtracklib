# processing examples/cxx/cuda/CMakeLists.txt

set( EXAMPLE_TARGETS )

# -----------------------------------------------------------------------------

add_executable( particle_set_addr_cuda_cxx particle_set_addr_cxx.cpp )
list( APPEND EXAMPLE_TARGETS particle_set_addr_cuda_cxx )
target_link_libraries( particle_set_addr_cuda_cxx
    PUBLIC ${EXAMPLE_LINK_LIBRARIES} )

# ------------------------------------------------------------------------------

if( EXAMPLE_TARGETS )
    set_property( TARGET ${EXAMPLE_TARGETS} PROPERTY LINKER_LANGUAGE CXX )
    set_property( TARGET ${EXAMPLE_TARGETS} PROPERTY CXX_STANDARD 11 )
    set_property( TARGET ${EXAMPLE_TARGETS} PROPERTY CXX_STANDARD_REQUIRED ON )
    set_property( TARGET ${EXAMPLE_TARGETS} PROPERTY COMPILE_OPTIONS
        ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
        ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )
endif()
