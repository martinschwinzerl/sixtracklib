#if defined( __cplusplus )
#include "sixtracklib/common/particles/storage_cobjects.h"
#include "sixtracklib/common/particles/definitions.h"

#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/element_store_restore.hpp"

namespace
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    typedef ::NS(Particle)                              _c_part_t;
    typedef SIXTRL_PARTICLE_ARGPTR_DEC _c_part_t*       _ptr_part_t;
    typedef SIXTRL_PARTICLE_ARGPTR_DEC _c_part_t const* _ptr_const_part_t;
    typedef ::NS(cobj_size_t)                           _size_t;
    typedef ::NS(particle_real_t)                       _real_t;

    static_assert( st::CObjElem_definitely_has_no_ptrs< _c_part_t >(),
        "Particle shouldn't have any dataptrs" );

    static_assert( st::CObjElem_allow_direct_storage< _c_part_t >(),
        "Particle are supposed to be suitable for direct storage" );
}

::NS(cobj_type_id_t) NS(Particle_type_id_ext)( void ) SIXTRL_NOEXCEPT
{
    return ::NS(Particle_type_id)();
}

::NS(cobj_size_t) NS(Particle_num_pointers)( void ) SIXTRL_NOEXCEPT
{
    return st::CObjElem_num_ptrs< _c_part_t >();
}

::NS(cobj_size_t) NS(Particle_required_num_bytes)(
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return st::CObjElem_required_num_bytes< _c_part_t >( slot_size );
}

::NS(cobj_size_t) NS(Particle_required_num_slots)(
    ::NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return st::CObjElem_required_num_slots< _c_part_t >( slot_size );
}


_ptr_const_part_t NS(Particle_const_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const st::CBufferView *const SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( buffer != nullptr );
    return buffer->get_object< _c_part_t >( pos_in_buffer );
}

_ptr_part_t NS(Particle_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC st::CBufferView* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_t) const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( buffer != nullptr );
    return buffer->get_object< _c_part_t >( pos_in_buffer );
}

bool NS(Particle_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const st::CBufferView *const
        SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const _c_part_t *const SIXTRL_RESTRICT orig
    ) SIXTRL_NOEXCEPT
{
    return ( ( buffer != nullptr ) &&
             ( buffer->can_add_copy_of_object< _c_part_t >( orig ) ) );
}

bool NS(Particle_can_add_copy_detailed)(
    SIXTRL_BUFFER_ARGPTR_DEC const st::CBufferView *const
        SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const _c_part_t *const SIXTRL_RESTRICT orig,
    SIXTRL_BUFFER_ARGPTR_DEC _size_t* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_BUFFER_ARGPTR_DEC _size_t* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC _size_t* SIXTRL_RESTRICT ptr_requ_objs,
    SIXTRL_BUFFER_ARGPTR_DEC _size_t* SIXTRL_RESTRICT ptr_requ_ptrs
) SIXTRL_NOEXCEPT
{
    return ( ( buffer != nullptr ) &&
             ( buffer->can_add_copy_of_object< _c_part_t >( orig,
                ptr_requ_buffer_size, ptr_requ_slots, ptr_requ_objs,
                    ptr_requ_ptrs ) ) );
}

SIXTRL_PARTICLE_ARGPTR_DEC _c_part_t* NS(Particle_new)(
    SIXTRL_BUFFER_ARGPTR_DEC st::CBufferView* SIXTRL_RESTRICT buffer )
{
    SIXTRL_PARTICLE_ARGPTR_DEC _c_part_t temp;
    ::NS(Particle_preset)( &temp );
    return ::NS(Particle_add_copy)( buffer, &temp );
}

SIXTRL_PARTICLE_ARGPTR_DEC _c_part_t* NS(Particle_add)(
    SIXTRL_BUFFER_ARGPTR_DEC st::CBufferView* SIXTRL_RESTRICT buffer,
    ::NS(particle_real_t)  const x,        ::NS(particle_real_t) const px,
    ::NS(particle_real_t)  const y,        ::NS(particle_real_t) const py,
    ::NS(particle_real_t)  const zeta,     ::NS(particle_real_t) const delta,
    ::NS(particle_real_t)  const psigma,
    ::NS(particle_index_t) const state,
    ::NS(particle_index_t) const at_element,
    ::NS(particle_index_t) const at_turn,  ::NS(particle_index_t) const id,
    ::NS(particle_real_t)  const s,        ::NS(particle_real_t)  const rvv,
    ::NS(particle_real_t)  const rpp,      ::NS(particle_real_t)  const chi,
    ::NS(particle_real_t)  const charge_ratio,
    ::NS(particle_real_t)  const charge0,  ::NS(particle_real_t)  const mass0,
    ::NS(particle_real_t)  const beta0,    ::NS(particle_real_t)  const gamma0,
    ::NS(particle_real_t)  const pc0 )
{
    SIXTRL_PARTICLE_ARGPTR_DEC _c_part_t temp;
    ::NS(Particle_preset)( &temp );
    ::NS(Particle_set_x)(  &temp, x );
    ::NS(Particle_set_y)(  &temp, y );
    ::NS(Particle_set_px)( &temp, px );
    ::NS(Particle_set_py)( &temp, py );
    ::NS(Particle_set_zeta)( &temp, zeta );
    ::NS(Particle_set_delta)( &temp, delta );
    ::NS(Particle_set_psigma)( &temp, psigma );
    ::NS(Particle_set_state)( &temp, state );
    ::NS(Particle_set_at_element)( &temp, at_element );
    ::NS(Particle_set_at_turn)( &temp, at_turn );
    ::NS(Particle_set_id)( &temp, id );
    ::NS(Particle_set_s)( &temp, s );
    ::NS(Particle_set_rvv)( &temp, rvv );
    ::NS(Particle_set_rpp)( &temp, rpp );
    ::NS(Particle_set_chi)( &temp, chi );
    ::NS(Particle_set_charge_ratio)( &temp, charge_ratio );
    ::NS(Particle_set_charge0)( &temp, charge0 );
    ::NS(Particle_set_mass0)( &temp, mass0 );
    ::NS(Particle_set_beta0)( &temp, beta0 );
    ::NS(Particle_set_gamma0)( &temp, gamma0 );
    ::NS(Particle_set_pc0)( &temp, pc0 );

    return ::NS(Particle_add_copy)( buffer, &temp );
}

SIXTRL_PARTICLE_ARGPTR_DEC _c_part_t* NS(Particle_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC st::CBufferView* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const _c_part_t *const SIXTRL_RESTRICT orig )
{
    return ( buffer != nullptr )
        ? st::CBufferView_add_copy_of_object_detail(
            *buffer, orig, nullptr, nullptr, nullptr, nullptr )
        : nullptr;
}

#endif /* _cplusplus */
