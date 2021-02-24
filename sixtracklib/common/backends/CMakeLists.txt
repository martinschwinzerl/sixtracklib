set( SIXTRL_COMMON_BACKENDS_CXX_HEADERS dlib_loader.h dlib_loader_posix.h )
set( SIXTRL_COMMON_BACKENDS_CXX_SOURCES
    dlib_loader.cpp dlib_loader_posix.cpp backends.cpp )

set( SIXTRL_COMMON_BACKENDS_C99_SOURCES )
set( SIXTRL_COMMON_BACKENDS_C99_HEADERS definitions.h backends.h
    definitions_cuda.h definitions_opencl.h compiler_compability.h
    helper_methods.h )

add_library( sixtrack_backends_cxx OBJECT
             ${SIXTRL_COMMON_BACKENDS_CXX_HEADERS}
             ${SIXTRL_COMMON_BACKENDS_C99_HEADERS}
             ${SIXTRL_COMMON_BACKENDS_CXX_SOURCES} )

target_include_directories( sixtrack_backends_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_backends_cxx PROPERTIES CXX_STANDARD 11
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_backends_cxx
    PRIVATE ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixtrack_common_internal as a module for sixtracklib:

set(  SIXTRACKL_LIBRARY_MODULES ${SIXTRACKL_LIBRARY_MODULES}
#     $<TARGET_OBJECTS:sixtrack_common_control_c99>
    $<TARGET_OBJECTS:sixtrack_backends_cxx> CACHE INTERNAL "" FORCE )

set( SIXTRACKL_LINK_LIBRARIES ${SIXTRACKL_LINK_LIBRARIES} ${CMAKE_DL_LIBS}
     CACHE INTERNAL "" FORCE )

# -----------------------------------------------------------------------------
# install :

if( SIXTRL_COMMON_BACKENDS_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_CONTROL_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_C99_INSTALL_PREFIX}/backends" )
endif()

if( SIXTACKL_ENABLE_CXX AND SIXTRL_COMMON_BACKENDS_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_CONTROL_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_C99_INSTALL_PREFIX}/backends" )
endif()
