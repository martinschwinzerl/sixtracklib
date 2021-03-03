set( SIXTRL_COMMON_CONTROL_CXX_HEADERS )
set( SIXTRL_COMMON_CONTROL_CXX_SOURCES
    argument.cpp controller.cpp node_id.cpp node_info.cpp
    program_item.cpp program_store.cpp )

set( SIXTRL_COMMON_CONTROL_C99_SOURCES )
set( SIXTRL_COMMON_CONTROL_C99_HEADERS
    definitions.h argument.h controller.h node_id.h node_info.h
    program_item.h program_store.h )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( sixtrack_common_control_cxx OBJECT
    ${SIXTRL_COMMON_CONTROL_CXX_HEADERS}
    ${SIXTRL_COMMON_CONTROL_C99_HEADERS}
    ${SIXTRL_COMMON_CONTROL_CXX_SOURCES} )

target_include_directories( sixtrack_common_control_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_control_cxx PROPERTIES CXX_STANDARD 11
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_control_cxx
    PRIVATE ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixtrack_common_control_cxx as a module for sixtracklib:

set(  SIXTRL_COMMON_MODULES ${SIXTRL_COMMON_MODULES}
    $<TARGET_OBJECTS:sixtrack_common_control_cxx> PARENT_SCOPE )

# -----------------------------------------------------------------------------
# install :

if( SIXTRL_COMMON_CONTROL_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_CONTROL_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_C99_INSTALL_PREFIX}/control" )
endif()

if( SIXTRL_COMMON_CONTROL_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_CONTROL_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_C99_INSTALL_PREFIX}/control" )
endif()
