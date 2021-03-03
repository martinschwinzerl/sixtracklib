#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/dipedge/dipedge.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DipoleEdge) const*
NS(DipoleEdge_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(DipoleEdge_const_from_cbuffer)( buffer, idx ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DipoleEdge)* NS(DipoleEdge_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(DipoleEdge_from_cbuffer)( buffer, idx ); }

NS(cobj_obj_id_type) NS(DipoleEdge_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(DipoleEdge_cobj_type_id)(); }

NS(size_type) NS(DipoleEdge_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(DipoleEdge_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(DipoleEdge_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(DipoleEdge_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(DipoleEdge_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(DipoleEdge_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(DipoleEdge_cobj_required_num_bytes_ext)( SIXTRL_BE_ARGPTR_DEC
    const NS(DipoleEdge) *const SIXTRL_RESTRICT cavity,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(DipoleEdge_cobj_required_num_bytes)( cavity, slot_size ); }

SIXTRL_BE_ARGPTR_DEC NS(DipoleEdge)* NS(DipoleEdge_preset_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(DipoleEdge)* SIXTRL_RESTRICT cavity ) SIXTRL_NOEXCEPT {
        return NS(DipoleEdge_preset)( cavity ); }

NS(status_type) NS(DipoleEdge_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(DipoleEdge)* SIXTRL_RESTRICT cavity ) SIXTRL_NOEXCEPT {
        return NS(DipoleEdge_clear)( cavity ); }

bool NS(DipoleEdge_cobj_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(DipoleEdge_cbuffer_can_be_added)( buffer,
    requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DipoleEdge)* NS(DipoleEdge_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    return NS(DipoleEdge_cbuffer_new)( buffer ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DipoleEdge)* NS(DipoleEdge_cbuffer_add_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_real_type) const r21, NS(be_real_type) const r43 ) {
        return NS(DipoleEdge_cbuffer_add)( buffer, r21, r43 ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DipoleEdge)*
NS(DipoleEdge_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(DipoleEdge) *const SIXTRL_RESTRICT orig ) {
    return NS(DipoleEdge_cbuffer_add_copy)( buffer, orig ); }

