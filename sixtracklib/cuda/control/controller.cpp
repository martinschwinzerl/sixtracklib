#include "sixtracklib/cuda/controller.hpp"

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )

#include <cstddef>
#include <cstdlib>

#include

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_id.hpp"
#include "sixtracklib/common/control/kernel_config_key.hpp"
#include "sixtracklib/common/control/kernel_config_store.hpp"
#include "sixtracklib/common/control/controller_base.hpp"
#include "sixtracklib/common/control/node_controller_base.hpp"
#include "sixtracklib/common/control/node_store.hpp"

#include "sixtracklib/cuda/definitions.h"
#include "sixtracklib/cuda/cuda_tools.h"
#include "sixtracklib/cuda/argument.hpp"
#include "sixtracklib/cuda/control/kernel_config_store.hpp"
#include "sixtracklib/cuda/wrappers/controller_wrappers.h"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    CudaController::CudaController(
        char const* config_str ) :
        st::NodeControllerBase( st::ARCHITECTURE_CUDA,
            st::CUDA_ARCHITECTURE_STR, st::CudaKernelConfigStore_get(),
                st::NodeStore_get(), config_str ),
        m_index_to_debug_registers(),
        m_device_selector( st::CudaDeviceSelector_get() )
    {
        CudaController::status_t const status = this->doInitCudaController(
            nullptr, nullptr, config_str );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    CudaController::CudaController(
        CudaController::cuda_dev_index_t const cuda_dev_index,
        char const* config_str ) :
        st::NodeControllerBase( st::ARCHITECTURE_CUDA,
            st::CUDA_ARCHITECTURE_STR, st::CudaKernelConfigStore_get(),
                st::NodeStore_get(), config_str ),
        m_index_to_debug_registers(),
        m_device_selector( st::CudaDeviceSelector_get() )
    {
        CudaController::status_t const status = this->doInitCudaController(
            nullptr, nullptr, config_str, cuda_dev_index );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    CudaController::CudaController(
        CudaController::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        char const* config_str ) :
        st::NodeControllerBase( st::ARCHITECTURE_CUDA,
            st::CUDA_ARCHITECTURE_STR, st::CudaKernelConfigStore_get(),
                st::NodeStore_get(), config_str ),
        m_index_to_debug_registers(),
        m_device_selector( st::CudaDeviceSelector_get() )
    {
        CudaController::status_t const status = this->doInitCudaController(
            nullptr, nullptr, config_str, node_id );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    CudaController::CudaController(
        CudaController::platform_id_t const platform_id,
        CudaController::device_id_t const device_id, char const* config_str ) :
        st::NodeControllerBase( st::ARCHITECTURE_CUDA,
            st::CUDA_ARCHITECTURE_STR, st::CudaKernelConfigStore_get(),
                st::NodeStore_get(), config_str ),
        m_index_to_debug_registers(),
        m_device_selector( st::CudaDeviceSelector_get() )
    {
        CudaController::status_t const status = this->doInitCudaController(
            nullptr, nullptr, config_str, platform_id, device_id );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    CudaController::CudaController(
        CudaController::node_index_t const node_index, char const* config_str,
        CudaController::device_selector_t* SIXTRL_RESTRICT ptr_device_selector,
        CudaController::node_store_t* SIXTRL_RESTRICT ptr_node_store ) :
        st::NodeControllerBase( st::ARCHITECTURE_CUDA,
            st::CUDA_ARCHITECTURE_STR, st::CudaKernelConfigStore_get(),
                st::NodeStore_get(), config_str ),
        m_index_to_debug_registers(),
        m_device_selector( st::CudaDeviceSelector_get() )
    {
        CudaController::status_t const status = this->doInitCudaController(
            ptr_device_selector, ptr_node_store, config_str, node_index );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    /* --------------------------------------------------------------------- */

    CudaController::CudaController(
        std::string const& SIXTRL_RESTRICT_REF config_str ) :
        st::NodeControllerBase( st::ARCHITECTURE_CUDA,
            st::CUDA_ARCHITECTURE_STR, st::CudaKernelConfigStore_get(),
                st::NodeStore_get(), config_str.c_str() ),
        m_index_to_debug_registers(),
        m_device_selector( st::CudaDeviceSelector_get() )
    {
        CudaController::status_t const status = this->doInitCudaController(
            nullptr, nullptr, config_str.c_str() );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    CudaController::CudaController(
        CudaController::cuda_dev_index_t const cuda_dev_index,
        std::string const& SIXTRL_RESTRICT_REF config_str ) :
        st::NodeControllerBase( st::ARCHITECTURE_CUDA,
            st::CUDA_ARCHITECTURE_STR, st::CudaKernelConfigStore_get(),
                st::NodeStore_get(), config_str.c_str() ),
        m_index_to_debug_registers(),
        m_device_selector( st::CudaDeviceSelector_get() )
    {
        CudaController::status_t const status = this->doInitCudaController(
            nullptr, nullptr, config_str.c_str(), cuda_dev_index );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    CudaController::CudaController(
        CudaController::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        std::string const& SIXTRL_RESTRICT_REF config_str ) :
        st::NodeControllerBase( st::ARCHITECTURE_CUDA,
            st::CUDA_ARCHITECTURE_STR, st::CudaKernelConfigStore_get(),
                st::NodeStore_get(), config_str.c_str() ),
        m_index_to_debug_registers(),
        m_device_selector( st::CudaDeviceSelector_get() )
    {
        CudaController::status_t const status = this->doInitCudaController(
            nullptr, nullptr, config_str.c_str(), node_id );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    CudaController::CudaController(
        CudaController::platform_id_t const platform_id,
        CudaController::device_id_t const device_id,
        std::string const& SIXTRL_RESTRICT_REF config_str ) :
        st::NodeControllerBase( st::ARCHITECTURE_CUDA,
            st::CUDA_ARCHITECTURE_STR, st::CudaKernelConfigStore_get(),
                st::NodeStore_get(), config_str.c_str() ),
        m_index_to_debug_registers(),
        m_device_selector( st::CudaDeviceSelector_get() )
    {
        CudaController::status_t const status = this->doInitCudaController(
            nullptr, nullptr, config_str.c_str(), platform_id, device_id );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    CudaController::CudaController(
        CudaController::node_index_t const node_index,
        std::string const& SIXTRL_RESTRICT_REF config_str,
        CudaController::device_selector_t* SIXTRL_RESTRICT ptr_device_selector,
        CudaController::node_store_t* SIXTRL_RESTRICT ptr_node_store ) :
        st::NodeControllerBase( st::ARCHITECTURE_CUDA,
            st::CUDA_ARCHITECTURE_STR, st::CudaKernelConfigStore_get(),
                st::NodeStore_get(), config_str.c_str() ),
        m_index_to_debug_registers(),
        m_device_selector( st::CudaDeviceSelector_get() )
    {
        CudaController::status_t const status = this->doInitCudaController(
            ptr_device_selector, ptr_node_store,
                config_str.c_str(), node_index );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    /* --------------------------------------------------------------------- */

    CudaController::~CudaController() SIXTRL_NOEXCEPT
    {
        auto it  = this->m_index_to_debug_registers.begin();
        auto end = this->m_index_to_debug_registers.end();

        ::cudaError_t err = ::cudaSuccess;

        for( ; it != end ; ++it )
        {
            if( it->second != nullptr )
            {
                err = ::cudaFree( it->second );
                SIXTRL_ASSERT( err == ::cudaSuccess );
                ( void )err;

                it->second = nullptr;
            }
        }

        this->m_index_to_debug_registers.clear();
    }

    /* ===================================================================== */

    CudaController::status_t CudaController::sendMemory(
        CudaController::cuda_arg_buffer_t SIXTRL_RESTRICT destination,
        void const* SIXTRL_RESTRICT source,
        CudaController::size_type const source_length )
    {
        CudaController::lock_t lock( *this->nodeStore().lockable() );

        return CudaController::PerformSendOperation( lock,
            destination, source, source_length );
    }

    CudaController::status_t CudaController::receiveMemory(
        void* SIXTRL_RESTRICT destination,
        CudaController::cuda_const_arg_buffer_t SIXTRL_RESTRICT source,
        CudaController::size_type const source_length )
    {
        CudaController::lock_t lock( *this->nodeStore().lockable() );

        return CudaController::PerformReceiveOperation( lock,
            destination, source_length, source, source_length );
    }

    CudaController::status_t CudaController::remap(
        cuda_arg_buffer_t SIXTRL_RESTRICT managed_buffer_begin,
        size_type const slot_size )
    {
        CudaController::lock_t lock( *this->nodeStore().lockable() );

        return this->doRemapCObjectsBufferDirectly(
            managed_buffer_begin, slot_size );
    }

    bool CudaController::isRemapped(
        CudaController::cuda_arg_buffer_t SIXTRL_RESTRICT managed_buffer_begin,
        CudaController::size_type const slot_size )
    {
        CudaController::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        CudaController::lock_t lock( *this->nodeStore().lockable() );

        bool const is_remapped = this->doCheckIsCobjectsBufferRemappedDirectly(
            &status, managed_buffer_begin, slot_size );

        if( status != st::ARCH_STATUS_SUCCESS )
        {
            lock.unlock();
            throw std::runtime_error(
                "unable to perform isRemapped() check on managd cuda buffer" );
        }

        return is_remapped;
    }

    /* ===================================================================== */

    CudaController::status_t CudaController::doSend(
        CudaController::ptr_arg_base_t SIXTRL_RESTRICT dest_arg,
        const void *const SIXTRL_RESTRICT source,
        CudaController::size_type const source_length )
    {
        using _this_t    = st::CudaController;
        using status_t   = _this_t::status_t;
        using size_t     = _this_t::size_type;
        using cuda_arg_t = st::CudaArgument;
        using cuda_arg_buffer_t = cuda_arg_t::cuda_arg_buffer_t;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        SIXTRL_ASSERT( this->readyForSend() );
        SIXTRL_ASSERT( dest_arg != nullptr );
        SIXTRL_ASSERT( source   != nullptr );
        SIXTRL_ASSERT( source_length > size_t{ 0 } );
        SIXTRL_ASSERT( dest_arg->capacity() >= source_length );

        if( dest_arg->hasArgumentBuffer() )
        {
            cuda_arg_t* cuda_arg = dest_arg->asDerivedArgument< cuda_arg_t >(
                st::ARCHITECTURE_CUDA );

            if( ( cuda_arg != nullptr ) &&
                ( cuda_arg->hasCudaArgBuffer() ) &&
                ( cuda_arg->attachedToNode().valid() ) )
            {
                _this_t::lock_t lock( *this->nodeStore().lockable() );
                _this_t::index_t initial_node_index = _this_t::UNDEFINED_INDEX;

                auto switch_nodes_res = this->doChangeNodeBeforeOp(
                    lock, &initial_node_index, cuda_arg->attachedToNode() );

                status = switch_nodes_res.first;
                bool const changed_nodes = switch_nodes_res.second;

                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( ( initial_node_index != _this_t::UNDEFINED_INDEX ) &&
                      ( ( !changed_nodes ) || ( initial_node_index !=
                          this->selectedNodeIndex( lock ) ) ) &&
                      (  this->ptrSelectedNodeId( lock ) != nullptr ) &&
                      ( cuda_arg->attachedtoNode() ==
                        *this->ptrSelectedNodeId( lock ) ) ) );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = _this_t::PerformSendOperation( lock,
                        cuda_arg->cudaArgBuffer(), source, source_length );
                }

                if( ( changed_nodes ) &&
                    ( st::ARCH_STATUS_SUCCESS != this->doChangeSelectedNode(
                            lock, initial_node_index ) ) )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }
        }

        return status;
    }

    CudaController::status_t CudaController::doReceive(
        void* SIXTRL_RESTRICT destination,
        CudaController::size_type const dest_capacity,
        CudaController::ptr_arg_base_t SIXTRL_RESTRICT src_arg )
    {
        using _this_t    = CudaController;
        using status_t   = _this_t::status_t;
        using size_t     = _this_t::size_type;
        using cuda_arg_t = st::CudaArgument;
        using cuda_arg_buffer_t = cuda_arg_t::cuda_arg_buffer_t;

        status_t status = status_t{ -1 };

        SIXTRL_ASSERT( this->readyForReceive() );
        SIXTRL_ASSERT( destination != nullptr );
        SIXTRL_ASSERT( src_arg != nullptr );
        SIXTRL_ASSERT( src_arg->size() > size_t{ 0 } );
        SIXTRL_ASSERT( dest_capacity >= src_arg->size() );

        if( src_arg->hasArgumentBuffer() )
        {
            cuda_arg_t* cuda_arg = src_arg->asDerivedArgument< cuda_arg_t >(
                st::ARCHITECTURE_CUDA );

            if( ( cuda_arg != nullptr ) && ( cuda_arg->hasCudaArgBuffer() ) &&
                ( cuda_arg->attachedToNode().valid() ) )
            {
                _this_t::lock_t lock( *this->nodeStore().lockable() );
                _this_t::index_t initial_node_index = _this_t::UNDEFINED_INDEX;

                auto switch_nodes_res = this->doChangeNodeBeforeOp(
                    lock, &initial_node_index, cuda_arg->attachedToNode() );

                status = switch_nodes_res.first;
                bool const changed_nodes = switch_nodes_res.second;

                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( ( initial_node_index != _this_t::UNDEFINED_INDEX ) &&
                      ( ( !changed_nodes ) || ( initial_node_index !=
                          this->selectedNodeIndex( lock ) ) ) &&
                      (  this->ptrSelectedNodeId( lock ) != nullptr ) &&
                      ( cuda_arg->attachedtoNode() ==
                        *this->ptrSelectedNodeId( lock ) ) ) );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = _this_t::PerformReceiveOperation( lock,
                        destination, dest_capacity, cuda_arg->cudaArgBuffer(),
                            src_arg->size() );
                }

                if( ( changed_nodes ) &&
                    ( st::ARCH_STATUS_SUCCESS != this->doChangeSelectedNode(
                            lock, initial_node_index ) ) )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }
        }

        return status;
    }

    CudaController::status_t CudaController::doSetDebugRegister(
        CudaController::debug_register_t const debug_register )
    {
        using _this_t = st::CudaController;
        using _base_t = _this_t::_base_controller_t;

        _this_t::lock_t lock( *this->nodeStore().lockable() );

        _this_t::status_t status = this->doSetDebugRegisterCudaBaseImpl(
            lock, debug_register );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = _base_t::doSetDebugRegister( debug_register );
        }

        return status;
    }

    CudaController::status_t CudaController::doFetchDebugRegister(
        CudaController::debug_register_t* SIXTRL_RESTRICT ptr_debug_register )
    {
        using _this_t = st::CudaController;
        using _base_t = _this_t::_base_controller_t;

        _this_t::lock_t lock( *this->nodeStore().lockable() );

        _this_t::status_t status = this->doFetchDebugRegisterCudaBaseImpl(
            lock, ptr_debug_register );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = _base_t::doFetchDebugRegister( ptr_debug_register );
        }

        return status;
    }

    CudaController::status_t CudaController::doRemapCObjectsBufferArg(
        CudaController::ptr_arg_base_t SIXTRL_RESTRICT buffer_arg )
    {
        using    _this_t = st::CudaController;
        using     size_t = _this_t::size_type;
        using cuda_arg_t = st::CudaArgument;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _this_t::lock_t lock( *this->nodeStore().lockable() );

        if( ( buffer_arg == nullptr ) || ( !this->readyForRunningKernel() ) )
        {
            return status;
        }

        cuda_arg_t* buffer_cuda_arg = buffer_arg->asDerivedArgument<
            st::CudaArgument >( this->archId() );

        if( ( buffer_cuda_arg != nullptr ) &&
            ( buffer_cuda_arg->usesCObjectsBuffer() ) &&
            ( buffer_cuda_arg->hasCudaArgBuffer() ) &&
            ( buffer_cuda_arg->capacity() > size_t{ 0 } ) &&
            ( buffer_cuda_arg->attachedToNode().valid() ) )
        {
            _this_t::node_index_t initial_index = _this_t::UNDEFINED_INDEX;

            auto switch_nodes_res = this->doChangeNodeBeforeOp(
                lock, &initial_index, buffer_cuda_arg->attachedToNode() );

            status = switch_nodes_res.first;
            bool const changed_nodes = switch_nodes_res.second;

            if( status = st::ARCH_STATUS_SUCCESS )
            {
                status = this->doRemapCObjectsBufferDirectly( lock,
                    buffer_cuda_arg->cudaArgBuffer(),
                    buffer_cuda_arg->cobjectsBufferSlotSize() );
            }

            if( ( changed_nodes ) &&
                ( st::ARCH_STATUS_SUCCESS != this->doChangeSelectedNode(
                    lock, initial_index ) ) )
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        return status;
    }

    bool CudaController::doIsCObjectsBufferArgRemapped(
        CudaController::ptr_arg_base_t SIXTRL_RESTRICT buffer_arg,
        CudaController::status_t* SIXTRL_RESTRICT ptr_status )
    {
        using _this_t = st::CudaController;
        using   status_t = ::status_t;
        using     size_t = st::CudaController::size_type;
        using cuda_arg_t = st::CudaArgument;

        bool is_remapped = false;

        _this_t::status_t status = status = st::ARCH_STATUS_GENERAL_FAILURE;
        _this_t::lock_t lock( *this->nodeStore().lockable() );

        if( ( buffer_arg != nullptr ) && ( this->readyForRunningKernel() ) )
        {
            cuda_arg_t* buffer_cuda_arg = buffer_arg->asDerivedArgument<
                st::CudaArgument >( this->archId() );

            if( ( buffer_cuda_arg != nullptr ) &&
                ( buffer_cuda_arg->usesCObjectsBuffer() ) &&
                ( buffer_cuda_arg->hasCudaArgBuffer() ) &&
                ( buffer_cuda_arg->capacity() > size_t{ 0 } ) &&
                ( buffer_cuda_arg->attachedToNode().valid() ) )
            {
                _this_t::node_index_t initial_index = _this_t::UNDEFINED_INDEX;

                auto switch_nodes_res = this->doChangeNodeBeforeOp(
                    lock, &initial_index, buffer_cuda_arg->attachedToNode() );

                status = switch_nodes_res.first;
                bool const changed_nodes = switch_nodes_res.second;

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    is_remapped = this->doCheckIsCobjectsBufferRemappedDirectly(
                        lock, &status, buffer_cuda_arg->cudaArgBuffer(),
                            buffer_cuda_arg->cobjectsBufferSlotSize() );
                }

                if( ( changed_nodes ) &&
                    ( st::ARCH_STATUS_SUCCESS != this->doChangeSelectedNode(
                        lock, initial_index ) ) )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }
        }

        if( status != st::ARCH_STATUS_SUCCESS )
        {
            is_remapped = false;
        }

        if( ptr_status != nullptr )
        {
            *ptr_status = status;
        }

        return is_remapped;
    }

    CudaController::status_t CudaController::doRemapCObjectsBufferDirectly(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaController::cuda_arg_buffer_t SIXTRL_RESTRICT managed_buffer_begin,
        CudaController::size_type const slot_size )
    {
        using    _this_t        = CudaController;
        using kernel_config_t   = _this_t::kernel_config_t;
        using   status_t        = _this_t::status_t;
        using     size_t        = _this_t::size_type;
        using cuda_arg_buffer_t = _this_t::cuda_arg_buffer_t;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( slot_size > size_t{ 0 } ) &&
            ( managed_buffer_begin != nullptr ) &&
            ( this->nodeStore().checkLock( lock ) ) &&
            ( this->hasSelectedNode( lock ) ) &&
            ( this->readyForRunningKernel() ) )
        {
            _this_t::node_index_t const selected_node_index =
                this->selectedNodeIndex( lock );
            SIXTRL_ASSERT( selected_node_index != _this_t::UNDEFINED_INDEX );

            kernel_config_t const* kernel_config = nullptr;

            bool const in_debug_mode = this->isInDebugMode();

            if( in_debug_mode )
            {
                kernel_config = this->ptrKernelConfig(
                    this->remapCObjectBufferDebugKernelId() );
            }
            else
            {
                kernel_config = this->ptrKernelConfig(
                    this->remapCObjectBufferKernelId() );
            }

            if( kernel_config != nullptr )
            {
                if( in_debug_mode )
                {
                    ::NS(Buffer_remap_cuda_wrapper)(
                        kernel_config, managed_buffer_begin, slot_size );

                    status = st::ARCH_STATUS_SUCCESS;
                }
                else
                {
                    _this_t::cuda_arg_buffer_t cuda_debug_reg =
                        this->doGetPtrCudaDebugRegister(
                            lock, selected_node_index );

                    if( cuda_debug_reg != nullptr )
                    {
                        status = this->prepareDebugRegisterForUse();

                        if( status == st::ARCH_STATUS_SUCCESS )
                        {
                            ::NS(Buffer_remap_cuda_debug_wrapper)(
                                kernel_config, managed_buffer_begin, slot_size,
                                    cuda_debug_reg );

                            status = this->evaluateDebugRegisterAfterUse();
                        }
                    }
                }
            }
        }

        return status;
    }

    bool CudaController::doCheckIsCobjectsBufferRemappedDirectly(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaController::status_t* SIXTRL_RESTRICT ptr_status,
        CudaController::cuda_arg_buffer_t SIXTRL_RESTRICT managed_buffer_begin,
        CudaController::size_type const slot_size )
    {
        using    _this_t        = CudaController;
        using   status_t        = _this_t::status_t;
        using     size_t        = _this_t::size_type;
        using cuda_arg_buffer_t = _this_t::cuda_arg_buffer_t;

        bool is_remapped = false;

        if( ( slot_size > size_t{ 0 } ) &&
            ( managed_buffer_begin != nullptr ) &&
            ( this->nodeStore().checkLock( lock ) ) &&
            ( this->readyForRunningKernel() ) &&
            ( this->hasSelectedNode( lock ) ) )
        {
            _this_t::node_index_t const selected_node_index =
                this->selectedNodeIndex( lock );

            SIXTRL_ASSERT( selected_node_index != _this_t::UNDEFINED_INDEX );

            is_remapped = ::NS(Buffer_is_remapped_cuda_wrapper)(
                managed_buffer_begin, slot_size,
                    this->doGetPtrCudaDebugRegister( lock, selected_node_index ),
                        ptr_status );
        }

        return is_remapped;
    }

    CudaController::status_t CudaController::doSelectNode(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaController::node_index_t const node_index )
    {
        return this->doSelectNodeCudaImpl( lock, node_index );
    }

    CudaController::status_t CudaController::doSelectNodeCudaImpl(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaController::node_index_t const idx )
    {
        using _this_t = st::CudaController;
        using _base_t = _this_t::_base_controller_t;
        using ptr_node_id_t = _this_t::node_id_t const*;
        using platform_id_t = _this_t::platform_id_t;
        using device_id_t   = _this_t::device_id_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( !this->nodeStore().checkLock( lock ) ) ||
            ( !this->deviceSelector().checkLock( lock ) ) )
        {
            return status;
        }

        SIXTRL_ASSERT( !this->hasSelectedNode( lock ) );
        SIXTRL_ASSERT( node_index != _this_t::UNDEFINED_INDEX );
        SIXTRL_ASSERT( this->doCheckIfNodeIndexIsAvailableLocally(
            lock, node_index ) );

        ptr_node_id_t ptr_node_id = this->ptrNodeId( lock, node_index );

        if( ( ptr_node_id != nullptr ) &&
            ( ptr_node_id->archId() == this->archId() ) &&
            ( ptr_node_id->platformId() != _this_t::ILLEGAL_PLATFORM_ID ) &&
            ( ptr_node_id->deviceId() == device_id_t{ 0 } ) )
        {
            platform_id_t const dev_id = ptr_node_id->platformId();
            status = _base_t::doSelectNode( lock, node_index );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->deviceSelector().setDeviceId( lock, dev_id );
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( ( platform_id = this->deviceSelector().deviceId( lock ) ) &&
                  ( this->ptrSelectedNodeId( lock ) != nullptr ) &&
                  ( this->ptrSelectedNodeId( lock )->valid() ) &&
                  ( this->ptrSelectedNodeId( lock )->platformId() == dev_id ) &&
                  ( this->ptrSelectedNodeId( lock )->deviceId() ==
                    device_id_t{ 0 } ) &&
                  ( this->selectedNodeIndex( lock ) == node_index ) ) );
        }

        return status;
    }

    CudaController::status_t CudaController::doChangeSelectedNode(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaController::node_index_t const new_node_index )
    {
        using _this_t = st::CudaController;
        using _base_t = _this_t::_base_controller_t;
        using ptr_node_id_t = _this_t::node_id_t const*;
        using platform_id_t = _this_t::platform_id_t;
        using device_id_t   = _this_t::device_id_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        SIXTRL_ASSERT( new_node_index != _this_t::UNDEFINED_INDEX );

        if( ( !this->nodeStore().checkLock( lock ) ) ||
            ( !this->deviceSelector().checkLock( lock ) ) )
        {
            return status;
        }

        SIXTRL_ASSERT( this->hasSelectedNode( lock ) );
        SIXTRL_ASSERT( this->selectedNodeIndex( lock ) != new_node_index );
        SIXTRL_ASSERT( this->doCheckIfNodeIndexIsAvailableLocally(
                       lock, new_node_index ) );

        SIXTRL_ASSERT( this->ptrSelectedNodeId( lock ) != nullptr );
        SIXTRL_ASSERT( this->ptrSelectedNodeId( lock )->valid() );

        SIXTRL_ASSERT( this->ptrSelectedNodeId( lock )->archId() ==
                       this->archId() );

        SIXTRL_ASSERT( this->ptrSelectedNodeId( lock )->platformId() ==
                       this->deviceSelector().deviceId( lock ) );

        SIXTRL_ASSERT( this->ptrSelectedNodeId( lock )->deviceId() ==
                       device_id_t{ 0 } );

        ptr_node_id_t ptr_node_id = this->ptrNodeId( lock, new_node_index );

        if( ( ptr_node_id != nullptr ) &&
            ( ptr_node_id->archId() == this->archId() ) &&
            ( ptr_node_id->platformId() != _this_t::ILLEGAL_PLATFORM_ID ) &&
            ( ptr_node_id->deviceId() == device_id_t{ 0 } ) )
        {
            _this_t::platform_id_t const dev_id = ptr_node_id->platformId();
            SIXTRL_ASSERT( dev_id != this->ptrSelectedNodeId( lock )->platformId() );

            status = _base_t::doChangeSelectedNode( lock, new_node_index );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->deviceSelector().setDeviceId( lock, dev_id );
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( ( dev_id == this->deviceSelector().deviceId( lock ) ) &&
                  ( this->ptrSelectedNodeId( lock ) != nullptr ) &&
                  ( this->ptrSelectedNodeId( lock )->valid() ) &&
                  ( this->ptrSelectedNodeId( lock )->platformId() == dev_id ) &&
                  ( this->ptrSelectedNodeId( lock )->deviceId() ==
                    device_id_t{ 0 } ) &&
                  ( this->selectedNodeIndex( lock ) == new_node_index ) ) );
        }

        return status;
    }

    bool CudaController::doCheckIsNodeInitialized(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaController::node_index_t const index )
    {
        using _this_t = st::CudaController;
        using node_id_t = _this_t::node_id_t;

        bool is_node_initialized = false;

        if( ( index != _this_t::UNDEFINED_INDEX ) &&
            ( this->nodeStore().checkLock( lock ) ) &&
            ( this->nodeStore().isNodeAvailable( lock, index ) ) )
        {
            node_id_t const* ptr_node_id = this->ptrNodeId( lock, index );

            if( ptr_node == nullptr )
            {
                return is_node_initialized;
            }

            SIXTRL_ASSERT( ptr_node_id->valid() );
            SIXTRL_ASSERT( ptr_node_id->archId() == this->archId() );

            SIXTRL_ASSERT( ptr_node_id->platformId() !=
                           _this_t::ILLEGAL_PLATFORM_ID );

            SIXTRL_ASSERT( ptr_node_id->deviceId() ==
                            _this_t::device_id_t{ 0 } );


        }

        return is_node_initialized;
    }

    CudaController::status_t CudaController::doInitializeNode(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaController::node_index_t const index )
    {

    }

    /* --------------------------------------------------------------------- */

    void CudaController::doEnableCudaController()
    {
        SIXTRL_ASSERT( this->hasSelectedNode() );

        if( this->hasRemapCObjectBufferKernel() )
        {
            this->doSetReadyForSendFlag( true );
        }

        this->doSetReadyForReceiveFlag( true );
        this->doSetReadyForRunningKernelsFlag( true );
    }



    CudaController::status_t CudaController::PerformSendOperation(
        ::NS(cuda_arg_buffer_t) SIXTRL_RESTRICT destination,
        void const* SIXTRL_RESTRICT src_begin,
        CudaController::size_type const src_length )
    {
        using status_t = CudaController::status_t;
        using size_t = CudaController::size_type;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( destination != nullptr ) && ( src_begin != nullptr ) &&
            ( reinterpret_cast< std::uintptr_t >( destination ) !=
              reinterpret_cast< std::uintptr_t >( src_begin ) ) &&
            ( src_length > size_t{ 0 } ) )
        {
            ::cudaError_t const ret = ::cudaMemcpy(
                destination, src_begin, src_length, cudaMemcpyHostToDevice );

            if( ret == ::cudaSuccess )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    CudaController::status_t CudaController::PerformReceiveOperation(
        void* SIXTRL_RESTRICT destination,
        CudaController::size_type const destination_capacity,
        ::NS(cuda_const_arg_buffer_t) SIXTRL_RESTRICT src_begin,
        CudaController::size_type const src_length )
    {
        using status_t = CudaController::status_t;
        using size_t   = CudaController::size_type;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( destination != nullptr ) && ( src_begin != nullptr ) &&
            ( reinterpret_cast< std::uintptr_t >( destination ) !=
              reinterpret_cast< std::uintptr_t >( src_begin ) ) &&
            ( destination_capacity >= src_length ) &&
            ( src_length > size_t{ 0 } ) )
        {
            ::cudaError_t const err = ::cudaMemcpy(
                destination, src_begin, src_length, cudaMemcpyDeviceToHost );

            if( err == ::cudaSuccess )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    CudaController::status_t CudaController::doCreateCudaDebugRegister(
        CudaController::node_index_t const node_index,
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        CudaController::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _this_t::cuda_arg_buffer_t ptr_debug_register = nullptr;

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( node_index == this->selectedNodeIndex( lock ) ) )
        {
            ::cudaError_t err = ::cudaMalloc(
                &ptr_debug_register, sizeof( debug_register_t ) );

            if( err == ::cudaSuccess )
            {
                auto res = this->m_index_to_debug_registers.insert(
                    std::make_pair( node_index, ptr_debug_register ) );

                if( res.second )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }

            if( ( ptr_debug_register != nullptr ) &&
                ( status != st::ARCH_STATUS_SUCCESS ) )
            {
                err = ::cudaFree( ptr_debug_register );
                SIXTRL_ASSERT( err == ::cudaSuccess );
                ( void )err;
            }
        }

        return status;
    }

    CudaController::status_t
    CudaController::doFinishCudaControllerInitialization(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        CudaController::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;


        return status;
    }

    /* --------------------------------------------------------------------- */

    CudaController::status_t CudaController::doInitCudaDebugRegister(
        CudaController::node_index_t const node_index,
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        using _this_t = CudaController;
        using debug_register_t = _this_t::debug_register_t;
        using index_t = _this_t::node_index_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( node_index != _this_t::UNDEFINED_INDEX ) &&
            ( this->nodeStore().checkLock( lock ) ) &&
            ( this->isSyncWithNodeStore() ) &&
            ( this->doCheckIfNodeIndexIsAvailableLocally( lock, node_index ) ) )
        {
            auto it = this->m_index_to_debug_registers.find( node_index );

            if( ( it == this->m_index_to_debug_registers.end() ) ||
                ( it->second == nullptr ) )
            {
                status = st::ARCH_STATUS_SUCCESS;

                index_t const prev_node_idx = this->selectedNodeIndex( lock );

                SIXTRL_ASSERT( this->ptrSelectedNodeId( lock ) != nullptr );
                SIXTRL_ASSERT( this->ptrSelectedNodeId( lock )->valid() );
                SIXTRL_ASSERT( this->ptrSelectedNodeId( lock )->platformId() ==
                               this->deviceSelector().deviceId( lock ) );

                if( node_index != prev_node_idx )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;

                    _this_t::node_id_t const& node_id =
                        this->nodeStore().nodeId( node_index );

                    if( node_id.valid() )
                    {
                        status = this->doChangeSelectedNode( lock, node_index );

                        SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                            ( ( this->selectedNodeIndex( lock ) == node_index ) &&
                              ( this->ptrSelectedNodeId( lock ) != nullptr ) &&
                              ( this->ptrSelectedNodeId( lock )->valid() ) &&
                              ( this->ptrSelectedNodeId( lock )->platformId()
                                == this->deviceSelector().deviceId( lock ) )
                            ) );
                    }
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = this->doCreateCudaDebugRegister( lock, node_index );
                }

                if( prev_node_idx != this->selectedNodeIndex( lock ) )
                {
                    if( st::ARCH_STATUS_SUCCESS == this->doChangeSelectedNode(
                            lock, prev_node_idx ) )
                    {
                        auto ptr_sel_node_id = this->ptrSelectedNodeId( lock );

                        if( ( ptr_sel_node_id == nullptr ) ||
                            ( !ptr_sel_node_id->valid() ) ||
                            ( ptr_sel_node_id->platformId() !=
                              this->deviceSelector().deviceId( lock ) ) )
                        {
                            status = st::ARCH_STATUS_GENERAL_FAILURE;
                        }
                    }
                    else
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                    }
                }
            }
            else if( it->second != nullptr )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    CudaController::cuda_const_arg_buffer_t
    CudaController::doGetPtrCudaDebugRegister(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        node_index_t const node_index ) const SIXTRL_NOEXCEPT
    {
        using _this_t = CudaController;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _this_t::cuda_const_arg_buffer_t ptr_debug_register = nullptr;

        if( ( node_index != _this_t::UNDEFINED_INDEX ) &&
            ( this->nodestore().checkLock( lock ) ) &&
            ( this->isSyncWithNodeStore() ) )
        {
            SIXTRL_ASSERT( this->doCheckIfNodeIndexIsAvailableLocally(
                lock, node_index ) );

            auto it = this->m_index_to_debug_registers.find( node_index );

            if( it != this->m_index_to_debug_registers.end() )
            {
                ptr_debug_register = it->second;
            }
        }

        return status;
    }

    CudaController::status_t CudaController::doDeleteCudaDebugRegister(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock
        CudaController::node_index_t const node_index ) SIXTRL_NOEXCEPT
    {
        using _this_t = CudaController;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( node_index != _this_t::UNDEFINED_INDEX ) &&
            ( this->nodestore().checkLock( lock ) ) &&
            ( this->isSyncWithNodeStore() ) &&
            ( this->doCheckIfNodeIndexIsAvailableLocally(
                lock, node_index ) ) )
        {
            auto it = this->m_index_to_debug_registers.find( node_index );

            if( it != this->m_index_to_debug_registers.end() )
            {
                if( it->second != nullptr )
                {
                    ::cudaError_t err = ::cudaFree( it->second );
                    SIXTRL_ASSERT( err == ::cudaSuccess );
                }

                this->m_index_to_debug_registers.erase( it );
                it = this->m_index_to_debug_registers.end();
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    CudaController::status_t CudaController::doSetDebugRegisterCudaBaseImpl(
        CudaController::debug_register_t const debug_register )
    {
        return CudaController::PerformSendOperation(
            this->doGetPtrCudaDebugRegister(),
                &debug_register, sizeof( debug_register ) );
    }

    CudaController::status_t CudaController::doFetchDebugRegisterCudaBaseImpl(
        CudaController::debug_register_t* SIXTRL_RESTRICT ptr_debug_register )
    {
        using debug_register_t = CudaController::debug_register_t;

        return CudaController::PerformReceiveOperation(
            ptr_debug_register, sizeof( debug_register_t ),
            this->doGetPtrCudaDebugRegister(),
            sizeof( debug_register_t ) );
    }
}

#endif /* C++, Host */

/* end: sixtracklib/cuda/internal/controller.cpp */
