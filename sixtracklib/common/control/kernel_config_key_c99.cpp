#include "sixtracklib/common/control/kernel_config_key.h"
#include "sixtracklib/common/control/kernel_config_key.hpp"

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <memory>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_id.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(KernelConfigKey)* NS(KernelConfigKey_create)( void )
{
    return new st::KernelConfigKey;
}

::NS(KernelConfigKey)* NS(KernelConfigKey_new)(
    NS(arch_id_t) const arch_id,
    NS(kernel_purpose_t) const purpose,
    NS(arch_variant_flags_t) const variant,
    char const* SIXTRL_RESTRICT kernel_config_str )
{
    return new st::KernelConfigKey( arch_id, purpose, variant,
        st::DEFAULT_KERNEL_ARGUMENT_SET, kernel_config_str );
}

::NS(KernelConfigKey)* NS(KernelConfigKey_new_from_copy)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT orig )
{
    return ( orig != nullptr ) ? new st::KernelConfigKey( *orig ) : nullptr;
}

::NS(KernelConfigKey)* NS(KernelConfigKey_new_from_node_id)(
    const ::NS(NodeId) *const node_id,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(arch_variant_flags_t) const variant,
    ::NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT kernel_config_str )
{
    return new st::KernelConfigKey( node_id, purpose, variant,
        argument_set, kernel_config_str );
}

NS(KernelConfigKey)* NS(KernelConfigKey_new_detailed)(
    ::NS(arch_id_t) const arch_id,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(arch_variant_flags_t) const variant,
    ::NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT kernel_config_str,
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    st::NodeId const node_id( arch_id, platform_id, device_id );
    return new st::KernelConfigKey( node_id, purpose, variant, argument_set,
        kernel_config_str );
}

void NS(KernelConfigKey_delete)( ::NS(KernelConfigKey)* SIXTRL_RESTRICT key )
{
    delete key;
}

/* ------------------------------------------------------------------------- */

::NS(arch_status_t) NS(KernelConfigKey_reset_to_default_values)(
    ::NS(KernelConfigKey)* SIXTRL_RESTRICT key )
{
    return ( key != nullptr ) ? key->reset() : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(KernelConfigKey_reset)(
    ::NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(arch_variant_flags_t) const variant,
    ::NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT conf_str )
{
    return ( key != nullptr )
        ? key->reset( key->nodeId(), purpose, variant, argument_set, conf_str )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(KernelConfigKey_reset_with_node_id)(
    ::NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    const ::NS(NodeId) *const SIXTRL_RESTRICT node_id,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(arch_variant_flags_t) const variant,
    ::NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT conf_str )
{
    return ( ( key != nullptr ) && ( node_id != nullptr ) )
        ? key->reset( node_id, purpose, variant, argument_set, conf_str )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(KernelConfigKey_reset_detailed)(
    ::NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    ::NS(arch_id_t) const arch_id,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(arch_variant_flags_t) const variant,
    ::NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT conf_str,
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    st::NodeId const node_id( arch_id, platform_id, device_id );
    return ( key != nullptr )
        ? key->reset( st::NodeId{ arch_id, platform_id, device_id },
                      purpose, variant, argument_set, conf_str )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

bool NS(KernelConfigKey_is_valid)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( key != nullptr ) && ( key->valid() ) );
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
        ? key->purpose() : st::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;
}

void NS(KernelConfigKey_set_purpose)(
    ::NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    ::NS(kernel_purpose_t) const purpose )
{
    if( key != nullptr ) key->setPurpose( purpose );
}

::NS(arch_variant_flags_t) NS(KernelConfigKey_get_variant)(
    const NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != nullptr ) ? key->variant() : st::ARCH_VARIANT_NONE;
}

bool NS(KernelConfigKey_are_variant_flags_set)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key,
    ::NS(arch_variant_flags_t) const variant_flags )
{
    return ( ( key != nullptr ) &&
             ( key->areVariantFlagsSet( variant_flags ) ) );
}

bool NS(KernelConfigKey_is_variant_debug_mode)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( key != nullptr ) && ( key->variantDebugMode() ) );
}

bool NS(KernelConfigKey_is_variant_release_mode)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( key != nullptr ) && ( key->variantReleaseMode() ) );
}

void NS(KernelConfigKey_set_variant)(
    ::NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    ::NS(arch_variant_flags_t) const variant )
{
    if( key != nullptr ) key->setVariant( variant );
}

::NS(kernel_argument_set_t) NS(KernelConfigKey_get_argument_set)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != nullptr )
        ? key->argumentSet() : st::DEFAULT_KERNEL_ARGUMENT_SET;
}

void NS(KernelConfigKey_set_argument_set)(
    ::NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    ::NS(kernel_argument_set_t) const argument_set )
{
    if( key != nullptr ) key->setArgumentSet( argument_set );
}

/* ------------------------------------------------------------------------- */

bool NS(KernelConfigKey_has_config_str)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( key != nullptr ) && ( key->hasConfigStr() ) );
}

char const* NS(KernelConfigKey_get_config_str)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( key != nullptr ) ? key->ptrConfigStr() : nullptr;
}

void NS(KernelConfigKey_set_config_str)(
    ::NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    char const* SIXTRL_RESTRICT config_str )
{
    if( key != nullptr ) key->setConfigStr( config_str );
}

/* ------------------------------------------------------------------------- */

bool NS(KernelConfigKey_has_node_id)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( key != nullptr ) && ( key->hasNodeId() ) );
}

::NS(NodeId) const* NS(KernelConfigKey_get_node_id)(
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

bool NS(KernelConfigKey_are_equal)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs )
{
    return ( ( lhs != nullptr ) && ( rhs != nullptr ) && ( *lhs == *rhs ) );
}

bool NS(KernelConfigKey_are_not_equal)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs )
{
    return ( ( ( lhs == nullptr ) && ( rhs != nullptr ) ) ||
             ( ( lhs != nullptr ) && ( rhs == nullptr ) ) ||
             ( ( lhs != nullptr ) && ( rhs != nullptr ) && ( *lhs != *rhs ) ) );
}

bool NS(KernelConfigKey_are_equal_except_purpose)(
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT lhs,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT rhs )
{
    return ( ( lhs != nullptr ) && ( rhs != nullptr ) &&
             ( lhs->isEqualExceptPurpose( *rhs ) ) );
}

/* end: sixtracklib/common/control/kernel_config_key.c */
