#include "sixtracklib/common/control/node_info.hpp"

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
#include "sixtracklib/testlib.h"

TEST( CXX_CommonControlNodeInfoBaseTests, NodeInfoCreationNoNodeStore )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using node_id_t             = st::NodeId;
    using node_info_t           = st::NodeInfoBase;
    using platform_id_t         = node_info_t::platform_id_t;
    using device_id_t           = node_info_t::device_id_t;
    using size_t                = node_info_t::size_type;
    using arch_id_t             = node_info_t::arch_id_t;
    using status_t              = node_info_t::status_t;

    /* Verify that a suitable arch is available */
    st::Architectures const& archs = st::Architectures_get_const();
    SIXTRL_ASSERT( archs.numArchitectures() > size_t{ 0 } );

    arch_id_t const arch_id = archs.archIdByNumber( size_t{ 0 } );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_NONE );

    SIXTRL_ASSERT(  archs.hasArchitecture( arch_id ) );
    SIXTRL_ASSERT(  archs.isAvailable( arch_id ) );
    SIXTRL_ASSERT( !archs.isShutdown( arch_id ) );

    node_info_t node_info_a( arch_id );

    ASSERT_TRUE( !node_info_a.hasNodeStore() );
    ASSERT_TRUE(  node_info_a.ptrNodeStore() == nullptr );

    ASSERT_TRUE(  node_info_a.archId() == arch_id );
    ASSERT_TRUE(  node_info_a.hasArchStr() );
    ASSERT_TRUE(  node_info_a.archStr().compare(
        archs.archStr( arch_id ) ) == 0 );

    ASSERT_TRUE( !node_info_a.nodeId().valid() );
    ASSERT_TRUE(  node_info_a.platformId() == st::NODE_ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE(  node_info_a.deviceId() == st::NODE_ILLEGAL_DEVICE_ID );

    ASSERT_TRUE( !node_info_a.hasDeviceName() );
    ASSERT_TRUE( !node_info_a.hasPlatformName() );
    ASSERT_TRUE( !node_info_a.hasDescription() );
    ASSERT_TRUE( !node_info_a.hasUniqueIdStr() );

    status_t status = node_info_a.setPlatformId( platform_id_t{ 3 } );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    status = node_info_a.setDeviceId( device_id_t{ 14 } );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE( node_info_a.nodeId().valid() );
    ASSERT_TRUE( node_info_a.platformId() == platform_id_t{ 3 } );
    ASSERT_TRUE( node_info_a.deviceId() == device_id_t{ 14 } );

    node_info_a.setPlatformName( "platform_a" );
    ASSERT_TRUE( node_info_a.hasPlatformName() );
    ASSERT_TRUE( node_info_a.platformName().compare( "platform_a" ) == 0 );

    node_info_a.setDeviceName( "device_a" );
    ASSERT_TRUE( node_info_a.hasDeviceName() );
    ASSERT_TRUE( node_info_a.deviceName().compare( "device_a" ) == 0 );

    node_info_a.setDescription( "description_a" );
    ASSERT_TRUE( node_info_a.hasDescription() );
    ASSERT_TRUE( node_info_a.description().compare( "description_a" ) == 0 );

    node_id_t temp_node_id( arch_id );
    temp_node_id.setPlatformId( platform_id_t{ 2 } );
    temp_node_id.setDeviceId( device_id_t{ 72 } );

    status = node_info_a.nodeId().fromString(
        temp_node_id.toString( st::NODE_ID_STR_FORMAT_ARCHSTR ) );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( node_info_a.nodeId().valid() );
    ASSERT_TRUE( node_info_a.nodeId() == temp_node_id );

    temp_node_id.setPlatformId( platform_id_t{ 3 } );
    temp_node_id.setDeviceId( device_id_t{ 14 } );

    status = node_info_a.nodeId().fromString(
        temp_node_id.toString( st::NODE_ID_STR_FORMAT_NOARCH ) );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( node_info_a.archId() == arch_id );
    ASSERT_TRUE( node_info_a.nodeId() == temp_node_id );

    size_t const node_info_a_str_capacity =
        node_info_a.requiredOutStringLength();

    ASSERT_TRUE( node_info_a_str_capacity > size_t{ 0 } );

    std::vector< char > node_info_a_cstr( node_info_a_str_capacity, '\0' );
    std::string const node_info_a_str = node_info_a.toString();

    ASSERT_TRUE( node_info_a_str.size() <= node_info_a_str_capacity );
    ASSERT_TRUE( node_info_a_str.size() > size_t{ 0 } );

    size_t const too_short = ( node_info_a_str_capacity > size_t{ 2 } )
        ? ( node_info_a_str_capacity >> size_t{ 1 } ) + size_t{ 1 }
        : size_t{ 1 };

    status = node_info_a.toString( too_short, node_info_a_cstr.data() );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );

    status = node_info_a.toString(
        node_info_a_cstr.size(), node_info_a_cstr.data() );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( std::strlen( node_info_a_cstr.data() ) > size_t{ 0 } );
    ASSERT_TRUE( std::strlen( node_info_a_cstr.data() ) ==
                 node_info_a_str.size() );

    ASSERT_TRUE( node_info_a_str.compare( node_info_a_cstr.data() ) == 0 );
}

/* end: tests/sixtracklib/common/control/test_node_info_base_cxx.cpp */
