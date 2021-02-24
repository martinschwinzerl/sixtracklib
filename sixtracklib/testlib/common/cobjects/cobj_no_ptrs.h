#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_NO_PTRS_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_NO_PTRS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_COBJECTS_TYPE_ID_TEST_NO_PTRS )
    #define SIXTRL_COBJECTS_TYPE_ID_TEST_NO_PTRS 32368
#endif /* !defined( SIXTRL_COBJECTS_TYPE_ID_TEST_NO_PTRS ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if !defined( _GPUCODE )
SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST NS(cobj_obj_id_type)
    NS(COBJECTS_TYPE_ID_TEST_NO_PTRS) = ( NS(cobj_obj_id_type)
        )SIXTRL_COBJECTS_TYPE_ID_TEST_NO_PTRS;
#endif /* !defined( _GPUCODE ) */

struct NS(CObjIndex);
struct NS(CBuffer);

typedef struct SIXTRL_STRUCT_ALIGN( SIXTRL_DEFAULT_ALIGN ) NS(CObjTestNoPtrs)
{
    NS(cobj_test_real_type)   a      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(cobj_test_uint64_type) b      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(cobj_test_real_type)   c[ 6 ] SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
    NS(cobj_test_int64_type)  d      SIXTRL_FIELD_ALIGN( SIXTRL_DEFAULT_ALIGN );
}
NS(CObjTestNoPtrs);

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_real_type) NS(CObjTestNoPtrs_a)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_real_type)
NS(CObjTestNoPtrs_default_a)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestNoPtrs_set_a)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT e,
    NS(cobj_test_real_type) const a ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type) NS(CObjTestNoPtrs_b)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_uint64_type) NS(CObjTestNoPtrs_default_b)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestNoPtrs_set_b)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT e,
    NS(cobj_test_uint64_type) const b ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_real_type) NS(CObjTestNoPtrs_c)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT e,
    NS(size_type) const index ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_real_type) NS(CObjTestNoPtrs_default_c)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestNoPtrs_set_c)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT e,
    NS(size_type) const index,
    NS(cobj_test_real_type) const c_value ) SIXTRL_NOEXCEPT;

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(CObjTestNoPtrs_c_length)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN
SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestNoPtrs_c_const_begin)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN
SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestNoPtrs_c_const_end)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestNoPtrs_c_begin)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
    SIXTRL_RESTRICT e ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestNoPtrs_c_end)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
    SIXTRL_RESTRICT e ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_int64_type) NS(CObjTestNoPtrs_d)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_test_int64_type) NS(CObjTestNoPtrs_default_d)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestNoPtrs_set_d)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT e,
    NS(cobj_test_int64_type) const d ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */


SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_id_type) NS(CObjTestNoPtrs_cobj_type_id)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(CObjTestNoPtrs_cobj_num_dataptrs)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjTestNoPtrs_cobj_actual_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjTestNoPtrs_cobj_reserved_handle_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjTestNoPtrs_cobj_required_num_bytes)( SIXTRL_TESTLIB_ARGPTR_DEC
        const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT obj,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_preset)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestNoPtrs_clear)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestNoPtrs_init)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT obj,
    NS(cobj_test_real_type) const a, NS(cobj_test_uint64_type) const b,
    SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const* SIXTRL_RESTRICT c,
    NS(cobj_test_int64_type) const d ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(CObjTestNoPtrs_copy)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT dest,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjIndex_is_cobj_test_no_ptrs)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs) const*
NS(CObjTestNoPtrs_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    const struct NS(CObjIndex) *const obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC
    struct NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs) const*
NS(CObjTestNoPtrs_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT pbuffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs) const*
NS(CObjTestNoPtrs_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjTestNoPtrs_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    NS(cobj_test_real_type) const a, NS(cobj_test_uint64_type) const b,
    SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const* SIXTRL_RESTRICT c,
    NS(cobj_test_int64_type) const d  )  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer_begin,
    NS(size_type) const slot_size,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT orig ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjTestNoPtrs_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cbuffer_new)( SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)*
    SIXTRL_RESTRICT buffer );

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_test_real_type) const a, NS(cobj_test_uint64_type) const b,
    SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const* SIXTRL_RESTRICT c,
    NS(cobj_test_int64_type) const d );

SIXTRL_STATIC SIXTRL_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT orig );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs) const*
NS(CObjTestNoPtrs_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_obj_id_type)
NS(CObjTestNoPtrs_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(CObjTestNoPtrs_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(CObjTestNoPtrs_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(CObjTestNoPtrs_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_size_type)
NS(CObjTestNoPtrs_cobj_required_num_bytes_ext)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT o,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_preset_ext)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(CObjTestNoPtrs_clear_ext)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(CObjTestNoPtrs_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const struct NS(CBuffer) *const
        SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT b );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_test_real_type) const a, NS(cobj_test_uint64_type) const b,
    SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const* SIXTRL_RESTRICT c,
    NS(cobj_test_int64_type) const d  );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC struct NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT obj );

#endif /* !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(CObjTestNoPtrs_compare)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT lhs,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type)
NS(CObjTestNoPtrs_compare_with_tolerances)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT l,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT r,
    NS(cobj_test_real_type) const rel_tolerance,
    NS(cobj_test_real_type) const abs_tolerance ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type)
NS(CObjTestNoPtrs_difference)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT l,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT r,
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    static constexpr cobj_obj_id_type COBJECTS_TYPE_ID_TEST_NO_PTRS =
        cobj_obj_id_type{ SIXTRL_COBJECTS_TYPE_ID_TEST_NO_PTRS };

    template<> struct CObjectsTraits< ::NS(CObjTestNoPtrs) >
    {
        static constexpr cobj_obj_id_type TYPE_ID =
            SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_TEST_NO_PTRS;
    };

    template<> struct CObjectsIdTraits<
        SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_TEST_NO_PTRS > {
            typedef ::NS(CObjTestNoPtrs) value_type; };

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


SIXTRL_INLINE NS(cobj_test_real_type) NS(CObjTestNoPtrs_a)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR ); return obj->a; }

SIXTRL_INLINE NS(cobj_test_real_type)
NS(CObjTestNoPtrs_default_a)() SIXTRL_NOEXCEPT {
    return ( NS(cobj_test_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(CObjTestNoPtrs_set_a)(
    SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)* SIXTRL_RESTRICT obj,
    NS(cobj_test_real_type) const a ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->a = a;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cobj_test_uint64_type) NS(CObjTestNoPtrs_b)(
    SIXTRL_TESTLIB_ARGPTR_DEC  const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    return obj->b; }

SIXTRL_INLINE NS(cobj_test_uint64_type) NS(CObjTestNoPtrs_default_b)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_test_uint64_type) )0; }

SIXTRL_INLINE NS(status_type) NS(CObjTestNoPtrs_set_b)(
    SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)* SIXTRL_RESTRICT obj,
    NS(cobj_test_uint64_type) const b ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->b = b;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cobj_test_int64_type) NS(CObjTestNoPtrs_d)(
    SIXTRL_TESTLIB_ARGPTR_DEC  const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR ); return obj->d; }

SIXTRL_INLINE NS(cobj_test_int64_type) NS(CObjTestNoPtrs_default_d)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_test_int64_type) )0; }

SIXTRL_INLINE NS(status_type) NS(CObjTestNoPtrs_set_d)(
    SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)* SIXTRL_RESTRICT obj,
    NS(cobj_test_int64_type) const d ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    obj->d = d;
    return ( NS(status_type) )SIXTRL_STATUS_SUCCESS; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cobj_test_real_type) NS(CObjTestNoPtrs_c)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT e,
    NS(size_type) const index ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( e != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( index < ( NS(size_type) )6u );
    return e->c[ index ];
}

SIXTRL_INLINE NS(cobj_test_real_type) NS(CObjTestNoPtrs_default_c)(
    void ) SIXTRL_NOEXCEPT { return ( NS(cobj_test_real_type) )0.; }

SIXTRL_INLINE NS(status_type) NS(CObjTestNoPtrs_set_c)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT e,
    NS(size_type) const index,
    NS(cobj_test_real_type) const c_value ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( e != SIXTRL_NULLPTR ) && ( index < ( NS(size_type) )6u ) )
    {
        e->c[ index ] = c_value;
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

SIXTRL_INLINE NS(size_type) NS(CObjTestNoPtrs_c_length)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT {
    return ( e != SIXTRL_NULLPTR ) ? ( NS(size_type) )6u : ( NS(size_type) )0u;
}

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestNoPtrs_c_const_begin)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT {
    return ( e != SIXTRL_NULLPTR )
        ? ( SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const* )&e->c[ 0 ]
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const*
NS(CObjTestNoPtrs_c_const_end)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT e
) SIXTRL_NOEXCEPT {
    return ( e != SIXTRL_NULLPTR )
        ? ( SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const* )&e->c[ 6 ]
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestNoPtrs_c_begin)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
    SIXTRL_RESTRICT e ) SIXTRL_NOEXCEPT {
    return ( e != SIXTRL_NULLPTR )
        ? ( SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type)* )&e->c[ 0 ]
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type)*
NS(CObjTestNoPtrs_c_end)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
    SIXTRL_RESTRICT e ) SIXTRL_NOEXCEPT {
    return ( e != SIXTRL_NULLPTR )
        ? ( SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type)* )&e->c[ 6 ]
        : SIXTRL_NULLPTR; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(cobj_obj_id_type) NS(CObjTestNoPtrs_cobj_type_id)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_obj_id_type)
        )SIXTRL_COBJECTS_TYPE_ID_TEST_NO_PTRS; }

SIXTRL_INLINE NS(cobj_size_type) NS(CObjTestNoPtrs_cobj_num_dataptrs)(
    ) SIXTRL_NOEXCEPT { return ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(CObjTestNoPtrs_cobj_actual_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    if( slot_size == ( NS(cobj_size_type) )0u )
        slot_size =  ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN;
    return NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(CObjTestNoPtrs) ), slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CObjTestNoPtrs_cobj_reserved_handle_size)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(CObjTestNoPtrs_cobj_actual_handle_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CObjTestNoPtrs_cobj_required_num_bytes)(
    SIXTRL_TESTLIB_ARGPTR_DEC  const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( obj ),
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_cobj_reserved_handle_size)( slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_preset)( SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    if( obj != SIXTRL_NULLPTR ) NS(CObjTestNoPtrs_clear)( obj );
    return obj; }

SIXTRL_INLINE NS(status_type) NS(CObjTestNoPtrs_clear)(
    SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_init)( obj, NS(CObjTestNoPtrs_default_a)(),
        NS(CObjTestNoPtrs_default_b)(), SIXTRL_NULLPTR,
        NS(CObjTestNoPtrs_default_d)() ); }

SIXTRL_INLINE NS(status_type) NS(CObjTestNoPtrs_init)(
    SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)* SIXTRL_RESTRICT obj,
    NS(cobj_test_real_type) const a, NS(cobj_test_uint64_type) const b,
    SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const* SIXTRL_RESTRICT c,
    NS(cobj_test_int64_type) const d ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    NS(size_type) ii = ( NS(size_type) )0u;
    NS(size_type) const nn = NS(CObjTestNoPtrs_c_length)( obj );
    SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
    status |= NS(CObjTestNoPtrs_set_a)( obj, a );
    status |= NS(CObjTestNoPtrs_set_b)( obj, b );

    if( c != SIXTRL_NULLPTR )
    {
        for( ; ii < nn ; ++ii ) {
            status |= NS(CObjTestNoPtrs_set_c)( obj, ii, c[ ii ] );
        }
    }
    else
    {
        for( ; ii < nn ; ++ii ) {
            status |= NS(CObjTestNoPtrs_set_c)( obj, ii,
                NS(CObjTestNoPtrs_default_c)() );
        }
    }

    status |= NS(CObjTestNoPtrs_set_d)( obj, d );
    return status; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(status_type) NS(CObjTestNoPtrs_copy)(
    SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)* SIXTRL_RESTRICT dest,
    SIXTRL_TESTLIB_ARGPTR_DEC  const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT src
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( dest != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) ) {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
        if( dest != src ) {
            status |= NS(CObjTestNoPtrs_init)( dest,
                NS(CObjTestNoPtrs_a)( src ),
                NS(CObjTestNoPtrs_b)( src ),
                NS(CObjTestNoPtrs_c_const_begin)( src ),
                NS(CObjTestNoPtrs_d)( src ) ); } }
    return status; }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjIndex_is_cobj_test_no_ptrs)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjIndex_is_consistent_with_type)( obj,
        NS(CObjTestNoPtrs_cobj_type_id)(),
            NS(CObjTestNoPtrs_cobj_actual_handle_size)(
                ( NS(cobj_size_type) )SIXTRL_DEFAULT_ALIGN ) ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs) const*
NS(CObjTestNoPtrs_const_from_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const
    NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT {
    return ( NS(CObjIndex_is_cobj_test_no_ptrs)( obj ) )
        ? ( SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs) const* )(
            uintptr_t )NS(CObjIndex_begin_addr)( obj )
        : SIXTRL_NULLPTR; }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_from_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* obj ) SIXTRL_NOEXCEPT {
    return ( SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)*
        )NS(CObjTestNoPtrs_const_from_cobj_index)( obj ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs) const*
NS(CObjTestNoPtrs_const_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_const_from_cobj_index)(
        NS(CObjFlatBuffer_const_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_from_cobj_flat_buffer)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_from_cobj_index)(
        NS(CObjFlatBuffer_index)( buffer, idx, slot_size ) ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs) const*
NS(CObjTestNoPtrs_const_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_const_from_cobj_index)(
        NS(CBuffer_const_index_at)( buffer, idx ) ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_from_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_from_cobj_index)(
        NS(CBuffer_index_at)( buffer, idx ) ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CObjTestNoPtrs_cobj_flat_buffer_can_be_added)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_can_add_copy_of_trivial_object)( buffer, slot_size,
        NS(CObjTestNoPtrs_cobj_reserved_handle_size)( slot_size ),
            requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cobj_flat_buffer_new)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CObjTestNoPtrs) elem;
    NS(CObjTestNoPtrs_clear)( &elem );
    return NS(CObjTestNoPtrs_cobj_flat_buffer_add_copy)(
        buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cobj_flat_buffer_add)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    NS(cobj_test_real_type) const a, NS(cobj_test_uint64_type) const b,
    SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const* c,
    NS(cobj_test_int64_type) const d )  SIXTRL_NOEXCEPT {
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CObjTestNoPtrs) elem;
    NS(CObjTestNoPtrs_init)( &elem, a, b, c, d );
    return NS(CObjTestNoPtrs_cobj_flat_buffer_add_copy)(
        buffer, slot_size, &elem ); }

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cobj_flat_buffer_add_copy)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size,
    SIXTRL_TESTLIB_ARGPTR_DEC  const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT orig ) SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_from_cobj_index)(
            NS(CObjFlatBuffer_add_copy_of_trivial_object)( buffer, slot_size,
                orig, NS(CObjTestNoPtrs_cobj_reserved_handle_size)( slot_size ),
                    NS(CObjTestNoPtrs_cobj_type_id)(), false ) ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(CObjTestNoPtrs_cbuffer_can_be_added)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_dataptrs
) SIXTRL_NOEXCEPT { return NS(CBuffer_can_add_copy_of_trivial_object)( b,
    NS(CObjTestNoPtrs_cobj_reserved_handle_size)( NS(CBuffer_slot_size)( b ) ),
        requ_buffer_size, requ_n_slots, requ_n_objects, requ_n_dataptrs ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cbuffer_new)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer ) {
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs) elem;
    NS(CObjTestNoPtrs_clear)( &elem );
    return NS(CObjTestNoPtrs_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cbuffer_add)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_test_real_type) const a, NS(cobj_test_uint64_type) const b,
    SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const* SIXTRL_RESTRICT c,
    NS(cobj_test_int64_type) const d ) {
    SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs) elem;
    NS(CObjTestNoPtrs_init)( &elem, a, b, c, d );
    return NS(CObjTestNoPtrs_cbuffer_add_copy)( buffer, &elem ); }

SIXTRL_INLINE SIXTRL_TESTLIB_ARGPTR_DEC  NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cbuffer_add_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_TESTLIB_ARGPTR_DEC  const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT orig ) {
    return NS(CObjTestNoPtrs_from_cobj_index)(
        NS(CBuffer_add_copy_of_trivial_object)( buffer, orig,
            NS(CObjTestNoPtrs_cobj_reserved_handle_size)( NS(CBuffer_slot_size)(
                buffer ) ), NS(CObjTestNoPtrs_cobj_type_id)(), false ) ); }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cmp_result_type) NS(CObjTestNoPtrs_compare)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT lhs,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_compare_with_tolerances)( lhs, rhs,
        ( NS(cobj_test_real_type) )0.0,
        ( NS(cobj_test_real_type) )SIXTRL_REAL_TYPE_EPS ); }

SIXTRL_INLINE NS(cmp_result_type) NS(CObjTestNoPtrs_compare_with_tolerances)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT lhs,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
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

            if( ( result == ( NS(cmp_result_type) )0 ) && ( lhs->b != rhs->b ) )
                  result = ( lhs->b > rhs->b )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;

            SIXTRL_ASSERT( NS(CObjTestNoPtrs_c_length)( lhs ) ==
                           NS(CObjTestNoPtrs_c_length)( rhs ) );

            if( ( result == 0 ) &&
                ( NS(CObjTestNoPtrs_c_const_begin)( lhs ) !=
                  NS(CObjTestNoPtrs_c_const_begin)( rhs ) ) )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(CObjTestNoPtrs_c_const_begin)( lhs ),
                    NS(CObjTestNoPtrs_c_const_end)( lhs ),
                    NS(CObjTestNoPtrs_c_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( ( result == 0 ) && ( lhs->d != rhs->d ) )
                  result = ( lhs->d > rhs->d )
                    ? ( NS(cmp_result_type ) )+1 : ( NS(cmp_result_type) )-1;
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;
    return result;
}

SIXTRL_INLINE NS(status_type) NS(CObjTestNoPtrs_difference)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT lhs,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT rhs,
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) &&
        ( diff != lhs ) && ( diff != rhs ) && ( lhs != rhs ) )
    {
        status = NS(CObjTestNoPtrs_set_a)( diff,
            NS(Type_subtract_real_type)(
                NS(CObjTestNoPtrs_a)( lhs ), NS(CObjTestNoPtrs_a)( rhs ) ) );

        status |= NS(CObjTestNoPtrs_set_b)( diff,
            NS(Type_subtract_uint64_type)(
                NS(CObjTestNoPtrs_b)( lhs ), NS(CObjTestNoPtrs_b)( rhs ) ) );

        SIXTRL_ASSERT( NS(CObjTestNoPtrs_c_length)( diff ) ==
                       NS(CObjTestNoPtrs_c_length)( lhs ) );

        SIXTRL_ASSERT( NS(CObjTestNoPtrs_c_length)( diff ) ==
                       NS(CObjTestNoPtrs_c_length)( rhs ) );

        status |= NS(Type_subtract_real_type_ranges)(
            NS(CObjTestNoPtrs_c_begin)( diff ),
            NS(CObjTestNoPtrs_c_const_begin)( lhs ),
            NS(CObjTestNoPtrs_c_const_end)( lhs ),
            NS(CObjTestNoPtrs_c_const_begin)( rhs ) );

        status |= NS(CObjTestNoPtrs_set_d)( diff, NS(Type_subtract_int64_type)(
            NS(CObjTestNoPtrs_d)( lhs ), NS(CObjTestNoPtrs_d)( rhs ) ) );
    }

    return status;
}

#if !defined(  _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_NO_PTRS_H__ */
