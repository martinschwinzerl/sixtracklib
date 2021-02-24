#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/track/cmp_sixtrack.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

::NS(status_type) NS(Track_testlib_cmp_sequ_by_sequ_sixtrack_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const cmp_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const lattice_buffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT diff_buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_first_fail_idx,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) {
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::status_type status = st::STATUS_GENERAL_FAILURE;

    if( ( track_pbuffer  != nullptr ) && ( cmp_pbuffer != nullptr ) &&
        ( lattice_buffer != nullptr ) &&
        ( !::NS(CBuffer_needs_remapping)( cmp_pbuffer ) ) &&
        ( !::NS(CBuffer_needs_remapping)( lattice_buffer ) ) &&
        ( !::NS(CBuffer_needs_remapping)( track_pbuffer ) ) &&
        (  ::NS(CBuffer_num_objects)( cmp_pbuffer ) > 0u ) &&
        (  ::NS(CBuffer_num_objects)( lattice_buffer ) > 0 ) &&
        (  ::NS(CBuffer_slot_size)( lattice_buffer ) ==
           ::NS(CBuffer_slot_size)( cmp_pbuffer ) ) &&
        (  ::NS(CBuffer_slot_size)( track_pbuffer ) ==
           ::NS(CBuffer_slot_size)( cmp_pbuffer ) ) &&
        (  ::NS(CBuffer_size)( cmp_pbuffer ) <=
           ::NS(CBuffer_capacity)( track_pbuffer ) ) )
    {
        SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* diff_buffer_begin = nullptr;
        ::NS(cobj_size_type) diff_buffer_capacity = ::NS(cobj_size_type){ 0 };

        if( ( ( diff_buffer != nullptr ) &&
            ( !::NS(CBuffer_needs_remapping)( diff_buffer ) ) &&
            (  ::NS(CBuffer_slot_size)( diff_buffer ) ==
               ::NS(CBuffer_slot_size)( cmp_pbuffer ) ) &&
            (  ::NS(CBuffer_capacity)( diff_buffer ) >=
               ::NS(CBuffer_size)( cmp_pbuffer ) ) ) )
        {
            diff_buffer_begin = ::NS(CBuffer_p_base_begin)( diff_buffer );
            diff_buffer_capacity = ::NS(CBuffer_capacity)( diff_buffer );
        }

        status = ::NS(Track_testlib_cmp_sequ_by_sequ_sixtrack_cobj_flat_buffer)(
            ::NS(CBuffer_p_base_begin)( track_pbuffer ),
            ::NS(CBuffer_capacity)( track_pbuffer ),
            ::NS(CBuffer_p_const_base_begin)( cmp_pbuffer ),
            ::NS(CBuffer_p_const_base_begin)( lattice_buffer ),
            rel_tolerance, abs_tolerance, diff_buffer_begin,
            diff_buffer_capacity, ptr_first_fail_idx, config,
            ::NS(CBuffer_slot_size)( cmp_pbuffer ) );
    }

    return status;
}

#endif /* defined( __cplusplus ) */
