set( CXX_HEADERS definitions.h arch_obj.h architecture.h architectures_store.h )
set( CXX_SOURCES arch_obj.cpp architecture.cpp architectures_store.cpp )
add_library( sixtrack_base_arch OBJECT ${CXX_HEADERS} ${CXX_SOURCES} )

target_include_directories( sixtrack_base_arch
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

target_compile_options( sixtrack_base_arch PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

set( SIXTRL_BASE_OBJ_LIBRARIES ${SIXTRL_BASE_OBJ_LIBRARIES}
     $<TARGET_OBJECTS:sixtrack_base_arch> PARENT_SCOPE )

install( FILES ${CXX_HEADERS}
         DESTINATION ${SIXTRL_BASE_INSTALL_PATH}/architecture )
