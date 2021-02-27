set( SIXTRL_TESTLIB_PARTICLES_C99_SOURCES )
set( SIXTRL_TESTLIB_PARTICLES_C99_HEADERS
     particle.h particles.h particles_addr.h )

set( SIXTRL_TESTLIB_PARTICLES_CXX_HEADERS )
set( SIXTRL_TESTLIB_PARTICLES_CXX_SOURCES particle.cpp particles.cpp )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( sixtrack_testlib_common_particles_cxx OBJECT
             ${SIXTRL_TESTLIB_PARTICLES_CXX_HEADERS}
             ${SIXTRL_TESTLIB_PARTICLES_C99_HEADERS}
             ${SIXTRL_TESTLIB_PARTICLES_CXX_SOURCES} )

target_include_directories( sixtrack_testlib_common_particles_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_testlib_common_particles_cxx PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_testlib_common_particles_cxx PRIVATE
        ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
        ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( SIXTRL_TESTLIB_COMMON_OBJ_LIBRARIES ${SIXTRL_TESTLIB_COMMON_OBJ_LIBRARIES}
     $<TARGET_OBJECTS:sixtrack_testlib_common_particles_cxx> PARENT_SCOPE )

# -----------------------------------------------------------------------------
# install:

if( SIXTRL_TESTLIB_PARTICLES_C99_HEADERS )
    install( FILES ${SIXTRL_TESTLIB_PARTICLES_C99_HEADERS}
             DESTINATION "${SIXTRL_TESTLIB_COMMON_C99_INSTALL_PREFIX}/particles" )
endif()

if( SIXTRACKL_ENABLE_CXX AND SIXTRL_TESTLIB_PARTICLES_CXX_HEADERS )
    install( FILES ${SIXTRL_TESTLIB_PARTICLES_CXX_HEADERS}
             DESTINATION "${SIXTRL_TESTLIB_COMMON_CXX_INSTALL_PREFIX}/particles" )
 endif()
