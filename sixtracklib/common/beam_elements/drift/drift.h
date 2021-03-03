#ifndef SIXTRACKLIB_COMMON_BE_DRIFT_BEAM_ELEMENT_DRIFT_H__
#define SIXTRACKLIB_COMMON_BE_DRIFT_BEAM_ELEMENT_DRIFT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(Drift)
{
    NS(be_real_type) length SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(Drift);

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Drift_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Drift_init)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT drift,
    NS(be_real_type) const length ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(Drift_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(Drift_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(Drift_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(Drift_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(Drift_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT drift,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Drift_default_length)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Drift_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT drift
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Drift_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT drift,
    NS(be_real_type) const length ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Drift_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const
        SIXTRL_RESTRICT source ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_drift)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift) const*
NS(Drift_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const
    struct NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift)*
NS(Drift_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
    SIXTRL_RESTRICT index_obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift) const*
NS(Drift_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const index, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift)*
NS(Drift_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const index, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift) const*
NS(Drift_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift)*
NS(Drift_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift) const*
NS(Drift_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift)*
NS(Drift_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type) NS(Drift_cobj_type_id_ext)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type) NS(Drift_cobj_num_dataptrs_ext)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Drift_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Drift_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(Drift_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT drift,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

/* ========================================================================= */

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(DriftExact)
{
    NS(be_real_type) length SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(DriftExact);

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(DriftExact_init)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT drift,
    NS(be_real_type) const length ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(DriftExact_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(DriftExact_default_length)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(DriftExact_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT drift
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(DriftExact_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT drift,
    NS(be_real_type) const length ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(DriftExact_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const
        SIXTRL_RESTRICT source ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(DriftExact_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(DriftExact_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(DriftExact_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(DriftExact_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(DriftExact_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT drift,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(DriftExact)*
NS(DriftExact_preset)( SIXTRL_BE_ARGPTR_DEC NS(DriftExact)*
    SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_drift_exact)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(DriftExact) const*
NS(DriftExact_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(DriftExact)*
NS(DriftExact_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(DriftExact) const*
NS(DriftExact_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(DriftExact)*
NS(DriftExact_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(DriftExact) const*
NS(DriftExact_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(DriftExact)*
NS(DriftExact_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(DriftExact) const*
NS(DriftExact_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(DriftExact)*
NS(DriftExact_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(DriftExact_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(DriftExact_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(DriftExact_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(DriftExact_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(DriftExact_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT drift,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(DriftExact)*
NS(DriftExact_preset_ext)( SIXTRL_BE_ARGPTR_DEC NS(DriftExact)*
    SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(DriftExact_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsTraits< ::NS(Drift) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_DRIFT;
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_DRIFT > {
            typedef ::NS(Drift) value_type; };


    template<> struct CObjectsTraits< ::NS(DriftExact) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_DRIFT_EXACT;
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_DRIFT_EXACT > {
            typedef ::NS(DriftExact) value_type; };

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
    #include "sixtracklib/common/beam_elements/drift/drift_cobj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Drift)* NS(Drift_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT {
    if( drift != SIXTRL_NULLPTR ) NS(Drift_clear)( drift );
    return drift; }

SIXTRL_INLINE NS(status_type) NS(Drift_init)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT drift,
    NS(be_real_type) const length ) SIXTRL_NOEXCEPT {
    return NS(Drift_set_length)( drift, length ); }

SIXTRL_INLINE NS(status_type) NS(Drift_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT {
    return NS(Drift_init)( drift, NS(Drift_default_length)() ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(Drift_cobj_type_id)() SIXTRL_NOEXCEPT {
    return ( NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_DRIFT; }

SIXTRL_INLINE NS(cobj_size_type) NS(Drift_cobj_num_dataptrs)() SIXTRL_NOEXCEPT {
    return ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(Drift_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(Drift) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(Drift_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(Drift_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(Drift_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( drift ), NS(cobj_size_type) slot_size
) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return NS(Drift_cobj_reserved_handle_size)( slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(Drift_length)( SIXTRL_BE_ARGPTR_DEC const
    NS(Drift) *const SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( drift != SIXTRL_NULLPTR );
    return drift->length; }

SIXTRL_INLINE NS(be_real_type) NS(Drift_default_length)() SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(Drift_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT drift,
    NS(be_real_type) const length ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( drift != SIXTRL_NULLPTR );
    drift->length = length;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE NS(status_type) NS(Drift_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT source
) SIXTRL_NOEXCEPT { return NS(Drift_set_length)(
        destination, NS(Drift_length)( source ) ); }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_drift)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const
    NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(Drift_cobj_type_id)(), NS(Drift_cobj_actual_handle_size)(
            ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift) const*
NS(Drift_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex)
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_drift)( obj ) )
        ? ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift)* NS(Drift_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift)*
        )NS(Drift_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift) const*
NS(Drift_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(Drift_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift)*
NS(Drift_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(Drift_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift) const*
NS(Drift_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Drift_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Drift)* NS(Drift_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Drift_from_cobj_index)( NS(CBuffer_index_at)( buffer, idx ) ); }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(DriftExact_cobj_type_id)(
) SIXTRL_NOEXCEPT { return ( NS(cobj_obj_id_type)
    )SIXTRL_COBJECTS_TYPE_ID_DRIFT_EXACT; }

SIXTRL_INLINE NS(cobj_size_type) NS(DriftExact_cobj_num_dataptrs)(
) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(DriftExact_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(DriftExact) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(DriftExact_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(DriftExact_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(DriftExact_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( drift ),
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return NS(DriftExact_cobj_reserved_handle_size)( slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* NS(DriftExact_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT {
    if( drift != SIXTRL_NULLPTR ) NS(DriftExact_clear)( drift );
    return drift; }

SIXTRL_INLINE NS(status_type) NS(DriftExact_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT {
    return NS(DriftExact_init)( drift, NS(DriftExact_default_length)() ); }

SIXTRL_INLINE NS(status_type) NS(DriftExact_init)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT drift,
    NS(be_real_type) const length ) SIXTRL_NOEXCEPT {
    return NS(DriftExact_set_length)( drift, length ); }

SIXTRL_INLINE NS(be_real_type) NS(DriftExact_length)( SIXTRL_BE_ARGPTR_DEC const
    NS(DriftExact) *const SIXTRL_RESTRICT drift ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( drift != SIXTRL_NULLPTR ); return drift->length; }

SIXTRL_INLINE NS(status_type) NS(DriftExact_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT drift,
    NS(be_real_type) const length ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( drift != SIXTRL_NULLPTR );
    drift->length = length;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE NS(be_real_type) NS(DriftExact_default_length)() SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(DriftExact_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) ) {
        status = ( dest != src )
            ? NS(DriftExact_init)( dest, NS(DriftExact_length)( src ) )
            : ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_drift_exact)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjIndex_is_consistent_with_type)( obj,
    NS(DriftExact_cobj_type_id)(), NS(DriftExact_cobj_actual_handle_size)(
        ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DriftExact) const*
NS(DriftExact_const_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return ( NS(CObjIndex_is_drift_exact)( obj ) )
        ? ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DriftExact) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DriftExact)*
NS(DriftExact_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DriftExact)*
        )NS(DriftExact_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DriftExact) const*
NS(DriftExact_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(DriftExact_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DriftExact)*
NS(DriftExact_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(DriftExact_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DriftExact) const*
NS(DriftExact_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(DriftExact_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(DriftExact)*
NS(DriftExact_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(DriftExact_from_cobj_index)(
        NS(CBuffer_index_at)( buffer, idx ) ); }

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BE_DRIFT_BEAM_ELEMENT_DRIFT_H__ */
