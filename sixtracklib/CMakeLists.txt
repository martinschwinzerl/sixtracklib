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

set( CMAKE_POSITION_INDEPENDENT_CODE ON )
set( CMAKE_VISIBILITY_INLINES_HIDDEN TRUE )
set( CMAKE_CXX_VISIBILITY_PRESET hidden )
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

check_ipo_supported( RESULT SIXTRL_LTO_SUPPORTED )

# ------------------------------------------------------------------------------
# Collect submodules and link_libriaries in these two lists:

set( SIXTRACKLIB_SUBMODULES )
set( SIXTRACKLIB_SUBMODULES_LINK_LIBRARIES )

# prepare install path for the "main" sixtracklib
set( SIXTRL_INSTALL_PATH "${CMAKE_INSTALL_INCLUDEDIR}/sixtracklib" )

# ------------------------------------------------------------------------------
# iterate over the submodules

add_subdirectory( backends )

# ------------------------------------------------------------------------------
# build the library

set( SIXTRACKLIB_HEADERS )
set( SIXTRACKLIB_SOURCES )

add_library( sixtrack SHARED
    ${SIXTRACKLIB_HEADERS} ${SIXTRACKLIB_SOURCES} ${SIXTRACKLIB_SUBMODULES} )

set_target_properties( sixtrack PROPERTIES
    LINK_WHAT_YOU_USE TRUE SOVERSION 0.1.0 VERSION 0.1.0 )

if( SIXTRL_LTO_SUPPORTED )
    set_target_properties( sixtrack PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION TRUE )
endif()

target_link_libraries( sixtrack PUBLIC sixtrack_base )

target_include_directories( sixtrack
    PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

if( SIXTRACKLIB_SUBMODULES_LINK_LIBRARIES )
    target_link_libraries( sixtrack
        PRIVATE ${SIXTRACKLIB_SUBMODULES_LINK_LIBRARIES} )
endif()

# ------------------------------------------------------------------------------
# prepare the header with API export macros

generate_export_header( sixtrack
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/export.h
    EXPORT_MACRO_NAME SIXTRL_EXPORT_API
    NO_EXPORT_MACRO_NAME SIXTRL_PRIVATE_API
    DEPRECATED_MACRO_NAME SIXTRL_DEPRECATED_API
    STATIC_DEFINE SIXTRL_IS_STATIC_BUILD
)

# ------------------------------------------------------------------------------
# handle install:

if( SIXTRACKLIB_HEADERS )
    install( FILES ${SIXTRACKLIB_HEADERS} DESTINATION ${SIXTRL_INSTALL_PATH} )
endif()

install( FILES ${CMAKE_CURRENT_SOURCE_DIR}/export.h
         DESTINATION ${SIXTRL_INSTALL_PATH} )
