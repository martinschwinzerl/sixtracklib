#ifndef SIXTRACKLIB_COMMON_GENERATED_HELPERS_H__
#define SIXTRACKLIB_COMMON_GENERATED_HELPERS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE )
SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(OpenCL_enabled)( void ) SIXTRL_NOEXCEPT;
SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Cuda_enabled)( void ) SIXTRL_NOEXCEPT;
#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_GENERATED_HELPERS_H__ */
