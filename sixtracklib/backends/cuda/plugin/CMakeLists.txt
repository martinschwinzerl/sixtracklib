set( SIXTRL_CUDA_PLUGIN_HEADERS init_finish.h cuda_tools.h node.h device.h )
set( SIXTRL_CUDA_PLUGIN_SOURCES init_finish.cpp node.cpp device.cpp )

add_library( sixtrack_cuda_plugin OBJECT
    ${SIXTRL_CUDA_PLUGIN_HEADERS} ${SIXTRL_CUDA_PLUGIN_SOURCES} )

target_include_directories( sixtrack_cuda_plugin
    PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

if( SIXTRL_LTO_SUPPORTED )
    set_target_properties( sixtrack_cuda_plugin PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION TRUE )
endif()

target_link_libraries( sixtrack_cuda_plugin PRIVATE CUDA::nvrtc )

set( PLUGIN_OBJECT_LIBRARY_SUBMODULES ${PLUGIN_OBJECT_LIBRARY_SUBMODULES}
     $<TARGET_OBJECTS:sixtrack_cuda_plugin> PARENT_SCOPE )

# ------------------------------------------------------------------------------
# handle install

if( SIXTRL_CUDA_PLUGIN_HEADERS )
    install( FILES ${SIXTRL_CUDA_PLUGIN_HEADERS}
             DESTINATION ${BACKENDS_CUDA_INSTALL_PATH} )
endif()
