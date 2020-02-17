#ifndef SIXTRACKLIB_COMMON_COBJECTS_FLAT_BUFFER_C99_H__
#define SIXTRACKLIB_COMMON_COBJECTS_FLAT_BUFFER_C99_H__

#if !defined(  SIXTRL_NO_SYSTEM_INCLUDES )
    #if !defined( __cplusplus )
        #include <stdbool.h>
        #include <stddef.h>
        #include <stdlib.h>
        #include <limits.h>
    #else
        #include <cstddef>
        #include <cstdlib>
    #endif /* C++ */
#endif /* !defined(  SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/buffer_object_defines.h"
#endif /* SIXTRL_NO_INCLUDES */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* *******               Minimal Flat Buffer Interface              ******** */
/* ************************************************************************* */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_slot_based_size)(
    NS(cobj_size_t) const in_length,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t) const*
NS(CObjFlatBuffer_ptr_const_header)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t)*
NS(CObjFlatBuffer_ptr_header)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_section_entity_size)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const header_section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t)
NS(CObjFlatBuffer_size_section_header)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_size_header)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_size)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_section_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(ptr_const_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_const_section_begin)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const header_section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(ptr_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_section_begin)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const header_section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_is_section_header_consistent)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_section_max_size)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t)
NS(CObjFlatBuffer_section_num_entities)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_calc_section_size)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id, NS(cobj_size_t) const num_entities,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_section_size)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t)
NS(CObjFlatBuffer_section_max_num_entities)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_section_offset)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(CObjFlatBuffer_set_section_num_entities)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const num_entities,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(CObjFlatBuffer_set_section_max_size)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const max_section_size,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(CObjFlatBuffer_section_init)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const num_elements_in_section,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_section_end_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(ptr_const_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_const_section_end)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const header_section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(ptr_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_section_end)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const header_section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_section_data_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(ptr_const_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_const_section_data_begin)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const header_section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(ptr_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_section_data_begin)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const header_section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_section_data_end_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(ptr_const_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_const_section_data_end)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const header_section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(ptr_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_section_data_end)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const header_section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_num_slots)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_num_indices)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_num_pointers)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_num_garbage_ranges)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_max_num_slots)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_max_num_indices)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_max_num_pointers)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t)
NS(CObjFlatBuffer_max_num_garbage_ranges)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_size_slots)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_size_indices)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_size_pointers)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_size_garbage_ranges)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_max_size_slots)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_max_size_indices)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_max_size_pointers)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t)
NS(CObjFlatBuffer_max_size_garbage_ranges)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t) NS(CObjFlatBuffer_slots_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_indices_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_pointers_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_garbage_ranges_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* ========================================================================= */

struct NS(CObjIndex);

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC struct NS(CObjIndex) const*
NS(CObjFlatBuffer_const_index)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC struct NS(CObjIndex)*
NS(CObjFlatBuffer_index)( NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC struct NS(CObjIndex) const*
NS(CObjFlatBuffer_const_indices_begin)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC struct NS(CObjIndex) const*
NS(CObjFlatBuffer_const_indices_end)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT end,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC struct NS(CObjIndex)*
NS(CObjFlatBuffer_indices_begin)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC struct NS(CObjIndex)*
NS(CObjFlatBuffer_indices_end)( NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_num_objects)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_max_num_objects)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_size_objects)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t) NS(CObjFlatBuffer_max_size_objects)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_objects_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_objects_end_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_objects_data_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_objects_data_end_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_index_begin_addr_by_pos_in_buffer_filter_by_type_info)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_type_id_t) const required_type_id,
    NS(cobj_size_t) const min_size,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* ************************************************************************* */
/* ******                          Remapping                         ******* */
/* ************************************************************************* */

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_stored_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_address_t)
NS(CObjFlatBuffer_buffer_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_needs_remapping)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t) NS(CObjFlatBuffer_base_addr_offset)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_diff_t)*
        SIXTRL_RESTRICT ptr_to_addr_offset,
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t) NS(CObjFlatBuffer_remap_header)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_diff_t)
        const* SIXTRL_RESTRICT offsets,
    NS(cobj_size_t) const slot_size )  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t) NS(CObjFlatBuffer_remap_section_slots)(
    NS(ptr_raw_buffer_data_t)  SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_diff_t) const*
        SIXTRL_RESTRICT offsets,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(CObjFlatBuffer_remap_section_indices)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_diff_t) const*
        SIXTRL_RESTRICT offsets,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(CObjFlatBuffer_remap_section_dataptrs)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_diff_t) const*
        SIXTRL_RESTRICT offsets,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(CObjFlatBuffer_remap_section_garbage)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_diff_t) const*
        SIXTRL_RESTRICT offsets,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t) NS(CObjFlatBuffer_remap)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size );

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t) NS(CObjFlatBuffer_apply_addr_offset)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_address_diff_t) const addr_offset,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* ************************************************************************* */
/* ******                  Load / Store API support                  ******* */
/* ************************************************************************* */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(CObjFlatBuffer_store_obj_same_layout_parameters_from_argptr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer, NS(cobj_size_t) const slot_size,
    NS(cobj_type_id_t) const type_id,
    SIXTRL_BUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT obj_to_store,
    NS(cobj_size_t) const obj_size, NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT offsets,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_t)* SIXTRL_RESTRICT save_ptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer, NS(cobj_size_t) const slot_size,
    NS(cobj_type_id_t) const type_id,
    SIXTRL_BUFFER_ARGPTR_DEC void* SIXTRL_RESTRICT obj_to_store,
    NS(cobj_size_t) const obj_size, NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT offsets,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_t)* SIXTRL_RESTRICT save_ptrs
) SIXTRL_NOEXCEPT;

/* ************************************************************************* */
/* ******                  Change Layout / Reserve                   ******* */
/* ************************************************************************* */

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t)
NS(CObjFlatBuffer_predict_required_num_bytes)(
    NS(cobj_size_t) const obj_handle_size,
    NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t)
NS(CObjFlatBuffer_predict_required_num_slots)(
    NS(cobj_size_t) const obj_handle_size,
    NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_size_t)
NS(CObjFlatBuffer_calc_required_buffer_size)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const max_num_objects,
    NS(cobj_size_t) const max_num_slots,
    NS(cobj_size_t) const max_num_dataptrs,
    NS(cobj_size_t) const max_num_garbage_ranges,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_has_cbuffer_structure)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const current_buffer_capacity,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t) NS(CObjFlatBuffer_init_empty)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const current_buffer_capacity,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t) NS(CObjFlatBuffer_reallocate)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const current_buffer_capacity,
    NS(cobj_size_t) const slot_size,
    NS(cobj_size_t) const max_num_slots,
    NS(cobj_size_t) const max_num_objects,
    NS(cobj_size_t) const max_num_dataptrs,
    NS(cobj_size_t) const max_num_garbage_ranges,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)*
        SIXTRL_RESTRICT ptr_requ_buffer_size )  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t) NS(CObjFlatBuffer_allocate)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const current_buffer_capacity,
    NS(cobj_size_t) const slot_size,
    NS(cobj_size_t) const max_num_slots,
    NS(cobj_size_t) const max_num_objects,
    NS(cobj_size_t) const max_num_dataptrs,
    NS(cobj_size_t) const max_num_garbage_ranges,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)*
        SIXTRL_RESTRICT ptr_buffer_length ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t) NS(CObjFlatBuffer_clear)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    bool const set_data_to_zero,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* ************************************************************************* */
/* ******       Add / ( Remove? ) Objects To The Buffer API          ******* */
/* ************************************************************************* */

SIXTRL_STATIC SIXTRL_FN bool NS(CObjFlatBuffer_can_add_copy_of_object)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    NS(cobj_size_t) const obj_handle_size,
    NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT
        ptr_requ_buffer_size,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_n_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_n_objs,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_num_ptrs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)*
NS(CObjFlatBuffer_add_copy_of_object)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    SIXTRL_BUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_t) const obj_size,
    NS(cobj_type_id_t) const type_id, NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT offsets,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
/* ||||||||||            implementation of inline methods          ||||||||| */
/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */


#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/address_manipulations.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/garbage_range.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* *******         Additional internal functions and helpers        ******** */
/* ************************************************************************* */

/* ------------------------------------------------------------------------- */
/* Helper functions for adding a copy of an object to a flat buffer          */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(_CObjFlatBuffer_memcpy_from_argptr_to_dataptr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT destination,
    SIXTRL_BUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT source,
    NS(cobj_size_t) const num_bytes_to_copy,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(_CObjFlatBuffer_memcpy_from_dataptr_to_argptr)(
    SIXTRL_BUFFER_ARGPTR_DEC void* SIXTRL_RESTRICT destination,
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT source,
    NS(cobj_size_t) const num_bytes_to_copy,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(_CObjFlatBuffer_add_copy_of_object_obj_handle_part)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    SIXTRL_BUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_t) const obj_size,
    NS(cobj_size_t) const predicted_stored_bytes_in_slots,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(_CObjFlatBuffer_add_copy_of_object_ptrs_part)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    SIXTRL_BUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_t) const obj_size,
    NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT offsets,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(_CObjFlatBuffer_add_copy_of_object_ptr_field_part)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    SIXTRL_BUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_t) const obj_size,
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t)* ptr_to_pointer_in_section,
    NS(cobj_address_t) const stored_obj_begin_addr,
    NS(cobj_size_t) const field_offset_from_stored_obj_begin,
    NS(cobj_address_t) const storage_field_data_begin_addr,
    NS(cobj_size_t) const storage_field_data_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)*
NS(_CObjFlatBuffer_add_copy_of_object_index_part)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    NS(cobj_type_id_t) const type_id,
    NS(cobj_size_t) const num_bytes_stored_in_slots,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cobj_status_t)
NS(_CObjFlatBuffer_add_copy_of_object_update_buffer_params)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    NS(cobj_size_t) const requ_num_slots,
    NS(cobj_size_t) const requ_num_objects,
    NS(cobj_size_t) const requ_num_ptrs ) SIXTRL_NOEXCEPT;

/* ************************************************************************* */
/* *******               Minimal Flat Buffer Interface              ******** */
/* ************************************************************************* */

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_slot_based_size)(
    NS(cobj_size_t) const in_length,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)  _size_t;
    _size_t slot_based_length;

    SIXTRL_ASSERT( slot_size > ( _size_t )0u );

    slot_based_length  = in_length / slot_size;
    slot_based_length *= slot_size;

    return ( slot_based_length == in_length )
        ? slot_based_length : ( slot_based_length + slot_size );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t) const*
NS(CObjFlatBuffer_ptr_const_header)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)    _size_t;
    typedef NS(cobj_address_t) _addr_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _addr_t const* _ptr_addr_t;

    _ptr_addr_t ptr_header = SIXTRL_NULLPTR;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > _size_t{ 0 } ) )
    {
        _addr_t const buffer_addr = ( _addr_t )(uintptr_t )buffer;

        SIXTRL_ASSERT( buffer_addr % slot_size == ( _addr_t )0 );
        SIXTRL_ASSERT( NS(CObjFlatBuffer_slot_based_size)(
            sizeof( _addr_t ), slot_size ) > ( _size_t )0u );

        ptr_header = ( _ptr_addr_t )( uintptr_t )buffer_addr;
    }

    return ptr_header;
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t)*
NS(CObjFlatBuffer_ptr_header)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t)* ptr_addr_t;
    return ( ptr_addr_t )NS(CObjFlatBuffer_ptr_const_header)(
        buffer, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_section_entity_size)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_t) entity_size = ( NS(cobj_size_t) )0u;

    SIXTRL_ASSERT( slot_size != ( NS(cobj_size_t) )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );

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
                        sizeof( NS(cobj_address_t) const* ), slot_size );
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
            entity_size = ( NS(cobj_size_t) )0u;
        }
    };

    return entity_size;
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_size_section_header)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_t) sec_header_size = ( NS(cobj_size_t) )0u;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( NS(cobj_size_t) )0u )&&
        ( section_id >= SIXTRL_CBUFFER_SECTION_ID_SLOTS ) &&
        ( section_id <= SIXTRL_CBUFFER_SECTION_ID_GARBAGE ) )
    {
        sec_header_size = NS(CObjFlatBuffer_slot_based_size)(
            sizeof( NS(cobj_size_t) ) * ( NS(cobj_size_t) )2, slot_size );

        SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );
        SIXTRL_ASSERT( sec_header_size > ( NS(cobj_size_t) )0u );
    }

    return sec_header_size;
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_size_header)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_t) header_size = ( NS(cobj_size_t) )0u;

    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t) const* ptr_header =
        NS(CObjFlatBuffer_ptr_const_header)( buffer, slot_size );

    if( ptr_header != SIXTRL_NULLPTR )
    {
        /* NOTE: Check for remap here ? */
        SIXTRL_ASSERT( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] >=
                       ptr_header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ] );

        header_size = ( NS(cobj_size_t)
            )ptr_header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ];
    }

    return header_size;
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_size)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_t) buffer_size = ( NS(cobj_size_t) )0u;

    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t) const* ptr_header =
        NS(CObjFlatBuffer_ptr_const_header)( buffer, slot_size );

    if( ptr_header != SIXTRL_NULLPTR )
    {
        /* NOTE: Check for remap here ? */
        SIXTRL_ASSERT( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] >=
                       ptr_header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ] );

        buffer_size = ( NS(cobj_size_t)
            )ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ];
    }

    return buffer_size;
}

/* -- -- -- -- */

SIXTRL_INLINE NS(cobj_address_t) NS(CObjFlatBuffer_section_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const section_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_address_t) begin_addr =
        ( NS(cobj_address_t) )SIXTRL_COBJECTS_NULL_ADDRESS;

    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t) const* ptr_header =
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

SIXTRL_INLINE NS(ptr_const_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_const_section_begin)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(ptr_const_raw_buffer_data_t) )( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );
}

SIXTRL_INLINE NS(ptr_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_section_begin)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(ptr_raw_buffer_data_t) )( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE bool NS(CObjFlatBuffer_is_section_header_consistent)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_size_t) const* _ptr_size_t;

    NS(cobj_size_t) const sec_header_size =
        NS(CObjFlatBuffer_size_section_header)( buffer, sec_id, slot_size );

    NS(cobj_size_t) const sec_entity_size =
        NS(CObjFlatBuffer_section_entity_size)( buffer, sec_id, slot_size );

    _ptr_size_t ptr_sec_header = ( _ptr_size_t )( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    return (
        ( ptr_sec_header != SIXTRL_NULLPTR ) &&
        ( slot_size > ( NS(cobj_size_t) )0u ) &&
        ( ( uintptr_t )ptr_sec_header % slot_size == ( uintptr_t )0u ) &&
        ( sec_entity_size > ( NS(cobj_size_t) )0u ) &&
        ( sec_entity_size % slot_size == ( NS(cobj_size_t) )0u ) &&
        ( sec_header_size > ( NS(cobj_size_t) )0u ) &&
        ( sec_header_size % slot_size == ( NS(cobj_size_t) )0u ) &&
        ( ptr_sec_header[ 0 ] >= sec_header_size ) &&
        ( ptr_sec_header[ 0 ] % slot_size == ( NS(cobj_size_t) )0u ) &&
        ( ptr_sec_header[ 0 ] >=
          ( sec_header_size + ptr_sec_header[ 1 ] * sec_entity_size ) ) );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_section_max_size)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_size_t) const* _ptr_size_t;

    NS(cobj_size_t) max_section_size = ( NS(cobj_size_t) )0u;
    _ptr_size_t ptr_sec_header = ( _ptr_size_t )( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    if( ptr_sec_header != SIXTRL_NULLPTR )
    {
        SIXTRL_ASSERT( NS(CObjFlatBuffer_is_section_header_consistent)(
            buffer, sec_id, slot_size ) );

        max_section_size = ptr_sec_header[ 0 ];
    }

    return max_section_size;
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_section_num_entities)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_size_t) const* _ptr_size_t;

    NS(cobj_size_t) num_entities = ( NS(cobj_size_t) )0u;

    _ptr_size_t ptr_sec_header = ( _ptr_size_t )( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    if( ptr_sec_header != SIXTRL_NULLPTR )
    {
        SIXTRL_ASSERT( NS(CObjFlatBuffer_is_section_header_consistent)(
            buffer, sec_id, slot_size ) );

        num_entities = ptr_sec_header[ 1 ];
    }

    return num_entities;
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_calc_section_size)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id, NS(cobj_size_t) const num_entities,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_t) calc_section_size = ( NS(cobj_size_t) )0u;

    NS(cobj_size_t) const sec_header_size =
        NS(CObjFlatBuffer_size_section_header)( buffer, sec_id, slot_size );

    NS(cobj_size_t) const sec_entity_size =
        NS(CObjFlatBuffer_section_entity_size)( buffer, sec_id, slot_size );

    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_t) )0u );

    if( ( slot_size > ( NS(cobj_size_t) )0u ) &&
        ( sec_entity_size > ( NS(cobj_size_t) )0u ) &&
        ( sec_header_size > ( NS(cobj_size_t) )0u ) )
    {
        SIXTRL_ASSERT( sec_header_size % slot_size == ( NS(cobj_size_t) )0u );
        SIXTRL_ASSERT( sec_entity_size % slot_size == ( NS(cobj_size_t) )0u );

        calc_section_size = sec_header_size + num_entities * sec_entity_size;
    }

    return calc_section_size;
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_section_size)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_t) const section_size =
        NS(CObjFlatBuffer_size_section_header)(  buffer, sec_id, slot_size ) +
      ( NS(CObjFlatBuffer_section_num_entities)( buffer, sec_id, slot_size ) *
        NS(CObjFlatBuffer_section_entity_size)(  buffer, sec_id, slot_size ) );

    SIXTRL_ASSERT( section_size <= NS(CObjFlatBuffer_section_max_size)(
        buffer, sec_id, slot_size ) );

    return section_size;
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_section_max_num_entities)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_size_t) const sec_header_size =
        NS(CObjFlatBuffer_size_section_header)( buffer, sec_id, slot_size );

    NS(cobj_size_t) const sec_max_size =
        NS(CObjFlatBuffer_section_max_size)( buffer, sec_id, slot_size );

    NS(cobj_size_t) const sec_entity_size =
        NS(CObjFlatBuffer_section_entity_size)( buffer, sec_id, slot_size );

    NS(cobj_size_t) const max_num_elements =
        ( ( sec_header_size <= sec_max_size ) &&
             ( sec_entity_size > ( NS(cobj_size_t) )0u ) )
        ? ( sec_max_size - sec_header_size ) / sec_entity_size
        : ( NS(cobj_size_t) )0u;

    SIXTRL_ASSERT( max_num_elements >= NS(CObjFlatBuffer_section_num_entities)(
        buffer, sec_id, slot_size ) );

    return max_num_elements;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_section_offset)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_address_diff_t) section_offset = ( NS(cobj_address_diff_t) )0u;

    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t) const* ptr_header =
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

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_set_section_num_entities)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const num_entities,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_size_t)* _ptr_sec_header_t;
    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    _ptr_sec_header_t ptr_sec_header = ( _ptr_sec_header_t)( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    if( ptr_sec_header != SIXTRL_NULLPTR )
    {
        SIXTRL_ASSERT( slot_size > ( NS(cobj_size_t) )0u );
        SIXTRL_ASSERT( ( uintptr_t )ptr_sec_header % slot_size == 0u );

        ptr_sec_header[ 1 ] = num_entities;
        status = SIXTRL_COBJECTS_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_set_section_max_size)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const max_section_size,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_size_t)* _ptr_sec_header_t;
    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    _ptr_sec_header_t ptr_sec_header = ( _ptr_sec_header_t)( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    if( ( ptr_sec_header != SIXTRL_NULLPTR ) &&
        ( slot_size > ( NS(cobj_size_t) )0u ) &&
        ( max_section_size % slot_size == ( NS(cobj_size_t) )0u ) &&
        ( max_section_size >= NS(CObjFlatBuffer_size_section_header)(
                buffer, sec_id, slot_size ) ) )
    {
        ptr_sec_header[ 0 ] = max_section_size;
        status = SIXTRL_COBJECTS_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_section_init)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const num_elements_in_section,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t) _size_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_size_t)* _ptr_sec_header_t;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    _ptr_sec_header_t ptr_sec_header = ( _ptr_sec_header_t )( uintptr_t
        )NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    _size_t const section_size = NS(CObjFlatBuffer_calc_section_size)(
        buffer, sec_id, num_elements_in_section, slot_size );

    if( ( ptr_sec_header != SIXTRL_NULLPTR ) && ( slot_size >( _size_t )0u ) &&
        ( section_size > ( _size_t )0u ) )
    {
        ptr_sec_header[ 0 ] = section_size;
        ptr_sec_header[ 1 ] = num_elements_in_section;
        status = SIXTRL_COBJECTS_STATUS_SUCCESS;
    }

    return status;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(cobj_address_t) NS(CObjFlatBuffer_section_end_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_STATIC_VAR NS(cobj_address_t) SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
        ( NS(cobj_address_t) )SIXTRL_COBJECTS_NULL_ADDRESS;

    NS(cobj_size_t) const sec_max_size =
        NS(CObjFlatBuffer_section_max_size)( buffer, sec_id, slot_size );

    NS(cobj_address_t) data_begin_addr =
        NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    return ( data_begin_addr != NULL_ADDR )
         ? ( data_begin_addr + sec_max_size ) : NULL_ADDR;
}


SIXTRL_INLINE NS(ptr_const_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_const_section_end)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(ptr_const_raw_buffer_data_t) )( uintptr_t
        )NS(CObjFlatBuffer_section_end_addr)( buffer, sec_id, slot_size );
}

SIXTRL_INLINE NS(ptr_raw_buffer_data_t) NS(CObjFlatBuffer_ptr_section_end)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(ptr_raw_buffer_data_t) )( uintptr_t
        )NS(CObjFlatBuffer_section_end_addr)( buffer, sec_id, slot_size );
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(cobj_address_t) NS(CObjFlatBuffer_section_data_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_STATIC_VAR NS(cobj_address_t) SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
        ( NS(cobj_address_t) )SIXTRL_COBJECTS_NULL_ADDRESS;

    NS(cobj_size_t) const sec_header_size=
        NS(CObjFlatBuffer_size_section_header)( buffer, sec_id, slot_size );

    NS(cobj_address_t) data_begin_addr =
        NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    return ( data_begin_addr != NULL_ADDR )
         ? ( data_begin_addr + sec_header_size ) : NULL_ADDR;
}


SIXTRL_INLINE NS(ptr_const_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_const_section_data_begin)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(ptr_const_raw_buffer_data_t) )( uintptr_t
        )NS(CObjFlatBuffer_section_data_begin_addr)(buffer, sec_id, slot_size);
}

SIXTRL_INLINE NS(ptr_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_section_data_begin)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(ptr_raw_buffer_data_t) )( uintptr_t
        )NS(CObjFlatBuffer_section_data_begin_addr)(buffer, sec_id, slot_size);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cobj_address_t)
NS(CObjFlatBuffer_section_data_end_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_STATIC_VAR NS(cobj_address_t) SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
        ( NS(cobj_address_t) )SIXTRL_COBJECTS_NULL_ADDRESS;

    NS(cobj_size_t) const sec_size=
        NS(CObjFlatBuffer_section_size)( buffer, sec_id, slot_size );

    NS(cobj_address_t) data_begin_addr =
        NS(CObjFlatBuffer_section_begin_addr)( buffer, sec_id, slot_size );

    return ( data_begin_addr != NULL_ADDR )
         ? ( data_begin_addr + sec_size ) : NULL_ADDR;
}

SIXTRL_INLINE NS(ptr_const_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_const_section_data_end)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(ptr_const_raw_buffer_data_t) )( uintptr_t
        )NS(CObjFlatBuffer_section_data_end_addr)( buffer, sec_id, slot_size );
}

SIXTRL_INLINE NS(ptr_raw_buffer_data_t)
NS(CObjFlatBuffer_ptr_section_data_end)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const sec_id,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(ptr_raw_buffer_data_t) )( uintptr_t
        )NS(CObjFlatBuffer_section_data_end_addr)( buffer, sec_id, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_num_slots)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_num_indices)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_num_pointers)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_num_garbage_ranges)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_max_num_slots)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_max_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_max_num_indices)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_max_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_max_num_pointers)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_max_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t)
NS(CObjFlatBuffer_max_num_garbage_ranges)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_max_num_entities)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_size_slots)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_size_indices)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_size_pointers)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_size_garbage_ranges)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_max_size_slots)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_max_size_indices)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_max_size_pointers)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t)
NS(CObjFlatBuffer_max_size_garbage_ranges)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_address_t) NS(CObjFlatBuffer_slots_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_begin_addr)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );
}

SIXTRL_INLINE NS(cobj_address_t)
NS(CObjFlatBuffer_indices_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_begin_addr)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_address_t)
NS(CObjFlatBuffer_pointers_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_begin_addr)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );
}

SIXTRL_INLINE NS(cobj_address_t)
NS(CObjFlatBuffer_garbage_ranges_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_begin_addr)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );
}

/* ========================================================================= */

SIXTRL_INLINE NS(ptr_const_cobj_index_t) NS(CObjFlatBuffer_const_index)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(ptr_const_cobj_index_t) indices_begin =
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size );

    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_t) )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == 0u );
    SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) );

    return ( ( indices_begin != SIXTRL_NULLPTR ) &&
             ( NS(CObjFlatBuffer_num_objects)( buffer, slot_size ) >
               pos_in_buffer ) )
           ? ( indices_begin + pos_in_buffer ) : SIXTRL_NULLPTR;
}

SIXTRL_INLINE NS(ptr_cobj_index_t) NS(CObjFlatBuffer_index)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size )  SIXTRL_NOEXCEPT
{
    return ( NS(ptr_cobj_index_t) )NS(CObjFlatBuffer_const_index)(
        buffer, pos_in_buffer, slot_size );
}

SIXTRL_INLINE NS(ptr_const_cobj_index_t) NS(CObjFlatBuffer_const_indices_begin)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(ptr_const_cobj_index_t) )( uintptr_t
        )NS(CObjFlatBuffer_section_data_begin_addr)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(ptr_const_cobj_index_t) NS(CObjFlatBuffer_const_indices_end)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(ptr_const_cobj_index_t) indices_end =
        NS(CObjFlatBuffer_const_indices_begin)( buffer, slot_size );

    return ( indices_end != SIXTRL_NULLPTR )
        ? ( indices_end + NS(CObjFlatBuffer_num_objects)( buffer, slot_size ) )
        : SIXTRL_NULLPTR;
}

SIXTRL_INLINE NS(ptr_cobj_index_t) NS(CObjFlatBuffer_indices_begin)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(ptr_cobj_index_t) )( uintptr_t
        )NS(CObjFlatBuffer_section_data_begin_addr)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(ptr_cobj_index_t) NS(CObjFlatBuffer_indices_end)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(ptr_cobj_index_t) indices_end =
        NS(CObjFlatBuffer_indices_begin)( buffer, slot_size );

    return ( indices_end != SIXTRL_NULLPTR )
        ? ( indices_end + NS(CObjFlatBuffer_num_objects)( buffer, slot_size ) )
        : SIXTRL_NULLPTR;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_num_objects)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_num_entities)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_max_num_objects)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_max_num_entities)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_size_objects)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_size)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_max_size_objects)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_max_num_entities)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cobj_address_t) NS(CObjFlatBuffer_objects_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_begin_addr)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_address_t) NS(CObjFlatBuffer_objects_end_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_end_addr)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_address_t) NS(CObjFlatBuffer_objects_data_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

SIXTRL_INLINE NS(cobj_address_t) NS(CObjFlatBuffer_objects_data_end_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjFlatBuffer_section_data_end_addr)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_address_t)
NS(CObjFlatBuffer_index_begin_addr_by_pos_in_buffer_filter_by_type_info)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_type_id_t) const required_type_id,
    NS(cobj_size_t) const min_size,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(CObjIndex_begin_addr_filter_by_type_info)(
        NS(CObjFlatBuffer_const_index)( buffer, pos_in_buffer, slot_size ),
            required_type_id, min_size, slot_size );
}

/* ************************************************************************* */
/* ******                          Remapping                         ******* */
/* ************************************************************************* */

SIXTRL_INLINE NS(cobj_address_t) NS(CObjFlatBuffer_stored_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t) const* ptr_header =
        NS(CObjFlatBuffer_ptr_const_header)( buffer, slot_size );

    return ( ptr_header != SIXTRL_NULLPTR )
        ? ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ]
        : ( NS(cobj_address_t) )SIXTRL_COBJECTS_NULL_ADDRESS;
}

SIXTRL_INLINE NS(cobj_address_t) NS(CObjFlatBuffer_buffer_begin_addr)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_t)  )0u );
    SIXTRL_ASSERT( ( ( ( uintptr_t )buffer ) % slot_size ) == 0u );
    ( void )slot_size;

    return ( NS(cobj_address_t) )( uintptr_t )buffer;
}

SIXTRL_INLINE bool NS(CObjFlatBuffer_needs_remapping)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t) const* ptr_header =
        NS(CObjFlatBuffer_ptr_const_header)( buffer, slot_size );

    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_t) )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );

    return ( ( ptr_header != SIXTRL_NULLPTR ) &&
             ( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ] !=
               ( NS(cobj_address_t) )SIXTRL_COBJECTS_NULL_ADDRESS ) &&
             ( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ] !=
               ( ( NS(cobj_address_t) )( uintptr_t )buffer ) ) );
}

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_base_addr_offset)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_diff_t)*
        SIXTRL_RESTRICT ptr_addr_offset,
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
    NS(cobj_address_diff_t) addr_offset = ( NS(cobj_address_diff_t) )0u;

    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t) const* ptr_header =
        NS(CObjFlatBuffer_ptr_const_header)( buffer, slot_size );

    if( ptr_header != SIXTRL_NULLPTR )
    {
        NS(cobj_address_t) const stored_addr =
            ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ];

        NS(cobj_address_t) const base_addr =
            ( NS(cobj_address_t) )( uintptr_t )buffer;

        SIXTRL_ASSERT( slot_size > ( NS(cobj_size_t) )0u );
        SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );

        addr_offset = ( base_addr > stored_addr )
            ?    ( NS(cobj_address_diff_t) )( base_addr - stored_addr )
            : -( ( NS(cobj_address_diff_t) )( stored_addr - base_addr ) );

        if( ptr_addr_offset != SIXTRL_NULLPTR )
        {
            *ptr_addr_offset = addr_offset;
        }

        status = SIXTRL_COBJECTS_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_remap_header)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_diff_t) const*
        SIXTRL_RESTRICT offsets,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_address_t)      _addr_t;
    typedef NS(cobj_address_diff_t) _diff_t;
    typedef NS(cobj_size_t)         _size_t;

    SIXTRL_BUFFER_DATAPTR_DEC _addr_t* header =
            NS(CObjFlatBuffer_ptr_header)( buffer, slot_size );

    SIXTRL_BUFFER_ARGPTR_DEC _diff_t base_addr_offset = ( _diff_t )0u;
    NS(cobj_status_t) status = NS(CObjFlatBuffer_base_addr_offset)(
        &base_addr_offset, buffer, slot_size );

    if( ( status != SIXTRL_COBJECTS_STATUS_SUCCESS ) ||
        ( base_addr_offset != offsets[ 0 ] ) ||
        ( header == SIXTRL_NULLPTR ) )
    {
        return SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
    }

    SIXTRL_ASSERT( status == SIXTRL_COBJECTS_STATUS_SUCCESS );
    SIXTRL_ASSERT( offsets != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( slot_size > ( NS(cobj_size_t) )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );

    if( base_addr_offset != ( _diff_t )0u )
    {
        SIXTRL_STATIC_VAR _addr_t SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
            ( _addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;

        _size_t const sec_ids[ 5 ] =
        {
            ( _size_t )SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR,
            ( _size_t )SIXTRL_CBUFFER_SECTION_ID_SLOTS,
            ( _size_t )SIXTRL_CBUFFER_SECTION_ID_INDICES,
            ( _size_t )SIXTRL_CBUFFER_SECTION_ID_POINTERS,
            ( _size_t )SIXTRL_CBUFFER_SECTION_ID_GARBAGE
        };

        _addr_t remapped[ 5 ] = { 0u, 0u, 0u, 0u, 0u };

        SIXTRL_ASSERT( header[ sec_ids[ 4 ] ] > header[ sec_ids[ 3 ] ] );
        SIXTRL_ASSERT( header[ sec_ids[ 3 ] ] > header[ sec_ids[ 2 ] ] );
        SIXTRL_ASSERT( header[ sec_ids[ 2 ] ] > header[ sec_ids[ 1 ] ] );
        SIXTRL_ASSERT( header[ sec_ids[ 1 ] ] > header[ sec_ids[ 0 ] ] );

        for( _size_t ii = ( _size_t )0 ; ii < ( _size_t )5 ; ++ii )
        {
            remapped[ ii ] = NS(CObjFlatBuffer_perform_addr_shift)(
                header[ sec_ids[ ii ] ], offsets[ ii ], slot_size );

            if( remapped[ ii ] == NULL_ADDR )
            {
                status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
                break;
            }
        }

        if( ( status == SIXTRL_COBJECTS_STATUS_SUCCESS ) &&
            ( remapped[ 0 ] == ( _addr_t )( uintptr_t )buffer ) )
        {
            for( _size_t ii = ( _size_t )0u ; ii < ( _size_t )5u ; ++ii )
            {
                header[ sec_ids[ ii ] ] = remapped[ ii ];
            }
        }
        else if( status == SIXTRL_COBJECTS_STATUS_SUCCESS )
        {
            status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_remap_section_slots)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_diff_t) const*
        SIXTRL_RESTRICT /* offsets */,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( NS(CObjFlatBuffer_is_section_header_consistent)(
                buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) )
        ? SIXTRL_COBJECTS_STATUS_SUCCESS
        : SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
}

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_remap_section_indices)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_diff_t) const*
        SIXTRL_RESTRICT offsets,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_address_t)      _addr_t;
    typedef NS(cobj_address_diff_t) _diff_t;
    typedef NS(cobj_size_t)         _size_t;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    if( ( offsets != SIXTRL_NULLPTR ) &&
        ( NS(CObjFlatBuffer_is_section_header_consistent)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size ) ) )
    {
        status = SIXTRL_COBJECTS_STATUS_SUCCESS;

        if( ( offsets[ 1 ] != ( _diff_t )0u ) &&
            ( NS(CObjFlatBuffer_num_indices)( buffer,slot_size ) >
              ( _size_t )0u ) )
        {
            _addr_t const slots_begin_addr =
                NS(CObjFlatBuffer_section_data_begin_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            _addr_t const slots_end_addr =
                NS(CObjFlatBuffer_section_data_end_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            _addr_t min_legal_next_addr = slots_begin_addr;

            NS(ptr_cobj_index_t) it =
                NS(CObjFlatBuffer_indices_begin)( buffer, slot_size );

            NS(ptr_cobj_index_t) end =
                NS(CObjFlatBuffer_indices_end)( buffer, slot_size );

            SIXTRL_ASSERT( it != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( ( uintptr_t )it <= ( uintptr_t )end );

            for( ; it != end ; ++it )
            {
                _addr_t const obj_begin_addr = NS(CObjIndex_begin_addr)( it );
                _addr_t const r_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                        obj_begin_addr, offsets[ 1 ], slot_size );

                SIXTRL_ASSERT( NS(CObjIndex_size)( it ) % slot_size ==
                               ( _size_t )0u );

                SIXTRL_ASSERT( min_legal_next_addr >= slots_begin_addr );
                SIXTRL_ASSERT( min_legal_next_addr <  slots_end_addr );

                if( ( r_addr != ( _addr_t )SIXTRL_COBJECTS_NULL_ADDRESS ) &&
                    ( r_addr < slots_end_addr ) &&
                    ( r_addr >= min_legal_next_addr ) )
                {
                    SIXTRL_ASSERT( r_addr % slot_size == ( _addr_t )0u );
                    SIXTRL_ASSERT( min_legal_next_addr % slot_size ==
                                   ( _addr_t )0 );

                    min_legal_next_addr = r_addr + NS(CObjIndex_size)( it );
                    NS(CObjIndex_set_begin_addr)( it, r_addr );
                }
                else
                {
                    status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_remap_section_dataptrs)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_diff_t) const*
        SIXTRL_RESTRICT offsets,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)                     _size_t;
    typedef NS(cobj_address_diff_t)             _diff_t;
    typedef NS(cobj_address_t)                  _addr_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _addr_t*  _ptr_addr_t;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    if( ( offsets != SIXTRL_NULLPTR ) &&
        ( NS(CObjFlatBuffer_is_section_header_consistent)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size ) ) )
    {
        status = SIXTRL_COBJECTS_STATUS_SUCCESS;

        if( ( offsets[ 1 ] != ( _diff_t )0u ) &&
            ( NS(CObjFlatBuffer_num_pointers)( buffer,slot_size ) >
              ( _size_t )0u ) )
        {
            SIXTRL_STATIC_VAR _addr_t SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
                ( _addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;

            _addr_t const slots_begin_addr =
                NS(CObjFlatBuffer_section_data_begin_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            _addr_t const slots_end_addr =
                NS(CObjFlatBuffer_section_data_end_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            _ptr_addr_t it = ( _ptr_addr_t )( uintptr_t
                )NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

            _ptr_addr_t end = ( _ptr_addr_t )( uintptr_t
                )NS(CObjFlatBuffer_section_data_end_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

            SIXTRL_ASSERT( it != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( slots_begin_addr <= slots_end_addr );
            SIXTRL_ASSERT( slots_begin_addr != NULL_ADDR );
            SIXTRL_ASSERT( slots_end_addr   != NULL_ADDR );

            for( ; it != end ; ++it )
            {
                _addr_t const r_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                    *it, offsets[ 1 ], slot_size );

                _ptr_addr_t ptr_in_slots = ( _ptr_addr_t )( uintptr_t )r_addr;

                _addr_t const r_slot_addr = ( r_addr != NULL_ADDR )
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
                    status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_remap_section_garbage)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_diff_t) const*
        SIXTRL_RESTRICT offsets,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)                             _size_t;
    typedef NS(cobj_address_diff_t)                     _diff_t;
    typedef NS(cobj_address_t)                          _addr_t;
    typedef NS(CObjGarbageRange)                        _garbage_range_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _garbage_range_t* _ptr_to_garbage_t;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    if( ( offsets != SIXTRL_NULLPTR ) &&
        ( NS(CObjFlatBuffer_is_section_header_consistent)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size ) ) )
    {
        status = SIXTRL_COBJECTS_STATUS_SUCCESS;

        if( ( offsets[ 1 ] != ( _diff_t )0u ) &&
            ( NS(CObjFlatBuffer_num_pointers)( buffer,slot_size ) >
              ( _size_t )0u ) )
        {
            SIXTRL_STATIC_VAR _addr_t SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
                ( _addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;

            _addr_t const slots_begin_addr =
                NS(CObjFlatBuffer_section_data_begin_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            _addr_t const slots_end_addr =
                NS(CObjFlatBuffer_section_data_end_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            _ptr_to_garbage_t it = ( _ptr_to_garbage_t )( uintptr_t
                )NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

            _ptr_to_garbage_t end = ( _ptr_to_garbage_t )( uintptr_t
                )NS(CObjFlatBuffer_section_data_end_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

            SIXTRL_ASSERT( it != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( slots_begin_addr <= slots_end_addr );
            SIXTRL_ASSERT( slots_begin_addr != NULL_ADDR );
            SIXTRL_ASSERT( slots_end_addr   != NULL_ADDR );

            for( ; it != end ; ++it )
            {
                _addr_t const addr = NS(CObjGarbageRange_begin_addr)( it );

                _addr_t const r_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                    addr, offsets[ 1 ], slot_size );

                if( ( r_addr != NULL_ADDR ) &&
                    ( r_addr >= slots_begin_addr ) &&
                    ( r_addr <  slots_end_addr ) )
                {
                    NS(CObjGarbageRange_set_begin_addr)( it, r_addr );
                }
                else
                {
                    status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }
    }

    return status;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_remap)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size )
{
    NS(cobj_address_diff_t) base_addr_offset = ( NS(cobj_address_diff_t) )0;
    NS(cobj_status_t) status = NS(CObjFlatBuffer_base_addr_offset)(
        &base_addr_offset, buffer, slot_size );

    if( ( status == SIXTRL_COBJECTS_STATUS_SUCCESS ) &&
        ( base_addr_offset != ( NS(cobj_address_diff_t) )0 ) )
    {
        NS(cobj_address_diff_t) const offsets[] =
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

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_apply_addr_offset)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_address_diff_t) const addr_offset,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_address_t)                          _addr_t;
    typedef NS(cobj_address_diff_t)                     _diff_t;
    typedef NS(cobj_size_t)                             _size_t;
    typedef NS(CObjGarbageRange)                        _garbage_range_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _addr_t*          _ptr_addr_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _garbage_range_t* _ptr_garbage_t;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_SUCCESS;
    _ptr_addr_t header = NS(CObjFlatBuffer_ptr_header)( buffer, slot_size );

    if( ( addr_offset != ( _diff_t )0 ) && ( header != SIXTRL_NULLPTR ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) )
    {
        SIXTRL_STATIC_VAR _addr_t SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
            ( _addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;

        _size_t const num_objects = NS(CObjFlatBuffer_num_objects)(
            buffer, slot_size );

        _size_t const num_pointers = NS(CObjFlatBuffer_num_pointers)(
            buffer, slot_size );

        _size_t const num_garbage_ranges =
            NS(CObjFlatBuffer_num_garbage_ranges)( buffer, slot_size );

        _addr_t const slot_begin_addr = NS(CObjFlatBuffer_section_begin_addr)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

        _addr_t const slot_end_addr = NS(CObjFlatBuffer_section_end_addr)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

        _addr_t const r_slot_begin_addr =NS(CObjFlatBuffer_perform_addr_shift)(
            slot_begin_addr, addr_offset, slot_size );

        _addr_t const r_slot_end_addr = NS(CObjFlatBuffer_perform_addr_shift)(
            slot_end_addr, addr_offset, slot_size );

        if( ( r_slot_begin_addr == NULL_ADDR ) ||
            ( r_slot_end_addr == NULL_ADDR ) ||
            ( slot_begin_addr == NULL_ADDR ) ||
            ( slot_end_addr == NULL_ADDR ) )
        {
            return SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
        }

        if( num_garbage_ranges > ( _size_t )0u )
        {
            _ptr_garbage_t it  = ( _ptr_garbage_t )( uintptr_t
                )NS(CObjFlatBuffer_section_data_begin_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

            _ptr_garbage_t end  = ( _ptr_garbage_t )( uintptr_t
                )NS(CObjFlatBuffer_section_data_end_addr)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

            SIXTRL_ASSERT( it != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( ( uintptr_t )end >= ( uintptr_t )it );
            SIXTRL_ASSERT( ( _size_t )( end - it ) == num_garbage_ranges );

            for( ; it != end ; ++it )
            {
                _addr_t const addr = NS(CObjGarbageRange_begin_addr)( it );
                _addr_t const r_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                    addr, addr_offset, slot_size );

                SIXTRL_ASSERT( addr != NULL_ADDR );
                SIXTRL_ASSERT( addr >= slot_begin_addr );
                SIXTRL_ASSERT( addr <  slot_end_addr );

                if( r_addr == NULL_ADDR )
                {
                    status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
                    break;
                }

                NS(CObjGarbageRange_set_begin_addr)( it, r_addr );
            }
        }

        if( ( status == SIXTRL_COBJECTS_STATUS_SUCCESS ) &&
            ( num_pointers > ( _size_t )0 ) )
        {
            _ptr_addr_t it  = ( _ptr_addr_t )( uintptr_t
                )NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

            _ptr_addr_t end = ( _ptr_addr_t )( uintptr_t
                )NS(CObjFlatBuffer_section_data_end_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

            SIXTRL_ASSERT( it != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( ( uintptr_t )end >= ( uintptr_t )it );
            SIXTRL_ASSERT( ( _size_t )( end - it ) == num_pointers );

            for( ; it != end ; ++it )
            {
                _ptr_addr_t slot_ptr = ( _ptr_addr_t )( uintptr_t )*it;

                _addr_t const r_slot_addr = ( *it != NULL_ADDR )
                    ? NS(CObjFlatBuffer_perform_addr_shift)( *slot_ptr,
                        addr_offset, slot_size )
                    : NULL_ADDR;

                _addr_t const r_slot_ptr_addr =
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
                    status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
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

        if( ( status == SIXTRL_COBJECTS_STATUS_SUCCESS ) &&
            ( num_objects > ( _size_t )0u ) )
        {
            NS(ptr_cobj_index_t) it = NS(CObjFlatBuffer_indices_begin)(
                buffer, slot_size );

            NS(ptr_cobj_index_t) end = NS(CObjFlatBuffer_indices_end)(
                buffer, slot_size );

            SIXTRL_ASSERT( it != SIXTRL_NULLPTR );

            for( ; it != end ; ++it )
            {
                _addr_t const obj_addr = NS(CObjIndex_begin_addr)( it );

                if( obj_addr != NULL_ADDR )
                {
                    _addr_t const r_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                        obj_addr, addr_offset, slot_size );

                    SIXTRL_ASSERT( obj_addr >= slot_begin_addr );
                    SIXTRL_ASSERT( obj_addr <  slot_end_addr );
                    SIXTRL_ASSERT( r_addr   >= r_slot_begin_addr );
                    SIXTRL_ASSERT( r_addr   <  r_slot_end_addr );

                    if( r_addr == NULL_ADDR )
                    {
                        status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    NS(CObjIndex_set_begin_addr)( it, r_addr );
                }
            }
        }

        if( status == SIXTRL_COBJECTS_STATUS_SUCCESS )
        {
            _addr_t const r_base_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR ],
                    addr_offset, slot_size );

            _addr_t const r_slots_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                header[ SIXTRL_CBUFFER_SECTION_ID_SLOTS ],
                    addr_offset, slot_size );

            _addr_t const r_objs_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                header[ SIXTRL_CBUFFER_SECTION_ID_INDICES ],
                    addr_offset, slot_size );

            _addr_t const r_ptrs_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                header[ SIXTRL_CBUFFER_SECTION_ID_POINTERS ],
                    addr_offset, slot_size );

            _addr_t const r_garbage_addr = NS(CObjFlatBuffer_perform_addr_shift)(
                header[ SIXTRL_CBUFFER_SECTION_ID_GARBAGE ],
                    addr_offset, slot_size );

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
                status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
            }
        }
    }
    else if( addr_offset != ( _diff_t )0 )
    {
        status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
    }

    return status;
}

/* ************************************************************************* */
/* ******                  Load / Store API support                  ******* */
/* ************************************************************************* */

SIXTRL_INLINE NS(cobj_status_t)
NS(CObjFlatBuffer_store_obj_same_layout_parameters_from_argptr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer, NS(cobj_size_t) const slot_size,
    NS(cobj_type_id_t) const type_id,
    SIXTRL_BUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT obj_to_store,
    NS(cobj_size_t) const obj_size, NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT offsets,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_t)* SIXTRL_RESTRICT save_ptrs
) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)     _size_t;
    typedef NS(cobj_address_t)  _addr_t;
    typedef NS(cobj_raw_t)      _raw_t;

    SIXTRL_STATIC_VAR _raw_t SIXTRL_CONSTEXPR_OR_CONST ZBYTE = ( _raw_t )0u;
    SIXTRL_STATIC_VAR _addr_t SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
        ( _addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
    NS(ptr_const_cobj_index_t) index_obj = NS(CObjFlatBuffer_const_index)(
        buffer, pos_in_buffer, slot_size );

    SIXTRL_ASSERT( type_id != (
        NS(cobj_type_id_t) )SIXTRL_COBJECTS_ILLEGAL_TYPE_ID );

    if( (  index_obj != SIXTRL_NULLPTR ) &&
        (  NS(CObjIndex_type_id)( index_obj ) == type_id ) &&
        (  NS(CObjIndex_begin_addr)( index_obj ) != NULL_ADDR ) &&
        (  NS(CObjIndex_size)( index_obj ) >= obj_size ) &&
        ( obj_size > ( _size_t )0u ) && ( obj_to_store != SIXTRL_NULLPTR ) )
    {
        typedef SIXTRL_BUFFER_DATAPTR_DEC _addr_t*          _ptr_dest_addr_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC _raw_t*           _ptr_dest_data_t;
        typedef SIXTRL_BUFFER_ARGPTR_DEC  _raw_t  const*    _ptr_src_data_t;

        _addr_t const dest_begin_addr =
            NS(CObjIndex_begin_addr)( index_obj );

        _ptr_dest_data_t dest_begin = (
            _ptr_dest_data_t )( uintptr_t )dest_begin_addr;

        _size_t const storage_obj_size =
                NS(CObjFlatBuffer_slot_based_size)( obj_size, slot_size );

        status = ( NS(cobj_status_t) )SIXTRL_COBJECTS_STATUS_SUCCESS;

        SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)(
            buffer, slot_size ) );

        SIXTRL_ASSERT( NS(CObjIndex_begin_addr)( index_obj ) % slot_size ==
                       ( _addr_t )0u );

        if( ( num_pointers > ( _size_t )0u ) &&
            ( save_ptrs != SIXTRL_NULLPTR ) )
        {
            _size_t ii = ( _size_t )num_pointers;

            SIXTRL_ASSERT( ( uintptr_t )obj_to_store % slot_size ==
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
                _size_t const field_offset = offsets[ ii ];
                _addr_t const dest_field_addr = dest_begin_addr + field_offset;
                _ptr_dest_addr_t _ptr_field_addr = ( _ptr_dest_addr_t)(
                    uintptr_t )dest_field_addr;

                if( ( ( field_offset % slot_size ) != ( _size_t )0u ) ||
                    ( ( field_offset + slot_size ) > obj_size ) )
                {
                    status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
                    break;
                }

                save_ptrs[ ii ] = *( _ptr_field_addr );

                if( ( save_ptrs[ ii ] == NULL_ADDR ) &&
                    ( counts[ ii ] * sizes[ ii ] > ( _size_t )0u ) )
                {
                    status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }

        if( status == SIXTRL_COBJECTS_STATUS_SUCCESS )
        {
            if( storage_obj_size > obj_size )
            {
                SIXTRACKLIB_SET_VALUES(
                    _raw_t, dest_begin, storage_obj_size, ZBYTE );
            }

            status = NS(_CObjFlatBuffer_memcpy_from_argptr_to_dataptr)(
                dest_begin, obj_to_store, obj_size, slot_size );
        }

        if( ( status == SIXTRL_COBJECTS_STATUS_SUCCESS ) &&
            ( num_pointers > ( _size_t )0u ) )
        {
            _size_t const requ_storage_size =
                NS(CObjFlatBuffer_predict_required_num_bytes)(
                    obj_size, num_pointers, sizes, counts, slot_size );

            _size_t ii = ( _size_t )0u;

            SIXTRL_ASSERT( requ_storage_size >= storage_obj_size );
            SIXTRL_ASSERT( requ_storage_size % slot_size == ( _size_t )0u );
            SIXTRL_ASSERT( requ_storage_size >=
                NS(CObjIndex_size)( index_obj ) );
            SIXTRL_ASSERT( save_ptrs != SIXTRL_NULLPTR );

            for( ; ii < num_pointers ; ++ii )
            {
                _size_t const field_offset = offsets[ ii ];
                _size_t const field_size = NS(CObjFlatBuffer_slot_based_size)(
                    sizes[ ii ] * counts[ ii ], slot_size );

                _addr_t const src_begin_addr =
                    ( _addr_t )( uintptr_t )obj_to_store;

                _addr_t const src_field_addr = src_begin_addr + field_offset;
                _ptr_src_data_t _ptr_field_src = ( _ptr_src_data_t )(
                    uintptr_t )src_field_addr;

                _addr_t const dest_field_addr = dest_begin_addr + field_offset;
                _ptr_dest_addr_t _ptr_field_dest_addr = ( _ptr_dest_addr_t )(
                    uintptr_t )dest_field_addr;

                _ptr_dest_data_t _ptr_field_dest = ( _ptr_dest_data_t )(
                    uintptr_t )save_ptrs[ ii ];

                SIXTRL_ASSERT( ( field_offset % slot_size ) == ( _size_t )0u );
                SIXTRL_ASSERT( ( field_offset + slot_size ) <= obj_size );
                SIXTRL_ASSERT( ( save_ptrs[ ii ] != NULL_ADDR ) ||
                               ( field_size == ( _size_t )0u ) );

                *_ptr_field_dest_addr = save_ptrs[ ii ];

                status = NS(_CObjFlatBuffer_memcpy_from_argptr_to_dataptr)(
                    _ptr_field_dest, _ptr_field_src, field_size, slot_size );

                if( status != SIXTRL_COBJECTS_STATUS_SUCCESS )
                {
                    break;
                }
            }
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_t)
NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer, NS(cobj_size_t) const slot_size,
    NS(cobj_type_id_t) const type_id,
    SIXTRL_BUFFER_ARGPTR_DEC void* SIXTRL_RESTRICT obj_to_update,
    NS(cobj_size_t) const obj_size, NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT offsets,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_address_t)* SIXTRL_RESTRICT save_ptrs
) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)     _size_t;
    typedef NS(cobj_address_t)  _addr_t;
    typedef NS(cobj_raw_t)      _raw_t;

    SIXTRL_STATIC_VAR _raw_t SIXTRL_CONSTEXPR_OR_CONST ZBYTE = ( _raw_t )0u;
    SIXTRL_STATIC_VAR _addr_t SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
        ( _addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
    NS(ptr_const_cobj_index_t) index_obj = NS(CObjFlatBuffer_const_index)(
        buffer, pos_in_buffer, slot_size );

    SIXTRL_ASSERT( type_id != (
        NS(cobj_type_id_t) )SIXTRL_COBJECTS_ILLEGAL_TYPE_ID );

    if( (  index_obj != SIXTRL_NULLPTR ) &&
        (  NS(CObjIndex_type_id)( index_obj ) == type_id ) &&
        (  NS(CObjIndex_begin_addr)( index_obj ) != NULL_ADDR ) &&
        (  NS(CObjIndex_size)( index_obj ) >= obj_size ) &&
        ( obj_size > ( _size_t )0u ) && ( obj_to_update != SIXTRL_NULLPTR ) )
    {
        typedef SIXTRL_BUFFER_ARGPTR_DEC _addr_t* _ptr_dest_addr_t;
        typedef SIXTRL_BUFFER_ARGPTR_DEC _raw_t* _ptr_dest_data_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC _raw_t const* _ptr_src_data_t;

        _addr_t const dest_begin_addr = ( _addr_t )( uintptr_t )obj_to_update;

        _ptr_dest_data_t dest_begin = (
            _ptr_dest_data_t )( uintptr_t )dest_begin_addr;

        _size_t const storage_obj_size =
                NS(CObjFlatBuffer_slot_based_size)( obj_size, slot_size );

        status = ( NS(cobj_status_t) )SIXTRL_COBJECTS_STATUS_SUCCESS;

        SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)(
            buffer, slot_size ) );

        SIXTRL_ASSERT( NS(CObjIndex_begin_addr)( index_obj ) % slot_size ==
                       ( _addr_t )0u );

        if( ( num_pointers > ( _size_t )0u ) &&
            ( save_ptrs != SIXTRL_NULLPTR ) )
        {
            _size_t ii = ( _size_t )num_pointers;

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
                _size_t const field_offset = offsets[ ii ];
                _addr_t const dest_field_addr = dest_begin_addr + field_offset;
                _ptr_dest_addr_t _ptr_field_addr = ( _ptr_dest_addr_t)(
                    uintptr_t )dest_field_addr;

                if( ( ( field_offset % slot_size ) != ( _size_t )0u ) ||
                    ( ( field_offset + slot_size ) > obj_size ) )
                {
                    status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
                    break;
                }

                save_ptrs[ ii ] = *( _ptr_field_addr );

                if( ( save_ptrs[ ii ] == NULL_ADDR ) &&
                    ( counts[ ii ] * sizes[ ii ] > ( _size_t )0u ) )
                {
                    status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }

        if( status == SIXTRL_COBJECTS_STATUS_SUCCESS )
        {
            _ptr_src_data_t _src = ( _ptr_src_data_t )( uintptr_t
                )NS(CObjIndex_begin_addr)( index_obj );

            if( storage_obj_size > obj_size )
            {
                SIXTRACKLIB_SET_VALUES(
                    _raw_t, dest_begin, storage_obj_size, ZBYTE );
            }

            status = NS(_CObjFlatBuffer_memcpy_from_dataptr_to_argptr)(
                dest_begin, _src, obj_size, slot_size );
        }

        if( ( status == SIXTRL_COBJECTS_STATUS_SUCCESS ) &&
            ( num_pointers > ( _size_t )0u ) )
        {
            _size_t const requ_storage_size =
                NS(CObjFlatBuffer_predict_required_num_bytes)(
                    obj_size, num_pointers, sizes, counts, slot_size );

            _size_t ii = ( _size_t )0u;

            SIXTRL_ASSERT( requ_storage_size >= storage_obj_size );
            SIXTRL_ASSERT( requ_storage_size % slot_size == ( _size_t )0u );
            SIXTRL_ASSERT( requ_storage_size >=
                NS(CObjIndex_size)( index_obj ) );
            SIXTRL_ASSERT( save_ptrs != SIXTRL_NULLPTR );

            for( ; ii < num_pointers ; ++ii )
            {
                _size_t const field_offset = offsets[ ii ];
                _size_t const field_size = NS(CObjFlatBuffer_slot_based_size)(
                    sizes[ ii ] * counts[ ii ], slot_size );

                _addr_t const src_begin_addr =
                    NS(CObjIndex_begin_addr)( index_obj );

                _addr_t const src_field_addr = src_begin_addr + field_offset;
                _ptr_src_data_t _ptr_field_src = ( _ptr_src_data_t )(
                    uintptr_t )src_field_addr;

                _addr_t const dest_field_addr = dest_begin_addr + field_offset;
                _ptr_dest_addr_t _ptr_field_dest_addr = ( _ptr_dest_addr_t )(
                    uintptr_t )dest_field_addr;

                _ptr_dest_data_t _ptr_field_dest = ( _ptr_dest_data_t )(
                    uintptr_t )save_ptrs[ ii ];

                SIXTRL_ASSERT( ( field_offset % slot_size ) == ( _size_t )0u );
                SIXTRL_ASSERT( ( field_offset + slot_size ) <= obj_size );
                SIXTRL_ASSERT( ( save_ptrs[ ii ] != NULL_ADDR ) ||
                               ( field_size == ( _size_t )0u ) );

                *_ptr_field_dest_addr = save_ptrs[ ii ];

                status = NS(_CObjFlatBuffer_memcpy_from_dataptr_to_argptr)(
                    _ptr_field_dest, _ptr_field_src, field_size, slot_size );

                if( status != SIXTRL_COBJECTS_STATUS_SUCCESS )
                {
                    break;
                }
            }
        }
    }

    return status;
}

/* ************************************************************************* */
/* ******                  Change Layout / Reserve                   ******* */
/* ************************************************************************* */

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_predict_required_num_bytes)(
    NS(cobj_size_t) const obj_handle_size,
    NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t) _size_t;
    _size_t requ_num_bytes = ( _size_t )0u;

    if( ( slot_size > ( _size_t )0u ) && ( obj_handle_size > ( _size_t )0u ) )
    {
        requ_num_bytes = NS(CObjFlatBuffer_slot_based_size)(
            obj_handle_size, slot_size );

        SIXTRL_ASSERT( requ_num_bytes > ( _size_t )0u );
        SIXTRL_ASSERT( ( num_pointers == ( _size_t )0u ) ||
                       ( ( counts != SIXTRL_NULLPTR ) &&
                         ( sizes  != SIXTRL_NULLPTR ) ) );

        if( num_pointers > ( _size_t )0u )
        {
            for( _size_t ii = ( _size_t )0u ; ii < num_pointers ; ++ii )
            {
                requ_num_bytes += NS(CObjFlatBuffer_slot_based_size)(
                    counts[ ii ] * sizes[ ii ], slot_size );
            }
        }

        SIXTRL_ASSERT( requ_num_bytes % slot_size == ( _size_t )0u );
    }

    return requ_num_bytes;
}

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_predict_required_num_slots)(
    NS(cobj_size_t) const obj_handle_size,
    NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t) _size_t;
    _size_t requ_num_slots = ( _size_t )0u;

    if( slot_size > ( _size_t )0u )
    {
        _size_t const requ_num_bytes =
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

SIXTRL_INLINE NS(cobj_size_t) NS(CObjFlatBuffer_calc_required_buffer_size)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const max_num_slots,
    NS(cobj_size_t) const max_num_objs,
    NS(cobj_size_t) const max_num_dataptrs,
    NS(cobj_size_t) const max_num_garbage_ranges,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t) _size_t;

    _size_t const header_size =
        NS(CObjFlatBuffer_size_header)( buffer, slot_size );

    _size_t const requ_slots_size = NS(CObjFlatBuffer_calc_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, max_num_slots, slot_size );

    _size_t const requ_objs_size = NS(CObjFlatBuffer_calc_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, max_num_objs, slot_size );

    _size_t const requ_ptrs_size = NS(CObjFlatBuffer_calc_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS,
            max_num_dataptrs, slot_size );

    _size_t const requ_garbage_size = NS(CObjFlatBuffer_calc_section_size)(
        buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE,
            max_num_garbage_ranges, slot_size );

    return header_size +
        requ_slots_size + requ_objs_size + requ_ptrs_size + requ_garbage_size;
}

SIXTRL_INLINE bool NS(CObjFlatBuffer_has_cbuffer_structure)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const buffer_capacity,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)     _size_t;
    typedef NS(cobj_address_t)  _addr_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _addr_t* _ptr_addr_t;

    SIXTRL_STATIC_VAR _size_t const ZERO = ( _size_t )0u;
    SIXTRL_STATIC_VAR _addr_t const NULL_ADDR =
        ( _addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;


    bool has_cbuffer_structure = false;
    _ptr_addr_t header = NS(CObjFlatBuffer_ptr_header)( buffer, slot_size );

    if( ( header != SIXTRL_NULLPTR ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_BASE_ADDR   ] != NULL_ADDR ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] != ZERO ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ] != ZERO ) &&
        ( header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] >
          header[ SIXTRL_CBUFFER_SECTION_ID_HEADER_SIZE ]  ) &&
        ( ( buffer_capacity == ZERO ) ||
          ( ( header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ] >=
              SIXTRL_CBUFFER_MIN_SIZE ) &&
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

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_init_empty)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const buffer_capacity,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)     _size_t;
    typedef NS(cobj_address_t)  _addr_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _addr_t* _ptr_addr_t;

    SIXTRL_STATIC_VAR _size_t const ZERO = ( _size_t )0u;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;
    _ptr_addr_t header = NS(CObjFlatBuffer_ptr_header)( buffer, slot_size );

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ZERO ) &&
        ( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u ) &&
        ( header != SIXTRL_NULLPTR ) )
    {
        typedef NS(cobj_raw_t) _raw_t;

        SIXTRL_STATIC_VAR _raw_t  const ZBYTE = ( _raw_t )0u;

        _addr_t const base_addr = ( _addr_t )( uintptr_t )header;

        _size_t const header_size =
            ( _size_t )SIXTRL_CBUFFER_DEFAULT_HEADER_SIZE;

        _size_t const slots_sec_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, ZERO, slot_size );

        _size_t const objs_sec_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, ZERO, slot_size );

        _size_t const ptrs_sec_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, ZERO, slot_size );

        _size_t const garbage_sec_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, ZERO, slot_size );

        _size_t const buffer_size = header_size + slots_sec_size +
                                    objs_sec_size + ptrs_sec_size +
                                    garbage_sec_size;

        _addr_t sec_begin_addr = base_addr + header_size;
        NS(ptr_raw_buffer_data_t) _raw_header = ( NS(ptr_raw_buffer_data_t) )(
            uintptr_t )base_addr;

        if( buffer_size > buffer_capacity ) return status;

        SIXTRACKLIB_SET_VALUES( _raw_t, _raw_header, buffer_size, ZBYTE );

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

        status = NS(CObjFlatBuffer_section_init)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, ZERO, slot_size );

        if( status == SIXTRL_COBJECTS_STATUS_SUCCESS )
        {
            status = NS(CObjFlatBuffer_section_init)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_SLOTS, ZERO, slot_size );
        }

        if( status == SIXTRL_COBJECTS_STATUS_SUCCESS )
        {
            status = NS(CObjFlatBuffer_section_init)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_INDICES, ZERO, slot_size );
        }

        if( status == SIXTRL_COBJECTS_STATUS_SUCCESS )
        {
            status = NS(CObjFlatBuffer_section_init)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_POINTERS, ZERO, slot_size );
        }

        if( status == SIXTRL_COBJECTS_STATUS_SUCCESS )
        {
            status = NS(CObjFlatBuffer_section_init)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_GARBAGE, ZERO, slot_size );
        }
    }

    return status;

}

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_reallocate)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const current_buffer_capacity,
    NS(cobj_size_t) const slot_size,
    NS(cobj_size_t) const max_n_slots,
    NS(cobj_size_t) const max_n_objs,
    NS(cobj_size_t) const max_n_ptrs,
    NS(cobj_size_t) const max_n_garbage_ranges,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT
        ptr_requ_buffer_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)    _size_t;
    typedef NS(cobj_raw_t)     _raw_t;
    typedef NS(cobj_address_t) _addr_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _raw_t* _ptr_raw_t;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    if( ( buffer != nullptr ) && ( slot_size > ( _size_t )0u ) &&
        ( current_buffer_capacity >= SIXTRL_CBUFFER_MIN_SIZE ) )
    {
        _size_t const cur_buffer_size =
            ::NS(CObjFlatBuffer_size)( buffer, slot_size );

        /* ----------------------------------------------------------------- */
        /* Since this is the realloc method, we need to get the current
         * allocation to understand howto modify the layout */

        _size_t const cur_num_slots =
            ::NS(CObjFlatBuffer_num_slots)( buffer, slot_size );

        _size_t const cur_num_objs =
            ::NS(CObjFlatBuffer_num_objects)( buffer, slot_size );

        _size_t const cur_num_ptrs =
            ::NS(CObjFlatBuffer_num_pointers)( buffer, slot_size );

        _size_t const cur_num_garbage =
            ::NS(CObjFlatBuffer_num_garbage_ranges)( buffer, slot_size );

        /* ----------------------------------------------------------------- */
        /* Get the current max number of enteties per section -> maybe
         * we do not need to reallocate at all? */

        _size_t const cur_max_num_slots =
            ::NS(CObjFlatBuffer_max_num_slots)( buffer, slot_size );

        _size_t const cur_max_num_objs =
            ::NS(CObjFlatBuffer_max_num_objects)( buffer, slot_size );

        _size_t const cur_max_num_ptrs =
            ::NS(CObjFlatBuffer_max_num_pointers)( buffer, slot_size );

        _size_t const cur_max_num_garbage =
            ::NS(CObjFlatBuffer_max_num_garbage_ranges)( buffer, slot_size );

        /* ----------------------------------------------------------------- */
        /* Find the actual requested number of entities for each section ->
         * i.e. if the newly requested max number is smaller than the current
         * occupancy, we have to adapt the requested number accordingly.
         * Note that this does not increase the numbers above what is strictly
         * asked/required, so if you want to be more generous, ask for
         * higher numbers! */

        _size_t const requ_n_slots = ( cur_num_slots <= max_n_slots )
            ? max_n_slots : cur_num_slots;

        _size_t const requ_n_objs = ( cur_num_objs <= max_n_objs )
            ? max_n_objs : cur_num_objs;

        _size_t const requ_n_ptrs = ( cur_num_ptrs <= max_n_ptrs )
            ? max_n_ptrs : cur_num_ptrs;

        _size_t const requ_n_garbage =
            ( cur_num_garbage <= max_n_garbage_ranges )
                ? max_n_garbage_ranges : cur_num_garbage;

        /* ----------------------------------------------------------------*/
        /* Based on the requ_n_* numbers, calculate the required minimum
         * buffer capacity in pieces to also have the partial results for the
         * new section lenghts available */

        _size_t const header_size = NS(CObjFlatBuffer_size_header)(
            buffer, slot_size );

        _size_t const requ_slots_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, requ_n_slots, slot_size );

        _size_t const requ_objs_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, requ_n_objs, slot_size);

        _size_t const requ_ptrs_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS,requ_n_ptrs, slot_size);

        _size_t const requ_garbage_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer,SIXTRL_CBUFFER_SECTION_ID_GARBAGE,requ_n_garbage,slot_size);

        _size_t const requ_buffer_size = header_size + requ_slots_size +
                requ_objs_size + requ_ptrs_size + requ_garbage_size;

        if(  ptr_requ_buffer_size != SIXTRL_NULLPTR )
        {
            *ptr_requ_buffer_size = requ_buffer_size;
        }

        if( ( requ_n_slots     <= cur_max_num_slots   ) &&
            ( requ_n_objs      <= cur_max_num_objs    ) &&
            ( requ_n_ptrs      <= cur_max_num_ptrs    ) &&
            ( requ_n_garbage   <= cur_max_num_garbage ) &&
            ( requ_buffer_size <= cur_buffer_size     ) )
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

            SIXTRL_ASSERT( requ_n_slots     >= max_n_slots );
            SIXTRL_ASSERT( requ_n_objs      >= max_n_objs  );
            SIXTRL_ASSERT( requ_n_ptrs      >= max_n_ptrs  );
            SIXTRL_ASSERT( requ_n_garbage   >= max_n_garbage_ranges );

            return SIXTRL_COBJECTS_STATUS_SUCCESS;
        }

        if( ( cur_buffer_size  <= current_buffer_capacity ) &&
            ( requ_buffer_size <= current_buffer_capacity ) )
        {
            SIXTRL_STATIC_VAR NS(cobj_raw_t) SIXTRL_CONSTEXPR_OR_CONST
                ZERO = ( NS(cobj_raw_t) )0;

            /* Get the current section sizes and offsets */

            _size_t const cur_slots_size =
                ::NS(CObjFlatBuffer_size_slots)( buffer, slot_size );

            _size_t const cur_objs_size =
                ::NS(CObjFlatBuffer_size_objects)( buffer, slot_size );

            _size_t const cur_ptrs_size =
                ::NS(CObjFlatBuffer_size_pointers)( buffer, slot_size );

            _size_t const cur_garbage_size =
                ::NS(CObjFlatBuffer_size_garbage_ranges)( buffer, slot_size );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            _size_t const cur_slots_off = ::NS(CObjFlatBuffer_section_offset)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

            _size_t const cur_objs_off = ::NS(CObjFlatBuffer_section_offset)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );

            _size_t const cur_ptrs_off = ::NS(CObjFlatBuffer_section_offset)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

            _size_t const cur_garbage_off= ::NS(CObjFlatBuffer_section_offset)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

            /* ------------------------------------------------------------- */
            /* Calculate the new offsets */

            _size_t const new_slots_offset = header_size;
            _size_t const new_objs_offset = new_slots_offset + requ_slots_size;
            _size_t const new_ptrs_offset = new_objs_offset + requ_objs_size;

            _size_t const new_garbage_offset =
                new_ptrs_offset + requ_ptrs_size;

            bool slots_finished   = ( new_slots_offset   == cur_slots_off   );
            bool objs_finished    = ( new_objs_offset    == cur_objs_off    );
            bool ptrs_finished    = ( new_ptrs_offset    == cur_ptrs_off    );
            bool garbage_finished = ( new_garbage_offset == cur_garbage_off );

            SIXTRL_ASSERT( new_slots_offset == cur_slots_off );

            /* ------------------------------------------------------------- */

            if( !garbage_finished )
            {
                if( new_garbage_offset > cur_garbage_off )
                {
                    _ptr_raw_t source = buffer + cur_garbage_off;
                    _ptr_raw_t destination = buffer + new_garbage_offset;
                    _size_t nn_at_begin = new_garbage_offset - cur_garbage_off;

                    SIXTRACKLIB_MOVE_VALUES(
                        _raw_t, destination, source, cur_garbage_size );

                    if( nn_at_begin > cur_garbage_size )
                    {
                        nn_at_begin = cur_garbage_size;
                    }

                    SIXTRACKLIB_SET_VALUES( _raw_t, source, nn_at_begin, ZERO);

                    if( requ_garbage_size > cur_garbage_size )
                    {
                        _size_t const nn= requ_garbage_size - cur_garbage_size;

                        SIXTRACKLIB_SET_VALUES( _raw_t,
                            destination + cur_garbage_size, nn, ZERO );
                    }

                    garbage_finished = true;
                }
                else if( new_garbage_offset >=
                            ( cur_ptrs_off + cur_ptrs_size ) )
                {
                    _ptr_raw_t source =      buffer + cur_garbage_off;
                    _ptr_raw_t destination = buffer + new_garbage_offset;

                    SIXTRACKLIB_MOVE_VALUES(
                        _raw_t, destination, source, cur_garbage_size );

                    garbage_finished = true;
                }
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( ( garbage_finished ) && ( !ptrs_finished ) )
            {
                if( new_ptrs_offset > cur_ptrs_off )
                {
                    _ptr_raw_t source      = buffer + cur_ptrs_off;
                    _ptr_raw_t destination = buffer + new_ptrs_offset;
                    _size_t    nn_at_begin = new_ptrs_offset - cur_ptrs_off;

                    SIXTRACKLIB_MOVE_VALUES(
                        _raw_t, destination, source, cur_ptrs_size );

                    if( nn_at_begin > cur_ptrs_size )
                    {
                        nn_at_begin = cur_ptrs_size;
                    }

                    SIXTRACKLIB_SET_VALUES(
                        _raw_t, source, nn_at_begin, ZERO );

                    if( requ_ptrs_size > cur_ptrs_size )
                    {
                        _size_t const bytes_to_fill =
                            requ_ptrs_size - cur_ptrs_size;

                        SIXTRACKLIB_SET_VALUES( _raw_t,
                            destination + cur_ptrs_size, bytes_to_fill, ZERO );
                    }

                    ptrs_finished = true;
                }
                else if( new_ptrs_offset >= ( cur_objs_off + cur_objs_size ) )
                {
                    _ptr_raw_t source      = buffer + cur_ptrs_off;
                    _ptr_raw_t destination = buffer + new_ptrs_offset;

                    SIXTRACKLIB_MOVE_VALUES(
                        _raw_t, destination, source, cur_ptrs_size );

                    ptrs_finished = true;
                }
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( ( garbage_finished ) && ( ptrs_finished ) &&
                ( !objs_finished ) )
            {
                if( new_objs_offset > cur_objs_off )
                {
                    _ptr_raw_t source      = buffer + cur_objs_off;
                    _ptr_raw_t destination = buffer + new_objs_offset;
                    _size_t nn_at_begin    = new_objs_offset - cur_objs_off;

                    SIXTRACKLIB_MOVE_VALUES(
                        _raw_t, destination, source, cur_objs_size );

                    if( nn_at_begin > cur_objs_size )
                    {
                        nn_at_begin = cur_objs_size;
                    }

                    SIXTRACKLIB_SET_VALUES( _raw_t, source, nn_at_begin, ZERO);

                    if( requ_objs_size > cur_objs_size )
                    {
                        _size_t const bytes_to_fill =
                            requ_objs_size - cur_objs_size;

                        SIXTRACKLIB_SET_VALUES( _raw_t,
                            destination + cur_objs_size, bytes_to_fill, ZERO );
                    }

                    objs_finished = true;
                }
                else if( new_objs_offset >= ( cur_slots_off + cur_slots_size ))
                {
                    _ptr_raw_t source      = buffer + cur_objs_off;
                    _ptr_raw_t destination = buffer + new_objs_offset;

                    SIXTRACKLIB_MOVE_VALUES(
                        _raw_t, destination, source, cur_objs_size );

                    objs_finished = true;
                }
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( ( slots_finished ) && ( ptrs_finished ) &&
                ( objs_finished  ) && ( garbage_finished ) )
            {
                if( requ_slots_size > cur_slots_size )
                {
                    _ptr_raw_t destination = buffer + new_slots_offset;
                    _size_t const bytes_to_fill =
                        requ_slots_size - cur_slots_size;

                    SIXTRACKLIB_SET_VALUES( _raw_t,
                        destination + cur_slots_size, bytes_to_fill, ZERO );
                }
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( ( slots_finished ) && ( ptrs_finished ) &&
                ( objs_finished  ) && ( garbage_finished  ) )
            {
                typedef SIXTRL_BUFFER_DATAPTR_DEC _addr_t* _ptr_addr_t;

                _addr_t const begin_addr = ( _addr_t )( uintptr_t )buffer;

                _addr_t const new_slots_section_begin_addr =
                    ( _addr_t )( uintptr_t )( begin_addr + new_slots_offset );

                _addr_t const new_objs_section_begin_addr =
                    ( _addr_t )( uintptr_t )( begin_addr + new_objs_offset );

                _addr_t const new_dataptrs_section_begin_addr =
                    ( _addr_t )( uintptr_t )(begin_addr + new_ptrs_offset );

                _addr_t const new_garbage_section_begin_addr =
                    ( _addr_t )( uintptr_t )(
                        begin_addr + new_garbage_offset );

                _ptr_addr_t ptr_header = NS(CObjFlatBuffer_ptr_header)(
                    buffer, slot_size );

                SIXTRL_ASSERT( ptr_header[ 0 ] ==
                    ( _addr_t )( uintptr_t )buffer );

                SIXTRL_ASSERT( ptr_header[ SIXTRL_CBUFFER_SECTION_ID_SLOTS ] ==
                    new_slots_section_begin_addr );

                ptr_header[ SIXTRL_CBUFFER_SECTION_ID_BUFFER_SIZE ]
                    = requ_buffer_size;

                ptr_header[ SIXTRL_CBUFFER_SECTION_ID_SLOTS ]
                    = new_slots_section_begin_addr;

                ptr_header[ SIXTRL_CBUFFER_SECTION_ID_INDICES ]
                    = new_objs_section_begin_addr;

                ptr_header[ SIXTRL_CBUFFER_SECTION_ID_POINTERS ]
                    = new_dataptrs_section_begin_addr;

                ptr_header[ SIXTRL_CBUFFER_SECTION_ID_GARBAGE ]
                    = new_garbage_section_begin_addr;

                status = NS(CObjFlatBuffer_set_section_max_size)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS,
                        requ_slots_size, slot_size );

                status |= NS(CObjFlatBuffer_set_section_max_size)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES,
                        requ_objs_size, slot_size );

                status |= NS(CObjFlatBuffer_set_section_max_size)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS,
                        requ_ptrs_size, slot_size );

                status |= NS(CObjFlatBuffer_set_section_max_size)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE,
                        requ_garbage_size, slot_size );

                SIXTRL_ASSERT(
                    ( status != SIXTRL_COBJECTS_STATUS_SUCCESS ) ||
                    ( ( NS(CObjFlatBuffer_num_slots)( buffer, slot_size ) ==
                            cur_num_slots ) &&
                      ( NS(CObjFlatBuffer_num_objects)( buffer, slot_size ) ==
                            cur_num_objs ) &&
                      ( NS(CObjFlatBuffer_num_pointers)( buffer, slot_size ) ==
                            cur_num_ptrs ) &&
                      ( NS(CObjFlatBuffer_num_garbage_ranges)( buffer,
                            slot_size ) == cur_num_garbage ) &&
                      ( NS(CObjFlatBuffer_max_num_slots)( buffer, slot_size )
                            >= requ_n_slots ) &&
                      ( NS(CObjFlatBuffer_max_num_objects)( buffer,
                            slot_size ) >= requ_n_objs ) &&
                      ( NS(CObjFlatBuffer_max_num_pointers)( buffer,
                            slot_size ) >= requ_n_ptrs ) &&
                      ( NS(CObjFlatBuffer_max_num_garbage_ranges)(
                            buffer, slot_size ) >= requ_n_garbage ) ) );
            }
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_allocate)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const current_buffer_capacity,
    NS(cobj_size_t) const slot_size,
    NS(cobj_size_t) const max_num_slots,
    NS(cobj_size_t) const max_num_objects,
    NS(cobj_size_t) const max_num_pointers,
    NS(cobj_size_t) const max_num_garbage_ranges,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)*
            SIXTRL_RESTRICT ptr_buffer_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)                     _size_t;
    typedef NS(cobj_address_t)                  _addr_t;
    typedef NS(cobj_raw_t)                      _raw_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _addr_t*  _ptr_addr_t;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( _size_t )0u ) &&
        ( current_buffer_capacity >= SIXTRL_CBUFFER_MIN_SIZE ) )
    {
        _size_t const header_size =
            NS(CObjFlatBuffer_size_header)( buffer, slot_size );

        _size_t const slots_max_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, max_num_slots, slot_size);

        _size_t const objs_max_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_INDICES, max_num_slots,slot_size);

        _size_t const ptrs_max_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, max_num_slots,
                slot_size );

        _size_t const garbage_max_size = NS(CObjFlatBuffer_calc_section_size)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_GARBAGE, max_num_garbage_ranges,
                slot_size );

        _size_t const requ_buffer_size = header_size +
            slots_max_size + objs_max_size + ptrs_max_size  + garbage_max_size;

        _ptr_addr_t ptr_header =
            NS(CObjFlatBuffer_ptr_header)( buffer, slot_size );

        if( ( requ_buffer_size <= current_buffer_capacity ) &&
            ( ptr_header != SIXTRL_NULLPTR ) )
        {
            SIXTRL_STATIC_VAR _raw_t SIXTRL_CONSTEXPR_OR_CONST ZBYTE =
                ( _raw_t )0u;

            _size_t const slots_offset      = header_size;
            _size_t const objs_offset       = slots_offset + slots_max_size;
            _size_t const ptrs_offset       = objs_offset  + objs_max_size;
            _size_t const garbage_offset    = ptrs_offset  + ptrs_max_size;

            _addr_t const buffer_begin_addr = ( _addr_t )( uintptr_t )buffer;
            _addr_t const slots_begin_addr  = buffer_begin_addr + slots_offset;
            _addr_t const objs_begin_addr   = buffer_begin_addr + objs_offset;
            _addr_t const ptrs_begin_addr   = buffer_begin_addr + ptrs_offset;
            _addr_t const garbage_begin_addr =
                buffer_begin_addr + garbage_offset;

            SIXTRACKLIB_SET_VALUES(
                _raw_t, buffer, current_buffer_capacity, ZBYTE );

            ptr_header[ 0 ] = buffer_begin_addr;
            ptr_header[ 1 ] = requ_buffer_size;
            ptr_header[ 2 ] = header_size;
            ptr_header[ 3 ] = slots_begin_addr;
            ptr_header[ 4 ] = objs_begin_addr;
            ptr_header[ 5 ] = ptrs_begin_addr;
            ptr_header[ 6 ] = garbage_begin_addr;

            status = NS(CObjFlatBuffer_set_section_max_size)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_SLOTS, slots_max_size, slot_size );

            status |= NS(CObjFlatBuffer_set_section_max_size)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_INDICES, objs_max_size, slot_size );

            status |= NS(CObjFlatBuffer_set_section_max_size)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_POINTERS, ptrs_max_size, slot_size );

            status |= NS(CObjFlatBuffer_set_section_max_size)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_GARBAGE, garbage_max_size,
                    slot_size );

            status |= NS(CObjFlatBuffer_set_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_SLOTS, max_num_slots, slot_size );

            status |= NS(CObjFlatBuffer_set_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_INDICES, max_num_objects, slot_size );

            status |= NS(CObjFlatBuffer_set_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_POINTERS, max_num_pointers,
                    slot_size );

            status |= NS(CObjFlatBuffer_set_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_GARBAGE,
                    max_num_garbage_ranges, slot_size );
        }

        if(  ptr_buffer_size != SIXTRL_NULLPTR )
        {
            *ptr_buffer_size  = requ_buffer_size;
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_t) NS(CObjFlatBuffer_clear)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    bool const set_data_to_zero,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t) _size_t;
    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;


    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( _size_t )0u ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) )
    {
        _size_t const num_slots =
            NS(CObjFlatBuffer_num_slots)( buffer, slot_size );

        _size_t const num_objects =
            NS(CObjFlatBuffer_num_objects)( buffer, slot_size );

        _size_t const num_pointers =
            NS(CObjFlatBuffer_num_pointers)( buffer, slot_size );

        _size_t const num_garbage_ranges =
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
            if( num_slots > ( _size_t )0u )
            {
                typedef NS(cobj_raw_t) _raw_t;
                SIXTRL_STATIC_VAR _raw_t SIXTRL_CONSTEXPR_OR_CONST
                    ZERO = ( _raw_t )0u;

                NS(ptr_raw_buffer_data_t) slots_begin =
                    NS(CObjFlatBuffer_ptr_section_data_begin)(
                        buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

                _size_t const num_bytes_to_clear = num_slots * slot_size;

                SIXTRL_ASSERT( NS(CObjFlatBuffer_section_entity_size)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) ==
                        slot_size );

                SIXTRL_ASSERT(
                NS(CObjFlatBuffer_size_slots)( buffer, slot_size ) ==
                ( num_bytes_to_clear + NS(CObjFlatBuffer_size_section_header)(
                    buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) ) );

                SIXTRACKLIB_SET_VALUES(
                    _raw_t, slots_begin, num_bytes_to_clear, ZERO );
            }

            if( num_objects > ( _size_t )0u )
            {
                NS(ptr_cobj_index_t) it = NS(CObjFlatBuffer_indices_begin)(
                    buffer, slot_size );

                NS(ptr_cobj_index_t) end = NS(CObjFlatBuffer_indices_end)(
                    buffer, slot_size );

                for( ; it != end ; ++it ) NS(CObjIndex_preset)( it );
            }

            if( num_pointers > ( _size_t )0u )
            {
                typedef NS(cobj_address_t) _addr_t;
                typedef SIXTRL_BUFFER_DATAPTR_DEC _addr_t* _ptr_addr_t;

                SIXTRL_STATIC_VAR _addr_t SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
                    ( _addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;

                _ptr_addr_t it = ( _ptr_addr_t )( uintptr_t
                    )NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
                        SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

                _ptr_addr_t end = ( _ptr_addr_t )( uintptr_t
                    )NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
                        SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

                for( ; it != end ; ++it ) *it = NULL_ADDR;
            }

            if( num_garbage_ranges > ( _size_t )0u )
            {
                typedef NS(CObjGarbageRange) _garbage_t;
                typedef SIXTRL_BUFFER_DATAPTR_DEC _garbage_t* _ptr_garbage_t;

                _ptr_garbage_t it = ( _ptr_garbage_t )( uintptr_t
                    )NS(CObjFlatBuffer_section_data_begin_addr)( buffer,
                        SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

                _ptr_garbage_t end = ( _ptr_garbage_t )( uintptr_t
                    )NS(CObjFlatBuffer_section_data_end_addr)( buffer,
                        SIXTRL_CBUFFER_SECTION_ID_GARBAGE, slot_size );

                for( ; it != end ; ++it ) NS(CObjGarbageRange_preset)( it );
            }
        }

        status = NS(CObjFlatBuffer_set_section_num_entities)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, ( _size_t )0u, slot_size );

        status |= NS(CObjFlatBuffer_set_section_num_entities)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_INDICES, ( _size_t )0u, slot_size );

        status |= NS(CObjFlatBuffer_set_section_num_entities)(buffer,
            SIXTRL_CBUFFER_SECTION_ID_POINTERS, ( _size_t )0u, slot_size );

        status |= NS(CObjFlatBuffer_set_section_num_entities)(buffer,
            SIXTRL_CBUFFER_SECTION_ID_GARBAGE, ( _size_t )0u, slot_size );
    }

    return status;
}

/* ************************************************************************* */
/* ******       Add / ( Remove? ) Objects To The Buffer API          ******* */
/* ************************************************************************* */

SIXTRL_INLINE bool NS(CObjFlatBuffer_can_add_copy_of_object)(
    NS(ptr_const_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    NS(cobj_size_t) const obj_handle_size,
    NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_n_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_n_objs,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT ptr_requ_n_ptrs
) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t) _size_t;
    bool can_be_added = false;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( _size_t )0u ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) &&
        ( obj_handle_size > ( _size_t )0u ) &&
        ( ( num_pointers == ( _size_t )0u ) ||
          ( ( num_pointers > ( _size_t )0u ) &&
            ( sizes != SIXTRL_NULLPTR ) && ( counts != SIXTRL_NULLPTR ) &&
            ( sizes != counts ) ) ) )
    {
        _size_t const cur_num_slots =
            NS(CObjFlatBuffer_num_slots)( buffer, slot_size );

        _size_t const max_num_slots =
            NS(CObjFlatBuffer_max_num_slots)( buffer, slot_size );

        _size_t const req_num_slots = cur_num_slots +
            NS(CObjFlatBuffer_predict_required_num_slots)( obj_handle_size,
                num_pointers, sizes, counts, slot_size );

        _size_t const cur_num_objs =
            NS(CObjFlatBuffer_num_objects)( buffer, slot_size );

        _size_t const max_num_objs =
            NS(CObjFlatBuffer_max_num_slots)( buffer, slot_size );

        _size_t const req_num_objs = cur_num_objs + ( _size_t )1u;

        _size_t const cur_num_ptrs =
            NS(CObjFlatBuffer_num_pointers)( buffer, slot_size );

        _size_t const max_num_ptrs =
            NS(CObjFlatBuffer_max_num_slots)( buffer, slot_size );

        _size_t const req_num_ptrs = cur_num_ptrs + num_pointers;

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

SIXTRL_INLINE NS(ptr_cobj_index_t) NS(CObjFlatBuffer_add_copy_of_object)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    SIXTRL_BUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_t) const obj_size,
    NS(cobj_type_id_t) const type_id, NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT offsets,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)    _size_t;
    typedef NS(cobj_address_t) _addr_t;

    NS(ptr_cobj_index_t) ptr_added_obj = SIXTRL_NULLPTR;

    _addr_t const begin_addr = ( _addr_t )( uintptr_t )buffer;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( _size_t )0u ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) &&
        ( ( begin_addr % slot_size ) == ( uintptr_t )0u ) &&
        ( ptr_obj_to_copy != SIXTRL_NULLPTR ) && ( obj_size > ( _size_t)0u ) &&
        ( type_id != ( NS(cobj_type_id_t) )SIXTRL_COBJECTS_ILLEGAL_TYPE_ID ) &&
        ( ( num_pointers == ( _size_t )0u ) ||
          ( ( num_pointers > ( _size_t )0u ) &&
            ( offsets != SIXTRL_NULLPTR ) && ( sizes != SIXTRL_NULLPTR ) &&
            ( counts  != SIXTRL_NULLPTR ) && ( sizes != counts  ) &&
            ( counts  != offsets        ) && ( sizes != offsets ) ) ) )
    {
        _size_t const obj_size_for_storage =
            NS(CObjFlatBuffer_slot_based_size)( obj_size, slot_size );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        _size_t const cur_num_slots =
            NS(CObjFlatBuffer_num_slots)( buffer, slot_size );

        _size_t const additional_num_slots =
            NS(CObjFlatBuffer_predict_required_num_slots)(
                obj_size, num_pointers, sizes, counts, slot_size );

        _size_t const requ_num_slots = cur_num_slots + additional_num_slots;

        _size_t const max_num_slots =
            NS(CObjFlatBuffer_max_num_slots)( buffer, slot_size );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        _size_t const cur_num_objs =
            NS(CObjFlatBuffer_num_objects)( buffer, slot_size );

        _size_t const requ_num_objs = cur_num_objs + ( _size_t )1u;

        _size_t const max_num_objs =
            NS(CObjFlatBuffer_max_num_objects)( buffer, slot_size );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        _size_t const cur_num_ptrs =
            NS(CObjFlatBuffer_num_pointers)( buffer, slot_size );

        _size_t const requ_num_ptrs = cur_num_ptrs + num_pointers;

        _size_t const max_num_ptrs =
            NS(CObjFlatBuffer_max_num_pointers)( buffer, slot_size );

        NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_ASSERT( cur_num_slots <= max_num_slots );
        SIXTRL_ASSERT( cur_num_objs  <= max_num_objs  );
        SIXTRL_ASSERT( cur_num_ptrs  <= max_num_ptrs  );
        SIXTRL_ASSERT( obj_size_for_storage >= obj_size );

        if( ( requ_num_slots <= max_num_slots ) &&
            ( requ_num_objs  <= max_num_objs  ) &&
            ( requ_num_ptrs  <= max_num_ptrs  ) )
        {
            _size_t const max_num_garbage_ranges =
                NS(CObjFlatBuffer_max_num_garbage_ranges)( buffer, slot_size );

            _size_t const predicted_stored_bytes_in_slots =
                additional_num_slots * slot_size;

            SIXTRL_ASSERT( NS(CObjFlatBuffer_calc_required_buffer_size)(
                buffer, requ_num_slots, requ_num_objs, requ_num_ptrs,
                    max_num_garbage_ranges, slot_size ) <=
                        NS(CObjFlatBuffer_size)( buffer, slot_size ) );

            status = NS(_CObjFlatBuffer_add_copy_of_object_obj_handle_part)(
                buffer, slot_size, ptr_obj_to_copy, obj_size,
                    predicted_stored_bytes_in_slots, init_space_with_zeros );

            if( ( status == SIXTRL_COBJECTS_STATUS_SUCCESS ) &&
                ( num_pointers > ( _size_t )0u ) )
            {
                status = NS(_CObjFlatBuffer_add_copy_of_object_ptrs_part)(
                    buffer, slot_size, ptr_obj_to_copy, obj_size, num_pointers,
                        offsets, sizes, counts, init_space_with_zeros );
            }

            if( status == SIXTRL_COBJECTS_STATUS_SUCCESS )
            {
                NS(ptr_cobj_index_t) ptr_temp_index =
                    NS(_CObjFlatBuffer_add_copy_of_object_index_part)( buffer,
                        slot_size, type_id, predicted_stored_bytes_in_slots,
                            init_space_with_zeros );

                if( ( ptr_temp_index != SIXTRL_NULLPTR ) &&
                    ( SIXTRL_COBJECTS_STATUS_SUCCESS ==
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

/* ------------------------------------------------------------------------- */
/* Helper functions implementation for adding a copy of an object to buffer  */
/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(cobj_status_t)
NS(_CObjFlatBuffer_memcpy_from_argptr_to_dataptr)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT destination,
    SIXTRL_BUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT source,
    NS(cobj_size_t) const num_bytes_to_copy, NS(cobj_size_t) const slot_size
) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t) _size_t;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    if( ( destination != SIXTRL_NULLPTR ) && ( slot_size > ( _size_t )0u ) &&
        ( ( uintptr_t )destination % slot_size == ( uintptr_t )0u ) &&
        ( source != SIXTRL_NULLPTR ) )
    {
        status = SIXTRL_COBJECTS_STATUS_SUCCESS;

        if( num_bytes_to_copy > ( _size_t )0u )
        {
            #if !defined( _GPUCODE )
                #if defined( __cplusplus )
                typedef NS(cobj_raw_t) _raw_t;
                typedef SIXTRL_BUFFER_ARGPTR_DEC _raw_t const* _ptr_raw_src_t;

                _ptr_raw_src_t src_begin = reinterpret_cast< _ptr_raw_src_t >(
                    reinterpret_cast< uintptr_t >( source ) );
                _ptr_raw_src_t src_end = src_begin;
                std::advance(  src_end, num_bytes_to_copy );
                std::copy( src_begin, src_end, destination );

                #else /* C++ */
                memcpy( destination, source, num_bytes_to_copy );

                #endif /* C++ */

            #else /* defined( _GPUCODE ) */
            typedef NS(cobj_raw_t) _raw_t;
            typedef SIXTRL_BUFFER_ARGPTR_DEC _raw_t const* _ptr_raw_src_t;
            typedef SIXTRL_BUFFER_DATAPTR_DEC _raw_t*      _ptr_raw_dest_t;

            _ptr_raw_dest_t dest_it = destination;
            _ptr_raw_src_t  src_it  = ( _ptr_raw_src_t )( uintptr_t )source;
            _ptr_raw_src_t  src_end = src_it + num_bytes_to_copy;

            for( ; src_it != src_end ; ++src_it, ++dest_it )
            {
                *src_it = *dest_it;
            }

            #endif /* _GPUCODE ) */
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_t)
NS(_CObjFlatBuffer_memcpy_from_dataptr_to_argptr)(
    SIXTRL_BUFFER_ARGPTR_DEC void* SIXTRL_RESTRICT destination,
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT source,
    NS(cobj_size_t) const num_bytes_to_copy,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t) _size_t;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    if( ( destination != SIXTRL_NULLPTR ) && ( slot_size > ( _size_t )0u ) &&
        ( source != SIXTRL_NULLPTR ) &&
        ( ( uintptr_t )source % slot_size == ( uintptr_t )0u ) )
    {
        status = SIXTRL_COBJECTS_STATUS_SUCCESS;

        if( num_bytes_to_copy > ( _size_t )0u )
        {
            #if !defined( _GPUCODE )
                #if defined( __cplusplus )
                typedef NS(cobj_raw_t) _raw_t;
                typedef SIXTRL_BUFFER_ARGPTR_DEC _raw_t* _ptr_raw_dest_t;
                typedef SIXTRL_BUFFER_DATAPTR_DEC _raw_t const* _ptr_raw_src_t;

                _ptr_raw_dest_t dest_begin = reinterpret_cast< _ptr_raw_dest_t
                    >( reinterpret_cast< uintptr_t >( destination ) );

                _ptr_raw_src_t src_begin = reinterpret_cast< _ptr_raw_src_t >(
                    reinterpret_cast< uintptr_t >( source ) );

                _ptr_raw_src_t src_end = src_begin;
                std::advance(  src_end, num_bytes_to_copy );
                std::copy( src_begin, src_end, dest_begin );

                #else /* C++ */
                memcpy( destination, source, num_bytes_to_copy );

                #endif /* C++ */

            #else /* defined( _GPUCODE ) */
            typedef NS(cobj_raw_t) _raw_t;
            typedef SIXTRL_BUFFER_ARGPTR_DEC _raw_t const* _ptr_raw_src_t;
            typedef SIXTRL_BUFFER_DATAPTR_DEC _raw_t*      _ptr_raw_dest_t;

            _ptr_raw_dest_t dest_it =
                ( _ptr_raw_dest_t )( uintptr_t )destination;

            _ptr_raw_src_t  src_it  = source;
            _ptr_raw_src_t  src_end = src_it + num_bytes_to_copy;

            for( ; src_it != src_end ; ++src_it, ++dest_it )
            {
                *src_it = *dest_it;
            }

            #endif /* _GPUCODE ) */
        }
    }

    return status;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

SIXTRL_INLINE NS(cobj_status_t)
NS(_CObjFlatBuffer_add_copy_of_object_obj_handle_part)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    SIXTRL_BUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_t) const obj_size,
    NS(cobj_size_t) const predicted_stored_bytes_in_slots,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)     _size_t;
    typedef NS(cobj_address_t)  _addr_t;
    typedef NS(cobj_raw_t)      _raw_t;
    typedef SIXTRL_BUFFER_ARGPTR_DEC    _raw_t const* _ptr_obj_src_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC   _raw_t*       _ptr_obj_dest_t;

    SIXTRL_STATIC_VAR _raw_t SIXTRL_CONSTEXPR_OR_CONST ZBYTE = ( _raw_t )0u;
    SIXTRL_STATIC_VAR _addr_t SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
        ( _addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( _size_t )0u ) &&
        ( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) &&
        ( ptr_obj_to_copy != SIXTRL_NULLPTR ) &&
        ( obj_size > ( _size_t )0u )  )
    {
        /* End of current slots data -> begin of stored obj!! */
        _addr_t const obj_addr = NS(CObjFlatBuffer_section_data_end_addr)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

        _ptr_obj_dest_t dest = ( _ptr_obj_dest_t )( uintptr_t )obj_addr;
        _ptr_obj_src_t  src  = ( _ptr_obj_src_t )( uintptr_t )ptr_obj_to_copy;

        /* Perform some consistency checks to ensure that we will
         * not overwrite the boundaries between the sections ->
         * there should be no problems, so every violation here would
         * be pretty exceptional */

        SIXTRL_ASSERT( obj_addr != NULL_ADDR  );

        SIXTRL_ASSERT( NS(CObjFlatBuffer_section_end_addr)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) >=
                ( obj_addr + predicted_stored_bytes_in_slots ) );

        SIXTRL_ASSERT( predicted_stored_bytes_in_slots >= obj_size );
        SIXTRL_ASSERT( predicted_stored_bytes_in_slots >=
            NS(CObjFlatBuffer_slot_based_size)( obj_size, slot_size ) );

        if( init_space_with_zeros )
        {
            SIXTRACKLIB_SET_VALUES(
                _raw_t, dest, predicted_stored_bytes_in_slots, ZBYTE );
        }

        /* Copy the obj handle to the begin of the slots section */

        status = NS(_CObjFlatBuffer_memcpy_from_argptr_to_dataptr)(
            dest, src, obj_size, slot_size );
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_t)
NS(_CObjFlatBuffer_add_copy_of_object_ptr_field_part)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    SIXTRL_BUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_t) const obj_size,
    SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_address_t)* ptr_to_pointer_in_section,
    NS(cobj_address_t) const stored_obj_begin_addr,
    NS(cobj_size_t) const field_offset_from_stored_obj_begin,
    NS(cobj_address_t) const storage_field_data_begin_addr,
    NS(cobj_size_t) const storage_field_data_size ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)                         _size_t;
    typedef NS(cobj_address_t)                      _addr_t;
    typedef NS(cobj_raw_t)                          _raw_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _addr_t*      _ptr_dest_addr_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _raw_t*       _ptr_dest_data_t;
    typedef SIXTRL_BUFFER_ARGPTR_DEC _addr_t const* _ptr_target_addr_t;
    typedef SIXTRL_BUFFER_ARGPTR_DEC _raw_t  const* _ptr_source_data_t;

    SIXTRL_STATIC_VAR _addr_t SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR = ( _addr_t
        )SIXTRL_COBJECTS_NULL_ADDRESS;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( slot_size > ( _size_t )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );
    SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) );
    SIXTRL_ASSERT( ptr_obj_to_copy != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( obj_size >= slot_size );
    SIXTRL_ASSERT( storage_field_data_size % slot_size == ( _size_t )0u );
    SIXTRL_ASSERT( stored_obj_begin_addr != NULL_ADDR );
    SIXTRL_ASSERT( stored_obj_begin_addr % slot_size == ( _addr_t )0u );

    /* We are not checking the field_offset_from_stored_obj_begin and assume
     * it's legal and has been checked by the calling function ->
     * see discussion in NS(_CObjFlatBuffer_add_copy_of_object_ptrs_part) on
     * which constraints to this parameter! */

    if( ( ptr_to_pointer_in_section != SIXTRL_NULLPTR ) &&
        ( storage_field_data_begin_addr % slot_size == ( _addr_t )0u ) )
    {
        _addr_t const pointer_target_in_obj_addr =
            stored_obj_begin_addr + field_offset_from_stored_obj_begin;

        _ptr_dest_addr_t ptr_pointer_target_in_obj = ( _ptr_dest_addr_t
            )( uintptr_t )pointer_target_in_obj_addr;

        _addr_t const orig_obj_begin_addr =
            ( _addr_t )( uintptr_t )ptr_obj_to_copy;

        _addr_t const orig_pointer_target_in_obj_addr =
            orig_obj_begin_addr + field_offset_from_stored_obj_begin;

        _ptr_target_addr_t ptr_target_addr =
            ( _ptr_target_addr_t )( uintptr_t )orig_pointer_target_in_obj_addr;

        SIXTRL_ASSERT( pointer_target_in_obj_addr % slot_size ==
            ( _addr_t )0u );

        status = SIXTRL_COBJECTS_STATUS_SUCCESS;

        if( ( *ptr_target_addr != NULL_ADDR ) &&
            ( storage_field_data_size > ( _size_t )0u ) )
        {
            _ptr_source_data_t field_data_src = ( _ptr_source_data_t )(
                uintptr_t )( *ptr_target_addr );

            _ptr_dest_data_t field_data_dest = ( _ptr_dest_data_t )(
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

        if( status == SIXTRL_COBJECTS_STATUS_SUCCESS )
        {
            *ptr_pointer_target_in_obj = storage_field_data_begin_addr;
            *ptr_to_pointer_in_section = pointer_target_in_obj_addr;
        }
    }

    return status;
}

SIXTRL_INLINE NS(cobj_status_t)
NS(_CObjFlatBuffer_add_copy_of_object_ptrs_part)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    SIXTRL_BUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT ptr_obj_to_copy,
    NS(cobj_size_t) const obj_size,
    NS(cobj_size_t) const num_pointers,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT offsets,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t) const* SIXTRL_RESTRICT counts,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)                         _size_t;
    typedef NS(cobj_address_t)                      _addr_t;
    typedef NS(cobj_raw_t)                          _raw_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _addr_t*      _ptr_addr_t;

    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    _size_t const storage_obj_size = NS(CObjFlatBuffer_slot_based_size)(
        obj_size, slot_size );

    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( slot_size > ( _size_t )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );
    SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) );
    SIXTRL_ASSERT( storage_obj_size % slot_size == ( _size_t )0u );
    SIXTRL_ASSERT( ( num_pointers == ( _size_t )0u ) ||
        ( storage_obj_size >= slot_size ) );

    SIXTRL_ASSERT( ( num_pointers == ( _size_t )0u ) ||
        ( ( offsets != SIXTRL_NULLPTR ) && ( counts != SIXTRL_NULLPTR ) &&
          ( offsets != counts ) && ( sizes != SIXTRL_NULLPTR ) &&
          ( offsets != sizes  ) && ( sizes != counts ) ) );

    if( ( num_pointers > ( _size_t )0u ) &&
        ( ptr_obj_to_copy != SIXTRL_NULLPTR ) )
    {
        /* The object handle would have been added to at the end of the
         * current slots data section -> use this address as the minimum
         * address which a pointer can have */
        _addr_t const obj_handle_addr =
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

        _size_t const max_allowed_offset = ( storage_obj_size == obj_size )
            ? ( storage_obj_size - slot_size )
            : ( ( obj_size > slot_size )
                    ? slot_size * ( ( obj_size / slot_size ) - ( _size_t )1 )
                    : ( _size_t )0u );

        /* The end of the obj handle is also the begin of the area where
         * the arrays for the fields of the object are stored */
        _addr_t storage_fields_data_addr = obj_handle_addr + storage_obj_size;

        /* The number of pointers to be stored need the following number of
         * bytes on the buffer */
        _size_t const storage_ptrs_size = NS(CObjFlatBuffer_slot_based_size)(
                sizeof( _ptr_addr_t ) * num_pointers, slot_size );

        /* The end of the current pointers data section is the begin address
         * for the data - pointers of this element: */
        _addr_t ptrs_begin_addr = NS(CObjFlatBuffer_section_data_end_addr)(
            buffer, SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size );

        _ptr_addr_t out_it  = ( _ptr_addr_t )( uintptr_t )ptrs_begin_addr;

        _size_t ii = ( _size_t )0u;

        SIXTRL_ASSERT( ptrs_begin_addr % slot_size == ( _addr_t )0u );
        SIXTRL_ASSERT( NS(CObjFlatBuffer_section_end_addr)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_POINTERS, slot_size ) >=
                ( ptrs_begin_addr + storage_ptrs_size ) );

        SIXTRL_ASSERT( NS(CObjFlatBuffer_section_end_addr)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) >=
                storage_fields_data_addr );

        if( init_space_with_zeros )
        {
            SIXTRL_STATIC_VAR _raw_t SIXTRL_CONSTEXPR_OR_CONST
                ZBYTE = ( _raw_t )0u;

            NS(ptr_raw_buffer_data_t) dest = ( NS(ptr_raw_buffer_data_t) )(
                uintptr_t )ptrs_begin_addr;

            SIXTRACKLIB_SET_VALUES( _raw_t, dest, storage_ptrs_size, ZBYTE );
        }

        for( ; ii < num_pointers ; ++ii, ++out_it )
        {
            status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

            /* [1] See above for the calculation of max_allowed_offset
             *     from the obj_size; change this calculation above and
             *     DO NOT CHANGE this check here if you want to change the
             *     behaviour! */

            if( offsets[ ii ] <= max_allowed_offset )
            {
                /* NOTE: field_size == 0 is, on purpose, a valid result here */
                _size_t const field_size = NS(CObjFlatBuffer_slot_based_size)(
                    sizes[ ii ] * counts[ ii ], slot_size );

                status = NS(_CObjFlatBuffer_add_copy_of_object_ptr_field_part)(
                    buffer, slot_size, ptr_obj_to_copy, obj_size,
                        out_it, obj_handle_addr, offsets[ ii ],
                            storage_fields_data_addr, field_size );

                storage_fields_data_addr += field_size;
            }

            /* One final check to ensure that the field data does not
             * run past the section limit! */

            SIXTRL_ASSERT( ( status != SIXTRL_COBJECTS_STATUS_SUCCESS ) ||
                ( NS(CObjFlatBuffer_section_end_addr)( buffer,
                    SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) >=
                        storage_fields_data_addr ) );

            if( status != SIXTRL_COBJECTS_STATUS_SUCCESS ) break;
        }
    }
    else if( num_pointers == ( _size_t )0u )
    {
        status = SIXTRL_COBJECTS_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(ptr_cobj_index_t)
NS(_CObjFlatBuffer_add_copy_of_object_index_part)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    NS(cobj_type_id_t) const type_id,
    NS(cobj_size_t) const num_bytes_stored_in_slots,
    bool const init_space_with_zeros ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t)                             _size_t;
    typedef NS(cobj_address_t)                          _addr_t;
    typedef NS(cobj_raw_t)                              _raw_t;
    typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* _ptr_index_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC _raw_t*           _ptr_raw_t;

    SIXTRL_STATIC_VAR _addr_t SIXTRL_CONSTEXPR_OR_CONST NULL_ADDR =
        ( _addr_t )SIXTRL_COBJECTS_NULL_ADDRESS;

    _ptr_index_t ptr_stored_index = SIXTRL_NULLPTR;

    _size_t const storage_index_size = NS(CObjFlatBuffer_slot_based_size)(
        sizeof( NS(CObjIndex) ), slot_size );

    _addr_t const stored_obj_begin_addr =
        NS(CObjFlatBuffer_section_data_end_addr)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size );

    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( slot_size > ( _size_t )0u );
    SIXTRL_ASSERT( ( uintptr_t )buffer % slot_size == ( uintptr_t )0u );
    SIXTRL_ASSERT( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) );
    SIXTRL_ASSERT( num_bytes_stored_in_slots >= slot_size );
    SIXTRL_ASSERT( num_bytes_stored_in_slots % slot_size == ( _size_t )0u );

    SIXTRL_ASSERT( stored_obj_begin_addr % slot_size == ( _addr_t )0u );
    SIXTRL_ASSERT( stored_obj_begin_addr != NULL_ADDR );

    /* Check that the stored obj plus the amount of data stored in slots
     * still fits into the slots section */
    SIXTRL_ASSERT( NS(CObjFlatBuffer_section_end_addr)( buffer,
        SIXTRL_CBUFFER_SECTION_ID_SLOTS, slot_size ) >= (
            ( stored_obj_begin_addr + num_bytes_stored_in_slots ) ) );

    if( type_id != ( NS(cobj_type_id_t) )SIXTRL_COBJECTS_ILLEGAL_TYPE_ID )
    {
        _addr_t const index_begin_addr =
            NS(CObjFlatBuffer_section_data_end_addr)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size );

        SIXTRL_ASSERT( index_begin_addr != NULL_ADDR );
        SIXTRL_ASSERT( index_begin_addr % slot_size == ( _addr_t )0u );

        /* Verify that we have enough space in the indices section to store one
        * more index object */
        SIXTRL_ASSERT( NS(CObjFlatBuffer_section_end_addr)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_INDICES, slot_size ) >=
                ( index_begin_addr + storage_index_size ) );

        if( init_space_with_zeros )
        {
            SIXTRL_STATIC_VAR _raw_t SIXTRL_CONSTEXPR_OR_CONST
                ZBYTE = ( _raw_t )0u;

            _ptr_raw_t dest = ( _ptr_raw_t )( uintptr_t )index_begin_addr;
            SIXTRACKLIB_SET_VALUES( _raw_t, dest, storage_index_size, ZBYTE );
        }

        ptr_stored_index = ( _ptr_index_t )( uintptr_t )index_begin_addr;

        NS(CObjIndex_preset)( ptr_stored_index );
        NS(CObjIndex_set_type_id)( ptr_stored_index, type_id );
        NS(CObjIndex_set_begin_addr)( ptr_stored_index, stored_obj_begin_addr);
        NS(CObjIndex_set_size)( ptr_stored_index, num_bytes_stored_in_slots );
    }

    return ptr_stored_index;
}

SIXTRL_INLINE NS(cobj_status_t)
NS(_CObjFlatBuffer_add_copy_of_object_update_buffer_params)(
    NS(ptr_raw_buffer_data_t) SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const slot_size,
    NS(cobj_size_t) const requ_num_slots,
    NS(cobj_size_t) const requ_num_objects,
    NS(cobj_size_t) const requ_num_pointers ) SIXTRL_NOEXCEPT
{
    typedef NS(cobj_size_t) _size_t;
    NS(cobj_status_t) status = SIXTRL_COBJECTS_STATUS_GENERAL_FAILURE;

    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > ( _size_t )0u ) &&
        ( !NS(CObjFlatBuffer_needs_remapping)( buffer, slot_size ) ) &&
        ( NS(CObjFlatBuffer_max_num_slots)( buffer, slot_size ) >=
          requ_num_slots ) &&
        ( NS(CObjFlatBuffer_max_num_objects)( buffer, slot_size ) >=
          requ_num_objects ) &&
        ( NS(CObjFlatBuffer_max_num_pointers)( buffer, slot_size ) >=
          requ_num_pointers ) )
    {
        _size_t const cur_num_slots =
            NS(CObjFlatBuffer_num_slots)( buffer, slot_size );

        _size_t const cur_num_objs =
            NS(CObjFlatBuffer_num_objects)( buffer, slot_size );

        _size_t const cur_num_ptrs =
            NS(CObjFlatBuffer_num_pointers)( buffer, slot_size );

        status = NS(CObjFlatBuffer_set_section_num_entities)( buffer,
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, requ_num_slots, slot_size );

        if( status == SIXTRL_COBJECTS_STATUS_SUCCESS )
        {
            status = NS(CObjFlatBuffer_set_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_INDICES, requ_num_objects,
                    slot_size );
        }

        if( status == SIXTRL_COBJECTS_STATUS_SUCCESS )
        {
            status = NS(CObjFlatBuffer_set_section_num_entities)( buffer,
                SIXTRL_CBUFFER_SECTION_ID_POINTERS, requ_num_pointers,
                    slot_size );
        }

        if( status != SIXTRL_COBJECTS_STATUS_SUCCESS )
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

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_COBJECTS_FLAT_BUFFER_C99_H__ */
