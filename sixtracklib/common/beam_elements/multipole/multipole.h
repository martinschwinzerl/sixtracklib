#ifndef SIXTRACKLIB_COMMON_BE_MULTIPOLE_BEAM_ELEMENT_MULTIPOLE_H__
#define SIXTRACKLIB_COMMON_BE_MULTIPOLE_BEAM_ELEMENT_MULTIPOLE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(CObjIndex);
struct NS(CBuffer);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(Multipole)
{
    NS(be_order_type)  max_order    SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_order_type)  order        SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)   length       SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)   hxl          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_real_type)   hyl          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(be_addr_type)   bal_addr     SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(Multipole);

SIXTRL_STATIC SIXTRL_FN NS(be_order_type) NS(Multipole_max_order)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_order_type)
NS(Multipole_default_max_order)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_max_order)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_order_type) const max_order ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(Multipole_bal_capacity)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(Multipole_set_bal_capacity)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const bal_capacity ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_order_type) NS(Multipole_order)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_order_type) NS(Multipole_default_order)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_order)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_order_type) const order ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(Multipole_bal_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_size_type) NS(Multipole_set_bal_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const bal_length ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Multipole_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Multipole_default_length)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const length ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Multipole_hxl)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Multipole_default_hxl)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_hxl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const hxl ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Multipole_hyl)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Multipole_default_hyl)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_hyl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const hyl ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_addr_type) NS(Multipole_bal_addr)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
        SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_addr_type) NS(Multipole_default_bal_addr)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_bal_addr)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_addr_type) const bal_addr ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(Multipole_const_bal_begin)( SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
    SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(Multipole_const_bal_end)( SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
    SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(Multipole_const_reserved_bal_end)( SIXTRL_BE_ARGPTR_DEC const
    NS(Multipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(Multipole_bal_begin)( SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
    SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(Multipole_bal_end)( SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
    SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(Multipole_reserved_bal_end)( SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Multipole_default_bal_value)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Multipole_bal)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const bal_index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_bal_value)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const idx, NS(be_real_type) const value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_bal)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT values_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_all_bal_values)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const value ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Multipole_knl)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole,
    NS(be_order_type) const knl_index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Multipole_default_knl_value)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_knl_value)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const idx, NS(be_real_type) const value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_knl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT values_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_all_knl_values)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const value ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Multipole_ksl)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole,
    NS(be_order_type) const ksl_index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_type) NS(Multipole_default_ksl_value)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_ksl_value)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const idx, NS(be_real_type) const value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_ksl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT values_begin
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_set_all_ksl_values)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const value ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(Multipole_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(Multipole_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(Multipole_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(Multipole_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(Multipole_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_preset)( SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_init)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_order_type) const max_order, NS(be_order_type) const order,
    NS(be_real_type) const length,
    NS(be_real_type) const hxl, NS(be_real_type) const hyl,
    NS(be_addr_type) const bal_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT destination,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
        SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_multipole)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct
    NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_cobj_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT offsets,
    NS(size_type) const max_num_offsets,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_cobj_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT counts,
    NS(size_type) const max_num_counts,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_cobj_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT sizes,
    NS(size_type) const max_num_sizes,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(Multipole_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size, NS(be_order_type) const order_max,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(Multipole)*
NS(Multipole_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size, NS(be_order_type) const max_order
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(Multipole)*
NS(Multipole_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size, NS(be_order_type) const max_order,
    NS(be_order_type) const order, NS(be_real_type) const length,
    NS(be_real_type) const hxl, NS(be_real_type) const hyl,
    NS(be_addr_type) const bal_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(Multipole)*
NS(Multipole_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(Multipole_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(be_order_type) const order_max,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_cbuffer_new)( SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)*
    SIXTRL_RESTRICT buffer, NS(be_order_type) const order_max );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_order_type) const max_order, NS(be_order_type) const order,
    NS(be_real_type) const length,
    NS(be_real_type) const hxl, NS(be_real_type) const hyl,
    NS(be_addr_type) const bal_addr );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT orig );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type) NS(Multipole_cobj_type_id_ext)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Multipole_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Multipole_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(Multipole_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(Multipole_cobj_required_num_bytes_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_preset_ext)( SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(Multipole_clear_ext)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Multipole_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(be_order_type) const order_max,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_order_type) const order_max );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(be_order_type) const max_order, NS(be_order_type) const order,
    NS(be_real_type) const length,
    NS(be_real_type) const hxl, NS(be_real_type) const hyl,
    NS(be_addr_type) const bal_addr );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_cobj_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp );

#endif /* !defined( _GPUCODE ) */
#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct CObjectsTraits< ::NS(Multipole) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_MULTIPOLE;
    };

    template<> struct CObjectsNumPointersTraits< ::NS(Multipole) >
    {
        static constexpr cobj_size_type NUM_POINTERS =
            SIXTRL_CXX_NAMESPACE::cobj_size_type{ 1u };
    };

    template<> struct CObjectsActualHandleSizeTraits< ::NS(Multipole) >
    {
        SIXTRL_FN static cobj_size_type HANDLE_SIZE(
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Multipole_cobj_actual_handle_size)( slot_size ); }
    };

    template<> struct CObjectsReservedHandleSizeTraits< ::NS(Multipole) >
    {
        SIXTRL_FN static cobj_size_type HANDLE_SIZE(
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Multipole_cobj_reserved_handle_size)( slot_size ); }
    };

    template<> struct CObjectsRequiredNumBytesTraits< ::NS(Multipole) >
    {
        SIXTRL_FN static cobj_size_type REQUIRED_NUM_BYTES(
        SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(Multipole) *const SIXTRL_RESTRICT mp,
        cobj_size_type slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Multipole_cobj_required_num_bytes)( mp, slot_size ); }
    };

    template<> struct CObjectsAttributesOffsetsTraits< ::NS(Multipole) >
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT offsets,
            cobj_size_type const max_num_offsets,
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(Multipole) *const
                SIXTRL_RESTRICT mp,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Multipole_cobj_attributes_offsets)( offsets,
                max_num_offsets, mp, slot_size ); }
    };

    template<> struct CObjectsAttributesSizesTraits< ::NS(Multipole) >
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT sizes,
            cobj_size_type const max_num_sizes,
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(Multipole) *const
                SIXTRL_RESTRICT mp,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Multipole_cobj_attributes_sizes)(
                sizes, max_num_sizes, mp, slot_size ); }
    };

    template<> struct CObjectsAttributesCountsTraits< ::NS(Multipole) >
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT counts,
            cobj_size_type const max_num_counts,
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(Multipole) *const
                SIXTRL_RESTRICT mp,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(Multipole_cobj_attributes_counts)(
                counts, max_num_counts, mp, slot_size ); }
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_MULTIPOLE > {
            typedef ::NS(Multipole) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* ************************************************************************* */
/* *****          Implementation of C inline functions                   *** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/internal/math_factorial.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(be_order_type) NS(Multipole_max_order)( SIXTRL_BE_ARGPTR_DEC
    const NS(Multipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    return mp->max_order; }

SIXTRL_INLINE NS(be_order_type) NS(Multipole_default_max_order)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_order_type) )0; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_max_order)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_order_type) const max_order ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( max_order >= ( NS(be_order_type) )0u ) && ( mp != SIXTRL_NULLPTR ) &&
        ( NS(Multipole_order)( mp ) <= max_order ) ) {
        mp->max_order = max_order;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(be_size_type) NS(Multipole_bal_capacity)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT {
    return ( ( NS(be_order_type) )mp->max_order >= ( NS(be_order_type) )0u )
        ? ( NS(be_size_type) )( 2 * mp->max_order + 2 )
        : ( NS(be_size_type) )0u; }

SIXTRL_INLINE NS(be_size_type) NS(Multipole_set_bal_capacity)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const bal_capacity ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( bal_capacity >= ( NS(be_size_type) )0u ) &&
        ( mp != SIXTRL_NULLPTR ) && ( bal_capacity >= ( NS(be_size_type) )2u ) )
    {
        NS(be_order_type) const max_order =
            ( NS(be_order_type) )( ( bal_capacity - 2u ) >> 1u );
        status = NS(Multipole_set_max_order)( mp, max_order );
    }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_order_type) NS(Multipole_order)( SIXTRL_BE_ARGPTR_DEC const
    NS(Multipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); return mp->order; }

SIXTRL_INLINE NS(be_order_type) NS(Multipole_default_order)() SIXTRL_NOEXCEPT {
    return ( NS(be_order_type) )0u; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_order)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_order_type) const order ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( order >= ( NS(be_order_type) )0u ) && ( mp != SIXTRL_NULLPTR ) &&
        ( ( NS(Multipole_max_order)( mp ) >= order ) ||
          ( NS(Multipole_max_order)( mp ) == ( NS(be_order_type) )0u ) ) ) {
        mp->order = order;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(be_size_type) NS(Multipole_bal_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( NS(Multipole_order)( mp ) >= ( NS(be_order_type) )0u );
    return ( NS(be_size_type) )( 2 * NS(Multipole_order)( mp ) + 2 ); }

SIXTRL_INLINE NS(be_size_type) NS(Multipole_set_bal_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const bal_length ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( bal_length >= ( NS(be_size_type) )0u ) &&
        ( mp != SIXTRL_NULLPTR ) && ( bal_length >= ( NS(be_size_type) )2u ) ) {
        NS(be_order_type) const order = ( NS(be_order_type) )(
            ( bal_length - 2u ) >> 1 );
        status = NS(Multipole_set_order)( mp, order ); }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(Multipole_length)( SIXTRL_BE_ARGPTR_DEC const
    NS(Multipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); return mp->length; }

SIXTRL_INLINE NS(be_real_type) NS(Multipole_default_length)() SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const length ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); mp->length = length;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(Multipole_hxl)( SIXTRL_BE_ARGPTR_DEC const
    NS(Multipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); return mp->hxl; }

SIXTRL_INLINE NS(be_real_type) NS(Multipole_default_hxl)() SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_hxl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const hxl ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); mp->hxl = hxl;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(be_real_type) NS(Multipole_hyl)( SIXTRL_BE_ARGPTR_DEC const
    NS(Multipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); return mp->hyl; }

SIXTRL_INLINE NS(be_real_type) NS(Multipole_default_hyl)() SIXTRL_NOEXCEPT {
    return ( NS(be_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_hyl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const hyl ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); mp->hyl = hyl;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_addr_type) NS(Multipole_bal_addr)( SIXTRL_BE_ARGPTR_DEC
    const NS(Multipole) *const SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); return mp->bal_addr; }

SIXTRL_INLINE NS(be_addr_type) NS(Multipole_default_bal_addr)() SIXTRL_NOEXCEPT {
    return  ( NS(be_addr_type) )SIXTRL_NULL_ADDR; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_bal_addr)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_addr_type) const bal_addr ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR ); mp->bal_addr = bal_addr;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(Multipole_const_bal_begin)( SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* )( uintptr_t
        )NS(Multipole_bal_addr)( mp ); }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(Multipole_const_bal_end)( SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* ptr_end =
        NS(Multipole_const_bal_begin)( mp );
    if( ptr_end != SIXTRL_NULLPTR ) {
        ptr_end = ptr_end + NS(Multipole_bal_length)( mp ); }
    return ptr_end; }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const*
NS(Multipole_const_reserved_bal_end)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp
) SIXTRL_NOEXCEPT {
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* ptr_end =
        NS(Multipole_const_bal_begin)( mp );
    if( ptr_end != SIXTRL_NULLPTR ) {
        ptr_end = ptr_end + NS(Multipole_bal_capacity)( mp ); }
    return ptr_end; }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* NS(Multipole_bal_begin)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
        )NS(Multipole_const_bal_begin)( mp ); }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* NS(Multipole_bal_end)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
        )NS(Multipole_const_bal_end)( mp ); }

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
NS(Multipole_reserved_bal_end)( SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
    SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_DATAPTR_DEC NS(be_real_type)*
        )NS(Multipole_const_reserved_bal_end)( mp ); }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(Multipole_bal)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const bal_index ) SIXTRL_NOEXCEPT {
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* ptr_begin =
        NS(Multipole_const_bal_begin)( mp );
    SIXTRL_ASSERT( ptr_begin != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( bal_index < NS(Multipole_bal_length)( mp ) );
    return ptr_begin[ bal_index ]; }

SIXTRL_INLINE NS(be_real_type) NS(Multipole_default_bal_value)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_bal_value)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(cobj_size_type) const idx, NS(be_real_type) const val ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal = NS(Multipole_bal_begin)( mp );
    if( ( bal != SIXTRL_NULLPTR ) && ( idx < NS(Multipole_bal_length)( mp ) ) )
    {
        bal[ idx ] = val;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_bal)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT in_bal_it
) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_it = NS(Multipole_bal_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_it  != SIXTRL_NULLPTR ) &&
        ( in_bal_it != SIXTRL_NULLPTR ) ) {
        bal_iterator_type bal_end = bal_it + NS(Multipole_bal_length)( mp );
        for( ; bal_it != bal_end ; ++bal_it, ++in_bal_it ) *bal_it = *in_bal_it;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_all_bal_values)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const value ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_it  = NS(Multipole_bal_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_it  != SIXTRL_NULLPTR ) ) {
        bal_iterator_type bal_end = bal_it + NS(Multipole_bal_length)( mp );
        for( ; bal_it != bal_end ; ++bal_it ) *bal_it = value;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(Multipole_knl)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(be_order_type) const knl_index ) SIXTRL_NOEXCEPT {
    NS(be_size_type) const idx = ( NS(be_size_type) )( 2 * knl_index );
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( knl_index >= ( NS(be_order_type) )0 );
    SIXTRL_ASSERT( knl_index <= NS(Multipole_order)( mp ) );
    SIXTRL_ASSERT( idx < NS(Multipole_bal_length)( mp ) );
    return NS(Multipole_bal)( mp, idx ) * NS(Math_factorial)( knl_index ); }

SIXTRL_INLINE NS(be_real_type) NS(Multipole_default_knl_value)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_knl_value)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const k_idx, NS(be_real_type) const knl_value
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal = NS(Multipole_bal_begin)( mp );
    NS(be_size_type) const bal_index = ( NS(be_size_type) )( 2 * k_idx );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal != SIXTRL_NULLPTR ) &&
        ( bal_index < NS(Multipole_bal_length)( mp ) ) ) {
        bal[ bal_index ] = knl_value / NS(Math_factorial)( k_idx );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_knl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT knl_begin
) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_values = NS(Multipole_bal_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_values != SIXTRL_NULLPTR ) &&
        ( knl_begin != SIXTRL_NULLPTR ) ) {
        NS(be_size_type) const nn = NS(Multipole_bal_length)( mp );
        NS(be_order_type) k_idx = ( NS(be_order_type) )0;
        NS(be_size_type) ii = ( NS(be_size_type) )0;
        for( ; ii < nn ; ii += 2u, ++k_idx )
            bal_values[ ii ] = knl_begin[ k_idx ] / NS(Math_factorial)( k_idx );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_all_knl_values)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const knl_value ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_values = NS(Multipole_bal_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_values != SIXTRL_NULLPTR ) ) {
        NS(be_size_type) const nn = NS(Multipole_bal_length)( mp );
        NS(be_order_type) k_idx = ( NS(be_order_type) )0;
        NS(be_size_type) ii = ( NS(be_size_type) )0;
        for( ; ii < nn ; ii += 2u, ++k_idx )
            bal_values[ ii ] = knl_value / NS(Math_factorial)( k_idx );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(be_real_type) NS(Multipole_ksl)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(be_order_type) const ksl_index ) SIXTRL_NOEXCEPT {
    NS(be_size_type) const idx = ( NS(be_size_type) )( 2 * ksl_index + 1 );
    SIXTRL_ASSERT( mp != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ksl_index >= ( NS(be_order_type) )0 );
    SIXTRL_ASSERT( ksl_index <= NS(Multipole_order)( mp ) );
    return NS(Multipole_bal)( mp, idx ) * NS(Math_factorial)( ksl_index ); }

SIXTRL_INLINE NS(be_real_type) NS(Multipole_default_ksl_value)(
    ) SIXTRL_NOEXCEPT { return ( NS(be_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_ksl_value)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_size_type) const k_idx, NS(be_real_type) const ksl_value
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal = NS(Multipole_bal_begin)( mp );
    NS(be_size_type) const bal_index = ( NS(be_size_type) )( 2 * k_idx + 1 );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal != SIXTRL_NULLPTR ) &&
        ( bal_index < NS(Multipole_bal_length)( mp ) ) ) {
        bal[ bal_index ] = ksl_value / NS(Math_factorial)( k_idx );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_ksl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    SIXTRL_BE_DATAPTR_DEC NS(be_real_type) const* SIXTRL_RESTRICT ksl_begin
) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_values = NS(Multipole_bal_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_values != SIXTRL_NULLPTR ) &&
        ( ksl_begin != SIXTRL_NULLPTR ) ) {
        NS(be_size_type) const nn = NS(Multipole_bal_length)( mp );
        NS(be_order_type) k_idx = ( NS(be_order_type) )0;
        NS(be_size_type) ii = ( NS(be_size_type) )1;
        for( ; ii < nn ; ii += 2u, ++k_idx )
            bal_values[ ii ] = ksl_begin[ k_idx ] / NS(Math_factorial)( k_idx );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Multipole_set_all_ksl_values)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_real_type) const ksl_value ) SIXTRL_NOEXCEPT {
    typedef SIXTRL_BE_DATAPTR_DEC NS(be_real_type)* bal_iterator_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    bal_iterator_type bal_values = NS(Multipole_bal_begin)( mp );
    if( ( mp != SIXTRL_NULLPTR ) && ( bal_values != SIXTRL_NULLPTR ) ) {
        NS(be_size_type) const nn = NS(Multipole_bal_length)( mp );
        NS(be_order_type) k_idx = ( NS(be_order_type) )0;
        NS(be_size_type) ii = ( NS(be_size_type) )1;
        for( ; ii < nn ; ii += 2u, ++k_idx )
            bal_values[ ii ] = ksl_value / NS(Math_factorial)( k_idx );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(Multipole_cobj_type_id)() SIXTRL_NOEXCEPT
{ return ( NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_MULTIPOLE; }

SIXTRL_INLINE NS(cobj_size_type) NS(Multipole_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )1u; }

SIXTRL_INLINE NS(cobj_size_type) NS(Multipole_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(Multipole) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(Multipole_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(Multipole_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(Multipole_cobj_required_num_bytes)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_t;
    st_size_t num_bytes = ( st_size_t )0u;

    if( slot_size == ( st_size_t )0u )
        slot_size =  ( st_size_t )SIXTRL_DEFAULT_ALIGN;

    SIXTRL_ARGPTR_DEC st_size_t SIZES[ 1 ];
    SIXTRL_ARGPTR_DEC st_size_t COUNTS[ 1 ];

    NS(status_type) status = NS(Multipole_cobj_attributes_sizes)( &SIZES[ 0 ],
        NS(Multipole_cobj_num_dataptrs)(), mp, slot_size );

    if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        status = NS(Multipole_cobj_attributes_counts)( &COUNTS[ 0 ],
            NS(Multipole_cobj_num_dataptrs)(), mp, slot_size );

    if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        num_bytes = NS(CObjFlatBuffer_predict_required_num_bytes)(
            NS(Multipole_cobj_reserved_handle_size)( slot_size ),
            NS(Multipole_cobj_num_dataptrs)(),
            &SIZES[ 0 ], &COUNTS[ 0 ], slot_size );

    return num_bytes; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole)* NS(Multipole_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    if( mp != SIXTRL_NULLPTR ) NS(Multipole_clear)( mp );
    return mp; }

SIXTRL_INLINE NS(status_type) NS(Multipole_init)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp,
    NS(be_order_type) const max_order, NS(be_order_type) const order,
    NS(be_real_type) const length, NS(be_real_type) const hxl,
    NS(be_real_type) const hyl, NS(be_addr_type) const bal_addr ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( mp != SIXTRL_NULLPTR ) && ( max_order >= ( NS(be_order_type) )0u ) &&
        ( order >= ( NS(be_order_type) )0u ) && ( max_order >= order ) ) {
        mp->max_order = max_order;
        status = NS(Multipole_set_order)( mp, order ) |
                 NS(Multipole_set_length)( mp, length ) |
                 NS(Multipole_set_hxl)( mp, hxl ) |
                 NS(Multipole_set_hyl)( mp, hyl ) |
                 NS(Multipole_set_bal_addr)( mp, bal_addr ); }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Multipole_clear)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT mp ) SIXTRL_NOEXCEPT {
    return NS(Multipole_init)( mp, NS(Multipole_default_max_order)(),
        NS(Multipole_default_order)(), NS(Multipole_default_length)(),
            NS(Multipole_default_hxl)(), NS(Multipole_default_hyl)(),
                NS(Multipole_default_bal_addr)() ); }

SIXTRL_INLINE NS(status_type) NS(Multipole_copy)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT dst,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) ) {
        if( ( src != dst ) &&
            ( NS(Multipole_order)( src ) <= NS(Multipole_max_order)( dst ) ) ) {
            status = NS(Multipole_set_order)( dst, NS(Multipole_order)( src ) );
            status |= NS(Multipole_set_length)(
                dst, NS(Multipole_length)( src ) );
            status |= NS(Multipole_set_hxl)(
                dst, NS(Multipole_hxl)( src ) );
            status |= NS(Multipole_set_hyl)(
                dst, NS(Multipole_hyl)( src ) );
            status |= NS(Multipole_set_bal)( dst,
                        NS(Multipole_const_bal_begin)( src ) ); }
        else if( src == dst ) {
            status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    }
    return status; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_multipole)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(Multipole_cobj_type_id)(), NS(Multipole_cobj_actual_handle_size)(
            ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return ( NS(CObjIndex_is_multipole)( obj ) )
        ? ( SIXTRL_BE_ARGPTR_DEC NS(Multipole) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole)* NS(Multipole_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
        )NS(Multipole_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(Multipole_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(Multipole_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Multipole_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole)* NS(Multipole_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Multipole_from_cobj_index)( NS(CBuffer_index_at)( buffer, idx ) );
}

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(status_type) NS(Multipole_cobj_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT offsets,
    NS(size_type) const max_num_offsets,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(Multipole_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;
    if( ( mp != SIXTRL_NULLPTR ) && ( offsets != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_offsets >= ndataptrs ) &&
        ( ndataptrs == ( ( st_size_t )1u ) ) ) {
        offsets[ ii++ ] =
            ( st_size_t )2 * NS(CObjFlatBuffer_slot_based_size)( sizeof(
                NS(be_order_type) ), slot_size ) +
            ( st_size_t )3 * NS(CObjFlatBuffer_slot_based_size)( sizeof(
                NS(be_real_type) ), slot_size );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

    if( ( offsets != SIXTRL_NULLPTR ) &&
        ( max_num_offsets > ( st_size_t )0u ) && ( ii < max_num_offsets ) ) {
        while( ii < max_num_offsets ) { offsets[ ii++ ] = ( st_size_t )0u; } }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Multipole_cobj_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT counts,
    NS(size_type) const max_num_counts,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(Multipole_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;
    if( ( mp != SIXTRL_NULLPTR ) && ( counts != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_counts >= ndataptrs ) &&
        ( ndataptrs == ( ( st_size_t )1u ) ) ) {
        counts[ ii++ ] = NS(Multipole_bal_capacity)( mp );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

    if( ( counts != SIXTRL_NULLPTR ) &&
        ( max_num_counts > ( st_size_t )0u ) && ( ii < max_num_counts ) ) {
        while( ii < max_num_counts ) { counts[ ii++ ] = ( st_size_t )0u; } }
    return status; }

SIXTRL_INLINE NS(status_type) NS(Multipole_cobj_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT sizes,
    NS(size_type) const max_num_sizes,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT mp,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(Multipole_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;
    if( ( mp != SIXTRL_NULLPTR ) && ( sizes != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_sizes >= ndataptrs ) &&
        ( ndataptrs == ( ( st_size_t )1u ) ) ) {
        sizes[ ii++ ] = sizeof( NS(be_real_type) );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

    if( ( sizes != SIXTRL_NULLPTR ) &&
        ( max_num_sizes > ( st_size_t )0u ) && ( ii < max_num_sizes ) ) {
        while( ii < max_num_sizes ) { sizes[ ii++ ] = ( st_size_t )0u; } }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Multipole_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size, NS(be_order_type) const max_order,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT {
    bool can_be_added = false;
    SIXTRL_CBUFFER_ARGPTR_DEC NS(Multipole) mp;
    NS(status_type) status = NS(Multipole_init)( &mp, max_order, max_order,
        NS(Multipole_default_length)(), NS(Multipole_default_hxl)(),
            NS(Multipole_default_hyl)(), NS(Multipole_default_bal_addr)() );

    if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
        ( NS(Multipole_cobj_num_dataptrs)() == ( NS(cobj_size_type) )1u ) &&
        ( slot_size > ( NS(cobj_size_type) )0u ) &&
        ( max_order >= ( NS(be_order_type) )0u ) )
    {
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) SIZES[ 1 ];
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) COUNTS[ 1 ];

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(Multipole_cobj_attributes_sizes)(
                &SIZES[ 0 ], 1u, &mp, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(Multipole_cobj_attributes_counts)(
                &COUNTS[ 0 ], 1u, &mp, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            can_be_added = NS(CObjFlatBuffer_can_add_copy_of_object)( buffer,
                slot_size, NS(Multipole_cobj_reserved_handle_size)( slot_size ),
                NS(Multipole_cobj_num_dataptrs)(), &SIZES[ 0 ], &COUNTS[ 0 ],
                requ_buffer_size, requ_n_slots, requ_n_objects,
                requ_n_dataptrs ); }
    }
    return can_be_added; }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(Multipole)*
NS(Multipole_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size, NS(be_order_type) const order_max
) SIXTRL_NOEXCEPT {
    SIXTRL_BE_ARGPTR_DEC NS(Multipole) elem;
    NS(status_type) status = NS(Multipole_clear)( &elem );
    status |= NS(Multipole_set_max_order)( &elem, order_max );
    status |= NS(Multipole_set_order)( &elem, order_max );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(Multipole_cobj_flat_buffer_add_copy)( buffer, slot_size, &elem )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(Multipole)*
NS(Multipole_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size, NS(be_order_type) const max_order,
    NS(be_order_type) const order, NS(be_real_type) const length,
    NS(be_real_type) const hxl, NS(be_real_type) const hyl,
    NS(be_addr_type) const bal_addr )  SIXTRL_NOEXCEPT {
    SIXTRL_BE_ARGPTR_DEC NS(Multipole) elem;
    NS(status_type) status = NS(Multipole_init)(
        &elem, max_order, order, length, hxl, hyl, bal_addr  );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(Multipole_cobj_flat_buffer_add_copy)( buffer, slot_size, &elem )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(Multipole)*
NS(Multipole_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_DATAPTR_DEC NS(Multipole)* ptr_added_elem = SIXTRL_NULLPTR;

    if( ( NS(Multipole_cobj_num_dataptrs)() == ( NS(cobj_size_type) )1u ) &&
        ( slot_size > ( NS(cobj_size_type) )0u ) &&
        ( NS(Multipole_max_order)( orig ) >= ( NS(be_order_type) )0u ) &&
        ( NS(Multipole_order)( orig ) >= ( NS(be_order_type) )0u ) &&
        ( NS(Multipole_order)( orig ) <= NS(Multipole_max_order)( orig ) ) )
    {
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) OFFSETS[ 1 ];
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) SIZES[ 1 ];
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) COUNTS[ 1 ];

        NS(status_type) status = NS(Multipole_cobj_attributes_sizes)(
                &SIZES[ 0 ], 1u, orig, slot_size );

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(Multipole_cobj_attributes_counts)(
                &COUNTS[ 0 ], 1u, orig, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(Multipole_cobj_attributes_offsets)(
                &OFFSETS[ 0 ], 1u, orig, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            ptr_added_elem = ( SIXTRL_CBUFFER_DATAPTR_DEC NS(Multipole)* )(
                uintptr_t )NS(CObjIndex_begin_addr)(
                    NS(CObjFlatBuffer_add_copy_of_object)( buffer, slot_size,
                        orig, NS(Multipole_cobj_reserved_handle_size)(
                            slot_size ), NS(Multipole_cobj_type_id)(),
                        NS(Multipole_cobj_num_dataptrs)(), &OFFSETS[ 0 ],
                        &SIZES[ 0 ], &COUNTS[ 0 ], true ) );
        }
    }
    return ptr_added_elem; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Multipole_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(be_order_type) const max_order,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(Multipole_cobj_flat_buffer_can_be_added)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ), max_order,
        requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole)* NS(Multipole_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_order_type) const max_order ) {
    SIXTRL_BE_ARGPTR_DEC NS(Multipole) elem;
    NS(status_type) status = NS(Multipole_clear)( &elem );
    status |= NS(Multipole_set_max_order)( &elem, max_order );
    status |= NS(Multipole_set_order)( &elem, max_order );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(Multipole_cbuffer_add_copy)( buffer, &elem )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole)* NS(Multipole_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(be_order_type) const max_order, NS(be_order_type) const order,
    NS(be_real_type) const length, NS(be_real_type) const hxl,
    NS(be_real_type) const hyl, NS(be_addr_type) const bal_addr ) {
    SIXTRL_BE_ARGPTR_DEC NS(Multipole) elem;
    NS(status_type) status = NS(Multipole_init)(
        &elem, max_order, order, length, hxl, hyl, bal_addr );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(Multipole_cbuffer_add_copy)( buffer, &elem ) : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT orig ) {
    SIXTRL_CBUFFER_DATAPTR_DEC NS(Multipole)* ptr_added_elem = SIXTRL_NULLPTR;

    if( ( NS(Multipole_cobj_num_dataptrs)() == ( NS(cobj_size_type) )1u ) &&
        ( NS(Multipole_max_order)( orig ) >= ( NS(be_order_type) )0u ) &&
        ( NS(Multipole_order)( orig ) >= ( NS(be_order_type) )0u ) &&
        ( NS(Multipole_order)( orig ) <= NS(Multipole_max_order)( orig ) ) )
    {
        NS(cobj_size_type) const slot_size = NS(CBuffer_slot_size)( buffer );
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) OFFSETS[ 1 ];
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) SIZES[ 1 ];
        SIXTRL_ARGPTR_DEC NS(cobj_size_type) COUNTS[ 1 ];

        NS(status_type) status = NS(Multipole_cobj_attributes_sizes)(
                &SIZES[ 0 ], 1u, orig, slot_size );

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(Multipole_cobj_attributes_counts)(
                &COUNTS[ 0 ], 1u, orig, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(Multipole_cobj_attributes_offsets)(
                &OFFSETS[ 0 ], 1u, orig, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            ptr_added_elem = ( SIXTRL_CBUFFER_DATAPTR_DEC NS(Multipole)* )(
                uintptr_t )NS(CObjIndex_begin_addr)(
                    NS(CBuffer_add_copy_of_object)( buffer, orig,
                        NS(Multipole_cobj_reserved_handle_size)( slot_size ),
                        NS(Multipole_cobj_type_id)(),
                        NS(Multipole_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );
        }
    }
    return ptr_added_elem; }

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BE_MULTIPOLE_BEAM_ELEMENT_MULTIPOLE_H__ */
