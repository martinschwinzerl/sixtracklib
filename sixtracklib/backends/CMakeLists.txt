message( STATUS "---- processing sixtracklib/backends/CMakeLists.txt" )

# prepare the install path for all headers belonging to this module
set( SIXTRL_BACKENDS_INSTALL_PATH "${SIXTRL_INSTALL_PATH}/backends" )

# create a backends.h file for encoding the enabled / disabled options
set( BACKENDS_H_IN  ${CMAKE_CURRENT_SOURCE_DIR}/backends.h.in )
set( BACKENDS_H_OUT ${CMAKE_CURRENT_SOURCE_DIR}/backends.h )
configure_file( ${BACKENDS_H_IN} ${BACKENDS_H_OUT} @ONLY )

# ------------------------------------------------------------------------------
# prepare iteration over the individual backends:

set( SIXTRACKLIB_BACKENDS_SUBMODULES )
set( SIXTRACKLIB_BACKENDS_SUBMODULES_LINK_LIBRARIES )

add_subdirectory( cuda )

set( SIXTRACKLIB_SUBMODULES
   ${SIXTRACKLIB_SUBMODULES} ${SIXTRACKLIB_BACKENDS_SUBMODULES} PARENT_SCOPE )

set( SIXTRACKLIB_SUBMODULES_LINK_LIBRARIES
   ${SIXTRACKLIB_SUBMODULES_LINK_LIBRARIES}
   ${SIXTRACKLIB_BACKENDS_SUBMODULES_LINK_LIBRARIES} PARENT_SCOPE )

# ------------------------------------------------------------------------------
# Handle install:

set( BACKENDS_H_OUT ${SIXTRL_BACKENDS_INSTALL_PATH}/backends.h )
install( CODE
    "${SIXTRACKLIB_BACKENDS_STR}
     message( STATUS \"Generating: ${BACKENDS_H_OUT}\" )
     configure_file( \"${BACKENDS_H_IN}\" \"${BACKENDS_H_OUT}\" @ONLY )" )
