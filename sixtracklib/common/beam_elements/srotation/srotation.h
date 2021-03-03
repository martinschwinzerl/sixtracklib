#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(SRotation)
{
    NS(be_real_type) cos_z SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type) sin_z SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(SRotation);

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SRotation_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SRotation_init)(
SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_type) const cos_z, NS(be_real_type) const sin_z ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SRotation_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SRotation_angle)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SRotation_cos_z)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SRotation_sin_z)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SRotation_default_angle)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SRotation_default_angle_deg)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SRotation_default_cos_z)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(SRotation_default_sin_z)(
    void ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SRotation_set_angle)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_type) const angle ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SRotation_set_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_type) const angle_deg ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SRotation_set_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_type) const cos_angle ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SRotation_set_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_type) const sin_angle ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN int NS(SRotation_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type)
NS(SRotation_cobj_type_id)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(SRotation_cobj_num_dataptrs)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(SRotation_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(SRotation_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(SRotation_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srot,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(SRotation)*
NS(SRotation_preset)( SIXTRL_BE_ARGPTR_DEC NS(SRotation)*
    SIXTRL_RESTRICT srot ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_srotation)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation) const*
NS(SRotation_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation)*
NS(SRotation_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
    obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation) const*
NS(SRotation_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation)*
NS(SRotation_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation) const*
NS(SRotation_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation)*
NS(SRotation_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation) const*
NS(SRotation_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation)*
NS(SRotation_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(SRotation_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(SRotation_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(SRotation_cobj_actual_handle_size_ext)(
        NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(SRotation_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(SRotation_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srot,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(SRotation)*
NS(SRotation_preset_ext)( SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT srot
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(SRotation_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT srot ) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */
#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsStoreResultTypeTraits< ::NS(SRotation) >
    {
        typedef ::NS(SRotation) value_type;
        typedef SIXTRL_BE_ARGPTR_DEC value_type const* const_pointer;
        typedef SIXTRL_BE_ARGPTR_DEC value_type* pointer;
    };

    template<> struct CObjectsTraits< ::NS(SRotation) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_SROTATION;
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_SROTATION > {
            typedef ::NS(SRotation) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* ************************************************************************* */
/* *****          Implementation of C inline functions                   *** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/math_functions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE )
    #include "sixtracklib/common/beam_elements/srotation/srotation_cobj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(status_type) NS(SRotation_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
        return NS(SRotation_init)( elem, NS(SRotation_default_cos_z)(),
            NS(SRotation_default_sin_z)() ); }

SIXTRL_INLINE NS(status_type) NS(SRotation_init)(
SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT elem,
    NS(be_real_type) const cos_z,
    NS(be_real_type) const sin_z ) SIXTRL_NOEXCEPT {
    return NS(SRotation_set_cos_z)( elem, cos_z ) |
           NS(SRotation_set_sin_z)( elem, sin_z ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(SRotation_angle_deg)( SIXTRL_BE_ARGPTR_DEC
    const NS(SRotation) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    return NS(MathConst_rad2deg)() * NS(SRotation_angle)( elem ); }

SIXTRL_INLINE NS(be_real_type) NS(SRotation_angle)( SIXTRL_BE_ARGPTR_DEC const
    NS(SRotation) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    return NS(atan2)( NS(SRotation_sin_z)( elem ),
                      NS(SRotation_cos_z)( elem ) ); }

SIXTRL_INLINE NS(be_real_type) NS(SRotation_cos_z)( SIXTRL_BE_ARGPTR_DEC const
    NS(SRotation) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(abs)( elem->cos_z ) <= ( NS(be_real_type) )1. );
    SIXTRL_ASSERT( NS(abs)( elem->sin_z ) <= ( NS(be_real_type) )1. );
    return elem->cos_z; }

SIXTRL_INLINE NS(be_real_type) NS(SRotation_sin_z)( SIXTRL_BE_ARGPTR_DEC const
    NS(SRotation) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(abs)( elem->cos_z ) <= ( NS(be_real_type) )1. );
    SIXTRL_ASSERT( NS(abs)( elem->sin_z ) <= ( NS(be_real_type) )1. );
    return elem->sin_z; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(SRotation_default_angle)( void
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.0; }

SIXTRL_INLINE NS(be_real_type) NS(SRotation_default_angle_deg)( void
    ) SIXTRL_NOEXCEPT
{ return NS(MathConst_rad2deg)() * NS(SRotation_default_angle)(); }

SIXTRL_INLINE NS(be_real_type) NS(SRotation_default_cos_z)( void
    ) SIXTRL_NOEXCEPT { return NS(cos)( NS(SRotation_default_angle)() ); }

SIXTRL_INLINE NS(be_real_type) NS(SRotation_default_sin_z)( void
    ) SIXTRL_NOEXCEPT { return NS(sin)( NS(SRotation_default_angle)() ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(status_type) NS(SRotation_set_angle)( SIXTRL_BE_ARGPTR_DEC
    NS(SRotation)* SIXTRL_RESTRICT elem, NS(be_real_type) const angle
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    elem->cos_z = NS(cos)( angle );
    elem->sin_z = NS(sin)( angle );
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE NS(status_type) NS(SRotation_set_angle_deg)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT e,
    NS(be_real_type) const angle_deg ) SIXTRL_NOEXCEPT {
    return NS(SRotation_set_angle)( e, NS(MathConst_deg2rad)() * angle_deg ); }

SIXTRL_INLINE NS(status_type) NS(SRotation_set_cos_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT e,
    NS(be_real_type) const cos_angle ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( e != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(abs)( cos_angle ) <= ( NS(be_real_type) )1. );
    e->cos_z = cos_angle;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE NS(status_type) NS(SRotation_set_sin_z)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT e,
    NS(be_real_type) const sin_z ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( e != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(abs)( sin_z ) <= ( NS(be_real_type) )1. );
    e->sin_z = sin_z;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE int NS(SRotation_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) ) {
        status = ( dst != src )
            ? NS(SRotation_init)( dst, NS(SRotation_cos_z)( src ),
                    NS(SRotation_sin_z)( src ) )
            : ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(cobj_obj_id_type) NS(SRotation_cobj_type_id)() SIXTRL_NOEXCEPT {
    return ( NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_SROTATION; }

SIXTRL_INLINE NS(cobj_size_type) NS(SRotation_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(SRotation_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(SRotation) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(SRotation_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(SRotation_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(SRotation_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( srot ),
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return NS(SRotation_cobj_reserved_handle_size)( slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(SRotation)* NS(SRotation_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT srot ) SIXTRL_NOEXCEPT {
    if( srot != SIXTRL_NULLPTR ) NS(SRotation_clear)( srot );
    return srot; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_srotation)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjIndex_is_consistent_with_type)( obj,
    NS(SRotation_cobj_type_id)(), NS(SRotation_cobj_actual_handle_size)(
        ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation) const*
NS(SRotation_const_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_srotation)( obj ) )
        ? ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation)*
NS(SRotation_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation)*
        )NS(SRotation_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation) const*
NS(SRotation_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(SRotation_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation)*
NS(SRotation_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(SRotation_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation) const*
NS(SRotation_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(SRotation_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(SRotation)*
NS(SRotation_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(SRotation_from_cobj_index)( NS(CBuffer_index_at)( buffer, idx ) ); }

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_H__ */
