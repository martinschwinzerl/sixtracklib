#ifndef SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_BASE_C99_H__
#define SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_BASE_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include <stdio.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/kernel_config_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfig_delete)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_id_t) NS(KernelConfig_get_arch_id)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_has_arch_string)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(KernelConfig_get_ptr_arch_string)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_has_kernel_id)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ctrl_kernel_id_t)
NS(KernelConfig_get_kernel_id)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfig_set_kernel_id)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config,
    NS(ctrl_kernel_id_t) const kernel_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_has_name)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(KernelConfig_get_ptr_name_string)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfig_set_name)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config,
    char const* SIXTRL_RESTRICT kernel_name );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ctrl_size_t)
NS(KernelConfig_get_num_arguments)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfig_set_num_arguments)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config,
    NS(ctrl_size_t) const num_kernel_args );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(kernel_config_variant_t)
NS(KernelConfig_get_variant_flags)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_are_variant_flags_set)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    NS(kernel_config_variant_t) const flags_to_check );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_is_variant_debug_mode)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_is_variant_release_mode)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfig_set_variant_flags)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config,
    NS(kernel_config_variant_t) const variant_flags );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_has_nodes)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(KernelConfig_get_num_nodes)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId) const* NS(KernelConfig_get_const_node)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    NS(arch_size_t) const num_node_in_list );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId)* NS(KernelConfig_get_node)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config,
    NS(arch_size_t) const num_node_in_list );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelConfig_assign_to_node)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config,
    const NS(NodeId) *const SIXTRL_RESTRICT ptr_node );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_is_assigned_to_node)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    const NS(NodeId) *const SIXTRL_RESTRICT ptr_node );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(KernelConfig_is_assigned_to_node_with_platform_and_device_id)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfig_detach_from_node)( NS(KernelConfigBase)* SIXTRL_RESTRICT conf,
    const NS(NodeId) *const SIXTRL_RESTRICT ptr_node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfig_detach_from_node_with_platform_id_and_device_id)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT conf,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfig_clear)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_needs_update)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ctrl_status_t) NS(KernelConfig_update)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfig_print)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    FILE* SIXTRL_RESTRICT output );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfig_print_out)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_BASE_C99_H__ */
/* end: sixtracklib/common/control/kernel_config_base.h */
