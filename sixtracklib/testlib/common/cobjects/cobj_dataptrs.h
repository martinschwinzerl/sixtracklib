#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_DATAPTRS_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_DATAPTRS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_COBJECTS_TYPE_ID_TEST_DATAPTRS )
    #define SIXTRL_COBJECTS_TYPE_ID_TEST_DATAPTRS 32369
#endif /* !defined( SIXTRL_COBJECTS_TYPE_ID_TEST_DATAPTRS ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if !defined( _GPUCODE )
SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_obj_id_type)
    NS(COBJECTS_TYPE_ID_TEST_DATAPTRS) = ( NS(cobj_obj_id_type)
        )SIXTRL_COBJECTS_TYPE_ID_TEST_DATAPTRS;
#endif /* !defined( _GPUCODE ) */

struct NS(CObjIndex);
struct NS(CBuffer);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(CObjTestDataptrs)
{
    NS(cobj_test_real_type)   a          SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(cobj_test_uint64_type) b_capacity SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(cobj_test_uint64_type) b_length   SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(cobj_test_addr_type)   b_addr     SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(cobj_test_uint64_type) c_capacity SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(cobj_test_uint64_type) c_length   SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(cobj_test_addr_type)   c_addr     SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(CObjTestDataptrs);

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_real_type) NS(CObjTestDataptrs_a)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT e ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_real_type)
NS(CObjTestDataptrs_default_a)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_a)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT e,
    NS(cobj_test_real_type) const a ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_b_capacity)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT e ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_b_length)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT e ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_addr_type)
NS(CObjTestDataptrs_b_addr)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT e ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_addr_type)
NS(CObjTestDataptrs_default_b_addr)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_b_addr)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT e,
    NS(cobj_test_addr_type) const b_addr ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_b_capacity)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_default_b_capacity)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_b_capacity)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_uint64_type) const b_capacity ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_b_length)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_default_b_length)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_b_length)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_uint64_type) const b_length ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_real_type) NS(CObjTestDataptrs_b)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const SIXTRL_RESTRICT e,
    NS(cobj_size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_real_type)
NS(CObjTestDataptrs_default_b)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_b)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_size_type) const index,
    NS(cobj_test_real_type) const b_value ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestDataptrs_b_const_begin)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestDataptrs_b_const_end)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestDataptrs_const_reserved_b_end)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestDataptrs_b_begin)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestDataptrs_b_end)( SIXTRL_TESTLIB_ARGPTR_DEC
    NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestDataptrs_reserved_b_end)( SIXTRL_TESTLIB_ARGPTR_DEC
    NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_all_b_values)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_real_type) const b_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_b_values)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(size_type) const num_b_values,
    SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
        SIXTRL_RESTRICT b_values ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_c_capacity)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT e ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_c_length)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT e ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_addr_type)
NS(CObjTestDataptrs_c_addr)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT e ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_addr_type)
NS(CObjTestDataptrs_default_c_addr)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_c_addr)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT e,
    NS(cobj_test_addr_type) const b_addr ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_c_capacity)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_default_c_capacity)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_c_capacity)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_uint64_type) const b_capacity ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_c_length)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_default_c_length)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_c_length)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_uint64_type) const b_length ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_real_type) NS(CObjTestDataptrs_c)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const SIXTRL_RESTRICT e,
    NS(cobj_size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_real_type)
NS(CObjTestDataptrs_default_c)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_c)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_size_type) const index,
    NS(cobj_test_real_type) const c_value ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestDataptrs_c_const_begin)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestDataptrs_c_const_end)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestDataptrs_const_reserved_c_end)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestDataptrs_c_begin)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestDataptrs_c_end)( SIXTRL_TESTLIB_ARGPTR_DEC
    NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestDataptrs_reserved_c_end)( SIXTRL_TESTLIB_ARGPTR_DEC
    NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_all_c_values)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_real_type) const c_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_set_c_values)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(size_type) const num_c_values,
    SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
        SIXTRL_RESTRICT c_values ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(CObjTestDataptrs_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(CObjTestDataptrs_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjTestDataptrs_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjTestDataptrs_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjTestDataptrs_cobj_required_num_bytes)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem, NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_preset)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_clear)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_init)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_real_type) const a,
    NS(cobj_test_uint64_type) b_capacity,
    NS(cobj_test_uint64_type) const b_length,
    NS(cobj_test_addr_type) const b_addr,
    NS(cobj_test_uint64_type) c_capacity,
    NS(cobj_test_uint64_type) const c_length,
    NS(cobj_test_addr_type) const c_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestDataptrs_copy)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT dest,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_cobj_test_dataptrs)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs) const*
NS(CObjTestDataptrs_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs) const*
NS(CObjTestDataptrs_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs) const*
NS(CObjTestDataptrs_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(CObjTestDataptrs_cobj_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT offsets,
    NS(size_type) const max_num_offsets,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(CObjTestDataptrs_cobj_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT counts,
    NS(size_type) const max_num_counts,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(CObjTestDataptrs_cobj_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT sizes,
    NS(size_type) const max_num_sizes,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjTestDataptrs_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const c_capacity,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const c_capacity ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    NS(cobj_test_real_type) const a,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const b_length,
    NS(cobj_test_addr_type) const b_addr,
    NS(cobj_test_uint64_type) const c_capacity,
    NS(cobj_test_uint64_type) const c_length,
    NS(cobj_test_addr_type) const c_addr )  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT orig ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjTestDataptrs_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const c_capacity,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const c_capacity );

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_test_real_type) const a,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const b_length,
    NS(cobj_test_addr_type) const b_addr,
    NS(cobj_test_uint64_type) const c_capacity,
    NS(cobj_test_uint64_type) const c_length,
    NS(cobj_test_addr_type) const c_addr );

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT orig );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TESTLIB_ARGPTR_DEC
NS(CObjTestDataptrs) const* NS(CObjTestDataptrs_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(CObjTestDataptrs_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(CObjTestDataptrs_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(CObjTestDataptrs_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(CObjTestDataptrs_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(CObjTestDataptrs_cobj_required_num_bytes_ext)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_preset_ext)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(CObjTestDataptrs_clear_ext)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(CObjTestDataptrs_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const c_capacity,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const c_capacity );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_test_real_type) const a,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const b_length,
    NS(cobj_test_addr_type) const b_addr,
    NS(cobj_test_uint64_type) const c_capacity,
    NS(cobj_test_uint64_type) const c_length,
    NS(cobj_test_addr_type) const c_addr );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem );

#endif /* !defined( _GPUCODE ) */

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(CObjTestDataptrs_compare)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT lhs,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type)
NS(CObjTestDataptrs_compare_with_tolerances)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT lhs,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT rhs,
    NS(cobj_test_real_type) const rel_tolerance,
    NS(cobj_test_real_type) const abs_tolerance ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(CObjTestDataptrs_difference)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT lhs,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT rhs,
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    #if !defined( _GPUCODE )
    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST cobj_obj_id_type
        COBJECTS_TYPE_ID_TEST_DATAPTRS = cobj_obj_id_type{
            SIXTRL_COBJECTS_TYPE_ID_TEST_DATAPTRS };
    #endif /* !defined( _GPUCODE ) */

    template<> struct CObjectsTraits< ::NS(CObjTestDataptrs) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_TEST_DATAPTRS;
    };

    template<> struct CObjectsNumPointersTraits< ::NS(CObjTestDataptrs) >
    {
        static constexpr cobj_size_type NUM_POINTERS =
            SIXTRL_CXX_NAMESPACE::cobj_size_type{ 2u };
    };

    template<> struct CObjectsActualHandleSizeTraits< ::NS(CObjTestDataptrs) >
    {
        SIXTRL_FN static cobj_size_type HANDLE_SIZE(
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(CObjTestDataptrs_cobj_actual_handle_size)( slot_size ); }
    };

    template<> struct CObjectsReservedHandleSizeTraits< ::NS(CObjTestDataptrs) >
    {
        SIXTRL_FN static cobj_size_type HANDLE_SIZE(
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(CObjTestDataptrs_cobj_reserved_handle_size)(
                slot_size ); }
    };

    template<> struct CObjectsRequiredNumBytesTraits< ::NS(CObjTestDataptrs) >
    {
        SIXTRL_FN static cobj_size_type REQUIRED_NUM_BYTES(
        SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(CObjTestDataptrs) *const
            SIXTRL_RESTRICT elem, cobj_size_type slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(CObjTestDataptrs_cobj_required_num_bytes)(
                elem, slot_size ); }
    };

    template<> struct CObjectsAttributesOffsetsTraits< ::NS(CObjTestDataptrs) >
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT offsets,
            cobj_size_type const max_num_offsets,
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(CObjTestDataptrs) *const
                SIXTRL_RESTRICT elem,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(CObjTestDataptrs_cobj_attributes_offsets)( offsets,
                max_num_offsets, elem, slot_size ); }
    };

    template<> struct CObjectsAttributesSizesTraits< ::NS(CObjTestDataptrs) >
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT sizes,
            cobj_size_type const max_num_sizes,
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(CObjTestDataptrs) *const
                SIXTRL_RESTRICT elem,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(CObjTestDataptrs_cobj_attributes_sizes)(
                sizes, max_num_sizes, elem, slot_size ); }
    };

    template<> struct CObjectsAttributesCountsTraits< ::NS(CObjTestDataptrs) >
    {
        SIXTRL_FN static cobj_status_type GET(
            SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT counts,
            cobj_size_type const max_num_counts,
            SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(CObjTestDataptrs) *const
                SIXTRL_RESTRICT elem,
            cobj_size_type const slot_size ) SIXTRL_NOEXCEPT {
            return ::NS(CObjTestDataptrs_cobj_attributes_counts)(
                counts, max_num_counts, elem, slot_size ); }
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_TEST_DATAPTRS > {
            typedef ::NS(CObjTestDataptrs) value_type; };

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */

/* ************************************************************************* */
/* *****          Implementation of C inline functions                   *** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/internal/type_arithmetic_helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined(  _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cobj_test_real_type) NS(CObjTestDataptrs_a)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR ); return obj->a; }

SIXTRL_INLINE NS(cobj_test_real_type)
NS(CObjTestDataptrs_default_a)() SIXTRL_NOEXCEPT {
    return ( NS(cobj_test_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_a)(
    SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestDataptrs)* SIXTRL_RESTRICT obj,
    NS(cobj_test_real_type) const a ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a = a;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cobj_test_uint64_type) NS(CObjTestDataptrs_b_capacity)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const SIXTRL_RESTRICT
        elem ) SIXTRL_NOEXCEPT {
            SIXTRL_ASSERT( elem != SIXTRL_NULLPTR ); return elem->b_capacity; }

SIXTRL_INLINE NS(cobj_test_uint64_type) NS(CObjTestDataptrs_default_b_capacity)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_test_uint64_type) )0u; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_b_capacity)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_uint64_type) const b_capacity ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR ); elem->b_capacity = b_capacity;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_b_length)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR ); return elem->b_length; }

SIXTRL_INLINE NS(cobj_test_uint64_type) NS(CObjTestDataptrs_default_b_length)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_test_uint64_type) )0u; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_b_length)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_uint64_type) const b_length ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR ); elem->b_length = b_length;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE NS(cobj_test_addr_type) NS(CObjTestDataptrs_b_addr)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR ); return elem->b_addr; }

SIXTRL_INLINE NS(cobj_test_addr_type) NS(CObjTestDataptrs_default_b_addr)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_test_addr_type) )0u; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_b_addr)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_addr_type) const b_addr ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( elem != SIXTRL_NULLPTR ) {
        elem->b_addr = b_addr;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(cobj_test_real_type) NS(CObjTestDataptrs_b)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem, NS(cobj_size_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( index < NS(CObjTestDataptrs_b_length)( elem ) );
    SIXTRL_ASSERT( NS(CObjTestDataptrs_b_const_begin)( elem ) !=
                   SIXTRL_NULLPTR );
    return NS(CObjTestDataptrs_b_const_begin)( elem )[ index ]; }

SIXTRL_INLINE NS(cobj_test_real_type) NS(CObjTestDataptrs_default_b)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_test_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_b)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_size_type) const index,
    NS(cobj_test_real_type) const b_value ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( elem != SIXTRL_NULLPTR ) &&
        ( NS(CObjTestDataptrs_b_addr)( elem ) !=
          ( NS(cobj_test_addr_type) )SIXTRL_NULL_ADDR ) &&
        ( index < NS(CObjTestDataptrs_b_length)( elem ) ) ) {
        NS(CObjTestDataptrs_b_begin)( elem )[ index ] = b_value;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestDataptrs_b_const_begin)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const* )(
        uintptr_t )NS(CObjTestDataptrs_b_addr)( elem ); }

SIXTRL_INLINE SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestDataptrs_b_const_end)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const* ptr =
        NS(CObjTestDataptrs_b_const_begin)( elem );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(CObjTestDataptrs_b_length)( elem );
    return ptr; }

SIXTRL_INLINE SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestDataptrs_const_reserved_b_end)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const* ptr =
        NS(CObjTestDataptrs_b_const_begin)( elem );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(CObjTestDataptrs_b_capacity)( elem );
    return ptr; }

SIXTRL_INLINE SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestDataptrs_b_begin)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type)* )( uintptr_t
        )NS(CObjTestDataptrs_b_addr)( elem ); }

SIXTRL_INLINE SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestDataptrs_b_end)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)* ptr =
        NS(CObjTestDataptrs_b_begin)( elem );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(CObjTestDataptrs_b_length)( elem );
    return ptr; }

SIXTRL_INLINE SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestDataptrs_reserved_b_end)( SIXTRL_TESTLIB_ARGPTR_DEC
    NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)* ptr =
        NS(CObjTestDataptrs_b_begin)( elem );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(CObjTestDataptrs_b_capacity)( elem );
    return ptr; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_all_b_values)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_real_type) const b_value ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( elem != SIXTRL_NULLPTR ) {
        NS(size_type) const nn = NS(CObjTestDataptrs_b_length)( elem );
        NS(size_type) ii = ( NS(size_type) )0u;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        for( ; ii < nn ; ++ii )
            status |= NS(CObjTestDataptrs_set_b)( elem, ii, b_value );
    }
    return status; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_b_values)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(size_type) const num_b_values,
    SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
        SIXTRL_RESTRICT b_values ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( elem != SIXTRL_NULLPTR ) && ( b_values != SIXTRL_NULLPTR ) ) {
        NS(size_type) ii = ( NS(size_type) )0u;
        NS(size_type) const nn =
            ( num_b_values < NS(CObjTestDataptrs_b_length)( elem ) )
                ? num_b_values : NS(CObjTestDataptrs_b_length)( elem );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        for( ; ii < nn ; ++ii )
            status |= NS(CObjTestDataptrs_set_b)( elem, ii, b_values[ ii ] );
    }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cobj_test_uint64_type) NS(CObjTestDataptrs_c_capacity)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const SIXTRL_RESTRICT
        elem ) SIXTRL_NOEXCEPT {
            SIXTRL_ASSERT( elem != SIXTRL_NULLPTR ); return elem->c_capacity; }

SIXTRL_INLINE NS(cobj_test_uint64_type) NS(CObjTestDataptrs_default_c_capacity)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_test_uint64_type) )0u; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_c_capacity)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_uint64_type) const c_capacity ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR ); elem->c_capacity = c_capacity;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE NS(cobj_test_uint64_type)
NS(CObjTestDataptrs_c_length)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR ); return elem->c_length; }

SIXTRL_INLINE NS(cobj_test_uint64_type) NS(CObjTestDataptrs_default_c_length)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_test_uint64_type) )0u; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_c_length)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_uint64_type) const c_length ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR ); elem->c_length = c_length;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

SIXTRL_INLINE NS(cobj_test_addr_type) NS(CObjTestDataptrs_c_addr)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR ); return elem->c_addr; }

SIXTRL_INLINE NS(cobj_test_addr_type) NS(CObjTestDataptrs_default_c_addr)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_test_addr_type) )0u; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_c_addr)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_addr_type) const c_addr ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( elem != SIXTRL_NULLPTR ) {
        elem->c_addr = c_addr;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(cobj_test_real_type) NS(CObjTestDataptrs_c)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem, NS(cobj_size_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( index < NS(CObjTestDataptrs_c_length)( elem ) );
    SIXTRL_ASSERT( NS(CObjTestDataptrs_c_const_begin)( elem ) !=
                   SIXTRL_NULLPTR );
    return NS(CObjTestDataptrs_c_const_begin)( elem )[ index ]; }

SIXTRL_INLINE NS(cobj_test_real_type) NS(CObjTestDataptrs_default_c)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_test_real_type) )0.0; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_c)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_size_type) const index,
    NS(cobj_test_real_type) const c_value ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( elem != SIXTRL_NULLPTR ) &&
        ( NS(CObjTestDataptrs_c_addr)( elem ) !=
          ( NS(cobj_test_addr_type) )SIXTRL_NULL_ADDR ) &&
        ( index < NS(CObjTestDataptrs_c_length)( elem ) ) ) {
        NS(CObjTestDataptrs_c_begin)( elem )[ index ] = c_value;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestDataptrs_c_const_begin)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const* )(
        uintptr_t )NS(CObjTestDataptrs_c_addr)( elem ); }

SIXTRL_INLINE SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestDataptrs_c_const_end)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const* ptr =
        NS(CObjTestDataptrs_c_const_begin)( elem );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(CObjTestDataptrs_c_length)( elem );
    return ptr; }

SIXTRL_INLINE SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestDataptrs_const_reserved_c_end)( SIXTRL_TESTLIB_ARGPTR_DEC const
    NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const* ptr =
        NS(CObjTestDataptrs_c_const_begin)( elem );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(CObjTestDataptrs_c_capacity)( elem );
    return ptr; }

SIXTRL_INLINE SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestDataptrs_c_begin)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type)* )( uintptr_t
        )NS(CObjTestDataptrs_c_addr)( elem ); }

SIXTRL_INLINE SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestDataptrs_c_end)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)* ptr =
        NS(CObjTestDataptrs_c_begin)( elem );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(CObjTestDataptrs_c_length)( elem );
    return ptr; }

SIXTRL_INLINE SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestDataptrs_reserved_c_end)( SIXTRL_TESTLIB_ARGPTR_DEC
    NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type)* ptr =
        NS(CObjTestDataptrs_c_begin)( elem );
    if( ptr != SIXTRL_NULLPTR )
        ptr = ptr + NS(CObjTestDataptrs_c_capacity)( elem );
    return ptr; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_all_c_values)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_real_type) const c_value ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( elem != SIXTRL_NULLPTR ) {
        NS(size_type) const nn = NS(CObjTestDataptrs_c_length)( elem );
        NS(size_type) ii = ( NS(size_type) )0u;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        for( ; ii < nn ; ++ii )
            status |= NS(CObjTestDataptrs_set_c)( elem, ii, c_value );
    }
    return status; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_set_c_values)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(size_type) const num_c_values,
    SIXTRL_TESTLIB_DATAPTR_DEC NS(cobj_test_real_type) const*
        SIXTRL_RESTRICT c_values ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( elem != SIXTRL_NULLPTR ) && ( c_values != SIXTRL_NULLPTR ) ) {
        NS(size_type) ii = ( NS(size_type) )0u;
        NS(size_type) const nn =
            ( num_c_values < NS(CObjTestDataptrs_c_length)( elem ) )
                ? num_c_values : NS(CObjTestDataptrs_c_length)( elem );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        for( ; ii < nn ; ++ii )
            status |= NS(CObjTestDataptrs_set_c)( elem, ii, c_values[ ii ] );
    }
    return status; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_obj_id_type)
NS(CObjTestDataptrs_cobj_type_id)() SIXTRL_NOEXCEPT
{ return ( NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_TEST_DATAPTRS; }

SIXTRL_INLINE NS(cobj_size_type) NS(CObjTestDataptrs_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )2u; }

SIXTRL_INLINE NS(cobj_size_type) NS(CObjTestDataptrs_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(CObjTestDataptrs) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CObjTestDataptrs_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(CObjTestDataptrs_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CObjTestDataptrs_cobj_required_num_bytes)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem, NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_t;
    st_size_t num_bytes = ( st_size_t )0u;

    if( slot_size == ( st_size_t )0u )
        slot_size =  ( st_size_t )SIXTRL_DEFAULT_ALIGN;

    SIXTRL_ARGPTR_DEC st_size_t SIZES[ 2 ];
    SIXTRL_ARGPTR_DEC st_size_t COUNTS[ 2 ];

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_ASSERT( NS(CObjTestDataptrs_cobj_num_dataptrs)() ==
        ( st_size_t )2u );

    status = NS(CObjTestDataptrs_cobj_attributes_sizes)(
        &SIZES[ 0 ], NS(CObjTestDataptrs_cobj_num_dataptrs)(), elem, slot_size );

    if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        status = NS(CObjTestDataptrs_cobj_attributes_counts)( &COUNTS[ 0 ],
            NS(CObjTestDataptrs_cobj_num_dataptrs)(), elem, slot_size );

    if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        num_bytes = NS(CObjFlatBuffer_predict_required_num_bytes)(
            NS(CObjTestDataptrs_cobj_reserved_handle_size)( slot_size ),
            NS(CObjTestDataptrs_cobj_num_dataptrs)(),
            &SIZES[ 0 ], &COUNTS[ 0 ], slot_size );

    return num_bytes; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_preset)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
    if( elem != SIXTRL_NULLPTR ) NS(CObjTestDataptrs_clear)( elem );
    return elem; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_init)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem,
    NS(cobj_test_real_type) const a,
    NS(cobj_test_uint64_type) b_capacity,
    NS(cobj_test_uint64_type) const b_length,
    NS(cobj_test_addr_type) const b_addr,
    NS(cobj_test_uint64_type) c_capacity,
    NS(cobj_test_uint64_type) const c_length,
    NS(cobj_test_addr_type) const c_addr ) SIXTRL_NOEXCEPT
{
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( elem != SIXTRL_NULLPTR )
    {
        if( b_length > b_capacity ) b_capacity = b_length;
        if( c_length > c_capacity ) c_capacity = c_length;

        status = NS(CObjTestDataptrs_set_a)( elem, a ) |
                 NS(CObjTestDataptrs_set_b_capacity)( elem, b_capacity ) |
                 NS(CObjTestDataptrs_set_b_length)( elem, b_length ) |
                 NS(CObjTestDataptrs_set_b_addr)( elem, b_addr ) |
                 NS(CObjTestDataptrs_set_c_capacity)( elem, c_capacity ) |
                 NS(CObjTestDataptrs_set_c_length)( elem, c_length ) |
                 NS(CObjTestDataptrs_set_c_addr)( elem, c_addr );
    } return status;
}

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_clear)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem
) SIXTRL_NOEXCEPT { return NS(CObjTestDataptrs_init)( elem,
        NS(CObjTestDataptrs_default_a)(),
        NS(CObjTestDataptrs_default_b_capacity)(),
        NS(CObjTestDataptrs_default_b_length)(),
        NS(CObjTestDataptrs_default_b_addr)(),
        NS(CObjTestDataptrs_default_c_capacity)(),
        NS(CObjTestDataptrs_default_c_length)(),
        NS(CObjTestDataptrs_default_c_addr)() ); }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_copy)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT dst,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) &&
        ( src != dst ) &&
        ( NS(CObjTestDataptrs_b_length)( src ) <=
          NS(CObjTestDataptrs_b_capacity)( dst ) ) &&
        ( NS(CObjTestDataptrs_c_length)( src ) <=
          NS(CObjTestDataptrs_c_capacity)( dst ) ) )
    {
        status = NS(CObjTestDataptrs_set_a)( dst,
                    NS(CObjTestDataptrs_a)( src ) );

        status |= NS(CObjTestDataptrs_set_b_length)( dst,
                    NS(CObjTestDataptrs_b_length)( src ) );

        status |= NS(CObjTestDataptrs_set_b_values)( dst,
                    NS(CObjTestDataptrs_b_length)( src ),
                    NS(CObjTestDataptrs_b_const_begin)( src ) );

        status |= NS(CObjTestDataptrs_set_c_length)( dst,
                    NS(CObjTestDataptrs_c_length)( src ) );

        status |= NS(CObjTestDataptrs_set_c_values)( dst,
                    NS(CObjTestDataptrs_c_length)( src ),
                    NS(CObjTestDataptrs_c_const_begin)( src ) );
    }
    else if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
             ( src == dst ) )
    {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }

    return status; }

/* ------------------------------------------------------------------------- */


SIXTRL_INLINE bool NS(CObjIndex_is_cobj_test_dataptrs)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(CObjTestDataptrs_cobj_type_id)(),
        NS(CObjTestDataptrs_cobj_actual_handle_size)(
            ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs) const*
NS(CObjTestDataptrs_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_cobj_test_dataptrs)( obj ) )
        ? ( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
        )NS(CObjTestDataptrs_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs) const*
NS(CObjTestDataptrs_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjTestDataptrs_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjTestDataptrs_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs) const*
NS(CObjTestDataptrs_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(CObjTestDataptrs_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(CObjTestDataptrs_from_cobj_index)(
        NS(CBuffer_index_at)( buffer, idx ) ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_cobj_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT offsets,
    NS(size_type) const max_num_offsets,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(CObjTestDataptrs_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;
    if( ( elem != SIXTRL_NULLPTR ) && ( offsets != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_offsets >= ndataptrs ) &&
        ( ndataptrs == ( ( st_size_t )2u ) ) )
    {
        st_size_t const b_addr_offset =
            ( st_size_t )1u * NS(CObjFlatBuffer_slot_based_size)( sizeof(
                NS(cobj_test_real_type) ), slot_size ) +
            ( st_size_t )2u * NS(CObjFlatBuffer_slot_based_size)( sizeof(
                NS(cobj_test_uint64_type) ), slot_size );

        st_size_t const c_addr_offset = b_addr_offset +
            ( st_size_t )1u * NS(CObjFlatBuffer_slot_based_size)( sizeof(
                NS(cobj_test_addr_type) ), slot_size ) +
            ( st_size_t )2u * NS(CObjFlatBuffer_slot_based_size)( sizeof(
                NS(cobj_test_uint64_type) ), slot_size );

        offsets[ ii++ ] = b_addr_offset;
        offsets[ ii++ ] = c_addr_offset;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }

    if( ( offsets != SIXTRL_NULLPTR ) &&
        ( max_num_offsets > ( st_size_t )0u ) && ( ii < max_num_offsets ) ) {
        while( ii < max_num_offsets ) { offsets[ ii++ ] = ( st_size_t )0u; } }
    return status; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_cobj_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT counts,
    NS(size_type) const max_num_counts,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(CObjTestDataptrs_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;
    if( ( elem != SIXTRL_NULLPTR ) && ( counts != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_counts >= ndataptrs ) &&
        ( ndataptrs == ( ( st_size_t )2u ) ) ) {
        counts[ ii++ ] = NS(CObjTestDataptrs_b_capacity)( elem );
        counts[ ii++ ] = NS(CObjTestDataptrs_c_capacity)( elem );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

    if( ( counts != SIXTRL_NULLPTR ) &&
        ( max_num_counts > ( st_size_t )0u ) && ( ii < max_num_counts ) ) {
        while( ii < max_num_counts ) { counts[ ii++ ] = ( st_size_t )0u; } }
    return status; }

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_cobj_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(size_type)* SIXTRL_RESTRICT sizes,
    NS(size_type) const max_num_sizes,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const SIXTRL_RESTRICT elem,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(size_type) st_size_t;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const ndataptrs = NS(CObjTestDataptrs_cobj_num_dataptrs)();
    st_size_t ii = ( st_size_t )0u;
    if( ( elem != SIXTRL_NULLPTR ) && ( sizes != SIXTRL_NULLPTR ) &&
        ( slot_size > ( st_size_t )0u ) && ( max_num_sizes >= ndataptrs ) &&
        ( ndataptrs == ( ( st_size_t )2u ) ) ) {
        sizes[ ii++ ] = sizeof( NS(cobj_test_real_type) );
        sizes[ ii++ ] = sizeof( NS(cobj_test_real_type) );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

    if( ( sizes != SIXTRL_NULLPTR ) &&
        ( max_num_sizes > ( st_size_t )0u ) && ( ii < max_num_sizes ) ) {
        while( ii < max_num_sizes ) { sizes[ ii++ ] = ( st_size_t )0u; } }
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(CObjTestDataptrs_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const c_capacity,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_t;
    bool can_be_added = false;
    st_size_t const N_PTRS = NS(CObjTestDataptrs_cobj_num_dataptrs)();
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CObjTestDataptrs) elem;
    NS(status_type) status = NS(CObjTestDataptrs_init)( &elem,
        NS(CObjTestDataptrs_default_a)(),
        b_capacity, b_capacity, NS(CObjTestDataptrs_default_b_addr)(),
        c_capacity, c_capacity, NS(CObjTestDataptrs_default_c_addr)() );

    if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
        ( slot_size > ( st_size_t )0u ) && ( N_PTRS == ( st_size_t )2u ) ) {
        SIXTRL_ARGPTR_DEC st_size_t SIZES[ 2 ];
        SIXTRL_ARGPTR_DEC st_size_t COUNTS[ 2 ];

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(CObjTestDataptrs_cobj_attributes_sizes)(
                &SIZES[ 0 ], N_PTRS, &elem, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(CObjTestDataptrs_cobj_attributes_counts)(
                &COUNTS[ 0 ], N_PTRS, &elem, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            can_be_added = NS(CObjFlatBuffer_can_add_copy_of_object)( buffer,
                slot_size, NS(CObjTestDataptrs_cobj_reserved_handle_size)( slot_size ),
                N_PTRS, &SIZES[ 0 ], &COUNTS[ 0 ], requ_buffer_size,
                requ_n_slots, requ_n_objects, requ_n_dataptrs ); }
    }
    return can_be_added; }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const c_capacity ) SIXTRL_NOEXCEPT {
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs) elem;
    NS(status_type) status = NS(CObjTestDataptrs_clear)( &elem );
    status |= NS(CObjTestDataptrs_set_b_capacity)( &elem, b_capacity );
    status |= NS(CObjTestDataptrs_set_c_capacity)( &elem, c_capacity );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(CObjTestDataptrs_cobj_flat_buffer_add_copy)(
            buffer, slot_size, &elem )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(cobj_test_real_type) const a,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const b_length,
    NS(cobj_test_addr_type) const b_addr,
    NS(cobj_test_uint64_type) const c_capacity,
    NS(cobj_test_uint64_type) const c_length,
    NS(cobj_test_addr_type) const c_addr )  SIXTRL_NOEXCEPT {
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs) elem;
    NS(status_type) status = NS(CObjTestDataptrs_init)(
        &elem, a, b_capacity, b_length, b_addr, c_capacity, c_length, c_addr );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(CObjTestDataptrs_cobj_flat_buffer_add_copy)(
            buffer, slot_size, &elem )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const SIXTRL_RESTRICT orig
) SIXTRL_NOEXCEPT {
    typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestDataptrs)* elem_pointer_type;
    typedef NS(size_type) st_size_t;
    elem_pointer_type ptr_added_elem = SIXTRL_NULLPTR;

    if( ( NS(CObjTestDataptrs_cobj_num_dataptrs)() == ( st_size_t )2u ) &&
        ( slot_size > ( st_size_t )0u ) &&
        ( NS(CObjTestDataptrs_b_capacity)( orig ) >=
          NS(CObjTestDataptrs_b_length)( orig ) ) &&
        ( NS(CObjTestDataptrs_c_capacity)( orig ) >=
          NS(CObjTestDataptrs_c_length)( orig ) ) )
    {
        st_size_t const N_PTRS = NS(CObjTestDataptrs_cobj_num_dataptrs)();

        SIXTRL_ARGPTR_DEC st_size_t OFFSETS[ 2 ];
        SIXTRL_ARGPTR_DEC st_size_t SIZES[ 2 ];
        SIXTRL_ARGPTR_DEC st_size_t COUNTS[ 2 ];

        NS(status_type) status = NS(CObjTestDataptrs_cobj_attributes_sizes)(
                &SIZES[ 0 ], N_PTRS, orig, slot_size );

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(CObjTestDataptrs_cobj_attributes_counts)(
                &COUNTS[ 0 ], N_PTRS, orig, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(CObjTestDataptrs_cobj_attributes_offsets)(
                &OFFSETS[ 0 ], N_PTRS, orig, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            ptr_added_elem = NS(CObjTestDataptrs_from_cobj_index)(
                NS(CObjFlatBuffer_add_copy_of_object)( buffer, slot_size, orig,
                    NS(CObjTestDataptrs_cobj_reserved_handle_size)( slot_size ),
                    NS(CObjTestDataptrs_cobj_type_id)(), N_PTRS, &OFFSETS[ 0 ],
                    &SIZES[ 0 ], &COUNTS[ 0 ], true ) );
        }
    }
    return ptr_added_elem; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(CObjTestDataptrs_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const c_capacity,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(CObjTestDataptrs_cobj_flat_buffer_can_be_added)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ), b_capacity,
        c_capacity, requ_buffer_size, requ_n_slots, requ_n_objects,
            requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const c_capacity ) {
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs) elem;
    NS(status_type) status = NS(CObjTestDataptrs_clear)( &elem );
    status |= NS(CObjTestDataptrs_set_b_capacity)( &elem, b_capacity );
    status |= NS(CObjTestDataptrs_set_c_capacity)( &elem, c_capacity );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(CObjTestDataptrs_cbuffer_add_copy)( buffer, &elem )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_test_real_type) const a,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const b_length,
    NS(cobj_test_addr_type) const b_addr,
    NS(cobj_test_uint64_type) const c_capacity,
    NS(cobj_test_uint64_type) const c_length,
    NS(cobj_test_addr_type) const c_addr ) {
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs) elem;
    NS(status_type) status = NS(CObjTestDataptrs_init)(
        &elem, a, b_capacity, b_length, b_addr, c_capacity, c_length, c_addr );
    return ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        ? NS(CObjTestDataptrs_cbuffer_add_copy)( buffer, &elem )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT orig ) {
    typedef NS(cobj_size_type) st_size_t;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestDataptrs)* elem_pointer_type;
    elem_pointer_type ptr_added_elem = SIXTRL_NULLPTR;
    st_size_t const N_PTRS = NS(CObjTestDataptrs_cobj_num_dataptrs)();
    st_size_t const slot_size = NS(CBuffer_slot_size)( buffer );

    if( ( buffer != SIXTRL_NULLPTR ) && ( N_PTRS == ( st_size_t )2u ) &&
        ( slot_size > ( st_size_t )0u ) )
    {
        SIXTRL_ARGPTR_DEC st_size_t OFFSETS[ 2 ];
        SIXTRL_ARGPTR_DEC st_size_t SIZES[ 2 ];
        SIXTRL_ARGPTR_DEC st_size_t COUNTS[ 2 ];

        NS(status_type) status = NS(CObjTestDataptrs_cobj_attributes_sizes)(
                &SIZES[ 0 ], N_PTRS, orig, slot_size );

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(CObjTestDataptrs_cobj_attributes_counts)(
                &COUNTS[ 0 ], N_PTRS, orig, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            status = NS(CObjTestDataptrs_cobj_attributes_offsets)(
                &OFFSETS[ 0 ], N_PTRS, orig, slot_size ); }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) {
            ptr_added_elem = NS(CObjTestDataptrs_from_cobj_index)(
                NS(CBuffer_add_copy_of_object)( buffer, orig,
                    NS(CObjTestDataptrs_cobj_reserved_handle_size)( slot_size ),
                    NS(CObjTestDataptrs_cobj_type_id)(), N_PTRS,
                    &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );
        }
    }
    return ptr_added_elem; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cmp_result_type) NS(CObjTestDataptrs_compare)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT lhs,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT {
    return NS(CObjTestDataptrs_compare_with_tolerances)( lhs, rhs,
        ( NS(cobj_test_real_type) )0.0,
        ( NS(cobj_test_real_type) )SIXTRL_REAL_TYPE_EPS ); }

SIXTRL_INLINE NS(cmp_result_type) NS(CObjTestDataptrs_compare_with_tolerances)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT lhs,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT rhs,
    NS(cobj_test_real_type) const rel_tolerance,
    NS(cobj_test_real_type) const abs_tolerance ) SIXTRL_NOEXCEPT {

    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            result = NS(Type_value_comp_result_with_tolerances)(
                lhs->a, rhs->a, rel_tolerance, abs_tolerance );

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(CObjTestDataptrs_b_length)( lhs ) !=
                  NS(CObjTestDataptrs_b_length)( rhs ) ) )
            {
                result = ( NS(CObjTestDataptrs_b_length)( lhs ) >
                           NS(CObjTestDataptrs_b_length)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == 0 ) &&
                ( NS(CObjTestDataptrs_b_const_begin)( lhs ) !=
                  NS(CObjTestDataptrs_b_const_begin)( rhs ) ) )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(CObjTestDataptrs_b_const_begin)( lhs ),
                    NS(CObjTestDataptrs_b_const_end)( lhs ),
                    NS(CObjTestDataptrs_b_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(CObjTestDataptrs_c_length)( lhs ) !=
                  NS(CObjTestDataptrs_c_length)( rhs ) ) )
            {
                result = ( NS(CObjTestDataptrs_c_length)( lhs ) >
                           NS(CObjTestDataptrs_c_length)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == 0 ) &&
                ( NS(CObjTestDataptrs_c_const_begin)( lhs ) !=
                  NS(CObjTestDataptrs_c_const_begin)( rhs ) ) )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(CObjTestDataptrs_c_const_begin)( lhs ),
                    NS(CObjTestDataptrs_c_const_end)( lhs ),
                    NS(CObjTestDataptrs_c_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;

    return result;
}

SIXTRL_INLINE NS(status_type) NS(CObjTestDataptrs_difference)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT lhs,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT rhs,
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) &&
        ( diff != lhs ) && ( diff != rhs ) && ( lhs != rhs ) &&
        ( NS(CObjTestDataptrs_b_length)( diff ) ==
          NS(CObjTestDataptrs_b_length)( lhs ) ) &&
        ( NS(CObjTestDataptrs_b_length)( diff ) ==
          NS(CObjTestDataptrs_b_length)( rhs ) ) &&
        ( NS(CObjTestDataptrs_c_length)( diff ) ==
          NS(CObjTestDataptrs_c_length)( lhs ) ) &&
        ( NS(CObjTestDataptrs_c_length)( diff ) ==
          NS(CObjTestDataptrs_c_length)( rhs ) ) )
    {
        status = NS(CObjTestDataptrs_set_a)( diff,
            NS(Type_subtract_real_type)(
                NS(CObjTestDataptrs_a)( lhs ),
                NS(CObjTestDataptrs_a)( rhs ) ) );

        status |= NS(Type_subtract_real_type_ranges)(
            NS(CObjTestDataptrs_b_begin)( diff ),
            NS(CObjTestDataptrs_b_const_begin)( lhs ),
            NS(CObjTestDataptrs_b_const_end)( lhs ),
            NS(CObjTestDataptrs_b_const_begin)( rhs ) );

        status |= NS(Type_subtract_real_type_ranges)(
            NS(CObjTestDataptrs_c_begin)( diff ),
            NS(CObjTestDataptrs_c_const_begin)( lhs ),
            NS(CObjTestDataptrs_c_const_end)( lhs ),
            NS(CObjTestDataptrs_c_const_begin)( rhs ) );
    }

    return status;
}

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_DATAPTRS_H__ */
