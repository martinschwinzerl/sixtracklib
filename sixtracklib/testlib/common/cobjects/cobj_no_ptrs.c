#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/cobjects/cobj_no_ptrs.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE )

SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs) const*
NS(CObjTestNoPtrs_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_const_from_cbuffer)( b, idx ); }

SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_from_cbuffer)( b, idx ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

NS(cobj_obj_id_type) NS(CObjTestNoPtrs_cobj_type_id_ext)() SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_cobj_type_id)(); }

NS(cobj_size_type) NS(CObjTestNoPtrs_cobj_num_dataptrs_ext)() SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(CObjTestNoPtrs_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(CObjTestNoPtrs_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(CObjTestNoPtrs_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(CObjTestNoPtrs_cobj_reserved_handle_size)( slot_size ); }

NS(cobj_size_type) NS(CObjTestNoPtrs_cobj_required_num_bytes_ext)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const SIXTRL_RESTRICT o,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_cobj_required_num_bytes)( o, slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* NS(CObjTestNoPtrs_preset_ext)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjTestNoPtrs_preset)( obj ); }

NS(status_type) NS(CObjTestNoPtrs_clear_ext)(
    SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT { return NS(CObjTestNoPtrs_clear)( obj ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(CObjTestNoPtrs_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT {
    return NS(CObjTestNoPtrs_cbuffer_can_be_added)(
        b, requ_buffer_size, requ_slots, requ_objects, requ_dataptrs ); }

SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* NS(CObjTestNoPtrs_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) {
    return NS(CObjTestNoPtrs_cbuffer_new)( b ); }

SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)* NS(CObjTestNoPtrs_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_test_real_type) const a, NS(cobj_test_uint64_type) const b,
    SIXTRL_TESTLIB_ARGPTR_DEC NS(cobj_test_real_type) const* SIXTRL_RESTRICT c,
    NS(cobj_test_int64_type) const d  ) {
    return NS(CObjTestNoPtrs_cbuffer_add)( buffer, a, b, c, d ); }

SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestNoPtrs)*
NS(CObjTestNoPtrs_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestNoPtrs) *const
        SIXTRL_RESTRICT obj ) { return NS(CObjTestNoPtrs_cbuffer_add_copy)(
            buffer, obj ); }

#endif /* !defined( _GPUCODE ) */
