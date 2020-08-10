message( STATUS "---- processing sixtracklib_base/CMakeLists.txt" )

set( CMAKE_POSITION_INDEPENDENT_CODE ON )
set( CMAKE_VISIBILITY_INLINES_HIDDEN TRUE )
set( CMAKE_CXX_VISIBILITY_PRESET hidden )
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

check_ipo_supported( RESULT SIXTRL_BASE_LTO_SUPPORTED )
set( SIXTRL_BASE_INSTALL_PATH ${CMAKE_INSTALL_INCLUDEDIR} )

set( SIXTRL_BASE_OBJECT_LIBRARY_SUBMODULES )
set( SIXTRL_BASE_INTERFACE_SUBMODULES )
set( SIXTRL_BASE_SUBMODULE_LINK_LIBRARIES )

# -----------------------------------------------------------------------------
# iterate over submodules:

add_subdirectory( backend )
# add_subdirectory( controller )
add_subdirectory( generated )
add_subdirectory( internal )
add_subdirectory( node )
# add_subdirectory( track )

# -----------------------------------------------------------------------------
# build library sixtrack_base:

set( SIXTRL_BASE_HEADERS definitions.h )
set( SIXTRL_BASE_SOURCES )

add_library( sixtrack_base SHARED
    ${SIXTRL_BASE_HEADERS} ${SIXTRL_BASE_SOURCES}
    ${SIXTRL_BASE_OBJECT_LIBRARY_SUBMODULES} )

set_target_properties( sixtrack_base PROPERTIES
    LINK_WHAT_YOU_USE TRUE SOVERSION 0.1.0 VERSION 0.1.0
    LINKER_LANGUAGE C )

target_include_directories( sixtrack_base
    PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

if( SIXTRL_BASE_INTERFACE_SUBMODULES )
    target_link_libraries( sixtrack_base
        PUBLIC ${SIXTRL_BASE_INTERFACE_SUBMODULES} )
endif()

if( SIXTRL_BASE_SUBMODULE_LINK_LIBRARIES )
    target_link_libraries( sixtrack_base
        PRIVATE ${SIXTRL_BASE_SUBMODULE_LINK_LIBRARIES} )
endif()

target_link_libraries( sixtrack_base PUBLIC toml11::toml11 )
target_link_libraries( sixtrack_base PUBLIC ${CMAKE_DL_LIBS} )

if( SIXTRL_BASE_LTO_SUPPORTED )
    set_target_properties( sixtrack_base PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION TRUE )
endif()

# -----------------------------------------------------------------------------
# generate the export.h header needed for declaring exported symbols in the
# dynamic library:

generate_export_header( sixtrack_base
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/export.h
    EXPORT_MACRO_NAME SIXTRL_BASE_EXPORT_API
    NO_EXPORT_MACRO_NAME SIXTRL_BASE_PRIVATE_API
    DEPRECATED_MACRO_NAME SIXTRL_BASE_DEPRECATED_API
    STATIC_DEFINE SIXTRL_BASE_IS_STATIC_BUILD
)

# ------------------------------------------------------------------------------
# handle install:

install( FILES ${CMAKE_CURRENT_SOURCE_DIR}/export.h
         DESTINATION ${SIXTRL_BASE_INSTALL_PATH} )

install( FILES ${SIXTRL_BASE_HEADERS}
         DESTINATION ${SIXTRL_BASE_INSTALL_PATH} )
