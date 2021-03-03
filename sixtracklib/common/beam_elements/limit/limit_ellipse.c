#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/limit/limit_ellipse.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitEllipse) const*
NS(LimitEllipse_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(LimitEllipse_const_from_cbuffer)( buffer, idx ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitEllipse)*
NS(LimitEllipse_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(LimitEllipse_from_cbuffer)( buffer, idx ); }

NS(cobj_obj_id_type) NS(LimitEllipse_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(LimitEllipse_cobj_type_id)(); }

NS(size_type) NS(LimitEllipse_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(LimitEllipse_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(LimitEllipse_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(LimitEllipse_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(LimitEllipse_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(LimitEllipse_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(LimitEllipse_cobj_required_num_bytes_ext)( SIXTRL_BE_ARGPTR_DEC
    const NS(LimitEllipse) *const SIXTRL_RESTRICT limit,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(LimitEllipse_cobj_required_num_bytes)( limit, slot_size ); }

SIXTRL_BE_ARGPTR_DEC NS(LimitEllipse)* NS(LimitEllipse_preset_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitEllipse)* SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { return NS(LimitEllipse_preset)( limit ); }

NS(status_type) NS(LimitEllipse_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitEllipse)* SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { return NS(LimitEllipse_clear)( limit ); }

bool NS(LimitEllipse_cobj_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(LimitEllipse_cbuffer_can_be_added)( buffer,
    requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitEllipse)*
NS(LimitEllipse_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    return NS(LimitEllipse_cbuffer_new)( buffer ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitEllipse)*
NS(LimitEllipse_cbuffer_add_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_real_type) const a_squ, NS(be_real_type) const b_squ ) {
        return NS(LimitEllipse_cbuffer_add)( buffer, a_squ, b_squ ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitEllipse)*
NS(LimitEllipse_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT orig ) {
    return NS(LimitEllipse_cbuffer_add_copy)( buffer, orig ); }
