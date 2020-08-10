#ifndef SIXTRACKLIB_BASE_BACKEND_DEFINITIONS_H__
#define SIXTRACKLIB_BASE_BACKEND_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

typedef SIXTRL_INT64_T  NS(backend_id_t);

#if !defined( SIXTRL_BACKEND_NONE )
    #define SIXTRL_BACKEND_UNDEFINED 0
#endif /* !defined( SIXTRL_BACKEND_NONE ) */

#if !defined( SIXTRL_BACKEND_NONE )
    #define SIXTRL_BACKEND_UNDEFINED_STR ""
#endif /* !defined( SIXTRL_BACKEND_NONE ) */

#if !defined( SIXTRL_BACKEND_CPU )
    #define SIXTRL_BACKEND_CPU 1
#endif /* !defined( SIXTRL_BACKEND_CPU ) */

#if !defined( SIXTRL_BACKEND_NONE )
    #define SIXTRL_BACKEND_CPU_STR "cpu"
#endif /* !defined( SIXTRL_BACKEND_NONE ) */

#if !defined( SIXTRL_BACKEND_OPENCL )
    #define SIXTRL_BACKEND_OPENCL 2
#endif /* !defined( SIXTRL_BACKEND_OPENCL ) */

#if !defined( SIXTRL_BACKEND_NONE )
    #define SIXTRL_BACKEND_OPENCL_STR "opencl"
#endif /* !defined( SIXTRL_BACKEND_NONE ) */

#if !defined( SIXTRL_BACKEND_CUDA )
    #define SIXTRL_BACKEND_CUDA 3
#endif /* !defined( SIXTRL_BACKEND_CUDA ) */

#if !defined( SIXTRL_BACKEND_CUDA_STR )
    #define SIXTRL_BACKEND_CUDA_STR "cuda"
#endif /* !defined( SIXTRL_BACKEND_CUDA_STR ) */

#if !defined( SIXTRL_BACKEND_CUDA_NVRTC )
    #define SIXTRL_BACKEND_CUDA_NVRTC 4
#endif /* !defined( SIXTRL_BACKEND_CUDA_NVRTC ) */

#if !defined( SIXTRL_BACKEND_CUDA_NVRTC_STR )
    #define SIXTRL_BACKEND_CUDA_NVRTC_STR "cuda_nvrtc"
#endif /* !defined( SIXTRL_BACKEND_CUDA_NVRTC_STR ) */

#if !defined( SIXTRL_BACKEND_OPENMP )
    #define SIXTRL_BACKEND_OPENMP 5
#endif /* !defined( SIXTRL_BACKEND_OPENMP ) */

#if !defined( SIXTRL_BACKEND_OPENMP_STR )
    #define SIXTRL_BACKEND_OPENMP_STR "openmp"
#endif /* !defined( SIXTRL_BACKEND_OPENMP_STR ) */

#if !defined( SIXTRL_BACKEND_ILLEGAL )
    #define SIXTRL_BACKEND_ILLEGAL 0xffff
#endif /* !defined( SIXTRL_BACKEND_ILLEGAL ) */

#if !defined( _GPUCODE )
#if defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC_VAR const NS(backend_id_t)
NS(BACKEND_UNDEFINED) = ( NS(backend_id_t) )SIXTRL_BACKEND_UNDEFINED;

SIXTRL_STATIC_VAR const NS(backend_id_t)
NS(BACKEND_CPU) = ( NS(backend_id_t) )SIXTRL_BACKEND_CPU;

SIXTRL_STATIC_VAR const NS(backend_id_t)
NS(BACKEND_OPENCL) = ( NS(backend_id_t) )SIXTRL_BACKEND_OPENCL;

SIXTRL_STATIC_VAR const NS(backend_id_t)
NS(BACKEND_CUDA) = ( NS(backend_id_t) )SIXTRL_BACKEND_CUDA;

SIXTRL_STATIC_VAR const NS(backend_id_t)
NS(BACKEND_CUDA_NVRTC) = ( NS(backend_id_t) )SIXTRL_BACKEND_CUDA_NVRTC;

SIXTRL_STATIC_VAR const NS(backend_id_t)
NS(BACKEND_OPENMP) = ( NS(backend_id_t) )SIXTRL_BACKEND_OPENMP;

#if defined( __cplusplus )
}
#endif /* C++ */
#endif /* Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(backend_id_t) backend_id_t;

    static constexpr backend_id_t BACKEND_UNDEFINED =
        static_cast< backend_id_t >( SIXTRL_BACKEND_UNDEFINED );

    static constexpr backend_id_t BACKEND_CPU =
        static_cast< backend_id_t >( SIXTRL_BACKEND_CPU );

    static constexpr backend_id_t BACKEND_OPENCL =
        static_cast< backend_id_t >( SIXTRL_BACKEND_OPENCL );

    static constexpr backend_id_t BACKEND_CUDA =
        static_cast< backend_id_t >( SIXTRL_BACKEND_CUDA );

    static constexpr backend_id_t BACKEND_CUDA_NVRTC =
        static_cast< backend_id_t >( SIXTRL_BACKEND_CUDA_NVRTC );

    static constexpr backend_id_t BACKEND_OPENMP =
        static_cast< backend_id_t >( SIXTRL_BACKEND_OPENMP );

    static constexpr backend_id_t BACKEND_ILLEGAL =
        static_cast< backend_id_t >( SIXTRL_BACKEND_ILLEGAL );
}
#endif /*  ns: SIXTRL_CXX_NAMESPACE */
#endif /* SIXTRACKLIB_BASE_BACKEND_DEFINITIONS_H__ */
