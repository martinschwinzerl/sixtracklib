#ifndef SIXTRACKLIB_COMMON_COBJECTS_CBUFFER_C99_H__
#define SIXTRACKLIB_COMMON_COBJECTS_CBUFFER_C99_H__

#if !defined( SIXTRL_NO_INCLUDE )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/garbage_range.h"
    #include "sixtracklib/common/cobjects/index_object.h"
#endif /* !defined( SIXTRL_NO_INCLUDE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

typedef struct NS(CBuffer)
{
    NS(cobj_addr_type)          m_base_addr;
    NS(cobj_size_type)          m_slot_size;
    NS(cobj_size_type)          m_capacity;
    NS(cobj_size_type)          m_reserve_factor_nominator;
    NS(cobj_size_type)          m_reserve_factor_denominator;
    NS(cobj_buffer_flags_type)  m_buffer_flags;
    NS(cobj_addr_type)          m_datastore_addr;
}
NS(CBuffer);

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_header_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_min_buffer_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
NS(CBuffer_preset)( SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
    SIXTRL_RESTRICT buffer ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_clear)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_init_as_view)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_addr_type) const base_addr,
    NS(cobj_size_type) const capacity ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_init_as_view_detailed)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_addr_type) const base_addr, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const capacity, NS(cobj_buffer_flags_type) const flags
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(CBuffer_init_as_copy_of_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT orig );

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(CBuffer_init_as_copy_of_cobj_flat_buffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const*
        SIXTRL_RESTRICT orig_buffer_begin,
    NS(cobj_size_type) const orig_slot_size );


/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_free)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(CBuffer_delete)( SIXTRL_CBUFFER_ARGPTR_DEC
    NS(CBuffer)* SIXTRL_RESTRICT view );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_status_type) NS(CBuffer_init_as_buffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const capacity );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_status_type)
NS(CBuffer_init_as_buffer_detailed)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const capacity,
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges,
    NS(cobj_size_type) const slot_size,
    NS(cobj_buffer_flags_type) flags );

SIXTRL_EXTERN SIXTRL_FN NS(cobj_status_type)
NS(CBuffer_init_from_file)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT path_to_file
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_FN NS(cobj_status_type) NS(CBuffer_free)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer
) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
NS(CBuffer_new_as_view)( NS(cobj_addr_type) const base_addr,
                         NS(cobj_size_type) const capacity );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
NS(CBuffer_new_as_view_detailed)( NS(cobj_addr_type) const base_addr,
    NS(cobj_size_type) const slot_size, NS(cobj_size_type) const capacity,
    NS(cobj_buffer_flags_type) const flags );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
NS(CBuffer_new)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
NS(CBuffer_new_with_capacity)( NS(cobj_size_type) const capacity );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
NS(CBuffer_new_detailed)( NS(cobj_size_type) capacity,
    NS(cobj_size_type) const slot_size, NS(cobj_buffer_flags_type) flags );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
NS(CBuffer_new_as_copy)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const
    SIXTRL_RESTRICT view );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
NS(CBuffer_new_as_copy_detailed)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT orig,
    NS(cobj_buffer_flags_type) const flags );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
NS(CBuffer_new_from_file)( char const* SIXTRL_RESTRICT path_tofile );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
NS(CBuffer_new_from_file_detailed)(
    char const* SIXTRL_RESTRICT path_tofile,
    NS(cobj_size_type) const slot_size, NS(cobj_buffer_flags_type) flags );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
NS(CBuffer_new_with_structure)(
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges,
    NS(cobj_size_type) const slot_size,
    NS(cobj_buffer_flags_type) flags );

#endif /* !defined( _GPUCODE ) */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CBuffer_required_buffer_length)(
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CBuffer_aligned_base_addr)(
    NS(cobj_addr_type) const raw_base_addr,
    NS(cobj_size_type) const raw_capacity,
    NS(cobj_size_type) const alignment,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* ptr_capacity ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_buffer_flags_type)
NS(CBuffer_flags)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const
    SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_is_buffer_flag_set)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_buffer_flags_type) const flag_to_test ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_is_buffer_flag_set_detailed)(
    NS(cobj_buffer_flags_type) const set_of_flags,
    NS(cobj_buffer_flags_type) const flag_to_test ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_allow_remap)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_allow_allocate)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_allow_realloc)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_allow_append)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_owns_stored_data)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_has_special_memory)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_storage_is_c_ptr)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_storage_is_cxx_vector)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_storage_force_init)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_slot_size)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_size)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_capacity)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_size_header)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_size_section_header)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const sec_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_size_slots)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_size_objects)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_size_pointers)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_size_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_num_slots)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_num_objects)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_num_pointers)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_num_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_max_slots)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_max_objects)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_max_pointers)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_max_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_begin_addr)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_end_addr)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_begin_addr_slots)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_begin_addr_objects)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_begin_addr_pointers)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_begin_addr_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_end_addr_slots)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_end_addr_objects)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_end_addr_pointers)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_end_addr_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_datastore_address)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_base_address)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer) NS(CBuffer_p_const_base)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CBuffer_p_const_base_begin)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer)
    *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer) NS(CBuffer_p_const_base_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_base_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_base_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_base)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer) NS(CBuffer_p_const_slots)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_slots)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CBuffer_p_const_slots_begin)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer)
    *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_slots_begin)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer) NS(CBuffer_p_const_slots_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_slots_end)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CBuffer_p_const_objects)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer)
    *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_objects)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CBuffer_p_const_objects_begin)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer)
    *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_objects_begin)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CBuffer_p_const_objects_end)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer)
    *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_objects_end)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CBuffer_p_const_pointers)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer)
    *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_pointers)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CBuffer_p_const_pointers_begin)( SIXTRL_CBUFFER_ARGPTR_DEC const
    NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_pointers_begin)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CBuffer_p_const_pointers_end)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer)
  *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_pointers_end)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer) NS(CBuffer_p_const_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_garbage)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CBuffer_p_const_garbage_begin)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer)
    *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_garbage_begin)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CBuffer_p_const_garbage_end)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer)
    *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer) NS(CBuffer_p_garbage_end)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_index_const_pointer)
NS(CBuffer_const_objects_begin)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer)
    *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_index_pointer) NS(CBuffer_objects_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_index_const_pointer)
NS(CBuffer_const_objects_end)( SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer)
    *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_index_pointer) NS(CBuffer_objects_end)(
  SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_index_const_pointer)
NS(CBuffer_const_index_at)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const pos ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_obj_index_pointer) NS(CBuffer_index_at)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const pos ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_diff_type) NS(CBuffer_address_to_offset)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_addr_type) const address ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_offset_to_address)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_addr_diff_type) const offset ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_has_capacity_for_allocate)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_can_allocate)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_allocate)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges );

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_reallocate)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges );

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_needs_remapping)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_can_remap)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_remap)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer
) SIXTRL_NOEXCEPT;

/* ========================================================================== */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_reserve_factor_nominator)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CBuffer_reserve_factor_denominator)( SIXTRL_CBUFFER_ARGPTR_DEC const
    NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CBuffer_set_reserve_factor_nominator)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const factor_nominator ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CBuffer_set_reserve_factor_denominator)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const factor_deominator ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(CBuffer_set_reserve_factor)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const factor_nominator,
    NS(cobj_size_type) const factor_denominator ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CBuffer_reserve_scale_capacity)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const capacity ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_reserve)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const capacity );

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_reserve_detailed)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges );

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_init_c99_ptr_store)(
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CBuffer_base_addr_from_c99_ptr_store)(
    NS(cobj_addr_type) const store_addr,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_free_c99_ptr_store)(
    NS(cobj_addr_type) const store_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CBuffer_init_cxx_vector_store)(
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CBuffer_base_addr_from_cxx_vector_store)(
    NS(cobj_addr_type) const store_addr,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_free_cxx_vector_store)(
    NS(cobj_addr_type) const store_addr ) SIXTRL_NOEXCEPT;

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_from_view)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT view );

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CBuffer_from_flat_buffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT flat_buffer_begin,
    NS(cobj_size_type) const flat_buffer_capacity );

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_status_type) NS(CBuffer_from_file)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    char const* SIXTRL_RESTRICT path_tofile );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_status_type) NS(CBuffer_to_file)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    char const* SIXTRL_RESTRICT path_to_file );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_status_type) NS(CBuffer_to_file_normalised)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    char const* SIXTRL_RESTRICT path_tofile,
    NS(cobj_addr_type) const normalised_base_addr );

#endif /* !defined( _GPUCODE ) */

/* -------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_can_add_copy_of_object)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const obj_type_size,
    NS(cobj_size_type) const num_dataptrs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_pointers
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CBuffer_can_add_copy_of_trivial_object)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const obj_type_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_pointers
) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
NS(CBuffer_add_copy_of_object_detailed)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT obj_handle,
    NS(cobj_size_type) const reserved_obj_handle_size,
    NS(cobj_size_type) const actual_obj_handle_size,
    NS(cobj_obj_id_type) const type_id,
    NS(cobj_size_type) const num_dataptrs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    bool fill_with_zeros );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
NS(CBuffer_add_copy_of_object)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT obj_handle,
    NS(cobj_size_type) const obj_handle_size,
    NS(cobj_obj_id_type) const type_id,
    NS(cobj_size_type) const num_dataptrs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    bool fill_with_zeros );

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
NS(CBuffer_add_copy_of_trivial_object)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT obj_handle,
    NS(cobj_size_type) const obj_handle_size,
    NS(cobj_obj_id_type) const type_id, bool fill_with_zeros );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************** */
/* ************************************************************************** */

#if !defined( SXITRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/flat_buffer.h"
#endif /* !defined( SXITRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDE )
    #if defined( __cplusplus )
        #include <cstdlib>
        #include <utility>
        #include <vector>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDE ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <string.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_INLINE SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* NS(CBuffer_preset)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    if( b != SIXTRL_NULLPTR ) { NS(CBuffer_clear)( b ); }
    return b; }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_header_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(CObjFlatBuffer_header_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_min_buffer_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
        return NS(CObjFlatBuffer_min_buffer_size)( slot_size ); }

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_clear)( SIXTRL_CBUFFER_ARGPTR_DEC
    NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    NS(cobj_status_type) status = (
        NS(cobj_status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( b != SIXTRL_NULLPTR ) {
        b->m_base_addr = ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS;
        b->m_slot_size = ( NS(cobj_size_type) )SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE;
        b->m_capacity  = ( NS(cobj_size_type) )0u;
        b->m_reserve_factor_nominator = ( NS(cobj_size_type) )1u;
        b->m_reserve_factor_denominator = ( NS(cobj_size_type) )1u;
        b->m_buffer_flags = ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_NONE;
        b->m_datastore_addr = ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS;
        status = ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS;
    }
    return status; }

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_init_as_view)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_addr_type) const base_addr,
    NS(cobj_size_type) const capacity ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_buffer_flags_type) flags_type;
    return NS(CBuffer_init_as_view_detailed)( b, base_addr,
        ( NS(cobj_size_type) )SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE, capacity,
        ( flags_type )SIXTRL_CBUFFER_FLAGS_ALLOW_REMAPPING |
        ( flags_type )SIXTRL_CBUFFER_FLAGS_ALLOW_ALLOC |
        ( flags_type )SIXTRL_CBUFFER_FLAGS_ALLOW_REALLOC |
        ( flags_type )SIXTRL_CBUFFER_FLAGS_ALLOW_APPEND ); }

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_init_as_view_detailed)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_addr_type) const base_addr, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const capacity,
    NS(cobj_buffer_flags_type) const flags ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_status_type) status_t;
    typedef NS(cobj_addr_type) addr_t;
    typedef NS(cobj_size_type) st_size_t;

    status_t status = ( status_t )SIXTRL_STATUS_GENERAL_FAILURE;
    SIXTRL_STATIC_VAR addr_t const NULL_ADDR = (
        addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;

    if( ( b != SIXTRL_NULLPTR ) && ( base_addr != NULL_ADDR ) &&
        ( slot_size > ( st_size_t )0u ) &&
        ( capacity >= NS(CBuffer_min_buffer_size)( slot_size ) ) &&
        ( NS(CBuffer_base_address)( b ) == NULL_ADDR ) &&
        ( NS(CBuffer_datastore_address)( b ) == NULL_ADDR ) &&
        ( NS(CBuffer_flags)( b ) == ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_NONE ) ) {

        b->m_base_addr = base_addr;
        b->m_slot_size = slot_size;
        b->m_capacity  = capacity;
        b->m_buffer_flags = flags;

        if( ( !NS(CBuffer_is_buffer_flag_set)( b, ( NS(cobj_buffer_flags_type)
                )SIXTRL_CBUFFER_FLAGS_FORCE_INIT ) ) &&
            ( NS(CObjFlatBuffer_has_cbuffer_structure)(
                NS(CBuffer_p_const_base)( b ), capacity, slot_size ) ) )
        {
            NS(cobj_size_type) const read_buffer_size = NS(CObjFlatBuffer_size)(
                NS(CBuffer_p_const_base)( b ), slot_size );

            if( b->m_capacity < read_buffer_size )
                b->m_capacity = read_buffer_size;
            status = ( status_t )SIXTRL_STATUS_SUCCESS;
        }
        else
        {
            SIXTRL_ASSERT( NS(CBuffer_p_const_base)( b ) != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( NS(CBuffer_slot_size)( b ) > ( st_size_t )0u );

            status = NS(CObjFlatBuffer_init_empty)(
                NS(CBuffer_p_base)( b ), capacity, NS(CBuffer_slot_size)( b ) );
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_init_as_copy_of_cbuffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT orig ) {
    return NS(CBuffer_init_as_copy_of_cobj_flat_buffer)( buffer,
        NS(CBuffer_p_const_base)( orig ), NS(CBuffer_slot_size)( orig ) );
}

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_init_as_copy_of_cobj_flat_buffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const*
        SIXTRL_RESTRICT orig_buffer_begin,
    NS(cobj_size_type) const orig_slot_size )
{
    typedef NS(cobj_size_type) st_size_t;
    typedef NS(cobj_status_type) st_status_t;

    st_status_t status = ( st_status_t )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( buffer != SIXTRL_NULLPTR ) && ( orig_slot_size > ( st_size_t )0u ) &&
        ( orig_buffer_begin != SIXTRL_NULLPTR ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)( orig_buffer_begin,
            NS(CObjFlatBuffer_size)( orig_buffer_begin, orig_slot_size ),
                orig_slot_size ) ) )
    {
        st_size_t const orig_buffer_size = NS(CObjFlatBuffer_size)(
            orig_buffer_begin, orig_slot_size );

        SIXTRL_ASSERT( orig_buffer_size % orig_slot_size == ( st_size_t )0u );

        if( ( NS(CBuffer_p_const_base_begin)( buffer ) != SIXTRL_NULLPTR ) &&
            ( NS(CBuffer_slot_size)( buffer ) == orig_slot_size ) )
        {
            if( ( NS(CBuffer_capacity)( buffer ) < orig_buffer_size ) &&
                ( NS(CBuffer_owns_stored_data)( buffer ) ) &&
                ( NS(CBuffer_allow_allocate)( buffer ) ) &&
                ( NS(CBuffer_allow_remap)( buffer ) ) )
            {
                NS(CBuffer_reserve)( buffer, orig_buffer_size );
            }

            if( ( NS(CBuffer_capacity)( buffer ) >= orig_buffer_size ) &&
                ( NS(CBuffer_allow_allocate)( buffer ) ) &&
                ( NS(CBuffer_allow_remap)( buffer ) ) )
            {
                typedef NS(cobj_raw_type) raw_type;
                NS(cobj_raw_pointer) dest = NS(CBuffer_p_base_begin)( buffer );

                SIXTRACKLIB_COPY_VALUES(
                    raw_type, dest, orig_buffer_begin, orig_buffer_size );

                status = NS(CBuffer_remap)( buffer );
            }
        }
    }

    return status;
}

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_free)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_addr_type) addr_t;
    typedef NS(cobj_status_type) st_status_t;
    st_status_t status = ( st_status_t )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( b != SIXTRL_NULLPTR ) && ( NS(CBuffer_owns_stored_data)( b ) ) &&
        ( NS(CBuffer_datastore_address)( b ) !=
            ( addr_t )SIXTRL_COBJECTS_NULL_ADDRESS ) ) {
        if( NS(CBuffer_storage_is_c_ptr)( b ) ) {
            status = NS(CBuffer_free_c99_ptr_store)(
                NS(CBuffer_datastore_address)( b ) ); }
        else if( NS(CBuffer_storage_is_cxx_vector)( b ) ) {
            status = NS(CBuffer_free_cxx_vector_store)(
                NS(CBuffer_datastore_address)( b ) ); }

        if( status == ( st_status_t )SIXTRL_STATUS_SUCCESS ) {
            b->m_base_addr = ( addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;
            b->m_capacity = ( NS(cobj_size_type) )0u;
            b->m_datastore_addr = ( addr_t )SIXTRL_COBJECTS_NULL_ADDRESS; } }

    return status; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_required_buffer_length)(
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_predict_required_buffer_size)(
        max_num_slots, max_num_objects, max_num_pointers,
            max_num_garbage_ranges, slot_size ); }

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_aligned_base_addr)(
    NS(cobj_addr_type) const raw_base_addr,
    NS(cobj_size_type) const raw_capacity,
    NS(cobj_size_type) const alignment,
    NS(cobj_size_type) const slot_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* ptr_capacity ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_aligned_base_addr)( raw_base_addr,
        raw_capacity, alignment, ptr_capacity, slot_size ); }

SIXTRL_INLINE bool NS(CBuffer_is_buffer_flag_set_detailed)(
    NS(cobj_buffer_flags_type) const set_of_flags,
    NS(cobj_buffer_flags_type) const flags_to_test ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_buffer_flags_type) flags_type;
    return ( ( set_of_flags  != ( flags_type )SIXTRL_CBUFFER_FLAGS_NONE ) &&
             ( flags_to_test != ( flags_type )SIXTRL_CBUFFER_FLAGS_NONE ) &&
             ( ( set_of_flags & flags_to_test ) == flags_to_test ) ); }

SIXTRL_INLINE bool NS(CBuffer_is_buffer_flag_set)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_buffer_flags_type) const flags_to_test ) SIXTRL_NOEXCEPT {
    return NS(CBuffer_is_buffer_flag_set_detailed)(
        NS(CBuffer_flags)( b ), flags_to_test ); }

SIXTRL_INLINE void NS(CObjFlatBuffer_set_buffer_flag)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_buffer_flags_type) const flags ) SIXTRL_NOEXCEPT {
    if( buffer != SIXTRL_NULLPTR ) buffer->m_buffer_flags = flags; }

SIXTRL_INLINE NS(cobj_buffer_flags_type) NS(CBuffer_flags)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( b != SIXTRL_NULLPTR )
    ? b->m_buffer_flags
    : ( NS(cobj_buffer_flags_type) )SIXTRL_CBUFFER_FLAGS_NONE; }

SIXTRL_INLINE bool NS(CBuffer_allow_remap)( SIXTRL_CBUFFER_ARGPTR_DEC const
    NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return NS(CBuffer_is_buffer_flag_set)( b, ( NS(cobj_buffer_flags_type)
        )SIXTRL_CBUFFER_FLAGS_ALLOW_REMAPPING ); }

SIXTRL_INLINE bool NS(CBuffer_allow_allocate)( SIXTRL_CBUFFER_ARGPTR_DEC const
    NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return NS(CBuffer_is_buffer_flag_set)( b, ( NS(cobj_buffer_flags_type)
        )SIXTRL_CBUFFER_FLAGS_ALLOW_ALLOC ); }

SIXTRL_INLINE bool NS(CBuffer_allow_realloc)( SIXTRL_CBUFFER_ARGPTR_DEC const
    NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return NS(CBuffer_is_buffer_flag_set)( b, ( NS(cobj_buffer_flags_type)
        )SIXTRL_CBUFFER_FLAGS_ALLOW_REALLOC ); }

SIXTRL_INLINE bool NS(CBuffer_allow_append)( SIXTRL_CBUFFER_ARGPTR_DEC const
    NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return NS(CBuffer_is_buffer_flag_set)( b, ( NS(cobj_buffer_flags_type)
        )SIXTRL_CBUFFER_FLAGS_ALLOW_APPEND ); }

SIXTRL_INLINE bool NS(CBuffer_owns_stored_data)( SIXTRL_CBUFFER_ARGPTR_DEC const
    NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return NS(CBuffer_is_buffer_flag_set)( b, ( NS(cobj_buffer_flags_type)
        )SIXTRL_CBUFFER_FLAGS_OWNS_STORED_DATA ); }

SIXTRL_INLINE bool NS(CBuffer_has_special_memory)( SIXTRL_CBUFFER_ARGPTR_DEC const
    NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return NS(CBuffer_is_buffer_flag_set)( b, ( NS(cobj_buffer_flags_type)
        )SIXTRL_CBUFFER_FLAGS_SPECIAL_MEMORY ); }

SIXTRL_INLINE bool NS(CBuffer_storage_is_c_ptr)( SIXTRL_CBUFFER_ARGPTR_DEC const
    NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
        return NS(CBuffer_is_buffer_flag_set)( b, ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_STORAGE_IS_C_PTR ); }

SIXTRL_INLINE bool NS(CBuffer_storage_is_cxx_vector)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
        return NS(CBuffer_is_buffer_flag_set)( b, ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR ); }

SIXTRL_INLINE bool NS(CBuffer_storage_force_init)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
        return NS(CBuffer_is_buffer_flag_set)( b, ( NS(cobj_buffer_flags_type)
            )SIXTRL_CBUFFER_FLAGS_FORCE_INIT ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_slot_size)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != SIXTRL_NULLPTR )
        ? b->m_slot_size
        : ( NS(cobj_size_type) )SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE; }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_size)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_size)( NS(CBuffer_p_const_base)( b ),
        NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_capacity)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( b != SIXTRL_NULLPTR ) ? b->m_capacity : ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_size_header)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_size_header)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_size_section_header)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const sec_id ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_size_section_header)(
        NS(CBuffer_p_const_base)( b ), sec_id, NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_size_slots)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_size_slots)(
        NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_size_objects)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_size_objects)(
        NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_size_pointers)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_size_pointers)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_size_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_size_garbage_ranges)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_num_slots)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_num_slots)(
        NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_num_objects)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_num_objects)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_num_pointers)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_num_pointers)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_num_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_num_garbage_ranges)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_max_slots)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
     return NS(CObjFlatBuffer_max_num_slots)( NS(CBuffer_p_const_base)( b ),
        NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_max_objects)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_max_num_objects)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_max_pointers)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_max_num_pointers)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_max_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_max_num_garbage_ranges)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_begin_addr)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( b != SIXTRL_NULLPTR )
    ? b->m_base_addr : ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS; }

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_end_addr)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_addr_type) addr_type;
    return ( ( b != SIXTRL_NULLPTR ) &&
             ( b->m_base_addr != ( addr_type )SIXTRL_COBJECTS_NULL_ADDRESS ) )
        ? ( b->m_base_addr + NS(CBuffer_size)( b ) )
        : ( addr_type )SIXTRL_COBJECTS_NULL_ADDRESS; }


SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_begin_addr_slots)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_slots_begin_addr)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_begin_addr_objects)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_indices_begin_addr)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_begin_addr_pointers)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_pointers_begin_addr)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_begin_addr_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_garbage_ranges_begin_addr)(
    NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }


SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_end_addr_slots)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_section_end_addr)(
    NS(CBuffer_p_const_base)( b ), ( NS(cobj_size_type)
        )SIXTRL_CBUFFER_SECTION_ID_SLOTS, NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_end_addr_objects)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_section_end_addr)(
    NS(CBuffer_p_const_base)( b ), ( NS(cobj_size_type)
        )SIXTRL_CBUFFER_SECTION_ID_INDICES, NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_end_addr_pointers)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_section_end_addr)(
    NS(CBuffer_p_const_base)( b ), ( NS(cobj_size_type)
        )SIXTRL_CBUFFER_SECTION_ID_POINTERS, NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_end_addr_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_section_end_addr)(
    NS(CBuffer_p_const_base)( b ), ( NS(cobj_size_type)
        )SIXTRL_CBUFFER_SECTION_ID_GARBAGE, NS(CBuffer_slot_size)( b ) ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_base_address)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( b != SIXTRL_NULLPTR )
    ? b->m_base_addr : ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS; }

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_datastore_address)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( b != SIXTRL_NULLPTR )
    ? b->m_datastore_addr : ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS; }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_base)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer))( uintptr_t
    )NS(CBuffer_base_address)( b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_base_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CBuffer_p_const_base)( b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_base_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
        )NS(CBuffer_end_addr)( b ); }

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_base)( SIXTRL_CBUFFER_ARGPTR_DEC
    NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT { return (
        NS(cobj_raw_pointer))( uintptr_t )NS(CBuffer_base_address)( b ); }

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_base_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer))( uintptr_t )NS(CBuffer_base_address)( b ); }

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_base_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_end_addr)( b ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_slots)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
    )NS(CBuffer_begin_addr_slots)( b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_slots_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
    )NS(CBuffer_begin_addr_slots)( b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_slots_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
    )NS(CBuffer_end_addr_slots)( b ); }


SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_slots)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_begin_addr_slots)(
        b ); }

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_slots_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_begin_addr_slots)(
        b ); }

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_slots_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_end_addr_slots)(
        b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_objects)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
    )NS(CBuffer_begin_addr_objects)( b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_objects_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
    )NS(CBuffer_begin_addr_objects)( b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_objects_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
    )NS(CBuffer_end_addr_objects)( b ); }


SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_objects)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_begin_addr_objects)(
        b ); }

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_objects_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_begin_addr_objects)(
        b ); }

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_objects_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_end_addr_objects)(
        b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_pointers)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
    )NS(CBuffer_begin_addr_pointers)( b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_pointers_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
    )NS(CBuffer_begin_addr_pointers)( b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_pointers_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
    )NS(CBuffer_end_addr_pointers)( b ); }


SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_pointers)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_begin_addr_pointers)(
        b ); }

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_pointers_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_begin_addr_pointers)(
        b ); }

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_pointers_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_end_addr_pointers)(
        b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
    )NS(CBuffer_begin_addr_garbage)( b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_garbage_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
    )NS(CBuffer_begin_addr_garbage)( b ); }

SIXTRL_INLINE NS(cobj_raw_const_pointer) NS(CBuffer_p_const_garbage_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( NS(cobj_raw_const_pointer) )( uintptr_t
    )NS(CBuffer_end_addr_garbage)( b ); }

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_garbage)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_begin_addr_garbage)(
        b ); }

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_garbage_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_begin_addr_garbage)(
        b ); }

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CBuffer_p_garbage_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(cobj_raw_pointer) )( uintptr_t )NS(CBuffer_end_addr_garbage)(
        b ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_obj_index_const_pointer) NS(CBuffer_const_objects_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_const_indices_begin)(
        NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_obj_index_const_pointer) NS(CBuffer_const_objects_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_const_indices_end)(
        NS(CBuffer_p_const_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_obj_index_pointer) NS(CBuffer_objects_begin)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_indices_begin)(
        NS(CBuffer_p_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_obj_index_pointer) NS(CBuffer_objects_end)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_indices_end)(
        NS(CBuffer_p_base)( b ), NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_obj_index_const_pointer) NS(CBuffer_const_index_at)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const pos ) SIXTRL_NOEXCEPT {
        return NS(CObjFlatBuffer_const_index)( NS(CBuffer_p_const_base)( b ),
            pos, NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_obj_index_pointer) NS(CBuffer_index_at)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const pos ) SIXTRL_NOEXCEPT {
        return NS(CObjFlatBuffer_index)( NS(CBuffer_p_base)( b ),
            pos, NS(CBuffer_slot_size)( b ) ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_addr_diff_type) NS(CBuffer_address_to_offset)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_addr_type) const address ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_address_to_offset)( NS(CBuffer_base_address)( b ),
        address, NS(CBuffer_slot_size)( b ) ); }

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_offset_to_address)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_addr_diff_type) const offset ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_offset_to_address)( NS(CBuffer_base_address)( b ),
        offset, NS(CBuffer_slot_size)( b ) ); }

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CBuffer_has_capacity_for_allocate)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_t;
    st_size_t const slot_size = NS(CBuffer_slot_size)( b );
    st_size_t const requ_buffer_size =
        NS(CObjFlatBuffer_calc_required_buffer_size)(
            NS(CBuffer_p_const_base)( b ), max_num_slots, max_num_objects,
                max_num_pointers,max_num_garbage_ranges, slot_size );

    SIXTRL_ASSERT( NS(CBuffer_capacity)( b ) >= NS(CBuffer_size)( b ) );
    return ( ( requ_buffer_size >= NS(CBuffer_min_buffer_size)( slot_size ) ) &&
             ( requ_buffer_size <= NS(CBuffer_capacity)( b ) ) ); }

SIXTRL_INLINE bool NS(CBuffer_can_allocate)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges ) SIXTRL_NOEXCEPT {
    return ( ( NS(CBuffer_allow_allocate)( b ) ) &&
        ( NS(CBuffer_has_capacity_for_allocate)( b, max_num_slots,
            max_num_objects, max_num_pointers, max_num_garbage_ranges ) ) ); }

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_allocate)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const max_n_slots,
    NS(cobj_size_type) const max_n_objects,
    NS(cobj_size_type) const max_n_pointers,
    NS(cobj_size_type) const max_n_garbage_ranges ) {
    typedef NS(cobj_size_type) st_size_t;
    typedef NS(cobj_status_type) st_status_t;

    st_status_t status = ( st_status_t )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( b != SIXTRL_NULLPTR ) && ( NS(CBuffer_allow_allocate)( b ) ) )
    {
        st_size_t requ_buffer_size = ( st_size_t )0u;
        st_size_t const slot_size = NS(CBuffer_slot_size)( b );
        SIXTRL_ASSERT( NS(CBuffer_capacity)( b ) >= NS(CBuffer_size)( b ) );

        status = NS(CObjFlatBuffer_allocate)( NS(CBuffer_p_base)( b ),
            NS(CBuffer_capacity)( b ), slot_size, max_n_slots, max_n_objects,
                max_n_pointers, max_n_garbage_ranges, &requ_buffer_size );

        if( ( status != ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS ) &&
            ( requ_buffer_size > NS(CBuffer_min_buffer_size)( slot_size ) ) &&
            ( requ_buffer_size > NS(CBuffer_capacity)( b ) ) )
        {
            NS(cobj_size_type) const requ_capacity =
                NS(CBuffer_reserve_scale_capacity)( b, requ_buffer_size );

            SIXTRL_ASSERT( NS(CBuffer_capacity)( b ) < requ_capacity );
            SIXTRL_ASSERT( requ_buffer_size <= requ_capacity );
            status = NS(CBuffer_reserve)( b, requ_capacity );

            if( ( status == ( st_status_t )SIXTRL_STATUS_SUCCESS ) &&
                ( requ_capacity <= NS(CBuffer_capacity)( b ) ) )
            {
                status = NS(CObjFlatBuffer_allocate)( NS(CBuffer_p_base)( b ),
                    NS(CBuffer_capacity)( b ), slot_size, max_n_slots,
                        max_n_objects, max_n_pointers, max_n_garbage_ranges,
                            &requ_buffer_size );
            }
        }

        SIXTRL_ASSERT( ( status != ( st_status_t )SIXTRL_STATUS_SUCCESS ) ||
            ( ( requ_buffer_size <= NS(CBuffer_capacity)( b ) ) &&
              ( requ_buffer_size >= NS(CBuffer_min_buffer_size)( slot_size ) ) &&
              ( requ_buffer_size == NS(CObjFlatBuffer_size)(
                    NS(CBuffer_p_const_base)( b ), slot_size ) ) &&
              ( ( st_size_t )0u      == NS(CBuffer_num_slots)( b ) ) &&
              ( ( st_size_t )0u      == NS(CBuffer_num_objects)( b ) ) &&
              ( ( st_size_t )0u      == NS(CBuffer_num_pointers)( b ) ) &&
              ( ( st_size_t )0u      == NS(CBuffer_num_garbage)( b ) ) &&
              ( max_n_slots          <= NS(CBuffer_max_slots)( b ) ) &&
              ( max_n_objects        <= NS(CBuffer_max_objects)( b ) ) &&
              ( max_n_pointers       <= NS(CBuffer_max_pointers)( b ) ) &&
              ( max_n_garbage_ranges <= NS(CBuffer_max_garbage)( b ) ) ) );
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_reallocate)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const max_n_slots,
    NS(cobj_size_type) const max_n_objects,
    NS(cobj_size_type) const max_n_pointers,
    NS(cobj_size_type) const max_n_garbage_ranges ) {
    typedef NS(cobj_size_type)   st_size_t;
    typedef NS(cobj_status_type) st_status_t;

    st_status_t status = ( st_status_t )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( b != SIXTRL_NULLPTR ) && ( NS(CBuffer_allow_allocate)( b ) ) )
    {
        st_size_t requ_buffer_size = ( st_size_t )0u;
        st_size_t const slot_size = NS(CBuffer_slot_size)( b );
        SIXTRL_ASSERT( NS(CBuffer_capacity)( b ) >= NS(CBuffer_size)( b ) );

        status = NS(CObjFlatBuffer_reallocate)( NS(CBuffer_p_base)( b ),
            NS(CBuffer_capacity)( b ), slot_size, max_n_slots, max_n_objects,
                max_n_pointers, max_n_garbage_ranges, &requ_buffer_size );

        if( ( status != ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS ) &&
            ( requ_buffer_size > NS(CBuffer_min_buffer_size)( slot_size ) ) &&
            ( requ_buffer_size > NS(CBuffer_capacity)( b ) ) )
        {
            NS(cobj_size_type) const requ_capacity =
                NS(CBuffer_reserve_scale_capacity)( b, requ_buffer_size );

            SIXTRL_ASSERT( NS(CBuffer_capacity)( b ) < requ_capacity );
            SIXTRL_ASSERT( requ_buffer_size <= requ_capacity );
            status = NS(CBuffer_reserve)( b, requ_capacity );

            if( ( status == ( st_status_t )SIXTRL_STATUS_SUCCESS ) &&
                ( requ_capacity <= NS(CBuffer_capacity)( b ) ) )
            {
                status = NS(CObjFlatBuffer_reallocate)( NS(CBuffer_p_base)( b ),
                    NS(CBuffer_capacity)( b ), slot_size, max_n_slots,
                        max_n_objects, max_n_pointers, max_n_garbage_ranges,
                            &requ_buffer_size );
            }
        }

        SIXTRL_ASSERT( ( status != ( st_status_t )SIXTRL_STATUS_SUCCESS ) ||
            ( ( requ_buffer_size <= NS(CBuffer_capacity)( b ) ) &&
              ( requ_buffer_size >= NS(CBuffer_min_buffer_size)( slot_size ) ) &&
              ( requ_buffer_size == NS(CObjFlatBuffer_size)(
                NS(CBuffer_p_const_base)( b ), slot_size ) ) &&
              ( ( st_size_t )0u  == NS(CBuffer_num_slots)( b ) ) &&
              ( ( st_size_t )0u  == NS(CBuffer_num_objects)( b ) ) &&
              ( ( st_size_t )0u  == NS(CBuffer_num_pointers)( b ) ) &&
              ( ( st_size_t )0u  == NS(CBuffer_num_garbage)( b ) ) &&
              ( max_n_slots          <= NS(CBuffer_max_slots)( b ) ) &&
              ( max_n_objects        <= NS(CBuffer_max_objects)( b ) ) &&
              ( max_n_pointers       <= NS(CBuffer_max_pointers)( b ) ) &&
              ( max_n_garbage_ranges <= NS(CBuffer_max_garbage)( b ) ) ) );
    }

    return status;
}

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CBuffer_needs_remapping)( SIXTRL_CBUFFER_ARGPTR_DEC const
    NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( ( NS(CBuffer_can_remap)( b ) ) &&
        ( NS(CObjFlatBuffer_needs_remapping)( NS(CBuffer_p_const_base)( b ),
            NS(CBuffer_slot_size)( b ) ) ) ); }

SIXTRL_INLINE bool NS(CBuffer_can_remap)( SIXTRL_CBUFFER_ARGPTR_DEC const
    NS(CBuffer) *const SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( ( b != SIXTRL_NULLPTR ) &&
             ( NS(CBuffer_p_const_base)( b ) != SIXTRL_NULLPTR ) &&
             ( NS(CBuffer_size)( b ) >=
               NS(CBuffer_min_buffer_size)( NS(CBuffer_slot_size)( b ) ) ) &&
             ( NS(CBuffer_allow_remap)( b ) ) ); }

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_remap)( SIXTRL_CBUFFER_ARGPTR_DEC
    NS(CBuffer)* SIXTRL_RESTRICT b ) SIXTRL_NOEXCEPT {
    return ( NS(CBuffer_can_remap)( b ) )
        ? NS(CObjFlatBuffer_remap)(
            NS(CBuffer_p_base)( b ), NS(CBuffer_slot_size)( b ) )
        : ( NS(cobj_status_type) )SIXTRL_STATUS_GENERAL_FAILURE; }

/* ========================================================================== */

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_reserve_factor_nominator)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( b != SIXTRL_NULLPTR )
    ? b->m_reserve_factor_nominator : ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_reserve_factor_denominator)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b
) SIXTRL_NOEXCEPT { return ( b != SIXTRL_NULLPTR )
    ? b->m_reserve_factor_denominator : ( NS(cobj_size_type) )0u; }

SIXTRL_INLINE void NS(CBuffer_set_reserve_factor_nominator)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const factor_nominator ) SIXTRL_NOEXCEPT {
    if( ( b != SIXTRL_NULLPTR ) &&
        ( factor_nominator > ( NS(cobj_size_type) )0u ) ) {
        b->m_reserve_factor_nominator = factor_nominator; } }

SIXTRL_INLINE void NS(CBuffer_set_reserve_factor_denominator)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const factor_denominator ) SIXTRL_NOEXCEPT {
    if( ( b != SIXTRL_NULLPTR ) &&
        ( factor_denominator > ( NS(cobj_size_type) )0u ) ) {
        b->m_reserve_factor_denominator = factor_denominator; } }

SIXTRL_INLINE void NS(CBuffer_set_reserve_factor)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const factor_nominator,
    NS(cobj_size_type) const factor_denominator ) SIXTRL_NOEXCEPT {
    if( ( b != SIXTRL_NULLPTR ) &&
        ( factor_nominator > ( NS(cobj_size_type) )0u ) &&
        ( factor_denominator >= factor_nominator  ) ) {
        b->m_reserve_factor_nominator   = factor_nominator;
        b->m_reserve_factor_denominator = factor_denominator; } }

SIXTRL_INLINE NS(cobj_size_type) NS(CBuffer_reserve_scale_capacity)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const capacity ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( b != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( b->m_reserve_factor_denominator > ( NS(cobj_size_type) )0u );
    SIXTRL_ASSERT( b->m_reserve_factor_nominator >=
                   b->m_reserve_factor_denominator );
    return ( b->m_reserve_factor_nominator * capacity ) /
             b->m_reserve_factor_denominator; }

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_init_c99_ptr_store)(
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_addr_type) addr_type;
    addr_type store_addr = ( addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;

    #if !defined( _GPUCODE )
    typedef NS(cobj_size_type) st_size_t;

    if( ( capacity != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_t )0u ) &&
        ( *capacity >= NS(CBuffer_min_buffer_size)( slot_size ) ) )
    {
        typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_raw_type) raw_type;
        typedef raw_type* raw_pointer;

        *capacity += slot_size;
        st_size_t const num_bytes_to_alloc = sizeof( raw_type ) * ( *capacity );
        raw_pointer ptr_storage = ( raw_pointer )malloc( num_bytes_to_alloc );
        store_addr = ( addr_type )( uintptr_t )ptr_storage;
    }

    #else /* defined( _GPUCODE ) */
    ( void )capacity;
    ( void )slot_size;

    #endif /* !defined( _GPUCODE ) */
    return store_addr; }

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_base_addr_from_c99_ptr_store)(
    NS(cobj_addr_type) const store_addr,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {

    typedef NS(cobj_addr_type) addr_type;
    addr_type base_addr = ( addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;

    #if !defined( _GPUCODE )
    typedef NS(cobj_size_type) st_size_t;

    if( (  store_addr != ( addr_type )SIXTRL_COBJECTS_NULL_ADDRESS ) &&
        (  slot_size > ( st_size_t )0u ) && (  capacity != SIXTRL_NULLPTR ) &&
        ( *capacity >= NS(CBuffer_min_buffer_size)( slot_size ) ) )
    {
        SIXTRL_ARGPTR_DEC st_size_t resulting_capacity = ( st_size_t )0u;
        base_addr = NS(CObjFlatBuffer_aligned_base_addr)( store_addr,
            *capacity, slot_size, &resulting_capacity, slot_size );

        if( ( base_addr != ( addr_type )SIXTRL_COBJECTS_NULL_ADDRESS ) &&
            ( resulting_capacity > NS(CBuffer_min_buffer_size)( slot_size ) ) )
        {
            *capacity = resulting_capacity;
        }
        else
        {
            base_addr = ( addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;
            *capacity = ( st_size_t )0u;
        }
    }

    #else /* defined( _GPUCODE ) */
    ( void )store_addr;
    ( void )capacity;
    ( void )slot_size;
    #endif /* !defined( _GPUCODE ) */

    return base_addr;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_free_c99_ptr_store)(
    NS(cobj_addr_type) const store_addr ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_status_type) status_t;
    status_t status = ( status_t )SIXTRL_STATUS_GENERAL_FAILURE;
    #if !defined( _GPUCODE )
    if( store_addr != ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS )
    {
        free( ( SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_raw_type)* )store_addr );
        status = ( status_t )SIXTRL_STATUS_SUCCESS;
    }
    #else /* defined( _GPUCODE ) */
    ( void )store_addr;
    #endif /* !defined( _GPUCODE ) */
    return status;
}

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_init_cxx_vector_store)(
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_addr_type) addr_type;
    addr_type store_addr = ( addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;

    #if !defined( _GPUCODE ) && defined( __cplusplus )
    typedef ::NS(cobj_size_type) st_size_t;

    if( ( slot_size > st_size_t{ 0 } ) && ( capacity != SIXTRL_NULLPTR ) &&
        ( *capacity >= NS(CBuffer_min_buffer_size)( slot_size ) ) )
    {
        typedef SIXTRL_CBUFFER_DATAPTR_DEC ::NS(cobj_raw_type) raw_type;
        typedef SIXTRL_CBUFFER_ARGPTR_DEC std::vector< raw_type > buffer_type;

        *capacity  += slot_size;
        buffer_type* raw_buffer = new buffer_type( *capacity, raw_type{ 0 } );

        if( ( raw_buffer != nullptr ) && ( raw_buffer->size() >= *capacity ) )
        {
            store_addr = static_cast< addr_type >( reinterpret_cast<
                uintptr_t >( raw_buffer ) );
        }
    }

    #else /* defined( _GPUCODE ) */
    ( void )capacity;
    ( void )slot_size;

    #endif /* !defined( _GPUCODE ) */
    return store_addr;
}

SIXTRL_INLINE NS(cobj_addr_type) NS(CBuffer_base_addr_from_cxx_vector_store)(
    NS(cobj_addr_type) const store_addr,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {

    typedef NS(cobj_addr_type) addr_type;
    addr_type base_addr = ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS;

    #if !defined( _GPUCODE ) && defined( __cplusplus )
    typedef ::NS(cobj_size_type) st_size_t;

    if( (  store_addr != addr_type{ SIXTRL_COBJECTS_NULL_ADDRESS } ) &&
        (  slot_size > st_size_t{ 0 } ) && (  capacity != SIXTRL_NULLPTR ) &&
        ( *capacity >= NS(CBuffer_min_buffer_size)( slot_size ) ) )
    {
        typedef SIXTRL_CBUFFER_DATAPTR_DEC ::NS(cobj_raw_type) raw_type;
        typedef SIXTRL_CBUFFER_ARGPTR_DEC std::vector< raw_type >
                raw_buffer_type;

        raw_buffer_type* ptr_raw_buffer = reinterpret_cast< raw_buffer_type* >(
            static_cast< uintptr_t >( store_addr ) );

        if( ptr_raw_buffer != nullptr )
        {
            SIXTRL_ARGPTR_DEC st_size_t resulting_capacity = st_size_t{ 0 };
            base_addr = ::NS(CObjFlatBuffer_aligned_base_addr)(
                static_cast< addr_type >( reinterpret_cast< uintptr_t >(
                    ptr_raw_buffer->data() ) ),
                *capacity, slot_size, &resulting_capacity, slot_size );

            if( ( base_addr != addr_type{ SIXTRL_COBJECTS_NULL_ADDRESS } ) &&
                ( resulting_capacity > NS(CBuffer_min_buffer_size)(
                    slot_size ) ) )
            {
                *capacity = resulting_capacity;
            }
            else
            {
                base_addr = addr_type{ SIXTRL_COBJECTS_NULL_ADDRESS };
                *capacity = st_size_t{ 0 };
            }
        }
    }

    #else /* defined( _GPUCODE ) */
    ( void )store_addr;
    ( void )capacity;
    ( void )slot_size;
    #endif /* !defined( _GPUCODE ) */

    return base_addr;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_free_cxx_vector_store)(
    NS(cobj_addr_type) const store_addr ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_status_type) status_t;
    status_t status = ( status_t )SIXTRL_STATUS_GENERAL_FAILURE;

    #if !defined( _GPUCODE ) && defined( __cplusplus )
    if( store_addr != ::NS(cobj_addr_type){ SIXTRL_COBJECTS_NULL_ADDRESS } )
    {
        typedef SIXTRL_CBUFFER_DATAPTR_DEC ::NS(cobj_raw_type) raw_type;
        typedef SIXTRL_CBUFFER_ARGPTR_DEC std::vector< raw_type >
                raw_buffer_type;

        raw_buffer_type* ptr_raw_buffer = reinterpret_cast< raw_buffer_type* >(
            static_cast< uintptr_t >( store_addr ) );

        SIXTRL_ASSERT( ptr_raw_buffer != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( ptr_raw_buffer->size() >=
            NS(CBuffer_min_buffer_size)( 0u ) );

        ptr_raw_buffer->clear();
        delete( ptr_raw_buffer );
        ptr_raw_buffer = SIXTRL_NULLPTR;
    }
    #else /* !defined( _GPUCODE ) */
    ( void )store_addr;
    #endif /* !defined( _GPUCODE ) */
    return status;
}

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_reserve)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) new_capacity )
{
    typedef NS(cobj_addr_type) addr_t;
    typedef NS(cobj_size_type) st_size_t;
    typedef NS(cobj_status_type) st_status_t;

    st_status_t status = ( st_status_t )SIXTRL_STATUS_GENERAL_FAILURE;
    st_size_t const current_capacity = NS(CBuffer_capacity)( b );
    st_size_t const slot_size = NS(CBuffer_slot_size)( b );

    if( ( b != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_t )0u ) )
    {
        if( new_capacity < NS(CBuffer_min_buffer_size)( slot_size ) )
            new_capacity = NS(CBuffer_min_buffer_size)( slot_size );

        if( new_capacity <= current_capacity )
        {
            status = ( st_status_t ) SIXTRL_STATUS_SUCCESS;
        }
        else if( ( NS(CBuffer_owns_stored_data)( b ) ) &&
            ( ( current_capacity == ( st_size_t )0u ) ||
              ( NS(CBuffer_allow_allocate)( b ) ) ||
              ( NS(CBuffer_allow_realloc)( b ) ) ) )
        {
            SIXTRL_STATIC_VAR addr_t const NULL_ADDR = (
                addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;

            SIXTRL_STATIC_VAR st_status_t const STATUS_FAILURE = (
                st_status_t )SIXTRL_STATUS_GENERAL_FAILURE;

            SIXTRL_STATIC_VAR st_status_t const STATUS_SUCCESS = (
                st_status_t )SIXTRL_STATUS_SUCCESS;

            st_size_t const slot_size = NS(CBuffer_slot_size)( b );
            addr_t const saved_base_addr  = NS(CBuffer_base_address)( b );
            addr_t const saved_store_addr = NS(CBuffer_datastore_address)( b );

            addr_t new_store_addr     = NULL_ADDR;
            addr_t new_base_addr      = NULL_ADDR;

            SIXTRL_ARGPTR_DEC st_size_t capacity = new_capacity;
            status = STATUS_SUCCESS;

            if( NS(CBuffer_storage_is_c_ptr)( b ) )
            {
                new_store_addr = NS(CBuffer_init_c99_ptr_store)(
                    &capacity, slot_size );
            }
            else if( NS(CBuffer_storage_is_cxx_vector)( b ) )
            {
                new_store_addr = NS(CBuffer_init_cxx_vector_store)(
                    &capacity, slot_size );
            }

            if( ( capacity < new_capacity ) || ( new_store_addr == NULL_ADDR ) )
            {
                status = STATUS_FAILURE;
            }

            if( status == STATUS_SUCCESS )
            {
                if( NS(CBuffer_storage_is_c_ptr)( b ) )
                {
                    new_base_addr = NS(CBuffer_base_addr_from_c99_ptr_store)(
                        new_store_addr, &capacity, slot_size );
                }
                else if( NS(CBuffer_storage_is_cxx_vector)( b ) )
                {
                    new_base_addr = NS(CBuffer_base_addr_from_cxx_vector_store)(
                        new_store_addr, &capacity, slot_size );
                }

                if( ( capacity < new_capacity ) ||
                    ( new_base_addr == NULL_ADDR ) )
                {
                    status = STATUS_FAILURE;
                }
            }

            if( status == STATUS_SUCCESS )
            {
                st_size_t const cur_buffer_size = NS(CBuffer_size)( b );
                new_capacity = capacity;

                if( current_capacity >= NS(CBuffer_min_buffer_size)(
                        slot_size ) )
                {
                    typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_raw_type) raw_type;
                    typedef raw_type* raw_pointer;

                    raw_pointer current_base_p = NS(CBuffer_p_base_begin)( b );
                    raw_pointer new_base_p = ( raw_pointer )(
                        uintptr_t )new_base_addr;

                    SIXTRL_ASSERT( new_base_p != SIXTRL_NULLPTR );
                    SIXTRL_ASSERT( current_base_p != SIXTRL_NULLPTR );

                    SIXTRACKLIB_COPY_VALUES(
                        raw_type, new_base_p, current_base_p, cur_buffer_size );

                    status = NS(CObjFlatBuffer_remap)( new_base_p, slot_size );
                }

                if( status == STATUS_SUCCESS )
                {
                    b->m_base_addr      = new_base_addr;
                    b->m_capacity       = new_capacity;
                    b->m_datastore_addr = new_store_addr;

                    if( NS(CBuffer_storage_is_c_ptr)( b ) )
                    {
                        status = NS(CBuffer_free_c99_ptr_store)(
                            saved_store_addr );
                    }
                    else if( NS(CBuffer_storage_is_cxx_vector)( b ) )
                    {
                        status = NS(CBuffer_free_cxx_vector_store)(
                            saved_store_addr );
                    }
                }
            }

            if( status != STATUS_SUCCESS )
            {
                if( new_store_addr != NULL_ADDR )
                {
                    if( NS(CBuffer_storage_is_c_ptr)( b ) )
                    {
                        status = NS(CBuffer_free_c99_ptr_store)( new_store_addr );
                        SIXTRL_ASSERT( status == STATUS_SUCCESS );
                    }
                    else if( NS(CBuffer_storage_is_cxx_vector)( b ) )
                    {
                        status = NS(CBuffer_free_cxx_vector_store)(
                            new_store_addr );
                        SIXTRL_ASSERT( status == STATUS_SUCCESS );
                    }
                }

                SIXTRL_ASSERT( saved_store_addr != new_store_addr );
                SIXTRL_ASSERT( saved_base_addr  != new_base_addr );

                b->m_base_addr      = saved_base_addr;
                b->m_capacity       = current_capacity;
                b->m_datastore_addr = saved_store_addr;
            }
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_reserve_detailed)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_pointers,
    NS(cobj_size_type) const max_num_garbage_ranges ) {

    NS(cobj_status_type) status = ( NS(cobj_status_type)
        )SIXTRL_STATUS_GENERAL_FAILURE;

    NS(cobj_size_type) capacity = NS(CObjFlatBuffer_calc_required_buffer_size)(
        NS(CBuffer_p_const_base)( b ), max_num_slots, max_num_objects,
            max_num_pointers, max_num_garbage_ranges,
                NS(CBuffer_slot_size)( b ) );

    status = NS(CBuffer_reserve)( b, capacity );

    SIXTRL_ASSERT( ( status != ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS ) ||
        ( ( NS(CBuffer_has_capacity_for_allocate)( b, max_num_slots,
            max_num_objects, max_num_pointers, max_num_garbage_ranges ) ) &&
          ( !NS(CBuffer_needs_remapping)( b ) ) ) );

    return status;
}

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_from_view)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT view ) {
    return NS(CBuffer_from_flat_buffer)( buffer, NS(CBuffer_p_const_base)(
        view ), NS(CBuffer_capacity)( view ) ); }

SIXTRL_INLINE NS(cobj_status_type) NS(CBuffer_from_flat_buffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT b,
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT flat_buffer_begin,
    NS(cobj_size_type) const flat_buffer_capacity )
{
    NS(cobj_status_type) status = (
        NS(cobj_status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    NS(cobj_size_type) const slot_size = NS(CBuffer_slot_size)( b );
    NS(cobj_size_type) f_size = ( NS(cobj_size_type) )0u;

    if( ( b != SIXTRL_NULLPTR ) &&
        ( flat_buffer_begin != SIXTRL_NULLPTR ) &&
        ( ( NS(cobj_size_type) )0u != slot_size ) &&
        ( NS(CBuffer_allow_remap)( b ) ) &&
        ( NS(CBuffer_p_const_base)( b ) != flat_buffer_begin ) &&
        ( NS(CObjFlatBuffer_has_cbuffer_structure)(
            flat_buffer_begin, flat_buffer_capacity, slot_size ) ) )
    {
        f_size = NS(CObjFlatBuffer_size)( flat_buffer_begin, slot_size );
    }

    if( f_size > NS(CBuffer_min_buffer_size)( slot_size ) )
    {
        if( NS(CBuffer_capacity)( b ) <= f_size )
        {
            status = ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS;
        }
        else if( NS(CBuffer_allow_realloc)( b ) )
        {
            status = NS(CObjFlatBuffer_init_empty)(
                NS(CBuffer_p_base)( b ), NS(CBuffer_capacity)( b ), slot_size );

            if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            {
                status = NS(CBuffer_reserve)( b,
                    NS(CBuffer_reserve_scale_capacity)( b, f_size ) );
            }
        }

        if( ( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS ) &&
            ( NS(CBuffer_capacity)( b ) < f_size ) )
        {
            status = ( NS(cobj_status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
        }

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
        {
            typedef NS(cobj_raw_type) raw_type;

            SIXTRL_ASSERT( NS(CBuffer_capacity)( b ) >= f_size );
            SIXTRACKLIB_COPY_VALUES(
                raw_type, NS(CBuffer_p_base)( b ), flat_buffer_begin, f_size );

            if( NS(CBuffer_needs_remapping)( b ) )
            {
                status = NS(CBuffer_remap)( b );
            }
        }
    }

    return status;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE bool NS(CBuffer_can_add_copy_of_object)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const obj_type_size,
    NS(cobj_size_type) const num_dataptrs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_pointers
) SIXTRL_NOEXCEPT {
    return ( ( NS(CBuffer_allow_append)( buffer ) ) &&
             ( NS(CObjFlatBuffer_can_add_copy_of_object)(
                NS(CBuffer_p_const_base)( buffer ),
                    NS(CBuffer_slot_size)( buffer ), obj_type_size,
                        num_dataptrs, sizes, counts, requ_buffer_size,
                            requ_n_slots, requ_n_objects, requ_n_pointers) ) );
}

SIXTRL_INLINE bool NS(CBuffer_can_add_copy_of_trivial_object)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const obj_type_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_pointers
) SIXTRL_NOEXCEPT { return NS(CBuffer_can_add_copy_of_object)( buffer,
    obj_type_size, 0u, SIXTRL_NULLPTR, SIXTRL_NULLPTR, requ_buffer_size,
        requ_n_slots, requ_n_objects, requ_n_pointers ); }

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
NS(CBuffer_add_copy_of_object_detailed)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT obj_handle,
    NS(cobj_size_type) const reserved_obj_handle_size,
    NS(cobj_size_type) const actual_obj_handle_size,
    NS(cobj_obj_id_type) const type_id,
    NS(cobj_size_type) const num_dataptrs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    bool fill_with_zeros ) {
    typedef NS(cobj_size_type) st_size_t;
    typedef NS(cobj_obj_id_type) type_id_t;
    typedef NS(cobj_status_type) st_status_t;
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* ptr_added_obj = SIXTRL_NULLPTR;

    if( ( buffer != SIXTRL_NULLPTR ) && ( obj_handle != SIXTRL_NULLPTR ) &&
        ( NS(CBuffer_allow_append)( buffer ) ) &&
        ( type_id != ( type_id_t )SIXTRL_COBJECTS_TYPE_ID_ILLEGAL ) &&
        ( type_id != ( type_id_t )SIXTRL_COBJECTS_TYPE_ID_UNDEFINED ) &&
        ( actual_obj_handle_size > ( st_size_t )0u ) &&
        ( reserved_obj_handle_size >= actual_obj_handle_size ) )
    {
        SIXTRL_ARGPTR_DEC st_size_t requ_buffer_size = ( st_size_t )0u;
        SIXTRL_ARGPTR_DEC st_size_t requ_n_slots     = ( st_size_t )0u;
        SIXTRL_ARGPTR_DEC st_size_t requ_n_objects   = ( st_size_t )0u;
        SIXTRL_ARGPTR_DEC st_size_t requ_n_pointers  = ( st_size_t )0u;

        bool can_add_object = NS(CBuffer_can_add_copy_of_object)( buffer,
            reserved_obj_handle_size, num_dataptrs, sizes, counts,
                &requ_buffer_size, &requ_n_slots, &requ_n_objects,
                    &requ_n_pointers );

        if( ( !can_add_object ) &&
            ( requ_buffer_size > NS(CBuffer_size)( buffer ) ) &&
            ( NS(CBuffer_allow_realloc)( buffer ) ) )
        {
            st_size_t const new_capacity = NS(CBuffer_reserve_scale_capacity)(
                buffer, requ_buffer_size );

            st_status_t status = NS(CBuffer_reserve)( buffer, new_capacity );

            if( ( st_status_t )SIXTRL_STATUS_SUCCESS == status )
            {
                status = NS(CObjFlatBuffer_reallocate)(
                    NS(CBuffer_p_base_begin)( buffer ), NS(CBuffer_capacity)(
                        buffer ), NS(CBuffer_slot_size)( buffer ), requ_n_slots,
                            requ_n_objects, requ_n_pointers,
                                NS(CBuffer_max_garbage)( buffer ),
                                    &requ_buffer_size );
            }

            if( ( st_status_t )SIXTRL_STATUS_SUCCESS == status )
            {
                can_add_object = NS(CBuffer_can_add_copy_of_object)( buffer,
                    reserved_obj_handle_size, num_dataptrs, sizes, counts,
                        SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
                            SIXTRL_NULLPTR );
            }
        }

        if( can_add_object )
        {
            ptr_added_obj = NS(CObjFlatBuffer_add_copy_of_object_detailed)(
                NS(CBuffer_p_base)( buffer ), NS(CBuffer_slot_size)( buffer ),
                    obj_handle, reserved_obj_handle_size, actual_obj_handle_size,
                        type_id, num_dataptrs, offsets, sizes, counts,
                            fill_with_zeros );
        }
    }

    return ptr_added_obj;
}

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)*
NS(CBuffer_add_copy_of_object)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT obj_handle,
    NS(cobj_size_type) const obj_handle_size,
    NS(cobj_obj_id_type) const type_id,
    NS(cobj_size_type) const num_dataptrs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    bool fill_with_zeros ) { return NS(CBuffer_add_copy_of_object_detailed)(
        buffer, obj_handle, obj_handle_size, obj_handle_size, type_id,
            num_dataptrs, offsets, sizes, counts, fill_with_zeros ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)*
NS(CBuffer_add_copy_of_trivial_object)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT obj_handle,
    NS(cobj_size_type) const obj_handle_size,
    NS(cobj_obj_id_type) const type_id, bool fill_with_zeros ) {
    return NS(CBuffer_add_copy_of_object)( buffer, obj_handle, obj_handle_size,
        type_id, 0u, SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
            fill_with_zeros ); }

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_COMMON_COBJECTS_CBUFFER_C99_H__ */
