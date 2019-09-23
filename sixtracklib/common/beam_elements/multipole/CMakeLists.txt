# --------------------------------------------------------------------------
# processing sixtracklib/common/beam_elements/multipole/CMakeLists.txt

set( SIXTRL_COMMON_BE_MULTIPOLE_CXX_HEADERS
     multipole_traits.hpp
     multipole_data.hpp
     multipole.hpp
     track.hpp
)

set( SIXTRL_COMMON_BE_MULTIPOLE_CXX_SOURCES )


set( SIXTRL_COMMON_BE_MULTIPOLE_C99_HEADERS
     multipole.h
     multipole_api.h
     track.h
)

set( SIXTRL_COMMON_BE_MULTIPOLE_C99_SOURCES
     multipole_api.c
)

add_library( sixtrack_common_be_multipole OBJECT
    ${SIXTRL_COMMON_BE_MULTIPOLE_C99_HEADERS}
    ${SIXTRL_COMMON_BE_MULTIPOLE_CXX_HEADERS}
    ${SIXTRL_COMMON_BE_MULTIPOLE_C99_SOURCES}
)

target_include_directories( sixtrack_common_be_multipole PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_be_multipole PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON
    C_STANDARD 99 C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_be_multipole PRIVATE
    ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixtrack_common_be_multipole as a module for sixtracklib:

set(  SIXTRACKL_LIBRARY_MODULES ${SIXTRACKL_LIBRARY_MODULES}
    $<TARGET_OBJECTS:sixtrack_common_be_multipole> CACHE INTERNAL "" FORCE )

# =======================================================================
# Install

if( SIXTRL_COMMON_BE_MULTIPOLE_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_MULTIPOLE_C99_HEADERS}
             DESTINATION "${BE_INSTALL_PREFIX}/multipole" )
endif()

if( SIXTRL_COMMON_BE_MULTIPOLE_CXX_HEADERS AND SIXTRACKL_ENABLE_CXX )
    install( FILES ${SIXTRL_COMMON_BE_MULTIPOLE_CXX_HEADERS}
             DESTINATION "${BE_INSTALL_PREFIX}/multipole" )
endif()

#end: sixtracklib/common/beam_elements/multipole/CMakeLists.txt
