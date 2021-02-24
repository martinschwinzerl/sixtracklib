#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/track/cmp_elem_by_elem.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

NS(status_type) NS(Track_testlib_cmp_elem_by_elem_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const cmp_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const lattice_buffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT diff_buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_first_fail_idx,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) {
    return NS(Track_testlib_cmp_elem_by_elem_cbuffer)(
        track_pbuffer, cmp_pbuffer, lattice_buffer, rel_tolerance,
            abs_tolerance, diff_buffer, ptr_first_fail_idx, config );
}

NS(status_type) NS(Track_testlib_compare_elem_by_elem_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT cmp_pbuffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT
        ptr_first_fail_sequ_idx,
    SIXTRL_ARGPTR_DEC NS(particles_num_type)* SIXTRL_RESTRICT
        ptr_first_fail_pset_idx ) SIXTRL_NOEXCEPT
{
    return NS(Track_testlib_compare_elem_by_elem_cbuffer)( track_pbuffer,
        cmp_pbuffer, rel_tolerance, abs_tolerance, ptr_first_fail_sequ_idx,
            ptr_first_fail_pset_idx );
}
