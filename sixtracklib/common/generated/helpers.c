#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/generated/helpers.h"
    #include "sixtracklib/common/generated/config.h"
    #include "sixtracklib/common/generated/modules.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE )

bool NS(OpenCL_enabled)( void ) SIXTRL_NOEXCEPT {
    #if defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
               ( SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1 )
    return true;
    #else /* !defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) */
    return false;
    #endif /* defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) */
}

bool NS(Cuda_enabled)( void ) SIXTRL_NOEXCEPT {
    #if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
               ( SIXTRACKLIB_ENABLE_MODULE_CUDA == 1 )
    return true;
    #else /* !defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) */
    return false;
    #endif /* defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) */
}

#endif /* !defined( _GPUCODE ) */
