set( SIXTRL_COMMON_BEAM_ELEMENTS_C99_HEADERS
    definitions.h
    limit_global_aperture.h
    beam_elements.h
    drift.h cavity.h multipole.h
    srotation.h xy_shift.h
    track.h
)

set( SIXTRL_COMMON_BEAM_ELEMENTS_C99_SOURCES )

#add_subdirectory( sixtrack_common_belem OBJECT
#   ${SIXTRL_COMMON_BEAM_ELEMENTS_C99_HEADERS}
#   ${SIXTRL_COMMON_BEAM_ELEMENTS_C99_SOURCES} )
#
# target_include_directories( sixtrack_common_belem PRIVATE
#     $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
#     $<INSTALL_INTERFACE:include> )
#
# set_target_properties( sixtrack_common_belem PROPERTIES
#     LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON
#     C_STANDARD 99 C_STANDARD_REQUIRED ON )
#
# target_compile_options( sixtrack_common_belem PRIVATE
#     ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# -----------------------------------------------------------------------------
# cxx:

set( SIXTRL_COMMON_BEAM_ELEMENTS_CXX_HEADERS beam_elements.hpp drift.hpp
     cavity.hpp multipole.hpp srotation.hpp xy_shift.hpp )

set( SIXTRL_COMMON_BEAM_ELEMENTS_CXX_SOURCES )

#add_subdirectory( sixtrack_common_belem_cxx OBJECT
#   ${SIXTRL_COMMON_BEAM_ELEMENTS_CXX_HEADERS}
#   ${SIXTRL_COMMON_BEAM_ELEMENTS_C99_HEADERS}
#   ${SIXTRL_COMMON_BEAM_ELEMENTS_CXX_SOURCES} )
#
# target_include_directories( sixtrack_common_belem_cxx PRIVATE
#     $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
#     $<INSTALL_INTERFACE:include> )
#
# set_target_properties( sixtrack_common_belem_cxx PROPERTIES
#     LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
#     CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )
#
# target_compile_options( sixtrack_common_belem_cxx PRIVATE
#     ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# =============================================================================
# Submodules:

set( SIXTRL_COMMON_BE_C99_INSTALL_PREFIX
     "${SIXTRL_COMMON_C99_INSTALL_PREFIX}/beam_elements" )

set( SIXTRL_COMMON_BE_CXX_INSTALL_PREFIX
     "${SIXTRL_COMMON_CXX_INSTALL_PREFIX}/beam_elements" )

# -----------------------------------------------------------------------------

set( SIXTRL_COMMON_BEAM_ELEMENTS_LIBRARIES CACHE INTERNAL "" FORCE )

# add_subdirectory( beam_monitor )
add_subdirectory( cavity )
add_subdirectory( drift )
add_subdirectory( multipole )
add_subdirectory( srotation )
add_subdirectory( xy_shift )

add_library( sixtrack_cxx_be SHARED
    ${SIXTRL_COMMON_BEAM_ELEMENTS_C99_HEADERS}
    ${SIXTRL_COMMON_BEAM_ELEMENTS_CXX_HEADERS}
    ${SIXTRL_COMMON_BEAM_ELEMENTS_CXX_SOURCES}
    ${SIXTRL_COMMON_BEAM_ELEMENTS_LIBRARIES} )

# =============================================================================
# python bindings:

if( SIXTRACKL_ENABLE_PYTHON AND pybind11_FOUND )
    add_library( sixtrack_py_common_be OBJECT python_bindings.cpp )

    target_include_directories( sixtrack_py_common_be PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

    set_target_properties( sixtrack_py_common_be PROPERTIES
        LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
        CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

    target_link_libraries( sixtrack_py_common_be PRIVATE pybind11::module )

    set( SIXTRACKLIB_PYTHON_BINDINGS_LIBS ${SIXTRACKLIB_PYTHON_BINDINGS_LIBS}
         $<TARGET_OBJECTS:sixtrack_py_common_be> CACHE STRING "" FORCE )
endif()

# =============================================================================
# Install:

if( SIXTRL_COMMON_BEAM_ELEMENTS_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_BEAM_ELEMENTS_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_C99_INSTALL_PREFIX}/beam_elements" )
endif()

if( SIXTRACKLIB_ENABLE_CXX AND SIXTRL_COMMON_BEAM_ELEMENTS_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_BEAM_ELEMENTS_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_CXX_INSTALL_PREFIX}/beam_elements" )
endif()
