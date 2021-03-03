#ifndef SIXTRACKLIB_COMMON_COBJECTS_FLAT_BUFFER_C99_H__
#define SIXTRACKLIB_COMMON_COBJECTS_FLAT_BUFFER_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* SIXTRL_NO_INCLUDES */

#if !defined(  SIXTRL_NO_SYSTEM_INCLUDES )
    #if !defined( _cplusplus )
        #include <stdbool.h>
    #endif /* C++ */
#endif /* !defined(  SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( _cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( _cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* *******               Minimal Flat Buffer Interface              ******** */
/* ************************************************************************* */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_slot_based_size)(
    NS(cobj_size_type) const in_length,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type) const*
NS(CObjFlatBuffer_ptr_const_header)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type)*
NS(CObjFlatBuffer_ptr_header)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjFlatBuffer_section_entity_size)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const header_section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjFlatBuffer_size_section_header)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_size_header)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_size)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_section_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CObjFlatBuffer_ptr_const_section_begin)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const header_section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer)
NS(CObjFlatBuffer_ptr_section_begin)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const header_section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_is_section_header_consistent)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_section_max_size)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjFlatBuffer_section_num_entities)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_calc_section_size)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id, NS(cobj_size_type) const num_entities,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_section_size)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjFlatBuffer_section_max_num_entities)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_section_offset)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(CObjFlatBuffer_set_section_num_entities)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const num_entities,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(CObjFlatBuffer_set_section_max_size)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const max_section_size,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(CObjFlatBuffer_section_init)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const num_elements_in_section,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_section_end_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CObjFlatBuffer_ptr_const_section_end)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const header_section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer)
NS(CObjFlatBuffer_ptr_section_end)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const header_section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_section_data_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CObjFlatBuffer_ptr_const_section_data_begin)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const header_section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer)
NS(CObjFlatBuffer_ptr_section_data_begin)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const header_section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_section_data_end_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_const_pointer)
NS(CObjFlatBuffer_ptr_const_section_data_end)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const header_section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_raw_pointer)
NS(CObjFlatBuffer_ptr_section_data_end)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const header_section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_num_slots)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_num_indices)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_num_pointers)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_num_garbage_ranges)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_max_num_slots)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_max_num_indices)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_max_num_pointers)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjFlatBuffer_max_num_garbage_ranges)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_size_slots)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_size_indices)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_size_pointers)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_size_garbage_ranges)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_max_size_slots)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_max_size_indices)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_max_size_pointers)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjFlatBuffer_max_size_garbage_ranges)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CObjFlatBuffer_slots_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_indices_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_pointers_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_garbage_ranges_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* ========================================================================= */

struct NS(CObjIndex);

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const*
NS(CObjFlatBuffer_const_index)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const pos_in_buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
NS(CObjFlatBuffer_index)( NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const pos_in_buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const*
NS(CObjFlatBuffer_const_indices_begin)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const*
NS(CObjFlatBuffer_const_indices_end)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT end,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
NS(CObjFlatBuffer_indices_begin)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
NS(CObjFlatBuffer_indices_end)( NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_num_objects)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_max_num_objects)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_size_objects)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_max_size_objects)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_objects_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_objects_end_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_objects_data_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_objects_data_end_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_index_begin_addr_by_pos_in_buffer_filter_by_type_info)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const pos_in_buffer,
    NS(cobj_obj_id_type) const required_type_id,
    NS(cobj_size_type) const min_size,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* ************************************************************************* */
/* ******                          Remapping                         ******* */
/* ************************************************************************* */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_stored_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type)
NS(CObjFlatBuffer_buffer_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_needs_remapping)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CObjFlatBuffer_aligned_base_addr)(
    NS(cobj_addr_type) const raw_base_addr,
    NS(cobj_size_type) const raw_capacity,
    NS(cobj_size_type) alignment,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* ptr_capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_diff_type)
NS(CObjFlatBuffer_address_to_offset)(
    NS(cobj_addr_type) const raw_base_addr,
    NS(cobj_addr_type) const target_address,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_addr_type) NS(CObjFlatBuffer_offset_to_address)(
    NS(cobj_addr_type) const raw_base_addr, NS(cobj_addr_diff_type) const offset,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CObjFlatBuffer_base_addr_offset)(
    SIXTRL_ARGPTR_DEC NS(cobj_addr_diff_type)* SIXTRL_RESTRICT oset,
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CObjFlatBuffer_remap_header)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_diff_type) const* SIXTRL_RESTRICT oset,
    NS(cobj_size_type) const slot_size )  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CObjFlatBuffer_remap_section_slots)(
    NS(cobj_raw_pointer)  SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_diff_type) const* SIXTRL_RESTRICT offsets,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(CObjFlatBuffer_remap_section_indices)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_diff_type) const* SIXTRL_RESTRICT oset,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(CObjFlatBuffer_remap_section_dataptrs)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_diff_type) const* SIXTRL_RESTRICT oset,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(CObjFlatBuffer_remap_section_garbage)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_diff_type) const* SIXTRL_RESTRICT oset,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CObjFlatBuffer_remap)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(CObjFlatBuffer_apply_addr_offset)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_addr_diff_type) const addr_offset,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* ************************************************************************* */
/* ******                  Load / Store API support                  ******* */
/* ************************************************************************* */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(CObjFlatBuffer_store_obj_same_layout_parameters_from_argptr)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const pos_in_buffer, NS(cobj_size_type) const slot_size,
    NS(cobj_obj_id_type) const type_id,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT obj_to_store,
    NS(cobj_size_type) const obj_size, NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_type)* SIXTRL_RESTRICT save_ptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const pos_in_buffer, NS(cobj_size_type) const slot_size,
    NS(cobj_obj_id_type) const type_id,
    SIXTRL_CBUFFER_ARGPTR_DEC void* SIXTRL_RESTRICT obj_to_store,
    NS(cobj_size_type) const obj_size, NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_type)* SIXTRL_RESTRICT save_ptrs
) SIXTRL_NOEXCEPT;

/* ************************************************************************* */
/* ******                  Change Layout / Reserve                   ******* */
/* ************************************************************************* */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjFlatBuffer_predict_required_num_bytes)(
    NS(cobj_size_type) const obj_handle_size,
    NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjFlatBuffer_predict_required_num_slots)(
    NS(cobj_size_type) const obj_handle_size,
    NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjFlatBuffer_calc_required_buffer_size)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_dataptrs,
    NS(cobj_size_type) const max_num_garbage_ranges,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type)
NS(CObjFlatBuffer_predict_required_buffer_size)(
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_dataptrs,
    NS(cobj_size_type) const max_num_garbage_ranges,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_min_buffer_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_type) NS(CObjFlatBuffer_header_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_has_cbuffer_structure)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const current_buffer_capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CObjFlatBuffer_init_empty)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const current_buffer_capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(CObjFlatBuffer_init_empty_detailed)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const max_n_slots, NS(cobj_size_type) const max_n_objs,
    NS(cobj_size_type) const max_n_ptrs, NS(cobj_size_type) const max_n_garbage,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_can_allocate)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const max_n_slots, NS(cobj_size_type) const max_n_objs,
    NS(cobj_size_type) const max_n_ptrs, NS(cobj_size_type) const max_n_garbage,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_can_reallocate)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const max_n_slots, NS(cobj_size_type) const max_n_objs,
    NS(cobj_size_type) const max_n_ptrs, NS(cobj_size_type) const max_n_garbage,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_max_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_max_n_objs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_max_n_ptrs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_max_n_garbage
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CObjFlatBuffer_allocate)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const max_n_slots, NS(cobj_size_type) const max_n_objs,
    NS(cobj_size_type) const max_n_ptrs, NS(cobj_size_type) const max_n_garbage,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_buffer_length
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CObjFlatBuffer_reallocate)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const max_n_slots, NS(cobj_size_type) const max_n_objs,
    NS(cobj_size_type) const max_n_ptrs, NS(cobj_size_type) const max_n_garbage,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size
)  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type) NS(CObjFlatBuffer_clear)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    bool const set_data_to_zero,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* ************************************************************************* */
/* ******       Add / ( Remove? ) Objects To The Buffer API          ******* */
/* ************************************************************************* */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_can_add_copy_of_object)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const obj_handle_size,
    NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_objs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_num_ptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_can_add_copy_of_trivial_object)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const obj_handle_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_objs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_num_ptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
NS(CObjFlatBuffer_add_copy_of_object_detailed)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_type) const reserved_obj_size,
    NS(cobj_size_type) const actual_obj_size,
    NS(cobj_obj_id_type) const type_id, NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
NS(CObjFlatBuffer_add_copy_of_object)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_type) const obj_size,
    NS(cobj_obj_id_type) const type_id, NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex)*
NS(CObjFlatBuffer_add_copy_of_trivial_object)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_type) const obj_size,
    NS(cobj_obj_id_type) const type_id,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT;

#if defined( _cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( _cplusplus ) && !defined( _GPUCODE ) */

/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
/* ||||||||||            implementation of inline methods          ||||||||| */
/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/address_manipulations.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/garbage_range.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( _cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( _cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* *******         Additional internal functions and helpers        ******** */
/* ************************************************************************* */

/* ------------------------------------------------------------------------- */
/* Helper functions for adding a copy of an object to a flat buffer          */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(_CObjFlatBuffer_memcpy_from_argptr_to_dataptr)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT destination,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT source,
    NS(cobj_size_type) const num_bytes_to_copy,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(_CObjFlatBuffer_memcpy_from_dataptr_to_argptr)(
    SIXTRL_CBUFFER_ARGPTR_DEC void* SIXTRL_RESTRICT destination,
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT source,
    NS(cobj_size_type) const num_bytes_to_copy,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(_CObjFlatBuffer_add_copy_of_object_obj_handle_part)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_type) const obj_size,
    NS(cobj_size_type) const predicted_stored_bytes_in_slots,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(_CObjFlatBuffer_add_copy_of_object_ptrs_part)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_type) const obj_size,
    NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(_CObjFlatBuffer_add_copy_of_object_ptr_field_part)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_type) const obj_size,
    SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type)* ptr_to_pointer_in_section,
    NS(cobj_addr_type) const stored_obj_begin_addr,
    NS(cobj_size_type) const field_offset_from_stored_obj_begin,
    NS(cobj_addr_type) const storage_field_data_begin_addr,
    NS(cobj_size_type) const storage_field_data_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)*
NS(_CObjFlatBuffer_add_copy_of_object_index_part)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(cobj_obj_id_type) const type_id,
    NS(cobj_size_type) const num_bytes_stored_in_slots,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_type)
NS(_CObjFlatBuffer_add_copy_of_object_update_buffer_params)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const requ_num_slots,
    NS(cobj_size_type) const requ_num_objects,
    NS(cobj_size_type) const requ_num_ptrs ) SIXTRL_NOEXCEPT;

#if defined( _cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( _cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* *******               Minimal Flat Buffer Interface              ******** */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/index_object.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( _cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( _cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_slot_based_size)(
    NS(cobj_size_type) const in_length,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type)  st_size_type;
    st_size_type slot_based_length;

    SIXTRL_ASSERT( slot_size > ( st_size_type )0u );

    slot_based_length  = in_length / slot_size;
    slot_based_length *= slot_size;

    return ( slot_based_length == in_length )
        ? slot_based_length : ( slot_based_length + slot_size );
}

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type) const*
NS(CObjFlatBuffer_ptr_const_header)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;
    typedef NS(cobj_addr_type) st_addr_type;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC st_addr_type const* addr_pointer;

    addr_pointer ptr_header = SIXTRL_NULLPTR;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_type )0 ) )
    {
        st_addr_type const buffer_addr = ( st_addr_type )(uintptr_t )buffer;

        SIXTRL_ASSERT( buffer_addr % slot_size == ( st_addr_type )0 );
        SIXTRL_ASSERT( NS(CObjFlatBuffer_slot_based_size)(
            sizeof( st_addr_type ), slot_size ) > ( st_size_type )0u );

        ptr_header = ( addr_pointer )( uintptr_t )buffer_addr;
    }

    return ptr_header;
}

SIXTRL_INLINE SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type)*
NS(CObjFlatBuffer_ptr_header)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type)* addr_pointer;
    return ( addr_pointer )NS(CObjFlatBuffer_ptr_const_header)(
        buffer, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_section_entity_size)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_type) entity_size = ( NS(cobj_size_type) )0u;

    SIXTRL_ASSERT( slot_size != ( NS(cobj_size_type) )0u );
    SIXTRL_ASSERT( ( buffer == SIXTRL_NULLPTR ) ||
                   ( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u ) );

    ( void )buffer;

    switch( section_id )
    {
        case SIXTRL_CBUFFER_SECTION_ID_SLOTS:
        {
            entity_size = slot_size;
            break;
        }

        case SIXTRL_CBUFFER_SECTION_ID_INDICES:
        {
            entity_size = NS(CObjFlatBuffer_slot_based_size)(
                        sizeof( NS(CObjIndex) ), slot_size );
            break;
        }

        case SIXTRL_CBUFFER_SECTION_ID_POINTERS:
        {
            entity_size = NS(CObjFlatBuffer_slot_based_size)(
                        sizeof( NS(cobj_addr_type) const* ), slot_size );
            break;
        }

        case SIXTRL_CBUFFER_SECTION_ID_GARBAGE:
        {
            entity_size = NS(CObjFlatBuffer_slot_based_size)(
                        sizeof( NS(CObjGarbageRange) ), slot_size );
            break;
        }

        default:
        {
            entity_size = ( NS(cobj_size_type) )0u;
        }
    };

    return entity_size;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_size_section_header)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_type) sec_header_size = ( NS(cobj_size_type) )0u;

    if( ( slot_size > ( NS(cobj_size_type) )0u )&&
        ( section_id >= SIXTRL_CBUFFER_SECTION_ID_SLOTS ) &&
        ( section_id <= SIXTRL_CBUFFER_SECTION_ID_GARBAGE ) )
    {
        sec_header_size = NS(CObjFlatBuffer_slot_based_size)(
            sizeof( NS(cobj_size_type) ) * ( NS(cobj_size_type) )2, slot_size );

        SIXTRL_ASSERT( ( buffer == SIXTRL_NULLPTR ) ||
            ( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u ) );
        SIXTRL_ASSERT( sec_header_size > ( NS(cobj_size_type) )0u );

        ( void )buffer;
    }

    return sec_header_size;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_size_header)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_type) header_size = ( NS(cobj_size_type) )0u;

    SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type) const* ptr_header =
        NS(CObjFlatBuffer_ptr_const_header)( buffer, slot_size );

    if( ptr_header != SIXTRL_NULLPTR )
    {
        /* NOTE: Check for remap here ? */
        SIXTRL_ASSERT( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] >=
                       ptr_header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ] );

        header_size = ( NS(cobj_size_type)
            )ptr_header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ];
    }

    return header_size;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_size)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_type) buffer_size = ( NS(cobj_size_type) )0u;

    SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type) const* ptr_header =
        NS(CObjFlatBuffer_ptr_const_header)( buffer, slot_size );

    if( ptr_header != SIXTRL_NULLPTR )
    {
        /* NOTE: Check for remap here ? */
        SIXTRL_ASSERT( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] >=
                       ptr_header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ] );

        buffer_size = ( NS(cobj_size_type)
            )ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ];
    }

    return buffer_size;
}

/* -- -- -- -- */

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_section_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const section_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_addr_type) begin_addr =
        ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS;

    SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type) const* ptr_header =
        NS(CObjFlatBuffer_ptr_const_header)( buffer, slot_size );

    if( ( ptr_header != SIXTRL_NULLPTR ) &&
        ( section_id >= SIXTRL_CBUFFER_SECTION_ID_SLOTS ) &&
        ( section_id <= SIXTRL_CBUFFER_SECTION_ID_GARBAGE ) )
    {
        SIXTRL_ASSERT( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ] ==
                       ( uintptr_t )ptr_header );

        SIXTRL_ASSERT( ptr_header[ section_id ] >=
            ( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ] +
              ptr_header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ] ) );

        begin_addr = ptr_header[ section_id ];
    }

    return begin_addr;
}

SIXTRL_INLINE NS(cobj_raw_const_pointer)
NS(CObjFlatBuffer_ptr_const_section_begin)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(cobj_raw_const_pointer) )( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );
}

SIXTRL_INLINE NS(cobj_raw_pointer)
NS(CObjFlatBuffer_ptr_section_begin)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(cobj_raw_pointer) )( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE bool NS(CObjFlatBuffer_is_section_header_consistent)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_size_type) const* ptr_size_t;

    NS(cobj_size_type) const sec_header_size =
        NS(CObjFlatBuffer_size_section_header)( buffer, sec_id, slot_size );

    NS(cobj_size_type) const sec_entity_size =
        NS(CObjFlatBuffer_section_entity_size)( buffer, sec_id, slot_size );

    ptr_size_t ptr_sec_header = ( ptr_size_t )( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    return (
        ( ptr_sec_header != SIXTRL_NULLPTR ) &&
        ( slot_size > ( NS(cobj_size_type) )0u ) &&
        ( ( uintptr_t )ptr_sec_header % slot_size == ( uintptr_t )0u ) &&
        ( sec_entity_size > ( NS(cobj_size_type) )0u ) &&
        ( sec_entity_size % slot_size == ( NS(cobj_size_type) )0u ) &&
        ( sec_header_size > ( NS(cobj_size_type) )0u ) &&
        ( sec_header_size % slot_size == ( NS(cobj_size_type) )0u ) &&
        ( ptr_sec_header[ 0 ] >= sec_header_size ) &&
        ( ptr_sec_header[ 0 ] % slot_size == ( NS(cobj_size_type) )0u ) &&
        ( ptr_sec_header[ 0 ] >=
          ( sec_header_size + ptr_sec_header[ 1 ] * sec_entity_size ) ) );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_section_max_size)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_size_type) const* ptr_size_t;

    NS(cobj_size_type) max_section_size = ( NS(cobj_size_type) )0u;
    ptr_size_t ptr_sec_header = ( ptr_size_t )( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    if( ptr_sec_header != SIXTRL_NULLPTR )
    {
        SIXTRL_ASSERT( NS(CObjFlatBuffer_is_section_header_consistent)(
            buffer, sec_id, slot_size ) );

        max_section_size = ptr_sec_header[ 0 ];
    }

    return max_section_size;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_section_num_entities)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_size_type) const* ptr_size_t;

    NS(cobj_size_type) num_entities = ( NS(cobj_size_type) )0u;

    ptr_size_t ptr_sec_header = ( ptr_size_t )( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    if( ptr_sec_header != SIXTRL_NULLPTR )
    {
        SIXTRL_ASSERT( NS(CObjFlatBuffer_is_section_header_consistent)(
            buffer, sec_id, slot_size ) );

        num_entities = ptr_sec_header[ 1 ];
    }

    return num_entities;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_calc_section_size)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id, NS(cobj_size_type) const num_entities,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_type) calc_section_size = ( NS(cobj_size_type) )0u;

    NS(cobj_size_type) const sec_header_size =
        NS(CObjFlatBuffer_size_section_header)( buffer, sec_id, slot_size );

    NS(cobj_size_type) const sec_entity_size =
        NS(CObjFlatBuffer_section_entity_size)( buffer, sec_id, slot_size );

    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );

    if( ( slot_size > ( NS(cobj_size_type) )0u ) &&
        ( sec_entity_size > ( NS(cobj_size_type) )0u ) &&
        ( sec_header_size > ( NS(cobj_size_type) )0u ) )
    {
        SIXTRL_ASSERT( sec_header_size % slot_size == ( NS(cobj_size_type) )0u );
        SIXTRL_ASSERT( sec_entity_size % slot_size == ( NS(cobj_size_type) )0u );

        calc_section_size = sec_header_size + num_entities * sec_entity_size;
    }

    return calc_section_size;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_section_size)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_type) const section_size =
        NS(CObjFlatBuffer_size_section_header)(  buffer, sec_id, slot_size ) +
      ( NS(CObjFlatBuffer_section_num_entities)( buffer, sec_id, slot_size ) *
        NS(CObjFlatBuffer_section_entity_size)(  buffer, sec_id, slot_size ) );

    SIXTRL_ASSERT( section_size <= NS(CObjFlatBuffer_section_max_size)(
        buffer, sec_id, slot_size ) );

    return section_size;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_section_max_num_entities)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_type) const sec_header_size =
        NS(CObjFlatBuffer_size_section_header)( buffer, sec_id, slot_size );

    NS(cobj_size_type) const sec_max_size =
        NS(CObjFlatBuffer_section_max_size)( buffer, sec_id, slot_size );

    NS(cobj_size_type) const sec_entity_size =
        NS(CObjFlatBuffer_section_entity_size)( buffer, sec_id, slot_size );

    NS(cobj_size_type) const max_num_elements =
        ( ( sec_header_size <= sec_max_size ) &&
             ( sec_entity_size > ( NS(cobj_size_type) )0u ) )
        ? ( sec_max_size - sec_header_size ) / sec_entity_size
        : ( NS(cobj_size_type) )0u;

    SIXTRL_ASSERT( max_num_elements >= NS(CObjFlatBuffer_section_num_entities)(
        buffer, sec_id, slot_size ) );

    return max_num_elements;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_section_offset)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_addr_diff_type) section_offset = ( NS(cobj_addr_diff_type) )0u;

    SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type) const* ptr_header =
        NS(CObjFlatBuffer_ptr_const_header)( buffer, slot_size );

    if( ( ptr_header != SIXTRL_NULLPTR ) &&
        ( sec_id >= SIXTRL_CBUFFER_SECTION_ID_SLOTS ) &&
        ( sec_id <= SIXTRL_CBUFFER_SECTION_ID_GARBAGE ) &&
        ( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ] <=
          ptr_header[ sec_id ] ) )
    {
        section_offset = ( ptr_header[ sec_id ] -
            ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ] );
    }

    return section_offset;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_set_section_num_entities)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const num_entities,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_size_type)* ptr_sec_header_t;
    NS(cobj_status_type) status = ( NS(cobj_status_type)
        )SIXTRL_STATUS_GENERAL_FAILURE;

    ptr_sec_header_t ptr_sec_header = ( ptr_sec_header_t)( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    if( ptr_sec_header != SIXTRL_NULLPTR )
    {
        SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
        SIXTRL_ASSERT( ( uintptr_t )ptr_sec_header % slot_size == 0u );

        ptr_sec_header[ 1 ] = num_entities;
        status = ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_set_section_max_size)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const max_section_size,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_size_type)* ptr_sec_header_t;
    NS(cobj_status_type) status = ( NS(cobj_status_type)
        )SIXTRL_STATUS_GENERAL_FAILURE;

    ptr_sec_header_t ptr_sec_header = ( ptr_sec_header_t)( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    if( ( ptr_sec_header != SIXTRL_NULLPTR ) &&
        ( slot_size > ( NS(cobj_size_type) )0u ) &&
        ( max_section_size % slot_size == ( NS(cobj_size_type) )0u ) &&
        ( max_section_size >= NS(CObjFlatBuffer_size_section_header)(
                buffer, sec_id, slot_size ) ) )
    {
        ptr_sec_header[ 0 ] = max_section_size;
        status = ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_section_init)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const num_elements_in_section,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_size_type)* ptr_sec_header_t;

    NS(cobj_status_type) status = ( NS(cobj_status_type)
        )SIXTRL_STATUS_GENERAL_FAILURE;

    ptr_sec_header_t ptr_sec_header = ( ptr_sec_header_t )( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    st_size_type const section_size = NS(CObjFlatBuffer_calc_section_size)(
        buffer, sec_id, num_elements_in_section, slot_size );

    if( ( ptr_sec_header != SIXTRL_NULLPTR ) && ( slot_size >( st_size_type )0u ) &&
        ( section_size > ( st_size_type )0u ) )
    {
        ptr_sec_header[ 0 ] = section_size;
        ptr_sec_header[ 1 ] = num_elements_in_section;
        status = ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS;
    }

    return status;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_section_end_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_STATIC_VAR NS(cobj_addr_type) SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
        ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS;

    NS(cobj_size_type) const sec_max_size =
        NS(CObjFlatBuffer_section_max_size)( buffer, sec_id, slot_size );

    NS(cobj_addr_type) data_begin_addr =
        NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    return ( data_begin_addr != NULL_ADDR )
         ? ( data_begin_addr + sec_max_size ) : NULL_ADDR;
}


SIXTRL_INLINE NS(cobj_raw_const_pointer)
NS(CObjFlatBuffer_ptr_const_section_end)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(cobj_raw_const_pointer) )( uintptr_t
        )NS(CObjFlatBuffer_section_end_addr)( buffer, sec_id, slot_size );
}

SIXTRL_INLINE NS(cobj_raw_pointer) NS(CObjFlatBuffer_ptr_section_end)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(cobj_raw_pointer) )( uintptr_t
        )NS(CObjFlatBuffer_section_end_addr)( buffer, sec_id, slot_size );
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_section_data_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_STATIC_VAR NS(cobj_addr_type) SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
        ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS;

    NS(cobj_size_type) const sec_header_size=
        NS(CObjFlatBuffer_size_section_header)( buffer, sec_id, slot_size );

    NS(cobj_addr_type) data_begin_addr =
        NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    return ( data_begin_addr != NULL_ADDR )
         ? ( data_begin_addr + sec_header_size ) : NULL_ADDR;
}


SIXTRL_INLINE NS(cobj_raw_const_pointer)
NS(CObjFlatBuffer_ptr_const_section_data_begin)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(cobj_raw_const_pointer) )( uintptr_t
        )NS(CObjFlatBuffer_section_data_begin_addr)(buffer, sec_id, slot_size);
}

SIXTRL_INLINE NS(cobj_raw_pointer)
NS(CObjFlatBuffer_ptr_section_data_begin)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(cobj_raw_pointer) )( uintptr_t
        )NS(CObjFlatBuffer_section_data_begin_addr)(buffer, sec_id, slot_size);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cobj_addr_type)
NS(CObjFlatBuffer_section_data_end_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_STATIC_VAR NS(cobj_addr_type) SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
        ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS;

    NS(cobj_size_type) const sec_size=
        NS(CObjFlatBuffer_section_size)( buffer, sec_id, slot_size );

    NS(cobj_addr_type) data_begin_addr =
        NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    return ( data_begin_addr != NULL_ADDR )
         ? ( data_begin_addr + sec_size ) : NULL_ADDR;
}

SIXTRL_INLINE NS(cobj_raw_const_pointer)
NS(CObjFlatBuffer_ptr_const_section_data_end)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(cobj_raw_const_pointer) )( uintptr_t
        )NS(CObjFlatBuffer_section_data_end_addr)( buffer, sec_id, slot_size );
}

SIXTRL_INLINE NS(cobj_raw_pointer)
NS(CObjFlatBuffer_ptr_section_data_end)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const sec_id,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(cobj_raw_pointer) )( uintptr_t
        )NS(CObjFlatBuffer_section_data_end_addr)( buffer, sec_id, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_num_slots)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_num_indices)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_num_pointers)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_num_garbage_ranges)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_max_num_slots)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_max_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_max_num_indices)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_max_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_max_num_pointers)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_max_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type)
NS(CObjFlatBuffer_max_num_garbage_ranges)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_max_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_size_slots)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_size_indices)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_size_pointers)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_size_garbage_ranges)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_max_size_slots)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_max_size_indices)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_max_size_pointers)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type)
NS(CObjFlatBuffer_max_size_garbage_ranges)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_slots_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_begin_addr)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );
}

SIXTRL_INLINE NS(cobj_addr_type)
NS(CObjFlatBuffer_indices_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_begin_addr)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_addr_type)
NS(CObjFlatBuffer_pointers_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_begin_addr)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );
}

SIXTRL_INLINE NS(cobj_addr_type)
NS(CObjFlatBuffer_garbage_ranges_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_begin_addr)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );
}

/* ========================================================================= */

SIXTRL_INLINE NS(cobj_obj_index_const_pointer) NS(CObjFlatBuffer_const_index)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const pos_in_buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_obj_index_const_pointer) indices_begin =
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size );

    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == 0u );
    SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) );

    return ( ( indices_begin != SIXTRL_NULLPTR ) &&
             ( NS(CObjFlatBuffer_num_objects)( buffer, slot_size ) >
               pos_in_buffer ) )
           ? ( indices_begin + pos_in_buffer ) : SIXTRL_NULLPTR;
}

SIXTRL_INLINE NS(cobj_obj_index_pointer) NS(CObjFlatBuffer_index)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const pos_in_buffer,
    NS(cobj_size_type) const slot_size )  SIXTRL_NOEXCEPT
{
    return ( NS(cobj_obj_index_pointer) )NS(CObjFlatBuffer_const_index)(
        buffer, pos_in_buffer, slot_size );
}

SIXTRL_INLINE NS(cobj_obj_index_const_pointer)
NS(CObjFlatBuffer_const_indices_begin)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(cobj_obj_index_const_pointer) )( uintptr_t
        )NS(CObjFlatBuffer_section_data_begin_addr)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_obj_index_const_pointer)
NS(CObjFlatBuffer_const_indices_end)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_obj_index_const_pointer) indices_end =
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size );

    return ( indices_end != SIXTRL_NULLPTR )
        ? ( indices_end + NS(CObjFlatBuffer_num_objects)( buffer, slot_size ) )
        : SIXTRL_NULLPTR;
}

SIXTRL_INLINE NS(cobj_obj_index_pointer) NS(CObjFlatBuffer_indices_begin)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(cobj_obj_index_pointer) )( uintptr_t
        )NS(CObjFlatBuffer_section_data_begin_addr)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_obj_index_pointer) NS(CObjFlatBuffer_indices_end)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_obj_index_pointer) indices_end =
        NS(CObjFlatBuffer_indices_begin)( buffer, slot_size );

    return ( indices_end != SIXTRL_NULLPTR )
        ? ( indices_end + NS(CObjFlatBuffer_num_objects)( buffer, slot_size ) )
        : SIXTRL_NULLPTR;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_num_objects)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_num_entities)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_max_num_objects)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_max_num_entities)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_size_objects)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_max_size_objects)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_max_num_entities)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_objects_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_begin_addr)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_objects_end_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_end_addr)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_objects_data_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_objects_data_end_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_data_end_addr)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_addr_type)
NS(CObjFlatBuffer_index_begin_addr_by_pos_in_buffer_filter_by_type_info)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const pos_in_buffer,
    NS(cobj_obj_id_type) const required_type_id,
    NS(cobj_size_type) const min_size,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjIndex_begin_addr_filter_by_type_info)(
        NS(CObjFlatBuffer_const_index)( buffer, pos_in_buffer, slot_size ),
            required_type_id, min_size, slot_size );
}

/* ************************************************************************* */
/* ******                          Remapping                         ******* */
/* ************************************************************************* */

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_stored_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type) const* ptr_header =
        NS(CObjFlatBuffer_ptr_const_header)( buffer, slot_size );

    return ( ptr_header != SIXTRL_NULLPTR )
        ? ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ]
        : ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS;
}

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_buffer_begin_addr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type)  )0u );
    SIXTRL_ASSERT( ( ( ( uintptr_t )buffer ) % slot_size ) == 0u );
    ( void )slot_size;

    return ( NS(cobj_addr_type) )( uintptr_t )buffer;
}

SIXTRL_INLINE bool NS(CObjFlatBuffer_needs_remapping)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type) const* ptr_header =
        NS(CObjFlatBuffer_ptr_const_header)( buffer, slot_size );

    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );

    return ( ( ptr_header != SIXTRL_NULLPTR ) &&
             ( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ] !=
               ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS ) &&
             ( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ] !=
               ( ( NS(cobj_addr_type) )( uintptr_t )buffer ) ) );
}

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_aligned_base_addr)(
    NS(cobj_addr_type) const raw_base_addr,
    NS(cobj_size_type) const raw_capacity,
    NS(cobj_size_type) alignment,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* ptr_capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_addr_type) addr_type;
    addr_type base_addr = ( addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;
    NS(cobj_size_type) capacity  = ( NS(cobj_size_type) )0u;
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );

    if( alignment == ( NS(cobj_size_type) )0u )
        alignment = slot_size;
    else if( ( alignment % slot_size ) != ( NS(cobj_size_type) )0u )
        alignment = NS(CObjFlatBuffer_slot_based_size)( alignment, slot_size );

    if( ( raw_base_addr != ( addr_type )SIXTRL_COBJECTS_NULL_ADDRESS ) &&
        ( alignment > ( NS(cobj_size_type) )0u ) &&
        ( raw_capacity >= alignment ) )
    {
        addr_type const mis_align = raw_base_addr % alignment;
        base_addr = raw_base_addr;
        capacity = raw_capacity;

        if( mis_align != ( addr_type )0u )
        {
            NS(cobj_size_type) const offset = alignment - mis_align;
            base_addr += offset;
            capacity  -= offset;
        }
    }

    if(  ptr_capacity != SIXTRL_NULLPTR ) *ptr_capacity = capacity;
    return base_addr; }


SIXTRL_INLINE NS(cobj_addr_diff_type) NS(CObjFlatBuffer_address_to_offset)(
    NS(cobj_addr_type) const raw_base_addr,
    NS(cobj_addr_type) const target_address,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    SIXTRL_ASSERT( raw_base_addr % slot_size == ( NS(cobj_size_type) )0u );
    SIXTRL_ASSERT( raw_base_addr != (
        NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS );
    return ( ( target_address >= raw_base_addr ) &&
             ( ( target_address % slot_size ) == ( NS(cobj_addr_type) )0u ) )
        ? ( target_address - raw_base_addr ) : ( NS(cobj_addr_type) )0u; }

SIXTRL_INLINE NS(cobj_addr_type) NS(CObjFlatBuffer_offset_to_address)(
    NS(cobj_addr_type) const raw_base_addr, NS(cobj_addr_diff_type) const offset,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return ( NS(CObjFlatBuffer_check_addr_arithmetic)(
                raw_base_addr, offset, slot_size ) )
        ? NS(CObjFlatBuffer_perform_addr_shift)(
            raw_base_addr, offset, slot_size )
        : ( NS(cobj_addr_type) )SIXTRL_COBJECTS_NULL_ADDRESS; }

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_base_addr_offset)(
    SIXTRL_ARGPTR_DEC NS(cobj_addr_diff_type)*
        SIXTRL_RESTRICT ptr_addr_offset,
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_status_type) status = ( NS(cobj_status_type)
        )SIXTRL_STATUS_GENERAL_FAILURE;
    NS(cobj_addr_diff_type) addr_offset = ( NS(cobj_addr_diff_type) )0u;

    SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type) const* ptr_header =
        NS(CObjFlatBuffer_ptr_const_header)( buffer, slot_size );

    if( ptr_header != SIXTRL_NULLPTR )
    {
        NS(cobj_addr_type) const stored_addr =
            ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ];

        NS(cobj_addr_type) const base_addr =
            ( NS(cobj_addr_type) )( uintptr_t )buffer;

        SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
        SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );

        addr_offset = ( base_addr > stored_addr )
            ?    ( NS(cobj_addr_diff_type) )( base_addr - stored_addr )
            : -( ( NS(cobj_addr_diff_type) )( stored_addr - base_addr ) );

        if( ptr_addr_offset != SIXTRL_NULLPTR )
        {
            *ptr_addr_offset = addr_offset;
        }

        status = ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_remap_header)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_diff_type) const*
        SIXTRL_RESTRICT offsets,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_addr_type) st_addr_type;
    typedef NS(cobj_addr_diff_type) st_addr_diff_type;
    typedef NS(cobj_size_type) st_size_type;

    SIXTRL_CBUFFER_DATAPTR_DEC st_addr_type* header =
            NS(CObjFlatBuffer_ptr_header)( buffer, slot_size );

    SIXTRL_CBUFFER_ARGPTR_DEC st_addr_diff_type base_addr_offset = ( st_addr_diff_type )0u;
    NS(cobj_status_type) status = NS(CObjFlatBuffer_base_addr_offset)(
        &base_addr_offset, buffer, slot_size );

    if( ( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) ||
        ( base_addr_offset != offsets[ 0 ] ) ||
        ( header == SIXTRL_NULLPTR ) )
    {
        return SIXTRL_STATUS_GENERAL_FAILURE;
    }

    SIXTRL_ASSERT( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS );
    SIXTRL_ASSERT( offsets != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_type) )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );

    if( base_addr_offset != ( st_addr_diff_type )0u )
    {
        SIXTRL_STATIC_VAR st_addr_type SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
            ( st_addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;

        st_size_type const sec_ids[ 5 ] =
        {
            ( st_size_type )SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR,
            ( st_size_type )SIXTRL_CBUFFER_SECTION_ID_SLOTS,
            ( st_size_type )SIXTRL_CBUFFER_SECTION_ID_INDICES,
            ( st_size_type )SIXTRL_CBUFFER_SECTION_ID_POINTERS,
            ( st_size_type )SIXTRL_CBUFFER_SECTION_ID_GARBAGE
        };

        st_addr_type remapped[ 5 ] = { 0u, 0u, 0u, 0u, 0u };

        SIXTRL_ASSERT( header[ sec_ids[ 4 ] ] > header[ sec_ids[ 3 ] ] );
        SIXTRL_ASSERT( header[ sec_ids[ 3 ] ] > header[ sec_ids[ 2 ] ] );
        SIXTRL_ASSERT( header[ sec_ids[ 2 ] ] > header[ sec_ids[ 1 ] ] );
        SIXTRL_ASSERT( header[ sec_ids[ 1 ] ] > header[ sec_ids[ 0 ] ] );

        for( st_size_type ii = ( st_size_type )0 ; ii < ( st_size_type )5 ; ++ii )
        {
            remapped[ ii ] = NS(CObjFlatBuffer_perform_addr_shift)(
                header[ sec_ids[ ii ] ], offsets[ ii ], slot_size );

            if( remapped[ ii ] == NULL_ADDR )
            {
                status = ( NS(cobj_status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                break;
            }
        }

        if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
            ( remapped[ 0 ] == ( st_addr_type )( uintptr_t )buffer ) )
        {
            for( st_size_type ii = ( st_size_type )0u ; ii < ( st_size_type )5u ; ++ii )
            {
                header[ sec_ids[ ii ] ] = remapped[ ii ];
            }
        }
        else if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        {
            status = ( NS(cobj_status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_remap_section_slots)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_diff_type) const*
        SIXTRL_RESTRICT SIXTRL_UNUSED( offsets ),
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(CObjFlatBuffer_is_section_header_consistent)(
                buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) )
        ? SIXTRL_STATUS_SUCCESS
        : SIXTRL_STATUS_GENERAL_FAILURE;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_remap_section_indices)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_diff_type) const*
        SIXTRL_RESTRICT offsets,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_status_type) st_status_type;
    typedef NS(cobj_addr_type) st_addr_type;
    typedef NS(cobj_addr_diff_type) st_addr_diff_type;
    typedef NS(cobj_size_type)  st_size_type;

    st_status_type status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( offsets != SIXTRL_NULLPTR ) &&
        ( NS(CObjFlatBuffer_is_section_header_consistent)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size ) ) )
    {
        status = ( st_status_type )SIXTRL_STATUS_SUCCESS;

        if( ( offsets[ 1 ] != ( st_addr_diff_type )0u ) &&
            ( NS(CObjFlatBuffer_num_indices)( buffer,slot_size ) >
              ( st_size_type )0u ) )
        {
            st_addr_type const slots_begin_addr =
                NS(CObjFlatBuffer_section_data_begin_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            st_addr_type const slots_end_addr =
                NS(CObjFlatBuffer_section_data_end_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            st_addr_type min_legal_next_addr = slots_begin_addr;

            NS(cobj_obj_index_pointer) it =
                NS(CObjFlatBuffer_indices_begin)( buffer, slot_size );

            NS(cobj_obj_index_pointer) end =
                NS(CObjFlatBuffer_indices_end)( buffer, slot_size );

            SIXTRL_ASSERT( it != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( ( uintptr_t )it <= ( uintptr_t )end );

            for( ; it != end ; ++it )
            {
                st_addr_type const obj_begin_addr = NS(CObjIndex_begin_addr)( it );
                st_addr_type const r_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                        obj_begin_addr, offsets[ 1 ], slot_size );

                SIXTRL_ASSERT( NS(CObjIndex_size)( it ) % slot_size ==
                               ( st_size_type )0u );

                SIXTRL_ASSERT( min_legal_next_addr >= slots_begin_addr );
                SIXTRL_ASSERT( min_legal_next_addr <  slots_end_addr );

                if( ( r_addr != ( st_addr_type )SIXTRL_COBJECTS_NULL_ADDRESS ) &&
                    ( r_addr < slots_end_addr ) &&
                    ( r_addr >= min_legal_next_addr ) )
                {
                    SIXTRL_ASSERT( r_addr % slot_size == ( st_addr_type )0u );
                    SIXTRL_ASSERT( min_legal_next_addr % slot_size ==
                                   ( st_addr_type )0 );

                    min_legal_next_addr = r_addr + NS(CObjIndex_size)( it );
                    NS(CObjIndex_set_begin_addr)( it, r_addr );
                }
                else
                {
                    status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_remap_section_dataptrs)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_diff_type) const*
        SIXTRL_RESTRICT offsets,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_status_type) st_status_type;
    typedef NS(cobj_size_type) st_size_type;
    typedef NS(cobj_addr_diff_type) st_addr_diff_type;
    typedef NS(cobj_addr_type) st_addr_type;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC st_addr_type*  addr_pointer;

    st_status_type status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( offsets != SIXTRL_NULLPTR ) &&
        ( NS(CObjFlatBuffer_is_section_header_consistent)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size ) ) )
    {
        status = ( st_status_type )SIXTRL_STATUS_SUCCESS;

        if( ( offsets[ 1 ] != ( st_addr_diff_type )0u ) &&
            ( NS(CObjFlatBuffer_num_pointers)( buffer,slot_size ) >
              ( st_size_type )0u ) )
        {
            SIXTRL_STATIC_VAR st_addr_type SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
                ( st_addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;

            st_addr_type const slots_begin_addr =
                NS(CObjFlatBuffer_section_data_begin_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            st_addr_type const slots_end_addr =
                NS(CObjFlatBuffer_section_data_end_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            addr_pointer it = ( addr_pointer )( uintptr_t
                )NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

            addr_pointer end = ( addr_pointer )( uintptr_t
                )NS(CObjFlatBuffer_section_data_end_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

            SIXTRL_ASSERT( it != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( slots_begin_addr <= slots_end_addr );
            SIXTRL_ASSERT( slots_begin_addr != NULL_ADDR );
            SIXTRL_ASSERT( slots_end_addr   != NULL_ADDR );

            for( ; it != end ; ++it )
            {
                st_addr_type const r_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                    *it, offsets[ 1 ], slot_size );

                addr_pointer ptr_in_slots = ( addr_pointer )( uintptr_t )r_addr;

                st_addr_type const r_slot_addr = ( r_addr != NULL_ADDR )
                    ? NS(CObjFlatBuffer_perform_addr_shift)(
                        *ptr_in_slots, offsets[ 1 ], slot_size )
                    : NULL_ADDR;

                if( ( r_addr != NULL_ADDR ) &&
                    ( r_addr >= slots_begin_addr ) &&
                    ( r_addr <  slots_end_addr ) &&
                    ( r_slot_addr != NULL_ADDR ) &&
                    ( r_slot_addr >= slots_begin_addr ) &&
                    ( r_slot_addr <  slots_end_addr ) )
                {
                    *ptr_in_slots = r_slot_addr;
                    *it = r_addr;
                }
                else
                {
                    status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_remap_section_garbage)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_diff_type) const*
        SIXTRL_RESTRICT offsets,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_status_type) st_status_type;
    typedef NS(cobj_size_type) st_size_type;
    typedef NS(cobj_addr_diff_type) st_addr_diff_type;
    typedef NS(cobj_addr_type) st_addr_type;
    typedef NS(CObjGarbageRange) garbage_range_t;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC garbage_range_t* ptr_to_garbage_t;

    st_status_type status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( offsets != SIXTRL_NULLPTR ) &&
        ( NS(CObjFlatBuffer_is_section_header_consistent)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size ) ) )
    {
        status = ( st_status_type )SIXTRL_STATUS_SUCCESS;

        if( ( offsets[ 1 ] != ( st_addr_diff_type )0u ) &&
            ( NS(CObjFlatBuffer_num_pointers)( buffer,slot_size ) >
              ( st_size_type )0u ) )
        {
            SIXTRL_STATIC_VAR st_addr_type SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
                ( st_addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;

            st_addr_type const slots_begin_addr =
                NS(CObjFlatBuffer_section_data_begin_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            st_addr_type const slots_end_addr =
                NS(CObjFlatBuffer_section_data_end_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            ptr_to_garbage_t it = ( ptr_to_garbage_t )( uintptr_t
                )NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

            ptr_to_garbage_t end = ( ptr_to_garbage_t )( uintptr_t
                )NS(CObjFlatBuffer_section_data_end_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

            SIXTRL_ASSERT( it != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( slots_begin_addr <= slots_end_addr );
            SIXTRL_ASSERT( slots_begin_addr != NULL_ADDR );
            SIXTRL_ASSERT( slots_end_addr   != NULL_ADDR );

            for( ; it != end ; ++it )
            {
                st_addr_type const addr = NS(CObjGarbageRange_begin_addr)( it );

                st_addr_type const r_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                    addr, offsets[ 1 ], slot_size );

                if( ( r_addr != NULL_ADDR ) &&
                    ( r_addr >= slots_begin_addr ) &&
                    ( r_addr <  slots_end_addr ) )
                {
                    NS(CObjGarbageRange_set_begin_addr)( it, r_addr );
                }
                else
                {
                    status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }
    }

    return status;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_remap)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size )
{
    typedef NS(cobj_status_type) st_status_type;
    NS(cobj_addr_diff_type) base_addr_offset = ( NS(cobj_addr_diff_type) )0;
    NS(cobj_status_type) status = NS(CObjFlatBuffer_base_addr_offset)(
        &base_addr_offset, buffer, slot_size );

    if( ( status == ( st_status_type )SIXTRL_STATUS_SUCCESS ) &&
        ( base_addr_offset != ( NS(cobj_addr_diff_type) )0 ) )
    {
        NS(cobj_addr_diff_type) const offsets[] =
        {
            base_addr_offset, base_addr_offset, base_addr_offset,
            base_addr_offset, base_addr_offset
        };

        status  = NS(CObjFlatBuffer_remap_header)(
            buffer, offsets, slot_size );

        status |= NS(CObjFlatBuffer_remap_section_slots)(
            buffer, offsets, slot_size );

        status |= NS(CObjFlatBuffer_remap_section_indices)(
            buffer, offsets, slot_size );

        status |= NS(CObjFlatBuffer_remap_section_dataptrs)(
            buffer, offsets, slot_size );

        status |= NS(CObjFlatBuffer_remap_section_garbage)(
            buffer, offsets, slot_size );
    }

    return status;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_apply_addr_offset)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_addr_diff_type) const addr_offset,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_status_type) st_status_type;
    typedef NS(cobj_addr_type) st_addr_type;
    typedef NS(cobj_addr_diff_type) st_addr_diff_type;
    typedef NS(cobj_size_type) st_size_type;
    typedef NS(CObjGarbageRange)  garbage_range_t;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC st_addr_type* addr_pointer;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC garbage_range_t* ptr_garbage_t;

    st_status_type status = ( st_status_type )SIXTRL_STATUS_SUCCESS;
    addr_pointer header = NS(CObjFlatBuffer_ptr_header)( buffer, slot_size );

    if( ( addr_offset != ( st_addr_diff_type )0 ) && ( header != SIXTRL_NULLPTR ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) )
    {
        SIXTRL_STATIC_VAR st_addr_type SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
            ( st_addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;

        st_size_type const num_objects = NS(CObjFlatBuffer_num_objects)(
            buffer, slot_size );

        st_size_type const num_pointers = NS(CObjFlatBuffer_num_pointers)(
            buffer, slot_size );

        st_size_type const num_garbage_ranges =
            NS(CObjFlatBuffer_num_garbage_ranges)( buffer, slot_size );

        st_addr_type const slot_begin_addr =
            NS(CObjFlatBuffer_section_begin_addr)( buffer,
                ( st_size_type )SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

        st_addr_type const slot_end_addr = NS(CObjFlatBuffer_section_end_addr)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

        st_addr_type const r_slot_begin_addr =
            NS(CObjFlatBuffer_perform_addr_shift)( slot_begin_addr, addr_offset,
                slot_size );

        st_addr_type const r_slot_end_addr =
            NS(CObjFlatBuffer_perform_addr_shift)( slot_end_addr, addr_offset,
                slot_size );

        if( ( r_slot_begin_addr == NULL_ADDR ) ||
            ( r_slot_end_addr == NULL_ADDR ) ||
            ( slot_begin_addr == NULL_ADDR ) ||
            ( slot_end_addr == NULL_ADDR ) )
        {
            return SIXTRL_STATUS_GENERAL_FAILURE;
        }

        if( num_garbage_ranges > ( st_size_type )0u )
        {
            ptr_garbage_t it  = ( ptr_garbage_t )( uintptr_t
                )NS(CObjFlatBuffer_section_data_begin_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

            ptr_garbage_t end  = ( ptr_garbage_t )( uintptr_t
                )NS(CObjFlatBuffer_section_data_end_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

            SIXTRL_ASSERT( it != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( ( uintptr_t )end >= ( uintptr_t )it );
            SIXTRL_ASSERT( ( st_size_type )( end - it ) == num_garbage_ranges );

            for( ; it != end ; ++it )
            {
                st_addr_type const addr = NS(CObjGarbageRange_begin_addr)( it );
                st_addr_type const r_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                    addr, addr_offset, slot_size );

                SIXTRL_ASSERT( addr != NULL_ADDR );
                SIXTRL_ASSERT( addr >= slot_begin_addr );
                SIXTRL_ASSERT( addr <  slot_end_addr );

                if( r_addr == NULL_ADDR )
                {
                    status = ( NS(cobj_status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }

                NS(CObjGarbageRange_set_begin_addr)( it, r_addr );
            }
        }

        if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
            ( num_pointers > ( st_size_type )0 ) )
        {
            addr_pointer it  = ( addr_pointer )( uintptr_t
                )NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

            addr_pointer end = ( addr_pointer )( uintptr_t
                )NS(CObjFlatBuffer_section_data_end_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

            SIXTRL_ASSERT( it != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( ( uintptr_t )end >= ( uintptr_t )it );
            SIXTRL_ASSERT( ( st_size_type )( end - it ) == num_pointers );

            for( ; it != end ; ++it )
            {
                addr_pointer slot_ptr = ( addr_pointer )( uintptr_t )*it;

                st_addr_type const r_slot_addr = ( *it != NULL_ADDR )
                    ? NS(CObjFlatBuffer_perform_addr_shift)( *slot_ptr,
                        addr_offset, slot_size )
                    : NULL_ADDR;

                st_addr_type const r_slot_ptr_addr =
                    NS(CObjFlatBuffer_perform_addr_shift)(
                        *it, addr_offset, slot_size );

                SIXTRL_ASSERT( *it >= slot_begin_addr );
                SIXTRL_ASSERT( *it <  slot_end_addr );
                SIXTRL_ASSERT(  slot_ptr != SIXTRL_NULLPTR );
                SIXTRL_ASSERT( *slot_ptr >= slot_begin_addr );
                SIXTRL_ASSERT( *slot_ptr <  slot_end_addr );

                if( ( r_slot_addr == NULL_ADDR ) ||
                    ( r_slot_ptr_addr == NULL_ADDR ) )
                {
                    status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }

                SIXTRL_ASSERT( r_slot_addr     >= r_slot_begin_addr );
                SIXTRL_ASSERT( r_slot_addr     <  r_slot_end_addr   );
                SIXTRL_ASSERT( r_slot_ptr_addr >= r_slot_begin_addr );
                SIXTRL_ASSERT( r_slot_ptr_addr <  r_slot_end_addr   );

                *slot_ptr = r_slot_addr;
                *it       = r_slot_ptr_addr;
            }
        }

        if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
            ( num_objects > ( st_size_type )0u ) )
        {
            NS(cobj_obj_index_pointer) it = NS(CObjFlatBuffer_indices_begin)(
                buffer, slot_size );

            NS(cobj_obj_index_pointer) end = NS(CObjFlatBuffer_indices_end)(
                buffer, slot_size );

            SIXTRL_ASSERT( it != SIXTRL_NULLPTR );

            for( ; it != end ; ++it )
            {
                st_addr_type const obj_addr = NS(CObjIndex_begin_addr)( it );

                if( obj_addr != NULL_ADDR )
                {
                    st_addr_type const r_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                        obj_addr, addr_offset, slot_size );

                    SIXTRL_ASSERT( obj_addr >= slot_begin_addr );
                    SIXTRL_ASSERT( obj_addr <  slot_end_addr );
                    SIXTRL_ASSERT( r_addr   >= r_slot_begin_addr );
                    SIXTRL_ASSERT( r_addr   <  r_slot_end_addr );

                    if( r_addr == NULL_ADDR )
                    {
                        status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    NS(CObjIndex_set_begin_addr)( it, r_addr );
                }
            }
        }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        {
            st_addr_type const r_base_addr =
                NS(CObjFlatBuffer_perform_addr_shift)( header[
                    SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ], addr_offset,
                        slot_size );

            st_addr_type const r_slots_addr =
                NS(CObjFlatBuffer_perform_addr_shift)( header[
                    SIXTRL_CBUFFER_SECTION_ID_SLOTS ], addr_offset, slot_size );

            st_addr_type const r_objs_addr =
                NS(CObjFlatBuffer_perform_addr_shift)( header[
                    SIXTRL_CBUFFER_SECTION_ID_INDICES ], addr_offset,
                        slot_size );

            st_addr_type const r_ptrs_addr =
                NS(CObjFlatBuffer_perform_addr_shift)( header[
                    SIXTRL_CBUFFER_SECTION_ID_POINTERS ], addr_offset,
                        slot_size );

            st_addr_type const r_garbage_addr =
                NS(CObjFlatBuffer_perform_addr_shift)( header[
                    SIXTRL_CBUFFER_SECTION_ID_GARBAGE ], addr_offset,
                        slot_size );

            if( ( r_base_addr != NULL_ADDR ) && ( r_slots_addr != NULL_ADDR ) &&
                ( r_objs_addr != NULL_ADDR ) && ( r_ptrs_addr  != NULL_ADDR ) &&
                ( r_garbage_addr != NULL_ADDR ) )
            {
                header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ] = r_base_addr;
                header[ SIXTRL_CBUFFER_SECTION_ID_SLOTS     ] = r_slots_addr;
                header[ SIXTRL_CBUFFER_SECTION_ID_INDICES   ] = r_objs_addr;
                header[ SIXTRL_CBUFFER_SECTION_ID_POINTERS  ] = r_ptrs_addr;
                header[ SIXTRL_CBUFFER_SECTION_ID_GARBAGE   ] = r_garbage_addr;
            }
            else
            {
                status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
            }
        }
    }
    else if( addr_offset != ( st_addr_diff_type )0 )
    {
        status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
    }

    return status;
}

/* ************************************************************************* */
/* ******                  Load / Store API support                  ******* */
/* ************************************************************************* */

SIXTRL_INLINE NS(cobj_status_type)
NS(CObjFlatBuffer_store_obj_same_layout_parameters_from_argptr)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const pos_in_buffer, NS(cobj_size_type) const slot_size,
    NS(cobj_obj_id_type) const type_id,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT obj_to_store,
    NS(cobj_size_type) const obj_size, NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_type)* SIXTRL_RESTRICT save_ptrs
) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_status_type) st_status_type;
    typedef NS(cobj_size_type)   st_size_type;
    typedef NS(cobj_addr_type)   st_addr_type;
    typedef NS(cobj_raw_type)    st_raw_type;

    SIXTRL_STATIC_VAR st_addr_type SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
        ( st_addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;

    st_status_type status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
    NS(cobj_obj_index_const_pointer) index_obj = NS(CObjFlatBuffer_const_index)(
        buffer, pos_in_buffer, slot_size );

    SIXTRL_ASSERT( type_id != (
        NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_ILLEGAL );

    if( (  index_obj != SIXTRL_NULLPTR ) &&
        (  NS(CObjIndex_type_id)( index_obj ) == type_id ) &&
        (  NS(CObjIndex_begin_addr)( index_obj ) != NULL_ADDR ) &&
        (  NS(CObjIndex_size)( index_obj ) >= obj_size ) &&
        ( obj_size > ( st_size_type )0u ) && ( obj_to_store != SIXTRL_NULLPTR ) )
    {
        typedef SIXTRL_CBUFFER_DATAPTR_DEC st_addr_type*       ptr_dest_addr_type;
        typedef SIXTRL_CBUFFER_DATAPTR_DEC st_raw_type*        ptr_dest_data_t;
        typedef SIXTRL_CBUFFER_ARGPTR_DEC  st_addr_type const* ptr_src_addr_t;
        typedef SIXTRL_CBUFFER_ARGPTR_DEC  st_raw_type  const* ptr_src_data_t;

        st_addr_type const src_begin_addr = ( st_addr_type )(
            uintptr_t )obj_to_store;

        st_addr_type const dest_begin_addr =
            NS(CObjIndex_begin_addr)( index_obj );

        ptr_dest_data_t dest_begin = (
            ptr_dest_data_t )( uintptr_t )dest_begin_addr;

        st_size_type const storage_obj_size =
                NS(CObjFlatBuffer_slot_based_size)( obj_size, slot_size );

        status = ( st_status_type )SIXTRL_STATUS_SUCCESS;

        SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)(
            buffer, slot_size ) );

        SIXTRL_ASSERT( NS(CObjIndex_begin_addr)( index_obj ) % slot_size ==
                       ( st_addr_type )0u );

        if( ( num_pointers > ( st_size_type )0u ) &&
            ( save_ptrs != SIXTRL_NULLPTR ) )
        {
            st_size_type ii = ( st_size_type )0u;

            SIXTRL_ASSERT( src_begin_addr % slot_size == ( st_addr_type )0u );
            SIXTRL_ASSERT( offsets   != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( sizes     != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( counts    != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( save_ptrs != SIXTRL_NULLPTR );

            SIXTRL_ASSERT( offsets   != sizes );
            SIXTRL_ASSERT( offsets   != counts );
            SIXTRL_ASSERT( counts    != sizes );

            for( ; ii < num_pointers ; ++ii )
            {
                st_size_type const field_offset = offsets[ ii ];

                ptr_dest_addr_type ptr_dest_field_addr = ( ptr_dest_addr_type)(
                    uintptr_t )( dest_begin_addr + field_offset );

                ptr_src_addr_t ptr_src_field_addr = ( ptr_src_addr_t )(
                    uintptr_t )( src_begin_addr + field_offset );

                if( ( ( field_offset % slot_size ) != ( st_size_type )0u ) ||
                    ( ( field_offset + slot_size ) > obj_size ) )
                {
                    status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }

                if( ( ( save_ptrs[ ii ] == NULL_ADDR ) ||
                      ( *ptr_src_field_addr == NULL_ADDR ) ) &&
                    ( counts[ ii ] * sizes[ ii ] > ( st_size_type )0u ) )
                {
                    status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }

                save_ptrs[ ii ] = *( ptr_dest_field_addr );
            }
        }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        {
            if( storage_obj_size > obj_size )
            {
                SIXTRL_STATIC_VAR st_raw_type const ZBYTE = ( st_raw_type )0u;
                SIXTRACKLIB_SET_VALUES( st_raw_type, dest_begin,
                                        storage_obj_size, ZBYTE );
            }

            status = NS(_CObjFlatBuffer_memcpy_from_argptr_to_dataptr)(
                dest_begin, obj_to_store, obj_size, slot_size );
        }

        if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
            ( num_pointers > ( st_size_type )0u ) )
        {
            st_size_type const requ_storage_size =
                NS(CObjFlatBuffer_predict_required_num_bytes)(
                    obj_size, num_pointers, sizes, counts, slot_size );

            st_size_type ii = ( st_size_type )0u;

            SIXTRL_ASSERT( requ_storage_size >= storage_obj_size );
            SIXTRL_ASSERT( requ_storage_size % slot_size == ( st_size_type )0u );
            SIXTRL_ASSERT( requ_storage_size >=
                NS(CObjIndex_size)( index_obj ) );
            SIXTRL_ASSERT( save_ptrs != SIXTRL_NULLPTR );

            ( void )requ_storage_size;

            for( ; ii < num_pointers ; ++ii )
            {
                st_size_type const field_offset = offsets[ ii ];
                st_size_type const field_size = NS(CObjFlatBuffer_slot_based_size)(
                    sizes[ ii ] * counts[ ii ], slot_size );

                ptr_src_addr_t ptr_field_src_addr = ( ptr_src_addr_t )(
                    uintptr_t )( src_begin_addr + field_offset );

                ptr_src_data_t ptr_field_src = ( ptr_src_data_t )(
                    uintptr_t )( *ptr_field_src_addr );

                ptr_dest_addr_type ptr_field_dest_addr = ( ptr_dest_addr_type )(
                    uintptr_t )( dest_begin_addr + field_offset );

                ptr_dest_data_t ptr_field_dest = ( ptr_dest_data_t )(
                    uintptr_t )save_ptrs[ ii ];

                SIXTRL_ASSERT( ( field_offset % slot_size ) == ( st_size_type )0u );
                SIXTRL_ASSERT( ( field_offset + slot_size ) <= obj_size );

                *ptr_field_dest_addr = save_ptrs[ ii ];

                if( ( save_ptrs[ ii ] == NULL_ADDR ) ||
                    ( *ptr_field_src_addr == NULL_ADDR ) ||
                    ( field_size == ( st_size_type )0u ) )
                {
                    if( ( save_ptrs[ ii ] != NULL_ADDR ) ||
                        ( *ptr_field_src_addr != NULL_ADDR ) ||
                        ( field_size > ( st_size_type )0u ) )
                    {
                        status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
                    }
                }

                if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
                {
                    status = NS(_CObjFlatBuffer_memcpy_from_argptr_to_dataptr)(
                        ptr_field_dest, ptr_field_src, field_size, slot_size );
                }

                if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) break;
            }
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type)
NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const pos_in_buffer, NS(cobj_size_type) const slot_size,
    NS(cobj_obj_id_type) const type_id,
    SIXTRL_CBUFFER_ARGPTR_DEC void* SIXTRL_RESTRICT obj_to_update,
    NS(cobj_size_type) const obj_size, NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    SIXTRL_ARGPTR_DEC NS(cobj_addr_type)* SIXTRL_RESTRICT save_ptrs
) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_status_type) st_status_type;
    typedef NS(cobj_size_type)   st_size_type;
    typedef NS(cobj_addr_type)   st_addr_type;
    typedef NS(cobj_raw_type)    st_raw_type;

    SIXTRL_STATIC_VAR st_addr_type SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
        ( st_addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;

    st_status_type status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
    NS(cobj_obj_index_const_pointer) index_obj = NS(CObjFlatBuffer_const_index)(
        buffer, pos_in_buffer, slot_size );

    SIXTRL_ASSERT( type_id != (
        NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_ILLEGAL );

    if( (  index_obj != SIXTRL_NULLPTR ) &&
        (  NS(CObjIndex_type_id)( index_obj ) == type_id ) &&
        (  NS(CObjIndex_begin_addr)( index_obj ) != NULL_ADDR ) &&
        (  NS(CObjIndex_size)( index_obj ) >= obj_size ) &&
        ( obj_size > ( st_size_type )0u ) && ( obj_to_update != SIXTRL_NULLPTR ) )
    {
        typedef SIXTRL_CBUFFER_ARGPTR_DEC st_addr_type*        ptr_dest_addr_type;
        typedef SIXTRL_CBUFFER_ARGPTR_DEC  st_raw_type*        ptr_dest_data_t;

        typedef SIXTRL_CBUFFER_DATAPTR_DEC st_addr_type const* ptr_src_addr_t;
        typedef SIXTRL_CBUFFER_DATAPTR_DEC st_raw_type  const* ptr_src_data_t;

        st_addr_type const dest_begin_addr = ( st_addr_type )(
            uintptr_t )obj_to_update;

        ptr_dest_data_t dest_begin = ( ptr_dest_data_t )(
            uintptr_t )dest_begin_addr;

        st_size_type const storage_obj_size =
            NS(CObjFlatBuffer_slot_based_size)( obj_size, slot_size );

        status = ( st_status_type )SIXTRL_STATUS_SUCCESS;

        SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) );
        SIXTRL_ASSERT( NS(CObjIndex_begin_addr)( index_obj ) % slot_size ==
                       ( st_addr_type )0u );

        if( ( num_pointers > ( st_size_type )0u ) &&
            ( save_ptrs != SIXTRL_NULLPTR ) )
        {
            st_size_type ii = ( st_size_type )0u;

            SIXTRL_ASSERT( ( uintptr_t )obj_to_update % slot_size ==
                           ( uintptr_t )0u );

            SIXTRL_ASSERT( offsets   != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( sizes     != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( counts    != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( save_ptrs != SIXTRL_NULLPTR );

            SIXTRL_ASSERT( offsets   != sizes );
            SIXTRL_ASSERT( offsets   != counts );
            SIXTRL_ASSERT( counts    != sizes );

            for( ; ii < num_pointers ; ++ii )
            {
                st_size_type const field_offset = offsets[ ii ];
                st_addr_type const dest_field_addr = dest_begin_addr + field_offset;
                ptr_dest_addr_type ptr_field_addr = ( ptr_dest_addr_type)(
                    uintptr_t )dest_field_addr;

                if( ( ( field_offset % slot_size ) != ( st_size_type )0u ) ||
                    ( ( field_offset + slot_size ) > obj_size ) )
                {
                    status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }

                save_ptrs[ ii ] = *( ptr_field_addr );

                if( ( save_ptrs[ ii ] == NULL_ADDR ) &&
                    ( counts[ ii ] * sizes[ ii ] > ( st_size_type )0u ) )
                {
                    status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        {
            ptr_src_data_t src = ( ptr_src_data_t )( uintptr_t
                )NS(CObjIndex_begin_addr)( index_obj );

            if( storage_obj_size > obj_size )
            {
                SIXTRL_STATIC_VAR st_raw_type const ZBYTE = ( st_raw_type )0u;
                SIXTRACKLIB_SET_VALUES( st_raw_type, dest_begin,
                                        storage_obj_size, ZBYTE );
            }

            status = NS(_CObjFlatBuffer_memcpy_from_dataptr_to_argptr)(
                dest_begin, src, obj_size, slot_size );
        }

        if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
            ( num_pointers > ( st_size_type )0u ) )
        {
            st_addr_type const src_begin_addr =
                    NS(CObjIndex_begin_addr)( index_obj );

            st_size_type const requ_storage_size =
                NS(CObjFlatBuffer_predict_required_num_bytes)(
                    obj_size, num_pointers, sizes, counts, slot_size );

            st_size_type ii = ( st_size_type )0u;

            SIXTRL_ASSERT( requ_storage_size >= storage_obj_size );
            SIXTRL_ASSERT( requ_storage_size % slot_size == ( st_size_type )0u );
            SIXTRL_ASSERT( requ_storage_size >=
                NS(CObjIndex_size)( index_obj ) );
            SIXTRL_ASSERT( save_ptrs != SIXTRL_NULLPTR );

            ( void )requ_storage_size;

            for( ; ii < num_pointers ; ++ii )
            {
                st_size_type const field_offset = offsets[ ii ];
                st_size_type const field_size = NS(CObjFlatBuffer_slot_based_size)(
                    sizes[ ii ] * counts[ ii ], slot_size );

                ptr_src_addr_t ptr_field_src_addr = ( ptr_src_addr_t )(
                    uintptr_t )( src_begin_addr + field_offset );

                ptr_src_data_t ptr_field_src = ( ptr_src_data_t )(
                    uintptr_t )( *ptr_field_src_addr );

                st_addr_type const dest_field_addr = dest_begin_addr + field_offset;
                ptr_dest_addr_type ptr_field_dest_addr = ( ptr_dest_addr_type )(
                    uintptr_t )dest_field_addr;

                ptr_dest_data_t ptr_field_dest = ( ptr_dest_data_t )(
                    uintptr_t )save_ptrs[ ii ];

                *ptr_field_dest_addr = save_ptrs[ ii ];

                SIXTRL_ASSERT( ( field_offset % slot_size ) == ( st_size_type )0u );
                SIXTRL_ASSERT( ( field_offset + slot_size ) <= obj_size );

                if( ( save_ptrs[ ii ] == NULL_ADDR ) ||
                    ( *ptr_field_src_addr == NULL_ADDR ) ||
                    ( field_size == ( st_size_type )0u ) )
                {
                    if( ( save_ptrs[ ii ] != NULL_ADDR ) ||
                        ( *ptr_field_src_addr != NULL_ADDR ) ||
                        ( field_size > ( st_size_type )0u ) )
                    {
                        status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;
                    }
                }

                if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
                {
                    status = NS(_CObjFlatBuffer_memcpy_from_dataptr_to_argptr)(
                        ptr_field_dest, ptr_field_src, field_size, slot_size );
                }

                if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) break;
            }
        }
    }

    return status;
}

/* ************************************************************************* */
/* ******                  Change Layout / Reserve                   ******* */
/* ************************************************************************* */

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_predict_required_num_bytes)(
    NS(cobj_size_type) const obj_handle_size,
    NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;
    st_size_type requ_num_bytes = ( st_size_type )0u;

    if( ( slot_size > ( st_size_type )0u ) &&
        ( obj_handle_size > ( st_size_type )0u ) )
    {
        requ_num_bytes = NS(CObjFlatBuffer_slot_based_size)(
            obj_handle_size, slot_size );

        SIXTRL_ASSERT( requ_num_bytes > ( st_size_type )0u );
        SIXTRL_ASSERT( ( num_pointers == ( st_size_type )0u ) ||
                       ( ( counts != SIXTRL_NULLPTR ) &&
                         ( sizes  != SIXTRL_NULLPTR ) ) );

        if( num_pointers > ( st_size_type )0u )
        {
            for( st_size_type ii = ( st_size_type )0u ;
                 ii < num_pointers ; ++ii )
            {
                requ_num_bytes += NS(CObjFlatBuffer_slot_based_size)(
                    counts[ ii ] * sizes[ ii ], slot_size );
            }
        }

        SIXTRL_ASSERT( requ_num_bytes % slot_size == ( st_size_type )0u );
    }

    return requ_num_bytes;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_predict_required_num_slots)(
    NS(cobj_size_type) const obj_handle_size,
    NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;
    st_size_type requ_num_slots = ( st_size_type )0u;

    if( slot_size > ( st_size_type )0u )
    {
        st_size_type const requ_num_bytes =
            NS(CObjFlatBuffer_predict_required_num_bytes)( obj_handle_size,
                num_pointers, sizes, counts, slot_size );

        requ_num_slots = requ_num_bytes / slot_size;

        if( ( requ_num_slots * slot_size ) < requ_num_bytes )
        {
            ++requ_num_slots;
        }
    }

    return requ_num_slots;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_calc_required_buffer_size)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objs,
    NS(cobj_size_type) const max_num_dataptrs,
    NS(cobj_size_type) const max_num_garbage_ranges,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;

    st_size_type const header_size =
        NS(CObjFlatBuffer_size_header)( buffer, slot_size );

    st_size_type const requ_slots_size = NS(CObjFlatBuffer_calc_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, max_num_slots, slot_size );

    st_size_type const requ_objs_size = NS(CObjFlatBuffer_calc_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, max_num_objs, slot_size );

    st_size_type const requ_ptrs_size = NS(CObjFlatBuffer_calc_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS,
            max_num_dataptrs, slot_size );

    st_size_type const requ_garbage_size = NS(CObjFlatBuffer_calc_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE,
            max_num_garbage_ranges, slot_size );

    return header_size +
        requ_slots_size + requ_objs_size + requ_ptrs_size + requ_garbage_size;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_predict_required_buffer_size)(
    NS(cobj_size_type) const max_num_slots,
    NS(cobj_size_type) const max_num_objects,
    NS(cobj_size_type) const max_num_dataptrs,
    NS(cobj_size_type) const max_num_garbage_ranges,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;

    st_size_type requ_buffer_size = ( st_size_type )0;

    if( slot_size > ( st_size_type )0 )
    {
        requ_buffer_size  = NS(CObjFlatBuffer_header_size)( slot_size );

        requ_buffer_size += NS(CObjFlatBuffer_calc_section_size)(
            SIXTRL_NULLPTR, SIXTRL_CBUFFER_SECTION_ID_SLOTS,
                max_num_slots, slot_size );

        requ_buffer_size += NS(CObjFlatBuffer_calc_section_size)(
            SIXTRL_NULLPTR, SIXTRL_CBUFFER_SECTION_ID_INDICES,
                max_num_objects, slot_size );

        requ_buffer_size += NS(CObjFlatBuffer_calc_section_size)(
            SIXTRL_NULLPTR, SIXTRL_CBUFFER_SECTION_ID_POINTERS,
                max_num_dataptrs, slot_size );

        requ_buffer_size += NS(CObjFlatBuffer_calc_section_size)(
            SIXTRL_NULLPTR, SIXTRL_CBUFFER_SECTION_ID_GARBAGE,
                max_num_garbage_ranges, slot_size );
    }

    return requ_buffer_size;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_min_buffer_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_t;
    return ( slot_size > ( st_size_t )0u )
        ? NS(CObjFlatBuffer_predict_required_buffer_size)( ( st_size_t )0u,
            ( st_size_t )0u, ( st_size_t )0u, ( st_size_t )0u, slot_size )
        : ( st_size_t )SIXTRL_CBUFFER_DEFAULT_MIN_BUFFER_SIZE;
}

SIXTRL_INLINE NS(cobj_size_type) NS(CObjFlatBuffer_header_size)(
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_t;
    SIXTRL_ASSERT( ( st_size_t )SIXTRL_CBUFFER_NUM_HEADER_ENTRIES >
                   ( st_size_t )0u );

    return ( slot_size > ( st_size_t )0u )
        ? ( ( st_size_t )SIXTRL_CBUFFER_NUM_HEADER_ENTRIES ) *
          ( NS(CObjFlatBuffer_slot_based_size)(
                sizeof( NS(cobj_addr_type) ), slot_size ) )
        : ( st_size_t )SIXTRL_CBUFFER_DEFAULT_HEADER_SIZE;
}

SIXTRL_INLINE bool NS(CObjFlatBuffer_has_cbuffer_structure)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const buffer_capacity,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;
    typedef NS(cobj_addr_type) st_addr_type;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC st_addr_type const* addr_pointer;

    SIXTRL_STATIC_VAR st_size_type const ZERO = ( st_size_type )0u;
    SIXTRL_STATIC_VAR st_addr_type const NULL_ADDR =
        ( st_addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;

    bool has_cbuffer_structure = false;
    addr_pointer header = NS(CObjFlatBuffer_ptr_const_header)(
        buffer, slot_size );

    if( ( header != SIXTRL_NULLPTR ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR   ] != NULL_ADDR ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] != ZERO ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ] != ZERO ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] >
          header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ]  ) &&
        ( ( buffer_capacity == ZERO ) ||
          ( ( header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] >=
              NS(CObjFlatBuffer_min_buffer_size)( slot_size ) ) &&
            ( buffer_capacity >=
              header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] ) ) ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_SLOTS     ] != NULL_ADDR ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_SLOTS     ] >=
          ( header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ] +
            header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ] ) ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_INDICES   ] != NULL_ADDR ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_INDICES   ] >=
          header[ SIXTRL_CBUFFER_SECTION_ID_SLOTS     ] ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_POINTERS  ] != NULL_ADDR ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_POINTERS  ] >=
          header[ SIXTRL_CBUFFER_SECTION_ID_INDICES   ] ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_GARBAGE   ] != NULL_ADDR ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_GARBAGE   ] >=
          header[ SIXTRL_CBUFFER_SECTION_ID_POINTERS  ] ) )
    {
        has_cbuffer_structure = true;
    }

    return has_cbuffer_structure;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_init_empty)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size
) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_init_empty_detailed)( buffer, capacity, slot_size,
        ( NS(cobj_size_type) )0u, ( NS(cobj_size_type) )0u,
            ( NS(cobj_size_type) )0u, ( NS(cobj_size_type) )0u,
                SIXTRL_NULLPTR );
}

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_init_empty_detailed)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT b,
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const max_n_slots, NS(cobj_size_type) const max_n_objs,
    NS(cobj_size_type) const max_n_ptrs, NS(cobj_size_type) const max_n_garbage,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size
) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_type;
    NS(cobj_status_type) status = ( NS(cobj_status_type)
        )SIXTRL_STATUS_GENERAL_FAILURE;

    SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type)* header =
        NS(CObjFlatBuffer_ptr_header)( b, slot_size );

    if( ( b != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_type )0u ) &&
        ( ( uintptr_t )b % slot_size == ( uintptr_t )0u ) &&
        ( capacity >= NS(CObjFlatBuffer_min_buffer_size)( slot_size ) ) &&
        ( header != SIXTRL_NULLPTR ) )
    {
        typedef NS(cobj_raw_type) st_raw_type;
        SIXTRL_STATIC_VAR st_raw_type const ZBYTE = ( st_raw_type )0u;

        NS(cobj_addr_type) const base_addr = (
            NS(cobj_addr_type) )( uintptr_t )header;

        st_size_type const header_size =
            NS(CObjFlatBuffer_header_size)( slot_size );

        st_size_type const slots_sec_size = NS(CObjFlatBuffer_calc_section_size)(
            b, SIXTRL_CBUFFER_SECTION_ID_SLOTS, max_n_slots, slot_size );

        st_size_type const objs_sec_size = NS(CObjFlatBuffer_calc_section_size)(
            b, SIXTRL_CBUFFER_SECTION_ID_INDICES, max_n_objs, slot_size );

        st_size_type const ptrs_sec_size = NS(CObjFlatBuffer_calc_section_size)(
            b, SIXTRL_CBUFFER_SECTION_ID_POINTERS, max_n_ptrs, slot_size );

        st_size_type const garbage_sec_size =
            NS(CObjFlatBuffer_calc_section_size)( b,
                SIXTRL_CBUFFER_SECTION_ID_GARBAGE, max_n_garbage, slot_size );

        st_size_type const buffer_size = header_size + slots_sec_size +
            objs_sec_size + ptrs_sec_size + garbage_sec_size;

        NS(cobj_addr_type) sec_begin_addr = base_addr + header_size;

        NS(cobj_raw_pointer) raw_header = ( NS(cobj_raw_pointer) )(
            uintptr_t )base_addr;


        if(  requ_buffer_size != SIXTRL_NULLPTR )
            *requ_buffer_size  = buffer_size;

        if( buffer_size > capacity ) return status;

        SIXTRACKLIB_SET_VALUES( st_raw_type, raw_header, buffer_size, ZBYTE );

        header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ]   = base_addr;
        header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] = buffer_size;
        header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ] = header_size;

        header[ SIXTRL_CBUFFER_SECTION_ID_SLOTS ] = sec_begin_addr;
        sec_begin_addr += slots_sec_size;

        header[ SIXTRL_CBUFFER_SECTION_ID_INDICES ] = sec_begin_addr;
        sec_begin_addr += objs_sec_size;

        header[ SIXTRL_CBUFFER_SECTION_ID_POINTERS ] = sec_begin_addr;
        sec_begin_addr += ptrs_sec_size;

        header[ SIXTRL_CBUFFER_SECTION_ID_GARBAGE  ] = sec_begin_addr;

        status = NS(CObjFlatBuffer_section_init)( b,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, ( st_size_type )0u, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(CObjFlatBuffer_set_section_max_size)( b,
                SIXTRL_CBUFFER_SECTION_ID_SLOTS, slots_sec_size, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(CObjFlatBuffer_section_init)( b,
                SIXTRL_CBUFFER_SECTION_ID_INDICES, ( st_size_type )0u,
                    slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(CObjFlatBuffer_set_section_max_size)( b,
                SIXTRL_CBUFFER_SECTION_ID_INDICES, objs_sec_size, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(CObjFlatBuffer_section_init)( b,
                SIXTRL_CBUFFER_SECTION_ID_POINTERS, ( st_size_type )0u,
                    slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(CObjFlatBuffer_set_section_max_size)( b,
                SIXTRL_CBUFFER_SECTION_ID_POINTERS, ptrs_sec_size, slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(CObjFlatBuffer_section_init)( b,
                SIXTRL_CBUFFER_SECTION_ID_GARBAGE, ( st_size_type )0u,
                    slot_size );

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
            status = NS(CObjFlatBuffer_set_section_max_size)( b,
                SIXTRL_CBUFFER_SECTION_ID_GARBAGE, garbage_sec_size, slot_size );
    }

    return status; }

SIXTRL_INLINE bool NS(CObjFlatBuffer_can_allocate)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT b,
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const max_n_slots, NS(cobj_size_type) const max_n_objs,
    NS(cobj_size_type) const max_n_ptrs, NS(cobj_size_type) const max_n_garbage,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)*
        SIXTRL_RESTRICT requ_buffer_size ) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_type;
    bool can_alloc = false;
    st_size_type calc_buffer_size = ( st_size_type )0u;

    if( ( b != SIXTRL_NULLPTR ) && ( slot_size > ( NS(cobj_size_type) )0u ) &&
        ( ( uintptr_t )b % slot_size == ( uintptr_t )0u ) &&
        ( capacity >= NS(CObjFlatBuffer_min_buffer_size)( slot_size ) ) &&
        ( NS(CObjFlatBuffer_ptr_const_header)( b, slot_size
            ) != SIXTRL_NULLPTR ) )
    {
        st_size_type const header_size =
            NS(CObjFlatBuffer_header_size)( slot_size );

        st_size_type const slots_sec_size = NS(CObjFlatBuffer_calc_section_size)(
            b, SIXTRL_CBUFFER_SECTION_ID_SLOTS, max_n_slots, slot_size );

        st_size_type const objs_sec_size = NS(CObjFlatBuffer_calc_section_size)(
            b, SIXTRL_CBUFFER_SECTION_ID_INDICES, max_n_objs, slot_size );

        st_size_type const ptrs_sec_size = NS(CObjFlatBuffer_calc_section_size)(
            b, SIXTRL_CBUFFER_SECTION_ID_POINTERS, max_n_ptrs, slot_size );

        st_size_type const garbage_sec_size =
            NS(CObjFlatBuffer_calc_section_size)( b,
                SIXTRL_CBUFFER_SECTION_ID_GARBAGE, max_n_garbage, slot_size );

        calc_buffer_size = header_size + slots_sec_size + objs_sec_size +
                           ptrs_sec_size + garbage_sec_size;

        SIXTRL_ASSERT( calc_buffer_size >= NS(CObjFlatBuffer_min_buffer_size)(
            slot_size ) );

        can_alloc = ( calc_buffer_size <= capacity );
    }
    if(  requ_buffer_size != SIXTRL_NULLPTR )
        *requ_buffer_size  = calc_buffer_size;
    return can_alloc; }


SIXTRL_INLINE bool NS(CObjFlatBuffer_can_reallocate)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT b,
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const max_n_slots, NS(cobj_size_type) const max_n_objs,
    NS(cobj_size_type) const max_n_ptrs, NS(cobj_size_type) const max_n_garbage,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_max_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_max_n_objs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_max_n_ptrs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_max_n_garbage
) SIXTRL_NOEXCEPT {
    typedef NS(cobj_size_type) st_size_type;
    bool can_realloc = false;
    st_size_type calc_buffer_size   = ( st_size_type )0u;
    st_size_type calc_max_n_slots   = ( st_size_type )0u;
    st_size_type calc_max_n_objs    = ( st_size_type )0u;
    st_size_type calc_max_n_ptrs    = ( st_size_type )0u;
    st_size_type calc_max_n_garbage = ( st_size_type )0u;

    if( ( b != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_type )0u ) &&
        ( ( uintptr_t )b % slot_size == ( uintptr_t )0u ) &&
        ( capacity >= NS(CObjFlatBuffer_min_buffer_size)( slot_size ) ) &&
        ( NS(CObjFlatBuffer_ptr_const_header)( b, slot_size
            ) != SIXTRL_NULLPTR ) )
    {
        st_size_type slots_sec_size   = ( st_size_type )0u;
        st_size_type objs_sec_size    = ( st_size_type )0u;
        st_size_type ptrs_sec_size    = ( st_size_type )0u;
        st_size_type garbage_sec_size = ( st_size_type )0u;

        st_size_type const header_size =
            NS(CObjFlatBuffer_header_size)( slot_size );

        if( NS(CObjFlatBuffer_has_cbuffer_structure)( b, capacity, slot_size ) )
        {
            calc_max_n_slots = NS(CObjFlatBuffer_num_slots)( b, slot_size );
            calc_max_n_objs = NS(CObjFlatBuffer_num_objects)( b, slot_size );
            calc_max_n_ptrs = NS(CObjFlatBuffer_num_pointers)( b, slot_size );
            calc_max_n_garbage = NS(CObjFlatBuffer_num_garbage_ranges)(
                b, slot_size );
        }

        if( calc_max_n_slots < max_n_slots ) calc_max_n_slots = max_n_slots;
        if( calc_max_n_objs  < max_n_objs  ) calc_max_n_objs  = max_n_objs;
        if( calc_max_n_ptrs  < max_n_ptrs  ) calc_max_n_ptrs  = max_n_ptrs;
        if( calc_max_n_garbage < max_n_garbage )
            calc_max_n_garbage = max_n_garbage;

        slots_sec_size = NS(CObjFlatBuffer_calc_section_size)( b,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, calc_max_n_slots, slot_size );

        objs_sec_size = NS(CObjFlatBuffer_calc_section_size)( b,
            SIXTRL_CBUFFER_SECTION_ID_INDICES, calc_max_n_objs, slot_size );

        ptrs_sec_size = NS(CObjFlatBuffer_calc_section_size)( b,
            SIXTRL_CBUFFER_SECTION_ID_POINTERS, calc_max_n_ptrs, slot_size );

        garbage_sec_size = NS(CObjFlatBuffer_calc_section_size)( b,
            SIXTRL_CBUFFER_SECTION_ID_GARBAGE, calc_max_n_garbage, slot_size );

        calc_buffer_size = header_size + slots_sec_size + objs_sec_size +
            ptrs_sec_size + garbage_sec_size;

        SIXTRL_ASSERT( calc_buffer_size >= NS(CObjFlatBuffer_min_buffer_size)(
            slot_size ) );

        can_realloc = ( calc_buffer_size <= capacity );
    }

    if(  requ_buffer_size != SIXTRL_NULLPTR )
        *requ_buffer_size  = calc_buffer_size;

    if(  requ_max_n_slots != SIXTRL_NULLPTR )
        *requ_max_n_slots  = calc_max_n_slots;

    if(  requ_max_n_objs != SIXTRL_NULLPTR )
        *requ_max_n_objs  = calc_max_n_objs;

    if(  requ_max_n_ptrs != SIXTRL_NULLPTR )
        *requ_max_n_ptrs  = calc_max_n_ptrs;

    if(  requ_max_n_garbage != SIXTRL_NULLPTR )
        *requ_max_n_garbage  = calc_max_n_garbage;

    return can_realloc;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_reallocate)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const requ_max_n_slots,
    NS(cobj_size_type) const requ_max_n_objs,
    NS(cobj_size_type) const requ_max_n_ptrs,
    NS(cobj_size_type) const requ_max_n_garbage,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size
) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_status_type) st_status_type;
    typedef NS(cobj_size_type)   st_size_type;
    typedef NS(cobj_raw_type)    st_raw_type;
    typedef NS(cobj_addr_type)   st_addr_type;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC st_raw_type* raw_pointer;

    st_status_type status = ( st_status_type )SIXTRL_STATUS_GENERAL_FAILURE;

    SIXTRL_ARGPTR_DEC st_size_type calc_buffer_size = ( st_size_type )0;
    SIXTRL_ARGPTR_DEC st_size_type target_n_slots   = ( st_size_type )0;
    SIXTRL_ARGPTR_DEC st_size_type target_n_objs    = ( st_size_type )0;
    SIXTRL_ARGPTR_DEC st_size_type target_n_ptrs    = ( st_size_type )0;
    SIXTRL_ARGPTR_DEC st_size_type target_n_garbage = ( st_size_type )0;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_type )0u ) &&
        ( capacity >= NS(CObjFlatBuffer_min_buffer_size)( slot_size ) ) &&
        ( NS(CObjFlatBuffer_can_reallocate)( buffer, capacity, slot_size,
            requ_max_n_slots, requ_max_n_objs, requ_max_n_ptrs,
                requ_max_n_garbage, &calc_buffer_size, &target_n_slots,
                    &target_n_objs, &target_n_ptrs, &target_n_garbage ) ) ) {
        status  = ( st_status_type )SIXTRL_STATUS_SUCCESS; }

    if( status == ( st_status_type )SIXTRL_STATUS_SUCCESS )
    {
        /* ----------------------------------------------------------------*/
        /* Based on the requ_n_* numbers, calculate the required minimum
         * buffer capacity in pieces to also have the partial results for the
         * new section lenghts available */

        st_size_type const current_buffer_size =
            NS(CObjFlatBuffer_size)( buffer, slot_size );

        st_size_type const header_size = NS(CObjFlatBuffer_size_header)(
            buffer, slot_size );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

        st_size_type const cur_max_n_slots =
            NS(CObjFlatBuffer_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

        st_size_type const cur_max_n_objs =
            NS(CObjFlatBuffer_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );

        st_size_type const cur_max_n_ptrs =
            NS(CObjFlatBuffer_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

        st_size_type const cur_max_n_garbage =
            NS(CObjFlatBuffer_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

        st_size_type const cur_n_slots = NS(CObjFlatBuffer_section_num_entities)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

        st_size_type const cur_n_objs = NS(CObjFlatBuffer_section_num_entities)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );

        st_size_type const cur_n_ptrs = NS(CObjFlatBuffer_section_num_entities)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

        st_size_type const cur_n_garbage =
            NS(CObjFlatBuffer_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

        st_size_type const requ_slots_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS,
                target_n_slots, slot_size );

        st_size_type const requ_objs_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES,
                target_n_objs, slot_size);

        st_size_type const requ_ptrs_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS,
                target_n_ptrs, slot_size);

        st_size_type const requ_garbage_size =
            NS(CObjFlatBuffer_calc_section_size)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_GARBAGE,
                    target_n_garbage, slot_size );

        SIXTRL_ASSERT( current_buffer_size <= capacity );
        calc_buffer_size = header_size + requ_slots_size + requ_objs_size +
                           requ_ptrs_size + requ_garbage_size;

        SIXTRL_ASSERT( calc_buffer_size >= NS(CObjFlatBuffer_min_buffer_size)(
            slot_size ) );

        if(  requ_buffer_size != SIXTRL_NULLPTR )
            *requ_buffer_size = calc_buffer_size;

        if( ( target_n_slots      <= cur_max_n_slots     ) &&
            ( target_n_objs       <= cur_max_n_objs      ) &&
            ( target_n_ptrs       <= cur_max_n_ptrs      ) &&
            ( target_n_garbage    <= cur_max_n_garbage   ) &&
            ( calc_buffer_size    <= current_buffer_size ) &&
            ( current_buffer_size <= capacity ) )
        {
            /* The current layout for the buffer can store the requested
             * configuration (which may be larger than what is requested
             * via the max_n_* numbers due to the currently stored data).
             *
             * NOTE: This method does not shrink sections if
             * they are larger than requested -> this would complicate things
             * a bit, so it's omitted -> implement, if required !
             *
             * For now we are finished here -> success ! */

            SIXTRL_ASSERT( cur_n_slots   <= target_n_slots   );
            SIXTRL_ASSERT( cur_n_objs    <= target_n_objs    );
            SIXTRL_ASSERT( cur_n_ptrs    <= target_n_ptrs    );
            SIXTRL_ASSERT( cur_n_garbage <= target_n_garbage );

            status = ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS;
        }
        else if( ( current_buffer_size <= capacity ) &&
                 ( calc_buffer_size <= capacity ) )
        {
            /* Get the current section sizes and offsets */

            st_size_type const cur_slots_size =
                NS(CObjFlatBuffer_size_slots)( buffer, slot_size );

            st_size_type const cur_objs_size =
                NS(CObjFlatBuffer_size_objects)( buffer, slot_size );

            st_size_type const cur_ptrs_size =
                NS(CObjFlatBuffer_size_pointers)( buffer, slot_size );

            st_size_type const cur_garbage_size =
                NS(CObjFlatBuffer_size_garbage_ranges)( buffer, slot_size );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            st_size_type const cur_slots_off = NS(CObjFlatBuffer_section_offset)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            st_size_type const cur_objs_off = NS(CObjFlatBuffer_section_offset)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );

            st_size_type const cur_ptrs_off = NS(CObjFlatBuffer_section_offset)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

            st_size_type const cur_garbage_off= NS(CObjFlatBuffer_section_offset)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

            /* ------------------------------------------------------------- */
            /* Calculate the new offsets */

            st_size_type const new_slots_offset = header_size;

            st_size_type const new_objs_offset  =
                new_slots_offset + requ_slots_size;

            st_size_type const new_ptrs_offset =
                new_objs_offset + requ_objs_size;

            st_size_type const new_garbage_offset =
                new_ptrs_offset + requ_ptrs_size;

            bool slots_finished   = ( new_slots_offset   == cur_slots_off   );
            bool objs_finished    = ( new_objs_offset    == cur_objs_off    );
            bool ptrs_finished    = ( new_ptrs_offset    == cur_ptrs_off    );
            bool garbage_finished = ( new_garbage_offset == cur_garbage_off );

            SIXTRL_STATIC_VAR NS(cobj_raw_type) SIXTRL_CONSTEXPR_OR_CONST
                ZERO = ( NS(cobj_raw_type) )0;

            SIXTRL_ASSERT( new_slots_offset == cur_slots_off );

            /* ------------------------------------------------------------- */

            if( !garbage_finished )
            {
                if( new_garbage_offset > cur_garbage_off )
                {
                    raw_pointer source = buffer + cur_garbage_off;
                    raw_pointer destination = buffer + new_garbage_offset;
                    st_size_type nn_at_begin = new_garbage_offset - cur_garbage_off;

                    SIXTRACKLIB_MOVE_VALUES( st_raw_type,
                        destination, source, cur_garbage_size );

                    if( nn_at_begin > cur_garbage_size ) {
                        nn_at_begin = cur_garbage_size; }

                    SIXTRACKLIB_SET_VALUES( st_raw_type,
                        source, nn_at_begin, ZERO);

                    if( requ_garbage_size > cur_garbage_size )
                    {
                        st_size_type const nn =
                            requ_garbage_size - cur_garbage_size;

                        SIXTRACKLIB_SET_VALUES( st_raw_type,
                            destination + cur_garbage_size, nn, ZERO );
                    }

                    garbage_finished = true;
                }
                else if( new_garbage_offset >= ( cur_ptrs_off + cur_ptrs_size ) )
                {
                    raw_pointer source =      buffer + cur_garbage_off;
                    raw_pointer destination = buffer + new_garbage_offset;

                    SIXTRACKLIB_MOVE_VALUES( st_raw_type,
                        destination, source, cur_garbage_size );

                    garbage_finished = true;
                }
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( ( garbage_finished ) && ( !ptrs_finished ) )
            {
                if( new_ptrs_offset > cur_ptrs_off )
                {
                    raw_pointer source = buffer + cur_ptrs_off;
                    raw_pointer destination = buffer + new_ptrs_offset;
                    st_size_type nn_at_begin = new_ptrs_offset - cur_ptrs_off;

                    SIXTRACKLIB_MOVE_VALUES(
                        st_raw_type, destination, source, cur_ptrs_size );

                    if( nn_at_begin > cur_ptrs_size )
                        nn_at_begin = cur_ptrs_size;

                    SIXTRACKLIB_SET_VALUES(
                        st_raw_type, source, nn_at_begin, ZERO );

                    if( requ_ptrs_size > cur_ptrs_size )
                    {
                        st_size_type const bytes_to_fill =
                            requ_ptrs_size - cur_ptrs_size;

                        SIXTRACKLIB_SET_VALUES( st_raw_type,
                            destination + cur_ptrs_size, bytes_to_fill, ZERO );
                    }

                    ptrs_finished = true;
                }
                else if( new_ptrs_offset >= ( cur_objs_off + cur_objs_size ) )
                {
                    raw_pointer source = buffer + cur_ptrs_off;
                    raw_pointer destination = buffer + new_ptrs_offset;

                    SIXTRACKLIB_MOVE_VALUES(
                        st_raw_type, destination, source, cur_ptrs_size );

                    ptrs_finished = true;
                }
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( ( garbage_finished ) && ( ptrs_finished ) &&
                ( !objs_finished ) )
            {
                if( new_objs_offset > cur_objs_off )
                {
                    raw_pointer source = buffer + cur_objs_off;
                    raw_pointer destination = buffer + new_objs_offset;
                    st_size_type nn_at_begin = new_objs_offset - cur_objs_off;

                    SIXTRACKLIB_MOVE_VALUES(
                        st_raw_type, destination, source, cur_objs_size );

                    if( nn_at_begin > cur_objs_size )
                        nn_at_begin = cur_objs_size;

                    SIXTRACKLIB_SET_VALUES(
                        st_raw_type, source, nn_at_begin, ZERO);

                    if( requ_objs_size > cur_objs_size )
                    {
                        st_size_type const bytes_to_fill =
                            requ_objs_size - cur_objs_size;

                        SIXTRACKLIB_SET_VALUES( st_raw_type,
                            destination + cur_objs_size, bytes_to_fill, ZERO );
                    }

                    objs_finished = true;
                }
                else if( new_objs_offset >= ( cur_slots_off + cur_slots_size ))
                {
                    raw_pointer source = buffer + cur_objs_off;
                    raw_pointer destination = buffer + new_objs_offset;

                    SIXTRACKLIB_MOVE_VALUES(
                        st_raw_type, destination, source, cur_objs_size );

                    objs_finished = true;
                }
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( ( slots_finished ) && ( ptrs_finished ) &&
                ( objs_finished  ) && ( garbage_finished ) )
            {
                typedef SIXTRL_CBUFFER_DATAPTR_DEC st_addr_type* addr_pointer;

                if( requ_slots_size > cur_slots_size )
                {
                    raw_pointer destination = buffer + new_slots_offset;
                    st_size_type const bytes_to_fill =
                        requ_slots_size - cur_slots_size;

                    SIXTRACKLIB_SET_VALUES( st_raw_type,
                        destination + cur_slots_size, bytes_to_fill, ZERO );
                }

                st_addr_type const begin_addr = (
                    st_addr_type )( uintptr_t )buffer;

                st_addr_type const new_slots_section_begin_addr = ( st_addr_type
                    )( uintptr_t )( begin_addr + new_slots_offset );

                st_addr_type const new_objs_section_begin_addr = ( st_addr_type
                    )( uintptr_t )( begin_addr + new_objs_offset );

                st_addr_type const new_dataptrs_section_begin_addr = (
                    st_addr_type )( uintptr_t )(begin_addr + new_ptrs_offset );

                st_addr_type const new_garbage_section_begin_addr = (
                    st_addr_type )( uintptr_t )(
                        begin_addr + new_garbage_offset );

                addr_pointer ptr_header = NS(CObjFlatBuffer_ptr_header)(
                    buffer, slot_size );

                SIXTRL_ASSERT( ptr_header[ 0 ] ==
                    ( st_addr_type )( uintptr_t )buffer );

                SIXTRL_ASSERT( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_SLOTS ] ==
                    new_slots_section_begin_addr );

                ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] =
                    calc_buffer_size;

                ptr_header[ SIXTRL_CBUFFER_SECTION_ID_SLOTS ] =
                    new_slots_section_begin_addr;

                ptr_header[ SIXTRL_CBUFFER_SECTION_ID_INDICES ] =
                    new_objs_section_begin_addr;

                ptr_header[ SIXTRL_CBUFFER_SECTION_ID_POINTERS ]
                    = new_dataptrs_section_begin_addr;

                ptr_header[ SIXTRL_CBUFFER_SECTION_ID_GARBAGE ]
                    = new_garbage_section_begin_addr;

                status = NS(CObjFlatBuffer_set_section_max_size)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS,
                        requ_slots_size, slot_size );

                status |= NS(CObjFlatBuffer_set_section_num_entities)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, cur_n_slots,
                        slot_size );

                status |= NS(CObjFlatBuffer_set_section_max_size)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES,
                        requ_objs_size, slot_size );

                status |= NS(CObjFlatBuffer_set_section_num_entities)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, cur_n_objs,
                        slot_size );

                status |= NS(CObjFlatBuffer_set_section_max_size)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS,
                        requ_ptrs_size, slot_size );

                status |= NS(CObjFlatBuffer_set_section_num_entities)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, cur_n_ptrs,
                        slot_size );

                status |= NS(CObjFlatBuffer_set_section_max_size)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE,
                        requ_garbage_size, slot_size );

                status |= NS(CObjFlatBuffer_set_section_num_entities)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, cur_n_garbage,
                        slot_size );
            }
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_allocate)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT b,
    NS(cobj_size_type) const capacity, NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const max_n_slots, NS(cobj_size_type) const max_n_objs,
    NS(cobj_size_type) const max_n_ptrs, NS(cobj_size_type) const max_n_garbage,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size
) SIXTRL_NOEXCEPT {
    NS(cobj_status_type) status = (
        NS(cobj_status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    SIXTRL_ARGPTR_DEC NS(cobj_size_type) calc_buffer_size =
        ( NS(cobj_size_type) )0u;

    if( ( b != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_type )0u ) &&
        ( capacity >= NS(CObjFlatBuffer_min_buffer_size)( slot_size ) ) )
    {
        status = ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS;

        if( !NS(CObjFlatBuffer_has_cbuffer_structure)( b, capacity, slot_size ) )
        {
            status = NS(CObjFlatBuffer_init_empty)( b, capacity, slot_size );
        }

        if( ( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS ) &&
            ( !NS(CObjFlatBuffer_can_allocate)( b, capacity, slot_size,
                max_n_slots, max_n_objs, max_n_ptrs, max_n_garbage,
                    &calc_buffer_size ) ) )
        {
            status = ( NS(cobj_status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
        }

        if( status == ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS )
        {
            SIXTRL_ASSERT( capacity >= calc_buffer_size );
            SIXTRL_ASSERT( calc_buffer_size >=
                NS(CObjFlatBuffer_min_buffer_size)( slot_size ) );

            status = NS(CObjFlatBuffer_init_empty_detailed)( b, capacity,
                slot_size, max_n_slots, max_n_objs, max_n_ptrs, max_n_garbage,
                    requ_buffer_size );
        }
        else if( requ_buffer_size != SIXTRL_NULLPTR )
        {
            *requ_buffer_size = calc_buffer_size;
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type) NS(CObjFlatBuffer_clear)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    bool const set_data_to_zero,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;


    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_type )0u ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) )
    {
        st_size_type const num_slots =
            NS(CObjFlatBuffer_num_slots)( buffer, slot_size );

        st_size_type const num_objects =
            NS(CObjFlatBuffer_num_objects)( buffer, slot_size );

        st_size_type const num_pointers =
            NS(CObjFlatBuffer_num_pointers)( buffer, slot_size );

        st_size_type const num_garbage_ranges =
            NS(CObjFlatBuffer_num_garbage_ranges)( buffer, slot_size );

        SIXTRL_ASSERT( NS(CObjFlatBuffer_max_num_slots)(
            buffer, slot_size ) >= num_slots );

        SIXTRL_ASSERT( NS(CObjFlatBuffer_max_num_objects)(
            buffer, slot_size ) >= num_objects );

        SIXTRL_ASSERT( NS(CObjFlatBuffer_max_num_pointers)(
            buffer, slot_size ) >= num_pointers );

        SIXTRL_ASSERT( NS(CObjFlatBuffer_max_num_garbage_ranges)(
            buffer, slot_size ) >= num_garbage_ranges );

        if( set_data_to_zero )
        {
            if( num_slots > ( st_size_type )0u )
            {
                typedef NS(cobj_raw_type) st_raw_type;
                SIXTRL_STATIC_VAR st_raw_type SIXTRL_CONSTEXPR_OR_CONST
                    ZERO = ( st_raw_type )0u;

                NS(cobj_raw_pointer) slots_begin =
                    NS(CObjFlatBuffer_ptr_section_data_begin)(
                        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

                st_size_type const num_bytes_to_clear = num_slots * slot_size;

                SIXTRL_ASSERT( NS(CObjFlatBuffer_section_entity_size)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) ==
                        slot_size );

                SIXTRL_ASSERT(
                NS(CObjFlatBuffer_size_slots)( buffer, slot_size ) ==
                ( num_bytes_to_clear + NS(CObjFlatBuffer_size_section_header)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) ) );

                SIXTRACKLIB_SET_VALUES(
                    st_raw_type, slots_begin, num_bytes_to_clear, ZERO );
            }

            if( num_objects > ( st_size_type )0u )
            {
                NS(cobj_obj_index_pointer) it = NS(CObjFlatBuffer_indices_begin)(
                    buffer, slot_size );

                NS(cobj_obj_index_pointer) end = NS(CObjFlatBuffer_indices_end)(
                    buffer, slot_size );

                for( ; it != end ; ++it ) NS(CObjIndex_preset)( it );
            }

            if( num_pointers > ( st_size_type )0u )
            {
                typedef NS(cobj_addr_type) st_addr_type;
                typedef SIXTRL_CBUFFER_DATAPTR_DEC st_addr_type* addr_pointer;

                SIXTRL_STATIC_VAR st_addr_type SIXTRL_CONSTEXPR_OR_CONST
                    NULL_ADDR = ( st_addr_type )SIXTRL_COBJECTS_NULL_ADDRESS;

                addr_pointer it = ( addr_pointer )( uintptr_t
                    )NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
                        SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

                addr_pointer end = ( addr_pointer )( uintptr_t
                    )NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
                        SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

                for( ; it != end ; ++it ) *it = NULL_ADDR;
            }

            if( num_garbage_ranges > ( st_size_type )0u )
            {
                typedef NS(CObjGarbageRange) _garbage_t;
                typedef SIXTRL_CBUFFER_DATAPTR_DEC _garbage_t* ptr_garbage_t;

                ptr_garbage_t it = ( ptr_garbage_t )( uintptr_t
                    )NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
                        SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

                ptr_garbage_t end = ( ptr_garbage_t )( uintptr_t
                    )NS(CObjFlatBuffer_section_data_end_addr)( buffer,
                        SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

                for( ; it != end ; ++it ) NS(CObjGarbageRange_preset)( it );
            }
        }

        status = NS(CObjFlatBuffer_set_section_num_entities)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, ( st_size_type )0u, slot_size );

        status |= NS(CObjFlatBuffer_set_section_num_entities)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_INDICES, ( st_size_type )0u, slot_size );

        status |= NS(CObjFlatBuffer_set_section_num_entities)(buffer,
            SIXTRL_CBUFFER_SECTION_ID_POINTERS, ( st_size_type )0u, slot_size );

        status |= NS(CObjFlatBuffer_set_section_num_entities)(buffer,
            SIXTRL_CBUFFER_SECTION_ID_GARBAGE, ( st_size_type )0u, slot_size );
    }

    return status;
}

/* ************************************************************************* */
/* ******       Add / ( Remove? ) Objects To The Buffer API          ******* */
/* ************************************************************************* */

SIXTRL_INLINE bool NS(CObjFlatBuffer_can_add_copy_of_object)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const obj_handle_size,
    NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_objs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_ptrs
) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;
    bool can_be_added = false;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_type )0u ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) &&
        ( obj_handle_size > ( st_size_type )0u ) &&
        ( ( num_pointers == ( st_size_type )0u ) ||
          ( ( num_pointers > ( st_size_type )0u ) &&
            ( sizes != SIXTRL_NULLPTR ) && ( counts != SIXTRL_NULLPTR ) &&
            ( sizes != counts ) ) ) )
    {
        st_size_type const cur_num_slots =
            NS(CObjFlatBuffer_num_slots)( buffer, slot_size );

        st_size_type const max_num_slots =
            NS(CObjFlatBuffer_max_num_slots)( buffer, slot_size );

        st_size_type const req_num_slots = cur_num_slots +
            NS(CObjFlatBuffer_predict_required_num_slots)( obj_handle_size,
                num_pointers, sizes, counts, slot_size );

        st_size_type const cur_num_objs =
            NS(CObjFlatBuffer_num_objects)( buffer, slot_size );

        st_size_type const max_num_objs =
            NS(CObjFlatBuffer_max_num_slots)( buffer, slot_size );

        st_size_type const req_num_objs = cur_num_objs + ( st_size_type )1u;

        st_size_type const cur_num_ptrs =
            NS(CObjFlatBuffer_num_pointers)( buffer, slot_size );

        st_size_type const max_num_ptrs =
            NS(CObjFlatBuffer_max_num_pointers)( buffer, slot_size );

        st_size_type const req_num_ptrs = cur_num_ptrs + num_pointers;

        SIXTRL_ASSERT( cur_num_slots <= max_num_slots );
        SIXTRL_ASSERT( cur_num_objs  <= max_num_objs  );
        SIXTRL_ASSERT( cur_num_ptrs  <= max_num_ptrs  );

        SIXTRL_ASSERT(
            NS(CObjFlatBuffer_num_garbage_ranges)( buffer, slot_size ) <=
            NS(CObjFlatBuffer_max_num_garbage_ranges)( buffer, slot_size ) );

        if(  ptr_requ_n_slots != SIXTRL_NULLPTR )
        {
            *ptr_requ_n_slots  = req_num_slots;
        }

        if(  ptr_requ_n_objs != SIXTRL_NULLPTR )
        {
            *ptr_requ_n_objs  = req_num_objs;
        }

        if(  ptr_requ_n_ptrs != SIXTRL_NULLPTR )
        {
            *ptr_requ_n_ptrs  = req_num_ptrs;
        }

        if( requ_buffer_size != SIXTRL_NULLPTR )
        {
            *requ_buffer_size = NS(CObjFlatBuffer_calc_required_buffer_size)(
                buffer, req_num_slots, req_num_objs, req_num_ptrs,
                    NS(CObjFlatBuffer_max_num_garbage_ranges)(
                        buffer, slot_size ), slot_size );
        }

        can_be_added = (
            ( req_num_objs  <= max_num_objs  ) &&
            ( req_num_ptrs  <= max_num_ptrs  ) &&
            ( req_num_slots <= max_num_slots ) );
    }

    return can_be_added;
}

SIXTRL_INLINE bool NS(CObjFlatBuffer_can_add_copy_of_trivial_object)(
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size, NS(cobj_size_type) const obj_handle_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_objs,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT requ_n_ptrs
) SIXTRL_NOEXCEPT { return NS(CObjFlatBuffer_can_add_copy_of_object)( buffer,
    slot_size, obj_handle_size, 0u, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
        requ_buffer_size, requ_n_slots, requ_n_objs, requ_n_ptrs ); }

SIXTRL_INLINE SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)*
NS(CObjFlatBuffer_add_copy_of_object)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_type) const obj_size,
    NS(cobj_obj_id_type) const type_id, NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_add_copy_of_object_detailed)( buffer, slot_size,
        ptr_obj_to_copy, obj_size, obj_size, type_id, num_pointers, offsets,
            sizes, counts, init_space_with_zeros ); }

SIXTRL_INLINE NS(cobj_obj_index_pointer)
NS(CObjFlatBuffer_add_copy_of_object_detailed)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_type) const reserved_obj_size,
    NS(cobj_size_type) const actual_obj_size,
    NS(cobj_obj_id_type) const type_id, NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;
    typedef NS(cobj_addr_type) st_addr_type;
    typedef NS(cobj_obj_id_type) type_id_t;

    NS(cobj_obj_index_pointer) ptr_added_obj = SIXTRL_NULLPTR;

    st_addr_type const begin_addr = ( st_addr_type )( uintptr_t )buffer;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_type )0u ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) &&
        ( ( begin_addr % slot_size ) == ( uintptr_t )0u ) &&
        ( ptr_obj_to_copy != SIXTRL_NULLPTR ) &&
        ( actual_obj_size > ( st_size_type)0u ) &&
        ( reserved_obj_size >= actual_obj_size ) &&
        ( type_id != ( type_id_t )SIXTRL_COBJECTS_TYPE_ID_ILLEGAL ) &&
        ( type_id != ( type_id_t )SIXTRL_COBJECTS_TYPE_ID_UNDEFINED ) &&
        ( ( num_pointers == ( st_size_type )0u ) ||
          ( ( num_pointers > ( st_size_type )0u ) &&
            ( offsets != SIXTRL_NULLPTR ) && ( sizes != SIXTRL_NULLPTR ) &&
            ( counts  != SIXTRL_NULLPTR ) && ( sizes != counts  ) &&
            ( counts  != offsets        ) && ( sizes != offsets ) ) ) )
    {
        st_size_type const cur_num_slots =
            NS(CObjFlatBuffer_num_slots)( buffer, slot_size );

        st_size_type const additional_num_slots =
            NS(CObjFlatBuffer_predict_required_num_slots)(
                reserved_obj_size, num_pointers, sizes, counts, slot_size );

        st_size_type const requ_num_slots = cur_num_slots + additional_num_slots;

        st_size_type const max_num_slots =
            NS(CObjFlatBuffer_max_num_slots)( buffer, slot_size );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        st_size_type const cur_num_objs =
            NS(CObjFlatBuffer_num_objects)( buffer, slot_size );

        st_size_type const requ_num_objs = cur_num_objs + ( st_size_type )1u;

        st_size_type const max_num_objs =
            NS(CObjFlatBuffer_max_num_objects)( buffer, slot_size );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        st_size_type const cur_num_ptrs =
            NS(CObjFlatBuffer_num_pointers)( buffer, slot_size );

        st_size_type const requ_num_ptrs = cur_num_ptrs + num_pointers;

        st_size_type const max_num_ptrs =
            NS(CObjFlatBuffer_max_num_pointers)( buffer, slot_size );

        NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_ASSERT( cur_num_slots <= max_num_slots );
        SIXTRL_ASSERT( cur_num_objs  <= max_num_objs  );
        SIXTRL_ASSERT( cur_num_ptrs  <= max_num_ptrs  );
        SIXTRL_ASSERT( NS(CObjFlatBuffer_slot_based_size)(
            reserved_obj_size, slot_size ) >= reserved_obj_size );
        SIXTRL_ASSERT( NS(CObjFlatBuffer_slot_based_size)(
            actual_obj_size, slot_size ) >= actual_obj_size );

        if( ( requ_num_slots <= max_num_slots ) &&
            ( requ_num_objs  <= max_num_objs  ) &&
            ( requ_num_ptrs  <= max_num_ptrs  ) )
        {
            st_size_type const predicted_stored_bytes_in_slots =
                additional_num_slots * slot_size;

            SIXTRL_ASSERT( NS(CObjFlatBuffer_calc_required_buffer_size)(
                    buffer, requ_num_slots, requ_num_objs, requ_num_ptrs,
                        NS(CObjFlatBuffer_max_num_garbage_ranges)(
                            buffer, slot_size ), slot_size ) <=
                NS(CObjFlatBuffer_size)( buffer, slot_size ) );

            status = NS(_CObjFlatBuffer_add_copy_of_object_obj_handle_part)(
                buffer, slot_size, ptr_obj_to_copy, actual_obj_size,
                    predicted_stored_bytes_in_slots,
                        ( init_space_with_zeros ) ||
                        ( reserved_obj_size > actual_obj_size ) );

            if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
                ( num_pointers > ( st_size_type )0u ) )
            {
                status = NS(_CObjFlatBuffer_add_copy_of_object_ptrs_part)(
                    buffer, slot_size, ptr_obj_to_copy, reserved_obj_size,
                        num_pointers, offsets, sizes, counts,
                            init_space_with_zeros );
            }

            if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
            {
                NS(cobj_obj_index_pointer) ptr_temp_index =
                    NS(_CObjFlatBuffer_add_copy_of_object_index_part)( buffer,
                        slot_size, type_id, predicted_stored_bytes_in_slots,
                            init_space_with_zeros );

                if( ( ptr_temp_index != SIXTRL_NULLPTR ) &&
                    ( SIXTRL_STATUS_SUCCESS ==
                      NS(_CObjFlatBuffer_add_copy_of_object_update_buffer_params)(
                            buffer, slot_size, requ_num_slots, requ_num_objs,
                                requ_num_ptrs ) ) )
                {
                    ptr_added_obj = ptr_temp_index;
                }
            }
        }
    }

    return ptr_added_obj;
}

SIXTRL_INLINE NS(cobj_obj_index_pointer)
NS(CObjFlatBuffer_add_copy_of_trivial_object)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_type) const obj_size, NS(cobj_obj_id_type) const type_id,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_add_copy_of_object)( buffer, slot_size,
        ptr_obj_to_copy, obj_size, type_id, 0u, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
            SIXTRL_NULLPTR, init_space_with_zeros ); }

/* ------------------------------------------------------------------------- */
/* Helper functions implementation for adding a copy of an object to buffer  */
/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_status_type)
NS(_CObjFlatBuffer_memcpy_from_argptr_to_dataptr)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT destination,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT source,
    NS(cobj_size_type) const num_bytes_to_copy, NS(cobj_size_type) const slot_size
) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( destination != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_type )0u ) &&
        ( ( uintptr_t )destination % slot_size == ( uintptr_t )0u ) &&
        ( source != SIXTRL_NULLPTR ) )
    {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;

        if( num_bytes_to_copy > ( st_size_type )0u )
        {
            #if !defined( _GPUCODE )
                #if defined( _cplusplus )
                typedef NS(cobj_raw_type) st_raw_type;
                typedef SIXTRL_CBUFFER_ARGPTR_DEC st_raw_type const* ptr_raw_src_t;

                ptr_raw_src_t src_begin = reinterpret_cast< ptr_raw_src_t >(
                    reinterpret_cast< uintptr_t >( source ) );
                ptr_raw_src_t src_end = src_begin;
                std::advance(  src_end, num_bytes_to_copy );
                std::copy( src_begin, src_end, destination );

                #else /* C++ */
                memcpy( destination, source, num_bytes_to_copy );

                #endif /* C++ */

            #else /* defined( _GPUCODE ) */
            typedef NS(cobj_raw_type) st_raw_type;
            typedef SIXTRL_CBUFFER_ARGPTR_DEC st_raw_type const* ptr_raw_src_t;
            typedef SIXTRL_CBUFFER_DATAPTR_DEC st_raw_type*      ptr_raw_dest_t;

            ptr_raw_dest_t dest_it = destination;
            ptr_raw_src_t  src_it  = ( ptr_raw_src_t )( uintptr_t )source;
            ptr_raw_src_t  src_end = src_it + num_bytes_to_copy;

            for( ; src_it != src_end ; ++src_it, ++dest_it )
            {
                *dest_it = *src_it;
            }

            #endif /* _GPUCODE ) */
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type)
NS(_CObjFlatBuffer_memcpy_from_dataptr_to_argptr)(
    SIXTRL_CBUFFER_ARGPTR_DEC void* SIXTRL_RESTRICT destination,
    NS(cobj_raw_const_pointer) SIXTRL_RESTRICT source,
    NS(cobj_size_type) const num_bytes_to_copy,
    NS(cobj_size_type) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( destination != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_type )0u ) &&
        ( source != SIXTRL_NULLPTR ) &&
        ( ( uintptr_t )source % slot_size == ( uintptr_t )0u ) )
    {
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;

        if( num_bytes_to_copy > ( st_size_type )0u )
        {
            #if !defined( _GPUCODE )
                #if defined( _cplusplus )
                typedef NS(cobj_raw_type) st_raw_type;
                typedef SIXTRL_CBUFFER_ARGPTR_DEC st_raw_type* ptr_raw_dest_t;
                typedef SIXTRL_CBUFFER_DATAPTR_DEC st_raw_type const* ptr_raw_src_t;

                ptr_raw_dest_t dest_begin = reinterpret_cast< ptr_raw_dest_t
                    >( reinterpret_cast< uintptr_t >( destination ) );

                ptr_raw_src_t src_begin = reinterpret_cast< ptr_raw_src_t >(
                    reinterpret_cast< uintptr_t >( source ) );

                ptr_raw_src_t src_end = src_begin;
                std::advance(  src_end, num_bytes_to_copy );
                std::copy( src_begin, src_end, dest_begin );

                #else /* C++ */
                memcpy( destination, source, num_bytes_to_copy );

                #endif /* C++ */

            #else /* defined( _GPUCODE ) */
            typedef NS(cobj_raw_type) st_raw_type;
            typedef SIXTRL_CBUFFER_DATAPTR_DEC st_raw_type const* ptr_raw_src_t;
            typedef SIXTRL_CBUFFER_ARGPTR_DEC st_raw_type* ptr_raw_dest_t;

            ptr_raw_dest_t dest_it =
                ( ptr_raw_dest_t )( uintptr_t )destination;

            ptr_raw_src_t src_it  = source;
            ptr_raw_src_t src_end = src_it + num_bytes_to_copy;

            for( ; src_it != src_end ; ++src_it, ++dest_it )
            {
                *dest_it = *src_it;
            }

            #endif /* _GPUCODE ) */
        }
    }

    return status;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(cobj_status_type)
NS(_CObjFlatBuffer_add_copy_of_object_obj_handle_part)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_type) const obj_size,
    NS(cobj_size_type) const predicted_stored_bytes_in_slots,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type)     st_size_type;
    typedef NS(cobj_addr_type)  st_addr_type;
    typedef NS(cobj_raw_type)      st_raw_type;
    typedef SIXTRL_CBUFFER_ARGPTR_DEC    st_raw_type const* ptr_obj_src_t;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC   st_raw_type*       ptr_obj_dest_t;

    SIXTRL_STATIC_VAR st_raw_type SIXTRL_CONSTEXPR_OR_CONST ZBYTE = ( st_raw_type )0u;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_type )0u ) &&
        ( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) &&
        ( ptr_obj_to_copy != SIXTRL_NULLPTR ) &&
        ( obj_size > ( st_size_type )0u ) )
    {
        /* End of current slots data -> begin of stored obj!! */
        st_addr_type const obj_addr = NS(CObjFlatBuffer_section_data_end_addr)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

        ptr_obj_dest_t dest = ( ptr_obj_dest_t )( uintptr_t )obj_addr;
        ptr_obj_src_t  src  = ( ptr_obj_src_t )( uintptr_t )ptr_obj_to_copy;

        /* Perform some consistency checks to ensure that we will
         * not overwrite the boundaries between the sections ->
         * there should be no problems, so every violation here would
         * be pretty exceptional */

        SIXTRL_ASSERT( obj_addr != ( st_addr_type )SIXTRL_COBJECTS_NULL_ADDRESS );

        SIXTRL_ASSERT( NS(CObjFlatBuffer_section_end_addr)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) >=
                ( obj_addr + predicted_stored_bytes_in_slots ) );

        SIXTRL_ASSERT( predicted_stored_bytes_in_slots >= obj_size );
        SIXTRL_ASSERT( predicted_stored_bytes_in_slots >=
            NS(CObjFlatBuffer_slot_based_size)( obj_size, slot_size ) );

        if( init_space_with_zeros )
        {
            SIXTRACKLIB_SET_VALUES(
                st_raw_type, dest, predicted_stored_bytes_in_slots, ZBYTE );
        }

        /* Copy the obj handle to the begin of the slots section */

        status = NS(_CObjFlatBuffer_memcpy_from_argptr_to_dataptr)(
            dest, src, obj_size, slot_size );
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type)
NS(_CObjFlatBuffer_add_copy_of_object_ptr_field_part)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_type) const obj_size,
    SIXTRL_CBUFFER_DATAPTR_DEC NS(cobj_addr_type)* ptr_to_pointer_in_section,
    NS(cobj_addr_type) const stored_obj_begin_addr,
    NS(cobj_size_type) const field_offset_from_stored_obj_begin,
    NS(cobj_addr_type) const storage_field_data_begin_addr,
    NS(cobj_size_type) const storage_field_data_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type)                         st_size_type;
    typedef NS(cobj_addr_type)                      st_addr_type;
    typedef NS(cobj_raw_type)                          st_raw_type;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC st_addr_type*      ptr_dest_addr_type;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC st_raw_type*       ptr_dest_data_t;
    typedef SIXTRL_CBUFFER_ARGPTR_DEC st_addr_type const* ptr_target_addr_t;
    typedef SIXTRL_CBUFFER_ARGPTR_DEC st_raw_type  const* ptr_source_data_t;

    SIXTRL_STATIC_VAR st_addr_type SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR = ( st_addr_type
        )SIXTRL_COBJECTS_NULL_ADDRESS;

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( slot_size > ( st_size_type )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );
    SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) );
    SIXTRL_ASSERT( ptr_obj_to_copy != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( obj_size >= slot_size );
    SIXTRL_ASSERT( storage_field_data_size % slot_size == ( st_size_type )0u );
    SIXTRL_ASSERT( stored_obj_begin_addr != NULL_ADDR );
    SIXTRL_ASSERT( stored_obj_begin_addr % slot_size == ( st_addr_type )0u );

    ( void )buffer;
    ( void )obj_size;

    /* We are not checking the field_offset_from_stored_obj_begin and assume
     * it's legal and has been checked by the calling function ->
     * see discussion in NS(_CObjFlatBuffer_add_copy_of_object_ptrs_part) on
     * which constraints to this parameter! */

    if( ( ptr_to_pointer_in_section != SIXTRL_NULLPTR ) &&
        ( storage_field_data_begin_addr % slot_size == ( st_addr_type )0u ) )
    {
        st_addr_type const pointer_target_in_obj_addr =
            stored_obj_begin_addr + field_offset_from_stored_obj_begin;

        ptr_dest_addr_type ptr_pointer_target_in_obj = ( ptr_dest_addr_type
            )( uintptr_t )pointer_target_in_obj_addr;

        st_addr_type const orig_obj_begin_addr =
            ( st_addr_type )( uintptr_t )ptr_obj_to_copy;

        st_addr_type const orig_pointer_target_in_obj_addr =
            orig_obj_begin_addr + field_offset_from_stored_obj_begin;

        ptr_target_addr_t ptr_target_addr =
            ( ptr_target_addr_t )( uintptr_t )orig_pointer_target_in_obj_addr;

        SIXTRL_ASSERT( pointer_target_in_obj_addr % slot_size ==
            ( st_addr_type )0u );

        status = ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS;

        if( ( *ptr_target_addr != NULL_ADDR ) &&
            ( storage_field_data_size > ( st_size_type )0u ) )
        {
            ptr_source_data_t field_data_src = ( ptr_source_data_t )(
                uintptr_t )( *ptr_target_addr );

            ptr_dest_data_t field_data_dest = ( ptr_dest_data_t )(
                uintptr_t )storage_field_data_begin_addr;

            status = NS(_CObjFlatBuffer_memcpy_from_argptr_to_dataptr)(
                field_data_dest, field_data_src, storage_field_data_size,
                    slot_size );
        }
        /* else: *ptr_target_addr == NULL_ADDR -> the slots in the
         *        field_Data_store have been initialized according to
         *        the users wishes during storing the slots, we just
         *        have to assign the address to the target pointer
         *
         * else: *ptr_target_addr != NULL_ADDR && storage_field_data_size == 0
         *       Also nothing to do, the pointer points somewhere else
         *       and is not subject to the cbuffer storage mechanism. Users
         *       who submit sizes * counts == 0 values hopefully know what
         *       they are doing :-) */

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        {
            *ptr_pointer_target_in_obj = storage_field_data_begin_addr;
            *ptr_to_pointer_in_section = pointer_target_in_obj_addr;
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_type)
NS(_CObjFlatBuffer_add_copy_of_object_ptrs_part)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_type) const obj_size,
    NS(cobj_size_type) const num_pointers,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type) const* SIXTRL_RESTRICT counts,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type)                         st_size_type;
    typedef NS(cobj_addr_type)                      st_addr_type;
    typedef NS(cobj_raw_type)                          st_raw_type;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC st_addr_type*      addr_pointer;

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    st_size_type const storage_obj_size = NS(CObjFlatBuffer_slot_based_size)(
        obj_size, slot_size );

    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( slot_size > ( st_size_type )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );
    SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) );
    SIXTRL_ASSERT( storage_obj_size % slot_size == ( st_size_type )0u );
    SIXTRL_ASSERT( ( num_pointers == ( st_size_type )0u ) ||
        ( storage_obj_size >= slot_size ) );

    SIXTRL_ASSERT( ( num_pointers == ( st_size_type )0u ) ||
        ( ( offsets != SIXTRL_NULLPTR ) && ( counts != SIXTRL_NULLPTR ) &&
          ( offsets != counts ) && ( sizes != SIXTRL_NULLPTR ) &&
          ( offsets != sizes  ) && ( sizes != counts ) ) );

    if( ( num_pointers > ( st_size_type )0u ) &&
        ( ptr_obj_to_copy != SIXTRL_NULLPTR ) )
    {
        /* The object handle would have been added to at the end of the
         * current slots data section -> use this address as the minimum
         * address which a pointer can have */
        st_addr_type const obj_handle_addr =
            NS(CObjFlatBuffer_section_data_end_addr)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

        /* NOTE: At the moment, we enforce that the targets of the pointers
         *       have to be located in the object handle itself; this is
         *       sensible but rules out things like chained pointers, etc.
         *
         *       two legal cases:
         *       - if obj_size is evenly divisble by the slot_size and at least
         *         slot_size bytes long, the last dataptr fully within
         *         obj_handle is located ( obj_size - slot_size ) bytes from
         *         the obj_handle begin
         *
         *       - if obj_size is not divisble without remainder by slot_size
         *         but is larger than slot_size, then the last dataptr fully
         *         within the obj_handle could be located
         *         slot_size * ( ( obj_size / slot_size ) - 1 ) bytes from
         *         the beginning. The -1 requires the obj_size > slot_size
         *         condition.
         *
         * If a more general cases are intended to be allowed, change the
         * calculation of the limit below and DO NOT CHANGE THE check against
         * this constraint below at [1]!!!!
         *
         * WARNING: Even if the conditions are relaxed to allow pointer
         *          targets outside of the obj_handle, the offsets always have
         *          to be divisble without remainder by the slot size!
         */

        st_size_type const max_allowed_offset = ( storage_obj_size == obj_size )
            ? ( storage_obj_size - slot_size )
            : ( ( obj_size > slot_size )
                    ? slot_size * ( ( obj_size / slot_size ) - ( st_size_type )1 )
                    : ( st_size_type )0u );

        /* The end of the obj handle is also the begin of the area where
         * the arrays for the fields of the object are stored */
        st_addr_type storage_fields_data_addr = obj_handle_addr + storage_obj_size;

        /* The number of pointers to be stored need the following number of
         * bytes on the buffer */
        st_size_type const storage_ptrs_size = NS(CObjFlatBuffer_slot_based_size)(
                sizeof( addr_pointer ) * num_pointers, slot_size );

        /* The end of the current pointers data section is the begin address
         * for the data - pointers of this element: */
        st_addr_type ptrs_begin_addr = NS(CObjFlatBuffer_section_data_end_addr)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

        addr_pointer out_it  = ( addr_pointer )( uintptr_t )ptrs_begin_addr;

        st_size_type ii = ( st_size_type )0u;

        SIXTRL_ASSERT( ptrs_begin_addr % slot_size == ( st_addr_type )0u );
        SIXTRL_ASSERT( NS(CObjFlatBuffer_section_end_addr)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size ) >=
                ( ptrs_begin_addr + storage_ptrs_size ) );

        SIXTRL_ASSERT( NS(CObjFlatBuffer_section_end_addr)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) >=
                storage_fields_data_addr );

        if( init_space_with_zeros )
        {
            SIXTRL_STATIC_VAR st_raw_type SIXTRL_CONSTEXPR_OR_CONST
                ZBYTE = ( st_raw_type )0u;

            NS(cobj_raw_pointer) dest = ( NS(cobj_raw_pointer) )(
                uintptr_t )ptrs_begin_addr;

            SIXTRACKLIB_SET_VALUES( st_raw_type, dest, storage_ptrs_size, ZBYTE );
        }

        for( ; ii < num_pointers ; ++ii, ++out_it )
        {
            status = ( NS(cobj_status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

            /* [1] See above for the calculation of max_allowed_offset
             *     from the obj_size; change this calculation above and
             *     DO NOT CHANGE this check here if you want to change the
             *     behaviour! */

            if( offsets[ ii ] <= max_allowed_offset )
            {
                /* NOTE: field_size == 0 is, on purpose, a valid result here */
                st_size_type const field_size = NS(CObjFlatBuffer_slot_based_size)(
                    sizes[ ii ] * counts[ ii ], slot_size );

                status = NS(_CObjFlatBuffer_add_copy_of_object_ptr_field_part)(
                    buffer, slot_size, ptr_obj_to_copy, obj_size,
                        out_it, obj_handle_addr, offsets[ ii ],
                            storage_fields_data_addr, field_size );

                storage_fields_data_addr += field_size;
            }

            /* One final check to ensure that the field data does not
             * run past the section limit! */

            SIXTRL_ASSERT( ( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) ||
                ( NS(CObjFlatBuffer_section_end_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) >=
                        storage_fields_data_addr ) );

            if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) break;
        }
    }
    else if( num_pointers == ( st_size_type )0u )
    {
        status = ( NS(cobj_status_type) )SIXTRL_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(cobj_obj_index_pointer)
NS(_CObjFlatBuffer_add_copy_of_object_index_part)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(cobj_obj_id_type) const type_id,
    NS(cobj_size_type) const num_bytes_stored_in_slots,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;
    typedef NS(cobj_addr_type) st_addr_type;
    typedef NS(cobj_raw_type) st_raw_type;
    typedef SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* ptr_index_t;
    typedef SIXTRL_CBUFFER_DATAPTR_DEC st_raw_type* raw_pointer;

    ptr_index_t ptr_stored_index = SIXTRL_NULLPTR;

    st_size_type const storage_index_size = NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(CObjIndex) ), slot_size );

    st_addr_type const stored_obj_begin_addr =
        NS(CObjFlatBuffer_section_data_end_addr)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( slot_size > ( st_size_type )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );
    SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) );
    SIXTRL_ASSERT( num_bytes_stored_in_slots >= slot_size );
    SIXTRL_ASSERT( num_bytes_stored_in_slots % slot_size == ( st_size_type )0u );

    SIXTRL_ASSERT( stored_obj_begin_addr % slot_size == ( st_addr_type )0u );
    SIXTRL_ASSERT( stored_obj_begin_addr !=
        ( st_addr_type )SIXTRL_COBJECTS_NULL_ADDRESS );

    /* Check that the stored obj plus the amount of data stored in slots
     * still fits into the slots section */
    SIXTRL_ASSERT( NS(CObjFlatBuffer_section_end_addr)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) >= (
            ( stored_obj_begin_addr + num_bytes_stored_in_slots ) ) );

    if( type_id != ( NS(cobj_obj_id_type) )SIXTRL_COBJECTS_TYPE_ID_ILLEGAL )
    {
        st_addr_type const index_begin_addr =
            NS(CObjFlatBuffer_section_data_end_addr)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );

        SIXTRL_ASSERT( index_begin_addr !=
            ( st_addr_type )SIXTRL_COBJECTS_NULL_ADDRESS );
        SIXTRL_ASSERT( index_begin_addr % slot_size == ( st_addr_type )0u );

        /* Verify that we have enough space in the indices section to store one
        * more index object */
        SIXTRL_ASSERT( NS(CObjFlatBuffer_section_end_addr)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size ) >=
                ( index_begin_addr + storage_index_size ) );

        if( init_space_with_zeros )
        {
            SIXTRL_STATIC_VAR st_raw_type SIXTRL_CONSTEXPR_OR_CONST
                ZBYTE = ( st_raw_type )0u;

            raw_pointer dest = ( raw_pointer )( uintptr_t )index_begin_addr;
            SIXTRACKLIB_SET_VALUES( st_raw_type, dest, storage_index_size, ZBYTE );
        }

        ptr_stored_index = ( ptr_index_t )( uintptr_t )index_begin_addr;

        NS(CObjIndex_preset)( ptr_stored_index );
        NS(CObjIndex_set_type_id)( ptr_stored_index, type_id );
        NS(CObjIndex_set_begin_addr)( ptr_stored_index, stored_obj_begin_addr);
        NS(CObjIndex_set_size)( ptr_stored_index, num_bytes_stored_in_slots );
    }

    return ptr_stored_index;
}

SIXTRL_INLINE NS(cobj_status_type)
NS(_CObjFlatBuffer_add_copy_of_object_update_buffer_params)(
    NS(cobj_raw_pointer) SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const slot_size,
    NS(cobj_size_type) const requ_num_slots,
    NS(cobj_size_type) const requ_num_objects,
    NS(cobj_size_type) const requ_num_pointers ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_type) st_size_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( st_size_type )0u ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) &&
        ( NS(CObjFlatBuffer_max_num_slots)( buffer, slot_size ) >=
          requ_num_slots ) &&
        ( NS(CObjFlatBuffer_max_num_objects)( buffer, slot_size ) >=
          requ_num_objects ) &&
        ( NS(CObjFlatBuffer_max_num_pointers)( buffer, slot_size ) >=
          requ_num_pointers ) )
    {
        st_size_type const cur_num_slots =
            NS(CObjFlatBuffer_num_slots)( buffer, slot_size );

        st_size_type const cur_num_objs =
            NS(CObjFlatBuffer_num_objects)( buffer, slot_size );

        st_size_type const cur_num_ptrs =
            NS(CObjFlatBuffer_num_pointers)( buffer, slot_size );

        status = NS(CObjFlatBuffer_set_section_num_entities)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, requ_num_slots, slot_size );

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        {
            status = NS(CObjFlatBuffer_set_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_INDICES, requ_num_objects,
                    slot_size );
        }

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        {
            status = NS(CObjFlatBuffer_set_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_POINTERS, requ_num_pointers,
                    slot_size );
        }

        if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        {
            /* try to roll-back in case of error */

            NS(CObjFlatBuffer_set_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_SLOTS, cur_num_slots, slot_size );

            NS(CObjFlatBuffer_set_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_INDICES, cur_num_objs, slot_size );

            NS(CObjFlatBuffer_set_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_SLOTS, cur_num_ptrs, slot_size );
        }
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( _cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( _cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_COBJECTS_FLAT_BUFFER_C99_H__ */
