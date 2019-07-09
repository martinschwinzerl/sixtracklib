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

typedef struct NS(KernelConfigKey)
{
    NS(node_id_t)           node_id         SIXTRL_ALIGN( 8 );
    NS(kernel_purpose_t)    kernel_purpose  SIXTRL_ALIGN( 8 );
    NS(kernel_variant_t)    kernel_variant  SIXTRL_ALIGN( 8 );
}
NS(KernelConfigKey);

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigKey)* NS(KernelConfigKey_preset)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelConfigKey_init)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(kernel_purpose_t) const purpose,
    NS(Kernel_variant_t) const variant );


SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_is_valid)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTRRN SIXTRL_HOST_FN NS(arch_id_t) NS(KernelConfigKey_get_arch_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_platform_id_t)
NS(KernelConfigKey_get_platform_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_device_id_t)
NS(KernelConfigKey_get_device_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_is_smaller_than)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfigKey_are_equal)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs );

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(KernelConfigKey_compare)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs );

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_KEY_C99_H__ */

/* end: sixtracklib/common/control/kernel_config_key.h */
