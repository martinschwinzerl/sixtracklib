#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) && \
    ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER == 1 )
struct NS(SingleParticleView);
#else/*  !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER )  */
struct NS(SingleParticle);
#endif /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER )  */

struct NS(CObjIndex);
#if !defined( _GPUCODE )
struct NS(CBuffer);
#endif /* !defined( _GPUCODE ) */

/* ========================================================================= */

typedef SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) struct NS(Particles)
{
    NS(particles_num_type)  max_num_particles SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_num_type)  num_particles     SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) charge0_addr      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* C */
    NS(particles_addr_type) mass0_addr        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* eV */
    NS(particles_addr_type) beta0_addr        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* nounit */
    NS(particles_addr_type) gamma0_addr       SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* nounit */
    NS(particles_addr_type) p0c_addr          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* eV */

    NS(particles_addr_type) s_addr            SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* [m] */
    NS(particles_addr_type) x_addr            SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* [m] */
    NS(particles_addr_type) y_addr            SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* [m] */
    NS(particles_addr_type) px_addr           SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* Px/P0 */
    NS(particles_addr_type) py_addr           SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* Py/P0 */
    NS(particles_addr_type) zeta_addr         SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* */

    NS(particles_addr_type) psigma_addr       SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* (E-E0) / (beta0 P0c) conjugate of sigma */
    NS(particles_addr_type) delta_addr        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* P/P0-1 = 1/rpp-1 */
    NS(particles_addr_type) rpp_addr          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* ratio P0 /P */
    NS(particles_addr_type) rvv_addr          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* ratio beta / beta0 */
    NS(particles_addr_type) chi_addr          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* q/q0 * m/m0  */
    NS(particles_addr_type) charge_ratio_addr SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN ); /* ratio q/q0 */

    NS(particles_addr_type) id_addr           SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) at_element_addr   SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) at_turn_addr      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particles_addr_type) state_addr        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(Particles);

/* ========================================================================== */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type)
NS(Particles_cobj_type_id)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(Particles_cobj_num_dataptrs)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(Particles_cobj_actual_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(Particles_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(Particles_cobj_required_num_bytes)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_preset)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_clear)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_num_type) NS(Particles_max_num_particles)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_num_type)
NS(Particles_default_max_num_particles)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_max_num_particles)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const num_particles ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(particles_num_type) NS(Particles_num_particles)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_num_type)
NS(Particles_default_num_particles)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_num_particles)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const num_particles ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_particles)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_range_contains_particle_set)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(CObjIndex_range_total_num_particle_sets)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_num_type)
NS(CObjIndex_range_total_num_individual_particles)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_contains_particle_set)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT begin,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(CObjFlatBuffer_total_num_particle_sets)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_num_type)
NS(CObjFlatBuffer_total_num_individual_particles)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_is_particle_set_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_charge0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_charge0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const x_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_charge0_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_charge0_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_charge0_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_charge0_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;


SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_charge0_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_charge0_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_charge0)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_charge0)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_charge0)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const charge0_value ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_mass0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_mass0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const mass0_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_mass0_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_mass0_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_mass0_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_mass0_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;


SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_mass0_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_mass0_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_mass0)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_mass0)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_mass0)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const mass0_value ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_beta0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_beta0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const beta0_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_beta0_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_beta0_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_beta0_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_beta0_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_beta0_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_beta0_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_beta0)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_beta0)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_beta0)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const beta0_value ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_gamma0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_gamma0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const gamma0_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_gamma0_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_gamma0_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_gamma0_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_gamma0_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_gamma0_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_gamma0_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_gamma0)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_gamma0)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_gamma0)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const gamma0_value ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_p0c_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_p0c_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const p0c_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_p0c_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_p0c_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_p0c_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_p0c_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_p0c_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_p0c_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_p0c)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_p0c)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_p0c)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const p0c_value ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_s_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_s_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const s_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_s_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_s_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_s_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_s_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_s_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_s_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_s)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_s)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_s)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const s_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_add_to_s)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_s ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_scale_s)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_s ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_x_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_x_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const x_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_x_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_x_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_x_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_x_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_x_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_x_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_x)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_x)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_x)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const x_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_add_to_x)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_x ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_scale_x)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_x ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_y_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_y_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const y_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_y_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_y_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_y_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_y_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_y_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_y_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_y)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_y)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_y)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const y_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_add_to_y)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_y ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_scale_y)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_y ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_px_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_px_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const zeta_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_px_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_px_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_px_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_px_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_px_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_px_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_px)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_px)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_px)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const zeta_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_add_to_px)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_px ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_scale_px)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_px ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_py_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_py_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const py_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_py_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_py_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_py_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_py_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_py_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_py_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_py)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_py)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_py)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const py_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_add_to_py)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_py ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_scale_py)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_py ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_zeta_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_zeta_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const zeta_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_zeta_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_zeta_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_zeta_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_zeta_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_zeta_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_zeta_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_zeta)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_zeta)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_zeta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const zeta_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_add_to_zeta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_zeta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_scale_zeta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_zeta ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_psigma_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_psigma_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const psigma_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_psigma_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_psigma_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_psigma_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_psigma_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_psigma_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_psigma_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_psigma)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_psigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_psigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const psigma_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_add_to_psigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_psigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_scale_psigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_psigma ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_delta_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_delta_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const delta_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_delta_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_delta_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_delta_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_delta_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_delta_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_delta_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_delta)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_delta)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_delta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const delta_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_add_to_delta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_delta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_scale_delta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_delta ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_rpp_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_rpp_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const rpp_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_rpp_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_rpp_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_rpp_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_rpp_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_rpp_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_rpp_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_rpp)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_rpp)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_rpp)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const rpp_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_scale_rpp)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_rpp ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_rvv_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_rvv_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const rvv_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_rvv_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_rvv_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_rvv_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_rvv_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_rvv_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_rvv_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_rvv)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_rvv)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_rvv)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const rvv_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_scale_rvv)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_rvv ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_chi_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_chi_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const chi_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_chi_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_chi_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_chi_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_chi_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_chi_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_chi_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_chi)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_chi)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_chi)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const chi_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_scale_chi)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_chi ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_charge_ratio_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_charge_ratio_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const charge_ratio_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_charge_ratio_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_charge_ratio_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_charge_ratio_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_charge_ratio_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_const_pointer)
NS(Particles_const_reserved_charge_ratio_end)( SIXTRL_PARTICLES_ARGPTR_DEC
    const NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_real_pointer)
NS(Particles_reserved_charge_ratio_end)( SIXTRL_PARTICLES_ARGPTR_DEC
    NS(Particles)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_default_charge_ratio)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_charge_ratio)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_charge_ratio)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const charge_ratio_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_scale_charge_ratio)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_charge_ratio ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_id_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_id_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const id_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_index_type) const*
NS(Particles_id_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_index_type) const*
NS(Particles_id_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_index_type)*
NS(Particles_id_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_index_type)*
NS(Particles_id_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_const_pointer)
NS(Particles_const_reserved_id_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_pointer)
NS(Particles_reserved_id_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particles_default_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particles_id)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_id)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_index_type) const id_value ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_at_element_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_at_element_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const at_element_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_index_const_pointer)
NS(Particles_at_element_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_const_pointer)
NS(Particles_at_element_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_pointer)
NS(Particles_at_element_begin)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_pointer)
NS(Particles_at_element_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particles_default_at_element)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particles_at_element)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_at_element)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_index_type) const at_element_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_increment_at_element)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_const_pointer)
NS(Particles_const_reserved_at_element_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_pointer)
NS(Particles_reserved_at_element_end)( SIXTRL_PARTICLES_ARGPTR_DEC
    NS(Particles)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_at_turn_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_at_turn_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const at_turn_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_index_const_pointer)
NS(Particles_at_turn_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_const_pointer)
NS(Particles_at_turn_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_pointer) NS(Particles_at_turn_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_pointer) NS(Particles_at_turn_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_const_pointer)
NS(Particles_const_reserved_at_turn_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_pointer)
NS(Particles_reserved_at_turn_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particles_default_at_turn)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particles_at_turn)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_at_turn)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_index_type) const at_turn_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_increment_at_turn)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_finish_turn)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_index_type) const start_at_element ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particles_addr_type) NS(Particles_state_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_state_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const state_addr ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particles_index_const_pointer)
NS(Particles_state_const_begin)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_const_pointer)
NS(Particles_state_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_pointer) NS(Particles_state_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_pointer) NS(Particles_state_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_const_pointer)
NS(Particles_const_reserved_state_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_index_pointer)
NS(Particles_reserved_state_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particles_default_state)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Particles_state)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_set_state)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_index_type) const state_value ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(Particles_is_lost)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particles_is_active)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Particles_is_not_lost)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_num_type) NS(Particles_num_lost_particles)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_num_type)
NS(Particles_num_active_particles)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_mark_as_lost)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_index_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_keep_active_if_not_lost)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_index_type) const index ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_mass_ratio)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_mass)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_charge)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_beta)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_gamma)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_tau)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_sigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_ptau)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN void NS(Particles_update_tau)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const tau ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_update_sigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const tau ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_update_delta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const delta ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_update_psigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const psigma ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_update_ptau)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const ptau ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_energy0)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(Particles_energy)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_update_energy)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const new_energy_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_add_to_energy)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_energy ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(Particles_init_attributes)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_init_attributes_detailed)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_index_type) start_id, NS(particle_index_type) const id_stride,
    NS(particle_index_type) const at_element,
    NS(particle_index_type) const at_turn ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN void NS(Particles_init_from_charge0_mass0_p0c)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const p0c ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_init_from_charge0_mass0_beta0)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const beta0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_init_from_charge0_mass0_gamma0)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const gamma0 ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_init_with_pointers)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(Particles_min_max_id)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_id
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_init_min_max_attributes_for_find)(
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_at_turn,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_at_turn
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_min_max_attributes_sanity_check)(
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_at_turn,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_at_turn
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_merge_min_max_attributes_from_find)(
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_at_turn,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_at_turn,
    NS(particle_index_type) const found_min_id,
    NS(particle_index_type) const found_max_id,
    NS(particle_index_type) const found_min_at_element,
    NS(particle_index_type) const found_max_at_element,
    NS(particle_index_type) const found_min_at_turn,
    NS(particle_index_type) const found_max_at_turn ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Particles_find_min_max_attributes)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_at_turn,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_at_turn
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void
NS(Particles_cobj_flat_buffer_find_min_max_attributes_in_particle_sets)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size, NS(size_type) const  num_particle_sets,
    SIXTRL_ARGPTR_DEC NS(size_type) const* SIXTRL_RESTRICT indices_begin,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_part_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_part_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_element_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_element_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_turn_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_turn_id );

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_cobj_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT offsets,
    NS(size_type) const max_num_offsets,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_cobj_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT counts,
    NS(size_type) const max_num_counts,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_cobj_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT sizes,
    NS(size_type) const max_num_sizes,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(Particles_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(Particles)*
NS(Particles_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(Particles)*
NS(Particles_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(Particles)*
NS(Particles_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN bool NS(Particles_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(particles_num_type) const max_num_particles,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles );

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr );

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_copy_single)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    NS(particles_num_type) const destination_index,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT source,
    NS(particles_num_type) const source_index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_copy_range)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
        SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT source,
    NS(particles_num_type) const source_start_index,
    NS(particles_num_type) const source_end_index,
    NS(particles_num_type) const destination_start_index,
    NS(particles_num_type) stride ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_copy)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT source ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

#if defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) && \
    ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER == 1 )

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_to_single_particle)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    NS(particles_num_type) const index,
    SIXTRL_PARTICLE_ARGPTR_DEC struct NS(SingleParticleView)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_from_single_particle)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT pset,
    NS(particles_num_type) const index,
    SIXTRL_PARTICLE_ARGPTR_DEC const struct NS(SingleParticleView) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

#else /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_to_single_particle)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    NS(particles_num_type) const index,
    SIXTRL_PARTICLE_ARGPTR_DEC struct NS(SingleParticle)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_from_single_particle)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT pset,
    NS(particles_num_type) const index,
    SIXTRL_PARTICLE_ARGPTR_DEC const struct NS(SingleParticle) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

#endif /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const*
NS(Particles_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const
    struct NS(CObjIndex) *const SIXTRL_RESTRICT obj_index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
    SIXTRL_RESTRICT obj_index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(Particles) const*
NS(Particles_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const index,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(Particles)*
NS(Particles_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const index,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const*
NS(Particles_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(Particles_difference_max_value)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLES_ARGPTR_DEC NS(particles_num_type)*
        SIXTRL_RESTRICT max_value_index,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const*
NS(Particles_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Particles_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(particles_num_type) const max_num_particles,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particles_difference_max_value_ext)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLES_ARGPTR_DEC NS(particles_num_type)*
        SIXTRL_RESTRICT max_value_index,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(Particles_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Particles_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Particles_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Particles_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Particles_cobj_required_num_bytes_ext)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Particles)* NS(Particles_preset_ext)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(Particles_clear_ext)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(particles_num_type)
NS(Particles_max_num_particles_ext)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(particles_num_type)
NS(Particles_num_particles_ext)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(CObjIndex_range_contains_particle_set_ext)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(CObjIndex_range_total_num_particle_sets_ext)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(particles_num_type)
NS(CObjIndex_range_total_num_individual_particles_ext)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(CObjFlatBuffer_contains_particle_set_ext)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT begin,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(CObjFlatBuffer_total_num_particle_sets_ext)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(particles_num_type)
NS(CObjFlatBuffer_total_num_individual_particles_ext)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(CObjFlatBuffer_is_particle_set_buffer_ext)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(CBuffer_is_particle_set_buffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT buffer ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(CBuffer_num_particle_sets)( SIXTRL_CBUFFER_ARGPTR_DEC const
    struct NS(CBuffer) *const SIXTRL_RESTRICT buffer ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(particles_num_type)
NS(CBuffer_num_individual_particles)( SIXTRL_CBUFFER_ARGPTR_DEC const
    struct NS(CBuffer) *const SIXTRL_RESTRICT buffer ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type)
NS(Particles_sort_and_find_min_max_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particles_find_min_max_attributes_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_part_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_part_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_element_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_element_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_turn_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_turn_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(Particles_cbuffer_find_min_max_attributes_in_particle_sets)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT buf,
    NS(size_type) const  num_particle_sets,
    SIXTRL_ARGPTR_DEC NS(size_type) const* SIXTRL_RESTRICT indices_begin,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_part_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_part_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_element_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_element_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_turn_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_turn_id );
/*
SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particles_sort_ext)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particles_sort_detail_ext)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    SIXTRL_ARGPTR_DEC NS(particles_sort_flags) const* SIXTRL_RESTRICT sort_flags,
    NS(size_type) const num_sort_flags ) SIXTRL_NOEXCEPT;
*/
#endif /* Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsTraits< ::NS(Particles) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_PARTICLES_COLLECTION;
    };

    template<> struct CObjectsNumPointersTraits< ::NS(Particles) >
    {
        static constexpr cobj_size_type NUM_POINTERS =
            SIXTRL_CXX_NAMESPACE::cobj_size_type{
                SIXTRL_PARTICLES_NUM_DATAPTRS };
    };

    template<> struct CObjectsActualHandleSizeTraits< ::NS(Particles) >
    {
        SIXTRL_FN static cobj_size_type HANDLE_SIZE(
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Particles_cobj_actual_handle_size)( slot_size ); }
    };

    template<> struct CObjectsReservedHandleSizeTraits< ::NS(Particles) >
    {
        SIXTRL_FN static cobj_size_type HANDLE_SIZE(
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Particles_cobj_reserved_handle_size)( slot_size ); }
    };

    template<> struct CObjectsRequiredNumBytesTraits< ::NS(Particles) >
    {
        SIXTRL_FN static cobj_size_type REQUIRED_NUM_BYTES(
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(Particles) *const
                SIXTRL_RESTRICT pset,
            cobj_size_type slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Particles_cobj_required_num_bytes)( pset, slot_size ); }
    };

    template<> struct CObjectsAttributesOffsetsTraits< ::NS(Particles) >
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT offsets,
            cobj_size_type const max_num_offsets,
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(Particles) *const
                SIXTRL_RESTRICT pset,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Particles_cobj_attributes_offsets)( offsets,
                max_num_offsets, pset, slot_size ); }
    };

    template<> struct CObjectsAttributesSizesTraits< ::NS(Particles) >
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT sizes,
            cobj_size_type const max_num_sizes,
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(Particles) *const
                SIXTRL_RESTRICT pset,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Particles_cobj_attributes_sizes)(
                sizes, max_num_sizes, pset, slot_size ); }
    };

    template<> struct CObjectsAttributesCountsTraits< ::NS(Particles) >
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT counts,
            cobj_size_type const max_num_counts,
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(Particles) *const
                SIXTRL_RESTRICT pset,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Particles_cobj_attributes_counts)(
                counts, max_num_counts, pset, slot_size ); }
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_PARTICLES_COLLECTION > {
            typedef ::NS(Particles) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* ========================================================================= */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/particles/particle_helper.h"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(Particles_cobj_type_id)( ) SIXTRL_NOEXCEPT
{ return ( NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_PARTICLES_COLLECTION; }

SIXTRL_INLINE NS(cobj_size_type) NS(Particles_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return (NS(cobj_size_type))NS(PARTICLES_NUM_DATAPTRS); }

SIXTRL_INLINE NS(cobj_size_type) NS(Particles_cobj_actual_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size  = ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(Particles) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(Particles_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(Particles_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(Particles_cobj_required_num_bytes)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {

    NS(cobj_size_type) num_bytes = ( NS(cobj_size_type) )0u;
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) SIZES[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) COUNTS[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_ASSERT( NS(Particles_cobj_num_dataptrs)() ==
                   ( NS(cobj_size_type) )SIXTRL_PARTICLES_NUM_DATAPTRS );
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;

    status = NS(Particles_cobj_attributes_sizes)(
        &SIZES[ 0 ], NS(Particles_cobj_num_dataptrs)(), pset, slot_size );

    if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        status = NS(Particles_cobj_attributes_counts)(
            &COUNTS[ 0 ], NS(Particles_cobj_num_dataptrs)(), pset, slot_size );

    if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        num_bytes = NS(CObjFlatBuffer_predict_required_num_bytes)(
            NS(Particles_cobj_reserved_handle_size)( slot_size ),
            NS(Particles_cobj_num_dataptrs)(),
            &SIZES[ 0 ], &COUNTS[ 0 ], slot_size );

    return num_bytes; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(Particles)* NS(Particles_preset)( SIXTRL_PARTICLES_ARGPTR_DEC
    NS(Particles)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    if( p != SIXTRL_NULLPTR ) NS(Particles_clear)( p ); return p; }

SIXTRL_INLINE NS(status_type) NS(Particles_clear)( SIXTRL_PARTICLES_ARGPTR_DEC
    NS(Particles)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    NS(Particles_init_with_pointers)( p,
        NS(Particles_default_num_particles)(),
        NS(Particles_default_num_particles)(),
        SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
        SIXTRL_NULLPTR,
        SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
        SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
        SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
        SIXTRL_NULLPTR,
        SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR );

    return ( p != SIXTRL_NULLPTR )
        ? ( NS(status_type) )SIXTRL_STATUS_SUCCESS
        : ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_num_type) NS(Particles_max_num_particles)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR ); return p->max_num_particles; }

SIXTRL_INLINE NS(particles_num_type) NS(Particles_default_max_num_particles)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particles_num_type) )0u; }

SIXTRL_INLINE void NS(Particles_set_max_num_particles)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const max_num_particles ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( max_num_particles >= ( NS(particles_num_type) )0u );
    p->max_num_particles = max_num_particles; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(particles_num_type) NS(Particles_default_num_particles)(
    void ) SIXTRL_NOEXCEPT { return ( NS(particles_num_type) )0u; }

SIXTRL_INLINE NS(particles_num_type) NS(Particles_num_particles)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->num_particles; }

SIXTRL_INLINE void NS(Particles_set_num_particles)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const num_particles ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( num_particles >= ( NS(particles_num_type) )0u );
    p->num_particles = num_particles; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_particles)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjIndex_is_consistent_with_type)( obj,
    NS(Particles_cobj_type_id)(),
    NS(Particles_cobj_actual_handle_size)( 0u ) ); }

SIXTRL_INLINE bool NS(CObjIndex_range_contains_particle_set)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT {
    bool contains_particle_sets = false;
    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
    {
        SIXTRL_ASSERT( ( ( uintptr_t )it ) >= ( ( uintptr_t )end ) );
        for( ; ( ( it != end ) && ( !contains_particle_sets ) ) ; ++it )
        {
            contains_particle_sets = NS(CObjIndex_is_particles)( it++ );
        }
    }
    return contains_particle_sets;
}

SIXTRL_INLINE NS(size_type) NS(CObjIndex_range_total_num_particle_sets)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    st_size_t num_particle_sets = ( st_size_t )0u;
    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) ) {
        SIXTRL_ASSERT( ( ( uintptr_t )it ) >= ( ( uintptr_t )end ) );
        for( ; it != end ; ++it ) {
            num_particle_sets += (
                st_size_t )NS(CObjIndex_is_particles)( it ); } }
    return num_particle_sets; }

SIXTRL_INLINE NS(particles_num_type)
NS(CObjIndex_range_total_num_individual_particles)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT {
    NS(particles_num_type) num_particles = ( NS(particles_num_type) )0u;
    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) ) {
        for( ; it != end ; ++it ) {
            if( NS(CObjIndex_is_particles)( it ) ) {
                SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* pset =
                    NS(Particles_const_from_cobj_index)( it );
                SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                               NS(Particles_num_particles)( pset ) );
                num_particles += NS(Particles_num_particles)( pset ); } }
    }
    return num_particles; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE bool NS(CObjFlatBuffer_contains_particle_set)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_range_contains_particle_set)(
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ) ); }

SIXTRL_INLINE NS(size_type) NS(CObjFlatBuffer_total_num_particle_sets)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_range_total_num_particle_sets)(
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ) ); }

SIXTRL_INLINE NS(particles_num_type) NS(CObjFlatBuffer_total_num_individual_particles)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_range_total_num_individual_particles)(
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ) ); }

SIXTRL_INLINE bool NS(CObjFlatBuffer_is_particle_set_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return ( NS(CObjFlatBuffer_num_objects)( buffer, slot_size ) ==
        NS(CObjIndex_range_total_num_particle_sets)(
            NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
            NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ) ) ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_charge0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->charge0_addr; }

SIXTRL_INLINE void NS(Particles_set_charge0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const charge0_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->charge0_addr = charge0_addr;
}

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_charge0_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->charge0_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_charge0_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_charge0_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_charge0_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_charge0_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_charge0_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_charge0_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_charge0_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_charge0_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_charge0_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_charge0_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_charge0)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_charge0)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_charge0)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_charge0_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_charge0_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_charge0)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const charge0_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_charge0_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_charge0_begin)( p )[ index ] = charge0_value; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_mass0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->mass0_addr; }

SIXTRL_INLINE void NS(Particles_set_mass0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const mass0_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->mass0_addr = mass0_addr;
}

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_mass0_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->mass0_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_mass0_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_mass0_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_mass0_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_mass0_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_mass0_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_mass0_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_mass0_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_mass0_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_mass0_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_mass0_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_mass0)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_mass0)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_mass0)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_mass0_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_mass0_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_mass0)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const mass0_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_mass0_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_mass0_begin)( p )[ index ] = mass0_value; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_beta0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->beta0_addr; }

SIXTRL_INLINE void NS(Particles_set_beta0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const beta0_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->beta0_addr = beta0_addr;
}

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_beta0_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->beta0_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_beta0_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_beta0_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_beta0_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_beta0_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_beta0_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_beta0_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_beta0_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_beta0_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_beta0_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_beta0_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_beta0)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_beta0)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_beta0)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_beta0_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_beta0_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_beta0)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const beta0_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_beta0_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_beta0_begin)( p )[ index ] = beta0_value; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_gamma0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->gamma0_addr; }

SIXTRL_INLINE void NS(Particles_set_gamma0_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const gamma0_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->gamma0_addr = gamma0_addr;
}

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_gamma0_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->gamma0_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_gamma0_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_gamma0_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_gamma0_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_gamma0_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_gamma0_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_gamma0_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_gamma0_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_gamma0_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_gamma0_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_gamma0_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_gamma0)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_gamma0)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_gamma0)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_gamma0_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_gamma0_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_gamma0)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const gamma0_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_gamma0_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_gamma0_begin)( p )[ index ] = gamma0_value; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_p0c_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->p0c_addr; }

SIXTRL_INLINE void NS(Particles_set_p0c_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const p0c_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->p0c_addr = p0c_addr;
}

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_p0c_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->p0c_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_p0c_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_p0c_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_p0c_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_p0c_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_p0c_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_p0c_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_p0c_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_p0c_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_p0c_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_p0c_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_p0c)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_p0c)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_p0c)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_p0c_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_p0c_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_p0c)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const p0c_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_p0c_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_p0c_begin)( p )[ index ] = p0c_value; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_s_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->s_addr; }

SIXTRL_INLINE void NS(Particles_set_s_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const s_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->s_addr = s_addr;
}

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_s_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->s_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_s_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_s_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_s_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_s_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_s_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_s_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_s_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_s_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_s_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_s_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_s)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_s)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_s)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_s_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_s_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_s)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const s_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_s_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_s_begin)( p )[ index ] = s_value; }

SIXTRL_INLINE void NS(Particles_add_to_s)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_s ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_s_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_s_begin)( p )[ index ] += d_s; }

SIXTRL_INLINE void NS(Particles_scale_s)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_s ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_s_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_s_begin)( p )[ index ] *= factor_s; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_x_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->x_addr; }

SIXTRL_INLINE void NS(Particles_set_x_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const x_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->x_addr = x_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_x_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->x_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_x_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_x_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_x_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_x_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_x_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_x_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_x_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_x_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_x_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_x_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_x)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_x)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_x)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_x_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_x_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_x)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const x_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_x_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_x_begin)( p )[ index ] = x_value; }

SIXTRL_INLINE void NS(Particles_add_to_x)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_x ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_x_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_x_begin)( p )[ index ] += d_x; }

SIXTRL_INLINE void NS(Particles_scale_x)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_x ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_x_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_x_begin)( p )[ index ] *= factor_x; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_y_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->y_addr; }

SIXTRL_INLINE void NS(Particles_set_y_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const y_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->y_addr = y_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_y_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->y_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_y_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_y_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_y_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_y_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_y_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_y_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_y_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_y_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_y_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_y_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_y)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_y)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_y)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_y_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_y_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_y)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const y_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_y_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_y_begin)( p )[ index ] = y_value; }

SIXTRL_INLINE void NS(Particles_add_to_y)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_y ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_y_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_y_begin)( p )[ index ] += d_y; }

SIXTRL_INLINE void NS(Particles_scale_y)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_y ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_y_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_y_begin)( p )[ index ] *= factor_y; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_px_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->px_addr; }

SIXTRL_INLINE void NS(Particles_set_px_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const px_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->px_addr = px_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_px_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->px_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_px_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_px_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_px_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_px_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_px_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_px_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_px_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_px_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_px_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_px_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_px)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_px)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_px)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_px_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_px_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_px)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const px_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_px_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_px_begin)( p )[ index ] = px_value; }

SIXTRL_INLINE void NS(Particles_add_to_px)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_px ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_px_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_px_begin)( p )[ index ] += d_px; }

SIXTRL_INLINE void NS(Particles_scale_px)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_px ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_px_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_px_begin)( p )[ index ] *= factor_px; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_py_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->py_addr; }

SIXTRL_INLINE void NS(Particles_set_py_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const py_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->py_addr = py_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_py_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->py_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_py_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_py_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_py_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_py_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_py_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_py_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_py_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_py_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_py_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_py_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_py)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_py)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_py)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_py_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_py_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_py)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const py_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_py_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_py_begin)( p )[ index ] = py_value; }

SIXTRL_INLINE void NS(Particles_add_to_py)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_py ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_px_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_py_begin)( p )[ index ] += d_py; }

SIXTRL_INLINE void NS(Particles_scale_py)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_py ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_px_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_py_begin)( p )[ index ] *= factor_py; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_zeta_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->zeta_addr; }

SIXTRL_INLINE void NS(Particles_set_zeta_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const zeta_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->zeta_addr = zeta_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_zeta_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->zeta_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_zeta_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_zeta_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_zeta_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_zeta_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_zeta_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_zeta_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_zeta_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_zeta_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_zeta_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_zeta_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_zeta)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_zeta)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_zeta)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_zeta_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_zeta_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_zeta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const zeta_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_zeta_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_zeta_begin)( p )[ index ] = zeta_value; }

SIXTRL_INLINE void NS(Particles_add_to_zeta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_zeta ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_zeta_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_zeta_begin)( p )[ index ] += d_zeta; }

SIXTRL_INLINE void NS(Particles_scale_zeta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_zeta ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_zeta_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_zeta_begin)( p )[ index ] *= factor_zeta; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_delta_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->delta_addr; }

SIXTRL_INLINE void NS(Particles_set_delta_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const delta_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->delta_addr = delta_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_delta_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->delta_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_delta_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_delta_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_delta_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_delta_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_delta_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_delta_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_delta_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_delta_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_delta_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_delta_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_delta)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_delta)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_delta)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_delta_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_delta_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_delta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const delta_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_delta_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_delta_begin)( p )[ index ] = delta_value; }

SIXTRL_INLINE void NS(Particles_add_to_delta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_delta ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_delta_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_delta_begin)( p )[ index ] += d_delta; }

SIXTRL_INLINE void NS(Particles_scale_delta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_delta ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_delta_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_delta_begin)( p )[ index ] *= factor_delta; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_psigma_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->psigma_addr; }

SIXTRL_INLINE void NS(Particles_set_psigma_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const psigma_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->psigma_addr = psigma_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_psigma_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->psigma_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_psigma_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_psigma_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_psigma_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_psigma_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_psigma_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_psigma_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_psigma_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_psigma_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_psigma_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_psigma_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_psigma)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_psigma)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_psigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_psigma_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_psigma_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_psigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const psigma_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_psigma_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_psigma_begin)( p )[ index ] = psigma_value; }

SIXTRL_INLINE void NS(Particles_add_to_psigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_psigma ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_psigma_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_psigma_begin)( p )[ index ] += d_psigma; }

SIXTRL_INLINE void NS(Particles_scale_psigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_psigma ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_psigma_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_psigma_begin)( p )[ index ] *= factor_psigma; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_rpp_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->rpp_addr; }

SIXTRL_INLINE void NS(Particles_set_rpp_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const rpp_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->rpp_addr = rpp_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_rpp_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->rpp_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_rpp_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_rpp_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_rpp_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_rpp_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_rpp_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_rpp_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_rpp_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_rpp_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_rpp_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_rpp_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_rpp)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_rpp)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_rpp)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_rpp_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_rpp_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_rpp)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const rpp_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_rpp_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_rpp_begin)( p )[ index ] = rpp_value; }

SIXTRL_INLINE void NS(Particles_scale_rpp)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_rpp ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_rpp_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_rpp_begin)( p )[ index ] *= factor_rpp; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_rvv_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->rvv_addr; }

SIXTRL_INLINE void NS(Particles_set_rvv_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const rvv_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->rvv_addr = rvv_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_rvv_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->rvv_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_rvv_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_rvv_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_rvv_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_rvv_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_rvv_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_rvv_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_rvv_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_rvv_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_rvv_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_rvv_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_rvv)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_rvv)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_rvv)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_rvv_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_rvv_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_rvv)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const rvv_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_rvv_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_rvv_begin)( p )[ index ] = rvv_value; }

SIXTRL_INLINE void NS(Particles_scale_rvv)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_rvv ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_rvv_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_rvv_begin)( p )[ index ] *= factor_rvv; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_chi_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->chi_addr; }

SIXTRL_INLINE void NS(Particles_set_chi_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const chi_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->chi_addr = chi_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_chi_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )( uintptr_t )p->chi_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer) NS(Particles_chi_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_chi_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_chi_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_chi_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_chi_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_chi_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_chi_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_chi_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_chi_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_chi_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_chi)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_chi)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_chi)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_chi_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_chi_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_chi)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const chi_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_chi_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_chi_begin)( p )[ index ] = chi_value; }

SIXTRL_INLINE void NS(Particles_scale_chi)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_chi ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_chi_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_chi_begin)( p )[ index ] *= factor_chi; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_charge_ratio_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->charge_ratio_addr; }

SIXTRL_INLINE void NS(Particles_set_charge_ratio_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const charge_ratio_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->charge_ratio_addr = charge_ratio_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_charge_ratio_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_real_const_pointer ) )(
        uintptr_t )p->charge_ratio_addr; }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_charge_ratio_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_real_const_pointer) ptr_end =
        NS(Particles_charge_ratio_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_charge_ratio_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_charge_ratio_const_begin)( p ); }

SIXTRL_INLINE NS(particles_real_pointer) NS(Particles_charge_ratio_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_real_pointer)
    )NS(Particles_charge_ratio_const_end)( p ); }

SIXTRL_INLINE NS(particles_real_const_pointer)
NS(Particles_const_reserved_charge_ratio_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_real_const_pointer) ptr =
        NS(Particles_charge_ratio_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_real_pointer)
NS(Particles_reserved_charge_ratio_end)( SIXTRL_PARTICLES_ARGPTR_DEC
    NS(Particles)* SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_real_pointer)
        )NS(Particles_const_reserved_charge_ratio_end)( pset ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_default_charge_ratio)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_charge_ratio)(); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_charge_ratio)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_charge_ratio_const_begin)(
        p ) != SIXTRL_NULLPTR );
    return NS(Particles_charge_ratio_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_charge_ratio)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const charge_ratio_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_charge_ratio_const_begin)(
        p ) != SIXTRL_NULLPTR );
    NS(Particles_charge_ratio_begin)( p )[ index ] = charge_ratio_value; }

SIXTRL_INLINE void NS(Particles_scale_charge_ratio)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const factor_charge_ratio ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_charge_ratio_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_charge_ratio_begin)( p )[ index ] *= factor_charge_ratio; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_id_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR ); return p->id_addr; }

SIXTRL_INLINE void NS(Particles_set_id_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const id_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR ); p->id_addr = id_addr; }

SIXTRL_INLINE NS(particles_index_const_pointer) NS(Particles_id_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_index_const_pointer ) )( uintptr_t )p->id_addr; }

SIXTRL_INLINE NS(particles_index_const_pointer)
NS(Particles_id_const_end)( SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles)
    *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_index_const_pointer) ptr_end =
        NS(Particles_id_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_index_pointer) NS(Particles_id_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_index_pointer)
    )NS(Particles_id_const_begin)( p ); }

SIXTRL_INLINE NS(particles_index_pointer) NS(Particles_id_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_index_pointer)
    )NS(Particles_id_const_end)( p ); }

SIXTRL_INLINE NS(particles_index_const_pointer)
NS(Particles_const_reserved_id_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_index_const_pointer) ptr =
        NS(Particles_id_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_index_pointer)
NS(Particles_reserved_id_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_index_pointer)
        )NS(Particles_const_reserved_id_end)( pset ); }

SIXTRL_INLINE NS(particle_index_type) NS(Particles_default_id)( void
    ) SIXTRL_NOEXCEPT { return NS(Particle_default_id)(); }

SIXTRL_INLINE NS(particle_index_type) NS(Particles_id)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_id_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_id_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_id)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_index_type) const id_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_id_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_id_begin)( p )[ index ] = id_value; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_at_element_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->at_element_addr; }

SIXTRL_INLINE void NS(Particles_set_at_element_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const at_element_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->at_element_addr = at_element_addr; }

SIXTRL_INLINE NS(particles_index_const_pointer)
NS(Particles_at_element_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_index_const_pointer ) )(
        uintptr_t )p->at_element_addr; }

SIXTRL_INLINE NS(particles_index_const_pointer)
NS(Particles_at_element_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_index_const_pointer) ptr_end =
        NS(Particles_at_element_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_index_pointer) NS(Particles_at_element_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_index_pointer)
    )NS(Particles_at_element_const_begin)( p ); }

SIXTRL_INLINE NS(particles_index_pointer) NS(Particles_at_element_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_index_pointer)
    )NS(Particles_at_element_const_end)( p ); }

SIXTRL_INLINE NS(particles_index_const_pointer)
NS(Particles_const_reserved_at_element_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_index_const_pointer) ptr =
        NS(Particles_at_element_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_index_pointer)
NS(Particles_reserved_at_element_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_index_pointer)
        )NS(Particles_const_reserved_at_element_end)( pset ); }

SIXTRL_INLINE NS(particle_index_type) NS(Particles_default_at_element)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_at_element)(); }

SIXTRL_INLINE NS(particle_index_type) NS(Particles_at_element)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_at_element_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_at_element_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_at_element)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_index_type) const at_element_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_at_element_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_at_element_begin)( p )[ index ] = at_element_value; }

SIXTRL_INLINE void NS(Particles_increment_at_element)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_is_active)( p, index ) );
    SIXTRL_ASSERT( NS(Particles_at_element)( p, index ) >=
                   ( NS(particle_index_type) )0u );
    SIXTRL_ASSERT( NS(Particles_is_active)( p, index ) );
    SIXTRL_ASSERT( NS(Particles_at_element_const_begin)( p ) != SIXTRL_NULLPTR );
    ++NS(Particles_at_element_begin)( p )[ index ]; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_at_turn_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->at_turn_addr; }

SIXTRL_INLINE void NS(Particles_set_at_turn_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const at_turn_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->at_turn_addr = at_turn_addr; }

SIXTRL_INLINE NS(particles_index_const_pointer)
NS(Particles_at_turn_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_index_const_pointer ) )(
        uintptr_t )p->at_turn_addr; }

SIXTRL_INLINE NS(particles_index_const_pointer)
NS(Particles_at_turn_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_index_const_pointer) ptr_end =
        NS(Particles_at_turn_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_index_pointer) NS(Particles_at_turn_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_index_pointer)
    )NS(Particles_at_turn_const_begin)( p ); }

SIXTRL_INLINE NS(particles_index_pointer) NS(Particles_at_turn_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_index_pointer)
    )NS(Particles_at_turn_const_end)( p ); }

SIXTRL_INLINE NS(particles_index_const_pointer)
NS(Particles_const_reserved_at_turn_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_index_const_pointer) ptr =
        NS(Particles_at_turn_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_index_pointer)
NS(Particles_reserved_at_turn_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_index_pointer)
        )NS(Particles_const_reserved_at_turn_end)( pset ); }

SIXTRL_INLINE NS(particle_index_type) NS(Particles_default_at_turn)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_at_turn)(); }

SIXTRL_INLINE NS(particle_index_type) NS(Particles_at_turn)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_at_turn_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_at_turn_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_at_turn)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_index_type) const at_turn_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_at_turn_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_at_turn_begin)( p )[ index ] = at_turn_value; }

SIXTRL_INLINE void NS(Particles_increment_at_turn)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_at_turn_const_begin)( p ) != SIXTRL_NULLPTR );
    ++NS(Particles_at_turn_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_finish_turn)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_index_type) const start_at_element ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( start_at_element >= ( NS(particle_index_type) )0u );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_is_active)( p, index ) );
    SIXTRL_ASSERT( NS(Particles_at_element)( p, index ) >=
                   ( NS(particle_index_type) )0u );
    SIXTRL_ASSERT( NS(Particles_is_active)( p, index ) );
    SIXTRL_ASSERT( NS(Particles_at_turn)( p, index ) >=
                   ( NS(particle_index_type) )0u );
    SIXTRL_ASSERT( NS(Particles_at_element_begin)( p ) != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_at_turn_const_begin)( p ) != SIXTRL_NULLPTR );
    ++NS(Particles_at_turn_begin)( p )[ index ];
    NS(Particles_at_element_begin)( p )[ index ] = start_at_element; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particles_addr_type) NS(Particles_state_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return p->state_addr; }

SIXTRL_INLINE void NS(Particles_set_state_addr)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_addr_type) const state_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    p->state_addr = state_addr; }

SIXTRL_INLINE NS(particles_index_const_pointer) NS(Particles_state_const_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    return ( NS(particles_index_const_pointer ) )(
        uintptr_t )p->state_addr; }

SIXTRL_INLINE NS(particles_index_const_pointer) NS(Particles_state_const_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    NS(particles_index_const_pointer) ptr_end =
        NS(Particles_state_const_begin)( p );
    if( ptr_end != SIXTRL_NULLPTR )
        ptr_end = ptr_end + ( intptr_t )NS(Particles_num_particles)( p );
    return ptr_end; }

SIXTRL_INLINE NS(particles_index_pointer) NS(Particles_state_begin)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_index_pointer)
    )NS(Particles_state_const_begin)( p ); }

SIXTRL_INLINE NS(particles_index_pointer) NS(Particles_state_end)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return ( NS(particles_index_pointer)
    )NS(Particles_state_const_end)( p ); }

SIXTRL_INLINE NS(particles_index_const_pointer)
NS(Particles_const_reserved_state_end)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( pset ) >=
                   ( NS(particles_num_type) )0u );
    SIXTRL_ASSERT( NS(Particles_max_num_particles)( pset ) >=
                   NS(Particles_num_particles)( pset ) );
    NS(particles_index_const_pointer) ptr =
        NS(Particles_state_const_begin)( pset );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(Particles_max_num_particles)( pset );
    return ptr; }

SIXTRL_INLINE NS(particles_index_pointer)
NS(Particles_reserved_state_end)( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT {
    return ( NS(particles_index_pointer)
        )NS(Particles_const_reserved_state_end)( pset ); }

SIXTRL_INLINE NS(particle_index_type) NS(Particles_default_state)(
    void ) SIXTRL_NOEXCEPT { return NS(Particle_default_state)(); }

SIXTRL_INLINE NS(particle_index_type) NS(Particles_state)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_state_const_begin)( p ) != SIXTRL_NULLPTR );
    return NS(Particles_state_const_begin)( p )[ index ]; }

SIXTRL_INLINE void NS(Particles_set_state)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_index_type) const state_value ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_state_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_state_begin)( p )[ index ] = state_value; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Particles_is_lost)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return ( NS(Particles_state)( p, index ) != ( NS(particle_index_type) )1 ); }

SIXTRL_INLINE bool NS(Particles_is_active)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return ( NS(Particles_state)( p, index ) == ( NS(particle_index_type) )1 ); }

SIXTRL_INLINE bool NS(Particles_is_not_lost)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particles_is_active)( p, index ); }

SIXTRL_INLINE void NS(Particles_mark_as_lost)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    NS(Particles_set_state)( p, index, ( NS(particle_index_type) )0u ); }

SIXTRL_INLINE void NS(Particles_keep_active_if_not_lost)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Particles_num_particles)( p ) > index );
    SIXTRL_ASSERT( NS(Particles_state_const_begin)( p ) != SIXTRL_NULLPTR );
    NS(Particles_state_begin)( p )[ index ] &= ( NS(particle_index_type) )1u;
}

SIXTRL_INLINE NS(particles_num_type) NS(Particles_num_lost_particles)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    typedef NS(particles_num_type) npart_type;
    npart_type num_lost = 0;
    npart_type const npart = NS(Particles_num_particles)( p );
    npart_type ii = 0;
    for( ; ii < npart ; ++ii )
        num_lost += ( npart_type )NS(Particles_is_lost)( p, ii );
    return num_lost; }

SIXTRL_INLINE NS(particles_num_type)
NS(Particles_num_active_particles)( SIXTRL_PARTICLES_ARGPTR_DEC const
    NS(Particles) *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    typedef NS(particles_num_type) npart_type;
    npart_type num_active = 0;
    npart_type const npart = NS(Particles_num_particles)( p );
    npart_type ii = 0;
    for( ; ii < npart ; ++ii )
        num_active += ( npart_type )NS(Particles_is_active)( p, ii );
    return num_active; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_type) NS(Particles_beta)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particle_beta_impl)(
        NS(Particles_beta0)( p, index ), NS(Particles_rvv)( p, index ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_gamma)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particle_gamma_impl)(
        NS(Particles_beta0)( p, index ), NS(Particles_rvv)( p, index ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_mass_ratio)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particle_mass_ratio_impl)( NS(Particles_charge_ratio)( p, index ),
        NS(Particles_chi)( p, index ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_mass)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particle_mass_impl)( NS(Particles_charge_ratio)( p, index ),
        NS(Particles_chi)( p, index ), NS(Particles_mass0)( p, index ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_charge)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particle_charge_impl)( NS(Particles_charge_ratio)( p, index ),
        NS(Particles_charge0)( p, index ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(particle_real_type) NS(Particles_tau)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particle_tau_impl)( NS(Particles_zeta)( p, index ),
        NS(Particles_rvv)( p, index ), NS(Particles_beta0)( p, index ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_sigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particle_sigma_impl)( NS(Particles_zeta)( p, index ),
        NS(Particles_rvv)( p, index ) ); }

SIXTRL_INLINE NS(particle_real_type) NS(Particles_ptau)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particle_ptau_impl)( NS(Particles_delta)( p, index ),
        NS(Particles_beta0)( p, index ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE void NS(Particles_update_tau)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const tau ) SIXTRL_NOEXCEPT {
    NS(Particles_set_zeta)( p, index,
        NS(Particle_zeta_from_tau_impl)( tau,
            NS(Particles_rvv)( p, index ),
            NS(Particles_beta0)( p, index ) ) ); }

SIXTRL_INLINE void NS(Particles_update_sigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const sigma ) SIXTRL_NOEXCEPT {
    NS(Particles_set_zeta)( p, index, NS(Particle_zeta_from_sigma_impl)(
        sigma, NS(Particles_rvv)( p, index ) ) ); }

SIXTRL_INLINE void NS(Particles_update_delta)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const delta ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_real_type) real_type;
    real_type updated_delta  = ( real_type )0.0;
    real_type updated_psigma = ( real_type )0.0;
    real_type updated_rpp    = ( real_type )0.0;
    real_type updated_rvv    = ( real_type )0.0;

    NS(Particle_update_delta_impl)( delta, NS(Particles_beta0)( p, index ),
        &updated_delta, &updated_psigma, &updated_rpp, &updated_rvv );

    NS(Particles_set_delta)(  p, index, updated_delta );
    NS(Particles_set_psigma)( p, index, updated_psigma );
    NS(Particles_set_rpp)(    p, index, updated_rpp );
    NS(Particles_set_rvv)(    p, index, updated_rvv );
}

SIXTRL_INLINE void NS(Particles_update_psigma)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const psigma ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_real_type) real_type;
    real_type updated_delta  = ( real_type )0.0;
    real_type updated_psigma = ( real_type )0.0;
    real_type updated_rpp    = ( real_type )0.0;
    real_type updated_rvv    = ( real_type )0.0;

    NS(Particle_update_psigma_impl)( psigma, NS(Particles_beta0)( p, index ),
        &updated_delta, &updated_psigma, &updated_rpp, &updated_rvv );

    NS(Particles_set_delta)(  p, index, updated_delta );
    NS(Particles_set_psigma)( p, index, updated_psigma );
    NS(Particles_set_rpp)(    p, index, updated_rpp );
    NS(Particles_set_rvv)(    p, index, updated_rvv );
}

SIXTRL_INLINE void NS(Particles_update_ptau)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const ptau ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_real_type) real_type;
    real_type updated_delta  = ( real_type )0.0;
    real_type updated_psigma = ( real_type )0.0;
    real_type updated_rpp    = ( real_type )0.0;
    real_type updated_rvv    = ( real_type )0.0;

    NS(Particle_update_ptau_impl)( ptau, NS(Particles_beta0)( p, index ),
        &updated_delta, &updated_psigma, &updated_rpp, &updated_rvv );

    NS(Particles_set_delta)(  p, index, updated_delta );
    NS(Particles_set_psigma)( p, index, updated_psigma );
    NS(Particles_set_rpp)(    p, index, updated_rpp );
    NS(Particles_set_rvv)(    p, index, updated_rvv );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(particle_real_type) NS(Particles_energy0)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particle_energy0_impl)( NS(Particles_mass0)( p, index ),
        NS(Particles_p0c)( p, index ) );
}

SIXTRL_INLINE NS(particle_real_type) NS(Particles_energy)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particles_num_type) const index ) SIXTRL_NOEXCEPT {
    return NS(Particle_energy_impl)( NS(Particles_p0c)( p, index ),
        NS(Particles_mass0)( p, index ), NS(Particles_mass_ratio)( p, index ),
        NS(Particles_delta)( p, index ), NS(Particles_beta0)( p, index ) ); }

SIXTRL_INLINE void NS(Particles_update_energy)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const new_energy_value ) SIXTRL_NOEXCEPT {
    NS(Particles_add_to_energy)( p, index, new_energy_value -
        NS(Particles_energy)( p, index ) ); }

SIXTRL_INLINE void NS(Particles_add_to_energy)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particles_num_type) const index,
    NS(particle_real_type) const d_energy ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_type) real_type;
    real_type zeta = NS(Particles_zeta)( p, index );
    real_type updated_delta  = ( real_type )0.0;
    real_type updated_psigma = ( real_type )0.0;
    real_type updated_rpp    = ( real_type )0.0;
    real_type updated_rvv    = ( real_type )0.0;

    NS(Particle_add_to_energy_impl)( NS(Particles_energy0)( p, index ),
        NS(Particles_delta)( p, index ), NS(Particles_rvv)( p, index ),
        NS(Particles_beta0)( p, index ), d_energy, &zeta, &updated_delta,
        &updated_psigma, &updated_rpp, &updated_rvv );

    NS(Particles_set_zeta)(   p, index, zeta );
    NS(Particles_set_delta)(  p, index, updated_delta );
    NS(Particles_set_psigma)( p, index, updated_psigma );
    NS(Particles_set_rpp)(    p, index, updated_rpp );
    NS(Particles_set_rvv)(    p, index, updated_rvv ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(Particles_init_attributes)( SIXTRL_PARTICLES_ARGPTR_DEC
    NS(Particles)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    NS(Particles_init_attributes_detailed)( p,
        NS(Particles_default_id)(), 1, 0, 0 ); }

SIXTRL_INLINE void NS(Particles_init_attributes_detailed)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_index_type) id, NS(particle_index_type) const id_stride,
    NS(particle_index_type) const at_element,
    NS(particle_index_type) const at_turn ) SIXTRL_NOEXCEPT {
    typedef NS(particle_index_type) index_type;
    typedef NS(particles_num_type)  npart_type;
    if( ( p != SIXTRL_NULLPTR ) &&
        ( id >= ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_ID ) &&
        ( id <= ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_ID ) &&
        ( id_stride > ( index_type )0 ) &&
        ( at_element >= ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) &&
        ( at_element <= ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT ) &&
        ( at_turn    >= ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN ) &&
        ( at_turn    <= ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN ) ) {
        npart_type const npart = NS(Particles_num_particles)( p );
        npart_type ii = ( npart_type )0u;
        for( ; ii < npart ; ++ii, id += id_stride ) {
            NS(Particles_set_id)( p, ii, id );
            NS(Particles_set_at_element)( p, ii, at_element );
            NS(Particles_set_at_turn)( p, ii, at_turn );
            NS(Particles_set_state)( p, ii, NS(Particles_default_state)() ); }
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE void NS(Particles_init_from_charge0_mass0_p0c)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const p0c ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_real_type) real_type;
    typedef NS(particles_num_type) npart_type;
    if( ( p != SIXTRL_NULLPTR ) && ( mass0 > ( real_type )0. ) &&
        ( p0c >= ( real_type )0. ) ) {
        npart_type const npart = NS(Particles_num_particles)( p );
        npart_type ii = ( npart_type )0u;
        real_type beta0 = NS(Particles_default_beta0)();
        real_type gamma0 = NS(Particles_default_gamma0)();
        NS(Particle_beta0_gamma0_from_charge0_mass0_p0c_impl)(
            charge0, mass0, p0c, &beta0, &gamma0 );
        for( ; ii < npart ; ++ii ) {
            NS(Particles_set_charge0)( p, ii, charge0 );
            NS(Particles_set_mass0)(   p, ii, mass0 );
            NS(Particles_set_beta0)(   p, ii, beta0 );
            NS(Particles_set_gamma0)(  p, ii, gamma0 );
            NS(Particles_set_p0c)(     p, ii, p0c ); }
    }
}

SIXTRL_INLINE void NS(Particles_init_from_charge0_mass0_beta0)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const beta0 ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_real_type) real_type;
    typedef NS(particles_num_type) npart_type;
    if( ( p != SIXTRL_NULLPTR ) && ( mass0 > ( real_type )0. ) &&
        ( beta0 >= ( real_type )0. ) && ( beta0 <= ( real_type )1. ) ) {
        npart_type const npart = NS(Particles_num_particles)( p );
        npart_type ii = ( npart_type )0u;
        real_type p0c    = NS(Particles_default_p0c)();
        real_type gamma0 = NS(Particles_default_gamma0)();
        NS(Particle_gamma0_p0c_from_charge0_mass0_beta0_impl)(
            charge0, mass0, beta0, &gamma0, &p0c );

        for( ; ii < npart ; ++ii ) {
            NS(Particles_set_charge0)( p, ii, charge0 );
            NS(Particles_set_mass0)( p, ii, mass0 );
            NS(Particles_set_beta0)( p, ii, beta0 );
            NS(Particles_set_gamma0)( p, ii, gamma0 );
            NS(Particles_set_p0c)( p, ii, p0c ); }
    }
}

SIXTRL_INLINE void NS(Particles_init_from_charge0_mass0_gamma0)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_type) const charge0, NS(particle_real_type) const mass0,
    NS(particle_real_type) const gamma0 ) SIXTRL_NOEXCEPT  {
    typedef SIXTRL_PARTICLES_DATAPTR_DEC NS(particle_real_type) real_type;
    typedef NS(particles_num_type) npart_type;
    if( ( p != SIXTRL_NULLPTR ) && ( mass0 > ( real_type )0. ) &&
        ( gamma0 >= ( real_type )1. ) ) {
        npart_type const npart = NS(Particles_num_particles)( p );
        npart_type ii = ( npart_type )0u;
        real_type beta0 = NS(Particles_default_beta0)();
        real_type p0c = NS(Particles_default_p0c)();
        NS(Particle_beta0_p0c_from_charge0_mass0_gamma0_impl)(
            charge0, mass0, gamma0, &beta0, &p0c );

        for( ; ii < npart ; ++ii ) {
            NS(Particles_set_charge0)( p, ii, charge0 );
            NS(Particles_set_mass0)( p, ii, mass0 );
            NS(Particles_set_beta0)( p, ii, beta0 );
            NS(Particles_set_gamma0)( p, ii, gamma0 );
            NS(Particles_set_p0c)( p, ii, p0c ); }
    }
}

SIXTRL_INLINE void NS(Particles_init_with_pointers)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT pset,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr ) SIXTRL_NOEXCEPT {
    typedef NS(particles_addr_type) addr_type;
    if( ( pset != SIXTRL_NULLPTR ) &&
        ( num_particles >= ( NS(particles_num_type) )0u ) &&
        ( num_particles <= max_num_particles ) ) {

        NS(Particles_set_max_num_particles)( pset, max_num_particles );
        NS(Particles_set_num_particles)( pset, num_particles );

        NS(Particles_set_charge0_addr)(
            pset, ( addr_type )( uintptr_t )charge0_ptr );

        NS(Particles_set_mass0_addr)(
            pset, ( addr_type )( uintptr_t )mass0_ptr );

        NS(Particles_set_beta0_addr)(
            pset, ( addr_type )( uintptr_t )beta0_ptr );

        NS(Particles_set_gamma0_addr)(
            pset, ( addr_type )( uintptr_t )gamma0_ptr );

        NS(Particles_set_p0c_addr)(  pset, ( addr_type )( uintptr_t )p0c_ptr );
        NS(Particles_set_s_addr)(    pset, ( addr_type )( uintptr_t )s_ptr );
        NS(Particles_set_x_addr)(    pset, ( addr_type )( uintptr_t )x_ptr );
        NS(Particles_set_y_addr)(    pset, ( addr_type )( uintptr_t )y_ptr );
        NS(Particles_set_px_addr)(   pset, ( addr_type )( uintptr_t )px_ptr );
        NS(Particles_set_py_addr)(   pset, ( addr_type )( uintptr_t )py_ptr );
        NS(Particles_set_zeta_addr)( pset, ( addr_type )( uintptr_t )zeta_ptr );

        NS(Particles_set_delta_addr)( pset,
            ( addr_type )( uintptr_t )delta_ptr );

        NS(Particles_set_psigma_addr)( pset,
            ( addr_type )( uintptr_t )psigma_ptr );

        NS(Particles_set_rpp_addr)( pset, ( addr_type )( uintptr_t )rpp_ptr );
        NS(Particles_set_rvv_addr)( pset, ( addr_type )( uintptr_t )rvv_ptr );
        NS(Particles_set_chi_addr)( pset, ( addr_type )( uintptr_t )chi_ptr );

        NS(Particles_set_charge_ratio_addr)( pset,
            ( addr_type )( uintptr_t )charge_ratio_ptr );

        NS(Particles_set_id_addr)( pset, ( addr_type )( uintptr_t )id_ptr );
        NS(Particles_set_at_element_addr)( pset,
            ( addr_type )( uintptr_t )at_element_ptr );

        NS(Particles_set_at_turn_addr)( pset,
            ( addr_type )( uintptr_t )at_turn_ptr );

        NS(Particles_set_state_addr)( pset,
            ( addr_type )( uintptr_t )state_ptr );
    }
}

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(Particles_min_max_id)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_id
) SIXTRL_NOEXCEPT {
    typedef NS(particle_index_type) index_type;
    index_type min_id = ( index_type )0;
    index_type max_id = ( index_type )0;
    NS(particles_num_type) const npart = NS(Particles_num_particles)( pset );
    SIXTRL_PARTICLES_DATAPTR_DEC index_type const* ptr_ids =
        NS(Particles_id_const_begin)( pset );

    if( ( ptr_ids != SIXTRL_NULLPTR ) &&
        ( npart > ( NS(particles_num_type) )0 ) ) {
        NS(particles_num_type) ii = 0;

        NS(Particles_init_min_max_attributes_for_find)( &min_id, &max_id,
            SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR );

        for( ; ii < npart ; ++ii ) {
            index_type const id = ptr_ids[ ii ];
            if( ( id >= ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_ID ) &&
                ( id <= ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_ID ) )
            {
                SIXTRL_ASSERT( id != ( index_type )SIXTRL_PARTICLE_ILLEGAL_ID );
                if( min_id > id ) min_id = id;
                if( max_id < id ) max_id = id;
            }
        }

        NS(Particles_min_max_attributes_sanity_check)( &min_id, &max_id,
            SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR );
    }

    NS(Particles_merge_min_max_attributes_from_find)( ptr_min_id, ptr_max_id,
        SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
        min_id, max_id, ( index_type )SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT,
        ( index_type )SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT,
        ( index_type )SIXTRL_PARTICLE_ILLEGAL_AT_TURN,
        ( index_type )SIXTRL_PARTICLE_ILLEGAL_AT_TURN );
}

SIXTRL_INLINE void NS(Particles_init_min_max_attributes_for_find)(
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_at_turn,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_at_turn
) SIXTRL_NOEXCEPT
{
    typedef NS(particle_index_type) index_type;

    if( min_id != SIXTRL_NULLPTR ) *min_id = ( index_type
        )SIXTRL_PARTICLE_MAX_LEGAL_ID;

    if( max_id != SIXTRL_NULLPTR ) *max_id = ( index_type
        )SIXTRL_PARTICLE_MIN_LEGAL_ID;

    if( min_at_element != SIXTRL_NULLPTR ) *min_at_element = ( index_type
        )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT;

    if( max_at_element != SIXTRL_NULLPTR ) *max_at_element = ( index_type
        )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT;

    if( min_at_turn != SIXTRL_NULLPTR ) *min_at_turn = ( index_type
        )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN;

    if( max_at_turn != SIXTRL_NULLPTR ) *max_at_turn = ( index_type
        )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN;
}

SIXTRL_INLINE void NS(Particles_min_max_attributes_sanity_check)(
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_at_elem,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_at_elem,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT min_at_turn,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT max_at_turn
) SIXTRL_NOEXCEPT
{
    typedef NS(particle_index_type) idx_type;

    if( (  min_id != SIXTRL_NULLPTR ) && ( max_id != SIXTRL_NULLPTR ) &&
        ( *min_id != ( idx_type )SIXTRL_PARTICLE_ILLEGAL_ID ) &&
        ( *max_id != ( idx_type )SIXTRL_PARTICLE_ILLEGAL_ID ) )
    {
        if( ( *max_id < *min_id ) ||
            ( ( *min_id > ( idx_type )SIXTRL_PARTICLE_MAX_LEGAL_ID ) ||
              ( *min_id < ( idx_type )SIXTRL_PARTICLE_MIN_LEGAL_ID ) ||
              ( *max_id > ( idx_type )SIXTRL_PARTICLE_MAX_LEGAL_ID ) ||
              ( *max_id < ( idx_type )SIXTRL_PARTICLE_MIN_LEGAL_ID ) ) )
        {
            *min_id = ( idx_type )SIXTRL_PARTICLE_ILLEGAL_ID;
            *max_id = ( idx_type )SIXTRL_PARTICLE_ILLEGAL_ID;
        }
    }

    if( (  min_at_elem != SIXTRL_NULLPTR ) &&
        (  max_at_elem != SIXTRL_NULLPTR ) &&
        ( *min_at_elem != ( idx_type )SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT ) &&
        ( *max_at_elem != ( idx_type )SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT ) )
    {
        if( ( *max_at_elem < *min_at_elem ) ||
            ( ( *min_at_elem > ( idx_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT ) ||
              ( *min_at_elem < ( idx_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) ||
              ( *max_at_elem > ( idx_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT ) ||
              ( *max_at_elem < ( idx_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) ) )
        {
            *min_at_elem = ( idx_type )SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT;
            *max_at_elem = ( idx_type )SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT;
        }
    }

    if( (  min_at_turn != SIXTRL_NULLPTR ) &&
        (  max_at_turn != SIXTRL_NULLPTR ) &&
        ( *min_at_turn != ( idx_type )SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT ) &&
        ( *max_at_turn != ( idx_type )SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT ) )
    {
        if( ( *max_at_turn < *min_at_turn ) ||
            ( ( *min_at_turn > ( idx_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN ) ||
              ( *min_at_turn < ( idx_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN ) ||
              ( *max_at_turn > ( idx_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN ) ||
              ( *max_at_turn < ( idx_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN ) ) )
        {
            *min_at_turn = ( idx_type )SIXTRL_PARTICLE_ILLEGAL_AT_TURN;
            *max_at_turn = ( idx_type )SIXTRL_PARTICLE_ILLEGAL_AT_TURN;
        }
    }
}

SIXTRL_INLINE void NS(Particles_merge_min_max_attributes_from_find)(
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_at_turn,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_at_turn,
    NS(particle_index_type) const found_min_id,
    NS(particle_index_type) const found_max_id,
    NS(particle_index_type) const found_min_at_element,
    NS(particle_index_type) const found_max_at_element,
    NS(particle_index_type) const found_min_at_turn,
    NS(particle_index_type) const found_max_at_turn ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_index_type) index_type;

    if( (  ptr_min_id   != SIXTRL_NULLPTR ) &&
        (  found_min_id != ( index_type )SIXTRL_PARTICLE_ILLEGAL_ID ) &&
        ( *ptr_min_id   != ( index_type )SIXTRL_PARTICLE_ILLEGAL_ID ) &&
        ( *ptr_min_id   > found_min_id ) )
    {
        *ptr_min_id = found_min_id;
    }

    if( (  ptr_max_id   != SIXTRL_NULLPTR ) &&
        (  found_max_id != ( index_type )SIXTRL_PARTICLE_ILLEGAL_ID ) &&
        ( *ptr_max_id   != ( index_type )SIXTRL_PARTICLE_ILLEGAL_ID ) &&
        ( *ptr_max_id   < found_max_id ) )
    {
        *ptr_max_id = found_max_id;
    }

    if( (  ptr_min_at_element   != SIXTRL_NULLPTR ) &&
        (  found_min_at_element !=
            (index_type)SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT ) &&
        ( *ptr_min_at_element   !=
            (index_type)SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT ) &&
        ( *ptr_min_at_element  > found_min_at_element ) )
    {
        *ptr_min_at_element = found_min_at_element;
    }

    if( (  ptr_max_at_element   != SIXTRL_NULLPTR ) &&
        (  found_max_at_element !=
            (index_type)SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT ) &&
        ( *ptr_max_at_element !=
            (index_type)SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT ) &&
        ( *ptr_max_at_element < found_max_at_element ) )
    {
        *ptr_max_at_element = found_max_at_element;
    }

    if( (  ptr_min_at_turn   != SIXTRL_NULLPTR ) &&
        (  found_min_at_turn != (index_type)SIXTRL_PARTICLE_ILLEGAL_AT_TURN ) &&
        ( *ptr_min_at_turn   != (index_type)SIXTRL_PARTICLE_ILLEGAL_AT_TURN ) &&
        ( *ptr_min_at_turn   >  found_min_at_turn ) )
    {
        *ptr_min_at_turn = found_min_at_turn;
    }

    if( (  ptr_max_at_turn   != SIXTRL_NULLPTR ) &&
        (  found_max_at_turn != (index_type)SIXTRL_PARTICLE_ILLEGAL_AT_TURN ) &&
        ( *ptr_max_at_turn   != (index_type)SIXTRL_PARTICLE_ILLEGAL_AT_TURN ) &&
        ( *ptr_max_at_turn   <  found_max_at_turn ) )
    {
        *ptr_max_at_turn = found_max_at_turn;
    }
}

SIXTRL_INLINE void NS(Particles_find_min_max_attributes)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)*
        SIXTRL_RESTRICT ptr_min_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)*
        SIXTRL_RESTRICT ptr_max_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)*
        SIXTRL_RESTRICT ptr_min_at_turn,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)*
        SIXTRL_RESTRICT ptr_max_at_turn ) SIXTRL_NOEXCEPT {
    typedef NS(particle_index_type) index_type;

    SIXTRL_ARGPTR_DEC index_type min_id          = ( index_type )0;
    SIXTRL_ARGPTR_DEC index_type max_id          = ( index_type )0;
    SIXTRL_ARGPTR_DEC index_type min_at_element  = ( index_type )0;
    SIXTRL_ARGPTR_DEC index_type max_at_element  = ( index_type )0;
    SIXTRL_ARGPTR_DEC index_type min_at_turn     = ( index_type )0;
    SIXTRL_ARGPTR_DEC index_type max_at_turn     = ( index_type )0;

    NS(particles_num_type) const npart = NS(Particles_num_particles)( pset );

    SIXTRL_PARTICLES_DATAPTR_DEC index_type const* ptr_ids =
        NS(Particles_id_const_begin)( pset );

    SIXTRL_PARTICLES_DATAPTR_DEC index_type const* ptr_at_elements =
        NS(Particles_at_element_const_begin)( pset );

    SIXTRL_PARTICLES_DATAPTR_DEC index_type const* ptr_at_turns =
        NS(Particles_at_turn_const_begin)( pset );

    if( ( ptr_ids != SIXTRL_NULLPTR ) &&
        ( ptr_at_elements != SIXTRL_NULLPTR ) &&
        ( ptr_at_turns != SIXTRL_NULLPTR ) &&
        ( npart > ( NS(particles_num_type) )0 ) )
    {
        NS(particles_num_type) ii = 0;
        NS(Particles_init_min_max_attributes_for_find)( &min_id, &max_id,
            &min_at_element, &max_at_element, &min_at_turn, &max_at_turn );

        SIXTRL_ASSERT( max_id < min_id );
        SIXTRL_ASSERT( max_at_element < min_at_element );
        SIXTRL_ASSERT( max_at_turn < min_at_turn );

        for( ; ii < npart ; ++ii )
        {
            index_type temp = ptr_ids[ ii ];

            if( ( temp >= ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_ID ) &&
                ( temp <= ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_ID ) )
            {
                SIXTRL_ASSERT( temp != (
                    index_type )SIXTRL_PARTICLE_ILLEGAL_ID );
                if( min_id > temp ) min_id = temp;
                if( max_id < temp ) max_id = temp;
            }

            temp = ptr_at_elements[ ii ];

            if( ( temp >= ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) &&
                ( temp <= ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT ) )
            {
                SIXTRL_ASSERT( temp != (
                    index_type )SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT );
                if( min_at_element > temp ) min_at_element = temp;
                if( max_at_element < temp ) max_at_element = temp;
            }

            temp = ptr_at_turns[ ii ];

            if( ( temp >= ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN ) &&
                ( temp <= ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN ) )
            {
                SIXTRL_ASSERT( temp != (
                    index_type )SIXTRL_PARTICLE_ILLEGAL_AT_TURN );
                if( min_at_turn > temp ) min_at_turn = temp;
                if( max_at_turn < temp ) max_at_turn = temp;
            }
        }

        NS(Particles_min_max_attributes_sanity_check)( &min_id, &max_id,
            &min_at_element, &max_at_element, &min_at_turn, &max_at_turn );
    }

    NS(Particles_merge_min_max_attributes_from_find)( ptr_min_id, ptr_max_id,
        ptr_min_at_element, ptr_max_at_element, ptr_min_at_turn, ptr_max_at_turn,
        min_id, max_id, min_at_element, max_at_element, min_at_turn, max_at_turn );
}

SIXTRL_INLINE void
NS(Particles_cobj_flat_buffer_find_min_max_attributes_in_particle_sets)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size, NS(size_type) const  num_particle_sets,
    SIXTRL_ARGPTR_DEC NS(size_type) const* SIXTRL_RESTRICT indices_begin,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_at_element,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_at_turn,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_at_turn )
{
    typedef NS(particle_index_type) index_type;

    if( ( NS(CObjFlatBuffer_is_particle_set_buffer)( buffer, slot_size ) ) &&
        ( num_particle_sets > ( NS(size_type) )0u ) &&
        ( indices_begin != SIXTRL_NULLPTR ) )
    {
        SIXTRL_ARGPTR_DEC index_type min_id, max_id,
            min_at_element, max_at_element, min_at_turn, max_at_turn;

        NS(size_type) ii = 0;

        NS(Particles_init_min_max_attributes_for_find)( &min_id, &max_id,
            &min_at_element, &max_at_element, &min_at_turn, &max_at_turn );

        for( ; ii < num_particle_sets ; ++ii )
        {
            NS(size_type) const pset_idx = indices_begin[ ii ];
            SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* pset =
                NS(Particles_const_from_cobj_flat_buffer)(
                    buffer, pset_idx, slot_size );

            if( pset == SIXTRL_NULLPTR ) continue;

            NS(Particles_find_min_max_attributes)( pset, &min_id, &max_id,
                &min_at_element, &max_at_element, &min_at_turn, &max_at_turn );
        }

        NS(Particles_merge_min_max_attributes_from_find)( ptr_min_id, ptr_max_id,
            ptr_min_at_element, ptr_max_at_element, ptr_min_at_turn,
                ptr_max_at_turn, min_id, max_id, min_at_element, max_at_element,
                    min_at_turn, max_at_turn );
    }
}

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(status_type) NS(Particles_cobj_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT offsets,
    NS(size_type) const max_num_offsets,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(Particles_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;
    if( ( p != SIXTRL_NULLPTR ) && ( offsets != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_offsets >= ndataptrs ) &&
        ( ndataptrs == ( st_size_t )SIXTRL_PARTICLES_NUM_DATAPTRS ) ) {

        st_size_t const first_offset = ( st_size_t )2 *
            NS(CObjFlatBuffer_slot_based_size)( sizeof( NS(particles_num_type) ),
                slot_size );

        st_size_t const addr_field_extent = NS(CObjFlatBuffer_slot_based_size)(
            sizeof( NS(particles_addr_type) ), slot_size );

        for( ; ii < ndataptrs ; ++ii )
            offsets[ ii ] = first_offset + ii * addr_field_extent;

        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

    if( ( offsets != SIXTRL_NULLPTR ) &&
        ( max_num_offsets > ( st_size_t )0u ) && ( ii < max_num_offsets ) ) {
        while( ii < max_num_offsets ) { offsets[ ii++ ] = ( st_size_t )0u; } }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Particles_cobj_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT counts,
    NS(size_type) const max_num_counts,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(Particles_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;

    if( ( p != SIXTRL_NULLPTR ) && ( counts != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_counts >= ndataptrs ) )
    {
        NS(particles_num_type) const npart_i =
            NS(Particles_max_num_particles)( p );

        st_size_t const npart = ( npart_i >= 0 )
            ? ( st_size_t )npart_i : ( st_size_t )0u;

        if( ndataptrs == ( st_size_t )SIXTRL_PARTICLES_NUM_DATAPTRS ) {
            for( ; ii < ndataptrs ; ++ii ){ counts[ ii ] = npart; }
            status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    }

    if( ( counts != SIXTRL_NULLPTR ) && ( ii < max_num_counts ) &&
        ( max_num_counts > ( st_size_t )0u ) ) {
        while( ii < max_num_counts ){ counts[ ii++ ] = ( st_size_t )0; } }

    return status; }


SIXTRL_INLINE NS(status_type) NS(Particles_cobj_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT sizes,
    NS(size_type) const max_num_sizes,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(Particles_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;

    if( ( p != SIXTRL_NULLPTR ) && ( sizes != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_sizes >= ndataptrs ) ) {
        st_size_t const NPTRS_REAL = ( st_size_t
            )SIXTRL_PARTICLES_NUM_REAL_DATAPTRS;

        st_size_t const NPTRS_INDEX = (
            st_size_t )SIXTRL_PARTICLES_NUM_INDEX_DATAPTRS;

        if( ndataptrs == ( NPTRS_REAL + NPTRS_INDEX ) ) {
            st_size_t const real_size = sizeof( NS(particle_real_type) );
            st_size_t const index_size = sizeof( NS(particle_index_type) );
            st_size_t jj = ( st_size_t )0u;
            for( ; ii < NPTRS_REAL  ; ++ii ) { sizes[ ii ] = real_size; }
            for( ; jj < NPTRS_INDEX ; ++jj, ++ii ) { sizes[ ii ] = index_size; }
            status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    }

    if( ( sizes != SIXTRL_NULLPTR ) &&
        ( max_num_sizes >= ( st_size_t )0 ) && ( ii < max_num_sizes ) ) {
        for( ; ii < max_num_sizes ; ++ii ) { sizes[ ii ] = ( st_size_t )0u; } }

    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE bool NS(Particles_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT b,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_t;
    bool can_be_added = false;
    SIXTRL_CBUFFER_ARGPTR_DEC NS(Particles) pset;
    NS(Particles_clear)( &pset );
    NS(Particles_set_max_num_particles)( &pset, max_num_particles );
    NS(Particles_set_num_particles)( &pset, max_num_particles );

    if( ( max_num_particles >= ( NS(particles_num_type) )0u ) &&
        ( b != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_t )0u ) ) {
        SIXTRL_ARGPTR_DEC st_size_t SIZES[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
        SIXTRL_ARGPTR_DEC st_size_t COUNTS[ SIXTRL_PARTICLES_NUM_DATAPTRS ];

        NS(cobj_status_type) status = NS(Particles_cobj_attributes_sizes)(
            &SIZES[ 0 ], NS(Particles_cobj_num_dataptrs)(), &pset, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(Particles_cobj_attributes_counts)( &COUNTS[ 0 ],
                NS(Particles_cobj_num_dataptrs)(), &pset, slot_size );

        SIXTRL_ASSERT( NS(Particles_cobj_num_dataptrs)() ==
            ( st_size_t )SIXTRL_PARTICLES_NUM_DATAPTRS );

        can_be_added = NS(CObjFlatBuffer_can_add_copy_of_object)( b, slot_size,
            NS(Particles_cobj_reserved_handle_size)( slot_size ),
            NS(Particles_cobj_num_dataptrs)(), &SIZES[ 0 ], &COUNTS[ 0 ],
            requ_buffer_size, requ_slots, requ_objects, requ_dataptrs ); }

    return can_be_added; }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(Particles)*
NS(Particles_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles ) SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(Particles) pset;
    NS(Particles_clear)( &pset );
    NS(Particles_set_max_num_particles)( &pset, max_num_particles );
    NS(Particles_set_num_particles)( &pset, max_num_particles );
    return NS(Particles_cobj_flat_buffer_add_copy)( buffer, slot_size, &pset );
}

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(Particles)*
NS(Particles_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr ) SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(Particles) pset;
    NS(Particles_init_with_pointers)( &pset, max_num_particles, num_particles,
        charge0_ptr, mass0_ptr, beta0_ptr, gamma0_ptr, p0c_ptr, s_ptr, x_ptr,
            y_ptr, px_ptr, py_ptr, zeta_ptr, psigma_ptr, delta_ptr, rpp_ptr,
                rvv_ptr, chi_ptr, charge_ratio_ptr, id_ptr, at_element_ptr,
                    at_turn_ptr, state_ptr );
    return NS(Particles_cobj_flat_buffer_add_copy)( buffer, slot_size, &pset );
}

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(Particles)*
NS(Particles_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_t;
    SIXTRL_CBUFFER_ARGPTR_DEC NS(Particles)* ptr_added_elem = SIXTRL_NULLPTR;
    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_t )0u ) ) {
        SIXTRL_ARGPTR_DEC st_size_t OFFSETS[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
        SIXTRL_ARGPTR_DEC st_size_t SIZES[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
        SIXTRL_ARGPTR_DEC st_size_t COUNTS[ SIXTRL_PARTICLES_NUM_DATAPTRS ];

        NS(cobj_status_type) status = NS(Particles_cobj_attributes_offsets)(
            &OFFSETS[ 0 ], NS(Particles_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(Particles_cobj_attributes_sizes)( &SIZES[ 0 ],
                NS(Particles_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(Particles_cobj_attributes_counts)( &COUNTS[ 0 ],
                NS(Particles_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS ) {
            SIXTRL_ASSERT( NS(Particles_cobj_num_dataptrs)() ==
                ( st_size_t )SIXTRL_PARTICLES_NUM_DATAPTRS );

            ptr_added_elem = ( SIXTRL_CBUFFER_ARGPTR_DEC NS(Particles)* )(
                uintptr_t )NS(CObjIndex_begin_addr)(
                    NS(CObjFlatBuffer_add_copy_of_object)( buffer, slot_size,
                    orig, NS(Particles_cobj_reserved_handle_size)( slot_size ),
                    NS(Particles_cobj_type_id)(),
                    NS(Particles_cobj_num_dataptrs)(),
                    &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) ); }
    }
    return ptr_added_elem; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE bool NS(Particles_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT { return NS(Particles_cobj_flat_buffer_can_be_added)(
    NS(CBuffer_p_const_base)( buffer ), NS(CBuffer_slot_size)( buffer ),
        max_num_particles, requ_buffer_size, requ_slots, requ_objects,
            requ_dataptrs ); }

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles ) {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(Particles) pset;
    NS(Particles_clear)( &pset );
    NS(Particles_set_max_num_particles)( &pset, max_num_particles );
    NS(Particles_set_num_particles)( &pset, max_num_particles );
    return NS(Particles_cbuffer_add_copy)( buffer, &pset ); }

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr ) {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(Particles) pset;
    NS(Particles_init_with_pointers)( &pset, max_num_particles, num_particles,
        charge0_ptr, mass0_ptr, beta0_ptr, gamma0_ptr, p0c_ptr,
            s_ptr, x_ptr, y_ptr, px_ptr, py_ptr, zeta_ptr, psigma_ptr, delta_ptr,
                rpp_ptr, rvv_ptr, chi_ptr, charge_ratio_ptr, id_ptr,
                    at_element_ptr, at_turn_ptr, state_ptr );
    return NS(Particles_cbuffer_add_copy)( buffer, &pset ); }

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT orig )
{
    typedef NS(cobj_size_type) st_size_t;
    SIXTRL_CBUFFER_ARGPTR_DEC NS(Particles)* ptr_added_elem = SIXTRL_NULLPTR;

    if( buffer != SIXTRL_NULLPTR ) {
        st_size_t const slot_size = NS(CBuffer_slot_size)( buffer );
        SIXTRL_ARGPTR_DEC st_size_t OFFSETS[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
        SIXTRL_ARGPTR_DEC st_size_t SIZES[ SIXTRL_PARTICLES_NUM_DATAPTRS ];
        SIXTRL_ARGPTR_DEC st_size_t COUNTS[ SIXTRL_PARTICLES_NUM_DATAPTRS ];

        NS(cobj_status_type) status = NS(Particles_cobj_attributes_offsets)(
            &OFFSETS[ 0 ], NS(Particles_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(Particles_cobj_attributes_sizes)( &SIZES[ 0 ],
                NS(Particles_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(Particles_cobj_attributes_counts)( &COUNTS[ 0 ],
                NS(Particles_cobj_num_dataptrs)(), orig, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS ) {
            SIXTRL_ASSERT( NS(Particles_cobj_num_dataptrs)() == (
                st_size_t )SIXTRL_PARTICLES_NUM_DATAPTRS );
            ptr_added_elem = ( SIXTRL_CBUFFER_ARGPTR_DEC NS(Particles)* )(
                uintptr_t )NS(CObjIndex_begin_addr)(
                NS(CBuffer_add_copy_of_object)( buffer, orig,
                    NS(Particles_cobj_reserved_handle_size)( slot_size ),
                    NS(Particles_cobj_type_id)(),
                    NS(Particles_cobj_num_dataptrs)(),
                    &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) ); }
    }
    return ptr_added_elem; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(status_type) NS(Particles_copy_single)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT dst,
    NS(particles_num_type) const dst_idx,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT src,
    NS(particles_num_type) const src_idx ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = NS(STATUS_GENERAL_FAILURE);
    if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
        ( NS(Particles_num_particles)( dst ) > dst_idx ) &&
        ( NS(Particles_num_particles)( src ) > src_idx ) )
    {
        NS(Particles_set_charge0)( dst, dst_idx,
            NS(Particles_charge0)( src, src_idx ) );

        NS(Particles_set_mass0)( dst, dst_idx,
            NS(Particles_mass0)( src, src_idx ) );

        NS(Particles_set_beta0)( dst, dst_idx,
            NS(Particles_beta0)( src, src_idx ) );

        NS(Particles_set_gamma0)( dst, dst_idx,
            NS(Particles_gamma0)( src, src_idx ) );

        NS(Particles_set_p0c)( dst, dst_idx,
            NS(Particles_p0c)( src, src_idx ) );

        NS(Particles_set_s)(  dst, dst_idx, NS(Particles_s)(  src, src_idx ) );
        NS(Particles_set_x)(  dst, dst_idx, NS(Particles_x)(  src, src_idx ) );
        NS(Particles_set_y)(  dst, dst_idx, NS(Particles_y)(  src, src_idx ) );
        NS(Particles_set_px)( dst, dst_idx, NS(Particles_px)( src, src_idx ) );
        NS(Particles_set_py)( dst, dst_idx, NS(Particles_py)( src, src_idx ) );

        NS(Particles_set_zeta)( dst, dst_idx,
            NS(Particles_zeta)( src, src_idx ) );

        NS(Particles_set_delta)( dst, dst_idx,
            NS(Particles_delta)( src, src_idx ) );

        NS(Particles_set_psigma)( dst, dst_idx,
            NS(Particles_psigma)( src, src_idx ) );

        NS(Particles_set_rpp)( dst, dst_idx,
            NS(Particles_rpp)( src, src_idx ) );

        NS(Particles_set_rvv)( dst, dst_idx,
            NS(Particles_rvv)( src, src_idx ) );

        NS(Particles_set_chi)( dst, dst_idx,
            NS(Particles_chi)( src, src_idx ) );

        NS(Particles_set_charge_ratio)( dst, dst_idx,
            NS(Particles_charge_ratio)( src, src_idx ) );

        NS(Particles_set_id)( dst, dst_idx, NS(Particles_id)( src, src_idx ) );
        NS(Particles_set_at_element)( dst, dst_idx,
            NS(Particles_at_element)( src, src_idx ) );

        NS(Particles_set_at_turn)( dst, dst_idx,
            NS(Particles_at_turn)( src, src_idx ) );

        NS(Particles_set_state)( dst, dst_idx,
            NS(Particles_state)( src, src_idx ) );

        status = NS(STATUS_SUCCESS);
    }

    return status;
}

SIXTRL_INLINE NS(status_type) NS(Particles_copy_range)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT dest,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT src,
    NS(particles_num_type) const src_idx_begin,
    NS(particles_num_type) const src_idx_end,
    NS(particles_num_type) const dst_idx_begin,
    NS(particles_num_type) stride ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = NS(STATUS_GENERAL_FAILURE);
    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) &&
        ( src_idx_begin <= src_idx_end ) &&
        ( NS(Particles_num_particles)( src ) >= src_idx_end ) &&
        ( NS(Particles_num_particles)( dest ) >= ( dst_idx_begin + (
            ( src_idx_end - src_idx_begin ) ) ) ) )
    {
        if( stride <= 0 ) stride = 1;

        NS(Particles_copy_real_field_impl)( NS(Particles_charge0_begin)( dest ),
            NS(Particles_charge0_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_mass0_begin)( dest ),
            NS(Particles_mass0_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_beta0_begin)( dest ),
            NS(Particles_beta0_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_gamma0_begin)( dest ),
            NS(Particles_gamma0_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_p0c_begin)( dest ),
            NS(Particles_p0c_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_s_begin)( dest ),
            NS(Particles_s_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_x_begin)( dest ),
            NS(Particles_x_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_y_begin)( dest ),
            NS(Particles_y_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_px_begin)( dest ),
            NS(Particles_px_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_py_begin)( dest ),
            NS(Particles_py_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_zeta_begin)( dest ),
            NS(Particles_zeta_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_psigma_begin)( dest ),
            NS(Particles_psigma_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_delta_begin)( dest ),
            NS(Particles_delta_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_rpp_begin)( dest ),
            NS(Particles_rpp_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_rvv_begin)( dest ),
            NS(Particles_rvv_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)( NS(Particles_chi_begin)( dest ),
            NS(Particles_chi_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_real_field_impl)(
            NS(Particles_charge_ratio_begin)( dest ),
                NS(Particles_charge_ratio_const_begin)( src ),
                    src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_index_field_impl)( NS(Particles_id_begin)( dest ),
            NS(Particles_id_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_index_field_impl)(
            NS(Particles_at_element_begin)( dest ),
                NS(Particles_at_element_const_begin)( src ),
                    src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_index_field_impl)( NS(Particles_at_turn_begin)( dest ),
            NS(Particles_at_turn_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        NS(Particles_copy_index_field_impl)( NS(Particles_state_begin)( dest ),
            NS(Particles_state_const_begin)( src ),
                src_idx_begin, src_idx_end, dst_idx_begin, stride );

        status = NS(STATUS_SUCCESS);
    }

    return status; }

SIXTRL_INLINE NS(status_type) NS(Particles_copy)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT source ) SIXTRL_NOEXCEPT {
    return NS(Particles_copy_range)( destination, source, 0,
        NS(Particles_num_particles)( source ), 0, 1 ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

#if defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) && \
           ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER == 1 )

SIXTRL_INLINE NS(status_type) NS(Particles_to_single_particle)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    NS(particles_num_type) const index,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(SingleParticleView)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT
{
    NS(status_type) status = NS(STATUS_GENERAL_FAILURE);
    if( ( pset != SIXTRL_NULLPTR ) && ( p != SIXTRL_NULLPTR ) &&
        ( NS(Particles_num_particles)( pset ) > index ) )
    {
        SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* dest =
            NS(SingleParticleView_particles)( p );

        if( ( dest == SIXTRL_NULLPTR ) &&
            ( p->index == ( NS(particle_index_type) )0u ) )
        {
            status = NS(SingleParticleView_init_from_pset)( p, pset, index );
        }
        else if( ( dest == pset ) && ( p->index == index ) )
        {
            status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        }
        else
        {
            SIXTRL_ASSERT( dest != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( ( dest != pset ) || ( p->index != index ) );
            status = NS(Particles_copy_single)( dest, p->index, pset, index );
        }
    }
    return status;
}

SIXTRL_INLINE NS(status_type) NS(Particles_from_single_particle)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT pset,
    NS(particles_num_type) const index,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(SingleParticleView) *const
        SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = NS(STATUS_GENERAL_FAILURE);
    if( ( pset != SIXTRL_NULLPTR ) && ( p != SIXTRL_NULLPTR ) &&
        ( NS(Particles_num_particles)( pset ) > index ) )
    {
        SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* src =
            NS(SingleParticleView_const_particles)( p );

        if( ( src != SIXTRL_NULLPTR ) &&
            ( NS(Particles_num_particles)( src ) > p->index ) )
        {
            if( ( src == pset ) && ( p->index == index ) )
            {
                status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
            }
            else
            {
                status = NS(Particles_copy_single)( pset, index, src, p->index );
            }
        }
    }

    return status;
}

#else /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

SIXTRL_INLINE NS(status_type) NS(Particles_to_single_particle)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    NS(particles_num_type) const idx,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(SingleParticle)* SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT
{
    NS(status_type) status = NS(STATUS_GENERAL_FAILURE);
    if( ( pset != SIXTRL_NULLPTR ) && ( p != SIXTRL_NULLPTR ) &&
        ( NS(Particles_num_particles)( pset ) > idx ) )
    {
        NS(Particle_set_x)(       p, NS(Particles_x)(       pset, idx ) );
        NS(Particle_set_y)(       p, NS(Particles_y)(       pset, idx ) );
        NS(Particle_set_px)(      p, NS(Particles_px)(      pset, idx ) );
        NS(Particle_set_py)(      p, NS(Particles_py)(      pset, idx ) );
        NS(Particle_set_zeta)(    p, NS(Particles_zeta)(    pset, idx ) );
        NS(Particle_set_delta)(   p, NS(Particles_delta)(   pset, idx ) );


        NS(Particle_set_state)(      p, NS(Particles_state)(      pset, idx ) );
        NS(Particle_set_at_element)( p, NS(Particles_at_element)( pset, idx ) );
        NS(Particle_set_at_turn)(    p, NS(Particles_at_turn)(    pset, idx ) );
        NS(Particle_set_id)(         p, NS(Particles_id)(         pset, idx ) );

        #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD == 1 )
        NS(Particle_set_psigma)(  p, NS(Particles_psigma)(  pset, idx ) );
        #endif /* defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */

        NS(Particle_set_rpp)(     p, NS(Particles_rpp)(     pset, idx ) );
        NS(Particle_set_rvv)(     p, NS(Particles_rvv)(     pset, idx ) );
        NS(Particle_set_chi)(     p, NS(Particles_chi)(     pset, idx ) );

        NS(Particle_set_charge_ratio)( p,
            NS(Particles_charge_ratio)( pset, idx ) );

        NS(Particle_set_charge0)( p, NS(Particles_charge0)( pset, idx ) );
        NS(Particle_set_mass0)(   p, NS(Particles_mass0)(   pset, idx ) );
        NS(Particle_set_beta0)(   p, NS(Particles_beta0)(   pset, idx ) );
        NS(Particle_set_gamma0)(  p, NS(Particles_gamma0)(  pset, idx ) );
        NS(Particle_set_p0c)(     p, NS(Particles_p0c)(     pset, idx ) );

        #if defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
        NS(Particle_set_s)( p, NS(Particles_s)( pset, idx ) );
        #endif /* SIXTRL_PARTICLE_USE_S_FIELD */

        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(status_type) NS(Particles_from_single_particle)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT pset,
    NS(particles_num_type) const idx,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(SingleParticle) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT
{
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( p != SIXTRL_NULLPTR ) && ( pset != SIXTRL_NULLPTR ) &&
        ( NS(Particles_num_particles)( pset ) > idx ) )
    {
        NS(Particles_set_x)(          pset, idx, NS(Particle_x)(          p ) );
        NS(Particles_set_y)(          pset, idx, NS(Particle_y)(          p ) );
        NS(Particles_set_px)(         pset, idx, NS(Particle_px)(         p ) );
        NS(Particles_set_py)(         pset, idx, NS(Particle_py)(         p ) );
        NS(Particles_set_zeta)(       pset, idx, NS(Particle_zeta)(       p ) );
        NS(Particles_set_delta)(      pset, idx, NS(Particle_delta)(      p ) );

        NS(Particles_set_state)(      pset, idx, NS(Particle_state)(      p ) );
        NS(Particles_set_at_element)( pset, idx, NS(Particle_at_element)( p ) );
        NS(Particles_set_at_turn)(    pset, idx, NS(Particle_at_turn)(    p ) );
        NS(Particles_set_id)(         pset, idx, NS(Particle_id)(         p ) );

        #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD == 1 )
        NS(Particles_set_psigma)( pset, idx, NS(Particle_psigma)( p ) );
        #endif /* defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) */

        NS(Particles_set_rpp)(        pset, idx, NS(Particle_rpp)(        p ) );
        NS(Particles_set_rvv)(        pset, idx, NS(Particle_rvv)(        p ) );
        NS(Particles_set_chi)(        pset, idx, NS(Particle_chi)(        p ) );

        NS(Particles_set_charge_ratio)( pset, idx,
            NS(Particle_charge_ratio)( p ) );

        NS(Particles_set_charge0)(    pset, idx, NS(Particle_charge0)(    p ) );
        NS(Particles_set_mass0)(      pset, idx, NS(Particle_mass0)(      p ) );
        NS(Particles_set_beta0)(      pset, idx, NS(Particle_beta0)(      p ) );
        NS(Particles_set_gamma0)(     pset, idx, NS(Particle_gamma0)(     p ) );
        NS(Particles_set_p0c)(        pset, idx, NS(Particle_p0c)(        p ) );

        #if defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
                   ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )
        NS(Particles_set_s)( pset, idx, NS(Particle_s)( p ) );
        #endif /* SIXTRL_PARTICLE_USE_S_FIELD */

        status = NS(STATUS_SUCCESS);
    }

    return status;
}

#endif /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const*
NS(Particles_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const
    NS(CObjIndex) *const SIXTRL_RESTRICT obj_index ) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_particles)( obj_index ) )
        ? ( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj_index )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)*
    SIXTRL_RESTRICT obj_index ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_PARTICLES_ARGPTR_DEC  NS(Particles)*
        )NS(Particles_const_from_cobj_index)( obj_index ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const*
NS(Particles_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const index, NS(size_type) const slot_size
) SIXTRL_NOEXCEPT { return NS(Particles_const_from_cobj_index)(
    NS(CObjFlatBuffer_const_index)( buffer, index, slot_size ) ); }

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const index, NS(size_type) const slot_size
) SIXTRL_NOEXCEPT { return NS(Particles_from_cobj_index)(
    NS(CObjFlatBuffer_index)( buffer, index, slot_size ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const*
NS(Particles_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Particles_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( b, idx ) ); }

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Particles_from_cobj_index)( NS(CBuffer_index_at)( b, idx ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE void NS(Particles_difference_max_value)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLES_ARGPTR_DEC NS(particles_num_type)*
        SIXTRL_RESTRICT max_value_index,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    if( ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) &&
        ( NS(Particles_num_particles)( dst ) > ( NS(particles_num_type) )0 ) &&
        ( NS(Particles_num_particles)( src ) > ( NS(particles_num_type) )0 ) )
    {
        NS(size_type) dummy_max_value_indices[
            SIXTRL_PARTICLES_NUM_DATAPTRS ] = {
            ( NS(particles_num_type) )0, ( NS(particles_num_type) )0,
            ( NS(particles_num_type) )0, ( NS(particles_num_type) )0,
            ( NS(particles_num_type) )0, ( NS(particles_num_type) )0,
            ( NS(particles_num_type) )0, ( NS(particles_num_type) )0,
            ( NS(particles_num_type) )0, ( NS(particles_num_type) )0,
            ( NS(particles_num_type) )0, ( NS(particles_num_type) )0,
            ( NS(particles_num_type) )0, ( NS(particles_num_type) )0,
            ( NS(particles_num_type) )0, ( NS(particles_num_type) )0,
            ( NS(particles_num_type) )0, ( NS(particles_num_type) )0,
            ( NS(particles_num_type) )0, ( NS(particles_num_type) )0,
            ( NS(particles_num_type) )0 };

        NS(particles_real_pointer) out_real_values_begin[
            SIXTRL_PARTICLES_NUM_REAL_DATAPTRS ] = {
            NS(Particles_charge0_begin)( dst ),
            NS(Particles_mass0_begin)( dst ), NS(Particles_beta0_begin)( dst ),
            NS(Particles_gamma0_begin)( dst ), NS(Particles_p0c_begin)( dst ),
            NS(Particles_s_begin)( dst ),
            NS(Particles_x_begin)( dst ), NS(Particles_y_begin)( dst ),
            NS(Particles_px_begin)( dst ), NS(Particles_py_begin)( dst ),
            NS(Particles_zeta_begin)( dst ), NS(Particles_psigma_begin)( dst ),
            NS(Particles_delta_begin)( dst ),
            NS(Particles_rpp_begin)( dst ), NS(Particles_rvv_begin)( dst ),
            NS(Particles_chi_begin)( dst ),
            NS(Particles_charge_ratio_begin)( dst ) };

        NS(particles_index_pointer) out_index_values_begin[
            SIXTRL_PARTICLES_NUM_INDEX_DATAPTRS ] = {
            NS(Particles_id_begin)( dst ),
            NS(Particles_at_element_begin)( dst ),
            NS(Particles_at_turn_begin)( dst ),
            NS(Particles_state_begin)( dst ) };

        NS(particles_real_const_pointer) in_real_values_begin[
            SIXTRL_PARTICLES_NUM_REAL_DATAPTRS ] = {
            NS(Particles_charge0_const_begin)( src ),
            NS(Particles_mass0_const_begin)( src ),
            NS(Particles_beta0_const_begin)( src ),
            NS(Particles_gamma0_const_begin)( src ),
            NS(Particles_p0c_const_begin)( src ),
            NS(Particles_s_const_begin)( src ),
            NS(Particles_x_const_begin)( src ),
            NS(Particles_y_const_begin)( src ),
            NS(Particles_px_const_begin)( src ),
            NS(Particles_py_const_begin)( src ),
            NS(Particles_zeta_const_begin)( src ),
            NS(Particles_psigma_const_begin)( src ),
            NS(Particles_delta_const_begin)( src ),
            NS(Particles_rpp_const_begin)( src ),
            NS(Particles_rvv_const_begin)( src ),
            NS(Particles_chi_const_begin)( src ),
            NS(Particles_charge_ratio_const_begin)( src ) };

        NS(particles_real_const_pointer) in_real_values_end[
            SIXTRL_PARTICLES_NUM_REAL_DATAPTRS ] = {
            NS(Particles_charge0_const_end)( src ),
            NS(Particles_mass0_const_end)( src ),
            NS(Particles_beta0_const_end)( src ),
            NS(Particles_gamma0_const_end)( src ),
            NS(Particles_p0c_const_end)( src ),
            NS(Particles_s_const_end)( src ),
            NS(Particles_x_const_end)( src ),
            NS(Particles_y_const_end)( src ),
            NS(Particles_px_const_end)( src ),
            NS(Particles_py_const_end)( src ),
            NS(Particles_zeta_const_end)( src ),
            NS(Particles_psigma_const_end)( src ),
            NS(Particles_delta_const_end)( src ),
            NS(Particles_rpp_const_end)( src ),
            NS(Particles_rvv_const_end)( src ),
            NS(Particles_chi_const_end)( src ),
            NS(Particles_charge_ratio_const_end)( src ) };

        NS(particles_index_const_pointer) in_index_values_begin[
            SIXTRL_PARTICLES_NUM_INDEX_DATAPTRS ] = {
            NS(Particles_id_const_begin)( src ),
            NS(Particles_at_element_const_begin)( src ),
            NS(Particles_at_turn_const_begin)( src ),
            NS(Particles_state_const_begin)( src ) };

        NS(particles_index_const_pointer) in_index_values_end[
            SIXTRL_PARTICLES_NUM_INDEX_DATAPTRS ] = {
            NS(Particles_id_const_end)( src ),
            NS(Particles_at_element_const_end)( src ),
            NS(Particles_at_turn_const_end)( src ),
            NS(Particles_state_const_end)( src ) };

        NS(size_type) ii = ( NS(size_type) )0u;
        NS(size_type) const NUM_REAL_DATAPTRS = (
            NS(size_type) )SIXTRL_PARTICLES_NUM_REAL_DATAPTRS;

        NS(size_type) jj = ( NS(size_type) )0u;
        NS(size_type) const NUM_INDEX_DATAPTRS = (
            NS(size_type) )SIXTRL_PARTICLES_NUM_INDEX_DATAPTRS;

        for( ; ii < NUM_REAL_DATAPTRS ; ++ii )
        {
            NS(particles_real_const_pointer) in_it  = in_real_values_begin[ ii ];
            NS(particles_real_const_pointer) in_end = in_real_values_end[ ii ];

            NS(particle_real_type) max_value     = ( NS(particle_real_type) )0.0;
            NS(particle_real_type) cmp_max_value = max_value;

            NS(size_type) kk = ( NS(size_type) )0;
            dummy_max_value_indices[ ii ] = ( NS(size_type) )0;

            for( ; in_it != in_end ; ++in_it, ++kk )
            {
                NS(particle_real_type) const value = *in_it;
                NS(particle_real_type) const cmp_value = NS(abs)( value );

                if( cmp_max_value < cmp_value )
                {
                    max_value = value;
                    cmp_max_value = cmp_value;
                    dummy_max_value_indices[ ii ] = kk;
                }
            }

            *out_real_values_begin[ ii ] = max_value;
        }

        ii = ( NS(size_type) )0u;
        jj = NUM_REAL_DATAPTRS;

        for( ; ii < NUM_INDEX_DATAPTRS ; ++ii, ++jj )
        {
            NS(particles_index_const_pointer) in_it  = in_index_values_begin[ ii ];
            NS(particles_index_const_pointer) in_end = in_index_values_end[ ii ];

            NS(particle_index_type) max_value = ( NS(particle_index_type) )0u;
            NS(particle_index_type) cmp_max_value = max_value;

            NS(size_type) kk = ( NS(size_type) )0u;
            dummy_max_value_indices[ jj ] = ( NS(size_type) )0u;

            for( ; in_it != in_end ; ++in_it, ++kk )
            {
                NS(particle_index_type) const value = *in_it;
                NS(particle_index_type) const cmp_value =
                    ( value > ( NS(particle_index_type) )0 ) ? value : -value;

                if( cmp_max_value < cmp_value )
                {
                    cmp_max_value = cmp_value;
                    max_value     = value;
                    dummy_max_value_indices[ jj ] = kk;
                }
            }

            *out_index_values_begin[ ii ] = max_value;
        }

        if( max_value_index != 0 )
        {
            SIXTRL_STATIC_VAR NS(size_type) const NUM_DATAPTRS = (
                NS(size_type) )SIXTRL_PARTICLES_NUM_DATAPTRS;

            ii = ( NS(size_type) )0u;
            for( ; ii < NUM_DATAPTRS ; ++ii ) {
                max_value_index[ ii ] = dummy_max_value_indices[ ii ];
            }

            max_value_index = max_value_index + 21;
        }
    }
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_H__ */
