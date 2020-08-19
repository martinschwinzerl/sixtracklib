set( C99_HEADERS )
set( C99_SOURCES )

set( CXX_HEADERS base_types.h class_id.h compiler_attributes.h
    compiler_compability.h mem_helpers.h namespace_defines.h namespace_undef.h
    obj_c_api_traits.h obj_illegal_type.h obj_data_type_traits.h
    obj_store_traits.h obj_type_id_traits.h thread_id.h thread_lock.h )
set( CXX_SOURCES thread_id.cpp thread_lock.cpp )

add_library( sixtrack_base_internal OBJECT
    ${CXX_HEADERS} ${C99_HEADERS} ${CXX_SOURCES} )

target_include_directories( sixtrack_base_internal
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

target_compile_options( sixtrack_base_internal PRIVATE
    ${SIXTRACKLIB_CXX_FLAGS} ${SIXTRACKLIB_CPU_FLAGS}
    ${SIXTRACKL_CXX_AUTOVEC_FLAGS} )

if( SIXTRL_BASE_LTO_SUPPORTED )
    set_target_properties( sixtrack_base_internal PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION TRUE )
endif()

set( SIXTRL_BASE_OBJECT_LIBRARY_SUBMODULES
   ${SIXTRL_BASE_OBJECT_LIBRARY_SUBMODULES}
   $<TARGET_OBJECTS:sixtrack_base_internal> PARENT_SCOPE )

# ------------------------------------------------------------------------------
# handle install:

if( C99_HEADERS )
    install( FILES ${C99_HEADERS}
             DESTINATION ${SIXTRL_BASE_INSTALL_PATH}/internal )
 endif()

if( CXX_HEADERS )
    install( FILES ${CXX_HEADERS}
             DESTINATION ${SIXTRL_BASE_INSTALL_PATH}/internal )
 endif()
