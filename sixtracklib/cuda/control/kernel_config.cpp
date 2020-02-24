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

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace  st   = SIXTRL_CXX_NAMESPACE;
        using _this_t   = st::CudaKernelConfig;
        using _size_t   = _this_t::size_type;
        using _status_t = _this_t::status_t;
    }

    CudaKernelConfig::CudaKernelConfig(
        _size_t const block_dimensions,
        _size_t const threads_per_block_dimensions,
        _size_t const shared_mem_per_block, _size_t const max_block_size_limit,
        _size_t const warp_size, char const* SIXTRL_RESTRICT config_str ) :
        st::KernelConfigBase( st::ARCHITECTURE_CUDA,
            SIXTRL_ARCHITECTURE_CUDA_STR, config_str, block_dimensions,
            threads_per_block_dimensions ),
            m_blocks(), m_threads_per_block(),
            m_warp_size( CudaKernelConfig::DEFAULT_WARP_SIZE ),
            m_shared_mem_per_block( shared_mem_per_block ),
            m_max_block_size_limit( max_block_size_limit )
    {
        if( warp_size > _size_t{ 0 } ) this->setWarpSize( warp_size );
    }

    CudaKernelConfig::CudaKernelConfig(
        std::string const& SIXTRL_RESTRICT_REF name_str,
        _size_t const num_kernel_arguments,
        _size_t const block_dimensions,
        _size_t const threads_per_block_dimensions,
        _size_t const shared_mem_per_block,
        _size_t const max_block_size_limit,
        _size_t const warp_size,
        char const* SIXTRL_RESTRICT config_str ) :
        st::KernelConfigBase( st::ARCHITECTURE_CUDA,
            SIXTRL_ARCHITECTURE_CUDA_STR, config_str, block_dimensions,
            threads_per_block_dimensions ),
            m_blocks(), m_threads_per_block(),
            m_warp_size( CudaKernelConfig::DEFAULT_WARP_SIZE ),
            m_shared_mem_per_block( shared_mem_per_block ),
            m_max_block_size_limit( max_block_size_limit )
    {
        if( warp_size > _size_t{ 0 } ) this->setWarpSize( warp_size );
        this->setNumArguments( num_kernel_arguments );
        this->setName( name_str );
    }

    CudaKernelConfig::CudaKernelConfig(
        char const* SIXTRL_RESTRICT name_str,
        _size_t const num_kernel_arguments,
        _size_t const block_dimensions,
        _size_t const threads_per_block_dimensions,
        _size_t const shared_mem_per_block,
        _size_t const max_block_size_limit,
        _size_t const warp_size, char const* SIXTRL_RESTRICT config_str ) :
        st::KernelConfigBase( st::ARCHITECTURE_CUDA,
            SIXTRL_ARCHITECTURE_CUDA_STR, config_str, block_dimensions,
            threads_per_block_dimensions ),
            m_blocks(), m_threads_per_block(),
            m_warp_size( CudaKernelConfig::DEFAULT_WARP_SIZE ),
            m_shared_mem_per_block( shared_mem_per_block ),
            m_max_block_size_limit( max_block_size_limit )
    {
        if( warp_size > _size_t{ 0 } ) this->setWarpSize( warp_size );
        this->setNumArguments( num_kernel_arguments );
        this->setName( name_str );
    }

    _size_t CudaKernelConfig::sharedMemPerBlock() const SIXTRL_NOEXCEPT
    {
        return this->m_shared_mem_per_block;
    }

    void CudaKernelConfig::setSharedMemPerBlock(
        _size_t const shared_mem_per_block ) SIXTRL_NOEXCEPT
    {
        this->m_shared_mem_per_block = shared_mem_per_block;
    }

    _size_t CudaKernelConfig::maxBlockSizeLimit() const SIXTRL_NOEXCEPT
    {
        return this->m_max_block_size_limit;
    }

    void CudaKernelConfig::setMaxBlockSizeLimit(
        _size_t const max_block_size_limit ) SIXTRL_NOEXCEPT
    {
        this->m_max_block_size_limit = max_block_size_limit;
    }

    ::dim3 const& CudaKernelConfig::blocks() const SIXTRL_NOEXCEPT
    {
        return this->m_blocks;
    }

    ::dim3 const& CudaKernelConfig::threadsPerBlock() const SIXTRL_NOEXCEPT
    {
        return this->m_threads_per_block;
    }

    ::dim3 const* CudaKernelConfig::ptrBlocks() const SIXTRL_NOEXCEPT
    {
        return ( !this->needsUpdate() ) ? &this->m_blocks : nullptr;
    }

    ::dim3 const* CudaKernelConfig::ptrThreadsPerBlock() const SIXTRL_NOEXCEPT
    {
        return ( !this->needsUpdate() ) ? &this->m_threads_per_block : nullptr;
    }

    _size_t CudaKernelConfig::warpSize() const SIXTRL_NOEXCEPT
    {
        return this->m_warp_size;
    }

    void CudaKernelConfig::setWarpSize( _size_t const warp_s ) SIXTRL_NOEXCEPT
    {
        if( warp_s > _size_t{ 0 } ) this->m_warp_size = warp_s;
    }

    _status_t CudaKernelConfig::doUpdate()
    {
        bool success = false;

        _size_t const items_dim = this->workItemsDim();
        _size_t const wgroups_dim = this->workGroupsDim();

        if( ( items_dim > _size_t{ 0 } ) && ( wgroups_dim == items_dim ) )
        {
            _size_t num_blocks[]  = {_size_t{ 1 }, _size_t{ 1 }, _size_t{ 1 } };
            _size_t num_threads[] = {_size_t{ 1 }, _size_t{ 1 }, _size_t{ 1 } };

            success = true;

            for( _size_t ii = _size_t{ 0 } ; ii < items_dim ; ++ii )
            {
                _size_t const wgsize = this->workGroupSize( ii );
                _size_t const num_items = this->numWorkItems( ii );

                if( ( wgsize == 0u ) || ( num_items == 0u ) )
                {
                    success = false;
                    break;
                }

                num_threads[ ii ] = wgsize;
                num_blocks[ ii ]  = num_items / wgsize;

                if( ( num_items * wgsize ) < num_blocks[ ii ] )
                {
                    ++num_blocks[ ii ];
                }
            }

            if( success )
            {
                _size_t const total_num_blocks =
                    num_blocks[ 0 ] * num_blocks[ 1 ] * num_blocks[ 2 ];

                this->m_blocks.x = num_blocks[ 0 ];
                this->m_blocks.y = num_blocks[ 1 ];
                this->m_blocks.z = num_blocks[ 2 ];

                _size_t const threads_per_block =
                    num_threads[ 0 ] * num_threads[ 1 ] * num_threads[ 2 ];

                this->m_threads_per_block.x = num_threads[ 0 ];
                this->m_threads_per_block.y = num_threads[ 1 ];
                this->m_threads_per_block.z = num_threads[ 2 ];

                success = ( ( total_num_blocks  > _size_t{ 0 } ) &&
                            ( threads_per_block > _size_t{ 0 } ) );
            }
        }

        return ( success )
            ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    _status_t CudaKernelConfig::setGrid(
        _size_t const x_blocks, _size_t const x_threads_per_block,
        _size_t const y_blocks, _size_t const y_threads_per_block,
        _size_t const z_blocks, _size_t const z_threads_per_block )
    {
        _status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( x_blocks > _size_t{ 0 } ) &&
            ( x_threads_per_block > _size_t{ 0 } ) &&
            ( y_blocks > _size_t{ 0 } ) &&
            ( y_threads_per_block > _size_t{ 0 } ) &&
            ( z_blocks > _size_t{ 0 } ) &&
            ( z_threads_per_block > _size_t{ 0 } ) )
        {
            status = this->setNumWorkItems(
                x_blocks * x_threads_per_block,
                y_blocks * y_threads_per_block,
                z_blocks * z_threads_per_block );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->setWorkGroupSizes( x_threads_per_block,
                    y_threads_per_block, z_threads_per_block );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                this->m_blocks.x = x_blocks;
                this->m_blocks.y = y_blocks;
                this->m_blocks.z = z_blocks;

                this->m_threads_per_block.x = x_threads_per_block;
                this->m_threads_per_block.y = y_threads_per_block;
                this->m_threads_per_block.z = z_threads_per_block;
            }
        }

        return status;
    }

    _status_t CudaKernelConfig::setGrid(
        ::dim3 const& SIXTRL_RESTRICT_REF num_blocks,
        ::dim3 const& SIXTRL_RESTRICT_REF threads_per_block )
    {
        _status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( num_blocks.x > _size_t{ 0 } ) &&
            ( threads_per_block.x > _size_t{ 0 } ) &&
            ( num_blocks.y > _size_t{ 0 } ) &&
            ( threads_per_block.y > _size_t{ 0 } ) &&
            ( num_blocks.z > _size_t{ 0 } ) &&
            ( threads_per_block.z > _size_t{ 0 } ) )
        {
            status = this->setNumWorkItems(
                num_blocks.x * threads_per_block.x,
                num_blocks.y * threads_per_block.y,
                num_blocks.z * threads_per_block.z );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->setWorkGroupSizes( threads_per_block.x,
                    threads_per_block.y, threads_per_block.z );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                this->m_blocks = num_blocks;
                this->m_threads_per_block = threads_per_block;
            }
        }

        return status;
    }

    _size_t CudaKernelConfig::totalNumBlocks() const SIXTRL_NOEXCEPT
    {
        return ( !this->needsUpdate() )
            ? ( this->m_blocks.x * this->m_blocks.y * this->m_blocks.z )
            : _size_t{ 0 };
    }

    _size_t CudaKernelConfig::totalNumThreadsPerBlock() const SIXTRL_NOEXCEPT
    {
        return ( !this->needsUpdate() )
            ? ( this->m_threads_per_block.x * this->m_threads_per_block.y *
                this->m_threads_per_block.z )
            : _size_t{ 0 };
    }

    _size_t CudaKernelConfig::totalNumThreads() const SIXTRL_NOEXCEPT
    {
        return this->totalNumBlocks() * this->totalNumThreadsPerBlock();
    }

    void CudaKernelConfig::doPrintToOutputStream(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        using size_t = KernelConfigBase::size_type;

        if( this->needsUpdate() )
        {
            output << "!!! WARNING: Preliminary values, "
                   << "call update() before using !!!\r\n\r\n";
        }

        if( this->hasName() )
        {
            output << "kernel name          : " << this->name() << "\r\n";
        }

        output << "num kernel arguments : "
               << std::setw( 6 ) << this->numArguments() << "\r\n";

        if( this->workItemsDim() > _size_t{ 0 } )
        {
            output << "block dim            : " << this->workItemsDim()
                   << "blocks               : [ "
                   << std::setw( 5 ) << this->blocks().x << " / "
                   << std::setw( 5 ) << this->blocks().y << " / "
                   << std::setw( 5 ) << this->blocks().z << " ]\r\n";
        }

        if( this->workGroupsDim() > _size_t{ 0 } )
        {
            output << "threads grid dim     : " << this->workItemsDim()
                   << "threads per block    : [ "
                   << std::setw( 5 ) << this->threadsPerBlock().x << " / "
                   << std::setw( 5 ) << this->threadsPerBlock().y << " / "
                   << std::setw( 5 ) << this->threadsPerBlock().z
                   << " ]\r\n";
        }

        output << "shared mem per block : "
               << std::setw( 6 ) << this->sharedMemPerBlock()
               << " bytes\r\n"
               << "warp size            : "
               << std::setw( 6 ) << this->warpSize() << " threads\r\n";

        if( this->maxBlockSizeLimit() > _size_t{ 0 } )
        {
            output << "max block size limit : " << std::setw( 6 )
                   << this->maxBlockSizeLimit() << "\r\n";
        }

        return;
    }
}

#endif /* C++, Host */

/* end: sixtracklib/cuda/control/kernel_config.cpp */
