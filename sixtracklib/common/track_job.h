#ifndef SIXTRL_SIXTRACKLIB_COMMON_TRACK_JOB_H__
#define SIXTRL_SIXTRACKLIB_COMMON_TRACK_JOB_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <cstddef>
        #include <cstdint>
        #include <cstdlib>
        #include <cstring>
        #include <iostream>
        #include <memory>
        #include <regex>
        #include <string>
        #include <utility>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/internal/track_job_base.h"

    #if defined( __cplusplus )
        #include "sixtracklib/common/buffer.hpp"
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

struct NS(ElemByElemConfig);

#if !defined( _GPUCODE )

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_HOST_FN SIXTRL_STATIC std::string TrackJob_extract_device_id_str(
        std::string const& SIXTRL_RESTRICT_REF config_str );

    SIXTRL_HOST_FN SIXTRL_STATIC std::string TrackJob_extract_device_id_str(
        const char *const SIXTRL_RESTRICT config_str );

    SIXTRL_HOST_FN SIXTRL_STATIC std::string TrackJob_sanitize_arch_str(
        std::string const& SIXTRL_RESTRICT_REF arch_str );

    SIXTRL_HOST_FN SIXTRL_STATIC std::string TrackJob_sanitize_arch_str(
        const char *const SIXTRL_RESTRICT arch_str );

    SIXTRL_HOST_FN TrackJobBase* TrackJob_create(
        const char *const SIXTRL_RESTRICT arch_str,
        const char *const SIXTRL_RESTRICT config_str );

    SIXTRL_HOST_FN TrackJobBase* TrackJob_create(
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        std::string const& SIXTRL_RESTRICT_REF config_str );

    SIXTRL_HOST_FN TrackJobBase* TrackJob_new(
        const char *const SIXTRL_RESTRICT arch_str,
        ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
        ::NS(Buffer)* SIXTRL_RESTRICT beam_elemements_buffer,
        const char *const SIXTRL_RESTRICT config_str );

    SIXTRL_HOST_FN TrackJobBase* TrackJob_new(
        const char *const SIXTRL_RESTRICT arch_str,
        ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
        ::NS(Buffer)* SIXTRL_RESTRICT beam_elemements_buffer,
        ::NS(Buffer)* SIXTRL_RESTRICT output_buffer,
        ::NS(buffer_size_t) const dump_elem_by_elem_turns,
        const char *const SIXTRL_RESTRICT config_str );

    SIXTRL_HOST_FN TrackJobBase* TrackJob_new(
        const char *const SIXTRL_RESTRICT arch_str,
        ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
        ::NS(buffer_size_t) const num_particle_sets,
        ::NS(buffer_size_t) const* SIXTRL_RESTRICT particle_set_indices_begin,
        ::NS(Buffer)* SIXTRL_RESTRICT beam_elemements_buffer,
        ::NS(Buffer)* SIXTRL_RESTRICT output_buffer,
        ::NS(buffer_size_t) const dump_elem_by_elem_turns,
        const char *const SIXTRL_RESTRICT config_str );

    SIXTRL_HOST_FN TrackJobBase* TrackJob_new(
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        Buffer& SIXTRL_RESTRICT_REF particles_buffer,
        Buffer& SIXTRL_RESTRICT_REF beam_elemements_buffer,
        std::string const& SIXTRL_RESTRICT_REF config_str );

    SIXTRL_HOST_FN TrackJobBase* TrackJob_new(
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        Buffer& SIXTRL_RESTRICT_REF particles_buffer,
        Buffer& SIXTRL_RESTRICT_REF beam_elemements_buffer,
        Buffer* SIXTRL_RESTRICT output_buffer,
        Buffer::size_type const dump_elem_by_elem_turns,
        std::string const& SIXTRL_RESTRICT_REF config_str );

    SIXTRL_HOST_FN TrackJobBase* TrackJob_new(
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        Buffer& SIXTRL_RESTRICT_REF particles_buffer,
        Buffer::size_type const num_particle_sets,
        Buffer::size_type const* SIXTRL_RESTRICT particle_set_indices_begin,
        Buffer& SIXTRL_RESTRICT_REF beam_elemements_buffer,
        Buffer* SIXTRL_RESTRICT output_buffer,
        Buffer::size_type const dump_elem_by_elem_turns,
        std::string const& SIXTRL_RESTRICT_REF config_str );

    template< typename Iter >
    SIXTRL_HOST_FN TrackJobBase* TrackJob_new(
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        Buffer& SIXTRL_RESTRICT_REF particles_buffer,
        Iter particle_set_indices_begin, Iter particle_set_indices_end,
        Buffer& SIXTRL_RESTRICT_REF beam_elemements_buffer,
        Buffer* SIXTRL_RESTRICT output_buffer,
        Buffer::size_type const dump_elem_by_elem_turns,
        std::string const& SIXTRL_RESTRICT_REF config_str );
}

extern "C" {

#endif /* defined( __cplusplus ) */

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(TrackJob_extract_device_id_str)(
        const char *const SIXTRL_RESTRICT config_str,
        char* SIXTRL_RESTRICT device_id_str,
        NS(buffer_size_t) const max_device_id_str_len );

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(TrackJob_sanitize_arch_str_inplace)(
        char* SIXTRL_RESTRICT arch_str,
        NS(buffer_size_t) const max_arch_str_len );

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(TrackJob_sanitize_arch_str)(
        const char *const SIXTRL_RESTRICT arch_str,
        char* SIXTRL_RESTRICT sanitized_arch_str,
        NS(buffer_size_t) const max_arch_str_len );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(TrackJobBase)* NS(TrackJob_create)(
    const char *const SIXTRL_RESTRICT arch,
    const char *const SIXTRL_RESTRICT config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(TrackJobBase)* NS(TrackJob_new)(
    const char *const SIXTRL_RESTRICT arch,
    NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    const char *const SIXTRL_RESTRICT config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(TrackJobBase)* NS(TrackJob_new_with_output)(
    const char *const SIXTRL_RESTRICT arch,
    NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    NS(Buffer)* SIXTRL_RESTRICT output_buffer,
    NS(buffer_size_t) const dump_elem_by_elem_turns,
    const char *const SIXTRL_RESTRICT config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(TrackJobBase)* NS(TrackJob_new_detailed)(
    const char *const SIXTRL_RESTRICT arch,
    NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    NS(buffer_size_t) const num_particle_sets,
    NS(buffer_size_t) const* SIXTRL_RESTRICT particle_set_indices_begin,
    NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    NS(Buffer)* SIXTRL_RESTRICT output_buffer,
    NS(buffer_size_t) const dump_elem_by_elem_turns,
    const char *const SIXTRL_RESTRICT config_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_delete)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(track_status_t) NS(TrackJob_track_until)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(buffer_size_t) const until_turn );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(track_status_t)
NS(TrackJob_track_elem_by_elem)( NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(buffer_size_t) const until_turn );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(track_status_t)
NS(TrackJob_track_line)( NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(buffer_size_t) const beam_elem_begin_index,
    NS(buffer_size_t) const beam_elem_end_index,
    bool const finish_turn );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_collect)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_collect_detailed)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(track_job_collect_flag_t) const flags );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_collect_particles)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_collect_beam_elements)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_collect_output)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_enable_collect_particles)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_disable_collect_particles)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_is_collecting_particles)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_enable_collect_beam_elements)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_disable_collect_beam_elements)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_is_collecting_beam_elements)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_enable_collect_output)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_disable_collect_output)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_is_collecting_output)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(track_job_collect_flag_t)
NS(TrackJob_get_collect_flags)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_set_collect_flags)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(track_job_collect_flag_t) const flag );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_requires_collecting)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );


SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_push)(
    NS(TrackJobBase)* SIXTRL_RESTRICT track_job,
    NS(track_job_push_flag_t) const flags );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_push_particles)(
    NS(TrackJobBase)* SIXTRL_RESTRICT track_job );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_push_beam_elements)(
    NS(TrackJobBase)* SIXTRL_RESTRICT track_job );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_push_output)(
    NS(TrackJobBase)* SIXTRL_RESTRICT track_job );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_can_fetch_particles_addr)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT track_job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_particles_addr)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT track_job );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(TrackJob_clear)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_reset)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    NS(Buffer)* SIXTRL_RESTRICT output_buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_reset_particle_set)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    NS(buffer_size_t) const particle_set_index,
    NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    NS(Buffer)* SIXTRL_RESTRICT output_buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_reset_with_output)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    NS(Buffer)* SIXTRL_RESTRICT output_buffer,
    NS(buffer_size_t) const dump_elem_by_elem_turns );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_reset_detailed)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    NS(buffer_size_t) const num_particle_sets,
    NS(buffer_size_t) const* SIXTRL_RESTRICT particle_set_indices_begin,
    NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    NS(Buffer)* SIXTRL_RESTRICT output_buffer,
    NS(buffer_size_t) const dump_elem_by_elem_turns );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_select_particle_set)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(buffer_size_t) const particle_set_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_assign_output_buffer)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(Buffer)* SIXTRL_RESTRICT ptr_output_buffer );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(track_job_type_t) NS(TrackJob_get_type_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(TrackJob_get_type_str)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_device_id_str)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(TrackJob_get_device_id_str)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_config_str)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(TrackJob_get_config_str)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_get_num_particle_sets)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t) const*
NS(TrackJob_get_particle_set_indices_begin)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t) const*
NS(TrackJob_get_particle_set_indices_end)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_get_particle_set_index)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const n );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t) const*
NS(TrackJob_get_num_particles_in_sets_begin)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t) const*
NS(TrackJob_get_num_particles_in_sets_end)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_get_num_particles_in_set)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const n );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_get_total_num_particles_in_sets)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(particle_index_t)
NS(TrackJob_get_min_particle_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(particle_index_t)
NS(TrackJob_get_max_particle_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(particle_index_t)
NS(TrackJob_get_min_element_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(particle_index_t)
NS(TrackJob_get_max_element_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(particle_index_t)
NS(TrackJob_get_min_initial_turn_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(particle_index_t)
NS(TrackJob_get_max_initial_turn_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer)* NS(TrackJob_get_particles_buffer)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer) const*
NS(TrackJob_get_const_particles_buffer)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer)*
NS(TrackJob_get_beam_elements_buffer)( NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer) const*
NS(TrackJob_get_const_beam_elements_buffer)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_output_buffer)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_owns_output_buffer)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_elem_by_elem_output)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_beam_monitor_output)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_get_beam_monitor_output_buffer_offset)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_get_elem_by_elem_output_buffer_offset)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_get_num_elem_by_elem_turns)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer)* NS(TrackJob_get_output_buffer)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer) const*
NS(TrackJob_get_const_output_buffer)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_config_buffer)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer) const* NS(TrackJob_const_config_buffer)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer)* NS(TrackJob_config_buffer)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_can_fetch_particles_addr)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_particles_addr)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackJob_fetch_particles_addr)( NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackJob_clear_particles_addr)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(buffer_size_t) const particle_set_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackJob_clear_all_particles_addr)( NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN struct NS(ParticlesAddr) const*
NS(TrackJob_particles_addr)( const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const particle_set_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer) const*
NS(TrackJob_particles_addr_buffer)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(AssignAddressItem)*
NS(TrackJob_add_assign_address_item)( NS(TrackJobBase)* SIXTRL_RESTRICT job,
    const NS(AssignAddressItem) *const SIXTRL_RESTRICT_REF assign_item_to_add );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(AssignAddressItem)*
NS(TrackJob_add_assign_address_item_detailed)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(object_type_id_t) const dest_type_id,
    NS(buffer_size_t) const dest_buffer_id,
    NS(buffer_size_t) const dest_elem_index,
    NS(buffer_size_t) const dest_pointer_offset,
    NS(object_type_id_t) const src_type_id,
    NS(buffer_size_t) const src_buffer_id,
    NS(buffer_size_t) const src_elem_index,
    NS(buffer_size_t) const src_pointer_offset );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackJob_remove_assign_address_item)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(AssignAddressItem)* SIXTRL_RESTRICT item_to_remove );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackJob_remove_assign_address_item_by_key_and_index)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    const NS(TrackJobDestSrcBufferIds) *const SIXTRL_RESTRICT_REF key,
    NS(buffer_size_t) const index_of_item_to_remove );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_assign_address_item)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    const NS(AssignAddressItem) *const SIXTRL_RESTRICT_REF assign_item_to_add );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_assign_item_by_index)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const dest_buffer_id,
    NS(buffer_size_t) const src_buffer_id,
    NS(buffer_size_t) const assign_item_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_assign_address_item_detailed)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(object_type_id_t) const dest_type_id,
    NS(buffer_size_t) const dest_buffer_id,
    NS(buffer_size_t) const dest_elem_index,
    NS(buffer_size_t) const dest_pointer_offset,
    NS(object_type_id_t) const src_type_id,
    NS(buffer_size_t) const src_buffer_id,
    NS(buffer_size_t) const src_elem_index,
    NS(buffer_size_t) const src_pointer_offset );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_index_of_assign_address_item_detailed)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(object_type_id_t) const dest_type_id,
    NS(buffer_size_t) const dest_buffer_id,
    NS(buffer_size_t) const dest_elem_index,
    NS(buffer_size_t) const dest_pointer_offset,
    NS(object_type_id_t) const src_type_id,
    NS(buffer_size_t) const src_buffer_id,
    NS(buffer_size_t) const src_elem_index,
    NS(buffer_size_t) const src_pointer_offset );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_index_of_assign_address_item)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    const NS(AssignAddressItem) *const  SIXTRL_RESTRICT assign_item_to_add );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_assign_items)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const dest_buffer_id,
    NS(buffer_size_t) const src_buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t) NS(TrackJob_num_assign_items)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const dest_buffer_id,
    NS(buffer_size_t) const src_buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_total_num_assign_items)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(AssignAddressItem) const*
NS(TrackJob_ptr_assign_address_item)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    const NS(AssignAddressItem) *const SIXTRL_RESTRICT assign_address_item );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(AssignAddressItem) const*
NS(TrackJob_ptr_assign_address_item_detailed)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(object_type_id_t) const dest_type_id,
    NS(buffer_size_t) const dest_buffer_id,
    NS(buffer_size_t) const dest_elem_index,
    NS(buffer_size_t) const dest_pointer_offset,
    NS(object_type_id_t) const src_type_id,
    NS(buffer_size_t) const src_buffer_id,
    NS(buffer_size_t) const src_elem_index,
    NS(buffer_size_t) const src_pointer_offset );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(AssignAddressItem) const*
NS(TrackJob_ptr_assign_address_item_by_index)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const dest_buffer_id,
    NS(buffer_size_t) const src_buffer_id,
    NS(buffer_size_t) const assign_address_item_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_num_distinct_available_assign_address_items_dest_src_pairs)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_available_assign_address_items_dest_src_pairs)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const max_num_pairs,
    NS(TrackJobDestSrcBufferIds)* pairs_begin );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer)* NS(TrackJob_buffer_by_buffer_id)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job, NS(buffer_size_t) const buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer) const*
NS(TrackJob_const_buffer_by_buffer_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_is_buffer_by_buffer_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_is_raw_memory_by_buffer_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const*
NS(TrackJob_assign_items_begin)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const dest_buffer_id,
    NS(buffer_size_t) const src_buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const*
NS(TrackJob_assign_items_end)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const dest_buffer_id,
    NS(buffer_size_t) const src_buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(TrackJobDestSrcBufferIds) const*
NS(TrackJob_assign_item_dest_src_begin)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(TrackJobDestSrcBufferIds) const*
NS(TrackJob_assign_item_dest_src_end)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackJob_commit_address_assignments)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackJob_assign_all_addresses)( NS(TrackJobBase)* SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackJob_assign_addresses)( NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(buffer_size_t) const dest_buffer_id,
    NS(buffer_size_t) const src_buffer_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(AssignAddressItem)*
NS(TrackJob_add_assign_address_item)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    const NS(AssignAddressItem) *const SIXTRL_RESTRICT assign_item_to_add );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(AssignAddressItem)*
NS(TrackJob_add_assign_address_item_detail)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(object_type_id_t) const dest_type_id,
    NS(arch_size_t) const dest_buffer_id, NS(arch_size_t) const dest_elem_index,
    NS(arch_size_t) const dest_pointer_offset,
    NS(object_type_id_t) const src_type_id,
    NS(arch_size_t) const src_buffer_id, NS(arch_size_t) const src_elem_index,
    NS(arch_size_t) const src_pointer_offset );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_assign_items)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(arch_size_t) const dest_buffer_id, NS(arch_size_t) const src_buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(TrackJob_num_assign_items)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(arch_size_t) const dest_buffer_id, NS(arch_size_t) const src_buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer)* NS(TrackJob_buffer_by_buffer_id)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job, NS(arch_size_t) const buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer) const*
NS(TrackJob_const_buffer_by_buffer_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(arch_size_t) const buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(TrackJob_num_distinct_assign_items_dest_src_pairs)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN
NS(arch_size_t) NS(TrackJob_assign_items_dest_src_pairs)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(arch_size_t) const max_num_pairs,
    NS(AssignAddressItemDestSrcPair)* pairs_begin );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(AssignAddressItem) const*
NS(TrackJob_assign_items_dest_src_begin)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(arch_size_t) const dest_buffer_id, NS(arch_size_t) const src_buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(AssignAddressItem) const*
NS(TrackJob_assign_items_dest_src_end)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(arch_size_t) const dest_buffer_id, NS(arch_size_t) const src_buffer_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(TrackJob_stored_buffers_capacity)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackJob_reserve_stored_buffers_capacity)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job, NS(arch_size_t) const capacity );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_stored_buffers)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(TrackJob_num_stored_buffers)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(TrackJob_min_stored_buffer_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(TrackJob_max_stored_buffer_id)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(TrackJob_create_stored_buffer)( NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(buffer_size_t) const buffer_capacity );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(TrackJob_add_stored_buffer)( NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(Buffer)* SIXTRL_RESTRICT buffer, bool const take_ownership,
    bool const delete_ptr_after_move );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_owns_stored_buffer)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(arch_size_t) const buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackJob_remove_stored_buffer)( NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(arch_size_t) const buffer_index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer)* NS(TrackJob_stored_buffer)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(arch_size_t) const buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer) const*
NS(TrackJob_const_stored_buffer)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(arch_size_t) const buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(TrackJob_push_stored_buffer)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job, NS(arch_size_t) const buffer_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(TrackJob_collect_stored_buffer)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job, NS(arch_size_t) const buffer_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_beam_monitors)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_get_num_beam_monitors)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t) const*
NS(TrackJob_get_beam_monitor_indices_begin)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t) const*
NS(TrackJob_get_beam_monitor_indices_end)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(TrackJob_get_beam_monitor_index)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const n );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_has_elem_by_elem_config)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ElemByElemConfig) const*
NS(TrackJob_get_elem_by_elem_config)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(TrackJob_is_elem_by_elem_config_rolling)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(TrackJob_get_default_elem_by_elem_config_rolling_flag)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TrackJob_set_default_elem_by_elem_config_rolling_flag)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job,
    bool const is_rolling_flag );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(elem_by_elem_order_t)
NS(TrackJob_get_elem_by_elem_config_order)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(elem_by_elem_order_t)
NS(TrackJob_get_default_elem_by_elem_config_order)(
    const NS(TrackJobBase) *const SIXTRL_RESTRICT job );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(TrackJob_set_default_elem_by_elem_config_order)(
    NS(TrackJobBase)* SIXTRL_RESTRICT job,
    NS(elem_by_elem_order_t) const order );


#if defined( __cplusplus )
} /* extern "C" { */
#endif /* defined( __cplusplus ) */

/* ************************************************************************* */
/* *****              Implementation of Inline Functions               ***** */
/* ************************************************************************* */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE SIXTRL_HOST_FN std::string TrackJob_extract_device_id_str(
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        return SIXTRL_CXX_NAMESPACE::TrackJob_extract_device_id_str(
            config_str.c_str() );
    }

    SIXTRL_INLINE SIXTRL_HOST_FN std::string TrackJob_extract_device_id_str(
        const char *const SIXTRL_RESTRICT config_str )
    {
        if( ( config_str != nullptr ) &&
            ( std::strlen( config_str ) > std::size_t{ 0 } ) )
        {
            /*
            std::regex re(
                        "device_id_str[:blank:]*=[:blank:]*"
                              "([:digit:]+.[:digit:]+)[A-Za-z0-9_\\-#=:;., \t]*|"
                        "^[A-Za-z0-9_\\-#=;.:, \t]*([:digit:]+.[:digit:]+);|"
                        "([:digit:]+.[:digit:]+)" );*/

            std::regex re( "\\s*([0-9]+\\.[0-9]+)[\\sA-Za-z0-9#\\;]*" );
            std::cmatch matches;

            std::regex_match( config_str, matches, re );

            if( ( matches.ready() ) && ( !matches.empty() ) )
            {
                return std::string{ matches[ matches.size() - 1 ] };
            }
        }

        return std::string{ "" };
    }

    SIXTRL_INLINE std::string TrackJob_sanitize_arch_str(
        std::string const& SIXTRL_RESTRICT_REF arch_str )
    {
        return SIXTRL_CXX_NAMESPACE::TrackJob_sanitize_arch_str(
            arch_str.c_str() );
    }

    SIXTRL_INLINE SIXTRL_HOST_FN std::string TrackJob_sanitize_arch_str(
        const char *const SIXTRL_RESTRICT arch_str )
    {
        std::size_t const arch_str_len = ( arch_str != nullptr )
            ? std::strlen( arch_str ) : std::size_t{ 0 };

        std::string result_str;

        if( arch_str_len > std::size_t{ 0 } )
        {
            char const* it  = arch_str;
            char const* end = arch_str;
            std::advance( end, arch_str_len );

            result_str.resize( arch_str_len );
            std::transform( it, end, result_str.begin(), ::tolower );

        }

        return result_str;
    }

    template< typename Iter >
    SIXTRL_INLINE SIXTRL_HOST_FN TrackJobBase* TrackJob_new(
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        Buffer& SIXTRL_RESTRICT_REF particles_buffer,
        Iter particle_set_indices_begin, Iter particle_set_indices_end,
        Buffer& SIXTRL_RESTRICT_REF beam_elemements_buffer,
        Buffer* SIXTRL_RESTRICT output_buffer,
        Buffer::size_type const dump_elem_by_elem_turns,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        TrackJobBase* ptr_job = TrackJob_create( arch_str, config_str );

        if( ( ptr_job != nullptr ) && ( !ptr_job->reset( particles_buffer,
                particle_set_indices_begin, particle_set_indices_end,
                    beam_elemements_buffer, output_buffer,
                        dump_elem_by_elem_turns ) ) )
        {
            delete ptr_job;
            ptr_job = nullptr;
        }

        return ptr_job;
    }
}

#endif /* defined( __cplusplus ) */

#endif /* !defined( _GPUCODE ) */

#endif /* SIXTRL_SIXTRACKLIB_COMMON_TRACK_JOB_H__ */

/* end: sixtracklib/common/track_job.h */
