#ifndef SIXTRACKLIB_COMMON_BUFFER_BUFFER_STORE_C99_H__
#define SIXTRACKLIB_COMMON_BUFFER_BUFFER_STORE_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/buffer/buffer_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"

    #if defined( __cplusplus ) && !defined( _GPUCODE )
        #include "sixtracklib/common/buffer.hpp"
    #endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/buffer/buffer_toc.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(BufferStoreBase)*
NS(BufferStoreBase_create_with_buffer)( NS(buffer_size_t) const capacity,
    NS(buffer_store_role_t) const role );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(BufferStoreBase)*
NS(BufferStoreBase_create_with_buffer_detailed)(
    NS(buffer_size_t) const buffer_capacity,
    NS(buffer_store_role_t) const role,
    NS(buffer_flags_t) const buffer_flags );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(BufferStoreBase)* NS(BufferStoreBase_new)(
    NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_store_role_t) const role,
    bool const take_ownership, bool const delete_after_move );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(BufferStoreBase)*
NS(BufferStoreBase_new_as_copy)(
    const NS(BufferStoreBase) *const SIXTRL_RESTRICT orig );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BufferStoreBase_delete)(
    NS(BufferStoreBase)* SIXTRL_RESTRICT store );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(BufferStoreBase_active)(
    const NS(BufferStoreBase) *const SIXTRL_RESTRICT store ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(buffer_store_role_t) NS(BufferStoreBase_role)(
    const NS(BufferStoreBase) *const SIXTRL_RESTRICT store ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(BufferStoreBase_owns_buffer)(
    const NS(BufferStoreBase) *const SIXTRL_RESTRICT store ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer) const* NS(BufferStoreBase_const_buffer)(
    const NS(BufferStoreBase) *const SIXTRL_RESTRICT store ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(Buffer)* NS(BufferStoreBase_buffer)(
    NS(BufferStoreBase)* SIXTRL_RESTRICT store ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BufferStoreBase_clear)(
    NS(BufferStoreBase)* SIXTRL_RESTRICT store ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BufferStoreBase_reset_with_new_buffer)(
    NS(BufferStoreBase)* SIXTRL_RESTRICT store,
    NS(buffer_size_t) const buffer_capacity,
    NS(buffer_store_role_t) const role );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(BufferStoreBase_reset_with_new_buffer_detailed)(
    NS(BufferStoreBase)* SIXTRL_RESTRICT store,
    NS(buffer_size_t) const buffer_capacity,
    NS(buffer_store_role_t) const role,
    NS(buffer_flags_t) const buffer_flags );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BufferStoreBase_reset)(
    NS(BufferStoreBase)* SIXTRL_RESTRICT store,
    NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_store_role_t) const role,
    bool const take_ownership, bool const delete_ptr_after_move );

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BUFFER_BUFFER_STORE_C99_H__ */
