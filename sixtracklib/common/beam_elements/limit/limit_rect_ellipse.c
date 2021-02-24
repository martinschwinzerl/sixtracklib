#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/limit/limit_rect_ellipse.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse) const*
NS(LimitRectEllipse_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(LimitRectEllipse_const_from_cbuffer)( buffer, idx ); }

SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)*
NS(LimitRectEllipse_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(LimitRectEllipse_from_cbuffer)( buffer, idx ); }

NS(cobj_obj_id_type) NS(LimitRectEllipse_cobj_type_id_ext)() SIXTRL_NOEXCEPT {
    return NS(LimitRectEllipse_cobj_type_id)(); }

NS(size_type) NS(LimitRectEllipse_cobj_num_dataptrs_ext)() SIXTRL_NOEXCEPT {
        return NS(LimitRectEllipse_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(LimitRectEllipse_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(LimitRectEllipse_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(LimitRectEllipse_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(LimitRectEllipse_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(LimitRectEllipse_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(LimitRectEllipse_cobj_required_num_bytes)( limit, slot_size ); }

SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* NS(LimitRectEllipse_preset_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { return NS(LimitRectEllipse_preset)( limit ); }

NS(status_type) NS(LimitRectEllipse_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { return NS(LimitRectEllipse_clear)( limit ); }

bool NS(LimitRectEllipse_cobj_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(LimitRectEllipse_cbuffer_can_be_added)( buffer,
    requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* NS(LimitRectEllipse_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    return NS(LimitRectEllipse_cbuffer_new)( buffer ); }

SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* NS(LimitRectEllipse_cbuffer_add_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_real_type) const x_max, NS(be_real_type) const y_max,
    NS(be_real_type) const a_squ, NS(be_real_type) const b_squ ) {
        return NS(LimitRectEllipse_cbuffer_add)(
            buffer, x_max, y_max, a_squ, b_squ ); }

SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)*
NS(LimitRectEllipse_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT orig )
{
    return NS(LimitRectEllipse_cbuffer_add_copy)( buffer, orig );
}

