set( BE_INSTALL_PREFIX
    "${CMAKE_INSTALL_PREFIX}/include/sixtracklib/common/beam_elements" )

add_subdirectory( beamfields )
add_subdirectory( dipedge )
add_subdirectory( drift )
add_subdirectory( cavity )
add_subdirectory( limit )
add_subdirectory( monitor )
add_subdirectory( multipole )
add_subdirectory( rfmultipole )
add_subdirectory( srotation )
add_subdirectory( xyshift )
