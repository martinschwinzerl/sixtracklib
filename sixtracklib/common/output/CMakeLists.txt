# sixtracklib/common/output/CMakeLists.txt

set( SIXTRACKLIB_COMMON_OUTPUT_C99_HEADERS
     elem_by_elem_config.h
     elem_by_elem_output_buffer.h
     output_buffer.h
)

set( SIXTRACKLIB_COMMON_OUTPUT_C99_SOURCES
     elem_by_elem_config.c
     elem_by_elem_output_buffer.c
     output_buffer.c
)

set( SIXTRACKLIB_COMMON_OUTPUT_CXX_HEADERS
     output_buffer.hpp
)

set( SIXTRACKLIB_COMMON_OUTPUT_CXX_SOURCES )

# ------------------------------------------------------------------------------
# build sixtrack_common_output  submodule object library

add_library( sixtrack_common_output OBJECT
             ${SIXTRACKLIB_COMMON_OUTPUT_C99_HEADERS}
             ${SIXTRACKLIB_COMMON_OUTPUT_C99_SOURCES}
)

target_include_directories( sixtrack_common_output PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_output PROPERTIES LINKER_LANGUAGE C )
set_target_properties( sixtrack_common_output
                       PROPERTIES POSITION_INDEPENDENT_CODE ON )

set_target_properties( sixtrack_common_output PROPERTIES C_STANDARD 99 )
set_target_properties( sixtrack_common_output
                       PROPERTIES C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_output PRIVATE
                        -Wall -Werror -pedantic -ansi ${SIXTRACKLIB_CPU_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixtrack_common_output as a module for sixtracklib:

set(  SIXTRACKL_LIBRARY_MODULES
    ${SIXTRACKL_LIBRARY_MODULES}
    $<TARGET_OBJECTS:sixtrack_common_output> CACHE INTERNAL "" FORCE )

# ------------------------------------------------------------------------------
# Pass in C++ headers to parent scope to track as a depenency for the whole lib

if( SIXTRACKLIB_COMMON_OUTPUT_CXX_HEADERS )
    string( REGEX REPLACE "([^;]+)" "output/\\1" LOCAL_CXX_HEADERS
            "${SIXTRACKLIB_COMMON_OUTPUT_CXX_HEADERS}" )

    set(  SIXTRACKLIB_COMMON_CXX_HEADERS
        ${SIXTRACKLIB_COMMON_CXX_HEADERS}
        ${LOCAL_CXX_HEADERS} PARENT_SCOPE )
endif()

# ==============================================================================
# install :

if( SIXTRACKLIB_COMMON_OUTPUT_C99_HEADERS )

    set( SIXTRACKLIB_COMMON_OUTPUT_C99_INSTALL_PATH
         include/sixtracklib/common/output )

    install( FILES ${SIXTRACKLIB_COMMON_OUTPUT_C99_HEADERS}
             DESTINATION ${SIXTRACKLIB_COMMON_OUTPUT_C99_INSTALL_PATH} )
endif()


if( SIXTRACKLIB_COMMON_OUTPUT_CXX_HEADERS )

    set( SIXTRACKLIB_COMMON_OUTPUT_CXX_INSTALL_PATH
         include/sixtracklib/common/output )

    install( FILES ${SIXTRACKLIB_COMMON_OUTPUT_CXX_HEADERS}
             DESTINATION ${SIXTRACKLIB_COMMON_OUTPUT_CXX_INSTALL_PATH} )
endif()

# end: sixtracklib/common/output/CMakeLists.txt
