#ifndef SIXTRACKLIB_BASE_ARCHITECTURE_DEFINITIONS_H__
#define SIXTRACKLIB_BASE_ARCHITECTURE_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

/* ------------------------------------------------------------------------- */

typedef SIXTRL_INT64_T  NS(arch_id_t);
typedef SIXTRL_UINT64_T NS(arch_state_flags_t);

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_ARCHITECTURE_NONE )
    #define SIXTRL_ARCHITECTURE_UNDEFINED 0
#endif /* !defined( SIXTRL_ARCHITECTURE_NONE ) */

#if !defined( SIXTRL_ARCHITECTURE_NONE )
    #define SIXTRL_ARCHITECTURE_UNDEFINED_STR ""
#endif /* !defined( SIXTRL_ARCHITECTURE_NONE ) */

#if !defined( SIXTRL_ARCHITECTURE_CPU )
    #define SIXTRL_ARCHITECTURE_CPU 1
#endif /* !defined( SIXTRL_ARCHITECTURE_CPU ) */

#if !defined( SIXTRL_ARCHITECTURE_NONE )
    #define SIXTRL_ARCHITECTURE_CPU_STR "cpu"
#endif /* !defined( SIXTRL_ARCHITECTURE_NONE ) */

#if !defined( SIXTRL_ARCHITECTURE_OPENCL )
    #define SIXTRL_ARCHITECTURE_OPENCL 2
#endif /* !defined( SIXTRL_ARCHITECTURE_OPENCL ) */

#if !defined( SIXTRL_ARCHITECTURE_NONE )
    #define SIXTRL_ARCHITECTURE_OPENCL_STR "opencl"
#endif /* !defined( SIXTRL_ARCHITECTURE_NONE ) */

#if !defined( SIXTRL_ARCHITECTURE_CUDA )
    #define SIXTRL_ARCHITECTURE_CUDA 3
#endif /* !defined( SIXTRL_ARCHITECTURE_CUDA ) */

#if !defined( SIXTRL_ARCHITECTURE_CUDA_STR )
    #define SIXTRL_ARCHITECTURE_CUDA_STR "cuda"
#endif /* !defined( SIXTRL_ARCHITECTURE_CUDA_STR ) */

#if !defined( SIXTRL_ARCHITECTURE_CUDA_NVRTC )
    #define SIXTRL_ARCHITECTURE_CUDA_NVRTC 4
#endif /* !defined( SIXTRL_ARCHITECTURE_CUDA_NVRTC ) */

#if !defined( SIXTRL_ARCHITECTURE_CUDA_NVRTC_STR )
    #define SIXTRL_ARCHITECTURE_CUDA_NVRTC_STR "cuda_nvrtc"
#endif /* !defined( SIXTRL_ARCHITECTURE_CUDA_NVRTC_STR ) */

#if !defined( SIXTRL_ARCHITECTURE_OPENMP )
    #define SIXTRL_ARCHITECTURE_OPENMP 5
#endif /* !defined( SIXTRL_ARCHITECTURE_OPENMP ) */

#if !defined( SIXTRL_ARCHITECTURE_OPENMP_STR )
    #define SIXTRL_ARCHITECTURE_OPENMP_STR "openmp"
#endif /* !defined( SIXTRL_ARCHITECTURE_OPENMP_STR ) */

#if !defined( SIXTRL_ARCHITECTURE_ILLEGAL )
    #define SIXTRL_ARCHITECTURE_ILLEGAL 0xffff
#endif /* !defined( SIXTRL_ARCHITECTURE_ILLEGAL ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( SIXTRL_ARCH_STATE_NONE )
    #define SIXTRL_ARCH_STATE_NONE 0x00
#endif /* !defined( SIXTRL_ARCH_STATE_NONE ) */

#if !defined( SIXTRL_ARCH_STATE_ENABLED )
    #define SIXTRL_ARCH_STATE_ENABLED 0x01
#endif /* !defined( SIXTRL_ARCH_STATE_ENABLED ) */

#if !defined( SIXTRL_ARCH_STATE_ACTIVATED )
    #define SIXTRL_ARCH_STATE_ACTIVATED 0x02
#endif /* !defined( SIXTRL_ARCH_STATE_ACTIVATED ) */

#if !defined( SIXTRL_ARCH_STATE_AVAILABLE )
    #define SIXTRL_ARCH_STATE_AVAILABLE 0x03
#endif /* !defined( SIXTRL_ARCH_STATE_ACTIVATED ) */

#if !defined( SIXTRL_ARCH_STATE_SHUTDOWN )
    #define SIXTRL_ARCH_STATE_SHUTDOWN 0x04
#endif /* !defined( SIXTRL_ARCH_STATE_SHUTDOWN ) */

#if !defined( SIXTRL_ARCH_STATE_ERROR )
    #define SIXTRL_ARCH_STATE_ERROR 0xff
#endif /* !defined( SIXTRL_ARCH_STATE_ERROR ) */

#if !defined( _GPUCODE )
#if defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC_VAR const NS(arch_id_t)
NS(ARCHITECTURE_UNDEFINED) = ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_UNDEFINED;

SIXTRL_STATIC_VAR const NS(arch_id_t)
NS(ARCHITECTURE_CPU) = ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_CPU;

SIXTRL_STATIC_VAR const NS(arch_id_t)
NS(ARCHITECTURE_OPENCL) = ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_OPENCL;

SIXTRL_STATIC_VAR const NS(arch_id_t)
NS(ARCHITECTURE_CUDA) = ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_CUDA;

SIXTRL_STATIC_VAR const NS(arch_id_t)
NS(ARCHITECTURE_CUDA_NVRTC) = ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_CUDA_NVRTC;

SIXTRL_STATIC_VAR const NS(arch_id_t)
NS(ARCHITECTURE_OPENMP) = ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_OPENMP;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR const NS(arch_state_flags_t)
    NS(ARCH_STATE_NONE) = ( NS(arch_state_flags_t) )SIXTRL_ARCH_STATE_NONE;

SIXTRL_STATIC_VAR const NS(arch_state_flags_t)
    NS(ARCH_STATE_ENABLED) = ( NS(arch_state_flags_t)
        )SIXTRL_ARCH_STATE_ENABLED;

SIXTRL_STATIC_VAR const NS(arch_state_flags_t)
    NS(ARCH_STATE_ACTIVATED) = ( NS(arch_state_flags_t)
        )SIXTRL_ARCH_STATE_ACTIVATED;

SIXTRL_STATIC_VAR const NS(arch_state_flags_t)
    NS(ARCH_STATE_AVAILABLE) = ( NS(arch_state_flags_t)
        )SIXTRL_ARCH_STATE_AVAILABLE;

SIXTRL_STATIC_VAR const NS(arch_state_flags_t)
    NS(ARCH_STATE_SHUTDOWN) = ( NS(arch_state_flags_t)
        )SIXTRL_ARCH_STATE_SHUTDOWN;

SIXTRL_STATIC_VAR const NS(arch_state_flags_t)
    NS(ARCH_STATE_ERROR) = ( NS(arch_state_flags_t) )SIXTRL_ARCH_STATE_ERROR;

#if defined( __cplusplus )
}
#endif /* C++ */
#endif /* Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(arch_id_t) arch_id_t;
    typedef ::NS(arch_state_flags_t) arch_state_flags_t;

    static constexpr arch_id_t ARCHITECTURE_UNDEFINED =
        static_cast< arch_id_t >( SIXTRL_ARCHITECTURE_UNDEFINED );

    static constexpr arch_id_t ARCHITECTURE_CPU =
        static_cast< arch_id_t >( SIXTRL_ARCHITECTURE_CPU );

    static constexpr arch_id_t ARCHITECTURE_OPENCL =
        static_cast< arch_id_t >( SIXTRL_ARCHITECTURE_OPENCL );

    static constexpr arch_id_t ARCHITECTURE_CUDA =
        static_cast< arch_id_t >( SIXTRL_ARCHITECTURE_CUDA );

    static constexpr arch_id_t ARCHITECTURE_CUDA_NVRTC =
        static_cast< arch_id_t >( SIXTRL_ARCHITECTURE_CUDA_NVRTC );

    static constexpr arch_id_t ARCHITECTURE_OPENMP =
        static_cast< arch_id_t >( SIXTRL_ARCHITECTURE_OPENMP );

    static constexpr arch_id_t ARCHITECTURE_ILLEGAL =
        static_cast< arch_id_t >( SIXTRL_ARCHITECTURE_ILLEGAL );

    /* -  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    static constexpr arch_state_flags_t ARCH_STATE_NONE =
        static_cast< arch_state_flags_t >( SIXTRL_ARCH_STATE_NONE );

    static constexpr arch_state_flags_t ARCH_STATE_ENABLED =
        static_cast< arch_state_flags_t >( SIXTRL_ARCH_STATE_ENABLED );

    static constexpr arch_state_flags_t ARCH_STATE_ACTIVATED =
        static_cast< arch_state_flags_t >( SIXTRL_ARCH_STATE_ACTIVATED );

    static constexpr arch_state_flags_t ARCH_STATE_AVAILABLE =
        static_cast< arch_state_flags_t >( SIXTRL_ARCH_STATE_AVAILABLE );

    static constexpr arch_state_flags_t ARCH_STATE_SHUTDOWN =
        static_cast< arch_state_flags_t >( SIXTRL_ARCH_STATE_SHUTDOWN );

    static constexpr arch_state_flags_t ARCH_STATE_ERROR =
        static_cast< arch_state_flags_t >( SIXTRL_ARCH_STATE_ERROR );
}
#endif /*  ns: SIXTRL_CXX_NAMESPACE */

#endif /* SIXTRACKLIB_BASE_ARCHITECTURE_DEFINITIONS_H__ */
