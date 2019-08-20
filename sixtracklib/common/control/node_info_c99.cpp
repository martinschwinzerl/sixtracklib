#include "sixtracklib/common/control/node_info.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_info.hpp"
#include "sixtracklib/common/control/node_store.hpp"

#if !defined( _GPUCODE )

namespace  st = SIXTRL_CXX_NAMESPACE;
using _info_t = st::NodeInfoBase;

::NS(NodeInfoBase)* NS(NodeInfoBase_create)(
    ::NS(arch_id_t) const arch_id,
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store )
{
    return new st::NodeInfoBase( arch_id, nullptr, nullptr, nullptr,
        _info_t::ILLEGAL_PLATFORM_ID, _info_t::ILLEGAL_DEVICE_ID, node_store );
}

::NS(NodeInfoBase)* NS(NodeInfoBase_new)(
    ::NS(NodeId)* SIXTRL_RESTRICT node_id,
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store )
{
    return new st::NodeInfoBase(
        node_id, nullptr, nullptr, nullptr, node_store );
}

::NS(NodeInfoBase)* NS(NodeInfoBase_new_detailed)(
    ::NS(arch_id_t) const arch_id,
    const char *const SIXTRL_RESTRICT platform_name,
    const char *const SIXTRL_RESTRICT device_name,
    const char *const SIXTRL_RESTRICT description,
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id,
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store )
{
    return new st::NodeInfoBase( arch_id, platform_name, device_name,
        description, platform_id, device_id, node_store );
}

void NS(NodeInfo_delete)( ::NS(NodeInfoBase)* SIXTRL_RESTRICT node_info )
{
    if( node_info != nullptr ) delete node_info;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeInfo_has_arch_str)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasArchStr() ) );
}

char const* NS(NodeInfo_get_arch_str)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrArchStr() : nullptr;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeInfo_has_node_store)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasNodeStore() ) );
}

::NS(NodeStore) const* NS(NodeInfo_get_ptr_const_node_store)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrNodeStore() : nullptr;
}

::NS(NodeStore)* NS(NodeInfo_get_ptr_node_store)(
    ::NS(NodeInfoBase)* SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrNodeStore() : nullptr;
}

::NS(arch_status_t) NS(NodeInfo_assign_to_node_store)(
    ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    ::NS(NodeStore)* SIXTRL_RESTRICT node_store )
{
    return ( ( info != nullptr ) && ( node_store != nullptr ) )
        ? info->assignToNodeStore( *node_store )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeInfo_detach_from_node_store)(
    ::NS(NodeInfoBase)* SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->detachFromNodeStore() : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

::NS(NodeId) const* NS(NodeInfo_get_ptr_const_node_id)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrCNodeId() : nullptr;
}

::NS(arch_id_t) NS(NodeInfo_get_arch_id)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    _info_t::arch_id_t arch_id = _info_t::ARCH_ILLEGAL;

    if( ( info != nullptr ) && ( info->lockable() != nullptr ) )
    {
        _info_t::lock_t const lock( *info->lockable() );
        arch_id = info->archId( lock );
    }
    else if( ( info != nullptr ) && ( info->ptrNodeStore() == nullptr ) )
    {
        arch_id = info->archId();
    }

    return arch_id;
}

::NS(node_platform_id_t) NS(NodeInfo_get_platform_id)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->platformId() : _info_t::ILLEGAL_PLATFORM_ID;
}

::NS(node_device_id_t) NS(NodeInfo_get_device_id)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->deviceId() : _info_t::ILLEGAL_DEVICE_ID;
}

::NS(arch_status_t) NS(NodeInfo_set_platform_id)(
    ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    ::NS(node_platform_id_t) const platform_id )
{
    return ( info != nullptr )
        ? info->setPlatformId( platform_id ) : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeInfo_set_device_id)(
    ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    ::NS(node_device_id_t) const device_id )
{
    return ( info != nullptr )
        ? info->setDeviceId( device_id ) : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

::NS(node_index_t) NS(NodeInfo_get_node_index)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->nodeIndex() : _info_t::UNDEFINED_INDEX;
}

/* ------------------------------------------------------------------------- */

bool NS(NodeInfo_has_platform_name)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasPlatformName() ) );
}

char const* NS(NodeInfo_get_platform_name_str)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrPlatformNameStr() : nullptr;
}

::NS(arch_status_t) NS(NodeInfo_set_platform_name)(
    ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    const char *const SIXTRL_RESTRICT platform_name )
{
    return ( info != nullptr ) ? info->setPlatformName( platform_name )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

bool NS(NodeInfo_has_device_name)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasDeviceName() ) );
}

char const* NS(NodeInfo_get_device_name_str)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrDeviceNameStr() : nullptr;
}

void NS(NodeInfo_set_device_name)(
    ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    const char *const SIXTRL_RESTRICT device_name )
{
    if( info != nullptr ) info->setDeviceName( device_name );
}

bool NS(NodeInfo_has_description)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasDescription() ) );
}

char const* NS(NodeInfo_get_description_str)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrDescriptionStr() : nullptr;
}

void NS(NodeInfo_set_description)(
    ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    const char *const SIXTRL_RESTRICT description_str )
{
    if( info != nullptr ) info->setDescription( description_str );
}

/* ------------------------------------------------------------------------- */

bool NS(NodeInfo_has_unique_id_str)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->hasUniqueIdStr() ) );
}

char const* NS(NodeInfo_unique_id_str)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr ) ? info->ptrUniqueIdStr() : nullptr;
}

bool NS(NodeInfo_maps_to_same_unique_id_str)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    char const* SIXTRL_RESTRICT unique_id_str )
{
    return ( ( info != nullptr ) && ( info->mapsToSame( unique_id_str ) ) );
}

bool NS(NodeInfo_maps_to_same_node_by_unique_id_str)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT other_info )
{
    return ( ( info != nullptr ) && ( other_info != nullptr ) &&
             ( info->mapsToSame( *other_info ) ) );
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(NodeInfo_get_max_attachement_count)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->maxAttachementCount() : st::arch_size_t{ 0 };
}

bool NS(NodeInfo_is_attached_to_any_set)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->isAttachedToAnySet() ) );
}

::NS(arch_size_t) NS(NodeInfo_get_num_attached_sets)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->numAttachedSets() : st::arch_size_t{ 0 };
}

bool NS(NodeInfo_is_attached_to_set)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::NS(node_set_id_t) const set_id )
{
    return ( ( info != nullptr ) && ( info->isAttachedToSet( set_id ) ) );
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(NodeInfo_get_max_selection_count)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->maxSelectionCount() : st::arch_size_t{ 0 };
}

bool NS(NodeInfo_is_selected_by_any_set)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( ( info != nullptr ) && ( info->isSelectedByAnySet() ) );
}

::NS(arch_size_t) NS(NodeInfo_get_num_selection_count)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->numSelectionCount() : st::arch_size_t{ 0 };
}

bool NS(NodeInfo_is_selected_by_set)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::NS(node_set_id_t) const node_set_id )
{
    return ( ( info != nullptr ) && ( info->isSelectedBySet( node_set_id ) ) );
}

bool NS(NodeInfo_is_default_for_set)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::NS(node_set_id_t) const node_set_id )
{
    return ( ( info != nullptr ) && ( info->isDefaultForSet( node_set_id ) ) );
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(NodeInfo_get_required_out_string_length)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return ( info != nullptr )
        ? info->requiredOutStringLength() : st::arch_size_t{ 0 };
}

::NS(arch_size_t) NS(NodeInfo_get_required_out_string_length_for_set)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::NS(node_set_id_t) const node_set_id )
{
    return ( info != nullptr )
        ? info->requiredOutStringLength( node_set_id )
        : st::arch_size_t{ 0 };
}

void NS(NodeInfo_print)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::FILE* SIXTRL_RESTRICT output )
{
    if( info != nullptr ) info->print( output );
}

void NS(NodeInfo_print_for_set)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::FILE* SIXTRL_RESTRICT output, ::NS(node_set_id_t) const node_set_id )
{
    if( info != nullptr ) info->print( output, node_set_id );
}

void NS(NodeInfo_print_out)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    if( info != nullptr ) info->printOut();
}

void NS(NodeInfo_print_out_for_set)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::NS(node_set_id_t) const node_set_id )
{
    if( info != nullptr ) info->printOut( node_set_id );
}

::NS(arch_status_t) NS(NodeInfo_to_string)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::NS(arch_size_t) const out_str_capacity,
    char* SIXTRL_RESTRICT out_str )
{
    return ( info != nullptr )
        ? info->toString( out_str_capacity, out_str )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(NodeInfo_to_string_for_set)(
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::NS(arch_size_t) const out_str_capacity, char* SIXTRL_RESTRICT out_str,
    ::NS(node_set_id_t) const node_set_id )
{
    return ( info != nullptr )
        ? info->toString( out_str_capacity, out_str, node_set_id )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

#endif /* !defined( _GPUCODE ) */

/* end: sixtracklib/common/control/node_info_c99.cpp */
