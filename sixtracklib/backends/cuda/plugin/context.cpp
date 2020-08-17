#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/plugin/context.h"
    #include "sixtracklib/backends/cuda/plugin/cuda_tools.h"
    #include "sixtracklib_base/backend/backends_store.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cuda.h>
    #if defined( __cplusplus )
        #include <algorithm>
        #include <iostream>
        #include <memory>
        #include <string>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st      = SIXTRL_CXX_NAMESPACE;
        using this_t      = st::CudaContext;
        using dev_t       = st::CudaNodeId;
        using st_status_t = this_t::status_type;
        using guard_t     = this_t::guard_type;
        using thread_id_t = this_t::thread_id_type;
    }

    /* ********************************************************************* */

    constexpr this_t::flags_type this_t::FLAGS_NONE;
    constexpr this_t::flags_type this_t::CREATE_SCHED_AUTO;
    constexpr this_t::flags_type this_t::CREATE_SCHED_SPIN;
    constexpr this_t::flags_type this_t::CREATE_SCHED_YIELD;
    constexpr this_t::flags_type this_t::CREATE_SCHED_BLOCKING_SYNC;
    constexpr this_t::flags_type this_t::CREATE_SCHED_BITMASK;
    constexpr this_t::flags_type this_t::CREATE_MAP_HOST;
    constexpr this_t::flags_type this_t::CREATE_CUDA_FLAGS_BITMASK;
    constexpr this_t::flags_type this_t::CREATE_PRIMARY_CTX;
    constexpr this_t::flags_type this_t::IS_PRIMARY_CTX;

    constexpr this_t::flags_type this_t::ALL_FLAGS;
    constexpr this_t::flags_type this_t::ALL_PRIMARY_CTX_CREATE_FLAGS;
    constexpr this_t::flags_type this_t::ALL_OWNED_CTX_CREATE_FLAGS;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    std::shared_ptr< this_t > this_t::MAKE_PRIMARY_CTX(
        st::CudaNodeId const& SIXTRL_RESTRICT_REF node_id )
    {
        std::shared_ptr< this_t > primary_ctx( nullptr );
        st::CudaBackend* cuda_be = nullptr;
        st::BaseBackend* backend = st::BackendsStore_global().backend(
            st::BACKEND_CUDA );

        if( ( backend != nullptr ) &&
            ( backend->backend_id() == st::BACKEND_CUDA ) )
        {
            cuda_be = static_cast< st::CudaBackend* >( backend );
        }

        if( cuda_be != nullptr )
        {
            this_t::guard_type const lock( cuda_be->create_lock() );

            primary_ctx = this_t::MAKE_PRIMARY_CTX_DETAILED( node_id,
                this_t::CREATE_PRIMARY_CTX | this_t::CREATE_SCHED_AUTO,
                std::this_thread::get_id(), *cuda_be, lock );
        }

        return primary_ctx;
    }

    std::shared_ptr< this_t > this_t::MAKE_PRIMARY_CTX_DETAILED(
        st::CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
        this_t::flags_type create_flags, this_t::thread_id_type const tid,
        st::CudaBackend& SIXTRL_RESTRICT_REF backend,
        this_t::guard_type const& SIXTRL_RESTRICT_REF lock )
    {
        std::shared_ptr< this_t > primary_ctx( nullptr );

        if( ( backend.backend_id() == st::BACKEND_CUDA ) &&
            ( backend.is_locked( lock ) ) && ( backend.is_ready() ) &&
            ( node_id.is_legal() ) && ( node_id.device_handle() !=
                st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
            ( tid == std::this_thread::get_id() ) )
        {
            primary_ctx.reset( new this_t( backend ) );
            create_flags |= this_t::CREATE_PRIMARY_CTX;

            if( ( primary_ctx.get() != nullptr ) &&
                ( primary_ctx->init_primary_ctx( node_id, create_flags,
                    backend, lock ) != st::STATUS_SUCCESS ) )
            {
                primary_ctx.reset();
            }
        }

        return primary_ctx;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    std::shared_ptr< this_t > this_t::MAKE_CTX(
        st::CudaNodeId const& SIXTRL_RESTRICT_REF node_id )
    {
        std::shared_ptr< this_t > ctx( nullptr );
        st::CudaBackend* cuda_be = nullptr;
        st::BaseBackend* backend = st::BackendsStore_global().backend(
            st::BACKEND_CUDA );

        if( ( backend != nullptr ) &&
            ( backend->backend_id() == st::BACKEND_CUDA ) )
        {
            cuda_be = static_cast< st::CudaBackend* >( backend );
        }

        if( cuda_be != nullptr )
        {
            this_t::guard_type const lock( cuda_be->create_lock() );

            ctx = this_t::MAKE_CTX_DETAILED( node_id,
                this_t::CREATE_PRIMARY_CTX | this_t::CREATE_SCHED_AUTO,
                std::this_thread::get_id(), *cuda_be, lock );
        }

        return ctx;
    }

    std::shared_ptr< this_t > this_t::MAKE_CTX_DETAILED(
        st::CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
        this_t::flags_type const create_flags, this_t::thread_id_type const tid,
        st::CudaBackend& SIXTRL_RESTRICT_REF backend,
        this_t::guard_type const& SIXTRL_RESTRICT_REF lock )
    {
        std::shared_ptr< this_t > ctx( nullptr );

        if( ( backend.backend_id() == st::BACKEND_CUDA ) &&
            ( backend.is_locked( lock ) ) && ( backend.is_ready() ) &&
            ( node_id.is_legal() ) && ( node_id.device_handle() !=
                st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
            ( tid == std::this_thread::get_id() ) )
        {
            ctx.reset( new this_t( backend ) );

            if( ( ctx.get() != nullptr ) && ( ctx->init_owned_ctx( node_id,
                    create_flags, backend, lock ) != st::STATUS_SUCCESS ) )
            {
                ctx.reset();
            }
        }

        return ctx;
    }

    /* ================================================================ */

    this_t::~CudaContext()
    {
        guard_t const lock( this->base_backend().create_lock() );

        if( this->m_node_id.device_handle() !=
                st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE )
        {
            if( this->is_primary() )
            {
                SIXTRL_CUDA_DRIVER_API_NOTHROW_CALL(
                    ::cuDevicePrimaryCtxRelease,
                    ( this->m_node_id.device_handle() ) );
            }
            else if( this->m_ctx_handle != nullptr )
            {
                SIXTRL_ASSERT( this->num_attached_threads(
                    lock ) <= st_size_t{ 1 } );

                if( this->is_current_thread_owner( lock ) )
                {
                    SIXTRL_CUDA_DRIVER_API_NOTHROW_CALL( ::cuCtxDestroy,
                        ( this->m_ctx_handle ) );
                }
                else if( this->has_owner_thread( lock ) )
                {
                    std::cerr << "ERROR: destructor to regular context has to"
                              << " be called by the owning thread!"
                              << std::endl;

                    SIXTRL_ASSERT( this->owner_thread( lock ) ==
                                   std::this_thread::get_id() );
                }
            }
        }
    }

    bool this_t::is_primary() const
    {
        return ( this_t::IS_PRIMARY_CTX ==
            ( this->m_flags & this_t::IS_PRIMARY_CTX ) );
    }

    st::CudaNodeId const& this_t::node_id() const SIXTRL_NOEXCEPT
    {
        return this->m_node_id;
    }

    this_t::ctx_handle_type this_t::raw_ctx_handle(
        this_t::guard_type const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        return ( ( this->base_backend().is_locked( lock ) ) &&
                 ( this->m_node_id.is_legal() ) &&
                 ( this->m_node_id.backend_id() == st::BACKEND_CUDA ) )
            ? this->m_ctx_handle : nullptr;
    }

    this_t::const_ctx_handle_type this_t::raw_ctx_handle( this_t::guard_type
        const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->base_backend().is_locked( lock ) ) &&
                 ( this->m_node_id.is_legal() ) &&
                 ( this->m_node_id.backend_id() == st::BACKEND_CUDA ) )
            ? this->m_ctx_handle : nullptr;
    }

    this_t::CudaContext( st::CudaBackend& SIXTRL_RESTRICT_REF cuda_be ) :
        st::BaseMTShareableContext( cuda_be ) {}

    st_status_t this_t::do_attach_to_thread( thread_id_t tid,
        guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        using base_ctx_t = st::BaseMTShareableContext;
        using node_id_t = st::CudaNodeId;

        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->base_backend().is_locked( lock ) ) &&
            ( this->m_node_id.is_legal() ) &&
            ( this->m_node_id.device_handle() !=
              node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
            ( this->m_node_id.backend_id() == st::BACKEND_CUDA ) )
        {
            status = base_ctx_t::do_attach_to_thread( tid, lock );
        }

        if( status == st::STATUS_SUCCESS )
        {
            if( this->is_primary() )
            {
                SIXTRL_CUDA_DRIVER_API_CALL( ::cuDevicePrimaryCtxRetain,
                    ( &this->m_ctx_handle, this->m_node_id.device_handle() ) );
            }
        }

        return status;
    }

    st_status_t this_t::do_detach_from_thread( thread_id_t tid,
        guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        using base_ctx_t = st::BaseMTShareableContext;
        using node_id_t = st::CudaNodeId;

        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->base_backend().is_locked( lock ) ) &&
            ( this->m_node_id.is_legal() ) &&
            ( this->m_node_id.device_handle() !=
              node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
            ( this->m_node_id.backend_id() == st::BACKEND_CUDA ) )
        {
            status = base_ctx_t::do_detach_from_thread( tid, lock );
        }

        if( status == st::STATUS_SUCCESS )
        {
            if( this->is_primary() )
            {
                SIXTRL_CUDA_DRIVER_API_CALL( ::cuDevicePrimaryCtxRelease,
                    ( this->m_node_id.device_handle() ) );
            }
        }

        return status;
    }

    st_status_t this_t::do_set_owner_thread_id( thread_id_t tid,
        guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        if( !this->has_owner_thread( lock ) )
        {
            if( this->is_primary() )
            {
                status = st::STATUS_SUCCESS;
            }
            else if( tid == std::this_thread::get_id() )
            {
                status = st::BaseMTShareableContext::do_set_owner_thread_id(
                    tid, lock );
            }
        }
        else if( ( this->is_current_thread_owner( lock ) ) &&
                 ( tid == thread_id_t{} ) )
        {
            if( this->is_primary() )
            {
                status = st::STATUS_SUCCESS;
            }
            else
            {
                status = st::BaseMTShareableContext::do_set_owner_thread_id(
                    thread_id_t{}, lock );
            }
        }

        return status;
    }

    st_status_t this_t::init_primary_ctx(
        st::CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
        this_t::flags_type const create_flags,
        st::CudaBackend& SIXTRL_RESTRICT_REF backend,
        guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        if( ( backend.is_ready() ) && ( backend.is_locked( lock ) ) &&
            ( backend.backend_id() == st::BACKEND_CUDA ) &&
            ( node_id.device_handle() !=
              st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
            ( ( create_flags & this_t::CREATE_PRIMARY_CTX ) ==
                this_t::CREATE_PRIMARY_CTX ) &&
            ( this->m_ctx_handle == nullptr ) && ( this->m_is_active = false ) )
        {
            this->m_node_id.clear();

            SIXTRL_CUDA_DRIVER_API_CALL( ::cuDevicePrimaryCtxRetain, (
                &this->m_ctx_handle, node_id.device_handle() ) );

            if( this->m_ctx_handle != nullptr )
            {
                this_t::flags_type const sanitized_create_flags =
                    ( create_flags & this_t::ALL_PRIMARY_CTX_CREATE_FLAGS );

                if( sanitized_create_flags != this_t::FLAGS_NONE )
                {
                    SIXTRL_CUDA_DRIVER_API_CALL( ::cuDevicePrimaryCtxSetFlags,
                        ( node_id.device_handle(), sanitized_create_flags ) );

                    this->m_flags = sanitized_create_flags;
                }
                else
                {
                    this->m_flags = this_t::FLAGS_NONE;
                }

                this->m_flags |= this_t::CREATE_PRIMARY_CTX;
                this->m_node_id.clear();
                this->m_node_id.set_device_handle( node_id.device_handle() );
                this->m_is_active = true;

                status = ( this->has_owner_thread( lock ) )
                    ? this->do_set_owner_thread_id( thread_id_t{}, lock )
                    : st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    st_status_t this_t::init_owned_ctx(
        st::CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
        this_t::flags_type const create_flags,
        st::CudaBackend& SIXTRL_RESTRICT_REF backend,
        guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        if( ( backend.is_ready() ) && ( backend.is_locked( lock ) ) &&
            ( backend.backend_id() == st::BACKEND_CUDA ) &&
            ( node_id.device_handle() !=
              st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
            ( ( create_flags & this_t::CREATE_PRIMARY_CTX ) !=
                this_t::CREATE_PRIMARY_CTX ) &&
            ( this->m_ctx_handle == nullptr ) && ( this->m_is_active = false ) )
        {
            this->m_node_id.clear();
            this_t::flags_type const sanitized_create_flags =
                    ( create_flags & this_t::ALL_OWNED_CTX_CREATE_FLAGS );

            SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxCreate, (
                &this->m_ctx_handle, sanitized_create_flags,
                    node_id.device_handle() ) );

            if( this->m_ctx_handle != nullptr )
            {
                this->m_flags = sanitized_create_flags;
                this->m_node_id.set_device_handle( node_id.device_handle() );
                this->m_is_active = true;

                status = this->do_set_owner_thread_id(
                    std::this_thread::get_id(), lock );
            }
        }

        return status;
    }
}

#endif /* C++, Host */
