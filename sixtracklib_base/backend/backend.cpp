#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/definitions.h"
    #include "sixtracklib_base/backend/dlib.h"
    #include "sixtracklib_base/backend/backend.h"
    #include "sixtracklib_base/backend/dlib_loader.h"
    #include "sixtracklib_base/backend/node_backend.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUODE ) && defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <cstring>
    #include <fstream>
    #include <sstream>

    #include <toml.hpp>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using this_t = st::BaseBackend;
        using st_backend_id_t = this_t::backend_id_t;
        using st_status_t  = this_t::status_t;
        using st_size_t = this_t::size_type;
        using st_class_variant_t = this_t::class_variant_t;
        using fs_string_t = this_t::fs_string_type;
        using fs_str_char_t = this_t::fs_string_char_t;
        using string_t = this_t::string_type;
        using str_char_t = this_t::string_char_t;
        using sstream_t = this_t::sstream_t;
        using in_sstream_t = std::istringstream;
    }

    constexpr st_class_variant_t this_t::BACKEND_VARIANT_DEFAULT;
    constexpr st_class_variant_t this_t::BACKEND_VARIANT_HAS_NODES;

    constexpr this_t::run_dlib_init_finish_fn_flags_t
              this_t::RUN_BACKEND_INIT_FN_AUTO;

    constexpr this_t::run_dlib_init_finish_fn_flags_t
              this_t::RUN_BACKEND_INIT_FN_EXPLICITLY;

    constexpr this_t::run_dlib_init_finish_fn_flags_t
              this_t::RUN_BACKEND_SHUTDOWN_FN_AUTO;

    constexpr this_t::run_dlib_init_finish_fn_flags_t
              this_t::RUN_BACKEND_SHUTDOWN_FN_EXPLICITLY;

    constexpr this_t::be_symbol_id_t this_t::SYMBOL_ID_INIT_BACKEND;
    constexpr this_t::be_symbol_id_t this_t::SYMBOL_ID_SHUTDOWN_BACKEND;
    constexpr this_t::be_symbol_id_t this_t::SYMBOL_ID_ILLEGAL;


    bool this_t::IS_PREDEFINED_BACKEND(
        st_backend_id_t const backend_id ) SIXTRL_NOEXCEPT
    {
        return ( ( backend_id == st::BACKEND_CPU ) ||
                 ( backend_id == st::BACKEND_OPENCL ) ||
                 ( backend_id == st::BACKEND_CUDA ) ||
                 ( backend_id == st::BACKEND_CUDA_NVRTC ) ||
                 ( backend_id == st::BACKEND_OPENMP ) );
    }

    bool this_t::IS_PREDEFINED_BACKEND(
        string_t const& SIXTRL_RESTRICT_REF backend_str ) SIXTRL_NOEXCEPT
    {
        return this_t::IS_PREDEFINED_BACKEND(
            this_t::PREDEFINED_BACKEND_STR_TO_ID( backend_str ) );
    }

    st_backend_id_t this_t::PREDEFINED_BACKEND_STR_TO_ID(
        string_t const& SIXTRL_RESTRICT_REF backend_str ) SIXTRL_NOEXCEPT
    {
        st_backend_id_t backend_id = st::BACKEND_ILLEGAL;

        if( !backend_str.empty() )
        {
            backend_id = st::BACKEND_UNDEFINED;

            if( backend_str.compare( SIXTRL_BACKEND_CPU_STR ) == 0 )
            {
                backend_id = st::BACKEND_CPU;
            }
            else if( backend_str.compare( SIXTRL_BACKEND_OPENCL_STR ) == 0 )
            {
                backend_id = st::BACKEND_OPENCL;
            }
            else if( backend_str.compare( SIXTRL_BACKEND_CUDA_STR ) == 0 )
            {
                backend_id = st::BACKEND_CUDA;
            }
            else if( backend_str.compare(
                    SIXTRL_BACKEND_CUDA_NVRTC_STR ) == 0 )
            {
                backend_id = st::BACKEND_CUDA_NVRTC;
            }
            else if( backend_str.compare( SIXTRL_BACKEND_OPENMP_STR ) == 0 )
            {
                backend_id = st::BACKEND_OPENMP;
            }
        }

        return backend_id;
    }

    string_t this_t::PREDEFINED_BACKEND_ID_TO_STR(
        st_backend_id_t const backend_id )
    {
        switch( backend_id )
        {
            case st::BACKEND_CPU:
            {
                return string_t{ SIXTRL_BACKEND_CPU_STR };
            }

            case st::BACKEND_OPENCL:
            {
                return string_t{ SIXTRL_BACKEND_OPENCL_STR };
            }

            case st::BACKEND_CUDA:
            {
                return string_t{ SIXTRL_BACKEND_CUDA_STR };
            }

            case st::BACKEND_CUDA_NVRTC:
            {
                return string_t{ SIXTRL_BACKEND_CUDA_NVRTC_STR };
            }

            case st::BACKEND_OPENMP:
            {
                return string_t{ SIXTRL_BACKEND_OPENMP_STR };
            }

            default:
            {
                SIXTRL_ASSERT( !this_t::IS_PREDEFINED_BACKEND( backend_id ) );
            }
        };

        return string_t{};
    }

    st_size_t this_t::REQUIRED_STR_BUFFER_CAPACITY_FOR_PREDEFINED_BACKEND(
        st_backend_id_t const backend_id )
    {
        string_t const temp( this_t::PREDEFINED_BACKEND_ID_TO_STR(
            backend_id ) );

        return temp.size() + st_size_t{ 1 };
    }

    st_status_t this_t::PREDEFINED_BACKEND_ID_TO_STR(
        str_char_t* SIXTRL_RESTRICT out_buffer,
        st_size_t const out_buffer_capacity,
        st_backend_id_t const backend_id ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( out_buffer != nullptr ) &&
            ( out_buffer_capacity > st_size_t{ 1 } ) )
        {
            string_t const temp( this_t::PREDEFINED_BACKEND_ID_TO_STR(
                backend_id ) );

            if( temp.size() < out_buffer_capacity )
            {
                std::fill( out_buffer, out_buffer + out_buffer_capacity,
                           '\0' );
                std::strncpy( out_buffer, temp.c_str(),
                              out_buffer_capacity - st_size_t{ 1 } );

                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    this_t::~BaseBackend() SIXTRL_NOEXCEPT
    {
        if( ( this->run_shutdown_backend_fn_explicitly() ) &&
            ( this->m_shutdown_backend_fn != nullptr ) )
        {
            this->m_shutdown_backend_fn();
        }
    }

    /* --------------------------------------------------------------------- */

    bool this_t::has_nodes() const SIXTRL_NOEXCEPT {
        return this->is_class_variant( this_t::BACKEND_VARIANT_HAS_NODES ); }

    st::BaseNodeBackend const* this_t::as_node_backend() const SIXTRL_NOEXCEPT
    {
        return ( this->has_nodes() )
            ? static_cast< st::BaseNodeBackend const* >( this ) : nullptr;
    }

    st::BaseNodeBackend* this_t::as_node_backend() SIXTRL_NOEXCEPT
    {
        return const_cast< st::BaseNodeBackend*  >( static_cast<
            this_t const& >( *this ).as_node_backend() );
    }

    /* --------------------------------------------------------------------- */

    bool this_t::has_dynamic_library_loader() const SIXTRL_NOEXCEPT
    {
        return ( this->m_dlib_loader.get() != nullptr );
    }

    bool this_t::has_dynamic_library_handle() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_dlib_loader.get() != nullptr ) &&
                 ( this->m_dlib_loader->has_dynamic_lib_handle() ) );
    }

    this_t::dlib_loader_t& this_t::dynamic_library_loader() SIXTRL_NOEXCEPT
    {
        return this->m_dlib_loader;
    }

    st::BaseDynLibLoader const*
    this_t::ptr_base_dynamic_library_loader() const SIXTRL_NOEXCEPT
    {
        return this->m_dlib_loader.get();
    }

    st::BaseDynLibLoader*
    this_t::ptr_base_dynamic_library_loader() SIXTRL_NOEXCEPT
    {
        return this->m_dlib_loader.get();
    }

    /* ********************************************************************* */

    constexpr this_t::symbol_name_flags_t
        this_t::SYMBOL_NAME_DO_NOTHING;

    constexpr this_t::symbol_name_flags_t
        this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR;

    constexpr this_t::symbol_name_flags_t
        this_t::SYMBOL_NAME_ADD_CXX_NAMESPACE_STR;

    /* --------------------------------------------------------------------- */

    st_status_t this_t::remove_symbol( this_t::be_symbol_id_t const
        symbol_id ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( symbol_id != this_t::SYMBOL_ID_ILLEGAL )
        {
            auto const num_erased = this->m_symbol_id_to_symbol_name_map.erase(
                symbol_id );

            if( num_erased > st_size_t{ 0 } )
            {
                SIXTRL_ASSERT( num_erased == st_size_t{ 1 } );
                status = st::STATUS_SUCCESS;
            }
        }

        SIXTRL_ASSERT( ( status != st::STATUS_SUCCESS ) ||
            ( !this->has_symbol_name( symbol_id ) ) );

        return status;
    }

    st_status_t this_t::set_symbol_name(
        this_t::be_symbol_id_t const symbol_id,
        this_t::string_type const& SIXTRL_RESTRICT_REF symbol_name,
        this_t::symbol_name_flags_t const flags )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( symbol_id != this_t::SYMBOL_ID_ILLEGAL )
        {
            if( !symbol_name.empty() )
            {
                this_t::sstream_t a2str;

                if( ( flags != this_t::SYMBOL_NAME_DO_NOTHING ) &&
                    ( ( flags &  this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR ) ==
                        this_t::SYMBOL_NAME_ADD_C99_NAMESPACE_STR ) )
                {
                    a2str << SIXTRL_C99_NAMESPACE_PREFIX_STR;
                }

                if( ( flags != this_t::SYMBOL_NAME_DO_NOTHING ) &&
                    ( ( flags &  this_t::SYMBOL_NAME_ADD_CXX_NAMESPACE_STR ) ==
                        this_t::SYMBOL_NAME_ADD_CXX_NAMESPACE_STR ) )
                {
                    a2str << SIXTRL_CXX_NAMESPACE_PREFIX_STR;
                }

                a2str << symbol_name;

                auto it = this->m_symbol_id_to_symbol_name_map.find( symbol_id );
                if( it == this->m_symbol_id_to_symbol_name_map.end() )
                {
                    auto ret = this->m_symbol_id_to_symbol_name_map.emplace(
                        std::make_pair( symbol_id, a2str.str() ) );

                    if( ret.second ) status = st::STATUS_SUCCESS;
                }
                else
                {
                    it->second = symbol_name;
                    status = st::STATUS_SUCCESS;
                }
            }
            else
            {
                status = this->remove_symbol( symbol_id );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    st_status_t this_t::update_undefined_backend_id(
        st_backend_id_t const backend_id ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( backend_id != st::BACKEND_ILLEGAL ) &&
            ( backend_id != st::BACKEND_UNDEFINED ) &&
            ( this->backend_id() == st::BACKEND_UNDEFINED ) &&
            ( !this->is_available() ) && ( !this->is_ready() ) )
        {
            status = this->set_backend_id( backend_id );
        }

        return status;
    }

    st_status_t this_t::update_undefined_backend_id_detailed(
        st_backend_id_t const backend_id,
        string_t const& SIXTRL_RESTRICT_REF backend_str )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( backend_id != st::BACKEND_ILLEGAL ) &&
            ( backend_id != st::BACKEND_UNDEFINED ) &&
            ( this->backend_id() == st::BACKEND_UNDEFINED ) &&
            ( !this->is_available() ) && ( !this->is_ready() ) )
        {
            status = this->set_backend_id( backend_id );
            if( status == st::STATUS_SUCCESS )
            {
                this->m_backend_str = backend_str;
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool this_t::is_available() const SIXTRL_NOEXCEPT
    {
        return this->m_is_available;
    }

    bool this_t::is_ready() const SIXTRL_NOEXCEPT
    {
        return ( ( this->is_available() ) && ( this->m_is_ready ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    this_t::run_dlib_init_finish_fn_flags_t
    this_t::run_init_backend_fn_mode() const SIXTRL_NOEXCEPT
    {
        return ( this->m_run_init_finish_fn_mode & (
            this_t::RUN_BACKEND_INIT_FN_AUTO |
            this_t::RUN_BACKEND_INIT_FN_EXPLICITLY ) );
    }

    this_t::run_dlib_init_finish_fn_flags_t
    this_t::run_shutdown_backend_fn_mode() const SIXTRL_NOEXCEPT
    {
        return ( this->m_run_init_finish_fn_mode & (
            this_t::RUN_BACKEND_SHUTDOWN_FN_AUTO |
            this_t::RUN_BACKEND_SHUTDOWN_FN_EXPLICITLY ) );
    }

    bool this_t::run_init_backend_fn_auto() const SIXTRL_NOEXCEPT
    {
        return !this->run_init_backend_fn_explicitly();
    }

    bool this_t::run_init_backend_fn_explicitly() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_run_init_finish_fn_mode &
                   this_t::RUN_BACKEND_INIT_FN_EXPLICITLY ) ==
                   this_t::RUN_BACKEND_INIT_FN_EXPLICITLY );
    }

    bool this_t::run_shutdown_backend_fn_auto() const SIXTRL_NOEXCEPT
    {
        return !this->run_shutdown_backend_fn_explicitly();
    }

    bool this_t::run_shutdown_backend_fn_explicitly() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_run_init_finish_fn_mode &
                   this_t::RUN_BACKEND_SHUTDOWN_FN_EXPLICITLY ) ==
                   this_t::RUN_BACKEND_SHUTDOWN_FN_EXPLICITLY );
    }

    /* --------------------------------------------------------------------- */

    bool this_t::has_backend_string() const SIXTRL_NOEXCEPT
    {
        return !this->m_backend_str.empty();
    }

    string_t const& this_t::backend_string_str() const SIXTRL_NOEXCEPT
    {
        return this->m_backend_str;
    }

    str_char_t const* this_t::backend_string() const SIXTRL_NOEXCEPT
    {
        return this->m_backend_str.c_str();
    }

    string_t this_t::config_key() const
    {
        sstream_t config_key;
        config_key << "backends";

        if( this->has_backend_string() )
        {
            config_key << "." << this->backend_string_str();
        }
        else
        {
            config_key << ".id_" << this->backend_id();
        }

        return config_key.str();
    }

    st_status_t this_t::configure(
        string_t const& SIXTRL_RESTRICT_REF config_string )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( !this->is_ready() )
        {
            in_sstream_t in_stream{ config_string };
            status = this->do_configure( in_stream, this->config_key() );
        }

        return status;
    }

    st_status_t this_t::configure_from_file(
        fs_string_t const& SIXTRL_RESTRICT_REF path_config_file )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        std::ifstream config_file_str( path_config_file, std::ios::in );

        if( ( !this->is_ready() ) && ( config_file_str.is_open() ) )
        {
            sstream_t config_key;
            config_key << "backends";

            if( this->has_backend_string() )
            {
                config_key << "." << this->backend_string_str();
            }
            else
            {
                config_key << ".id_" << this->backend_id();
            }

            status = this->do_configure( config_file_str, config_key.str() );
        }

        return status;
    }

    bool this_t::has_symbol_name(
        this_t::be_symbol_id_t const symbol_id ) const SIXTRL_NOEXCEPT
    {
        bool symbol_name_available = false;

        if( ( symbol_id != this_t::SYMBOL_ID_ILLEGAL ) &&
            ( !this->m_symbol_id_to_symbol_name_map.empty() ) )
        {
            auto it = this->m_symbol_id_to_symbol_name_map.find( symbol_id );
            symbol_name_available = (
                ( it != this->m_symbol_id_to_symbol_name_map.end() ) &&
                ( !it->second.empty() ) );
        }

        return symbol_name_available;
    }

    string_t const& this_t::symbol_name_str(
        this_t::be_symbol_id_t const symbol_id ) const
    {
        auto it = this->m_symbol_id_to_symbol_name_map.find( symbol_id );

        if( ( it == this->m_symbol_id_to_symbol_name_map.end() ) ||
            ( it->second.empty() ) )
        {
            if( symbol_id == this_t::SYMBOL_ID_ILLEGAL )
            {
                throw std::runtime_error( "symbol id is illegal" );
            }

            if( it == this->m_symbol_id_to_symbol_name_map.end() )
            {
                throw std::runtime_error( "symbol name not found" );
            }

            if( it->second.empty() )
            {
                throw std::runtime_error( "symbol name empty" );
            }
        }

        return it->second;
    }

    this_t::string_char_t const* this_t::symbol_name(
        this_t::be_symbol_id_t const symbol_id ) const SIXTRL_NOEXCEPT
    {
        this_t::string_char_t const* symbol_name_cstr = nullptr;
        auto it = this->m_symbol_id_to_symbol_name_map.find( symbol_id );

        if( ( symbol_id != this_t::SYMBOL_ID_ILLEGAL ) &&
            ( it != this->m_symbol_id_to_symbol_name_map.end() ) &&
            ( !it->second.empty() ) )
        {
            symbol_name_cstr = it->second.c_str();
        }

        return symbol_name_cstr;
    }

    st_status_t this_t::make_available()
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( !this->is_available() ) && ( !this->is_ready() ) )
        {
            status = this->do_make_available();

            if( status == st::STATUS_SUCCESS )
            {
                this->update_is_available_flag( true );
            }
        }

        return status;
    }

    st_status_t this_t::make_ready()
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->is_available() ) && ( !this->is_ready() ) )
        {
            status = this->do_make_ready();

            if( status == st::STATUS_SUCCESS )
            {
                this->update_is_ready_flag( true );
            }
        }

        return status;
    }

    /* ******************************************************************** */

    this_t::BaseBackend( st_backend_id_t const backend_id,
        string_t const& SIXTRL_RESTRICT_REF backend_name_str ) :
        st::BaseBackendObj( backend_id, st::CLASS_ID_BACKEND ),
        m_symbol_id_to_symbol_name_map(),
        m_backend_str( backend_name_str )
    {}

    st_status_t this_t::do_configure(
        std::istream& SIXTRL_RESTRICT_REF in_stream,
        std::string const& SIXTRL_RESTRICT_REF table_key )
    {
        st_status_t status = st::STATUS_SUCCESS;
        auto ptr_dlib_loader = this->ptr_base_dynamic_library_loader();

        if( ptr_dlib_loader != nullptr )
        {
            auto const conf = toml::parse( in_stream );

            if( conf.contains( table_key ) )
            {
                auto const& be_table = toml::find( conf, table_key );

                if( be_table.contains( "path_to_dlib" ) )
                {
                    auto const path_to_dlib = toml::find< fs_string_t >(
                        be_table, "path_to_dlib" );

                    if( !path_to_dlib.empty() )
                    {
                        status = ptr_dlib_loader->set_path_to_dlib(
                            path_to_dlib );
                    }
                }
            }
        }

        return status;
    }

    st_status_t this_t::do_make_available()
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( !this->is_available() ) && ( !this->is_ready() ) )
        {
            status = st::STATUS_SUCCESS;
            auto ptr_dlib_loader = this->ptr_base_dynamic_library_loader();

            if( ptr_dlib_loader != nullptr )
            {
                SIXTRL_ASSERT( ptr_dlib_loader->has_path_to_dynamic_lib() );
                status = ptr_dlib_loader->load_dynamic_library();
            }

            if( status == st::STATUS_SUCCESS )
            {
                status = this->do_assign_symbols();
            }

            if( status == st::STATUS_SUCCESS )
            {
                if( ( ( this->run_init_backend_fn_explicitly() ) &&
                      ( this->m_init_backend_fn == nullptr ) ) ||
                    ( ( this->run_shutdown_backend_fn_explicitly() ) &&
                      ( this->m_shutdown_backend_fn == nullptr ) ) )
                {
                    status = st::STATUS_GENERAL_FAILURE;
                }
            }
        }

        return status;
    }

    st_status_t this_t::do_assign_symbols()
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( !this->is_available() ) && ( !this->is_ready() ) )
        {
            status = st::STATUS_SUCCESS;
            auto ptr_dlib_loader = this->ptr_base_dynamic_library_loader();

            if( (  ptr_dlib_loader != nullptr ) &&
                ( !ptr_dlib_loader->has_dynamic_lib_handle() ) &&
                (  ptr_dlib_loader->has_path_to_dynamic_lib() ) )
            {
                status = ptr_dlib_loader->load_dynamic_library();
            }

            if( ( status == st::STATUS_SUCCESS ) &&
                ( ptr_dlib_loader != nullptr ) &&
                ( ptr_dlib_loader->has_dynamic_lib_handle() ) )
            {
                this_t::string_type symbol_name = (
                    this->has_symbol_name( this_t::SYMBOL_ID_INIT_BACKEND ) )
                    ? this->symbol_name( this_t::SYMBOL_ID_INIT_BACKEND )
                    : this_t::string_type{};

                this->m_init_backend_fn = ptr_dlib_loader->load_symbol<
                    decltype( this->m_init_backend_fn ) >( symbol_name,
                        this->run_init_backend_fn_explicitly() );

                symbol_name = ( this->has_symbol_name(
                        this_t::SYMBOL_ID_SHUTDOWN_BACKEND ) )
                    ? this->symbol_name( this_t::SYMBOL_ID_SHUTDOWN_BACKEND )
                    : this_t::string_type{};

                this->m_shutdown_backend_fn = ptr_dlib_loader->load_symbol<
                    decltype( this->m_shutdown_backend_fn ) >( symbol_name,
                        this->run_shutdown_backend_fn_explicitly() );
            }
        }

        return status;
    }

    st_status_t this_t::do_reset_symbols()
    {
        this->m_init_backend_fn = nullptr;
        this->m_shutdown_backend_fn = nullptr;
        return st::STATUS_SUCCESS;
    }

    st_status_t this_t::do_make_ready()
    {
        return ( ( this->is_available() ) && ( !this->is_ready() ) )
            ? st::STATUS_SUCCESS : st::STATUS_GENERAL_FAILURE;
    }

    st_status_t this_t::set_backend_string(
        string_t const& SIXTRL_RESTRICT_REF backend_str ) {
        this->m_backend_str = backend_str;
        return SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS;
    }

    bool this_t::check_is_base_backend_ready() const SIXTRL_NOEXCEPT
    {
        return this->is_available();
    }

    void this_t::update_is_available_flag(
        bool const is_available ) SIXTRL_NOEXCEPT
    {
        this->m_is_available = is_available;
    }

    void this_t::update_is_ready_flag( bool const is_ready ) SIXTRL_NOEXCEPT
    {
        this->m_is_ready = is_ready;
    }

    void this_t::update_run_init_finish_fn_mode(
        this_t::run_dlib_init_finish_fn_flags_t const
            run_init_finish_mode ) SIXTRL_NOEXCEPT
    {
        this->m_run_init_finish_fn_mode = ( (
            this_t::RUN_BACKEND_INIT_FN_AUTO |
            this_t::RUN_BACKEND_INIT_FN_EXPLICITLY |
            this_t::RUN_BACKEND_SHUTDOWN_FN_AUTO |
            this_t::RUN_BACKEND_SHUTDOWN_FN_EXPLICITLY ) &
            run_init_finish_mode );
    }
}

#endif /* C++, Host */