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
    using node_id_t     = st::NodeId;
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

<<<<<<< HEAD
    /* Create first node with non-set platform_id and device_id: */

=======
>>>>>>> origin/cuda_dev
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

<<<<<<< HEAD
    /* add first node info to the store: */

=======
>>>>>>> origin/cuda_dev
    node_index_t const node_100_idx = store.addNode( std::move( ptr_node ) );

    ASSERT_TRUE( node_100_idx != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( ptr_node.get() == nullptr );
    ASSERT_TRUE( store.hasArchitecture( arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx ) == ptr_cmp_node );

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
                 "platform0" ) );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->hasDeviceName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->deviceName().compare(
                 "device00" ) );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->hasDescription() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_100_idx )->description().compare(
                 "descr 00" ) );

    ASSERT_TRUE( store.hasPlatform( arch_id, platform_id_t{ 0 } ) );
    ASSERT_TRUE( store.totalNumNodes() == size_t{ 1 } );
    ASSERT_TRUE( store.numNodes( arch_id ) == size_t{ 1 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 0 } ) == size_t{ 1 } );

<<<<<<< HEAD
    /* create a second node_info to the exisiting platform: */

    ptr_node.reset( new node_info_t( arch_id, "platform0", "device01",
         "descr 01", platform_id_t{ 0 }, store_t::ILLEGAL_DEVICE_ID ) );
=======
    ptr_node.reset( new node_info_t( arch_id, "platform0", "device01",
         "descr 01", platform_id_t{ 0 }, _store_t::ILLEGAL_DEVICE_ID ) );
>>>>>>> origin/cuda_dev

    SIXTRL_ASSERT( ptr_node.get() != nullptr );
    ptr_cmp_node = ptr_node.get();

    SIXTRL_ASSERT( ptr_node->archId() == arch_id );
    SIXTRL_ASSERT( ptr_node->platformId() == platform_id_t{ 0 } );
    SIXTRL_ASSERT( ptr_node->deviceId() == store_t::ILLEGAL_DEVICE_ID );
    SIXTRL_ASSERT( ptr_node->hasPlatformName() );
    SIXTRL_ASSERT( ptr_node->platformName().compare( "platform0" ) == 0 );
    SIXTRL_ASSERT( ptr_node->deviceName().compare( "device01" ) == 0 );
    SIXTRL_ASSERT( ptr_node->description().compare( "descr 11" ) == 0 );

<<<<<<< HEAD
    /* add second node to the store */

=======
>>>>>>> origin/cuda_dev
    node_index_t const node_101_idx = store.addNode( std::move( ptr_node ) );

    ASSERT_TRUE( node_101_idx != store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( node_100_idx != node_101_idx );
    ASSERT_TRUE( ptr_node.get() == nullptr );
    ASSERT_TRUE( store.hasArchitecture( arch_id ) );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx ) != nullptr );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx ) == ptr_cmp_node );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->platformId() !=
                 store_t::ILLEGAL_PLATFORM_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->deviceId() !=
                 store_t::ILLEGAL_DEVICE_ID );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->platformId() ==
                 platform_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->deviceId() ==
                 device_id_t{ 0 } );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->hasPlatformName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->platformName().compare(
                 "platform0" ) );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->hasDeviceName() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->deviceName().compare(
                 "device01" ) );

    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->hasDescription() );
    ASSERT_TRUE( store.ptrNodeInfoBase( node_101_idx )->description().compare(
                 "descr 01" ) );

    ASSERT_TRUE( store.hasPlatform( arch_id, platform_id_t{ 0 } ) );
    ASSERT_TRUE( store.totalNumNodes() == size_t{ 2 } );
    ASSERT_TRUE( store.numNodes( arch_id ) == size_t{ 2 } );
    ASSERT_TRUE( store.numNodes( arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );


}

/* end: tests/sixtracklib/common/control/test_node_store_cxx.cpp */
