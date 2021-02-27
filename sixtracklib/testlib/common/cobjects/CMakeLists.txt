set( SIXTRL_TESTLIB_COBJECTS_C99_HEADERS
    definitions.h cobj_no_ptrs.h cobj_dataptrs.h )
set( SIXTRL_TESTLIB_COBJECTS_C99_SOURCES cobj_no_ptrs.c cobj_dataptrs.c )

set( SIXTRL_TESTLIB_COBJECTS_CXX_HEADERS cobj_no_ptrs.hpp cobj_dataptrs.hpp )
set( SIXTRL_TESTLIB_COBJECTS_CXX_SOURCES cobjects.cpp )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( sixtrack_testlib_common_cobjects_cxx OBJECT
             ${SIXTRL_TESTLIB_COBJECTS_CXX_HEADERS}
             ${SIXTRL_TESTLIB_COBJECTS_C99_HEADERS}
             ${SIXTRL_TESTLIB_COBJECTS_CXX_SOURCES} )

target_include_directories( sixtrack_testlib_common_cobjects_cxx PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_testlib_common_cobjects_cxx PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_testlib_common_cobjects_cxx PRIVATE
        ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
        ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( sixtrack_testlib_common_cobjects_c99 OBJECT
             ${SIXTRL_TESTLIB_COBJECTS_C99_HEADERS}
             ${SIXTRL_TESTLIB_COBJECTS_CXX_HEADERS}
             ${SIXTRL_TESTLIB_COBJECTS_C99_SOURCES} )

target_include_directories( sixtrack_testlib_common_cobjects_c99 PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include> )

set_target_properties( sixtrack_testlib_common_cobjects_c99 PROPERTIES
    LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON C_STANDARD 99
    C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_testlib_common_cobjects_c99 PRIVATE
        ${SIXTRACKLIB_C99_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
        ${SIXTRACKL_C99_AUTOVEC_FLAGS} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( SIXTRL_TESTLIB_COMMON_OBJ_LIBRARIES ${SIXTRL_TESTLIB_COMMON_OBJ_LIBRARIES}
     $<TARGET_OBJECTS:sixtrack_testlib_common_cobjects_c99>
     $<TARGET_OBJECTS:sixtrack_testlib_common_cobjects_cxx> PARENT_SCOPE )

# -----------------------------------------------------------------------------
# install:


if( SIXTRL_TESTLIB_COBJECTS_C99_HEADERS )
    install( FILES ${SIXTRL_TESTLIB_COBJECTS_C99_HEADERS}
             DESTINATION "${SIXTRL_TESTLIB_COMMON_C99_INSTALL_PREFIX}/cobjects" )
endif()

if( SIXTRACKL_ENABLE_CXX AND SIXTRL_TESTLIB_COBJECTS_CXX_HEADERS )
    install( FILES ${SIXTRL_TESTLIB_COBJECTS_CXX_HEADERS}
             DESTINATION "${SIXTRL_TESTLIB_COMMON_CXX_INSTALL_PREFIX}/cobjects" )
 endif()
