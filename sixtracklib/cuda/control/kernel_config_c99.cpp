#include "sixtracklib/cuda/control/kernel_config.h"

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )

#include <cuda_runtime_api.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/cuda/definitions.h"
#include "sixtracklib/cuda/controller.hpp"
#include "sixtracklib/cuda/control/kernel_config.hpp"
#include "sixtracklib/cuda/control/node_info.hpp"
#include "sixtracklib/cuda/controller.hpp"
#include "sixtracklib/cuda/controller.h"

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(CudaKernelConfig)* NS(CudaKernelConfig_new)(
    ::NS(arch_size_t) const num_kernel_args,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(kernel_variant_t) const variant_flags,
    char const* SIXTRL_RESTRICT kernel_name )
{
    return new st::CudaKernelConfig(
        num_kernel_args, purpose, variant_flags,
        st::CudaKernelConfig::DEFAULT_BLOCK_DIMENSIONS,
        st::CudaKernelConfig::DEFAULT_THREADS_PER_BLOCK_DIMENSIONS,
        kernel_name );
}

NS(CudaKernelConfig)* NS(CudaKernelConfig_new_detailed)(
    ::NS(arch_size_t) const num_kernel_args,
    ::NS(kernel_purpose_t) const purpose,
    ::NS(kernel_variant_t) const variant_flags,
    ::NS(arch_size_t) const block_dim,
    ::NS(arch_size_t) const threads_per_block_dim,
    char const* SIXTRL_RESTRICT kernel_name,
    ::NS(arch_size_t) const shared_mem_per_block,
    ::NS(arch_size_t) const shared_mem_per_thread,
    ::NS(arch_size_t) const max_block_size_limit,
    ::NS(arch_size_t) const warp_size,
    char const* SIXTRL_RESTRICT config_str )
{
    return new st::CudaKernelConfig( num_kernel_args, purpose, variant_flags,
        block_dim, threads_per_block_dim, kernel_name, shared_mem_per_block,
        shared_mem_per_thread, max_block_size_limit, warp_size, config_str );
}

/* ------------------------------------------------------------------------ */

::dim3 const* NS(CudaKernelConfig_get_ptr_const_blocks)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr ) ? config->ptrBlocks() : nullptr;
}

bool NS(CudaKernelConfig_has_block_offsets)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT config )
{
    return ( ( config != nullptr ) && ( config->hasBlockOffsets() ) );
}

::dim3 const* NS(CudaKernelConfig_get_ptr_const_block_offsets)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr ) ? config->ptrBlockOffsets() : nullptr;
}

::dim3 const* NS(CudaKernelConfig_get_ptr_const_threads_per_block)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr ) ? config->ptrThreadsPerBlock() : nullptr;
}

/* ------------------------------------------------------------------------ */

::NS(arch_size_t) NS(CudaKernelConfig_total_num_blocks)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT kernel_config )
{
    return ( config != nullptr )
        ? config->totalNumBlocks() : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(CudaKernelConfig_total_num_threads_per_block)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT kernel_config )
{
    return ( config != nullptr )
        ? config->totalNumThreadsPerBlock() : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(CudaKernelConfig_total_num_threads)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT kernel_config )
{
    return ( config != nullptr )
        ? config->totalNumThreads() : ::NS(arch_size_t){ 0 };
}

/* ------------------------------------------------------------------------ */

::NS(arch_status_t) NS(CudaKernelConfig_set_grid)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    const ::dim3 *const SIXTRL_RESTRICT blocks,
    const ::dim3 *const SIXTRL_RESTRICT threads_per_block )
{
    using size_t = st::CudaKernelConfig::arch_size_t;

    ::NS(arch_status_t) status = ::NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( config != nullptr ) &&
        ( config->blockDimensions() > size_t{ 0 } ) &&
        ( config->threadsPerBlockDimensions() > size_t{ 0 } ) )
    {
        ::dim3 block_offsets( 0u, 0u, 0u );

        if( ( blocks != nullptr ) && ( threads_per_block != nullptr ) )
        {
            status = config->setGrid(
                *blocks, *threads_per_block, block_offsets );
        }
    }

    return status;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_grid_with_offset)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    const ::dim3 *const SIXTRL_RESTRICT blocks,
    const ::dim3 *const SIXTRL_RESTRICT threads_per_block,
    const ::dim3 *const SIXTRL_RESTRICT block_offsets )
{
    using size_t = st::CudaKernelConfig::arch_size_t;

    ::NS(arch_status_t) status = ::NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( config != nullptr ) &&
        ( config->blockDimensions() > size_t{ 0 } ) &&
        ( config->threadsPerBlockDimensions() > size_t{ 0 } ) )
    {
        ::dim3 temp_block_offsets( 0u, 0u, 0u );

        if( ( blocks != nullptr ) && ( threads_per_block != nullptr ) )
        {
            ::dim3 const* ptr_block_offsets = ( block_offsets != nullptr )
                ? block_offsets : &temp_block_offsets;

            status = config->setGrid( *blocks, *threads_per_block,
                                      *ptr_block_offsets );
        }
    }

    return status;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_blocks)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    const dim3 *const SIXTRL_RESTRICT blocks )
{
    return ( ( config != nullptr ) && ( blocks != nullptr ) )
        ? config->setBlocks( *blocks ) : st::ARCH_STATUS_GENERAL_FAILURE;
}


::NS(arch_status_t) NS(CudaKernelConfig_set_blocks_1d)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const x_blocks )
{
    return ( config != nullptr )
        ? config->setBlocks( x_blocks ) : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_blocks_2d)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const x_blocks, ::NS(arch_size_t) const y_blocks )
{
    return ( config != nullptr )
        ? config->setBlocks( x_blocks, y_blocks )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_blocks_3d)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const x_blocks, ::NS(arch_size_t) const y_blocks,
    ::NS(arch_size_t) const z_blocks )
{
    return ( config != nullptr )
        ? config->setBlocks( x_blocks, y_blocks, z_blocks )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_block_offsets)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    const dim3 *const SIXTRL_RESTRICT block_offsets )
{
    return ( ( config != nullptr ) && ( block_offsets != nullptr ) )
        ? config->setBlockOffsets( *block_offsets )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_block_offsets_1d)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const x_offset )
{
    return ( config != nullptr ) ? config->setBlockOffsets( x_offset )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_block_offsets_2d)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const x_offset, ::NS(arch_size_t) const y_offset )
{
    return ( config != nullptr )
        ? config->setBlockOffsets( x_offset, y_offset )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_block_offsets_3d)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const x_offset, ::NS(arch_size_t) const y_offset,
    ::NS(arch_size_t) const z_offset )
{
    return ( config != nullptr )
        ? config->setBlockOffsets( x_offset, y_offset, z_offset )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}


::NS(arch_status_t) NS(CudaKernelConfig_set_threads_per_block)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    const ::dim3 *const SIXTRL_RESTRICT threads_per_block )
{
    return ( ( config != nullptr )  && ( threads_per_block != nullptr ) )
        ? config->setThreadsPerBlock( *threads_per_block )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_threads_per_block_1d)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const x_threads )
{
    return ( config != nullptr ) ? config->setThreadsPerBlock( x_threads )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_threads_per_block_2d)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const x_threads, ::NS(arch_size_t) const y_threads )
{
    return ( config != nullptr )
        ? config->setThreadsPerBlock( x_threads, y_threads )
        : st::ARCH_STATUS_GENERAL_FAILURE;


::NS(arch_status_t) NS(CudaKernelConfig_set_threads_per_block_3d)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const x_threads, ::NS(arch_size_t) const y_threads,
    ::NS(arch_size_t) const z_threads )
{
    return ( config != nullptr )
        ? config->setThreadsPerBlock( x_threads, y_threads, z_threads )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(CudaKernelConfig_get_block_dim)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr )
        ? config->blockDimensions() : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(CudaKernelConfig_get_threads_per_block_dim)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr )
        ? config->threadsPerBlockDimensions() : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(CudaKernelConfig_get_shared_mem_per_block)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr )
        ? config->sharedMemPerBlock() : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(CudaKernelConfig_get_shared_mem_per_thread)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr )
        ? config->sharedMemPerThread() : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(CudaKernelConfig_get_max_block_size_limit)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr )
        ? config->maxBlockSizeLimit() : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(CudaKernelConfig_get_warp_size)(
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT config )
{
    return ( config != nullptr ) ? config->warpSize() : ::NS(arch_size_t){ 0 };
}

::NS(arch_status_t)  NS(CudaKernelConfig_reset)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const block_dim,
    ::NS(arch_size_t) const threads_per_block_dim,
    ::NS(arch_size_t) const shared_mem_per_block,
    ::NS(arch_size_t) const shared_mem_per_thread,
    ::NS(arch_size_t) const max_block_size_limit,
    ::NS(arch_size_t) const warp_size )
{
    return ( config != nullptr )
        ? config->reset( block_dim,
            threads_per_block_dim, shared_mem_per_block, shared_mem_per_thread,
            max_block_size_limit, warp_size )
        : st::ARCH_STATUS_GENERAL_FAILURE;

}

::NS(arch_status_t) NS(CudaKernelConfig_set_block_dim)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const block_dims )
{
    return ( config != nullptr )
        ? config->setBlockDimensions( block_dims )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_threads_per_block_dim)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const threads_per_block_dims )
{
    return ( config != nullptr )
        ? config->setThreadsPerBlockDimensions( threads_per_block_dims )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_grid_dimensions)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const block_dims,
    ::NS(arch_size_t) const threads_per_block_dims )
{
    return ( config != nullptr )
        ? config->setGridDimensions( block_dims, threads_per_block_dims )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_shared_mem_per_block)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const shared_mem_per_block )
{
    return ( config != nullptr )
        ? config->setSharedMemPerBlock( shared_mem_per_block )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_shared_mem_per_thread)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const shared_mem_per_thread )
{
    return ( config != nullptr )
        ? config->setSharedMemPerThread( shared_mem_per_thread )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_max_block_size_limit)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const max_block_size_limit )
{
    return ( config != nullptr )
        ? config->setMaxBlockSizeLimit( max_block_size_limit )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(CudaKernelConfig_set_warp_size)(
    ::NS(CudaKernelConfig)* SIXTRL_RESTRICT config,
    ::NS(arch_size_t) const warp_size )
{
   return ( config != nullptr )
       ? config->setWarpSize( warp_size ) : st::ARCH_STATUS_GENERAL_FAILURE;
}

#endif /* C++, Host */

/* end: sixtracklib/cuda/control/kernel_config_c99.cpp */
