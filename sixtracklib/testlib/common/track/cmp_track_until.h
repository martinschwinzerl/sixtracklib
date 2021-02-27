#ifndef SIXTRACKLIB_TESTLIB_COMMON_TRACK_TEST_CMP_TRACK_UNTIL_H__
#define SIXTRACKLIB_TESTLIB_COMMON_TRACK_TEST_CMP_TRACK_UNTIL_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

struct NS(TrackConfig);
struct NS(CBuffer);

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Track_testlib_until_turn_lattice_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT cmp_pbuffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT lattice_buffer,
    NS(cobj_size_type) const lattice_buffer_capacity,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT diff_buffer,
    NS(cobj_size_type) const diff_buffer_capacity,
    NS(particle_index_type) const until_turn,
    NS(particle_index_type) const line_start_at_element,
    NS(cobj_size_type) const line_start_index,
    SIXTRL_TRACK_ARGPTR_DEC const struct NS(TrackConfig) *const
        SIXTRL_RESTRICT config,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Track_testlib_compare_all_particle_sets_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT cmp_pbuffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT
        ptr_first_fail_pset_idx,
    SIXTRL_ARGPTR_DEC NS(particles_num_type)* SIXTRL_RESTRICT
        ptr_first_fail_particle_idx,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Track_testlib_until_turn_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT cmp_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT lattice_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT diff_buffer,
    NS(particle_index_type) const until_turn,
    NS(particle_index_type) const line_start_at_element,
    NS(cobj_size_type) const line_start_index,
    SIXTRL_TRACK_ARGPTR_DEC const struct NS(TrackConfig) *const
        SIXTRL_RESTRICT config ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Track_testlib_compare_all_particle_sets_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT cmp_pbuffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT
        ptr_first_fail_pset_idx,
    SIXTRL_ARGPTR_DEC NS(particles_num_type)* SIXTRL_RESTRICT
        ptr_first_fail_particle_idx ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type)
NS(Track_testlib_until_turn_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT cmp_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT lattice_buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT diff_buffer,
    NS(particle_index_type) const until_turn,
    NS(particle_index_type) const line_start_at_element,
    NS(cobj_size_type) const line_start_index,
    SIXTRL_TRACK_ARGPTR_DEC const struct NS(TrackConfig) *const
        SIXTRL_RESTRICT config ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type)
NS(Track_testlib_compare_all_particle_sets_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT cmp_pbuffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT
        ptr_first_fail_pset_idx,
    SIXTRL_ARGPTR_DEC NS(particles_num_type)* SIXTRL_RESTRICT
        ptr_first_fail_particle_idx ) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/particles/particles.h"
    #include "sixtracklib/common/beam_elements/all_beam_elements.h"
    #include "sixtracklib/common/track/track_config.h"
    #include "sixtracklib/common/track/track.h"
    #include "sixtracklib/testlib/common/particles/particles.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(status_type)
NS(Track_testlib_until_turn_lattice_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT cmp_pbuffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT lattice_buf,
    NS(cobj_size_type) const lbuf_capacity,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT diff_pbuffer,
    NS(cobj_size_type) const diff_buffer_capacity,
    NS(particle_index_type) const until_turn,
    NS(particle_index_type) const line_start_at_elem,
    NS(cobj_size_type) const line_start_index,
    SIXTRL_TRACK_ARGPTR_DEC const NS(TrackConfig) *const SIXTRL_RESTRICT config,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_t;
    typedef NS(particle_index_type) index_type;
    typedef NS(particles_num_type) npart_type;

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    bool has_diff_buffer = (
        ( diff_pbuffer != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_t )0u ) &&
        ( diff_buffer_capacity >
          NS(CObjFlatBuffer_min_buffer_size)( slot_size ) ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            diff_pbuffer, diff_buffer_capacity, slot_size ) ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( diff_pbuffer, slot_size ) ) );

    if( ( slot_size > ( st_size_t )0u ) && ( cmp_pbuffer != SIXTRL_NULLPTR ) &&
        ( track_pbuffer != SIXTRL_NULLPTR ) &&
        ( lattice_buf != SIXTRL_NULLPTR ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            track_pbuffer, 0u, slot_size ) ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( track_pbuffer, slot_size ) ) &&
        (  NS(CObjFlatBuffer_num_objects)( track_pbuffer, slot_size ) >
           ( st_size_t )0u ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            cmp_pbuffer, 0u, slot_size ) ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( cmp_pbuffer, slot_size ) ) &&
        ( NS(CObjFlatBuffer_num_objects)( cmp_pbuffer, slot_size ) ==
          NS(CObjFlatBuffer_num_objects)( track_pbuffer, slot_size ) ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            lattice_buf, lbuf_capacity, slot_size ) ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( lattice_buf, slot_size ) ) &&
        ( NS(CObjFlatBuffer_num_objects)( lattice_buf, slot_size ) >
          ( st_size_t )0u ) &&
        ( NS(CObjFlatBuffer_min_buffer_size)( slot_size ) <= lbuf_capacity ) )
    {
        st_size_t pset_idx = ( st_size_t )0u;
        st_size_t const num_psets = NS(CObjFlatBuffer_num_objects)(
            cmp_pbuffer, slot_size );

        st_size_t nelems_in_lattice = NS(CObjFlatBuffer_num_objects)(
            lattice_buf, slot_size );

        SIXTRL_ARGPTR_DEC st_size_t eot_idx = nelems_in_lattice;

        status =
        NS(EndTracking_terminate_lattice_with_eot_marker_cobj_flat_buffer)(
            lattice_buf, lbuf_capacity, slot_size, line_start_index,
                    line_start_at_elem, &eot_idx );

        if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        {
            return status;
        }

        nelems_in_lattice = NS(CObjFlatBuffer_num_objects)(
            lattice_buf, slot_size );

        SIXTRL_ASSERT( eot_idx < nelems_in_lattice );

        SIXTRL_ASSERT( eot_idx < NS(CObjFlatBuffer_num_objects)(
            lattice_buf, slot_size ) );

        SIXTRL_ASSERT( NS(EndTracking_lattice_contains_no_illegal_markers_cobj)(
            NS(CObjFlatBuffer_const_indices_begin)( lattice_buf, slot_size ),
                nelems_in_lattice, line_start_index, line_start_at_elem ) );

        SIXTRL_ASSERT( NS(EndTracking_is_legal_eot_marker_in_lattice_cobj)(
            NS(EndTracking_const_from_cobj_flat_buffer)( lattice_buf, eot_idx,
                slot_size ), eot_idx, nelems_in_lattice, line_start_index,
                    line_start_at_elem ) );

        SIXTRL_ASSERT( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS );

        has_diff_buffer &= (
            ( NS(CObjFlatBuffer_size)( track_pbuffer, slot_size ) <=
              diff_buffer_capacity ) &&
            ( ( NS(CObjFlatBuffer_num_objects)( diff_pbuffer, slot_size ) ==
                ( st_size_t )0u ) ||
              ( NS(CObjFlatBuffer_num_objects)( diff_pbuffer, slot_size ) ==
                NS(CObjFlatBuffer_num_objects)( track_pbuffer, slot_size ) ) ) );

        for( ; pset_idx < num_psets ; ++pset_idx )
        {
            st_size_t num_active_particles = ( st_size_t )0u;

            index_type start_at_elem = (
                index_type )SIXTRL_PARTICLE_ILLEGAL_AT_ELEMENT;

            index_type start_at_turn = (
                index_type )SIXTRL_PARTICLE_ILLEGAL_AT_TURN;

            SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* pset_track =
                NS(Particles_from_cobj_flat_buffer)(
                    track_pbuffer, pset_idx, slot_size );

            SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles) const* pset_cmp =
                NS(Particles_const_from_cobj_flat_buffer)(
                    cmp_pbuffer, pset_idx, slot_size );

            SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* pset_diff =
                ( has_diff_buffer )
                    ? NS(Particles_from_cobj_flat_buffer)(
                        diff_pbuffer, pset_idx, slot_size )
                    : SIXTRL_NULLPTR;

            npart_type ii = ( npart_type )0u;
            npart_type const NPART = NS(Particles_num_particles)( pset_cmp );

            if( pset_diff == SIXTRL_NULLPTR )
            {
                SIXTRL_ASSERT(
                    NS(CObjFlatBuffer_num_objects)( track_pbuffer, slot_size ) >
                    NS(CObjFlatBuffer_num_objects)( diff_pbuffer, slot_size ) );

                SIXTRL_ASSERT( pset_idx ==
                    NS(CObjFlatBuffer_num_objects)( diff_pbuffer, slot_size ) );

                pset_diff = NS(Particles_cobj_flat_buffer_new)(
                    diff_pbuffer, slot_size, NPART );
            }

            if( ( pset_cmp == SIXTRL_NULLPTR ) ||
                ( !( ( has_diff_buffer ) && ( pset_diff != SIXTRL_NULLPTR ) &&
                     ( NS(Particles_num_particles)( pset_diff ) == NPART ) ) ) ||
                ( pset_track == SIXTRL_NULLPTR ) || ( NPART < ii )  ||
                ( NPART != NS(Particles_num_particles)( pset_track ) ) )
            {
                status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                break;
            }

            SIXTRL_ASSERT( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS );
            SIXTRL_ASSERT( ( !has_diff_buffer ) ||
                ( NS(Particles_num_particles)( pset_diff ) == NPART ) );

            for( ; ii < NPART ; ++ii )
            {
                if( ( ( !NS(Particles_is_active)( pset_track, ii ) ) &&
                      (  NS(Particles_is_active)( pset_cmp, ii ) ) ) )
                {
                   status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                   break;
                }

                if( !NS(Particles_is_active)( pset_track, ii ) )
                {
                    continue;
                }

                if( NS(Particles_at_turn)( pset_cmp, ii ) <
                    NS(Particles_at_turn)( pset_track, ii ) )
                {
                   status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                   break;
                }

                SIXTRL_ASSERT( NS(Particles_at_element)( pset_track, ii ) >=
                    ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT );

                SIXTRL_ASSERT( NS(Particles_at_element)( pset_track, ii ) <=
                    ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT );

                SIXTRL_ASSERT( NS(Particles_at_turn)( pset_track, ii ) >=
                    ( index_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN );

                SIXTRL_ASSERT( NS(Particles_at_turn)( pset_track, ii ) <=
                    ( index_type )SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN );

                if( num_active_particles == ( st_size_t )0u )
                {
                    start_at_elem = NS(Particles_at_element)( pset_track, ii );
                    start_at_turn = NS(Particles_at_turn)( pset_track, ii );
                }

                if( start_at_elem != NS(Particles_at_element)( pset_track, ii ) )
                {
                    status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }

                if( start_at_turn != NS(Particles_at_turn)( pset_track, ii ) )
                {
                    status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }

                ++num_active_particles;
            }

            if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) break;

            if( num_active_particles == ( st_size_t )0u )
            {
                status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                break;
            }

            for( ii = ( npart_type )0u ; ii < NPART ; ++ii )
            {
                SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) p;
                status = NS(Particle_clear)( &p );
                status |= NS(Particles_to_single_particle)( pset_track, ii, &p );

                if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) break;

                st_size_t idx = NS(Track_particle_until_turn_eot_marker_cobj)(
                    &p, until_turn, NS(CObjFlatBuffer_const_indices_begin)(
                        lattice_buf, slot_size ), eot_idx, line_start_index,
                            line_start_at_elem, config );

                if( ( idx != line_start_index ) &&
                    ( NS(Particle_is_active)( &p ) ) )
                {
                    status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                }

                status |= NS(Particles_from_single_particle)(
                    pset_track, ii, &p );

                if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
                {
                    break;
                }
            }

            if( ( has_diff_buffer ) &&
                ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) )
            {
                status = NS(Particles_difference)(
                    pset_cmp, pset_track, pset_diff );
            }

            if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) break;
        }
    }

    return status;
}

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(Track_testlib_compare_all_particle_sets_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT cmp_pbuffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT
        ptr_first_fail_pset_idx,
    SIXTRL_ARGPTR_DEC NS(particles_num_type)* SIXTRL_RESTRICT
        ptr_first_fail_particle_idx,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_t;
    typedef NS(particles_num_type) npart_type;

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t first_fail_pset_idx = ( st_size_t )0u;
    npart_type first_fail_particle_idx = ( npart_type )0u;

    if( ( slot_size > ( st_size_t )0u ) && ( cmp_pbuffer != SIXTRL_NULLPTR ) &&
        ( track_pbuffer != SIXTRL_NULLPTR ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            track_pbuffer, 0u, slot_size ) ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( track_pbuffer, slot_size ) ) &&
        (  NS(CObjFlatBuffer_num_objects)( track_pbuffer, slot_size ) >
           ( st_size_t )0u ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            cmp_pbuffer, 0u, slot_size ) ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( cmp_pbuffer, slot_size ) ) &&
        ( NS(CObjFlatBuffer_num_objects)( cmp_pbuffer, slot_size ) ==
          NS(CObjFlatBuffer_num_objects)( track_pbuffer, slot_size ) ) )
    {
        st_size_t pset_idx = ( st_size_t )0u;
        st_size_t const num_psets = NS(CObjFlatBuffer_num_objects)(
            cmp_pbuffer, slot_size );

        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;

        for( ; pset_idx < num_psets ; ++pset_idx )
        {
            SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles) const* pset_track =
                NS(Particles_const_from_cobj_flat_buffer)( track_pbuffer,
                    pset_idx, slot_size );

            SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles) const* pset_cmp =
                NS(Particles_const_from_cobj_flat_buffer)( cmp_pbuffer,
                    pset_idx, slot_size );

            npart_type ii = ( npart_type )0u;
            npart_type const NPART = NS(Particles_num_particles)( pset_cmp );

            if( ( pset_cmp == SIXTRL_NULLPTR ) ||
                ( pset_track == SIXTRL_NULLPTR ) || ( ii > NPART ) ||
                ( NS(Particles_num_particles)( pset_track ) != NPART ) )
            {
                first_fail_pset_idx = pset_idx;
                status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                break;
            }

            for( ; ii < NPART ; ++ii )
            {
                SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) track_p;
                SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle) cmp_p;

                status  = NS(Particle_clear)( &track_p );
                status |= NS(Particles_to_single_particle)(
                    pset_track, ii, &track_p );

                status |= NS(Particle_clear)( &cmp_p );
                status |= NS(Particles_to_single_particle)(
                    pset_cmp, ii, &cmp_p );

                if( ( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) ||
                    ( 0 != NS(Particle_compare_with_tolerances)( &cmp_p,
                        &track_p, rel_tolerance, abs_tolerance ) ) )
                {
                    status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                    first_fail_pset_idx = pset_idx;
                    first_fail_particle_idx = ii;
                    break;
                }
            }
        }
    }

    if(  ptr_first_fail_pset_idx != SIXTRL_NULLPTR )
        *ptr_first_fail_pset_idx = first_fail_pset_idx;

    if(  ptr_first_fail_particle_idx != SIXTRL_NULLPTR )
        *ptr_first_fail_particle_idx = first_fail_particle_idx;

    return status;
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(status_type) NS(Track_testlib_until_turn_cbuffer)(
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
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( track_pbuffer != SIXTRL_NULLPTR ) &&
        ( cmp_pbuffer != SIXTRL_NULLPTR ) &&
        ( lattice_buffer != SIXTRL_NULLPTR ) &&
        ( NS(CBuffer_slot_size)( cmp_pbuffer ) ==
          NS(CBuffer_slot_size)( track_pbuffer ) ) &&
        ( NS(CBuffer_slot_size)( cmp_pbuffer ) ==
          NS(CBuffer_slot_size)( lattice_buffer ) ) &&
        ( ( diff_buffer == SIXTRL_NULLPTR ) ||
          ( NS(CBuffer_slot_size)( cmp_pbuffer ) ==
            NS(CBuffer_slot_size)( diff_buffer ) ) ) )
    {
        NS(cobj_size_type) diff_buffer_capacity = ( NS(cobj_size_type) )0u;
        SIXTRL_CBUFFER_DATAPTR_DEC unsigned char*
            diff_buffer_begin = SIXTRL_NULLPTR;

        if( ( diff_buffer != SIXTRL_NULLPTR ) &&
            ( NS(CBuffer_slot_size)( diff_buffer ) ==
              NS(CBuffer_slot_size)( cmp_pbuffer ) ) )
        {
            diff_buffer_begin = NS(CBuffer_p_base_begin)( diff_buffer );
            diff_buffer_capacity = NS(CBuffer_capacity)( diff_buffer );
        }

        status = NS(EndTracking_terminate_lattice_with_eot_marker_cbuffer)(
            lattice_buffer, line_start_index, line_start_at_element,
                SIXTRL_NULLPTR );

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        {
            status = NS(Track_testlib_until_turn_lattice_cobj_flat_buffer)(
                NS(CBuffer_p_base_begin)( track_pbuffer ),
                NS(CBuffer_p_const_base_begin)( cmp_pbuffer ),
                NS(CBuffer_p_base_begin)( lattice_buffer ),
                NS(CBuffer_capacity)( lattice_buffer ),
                diff_buffer_begin, diff_buffer_capacity, until_turn,
                line_start_at_element, line_start_index, config,
                NS(CBuffer_slot_size)( cmp_pbuffer ) );
        }
    }

    return status;
}

SIXTRL_INLINE NS(status_type)
NS(Track_testlib_compare_all_particle_sets_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const
        SIXTRL_RESTRICT track_pbuffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const
        SIXTRL_RESTRICT cmp_pbuffer,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT
        ptr_first_fail_pset_idx,
    SIXTRL_ARGPTR_DEC NS(particles_num_type)* SIXTRL_RESTRICT
        ptr_first_fail_particle_idx ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( track_pbuffer != SIXTRL_NULLPTR ) &&
        ( cmp_pbuffer != SIXTRL_NULLPTR ) &&
        ( NS(CBuffer_slot_size)( cmp_pbuffer ) ==
          NS(CBuffer_slot_size)( track_pbuffer ) ) )
    {
        status = NS(Track_testlib_compare_all_particle_sets_cobj_flat_buffer)(
            NS(CBuffer_p_const_base_begin)( track_pbuffer ),
            NS(CBuffer_p_const_base_begin)( cmp_pbuffer ),
            rel_tolerance, abs_tolerance,
            ptr_first_fail_pset_idx, ptr_first_fail_particle_idx,
            NS(CBuffer_slot_size)( cmp_pbuffer ) );
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_TRACK_TEST_CMP_TRACK_UNTIL_H__ */
