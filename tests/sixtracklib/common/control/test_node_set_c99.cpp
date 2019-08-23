#include "sixtracklib/common/control/node_set.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_info.h"
#include "sixtracklib/common/control/node_set.h"
#include "sixtracklib/testlib.h"

TEST( C99_CommonControlNodeSetTests, NodeSetBaseBasicUsage )
{
    using store_t          = ::NS(NodeStore);
    using node_set_t       = ::NS(TestNodeSetBase);
    using platform_id_t    = ::NS(node_platform_id_t);
    using size_t           = ::NS(arch_size_t);
    using arch_id_t        = ::NS(arch_id_t);
    using node_index_t     = ::NS(node_index_t);
    using node_set_id_t    = ::NS(node_set_id_t);
    using status_t         = ::NS(arch_status_t);

    /* Create three dummy architectures to allow variation in the
     * node sets based on the arch_id parameter: */

    ::NS(Architectures)* ptr_archs = ::NS(Architectures_get_ptr)();

    static constexpr size_t NUM_ARCHS = size_t{ 5 };
    arch_id_t arch_ids[ NUM_ARCHS ] =
    {
        ::NS(NODE_UNDEFINED_INDEX), ::NS(NODE_UNDEFINED_INDEX),
        ::NS(NODE_UNDEFINED_INDEX), ::NS(NODE_UNDEFINED_INDEX),
        ::NS(NODE_UNDEFINED_INDEX)
    };

    status_t status = ::NS(Architectures_setup)(
        ptr_archs, NUM_ARCHS, arch_id_t{ 32 }, &arch_ids[ 0 ] );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    /* Create an empty store */

    store_t* store = ::NS(NodeStore_new)();
    ASSERT_TRUE( store != nullptr );

    /* Setup node_infos to be used with the NodeSetBase instances */

    static constexpr size_t NUM_NODES = 12;

    const arch_id_t nodes_arch_ids[ NUM_NODES ] =
    {
        arch_ids[ 0 ], arch_ids[ 0 ], arch_ids[ 0 ],
        arch_ids[ 1 ], arch_ids[ 1 ],
        arch_ids[ 2 ],
        arch_ids[ 3 ], arch_ids[ 3 ], arch_ids[ 3 ], arch_ids[ 3 ],
        arch_ids[ 4 ], arch_ids[ 4 ]
    };

    const platform_id_t nodes_platform_ids[ NUM_NODES ] =
    {
        platform_id_t{ 0 }, platform_id_t{ 0 }, platform_id_t{ 0 },
        platform_id_t{ 0 }, platform_id_t{ 1 },
        platform_id_t{ 0 },
        ::NS(NODE_ILLEGAL_PLATFORM_ID), ::NS(NODE_ILLEGAL_PLATFORM_ID),
        ::NS(NODE_ILLEGAL_PLATFORM_ID), ::NS(NODE_ILLEGAL_PLATFORM_ID),
        platform_id_t{ 42 }, ::NS(NODE_ILLEGAL_PLATFORM_ID)
    };

    const size_t nodes_max_attach_cnt[ NUM_NODES ] =
    {
        size_t{ 1 }, size_t{ 1 }, size_t{ 1 },
        size_t{ 2 }, size_t{ 2 },
        size_t{ 0 },
        size_t{ 1 }, size_t{ 2 }, size_t{ 2 }, size_t{ 2 },
        size_t{ 1 }, size_t{ 1 }
    };

    const size_t nodes_max_selection_cnt[ NUM_NODES ] =
    {
        size_t{ 1 }, size_t{ 1 }, size_t{ 1 },
        size_t{ 2 }, size_t{ 2 },
        size_t{ 0 },
        size_t{ 1 }, size_t{ 1 }, size_t{ 1 }, size_t{ 0 },
        size_t{ 1 }, size_t{ 2 }
    };

    node_index_t cmp_node_indices[ NUM_NODES ];
    std::fill( &cmp_node_indices[ 0 ], &cmp_node_indices[ NUM_NODES ],
               ::NS(NODE_UNDEFINED_INDEX) );

    status = ::NS(TestNodeInfo_add_to_node_store)( store, NUM_NODES,
        &nodes_arch_ids[ 0 ], &nodes_platform_ids[ 0 ],
            &nodes_max_attach_cnt[ 0 ], &nodes_max_selection_cnt[ 0 ],
                &cmp_node_indices[ 0 ] );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    SIXTRL_ASSERT( ::NS(NodeStore_get_total_num_nodes)( store ) == NUM_NODES );

    std::vector< node_index_t > node_indices(
        NUM_NODES, ::NS(NODE_UNDEFINED_INDEX) );

    size_t cmp_num_nodes = size_t{ 0 };
    status = ::NS(NodeStore_get_all_node_indices)(
        store, NUM_NODES, node_indices.data(), &cmp_num_nodes );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( cmp_num_nodes == NUM_NODES );
    ASSERT_TRUE( std::equal( node_indices.begin(), node_indices.end(),
                             &cmp_node_indices[ 0 ] ) );

    SIXTRL_ASSERT( ::NS(NodeStore_has_architecture)( store, arch_ids[ 0 ] ) );
    SIXTRL_ASSERT( ::NS(NodeStore_has_architecture)( store, arch_ids[ 1 ] ) );
    SIXTRL_ASSERT( ::NS(NodeStore_has_architecture)( store, arch_ids[ 2 ] ) );
    SIXTRL_ASSERT( ::NS(NodeStore_has_architecture)( store, arch_ids[ 3 ] ) );
    SIXTRL_ASSERT( ::NS(NodeStore_has_architecture)( store, arch_ids[ 4 ] ) );

    SIXTRL_ASSERT( ::NS(NodeStore_get_num_nodes)(
        store, arch_ids[ 0 ] ) == size_t{ 3 } );

    SIXTRL_ASSERT( ::NS(NodeStore_get_num_nodes)(
        store, arch_ids[ 1 ] ) == size_t{ 2 } );

    SIXTRL_ASSERT( ::NS(NodeStore_get_num_nodes)(
        store, arch_ids[ 2 ] ) == size_t{ 1 } );

    SIXTRL_ASSERT( ::NS(NodeStore_get_num_nodes)(
        store, arch_ids[ 3 ] ) == size_t{ 4 } );

    SIXTRL_ASSERT( ::NS(NodeStore_get_num_nodes)(
        store, arch_ids[ 4 ] ) == size_t{ 2 } );

    for( auto const node_index : node_indices )
    {
        auto ptr_node_info = ::NS(NodeStore_get_ptr_const_node_info_base)(
            store, node_index );

        ASSERT_TRUE( ptr_node_info != nullptr );

        SIXTRL_ASSERT( !::NS(NodeStore_is_node_attached_to_any_set)(
            store, node_index ) );

        SIXTRL_ASSERT( !::NS(NodeStore_is_node_selected_by_any_set)(
            store, node_index ) );

        SIXTRL_ASSERT( !::NS(NodeStore_is_node_default_for_any_set)(
            store, node_index ) );
    }

    /* --------------------------------------------------------------------- */
    /* Verify initial state - no node sets available */

    ASSERT_TRUE( !::NS(NodeStore_has_node_sets)( store ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_node_sets)( store ) == size_t{ 0 } );

    /* create a new node set ... */

    node_set_t* ptr_node_set_1a = ::NS(TestNodeSetBase_create)( store );
    ASSERT_TRUE( ptr_node_set_1a != nullptr );
    ASSERT_TRUE( ::NS(NodeSet_get_ptr_node_store)( ptr_node_set_1a ) != nullptr );
    ASSERT_TRUE( ::NS(NodeSet_get_ptr_node_store)( ptr_node_set_1a ) == store );

    /* ... and add it to the store */

    node_set_id_t const node_set_1a_id =
        ::NS(NodeStore_add_node_set)( store, ptr_node_set_1a );

    ASSERT_TRUE( node_set_1a_id != ::NS(NODE_ILLEGAL_NODE_SET_ID) );
    ASSERT_TRUE( ::NS(NodeStore_has_node_set)( store, node_set_1a_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_node_sets)( store ) == size_t{ 1 } );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_set_base)(
        store, node_set_1a_id ) == ptr_node_set_1a );

    ASSERT_TRUE( ::NS(NodeSet_get_node_set_id)( ptr_node_set_1a ) ==
        node_set_1a_id );

    ASSERT_TRUE( ::NS(NodeSet_get_num_nodes)( ptr_node_set_1a ) ==
        size_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeSet_get_min_node_index)( ptr_node_set_1a ) ==
        ::NS(NODE_UNDEFINED_INDEX) );

    ASSERT_TRUE( ::NS(NodeSet_get_max_node_index)( ptr_node_set_1a ) ==
        ::NS(NODE_UNDEFINED_INDEX) );

    /* there are still none nodes attached to this node set */

    for( auto const idx : node_indices )
    {
        auto ptr_node_info = ::NS(NodeStore_get_ptr_const_node_info_base)(
            store, idx );

        ASSERT_TRUE( ptr_node_info != nullptr );

        ASSERT_TRUE( !::NS(NodeStore_is_node_attached_to_any_set)(
            store, idx ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_attached_to_set)(
            store, idx, node_set_1a_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_any_set)(
            store, idx ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
            store, idx, node_set_1a_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_any_set)(
            store, idx ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_set)(
            store, idx, node_set_1a_id ) );
    }

    /* --------------------------------------------------------------------- */
    /* Attach all nodes from arch_ids[ 0 ] to node_set_1a_id: */

    status = ::NS(NodeStore_get_node_indices_for_architecture)(
        store, NUM_NODES, node_indices.data(), arch_ids[ 0 ], &cmp_num_nodes );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( cmp_num_nodes == ::NS(NodeStore_get_num_nodes)(
        store, arch_ids[ 0 ] ) );

    status = ::NS(NodeStore_attach_all_architecture_nodes_to_set)(
        store, arch_ids[ 0 ], node_set_1a_id );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_num_nodes)( ptr_node_set_1a ) ==
                 ::NS(NodeStore_get_num_nodes)( store, arch_ids[ 0 ] ) );

    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_set)( store, node_set_1a_id ) ==
                 ::NS(NodeStore_get_num_nodes)( store, arch_ids[ 0 ] ) );

    auto idx_it  = node_indices.begin();
    auto idx_end = node_indices.begin();

    std::advance( idx_end,
                  ::NS(NodeStore_get_num_nodes)( store, arch_ids[ 0 ] ) );

    for( ; idx_it != idx_end ; ++idx_it )
    {
        auto ptr_node_info = ::NS(NodeStore_get_ptr_const_node_info_base)(
            store, *idx_it );

        ASSERT_TRUE( ptr_node_info != nullptr );

        ASSERT_TRUE( ::NS(NodeStore_is_node_attached_to_any_set)(
            store, *idx_it ) );

        ASSERT_TRUE( ::NS(NodeStore_is_node_attached_to_set)(
            store, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_any_set)(
            store, *idx_it ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
            store, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE(  ::NS(NodeStore_can_node_be_selected_by_set)(
            store, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_any_set)(
            store, *idx_it ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_set)(
            store, *idx_it, node_set_1a_id ) );
    }

    /* --------------------------------------------------------------------- */
    /* Add another node_set for arch_ids[ 0 ]: */

     node_set_t* ptr_node_set_1b = ::NS(TestNodeSetBase_create)( store );
    ASSERT_TRUE( ptr_node_set_1b != nullptr );

    ASSERT_TRUE( ::NS(NodeSet_get_ptr_node_store)( ptr_node_set_1b ) != nullptr );
    ASSERT_TRUE( ::NS(NodeSet_get_ptr_node_store)( ptr_node_set_1b ) == store );

    /* ... and add it to the store */

    node_set_id_t const node_set_1b_id =
        ::NS(NodeStore_add_node_set)( store, ptr_node_set_1b );

    ASSERT_TRUE( node_set_1b_id != ::NS(NODE_ILLEGAL_NODE_SET_ID) );
    ASSERT_TRUE( ::NS(NodeStore_has_node_set)( store, node_set_1b_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_node_sets)( store ) == size_t{ 2 } );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_set_base)(
        store, node_set_1b_id ) == ptr_node_set_1b );

    ASSERT_TRUE( ::NS(NodeSet_get_num_nodes)(
        ptr_node_set_1b ) == size_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeSet_get_min_node_index)(
        ptr_node_set_1b ) == ::NS(NODE_UNDEFINED_INDEX) );

    ASSERT_TRUE( ::NS(NodeSet_get_max_node_index)(
        ptr_node_set_1b ) == ::NS(NODE_UNDEFINED_INDEX) );

    /* the nodes of arch_ids[ 0 ] have a max attachement cnt of 1; thus,it
     * should not be possible to attach any of these nodes to node_set_1b_id: */

    status = ::NS(NodeStore_attach_all_architecture_nodes_to_set)(
        store, arch_ids[ 0 ], node_set_1b_id );

    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );

    idx_it = node_indices.begin();

    for( ; idx_it != idx_end ; ++idx_it )
    {
        auto ptr_node_info = ::NS(NodeStore_get_ptr_const_node_info_base)(
            store, *idx_it );

        ASSERT_TRUE( ptr_node_info != nullptr );

        ASSERT_TRUE(  ::NS(NodeStore_is_node_attached_to_any_set)(
            store, *idx_it ) );

        ASSERT_TRUE(  ::NS(NodeStore_is_node_attached_to_set)(
            store, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_attached_to_set)(
            store, *idx_it, node_set_1b_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_any_set)(
            store, *idx_it ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
            store, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
            store, *idx_it, node_set_1b_id ) );

        ASSERT_TRUE(  ::NS(NodeStore_can_node_be_selected_by_set)(
            store, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !::NS(NodeStore_can_node_be_selected_by_set)(
            store, *idx_it, node_set_1b_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_any_set)(
            store, *idx_it ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_set)(
            store, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_set)(
            store, *idx_it, node_set_1b_id ) );
    }

    /* --------------------------------------------------------------------- */
    /* Add another node_set for arch_ids[ 1 ]: */

     node_set_t* ptr_node_set_2a = ::NS(TestNodeSetBase_create)( store );
    ASSERT_TRUE( ptr_node_set_2a != nullptr );

    ASSERT_TRUE( ::NS(NodeSet_get_ptr_node_store)( ptr_node_set_2a ) != nullptr );
    ASSERT_TRUE( ::NS(NodeSet_get_ptr_node_store)( ptr_node_set_2a ) == store );

    /* ... and add it to the store */

    node_set_id_t const node_set_2a_id =
        ::NS(NodeStore_add_node_set)( store, ptr_node_set_2a );

    ASSERT_TRUE( node_set_2a_id != ::NS(NODE_ILLEGAL_NODE_SET_ID) );
    ASSERT_TRUE( ::NS(NodeStore_has_node_set)( store, node_set_2a_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_node_sets)( store ) == size_t{ 3 } );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_set_base)(
        store, node_set_2a_id ) == ptr_node_set_2a );

    ASSERT_TRUE( ::NS(NodeSet_get_num_nodes)(
        ptr_node_set_2a ) == size_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeSet_get_min_node_index)(
        ptr_node_set_2a ) == ::NS(NODE_UNDEFINED_INDEX) );

    ASSERT_TRUE( ::NS(NodeSet_get_max_node_index)(
        ptr_node_set_2a ) == ::NS(NODE_UNDEFINED_INDEX) );

    /* --------------------------------------------------------------------- */
    /* Attach all nodes from arch_ids[ 1 ] to node_set_1a_id: */

    status = ::NS(NodeStore_get_node_indices_for_architecture)(
        store, NUM_NODES, node_indices.data(), arch_ids[ 1 ], &cmp_num_nodes );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( cmp_num_nodes == ::NS(NodeStore_get_num_nodes)(
        store, arch_ids[ 1 ] ) );

    idx_it  = node_indices.begin();
    idx_end = node_indices.begin();
    std::advance( idx_end, cmp_num_nodes );

    for( ; idx_it != idx_end ; ++idx_it )
    {
        ASSERT_TRUE( !::NS(NodeStore_is_node_attached_to_any_set)(
            store, *idx_it ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_any_set)(
            store, *idx_it ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_any_set)(
            store, *idx_it ) );

        status = ::NS(NodeStore_attach_node_to_set)(
            store, *idx_it, node_set_2a_id );

        ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
        ASSERT_TRUE( ::NS(NodeStore_is_node_attached_to_any_set)(
            store, *idx_it ) );

        ASSERT_TRUE( ::NS(NodeStore_is_node_attached_to_set)(
            store, *idx_it, node_set_2a_id ) );

        ASSERT_TRUE( ::NS(NodeStore_can_node_be_selected_by_set)(
            store, *idx_it, node_set_2a_id ) );
    }

    ASSERT_TRUE( ::NS(NodeSet_get_num_nodes)( ptr_node_set_2a ) ==
        cmp_num_nodes );

    ASSERT_TRUE( ::NS(NodeSet_get_min_node_index)(
        ptr_node_set_2a ) == node_indices.front() );

    ASSERT_TRUE( ::NS(NodeSet_get_max_node_index)(
        ptr_node_set_2a ) == node_indices.at( cmp_num_nodes - 1 ) );

    /* --------------------------------------------------------------------- */
    /* Add another node_set for arch_ids[ 1 ]: */

    node_set_t* ptr_node_set_2b = ::NS(TestNodeSetBase_create)( store );
    ASSERT_TRUE( ptr_node_set_2b != nullptr );

    ASSERT_TRUE( ::NS(NodeSet_get_ptr_node_store)( ptr_node_set_2b ) != nullptr );
    ASSERT_TRUE( ::NS(NodeSet_get_ptr_node_store)( ptr_node_set_2b ) == store );

    /* ... and add it to the store */

    node_set_id_t const node_set_2b_id =
        ::NS(NodeStore_add_node_set)( store, ptr_node_set_2b );

    ASSERT_TRUE( node_set_2b_id != ::NS(NODE_ILLEGAL_NODE_SET_ID) );
    ASSERT_TRUE( ::NS(NodeStore_has_node_set)( store, node_set_2b_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_node_sets)( store ) == size_t{ 4 } );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_set_base)(
        store, node_set_2b_id ) == ptr_node_set_2b );

    ASSERT_TRUE( ::NS(NodeSet_get_num_nodes)(
        ptr_node_set_2b ) == size_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeSet_get_min_node_index)(
        ptr_node_set_2b ) == ::NS(NODE_UNDEFINED_INDEX) );

    ASSERT_TRUE( ::NS(NodeSet_get_max_node_index)(
        ptr_node_set_2b ) == ::NS(NODE_UNDEFINED_INDEX) );

    /* --------------------------------------------------------------------- */
    /* Attach all nodes from arch_ids[ 1 ] to node_set_1a_id: */

    status = ::NS(NodeStore_get_node_indices_for_architecture)(
        store, NUM_NODES, node_indices.data(), arch_ids[ 1 ], &cmp_num_nodes );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( cmp_num_nodes == ::NS(NodeStore_get_num_nodes)(
        store, arch_ids[ 1 ] ) );

    idx_it  = node_indices.begin();
    idx_end = node_indices.begin();
    std::advance( idx_end, cmp_num_nodes );

    for( ; idx_it != idx_end ; ++idx_it )
    {
        /* Note: this time, the node has already been selected by
         * node_set_2a_id: */

        ASSERT_TRUE(  ::NS(NodeStore_is_node_attached_to_any_set)(
            store, *idx_it ) );

        ASSERT_TRUE(  ::NS(NodeStore_is_node_attached_to_set)(
            store, *idx_it, node_set_2a_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_any_set)(
            store, *idx_it ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_any_set)(
            store, *idx_it ) );

        status = ::NS(NodeStore_attach_node_to_set)(
            store, *idx_it, node_set_2b_id );

        ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

        ASSERT_TRUE( ::NS(NodeStore_is_node_attached_to_any_set)(
            store, *idx_it ) );

        ASSERT_TRUE( ::NS(NodeStore_is_node_attached_to_set)(
            store, *idx_it, node_set_2b_id ) );

        ASSERT_TRUE( ::NS(NodeStore_can_node_be_selected_by_set)(
            store, *idx_it, node_set_2b_id ) );
    }

    ASSERT_TRUE( ::NS(NodeSet_get_num_nodes)(
        ptr_node_set_2b ) == cmp_num_nodes );

    ASSERT_TRUE( ::NS(NodeSet_get_min_node_index)(
        ptr_node_set_2b ) == node_indices.front() );

    ASSERT_TRUE( ::NS(NodeSet_get_max_node_index)(
        ptr_node_set_2b ) == node_indices.at( cmp_num_nodes - 1 ) );

    /* Create another node_set and assign all assignable nodes from
     * arch_ids[ 2 ], arch_ids[ 3 ], arch_ids[ 4 ] : */

    node_set_t* ptr_node_set_3 = ::NS(TestNodeSetBase_create)( store );
    ASSERT_TRUE( ptr_node_set_3 != nullptr );

    ASSERT_TRUE( ::NS(NodeSet_get_ptr_node_store)(
        ptr_node_set_3 ) != nullptr );

    ASSERT_TRUE( ::NS(NodeSet_get_ptr_node_store)( ptr_node_set_3 ) == store );

    /* ... and add it to the store */

    node_set_id_t const node_set_3_id =
        ::NS(NodeStore_add_node_set)( store, ptr_node_set_3 );

    ASSERT_TRUE( node_set_3_id != ::NS(NODE_ILLEGAL_NODE_SET_ID) );
    ASSERT_TRUE( ::NS(NodeStore_has_node_set)( store, node_set_3_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_node_sets)( store ) == size_t{ 5 } );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_set_base)(
        store, node_set_3_id ) == ptr_node_set_3 );

    ASSERT_TRUE( ::NS(NodeSet_get_num_nodes)( ptr_node_set_3 ) == size_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeSet_get_min_node_index)(
        ptr_node_set_3 ) == ::NS(NODE_UNDEFINED_INDEX) );

    ASSERT_TRUE( ::NS(NodeSet_get_max_node_index)(
        ptr_node_set_3 ) == ::NS(NODE_UNDEFINED_INDEX) );

    size_t num_nodes_not_attached = size_t{ 0 };

    for( size_t ii = size_t{ 2 } ; ii < NUM_ARCHS ; ++ii )
    {
        status = ::NS(NodeStore_get_node_indices_for_architecture)(
            store, NUM_NODES, node_indices.data(),
                arch_ids[ ii ], &cmp_num_nodes );

        ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

        ASSERT_TRUE( cmp_num_nodes == ::NS(NodeStore_get_num_nodes)(
            store, arch_ids[ ii ] ) );

        ASSERT_TRUE( cmp_num_nodes > size_t{ 0 } );

        idx_it  = node_indices.begin();
        idx_end = node_indices.begin();
        std::advance( idx_end, cmp_num_nodes );

        for( ; idx_it != idx_end ; ++idx_it )
        {
            ASSERT_TRUE( *idx_it != ::NS(NODE_UNDEFINED_INDEX) );

            auto ptr_node_info = ::NS(NodeStore_get_ptr_const_node_info_base)(
                store, *idx_it );

            ASSERT_TRUE( ptr_node_info != nullptr );

            status = ::NS(NodeStore_attach_node_to_set)(
                store, *idx_it, node_set_3_id );

            ASSERT_TRUE(
                ( ( ::NS(NodeInfo_get_num_attached_sets)( ptr_node_info ) <=
                    ::NS(NodeInfo_get_max_attachement_count)(
                        ptr_node_info ) ) &&
                  ( status == ::NS(ARCH_STATUS_SUCCESS) ) &&
                  ( ::NS(NodeStore_is_node_attached_to_any_set)(
                        store, *idx_it ) ) &&
                  ( ::NS(NodeStore_is_node_attached_to_set)(
                    store, *idx_it, node_set_3_id ) ) ) ||
                ( ( ::NS(NodeInfo_get_num_attached_sets)( ptr_node_info ) ==
                    ::NS(NodeInfo_get_max_attachement_count)(
                        ptr_node_info ) ) &&
                  ( status != ::NS(ARCH_STATUS_SUCCESS) ) ) );

            if( !::NS(NodeStore_is_node_attached_to_set)(
                    store, *idx_it, node_set_3_id ) )
            {
                ++num_nodes_not_attached;
            }

            ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_any_set)(
                store, *idx_it ) );

            ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
                store, *idx_it, node_set_3_id ) );

            ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_any_set)(
                store, *idx_it ) );

            ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_set)(
                store, *idx_it, node_set_3_id ) );
        }
    }

    size_t const node_set_3_num_nodes = ::NS(NodeSet_get_num_nodes)(
        ptr_node_set_3 );

    size_t const arch_ids_2_num_nodes = ::NS(NodeStore_get_num_nodes)(
        store, arch_ids[ 2 ] );

    size_t const arch_ids_3_num_nodes = ::NS(NodeStore_get_num_nodes)(
        store, arch_ids[ 3 ] );

    size_t const arch_ids_4_num_nodes = ::NS(NodeStore_get_num_nodes)(
        store, arch_ids[ 4 ] );

    ASSERT_TRUE( ( num_nodes_not_attached + node_set_3_num_nodes )
        == ( arch_ids_2_num_nodes + arch_ids_3_num_nodes +
                arch_ids_4_num_nodes ) );

    /* Detach the first node from the first node_set */

    ASSERT_TRUE( ::NS(NodeStore_is_node_attached_to_set)(
        store, cmp_node_indices[ 0 ], node_set_1a_id ) );

    status = ::NS(NodeStore_detach_node_from_set)(
        store, cmp_node_indices[ 0 ], node_set_1a_id );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( !::NS(NodeStore_is_node_attached_to_set)(
        store, cmp_node_indices[ 0 ], node_set_1a_id ) );

    status = ::NS(NodeStore_attach_node_to_set)(
        store, cmp_node_indices[ 0 ], node_set_3_id );

    ASSERT_TRUE( ::NS(NodeStore_is_node_attached_to_set)(
        store, cmp_node_indices[ 0 ], node_set_3_id ) );

    ASSERT_TRUE( ( num_nodes_not_attached + ::NS(NodeSet_get_num_nodes)(
        ptr_node_set_3 ) )
        == ( ::NS(NodeStore_get_num_nodes)( store, arch_ids[ 2 ] ) +
             ::NS(NodeStore_get_num_nodes)( store, arch_ids[ 3 ] ) +
             ::NS(NodeStore_get_num_nodes)( store, arch_ids[ 4 ] ) +
             size_t{ 1 } ) );

    /* --------------------------------------------------------------------- */
    /* Cleanup */

    ::NS(NodeStore_delete)( store );
}

/* end: /sixtracklib/common/control/test_node_set_c99.cpp */
