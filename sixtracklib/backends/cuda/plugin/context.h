#ifndef SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CONTEXT_H__
#define SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CONTEXT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/plugin/node.h"
    #include "sixtracklib_base/control/context.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if SIXTRACKL_ENABLE_BACKEND_CUDA
        #include <cuda.h>
    #endif /* CUDA enabled */

    #if defined( __cplusplus )
        #include <memory>
        #include <mutex>
        #include <string>
        #include <thread>
        #include <type_traits>
        #include <vector>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
    ( SIXTRACKL_ENABLE_BACKEND_CUDA == 1 )

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class CudaBackend;
    class CudaContext;

    class SIXTRL_EXPORT_API CudaContext :
        public SIXTRL_CXX_NAMESPACE::BaseMTShareableContext
    {
        public:

        static_assert( std::is_pointer< ::CUcontext >::value,
            "Requirement that ::CUcontext is a type-alias to a pointer "
            "type is violated" );

        using flags_type = unsigned int; /* CUDA uses this for flags! */
        using status_type = SIXTRL_CXX_NAMESPACE::status_t;
        using node_id_type = SIXTRL_CXX_NAMESPACE::CudaNodeId;

        using ctx_handle_type = ::CUcontext;
        using const_ctx_handle_type = typename std::add_pointer<
            typename std::add_const< typename std::remove_pointer<
                ctx_handle_type >::type >::type >::type;

        using ctx_handle_int_repr_type = std::intptr_t;


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

        static constexpr flags_type CREATE_OWNED_CTX =
            flags_type{ 0x02000000 };
        static constexpr flags_type HAS_OWNERSHIP_CTX = CREATE_OWNED_CTX;

        static_assert( ( CREATE_OWNED_CTX & CREATE_CUDA_FLAGS_BITMASK ) ==
                         FLAGS_NONE,
                        "CREATE_OWNED_CTX has to be disjunct from the upstream "
                        "cuda create context flags" );

        static constexpr flags_type ALL_FLAGS =
            CREATE_CUDA_FLAGS_BITMASK | CREATE_PRIMARY_CTX;

        static constexpr flags_type ALL_PRIMARY_CTX_CREATE_FLAGS =
            CREATE_SCHED_SPIN | CREATE_SCHED_YIELD |
            CREATE_SCHED_BLOCKING_SYNC | CREATE_SCHED_AUTO;

        static constexpr flags_type ALL_OWNED_CTX_CREATE_FLAGS =
            CREATE_SCHED_SPIN | CREATE_SCHED_YIELD |
            CREATE_SCHED_BLOCKING_SYNC | CREATE_SCHED_AUTO |
            CREATE_MAP_HOST;

        static constexpr flags_type DEFAULT_PRIMARY_CREATE_FLAGS =
            CREATE_SCHED_AUTO | CREATE_PRIMARY_CTX | CREATE_MAP_HOST;

        static constexpr flags_type DEFAULT_OWNED_CREATE_FLAGS =
            CREATE_SCHED_AUTO;

        /* ---------------------------------------------------------------- */

        SIXTRL_STATIC SIXTRL_HOST_FN
        ctx_handle_int_repr_type CURRENT_CTX_INT_REPR();

        SIXTRL_STATIC SIXTRL_HOST_FN
        status_type SET_CURRENT_CTX_BY_INT_REPR(
            ctx_handle_int_repr_type const ctx_int_repr,
            ctx_handle_int_repr_type* SIXTRL_RESTRICT prev_ctx );

        /* ================================================================ */

        SIXTRL_HOST_FN explicit CudaContext(
            thread_id_type const& SIXTRL_RESTRICT_REF tid = thread_id_type{} );

        SIXTRL_HOST_FN explicit CudaContext(
            CudaBackend& SIXTRL_RESTRICT_REF cuda_be,
            thread_id_type const& SIXTRL_RESTRICT_REF tid = thread_id_type{} );

        SIXTRL_HOST_FN CudaContext( CudaContext const& ) = delete;
        SIXTRL_HOST_FN CudaContext( CudaContext&& ) = delete;

        SIXTRL_HOST_FN CudaContext& operator=( CudaContext const& ) = delete;
        SIXTRL_HOST_FN CudaContext& operator=( CudaContext&& ) = delete;

        SIXTRL_HOST_FN ~CudaContext();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t init(
            CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
            flags_type const create_flags = DEFAULT_OWNED_CREATE_FLAGS );

        SIXTRL_HOST_FN status_t init(
            CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
            flags_type const create_flags,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t init_as_primary(
            CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
            flags_type const create_flags = DEFAULT_PRIMARY_CREATE_FLAGS );

        SIXTRL_HOST_FN status_t init_as_primary(
            CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
            flags_type const create_flags,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t init_as_ext_shared(
            ctx_handle_int_repr_type const ext_ctx_repr );

        SIXTRL_HOST_FN status_t init_as_ext_shared(
            ctx_handle_int_repr_type const ext_ctx_repr,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        /* ---------------------------------------------------------------- */

        SIXTRL_HOST_FN bool is_primary() const;
        SIXTRL_HOST_FN bool is_primary(
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_ownership() const;
        SIXTRL_HOST_FN bool has_ownership(
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_ext_shared() const;
        SIXTRL_HOST_FN bool is_ext_shared(
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN CudaNodeId node_id() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN CudaNodeId const& node_id(
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN ctx_handle_type handle(
            guard_type const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN const_ctx_handle_type handle(
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN ctx_handle_int_repr_type handle_int_repr() const;
        SIXTRL_HOST_FN ctx_handle_int_repr_type handle_int_repr(
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN status_t do_attach_thread(
            thread_id_type const& SIXTRL_RESTRICT_REF tid,
            guard_type const& SIXTRL_RESTRICT_REF lock ) override;

        SIXTRL_HOST_FN status_t do_detach_thread(
            thread_id_type  const& SIXTRL_RESTRICT_REF tid,
            guard_type const& SIXTRL_RESTRICT_REF lock ) override;

        private:

        CudaNodeId m_node_id = SIXTRL_CXX_NAMESPACE::CudaNodeId{};
        ctx_handle_type m_ctx_handle = nullptr;
        flags_type  m_flags = FLAGS_NONE;
    };

    SIXTRL_STATIC SIXTRL_HOST_FN bool Context_is_cuda_context(
        const SIXTRL_CXX_NAMESPACE::BaseContext *const
            SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT;

    SIXTRL_STATIC SIXTRL_HOST_FN CudaContext const* CudaContext_get(
        const SIXTRL_CXX_NAMESPACE::BaseContext *const
            SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT;

    SIXTRL_STATIC SIXTRL_HOST_FN CudaContext* CudaContext_get(
        SIXTRL_CXX_NAMESPACE::BaseContext*
            SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT;

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE bool Context_is_cuda_context( const
        SIXTRL_CXX_NAMESPACE::BaseContext *const
            SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( ( ptr_base != nullptr ) &&
                 ( ptr_base->backend_id() == st::BACKEND_CUDA ) &&
                 ( ptr_base->is_mt_shareable_context() ) );
    }

    SIXTRL_INLINE CudaContext const* CudaContext_get(
        const SIXTRL_CXX_NAMESPACE::BaseContext *const
            SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( st::Context_is_cuda_context( ptr_base ) )
            ? static_cast< st::CudaContext const* >( ptr_base ) : nullptr;
    }

    SIXTRL_INLINE CudaContext* CudaContext_get(
        SIXTRL_CXX_NAMESPACE::BaseContext*
            SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( st::Context_is_cuda_context( ptr_base ) )
            ? static_cast< st::CudaContext* >( ptr_base ) : nullptr;
    }

} /* ns: SIXTRL_CXX_NAMESPACE */

#endif /* SIXTRACKL_ENABLE_BACKEND_CUDA */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                   Exported Plugin C-API :: Types                !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

#if defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
           ( SIXTRACKL_ENABLE_BACKEND_CUDA == 1 ) && \
    defined( SIXTRL_CUDA_PLUGIN_BUILT ) && ( SIXTRL_CUDA_PLUGIN_BUILT == 1 )

#if defined( __cplusplus ) && !defined( _GPUCODE )

typedef SIXTRL_CXX_NAMESPACE::CudaContext NS(CudaContext);
typedef SIXTRL_CXX_NAMESPACE::CudaContext::flags_type
        NS(cuda_ctx_create_flags_t);
typedef SIXTRL_CXX_NAMESPACE::CudaContext::ctx_handle_int_repr_type
        NS(cuda_ctx_int_repr_type);

#elif !defined( _GPUCODE ) /* C, Host */

struct NS(CudaContext);
typedef unsigned int NS(cuda_ctx_create_flags_t);
typedef intptr_t NS(cuda_ctx_int_repr_type);

#endif /* C++ / C, Host */
#else /* !SIXTRACKL_ENABLE_BACKEND_CUDA || !SIXTRL_CUDA_PLUGIN_BUILT */

typedef void NS(CudaContext);
typedef unsigned int NS(cuda_ctx_create_flags_t);
typedef intptr_t NS(cuda_ctx_int_repr_type);

#endif /* SIXTRACKL_ENABLE_BACKEND_CUDA && SIXTRL_CUDA_PLUGIN_BUILT */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                Exported Plugin C-API :: Functions               !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

SIXTRL_EXPORT_API SIXTRL_HOST_FN
NS(cuda_ctx_int_repr_type) NS(CudaContext_current_ctx)( void );

SIXTRL_EXPORT_API SIXTRL_HOST_FN
NS(status_t) NS(CudaContext_set_current_ctx)(
    NS(cuda_ctx_int_repr_type) const ctx_to_change_to,
    NS(cuda_ctx_int_repr_type)* SIXTRL_RESTRICT ptr_current_ctx_repr );

SIXTRL_EXPORT_API SIXTRL_HOST_FN
NS(BaseContext)* NS(CudaContext_create)(
    const NS(ThreadId) *const SIXTRL_RESTRICT tid );

SIXTRL_EXPORT_API SIXTRL_HOST_FN NS(status_t) NS(CudaContext_init)(
    NS(BaseContext)* SIXTRL_RESTRICT ctx,
    const NS(BaseNodeId) *const SIXTRL_RESTRICT node_id,
    NS(cuda_ctx_create_flags_t) const create_flags,
    const NS(ThreadUniqueLock) *const SIXTRL_RESTRICT ptr_lock );

SIXTRL_EXPORT_API SIXTRL_HOST_FN NS(status_t) NS(CudaContext_init_as_primary)(
    NS(BaseContext)* SIXTRL_RESTRICT ctx,
    const NS(BaseNodeId) *const SIXTRL_RESTRICT node_id,
    NS(cuda_ctx_create_flags_t) const create_flags,
    const NS(ThreadUniqueLock) *const SIXTRL_RESTRICT ptr_lock );

SIXTRL_EXPORT_API SIXTRL_HOST_FN
NS(status_t) NS(CudaContext_init_as_ext_shared)(
    NS(BaseContext)* SIXTRL_RESTRICT ctx,
    NS(cuda_ctx_int_repr_type) const ext_ctx_repr,
    const NS(ThreadUniqueLock) *const SIXTRL_RESTRICT ptr_lock );

SIXTRL_EXPORT_API SIXTRL_HOST_FN
const NS(BaseNodeId) *const NS(CudaContext_node_id)(
    const NS(BaseContext) *const SIXTRL_RESTRICT ctx,
    const NS(ThreadUniqueLock) *const
        SIXTRL_RESTRICT ptr_lock ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CONTEXT_H__ */
