#ifndef SIXTRACKL_COMMON_TRACK_TRACK_CONFIG_C99_H__
#define SIXTRACKL_COMMON_TRACK_TRACK_CONFIG_C99_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <math.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/generated/config.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
    #if !defined( _GPUCODE )
        #include "sixtracklib/common/buffer.h"
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

typedef enum NS(track_config_variant_dim_e)
{
    NS(TRACK_CONFIG_VARIANT_KERNEL_IMPL_FLAG_INDEX)             0,
    NS(TRACK_CONFIG_VARIANT_ENABLE_TRACK_MAPS_FLAG_INDEX)       1,
    NS(TRACK_CONFIG_VARIANT_GLOBAL_LIMIT_RECT_CHECK_FLAG_INDEX) 2,
    NS(TRACK_CONFIG_VARIANT_NUM_FLAGS)                          3
}
NS(track_config_variant_dim_t);


typedef struct NS(TrackConfigVariant)
{
    SIXTRL_UINT64_T flags[NS(TRACK_CONFIG_VARIANT_NUM_FLAGS)] SIXTRL_ALIGN( 8 );
}
NS(TrackConfigVariant);

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfigVariant)*
NS(TrackConfigVariant_preset)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfigVariant)* SIXTRL_RESTRICT var );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(track_conf_bitfield_t)
NS(TrackConfig_default_kernel_impl_flags)( void );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_feature_t)
NS(TrackConfig_default_track_bb4d)( void );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_feature_t)
NS(TrackConfig_default_track_bb6d)( void );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_feature_t)
NS(TrackConfig_default_track_sc_coasting)( void );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_feature_t)
NS(TrackConfig_default_track_sc_bunched)( void );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_feature_t)
NS(TrackConfig_default_track_tricub)( void );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_feature_t)
NS(TrackConfig_default_global_limit_rect_check)( void );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_real_t)
NS(TrackConfig_default_global_limit_rect_min_x)( void );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_real_t)
NS(TrackConfig_default_global_limit_rect_max_x)( void );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_real_t)
NS(TrackConfig_default_global_limit_rect_min_y)( void );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_real_t)
NS(TrackConfig_default_global_limit_rect_max_y)( void );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_real_t)
NS(TrackConfig_default_global_limit_rect_min_length)( void );

/* ------------------------------------------------------------------------- */

typedef SIXTRL_UINT64_T NS(track_conf_bitfield_t);
typedef SIXTRL_REAL_T   NS(track_conf_real_t);

typedef struct NS(TrackConfig)
{
    NS(TrackConfigVariant)    variant                       SIXTRL_ALIGN( 8 );
    NS(track_conf_bitfield_t) kernel_impl_flags             SIXTRL_ALIGN( 8 );

    NS(track_conf_feature_t)  track_bb4d                    SIXTRL_ALIGN( 8 );
    NS(track_conf_feature_t)  track_bb6d                    SIXTRL_ALIGN( 8 );
    NS(track_conf_feature_t)  track_sc_coasting             SIXTRL_ALIGN( 8 );
    NS(track_conf_feature_t)  track_sc_bunched              SIXTRL_ALIGN( 8 );
    NS(track_conf_feature_t)  track_tricub                  SIXTRL_ALIGN( 8 );

    NS(track_conf_feature_t)  global_limit_rect_check       SIXTRL_ALIGN( 8 );
    NS(track_conf_real_t)     global_limit_rect_min_x       SIXTRL_ALIGN( 8 );
    NS(track_conf_real_t)     global_limit_rect_max_x       SIXTRL_ALIGN( 8 );
    NS(track_conf_real_t)     global_limit_rect_min_y       SIXTRL_ALIGN( 8 );
    NS(track_conf_real_t)     global_limit_rect_max_y       SIXTRL_ALIGN( 8 );
    NS(track_conf_real_t)     global_limit_rect_min_length  SIXTRL_ALIGN( 8 );
}
NS(TrackConfig);

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_preset)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_clear)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT conf );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(object_type_id_t)
NS(TrackConfig_type_id)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT config );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(TrackConfig_num_dataptrs)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT config );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(TrackConfig_num_slots)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT interpol,
    NS(buffer_size_t) const slot_size );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfigVariant) const*
NS(TrackConfig_variant)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_bitfield_t)
NS(TrackConfig_kernel_impl_flags)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_feature_t) NS(TrackConfig_track_bb4d)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig)
        *const SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_feature_t) NS(TrackConfig_track_bb6d)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig)
        *const SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_feature_t)
NS(TrackConfig_track_sc_coasting)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_feature_t)
NS(TrackConfig_track_sc_bunched)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_feature_t)
NS(TrackConfig_track_tricub)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_feature_t)
NS(TrackConfig_global_limit_rect_check)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_real_t)
NS(TrackConfig_global_limit_rect_min_x)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_real_t)
NS(TrackConfig_global_limit_rect_max_x)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_real_t)
NS(TrackConfig_global_limit_rect_min_y)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_real_t)
NS(TrackConfig_global_limit_rect_max_y)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf );

SIXTRL_STATIC SIXTRL_FN NS(track_conf_real_t)
NS(TrackConfig_global_limit_rect_min_length)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_set_kernel_impl_flags)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_bitfield_t) const kernel_impl_flags );

SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_set_track_bb4d)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_feature_t) const track_bb4d );

SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_set_track_bb6d)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_feature_t) const track_bb6d );

SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_set_track_sc_coasting)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_feature_t) const track_sc_coasting );

SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_set_track_sc_bunched)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_feature_t) const track_sc_bunched );

SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_set_track_tricub)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_feature_t) const track_tricub );


SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_set_global_limit_rect_check)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_feature_t) const global_limit_rect_check );

SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_set_global_limit_rect_min_x)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_real_t) const global_limit_rect_min_x );

SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_set_global_limit_rect_max_x)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_real_t) const global_limit_rect_max_x );

SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_set_global_limit_rect_min_x)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_real_t) const global_limit_rect_min_y );

SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_set_global_limit_rect_max_x)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_real_t) const global_limit_rect_max_y );

SIXTRL_STATIC SIXTRL_FN void NS(TrackConfig_set_global_limit_rect_min_length)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_real_t) const global_limit_rect_min_length );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_from_obj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    NS(Object)* SIXTRL_RESTRICT obj );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(TrackConfig_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig)
        *const SIXTRL_RESTRICT interpol, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(TrackConfig_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig)
        *const SIXTRL_RESTRICT interpol, NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(TrackConfig_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig)
        *const SIXTRL_RESTRICT config );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_buffer)(
    SIXTRL_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_from_buffer)(
    SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(TrackConfig)*
NS(TrackConfig_create)( void );

SIXTRL_HOST_FN SIXTRL_HOST_FN NS(TrackConfig)*
NS(TrackConfig_new_from_variant)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfigVariant) *const SIXTRL_RESTRICT variant );

SIXTRL_HOST_FN SIXTRL_HOST_FN void NS(TrackConfig_delete)(
    NS(TrackConfig)* SIXTRL_RESTRICT config );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackConfig_update_variant)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackConfig_init_from_variant)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfigVariant) *const
        SIXTRL_RESTRICT variant );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackConfig_compiler_options_required_capacity)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT conf,
    SIXTRL_ARGTPR_DEC char const* SIXTRL_RESTRICT option_prefix );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackConfig_compiler_options)( SIXTRL_ARGPTR_DEC char* compiler_options_str,
    NS(buffer_size_t) const compiler_options_str_capacity,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT conf,
    SIXTRL_ARGTPR_DEC char const* SIXTRL_RESTRICT option_prefix );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackConfig_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
     NS(track_conf_bitfield_t) const kernel_impl_flags,
     NS(track_conf_feature_t) const track_bb4d,
     NS(track_conf_feature_t) const track_bb6d,
     NS(track_conf_feature_t) const track_sc_coasting,
     NS(track_conf_feature_t) const track_sc_bunched,
     NS(track_conf_feature_t) const track_tricub,
     NS(track_conf_feature_t) const global_limit_rect_check,
     NS(track_conf_real_t) const global_limit_rect_min_x,
     NS(track_conf_real_t) const global_limit_rect_max_x,
     NS(track_conf_real_t) const global_limit_rect_min_y,
     NS(track_conf_real_t) const global_limit_rect_max_y,
     NS(track_conf_real_t) const global_limit_rect_min_length );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT config );

#endif /* defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TrackConfig_copy)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig)
        *const SIXTRL_RESTRICT source );

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* */
/* ****                Implementation of Inline Methods                 **** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES)
    #if !defined( _GPUCODE )
        #include "sixtracklib/common/generated/config.h"
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_INCLUDES) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfigVariant)*
NS(TrackConfigVariant_preset)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfigVariant)* SIXTRL_RESTRICT var )
{
    if( var != SIXTRL_NULLPTR )
    {
        SIXTRL_INT64_T const nn =
            ( SIXTRL_INT64_T )NS(TRACK_CONFIG_VARIANT_NUM_FLAGS);

        SIXTRL_INT64_T ii = ( SIXTRL_INT64_T )0u;

        for( ; ii < nn ; ++ii )
        {
            var->flags[ ii ] = ( SIXTRL_UINT64_T )0u;
        }
    }

    return var;
}

/* ========================================================================= */

SIXTRL_INLINE NS(track_conf_bitfield_t)
NS(TrackConfig_default_kernel_impl_flags)( void )
{
    return ( NS(track_conf_bitfield_t) )0u;
}

SIXTRL_INLINE NS(track_conf_feature_t)
NS(TrackConfig_default_track_bb4d)( void )
{
    #if defined( SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_4D ) && !defined( _GPUCODE )
        #if SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_4D == SIXTRL_TRACK_MAP_ENABLED
        return NS(TRACK_MAP_ENABLED);

        #elif SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_4D == SIXTRL_TRACK_MAP_CONDITIONAL
        return NS(TRACK_MAP_CONDITIONAL);

        #elif SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_4D == SIXTRL_TRACK_MAP_DISABLED_SKIP
        return NS(TRACK_MAP_DISABLED_SKIP);

        #endif
    #endif /* defined( SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_4D ) */

    return NS(TRACK_MAP_DISABLED_ERROR);
}

SIXTRL_INLINE NS(track_conf_feature_t)
NS(TrackConfig_default_track_bb6d)( void )
{
    #if defined( SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_6D ) && !defined( _GPUCODE )
        #if SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_6D == SIXTRL_TRACK_MAP_ENABLED
        return NS(TRACK_MAP_ENABLED);

        #elif SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_6D == SIXTRL_TRACK_MAP_CONDITIONAL
        return NS(TRACK_MAP_CONDITIONAL);

        #elif SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_6D == SIXTRL_TRACK_MAP_DISABLED_SKIP
        return NS(TRACK_MAP_DISABLED_SKIP);

        #endif
    #endif /* defined( SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_6D ) */

    return NS(TRACK_MAP_DISABLED_ERROR);
}

SIXTRL_INLINE NS(track_conf_feature_t)
NS(TrackConfig_default_track_sc_coasting)( void )
{
    #if defined( SIXTRL_ENABLE_SPACE_CHARGE_COASTING ) && !defined( _GPUCODE )
        #if SIXTRL_ENABLE_SPACE_CHARGE_COASTING == SIXTRL_TRACK_MAP_ENABLED
        return NS(TRACK_MAP_ENABLED);

        #elif SIXTRL_ENABLE_SPACE_CHARGE_COASTING == SIXTRL_TRACK_MAP_CONDITIONAL
        return NS(TRACK_MAP_CONDITIONAL);

        #elif SIXTRL_ENABLE_SPACE_CHARGE_COASTING == SIXTRL_TRACK_MAP_DISABLED_SKIP
        return NS(TRACK_MAP_DISABLED_SKIP);

        #endif
    #endif /* defined( SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_6D ) */

    return NS(TRACK_MAP_DISABLED_ERROR);
}

SIXTRL_INLINE NS(track_conf_feature_t)
NS(TrackConfig_default_track_sc_bunched)( void )
{
    #if defined( SIXTRL_ENABLE_SPACE_CHARGE_BUNCHED ) && !defined( _GPUCODE )
        #if SIXTRL_ENABLE_SPACE_CHARGE_BUNCHED == SIXTRL_TRACK_MAP_ENABLED
        return NS(TRACK_MAP_ENABLED);

        #elif SIXTRL_ENABLE_SPACE_CHARGE_BUNCHED == SIXTRL_TRACK_MAP_CONDITIONAL
        return NS(TRACK_MAP_CONDITIONAL);

        #elif SIXTRL_ENABLE_SPACE_CHARGE_BUNCHED == SIXTRL_TRACK_MAP_DISABLED_SKIP
        return NS(TRACK_MAP_DISABLED_SKIP);

        #endif
    #endif /* defined( SIXTRL_ENABLE_SPACE_CHARGE_BUNCHED ) */

    return NS(TRACK_MAP_DISABLED_ERROR);
}

SIXTRL_INLINE NS(track_conf_feature_t)
NS(TrackConfig_default_track_tricub)( void )
{
    #if defined( SIXTRL_ENABLE_BE_TRICUB_MAP ) && !defined( _GPUCODE )
        #if SIXTRL_ENABLE_TRICUB == SIXTRL_TRACK_MAP_ENABLED
        return NS(TRACK_MAP_ENABLED);

        #elif SIXTRL_ENABLE_TRICUB == SIXTRL_TRACK_MAP_CONDITIONAL
        return NS(TRACK_MAP_CONDITIONAL);

        #elif SIXTRL_ENABLE_TRICUB == SIXTRL_TRACK_MAP_DISABLED_SKIP
        return NS(TRACK_MAP_DISABLED_SKIP);

        #endif
    #endif /* defined( SIXTRL_ENABLE_BE_TRICUB_MAP ) */

    return NS(TRACK_MAP_DISABLED_ERROR);
}

SIXTRL_INLINE NS(track_conf_feature_t)
NS(TrackConfig_default_global_limit_rect_check)( void )
{
    #if defined( SIXTRL_GLOBAL_LIMIT_RECT_CHECK ) && !defined( _GPUCODE )
        #if SIXTRL_GLOBAL_LIMIT_RECT_CHECK == SIXTRL_GLOBAL_LIMIT_RECT_CHECK_ALWAYS
        return NS(TRACK_MAP_ENABLED);

        #elif SIXTRL_GLOBAL_LIMIT_RECT_CHECK == SIXTRL_GLOBAL_LIMIT_RECT_CHECK_CONDITIONAL
        return NS(TRACK_MAP_CONDITIONAL);

        #elif SIXTRL_GLOBAL_LIMIT_RECT_CHECK == SIXTRL_GLOBAL_LIMIT_RECT_CHECK_NEVER
        return NS(TRACK_MAP_DISABLED_SKIP);

        #endif
    #endif /* defined( SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_6D ) */

    return NS(TRACK_MAP_DISABLED_ERROR);
}

SIXTRL_INLINE NS(track_conf_real_t)
NS(TrackConfig_default_global_limit_rect_min_x)( void )
{
    #if defined( SIXTRL_GLOBAL_LIMIT_RECT_MIN_X ) && !defined( _GPUCODE )
        return ( NS(track_conf_real_t) )SIXTRL_GLOBAL_LIMIT_RECT_MIN_X;
    #else
        return ( NS(track_conf_real_t) )-1.0;
}

SIXTRL_INLINE NS(track_conf_real_t)
NS(TrackConfig_default_global_limit_rect_max_x)( void )
{
    #if defined( SIXTRL_GLOBAL_LIMIT_RECT_MAX_X ) && !defined( _GPUCODE )
        return ( NS(track_conf_real_t) )SIXTRL_GLOBAL_LIMIT_RECT_MAX_X;
    #else
        return ( NS(track_conf_real_t) )1.0;
}

SIXTRL_INLINE NS(track_conf_real_t)
NS(TrackConfig_default_global_limit_rect_min_y)( void )
{
    #if defined( SIXTRL_GLOBAL_LIMIT_RECT_MIN_Y ) && !defined( _GPUCODE )
        return ( NS(track_conf_real_t) )SIXTRL_GLOBAL_LIMIT_RECT_MIN_Y;
    #else
        return ( NS(track_conf_real_t) )-1.0;
}

SIXTRL_INLINE NS(track_conf_real_t)
NS(TrackConfig_default_global_limit_rect_max_x)( void )
{
    #if defined( SIXTRL_GLOBAL_LIMIT_RECT_MAX_Y ) && !defined( _GPUCODE )
        return ( NS(track_conf_real_t) )SIXTRL_GLOBAL_LIMIT_RECT_MAX_Y;
    #else
        return ( NS(track_conf_real_t) )1.0;
}

SIXTRL_INLINE NS(track_conf_real_t)
NS(TrackConfig_default_global_limit_rect_min_length)( void )
{
    #if defined( SIXTRL_GLOBAL_LIMIT_RECT_MIN_LENGTH ) && !defined( _GPUCODE )
        return ( NS(track_conf_real_t) )SIXTRL_GLOBAL_LIMIT_RECT_MIN_LENGTH;
    #else
        return ( NS(track_conf_real_t) )0.0;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_preset)( SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
    SIXTRL_RESTRICT conf )
{
    if( conf != SIXTRL_NULLPTR )
    {
        NS(TrackConfig_clear)( conf );
    }

    return conf;
}

SIXTRL_INLINE void NS(TrackConfig_clear)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );

    NS(TrackConfigVariant_preset)( &conf->variant );
    conf->kernel_impl_flags = NS(TrackConfig_default_kernel_impl_flags)();

    conf->track_bb4d        = NS(TrackConfig_default_track_bb4d)();
    conf->track_bb6d        = NS(TrackConfig_default_track_bb6d)();
    conf->track_sc_coasting = NS(TrackConfig_default_track_sc_coasting)();
    conf->track_sc_bunched  = NS(TrackConfig_default_track_sc_bunched)();
    conf->track_tricub      = NS(TrackConfig_default_track_tricub)();

    conf->global_limit_rect_check =
        NS(TrackConfig_default_global_limit_rect_check)();

    conf->global_limit_rect_min_x =
        NS(TrackConfig_default_global_limit_rect_min_x)();

    conf->global_limit_rect_max_x =
        NS(TrackConfig_default_global_limit_rect_max_x)();

    conf->global_limit_rect_min_y =
        NS(TrackConfig_default_global_limit_rect_min_y)();

    conf->global_limit_rect_max_y =
        NS(TrackConfig_default_global_limit_rect_max_y)();

    conf->global_limit_rect_min_length =
        NS(TrackConfig_default_global_limit_rect_min_length)();
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(object_type_id_t)
NS(TrackConfig_type_id)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT config )
{
    ( void )config;
    return NS(OBJECT_TYPE_TRACK_CONFIG);
}

SIXTRL_INLINE NS(buffer_size_t)
NS(TrackConfig_num_dataptrs)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT config )
{
    ( void )config;
    return ( NS(buffer_size_t) )0u;
}

SIXTRL_INLINE NS(buffer_size_t)
NS(TrackConfig_num_slots)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT interpol,
    NS(buffer_size_t) const slot_size )
{
    ( void )config;
    return NS(ManagedBuffer_get_slot_based_length)(
        sizeof( NS(TrackConfig) ), slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfigVariant) const*
NS(TrackConfig_variant)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return &conf->variant;
}

SIXTRL_INLINE NS(track_conf_bitfield_t)
NS(TrackConfig_kernel_impl_flags)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return conf->kernel_impl_flags;
}


SIXTRL_INLINE NS(track_conf_feature_t) NS(TrackConfig_track_bb4d)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig)
        *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return conf->track_bb4d;
}

SIXTRL_INLINE NS(track_conf_feature_t) NS(TrackConfig_track_bb6d)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig)
        *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return conf->track_bb6d;
}

SIXTRL_INLINE NS(track_conf_feature_t)
NS(TrackConfig_track_sc_coasting)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return conf->track_sc_coasting;
}

SIXTRL_INLINE NS(track_conf_feature_t)
NS(TrackConfig_track_sc_bunched)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return conf->track_sc_bunched;
}

SIXTRL_INLINE NS(track_conf_feature_t)
NS(TrackConfig_track_tricub)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return conf->track_tricub;
}

SIXTRL_INLINE NS(track_conf_feature_t)
NS(TrackConfig_global_limit_rect_check)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return conf->global_limit_rect_check;
}

SIXTRL_INLINE NS(track_conf_real_t)
NS(TrackConfig_global_limit_rect_min_x)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return conf->global_limit_rect_min_x;
}

SIXTRL_INLINE NS(track_conf_real_t)
NS(TrackConfig_global_limit_rect_max_x)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return conf->global_limit_rect_max_x;
}

SIXTRL_INLINE NS(track_conf_real_t)
NS(TrackConfig_global_limit_rect_min_y)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return conf->global_limit_rect_min_y;
}

SIXTRL_INLINE NS(track_conf_real_t)
NS(TrackConfig_global_limit_rect_max_y)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return conf->global_limit_rect_max_y;
}

SIXTRL_INLINE NS(track_conf_real_t)
NS(TrackConfig_global_limit_rect_min_length)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(TrackConfig) *const SIXTRL_RESTRICT conf )
{
    SIXTRL_ASSERT( conf != SIXTRL_NULLPTR );
    return conf->global_limit_rect_min_length;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(TrackConfig_set_kernel_impl_flags)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_bitfield_t) const kernel_impl_flags )
{
    if( conf != SIXTRL_NULLPTR ) conf->kernel_impl_flags = kernel_impl_flags;
}

SIXTRL_INLINE void NS(TrackConfig_set_track_bb4d)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_feature_t) const track_bb4d )
{
    if( conf != SIXTRL_NULLPTR ) conf->track_bb4d = track_bb4d;
}

SIXTRL_INLINE void NS(TrackConfig_set_track_bb6d)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_feature_t) const track_bb6d )
{
    if( conf != SIXTRL_NULLPTR ) conf->track_bb6d = track_bb6d;
}

SIXTRL_INLINE void NS(TrackConfig_set_track_sc_coasting)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_feature_t) const track_sc_coasting )
{
    if( conf != SIXTRL_NULLPTR ) conf->track_sc_coasting = track_sc_coasting;
}

SIXTRL_INLINE void NS(TrackConfig_set_track_sc_bunched)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_feature_t) const track_sc_bunched )
{
    if( conf != SIXTRL_NULLPTR ) conf->track_sc_bunched = track_sc_bunched;
}

SIXTRL_INLINE void NS(TrackConfig_set_track_tricub)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_feature_t) const track_tricub )
{
    if( conf != SIXTRL_NULLPTR ) conf->track_tricub = track_tricub;
}


SIXTRL_INLINE void NS(TrackConfig_set_global_limit_rect_check)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config
    NS(track_conf_feature_t) const global_limit_rect_check )
{
    if( conf != SIXTRL_NULLPTR )
        conf->global_limit_rect_check = global_limit_rect_check;
}

SIXTRL_INLINE void NS(TrackConfig_set_global_limit_rect_min_x)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_real_t) const global_limit_rect_min_x )
{
    if( conf != SIXTRL_NULLPTR )
        conf->global_limit_rect_min_x = global_limit_rect_min_x;
}

SIXTRL_INLINE void NS(TrackConfig_set_global_limit_rect_max_x)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_real_t) const global_limit_rect_max_x )

{
    if( conf != SIXTRL_NULLPTR )
        conf->global_limit_rect_max_x = global_limit_rect_max_x;
}

SIXTRL_INLINE void NS(TrackConfig_set_global_limit_rect_min_y)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_real_t) const global_limit_rect_min_y )
{
    if( conf != SIXTRL_NULLPTR )
        conf->global_limit_rect_min_y = global_limit_rect_min_y;
}

SIXTRL_INLINE void NS(TrackConfig_set_global_limit_rect_max_x)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_real_t) const global_limit_rect_max_y )
{
    if( conf != SIXTRL_NULLPTR )
        conf->global_limit_rect_max_y = global_limit_rect_max_y;
}

SIXTRL_INLINE void NS(TrackConfig_set_global_limit_rect_min_length)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    NS(track_conf_real_t) const global_limit_rect_min_length )
{
    if( conf != SIXTRL_NULLPTR )
        conf->global_limit_rect_min_length = global_limit_rect_min_length;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_obj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT obj )
{
    return (
        ( NS(Object_get_type_id)( obj ) == NS(OBJECT_TYPE_TRACK_CONFIG) ) &&
        ( NS(Object_get_size)( obj ) >= sizeof( NS(TrackConfig) ) ) )
        ? ( SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig) const* )(
            uintptr_t )NS(Object_get_begin_addr)( obj )
        : SIXTRL_NULLPTR;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_from_obj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC
    NS(Object)* SIXTRL_RESTRICT obj )
{
    return ( SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
        )NS(TrackConfig_const_from_obj_index)( obj );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig) const*
NS(TrackConfig_const_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(TrackConfig_const_from_obj_index)(
        NS(ManagedBuffer_get_const_object)( buffer, index, slot_size ) );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_from_managed_buffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const index, NS(buffer_size_t) const slot_size )
{
    return NS(TrackConfig_from_obj_index)(
        NS(ManagedBuffer_const_object)( buffer, index, slot_size ) );
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(arch_status_t) NS(TrackConfig_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig)
        *const SIXTRL_RESTRICT config, NS(buffer_size_t) const slot_size )
{
    SIXTRL_ASSERT( NS(TrackConfig_num_dataptrs)( config ) ==
        ( NS(buffer_size_t) )0u );

    ( void )config;
    return NS(Buffer_set_attr_arrays_for_trivial_object)(
        offsets_begin, max_num_offsets, slot_size );
}

SIXTRL_INLINE NS(arch_status_t) NS(TrackConfig_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig)
        *const SIXTRL_RESTRICT config, NS(buffer_size_t) const slot_size )
{
    SIXTRL_ASSERT( NS(TrackConfig_num_dataptrs)( config ) ==
        ( NS(buffer_size_t) )0u );

    ( void )config;
    return NS(Buffer_set_attr_arrays_for_trivial_object)(
        sizes_begin, max_num_sizes, slot_size );
}

SIXTRL_INLINE NS(arch_status_t) NS(TrackConfig_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig)
        *const SIXTRL_RESTRICT config )
{
    SIXTRL_ASSERT( NS(TrackConfig_num_dataptrs)( config ) ==
        ( NS(buffer_size_t) )0u );

    ( void )config;
    return NS(Buffer_set_attr_arrays_for_trivial_object)(
        counts_begin, max_num_counts, SIXTRL_BUFFER_DEFAULT_SLOT_SIZE );
}

SIXTRL_INLINE NS(arch_status_t) NS(TrackConfig_copy)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT dest,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig)
        *const SIXTRL_RESTRICT source )
{
    NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) )
    {
        if( dest != src )
        {
            NS(TrackConfig_set_kernel_impl_flags)( dest,
                NS(TrackConfig_kernel_impl_flags)( src ) );

            NS(TrackConfig_set_track_bb4d)( dest,
                NS(TrackConfig_track_bb4d)( src ) );

            NS(TrackConfig_set_track_bb6d)( dest,
                NS(TrackConfig_track_bb6d)( src ) );

            NS(TrackConfig_set_track_sc_coasting)( dest,
                NS(TrackConfig_track_sc_coasting)( src ) );

            NS(TrackConfig_set_track_sc_bunched)( dest,
                NS(TrackConfig_track_sc_bunched)( src ) );

            NS(TrackConfig_set_track_tricub)( dest,
                NS(TrackConfig_track_tricub)( src ) );

            NS(TrackConfig_set_global_limit_rect_check)( dest,
                NS(TrackConfig_global_limit_rect_check)( src ) );

            NS(TrackConfig_set_global_limit_rect_min_x)( dest,
                NS(TrackConfig_global_limit_rect_min_x)( src ) );

            NS(TrackConfig_set_global_limit_rect_max_x)( dest,
                NS(TrackConfig_global_limit_rect_max_x)( src ) );

            NS(TrackConfig_set_global_limit_rect_min_y)( dest,
                NS(TrackConfig_global_limit_rect_min_y)( src ) );

            NS(TrackConfig_set_global_limit_rect_max_y)( dest,
                NS(TrackConfig_global_limit_rect_max_y)( src ) );

            NS(TrackConfig_set_global_limit_rect_min_length)( dest,
                NS(TrackConfig_global_limit_rect_min_length)( src ) );

            status = NS(TrackConfig_update_variant)( dest );
        }
    }

    return status;
}

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKL_COMMON_TRACK_TRACK_CONFIG_C99_H__ */
