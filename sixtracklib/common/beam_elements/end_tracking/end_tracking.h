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

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_end_tracking)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    struct NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN
SIXTRL_BE_ARGPTR_DEC NS(EndTracking) const* NS(EndTracking_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(EndTracking_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx,
    bool const ends_turn )  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(EndTracking)*
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

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx, bool const ends_turn  );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT orig );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(EndTracking_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx, bool const ends_turn );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_cobj_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT elem );

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

SIXTRL_INLINE bool NS(CObjIndex_is_end_tracking)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(EndTracking_cobj_type_id)(),
        NS(EndTracking_cobj_actual_handle_size)(
            ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_end_tracking)( obj ) )
        ? ( SIXTRL_BE_ARGPTR_DEC NS(EndTracking) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
        )NS(EndTracking_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(EndTracking_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(EndTracking_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(EndTracking) const*
NS(EndTracking_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(EndTracking_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(EndTracking_from_cobj_index)(
        NS(CBuffer_index_at)( buffer, idx ) ); }

/* -------------------------------------------------------------------------- */

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

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(EndTracking) elem;
    NS(EndTracking_clear)( &elem );
    return NS(EndTracking_cobj_flat_buffer_add_copy)( buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(EndTracking)*
NS(EndTracking_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx,
    bool const ends_turn )  SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(EndTracking) elem;
    NS(EndTracking_init)( &elem, next_at_element, next_buffer_idx, ends_turn );
    return NS(EndTracking_cobj_flat_buffer_add_copy)( buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(EndTracking)*
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

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* NS(EndTracking_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking) elem;
    NS(EndTracking_clear)( &elem );
    return NS(EndTracking_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* NS(EndTracking_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particle_index_type) const next_at_element,
    NS(size_type) const next_buffer_idx,
    bool const ends_turn  ) {
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking) elem;
    NS(EndTracking_init)( &elem, next_at_element, next_buffer_idx, ends_turn );
    return NS(EndTracking_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(EndTracking)*
NS(EndTracking_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT orig ) {
    NS(cobj_size_type) const slot_size = NS(CBuffer_slot_size)( buffer );
    return NS(EndTracking_from_cobj_index)(
        NS(CBuffer_add_copy_of_trivial_object)( buffer, orig,
            NS(EndTracking_cobj_reserved_handle_size)( slot_size ),
            NS(EndTracking_cobj_type_id)(), false ) ); }

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_END_TRACKING_H__ */
