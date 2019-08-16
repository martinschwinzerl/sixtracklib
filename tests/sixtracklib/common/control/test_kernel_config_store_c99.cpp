#include "sixtracklib/common/control/kernel_config_store.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/architecture.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/kernel_config_key.h"
#include "sixtracklib/common/control/kernel_config_base.h"
#include "sixtracklib/testlib.h"

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        template< typename... Args >
        ::NS(KernelConfigBase)* KernelConfigBase_new( Args&&... args )
        {
            return new SIXTRL_CXX_NAMESPACE::KernelConfigBase(
                std::forward< Args >( args )... );
        }
    }
}

TEST( C99_CommonControlKernelStoreCommonTests, AddRemoveKernelConfigs )
{
    using store_t        = ::NS(KernelConfigStore);
    using kernel_id_t    = ::NS(ctrl_kernel_id_t);
    using key_t          = ::NS(KernelConfigKey);
    using config_base_t  = ::NS(KernelConfigBase);
    using size_t         = ::NS(arch_size_t);
    using arch_id_t      = ::NS(arch_id_t);
    using status_t       = ::NS(arch_status_t);
    using argument_set_t = ::NS(kernel_argument_set_t);

    /* Verify that a suitable arch is available */
    ::NS(Architectures) const* ptr_archs = ::NS(Architectures_get_ptr_const)();
    SIXTRL_ASSERT( ptr_archs != nullptr );
    SIXTRL_ASSERT( ::NS(Architectures_get_num_architectures)( ptr_archs ) >
        size_t{ 0 } );

    arch_id_t const arch_id = ::NS(Architectures_get_arch_id_by_number)(
        ptr_archs, size_t{ 0 } );
    SIXTRL_ASSERT( arch_id != ::NS(ARCHITECTURE_ILLEGAL) );
    SIXTRL_ASSERT( arch_id != ::NS(ARCHITECTURE_NONE) );
    SIXTRL_ASSERT(  ::NS(Architectures_has_architecture)( ptr_archs, arch_id ) );
    SIXTRL_ASSERT(  ::NS(Architectures_has_arch_str)( ptr_archs, arch_id ) );

    /* --------------------------------------------------------------------- */
    /* Create an empty store */

    store_t* store = ::NS(KernelConfigStore_create)();
    SIXTRL_ASSERT( store != nullptr );

    /* --------------------------------------------------------------------- */
    /* Verify that the store is indeed empty and does not contain any kernel
     * configs */
    ASSERT_TRUE(  ::NS(KernelConfigStore_get_num_kernel_sets)(
        store ) == size_t{ 0 } );

    ASSERT_TRUE(  ::NS(KernelConfigStore_get_num_stored_kernels)(
        store ) == size_t{ 0 } );

    /* --------------------------------------------------------------------- */
    /* A NS(KernelConfigKey) instance embodies the different parameters by
     * which a kernel may differ; first, create a default release-mode
     * key for buffer remapping */

    key_t* key_remap_release_0 = ::NS(KernelConfigKey_new)(
        arch_id, ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER),
        ::NS(ARCH_VARIANT_NONE), nullptr );

    SIXTRL_ASSERT( key_remap_release_0 != nullptr );
    ::NS(KernelConfigKey_set_argument_set)(
        key_remap_release_0, argument_set_t{ 0 } );

    /* --------------------------------------------------------------------- */
    /* There should, consequently, be no entry in the store for the key we
     * just created */

    ASSERT_TRUE( !::NS(KernelConfigStore_has_kernel_by_key)(
        store, key_remap_release_0 ) );

    ASSERT_TRUE(  ::NS(KernelConfigStore_get_kernel_id_by_key)(
        store, key_remap_release_0 ) == ::NS(ARCH_ILLEGAL_KERNEL_ID) );

    ASSERT_TRUE( !::NS(KernelConfigStore_has_default_init_kernel_config_parameters)(
        store, key_remap_release_0 ) );

    /* --------------------------------------------------------------------- */
    /* Since there are no default parameters for the key available (cf prev
     * ASSERT_TRUE statement), any attempt to let the store automatically
     * create a kernel configuration will fail */

    kernel_id_t id_remap_release = ::NS(KernelConfigStore_init_kernel_config)(
        store, key_remap_release_0 );

    ASSERT_TRUE( id_remap_release == ::NS(ARCH_ILLEGAL_KERNEL_ID) );

    ASSERT_TRUE( NS(KernelConfigStore_get_num_stored_kernels)(
        store ) == size_t{ 0 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_num_kernel_config_keys)(
        store, id_remap_release ) == size_t{ 0 } );

    /* --------------------------------------------------------------------- */
    /* Manually create a kernel config instance */

    config_base_t* ptr_remap_release_kernel_conf =
        SIXTRL_CXX_NAMESPACE::tests::KernelConfigBase_new(
            *key_remap_release_0, size_t{ 2 }, "remap_release_kernel" );

    /* Transfer ownership of this kernel config instance to the store ->
     * if successful, we are no longer allowed to call
     * NS(KernelConfig_delete)() on this pointer !!!! */

    id_remap_release = ::NS(KernelConfigStore_add_kernel_config)(
        store, key_remap_release_0, ptr_remap_release_kernel_conf );

    /* Verify if successful and if so, set the pointer to NULL to prevent
     * a double-free */

    if( ( id_remap_release != ::NS(ARCH_ILLEGAL_KERNEL_ID) ) &&
        ( ::NS(KernelConfigStore_get_ptr_kernel_config_base)(
        store, id_remap_release ) == ptr_remap_release_kernel_conf ) )
    {
        ptr_remap_release_kernel_conf = nullptr;
    }

    /* --------------------------------------------------------------------- */
    /* We *should* get see the newly added kernel config reflected in the
     * stores state */

    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel_by_key)(
        store, key_remap_release_0 ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel)(
        store, id_remap_release ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_key)(
        store, key_remap_release_0 ) == id_remap_release );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_kernel_id)(
        store, id_remap_release ) == id_remap_release );

    ASSERT_TRUE( NS(KernelConfigStore_get_num_stored_kernels)(
        store ) == size_t{ 1 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_num_kernel_config_keys)(
        store, id_remap_release ) == size_t{ 1 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
        store, id_remap_release ) != nullptr );

    /* --------------------------------------------------------------------- */
    /* A kernel config can be accessed by multiple keys; let's add a
     * second key that differs from the first one only in the argument set
     * parameter */

    key_t* key_remap_release_1 = ::NS(KernelConfigKey_new)(
        arch_id, ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER),
        ::NS(ARCH_VARIANT_NONE), nullptr );

    SIXTRL_ASSERT( key_remap_release_1 != nullptr );
    ::NS(KernelConfigKey_set_argument_set)(
        key_remap_release_1, argument_set_t{ 1 } );

    /* --------------------------------------------------------------------- */
    /* Attempt to map the newly created key to the already existing
     * kernel config ... */

    status_t status = ::NS(KernelConfigStore_add_kernel_config_to_key_mapping)(
        store, key_remap_release_1, id_remap_release );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    /* ... and check whether the internal state of the store has been updated
     * accordingly */

    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel_by_key)(
        store, key_remap_release_0 ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel_by_key)(
        store, key_remap_release_1 ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel)(
        store, id_remap_release ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_key)(
        store, key_remap_release_0 ) == id_remap_release );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_key)(
        store, key_remap_release_1 ) == id_remap_release );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_kernel_id)(
        store, id_remap_release ) == id_remap_release );

    ASSERT_TRUE( NS(KernelConfigStore_get_num_stored_kernels)(
        store ) == size_t{ 1 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_num_kernel_config_keys)(
        store, id_remap_release ) == size_t{ 2 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
        store, id_remap_release ) != nullptr );

    /* --------------------------------------------------------------------- */
    /* create another new key which differs from the first one in the variant
     * attribute. Here, we create a kernel config for the debug configuration */

    key_t* key_remap_debug_0 = ::NS(KernelConfigKey_new)(
        arch_id, ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER),
            ::NS(ARCH_VARIANT_DEBUG), nullptr );

    SIXTRL_ASSERT( key_remap_debug_0 != nullptr );
    ::NS(KernelConfigKey_set_argument_set)(
        key_remap_debug_0, argument_set_t{ 0 } );

    /* The key should not select the existing kernel or have any other
     * representation in the store yet; */

    ASSERT_TRUE( !::NS(KernelConfigStore_has_kernel_by_key)(
        store, key_remap_debug_0 ) );

    ASSERT_TRUE(  ::NS(KernelConfigStore_get_kernel_id_by_key)(
        store, key_remap_debug_0 ) == ::NS(ARCH_ILLEGAL_KERNEL_ID) );

    ASSERT_TRUE(
        !::NS(KernelConfigStore_has_default_init_kernel_config_parameters)(
            store, key_remap_debug_0 ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_init_kernel_config)(
        store, key_remap_debug_0 ) == ::NS(ARCH_ILLEGAL_KERNEL_ID) );

    /* --------------------------------------------------------------------- */
    /* We can add a set of default parameters to enable the automatical
     * of a kernel config for this specific new key */

    status = NS(KernelConfigStore_set_default_init_kernel_config_parameters)(
        store, key_remap_debug_0, size_t{ 3 }, "remap_debug_kernel_01" );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE(
        ::NS(KernelConfigStore_has_default_init_kernel_config_parameters)(
            store, key_remap_debug_0 ) );

    /* --------------------------------------------------------------------- */
    /* Creating a kernel from default parameters should now be possible */

    kernel_id_t id_remap_debug_0 = ::NS(KernelConfigStore_init_kernel_config)(
        store, key_remap_debug_0 );

    ASSERT_TRUE( id_remap_debug_0 != store_t::ILLEGAL_KERNEL_CONFIG_ID );
    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel)( store, id_remap_debug_0) );

    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel_by_key)(
        store, key_remap_debug_0 ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_key)(
        store, key_remap_debug_0 ) == id_remap_debug_0 );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_kernel_id)(
        store, id_remap_debug_0 ) == id_remap_debug_0 );

    ASSERT_TRUE( NS(KernelConfigStore_get_num_stored_kernels)(
        store ) == size_t{ 2 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_num_kernel_config_keys)(
        store, id_remap_debug_0 ) == size_t{ 1 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
        store, id_remap_debug_0 ) != nullptr );

    ASSERT_TRUE( ::NS(KernelConfigStore_init_kernel_config)(
        store, key_remap_debug_0 ) == id_remap_debug_0 );

    ASSERT_TRUE( NS(KernelConfigStore_get_num_stored_kernels)(
        store ) == size_t{ 2 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_num_kernel_config_keys)(
        store, id_remap_debug_0 ) == size_t{ 1 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
        store, id_remap_debug_0 ) != nullptr );

    /* --------------------------------------------------------------------- */
    /* Again, add an alias key to the previously created debug remapping
     * kernel config */

    key_t* key_remap_debug_1 = ::NS(KernelConfigKey_new)( arch_id,
        ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER), ::NS(ARCH_VARIANT_DEBUG),
            nullptr );

    SIXTRL_ASSERT( key_remap_debug_1 != nullptr );
    ::NS(KernelConfigKey_set_argument_set)(
        key_remap_debug_1, argument_set_t{ 1 } );

    ASSERT_TRUE( !::NS(KernelConfigStore_has_kernel_by_key)(
        store, key_remap_debug_1 ) );

    ASSERT_TRUE(  ::NS(KernelConfigStore_get_kernel_id_by_key)(
        store, key_remap_debug_1 ) == ::NS(ARCH_ILLEGAL_KERNEL_ID) );

    ASSERT_TRUE(
        !::NS(KernelConfigStore_has_default_init_kernel_config_parameters)(
            store, key_remap_debug_1 ) );

    /* Even if we add a set of default parameters for the
     * key_remap_debug_1 key ... */

    status = ::NS(KernelConfigStore_set_default_init_kernel_config_parameters)(
        store, key_remap_debug_1, size_t{ 3 }, "remap_debug_kernel_01" );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(
        ::NS(KernelConfigStore_has_default_init_kernel_config_parameters)(
            store, key_remap_debug_1 ) );

    /* ... an alias mapping takes precedence over default parameters */

    status = ::NS(KernelConfigStore_add_kernel_config_to_key_mapping)(
        store, key_remap_debug_1, id_remap_debug_0 );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    /* Check that the store reflects the now two kernels with two alias
     * mappings each */

    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel)(
        store, id_remap_debug_0 ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel_by_key)(
        store, key_remap_debug_0 ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel_by_key)(
        store, key_remap_debug_1 ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_key)(
        store, key_remap_debug_0 ) == id_remap_debug_0 );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_key)(
        store, key_remap_debug_1 ) == id_remap_debug_0 );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_kernel_id)(
        store, id_remap_debug_0  ) == id_remap_debug_0 );

    ASSERT_TRUE( NS(KernelConfigStore_get_num_stored_kernels)(
        store ) == size_t{ 2 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_num_kernel_config_keys)(
        store, id_remap_debug_0 ) == size_t{ 2 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
        store, id_remap_debug_0 ) != nullptr );

    ASSERT_TRUE( id_remap_debug_0 == ::NS(KernelConfigStore_init_kernel_config)(
        store, key_remap_debug_1 ) );

    /* --------------------------------------------------------------------- */
    /* Removing the kernel config.
     * This should also remove both alias mappigns */

    status = ::NS(KernelConfigStore_remove_kernel_config_by_id)(
        store, id_remap_debug_0 );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( !::NS(KernelConfigStore_has_kernel)(
        store, id_remap_debug_0 ) );

    ASSERT_TRUE( !::NS(KernelConfigStore_has_kernel_by_key)(
        store, key_remap_debug_0 ) );

    ASSERT_TRUE( !::NS(KernelConfigStore_has_kernel_by_key)(
        store, key_remap_debug_1 ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_key)(
        store, key_remap_debug_0 ) == ::NS(ARCH_ILLEGAL_KERNEL_ID) );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_key)(
        store, key_remap_debug_1 ) == ::NS(ARCH_ILLEGAL_KERNEL_ID) );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_kernel_id_by_kernel_id)(
        store, id_remap_debug_0 ) == ::NS(ARCH_ILLEGAL_KERNEL_ID) );

    ASSERT_TRUE( NS(KernelConfigStore_get_num_stored_kernels)(
        store ) == size_t{ 1 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_num_kernel_config_keys)(
        store, id_remap_debug_0 ) == size_t{ 0 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
        store, id_remap_debug_0 ) == nullptr );

    /* --------------------------------------------------------------------- */
    /* Clean-up */

    ::NS(KernelConfigKey_delete)( key_remap_release_0 );
    ::NS(KernelConfigKey_delete)( key_remap_release_1 );
    ::NS(KernelConfigKey_delete)( key_remap_debug_0 );
    ::NS(KernelConfigKey_delete)( key_remap_debug_1 );
    ::NS(KernelConfigStore_delete)( store );

    if( ptr_remap_release_kernel_conf != nullptr )
    {
        ::NS(KernelConfig_delete)( ptr_remap_release_kernel_conf );
        ptr_remap_release_kernel_conf = nullptr;
    }
}

/* end: tests/sixtracklib/common/control/test_kernel_config_store_c99.cpp */
