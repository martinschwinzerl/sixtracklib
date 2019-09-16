#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DIPEDGE_TRACK_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DIPEDGE_TRACK_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/track_particle.h"
    #include "sixtracklib/common/beam_elements/dipedge/dipedge.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, host */

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(Dipedge_track)(
    NS(TrackParticle)* SIXTRL_RESTRICT particles,
    const NS(DipoleEdge) *const SIXTRL_RESTRICT dipedge )
{
    SIXTRL_ASSERT( particle != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( dipedge  != SIXTRL_NULLPTR );

    particle->px += particle->x * dipedge->r21;
    particle->py += particle->y * dipedge->r43;

    return SIXTRL_TRACK_SUCCESS;
}

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DIPEDGE_TRACK_C99_H__ */
/* end: */
