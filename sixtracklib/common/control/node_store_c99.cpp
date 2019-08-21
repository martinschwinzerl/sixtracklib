#include "sixtracklib/common/control/node_store.h"

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <utility>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/common/control/node_id.hpp"
#include "sixtracklib/common/control/node_store.hpp"
#include "sixtracklib/common/control/node_info.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;
using _store_t = st::NodeStore;

::NS(NodeStore)* NS(NodeStore_get_global_ptr)( void )
{
    return st::NodeStore_get_ptr();
}

::NS(NodeStore) const* NS(NodeStore_get_global_const_ptr)( void )
{
    return st::NodeStore_get_const_ptr();
}

/* ------------------------------------------------------------------------- */

::NS(NodeStore)* NS(NodeStore_new)()
{
    return new st::NodeStore;
}

void NS(NodeStore_delete)( ::NS(NodeStore)* SIXTRL_RESTRICT store )
{
    delete store;
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(NodeStore_get_num_architectures)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store )
{
    return ( node_store != nullptr )
        ? node_store->numArchitectures() : ::NS(arch_size_t){ 0 };
}

bool NS(NodeStore_has_architecture)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id )
{
    return ( ( node_store != nullptr) &&
             ( node_store->hasArchitecture( arch_id ) ) );
}

::NS(arch_status_t) NS(NodeStore_get_architecture_ids)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_size_t) const max_num_arch_ids,
    NS(arch_id_t)* SIXTRL_RESTRICT arch_ids_begin,
    ::NS(arch_size_t)* SIXTRL_RESTRICT ptr_num_archs )
{
    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    if( ( node_store != nullptr ) && ( arch_ids_begin != nullptr ) &&
        ( max_num_arch_ids > ::NS(arch_size_t){ 0 } ) )
    {
        status = node_store->architectureIds(
            arch_ids_begin, arch_ids_begin + max_num_arch_ids, ptr_num_archs );
    }

    return status;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeStore_has_platform)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id, ::NS(node_platform_id_t) const platform_id )
{
    return ( ( node_store ) &&
             ( node_store->hasPlatform( arch_id, platform_id ) ) );
}

::NS(arch_size_t) NS(NodeStore_get_num_platforms)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id )
{
    return ( node_store != nullptr )
        ? node_store->numPlatforms( arch_id ) : ::NS(arch_size_t){ 0 };
}

/* ------------------------------------------------------------------------- */

::NS(node_index_t) NS(NodeStore_find_node_index_by_node_id)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    const NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    return ( ( node_store != nullptr ) && ( node_id != nullptr ) )
        ? node_store->findNodeIndex( node_id ) : st::NodeStore::UNDEFINED_INDEX;
}

::NS(node_index_t) NS(NodeStore_find_node_index_by_arch_platform_device_ids)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id, ::NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    return ( node_store != nullptr )
        ? node_store->findNodeIndex( arch_id, platform_id, device_id )
        : st::NodeStore::UNDEFINED_INDEX;
}

::NS(node_index_t) NS(NodeStore_find_node_index_by_node_info)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    const NS(NodeInfoBase) *const SIXTRL_RESTRICT ptr_node_info )
{
    return ( node_store != nullptr )
        ? node_store->findNodeIndex( ptr_node_info )
        : st::NodeStore::UNDEFINED_INDEX;
}

::NS(node_index_t) NS(NodeStore_find_node_index)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    char const* SIXTRL_RESTRICT node_id_str )
{
    return ( node_store != nullptr )
        ? node_store->findNodeIndex( node_id_str )
        : st::NodeStore::UNDEFINED_INDEX;
}

::NS(node_index_t) NS(NodeStore_find_node_index_by_arch_node_id_str)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id,
    char const* SIXTRL_RESTRICT node_id_str )
{
    return ( node_store != nullptr )
        ? node_store->findNodeIndex( arch_id, node_id_str )
        : st::NodeStore::UNDEFINED_INDEX;
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(NodeStore_get_total_num_nodes)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store )
{
    return ( node_store != nullptr )
        ? node_store->totalNumNodes() : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(NodeStore_get_num_nodes)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id )
{
    return ( node_store != nullptr )
        ? node_store->numNodes( arch_id ) : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(NodeStore_get_num_nodes_for_platform)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id, ::NS(node_platform_id_t) const platform_id )
{
    return ( node_store != nullptr )
        ? node_store->numNodes( arch_id, platform_id )
        : ::NS(arch_size_t){ 0 };
}

::NS(node_index_t) NS(NodeStore_get_min_attached_node_index)(
    const NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    NS(node_set_id_t) const node_set_id )
{
    return ( node_store != nullptr )
        ? node_store->minAttachedNodeIndex( node_set_id )
        : _store_t::UNDEFINED_INDEX;
}

::NS(node_index_t) NS(NodeStore_get_max_attached_node_index)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_set_id_t) const node_set_id )
{
    return ( node_store != nullptr )
        ? node_store->maxAttachedNodeIndex( node_set_id )
        : _store_t::UNDEFINED_INDEX;
}

::NS(arch_size_t) NS(NodeStore_get_num_nodes_for_set)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_set_id_t) const node_set_id )
{
    return ( node_store != nullptr )
        ? node_store->numNodes( node_set_id ) : st::arch_size_t{ 0 };
}

::NS(arch_size_t) NS(NodeStore_get_num_selected_nodes_for_set)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_set_id_t) const node_set_id )
{
    return ( node_store != nullptr )
        ? node_store->numSelectedNodes( node_set_id ) : st::arch_size_t{ 0 };
}

::NS(arch_size_t) NS(NodeStore_get_num_default_nodes_for_set)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_set_id_t) const node_set_id )
{
    return ( node_store != nullptr )
        ? node_store->numDefaultNodes( node_set_id ) : st::arch_size_t{ 0 };
}

/* ------------------------------------------------------------------------- */

::NS(arch_status_t) NS(NodeStore_get_all_node_indices)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_size_t) const max_num_node_indices,
    ::NS(node_index_t)* SIXTRL_RESTRICT node_indices_begin,
    ::NS(arch_size_t)* SIXTRL_RESTRICT ptr_num_node_indices )
{
    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    if( ( node_store != nullptr ) && ( node_indices_begin != nullptr ) &&
        ( max_num_node_indices > ::NS(arch_size_t){ 0 } ) )
    {
        status = node_store->architectureIds(
            node_indices_begin, node_indices_begin + max_num_node_indices,
            ptr_num_node_indices );
    }

    return status;
}

::NS(arch_status_t) NS(NodeStore_get_node_indices_for_architecture)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t)* SIXTRL_RESTRICT node_indices_begin,
    ::NS(arch_size_t) const max_num_node_indices,
    ::NS(arch_id_t) const arch_id,
    ::NS(arch_size_t)* SIXTRL_RESTRICT ptr_num_node_indices )
{
    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    if( ( node_store != nullptr ) && ( node_indices_begin != nullptr ) &&
        ( max_num_node_indices > ::NS(arch_size_t){ 0 } ) )
    {
        status = node_store->nodeIndices( node_indices_begin,
            node_indices_begin + max_num_node_indices, arch_id,
                ptr_num_node_indices );
    }

    return status;
}

::NS(arch_status_t) NS(NodeStore_get_node_indices_for_platform)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_size_t) const max_num_node_indices,
    ::NS(node_index_t)* SIXTRL_RESTRICT node_indices_begin,
    ::NS(arch_id_t) const arch_id, ::NS(node_platform_id_t) const platform_id,
    ::NS(arch_size_t)* SIXTRL_RESTRICT ptr_num_node_indices )
{
    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    if( ( node_store != nullptr ) && ( node_indices_begin != nullptr ) &&
        ( max_num_node_indices > ::NS(arch_size_t){ 0 } ) )
    {
        status = node_store->nodeIndices( node_indices_begin,
            node_indices_begin + max_num_node_indices, arch_id, platform_id,
                ptr_num_node_indices );
    }

    return status;
}

::NS(arch_status_t) NS(NodeStore_get_node_indices_for_set)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_size_t) const max_num_node_indices,
    ::NS(node_index_t)* SIXTRL_RESTRICT node_indices_begin,
    ::NS(node_set_id_t) const node_set_id,
    ::NS(arch_size_t)* SIXTRL_RESTRICT ptr_num_node_indices )
{
    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    if( ( node_store != nullptr ) &&
        ( node_set_id != _store_t::ILLEGAL_NODE_SET_ID ) &&
        ( node_indices_begin != nullptr ) &&
        ( max_num_node_indices > ::NS(arch_size_t){ 0 } ) )
    {
        status = node_store->nodeIndices( node_indices_begin,
            node_indices_begin + max_num_node_indices, node_set_id,
                ptr_num_node_indices );
    }

    return status;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeStore_is_node_available)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( ( node_store != nullptr ) &&
        ( node_store->isNodeAvailable( node_index ) ) );
}

::NS(NodeId) const* NS(NodeStore_get_ptr_const_node_id)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( node_store != nullptr )
        ? node_store->ptrNodeId( node_index ) : nullptr;
}

::NS(NodeInfoBase) const* NS(NodeStore_get_ptr_const_node_info_base)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( node_store != nullptr )
        ? node_store->ptrNodeInfoBase( node_index ) : nullptr;
}

::NS(NodeInfoBase) const* NS(NodeStore_get_ptr_node_info_base)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const index )
{
    return ( node_store != nullptr )
        ? node_store->ptrNodeInfoBase( index ) : nullptr;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeStore_has_node_sets)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store )
{
    return ( ( node_store != nullptr ) && ( node_store->hasNodeSets() ) );
}

::NS(arch_size_t) NS(NodeStore_get_num_node_sets)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store )
{
    return ( node_store )
        ? node_store->numNodeSets() : st::ARCH_STATUS_GENERAL_FAILURE;
}

bool NS(NodeStore_has_node_set)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_set_id_t) const set_id )
{
    return ( ( node_store ) && ( node_store->hasNodeSet( set_id ) ) );
}

bool NS(NodeStore_has_node_set_by_ptr)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(NodeSetBase)* SIXTRL_RESTRICT node_set )
{
    return ( ( node_store != nullptr ) && ( node_set != nullptr ) &&
             ( node_store->hasNodeSet( *node_set ) ) );
}

::NS(node_set_id_t) NS(NodeStore_add_node_set)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(NodeSetBase)* SIXTRL_RESTRICT ptr_node_set_to_store )
{
    _store_t::node_set_id_t node_set_id = _store_t::ILLEGAL_NODE_SET_ID;

    if( ( node_store != nullptr ) && ( ptr_node_set_to_store != nullptr ) )
    {
        std::unique_ptr< _store_t::node_set_base_t > ptr(
            ptr_node_set_to_store );

        if( ptr.get() == ptr_node_set_to_store )
        {
            node_set_id = node_store->addNodeSet( std::move( ptr ) );
        }
    }

    return node_set_id;
}

::NS(arch_status_t) NS(NodeStore_remove_node_set)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_set_id_t) const set_id )
{
    return ( node_store != nullptr )
        ? node_store->removeNodeSet( set_id ) : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(node_set_id_t) NS(NodeStore_get_node_set_id)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(NodeSetBase)* SIXTRL_RESTRICT node_set )
{
    return ( ( node_store != nullptr ) && ( node_set != nullptr ) )
        ? node_store->nodeSetId( *node_set ) : _store_t::ILLEGAL_NODE_SET_ID;
}

::NS(NodeSetBase)* NS(NodeStore_get_ptr_node_set)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_set_id_t) const node_set_id )
{
    return ( node_store != nullptr )
        ? node_store->ptrNodeSetBase( node_set_id ) : nullptr;
}

::NS(NodeSetBase) const* NS(NodeStore_get_ptr_const_node_set_base)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_set_id_t) const node_set_id )
{
    return ( node_store != nullptr )
        ? node_store->ptrNodeSetBase( node_set_id ) : nullptr;
}

/* ------------------------------------------------------------------------- */

::NS(node_index_t) NS(NodeStore_add_node)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(NodeInfoBase)* SIXTRL_RESTRICT ptr_node_info_to_store )
{
    _store_t::node_index_t node_index = _store_t::UNDEFINED_INDEX;

    if( ( node_store != nullptr ) && ( ptr_node_info_to_store != nullptr ) )
    {
        std::unique_ptr< ::NS(NodeInfoBase) > ptr( ptr_node_info_to_store );

        if( ptr.get() == ptr_node_info_to_store )
        {
            node_index = node_store->addNode( std::move( ptr ) );
        }
    }

    return node_index;
}

::NS(arch_status_t) NS(NodeStore_remove_node)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( node_store != nullptr ) ? node_store->removeNode( node_index )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeStore_attach_node_to_set)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index,
    ::NS(node_set_id_t) const set_id )
{
    return ( node_store != nullptr )
        ? node_store->attachNodeToSet( node_index, set_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeStore_attach_all_architecture_nodes_to_set)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id, ::NS(node_set_id_t) const node_set_id )
{
    return ( node_store != nullptr )
        ? node_store->attachAllArchitectureNodesToSet( arch_id, node_set_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeStore_detach_node_from_set)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index,
    ::NS(node_set_id_t) const node_set_id )
{
    return ( node_store != nullptr )
        ? node_store->detachNodeFromSet( node_index, node_set_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeStore_detach_all_nodes_from_set)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_set_id_t) const set_id )
{
    return ( node_store != nullptr )
        ? node_store->detachAllNodesFromSet( set_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeStore_detach_node_from_all_sets)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( node_store != nullptr )
        ? node_store->detachNodeFromAllSets( node_index )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_size_t) NS(NodeStore_num_sets_attached_to_node)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( node_store != nullptr )
        ? node_store->numSetsAttachedToNode( node_index ) : st::arch_size_t{ 0 };
}

bool NS(NodeStore_is_node_attached_to_any_set)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( ( node_store != nullptr ) &&
        ( node_store->isNodeAttachedToAnySet( node_index ) ) );
}

bool NS(NodeStore_is_node_attached_to_set)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index,
    ::NS(node_set_id_t) const node_set_id )
{
    return ( ( node_store != nullptr ) &&
        ( node_store->isNodeAttachedToSet( node_index, node_set_id ) ) );
}

bool NS(NodeStore_can_node_be_selected_by_set)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const index, ::NS(node_set_id_t) const node_set_id )
{
    return ( ( node_store != nullptr ) &&
             ( node_store->canNodeBeSelectedBySet( index, node_set_id ) ) );
}

bool NS(NodeStore_is_node_selected_by_set)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index, ::NS(node_set_id_t) const set_id )
{
    return ( ( node_store != nullptr ) &&
             ( node_store->isNodeSelectedBySet( node_index, set_id ) ) );
}

bool NS(NodeStore_is_node_selected_by_any_set)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( ( node_store != nullptr ) &&
             ( node_store->isNodeSelectedByAnySet( node_index ) ) );
}

::NS(arch_size_t) NS(NodeStore_num_selecting_sets_for_node)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( node_store != nullptr )
        ? node_store->numSelectingSetsForNode( node_index )
        : st::arch_size_t{ 0 };
}

bool NS(NodeStore_is_node_default_for_set)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index, ::NS(node_set_id_t) const set_id )
{
    return ( ( node_store != nullptr ) &&
             ( node_store->isNodeDefaultForSet( node_index, set_id ) ) );
}

bool NS(NodeStore_is_node_default_for_any_set)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( ( node_store != nullptr ) &&
             ( node_store->isNodeDefaultForAnySet( node_index ) ) );
}

::NS(arch_size_t) NS(NodeStore_get_num_sets_having_node_as_default)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const index )
{
    return ( node_store != nullptr )
        ? node_store->numSetsHavingNodeAsDefault( index )
        : st::arch_size_t{ 0 };
}

/* ------------------------------------------------------------------------- */

void NS(NodeStore_clear)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store )
{
    if( node_store != nullptr ) node_store->clear();
}

/* ------------------------------------------------------------------------- */

SIXTRL_UINT64_T NS(NodeStore_get_sync_id_value)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store )
{
    return ( node_store != nullptr )
        ? node_store->syncIdValue() : _store_t::ILLEGAL_SYNC_ID_VALUE;
}

bool NS(NodeStore_is_sync_with)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    SIXTRL_UINT64_T const sync_id_value )
{
    return ( ( node_store != nullptr ) &&
             ( node_store->isSyncWith( sync_id_value ) ) );
}

/* end: sixtracklib/common/control/node_store_c99.cpp */
