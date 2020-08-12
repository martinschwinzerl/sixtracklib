#ifndef SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CONTEXT_H__
#define SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CONTEXT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/definitions.h"
    #include "sixtracklib/backends/cuda/plugin/device.h"
    #include "sixtracklib_base/backend/backend_obj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cuda.h>
    #if defined( __cplusplus )
        #include <memory>
        #include <mutex>
        #include <string>
        #include <thread>
        #include <type_traits>
        #include <vector>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class CudaStoredContext
    {
        public:

        static_assert( std::is_pointer< ::CUcontext >::value,
            "Requirement that ::CUcontext is a type-alias to a pointer "
            "type is violated" );

        using flags_type = unsigned int; /* CUDA uses this for flags! */
        using size_type = SIXTRL_CXX_NAMESPACE::size_t;
        using device_type = SIXTRL_CXX_NAMESPACE::CudaDevice;
        using thread_id_type = std::thread::id;
        using status_type = SIXTRL_CXX_NAMESPACE::status_t;

        using cuda_handle_type = ::CUcontext;
        using const_cuda_handle_type = typename std::add_pointer<
            typename std::add_const< typename std::remove_pointer<
                ::CUcontext >::type >::type >::type;
        using cuda_handle_int_repr_type = std::intptr_t;

        using lockable_t = std::mutex;
        using lock_t = std::unique_lock< lockable_t >;

        static constexpr flags_type FLAGS_NONE = flags_type{ 0x00000000 };
        static constexpr flags_type CREATE_SCHED_AUTO =
            static_cast< flags_type >( ::CU_CTX_SCHED_AUTO );

        static constexpr flags_type CREATE_SCHED_SPIN =
            static_cast< flags_type >( ::CU_CTX_SCHED_SPIN );

        static constexpr flags_type CREATE_SCHED_YIELD =
            static_cast< flags_type >( ::CU_CTX_SCHED_YIELD );

        static constexpr flags_type CREATE_SCHED_BLOCKING_SYNC =
            static_cast< flags_type >( ::CU_CTX_SCHED_SPIN );

        static constexpr flags_type CREATE_SCHED_BITMASK =
            static_cast< flags_type >( ::CU_CTX_SCHED_MASK );

        static constexpr flags_type CREATE_MAP_HOST =
            static_cast< flags_type >( ::CU_CTX_MAP_HOST );

        static constexpr flags_type CREATE_CUDA_FLAGS_BITMASK =
            static_cast< flags_type >( ::CU_CTX_FLAGS_MASK );

        static constexpr flags_type CREATE_PRIMARY_CTX =
            flags_type{ 0x01000000 };
        static constexpr flags_type IS_PRIMARY_CTX = CREATE_PRIMARY_CTX;

        static_assert( ( CREATE_PRIMARY_CTX & CREATE_CUDA_FLAGS_BITMASK ) ==
                         FLAGS_NONE,
                        "CREATE_PRIMARY_CTX has to be disjunct from the upstream "
                        "cuda create context flags" );

        static constexpr flags_type TAKE_OWNERSHIP = flags_type{ 0x02000000 };
        static constexpr flags_type HAS_OWNERSHIP  = TAKE_OWNERSHIP;

        static_assert( ( TAKE_OWNERSHIP & CREATE_CUDA_FLAGS_BITMASK ) ==
                         FLAGS_NONE,
                        "TAKE_OWNERSHIP has to be disjunct from the upstream "
                        "cuda create context flags" );

        static constexpr flags_type ALL_FLAGS =
            CREATE_CUDA_FLAGS_BITMASK | CREATE_PRIMARY_CTX | TAKE_OWNERSHIP;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN CudaStoredContext();

        SIXTRL_HOST_FN CudaStoredContext(
            CudaStoredContext const& ) = delete;

        SIXTRL_HOST_FN CudaStoredContext(
            CudaStoredContext&& ) = default;

        SIXTRL_HOST_FN CudaStoredContext& operator=(
            CudaStoredContext const& ) = delete;

        SIXTRL_HOST_FN CudaStoredContext& operator=(
            CudaStoredContext&& ) = default;

        SIXTRL_HOST_FN ~CudaStoredContext();

        /* ---------------------------------------------------------------- */

        SIXTRL_HOST_FN bool is_primary(
            lock_t const& SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_primary() const{
            return this->is_primary( lock_t{ this->m_lockable } ); }


        SIXTRL_HOST_FN bool has_ownership(
            lock_t const& SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_ownership() const {
            return this->has_ownership( lock_t{ this->m_lockable } ); }


        SIXTRL_HOST_FN size_type num_associated_threads(
            lock_t const& SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_associated_threads() const {
            lock_t guard( this->m_lockable );
            return this->num_associated_threads( guard ); }


        SIXTRL_HOST_FN bool is_associated_with_any_thread(
            lock_t const& SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_associated_with_any_thread() const {
            lock_t guard( this->m_lockable );
            return this->is_associated_with_any_thread( guard ); }


        SIXTRL_HOST_FN bool is_associated_with_thread( thread_id_type const tid,
            lock_t const& SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_associated_with_thread( thread_id_type const
            tid ) const { return this->is_associated_with_thread( tid,
                lock_t{ this->m_lockable } ); }


        SIXTRL_HOST_FN thread_id_type const* associated_thread_ids_begin(
            lock_t const& SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN thread_id_type const* associated_thread_ids_begin() const {
            return this->associated_thread_ids_begin( lock_t{
                    this->m_lockable } ); }


        SIXTRL_HOST_FN thread_id_type const* associated_thread_ids_end(
            lock_t const& SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN thread_id_type const* associated_thread_ids_end() const {
            return this->associated_thread_ids_end(
                lock_t{ this->m_lockable } ); }


        SIXTRL_HOST_FN status_type associate_with_current_thread( lock_t const&
            SIXTRL_RESTRICT_REF guard );

        SIXTRL_HOST_FN status_type associate_with_current_thread() {
            return this->associate_with_current_thread(
                lock_t{ this->m_lockable } ); }


        SIXTRL_HOST_FN status_type associate_with_thread(
            thread_id_type const tid, lock_t const& SIXTRL_RESTRICT_REF guard );

        SIXTRL_HOST_FN status_type associate_with_thread( thread_id_type const
            tid ) { return this->associate_with_thread( tid,
                lock_t{ this->m_lockable } ); }


        SIXTRL_HOST_FN status_type disassociate_from_current_thread(
            lock_t const& SIXTRL_RESTRICT_REF guard );

        SIXTRL_HOST_FN status_type disassociate_from_current_thread() {
            return this->disassociate_from_current_thread(
                lock_t{ this->m_lockable } ); }


        SIXTRL_HOST_FN status_type disassociate_from_thread(
            thread_id_type const tid, lock_t const& SIXTRL_RESTRICT_REF guard );

        SIXTRL_HOST_FN status_type disassociate_from_thread( thread_id_type
            const tid ) { return this->disassociate_from_thread(
                    tid, lock_t{ this->m_lockable } ); }


        SIXTRL_HOST_FN cuda_handle_type cuda_handle(
            lock_t const& SIXTRL_RESTRICT_REF guard ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN cuda_handle_type cuda_handle() {
            return this->cuda_handle( lock_t{ this->m_lockable } ); }


        SIXTRL_HOST_FN const_cuda_handle_type cuda_handle(
            lock_t const& SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN const_cuda_handle_type cuda_handle() const {
            return this->cuda_handle( lock_t{ this->m_lockable } ); }


        SIXTRL_HOST_FN cuda_handle_int_repr_type cuda_handle_int_repr(
            lock_t const& SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN cuda_handle_int_repr_type cuda_handle_int_repr() const {
            return this->cuda_handle_int_repr( lock_t{ this->m_lockable } ); }


        SIXTRL_HOST_FN bool is_active( lock_t const&
            SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_active() const {
                return this->is_active( lock_t{ this->m_lockable } ); }


        SIXTRL_HOST_FN status_type init_as_primary_ctx(
            ::CUdevice const cuda_dev_handle,
            lock_t const& SIXTRL_RESTRICT_REF guard );

        SIXTRL_HOST_FN status_type init_as_primary_ctx(
            ::CUdevice const cuda_dev_handle ) {
            return this->init_as_primary_ctx( cuda_dev_handle,
                lock_t{ this->m_lockable} ); }

        SIXTRL_HOST_FN status_type init_as_owned_ctx(
            ::CUdevice const cuda_dev_handle, flags_type const create_flags,
            lock_t const& SIXTRL_RESTRICT_REF guard );

        SIXTRL_HOST_FN status_type init_as_owned_ctx(
            ::CUdevice const cuda_dev_handle, flags_type const create_flags ) {
            return this->init_as_owned_ctx( cuda_dev_handle, create_flags,
                lock_t{ this->m_lockable } ); }

        SIXTRL_HOST_FN status_type init_as_nonowned_ctx(
            ::CUdevice const cuda_dev_handle, ::CUcontext ext_context,
            lock_t const& SIXTRL_RESTRICT_REF guard );

        SIXTRL_HOST_FN status_type init_as_nonowned_ctx(
            ::CUdevice const cuda_dev_handle, ::CUcontext ext_context ) {
            return this->init_as_nonowned_ctx( cuda_dev_handle, ext_context,
                lock_t{ this->m_lockable } ); }

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT {
            return &this->m_lockable; }

        private:

        std::vector< thread_id_type > m_associated_thread_ids;
        device_type m_device;
        mutable lockable_t  m_lockable;

        ::CUcontext m_ctx = nullptr;
        flags_type  m_flags = FLAGS_NONE;
    };

    class SIXTRL_EXPORT_API CudaContext : public BaseBackendObj
    {
        public:

        using flags_type = uint64_t;
        using size_type = SIXTRL_CXX_NAMESPACE::size_t;
        using device_type = SIXTRL_CXX_NAMESPACE::CudaDevice;

        static constexpr flags_type FLAGS_NONE =
            flags_type{ 0x0000000000000000 };

        static constexpr flags_type CREATE_AS_PRIMARY_CTX =
            flags_type{ 0x0000000000000001 };

        static constexpr flags_type IS_PRIMARY_CTX =
            flags_type{ 0x0000000000000001 };

        static constexpr flags_type CREATE_TAKE_OWNERSHIP =
            flags_type{ 0x0000000000000002 };

        static constexpr flags_type HAS_OWNERSHIP =
            flags_type{ 0x0000000000000002 };

        private:

        using destroy_callback_fn_type = void (*)( ::CUcontext );

        static_assert( std::is_pointer< ::CUcontext >::value,
            "Requirement that ::CUcontext is a type-alias to a pointer "
            "type is violated" );

        struct StoredCtx
        {
            SIXTRL_HOST_FN explicit StoredCtx(
                ::CUdevice const cuda_device_handle =
                    device_type::ILLEGAL_DEVICE_HANDLE,
                ::CUcontext ext_context = nullptr,
                flags_type const create_flags = FLAGS_NONE );

            SIXTRL_HOST_FN StoredCtx( StoredCtx const& ) = delete;
            SIXTRL_HOST_FN StoredCtx( StoredCtx&& ) = default;
            SIXTRL_HOST_FN StoredCtx& operator=( StoredCtx const& ) = delete;
            SIXTRL_HOST_FN StoredCtx& operator=( StoredCtx&& ) = default;

            SIXTRL_HOST_FN ~StoredCtx();

            SIXTRL_HOST_FN bool is_primary() const SIXTRL_NOEXCEPT;
            SIXTRL_HOST_FN bool has_ownership() const SIXTRL_NOEXCEPT;

            device_type m_device;
            ::CUcontext m_ctx = nullptr;
            flags_type  m_flags = FLAGS_NONE;
            destroy_callback_fn_type m_destroy_callback_fn = nullptr;
        };

        using ptr_stored_ctx_type = std::shared_ptr< StoredCtx >;

        public:

        SIXTRL_HOST_FN explicit CudaContext(
            device_type const& SIXTRL_RESTRICT_REF device,
            flags_type const create_flags = CREATE_TAKE_OWNERSHIP );

        SIXTRL_HOST_FN CudaContext( CudaContext const& );
        SIXTRL_HOST_FN CudaContext( CudaContext&& );

        SIXTRL_HOST_FN CudaContext& operator=( CudaContext const& );
        SIXTRL_HOST_FN CudaContext& operator=( CudaContext&& );

        SIXTRL_HOST_FN virtual ~CudaContext() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_primary() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_active() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN ::CUcontext cuda_handle() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN device_type const& device() const SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN device_type& device() SIXTRL_NOEXCEPT;

        private:

        ptr_stored_ctx_type m_stored_ctx;
    };

} /* ns: SIXTRL_CXX_NAMESPACE */

#elif !defined( _GPUCODE ) /* C, Host */

#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CONTEXT_H__ */
