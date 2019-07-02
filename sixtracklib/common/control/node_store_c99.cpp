#include "sixtracklib/common/control/node_store.h"

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <utility>


#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/controller_base.h"
#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/common/control/node_store.hpp"
#include "sixtracklib/common/control/node_info.hpp"

#include "sixtracklib/common/control/controller_base.hpp"
#include "sixtracklib/common/control/node_controller_base.hpp"
#include "sixtracklib/common/control/node_id.hpp"
#include "sixtracklib/common/control/node_info.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;


::NS(NodeStore)* NS(NodeStore_get_ptr)( void )
{
    return st::NodeStore_get_ptr();
}

::NS(NodeStore) const* NS(NodeStore_get_const_ptr)( void )
{
    return return st::NodeStore_get_const_ptr();
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(NodeStore_get_num_architectures)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store )
{
    return ( node_store != nullptr )
        ? node->numArchitectures() : ::NS(arch_size_t){ 0 };
}

bool NS(NodeStore_has_architecture)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id )
{
    return ( ( node_store != nullptr) &&
             ( node_store->hasArchitecture( arch_id ) );
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
            arch_ids_begin, arch_ids_begin, + max_num_arch_ids,
                ptr_num_archs );
    }

    return status;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeStore_has_platform)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id, ::NS(node_platform_id_t) const platform_id )
{
    return ( ( node_store ) &&
             ( node_store->hasPlatform( arch_id, platform_id ) );
}

bool NS(NodeStore_has_platform_by_name)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id,
    char const* SIXTRL_RESTRICT platform_name_str )
{
    return ( ( node_store ) &&
             ( node_store->hasPlatform( arch_id, platform_name_str ) ) );
}

::NS(node_platform_id_t) NS(NodeStore_get_platform_id_by_platform_name)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    char const* SIXTRL_RESTRICT platform_name_str )
{
    return ( node_store != nullptr )
        ? node_store->platformIdByName( arch_id, platform_name_str )
        : st::NodeStore::ILLEGAL_PLATFORM_ID;
}

::NS(arch_size_t) NS(NodeStore_get_num_platforms)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id )
{
    return ( node_store != nullptr )
        ? node_store->numPlatforms( arch_id ) : ::NS(arch_size_t){ 0 };
}

::NS(arch_status_t) NS(NodeStore_add_platform_name_mapping)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store, ::NS(arch_id_t) const arch_id,
    ::NS(node_platform_id_t) const platform_id,
    char const* SIXTRL_RESTRICT platform_name_str )
{
    return ( node_store != nullptr )
        ? node_store->( arch_id, platform_id, platform_name )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(NodeStore_get_num_of_controllers)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store )
{
    return ( node_store != nullptr )
        ? node_store->numControllers() : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(NodeStore_get_num_controllers_by_architecture)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id )
{
    return ( node_store != nullptr )
        ? node_store->numControllers( arch_id ) : :NS(arch_size_t){ 0 };
}

bool NS(NodeStore_has_controller)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    const ::NS(ControllerBase) *const  SIXTRL_RESTRICT controller )
{
    return ( ( node_store != nullptr ) && ( controller != nullptr ) &&
             ( node_store->hasController( *controller ) ) );
}

/* ------------------------------------------------------------------------- */

::NS(node_index_t) NS(NodeStore_find_node_index_by_node_id)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    const NS(NodeId) *const SIXTRL_RETRICT node_id )
{
    return ( ( node_store != nullptr ) && ( node_id != nullptr ) )
        ? node_store->findNodeIndex( *node_id )
        : st::NodeStore::UNDEFINED_INDEX;
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

::NS(arch_size_t) NS(NodeStore_total_num_nodes)(
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

::NS(arch_size_t) NS(NodeStore_get_num_nodes_for_controller)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    const ::NS(ControllerBase) *const  SIXTRL_RESTRICT controller )
{
    return ( ( node_store != nullptr ) && ( controller != nullptr ) )
        ? node_store->numNodes( controller ) : ::NS(arch_size_t){ 0 };
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
        ( max_num_arch_ids > ::NS(arch_size_t){ 0 } ) )
    {
        status = node_store->architectureIds(
            node_indices_begin, node_indices_begin + max_num_arch_ids,
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
        ( max_num_arch_ids > ::NS(arch_size_t){ 0 } ) )
    {
        status = node_store->architectureIds( node_indices_begin,
            node_indices_begin + max_num_arch_ids, arch_id,
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
        ( max_num_arch_ids > ::NS(arch_size_t){ 0 } ) )
    {
        status = node_store->architectureIds( node_indices_begin,
            node_indices_begin + max_num_arch_ids, arch_id, platform_id,
                ptr_num_node_indices );
    }

    return status;
}

::NS(arch_status_t) NS(NodeStore_get_node_indices_for_controller)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(arch_size_t) const max_num_node_indices,
    ::NS(node_index_t)* SIXTRL_RESTRICT node_indices_begin,
    const ::NS(ControllerBase) *const  SIXTRL_RESTRICT controller,
    ::NS(arch_size_t)* SIXTRL_RESTRICT ptr_num_node_indices )
{
    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    if( ( node_store != nullptr ) && ( controller != nullptr ) &&
        ( node_indices_begin != nullptr ) &&
        ( max_num_arch_ids > ::NS(arch_size_t){ 0 } ) )
    {
        status = node_store->architectureIds( node_indices_begin,
            node_indices_begin + max_num_arch_ids, *controller,
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
        ? node_store->ptrNodeInfoBase( node_index ) : nullptr;
}

/* ------------------------------------------------------------------------- */

::NS(arch_status_t) NS(NodeStore_attach_node_to_controller)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index,
    ::NS(ControllerBase)* SIXTRL_RESTRICT controller )
{
    return ( ( node_store != nullptr ) && ( controller != nullptr ) )
        ? node_store->attachNodeToController( node_index, *controller )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeStore_attach_all_architecture_nodes_to_controller)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(ControllerBase)* SIXTRL_RESTRICT controller )
{
    return ( ( node_store != nullptr ) && ( controller != nullptr ) )
        ? node_store->attachAllArchitectureNodesToController( *controller )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeStore_detach_node_from_controller)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index,
    const ::NS(ControllerBase) *const  SIXTRL_RESTRICT controller )
{
    return ( ( node_store != nullptr ) && ( controller != nullptr ) )
        ? node_store->detachNodeFromController( node_index, *controller )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeStore_detach_all_nodes_from_controller)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    const ::NS(ControllerBase) *const  SIXTRL_RESTRICT controller )
{
    return ( ( node_store != nullptr ) && ( controller != nullptr ) )
        ? node_store->detachAllNodesFromController( *controller )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeStore_detach_all_nodes_by_architecture)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(arch_id_t) const arch_id )
{
    return ( ( node_store != nullptr ) && ( controller != nullptr ) )
        ? node_store->detachAllNodesByArchitecture( arch_id, *controller )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeStore_detach_node_from_all_controllers)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( ( node_store != nullptr ) && ( controller != nullptr ) )
        ? node_store->detachNodeFromAllControllers( node_index )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_size_t) NS(NodeStore_get_num_controllers_attached_to_node)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( node_store != nullptr )
        ? node_store->numControllersAttachedToNode( node_index )
        : ::NS(arch_size_t){ 0 };
}

bool NS(NodeStore_is_node_attached_to_any_controller)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( ( node_store != nullptr ) &&
        ( node_store->isNodeAttachedtoAnyController)( node_index ) );
}

bool NS(NodeStore_is_node_attached_to_controller)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index,
    const ::NS(ControllerBase) *const  SIXTRL_RESTRICT controller )
{
    return ( ( node_store != nullptr ) && ( controller != nullptr ) &&
        ( node_store->isNodeAttachedToController( node_index, *controller ) ) );
}

::NS(arch_status_t) NS(NodeStore_mark_node_as_selected_by_controller)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index,
    const ::NS(ControllerBase) *const  SIXTRL_RESTRICT controller )
{
    return ( ( node_store != nullptr ) && ( controller != nullptr ) )
        ? node_store->markNodeAsSelectedByController( node_index, *controller )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeStore_unselect_node_for_controller)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index,
    const ::NS(ControllerBase) *const  SIXTRL_RESTRICT controller )
{
    return ( ( node_store != nullptr ) && ( controller != nullptr ) )
        ? node_store->unselectNodeForController( node_index, *controller )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

bool NS(NodeStore_is_node_selected_by_controller)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index,
    const ::NS(ControllerBase) *const  SIXTRL_RESTRICT controller )
{
    return ( ( node_store != nullptr ) && ( controller != nullptr ) &&
        ( node_store->isNodeSelectedByController( node_index, *controller ) ) );
}

bool NS(NodeStore_is_node_selected_by_any_controller)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( ( node_store != nullptr ) &&
        ( node_store->isNodeSelectedByAnyController( node_index ) ) );
}

::NS(arch_size_t) NS(NodeStore_get_num_selecting_controllers_for_node)(
    const ::NS(NodeStore) *const SIXTRL_RESTRICT node_store,
    ::NS(node_index_t) const node_index )
{
    return ( node_store != nullptr )
        ? node_store->numSelectingControllersForNode( node_index )
        ; ::NS(arch_size_t){ 0 };
}

/* ------------------------------------------------------------------------- */

void NS(NodeStore_clear)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store )
{
    if( node_store != nullptr ) node_store->clear();
}

::NS(arch_status_t) NS(NodeStore_rebuild)(
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store )
{
    return ( node_store != nullptr )
        ? node_store->rebuild() : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeStore_check_lock)(
    const ::NS(NodeStore) *const  SIXTRL_RESTRICT node_store,
    const ::NS(NodeStoreLock) *const SIXTRL_RESTRICT lock )
{
    return ( ( node_store != nullptr ) && ( lock != nullptr ) &&
             ( node_store->checkLock( *lock ) ) );
}

/* end: sixtracklib/common/control/node_store_c99.cpp */
