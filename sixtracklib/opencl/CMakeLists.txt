# ==============================================================================
# OpenCL 1.x sixtracklib submodule

message( STATUS "---- processing sixtracklib/opencl/CMakeLists.txt" )

set( SIXTRL_OPENCL_C99_INSTALL_PREFIX "${SIXTRL_C99_INSTALL_PREFIX}/opencl" )
set( SIXTRL_OPENCL_CXX_INSTALL_PREFIX "${SIXTRL_CXX_INSTALL_PREFIX}/opencl" )
set( SIXTRL_DEFAULT_OPENCL_COMPILER_FLAGS "" )

if( SIXTRACKL_OPENCL_DEFAULT_COMPILER_FLAGS )
    set( SIXTRL_DEFAULT_OPENCL_COMPILER_FLAGS
         "${SIXTRACKL_OPENCL_DEFAULT_COMPILER_FLAGS}" )
endif()

set( OPENCL_H_IN_FILE  "${CMAKE_CURRENT_SOURCE_DIR}/opencl.h.template" )
set( OPENCL_H_OUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/opencl.h" )
configure_file( ${OPENCL_H_IN_FILE} ${OPENCL_H_OUT_FILE} @ONLY )

set( OPENCL_HPP_IN_FILE  "${CMAKE_CURRENT_SOURCE_DIR}/opencl.hpp.template" )
set( OPENCL_HPP_OUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/opencl.hpp" )
configure_file( ${OPENCL_HPP_IN_FILE} ${OPENCL_HPP_OUT_FILE} @ONLY )

set( SIXTRL_OPENCL_GENERATED_C99_HEADERS opencl.h )
set( SIXTRL_OPENCL_GENERATED_CXX_HEADERS opencl.hpp )

set( SIXTRL_OPENCL_C99_HEADERS definitions.h )
set( SIXTRL_OPENCL_CXX_HEADERS )

# -----------------------------------------------------------------------------
# submodules

set( SIXTRL_OPENCL_MODULES )
set( SIXTRL_OPENCL_LINK_LIBRARIES )

add_subdirectory( control )
add_subdirectory( internal )
add_subdirectory( kernels )
add_subdirectory( track )

set( SIXTRL_MODULES ${SIXTRL_MODULES} ${SIXTRL_OPENCL_MODULES} PARENT_SCOPE )

set( SIXTRL_LINK_LIBRARIES ${SIXTRL_LINK_LIBRARIES}
   ${SIXTRL_OPENCL_LIBRARIES} PARENT_SCOPE )

# -----------------------------------------------------------------------------
# Install:

# set( OPENCL_H_INSTALL_FILE "${CXX_HEADERS_INSTALL_PATH}/${OPENCL_H_OUT_FILE}" )
# set( OPENCL_HPP_INSTALL_FILE "${CXX_HEADERS_INSTALL_PATH}/${OPENCL_HPP_OUT_FILE}" )
#
# set( CL_H_INSTALL_INFO
#     "set( SIXTRACKL_MIN_OPENCL_VERSION    ${SIXTRACKL_MIN_OPENCL_VERSION} )
#      set( SIXTRACKL_TARGET_OPENCL_VERSION ${SIXTRACKL_TARGET_OPENCL_VERSION} )
#      set( SIXTRL_OPENCL_CXX_HEADER_FILE \"${SIXTRL_OPENCL_CXX_HEADER_FILE}\" )
#      set( SIXTRL_OPENCL_CXX_INCLUDE_DIR \"${SIXTRL_OPENCL_CXX_INCLUDE_DIR}\" )
#      set( SIXTRL_OPENCL_CXX_HEADER_FILE_VERSION ${SIXTRL_OPENCL_CXX_HEADER_FILE_VERSION} )
#      set( SIXTRL_OPENCL_C99_HEADER_FILE \"${SIXTRL_OPENCL_C99_HEADER_FILE}\" )
#      set( SIXTRL_OPENCL_C99_INCLUDE_DIR \"${SIXTRL_OPENCL_C99_INCLUDE_DIR}\" )
#      set( SIXTRL_OPENCL_C99_HEADER_FILE_VERSION ${SIXTRL_OPENCL_C99_HEADER_FILE_VERSION} )
#      set( SIXTRL_OPENCL_PRINT_BUILD_REPORT ${SIXTRL_OPENCL_PRINT_BUILD_REPORT} )
#      set( SIXTRL_OPENCL_ENABLE_EXCEPTION_STR
#           ${SIXTRL_OPENCL_ENABLE_EXCEPTION_STR} )
#      set( SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG
#           ${SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG} ) " )
#
# install( CODE "
#          ${CL_H_INSTALL_INFO}
#          message( STATUS \"Generating: ${OPENCL_H_INSTALL_FILE}\" )
#          configure_file( \"${OPENCL_H_IN_FILE}\"
#                          \"${OPENCL_H_INSTALL_FILE}\" @ONLY )
#          message( STATUS \"Generating: ${OPENCL_HPP_INSTALL_FILE}\" )
#          configure_file( \"${OPENCL_HPP_IN_FILE}\"
#                          \"${OPENCL_HPP_INSTALL_FILE}\" @ONLY )" )
#
# if( SIXTRL_OPENCL_C99_HEADER_FILE )
#     install( FILES ${SIXTRL_OPENCL_C99_HEADER_FILE}
#              DESTINATION ${SIXTRL_OPENCL_C99_INSTALL_PREFIX} )
# endif()
#
# if( SIXTRL_OPENCL_CXX_HEADER_FILE )
#     install( FILES ${SIXTRL_OPENCL_CXX_HEADER_FILE}
#              DESTINATION ${SIXTRL_OPENCL_CXX_INSTALL_PREFIX} )
# endif()
