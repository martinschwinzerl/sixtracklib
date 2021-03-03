# ----------------------------------------------------------------------------
# sixtracklib/common/beam_elements/CMakeLists.txt

set( SIXTRL_COMMON_CXX_INSTALL_PREFIX
   "${SIXTRL_COMMON_CXX_INSTALL_PREFIX}/beam_elements" )

set( SIXTRL_COMMON_CXX_INSTALL_PREFIX
   "${SIXTRL_COMMON_CXX_INSTALL_PREFIX}/beam_elements" )

set( SIXTRL_COMMON_BEAM_ELEMENTS_LINK_LIBRARIES )
set( SIXTRL_COMMON_BEAM_ELEMENTS_MODULES )

add_subdirectory( beamfields )
add_subdirectory( cavity )
add_subdirectory( dipedge )
add_subdirectory( drift )
add_subdirectory( end_tracking )
add_subdirectory( limit )
add_subdirectory( monitor )
add_subdirectory( multipole )
add_subdirectory( rf_multipole )
add_subdirectory( srotation )
add_subdirectory( xy_shift )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( SIXTRL_COMMON_BEAM_ELEMS_CXX_HEADERS )
set( SIXTRL_COMMON_BEAM_ELEMS_CXX_SOURCES )

set( SIXTRL_COMMON_BEAM_ELEMS_C99_HEADERS definitions.h beam_elements_undef.h
    beam_elements.h all_beam_elements.h all_tracking_maps.h )

set( SIXTRL_COMMON_BEAM_ELEMS_C99_SOURCES beam_elements.c )

if( SIXTRACKL_ENABLE_DEMOTRACK )
    set( SIXTRL_COMMON_BEAM_ELEMS_C99_HEADERS
       ${SIXTRL_COMMON_BEAM_ELEMS_C99_HEADERS} demotrack.h )
    set( SIXTRL_COMMON_BEAM_ELEMS_CXX_SOURCES demotrack.cpp )
endif()

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( sixtrack_common_beam_elems_c99 OBJECT
    ${SIXTRL_COMMON_BEAM_ELEMS_C99_HEADERS}
    ${SIXTRL_COMMON_BEAM_ELEMS_CXX_HEADERS}
    ${SIXTRL_COMMON_BEAM_ELEMS_C99_SOURCES} )

target_include_directories( sixtrack_common_beam_elems_c99 PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_beam_elems_c99 PROPERTIES
    POSITION_INDEPENDENT_CODE ON LINKER_LANGUAGE C C_STANDARD 99
    C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_beam_elems_c99 PRIVATE
    ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_C99_AUTOVEC_FLAGS} )

set( SIXTRL_COMMON_BEAM_ELEMENTS_MODULES ${SIXTRL_COMMON_BEAM_ELEMENTS_MODULES}
   $<TARGET_OBJECTS:sixtrack_common_beam_elems_c99> )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( SIXTRL_COMMON_BEAM_ELEMS_CXX_SOURCES )
    add_library( sixtrack_common_beam_elems_cxx OBJECT
        ${SIXTRL_COMMON_BEAM_ELEMS_CXX_HEADERS}
        ${SIXTRL_COMMON_BEAM_ELEMS_C99_HEADERS}
        ${SIXTRL_COMMON_BEAM_ELEMS_CXX_SOURCES} )

    target_include_directories( sixtrack_common_beam_elems_cxx PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

    set_target_properties( sixtrack_common_beam_elems_cxx PROPERTIES
        POSITION_INDEPENDENT_CODE ON LINKER_LANGUAGE C CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON )

    target_compile_options( sixtrack_common_beam_elems_cxx PRIVATE
        ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
        ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

    set( SIXTRL_COMMON_BEAM_ELEMENTS_MODULES
         ${SIXTRL_COMMON_BEAM_ELEMENTS_MODULES}
         $<TARGET_OBJECTS:sixtrack_common_beam_elems_cxx> )
endif()

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( SIXTRL_COMMON_LINK_LIBRARIES ${SIXTRL_COMMON_LINK_LIBRARIES}
   ${SIXTRL_COMMON_BEAM_ELEMENTS_LINK_LIBRARIES} PARENT_SCOPE )

set( SIXTRL_COMMON_MODULES ${SIXTRL_COMMON_MODULES}
   ${SIXTRL_COMMON_BEAM_ELEMENTS_MODULES} PARENT_SCOPE )

# ==============================================================================
# Handle install:

if( SIXTRL_COMMON_BEAM_ELEMS_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_INTERNAL_C99_HEADERS}
             DESTINATION ${SIXTRL_COMMON_C99_INSTALL_PREFIX} )
endif()

if( SIXTRL_COMMON_BEAM_ELEMS_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_BEAM_ELEMS_CXX_HEADERS}
             DESTINATION ${SIXTRL_COMMON_CXX_INSTALL_PREFIX} )
endif()
