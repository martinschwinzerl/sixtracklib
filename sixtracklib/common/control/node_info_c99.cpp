#include "node_info.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_info.hpp"


#if !defined( _GPUCODE )

namespace st = SIXTRL_CXX_NAMESPACE;

void NS(NodeInfo_delete)( ::NS(NodeInfoBase)* SIXTRL_RESTRICT node_info )
{
    if( node_info != nullptr ) delete node_info;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeInfo_has_node_id)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasNodeId() ) );
}

bool NS(NodeInfo_owns_node_id)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->ownsNodeId() ) );
}

::NS(NodeId) const* NS(NodeInfo_get_ptr_const_node_id)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrNodeId() : nullptr;
}

::NS(NodeId)* NS(NodeInfo_get_ptr_node_id)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrNodeId() : nullptr;
}

::NS(node_platform_id_t) NS(NodeInfo_get_platform_id)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->platformId() : st::NODE_ILLEGAL_PATFORM_ID;
}

::NS(arch_status_t) NS(NodeInfo_set_platform_id)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    ::NS(node_platform_id_t) const platform_id )
{
    return ( info != nullptr )
        ? info->setPlatformId( platform_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(node_device_id_t) NS(NodeInfo_get_device_id)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->deviceId() : st::NODE_ILLEGAL_DEVICE_ID;
}

::NS(arch_status_t) NS(NodeInfo_set_device_id)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    ::NS(node_device_id_t) const device_id )
{
    return ( info != nullptr )
        ? info->setDeviceId( device_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(NodePlatformNodeIdPair) const*
NS(NodeInfo_get_const_platform_id_platform_id_pair)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )? info->ptrPlatformDeviceIdPair() : nullptr;
}

::NS(NodePlatformNodeIdPair)* NS(NodeInfo_get_platform_id_platform_id_pair)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info )
{
    return ( info != nullptr )? info->ptrPlatformDeviceIdPair() : nullptr;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeInfo_has_controllers)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfo) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasControllers() ) );
}

::NS(arch_size_t) NS(NodeInfo_get_num_of_controllers)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfo) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->numControllers() : ::NS(arch_size_t){ 0 };
}

bool NS(NodeInfo_is_attached_to_controller)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfo) *const SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( ( info != nullptr ) &&
             ( info->isAttachedToController( ptr_controller ) ) );
}

bool NS(NodeInfo_has_node_index)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfo) *const SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( ( info != nullptr ) && ( info->hasNodeIndex( ptr_controller ) ) );
}

::NS(node_index_t) NS(NodeInfo_get_node_index)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfo) *const SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( info != nullptr )
        ? info->getNodeIndex( ptr_controller )
        : st::NodeInfoBase::UNDEFINED_INDEX;
}

::NS(arch_status_t) NS(NodeInfo_set_node_index)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfo)* SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller,
    ::NS(node_index_t) const node_index )
{
    return ( info != nullptr )
        ? indo->setNodeIndex( ptr_cotnroller, node_index )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

bool NS(NodeInfo_is_selected)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfo) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->isSelected() ) );
}

bool NS(NodeInfo_is_selected_by_controller)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfo) *const SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( ( info != nullptr ) &&
             ( info->isSelectedByController( ptr_controller ) ) );
}

bool NS(NodeInfo_is_default)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfo) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->isDefault() ) );
}

bool NS(NodeInfo_is_default_for_controller)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfo) *const SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( ( info != nullptr ) &&
             ( info->isDefaultForController( ptr_controller ) ) );
}

::NS(ControllerBase) const* NS(NodeInfo_get_const_selecting_controller)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfo) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrSelectingController() : nullptr;
}

::NS(arch_status_t) NS(NodeInfo_set_selected_controller)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfo)* SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( info != nullptr )
        ? info->setPtrSelectedController( ptr_controller )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeInfo_reset_selecting_controller)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfo)* SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->resetSelectingController()
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeInfo_attach_to_controller)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfo)* SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller,
    ::NS(node_index_t) const node_index )
{
    return ( info != nullptr )
        ? info->attachToController( ptr_controller, node_index )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeInfo_detach_from_controller)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfo)* SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( info != nullptr )
        ? info->detachFromController( ptr_controller )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(ControllerBase) const* NS(NodeInfo_get_const_controller)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfo) *const SIXTRL_RESTRICT info,
    ::NS(arch_size_t) const num_of_controller_in_sequence )
{
    return ( info != nullptr )
        ? info->ptrController( num_of_controller_in_sequence ) : nullptr;
}

/* ------------------------------------------------------------------------- */

::NS(arch_id_t) NS(NodeInfo_get_arch_id)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->archId() : st::ARCHITECTURE_ILLEGAL;
}

bool NS(NodeInfo_has_arch_string)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasArchStr() ) );
}

char const* NS(NodeInfo_get_arch_string)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrArchStr() : nullptr;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeInfo_has_platform_name)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasPlatformName() ) );
}

char const* NS(NodeInfo_get_platform_name)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrPlatformNameStr() : nullptr;
}

void NS(NodeInfo_set_platform_name)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT platform_name )
{
    if( info != nullptr ) info->setPlatformName( platform_name );
}

bool NS(NodeInfo_has_device_name)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasDeviceName() ) );
}

char const* NS(NodeInfo_get_device_name)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrDeviceNameStr() : nullptr;
}

void NS(NodeInfo_set_device_name)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT device_name )
{
    if( info != nullptr ) info->setDeviceName( device_name );
}

bool NS(NodeInfo_has_description)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasDescription() ) );
}

char const* NS(NodeInfo_get_description)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrDescriptionStr() : nullptr;
}

void NS(NodeInfo_set_description)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT description )
{
    if( info != nullptr ) info->setPlatformName( description );
}

/* ------------------------------------------------------------------------- */

void NS(NodeInfo_print)( SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const
    SIXTRL_RESTRICT info, ::FILE* SIXTRL_RESTRICT output,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    if( ( info != nullptr ) && ( output != nullptr ) )
    {
        info->print( output, ptr_controller );
    }
}

void NS(NodeInfo_print_out)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    if( info != nullptr ) info->printOut( ptr_controller );
}


::NS(arch_size_t) NS(NodeInfo_get_required_output_str_length)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( info != nullptr )
        ? info->requiredOutStringLength( ptr_controller )
        : ::NS(arch_size_t){ 0 };
}

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(NodeInfo_convert_to_string)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    NS(arch_size_t) const out_string_capacity,
    char* SIXTRL_RESTRICT out_string,
    const NS(ControllerBase) *const SIXTRL_RESTRICT ptr_controller )
{
    return ( info != nullptr )
        ? info->toString( out_string_capacity, out_string, ptr_controller )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

#endif /* !defined( _GPUCODE ) */

/* end: sixtracklib/common/control/node_info_c99.cpp */
