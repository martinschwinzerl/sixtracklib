set( SIXTRL_MULTIPREC_PARTICLES_CXX_HEADERS
    particle_unit.hpp particle_set.hpp
)
set( SIXTRL_MULTIPREC_PARTICLES_CXX_SOURCES )

set( SIXTRL_MULTIPREC_PARTICLES_C99_HEADERS )
set( SIXTRL_MULTIPREC_PARTICLES_C99_SOURCES )

# =============================================================================
# python bindings:

if( SIXTRACKL_ENABLE_PYTHON AND pybind11_FOUND )
    add_library( sixtrack_py_multiprec_particles OBJECT python_bindings.cpp )

    target_include_directories( sixtrack_py_multiprec_particles PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

    set_target_properties( sixtrack_py_multiprec_particles PROPERTIES
        LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
        CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

    target_link_libraries( sixtrack_py_multiprec_particles
        PRIVATE pybind11::module )

    if( Boost_FOUND )
        target_link_libraries(
            sixtrack_py_multiprec_particles PRIVATE Boost::boost )
    endif()

    set( SIXTRACKLIB_PYTHON_BINDINGS_LIBS ${SIXTRACKLIB_PYTHON_BINDINGS_LIBS}
         $<TARGET_OBJECTS:sixtrack_py_multiprec_particles>
         CACHE STRING "" FORCE )
endif()

# =============================================================================
# install :

if( SIXTRL_MULTIPREC_PARTICLES_C99_HEADERS )
    install( FILES ${SIXTRL_MULTIPREC_PARTICLES_C99_HEADERS}
         DESTINATION "${SIXTRL_MULTIPREC_C99_INSTALL_PREFIX}/particles" )
 endif()

 if( SIXTRL_MULTIPREC_PARTICLES_CXX_HEADERS AND SIXTRACKL_ENABLE_CXX )
    install( FILES ${SIXTRL_MULTIPREC_PARTICLES_CXX_HEADERS}
         DESTINATION "${SIXTRL_MULTIPREC_CXX_INSTALL_PREFIX}/particles" )
 endif()
