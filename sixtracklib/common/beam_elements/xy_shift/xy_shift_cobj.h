#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_COBJ_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_COBJ_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

/* SIXTRL_CBUFFER_OBJ_DATAPTR_DEC */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

SIXTRL_STATIC SIXTRL_FN bool NS(XYShift_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    NS(be_real_type) const dx, NS(be_real_type) const dy )  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(XYShift_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cbuffer_new)( SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)*
    SIXTRL_RESTRICT buffer );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_real_type) const dx, NS(be_real_type) const dy )SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT orig );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(XYShift_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_real_type) const dx, NS(be_real_type) const dy )  SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cobj_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT xy_shift );

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

SIXTRL_INLINE bool NS(XYShift_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_can_add_copy_of_trivial_object)( buffer, slot_size,
        NS(XYShift_cobj_reserved_handle_size)( slot_size ),
            requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_ARGPTR_DEC NS(XYShift) elem;
    NS(XYShift_clear)( &elem );
    return NS(XYShift_cobj_flat_buffer_add_copy)( buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(be_real_type) const dx, NS(be_real_type) const dy )  SIXTRL_NOEXCEPT {
    SIXTRL_BE_ARGPTR_DEC NS(XYShift) elem;
    NS(XYShift_init)( &elem, dx, dy );
    return NS(XYShift_cobj_flat_buffer_add_copy)( buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT {
    return NS(XYShift_from_cobj_index)(
        NS(CObjFlatBuffer_add_copy_of_trivial_object)( buffer, slot_size, orig,
            NS(XYShift_cobj_reserved_handle_size)( slot_size ),
                NS(XYShift_cobj_type_id)(), false ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(XYShift_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(CBuffer_can_add_copy_of_trivial_object)( b,
    NS(XYShift_cobj_reserved_handle_size)( NS(CBuffer_slot_size)( b ) ),
        requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    SIXTRL_BE_ARGPTR_DEC NS(XYShift) elem;
    NS(XYShift_clear)( &elem );
    return NS(XYShift_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_real_type) const dx, NS(be_real_type) const dy )  SIXTRL_NOEXCEPT {
    SIXTRL_BE_ARGPTR_DEC NS(XYShift) elem;
    NS(XYShift_init)( &elem, dx, dy );
    return NS(XYShift_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(XYShift)*
NS(XYShift_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT orig ) {
    NS(cobj_size_type) const slot_size = NS(CBuffer_slot_size)( buffer );
    return NS(XYShift_from_cobj_index)( NS(CBuffer_add_copy_of_trivial_object)(
        buffer, orig, NS(XYShift_cobj_actual_handle_size)( slot_size ),
            NS(XYShift_cobj_type_id)(), false ) ); }

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_COBJ_H__  */
