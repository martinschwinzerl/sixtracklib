set( SIXTRL_COMMON_BE_DRIFT_C99_HEADERS
    definitions.h drift.h storage_cobjects.h )

set( SIXTRL_COMMON_BE_DRIFT_C99_SOURCES )

#add_subdirectory( sixtrack_common_be_drift OBJECT
#   ${SIXTRL_COMMON_BE_DRIFT_C99_HEADERS}
#   ${SIXTRL_COMMON_BE_DRIFT_C99_SOURCES} )
#
# target_include_directories( sixtrack_common_be_drift PRIVATE
#     $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
#     $<INSTALL_INTERFACE:include> )
#
# set_target_properties( sixtrack_common_be_drift PROPERTIES
#     LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON
#     C_STANDARD 99 C_STANDARD_REQUIRED ON )
#
# target_compile_options( sixtrack_common_be_drift PRIVATE
#     ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# -----------------------------------------------------------------------------
# cxx:

set( SIXTRL_COMMON_BE_DRIFT_CXX_HEADERS
     drift_data.hpp drift.hpp  )

set( SIXTRL_COMMON_BE_DRIFT_CXX_SOURCES
     storage_cobjects.cpp )

add_library( sixtrack_common_belems_drift_cxx OBJECT
  ${SIXTRL_COMMON_BE_DRIFT_CXX_HEADERS}
  ${SIXTRL_COMMON_BE_DRIFT_C99_HEADERS}
  ${SIXTRL_COMMON_BE_DRIFT_CXX_SOURCES} )

target_include_directories( sixtrack_common_belems_drift_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_belems_drift_cxx PROPERTIES
    LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_belems_drift_cxx PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# =============================================================================
# Install:

if( SIXTRL_COMMON_BE_DRIFT_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_DRIFT_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_BE_C99_INSTALL_PREFIX}/drift" )
endif()

if( SIXTRACKLIB_ENABLE_CXX AND SIXTRL_COMMON_BE_DRIFT_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_DRIFT_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_BE_C99_INSTALL_PREFIX}/drift" )
endif()
