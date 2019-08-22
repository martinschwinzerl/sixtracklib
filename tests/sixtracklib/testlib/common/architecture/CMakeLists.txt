# ==============================================================================
# tests/sixtracklib/testlib/common/architecture/CMakeLists.txt

set( SIXTRL_TESTLIB_COMMON_ARCHITECTURE_C99_HEADERS
     architecture.h )

set( SIXTRL_TESTLIB_COMMON_ARCHITECTURE_C99_SOURCES )

# ------------------------------------------------------------------------------

set( SIXTRL_TESTLIB_COMMON_ARCHITECTURE_CXX_HEADERS
    architecture.hpp
)

set( SIXTRL_TESTLIB_COMMON_ARCHITECTURE_CXX_SOURCES
     architecture.cpp
     architecture_c99.cpp
)

add_library( sixtrack_test_common_architecture_cxx OBJECT
    ${SIXTRL_TESTLIB_COMMON_ARCHITECTURE_C99_HEADERS}
    ${SIXTRL_TESTLIB_COMMON_ARCHITECTURE_CXX_HEADERS}
    ${SIXTRL_TESTLIB_COMMON_ARCHITECTURE_CXX_SOURCES} )

target_include_directories( sixtrack_test_common_architecture_cxx PRIVATE
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tests> )

set_target_properties( sixtrack_test_common_architecture_cxx PROPERTIES
    LINKER_LANGUAGE C  POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 11 C_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_test_common_architecture_cxx PRIVATE
        ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixtrack_test_common_architecture_cxx as a module for sixtrack_test:

set(  SIXTRACKL_TESTLIB_LIBRARY_MODULES
    ${SIXTRACKL_TESTLIB_LIBRARY_MODULES}
    $<TARGET_OBJECTS:sixtrack_test_common_architecture_cxx>
    CACHE INTERNAL "" FORCE )

# ==============================================================================
# Install :

if( SIXTRL_TESTLIB_COMMON_ARCHITECTURE_C99_HEADERS )
    install( FILES ${SIXTRL_TESTLIB_COMMON_ARCHITECTURE_C99_HEADERS}
        DESTINATION "${SIXTRL_TESTLIB_COMMON_INSTALL_C99_PATH}/architecture" )
endif()


if( ( SIXTRL_TESTLIB_COMMON_ARCHITECTURE_CXX_HEADERS ) AND
    ( SIXTRACKL_ENABLE_CXX ) )
    install( FILES ${SIXTRL_TESTLIB_COMMON_ARCHITECTURE_CXX_HEADERS}
        DESTINATION "${SIXTRL_TESTLIB_COMMON_INSTALL_CXX_PATH}/architecture" )

endif()

#end: tests/sixtracklib/testlib/common/architecture/CMakeLists.txt
