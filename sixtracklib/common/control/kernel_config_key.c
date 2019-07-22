#include "sixtracklib/common/control/kernel_config_key.h"

#include "sixtracklib/common/control/kernel_config_key.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(KernelConfigKey)* NS(KernelConfigKey_new)(
    ::NS(node_id_t) const arch_id,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(kernel_variant_t) const variant,
    char const* SIXTRL_RESTRICT config_str )
{
    return new st::KernelConfigKey( arch_id, purpose, variant, config_str );
}

NS(KernelConfigKey)* NS(KernelConfigKey_new_detailed)(
    ::NS(arch_id_t) const arch_id,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(kernel_variant_t) const variant,
    char const* SIXTRL_RESTRICT config_str,
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    st::NodeId const node_id( arch_id, platform_id, device_id );
    return new st::KernelConfigKey( node_id, purpose, variant, config_str );
}

void NS(KernelConfigKey_delete)( ::NS(KernelConfigKey)* SIXTRL_RESTRICT key )
{
    delete key;
}

/* ------------------------------------------------------------------------- */

::NS(arch_id_t) NS(KernelConfigKey_get_arch_id)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != nullptr ) ? key->archId() : st::ARCHITECTURE_ILLEGAL;
}

::NS(kernel_purpose_t) NS(KernelConfigKey_get_purpose)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != nullptr )
        ? key->purpose : st::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;
}

::NS(kernel_variant_t) NS(KernelConfigKey_get_variant)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != nullptr )
        ? key->variant() : st::KERNEL_CONFIG_VARIANT_NONE;
}

/* ------------------------------------------------------------------------- */

bool NS(KernelConfigKey_has_config_str)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( key != nullptr ) && ( key->hasConfigStr() ) );
}

char const* NS(KernelConfigKey_config_str)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != nullptr ) ? key->ptrConfigstr() : nullptr;
}

bool NS(KernelConfigKey_has_node_id)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( key != nullptr ) && ( key->hasNodeId() ) );
}

::NS(node_id_t) const* NS(KernelConfigKey_get_node_id)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != nullptr ) ? key->ptrNodeId() : nullptr;
}

/* ------------------------------------------------------------------------- */

::NS(node_platform_id_t) NS(KernelConfigKey_get_platform_id)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != nullptr )
        ? key->platformId() : st::NODE_ILLEGAL_PLATFORM_ID;
}

::NS(node_device_id_t) NS(KernelConfigKey_get_device_id)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != nullptr )
        ? key->deviceId() : st::NODE_ILLEGAL_DEVICE_ID;
}

/* ------------------------------------------------------------------------- */

int NS(KernelConfigKey_compare)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs )
{
    int cmp_result = -1;

    if( ( lhs != nullptr ) && ( rhs != nullptr ) )
    {
        cmp_result = lhs->compare( *rhs );
    }
    else if( rhs != nullptr )
    {
        cmp_result = +1;
    }

    return cmp_result;
}


/* end: sixtracklib/common/control/kernel_config_key.c */
