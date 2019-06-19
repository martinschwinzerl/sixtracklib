#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/common/control/node_id.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

SIXTRL_ARGPTR_DEC ::NS(NodeId)*
NS(NodeId_preset)( SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node_id )
{
    if( node_id != nullptr )
    {
        node_id->clear();
    }

    return node_id;
}

SIXTRL_ARGPTR_DEC ::NS(NodeId)* NS(NodeId_create)( void )
{
    return new st::NodeId;
}

void NS(NodeId_delete)( SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id )
{
    delete node_id;
    return;
}

SIXTRL_ARGPTR_DEC ::NS(NodeId)* NS(NodeId_new)(
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    return new st::NodeId( platform_id, device_id );
}

SIXTRL_ARGPTR_DEC ::NS(NodeId)* NS(NodeId_new_from_string)(
    char const* SIXTRL_RESTRICT node_id_str )
{
    return ( ( node_id_str != nullptr ) &&
             ( std::strlen( node_id_str ) > std::size_t{ 0 } ) )
        ? new st::NodeId( node_id_str ) : nullptr;
}

bool NS(NodeId_is_valid)( SIXTRL_ARGPTR_DEC
    const ::NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    return ( ( node_id != nullptr ) && ( node_id->valid() ) );
}

::NS(node_platform_id_t) NS(NodeId_get_platform_id)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    return ( node_id != nullptr )
        ? node_id->platformId() : st::NODE_ILLEGAL_PATFORM_ID;
}

::NS(node_device_id_t) NS(NodeId_get_device_id)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    return ( node_id != nullptr )
        ? node_id->deviceId() : st::NODE_ILLEGAL_DEVICE_ID;
}

void NS(NodeId_set_platform_id)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node_id,
    ::NS(node_platform_id_t) const platform_id )
{
    if( node_id != nullptr ) node_id->setPlatformId( platform_id );
}

void NS(NodeId_set_device_id)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node_id,
    ::NS(node_device_id_t) const device_id )
{
    if( node_id != nullptr ) node_id->setDeviceId( device_id );
}

NS(NodePlatformNodeIdPair) const*
NS(NodeId_get_const_platform_id_platform_id_pair)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return ( node != nullptr ) ? &node->platformDeviceIdPair() : nullptr;
}

NS(NodePlatformNodeIdPair)* NS(NodeId_get_platform_id_platform_id_pair)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node )
{
    return ( node != nullptr ) ? &node->platformDeviceIdPair() : nullptr;
}

/* ------------------------------------------------------------------------ */

bool NS(NodeId_has_controllers)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return ( ( node != nullptr ) && ( node->hasController() ) );
}

::NS(arch_size_t) NS(NodeId_get_num_of_controllers)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return ( node != nullptr )
        ? node->numControllers() : ::NS(arch_size_t){ 0 };
}

bool NS(NodeId_is_attached_to_controller)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( ( node != nullptr ) &&
             ( node->isAttachedToController)( ptr_controller ) );
}

bool NS(NodeId_has_node_index)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( ( node != nullptr ) &&
             ( node->hasNodeIndex( ptr_controller ) ) );
}

::NS(node_index_t) ::NS(NodeId_get_node_index)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( node != nullptr )
        ? node->nodeIndex( ptr_controller ) : ::NS(NODE_UNDEFINED_INDEX);
}

::NS(arch_status_t) NS(NodeId_set_node_index)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller,
    ::NS(node_index_t) const node_index )
{
    return ( node != nullptr )
        ? node->setNodeIndex( ptr_controller, node_index )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

bool NS(NodeId_is_selected)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return ( ( node != nullptr ) && ( node->isSelected() ) );
}

bool NS(NodeId_is_selected_by_controller)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( ( node != nullptr ) &&
             ( node->isSelectedByController( ptr_controller ) ) );
}

bool NS(NodeId_is_default)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return ( ( node != nullptr ) && ( node->isDefault() ) );
}

bool NS(NodeId_is_default_for_controller)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( ( node != nullptr ) &&
             ( node->isDefaultForController( ptr_controller ) ) );
}

::NS(ControllerBase) const* NS(NodeId_get_const_selecting_controller)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node )
{
    return ( node != nullptr ) ? node->ptrSelectingController() : nullptr;
}

::NS(arch_status_t) NS(NodeId_set_selected_controller)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( node != nullptr )
        ? node->setPtrSelectedController( ptr_controller )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

NS(arch_status_t) NS(NodeId_reset_selecting_controller)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node )
{
    return ( node != nullptr )
        ? node->resetSelectingController()
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t) NS(NodeId_attach_to_controller)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller,
    ::NS(node_index_t) const node_index )
{
    return ( node != nullptr )
        ? node->attachToController( ptr_controller, node_index )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t) NS(NodeId_detach_from_controller)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( node != nullptr )
        ? node->detachFromController( ptr_controller )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(ControllerBase) const* NS(NodeId_get_const_controller)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    ::NS(arch_size_t) const num_of_controller_in_sequence )
{
    return ( node != nullptr )
        ? node->ptrController( num_of_controller_in_sequence ) : nullptr;
}

/* ------------------------------------------------------------------------- */

::NS(arch_status_t) NS(NodeId_from_node_id_str)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node,
    char const* SIXTRL_RESTRICT node_id_str )
{
    return ( node != nullptr )
        ? node->fromNodeIdStr( node_id_str )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}


::NS(arch_status_t) NS(NodeId_to_node_id_str)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    ::NS(arch_size_t) const output_str_capacity,
    char* SIXTRL_RESTRICT output_str )
{
    return ( node != nullptr )
        ? node->toNodeIdStr( output_str_capacity, output_str )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

/* ------------------------------------------------------------------------- */

void NS(NodeId_print)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    ::FILE* SIXTRL_RESTRICT fp,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_ctrl )
{
    if( node != nullptr ) node->print( fp, ptr_ctrl );
}

void NS(NodeId_print_out)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_ctrl )
{
    if( node != nullptr ) node->printOut( ptr_ctrl );
}

::NS(arch_size_t) NS(NodeId_required_str_capacity)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_ctrl )
{
    return ( node != nullptr )
        ? node->requiredStringCapacity( ptr_ctrl )
        : ::NS(arch_size_t){ 0 };
}

::NS(arch_status_t) NS(NodeId_to_string)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    ::NS(arch_size_t) const output_str_capacity,
    char* SIXTRL_RESTRICT output_str,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_ctrl )
{
    return ( node != nullptr )
        ? node->toString( output_str_capacity, output_str, ptr_ctrl )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

/* ------------------------------------------------------------------------- */

void NS(NodeId_clear)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node_id )
{
    if( node_id != nullptr ) node_id->clear();
}

/* ------------------------------------------------------------------------- */

int NS(NodeId_compare)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT rhs )
{
    int cmp_result = -1;

    if( ( lhs != nullptr ) && ( rhs != nullptr ) )
    {
        cmp_result = st::compareNodeIds( *lhs, *rhs );
    }
    else if( rhs != nullptr )
    {
        cmp_result = +1;
    }

    return cmp_result;
}

bool NS(NodeId_are_equal)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT rhs )
{
    return ( ::NS(NodeId_compare)( lhs, rhs ) == 0 );
}

/* ------------------------------------------------------------------------- */

::NS(arch_status_t) NS(NodeId_extract_node_id_str_from_config_str)(
    char const* SIXTRL_RESTRICT config_str, char* SIXTRL_RESTRICT node_id_str,
    ::NS(buffer_size_t) const node_id_str_capacity )
{
    int success = st::ARCH_STATUS_GENERAL_FAILURE;
    using buf_size_t = ::NS(buffer_size_t);

    if( ( config_str != nullptr ) && ( node_id_str != nullptr ) &&
        ( std::strlen( config_str ) > buf_size_t{ 0 } ) &&
        ( node_id_str_capacity > buf_size_t{ 1 } ) )
    {
        std::memset( node_id_str, ( int )'\0', node_id_str_capacity );
        std::string const str = st::NodeId_extract_node_id_str_from_config_str(
            config_str );

        if( !str.empty() )
        {
            if( str.size() < node_id_str_capacity )
            {
                std::strncpy( node_id_str, str.c_str(), str.size() );
                success = st::ARCH_STATUS_SUCCESS;
            }
        }
        else
        {
            success = st::ARCH_STATUS_SUCCESS;
        }
    }
    else if( ( config_str != nullptr ) &&
             ( std::strlen( config_str ) == buf_size_t{ 0 } ) )
    {
        if( ( node_id_str != nullptr ) &&
            ( node_id_str_capacity > buf_size_t{ 1 } ) )
        {
            std::memset( node_id_str, ( int )'\0', node_id_str_capacity );
        }

        success = st::ARCH_STATUS_SUCCESS;
    }

    return success;
}

/* end: sixtracklib/common/control/node_id_c99.cpp */
