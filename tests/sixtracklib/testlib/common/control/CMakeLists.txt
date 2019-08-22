# ==============================================================================
# tests/sixtracklib/testlib/common/control/CMakeLists.txt

set( SIXTRL_TESTLIB_COMMON_CONTROL_C99_HEADERS
     node_info.h
     node_set.h
)

set( SIXTRL_TESTLIB_COMMON_CONTROL_C99_SOURCES )

# ------------------------------------------------------------------------------

set( SIXTRL_TESTLIB_COMMON_CONTROL_CXX_HEADERS
    node_info.hpp
    node_set.hpp
)

set( SIXTRL_TESTLIB_COMMON_CONTROL_CXX_SOURCES
     node_info.cpp
     node_info_c99.cpp
     node_set.cpp
     node_set_c99.cpp
)

add_library( sixtrack_test_common_control_cxx OBJECT
    ${SIXTRL_TESTLIB_COMMON_CONTROL_C99_HEADERS}
    ${SIXTRL_TESTLIB_COMMON_CONTROL_CXX_HEADERS}
    ${SIXTRL_TESTLIB_COMMON_CONTROL_CXX_SOURCES} )

target_include_directories( sixtrack_test_common_control_cxx PRIVATE
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tests> )

set_target_properties( sixtrack_test_common_control_cxx PROPERTIES
    LINKER_LANGUAGE C  POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 11 C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_test_common_control_cxx PRIVATE
        ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixtrack_test_common_control_cxx as a module for sixtrack_test:

set(  SIXTRACKL_TESTLIB_LIBRARY_MODULES
    ${SIXTRACKL_TESTLIB_LIBRARY_MODULES}
    $<TARGET_OBJECTS:sixtrack_test_common_control_cxx>
    CACHE INTERNAL "" FORCE )

# ==============================================================================
# Install :

if( SIXTRL_TESTLIB_COMMON_CONTROL_C99_HEADERS )
    install( FILES ${SIXTRL_TESTLIB_COMMON_CONTROL_C99_HEADERS}
             DESTINATION "${SIXTRL_TESTLIB_COMMON_INSTALL_C99_PATH}/control" )
endif()

if( ( SIXTRL_TESTLIB_COMMON_CONTROL_CXX_HEADERS ) AND
    ( SIXTRACKL_ENABLE_CXX ) )
    install( FILES ${SIXTRL_TESTLIB_COMMON_CONTROL_CXX_HEADERS}
             DESTINATION "${SIXTRL_TESTLIB_COMMON_INSTALL_CXX_PATH}/control" )

endif()

#end: tests/sixtracklib/testlib/common/control/CMakeLists.txt
