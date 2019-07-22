#ifndef SIXTRACKLIB_ARCHITECTURE_ARCHITECTURES_C99_H__
#define SIXTRACKLIB_ARCHITECTURE_ARCHITECTURES_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/architecture/architecture.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/architecture/definitions.h"
    #include "sixtracklib/common/architecture/arch_data.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Architectures_has_architecture)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Architectures_has_arch_str)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(Architectures_get_arch_str)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_id_t) NS(Architectures_get_arch_id)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures,
    char const* SIXTRL_RESTRICT arch_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ArchData) const*
NS(Architectures_get_ptr_const_arch_data)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ArchData) const*
NS(Architectures_get_ptr_const_arch_data_by_arch_str)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures,
    char const* SIXTRL_RESTRICT arch_str );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t) NS(Architectures_get_num_architectures)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Architectures_has_handle)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Architectures_is_enabled)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Architectures_is_activated)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Architectures_is_available)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Architectures_is_shutdown)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_init_flags_t)
NS(Architectures_get_init_flags)(
    const NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_ARCHITECTURE_ARCHITECTURES_C99_H__ */

/* end: sixtracklib/common/architecture/architecture.h */
