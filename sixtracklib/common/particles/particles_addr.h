#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLES_ADDR_C99_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLES_ADDR_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(Particles);
struct NS(CObjIndex);
struct NS(CBuffer);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(ParticlesAddr)
{
    NS(particles_num_type) max_num_particles
        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );

    NS(particles_addr_type) charge0_addr    SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) mass0_addr      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) beta0_addr      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) gamma0_addr     SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) p0c_addr        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );

    NS(particles_addr_type) s_addr          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) x_addr          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) y_addr          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) px_addr         SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) py_addr         SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) zeta_addr       SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );

    NS(particles_addr_type) psigma_addr     SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) delta_addr      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) rpp_addr        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) rvv_addr        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) chi_addr        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );

    NS(particles_addr_type) charge_ratio_addr
        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );

    NS(particles_addr_type) id_addr         SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) at_element_addr SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) at_turn_addr    SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) state_addr      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(ParticlesAddr);

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type)
NS(ParticlesAddr_cobj_type_id)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(ParticlesAddr_cobj_num_dataptrs)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(ParticlesAddr_cobj_actual_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(ParticlesAddr_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(ParticlesAddr_cobj_required_num_bytes)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr, NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* Helper functions: */

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_preset)( SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
    SIXTRL_RESTRICT addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(ParticlesAddr_clear)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
        SIXTRL_RESTRICT addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(ParticlesAddr_init)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT addr,
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

SIXTRL_STATIC SIXTRL_FN void NS(ParticlesAddr_copy)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(ParticlesAddr_compare_values)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */
/* Assignment from and to NS(Particles) */

SIXTRL_STATIC SIXTRL_FN void NS(ParticlesAddr_assign_from_particles)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT paddr,
    SIXTRL_PARTICLES_ARGPTR_DEC const struct NS(Particles) *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(ParticlesAddr_assign_to_particles)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr,
    SIXTRL_PARTICLES_ARGPTR_DEC struct NS(Particles)* SIXTRL_RESTRICT pset
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(ParticlesAddr_remap_addresses)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT paddr,
    NS(particles_addr_diff_type) const addr_offset
) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_particles_addr)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr) const*
NS(ParticlesAddr_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    struct NS(CObjIndex)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(ParticlesAddr) const*
NS(ParticlesAddr_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const index, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const index, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr) const*
NS(ParticlesAddr_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Particles_cobj_flat_buffer_store_addresses)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT paddr_buffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const index, NS(size_type) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Particles_cobj_flat_buffer_store_all_addresses)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT paddr_buffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const slot_size );

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(ParticlesAddr_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(ParticlesAddr)*
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

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(ParticlesAddr)*
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

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(ParticlesAddr)*
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

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(ParticlesAddr_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(ParticlesAddr_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(ParticlesAddr_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(ParticlesAddr_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(ParticlesAddr_cobj_required_num_bytes_ext)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr) const*
NS(ParticlesAddr_const_from_cbuffer_ext)( SIXTRL_CBUFFER_ARGPTR_DEC
        const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_from_cbuffer_ext)( SIXTRL_CBUFFER_ARGPTR_DEC
        struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_preset_ext)( SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
    SIXTRL_RESTRICT paddr ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(ParticlesAddr_assign_from_particles_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT part_addr,
    SIXTRL_PARTICLE_ARGPTR_DEC const struct NS(Particles) *const
        SIXTRL_RESTRICT p );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(ParticlesAddr_assign_to_particles_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT part_addr,
    SIXTRL_PARTICLE_ARGPTR_DEC struct NS(Particles)*  SIXTRL_RESTRICT p );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(ParticlesAddr_remap_addresses_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT part_addr,
    NS(particles_addr_diff_type) const addr_offset );

/* ------------------------------------------------------------------------ */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type)
NS(ParticlesAddr_prepare_buffer_based_on_particles_buffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT paddr_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT pbuffer );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type)
NS(ParticlesAddr_buffer_store_addresses)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT paddr_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT pbuffer, NS(size_type) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type)
NS(ParticlesAddr_buffer_store_all_addresses)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT paddr_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT pbuffer );

/* ------------------------------------------------------------------------ */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(ParticlesAddr_buffer_remap_adresses)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const buffer_index,
    NS(particles_addr_diff_type) const addr_offset );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(ParticlesAddr_buffer_all_remap_adresses)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_addr_diff_type) const addr_offset );

/* ------------------------------------------------------------------------ */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ParticlesAddr_cobj_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_new_ext)( SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)*
    SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
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

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT addr );

#endif /* !defined( _GPUCODE ) */
#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsTraits< ::NS(ParticlesAddr) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_PARTICLES_ADDR;
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_PARTICLES_ADDR > {
            typedef ::NS(ParticlesAddr) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* ************************************************************************* */
/* *****          Implementation of C inline functions                   *** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particles.h"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(ParticlesAddr_cobj_type_id)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_obj_id_type)
        )SIXTRL_COBJECTS_TYPE_ID_PARTICLES_ADDR; }

SIXTRL_INLINE NS(cobj_size_type) NS(ParticlesAddr_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(ParticlesAddr_cobj_actual_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(ParticlesAddr) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(ParticlesAddr_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    return NS(ParticlesAddr_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(ParticlesAddr_cobj_required_num_bytes)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr, NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    ( void )paddr; SIXTRL_ASSERT( NS(ParticlesAddr_cobj_num_dataptrs)() == 0u );
    return NS(ParticlesAddr_cobj_reserved_handle_size)( slot_size ); }

/* ------------------------------------------------------------------------- */
/* Helper functions: */

SIXTRL_INLINE SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_preset)( SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
    SIXTRL_RESTRICT paddr ) SIXTRL_NOEXCEPT {
        NS(ParticlesAddr_clear)( paddr ); return paddr; }

SIXTRL_INLINE void NS(ParticlesAddr_clear)( SIXTRL_PARTICLES_ADDR_ARGPTR_DEC
    NS(ParticlesAddr)* SIXTRL_RESTRICT paddr ) SIXTRL_NOEXCEPT {
    SIXTRL_STATIC_VAR NS(particles_addr_type) const NULL_ADDR =
        ( NS(particles_addr_type) )( uintptr_t )SIXTRL_NULL_ADDR;
    NS(ParticlesAddr_init)( paddr, ( NS(particles_num_type) )0u,
        NULL_ADDR, NULL_ADDR, NULL_ADDR, NULL_ADDR, NULL_ADDR,
        NULL_ADDR, NULL_ADDR, NULL_ADDR, NULL_ADDR, NULL_ADDR,
        NULL_ADDR, NULL_ADDR,
        NULL_ADDR, NULL_ADDR, NULL_ADDR, NULL_ADDR, NULL_ADDR,
        NULL_ADDR, NULL_ADDR, NULL_ADDR, NULL_ADDR ); }

SIXTRL_INLINE void NS(ParticlesAddr_init)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT paddr,
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
    NS(particles_addr_type) const state_addr ) SIXTRL_NOEXCEPT
{
    if( paddr != SIXTRL_NULLPTR ) {
        paddr->max_num_particles = max_num_particles;
        paddr->charge0_addr      = charge0_addr;
        paddr->mass0_addr        = mass0_addr;
        paddr->beta0_addr        = beta0_addr;
        paddr->gamma0_addr       = gamma0_addr;
        paddr->p0c_addr          = p0c_addr;

        paddr->s_addr            = s_addr;
        paddr->x_addr            = x_addr;
        paddr->y_addr            = y_addr;
        paddr->px_addr           = px_addr;
        paddr->py_addr           = py_addr;
        paddr->zeta_addr         = zeta_addr;
        paddr->psigma_addr       = psigma_addr;

        paddr->delta_addr        = delta_addr;
        paddr->rpp_addr          = rpp_addr;
        paddr->rvv_addr          = rvv_addr;
        paddr->chi_addr          = chi_addr;
        paddr->charge_ratio_addr = charge_ratio_addr;

        paddr->id_addr           = id_addr;
        paddr->at_element_addr   = at_element_addr;
        paddr->at_turn_addr      = at_turn_addr;
        paddr->state_addr        = state_addr; }
}

SIXTRL_INLINE void NS(ParticlesAddr_copy)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT {
    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) &&
        ( src  != dest ) ) { *dest = *src; }
}

SIXTRL_INLINE int NS(ParticlesAddr_compare_values)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT {
    int cmp_result = -1;

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        cmp_result = ( lhs->max_num_particles == rhs->max_num_particles )
            ? 0
            : ( ( lhs->max_num_particles > rhs->max_num_particles ) ? +1 : -1 );

        if( ( cmp_result == 0 ) && ( lhs->charge0_addr != rhs->charge0_addr ) ) {
            cmp_result = ( lhs->charge0_addr > rhs->charge0_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->mass0_addr != rhs->mass0_addr ) ) {
            cmp_result = ( lhs->mass0_addr > rhs->mass0_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->beta0_addr != rhs->beta0_addr ) ) {
            cmp_result = ( lhs->beta0_addr > rhs->beta0_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->gamma0_addr != rhs->gamma0_addr ) ) {
            cmp_result = ( lhs->gamma0_addr > rhs->gamma0_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->p0c_addr != rhs->p0c_addr ) ) {
            cmp_result = ( lhs->p0c_addr > rhs->p0c_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->s_addr != rhs->s_addr ) ) {
            cmp_result = ( lhs->s_addr > rhs->s_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->x_addr != rhs->x_addr ) ) {
            cmp_result = ( lhs->x_addr > rhs->x_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->y_addr != rhs->y_addr ) ) {
            cmp_result = ( lhs->y_addr > rhs->y_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->px_addr != rhs->px_addr ) ) {
            cmp_result = ( lhs->px_addr > rhs->px_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->py_addr != rhs->py_addr ) ) {
            cmp_result = ( lhs->py_addr > rhs->py_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->zeta_addr != rhs->zeta_addr ) ) {
            cmp_result = ( lhs->zeta_addr > rhs->zeta_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->psigma_addr != rhs->psigma_addr ) ) {
            cmp_result = ( lhs->psigma_addr > rhs->psigma_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->delta_addr != rhs->delta_addr ) ) {
            cmp_result = ( lhs->delta_addr > rhs->delta_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->rpp_addr != rhs->rpp_addr ) ) {
            cmp_result = ( lhs->rpp_addr > rhs->rpp_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->rvv_addr != rhs->rvv_addr ) ) {
            cmp_result = ( lhs->rvv_addr > rhs->rvv_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->chi_addr != rhs->chi_addr ) ) {
            cmp_result = ( lhs->chi_addr > rhs->chi_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) &&
            ( lhs->charge_ratio_addr != rhs->charge_ratio_addr ) )
        {
            cmp_result = ( lhs->charge_ratio_addr > rhs->charge_ratio_addr )
                ? +1 : -1;
        }

        if( ( cmp_result == 0 ) && ( lhs->id_addr != rhs->id_addr ) ) {
            cmp_result = ( lhs->id_addr > rhs->id_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) &&
            ( lhs->at_element_addr != rhs->at_element_addr ) )
        {
            cmp_result = ( lhs->at_element_addr >
                rhs->at_element_addr ) ? +1 : -1;
        }

        if( ( cmp_result == 0 ) && ( lhs->at_turn_addr != rhs->at_turn_addr ) ) {
            cmp_result = ( lhs->at_turn_addr > rhs->at_turn_addr ) ? +1 : -1; }

        if( ( cmp_result == 0 ) && ( lhs->state_addr != rhs->state_addr ) ) {
            cmp_result = ( lhs->state_addr > rhs->state_addr ) ? +1 : -1; }
    }
    else if( lhs != SIXTRL_NULLPTR )
    {
        cmp_result = 1;
    }

    return cmp_result;
}

/* ------------------------------------------------------------------------- */
/* Assignment from and to NS(Particles) */

SIXTRL_INLINE void NS(ParticlesAddr_assign_from_particles)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT paddr,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( ( uintptr_t )pset != ( uintptr_t )paddr );
    NS(ParticlesAddr_init)( paddr, NS(Particles_max_num_particles)( pset ),
        NS(Particles_charge0_addr)( pset ), NS(Particles_mass0_addr)( pset ),
        NS(Particles_beta0_addr)( pset ),   NS(Particles_gamma0_addr)( pset ),
        NS(Particles_p0c_addr)( pset ),
        NS(Particles_s_addr)( pset ), NS(Particles_x_addr)( pset ),
        NS(Particles_y_addr)( pset ), NS(Particles_px_addr)( pset ),
        NS(Particles_py_addr)( pset ), NS(Particles_zeta_addr)( pset ),
        NS(Particles_psigma_addr)( pset ),  NS(Particles_delta_addr)( pset ),
        NS(Particles_rpp_addr)( pset ), NS(Particles_rvv_addr)( pset ),
        NS(Particles_chi_addr)( pset ), NS(Particles_charge_ratio_addr)( pset ),
        NS(Particles_id_addr)( pset ), NS(Particles_at_element_addr)( pset ),
        NS(Particles_at_turn_addr)( pset ),
        NS(Particles_state_addr)( pset ) ); }

SIXTRL_INLINE void NS(ParticlesAddr_assign_to_particles)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr,
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT pset
) SIXTRL_NOEXCEPT {

    SIXTRL_ASSERT( ( pset != SIXTRL_NULLPTR ) && ( paddr != SIXTRL_NULLPTR ) );
    SIXTRL_ASSERT( ( uintptr_t )pset != ( uintptr_t )paddr );
    SIXTRL_ASSERT(
        ( NS(Particles_max_num_particles)( pset ) ==
          ( NS(particles_num_type) )0u ) ||
        ( NS(Particles_max_num_particles)( pset ) ==
          paddr->max_num_particles ) );

    SIXTRL_ASSERT( NS(Particles_charge0_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_mass0_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_beta0_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_gamma0_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_p0c_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_s_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_x_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_y_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_px_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_py_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_zeta_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_psigma_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_delta_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_rpp_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_rvv_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_chi_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_charge_ratio_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_id_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_at_element_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_at_turn_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    SIXTRL_ASSERT( NS(Particles_state_addr)( pset ) ==
                   ( NS(particles_addr_type) )SIXTRL_NULL_ADDR );

    NS(Particles_set_max_num_particles)(     pset, paddr->max_num_particles );

    NS(Particles_set_charge0_addr)(      pset, paddr->charge0_addr );
    NS(Particles_set_mass0_addr)(        pset, paddr->mass0_addr );
    NS(Particles_set_beta0_addr)(        pset, paddr->beta0_addr );
    NS(Particles_set_gamma0_addr)(       pset, paddr->gamma0_addr );
    NS(Particles_set_p0c_addr)(          pset, paddr->p0c_addr );

    NS(Particles_set_s_addr)(            pset, paddr->s_addr );
    NS(Particles_set_x_addr)(            pset, paddr->x_addr );
    NS(Particles_set_y_addr)(            pset, paddr->y_addr );
    NS(Particles_set_px_addr)(           pset, paddr->px_addr );
    NS(Particles_set_py_addr)(           pset, paddr->py_addr );
    NS(Particles_set_zeta_addr)(         pset, paddr->zeta_addr );
    NS(Particles_set_psigma_addr)(       pset, paddr->psigma_addr );

    NS(Particles_set_delta_addr)(        pset, paddr->delta_addr );
    NS(Particles_set_rpp_addr)(          pset, paddr->rpp_addr );
    NS(Particles_set_rvv_addr)(          pset, paddr->rvv_addr );
    NS(Particles_set_chi_addr)(          pset, paddr->chi_addr );
    NS(Particles_set_charge_ratio_addr)( pset, paddr->charge_ratio_addr );

    NS(Particles_set_id_addr)(           pset, paddr->id_addr );
    NS(Particles_set_at_element_addr)(   pset, paddr->at_element_addr );
    NS(Particles_set_at_turn_addr)(      pset, paddr->at_turn_addr );
    NS(Particles_set_state_addr)(        pset, paddr->state_addr );
}

SIXTRL_INLINE void NS(ParticlesAddr_remap_addresses)(
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)* SIXTRL_RESTRICT paddr,
    NS(particles_addr_diff_type) const addr_offset ) SIXTRL_NOEXCEPT
{
    typedef NS(particles_addr_type) address_t;
    typedef NS(particles_addr_diff_type) diff_t;

    SIXTRL_STATIC_VAR address_t const ADDR0 = ( address_t )SIXTRL_NULL_ADDR;

    if( paddr != SIXTRL_NULLPTR )
    {
        if( ( addr_offset == ( NS(particles_addr_diff_type) )0u ) ||
            ( paddr->charge0_addr      == ADDR0 ) ||
            ( paddr->mass0_addr        == ADDR0 ) ||
            ( paddr->beta0_addr        == ADDR0 ) ||
            ( paddr->gamma0_addr       == ADDR0 ) ||
            ( paddr->p0c_addr          == ADDR0 ) ||
            ( paddr->s_addr            == ADDR0 ) ||
            ( paddr->x_addr            == ADDR0 ) ||
            ( paddr->y_addr            == ADDR0 ) ||
            ( paddr->px_addr           == ADDR0 ) ||
            ( paddr->py_addr           == ADDR0 ) ||
            ( paddr->zeta_addr         == ADDR0 ) ||
            ( paddr->psigma_addr       == ADDR0 ) ||
            ( paddr->delta_addr        == ADDR0 ) ||
            ( paddr->rpp_addr          == ADDR0 ) ||
            ( paddr->rvv_addr          == ADDR0 ) ||
            ( paddr->chi_addr          == ADDR0 ) ||
            ( paddr->charge_ratio_addr == ADDR0 ) ||
            ( paddr->id_addr           == ADDR0 ) ||
            ( paddr->at_element_addr   == ADDR0 ) ||
            ( paddr->at_turn_addr      == ADDR0 ) ||
            ( paddr->state_addr        == ADDR0 ) ) { return; }
    }

    if( ( paddr != SIXTRL_NULLPTR ) && ( addr_offset > ( diff_t )0u ) )
    {
        /* TODO: Prevent overflows by checking value + addr_offset <= MAX */

        paddr->charge0_addr        += addr_offset;
        paddr->mass0_addr          += addr_offset;
        paddr->beta0_addr          += addr_offset;
        paddr->gamma0_addr         += addr_offset;
        paddr->p0c_addr            += addr_offset;
        paddr->s_addr              += addr_offset;
        paddr->x_addr              += addr_offset;
        paddr->y_addr              += addr_offset;
        paddr->px_addr             += addr_offset;
        paddr->py_addr             += addr_offset;
        paddr->zeta_addr           += addr_offset;
        paddr->psigma_addr         += addr_offset;
        paddr->delta_addr          += addr_offset;
        paddr->rpp_addr            += addr_offset;
        paddr->rvv_addr            += addr_offset;
        paddr->chi_addr            += addr_offset;
        paddr->charge_ratio_addr   += addr_offset;
        paddr->id_addr             += addr_offset;
        paddr->at_element_addr     += addr_offset;
        paddr->at_turn_addr        += addr_offset;
        paddr->state_addr          += addr_offset;
    }
    else if( ( paddr != SIXTRL_NULLPTR ) && ( addr_offset < ( diff_t )0u ) )
    {
        address_t const abs_offset = ( address_t )( -addr_offset );

        paddr->charge0_addr = ( paddr->charge0_addr >= abs_offset )
            ? paddr->charge0_addr - abs_offset : ADDR0;

        paddr->mass0_addr = ( paddr->mass0_addr >= abs_offset )
            ? paddr->mass0_addr - abs_offset  : ADDR0;

        paddr->beta0_addr = ( paddr->beta0_addr  >= abs_offset )
            ? paddr->beta0_addr - abs_offset  : ADDR0;

        paddr->gamma0_addr = ( paddr->gamma0_addr >= abs_offset )
            ? paddr->gamma0_addr - abs_offset : ADDR0;

        paddr->p0c_addr = ( paddr->p0c_addr >= abs_offset )
            ? paddr->p0c_addr - abs_offset : ADDR0;

        paddr->s_addr = ( paddr->s_addr >= abs_offset )
            ? paddr->s_addr - abs_offset : ADDR0;

        paddr->x_addr = ( paddr->x_addr >= abs_offset )
            ? paddr->x_addr - abs_offset : ADDR0;

        paddr->y_addr = ( paddr->y_addr >= abs_offset )
            ? paddr->y_addr - abs_offset : ADDR0;

        paddr->px_addr = ( paddr->px_addr >= abs_offset )
            ? paddr->px_addr - abs_offset : ADDR0;

        paddr->py_addr = ( paddr->py_addr >= abs_offset )
            ? paddr->py_addr - abs_offset : ADDR0;

        paddr->zeta_addr = ( paddr->zeta_addr >= abs_offset )
            ? paddr->zeta_addr - abs_offset : ADDR0;

        paddr->psigma_addr = ( paddr->psigma_addr >= abs_offset )
            ? paddr->psigma_addr - abs_offset : ADDR0;

        paddr->delta_addr = ( paddr->delta_addr  >= abs_offset )
            ? paddr->delta_addr - abs_offset : ADDR0;

        paddr->rpp_addr = ( paddr->rpp_addr >= abs_offset )
            ? paddr->rpp_addr - abs_offset : ADDR0;

        paddr->rvv_addr = ( paddr->rvv_addr >= abs_offset )
            ? paddr->rvv_addr - abs_offset : ADDR0;

        paddr->chi_addr = ( paddr->chi_addr >= abs_offset )
            ? paddr->chi_addr - abs_offset : ADDR0;

        paddr->charge_ratio_addr = ( paddr->charge_ratio_addr  >= abs_offset )
            ? paddr->charge_ratio_addr - abs_offset : ADDR0;

        paddr->id_addr = ( paddr->id_addr >= abs_offset )
            ? paddr->id_addr - abs_offset : ADDR0;

        paddr->at_element_addr = ( paddr->at_element_addr >= abs_offset )
            ? paddr->at_element_addr - abs_offset : ADDR0;

        paddr->at_turn_addr = ( paddr->at_turn_addr >= abs_offset )
            ? paddr->at_turn_addr - abs_offset : ADDR0;

        paddr->state_addr = ( paddr->state_addr >= abs_offset )
            ? paddr->state_addr - abs_offset   : ADDR0;
    }
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_particles_addr)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(ParticlesAddr_cobj_type_id)(),
        NS(ParticlesAddr_cobj_actual_handle_size)( 0u ) ); }

SIXTRL_INLINE SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr) const*
NS(ParticlesAddr_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_particles_addr)( obj ) )
        ? ( SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    struct NS(CObjIndex)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_particles_addr)( obj ) )
        ? ( SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr) const*
NS(ParticlesAddr_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(ParticlesAddr_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(ParticlesAddr_from_cobj_index)( NS(CObjFlatBuffer_index)(
        buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr) const*
NS(ParticlesAddr_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(ParticlesAddr_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( b, idx ) ); }

SIXTRL_INLINE SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(ParticlesAddr_from_cobj_index)( NS(CBuffer_index_at)( b, idx ) ); }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(status_type) NS(Particles_cobj_flat_buffer_store_addresses)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT paddr_buffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) {

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC NS(ParticlesAddr)* paddr =
        NS(ParticlesAddr_from_cobj_flat_buffer)( paddr_buffer, idx, slot_size );
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* pset =
            NS(Particles_const_from_cobj_flat_buffer)( pbuffer, idx, slot_size );

    if( paddr != SIXTRL_NULLPTR )
    {
        if( pset != SIXTRL_NULLPTR )
        {
            NS(ParticlesAddr_assign_from_particles)( paddr, pset );
        }
        else
        {
            NS(ParticlesAddr_clear)( paddr );
        }

        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(status_type) NS(Particles_cobj_flat_buffer_store_all_addresses)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT paddr_buffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const slot_size ) {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    NS(size_type) const num_pset_objects = NS(CObjFlatBuffer_num_objects)(
        pbuffer, slot_size );
    NS(size_type) const num_paddr_objects = NS(CObjFlatBuffer_num_objects)(
        paddr_buffer, slot_size );

    if( num_pset_objects == num_paddr_objects )
    {
        NS(size_type) ii = ( NS(size_type) )0u;
        for( ; ii < num_pset_objects ; ++ii )
        {
            status = NS(Particles_cobj_flat_buffer_store_addresses)(
                paddr_buffer, pbuffer, ii, slot_size );
            if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) break;
        }
    }
    return status;
}

/* ------------------------------------------------------------------------- */

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

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT b,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(ParticlesAddr) paddr;
    NS(ParticlesAddr_clear)( &paddr );
    return NS(ParticlesAddr_cobj_flat_buffer_add_copy)( b, slot_size, &paddr ); }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(ParticlesAddr)*
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
    SIXTRL_CBUFFER_ARGPTR_DEC NS(ParticlesAddr) paddr;
    NS(ParticlesAddr_init)( &paddr, max_num_particles,
        charge0_addr, mass0_addr, beta0_addr, gamma0_addr, p0c_addr,
        s_addr, x_addr, y_addr, px_addr, py_addr, zeta_addr, psigma_addr,
        delta_addr, rpp_addr, rvv_addr, chi_addr, charge_ratio_addr,
        id_addr, at_element_addr, at_turn_addr, state_addr );
    return NS(ParticlesAddr_cobj_flat_buffer_add_copy)( b, slot_size, &paddr ); }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_CBUFFER_DATAPTR_DEC NS(ParticlesAddr)* )( uintptr_t
        )NS(CObjIndex_begin_addr)( NS(CObjFlatBuffer_add_copy_of_trivial_object)(
            buffer, slot_size, paddr,
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

SIXTRL_INLINE SIXTRL_CBUFFER_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(ParticlesAddr) paddr;
    NS(ParticlesAddr_clear)( &paddr );
    return NS(ParticlesAddr_cbuffer_add_copy)( buffer, &paddr ); }

SIXTRL_INLINE SIXTRL_CBUFFER_ARGPTR_DEC NS(ParticlesAddr)*
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
    SIXTRL_CBUFFER_ARGPTR_DEC NS(ParticlesAddr) paddr;
    NS(ParticlesAddr_init)( &paddr, max_num_particles,
        charge0_addr, mass0_addr, beta0_addr, gamma0_addr, p0c_addr,
        s_addr, x_addr, y_addr, px_addr, py_addr, zeta_addr, psigma_addr,
        delta_addr, rpp_addr, rvv_addr, chi_addr, charge_ratio_addr,
        id_addr, at_element_addr, at_turn_addr, state_addr );
    return NS(ParticlesAddr_cbuffer_add_copy)( buffer, &paddr ); }

SIXTRL_INLINE SIXTRL_CBUFFER_ARGPTR_DEC NS(ParticlesAddr)*
NS(ParticlesAddr_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ADDR_ARGPTR_DEC const NS(ParticlesAddr) *const
        SIXTRL_RESTRICT paddr ) {
    return ( SIXTRL_CBUFFER_ARGPTR_DEC NS(ParticlesAddr)* )( uintptr_t
        )NS(CObjIndex_begin_addr)( NS(CBuffer_add_copy_of_trivial_object)(
            buffer, paddr, NS(ParticlesAddr_cobj_reserved_handle_size)(
                NS(CBuffer_slot_size)( buffer ) ),
            NS(ParticlesAddr_cobj_type_id)(), true ) ); }

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLES_ADDR_H__ */
