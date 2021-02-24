#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/rf_multipole/rf_multipole.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_BE_ARGPTR_DEC NS(RFMultipole) const*
NS(RFMultipole_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(RFMultipole_const_from_cbuffer)( buffer, idx ); }

SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* NS(RFMultipole_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(RFMultipole_from_cbuffer)( buffer, idx ); }

NS(cobj_obj_id_type) NS(RFMultipole_cobj_type_id_ext)() SIXTRL_NOEXCEPT {
    return NS(RFMultipole_cobj_type_id)(); }

NS(size_type) NS(RFMultipole_cobj_num_dataptrs_ext)() SIXTRL_NOEXCEPT {
    return NS(RFMultipole_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(RFMultipole_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(RFMultipole_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(RFMultipole_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(RFMultipole_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(RFMultipole_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(RFMultipole_cobj_required_num_bytes)( mp, slot_size ); }

SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* NS(RFMultipole_preset_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT { return NS(RFMultipole_preset)( mp ); }

NS(status_type) NS(RFMultipole_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* SIXTRL_RESTRICT mp )
SIXTRL_NOEXCEPT { return NS(RFMultipole_clear)( mp ); }

bool NS(RFMultipole_cobj_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(be_order_type) const max_order,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(RFMultipole_cbuffer_can_be_added)( buffer,
    max_order, requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs );
}

SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* NS(RFMultipole_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_order_type) const max_order ) {
    return NS(RFMultipole_cbuffer_new)( buffer, max_order ); }

SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* NS(RFMultipole_cbuffer_add_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_order_type) const max_order, NS(be_order_type) const order,
    NS(be_real_type) const voltage, NS(be_real_type) const frequency,
    NS(be_real_type) const lag, NS(be_addr_type) const bal_addr,
    NS(be_addr_type) const phase_addr ) {
        return NS(RFMultipole_cbuffer_add)( buffer, max_order, order,
            voltage, frequency, lag, bal_addr, phase_addr ); }

SIXTRL_BE_ARGPTR_DEC NS(RFMultipole)* NS(RFMultipole_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(RFMultipole) *const SIXTRL_RESTRICT orig ) {
    return NS(RFMultipole_cbuffer_add_copy)( buffer, orig ); }

