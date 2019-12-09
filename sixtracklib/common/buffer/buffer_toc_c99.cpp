#include "sixtracklib/common/buffer/buffer_toc.h"

#if defined( __cplusplus ) && !defined( _GPUCODE )

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(BufferToc)* NS(BufferToc_new)(
    const ::NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return new st::BufferToc( buffer );
}

void NS(BufferToc_delete)( ::NS(BufferToc)* SIXTRL_RESTRICT buffer_toc )
{
    delete buffer_toc;
}

/* ------------------------------------------------------------------------- */

bool NS(BufferToc_has_types)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT
{
    return ( ( buffer_toc != nullptr ) && ( buffer_toc->has_types() ) );
}

::NS(buffer_size_t) NS(BufferToc_num_types)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->num_types() : st::buffer_size_t{ 0 };
}

::NS(object_type_id_t) const* NS(BufferToc_types_begin)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr ) ? buffer_toc->types_begin() : nullptr;
}

::NS(object_type_id_t) const* NS(BufferToc_types_end)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr ) ? buffer_toc->types_end() : nullptr;
}

/* ------------------------------------------------------------------------- */

bool NS(BufferToc_has_type_elements)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( ( buffer_toc != nullptr ) &&
             ( buffer_toc->has_type_elements( type_id ) ) );
}

::NS(buffer_size_t) NS(BufferToc_num_type_elements)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->num_type_elements( type_id ) : st::buffer_size_t{ 0 };
}

::NS(buffer_size_t) const* NS(BufferToc_type_elements_indices_begin)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->type_elements_indices_begin( type_id ) : nullptr;
}

::NS(buffer_size_t) const* NS(BufferToc_type_elements_indices_end)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    ::NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->type_elements_indices_end( type_id ) : nullptr;
}


::NS(buffer_size_t) NS(BufferToc_type_element_index)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id, NS(buffer_size_t) const id )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->type_element_index( type_id, id )
        : st::BufferToc::ILLEGAL_ELEMENT_ID;
}

::NS(buffer_size_t) NS(BufferToc_type_element_index_no_check)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id, NS(buffer_size_t) const id )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->type_element_index_no_check( type_id, id )
        : st::BufferToc::ILLEGAL_ELEMENT_ID;
}

/* ------------------------------------------------------------------------- */

::NS(arch_status_t) NS(BufferToc_reset)(
    ::NS(BufferToc)* SIXTRL_RESTRICT buffer_toc,
    const ::NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return ( buffer_toc != nullptr )
        ? buffer_toc->reset( buffer ) : st::ARCH_STATUS_GENERAL_FAILURE;
}

void NS(BufferToc_clear)( void )
{
    if( buffer_toc != nullptr ) buffer_toc->clear();
}

/* ----------------------------------------------------------------- */

bool NS(BufferToc_are_equal)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT lhs,
    const ::NS(BufferToc) *const SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT
{
    if( ( lhs != nullptr ) && ( rhs != nullptr ) )
    {
        return ( *lhs == *rhs );
    }

    return false;
}

bool NS(BufferToc_are_not_equal)(
    const ::NS(BufferToc) *const SIXTRL_RESTRICT lhs,
    const ::NS(BufferToc) *const SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT
{
    if( ( lhs != nullptr ) && ( rhs != nullptr ) )
    {
        return ( *lhs != *rhs );
    }

    return false;
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
