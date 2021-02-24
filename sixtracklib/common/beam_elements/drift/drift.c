#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_BE_ARGPTR_DEC NS(Drift) const* NS(Drift_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(Drift_const_from_cbuffer)( buffer, idx ); }

SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(Drift_from_cbuffer)( buffer, idx ); }

NS(cobj_obj_id_type) NS(Drift_cobj_type_id_ext)() SIXTRL_NOEXCEPT {
    return NS(Drift_cobj_type_id)(); }

NS(size_type) NS(Drift_cobj_num_dataptrs_ext)() SIXTRL_NOEXCEPT {
        return NS(Drift_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(Drift_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(Drift_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(Drift_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(Drift_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(Drift_cobj_required_num_bytes_ext)( SIXTRL_BE_ARGPTR_DEC
    const NS(Drift) *const SIXTRL_RESTRICT drift,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(Drift_cobj_required_num_bytes)( drift, slot_size ); }

SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_preset_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT {
        return NS(Drift_preset)( drift ); }

NS(status_type) NS(Drift_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT {
        return NS(Drift_clear)( drift ); }

bool NS(Drift_cobj_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(Drift_cbuffer_can_be_added)( buffer,
    requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    return NS(Drift_cbuffer_new)( buffer ); }

SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_cbuffer_add_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_real_type) const length ) {
        return NS(Drift_cbuffer_add)( buffer, length ); }

SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT orig ) {
    return NS(Drift_cbuffer_add_copy)( buffer, orig ); }

/* ------------------------------------------------------------------------- */

SIXTRL_BE_ARGPTR_DEC NS(DriftExact) const* NS(DriftExact_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(DriftExact_const_from_cbuffer)( buffer, idx ); }

SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* NS(DriftExact_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(DriftExact_from_cbuffer)( buffer, idx ); }

NS(cobj_obj_id_type) NS(DriftExact_cobj_type_id_ext)() SIXTRL_NOEXCEPT {
    return NS(DriftExact_cobj_type_id)(); }

NS(size_type) NS(DriftExact_cobj_num_dataptrs_ext)() SIXTRL_NOEXCEPT {
        return NS(DriftExact_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(DriftExact_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(DriftExact_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(DriftExact_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(DriftExact_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(DriftExact_cobj_required_num_bytes_ext)( SIXTRL_BE_ARGPTR_DEC
    const NS(DriftExact) *const SIXTRL_RESTRICT drift,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(DriftExact_cobj_required_num_bytes)( drift, slot_size ); }

SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* NS(DriftExact_preset_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT {
        return NS(DriftExact_preset)( drift ); }

NS(status_type) NS(DriftExact_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT {
        return NS(DriftExact_clear)( drift ); }

bool NS(DriftExact_cobj_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(DriftExact_cbuffer_can_be_added)( buffer,
    requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* NS(DriftExact_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    return NS(DriftExact_cbuffer_new)( buffer ); }

SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* NS(DriftExact_cbuffer_add_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_real_type) const length ) {
        return NS(DriftExact_cbuffer_add)( buffer, length ); }

SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* NS(DriftExact_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT orig ) {
    return NS(DriftExact_cbuffer_add_copy)( buffer, orig ); }
