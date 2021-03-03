#ifndef SIXTRACKLIB_COMMON_BE_LIMIT_BE_LIMIT_RECT_ELLIPSE_C99_H__
#define SIXTRACKLIB_COMMON_BE_LIMIT_BE_LIMIT_RECT_ELLIPSE_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(LimitRectEllipse)
{
    NS(be_real_type)  x_max       SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)  y_max       SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)  a_squ       SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)  b_squ       SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)  a_b_squ     SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(LimitRectEllipse);

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRectEllipse_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRectEllipse_init)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const x_max, NS(be_real_type) const y_max,
    NS(be_real_type) const a_squ, NS(be_real_type) const b_squ
) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRectEllipse_x_max)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRectEllipse_default_x_max)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRectEllipse_set_x_max)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const x_max ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRectEllipse_y_max)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRectEllipse_default_y_max)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRectEllipse_set_y_max)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const y_max ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRectEllipse_a_squ)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRectEllipse_default_a_squ)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRectEllipse_set_a_squ)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const a_squ ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRectEllipse_b_squ)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRectEllipse_default_b_squ)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRectEllipse_set_b_squ)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const b_squ ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(LimitRectEllipse_a_b_squ)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRectEllipse_set_a_b_squ)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const a_b_squ ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(LimitRectEllipse_is_consistent)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRectEllipse_update)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRectEllipse_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)*
NS(LimitRectEllipse_preset)( SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)*
    SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(LimitRectEllipse_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(LimitRectEllipse_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(LimitRectEllipse_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(LimitRectEllipse_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(LimitRectEllipse_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_limit_rect_ellipse)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse) const*
NS(LimitRectEllipse_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse)*
NS(LimitRectEllipse_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse) const*
NS(LimitRectEllipse_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse)*
NS(LimitRectEllipse_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse) const*
NS(LimitRectEllipse_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse)*
NS(LimitRectEllipse_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse) const*
NS(LimitRectEllipse_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN
SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse)*
NS(LimitRectEllipse_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(LimitRectEllipse_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(LimitRectEllipse_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(LimitRectEllipse_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(LimitRectEllipse_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(LimitRectEllipse_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)*
NS(LimitRectEllipse_preset_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(LimitRectEllipse_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */
#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsTraits< ::NS(LimitRectEllipse) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_LIMIT_RECT_ELLIPSE;
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_LIMIT_RECT_ELLIPSE > {
            typedef ::NS(LimitRectEllipse) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* ************************************************************************* */
/* *****               Inline functions and methods                    ***** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/generated/config.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE )
    #include "sixtracklib/common/beam_elements/limit/limit_rect_ellipse_cobj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && !defined( _GPUCODE ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(status_type) NS(LimitRectEllipse_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { return NS(LimitRectEllipse_init)( limit,
        NS(LimitRectEllipse_default_x_max)(),
        NS(LimitRectEllipse_default_y_max)(),
        NS(LimitRectEllipse_default_a_squ)(),
        NS(LimitRectEllipse_default_b_squ)() ); }

SIXTRL_INLINE NS(status_type) NS(LimitRectEllipse_init)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const x_max, NS(be_real_type) const y_max,
    NS(be_real_type) const a_squ, NS(be_real_type) const b_squ
) SIXTRL_NOEXCEPT {
    return NS(LimitRectEllipse_set_y_max)( limit, y_max ) |
           NS(LimitRectEllipse_set_x_max)( limit, x_max ) |
           NS(LimitRectEllipse_set_a_squ)( limit, a_squ ) |
           NS(LimitRectEllipse_set_b_squ)( limit, b_squ ) |
           NS(LimitRectEllipse_set_a_b_squ)( limit, a_squ * b_squ ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(LimitRectEllipse_a_squ)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    return limit->a_squ; }

SIXTRL_INLINE NS(be_real_type) NS(LimitRectEllipse_default_a_squ)()
SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )SIXTRL_APERTURE_X_LIMIT *
           ( NS(be_real_type) )SIXTRL_APERTURE_X_LIMIT; }

SIXTRL_INLINE NS(status_type) NS(LimitRectEllipse_set_a_squ)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const a_squ ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( limit != SIXTRL_NULLPTR ) && ( a_squ >= ( NS(be_real_type) )0.0 ) ) {
        limit->a_squ = a_squ;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(LimitRectEllipse_x_max)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    return limit->x_max; }

SIXTRL_INLINE NS(be_real_type) NS(LimitRectEllipse_default_x_max)(
) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )SIXTRL_APERTURE_X_LIMIT; }

SIXTRL_INLINE NS(status_type) NS(LimitRectEllipse_set_x_max)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const x_max ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( limit != SIXTRL_NULLPTR ) && ( x_max >= ( NS(be_real_type) )0.0 ) ) {
        limit->x_max = x_max;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(LimitRectEllipse_b_squ)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    return limit->b_squ; }

SIXTRL_INLINE NS(be_real_type) NS(LimitRectEllipse_default_b_squ)(
) SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )SIXTRL_APERTURE_Y_LIMIT *
           ( NS(be_real_type) )SIXTRL_APERTURE_Y_LIMIT; }

SIXTRL_INLINE NS(status_type) NS(LimitRectEllipse_set_b_squ)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const b_squ ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( limit != SIXTRL_NULLPTR ) && ( b_squ >= ( NS(be_real_type) )0.0 ) ) {
        limit->b_squ = b_squ;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(LimitRectEllipse_a_b_squ)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    return limit->a_b_squ; }

SIXTRL_INLINE NS(status_type) NS(LimitRectEllipse_set_a_b_squ)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const a_b_squ ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( limit != SIXTRL_NULLPTR ) &&
        ( a_b_squ >= ( NS(be_real_type) )0.0 ) ) {
        limit->a_b_squ = a_b_squ;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(LimitRectEllipse_y_max)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT { SIXTRL_ASSERT( limit != SIXTRL_NULLPTR );
    return limit->y_max; }

SIXTRL_INLINE NS(be_real_type) NS(LimitRectEllipse_default_y_max)() SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )SIXTRL_APERTURE_Y_LIMIT; }

SIXTRL_INLINE NS(status_type) NS(LimitRectEllipse_set_y_max)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit,
    NS(be_real_type) const y_max ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( limit != SIXTRL_NULLPTR ) && ( y_max >= ( NS(be_real_type) )0.0 ) ) {
        limit->y_max = y_max;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(LimitRectEllipse_is_consistent)( SIXTRL_BE_ARGPTR_DEC
    const NS(LimitRectEllipse) *const SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT {
    bool is_consistent = false;
    if( limit != SIXTRL_NULLPTR )
    {
        typedef NS(be_real_type) real_type;

        is_consistent = (
            ( NS(LimitRectEllipse_x_max)( limit ) >= ( real_type )0.0 ) &&
            ( NS(LimitRectEllipse_y_max)( limit ) >= ( real_type )0.0 ) &&
            ( NS(LimitRectEllipse_a_squ)( limit ) >= ( real_type )0.0 ) &&
            ( NS(LimitRectEllipse_b_squ)( limit ) >= ( real_type )0.0 ) &&
            ( ( ( NS(LimitRectEllipse_a_squ)( limit ) *
                  NS(LimitRectEllipse_b_squ)( limit ) ) <=
                ( NS(LimitRectEllipse_a_b_squ)( limit ) +
                  SIXTRL_REAL_TYPE_EPS ) )  ||
              ( ( NS(LimitRectEllipse_a_squ)( limit ) *
                  NS(LimitRectEllipse_b_squ)( limit ) ) >=
                ( NS(LimitRectEllipse_a_b_squ)( limit ) -
                  SIXTRL_REAL_TYPE_EPS ) ) ) );
    }
    return is_consistent;
}

SIXTRL_INLINE NS(status_type) NS(LimitRectEllipse_update)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT limit
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( limit != SIXTRL_NULLPTR ) &&
        ( NS(LimitRectEllipse_x_max)( limit ) >= ( NS(be_real_type) )0.0 ) &&
        ( NS(LimitRectEllipse_y_max)( limit ) >= ( NS(be_real_type) )0.0 ) &&
        ( NS(LimitRectEllipse_a_squ)( limit ) >= ( NS(be_real_type) )0.0 ) &&
        ( NS(LimitRectEllipse_b_squ)( limit ) >= ( NS(be_real_type) )0.0 ) )
    {
        status = NS(LimitRectEllipse_set_a_b_squ)( limit,
            NS(LimitRectEllipse_a_squ)( limit ) *
            NS(LimitRectEllipse_b_squ)( limit ) );

        if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
            ( !NS(LimitRectEllipse_is_consistent)( limit ) ) )
        {
            status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
        }
    }

    return status;
}

SIXTRL_INLINE NS(status_type) NS(LimitRectEllipse_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT dest,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) ) {
        status = ( src != dest )
            ? NS(LimitRectEllipse_init)( dest,
                NS(LimitRectEllipse_x_max)( src ),
                NS(LimitRectEllipse_y_max)( src ),
                NS(LimitRectEllipse_a_squ)( src ),
                NS(LimitRectEllipse_b_squ)( src ) )
            : ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(LimitRectEllipse_cobj_type_id)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_obj_id_type)
        )SIXTRL_COBJECTS_TYPE_ID_LIMIT_RECT_ELLIPSE; }

SIXTRL_INLINE NS(cobj_size_type) NS(LimitRectEllipse_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(LimitRectEllipse_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(LimitRectEllipse) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(LimitRectEllipse_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(LimitRectEllipse_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(LimitRectEllipse_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( limit ),
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return NS(LimitRectEllipse_cobj_reserved_handle_size)( slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)*
NS(LimitRectEllipse_preset)( SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)*
    SIXTRL_RESTRICT limit ) SIXTRL_NOEXCEPT {
    if( limit != SIXTRL_NULLPTR ) NS(LimitRectEllipse_clear)( limit );
    return limit; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_limit_rect_ellipse)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(LimitRectEllipse_cobj_type_id)(),
        NS(LimitRectEllipse_cobj_actual_handle_size)( ( NS(cobj_size_type)
            )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse) const*
NS(LimitRectEllipse_const_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return ( NS(CObjIndex_is_limit_rect_ellipse)( obj ) )
        ? ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj ) : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse)*
NS(LimitRectEllipse_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse)*
        )NS(LimitRectEllipse_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse) const*
NS(LimitRectEllipse_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(LimitRectEllipse_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse)*
NS(LimitRectEllipse_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(LimitRectEllipse_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse) const*
NS(LimitRectEllipse_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(LimitRectEllipse_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(LimitRectEllipse)*
NS(LimitRectEllipse_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(LimitRectEllipse_from_cobj_index)(
        NS(CBuffer_index_at)( buffer, idx ) ); }

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BE_LIMIT_BE_LIMIT_RECT_ELLIPSE_C99_H__ */
