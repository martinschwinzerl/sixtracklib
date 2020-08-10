#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/backend/backends_store.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <toml.hpp>

        #include <algorithm>
        #include <fstream>
        #include <iostream>
        #include <sstream>
        #include <utility>
    #endif /* c++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using store_t = st::BackendsStore;
        using base_backend_t = st::BaseBackend;
        using st_backend_id_t = store_t::backend_id_t;
        using st_status_t = store_t::status_t;
        using string_t = store_t::string_type;
        using str_char_t = store_t::string_char_t;
        using sstream_t = base_backend_t::sstream_t;
    }

    constexpr st_backend_id_t store_t::MIN_USERDEFINED_BACKEND_ID;
    constexpr st_backend_id_t store_t::MAX_USERDEFINED_BACKEND_ID;

    constexpr store_t::config_source_t store_t::CONFIG_NONE;
    constexpr store_t::config_source_t store_t::CONFIG_STRING;
    constexpr store_t::config_source_t store_t::CONFIG_FILE;

    /* --------------------------------------------------------------------- */

    st_status_t store_t::INIT_PREDEFINED_BACKENDS(
        store_t& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( backend_store ) )
    {
        return st::STATUS_GENERAL_FAILURE;
    }

    /* --------------------------------------------------------------------- */

    store_t::BackendsStore() :
        m_id_to_backends(), m_backend_str_to_backend_id(),
        m_stored_backend_ids(), m_backends_with_nodes(),
        m_node_id_format_backendid_regex_str(),
        m_node_id_format_backendstr_regex_str(),
        m_config_data(),
        m_next_userdefined_backend_id( store_t::MIN_USERDEFINED_BACKEND_ID ),
        m_config_source( store_t::CONFIG_NONE )
    {

    }

    bool store_t::has_backend(
        st_backend_id_t const backend_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( backend_id != st::BACKEND_ILLEGAL ) &&
                 ( backend_id != st::BACKEND_UNDEFINED ) &&
                 ( this->m_id_to_backends.find( backend_id ) !=
                   this->m_id_to_backends.end() ) );
    }

    bool store_t::has_backend_by_str(
        string_t const& SIXTRL_RESTRICT_REF backend_str ) const SIXTRL_NOEXCEPT
    {
        return this->has_backend( this->backend_id_by_str( backend_str ) );
    }

    bool store_t::has_backend_string(
        st_backend_id_t const backend_id ) const SIXTRL_NOEXCEPT
    {
        bool has_backend_str = false;

        SIXTRL_ASSERT( this->m_id_to_backends.size() ==
                       this->m_stored_backend_ids.size() );

        SIXTRL_ASSERT( this->m_stored_backend_ids.size() >=
                       this->m_backend_str_to_backend_id.size() );

        if( ( backend_id != st::BACKEND_ILLEGAL ) &&
            ( backend_id != st::BACKEND_UNDEFINED ) )
        {
            auto it = this->m_id_to_backends.find( backend_id );

            if( ( it != this->m_id_to_backends.end() ) &&
                ( it->second.get() != nullptr ) )
            {
                has_backend_str = it->second->has_backend_string();

                SIXTRL_ASSERT( ( !has_backend_str ) ||
                    ( ( !it->second->backend_string_str().empty() ) &&
                      ( this->m_backend_str_to_backend_id.find(
                        it->second->backend_string_str() ) !=
                        this->m_backend_str_to_backend_id.end() ) &&
                      ( this->m_backend_str_to_backend_id.find(
                        it->second->backend_string_str() )->second == backend_id ) ) );
            }
        }

        return has_backend_str;
    }

    string_t const& store_t::backend_string_str(
        st_backend_id_t const backend_id ) const
    {
        SIXTRL_ASSERT( this->m_id_to_backends.size() ==
                       this->m_stored_backend_ids.size() );

        SIXTRL_ASSERT( this->m_stored_backend_ids.size() >=
                       this->m_backend_str_to_backend_id.size() );

        if( ( backend_id == st::BACKEND_ILLEGAL ) ||
            ( backend_id == st::BACKEND_UNDEFINED ) )
        {
            throw std::runtime_error( "illegal/undefined backend_id" );
        }

        auto it = this->m_id_to_backends.find( backend_id );

        if( it == this->m_id_to_backends.end() )
        {
            throw std::runtime_error( "backend_id not stored" );
        }

        if( it->second.get() == nullptr )
        {
            throw std::runtime_error( "empty / null backend stored" );
        }

        if( !it->second->has_backend_string() )
        {
            throw std::runtime_error( "stored backend has no backend_string" );
        }

        return it->second->backend_string_str();
    }

    char const* store_t::backend_string(
        st_backend_id_t const backend_id ) const SIXTRL_NOEXCEPT
    {
        char const* backend_cstring = nullptr;

        SIXTRL_ASSERT( this->m_id_to_backends.size() ==
                       this->m_stored_backend_ids.size() );

        SIXTRL_ASSERT( this->m_stored_backend_ids.size() >=
                       this->m_backend_str_to_backend_id.size() );

        if( ( backend_id != st::BACKEND_ILLEGAL ) &&
            ( backend_id != st::BACKEND_UNDEFINED ) )
        {
            auto it = this->m_id_to_backends.find( backend_id );

            if( ( it != this->m_id_to_backends.end() ) &&
                ( it->second.get() != nullptr ) )
            {
                if( it->second->has_backend_string() )
                {
                    backend_cstring = it->second->backend_string();
                }
            }
        }

        return backend_cstring;
    }

    st_backend_id_t store_t::backend_id_by_str( string_t const&
        SIXTRL_RESTRICT_REF backend_str ) const SIXTRL_NOEXCEPT
    {
        st_backend_id_t backend_id = st::BACKEND_ILLEGAL;

        SIXTRL_ASSERT( this->m_id_to_backends.size() ==
                       this->m_stored_backend_ids.size() );

        SIXTRL_ASSERT( this->m_stored_backend_ids.size() >=
                       this->m_backend_str_to_backend_id.size() );

        if( !backend_str.empty() )
        {
            auto it = this->m_backend_str_to_backend_id.find( backend_str );

            if( it != this->m_backend_str_to_backend_id.end() )
            {
                SIXTRL_ASSERT(
                    ( it->second != st::BACKEND_ILLEGAL ) &&
                    ( it->second != st::BACKEND_UNDEFINED ) &&
                    ( this->has_backend( it->second ) ) );

                backend_id = it->second;
            }
        }

        return backend_id;
    }

    st_size_t store_t::num_backends() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_id_to_backends.size() ==
                       this->m_stored_backend_ids.size() );

        SIXTRL_ASSERT( this->m_stored_backend_ids.size() >=
                       this->m_backend_str_to_backend_id.size() );

        return this->m_stored_backend_ids.size();
    }

    st_backend_id_t store_t::backend_id_by_idx(
        st_size_t const idx ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_id_to_backends.size() ==
                       this->m_stored_backend_ids.size() );

        SIXTRL_ASSERT( this->m_stored_backend_ids.size() >=
                       this->m_backend_str_to_backend_id.size() );

        return ( this->m_stored_backend_ids.size() > idx )
            ? this->m_stored_backend_ids[ idx ]
            : st::BACKEND_ILLEGAL;
    }

    st_backend_id_t const* store_t::backend_ids_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_id_to_backends.size() ==
                       this->m_stored_backend_ids.size() );

        SIXTRL_ASSERT( this->m_stored_backend_ids.size() >=
                       this->m_backend_str_to_backend_id.size() );

        return ( !this->m_stored_backend_ids.empty() )
            ? this->m_stored_backend_ids.data() : nullptr;
    }

    st_backend_id_t const* store_t::backend_ids_end() const SIXTRL_NOEXCEPT
    {
        auto ptr_end = this->backend_ids_begin();

        if( ptr_end != nullptr )
        {
            SIXTRL_ASSERT( this->m_id_to_backends.size() ==
                        this->m_stored_backend_ids.size() );

            SIXTRL_ASSERT( this->m_stored_backend_ids.size() >=
                        this->m_backend_str_to_backend_id.size() );

            std::advance( ptr_end, this->m_stored_backend_ids.size() );
        }

        return ptr_end;
    }

    base_backend_t const* store_t::backend(
        st_backend_id_t const backend_id ) const SIXTRL_NOEXCEPT
    {
        base_backend_t const* ptr_backend = nullptr;

        if( ( backend_id != st::BACKEND_ILLEGAL ) &&
            ( backend_id != st::BACKEND_UNDEFINED ) )
        {
            auto it = this->m_id_to_backends.find( backend_id );

            if( it != this->m_id_to_backends.end() )
            {
                ptr_backend = it->second.get();
            }
        }

        return ptr_backend;
    }

    base_backend_t* store_t::backend( st_backend_id_t const backend_id ) SIXTRL_NOEXCEPT
    {
        return const_cast< base_backend_t* >( static_cast< store_t const& >(
            *this ).backend( backend_id ) );
    }

    base_backend_t const* store_t::backend_by_str(
        string_t const& SIXTRL_RESTRICT_REF backend_str ) const SIXTRL_NOEXCEPT
    {
        return this->backend( this->backend_id_by_str( backend_str ) );
    }

    base_backend_t* store_t::backend_by_str( string_t const&
        SIXTRL_RESTRICT_REF backend_str ) SIXTRL_NOEXCEPT
    {
        return this->backend( this->backend_id_by_str( backend_str ) );
    }

    base_backend_t const* store_t::backend_by_idx(
        st_size_t const idx ) const SIXTRL_NOEXCEPT
    {
        return this->backend( this->backend_id_by_idx( idx ) );
    }

    base_backend_t* store_t::backend_by_idx( st_size_t const idx ) SIXTRL_NOEXCEPT
    {
        return this->backend( this->backend_id_by_idx( idx ) );
    }

    /* --------------------------------------------------------------------- */

    bool store_t::has_backends_with_nodes() const SIXTRL_NOEXCEPT {
        return !this->m_backends_with_nodes.empty(); }

    store_t::backend_id_t const*
    store_t::backends_with_nodes_begin() const SIXTRL_NOEXCEPT {
        return ( !this->m_backends_with_nodes.empty() )
            ? this->m_backends_with_nodes.data() : nullptr; }

    store_t::backend_id_t const*
    store_t::backends_with_nodes_end() const SIXTRL_NOEXCEPT {
        auto end_ptr = this->backends_with_nodes_begin();
        if( end_ptr != nullptr )
            std::advance( end_ptr, this->m_backends_with_nodes.size() );
        return end_ptr;
    }

    st_size_t store_t::backend_string_for_backends_with_nodes(
        string_t* backend_str_begin, st_size_t const max_num_backend_str ) const
    {
        return ( ( backend_str_begin != nullptr ) &&
                 ( max_num_backend_str > st_size_t{ 0 } ) )
            ? this->backend_string_for_backends_with_nodes(
                backend_str_begin, backend_str_begin + max_num_backend_str )
            : st_size_t{ 0 };
    }

    /* --------------------------------------------------------------------- */

    string_t const& store_t::node_id_format_backendid_regex_str()
    {
        if( ( this->m_node_id_format_backendid_regex_str.empty() ) &&
            ( this->has_backends_with_nodes() ) )
        {
            this->do_update_node_id_format_regex_strs();
        }

        return this->m_node_id_format_backendid_regex_str;
    }

    string_t const& store_t::node_id_format_backendstr_regex_str()
    {
        if( ( this->m_node_id_format_backendstr_regex_str.empty() ) &&
            ( this->has_backends_with_nodes() ) )
        {
            this->do_update_node_id_format_regex_strs();
        }

        return this->m_node_id_format_backendid_regex_str;
    }

    string_t store_t::node_id_format_backendid_regex_str_for_backend(
        st_backend_id_t const backend_id )
    {
        sstream_t a2str;
        auto backend = this->backend( backend_id );

        if( ( backend != nullptr ) && ( backend->has_nodes() ) )
        {
            SIXTRL_ASSERT( backend_id != st::BACKEND_ILLEGAL );
            a2str << backend_id << "\\:([0-9]{1,3})\\.([0-9]{1,3})";
        }

        return a2str.str();
    }

    string_t store_t::node_id_format_backendstr_regex_str_for_backend(
        st_backend_id_t const backend_id )
    {
        sstream_t a2str;
        auto backend = this->backend( backend_id );

        if( ( backend != nullptr ) && ( backend->has_nodes() ) &&
            ( backend->has_backend_string() ) )
        {
            SIXTRL_ASSERT( backend_id != st::BACKEND_ILLEGAL );
            a2str << backend->backend_string_str()
                  << "\\:([0-9]{1,3})\\.([0-9]{1,3})";
        }

        return a2str.str();
    }

    /* --------------------------------------------------------------------- */

    st_status_t store_t::add_backend(
        std::unique_ptr< base_backend_t > backend_to_store )
    {
        return this->do_add_backend( std::move( backend_to_store ) );
    }

    st_status_t store_t::remove_backend( st_backend_id_t const backend_id )
    {
        return this->do_remove_backend( backend_id );
    }

    st_status_t store_t::remove_backend_by_str(
        string_t const& SIXTRL_RESTRICT_REF backend_str )
    {
        return this->do_remove_backend( this->backend_id_by_str( backend_str ) );
    }

    /* --------------------------------------------------------------------- */

    bool store_t::has_config_data() const SIXTRL_NOEXCEPT {
        return ( ( this->m_config_source == store_t::CONFIG_STRING ) ||
                 ( this->m_config_source == store_t::CONFIG_FILE ) ) &&
               ( !this->m_config_data.empty() );
    }

    bool store_t::has_config_string() const SIXTRL_NOEXCEPT
    {
        return ( (  this->m_config_source == store_t::CONFIG_STRING ) &&
                 ( !this->m_config_data.empty() ) );
    }

    bool store_t::has_path_to_config_file() const SIXTRL_NOEXCEPT
    {
        return ( (  this->m_config_source == store_t::CONFIG_FILE ) &&
                 ( !this->m_config_data.empty() ) );
    }

    store_t::config_source_t store_t::config_source() const SIXTRL_NOEXCEPT {
        return this->m_config_source;
    }

    string_t const& store_t::config_string_str() const
    {
        if( this->m_config_source != store_t::CONFIG_STRING )
        {
            throw std::runtime_error( "wrong config source != CONFIG_STRING" );
        }

        return this->m_config_data;
    }

    store_t::string_char_t const*
    store_t::config_string() const SIXTRL_NOEXCEPT
    {
        return ( this->has_config_string() )
            ? this->m_config_data.data() : nullptr;
    }

    st_status_t store_t::set_config_string(
        string_t const& SIXTRL_RESTRICT_REF config_str )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( !config_str.empty() )
        {
            store_t::config_source_t source = store_t::CONFIG_STRING;

            try
            {
                std::istringstream config_stream{ config_str };
                auto const test_conf = toml::parse( config_stream );
            }
            catch( toml::syntax_error const& err )
            {
                std::cerr << "unable to parse input config string: \r\n"
                          << err.what() << std::endl;
                source = store_t::CONFIG_NONE;
            }

            if( source == store_t::CONFIG_STRING )
            {
                this->m_config_data = config_str;
                this->m_config_source = source;
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    store_t::fs_string_type const& store_t::path_to_config_file_str() const
    {
        /* TODO: Convert between string_type and fs_string_type! */
        if( this->m_config_source != store_t::CONFIG_FILE )
        {
            throw std::runtime_error( "wrong config source != CONFIG_FILE" );
        }

        return this->m_config_data;
    }

    store_t::fs_string_char_t const*
    store_t::path_to_config_file() const SIXTRL_NOEXCEPT
    {
        /* TODO: Convert between string_type and fs_string_type! */
        return ( this->has_path_to_config_file() )
            ? this->m_config_data.c_str() : nullptr;
    }

    st_status_t store_t::set_path_to_config_file(
        store_t::fs_string_type const& SIXTRL_RESTRICT_REF path_to_file )
    {
        /* TODO: Convert between fs_string_type and string_type! */

        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( !path_to_file.empty() )
        {
            std::ifstream config_stream( path_to_file.c_str(),
                std::ios::in );

            if( config_stream.is_open() )
            {
                store_t::config_source_t source = store_t::CONFIG_FILE;

                try
                {
                    auto const test_conf = toml::parse( config_stream );
                }
                catch( toml::syntax_error const& err )
                {
                    std::cerr << "unable to parse input config file \""
                              << path_to_file << "\": \r\n"
                              << err.what() << std::endl;
                    source = store_t::CONFIG_NONE;
                }

                if( source == store_t::CONFIG_FILE )
                {
                    this->m_config_data = path_to_file;
                    this->m_config_source = source;
                    status = st::STATUS_SUCCESS;
                }
            }
        }

        return status;

    }

    st_status_t store_t::set_config_data(
        string_t const& SIXTRL_RESTRICT_REF config_data,
        store_t::config_source_t const source )
    {
         /* TODO: Convert between fs_string_type and string_type! */
         st_status_t status = st::STATUS_GENERAL_FAILURE;

         switch( source )
         {
             case store_t::CONFIG_FILE:
             {
                 status = this->set_path_to_config_file( config_data );
                 break;
             }

             case store_t::CONFIG_STRING:
             {
                 status = this->set_config_string( config_data );
                 break;
             }

             case store_t::CONFIG_NONE:
             {
                 this->reset_config_data();
                 status = st::STATUS_SUCCESS;
             }

             default:
             {
                 status = st::STATUS_GENERAL_FAILURE;
             }
         };

         return status;
    }

    void store_t::reset_config_data()
    {
        this->m_config_data.clear();
        this->m_config_source = store_t::CONFIG_NONE;
    }

    /* --------------------------------------------------------------------- */

    st_status_t store_t::init_backend( store_t::backend_id_t const backend_id )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        auto bend = this->backend( backend_id );

        if( bend != nullptr )
        {
            status = st::STATUS_SUCCESS;

            if( !bend->is_available() )
            {
                if( this->has_config_string() )
                {
                    status = bend->configure( this->config_string_str() );
                }
                else if( this->has_path_to_config_file() )
                {
                    status = bend->configure_from_file(
                        this->path_to_config_file_str() );
                }

                if( status == st::STATUS_SUCCESS )
                {
                    status = bend->make_available();
                }
            }

            if( ( status == st::STATUS_SUCCESS ) &&
                ( bend->is_available() ) && ( !bend->is_ready() ) )
            {
                status = bend->make_ready();
            }
        }

        return status;
    }

    st_status_t store_t::init_backend_with_config(
        store_t::backend_id_t const backend_id,
        string_t const& SIXTRL_RESTRICT_REF config_string )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        auto bend = this->backend( backend_id );

        if( bend != nullptr )
        {
            status = st::STATUS_SUCCESS;

            if( !bend->is_available() )
            {
                status = bend->configure( config_string );

                if( status == st::STATUS_SUCCESS )
                {
                    status = bend->make_available();
                }
            }

            if( ( status == st::STATUS_SUCCESS ) &&
                ( bend->is_available() ) && ( !bend->is_ready() ) )
            {
                status = bend->make_ready();
            }
        }

        return status;
    }

    st_status_t store_t::init_backend_with_config_file(
        store_t::backend_id_t const backend_id,
        store_t::fs_string_type const& SIXTRL_RESTRICT_REF path_to_conf_file )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        auto bend = this->backend( backend_id );

        if( bend != nullptr )
        {
            status = st::STATUS_SUCCESS;

            if( !bend->is_available() )
            {
                status = bend->configure_from_file( path_to_conf_file );

                if( status == st::STATUS_SUCCESS )
                {
                    status = bend->make_available();
                }
            }

            if( ( status == st::STATUS_SUCCESS ) &&
                ( bend->is_available() ) && ( !bend->is_ready() ) )
            {
                status = bend->make_ready();
            }
        }

        return status;
    }

    /* ===================================================================== */

    st_status_t store_t::do_add_backend(
        std::unique_ptr< base_backend_t >&& backend_to_store )
    {
        return this->do_add_backend_base_impl(
            std::move( backend_to_store ) );
    }

    st_status_t store_t::do_remove_backend( st_backend_id_t const backend_id )
    {
        return this->do_remove_backend_base_impl( backend_id );
    }

    /* --------------------------------------------------------------------- */

    st_status_t store_t::do_add_backend_base_impl(
        std::unique_ptr< base_backend_t >&& backend_to_store )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( backend_to_store.get() == nullptr )
        {
            return status;
        }

        bool const backend_has_nodes = backend_to_store->has_nodes();

        st_backend_id_t backend_id = backend_to_store->backend_id();

        if( ( backend_id != st::BACKEND_ILLEGAL ) &&
            ( base_backend_t::IS_PREDEFINED_BACKEND( backend_id ) ) )
        {
            status = st::STATUS_SUCCESS;
        }
        else if( ( backend_id == st::BACKEND_UNDEFINED ) &&
                 ( this->m_next_userdefined_backend_id <
                   store_t::MAX_USERDEFINED_BACKEND_ID ) )
        {
            auto max_it = std::max_element( this->m_stored_backend_ids.begin(),
                this->m_stored_backend_ids.end() );

            if( (  max_it != this->m_stored_backend_ids.end() ) &&
                ( *max_it >= this->m_next_userdefined_backend_id ) )
            {
                return st::STATUS_GENERAL_FAILURE;
            }

            status = backend_to_store->update_undefined_backend_id(
                this->m_next_userdefined_backend_id++ );
        }

        if( status == st::STATUS_SUCCESS )
        {
            SIXTRL_ASSERT( this->m_backend_str_to_backend_id.size() <=
                           this->m_stored_backend_ids.size() );

            SIXTRL_ASSERT( this->m_id_to_backends.size() ==
                           this->m_stored_backend_ids.size() );

            auto it = this->m_id_to_backends.find( backend_id );
            if( it != this->m_id_to_backends.end() )
            {
                SIXTRL_ASSERT( ( !backend_to_store->has_backend_string() ) ||
                    ( ( ( this->m_backend_str_to_backend_id.find(
                            backend_to_store->backend_string_str() ) !=
                          this->m_backend_str_to_backend_id.end() ) &&
                        ( this->m_backend_str_to_backend_id.find(
                            backend_to_store->backend_string_str() )->second
                                == backend_id ) ) ) );

                SIXTRL_ASSERT( std::find( this->m_stored_backend_ids.begin(),
                    this->m_stored_backend_ids.end(), backend_id ) !=
                        this->m_stored_backend_ids.end() );

                return st::STATUS_GENERAL_FAILURE;
            }

            if( status == st::STATUS_SUCCESS )
            {
                auto res = this->m_id_to_backends.emplace(
                    std::make_pair( backend_id, std::move(
                        backend_to_store ) ) );

                if( res.second )
                {
                    SIXTRL_ASSERT(
                        ( !res.first->second->has_backend_string() ) ||
                        ( this->m_backend_str_to_backend_id.find(
                            res.first->second->backend_string_str() ) ==
                                this->m_backend_str_to_backend_id.end() ) );

                    if( res.first->second->has_backend_string() )
                    {
                        auto res2 = this->m_backend_str_to_backend_id.emplace(
                            std::make_pair(
                                res.first->second->backend_string_str(),
                                backend_id ) );

                        if( !res2.second )
                        {
                            this->m_id_to_backends.erase( res.first );
                            status = st::STATUS_GENERAL_FAILURE;
                        }
                    }

                    if( status == st::STATUS_SUCCESS )
                    {
                        this->m_stored_backend_ids.push_back( backend_id );

                        if( backend_has_nodes )
                        {
                            this->m_backends_with_nodes.push_back( backend_id );
                            this->m_node_id_format_backendid_regex_str.clear();
                            this->m_node_id_format_backendstr_regex_str.clear();
                        }
                    }
                }
                else
                {
                    status = st::STATUS_GENERAL_FAILURE;
                }
            }

            SIXTRL_ASSERT( ( status != st::STATUS_SUCCESS ) ||
                ( ( this->m_id_to_backends.size() ==
                    this->m_stored_backend_ids.size() ) &&
                  ( this->m_backend_str_to_backend_id.size() <=
                    this->m_stored_backend_ids.size() ) &&
                  ( this->m_backends_with_nodes.size() <=
                    this->m_stored_backend_ids.size() ) &&
                  ( this->m_id_to_backends.find( backend_id ) !=
                    this->m_id_to_backends.end() ) &&
                  ( this->m_id_to_backends.find( backend_id )->second.get()
                    != nullptr ) ) );
        }

        return status;
    }

    st_status_t store_t::do_remove_backend_base_impl(
        st_backend_id_t const backend_id ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( backend_id != st::BACKEND_ILLEGAL ) &&
            ( backend_id != st::BACKEND_UNDEFINED ) )
        {
            SIXTRL_ASSERT( this->m_id_to_backends.size() ==
                           this->m_stored_backend_ids.size() );

            SIXTRL_ASSERT( this->m_backend_str_to_backend_id.size() <=
                           this->m_stored_backend_ids.size() );

            auto map_it = this->m_id_to_backends.find( backend_id );
            auto list_it = std::find( this->m_stored_backend_ids.begin(),
                this->m_stored_backend_ids.end(), backend_id );

            auto str_found = this->m_backend_str_to_backend_id.end();
            auto str_it = this->m_backend_str_to_backend_id.begin();

            for( ; str_it != this->m_backend_str_to_backend_id.end() ; ++str_it )
            {
                if( str_it->second == backend_id )
                {
                    str_found = str_it;
                    break;
                }
            }

            if( ( map_it != this->m_id_to_backends.end() ) &&
                ( map_it->second.get() != nullptr ) &&
                ( list_it != this->m_stored_backend_ids.end() ) &&
                ( ( !map_it->second->has_backend_string() ) ||
                  ( ( str_it != this->m_backend_str_to_backend_id.end() ) &&
                    ( str_it->first.compare(
                        map_it->second->backend_string() ) == 0 ) ) ) )
            {
                if( map_it->second->has_nodes() )
                {
                    this->m_node_id_format_backendid_regex_str.clear();
                    this->m_node_id_format_backendstr_regex_str.clear();
                }

                this->m_id_to_backends.erase( map_it );
                this->m_stored_backend_ids.erase( list_it );

                if( str_it != this->m_backend_str_to_backend_id.end() )
                {
                    this->m_backend_str_to_backend_id.erase( str_it );
                }

                status = st::STATUS_SUCCESS;
            }
            else if( ( map_it == this->m_id_to_backends.end() ) &&
                  ( list_it == this->m_stored_backend_ids.end() ) &&
                  ( str_it == this->m_backend_str_to_backend_id.end() ) )
            {
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    st_status_t store_t::do_update_node_id_format_regex_strs()
    {
        this->m_node_id_format_backendid_regex_str.clear();
        this->m_node_id_format_backendstr_regex_str.clear();

        if( !this->m_backends_with_nodes.empty() )
        {
            sstream_t backendid_regex;
            sstream_t backendstr_regex;

            if( this->m_backends_with_nodes.size() > st_size_t{ 0 } )
            {
                st_size_t nn_backendid = st_size_t{ 0 };
                st_size_t nn_backendstr = st_size_t{ 0 };

                if( this->m_backends_with_nodes.size() > st_size_t{ 1 } )
                {
                    backendid_regex << "(";
                }

                for( auto const backend_id : this->m_backends_with_nodes )
                {
                    auto backend = this->backend( backend_id );
                    SIXTRL_ASSERT( backend != nullptr );
                    SIXTRL_ASSERT( backend->has_nodes() );

                    if( nn_backendid > st_size_t{ 0 } ) backendid_regex << "|";
                    backendid_regex << backend_id;
                    ++nn_backendid;

                    if( backend->has_backend_string() ) ++nn_backendstr;
                }

                if( this->m_backends_with_nodes.size() > st_size_t{ 1 } )
                {
                    backendid_regex << ")";
                }

                backendid_regex << "\\:([0-9]{1,3})\\.([0-9]{1,3})";

                if( nn_backendstr >= st_size_t{ 1 } )
                {
                    st_size_t ii = st_size_t{ 0 };
                    if( nn_backendstr > st_size_t{ 1 } ) backendstr_regex << "(";

                    for( auto const backend_id : this->m_backends_with_nodes )
                    {
                        auto backend = this->backend( backend_id );
                        SIXTRL_ASSERT( backend != nullptr );
                        SIXTRL_ASSERT( backend->has_nodes() );
                        if( !backend->has_backend_string() ) continue;

                        if( ii == nn_backendstr ) break;
                        if( ii > st_size_t{ 0 } ) backendstr_regex << "|";

                        backendstr_regex << backend->backend_string_str();
                        ++ii;
                    }

                    if( nn_backendstr > st_size_t{ 1 } ) backendstr_regex << ")";
                    backendstr_regex << "\\:([0-9]{1,3})\\.([0-9]{1,3})";
                }
            }

            this->m_node_id_format_backendid_regex_str = backendid_regex.str();
            this->m_node_id_format_backendstr_regex_str = backendstr_regex.str();
        }

        return st::STATUS_SUCCESS;
    }

    void store_t::do_clear_node_id_format_regex_strs()
    {
        this->m_node_id_format_backendid_regex_str.clear();
        this->m_node_id_format_backendstr_regex_str.clear();
    }

    /* ********************************************************************* */

    store_t const& BackendsStore_const_global() {
        static store_t const global_store;
        return global_store;
    }

    store_t& BackendsStore_global() {
        return const_cast< store_t& >( st::BackendsStore_const_global() );
    }

    store_t const* BackendsStore_ptr_const_global() {
        return std::addressof( st::BackendsStore_const_global() );
    }

    store_t* BackendsStore_ptr_global() {
        return std::addressof( st::BackendsStore_global() );
    }
}

::NS(BackendsStore) const* NS(BackendsStore_ptr_const_global)()
{
    return SIXTRL_CXX_NAMESPACE::BackendsStore_ptr_const_global();
}

::NS(BackendsStore)* NS(BackendsStore_ptr_global)()
{
    return SIXTRL_CXX_NAMESPACE::BackendsStore_ptr_global();
}

#endif /* C++, Host */
