set( CXX_HEADERS definitions.h node_id.h node_info.h tools.h )
set( CXX_SOURCES node_id.cpp node_info.cpp tools.cpp )
add_library( sixtrack_base_node OBJECT ${CXX_HEADERS} ${CXX_SOURCES} )

target_include_directories( sixtrack_base_node
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

target_compile_options( sixtrack_base_node PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

set( SIXTRL_BASE_OBJ_LIBRARIES ${SIXTRL_BASE_OBJ_LIBRARIES}
     $<TARGET_OBJECTS:sixtrack_base_node> PARENT_SCOPE )

install( FILES ${CXX_HEADERS} DESTINATION ${SIXTRL_BASE_INSTALL_PATH}/node )


