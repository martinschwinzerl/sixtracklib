#include "sixtracklib/common/control/kernel_config_key.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"
#include "sixtracklib/common/architecture/architecture.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/testlib.h"

TEST( C99_CommonControlKernelConfigKeyTests, MinimalUsage )
{
    using key_t         = ::NS(KernelConfigKey);
    using size_t        = ::NS(ctrl_size_t);
    using arch_id_t     = ::NS(arch_id_t);
    using node_id_t     = ::NS(NodeId);
    using platform_id_t = ::NS(node_platform_id_t);
    using device_id_t   = ::NS(node_device_id_t);
    using status_t      = ::NS(arch_status_t);

    /* Verify that a suitable arch is available */
    ::NS(Architectures) const* ptr_archs = ::NS(Architectures_get_const_ptr)();
    SIXTRL_ASSERT( ptr_archs != nullptr );
    SIXTRL_ASSERT( ::NS(Architectures_get_num_architectures)( ptr_archs ) >
        size_t{ 0 } );

    arch_id_t const arch = ::NS(Architectures_get_arch_id_by_number)(
        ptr_archs, size_t{ 0 } );
    SIXTRL_ASSERT( arch != ::NS(ARCHITECTURE_ILLEGAL) );
    SIXTRL_ASSERT( arch != ::NS(ARCHITECTURE_NONE) );
    SIXTRL_ASSERT(  ::NS(Architectures_has_architecture)( ptr_archs, arch ) );
    SIXTRL_ASSERT(  ::NS(Architectures_has_arch_str)( ptr_archs, arch ) );

    /* --------------------------------------------------------------------- */

    key_t* key_a = ::NS(KernelConfigKey_create)();

    ASSERT_TRUE( key_a != nullptr );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_arch_id)( key_a )  ==
                  ::NS(ARCHITECTURE_ILLEGAL) );
    ASSERT_TRUE( !::NS(KernelConfigKey_has_node_id)( key_a ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_purpose)( key_a ) ==
                  ::NS(KERNEL_CONFIG_PURPOSE_UNSPECIFIED) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_variant)( key_a ) ==
                  ::NS(ARCH_VARIANT_NONE) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_argument_set)( key_a ) ==
                  ::NS(DEFAULT_KERNEL_ARGUMENT_SET) );
    ASSERT_TRUE( !::NS(KernelConfigKey_has_config_str)( key_a ) );
    ASSERT_TRUE( !::NS(KernelConfigKey_is_valid)( key_a ) );

    status_t status = ::NS(KernelConfigKey_reset_detailed)( key_a, arch,
        ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER), ::NS(ARCH_VARIANT_NONE),
        ::NS(DEFAULT_KERNEL_ARGUMENT_SET), nullptr,
        ::NS(NODE_ILLEGAL_PLATFORM_ID), ::NS(NODE_ILLEGAL_DEVICE_ID) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_get_arch_id)( key_a )  == arch );
    ASSERT_TRUE( !::NS(KernelConfigKey_has_node_id)( key_a ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_purpose)( key_a ) ==
                  ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_variant)( key_a ) ==
                  ::NS(ARCH_VARIANT_NONE) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_argument_set)( key_a ) ==
                  ::NS(DEFAULT_KERNEL_ARGUMENT_SET) );
    ASSERT_TRUE( !::NS(KernelConfigKey_has_config_str)( key_a ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_is_valid)( key_a ) );

    key_t* key_b = ::NS(KernelConfigKey_new_from_copy)( key_a );

    ASSERT_TRUE( key_b != nullptr );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_arch_id)( key_b )  == arch );
    ASSERT_TRUE( !::NS(KernelConfigKey_has_node_id)( key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_purpose)( key_b ) ==
                  ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_variant)( key_b ) ==
                  ::NS(ARCH_VARIANT_NONE) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_argument_set)( key_b ) ==
                  ::NS(DEFAULT_KERNEL_ARGUMENT_SET) );
    ASSERT_TRUE( !::NS(KernelConfigKey_has_config_str)( key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_is_valid)( key_b ) );

    ASSERT_TRUE( ::NS(KernelConfigKey_are_equal)( key_a, key_b ) );
    ASSERT_TRUE( ::NS(KernelConfigKey_compare)( key_a, key_b ) == 0 );

   ::NS(KernelConfigKey_set_purpose)(
       key_b, ::NS(KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID) );

    ASSERT_TRUE( ::NS(KernelConfigKey_is_valid)( key_b ) );
    ASSERT_TRUE( ::NS(KernelConfigKey_are_not_equal)( key_a, key_b ) );
    ASSERT_TRUE( ::NS(KernelConfigKey_compare)( key_a, key_b ) != 0 );
    ASSERT_TRUE( ::NS(KernelConfigKey_are_equal_except_purpose)(
        key_a, key_b ) );

    ::NS(KernelConfigKey_set_purpose)( key_b,
            ::NS(KernelConfigKey_get_purpose)( key_a ) );

    ::NS(KernelConfigKey_set_variant)( key_b, ::NS(ARCH_VARIANT_DEBUG) );

    ASSERT_TRUE( ::NS(KernelConfigKey_is_valid)( key_b ) );
    ASSERT_TRUE( ::NS(KernelConfigKey_are_not_equal)( key_a, key_b ) );
    ASSERT_TRUE( ::NS(KernelConfigKey_compare)( key_a, key_b ) != 0 );
    ASSERT_TRUE( !::NS(KernelConfigKey_are_equal_except_purpose)(
        key_a, key_b ) );

    ::NS(KernelConfigKey_set_variant)( key_b,
        ::NS(KernelConfigKey_get_variant)( key_a ) );

    ::NS(KernelConfigKey_set_argument_set)(
        key_b, ::NS(KernelConfigKey_get_argument_set)( key_a ) + size_t{ 1 } );

    ASSERT_TRUE( ::NS(KernelConfigKey_is_valid)( key_b ) );
    ASSERT_TRUE( ::NS(KernelConfigKey_are_not_equal)( key_a, key_b ) );
    ASSERT_TRUE( ::NS(KernelConfigKey_compare)( key_a, key_b ) != 0 );
    ASSERT_TRUE( !::NS(KernelConfigKey_are_equal_except_purpose)( key_a, key_b ) );


    ::NS(KernelConfigKey_set_argument_set)( key_b,
        ::NS(KernelConfigKey_get_argument_set)( key_a ) );

    ::NS(KernelConfigKey_set_config_str)( key_b,
        "this is a config_str argument; key_a does not have a config_str" );

    ASSERT_TRUE(  ::NS(KernelConfigKey_is_valid)( key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_has_config_str)( key_b ) );
    ASSERT_TRUE( !::NS(KernelConfigKey_has_config_str)( key_a ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_are_not_equal)( key_a, key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_compare)( key_a, key_b ) != 0 );
    ASSERT_TRUE( !::NS(KernelConfigKey_are_equal_except_purpose)( key_a, key_b ) );

    ::NS(KernelConfigKey_set_config_str)( key_b, nullptr );

    ASSERT_TRUE(  ::NS(KernelConfigKey_is_valid)( key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_are_equal)( key_a, key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_compare)( key_a, key_b ) == 0 );
    ASSERT_TRUE(  ::NS(KernelConfigKey_are_equal_except_purpose)( key_a, key_b ) );

    status = ::NS(KernelConfigKey_reset_to_default_values)( key_b );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( !::NS(KernelConfigKey_is_valid)( key_b ) );
    ASSERT_TRUE( !::NS(KernelConfigKey_has_config_str)( key_b ) );
    ASSERT_TRUE( !::NS(KernelConfigKey_has_config_str)( key_a ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_are_not_equal)( key_a, key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_compare)( key_a, key_b ) != 0 );
    ASSERT_TRUE( !::NS(KernelConfigKey_are_equal_except_purpose)(
        key_a, key_b ) );

    node_id_t* node_id = ::NS(NodeId_new_detailed)(
        arch, platform_id_t{ 1 }, device_id_t{ 2 } );

    SIXTRL_ASSERT( node_id != nullptr );
    SIXTRL_ASSERT( ::NS(NodeId_is_valid)( node_id ) );

    status = ::NS(KernelConfigKey_reset_with_node_id)( key_b, node_id,
        ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER), ::NS(ARCH_VARIANT_NONE),
        ::NS(DEFAULT_KERNEL_ARGUMENT_SET), nullptr );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_is_valid)( key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_has_node_id)( key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_purpose)( key_b ) ==
                  ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_variant)( key_b ) ==
                  ::NS(ARCH_VARIANT_NONE) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_argument_set)( key_b ) ==
                  ::NS(DEFAULT_KERNEL_ARGUMENT_SET) );
    ASSERT_TRUE( !::NS(KernelConfigKey_has_config_str)( key_b ) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_get_arch_id)( key_b ) ==
                  ::NS(KernelConfigKey_get_arch_id)( key_a ) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_get_purpose)( key_b ) ==
                  ::NS(KernelConfigKey_get_purpose)( key_a ) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_get_variant)( key_b ) ==
                  ::NS(KernelConfigKey_get_variant)( key_a ) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_get_argument_set)( key_b ) ==
                  ::NS(KernelConfigKey_get_argument_set)( key_a ) );

    ASSERT_TRUE( !::NS(KernelConfigKey_has_config_str)( key_a ) );
    ASSERT_TRUE( !::NS(KernelConfigKey_has_node_id)( key_a ) );
    ASSERT_TRUE( !::NS(KernelConfigKey_are_equal)( key_a, key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_are_not_equal)( key_a, key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_compare)( key_a, key_b ) != 0 );
    ASSERT_TRUE( !::NS(KernelConfigKey_are_equal_except_purpose)(
                    key_a, key_b ) );

    status = ::NS(KernelConfigKey_reset_detailed)( key_a,
        ::NS(NodeId_get_arch_id)( node_id ),
        ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER), ::NS(ARCH_VARIANT_NONE),
        ::NS(DEFAULT_KERNEL_ARGUMENT_SET), nullptr,
        ::NS(NodeId_get_platform_id)( node_id ),
        ::NS(NodeId_get_device_id)( node_id ) );

    ASSERT_TRUE(  status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_is_valid)( key_a ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_has_node_id)( key_a ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_get_purpose)( key_a ) ==
                  ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_get_variant)( key_a ) ==
                  ::NS(ARCH_VARIANT_NONE) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_get_argument_set)( key_a ) ==
                  ::NS(DEFAULT_KERNEL_ARGUMENT_SET) );

    ASSERT_TRUE( !::NS(KernelConfigKey_has_config_str)( key_a ) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_get_arch_id)( key_b ) ==
                  ::NS(KernelConfigKey_get_arch_id)( key_a ) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_get_purpose)( key_b ) ==
                  ::NS(KernelConfigKey_get_purpose)( key_a ) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_get_variant)( key_b ) ==
                  ::NS(KernelConfigKey_get_variant)( key_a ) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_get_argument_set)( key_b ) ==
                  ::NS(KernelConfigKey_get_argument_set)( key_a ) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_are_equal)( key_a, key_b ) );
    ASSERT_TRUE( !::NS(KernelConfigKey_are_not_equal)( key_a, key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_compare)( key_a, key_b ) == 0 );
    ASSERT_TRUE(  ::NS(KernelConfigKey_are_equal_except_purpose)(
        key_a, key_b ) );

    ::NS(KernelConfigKey_set_purpose)( key_a,
        ::NS(KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_is_valid)( key_a ) );
    ASSERT_TRUE( !::NS(KernelConfigKey_are_equal)( key_a, key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_are_not_equal)( key_a, key_b ) );
    ASSERT_TRUE(  ::NS(KernelConfigKey_compare)( key_a, key_b ) != 0 );
    ASSERT_TRUE(  ::NS(KernelConfigKey_are_equal_except_purpose)(
        key_a, key_b ) );

    /* --------------------------------------------------------------------- */

    ::NS(NodeId_delete)( node_id );
    ::NS(KernelConfigKey_delete)( key_a );
    ::NS(KernelConfigKey_delete)( key_b );
}

/* end: tests/sixtracklib/common/control/test_kernel_config_key_c99.cpp */
