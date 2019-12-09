#ifndef SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_C99_H__
#define SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/buffer/buffer_toc.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
extern "C" {
#endif /* defined( __cplusplus ) */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(BufferToc)* NS(BufferToc_new)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BufferToc_delete)(
    NS(BufferToc)* SIXTRL_RESTRICT buffer );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(BufferToc_has_types)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t) NS(BufferToc_num_types)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(object_type_id_t) const*
NS(BufferToc_types_begin)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(object_type_id_t) const*
NS(BufferToc_types_end)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(BufferToc_has_type_elements)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t) NS(BufferToc_num_type_elements)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t) const*
NS(BufferToc_type_elements_indices_begin)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t) const*
NS(BufferToc_type_elements_indices_end)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(BufferToc_type_element_index)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id, NS(buffer_size_t) const id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_size_t)
NS(BufferToc_type_element_index_no_check)(
    const NS(BufferToc) *const SIXTRL_RESTRICT buffer_toc,
    NS(object_type_id_t) const type_id, NS(buffer_size_t) const id );

/* ----------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(BufferToc_reset)(
    NS(BufferToc)* SIXTRL_RESTRICT buffer_toc,
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BufferToc_clear)( void );

/* ----------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(BufferToc_are_equal)(
    const NS(BufferToc) *const SIXTRL_RESTRICT lhs,
    const NS(BufferToc) *const SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(BufferToc_are_not_equal)(
    const NS(BufferToc) *const SIXTRL_RESTRICT lhs,
    const NS(BufferToc) *const SIXTRL_RESTRICT rhs ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */

#endif /* !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_C99_H__ */
