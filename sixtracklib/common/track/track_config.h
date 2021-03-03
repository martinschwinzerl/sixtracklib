#ifndef SIXTRACKLIB_COMMON_TRACK_TRACK_CONFIG_H__
#define SIXTRACKLIB_COMMON_TRACK_TRACK_CONFIG_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

struct NS(CObjIndex);
struct NS(CBuffer);

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(TrackConfig)
{
    NS(particle_real_type) x_min                   SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type) x_max                   SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type) y_min                   SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(particle_real_type) y_max                   SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(track_flags_type)   check_aperture_at_drift SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)       check_min_drift_length  SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(TrackConfig);


/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(TrackConfig_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(TrackConfig_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(TrackConfig_cobj_actual_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(TrackConfig_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(TrackConfig_cobj_required_num_bytes)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)*
NS(TrackConfig_preset)( SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT
    config ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(TrackConfig_clear)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(TrackConfig_init)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(particle_real_type) const x_min, NS(particle_real_type) const x_max,
    NS(particle_real_type) const y_min, NS(particle_real_type) const y_max,
    NS(track_flags_type) const check_aperture_at_drift,
    NS(be_real_type) const check_min_drift_length ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(TrackConfig_x_min)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(TrackConfig_default_x_min)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(TrackConfig_set_x_min)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(particle_real_type) const x_min ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(TrackConfig_x_max)(
    SIXTRL_TRACK_ARGPTR_DEC  const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(TrackConfig_default_x_max)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(TrackConfig_set_x_max)(
    SIXTRL_TRACK_ARGPTR_DEC  NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(particle_real_type) const x_max ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(TrackConfig_y_min)(
    SIXTRL_TRACK_ARGPTR_DEC  const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(TrackConfig_default_y_min)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(TrackConfig_set_y_min)(
    SIXTRL_TRACK_ARGPTR_DEC  NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(particle_real_type) const y_min ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(TrackConfig_y_max)(
    SIXTRL_TRACK_ARGPTR_DEC  const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_type) NS(TrackConfig_default_y_max)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(TrackConfig_set_y_max)(
    SIXTRL_TRACK_ARGPTR_DEC  NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(particle_real_type) const y_max ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(track_flags_type)
NS(TrackConfig_check_aperture_at_drift)(
    SIXTRL_TRACK_ARGPTR_DEC  const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(track_flags_type)
NS(TrackConfig_default_check_aperture_at_drift)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(TrackConfig_set_check_aperture_at_drift)(
    SIXTRL_TRACK_ARGPTR_DEC  NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_flags_type) const check_aperture_at_drift ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(TrackConfig_always_check_aperture_at_drift)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(TrackConfig_never_check_aperture_at_drift)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(TrackConfig_conditional_check_aperture_at_drift)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type)
NS(TrackConfig_check_min_drift_length)(
    SIXTRL_TRACK_ARGPTR_DEC  const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type)
NS(TrackConfig_default_check_min_drift_length)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(TrackConfig_set_check_min_drift_length)(
    SIXTRL_TRACK_ARGPTR_DEC  NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(be_real_type) const check_min_drift_length ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN bool NS(TrackConfig_is_consistent)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(TrackConfig_update)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(TrackConfig_copy)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT destination,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT source ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_track_config)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
    obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_cobj_flat_buffer_save)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(TrackConfig_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(TrackConfig_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(TrackConfig_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(TrackConfig_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(TrackConfig_cobj_required_num_bytes_ext)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)*
NS(TrackConfig_preset_ext)( SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)*
    SIXTRL_RESTRICT config ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(TrackConfig_clear_ext)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */
#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsStoreResultTypeTraits< ::NS(TrackConfig) >
    {
        typedef ::NS(TrackConfig) value_type;
        typedef SIXTRL_TRACK_ARGPTR_DEC value_type const* const_pointer;
        typedef SIXTRL_TRACK_ARGPTR_DEC value_type* pointer;
    };

    template<> struct CObjectsTraits< ::NS(TrackConfig) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_TRACK_CONFIG;
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_TRACK_CONFIG > {
            typedef ::NS(TrackConfig) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* ************************************************************************* */
/* *****          Implementation of C inline functions                   *** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE )
    #include "sixtracklib/common/track/track_config_cobj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES )  && !defined( _GPUCODE ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(TrackConfig_cobj_type_id)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_obj_id_type)
        )SIXTRL_COBJECTS_TYPE_ID_TRACK_CONFIG; }

SIXTRL_INLINE NS(cobj_size_type) NS(TrackConfig_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(TrackConfig_cobj_actual_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(TrackConfig) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(TrackConfig_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(TrackConfig_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(TrackConfig_cobj_required_num_bytes)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( config ),
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    return NS(TrackConfig_cobj_reserved_handle_size)( slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* NS(TrackConfig_preset)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT {
    if( config != SIXTRL_NULLPTR ) NS(TrackConfig_clear)( config );
    return config; }

SIXTRL_INLINE NS(status_type) NS(TrackConfig_clear)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT {
    return NS(TrackConfig_init)( config,
        NS(TrackConfig_default_x_min)(), NS(TrackConfig_default_x_max)(),
        NS(TrackConfig_default_y_min)(), NS(TrackConfig_default_y_max)(),
        NS(TrackConfig_default_check_aperture_at_drift)(),
        NS(TrackConfig_default_check_min_drift_length)() ); }

SIXTRL_INLINE NS(status_type) NS(TrackConfig_init)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(particle_real_type) const x_min, NS(particle_real_type) const x_max,
    NS(particle_real_type) const y_min, NS(particle_real_type) const y_max,
    NS(track_flags_type) const check_aperture_at_drift,
    NS(be_real_type) const check_min_drift_length ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    status |= NS(TrackConfig_set_x_min)( config, x_min );
    status |= NS(TrackConfig_set_x_max)( config, x_max );
    status |= NS(TrackConfig_set_y_min)( config, y_min );
    status |= NS(TrackConfig_set_y_max)( config, y_max );
    status |= NS(TrackConfig_set_check_aperture_at_drift)(
        config, check_aperture_at_drift );
    status |= NS(TrackConfig_set_check_min_drift_length)(
        config, check_min_drift_length );
    return status; }

SIXTRL_INLINE NS(particle_real_type) NS(TrackConfig_x_min)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( config != SIXTRL_NULLPTR ); return config->x_min; }

SIXTRL_INLINE NS(particle_real_type)
NS(TrackConfig_default_x_min)() SIXTRL_NOEXCEPT {
    return -( ( NS(particle_real_type) )SIXTRL_APERTURE_X_LIMIT ); }

SIXTRL_INLINE NS(status_type) NS(TrackConfig_set_x_min)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(particle_real_type) const x_min ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( config != SIXTRL_NULLPTR );
    config->x_min = x_min;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }


SIXTRL_INLINE NS(particle_real_type) NS(TrackConfig_x_max)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( config != SIXTRL_NULLPTR );
    return config->x_max; }

SIXTRL_INLINE NS(particle_real_type)
NS(TrackConfig_default_x_max)() SIXTRL_NOEXCEPT {
    return ( NS(particle_real_type) )SIXTRL_APERTURE_X_LIMIT; }

SIXTRL_INLINE NS(status_type) NS(TrackConfig_set_x_max)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(particle_real_type) const x_max ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( config != SIXTRL_NULLPTR );
    config->x_max = x_max;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE NS(particle_real_type) NS(TrackConfig_y_min)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( config != SIXTRL_NULLPTR );
    return config->y_min; }

SIXTRL_INLINE NS(particle_real_type) NS(TrackConfig_default_y_min)()
SIXTRL_NOEXCEPT { return -( ( NS(particle_real_type) )SIXTRL_APERTURE_Y_LIMIT ); }

SIXTRL_INLINE NS(status_type) NS(TrackConfig_set_y_min)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(particle_real_type) const y_min ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( config != SIXTRL_NULLPTR );
    config->y_min = y_min;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(particle_real_type) NS(TrackConfig_y_max)(
    SIXTRL_TRACK_ARGPTR_DEC  const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( config != SIXTRL_NULLPTR );
    return config->y_max;
}

SIXTRL_INLINE NS(particle_real_type) NS(TrackConfig_default_y_max)()
    SIXTRL_NOEXCEPT { return ( NS(particle_real_type) )SIXTRL_APERTURE_Y_LIMIT; }

SIXTRL_INLINE NS(status_type) NS(TrackConfig_set_y_max)(
    SIXTRL_TRACK_ARGPTR_DEC  NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(particle_real_type) const y_max ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( config != SIXTRL_NULLPTR );
    config->y_max = y_max;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(track_flags_type) NS(TrackConfig_check_aperture_at_drift)(
    SIXTRL_TRACK_ARGPTR_DEC  const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( config != SIXTRL_NULLPTR );
    return config->check_aperture_at_drift;
}

SIXTRL_INLINE NS(track_flags_type)
NS(TrackConfig_default_check_aperture_at_drift)( void ) SIXTRL_NOEXCEPT {
    return ( NS(track_flags_type) )SIXTRL_GLOBAL_APERTURE_CHECK_ALWAYS; }

SIXTRL_INLINE NS(status_type)
NS(TrackConfig_set_check_aperture_at_drift)(
    SIXTRL_TRACK_ARGPTR_DEC  NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_flags_type) const flag ) SIXTRL_NOEXCEPT {
    typedef NS(track_flags_type) flags_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( config != SIXTRL_NULLPTR ) &&
        ( ( flag == ( flags_type )SIXTRL_GLOBAL_APERTURE_CHECK_ALWAYS ) ||
          ( flag == ( flags_type )SIXTRL_GLOBAL_APERTURE_CHECK_CONDITIONAL ) ||
          ( flag == ( flags_type )SIXTRL_GLOBAL_APERTURE_CHECK_NEVER ) ) )
    {
        config->check_aperture_at_drift = flag;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(be_real_type) NS(TrackConfig_check_min_drift_length)(
    SIXTRL_TRACK_ARGPTR_DEC  const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( config != SIXTRL_NULLPTR );
    return config->check_min_drift_length; }

SIXTRL_INLINE NS(be_real_type) NS(TrackConfig_default_check_min_drift_length)(
    ) SIXTRL_NOEXCEPT { return (
        NS(be_real_type) )SIXTRL_APERTURE_CONDITIONAL_MIN_DRIFT_LENGTH; }

SIXTRL_INLINE NS(status_type) NS(TrackConfig_set_check_min_drift_length)(
    SIXTRL_TRACK_ARGPTR_DEC  NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(be_real_type) const min_drift_length ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( config != SIXTRL_NULLPTR ) &&
        ( min_drift_length >= ( NS(be_real_type) )0.0 ) )
    {
        config->check_min_drift_length = min_drift_length;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status;
}

SIXTRL_INLINE bool NS(TrackConfig_always_check_aperture_at_drift)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT {
    return ( ( config != SIXTRL_NULLPTR ) &&
             ( config->check_aperture_at_drift == ( NS(track_flags_type)
                 )SIXTRL_GLOBAL_APERTURE_CHECK_ALWAYS ) ); }

SIXTRL_INLINE bool NS(TrackConfig_never_check_aperture_at_drift)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT {
    return ( ( config != SIXTRL_NULLPTR ) &&
             ( config == ( NS(track_flags_type)
                 )SIXTRL_GLOBAL_APERTURE_CHECK_NEVER ) ); }

SIXTRL_INLINE bool NS(TrackConfig_conditional_check_aperture_at_drift)(
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT {
    return ( ( !NS(TrackConfig_always_check_aperture_at_drift)( config ) ) &&
             ( !NS(TrackConfig_never_check_aperture_at_drift)( config ) ) ); }

SIXTRL_INLINE bool NS(TrackConfig_is_consistent)( SIXTRL_TRACK_ARGPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT config ) SIXTRL_NOEXCEPT {
    bool is_consistent = false;
    if( config != SIXTRL_NULLPTR ) {
        is_consistent = (
            ( NS(TrackConfig_x_min)( config ) <=
              NS(TrackConfig_x_max)( config ) ) &&
            ( NS(TrackConfig_y_min)( config ) <=
              NS(TrackConfig_y_max)( config ) ) );
    }
    return is_consistent;
}

SIXTRL_INLINE NS(status_type) NS(TrackConfig_update)( SIXTRL_TRACK_ARGPTR_DEC
    NS(TrackConfig)* SIXTRL_RESTRICT config ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( config != SIXTRL_NULLPTR )
    {
        NS(be_real_type) const new_x_min =
            ( NS(TrackConfig_x_min)( config ) <=
              NS(TrackConfig_x_max)( config ) )
                ? NS(TrackConfig_x_min)( config )
                : NS(TrackConfig_x_max)( config );

        NS(be_real_type) const new_x_max =
            ( NS(TrackConfig_x_max)( config ) >=
              NS(TrackConfig_x_min)( config ) )
                ? NS(TrackConfig_x_max)( config )
                : NS(TrackConfig_x_min)( config );

        NS(be_real_type) const new_y_min =
            ( NS(TrackConfig_y_min)( config ) <=
              NS(TrackConfig_y_max)( config ) )
                ? NS(TrackConfig_y_min)( config )
                : NS(TrackConfig_y_max)( config );

        NS(be_real_type) const new_y_max =
            ( NS(TrackConfig_y_max)( config ) >=
              NS(TrackConfig_y_min)( config ) )
                ? NS(TrackConfig_y_max)( config )
                : NS(TrackConfig_y_min)( config );

        status = NS(TrackConfig_init)(
            config, new_x_min, new_x_max, new_y_min, new_y_max,
                NS(TrackConfig_check_aperture_at_drift)( config ),
                NS(TrackConfig_check_min_drift_length)( config ) );

        if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
            ( !NS(TrackConfig_is_consistent)( config ) ) )
        {
            status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
        }
    }
    return status;
}

SIXTRL_INLINE NS(status_type) NS(TrackConfig_copy)(
    SIXTRL_TRACK_ARGPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT dest,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        if( dest != src ) {
            status |= NS(TrackConfig_init)( dest,
                NS(TrackConfig_x_min)( src ), NS(TrackConfig_x_max)( src ),
                NS(TrackConfig_y_min)( src ), NS(TrackConfig_y_max)( src ),
                NS(TrackConfig_check_aperture_at_drift)( src ),
                NS(TrackConfig_check_min_drift_length)( src ) ); }
    }
    return status; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_track_config)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(TrackConfig_cobj_type_id)(), NS(TrackConfig_cobj_actual_handle_size)(
            ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_track_config)( obj ) )
        ? ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj
) SIXTRL_NOEXCEPT { return ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig)*
    )NS(TrackConfig_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(TrackConfig_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(TrackConfig_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(TrackConfig_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(TrackConfig_from_cobj_index)(
        NS(CBuffer_index_at)( buffer, idx ) ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_cobj_flat_buffer_save)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return ( ( pbuffer == SIXTRL_NULLPTR ) ||
        ( !NS(CObjFlatBuffer_has_cbuffer_structure)( pbuffer, 0, slot_size ) ) ||
        (  NS(CObjFlatBuffer_num_objects)( pbuffer, slot_size ) > idx ) )
        ? SIXTRL_NULLPTR
        : NS(TrackConfig_const_from_cobj_flat_buffer)( pbuffer, idx, slot_size );
}


#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_TRACK_TRACK_CONFIG_H__ */
