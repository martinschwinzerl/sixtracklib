#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/track/cmp_track_until.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

NS(status_type) NS(Track_testlib_until_turn_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const
        SIXTRL_RESTRICT cmp_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT lattice_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT diff_buffer,
    NS(particle_index_type) const until_turn,
    NS(particle_index_type) const line_start_at_element,
    NS(cobj_size_type) const line_start_index,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) SIXTRL_NOEXCEPT
{
    return NS(Track_testlib_until_turn_cbuffer)( track_pbuffer, cmp_pbuffer,
        lattice_buffer, diff_buffer, until_turn, line_start_at_element,
            line_start_index, config );
}

NS(status_type) NS(Track_testlib_compare_all_particle_sets_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT cmp_pbuffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT
        ptr_first_fail_pset_idx,
    SIXTRL_ARGPTR_DEC NS(particles_num_type)* SIXTRL_RESTRICT
        ptr_first_fail_particle_idx ) SIXTRL_NOEXCEPT {
    return NS(Track_testlib_compare_all_particle_sets_cbuffer)( track_pbuffer,
        cmp_pbuffer, rel_tolerance, abs_tolerance, ptr_first_fail_pset_idx,
            ptr_first_fail_particle_idx );
}
