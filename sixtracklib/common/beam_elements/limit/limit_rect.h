#ifndef SIXTRL_COMMON_BEAM_ELEMENTS_LIMIT_RECT_C99_H__
#define SIXTRL_COMMON_BEAM_ELEMENTS_LIMIT_RECT_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(LimitRect)
{
    NS(be_real_type) x_min SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type) x_max SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );

    NS(be_real_type) y_min SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type) y_max SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(LimitRect);

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRect_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRect_init)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const x_min, NS(be_real_type) const x_max,
    NS(be_real_type) const y_min, NS(be_real_type) const y_max
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRect_x_min)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRect_default_x_min)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRect_set_x_min)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const x_min ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRect_x_max)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRect_default_x_max)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRect_set_x_max)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const x_max ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRect_y_min)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRect_default_y_min)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRect_set_y_min)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const y_min ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRect_y_max)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRect_default_y_max)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRect_set_y_max)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const y_max ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_preset)( SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
    SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(LimitRect_is_consistent)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const
        SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRect_update)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRect_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(LimitRect_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(LimitRect_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(LimitRect_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(LimitRect_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(LimitRect_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* NS(LimitRect_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_limit_rect)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect) const*
NS(LimitRect_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    struct NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect) const*
NS(LimitRect_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN
SIXTRL_BE_ARGPTR_DEC NS(LimitRect) const* NS(LimitRect_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(LimitRect_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(LimitRect)*
NS(LimitRect_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(LimitRect)*
NS(LimitRect_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(be_real_type) const x_min, NS(be_real_type) const x_max,
    NS(be_real_type) const y_min, NS(be_real_type) const y_max ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(LimitRect)*
NS(LimitRect_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(LimitRect_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_real_type) const x_min, NS(be_real_type) const x_max,
    NS(be_real_type) const y_min, NS(be_real_type) const y_max  );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT orig );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect) const*
NS(LimitRect_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(LimitRect_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(LimitRect_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(LimitRect_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(LimitRect_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(LimitRect_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_preset_ext)( SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT
    limit ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(LimitRect_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(LimitRect_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_real_type) const x_min, NS(be_real_type) const x_max,
    NS(be_real_type) const y_min, NS(be_real_type) const y_max );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_cobj_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit );

#endif /* !defined( _GPUCODE ) */
#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsTraits< ::NS(LimitRect) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_LIMIT_RECT;
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_LIMIT_RECT > {
            typedef ::NS(LimitRect) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* ========================================================================= */
/*        Implementation of inline functions for NS(LimitRect)               */
/* ========================================================================= */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/generated/config.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(status_type) NS(LimitRect_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT {
    return NS(LimitRect_init)( limit,
        NS(LimitRect_default_x_min)(), NS(LimitRect_default_x_max)(),
        NS(LimitRect_default_y_min)(), NS(LimitRect_default_y_max)() ); }

SIXTRL_INLINE NS(status_type) NS(LimitRect_init)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const x_min, NS(be_real_type) const x_max,
    NS(be_real_type) const y_min, NS(be_real_type) const y_max
) SIXTRL_NOEXCEPT {
    return NS(LimitRect_set_x_min)( limit, x_min ) |
           NS(LimitRect_set_x_max)( limit, x_max ) |
           NS(LimitRect_set_y_min)( limit, y_min ) |
           NS(LimitRect_set_y_max)( limit, y_max ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(LimitRect_x_min)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    return limit->x_min; }

SIXTRL_INLINE NS(be_real_type) NS(LimitRect_default_x_min)( ) SIXTRL_NOEXCEPT {
    return -( ( NS(be_real_type) )SIXTRL_APERTURE_X_LIMIT ); }

SIXTRL_INLINE NS(status_type) NS(LimitRect_set_x_min)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const x_min ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    limit->x_min = x_min;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(LimitRect_x_max)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    return limit->x_max; }

SIXTRL_INLINE NS(be_real_type) NS(LimitRect_default_x_max)() SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )SIXTRL_APERTURE_X_LIMIT; }

SIXTRL_INLINE NS(status_type) NS(LimitRect_set_x_max)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const x_max ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    limit->x_max = x_max;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(LimitRect_y_min)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    return limit->y_min; }

SIXTRL_INLINE NS(be_real_type) NS(LimitRect_default_y_min)() SIXTRL_NOEXCEPT {
    return -( ( NS(be_real_type) )SIXTRL_APERTURE_Y_LIMIT ); }

SIXTRL_INLINE NS(status_type) NS(LimitRect_set_y_min)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const y_min ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    limit->y_min = y_min;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(LimitRect_y_max)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    return limit->y_max; }

SIXTRL_INLINE NS(be_real_type) NS(LimitRect_default_y_max)() SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )SIXTRL_APERTURE_Y_LIMIT; }

SIXTRL_INLINE NS(status_type) NS(LimitRect_set_y_max)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const y_max ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    limit->y_max = y_max;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(LimitRect_is_consistent)( SIXTRL_BE_ARGPTR_DEC
    const NS(LimitRect) *const SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT {
    bool is_consistent = false;
    if( limit != SIXTRL_NULLPTR )
    {
        is_consistent = (
            ( NS(LimitRect_x_min)( limit ) <= NS(LimitRect_x_max)( limit ) ) &&
            ( NS(LimitRect_y_min)( limit ) <= NS(LimitRect_y_max)( limit ) ) );
    }
    return is_consistent;
}

SIXTRL_INLINE NS(status_type) NS(LimitRect_update)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( limit != SIXTRL_NULLPTR )
    {
        NS(be_real_type) const new_x_min =
            ( NS(LimitRect_x_min)( limit ) <= NS(LimitRect_x_max)( limit ) )
                ? NS(LimitRect_x_min)( limit ) : NS(LimitRect_x_max)( limit );

        NS(be_real_type) const new_x_max =
            ( NS(LimitRect_x_max)( limit ) >= NS(LimitRect_x_min)( limit ) )
                ? NS(LimitRect_x_max)( limit ) : NS(LimitRect_x_min)( limit );

        NS(be_real_type) const new_y_min =
            ( NS(LimitRect_y_min)( limit ) <= NS(LimitRect_y_max)( limit ) )
                ? NS(LimitRect_y_min)( limit ) : NS(LimitRect_y_max)( limit );

        NS(be_real_type) const new_y_max =
            ( NS(LimitRect_y_max)( limit ) >= NS(LimitRect_y_min)( limit ) )
                ? NS(LimitRect_y_max)( limit ) : NS(LimitRect_y_min)( limit );

        status = NS(LimitRect_init)(
            limit, new_x_min, new_x_max, new_y_min, new_y_max );

        if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
            ( !NS(LimitRect_is_consistent)( limit ) ) )
        {
            status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
        }
    }
    return status;
}

SIXTRL_INLINE NS(status_type) NS(LimitRect_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) ) {
        status = ( src != dest )
            ? NS(LimitRect_init)( dest,
                NS(LimitRect_x_min)( src ), NS(LimitRect_x_max)( src ),
                NS(LimitRect_y_min)( src ), NS(LimitRect_y_max)( src ) )
            : ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(LimitRect_cobj_type_id)() SIXTRL_NOEXCEPT
{ return ( NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_LIMIT_RECT; }

SIXTRL_INLINE NS(cobj_size_type) NS(LimitRect_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(LimitRect_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(LimitRect) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(LimitRect_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(LimitRect_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(LimitRect_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( limit ),
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(LimitRect_cobj_reserved_handle_size)( slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* NS(LimitRect_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT {
    if( limit != SIXTRL_NULLPTR ) NS(LimitRect_clear)( limit );
    return limit; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_limit_rect)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
        return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(LimitRect_cobj_type_id)(), NS(LimitRect_cobj_reserved_handle_size)(
            ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitRect) const*
NS(LimitRect_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const
    NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_limit_rect)( obj ) )
        ? ( SIXTRL_BE_ARGPTR_DEC NS(LimitRect) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* NS(LimitRect_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
        )NS(LimitRect_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitRect) const*
NS(LimitRect_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(LimitRect_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(LimitRect_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitRect) const*
NS(LimitRect_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(LimitRect_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* NS(LimitRect_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(LimitRect_from_cobj_index)( NS(CBuffer_index_at)( buffer, idx ) ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(LimitRect_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_can_add_copy_of_trivial_object)( buffer, slot_size,
        NS(LimitRect_cobj_reserved_handle_size)( slot_size ),
            requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(LimitRect)*
NS(LimitRect_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(LimitRect) elem;
    NS(LimitRect_clear)( &elem );
    return NS(LimitRect_cobj_flat_buffer_add_copy)( buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(LimitRect)*
NS(LimitRect_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(be_real_type) const x_min, NS(be_real_type) const x_max,
    NS(be_real_type) const y_min, NS(be_real_type) const y_max ) SIXTRL_NOEXCEPT
{
    SIXTRL_CBUFFER_ARGPTR_DEC NS(LimitRect) elem;
    NS(LimitRect_init)( &elem, x_min, x_max, y_min, y_max );
    return NS(LimitRect_cobj_flat_buffer_add_copy)( buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(LimitRect)*
NS(LimitRect_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT {
    return ( SIXTRL_CBUFFER_DATAPTR_DEC NS(LimitRect)* )( uintptr_t
        )NS(CObjIndex_begin_addr)( NS(CObjFlatBuffer_add_copy_of_trivial_object)(
            buffer, slot_size, orig, NS(LimitRect_cobj_reserved_handle_size)(
                slot_size ), NS(LimitRect_cobj_type_id)(), false ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(LimitRect_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(CBuffer_can_add_copy_of_trivial_object)( b,
    NS(LimitRect_cobj_reserved_handle_size)( NS(CBuffer_slot_size)( b ) ),
        requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* NS(LimitRect_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect) elem;
    NS(LimitRect_clear)( &elem );
    return NS(LimitRect_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* NS(LimitRect_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_real_type) const x_min, NS(be_real_type) const x_max,
    NS(be_real_type) const y_min, NS(be_real_type) const y_max  ) {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(LimitRect) elem;
    NS(LimitRect_init)( &elem, x_min, x_max, y_min, y_max );
    return NS(LimitRect_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitRect)*
NS(LimitRect_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT orig ) {
    return ( SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* )( uintptr_t
        )NS(CObjIndex_begin_addr)( NS(CBuffer_add_copy_of_trivial_object)(
            buffer, orig, NS(LimitRect_cobj_actual_handle_size)(
                NS(CBuffer_slot_size)( buffer ) ), NS(LimitRect_cobj_type_id)(),
                    false ) ); }

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRL_COMMON_BEAM_ELEMENTS_LIMIT_RECT_C99_H__ */
