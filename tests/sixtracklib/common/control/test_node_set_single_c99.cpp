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
#include "sixtracklib/common/architecture/architecture.h"
#include "sixtracklib/common/control/node_info.h"
#include "sixtracklib/common/control/node_store.h"
#include "sixtracklib/testlib.h"

TEST( C99_CommonControlNodeSetSingleTests, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    namespace st_test = SIXTRL_CXX_NAMESPACE::tests;

    using store_t          = ::NS(NodeStore);
    using node_set_t       = ::NS(TestNodeSetSingle);
    using platform_id_t    = ::NS(node_platform_id_t);
    using size_t           = ::NS(arch_size_t);
    using arch_id_t        = ::NS(arch_id_t);
    using node_index_t     = ::NS(node_index_t);
    using node_set_id_t    = ::NS(node_set_id_t);
    using status_t         = ::NS(arch_status_t);

    /* ********************************************************************* */
    /* *****                      Setup tests                          ***** */
    /* ********************************************************************* */

    /* Create a dummy architecture for the unit-test: */

    ::NS(Architectures)* ptr_archs = ::NS(Architectures_get_ptr)();

    static constexpr size_t NUM_ARCHS = size_t{ 1 };
    arch_id_t arch_id = ::NS(NODE_UNDEFINED_INDEX);

    status_t status = ::NS(Architectures_setup)(
        ptr_archs, NUM_ARCHS, arch_id_t{ 32 }, &arch_id );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    /* Create an empty store */

    store_t* store = ::NS(NodeStore_new)();
    ASSERT_TRUE( store != nullptr );

    /* Create a set of nodes */

    static constexpr size_t NUM_NODES = 3;

    const arch_id_t nodes_arch_ids[ NUM_NODES ] =
    {
        arch_id, arch_id, arch_id
    };

    const platform_id_t nodes_platform_ids[ NUM_NODES ] =
    {
        ::NS(NODE_ILLEGAL_PLATFORM_ID), ::NS(NODE_ILLEGAL_PLATFORM_ID),
        ::NS(NODE_ILLEGAL_PLATFORM_ID)
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
               ::NS(NODE_UNDEFINED_INDEX) );

    status = ::NS(TestNodeInfo_add_to_node_store)( store, NUM_NODES,
        &nodes_arch_ids[ 0 ], &nodes_platform_ids[ 0 ],
            &nodes_max_attach_cnt[ 0 ], &nodes_max_selection_cnt[ 0 ],
                &cmp_node_indices[ 0 ] );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    SIXTRL_ASSERT(  ::NS(NodeStore_get_total_num_nodes)( store ) == NUM_NODES );
    SIXTRL_ASSERT( !::NS(NodeStore_has_node_sets)( store ) );

    /* Create a node set */

    node_set_t* set = ::NS(TestNodeSetSingle_create)( store );
    ASSERT_TRUE( set != nullptr );

    node_set_id_t const set_id = ::NS(NodeStore_add_node_set)( store, set );
    SIXTRL_ASSERT( set_id != ::NS(NODE_UNDEFINED_INDEX) );
    SIXTRL_ASSERT( ::NS(NodeStore_has_node_set)( store, set_id ) );
    SIXTRL_ASSERT( ::NS(NodeStore_get_ptr_const_node_set_base)(
        store, set_id ) == set );

    SIXTRL_ASSERT( ::NS(NodeSet_get_node_set_id)( set ) == set_id );

    /* Configure node set to be as restrictive as possible; these restrictions
     * are relaxed over the course of the tests below */

    ::NS(TestNodeSetSingle_set_can_directly_change_selected_node_flag)(
        set, false );
    ::NS(TestNodeSetSingle_set_can_unselect_node_flag)( set, false );
    ::NS(TestNodeSetSingle_set_use_auto_select_flag)( set, false );

    SIXTRL_ASSERT( !::NS(NodeSet_supports_changing_selected_node)( set ) );
    SIXTRL_ASSERT( !::NS(NodeSet_supports_directly_changing_selected_node)(
        set ) );

    SIXTRL_ASSERT( !::NS(NodeSet_supports_unselecting_node)( set ) );
    SIXTRL_ASSERT( !::NS(NodeSet_uses_auto_select)( set ) );

    /* Assign all nodes to the set */

    status = ::NS(NodeStore_attach_all_architecture_nodes_to_set)(
        store, arch_id, set_id );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_num_nodes)( set ) == NUM_NODES );

    for( size_t ii = size_t{ 0 } ; ii < NUM_NODES ; ++ii )
    {
        node_index_t const idx = cmp_node_indices[ ii ];
        ASSERT_TRUE( idx != ::NS(NODE_UNDEFINED_INDEX) );

        ASSERT_TRUE( ::NS(NodeStore_is_node_attached_to_any_set)(
            store, idx ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_any_set)(
            store, idx ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_any_set)(
            store, idx ) );

        ASSERT_TRUE(  ::NS(NodeStore_is_node_attached_to_set)(
            store, idx, set_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
            store, idx, set_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_set)(
            store, idx, set_id ) );

        ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, idx ) );
        ASSERT_TRUE( !::NS(NodeSet_is_default)( set, idx ) );
    }

    node_index_t const node_idx_1 = cmp_node_indices[ 0 ];
    node_index_t const node_idx_2 = cmp_node_indices[ 1 ];
    node_index_t const node_idx_3 = cmp_node_indices[ 2 ];

    /* ********************************************************************* */
    /* *****                    Perform tests                          ***** */
    /* ********************************************************************* */

    ASSERT_TRUE( ::NS(NodeSet_get_selected_node_index)( set ) ==
                 ::NS(NODE_UNDEFINED_INDEX) );

    /* Select first node: */

    bool can_perform_op = ::NS(NodeSet_can_select_node)( set, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = ::NS(NodeSet_select_node)( set, node_idx_1 );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_1 );
    ASSERT_TRUE( ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( ::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Try to select node #1 again. Since this is already selected, it should
     * work */

    can_perform_op = ::NS(NodeSet_can_select_node)( set, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = ::NS(NodeSet_select_node)( set, node_idx_1 );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_1 );
    ASSERT_TRUE( ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( ::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Same again, but this time using the changeSelectedNodeTo() API.
     * This should work because it is actually a NOP */

    can_perform_op = ::NS(NodeSet_can_change_selection_to_node)(
        set, node_idx_1 );

    ASSERT_TRUE( can_perform_op );
    status = ::NS(NodeSet_change_selection_to_node)( set, node_idx_1 );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_selected_node_index)(
        set ) == node_idx_1 );

    ASSERT_TRUE( ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( ::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Try to select node #2. Since change of node and unselection of node
     * is not available, this should not work */

    can_perform_op = ::NS(NodeSet_can_select_node)( set, node_idx_2 );
    ASSERT_TRUE( !can_perform_op );

    status = ::NS(NodeSet_select_node)( set, node_idx_2 );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_1 );
    ASSERT_TRUE( ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( ::NS(NodeSet_is_selected)( set, node_idx_1 ) );

    /* Try to select node #2 by means of the changeSelectedNodeTo() API.
     * Should not work because all capabilities in this regard are disabled */

    can_perform_op = ::NS(NodeSet_can_change_selection_to_node)(
        set, node_idx_2 );

    ASSERT_TRUE( !can_perform_op );

    status = ::NS(NodeSet_change_selection_to_node)( set, node_idx_2 );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_1 );
    ASSERT_TRUE( ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( ::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Try to unselect node #2 -> should not work because we disabled
     * the unselection capabilities above AND because node#2 is not selected */

    can_perform_op = ::NS(NodeSet_can_unselect_node)( set, node_idx_2 );
    ASSERT_TRUE( !can_perform_op );

    status = ::NS(NodeSet_unselect_node)( set, node_idx_2 );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_1 );
    ASSERT_TRUE( ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( ::NS(NodeSet_is_selected)( set, node_idx_1 ) );

    /* Try to unselect node #1 -> should not work because we disabled
     * the unselection capabilities above */

    can_perform_op = ::NS(NodeSet_can_unselect_node)( set, node_idx_1 );
    ASSERT_TRUE( !can_perform_op );

    status = ::NS(NodeSet_unselect_node)( set, node_idx_1 );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_1 );
    ASSERT_TRUE( ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( ::NS(NodeSet_is_selected)( set, node_idx_1 ) );

    /* Enable unselection. This implies enabling the ability to change nodes;
     * directly changing nodes is however a different capability */

    ::NS(TestNodeSetSingle_set_can_unselect_node_flag)( set, true );
    ASSERT_TRUE(  ::NS(NodeSet_supports_unselecting_node)( set ) );
    ASSERT_TRUE(  ::NS(NodeSet_supports_changing_selected_node)( set ) );
    ASSERT_TRUE( !::NS(NodeSet_supports_directly_changing_selected_node)(
        set ) );

    /* Try to unselect node #2 -> should not work because because node#2
     * is not selected */

    can_perform_op = ::NS(NodeSet_can_unselect_node)( set, node_idx_2 );
    ASSERT_TRUE( !can_perform_op );

    status = ::NS(NodeSet_unselect_node)( set, node_idx_2 );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_1 );
    ASSERT_TRUE( ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( ::NS(NodeSet_is_selected)( set, node_idx_1 ) );

    /* Try to unselect node #1 -> should now work  */

    can_perform_op = ::NS(NodeSet_can_unselect_node)( set, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = ::NS(NodeSet_unselect_node)( set, node_idx_1 );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_selected_node_index)( set ) ==
                 ::NS(NODE_UNDEFINED_INDEX) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_any_set)(
        store, node_idx_1 ) );

    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 0 } );

    /* Selecting node #2 now: */

    can_perform_op = ::NS(NodeSet_can_select_node)( set, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = ::NS(NodeSet_select_node)( set, node_idx_2 );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_2 );
    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE(  ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_2, set_id ) );

    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE(  ::NS(NodeSet_is_selected)( set, node_idx_2 ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Try changing to node #3 but from the wrong current node (#1, but #2
     * is selected ) -> regardless of capabilities, this should not work! */

    can_perform_op = ::NS(NodeSet_can_change_selection_from_node_to_node)(
        set, node_idx_1, node_idx_3 );
    ASSERT_TRUE( !can_perform_op );

    status = ::NS(NodeSet_change_selection_from_node_to_node)(
        set, node_idx_1, node_idx_3 );

    ASSERT_TRUE(  status != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_2 );
    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE(  ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_2, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_3, set_id ) );

    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE(  ::NS(NodeSet_is_selected)( set, node_idx_2 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_3 ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Changing to node #3 now should work because we can unselect and
     * then select. Verify that direct change is disabled, though */

    ASSERT_TRUE( !::NS(NodeSet_supports_directly_changing_selected_node)(
        set ) );

    can_perform_op = ::NS(NodeSet_can_change_selection_from_node_to_node)(
        set, node_idx_2, node_idx_3 );
    ASSERT_TRUE( can_perform_op );

    status = ::NS(NodeSet_change_selection_from_node_to_node)(
        set, node_idx_2, node_idx_3 );

    ASSERT_TRUE(  status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_3 );
    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_2, set_id ) );

    ASSERT_TRUE(  ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_3, set_id ) );

    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_2 ) );
    ASSERT_TRUE(  ::NS(NodeSet_is_selected)( set, node_idx_3 ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Use NodeSetSingle changeSelectedNodeTo() which omits the source node
     * index to change back to node #1. Should work */

    can_perform_op = ::NS(NodeSet_can_change_selection_to_node)(
        set, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = ::NS(NodeSet_change_selection_to_node)( set, node_idx_1 );
    ASSERT_TRUE(  status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_1 );
    ASSERT_TRUE(  ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_2, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_3, set_id ) );

    ASSERT_TRUE(  ::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_2 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_3 ) );

    ASSERT_TRUE(  ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Change from node #1 to #2 using the selectNode API; this should work
     * even though node #1 is currently selected as unselecting is enabled */

    can_perform_op = ::NS(NodeSet_can_select_node)( set, node_idx_2 );
    ASSERT_TRUE( can_perform_op );

    status = ::NS(NodeSet_select_node)( set, node_idx_2 );
    ASSERT_TRUE(  status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_2 );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE(  ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_2, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_3, set_id ) );

    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE(  ::NS(NodeSet_is_selected)( set, node_idx_2 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_3 ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Disable unselecting capability. Enable direct changing nodes */

    ::NS(TestNodeSetSingle_set_can_directly_change_selected_node_flag)(
        set, true );

    ::NS(TestNodeSetSingle_set_can_unselect_node_flag)( set, false );

    ASSERT_TRUE(  ::NS(NodeSet_supports_changing_selected_node)( set ) );
    ASSERT_TRUE(  ::NS(NodeSet_supports_directly_changing_selected_node)(
        set ) );

    ASSERT_TRUE( !::NS(NodeSet_supports_unselecting_node)( set ) );

    /* Can not change from node #1 to #3 because, regardless of capabilities,
     * the currently selected node is #2 */

    can_perform_op = ::NS(NodeSet_can_change_selection_from_node_to_node)(
        set, node_idx_1, node_idx_3 );

    ASSERT_TRUE( !can_perform_op );

    status = ::NS(NodeSet_change_selection_from_node_to_node)(
        set, node_idx_1, node_idx_3 );

    ASSERT_TRUE(  status != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_2 );
    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE(  ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_2, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_3, set_id ) );

    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE(  ::NS(NodeSet_is_selected)( set, node_idx_2 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_3 ) );

    ASSERT_TRUE(  ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Change node #2 to node #3.
     * Should work due to directly change capability */

    can_perform_op = ::NS(NodeSet_can_change_selection_from_node_to_node)(
        set, node_idx_2, node_idx_3 );

    ASSERT_TRUE( can_perform_op );

    status = ::NS(NodeSet_change_selection_from_node_to_node)(
        set, node_idx_2, node_idx_3 );

    ASSERT_TRUE(  status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_3 );
    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_2, set_id ) );

    ASSERT_TRUE(  ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_3, set_id ) );

    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_2 ) );
    ASSERT_TRUE(  ::NS(NodeSet_is_selected)( set, node_idx_3 ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Change node #3 to node #1 using selectNode API.
     * Should work due to directly change capability */

    can_perform_op = ::NS(NodeSet_can_select_node)( set, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = ::NS(NodeSet_select_node)( set, node_idx_1 );
    ASSERT_TRUE(  status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_1 );
    ASSERT_TRUE(  ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_2, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_3, set_id ) );

    ASSERT_TRUE(  ::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_2 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_3 ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Enable unselecting nodes and raise the minimum number of selected
     * nodes to 1. This should prevent unselection of nodes even if the
     * capability is granted */

    ::NS(TestNodeSetSingle_set_can_unselect_node_flag)( set, true );
    ::NS(TestNodeSetSingle_set_can_directly_change_selected_node_flag)(
        set, false );

    ::NS(TestNodeSetSingle_set_min_num_selectable_nodes)( set, size_t{ 1 } );

    ASSERT_TRUE( !::NS(NodeSet_supports_directly_changing_selected_node)(
        set ) );

    ASSERT_TRUE(  ::NS(NodeSet_supports_unselecting_node)( set ) );
    ASSERT_TRUE(  ::NS(NodeSet_supports_changing_selected_node)( set ) );
    ASSERT_TRUE( !::NS(NodeSet_uses_auto_select)( set ) );

    ASSERT_TRUE(  ::NS(NodeStore_get_num_default_nodes_for_set)(
        store, set_id ) == size_t{ 0 } );

    ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_any_set)(
        store, node_idx_1 ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE(  ::NS(NodeStore_can_node_be_made_default_for_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE(  ::NS(NodeSet_get_min_num_selectable_nodes)( set ) ==
            ::NS(NodeStore_get_num_selected_nodes_for_set)( store, set_id ) );

    /* Attempt to unselect node_idx_1 -> should not work because doing so
     * would drop the number of selected nodes below the new treshold & there
     * are no default nodes to autoSelect */

    can_perform_op = ::NS(NodeSet_can_unselect_node)( set, node_idx_1 );
    ASSERT_TRUE( !can_perform_op );

    status = ::NS(NodeSet_unselect_node)( set, node_idx_1 );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_1 );
    ASSERT_TRUE(  ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_2, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_3, set_id ) );

    ASSERT_TRUE(  ::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_2 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_3 ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Add node_idx_1 as a default node */

    status = ::NS(TestNodeSetSingle_select_default_node)( set, node_idx_1 );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_default_node_index)( set ) == node_idx_1 );
    ASSERT_TRUE( ::NS(NodeSet_has_default_node)( set ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_default_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    ASSERT_TRUE( ::NS(NodeStore_is_node_default_for_any_set)(
        store, node_idx_1 ) );

    ASSERT_TRUE( ::NS(NodeStore_is_node_default_for_set)(
        store, node_idx_1, set_id ) );

    /* Try to repeat the unselect operation of node_idx_1 ->
     * this should still not be possible as a) autoselect is not enabled and
     * b) unselecting node_idx_1 would result in node_idx_1 being selected
     * again as per default -> this is considered an non-successful op. */

    can_perform_op = ::NS(NodeSet_can_unselect_node)( set, node_idx_1 );
    ASSERT_TRUE( !can_perform_op );

    status = ::NS(NodeSet_unselect_node)( set, node_idx_1 );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_1 );

    ASSERT_TRUE(  ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_2, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_3, set_id ) );

    ASSERT_TRUE(  ::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_2 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_3 ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* enable auto-select */

    ::NS(TestNodeSetSingle_set_use_auto_select_flag)( set, true );
    ASSERT_TRUE( ::NS(NodeSet_uses_auto_select)( set ) );

    /* Try to repeat the unselection again, which still should not work since
     * node_idx_1 is both selected and the default node */

    can_perform_op = ::NS(NodeSet_can_unselect_node)( set, node_idx_1 );
    ASSERT_TRUE( !can_perform_op );

    status = ::NS(NodeSet_unselect_node)( set, node_idx_1 );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_1 );

    ASSERT_TRUE(  ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_2, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_3, set_id ) );

    ASSERT_TRUE(  ::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_2 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_3 ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* Attempting to add a second default node to get out of the dilemma should
     * not work as we are using a NodeSetSingle instance here which has a
     * maximum num of default nodes of 1 */

    status = ::NS(TestNodeSetSingle_select_default_node)( set, node_idx_2 );
    ASSERT_TRUE(  status != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_default_node_index)( set ) == node_idx_1 );
    ASSERT_TRUE(  ::NS(NodeSet_has_default_node)( set ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_default_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    ASSERT_TRUE(  ::NS(NodeStore_is_node_default_for_any_set)(
        store, node_idx_1 ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_any_set)(
        store, node_idx_2 ) );

    ASSERT_TRUE(  ::NS(NodeStore_is_node_default_for_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_set)(
        store, node_idx_2, set_id ) );

    /* Remove node #1 as default node first, then try to set node #2 as default
     * node */

    status = ::NS(TestNodeSetSingle_remove_default_node)( set );
    ASSERT_TRUE(  status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_default_node_index)( set ) ==
                  ::NS(NODE_UNDEFINED_INDEX) );
    ASSERT_TRUE( !::NS(NodeSet_has_default_node)( set ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_default_nodes_for_set)(
                  store, set_id ) == size_t{ 0 } );

    ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_any_set)(
                 store, node_idx_1 ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_any_set)(
                  store, node_idx_2 ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_set)(
                 store, node_idx_1, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_set)(
                 store, node_idx_2, set_id ) );

    status = ::NS(TestNodeSetSingle_select_default_node)( set, node_idx_2 );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeSet_get_default_node_index)( set ) == node_idx_2 );
    ASSERT_TRUE( ::NS(NodeSet_has_default_node)( set ) );
    ASSERT_TRUE( ::NS(NodeStore_get_num_default_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    ASSERT_TRUE( ::NS(NodeStore_is_node_default_for_any_set)(
        store, node_idx_2 ) );

    ASSERT_TRUE( ::NS(NodeStore_is_node_default_for_set)(
        store, node_idx_2, set_id ) );

    /* Now, unselection should work. We expect the selection to switch to
     * node #2 if we unselect node #1: */

    can_perform_op = ::NS(NodeSet_can_unselect_node)( set, node_idx_1 );
    ASSERT_TRUE( can_perform_op );

    status = ::NS(NodeSet_unselect_node)( set, node_idx_1 );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)( set ) == node_idx_2 );
    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_1, set_id ) );

    ASSERT_TRUE(  ::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_2, set_id ) );

    ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
        store, node_idx_3, set_id ) );

    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_1 ) );
    ASSERT_TRUE(  ::NS(NodeSet_is_selected)( set, node_idx_2 ) );
    ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, node_idx_3 ) );
    ASSERT_TRUE(  ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 1 } );

    /* detach all nodes from set */

    status = ::NS(NodeStore_detach_all_nodes_from_set)( store, set_id );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE( ::NS(NodeStore_has_node_set)( store, set_id ) );
    ASSERT_TRUE( ::NS(NodeStore_get_ptr_const_node_set_base)(
        store, set_id ) == set );

    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes)( store, arch_id ) == NUM_NODES );
    ASSERT_TRUE( ::NS(NodeStore_get_num_nodes_for_set)(
        store, set_id ) == size_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeStore_get_num_selected_nodes_for_set)(
        store, set_id ) == size_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeStore_get_num_default_nodes_for_set)(
        store, set_id ) == size_t{ 0 } );

    ASSERT_TRUE(  ::NS(NodeSet_get_num_nodes)( set ) == size_t{ 0 } );
    ASSERT_TRUE(  ::NS(NodeSet_get_selected_node_index)(
        set ) == ::NS(NODE_UNDEFINED_INDEX) );

    ASSERT_TRUE(  ::NS(NodeSet_get_default_node_index)(
        set ) == ::NS(NODE_UNDEFINED_INDEX) );

    for( size_t ii = size_t{ 0 } ; ii < NUM_NODES ; ++ii )
    {
        node_index_t const index = cmp_node_indices[ ii ];
        ASSERT_TRUE( index != ::NS(NODE_UNDEFINED_INDEX) );
        ASSERT_TRUE(  ::NS(NodeStore_is_node_available)( store, index ) );
        ASSERT_TRUE( !::NS(NodeStore_is_node_attached_to_any_set)(
            store, index ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_attached_to_set)(
            store, index, set_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_any_set)(
            store, index ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_selected_by_set)(
            store, index, set_id ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_any_set)(
            store, index ) );

        ASSERT_TRUE( !::NS(NodeStore_is_node_default_for_set)(
            store, index, set_id ) );

        ASSERT_TRUE( ::NS(NodeStore_get_num_sets_attached_to_node)(
            store, index ) == size_t{ 0 } );

        ASSERT_TRUE( ::NS(NodeStore_get_num_selecting_sets_for_node)(
            store, index ) == size_t{ 0 } );

        ASSERT_TRUE( ::NS(NodeStore_get_num_sets_having_node_as_default)(
            store, index ) == size_t{ 0 } );

        ASSERT_TRUE( !::NS(NodeSet_is_selected)( set, index ) );
        ASSERT_TRUE( !::NS(NodeSet_is_default)( set, index ) );
    }

    /* --------------------------------------------------------------------- */
    /* Cleanup */

    ::NS(NodeStore_delete)( store );
}

TEST( C99_CommonControlNodeSetSingleTests, SelectNodesConflicting )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    namespace st_test = SIXTRL_CXX_NAMESPACE::tests;

    using store_t          = ::NS(NodeStore);
    using node_set_t       = ::NS(TestNodeSetSingle);
    using platform_id_t    = ::NS(node_platform_id_t);
    using size_t           = ::NS(arch_size_t);
    using arch_id_t        = ::NS(arch_id_t);
    using node_index_t     = ::NS(node_index_t);
    using node_set_id_t    = ::NS(node_set_id_t);
    using status_t         = ::NS(arch_status_t);

    /* ********************************************************************* */
    /* *****                      Setup tests                          ***** */
    /* ********************************************************************* */

    /* Create a dummy architecture for the unit-test: */

    ::NS(Architectures)* ptr_archs = ::NS(Architectures_get_ptr)();

    static constexpr size_t NUM_ARCHS = size_t{ 1 };
    arch_id_t arch_id = ::NS(NODE_UNDEFINED_INDEX);

    status_t status = ::NS(Architectures_setup)(
        ptr_archs, NUM_ARCHS, arch_id_t{ 32 }, &arch_id );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    /* Create an empty store */

    store_t* store = ::NS(NodeStore_new)();
    ASSERT_TRUE( store != nullptr );

    /* Create a set of nodes */

    static constexpr size_t NUM_NODES = 3;

    const arch_id_t nodes_arch_ids[ NUM_NODES ] =
    {
        arch_id, arch_id, arch_id
    };

    const platform_id_t nodes_platform_ids[ NUM_NODES ] =
    {
        ::NS(NODE_ILLEGAL_PLATFORM_ID), ::NS(NODE_ILLEGAL_PLATFORM_ID),
        ::NS(NODE_ILLEGAL_PLATFORM_ID)
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
               ::NS(NODE_UNDEFINED_INDEX) );

    status = ::NS(TestNodeInfo_add_to_node_store)( store, NUM_NODES,
        &nodes_arch_ids[ 0 ], &nodes_platform_ids[ 0 ],
            &nodes_max_attach_cnt[ 0 ], &nodes_max_selection_cnt[ 0 ],
                &cmp_node_indices[ 0 ] );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    SIXTRL_ASSERT(  ::NS(NodeStore_get_total_num_nodes)( store ) == NUM_NODES );
    SIXTRL_ASSERT( !::NS(NodeStore_has_node_sets)( store ) );

    /* Create a node set */

    node_set_t* set = ::NS(TestNodeSetSingle_create)( store );
    ASSERT_TRUE( set != nullptr );

    node_set_id_t const set_id = ::NS(NodeStore_add_node_set)( store, set );
    SIXTRL_ASSERT( set_id != ::NS(NODE_UNDEFINED_INDEX) );
    SIXTRL_ASSERT( ::NS(NodeStore_has_node_set)( store, set_id ) );
    SIXTRL_ASSERT( ::NS(NodeStore_get_ptr_const_node_set_base)(
        store, set_id ) == set );

    SIXTRL_ASSERT( ::NS(NodeSet_get_node_set_id)( set ) == set_id );

    /* --------------------------------------------------------------------- */
    /* Cleanup */

    ::NS(NodeStore_delete)( store );
}

/* end: tests/sixtracklib/common/control/test_node_set_single_cxx.cpp */
