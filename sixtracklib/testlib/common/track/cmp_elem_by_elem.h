#ifndef SIXTRACKLIB_TESTLIB_COMMON_TRACK_TEST_CMP_ELEM_BY_ELEM_H__
#define SIXTRACKLIB_TESTLIB_COMMON_TRACK_TEST_CMP_ELEM_BY_ELEM_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/particles/particles.h"
    #include "sixtracklib/common/beam_elements/all_beam_elements.h"
    #include "sixtracklib/common/track/track_config.h"
    #include "sixtracklib/common/track/track.h"

    #include "sixtracklib/testlib/common/particles/particle.h"
    #include "sixtracklib/testlib/common/particles/particles.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Track_testlib_elem_by_elem_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT track_pbuffer,
    NS(cobj_size_type) const track_pbuffer_capacity,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT cmp_pbuffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT lattice_buffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT diff_buffer,
    NS(cobj_size_type) const diff_buffer_capacity,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Track_testlib_compare_elem_by_elem_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT cmp_pbuffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT
        ptr_first_fail_sequ_idx,
    SIXTRL_ARGPTR_DEC NS(particles_num_type)* SIXTRL_RESTRICT
        ptr_first_fail_pset_idx,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Track_testlib_elem_by_elem_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const cmp_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const lattice_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT diff_buffer,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT config );

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Track_testlib_compare_elem_by_elem_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT cmp_pbuffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT
        ptr_first_fail_sequ_idx,
    SIXTRL_ARGPTR_DEC NS(particles_num_type)* SIXTRL_RESTRICT
        ptr_first_fail_pset_idx ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type)
NS(Track_testlib_elem_by_elem_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const cmp_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const lattice_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT diff_buffer,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const
        SIXTRL_RESTRICT config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type)
NS(Track_testlib_compare_elem_by_elem_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT cmp_pbuffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT
        ptr_first_fail_sequ_idx,
    SIXTRL_ARGPTR_DEC NS(particles_num_type)* SIXTRL_RESTRICT
        ptr_first_fail_pset_idx ) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

SIXTRL_INLINE NS(status_type) NS(Track_testlib_elem_by_elem_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* track_pbuffer,
    NS(cobj_size_type) const track_pbuffer_capacity,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT cmp_pbuffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT lattice_buffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT diff_buffer,
    NS(cobj_size_type) const diff_buffer_capacity,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_type) real_type;
    typedef NS(particle_index_type) index_type;

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( slot_size > ( NS(cobj_size_type) )0u ) &&
        ( track_pbuffer != SIXTRL_NULLPTR ) &&
        ( cmp_pbuffer != SIXTRL_NULLPTR ) &&
        ( lattice_buffer != SIXTRL_NULLPTR ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            track_pbuffer, track_pbuffer_capacity, slot_size ) ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            cmp_pbuffer, 0u, slot_size ) ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            lattice_buffer, 0u, slot_size ) ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( track_pbuffer, slot_size ) ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( cmp_pbuffer, slot_size ) ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( lattice_buffer, slot_size ) ) &&
        (  NS(CObjFlatBuffer_size)( cmp_pbuffer, slot_size ) <=
           track_pbuffer_capacity ) &&
        (  NS(CObjFlatBuffer_num_objects)( cmp_pbuffer, slot_size ) > 0u ) &&
        (  NS(CObjFlatBuffer_num_objects)( lattice_buffer, slot_size ) > 0u ) )
    {
        bool const has_diff_buffer = ( ( diff_buffer != SIXTRL_NULLPTR ) &&
            ( diff_buffer_capacity >= NS(CObjFlatBuffer_min_buffer_size)(
                slot_size ) ) &&
            ( diff_buffer_capacity >= NS(CObjFlatBuffer_size)(
                cmp_pbuffer, slot_size ) ) );

        NS(cobj_size_type) const NUM_SEQUENCES = NS(CObjFlatBuffer_num_objects)(
            cmp_pbuffer, slot_size );

        NS(cobj_size_type) const NUM_BEAM_ELEMENTS =
            NS(CObjFlatBuffer_num_objects)( lattice_buffer, slot_size );

        NS(cobj_size_type) ii = ( NS(cobj_size_type) )1u;

        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;

        for( ; ii < NUM_SEQUENCES ; ++ii )
        {
            SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* pset_a =
                NS(Particles_const_from_cobj_flat_buffer)( cmp_pbuffer,
                    ii - 1u, slot_size );

            SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* pset_b =
                NS(Particles_const_from_cobj_flat_buffer)( cmp_pbuffer,
                    ii, slot_size );

            NS(particles_num_type) jj = ( NS(particles_num_type) )0u;
            NS(particles_num_type) const NUM_PARTICLES =
                NS(Particles_num_particles)( pset_a );

            SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* pset_track =
                NS(Particles_cobj_flat_buffer_new)( track_pbuffer, slot_size,
                    NUM_PARTICLES );

            SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* pset_diff =
                ( has_diff_buffer )
                ? NS(Particles_cobj_flat_buffer_new)( diff_buffer, slot_size,
                    NUM_PARTICLES )
                : SIXTRL_NULLPTR;


            if( ( NUM_PARTICLES < jj ) || ( pset_track == SIXTRL_NULLPTR ) ||
                ( ( has_diff_buffer ) &&
                  ( ( pset_diff == SIXTRL_NULLPTR ) ||
                    ( NUM_PARTICLES != NS(Particles_num_particles)(
                        pset_diff ) ) ) ) ||
                ( NUM_PARTICLES != NS(Particles_num_particles)( pset_b ) ) ||
                ( NUM_PARTICLES != NS(Particles_num_particles)( pset_track ) ) )
            {
                status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                break;
            }

            status = NS(Particles_copy)( pset_track, pset_a );

            if( ( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) ||
                ( 0 != NS(Particles_compare_with_tolerances)(
                    pset_a, pset_track, ( real_type )0.0, ( real_type )0.0 ) ) )
            {
                status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                break;
            }

            for( ; jj < NUM_PARTICLES ; ++jj )
            {
                NS(cobj_size_type) start_obj_index   = NUM_BEAM_ELEMENTS + 1u;
                NS(cobj_size_type) end_obj_index     = start_obj_index;
                NS(cobj_size_type) cmp_end_obj_index = start_obj_index;

                SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) p;
                SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) cmp_p;

                status |= NS(Particle_clear)( &p );
                status |= NS(Particle_clear)( &cmp_p );

                status |= NS(Particles_to_single_particle)( pset_track, jj, &p );
                status |= NS(Particles_to_single_particle)( pset_b, jj, &cmp_p );

                if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
                {
                    break;
                }

                if( ( NS(Particle_at_element)( &cmp_p ) <
                      ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) ||
                    ( NS(Particle_at_element)( &cmp_p ) >
                      ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT ) ||
                    ( NS(Particle_at_turn)( &cmp_p ) <
                      ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) ||
                    ( NS(Particle_at_turn)( &cmp_p ) >
                      ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT ) ||
                    ( NS(Particle_at_element)( &p ) <
                      ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) ||
                    ( NS(Particle_at_element)( &p ) >
                      ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT ) ||
                    ( NS(Particle_at_turn)( &p ) <
                      ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) ||
                    ( NS(Particle_at_turn)( &p ) >
                      ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT ) )
                {
                    status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }

                if( ( ( NS(Particle_at_turn)( &p ) ==
                        NS(Particle_at_turn)( &cmp_p ) ) &&
                      ( NS(Particle_at_element)( &p ) >
                        NS(Particle_at_element)( &cmp_p ) ) ) ||
                    ( ( NS(Particle_at_turn)( &p ) <
                        NS(Particle_at_turn)( &cmp_p ) ) &&
                      ( ( NS(Particle_at_element)( &cmp_p ) != 0 ) ||
                        ( NS(Particle_at_turn)( &cmp_p ) !=
                          NS(Particle_at_turn)( &p ) + 1 ) ) ) )
                {
                    status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }

                start_obj_index = (
                    NS(cobj_size_type) )NS(Particle_at_element)( &p );

                bool const is_end_of_turn = ( NS(Particle_at_turn)( &cmp_p ) ==
                    ( NS(Particle_at_turn)( &p ) + ( index_type )1u ) );

                end_obj_index = ( !is_end_of_turn )
                    ? ( NS(cobj_size_type) )NS(Particle_at_element)( &cmp_p )
                    : start_obj_index + 1u;

                SIXTRL_ASSERT( start_obj_index <  NUM_BEAM_ELEMENTS );
                SIXTRL_ASSERT( end_obj_index   <= NUM_BEAM_ELEMENTS );

                SIXTRL_ASSERT( status == (
                    NS(status_type) )SIXTRL_STATUS_SUCCESS );

                cmp_end_obj_index =
                NS(Track_particle_over_line_or_until_end_of_turn_cobj)(
                    &p, NS(CObjFlatBuffer_const_indices_begin)(
                        lattice_buffer, slot_size ), start_obj_index,
                            end_obj_index, config );

                if( ( cmp_end_obj_index != end_obj_index ) ||
                    ( NS(Particle_is_active)( &p ) !=
                      NS(Particle_is_active)( &cmp_p ) ) )
                {
                    status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }

                if( ( is_end_of_turn ) && ( NS(Particle_is_active)( &p ) ) )
                {
                    NS(Particle_finish_turn)( &p,
                        NS(Particle_at_element)( &cmp_p ) );
                }

                if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
                {
                    status = NS(Particles_from_single_particle)(
                        pset_track, jj, &p );
                }

                if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) break;
            }

            if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
                ( has_diff_buffer ) )
            {
                SIXTRL_ASSERT( pset_diff != SIXTRL_NULLPTR );

                status = NS(Particles_difference)(
                    pset_b, pset_track, pset_diff );
            }

            if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) break;
        }
    }

    return status;
}

SIXTRL_INLINE NS(status_type)
NS(Track_testlib_compare_elem_by_elem_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT cmp_pbuffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT
        ptr_first_fail_sequ_idx,
    SIXTRL_ARGPTR_DEC NS(particles_num_type)* SIXTRL_RESTRICT
        ptr_first_fail_pset_idx,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( slot_size > ( NS(cobj_size_type) )0u ) &&
        ( track_pbuffer != SIXTRL_NULLPTR ) &&
        ( cmp_pbuffer != SIXTRL_NULLPTR ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            track_pbuffer, 0u, slot_size ) ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            cmp_pbuffer, 0u, slot_size ) ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( track_pbuffer, slot_size ) ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( cmp_pbuffer, slot_size ) ) &&
        (  NS(CObjFlatBuffer_num_objects)( cmp_pbuffer, slot_size ) > 0u ) &&
        (  NS(CObjFlatBuffer_num_objects)( track_pbuffer, slot_size ) + 1u ==
           NS(CObjFlatBuffer_num_objects)( cmp_pbuffer, slot_size ) ) )
    {
        NS(cobj_size_type) const NUM_SEQUENCES =
            NS(CObjFlatBuffer_num_objects)( cmp_pbuffer, slot_size );

        NS(cobj_size_type) first_fail_sequ_idx = NUM_SEQUENCES;

        NS(particles_num_type) first_fail_pset_idx = (
            NS(particles_num_type) )0u;

        NS(cobj_size_type) ii = ( NS(cobj_size_type) )1u;

        for( ; ii < NUM_SEQUENCES ; ++ii )
        {
            SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* pset_track =
                NS(Particles_const_from_cobj_flat_buffer)(
                    track_pbuffer, ii - 1u, slot_size );

            SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* pset_cmp =
                NS(Particles_const_from_cobj_flat_buffer)(
                    cmp_pbuffer, ii, slot_size );

            NS(particles_num_type) jj = ( NS(particles_num_type) )0u;

            NS(particles_num_type) const NPARTICLES =
                NS(Particles_num_particles)( pset_cmp );

            if( ( pset_cmp   == SIXTRL_NULLPTR ) ||
                ( pset_track == SIXTRL_NULLPTR ) ||
                ( pset_track == pset_cmp ) || ( NPARTICLES < jj ) ||
                ( NPARTICLES != NS(Particles_num_particles)( pset_track ) ) )
            {
                status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                break;
            }

            for( ; jj < NPARTICLES ; ++jj )
            {
                SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) p;
                SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) cmp_p;

                status  = NS(Particle_clear)( &p );
                status |= NS(Particle_clear)( &cmp_p );

                status |= NS(Particles_to_single_particle)(
                    pset_track, jj, &p );

                status |= NS(Particles_to_single_particle)(
                    pset_cmp, jj, &cmp_p );

                if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
                {
                    break;
                }

                if( 0 != NS(Particle_compare_with_tolerances)(
                        &cmp_p, &p, rel_tolerance, abs_tolerance ) )
                {
                    status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                    first_fail_sequ_idx = ii - 1u;
                    first_fail_pset_idx = jj;
                    break;
                }
            }

            if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) break;
        }

        if(  ptr_first_fail_sequ_idx != SIXTRL_NULLPTR )
            *ptr_first_fail_sequ_idx  = first_fail_sequ_idx;

        if(  ptr_first_fail_pset_idx != SIXTRL_NULLPTR )
            *ptr_first_fail_pset_idx  = first_fail_pset_idx;
    }

    return status;
}

SIXTRL_INLINE NS(status_type) NS(Track_testlib_elem_by_elem_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const cmp_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const lattice_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT diff_buffer,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config
) {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( track_pbuffer  != SIXTRL_NULLPTR ) &&
        ( cmp_pbuffer != SIXTRL_NULLPTR ) &&
        ( lattice_buffer != SIXTRL_NULLPTR ) &&
        ( !NS(CBuffer_needs_remapping)( cmp_pbuffer ) ) &&
        ( !NS(CBuffer_needs_remapping)( lattice_buffer ) ) &&
        ( !NS(CBuffer_needs_remapping)( track_pbuffer ) ) &&
        (  NS(CBuffer_num_objects)( cmp_pbuffer ) > 0u ) &&
        (  NS(CBuffer_num_objects)( lattice_buffer ) > 0u ) &&
        (  NS(CBuffer_slot_size)( lattice_buffer ) ==
           NS(CBuffer_slot_size)( cmp_pbuffer ) ) &&
        (  NS(CBuffer_slot_size)( track_pbuffer ) ==
           NS(CBuffer_slot_size)( cmp_pbuffer ) ) &&
        (  NS(CBuffer_size)( cmp_pbuffer ) <=
           NS(CBuffer_capacity)( track_pbuffer ) ) )
    {
        NS(cobj_size_type) diff_buffer_capacity = ( NS(cobj_size_type) )0u;
        SIXTRL_CBUFFER_DATAPTR_DEC unsigned char*
            diff_buffer_begin = SIXTRL_NULLPTR;

        if( ( ( diff_buffer != SIXTRL_NULLPTR ) &&
            ( !NS(CBuffer_needs_remapping)( diff_buffer ) ) &&
            (  NS(CBuffer_slot_size)( diff_buffer ) ==
               NS(CBuffer_slot_size)( cmp_pbuffer ) ) &&
            (  NS(CBuffer_capacity)( diff_buffer ) >=
               NS(CBuffer_size)( cmp_pbuffer ) ) ) )
        {
            diff_buffer_begin = NS(CBuffer_p_base_begin)( diff_buffer );
            diff_buffer_capacity = NS(CBuffer_capacity)( diff_buffer );
        }

        status = NS(Track_testlib_elem_by_elem_cobj_flat_buffer)(
            NS(CBuffer_p_base_begin)( track_pbuffer ),
            NS(CBuffer_capacity)( track_pbuffer ),
            NS(CBuffer_p_const_base_begin)( cmp_pbuffer ),
            NS(CBuffer_p_const_base_begin)( lattice_buffer ),
            diff_buffer_begin, diff_buffer_capacity, config,
            NS(CBuffer_slot_size)( cmp_pbuffer ) );
    }

    return status;
}

SIXTRL_INLINE NS(status_type)
NS(Track_testlib_compare_elem_by_elem_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT cmp_pbuffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT
        ptr_first_fail_sequ_idx,
    SIXTRL_ARGPTR_DEC NS(particles_num_type)* SIXTRL_RESTRICT
        ptr_first_fail_pset_idx ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( track_pbuffer  != SIXTRL_NULLPTR ) &&
        ( cmp_pbuffer    != SIXTRL_NULLPTR ) &&
        ( !NS(CBuffer_needs_remapping)( track_pbuffer ) ) &&
        ( !NS(CBuffer_needs_remapping)( cmp_pbuffer ) ) &&
        (  NS(CBuffer_num_objects)( cmp_pbuffer ) > 0u ) &&
        (  NS(CBuffer_num_objects)( track_pbuffer ) + 1u ==
           NS(CBuffer_num_objects)( cmp_pbuffer ) ) &&
        (  NS(CBuffer_slot_size)( track_pbuffer ) ==
           NS(CBuffer_slot_size)( cmp_pbuffer ) ) )
    {
        status = NS(Track_testlib_compare_elem_by_elem_cobj_flat_buffer)(
            NS(CBuffer_p_const_base_begin)( track_pbuffer ),
            NS(CBuffer_p_const_base_begin)( cmp_pbuffer ),
            rel_tolerance, abs_tolerance,
            ptr_first_fail_sequ_idx, ptr_first_fail_pset_idx,
            NS(CBuffer_slot_size)( cmp_pbuffer ) );
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_TRACK_TEST_CMP_ELEM_BY_ELEM_H__ */
