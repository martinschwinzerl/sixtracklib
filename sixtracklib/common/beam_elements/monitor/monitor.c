#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/monitor/monitor.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor) const*
NS(Monitor_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(Monitor_const_from_cbuffer)( buffer, idx ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)* NS(Monitor_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(Monitor_from_cbuffer)( buffer, idx ); }

NS(cobj_obj_id_type) NS(Monitor_cobj_type_id_ext)() SIXTRL_NOEXCEPT {
    return NS(Monitor_cobj_type_id)(); }

NS(size_type) NS(Monitor_cobj_num_dataptrs_ext)() SIXTRL_NOEXCEPT {
    return NS(Monitor_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(Monitor_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(Monitor_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(Monitor_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(Monitor_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(Monitor_cobj_required_num_bytes_ext)( SIXTRL_BE_ARGPTR_DEC
    const NS(Monitor) *const SIXTRL_RESTRICT monitor,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(Monitor_cobj_required_num_bytes)( monitor, slot_size ); }

SIXTRL_BE_ARGPTR_DEC NS(Monitor)* NS(Monitor_preset_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT cavity ) SIXTRL_NOEXCEPT {
        return NS(Monitor_preset)( cavity ); }

NS(status_type) NS(Monitor_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT cavity ) SIXTRL_NOEXCEPT {
        return NS(Monitor_clear)( cavity ); }

bool NS(Monitor_cobj_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(Monitor_cbuffer_can_be_added)( buffer,
    requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)* NS(Monitor_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    return NS(Monitor_cbuffer_new)( buffer ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)* NS(Monitor_cbuffer_add_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particle_index_type) const num_stores,
    NS(particle_index_type) const start, NS(particle_index_type) const skip,
    NS(particle_index_type) const min_particle_id,
    NS(particle_index_type) const max_particle_id,
    NS(be_flags_type) const is_rolling,
    NS(be_flags_type) const is_turn_ordered,
    NS(be_addr_type) const out_addr ) {
    return NS(Monitor_cbuffer_add)( buffer, num_stores, start, skip,
        min_particle_id, max_particle_id, is_rolling, is_turn_ordered,
            out_addr ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Monitor)* NS(Monitor_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT orig ) {
    return NS(Monitor_cbuffer_add_copy)( buffer, orig ); }

