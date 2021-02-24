#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

NS(cobj_obj_id_type) NS(Particle_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(Particle_cobj_type_id)(); }

NS(cobj_size_type) NS(Particle_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(Particle_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(Particle_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(Particle_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(Particle_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    return NS(Particle_cobj_reserved_handle_size)( slot_size ); }

NS(cobj_size_type) NS(Particle_cobj_required_num_bytes_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(Particle_cobj_required_num_bytes)( p, slot_size ); }

SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) const*
NS(Particle_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buf,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Particle_const_from_cbuffer)( buf, idx ); }

SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* NS(Particle_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buf,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Particle_from_cbuffer)( buf, idx ); }

bool NS(Particle_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buf,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT { return NS(Particle_cbuffer_can_be_added)( buf,
    ptr_requ_buffer_size, ptr_requ_slots, ptr_requ_objects, ptr_requ_dataptrs );
}

SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* NS(Particle_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buf ) {
    return NS(Particle_cbuffer_new)( buf ); }

SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* NS(Particle_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buf,
    NS(particle_real_type)  const x,       NS(particle_real_type)  const y,
    NS(particle_real_type)  const px,      NS(particle_real_type)  const py,
    NS(particle_real_type)  const zeta,    NS(particle_real_type)  const delta,
    NS(particle_index_type) const state,
    NS(particle_index_type) const at_element,
    NS(particle_index_type) const at_turn, NS(particle_index_type) const id,
    NS(particle_real_type)  const psigma,  NS(particle_real_type)  const rpp,
    NS(particle_real_type)  const rvv,     NS(particle_real_type)  const chi,
    NS(particle_real_type)  const charge_ratio,
    NS(particle_real_type)  const charge0, NS(particle_real_type)  const mass0,
    NS(particle_real_type)  const beta0,   NS(particle_real_type)  const gamma0,
    NS(particle_real_type)  const p0c,     NS(particle_real_type)  const s
) { return NS(Particle_cbuffer_add)( buf,
    x, y, px, py, zeta, delta, state, at_element, at_turn, id, psigma, rpp, rvv,
        chi, charge_ratio, charge0, mass0, beta0, gamma0, p0c, s ); }

SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* NS(Particle_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT orig
) { return NS(Particle_cbuffer_add_copy)( buffer, orig ); }
