#ifndef SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_KEY_C99_H__
#define SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_KEY_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/kernel_config_key.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigKey)*
    NS(KernelConfigKey_create)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigKey)* NS(KernelConfigKey_new)(
    NS(arch_id_t) const arch_id,
    NS(kernel_purpose_t) const purpose,
    NS(arch_variant_flags_t) const variant,
    char const* SIXTRL_RESTRICT kernel_config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigKey)*
NS(KernelConfigKey_new_from_copy)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigKey)*
NS(KernelConfigKey_new_from_node_id)(
    const NS(NodeId) *const node_id,
    NS(kernel_purpose_t) const purpose,
    NS(arch_variant_flags_t) const variant,
    NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT kernel_config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigKey)*
NS(KernelConfigKey_new_detailed)(
    NS(arch_id_t) const arch_id,
    NS(kernel_purpose_t) const purpose,
    NS(arch_variant_flags_t) const variant,
    NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT kernel_config_str,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfigKey_delete)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfigKey_assign_from)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT destination,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT source );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfigKey_reset_to_default_values)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelConfigKey_reset)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    NS(kernel_purpose_t) const purpose,
    NS(arch_variant_flags_t) const variant,
    NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT kernel_config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfigKey_reset_with_node_id)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    const NS(NodeId) *const SIXTRL_RESTRICT node_id,
    NS(kernel_purpose_t) const purpose,
    NS(arch_variant_flags_t) const variant,
    NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT kernel_config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfigKey_reset_detailed)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    NS(arch_id_t) const arch_id,
    NS(kernel_purpose_t) const purpose,
    NS(arch_variant_flags_t) const variant,
    NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT kernel_config_str,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_is_valid)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_id_t) NS(KernelConfigKey_get_arch_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(kernel_purpose_t)
NS(KernelConfigKey_get_purpose)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfigKey_set_purpose)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    NS(kernel_purpose_t) const purpose );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_variant_flags_t)
NS(KernelConfigKey_get_variant)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_are_variant_flags_set)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key,
    NS(arch_variant_flags_t) const variant_flags );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_is_variant_debug_mode)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_is_variant_release_mode)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfigKey_set_variant)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    NS(arch_variant_flags_t) const variant );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(kernel_argument_set_t)
NS(KernelConfigKey_get_argument_set)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfigKey_set_argument_set)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    NS(kernel_argument_set_t) const argument_set );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_has_config_str)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(KernelConfigKey_get_config_str)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfigKey_set_config_str)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    char const* SIXTRL_RESTRICT config_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_has_node_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId) const*
NS(KernelConfigKey_get_node_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_platform_id_t)
NS(KernelConfigKey_get_platform_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_device_id_t)
NS(KernelConfigKey_get_device_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(KernelConfigKey_compare)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_are_equal)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_are_not_equal)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_are_equal_except_purpose)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs );

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_KEY_C99_H__ */

/* end: sixtracklib/common/control/kernel_config_key.h */
