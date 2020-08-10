#ifndef SIXTRACKLIB_BACKENDS_CUDA_CUDA_H__
#define SIXTRACKLIB_BACKENDS_CUDA_CUDA_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/definitions.h"
    #include "sixtracklib/backends/cuda/dlib.h"
    #include "sixtracklib/backends/cuda/backend.h"

    #if defined( SIXTRACKLIB_CUDA_PLUGIN_BUILT ) && \
                 SIXTRACKLIB_CUDA_PLUGIN_BUILT == 1
        #include "sixtracklib/backends/cuda/plugin.h"
    #endif /* plugin */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */
#endif /* SIXTRACKLIB_BACKENDS_CUDA_CUDA_H__ */
