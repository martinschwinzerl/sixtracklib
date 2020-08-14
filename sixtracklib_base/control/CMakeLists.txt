# processing sixtracklib_base/control/CMakeLists.txt
set( C99_HEADERS )
set( C99_SOURCES )

set( CXX_HEADERS definitions.h context.h )
set( CXX_SOURCES context.cpp )
add_library( sixtrack_base_control OBJECT ${CXX_HEADERS} ${CXX_SOURCES} )

target_include_directories( sixtrack_base_control
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

target_compile_options( sixtrack_base_control PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

if( SIXTRL_BASE_LTO_SUPPORTED )
    set_target_properties( sixtrack_base_control PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION TRUE )
endif()

set( SIXTRL_BASE_OBJECT_LIBRARY_SUBMODULES
   ${SIXTRL_BASE_OBJECT_LIBRARY_SUBMODULES}
   $<TARGET_OBJECTS:sixtrack_base_control> PARENT_SCOPE )

# -----------------------------------------------------------------------------
# handle installation

if( C99_HEADERS )
    install( FILES ${C99_HEADERS}
             DESTINATION ${SIXTRL_BASE_INSTALL_PATH}/control )
 endif()

if( CXX_HEADERS )
    install( FILES ${CXX_HEADERS}
             DESTINATION ${SIXTRL_BASE_INSTALL_PATH}/control )
 endif()
