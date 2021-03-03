#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLES_ADDR_COBJ_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLES_ADDR_COBJ_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/particles/particles_addr.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

SIXTRL_STATIC SIXTRL_FN bool NS(ParticlesAddr_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles,
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
    NS(particles_addr_type) const state_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN bool NS(ParticlesAddr_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(particles_num_type) const max_num_particles,
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
    NS(particles_addr_type) const state_addr );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr );

#if !defined( _GPUCODE )


SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ParticlesAddr_cobj_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_new_ext)( SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)*
    SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles,
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
    NS(particles_addr_type) const state_addr );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT addr );

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE bool NS(ParticlesAddr_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_can_add_copy_of_trivial_object)(
    buffer, slot_size, NS(ParticlesAddr_cobj_reserved_handle_size)( slot_size ),
        requ_buffer_size, requ_slots, requ_objects, requ_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT b,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr) paddr;
    NS(ParticlesAddr_clear)( &paddr );
    return NS(ParticlesAddr_cobj_flat_buffer_add_copy)( b, slot_size, &paddr ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT b,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles,
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
    NS(particles_addr_type) const state_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr) paddr;
    NS(ParticlesAddr_init)( &paddr, max_num_particles,
        charge0_addr, mass0_addr, beta0_addr, gamma0_addr, p0c_addr,
        s_addr, x_addr, y_addr, px_addr, py_addr, zeta_addr, psigma_addr,
        delta_addr, rpp_addr, rvv_addr, chi_addr, charge_ratio_addr,
        id_addr, at_element_addr, at_turn_addr, state_addr );
    return NS(ParticlesAddr_cobj_flat_buffer_add_copy)( b, slot_size, &paddr ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr ) SIXTRL_NOEXCEPT {
    return NS(ParticlesAddr_from_cobj_index)(
        NS(CObjFlatBuffer_add_copy_of_trivial_object)( buffer, slot_size, paddr,
            NS(ParticlesAddr_cobj_reserved_handle_size)( slot_size ),
            NS(ParticlesAddr_cobj_type_id)(), true ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE bool NS(ParticlesAddr_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT {
    return NS(CBuffer_can_add_copy_of_trivial_object)( buffer,
        NS(ParticlesAddr_cobj_reserved_handle_size)( NS(CBuffer_slot_size)(
            buffer ) ), ptr_requ_buffer_size, ptr_requ_slots, ptr_requ_objects,
                ptr_requ_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr) paddr;
    NS(ParticlesAddr_clear)( &paddr );
    return NS(ParticlesAddr_cbuffer_add_copy)( buffer, &paddr ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles,
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
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr) paddr;
    NS(ParticlesAddr_init)( &paddr, max_num_particles,
        charge0_addr, mass0_addr, beta0_addr, gamma0_addr, p0c_addr,
        s_addr, x_addr, y_addr, px_addr, py_addr, zeta_addr, psigma_addr,
        delta_addr, rpp_addr, rvv_addr, chi_addr, charge_ratio_addr,
        id_addr, at_element_addr, at_turn_addr, state_addr );
    return NS(ParticlesAddr_cbuffer_add_copy)( buffer, &paddr ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr ) {
    NS(cobj_size_type) const slot_size = NS(CBuffer_slot_size)( buffer );
    return NS(ParticlesAddr_from_cobj_index)(
        NS(CBuffer_add_copy_of_trivial_object)( buffer, paddr,
            NS(ParticlesAddr_cobj_reserved_handle_size)( slot_size ),
            NS(ParticlesAddr_cobj_type_id)(), true ) ); }

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLES_ADDR_COBJ_H__ */
