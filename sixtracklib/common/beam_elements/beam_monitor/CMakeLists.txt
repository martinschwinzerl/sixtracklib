set( SIXTRL_COMMON_BE_BEAM_MONITOR_C99_HEADERS
    definitions.h beam_monitor.h beam_monitor_api.h beam_monitor_cobjects_api.h
    track.h )

set( SIXTRL_COMMON_BE_BEAM_MONITOR_C99_SOURCES )

#add_subdirectory( sixtrack_common_be_beam_monitor OBJECT
#   ${SIXTRL_COMMON_BE_BEAM_MONITOR_C99_HEADERS}
#   ${SIXTRL_COMMON_BE_BEAM_MONITOR_C99_SOURCES} )
#
# target_include_directories( sixtrack_common_be_beam_monitor PRIVATE
#     $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
#     $<INSTALL_INTERFACE:include> )
#
# set_target_properties( sixtrack_common_be_beam_monitor PROPERTIES
#     LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON
#     C_STANDARD 99 C_STANDARD_REQUIRED ON )
#
# target_compile_options( sixtrack_common_be_beam_monitor PRIVATE
#     ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# -----------------------------------------------------------------------------
# cxx:

set( SIXTRL_COMMON_BE_BEAM_MONITOR_CXX_HEADERS
     beam_monitor_data.hpp beam_monitor_data_api.hpp beam_monitor_data_cobjects_api.hpp
     beam_monitor.hpp convert_cobjects.hpp )

set( SIXTRL_COMMON_BE_BEAM_MONITOR_CXX_SOURCES
     beam_monitor.cpp beam_monitor_cobjects_api.cpp )

add_library( sixtrack_common_belems_beam_monitor_cxx OBJECT
  ${SIXTRL_COMMON_BE_BEAM_MONITOR_CXX_HEADERS}
  ${SIXTRL_COMMON_BE_BEAM_MONITOR_C99_HEADERS}
  ${SIXTRL_COMMON_BE_BEAM_MONITOR_CXX_SOURCES} )

target_include_directories( sixtrack_common_belems_beam_monitor_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_belems_beam_monitor_cxx PROPERTIES
    LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_belems_beam_monitor_cxx PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# =============================================================================
# Install:

if( SIXTRL_COMMON_BE_BEAM_MONITOR_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_BEAM_MONITOR_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_BE_C99_INSTALL_PREFIX}/beam_monitor" )
endif()

if( SIXTRACKLIB_ENABLE_CXX AND SIXTRL_COMMON_BE_BEAM_MONITOR_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_BEAM_MONITOR_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_BE_C99_INSTALL_PREFIX}/beam_monitor" )
endif()
