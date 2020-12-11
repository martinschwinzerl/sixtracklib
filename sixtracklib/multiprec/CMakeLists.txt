# ==============================================================================
# Multiprecision sixtracklib architecture
message( STATUS "---- processing sixtracklib/multiprec/CMakeLists.txt" )

set( SIXTRL_MULTIPREC_C99_HEADERS definitions.h )
set( SIXTRL_MULTIPREC_C99_SOURCES )

set( SIXTRL_MULTIPREC_CXX_HEADERS random.hpp )
set( SIXTRL_MULTIPREC_CXX_SOURCES )

if( Boost_FOUND )
    set( SIXTRACKL_LINK_LIBRARIES ${SIXTRACKL_LINK_LIBRARIES}
        Boost::boost CACHE INTERNAL "" FORCE )
endif()

set(   SIXTRL_MULTIPREC_C99_INSTALL_PREFIX
    "${SIXTRACKLIB_C99_INSTALL_PATH}/multiprec" )

set(   SIXTRL_MULTIPREC_CXX_INSTALL_PREFIX
    "${SIXTRACKLIB_CXX_INSTALL_PATH}/multiprec" )

add_subdirectory( beam_elements )
add_subdirectory( particles )

# =============================================================================
# python bindings:

if( SIXTRACKL_ENABLE_PYTHON AND pybind11_FOUND )
    add_library( sixtrack_py_multiprec OBJECT python_bindings.cpp )

    target_include_directories( sixtrack_py_multiprec PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

    set_target_properties( sixtrack_py_multiprec PROPERTIES
        LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
        CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

    target_link_libraries( sixtrack_py_multiprec PRIVATE pybind11::module )

    if( Boost_FOUND )
        target_link_libraries( sixtrack_py_multiprec PRIVATE Boost::boost )
    endif()

    set( SIXTRACKLIB_PYTHON_BINDINGS_LIBS ${SIXTRACKLIB_PYTHON_BINDINGS_LIBS}
         $<TARGET_OBJECTS:sixtrack_py_multiprec> CACHE STRING "" FORCE )
endif()

# =============================================================================
# install :

if( SIXTRL_MULTIPREC_C99_HEADERS )
    install( FILES ${SIXTRL_MULTIPREC_C99_HEADERS}
         DESTINATION ${SIXTRL_MULTIPREC_C99_INSTALL_PREFIX} )
 endif()

 if( SIXTRL_MULTIPREC_CXX_HEADERS AND SIXTRACKL_ENABLE_CXX )
    install( FILES ${SIXTRL_MULTIPREC_CXX_HEADERS}
         DESTINATION ${SIXTRL_MULTIPREC_CXX_INSTALL_PREFIX} )
 endif()

#end: sixtracklib/multiprec/CMakeLists.txt
