#ifndef SIXTRACKLIB_CUDA_CONTROLLER_HPP__
#define SIXTRACKLIB_CUDA_CONTROLLER_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <map>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_controller_base.h"
    #include "sixtracklib/cuda/definitions.h"
    #include "sixtracklib/cuda/control/node_info.h"
    #include "sixtracklib/common/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_store.hpp"
    #include "sixtracklib/common/control/kernel_config_key.hpp"
    #include "sixtracklib/common/control/kernel_config_store.hpp"
    #include "sixtracklib/cuda/control/kernel_config.hpp"
    #include "sixtracklib/cuda/control/node_info.hpp"
    #include "sixtracklib/cuda/control/device_selector.hpp"
    #include "sixtracklib/common/buffer.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class CudaArgument;

    class CudaController : public SIXTRL_CXX_NAMESPACE::NodeControllerBase
    {
        private:

        using _base_controller_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;

        public:

        using node_info_t       = SIXTRL_CXX_NAMESPACE::CudaNodeInfo;
        using kernel_config_t   = SIXTRL_CXX_NAMESPACE::CudaKernelConfig;
        using device_selector_t = SIXTRL_CXX_NAMESPACE::CudaDeviceSelector;
        using node_store_t      = device_selector_t::node_store_t;
        using cuda_dev_index_t  = node_info_t::cuda_dev_index_t;
        using cuda_arg_buffer_t = ::NS(cuda_arg_buffer_t);
        using cuda_const_arg_buffer_t = ::NS(cuda_const_arg_buffer_t);

        static SIXTRL_CONSTEXPR_OR_CONST size_type
            DEFAULT_WARP_SIZE = kernel_config_t::DEFAULT_WARP_SIZE;

        SIXTRL_HOST_FN explicit CudaController(
            char const* config_str = nullptr );

        SIXTRL_HOST_FN explicit CudaController(
            cuda_dev_index_t const node_index,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN explicit CudaController(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN CudaController(
            platform_id_t const platform_id, device_id_t const device_id,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN CudaController(
            node_index_t const node_index,
            char const* SIXTRL_RESTRICT config_str,
            device_selector_t* SIXTRL_RESTRICT ptr_device_selector,
            node_store_t* SIXTRL_RESTRICT ptr_node_store = nullptr );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN explicit CudaController(
            std::string const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN CudaController(
            cuda_dev_index_t const node_index,
            std::string const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN CudaController(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            std::string const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN CudaController(
            platform_id_t const platform_id, device_id_t const device_id,
            std::string const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN CudaController(
            node_index_t const node_index,
            std::string const& SIXTRL_RESTRICT_REF config_str,
            device_selector_t* SIXTRL_RESTRICT ptr_device_selector,
            node_store_t* SIXTRL_RESTRICT ptr_node_store = nullptr );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN CudaController( CudaController const& other) = default;
        SIXTRL_HOST_FN CudaController( CudaController&& other) = default;

        SIXTRL_HOST_FN CudaController&
        operator=( CudaController const& other) = default;

        SIXTRL_HOST_FN CudaController& operator=(
            CudaController&& other) = default;

        SIXTRL_HOST_FN virtual ~CudaController() SIXTRL_NOEXCEPT;

        /* ================================================================= */

        template< typename Args... >
        SIXTRL_HOST_FN node_info_t const* ptrNodeInfo( Args&& args ) const;

        template< typename Args... >
        SIXTRL_HOST_FN node_info_t const* ptrNodeInfo(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&& args ) const SIXTRL_NOEXCEPT;

        /* ================================================================= */

        using _base_controller_t::selectNode;

        SIXTRL_HOST_FN status_t selectNode(
            cuda_dev_index_t const cuda_dev_index );

        SIXTRL_HOST_FN status_t selectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            cuda_dev_index_t const cuda_dev_index );

        /* ================================================================ */

        using _base_controller_t::changeSelectedNode;

        SIXTRL_HOST_FN status_t changeSelectedNode(
            cuda_dev_index_t const cuda_dev_index );

        SIXTRL_HOST_FN status_t changeSelectedNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            cuda_dev_index_t const cuda_dev_index );

        /* ================================================================ */

        SIXTRL_HOST_FN status_t sendMemory(
            cuda_arg_buffer_t SIXTRL_RESTRICT destination,
            void const* SIXTRL_RESTRICT source,
            size_type const source_length );

        SIXTRL_HOST_FN status_t receiveMemory(
            void* SIXTRL_RESTRICT destination,
            cuda_const_arg_buffer_t SIXTRL_RESTRICT source,
            size_type const source_length );

        /* ================================================================ */

        using _base_controller_t::remap;
        using _base_controller_t::isRemapped;

        status_t remap( cuda_arg_buffer_t SIXTRL_RESTRICT managed_buffer_begin,
            size_type const slot_size );

        bool isRemapped( cuda_arg_buffer_t SIXTRL_RESTRICT managed_buffer_begin,
            size_type const slot_size );

        /* ================================================================ */

        template< typename Args... >
        SIXTRL_HOST_FN kernel_config_t const* ptrKernelConfig(
            Args&&... args ) const;

        template< typename Args... >
        SIXTRL_HOST_FN kernel_config_t* ptrKernelConfig( Args&&... args );

        /* ================================================================ */

        protected:

        using ptr_cuda_kernel_config_t = std::unique_ptr< kernel_config_t >;

         SIXTRL_HOST_FN virtual status_t doSend(
            ptr_arg_base_t SIXTRL_RESTRICT destination,
            const void *const SIXTRL_RESTRICT source,
            size_type const source_length ) override;

        SIXTRL_HOST_FN virtual status_t doReceive(
            void* SIXTRL_RESTRICT destination,
            size_type const dest_capacity,
            ptr_arg_base_t SIXTRL_RESTRICT source ) override;

        SIXTRL_HOST_FN virtual status_t doRemapCObjectsBufferArg(
            ptr_arg_base_t SIXTRL_RESTRICT arg ) override;

        SIXTRL_HOST_FN virtual bool doIsCObjectsBufferArgRemapped(
            ptr_arg_base_t SIXTRL_RESTRICT arg,
            status_t* SIXTRL_RESTRICT ptr_status ) override;

        SIXTRL_HOST_FN virtual status_t doSetDebugRegister(
            debug_register_t const debug_register ) override;

        SIXTRL_HOST_FN virtual status_t doFetchDebugRegister(
            debug_register_t* SIXTRL_RESTRICT ptr_debug_register ) override;

        SIXTRL_HOST_FN virtual status_t doSelectNode(
                lock_t const& SIXTRL_RESTRICT_REF lock,
                node_index_t const node_index ) override;

        SIXTRL_HOST_FN virtual status_t doChangeSelectedNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const new_selected_node_index ) override;

        SIXTRL_HOST_FN virtual bool doCheckIsNodeInitialized(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const index ) override;

        SIXTRL_HOST_FN virtual status_t doInitializeNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const index ) override;

        private:

        using index_to_debug_register_map_t =
            std::map< node_index_t, cuda_arg_buffer_t >;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN device_selector_t const&
        deviceSelector() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN device_selector_t& deviceSelector() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t doRemapCObjectsBufferDirectly(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            cuda_arg_buffer_t SIXTRL_RESTRICT managed_buffer_begin,
            size_type const slot_size );

        SIXTRL_HOST_FN bool doCheckIsCobjectsBufferRemappedDirectly(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            status_t* SIXTRL_RESTRICT ptr_status,
            cuda_arg_buffer_t SIXTRL_RESTRICT managed_buffer_begin,
            size_type const slot_size );

        /* ----------------------------------------------------------------- */

        template< typename Args... >
        SIXTRL_HOST_FN status_t doInitCudaController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            device_selector_t* SIXTRL_RESTRICT ptr_device_selector,
            node_store_t* SIXTRL_RESTRICT ptr_node_store,
            Args&&... args );

        SIXTRL_HOST_FN status_t doCreateCudaDebugRegister(
            node_index_t const node_index,
            lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN void doFinishCudaControllerInitialization(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t doInitCudaDebugRegister(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        SIXTRL_HOST_FN cuda_arg_buffer_t
        doGetPtrCudaDebugRegister( lock_t const& SIXTRL_RESTRICT_REF lock
            node_index_t const node_index ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN cuda_const_arg_buffer_t
        doGetPtrCudaDebugRegister( lock_t const& SIXTRL_RESTRICT_REF lock
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doDeleteCudaDebugRegister(
            lock_t const& SIXTRL_RESTRICT_REF lock
            node_index_t const node_index ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN static status_t PerformSendOperation(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            cuda_arg_buffer_t SIXTRL_RESTRICT destination,
            void const* SIXTRL_RESTRICT src_begin, size_type const src_length );

        SIXTRL_HOST_FN static status_t PerformReceiveOperation(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            void* SIXTRL_RESTRICT destination,
            size_type const destination_capacity,
            cuda_const_arg_buffer_t SIXTRL_RESTRICT source_begin,
            size_type const source_length );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t doSetDebugRegisterCudaBaseImpl(
            debug_register_t const debug_register );

        SIXTRL_HOST_FN status_t doFetchDebugRegisterCudaBaseImpl(
            debug_register_t* SIXTRL_RESTRICT ptr_debug_register );

        SIXTRL_HOST_FN status_t doSelectNodeCudaImpl(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const idx );

        SIXTRL_HOST_FN status_t doInitializeNodeCudaImpl(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index );

        SIXTRL_HOST_FN status_t doRemapCObjectsBufferCudaBaseImpl(
            ptr_arg_base_t SIXTRL_RESTRICT arg, size_type const arg_size );

        index_to_debug_register_map_t   m_index_to_debug_registers;
        device_selector_t&              m_device_selector;
    };
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

typedef SIXTRL_CXX_NAMESPACE::CudaController NS(CudaController);

#else /* C++, Host */

typedef void NS(CudaController);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE CudaController::cuda_arg_buffer_t
    CudaController::doGetPtrCudaDebugRegister(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        node_index_t const node_index ) SIXTRL_NOEXCEPT
    {
        return const_cast< CudaController::cuda_arg_buffer_t >(
            static_cast< CudaController const& >(
                *this ).doGetPtrCudaDebugRegister( lock, node_index ) );
    }

    /* --------------------------------------------------------------------- */

    template< typename Args... >
    CudaController::node_info_t const*
    CudaController::ptrNodeInfo( Args&& args ) const
    {
        CudaController::lock_t lock( *this->nodeStore().lockable() );
        return this->ptrNodeInfo( lock, std::forward< Args >( args )... );
    }

    template< typename Args... >
    CudaController::node_info_t const* CudaController::ptrNodeInfo(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&& args ) const SIXTRL_NOEXCEPT
    {
        using node_info_t = CudaController::node_info_t;
        using node_info_base_t = CudaController::node_info_base_t;

        node_info_base_t const* node_info_base = this->ptrNodeInfoBase(
            lock, std::forward< Args >( args )... );

        return ( node_info_base != nullptr )
            ? node_info_base->asDerivedNodeInfo< node_info_t >( this->archId() )
            : nullptr;
    }

    /* --------------------------------------------------------------------- */

    template< typename Args... >
    CudaController::status_t CudaController::doInitCudaController(
        CudaController::device_selector_t* SIXTRL_RESTRICT ptr_device_selector,
        CudaController::node_store_t* SIXTRL_RESTRICT ptr_node_store,
        char const* SIXTRL_RESTRICT config_str, Args&&... args )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        using _this_t = CudaController;
        using _base_t = _this_t::_base_controller_t;
        using _select_fn_t = _base_t::selectNodeFn;

        _this_t::status_t status = st::ARCH_STATUS_SUCCESS;

        if( ( ptr_node_store != nullptr ) &&
            ( this->ptrNodeStore() != ptr_node_store ) )
        {
            status = this->doUpdateNodeStore( *ptr_node_store );
        }

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( ptr_device_selector != nullptr ) &&
            ( ptr_device_selector != this->ptrDeviceSelector() ) )
        {
            status = this->doUpdateDeviceSelector( *ptr_device_selector );
        }

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( this->deviceSelector().ptrNodeStore() != this->ptrNodeStore() ) )
        {
            status = this->deviceSelector().reset( this->nodeStore() );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            CudaController::lock_t lock( *this->nodeStore().lockable() );

            if( this->nodeStore().checkLock( lock ) )
            {
                this->doSetReadyForRunningKernelsFlag( false );
                this->doSetReadyForSendFlag( false );
                this->doSetReadyForReceiveFlag( false );

                this->doSetCanDirectlyChangeSelectedNodeFlag( true );
                this->doSetCanUnselectNodeFlag( false );
                this->doSetUseAutoSelectFlag( true );

                if( !this->nodeStore().hasArchitecture(
                        lock, this->archId() ) )
                {
                    status = this->doAttachAllArchNodes( lock );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        status = _base_t::doSyncWithNodeStore(
                            lock, this->ptrNodeStore() );
                    }
                }
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( this->isSyncWithNodeStore() ) )
            {
                _select_fn_t select_fn = static_cast< _select_fn_t >(
                    &_this_t::doSelectNodeCudaImpl );

                status = this->doInitiallySelectNode( lock, select_fn,
                    config_str, std::forward< Args >( args )... );
            }

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            this->doFinishCudaControllerInitialization( lock );
        }

        return status;
    }

    /* ===================================================================== */

    template< typename Args... >
    CudaController::node_info_t const* CudaController::ptrNodeInfo(
        Args&& args ) const
    {
        using node_info_t = CudaController::node_info_t;
        using node_info_base_t = CudaController::node_info_base_t;

        CudaController::lock_t lock( *this->nodeStore().lockable() );
        node_info_base_t const* ptr_info_base =
            this->ptrNodeInfoBase( lock, std::forward< Args >( args )... );

        return ( ptr_info_base != nullptr )
            ? ptr_info_base->asDerivedNodeInfo< node_info_t >( this->archId() )
            : nullptr;
    }

    template< typename Args... >
    CudaController::node_info_t const* CudaController::ptrNodeInfo(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&& args ) const SIXTRL_NOEXCEPT
    {
        using node_info_t = CudaController::node_info_t;
        using node_info_base_t = CudaController::node_info_base_t;

        node_info_base_t const* ptr_info_base =
            this->ptrNodeInfoBase( lock, std::forward< Args >( args )... );

        return ( ptr_info_base != nullptr )
            ? ptr_info_base->asDerivedNodeInfo< node_info_t >( this->archId() )
            : nullptr;
    }

    /* ===================================================================== */

    SIXTRL_INLINE CudaController::status_t CudaController::selectNode(
        CudaController::cuda_dev_index_t const cuda_dev_index )
    {
        CudaController::lock_t lock( *this->nodeStore().lockable() );
        return this->selectNode( lock, cuda_dev_index );
    }

    SIXTRL_INLINE CudaController::status_t CudaController::selectNode(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaController::cuda_dev_index_t const cuda_dev_index )
    {
        using platform_id_t = CudaController::platform_id_t;
        using device_id_t = CudaController::device_id_t;

        return this->selectNode( lock, this->nodeIndex( lock,
            this->archId(), static_cast< platform_id_t >( cuda_dev_index ),
                device_id_t{ 0 } ) );
    }

    /* ===================================================================== */

    SIXTRL_INLINE CudaController::status_t CudaController::changeSelectedNode(
        CudaController::cuda_dev_index_t const cuda_dev_index )
    {
        CudaController::lock_t lock( *this->nodeStore().lockable() );
        return this->changeSelectedNode( lock, cuda_dev_index );
    }

    SIXTRL_INLINE CudaController::status_t CudaController::changeSelectedNode(
        CudaController::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaController::cuda_dev_index_t const cuda_dev_index )
    {
        return this->changeSelectedNode( lock, this->nodeIndex( lock,
            this->archId(), static_cast< platform_id_t >( cuda_dev_index ),
                device_id_t{ 0 } ) );
    }

    /* --------------------------------------------------------------------- */

    template< typename Args... >
    CudaController::kernel_config_t const*
    CudaController::ptrKernelConfig( Args&&... args ) const
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        using kernel_conf_store_t = st::CudaKernelConfigStore;
        st::KernelConfigStore const* ptr_base = this->ptrKernelConfigStore();

        st::CudaKernelConfigStore const* ptr_store = ( ptr_base != nullptr )
            ? ptr_base->asDerivedKernelConfigStore< kernel_conf_store_t >()
            : nullptr;

        return ( ptr_store != nullptr )
            ? ptr_store->ptrKernelConfig( std::forward< Args >( args )... );
    }

    template< typename Args... >
    CudaController::kernel_config_t*
    CudaController::ptrKernelConfig( Args&&... args )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        using kernel_conf_store_t = st::CudaKernelConfigStore;
        st::KernelConfigStore* ptr_base = this->ptrKernelConfigStore();

        st::CudaKernelConfigStore* ptr_store = ( ptr_base != nullptr )
            ? ptr_base->asDerivedKernelConfigStore< kernel_conf_store_t >()
            : nullptr;

        return ( ptr_store != nullptr )
            ? ptr_store->ptrKernelConfig( std::forward< Args >( args )... );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CudaController::device_selector_t const&
    CudaController::deviceSelector() const SIXTRL_NOEXCEPT
    {
        return this->m_device_selector;
    }

    SIXTRL_INLINE CudaController::device_selector_t&
    CudaController::deviceSelector() SIXTRL_NOEXCEPT
    {
        return this->m_device_selector;
    }

    SIXTRL_INLINE CudaController::device_selector_t const*
    CudaController::ptrDeviceSelector() const SIXTRL_NOEXCEPT
    {
        return &this->m_device_selector;
    }

    SIXTRL_INLINE CudaController::device_selector_t*
    CudaController::ptrDeviceSelector() SIXTRL_NOEXCEPT
    {
        return &this->m_device_selector;
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_CUDA_CONTROLLER_HPP__ */

/* end: sixtracklib/cuda/controller.hpp */
