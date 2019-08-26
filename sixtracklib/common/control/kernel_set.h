#ifndef SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_SET_C99_H__
#define SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_SET_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/kernel_set.hpp"
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/kernel_config_key.h"
    #include "sixtracklib/common/control/kernel_config_base.h"
    #include "sixtracklib/common/control/kernel_config_store.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(kernel_purpose_t)
NS(KernelSet_get_default_controller_purpose)( NS(arch_size_t) const ii );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(KernelSet_get_num_default_controller_purposes)();

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(kernel_purpose_t)
NS(KernelSet_get_default_track_job_purpose)( NS(arch_size_t) const ii );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(KernelSet_get_num_default_track_job_purposes)();

/* ========================================================================= */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelSetBase)* NS(KernelSetBase_new)(
    NS(arch_id_t) const arch_id,
    NS(KernelConfigStore)* SIXTRL_RESTRICT kernel_conf_store );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelSetBase)* NS(KernelSetBase_new_detailed)(
    NS(arch_id_t) const arch_id,
    NS(KernelConfigStore)* SIXTRL_RESTRICT kernel_conf_store,
    NS(arch_size_t) const num_purposes,
    NS(kernel_purpose_t) const* SIXTRL_RESTRICT purposes_begin );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelSet_delete)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_is_for_controllers)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_is_for_track_jobs)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(KernelSet_get_num_of_purposes)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(KernelSet_get_num_of_purposes_for_kernel_config_id)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    NS(ctrl_kernel_id_t) const kernel_config_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(KernelSet_get_num_of_pinned_purposes)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigBase) const*
NS(KernelSet_get_ptr_const_kernel_config_base)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigBase)*
NS(KernelSet_get_ptr_kernel_config_base)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ctrl_kernel_id_t)
NS(KernelSet_get_kernel_config_id)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_has_kernel_config_id)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    NS(ctrl_kernel_id_t) const kernel_config_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(KernelSet_is_purpose_associated_with_kernel_config_id)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    NS(ctrl_kernel_id_t) const kernel_config_id,
    NS(kernel_purpose_t) const purpose );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigKey) const*
NS(KernelSet_get_ptr_const_kernel_config_key)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigKey) const*
NS(KernelSet_get_ptr_const_current_config_key)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(kernel_set_id_t)
NS(KernelSet_get_kernel_set_id)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelSet_set_kernel_set_id)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set,
    NS(kernel_set_id_t) const kernel_set_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_requires)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_is_pinned)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_is_available)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_are_all_available)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_has_kernel_config_key)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_can_switch_kernel)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_can_switch_all_kernels)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    NS(KernelConfigKey)* SIXTRL_RESTRICT key );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelSet_switch_kernel)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT_REF key,
    bool is_pinned_flag );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelSet_switch_kernels)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelSet_sync_with_store)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set,
    bool const perform_config_update_if_required );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelSet_sync_with_store_and_assign_key)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key,
    bool const perform_config_update_if_required );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelSet_update_kernel_op_flags)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(kernel_op_flags_t)
NS(KernelSet_get_kernel_op_flags)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_config_needs_update)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelSet_update_config)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelSet_update_all_configs)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_is_ready)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_is_ready_by_key)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_are_ready)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelSet_reset)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelSet_reset_for_purpose)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelSet_reset_kernel_config)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set,
    NS(ctrl_kernel_id_t) const kernel_config_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelSet_add_purpose)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelSet_add_purposes)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set,
    NS(arch_size_t) const num_purposes,
    NS(kernel_purpose_t) const* SIXTRL_RESTRICT purposes_begin );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelSet_remove_purpose)(
    NS(KernelSetBase)* SIXTRL_RESTRICT set,
    NS(kernel_purpose_t) const purpose );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_UINT64_T NS(KernelSet_get_sync_id_value)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelSet_is_sync_with)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set,
    SIXTRL_UINT64_T const sync_id_value );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigStore) const*
NS(KernelSet_get_const_kernel_config_store)(
    const NS(KernelSetBase) *const SIXTRL_RESTRICT set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(KernelConfigStore)*
NS(KernelSet_get_kernel_config_store)( NS(KernelSetBase)* SIXTRL_RESTRICT set );

/* ========================================================================= */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ControllerKernelSetBase)*
NS(ControllerKernelSet_new)(
    NS(arch_id_t) const arch_id,
    NS(KernelConfigStore)* SIXTRL_RESTRICT kernel_conf_store );

/* ----------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(ControllerKernelSet_init_default_controller_kernels)(
    NS(ControllerKernelSetBase)* SIXTRL_RESTRICT ctrl );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(ControllerKernelSet_configure_default_controller_kernels)(
    NS(ControllerKernelSetBase)* SIXTRL_RESTRICT ctrl );

/* ----------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_kernel_id_t)
NS(ControllerKernelSet_init_remap_buffer_kernel_config)(
    NS(ControllerKernelSetBase)* SIXTRL_RESTRICT ctrl,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(ControllerKernelSet_configure_remap_buffer_kernel_config)(
    NS(ControllerKernelSetBase)* SIXTRL_RESTRICT ctrl );


#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_SET_C99_H__ */

/* end: sixtracklib/common/control/kernel_config_set.h */
