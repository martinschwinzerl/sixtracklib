message( STATUS "---- processing sixtracklib/backends/cuda/CMakeLists.txt" )

set( BACKENDS_CUDA_INSTALL_PATH "${SIXTRL_BACKENDS_INSTALL_PATH}/cuda" )
set( PLUGIN_HEADER_INSTALL_PATH ${BACKENDS_CUDA_INSTALL_PATH} )

set( SIXTRL_CUDA_PLUGIN_SOVERSION ${PROJECT_VERSION} )
set( SIXTRL_CUDA_PLUGIN_VERSION
        "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}" )

set( SIXTRL_CUDA_ALLOWED_DEVICES_ENV_VARIABLE "SIXTRACKLIB_DEVICES" )


if( CUDAToolkit_FOUND AND SIXTRACKL_ENABLE_CUDA )
    set( SIXTRL_CUDA_PLUGIN_BUILT 1 )
    set( SIXTRL_CUDA_PLUGIN_PATH_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/" )
    set( SIXTRL_CUDA_PLUGIN_NAME "${CMAKE_SHARED_LIBRARY_PREFIX}sixtrack_cuda" )
    set( SIXTRL_CUDA_PLUGIN_FILENAME
        "${SIXTRL_CUDA_PLUGIN_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}" )
    set( SIXTRL_CUDA_PLUGIN_DEFAULT_KERNEL_DIR
        "${CMAKE_CURRENT_SOURCE_DIR}/kernels/" )
    set( SIXTRL_CUDA_PLUGIN_EXCEPTION_ON_ERROR 1 )
    set( PLUGIN_OBJECT_LIBRARY_SUBMODULES )
    set( PLUGIN_INTERFACE_SUBMODULES )

    add_subdirectory( plugin )
    add_subdirectory( kernels )

    set( PLUGIN_SOURCES )
    set( PLUGIN_HEADERS definitions.h plugin.h )

    add_library( sixtrack_cuda MODULE
        ${PLUGIN_HEADERS} ${PLUGIN_OBJECT_LIBRARY_SUBMODULES} )

    if( PLUGIN_INTERFACE_SUBMODULES )
        target_link_libraries(
            sixtrack_cuda PUBLIC ${PLUGIN_INTERFACE_SUBMODULES} )
    endif()

    set_target_properties( sixtrack_cuda PROPERTIES
        LINK_WHAT_YOU_USE TRUE
        SOVERSION "${SIXTRL_CUDA_PLUGIN_SOVERSION}"
        VERSION "${SIXTRL_CUDA_PLUGIN_VERSION}"
        LINKER_LANGUAGE C )

    if( SIXTRL_LTO_SUPPORTED )
        set_target_properties( sixtrack_cuda PROPERTIES
            INTERPROCEDURAL_OPTIMIZATION TRUE )
    endif()

    target_link_libraries( sixtrack_cuda PRIVATE sixtrack_base )
    target_link_libraries( sixtrack_cuda PRIVATE CUDA::nvrtc  )

else()
    set( SIXTRL_CUDA_PLUGIN_BUILT 0 )
    set( SIXTRL_CUDA_PLUGIN_EXCEPTION_ON_ERROR 0 )
endif()

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/dlib.h.in
                ${CMAKE_CURRENT_SOURCE_DIR}/dlib.h @ONLY )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( SIXTRL_BACKENDS_CUDA_HEADERS definitions.h dlib.h backend.h )
set( SIXTRL_BACKENDS_CUDA_SOURCES backend.cpp )

add_library( sixtrack_backends_cuda OBJECT
    ${SIXTRL_BACKENDS_CUDA_HEADERS} ${SIXTRL_BACKENDS_CUDA_SOURCES} )

target_link_libraries( sixtrack_backends_cuda PRIVATE sixtrack_base )

target_include_directories( sixtrack_backends_cuda
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

set( SIXTRACKLIB_BACKENDS_SUBMODULES ${SIXTRACKLIB_BACKENDS_SUBMODULES}
     $<TARGET_OBJECTS:sixtrack_backends_cuda> PARENT_SCOPE )

# ------------------------------------------------------------------------------
# handle install

install( CODE
    "set( SIXTRL_CUDA_PLUGIN_BUILT ${SIXTRL_CUDA_PLUGIN_BUILT} )
     set( SIXTRL_CUDA_PLUGIN_SOVERSION \"${PROJECT_VERSION}\" )
     set( SIXTRL_CUDA_PLUGIN_VERSION \"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}\" )
     set( SIXTRL_CUDA_PLUGIN_PATH_PREFIX \"${BACKENDS_CUDA_INSTALL_PATH}/\" )
     set( SIXTRL_CUDA_PLUGIN_NAME \"${CMAKE_SHARED_LIBRARY_PREFIX}sixtrack_cuda\" )
     set( SIXTRL_CUDA_PLUGIN_FILENAME \"${SIXTRL_CUDA_PLUGIN_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}\" )
     set( SIXTRL_CUDA_PLUGIN_DEFAULT_KERNEL_DIR \"${CMAKE_CURRENT_SOURCE_DIR}/kernels/\" )
     set( SIXTRL_CUDA_PLUGIN_EXCEPTION_ON_ERROR ${SIXTRL_CUDA_PLUGIN_EXCEPTION_ON_ERROR} )
     message( STATUS \"Generating ${BACKENDS_CUDA_INSTALL_PATH}/dlib.h ...\" )
     configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/dlib.h.in
                     ${BACKENDS_CUDA_INSTALL_PATH}/dlib.h @ONLY )"
)

if( SIXTRL_BACKENDS_CUDA_HEADERS )
    install( FILES ${SIXTRL_BACKENDS_CUDA_HEADERS}
             DESTINATION ${BACKENDS_CUDA_INSTALL_PATH} )
endif()

if( SIXTRL_CUDA_PLUGIN_BUILT AND ${SIXTRL_CUDA_PLUGIN_BUILT} EQUAL 1 )

endif()
