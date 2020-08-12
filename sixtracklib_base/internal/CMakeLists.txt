add_library( sixtrack_base_internal INTERFACE ${SIXTRL_HEADERS} )

set( SIXTRL_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/base_types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/class_id.h
    ${CMAKE_CURRENT_SOURCE_DIR}/compiler_attributes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/compiler_compability.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mem_helpers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/namespace_defines.h
    ${CMAKE_CURRENT_SOURCE_DIR}/namespace_undef.h
    ${CMAKE_CURRENT_SOURCE_DIR}/obj_c_api_traits.h
    ${CMAKE_CURRENT_SOURCE_DIR}/obj_illegal_type.h
    ${CMAKE_CURRENT_SOURCE_DIR}/obj_data_type_traits.h
    ${CMAKE_CURRENT_SOURCE_DIR}/obj_store_traits.h
    ${CMAKE_CURRENT_SOURCE_DIR}/obj_type_id_traits.h )

target_sources( sixtrack_base_internal INTERFACE ${SIXTRL_HEADERS} )
target_include_directories( sixtrack_base_internal INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> )

set( SIXTRL_BASE_INTERFACE_SUBMODULES ${SIXTRL_BASE_INTERFACE_SUBMODULES}
     sixtrack_base_internal PARENT_SCOPE )

# ------------------------------------------------------------------------------
# handle install:

if( SIXTRL_HEADERS )
    install( FILES ${SIXTRL_HEADERS}
             DESTINATION ${SIXTRL_BASE_INSTALL_PATH}/internal )
endif()
