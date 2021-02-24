message( STATUS "------ processing sixtracklib/testlib/common/CMakeLists.txt" )

set(   SIXTRL_TESTLIB_COMMON_C99_INSTALL_PREFIX
    "${SIXTRL_TESTLIB_C99_INSTALL_PREFIX}/common" )

set(   SIXTRL_TESTLIB_COMMON_CXX_INSTALL_PREFIX
    "${SIXTRL_TESTLIB_CXX_INSTALL_PREFIX}/common" )

set( SIXTRL_TESTLIB_OBJECT_LIBRARIES )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_subdirectory( cobjects )
add_subdirectory( beam_elements )
add_subdirectory( particles )
add_subdirectory( track )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set(  SIXTRL_TESTLIB_OBJECT_LIBRARIES
    ${SIXTRL_TESTLIB_OBJECT_LIBRARIES} PARENT_SCOPE )


