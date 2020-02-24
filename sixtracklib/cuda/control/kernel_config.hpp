#ifndef SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_CXX_HPP__
#define SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_CXX_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <cuda_runtime_api.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */


#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/kernel_config_base.h"
    #include "sixtracklib/cuda/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/kernel_config_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class CudaKernelConfig : public SIXTRL_CXX_NAMESPACE::KernelConfigBase
    {
        private:

        using _base_config_t = SIXTRL_CXX_NAMESPACE::KernelConfigBase;

        public:

        using arch_id_t   = _base_config_t::arch_id_t;
        using size_type   = _base_config_t::size_type;
        using kernel_id_t = _base_config_t::kernel_id_t;
        using ptr_kernel_wrapper_t = void*;

        static constexpr size_type DEFAULT_WARP_SIZE = size_type{ 32 };

        SIXTRL_HOST_FN explicit CudaKernelConfig(
            size_type const block_dimensions = size_type{ 1 },
            size_type const threads_per_block_dimensions = size_type{ 1 },
            size_type const shared_mem_per_block = size_type{ 0 },
            size_type const max_block_size_limit = size_type{ 0 },
            size_type const warp_size = DEFAULT_WARP_SIZE,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN explicit CudaKernelConfig(
            std::string const& SIXTRL_RESTRICT_REF name_str,
            size_type const num_kernel_arguments = size_type{ 0 },
            size_type const block_dimensions = size_type{ 1 },
            size_type const threads_per_block_dimensions = size_type{ 1 },
            size_type const shared_mem_per_block = size_type{ 0 },
            size_type const max_block_size_limit = size_type{ 0 },
            size_type const warp_size = DEFAULT_WARP_SIZE,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN explicit CudaKernelConfig(
            char const* SIXTRL_RESTRICT name_str,
            size_type const num_kernel_arguments = size_type{ 0 },
            size_type const block_dimensions = size_type{ 1 },
            size_type const threads_per_block_dimensions = size_type{ 1 },
            size_type const shared_mem_per_block = size_type{ 0 },
            size_type const max_block_size_limit = size_type{ 0 },
            size_type const warp_size = DEFAULT_WARP_SIZE,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN CudaKernelConfig(
            CudaKernelConfig const& other ) = default;

        SIXTRL_HOST_FN CudaKernelConfig(
            CudaKernelConfig&& other ) = default;

        SIXTRL_HOST_FN CudaKernelConfig& operator=(
        SIXTRL_HOST_FN CudaKernelConfig const& rhs ) = default;

        SIXTRL_HOST_FN CudaKernelConfig& operator=(
            CudaKernelConfig&& rhs ) = default;

        SIXTRL_HOST_FN virtual ~CudaKernelConfig() = default;

        size_type warpSize() const SIXTRL_NOEXCEPT;
        void setWarpSize( size_type const warp_size ) SIXTRL_NOEXCEPT;

        size_type sharedMemPerBlock() const SIXTRL_NOEXCEPT;
        void setSharedMemPerBlock(
            size_type const shared_mem_per_block ) SIXTRL_NOEXCEPT;

        size_type maxBlockSizeLimit() const SIXTRL_NOEXCEPT;
        void setMaxBlockSizeLimit(
            size_type const max_block_size_limit ) SIXTRL_NOEXCEPT;

        ::dim3 const& blocks() const SIXTRL_NOEXCEPT;
        ::dim3 const& threadsPerBlock() const SIXTRL_NOEXCEPT;

        ::dim3 const* ptrBlocks() const SIXTRL_NOEXCEPT;
        ::dim3 const* ptrThreadsPerBlock() const SIXTRL_NOEXCEPT;

        status_t setGrid(
            size_type const x_blocks = 1u,
            size_type const x_threads_per_block = 1u,
            size_type const y_blocks = 1u,
            size_type const y_threads_per_block = 1u,
            size_type const z_blocks = 1u,
            size_type const z_threads_per_block = 1u );

        status_t setGrid(
            ::dim3 const& SIXTRL_RESTRICT_REF num_blocks,
            ::dim3 const& SIXTRL_RESTRICT_REF threads_per_block );

        size_type totalNumBlocks() const SIXTRL_NOEXCEPT;
        size_type totalNumThreadsPerBlock() const SIXTRL_NOEXCEPT;
        size_type totalNumThreads() const SIXTRL_NOEXCEPT;

        protected:

        virtual status_t doUpdate() override;
        virtual void doPrintToOutputStream(
            std::ostream& SIXTRL_RESTRICT_REF output ) const override;

        private:

        ::dim3    m_blocks;
        ::dim3    m_threads_per_block;

        size_type m_warp_size;
        size_type m_shared_mem_per_block;
        size_type m_max_block_size_limit;
    };
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

typedef SIXTRL_CXX_NAMESPACE::CudaKernelConfig NS(CudaKernelConfig);

#else /* C++, Host */

typedef void NS(CudaKernelConfig);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

#endif /* SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_CXX_HPP__ */
