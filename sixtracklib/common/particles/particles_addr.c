#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particles_addr.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

NS(cobj_obj_id_type) NS(ParticlesAddr_cobj_type_id_ext)() SIXTRL_NOEXCEPT {
    return NS(ParticlesAddr_cobj_type_id)(); }

NS(size_type) NS(ParticlesAddr_cobj_num_dataptrs_ext)() SIXTRL_NOEXCEPT {
    return NS(ParticlesAddr_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(ParticlesAddr_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    return NS(ParticlesAddr_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(ParticlesAddr_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    return NS(ParticlesAddr_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(ParticlesAddr_cobj_required_num_bytes_ext)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    return NS(ParticlesAddr_cobj_required_num_bytes)( paddr, slot_size ); }

/* ------------------------------------------------------------------------- */

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr) const*
NS(ParticlesAddr_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(size_type) const index ) SIXTRL_NOEXCEPT {
        return NS(ParticlesAddr_const_from_cbuffer)( b, index ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)* NS(ParticlesAddr_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(size_type) const index ) SIXTRL_NOEXCEPT {
        return NS(ParticlesAddr_from_cbuffer)( b, index ); }

SIXTRL_PARTICLE_ARGPTR_DEC NS(ParticlesAddr)* NS(ParticlesAddr_preset_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT paddr ) {
    return NS(ParticlesAddr_preset)( paddr ); }

void NS(ParticlesAddr_assign_from_particles_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT part_addr,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p ) {
    NS(ParticlesAddr_assign_from_particles)( part_addr, p ); }

void NS(ParticlesAddr_assign_to_particles_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)*  SIXTRL_RESTRICT p ) {
    NS(ParticlesAddr_assign_to_particles)( paddr, p ); }

void NS(ParticlesAddr_remap_addresses_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT paddr,
    NS(particles_addr_diff_type) const addr_offset ) {
    NS(ParticlesAddr_remap_addresses)( paddr, addr_offset ); }

/* ------------------------------------------------------------------------ */

NS(status_type) NS(ParticlesAddr_prepare_buffer_based_on_particles_buffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT paddr_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT pbuffer ) {

    typedef SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* obj_iterator;
    typedef SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* pset_pointer;
    typedef SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)* paddr_pointer;
    typedef NS(particles_num_type) npart_type;

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( paddr_buffer != SIXTRL_NULLPTR ) && ( pbuffer != SIXTRL_NULLPTR ) &&
        ( NS(CBuffer_is_particle_set_buffer)( pbuffer ) ) )
    {
        NS(size_type) const num_psets = NS(CBuffer_num_particle_sets)( pbuffer );
        NS(size_type) num_psets_found = ( NS(size_type) )0u;

        obj_iterator it  = NS(CBuffer_const_objects_begin)( pbuffer );
        obj_iterator end = NS(CBuffer_const_objects_end)( pbuffer );

        if( NS(CBuffer_num_objects)( paddr_buffer ) > ( NS(size_type) )0u )
        {
            NS(CObjFlatBuffer_init_empty)(
                NS(CBuffer_p_base_begin)( paddr_buffer ),
                NS(CBuffer_capacity)( paddr_buffer ),
                NS(CBuffer_slot_size)( paddr_buffer ) );
        }

        SIXTRL_ASSERT( NS(CBuffer_num_objects)(
            paddr_buffer ) == ( NS(size_type) )0u );

        for( ; it != end ; ++it ) {
            pset_pointer pset   = NS(Particles_const_from_cobj_index)( it );
            paddr_pointer paddr = NS(ParticlesAddr_cbuffer_new)( paddr_buffer );
            if( paddr != SIXTRL_NULLPTR ) ++num_psets_found;

            if( ( pset != SIXTRL_NULLPTR ) && ( paddr != SIXTRL_NULLPTR ) &&
                ( ( npart_type )0 < NS(Particles_num_particles)( pset ) ) ) {
                paddr->max_num_particles = NS(Particles_num_particles)( pset ); }
        }

        status = ( ( num_psets_found == num_psets ) &&
                   ( NS(CBuffer_num_objects)( pbuffer ) ==
                     NS(CBuffer_num_objects)( paddr_buffer ) ) )
            ? ( NS(status_type) )SIXTRL_STATUS_SUCCESS
            : ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    }

    return status;
}

NS(status_type) NS(ParticlesAddr_buffer_store_addresses)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT paddr_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT pbuffer,
    NS(size_type) const index ) {
    SIXTRL_ASSERT( paddr_buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( pbuffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(CBuffer_slot_size)( paddr_buffer ) ==
                   NS(CBuffer_slot_size)( pbuffer ) );
    return NS(Particles_cobj_flat_buffer_store_addresses)(
        NS(CBuffer_p_base_begin)( paddr_buffer ),
            NS(CBuffer_p_const_base_begin)( pbuffer ),
                index, NS(CBuffer_slot_size)( pbuffer ) ); }

NS(status_type) NS(ParticlesAddr_buffer_store_all_addresses)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT paddr_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT pbuffer ) {
    SIXTRL_ASSERT( paddr_buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( pbuffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(CBuffer_slot_size)( paddr_buffer ) ==
                   NS(CBuffer_slot_size)( pbuffer ) );
    return NS(Particles_cobj_flat_buffer_store_all_addresses)(
        NS(CBuffer_p_base_begin)( paddr_buffer ),
            NS(CBuffer_p_const_base_begin)( pbuffer ),
                NS(CBuffer_slot_size)( pbuffer ) ); }

/* ------------------------------------------------------------------------ */

void NS(ParticlesAddr_buffer_remap_adresses)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const buffer_index,
    NS(particles_addr_diff_type) const addr_offset ) {
    NS(ParticlesAddr_remap_addresses)(
        NS(ParticlesAddr_from_cbuffer)( buffer, buffer_index ), addr_offset ); }

void NS(ParticlesAddr_buffer_all_remap_adresses)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_addr_diff_type) const addr_offset ) {
    typedef SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj_iterator;

    obj_iterator it  = NS(CBuffer_objects_begin)( buffer );
    obj_iterator end = NS(CBuffer_objects_end)( buffer );

    if( ( buffer != SIXTRL_NULLPTR ) && ( it != SIXTRL_NULLPTR ) &&
        ( end != SIXTRL_NULLPTR ) && ( ( uintptr_t )it < ( uintptr_t )end ) )
    {
        for( ; it != end ; ++it )
        {
            SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)* paddr =
                NS(ParticlesAddr_from_cobj_index)( it );

            if( paddr == SIXTRL_NULLPTR ) continue;
            NS(ParticlesAddr_remap_addresses)( paddr, addr_offset );
        }
    }
}

bool NS(ParticlesAddr_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT { return NS(ParticlesAddr_cbuffer_can_be_added)( buffer,
    requ_buffer_size, requ_slots, requ_objects, requ_dataptrs ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    return NS(ParticlesAddr_cbuffer_new)( buffer ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const num_particles,
    NS(particles_addr_type) const charge0_addr,
    NS(particles_addr_type) const mass0_addr,
    NS(particles_addr_type) const beta0_addr,
    NS(particles_addr_type) const gamma0_addr,
    NS(particles_addr_type) const p0c_addr,
    NS(particles_addr_type) const s_addr,
    NS(particles_addr_type) const x_addr,
    NS(particles_addr_type) const y_addr,
    NS(particles_addr_type) const px_addr,
    NS(particles_addr_type) const py_addr,
    NS(particles_addr_type) const zeta_addr,
    NS(particles_addr_type) const psigma_addr,
    NS(particles_addr_type) const delta_addr,
    NS(particles_addr_type) const rpp_addr,
    NS(particles_addr_type) const rvv_addr,
    NS(particles_addr_type) const chi_addr,
    NS(particles_addr_type) const charge_ratio_addr,
    NS(particles_addr_type) const id_addr,
    NS(particles_addr_type) const at_element_addr,
    NS(particles_addr_type) const at_turn_addr,
    NS(particles_addr_type) const state_addr ) {
    return NS(ParticlesAddr_cbuffer_add)( buffer, num_particles,
        charge0_addr, mass0_addr, beta0_addr, gamma0_addr, p0c_addr,
        s_addr, x_addr, y_addr, px_addr, py_addr, zeta_addr, psigma_addr,
        delta_addr, rpp_addr, rvv_addr, chi_addr, charge_ratio_addr,
        id_addr, at_element_addr, at_turn_addr, state_addr ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr ) { return NS(ParticlesAddr_cbuffer_add_copy)(
            buffer, paddr ); }

