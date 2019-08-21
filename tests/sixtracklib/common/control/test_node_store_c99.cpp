#include "sixtracklib/common/control/node_store.h"

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
#include "sixtracklib/common/control/node_info.h"
#include "sixtracklib/testlib.h"

TEST( C99_CommonControlNodeStoreTests, NodeStoreCreateAddNodeInfoDestroy )
{
    using store_t       = ::NS(NodeStore);
    using node_info_t   = ::NS(NodeInfoBase);
    using platform_id_t = ::NS(node_platform_id_t);
    using device_id_t   = ::NS(node_device_id_t);
    using size_t        = ::NS(arch_size_t);
    using node_index_t  = ::NS(node_index_t);
    using status_t      = ::NS(arch_status_t);

    /* Verify that one suitable architecture is available */
    ::NS(Architectures) const* ptr_archs = ::NS(Architectures_get_ptr_const)();
    SIXTRL_ASSERT( ptr_archs != nullptr );
    SIXTRL_ASSERT( ::NS(Architectures_get_num_architectures)(
        ptr_archs ) > size_t{ 0 } );

    ::NS(arch_id_t) const arch_id = ::NS(Architectures_get_arch_id_by_number)(
        ptr_archs, size_t{ 0 } );

    SIXTRL_ASSERT(  arch_id != ::NS(ARCHITECTURE_ILLEGAL) );
    SIXTRL_ASSERT(  arch_id != ::NS(ARCHITECTURE_NONE) );
    SIXTRL_ASSERT(  ::NS(Architectures_has_architecture)( ptr_archs, arch_id ) );
    SIXTRL_ASSERT(  ::NS(Architectures_is_available)( ptr_archs, arch_id ) );
    SIXTRL_ASSERT( !::NS(Architectures_is_shutdown)( ptr_archs, arch_id ) );

    /* Create an empty store */

    store_t* store = ::NS(NodeStore_new)();
    ASSERT_TRUE( store != nullptr );

    ASSERT_TRUE( ::NS(NodeStore_get_num_architectures)( store ) == size_t{ 0 } );
    ASSERT_TRUE( !::NS(NodeStore_has_architecture)( store, arch_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_platforms)( store, arch_id ) == size_t{ 0 } );
    ASSERT_TRUE( !::NS(NodeStore_has_platform)( store, arch_id, platform_id_t{ 0 } ) );
    ASSERT_TRUE( ::NS(NodeStore_get_total_num_nodes)( store ) == size_t{ 0 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes)( store, arch_id ) == size_t{ 0 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_node_sets)( store ) == size_t{ 0 } );

    /* Create first node with non-set platform_id and device_id: */

    node_info_t* ptr_node = ::NS(NodeInfoBase_create)( arch_id, nullptr );

    SIXTRL_ASSERT( ::NS(NodeInfo_get_arch_id)( ptr_node ) == arch_id );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_platform_id)( ptr_node ) == ::NS(NODE_ILLEGAL_PLATFORM_ID) );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_device_id)( ptr_node ) == ::NS(NODE_ILLEGAL_DEVICE_ID) );

    ::NS(NodeInfo_set_platform_name)( ptr_node, "platform0" );
    ::NS(NodeInfo_set_device_name)( ptr_node, "device00" );
    ::NS(NodeInfo_set_description)( ptr_node, "descr 00" );

    SIXTRL_ASSERT( ::NS(NodeInfo_has_platform_name)( ptr_node ) );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_platform_name_str)( ptr_node ), "platform0" ) == 0 );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_device_name_str)( ptr_node ), "device00" ) == 0 );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_description_str)( ptr_node ), "descr 00" ) == 0 );

    /* add first node info to the store: */

    node_index_t const node_100_idx = ::NS(NodeStore_add_node)( store, ptr_node );

    ASSERT_TRUE( node_100_idx != ::NS(NODE_UNDEFINED_INDEX) );

    ASSERT_TRUE( ::NS(NodeStore_has_architecture)( store, arch_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx ) != nullptr );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx ) == ptr_node );
    ptr_node = nullptr;

    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx )->ptrNodeStore() == store );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx )->nodeIndex() == node_100_idx );

    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx ) ) != ::NS(NODE_ILLEGAL_PLATFORM_ID) );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx ) ) != ::NS(NODE_ILLEGAL_DEVICE_ID) );

    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx ) ) == platform_id_t{ 0 } );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx ) ) == device_id_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeInfo_has_platform_name)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_platform_name_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx ) ), "platform0" ) == 0 );

    ASSERT_TRUE( ::NS(NodeInfo_has_device_name)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_device_name_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx ) ), "device00" ) == 0 );

    ASSERT_TRUE( ::NS(NodeInfo_has_description)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_description_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_100_idx ) ), "descr 00" ) == 0 );

    ASSERT_TRUE( ::NS(NodeStore_has_platform)( store, arch_id, platform_id_t{ 0 } ) );
    ASSERT_TRUE( ::NS(NodeStore_get_total_num_nodes)( store ) == size_t{ 1 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes)( store, arch_id ) == size_t{ 1 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 0 } ) == size_t{ 1 } );

    /* create a second node_info to the exisiting platform: */

    SIXTRL_ASSERT( ptr_node == nullptr );
    ptr_node = ::NS(NodeInfoBase_new_detailed)( arch_id, "platform0",
        "device01", "descr 01", platform_id_t{ 0 },
            ::NS(NODE_ILLEGAL_DEVICE_ID), nullptr );

    ASSERT_TRUE( ptr_node != nullptr );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_arch_id)( ptr_node ) == arch_id );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_platform_id)( ptr_node ) == platform_id_t{ 0 } );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_device_id)( ptr_node ) == ::NS(NODE_ILLEGAL_DEVICE_ID) );
    SIXTRL_ASSERT( ::NS(NodeInfo_has_platform_name)( ptr_node ) );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_platform_name_str)( ptr_node ), "platform0" ) == 0 );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_device_name_str)( ptr_node ), "device01" ) == 0 );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_description_str)( ptr_node ), "descr 01" ) == 0 );

    /* add second node to the store */

    node_index_t const node_101_idx = ::NS(NodeStore_add_node)( store, ptr_node );

    ASSERT_TRUE( node_101_idx != ::NS(NODE_UNDEFINED_INDEX) );
    ASSERT_TRUE( node_100_idx != node_101_idx );

    ASSERT_TRUE( ::NS(NodeStore_has_architecture)( store, arch_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx ) != nullptr );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx ) == ptr_node );
    ptr_node = nullptr;

    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx )->ptrNodeStore() == store );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx )->nodeIndex() == node_101_idx );

    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx ) ) != ::NS(NODE_ILLEGAL_PLATFORM_ID) );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx ) ) != ::NS(NODE_ILLEGAL_DEVICE_ID) );

    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx ) ) == platform_id_t{ 0 } );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx ) ) == device_id_t{ 1 } );

    ASSERT_TRUE( ::NS(NodeInfo_has_platform_name)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_platform_name_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx ) ), "platform0" ) == 0 );

    ASSERT_TRUE( ::NS(NodeInfo_has_device_name)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_device_name_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx ) ), "device01" ) == 0 );

    ASSERT_TRUE( ::NS(NodeInfo_has_description)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_description_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_101_idx ) ), "descr 01" ) == 0 );

    ASSERT_TRUE( ::NS(NodeStore_has_platform)( store, arch_id, platform_id_t{ 0 } ) );
    ASSERT_TRUE( ::NS(NodeStore_get_total_num_nodes)( store ) == size_t{ 2 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes)( store, arch_id ) == size_t{ 2 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );

    /* create a third node_info,expected to get next free platform_id number */

    ptr_node = ::NS(NodeInfoBase_new_detailed)( arch_id, "platform1",
        "device10", "descr 10", ::NS(NODE_ILLEGAL_PLATFORM_ID),
            ::NS(NODE_ILLEGAL_DEVICE_ID), store );

    ASSERT_TRUE( ptr_node != nullptr );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_arch_id)( ptr_node ) == arch_id );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_platform_id)( ptr_node ) == ::NS(NODE_ILLEGAL_PLATFORM_ID) );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_device_id)( ptr_node ) == ::NS(NODE_ILLEGAL_DEVICE_ID) );
    SIXTRL_ASSERT( ::NS(NodeInfo_has_platform_name)( ptr_node ) );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_platform_name_str)( ptr_node ), "platform1" ) == 0 );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_device_name_str)( ptr_node ), "device10" ) == 0 );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_description_str)( ptr_node ), "descr 10" ) == 0 );

    /* add third node to the store */

    node_index_t const node_110_idx = ::NS(NodeStore_add_node)( store, ptr_node );

    ASSERT_TRUE( node_110_idx != ::NS(NODE_UNDEFINED_INDEX) );
    ASSERT_TRUE( node_100_idx != node_110_idx );
    ASSERT_TRUE( node_101_idx != node_110_idx );

    ASSERT_TRUE( ::NS(NodeStore_has_architecture)( store, arch_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) != nullptr );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) == ptr_node );
    ptr_node = nullptr;

    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx )->ptrNodeStore() == store );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx )->nodeIndex() == node_110_idx );

    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) != ::NS(NODE_ILLEGAL_PLATFORM_ID) );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) != ::NS(NODE_ILLEGAL_DEVICE_ID) );

    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) == platform_id_t{ 1 } );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) == device_id_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeInfo_has_platform_name)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_platform_name_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ), "platform1" ) == 0 );

    ASSERT_TRUE( ::NS(NodeInfo_has_device_name)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_device_name_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ), "device10" ) == 0 );

    ASSERT_TRUE( ::NS(NodeInfo_has_description)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_description_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ), "descr 10" ) == 0 );

    ASSERT_TRUE( ::NS(NodeStore_has_platform)( store, arch_id, platform_id_t{ 1 } ) );
    ASSERT_TRUE( ::NS(NodeStore_get_total_num_nodes)( store ) == size_t{ 3 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes)( store, arch_id ) == size_t{ 3 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 1 } ) == size_t{ 1 } );

    /* try to add the same node again, expect to get the same node_index */

    ptr_node = ::NS(NodeInfoBase_new_detailed)( arch_id, "platform1",
        "device10 updated", "descr 10 updated", platform_id_t{ 1 },
            device_id_t{ 0 }, store );

    ASSERT_TRUE( ptr_node != nullptr );
    ASSERT_TRUE( ptr_node != ::NS(NodeStore_get_ptr_node_info_base)(
        store, node_110_idx ) );

    SIXTRL_ASSERT( ::NS(NodeInfo_get_arch_id)( ptr_node ) == arch_id );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_platform_id)( ptr_node ) == platform_id_t{ 1 } );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_device_id)( ptr_node ) == device_id_t{ 0 } );
    SIXTRL_ASSERT( ::NS(NodeInfo_has_platform_name)( ptr_node ) );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_platform_name_str)( ptr_node ), "platform1" ) == 0 );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_device_name_str)( ptr_node ), "device10 updated" ) == 0 );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_description_str)( ptr_node ), "descr 10 updated" ) == 0 );

    node_index_t const node_110_idx_duplicate =
        ::NS(NodeStore_add_node)( store, ptr_node );

    ASSERT_TRUE( node_110_idx_duplicate != ::NS(NODE_UNDEFINED_INDEX) );
    ASSERT_TRUE( node_110_idx_duplicate == node_110_idx );
    ASSERT_TRUE( ::NS(NodeStore_has_architecture)( store, arch_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) != nullptr );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) == ptr_node );
    ptr_node = nullptr;

    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx )->ptrNodeStore() == store );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx )->nodeIndex() == node_110_idx );

    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx )->ptrNodeStore() == store );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx )->nodeIndex() == node_110_idx );

    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) != ::NS(NODE_ILLEGAL_PLATFORM_ID) );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) != ::NS(NODE_ILLEGAL_DEVICE_ID) );

    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) == platform_id_t{ 1 } );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) == device_id_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeInfo_has_platform_name)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_platform_name_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ), "platform1" ) == 0 );

    ASSERT_TRUE( ::NS(NodeInfo_has_device_name)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_device_name_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ), "device10 updated" ) == 0 );

    ASSERT_TRUE( ::NS(NodeInfo_has_description)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_description_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_110_idx ) ), "descr 10 updated" ) == 0 );

    ASSERT_TRUE( ::NS(NodeStore_has_platform)( store, arch_id, platform_id_t{ 1 } ) );
    ASSERT_TRUE( ::NS(NodeStore_get_total_num_nodes)( store ) == size_t{ 3 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes)( store, arch_id ) == size_t{ 3 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 1 } ) == size_t{ 1 } );

    /* add fourth node, leave a gap in the platform_id numbers */

    ptr_node = ::NS(NodeInfoBase_new_detailed)( arch_id, "platform5",
        "device50", "descr 50", platform_id_t{ 5 },
            ::NS(NODE_ILLEGAL_DEVICE_ID), store );

    SIXTRL_ASSERT( ::NS(NodeInfo_get_arch_id)( ptr_node ) == arch_id );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_platform_id)( ptr_node ) == platform_id_t{ 5 } );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_device_id)( ptr_node ) == ::NS(NODE_ILLEGAL_DEVICE_ID) );
    SIXTRL_ASSERT( ::NS(NodeInfo_has_platform_name)( ptr_node ) );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_platform_name_str)( ptr_node ), "platform5" ) == 0 );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_device_name_str)( ptr_node ), "device50" ) == 0 );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_description_str)( ptr_node ), "descr 50" ) == 0 );

    /* add fourth node to the store */

    node_index_t const node_500_idx = ::NS(NodeStore_add_node)( store, ptr_node );

    ASSERT_TRUE( node_500_idx != ::NS(NODE_UNDEFINED_INDEX) );
    ASSERT_TRUE( node_100_idx != node_500_idx );
    ASSERT_TRUE( node_101_idx != node_500_idx );
    ASSERT_TRUE( node_110_idx != node_500_idx );

    ASSERT_TRUE( ::NS(NodeStore_has_architecture)( store, arch_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) != nullptr );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) == ptr_node );
    ptr_node = nullptr;

    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx )->ptrNodeStore() == store );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx )->nodeIndex() == node_500_idx );

    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) ) != ::NS(NODE_ILLEGAL_PLATFORM_ID) );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) ) != ::NS(NODE_ILLEGAL_DEVICE_ID) );

    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) ) == platform_id_t{ 5 } );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) ) == device_id_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeInfo_has_platform_name)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_platform_name_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) ), "platform5" ) == 0 );

    ASSERT_TRUE( ::NS(NodeInfo_has_device_name)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_device_name_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) ), "device50" ) == 0 );

    ASSERT_TRUE( ::NS(NodeInfo_has_description)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_description_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) ), "descr 50" ) == 0 );

    ASSERT_TRUE( ::NS(NodeStore_has_platform)( store, arch_id, platform_id_t{ 5 } ) );
    ASSERT_TRUE( ::NS(NodeStore_get_total_num_nodes)( store ) == size_t{ 4 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes)( store, arch_id ) == size_t{ 4 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 1 } ) == size_t{ 1 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 5 } ) == size_t{ 1 } );

    /* add fifth node, expect next available platform_id  */

    ptr_node = ::NS(NodeInfoBase_new_detailed)( arch_id, "platform6",
        "device60", "descr 60", ::NS(NODE_ILLEGAL_PLATFORM_ID),
            ::NS(NODE_ILLEGAL_DEVICE_ID), store );

    SIXTRL_ASSERT( ::NS(NodeInfo_get_arch_id)( ptr_node ) == arch_id );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_platform_id)( ptr_node ) == ::NS(NODE_ILLEGAL_PLATFORM_ID) );
    SIXTRL_ASSERT( ::NS(NodeInfo_get_device_id)( ptr_node ) == ::NS(NODE_ILLEGAL_DEVICE_ID) );
    SIXTRL_ASSERT( ::NS(NodeInfo_has_platform_name)( ptr_node ) );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_platform_name_str)( ptr_node ), "platform6" ) == 0 );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_device_name_str)( ptr_node ), "device60" ) == 0 );
    SIXTRL_ASSERT( std::strcmp( ::NS(NodeInfo_get_description_str)( ptr_node ), "descr 60" ) == 0 );

    /* add fifth node to the store */

    node_index_t const node_600_idx = ::NS(NodeStore_add_node)( store, ptr_node );

    ASSERT_TRUE( node_600_idx != ::NS(NODE_UNDEFINED_INDEX) );
    ASSERT_TRUE( node_100_idx != node_600_idx );
    ASSERT_TRUE( node_101_idx != node_600_idx );
    ASSERT_TRUE( node_110_idx != node_600_idx );
    ASSERT_TRUE( node_500_idx != node_600_idx );

    ASSERT_TRUE( ::NS(NodeStore_has_architecture)( store, arch_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx ) != nullptr );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx ) == ptr_node );
    ptr_node = nullptr;

    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx )->ptrNodeStore() == store );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx )->nodeIndex() == node_600_idx );

    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx ) ) != ::NS(NODE_ILLEGAL_PLATFORM_ID) );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx ) ) != ::NS(NODE_ILLEGAL_DEVICE_ID) );

    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx ) ) == platform_id_t{ 6 } );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx ) ) == device_id_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeInfo_has_platform_name)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_platform_name_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx ) ), "platform6" ) == 0 );

    ASSERT_TRUE( ::NS(NodeInfo_has_device_name)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_device_name_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx ) ), "device60" ) == 0 );

    ASSERT_TRUE( ::NS(NodeInfo_has_description)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx ) ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_description_str)( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_600_idx ) ), "descr 60" ) == 0 );

    ASSERT_TRUE( ::NS(NodeStore_has_platform)( store, arch_id, platform_id_t{ 6 } ) );
    ASSERT_TRUE( ::NS(NodeStore_get_total_num_nodes)( store ) == size_t{ 5 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes)( store, arch_id ) == size_t{ 5 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 1 } ) == size_t{ 1 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 5 } ) == size_t{ 1 } );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 6 } ) == size_t{ 1 } );

    /* Remove node platform_id == 5, device_id == 0 */

    status_t status = ::NS(NodeStore_remove_node)( store, node_500_idx );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_info_base)( store, node_500_idx ) == nullptr );

    ASSERT_TRUE(  ::NS(NodeStore_has_platform)( store, arch_id, platform_id_t{ 5 } ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_total_num_nodes)( store ) == size_t{ 4 } );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_nodes)( store, arch_id ) == size_t{ 4 } );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 0 } ) == size_t{ 2 } );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 1 } ) == size_t{ 1 } );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 5 } ) == size_t{ 0 } );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_nodes_for_platform)( store, arch_id, platform_id_t{ 6 } ) == size_t{ 1 } );

    /* --------------------------------------------------------------------- */

    ::NS(NodeStore_delete)( store );
}

/* end: tests/sixtracklib/common/control/test_node_store_cxx.cpp */
