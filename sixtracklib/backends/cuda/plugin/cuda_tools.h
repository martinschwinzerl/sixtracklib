#ifndef SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CUDA_TOOLS_H__
#define SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CUDA_TOOLS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/definitions.h"
#endif /* C++ */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cuda.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE )

SIXTRL_STATIC SIXTRL_HOST_FN void NS(Cuda_init_thread)(
    unsigned int const flags );

SIXTRL_STATIC SIXTRL_HOST_FN NS(status_t) NS(Cuda_curesult_to_status)( 
    CUresult const result ) SIXTRL_NOEXCEPT;

#endif /* _GPUCODE */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */

/* ------------------------------------------------------------------------ */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE )

SIXTRL_INLINE void NS(Cuda_init_thread)( unsigned int const flags )
{
    CUresult const ret = cuInit( flags );
    SIXTRL_ASSERT( ret == CUDA_SUCCESS );
    ( void )ret;
}

SIXTRL_INLINE NS(status_t) NS(Cuda_curesult_to_status)( 
    CUresult const result ) SIXTRL_NOEXCEPT
{
    return ( result == CUDA_SUCCESS ) 
        ? ( NS(status_t) )SIXTRL_STATUS_SUCCESS
        : ( NS(status_t) )SIXTRL_STATUS_GENERAL_FAILURE;
}

#endif /* _GPUCODE */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CUDA_TOOLS_H__ */
