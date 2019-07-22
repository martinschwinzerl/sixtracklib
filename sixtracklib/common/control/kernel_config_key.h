#ifndef SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_KEY_C99_H__
#define SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_KEY_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigKey)* NS(KernelConfigKey_new)(
    NS(node_id_t) const arch_id,
    NS(kernel_purpose_t) const purpose,
    NS(arch_variant_t) const variant,
    char const* SIXTRL_RESTRICT config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigKey)*
NS(KernelConfigKey_new_detailed)(
    NS(arch_id_t) const arch_id,
    NS(kernel_purpose_t) const purpose,
    NS(arch_variant_t) const variant,
    char const* SIXTRL_RESTRICT config_str,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfigKey_delete)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_id_t) NS(KernelConfigKey_get_arch_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(kernel_purpose_t)
NS(KernelConfigKey_get_purpose)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfigKey_set_purpose)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    NS(kernel_purpose_t) const purpose );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_variant_t)
NS(KernelConfigKey_get_variant)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfigKey_set_variant)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    NS(arch_variant_t) const variant );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_has_config_str)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(KernelConfigKey_config_str)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfigKey_set_config_str)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    char const* SIXTRL_RESTRICT config_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_has_node_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_id_t) const*
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

SIXTRL_EXTERN SIXTRL_HOST_FN bool operator<( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool operator==( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN int compare( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_KEY_C99_H__ */

/* end: sixtracklib/common/control/kernel_config_key.h */
