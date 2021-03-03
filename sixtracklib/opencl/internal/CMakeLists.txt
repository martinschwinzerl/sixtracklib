set( SIXTRL_OPENCL_INTERNAL_C99_HEADERS helpers.h )
set( SIXTRL_OPENCL_INTERNAL_C99_SOURCES )

set( SIXTRL_OPENCL_INTERNAL_CXX_HEADERS )
set( SIXTRL_OPENCL_INTERNAL_CXX_SOURCES helpers.cpp )

set( SIXTRL_OCL_PARENT_C99_HEADERS ../definitions.h ../opencl.h )
set( SIXTRL_OCL_PARENT_CXX_HEADERS ../opencl.hpp )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( sixtrack_opencl_internal_cxx OBJECT
    ${SIXTRL_OPENCL_INTERNAL_CXX_HEADERS} ${SIXTRL_OCL_PARENT_C99_HEADERS}
    ${SIXTRL_OPENCL_INTERNAL_C99_HEADERS} ${SIXTRL_OCL_PARENT_CXX_HEADERS}
    ${SIXTRL_OPENCL_INTERNAL_CXX_SOURCES} )

target_link_libraries( sixtrack_opencl_internal_cxx
    PRIVATE ${SIXTRL_OPENCL_LIBRARIES} )

target_include_directories( sixtrack_opencl_internal_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_opencl_internal_cxx PROPERTIES CXX_STANDARD 11
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_opencl_internal_cxx
    PRIVATE ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

set( SIXTRL_OPENCL_MODULES ${SIXTRL_OPENCL_MODULES}
     $<TARGET_OBJECTS:sixtrack_opencl_internal_cxx> PARENT_SCOPE )

# -----------------------------------------------------------------------------
# Install:

if( SIXTRL_OPENCL_INTERNAL_C99_HEADERS )
    install( FILES ${SIXTRL_OPENCL_INTERNAL_C99_HEADERS}
             DESTINATION "${C99_HEADERS_INSTALL_PATH}/internal" )
endif()

if( SIXTRL_OPENCL_INTERNAL_CXX_HEADERS )
    install( FILES ${SIXTRL_OPENCL_INTERNAL_CXX_HEADERS}
             DESTINATION "${C99_HEADERS_INSTALL_PATH}/internal" )
endif()
