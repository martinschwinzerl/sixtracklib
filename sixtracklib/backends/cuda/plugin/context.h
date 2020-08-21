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

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN static std::shared_ptr< CudaContext >
        MAKE_PRIMARY_CTX( CudaNodeId const& SIXTRL_RESTRICT_REF node_id );

        SIXTRL_HOST_FN static std::shared_ptr< CudaContext >
        MAKE_PRIMARY_CTX_DETAILED(
            CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
            flags_type const flags_type, thread_id_type const tid,
            CudaBackend& SIXTRL_RESTRICT_REF backend,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN static std::shared_ptr< CudaContext > MAKE_CTX(
            CudaNodeId const& SIXTRL_RESTRICT_REF node_id );

        SIXTRL_HOST_FN static std::shared_ptr< CudaContext > MAKE_CTX_DETAILED(
            CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
            flags_type const flags_type, thread_id_type const tid,
            CudaBackend& SIXTRL_RESTRICT_REF backend,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        /* ================================================================ */

        SIXTRL_HOST_FN ~CudaContext();

        SIXTRL_HOST_FN bool is_primary() const;
        SIXTRL_HOST_FN CudaNodeId const& node_id() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN ctx_handle_type raw_ctx_handle(
            guard_type const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN const_ctx_handle_type raw_ctx_handle(
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN CudaContext( CudaBackend& SIXTRL_RESTRICT_REF cuda_be );

        SIXTRL_HOST_FN CudaContext( CudaContext const& ) = delete;
        SIXTRL_HOST_FN CudaContext( CudaContext&& ) = delete;

        SIXTRL_HOST_FN CudaContext& operator=( CudaContext const& ) = delete;
        SIXTRL_HOST_FN CudaContext& operator=( CudaContext&& ) = delete;


        SIXTRL_HOST_FN status_t do_attach_to_thread( thread_id_type tid,
            guard_type const& SIXTRL_RESTRICT_REF lock ) override;

        SIXTRL_HOST_FN status_t do_detach_from_thread( thread_id_type tid,
            guard_type const& SIXTRL_RESTRICT_REF lock ) override;

        SIXTRL_HOST_FN status_t do_set_owner_thread_id( thread_id_type tid,
            guard_type const& SIXTRL_RESTRICT_REF lock ) override;


        SIXTRL_HOST_FN status_t init_primary_ctx(
            CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
            flags_type const create_flags,
            CudaBackend& SIXTRL_RESTRICT_REF backend,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN status_t init_owned_ctx(
            CudaNodeId const& SIXTRL_RESTRICT_REF node_id,
            flags_type const create_flags,
            CudaBackend& SIXTRL_RESTRICT_REF backend,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        private:

        CudaNodeId m_node_id = SIXTRL_CXX_NAMESPACE::CudaNodeId{};
        ctx_handle_type m_ctx_handle = nullptr;
        flags_type  m_flags = FLAGS_NONE;
    };

} /* ns: SIXTRL_CXX_NAMESPACE */

#elif !defined( _GPUCODE ) /* C, Host */

#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_BACKENDS_CUDA_PLUGIN_CONTEXT_H__ */
