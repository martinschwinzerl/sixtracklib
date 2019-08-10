#ifndef SIXTRACKLIB_COMMON_CONTROL_CONTROLLER_BASE_H__
#define SIXTRACKLIB_COMMON_CONTROL_CONTROLLER_BASE_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/controller_base.hpp"
    #include "sixtracklib/common/control/argument_base.hpp"
    #include "sixtracklib/common/control/kernel_config_base.hpp"
    #include "sixtracklib/common/control/kernel_config_key.hpp"
    #include "sixtracklib/common/control/kernel_config_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
extern "C" {
#endif /* C++, host */

#if !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Controller_delete)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Controller_clear)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_id_t) NS(Controller_get_arch_id)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_has_arch_string)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(Controller_get_arch_string)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_has_config_string)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(Controller_get_config_string)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_uses_nodes)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_has_name)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(Controller_get_name_str)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Controller_set_name)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT controller_name );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_has_default_kernel_config_str)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN char const*
NS(Controller_get_default_kernel_config_str)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Controller_set_default_kernel_config_str)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT default_kernel_config_str );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(Controller_send_detailed)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    NS(ArgumentBase)* SIXTRL_RESTRICT destination,
    void const* SIXTRL_RESTRICT source, NS(arch_size_t) const src_len );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(Controller_send_buffer)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    NS(ArgumentBase)* SIXTRL_RESTRICT destination,
    NS(Buffer) const* SIXTRL_RESTRICT source );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(Controller_receive_detailed)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    void* SIXTRL_RESTRICT destination,
    NS(arch_size_t) const destination_capacity,
    NS(ArgumentBase)* SIXTRL_RESTRICT source );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(Controller_receive_buffer)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    NS(Buffer)* SIXTRL_RESTRICT destination,
    NS(ArgumentBase)* SIXTRL_RESTRICT source );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(Controller_is_cobjects_buffer_arg_remapped)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    NS(ArgumentBase)* SIXTRL_RESTRICT cobject_buffer_arg );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(Controller_remap_cobjects_buffer_arg)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    NS(ArgumentBase)* SIXTRL_RESTRICT cobject_buffer_arg );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_is_ready_to_run_kernel)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_is_ready_to_remap)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_is_ready_to_send)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_is_ready_to_receive)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

/* ------------------------------------------------------------------------ */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_is_in_debug_mode)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(Controller_enable_debug_mode)( NS(ControllerBase)* SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(Controller_disable_debug_mode)( NS(ControllerBase)* SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_variant_flags_t)
NS(Controller_active_variant_flags)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_are_variant_flags_set)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller,
    NS(arch_variant_flags_t) const variant_flags );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_variant_release_mode)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_variant_debug_mode)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

/* ========================================================================= */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(Controller_get_num_of_kernels)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(Controller_get_num_keys_for_kernel_id)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller,
    NS(ctrl_kernel_id_t) const kernel_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_has_kernel_id)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller,
    NS(ctrl_kernel_id_t) const kernel_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ctrl_kernel_id_t)
NS(Controller_get_kernel_id_by_key)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT kernel_config_key );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(Controller_add_kernel_config_mapping)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT kernel_config_key,
    NS(ctrl_kernel_id_t) const kernel_config_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigBase) const*
NS(Controller_get_const_kernel_config_base)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller,
    NS(ctrl_kernel_id_t) const kernel_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigBase)*
NS(Controller_get_kernel_config_base)(
    NS(ControllerBase)* SIXTRL_RESTRICT controller,
    NS(ctrl_kernel_id_t) const kernel_id );

/* ========================================================================= */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Controller_has_remap_buffer_kernel)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ctrl_kernel_id_t)
NS(Controller_get_remap_buffer_kernel_id)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigKey) const*
NS(Controller_get_remap_buffer_kernel_key)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT controller );

/* ========================================================================= */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(Controller_set_active_variant_flags)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    NS(arch_variant_flags_t) const variant_flags );

/* ========================================================================= */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigStore) const*
NS(Controller_get_const_kernel_config_store)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigStore)*
NS(Controller_get_kernel_config_store)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl );

/* ========================================================================= */

#endif /* !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
}
#endif /* C++, host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_CONTROLLER_BASE_H__ */

/* end: sixtracklib/common/control/controller_base.h */
