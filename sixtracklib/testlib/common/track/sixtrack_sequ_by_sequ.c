#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/track/sixtrack_sequ_by_sequ.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

NS(status_type) NS(Track_sixtrack_sequ_by_sequ_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const cmp_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const lattice_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT diff_buffer,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) {
    return NS(Track_sixtrack_sequ_by_sequ_cbuffer)(
        track_pbuffer, cmp_pbuffer, lattice_buffer, diff_buffer, config );
}
