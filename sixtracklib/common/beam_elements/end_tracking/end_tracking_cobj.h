#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_END_TRACKING_END_TRACKING_COBJ_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_END_TRACKING_END_TRACKING_COBJ_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/end_tracking/end_tracking.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

/* SIXTRL_CBUFFER_OBJ_DATAPTR_DEC */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(EndTracking_terminate_lattice_with_eot_marker_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT lattice_buffer,
    NS(cobj_size_type) const lattice_buffer_capacity,
    NS(cobj_size_type) const slot_size, NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_eot_marker_index
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(EndTracking_terminate_lattice_with_eot_marker_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT lattice_buffer,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_eot_marker_index
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN bool NS(EndTracking_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx,
    bool const ends_turn )  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(EndTracking_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx, bool const ends_turn  );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT orig );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(EndTracking_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx, bool const ends_turn );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cobj_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT elem );

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */


SIXTRL_INLINE NS(status_type)
NS(EndTracking_terminate_lattice_with_eot_marker_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT lattice_buffer,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_eot_marker_index
) SIXTRL_NOEXCEPT
{
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    st_size_t eot_idx = NS(CBuffer_num_objects)( lattice_buffer );

    if( ( lattice_buffer != SIXTRL_NULLPTR ) &&
        ( !NS(CBuffer_needs_remapping)( lattice_buffer ) ) &&
        ( line_start_index <= NS(CBuffer_num_objects)( lattice_buffer ) ) &&
        ( NS(CBuffer_num_objects)( lattice_buffer ) > ( st_size_t )0u ) &&
        ( NS(EndTracking_lattice_contains_no_illegal_markers_cobj)(
            NS(CBuffer_const_objects_begin)( lattice_buffer ),
            NS(CBuffer_num_objects)( lattice_buffer ), line_start_index,
                line_start_at_element ) ) )
    {
        SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* lattice =
            NS(CBuffer_const_objects_begin)( lattice_buffer );

        st_size_t nelems_in_lattice = NS(CBuffer_num_objects)( lattice_buffer );

        if( !NS(EndTracking_lattice_contains_no_illegal_markers_cobj)(
            NS(CBuffer_const_objects_begin)( lattice_buffer ), nelems_in_lattice,
                line_start_index, line_start_at_element ) )
        {
            if(  ptr_eot_marker_index != SIXTRL_NULLPTR )
                *ptr_eot_marker_index = nelems_in_lattice;

            return status;
        }

        eot_idx = NS(EndTracking_find_next_eot_marker_index_in_lattice_cobj)(
            lattice, nelems_in_lattice, line_start_index, line_start_at_element);

        if( eot_idx >= nelems_in_lattice )
        {
            eot_idx = nelems_in_lattice;

            SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* eot_marker =
                NS(EndTracking_cbuffer_add)( lattice_buffer,
                    line_start_at_element, line_start_index, true );

            if( eot_marker != SIXTRL_NULLPTR )
            {
                nelems_in_lattice = NS(CBuffer_num_objects)( lattice_buffer );

                SIXTRL_ASSERT( eot_marker == NS(EndTracking_const_from_cbuffer)(
                    lattice_buffer, eot_idx ) );

                SIXTRL_ASSERT( NS(EndTracking_is_legal_eot_marker_in_lattice_cobj)(
                    eot_marker, eot_idx, nelems_in_lattice, line_start_index,
                        line_start_at_element ) );

                SIXTRL_ASSERT( eot_idx ==
                    NS(EndTracking_find_next_eot_marker_index_in_lattice_cobj)(
                        NS(CBuffer_const_objects_begin)( lattice_buffer ),
                            nelems_in_lattice, line_start_index,
                                line_start_at_element ) );
            }
        }

        SIXTRL_ASSERT( NS(CBuffer_num_objects)(
            lattice_buffer ) == nelems_in_lattice );

        if( eot_idx < nelems_in_lattice )
        {
            SIXTRL_ASSERT(
                NS(EndTracking_lattice_contains_no_illegal_markers_cobj)(
                    NS(CBuffer_const_objects_begin)( lattice_buffer ),
                        nelems_in_lattice, line_start_index,
                            line_start_at_element ) );

            status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        }

        if( ptr_eot_marker_index != SIXTRL_NULLPTR )
        {
            *ptr_eot_marker_index = eot_idx;
        }
    }

    return status;
}

SIXTRL_INLINE NS(status_type)
NS(EndTracking_terminate_lattice_with_eot_marker_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT lattice_buffer,
    NS(cobj_size_type) const lbuffer_capacity,
    NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* ptr_eot_marker_index ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_t;

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t eot_idx = NS(CObjFlatBuffer_num_objects)(
        lattice_buffer, slot_size );

    if( ( lattice_buffer != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_t )0u ) &&
        ( lbuffer_capacity >= NS(CObjFlatBuffer_min_buffer_size)( slot_size ) ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            lattice_buffer, lbuffer_capacity, slot_size ) ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( lattice_buffer, slot_size ) ) &&
        (  NS(CObjFlatBuffer_size)( lattice_buffer, slot_size ) <=
           lbuffer_capacity ) &&
        ( NS(CObjFlatBuffer_num_objects)( lattice_buffer, slot_size ) >=
          line_start_index ) )
    {
        SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* lattice =
            NS(CObjFlatBuffer_const_indices_begin)( lattice_buffer, slot_size );

        st_size_t nelems_in_lattice = NS(CObjFlatBuffer_num_objects)(
            lattice_buffer, slot_size );

        eot_idx = nelems_in_lattice;

        if( !NS(EndTracking_lattice_contains_no_illegal_markers_cobj)(
                lattice, nelems_in_lattice, line_start_index,
                    line_start_at_element ) )
        {
            if(  ptr_eot_marker_index != SIXTRL_NULLPTR )
                *ptr_eot_marker_index = eot_idx;

            return status;
        }

        eot_idx = NS(EndTracking_find_next_eot_marker_index_in_lattice_cobj)(
            lattice, nelems_in_lattice, line_start_index,
                line_start_at_element );

        if( eot_idx >= nelems_in_lattice )
        {
            SIXTRL_ARGPTR_DEC st_size_t requ_n_slots = ( st_size_t )0u;
            SIXTRL_ARGPTR_DEC st_size_t requ_n_objs  = ( st_size_t )0u;
            SIXTRL_ARGPTR_DEC st_size_t requ_n_ptrs  = ( st_size_t )0u;
            SIXTRL_ARGPTR_DEC st_size_t requ_buffer_size = ( st_size_t )0u;

            if( ( !NS(EndTracking_cobj_flat_buffer_can_be_added)(
                    lattice_buffer, slot_size, &requ_buffer_size,
                        &requ_n_slots, &requ_n_objs, &requ_n_ptrs ) ) &&
                ( requ_buffer_size < lbuffer_capacity ) )
            {
                status = NS(CObjFlatBuffer_reallocate)( lattice_buffer,
                    lbuffer_capacity, slot_size, requ_n_slots, requ_n_objs,
                        requ_n_ptrs, NS(CObjFlatBuffer_num_garbage_ranges)(
                            lattice_buffer, slot_size ), &requ_buffer_size );

                SIXTRL_ASSERT(
                    ( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) ||
                    ( ( requ_buffer_size <= lbuffer_capacity ) &&
                      ( NS(EndTracking_cobj_flat_buffer_can_be_added)(
                          lattice_buffer, slot_size, SIXTRL_NULLPTR,
                            SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR ) ) )
                );

                status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( nelems_in_lattice == NS(CObjFlatBuffer_num_objects)(
                lattice_buffer, slot_size ) );

            if( NS(EndTracking_cobj_flat_buffer_can_be_added)( lattice_buffer,
                    slot_size, SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
                        SIXTRL_NULLPTR ) )
            {
                eot_idx = nelems_in_lattice;

                SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* eot_marker =
                    NS(EndTracking_cobj_flat_buffer_add)( lattice_buffer,
                        slot_size, line_start_at_element, line_start_index,
                            true );

                if( eot_marker != SIXTRL_NULLPTR )
                {
                    nelems_in_lattice = NS(CObjFlatBuffer_num_objects)(
                        lattice_buffer, slot_size );

                    SIXTRL_ASSERT( NS(EndTracking_const_from_cobj_flat_buffer)(
                        lattice_buffer, eot_idx, slot_size ) == eot_marker );

                    SIXTRL_ASSERT(
                        NS(EndTracking_is_legal_eot_marker_in_lattice_cobj)(
                            eot_marker, eot_idx, nelems_in_lattice,
                                line_start_index, line_start_at_element ) );

                    SIXTRL_ASSERT( eot_idx ==
                        NS(EndTracking_find_next_eot_marker_index_in_lattice_cobj)(
                            NS(CObjFlatBuffer_const_indices_begin)(
                                lattice_buffer, slot_size ),
                                    nelems_in_lattice, line_start_index,
                                        line_start_at_element ) );
                }
            }
        }

        SIXTRL_ASSERT( NS(CObjFlatBuffer_num_objects)(
            lattice_buffer, slot_size ) == nelems_in_lattice );

        if( eot_idx < nelems_in_lattice )
        {
            SIXTRL_ASSERT(
                NS(EndTracking_lattice_contains_no_illegal_markers_cobj)(
                    NS(CObjFlatBuffer_const_indices_begin)( lattice_buffer,
                        slot_size ), nelems_in_lattice, line_start_index,
                            line_start_at_element ) );

            status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        }

        if( ptr_eot_marker_index != SIXTRL_NULLPTR )
        {
            *ptr_eot_marker_index = eot_idx;
        }
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */


SIXTRL_INLINE bool NS(EndTracking_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_can_add_copy_of_trivial_object)( buffer, slot_size,
        NS(EndTracking_cobj_reserved_handle_size)( slot_size ),
            requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(EndTracking) elem;
    NS(EndTracking_clear)( &elem );
    return NS(EndTracking_cobj_flat_buffer_add_copy)( buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx,
    bool const ends_turn )  SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(EndTracking) elem;
    NS(EndTracking_init)( &elem, next_at_element, next_buffer_idx, ends_turn );
    return NS(EndTracking_cobj_flat_buffer_add_copy)( buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT {
    return NS(EndTracking_from_cobj_index)(
        NS(CObjFlatBuffer_add_copy_of_trivial_object)( buffer, slot_size, orig,
            NS(EndTracking_cobj_reserved_handle_size)( slot_size ),
            NS(EndTracking_cobj_type_id)(), false ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(EndTracking_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(CBuffer_can_add_copy_of_trivial_object)( b,
    NS(EndTracking_cobj_reserved_handle_size)( NS(CBuffer_slot_size)( b ) ),
        requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking) elem;
    NS(EndTracking_clear)( &elem );
    return NS(EndTracking_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx,
    bool const ends_turn  ) {
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking) elem;
    NS(EndTracking_init)( &elem, next_at_element, next_buffer_idx, ends_turn );
    return NS(EndTracking_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT orig ) {
    NS(cobj_size_type) const slot_size = NS(CBuffer_slot_size)( buffer );
    return NS(EndTracking_from_cobj_index)(
        NS(CBuffer_add_copy_of_trivial_object)( buffer, orig,
            NS(EndTracking_cobj_reserved_handle_size)( slot_size ),
            NS(EndTracking_cobj_type_id)(), false ) ); }

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_END_TRACKING_END_TRACKING_COBJ_H__  */
