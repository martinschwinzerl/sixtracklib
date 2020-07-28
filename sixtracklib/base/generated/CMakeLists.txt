# ==============================================================================
# common/generated sixtracklib submodule

set( C99_HEADERS )
set( SIXTRL_BASE_GENERATED_INSTALL_PATH ${SIXTRL_BASE_INSTALL_PATH}/generated )

# ------------------------------------------------------------------------------
# modules.h is a header file with pre-defined constants, allownig the user
# of the library to query which modules are present in from C/C++ code

set( MODULES_H_IN_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/modules.h.in )
set( MODULES_H_OUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules.h )
configure_file( ${MODULES_H_IN_PATH} ${MODULES_H_OUT_PATH} @ONLY )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# install:

set( MODULES_H_OUT_PATH ${SIXTRL_BASE_GENERATED_INSTALL_PATH}/modules.h )
install( CODE
    "${SIXTRACKLIB_MODULES_STR}
    message( STATUS \"Generating: ${MODULES_H_OUT_PATH}\" )
    configure_file( \"${MODULES_H_IN_PATH}\" \"${MODULES_H_OUT_PATH}\" @ONLY )"
)

# ------------------------------------------------------------------------------
# create a header file common/generated/path.h with the current,
# local absolute path to this directory. This is used as prefix for all
# source files which have to be processed during run-time
# (e.g. GPU Kernels, etc.)

# Note: Paths in CMake always use a slash as separator and always lack a
#       trailing slashes -> add them to make it easier to use the
#       macro in common/generated/path.h as a prefix for
#       filename and directory paths!

set( SIXTRACKLIB_TOP_LEVEL_DIR "${CMAKE_SOURCE_DIR}/" )
set( SIXTRACKLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR} )

set( PATH_H_IN_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/path.h.in )
set( PATH_H_OUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/path.h )
configure_file( ${PATH_H_IN_PATH} ${PATH_H_OUT_PATH} @ONLY )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# install:

set( SIXTRACKLIB_TOP_LEVEL_DIR "${CMAKE_INSTALL_PREFIX}/" )
set( SIXTRACKLIB_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX} )
set( PATH_H_OUT_PATH ${SIXTRL_BASE_GENERATED_INSTALL_PATH}/path.h )
install( CODE
   "set( SIXTRACKLIB_TOP_LEVEL_DIR \"${SIXTRACKLIB_TOP_LEVEL_DIR}\" )
    set( SIXTRACKLIB_INCLUDE_DIR \"${SIXTRACKLIB_INCLUDE_DIR}\" )
    message( STATUS \"Generating: ${PATH_H_OUT_PATH}\" )
    configure_file( \"${PATH_H_IN_PATH}\" \"${PATH_H_OUT_PATH}\" @ONLY )"
)

# ------------------------------------------------------------------------------
# Create a header file encapsulating the choices for the C and C++
# namespaces

set( NAMESPACE_H_IN_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/namespace.h.in" )
set( NAMESPACE_H_OUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/namespace.h" )
configure_file( ${NAMESPACE_H_IN_PATH} ${NAMESPACE_H_OUT_PATH} @ONLY )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# install:

set( NAMESPACE_H_OUT_PATH "${SIXTRL_BASE_GENERATED_INSTALL_PATH}/namespace.h" )
install( CODE
   "set( SIXTRACKL_C_NAMESPACE_STR \"${SIXTRACKL_C_NAMESPACE_STR}\" )
    set( SIXTRACKL_C_NAMESPACE_PREFIX \"${SIXTRACKL_C_NAMESPACE_PREFIX}\" )
    set( SIXTRACKL_CXX_NAMESPACE \"${SIXTRACKL_CXX_NAMESPACE}\" )
    set( SIXTRACKL_CXX_NAMESPACE_PREFIX \"${SIXTRACKL_CXX_NAMESPACE_PREFIX}\" )
    message( STATUS \"Generating: ${NAMESPACE_H_OUT_PATH}\" )
    configure_file( \"${NAMESPACE_H_IN_PATH}\" \"${NAMESPACE_H_OUT_PATH}\" @ONLY )"
)

# ------------------------------------------------------------------------------

set( SIXTRL_BASE_HEADERS ${SIXTRL_BASE_HEADERS}
     generated/modules.h generated/namespace.h generated/path.h PARENT_SCOPE )
