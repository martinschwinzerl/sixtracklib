#include "sixtracklib/common/control/kernel_config_store.h"
#include "sixtracklib/common/control/kernel_config_store.hpp"

#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/common/control/node_id.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;
using _store_t = st::KernelConfigStore;

::NS(KernelConfigStore)* NS(KernelConfigStore_create)( void )
{
    return new st::KernelConfigStore;
}

void NS(KernelConfigStore_delete)(
    NS(KernelConfigStore)* SIXTRL_RESTRICT store )
{
    delete store;
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(KernelConfigStore_get_num_kernel_sets)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store )
{
    return ( store != nullptr ) ? store->numKernelSets() : st::arch_size_t{ 0 };
}

::NS(kernel_set_id_t) NS(KernelConfigStore_add_kernel_set)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    ::NS(KernelSetBase)* ptr_kernel_set_to_take_ownership )
{
    st::kernel_set_id_t kernel_set_id = _store_t::ILLEGAL_KERNEL_SET_ID;

    if( store != nullptr )
    {
        std::unique_ptr< _store_t::kernel_set_t > ptr(
            ptr_kernel_set_to_take_ownership );

        kernel_set_id = store->addKernelSet( std::move( ptr ) );
    }

    return kernel_set_id;
}

bool NS(KernelConfigStore_has_kernel_set)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    NS(kernel_set_id_t) const kernel_set_id )
{
    return ( ( store != nullptr ) &&
             ( kernel_set_id != _store_t::ILLEGAL_KERNEL_SET_ID ) &&
             ( store->hasKernelSet( kernel_set_id ) ) );
}

bool NS(KernelConfigStore_has_kernel_set_by_ptr)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(KernelSetBase) *const SIXTRL_RESTRICT kernel_set )
{
    return ( ( store != nullptr ) && ( kernel_set != nullptr ) &&
             ( store->hasKernelSet( *kernel_set ) ) );
}

::NS(arch_status_t) NS(KernelConfigStore_update_kernel_set)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    ::NS(kernel_set_id_t) const kernel_set_id )
{
    return ( ( store != nullptr ) &&
             ( kernel_set_id != _store_t::ILLEGAL_KERNEL_SET_ID ) )
        ? store->updateKernelSet( kernel_set_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(kernel_set_id_t) NS(KernelConfigStore_get_kernel_set_id)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(KernelSetBase) *const SIXTRL_RESTRICT kernel_set )
{
    return ( ( store != nullptr ) && ( kernel_set != nullptr ) )
        ? store->kernelSetId( *kernel_set )  : _store_t::ILLEGAL_KERNEL_SET_ID;
}

::NS(KernelSetBase) const* NS(KernelConfigStore_get_ptr_const_kernel_set)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    ::NS(kernel_set_id_t) const kernel_set_id )
{
    return ( store != nullptr )
        ? store->ptrKernelSetBase( kernel_set_id ) : nullptr;
}

::NS(KernelSetBase)* NS(KernelConfigStore_get_ptr_kernel_set_base)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    ::NS(kernel_set_id_t) const kernel_set_id )
{
    return ( store != nullptr )
        ? store->ptrKernelSetBase( kernel_set_id ) : nullptr;
}

::NS(arch_status_t) NS(KernelConfigStore_remove_kernel_set)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    ::NS(kernel_set_id_t) const kernel_set_id )
{
    return ( store != nullptr )
        ? store->removeKernelSet( kernel_set_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

::NS(ctrl_kernel_id_t) NS(KernelConfigStore_add_kernel_config)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    ::NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    ::NS(KernelConfigBase)* SIXTRL_RESTRICT ptr_kernel_conf_to_take_ownership )
{
    ::NS(ctrl_kernel_id_t) kernel_id = _store_t::ILLEGAL_KERNEL_CONFIG_ID;

    if( ( store != nullptr ) && ( key != nullptr ) &&
        ( ptr_kernel_conf_to_take_ownership ) )
    {
        std::unique_ptr< _store_t::kernel_config_base_t >
            ptr( ptr_kernel_conf_to_take_ownership );

        kernel_id = store->addKernelConfig( *key, std::move( ptr ) );
    }

    return kernel_id;
}

::NS(arch_status_t) NS(KernelConfigStore_add_kernel_config_to_key_mapping)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    ::NS(KernelConfigKey)* SIXTRL_RESTRICT key,
    ::NS(ctrl_kernel_id_t) const kernel_config_id )
{
    return ( ( store != nullptr ) && ( key != nullptr ) )
        ? store->addKernelConfig( *key, kernel_config_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}


::NS(arch_status_t) NS(KernelConfigStore_remove_kernel_config_by_key)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT_REF key )
{
    return ( ( store != nullptr ) && ( key != nullptr ) )
        ? store->removeKernelConfig( *key )
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

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(KernelConfigStore_get_num_stored_kernels)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store )
{
    return ( store != nullptr )
        ? store->numStoredKernels() : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(KernelConfigStore_get_num_kernel_config_keys)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    ::NS(arch_kernel_id_t) const kernel_id )
{
    return ( store != nullptr )
        ? store->numKernelConfigKeys( kernel_id ) : ::NS(arch_size_t){ 0 };
}

/* ----------------------------------------------------------------- */

bool NS(KernelConfigStore_has_kernel)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    ::NS(ctrl_kernel_id_t) const kernel_config_id )
{
    return ( ( store != nullptr ) && ( store->hasKernel( kernel_config_id ) ) );
}

bool NS(KernelConfigStore_has_kernel_by_key)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( store != nullptr ) && ( key != nullptr ) &&
             ( store->hasKernel( *key ) ) );
}

bool NS(KernelConfigStore_has_kernel_by_ptr_config_base)(
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
    ::NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT config_str )
{
    std::string const _config_str = (
        ( config_str != nullptr ) && ( std::strlen( config_str ) ) )
            ? std::string{ config_str } : std::string{};

    return ( ( store != nullptr ) && ( store->hasKernel(
        arch_id, purpose, variant, argument_set, _config_str ) ) );
}

bool NS(KernelConfigStore_has_kernel_by_node_id_purpose_variant)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(NodeId) *const SIXTRL_RESTRICT node_id,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(kernel_variant_t) const variant,
    ::NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT config_str )
{
    return ( ( store != nullptr ) && ( store->hasKernel(
        st::KernelConfigStore::kernel_config_key_t{ node_id, purpose,
            variant, argument_set, config_str  } ) ) );
}

bool NS(KernelConfigStore_has_kernel_by_id)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    ::NS(arch_kernel_id_t) const kernel_id )
{
    return ( ( store != nullptr ) && ( store->hasKernel( kernel_id ) ) );
}

::NS(arch_kernel_id_t) NS(KernelConfigStore_get_kernel_id_by_kernel_id)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    ::NS(ctrl_kernel_id_t) const kernel_config_id )
{
    return ( store != nullptr ) ? store->kernelId( kernel_config_id )
        : _store_t::ILLEGAL_KERNEL_CONFIG_ID;
}

::NS(arch_kernel_id_t) NS(KernelConfigStore_get_kernel_id_by_key)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT_REF key )
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
    ::NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT config_str )
{
    using _this_t = st::KernelConfigStore;
    return ( store != nullptr )
        ? store->kernelId( _this_t::kernel_config_key_t{ arch_id, purpose,
            variant, argument_set, config_str } )
        : _this_t::ILLEGAL_KERNEL_CONFIG_ID;
}

::NS(arch_kernel_id_t)
NS(KernelConfigStore_get_kernel_id_by_node_id_detailed)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(NodeId) *const SIXTRL_RESTRICT node_id,
    ::NS(kernel_purpose_t) const purpose, ::NS(kernel_variant_t) const variant,
    ::NS(kernel_argument_set_t) const argument_set,
    char const* SIXTRL_RESTRICT config_str )
{
    using _this_t = st::KernelConfigStore;
    return ( store != nullptr )
        ? store->kernelId( _this_t::kernel_config_key_t{ node_id, purpose,
            variant, argument_set, config_str } )
        : _this_t::ILLEGAL_KERNEL_CONFIG_ID;
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

/* ------------------------------------------------------------------------- */

::NS(ctrl_kernel_id_t) NS(KernelConfigStore_init_kernel_config)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( store != nullptr ) && ( key != nullptr ) )
        ? store->initKernelConfig( *key )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(ctrl_kernel_id_t) NS(KernelConfigStore_init_kernel_config_detailed)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key,
    ::NS(arch_size_t) const num_kernel_args,
    char const* SIXTRL_RESTRICT kernel_name )
{
    return ( ( store != nullptr ) && ( key != nullptr ) )
        ? store->initKernelConfig( *key, num_kernel_args, kernel_name )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

::NS(arch_status_t)
NS(KernelConfigStore_set_default_init_kernel_config_parameters)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key,
    ::NS(arch_size_t) const num_kernel_arguments,
    char const* SIXTRL_RESTRICT kernel_name )
{
    return ( ( store != nullptr ) && ( key != nullptr ) )
        ? store->setDefaultInitKernelConfigParameters(
                *key, num_kernel_arguments, kernel_name )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t)
NS(KernelConfigStore_remove_default_init_kernel_config_parameters)(
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( store != nullptr ) && ( key != nullptr ) )
        ? store->removeDefaultInitKernelConfigParameters( *key )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

bool NS(KernelConfigStore_has_default_init_kernel_config_parameters)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( store != nullptr ) && ( key != nullptr ) &&
             ( store->hasDefaultInitKernelConfigParameters( *key ) ) );
}

::NS(arch_size_t) NS(KernelConfigStore_get_default_num_kernel_args)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( store != nullptr ) && ( key != nullptr ) )
        ? store->defaultNumKernelArgs( *key ) : st::arch_size_t{ 0 };
}

char const* NS(KernelConfigStore_get_default_kernel_name)(
    const ::NS(KernelConfigStore) *const SIXTRL_RESTRICT store,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
{
    return ( ( store != nullptr ) && ( key != nullptr ) )
        ? store->ptrDefaultKernelName( *key ) : nullptr;
}

/* end: sixtracklib/common/control/kernel_config_store_c99.cpp */
