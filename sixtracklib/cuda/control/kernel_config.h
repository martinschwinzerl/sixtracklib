#ifndef SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_C99_H__
#define SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/cuda/control/kernel_config.hpp"
    #include "sixtracklib/cuda/definitions.h"
    #include "sixtracklib/cuda/controller.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cuda_runtime_api.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/kernel_config_base.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(CudaKernelConfig)* NS(CudaKernelConfig_new)(
    NS(arch_size_t) const num_kernel_args,
    NS(kernel_purpose_t) const purpose,
    NS(kernel_variant_t) const variant_flags,
    char const* SIXTRL_RESTRICT kernel_name );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(CudaKernelConfig)*
NS(CudaKernelConfig_new_detailed)(
    NS(arch_size_t) const num_kernel_args,
    NS(kernel_purpose_t) const purpose,
    NS(kernel_variant_t) const variant_flags,
    NS(arch_size_t) const block_dimensions,
    NS(arch_size_t) const threads_per_block_dimensions,
    char const* SIXTRL_RESTRICT kernel_name,
    NS(arch_size_t) const shared_mem_per_block,
    NS(arch_size_t) const shared_mem_per_thread,
    NS(arch_size_t) const max_block_size_limit,
    NS(arch_size_t) const warp_size,
    char const* SIXTRL_RESTRICT config_str );

/* ------------------------------------------------------------------------ */

SIXTRL_EXTERN SIXTRL_HOST_FN dim3 const*
NS(CudaKernelConfig_get_ptr_const_blocks)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT cuda_kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(CudaKernelConfig_has_block_offsets)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT cuda_kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN dim3 const*
NS(CudaKernelConfig_get_ptr_const_block_offsets)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT cuda_kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN dim3 const*
NS(CudaKernelConfig_get_ptr_const_threads_per_block)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT cuda_kernel_config );

/* ------------------------------------------------------------------------ */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(CudaKernelConfig_total_num_blocks)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(CudaKernelConfig_total_num_threads_per_block)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(CudaKernelConfig_total_num_threads)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT kernel_config );

/* ------------------------------------------------------------------------ */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(CudaKernelConfig_set_grid)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    const dim3 *const SIXTRL_RESTRICT blocks,
    const dim3 *const SIXTRL_RESTRICT threads_per_block );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_grid_with_offset)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    const dim3 *const SIXTRL_RESTRICT blocks,
    const dim3 *const SIXTRL_RESTRICT threads_per_block,
    const dim3 *const SIXTRL_RESTRICT block_offsets );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_blocks)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    const dim3 *const SIXTRL_RESTRICT blocks );


SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_blocks_1d)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const x_blocks );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_blocks_2d)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const x_blocks, NS(arch_size_t) const y_blocks );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_blocks_3d)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const x_blocks, NS(arch_size_t) const y_blocks,
    NS(arch_size_t) const z_blocks );


SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_block_offsets)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    const dim3 *const SIXTRL_RESTRICT block_offsets );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_block_offsets_1d)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
     NS(arch_size_t) const x_offset );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_block_offsets_2d)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
     NS(arch_size_t) const x_offset,
     NS(arch_size_t) const y_offset );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_block_offsets_3d)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
     NS(arch_size_t) const x_offset,
     NS(arch_size_t) const y_offset,
     NS(arch_size_t) const z_offset );


SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_threads_per_block)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    const dim3 *const SIXTRL_RESTRICT threads_per_block );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_threads_per_block_1d)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const x_threads_per_block );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_threads_per_block_2d)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const x_threads_per_block,
    NS(arch_size_t) const y_threads_per_block );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_threads_per_block_3d)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const x_threads_per_block,
    NS(arch_size_t) const y_threads_per_block,
    NS(arch_size_t) const z_threads_per_block );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(CudaKernelConfig_get_block_dim)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT cuda_kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(CudaKernelConfig_get_threads_per_block_dim)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT cuda_kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(CudaKernelConfig_get_shared_mem_per_block)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT cuda_kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(CudaKernelConfig_get_shared_mem_per_thread)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT cuda_kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(CudaKernelConfig_get_max_block_size_limit)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT cuda_kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_size_t)
NS(CudaKernelConfig_get_warp_size)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT cuda_kernel_config );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_reset)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const block_dim,
    NS(arch_size_t) const threads_per_block_dim,
    NS(arch_size_t) const shared_mem_per_block,
    NS(arch_size_t) const shared_mem_per_thread,
    NS(arch_size_t) const max_block_size_limit,
    NS(arch_size_t) const warp_size );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_block_dim)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const block_dims );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_threads_per_block_dim)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const threads_per_block_dims );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_grid_dimensions)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const block_dims,
    NS(arch_size_t) const threads_per_block_dims );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_shared_mem_per_block)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const shared_mem_per_block );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_shared_mem_per_thread)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const shared_mem_per_thread );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_max_block_size_limit)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const max_block_size_limit );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t)
NS(CudaKernelConfig_set_warp_size)(
    NS(CudaKernelConfig)* SIXTRL_RESTRICT cuda_kernel_config,
    NS(arch_size_t) const warp_size );

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_C99_H__ */

/* end: sixtracklib/cuda/control/kernel_config.h */
