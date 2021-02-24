message( STATUS "------ processing sixtracklib/testlib/CMakeLists.txt" )

set( SIXTRL_TESTLIB_C99_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/testlib" )
set( SIXTRL_TESTLIB_CXX_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/testlib" )

set( SIXTRL_TESTLIB_OBJECT_LIBRARIES )

# ------------------------------------------------------------------------------

set( SIXTRL_TESTLIB_CXX_HEADERS )
set( SIXTRL_TESTLIB_CXX_SOURCES )

set( SIXTRL_TESTLIB_C99_HEADERS )
set( SIXTRL_TESTLIB_C99_SOURCES )

 # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 add_subdirectory( common )

 # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 set( SIXTRL_TESTLIB_OBJECT_LIBRARIES
    ${SIXTRL_TESTLIB_OBJECT_LIBRARIES} PARENT_SCOPE )

# -------------------------------------------------------------------------------

add_library( sixtrack_test SHARED ${SIXTRL_TESTLIB_OBJECT_LIBRARIES} )

target_include_directories( sixtrack_test PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_test PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_test PRIVATE
        ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
        ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

# -------------------------------------------------------------------------------
# install:


if( SIXTRL_TESTLIB_C99_HEADERS )
    install( FILES ${SIXTRL_TESTLIB_C99_HEADERS}
             DESTINATION ${SIXTRL_TESTLIB_C99_INSTALL_PREFIX} )
endif()

if( SIXTRACKL_ENABLE_CXX AND SIXTRL_TESTLIB_CXX_HEADERS )
    install( FILES ${SIXTRL_TESTLIB_CXX_HEADERS}
             DESTINATION ${SIXTRL_TESTLIB_CXX_INSTALL_PREFIX} )
 endif()
