#ifndef SIXTRACKLIB_BASE_ARCHITECTURE_NODE_ARCHITECTURE_H__
#define SIXTRACKLIB_BASE_ARCHITECTURE_NODE_ARCHITECTURE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/architecture/definitions.h"
    #include "sixtracklib/base/architecture/architecture.h"
    #include "sixtracklib/base/node/node_id.h"
    #include "sixtracklib/base/node/node_info.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <string>
        #include <ostream>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if  defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class SIXTRL_BASE_EXPORT_API NodeArchitecture :
        public SIXTRL_CXX_NAMESPACE::Architecture
    {
        public:

        using node_info_t =

        protected:

        static constexpr class_variant_flags_t ARCHITECTURE_VARIANT_DEFAULT =
            class_variant_flags_t{ 0 };

        static constexpr class_variant_flags_t ARCHITECTURE_VARIANT_NODES =
            class_variant_flags_t{ 1 };

        public:

        /* ----------------------------------------------------------------- */

        SIXTRL_STATIC SIXTRL_HOST_FN bool IS_PREDEFINED_ARCHITECTURE(
            arch_id_t const arch_id ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_HOST_FN bool IS_PREDEFINED_ARCHITECTURE(
            std::string const& SIXTRL_RESTRICT_REF arch_str ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_HOST_FN arch_id_t
        PREDEFINED_ARCHITECTURE_STR_TO_ID( std::string const&
            SIXTRL_RESTRICT_REF arch_str ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_HOST_FN std::string
        PREDEFINED_ARCHITECTURE_ID_TO_STR( arch_id_t const arch_id );

        SIXTRL_STATIC SIXTRL_HOST_FN size_type
        REQUIRED_STR_BUFFER_CAPACITY_FOR_PREDEFINED_ARCHITECTURE(
            arch_id_t const arch_id );

        SIXTRL_STATIC SIXTRL_HOST_FN status_t PREDEFINED_ARCHITECTURE_ID_TO_STR(
            char* SIXTRL_RESTRICT out_buffer,
            size_type const out_buffer_capacity, arch_id_t const arch_id
        ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN explicit Architecture(
        arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF arch_name_str = std::string{},
        state_flags_t const state_flags = SIXTRL_CXX_NAMESPACE::ARCH_STATE_NONE,
        init_arch_fn_t init_arch_fn = nullptr,
        shutdown_arch_fn_t shutdown_arch_fn = nullptr );

        SIXTRL_HOST_FN Architecture( Architecture const& ) = default;
        SIXTRL_HOST_FN Architecture( Architecture&& ) = default;

        SIXTRL_HOST_FN Architecture& operator=( Architecture const& ) = default;
        SIXTRL_HOST_FN Architecture& operator=( Architecture&& ) = default;

        SIXTRL_HOST_FN virtual ~Architecture();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t update_undefined_arch_id(
            arch_id_t const arch_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_plugin_handle() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN plugin_handle_t plugin_handle() SIXTRL_NOEXCEPT;

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE state_flags_t
        state_flags() const SIXTRL_NOEXCEPT { return this->m_state_flags; }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE status_t
        set_state_flags( state_flags_t const state_flags ) SIXTRL_NOEXCEPT {
            this->m_state_flags = state_flags;
            return SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS;
        }

        SIXTRL_HOST_FN bool is_enabled() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_activated() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_available() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_shutdown() const SIXTRL_NOEXCEPT;

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE
        bool has_arch_string() const SIXTRL_NOEXCEPT {
            return !this->m_arch_str.empty();
        }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE std::string const&
        arch_string_str() const SIXTRL_NOEXCEPT {
            return this->m_arch_str;
        }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE char const*
        arch_string() const SIXTRL_NOEXCEPT {
            return this->m_arch_str.c_str();
        }

        SIXTRL_HOST_FN status_t initialize();
        SIXTRL_HOST_FN status_t shutdown();

        /* ----------------------------------------------------------------- */

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE bool
            allows_nodes() const SIXTRL_NOEXCEPT {
                return this->is_class_variant( ARCHITECTURE_VARIANT_NODES ); }

        protected:

        SIXTRL_HOST_FN status_t set_init_arch_fn(
            init_arch_fn_t init_arch_fn );

        SIXTRL_HOST_FN status_t set_shutdown_arch_fn(
            shutdown_arch_fn_t shutdown_arch_fn );

        SIXTRL_HOST_FN status_t set_arch_string(
            std::string const& SIXTRL_RESTRICT_REF arch_str ) {
            this->m_arch_str = arch_str;
            return SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS;
        }

        private:

        std::string         m_arch_str;
        init_arch_fn_t      m_init_fn;
        shutdown_arch_fn_t  m_shutdown_fn;
        plugin_handle_t     m_plugin_handle;
        state_flags_t       m_state_flags;
    };
}

extern "C" { typedef SIXTRL_CXX_NAMESPACE::Architecture NS(Architecture); }

#else /* C++, Host */

struct NS(Architecture);

#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_ARCHITECTURE_NODE_ARCHITECTURE_H__ */
