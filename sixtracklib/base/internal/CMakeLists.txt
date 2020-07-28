set( C99_HEADERS
    class_id.h compiler_attributes.h compiler_compability.h
    namespace_defines.h namespace_undef.h )

set( SIXTRL_BASE_HEADERS ${SIXTRL_BASE_HEADERS}
     internal/class_id.h internal/compiler_attributes.h
     internal/compiler_compability.h internal/namespace_defines.h
     internal/namespace_undef.h PARENT_SCOPE
)

install( FILES ${C99_HEADERS}
         DESTINATION ${SIXTRL_BASE_INSTALL_PATH}/internal )
