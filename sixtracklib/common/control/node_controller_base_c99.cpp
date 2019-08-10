#include "sixtracklib/common/control/node_controller_base.h"

#include <cstddef>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "sixtracklib/common/control/definitions.h"

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(NodeStore) const* NS(Controller_get_ptr_node_store)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrNodeStore() : nullptr;
}

bool NS(Controller_is_sync_with_node_store)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->isSyncWithNodeStore() ) );
}

::NS(arch_status_t) NS(Controller_register_node_store_change)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->registerNodeStoreChange()
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(Controller_sync_with_node_store)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->syncWithNodeStore()
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(node_index_t) NS(Controller_get_num_available_nodes)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->numAvailableNodes() : ::NS(node_index_t){ 0 };
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(Controller_is_node_available_by_index)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(node_index_t) const node_index )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->isNodeAvailable( node_index ) ) );
}

bool NS(Controller_is_node_available_by_node_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    const ::NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) && ( node_id != nullptr ) &&
             ( ptr_nodes_ctrl->isNodeAvailable( *node_id ) ) );
}

bool NS(Controller_is_node_available_by_platform_id_and_device_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->isNodeAvailable(
                ptr_nodes_ctrl->archId(), platform_id, device_id ) ) );
}

bool NS(Controller_is_node_available)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT node_id_str )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->isNodeAvailable( node_id_str ) ) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(Controller_is_node_initialized)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    ::NS(node_index_t) const node_index )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->isNodeInitialized( node_index ) ) );
}

::NS(arch_status_t) NS(Controller_initialize_node)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    ::NS(node_index_t) const node_index )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->initializeNode( node_index )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(Controller_has_selected_node)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->hasSelectedNode() ) );
}

::NS(node_index_t) NS(Controller_get_selected_node_index)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->selectedNodeIndex()
        : st::NODE_UNDEFINED_INDEX;
}

::NS(NodeId) const* NS(Controller_get_ptr_selected_node_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrSelectedNodeId() : nullptr;
}

::NS(NodeInfoBase) const* NS(Controller_get_ptr_selected_node_info_base)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrSelectedNodeInfoBase() : nullptr;
}

char const* NS(Controller_get_selected_node_id_str)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrSelectedNodeIdStr() : nullptr;
}

::NS(arch_status_t) NS(Controller_copy_selected_node_id_str)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    char* SIXTRL_RESTRICT node_id_str,
    ::NS(arch_size_t) const max_str_length )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->selectedNodeIdStr( max_str_length, node_id_str )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(Controller_is_selected_node_by_index)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(node_index_t) const node_index )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl ) &&
             ( ptr_nodes_ctrl->isSelectedNode( node_index ) ) );
}

bool NS(Controller_is_selected_node_by_node_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    const ::NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl ) && ( node_id != nullptr ) &&
             ( ptr_nodes_ctrl->isSelectedNode( *node_id ) ) );
}

bool NS(Controller_is_selected_node_by_platform_id_and_device_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl ) &&
             ( ptr_nodes_ctrl->isSelectedNode(
                ptr_nodes_ctrl->archId(), platform_id, device_id ) ) );
}

bool NS(Controller_is_selected_node)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT node_id_str )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl ) &&
             ( ptr_nodes_ctrl->isSelectedNode( node_id_str ) ) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(Controller_uses_autoselect)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->usesAutoSelect() ) );
}

::NS(arch_status_t) NS(Controller_select_node)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT node_id_str )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );

    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->selectNode( node_id_str )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(Controller_select_node_by_node_id)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    const NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) && ( node_id != nullptr ) )
        ? ptr_nodes_ctrl->selectNode( *node_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(Controller_select_node_by_plaform_id_and_device_id)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->selectNode( platform_id, device_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(Controller_select_node_by_index)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctx,
    ::NS(node_index_t) const node_index )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctx );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->selectNode( node_index )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(Controller_can_change_selected_node)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->canChangeSelectedNode() ) );
}

bool NS(Controller_can_directly_change_selected_node)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->canDirectlyChangeSelectedNode() ) );
}

::NS(arch_status_t) NS(Controller_change_selected_node)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT node_id_str )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->changeSelectedNode( node_id_str )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(Controller_change_selected_node_by_node_id)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    const ::NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) && ( node_id != nullptr ) )
        ? ptr_nodes_ctrl->changeSelectedNode( *node_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t)
NS(Controller_change_selected_node_by_platform_id_and_device_id)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->changeSelectedNode( ptr_nodes_ctrl->archId(),
                platform_id, device_id ) : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(Controller_change_selected_node_by_index)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    ::NS(node_index_t) const new_selected_node_index )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->changeSelectedNode( new_selected_node_index )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(Controller_can_unselect_node)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->canUnselectNode() ) );
}

::NS(arch_status_t) NS(Controller_unselect_node)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->unselectNode() : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(Controller_unselect_node_by_index)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl, NS(node_index_t) const index )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->unselectNode( index )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(Controller_unselect_node_by_node_id)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    const NS(NodeId) *const SIXTRL_RESTRICT ptr_node_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) && ( ptr_node_id != nullptr ) )
        ? ptr_nodes_ctrl->unselectNode( *ptr_node_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(Controller_unselect_node_by_platform_id_and_device_id)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->unselectNode(
            ptr_nodes_ctrl->archId(), platform_id, device_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(Controller_unselect_node_by_node_id_str)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT node_id_str )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->unselectNode( node_id_str )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(Controller_has_default_node)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->hasDefaultNode() ) );
}

::NS(node_index_t) NS(Controller_get_default_node_index)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->defaultNodeIndex()
        : st::NODE_UNDEFINED_INDEX;
}

::NS(NodeId) const* NS(Controller_get_default_node_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrDefaultNodeId() : nullptr;
}

::NS(NodeInfoBase) const* NS(Controller_get_default_node_info_base)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrDefaultNodeInfoBase() : nullptr;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(Controller_is_default_node_index)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(node_index_t) const node_index )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->isDefaultNode( node_index ) ) );
}

bool NS(Controller_is_default_node_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    const NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) && ( node_id != nullptr ) &&
             ( ptr_nodes_ctrl->isDefaultNode( *node_id ) ) );
}

bool NS(Controller_is_default_platform_id_and_device_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->isDefaultNode(
                ptr_nodes_ctrl->archId(), platform_id, device_id ) ) );
}

bool NS(Controller_is_default_node)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT node_id_str )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) &&
             ( ptr_nodes_ctrl->isDefaultNode( node_id_str ) ) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(node_index_t) NS(Controller_get_node_index_by_node_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    const ::NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );

    return ( ( ptr_nodes_ctrl != nullptr ) && ( node_id != nullptr ) )
        ? ptr_nodes_ctrl->nodeIndex( *node_id ) : st::NODE_UNDEFINED_INDEX;
}

::NS(node_index_t) NS(Controller_get_node_index_by_platform_id_and_device_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );

    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->nodeIndex( platform_id, device_id )
        : st::NODE_UNDEFINED_INDEX;
}

::NS(node_index_t) NS(Controller_get_node_index_by_node_info)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT ptr_node_info )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );

    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->nodeIndex( ptr_node_info )
        : st::NODE_UNDEFINED_INDEX;
}

::NS(node_index_t) NS(Controller_get_node_index)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT node_id_str )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );

    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->nodeIndex( node_id_str )
        : st::NODE_UNDEFINED_INDEX;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(NodeId) const* NS(Controller_get_ptr_node_id_by_index)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(node_index_t) const node_index )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrNodeId( node_index ) : nullptr;
}

::NS(NodeId) const* NS(Controller_get_ptr_node_id_by_platform_id_and_device_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrNodeId( platform_id, device_id ) : nullptr;
}

::NS(NodeId) const* NS(Controller_get_ptr_node_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT node_id_str )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrNodeId( node_id_str ) : nullptr;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(NodeInfoBase) const* NS(Controller_get_ptr_node_info_base_by_index)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(node_index_t) const node_index )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrNodeInfoBase( node_index ) : nullptr;
}

::NS(NodeInfoBase) const* NS(Controller_get_ptr_node_info_base_by_node_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    const ::NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ( ptr_nodes_ctrl != nullptr ) && ( node_id != nullptr ) )
        ? ptr_nodes_ctrl->ptrNodeInfoBase( *node_id ) : nullptr;
}

::NS(NodeInfoBase) const*
NS(Controller_get_ptr_node_info_base_by_platform_id_and_device_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    NS(node_platform_id_t) const platform_id,
    NS(node_device_id_t) const device_id )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrNodeInfoBase( platform_id, device_id ) : nullptr;
}

::NS(NodeInfoBase) const* NS(Controller_get_ptr_node_info_base)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT node_id_str )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrNodeInfoBase( node_id_str ) : nullptr;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(node_index_t) const* NS(Controller_get_node_indices_begin)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->nodeIndicesBegin() : nullptr;
}

::NS(node_index_t) const* NS(Controller_get_node_indices_end)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->nodeIndicesEnd() : nullptr;
}

::NS(NodeId) const* NS(Controller_get_node_ids_begin)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->nodeIdsBegin() : nullptr;
}

::NS(NodeId) const* NS(Controller_get_node_ids_end)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->nodeIdsEnd() : nullptr;
}

char const* NS(Controller_get_node_id_string)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(node_index_t) const node_index )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->ptrNodeIdString( node_index )
        : nullptr;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

NS(arch_size_t) NS(Controller_get_required_available_node_infos_str_capacity)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->requiredAvailableNodeInfosStrCapacity()
        : ::NS(arch_size_t){ 0 };
}

void NS(Controller_print_available_nodes_info)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    FILE* SIXTRL_RESTRICT fp )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    if( ptr_nodes_ctrl != nullptr )
    {
        ptr_nodes_ctrl->printAvailableNodesInfo( fp );
    }
}

void NS(Controller_print_out_available_nodes_info)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );
    if( ptr_nodes_ctrl != nullptr )
    {
        ptr_nodes_ctrl->printAvailableNodesInfo();
    }
}

::NS(arch_status_t) NS(Controller_store_available_nodes_info_to_string)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    char* SIXTRL_RESTRICT nodes_info_str,
    ::NS(arch_size_t) const nodes_info_str_capacity,
    ::NS(arch_size_t)* SIXTRL_RESTRICT ptr_required_max_str_length )
{
    auto ptr_nodes_ctrl = st::asNodeController( ctrl );

    return ( ptr_nodes_ctrl != nullptr )
        ? ptr_nodes_ctrl->availableNodeInfosToString( nodes_info_str_capacity,
                node_sinfo_str )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* end: sixtracklib/common/control/node_controller_base.cpp */
