# ==============================================================================
# sixtracklib/common/CMakeLists.txt

message( STATUS "---- processing sixtracklib/common/CMakeLists.txt" )

set( SIXTRL_COMMON_C99_INSTALL_PREFIX "${SIXTRACKLIB_C99_INSTALL_PREFIX}/common" )
set( SIXTRL_COMMON_CXX_INSTALL_PREFIX "${SIXTRACKLIB_CXX_INSTALL_PREFIX}/common" )

set( SIXTRL_COMMON_LINK_LIBRARIES )
set( SIXTRL_COMMON_MODULES )

set(  SIXTRACKL_LINK_LIBRARIES ${SIXTRACKL_LINK_LIBRARIES} PARENT_SCOPE )

add_subdirectory( backends       )
add_subdirectory( beam_elements  )
add_subdirectory( cobjects       )
add_subdirectory( generated      )
add_subdirectory( control        )
add_subdirectory( internal       )
add_subdirectory( particles      )
add_subdirectory( track          )

set( SIXTRL_LINK_LIBRARIES ${SIXTRL_LINK_LIBRARIES}
    ${SIXTRL_COMMON_LINK_LIBRARIES} PARENT_SCOPE )

set( SIXTRL_MODULES ${SIXTRL_MODULES}
    ${SIXTRL_COMMON_MODULES} PARENT_SCOPE )

set( SIXTRL_COMMON_C99_HEADERS definitions.h )
set( SIXTRL_COMMON_CXX_HEADERS )

# ------------------------------------------------------------------------------
# install :

if( SIXTRL_COMMON_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_C99_HEADERS}
             DESTINATION ${SIXTRL_COMMON_C99_INSTALL_PREFIX} )
endif()

if( SIXTRL_COMMON_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_CXX_HEADERS}
             DESTINATION ${SIXTRL_COMMON_CXX_INSTALL_PREFIX} )
endif()
