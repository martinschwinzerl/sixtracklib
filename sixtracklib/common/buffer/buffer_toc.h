#ifndef SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_C99_H__
#define SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/buffer/buffer_toc.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <map>
        #include <vector>
        #include <unordered_map>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #if defined( __cplusplus )
        #include "sixtracklib/common/buffer.hpp"
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE )

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(BufferTableOfContents)*
NS(BufferTableOfContents_create)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(BufferTableOfContents)*
NS(BufferTableOfContents_new)( const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BufferTableOfContents_delete)(
    NS(BufferTableOfContents)* SIXTRL_RESTRICT buffer_toc );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BufferTableOfContents_swap)(
    NS(BufferTableOfContents)* SIXTRL_RESTRICT lhs,
    NS(BufferTableOfContents)* SIXTRL_RESTRICT rhs );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(BufferTableOfContents_get_total_num_entries)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(BufferTableOfContents_get_num_entry_types)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(object_type_id_t) const*
NS(BufferTableOfContents_get_entry_types_begin)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(object_type_id_t) const*
NS(BufferTableOfContents_get_entry_types_end)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(BufferTableOfContents_has_entries)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(BufferTableOfContents_get_num_entries)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) const*
NS(BufferTableOfContents_get_entry_indices_begin)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) const*
NS(BufferTableOfContents_get_entry_indices_end)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(BufferTableOfContents_get_entry_type_index)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(arch_size_t) const nn );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(object_type_id_t)
NS(BufferTableOfContents_get_entry_type_id)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(arch_size_t) const nn );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_addr_t)
NS(BufferTableOfContents_get_entry_offset)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(arch_size_t) const nn );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(BufferTableOfContents_get_entry_size)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(arch_size_t) const nn );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(BufferTableOfContents_get_entry_num_dataptrs)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(arch_size_t) const nn );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(BufferTableOfContents_get_entry_index_for_type)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id, NS(arch_size_t) const nn );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_addr_t)
NS(BufferTableOfContents_get_entry_offset_for_type)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id, NS(arch_size_t) const nn );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(BufferTableOfContents_get_entry_size_for_type)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id, NS(arch_size_t) const nn );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(BufferTableOfContents_get_entry_num_dataptrs_for_type)(
    const NS(BufferTableOfContents) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id, NS(arch_size_t) const nn );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BufferTableOfContents_clear)(
    NS(BufferTableOfContents)* SIXTRL_RESTRICT buffer_toc );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(BufferTableOfContents_reset)(
   NS(BufferTableOfContents)* SIXTRL_RESTRICT buffer_toc,
   NS(Buffer)* SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(BufferTableOfContents_append)(
    NS(BufferTableOfContents)* SIXTRL_RESTRICT buffer_toc,
    NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(arch_size_t) const num_entries_to_append );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(BufferTableOfContents_has_same_layout)(
    NS(BufferTableOfContents)* SIXTRL_RESTRICT buffer_toc,
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_C99_H__ */

/* end: sixtracklib/common/buffer/buffer_toc.h */
