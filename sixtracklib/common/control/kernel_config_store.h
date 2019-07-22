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
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif  /* C++, Host */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigStore)*
NS(KernelConfigStore_new)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfigStore_delete)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store );

/* ----------------------------------------------------------------- */

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

/* ----------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(KernelConfigStore_num_stored_kernels)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(KernelConfigStore_num_keys)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(arch_kernel_id_t) const kernel_id );

/* ----------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigStore_has_kernel_by_key(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigStore_has_kernel)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigStore_has_kernel_detailed)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(arch_id_t) const arch_id,
    NS(kernel_purpose_t) const purpose,
    NS(kernel_variant_t) const variant,
    char const* SIXTRL_RESTRICT config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(KernelConfigStore_has_kernel_by_node_id_purpose_variant)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(NodeId) *const SIXTRL_RESTRICT node_id,
    NS(kernel_purpose_t) const purpose,
    NS(kernel_variant_t) const variant,
    char const* SIXTRL_RESTRICT config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigStore_has_kernel_by_id)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(arch_kernel_id_t) const kernel_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_kernel_id_t)
NS(KernelConfigStore_get_kernel_id_by_key)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT_REF key ) const;

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
NS(KernelConfigStore_get_kernel_id_by_node_id_purpose_variant)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const NS(NodeId) *const SIXTRL_RESTRICT node_id,
    NS(kernel_purpose_t) const purpose, NS(kernel_variant_t) const variant,
    char const* SIXTRL_RESTRICT config_str );

/* ----------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigBase) const*
NS(KernelConfigStore_get_const_ptr_kernel_config_base)(
    const NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(arch_kernel_id_t) const kernel_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigBase)*
NS(KernelConfigStore_get_ptr_kernel_config_base)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    NS(arch_kernel_id_t) const kernel_id );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif  /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_STORE_C99_H__ */

/* end: sixtracklib/common/control/kernel_config_store.h */
