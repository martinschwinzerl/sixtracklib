#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/cobjects/cobj_dataptrs.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE )

SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs) const*
NS(CObjTestDataptrs_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
        return NS(CObjTestDataptrs_const_from_cbuffer)( b, idx ); }

SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(CObjTestDataptrs_from_cbuffer)( b, idx ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

NS(cobj_obj_id_type) NS(CObjTestDataptrs_cobj_type_id_ext)() SIXTRL_NOEXCEPT {
    return NS(CObjTestDataptrs_cobj_type_id)(); }

NS(cobj_size_type) NS(CObjTestDataptrs_cobj_num_dataptrs_ext)() SIXTRL_NOEXCEPT {
    return NS(CObjTestDataptrs_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(CObjTestDataptrs_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(CObjTestDataptrs_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(CObjTestDataptrs_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(CObjTestDataptrs_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(CObjTestDataptrs_cobj_required_num_bytes_ext)(
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem, NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjTestDataptrs_cobj_required_num_bytes)( elem, slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_preset_ext)( SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
        return NS(CObjTestDataptrs_preset)( elem ); }

NS(status_type) NS(CObjTestDataptrs_clear_ext)( SIXTRL_TESTLIB_ARGPTR_DEC
    NS(CObjTestDataptrs)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT {
        return NS(CObjTestDataptrs_clear)( elem ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(CObjTestDataptrs_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const c_capacity,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_dataptrs
) SIXTRL_NOEXCEPT { return NS(CObjTestDataptrs_cbuffer_can_be_added)(
    buffer, b_capacity, c_capacity, requ_buffer_size, requ_slots, requ_objects,
        requ_dataptrs ); }

SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const c_capacity ) {
    return NS(CObjTestDataptrs_cbuffer_new)( buffer, b_capacity, c_capacity ); }

SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_test_real_type) const a,
    NS(cobj_test_uint64_type) const b_capacity,
    NS(cobj_test_uint64_type) const b_length,
    NS(cobj_test_addr_type) const b_addr,
    NS(cobj_test_uint64_type) const c_capacity,
    NS(cobj_test_uint64_type) const c_length,
    NS(cobj_test_addr_type) const c_addr ) {
    return NS(CObjTestDataptrs_cbuffer_add)( buffer, a,
        b_capacity, b_length, b_addr, c_capacity, c_length, c_addr ); }

SIXTRL_TESTLIB_ARGPTR_DEC NS(CObjTestDataptrs)*
NS(CObjTestDataptrs_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_TESTLIB_ARGPTR_DEC const NS(CObjTestDataptrs) *const
        SIXTRL_RESTRICT elem ) {
    return NS(CObjTestDataptrs_cbuffer_add_copy)( buffer, elem ); }

#endif /* !defined( _GPUCODE ) */
