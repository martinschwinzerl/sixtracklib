# --------------------------------------------------------------------------
# processing sixtracklib/common/beam_elements/drift/CMakeLists.txt

set( SIXTRL_COMMON_BE_DRIFT_CXX_HEADERS
     drift_traits.hpp
     drift_data.hpp
     drift.hpp
     drift_exact_data.hpp
     drift_exact.hpp
     track.hpp
)

set( SIXTRL_COMMON_BE_DRIFT_CXX_SOURCES )


set( SIXTRL_COMMON_BE_DRIFT_C99_HEADERS
     drift.h
     drift_exact.h
     drift_api.h
     drift_exact_api.h
     track.h
)

set( SIXTRL_COMMON_BE_DRIFT_C99_SOURCES
     drift_api.c
     drift_exact_api.c )


add_library( sixtrack_common_be_drift OBJECT
    ${SIXTRL_COMMON_BE_DRIFT_C99_HEADERS}
    ${SIXTRL_COMMON_BE_DRIFT_CXX_HEADERS}
    ${SIXTRL_COMMON_BE_DRIFT_C99_SOURCES}
)

target_include_directories( sixtrack_common_be_drift PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_be_drift PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON
    C_STANDARD 99 C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_be_drift PRIVATE
    ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixtrack_common_be_drift as a module for sixtracklib:

set(  SIXTRACKL_LIBRARY_MODULES ${SIXTRACKL_LIBRARY_MODULES}
    $<TARGET_OBJECTS:sixtrack_common_be_drift> CACHE INTERNAL "" FORCE )

# =======================================================================
# Install

if( SIXTRL_COMMON_BE_DRIFT_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_DRIFT_C99_HEADERS}
             DESTINATION "${BE_INSTALL_PREFIX}/drift" )
endif()

if( SIXTRL_COMMON_BE_DRIFT_CXX_HEADERS AND SIXTRACKL_ENABLE_CXX )
    install( FILES ${SIXTRL_COMMON_BE_DRIFT_CXX_HEADERS}
             DESTINATION "${BE_INSTALL_PREFIX}/drift" )
endif()

#end:
