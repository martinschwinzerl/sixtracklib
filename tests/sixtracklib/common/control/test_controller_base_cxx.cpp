#include "sixtracklib/common/control/controller_base.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"
#include "sixtracklib/common/control/kernel_config_store.hpp"
#include "sixtracklib/common/control/kernel_config_base.hpp"
#include "sixtracklib/common/control/kernel_set.hpp"

#include "sixtracklib/testlib.hpp"

TEST( CXX_CommonControlControllerBase, SingleCtrlChangeVariantArgSetKey )
{
    namespace st                = SIXTRL_CXX_NAMESPACE;
    using ctrl_t                = st::tests::TestControllerBase;
    using kernel_conf_store_t   = st::KernelConfigStore;
    using kernel_set_t          = st::KernelSetBase;
    using purpose_t             = st::kernel_purpose_t;
    using kernel_config_id_t    = ctrl_t::kernel_id_t;
    using size_t                = ctrl_t::size_type;
    using status_t              = ctrl_t::status_t;
    using arch_id_t             = ctrl_t::arch_id_t;

    size_t const NUM_CTRL_PURPOSES = kernel_set_t::NUM_CONTROLLER_PURPOSES;

    /* Create three dummy architectures to allow variation in the
     * node sets based on the arch_id parameter: */

    st::Architectures& archs = st::Architectures_get();
    static constexpr size_t NUM_ARCHS = size_t{ 1 };
    arch_id_t arch_id = st::NODE_UNDEFINED_INDEX;
    status_t status = st::tests::Architectures_setup(
        archs, NUM_ARCHS, arch_id_t{ 32 }, &arch_id );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    /* Create an empty external store */

    kernel_conf_store_t store_1;

    ASSERT_TRUE( store_1.numKernelSets() == size_t{ 0 } );
    ASSERT_TRUE( store_1.numStoredKernels() == size_t{ 0 } );

    /* Create first controller: */

    ctrl_t ctrl_1a( arch_id, &store_1 );

    /* Check that ctrl_1a has the expected properties -> since there are
     * currently no kernels available, there is very little that should work */

    ASSERT_TRUE( arch_id == ctrl_1a.archId() );
    ASSERT_TRUE(  ctrl_1a.hasKernelConfigStore() );
    ASSERT_TRUE( !ctrl_1a.ownsKernelConfigStore() );
    ASSERT_TRUE(  static_cast< ctrl_t const& >( ctrl_1a ).ptrKernelConfigStore()
                  == &store_1 );

    ASSERT_TRUE(  ctrl_1a.kernelSetId() != ctrl_t::ILLEGAL_KERNEL_SET_ID );
    ASSERT_TRUE(  ctrl_1a.ptrConstKernelSet() != nullptr );

    ASSERT_TRUE( ctrl_1a.ptrConstKernelSet()->numPurposes() == NUM_CTRL_PURPOSES );
    ASSERT_TRUE( ctrl_1a.hasKernelSet() );
    ASSERT_TRUE( ctrl_1a.ptrConstKernelSet() != nullptr );
    ASSERT_TRUE( ctrl_1a.variantReleaseMode() );

    ASSERT_TRUE( store_1.numKernelSets() == size_t{ 1 } );
    ASSERT_TRUE( store_1.hasKernelSet( ctrl_1a.kernelSetId() ) );
    ASSERT_TRUE( store_1.hasKernelSet( *ctrl_1a.ptrConstKernelSet() ) );

    ASSERT_TRUE(  ctrl_1a.ptrConstKernelSet()->numPurposes() ==
                  kernel_set_t::NUM_CONTROLLER_PURPOSES );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose = kernel_set_t::CONTROLLER_PURPOSES[ ii ];

        ASSERT_TRUE( ctrl_1a.ptrConstKernelSet()->requires( purpose ) );
        ASSERT_FALSE( ctrl_1a.ptrConstKernelSet()->available( purpose ) );
        ASSERT_FALSE( ctrl_1a.ptrConstKernelSet()->ready( purpose ) );
    }

    ASSERT_TRUE(  ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( !ctrl_1a.readyForReceive() );
    ASSERT_TRUE( !ctrl_1a.readyForSend() );
    ASSERT_TRUE( !ctrl_1a.readyForRemap() );
    ASSERT_TRUE( !ctrl_1a.readyForRunningKernels() );

    /* Init default controller kernels: */

    ctrl_t::kernel_config_key_t key( ctrl_1a.currentKey() );
    ASSERT_TRUE( key.archId() == arch_id );
    ASSERT_TRUE( key.variant() == ctrl_1a.variant() );
    ASSERT_TRUE( key.argumentSet() == ctrl_t::kernel_argument_set_t{ 0 } );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        std::ostringstream a2str;

        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        key.setPurpose( purpose );

        a2str << "dummy_kernel_config_" << std::setfill( '0' ) << std::setw( 2 )
              << ii;

        status = store_1.setDefaultInitKernelConfigParameters(
            key, size_t{ 1 }, a2str.str() );

        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }

    ctrl_t::kernel_set_base_t* ptr_kset_base = store_1.ptrKernelSetBase(
        ctrl_1a.kernelSetId() );

    ASSERT_TRUE( ptr_kset_base != nullptr );
    ASSERT_TRUE( ptr_kset_base->isForControllers() );

    ctrl_t::kernel_set_t* ptr_kernel_set =
        static_cast< ctrl_t::kernel_set_t* >( ptr_kset_base );

    ASSERT_TRUE( ptr_kernel_set != nullptr );
    status = ptr_kernel_set->initDefaultControllerKernels();
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        ASSERT_TRUE( ptr_kernel_set->requires( purpose ) );
        ASSERT_TRUE( ptr_kernel_set->available( purpose ) );
    }

    if( !ptr_kernel_set->ready() )
    {
        status = ptr_kernel_set->configureDefaultControllerKernels();
    }

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( ptr_kernel_set->ready() );

    ASSERT_TRUE( !ctrl_1a.isSyncWithKernelSet() );
    status = ctrl_1a.syncWithKernelSet();
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );

    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    /* Save the kernel_ids for the controller configuration */
    std::vector< kernel_config_id_t > release_arg0_kernel_ids(
        NUM_CTRL_PURPOSES, ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id = ptr_kernel_set->kernelConfigId(
            kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        release_arg0_kernel_ids[ ii ] = kernel_id;
        ASSERT_TRUE( kernel_id != ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );
    }

    /* Changing the variant and the argument set to the current values
     * should not raise any problems event though it's a none-op */

    bool can_change = ctrl_1a.canChangeVariantFlags( ctrl_1a.variant() );
    ASSERT_TRUE( can_change );

    status = ctrl_1a.changeVariantFlags( ctrl_1a.variant() );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] ==
            ptr_kernel_set->kernelConfigId(
                kernel_set_t::CONTROLLER_PURPOSES[ ii ] ) );
    }

    can_change = ctrl_1a.canChangeArgumentSet( key.argumentSet() );
    ASSERT_TRUE( can_change );

    status = ctrl_1a.changeArgumentSet( key.argumentSet() );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] ==
            ptr_kernel_set->kernelConfigId(
                kernel_set_t::CONTROLLER_PURPOSES[ ii ] ) );
    }

    /* Try to change variant and argument set to values for which we have no
     * kernels yet -> this should fail */

    can_change = ctrl_1a.canChangeVariantFlags( st::ARCH_VARIANT_DEBUG );
    ASSERT_TRUE( !can_change );
    status = ctrl_1a.changeVariantFlags( st::ARCH_VARIANT_DEBUG );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );

    SIXTRL_ASSERT( key.argumentSet() != ctrl_t::kernel_argument_set_t{ 1 } );
    can_change = ctrl_1a.canChangeArgumentSet(
        ctrl_t::kernel_argument_set_t{ 1 } );
    ASSERT_TRUE( !can_change );
    status = ctrl_1a.changeArgumentSet( ctrl_t::kernel_argument_set_t{ 1 } );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );

    /* Prepare kernel configs for the debug variant */

    SIXTRL_ASSERT( key.variant() != st::ARCH_VARIANT_DEBUG );
    key.setVariant( st::ARCH_VARIANT_DEBUG );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        std::ostringstream a2str;

        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        key.setPurpose( purpose );

        a2str << "dummy_kernel_config_debug_" << std::setfill( '0' )
              << std::setw( 2 ) << ii;

        status = store_1.setDefaultInitKernelConfigParameters(
            key, size_t{ 1 }, a2str.str() );

        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }

    /* Try again to change the variant -> this should work now */

    can_change = ctrl_1a.canChangeVariantFlags( st::ARCH_VARIANT_DEBUG );
    ASSERT_TRUE( can_change );
    status = ctrl_1a.changeVariantFlags( st::ARCH_VARIANT_DEBUG );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        ASSERT_TRUE( ptr_kernel_set->requires( purpose ) );
        ASSERT_TRUE( ptr_kernel_set->available( purpose ) );
        ASSERT_TRUE( ptr_kernel_set->ready( purpose ) );
    }

    ASSERT_TRUE( ptr_kernel_set->ready() );
    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    /* Save the kernel_ids for the controller configuration */
    std::vector< kernel_config_id_t > debug_arg0_kernel_ids(
        NUM_CTRL_PURPOSES, ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id = ptr_kernel_set->kernelConfigId(
            kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        debug_arg0_kernel_ids[ ii ] = kernel_id;
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] != kernel_id );
    }

    ASSERT_TRUE(  ctrl_1a.variant() == key.variant() );
    ASSERT_TRUE(  ctrl_1a.currentKey().isEqualExceptPurpose( key ) );
    ASSERT_FALSE( ctrl_1a.variantReleaseMode() );
    ASSERT_TRUE(  ctrl_1a.variantDebugMode() );

    /* Switch the variant back to the initial value: */

    SIXTRL_ASSERT( key.variant() != st::ARCH_VARIANT_NONE );
    can_change = ctrl_1a.canChangeVariantFlags( st::ARCH_VARIANT_NONE );
    ASSERT_TRUE( can_change );
    status = ctrl_1a.changeVariantFlags( st::ARCH_VARIANT_NONE );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        ASSERT_TRUE( ptr_kernel_set->requires( purpose ) );
        ASSERT_TRUE( ptr_kernel_set->available( purpose ) );
        ASSERT_TRUE( ptr_kernel_set->ready( purpose ) );
    }

    ASSERT_TRUE( ptr_kernel_set->ready() );
    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id = ptr_kernel_set->kernelConfigId(
            kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        ASSERT_TRUE( kernel_id != ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] == kernel_id );
        ASSERT_TRUE( debug_arg0_kernel_ids[ ii ] != kernel_id );
    }

    ASSERT_TRUE( ctrl_1a.variant() == st::ARCH_VARIANT_NONE );
    ASSERT_TRUE( ctrl_1a.currentKey().variant() == st::ARCH_VARIANT_NONE );
    ASSERT_TRUE( ctrl_1a.variantReleaseMode() );
    ASSERT_FALSE( ctrl_1a.variantDebugMode() );

    key = ctrl_1a.currentKey();

    /* Try again to change the argument set to values for which we still have no
     * kernels yet -> this should fail */

    SIXTRL_ASSERT( key.argumentSet() != ctrl_t::kernel_argument_set_t{ 1 } );
    can_change = ctrl_1a.canChangeArgumentSet(
        ctrl_t::kernel_argument_set_t{ 1 } );
    ASSERT_TRUE( !can_change );
    status = ctrl_1a.changeArgumentSet( ctrl_t::kernel_argument_set_t{ 1 } );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );

    /* Prepare kernel configs for the debug variant */

    SIXTRL_ASSERT( key.variant() == st::ARCH_VARIANT_NONE );
    key.setArgumentSet( ctrl_t::kernel_argument_set_t{ 1 } );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        std::ostringstream a2str;

        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        key.setPurpose( purpose );

        a2str << "dummy_kernel_config_argset1_" << std::setfill( '0' )
              << std::setw( 2 ) << ii;

        status = store_1.setDefaultInitKernelConfigParameters(
            key, size_t{ 1 }, a2str.str() );

        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }

    /* Try again to change the kernel argument set -> this should work now */

    SIXTRL_ASSERT( key.argumentSet() == ctrl_t::kernel_argument_set_t{ 1 } );
    can_change = ctrl_1a.canChangeArgumentSet(
        ctrl_t::kernel_argument_set_t{ 1 } );
    ASSERT_TRUE( can_change );
    status = ctrl_1a.changeArgumentSet( ctrl_t::kernel_argument_set_t{ 1 } );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        ASSERT_TRUE( ptr_kernel_set->requires( purpose ) );
        ASSERT_TRUE( ptr_kernel_set->available( purpose ) );
        ASSERT_TRUE( ptr_kernel_set->ready( purpose ) );
    }

    ASSERT_TRUE( ptr_kernel_set->ready() );
    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    /* Save the kernel_ids for the controller configuration */
    std::vector< kernel_config_id_t > release_arg1_kernel_ids(
        NUM_CTRL_PURPOSES, ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id =  ptr_kernel_set->kernelConfigId(
            kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        release_arg1_kernel_ids[ ii ] = kernel_id;

        ASSERT_TRUE( kernel_id != ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] != kernel_id );
        ASSERT_TRUE( debug_arg0_kernel_ids[ ii ]   != kernel_id );
    }

    ASSERT_TRUE( ctrl_1a.variant() == st::ARCH_VARIANT_NONE );
    ASSERT_TRUE( ctrl_1a.currentKey().variant() == st::ARCH_VARIANT_NONE );
    ASSERT_TRUE( ctrl_1a.currentKey().argumentSet() ==
                 ctrl_t::kernel_argument_set_t{ 1 } );

    /* Switch back to kernel argument set #0 */

    can_change = ctrl_1a.canChangeArgumentSet(
        ctrl_t::kernel_argument_set_t{ 0 } );
    ASSERT_TRUE( can_change );
    status = ctrl_1a.changeArgumentSet( ctrl_t::kernel_argument_set_t{ 0 } );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        ASSERT_TRUE( ptr_kernel_set->requires( purpose ) );
        ASSERT_TRUE( ptr_kernel_set->available( purpose ) );
        ASSERT_TRUE( ptr_kernel_set->ready( purpose ) );
    }

    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    ASSERT_TRUE( ctrl_1a.currentKey().argumentSet() ==
                 ctrl_t::kernel_argument_set_t{ 0 } );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id =  ptr_kernel_set->kernelConfigId(
            kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        ASSERT_TRUE( kernel_id != ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] == kernel_id );
        ASSERT_TRUE( debug_arg0_kernel_ids[ ii ]   != kernel_id );
    }

    /* We can not switch to debug / arg_set1 since there are no
     * kernels provided (only for release / arg_set1  and debug / arg_set0 ) */

    key.setVariant( st::ARCH_VARIANT_DEBUG );
    key.setArgumentSet( ctrl_t::kernel_argument_set_t{ 1 } );

    can_change = ctrl_1a.canChangeToKey( key );
    ASSERT_TRUE( !can_change );

    status = ctrl_1a.changeToKey( key );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( key.argumentSet() != ctrl_1a.currentKey().argumentSet() );
    ASSERT_TRUE( key.variant() != ctrl_1a.currentKey().variant() );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id = ptr_kernel_set->kernelConfigId(
            kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        ASSERT_TRUE( kernel_id == release_arg0_kernel_ids[ ii ] );
    }

    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    ASSERT_TRUE( ctrl_1a.variantReleaseMode() );
    ASSERT_FALSE( ctrl_1a.variantDebugMode() );

    ASSERT_TRUE( ctrl_1a.currentKey().argumentSet() ==
                 ctrl_t::kernel_argument_set_t{ 0 } );

    /* Prepare kernel configs for the missing combination of arg set 1 and
     * debug mode */

    key.setVariant( st::ARCH_VARIANT_DEBUG );
    key.setArgumentSet( ctrl_t::kernel_argument_set_t{ 1 } );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        std::ostringstream a2str;

        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        key.setPurpose( purpose );

        a2str << "dummy_kernel_config_debug_argset1_" << std::setfill( '0' )
              << std::setw( 2 ) << ii;

        status = store_1.setDefaultInitKernelConfigParameters(
            key, size_t{ 1 }, a2str.str() );

        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }

    /* Try to switch again -> should work now */

    can_change = ctrl_1a.canChangeToKey( key );
    ASSERT_TRUE( can_change );

    status = ctrl_1a.changeToKey( key );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    std::vector< kernel_config_id_t > debug_arg1_kernel_ids(
        NUM_CTRL_PURPOSES, ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id =  ptr_kernel_set->kernelConfigId(
            kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        debug_arg1_kernel_ids[ ii ] = kernel_id;

        ASSERT_TRUE( kernel_id != ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] != kernel_id );
        ASSERT_TRUE( release_arg1_kernel_ids[ ii ] != kernel_id );
        ASSERT_TRUE( debug_arg0_kernel_ids[ ii ]   != kernel_id );
    }

    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    ASSERT_FALSE( ctrl_1a.variantReleaseMode() );
    ASSERT_TRUE ( ctrl_1a.variantDebugMode() );
    ASSERT_TRUE(  ctrl_1a.currentKey().argumentSet() ==
                 ctrl_t::kernel_argument_set_t{ 1 } );
}

TEST( CXX_CommonControlControllerBase, SingleCtrlChangeVariantArgSetKeyExtLock )
{
    namespace st                = SIXTRL_CXX_NAMESPACE;
    using ctrl_t                = st::tests::TestControllerBase;
    using kernel_conf_store_t   = st::KernelConfigStore;
    using kernel_set_t          = st::KernelSetBase;
    using purpose_t             = st::kernel_purpose_t;
    using kernel_config_id_t    = ctrl_t::kernel_id_t;
    using size_t                = ctrl_t::size_type;
    using status_t              = ctrl_t::status_t;
    using arch_id_t             = ctrl_t::arch_id_t;

    size_t const NUM_CTRL_PURPOSES = kernel_set_t::NUM_CONTROLLER_PURPOSES;

    /* Create three dummy architectures to allow variation in the
     * node sets based on the arch_id parameter: */

    st::Architectures& archs = st::Architectures_get();
    static constexpr size_t NUM_ARCHS = size_t{ 1 };
    arch_id_t arch_id = st::NODE_UNDEFINED_INDEX;
    status_t status = st::tests::Architectures_setup(
        archs, NUM_ARCHS, arch_id_t{ 32 }, &arch_id );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    /* Create an empty external store */

    kernel_conf_store_t store_1;

    kernel_conf_store_t::lock_t lock( *store_1.lockable() );

    ASSERT_TRUE( store_1.numKernelSets( lock ) == size_t{ 0 } );
    ASSERT_TRUE( store_1.numStoredKernels( lock ) == size_t{ 0 } );

    /* Create first controller: */

    ctrl_t ctrl_1a( lock, arch_id, &store_1 );

    /* Check that ctrl_1a has the expected properties -> since there are
     * currently no kernels available, there is very little that should work */

    ASSERT_TRUE( arch_id == ctrl_1a.archId() );
    ASSERT_TRUE(  ctrl_1a.hasKernelConfigStore() );
    ASSERT_TRUE( !ctrl_1a.ownsKernelConfigStore() );
    ASSERT_TRUE(  static_cast< ctrl_t const& >( ctrl_1a ).ptrKernelConfigStore()
                  == &store_1 );

    ASSERT_TRUE(  ctrl_1a.kernelSetId( lock ) != ctrl_t::ILLEGAL_KERNEL_SET_ID );
    ASSERT_TRUE(  nullptr != ctrl_1a.ptrConstKernelSet( lock ) );

    ASSERT_TRUE( ctrl_1a.ptrConstKernelSet( lock ) != nullptr );
    ASSERT_TRUE( ctrl_1a.ptrConstKernelSet(
        lock )->numPurposes( lock ) == NUM_CTRL_PURPOSES );
    ASSERT_TRUE( ctrl_1a.hasKernelSet( lock ) );
    ASSERT_TRUE( ctrl_1a.variantReleaseMode() );

    ASSERT_TRUE( store_1.numKernelSets( lock ) == size_t{ 1 } );
    ASSERT_TRUE( store_1.hasKernelSet( lock, ctrl_1a.kernelSetId( lock ) ) );
    ASSERT_TRUE( store_1.hasKernelSet( lock,
        *ctrl_1a.ptrConstKernelSet( lock ) ) );

    ASSERT_TRUE(  ctrl_1a.ptrConstKernelSet( lock )->numPurposes( lock ) ==
                  kernel_set_t::NUM_CONTROLLER_PURPOSES );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose = kernel_set_t::CONTROLLER_PURPOSES[ ii ];

        ASSERT_TRUE( ctrl_1a.ptrConstKernelSet(
            lock )->requires( lock, purpose ) );

        ASSERT_FALSE( ctrl_1a.ptrConstKernelSet(
            lock )->available( lock, purpose ) );

        ASSERT_FALSE( ctrl_1a.ptrConstKernelSet(
            lock )->ready( lock, purpose ) );
    }

    ASSERT_TRUE(  ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( !ctrl_1a.readyForReceive() );
    ASSERT_TRUE( !ctrl_1a.readyForSend() );
    ASSERT_TRUE( !ctrl_1a.readyForRemap() );
    ASSERT_TRUE( !ctrl_1a.readyForRunningKernels() );

    /* Init default controller kernels: */

    ctrl_t::kernel_config_key_t key( ctrl_1a.currentKey( lock ) );
    ASSERT_TRUE( key.archId() == arch_id );
    ASSERT_TRUE( key.variant() == ctrl_1a.variant() );
    ASSERT_TRUE( key.argumentSet() == ctrl_t::kernel_argument_set_t{ 0 } );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        std::ostringstream a2str;

        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        key.setPurpose( purpose );

        a2str << "dummy_kernel_config_" << std::setfill( '0' ) << std::setw( 2 )
              << ii;

        status = store_1.setDefaultInitKernelConfigParameters(
            lock, key, size_t{ 1 }, a2str.str() );

        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }

    ctrl_t::kernel_set_base_t* ptr_kset_base = store_1.ptrKernelSetBase(
        lock, ctrl_1a.kernelSetId( lock ) );

    ASSERT_TRUE( ptr_kset_base != nullptr );
    ASSERT_TRUE( ptr_kset_base->isForControllers() );

    ctrl_t::kernel_set_t* ptr_kernel_set =
        static_cast< ctrl_t::kernel_set_t* >( ptr_kset_base );

    ASSERT_TRUE( ptr_kernel_set != nullptr );
    status = ptr_kernel_set->initDefaultControllerKernels( lock );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        ASSERT_TRUE( ptr_kernel_set->requires( lock, purpose ) );
        ASSERT_TRUE( ptr_kernel_set->available( lock, purpose ) );
    }

    if( !ptr_kernel_set->ready( lock ) )
    {
        status = ptr_kernel_set->configureDefaultControllerKernels( lock );
    }

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( ptr_kernel_set->ready( lock ) );

    ASSERT_TRUE( !ctrl_1a.isSyncWithKernelSet() );
    status = ctrl_1a.syncWithKernelSet( lock );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );

    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    /* Save the kernel_ids for the controller configuration */
    std::vector< kernel_config_id_t > release_arg0_kernel_ids(
        NUM_CTRL_PURPOSES, ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id = ptr_kernel_set->kernelConfigId(
            lock, kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        release_arg0_kernel_ids[ ii ] = kernel_id;
        ASSERT_TRUE( kernel_id != ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );
    }

    /* Changing the variant and the argument set to the current values
     * should not raise any problems event though it's a none-op */

    bool can_change = ctrl_1a.canChangeVariantFlags( lock, ctrl_1a.variant() );
    ASSERT_TRUE( can_change );

    status = ctrl_1a.changeVariantFlags( lock, ctrl_1a.variant() );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] ==
            ptr_kernel_set->kernelConfigId(
                lock, kernel_set_t::CONTROLLER_PURPOSES[ ii ] ) );
    }

    can_change = ctrl_1a.canChangeArgumentSet( lock, key.argumentSet() );
    ASSERT_TRUE( can_change );

    status = ctrl_1a.changeArgumentSet( lock, key.argumentSet() );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] ==
            ptr_kernel_set->kernelConfigId(
                lock, kernel_set_t::CONTROLLER_PURPOSES[ ii ] ) );
    }

    /* Try to change variant and argument set to values for which we have no
     * kernels yet -> this should fail */

    can_change = ctrl_1a.canChangeVariantFlags( lock, st::ARCH_VARIANT_DEBUG );
    ASSERT_TRUE( !can_change );
    status = ctrl_1a.changeVariantFlags( lock, st::ARCH_VARIANT_DEBUG );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );

    SIXTRL_ASSERT( key.argumentSet() != ctrl_t::kernel_argument_set_t{ 1 } );
    can_change = ctrl_1a.canChangeArgumentSet(
        lock, ctrl_t::kernel_argument_set_t{ 1 } );
    ASSERT_TRUE( !can_change );

    status = ctrl_1a.changeArgumentSet(
        lock, ctrl_t::kernel_argument_set_t{ 1 } );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );

    /* Prepare kernel configs for the debug variant */

    SIXTRL_ASSERT( key.variant() != st::ARCH_VARIANT_DEBUG );
    key.setVariant( st::ARCH_VARIANT_DEBUG );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        std::ostringstream a2str;

        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        key.setPurpose( purpose );

        a2str << "dummy_kernel_config_debug_" << std::setfill( '0' )
              << std::setw( 2 ) << ii;

        status = store_1.setDefaultInitKernelConfigParameters(
            lock, key, size_t{ 1 }, a2str.str() );

        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }

    /* Try again to change the variant -> this should work now */

    can_change = ctrl_1a.canChangeVariantFlags( lock, st::ARCH_VARIANT_DEBUG );
    ASSERT_TRUE( can_change );
    status = ctrl_1a.changeVariantFlags( lock, st::ARCH_VARIANT_DEBUG );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        ASSERT_TRUE( ptr_kernel_set->requires( lock, purpose ) );
        ASSERT_TRUE( ptr_kernel_set->available( lock, purpose ) );
        ASSERT_TRUE( ptr_kernel_set->ready( lock, purpose ) );
    }

    ASSERT_TRUE( ptr_kernel_set->ready( lock ) );
    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    /* Save the kernel_ids for the controller configuration */
    std::vector< kernel_config_id_t > debug_arg0_kernel_ids(
        NUM_CTRL_PURPOSES, ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id = ptr_kernel_set->kernelConfigId(
            lock, kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        debug_arg0_kernel_ids[ ii ] = kernel_id;
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] != kernel_id );
    }

    ASSERT_TRUE(  ctrl_1a.variant() == key.variant() );
    ASSERT_TRUE(  ctrl_1a.currentKey( lock ).isEqualExceptPurpose( key ) );
    ASSERT_FALSE( ctrl_1a.variantReleaseMode() );
    ASSERT_TRUE(  ctrl_1a.variantDebugMode() );

    /* Switch the variant back to the initial value: */

    SIXTRL_ASSERT( key.variant() != st::ARCH_VARIANT_NONE );
    can_change = ctrl_1a.canChangeVariantFlags( lock, st::ARCH_VARIANT_NONE );
    ASSERT_TRUE( can_change );

    status = ctrl_1a.changeVariantFlags( lock, st::ARCH_VARIANT_NONE );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        ASSERT_TRUE( ptr_kernel_set->requires( lock, purpose ) );
        ASSERT_TRUE( ptr_kernel_set->available( lock, purpose ) );
        ASSERT_TRUE( ptr_kernel_set->ready( lock, purpose ) );
    }

    ASSERT_TRUE( ptr_kernel_set->ready( lock ) );
    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id = ptr_kernel_set->kernelConfigId(
            lock, kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        ASSERT_TRUE( kernel_id != ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] == kernel_id );
        ASSERT_TRUE( debug_arg0_kernel_ids[ ii ] != kernel_id );
    }

    ASSERT_TRUE( ctrl_1a.variant() == st::ARCH_VARIANT_NONE );
    ASSERT_TRUE( ctrl_1a.currentKey(
        lock ).variant() == st::ARCH_VARIANT_NONE );

    ASSERT_TRUE( ctrl_1a.variantReleaseMode() );
    ASSERT_FALSE( ctrl_1a.variantDebugMode() );

    key = ctrl_1a.currentKey( lock );

    /* Try again to change the argument set to values for which we still have no
     * kernels yet -> this should fail */

    SIXTRL_ASSERT( key.argumentSet() != ctrl_t::kernel_argument_set_t{ 1 } );

    can_change = ctrl_1a.canChangeArgumentSet(
        lock, ctrl_t::kernel_argument_set_t{ 1 } );
    ASSERT_TRUE( !can_change );

    status = ctrl_1a.changeArgumentSet(
        lock, ctrl_t::kernel_argument_set_t{ 1 } );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );

    /* Prepare kernel configs for the debug variant */

    SIXTRL_ASSERT( key.variant() == st::ARCH_VARIANT_NONE );
    key.setArgumentSet( ctrl_t::kernel_argument_set_t{ 1 } );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        std::ostringstream a2str;

        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        key.setPurpose( purpose );

        a2str << "dummy_kernel_config_argset1_" << std::setfill( '0' )
              << std::setw( 2 ) << ii;

        status = store_1.setDefaultInitKernelConfigParameters(
            lock, key, size_t{ 1 }, a2str.str() );

        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }

    /* Try again to change the kernel argument set -> this should work now */

    SIXTRL_ASSERT( key.argumentSet() == ctrl_t::kernel_argument_set_t{ 1 } );
    can_change = ctrl_1a.canChangeArgumentSet(
        lock, ctrl_t::kernel_argument_set_t{ 1 } );
    ASSERT_TRUE( can_change );

    status = ctrl_1a.changeArgumentSet(
        lock, ctrl_t::kernel_argument_set_t{ 1 } );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        ASSERT_TRUE( ptr_kernel_set->requires( lock, purpose ) );
        ASSERT_TRUE( ptr_kernel_set->available( lock, purpose ) );
        ASSERT_TRUE( ptr_kernel_set->ready( lock, purpose ) );
    }

    ASSERT_TRUE( ptr_kernel_set->ready( lock ) );
    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    /* Save the kernel_ids for the controller configuration */
    std::vector< kernel_config_id_t > release_arg1_kernel_ids(
        NUM_CTRL_PURPOSES, ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id =  ptr_kernel_set->kernelConfigId(
            lock, kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        release_arg1_kernel_ids[ ii ] = kernel_id;

        ASSERT_TRUE( kernel_id != ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] != kernel_id );
        ASSERT_TRUE( debug_arg0_kernel_ids[ ii ]   != kernel_id );
    }

    ASSERT_TRUE( ctrl_1a.variant() == st::ARCH_VARIANT_NONE );
    ASSERT_TRUE( ctrl_1a.currentKey( lock ).variant() == st::ARCH_VARIANT_NONE );
    ASSERT_TRUE( ctrl_1a.currentKey( lock ).argumentSet() ==
                 ctrl_t::kernel_argument_set_t{ 1 } );

    /* Switch back to kernel argument set #0 */

    can_change = ctrl_1a.canChangeArgumentSet(
        lock, ctrl_t::kernel_argument_set_t{ 0 } );
    ASSERT_TRUE( can_change );

    status = ctrl_1a.changeArgumentSet(
        lock, ctrl_t::kernel_argument_set_t{ 0 } );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        ASSERT_TRUE( ptr_kernel_set->requires( lock, purpose ) );
        ASSERT_TRUE( ptr_kernel_set->available( lock, purpose ) );
        ASSERT_TRUE( ptr_kernel_set->ready( lock, purpose ) );
    }

    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    ASSERT_TRUE( ctrl_1a.currentKey( lock ).argumentSet() ==
                 ctrl_t::kernel_argument_set_t{ 0 } );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id =  ptr_kernel_set->kernelConfigId(
            lock, kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        ASSERT_TRUE( kernel_id != ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] == kernel_id );
        ASSERT_TRUE( debug_arg0_kernel_ids[ ii ]   != kernel_id );
    }

    /* We can not switch to debug / arg_set1 since there are no
     * kernels provided (only for release / arg_set1  and debug / arg_set0 ) */

    key.setVariant( st::ARCH_VARIANT_DEBUG );
    key.setArgumentSet( ctrl_t::kernel_argument_set_t{ 1 } );

    can_change = ctrl_1a.canChangeToKey( lock, key );
    ASSERT_TRUE( !can_change );

    status = ctrl_1a.changeToKey( lock, key );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( key.argumentSet() != ctrl_1a.currentKey( lock ).argumentSet() );
    ASSERT_TRUE( key.variant() != ctrl_1a.currentKey( lock ).variant() );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id = ptr_kernel_set->kernelConfigId(
            lock, kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        ASSERT_TRUE( kernel_id == release_arg0_kernel_ids[ ii ] );
    }

    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    ASSERT_TRUE(  ctrl_1a.variantReleaseMode() );
    ASSERT_FALSE( ctrl_1a.variantDebugMode() );

    ASSERT_TRUE( ctrl_1a.currentKey( lock ).argumentSet() ==
                 ctrl_t::kernel_argument_set_t{ 0 } );

    /* Prepare kernel configs for the missing combination of arg set 1 and
     * debug mode */

    key.setVariant( st::ARCH_VARIANT_DEBUG );
    key.setArgumentSet( ctrl_t::kernel_argument_set_t{ 1 } );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        std::ostringstream a2str;

        purpose_t const purpose( kernel_set_t::CONTROLLER_PURPOSES[ ii ] );
        key.setPurpose( purpose );

        a2str << "dummy_kernel_config_debug_argset1_" << std::setfill( '0' )
              << std::setw( 2 ) << ii;

        status = store_1.setDefaultInitKernelConfigParameters(
            lock, key, size_t{ 1 }, a2str.str() );

        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }

    /* Try to switch again -> should work now */

    can_change = ctrl_1a.canChangeToKey( lock, key );
    ASSERT_TRUE( can_change );

    status = ctrl_1a.changeToKey( lock, key );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    std::vector< kernel_config_id_t > debug_arg1_kernel_ids(
        NUM_CTRL_PURPOSES, ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        kernel_config_id_t const kernel_id =  ptr_kernel_set->kernelConfigId(
            lock, kernel_set_t::CONTROLLER_PURPOSES[ ii ] );

        debug_arg1_kernel_ids[ ii ] = kernel_id;

        ASSERT_TRUE( kernel_id != ctrl_t::ILLEGAL_KERNEL_CONFIG_ID );
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] != kernel_id );
        ASSERT_TRUE( release_arg1_kernel_ids[ ii ] != kernel_id );
        ASSERT_TRUE( debug_arg0_kernel_ids[ ii ]   != kernel_id );
    }

    ASSERT_TRUE( ctrl_1a.isSyncWithKernelSet() );
    ASSERT_TRUE( ctrl_1a.readyForReceive() );
    ASSERT_TRUE( ctrl_1a.readyForSend() );
    ASSERT_TRUE( ctrl_1a.readyForRemap() );
    ASSERT_TRUE( ctrl_1a.readyForRunningKernels() );

    ASSERT_FALSE( ctrl_1a.variantReleaseMode() );
    ASSERT_TRUE ( ctrl_1a.variantDebugMode() );
    ASSERT_TRUE(  ctrl_1a.currentKey( lock ).argumentSet() ==
                 ctrl_t::kernel_argument_set_t{ 1 } );
}

/* end: tests/sixtracklib/common/control/test_controller_base_cxx.cpp */
