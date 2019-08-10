#ifndef SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_STORE_C99_H__
#define SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_STORE_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/cuda/control/kernel_config_store.hpp"
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/kernel_config_key.h"
    #include "sixtracklib/common/control/kernel_config_store.h"
    #include "sixtracklib/cuda/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )

NS(CudaKernelConfigStore)*
    NS(CudaKernelConfigStore_get_ptr)( void );

const NS(CudaKernelConfigStore) *const
    NS(CudaKernelConfigStore_get_ptr_const)( void );

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

#endif /* SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_STORE_C99_H__ */

/* end: */
