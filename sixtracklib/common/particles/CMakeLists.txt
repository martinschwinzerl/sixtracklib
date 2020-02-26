# ----------------------------------------------------------------------------
# sixtracklib/common/particles/CMakeLists.txt

set( SIXTRL_COMMON_PARTICLES_C99_HEADERS
     definitions.h
     particles_addr.h
     particle.h
     storage_cobjects.h
)

set( SIXTRL_COMMON_PARTICLES_C99_SOURCES
     particles.c
     particles_addr.c
)

add_library( sixtrack_common_particles_c99 OBJECT
    ${SIXTRL_COMMON_PARTICLES_C99_HEADERS}
    ${SIXTRL_COMMON_PARTICLES_C99_SOURCES}
)

target_include_directories( sixtrack_common_particles_c99 PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_particles_c99 PROPERTIES
    POSITION_INDEPENDENT_CODE ON LINKER_LANGUAGE C C_STANDARD 99
    C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_particles_c99 PRIVATE
    ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# -----------------------------------------------------------------------------

set( SIXTRL_COMMON_PARTICLES_CXX_HEADERS
     particle.hpp
     particle_data.hpp
     particles_addr.hpp )

set( SIXTRL_COMMON_PARTICLES_CXX_SOURCES
     storage_cobjects.cpp )


add_library( sixtrack_common_particles_cxx OBJECT
  ${SIXTRL_COMMON_PARTICLES_CXX_HEADERS}
  ${SIXTRL_COMMON_PARTICLES_C99_HEADERS}
  ${SIXTRL_COMMON_PARTICLES_CXX_SOURCES} )

target_include_directories( sixtrack_common_particles_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_particles_cxx PROPERTIES
    LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_particles_cxx PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# -----------------------------------------------------------------------------

set(  SIXTRACKL_LIBRARY_MODULES ${SIXTRACKL_LIBRARY_MODULES}
    $<TARGET_OBJECTS:sixtrack_common_particles_c99>
    $<TARGET_OBJECTS:sixtrack_common_particles_cxx>
    CACHE INTERNAL "" FORCE )

# ==============================================================================
# Handle install:

if( SIXTRL_COMMON_PARTICLES_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_INTERNAL_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_C99_INSTALL_PREFIX}/particles" )
endif()

if( SIXTRACKLIB_ENABLE_CXX AND SIXTRL_COMMON_PARTICLES_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_INTERNAL_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_CXX_INSTALL_PREFIX}/particles" )
endif()

#end: sixtracklib/common/particles/CMakeLists.txt
