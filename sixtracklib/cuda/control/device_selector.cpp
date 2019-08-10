#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/cuda/control/device_selector.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <memory>
    #include <mutex>
    #include <stdexcept>
    #include <thread>
    #include <utility>

    #include <cuda_runtime_api.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_info.hpp"
    #include "sixtracklib/common/control/node_store.hpp"
    #include "sixtracklib/cuda/definitions.h"
    #include "sixtracklib/cuda/control/node_info.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    CudaDeviceSelector::CudaDeviceSelector(
        CudaDeviceSelector::node_store_t* SIXTRL_RESTRICT ptr_node_store ) :
        m_node_store( ( ptr_node_store != nullptr )
            ? *ptr_node_store : st::NodeStore_get() ),
        m_num_available_devices( st::CudaDeviceSelector::size_type{ 0 } ),
        m_selected_device(  st::CudaDeviceSelector::ILLEGAL_CUDA_DEVICE_INDEX ),
        m_min_device_index( st::CudaDeviceSelector::ILLEGAL_CUDA_DEVICE_INDEX ),
        m_max_device_index( st::CudaDeviceSelector::ILLEGAL_CUDA_DEVICE_INDEX )
    {
        using  _this_t = st::CudaDeviceSelector;
        using status_t = _this_t::status_t;
        using lock_t   = _this_t::lock_t;

        lock_t lock( *this->nodeStore().lockable() );
        SIXTRL_ASSERT( this->nodeStore().checkLock( lock ) );

        status_t const status = this->reset( lock );

        if( status != st::ARCH_STATUS_SUCCESS )
        {
            throw std::runtime_error( "unable to init cuda device selector" );
        }

        SIXTRL_ASSERT( ( this->checkLock( lock ) ) &&
            ( ( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( this->m_selected_device !=
                   _this_t::ILLEGAL_CUDA_DEVICE_INDEX ) &&
                ( this->m_min_device_index !=
                   _this_t::ILLEGAL_CUDA_DEVICE_INDEX ) &&
                ( this->m_max_device_index !=
                   _this_t::ILLEGAL_CUDA_DEVICE_INDEX ) &&
                ( this->m_min_device_index <= this->m_selected_device ) &&
                ( this->m_selected_device <= this->m_max_device_index ) ) ||
              ( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( this->m_selected_device ==
                    _this_t::ILLEGAL_CUDA_DEVICE_INDEX )
                ( this->m_min_device_index ==
                    _this_t::ILLEGAL_CUDA_DEVICE_INDEX ) &&
                ( this->m_max_device_index ==
                    _this_t::ILLEGAL_CUDA_DEVICE_INDEX ) ) ) );
    }

    CudaDeviceSelector::status_t CudaDeviceSelector::reset(
        CudaDeviceSelector::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        using _this_t = st::CudaDeviceSelector;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        int temp_num_devices = int{ -1 };

        ::cudaError_t err = ::cudaGetDeviceCount( &temp_num_devices );

        if( ( err == ::cudaSuccess ) &&  ( temp_num_devices > 0 ) &&
            ( this->nodeStore().checkLock( lock ) ) )
        {
            this->m_min_device_index = int{ 0 };
            this->m_max_device_index = temp_num_devices - 1;
            this->m_num_available_devices = temp_num_devices;

            int current_device_index = int{ -1 };

            err = ::cudaGetDevice( &current_device_index );

            if( ( err == ::cudaSuccess ) &&
                ( current_device_index >= this->m_min_device_index ) &&
                ( current_device_index <= this->m_max_device_index ) )
            {
                this->m_selected_device = current_device_index;
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    CudaDeviceSelector::status_t CudaDeviceSelector::reset(
        CudaDeviceSelector::node_store_t& SIXTRL_RESTRICT_REF node_store )
    {
        CudaDeviceSelector::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( &node_store != this->ptrNodeStore() ) &&
            ( this->nodeStore().lockable() != node_store.lockable() ) )
        {
            CudaDeviceSelector::lock_t new_store_lock( *node_store.lockable() );
            CudaDeviceSelector::lock_t old_store_lock(
                *this->nodeStore().lockable() );

            status = this->reset( old_store_lock, node_store, new_store_lock );
        }

        return status;
    }

    CudaDeviceSelector::status_t CudaDeviceSelector::reset(
        CudaDeviceSelector::lock_t& SIXTRL_RESTRICT_REF old_store_lock,
        CudaDeviceSelector::node_store_t& SIXTRL_RESTRICT_REF node_store,
        CudaDeviceSelector::lock_t const& SIXTRL_RESTRICT_REF new_store_lock )
    {
        CudaDeviceSelector::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( &node_store != this->ptrNodeStore() ) &&
            (  node_store.checkLock( new_store_lock ) ) &&
            (  this->nodeStore().checkLock( old_store_lock ) ) )
        {
            this->m_node_store = node_store;
            old_store_lock.unlock();

            status = this->reset( new_store_lock );
        }

        return status;
    }

    CudaDeviceSelector::status_t CudaDeviceSelector::resetIfDifferentNodeStore(
        CudaDeviceSelector::node_store_t& SIXTRL_RESTRICT_REF node_store )
    {
        CudaDeviceSelector::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->ptrNodeStore() == &node_store )
        {
            status = st::ARCH_STATUS_SUCCESS:
        }
        else if( this->nodeStore().lockable() != node_store.lockable() )
        {
            CudaDeviceSelector::lock_t new_store_lock(
                *this->nodeStore().lockable() );

            CudaDeviceSelector::lock_t old_store_lock(
                *this->nodeStore().lockable() );

            this->m_node_store = node_store;
            old_store_lock.unlock();

            status = this->reset( new_store_lock, node_store );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    CudaDeviceSelector::status_t CudaDeviceSelector::setDeviceIndex(
        CudaDeviceSelector::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaDeviceSelector::device_index_t const new_device_index )
    {
        using _this_t = st::CudaDeviceSelector;
        using size_t = _this_t::size_type;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->m_num_available_devices > size_t{ 0 } ) &&
            ( this->m_min_device_index <= new_device_index ) &&
            ( this->m_max_device_index >= new_device_index ) )
        {
            if( this->m_selected_device != new_device_index )
            {
                ::cudaError_t err = ::cudaSetDevice( new_device_index );

                if( err == ::cudaSuccess )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
            else
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }
}

#endif /* end C++, Host */

/* end: sixtracklib/cuda/control/device_selector.cpp */
