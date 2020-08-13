set( CXX_HEADERS definitions.h node_id.h node_info.h )
set( CXX_SOURCES node_id.cpp node_info.cpp )
add_library( sixtrack_base_node OBJECT ${CXX_HEADERS} ${CXX_SOURCES} )

target_include_directories( sixtrack_base_node
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

target_compile_options( sixtrack_base_node PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

if( SIXTRL_BASE_LTO_SUPPORTED )
    set_target_properties( sixtrack_base_node PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION TRUE )
endif()

set( SIXTRL_BASE_OBJECT_LIBRARY_SUBMODULES
   ${SIXTRL_BASE_OBJECT_LIBRARY_SUBMODULES}
   $<TARGET_OBJECTS:sixtrack_base_node> PARENT_SCOPE )

install( FILES ${CXX_HEADERS} DESTINATION ${SIXTRL_BASE_INSTALL_PATH}/node )
