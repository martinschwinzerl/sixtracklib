#include "sixtracklib/common/control/kernel_config_key.h"


NS(KernelConfigKey)* NS(KernelConfigKey_preset)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key )
{
    if( key != SIXTRL_NULLPTR )
    {
        NS(NodeId_preset)( &key->node_id );
        key->purpose = NS(KERNEL_CONFIG_PURPOSE_UNSPECIFIED);
        key->variant = NS(KERNEL_CONFIG_VARIANT_NONE);
    }

    return key;
}

NS(arch_status_t) NS(KernelConfigKey_init)(
    NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    const NS(NodeId) *const SIXTRL_RESTRICT node,
    NS(kernel_purpose_t) const purpose, NS(Kernel_variant_t) const variant )
{
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( key != SIXTRL_NULLPTR ) &&
        ( node_id != SIXTRL_NULLPTR ) &&
        ( NS(NodeId_is_valid)( node_id ) ) &&
        ( purpose != NS(KERNEL_CONFIG_PURPOSE_UNSPECIFIED) ) )
    {
        key->node_id = *node_id;
        key->purpose = purpose;
        key->variant = variant;

        status = NS(ARCH_STATUS_SUCCESS);
    }

    return status;
}


bool NS(KernelConfigKey_is_valid)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( key != SIXTRL_NULLPTR ) &&
             ( NS(NodeId_is_valid)( key->node_id ) ) &&
             ( key->purpose != NS(KERNEL_CONFIG_PURPOSE_UNSPECIFIED) ) );
}

NS(arch_id_t) NS(KernelConfigKey_get_arch_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != SIXTRL_NULLPTR )
        ? NS(NodeId_get_arch_id)( &key->node_id )
        : NS(ARCHITECTURE_ILLEGAL);
}

NS(node_platform_id_t) NS(KernelConfigKey_get_platform_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != SIXTRL_NULLPTR )
        ? NS(NodeId_get_platform_id)( &key->node_id )
        : NS(NODE_ILLEGAL_PLATFORM_ID);
}

NS(node_device_id_t) NS(KernelConfigKey_get_device_id)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != SIXTRL_NULLPTR )
        ? NS(NodeId_get_device_id)( &key->node_id )
        : NS(NODE_ILLEGAL_DEVICE_ID);
}

bool NS(KernelConfigKey_is_smaller_than)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs )
{
    bool const is_smaller = false;

    if( NS(NodeId_is_smaller_than)( &lhs->node_id, &rhs->node_id ) )
    {
        is_smaller = true;
    }
    else if( NS(NodeId_are_equal)( &lhs->node_id, &rhs->node_id ) )
    {
        SIXTRL_ASSERT( lhs != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( rhs != SIXTRL_NULLPTR );

        if( ( lhs->purpose < rhs->purpose ) ||
            ( ( lhs->purpose == rhs->purpose ) &&
              ( lhs->variant <  rhs->variant ) ) )
        {
            is_smaller = true;
        }
    }

    return is_smaller;
}

bool NS(KernelConfigKey_are_equal)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs )
{
    return ( ( NS(NodeId_are_equal)( &lhs->node_id, &rhs->node_id ) ) &&
             ( NS(KernelConfigKey_get_purpose)( lhs ) ==
               NS(KernelConfigKey_get_purpose)( rhs ) ) &&
             ( NS(KernelConfigKey_get_variant)( lhs ) ==
               NS(KernelConfigKey_get_variant)( rhs ) ) );
}

int NS(KernelConfigKey_compare)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs )
{
    int cmp_result = -1;

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {

    }

    return cmp_result;
}

/* end: sixtracklib/common/control/kernel_config_key.c */
