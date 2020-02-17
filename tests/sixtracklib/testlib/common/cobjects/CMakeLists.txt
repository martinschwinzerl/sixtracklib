# ==============================================================================
# tests/sixtracklib/testlib/common/cobjects/CMakeLists.txt

set( SIXTRL_TESTLIB_COMMON_COBJECTS_C99_HEADERS
     type_no_ptrs.h type_fixed_num_ptrs.h )

set( SIXTRL_TESTLIB_COMMON_COBJECTS_C99_SOURCES )

# add_library( sixtrack_test_common_output_c99 OBJECT
#              ${SIXTRL_TESTLIB_COMMON_OUTPUT_C99_HEADERS}
#              ${SIXTRL_TESTLIB_COMMON_OUTPUT_C99_SOURCES}
# )

# target_include_directories( sixtrack_test_common_output_c99 PRIVATE
#     PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
#     PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tests> )

# set_target_properties( sixtrack_test_common_output_c99 PROPERTIES
#     LINKER_LANGUAGE C  POSITION_INDEPENDENT_CODE ON
#     C_STANDARD 99 C_STANDARD_REQUIRED ON )

# target_compile_options( sixtrack_test_common_output_c99 PRIVATE
#         ${SIXTRACKLIB_C99_FLAGS} ${SIXOUTPUTLIB_CPU_FLAGS} )

set( SIXTRL_TESTLIB_COMMON_COBJECTS_CXX_HEADERS )
set( SIXTRL_TESTLIB_COMMON_COBJECTS_CXX_SOURCES
     type_fixed_num_ptrs.cpp )

add_library( sixtrack_test_common_cobjects_cxx OBJECT
             ${SIXTRL_TESTLIB_COMMON_COBJECTS_C99_HEADERS}
             ${SIXTRL_TESTLIB_COMMON_COBJECTS_CXX_HEADERS}
             ${SIXTRL_TESTLIB_COMMON_COBJECTS_CXX_SOURCES}
)

target_include_directories( sixtrack_test_common_cobjects_cxx PRIVATE
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tests> )

set_target_properties( sixtrack_test_common_cobjects_cxx PROPERTIES
    LINKER_LANGUAGE C  POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_test_common_cobjects_cxx PRIVATE
        ${SIXTRACKLIB_CXX_FLAGS} ${SIXOUTPUTLIB_CPU_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixoutput_test_common_output_c99 and
# sixoutput_test_common_output_cxx as a module for sixoutput_test:

set(  SIXTRACKL_TESTLIB_LIBRARY_MODULES ${SIXTRACKL_TESTLIB_LIBRARY_MODULES}
      $<TARGET_OBJECTS:sixtrack_test_common_cobjects_cxx>
      CACHE INTERNAL "" FORCE )

# ==============================================================================
# Install :

if( SIXTRL_TESTLIB_COMMON_COBJECTS_C99_HEADERS )
    install( FILES ${SIXTRL_TESTLIB_COMMON_COBJECTS_C99_HEADERS}
             DESTINATION "${SIXTRL_TESTLIB_COMMON_INSTALL_C99_PATH}/cobjects" )
endif()

if( SIXTRL_TESTLIB_COMMON_COBJECTS_CXX_HEADERS AND SIXTRACKL_ENABLE_CXX )
    install( FILES ${SIXTRL_TESTLIB_COMMON_COBJECTS_CXX_HEADERS}
             DESTINATION "${SIXTRL_TESTLIB_COMMON_INSTALL_CXX_PATH}/cobjects" )
endif()

#end: tests/sixtracklib/testlib/common/cobjects/CMakeLists.txt
