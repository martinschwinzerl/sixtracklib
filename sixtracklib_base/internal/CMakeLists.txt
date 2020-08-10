add_library( sixtrack_base_internal INTERFACE ${SIXTRL_HEADERS} )

set( SIXTRL_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/class_id.h
    ${CMAKE_CURRENT_SOURCE_DIR}/compiler_attributes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/compiler_compability.h
    ${CMAKE_CURRENT_SOURCE_DIR}/namespace_defines.h
    ${CMAKE_CURRENT_SOURCE_DIR}/namespace_undef.h )

target_sources( sixtrack_base_internal INTERFACE ${SIXTRL_HEADERS} )

set( SIXTRL_BASE_INTERFACE_SUBMODULES ${SIXTRL_BASE_INTERFACE_SUBMODULES}
     sixtrack_base_internal PARENT_SCOPE )

# ------------------------------------------------------------------------------
# handle install:

if( SIXTRL_HEADERS )
    install( FILES ${SIXTRL_HEADERS}
             DESTINATION ${SIXTRL_BASE_INSTALL_PATH}/internal )
endif()
