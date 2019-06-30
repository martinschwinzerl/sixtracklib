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

::NS(arch_size_t) NS(NodeInfo_get_max_selection_count)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->maxSelectionCount() : ::NS(arch_size_t){ 0 };
}

bool NS(NodeInfo_is_attached_to_any_controller)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) &&
             ( info->isAttachedToAnyController() ) );
}

bool NS(NodeInfo_is_attached_to_controller)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const ctrl )
{
    return ( ( info != nullptr ) && ( ctrl != nullptr ) &&
             ( info->isAttachedToController( *ctrl ) ) );
}

::NS(arch_size_t) NS(NodeInfo_get_num_attached_controllers)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->numAttachedControllers() : ::NS(arch_size_t){ 0 };
}

bool NS(NodeInfo_is_selected_by_any_controller)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->isSelectedByAnyController() ) );
}

bool NS(NodeInfo_is_selected_by_controller)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( info != nullptr ) && ( ctrl != nullptr ) &&
             ( info->isSelectedByAnyController( *ctrl ) ) );
}

::NS(arch_size_t) NS(NodeInfo_get_num_selecting_controllers)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->numSelectingControllers() : ::NS(arch_size_t){ 0 };
}

/* ------------------------------------------------------------------------- */

bool NS(NodeInfo_has_unique_id_string)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasUniqueIdStr() ) );
}

char const* NS(NodeInfo_get_unique_id_string)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrUniqueIdStr() : nullptr;
}

bool NS(NodeInfo_maps_to_same)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT other )
{
    return ( ( info != nullptr ) && ( other != nullptr ) &&
             ( info->mapsToSame( *other ) ) );
}

bool NS(NodeInfo_maps_to_same_unique_id_string)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    char const* SIXTRL_RESTRICT unique_id_str )
{
    return ( ( info != nullptr ) && ( info->mapsToSame( unique_id_str ) ) );
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(NodeInfo_required_out_string_length)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( info != nullptr )
        ? info->requiredOutStringLength( ctrl ) : ::NS(arch_size_t){ 0 };
}

void NS(NodeInfo_print)( const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::FILE* SIXTRL_RESTRICT output,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    if( info != nullptr ) info->print( output, ctrl );
}

void NS(NodeInfo_print_out)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    if( info != nullptr) info->printOut( ctrl );
}

::NS(arch_status_t) NS(NodeInfo_to_string)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::NS(arch_size_t) const out_string_capacity, char* SIXTRL_RESTRICT out_str,
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( info != nullptr )
        ? info->toString( out_string_capacity, out_str, ctrl )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

#endif /* !defined( _GPUCODE ) */

/* end: sixtracklib/common/control/node_info_c99.cpp */
