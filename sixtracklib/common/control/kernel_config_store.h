#ifndef SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_STORE_C99_H__
#define SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_STORE_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/kernel_config_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/kernel_config_key.h"
    #include "sixtracklib/common/control/kernel_set.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif  /* C++, Host */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigStore)*
NS(KernelConfigStore_create)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfigStore_delete)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(KernelConfigStore_get_num_kernel_sets)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(kernel_set_id_t)
NS(KernelConfigStore_add_kernel_set)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    NS(KernelSetBase)* ptr_kernel_set_to_take_ownership );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigStore_has_kernel_set)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(kernel_set_id_t) const kernel_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigStore_has_kernel_set_by_ptr)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(KernelSetBase) *const SIXTRL_RESTRICT kernel_set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfigStore_update_kernel_set)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    NS(kernel_set_id_t) const kernel_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(kernel_set_id_t)
NS(KernelConfigStore_get_kernel_set_id)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(KernelSetBase) *const SIXTRL_RESTRICT kernel_set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelSetBase) const*
NS(KernelConfigStore_get_ptr_const_kernel_set)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(kernel_set_id_t) const kernel_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelSetBase)*
NS(KernelConfigStore_get_ptr_kernel_set_base)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    NS(kernel_set_id_t) const kernel_set_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfigStore_remove_kernel_set)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    NS(kernel_set_id_t) const kernel_set_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ctrl_kernel_id_t)
NS(KernelConfigStore_add_kernel_config)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    NS(KernelConfigBase)* SIXTRL_RESTRICT ptr_kernel_config_to_take_ownership );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfigStore_add_kernel_config_to_key_mapping)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    NS(ctrl_kernel_id_t) const kernel_config_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfigStore_remove_kernel_config_by_key)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT_REF key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfigStore_remove_kernel_config)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfigStore_remove_kernel_config_by_id)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    NS(arch_kernel_id_t) const kernel_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(KernelConfigStore_get_num_stored_kernels)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(KernelConfigStore_get_num_kernel_config_keys)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(arch_kernel_id_t) const kernel_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigStore_has_kernel_by_key)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigStore_has_kernel)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(ctrl_kernel_id_t) const kernel_config_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(KernelConfigStore_has_kernel_by_ptr_config_base)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigStore_has_kernel_detailed)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(arch_id_t) const arch_id,
    NS(kernel_purpose_t) const purpose,
    NS(kernel_variant_t) const variant,
    NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(KernelConfigStore_has_kernel_by_node_id_detailed)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(NodeId) *const SIXTRL_RESTRICT node_id,
    NS(kernel_purpose_t) const purpose,
    NS(kernel_variant_t) const variant,
    NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigStore_has_kernel_by_id)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(arch_kernel_id_t) const kernel_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_kernel_id_t)
NS(KernelConfigStore_get_kernel_id_by_kernel_id)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(ctrl_kernel_id_t) const kernel_config_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_kernel_id_t)
NS(KernelConfigStore_get_kernel_id_by_key)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT_REF key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_kernel_id_t)
NS(KernelConfigStore_get_kernel_id)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_kernel_id_t)
NS(KernelConfigStore_get_kernel_id_detailed)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(arch_id_t) const arch_id,
    NS(kernel_purpose_t) const purpose,
    NS(kernel_variant_t) const variant,
    char const* SIXTRL_RESTRICT config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_kernel_id_t)
NS(KernelConfigStore_get_kernel_id_by_node_id_detailed)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(NodeId) *const SIXTRL_RESTRICT node_id,
    NS(kernel_purpose_t) const purpose,
    NS(kernel_variant_t) const variant,
    NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT config_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigBase) const*
NS(KernelConfigStore_get_const_ptr_kernel_config_base)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(arch_kernel_id_t) const kernel_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigBase)*
NS(KernelConfigStore_get_ptr_kernel_config_base)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    NS(arch_kernel_id_t) const kernel_id );


/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ctrl_kernel_id_t)
NS(KernelConfigStore_init_kernel_config)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ctrl_kernel_id_t)
NS(KernelConfigStore_init_kernel_config_detailed)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key,
    NS(arch_size_t) const num_kernel_args,
    char const* SIXTRL_RESTRICT kernel_name );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfigStore_set_default_init_kernel_config_parameters)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key,
    NS(arch_size_t) const num_kernel_arguments,
    char const* SIXTRL_RESTRICT kernel_name );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfigStore_remove_default_init_kernel_config_parameters)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(KernelConfigStore_has_default_init_kernel_config_parameters)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(KernelConfigStore_get_default_num_kernel_args)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN char const*
NS(KernelConfigStore_get_default_kernel_name)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif  /* C++, Host */

#endif /* !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_STORE_C99_H__ */

/* end: sixtracklib/common/control/kernel_config_store.h */
