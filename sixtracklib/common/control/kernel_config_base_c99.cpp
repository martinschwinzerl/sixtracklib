#include "sixtracklib/common/control/kernel_config_base.h"

#include <cstddef>
#include <cstdlib>
#include <cstdio>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#include "sixtracklib/common/control/kernel_config_base.hpp"

void NS(KernelConfig_delete)( ::NS(KernelConfigBase)* SIXTRL_RESTRICT config )
{
    if( config != nullptr ) delete config;
    return;
}

/* ------------------------------------------------------------------------- */

::NS(arch_id_t) NS(KernelConfig_get_arch_id)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr )
        ? config->archId() : ::NS(ARCHITECTURE_ILLEGAL);
}

bool NS(KernelConfig_has_arch_string)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( ( config != nullptr ) && ( config->hasArchStr() ) );
}

char const* NS(KernelConfig_get_ptr_arch_string)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr ) ? config->ptrArchStr() : nullptr;
}

/* ------------------------------------------------------------------------- */

bool NS(KernelConfig_has_name)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT conf )
{
    return ( ( conf != nullptr ) && ( conf->hasName() ) );
}

char const* NS(KernelConfig_get_ptr_name_string)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT conf )
{
    return ( conf != nullptr ) ? conf->ptrNameStr() : nullptr;
}

void NS(KernelConfig_set_name)( ::NS(KernelConfigBase)* SIXTRL_RESTRICT conf,
    char const* SIXTRL_RESTRICT kernel_name )
{
    if( conf != nullptr ) conf->setName( kernel_name );
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(KernelConfig_get_num_arguments)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT conf )
{
    return ( conf != nullptr ) ? conf->numArguments() : ::NS(arch_size_t){ 0 };
}

::NS(arch_status_t) NS(KernelConfig_set_num_arguments)(
    ::NS(KernelConfigBase)* SIXTRL_RESTRICT conf,
    ::NS(arch_size_t) const num_kernel_args )
{
    return ( conf != nullptr )
        ? conf->setNumArguments( num_kernel_args )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

void NS(KernelConfig_clear)( ::NS(KernelConfigBase)* SIXTRL_RESTRICT conf )
{
    if( conf != nullptr ) conf->clear();
}

bool NS(KernelConfig_needs_update)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT conf )
{
    return ( ( conf != nullptr ) && ( conf->needsUpdate() ) );
}

bool NS(KernelConfig_performs_auto_update)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( ( config != nullptr ) && ( config->performsAutoUpdate() ) );
}

::NS(arch_status_t) NS(KernelConfig_update)(
    ::NS(KernelConfigBase)* SIXTRL_RESTRICT conf )
{
    return ( conf != nullptr )
        ? conf->update() : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

/* ------------------------------------------------------------------------- */

::NS(kernel_variant_t) NS(KernelConfig_get_variant_flags)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr )
        ? config->variantFlags() : ::NS(KERNEL_CONFIG_VARIANT_NONE);
}

bool NS(KernelConfig_has_variant_flags)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    NS(kernel_variant_t) const flags_to_check )
{
    return ( ( config != nullptr ) &&
             ( config->areVariantFlagsSet( flags_to_check ) ) );
}

bool NS(KernelConfig_is_variant_debug_mode)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( ( config != nullptr ) && ( config->variantDebugMode() ) );
}

bool NS(KernelConfig_is_variant_release_mode)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( ( config != nullptr ) && ( config->variantReleaseMode() ) );
}

/* ------------------------------------------------------------------------- */

bool NS(KernelConfig_has_specified_purpose)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( ( config != nullptr ) && ( config->hasSpecifiedPurpose() ) );
}

bool NS(KernelConfig_has_predefined_purpose)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( ( config != nullptr ) && ( config->hasPredefinedPurpose() ) );
}

bool NS(KernelConfig_has_userdefined_purpose)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( ( config != nullptr ) && ( config->hasUserdefinedPurpose() ) );
}

::NS(kernel_purpose_t) NS(KernelConfig_get_purpose)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr )
        ? config->purpose() : st::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(KernelConfig_required_string_representation_capacity)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr )
        ? config->requiredOutStringLength() : ::NS(arch_size_t){ 0 };
}

::NS(arch_status_t) NS(KernelConfig_to_string)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const out_str_capacity, char* SIXTRL_RESTRICT out_str )
{
    return ( config != nullptr )
        ? config->toString( out_str_capacity, out_str )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

void NS(KernelConfig_print)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT conf,
    ::FILE* SIXTRL_RESTRICT output )
{
    if( conf != nullptr ) conf->print( output );
}

void NS(KernelConfig_print_out)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT conf )
{
    if( conf != nullptr ) conf->printOut();
}

#endif /* C++, Host */

/* end: sixtracklib/common/control/kernel_config_base_c99.cpp */
