# ----------------------------------------------------------------------------
# sixtracklib/common/internal/CMakeLists.txt

set( SIXTRL_COMMON_INTERNAL_C99_HEADERS
    beam_elements_defines.h
    beam_elements_undef.h
    buffer_garbage_defines.h
    buffer_garbage_undef.h
    buffer_main_defines.h
    buffer_main_undef.h
    buffer_object_defines.h
    buffer_object_undef.h
    namespace_defines.h
    namespace_undef.h
    objects_type_id.h
    particles_defines.h
    particles_undef.h
    tools.h
)

# ------------------------------------------------------------------------------

set( SIXTRL_COMMON_INTERNAL_CXX_HEADERS track_job_base.h )
set( SIXTRL_COMMON_INTERNAL_CXX_SOURCES
     track_job_base.cpp
     track_job.cpp
     track_job_cpu.cpp
)

add_library( sixtrack_common_internal_cxx OBJECT
    ${SIXTRL_COMMON_INTERNAL_CXX_HEADERS}
    ${SIXTRL_COMMON_INTERNAL_CXX_SOURCES}
)

target_include_directories( sixtrack_common_internal_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_internal_cxx PROPERTIES
    LINKER_LANGUAGE C CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE ON )

target_compile_options( sixtrack_common_internal_cxx PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixtrack_common_internal as a module for sixtracklib:

set(  SIXTRACKL_LIBRARY_MODULES ${SIXTRACKL_LIBRARY_MODULES}
    $<TARGET_OBJECTS:sixtrack_common_internal_cxx> CACHE INTERNAL "" FORCE )

# -----------------------------------------------------------------------------
# install :

if( SIXTRL_COMMON_INTERNAL_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_INTERNAL_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_C99_INSTALL_PREFIX}/internal" )
endif()

if( SIXTRACKL_ENABLE_CXX AND SIXTRL_COMMON_INTERNAL_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_INTERNAL_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_CXX_INSTALL_PREFIX}/internal" )
endif()

#end: sixtracklib/common/buffer/CMakeLists.txt
