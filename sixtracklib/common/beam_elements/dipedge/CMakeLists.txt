# --------------------------------------------------------------------------
# processing sixtracklib/common/beam_elements/dipedge/CMakeLists.txt

set( SIXTRL_COMMON_BE_DIPEDGE_CXX_HEADERS
     dipedge_traits.hpp
     dipedge_data.hpp
     dipedge.hpp
     track.hpp
)

set( SIXTRL_COMMON_BE_DIPEDGE_CXX_SOURCES )


set( SIXTRL_COMMON_BE_DIPEDGE_C99_HEADERS
     dipedge.h
     dipedge_api.h
     track.h
)

set( SIXTRL_COMMON_BE_DIPEDGE_C99_SOURCES
     dipedge_api.c )


add_library( sixtrack_common_be_dipedge OBJECT
    ${SIXTRL_COMMON_BE_DIPEDGE_C99_HEADERS}
    ${SIXTRL_COMMON_BE_DIPEDGE_CXX_HEADERS}
    ${SIXTRL_COMMON_BE_DIPEDGE_C99_SOURCES}
)

target_include_directories( sixtrack_common_be_dipedge PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_be_dipedge PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON
    C_STANDARD 99 C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_be_dipedge PRIVATE
    ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixtrack_common_be_beambeam as a module for sixtracklib:

set(  SIXTRACKL_LIBRARY_MODULES ${SIXTRACKL_LIBRARY_MODULES}
    $<TARGET_OBJECTS:sixtrack_common_be_dipedge> CACHE INTERNAL "" FORCE )

# =======================================================================
# Install

if( SIXTRL_COMMON_BE_DIPEDGE_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_DIPEDGE_C99_HEADERS}
             DESTINATION "${BE_INSTALL_PREFIX}/dipedge" )
endif()

if( SIXTRL_COMMON_BE_DIPEDGE_CXX_HEADERS AND SIXTRACKL_ENABLE_CXX )
    install( FILES ${SIXTRL_COMMON_BE_DIPEDGE_CXX_HEADERS}
             DESTINATION "${BE_INSTALL_PREFIX}/dipedge" )
endif()

#end:
