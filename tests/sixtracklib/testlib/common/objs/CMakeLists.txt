# ==============================================================================
# tests/sixtracklib/testlib/common/objs/CMakeLists.txt

set( SIXTRL_TESTLIB_COMMON_OBJS_C99_HEADERS
     definitions.h
     type_no_ptrs.h
     type_no_ptrs_api.h
     type_no_ptrs_derived_api.h
     type_no_ptrs_init.h
     type_no_ptrs_convert.h
     type_no_ptrs_compare.h
     type_no_ptrs_cobjects.h
     type_const_num_ptrs.h
     type_const_num_ptrs_api.h
     type_const_num_ptrs_init.h
     type_const_num_ptrs_convert.h
)

set( SIXTRL_TESTLIB_COMMON_OBJS_C99_SOURCES )

# add_library( sixtrack_test_common_objs_c99 OBJECT
#              ${SIXTRL_TESTLIB_COMMON_OBJS_C99_HEADERS}
#              ${SIXTRL_TESTLIB_COMMON_OBJS_C99_SOURCES}
# )

# target_include_directories( sixtrack_test_common_output_c99 PRIVATE
#     PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
#     PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tests> )

# set_target_properties( sixtrack_test_common_output_c99 PROPERTIES
#     LINKER_LANGUAGE C  POSITION_INDEPENDENT_CODE ON
#     C_STANDARD 99 C_STANDARD_REQUIRED ON )

# target_compile_options( sixtrack_test_common_output_c99 PRIVATE
#         ${SIXTRACKLIB_C99_FLAGS} ${SIXOUTPUTLIB_CPU_FLAGS} )

set( SIXTRL_TESTLIB_COMMON_OBJS_CXX_HEADERS
      objs_traits.hpp
      objs_initialiser_base.hpp
      type_no_ptrs.hpp
      type_const_num_ptrs.hpp
)

set( SIXTRL_TESTLIB_COMMON_OBJS_CXX_SOURCES
     objs_initialiser_base.cpp
     type_no_ptrs.cpp
     type_no_ptrs_cobjects.cpp
     type_const_num_ptrs.cpp
     type_const_num_ptrs_cobjects.cpp
)

add_library( sixtrack_test_common_objs_cxx OBJECT
             ${SIXTRL_TESTLIB_COMMON_OBJS_C99_HEADERS}
             ${SIXTRL_TESTLIB_COMMON_OBJS_CXX_HEADERS}
             ${SIXTRL_TESTLIB_COMMON_OBJS_CXX_SOURCES}
)

target_include_directories( sixtrack_test_common_objs_cxx PRIVATE
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tests> )

set_target_properties( sixtrack_test_common_objs_cxx PROPERTIES
    LINKER_LANGUAGE C  POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON )

target_compile_options( sixtrack_test_common_objs_cxx PRIVATE
        ${SIXTRACKLIB_CXX_FLAGS} ${SIXOUTPUTLIB_CPU_FLAGS} )

# ------------------------------------------------------------------------------
# pass on sixoutput_test_common_output_c99 and
# sixoutput_test_common_output_cxx as a module for sixoutput_test:

set(  SIXTRACKL_TESTLIB_LIBRARY_MODULES ${SIXTRACKL_TESTLIB_LIBRARY_MODULES}
      $<TARGET_OBJECTS:sixtrack_test_common_objs_cxx> CACHE INTERNAL "" FORCE )

# ==============================================================================
# Install :

if( SIXTRL_TESTLIB_COMMON_OBJS_C99_HEADERS )
    install( FILES ${SIXTRL_TESTLIB_COMMON_OBJS_C99_HEADERS}
             DESTINATION "${SIXTRL_TESTLIB_COMMON_INSTALL_C99_PATH}/objs" )
endif()

if( SIXTRL_TESTLIB_COMMON_OBJS_CXX_HEADERS AND SIXTRACKL_ENABLE_CXX )
    install( FILES ${SIXTRL_TESTLIB_COMMON_OBJS_CXX_HEADERS}
             DESTINATION "${SIXTRL_TESTLIB_COMMON_INSTALL_CXX_PATH}/objs" )
endif()

#end: tests/sixtracklib/testlib/common/objs/CMakeLists.txt
