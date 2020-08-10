set( SIXTRL_BASE_BACKEND_INSTALL_PATH "${SIXTRL_BASE_INSTALL_PATH}/backend" )

# ------------------------------------------------------------------------------
# arch_dlib.h is a header file with macros needed to build the name of the
# backend plugin dynamic library names:

set( SIXTRACKL_BACKEND_DLIB_PREFIX_STR "${CMAKE_SHARED_LIBRARY_PREFIX}" )
set( SIXTRACKL_BACKEND_DLIB_SUFFIX_STR "${CMAKE_SHARED_LIBRARY_SUFFIX}" )
set( SIXTRACKL_BACKEND_DLIB_PATH_PREFIX "${CMAKE_BINARY_DIR}/sixtracklib/backends/" )

set( BACKEND_DLIB_H_IN  ${CMAKE_CURRENT_SOURCE_DIR}/dlib.h.in )
set( BACKEND_DLIB_H_OUT ${CMAKE_CURRENT_SOURCE_DIR}/dlib.h )
configure_file( ${BACKEND_DLIB_H_IN} ${BACKEND_DLIB_H_OUT} @ONLY )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( CXX_HEADERS definitions.h backend_obj.h dlib.h dlib_loader.h
    dlib_loader_posix.h backend.h backends_store.h node_backend.h )

set( CXX_SOURCES backend_obj.cpp dlib_loader.cpp dlib_loader_posix.cpp
                 backend.cpp backends_store.cpp node_backend.cpp )

add_library( sixtrack_base_backend OBJECT ${CXX_HEADERS} ${CXX_SOURCES} )

if( SIXTRL_BASE_LTO_SUPPORTED )
    set_target_properties( sixtrack_base_backend PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION TRUE )
endif()

target_include_directories( sixtrack_base_backend
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

target_compile_options( sixtrack_base_backend PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

set( SIXTRL_BASE_OBJECT_LIBRARY_SUBMODULES
   ${SIXTRL_BASE_OBJECT_LIBRARY_SUBMODULES}
   $<TARGET_OBJECTS:sixtrack_base_backend> PARENT_SCOPE )

target_link_libraries( sixtrack_base_backend PRIVATE toml11::toml11 )

# -----------------------------------------------------------------------------
# Handle install:

install( FILES ${CXX_HEADERS} DESTINATION ${SIXTRL_BASE_BACKEND_INSTALL_PATH} )

set( BACKEND_DLIB_H_OUT ${SIXTRL_BASE_BACKEND_INSTALL_PATH}/arch_dlib.h )
install( CODE
    "set( SIXTRACKL_BACKEND_DLIB_PREFIX_STR  \"${CMAKE_SHARED_LIBRARY_PREFIX}\" )
     set( SIXTRACKL_BACKEND_DLIB_SUFFIX_STR  \"${CMAKE_SHARED_LIBRARY_SUFFIX}\" )
     set( SIXTRACKL_BACKEND_DLIB_PATH_PREFIX \"${CMAKE_INSTALL_LIBDIR}/backends/\" )
    message( STATUS \"Generating: ${BACKEND_DLIB_H_OUT}\" )
    configure_file( \"${BACKEND_DLIB_H_IN}\" \"${BACKEND_DLIB_H_OUT}\" @ONLY )"
)
