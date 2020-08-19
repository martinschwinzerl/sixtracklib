#ifndef SIXTRACKLIB_BASE_CONTROL_CONTEXT_H__
#define SIXTRACKLIB_BASE_CONTROL_CONTEXT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/control/definitions.h"
    #include "sixtracklib_base/backend/backend.h"
    #include "sixtracklib_base/backend/backend_obj.h"
    #include "sixtracklib_base/internal/thread_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <atomic>
        #include <memory>
        #include <string>
        #include <thread>
        #include <type_traits>
        #include <vector>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class BaseMTShareableContext;

    class SIXTRL_BASE_EXPORT_API BaseContext :
        public SIXTRL_CXX_NAMESPACE::BaseBackendObj
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::size_t size_type;
        typedef void (*context_delete_fn_type)( BaseContext* SIXTRL_RESTRICT );

        static constexpr class_variant_t CTX_VARIANT_DEFAULT =
            class_variant_t{ 0x01 };

        static constexpr class_variant_t CTX_VARIANT_MT_SHAREABLE =
            class_variant_t{ 0x01 };

        typedef SIXTRL_CXX_NAMESPACE::BaseBackend base_backend_t;

        SIXTRL_HOST_FN virtual ~BaseContext();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool is_mt_shareable_context() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN BaseMTShareableContext const*
        as_mt_shareable_context() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN BaseMTShareableContext*
        as_mt_shareable_context() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN base_backend_t& base_backend() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN base_backend_t const&
            base_backend() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool is_active() const;

        protected:

        SIXTRL_HOST_FN explicit BaseContext(
            base_backend_t& SIXTRL_RESTRICT backend );

        SIXTRL_HOST_FN explicit BaseContext(
            backend_id_t const backend_id );

        SIXTRL_HOST_FN BaseContext( BaseContext const& );
        SIXTRL_HOST_FN BaseContext( BaseContext&& );

        SIXTRL_HOST_FN BaseContext& operator=( BaseContext const& );
        SIXTRL_HOST_FN BaseContext& operator=( BaseContext&& );

        SIXTRL_HOST_FN void update_is_active( bool const is_active_flag );

        private:

        std::atomic< bool > m_is_active;
        base_backend_t* m_ptr_base_backend;
    };

    /* ===================================================================== */

    class SIXTRL_BASE_EXPORT_API BaseMTShareableContext :
        public SIXTRL_CXX_NAMESPACE::BaseContext
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::ThreadId thread_id_type;
        typedef base_backend_t::lockable_type lockable_type;
        typedef base_backend_t::guard_type guard_type;
        typedef base_backend_t::size_type size_type;

        SIXTRL_HOST_FN virtual ~BaseMTShareableContext() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN thread_id_type owned_by() const;
        SIXTRL_HOST_FN thread_id_type const& owned_by(
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type num_attached_threads() const;
        SIXTRL_HOST_FN size_type num_attached_threads(
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool is_attached(
            thread_id_type const& SIXTRL_RESTRICT_REF tid ) const;

        SIXTRL_HOST_FN bool is_attached(
            thread_id_type const& SIXTRL_RESTRICT_REF tid,
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN thread_id_type const* attached_thread_ids_begin(
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN thread_id_type const* attached_thread_ids_end(
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_type attach_thread(
            thread_id_type const& SIXTRL_RESTRICT_REF tid );

        SIXTRL_HOST_FN status_type attach_thread(
            thread_id_type const& SIXTRL_RESTRICT_REF tid,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_type detach_thread(
            thread_id_type const& SIXTRL_RESTRICT_REF tid );

        SIXTRL_HOST_FN status_type detach_thread(
            thread_id_type const& SIXTRL_RESTRICT_REF tid,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        protected:

        SIXTRL_HOST_FN explicit BaseMTShareableContext(
            base_backend_t& SIXTRL_RESTRICT backend,
            thread_id_type const& SIXTRL_RESTRICT_REF tid = thread_id_type{} );

        SIXTRL_HOST_FN explicit BaseMTShareableContext(
            backend_id_t const backend_id,
            thread_id_type const& SIXTRL_RESTRICT_REF tid = thread_id_type{} );

        SIXTRL_HOST_FN BaseMTShareableContext(
            BaseMTShareableContext const& ) = delete;

        SIXTRL_HOST_FN BaseMTShareableContext(
            BaseMTShareableContext&& ) = delete;

        SIXTRL_HOST_FN BaseMTShareableContext&
        operator=( BaseMTShareableContext const& ) = delete;

        SIXTRL_HOST_FN BaseMTShareableContext&
        operator=( BaseMTShareableContext&& ) = delete;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual status_t do_attach_thread(
            thread_id_type const& SIXTRL_RESTRICT_REF tid,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN virtual status_t do_detach_thread(
            thread_id_type const& SIXTRL_RESTRICT_REF tid,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        private:

        SIXTRL_HOST_FN status_t do_attach_thread_mt_impl(
            thread_id_type const& SIXTRL_RESTRICT_REF tid,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN status_t do_detach_thread_mt_impl(
            thread_id_type const& SIXTRL_RESTRICT_REF tid,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        std::vector< thread_id_type > m_attached_threads;
        thread_id_type m_owner_thread_id;
    };
} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                   Exported Plugin C-API :: Types                !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )

typedef SIXTRL_CXX_NAMESPACE::BaseContext NS(BaseContext);
typedef SIXTRL_CXX_NAMESPACE::BaseMTShareableContext NS(BaseMTShareableContext);

#elif !defined( _GPUCODE )  /* C, Host */

struct NS(BaseContext);
struct NS(BaseMTShareableContext);

#endif /* C++ / C & Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                Exported Plugin C-API :: Functions               !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN void NS(Context_delete)(
    NS(BaseContext)* SIXTRL_RESTRICT ctx ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_CONTROL_CONTEXT_H__ */
