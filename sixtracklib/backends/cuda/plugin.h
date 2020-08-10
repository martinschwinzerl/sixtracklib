#ifndef SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_H__
#define SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/definitions.h"
    #include "sixtracklib/backends/cuda/dlib.h"

    #if defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
        SIXTRACKL_ENABLE_BACKEND_CUDA == 1

        #include "sixtracklib/backends/cuda/node.h"
        #include "sixtracklib/backends/cuda/controller.h"
        #include "sixtracklib/backends/cuda/track_job.h"

    #endif /* CUDA enabled */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */
#endif /* SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_H__ */
