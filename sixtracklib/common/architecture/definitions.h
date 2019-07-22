#ifndef SIXTRACKLIB_COMMON_ARCHITECTURE_DEFINITIONS_C99_H__
#define SIXTRACKLIB_COMMON_ARCHITECTURE_DEFINITIONS_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

typedef SIXTRL_UINT64_T             NS(arch_id_t);
typedef SIXTRL_UINT64_T             NS(arch_size_t);
typedef SIXTRL_UINT64_T             NS(arch_debugging_t);
typedef SIXTRL_UINT8_T              NS(arch_init_flags_t);
typedef SIXTRL_INT32_T              NS(arch_status_t);

/* ------------------------------------------------------------------------ */
/* Predefined  architecture type id's: limit them to 0x0000 - 0x01FF */
/* For userdefined type id's, the range 0x0200 - 0x03FF is reserved */

#if !defined( SIXTRL_ARCHITECTURE_ID_BITMASK )
    #define SIXTRL_ARCHITECTURE_ID_BITMASK 0x000003FF
#endif /* !defined( SIXTRL_ARCHITECTURE_ID_BITMASK) */

#if !defined( SIXTRL_ARCHITECTURE_ID_OFFSET )
    #define SIXTRL_ARCHITECTURE_ID_OFFSET 0
#endif /* !defined( SIXTRL_ARCHITECTURE_ID_OFFSET) */

/* Then reserve 8 bits to encode up to 256 variants for any specific
 * type_id */

#if !defined( SIXTRL_ARCHITECTURE_ID_VARIANT_BITMASK )
    #define SIXTRL_ARCHITECTURE_ID_VARIANT_BITMASK 0x000FF000
#endif /* !defined( SIXTRL_ARCHITECTURE_ID_VARIANT_BITMASK ) */

#if !defined( SIXTRL_ARCHITECTURE_ID_VARIANT_OFFSET )
    #define SIXTRL_ARCHITECTURE_ID_VARIANT_OFFSET 10
#endif /* !defined( SIXTRL_ARCHITECTURE_ID_VARIANT_OFFSET ) */

/* ------------------------------------------------------------------------ */

#if !defined( SIXTRL_ARCHITECTURE_MAX_STR_LENGTH )
    #define SIXTRL_ARCHITECTURE_MAX_STR_LENGTH 16
#endif /* !defined( SIXTRL_ARCHITECTURE_MAX_STR_LENGTH ) */

#if !defined( SIXTRL_ARCHITECTURE_ILLEGAL)
    #define SIXTRL_ARCHITECTURE_ILLEGAL 0x000003FF
#endif /* !defined( SIXTRL_ARCHITECTURE_ILLEGAL) */

#if !defined( SIXTRL_ARCHITECTURE_NONE)
    #define SIXTRL_ARCHITECTURE_NONE 0x00000000
#endif /* !defined( SIXTRL_ARCHITECTURE_NONE) */

#if !defined( SIXTRL_ARCHITECTURE_CPU)
    #define SIXTRL_ARCHITECTURE_CPU 0x00000001
#endif /* !defined( SIXTRL_ARCHITECTURE_CPU) */

#if !defined(SIXTRL_ARCHITECTURE_CPU_STR)
    #define SIXTRL_ARCHITECTURE_CPU_STR "cpu"
#endif /* !defined(SIXTRL_ARCHITECTURE_CPU_STR) */

#if !defined( SIXTRL_ARCHITECTURE_OPENCL)
    #define SIXTRL_ARCHITECTURE_OPENCL 0x00000002
#endif /* !defined( SIXTRL_ARCHITECTURE_OPENCL) */

#if !defined(SIXTRL_ARCHITECTURE_OPENCL_STR)
    #define SIXTRL_ARCHITECTURE_OPENCL_STR "opencl"
#endif /* !defined(SIXTRL_ARCHITECTURE_OPENCL_STR) */

#if !defined( SIXTRL_ARCHITECTURE_CUDA)
    #define SIXTRL_ARCHITECTURE_CUDA 0x00000003
#endif /* !defined( SIXTRL_ARCHITECTURE_CUDA) */

#if !defined(SIXTRL_ARCHITECTURE_CUDA_STR)
    #define SIXTRL_ARCHITECTURE_CUDA_STR "cuda"
#endif /* !defined(SIXTRL_ARCHITECTURE_CUDA_STR) */

/* ------------------------------------------------------------------------- */

#if !defined(SIXTRL_ARCH_STATUS_SUCCESS)
    #define SIXTRL_ARCH_STATUS_SUCCESS 0
#endif /* !defined(SIXTRL_ARCH_STATUS_SUCCESS) */

#if !defined(SIXTRL_ARCH_STATUS_GENERAL_FAILURE)
    #define SIXTRL_ARCH_STATUS_GENERAL_FAILURE -1
#endif /* !defined(SIXTRL_ARCH_STATUS_GENERAL_FAILURE) */

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_ARCH_INIT_STATE_NONE )
    #define SIXTRL_ARCH_INIT_STATE_NONE 0
#endif /* !defined( SIXTRL_ARCH_INIT_STATE_NONE ) */

#if !defined( SIXTRL_ARCH_INIT_STATE_ENABLED )
    #define SIXTRL_ARCH_INIT_STATE_ENABLED 0x01
#endif /* !defined( SIXTRL_ARCH_INIT_STATE_ENABLED ) */

#if !defined( SIXTRL_ARCH_INIT_STATE_ACTIVATED )
    #define SIXTRL_ARCH_INIT_STATE_ACTIVATED 0x02
#endif /* !defined( SIXTRL_ARCH_INIT_STATE_ACTIVATED ) */

#if !defined( SIXTRL_ARCH_INIT_STATE_AVAILABLE )
    #define SIXTRL_ARCH_INIT_STATE_AVAILABLE 0x03
#endif /* !defined( SIXTRL_ARCH_INIT_STATE_ACTIVATED ) */

#if !defined( SIXTRL_ARCH_INIT_STATE_SHUTDOWN )
    #define SIXTRL_ARCH_INIT_STATE_SHUTDOWN 0x04
#endif /* !defined( SIXTRL_ARCH_INIT_STATE_SHUTDOWN ) */

#if !defined( SIXTRL_ARCH_INIT_STATE_ERROR )
    #define SIXTRL_ARCH_INIT_STATE_ERROR 0xff
#endif /* !defined( SIXTRL_ARCH_INIT_STATE_ERROR ) */

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_ID_BITMASK) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_ID_BITMASK;

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_ID_OFFSET) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_ID_OFFSET;

SIXTRL_STATIC_VAR NS(arch_id_t) const
    NS(ARCHITECTURE_ID_VARIANT_BITMASK) = ( NS(arch_id_t)
        )SIXTRL_ARCHITECTURE_ID_VARIANT_BITMASK;

SIXTRL_STATIC_VAR NS(arch_id_t) const
    NS(ARCHITECTURE_ID_VARIANT_OFFSET) = ( NS(arch_id_t)
        )SIXTRL_ARCHITECTURE_ID_VARIANT_OFFSET;

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_ILLEGAL) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_ILLEGAL;

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_NONE) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_NONE;

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_CPU) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_CPU;

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_OPENCL) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_OPENCL;

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_CUDA) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_CUDA;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR NS(arch_status_t) const NS(ARCH_STATUS_SUCCESS) =
    ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;

SIXTRL_STATIC_VAR NS(arch_status_t) const NS(ARCH_STATUS_GENERAL_FAILURE) =
    ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

#endif /* !defined( _GPUCODE ) */

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR NS(arch_init_flags_t) const NS(ARCH_INIT_STATE_NONE) =
    ( NS(arch_init_flags_t) )SIXTRL_ARCH_INIT_STATE_NONE;

SIXTRL_STATIC_VAR NS(arch_init_flags_t) const NS(ARCH_INIT_STATE_ENABLED) =
    ( NS(arch_init_flags_t) )SIXTRL_ARCH_INIT_STATE_ENABLED;

SIXTRL_STATIC_VAR NS(arch_init_flags_t) const NS(ARCH_INIT_STATE_ACTIVATED) =
    ( NS(arch_init_flags_t) )SIXTRL_ARCH_INIT_STATE_ACTIVATED;

SIXTRL_STATIC_VAR NS(arch_init_flags_t) const NS(ARCH_INIT_STATE_AVAILABLE) =
    ( NS(arch_init_flags_t) )SIXTRL_ARCH_INIT_STATE_AVAILABLE;

SIXTRL_STATIC_VAR NS(arch_init_flags_t) const NS(ARCH_INIT_STATE_SHUTDOWN) =
    ( NS(arch_init_flags_t) )SIXTRL_ARCH_INIT_STATE_SHUTDOWN;

SIXTRL_STATIC_VAR NS(arch_init_flags_t) const NS(ARCH_INIT_STATE_ERROR) =
    ( NS(arch_init_flags_t) )SIXTRL_ARCH_INIT_STATE_ERROR;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}

namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(arch_status_t)          arch_status_t;
    typedef ::NS(arch_init_flags_t)      arch_init_flags_t;
    typedef ::NS(arch_id_t)              arch_id_t;
    typedef ::NS(arch_size_t)            arch_size_t;
    typedef ::NS(arch_debugging_t)       arch_debugging_t;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_ID_BITMASK = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_ID_BITMASK );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_ID_OFFSET = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_ID_OFFSET );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_ID_VARIANT_BITMASK = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_ID_VARIANT_BITMASK );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_ID_VARIANT_OFFSET = static_cast< arch_id_t
            >( SIXTRL_ARCHITECTURE_ID_VARIANT_OFFSET );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_ILLEGAL = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_ILLEGAL );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_NONE = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_NONE );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_CPU = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_CPU );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_OPENCL = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_OPENCL );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_CUDA = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_CUDA );

    /* --------------------------------------------------------------------- */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_status_t
        ARCH_STATUS_SUCCESS = static_cast< arch_status_t >(
            SIXTRL_ARCH_STATUS_SUCCESS );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_status_t
        ARCH_STATUS_GENERAL_FAILURE = static_cast< arch_status_t >(
            SIXTRL_ARCH_STATUS_GENERAL_FAILURE );

    /* --------------------------------------------------------------------- */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_init_flags_t
        ARCH_INIT_STATE_NONE = static_cast< arch_init_flags_t >(
            SIXTRL_ARCH_INIT_STATE_NONE );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_init_flags_t
        ARCH_INIT_STATE_ENABLED = static_cast< arch_init_flags_t >(
            SIXTRL_ARCH_INIT_STATE_ENABLED );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_init_flags_t
        ARCH_INIT_STATE_ACTIVATED = static_cast< arch_init_flags_t >(
            SIXTRL_ARCH_INIT_STATE_ACTIVATED );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_init_flags_t
        ARCH_INIT_STATE_AVAILABLE = static_cast< arch_init_flags_t >(
            SIXTRL_ARCH_INIT_STATE_ENABLED );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_init_flags_t
        ARCH_INIT_STATE_SHUTDOWN = static_cast< arch_init_flags_t >(
            SIXTRL_ARCH_INIT_STATE_SHUTDOWN );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_init_flags_t
        ARCH_INIT_STATE_ERROR = static_cast< arch_init_flags_t >(
            SIXTRL_ARCH_INIT_STATE_ERROR );
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_ARCHITECTURE_DEFINITIONS_C99_H__ */

/* end: sixtracklib/common/architecture/definitions.h */
