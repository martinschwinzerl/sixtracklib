#ifndef SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_INIT_FINISH_H__
#define SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_INIT_FINISH_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/definitions.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE )
SIXTRL_EXPORT_API SIXTRL_HOST_FN
void NS(Cuda_plugin_init)( void ) SIXTRL_DLIB_CONSTRUCTOR;

SIXTRL_EXPORT_API SIXTRL_HOST_FN
void NS(Cuda_plugin_finish)( void ) SIXTRL_DLIB_DESTRUCTOR;
#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_INIT_FINISH_H__ */
