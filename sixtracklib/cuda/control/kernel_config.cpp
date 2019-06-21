#include "sixtracklib/cuda/control/kernel_config.hpp"

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus ) && !defined( _GPUCODE ) && \
       !defined( __CUDA_ARCH__ )
        #include <cstddef>
        #include <cstdlib>
        #include <iomanip>
        #include <ostream>
    #endif /* C++, Host */

    #include <cuda_runtime_api.h>

#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/kernel_config_base.hpp"
    #include "sixtracklib/cuda/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    CudaKernelConfig::CudaKernelConfig(
        CudaKernelConfig::size_type const num_kernel_arguments,
        CudaKernelConfig::purpose_t const purpose,
        CudaKernelConfig::variant_t const variant_flags,
        CudaKernelConfig::size_type const block_dimensions,
        CudaKernelConfig::size_type const threads_per_block_dimensions,
        char const* SIXTRL_RESTRICT kernel_name_str,
        CudaKernelConfig::size_type const shared_mem_per_block,
        CudaKernelConfig::size_type const shared_mem_per_thread,
        CudaKernelConfig::size_type const max_block_size_limit,
        CudaKernelConfig::size_type const warp_size,
        char const* SIXTRL_RESTRICT config_str ) :
        st::KernelConfigBase( st::ARCHITECTURE_CUDA,
            SIXTRL_ARCHITECTURE_CUDA_STR, num_kernel_arguments,
            purpose, variant_flags, kernel_name_str, config_str ),
            m_blocks(), m_threads_per_block(), m_block_offsets( 0u, 0u, 0u ),
            m_block_dim( CudaKernelConfig::DEFAULT_BLOCK_DIMENSIONS ),
            m_threads_per_block_dim(
                CudaKernelConfig::DEFAULT_THREADS_PER_BLOCK_DIMENSIONS ),
            m_warp_size( CudaKernelConfig::DEFAULT_WARP_SIZE ),
            m_shared_mem_per_block(
                CudaKernelConfig::DEFAULT_SHARED_MEM_PER_BLOCK ),
            m_max_block_size_limit(
                CudaKernelConfig::DEFAULT_MAX_BLOCK_SIZE_LIMIT )
    {
        CudaKernelConfig::status_t status = this->reset(
            block_dimensions, threads_per_block_dimensions,
            shared_mem_per_block, shared_mem_per_thread,
            max_block_size_limit, warp_size );

        this->doSetNeedsUpdateFlag( true );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            this->doSetPerformsAutoUpdatesFlag( true );
        }
    }

    CudaKernelConfig::CudaKernelConfig(
        CudaKernelConfig::size_type const num_kernel_arguments,
        CudaKernelConfig::purpose_t const purpose,
        CudaKernelConfig::variant_t const variant_flags,
        CudaKernelConfig::size_type const block_dimensions,
        CudaKernelConfig::size_type const threads_per_block_dimensions,
        std::string const& SIXTRL_RESTRICT_REF kernel_name_str,
        CudaKernelConfig::size_type const shared_mem_per_block,
        CudaKernelConfig::size_type const shared_mem_per_thread,
        CudaKernelConfig::size_type const max_block_size_limit,
        CudaKernelConfig::size_type const warp_size,
        std::string const& SIXTRL_RESTRICT_REF config_str ) :
            st::KernelConfigBase( st::ARCHITECTURE_CUDA,
                SIXTRL_ARCHITECTURE_CUDA_STR, num_kernel_arguments, purpose,
                variant_flags, kernel_name_str, config_str ),
            m_blocks(), m_threads_per_block(), m_block_offsts( 0u, 0u, 0u ),
            m_block_dim( CudaKernelConfig::DEFAULT_BLOCK_DIMENSIONS),
            m_threads_per_block_dim(
                CudaKernelConfig::DEFAULT_THREADS_PER_BLOCK_DIMENSIONS ),
            m_warp_size( CudaKernelConfig::DEFAULT_WARP_SIZE ),
            m_shared_mem_per_block(
                CudaKernelConfig::DEFAULT_SHARED_MEM_PER_BLOCK ),
            m_max_block_size_limit(
                CudaKernelConfig::DEFAULT_MAX_BLOCK_SIZE_LIMIT )
    {
        CudaKernelConfig::status_t status = this->reset(
            block_dimensions, threads_per_block_dimensions,
                shared_mem_per_block, shared_mem_per_thread,
                    max_block_size_limit, warp_size );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            this->doSetPerformsAutoUpdatesFlag( true );
        }
    }

    /* --------------------------------------------------------------------- */

    CudaKernelConfig::status_t CudaKernelConfig::reset(
        CudaKernelConfig::size_type const block_dimensions,
        CudaKernelConfig::size_type const threads_per_block_dimensions,
        CudaKernelConfig::size_type const shared_mem_per_block,
        CudaKernelConfig::size_type const shared_mem_per_thread,
        CudaKernelConfig::size_type const max_block_size_limit,
        CudaKernelConfig::size_type const warp_size )
    {
        using size_t = CudaKernelConfig::size_type;

        CudaKernelConfig::status_t status = st::ARCH_STATUS_SUCCESS;

        size_t temp_block_dims   = this->blockDimensions();
        size_t temp_threads_dims= this->threadsPerBlockDimensions();
        size_t temp_shared_mem_per_block = this->m_shared_mem_per_block;
        size_t temp_shared_mem_per_thread = this->m_shared_mem_per_thread;
        size_t temp_max_block_size_limit = this->m_max_block_size_limit;
        size_t temp_warp_size = this->m_warp_size;

        if( block_dimensions != temp_block_dims )
        {
            if( ( block_dimensions >= size_t{ 1 } ) &&
                ( block_dimensions <= size_t{ 3 } ) )
            {
                temp_block_dims = block_dimensions;
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        if( threads_per_block_dimensions != temp_threads_dims)
        {
            if( ( threads_per_block_dimensions >= size_t{ 1 } ) &&
                ( threads_per_block_dimensions <= size_t{ 3 } ) )
            {
                temp_threads_dims= threads_per_block_dimensions;
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        if( shared_mem_per_block != temp_shared_mem_per_block )
        {
            temp_shared_mem_per_block = shared_mem_per_block;
        }

        if( shared_mem_pr_thread != temp_shared_mem_per_thread )
        {
            temp_shared_mem_per_thread = shared_mem_per_thread;
        }

        if( max_block_size_limit != temp_max_block_size_limit )
        {
            temp_max_block_size_limit = max_block_size_limit;
        }

        if( warp_size != temp_warp_size )
        {
            if( warp_size > size_t{ 0 } )
            {
                temp_warp_size = warp_size;
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            bool needs_update = false;

            if( temp_block_dims != this->blockDimensions() )
            {
                this->m_block_dim = temp_block_dims;
                needs_update = true;
            }

            if( temp_threads_dims!= this->threadsPerBlockDimensions() )
            {
                this->m_threads_per_block_dim = temp_threads_dim;
                needs_update = true;
            }

            if( temp_shared_mem_per_block != this->sharedMemPerBlock() )
            {
                this->m_shared_mem_per_block = temp_shared_mem_per_block;
                needs_update = true;
            }

            if( temp_shared_mem_per_thread != this->sharedMemPerThread() )
            {
                this->m_shared_mem_per_thread = temp_shared_mem_per_thread;
                needs_update = true;
            }

            if( temp_max_block_size_limit != this->maxBlockSizeLimit() )
            {
                this->m_max_block_size_limit = temp_max_block_size_limit;
                needs_update = true;
            }

            if( temp_warp_size != this->warpSize() )
            {
                this->m_warp_size = temp_warp_size;
                needs_update;
            }

            if( needs_update )
            {
                status = this->doSetNeedsUpdate();
            }
        }

        return status;
    }

    CudaKernelConfig::status_t CudaKernelConfig::setBlockDimensions(
        CudaKernelConfig::size_type const block_dimensions )
    {
        using size_t = CudaKernelConfig::size_type;

        CudaKernelConfig::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( block_dimensions == this->blockDimensions() )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }
        else if( ( block_dimensions >= size_t{ 1 } ) &&
                 ( block_dimensions <= size_t{ 3 } ) )
        {
            this->m_block_dim = block_dimensions;
            status = this->doSetNeedsUpdate();
        }

        return status;
    }

    CudaKernelConfig::status_t CudaKernelConfig::setThreadsPerBlockDimensions(
        CudaKernelConfig::size_type const threads_per_block_dims )
    {
        using size_t = CudaKernelConfig::size_type;

        CudaKernelConfig::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( threads_per_block_dims == this->threadsPerBlockDimensions() )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }
        else if( ( threads_per_block_dims >= size_t{ 1 } ) &&
                 ( threads_per_block_dims <= size_t{ 3 } ) )
        {
            this->m_threads_per_block_dim = threads_per_block_dims;
            status = this->doSetNeedsUpdate();
        }

        return status;
    }

    CudaKernelConfig::status_t CudaKernelConfig::setGridDimensions(
        CudaKernelConfig::size_type const block_dims,
        CudaKernelConfig::size_type const threads_per_block_dims )
    {
        using size_t = CudaKernelConfig::size_type;

        CudaKernelConfig::status_t status = st::ARCH_STATUS_SUCCESS;

        size_t temp_block_dims = this->blockDimensions();
        size_t temp_threads_dims = this->threadsPerBlockDimensions();

        if( block_dimensions != temp_block_dims )
        {
            if( ( block_dimensions >= size_t{ 1 } ) &&
                ( block_dimensions <= size_t{ 3 } ) )
            {
                temp_block_dims = block_dimensions;
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        if( threads_per_block_dimensions != this->threadsPerBlockDimensions() )
        {
            if( ( threads_per_block_dimensions >= size_t{ 1 } ) &&
                ( threads_per_block_dimensions <= size_t{ 3 } ) )
            {
                temp_threads_dims= threads_per_block_dimensions;
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            bool needs_update = false;

            if( temp_block_dims != this->blockDimensions() )
            {
                this->m_block_dim = temp_block_dims;
                needs_update = true;
            }

            if( temp_threads_dims!= this->threadsPerBlockDimensions() )
            {
                this->m_threads_per_block_dim = temp_threads_dim;
                needs_update = true;
            }

            if( needs_update )
            {
                status = this->doSetNeedsUpdate();
            }
        }

        return status;
    }

    CudaKernelConfig::status_t CudaKernelConfig::setSharedMemPerBlock(
        CudaKernelConfig::size_type const shared_mem_per_block )
    {
        CudaKernelConfig::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( shared_mem_per_block == this->m_shared_mem_per_block )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }
        else
        {
            this->m_shared_mem_per_block = shared_mem_per_block;
            status = this->doSetNeedsUpdate();
        }

        return status;
    }

    CudaKernelConfig::status_t CudaKernelConfig::setSharedMemPerThread(
        CudaKernelConfig::size_type const shared_mem_per_thread )
    {
        CudaKernelConfig::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( shared_mem_per_thread == this->m_shared_mem_per_thread )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }
        else
        {
            this->m_shared_mem_per_thread = shared_mem_per_thread;
            status = this->doSetNeedsUpdate();
        }

        return status;
    }

    CudaKernelConfig::status_t CudaKernelConfig::setMaxBlockSizeLimit(
        CudaKernelConfig::size_type const max_block_size_limit )
    {
        CudaKernelConfig::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( max_block_size_limit == this->m_max_block_size_limit )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }
        else
        {
            this->m_max_block_size_limit = max_block_size_limit;
            status = this->doSetNeedsUpdate();
        }

        return status;
    }

    CudaKernelConfig::status_t CudaKernelConfig::setWarpSize(
        CudaKernelConfig::size_type const warp_size )
    {
        CudaKernelConfig::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( warp_size == this->warpSize() )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }
        else if( warp_size > CudaKernelConfig::size_type{ 0 } )
        {
            this->m_warp_size = warp_size;
            status = this->doSetNeedsUpdate();
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    CudaKernelConfig::status_t CudaKernelConfig::setGrid(
        ::dim3 const& SIXTRL_RESTRICT_REF blocks,
        ::dim3 const& SIXTRL_RESTRICT_REF threads_per_block,
        ::dim3 const& SIXTRL_RESTRICT_REF block_offsets )
    {
        using _this_t = CudaKernelConfig;
        using  size_t = _this_t::size_type;

        _this_t::status_t status = st::ARCH_STATUS_SUCCESS;

        ::dim3 temp_blocks = this->m_blocks;
        ::dim3 temp_block_offsts = this->m_block_offsts;
        ::dim3 temp_threads_per_block = this->m_threads_per_block;

        size_t const block_dims= this->blockDimensions();
        size_t const threads_dims= this->theadsDimensions();

        if( !_this_t::AreDim3ObjectsEqual( blocks, temp_blocks, num_blocks ) )
        {
            status = _this_t::AssignToDim3( temp_blocks, blocks_dim, blocks.x,
                     blocks.y, blocks.z, size_t{ 1 }  );
        }

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( !_this_t::AreDim3ObjectsEqual( threads_per_block,
                 temp_threads_per_block, threads_dims) ) )
        {
            status = CudaKernelConfig::AssignToDim3( temp_threads_per_block,
                threads_dim, threads_per_block.x, threads_per_block.y,
                    threads_per_block.z, size_t{ 1 } );
        }

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( !_this_t::AreDim3ObjectsEqual(
                block_offsets, temp_block_offsets, block_dims) ) )
        {
            status = CudaKernelConfig::AssignToDim3( temp_block_offsets,
                blocks_dim, block_offsets.x, block_offsets.y,
                    block_offsets.z, size_t{ 0 } );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            bool needs_update = false;

            if( !_this_t::AreDim3ObjectsEqual(
                    temp_blocks, this->m_blocks, block_dims) )
            {
                this->m_blocks = temp_blocks;
                needs_update = true;
            }

            if( !_this_t::AreDim3ObjectsEqual( temp_threads_per_block,
                    this->m_threads_per_block, threads_dims) )
            {
                this->m_threads_per_block = temp_threads_per_block;
                needs_update = true;
            }

            if( !_this_t::AreDim3ObjectsEqual(
                    temp_block_offsets, this->m_block_offsts, block_dims) )
            {
                this->m_block_offsets = temp_block_offsets;
                needs_update = true;
            }

            if( needs_update )
            {
                status = this->doSetNeedsUpdate();
            }
        }

        return status;
    }

    CudaKernelConfig::status_t CudaKernelConfig::setBlocks(
        ::dim3 const& blocks ) SIXTRL_NOEXCEPT
    {
        return this->setBlocks( blocks.x, blocks.y, blocks.z );
    }

    CudaKernelConfig::status_t CudaKernelConfig::setBlocks(
        CudaKernelConfig::size_type const x_blocks,
        CudaKernelConfig::size_type const y_blocks,
        CudaKernelConfig::size_type const z_blocks )  SIXTRL_NOEXCEPT
    {
        CudaKernelConfig::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->blockDimensions() > CudaKernelConfig::size_type{ 0 } )
        {
            static constexpr unsigned int ONE = unsigned int{ 1 };

            if( ( x_blocks != this->m_blocks.x ) ||
                ( y_blocks != this->m_blocks.y ) ||
                ( z_blocks != this->m_blocks.z ) )
            {
                ::dim3 temp_blocks;

                status = CudaKernelConfig::AssignToDim3( temp_blocks,
                    this->blockDimensions(), x_blocks, y_blocks, z_blocks );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    this->m_blocks = temp_blocks;
                    this->doSetNeedsUpdate();
                }
            }
            else if( ( this->m_blocks.x >= ONE ) &&
                     ( this->m_blocks.y >= ONE ) &&
                     ( this->m_blocks.z >= ONE ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    CudaKernelConfig::status_t CudaKernelConfig::setThreadsPerBlock(
        ::dim3 const& SIXTRL_RESTRICT_REF threads_per_block ) SIXTRL_NOEXCEPT
    {
        return this->setThreadsPerBlock( threads_per_block.x,
            threads_per_block.y, threads_per_block.z );
    }

    CudaKernelConfig::status_t CudaKernelConfig::setThreadsPerBlock(
        CudaKernelConfig::size_type const x_threads,
        CudaKernelConfig::size_type const y_threads,
        CudaKernelConfig::size_type const z_threads ) SIXTRL_NOEXCEPT
    {
        CudaKernelConfig::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->threadsPerBlockDimensions() >
            CudaKernelConfig::size_type{ 0 } )
        {
            static constexpr unsigned int ONE = unsigned int{ 1 };

            if( ( x_threads != this->m_threads_per_block.x ) ||
                ( y_threads != this->m_threads_per_block.y ) ||
                ( z_threads != this->m_threads_per_block.z ) )
            {
                ::dim3 temp_threads;

                status = CudaKernelConfig::AssignToDim3( temp_threads,
                    this->threadsPerBlockDimensions(),
                        x_threads.x, y_threads, z_threads, ONE );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    this->m_threads_per_block = temp_threads;
                    this->doSetNeedsUpdate();
                }
            }
            else if( ( this->m_threads_per_block.x >= ONE ) &&
                     ( this->m_threads_per_block.y >= ONE ) &&
                     ( this->m_threads_per_block.z >= ONE ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    CudaKernelConfig::status_t CudaKernelConfig::setBlockOffsets(
        ::dim3 const& SIXTRL_RESTRICT_REF block_offsets ) SIXTRL_NOEXCEPT
    {
        return this->setBlockOffsets(
            block_offsets.x, block_offsets.y, block_offsets.z );
    }

    CudaKernelConfig::status_t CudaKernelConfig::setThreadsPerBlock(
        CudaKernelConfig::size_type const x_block_offset,
        CudaKernelConfig::size_type const y_block_offset,
        CudaKernelConfig::size_type const z_block_offset ) SIXTRL_NOEXCEPT
    {
        CudaKernelConfig::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        CudaKernelConfig::size_type const block_dims = this->blockDimensions();

        if( block_dims > CudaKernelConfig::size_type{ 0 } )
        {
            if( ( x_block_offset != this->m_block_offsets.x ) ||
                ( y_block_offset != this->m_block_offsets.y ) ||
                ( z_block_offset != this->m_block_offsets.z ) )
            {
                ::dim3 temp_block_offsets;

                status = CudaKernelConfig::AssignToDim3( temp_block_offsets,
                    block_dims, x_block_offset, y_block_offset, z_block_offset,
                        CudaKernelConfig::size_type{ 0 } );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    this->m_block_offsets = temp_block_offsets;
                    this->doSetNeedsUpdate();
                }
            }
            else
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    CudaKernelConfig::status_t CudaKernelConfig::doUpdate()
    {
        using size_t = CudaKernelConfig::size_type;

        CudaKernelConfig::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        size_t const block_dims = this->blockDimensions();
        size_t const threads_dims = this->threadsPerBlockDimensions();

        if( ( block_dims >= size_t{ 1 } ) &&
            ( block_dims <= size_t{ 3 } ) &&
            ( threads_dims >= size_t{ 1 } ) &&
            ( threads_dims <= size_t{ 3 } ) &&
            ( this->totalNumBlocks() > size_t{ 0 } ) &&
            ( this->totalNumThreadsPerBlock() > size_t{ 0 } ) )
        {
            this->doSetNeedsUpdateFlag( false );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    CudaKernelConfig::status_t CudaKernelConfig::doPrintToOutputStream(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        using size_t = KernelConfigBase::size_type;

        CudaKernelConfig::status_t status =
            st::KernelConfigBase::doPrintToOutputStream( output );

        if( status != st::ARCH_STATUS_SUCCESS ) return status;

        if( this->blockDimensions() > size_t{ 0 }  )
        {
            output << "Blocks dimensions     : "
                   << this->blockDimensions() << "\r\n"
                   << "Blocks                : [ "
                   << std::setw( 6 ) << this->m_blocks.x;

            if( this->blockDimensions() > size_t{ 1 } )
            {
                output << "," << std::setw( 6 ) << this->m_blocks.y;
            }

            if( this->blockDimensions() > size_t{ 2 } )
            {
                output << "," << std::setw( 6 ) << this->m_blocks.z;
            }

            output << " ]\r\n";

            if( this->hasBlockOffsets() )
            {
                output << "Block offsets         : [ "
                       << std::setw( 6 ) << this->m_block_offsets.x;

                if( this->blockDimensions() > size_t{ 1 } )
                {
                    output << "," << std::setw( 6 ) << this->m_block_offsets.y;
                }

                if( this->blockDimensions() > size_t{ 2 } )
                {
                    output << "," << std::setw( 6 ) << this->m_block_offsets.z;
                }

                output << " ]\r\n";
            }
        }

        if( this->threadsPerBlockDimensions() > size_t{ 0 } )
        {
            size_t const threads_dims = this->threadsPerBlockDimensions();

            output << "Threads/block dim.    : " << threads_dims << "\r\n"
                   << "Threads/block         : [ "
                   << std::setw( 6 ) << this->m_threads_per_block.x;

            if( this->blockDimensions() > size_t{ 1 } )
            {
                output << "," << std::setw( 6 ) << this->m_threads_per_block.y;
            }

            if( this->blockDimensions() > size_t{ 2 } )
            {
                output << "," << std::setw( 6 ) << this->m_threads_per_block.z;
            }

            output << " ]\r\n";
        }

        output << "Shared mem/block      : "
               << this->sharedMemPerBlock() << " bytes\r\n";

        if( this->maxBlockSizeLimit() > size_t{ 0 } )
        {
            output << "Max block size limit  : "
               << this->maxBlockSizeLimit() << "\r\n";
        }

        output << "Warp Size             : "
               << this->warpSize() << " threads\r\n";

        return status;
    }
}

#endif /* C++, Host */

/* end: sixtracklib/cuda/control/kernel_config.cpp */
