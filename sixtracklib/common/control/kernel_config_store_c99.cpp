#include "sixtracklib/common/control/kernel_config_store.h"
#include "sixtracklib/commom/control/kernel_config_store.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(KernelConfigStore)* NS(KernelConfigStore_new)( void )
{
    new st::KernelConfigStore;
}

void NS(KernelConfigStore_delete)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store )
{
    delete store;
}

/* ----------------------------------------------------------------- */

::NS(arch_status_t) NS(KernelConfigStore_remove_kernel_config_by_key)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT_REF key )
{
    return ( store != nullptr )
        ? store->removeKernelConfig( key )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(KernelConfigStore_remove_kernel_config)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT kernel_config )
{
    return ( ( store != nullptr ) && ( kernel_config != nullptr ) )
        ? store->removeKernelConfig( *kernel_config )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(KernelConfigStore_remove_kernel_config_by_id)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    ::NS(arch_kernel_id_t) const kernel_id )
{
    return ( store != nullptr )
        ? store->removeKernelConfig( kernel_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ----------------------------------------------------------------- */

::NS(arch_size_t) NS(KernelConfigStore_num_stored_kernels)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store )
{
    return ( store != nullptr )
        ? store->numStoredKernesl() : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(KernelConfigStore_num_keys)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    ::NS(arch_kernel_id_t) const kernel_id )
{
    return ( store != nullptr )
        ? store->numKeys( kernel_id ) : ::NS(arch_size_t){ 0 };
}

/* ----------------------------------------------------------------- */

bool NS(KernelConfigStore_has_kernel_by_key(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( store != nullptr ) && ( key != nullptr ) &&
             ( store->hasKernel( *key ) ) );
}

bool NS(KernelConfigStore_has_kernel)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT kernel_config )
{
    return ( ( store != nullptr ) && ( kernel_config != nullptr ) &&
             ( store->hasKernel( *kernel_config ) ) );
}

bool NS(KernelConfigStore_has_kernel_detailed)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    ::NS(arch_id_t) const arch_id,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(kernel_variant_t) const variant,
    char const* SIXTRL_RESTRICT config_str )
{
    std::string const _config_str = (
        ( config_str != nullptr ) && ( std::strlen( config_str ) ) )
            ? std::string{ config_str } : std::string{};

    return ( ( store != nullptr ) && ( store->hasKernel(
        arch_id, purpose, variant, _config_str ) ) );
}

bool NS(KernelConfigStore_has_kernel_by_node_id_purpose_variant)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(NodeId) *const SIXTRL_RESTRICT node_id,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(kernel_variant_t) const variant,
    char const* SIXTRL_RESTRICT config_str )
{
    std::string const _config_str = (
        ( config_str != nullptr ) && ( std::strlen( config_str ) ) )
            ? std::string{ config_str } : std::string{};

    return ( ( store != nullptr ) && ( node_id != nullptr ) &&
             ( store->hasKernel( *node_id, purpose, variant, _config_str ) ) );
}

bool NS(KernelConfigStore_has_kernel_by_id)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    ::NS(arch_kernel_id_t) const kernel_id )
{
    return ( ( store != nullptr ) && ( store->hasKernel( kernel_id ) ) );
}

::NS(arch_kernel_id_t) NS(KernelConfigStore_get_kernel_id_by_key)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT_REF key ) const
{
    return ( ( store != nullptr ) && ( key != nullptr ) )
        ? store->kernelId( *key ) : st::ARCH_ILLEGAL_KERNEL_ID;
}

::NS(arch_kernel_id_t) NS(KernelConfigStore_get_kernel_id)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(KernelConfigBase) *const SIXTRL_RESTRICT kernel_config )
{
    return ( ( store != nullptr ) && ( kernel_config != nullptr ) )
        ? store->kernelId( *kernel_config ) : st::ARCH_ILLEGAL_KERNEL_ID;
}

::NS(arch_kernel_id_t) NS(KernelConfigStore_get_kernel_id_detailed)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    ::NS(arch_id_t) const arch_id,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(kernel_variant_t) const variant,
    char const* SIXTRL_RESTRICT config_str )
{
    std::string const _config_str = (
        ( config_str != nullptr ) && ( std::strlen( config_str ) ) )
            ? std::string{ config_str } : std::string{};

    return ( ( store != nullptr ) && ( store->kernelId(
        arch_id, purpose, variant, _config_str ) ) );
}

::NS(arch_kernel_id_t)
NS(KernelConfigStore_get_kernel_id_by_node_id_purpose_variant)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(NodeId) *const SIXTRL_RESTRICT node_id,
    ::NS(kernel_purpose_t) const purpose, NS(kernel_variant_t) const variant,
    char const* SIXTRL_RESTRICT config_str )
{
    std::string const _config_str = (
        ( config_str != nullptr ) && ( std::strlen( config_str ) ) )
            ? std::string{ config_str } : std::string{};

    return ( ( store != nullptr ) && ( node_id != nullptr ) &&
        ( store->kernelId( *node_id, purpose, variant, _config_str ) ) );
}

/* ----------------------------------------------------------------- */

::NS(KernelConfigBase) const*
NS(KernelConfigStore_get_const_ptr_kernel_config_base)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    ::NS(arch_kernel_id_t) const kernel_id )
{
    return ( store != nullptr )
        ? store->ptrKernelConfigBase( kernel_id ) : nullptr;
}

::NS(KernelConfigBase)*
NS(KernelConfigStore_get_ptr_kernel_config_base)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    ::NS(arch_kernel_id_t) const kernel_id )
{
    return ( store != nullptr )
        ? store->ptrKernelConfigBase( kernel_id ) : nullptr;
}

/* end: sixtracklib/common/control/kernel_config_store_c99.cpp */
