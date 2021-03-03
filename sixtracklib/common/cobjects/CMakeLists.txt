set( SIXTRL_COMMON_COBJECTS_CXX_HEADERS cbuffer_view.hpp cbuffer.hpp )
set( SIXTRL_COMMON_COBJECTS_CXX_SOURCES cbuffer_c99.cpp cbuffer.cpp )

set( SIXTRL_COMMON_COBJECTS_C99_SOURCES index_object.c )
set( SIXTRL_COMMON_COBJECTS_C99_HEADERS
     definitions.h cobj_illegal_type.h cobj_type_traits.h
     address_manipulations.h cbuffer.h index_object.h flat_buffer.h
     garbage_range.h )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# c99:

add_library( sixtrack_common_cobjects_c99 OBJECT
  ${SIXTRL_COMMON_COBJECTS_C99_HEADERS}
  ${SIXTRL_COMMON_COBJECTS_CXX_HEADERS}
  ${SIXTRL_COMMON_COBJECTS_C99_SOURCES} )

target_include_directories( sixtrack_common_cobjects_c99 PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_cobjects_c99 PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON
    C_STANDARD 99 C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_cobjects_c99 PRIVATE
    ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_C99_AUTOVEC_FLAGS} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# cxx:

add_library( sixtrack_common_cobjects_cxx OBJECT
  ${SIXTRL_COMMON_COBJECTS_CXX_HEADERS}
  ${SIXTRL_COMMON_COBJECTS_C99_HEADERS}
  ${SIXTRL_COMMON_COBJECTS_CXX_SOURCES} )

target_include_directories( sixtrack_common_cobjects_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_cobjects_cxx PROPERTIES
    LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_cobjects_cxx PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )


set(  SIXTRL_COMMON_MODULES ${SIXTRL_COMMON_MODULES}
    $<TARGET_OBJECTS:sixtrack_common_cobjects_c99>
    $<TARGET_OBJECTS:sixtrack_common_cobjects_cxx> PARENT_SCOPE )

# =============================================================================
# Install:

if( SIXTRL_COMMON_COBJECTS_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_COBJECTS_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_C99_INSTALL_PREFIX}/cobjects" )
endif()

if( SIXTRL_COMMON_COBJECTS_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_COBJECTS_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_CXX_INSTALL_PREFIX}/cobjects" )
endif()
