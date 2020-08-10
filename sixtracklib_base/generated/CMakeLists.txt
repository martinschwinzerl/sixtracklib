set( SIXTRL_BASE_GENERATED_INSTALL_PATH ${SIXTRL_BASE_INSTALL_PATH}/generated )

# create an interface library with the generated headers
add_library( sixtrack_base_generated INTERFACE )

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

set( PATH_H_IN  ${CMAKE_CURRENT_SOURCE_DIR}/path.h.in )
set( PATH_H_OUT ${CMAKE_CURRENT_SOURCE_DIR}/path.h )
configure_file( ${PATH_H_IN} ${PATH_H_OUT} @ONLY )
target_sources( sixtrack_base_generated INTERFACE ${PATH_H_OUT} )

# Create a header file encapsulating the choices for the C and C++
# namespaces

set( NAMESPACE_H_IN  ${CMAKE_CURRENT_SOURCE_DIR}/namespace.h.in )
set( NAMESPACE_H_OUT ${CMAKE_CURRENT_SOURCE_DIR}/namespace.h )
configure_file( ${NAMESPACE_H_IN} ${NAMESPACE_H_OUT} @ONLY )
target_sources( sixtrack_base_generated INTERFACE ${NAMESPACE_H_OUT} )

# make the interface library a dependency for sixtrack_base
set( SIXTRL_BASE_INTERFACE_SUBMODULES ${SIXTRL_BASE_INTERFACE_SUBMODULES}
     sixtrack_base_generated PARENT_SCOPE )

# ------------------------------------------------------------------------------
# handle install:

set( SIXTRACKLIB_TOP_LEVEL_DIR "${CMAKE_INSTALL_PREFIX}/" )
set( SIXTRACKLIB_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX} )
set( PATH_H_OUT ${SIXTRL_BASE_GENERATED_INSTALL_PATH}/path.h )
install( CODE
   "set( SIXTRACKLIB_TOP_LEVEL_DIR \"${SIXTRACKLIB_TOP_LEVEL_DIR}\" )
    set( SIXTRACKLIB_INCLUDE_DIR \"${SIXTRACKLIB_INCLUDE_DIR}\" )
    message( STATUS \"Generating: ${PATH_H_OUT}\" )
    configure_file( ${PATH_H_IN} ${PATH_H_OUT} @ONLY )"
)

set( NAMESPACE_H_OUT ${SIXTRL_BASE_GENERATED_INSTALL_PATH}/namespace.h )
install( CODE
   "set( SIXTRACKL_C_NAMESPACE_STR \"${SIXTRACKL_C_NAMESPACE_STR}\" )
    set( SIXTRACKL_C_NAMESPACE_PREFIX \"${SIXTRACKL_C_NAMESPACE_PREFIX}\" )
    set( SIXTRACKL_CXX_NAMESPACE \"${SIXTRACKL_CXX_NAMESPACE}\" )
    set( SIXTRACKL_CXX_NAMESPACE_PREFIX \"${SIXTRACKL_CXX_NAMESPACE_PREFIX}\" )
    message( STATUS \"Generating: ${NAMESPACE_H_OUT}\" )
    configure_file( ${NAMESPACE_H_IN} ${NAMESPACE_H_OUT} @ONLY )"
)
