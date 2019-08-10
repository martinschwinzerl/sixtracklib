#include "sixtracklib/cuda/control/node_info.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>

#include <cuda.h>
#include <cuda_runtime.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_id.hpp"
#include "sixtracklib/common/control/node_info.hpp"
#include "sixtracklib/common/control/node_store.hpp"
#include "sixtracklib/common/control/arch_info.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    std::unique_ptr< CudaNodeInfo::node_info_base_t > MakeCudaNodeInfo(
        CudaNodeInfo::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaNodeInfo::cuda_dev_index_t const dev_index,
        const CudaNodeInfo::node_store_t *const SIXTRL_RESTRICT node_store )
    {
        using _this_t = st::CudaNodeInfo;
        using node_info_base_t = _this_t::node_info_base_t;
        using node_store_t = _this_t::node_store_t;

        node_store_t const& nodes_store = ( ptr_node_store != nullptr )
            ? *ptr_node_store : st::NodeStore_get_const();

        if( ( dev_index >= _this_t::cuda_dev_index_t{ 0 } ) &&
            ( dev_index != st::NodeStore::UNDEFINED_INDEX ) &&
            ( nodes_store.checkLock( lock ) ) &&
            ( nodes_store.hasArchitecture( lock, st::ARCHITECTURE_CUDA ) ) )
        {
            int temp_num_devices = int{ -1 };
            ::cudaError_t err = ::cudaGetDeviceCount( &temp_num_devices );

            if( ( err == ::cudaSuccess ) && ( temp_num_devices > dev_index ) )
            {
                return std::unique_ptr< node_info_base_t >(
                    new st::CudaNodeInfo( dev_index ) );
            }
        }

        return std::unique_ptr< node_info_base_t >( nullptr );
    }

    std::unique_ptr< CudaNodeInfo::node_info_base_t >
    CudaNodeInfo::MakeCudaNodeInfo(
        CudaNodeInfo::device_index_t const dev_index,
        const CudaNodeInfo::node_store_t *const SIXTRL_RESTRICT ptr_node_store )
    {
        using node_store_t = CudaNodeInfo::node_store_t;
        using lock_t       = CudaNodeInfo::lock_t;

        node_store_t const& nodes_store = ( ptr_node_store != nullptr )
            ? *ptr_node_store : st::NodeStore_get_const();

        lock_t lock( *nodes_store.lockable() );
        return CudaNodeInfo::MakeCudaNodeInfo(
            lock, dev_index, ptr_node_store );
    }

    CudaNodeInfo::CudaNodeInfo(
        CudaNodeInfo::cuda_dev_index_t const cuda_dev_index,
        CudaNodeInfo::device_id_t const device_id ) :
        st::NodeInfoBase( st::ARCHITECTURE_CUDA,
            SIXTRL_ARCHITECTURE_CUDA_STR ), m_device_properties()
    {
        using size_t = st::CudaNodeInfo::size_type;
        using dev_index_t = st::CudaNodeInfo::cuda_dev_index_t;

        if( cuda_dev_index >= dev_index_t{ 0 } )
        {
            CudaNodeInfo::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            ::cudaError_t err = ::cudaSuccess;
            int max_num_devices = int{ 0 };

            err = ::cudaGetDeviceCount( &max_num_devices );

            if( err == ::cudaSuccess )
            {
                if( static_cast< dev_index_t >(
                        max_num_devices ) > cuda_dev_index )
                {
                    status = this->setPlatformId( cuda_dev_index );

                    if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                        ( device_id != st::NodeStore::ILLEGAL_DEVICE_ID ) )
                    {
                        status = this->setDeviceId( device_id );
                    }
                }
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( err == ::cudaSuccess ) )
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;

                err = ::cudaGetDeviceProperties(
                    &this->m_device_properties, cuda_dev_index );

                if( err == ::cudaSuccess )
                {
                    status = this->doInitFromDeviceProperties(
                        this->m_device_properties );
                }
            }

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }
    }

    CudaNodeInfo::status_t CudaNodeInfo::doPrintToOutputStream(
        std::ostream& SIXTRL_RESTRICT_REF output,
        CudaNodeInfo::controller_base_t const* SIXTRL_RESTRICT ptr_ctrl ) const
    {
        CudaNodeInfo::status_t status =
            st::NodeInfoBase::doPrintToOutputStream( output, ptr_ctrl );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            if( this->cudaDeviceIndex() >= CudaNodeInfo::cuda_dev_index_t{ 0 } )
            {
                output << "Cuda dev index  : "
                       << this->cudaDeviceIndex()
                       << "\r\n";
            }
        }
    }

    CudaNodeInfo::status_t CudaNodeInfo::doInitFromDeviceProperties(
        CudaNodeInfo::cuda_dev_index_t const cuda_dev_index,
        ::cudaDeviceProp const& SIXTRL_RESTRICT_REF properties )
    {
        CudaNodeInfo::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( properties.major >= 2 ) && ( properties.minor >= 0 ) )
        {
            std::ostringstream a2str;

            int cuda_driver_version  = int{ 0 };
            int cuda_runtime_version = int{ 0 };

            a2str << "Cuda";

            err = ::cudaDriverGetVersion( &cuda_driver_version );

            if( err == ::cudaSuccess )
            {
                a2str << " :: Driver v" << cuda_driver_version / 1000
                      << "." << ( cuda_driver_version % 1000 ) / 10;
            }

            err = ::cudaRuntimeGetVersion( &cuda_runtime_version );

            if( err == ::cudaSuccess )
            {
                a2str << " :: Runtime v" << cuda_runtime_version / 1000
                      << "." << ( cuda_runtime_version % 1000 ) / 10;
            }

            this->setPlatformName( a2str.str() );

            a2str.str( "" );
            a2str << "compute_capability="
                  << properties.major << "." << properties.minor << "; "
                  << "multiprocessor_count="
                  << properties.multiProcessorCount
                  << ";";

            this->setDescription( a2str.str() );

            if( std::strlen( properties.name ) > size_t{ 0 } )
            {
                a2str.str( "" );
                a2str << properties.name;

                this->setPlatformName( a2str );

                char pci_bus_id[] =
                {
                    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
                };

                err = ::cudaDeviceGetPCIBusId(
                    pci_bus_id, 16u, cuda_dev_index );

                if( err == ::cudaSuccess )
                {
                    a2str << " [" << pci_bus_id << "]";
                    this->doSetUniqueIdStr( &pci_bus_id[ 0 ] );
                }
                else
                {
                    a2str << " device";
                }

                this->setDeviceName( a2str.str() );

                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }
}

/* end: sixtracklib/cuda/control/node_info.cpp */
