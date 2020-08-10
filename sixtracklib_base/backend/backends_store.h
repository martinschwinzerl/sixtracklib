#ifndef SIXTRACKLIB_BASE_BACKEND_BACKEND_STORE_H__
#define SIXTRACKLIB_BASE_BACKEND_BACKEND_STORE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/backend/definitions.h"
    #include "sixtracklib_base/backend/backend.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <memory>
        #include <string>
        #include <unordered_map>
        #include <vector>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class SIXTRL_BASE_EXPORT_API BackendsStore
    {
        public:

        using base_backend_t        = SIXTRL_CXX_NAMESPACE::BaseBackend;
        using size_type             = SIXTRL_CXX_NAMESPACE::size_t;
        using status_t              = SIXTRL_CXX_NAMESPACE::status_t;
        using ptr_base_backend_t    = std::unique_ptr< base_backend_t >;
        using backend_id_t          = base_backend_t::backend_id_t;
        using string_type           = base_backend_t::string_type;
        using string_char_t         = base_backend_t::string_char_t;
        using fs_string_type        = base_backend_t::fs_string_type;
        using fs_string_char_t      = base_backend_t::fs_string_char_t;
        using fs_sstream_t          = base_backend_t::fs_sstream_t;
        using config_source_t       = uint16_t;

        static SIXTRL_HOST_FN status_t INIT_PREDEFINED_BACKENDS(
            BackendsStore& SIXTRL_RESTRICT_REF backend_store );

        static constexpr backend_id_t MIN_USERDEFINED_BACKEND_ID =
            backend_id_t{ 256 };

        static constexpr backend_id_t MAX_USERDEFINED_BACKEND_ID =
            backend_id_t{ 0x7fffffff };

        static constexpr config_source_t CONFIG_NONE   = config_source_t{ 0 };
        static constexpr config_source_t CONFIG_STRING = config_source_t{ 1 };
        static constexpr config_source_t CONFIG_FILE   = config_source_t{ 2 };

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN BackendsStore();

        BackendsStore( BackendsStore const& ) = delete;
        BackendsStore( BackendsStore&& ) = delete;

        BackendsStore& operator=( BackendsStore const& ) = delete;
        BackendsStore& operator=( BackendsStore&& ) = delete;

        SIXTRL_BASE_EXPORT_API virtual ~BackendsStore() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_backend(
            backend_id_t const backend_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_backend_by_str(
            string_type const& SIXTRL_RESTRICT_REF
                backend_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_backend_string(
            backend_id_t const backend_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_type const& backend_string_str(
            backend_id_t const backend_id ) const;

        SIXTRL_HOST_FN string_char_t const* backend_string(
            backend_id_t const backend_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN backend_id_t backend_id_by_str(
            string_type const& SIXTRL_RESTRICT_REF
                backend_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_backends() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN backend_id_t backend_id_by_idx(
            size_type const idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN backend_id_t const*
        backend_ids_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN backend_id_t const*
        backend_ids_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN base_backend_t const*
        backend( backend_id_t const backend_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN base_backend_t*
        backend( backend_id_t const backend_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN base_backend_t const* backend_by_str( string_type const&
            SIXTRL_RESTRICT_REF backend_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN base_backend_t* backend_by_str(
            string_type const& SIXTRL_RESTRICT_REF backend_str ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN base_backend_t const*
        backend_by_idx( size_type const idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN base_backend_t*
        backend_by_idx( size_type const idx ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_backends_with_nodes() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN backend_id_t const*
        backends_with_nodes_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN backend_id_t const*
        backends_with_nodes_end() const SIXTRL_NOEXCEPT;

        template< typename BackendStrIter >
        SIXTRL_HOST_FN size_type backend_string_for_backends_with_nodes(
            BackendStrIter backend_str_begin,
            BackendStrIter backend_str_end ) const
        {
            size_type num_backend_strings = size_type{ 0 };

            auto it = backend_str_begin;
            auto backend_id_it = this->m_backends_with_nodes.begin();
            auto backend_id_end = this->m_backends_with_nodes.end();

            while( ( it != backend_str_end ) && ( backend_id_it != backend_id_end ) )
            {
                auto backend = this->backend( *backend_id_it );
                if( backend == nullptr ) continue;

                it->assign( backend->backend_string_str().begin(),
                            backend->backend_string_str().end() );
                ++it;
                ++num_backend_strings;
                ++backend_id_it;
            }

            while( it != backend_str_end )
            {
                it->clear();
                ++it;
            }

            return num_backend_strings;
        }

        SIXTRL_HOST_FN size_type backend_string_for_backends_with_nodes(
            string_type* backend_str_begin,
            size_type const max_num_backend_str ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN string_type const&
        node_id_format_backendid_regex_str();

        SIXTRL_HOST_FN string_type const&
        node_id_format_backendstr_regex_str();

        SIXTRL_HOST_FN string_type
        node_id_format_backendid_regex_str_for_backend(
            backend_id_t const backend_id );

        SIXTRL_HOST_FN string_type
        node_id_format_backendstr_regex_str_for_backend(
            backend_id_t const backend_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t add_backend(
            std::unique_ptr< base_backend_t > backend_to_store );

        SIXTRL_HOST_FN status_t remove_backend( backend_id_t const backend_id );
        SIXTRL_HOST_FN status_t remove_backend_by_str(
            string_type const& SIXTRL_RESTRICT_REF backend_str );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_config_data() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool has_config_string() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool has_path_to_config_file() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN config_source_t config_source() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_type const& config_string_str() const;
        SIXTRL_HOST_FN string_char_t const*
        config_string() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t
        set_config_string( string_type const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN fs_string_type const&
        path_to_config_file_str() const;

        SIXTRL_HOST_FN fs_string_char_t const*
        path_to_config_file() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_path_to_config_file(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_config_file );

        SIXTRL_HOST_FN status_t set_config_data(
            string_type const& SIXTRL_RESTRICT_REF config_data,
            config_source_t const source );

        SIXTRL_HOST_FN void reset_config_data();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t init_backend( backend_id_t const backend_id );

        SIXTRL_HOST_FN status_t init_backend_with_config(
            backend_id_t const backend_id,
            string_type const& SIXTRL_RESTRICT_REF config_string );

        SIXTRL_HOST_FN status_t init_backend_with_config_file(
            backend_id_t const backend_id,
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_conf_file );

        protected:

        using backend_id_list_t = std::vector< backend_id_t >;
        using id_to_backend_map_t = std::unordered_map< backend_id_t,
            std::unique_ptr< base_backend_t > >;

        using backend_str_to_backend_id_map_t =
            std::unordered_map< string_type, backend_id_t >;

        SIXTRL_HOST_FN virtual status_t do_add_backend(
            std::unique_ptr< base_backend_t >&& backend_to_store );

        SIXTRL_HOST_FN virtual status_t do_remove_backend(
            backend_id_t const backend_id );

        SIXTRL_HOST_FN virtual status_t do_update_node_id_format_regex_strs();
        SIXTRL_HOST_FN virtual void do_clear_node_id_format_regex_strs();

        private:

        SIXTRL_HOST_FN status_t do_add_backend_base_impl(
            std::unique_ptr< base_backend_t >&& backend_to_store );

        SIXTRL_HOST_FN status_t do_remove_backend_base_impl(
            backend_id_t const backend_id ) SIXTRL_NOEXCEPT;

        id_to_backend_map_t m_id_to_backends;
        backend_str_to_backend_id_map_t m_backend_str_to_backend_id;
        backend_id_list_t m_stored_backend_ids;
        backend_id_list_t m_backends_with_nodes;

        string_type       m_node_id_format_backendid_regex_str;
        string_type       m_node_id_format_backendstr_regex_str;
        string_type       m_config_data;

        backend_id_t      m_next_userdefined_backend_id;
        config_source_t   m_config_source;
    };

    SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN
    BackendsStore const& BackendsStore_const_global();

    SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN BackendsStore& BackendsStore_global();

    SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN
    BackendsStore const* BackendsStore_ptr_const_global();

    SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN
    BackendsStore* BackendsStore_ptr_global();

} /* ns: SIXTRL_CXX_NAMESPACE */

extern "C" { typedef SIXTRL_CXX_NAMESPACE::BackendsStore NS(BackendsStore); }

#else /* C++, Host */

struct NS(BackendsStore);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN
NS(BackendsStore) const* NS(BackendsStore_ptr_const_global)( void );

SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN
NS(BackendsStore)* NS(BackendsStore_ptr_global)( void );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_BACKEND_BACKEND_STORE_H__ */
