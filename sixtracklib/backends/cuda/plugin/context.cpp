#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/plugin/context.h"
    #include "sixtracklib/backends/cuda/plugin/cuda_tools.h"
    #include "sixtracklib/backends/cuda/backend.h"
    #include "sixtracklib_base/backend/backends_store.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
    #include "sixtracklib_base/internal/thread_lock.h"
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

#if defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
           ( SIXTRACKL_ENABLE_BACKEND_CUDA == 1 )

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
    constexpr this_t::flags_type this_t::CREATE_OWNED_CTX;
    constexpr this_t::flags_type this_t::IS_PRIMARY_CTX;
    constexpr this_t::flags_type this_t::HAS_OWNERSHIP_CTX;

    constexpr this_t::flags_type this_t::ALL_FLAGS;
    constexpr this_t::flags_type this_t::ALL_PRIMARY_CTX_CREATE_FLAGS;
    constexpr this_t::flags_type this_t::ALL_OWNED_CTX_CREATE_FLAGS;

    constexpr this_t::flags_type this_t::DEFAULT_OWNED_CREATE_FLAGS;
    constexpr this_t::flags_type this_t::DEFAULT_PRIMARY_CREATE_FLAGS;

    this_t::ctx_handle_int_repr_type this_t::CURRENT_CTX_INT_REPR()
    {
        ::CUcontext current_ctx = nullptr;
        SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxGetCurrent, ( &current_ctx ) );
        return reinterpret_cast< this_t::ctx_handle_int_repr_type >(
            current_ctx );
    }

    this_t::status_type this_t::SET_CURRENT_CTX_BY_INT_REPR(
        this_t::ctx_handle_int_repr_type const ctx_int_repr,
        this_t::ctx_handle_int_repr_type* SIXTRL_RESTRICT ptr_prev_ctx )
    {
        ::CUcontext current_ctx = nullptr;
        SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxGetCurrent, ( &current_ctx ) );

        ::CUcontext ctx_to_change_to = reinterpret_cast<
            ::CUcontext >( ctx_int_repr );

        if( current_ctx != ctx_to_change_to )
        {
            SIXTRL_CUDA_DRIVER_API_CALL(
                ::cuCtxSetCurrent, ( ctx_to_change_to ) );
        }

        if( ptr_prev_ctx != nullptr )
        {
            *ptr_prev_ctx = reinterpret_cast< this_t::ctx_handle_int_repr_type
                >( current_ctx );
        }

        return st::STATUS_SUCCESS;
    }

    /* ===================================================================== */

    this_t::CudaContext( thread_id_t const& SIXTRL_RESTRICT_REF tid ) :
        st::BaseMTShareableContext( st::BACKEND_CUDA, tid ) {}

    this_t::CudaContext(
        st::CudaBackend& SIXTRL_RESTRICT_REF cuda_be,
        thread_id_t const& SIXTRL_RESTRICT_REF tid ) :
        st::BaseMTShareableContext( cuda_be, tid ) {}

    this_t::~CudaContext()
    {
        if( this->is_active() )
        {
            guard_t const lock( this->base_backend().create_lock() );
            SIXTRL_ASSERT( this->base_backend().is_locked( lock ) );
            SIXTRL_ASSERT( this->m_node_id.device_handle() !=
                st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE );

            if( this->is_primary( lock ) )
            {
                SIXTRL_ASSERT( !this->has_ownership( lock ) );
                SIXTRL_ASSERT( !this->is_ext_shared( lock ) );

                SIXTRL_CUDA_DRIVER_API_NOTHROW_CALL(
                    ::cuDevicePrimaryCtxRelease,
                    ( this->m_node_id.device_handle() ) );
            }
            else if( is_ext_shared( lock ) )
            {
                SIXTRL_ASSERT( !this->has_ownership( lock ) );
                SIXTRL_ASSERT( !this->is_primary( lock ) );

                if( this->m_ctx_handle != nullptr )
                {
                    SIXTRL_CUDA_DRIVER_API_NOTHROW_CALL( ::cuCtxSetCurrent,
                        ( nullptr ) );
                }
            }
            else if( this->has_ownership( lock ) )
            {
                SIXTRL_ASSERT( !this->is_primary( lock ) );
                SIXTRL_ASSERT( !this->is_ext_shared( lock ) );
                SIXTRL_ASSERT( this->m_ctx_handle != nullptr );
                SIXTRL_ASSERT( this->is_attached(
                    this->owned_by( lock ), lock ) );

                if( this->num_attached_threads( lock ) > st_size_t{ 1 } )
                {
                    auto thread_it = this->attached_thread_ids_begin( lock );
                    auto thread_end = this->attached_thread_ids_end( lock );

                    for( ; thread_it != thread_end ; ++thread_it )
                    {
                        if( *thread_it == this->owned_by( lock ) ) continue;
                        std::cerr << "info: destroying "
                          << SIXTRL_CXX_NAMESPACE_STR << "::CudaContext"
                          << " while thread " << ( *thread_it )()
                          << " is still attached\r\n";
                    }
                }

                SIXTRL_CUDA_DRIVER_API_NOTHROW_CALL(
                    ::cuCtxDestroy, ( this->m_ctx_handle ) );
            }
        }
    }

    /* --------------------------------------------------------------------- */

    st_status_t this_t::init(
        st::CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
        this_t::flags_type const create_flags ) {
        return this->init( node_id, create_flags,
                           this->base_backend().create_lock() );
    }

    st_status_t this_t::init(
        st::CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
        this_t::flags_type const create_flags,
        guard_t const& SIXTRL_RESTRICT_REF lock ) {

        st_status_t status = st::STATUS_GENERAL_FAILURE;
        if( ( this->base_backend().is_locked( lock ) ) &&
            ( this->base_backend().is_ready() ) &&
            ( this->base_backend().backend_id() == st::BACKEND_CUDA ) &&
            ( this->backend_id() == st::BACKEND_CUDA ) &&
            ( node_id.device_handle() !=
              st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
            ( ( create_flags & this_t::CREATE_PRIMARY_CTX ) ==
                this_t::FLAGS_NONE ) &&
            ( this->m_ctx_handle == nullptr ) && ( !this->is_active() ) )
        {
            this->m_node_id.clear();

            this_t::flags_type const sanitized_create_flags =
                    ( create_flags & this_t::ALL_OWNED_CTX_CREATE_FLAGS );

            SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxCreate, (
                &this->m_ctx_handle, sanitized_create_flags,
                    node_id.device_handle() ) );

            if( this->m_ctx_handle != nullptr )
            {
                this->m_flags  = sanitized_create_flags;
                this->m_flags |= this_t::CREATE_OWNED_CTX;
                status = this->m_node_id.set_device_handle(
                    node_id.device_handle() );
                this->update_is_active( status == st::STATUS_SUCCESS );
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t this_t::init_as_primary(
        st::CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
        this_t::flags_type const create_flags ) {
        return this->init_as_primary( node_id, create_flags,
            this->base_backend().create_lock() );
    }

    st_status_t this_t::init_as_primary(
        st::CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
        this_t::flags_type const create_flags,
        guard_t const& SIXTRL_RESTRICT_REF lock ) {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        if( ( this->base_backend().is_ready() ) &&
            ( this->base_backend().is_locked( lock ) ) &&
            ( this->base_backend().backend_id() == st::BACKEND_CUDA ) &&
            ( this->backend_id() == st::BACKEND_CUDA ) &&
            ( node_id.device_handle() !=
              st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
            ( ( create_flags & this_t::CREATE_OWNED_CTX ) ==
                this_t::FLAGS_NONE ) &&
            ( this->m_ctx_handle == nullptr ) && ( !this->is_active() ) )
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
                status = this->m_node_id.set_device_handle(
                    node_id.device_handle() );
                this->update_is_active( status == st::STATUS_SUCCESS );
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t this_t::init_as_ext_shared(
        this_t::ctx_handle_int_repr_type const ext_ctx_repr ) {
        return this->init_as_ext_shared( ext_ctx_repr,
            this->base_backend().create_lock() ); }

    st_status_t this_t::init_as_ext_shared(
        this_t::ctx_handle_int_repr_type const ext_ctx_repr,
        guard_t const& SIXTRL_RESTRICT_REF lock ) {
         st_status_t status = st::STATUS_GENERAL_FAILURE;
        if( ( this->base_backend().is_ready() ) &&
            ( this->base_backend().is_locked( lock ) ) &&
            ( this->base_backend().backend_id() == st::BACKEND_CUDA ) &&
            ( this->backend_id() == st::BACKEND_CUDA ) &&
            ( ext_ctx_repr != this_t::ctx_handle_int_repr_type{ 0 } ) &&
            ( this->m_ctx_handle == nullptr ) && ( !this->is_active() ) )
        {
            this->m_flags = this_t::FLAGS_NONE;
            this->m_node_id.clear();

            ::CUcontext ext_ctx = reinterpret_cast<
                ::CUcontext >( ext_ctx_repr );

            if( ext_ctx != nullptr )
            {
                ::CUcontext saved_current_ctx = nullptr;
                SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxGetCurrent,
                    ( &saved_current_ctx ) );

                SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxSetCurrent, ( ext_ctx ) );

                ::CUdevice ext_ctx_device =
                    st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE;

                SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxGetDevice,
                    ( &ext_ctx_device ) );

                unsigned int ext_ctx_flags = 0u;
                SIXTRL_CUDA_DRIVER_API_CALL(
                    ::cuCtxGetFlags, ( &ext_ctx_flags ) );

                SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxSetCurrent, ( nullptr ) );

                if( saved_current_ctx != nullptr )
                {
                    SIXTRL_CUDA_DRIVER_API_CALL(
                        ::cuCtxSetCurrent, ( saved_current_ctx ) );
                }

                status = this->m_node_id.set_device_handle( ext_ctx_device );

                if( status == st::STATUS_SUCCESS )
                {
                    this->m_flags = ( this_t::ALL_FLAGS & ext_ctx_flags );
                }
            }

            if( ( status == st::STATUS_SUCCESS ) &&
                ( this->m_node_id.is_legal() ) &&
                ( this->m_node_id.device_handle() !=
                  st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
                ( ext_ctx != nullptr ) )
            {
                this->m_ctx_handle = ext_ctx;
                this->update_is_active( true );
            }
            else
            {
                status = st::STATUS_GENERAL_FAILURE;
                this->m_ctx_handle = nullptr;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool this_t::is_primary() const
    {
        return this->is_primary( this->base_backend().create_lock() );
    }

    bool this_t::is_primary(
        guard_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->base_backend().is_locked( lock ) ) &&
                 ( ( this->m_flags & this_t::IS_PRIMARY_CTX ) ==
                   this_t::IS_PRIMARY_CTX ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool this_t::has_ownership() const
    {
        return this->has_ownership( this->base_backend().create_lock() );
    }

    bool this_t::has_ownership(
        guard_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->base_backend().is_locked( lock ) ) &&
                 ( ( this->m_flags & this_t::HAS_OWNERSHIP_CTX ) ==
                   this_t::HAS_OWNERSHIP_CTX ) );
    }

    st::CudaNodeId this_t::node_id() const SIXTRL_NOEXCEPT
    {
        guard_t const lock( this->base_backend().create_lock() );
        return this->m_node_id;
    }

    st::CudaNodeId const& this_t::node_id(
        guard_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->base_backend().is_locked( lock ) );
        return this->m_node_id;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool this_t::is_ext_shared() const {
        return this->is_ext_shared( this->base_backend().create_lock() );
    }

    bool this_t::is_ext_shared(
        guard_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT {
        return ( ( this->base_backend().is_locked( lock ) ) &&
                 ( this_t::FLAGS_NONE == ( this->m_flags &
                 ( this_t::IS_PRIMARY_CTX | this_t::HAS_OWNERSHIP_CTX ) ) ) );
    }

    /* --------------------------------------------------------------------- */

    this_t::ctx_handle_type this_t::handle(
        guard_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        return ( ( this->base_backend().is_locked( lock ) ) &&
                 ( this->m_node_id.is_legal() ) &&
                 ( this->m_node_id.backend_id() == st::BACKEND_CUDA ) )
            ? this->m_ctx_handle : nullptr;
    }

    this_t::const_ctx_handle_type this_t::handle(
        guard_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->base_backend().is_locked( lock ) ) &&
                 ( this->m_node_id.is_legal() ) &&
                 ( this->m_node_id.backend_id() == st::BACKEND_CUDA ) )
            ? this->m_ctx_handle : nullptr;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    this_t::ctx_handle_int_repr_type this_t::handle_int_repr() const {
        return this->handle_int_repr( this->base_backend().create_lock() );
    }

    this_t::ctx_handle_int_repr_type this_t::handle_int_repr(
        guard_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT {
        using int_repr_t = this_t::ctx_handle_int_repr_type;
        return ( this->base_backend().is_locked( lock ) )
            ? reinterpret_cast< int_repr_t >( this->m_ctx_handle )
            : int_repr_t{ 0 };
    }

    /* ===================================================================== */

    st_status_t this_t::do_attach_thread(
        thread_id_t const& SIXTRL_RESTRICT_REF tid,
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
            status = ( this->is_attached( tid, lock ) )
                ? st::STATUS_SUCCESS : st::STATUS_GENERAL_FAILURE;

            if( status != st::STATUS_SUCCESS )
            {
                /* NOTE: we assume that tid == calling thread. Otherwise,
                 * we can't perform no meaningful operations! */

                ::CUcontext current_saved_ctx = nullptr;
                SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxGetCurrent,
                    ( &current_saved_ctx ) );

                status = ( current_saved_ctx == nullptr )
                    ? st::STATUS_SUCCESS : st::STATUS_GENERAL_FAILURE;

                if( current_saved_ctx != nullptr )
                {
                    /* The thread is currently attached to a different
                     * context -> detach from that first if it is a different
                     * context */

                    st::CudaBackend* cu_backend = st::CudaBackend_get(
                            &this->base_backend() );

                    if( current_saved_ctx == this->m_ctx_handle )
                    {
                        /* Already attached to this context -> ok ?! */
                        status = st::STATUS_SUCCESS;
                    }
                    else if( cu_backend != nullptr )
                    {
                        ::CUdevice current_ctx_device =
                            st::CudaNodeId::ILLEGAL_CUDA_DEVICE_HANDLE;

                        SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxGetDevice,
                            ( &current_ctx_device ) );

                        st::CudaNodeId ctx_node( current_ctx_device );
                        auto other_base_ctx = cu_backend->context(
                            ctx_node, lock );

                        st::CudaContext* other_ctx = st::CudaContext_get(
                            other_base_ctx.get() );

                        if( ( other_ctx != nullptr ) &&
                            ( other_ctx->handle( lock ) == current_saved_ctx ) )
                        {
                            status = other_ctx->detach_thread( tid, lock );
                        }

                        if( status == st::STATUS_SUCCESS )
                        {
                            SIXTRL_ASSERT(  other_ctx != nullptr );
                            SIXTRL_ASSERT( !other_ctx->is_attached( tid ) );
                            SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxGetCurrent,
                                ( &current_saved_ctx ) );

                            if( current_saved_ctx != nullptr )
                            {
                                status = st::STATUS_GENERAL_FAILURE;
                            }
                        }
                    }
                }

                if( status == st::STATUS_SUCCESS )
                {
                    SIXTRL_ASSERT( current_saved_ctx == nullptr );
                    status = base_ctx_t::do_attach_thread( tid, lock );
                }

                if( status == st::STATUS_SUCCESS )
                {
                    if( this->is_primary( lock ) )
                    {
                        SIXTRL_CUDA_DRIVER_API_CALL(
                            ::cuDevicePrimaryCtxRetain,
                            ( &this->m_ctx_handle,
                                this->m_node_id.device_handle() ) );
                    }
                    else
                    {
                        SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxSetCurrent,
                            ( this->m_ctx_handle ) );
                    }
                }
            }
        }

        return status;
    }

    st_status_t this_t::do_detach_thread(
        thread_id_t const& SIXTRL_RESTRICT_REF tid,
        guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        using base_ctx_t = st::BaseMTShareableContext;
        using node_id_t = st::CudaNodeId;

        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->base_backend().is_locked( lock ) ) &&
            ( this->m_node_id.is_legal() ) &&
            ( this->m_node_id.device_handle() !=
              node_id_t::ILLEGAL_CUDA_DEVICE_HANDLE ) &&
            ( this->m_node_id.backend_id() == st::BACKEND_CUDA ) &&
            ( this->is_attached( tid, lock ) ) &&
            ( this->owned_by( lock ) != tid ) )
        {
            ::CUcontext current_saved_ctx = nullptr;
            SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxGetCurrent,
                ( &current_saved_ctx ) );

            status = st::STATUS_SUCCESS;
            if( current_saved_ctx != nullptr )
            {
                if( current_saved_ctx == this->m_ctx_handle )
                {
                    if( this->is_primary( lock ) )
                    {
                        SIXTRL_CUDA_DRIVER_API_CALL(
                            ::cuDevicePrimaryCtxRelease,
                            ( this->m_node_id.device_handle() ) );

                        current_saved_ctx = nullptr;
                    }
                    else
                    {
                        SIXTRL_CUDA_DRIVER_API_CALL(
                            ::cuCtxSetCurrent, ( nullptr ) );

                        SIXTRL_CUDA_DRIVER_API_CALL(
                            ::cuCtxGetCurrent, ( &current_saved_ctx ) );
                    }
                }
                else
                {
                    status = st::STATUS_GENERAL_FAILURE;
                }
            }

            if( ( status == st::STATUS_SUCCESS ) &&
                ( current_saved_ctx == nullptr ) )
            {
                status = base_ctx_t::do_detach_thread( tid, lock );
            }
        }

        return status;
    }
}
#endif /* C++, Host */
#endif /* SIXTRACKL_ENABLE_BACKEND_CUDA */

/* ************************************************************************* */

#if defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
           ( SIXTRACKL_ENABLE_BACKEND_CUDA == 1 ) && \
    defined( SIXTRL_CUDA_PLUGIN_BUILT ) && ( SIXTRL_CUDA_PLUGIN_BUILT == 1 )

::NS(cuda_ctx_int_repr_type) NS(CudaContext_current_ctx)( void ) {
    return SIXTRL_CXX_NAMESPACE::CudaContext::CURRENT_CTX_INT_REPR();
}

::NS(status_t) NS(CudaContext_set_current_ctx)(
    ::NS(cuda_ctx_int_repr_type) const ctx_to_change_to,
    ::NS(cuda_ctx_int_repr_type)* SIXTRL_RESTRICT ptr_current_ctx_repr ) {
    return SIXTRL_CXX_NAMESPACE::CudaContext::SET_CURRENT_CTX_BY_INT_REPR(
        ctx_to_change_to, ptr_current_ctx_repr ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(BaseContext)* NS(CudaContext_create)(
    const ::NS(ThreadId) *const SIXTRL_RESTRICT tid )
{
    return ( tid != nullptr )
        ? new SIXTRL_CXX_NAMESPACE::CudaContext( *tid ) : nullptr;
}

::NS(status_t) NS(CudaContext_init)(
    ::NS(BaseContext)* SIXTRL_RESTRICT ctx,
    const ::NS(BaseNodeId) *const SIXTRL_RESTRICT node_id,
    ::NS(cuda_ctx_create_flags_t) const create_flags,
    const ::NS(ThreadUniqueLock) *const SIXTRL_RESTRICT ptr_lock )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::status_t status = st::STATUS_GENERAL_FAILURE;
    st::CudaContext* cu_ctx = st::CudaContext_get( ctx );
    st::CudaNodeId const* cu_node_id = st::CudaNodeId_get( node_id );

    if( ( cu_ctx   != nullptr ) && ( cu_node_id != nullptr ) &&
        ( ptr_lock != nullptr ) )
    {
        status = cu_ctx->init( *cu_node_id, create_flags, *ptr_lock );
    }

    return status;
}

::NS(status_t) NS(CudaContext_init_as_primary)(
    ::NS(BaseContext)* SIXTRL_RESTRICT ctx,
    const ::NS(BaseNodeId) *const SIXTRL_RESTRICT node_id,
    ::NS(cuda_ctx_create_flags_t) const create_flags,
    const NS(ThreadUniqueLock) *const SIXTRL_RESTRICT ptr_lock )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::status_t status = st::STATUS_GENERAL_FAILURE;
    st::CudaContext* cu_ctx = st::CudaContext_get( ctx );
    st::CudaNodeId const* cu_node_id = st::CudaNodeId_get( node_id );

    if( ( cu_ctx != nullptr ) && ( cu_node_id != nullptr ) &&
        ( ptr_lock != nullptr ) )
    {
        status = cu_ctx->init_as_primary(
            *cu_node_id, create_flags, *ptr_lock );
    }

    return status;
}

::NS(status_t) NS(CudaContext_init_as_ext_shared)(
    ::NS(BaseContext)* SIXTRL_RESTRICT ctx,
    ::NS(cuda_ctx_int_repr_type) const ext_ctx_repr,
    const ::NS(ThreadUniqueLock) *const SIXTRL_RESTRICT ptr_lock )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::CudaContext* cu_ctx = st::CudaContext_get( ctx );

    return ( ( cu_ctx != nullptr ) && ( ptr_lock != nullptr ) )
        ? cu_ctx->init_as_ext_shared( ext_ctx_repr, *ptr_lock )
        : st::STATUS_GENERAL_FAILURE;
}

const ::NS(BaseNodeId) *const NS(CudaContext_node_id)(
    const ::NS(BaseContext) *const SIXTRL_RESTRICT ctx,
    const ::NS(ThreadUniqueLock) *const
        SIXTRL_RESTRICT ptr_lock ) SIXTRL_NOEXCEPT {
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::CudaContext const* cu_ctx = st::CudaContext_get( ctx );
    return ( ( cu_ctx != nullptr ) && ( ptr_lock != nullptr ) )
        ? &cu_ctx->node_id( *ptr_lock ) : nullptr;
}

#else /* !SIXTRACKL_ENABLE_BACKEND_CUDA || !SIXTRL_CUDA_PLUGIN_BUILT */

#if defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
           ( SIXTRACKL_ENABLE_BACKEND_CUDA == 1 ) && \
    defined( SIXTRL_CUDA_PLUGIN_BUILT ) && ( SIXTRL_CUDA_PLUGIN_BUILT == 1 )

::NS(cuda_ctx_int_repr_type) NS(CudaContext_current_ctx)( void ) {
    return ::NS(cuda_ctx_int_repr_type){ 0 };
}

::NS(status_t) NS(CudaContext_set_current_ctx)(
    ::NS(cuda_ctx_int_repr_type) const ctx_to_change_to,
    ::NS(cuda_ctx_int_repr_type)* SIXTRL_RESTRICT ptr_current_ctx_repr ) {
    return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(BaseContext)* NS(CudaContext_create)(
    const ::NS(ThreadId) *const SIXTRL_RESTRICT SIXTRL_UNUSED( tid ) ) {
    return nullptr; }

::NS(status_t) NS(CudaContext_init)(
    ::NS(BaseContext)* SIXTRL_RESTRICT SIXTRL_UNUSED( ctx ),
    const ::NS(BaseNodeId) *const SIXTRL_RESTRICT SIXTRL_UNUSED( node_id ),
    ::NS(cuda_ctx_create_flags_t) const SIXTRL_UNUSED( create_flags ),
    const ::NS(ThreadUniqueLock) *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( ptr_lock ) ) {
    return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

::NS(status_t) NS(CudaContext_init_as_primary)(
    ::NS(BaseContext)* SIXTRL_RESTRICT SIXTRL_UNUSED( ctx ),
    const ::NS(BaseNodeId) *const SIXTRL_RESTRICT SIXTRL_UNUSED( node_id ),
    ::NS(cuda_ctx_create_flags_t) const SIXTRL_UNUSED( create_flags ),
    const NS(ThreadUniqueLock) *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( ptr_lock ) ) {
    return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

::NS(status_t) NS(CudaContext_init_as_ext_shared)(
    ::NS(BaseContext)* SIXTRL_RESTRICT SIXTRL_UNUSED( ctx ),
    ::NS(cuda_ctx_int_repr_type) const SIXTRL_UNUSED( ext_ctx_repr ),
    const ::NS(ThreadUniqueLock) *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( ptr_lock ) ) {
    return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

const ::NS(BaseNodeId) *const NS(CudaContext_node_id)(
    const ::NS(BaseContext) *const SIXTRL_RESTRICT SIXTRL_UNUSED( ctx ),
    const ::NS(ThreadUniqueLock) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_lock ) ) SIXTRL_NOEXCEPT {
    return nullptr;
}

#endif /* SIXTRACKL_ENABLE_BACKEND_CUDA && SIXTRL_CUDA_PLUGIN_BUILT */
#endif /* C++, Host */
