set( SIXTRL_MULTIPREC_BEAM_ELEMENTS_CXX_HEADERS
    cavity.hpp
    drift.hpp
    multipole.hpp
    srotation.hpp
    xy_shift.hpp
)

set( SIXTRL_MULTIPREC_BEAM_ELEMENTS_CXX_SOURCES )

set( SIXTRL_MULTIPREC_BEAM_ELEMENTS_C99_HEADERS )
set( SIXTRL_MULTIPREC_BEAM_ELEMENTS_C99_SOURCES )

# =============================================================================
# python bindings:

if( SIXTRACKL_ENABLE_PYTHON AND pybind11_FOUND )
    add_subdirectory( python_bindings )
endif()

# =============================================================================
# install :

if( SIXTRL_MULTIPREC_BEAM_ELEMENTS_C99_HEADERS )
    install( FILES ${SIXTRL_MULTIPREC_BEAM_ELEMENTS_C99_HEADERS}
         DESTINATION "${SIXTRL_MULTIPREC_C99_INSTALL_PREFIX}/beam_elements" )
 endif()

 if( SIXTRL_MULTIPREC_BEAM_ELEMENTS_CXX_HEADERS AND SIXTRACKL_ENABLE_CXX )
    install( FILES ${SIXTRL_MULTIPREC_BEAM_ELEMENTS_CXX_HEADERS}
         DESTINATION "${SIXTRL_MULTIPREC_CXX_INSTALL_PREFIX}/beam_elements" )
 endif()
