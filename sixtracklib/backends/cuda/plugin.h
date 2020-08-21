#ifndef SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_H__
#define SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/definitions.h"
    #include "sixtracklib/backends/cuda/dlib.h"

    #if defined( SIXTRL_CUDA_PLUGIN_BUILT ) && ( SIXTRL_CUDA_PLUGIN_BUILT == 1 )
        #include "sixtracklib/backends/cuda/plugin/context.h"
        #include "sixtracklib/backends/cuda/plugin/node.h"
//         #include "sixtracklib/backends/cuda/plugin/controller.h"
//         #include "sixtracklib/backends/cuda/plugin/track_job.h"

    #endif /* CUDA enabled */
#endif /* !defined( SIXTRL_CUDA_PLUGIN_BUILT ) */
#endif /* SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_H__ */
