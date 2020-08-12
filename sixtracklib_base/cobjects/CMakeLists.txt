# sixtracklib_base/cobjects/CMakeLists.txt

add_library( sixtrack_base_cobjects_c99 INTERFACE )

set( C99_HEADERS
     ${CMAKE_CURRENT_SOURCE_DIR}/c_api_helpers.h
     ${CMAKE_CURRENT_SOURCE_DIR}/definitions.h
     ${CMAKE_CURRENT_SOURCE_DIR}/definitions_undef.h
     ${CMAKE_CURRENT_SOURCE_DIR}/element_pointers.h
     ${CMAKE_CURRENT_SOURCE_DIR}/element_traits.h
     ${CMAKE_CURRENT_SOURCE_DIR}/field_counts.h
     ${CMAKE_CURRENT_SOURCE_DIR}/field_offsets.h
     ${CMAKE_CURRENT_SOURCE_DIR}/field_sizes.h
     ${CMAKE_CURRENT_SOURCE_DIR}/flat_buffer.h
     ${CMAKE_CURRENT_SOURCE_DIR}/garbage_range.h
     ${CMAKE_CURRENT_SOURCE_DIR}/helper_functions.h
     ${CMAKE_CURRENT_SOURCE_DIR}/index_object.h
     ${CMAKE_CURRENT_SOURCE_DIR}/obj_convert.h
     ${CMAKE_CURRENT_SOURCE_DIR}/obj_delegate.h
 )

target_sources( sixtrack_base_cobjects_c99 INTERFACE ${C99_HEADERS} )
target_include_directories( sixtrack_base_cobjects_c99
    INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

set( SIXTRL_BASE_INTERFACE_SUBMODULES ${SIXTRL_BASE_INTERFACE_SUBMODULES}
     sixtrack_base_cobjects_c99 PARENT_SCOPE )

 # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( CXX_HEADERS cbuffer_view.h cbuffer.h )
set( CXX_SOURCES cbuffer_view.cpp cbuffer.cpp )

add_library( sixtrack_base_cobjects_cxx OBJECT ${CXX_HEADERS} ${CXX_SOURCES} )

target_include_directories( sixtrack_base_cobjects_cxx
    PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

target_link_libraries( sixtrack_base_cobjects_cxx
    PRIVATE sixtrack_base_cobjects_c99 )

target_compile_options( sixtrack_base_cobjects_cxx PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

if( SIXTRL_BASE_LTO_SUPPORTED )
    set_target_properties( sixtrack_base_cobjects_cxx PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION TRUE )
endif()

set( SIXTRL_BASE_OBJECT_LIBRARY_SUBMODULES
   ${SIXTRL_BASE_OBJECT_LIBRARY_SUBMODULES}
   $<TARGET_OBJECTS:sixtrack_base_cobjects_cxx> PARENT_SCOPE )

# -----------------------------------------------------------------------------
# handle installation:

if( C99_HEADERS )
    install( FILES ${C99_HEADERS}
             DESTINATION ${SIXTRL_BASE_INSTALL_PATH}/cobjects )
 endif()

if( CXX_HEADERS )
    install( FILES ${CXX_HEADERS}
             DESTINATION ${SIXTRL_BASE_INSTALL_PATH}/cobjects )
 endif()
