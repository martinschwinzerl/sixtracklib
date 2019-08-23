#include "sixtracklib/common/control/node_set.h"
#include "sixtracklib/common/control/node_set.hpp"

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstdbool>
    #include <cstddef>
    #include <cstdlib>
    #include <memory>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/architecture/definitions.h"
    #include "sixtracklib/common/architecture/architecture.hpp"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/node_store.hpp"
    #include "sixtracklib/common/control/node_info.hpp"
    #include "sixtracklib/common/control/node_id.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace    st = SIXTRL_CXX_NAMESPACE;
using _base_t   = st::NodeSetBase;
using _single_t = st::NodeSetSingle;

#if !defined( _GPUCODE )

::NS(NodeSetBase)* NS(NodeSet_new)( ::NS(NodeStore)* SIXTRL_RESTRICT store )
{
    return ( store != nullptr ) ? new st::NodeSetBase( *store ) : nullptr;
}

::NS(node_set_id_t) NS(NodeSet_get_node_set_id)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( set != nullptr ) ? set->nodeSetId() : _base_t::ILLEGAL_NODE_SET_ID;
}

::NS(arch_status_t) NS(NodeSet_set_node_set_id)(
    ::NS(NodeSetBase)* SIXTRL_RESTRICT set,
    ::NS(node_set_id_t) const node_set_id )
{
    _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

    if( ( set != nullptr ) && ( set->ptrNodeStore() != nullptr ) &&
        ( set->lockable() != nullptr ) )
    {
        _base_t::lock_t const lock( *set->lockable() );
        status = set->setNodeSetId( lock, node_set_id );
    }

    return status;
}

void NS(NodeSet_delete)( ::NS(NodeSetBase)* SIXTRL_RESTRICT set )
{
    if( set != nullptr ) delete set;
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(NodeSet_get_num_nodes)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( set != nullptr ) ? set->numNodes() : st::arch_size_t{ 0 };
}

::NS(node_index_t) NS(NodeSet_get_min_node_index)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( set != nullptr ) ? set->minNodeIndex() : _base_t::UNDEFINED_INDEX;
}

::NS(node_index_t) NS(NodeSet_get_max_node_index)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( set != nullptr ) ? set->maxNodeIndex() : _base_t::UNDEFINED_INDEX;
}

::NS(node_index_t) NS(NodeSet_get_node_index)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::NS(arch_size_t) const nn )
{
    return ( set != nullptr ) ? set->nodeIndex( nn ) : _base_t::UNDEFINED_INDEX;
}

::NS(NodeId) const* NS(NodeSet_get_node_id)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::NS(arch_size_t) const nn )
{
    return ( set != nullptr ) ? set->ptrCNodeId( nn ) : nullptr;
}

::NS(NodeId) const* NS(NodeSet_get_node_id_by_node_index)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::NS(node_index_t) const node_index )
{
    return ( set != nullptr )
        ? set->ptrCNodeIdByNodeIndex( node_index ) : nullptr;
}

bool NS(NodeSet_is_node_available)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::NS(node_index_t) const node_index )
{
    return ( ( set != nullptr ) && ( set->available( node_index ) ) );
}

/* ------------------------------------------------------------------------- */

bool NS(NodeSet_uses_auto_select)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( ( set != nullptr ) && ( set->usesAutoSelect() ) );
}

bool NS(NodeSet_is_selected)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::NS(node_index_t) const node_index )
{
    return ( ( set != nullptr ) && ( set->isSelected( node_index ) ) );
}

bool NS(NodeSet_can_select_node)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::NS(node_index_t) const node_index )
{
    return ( ( set != nullptr ) && ( set->canSelectNode( node_index ) ) );
}

::NS(arch_size_t) NS(NodeSet_get_min_num_selectable_nodes)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( set != nullptr )
        ? set->minNumSelectableNodes() : st::arch_size_t{ 0 };
}

::NS(arch_size_t) NS(NodeSet_get_max_num_selectable_nodes)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( set != nullptr )
        ? set->maxNumSelectableNodes() : st::arch_size_t{ 0 };
}

/* ------------------------------------------------------------------------- */

bool NS(NodeSet_is_default)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::NS(node_index_t) const node_index )
{
    return ( ( set != nullptr ) && ( set->isDefault( node_index ) ) );
}

::NS(arch_size_t) NS(NodeSet_get_min_num_default_nodes)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( set != nullptr )
        ? set->minNumDefaultNodes() : st::arch_size_t{ 0 };
}

::NS(arch_size_t) NS(NodeSet_get_max_num_default_nodes)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( set != nullptr )
        ? set->maxNumDefaultNodes() : st::arch_size_t{ 0 };
}

/* ------------------------------------------------------------------------- */

bool NS(NodeSet_supports_changing_selected_node)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( ( set != nullptr ) && ( set->supportsChangingSelectedNode() ) );
}

bool NS(NodeSet_supports_directly_changing_selected_node)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( ( set != nullptr ) &&
             ( set->supportsDirectlyChangingSelectedNode() ) );
}

bool NS(NodeSet_can_change_selection_from_node_to_node)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::NS(node_index_t) const current_node_idx,
    ::NS(node_index_t) const next_node_idx )
{
    return ( ( set != nullptr ) && ( set->canChangeSelectedNodeTo(
        current_node_idx, next_node_idx ) ) );
}

::NS(arch_status_t) NS(NodeSet_change_selection_from_node_to_node)(
    ::NS(NodeSetBase)* SIXTRL_RESTRICT set,
    ::NS(node_index_t) const current_node_idx,
    ::NS(node_index_t) const next_node_idx )
{
    return ( set != nullptr )
        ? set->changeSelectedNodeTo( current_node_idx, next_node_idx )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeSet_supports_unselecting_node)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( ( set != nullptr ) && ( set->supportsUnselectingNode() ) );
}

bool NS(NodeSet_can_unselect_node)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::NS(node_index_t) const index )
{
    return ( ( set != nullptr ) && ( set->canUnselectNode( index ) ) );
}

::NS(arch_status_t) NS(NodeSet_unselect_node)(
    ::NS(NodeSetBase)* SIXTRL_RESTRICT set,
    ::NS(node_index_t) const node_index )
{
    return ( set != nullptr )
        ? set->unselectNode( node_index ) : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeSet_is_sync_with_store)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( ( set != nullptr) && ( set->isSyncWithStore() ) );
}

::NS(arch_status_t) NS(NodeSet_sync_with_store)(
    ::NS(NodeSetBase)* SIXTRL_RESTRICT set )
{
    return ( set != nullptr )
        ? set->syncWithStore() : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(NodeSet_required_out_string_length)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( set != nullptr )
        ? set->requiredOutStringLength() : st::arch_size_t{ 0 };
}

void NS(NodeSet_print)( const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::FILE* SIXTRL_RESTRICT output )
{
    if( set != nullptr ) set->print( output );
}

void NS(NodeSet_print_out)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    if( set != nullptr ) set->printOut();
}

::NS(arch_status_t) NS(NodeSet_to_string)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::NS(arch_size_t) const out_str_capacity, char* SIXTRL_RESTRICT out_str )
{
    return ( set != nullptr )
        ? set->toString( out_str_capacity, out_str )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

::NS(NodeStore) const* NS(NodeSet_get_ptr_const_node_store)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return ( set != nullptr ) ? set->ptrNodeStore() : nullptr;
}

::NS(NodeStore)* NS(NodeSet_get_ptr_node_store)(
    ::NS(NodeSetBase)* SIXTRL_RESTRICT set )
{
    return ( set != nullptr ) ? set->ptrNodeStore() : nullptr;
}

/* ************************************************************************* */
/* NodeSetSingle: */

bool NS(NodeSet_is_node_set_single)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return st::NodeSet_is_node_set_single( set );
}

::NS(NodeSetSingle) const* NS(NodeSet_as_const_node_set_single)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    return st::NodeSet_as_node_set_single( set );
}

::NS(NodeSetSingle)* NS(NodeSet_as_node_set_single)(
    ::NS(NodeSetBase)* SIXTRL_RESTRICT set )
{
    return st::NodeSet_as_node_set_single( set );
}

/* ------------------------------------------------------------------------ */

::NS(NodeSetSingle)* NS(NodeSetSingle_new)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store )
{
    return ( node_store != nullptr )
        ? new st::NodeSetSingle( *node_store ) : nullptr;
}

::NS(node_index_t) NS(NodeSet_get_selected_node_index)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    _single_t const* ptr = st::NodeSet_as_node_set_single( set );
    return ( ptr != nullptr )
        ? ptr->selectedNodeIndex() : _single_t::UNDEFINED_INDEX;
}

::NS(NodeId) const* NS(NodeSet_get_selected_node_id)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    _single_t const* ptr = st::NodeSet_as_node_set_single( set );
    return ( ptr != nullptr ) ? ptr->ptrSelectedCNodeId() : nullptr;
}

::NS(arch_status_t) NS(NodeSet_select_node)(
    ::NS(NodeSetBase)* SIXTRL_RESTRICT set,
    ::NS(node_index_t) const node_index )
{
    _single_t* ptr = st::NodeSet_as_node_set_single( set );
    return ( ptr != nullptr )
        ? ptr->selectNode( node_index ) : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

::NS(node_index_t) NS(NodeSet_get_default_node_index)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    _single_t const* ptr = st::NodeSet_as_node_set_single( set );
    return ( ptr != nullptr )
        ? ptr->defaultNodeIndex() : _single_t::UNDEFINED_INDEX;
}

::NS(NodeId) const* NS(NodeSet_get_default_node_id)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    _single_t const* ptr = st::NodeSet_as_node_set_single( set );
    return ( ptr != nullptr ) ? ptr->ptrDefaultCNodeId() : nullptr;
}

bool NS(NodeSet_has_default_node)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set )
{
    _single_t const* ptr = st::NodeSet_as_node_set_single( set );
    return ( ( ptr != nullptr ) && ( ptr->hasDefaultNode() ) );
}

/* ------------------------------------------------------------------------- */

bool NS(NodeSet_can_change_selection_to_node)(
    const ::NS(NodeSetBase) *const SIXTRL_RESTRICT set,
    ::NS(node_index_t) const index )
{
    _single_t const* ptr = st::NodeSet_as_node_set_single( set );
    return ( ( ptr != nullptr ) && ( ptr->canChangeSelectedNodeTo( index ) ) );
}

::NS(arch_status_t) NS(NodeSet_change_selection_to_node)(
    ::NS(NodeSetBase)* SIXTRL_RESTRICT set,
    ::NS(node_index_t) const index )
{
    _single_t* ptr = st::NodeSet_as_node_set_single( set );
    return ( ptr != nullptr ) ? ptr->changeSelectedNodeTo( index )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

#endif /* !defiend( _GPUCODE ) */

/* end: sixtracklib/common/control/node_set_c99.cpp */
