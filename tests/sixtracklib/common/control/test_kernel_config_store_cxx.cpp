#include "sixtracklib/common/control/kernel_config_store.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/testlib.h"

TEST( CXX_CommonControlKernelStoreCommonTests, AddRemoveKernelConfigs )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using store_t        = st::KernelConfigStore;
    using kernel_id_t    = store_t::kernel_config_id_t;
    using key_t          = store_t::kernel_config_key_t;
    using config_base_t  = store_t::kernel_config_base_t;
    using size_t         = store_t::size_type;
    using arch_id_t      = store_t::arch_id_t;
    using status_t       = store_t::status_t;
    using argument_set_t = store_t::argument_set_t;

    /* Verify that a suitable arch is available */
    st::Architectures const& archs = st::Architectures_get_const();
    SIXTRL_ASSERT( archs.numArchitectures() > size_t{ 0 } );

    arch_id_t const arch_id = archs.archIdByNumber( size_t{ 0 } );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_NONE );

    SIXTRL_ASSERT(  archs.hasArchitecture( arch_id ) );
    SIXTRL_ASSERT(  archs.hasArchStr( arch_id ) );

    /* --------------------------------------------------------------------- */
    /* Create an empty store */

    store_t store;

    /* Verify that the store is indeed empty and does not contain any kernel
     * configs */
    ASSERT_TRUE(  store.numKernelSets() == size_t{ 0 } );
    ASSERT_TRUE(  store.numStoredKernels() == size_t{ 0 } );

    /* --------------------------------------------------------------------- */
    /* A NS(KernelConfigKey) instance embodies the different parameters by
     * which a kernel may differ; first, create a default release-mode
     * key for buffer remapping */

    key_t key_remap_release_0( arch_id, st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER,
        st::ARCH_VARIANT_NONE, argument_set_t{ 0 } );

    /* --------------------------------------------------------------------- */
    /* There should, consequently, be no entry in the store for the key we
     * just created */


    ASSERT_TRUE( !store.hasKernel( key_remap_release_0 ) );

    ASSERT_TRUE(  store.kernelId( key_remap_release_0 ) ==
                  st::ARCH_ILLEGAL_KERNEL_ID );

    ASSERT_TRUE( !store.hasDefaultInitKernelConfigParameters(
        key_remap_release_0 ) );

    /* --------------------------------------------------------------------- */
    /* Since there are no default parameters for the key available (cf prev
     * ASSERT_TRUE statement), any attempt to let the store automatically
     * create a kernel configuration will fail */

    kernel_id_t id_remap_release = store.initKernelConfig( key_remap_release_0 );
    ASSERT_TRUE( id_remap_release == st::ARCH_ILLEGAL_KERNEL_ID );
    ASSERT_TRUE( store.numStoredKernels() == size_t{ 0 } );
    ASSERT_TRUE( store.numKernelConfigKeys( id_remap_release ) == size_t{ 0 } );

    /* --------------------------------------------------------------------- */
    /* Manually create a kernel config instance and pass it on to the store */

    std::unique_ptr< config_base_t > ptr_remap_release_kernel_conf(
        new config_base_t( key_remap_release_0, size_t{ 2 },
                           "remap_release_kernel" ) );

    id_remap_release = store.addKernelConfig(
        key_remap_release_0, std::move( ptr_remap_release_kernel_conf ) );

    ASSERT_TRUE( id_remap_release != st::ARCH_ILLEGAL_KERNEL_ID );
    ASSERT_TRUE( ptr_remap_release_kernel_conf.get() == nullptr );

    /* --------------------------------------------------------------------- */
    /* We *should* get see the newly added kernel config reflected in the
     * stores state */

    ASSERT_TRUE( store.hasKernel( key_remap_release_0 ) );
    ASSERT_TRUE( store.hasKernel( id_remap_release ) );
    ASSERT_TRUE( store.kernelId( key_remap_release_0 ) == id_remap_release );
    ASSERT_TRUE( store.kernelId( id_remap_release ) == id_remap_release );
    ASSERT_TRUE( store.numStoredKernels() == size_t{ 1 } );
    ASSERT_TRUE( store.numKernelConfigKeys( id_remap_release ) == size_t{ 1 } );
    ASSERT_TRUE( store.ptrKernelConfigBase( id_remap_release ) != nullptr );

    /* --------------------------------------------------------------------- */
    /* A kernel config can be accessed by multiple keys; let's add a
     * second key that differs from the first one only in the argument set
     * parameter */

    key_t key_remap_release_1( arch_id, st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER,
        st::ARCH_VARIANT_NONE, argument_set_t{ 1 } );

    /* --------------------------------------------------------------------- */
    /* Attempt to map the newly created key to the already existing
     * kernel config ... */

    status_t status = store.addKernelConfig(
        key_remap_release_1, id_remap_release );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    /* ... and check whether the internal state of the store has been updated
     * accordingly */

    ASSERT_TRUE( store.hasKernel( key_remap_release_0 ) );
    ASSERT_TRUE( store.hasKernel( key_remap_release_1 ) );
    ASSERT_TRUE( store.hasKernel( id_remap_release ) );
    ASSERT_TRUE( store.kernelId( key_remap_release_0 ) == id_remap_release );
    ASSERT_TRUE( store.kernelId( key_remap_release_1 ) == id_remap_release );
    ASSERT_TRUE( store.kernelId( id_remap_release ) == id_remap_release );
    ASSERT_TRUE( store.numStoredKernels() == size_t{ 1 } );
    ASSERT_TRUE( store.numKernelConfigKeys( id_remap_release ) == size_t{ 2 } );
    ASSERT_TRUE( store.ptrKernelConfigBase( id_remap_release ) != nullptr );

    /* --------------------------------------------------------------------- */
    /* create another new key which differs from the first one in the variant
     * attribute. Here, we create a kernel config for the debug configuration */

    key_t key_remap_debug_0( arch_id, st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER,
            st::ARCH_VARIANT_DEBUG, argument_set_t{ 0 } );

    /* The key should not select the existing kernel or have any other
     * representation in the store yet; */

    ASSERT_TRUE( !store.hasKernel( key_remap_debug_0 ) );
    ASSERT_TRUE(  store.kernelId( key_remap_debug_0 ) ==
                  st::ARCH_ILLEGAL_KERNEL_ID );

    ASSERT_TRUE( !store.hasDefaultInitKernelConfigParameters(
        key_remap_debug_0 ) );

    /* --------------------------------------------------------------------- */
    /* We can add a set of default parameters to enable the automatical
     * of a kernel config for this specific new key */

    status = store.setDefaultInitKernelConfigParameters(
        key_remap_debug_0, size_t{ 3 }, "remap_debug_kernel_01" );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( store.hasDefaultInitKernelConfigParameters(
        key_remap_debug_0 ) );

    /* --------------------------------------------------------------------- */
    /* Creating a kernel from default parameters should now be possible */

    kernel_id_t id_remap_debug_0 = store.initKernelConfig( key_remap_debug_0 );

    ASSERT_TRUE( id_remap_debug_0 != store_t::ILLEGAL_KERNEL_CONFIG_ID );
    ASSERT_TRUE( store.hasKernel( id_remap_debug_0 ) );
    ASSERT_TRUE( store.hasKernel( key_remap_debug_0 ) );
    ASSERT_TRUE( store.kernelId(  key_remap_debug_0 ) == id_remap_debug_0 );
    ASSERT_TRUE( store.kernelId( id_remap_debug_0 ) == id_remap_debug_0 );

    ASSERT_TRUE( store.numStoredKernels() == size_t{ 2 } );
    ASSERT_TRUE( store.numKernelConfigKeys( id_remap_debug_0 ) == size_t{ 1 } );
    ASSERT_TRUE( store.ptrKernelConfigBase( id_remap_debug_0 ) != nullptr );

    ASSERT_TRUE( store.initKernelConfig(
        key_remap_debug_0 ) == id_remap_debug_0 );

    ASSERT_TRUE( store.numStoredKernels() == size_t{ 2 } );
    ASSERT_TRUE( store.numKernelConfigKeys( id_remap_debug_0 ) == size_t{ 1 } );
    ASSERT_TRUE( store.ptrKernelConfigBase( id_remap_debug_0 ) != nullptr );

    /* --------------------------------------------------------------------- */
    /* Again, add an alias key to the previously created debug remapping
     * kernel config */

    key_t key_remap_debug_1( arch_id, st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER,
            st::ARCH_VARIANT_DEBUG, argument_set_t{ 1 } );

    ASSERT_TRUE( !store.hasKernel( key_remap_debug_1 ) );
    ASSERT_TRUE(  store.kernelId( key_remap_debug_1 ) ==
                  st::ARCH_ILLEGAL_KERNEL_ID );

    ASSERT_TRUE( !store.hasDefaultInitKernelConfigParameters(
        key_remap_debug_1 ) );

    /* Even if we add a set of default parameters for the
     * key_remap_debug_1 key ... */

    status = store.setDefaultInitKernelConfigParameters(
        key_remap_debug_1, size_t{ 3 }, "remap_debug_kernel_01" );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( store.hasDefaultInitKernelConfigParameters(
        key_remap_debug_1 ) );

    /* ... an alias mapping takes precedence over default parameters */

    status = store.addKernelConfig( key_remap_debug_1, id_remap_debug_0 );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    /* Check that the store reflects the now two kernels with two alias
     * mappings each */

    ASSERT_TRUE( store.hasKernel( id_remap_debug_0 ) );
    ASSERT_TRUE( store.hasKernel( key_remap_debug_0 ) );
    ASSERT_TRUE( store.hasKernel( key_remap_debug_1 ) );
    ASSERT_TRUE( store.kernelId(  key_remap_debug_0 ) == id_remap_debug_0 );
    ASSERT_TRUE( store.kernelId(  key_remap_debug_1 ) == id_remap_debug_0 );
    ASSERT_TRUE( store.kernelId(  id_remap_debug_0  ) == id_remap_debug_0 );

    ASSERT_TRUE( store.numStoredKernels() == size_t{ 2 } );
    ASSERT_TRUE( store.numKernelConfigKeys( id_remap_debug_0 ) == size_t{ 2 } );
    ASSERT_TRUE( store.ptrKernelConfigBase( id_remap_debug_0 ) != nullptr );

    ASSERT_TRUE( id_remap_debug_0 == store.initKernelConfig(
        key_remap_debug_1 ) );

    /* --------------------------------------------------------------------- */
    /* Removing the kernel config.
     * This should also remove both alias mappigns */

    status = store.removeKernelConfig( id_remap_debug_0 );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( !store.hasKernel( id_remap_debug_0 ) );
    ASSERT_TRUE( !store.hasKernel( key_remap_debug_0 ) );
    ASSERT_TRUE( !store.hasKernel( key_remap_debug_1 ) );

    ASSERT_TRUE( store.kernelId(  key_remap_debug_0 ) ==
                 st::ARCH_ILLEGAL_KERNEL_ID );

    ASSERT_TRUE( store.kernelId(  key_remap_debug_1 ) ==
                 st::ARCH_ILLEGAL_KERNEL_ID );

    ASSERT_TRUE( store.kernelId( id_remap_debug_0 ) ==
                 st::ARCH_ILLEGAL_KERNEL_ID );

    ASSERT_TRUE( store.numStoredKernels() == size_t{ 1 } );
    ASSERT_TRUE( store.numKernelConfigKeys( id_remap_debug_0 ) == size_t{ 0 } );
    ASSERT_TRUE( store.ptrKernelConfigBase( id_remap_debug_0 ) == nullptr );

}

TEST( CXX_CommonControlKernelStoreCommonTests, AddRemoveKernelConfigsExtLock )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using store_t        = st::KernelConfigStore;
    using kernel_id_t    = store_t::kernel_config_id_t;
    using key_t          = store_t::kernel_config_key_t;
    using config_base_t  = store_t::kernel_config_base_t;
    using size_t         = store_t::size_type;
    using arch_id_t      = store_t::arch_id_t;
    using status_t       = store_t::status_t;
    using argument_set_t = store_t::argument_set_t;
    using lock_t         = store_t::lock_t;

    /* Verify that a suitable arch is available */
    st::Architectures const& archs = st::Architectures_get_const();
    SIXTRL_ASSERT( archs.numArchitectures() > size_t{ 0 } );

    arch_id_t const arch_id = archs.archIdByNumber( size_t{ 0 } );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_NONE );

    SIXTRL_ASSERT(  archs.hasArchitecture( arch_id ) );
    SIXTRL_ASSERT(  archs.hasArchStr( arch_id ) );

    /* --------------------------------------------------------------------- */
    /* Create an empty store */

    store_t store;

    /* Explicitly acquire a lock for the internal mutex of the Store ->
     * everything now is guaranteed to happen in a single transaction */

    lock_t lock( *store.lockable() );
    ASSERT_TRUE( store.checkLock( lock ) );

    /* --------------------------------------------------------------------- */
    /* Verify that the store is indeed empty and does not contain any kernel
     * configs */

    ASSERT_TRUE(  store.numKernelSets( lock ) == size_t{ 0 } );
    ASSERT_TRUE(  store.numStoredKernels( lock ) == size_t{ 0 } );

    /* --------------------------------------------------------------------- */
    /* A NS(KernelConfigKey) instance embodies the different parameters by
     * which a kernel may differ; first, create a default release-mode
     * key for buffer remapping */

    key_t key_remap_release_0( arch_id, st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER,
        st::ARCH_VARIANT_NONE, argument_set_t{ 0 } );

    /* --------------------------------------------------------------------- */
    /* There should, consequently, be no entry in the store for the key we
     * just created */

    ASSERT_TRUE( !store.hasKernel( lock, key_remap_release_0 ) );

    ASSERT_TRUE(  store.kernelId( lock, key_remap_release_0 ) ==
                  st::ARCH_ILLEGAL_KERNEL_ID );

    ASSERT_TRUE( !store.hasDefaultInitKernelConfigParameters(
        lock, key_remap_release_0 ) );

    /* --------------------------------------------------------------------- */
    /* Since there are no default parameters for the key available (cf prev
     * ASSERT_TRUE statement), any attempt to let the store automatically
     * create a kernel configuration will fail */

    kernel_id_t id_remap_release =
        store.initKernelConfig( lock, key_remap_release_0 );

    ASSERT_TRUE( id_remap_release == st::ARCH_ILLEGAL_KERNEL_ID );
    ASSERT_TRUE( store.numStoredKernels( lock ) == size_t{ 0 } );
    ASSERT_TRUE( store.numKernelConfigKeys( lock, id_remap_release )
        == size_t{ 0 } );

    /* --------------------------------------------------------------------- */
    /* Manually create a kernel config instance and pass it on to the store */

    std::unique_ptr< config_base_t > ptr_remap_release_kernel_conf(
        new config_base_t( key_remap_release_0, size_t{ 2 },
                           "remap_release_kernel" ) );

    id_remap_release = store.addKernelConfig(
        lock, key_remap_release_0, std::move( ptr_remap_release_kernel_conf ) );

    ASSERT_TRUE( id_remap_release != st::ARCH_ILLEGAL_KERNEL_ID );

    /* --------------------------------------------------------------------- */
    /* We *should* get see the newly added kernel config reflected in the
     * stores state */

    ASSERT_TRUE( store.hasKernel( lock, key_remap_release_0 ) );
    ASSERT_TRUE( store.hasKernel( lock, id_remap_release ) );
    ASSERT_TRUE( store.kernelId( lock, key_remap_release_0 ) == id_remap_release );
    ASSERT_TRUE( store.kernelId( lock, id_remap_release ) == id_remap_release );
    ASSERT_TRUE( store.numStoredKernels( lock ) == size_t{ 1 } );
    ASSERT_TRUE( store.numKernelConfigKeys( lock, id_remap_release ) == size_t{ 1 } );
    ASSERT_TRUE( store.ptrKernelConfigBase( lock, id_remap_release ) != nullptr );

    /* --------------------------------------------------------------------- */
    /* A kernel config can be accessed by multiple keys; let's add a
     * second key that differs from the first one only in the argument set
     * parameter */

    key_t key_remap_release_1( arch_id, st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER,
        st::ARCH_VARIANT_NONE, argument_set_t{ 1 } );

    /* --------------------------------------------------------------------- */
    /* Attempt to map the newly created key to the already existing
     * kernel config ... */

    status_t status = store.addKernelConfig(
        lock, key_remap_release_1, id_remap_release );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

     /* ... and check whether the internal state of the store has been updated
      * accordingly */

    ASSERT_TRUE( store.hasKernel( lock, key_remap_release_0 ) );
    ASSERT_TRUE( store.hasKernel( lock, key_remap_release_1 ) );
    ASSERT_TRUE( store.hasKernel( lock, id_remap_release ) );
    ASSERT_TRUE( store.kernelId( lock, key_remap_release_0 ) == id_remap_release );
    ASSERT_TRUE( store.kernelId( lock, key_remap_release_1 ) == id_remap_release );
    ASSERT_TRUE( store.kernelId( lock, id_remap_release ) == id_remap_release );
    ASSERT_TRUE( store.numStoredKernels( lock ) == size_t{ 1 } );
    ASSERT_TRUE( store.numKernelConfigKeys( lock, id_remap_release ) == size_t{ 2 } );
    ASSERT_TRUE( store.ptrKernelConfigBase( lock, id_remap_release ) != nullptr );

     /* --------------------------------------------------------------------- */
     /* create another new key which differs from the first one in the variant
      * attribute. Here, we create a kernel config for the debug configuration */

    key_t key_remap_debug_0( arch_id, st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER,
            st::ARCH_VARIANT_DEBUG, argument_set_t{ 0 } );

    /* The key should not select the existing kernel or have any other
     * representation in the store yet; */

    ASSERT_TRUE( !store.hasKernel( lock, key_remap_debug_0 ) );
    ASSERT_TRUE(  store.kernelId( lock, key_remap_debug_0 ) ==
                  st::ARCH_ILLEGAL_KERNEL_ID );

    ASSERT_TRUE( !store.hasDefaultInitKernelConfigParameters(
        lock, key_remap_debug_0 ) );

    /* --------------------------------------------------------------------- */
    /* We can add a set of default parameters to enable the automatical
     * of a kernel config for this specific new key */

    status = store.setDefaultInitKernelConfigParameters(
        lock, key_remap_debug_0, size_t{ 3 }, "remap_debug_kernel_01" );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( store.hasDefaultInitKernelConfigParameters(
        lock, key_remap_debug_0 ) );

    /* --------------------------------------------------------------------- */
    /* Creating a kernel from default parameters should now be possible */

    kernel_id_t id_remap_debug_0 = store.initKernelConfig(
        lock, key_remap_debug_0 );

    ASSERT_TRUE( id_remap_debug_0 != store_t::ILLEGAL_KERNEL_CONFIG_ID );

    ASSERT_TRUE( store.hasKernel( lock, id_remap_debug_0 ) );
    ASSERT_TRUE( store.hasKernel( lock, key_remap_debug_0 ) );
    ASSERT_TRUE( store.kernelId(  lock, key_remap_debug_0 ) == id_remap_debug_0 );
    ASSERT_TRUE( store.kernelId( lock, id_remap_debug_0 ) == id_remap_debug_0 );

    ASSERT_TRUE( store.numStoredKernels( lock ) == size_t{ 2 } );
    ASSERT_TRUE( store.numKernelConfigKeys( lock, id_remap_debug_0 ) ==
        size_t{ 1 } );

    ASSERT_TRUE( store.ptrKernelConfigBase( lock, id_remap_debug_0 )
        != nullptr );

    ASSERT_TRUE( store.initKernelConfig( lock, key_remap_debug_0 ) ==
        id_remap_debug_0 );

    ASSERT_TRUE( store.numStoredKernels( lock ) == size_t{ 2 } );
    ASSERT_TRUE( store.numKernelConfigKeys( lock, id_remap_debug_0 ) ==
        size_t{ 1 } );

    ASSERT_TRUE( store.ptrKernelConfigBase( lock, id_remap_debug_0 ) !=
        nullptr );

    /* --------------------------------------------------------------------- */
    /* Again, add an alias key to the previously created debug remapping
     * kernel config */

    key_t key_remap_debug_1( arch_id, st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER,
            st::ARCH_VARIANT_DEBUG, argument_set_t{ 1 } );

    ASSERT_TRUE( !store.hasKernel( lock, key_remap_debug_1 ) );
    ASSERT_TRUE(  store.kernelId( lock, key_remap_debug_1 ) ==
                  st::ARCH_ILLEGAL_KERNEL_ID );

    ASSERT_TRUE( !store.hasDefaultInitKernelConfigParameters(
        lock, key_remap_debug_1 ) );

    /* Even if we add a set of default parameters for the
     * key_remap_debug_1 key ... */

    status = store.setDefaultInitKernelConfigParameters(
        lock, key_remap_debug_1, size_t{ 3 }, "remap_debug_kernel_01" );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE( store.hasDefaultInitKernelConfigParameters(
        lock, key_remap_debug_1 ) );

    /* ... an alias mapping takes precedence over default parameters */

    status = store.addKernelConfig( lock, key_remap_debug_1, id_remap_debug_0 );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    /* Check that the store reflects the now two kernels with two alias
     * mappings each */

    ASSERT_TRUE( store.hasKernel( lock, id_remap_debug_0 ) );
    ASSERT_TRUE( store.hasKernel( lock, key_remap_debug_0 ) );
    ASSERT_TRUE( store.hasKernel( lock, key_remap_debug_1 ) );
    ASSERT_TRUE( store.kernelId(  lock, key_remap_debug_0 ) ==
        id_remap_debug_0 );

    ASSERT_TRUE( store.kernelId( lock, key_remap_debug_1 ) == id_remap_debug_0 );
    ASSERT_TRUE( store.kernelId( lock, id_remap_debug_0  ) == id_remap_debug_0 );

    ASSERT_TRUE( store.numStoredKernels( lock ) == size_t{ 2 } );
    ASSERT_TRUE( store.numKernelConfigKeys( lock, id_remap_debug_0 ) ==
        size_t{ 2 } );

    ASSERT_TRUE( store.ptrKernelConfigBase( lock, id_remap_debug_0 ) !=
        nullptr );

    ASSERT_TRUE( id_remap_debug_0 == store.initKernelConfig(
        lock, key_remap_debug_1 ) );

    /* --------------------------------------------------------------------- */
    /* Removing the kernel config.
     * This should also remove both alias mappigns */

    status = store.removeKernelConfig( lock, id_remap_debug_0 );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( !store.hasKernel( lock, id_remap_debug_0 ) );
    ASSERT_TRUE( !store.hasKernel( lock, key_remap_debug_0 ) );
    ASSERT_TRUE( !store.hasKernel( lock, key_remap_debug_1 ) );

    ASSERT_TRUE( store.kernelId(  lock, key_remap_debug_0 ) ==
                 st::ARCH_ILLEGAL_KERNEL_ID );

    ASSERT_TRUE( store.kernelId(  lock, key_remap_debug_1 ) ==
                 st::ARCH_ILLEGAL_KERNEL_ID );

    ASSERT_TRUE( store.kernelId( lock, id_remap_debug_0 ) ==
                 st::ARCH_ILLEGAL_KERNEL_ID );

    ASSERT_TRUE( store.numStoredKernels( lock ) == size_t{ 1 } );

    ASSERT_TRUE( store.numKernelConfigKeys( lock, id_remap_debug_0 )
        == size_t{ 0 } );

    ASSERT_TRUE( store.ptrKernelConfigBase( lock, id_remap_debug_0 )
        == nullptr );
}

/* end: tests/sixtracklib/common/control/test_kernel_config_store_cxx.cpp */
