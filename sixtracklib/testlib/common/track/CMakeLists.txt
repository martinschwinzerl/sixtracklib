set( SIXTRL_TESTLIB_TRACK_C99_SOURCES
    sixtrack_sequ_by_sequ.c cmp_elem_by_elem.c )
set( SIXTRL_TESTLIB_TRACK_C99_HEADERS
    sixtrack_sequ_by_sequ.h cmp_elem_by_elem.h )

set( SIXTRL_TESTLIB_TRACK_CXX_HEADERS )
set( SIXTRL_TESTLIB_TRACK_CXX_SOURCES )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( sixtrack_testlib_common_track_c99 OBJECT
             ${SIXTRL_TESTLIB_TRACK_CXX_HEADERS}
             ${SIXTRL_TESTLIB_TRACK_C99_HEADERS}
             ${SIXTRL_TESTLIB_TRACK_CXX_SOURCES} )

target_include_directories( sixtrack_testlib_common_track_c99 PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_testlib_common_track_c99 PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON C_STANDARD 99
    C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_testlib_common_track_c99 PRIVATE
        ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
        ${SIXTRACKL_C99_AUTOVEC_FLAGS} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( SIXTRL_TESTLIB_OBJECT_LIBRARIES ${SIXTRL_TESTLIB_OBJECT_LIBRARIES}
     $<TARGET_OBJECTS:sixtrack_testlib_common_track_c99> PARENT_SCOPE )

# -----------------------------------------------------------------------------
# install:

if( SIXTRL_TESTLIB_TRACK_C99_HEADERS )
    install( FILES ${SIXTRL_TESTLIB_TRACK_C99_HEADERS}
             DESTINATION "${SIXTRL_TESTLIB_COMMON_C99_INSTALL_PREFIX}/track" )
endif()

if( SIXTRACKL_ENABLE_CXX AND SIXTRL_TESTLIB_TRACK_CXX_HEADERS )
    install( FILES ${SIXTRL_TESTLIB_TRACK_CXX_HEADERS}
             DESTINATION "${SIXTRL_TESTLIB_COMMON_CXX_INSTALL_PREFIX}/track" )
 endif()
