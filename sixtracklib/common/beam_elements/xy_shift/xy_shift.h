#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENT_XY_SHIFT_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENT_XY_SHIFT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(XYShift)
{
    NS(be_real_type) dx SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type) dy SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(XYShift);

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(XYShift_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT xy_shift ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(XYShift_init)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT xy_shift,
    NS(be_real_type) const dx, NS(be_real_type) const dy ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(XYShift_dx)(
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const
        SIXTRL_RESTRICT xy_shift ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(XYShift_default_dx)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(XYShift_set_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT xy_shift,
    NS(be_real_type) const dx ) SIXTRL_NOEXCEPT;


SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(XYShift_dy)(
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const
        SIXTRL_RESTRICT xy_shift ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(XYShift_default_dy)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(XYShift_set_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT xy_shift,
    NS(be_real_type) const dy ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(XYShift_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const
        SIXTRL_RESTRICT source ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(XYShift_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(XYShift_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(XYShift_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(XYShift_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(XYShift_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT xy_shift,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(XYShift)* NS(XYShift_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT xy_shift ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_xy_shift)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift) const*
NS(XYShift_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
    obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift) const*
NS(XYShift_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift) const*
NS(XYShift_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift) const*
NS(XYShift_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(XYShift_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(XYShift_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(XYShift_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(XYShift_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(XYShift_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT xy_shift,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(XYShift)*
NS(XYShift_preset_ext)( SIXTRL_BE_ARGPTR_DEC NS(XYShift)*
    SIXTRL_RESTRICT xy_shift ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(XYShift_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT xy_shift ) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */
#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsTraits< ::NS(XYShift) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_XY_SHIFT;
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_XY_SHIFT > {
            typedef ::NS(XYShift) value_type; };

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
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_cobj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(status_type) NS(XYShift_init)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_type) const dx, NS(be_real_type) const dy ) SIXTRL_NOEXCEPT {
    return NS(XYShift_set_dx)( elem, dx ) | NS(XYShift_set_dy)( elem, dy ); }

SIXTRL_INLINE NS(status_type) NS(XYShift_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    return NS(XYShift_init)( elem, NS(XYShift_default_dx)(),
        NS(XYShift_default_dy)() ); }
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(XYShift_dx)( SIXTRL_BE_ARGPTR_DEC const
    NS(XYShift) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR ); return elem->dx; }

SIXTRL_INLINE NS(be_real_type) NS(XYShift_default_dx)() SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(XYShift_set_dx)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_type) const dx ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dx = dx;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE NS(be_real_type) NS(XYShift_dy)( SIXTRL_BE_ARGPTR_DEC const
    NS(XYShift) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR ); return elem->dy; }

SIXTRL_INLINE NS(be_real_type) NS(XYShift_default_dy)() SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(XYShift_set_dy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_type) const dy ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->dy = dy;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE NS(status_type) NS(XYShift_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) )
    {
        status = ( dest != src )
            ? NS(XYShift_init)( dest, NS(XYShift_dx)( src ),
                                      NS(XYShift_dy)( src ) )
            : ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }

    return status; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(XYShift_cobj_type_id)() SIXTRL_NOEXCEPT {
    return ( NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_XY_SHIFT; }

SIXTRL_INLINE NS(cobj_size_type) NS(XYShift_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(XYShift_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(XYShift) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(XYShift_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(XYShift_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(XYShift_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( xy_shift ),
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    return NS(XYShift_cobj_reserved_handle_size)( slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(XYShift)* NS(XYShift_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT xy_shift ) SIXTRL_NOEXCEPT {
    if( xy_shift != SIXTRL_NULLPTR ) NS(XYShift_clear)( xy_shift );
    return xy_shift; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_xy_shift)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const
    NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(XYShift_cobj_type_id)(), NS(XYShift_cobj_actual_handle_size)(
            ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift) const*
NS(XYShift_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex)
    *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_xy_shift)( obj ) )
        ? ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
        )NS(XYShift_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift) const*
NS(XYShift_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(XYShift_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(XYShift_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift) const*
NS(XYShift_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(XYShift_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(XYShift_from_cobj_index)( NS(CBuffer_index_at)( buffer, idx ) ); }

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENT_XY_SHIFT_H__ */
