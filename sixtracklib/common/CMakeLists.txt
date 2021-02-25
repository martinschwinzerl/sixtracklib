# ==============================================================================
# sixtracklib/common/CMakeLists.txt

message( STATUS "---- processing sixtracklib/common/CMakeLists.txt" )

set( SIXTRL_COMMON_C99_INSTALL_PREFIX
     "${SIXTRACKLIB_C99_INSTALL_PREFIX}/common" )

set( SIXTRL_COMMON_CXX_INSTALL_PREFIX
     "${SIXTRACKLIB_CXX_INSTALL_PREFIX}/common" )

set(  SIXTRACKL_LINK_LIBRARIES ${SIXTRACKL_LINK_LIBRARIES} PARENT_SCOPE )

set( SIXTRACKLIB_COMMON_C99_HEADERS )
set( SIXTRACKLIB_COMMON_CXX_HEADERS )
set( SIXTRACKLIB_COMMON_PYTHON_BINDINGS_LIBS )

add_subdirectory( backends       )
add_subdirectory( beam_elements  )
add_subdirectory( cobjects       )
add_subdirectory( generated      )
# add_subdirectory( control        )
add_subdirectory( internal       )
add_subdirectory( particles      )
add_subdirectory( track          )

set(  SIXTRACKLIB_C99_HEADERS ${SIXTRACKLIB_C99_HEADERS}
#       beam_elements.h buffer.h constants.h controller.h definitions.h
#       particles.h track_job.h track_job_cpu.h
)

set(  SIXTRACKLIB_CXX_HEADERS ${SIXTRACKLIB_CXX_HEADERS}
#       beam_elements.hpp buffer.hpp particles.hpp
)

# =============================================================================
# python bindings:

# if( SIXTRACKL_ENABLE_PYTHON AND pybind11_FOUND )
#     add_library( sixtrack_py_common OBJECT
#         python_bindings.hpp python_bindings.cpp )
#
#     target_include_directories( sixtrack_py_common PRIVATE
#         $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )
#
#     set_target_properties( sixtrack_py_common PROPERTIES
#         LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
#         CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )
#
#     target_link_libraries( sixtrack_py_common PRIVATE pybind11::module )
#
#     set( SIXTRL_PYTHON_BINDINGS_MODULES ${SIXTRL_PYTHON_BINDINGS_MODULES}
#        $<TARGET_OBJECTS:sixtrack_py_common>
#        ${SIXTRACKLIB_COMMON_PYTHON_BINDINGS_LIBS} PARENT_SCOPE )
# endif()

# ------------------------------------------------------------------------------
# install :

if( SIXTRACKLIB_C99_HEADERS OR SIXTRACKLIB_COMMON_C99_HEADERS )
    install( FILES ${SIXTRACKLIB_C99_HEADERS} ${SIXTRACKLIB_COMMON_C99_HEADERS}
             DESTINATION ${SIXTRL_COMMON_C99_INSTALL_PREFIX} )
endif()

if( SIXTRACKL_ENABLE_CXX AND
    ( SIXTRACKLIB_CXX_HEADERS OR SIXTRACKLIB_COMMON_CXX_HEADERS ) )

    install( FILES ${SIXTRACKLIB_CXX_HEADERS} ${SIXTRACKLIB_COMMON_CXX_HEADERS}
             DESTINATION ${SIXTRL_COMMON_CXX_INSTALL_PREFIX} )
endif()

# end: sixtracklib/common/CMakeLists.txt
