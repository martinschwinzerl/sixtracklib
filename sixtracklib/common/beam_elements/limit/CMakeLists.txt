# --------------------------------------------------------------------------
# processing sixtracklib/common/beam_elements/limit/CMakeLists.txt

set( SIXTRL_COMMON_BE_LIMIT_CXX_HEADERS
     limit_traits.hpp
     limit_rect_data.hpp
     limit_rect.hpp
     limit_ellipse_data.hpp
     limit_ellipse.hpp
     limit.hpp
     track.hpp
)

set( SIXTRL_COMMON_BE_LIMIT_CXX_SOURCES )


set( SIXTRL_COMMON_BE_LIMIT_C99_HEADERS
     definitions.h
     limit_ellipse.h
     limit_ellipse_api.h
     limit_rect.h
     limit_rect_api.h
     limit.h
     track.h
)

set( SIXTRL_COMMON_BE_LIMIT_C99_SOURCES
     limit_ellipse_api.c
     limit_rect_api.c )


add_library( sixtrack_common_be_limit OBJECT
    ${SIXTRL_COMMON_BE_LIMIT_C99_HEADERS}
    ${SIXTRL_COMMON_BE_LIMIT_CXX_HEADERS}
    ${SIXTRL_COMMON_BE_LIMIT_C99_SOURCES}
)

target_include_directories( sixtrack_common_be_limit PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_be_limit PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON
    C_STANDARD 99 C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_be_limit PRIVATE
    ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixtrack_common_be_limit as a module for sixtracklib:

set(  SIXTRACKL_LIBRARY_MODULES ${SIXTRACKL_LIBRARY_MODULES}
    $<TARGET_OBJECTS:sixtrack_common_be_limit> CACHE INTERNAL "" FORCE )

# =======================================================================
# Install

if( SIXTRL_COMMON_BE_LIMIT_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_LIMIT_C99_HEADERS}
             DESTINATION "${BE_INSTALL_PREFIX}/limit" )
endif()

if( SIXTRL_COMMON_BE_LIMIT_CXX_HEADERS AND SIXTRACKL_ENABLE_CXX )
    install( FILES ${SIXTRL_COMMON_BE_LIMIT_CXX_HEADERS}
             DESTINATION "${BE_INSTALL_PREFIX}/limit" )
endif()

#end:
