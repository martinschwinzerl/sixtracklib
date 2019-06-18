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

bool NS(KernelConfig_has_kernel_id)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT conf )
{
    return ( ( conf != nullptr ) && ( conf->hasKernelId() ) );
}

NS(ctrl_kernel_id_t) NS(KernelConfig_get_kernel_id)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT conf )
{
    return ( conf != nullptr )
        ? conf->kernelId() : ::NS(ARCH_ILLEGAL_KERNEL_ID);
}

void NS(KernelConfig_set_kernel_id)(
    ::NS(KernelConfigBase)* SIXTRL_RESTRICT conf,
    NS(ctrl_kernel_id_t) const kernel_id )
{
    if( conf != nullptr ) conf->setKernelId( kernel_id );
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

::NS(ctrl_size_t) NS(KernelConfig_get_num_arguments)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT conf )
{
    return ( conf != nullptr ) ? conf->numArguments() : ::NS(ctrl_size_t){ 0 };
}

void NS(KernelConfig_set_num_arguments)(
    ::NS(KernelConfigBase)* SIXTRL_RESTRICT conf,
    ::NS(ctrl_size_t) const num_kernel_args )
{
    if( conf != nullptr ) conf->setNumArguments( num_kernel_args );
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

::NS(ctrl_status_t) NS(KernelConfig_update)(
    ::NS(KernelConfigBase)* SIXTRL_RESTRICT conf )
{
    return ( conf != nullptr )
        ? conf->update() : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

/* ------------------------------------------------------------------------- */

::NS(kernel_config_variant_t) NS(KernelConfig_get_variant_flags)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr )
        ? config->variantFlags() : ::NS(KERNEL_CONFIG_VARIANT_NONE);
}

bool NS(KernelConfig_has_variant_flags)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    NS(kernel_config_variant_t) const flags_to_check )
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

void NS(KernelConfig_set_variant_flags)(
    ::NS(KernelConfigBase)* SIXTRL_RESTRICT config,
    ::NS(kernel_config_variant_t) const variant_flags )
{
    if( config != nullptr ) config->setVariantFlags( variant_flags );
}

/* ------------------------------------------------------------------------- */

bool NS(KernelConfig_has_nodes)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( ( config != nullptr ) && ( config->hasNodes() ) );
}

::NS(arch_size_t) NS(KernelConfig_get_num_nodes)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr ) ? config->numNodes() : ::NS(arch_size_t){ 0 };
}

::NS(NodeId) const* NS(KernelConfig_get_const_node)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const num_node_in_list )
{
    return ( config != nullptr )
        ? config->ptrNode( num_node_in_list ) : nullptr;
}

::NS(NodeId)* NS(KernelConfig_get_node)(
    ::NS(KernelConfigBase)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const num_node_in_list )
{
    return ( config != nullptr )
        ? config->ptrNode( num_node_in_list ) : nullptr;
}

::NS(arch_status_t) NS(KernelConfig_assign_to_node)(
    ::NS(KernelConfigBase)* SIXTRL_RESTRICT config,
    const ::NS(NodeId) *const SIXTRL_RESTRICT ptr_node )
{
    return ( ( config != nullptr ) && ( ptr_node != nullptr ) )
        ? config->assignToNode( *ptr_node )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

bool NS(KernelConfig_is_assigned_to_node)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    const ::NS(NodeId) *const SIXTRL_RESTRICT ptr_node )
{
    return ( ( config != nullptr ) && ( ptr_node != nullptr ) &&
             ( config->isAssignedToNode( *ptr_node ) ) );
}

bool NS(KernelConfig_is_assigned_to_node_with_platform_and_device_id)(
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT config,
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    return ( ( config != nullptr ) &&
             ( config->isAssignedToNode( platform_id, device_id ) ) );
}

::NS(arch_status_t) NS(KernelConfig_detach_from_node)(
    ::NS(KernelConfigBase)* SIXTRL_RESTRICT conf,
    const ::NS(NodeId) *const SIXTRL_RESTRICT ptr_node )
{
    return ( ( config != nullptr ) && ( ptr_node != nullptr ) )
        ? config->detachFromNode( *ptr_node )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t)
NS(KernelConfig_detach_from_node_with_platform_id_and_device_id)(
    ::NS(KernelConfigBase)* SIXTRL_RESTRICT conf,
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    return ( config != nullptr )
        ? config->detachFromNode( platform_id, device_id )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

/* ------------------------------------------------------------------------- */

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
