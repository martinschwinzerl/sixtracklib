set( SIXTRL_COMMON_INTERNAL_C99_SOURCES math_qgauss.c )
set( SIXTRL_COMMON_INTERNAL_C99_HEADERS
    math_constants.h math_factorial.h math_functions.h
    math_interpol.h math_qgauss.h namespace_defines.h namespace_undef.h
    tools.h type_comparison_helpers.h )

set( SIXTRL_COMMON_INTERNAL_CXX_HEADERS file_tools.h thread_id.h thread_lock.h )
set( SIXTRL_COMMON_INTERNAL_CXX_SOURCES
    file_tools.cpp thread_id.cpp thread_lock.cpp )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( sixtrack_common_internal_c99 OBJECT
    ${SIXTRL_COMMON_INTERNAL_C99_HEADERS}
    ${SIXTRL_COMMON_INTERNAL_CXX_HEADERS}
    ${SIXTRL_COMMON_INTERNAL_C99_SOURCES}
)

target_include_directories( sixtrack_common_internal_c99 PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_internal_c99 PROPERTIES LINKER_LANGUAGE C
    POSITION_INDEPENDENT_CODE ON C_STANDARD 99 C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_internal_c99 PRIVATE
    ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKLIB_C99_AUTOVEC_FLAGS} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( sixtrack_common_internal_cxx OBJECT
    ${SIXTRL_COMMON_INTERNAL_CXX_HEADERS}
    ${SIXTRL_COMMON_INTERNAL_C99_HEADERS}
    ${SIXTRL_COMMON_INTERNAL_CXX_SOURCES} )

target_include_directories( sixtrack_common_internal_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_internal_cxx PROPERTIES LINKER_LANGUAGE C
    POSITION_INDEPENDENT_CODE ON CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_internal_cxx PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixtrack_common_internal as a module for sixtracklib:

set(  SIXTRL_COMMON_MODULES ${SIXTRL_COMMON_MODULES}
    $<TARGET_OBJECTS:sixtrack_common_internal_c99>
    $<TARGET_OBJECTS:sixtrack_common_internal_cxx> PARENT_SCOPE )

# -----------------------------------------------------------------------------
# install :

if( SIXTRL_COMMON_INTERNAL_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_INTERNAL_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_C99_INSTALL_PREFIX}/internal" )
endif()

if( SIXTRL_COMMON_INTERNAL_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_INTERNAL_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_CXX_INSTALL_PREFIX}/internal" )
endif()
