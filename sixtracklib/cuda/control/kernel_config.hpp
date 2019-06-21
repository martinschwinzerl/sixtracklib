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

        static constexpr size_type DEFAULT_BLOCK_DIMENSIONS = size_type{ 1 };

        static constexpr size_type
            DEFAULT_THREADS_PER_BLOCK_DIMENSIONS = size_type{ 1 };

        static constexpr size_type
            DEFAULT_SHARED_MEM_PER_BLOCK = size_type{ 0 };

        static constexpr size_type
            DEFAULT_SHARED_MEM_PER_THREAD = size_type{ 0 };

        static constexpr size_type
            DEFAULT_MAX_BLOCK_SIZE_LIMIT = size_type{ 0 };

        static constexpr size_type DEFAULT_WARP_SIZE = size_type{ 32 };

        SIXTRL_HOST_FN explicit CudaKernelConfig(
            size_type const num_kernel_arguments =
                _base_config_t::DEFAULT_NUM_KERNEL_ARGUMENTS,
            purpose_t const purpose = _base_config_t::DEFAULT_KERNEL_PURPOSE,
            variant_t const variant_flags =
                _base_config_t::DEFAULT_KERNEL_VARIANT,
            size_type const block_dimensions =
                DEFAULT_BLOCK_DIMENSIONS,
            size_type const threads_per_block_dimensions =
                DEFAULT_THREADS_PER_BLOCK_DIMENSIONS,
            char const* SIXTRL_RESTRICT name_str = nullptr,
            size_type const shared_mem_per_block =
                DEFAULT_SHARED_MEM_PER_BLOCK,
            size_type const shared_mem_per_thread =
                DEFAULT_SHARED_MEM_PER_THREAD,
            size_type const max_block_size_limit =
                DEFAULT_MAX_BLOCK_SIZE_LIMIT,
            size_type const warp_size = DEFAULT_WARP_SIZE,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN explicit CudaKernelConfig(
            size_type const num_kernel_arguments,
            purpose_t const purpose,
            variant_t const variant_flags,
            size_type const block_dimensions,
            size_type const threads_per_block_dimensions,
            std::string const& SIXTRL_RESTRICT_REF name_str,
            size_type const shared_mem_per_block =
                DEFAULT_SHARED_MEM_PER_BLOCK,
            size_type const shared_mem_per_thread =
                DEFAULT_SHARED_MEM_PER_THREAD,
            size_type const max_block_size_limit =
                DEFAULT_MAX_BLOCK_SIZE_LIMIT,
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

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN ::dim3 const& blocks() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN ::dim3 const& blockOffsets() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN ::dim3 const& threadsPerBlock() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN ::dim3 const* ptrBlocks() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN ::dim3 const* ptrBlockOffsets() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN ::dim3 const* ptrThreadsPerBlock() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type totalNumBlocks() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type totalNumThreadsPerBlock() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type totalNumThreads() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasBlockOffsets() const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t setGrid(
            ::dim3 const& SIXTRL_RESTRICT_REF blocks,
            ::dim3 const& SIXTRL_RESTRICT_REF threads_per_block,
            ::dim3 const& SIXTRL_RESTRICT_REF block_offsets =
                ::dim3{ 0u, 0u, 0u } ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setBlocks(
            ::dim3 const& SIXTRL_RESTRICT_REF blocks ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setBlocks(
            size_type const x_blocks = size_type{ 1 },
            size_type const y_blocks = size_type{ 1 },
            size_type const z_blocks = size_type{ 1 } )  SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setBlockOffsets(
            ::dim3 const& SIXTRL_RESTRICT_REF block_offsets ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setBlockOffsets(
            size_type const x_offset = size_type{ 0 },
            size_type const y_offset = size_type{ 0 },
            size_type const z_offset = size_type{ 0 } )  SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setThreadsPerBlock(
            ::dim3 const& SIXTRL_RESTRICT_REF threads_per_block
        ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setThreadsPerBlock(
            size_type const x_threads_per_block = size_type{ 1 },
            size_type const y_threads_per_block = size_type{ 1 },
            size_type const z_threads_per_block = size_type{ 1 }
        ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type blockDimensions() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        threadsPerBlockDimensions() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type sharedMemPerBlock()  const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type sharedMemPerThread() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type maxBlockSizeLimit()  const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type warpSize() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t reset( size_type const block_dimensions,
            size_type const threads_per_block_dimensions,
            size_type const shared_mem_per_block =
                DEFAULT_SHARED_MEM_PER_BLOCK,
            size_type const shared_mem_per_thread =
                DEFAULT_SHARED_MEM_PER_THREAD,
            size_type const max_block_size_limit =
                DEFAULT_MAX_BLOCK_SIZE_LIMIT,
            size_type const warp_size = DEFAULT_WARP_SIZE );

        SIXTRL_HOST_FN status_t setBlockDimensions(
            size_type const block_dimensions );

        SIXTRL_HOST_FN status_t setThreadsPerBlockDimensions(
            size_type const threads_per_block_dims );

        SIXTRL_HOST_FN status_t setGridDimensions( size_type const block_dims,
            size_type const threads_per_block_dims );

        SIXTRL_HOST_FN status_t setSharedMemPerBlock(
            size_type const shared_mem_per_block );

        SIXTRL_HOST_FN status_t setSharedMemPerThread(
            size_type const shared_mem_per_thread );

        SIXTRL_HOST_FN status_t setMaxBlockSizeLimit(
            size_type const max_block_size_limit );

        SIXTRL_HOST_FN status_t setWarpSize( size_type const warp_size );

        /* ----------------------------------------------------------------- */

        protected:

        SIXTRL_HOST_FN virtual status_t doUpdate() override;

        SIXTRL_HOST_FN virtual status_t doPrintToOutputStream(
            std::ostream& SIXTRL_RESTRICT_REF output ) const override;

        SIXTRL_STATIC SIXTRL_HOST_FN status_t AssignToDim3(
            ::dim3& SIXTRL_RESTRICT_REF destination,
            size_type const num_dimensions,
            size_type const x, size_type const y, size_type const z,
            size_type const min_allowed_entry =
                size_type{ 1 } )  SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_HOST_FN int CompareDim3Objects(
            ::dim3 const& SIXTRL_RESTRICT_REF lhs,
            ::dim3 const& SIXTRL_RESTRICT_REF rhs,
            size_type const num_dimensions ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_HOST_FN bool AreDim3ObjectsEqual(
            ::dim3 const& SIXTRL_RESTRICT_REF lhs,
            ::dim3 const& SIXTRL_RESTRICT_REF rhs,
            size_type const num_dimensions ) SIXTRL_NOEXCEPT;

        private:

        ::dim3    m_blocks;
        ::dim3    m_block_offsets;
        ::dim3    m_threads_per_block;

        size_type m_block_dim;
        size_type m_threads_per_block_dim;

        size_type m_warp_size;
        size_type m_shared_mem_per_block;
        size_type m_shared_mem_per_thread;
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


/* ************************************************************************* */
/* ******  Implementation of inline and template member functions    ******* */
/* ************************************************************************* */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE ::dim3 const&
    CudaKernelConfig::blocks() const SIXTRL_NOEXCEPT
    {
        return this->m_blocks;
    }

    SIXTRL_INLINE ::dim3 const&
    CudaKernelConfig::blockOffsets() const SIXTRL_NOEXCEPT
    {
        return this->m_block_offsets;
    }

    SIXTRL_INLINE ::dim3 const&
    CudaKernelConfig::threadsPerBlock() const SIXTRL_NOEXCEPT
    {
        return this->m_threads_per_block;
    }

    SIXTRL_INLINE ::dim3 const*
    CudaKernelConfig::ptrBlocks() const SIXTRL_NOEXCEPT
    {
        return &this->m_blocks;
    }

    SIXTRL_INLINE ::dim3 const*
    CudaKernelConfig::ptrBlockOffsets() const SIXTRL_NOEXCEPT
    {
        return &this->m_block_offstes;
    }

    SIXTRL_INLINE ::dim3 const*
    CudaKernelConfig::ptrThreadsPerBlock() const SIXTRL_NOEXCEPT
    {
        return &this->m_threads_per_block;
    }

    SIXTRL_INLINE bool CudaKernelConfig::hasBlockOffsets() const SIXTRL_NOEXCEPT
    {
        ::dim3 const cmp_offset( 0u, 0u, 0u );

        return ( CudaKernelConfig::CompareDim3Objects(
            cmp_offset, this->m_block_offsets, this->blockDimensions() ) > 0 );
    }

    SIXTRL_INLINE CudaKernelConfig::size_type
    CudaKernelConfig::totalNumBlocks() const SIXTRL_NOEXCEPT
    {
        return this->m_blocks.x * this->m_blocks.y * this->m_blocks.z;
    }

    SIXTRL_INLINE CudaKernelConfig::size_type
    CudaKernelConfig::totalNumThreadsPerBlock() const SIXTRL_NOEXCEPT
    {
        return this->m_threads_per_block.x *
               this->m_threads_per_block.y *
               this->m_threads_per_block.z;
    }

    SIXTRL_INLINE CudaKernelConfig::size_type
    CudaKernelConfig::totalNumThreads() const SIXTRL_NOEXCEPT
    {
        return this->totalNumBlocks() * this->totalNumThreadsPerBlock();
    }

    SIXTRL_INLINE CudaKernelConfig::size_type
    CudaKernelConfig::blockDimensions() const SIXTRL_NOEXCEPT
    {
        return this->m_block_dim;
    }

    SIXTRL_INLINE CudaKernelConfig::size_type
    CudaKernelConfig::threadsPerBlockDimensions() const SIXTRL_NOEXCEPT
    {
        return this->m_threads_per_block_dim;
    }

    SIXTRL_INLINE CudaKernelConfig::size_type
    CudaKernelConfig::sharedMemPerBlock() const SIXTRL_NOEXCEPT
    {
        return this->m_shared_mem_per_block;
    }

    SIXTRL_INLINE CudaKernelConfig::size_type
    CudaKernelConfig::sharedMemPerThread() const SIXTRL_NOEXCEPT
    {
        return this->m_shared_mem_per_thread;
    }

    SIXTRL_INLINE CudaKernelConfig::size_type
    CudaKernelConfig::maxBlockSizeLimit() const SIXTRL_NOEXCEPT
    {
        return this->m_max_block_size_limit;
    }

    SIXTRL_INLINE CudaKernelConfig::size_type
    CudaKernelConfig::warpSize() const SIXTRL_NOEXCEPT
    {
        return this->m_warp_size;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CudaKernelConfig::status_t CudaKernelConfig::AssignToDim3(
        ::dim3& SIXTRL_RESTRICT_REF destination,
        CudaKernelConfig::size_type const num_dimensions,
        CudaKernelConfig::size_type const x,
        CudaKernelConfig::size_type const y,
        CudaKernelConfig::size_type const z,
        CudaKernelConfig::size_type const min_allowed_entry ) SIXTRL_NOEXCEPT
    {
        CudaKernelConfig::status_t status =
            SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        switch( num_dimensions )
        {
            case CudaKernelConfig::size_type{ 1 }:
            {
                if( x >= min_allowed_entry )
                {
                    destination.x = x;
                    destination.y = min_allowed_entry;
                    destination.z = min_allowed_entry;

                    status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
                }

                break;
            }

            case CudaKernelConfig::size_type{ 2 }:
            {
                if( ( x >= min_allowed_entry ) && ( y >= min_allowed_entry ) )
                {
                    destination.x = x;
                    destination.y = y;
                    destination.z = min_allowed_entry;

                    status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
                }

                break;
            }

            case CudaKernelConfig::size_type{ 3 }:
            {
                if( ( x >= min_allowed_entry ) && ( y >= min_allowed_entry ) &&
                    ( y >= min_allowed_entry ) )
                {
                    destination.x = x;
                    destination.y = y;
                    destination.z = z;

                    status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
                }

                break;
            }

            default:
            {
                destination.x = destination.y =
                destination.y = min_allowed_entry;
            }
        };

        return status;
    }

    int CudaKernelConfig::CompareDim3Objects(
        ::dim3 const& SIXTRL_RESTRICT_REF lhs,
        ::dim3 const& SIXTRL_RESTRICT_REF rhs,
        CudaKernelConfig::size_type const num_dimensions ) SIXTRL_NOEXCEPT
    {
        using size_t = CudaKernelConfig::size_type;

        int compare_results = -1;

        if( ( num_dimensions >= size_t{ 1 } ) &&
            ( num_dimensions <= size_t{ 3 } ) )
        {
            compare_results = ( lhs.x < rhs.x )
                ? -1 : ( ( lhs.x > rhs.x ) ? +1 : 0 );

            if( ( compare_results == 0 ) &&
                ( num_dimensions >= size_t{ 2 } ) )
            {
                compare_results = ( lhs.y < rhs.y )
                    ? -1 : ( ( lhs.y > rhs.y ) ? +1 : 0 );
            }

            if( ( compare_results == 0 ) &&
                ( num_dimensions == size_t{ 3 } ) )
            {
                compare_results = ( lhs.z < rhs.z )
                    ? -1 : ( ( lhs.z > rhs.z ) ? +1 : 0 );
            }
        }

        return compare_results;
    }

    bool CudaKernelConfig::AreDim3ObjectsEqual(
        ::dim3 const& SIXTRL_RESTRICT_REF lhs,
        ::dim3 const& SIXTRL_RESTRICT_REF rhs,
        CudaKernelConfig::size_type const num_dimensions ) SIXTRL_NOEXCEPT
    {
        return ( 0 == CudaKernelConfig::CompareDim3Objects(
            lhs, rhs, num_dimensions ) );
    }
}

#endif /* SIXTRACKLIB_CUDA_CONTROL_KERNEL_CONFIG_CXX_HPP__ */
