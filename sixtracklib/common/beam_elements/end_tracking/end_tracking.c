#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/end_tracking/end_tracking.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(EndTracking_const_from_cbuffer)( buffer, idx ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(EndTracking_from_cbuffer)( buffer, idx ); }

NS(cobj_obj_id_type) NS(EndTracking_cobj_type_id_ext)() SIXTRL_NOEXCEPT {
    return NS(EndTracking_cobj_type_id)(); }

NS(size_type) NS(EndTracking_cobj_num_dataptrs_ext)() SIXTRL_NOEXCEPT {
    return NS(EndTracking_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(EndTracking_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(EndTracking_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(EndTracking_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(EndTracking_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(EndTracking_cobj_required_num_bytes_ext)( SIXTRL_BE_ARGPTR_DEC
    const NS(EndTracking) *const SIXTRL_RESTRICT elem,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(EndTracking_cobj_required_num_bytes)( elem, slot_size ); }

SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* NS(EndTracking_preset_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{ return NS(EndTracking_preset)( elem ); }

NS(status_type) NS(EndTracking_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{ return NS(EndTracking_clear)( elem ); }

NS(status_type) NS(EndTracking_terminate_lattice_with_eot_marker_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT lattice_buffer,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_eot_marker_index
) SIXTRL_NOEXCEPT {
    return NS(EndTracking_terminate_lattice_with_eot_marker_cbuffer)(
        lattice_buffer, line_start_index, line_start_at_element,
            ptr_eot_marker_index ); }

bool NS(EndTracking_cobj_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(EndTracking_cbuffer_can_be_added)( buffer,
    requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)* NS(EndTracking_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    return NS(EndTracking_cbuffer_new)( buffer ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)* NS(EndTracking_cbuffer_add_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx,
    bool const ends_turn ) { return NS(EndTracking_cbuffer_add)(
        buffer, next_at_element, next_buffer_idx, ends_turn ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT orig ) {
    return NS(EndTracking_cbuffer_add_copy)( buffer, orig ); }

