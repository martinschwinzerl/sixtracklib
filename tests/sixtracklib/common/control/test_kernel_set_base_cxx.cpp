#include "sixtracklib/common/control/kernel_set.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/kernel_config_base.hpp"
#include "sixtracklib/common/control/kernel_config_store.hpp"
#include "sixtracklib/testlib.h"

TEST( CXX_CommonControlKernelSetBaseTests, AddKernelSetToStoreSwitchRemove )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using store_t         = st::KernelConfigStore;
    using kernel_set_t    = st::KernelSetBase;
    using config_base_t   = st::KernelConfigBase;
    using key_t           = st::KernelConfigKey;
    using argument_set_t  = key_t::argument_set_t;
    using size_t          = key_t::size_type;
    using kernel_id_t     = store_t::kernel_config_id_t;
    using arch_id_t       = store_t::arch_id_t;
    using status_t        = store_t::status_t;
    using kernel_set_id_t = store_t::kernel_set_id_t;

    /* Verify that a suitable arch is available */
    st::Architectures const& archs = st::Architectures_get_const();
    SIXTRL_ASSERT( archs.numArchitectures() > size_t{ 0 } );

    arch_id_t const arch_id = archs.archIdByNumber( size_t{ 0 } );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_NONE );

    SIXTRL_ASSERT(  archs.hasArchitecture( arch_id ) );
    SIXTRL_ASSERT(  archs.hasArchStr( arch_id ) );

    /* --------------------------------------------------------------------- */
    /* Create an empty store: */

    store_t store;

    /* --------------------------------------------------------------------- */
    /* Setup the store for the kernel sets */
    /* Add four kernels for the release variant */

    key_t release_key( arch_id, st::KERNEL_CONFIG_PURPOSE_UNSPECIFIED,
                       st::ARCH_VARIANT_NONE, argument_set_t{ 0 }, nullptr );

    release_key.setPurpose( st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );

    std::unique_ptr< config_base_t > ptr_kernel(
        new config_base_t( release_key, size_t{ 1 }, "remap_release_kernel" ) );

    kernel_id_t const release_remap_id_0 = store.addKernelConfig(
        release_key, std::move( ptr_kernel ) );
    SIXTRL_ASSERT( release_remap_id_0 != store_t::ILLEGAL_KERNEL_CONFIG_ID );
    SIXTRL_ASSERT( ptr_kernel.get() == nullptr );

    release_key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );
    ptr_kernel.reset( new config_base_t(
        release_key, size_t{ 1 }, "track_release_kernel" ) );
    SIXTRL_ASSERT( ptr_kernel.get() != nullptr );
    kernel_id_t const track_release_id_0 = store.addKernelConfig(
        release_key, std::move( ptr_kernel ) );
    SIXTRL_ASSERT( track_release_id_0 != store_t::ILLEGAL_KERNEL_CONFIG_ID );
    SIXTRL_ASSERT( ptr_kernel.get() == nullptr );

    release_key.setPurpose( st::KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES );
    ptr_kernel.reset( new config_base_t(
        release_key, size_t{ 1 }, "fetch_addr_release_kernel" ) );
    SIXTRL_ASSERT( ptr_kernel.get() != nullptr );
    kernel_id_t const fetch_addr_release_id_0 = store.addKernelConfig(
        release_key, std::move( ptr_kernel ) );
    SIXTRL_ASSERT( fetch_addr_release_id_0 != store_t::ILLEGAL_KERNEL_CONFIG_ID );
    SIXTRL_ASSERT( ptr_kernel.get() == nullptr );

    release_key.setPurpose( st::KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID );
    ptr_kernel.reset( new config_base_t(
        release_key, size_t{ 1 }, "userdefined_release_kernel" ) );
    SIXTRL_ASSERT( ptr_kernel.get() != nullptr );
    kernel_id_t const usrdefined_release_id_0 = store.addKernelConfig(
        release_key, std::move( ptr_kernel ) );
    SIXTRL_ASSERT( usrdefined_release_id_0 != store_t::ILLEGAL_KERNEL_CONFIG_ID );
    SIXTRL_ASSERT( ptr_kernel.get() == nullptr );

    /* Add one kernel for the debug variant configuration */

    key_t debug_key( release_key );

    debug_key.setVariant( st::ARCH_VARIANT_DEBUG );

    debug_key.setPurpose( st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );
    ptr_kernel.reset( new config_base_t(
        debug_key, size_t{ 2 }, "remap_debug_kernel" ) );
    SIXTRL_ASSERT( ptr_kernel.get() != nullptr );
    kernel_id_t const remap_debug_id_0 = store.addKernelConfig( debug_key,
        std::move( ptr_kernel ) );
    SIXTRL_ASSERT( remap_debug_id_0 != store_t::ILLEGAL_KERNEL_CONFIG_ID );
    SIXTRL_ASSERT( ptr_kernel.get() == nullptr );

    /* Add an alias for the debug kernel to refer to the same kernel config */

    debug_key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );
    status_t status = store.addKernelConfig( debug_key, track_release_id_0 );
    SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );

    /* Add default parameters for the debug  variant of the fetch addr kernel */

    debug_key.setPurpose( st::KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES );
    status = store.setDefaultInitKernelConfigParameters(
        debug_key, size_t{ 6 }, "fetch_addr_debug_id" );
    SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );

    /* --------------------------------------------------------------------- */
    /* Add kernel_set for argument_set #0: */

    std::unique_ptr< kernel_set_t > ptr_set(
        new kernel_set_t( arch_id, store ) );

    ASSERT_TRUE( ptr_set.get() != nullptr );

    kernel_set_id_t const set0_id = store.addKernelSet( std::move( ptr_set ) );
    ASSERT_TRUE( set0_id != store_t::ILLEGAL_KERNEL_SET_ID );
    ASSERT_TRUE( store.hasKernelSet( set0_id ) );
    ASSERT_TRUE( store.numKernelSets() == size_t{ 1 } );

    kernel_set_t* ptr_set = store.ptrKernelSetBase( set0_id );
    ASSERT_TRUE( ptr_set != nullptr );
    ASSERT_TRUE( ptr_set->numPurposes() == size_t{ 0 } );
    ASSERT_TRUE( ptr_set->




}

/* end: */
