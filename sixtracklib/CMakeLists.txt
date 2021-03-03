# sixtracklib/sixtracklib
#
# Authors: R. De Maria, G. Iadarola, D. Pellegrini, H. Jasim, M. Schwinzerl
#
# Copyright 2018 CERN. This software is distributed under the terms of the GNU
# Lesser General Public License version 2.1, copied verbatim in the file
#`COPYING''.
#
# In applying this licence, CERN does not waive the privileges and immunities
# granted to it by virtue of its status as an Intergovernmental Organization or
# submit itself to any jurisdiction.

message( STATUS "---- processing sixtracklib/CMakeLists.txt" )

set( SIXTRL_C99_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/include/sixtracklib" )
set( SIXTRL_CXX_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/include/sixtracklib" )

# ==============================================================================
# testlib:

add_subdirectory( testlib )

# ==============================================================================
# sixtracklib:

set( SIXTRL_C99_HEADERS sixtracklib.h testlib.h )
set( SIXTRL_CXX_HEADERS sixtracklib.hpp testlib.hpp )

set( SIXTRL_MODULES )
set( SIXTRL_LINK_LIBRARIES )

add_subdirectory( common )

if( SIXTRACKL_ENABLE_OPENCL )
    add_subdirectory( opencl )
endif()

if( SIXTRACKL_ENABLE_CUDA )
#     add_subdirectory( cuda )
endif()

# ------------------------------------------------------------------------------
# shared sixtracklib :

set( SIXTRL_LINK_LIBRARIES ${SIXTRL_LINK_LIBRARIES} m )

add_library( sixtrack SHARED
             ${SIXTRL_C99_HEADERS} ${SIXTRL_CXX_HEADERS}
             ${SIXTRL_MODULES} )

if( SIXTRL_LINK_LIBRARIES )
    target_link_libraries( sixtrack ${SIXTRL_LINK_LIBRARIES} )
endif()

target_include_directories(
    sixtrack PUBLIC $<INSTALL_INTERFACE:include>
             PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

if( TARGET sixtrack_opencl )
    target_include_directories( sixtrack
        PUBLIC $<BUILD_INTERFACE:${SIXTRL_OPENCL_INCLUDE_DIRS}> )
endif()

# if( TARGET sixtrack_cuda_host )
#     target_include_directories( sixtrack
#         PUBLIC $<BUILD_INTERFACE:${SIXTRACKL_CUDA_INCLUDE_DIRS}> )
# endif()

# if( TARGET sixtrack_cuda_device )
#     set_target_properties( sixtrack PROPERTIES CUDA_RESOLVE_DEVICE_SYMBOLS ON )
# endif()

set_target_properties( sixtrack PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON C_STANDARD 99
    DEBUG_POSTFIX d C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack PRIVATE
    ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_C99_AUTOVEC_FLAGS} )

# ------------------------------------------------------------------------------
message( STATUS "****" )
message( STATUS "****" )
message( STATUS "SIXTRL_MODULES:" )
message( STATUS "${SIXTRL_MODULES}" )
message( STATUS "****" )
message( STATUS "****" )


add_library( sixtrack_static STATIC
              ${SIXTRL_C99_HEADERS} ${SIXTRL_CXX_HEADERS} ${SIXTRL_MODULES} )

if( SIXTRL_LINK_LIBRARIES )
    target_link_libraries( sixtrack_static ${SIXTRL_LINK_LIBRARIES} )
endif()

target_include_directories( sixtrack_static
    PUBLIC $<INSTALL_INTERFACE:include>
    PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

if( TARGET sixtrack_opencl )
    target_include_directories( sixtrack_static
        PUBLIC $<BUILD_INTERFACE:${SIXTRL_OPENCL_INCLUDE_DIRS}> )
endif()

# if( TARGET sixtrack_cuda_host )
#     target_include_directories( sixtrack_static
#         PUBLIC $<BUILD_INTERFACE:${SIXTRACKL_CUDA_INCLUDE_DIRS}> )
# endif()

# if( TARGET sixtrack_cuda_device )
#     set_target_properties( sixtrack_static PROPERTIES
#               CUDA_RESOLVE_DEVICE_SYMBOLS ON )
# endif()

set_target_properties( sixtrack_static PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON C_STANDARD 99
    DEBUG_POSTFIX d C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_static PRIVATE
    ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_C99_AUTOVEC_FLAGS} )

# ------------------------------------------------------------------------------
# install :

install( TARGETS sixtrack
         EXPORT  SixTracklib-targets
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib )

install( EXPORT SixTracklib-targets
         FILE   SixTracklibTargets.cmake
         NAMESPACE SixTracklib::
         DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake )

if( SIXTRL_C99_HEADERS )
    install( FILES ${SIXTRL_C99_HEADERS}
             DESTINATION ${SIXTRL_C99_INSTALL_PREFIX} )
endif()

if( SIXTRL_CXX_HEADERS )
    install( FILES ${SIXTRL_CXX_HEADERS}
             DESTINATION ${SIXTRL_CXX_INSTALL_PREFIX} )
endif()
