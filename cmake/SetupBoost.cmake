if( NOT  SIXTRACKL_CMAKE_SETUP_BOOST_FINISHED   )
    set( SIXTRACKL_CMAKE_SETUP_BOOST_FINISHED 1 )

    message( STATUS "---- Processing cmake/SetupBoost.cmake" )

    if( NOT Boost_FOUND )
       if( NOT SIXTRACKL_BOOST_COMPONENTS )
           find_package( Boost REQUIRED )
       else()
           find_package( Boost REQUIRED
               COMPONENTS ${SIXTRACKL_BOOST_COMPONENTS} )
       endif()

    endif()

endif()
#end: sixtracklib/cmake/SetupBoost.cmake

