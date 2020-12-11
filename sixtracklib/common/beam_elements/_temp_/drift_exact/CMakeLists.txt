set( SIXTRL_COMMON_BE_DRIFT_EXACT_C99_HEADERS
    definitions.h
    drift_exact.h
    drift_exact_api.h
    drift_exact_cobjects_api.h
    track.h )

set( SIXTRL_COMMON_BE_DRIFT_EXACT_C99_SOURCES )

#add_subdirectory( sixtrack_common_be_drift_exact OBJECT
#   ${SIXTRL_COMMON_BE_DRIFT_EXACT_C99_HEADERS}
#   ${SIXTRL_COMMON_BE_DRIFT_EXACT_C99_SOURCES} )
#
# target_include_directories( sixtrack_common_be_drift_exact PRIVATE
#     $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
#     $<INSTALL_INTERFACE:include> )
#
# set_target_properties( sixtrack_common_be_drift_exact PROPERTIES
#     LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON
#     C_STANDARD 99 C_STANDARD_REQUIRED ON )
#
# target_compile_options( sixtrack_common_be_drift_exact PRIVATE
#     ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# -----------------------------------------------------------------------------
# cxx:

set( SIXTRL_COMMON_BE_DRIFT_EXACT_CXX_HEADERS
     drift_exact.hpp drift_exact_convert.hpp )

set( SIXTRL_COMMON_BE_DRIFT_EXACT_CXX_SOURCES
     drift_exact.cpp drift_exact_cobjects_api.cpp )

add_library( sixtrack_common_belems_drift_exact_cxx OBJECT
  ${SIXTRL_COMMON_BE_DRIFT_EXACT_CXX_HEADERS}
  ${SIXTRL_COMMON_BE_DRIFT_EXACT_C99_HEADERS}
  ${SIXTRL_COMMON_BE_DRIFT_EXACT_CXX_SOURCES} )

target_include_directories( sixtrack_common_belems_drift_exact_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_belems_drift_exact_cxx PROPERTIES
    LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_belems_drift_exact_cxx PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# =============================================================================
# Install:

if( SIXTRL_COMMON_BE_DRIFT_EXACT_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_DRIFT_EXACT_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_BE_C99_INSTALL_PREFIX}/drift_exact" )
endif()

if( SIXTRACKLIB_ENABLE_CXX AND SIXTRL_COMMON_BE_DRIFT_EXACT_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_DRIFT_EXACT_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_BE_C99_INSTALL_PREFIX}/drift_exact" )
endif()
