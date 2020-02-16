#if defined( __cplusplus )
#include "sixtracklib/common/beam_elements/multipole/storage_cobjects.h"

#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/beam_elements/multipole/definitions.h"
#include "sixtracklib/common/cobjects/element_store_restore.hpp"

namespace
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    typedef ::NS(Multipole)                      _c_mp_t;
    typedef SIXTRL_BE_ARGPTR_DEC _c_mp_t*        _ptr_drift_t;
    typedef SIXTRL_BE_ARGPTR_DEC _c_mp_t const*  _ptr_const_drift_t;
    typedef ::NS(cobj_size_t)                    _size_t;
    typedef ::NS(be_real_t)                      _real_t;

    static_assert( st::CObjElem_definitely_has_ptrs< _c_mp_t >(),
        "Multipoles should have one pointer!" );

    static_assert( st::CObjElem_has_const_num_ptrs< _c_mp_t >(),
        "Multipoles should have a constant number of pointers (== 1)" );

    static_assert( st::CObjElem_max_num_ptrs< _c_mp_t >() == 1u,
        "Multipoles should have a max number of pointers == 1" );

    static_assert( st::CObjElem_min_num_ptrs< _c_mp_t >() == 1u,
        "Multipoles should have a min number of pointers == 1" );

    static_assert( st::CObjElem_has_always_same_sizes< _c_mp_t >(),
        "Multipoles should have not argument dependent data type size!" );

    static_assert( st::CObjElem_allow_direct_storage< _c_mp_t >(),
        "Multipoles are supposed to be suitable for direct storage" );
}

::NS(cobj_type_id_t) NS(Multipole_type_id_ext)( void ) SIXTRL_NOEXCEPT
{
    return ::NS(Multipole_type_id)();
}

_size_t NS(Multipole_num_pointers)( void ) SIXTRL_NOEXCEPT
{
    return st::CObjElem_num_ptrs< _c_mp_t >();
}

_size_t NS(Multipole_required_num_bytes)(
    _size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return st::CObjElem_required_num_bytes< _c_mp_t >( slot_size );
}

_size_t NS(Multipole_required_num_slots)(
    _size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return st::CObjElem_required_num_slots< _c_mp_t >( slot_size );
}


_ptr_const_drift_t NS(Multipole_const_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const st::CBufferView *const SIXTRL_RESTRICT buffer,
    _size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( buffer != nullptr );
    return buffer->get_object< _c_mp_t >( pos_in_buffer );
}

_ptr_drift_t NS(Multipole_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC st::CBufferView* SIXTRL_RESTRICT buffer,
    _size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( buffer != nullptr );
    return buffer->get_object< _c_mp_t >( pos_in_buffer );
}

bool NS(Multipole_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const st::CBufferView *const
        SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const _c_mp_t *const SIXTRL_RESTRICT orig
    ) SIXTRL_NOEXCEPT
{
    return ( ( buffer != nullptr ) &&
             ( buffer->can_add_copy_of_object< _c_mp_t >( orig ) ) );
}

bool NS(Multipole_can_add_copy_detailed)(
    SIXTRL_BUFFER_ARGPTR_DEC const st::CBufferView *const
        SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const _c_mp_t *const SIXTRL_RESTRICT orig,
    SIXTRL_BUFFER_ARGPTR_DEC _size_t* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_BUFFER_ARGPTR_DEC _size_t* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC _size_t* SIXTRL_RESTRICT ptr_requ_objs,
    SIXTRL_BUFFER_ARGPTR_DEC _size_t* SIXTRL_RESTRICT ptr_requ_ptrs
) SIXTRL_NOEXCEPT
{
    return ( ( buffer != nullptr ) &&
             ( buffer->can_add_copy_of_object< _c_mp_t >( orig,
                ptr_requ_buffer_size, ptr_requ_slots, ptr_requ_objs,
                    ptr_requ_ptrs ) ) );
}

SIXTRL_BE_ARGPTR_DEC _c_mp_t* NS(Multipole_new)(
    SIXTRL_BUFFER_ARGPTR_DEC st::CBufferView* SIXTRL_RESTRICT buffer )
{
    SIXTRL_BUFFER_ARGPTR_DEC _c_mp_t temp_drift;
    ::NS(Multipole_set_length)( &temp_drift, _real_t{ 0 } );
    return ::NS(Multipole_add_copy)( buffer, &temp_drift );
}

SIXTRL_BE_ARGPTR_DEC _c_mp_t* NS(Multipole_add)(
    SIXTRL_BUFFER_ARGPTR_DEC st::CBufferView* SIXTRL_RESTRICT buffer,
    ::NS(be_order_t) const order, _real_t const length,
    _real_t const hxl, _real_t const hyl,
    SIXTRL_BE_DATAPTR_DEC _real_t const* SIXTRL_RESTRICT bal_values )
{
    SIXTRL_BUFFER_ARGPTR_DEC _c_mp_t temp;

    temp.order    = order;
    temp.length   = length;
    temp.hxl      = hxl;
    temp.hyl      = hyl;
    temp.bal_addr = static_cast< st::cobj_address_t >(
        reinterpret_cast< uintptr_t >( bal_values ) );

    return ::NS(Multipole_add_copy)( buffer, &temp );
}

SIXTRL_BE_ARGPTR_DEC _c_mp_t* NS(Multipole_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC st::CBufferView* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const _c_mp_t *const SIXTRL_RESTRICT orig )
{
    return ( buffer != nullptr )
        ? st::CBufferView_add_copy_of_object_detail(
            *buffer, orig, nullptr, nullptr, nullptr, nullptr )
        : nullptr;
}

#endif /* _cplusplus */
