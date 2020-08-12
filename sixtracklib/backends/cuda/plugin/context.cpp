#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/plugin/context.h"
    #include "sixtracklib/backends/cuda/plugin/device.h"
    #include "sixtracklib/backends/cuda/plugin/cuda_tools.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cuda.h>
    #if defined( __cplusplus )
        #include <algorithm>
        #include <memory>
        #include <string>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using stored_ctx_t = st::CudaStoredContext;
        using this_t = st::CudaContext;
        using dev_t  = st::CudaDevice;
    }

    constexpr stored_ctx_t::flags_type stored_ctx_t::FLAGS_NONE;

    constexpr stored_ctx_t::flags_type stored_ctx_t::CREATE_SCHED_AUTO;
    constexpr stored_ctx_t::flags_type stored_ctx_t::CREATE_SCHED_SPIN;
    constexpr stored_ctx_t::flags_type stored_ctx_t::CREATE_SCHED_YIELD;
    constexpr stored_ctx_t::flags_type stored_ctx_t::CREATE_SCHED_BLOCKING_SYNC;
    constexpr stored_ctx_t::flags_type stored_ctx_t::CREATE_SCHED_BITMASK;

    constexpr stored_ctx_t::flags_type stored_ctx_t::CREATE_MAP_HOST;
    constexpr stored_ctx_t::flags_type stored_ctx_t::CREATE_CUDA_FLAGS_BITMASK;

    constexpr stored_ctx_t::flags_type stored_ctx_t::CREATE_PRIMARY_CTX;
    constexpr stored_ctx_t::flags_type stored_ctx_t::IS_PRIMARY_CTX;
    constexpr stored_ctx_t::flags_type stored_ctx_t::TAKE_OWNERSHIP;
    constexpr stored_ctx_t::flags_type stored_ctx_t::HAS_OWNERSHIP;

    constexpr stored_ctx_t::flags_type stored_ctx_t::ALL_FLAGS;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    stored_ctx_t::CudaStoredContext() :
        m_associated_thread_ids(), m_device( dev_t::ILLEGAL_DEVICE_HANDLE ),
        m_ctx( nullptr ), m_flags( stored_ctx_t::FLAGS_NONE )
    {

    }

    /* ---------------------------------------------------------------- */

    bool stored_ctx_t::is_primary( stored_ctx_t::lock_t const&
        SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT
    {
        static_assert(
            stored_ctx_t::IS_PRIMARY_CTX != stored_ctx_t::FLAGS_NONE,
            "IS_PRIMARY_CTX flag required to be different from FLAGS_NONE" );

        return ( ( this->is_active( guard ) ) &&
                 (   stored_ctx_t::IS_PRIMARY_CTX ==
                   ( stored_ctx_t::IS_PRIMARY_CTX & this->m_flags ) ) );
    }

    bool stored_ctx_t::has_ownership( stored_ctx_t::lock_t const&
        SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT
    {
        static_assert(
            stored_ctx_t::HAS_OWNERSHIP != stored_ctx_t::FLAGS_NONE,
            "HAS_OWNERSHIP flag required to be different from FLAGS_NONE" );

        return ( ( this->is_active( guard ) ) &&
                 (   stored_ctx_t::HAS_OWNERSHIP ==
                   ( stored_ctx_t::HAS_OWNERSHIP & this->m_flags ) ) );
    }

    stored_ctx_t::size_type stored_ctx_t::num_associated_threads(
        stored_ctx_t::lock_t const& guard ) const SIXTRL_NOEXCEPT
    {
        return ( this->is_active( guard ) )
            ? this->m_associated_thread_ids.size()
            : stored_ctx_t::size_type{ 0 };
    }

    bool stored_ctx_t::is_associated_with_any_thread( stored_ctx_t::lock_t
        const& SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->is_active( guard ) ) &&
                 ( !this->m_associated_thread_ids.empty() ) );
    }

    bool stored_ctx_t::is_associated_with_thread(
        stored_ctx_t::thread_id_type const tid,
        stored_ctx_t::lock_t const& SIXTRL_RESTRICT_REF
            guard ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->is_active( guard ) ) &&
                 ( tid != stored_ctx_t::thread_id_type{} ) &&
                 ( !this->m_associated_thread_ids.empty() ) &&
                 ( std::find( this->m_associated_thread_ids.begin(),
                              this->m_associated_thread_ids.end(), tid ) !=
                              this->m_associated_thread_ids.end() ) );
    }

    stored_ctx_t::thread_id_type const*
    stored_ctx_t::associated_thread_ids_begin( stored_ctx_t::lock_t const&
        SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT
    {
        return ( this->is_associated_with_any_thread( guard ) )
               ? this->m_associated_thread_ids.data() : nullptr;
    }

    stored_ctx_t::thread_id_type const*
    stored_ctx_t::associated_thread_ids_end( stored_ctx_t::lock_t const&
        SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT
    {
        auto ptr_end = this->associated_thread_ids_begin( guard );
        if( ptr_end != nullptr )
            std::advance( ptr_end, this->m_associated_thread_ids.size() );
        return ptr_end;
    }

    stored_ctx_t::status_type stored_ctx_t::associate_with_current_thread(
        stored_ctx_t::lock_t const& SIXTRL_RESTRICT_REF guard )
    {
        return this->associate_with_thread( std::this_thread::get_id(), guard );
    }

    stored_ctx_t::status_type stored_ctx_t::associate_with_thread(
        stored_ctx_t::thread_id_type tid,
        stored_ctx_t::lock_t const& SIXTRL_RESTRICT_REF guard )
    {
        stored_ctx_t::status_type status = st::STATUS_GENERAL_FAILURE;

        if( ( this->is_active( guard ) ) &&
            ( tid != stored_ctx_t::thread_id_type{} ) )
        {
            if( std::find( this->m_associated_thread_ids.begin(),
                           this->m_associated_thread_ids.end(), tid ) ==
                           this->m_associated_thread_ids.end() )
            {
                this->m_associated_thread_ids.push_back( tid );
            }

            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    stored_ctx_t::status_type stored_ctx_t::disassociate_from_current_thread(
        stored_ctx_t::lock_t const& SIXTRL_RESTRICT_REF guard )
    {
        return this->disassociate_from_thread(
            std::this_thread::get_id(), guard );
    }

    stored_ctx_t::status_type stored_ctx_t::disassociate_from_thread(
        stored_ctx_t::thread_id_type const tid,
        stored_ctx_t::lock_t const& SIXTRL_RESTRICT_REF guard )
    {
        stored_ctx_t::status_type status = st::STATUS_GENERAL_FAILURE;

        if( this->associate_with_thread( tid, guard ) )
        {
            SIXTRL_ASSERT( this->lockable() != nullptr );
            SIXTRL_ASSERT( this->lockable() == guard.mutex() );
            SIXTRL_ASSERT( guard.owns_lock() );

            auto it = std::find( this->m_associated_thread_ids.begin(),
                                 this->m_associated_thread_ids.end(), tid );

            SIXTRL_ASSERT( it != this->m_associated_thread_ids.end() );
            this->m_associated_thread_ids.erase( it );
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    stored_ctx_t::cuda_handle_type stored_ctx_t::cuda_handle(
        stored_ctx_t::lock_t const& SIXTRL_RESTRICT_REF guard ) SIXTRL_NOEXCEPT
    {
        return ( this->is_active( guard ) ) ? this->m_ctx : nullptr;
    }

    stored_ctx_t::const_cuda_handle_type
    stored_ctx_t::cuda_handle( stored_ctx_t::lock_t const&
        SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT
    {
        return ( this->is_active( guard ) ) ? this->m_ctx : nullptr;
    }

    stored_ctx_t::cuda_handle_int_repr_type
    stored_ctx_t::cuda_handle_int_repr( stored_ctx_t::lock_t const&
        SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< stored_ctx_t::cuda_handle_int_repr_type >(
            this->cuda_handle( guard ) );
    }

    bool stored_ctx_t::is_active( stored_ctx_t::lock_t const&
        SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT
    {
        bool result = false;

        if( ( this->lockable() != nullptr ) &&
            ( this->lockable() == guard.mutex() ) && ( guard.owns_lock() ) )
        {
            if( ( this->m_device.cuda_handle() !=
                  dev_t::ILLEGAL_DEVICE_HANDLE ) &&
                ( this->m_ctx != nullptr ) )
            {
                result = true;
            }

            SIXTRL_ASSERT( ( result ) || (
                ( this->m_device.cuda_handle() == dev_t::ILLEGAL_DEVICE_HANDLE ) &&
                ( this->m_ctx == nullptr ) &&
                ( this->m_associated_thread_ids.empty() ) &&
                ( this->m_flags == stored_ctx_t::FLAGS_NONE ) ) );
        }

        return result;
    }

    stored_ctx_t::status_type stored_ctx_t::init_as_primary_ctx(
        ::CUdevice const cuda_dev_handle,
        stored_ctx_t::lock_t const& SIXTRL_RESTRICT_REF guard )
    {
        stored_ctx_t::status_type status = st::STATUS_GENERAL_FAILURE;

        if( ( guard.owns_lock() ) && ( guard.mutex() == this->lockable() ) &&
            ( !this->is_active( guard ) ) &&
            (  this->m_flags == stored_ctx_t::FLAGS_NONE ) &&
            ( cuda_dev_handle != dev_t::ILLEGAL_DEVICE_HANDLE ) &&
            ( this->m_associated_thread_ids.empty() ) )
        {
            /* Do not engage in the push/pop stack but enforce that each
             * thread can only have one context -> this is less general than
             * allowed but should be sufficient for what we would like to do */

            ::CUcontext current_ctx = nullptr;
            SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxGetCurrent, ( &current_ctx ) );

            if( ( current_ctx == nullptr ) && ( this->m_device.init(
                    cuda_dev_handle ) == st::STATUS_SUCCESS ) )
            {
                ::CUcontext temp_ctx = nullptr;
                SIXTRL_CUDA_DRIVER_API_CALL( ::cuDevicePrimaryCtxRetain,
                    ( &temp_ctx, cuda_dev_handle ) );

                if( temp_ctx != nullptr )
                {
                    this->m_flags |= this_t::IS_PRIMARY_CTX;
                    this->m_ctx = temp_ctx;

                    SIXTRL_ASSERT( this->m_associated_thread_ids.empty() );
                    this->m_associated_thread_ids.push_back(
                        std::this_thread::get_id() );

                    status = st::STATUS_SUCCESS:
                }

                if( status != st::STATUS_GENERAL_FAILURE )
                {
                    this->m_device.reset();
                    this->m_associated_thread_ids.clear();
                    this->m_flags = stored_ctx_t::FLAGS_NONE;
                    this->m_ctx = nullptr;
                }
            }
        }

        return status;
    }

    stored_ctx_t::status_type stored_ctx_t::init_as_owned_ctx(
        ::CUdevice const cuda_dev_handle,
        stored_ctx_t::flags_type const create_flags,
        stored_ctx_t::lock_t const& SIXTRL_RESTRICT_REF guard )
    {
        stored_ctx_t::status_type status = st::STATUS_GENERAL_FAILURE;

        if( ( guard.owns_lock() ) && ( guard.mutex() == this->lockable() ) &&
            ( !this->is_active( guard ) ) &&
            (  this->m_flags == stored_ctx_t::FLAGS_NONE ) &&
            ( cuda_dev_handle != dev_t::ILLEGAL_DEVICE_HANDLE ) &&
            ( this->m_associated_thread_ids.empty() ) )
        {
            SIXTRL_ASSERT( this->m_associated_thread_ids.empty() );

            if( this->m_device.init( cuda_dev_handle ) == st::STATUS_SUCCESS )
            {
                stored_ctx_t::flags_type const cu_flags =
                    stored_ctx_t::CREATE_CUDA_FLAGS_BITMASK & create_flags;

                ::CUcontext temp_ctx = nullptr;
                SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxCreate,
                    ( &temp_ctx, cu_flags, cuda_dev_handle ) );

                if( temp_ctx != nullptr )
                {
                    this->m_flags |= this_t::HAS_OWNERSHIP;
                    this->m_flags |= cu_flags;
                    this->m_ctx    = temp_ctx;
                    this->m_associated_thread_ids.push_back(
                        std::this_thread::get_id() );
                    status = st::STATUS_SUCCESS:
                }

                if( status != st::STATUS_GENERAL_FAILURE )
                {
                    this->m_device.reset();
                    this->m_associated_thread_ids.clear();
                    this->m_flags = stored_ctx_t::FLAGS_NONE;
                    if( this->m_ctx != nullptr )
                    {
                        SIXTRL_CUDA_DRIVER_API_CALL(
                            ::cuCtxDestroy, ( this->m_ctx ) );
                    }
                }
            }
        }

        return status;
    }

    stored_ctx_t::status_type stored_ctx_t::init_as_nonowned_ctx(
        ::CUdevice const cuda_dev_handle,
        ::CUcontext ext_context, lock_t const& SIXTRL_RESTRICT_REF guard )
    {
        stored_ctx_t::status_type status = st::STATUS_GENERAL_FAILURE;

        if( ( guard.owns_lock() ) && ( guard.mutex() == this->lockable() ) &&
            ( !this->is_active( guard ) ) &&
            (  this->m_flags == stored_ctx_t::FLAGS_NONE ) &&
            ( cuda_dev_handle != dev_t::ILLEGAL_DEVICE_HANDLE ) &&
            ( ext_context != nullptr ) &&
            ( this->m_associated_thread_ids.empty() ) )
        {
            if( this->m_device.init( cuda_dev_handle ) == st::STATUS_SUCCESS )
            {
                stored_ctx_t::flags_type flags = stored_ctx_t::FLAGS_NONE;

                ::CUcontext temp_ctx = nullptr;
                SIXTRL_CUDA_DRIVER_API_CALL( ::cuCtxCreate,
                    ( &temp_ctx, cu_flags, cuda_dev_handle ) );

                if( temp_ctx != nullptr )
                {
                    this->m_flags |= this_t::HAS_OWNERSHIP;
                    this->m_flags |= cu_flags;
                    this->m_ctx    = temp_ctx;
                    this->m_associated_thread_ids.push_back(
                        std::this_thread::get_id() );
                    status = st::STATUS_SUCCESS:
                }

                if( status != st::STATUS_GENERAL_FAILURE )
                {
                    this->m_device.reset();
                    this->m_associated_thread_ids.clear();
                    this->m_flags = stored_ctx_t::FLAGS_NONE;
                    if( this->m_ctx != nullptr )
                    {
                        SIXTRL_CUDA_DRIVER_API_CALL(
                            ::cuCtxDestroy, ( this->m_ctx ) );
                    }
                }
            }
        }

        return status;
    }




    {
        st::status_t status = st::STATUS_GENERAL_FAILURE;
        this_t::flags_type used_flags = this_t::FLAGS_NONE;

        bool const is_primary_ctx = this->is_primary();
        bool const take_ownership = this->has_ownership();

        if( ( is_primary_ctx ) && ( ext_context == nullptr ) &&
            ( cuda_device_handle != dev_t::ILLEGAL_DEVICE_HANDLE ) )
        {

        }
        else if( !is_primary_ctx && take_ownership &&
                  cuda_device_handle != dev_t::ILLEGAL_DEVICE_HANDLE )
        {
            status = this->m_device.init( cuda_device_handle );

            if( status == st::STATUS_SUCCESS )
            {

            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            this->m_flags &= used_flags;
        }
    }

    /* ********************************************************************* */

    this_t::StoredCtx::StoredCtx(
        ::CUdevice const cuda_device_handle,
        ::CUcontext ext_context,
        this_t::flags_type const create_flags ) :
        m_device(), m_flags( create_flags )
    {
        st::status_t status = st::STATUS_GENERAL_FAILURE;
        this_t::flags_type used_flags = this_t::FLAGS_NONE;

        bool const is_primary_ctx = this->is_primary();
        bool const take_ownership = this->has_ownership();

        if( ( is_primary_ctx ) && ( ext_context == nullptr ) &&
            ( cuda_device_handle != dev_t::ILLEGAL_DEVICE_HANDLE ) )
        {
            status = this->m_device.init( cuda_device_handle );
            if( status == st::STATUS_SUCCESS )
            {
                SIXTRL_CUDA_DRIVER_API_NOTHROW_CALL(
                    ::cuDevicePrimaryCtxRetain,
                        ( &this->m_ctx, cuda_device_handle ) );

                used_flags |= this_t::IS_PRIMARY_CTX;
            }
        }
        else if( !is_primary_ctx && take_ownership &&
                  cuda_device_handle != dev_t::ILLEGAL_DEVICE_HANDLE )
        {
            status = this->m_device.init( cuda_device_handle );

            if( status == st::STATUS_SUCCESS )
            {

            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            this->m_flags &= used_flags;
        }
    }

    bool this_t::StoredCtx::is_primary() const SIXTRL_NOEXCEPT {
        return ( ( this_t::IS_PRIMARY_CTX != this_t::FLAGS_NONE ) &&
                 ( this_t::IS_PRIMARY_CTX == (
                   this_t::IS_PRIMARY_CTX & this->m_flags ) ) );
    }

    bool this_t::StoredCtx::has_ownership() const SIXTRL_NOEXCEPT {
        return ( ( this_t::HAS_OWNERSHIP != this_t::FLAGS_NONE ) &&
                 ( this_t::HAS_OWNERSHIP == (
                   this_t::HAS_OWNERSHIP & this->m_flags ) ) );
    }

    this_t::StoredCtx::~StoredCtx()
    {
        if( this->is_primary() )
        {
            if( this->m_device.cuda_handle() != dev_t::ILLEGAL_DEVICE_HANDLE )
            {
                unsigned int primary_ctx_flags = 0;
                int primary_ctx_active = 0;

                SIXTRL_ASSERT( this->m_device.is_legal() );
                SIXTRL_CUDA_DRIVER_API_NOTHROW_CALL(
                        ::cuDevicePrimaryCtxGetState,
                        ( this->m_device.cuda_handle(), &primary_ctx_flags,
                          &primary_ctx_active ) );

                if( primary_ctx_active == 1 )
                {
                    SIXTRL_CUDA_DRIVER_API_NOTHROW_CALL(
                        ::cuDevicePrimaryCtxRelease,
                        ( this->m_device.cuda_handle() ) );
                }
            }
        }
    }

}

#endif /* C++, Host */
