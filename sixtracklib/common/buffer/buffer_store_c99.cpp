#include "sixtracklib/common/buffer/buffer_store.h"

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <cstddef>
        #include <cstdlib>
        #include <memory>
        #include <utility>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #if defined( __cplusplus ) && !defined( _GPUCODE )
        #include "sixtracklib/common/buffer/buffer_store.hpp"
    #endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"

    #if defined( __cplusplus ) && !defined( _GPUCODE )
        #include "sixtracklib/common/buffer.hpp"
    #endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/buffer/buffer_toc.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(BufferStoreBase)* NS(BufferStoreBase_create_with_buffer)(
    ::NS(buffer_size_t) const capacity,
    ::NS(buffer_store_role_t) const role )
{
    return new st::BufferStoreBase( capacity, role );
}

::NS(BufferStoreBase)* NS(BufferStoreBase_create_with_buffer_detailed)(
    ::NS(buffer_size_t) const buffer_capacity,
    ::NS(buffer_store_role_t) const role,
    ::NS(buffer_flags_t) const buffer_flags )
{
    return new st::BufferStoreBase( capacity, role, buffer_flags );
}

::NS(BufferStoreBase)* NS(BufferStoreBase_new)(
    ::NS(Buffer)* SIXTRL_RESTRICT buffer,
    ::NS(buffer_store_role_t) const role,
    bool const take_ownership, bool const delete_after_move )
{
    return new st::BufferStoreBase(
        buffer, role, take_ownership, delete_after_move );
}

::NS(BufferStoreBase)* NS(BufferStoreBase_new_as_copy)(
    const ::NS(BufferStoreBase) *const SIXTRL_RESTRICT orig )
{
    return ( orig != nullptr ) ? new st::BufferStoreBase( *orig ) : nullptr;
}

void NS(BufferStoreBase_delete)( ::NS(BufferStoreBase)* SIXTRL_RESTRICT store )
{
    delete store;
}

bool NS(BufferStoreBase_active)(
    const ::NS(BufferStoreBase) *const SIXTRL_RESTRICT store ) SIXTRL_NOEXCEPT
{
    return ( ( store != nullptr ) && ( store->active() ) );
}

::NS(buffer_store_role_t) NS(BufferStoreBase_role)(
    const NS(BufferStoreBase) *const SIXTRL_RESTRICT store ) SIXTRL_NOEXCEPT
{
    return ( store != nullptr )
        ? store->role() : st::BufferStoreBase::USER_DEFINED_ROLE;
}

bool NS(BufferStoreBase_owns_buffer)(
    const ::NS(BufferStoreBase) *const SIXTRL_RESTRICT store ) SIXTRL_NOEXCEPT
{
    return ( ( store != nullptr ) && ( store->owns_buffer() ) );
}

::NS(Buffer) const* NS(BufferStoreBase_const_buffer)(
    const ::NS(BufferStoreBase) *const SIXTRL_RESTRICT store ) SIXTRL_NOEXCEPT
{
    return ( store != nullptr ) ? store->buffer() : nullptr;
}

::NS(Buffer)* NS(BufferStoreBase_buffer)(
    ::NS(BufferStoreBase)* SIXTRL_RESTRICT store ) SIXTRL_NOEXCEPT
{
    return ( store != nullptr ) ? store->buffer() : nullptr;
}

void NS(BufferStoreBase_clear)(
    ::NS(BufferStoreBase)* SIXTRL_RESTRICT store ) SIXTRL_NOEXCEPT
{
    if( store != nullptr ) store->clear();
}

void NS(BufferStoreBase_reset_with_new_buffer)(
    ::NS(BufferStoreBase)* SIXTRL_RESTRICT store,
    ::NS(buffer_size_t) const buffer_capacity,
    ::NS(buffer_store_role_t) const role )
{
    if( store != nullptr ) store->reset( buffer_capacity, role );
}

void NS(BufferStoreBase_reset_with_new_buffer_detailed)(
    ::NS(BufferStoreBase)* SIXTRL_RESTRICT store,
    ::NS(buffer_size_t) const buffer_capacity,
    ::NS(buffer_store_role_t) const role,
    ::NS(buffer_flags_t) const buffer_flags )
{
    if( store != nullptr ) store->reset( buffer_capacity, role, buffer_flags );
}

void NS(BufferStoreBase_reset)(
    ::NS(BufferStoreBase)* SIXTRL_RESTRICT store,
    ::NS(Buffer)* SIXTRL_RESTRICT buffer,
    ::NS(buffer_store_role_t) const role,
    bool const take_ownership, bool const delete_ptr_after_move )
{
    if( store != nullptr )
        store->reset( buffer, role, take_ownership, delete_ptr_after_move );
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
