# --------------------------------------------------------------------------
# processing sixtracklib/common/beam_elements/cavity/CMakeLists.txt

set( SIXTRL_COMMON_BE_CAVITY_CXX_HEADERS
     cavity_traits.hpp
     cavity_data.hpp
     cavity.hpp
     track.hpp
)

set( SIXTRL_COMMON_BE_CAVITY_CXX_SOURCES )


set( SIXTRL_COMMON_BE_CAVITY_C99_HEADERS
     cavity.h
     cavity_api.h
     track.h
)

set( SIXTRL_COMMON_BE_CAVITY_C99_SOURCES )

# =======================================================================
# Install

if( SIXTRL_COMMON_BE_CAVITY_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_CAVITY_C99_HEADERS}
             DESTINATION "${BE_INSTALL_PREFIX}/cavity" )
endif()

if( SIXTRL_COMMON_BE_CAVITY_CXX_HEADERS AND SIXTRACKL_ENABLE_CXX )
    install( FILES ${SIXTRL_COMMON_BE_CAVITY_CXX_HEADERS}
             DESTINATION "${BE_INSTALL_PREFIX}/cavity" )
endif()

#end:
