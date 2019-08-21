#include "sixtracklib/common/control/node_store.hpp"

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
#include "sixtracklib/common/control/node_info.hpp"
#include "sixtracklib/testlib.h"

TEST( CXX_CommonControlNodeStoreTests, NodeStoreCreateAddNodeInfoDestroy )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using store_t       = st::NodeStore;
    using node_info_t   = st::NodeInfoBase;
    using platform_id_t = st::node_platform_id_t;
    using device_id_t   = st::node_device_id_t;
    using size_t        = store_t::size_type;
    using arch_id_t     = store_t::arch_id_t;
    using node_index_t  = store_t::node_index_t;
    using status_t      = node_info_t::status_t;

    /* Verify that a suitable arch is available */
    st::Architectures const& archs = st::Architectures_get_const();
    SIXTRL_ASSERT( archs.numArchitectures() > size_t{ 1 } );

    arch_id_t const arch_id = archs.archIdByNumber( size_t{ 0 } );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_NONE );

    SIXTRL_ASSERT(  archs.hasArchitecture( arch_id ) );
    SIXTRL_ASSERT(  archs.isAvailable( arch_id ) );
    SIXTRL_ASSERT( !archs.isShutdown( arch_id ) );

    /* Create an empty store */

    store_t store;

    ASSERT_TRUE( store.numArchitectures() == size_t{ 0 } );
    ASSERT_TRUE( !store.hasArchitecture( arch_id ) );
    ASSERT_TRUE( store.numPlatforms( arch_id ) == size_t{ 0 } );
    ASSERT_TRUE( !store.hasPlatform( arch_id, platform_id_t{ 0 } ) );
    ASSERT_TRUE( store.totalNumNodes() == size_t{ 0 } );
    ASSERT_TRUE( store.numNodes( arch_id ) == size_t{ 0 } );
    ASSERT_TRUE( store.numNodeSets() == size_t{ 0 } );

    /* Create first node with non-set platform_id and device_id: */

    std::unique_ptr< node_info_t > ptr_node( new node_info_t( arch_id ) );
    node_info_t const* ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_cmp_node != nullptr );
    SIXTRL_ASSERT( ptr_node->archId() == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId() == store_t::ILLEGAL_PLATFORM_ID );
    SIXTRL_ASSERT( ptr_node->deviceId() == store_t::ILLEGAL_DEVICE_ID );

    ptr_node->setPlatformName( "platform0" );
    ptr_node->setDeviceName( "device00" );
    ptr_node->setDescription( "descr 00" );

    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform0" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device00" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 00" ) == 0 );

    /* add first node info to the store: */

    node_index_t const node_100_idx = store.addNode( std::move( ptr_node ) );

    ASSERT_TRUE( node_100_idx != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( ptr_node.get() == nullptr );
    ASSERT_TRUE( store.hasArchitecture( arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx ) == ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->ptrNodeStore() ==
                 &store );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->nodeIndex() ==
                 node_100_idx );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->platformId() !=
                 store_t::ILLEGAL_PLATFORM_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->deviceId() !=
                 store_t::ILLEGAL_DEVICE_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->platformId() ==
                 platform_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->deviceId() ==
                 device_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->hasPlatformName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->platformName().compare(
                 "platform0" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->hasDeviceName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->deviceName().compare(
                 "device00" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->hasDescription() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->description().compare(
                 "descr 00" ) == 0 );

    ASSERT_TRUE( store.hasPlatform( arch_id, platform_id_t{ 0 } ) );
    ASSERT_TRUE( store.totalNumNodes() == size_t{ 1 } );
    ASSERT_TRUE( store.numNodes( arch_id ) == size_t{ 1 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 0 } ) == size_t{ 1 } );

    /* create a second node_info to the exisiting platform: */

    ptr_node.reset( new node_info_t( arch_id, "platform0", "device01",
         "descr 01", platform_id_t{ 0 }, store_t::ILLEGAL_DEVICE_ID ) );

    SIXTRL_ASSERT( ptr_node.get() != nullptr );
    ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_node->archId() == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId() == platform_id_t{ 0 } );
    SIXTRL_ASSERT( ptr_node->deviceId() == store_t::ILLEGAL_DEVICE_ID );
    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform0" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device01" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 01" ) == 0 );

    /* add second node to the store */

    node_index_t const node_101_idx = store.addNode( std::move( ptr_node ) );

    ASSERT_TRUE( node_101_idx != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( node_100_idx != node_101_idx );
    ASSERT_TRUE( ptr_node.get() == nullptr );
    ASSERT_TRUE( store.hasArchitecture( arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx ) == ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->ptrNodeStore() ==
                 &store );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->nodeIndex() ==
                 node_101_idx );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->platformId() !=
                 store_t::ILLEGAL_PLATFORM_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->deviceId() !=
                 store_t::ILLEGAL_DEVICE_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->platformId() ==
                 platform_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->deviceId() ==
                 device_id_t{ 1 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->hasPlatformName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->platformName().compare(
                 "platform0" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->hasDeviceName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->deviceName().compare(
                 "device01" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->hasDescription() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->description().compare(
                 "descr 01" ) == 0 );

    ASSERT_TRUE( store.hasPlatform( arch_id, platform_id_t{ 0 } ) );
    ASSERT_TRUE( store.totalNumNodes() == size_t{ 2 } );
    ASSERT_TRUE( store.numNodes( arch_id ) == size_t{ 2 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );

    /* create a third node_info,expected to get next free platform_id number */

    ptr_node.reset( new node_info_t( arch_id, "platform1", "device10",
         "descr 10", store_t::ILLEGAL_PLATFORM_ID,
            store_t::ILLEGAL_DEVICE_ID ) );

    SIXTRL_ASSERT( ptr_node.get() != nullptr );
    ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_node->archId() == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId() == store_t::ILLEGAL_PLATFORM_ID );
    SIXTRL_ASSERT( ptr_node->deviceId() == store_t::ILLEGAL_DEVICE_ID );
    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform1" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device10" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 10" ) == 0 );

    /* add third node to the store */

    node_index_t const node_110_idx = store.addNode( std::move( ptr_node ) );

    ASSERT_TRUE( node_110_idx != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( node_100_idx != node_110_idx );
    ASSERT_TRUE( node_101_idx != node_110_idx );
    ASSERT_TRUE( ptr_node.get() == nullptr );
    ASSERT_TRUE( store.hasArchitecture( arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx ) == ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->ptrNodeStore() ==
                 &store );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->nodeIndex() ==
                 node_110_idx );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->platformId() !=
                 store_t::ILLEGAL_PLATFORM_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->deviceId() !=
                 store_t::ILLEGAL_DEVICE_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->platformId() ==
                 platform_id_t{ 1 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->deviceId() ==
                 device_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->hasPlatformName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->platformName().compare(
                 "platform1" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->hasDeviceName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->deviceName().compare(
                 "device10" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->hasDescription() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->description().compare(
                 "descr 10" ) == 0 );

    ASSERT_TRUE( store.hasPlatform( arch_id, platform_id_t{ 1 } ) );
    ASSERT_TRUE( store.totalNumNodes() == size_t{ 3 } );
    ASSERT_TRUE( store.numNodes( arch_id ) == size_t{ 3 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 1 } ) == size_t{ 1 } );

    /* try to add the same node again, expect to get the same node_index */

    ptr_node.reset( new node_info_t( arch_id, "platform1", "device10",
         "descr 10", platform_id_t{ 1 }, device_id_t{ 0 }, &store ) );

    SIXTRL_ASSERT( ptr_node.get() != nullptr );
    ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_node->archId() == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId() == platform_id_t{ 1 } );
    SIXTRL_ASSERT( ptr_node->deviceId() == device_id_t{ 0 } );
    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform1" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device10" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 10" ) == 0 );

    node_index_t const node_110_idx_duplicate =
        store.addNode( std::move( ptr_node ) );

    ASSERT_TRUE( node_110_idx_duplicate != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( node_110_idx_duplicate == node_110_idx );
    ASSERT_TRUE( store.hasArchitecture( arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx ) != ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->ptrNodeStore() ==
                 &store );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_110_idx )->nodeIndex() ==
                 node_110_idx );

    ASSERT_TRUE( store.hasPlatform( arch_id, platform_id_t{ 1 } ) );
    ASSERT_TRUE( store.totalNumNodes() == size_t{ 3 } );
    ASSERT_TRUE( store.numNodes( arch_id ) == size_t{ 3 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 1 } ) == size_t{ 1 } );

    /* add fourth node, leave a gap in the platform_id numbers */

    ptr_node.reset( new node_info_t( arch_id, "platform5", "device50",
         "descr 50", platform_id_t{ 5 }, store_t::ILLEGAL_DEVICE_ID ) );

    SIXTRL_ASSERT( ptr_node.get() != nullptr );
    ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_node->archId() == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId() == platform_id_t{ 5 } );
    SIXTRL_ASSERT( ptr_node->deviceId() == store_t::ILLEGAL_DEVICE_ID );
    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform5" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device50" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 50" ) == 0 );

    /* add fourth node to the store */

    node_index_t const node_500_idx = store.addNode( std::move( ptr_node ) );

    ASSERT_TRUE( node_500_idx != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( node_100_idx != node_500_idx );
    ASSERT_TRUE( node_101_idx != node_500_idx );
    ASSERT_TRUE( node_110_idx != node_500_idx );
    ASSERT_TRUE( ptr_node.get() == nullptr );
    ASSERT_TRUE( store.hasArchitecture( arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx ) == ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx )->ptrNodeStore() ==
                 &store );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx )->nodeIndex() ==
                 node_500_idx );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx )->platformId() !=
                 store_t::ILLEGAL_PLATFORM_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx )->deviceId() !=
                 store_t::ILLEGAL_DEVICE_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx )->platformId() ==
                 platform_id_t{ 5 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx )->deviceId() ==
                 device_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx )->hasPlatformName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx )->platformName().compare(
                 "platform5" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx )->hasDeviceName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx )->deviceName().compare(
                 "device50" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx )->hasDescription() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx )->description().compare(
                 "descr 50" ) == 0 );

    ASSERT_TRUE( store.hasPlatform( arch_id, platform_id_t{ 5 } ) );
    ASSERT_TRUE( store.totalNumNodes() == size_t{ 4 } );
    ASSERT_TRUE( store.numNodes( arch_id ) == size_t{ 4 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 1 } ) == size_t{ 1 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 5 } ) == size_t{ 1 } );

    /* add fifth node, expect next available platform_id  */

    ptr_node.reset( new node_info_t( arch_id, "platform6", "device60",
         "descr 60", store_t::ILLEGAL_PLATFORM_ID,
            store_t::ILLEGAL_DEVICE_ID ) );

    SIXTRL_ASSERT( ptr_node.get() != nullptr );
    ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_node->archId() == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId() == store_t::ILLEGAL_PLATFORM_ID );
    SIXTRL_ASSERT( ptr_node->deviceId() == store_t::ILLEGAL_DEVICE_ID );
    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform6" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device60" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 60" ) == 0 );

    /* add fifth node to the store */

    node_index_t const node_600_idx = store.addNode( std::move( ptr_node ) );

    ASSERT_TRUE( node_600_idx != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( node_100_idx != node_600_idx );
    ASSERT_TRUE( node_101_idx != node_600_idx );
    ASSERT_TRUE( node_110_idx != node_600_idx );
    ASSERT_TRUE( node_500_idx != node_600_idx );
    ASSERT_TRUE( ptr_node.get() == nullptr );
    ASSERT_TRUE( store.hasArchitecture( arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx ) == ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx )->ptrNodeStore() ==
                 &store );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx )->nodeIndex() ==
                 node_600_idx );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx )->platformId() !=
                 store_t::ILLEGAL_PLATFORM_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx )->deviceId() !=
                 store_t::ILLEGAL_DEVICE_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx )->platformId() ==
                 platform_id_t{ 6 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx )->deviceId() ==
                 device_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx )->hasPlatformName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx )->platformName().compare(
                 "platform6" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx )->hasDeviceName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx )->deviceName().compare(
                 "device60" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx )->hasDescription() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_600_idx )->description().compare(
                 "descr 60" ) == 0 );

    ASSERT_TRUE( store.hasPlatform( arch_id, platform_id_t{ 6 } ) );
    ASSERT_TRUE( store.totalNumNodes() == size_t{ 5 } );
    ASSERT_TRUE( store.numNodes( arch_id ) == size_t{ 5 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 1 } ) == size_t{ 1 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 5 } ) == size_t{ 1 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 6 } ) == size_t{ 1 } );

    /* Remove node platform_id == 5, device_id == 0 */

    status_t status = store.removeNode( node_500_idx );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_500_idx ) == nullptr );

    ASSERT_TRUE(  store.hasPlatform( arch_id, platform_id_t{ 5 } ) );
    ASSERT_TRUE(  store.totalNumNodes() == size_t{ 4 } );
    ASSERT_TRUE(  store.numNodes( arch_id ) == size_t{ 4 } );
    ASSERT_TRUE(  store.numNodes( arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );
    ASSERT_TRUE(  store.numNodes( arch_id, platform_id_t{ 1 } ) == size_t{ 1 } );
    ASSERT_TRUE(  store.numNodes( arch_id, platform_id_t{ 5 } ) == size_t{ 0 } );
    ASSERT_TRUE(  store.numNodes( arch_id, platform_id_t{ 6 } ) == size_t{ 1 } );
}


TEST( CXX_CommonControlNodeStoreTests,
      NodeStoreCreateAddNodeInfoDestroyExtLock )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using store_t       = st::NodeStore;
    using node_info_t   = st::NodeInfoBase;
    using platform_id_t = st::node_platform_id_t;
    using device_id_t   = st::node_device_id_t;
    using size_t        = store_t::size_type;
    using arch_id_t     = store_t::arch_id_t;
    using node_index_t  = store_t::node_index_t;
    using status_t      = node_info_t::status_t;

    /* Verify that a suitable arch is available */
    st::Architectures const& archs = st::Architectures_get_const();
    SIXTRL_ASSERT( archs.numArchitectures() > size_t{ 1 } );

    arch_id_t const arch_id = archs.archIdByNumber( size_t{ 0 } );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch_id != st::ARCHITECTURE_NONE );

    SIXTRL_ASSERT(  archs.hasArchitecture( arch_id ) );
    SIXTRL_ASSERT(  archs.isAvailable( arch_id ) );
    SIXTRL_ASSERT( !archs.isShutdown( arch_id ) );

    /* Create an empty store */

    store_t store;
    store_t::lock_t const lock( *store.lockable() );

    ASSERT_TRUE( store.numArchitectures( lock ) == size_t{ 0 } );
    ASSERT_TRUE( !store.hasArchitecture( lock, arch_id ) );
    ASSERT_TRUE( store.numPlatforms( lock, arch_id ) == size_t{ 0 } );
    ASSERT_TRUE( !store.hasPlatform( lock, arch_id, platform_id_t{ 0 } ) );
    ASSERT_TRUE( store.totalNumNodes( lock ) == size_t{ 0 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id ) == size_t{ 0 } );
    ASSERT_TRUE( store.numNodeSets( lock ) == size_t{ 0 } );

    /* Create first node with non-set platform_id and device_id: */

    std::unique_ptr< node_info_t > ptr_node( new node_info_t( arch_id ) );
    node_info_t const* ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_cmp_node != nullptr );
    SIXTRL_ASSERT( ptr_node->archId( lock ) == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId( lock ) ==
                   store_t::ILLEGAL_PLATFORM_ID );

    SIXTRL_ASSERT( ptr_node->deviceId( lock ) == store_t::ILLEGAL_DEVICE_ID );

    ptr_node->setPlatformName( "platform0" );
    ptr_node->setDeviceName( "device00" );
    ptr_node->setDescription( "descr 00" );

    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform0" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device00" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 00" ) == 0 );

    /* add first node info to the store: */

    node_index_t const node_100_idx = store.addNode(
        lock, std::move( ptr_node ) );

    ASSERT_TRUE( node_100_idx != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( ptr_node.get() == nullptr );
    ASSERT_TRUE( store.hasArchitecture( lock, arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_100_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_100_idx ) == ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_100_idx )->ptrNodeStore() ==
                 &store );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_100_idx )->nodeIndex(
                lock ) == node_100_idx );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_100_idx )->platformId(
                lock ) != store_t::ILLEGAL_PLATFORM_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_100_idx )->deviceId(
                lock ) != store_t::ILLEGAL_DEVICE_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_100_idx )->platformId(
                lock ) == platform_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_100_idx )->deviceId(
                lock ) == device_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase(
                    lock, node_100_idx )->hasPlatformName() );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_100_idx
                    )->platformName().compare( "platform0" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_100_idx )->hasDeviceName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_100_idx
                    )->deviceName().compare( "device00" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_100_idx )->hasDescription() );
    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_100_idx )->description().compare( "descr 00" ) == 0 );

    ASSERT_TRUE( store.hasPlatform( lock, arch_id, platform_id_t{ 0 } ) );
    ASSERT_TRUE( store.totalNumNodes( lock ) == size_t{ 1 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id ) == size_t{ 1 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 0 } ) ==
        size_t{ 1 } );

    /* create a second node_info to the exisiting platform: */

    ptr_node.reset( new node_info_t( arch_id, "platform0", "device01",
         "descr 01", platform_id_t{ 0 }, store_t::ILLEGAL_DEVICE_ID ) );

    SIXTRL_ASSERT( ptr_node.get() != nullptr );
    ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_node->archId( lock ) == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId( lock ) == platform_id_t{ 0 } );
    SIXTRL_ASSERT( ptr_node->deviceId( lock ) == store_t::ILLEGAL_DEVICE_ID );
    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform0" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device01" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 01" ) == 0 );

    /* add second node to the store */

    node_index_t const node_101_idx = store.addNode(
        lock, std::move( ptr_node ) );

    ASSERT_TRUE( node_101_idx != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( node_100_idx != node_101_idx );
    ASSERT_TRUE( ptr_node.get() == nullptr );
    ASSERT_TRUE( store.hasArchitecture( lock, arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_101_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_101_idx ) == ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_101_idx )->ptrNodeStore() ==
                 &store );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_101_idx )->nodeIndex(
                lock ) == node_101_idx );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_101_idx )->platformId(
                lock ) != store_t::ILLEGAL_PLATFORM_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_101_idx )->deviceId(
                lock ) != store_t::ILLEGAL_DEVICE_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_101_idx )->platformId(
                lock ) == platform_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_101_idx )->deviceId(
                lock ) == device_id_t{ 1 } );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_101_idx )->hasPlatformName() );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_101_idx )->platformName().compare( "platform0" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_101_idx )->hasDeviceName() );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_101_idx )->deviceName().compare( "device01" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_101_idx )->hasDescription() );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_101_idx )->description().compare( "descr 01" ) == 0 );

    ASSERT_TRUE( store.hasPlatform( lock, arch_id, platform_id_t{ 0 } ) );
    ASSERT_TRUE( store.totalNumNodes( lock ) == size_t{ 2 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id ) == size_t{ 2 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 0 } ) ==
        size_t{ 2 } );

    /* create a third node_info,expected to get next free platform_id number */

    ptr_node.reset( new node_info_t( arch_id, "platform1", "device10",
         "descr 10", store_t::ILLEGAL_PLATFORM_ID,
            store_t::ILLEGAL_DEVICE_ID ) );

    SIXTRL_ASSERT( ptr_node.get() != nullptr );
    ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_node->archId( lock ) == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId( lock ) ==
        store_t::ILLEGAL_PLATFORM_ID );

    SIXTRL_ASSERT( ptr_node->deviceId( lock ) == store_t::ILLEGAL_DEVICE_ID );
    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform1" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device10" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 10" ) == 0 );

    /* add third node to the store */

    node_index_t const node_110_idx = store.addNode(
        lock, std::move( ptr_node ) );

    ASSERT_TRUE( node_110_idx != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( node_100_idx != node_110_idx );
    ASSERT_TRUE( node_101_idx != node_110_idx );
    ASSERT_TRUE( ptr_node.get() == nullptr );
    ASSERT_TRUE( store.hasArchitecture( lock, arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx ) == ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx )->ptrNodeStore() ==
                 &store );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx )->nodeIndex(
                lock ) == node_110_idx );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx )->platformId(
                lock ) != store_t::ILLEGAL_PLATFORM_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx )->deviceId(
                lock ) != store_t::ILLEGAL_DEVICE_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx )->platformId(
                lock ) == platform_id_t{ 1 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx )->deviceId(
                lock ) == device_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_110_idx )->hasPlatformName() );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_110_idx )->platformName().compare( "platform1" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx )->hasDeviceName() );
    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_110_idx )->deviceName().compare( "device10" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_110_idx )->hasDescription() );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_110_idx )->description().compare( "descr 10" ) == 0 );

    ASSERT_TRUE( store.hasPlatform( lock, arch_id, platform_id_t{ 1 } ) );
    ASSERT_TRUE( store.totalNumNodes( lock ) == size_t{ 3 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id ) == size_t{ 3 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 0 } ) ==
        size_t{ 2 } );

    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 1 } ) ==
        size_t{ 1 } );

    /* try to add the same node again, expect to get the same node_index */

    ptr_node.reset( new node_info_t( arch_id, "platform1", "device10",
         "descr 10", platform_id_t{ 1 }, device_id_t{ 0 }, &store ) );

    SIXTRL_ASSERT( ptr_node.get() != nullptr );
    ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_node->archId( lock ) == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId( lock ) == platform_id_t{ 1 } );
    SIXTRL_ASSERT( ptr_node->deviceId( lock ) == device_id_t{ 0 } );
    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform1" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device10" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 10" ) == 0 );

    node_index_t const node_110_idx_duplicate = store.addNode(
        lock, std::move( ptr_node ) );

    ASSERT_TRUE( node_110_idx_duplicate != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( node_110_idx_duplicate == node_110_idx );
    ASSERT_TRUE( store.hasArchitecture( lock, arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx ) != ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx )->ptrNodeStore() ==
                 &store );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_110_idx )->nodeIndex(
            lock ) == node_110_idx );

    ASSERT_TRUE( store.hasPlatform( lock, arch_id, platform_id_t{ 1 } ) );
    ASSERT_TRUE( store.totalNumNodes( lock ) == size_t{ 3 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id ) == size_t{ 3 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 0 } ) ==
        size_t{ 2 } );

    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 1 } ) ==
        size_t{ 1 } );

    /* add fourth node, leave a gap in the platform_id numbers */

    ptr_node.reset( new node_info_t( arch_id, "platform5", "device50",
         "descr 50", platform_id_t{ 5 }, store_t::ILLEGAL_DEVICE_ID ) );

    SIXTRL_ASSERT( ptr_node.get() != nullptr );
    ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_node->archId( lock ) == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId( lock ) == platform_id_t{ 5 } );
    SIXTRL_ASSERT( ptr_node->deviceId( lock ) == store_t::ILLEGAL_DEVICE_ID );
    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform5" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device50" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 50" ) == 0 );

    /* add fourth node to the store */

    node_index_t const node_500_idx = store.addNode(
        lock, std::move( ptr_node ) );

    ASSERT_TRUE( node_500_idx != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( node_100_idx != node_500_idx );
    ASSERT_TRUE( node_101_idx != node_500_idx );
    ASSERT_TRUE( node_110_idx != node_500_idx );
    ASSERT_TRUE( ptr_node.get() == nullptr );
    ASSERT_TRUE( store.hasArchitecture( lock, arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_500_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_500_idx ) == ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_500_idx )->ptrNodeStore() ==
                 &store );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_500_idx )->nodeIndex(
                lock ) == node_500_idx );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_500_idx )->platformId(
                lock ) != store_t::ILLEGAL_PLATFORM_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_500_idx )->deviceId(
                lock ) != store_t::ILLEGAL_DEVICE_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_500_idx )->platformId(
                lock ) == platform_id_t{ 5 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_500_idx )->deviceId(
                lock ) == device_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_500_idx )->hasPlatformName() );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_500_idx )->platformName().compare( "platform5" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_500_idx )->hasDeviceName() );
    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_500_idx )->deviceName().compare( "device50" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_500_idx )->hasDescription() );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_500_idx )->description().compare( "descr 50" ) == 0 );

    ASSERT_TRUE( store.hasPlatform( lock, arch_id, platform_id_t{ 5 } ) );
    ASSERT_TRUE( store.totalNumNodes( lock ) == size_t{ 4 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id ) == size_t{ 4 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 0 } ) ==
        size_t{ 2 } );

    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 1 } ) ==
        size_t{ 1 } );

    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 5 } ) ==
        size_t{ 1 } );

    /* add fifth node, expect next available platform_id  */

    ptr_node.reset( new node_info_t( arch_id, "platform6", "device60",
         "descr 60", store_t::ILLEGAL_PLATFORM_ID,
            store_t::ILLEGAL_DEVICE_ID ) );

    SIXTRL_ASSERT( ptr_node.get() != nullptr );
    ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_node->archId( lock ) == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId( lock ) ==
                   store_t::ILLEGAL_PLATFORM_ID );

    SIXTRL_ASSERT( ptr_node->deviceId( lock ) == store_t::ILLEGAL_DEVICE_ID );

    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform6" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device60" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 60" ) == 0 );

    /* add fifth node to the store */

    node_index_t const node_600_idx = store.addNode(
        lock, std::move( ptr_node ) );

    ASSERT_TRUE( node_600_idx != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( node_100_idx != node_600_idx );
    ASSERT_TRUE( node_101_idx != node_600_idx );
    ASSERT_TRUE( node_110_idx != node_600_idx );
    ASSERT_TRUE( node_500_idx != node_600_idx );
    ASSERT_TRUE( ptr_node.get() == nullptr );
    ASSERT_TRUE( store.hasArchitecture( lock, arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_600_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_600_idx ) == ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_600_idx )->ptrNodeStore() ==
                 &store );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_600_idx )->nodeIndex(
                lock ) == node_600_idx );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_600_idx )->platformId(
                lock ) != store_t::ILLEGAL_PLATFORM_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_600_idx )->deviceId(
                lock ) != store_t::ILLEGAL_DEVICE_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_600_idx )->platformId(
                lock ) == platform_id_t{ 6 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_600_idx )->deviceId(
                lock ) == device_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_600_idx )->hasPlatformName() );

    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_600_idx )->platformName().compare( "platform6" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_600_idx )->hasDeviceName() );
    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_600_idx )->deviceName().compare( "device60" ) == 0 );

    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_600_idx )->hasDescription() );
    ASSERT_TRUE( store.ptrNodeInfoBase(
        lock, node_600_idx )->description().compare( "descr 60" ) == 0 );

    ASSERT_TRUE( store.hasPlatform( lock, arch_id, platform_id_t{ 6 } ) );
    ASSERT_TRUE( store.totalNumNodes( lock ) == size_t{ 5 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id ) == size_t{ 5 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 0 } ) ==
        size_t{ 2 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 1 } ) ==
        size_t{ 1 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 5 } ) ==
        size_t{ 1 } );
    ASSERT_TRUE( store.numNodes( lock, arch_id, platform_id_t{ 6 } ) ==
        size_t{ 1 } );

    /* Remove node platform_id == 5, device_id == 0 */

    status_t status = store.removeNode( lock, node_500_idx );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( store.ptrNodeInfoBase( lock, node_500_idx ) == nullptr );

    ASSERT_TRUE(  store.hasPlatform( lock, arch_id, platform_id_t{ 5 } ) );
    ASSERT_TRUE(  store.totalNumNodes( lock ) == size_t{ 4 } );
    ASSERT_TRUE(  store.numNodes( lock, arch_id ) == size_t{ 4 } );
    ASSERT_TRUE(  store.numNodes( lock, arch_id, platform_id_t{ 0 } ) ==
                    size_t{ 2 } );
    ASSERT_TRUE(  store.numNodes( lock, arch_id, platform_id_t{ 1 } ) ==
                    size_t{ 1 } );
    ASSERT_TRUE(  store.numNodes( lock, arch_id, platform_id_t{ 5 } ) ==
                    size_t{ 0 } );
    ASSERT_TRUE(  store.numNodes( lock, arch_id, platform_id_t{ 6 } ) ==
                    size_t{ 1 } );
}

/* end: tests/sixtracklib/common/control/test_node_store_cxx.cpp */
