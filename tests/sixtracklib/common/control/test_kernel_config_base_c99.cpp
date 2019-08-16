#include "sixtracklib/common/control/kernel_config_base.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/architecture.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/kernel_config_key.h"
#include "sixtracklib/common/control/node_id.h"
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

TEST( C99_CommonControlKernelConfigBaseTests, MinimalUsage )
{
    namespace st_test = SIXTRL_CXX_NAMESPACE::tests;

    using config_t       = ::NS(KernelConfigBase);
    using key_t          = ::NS(KernelConfigKey);
    using size_t         = ::NS(ctrl_size_t);
    using arch_id_t      = ::NS(arch_id_t);
    using node_id_t      = ::NS(NodeId);
    using platform_id_t  = ::NS(node_platform_id_t);
    using device_id_t    = ::NS(node_device_id_t);
    using argument_set_t = ::NS(kernel_argument_set_t);
    using status_t       = ::NS(arch_status_t);

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

    config_t* conf_a = st_test::KernelConfigBase_new( arch_id );

    ASSERT_TRUE( conf_a != nullptr );
    ASSERT_TRUE( ::NS(KernelConfig_get_arch_id)( conf_a ) == arch_id );
    ASSERT_TRUE( ::NS(KernelConfig_get_num_arguments)( conf_a ) ==
                 size_t{ 0 } );

    ASSERT_TRUE( !::NS(KernelConfig_has_config_str)( conf_a ) );
    ASSERT_TRUE( !::NS(KernelConfig_has_name)( conf_a ) );
    ASSERT_TRUE( !::NS(KernelConfig_is_attached_to_any_sets)( conf_a ) );

    ASSERT_TRUE(  ::NS(KernelConfig_get_num_attached_sets)( conf_a ) ==
                  size_t{ 0 } );

    ASSERT_TRUE(  ::NS(KernelConfig_get_max_num_attached_sets)( conf_a ) ==
                  size_t{ 1 } );

    ASSERT_TRUE(  ::NS(KernelConfig_get_variant)( conf_a ) ==
                  ::NS(ARCH_VARIANT_NONE) );

    ASSERT_TRUE(  ::NS(KernelConfig_get_argument_set)( conf_a ) ==
                   ::NS(DEFAULT_KERNEL_ARGUMENT_SET) );

    ASSERT_TRUE(  ::NS(KernelConfig_get_purpose)( conf_a ) ==
                  ::NS(KERNEL_CONFIG_PURPOSE_UNSPECIFIED) );

    ASSERT_TRUE( !::NS(KernelConfig_performs_auto_update)( conf_a ) );

    /* --------------------------------------------------------------------- */

    status_t status = ::NS(KernelConfig_set_num_arguments)(
        conf_a, size_t{ 3 } );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    ::NS(KernelConfig_set_purpose)( conf_a,
            ::NS(KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN) );

    ::NS(KernelConfig_set_name_str)( conf_a, "track_until_kernel" );

    ASSERT_TRUE(  ::NS(KernelConfig_has_name)( conf_a ) );
    ASSERT_TRUE(  std::strcmp( ::NS(KernelConfig_get_name_str)( conf_a ),
                               "track_until_kernel" ) == 0 );

    ASSERT_TRUE(  ::NS(KernelConfig_get_num_arguments)( conf_a ) ==
                  size_t{ 3 } );

    ASSERT_TRUE(  ::NS(KernelConfig_has_predefined_purpose)( conf_a ) );
    ASSERT_TRUE( !::NS(KernelConfig_has_userdefined_purpose)( conf_a ) );

    ASSERT_TRUE(  ::NS(KernelConfig_has_specified_purpose)( conf_a ) );
    ASSERT_TRUE(  ::NS(KernelConfig_get_purpose)( conf_a ) ==
                  ::NS(KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN) );

    ::NS(KernelConfig_set_purpose)( conf_a,
            ::NS(KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID) );

    ASSERT_TRUE(  ::NS(KernelConfig_has_specified_purpose)( conf_a ) );
    ASSERT_TRUE( !::NS(KernelConfig_has_predefined_purpose)( conf_a ) );
    ASSERT_TRUE(  ::NS(KernelConfig_has_userdefined_purpose)( conf_a ) );

    ::NS(KernelConfig_set_purpose)( conf_a,
            ::NS(KERNEL_CONFIG_PURPOSE_UNSPECIFIED) );

    ASSERT_TRUE( !::NS(KernelConfig_has_specified_purpose)( conf_a ) );
    ASSERT_TRUE( !::NS(KernelConfig_has_predefined_purpose)( conf_a ) );
    ASSERT_TRUE( !::NS(KernelConfig_has_userdefined_purpose)( conf_a ) );

    /* --------------------------------------------------------------------- */

    size_t const requ_str_capacity_a =
        ::NS(KernelConfig_required_string_representation_capacity)( conf_a );

    ASSERT_TRUE( requ_str_capacity_a > size_t{ 0 } );
    std::vector< char > out_cstr_a( requ_str_capacity_a, '\0' );

    status = ::NS(KernelConfig_to_string)(
        conf_a, out_cstr_a.size(), out_cstr_a.data() );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( std::strlen( out_cstr_a.data() ) > size_t{ 0 } );
    ASSERT_TRUE( std::strlen( out_cstr_a.data() ) < requ_str_capacity_a );

    /* --------------------------------------------------------------------- */

    std::string const key_b_config_str(
        "key config string, expected to show up in the kernel config as well" );

    node_id_t* node = ::NS(NodeId_new_detailed)(
        arch_id, platform_id_t{ 3 }, device_id_t{ 14 } );

    SIXTRL_ASSERT( node != nullptr );

    key_t* key_b  = ::NS(KernelConfigKey_new_from_node_id)(
        node, ::NS(KERNEL_CONFIG_PURPOSE_TRACK_LINE), ::NS(ARCH_VARIANT_DEBUG),
            argument_set_t{ 42 }, key_b_config_str.c_str() );

    SIXTRL_ASSERT( key_b != nullptr );
    SIXTRL_ASSERT( ::NS(KernelConfigKey_get_arch_id)( key_b ) == arch_id );
    SIXTRL_ASSERT( ::NS(KernelConfigKey_is_valid)( key_b ) );
    SIXTRL_ASSERT( ::NS(KernelConfigKey_has_node_id)( key_b ) );
    SIXTRL_ASSERT( ::NS(KernelConfigKey_has_config_str)( key_b ) );
    SIXTRL_ASSERT( ::NS(KernelConfigKey_get_argument_set)( key_b ) ==
                    argument_set_t{ 42 } );

    SIXTRL_ASSERT( std::strcmp( ::NS(KernelConfigKey_get_config_str)( key_b ),
                                key_b_config_str.c_str() ) == 0 );

    SIXTRL_ASSERT( ::NS(KernelConfigKey_get_purpose)( key_b ) ==
                   ::NS(KERNEL_CONFIG_PURPOSE_TRACK_LINE) );

    SIXTRL_ASSERT( ::NS(KernelConfigKey_get_variant)( key_b ) ==
                   ::NS(ARCH_VARIANT_DEBUG) );


    size_t const conf_b_num_args = size_t{ 5 };
    std::string const conf_b_kernel_name( "track_line_kernel" );

    config_t* conf_b = st_test::KernelConfigBase_new(
        *key_b, conf_b_num_args, conf_b_kernel_name );

    ASSERT_TRUE( ::NS(KernelConfig_get_arch_id)( conf_b )  ==
                 ::NS(KernelConfigKey_get_arch_id)( key_b ) );

    ASSERT_TRUE( ::NS(KernelConfig_get_purpose)( conf_b ) ==
                 ::NS(KernelConfigKey_get_purpose)( key_b ) );

    ASSERT_TRUE( ::NS(KernelConfig_get_variant)( conf_b ) ==
                 ::NS(KernelConfigKey_get_variant)( key_b ) );

    ASSERT_TRUE( ::NS(KernelConfig_has_config_str)( conf_b ) );
    ASSERT_TRUE( std::strcmp( ::NS(KernelConfig_get_config_str)( conf_b ),
                              key_b_config_str.c_str() ) == 0 );

    ASSERT_TRUE( ::NS(KernelConfig_get_argument_set)( conf_b ) ==
                 ::NS(KernelConfigKey_get_argument_set)( key_b ) );

    ASSERT_TRUE( ::NS(KernelConfig_has_arch_str)( conf_b ) );
    ASSERT_TRUE( std::strcmp( ::NS(KernelConfig_get_arch_str)( conf_b ),
                 ::NS(Architectures_get_arch_str)( ptr_archs, arch_id ) ) == 0 );

    /* --------------------------------------------------------------------- */

    size_t const requ_str_capacity_b =
        ::NS(KernelConfig_required_string_representation_capacity)( conf_b );

    ASSERT_TRUE( requ_str_capacity_b > size_t{ 0 } );
    std::vector< char > out_cstr_b( requ_str_capacity_b, '\0' );

    status = ::NS(KernelConfig_to_string)(
        conf_b, out_cstr_b.size(), out_cstr_b.data() );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( std::strlen( out_cstr_b.data() ) > size_t{ 0 } );
    ASSERT_TRUE( std::strlen( out_cstr_b.data() ) < requ_str_capacity_b );

    /* --------------------------------------------------------------------- */

    ::NS(KernelConfig_delete)( conf_a );
    ::NS(KernelConfig_delete)( conf_b );
    ::NS(KernelConfigKey_delete)( key_b );
    ::NS(NodeId_delete)( node );
}

/* end: tests/sixtracklib/common/control/test_kernel_config_base_c99.cpp */
