set( SIXTRL_COMMON_BE_CAVITY_C99_HEADERS
    definitions.h
    cavity.h
    cavity_api.h
    cavity_derived_api.h
    cavity_init.h
    cavity_convert.h
    cavity_compare.h
    cavity_cobjects_api.h
    track.h )

set( SIXTRL_COMMON_BE_CAVITY_C99_SOURCES )

#add_subdirectory( sixtrack_common_be_cavity OBJECT
#   ${SIXTRL_COMMON_BE_CAVITY_C99_HEADERS}
#   ${SIXTRL_COMMON_BE_CAVITY_C99_SOURCES} )
#
# target_include_directories( sixtrack_common_be_cavity PRIVATE
#     $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
#     $<INSTALL_INTERFACE:include> )
#
# set_target_properties( sixtrack_common_be_cavity PROPERTIES
#     LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON
#     C_STANDARD 99 C_STANDARD_REQUIRED ON )
#
# target_compile_options( sixtrack_common_be_cavity PRIVATE
#     ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# -----------------------------------------------------------------------------
# cxx:

set( SIXTRL_COMMON_BE_CAVITY_CXX_HEADERS cavity.hpp )
set( SIXTRL_COMMON_BE_CAVITY_CXX_SOURCES
     cavity.cpp cavity_cobjects_api.cpp )

add_library( sixtrack_common_belems_cavity_cxx OBJECT
  ${SIXTRL_COMMON_BE_CAVITY_CXX_HEADERS}
  ${SIXTRL_COMMON_BE_CAVITY_C99_HEADERS}
  ${SIXTRL_COMMON_BE_CAVITY_CXX_SOURCES} )

target_include_directories( sixtrack_common_belems_cavity_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_belems_cavity_cxx PROPERTIES
    LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_belems_cavity_cxx PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

set( SIXTRL_COMMON_BEAM_ELEMENTS_LIBRARIES
    ${SIXTRL_COMMON_BEAM_ELEMENTS_LIBRARIES}
    $<TARGET_OBJECTS:sixtrack_common_belems_cavity_cxx>
    CACHE INTERNAL "" FORCE )

# =============================================================================
# python bindings:

if( SIXTRACKL_ENABLE_PYTHON AND pybind11_FOUND )
    add_library( sixtrack_py_common_be_cavity OBJECT
                 python_bindings.hpp python_bindings.cpp )

    target_include_directories( sixtrack_py_common_be_cavity PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

    set_target_properties( sixtrack_py_common_be_cavity PROPERTIES
        LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
        CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

    target_link_libraries( sixtrack_py_common_be_cavity
        PRIVATE pybind11::module )

    set( SIXTRACKLIB_PYTHON_BINDINGS_LIBS ${SIXTRACKLIB_PYTHON_BINDINGS_LIBS}
         $<TARGET_OBJECTS:sixtrack_py_common_be_cavity>
         CACHE STRING "" FORCE )
endif()

# =============================================================================
# Install:

if( SIXTRL_COMMON_BE_CAVITY_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_CAVITY_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_BE_C99_INSTALL_PREFIX}/cavity" )
endif()

if( SIXTRACKLIB_ENABLE_CXX AND SIXTRL_COMMON_BE_CAVITY_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_CAVITY_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_BE_C99_INSTALL_PREFIX}/cavity" )
endif()
