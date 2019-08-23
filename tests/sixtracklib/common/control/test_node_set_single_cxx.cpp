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

TEST( CXX_CommonControlNodeSetSingleTests, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    namespace st_test = SIXTRL_CXX_NAMESPACE::tests;

    using store_t          = st::NodeStore;
    using node_set_t       = st_test::TestNodeSetSingle;
    using platform_id_t    = st::node_platform_id_t;
    using size_t           = store_t::size_type;
    using arch_id_t        = store_t::arch_id_t;
    using node_index_t     = store_t::node_index_t;
    using node_set_id_t    = store_t::node_set_id_t;
    using status_t         = store_t::status_t;
    using ptr_node_set_t   = std::unique_ptr< node_set_t >;

    /* ********************************************************************* */
    /* *****                      Setup tests                          ***** */
    /* ********************************************************************* */

    /* Create a dummy architecture for the unit-test: */

    st::Architectures& archs = st::Architectures_get();

    static constexpr size_t NUM_ARCHS = size_t{ 1 };
    arch_id_t arch_id = store_t::UNDEFINED_INDEX;

    status_t status = st_test::Architectures_setup(
        archs, NUM_ARCHS, arch_id_t{ 32 }, &arch_id );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    /* Create an empty store */

    store_t store;

    /* Create a set of nodes */

    static constexpr size_t NUM_NODES = 3;

    const arch_id_t nodes_arch_ids[ NUM_NODES ] =
    {
        arch_id, arch_id, arch_id
    };

    const platform_id_t nodes_platform_ids[ NUM_NODES ] =
    {
        store_t::ILLEGAL_PLATFORM_ID, store_t::ILLEGAL_PLATFORM_ID,
        store_t::ILLEGAL_PLATFORM_ID
    };

    const size_t nodes_max_attach_cnt[ NUM_NODES ] =
    {
        size_t{ 1 }, size_t{ 1 }, size_t{ 1 }
    };

    const size_t nodes_max_selection_cnt[ NUM_NODES ] =
    {
        size_t{ 1 }, size_t{ 1 }, size_t{ 1 }
    };

    node_index_t cmp_node_indices[ NUM_NODES ];
    std::fill( &cmp_node_indices[ 0 ], &cmp_node_indices[ NUM_NODES ],
               store_t::UNDEFINED_INDEX );

    status = st_test::TestNodeInfo_add_to_node_store( store, NUM_NODES,
        &nodes_arch_ids[ 0 ], &nodes_platform_ids[ 0 ],
            &nodes_max_attach_cnt[ 0 ], &nodes_max_selection_cnt[ 0 ],
                &cmp_node_indices[ 0 ] );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    SIXTRL_ASSERT(  store.totalNumNodes() == NUM_NODES );
    SIXTRL_ASSERT( !store.hasNodeSets() );

    /* Create a node set */

    ptr_node_set_t ptr_stored_set( new node_set_t( store ) );
    node_set_t* set = static_cast< node_set_t* >( ptr_stored_set.get() );
    SIXTRL_ASSERT( set != nullptr );

    node_set_id_t const set_id =
        store.addNodeSet( std::move( ptr_stored_set ) );
    SIXTRL_ASSERT( set_id != store_t::UNDEFINED_INDEX );
    SIXTRL_ASSERT( store.hasNodeSet( set_id ) );
    SIXTRL_ASSERT( store.ptrNodeSetBase( set_id ) == set );
    SIXTRL_ASSERT( set->nodeSetId() == set_id );

    /* Configure node set to be as restrictive as possible; these restrictions
     * are relaxed over the course of the tests below */

    set->setCanDirectlyChangeSelectedNodeFlag( false );
    set->setCanUnselectNodeFlag( false );
    set->setUseAutoselectFlag( false );

    SIXTRL_ASSERT( !set->supportsChangingSelectedNode() );
    SIXTRL_ASSERT( !set->supportsDirectlyChangingSelectedNode() );
    SIXTRL_ASSERT( !set->supportsUnselectingNode() );
    SIXTRL_ASSERT( !set->usesAutoSelect() );

    /* Assign all nodes to the set */

    status = store.attachAllArchitectureNodesToSet( arch_id, set_id );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->numNodes() == NUM_NODES );

    for( size_t ii = size_t{ 0 } ; ii < NUM_NODES ; ++ii )
    {
        node_index_t const idx = cmp_node_indices[ ii ];
        ASSERT_TRUE( idx != store_t::UNDEFINED_INDEX );

        ASSERT_TRUE(  store.isNodeAttachedToAnySet( idx ) );
        ASSERT_TRUE( !store.isNodeSelectedByAnySet( idx ) );
        ASSERT_TRUE( !store.isNodeDefaultForAnySet( idx ) );

        ASSERT_TRUE(  store.isNodeAttachedToSet( idx, set_id ) );
        ASSERT_TRUE( !store.isNodeSelectedBySet( idx, set_id ) );
        ASSERT_TRUE( !store.isNodeDefaultForSet( idx, set_id ) );

        ASSERT_TRUE( !set->isSelected( idx ) );
        ASSERT_TRUE( !set->isDefault( idx ) );
    }

    node_index_t const node_idx_1 = cmp_node_indices[ 0 ];
    node_index_t const node_idx_2 = cmp_node_indices[ 1 ];
    node_index_t const node_idx_3 = cmp_node_indices[ 2 ];

    /* ********************************************************************* */
    /* *****                    Perform tests                          ***** */
    /* ********************************************************************* */

    ASSERT_TRUE( set->selectedNodeIndex() == store_t::UNDEFINED_INDEX );

    /* Select first node: */

    bool can_perform_op = set->canSelectNode( node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->selectNode( node_idx_1 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( node_idx_1 ) );
    ASSERT_TRUE( store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Try to select node #1 again. Since this is already selected, it should
     * work */

    can_perform_op = set->canSelectNode( node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->selectNode( node_idx_1 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( node_idx_1 ) );
    ASSERT_TRUE( store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Same again, but this time using the changeSelectedNodeTo() API.
     * This should work because it is actually a NOP */

    can_perform_op = set->canChangeSelectedNodeTo( node_idx_1 );
    ASSERT_TRUE( can_perform_op );
    status = set->changeSelectedNodeTo( node_idx_1 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( node_idx_1 ) );
    ASSERT_TRUE( store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Try to select node #2. Since change of node and unselection of node
     * is not available, this should not work */

    can_perform_op = set->canSelectNode( node_idx_2 );
    ASSERT_TRUE( !can_perform_op );

    status = set->selectNode( node_idx_2 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( node_idx_1 ) );

    /* Try to select node #2 by means of the changeSelectedNodeTo() API.
     * Should not work because all capabilities in this regard are disabled */

    can_perform_op = set->canChangeSelectedNodeTo( node_idx_2 );
    ASSERT_TRUE( !can_perform_op );

    status = set->changeSelectedNodeTo( node_idx_2 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( node_idx_1 ) );
    ASSERT_TRUE( store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Try to unselect node #2 -> should not work because we disabled
     * the unselection capabilities above AND because node#2 is not selected */

    can_perform_op = set->canUnselectNode( node_idx_2 );
    ASSERT_TRUE( !can_perform_op );

    status = set->unselectNode( node_idx_2 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( node_idx_1 ) );

    /* Try to unselect node #1 -> should not work because we disabled
     * the unselection capabilities above */

    can_perform_op = set->canUnselectNode( node_idx_1 );
    ASSERT_TRUE( !can_perform_op );

    status = set->unselectNode( node_idx_1 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( node_idx_1 ) );

    /* Enable unselection. This implies enabling the ability to change nodes;
     * directly changing nodes is however a different capability */

    set->setCanUnselectNodeFlag( true );
    ASSERT_TRUE(  set->supportsUnselectingNode() );
    ASSERT_TRUE(  set->supportsChangingSelectedNode() );
    ASSERT_TRUE( !set->supportsDirectlyChangingSelectedNode() );

    /* Try to unselect node #2 -> should not work because because node#2
     * is not selected */

    can_perform_op = set->canUnselectNode( node_idx_2 );
    ASSERT_TRUE( !can_perform_op );

    status = set->unselectNode( node_idx_2 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( node_idx_1 ) );

    /* Try to unselect node #1 -> should now work  */

    can_perform_op = set->canUnselectNode( node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->unselectNode( node_idx_1 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedByAnySet( node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_1 ) );
    ASSERT_TRUE( store.numSelectedNodes( set_id ) == size_t{ 0 } );

    /* Selecting node #2 now: */

    can_perform_op = set->canSelectNode( node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->selectNode( node_idx_2 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_2 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( node_idx_2, set_id ) );
    ASSERT_TRUE( !set->isSelected( node_idx_1 ) );
    ASSERT_TRUE(  set->isSelected( node_idx_2 ) );
    ASSERT_TRUE( store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Try changing to node #3 but from the wrong current node (#1, but #2
     * is selected ) -> regardless of capabilities, this should not work! */

    can_perform_op = set->canChangeSelectedNodeTo( node_idx_1, node_idx_3 );
    ASSERT_TRUE( !can_perform_op );

    status = set->changeSelectedNodeTo( node_idx_1, node_idx_3 );
    ASSERT_TRUE(  status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_2 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_3, set_id ) );
    ASSERT_TRUE( !set->isSelected( node_idx_1 ) );
    ASSERT_TRUE(  set->isSelected( node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Changing to node #3 now should work because we can unselect and
     * then select. Verify that direct change is disabled, though */

    ASSERT_TRUE( !set->supportsDirectlyChangingSelectedNode() );
    can_perform_op = set->canChangeSelectedNodeTo( node_idx_2, node_idx_3 );
    ASSERT_TRUE( can_perform_op );

    status = set->changeSelectedNodeTo( node_idx_2, node_idx_3 );
    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_3 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_2, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( node_idx_3, set_id ) );
    ASSERT_TRUE( !set->isSelected( node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_2 ) );
    ASSERT_TRUE(  set->isSelected( node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Use NodeSetSingle changeSelectedNodeTo() which omits the source node index
     * to change back to node #1. Should work */

    can_perform_op = set->canChangeSelectedNodeTo( node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->changeSelectedNodeTo( node_idx_1 );
    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE(  store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_3, set_id ) );
    ASSERT_TRUE(  set->isSelected( node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Change from node #1 to #2 using the selectNode API; this should work
     * even though node #1 is currently selected as unselecting is enabled */

    can_perform_op = set->canSelectNode( node_idx_2 );
    ASSERT_TRUE( can_perform_op );

    status = set->selectNode( node_idx_2 );
    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_2 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_3, set_id ) );
    ASSERT_TRUE( !set->isSelected( node_idx_1 ) );
    ASSERT_TRUE(  set->isSelected( node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Disable unselecting capability. Enable direct changing nodes */

    set->setCanDirectlyChangeSelectedNodeFlag( true );
    set->setCanUnselectNodeFlag( false );

    ASSERT_TRUE(  set->supportsChangingSelectedNode() );
    ASSERT_TRUE(  set->supportsDirectlyChangingSelectedNode() );
    ASSERT_TRUE( !set->supportsUnselectingNode() );

    /* Can not change from node #1 to #3 because, regardless of capabilities,
     * the currently selected node is #2 */

    can_perform_op = set->canChangeSelectedNodeTo(
        node_idx_1, node_idx_3 );
    ASSERT_TRUE( !can_perform_op );

    status = set->changeSelectedNodeTo( node_idx_1, node_idx_3 );
    ASSERT_TRUE(  status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_2 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_3, set_id ) );
    ASSERT_TRUE( !set->isSelected( node_idx_1 ) );
    ASSERT_TRUE(  set->isSelected( node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Change node #2 to node #3.
     * Should work due to directly change capability */

    can_perform_op = set->canChangeSelectedNodeTo(
        node_idx_2, node_idx_3 );
    ASSERT_TRUE( can_perform_op );

    status = set->changeSelectedNodeTo( node_idx_2, node_idx_3 );
    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_3 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_2, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( node_idx_3, set_id ) );
    ASSERT_TRUE( !set->isSelected( node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_2 ) );
    ASSERT_TRUE(  set->isSelected( node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Change node #3 to node #1 using selectNode API.
     * Should work due to directly change capability */

    can_perform_op = set->canSelectNode( node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->selectNode( node_idx_1 );
    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE(  store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_3, set_id ) );
    ASSERT_TRUE(  set->isSelected( node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Enable unselecting nodes and raise the minimum number of selected
     * nodes to 1. This should prevent unselection of nodes even if the
     * capability is granted */

    set->setCanUnselectNodeFlag( true );
    set->setCanDirectlyChangeSelectedNodeFlag( false );
    set->setMinNumSelectableNodes( size_t{ 1 } );

    ASSERT_TRUE( !set->supportsDirectlyChangingSelectedNode() );
    ASSERT_TRUE(  set->supportsUnselectingNode() );
    ASSERT_TRUE(  set->supportsChangingSelectedNode() );
    ASSERT_TRUE( !set->usesAutoSelect() );

    ASSERT_TRUE(  store.numDefaultNodes( set_id ) == size_t{ 0 } );
    ASSERT_TRUE( !store.isNodeDefaultForAnySet( node_idx_1 ) );
    ASSERT_TRUE( !store.isNodeDefaultForSet( node_idx_1, set_id ) );
    ASSERT_TRUE(  store.canNodeBeMadeDefaultForSet( node_idx_1, set_id ) );
    ASSERT_TRUE(  set->minNumSelectableNodes() ==
                  store.numSelectedNodes( set_id ) );

    /* Attempt to unselect node_idx_1 -> should not work because doing so
     * would drop the number of selected nodes below the new treshold & there
     * are no default nodes to autoSelect */

    can_perform_op = set->canUnselectNode( node_idx_1 );
    ASSERT_TRUE( !can_perform_op );

    status = set->unselectNode( node_idx_1 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE(  store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_3, set_id ) );
    ASSERT_TRUE(  set->isSelected( node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Add node_idx_1 as a default node */

    status = set->selectDefaultNode( node_idx_1 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->defaultNodeIndex() == node_idx_1 );
    ASSERT_TRUE( set->hasDefaultNode() );
    ASSERT_TRUE( store.numDefaultNodes( set_id ) == size_t{ 1 } );
    ASSERT_TRUE( store.isNodeDefaultForAnySet( node_idx_1 ) );
    ASSERT_TRUE( store.isNodeDefaultForSet( node_idx_1, set_id ) );

    /* Try to repeat the unselect operation of node_idx_1 ->
     * this should still not be possible as a) autoselect is not enabled and
     * b) unselecting node_idx_1 would result in node_idx_1 being selected
     * again as per default -> this is considered an non-successful op. */

    can_perform_op = set->canUnselectNode( node_idx_1 );
    ASSERT_TRUE( !can_perform_op );

    status = set->unselectNode( node_idx_1 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE(  store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_3, set_id ) );
    ASSERT_TRUE(  set->isSelected( node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* enable auto-select */

    set->setUseAutoselectFlag( true );
    ASSERT_TRUE(  set->usesAutoSelect() );

    /* Try to repeat the unselection again, which still should not work since
     * node_idx_1 is both selected and the default node */

    can_perform_op = set->canUnselectNode( node_idx_1 );
    ASSERT_TRUE( !can_perform_op );

    status = set->unselectNode( node_idx_1 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE(  store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_3, set_id ) );
    ASSERT_TRUE(  set->isSelected( node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* Attempting to add a second default node to get out of the dilemma should
     * not work as we are using a NodeSetSingle instance here which has a
     * maximum num of default nodes of 1 */

    status = set->selectDefaultNode( node_idx_2 );
    ASSERT_TRUE(  status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->defaultNodeIndex() == node_idx_1 );
    ASSERT_TRUE(  set->hasDefaultNode() );
    ASSERT_TRUE(  store.numDefaultNodes( set_id ) == size_t{ 1 } );
    ASSERT_TRUE(  store.isNodeDefaultForAnySet( node_idx_1 ) );
    ASSERT_TRUE( !store.isNodeDefaultForAnySet( node_idx_2 ) );
    ASSERT_TRUE(  store.isNodeDefaultForSet( node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeDefaultForSet( node_idx_2, set_id ) );

    /* Remove node #1 as default node first, then try to set node #2 as default
     * node */

    status = set->removeDefaultNode();
    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->defaultNodeIndex() == store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( !set->hasDefaultNode() );
    ASSERT_TRUE(  store.numDefaultNodes( set_id ) == size_t{ 0 } );
    ASSERT_TRUE( !store.isNodeDefaultForAnySet( node_idx_1 ) );
    ASSERT_TRUE( !store.isNodeDefaultForAnySet( node_idx_2 ) );
    ASSERT_TRUE( !store.isNodeDefaultForSet( node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeDefaultForSet( node_idx_2, set_id ) );

    status = set->selectDefaultNode( node_idx_2 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->defaultNodeIndex() == node_idx_2 );
    ASSERT_TRUE( set->hasDefaultNode() );
    ASSERT_TRUE( store.numDefaultNodes( set_id ) == size_t{ 1 } );
    ASSERT_TRUE( store.isNodeDefaultForAnySet( node_idx_2 ) );
    ASSERT_TRUE( store.isNodeDefaultForSet( node_idx_2, set_id ) );

    /* Now, unselection should work. We expect the selection to switch to
     * node #2 if we unselect node #1: */

    can_perform_op = set->canUnselectNode( node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->unselectNode( node_idx_1 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_2 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_1, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( node_idx_3, set_id ) );
    ASSERT_TRUE( !set->isSelected( node_idx_1 ) );
    ASSERT_TRUE(  set->isSelected( node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( set_id ) == size_t{ 1 } );

    /* detach all nodes from set */

    status = store.detachAllNodesFromSet( set_id );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE( store.hasNodeSet( set_id ) );
    ASSERT_TRUE( store.ptrNodeSetBase( set_id ) == set );
    ASSERT_TRUE( store.numNodes( arch_id ) == NUM_NODES );
    ASSERT_TRUE( store.numNodes( set_id ) == size_t{ 0 } );
    ASSERT_TRUE( store.numSelectedNodes( set_id ) == size_t{ 0 } );
    ASSERT_TRUE( store.numDefaultNodes( set_id ) == size_t{ 0 } );

    ASSERT_TRUE(  set->numNodes() == size_t{ 0 } );
    ASSERT_TRUE(  set->selectedNodeIndex() == store_t::UNDEFINED_INDEX );
    ASSERT_TRUE(  set->defaultNodeIndex() == store_t::UNDEFINED_INDEX );

    for( size_t ii = size_t{ 0 } ; ii < NUM_NODES ; ++ii )
    {
        node_index_t const index = cmp_node_indices[ ii ];
        ASSERT_TRUE( index != store_t::UNDEFINED_INDEX );
        ASSERT_TRUE(  store.isNodeAvailable( index ) );
        ASSERT_TRUE( !store.isNodeAttachedToAnySet( index ) );
        ASSERT_TRUE( !store.isNodeAttachedToSet( index, set_id ) );
        ASSERT_TRUE( !store.isNodeSelectedByAnySet( index ) );
        ASSERT_TRUE( !store.isNodeSelectedBySet( index, set_id ) );
        ASSERT_TRUE( !store.isNodeDefaultForAnySet( index ) );
        ASSERT_TRUE( !store.isNodeDefaultForSet( index, set_id ) );

        ASSERT_TRUE( store.numSetsAttachedToNode( index ) == size_t{ 0 } );
        ASSERT_TRUE( store.numSelectingSetsForNode( index ) == size_t{ 0 } );
        ASSERT_TRUE( store.numSetsHavingNodeAsDefault( index ) == size_t{ 0 } );

        ASSERT_TRUE( !set->isSelected( index ) );
        ASSERT_TRUE( !set->isDefault( index ) );
    }
}


TEST( CXX_CommonControlNodeSetSingleTests, BasicUsageExtLock )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    namespace st_test = SIXTRL_CXX_NAMESPACE::tests;

    using store_t          = st::NodeStore;
    using node_set_t       = st_test::TestNodeSetSingle;
    using platform_id_t    = st::node_platform_id_t;
    using size_t           = store_t::size_type;
    using arch_id_t        = store_t::arch_id_t;
    using node_index_t     = store_t::node_index_t;
    using node_set_id_t    = store_t::node_set_id_t;
    using status_t         = store_t::status_t;
    using ptr_node_set_t   = std::unique_ptr< node_set_t >;

    /* ********************************************************************* */
    /* *****                      Setup tests                          ***** */
    /* ********************************************************************* */

    /* Create a dummy architecture for the unit-test: */

    st::Architectures& archs = st::Architectures_get();

    static constexpr size_t NUM_ARCHS = size_t{ 1 };
    arch_id_t arch_id = store_t::UNDEFINED_INDEX;

    status_t status = st_test::Architectures_setup(
        archs, NUM_ARCHS, arch_id_t{ 32 }, &arch_id );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    /* Create an empty store */

    store_t store;

    /* Create a set of nodes */

    static constexpr size_t NUM_NODES = 3;

    const arch_id_t nodes_arch_ids[ NUM_NODES ] =
    {
        arch_id, arch_id, arch_id
    };

    const platform_id_t nodes_platform_ids[ NUM_NODES ] =
    {
        store_t::ILLEGAL_PLATFORM_ID, store_t::ILLEGAL_PLATFORM_ID,
        store_t::ILLEGAL_PLATFORM_ID
    };

    const size_t nodes_max_attach_cnt[ NUM_NODES ] =
    {
        size_t{ 1 }, size_t{ 1 }, size_t{ 1 }
    };

    const size_t nodes_max_selection_cnt[ NUM_NODES ] =
    {
        size_t{ 1 }, size_t{ 1 }, size_t{ 1 }
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
    SIXTRL_ASSERT(  store.totalNumNodes( lock ) == NUM_NODES );
    SIXTRL_ASSERT( !store.hasNodeSets( lock ) );

    /* Create a node set */

    ptr_node_set_t ptr_stored_set( new node_set_t( lock, store ) );
    node_set_t* set = static_cast< node_set_t* >( ptr_stored_set.get() );
    SIXTRL_ASSERT( set != nullptr );

    node_set_id_t const set_id = store.addNodeSet(
        lock, std::move( ptr_stored_set ) );

    SIXTRL_ASSERT( set_id != store_t::UNDEFINED_INDEX );
    SIXTRL_ASSERT( store.hasNodeSet( lock, set_id ) );
    SIXTRL_ASSERT( store.ptrNodeSetBase( lock, set_id ) == set );
    SIXTRL_ASSERT( set->nodeSetId() == set_id );

    /* Configure node set to be as restrictive as possible; these restrictions
     * are relaxed over the course of the tests below */

    set->setCanDirectlyChangeSelectedNodeFlag( false );
    set->setCanUnselectNodeFlag( false );
    set->setUseAutoselectFlag( false );

    SIXTRL_ASSERT( !set->supportsChangingSelectedNode() );
    SIXTRL_ASSERT( !set->supportsDirectlyChangingSelectedNode() );
    SIXTRL_ASSERT( !set->supportsUnselectingNode() );
    SIXTRL_ASSERT( !set->usesAutoSelect() );

    /* Assign all nodes to the set */

    status = store.attachAllArchitectureNodesToSet( lock, arch_id, set_id );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->numNodes( lock ) == NUM_NODES );

    for( size_t ii = size_t{ 0 } ; ii < NUM_NODES ; ++ii )
    {
        node_index_t const idx = cmp_node_indices[ ii ];
        ASSERT_TRUE( idx != store_t::UNDEFINED_INDEX );

        ASSERT_TRUE(  store.isNodeAttachedToAnySet( lock, idx ) );
        ASSERT_TRUE( !store.isNodeSelectedByAnySet( lock, idx ) );
        ASSERT_TRUE( !store.isNodeDefaultForAnySet( lock, idx ) );

        ASSERT_TRUE(  store.isNodeAttachedToSet( lock, idx, set_id ) );
        ASSERT_TRUE( !store.isNodeSelectedBySet( lock, idx, set_id ) );
        ASSERT_TRUE( !store.isNodeDefaultForSet( lock, idx, set_id ) );

        ASSERT_TRUE( !set->isSelected( lock, idx ) );
        ASSERT_TRUE( !set->isDefault( lock, idx ) );
    }

    node_index_t const node_idx_1 = cmp_node_indices[ 0 ];
    node_index_t const node_idx_2 = cmp_node_indices[ 1 ];
    node_index_t const node_idx_3 = cmp_node_indices[ 2 ];

    /* ********************************************************************* */
    /* *****                    Perform tests                          ***** */
    /* ********************************************************************* */

    ASSERT_TRUE( set->selectedNodeIndex() == store_t::UNDEFINED_INDEX );

    /* Select first node: */

    bool can_perform_op = set->canSelectNode( lock, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->selectNode( lock, node_idx_1 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE( store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Try to select node #1 again. Since this is already selected, it should
     * work */

    can_perform_op = set->canSelectNode( lock, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->selectNode( lock, node_idx_1 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE( store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Same again, but this time using the changeSelectedNodeTo() API.
     * This should work because it is actually a NOP */

    can_perform_op = set->canChangeSelectedNodeTo( lock, node_idx_1 );
    ASSERT_TRUE( can_perform_op );
    status = set->changeSelectedNodeTo( lock, node_idx_1 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE( store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Try to select node #2. Since change of node and unselection of node
     * is not available, this should not work */

    can_perform_op = set->canSelectNode( lock, node_idx_2 );
    ASSERT_TRUE( !can_perform_op );

    status = set->selectNode( lock, node_idx_2 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( lock, node_idx_1 ) );

    /* Try to select node #2 by means of the changeSelectedNodeTo() API.
     * Should not work because all capabilities in this regard are disabled */

    can_perform_op = set->canChangeSelectedNodeTo( lock, node_idx_2 );
    ASSERT_TRUE( !can_perform_op );

    status = set->changeSelectedNodeTo( lock, node_idx_2 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE( store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Try to unselect node #2 -> should not work because we disabled
     * the unselection capabilities above AND because node#2 is not selected */

    can_perform_op = set->canUnselectNode( lock, node_idx_2 );
    ASSERT_TRUE( !can_perform_op );

    status = set->unselectNode( lock, node_idx_2 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( lock, node_idx_1 ) );

    /* Try to unselect node #1 -> should not work because we disabled
     * the unselection capabilities above */

    can_perform_op = set->canUnselectNode( lock, node_idx_1 );
    ASSERT_TRUE( !can_perform_op );

    status = set->unselectNode( lock, node_idx_1 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( lock, node_idx_1 ) );

    /* Enable unselection. This implies enabling the ability to change nodes;
     * directly changing nodes is however a different capability */

    set->setCanUnselectNodeFlag( true );
    ASSERT_TRUE(  set->supportsUnselectingNode() );
    ASSERT_TRUE(  set->supportsChangingSelectedNode() );
    ASSERT_TRUE( !set->supportsDirectlyChangingSelectedNode() );

    /* Try to unselect node #2 -> should not work because because node#2
     * is not selected */

    can_perform_op = set->canUnselectNode( lock, node_idx_2 );
    ASSERT_TRUE( !can_perform_op );

    status = set->unselectNode( lock, node_idx_2 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE( store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( set->isSelected( lock, node_idx_1 ) );

    /* Try to unselect node #1 -> should now work  */

    can_perform_op = set->canUnselectNode( lock, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->unselectNode( lock, node_idx_1 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->selectedNodeIndex() == store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedByAnySet( lock, node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE( store.numSelectedNodes( lock, set_id ) == size_t{ 0 } );

    /* Selecting node #2 now: */

    can_perform_op = set->canSelectNode( lock, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->selectNode( lock, node_idx_2 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_2 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( lock, node_idx_2, set_id ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE(  set->isSelected( lock, node_idx_2 ) );
    ASSERT_TRUE( store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Try changing to node #3 but from the wrong current node (#1, but #2
     * is selected ) -> regardless of capabilities, this should not work! */

    can_perform_op = set->canChangeSelectedNodeTo(
        lock, node_idx_1, node_idx_3 );

    ASSERT_TRUE( !can_perform_op );

    status = set->changeSelectedNodeTo( lock, node_idx_1, node_idx_3 );
    ASSERT_TRUE(  status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_2 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( lock, node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_3, set_id ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE(  set->isSelected( lock, node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Changing to node #3 now should work because we can unselect and
     * then select. Verify that direct change is disabled, though */

    ASSERT_TRUE( !set->supportsDirectlyChangingSelectedNode() );
    can_perform_op = set->canChangeSelectedNodeTo(
        lock, node_idx_2, node_idx_3 );
    ASSERT_TRUE( can_perform_op );

    status = set->changeSelectedNodeTo( lock, node_idx_2, node_idx_3 );
    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_3 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_2, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( lock, node_idx_3, set_id ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_2 ) );
    ASSERT_TRUE(  set->isSelected( lock, node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Use NodeSetSingle changeSelectedNodeTo() which omits the source node index
     * to change back to node #1. Should work */

    can_perform_op = set->canChangeSelectedNodeTo( lock, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->changeSelectedNodeTo( lock, node_idx_1 );
    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE(  store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_3, set_id ) );
    ASSERT_TRUE(  set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Change from node #1 to #2 using the selectNode API; this should work
     * even though node #1 is currently selected as unselecting is enabled */

    can_perform_op = set->canSelectNode( lock, node_idx_2 );
    ASSERT_TRUE( can_perform_op );

    status = set->selectNode( lock, node_idx_2 );
    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_2 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( lock, node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_3, set_id ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE(  set->isSelected( lock, node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Disable unselecting capability. Enable direct changing nodes */

    set->setCanDirectlyChangeSelectedNodeFlag( true );
    set->setCanUnselectNodeFlag( false );

    ASSERT_TRUE(  set->supportsChangingSelectedNode() );
    ASSERT_TRUE(  set->supportsDirectlyChangingSelectedNode() );
    ASSERT_TRUE( !set->supportsUnselectingNode() );

    /* Can not change from node #1 to #3 because, regardless of capabilities,
     * the currently selected node is #2 */

    can_perform_op = set->canChangeSelectedNodeTo(
        lock, node_idx_1, node_idx_3 );
    ASSERT_TRUE( !can_perform_op );

    status = set->changeSelectedNodeTo( lock, node_idx_1, node_idx_3 );
    ASSERT_TRUE(  status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_2 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( lock, node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_3, set_id ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE(  set->isSelected( lock, node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Change node #2 to node #3.
     * Should work due to directly change capability */

    can_perform_op = set->canChangeSelectedNodeTo(
        lock, node_idx_2, node_idx_3 );
    ASSERT_TRUE( can_perform_op );

    status = set->changeSelectedNodeTo( lock, node_idx_2, node_idx_3 );
    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_3 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_2, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( lock, node_idx_3, set_id ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_2 ) );
    ASSERT_TRUE(  set->isSelected( lock, node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Change node #3 to node #1 using selectNode API.
     * Should work due to directly change capability */

    can_perform_op = set->canSelectNode( lock, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->selectNode( lock, node_idx_1 );
    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE(  store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_3, set_id ) );
    ASSERT_TRUE(  set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Enable unselecting nodes and raise the minimum number of selected
     * nodes to 1. This should prevent unselection of nodes even if the
     * capability is granted */

    set->setCanUnselectNodeFlag( true );
    set->setCanDirectlyChangeSelectedNodeFlag( false );
    set->setMinNumSelectableNodes( lock, size_t{ 1 } );

    ASSERT_TRUE( !set->supportsDirectlyChangingSelectedNode() );
    ASSERT_TRUE(  set->supportsUnselectingNode() );
    ASSERT_TRUE(  set->supportsChangingSelectedNode() );
    ASSERT_TRUE( !set->usesAutoSelect() );

    ASSERT_TRUE(  store.numDefaultNodes( lock, set_id ) == size_t{ 0 } );
    ASSERT_TRUE( !store.isNodeDefaultForAnySet( lock, node_idx_1 ) );
    ASSERT_TRUE( !store.isNodeDefaultForSet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE(  store.canNodeBeMadeDefaultForSet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE(  set->minNumSelectableNodes() ==
                  store.numSelectedNodes( lock, set_id ) );

    /* Attempt to unselect node_idx_1 -> should not work because doing so
     * would drop the number of selected nodes below the new treshold & there
     * are no default nodes to autoSelect */

    can_perform_op = set->canUnselectNode( lock, node_idx_1 );
    ASSERT_TRUE( !can_perform_op );

    status = set->unselectNode( lock, node_idx_1 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE(  store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_3, set_id ) );
    ASSERT_TRUE(  set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Add node_idx_1 as a default node */

    status = set->selectDefaultNode( lock, node_idx_1 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->defaultNodeIndex() == node_idx_1 );
    ASSERT_TRUE( set->hasDefaultNode( lock ) );
    ASSERT_TRUE( store.numDefaultNodes( lock, set_id ) == size_t{ 1 } );
    ASSERT_TRUE( store.isNodeDefaultForAnySet( lock, node_idx_1 ) );
    ASSERT_TRUE( store.isNodeDefaultForSet( lock, node_idx_1, set_id ) );

    /* Try to repeat the unselect operation of node_idx_1 ->
     * this should still not be possible as a) autoselect is not enabled and
     * b) unselecting node_idx_1 would result in node_idx_1 being selected
     * again as per default -> this is considered an non-successful op. */

    can_perform_op = set->canUnselectNode( lock, node_idx_1 );
    ASSERT_TRUE( !can_perform_op );

    status = set->unselectNode( lock, node_idx_1 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE(  store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_3, set_id ) );
    ASSERT_TRUE(  set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* enable auto-select */

    set->setUseAutoselectFlag( true );
    ASSERT_TRUE(  set->usesAutoSelect() );

    /* Try to repeat the unselection again, which still should not work since
     * node_idx_1 is both selected and the default node */

    can_perform_op = set->canUnselectNode( lock, node_idx_1 );
    ASSERT_TRUE( !can_perform_op );

    status = set->unselectNode( lock, node_idx_1 );
    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_1 );
    ASSERT_TRUE(  store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_3, set_id ) );
    ASSERT_TRUE(  set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* Attempting to add a second default node to get out of the dilemma should
     * not work as we are using a NodeSetSingle instance here which has a
     * maximum num of default nodes of 1 */

    status = set->selectDefaultNode( lock, node_idx_2 );
    ASSERT_TRUE(  status != st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->defaultNodeIndex() == node_idx_1 );
    ASSERT_TRUE(  set->hasDefaultNode( lock ) );
    ASSERT_TRUE(  store.numDefaultNodes( lock, set_id ) == size_t{ 1 } );
    ASSERT_TRUE(  store.isNodeDefaultForAnySet( lock, node_idx_1 ) );
    ASSERT_TRUE( !store.isNodeDefaultForAnySet( lock, node_idx_2 ) );
    ASSERT_TRUE(  store.isNodeDefaultForSet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeDefaultForSet( lock, node_idx_2, set_id ) );

    /* Remove node #1 as default node first, then try to set node #2 as default
     * node */

    status = set->removeDefaultNode( lock );
    ASSERT_TRUE(  status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->defaultNodeIndex() == store_t::UNDEFINED_INDEX );
    ASSERT_TRUE( !set->hasDefaultNode( lock ) );
    ASSERT_TRUE(  store.numDefaultNodes( lock, set_id ) == size_t{ 0 } );
    ASSERT_TRUE( !store.isNodeDefaultForAnySet( lock, node_idx_1 ) );
    ASSERT_TRUE( !store.isNodeDefaultForAnySet( lock, node_idx_2 ) );
    ASSERT_TRUE( !store.isNodeDefaultForSet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE( !store.isNodeDefaultForSet( lock, node_idx_2, set_id ) );

    status = set->selectDefaultNode( lock, node_idx_2 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( set->defaultNodeIndex() == node_idx_2 );
    ASSERT_TRUE( set->hasDefaultNode( lock ) );
    ASSERT_TRUE( store.numDefaultNodes( lock, set_id ) == size_t{ 1 } );
    ASSERT_TRUE( store.isNodeDefaultForAnySet( lock, node_idx_2 ) );
    ASSERT_TRUE( store.isNodeDefaultForSet( lock, node_idx_2, set_id ) );

    /* Now, unselection should work. We expect the selection to switch to
     * node #2 if we unselect node #1: */

    can_perform_op = set->canUnselectNode( lock, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = set->unselectNode( lock, node_idx_1 );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE(  set->selectedNodeIndex() == node_idx_2 );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_1, set_id ) );
    ASSERT_TRUE(  store.isNodeSelectedBySet( lock, node_idx_2, set_id ) );
    ASSERT_TRUE( !store.isNodeSelectedBySet( lock, node_idx_3, set_id ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_1 ) );
    ASSERT_TRUE(  set->isSelected( lock, node_idx_2 ) );
    ASSERT_TRUE( !set->isSelected( lock, node_idx_3 ) );
    ASSERT_TRUE(  store.numSelectedNodes( lock, set_id ) == size_t{ 1 } );

    /* detach all nodes from set */

    status = store.detachAllNodesFromSet( lock, set_id );
    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE( store.hasNodeSet( lock, set_id ) );
    ASSERT_TRUE( store.ptrNodeSetBase( lock, set_id ) == set );
    ASSERT_TRUE( store.numNodes( lock, arch_id ) == NUM_NODES );
    ASSERT_TRUE( store.numNodes( lock, set_id ) == size_t{ 0 } );
    ASSERT_TRUE( store.numSelectedNodes( lock, set_id ) == size_t{ 0 } );
    ASSERT_TRUE( store.numDefaultNodes( lock, set_id ) == size_t{ 0 } );

    ASSERT_TRUE(  set->numNodes( lock ) == size_t{ 0 } );
    ASSERT_TRUE(  set->selectedNodeIndex() == store_t::UNDEFINED_INDEX );
    ASSERT_TRUE(  set->defaultNodeIndex() == store_t::UNDEFINED_INDEX );

    for( size_t ii = size_t{ 0 } ; ii < NUM_NODES ; ++ii )
    {
        node_index_t const index = cmp_node_indices[ ii ];
        ASSERT_TRUE( index != store_t::UNDEFINED_INDEX );
        ASSERT_TRUE(  store.isNodeAvailable( lock, index ) );
        ASSERT_TRUE( !store.isNodeAttachedToAnySet( lock, index ) );
        ASSERT_TRUE( !store.isNodeAttachedToSet( lock, index, set_id ) );
        ASSERT_TRUE( !store.isNodeSelectedByAnySet( lock, index ) );
        ASSERT_TRUE( !store.isNodeSelectedBySet( lock, index, set_id ) );
        ASSERT_TRUE( !store.isNodeDefaultForAnySet( lock, index ) );
        ASSERT_TRUE( !store.isNodeDefaultForSet( lock, index, set_id ) );

        ASSERT_TRUE( store.numSetsAttachedToNode(
            lock, index ) == size_t{ 0 } );

        ASSERT_TRUE( store.numSelectingSetsForNode(
            lock, index ) == size_t{ 0 } );

        ASSERT_TRUE( store.numSetsHavingNodeAsDefault(
            lock, index ) == size_t{ 0 } );

        ASSERT_TRUE( !set->isSelected( lock, index ) );
        ASSERT_TRUE( !set->isDefault( lock, index ) );
    }
}

/*

TEST( CXX_CommonControlNodeSetSingleTests, CompetingSelection )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    namespace st_test = SIXTRL_CXX_NAMESPACE::tests;

    using store_t          = st::NodeStore;
    using node_set_t       = st_test::TestNodeSetSingle;
    using platform_id_t    = st::node_platform_id_t;
    using size_t           = store_t::size_type;
    using arch_id_t        = store_t::arch_id_t;
    using node_index_t     = store_t::node_index_t;
    using node_set_id_t    = store_t::node_set_id_t;
    using status_t         = store_t::status_t;
    using arch_id_t        = store_t::arch_id_t;
    using ptr_node_set_t   = std::unique_ptr< node_set_t >;

}

TEST( CXX_CommonControlNodeSetSingleTests, CompetingSelectionExtLock )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    namespace st_test = SIXTRL_CXX_NAMESPACE::tests;

    using store_t          = st::NodeStore;
    using node_set_t       = st_test::TestNodeSetSingle;
    using platform_id_t    = st::node_platform_id_t;
    using size_t           = store_t::size_type;
    using arch_id_t        = store_t::arch_id_t;
    using node_index_t     = store_t::node_index_t;
    using node_set_id_t    = store_t::node_set_id_t;
    using status_t         = store_t::status_t;
    using arch_id_t        = store_t::arch_id_t;
    using ptr_node_set_t   = std::unique_ptr< node_set_t >;

}

*/

/* end: tests/sixtracklib/common/control/test_node_set_single_cxx.cpp */
