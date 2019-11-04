#ifndef SIXTRACKLIB_COMMON_BUFFER_BUFFER_BINARY_PATCH_ITEM_C99_H__
#define SIXTRACKLIB_COMMON_BUFFER_BUFFER_BINARY_PATCH_ITEM_C99_H__


#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/buffer/buffer_object.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

typedef struct NS(BinaryPatchItem)
{
    NS(object_type_id_t) elem_type_id            SIXTRL_ALIGN( 8 );
    NS(buffer_size_t)    elem_buffer_index       SIXTRL_ALIGN( 8 );
    NS(buffer_size_t)    elem_patch_begin_offset SIXTRL_ALIGN( 8 );
    NS(buffer_size_t)    patch_data_size         SIXTRL_ALIGN( 8 );
    NS(buffer_address_t) patch_data_begin        SIXTRL_ALIGN( 8 );
}
NS(BinaryPatchItem);

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(BinaryPatchItem_num_dataptrs)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(BinaryPatchItem) *const SIXTRL_RESTRICT item );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(BinaryPatchItem_num_slots)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(BinaryPatchItem) *const SIXTRL_RESTRICT item,
    NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_DATAPTR_DEC NS(BinaryPatchItem)*
NS(BinaryPatchItem_preset)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(BinaryPatchItem)* SIXTRL_RESTRICT item );

SIXTRL_STATIC SIXTRL_FN NS(object_type_id_t)
NS(BinaryPatchItem_elem_type_id)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(BinaryPatchItem) *const SIXTRL_RESTRICT item );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(BinaryPatchItem_elem_buffer_size)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(BinaryPatchItem) *const SIXTRL_RESTRICT item );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(BinaryPatchItem_elem_patch_begin_offset)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(BinaryPatchItem) *const SIXTRL_RESTRICT item );

SIXTRL_STATIC SIXTRL_FN NS(buffer_size_t)
NS(BinaryPatchItem_patch_data_size)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(BinaryPatchItem) *const SIXTRL_RESTRICT item );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC unsigned char const*
NS(BinaryPatchItem_get_const_patch_data_begin)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(BinaryPatchItem) *const SIXTRL_RESTRICT item );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC unsigned char*
NS(BinaryPatchItem_get_patch_data_begin)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(BinaryPatchItem)* SIXTRL_RESTRICT item );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(BinaryPatchItem_set_elem_type_id)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(BinaryPatchItem)* SIXTRL_RESTRICT item,
    NS(object_type_id_t) const elem_type_id );

SIXTRL_STATIC SIXTRL_FN void NS(BinaryPatchItem_set_elem_buffer_size)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(BinaryPatchItem)* SIXTRL_RESTRICT item,
    NS(buffer_size_t) const elem_buffer_size );

SIXTRL_STATIC SIXTRL_FN void NS(BinaryPatchItem_set_elem_patch_begin_offset)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(BinaryPatchItem)* SIXTRL_RESTRICT item,
    NS(buffer_size_t) const elem_patch_begin_offset );

SIXTRL_STATIC SIXTRL_FN void NS(BinaryPatchItem_set_patch_data_size)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(BinaryPatchItem)* SIXTRL_RESTRICT item,
    NS(buffer_size_t) const patch_data_size );

SIXTRL_STATIC SIXTRL_FN void NS(BinaryPatchItem_set_patch_data_begin)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(BinaryPatchItem)* SIXTRL_RESTRICT item,
    NS(buffer_address_t) const patch_data_begin );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(BinaryPatchItem const*
NS(BinaryPatchItem_managed_buffer_get_const_item)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const be_index,
    NS(buffer_size_t) const slot_size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(BinaryPatchItem)*
NS(BinaryPatchItem_managed_buffer_get_item)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(buffer_size_t) const be_index, NS(buffer_size_t) const slot_size );

#if !defined( _GPUCODE )

SIXTRL_STATIC SIXTRL_HOST_FN
SIXTRL_BUFFER_DATAPTR_DEC NS(BinaryPatchItem) const*
NS(BinaryPatchItem_buffer_get_const_item)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const be_index );

SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_BUFFER_DATAPTR_DEC
NS(BinaryPatchItem)* NS(BinaryPatchItem_buffer_get_item)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const be_index );

SIXTRL_STATIC SIXTRL_FN bool NS(BinaryPatchItem_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(BinaryPatchItem)*
NS(BinaryPatchItem_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(BinaryPatchItem)*
NS(BinaryPatchItem_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(object_type_id_t) const type_id,
    NS(buffer_size_t) const elem_index,
    NS(buffer_size_t) const dest_pointer_offset,
    NS(buffer_size_t) const out_buffer_index );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(BinaryPatchItem)*
NS(BinaryPatchItem_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC const NS(BinaryPatchItem) *const
        SIXTRL_RESTRICT item );

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* */
/* *****          Implementation of C inline functions                   *** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
    #if !defined( _GPUCODE )
    #include "sixtracklib/common/buffer.h"
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */


#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BUFFER_BUFFER_BINARY_PATCH_ITEM_C99_H__ */

/* end: */
