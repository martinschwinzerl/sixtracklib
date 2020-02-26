# ==============================================================================
# Multiprecision sixtracklib architecture

message( STATUS "---- processing sixtracklib/multiprec/CMakeLists.txt" )

if( Boost_FOUND )
    set( SIXTRACKL_LINK_LIBRARIES ${SIXTRACKL_LINK_LIBRARIES}
        Boost::boost CACHE INTERNAL "" FORCE )
endif()

#end: sixtracklib/multiprec/CMakeLists.txt
