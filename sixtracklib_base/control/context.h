#ifndef SIXTRACKLIB_BASE_CONTROL_CONTEXT_H__
#define SIXTRACKLIB_BASE_CONTROL_CONTEXT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/control/definitions.h"
    #include "sixtracklib_base/backend/backend.h"
    #include "sixtracklib_base/backend/backend_obj.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
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
    class BaseMTSharableContext;

    class SIXTRL_BASE_EXPORT_API BaseContext :
        public SIXTRL_CXX_NAMESPACE::BaseBackendObj
    {
        public:

        static constexpr class_variant_t CTX_VARIANT_DEFAULT =
            class_variant_t{ 0x01 };

        static constexpr class_variant_t CTX_VARIANT_MT_SHAREABLE =
            class_variant_t{ 0x01 };

        typedef SIXTRL_CXX_NAMESPACE::BaseBackend base_backend_t;

        SIXTRL_HOST_FN virtual ~BaseContext();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool is_mt_shareable_context() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN BaseMTSharableContext const*
        as_mt_shareable_context() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN BaseMTSharableContext*
        as_mt_shareable_context() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN base_backend_t& base_backend() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN base_backend_t const&
            base_backend() const SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN explicit BaseContext(
            base_backend_t& SIXTRL_RESTRICT backend );

        SIXTRL_HOST_FN explicit BaseContext(
            backend_id_t const backend_id );

        SIXTRL_HOST_FN BaseContext( BaseContext const& ) = default;
        SIXTRL_HOST_FN BaseContext( BaseContext&& ) = default;

        SIXTRL_HOST_FN BaseContext& operator=( BaseContext const& ) = default;
        SIXTRL_HOST_FN BaseContext& operator=( BaseContext&& ) = default;

        private:

        base_backend_t* m_ptr_base_backend;

        protected:
        bool m_is_active;
    };

    /* ===================================================================== */

    class SIXTRL_BASE_EXPORT_API BaseMTSharableContext :
        public SIXTRL_CXX_NAMESPACE::BaseContext
    {
        public:

        typedef base_backend_t::thread_id_type thread_id_type;
        typedef base_backend_t::lockable_type lockable_type;
        typedef base_backend_t::guard_type guard_type;
        typedef base_backend_t::size_type size_type;

        SIXTRL_HOST_FN virtual ~BaseMTSharableContext();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type num_associated_threads() const;
        SIXTRL_HOST_FN size_type num_associated_threads(
            guard_type const& SIXTRL_RESTRICT_REF guard ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

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





        protected:

        SIXTRL_HOST_FN explicit BaseMTSharableContext(
            base_backend_t& SIXTRL_RESTRICT backend );

        SIXTRL_HOST_FN explicit BaseMTSharableContext(
            backend_id_t const backend_id );

        SIXTRL_HOST_FN BaseMTSharableContext(
            BaseMTSharableContext const& ) = default;

        SIXTRL_HOST_FN BaseMTSharableContext(
            BaseMTSharableContext&& ) = default;

        SIXTRL_HOST_FN BaseMTSharableContext&
        operator=( BaseMTSharableContext const& ) = default;

        SIXTRL_HOST_FN BaseMTSharableContext&
        operator=( BaseMTSharableContext&& ) = default;



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



        private:

        std::vector< thread_id_type > m_associated_threads;
    };
};

extern "C" { typedef SIXTRL_CXX_NAMESPACE::BaseContext NS(BaseContext); }

#elif !defined( _GPUCODE ) /* C, Host */

struct NS(BaseContext);

#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_CONTROL_CONTEXT_H__ */
