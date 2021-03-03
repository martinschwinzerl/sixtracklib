#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beamfields/sc_qgauss.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile) const*
NS(SCQGaussProfile_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(SCQGaussProfile_const_from_cbuffer)( buffer, idx ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(SCQGaussProfile_from_cbuffer)( buffer, idx ); }

NS(cobj_obj_id_type) NS(SCQGaussProfile_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(SCQGaussProfile_cobj_type_id)(); }

NS(size_type) NS(SCQGaussProfile_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(SCQGaussProfile_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(SCQGaussProfile_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(SCQGaussProfile_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(SCQGaussProfile_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(SCQGaussProfile_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(SCQGaussProfile_cobj_required_num_bytes_ext)( SIXTRL_BE_ARGPTR_DEC
    const NS(SCQGaussProfile) *const SIXTRL_RESTRICT sc,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(SCQGaussProfile_cobj_required_num_bytes)( sc, slot_size ); }

SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)* NS(SCQGaussProfile_preset_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)* SIXTRL_RESTRICT sc ) SIXTRL_NOEXCEPT {
        return NS(SCQGaussProfile_preset)( sc ); }

NS(status_type) NS(SCQGaussProfile_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)* SIXTRL_RESTRICT sc ) SIXTRL_NOEXCEPT {
        return NS(SCQGaussProfile_clear)( sc ); }

bool NS(SCQGaussProfile_cobj_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(SCQGaussProfile_cbuffer_can_be_added)( buffer,
    requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    return NS(SCQGaussProfile_cbuffer_new)( buffer ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cbuffer_add_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_real_type) const number_of_particles,
    NS(be_real_type) const circumference,
    NS(be_real_type) const sigma_x, NS(be_real_type) const sigma_y,
    NS(be_real_type) const length,
    NS(be_real_type) const x_co, NS(be_real_type) const y_co,
    NS(be_real_type) const min_sigma_diff, NS(be_real_type) const q_param,
    bool const enabled ) {
        return NS(SCQGaussProfile_cbuffer_add)( buffer,
            number_of_particles, circumference, sigma_x, sigma_y, length,
                x_co, y_co, min_sigma_diff, q_param, enabled ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT orig ) {
    return NS(SCQGaussProfile_cbuffer_add_copy)( buffer, orig ); }
