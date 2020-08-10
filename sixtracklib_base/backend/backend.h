#ifndef SIXTRACKLIB_BASE_BACKEND_BACKEND_H__
#define SIXTRACKLIB_BASE_BACKEND_BACKEND_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/backend/definitions.h"
    #include "sixtracklib_base/backend/backend_obj.h"
    #include "sixtracklib_base/backend/dlib_loader.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <istream>
        #include <memory>
        #include <ostream>
        #include <sstream>
        #include <string>
        #include <unordered_map>
    #endif /* C++ */

    #if defined( __unix__ )
        #if defined( __GNUC__ ) && !defined( _GNU_SOURCE )
            #define _GNU_SOURCE
        #endif /* Gcc */
        #include <dlfcn.h>
    #endif /* defined( __unix__ ) */

    #if defined( __unix__ ) || \
        ( defined( __APPLE__ ) && defined( __MACH__ ) )
        #include <unistd.h>
    #endif /* *nix / POSIX / Apple MacOS X or iOS */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if  defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class BaseNodeBackend;

    class SIXTRL_BASE_EXPORT_API BaseBackend :
        public SIXTRL_CXX_NAMESPACE::BaseBackendObj
    {
        public:

        using size_type = SIXTRL_CXX_NAMESPACE::size_t;

        using string_type = std::string;
        using string_char_t = string_type::value_type;
        using sstream_t = std::ostringstream;

        using fs_string_type = std::string;
        using fs_string_char_t = fs_string_type::value_type;
        using fs_sstream_t = std::ostringstream;

        using init_backend_fn_t = void (*)( void );
        using shutdown_backend_fn_t = void (*)( void );

        using dlib_loader_t = std::shared_ptr<
            SIXTRL_CXX_NAMESPACE::BaseDynLibLoader >;

        using run_dlib_init_finish_fn_flags_t = uint16_t;

        static constexpr run_dlib_init_finish_fn_flags_t
            RUN_BACKEND_INIT_FN_AUTO =
                run_dlib_init_finish_fn_flags_t{ 0x00 };

        static constexpr run_dlib_init_finish_fn_flags_t
            RUN_BACKEND_INIT_FN_EXPLICITLY =
                run_dlib_init_finish_fn_flags_t{ 0x01 };

        static constexpr run_dlib_init_finish_fn_flags_t
            RUN_BACKEND_SHUTDOWN_FN_AUTO =
                run_dlib_init_finish_fn_flags_t{ 0x00 };

        static constexpr run_dlib_init_finish_fn_flags_t
            RUN_BACKEND_SHUTDOWN_FN_EXPLICITLY =
                run_dlib_init_finish_fn_flags_t{ 0x02 };

        using be_symbol_id_t = uint64_t;

        static constexpr class_variant_t
            BACKEND_VARIANT_DEFAULT = class_variant_t{ 0x00 };

        static constexpr class_variant_t
            BACKEND_VARIANT_HAS_NODES = class_variant_t{ 0x01 };

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        static constexpr be_symbol_id_t SYMBOL_ID_INIT_BACKEND =
            be_symbol_id_t{ 0 };

        static constexpr be_symbol_id_t SYMBOL_ID_SHUTDOWN_BACKEND =
            be_symbol_id_t{ 1 };

        static constexpr be_symbol_id_t SYMBOL_ID_ILLEGAL =
            be_symbol_id_t{ 0x7fffffffffffffff };

        /* ----------------------------------------------------------------- */

        SIXTRL_STATIC SIXTRL_HOST_FN bool
        IS_PREDEFINED_BACKEND( backend_id_t const backend_id ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_HOST_FN bool
        IS_PREDEFINED_BACKEND( string_type const& SIXTRL_RESTRICT_REF
            backend_str ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_HOST_FN backend_id_t
        PREDEFINED_BACKEND_STR_TO_ID( string_type const&
            SIXTRL_RESTRICT_REF backend_str ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_HOST_FN string_type
        PREDEFINED_BACKEND_ID_TO_STR( backend_id_t const backend_id );

        SIXTRL_STATIC SIXTRL_HOST_FN size_type
        REQUIRED_STR_BUFFER_CAPACITY_FOR_PREDEFINED_BACKEND(
            backend_id_t const backend_id );

        SIXTRL_STATIC SIXTRL_HOST_FN status_t
        PREDEFINED_BACKEND_ID_TO_STR(
            string_char_t* SIXTRL_RESTRICT out_buffer,
            size_type const out_buffer_capacity, backend_id_t const backend_id
        ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual ~BaseBackend() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN BaseNodeBackend const*
        as_node_backend() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN BaseNodeBackend* as_node_backend() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool has_nodes() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_dynamic_library_loader() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool has_dynamic_library_handle() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN dlib_loader_t& dynamic_library_loader() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN BaseDynLibLoader const*
        ptr_base_dynamic_library_loader() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t update_undefined_backend_id(
            backend_id_t const backend_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t update_undefined_backend_id_detailed(
            backend_id_t const backend_id,
            string_type const& backend_str = string_type{} );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool is_available() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_ready() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN run_dlib_init_finish_fn_flags_t
        run_init_backend_fn_mode() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN run_dlib_init_finish_fn_flags_t
        run_shutdown_backend_fn_mode() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool run_init_backend_fn_auto() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        run_init_backend_fn_explicitly() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        run_shutdown_backend_fn_auto() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        run_shutdown_backend_fn_explicitly() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_backend_string() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_type const&
        backend_string_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_t const*
        backend_string() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN string_type config_key() const;

        SIXTRL_HOST_FN status_t configure(
            string_type const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN status_t configure_from_file(
            fs_string_type const& SIXTRL_RESTRICT_REF path_to_config_file );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_symbol_name(
            be_symbol_id_t const symbold_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_type const& symbol_name_str(
            be_symbol_id_t const symbol_id ) const;

        SIXTRL_HOST_FN string_char_t const* symbol_name(
            be_symbol_id_t const symbol_id ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t make_available();
        SIXTRL_HOST_FN status_t make_ready();



        protected:

        using symid_to_symbol_name_map_t = std::unordered_map<
            be_symbol_id_t, string_type >;

        using symbol_name_flags_t = uint16_t;

        static constexpr symbol_name_flags_t
            SYMBOL_NAME_DO_NOTHING = symbol_name_flags_t{ 0 };

        static constexpr symbol_name_flags_t
            SYMBOL_NAME_ADD_C99_NAMESPACE_STR = symbol_name_flags_t{ 0x01 };

        static constexpr symbol_name_flags_t
            SYMBOL_NAME_ADD_CXX_NAMESPACE_STR = symbol_name_flags_t{ 0x02 };



        SIXTRL_HOST_FN explicit BaseBackend( backend_id_t const bend_id,
            string_type const& SIXTRL_RESTRICT_REF bend_str = string_type{} );

        SIXTRL_HOST_FN BaseBackend( BaseBackend const& ) = delete;
        SIXTRL_HOST_FN BaseBackend( BaseBackend&& ) = default;

        SIXTRL_HOST_FN BaseBackend& operator=( BaseBackend const& ) = delete;
        SIXTRL_HOST_FN BaseBackend& operator=( BaseBackend&& ) = default;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN BaseDynLibLoader*
        ptr_base_dynamic_library_loader() SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t remove_symbol(
            be_symbol_id_t const symbol_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_symbol_name( be_symbol_id_t const symbol_id,
            string_type const& SIXTRL_RESTRICT_REF symbol_name,
            symbol_name_flags_t const flags = SYMBOL_NAME_DO_NOTHING );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN virtual status_t do_configure(
            std::istream& SIXTRL_RESTRICT_REF config_stream,
            std::string const& SIXTRL_RESTRICT_REF table_key );

        SIXTRL_HOST_FN virtual status_t do_make_available();
        SIXTRL_HOST_FN virtual status_t do_assign_symbols();
        SIXTRL_HOST_FN virtual status_t do_reset_symbols();
        SIXTRL_HOST_FN virtual status_t do_make_ready();

        SIXTRL_HOST_FN status_t set_backend_string(
            string_type const& SIXTRL_RESTRICT_REF backend_str );

        SIXTRL_HOST_FN bool check_is_base_backend_ready() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void update_is_available_flag(
            bool const is_available ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void update_is_ready_flag(
            bool const is_ready ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void update_run_init_finish_fn_mode(
            run_dlib_init_finish_fn_flags_t const
                run_init_finish_mode ) SIXTRL_NOEXCEPT;

        private:
        symid_to_symbol_name_map_t m_symbol_id_to_symbol_name_map;
        string_type m_backend_str;
        dlib_loader_t m_dlib_loader = dlib_loader_t{ nullptr };

        protected:
        init_backend_fn_t      m_init_backend_fn     = nullptr;
        shutdown_backend_fn_t  m_shutdown_backend_fn = nullptr;

        private:
        run_dlib_init_finish_fn_flags_t m_run_init_finish_fn_mode =
            RUN_BACKEND_INIT_FN_EXPLICITLY |
            RUN_BACKEND_SHUTDOWN_FN_EXPLICITLY;

        bool m_is_available = false;
        bool m_is_ready = false;
    };
}

extern "C"
{
    typedef SIXTRL_CXX_NAMESPACE::BaseBackend NS(BaseBackend);
}

#else /* C++, Host */

struct NS(BaseBackend);

#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_BACKEND_BACKEND_H__ */
