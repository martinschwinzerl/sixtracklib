# ----------------------------------------------------------------------------
# sixtracklib/common/particles/CMakeLists.txt

set( SIXTRL_COMMON_PARTICLES_C99_HEADERS
     definitions.h
     particles_addr.h
     particle_unit.h
     particle_unit_api.h
     particle_unit_derived_api.h
     particle_unit_cobjects_api.h
     particle_unit_compare.h
     particle_unit_convert.h
     particle_set.h
     particle_set_helper_api.h
     particle_set_api.h
     particle_set_init.h
     particle_set_convert.h
     particle_set_compare.h
     particle_set_cobjects_api.h
     particle_set_particle_api.h
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
     particle_unit.hpp
     particle_set.hpp
     particle_set_vector.hpp
     particles_addr.hpp
)

set( SIXTRL_COMMON_PARTICLES_CXX_SOURCES
     particle_unit.cpp
     particle_unit_cobjects_api.cpp
     particle_set.cpp
     particle_set_cobjects_api.cpp
 )


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

# =============================================================================
# python bindings:

if( SIXTRACKL_ENABLE_PYTHON AND pybind11_FOUND )
    add_library( sixtrack_py_common_particles OBJECT
                 python_bindings.hpp python_bindings.cpp )

    target_include_directories( sixtrack_py_common_particles PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

    set_target_properties( sixtrack_py_common_particles PROPERTIES
        LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
        CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

    target_link_libraries( sixtrack_py_common_particles
        PRIVATE pybind11::module )

    set( SIXTRACKLIB_PYTHON_BINDINGS_LIBS ${SIXTRACKLIB_PYTHON_BINDINGS_LIBS}
         $<TARGET_OBJECTS:sixtrack_py_common_particles> CACHE STRING "" FORCE )
endif()

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
