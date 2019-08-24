#include "sixtracklib/common/control/node_set.hpp"

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
#include "sixtracklib/common/control/node_store.hpp"
#include "sixtracklib/testlib.hpp"

TEST( CXX_CommonControlNodeSetTests, NodeSetBaseBasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    namespace st_test = SIXTRL_CXX_NAMESPACE::tests;

    using store_t          = st::NodeStore;
    using node_set_t       = st_test::TestNodeSetBase;
    using platform_id_t    = st::node_platform_id_t;
    using size_t           = store_t::size_type;
    using arch_id_t        = store_t::arch_id_t;
    using node_index_t     = store_t::node_index_t;
    using node_set_id_t    = store_t::node_set_id_t;
    using status_t         = store_t::status_t;
    using arch_id_t        = store_t::arch_id_t;
    using ptr_node_set_t   = std::unique_ptr< node_set_t >;

    /* Create three dummy architectures to allow variation in the
     * node sets based on the arch_id parameter: */

    st::Architectures& archs = st::Architectures_get();

    static constexpr size_t NUM_ARCHS = size_t{ 5 };
    arch_id_t arch_ids[ NUM_ARCHS ] =
    {
        store_t::UNDEFINED_INDEX, store_t::UNDEFINED_INDEX,
        store_t::UNDEFINED_INDEX, store_t::UNDEFINED_INDEX,
        store_t::UNDEFINED_INDEX
    };

    status_t status = st_test::Architectures_setup(
        archs, NUM_ARCHS, arch_id_t{ 32 }, &arch_ids[ 0 ] );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    /* Create an empty store */

    store_t store;

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
        store_t::ILLEGAL_PLATFORM_ID, store_t::ILLEGAL_PLATFORM_ID,
        store_t::ILLEGAL_PLATFORM_ID, store_t::ILLEGAL_PLATFORM_ID,
        platform_id_t{ 42 }, store_t::ILLEGAL_PLATFORM_ID
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
               store_t::UNDEFINED_INDEX );

    status = st_test::TestNodeInfo_add_to_node_store( store, NUM_NODES,
        &nodes_arch_ids[ 0 ], &nodes_platform_ids[ 0 ],
            &nodes_max_attach_cnt[ 0 ], &nodes_max_selection_cnt[ 0 ],
                &cmp_node_indices[ 0 ] );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    SIXTRL_ASSERT( store.totalNumNodes() == NUM_NODES );

    std::vector< node_index_t > node_indices(
        NUM_NODES, store_t::UNDEFINED_INDEX );

    size_t cmp_num_nodes = size_t{ 0 };
    status = store.nodeIndices(
        node_indices.begin(), node_indices.end(), &cmp_num_nodes );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( cmp_num_nodes == NUM_NODES );
    ASSERT_TRUE( std::equal( node_indices.begin(), node_indices.end(),
                             &cmp_node_indices[ 0 ] ) );

    SIXTRL_ASSERT( store.hasArchitecture( arch_ids[ 0 ] ) );
    SIXTRL_ASSERT( store.hasArchitecture( arch_ids[ 1 ] ) );
    SIXTRL_ASSERT( store.hasArchitecture( arch_ids[ 2 ] ) );
    SIXTRL_ASSERT( store.hasArchitecture( arch_ids[ 3 ] ) );
    SIXTRL_ASSERT( store.hasArchitecture( arch_ids[ 4 ] ) );

    SIXTRL_ASSERT( store.numNodes( arch_ids[ 0 ] ) == size_t{ 3 } );
    SIXTRL_ASSERT( store.numNodes( arch_ids[ 1 ] ) == size_t{ 2 } );
    SIXTRL_ASSERT( store.numNodes( arch_ids[ 2 ] ) == size_t{ 1 } );
    SIXTRL_ASSERT( store.numNodes( arch_ids[ 3 ] ) == size_t{ 4 } );
    SIXTRL_ASSERT( store.numNodes( arch_ids[ 4 ] ) == size_t{ 2 } );

    for( auto const node_index : node_indices )
    {
        auto ptr_node_info = store.ptrNodeInfoBase( node_index );
        ASSERT_TRUE( ptr_node_info != nullptr );

        SIXTRL_ASSERT( !store.isNodeAttachedToAnySet( node_index ) );
        SIXTRL_ASSERT( !store.isNodeSelectedByAnySet( node_index ) );
        SIXTRL_ASSERT( !store.isNodeDefaultForAnySet( node_index ) );
    }

    /* --------------------------------------------------------------------- */
    /* Verify initial state - no node sets available */

    ASSERT_TRUE( !store.hasNodeSets() );
    ASSERT_TRUE(  store.numNodeSets() == size_t{ 0 } );

    /* create a new node set ... */

    ptr_node_set_t ptr_node_set( new node_set_t( store ) );
    node_set_t* ptr_node_set_1a = ptr_node_set.get();
    ptr_node_set_1a->setMaxNumSelectableNodes( size_t{ 1 } );

    ASSERT_TRUE( ptr_node_set.get() != nullptr );
    ASSERT_TRUE( ptr_node_set->ptrNodeStore() == &store );

    /* ... and add it to the store */

    node_set_id_t const node_set_1a_id = store.addNodeSet(
        std::move( ptr_node_set ) );

    ASSERT_TRUE( node_set_1a_id != store_t::ILLEGAL_NODE_SET_ID );
    ASSERT_TRUE( ptr_node_set.get() == nullptr );
    ASSERT_TRUE( ptr_node_set_1a   != nullptr );
    ASSERT_TRUE( store.hasNodeSet( node_set_1a_id ) );
    ASSERT_TRUE( store.numNodeSets() == size_t{ 1 } );
    ASSERT_TRUE( store.ptrNodeSetBase( node_set_1a_id ) == ptr_node_set_1a );
    ASSERT_TRUE( ptr_node_set_1a->nodeSetId() == node_set_1a_id );

    ASSERT_TRUE( ptr_node_set_1a->numNodes() == size_t{ 0 } );
    ASSERT_TRUE( ptr_node_set_1a->minNodeIndex() == store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( ptr_node_set_1a->maxNodeIndex() == store_t::UNDEFINED_INDEX );

    /* there are still none nodes attached to this node set */

    for( auto const idx : node_indices )
    {
        auto ptr_node_info = store.ptrNodeInfoBase( idx );
        ASSERT_TRUE( ptr_node_info != nullptr );

        ASSERT_TRUE( !store.isNodeAttachedToAnySet( idx ) );
        ASSERT_TRUE( !store.isNodeAttachedToSet( idx, node_set_1a_id ) );

        ASSERT_TRUE( !store.isNodeSelectedByAnySet( idx ) );
        ASSERT_TRUE( !store.isNodeSelectedBySet( idx, node_set_1a_id ) );

        ASSERT_TRUE( !store.isNodeDefaultForAnySet( idx ) );
        ASSERT_TRUE( !store.isNodeDefaultForSet( idx, node_set_1a_id ) );
    }

    /* --------------------------------------------------------------------- */
    /* Attach all nodes from arch_ids[ 0 ] to node_set_1a_id: */

    status = store.nodeIndices( node_indices.begin(), node_indices.end(),
        arch_ids[ 0 ], &cmp_num_nodes );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( cmp_num_nodes == store.numNodes( arch_ids[ 0 ] ) );

    status = store.attachAllArchitectureNodesToSet(
        arch_ids[ 0 ], node_set_1a_id );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( ptr_node_set_1a->numNodes() ==
                 store.numNodes( arch_ids[ 0 ] ) );

    ASSERT_TRUE( store.numNodes( node_set_1a_id ) ==
                 store.numNodes( arch_ids[ 0 ] ) );

    auto idx_it  = node_indices.begin();
    auto idx_end = node_indices.begin();
    std::advance( idx_end, store.numNodes( arch_ids[ 0 ] ) );

    for( ; idx_it != idx_end ; ++idx_it )
    {
        auto ptr_node_info = store.ptrNodeInfoBase( *idx_it );
        ASSERT_TRUE( ptr_node_info != nullptr );

        ASSERT_TRUE( store.isNodeAttachedToAnySet( *idx_it ) );
        ASSERT_TRUE( store.isNodeAttachedToSet( *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !store.isNodeSelectedByAnySet( *idx_it ) );
        ASSERT_TRUE( !store.isNodeSelectedBySet( *idx_it, node_set_1a_id ) );
        ASSERT_TRUE(  store.canNodeBeSelectedBySet( *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !store.isNodeDefaultForAnySet( *idx_it ) );
        ASSERT_TRUE( !store.isNodeDefaultForSet( *idx_it, node_set_1a_id ) );
    }

    /* --------------------------------------------------------------------- */
    /* Add another node_set for arch_ids[ 0 ]: */

    ptr_node_set.reset( new node_set_t( store ) );
    node_set_t* ptr_node_set_1b = ptr_node_set.get();

    ptr_node_set_1b->setMaxNumSelectableNodes( size_t{ 1 } );

    ASSERT_TRUE( ptr_node_set.get() != nullptr );
    ASSERT_TRUE( ptr_node_set->ptrNodeStore() == &store );

    /* ... and add it to the store */

    node_set_id_t const node_set_1b_id = store.addNodeSet(
        std::move( ptr_node_set ) );

    ASSERT_TRUE( node_set_1b_id != store_t::ILLEGAL_NODE_SET_ID );
    ASSERT_TRUE( ptr_node_set.get() == nullptr );
    ASSERT_TRUE( ptr_node_set_1b   != nullptr );
    ASSERT_TRUE( store.hasNodeSet( node_set_1b_id ) );
    ASSERT_TRUE( store.numNodeSets() == size_t{ 2 } );
    ASSERT_TRUE( store.ptrNodeSetBase( node_set_1b_id ) == ptr_node_set_1b );
    ASSERT_TRUE( ptr_node_set_1b->nodeSetId() == node_set_1b_id );

    ASSERT_TRUE( ptr_node_set_1b->numNodes() == size_t{ 0 } );
    ASSERT_TRUE( ptr_node_set_1b->minNodeIndex() == store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( ptr_node_set_1b->maxNodeIndex() == store_t::UNDEFINED_INDEX );

    /* the nodes of arch_ids[ 0 ] have a max attachement cnt of 1; thus,it
     * should not be possible to attach any of these nodes to node_set_1b_id: */

    status = store.attachAllArchitectureNodesToSet(
        arch_ids[ 0 ], node_set_1b_id );

    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );

    idx_it = node_indices.begin();

    for( ; idx_it != idx_end ; ++idx_it )
    {
        auto ptr_node_info = store.ptrNodeInfoBase( *idx_it );
        ASSERT_TRUE( ptr_node_info != nullptr );

        ASSERT_TRUE(  store.isNodeAttachedToAnySet( *idx_it ) );
        ASSERT_TRUE(  store.isNodeAttachedToSet( *idx_it, node_set_1a_id ) );
        ASSERT_TRUE( !store.isNodeAttachedToSet( *idx_it, node_set_1b_id ) );

        ASSERT_TRUE( !store.isNodeSelectedByAnySet( *idx_it ) );
        ASSERT_TRUE( !store.isNodeSelectedBySet( *idx_it, node_set_1a_id ) );
        ASSERT_TRUE( !store.isNodeSelectedBySet( *idx_it, node_set_1b_id ) );
        ASSERT_TRUE(  store.canNodeBeSelectedBySet( *idx_it, node_set_1a_id ) );
        ASSERT_TRUE( !store.canNodeBeSelectedBySet( *idx_it, node_set_1b_id ) );

        ASSERT_TRUE( !store.isNodeDefaultForAnySet( *idx_it ) );
        ASSERT_TRUE( !store.isNodeDefaultForSet( *idx_it, node_set_1a_id ) );
        ASSERT_TRUE( !store.isNodeDefaultForSet( *idx_it, node_set_1b_id ) );
    }

    /* --------------------------------------------------------------------- */
    /* Add another node_set for arch_ids[ 1 ]: */

    ptr_node_set.reset( new node_set_t( store ) );
    node_set_t* ptr_node_set_2a = ptr_node_set.get();

    ptr_node_set_2a->setMaxNumSelectableNodes( size_t{ 1 } );

    ASSERT_TRUE( ptr_node_set.get() != nullptr );
    ASSERT_TRUE( ptr_node_set->ptrNodeStore() == &store );

    /* ... and add it to the store */

    node_set_id_t const node_set_2a_id = store.addNodeSet(
        std::move( ptr_node_set ) );

    ASSERT_TRUE( node_set_2a_id != store_t::ILLEGAL_NODE_SET_ID );
    ASSERT_TRUE( ptr_node_set.get() == nullptr );
    ASSERT_TRUE( ptr_node_set_2a   != nullptr );
    ASSERT_TRUE( store.hasNodeSet( node_set_2a_id ) );
    ASSERT_TRUE( store.numNodeSets() == size_t{ 3 } );
    ASSERT_TRUE( store.ptrNodeSetBase( node_set_2a_id ) == ptr_node_set_2a );
    ASSERT_TRUE( ptr_node_set_2a->nodeSetId() == node_set_2a_id );

    ASSERT_TRUE( ptr_node_set_2a->numNodes() == size_t{ 0 } );
    ASSERT_TRUE( ptr_node_set_2a->minNodeIndex() == store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( ptr_node_set_2a->maxNodeIndex() == store_t::UNDEFINED_INDEX );

    /* --------------------------------------------------------------------- */
    /* Attach all nodes from arch_ids[ 1 ] to node_set_1a_id: */

    status = store.nodeIndices( node_indices.begin(), node_indices.end(),
        arch_ids[ 1 ], &cmp_num_nodes );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( cmp_num_nodes == store.numNodes( arch_ids[ 1 ] ) );

    idx_it  = node_indices.begin();
    idx_end = node_indices.begin();
    std::advance( idx_end, cmp_num_nodes );

    for( ; idx_it != idx_end ; ++idx_it )
    {
        ASSERT_TRUE( !store.isNodeAttachedToAnySet( *idx_it ) );
        ASSERT_TRUE( !store.isNodeSelectedByAnySet( *idx_it ) );
        ASSERT_TRUE( !store.isNodeDefaultForAnySet( *idx_it ) );

        status = store.attachNodeToSet( *idx_it, node_set_2a_id );
        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
        ASSERT_TRUE( store.isNodeAttachedToAnySet( *idx_it ) );
        ASSERT_TRUE( store.isNodeAttachedToSet( *idx_it, node_set_2a_id ) );
        ASSERT_TRUE( store.canNodeBeSelectedBySet( *idx_it, node_set_2a_id ) );
    }

    ASSERT_TRUE( ptr_node_set_2a->numNodes() == cmp_num_nodes );
    ASSERT_TRUE( ptr_node_set_2a->minNodeIndex() == node_indices.front() );
    ASSERT_TRUE( ptr_node_set_2a->maxNodeIndex() ==
                 node_indices.at( cmp_num_nodes - 1 ) );

    /* --------------------------------------------------------------------- */
    /* Add another node_set for arch_ids[ 1 ]: */

    ptr_node_set.reset( new node_set_t( store ) );
    node_set_t* ptr_node_set_2b = ptr_node_set.get();

    ptr_node_set_2b->setMaxNumSelectableNodes( size_t{ 1 } );

    ASSERT_TRUE( ptr_node_set.get() != nullptr );
    ASSERT_TRUE( ptr_node_set->ptrNodeStore() == &store );

    /* ... and add it to the store */

    node_set_id_t const node_set_2b_id = store.addNodeSet(
        std::move( ptr_node_set ) );

    ASSERT_TRUE( node_set_2b_id != store_t::ILLEGAL_NODE_SET_ID );
    ASSERT_TRUE( ptr_node_set.get() == nullptr );
    ASSERT_TRUE( ptr_node_set_2b   != nullptr );
    ASSERT_TRUE( store.hasNodeSet( node_set_2b_id ) );
    ASSERT_TRUE( store.numNodeSets() == size_t{ 4 } );
    ASSERT_TRUE( store.ptrNodeSetBase( node_set_2b_id ) == ptr_node_set_2b );
    ASSERT_TRUE( ptr_node_set_2b->nodeSetId() == node_set_2b_id );

    ASSERT_TRUE( ptr_node_set_2b->numNodes() == size_t{ 0 } );
    ASSERT_TRUE( ptr_node_set_2b->minNodeIndex() == store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( ptr_node_set_2b->maxNodeIndex() == store_t::UNDEFINED_INDEX );

    /* --------------------------------------------------------------------- */
    /* Attach all nodes from arch_ids[ 1 ] to node_set_1a_id: */

    status = store.nodeIndices( node_indices.begin(), node_indices.end(),
        arch_ids[ 1 ], &cmp_num_nodes );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( cmp_num_nodes == store.numNodes( arch_ids[ 1 ] ) );

    idx_it  = node_indices.begin();
    idx_end = node_indices.begin();
    std::advance( idx_end, cmp_num_nodes );

    for( ; idx_it != idx_end ; ++idx_it )
    {
        /* Note: this time, the node has already been selected by
         * node_set_2a_id: */

        ASSERT_TRUE(  store.isNodeAttachedToAnySet( *idx_it ) );
        ASSERT_TRUE(  store.isNodeAttachedToSet( *idx_it, node_set_2a_id ) );
        ASSERT_TRUE( !store.isNodeSelectedByAnySet( *idx_it ) );
        ASSERT_TRUE( !store.isNodeDefaultForAnySet( *idx_it ) );

        status = store.attachNodeToSet( *idx_it, node_set_2b_id );
        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
        ASSERT_TRUE( store.isNodeAttachedToAnySet( *idx_it ) );
        ASSERT_TRUE( store.isNodeAttachedToSet( *idx_it, node_set_2b_id ) );
        ASSERT_TRUE( store.canNodeBeSelectedBySet( *idx_it, node_set_2b_id ) );
    }

    ASSERT_TRUE( ptr_node_set_2b->numNodes() == cmp_num_nodes );
    ASSERT_TRUE( ptr_node_set_2b->minNodeIndex() == node_indices.front() );
    ASSERT_TRUE( ptr_node_set_2b->maxNodeIndex() ==
                 node_indices.at( cmp_num_nodes - 1 ) );

    /* Create another node_set and assign all assignable nodes from
     * arch_ids[ 2 ], arch_ids[ 3 ], arch_ids[ 4 ] : */

    ptr_node_set.reset( new node_set_t( store ) );
    node_set_t* ptr_node_set_3 = ptr_node_set.get();

    ptr_node_set_3->setMaxNumSelectableNodes( size_t{ 1 } );

    ASSERT_TRUE( ptr_node_set.get() != nullptr );
    ASSERT_TRUE( ptr_node_set->ptrNodeStore() == &store );

    /* add it to the store */

    node_set_id_t const node_set_3_id = store.addNodeSet(
        std::move( ptr_node_set ) );

    ASSERT_TRUE( node_set_3_id != store_t::ILLEGAL_NODE_SET_ID );
    ASSERT_TRUE( ptr_node_set.get() == nullptr );
    ASSERT_TRUE( ptr_node_set_3 != nullptr );
    ASSERT_TRUE( store.hasNodeSet( node_set_3_id ) );
    ASSERT_TRUE( store.numNodeSets() == size_t{ 5 } );
    ASSERT_TRUE( store.ptrNodeSetBase( node_set_3_id ) == ptr_node_set_3 );
    ASSERT_TRUE( ptr_node_set_3->nodeSetId() == node_set_3_id );

    ASSERT_TRUE( ptr_node_set_3->numNodes() == size_t{ 0 } );
    ASSERT_TRUE( ptr_node_set_3->minNodeIndex() == store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( ptr_node_set_3->maxNodeIndex() == store_t::UNDEFINED_INDEX );

    size_t num_nodes_not_attached = size_t{ 0 };

    for( size_t ii = size_t{ 2 } ; ii < NUM_ARCHS ; ++ii )
    {
        status = store.nodeIndices( node_indices.begin(), node_indices.end(),
            arch_ids[ ii ], &cmp_num_nodes );

        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
        ASSERT_TRUE( cmp_num_nodes == store.numNodes( arch_ids[ ii ] ) );
        ASSERT_TRUE( cmp_num_nodes > size_t{ 0 } );

        idx_it  = node_indices.begin();
        idx_end = node_indices.begin();
        std::advance( idx_end, cmp_num_nodes );

        for( ; idx_it != idx_end ; ++idx_it )
        {
            ASSERT_TRUE( *idx_it != store_t::UNDEFINED_INDEX );

            auto ptr_node_info = store.ptrNodeInfoBase( *idx_it );
            ASSERT_TRUE( ptr_node_info != nullptr );

            status = store.attachNodeToSet( *idx_it, node_set_3_id );

            ASSERT_TRUE( ( ( ptr_node_info->numAttachedSets() <=
                             ptr_node_info->maxAttachementCount() ) &&
                           ( status == st::ARCH_STATUS_SUCCESS ) &&
                           ( store.isNodeAttachedToAnySet( *idx_it ) ) &&
                           ( store.isNodeAttachedToSet(
                            *idx_it, node_set_3_id ) ) ) ||
                         ( ( ptr_node_info->numAttachedSets() ==
                             ptr_node_info->maxAttachementCount() ) &&
                           ( status != st::ARCH_STATUS_SUCCESS ) ) );

            if( !store.isNodeAttachedToSet( *idx_it, node_set_3_id ) )
            {
                ++num_nodes_not_attached;
            }

            ASSERT_TRUE( !store.isNodeSelectedByAnySet( *idx_it ) );
            ASSERT_TRUE( !store.isNodeSelectedBySet(
                *idx_it, node_set_3_id ) );

            ASSERT_TRUE( !store.isNodeDefaultForAnySet( *idx_it ) );
            ASSERT_TRUE( !store.isNodeDefaultForSet(
                *idx_it, node_set_3_id ) );
        }
    }

    size_t const node_set_3_num_nodes = ptr_node_set_3->numNodes();
    size_t const arch_ids_2_num_nodes = store.numNodes( arch_ids[ 2 ] );
    size_t const arch_ids_3_num_nodes = store.numNodes( arch_ids[ 3 ] );
    size_t const arch_ids_4_num_nodes = store.numNodes( arch_ids[ 4 ] );

    ASSERT_TRUE( ( num_nodes_not_attached + node_set_3_num_nodes )
        == ( arch_ids_2_num_nodes + arch_ids_3_num_nodes + arch_ids_4_num_nodes ) );

    /* Detach the first node from the first node_set */

    ASSERT_TRUE( store.isNodeAttachedToSet(
        cmp_node_indices[ 0 ], node_set_1a_id ) );

    status = store.detachNodeFromSet( cmp_node_indices[ 0 ], node_set_1a_id );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( !store.isNodeAttachedToSet(
        cmp_node_indices[ 0 ], node_set_1a_id  ) );

    status = store.attachNodeToSet( cmp_node_indices[ 0 ], node_set_3_id );
    ASSERT_TRUE( store.isNodeAttachedToSet(
        cmp_node_indices[ 0 ], node_set_3_id ) );

    ASSERT_TRUE( ( num_nodes_not_attached + ptr_node_set_3->numNodes() )
        == ( store.numNodes( arch_ids[ 2 ] ) + store.numNodes( arch_ids[ 3 ] ) +
             store.numNodes( arch_ids[ 4 ] ) + size_t{ 1 } ) );
}

TEST( CXX_CommonControlNodeSetTests, NodeSetBaseBasicUsageExtLock )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    namespace st_test = SIXTRL_CXX_NAMESPACE::tests;

    using store_t          = st::NodeStore;
    using node_set_t       = st_test::TestNodeSetBase;
    using platform_id_t    = st::node_platform_id_t;
    using size_t           = store_t::size_type;
    using arch_id_t        = store_t::arch_id_t;
    using node_index_t     = store_t::node_index_t;
    using node_set_id_t    = store_t::node_set_id_t;
    using status_t         = store_t::status_t;
    using ptr_node_set_t   = std::unique_ptr< node_set_t >;

    /* Create three dummy architectures to allow variation in the
     * node sets based on the arch_id parameter: */

    st::Architectures& archs = st::Architectures_get();

    static constexpr size_t NUM_ARCHS = size_t{ 5 };
    arch_id_t arch_ids[ NUM_ARCHS ] =
    {
        store_t::UNDEFINED_INDEX, store_t::UNDEFINED_INDEX,
        store_t::UNDEFINED_INDEX, store_t::UNDEFINED_INDEX,
        store_t::UNDEFINED_INDEX
    };

    status_t status = st_test::Architectures_setup(
        archs, NUM_ARCHS, arch_id_t{ 32 }, &arch_ids[ 0 ] );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    /* Create an empty store */

    store_t store;

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
        store_t::ILLEGAL_PLATFORM_ID, store_t::ILLEGAL_PLATFORM_ID,
        store_t::ILLEGAL_PLATFORM_ID, store_t::ILLEGAL_PLATFORM_ID,
        platform_id_t{ 42 }, store_t::ILLEGAL_PLATFORM_ID
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
               store_t::UNDEFINED_INDEX );

    status = st_test::TestNodeInfo_add_to_node_store( store, NUM_NODES,
        &nodes_arch_ids[ 0 ], &nodes_platform_ids[ 0 ],
            &nodes_max_attach_cnt[ 0 ], &nodes_max_selection_cnt[ 0 ],
                &cmp_node_indices[ 0 ] );

    store_t::lock_t const lock( *store.lockable() );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    SIXTRL_ASSERT( store.totalNumNodes( lock ) == NUM_NODES );

    std::vector< node_index_t > node_indices(
        NUM_NODES, store_t::UNDEFINED_INDEX );

    size_t cmp_num_nodes = size_t{ 0 };
    status = store.nodeIndices( lock, node_indices.begin(),
        node_indices.end(), &cmp_num_nodes );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( cmp_num_nodes == NUM_NODES );
    ASSERT_TRUE( std::equal( node_indices.begin(), node_indices.end(),
                             &cmp_node_indices[ 0 ] ) );

    SIXTRL_ASSERT( store.hasArchitecture( lock, arch_ids[ 0 ] ) );
    SIXTRL_ASSERT( store.hasArchitecture( lock, arch_ids[ 1 ] ) );
    SIXTRL_ASSERT( store.hasArchitecture( lock, arch_ids[ 2 ] ) );
    SIXTRL_ASSERT( store.hasArchitecture( lock, arch_ids[ 3 ] ) );
    SIXTRL_ASSERT( store.hasArchitecture( lock, arch_ids[ 4 ] ) );

    SIXTRL_ASSERT( store.numNodes( lock, arch_ids[ 0 ] ) == size_t{ 3 } );
    SIXTRL_ASSERT( store.numNodes( lock, arch_ids[ 1 ] ) == size_t{ 2 } );
    SIXTRL_ASSERT( store.numNodes( lock, arch_ids[ 2 ] ) == size_t{ 1 } );
    SIXTRL_ASSERT( store.numNodes( lock, arch_ids[ 3 ] ) == size_t{ 4 } );
    SIXTRL_ASSERT( store.numNodes( lock, arch_ids[ 4 ] ) == size_t{ 2 } );

    for( auto const node_index : node_indices )
    {
        auto ptr_node_info = store.ptrNodeInfoBase( lock, node_index );
        ASSERT_TRUE( ptr_node_info != nullptr );

        SIXTRL_ASSERT( !store.isNodeAttachedToAnySet( lock, node_index ) );
        SIXTRL_ASSERT( !store.isNodeSelectedByAnySet( lock, node_index ) );
        SIXTRL_ASSERT( !store.isNodeDefaultForAnySet( lock, node_index ) );
    }

    /* --------------------------------------------------------------------- */
    /* Verify initial state - no node sets available */

    ASSERT_TRUE( !store.hasNodeSets( lock ) );
    ASSERT_TRUE(  store.numNodeSets( lock ) == size_t{ 0 } );

    /* create a new node set ... */

    ptr_node_set_t ptr_node_set( new node_set_t( store ) );
    node_set_t* ptr_node_set_1a = ptr_node_set.get();

    ptr_node_set_1a->setMaxNumSelectableNodes( lock, size_t{ 1 } );

    ASSERT_TRUE( ptr_node_set.get() != nullptr );
    ASSERT_TRUE( ptr_node_set->ptrNodeStore() == &store );

    /* ... and add it to the store */

    node_set_id_t const node_set_1a_id = store.addNodeSet(
        lock, std::move( ptr_node_set ) );

    ASSERT_TRUE( node_set_1a_id != store_t::ILLEGAL_NODE_SET_ID );
    ASSERT_TRUE( ptr_node_set.get() == nullptr );
    ASSERT_TRUE( ptr_node_set_1a   != nullptr );
    ASSERT_TRUE( store.hasNodeSet( lock, node_set_1a_id ) );
    ASSERT_TRUE( store.numNodeSets( lock ) == size_t{ 1 } );
    ASSERT_TRUE( store.ptrNodeSetBase( lock, node_set_1a_id ) ==
                 ptr_node_set_1a );
    ASSERT_TRUE( ptr_node_set_1a->nodeSetId() == node_set_1a_id );

    ASSERT_TRUE( ptr_node_set_1a->numNodes( lock ) == size_t{ 0 } );

    ASSERT_TRUE( ptr_node_set_1a->minNodeIndex( lock ) ==
                 store_t::UNDEFINED_INDEX );

    ASSERT_TRUE( ptr_node_set_1a->maxNodeIndex( lock ) ==
                 store_t::UNDEFINED_INDEX );

    ASSERT_TRUE( ptr_node_set_1a->nodeIndicesBegin( lock ) == nullptr );
    ASSERT_TRUE( ptr_node_set_1a->nodeIndicesEnd( lock ) == nullptr );

    /* there are still none nodes attached to this node set */

    for( auto const idx : node_indices )
    {
        auto ptr_node_info = store.ptrNodeInfoBase( lock, idx );
        ASSERT_TRUE( ptr_node_info != nullptr );

        ASSERT_TRUE( !store.isNodeAttachedToAnySet( lock, idx ) );
        ASSERT_TRUE( !store.isNodeAttachedToSet( lock, idx, node_set_1a_id ) );

        ASSERT_TRUE( !store.isNodeSelectedByAnySet( lock, idx ) );
        ASSERT_TRUE( !store.isNodeSelectedBySet( lock, idx, node_set_1a_id ) );

        ASSERT_TRUE( !store.isNodeDefaultForAnySet( lock, idx ) );
        ASSERT_TRUE( !store.isNodeDefaultForSet( lock, idx, node_set_1a_id ) );
    }

    /* --------------------------------------------------------------------- */
    /* Attach all nodes from arch_ids[ 0 ] to node_set_1a_id: */

    status = store.nodeIndices( lock, node_indices.begin(), node_indices.end(),
        arch_ids[ 0 ], &cmp_num_nodes );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( cmp_num_nodes == store.numNodes( lock, arch_ids[ 0 ] ) );

    status = store.attachAllArchitectureNodesToSet(
        lock, arch_ids[ 0 ], node_set_1a_id );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( ptr_node_set_1a->numNodes( lock ) ==
                 store.numNodes( lock, arch_ids[ 0 ] ) );

    ASSERT_TRUE( store.numNodes( lock, node_set_1a_id ) ==
                 store.numNodes( lock, arch_ids[ 0 ] ) );

    ASSERT_TRUE( std::equal( ptr_node_set_1a->nodeIndicesBegin( lock ),
                             ptr_node_set_1a->nodeIndicesEnd( lock ),
                             node_indices.begin() ) );

    ASSERT_TRUE( std::equal(
        store.attachedNodeIndicesBegin( lock, node_set_1a_id ),
        store.attachedNodeIndicesEnd( lock, node_set_1a_id ),
        node_indices.begin() ) );

    ASSERT_TRUE( store.selectedNodeIndicesBegin( lock, node_set_1a_id ) ==
        store.selectedNodeIndicesEnd( lock, node_set_1a_id ) );

    ASSERT_TRUE( store.defaultNodeIndicesBegin( lock, node_set_1a_id ) ==
        store.defaultNodeIndicesEnd( lock, node_set_1a_id ) );

    auto idx_it  = node_indices.begin();
    auto idx_end = node_indices.begin();
    std::advance( idx_end, store.numNodes( lock, arch_ids[ 0 ] ) );

    for( ; idx_it != idx_end ; ++idx_it )
    {
        auto ptr_node_info = store.ptrNodeInfoBase( lock, *idx_it );
        ASSERT_TRUE( ptr_node_info != nullptr );

        ASSERT_TRUE( store.isNodeAttachedToAnySet( lock, *idx_it ) );
        ASSERT_TRUE( store.isNodeAttachedToSet(
            lock, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !store.isNodeSelectedByAnySet( lock, *idx_it ) );
        ASSERT_TRUE( !store.isNodeSelectedBySet(
            lock, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE(  store.canNodeBeSelectedBySet(
            lock, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !store.isNodeDefaultForAnySet( lock, *idx_it ) );
        ASSERT_TRUE( !store.isNodeDefaultForSet(
            lock, *idx_it, node_set_1a_id ) );
    }

    /* --------------------------------------------------------------------- */
    /* Add another node_set for arch_ids[ 0 ]: */

    ptr_node_set.reset( new node_set_t( store ) );
    node_set_t* ptr_node_set_1b = ptr_node_set.get();

    ptr_node_set_1b->setMaxNumSelectableNodes( lock, size_t{ 1 } );

    ASSERT_TRUE( ptr_node_set.get() != nullptr );
    ASSERT_TRUE( ptr_node_set->ptrNodeStore() == &store );

    /* ... and add it to the store */

    node_set_id_t const node_set_1b_id = store.addNodeSet(
        lock, std::move( ptr_node_set ) );

    ASSERT_TRUE( node_set_1b_id != store_t::ILLEGAL_NODE_SET_ID );
    ASSERT_TRUE( ptr_node_set.get() == nullptr );
    ASSERT_TRUE( ptr_node_set_1b   != nullptr );
    ASSERT_TRUE( store.hasNodeSet( lock, node_set_1b_id ) );
    ASSERT_TRUE( store.numNodeSets( lock ) == size_t{ 2 } );
    ASSERT_TRUE( store.ptrNodeSetBase(
        lock, node_set_1b_id ) == ptr_node_set_1b );

    ASSERT_TRUE( ptr_node_set_1b->nodeSetId() == node_set_1b_id );

    ASSERT_TRUE( ptr_node_set_1b->numNodes( lock ) == size_t{ 0 } );
    ASSERT_TRUE( ptr_node_set_1b->minNodeIndex( lock ) ==
                store_t::UNDEFINED_INDEX );

    ASSERT_TRUE( ptr_node_set_1b->maxNodeIndex( lock ) ==
                store_t::UNDEFINED_INDEX );

    ASSERT_TRUE( ptr_node_set_1b->nodeIndicesBegin( lock ) == nullptr );
    ASSERT_TRUE( ptr_node_set_1b->nodeIndicesEnd( lock ) == nullptr );

    /* the nodes of arch_ids[ 0 ] have a max attachement cnt of 1; thus,it
     * should not be possible to attach any of these nodes to node_set_1b_id: */

    status = store.attachAllArchitectureNodesToSet(
        lock, arch_ids[ 0 ], node_set_1b_id );

    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );

    idx_it = node_indices.begin();

    for( ; idx_it != idx_end ; ++idx_it )
    {
        auto ptr_node_info = store.ptrNodeInfoBase( lock, *idx_it );
        ASSERT_TRUE( ptr_node_info != nullptr );

        ASSERT_TRUE(  store.isNodeAttachedToAnySet( lock, *idx_it ) );
        ASSERT_TRUE(  store.isNodeAttachedToSet(
            lock, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !store.isNodeAttachedToSet(
            lock, *idx_it, node_set_1b_id ) );

        ASSERT_TRUE( !store.isNodeSelectedByAnySet( lock, *idx_it ) );
        ASSERT_TRUE( !store.isNodeSelectedBySet(
            lock, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !store.isNodeSelectedBySet(
            lock, *idx_it, node_set_1b_id ) );

        ASSERT_TRUE(  store.canNodeBeSelectedBySet(
            lock, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !store.canNodeBeSelectedBySet(
            lock, *idx_it, node_set_1b_id ) );

        ASSERT_TRUE( !store.isNodeDefaultForAnySet( lock, *idx_it ) );
        ASSERT_TRUE( !store.isNodeDefaultForSet(
            lock, *idx_it, node_set_1a_id ) );

        ASSERT_TRUE( !store.isNodeDefaultForSet(
            lock, *idx_it, node_set_1b_id ) );
    }

    ASSERT_TRUE( store.attachedNodeIndicesBegin( lock, node_set_1b_id ) ==
        store.attachedNodeIndicesEnd( lock, node_set_1b_id ) );

    ASSERT_TRUE( store.selectedNodeIndicesBegin( lock, node_set_1a_id ) ==
        store.selectedNodeIndicesEnd( lock, node_set_1a_id ) );

    ASSERT_TRUE( store.defaultNodeIndicesBegin( lock, node_set_1a_id ) ==
        store.defaultNodeIndicesEnd( lock, node_set_1a_id ) );

    /* --------------------------------------------------------------------- */
    /* Add another node_set for arch_ids[ 1 ]: */

    ptr_node_set.reset( new node_set_t( store ) );
    node_set_t* ptr_node_set_2a = ptr_node_set.get();

    ptr_node_set_2a->setMaxNumSelectableNodes( lock, size_t{ 1 } );

    ASSERT_TRUE( ptr_node_set.get() != nullptr );
    ASSERT_TRUE( ptr_node_set->ptrNodeStore() == &store );

    /* ... and add it to the store */

    node_set_id_t const node_set_2a_id = store.addNodeSet(
        lock, std::move( ptr_node_set ) );

    ASSERT_TRUE( node_set_2a_id != store_t::ILLEGAL_NODE_SET_ID );
    ASSERT_TRUE( ptr_node_set.get() == nullptr );
    ASSERT_TRUE( ptr_node_set_2a   != nullptr );
    ASSERT_TRUE( store.hasNodeSet( lock, node_set_2a_id ) );
    ASSERT_TRUE( store.numNodeSets( lock ) == size_t{ 3 } );

    ASSERT_TRUE( store.ptrNodeSetBase(
        lock, node_set_2a_id ) == ptr_node_set_2a );

    ASSERT_TRUE( ptr_node_set_2a->nodeSetId() == node_set_2a_id );

    ASSERT_TRUE( ptr_node_set_2a->numNodes( lock ) == size_t{ 0 } );
    ASSERT_TRUE( ptr_node_set_2a->minNodeIndex( lock ) ==
        store_t::UNDEFINED_INDEX );

    ASSERT_TRUE( ptr_node_set_2a->maxNodeIndex( lock ) ==
        store_t::UNDEFINED_INDEX );

    ASSERT_TRUE( ptr_node_set_2a->nodeIndicesBegin( lock ) == nullptr );
    ASSERT_TRUE( ptr_node_set_2a->nodeIndicesEnd( lock ) == nullptr );

    /* --------------------------------------------------------------------- */
    /* Attach all nodes from arch_ids[ 1 ] to node_set_1a_id: */

    status = store.nodeIndices( lock, node_indices.begin(), node_indices.end(),
                                    arch_ids[ 1 ], &cmp_num_nodes );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( cmp_num_nodes == store.numNodes( lock, arch_ids[ 1 ] ) );

    idx_it  = node_indices.begin();
    idx_end = node_indices.begin();
    std::advance( idx_end, cmp_num_nodes );

    for( ; idx_it != idx_end ; ++idx_it )
    {
        ASSERT_TRUE( !store.isNodeAttachedToAnySet( lock, *idx_it ) );
        ASSERT_TRUE( !store.isNodeSelectedByAnySet( lock, *idx_it ) );
        ASSERT_TRUE( !store.isNodeDefaultForAnySet( lock, *idx_it ) );

        status = store.attachNodeToSet( lock, *idx_it, node_set_2a_id );
        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
        ASSERT_TRUE( store.isNodeAttachedToAnySet( lock, *idx_it ) );
        ASSERT_TRUE( store.isNodeAttachedToSet(
            lock, *idx_it, node_set_2a_id ) );

        ASSERT_TRUE( store.canNodeBeSelectedBySet(
            lock, *idx_it, node_set_2a_id ) );
    }

    ASSERT_TRUE( ptr_node_set_2a->numNodes( lock ) == cmp_num_nodes );
    ASSERT_TRUE( ptr_node_set_2a->minNodeIndex(
        lock ) == node_indices.front() );

    ASSERT_TRUE( ptr_node_set_2a->maxNodeIndex( lock ) ==
                 node_indices.at( cmp_num_nodes - 1 ) );

    ASSERT_TRUE( std::equal(
        store.attachedNodeIndicesBegin( lock, node_set_2a_id ),
        store.attachedNodeIndicesEnd( lock, node_set_2a_id ),
        node_indices.begin() ) );

    ASSERT_TRUE( store.selectedNodeIndicesBegin( lock, node_set_2a_id ) ==
        store.selectedNodeIndicesEnd( lock, node_set_2a_id ) );

    ASSERT_TRUE( store.defaultNodeIndicesBegin( lock, node_set_2a_id ) ==
        store.defaultNodeIndicesEnd( lock, node_set_2a_id ) );

    /* --------------------------------------------------------------------- */
    /* Add another node_set for arch_ids[ 1 ]: */

    ptr_node_set.reset( new node_set_t( store ) );
    node_set_t* ptr_node_set_2b = ptr_node_set.get();

    ptr_node_set_2b->setMaxNumSelectableNodes( lock, size_t{ 1 } );

    ASSERT_TRUE( ptr_node_set.get() != nullptr );
    ASSERT_TRUE( ptr_node_set->ptrNodeStore() == &store );

    /* ... and add it to the store */

    node_set_id_t const node_set_2b_id = store.addNodeSet(
        lock, std::move( ptr_node_set ) );

    ASSERT_TRUE( node_set_2b_id != store_t::ILLEGAL_NODE_SET_ID );
    ASSERT_TRUE( ptr_node_set.get() == nullptr );
    ASSERT_TRUE( ptr_node_set_2b   != nullptr );
    ASSERT_TRUE( store.hasNodeSet( lock, node_set_2b_id ) );
    ASSERT_TRUE( store.numNodeSets( lock ) == size_t{ 4 } );
    ASSERT_TRUE( store.ptrNodeSetBase(
        lock, node_set_2b_id ) == ptr_node_set_2b );

    ASSERT_TRUE( ptr_node_set_2b->nodeSetId() == node_set_2b_id );

    ASSERT_TRUE( ptr_node_set_2b->numNodes( lock ) == size_t{ 0 } );
    ASSERT_TRUE( ptr_node_set_2b->minNodeIndex(
        lock ) == store_t::UNDEFINED_INDEX );

    ASSERT_TRUE( ptr_node_set_2b->maxNodeIndex(
        lock ) == store_t::UNDEFINED_INDEX );

    ASSERT_TRUE( ptr_node_set_2b->nodeIndicesBegin( lock ) == nullptr );
    ASSERT_TRUE( ptr_node_set_2b->nodeIndicesEnd( lock ) == nullptr );

    /* --------------------------------------------------------------------- */
    /* Attach all nodes from arch_ids[ 1 ] to node_set_1a_id: */

    status = store.nodeIndices( lock, node_indices.begin(), node_indices.end(),
                                arch_ids[ 1 ], &cmp_num_nodes );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( cmp_num_nodes == store.numNodes( lock, arch_ids[ 1 ] ) );

    idx_it  = node_indices.begin();
    idx_end = node_indices.begin();
    std::advance( idx_end, cmp_num_nodes );

    for( ; idx_it != idx_end ; ++idx_it )
    {
        /* Note: this time, the node has already been selected by
         * node_set_2a_id: */

        ASSERT_TRUE(  store.isNodeAttachedToAnySet( lock, *idx_it ) );
        ASSERT_TRUE(  store.isNodeAttachedToSet(
            lock, *idx_it, node_set_2a_id ) );

        ASSERT_TRUE( !store.isNodeSelectedByAnySet( lock, *idx_it ) );
        ASSERT_TRUE( !store.isNodeDefaultForAnySet( lock, *idx_it ) );

        status = store.attachNodeToSet( lock, *idx_it, node_set_2b_id );
        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
        ASSERT_TRUE( store.isNodeAttachedToAnySet( lock, *idx_it ) );
        ASSERT_TRUE( store.isNodeAttachedToSet(
            lock, *idx_it, node_set_2b_id ) );

        ASSERT_TRUE( store.canNodeBeSelectedBySet(
            lock, *idx_it, node_set_2b_id ) );
    }

    ASSERT_TRUE( ptr_node_set_2b->numNodes( lock ) == cmp_num_nodes );
    ASSERT_TRUE( ptr_node_set_2b->minNodeIndex(
        lock ) == node_indices.front() );

    ASSERT_TRUE( ptr_node_set_2b->maxNodeIndex( lock ) ==
                 node_indices.at( cmp_num_nodes - 1 ) );

    ASSERT_TRUE( std::equal(
        store.attachedNodeIndicesBegin( lock, node_set_2b_id ),
        store.attachedNodeIndicesEnd( lock, node_set_2b_id ),
        node_indices.begin() ) );

    ASSERT_TRUE( store.selectedNodeIndicesBegin( lock, node_set_2b_id ) ==
        store.selectedNodeIndicesEnd( lock, node_set_2a_id ) );

    ASSERT_TRUE( store.defaultNodeIndicesBegin( lock, node_set_2b_id ) ==
        store.defaultNodeIndicesEnd( lock, node_set_2b_id ) );

    /* Create another node_set and assign all assignable nodes from
     * arch_ids[ 2 ], arch_ids[ 3 ], arch_ids[ 4 ] : */

    ptr_node_set.reset( new node_set_t( store ) );
    node_set_t* ptr_node_set_3 = ptr_node_set.get();

    ptr_node_set_3->setMaxNumSelectableNodes( lock, size_t{ 1 } );

    ASSERT_TRUE( ptr_node_set.get() != nullptr );
    ASSERT_TRUE( ptr_node_set->ptrNodeStore() == &store );

    /* add it to the store */

    node_set_id_t const node_set_3_id = store.addNodeSet(
        lock, std::move( ptr_node_set ) );

    ASSERT_TRUE( node_set_3_id != store_t::ILLEGAL_NODE_SET_ID );
    ASSERT_TRUE( ptr_node_set.get() == nullptr );
    ASSERT_TRUE( ptr_node_set_3 != nullptr );
    ASSERT_TRUE( store.hasNodeSet( lock, node_set_3_id ) );
    ASSERT_TRUE( store.numNodeSets( lock ) == size_t{ 5 } );
    ASSERT_TRUE( store.ptrNodeSetBase(
        lock, node_set_3_id ) == ptr_node_set_3 );

    ASSERT_TRUE( ptr_node_set_3->nodeSetId() == node_set_3_id );

    ASSERT_TRUE( ptr_node_set_3->numNodes( lock ) == size_t{ 0 } );
    ASSERT_TRUE( ptr_node_set_3->minNodeIndex(
        lock ) == store_t::UNDEFINED_INDEX );

    ASSERT_TRUE( ptr_node_set_3->maxNodeIndex(
        lock ) == store_t::UNDEFINED_INDEX );

    ASSERT_TRUE( ptr_node_set_3->nodeIndicesBegin( lock ) == nullptr );
    ASSERT_TRUE( ptr_node_set_3->nodeIndicesEnd( lock ) == nullptr );

    size_t num_nodes_not_attached = size_t{ 0 };

    for( size_t ii = size_t{ 2 } ; ii < NUM_ARCHS ; ++ii )
    {
        status = store.nodeIndices(
            lock, node_indices.begin(), node_indices.end(),
            arch_ids[ ii ], &cmp_num_nodes );

        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
        ASSERT_TRUE( cmp_num_nodes == store.numNodes( lock, arch_ids[ ii ] ) );
        ASSERT_TRUE( cmp_num_nodes > size_t{ 0 } );

        idx_it  = node_indices.begin();
        idx_end = node_indices.begin();
        std::advance( idx_end, cmp_num_nodes );

        for( ; idx_it != idx_end ; ++idx_it )
        {
            ASSERT_TRUE( *idx_it != store_t::UNDEFINED_INDEX );

            auto ptr_node_info = store.ptrNodeInfoBase( lock, *idx_it );
            ASSERT_TRUE( ptr_node_info != nullptr );

            status = store.attachNodeToSet( lock, *idx_it, node_set_3_id );

            ASSERT_TRUE( ( ( ptr_node_info->numAttachedSets( lock ) <=
                             ptr_node_info->maxAttachementCount() ) &&
                           ( status == st::ARCH_STATUS_SUCCESS ) &&
                           ( store.isNodeAttachedToAnySet( lock, *idx_it ) ) &&
                           ( store.isNodeAttachedToSet(
                            lock, *idx_it, node_set_3_id ) ) ) ||
                         ( ( ptr_node_info->numAttachedSets( lock ) ==
                             ptr_node_info->maxAttachementCount() ) &&
                           ( status != st::ARCH_STATUS_SUCCESS ) ) );

            if( !store.isNodeAttachedToSet( lock, *idx_it, node_set_3_id ) )
            {
                ++num_nodes_not_attached;
            }

            ASSERT_TRUE( !store.isNodeSelectedByAnySet( lock, *idx_it ) );
            ASSERT_TRUE( !store.isNodeSelectedBySet(
                lock, *idx_it, node_set_3_id ) );

            ASSERT_TRUE( !store.isNodeDefaultForAnySet( lock, *idx_it ) );
            ASSERT_TRUE( !store.isNodeDefaultForSet(
                lock, *idx_it, node_set_3_id ) );
        }
    }

    ASSERT_TRUE( store.selectedNodeIndicesBegin( lock, node_set_3_id ) ==
        store.selectedNodeIndicesEnd( lock, node_set_3_id ) );

    ASSERT_TRUE( store.defaultNodeIndicesBegin( lock, node_set_3_id ) ==
        store.defaultNodeIndicesEnd( lock, node_set_3_id ) );

    size_t const node_set_3_num_nodes = ptr_node_set_3->numNodes( lock );
    size_t const arch_ids_2_num_nodes = store.numNodes( lock, arch_ids[ 2 ] );
    size_t const arch_ids_3_num_nodes = store.numNodes( lock, arch_ids[ 3 ] );
    size_t const arch_ids_4_num_nodes = store.numNodes( lock, arch_ids[ 4 ] );

    ASSERT_TRUE( ( num_nodes_not_attached + node_set_3_num_nodes )
        == ( arch_ids_2_num_nodes + arch_ids_3_num_nodes +
                arch_ids_4_num_nodes ) );

    /* Detach the first node from the first node_set */

    ASSERT_TRUE( store.isNodeAttachedToSet(
        lock, cmp_node_indices[ 0 ], node_set_1a_id ) );

    status = store.detachNodeFromSet(
        lock, cmp_node_indices[ 0 ], node_set_1a_id );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( !store.isNodeAttachedToSet(
        lock, cmp_node_indices[ 0 ], node_set_1a_id  ) );

    status = store.attachNodeToSet(
        lock, cmp_node_indices[ 0 ], node_set_3_id );

    ASSERT_TRUE( store.isNodeAttachedToSet(
        lock, cmp_node_indices[ 0 ], node_set_3_id ) );

    ASSERT_TRUE( ( num_nodes_not_attached + ptr_node_set_3->numNodes( lock ) )
        == ( store.numNodes( lock, arch_ids[ 2 ] ) +
             store.numNodes( lock, arch_ids[ 3 ] ) +
             store.numNodes( lock, arch_ids[ 4 ] ) + size_t{ 1 } ) );

    ASSERT_TRUE( store.attachedNodeIndicesBegin(
        lock, node_set_3_id ) != nullptr );

    ASSERT_TRUE( *store.attachedNodeIndicesBegin( lock, node_set_3_id ) ==
                 cmp_node_indices[ 0 ] );
}

/* end: /sixtracklib/common/control/test_node_set_cxx.cpp */
