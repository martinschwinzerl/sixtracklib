#include "sixtracklib/common/control/kernel_config_key.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_id.hpp"
#include "sixtracklib/testlib.h"

TEST( CXX_CommonControlKernelConfigKeyTests, MinimalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using key_t         = st::KernelConfigKey;
    using size_t        = st::ctrl_size_t;
    using arch_id_t     = st::arch_id_t;
    using node_id_t     = key_t::node_id_t;
    using platform_id_t = key_t::platform_id_t;
    using device_id_t   = key_t::device_id_t;
    using status_t      = key_t::status_t;

    /* Verify that a suitable arch is available */
    st::Architectures const& archs = st::Architectures_get_const();
    SIXTRL_ASSERT( archs.numArchitectures() > size_t{ 0 } );

    arch_id_t const arch_id = archs.archIdByNumber( size_t{ 0 } );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_NONE );

    SIXTRL_ASSERT(  archs.hasArchitecture( arch_id ) );
    SIXTRL_ASSERT(  archs.hasArchStr( arch_id ) );

    /* --------------------------------------------------------------------- */

    key_t key_a;

    ASSERT_TRUE(  key_a.archId()  == st::ARCHITECTURE_ILLEGAL );
    ASSERT_TRUE( !key_a.hasNodeId() );
    ASSERT_TRUE(  key_a.purpose() == st::KERNEL_CONFIG_PURPOSE_UNSPECIFIED );
    ASSERT_TRUE(  key_a.variant() == st::ARCH_VARIANT_NONE );
    ASSERT_TRUE(  key_a.argumentSet() == st::DEFAULT_KERNEL_ARGUMENT_SET );
    ASSERT_TRUE( !key_a.hasConfigStr() );
    ASSERT_TRUE( !key_a.valid() );

    key_a.reset( arch_id, st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );

    ASSERT_TRUE(  key_a.archId()  == arch_id );
    ASSERT_TRUE( !key_a.hasNodeId() );
    ASSERT_TRUE(  key_a.purpose() == st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );
    ASSERT_TRUE(  key_a.variant() == st::ARCH_VARIANT_NONE );
    ASSERT_TRUE(  key_a.argumentSet() == st::DEFAULT_KERNEL_ARGUMENT_SET );
    ASSERT_TRUE( !key_a.hasConfigStr() );
    ASSERT_TRUE(  key_a.valid() );

    key_t key_b( key_a );

    ASSERT_TRUE(  key_b.archId()  == arch_id );
    ASSERT_TRUE( !key_b.hasNodeId() );
    ASSERT_TRUE(  key_b.purpose() == st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );
    ASSERT_TRUE(  key_b.variant() == st::ARCH_VARIANT_NONE );
    ASSERT_TRUE(  key_b.argumentSet() == st::DEFAULT_KERNEL_ARGUMENT_SET );
    ASSERT_TRUE( !key_b.hasConfigStr() );
    ASSERT_TRUE(  key_b.valid() );

    ASSERT_TRUE( key_a == key_b );
    ASSERT_TRUE( key_a.compare( key_b ) == 0 );

    key_b.setPurpose( st::KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID );

    ASSERT_TRUE( key_b.valid() );
    ASSERT_TRUE( key_a != key_b );
    ASSERT_TRUE( key_a.compare( key_b ) != 0 );
    ASSERT_TRUE( key_a.isEqualExceptPurpose( key_b ) );

    key_b.setPurpose( key_a.purpose() );
    key_b.setVariant( st::ARCH_VARIANT_DEBUG );

    ASSERT_TRUE( key_b.valid() );
    ASSERT_TRUE( key_a != key_b );
    ASSERT_TRUE( key_a.compare( key_b ) != 0 );
    ASSERT_TRUE( !key_a.isEqualExceptPurpose( key_b ) );

    key_b.setVariant( key_a.variant() );
    key_b.setArgumentSet( key_a.argumentSet() + size_t{ 1 } );

    ASSERT_TRUE( key_b.valid() );
    ASSERT_TRUE( key_a != key_b );
    ASSERT_TRUE( key_a.compare( key_b ) != 0 );
    ASSERT_TRUE( !key_a.isEqualExceptPurpose( key_b ) );


    key_b.setArgumentSet( key_a.argumentSet() );
    key_b.setConfigStr( "this is a config_str argument; "
                        "key_a does not have a config_str" );

    ASSERT_TRUE(  key_b.valid() );
    ASSERT_TRUE(  key_b.hasConfigStr() );
    ASSERT_TRUE( !key_a.hasConfigStr() );
    ASSERT_TRUE(  key_a != key_b );
    ASSERT_TRUE(  key_a.compare( key_b ) != 0 );
    ASSERT_TRUE( !key_a.isEqualExceptPurpose( key_b ) );

    key_b.setConfigStr( nullptr );

    ASSERT_TRUE(  key_b.valid() );
    ASSERT_TRUE(  key_a == key_b );
    ASSERT_TRUE(  key_a.compare( key_b ) == 0 );
    ASSERT_TRUE(  key_a.isEqualExceptPurpose( key_b ) );

    status_t status = key_b.reset();

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( !key_b.valid() );
    ASSERT_TRUE( !key_b.hasConfigStr() );
    ASSERT_TRUE( !key_a.hasConfigStr() );
    ASSERT_TRUE(  key_a != key_b );
    ASSERT_TRUE(  key_a.compare( key_b ) != 0 );
    ASSERT_TRUE( !key_a.isEqualExceptPurpose( key_b ) );

    node_id_t node_id( arch_id, platform_id_t{ 1 }, device_id_t{ 2 } );
    SIXTRL_ASSERT( node_id.valid() );

    status = key_b.reset( node_id, st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  key_b.valid() );
    ASSERT_TRUE(  key_b.hasNodeId() );
    ASSERT_TRUE(  key_b.purpose() == st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );
    ASSERT_TRUE(  key_b.variant() == st::ARCH_VARIANT_NONE );
    ASSERT_TRUE(  key_b.argumentSet() == st::DEFAULT_KERNEL_ARGUMENT_SET );
    ASSERT_TRUE( !key_b.hasConfigStr() );
    ASSERT_TRUE(  key_b.archId()      == key_a.archId() );
    ASSERT_TRUE(  key_b.purpose()     == key_a.purpose() );
    ASSERT_TRUE(  key_b.variant()     == key_a.variant() );
    ASSERT_TRUE(  key_b.argumentSet() == key_a.argumentSet() );
    ASSERT_TRUE( !key_a.hasConfigStr() );
    ASSERT_TRUE( !key_a.hasNodeId() );
    ASSERT_TRUE(  key_a != key_b );
    ASSERT_TRUE(  key_a.compare( key_b ) != 0 );
    ASSERT_TRUE( !key_a.isEqualExceptPurpose( key_b ) );

    status = key_a.reset( node_id.getCApiPtr(),
                          st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );

    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  key_a.valid() );
    ASSERT_TRUE(  key_a.hasNodeId() );
    ASSERT_TRUE(  key_a.purpose() == st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );
    ASSERT_TRUE(  key_a.variant() == st::ARCH_VARIANT_NONE );
    ASSERT_TRUE(  key_a.argumentSet() == st::DEFAULT_KERNEL_ARGUMENT_SET );
    ASSERT_TRUE( !key_a.hasConfigStr() );
    ASSERT_TRUE(  key_b.archId()      == key_a.archId() );
    ASSERT_TRUE(  key_b.purpose()     == key_a.purpose() );
    ASSERT_TRUE(  key_b.variant()     == key_a.variant() );
    ASSERT_TRUE(  key_b.argumentSet() == key_a.argumentSet() );

    ASSERT_TRUE(  key_a == key_b );
    ASSERT_TRUE(  key_a.compare( key_b ) == 0 );
    ASSERT_TRUE(  key_a.isEqualExceptPurpose( key_b ) );

    key_a.setPurpose( st::KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID );

    ASSERT_TRUE(  key_a.valid() );
    ASSERT_TRUE(  key_a != key_b );
    ASSERT_TRUE(  key_a.compare( key_b ) != 0 );
    ASSERT_TRUE(  key_a.isEqualExceptPurpose( key_b ) );
}

TEST( CXX_CommonControlKernelConfigKeyTests, OrderingRelations )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using key_t          = st::KernelConfigKey;
    using size_t         = st::ctrl_size_t;
    using arch_id_t      = st::arch_id_t;
    using node_id_t      = key_t::node_id_t;
    using platform_id_t  = key_t::platform_id_t;
    using device_id_t    = key_t::device_id_t;
    using argument_set_t = key_t::argument_set_t;

    /* Verify that a suitable arch is available */
    st::Architectures const& archs = st::Architectures_get_const();
    SIXTRL_ASSERT( archs.numArchitectures() > size_t{ 0 } );

    arch_id_t const arch_id = archs.archIdByNumber( size_t{ 0 } );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_NONE );

    SIXTRL_ASSERT(  archs.hasArchitecture( arch_id ) );
    SIXTRL_ASSERT(  archs.hasArchStr( arch_id ) );

    key_t key_a( arch_id, st::KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID,
                 st::ARCH_VARIANT_NONE, argument_set_t{ 0 } );

    key_t key_b( arch_id, st::KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID,
                 st::ARCH_VARIANT_NONE, argument_set_t{ 1 } );

    ASSERT_TRUE( key_a < key_b );

    node_id_t node_cd( arch_id, platform_id_t{ 1 }, device_id_t{ 0 } );

    key_t key_c( node_cd, st::KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID,
                 st::ARCH_VARIANT_NONE, argument_set_t{ 1 }, "c" );

    key_t key_d( node_cd, st::KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID,
                 st::ARCH_VARIANT_NONE, argument_set_t{ 0 }, "d" );

    ASSERT_TRUE( key_c < key_d );

    key_d.setConfigStr( nullptr );

    ASSERT_TRUE( key_d < key_c );

}


/* end: tests/sixtracklib/common/control/test_kernel_config_key_cxx.cpp */
