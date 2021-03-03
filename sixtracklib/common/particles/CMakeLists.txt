# ----------------------------------------------------------------------------
# sixtracklib/common/particles/CMakeLists.txt

set( SIXTRL_COMMON_PARTICLES_C99_SOURCES particle.c particles.c particles_addr.c )
set( SIXTRL_COMMON_PARTICLES_C99_HEADERS definitions.h particles_undef.h
    particle_helper.h particle.h particle_cobj.h
    particles_addr.h particles_addr_cobj.h
    particles.h particles_cobj.h )

set( SIXTRL_COMMON_PARTICLES_CXX_SOURCES particles.cpp)
set( SIXTRL_COMMON_PARTICLES_CXX_HEADERS )

set( SIXTRL_COMMON_PARTICLES_PARENT_CXX_HEADERS )
set( SIXTRL_COMMON_PARTICLES_PARENT_C99_HEADERS ../definitions.h )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( SIXTRACKL_ENABLE_DEMOTRACK )
    set( SIXTRL_COMMON_PARTICLES_C99_HEADERS
       ${SIXTRL_COMMON_PARTICLES_C99_HEADERS} demotrack.h )
endif()

add_library( sixtrack_common_particles_c99 OBJECT
    ${SIXTRL_COMMON_PARTICLES_C99_HEADERS}
    ${SIXTRL_COMMON_PARTICLES_CXX_HEADERS}
    ${SIXTRL_COMMON_PARTICLES_PARENT_C99_HEADERS}
    ${SIXTRL_COMMON_PARTICLES_PARENT_CXX_HEADERS}
    ${SIXTRL_COMMON_PARTICLES_C99_SOURCES} )

target_include_directories( sixtrack_common_particles_c99 PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_particles_c99 PROPERTIES
    POSITION_INDEPENDENT_CODE ON LINKER_LANGUAGE C C_STANDARD 99
    C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_particles_c99 PRIVATE
    ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_C99_AUTOVEC_FLAGS} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( sixtrack_common_particles_cxx OBJECT
    ${SIXTRL_COMMON_PARTICLES_CXX_HEADERS}
    ${SIXTRL_COMMON_PARTICLES_C99_HEADERS}
    ${SIXTRL_COMMON_PARTICLES_PARENT_C99_HEADERS}
    ${SIXTRL_COMMON_PARTICLES_PARENT_CXX_HEADERS}
    ${SIXTRL_COMMON_PARTICLES_CXX_SOURCES} )

target_include_directories( sixtrack_common_particles_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_particles_cxx PROPERTIES
    POSITION_INDEPENDENT_CODE ON LINKER_LANGUAGE C CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_particles_cxx PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

# ==============================================================================

set(  SIXTRL_COMMON_MODULES ${SIXTRL_COMMON_MODULES}
    $<TARGET_OBJECTS:sixtrack_common_particles_c99>
    $<TARGET_OBJECTS:sixtrack_common_particles_cxx> PARENT_SCOPE )

# ==============================================================================
# Handle install:

if( SIXTRL_COMMON_PARTICLES_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_INTERNAL_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_C99_INSTALL_PREFIX}/particles" )
endif()

if( SIXTRL_COMMON_PARTICLES_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_PARTICLES_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_CXX_INSTALL_PREFIX}/particles" )
endif()
