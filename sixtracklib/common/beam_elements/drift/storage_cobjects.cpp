#if defined( __cplusplus )

#include "sixtracklib/common/cobjects/cbuffer_view.hpp"

#include "sixtracklib/common/beam_elements/drift/definitions.h"
#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/common/beam_elements/drift/storage_cobjects.h"
#include "sixtracklib/common/cobjects/element_traits.hpp"
#include "sixtracklib/common/cobjects/element_pointers.hpp"
#include "sixtracklib/common/cobjects/element_store_restore.hpp"
#include "sixtracklib/common/internal/buffer_object_defines.h"
#include "sixtracklib/common/buffer/buffer_type.h"
#include "sixtracklib/common/buffer/buffer_object.h"

namespace
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    typedef ::NS(Drift)                             _c_drift_t;
    typedef SIXTRL_BE_ARGPTR_DEC _c_drift_t*        _ptr_drift_t;
    typedef SIXTRL_BE_ARGPTR_DEC _c_drift_t const*  _ptr_const_drift_t;

    static_assert( st::CObjElem_definitely_has_no_ptrs< _c_drift_t >(),
        "Drifts shouldn't have any dataptrs" );

    static_assert( st::CObjElem_allow_direct_storage< _c_drift_t >(),
        "Drifts are supposed to be suitable for direct storage" );
}

::NS(cobj_type_id_t) NS(Drift_type_id_ext)( void ) SIXTRL_NOEXCEPT
{
    return ::NS(Drift_type_id)();
}

::NS(cobj_size_t) NS(Drift_num_pointers)( void ) SIXTRL_NOEXCEPT
{
    return st::CObjElem_num_ptrs< _c_drift_t >();
}

::NS(cobj_size_t) NS(Drift_required_num_bytes)(
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return st::CObjElem_required_num_bytes< _c_drift_t >( slot_size );
}

::NS(cobj_size_t) NS(Drift_required_num_slots)(
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return st::CObjElem_rerquired_num_slots< _c_drift_t >( slot_size );
}


_ptr_const_drift_t NS(Drift_const_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const st::CBufferView *const SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( buffer != nullptr );
    return buffer->get_object< _c_drift_t >( pos_in_buffer );
}

_ptr_drift_t NS(Drift_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC st::CBufferView* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( buffer != nullptr );
    return buffer->get_object< _c_drift_t >( pos_in_buffer );
}

#endif /* _cplusplus */
