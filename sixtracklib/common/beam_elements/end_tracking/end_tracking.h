#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_END_TRACKING_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_END_TRACKING_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

struct NS(CObjIndex);
struct NS(CBuffer);

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(EndTracking)
{
    NS(particle_index_type) next_at_element SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(size_type)           next_buffer_idx SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_flags_type)       ends_turn       SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(EndTracking);

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(EndTracking_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(EndTracking_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(EndTracking_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(EndTracking_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(EndTracking_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT elem,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_preset)( SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(EndTracking_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(EndTracking_init)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT elem,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx, bool const ends_turn
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(EndTracking_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT source
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type)
NS(EndTracking_next_at_element)( SIXTRL_BE_ARGPTR_DEC const NS(EndTracking)
    *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_type)
NS(EndTracking_default_next_at_element)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(EndTracking_set_next_at_element)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT elem,
    NS(particle_index_type) const next_at_element ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(EndTracking_next_buffer_idx)(
    SIXTRL_BE_ARGPTR_DEC  const NS(EndTracking) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(EndTracking_default_next_buffer_idx)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(EndTracking_set_next_buffer_idx)(
    SIXTRL_BE_ARGPTR_DEC  NS(EndTracking)* SIXTRL_RESTRICT elem,
    NS(size_type) const next_buffer_idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN bool NS(EndTracking_ends_turn)(
    SIXTRL_BE_ARGPTR_DEC  const NS(EndTracking) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(EndTracking_default_ends_turn)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(EndTracking_set_ends_turn)(
    SIXTRL_BE_ARGPTR_DEC  NS(EndTracking)* SIXTRL_RESTRICT elem,
    bool const ends_turn ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(EndTracking_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const
        SIXTRL_RESTRICT source ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(EndTracking_is_legal_marker_in_lattice_cobj)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT marker,
    NS(size_type) const marker_index, NS(size_type) const num_elems_in_lattice,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(EndTracking_is_legal_eot_marker_in_lattice_cobj)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT marker,
    NS(size_type) const eot_marker_index, NS(size_type) const nelems_in_lattice,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(EndTracking_find_next_eot_marker_index_in_lattice_cobj)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const*
        SIXTRL_RESTRICT lattice_begin,
    NS(size_type) const num_elements_in_lattice,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool
NS(EndTracking_lattice_contains_no_illegal_markers_cobj)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const*
        SIXTRL_RESTRICT lattice_begin,
    NS(size_type) const num_elements_in_lattice,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(EndTracking_num_legal_markers_in_lattice_cobj)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const*
        SIXTRL_RESTRICT lattice_begin,
    NS(size_type) const num_elements_in_lattice,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(EndTracking_get_legal_marker_indices_from_lattice_cobj)(
    NS(size_type) const max_num_indices,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT indices_begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const*
        SIXTRL_RESTRICT lattice_begin,
    NS(size_type) const num_elements_in_lattice,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type)
NS(EndTracking_terminate_lattice_with_eot_marker_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT lattice_buffer,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_element,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_eot_marker_index
) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_end_tracking)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    struct NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(EndTracking_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(EndTracking_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(EndTracking_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(EndTracking_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(EndTracking_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT elem,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_preset_ext)( SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(EndTracking_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */
#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsStoreResultTypeTraits< ::NS(EndTracking) >
    {
        typedef ::NS(EndTracking) value_type;
        typedef SIXTRL_BE_ARGPTR_DEC value_type const* const_pointer;
        typedef SIXTRL_BE_ARGPTR_DEC value_type* pointer;
    };

    template<> struct CObjectsTraits< ::NS(EndTracking) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_END_TRACKING;
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_END_TRACKING > {
            typedef ::NS(EndTracking) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* ************************************************************************* */
/* *****          Implementation of C inline functions                   *** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE )
    #include "sixtracklib/common/beam_elements/end_tracking/end_tracking_cobj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(EndTracking_cobj_type_id)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_obj_id_type)
        )SIXTRL_COBJECTS_TYPE_ID_END_TRACKING; }

SIXTRL_INLINE NS(cobj_size_type) NS(EndTracking_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(EndTracking_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(EndTracking) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(EndTracking_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(EndTracking_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(EndTracking_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return NS(EndTracking_cobj_reserved_handle_size)( slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* NS(EndTracking_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    if( elem != SIXTRL_NULLPTR ) NS(EndTracking_clear)( elem );
    return elem;
}

SIXTRL_INLINE NS(status_type) NS(EndTracking_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    return NS(EndTracking_init)( elem,
        NS(EndTracking_default_next_at_element)(),
        NS(EndTracking_default_next_buffer_idx)(),
        NS(EndTracking_default_ends_turn)() ); }

SIXTRL_INLINE NS(status_type) NS(EndTracking_init)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT elem,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx, bool const ends_turn ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    status |= NS(EndTracking_set_next_at_element)( elem, next_at_element );
    status |= NS(EndTracking_set_next_buffer_idx)( elem, next_buffer_idx );
    status |= NS(EndTracking_set_ends_turn)( elem, ends_turn );
    return status; }

SIXTRL_INLINE NS(particle_index_type) NS(EndTracking_next_at_element)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return elem->next_at_element; }

SIXTRL_INLINE NS(particle_index_type) NS(EndTracking_default_next_at_element)(
    ) SIXTRL_NOEXCEPT { return ( NS(particle_index_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(EndTracking_set_next_at_element)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT elem,
    NS(particle_index_type) const next_at_element ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( next_at_element >= (
        NS(particle_index_type) )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT );
    SIXTRL_ASSERT( next_at_element <= (
        NS(particle_index_type) )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT );
    elem->next_at_element = next_at_element;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }


SIXTRL_INLINE NS(size_type) NS(EndTracking_next_buffer_idx)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return elem->next_buffer_idx; }

SIXTRL_INLINE NS(size_type) NS(EndTracking_default_next_buffer_idx)(
    ) SIXTRL_NOEXCEPT { return ( NS(particle_index_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(EndTracking_set_next_buffer_idx)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT elem,
    NS(size_type) const next_buffer_idx ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->next_buffer_idx = next_buffer_idx;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }


SIXTRL_INLINE bool NS(EndTracking_ends_turn)( SIXTRL_BE_ARGPTR_DEC const
    NS(EndTracking) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    return ( elem->ends_turn == ( NS(be_flags_type) )1 ); }

SIXTRL_INLINE bool NS(EndTracking_default_ends_turn)() SIXTRL_NOEXCEPT {
    return true; }

SIXTRL_INLINE NS(status_type) NS(EndTracking_set_ends_turn)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT elem,
    bool const ends_turn ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->ends_turn = ( ends_turn )
        ? ( NS(be_flags_type) )1 : ( NS(be_flags_type) )0;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE NS(status_type) NS(EndTracking_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        if( dest != src )
        {
            status |= NS(EndTracking_set_next_at_element)( dest,
                          NS(EndTracking_next_at_element)( src ) );
            status |= NS(EndTracking_set_next_buffer_idx)( dest,
                          NS(EndTracking_next_buffer_idx)( src ) );
            status |= NS(EndTracking_set_ends_turn)( dest,
                          NS(EndTracking_ends_turn)( src ) );
        }
    }
    return status; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(EndTracking_is_legal_marker_in_lattice_cobj)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT m,
    NS(size_type) const marker_index,
    NS(size_type) const nelem_in_lattice, NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_elem ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_index_type) index_type;

    bool is_legal = false;

    if( ( m != SIXTRL_NULLPTR ) && ( marker_index >= line_start_index ) &&
        ( marker_index < nelem_in_lattice ) &&
        ( line_start_at_elem >= (
            index_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) &&
        ( line_start_at_elem + ( index_type )(
            nelem_in_lattice - line_start_index ) < ( index_type
                )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT ) )
    {
        is_legal  = ( NS(EndTracking_next_buffer_idx)( m ) < nelem_in_lattice );
        is_legal &= ( NS(EndTracking_next_at_element)( m ) < (
            line_start_at_elem +  ( index_type )( nelem_in_lattice -
                line_start_index ) ) );

        if( ( is_legal ) && ( NS(EndTracking_ends_turn)( m ) ) )
        {
            is_legal &= ( NS(EndTracking_next_buffer_idx)( m ) >=
                          line_start_index );

            is_legal &= ( NS(EndTracking_next_at_element)( m ) >=
                          line_start_at_elem );

            is_legal &= ( NS(EndTracking_next_buffer_idx)( m ) != marker_index );

            is_legal &= (
                ( NS(EndTracking_next_buffer_idx)( m ) - line_start_index ) ==
                ( NS(size_type) )( NS(EndTracking_next_at_element)( m ) -
                                   line_start_at_elem ) );
        }
        else if( is_legal )
        {
            is_legal &= ( NS(EndTracking_next_buffer_idx)( m ) > marker_index );
            is_legal &= ( NS(EndTracking_next_at_element)( m ) >
                ( index_type )( line_start_at_elem + (
                    marker_index - line_start_index ) ) );
        }
    }

    return is_legal;
}

SIXTRL_INLINE bool NS(EndTracking_is_legal_eot_marker_in_lattice_cobj)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT marker,
    NS(size_type) const eot_marker_index,
    NS(size_type) const nelems_in_lattice, NS(size_type) const line_start_idx,
    NS(particle_index_type) const line_start_at_elem ) SIXTRL_NOEXCEPT
{
    return ( ( NS(EndTracking_is_legal_marker_in_lattice_cobj)( marker,
                eot_marker_index, nelems_in_lattice, line_start_idx,
                    line_start_at_elem ) ) &&
             ( NS(EndTracking_ends_turn)( marker ) ) );
}

SIXTRL_INLINE NS(size_type)
NS(EndTracking_find_next_eot_marker_index_in_lattice_cobj)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT lattice,
    NS(size_type) const nelems_in_lattice, NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_elem ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_index_type) index_type;
    NS(size_type) index = nelems_in_lattice;

    if( ( lattice != SIXTRL_NULLPTR ) &&
        ( nelems_in_lattice > ( NS(size_type) )0 ) &&
        ( line_start_index <= nelems_in_lattice ) &&
        ( line_start_at_elem >= ( (
            index_type )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT + (
            index_type )line_start_index ) ) &&
        ( line_start_at_elem + ( index_type )( nelems_in_lattice -
            line_start_index ) < ( index_type
                )SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT ) )
    {
        index = line_start_index;

        for( ; index < nelems_in_lattice ; ++index ) {
            if( NS(EndTracking_is_legal_eot_marker_in_lattice_cobj)(
                    NS(EndTracking_const_from_cobj_index)( &lattice[ index ] ),
                        index, nelems_in_lattice, line_start_index,
                            line_start_at_elem ) ) break;
        }
    }

    return index;
}

SIXTRL_INLINE bool
NS(EndTracking_lattice_contains_no_illegal_markers_cobj)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT lattice,
    NS(size_type) const nelems_in_lattice, NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_elem ) SIXTRL_NOEXCEPT
{
    NS(size_type) index = line_start_index;

    bool has_no_illegal = (
        ( lattice != SIXTRL_NULLPTR ) &&
        ( nelems_in_lattice > ( NS(size_type) )0u ) &&
        ( nelems_in_lattice >= index ) );

    while( ( has_no_illegal ) && ( nelems_in_lattice > index ) )
    {
        if( NS(CObjIndex_is_end_tracking)( &lattice[ index ] ) ) {
            has_no_illegal &= NS(EndTracking_is_legal_marker_in_lattice_cobj)(
                NS(EndTracking_const_from_cobj_index)( &lattice[ index ] ),
                    index, nelems_in_lattice, line_start_index,
                        line_start_at_elem ); }
        ++index;
    }

    return has_no_illegal;
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(size_type) NS(EndTracking_num_legal_markers_in_lattice_cobj)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const*
        SIXTRL_RESTRICT lattice,
    NS(size_type) const num_elements_in_lattice,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_elem ) SIXTRL_NOEXCEPT
{
    NS(size_type) num_markers = ( NS(size_type) )0u;

    if( ( lattice != SIXTRL_NULLPTR ) &&
        ( num_elements_in_lattice >= line_start_index ) &&
        ( line_start_index >= ( NS(size_type) )0u ) &&
        ( line_start_at_elem >= (
            ( ( NS(particle_index_type) )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) +
            ( ( NS(particle_index_type) )line_start_index ) ) ) )
    {
        NS(size_type) ii = line_start_index;

        for( ; ii < num_elements_in_lattice ; ++ii )
        {
            if( ( NS(CObjIndex_is_end_tracking)( &lattice[ ii ] ) ) &&
                ( NS(EndTracking_is_legal_marker_in_lattice_cobj)(
                    NS(EndTracking_const_from_cobj_index)( &lattice[ ii ] ),
                        ii, num_elements_in_lattice, line_start_index,
                            line_start_at_elem ) ) )
            {
                ++num_markers;
            }
        }
    }

    return num_markers;
}

SIXTRL_INLINE NS(size_type)
NS(EndTracking_get_legal_marker_indices_from_lattice_cobj)(
    NS(size_type) const max_num_indices,
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT indices_begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT lattice,
    NS(size_type) const num_elements_in_lattice,
    NS(size_type) const line_start_index,
    NS(particle_index_type) const line_start_at_elem ) SIXTRL_NOEXCEPT
{
    NS(size_type) num_markers = ( NS(size_type) )0u;

    if( ( lattice != SIXTRL_NULLPTR ) &&
        ( ( indices_begin != SIXTRL_NULLPTR ) ||
          ( max_num_indices > ( NS(size_type) )0u ) ) &&
        ( num_elements_in_lattice >= line_start_index ) &&
        ( line_start_index >= ( NS(size_type) )0u ) &&
        ( line_start_at_elem >= (
            ( ( NS(particle_index_type) )SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT ) +
            ( ( NS(particle_index_type) )line_start_index ) ) ) )
    {
        NS(size_type) ii = line_start_index;

        for( ; ii < num_elements_in_lattice ; ++ii )
        {
            if( ( NS(CObjIndex_is_end_tracking)( &lattice[ ii ] ) ) &&
                ( NS(EndTracking_is_legal_marker_in_lattice_cobj)(
                    NS(EndTracking_const_from_cobj_index)( &lattice[ ii ] ),
                        ii, num_elements_in_lattice, line_start_index,
                            line_start_at_elem ) ) )
            {
                if( num_markers < max_num_indices )
                {
                    indices_begin[ num_markers ] = ii;
                }

                ++num_markers;
            }
        }
    }

    return num_markers;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_end_tracking)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(EndTracking_cobj_type_id)(),
        NS(EndTracking_cobj_actual_handle_size)(
            ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_end_tracking)( obj ) )
        ? ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
        )NS(EndTracking_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(EndTracking_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(EndTracking_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(EndTracking_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(EndTracking_from_cobj_index)(
        NS(CBuffer_index_at)( buffer, idx ) ); }

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_END_TRACKING_H__ */
