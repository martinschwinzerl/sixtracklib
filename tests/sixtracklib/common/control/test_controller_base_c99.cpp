#include "sixtracklib/common/control/controller_base.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/architecture/architecture.h"
#include "sixtracklib/common/control/kernel_config_store.h"
#include "sixtracklib/common/control/kernel_config_base.h"
#include "sixtracklib/common/control/kernel_set.h"

#include "sixtracklib/testlib.h"

TEST( C99_CommonControlControllerBase, SingleCtrlChangeVariantArgSetKey )
{
    using ctrl_t                = ::NS(TestControllerBase);
    using kernel_conf_store_t   = ::NS(KernelConfigStore);
    using purpose_t             = ::NS(kernel_purpose_t);
    using kernel_config_id_t    = ::NS(ctrl_kernel_id_t);
    using size_t                = ::NS(arch_size_t);
    using status_t              = ::NS(arch_status_t);
    using arch_id_t             = ::NS(arch_id_t);
    using kernel_arg_set_t      = ::NS(kernel_argument_set_t);
    using kernel_set_base_t     = ::NS(KernelSetBase);
    using ctrl_set_t            = ::NS(ControllerKernelSetBase);

    size_t const NUM_CTRL_PURPOSES =
        ::NS(KernelSet_get_num_default_controller_purposes)();

    /* Create three dummy architectures to allow variation in the
     * node sets based on the arch_id parameter: */

    ::NS(Architectures)* ptr_archs = ::NS(Architectures_get_ptr)();

    static constexpr size_t NUM_ARCHS = size_t{ 1 };
    arch_id_t arch_id = ::NS(NODE_UNDEFINED_INDEX);
    status_t status = ::NS(Architectures_setup)(
        ptr_archs, NUM_ARCHS, arch_id_t{ 32 }, &arch_id );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    /* Create an empty external store */

    kernel_conf_store_t* store_1 = ::NS(KernelConfigStore_create)();
    ASSERT_TRUE( store_1 != nullptr );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_num_kernel_sets)( store_1 ) ==
                 size_t{ 0 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_num_stored_kernels)( store_1 ) ==
                 size_t{ 0 } );

    /* Create first controller: */

    ctrl_t* ctrl_1a = ::NS(TestControllerBase_new_with_ext_kernel_store)(
        arch_id, store_1, ::NS(ARCH_ILLEGAL_KERNEL_SET_ID), nullptr );

    ASSERT_TRUE( ctrl_1a != nullptr );

    /* Check that ctrl_1a has the expected properties -> since there are
     * currently no kernels available, there is very little that should work */

    ASSERT_TRUE( arch_id == ::NS(Controller_get_arch_id)( ctrl_1a ) );
    ASSERT_TRUE(  ::NS(Controller_has_kernel_config_store)( ctrl_1a ) );
    ASSERT_TRUE( !::NS(Controller_owns_kernel_config_store)( ctrl_1a ) );
    ASSERT_TRUE(  ::NS(Controller_get_ptr_const_kernel_config_store)( ctrl_1a )
                  == store_1 );

    ASSERT_TRUE(  ::NS(Controller_get_kernel_set_id)( ctrl_1a ) !=
                  ::NS(ARCH_ILLEGAL_KERNEL_SET_ID) );

    ASSERT_TRUE(  ::NS(Controller_get_ptr_const_kernel_set)(
                    ctrl_1a ) != nullptr );

    ASSERT_TRUE( ::NS(KernelSet_get_num_of_purposes)(
        ::NS(Controller_get_ptr_const_kernel_set)( ctrl_1a ) ) ==
            NUM_CTRL_PURPOSES );

    ASSERT_TRUE( ::NS(Controller_has_kernel_set)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_get_ptr_const_kernel_set)(
                    ctrl_1a ) != nullptr );

    ASSERT_TRUE( ::NS(Controller_variant_release_mode)( ctrl_1a ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_num_kernel_sets)(
                    store_1 ) == size_t{ 1 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel_set)( store_1,
                    ::NS(Controller_get_kernel_set_id)( ctrl_1a ) ) );

    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel_set_by_ptr)( store_1,
                    ::NS(Controller_get_ptr_const_kernel_set)( ctrl_1a ) ) );

    ASSERT_TRUE( ::NS(KernelSet_get_num_of_purposes)(
        ::NS(Controller_get_ptr_const_kernel_set)( ctrl_1a ) )==
            NUM_CTRL_PURPOSES );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        ASSERT_TRUE( ::NS(KernelSet_requires)(
            ::NS(Controller_get_ptr_const_kernel_set)( ctrl_1a ), purpose ) );

        ASSERT_FALSE( ::NS(KernelSet_is_available)(
            ::NS(Controller_get_ptr_const_kernel_set)( ctrl_1a ), purpose ) );

        ASSERT_FALSE( ::NS(KernelSet_is_ready)(
            ::NS(Controller_get_ptr_const_kernel_set)( ctrl_1a ), purpose ) );
    }

    ASSERT_TRUE(  ::NS(Controller_is_sync_with_kernel_set)( ctrl_1a ) );
    ASSERT_TRUE( !::NS(Controller_is_ready_for_send)( ctrl_1a ) );
    ASSERT_TRUE( !::NS(Controller_is_ready_for_receive)( ctrl_1a ) );
    ASSERT_TRUE( !::NS(Controller_is_ready_for_remap)( ctrl_1a ) );
    ASSERT_TRUE( !::NS(Controller_is_ready_for_running_kernel)( ctrl_1a ) );

    /* Init default controller kernels: */

    ::NS(KernelConfigKey)* key = ::NS(KernelConfigKey_new_from_copy)(
        ::NS(Controller_get_current_key)( ctrl_1a ) );
    SIXTRL_ASSERT( key != nullptr );

    ASSERT_TRUE( ::NS(KernelConfigKey_get_arch_id)( key ) == arch_id );
    ASSERT_TRUE( ::NS(KernelConfigKey_get_variant)( key ) ==
                 ::NS(Controller_get_variant)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(KernelConfigKey_get_argument_set)( key ) ==
                 kernel_arg_set_t{ 0 } );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        std::ostringstream a2str;

        ::NS(KernelConfigKey_set_purpose)( key,
            ::NS(KernelSet_get_default_controller_purpose)( ii ) );

        a2str << "dummy_kernel_config_" << std::setfill( '0' ) << std::setw( 2 )
              << ii;

        std::string const temp_str( a2str.str() );

        status = ::NS(KernelConfigStore_set_default_init_kernel_config_parameters)(
            store_1, key, size_t{ 1 }, temp_str.c_str() );

        ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    }

    kernel_set_base_t* ptr_kernel_set_base =
        ::NS(KernelConfigStore_get_ptr_kernel_set)( store_1,
            ::NS(Controller_get_kernel_set_id)( ctrl_1a ) );

    ASSERT_TRUE( ptr_kernel_set_base != nullptr );
    ASSERT_TRUE( ::NS(KernelSet_is_for_controllers)( ptr_kernel_set_base ) );

    ctrl_set_t* ptr_kernel_set = ( ctrl_set_t* )ptr_kernel_set_base;
    ASSERT_TRUE( ptr_kernel_set != nullptr );

    status = ::NS(ControllerKernelSet_init_default_controller_kernels)(
        ptr_kernel_set );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        ASSERT_TRUE( ::NS(KernelSet_requires)( ptr_kernel_set, purpose ) );
        ASSERT_TRUE( ::NS(KernelSet_is_available)( ptr_kernel_set, purpose ) );
    }

    if( !::NS(KernelSet_are_ready)( ptr_kernel_set ) )
    {
        status = ::NS(ControllerKernelSet_configure_remap_buffer_kernel_config)(
            ptr_kernel_set );
    }

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(KernelSet_are_ready)( ptr_kernel_set ) );

    ASSERT_TRUE( !::NS(Controller_is_sync_with_kernel_set)( ctrl_1a ) );
    status = ::NS(Controller_sync_with_kernel_set)( ctrl_1a );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(Controller_is_sync_with_kernel_set)( ctrl_1a ) );

    ASSERT_TRUE( ::NS(Controller_is_ready_for_send)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_receive)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_remap)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_running_kernel)( ctrl_1a ) );

    /* Save the kernel_ids for the controller configuration */
    std::vector< kernel_config_id_t > release_arg0_kernel_ids(
        NUM_CTRL_PURPOSES, ::NS(ARCH_ILLEGAL_KERNEL_CONFIG_ID) );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        kernel_config_id_t const kernel_id =
            ::NS(KernelSet_get_kernel_config_id)( ptr_kernel_set, purpose );

        release_arg0_kernel_ids[ ii ] = kernel_id;
        ASSERT_TRUE( kernel_id != ::NS(ARCH_ILLEGAL_KERNEL_CONFIG_ID) );
    }

    /* Changing the variant and the argument set to the current values
     * should not raise any problems event though it's a none-op */

    bool can_change = ::NS(Controller_can_change_variant_flags)( ctrl_1a,
        ::NS(Controller_get_variant)( ctrl_1a ) );
    ASSERT_TRUE( can_change );

    status = ::NS(Controller_change_variant_flags)( ctrl_1a,
        ::NS(Controller_get_variant)( ctrl_1a ) );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] ==
            ::NS(KernelSet_get_kernel_config_id)( ptr_kernel_set, purpose ) );
    }

    can_change = ::NS(Controller_can_change_argument_set)(
        ctrl_1a, ::NS(KernelConfigKey_get_argument_set)( key ) );
    ASSERT_TRUE( can_change );

    status = ::NS(Controller_change_argument_set)(
        ctrl_1a, ::NS(KernelConfigKey_get_argument_set)( key ) );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] ==
            ::NS(KernelSet_get_kernel_config_id)( ptr_kernel_set, purpose ) );
    }

    /* Try to change variant and argument set to values for which we have no
     * kernels yet -> this should fail */

    can_change = ::NS(Controller_can_change_variant_flags)(
        ctrl_1a, ::NS(ARCH_VARIANT_DEBUG) );
    ASSERT_TRUE( !can_change );

    status = ::NS(Controller_change_variant_flags)(
        ctrl_1a, ::NS(ARCH_VARIANT_DEBUG) );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );

    SIXTRL_ASSERT( ::NS(KernelConfigKey_get_argument_set)( key ) != kernel_arg_set_t{ 1 } );
    can_change = ::NS(Controller_can_change_argument_set)(
        ctrl_1a, kernel_arg_set_t{ 1 } );
    ASSERT_TRUE( !can_change );

    status = ::NS(Controller_change_argument_set)(
        ctrl_1a, kernel_arg_set_t{ 1 } );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );

    /* Prepare kernel configs for the debug variant */

    SIXTRL_ASSERT( ::NS(KernelConfigKey_get_variant)(
        key ) != ::NS(ARCH_VARIANT_DEBUG) );
    ::NS(KernelConfigKey_set_variant)( key,  ::NS(ARCH_VARIANT_DEBUG) );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        std::ostringstream a2str;

        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        ::NS(KernelConfigKey_set_purpose)( key,  purpose );

        a2str << "dummy_kernel_config_debug_" << std::setfill( '0' )
              << std::setw( 2 ) << ii;

        std::string const temp_str( a2str.str() );

        status = ::NS(KernelConfigStore_set_default_init_kernel_config_parameters)(
            store_1, key, size_t{ 1 }, temp_str.c_str() );

        ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    }

    /* Try again to change the variant -> this should work now */

    can_change = ::NS(Controller_can_change_variant_flags)(
        ctrl_1a, ::NS(ARCH_VARIANT_DEBUG) );
    ASSERT_TRUE( can_change );

    status = ::NS(Controller_change_variant_flags)(
        ctrl_1a, ::NS(ARCH_VARIANT_DEBUG) );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        ASSERT_TRUE( ::NS(KernelSet_requires)( ptr_kernel_set, purpose ) );
        ASSERT_TRUE( ::NS(KernelSet_is_available)( ptr_kernel_set, purpose ) );
        ASSERT_TRUE( ::NS(KernelSet_is_ready)( ptr_kernel_set, purpose ) );
    }

    ASSERT_TRUE( ::NS(KernelSet_are_ready)( ptr_kernel_set ) );
    ASSERT_TRUE( ::NS(Controller_is_sync_with_kernel_set)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_send)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_receive)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_remap)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_running_kernel)( ctrl_1a ) );

    /* Save the kernel_ids for the controller configuration */
    std::vector< kernel_config_id_t > debug_arg0_kernel_ids(
        NUM_CTRL_PURPOSES, ::NS(ARCH_ILLEGAL_KERNEL_CONFIG_ID) );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        kernel_config_id_t const kernel_id =
            ::NS(KernelSet_get_kernel_config_id)( ptr_kernel_set, purpose );

        debug_arg0_kernel_ids[ ii ] = kernel_id;
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] != kernel_id );
    }

    ASSERT_TRUE(  ::NS(Controller_get_variant)( ctrl_1a ) ==
                  ::NS(KernelConfigKey_get_variant)( key ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_are_equal_except_purpose)(
        ::NS(Controller_get_current_key)( ctrl_1a ), key ) );
    ASSERT_FALSE( ::NS(Controller_variant_release_mode)( ctrl_1a ) );
    ASSERT_TRUE(  ::NS(Controller_variant_debug_mode)( ctrl_1a ) );

    /* Switch the variant back to the initial value: */

    SIXTRL_ASSERT( ::NS(KernelConfigKey_get_variant)( key )
                    != ::NS(ARCH_VARIANT_NONE) );

    can_change = ::NS(Controller_can_change_variant_flags)(
        ctrl_1a, ::NS(ARCH_VARIANT_NONE) );
    ASSERT_TRUE( can_change );

    status = ::NS(Controller_change_variant_flags)(
        ctrl_1a, ::NS(ARCH_VARIANT_NONE) );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        ASSERT_TRUE( ::NS(KernelSet_requires)( ptr_kernel_set, purpose ) );
        ASSERT_TRUE( ::NS(KernelSet_is_available)( ptr_kernel_set, purpose ) );
        ASSERT_TRUE( ::NS(KernelSet_is_ready)( ptr_kernel_set, purpose ) );
    }

    ASSERT_TRUE( ::NS(KernelSet_are_ready)( ptr_kernel_set ) );
    ASSERT_TRUE( ::NS(Controller_is_sync_with_kernel_set)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_send)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_receive)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_remap)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_running_kernel)( ctrl_1a ) );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        kernel_config_id_t const kernel_id =
            ::NS(KernelSet_get_kernel_config_id)( ptr_kernel_set, purpose );

        ASSERT_TRUE( kernel_id != ::NS(ARCH_ILLEGAL_KERNEL_CONFIG_ID) );
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] == kernel_id );
        ASSERT_TRUE( debug_arg0_kernel_ids[ ii ] != kernel_id );
    }

    ASSERT_TRUE( ::NS(Controller_get_variant)( ctrl_1a ) ==
        ::NS(ARCH_VARIANT_NONE) );

    ASSERT_TRUE( ::NS(KernelConfigKey_get_variant)(
        ::NS(Controller_get_current_key)( ctrl_1a ) ) ==
            ::NS(ARCH_VARIANT_NONE) );

    ASSERT_TRUE( ::NS(Controller_variant_release_mode)( ctrl_1a ) );
    ASSERT_FALSE( ::NS(Controller_variant_debug_mode)( ctrl_1a ) );

    ::NS(KernelConfigKey_assign_from)( key,
        ::NS(Controller_get_current_key)( ctrl_1a ) );

    /* Try again to change the argument set to values for which we still have no
     * kernels yet -> this should fail */

    SIXTRL_ASSERT( ::NS(KernelConfigKey_get_argument_set)( key ) != kernel_arg_set_t{ 1 } );
    can_change = ::NS(Controller_can_change_argument_set)( ctrl_1a, kernel_arg_set_t{ 1 } );
    ASSERT_TRUE( !can_change );
    status = ::NS(Controller_change_argument_set)( ctrl_1a, kernel_arg_set_t{ 1 } );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );

    /* Prepare kernel configs for the debug variant */

    SIXTRL_ASSERT( ::NS(KernelConfigKey_get_variant)( key ) == ::NS(ARCH_VARIANT_NONE) );
    ::NS(KernelConfigKey_set_argument_set)( key, kernel_arg_set_t{ 1 } );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        std::ostringstream a2str;

        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        ::NS(KernelConfigKey_set_purpose)( key,  purpose );

        a2str << "dummy_kernel_config_argset1_" << std::setfill( '0' )
              << std::setw( 2 ) << ii;

        std::string const temp_str( a2str.str() );

        status = ::NS(KernelConfigStore_set_default_init_kernel_config_parameters)(
            store_1, key, size_t{ 1 }, temp_str.c_str() );

        ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    }

    /* Try again to change the kernel argument set -> this should work now */

    SIXTRL_ASSERT( ::NS(KernelConfigKey_get_argument_set)( key ) == kernel_arg_set_t{ 1 } );
    can_change = ::NS(Controller_can_change_argument_set)( ctrl_1a, kernel_arg_set_t{ 1 } );
    ASSERT_TRUE( can_change );
    status = ::NS(Controller_change_argument_set)( ctrl_1a, kernel_arg_set_t{ 1 } );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        ASSERT_TRUE( ::NS(KernelSet_requires)( ptr_kernel_set, purpose ) );
        ASSERT_TRUE( ::NS(KernelSet_is_available)( ptr_kernel_set, purpose ) );
        ASSERT_TRUE( ::NS(KernelSet_is_ready)( ptr_kernel_set, purpose ) );
    }

    ASSERT_TRUE( ::NS(KernelSet_are_ready)( ptr_kernel_set ) );
    ASSERT_TRUE( ::NS(Controller_is_sync_with_kernel_set)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_send)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_receive)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_remap)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_running_kernel)( ctrl_1a ) );

    /* Save the kernel_ids for the controller configuration */
    std::vector< kernel_config_id_t > release_arg1_kernel_ids(
        NUM_CTRL_PURPOSES, ::NS(ARCH_ILLEGAL_KERNEL_CONFIG_ID) );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        kernel_config_id_t const kernel_id =
            ::NS(KernelSet_get_kernel_config_id)( ptr_kernel_set, purpose );

        release_arg1_kernel_ids[ ii ] = kernel_id;

        ASSERT_TRUE( kernel_id != ::NS(ARCH_ILLEGAL_KERNEL_CONFIG_ID) );
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] != kernel_id );
        ASSERT_TRUE( debug_arg0_kernel_ids[ ii ]   != kernel_id );
    }

    ASSERT_TRUE( ::NS(Controller_get_variant)( ctrl_1a ) ==
                 ::NS(ARCH_VARIANT_NONE) );

    ASSERT_TRUE( ::NS(KernelConfigKey_get_variant)(
        ::NS(Controller_get_current_key)( ctrl_1a ) ) ==
            ::NS(ARCH_VARIANT_NONE) );

    ASSERT_TRUE( ::NS(KernelConfigKey_get_argument_set)(
        ::NS(Controller_get_current_key)( ctrl_1a ) ) ==
            kernel_arg_set_t{ 1 } );

    /* Switch back to kernel argument set #0 */

    can_change = ::NS(Controller_can_change_argument_set)(
        ctrl_1a, kernel_arg_set_t{ 0 } );

    ASSERT_TRUE( can_change );
    status = ::NS(Controller_change_argument_set)(
        ctrl_1a, kernel_arg_set_t{ 0 } );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        ASSERT_TRUE( ::NS(KernelSet_requires)( ptr_kernel_set, purpose ) );
        ASSERT_TRUE( ::NS(KernelSet_is_available)( ptr_kernel_set, purpose ) );
        ASSERT_TRUE( ::NS(KernelSet_is_ready)( ptr_kernel_set, purpose ) );
    }

    ASSERT_TRUE( ::NS(Controller_is_sync_with_kernel_set)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_send)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_receive)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_remap)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_running_kernel)( ctrl_1a ) );

    ASSERT_TRUE( ::NS(KernelConfigKey_get_argument_set)(
        ::NS(Controller_get_current_key)( ctrl_1a ) ) ==
            kernel_arg_set_t{ 0 } );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        kernel_config_id_t const kernel_id =
            ::NS(KernelSet_get_kernel_config_id)( ptr_kernel_set, purpose );

        ASSERT_TRUE( kernel_id != ::NS(ARCH_ILLEGAL_KERNEL_CONFIG_ID) );
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] == kernel_id );
        ASSERT_TRUE( debug_arg0_kernel_ids[ ii ]   != kernel_id );
    }

    /* We can not switch to debug / arg_set1 since there are no
     * kernels provided (only for release / arg_set1  and debug / arg_set0 ) */

    ::NS(KernelConfigKey_set_variant)( key,  ::NS(ARCH_VARIANT_DEBUG) );
    ::NS(KernelConfigKey_set_argument_set)( key, kernel_arg_set_t{ 1 } );

    can_change = ::NS(Controller_can_change_to_key)( ctrl_1a, key );
    ASSERT_TRUE( !can_change );

    status = ::NS(Controller_change_to_key)( ctrl_1a, key );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(KernelConfigKey_get_argument_set)( key ) !=
                 ::NS(KernelConfigKey_get_argument_set)(
                    ::NS(Controller_get_current_key)( ctrl_1a ) ) );

    ASSERT_TRUE( ::NS(KernelConfigKey_get_variant)( key ) !=
                 ::NS(KernelConfigKey_get_variant)(
                    ::NS(Controller_get_current_key)( ctrl_1a ) ) );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        kernel_config_id_t const kernel_id =
            ::NS(KernelSet_get_kernel_config_id)( ptr_kernel_set, purpose );

        ASSERT_TRUE( kernel_id == release_arg0_kernel_ids[ ii ] );
    }

    ASSERT_TRUE( ::NS(Controller_is_sync_with_kernel_set)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_send)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_receive)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_remap)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_running_kernel)( ctrl_1a ) );

    ASSERT_TRUE( ::NS(Controller_variant_release_mode)( ctrl_1a ) );
    ASSERT_FALSE( ::NS(Controller_variant_debug_mode)( ctrl_1a ) );

    ASSERT_TRUE( ::NS(KernelConfigKey_get_argument_set)(
        ::NS(Controller_get_current_key)( ctrl_1a ) ) ==
            kernel_arg_set_t{ 0 } );

    /* Prepare kernel configs for the missing combination of arg set 1 and
     * debug mode */

    ::NS(KernelConfigKey_set_variant)( key,  ::NS(ARCH_VARIANT_DEBUG) );
    ::NS(KernelConfigKey_set_argument_set)( key, kernel_arg_set_t{ 1 } );

    for( size_t ii = size_t{ 0 }; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        std::ostringstream a2str;

        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        ::NS(KernelConfigKey_set_purpose)( key,  purpose );

        a2str << "dummy_kernel_config_debug_argset1_" << std::setfill( '0' )
              << std::setw( 2 ) << ii;

        std::string const temp_str( a2str.str() );

        status = ::NS(KernelConfigStore_set_default_init_kernel_config_parameters)(
            store_1, key, size_t{ 1 }, temp_str.c_str() );

        ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    }

    /* Try to switch again -> should work now */

    can_change = ::NS(Controller_can_change_to_key)( ctrl_1a, key );
    ASSERT_TRUE( can_change );

    status = ::NS(Controller_change_to_key)( ctrl_1a, key );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    std::vector< kernel_config_id_t > debug_arg1_kernel_ids(
        NUM_CTRL_PURPOSES, ::NS(ARCH_ILLEGAL_KERNEL_CONFIG_ID) );

    for( size_t ii = size_t{ 0 } ; ii < NUM_CTRL_PURPOSES ; ++ii )
    {
        purpose_t const purpose =
            ::NS(KernelSet_get_default_controller_purpose)( ii );

        kernel_config_id_t const kernel_id =
            ::NS(KernelSet_get_kernel_config_id)( ptr_kernel_set, purpose );

        debug_arg1_kernel_ids[ ii ] = kernel_id;

        ASSERT_TRUE( kernel_id != ::NS(ARCH_ILLEGAL_KERNEL_CONFIG_ID) );
        ASSERT_TRUE( release_arg0_kernel_ids[ ii ] != kernel_id );
        ASSERT_TRUE( release_arg1_kernel_ids[ ii ] != kernel_id );
        ASSERT_TRUE( debug_arg0_kernel_ids[ ii ]   != kernel_id );
    }

    ASSERT_TRUE( ::NS(Controller_is_sync_with_kernel_set)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_send)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_receive)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_remap)( ctrl_1a ) );
    ASSERT_TRUE( ::NS(Controller_is_ready_for_running_kernel)( ctrl_1a ) );

    ASSERT_FALSE( ::NS(Controller_variant_release_mode)( ctrl_1a ) );
    ASSERT_TRUE ( ::NS(Controller_variant_debug_mode)( ctrl_1a ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_argument_set)(
        ::NS(Controller_get_current_key)( ctrl_1a ) ) ==
            kernel_arg_set_t{ 1 } );

    /* --------------------------------------------------------------------- */

    ::NS(Controller_delete)( ctrl_1a );
    ::NS(KernelConfigKey_delete)( key );
    ::NS(KernelConfigStore_delete)( store_1 );
}

/* end: tests/sixtracklib/common/control/test_controller_base_c99.cpp */
