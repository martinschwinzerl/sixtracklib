#ifndef SIXTRACKL_COMMON_BE_MONITOR_BE_MONITOR_C99_HEADER_H__
#define SIXTRACKL_COMMON_BE_MONITOR_BE_MONITOR_C99_HEADER_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);
struct NS(Particles);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(Monitor)
{
    NS(particle_index_type) num_stores      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_index_type) start           SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_index_type) skip            SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_index_type) min_particle_id SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_index_type) max_particle_id SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_flags_type)       is_rolling      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_flags_type)       is_turn_ordered SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_addr_type)        out_addr        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(Monitor);

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Monitor_num_stores)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type)
NS(Monitor_default_num_stores)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_set_num_stores)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    NS(particle_index_type) const num_stores ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Monitor_start)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type)
NS(Monitor_default_start)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_set_start)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    NS(particle_index_type) const start ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Monitor_skip)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type)
NS(Monitor_default_skip)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_set_skip)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    NS(particle_index_type) const skip ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Monitor_min_particle_id)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type)
NS(Monitor_default_min_particle_id)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_set_min_particle_id)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    NS(particle_index_type) const min_particle_id ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type) NS(Monitor_max_particle_id)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type)
NS(Monitor_default_max_particle_id)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_set_max_particle_id)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    NS(particle_index_type) const max_particle_id ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_is_rolling)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_default_is_rolling)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_set_is_rolling)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    bool const is_rolling ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_is_turn_ordered)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_default_is_turn_ordered)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_set_is_turn_ordered)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    bool const is_turn_ordered ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_is_particle_ordered)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_set_is_particle_ordered)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    bool const is_particle_ordered ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_addr_type) NS(Monitor_out_addr)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_addr_type) NS(Monitor_default_out_addr)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_set_out_addr)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    bool const out_addr ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(Monitor_out_addr_offset)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(Monitor_out_addr_size)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC struct NS(Particles) const*
NS(Monitor_const_output_particles)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLES_ARGPTR_DEC struct NS(Particles)*
NS(Monitor_output_particles)( SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const
    SIXTRL_RESTRICT mon ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(Monitor_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(Monitor_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(Monitor_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(Monitor_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(Monitor_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT be_mon,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Monitor)*
NS(Monitor_preset)( SIXTRL_BE_ARGPTR_DEC NS(Monitor)*
    SIXTRL_RESTRICT be_mon ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT be_mon
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_init)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT be_mon,
    NS(particle_index_type) const num_stores,
    NS(particle_index_type) const start,
    NS(particle_index_type) const skip,
    NS(particle_index_type) const min_particle_id,
    NS(particle_index_type) const max_particle_id,
    bool const is_rolling, bool const is_turn_ordered,
    NS(be_addr_type) const out_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT source
) SIXTRL_NOEXCEPT;


/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_monitor)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor) const*
NS(Monitor_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor) const*
NS(Monitor_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor) const*
NS(Monitor_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_any_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type)
NS(Monitor_num_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type)
NS(Monitor_indices_in_cobj_index_range)(
    SIXTRL_ARGPTR_DEC NS(be_size_type)* SIXTRL_RESTRICT indices_begin,
    NS(be_size_type) const max_num_indices_begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end,
    NS(be_size_type) const start_index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_any_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type)
NS(Monitor_num_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type)
NS(Monitor_indices_in_cobj_flat_buffer)(
    SIXTRL_ARGPTR_DEC NS(be_size_type)* SIXTRL_RESTRICT indices_begin,
    NS(be_size_type) const max_num_indices_begin,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(be_size_type) const start_index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_any_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(Monitor_num_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(Monitor_indices_in_cbuffer)(
    SIXTRL_ARGPTR_DEC NS(be_size_type)* SIXTRL_RESTRICT indices_begin,
    NS(be_size_type) const max_num_indices_begin,
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(be_size_type) const start_index ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_is_active_for_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT be_mon,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particles_num_type)
NS(Monitor_output_particles_index)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT be_mon,
    NS(particle_index_type) const particle_id,
    NS(particle_index_type) const at_turn );

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_any_active_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type)
NS(Monitor_num_active_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type)
NS(Monitor_active_indices_in_cobj_index_range)(
    SIXTRL_ARGPTR_DEC NS(be_size_type)* SIXTRL_RESTRICT indices_begin,
    NS(be_size_type) const max_num_indices_begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id,
    NS(be_size_type) const start_index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_any_active_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type)
NS(Monitor_num_active_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type)
NS(Monitor_active_indices_in_cobj_flat_buffer)(
    SIXTRL_ARGPTR_DEC NS(be_size_type)* SIXTRL_RESTRICT indices_begin,
    NS(be_size_type) const max_num_indices_begin,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id,
    NS(be_size_type) const start_index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(Monitor_any_active_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(Monitor_num_active_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type)
NS(Monitor_active_indices_in_cbuffer)(
    SIXTRL_ARGPTR_DEC NS(be_size_type)* SIXTRL_RESTRICT indices_begin,
    NS(be_size_type) const max_num_indices_begin,
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id,
    NS(be_size_type) const start_index ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_reset)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Monitor_reset_all_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)* SIXTRL_RESTRICT begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Monitor_reset_all_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Monitor_reset_all_in_cbuffer)( SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)*
    SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor) const*
NS(Monitor_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(Monitor_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Monitor_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Monitor_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Monitor_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(Monitor_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT be_mon,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Monitor)*
NS(Monitor_preset_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT be_mon
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(Monitor_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT be_mon
) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */
#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsStoreResultTypeTraits< ::NS(Monitor) >
    {
        typedef ::NS(Monitor) value_type;
        typedef SIXTRL_BE_ARGPTR_DEC value_type const* const_pointer;
        typedef SIXTRL_BE_ARGPTR_DEC value_type* pointer;
    };

    template<> struct CObjectsTraits< ::NS(Monitor) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_MONITOR;
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_MONITOR > {
            typedef ::NS(Monitor) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* ************************************************************************* */
/* *****          Implementation of C inline functions                   *** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/particles/particles.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE )
    #include "sixtracklib/common/beam_elements/monitor/monitor_cobj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(particle_index_type) NS(Monitor_num_stores)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mon != SIXTRL_NULLPTR ); return mon->num_stores; }

SIXTRL_INLINE NS(particle_index_type) NS(Monitor_default_num_stores)(
    ) SIXTRL_NOEXCEPT { return ( NS(particle_index_type) )0u; }

SIXTRL_INLINE NS(status_type) NS(Monitor_set_num_stores)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    NS(particle_index_type) const num_stores ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( num_stores >= ( NS(particle_index_type) )0u ) &&
        ( mon != SIXTRL_NULLPTR ) ) {
        mon->num_stores = num_stores;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(particle_index_type) NS(Monitor_start)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( mon != SIXTRL_NULLPTR ); return mon->start; }

SIXTRL_INLINE NS(particle_index_type) NS(Monitor_default_start)(
    ) SIXTRL_NOEXCEPT { return ( NS(particle_index_type) )0u; }

SIXTRL_INLINE NS(status_type) NS(Monitor_set_start)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    NS(particle_index_type) const start ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( start >= ( NS(particle_index_type) )0u ) && ( mon != SIXTRL_NULLPTR ) ) {
        mon->start = start;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(particle_index_type) NS(Monitor_skip)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( mon != SIXTRL_NULLPTR ); return mon->skip; }

SIXTRL_INLINE NS(particle_index_type) NS(Monitor_default_skip)(
) SIXTRL_NOEXCEPT { return ( NS(particle_index_type) )1u; }

SIXTRL_INLINE NS(status_type) NS(Monitor_set_skip)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    NS(particle_index_type) const skip ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( skip > ( NS(particle_index_type) )0u ) && ( mon != SIXTRL_NULLPTR ) ) {
        mon->skip = skip;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(particle_index_type) NS(Monitor_min_particle_id)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mon != SIXTRL_NULLPTR ); return mon->min_particle_id; }

SIXTRL_INLINE NS(particle_index_type) NS(Monitor_default_min_particle_id)(
) SIXTRL_NOEXCEPT { return ( NS(particle_index_type)
    )SIXTRL_PARTICLE_MIN_LEGAL_ID; }

SIXTRL_INLINE NS(status_type) NS(Monitor_set_min_particle_id)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    NS(particle_index_type) const min_particle_id ) SIXTRL_NOEXCEPT {
    typedef NS(particle_index_type) index_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( mon != SIXTRL_NULLPTR ) &&
        ( min_particle_id >= ( index_t )SIXTRL_PARTICLE_MIN_LEGAL_ID ) &&
        ( min_particle_id <= ( index_t )SIXTRL_PARTICLE_MAX_LEGAL_ID ) ) {
        mon->min_particle_id = min_particle_id;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(particle_index_type) NS(Monitor_max_particle_id)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mon != SIXTRL_NULLPTR ); return mon->max_particle_id; }

SIXTRL_INLINE NS(particle_index_type) NS(Monitor_default_max_particle_id)(
) SIXTRL_NOEXCEPT { return ( NS(particle_index_type)
    )SIXTRL_PARTICLE_MIN_LEGAL_ID; }

SIXTRL_INLINE NS(status_type) NS(Monitor_set_max_particle_id)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    NS(particle_index_type) const max_particle_id ) SIXTRL_NOEXCEPT {
    typedef NS(particle_index_type) index_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( mon != SIXTRL_NULLPTR ) &&
        ( max_particle_id >= ( index_t )SIXTRL_PARTICLE_MIN_LEGAL_ID ) &&
        ( max_particle_id <= ( index_t )SIXTRL_PARTICLE_MAX_LEGAL_ID ) ) {
        mon->max_particle_id = max_particle_id;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Monitor_is_rolling)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mon != SIXTRL_NULLPTR );
    return ( mon->is_rolling == ( NS(be_flags_type) )1u ); }

SIXTRL_INLINE bool NS(Monitor_default_is_rolling)(
    void ) SIXTRL_NOEXCEPT { return true; }

SIXTRL_INLINE NS(status_type) NS(Monitor_set_is_rolling)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    bool const is_rolling_flag ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( mon != SIXTRL_NULLPTR ) {
        mon->is_rolling = ( is_rolling_flag )
            ? ( NS(be_flags_type) )1u : ( NS(be_flags_type) )0u;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Monitor_is_turn_ordered)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mon != SIXTRL_NULLPTR );
    return ( mon->is_turn_ordered == ( NS(be_flags_type) )1u ); }

SIXTRL_INLINE bool NS(Monitor_default_is_turn_ordered)(
    void ) SIXTRL_NOEXCEPT { return true; }

SIXTRL_INLINE NS(status_type) NS(Monitor_set_is_turn_ordered)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    bool const is_turn_ordered_flag ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( mon != SIXTRL_NULLPTR ) {
        mon->is_turn_ordered = ( is_turn_ordered_flag )
            ? ( NS(be_flags_type) )1u : ( NS(be_flags_type) )0u;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE bool NS(Monitor_is_particle_ordered)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT { return !NS(Monitor_is_turn_ordered)( mon ); }

SIXTRL_INLINE NS(status_type) NS(Monitor_set_is_particle_ordered)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    bool const is_particle_ordered ) SIXTRL_NOEXCEPT {
    return NS(Monitor_set_is_turn_ordered)( mon, !is_particle_ordered ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_addr_type) NS(Monitor_out_addr)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( mon != SIXTRL_NULLPTR );
    return mon->out_addr; }

SIXTRL_INLINE NS(be_addr_type) NS(Monitor_default_out_addr)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_addr_type) )0u; }

SIXTRL_INLINE NS(status_type) NS(Monitor_set_out_addr)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    bool const out_addr ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( mon != SIXTRL_NULLPTR ) {
        mon->out_addr = out_addr;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(cobj_size_type) NS(Monitor_out_addr_offset)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( mon ), NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size  = ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return ( NS(cobj_size_type) )5 * NS(CObjFlatBuffer_slot_based_size)(
                sizeof( NS(particle_index_type) ), slot_size ) +
           ( NS(cobj_size_type) )2 * NS(CObjFlatBuffer_slot_based_size)(
                sizeof( NS(be_flags_type) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(Monitor_out_addr_size)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( mon ), NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size  = ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(be_addr_type) ), slot_size ); }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const*
NS(Monitor_const_output_particles)( SIXTRL_BE_ARGPTR_DEC const
    NS(Monitor) *const SIXTRL_RESTRICT mon ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* )( uintptr_t
        )NS(Monitor_out_addr)( mon ); }

SIXTRL_INLINE SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Monitor_output_particles)( SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const
    SIXTRL_RESTRICT mon ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* )( uintptr_t
        )NS(Monitor_out_addr)( mon );
}

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Monitor)* NS(Monitor_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon
) SIXTRL_NOEXCEPT { if( mon != SIXTRL_NULLPTR ) NS(Monitor_clear)( mon );
    return mon; }

SIXTRL_INLINE NS(status_type) NS(Monitor_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon ) SIXTRL_NOEXCEPT {
    return NS(Monitor_init)( mon,
        NS(Monitor_default_num_stores)(),
        NS(Monitor_default_start)(),
        NS(Monitor_default_skip)(),
        NS(Monitor_default_min_particle_id)(),
        NS(Monitor_default_max_particle_id)(),
        NS(Monitor_default_is_rolling)(),
        NS(Monitor_default_is_turn_ordered)(),
        NS(Monitor_default_out_addr)() ); }

SIXTRL_INLINE NS(status_type) NS(Monitor_init)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon,
    NS(particle_index_type) const num_stores,
    NS(particle_index_type) const start,
    NS(particle_index_type) const skip,
    NS(particle_index_type) const min_particle_id,
    NS(particle_index_type) const max_particle_id,
    bool const is_rolling, bool const is_turn_ordered,
    NS(be_addr_type) const out_addr ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( mon != SIXTRL_NULLPTR ) {
        status = NS(Monitor_set_num_stores)( mon, num_stores ) |
                 NS(Monitor_set_start)( mon, start ) |
                 NS(Monitor_set_skip)( mon, skip ) |
                 NS(Monitor_set_min_particle_id)( mon, min_particle_id ) |
                 NS(Monitor_set_max_particle_id)( mon, max_particle_id ) |
                 NS(Monitor_set_is_rolling)( mon, is_rolling ) |
                 NS(Monitor_set_is_turn_ordered)( mon, is_turn_ordered ) |
                 NS(Monitor_set_out_addr)( mon, out_addr );
    }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Monitor_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const
        SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) )
    {
        if( dst != src )
        {
            status  = NS(Monitor_set_num_stores)( dst,
                          NS(Monitor_num_stores)( src ) );

            status |= NS(Monitor_set_start)( dst,
                          NS(Monitor_start)( src ) );

            status |= NS(Monitor_set_skip)(
                     dst, NS(Monitor_skip)( src ) );

            status |= NS(Monitor_set_max_particle_id)( dst,
                          NS(Monitor_max_particle_id)( src ) );

            status |= NS(Monitor_set_min_particle_id)( dst,
                          NS(Monitor_min_particle_id)( src ) );

            status |= NS(Monitor_set_is_rolling)(
                     dst, NS(Monitor_is_rolling)( src ) );

            status |= NS(Monitor_set_is_turn_ordered)( dst,
                          NS(Monitor_is_turn_ordered)( src ) );

            status |= NS(Monitor_set_out_addr)( dst,
                          NS(Monitor_out_addr)( src ) );
        }
        else
        {
            status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        }
    }

    return status;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(Monitor_cobj_type_id)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_obj_id_type)
        )SIXTRL_COBJECTS_TYPE_ID_MONITOR; }

SIXTRL_INLINE NS(cobj_size_type) NS(Monitor_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(Monitor_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(Monitor) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(Monitor_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(Monitor_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(Monitor_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( be_mon ),
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return NS(Monitor_cobj_reserved_handle_size)( slot_size ); }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(Monitor_any_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT {
    bool has_any = false;
    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
    {
        SIXTRL_ASSERT( ( uintptr_t )it <= ( uintptr_t )end );
        while( ( it != end ) && ( !has_any ) )
            has_any = NS(CObjIndex_is_monitor)( it++ );
    }
    return has_any;
}

SIXTRL_INLINE NS(be_size_type) NS(Monitor_num_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT {
    NS(be_size_type) num_be_monitors = ( NS(be_size_type) )0u;
    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) ) {
        SIXTRL_ASSERT( ( uintptr_t )it <= ( uintptr_t )end );
        for( ; it != end ; ++it ) {
            if( NS(CObjIndex_is_monitor)( it ) ) ++num_be_monitors; }
    }
    return num_be_monitors; }

SIXTRL_INLINE NS(be_size_type) NS(Monitor_indices_in_cobj_index_range)(
    SIXTRL_ARGPTR_DEC NS(be_size_type)* SIXTRL_RESTRICT indices_begin,
    NS(be_size_type) const max_num_indices,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end,
    NS(be_size_type) const start_index ) SIXTRL_NOEXCEPT {
    NS(be_size_type) num_be_monitors = ( NS(be_size_type) )0u;
    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( indices_begin != SIXTRL_NULLPTR ) &&
        ( max_num_indices > ( NS(be_size_type) )0u ) ) {
        NS(be_size_type) idx = start_index;
        SIXTRL_ASSERT( ( uintptr_t )it <= ( uintptr_t )end );
        while( ( it != end ) && ( num_be_monitors < max_num_indices ) ) {
            if( NS(CObjIndex_is_monitor)( it ) ) {
                indices_begin[ num_be_monitors++ ] = idx;
            }

            ++it;
            ++idx;
        }
    }
    return num_be_monitors; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Monitor_any_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(Monitor_any_in_cobj_index_range)(
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ) ); }

SIXTRL_INLINE NS(be_size_type) NS(Monitor_num_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(Monitor_num_in_cobj_index_range)(
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ) ); }

SIXTRL_INLINE NS(be_size_type)
NS(Monitor_indices_in_cobj_flat_buffer)(
    SIXTRL_ARGPTR_DEC NS(be_size_type)* SIXTRL_RESTRICT indices_begin,
    NS(be_size_type) const max_num_indices,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(be_size_type) const start_index ) SIXTRL_NOEXCEPT {
    return NS(Monitor_indices_in_cobj_index_range)(
        indices_begin, max_num_indices,
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ),
        start_index ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Monitor_any_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(Monitor_any_in_cobj_index_range)(
    NS(CBuffer_const_objects_begin)( b ), NS(CBuffer_const_objects_end)( b ) ); }

SIXTRL_INLINE NS(be_size_type) NS(Monitor_num_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(Monitor_num_in_cobj_index_range)(
    NS(CBuffer_const_objects_begin)( b ), NS(CBuffer_const_objects_end)( b ) ); }

SIXTRL_INLINE NS(be_size_type) NS(Monitor_indices_in_cbuffer)(
    SIXTRL_ARGPTR_DEC NS(be_size_type)* SIXTRL_RESTRICT indices_begin,
    NS(be_size_type) const max_num_indices,
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(be_size_type) const start_index ) SIXTRL_NOEXCEPT {
    return NS(Monitor_indices_in_cobj_index_range)(
        indices_begin, max_num_indices,
        NS(CBuffer_const_objects_begin)( b ), NS(CBuffer_const_objects_end)( b ),
        start_index ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(Monitor_is_active_for_particle)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT mon,
    NS(particle_index_type) const cur_at_turn,
    NS(particle_index_type) const cur_min_particle_id,
    NS(particle_index_type) const cur_max_particle_id ) SIXTRL_NOEXCEPT {
    bool is_active = false;

    if( ( mon != SIXTRL_NULLPTR ) &&
        ( NS(Monitor_start)( mon ) >= ( NS(particle_index_type)
            )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN ) &&
        ( cur_at_turn >= NS(Monitor_start)( mon ) ) &&
        ( ( cur_min_particle_id <= NS(Monitor_max_particle_id)( mon ) ) ||
          ( cur_max_particle_id >= NS(Monitor_min_particle_id)( mon ) ) ) &&
        ( ( cur_at_turn <= ( NS(Monitor_start)( mon ) +
                NS(Monitor_num_stores)( mon ) ) ) ||
          ( NS(Monitor_is_rolling)( mon ) ) ) )
    {
        SIXTRL_ASSERT( cur_min_particle_id <= cur_max_particle_id );
        SIXTRL_ASSERT( cur_min_particle_id >= ( NS(particle_index_type)
            )SIXTRL_PARTICLE_MIN_LEGAL_ID );

        SIXTRL_ASSERT( cur_min_particle_id <= ( NS(particle_index_type)
            )SIXTRL_PARTICLE_MAX_LEGAL_ID );

        SIXTRL_ASSERT( cur_max_particle_id >= ( NS(particle_index_type)
            )SIXTRL_PARTICLE_MIN_LEGAL_ID );

        SIXTRL_ASSERT( cur_max_particle_id <= ( NS(particle_index_type)
            )SIXTRL_PARTICLE_MAX_LEGAL_ID );

        SIXTRL_ASSERT( NS(Monitor_min_particle_id)( mon ) >= (
            NS(particle_index_type) )SIXTRL_PARTICLE_MIN_LEGAL_ID );

        SIXTRL_ASSERT( NS(Monitor_min_particle_id)( mon ) <= (
            NS(particle_index_type) )SIXTRL_PARTICLE_MAX_LEGAL_ID );

        SIXTRL_ASSERT( NS(Monitor_max_particle_id)( mon ) >= (
            NS(particle_index_type) )SIXTRL_PARTICLE_MIN_LEGAL_ID );

        SIXTRL_ASSERT( NS(Monitor_max_particle_id)( mon ) <= (
            NS(particle_index_type) )SIXTRL_PARTICLE_MAX_LEGAL_ID );

        SIXTRL_ASSERT( cur_at_turn >= ( NS(particle_index_type )
            )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN );

        SIXTRL_ASSERT( cur_at_turn <= ( NS(particle_index_type )
            )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN );

        is_active = true;
    }

    return is_active;
}

SIXTRL_INLINE NS(particles_num_type) NS(Monitor_output_particles_index)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT be_mon,
    NS(particle_index_type) const particle_id,
    NS(particle_index_type) const at_turn )
{
    typedef NS(particle_index_type) nturn_t;
    NS(particles_num_type) out_idx = ( NS(particles_num_type) )-1;

    nturn_t const n_stores = NS(Monitor_num_stores)( be_mon );
    nturn_t const start    = NS(Monitor_start)( be_mon );
    nturn_t const skip = NS(Monitor_skip)( be_mon );

    SIXTRL_ASSERT( at_turn     >= ( nturn_t )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN );
    SIXTRL_ASSERT( at_turn     <= ( nturn_t )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN );
    SIXTRL_ASSERT( particle_id >= ( nturn_t )SIXTRL_PARTICLE_MIN_LEGAL_ID );
    SIXTRL_ASSERT( particle_id <= ( nturn_t )SIXTRL_PARTICLE_MAX_LEGAL_ID );
    SIXTRL_ASSERT( start       >= ( nturn_t )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN );
    SIXTRL_ASSERT( start       <= ( nturn_t )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN );
    SIXTRL_ASSERT( n_stores    >= ( nturn_t )0u );
    SIXTRL_ASSERT( skip        >= ( nturn_t )1u );

    SIXTRL_ASSERT( NS(Monitor_min_particle_id)( be_mon ) >=
                   ( nturn_t )SIXTRL_PARTICLE_MIN_LEGAL_ID );

    SIXTRL_ASSERT( NS(Monitor_min_particle_id)( be_mon ) <=
                   ( nturn_t )SIXTRL_PARTICLE_MAX_LEGAL_ID );

    SIXTRL_ASSERT( NS(Monitor_max_particle_id)( be_mon ) >=
                   ( nturn_t )SIXTRL_PARTICLE_MIN_LEGAL_ID );

    SIXTRL_ASSERT( NS(Monitor_max_particle_id)( be_mon ) <=
                   ( nturn_t )SIXTRL_PARTICLE_MAX_LEGAL_ID );

    if( ( start <= at_turn ) &&
        ( n_stores > ( nturn_t )0u ) && ( skip > ( nturn_t )0u ) &&
        ( particle_id >= NS(Monitor_min_particle_id)( be_mon ) ) &&
        ( particle_id <= NS(Monitor_max_particle_id)( be_mon ) ) )
    {
        bool should_be_stored = false;
        nturn_t turn_in_be = at_turn - start;

        if( ( skip == ( nturn_t )1u ) ||
            ( ( turn_in_be % skip ) == ( nturn_t )0u ) )
        {
            turn_in_be = turn_in_be / skip;

            if( turn_in_be < n_stores )
            {
                should_be_stored = true;
            }
            else if( NS(Monitor_is_rolling)( be_mon ) )
            {
                turn_in_be = turn_in_be % n_stores;
                should_be_stored = true;
            }
        }

        if( should_be_stored )
        {
            nturn_t const be_min_id = NS(Monitor_min_particle_id)( be_mon );

            if( NS(Monitor_is_turn_ordered)( be_mon ) )
            {
                out_idx  = ( NS(particles_num_type) )( ( 1 +
                    NS(Monitor_max_particle_id)( be_mon ) - be_min_id ) *
                        turn_in_be + ( particle_id - be_min_id ) );
            }
            else
            {
                 out_idx = ( NS(particles_num_type) )(
                     ( particle_id - be_min_id ) * n_stores + turn_in_be );
            }
        }
    }

    return out_idx;
}

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(Monitor_any_active_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id ) SIXTRL_NOEXCEPT {
    bool has_any_active = false;
    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) )
    {
        SIXTRL_ASSERT( ( uintptr_t )it <= ( uintptr_t )end );
        while( ( it != end ) && ( !has_any_active ) ) {
            SIXTRL_BE_ARGPTR_DEC NS(Monitor) const* be_mon =
                NS(Monitor_const_from_cobj_index)( it++ );
            if( be_mon != SIXTRL_NULLPTR ) {
                has_any_active = NS(Monitor_is_active_for_particle)(
                    be_mon, current_at_turn, current_min_particle_id,
                        current_max_particle_id ); }
        }
    }
    return has_any_active;
}

SIXTRL_INLINE NS(be_size_type) NS(Monitor_num_active_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id ) SIXTRL_NOEXCEPT {
    NS(be_size_type) num_be_monitors = ( NS(be_size_type) )0u;
    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) ) {
        SIXTRL_ASSERT( ( uintptr_t )it <= ( uintptr_t )end );
        for( ; it != end ; ++it )
        {
            SIXTRL_BE_ARGPTR_DEC NS(Monitor) const* be_mon =
                NS(Monitor_const_from_cobj_index)( it );

            if( NS(Monitor_is_active_for_particle)( be_mon, current_at_turn,
                    current_min_particle_id, current_max_particle_id ) ) {
                ++num_be_monitors; }
        }
    }
    return num_be_monitors;
}

SIXTRL_INLINE NS(be_size_type)
NS(Monitor_active_indices_in_cobj_index_range)(
    SIXTRL_ARGPTR_DEC NS(be_size_type)* SIXTRL_RESTRICT indices_begin,
    NS(be_size_type) const max_num_indices,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id,
    NS(be_size_type) const start_index ) SIXTRL_NOEXCEPT {

    NS(be_size_type) num_be_monitors = ( NS(be_size_type) )0u;

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( indices_begin != SIXTRL_NULLPTR ) &&
        ( max_num_indices > ( NS(be_size_type) )0u ) ) {
        NS(be_size_type) idx = start_index;
        SIXTRL_ASSERT( ( uintptr_t )it <= ( uintptr_t )end );
        while( ( it != end ) && ( num_be_monitors < max_num_indices ) )
        {
            SIXTRL_BE_ARGPTR_DEC NS(Monitor) const* be_mon =
                NS(Monitor_const_from_cobj_index)( it );

            if( NS(Monitor_is_active_for_particle)( be_mon, current_at_turn,
                    current_min_particle_id, current_max_particle_id ) ) {
                indices_begin[ num_be_monitors++ ] = idx; }

            ++it;
            ++idx;
        }
    }

    return num_be_monitors; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Monitor_any_active_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id ) SIXTRL_NOEXCEPT {
    return NS(Monitor_any_active_in_cobj_index_range)(
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ),
        current_at_turn, current_min_particle_id, current_max_particle_id ); }

SIXTRL_INLINE NS(be_size_type) NS(Monitor_num_active_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id ) SIXTRL_NOEXCEPT {
    return NS(Monitor_num_active_in_cobj_index_range)(
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ),
        current_at_turn, current_min_particle_id, current_max_particle_id ); }

SIXTRL_INLINE NS(be_size_type)
NS(Monitor_active_indices_in_cobj_flat_buffer)(
    SIXTRL_ARGPTR_DEC NS(be_size_type)* SIXTRL_RESTRICT indices_begin,
    NS(be_size_type) const max_num_indices,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id,
    NS(be_size_type) const start_index ) SIXTRL_NOEXCEPT {
    return NS(Monitor_active_indices_in_cobj_index_range)(
        indices_begin, max_num_indices,
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_const_indices_end)( buffer, slot_size ),
        current_at_turn, current_min_particle_id, current_max_particle_id,
        start_index ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Monitor_any_active_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id ) SIXTRL_NOEXCEPT {
    return NS(Monitor_any_active_in_cobj_index_range)(
        NS(CBuffer_const_objects_begin)( b ), NS(CBuffer_const_objects_end)( b ),
        current_at_turn, current_min_particle_id, current_max_particle_id ); }

SIXTRL_INLINE NS(be_size_type) NS(Monitor_num_active_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id ) SIXTRL_NOEXCEPT {
    return NS(Monitor_num_active_in_cobj_index_range)(
        NS(CBuffer_const_objects_begin)( b ), NS(CBuffer_const_objects_end)( b ),
        current_at_turn, current_min_particle_id, current_max_particle_id ); }

SIXTRL_INLINE NS(be_size_type) NS(Monitor_active_indices_in_cbuffer)(
    SIXTRL_ARGPTR_DEC NS(be_size_type)* SIXTRL_RESTRICT indices_begin,
    NS(be_size_type) const max_num_indices,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(particle_index_type) const current_at_turn,
    NS(particle_index_type) const current_min_particle_id,
    NS(particle_index_type) const current_max_particle_id,
    NS(be_size_type) const start_index ) SIXTRL_NOEXCEPT {
    return NS(Monitor_active_indices_in_cobj_index_range)(
        indices_begin, max_num_indices, NS(CBuffer_const_objects_begin)( b ),
        NS(CBuffer_const_objects_end)( b ), current_at_turn,
        current_min_particle_id, current_max_particle_id, start_index ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(status_type) NS(Monitor_reset)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT mon ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( mon != SIXTRL_NULLPTR )
    {
        status = NS(Monitor_set_out_addr)(
            mon, NS(Monitor_default_out_addr)() );
    }
    return status;
}

SIXTRL_INLINE NS(status_type) NS(Monitor_reset_all_in_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) ) {
        SIXTRL_ASSERT( ( uintptr_t )it <= ( uintptr_t )end );
        for( ; it != end ; ++it )
        {
            SIXTRL_BE_ARGPTR_DEC NS(Monitor)* mon =
                NS(Monitor_from_cobj_index)( it );

            if( mon != SIXTRL_NULLPTR )
                status |= NS(Monitor_reset)( mon );
        }
    }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Monitor_reset_all_in_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(Monitor_reset_all_in_cobj_index_range)(
        NS(CObjFlatBuffer_indices_begin)( buffer, slot_size ),
        NS(CObjFlatBuffer_indices_end)( buffer, slot_size ) ); }

SIXTRL_INLINE NS(status_type) NS(Monitor_reset_all_in_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(Monitor_reset_all_in_cobj_index_range)(
    NS(CBuffer_objects_begin)( b ), NS(CBuffer_objects_end)( b ) ); }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_monitor)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(Monitor_cobj_type_id)(),
        NS(Monitor_cobj_actual_handle_size)(
            ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor) const*
NS(Monitor_const_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return ( NS(CObjIndex_is_monitor)( obj ) )
        ? ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj
) SIXTRL_NOEXCEPT { return ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
    )NS(Monitor_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor) const*
NS(Monitor_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(Monitor_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(Monitor_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor) const*
NS(Monitor_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Monitor_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)*
NS(Monitor_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Monitor_from_cobj_index)(
        NS(CBuffer_index_at)( buffer, idx ) ); }

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKL_COMMON_BE_MONITOR_BE_MONITOR_C99_HEADER_H__ */
