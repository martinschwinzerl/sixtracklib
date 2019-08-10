#include "sixtracklib/common/control/kernel_config_base.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/kernel_config_key.hpp"
#include "sixtracklib/common/control/node_id.hpp"
#include "sixtracklib/testlib.h"

TEST( CXX_CommonControlKernelConfigBaseTests, MinimalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using config_t       = st::KernelConfigBase;
    using key_t          = st::KernelConfigKey;
    using size_t         = st::ctrl_size_t;
    using arch_id_t      = st::arch_id_t;
    using node_id_t      = key_t::node_id_t;
    using platform_id_t  = key_t::platform_id_t;
    using device_id_t    = key_t::device_id_t;
    using status_t       = key_t::status_t;
    using argument_set_t = key_t::argument_set_t;

    /* Verify that a suitable arch is available */
    st::Architectures const& archs = st::Architectures_get_const();
    SIXTRL_ASSERT( archs.numArchitectures() > size_t{ 0 } );

    arch_id_t const arch_id = archs.archIdByNumber( size_t{ 0 } );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_NONE );

    SIXTRL_ASSERT(  archs.hasArchitecture( arch_id ) );
    SIXTRL_ASSERT(  archs.hasArchStr( arch_id ) );

    /* --------------------------------------------------------------------- */

    config_t conf_a( arch_id );

    ASSERT_TRUE( conf_a.archId() == arch_id );
    ASSERT_TRUE( conf_a.numArguments() ==
                 config_t::DEFAULT_NUM_KERNEL_ARGUMENTS );

    ASSERT_TRUE( !conf_a.hasConfigStr() );
    ASSERT_TRUE( !conf_a.hasName() );
    ASSERT_TRUE( !conf_a.isAttachedToAnySets() );
    ASSERT_TRUE(  conf_a.numAttachedSets() == size_t{ 0 } );
    ASSERT_TRUE(  conf_a.maxNumAttachedSets() ==
                  config_t::DEFAULT_MAX_NUM_ATTACHED_KERNEL_SETS );

    ASSERT_TRUE(  conf_a.variant() == config_t::DEFAULT_VARIANT );
    ASSERT_TRUE(  conf_a.argumentSet() == config_t::DEFAULT_ARGUMENT_SET );
    ASSERT_TRUE(  conf_a.purpose() == config_t::DEFAULT_KERNEL_PURPOSE );
    ASSERT_TRUE( !conf_a.performsAutoUpdate() );
    ASSERT_TRUE( !conf_a.variantDebugMode() );
    ASSERT_TRUE(  conf_a.variantReleaseMode() );

    /* --------------------------------------------------------------------- */

    conf_a.setNumArguments( size_t{ 3 } );
    conf_a.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );
    conf_a.setVariant( st::ARCH_VARIANT_DEBUG );
    conf_a.setName( "track_until_kernel" );

    ASSERT_TRUE(  conf_a.hasName() );
    ASSERT_TRUE(  conf_a.name().compare( "track_until_kernel" ) == 0 );
    ASSERT_TRUE(  conf_a.numArguments() == size_t{ 3 } );
    ASSERT_TRUE(  conf_a.hasPredefinedPurpose() );
    ASSERT_TRUE( !conf_a.hasUserdefinedPurpose() );
    ASSERT_TRUE(  conf_a.variantDebugMode() );
    ASSERT_TRUE( !conf_a.variantReleaseMode() );

    ASSERT_TRUE(  conf_a.hasSpecifiedPurpose() );
    ASSERT_TRUE(  conf_a.purpose() ==
                  st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );

    conf_a.setPurpose( st::KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID );
    ASSERT_TRUE(  conf_a.hasSpecifiedPurpose() );
    ASSERT_TRUE( !conf_a.hasPredefinedPurpose() );
    ASSERT_TRUE(  conf_a.hasUserdefinedPurpose() );

    conf_a.setPurpose( st::KERNEL_CONFIG_PURPOSE_UNSPECIFIED );
    ASSERT_TRUE( !conf_a.hasSpecifiedPurpose() );
    ASSERT_TRUE( !conf_a.hasPredefinedPurpose() );
    ASSERT_TRUE( !conf_a.hasUserdefinedPurpose() );

    /* --------------------------------------------------------------------- */

    size_t const requ_str_capacity_a = conf_a.requiredOutStringLength();
    ASSERT_TRUE( requ_str_capacity_a > size_t{ 0 } );

    std::string const out_str_a = conf_a.toString();
    ASSERT_TRUE( !out_str_a.empty() );
    ASSERT_TRUE(  out_str_a.size() < requ_str_capacity_a );

    std::vector< char > out_cstr_a( requ_str_capacity_a, '\0' );

    status_t status = conf_a.toString( out_cstr_a.size(), out_cstr_a.data() );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( std::strlen( out_cstr_a.data() ) == out_str_a.size() );
    ASSERT_TRUE( out_str_a.compare( out_cstr_a.data() ) == 0 );

    /* --------------------------------------------------------------------- */

    std::string const key_b_config_str(
        "key config string, expected to show up in the kernel config as well" );

    node_id_t node( arch_id, platform_id_t{ 3 }, device_id_t{ 14 } );

    key_t key_b( node, st::KERNEL_CONFIG_PURPOSE_TRACK_LINE,
                 st::ARCH_VARIANT_DEBUG, argument_set_t{ 42 },
                 key_b_config_str );

    SIXTRL_ASSERT( key_b.archId() == arch_id );
    SIXTRL_ASSERT( key_b.valid() );
    SIXTRL_ASSERT( key_b.hasNodeId() );
    SIXTRL_ASSERT( key_b.hasConfigStr() );
    SIXTRL_ASSERT( key_b.configStr().compare( key_b_config_str ) == 0 );
    SIXTRL_ASSERT( key_b.purpose() == st::KERNEL_CONFIG_PURPOSE_TRACK_LINE );
    SIXTRL_ASSERT( key_b.variant() == st::ARCH_VARIANT_DEBUG );
    SIXTRL_ASSERT( key_b.argumentSet() == argument_set_t{ 42 } );

    size_t const conf_b_num_args = size_t{ 5 };
    std::string const conf_b_kernel_name( "track_line_kernel" );

    config_t conf_b( key_b, conf_b_num_args, conf_b_kernel_name );

    ASSERT_TRUE(  conf_b.archId()  == key_b.archId() );
    ASSERT_TRUE(  conf_b.purpose() == key_b.purpose() );
    ASSERT_TRUE(  conf_b.variant() == key_b.variant() );
    ASSERT_TRUE(  conf_b.hasConfigStr() );
    ASSERT_TRUE(  conf_b.configStr().compare( key_b_config_str ) == 0 );
    ASSERT_TRUE(  conf_b.argumentSet() == key_b.argumentSet() );
    ASSERT_TRUE(  conf_b.hasArchStr() );
    ASSERT_TRUE(  conf_b.archStr().compare( archs.archStr( arch_id ) ) == 0 );
    ASSERT_TRUE(  conf_b.variantDebugMode() );
    ASSERT_TRUE( !conf_b.variantReleaseMode() );

    /* --------------------------------------------------------------------- */

    size_t const requ_str_capacity_b = conf_b.requiredOutStringLength();
    ASSERT_TRUE( requ_str_capacity_b > size_t{ 0 } );

    std::string const out_str_b = conf_b.toString();
    ASSERT_TRUE( !out_str_b.empty() );
    ASSERT_TRUE(  out_str_b.size() < requ_str_capacity_b );

    std::vector< char > out_cstr_b( requ_str_capacity_b, '\0' );

    status = conf_b.toString( out_cstr_b.size(), out_cstr_b.data() );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( std::strlen( out_cstr_b.data() ) == out_str_b.size() );
    ASSERT_TRUE( out_str_b.compare( out_cstr_b.data() ) == 0 );
}

/* end: tests/sixtracklib/common/control/test_kernel_config_base_cxx.cpp */
