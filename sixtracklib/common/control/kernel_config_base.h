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

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_has_name)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(KernelConfig_get_ptr_name_string)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfig_set_name)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config,
    char const* SIXTRL_RESTRICT kernel_name );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(KernelConfig_get_num_arguments)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(KernelConfig_set_num_arguments)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config,
    NS(arch_size_t) const num_kernel_args );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(kernel_variant_t)
NS(KernelConfig_get_variant_flags)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_are_variant_flags_set)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    NS(kernel_variant_t) const flags_to_check );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_is_variant_debug_mode)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_is_variant_release_mode)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_has_specified_purpose)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_has_predefined_purpose)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_has_userdefined_purpose)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(kernel_purpose_t) NS(KernelConfig_get_purpose)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(KernelConfig_clear)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_needs_update)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(KernelConfig_performs_auto_update)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(KernelConfig_update)(
    NS(KernelConfigBase)* SIXTRL_RESTRICT config );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(KernelConfig_required_string_representation_capacity)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config );

SIXTRL_HOST_FN NS(arch_status_t) NS(KernelConfig_to_string)(
    const NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    NS(arch_size_t) const out_str_capacity, char* SIXTRL_RESTRICT out_str );

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
