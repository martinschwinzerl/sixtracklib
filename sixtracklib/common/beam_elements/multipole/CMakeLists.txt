set( SIXTRL_COMMON_BE_MULTIPOLE_CXX_HEADERS )
set( SIXTRL_COMMON_BE_MULTIPOLE_CXX_SOURCES multipole.cpp )

set( SIXTRL_COMMON_BE_MULTIPOLE_C99_HEADERS multipole.h multipole_cobj.h track.h )
set( SIXTRL_COMMON_BE_MULTIPOLE_C99_SOURCES multipole.c track.c )

set( SIXTRL_COMMON_BE_PARENT_CXX_HEADERS )
set( SIXTRL_COMMON_BE_PARENT_C99_HEADERS ../../definitions.h
     ../definitions.h ../beam_elements.h ../cobj_type_ids.h )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( sixtrack_common_be_multipole_cxx OBJECT
    ${SIXTRL_COMMON_BE_MULTIPOLE_CXX_HEADERS}
    ${SIXTRL_COMMON_BE_MULTIPOLE_C99_HEADERS}
    ${SIXTRL_COMMON_BE_PARENT_C99_HEADERS}
    ${SIXTRL_COMMON_BE_PARENT_CXX_HEADERS}
    ${SIXTRL_COMMON_BE_MULTIPOLE_CXX_SOURCES} )

target_include_directories( sixtrack_common_be_multipole_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_be_multipole_cxx PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_be_multipole_cxx PRIVATE
        ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
        ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( sixtrack_common_be_multipole_c99 OBJECT
    ${SIXTRL_COMMON_BE_MULTIPOLE_CXX_HEADERS}
    ${SIXTRL_COMMON_BE_MULTIPOLE_C99_HEADERS}
    ${SIXTRL_COMMON_BE_PARENT_C99_HEADERS}
    ${SIXTRL_COMMON_BE_PARENT_CXX_HEADERS}
    ${SIXTRL_COMMON_BE_MULTIPOLE_C99_SOURCES} )

target_include_directories( sixtrack_common_be_multipole_c99 PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_common_be_multipole_c99 PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON C_STANDARD 99
    C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_common_be_multipole_c99 PRIVATE
        ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
        ${SIXTRACKL_C99_AUTOVEC_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixtrack_common_be_beambeam as a module for sixtracklib:

set(  SIXTRL_COMMON_BEAM_ELEMENTS_MODULES ${SIXTRL_COMMON_BEAM_ELEMENTS_MODULES}
    $<TARGET_OBJECTS:sixtrack_common_be_multipole_cxx>
    $<TARGET_OBJECTS:sixtrack_common_be_multipole_c99> PARENT_SCOPE )

# ----------------------------------------------------------------------------
# install :

if( SIXTRL_COMMON_BE_MULTIPOLE_C99_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_MULTIPOLE_C99_HEADERS}
             DESTINATION "${SIXTRL_COMMON_C99_INSTALL_PREFIX}/multipole" )
endif()

if( SIXTRL_COMMON_BE_MULTIPOLE_CXX_HEADERS )
    install( FILES ${SIXTRL_COMMON_BE_MULTIPOLE_CXX_HEADERS}
             DESTINATION "${SIXTRL_COMMON_CXX_INSTALL_PREFIX}/multipole" )
 endif()
