#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/track/track_config.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(TrackConfig_const_from_cbuffer)( buffer, idx ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig)* NS(TrackConfig_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(TrackConfig_from_cbuffer)( buffer, idx ); }

NS(cobj_obj_id_type) NS(TrackConfig_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(TrackConfig_cobj_type_id)(); }

NS(size_type) NS(TrackConfig_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(TrackConfig_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(TrackConfig_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(TrackConfig_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(TrackConfig_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(TrackConfig_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(TrackConfig_cobj_required_num_bytes_ext)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(TrackConfig_cobj_required_num_bytes)( config, slot_size ); }

SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* NS(TrackConfig_preset_ext)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT { return NS(TrackConfig_preset)( config ); }

NS(status_type) NS(TrackConfig_clear_ext)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT { return NS(TrackConfig_clear)( config ); }

bool NS(TrackConfig_cobj_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(TrackConfig_cbuffer_can_be_added)( buffer,
    requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig)* NS(TrackConfig_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    return NS(TrackConfig_cbuffer_new)( buffer ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig)* NS(TrackConfig_cbuffer_add_ext)(
    SIXTRL_TRACK_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particle_real_type) const x_min, NS(particle_real_type) const x_max,
    NS(particle_real_type) const y_min, NS(particle_real_type) const y_max,
    NS(track_flags_type) const check_aperture_flags,
    NS(be_real_type) const min_drift_length )
{
    return NS(TrackConfig_cbuffer_add)( buffer, x_min, x_max, y_min, y_max,
        check_aperture_flags, min_drift_length );
}

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT orig ) {
    return NS(TrackConfig_cbuffer_add_copy)( buffer, orig ); }
