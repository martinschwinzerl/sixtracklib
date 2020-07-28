message( STATUS "---- processing sixtracklib/base" )

set( CMAKE_POSITION_INDEPENDENT_CODE ON )
set( CMAKE_VISIBILITY_INLINES_HIDDEN TRUE )
set( CMAKE_CXX_VISIBILITY_PRESET hidden )
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( SIXTRL_BASE_OBJ_LIBRARIES )
set( SIXTRL_BASE_HEADERS )
set( SIXTRL_BASE_SOURCES )
set( SIXTRL_BASE_INSTALL_PATH ${CMAKE_INSTALL_INCLUDEDIR}/base )

add_subdirectory( architecture )
# add_subdirectory( controller )
add_subdirectory( generated )
add_subdirectory( internal )
add_subdirectory( node )
# add_subdirectory( track )

set( SIXTRL_BASE_HEADERS ${SIXTRL_BASE_HEADERS} definitions.h )

add_library( sixtrack_base SHARED
    ${SIXTRL_BASE_HEADERS} ${SIXTRL_BASE_SOURCES}
    ${SIXTRL_BASE_OBJ_LIBRARIES} )

generate_export_header( sixtrack_base
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/export.h
    EXPORT_MACRO_NAME SIXTRL_BASE_EXPORT_API
    NO_EXPORT_MACRO_NAME SIXTRL_BASE_PRIVATE_API
    DEPRECATED_MACRO_NAME SIXTRL_BASE_DEPRECATED_API
    STATIC_DEFINE SIXTRL_BASE_IS_STATIC_BUILD
)

install( FILES ${CMAKE_CURRENT_SOURCE_DIR}/export.h
         DESTINATION ${SIXTRL_BASE_INSTALL_PATH} )

install( FILES ${SIXTRL_BASE_HEADERS}
         DESTINATION ${SIXTRL_BASE_INSTALL_PATH} )
