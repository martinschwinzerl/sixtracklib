#include "sixtracklib/common/buffer/buffer_toc.h"
#include "sixtracklib/common/buffer/buffer_toc.hpp"

#include <cstddef>
#include <cstdlib>
#include <memory>
#include <utility>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/buffer.h"

namespace st = SIXTRL_CXX_NAMESPACE;
using _toc_t = st::BufferTableOfContents;

::NS(BufferTableOfContents)* NS(BufferTableOfContents_create)( void )
{
    return new _toc_t;
}

::NS(BufferTableOfContents)* NS(BufferTableOfContents_new)(
    const ::NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return new _toc_t( buffer );
}

void NS(BufferTableOfContents_delete)(
    ::NS(BufferTableOfContents)* SIXTRL_RESTRICT buffer_toc )
{
    delete buffer_toc;
}

void NS(BufferTableOfContents_swap)(
    ::NS(BufferTableOfContents)* SIXTRL_RESTRICT lhs,
    ::NS(BufferTableOfContents)* SIXTRL_RESTRICT rhs )
{
    using std::swap;
    if( ( lhs != nullptr ) && ( rhs != nullptr ) ) swap( *lhs, *rhs );
}

::NS(arch_size_t) NS(BufferTableOfContents_get_total_num_entries)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->total_num_entries() : _toc_t::size_type{ 0 };
}

::NS(arch_size_t) NS(BufferTableOfContents_get_num_entry_types)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->num_entry_types() : _toc_t::size_type{ 0 };
}

::NS(object_type_id_t) const* NS(BufferTableOfContents_get_entry_types_begin)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->entry_types_begin() : nullptr;
}

::NS(object_type_id_t) const* NS(BufferTableOfContents_get_entry_types_end)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc )
{
    return ( buffer_toc != nullptr ) ? buffer_toc->entry_types_end() : nullptr;
}

bool NS(BufferTableOfContents_has_entries)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id )
{
    return ( ( buffer_toc != nullptr ) &&
             ( buffer_toc->has_entries( type_id ) ) );
}

::NS(arch_size_t) NS(BufferTableOfContents_get_num_entries)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->num_entries( type_id ) : _toc_t::size_type{ 0 };
}

::NS(arch_size_t) const* NS(BufferTableOfContents_get_entry_indices_begin)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->entry_indices_begin( type_id ) : nullptr;
}

::NS(arch_size_t) const* NS(BufferTableOfContents_get_entry_indices_end)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->entry_indices_end( type_id ) : nullptr;
}

::NS(arch_size_t) NS(BufferTableOfContents_get_entry_type_index)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(arch_size_t) const nn )
{
    return ( buffer_toc != nullptr ) ? buffer_toc->entry_type_index( nn )
        : _toc_t::ILLEGAL_ENTRY_INDEX;
}

::NS(object_type_id_t) NS(BufferTableOfContents_get_entry_type_id)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(arch_size_t) const nn )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->entry_type_id( nn ) : st::OBJECT_TYPE_INVALID;
}

::NS(buffer_addr_t) NS(BufferTableOfContents_get_entry_offset)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(arch_size_t) const nn )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->entry_offset( nn ) : _toc_t::ILLEGAL_ENTRY_OFFSET;
}

::NS(arch_size_t) NS(BufferTableOfContents_get_entry_size)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(arch_size_t) const nn )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->entry_size( nn ) : _toc_t::ILLEGAL_ENTRY_SIZE;
}

::NS(arch_size_t) NS(BufferTableOfContents_get_entry_num_dataptrs)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(arch_size_t) const nn )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->entry_num_dataptrs( nn ) : _toc_t::ILLEGAL_NUM_DATAPTRS;
}

::NS(arch_size_t) NS(BufferTableOfContents_get_entry_index_for_type)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id, ::NS(arch_size_t) const nn )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->entry_index( type_id, nn ) : _toc_t::ILLEGAL_ENTRY_INDEX;
}

::NS(buffer_addr_t) NS(BufferTableOfContents_get_entry_offset_for_type)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id, ::NS(arch_size_t) const nn )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->entry_offset( type_id, nn )
        : _toc_t::ILLEGAL_ENTRY_OFFSET;
}

::NS(arch_size_t) NS(BufferTableOfContents_get_entry_size_for_type)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id, ::NS(arch_size_t) const nn )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->entry_size( type_id, nn ) : _toc_t::ILLEGAL_ENTRY_SIZE;
}

::NS(arch_size_t) NS(BufferTableOfContents_get_entry_num_dataptrs_for_type)(
    const ::NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id, ::NS(arch_size_t) const nn )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->entry_num_dataptrs( type_id, nn )
        : _toc_t::ILLEGAL_NUM_DATAPTRS;
}

void NS(BufferTableOfContents_clear)(
    ::NS(BufferTableOfContents)* SIXTRL_RESTRICT buffer_toc )
{
    if( buffer_toc != nullptr ) buffer_toc->clear();
}

::NS(arch_status_t) NS(BufferTableOfContents_reset)(
   ::NS(BufferTableOfContents)* SIXTRL_RESTRICT buffer_toc,
   ::NS(Buffer)* SIXTRL_RESTRICT buffer )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->reset( buffer ) : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(BufferTableOfContents_append)(
    ::NS(BufferTableOfContents)* SIXTRL_RESTRICT buffer_toc,
    ::NS(Buffer)* SIXTRL_RESTRICT buffer,
    ::NS(arch_size_t) const num_entries_to_append )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->append( buffer, num_entries_to_append )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

bool NS(BufferTableOfContents_has_same_layout)(
    ::NS(BufferTableOfContents)* SIXTRL_RESTRICT buffer_toc,
    const ::NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return ( ( buffer_toc != nullptr ) &&
             ( buffer_toc->has_same_layout)( buffer ) );
}

/* end: sixtracklib/common/buffer/buffer_toc_c99.cpp */
