#ifndef SIXTRACKLIB_COMMON_TRACK_TRACK_CONFIG_H__
#define SIXTRACKLIB_COMMON_TRACK_TRACK_CONFIG_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/generated/config.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

typedef struct NS(TrackConfig)
{
    NS(track_limit_t) m_global_aperture_check_min_x         SIXTRL_ALIGN( 8 );
    NS(track_limit_t) m_global_aperture_check_max_x         SIXTRL_ALIGN( 8 );
    NS(track_limit_t) m_global_aperture_check_min_y         SIXTRL_ALIGN( 8 );
    NS(track_limit_t) m_global_aperture_check_max_y         SIXTRL_ALIGN( 8 );
    NS(track_limit_t) m_global_aperture_check_min_length    SIXTRL_ALIGN( 8 );
    NS(track_config_flags_t) m_global_aperture_check_flags  SIXTRL_ALIGN( 8 );
    NS(track_config_flags_t) m_belem_group_flags_00         SIXTRL_ALIGN( 8 );
}
NS(TrackConfig);

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_preset)( SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
    SIXTRL_RESTRICT conf ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool
NS(TrackConfig_global_aperture_check_enabled)( SIXTRL_BUFFER_DATAPTR_DEC const
        NS(TrackConfig) *const SIXTRL_RESTRICT conf,
    NS(track_limit_t) const min_length ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(TrackConfig) TrackConfig;
}
#endif /* SIXTRL_BUFFER_DATAPTR_DEC */

/* ************************************************************************* */
/* ****                             implementation                     ***** */
/* ************************************************************************* */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
NS(TrackConfig_preset)( SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)*
    SIXTRL_RESTRICT conf ) SIXTRL_NOEXCEPT
{
    if( conf != SIXTRL_NULLPTR )
    {
        conf->m_global_aperture_check_min_x =
            ( NS(track_limit_t) )-SIXTRL_APERTURE_X_LIMIT;

        conf->m_global_aperture_check_min_y =
            ( NS(track_limit_t) )-SIXTRL_APERTURE_Y_LIMIT;

        conf->m_global_aperture_check_max_x =
            ( NS(track_limit_t) )SIXTRL_APERTURE_X_LIMIT;

        conf->m_global_aperture_check_max_y =
            ( NS(track_limit_t) )SIXTRL_APERTURE_Y_LIMIT;

        conf->m_global_aperture_check_min_length = ( NS(track_limit_t) )0;

        conf->m_global_aperture_check_flags =
            ( NS(track_config_flags_t) )SIXTRL_ENABLE_APERTURE_CHECK;

        conf->m_belem_group_flags_00 = ( NS(track_config_flags_t) )0;
    }

    return conf;
}

SIXTRL_INLINE bool NS(TrackConfig_global_aperture_check_enabled)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT conf,
    NS(track_limit_t) const elem_length ) SIXTRL_NOEXCEPT
{
    return ( ( conf != SIXTRL_NULLPTR ) &&
             ( conf->m_global_aperture_check_flags != 0 ) &&
             ( conf->m_global_aperture_check_min_length <= elem_length ) );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_TRACK_TRACK_CONFIG_H__ */
