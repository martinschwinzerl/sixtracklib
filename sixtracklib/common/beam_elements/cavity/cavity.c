#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/cavity.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_BE_ARGPTR_DEC NS(Cavity) const* NS(Cavity_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(Cavity_const_from_cbuffer)( buffer, idx ); }

SIXTRL_BE_ARGPTR_DEC NS(Cavity)* NS(Cavity_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(Cavity_from_cbuffer)( buffer, idx ); }

NS(cobj_obj_id_type) NS(Cavity_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(Cavity_cobj_type_id)(); }

NS(size_type) NS(Cavity_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(Cavity_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(Cavity_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(Cavity_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(Cavity_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(Cavity_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(Cavity_cobj_required_num_bytes_ext)( SIXTRL_BE_ARGPTR_DEC
    const NS(Cavity) *const SIXTRL_RESTRICT cavity,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(Cavity_cobj_required_num_bytes)( cavity, slot_size ); }

SIXTRL_BE_ARGPTR_DEC NS(Cavity)* NS(Cavity_preset_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT cavity ) SIXTRL_NOEXCEPT {
        return NS(Cavity_preset)( cavity ); }

NS(status_type) NS(Cavity_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(Cavity)* SIXTRL_RESTRICT cavity ) SIXTRL_NOEXCEPT {
        return NS(Cavity_clear)( cavity ); }

bool NS(Cavity_cobj_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(Cavity_cbuffer_can_be_added)( buffer,
    requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_BE_ARGPTR_DEC NS(Cavity)* NS(Cavity_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    return NS(Cavity_cbuffer_new)( buffer ); }

SIXTRL_BE_ARGPTR_DEC NS(Cavity)* NS(Cavity_cbuffer_add_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_real_type) const voltage, NS(be_real_type) const frequency,
    NS(be_real_type) const lag ) {
        return NS(Cavity_cbuffer_add)( buffer, voltage, frequency, lag ); }

SIXTRL_BE_ARGPTR_DEC NS(Cavity)* NS(Cavity_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT orig ) {
    return NS(Cavity_cbuffer_add_copy)( buffer, orig ); }

