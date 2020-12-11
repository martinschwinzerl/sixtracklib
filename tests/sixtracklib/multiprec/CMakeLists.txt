# ==============================================================================
# tests/sixtracklib/multiprec/CMakeLists.txt
message( STATUS "---- processing tests/sixtracklib/multiprec/CMakeLists.txt" )

set( SIXTRACKL_TEST_LIBRARIES sixtrack_cxx_be ${SIXTRACKL_TEST_LIBRARIES} )

add_subdirectory( beam_elements )
add_subdirectory( particles )
