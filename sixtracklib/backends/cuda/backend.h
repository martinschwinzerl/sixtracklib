#ifndef SIXTRACKLIB_BACKENDS_CUDA_BACKEND_BACKEND_H__
#define SIXTRACKLIB_BACKENDS_CUDA_BACKEND_BACKEND_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/backends.h"
    #include "sixtracklib_base/backend/node_backend.h"
    #include "sixtracklib_base/control/context.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( SIXTRACKL_ENABLE_BACKEND_CUDA ) && \
           ( SIXTRACKL_ENABLE_BACKEND_CUDA == 1 )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/plugin/node.h"
    #include "sixtracklib/backends/cuda/plugin/context.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class SIXTRL_EXPORT_API CudaBackend :
        public SIXTRL_CXX_NAMESPACE::BaseNodeBackend
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::NodeId node_id_type;
        typedef SIXTRL_CXX_NAMESPACE::BaseContext base_context_type;
        typedef SIXTRL_CXX_NAMESPACE::CudaContext context_type;

        static constexpr be_symbol_id_t SYMBOL_ID_NODE_ID_CREATE_DEV_HANDLE =
            be_symbol_id_t{ 100 };

        static constexpr be_symbol_id_t SYMBOL_ID_NODE_ID_GET_DEV_HANDLE =
            be_symbol_id_t{ 101 };

        static constexpr be_symbol_id_t SYMBOL_ID_NODE_ID_SET_DEV_HANDLE =
            be_symbol_id_t{ 102 };


        static constexpr be_symbol_id_t SYMBOL_ID_CTX_GET_CURRENT =
            be_symbol_id_t{ 103 };

        static constexpr be_symbol_id_t SYMBOL_ID_CTX_SET_CURRENT =
            be_symbol_id_t{ 104 };

        static constexpr be_symbol_id_t SYMBOL_ID_CTX_CREATE =
            be_symbol_id_t{ 105 };

        static constexpr be_symbol_id_t SYMBOL_ID_CTX_INIT =
            be_symbol_id_t{ 106 };

        static constexpr be_symbol_id_t SYMBOL_ID_CTX_INIT_AS_PRIMARY =
            be_symbol_id_t{ 107 };

        static constexpr be_symbol_id_t SYMBOL_ID_CTX_INIT_AS_EXT_SHARED =
            be_symbol_id_t{ 108 };

        static constexpr be_symbol_id_t SYMBOL_ID_CTX_DELETE =
            be_symbol_id_t{ 109 };

        static constexpr be_symbol_id_t SYMBOL_ID_CTX_GET_NODE_ID =
            be_symbol_id_t{ 110 };


        SIXTRL_HOST_FN CudaBackend();
        SIXTRL_HOST_FN CudaBackend( CudaBackend const& ) = delete;
        SIXTRL_HOST_FN CudaBackend( CudaBackend&& ) = delete;
        SIXTRL_HOST_FN CudaBackend& operator=( CudaBackend const& ) = delete;
        SIXTRL_HOST_FN CudaBackend& operator=( CudaBackend&& ) = delete;
        SIXTRL_HOST_FN virtual ~CudaBackend() = default;

        /* ----------------------------------------------------------------- */

        using SIXTRL_CXX_NAMESPACE::BaseNodeBackend::create_node_id;

        SIXTRL_HOST_FN managed_base_node_id_t create_node_id(
            SIXTRL_CXX_NAMESPACE::CudaNodeId::device_handle_type const handle );

        /* ----------------------------------------------------------------- */
        /* context API */

        using managed_ctx_t = std::shared_ptr< base_context_type >;

        SIXTRL_HOST_FN bool has_context(
            node_id_type const& SIXTRL_RESTRICT_REF node_id ) const;

        SIXTRL_HOST_FN bool has_context(
            node_id_type const& SIXTRL_RESTRICT_REF node_id,
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool inherit_ctx_during_init() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN void enable_inherit_ctx_during_init() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN void disable_inherit_ctx_during_init() SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN managed_ctx_t init_context(
            node_id_type const& SIXTRL_RESTRICT_REF node_id,
            context_type::flags_type const create_flags =
                context_type::DEFAULT_OWNED_CREATE_FLAGS );

        SIXTRL_HOST_FN managed_ctx_t init_context(
            node_id_type const& SIXTRL_RESTRICT_REF node_id,
            context_type::flags_type const create_flags,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN managed_ctx_t init_context_as_primary(
            node_id_type const& SIXTRL_RESTRICT_REF node_id,
            context_type::flags_type const create_flags =
                context_type::DEFAULT_PRIMARY_CREATE_FLAGS );

        SIXTRL_HOST_FN managed_ctx_t init_context_as_primary(
            node_id_type const& SIXTRL_RESTRICT_REF node_id,
            context_type::flags_type const create_flags,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN managed_ctx_t init_context_as_ext_shared(
            context_type::ctx_handle_int_repr_type const ext_ctx_repr );

        SIXTRL_HOST_FN managed_ctx_t init_context_as_ext_shared(
            context_type::ctx_handle_int_repr_type const ext_ctx_repr,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN managed_ctx_t context(
            node_id_type const& SIXTRL_RESTRICT_REF node_id ) const;

        SIXTRL_HOST_FN managed_ctx_t context(
            node_id_type const& SIXTRL_RESTRICT_REF node_id,
            guard_type const& SIXTRL_RESTRICT_REF lock ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */



        protected:

        using node_id_create_dev_handle_fn_t = ::NS(BaseNodeId)* (*)(
            ::NS(cuda_device_handle_type) const );

        using node_id_dev_handle_fn_t = ::NS(cuda_device_handle_type) (*)(
            const ::NS(BaseNodeId) *const SIXTRL_RESTRICT );

        using node_id_set_dev_handle_fn_t = ::NS(status_t) (*)(
            ::NS(BaseNodeId)* SIXTRL_RESTRICT,
            ::NS(cuda_device_handle_type) const );

        using ctx_get_current_fn_t = ::NS(cuda_ctx_int_repr_type) (*)();
        using ctx_set_current_fn_t = ::NS(status_t) (*)(
            ::NS(cuda_ctx_int_repr_type) const,
            ::NS(cuda_ctx_int_repr_type)* SIXTRL_RESTRICT );

        using ctx_create_fn_t = ::NS(BaseContext)* (*)(
            const ::NS(ThreadId) *const SIXTRL_RESTRICT );

        using ctx_init_fn_t = ::NS(status_t) (*)(
            ::NS(BaseContext)* SIXTRL_RESTRICT,
            const ::NS(BaseNodeId) *const SIXTRL_RESTRICT,
            ::NS(cuda_ctx_create_flags_t) const,
            const ::NS(ThreadUniqueLock) *const SIXTRL_RESTRICT );

        using ctx_init_primary_fn_t = ::NS(status_t) (*)(
            ::NS(BaseContext)* SIXTRL_RESTRICT,
            const ::NS(BaseNodeId) *const SIXTRL_RESTRICT,
            ::NS(cuda_ctx_create_flags_t) const,
            const ::NS(ThreadUniqueLock) *const SIXTRL_RESTRICT );

        using ctx_init_ext_shared_fn_t = ::NS(status_t) (*)(
            ::NS(BaseContext)* SIXTRL_RESTRICT,
            ::NS(cuda_ctx_int_repr_type) const,
            const ::NS(ThreadUniqueLock) *const SIXTRL_RESTRICT );

        using ctx_delete_fn_t = void (*)( ::NS(BaseContext)* );

        using ctx_get_node_id_fn_t = ::NS(BaseNodeId)* (*)(
            const ::NS(BaseContext) *const SIXTRL_RESTRICT,
            const ::NS(ThreadUniqueLock) *const SIXTRL_RESTRICT );

        SIXTRL_HOST_FN status_t do_assign_symbols() override;
        SIXTRL_HOST_FN status_t do_make_ready() override;

        private:

        std::unordered_map< ::CUdevice, managed_ctx_t > m_context_store;

        node_id_create_dev_handle_fn_t
            m_node_id_create_from_dev_handle_fn = nullptr;
        node_id_dev_handle_fn_t     m_node_id_dev_handle_fn     = nullptr;
        node_id_set_dev_handle_fn_t m_node_id_set_dev_handle_fn = nullptr;

        ctx_get_current_fn_t        m_ctx_get_current_fn        = nullptr;
        ctx_set_current_fn_t        m_ctx_set_current_fn        = nullptr;
        ctx_create_fn_t             m_ctx_create_fn             = nullptr;
        ctx_delete_fn_t             m_ctx_delete_fn             = nullptr;
        ctx_init_fn_t               m_ctx_init_fn               = nullptr;
        ctx_init_primary_fn_t       m_ctx_init_primary_fn       = nullptr;
        ctx_init_ext_shared_fn_t    m_ctx_init_ext_shared_fn    = nullptr;
        ctx_get_node_id_fn_t        m_ctx_get_node_id_fn        = nullptr;

        bool m_inherit_ctx_during_init = false;
    };

    SIXTRL_EXPORT_API SIXTRL_HOST_FN CudaBackend const* CudaBackend_get(
        const SIXTRL_CXX_NAMESPACE::BaseBackend *const
            SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT;

    SIXTRL_EXPORT_API SIXTRL_HOST_FN CudaBackend* CudaBackend_get(
        SIXTRL_CXX_NAMESPACE::BaseBackend*
            SIXTRL_RESTRICT ptr_base ) SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

    SIXTRL_EXPORT_API SIXTRL_HOST_FN CudaBackend* Cuda_init_backend();

    SIXTRL_EXPORT_API SIXTRL_HOST_FN
    CudaBackend* Cuda_init_backend_with_config_file(
        CudaBackend::fs_string_type const& SIXTRL_RESTRICT_REF path_to_conf );

    SIXTRL_EXPORT_API SIXTRL_HOST_FN CudaBackend*
    Cuda_init_backend_with_config_string(
        CudaBackend::string_type const& SIXTRL_RESTRICT_REF config_string );

    SIXTRL_EXPORT_API SIXTRL_HOST_FN void Cuda_shutdown_backend();

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */
#endif /* SIXTRACKL_ENABLE_BACKEND_CUDA */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                   Exported Plugin C-API :: Types                !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

#if defined( SIXTRACKL_ENABLE_BACKEND_CUDA )
#if defined( __cplusplus ) && !defined( _GPUCODE )

typedef SIXTRL_CXX_NAMESPACE::CudaBackend NS(CudaBackend);

#elif !defined( _GPUCODE ) /* C, Host */

struct NS(CudaBackend);

#endif /* C++ / C, Host */
#else /* NOT SIXTRACKL_ENABLE_BACKEND_CUDA */

typedef void NS(CudaBackend);

#endif /* SIXTRACKL_ENABLE_BACKEND_CUDA */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                Exported Plugin C-API :: Functions               !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

SIXTRL_EXPORT_API SIXTRL_HOST_FN
NS(CudaBackend)* NS(Cuda_init_backend)( void );

SIXTRL_EXPORT_API SIXTRL_HOST_FN
NS(CudaBackend)* NS(Cuda_init_backend_with_config_file)(
    char const* SIXTRL_RESTRICT path_to_conf );

SIXTRL_EXPORT_API SIXTRL_HOST_FN
NS(CudaBackend)* NS(Cuda_init_backend_with_config_string)(
    char const* SIXTRL_RESTRICT config_string );

SIXTRL_EXPORT_API SIXTRL_HOST_FN void
NS(Cuda_shutdown_backend)( void );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BACKENDS_CUDA_BACKEND_BACKEND_H__ */

