#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/control/program_store.h"
    #include "sixtracklib/opencl/control/program_item.h"
#endif /* !defined( SIXTRL_NO_INCLUDES )  */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <cctype>
    #include <cstdio>
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <sstream>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <toml.hpp>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using store_type                = st::OclProgramStore;
        using base_store_type           = st::ProgramStoreBase;
        using st_status_t               = store_type::status_type;
        using st_key_t                  = store_type::key_type;
        using st_prog_id_t              = store_type::program_id_type;
        using base_prg_item_type        = store_type::item_base_type;
        using ocl_base_prg_item_type    = store_type::ocl_program_item_type;
        using ocl_prg_config_store_type = st::OclProgramConfigStore;
        using ocl_prg_config_key_type   = ocl_prg_config_store_type::program_key_type;
        using ocl_prg_config_item_type  = ocl_prg_config_store_type::config_item_type;
        using ocl_rtc_prg_item_type     = st::OclRtcProgramItem;
        using ctx_key_type              = st::OclContextKey;

        SIXTRL_STATIC inline bool _string_is_integer(
            std::string const& SIXTRL_RESTRICT_REF str )
        {
            return ( ( !str.empty() ) &&
                     ( str.end() == std::find_if( str.begin(), str.end(),
                        []( unsigned char const ch ) -> bool {
                            return !std::isdigit( ch ); } ) ) );
        }
    }

    /* ********************************************************************* */

    constexpr ocl_prg_config_store_type::class_id_type
        ocl_prg_config_store_type::BASE_CLASS_ID;

    constexpr ocl_prg_config_store_type::class_id_type
        ocl_prg_config_store_type::CLASS_ID;

    constexpr ocl_prg_config_store_type::config_source_type
        ocl_prg_config_store_type::SOURCE_NOT_FOUND;

    constexpr ocl_prg_config_store_type::config_source_type
        ocl_prg_config_store_type::SOURCE_EXACT;

    constexpr ocl_prg_config_store_type::config_source_type
        ocl_prg_config_store_type::SOURCE_CONTEXT;

    constexpr ocl_prg_config_store_type::config_source_type
        ocl_prg_config_store_type::SOURCE_PLATFORM;

    constexpr ocl_prg_config_store_type::config_source_type
        ocl_prg_config_store_type::SOURCE_PROGRAM;

    constexpr ocl_prg_config_store_type::config_source_type
        ocl_prg_config_store_type::SOURCE_GLOBAL;


    st_status_t OclProgramConfigItem_update_from_toml_table(
        st::OclProgramConfigItem& SIXTRL_RESTRICT_REF config_item,
        toml::table const& SIXTRL_RESTRICT_REF node );

    st_status_t OclProgramConfigStore_update_from_toml_table(
        st::OclProgramConfigStore& SIXTRL_RESTRICT_REF config_store,
        toml::value const& SIXTRL_RESTRICT_REF top_level_table );

    void ocl_prg_config_store_type::clear() { this->m_items.clear(); }

    st_status_t ocl_prg_config_store_type::update_from_file(
        std::string const& SIXTRL_RESTRICT_REF path_to_config_file )
    {
        ::FILE* fp = std::fopen( path_to_config_file.c_str(), "r" );
        if( fp == nullptr ) return st::STATUS_GENERAL_FAILURE;
        std::fclose( fp );
        fp = nullptr;

        auto const data = toml::parse( path_to_config_file );
        return st::OclProgramConfigStore_update_from_toml_table(
            *this, data );
    }

    st_status_t ocl_prg_config_store_type::update_from_string(
        std::string const& SIXTRL_RESTRICT_REF config_string ) {
        std::istringstream str2a( config_string );
        auto const data = toml::parse( str2a );
        return st::OclProgramConfigStore_update_from_toml_table(
            *this, data );
    }

    ocl_prg_config_item_type const* ocl_prg_config_store_type::find(
        ocl_prg_config_key_type const& SIXTRL_RESTRICT_REF key,
        bool const use_best_possible_match ,
        ocl_prg_config_store_type::config_source_type*
            SIXTRL_RESTRICT ptr_source ) const SIXTRL_NOEXCEPT
    {
        using config_src_t = ocl_prg_config_store_type::config_source_type;
        ocl_prg_config_item_type const* conf = nullptr;

        config_src_t config_src = ocl_prg_config_store_type::SOURCE_NOT_FOUND;

        if( key.is_legal() )
        {
            auto it = this->m_items.find( key );

            if( it != this->m_items.end() )
            {
                conf = &( it->second );
                config_src = ocl_prg_config_store_type::SOURCE_EXACT;
            }
        }

        if( ( conf == nullptr ) && ( use_best_possible_match ) )
        {
            conf = this->default_config_item( key.ctx_key );

            if( conf != nullptr )
                config_src = ocl_prg_config_store_type::SOURCE_CONTEXT;

            if( conf == nullptr )
            {
                ctx_key_type platform_key;
                platform_key.clear();
                platform_key.platform_id = key.ctx_key.platform_id;

                conf = this->default_config_item( platform_key );

                if( conf != nullptr )
                    config_src = ocl_prg_config_store_type::SOURCE_PLATFORM;
            }

            if( conf == nullptr )
            {
                conf = this->default_config_item( key.name, key.options );

                if( conf != nullptr )
                    config_src = ocl_prg_config_store_type::SOURCE_PROGRAM;
            }

            if( conf == nullptr )
            {
                conf = this->default_config_item();

                if( conf != nullptr )
                    config_src = ocl_prg_config_store_type::SOURCE_GLOBAL;
            }
        }

        if( ptr_source != nullptr ) *ptr_source = config_src;
        return conf;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    ocl_prg_config_item_type const*
    ocl_prg_config_store_type::default_config_item(
        ctx_key_type const& SIXTRL_RESTRICT_REF context_key ) const SIXTRL_NOEXCEPT
    {
        ocl_prg_config_item_type const* conf = nullptr;

        if( ( context_key.is_legal() ) ||
            ( ( context_key.platform_id != st::NodeId::ILLEGAL_PLATFORM_ID ) &&
              ( context_key.num_devices == st::size_type{ 0 } ) ) )
        {
            ocl_prg_config_key_type key;
            key.ctx_key = context_key;
            key.name.clear();
            key.options.clear();

            auto it = this->m_items.find( key );
            if( it != this->m_items.end() )
            {
                conf = &( it->second );
            }
        }

        return conf;
    }

    ocl_prg_config_item_type const*
    ocl_prg_config_store_type::default_config_item(
        std::string const& SIXTRL_RESTRICT_REF name,
        std::string const& SIXTRL_RESTRICT_REF options ) const SIXTRL_NOEXCEPT
    {
        ocl_prg_config_item_type const* conf = nullptr;

        if( !name.empty() )
        {
            ocl_prg_config_key_type key;
            key.ctx_key.clear();
            key.name = name;
            key.options.clear();

            auto it = this->m_items.find( key );
            if( it != this->m_items.end() )
            {
                conf = &( it->second );
            }
        }

        return conf;
    }


    ocl_prg_config_item_type const*
    ocl_prg_config_store_type::default_config_item() const SIXTRL_NOEXCEPT
    {
        ocl_prg_config_item_type const* conf = nullptr;

        ocl_prg_config_key_type key;
        key.ctx_key.clear();
        key.name.clear();
        key.options.clear();

        auto it = this->m_items.find( key );
        if( it != this->m_items.end() )
        {
            conf = &( it->second );
        }

        return conf;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t ocl_prg_config_store_type::update_config_item(
        ocl_prg_config_item_type const& SIXTRL_RESTRICT_REF item,
        ocl_prg_config_key_type const& SIXTRL_RESTRICT_REF key )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( key.is_legal() )
        {
            this->m_items.emplace( std::make_pair( key, item ) );
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    st_status_t ocl_prg_config_store_type::update_default_config_item(
        ocl_prg_config_item_type const& SIXTRL_RESTRICT_REF item,
        ctx_key_type const& SIXTRL_RESTRICT_REF context_key )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( context_key.is_legal() ) ||
            ( ( context_key.platform_id != st::NodeId::ILLEGAL_PLATFORM_ID ) &&
              ( context_key.num_devices == st::size_type{ 0 } ) ) )
        {
            ocl_prg_config_key_type key;
            key.clear();
            key.ctx_key = context_key;

            this->m_items.emplace( std::make_pair( key, item ) );
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    st_status_t ocl_prg_config_store_type::update_default_config_item(
        ocl_prg_config_item_type const& SIXTRL_RESTRICT_REF item,
        std::string const& SIXTRL_RESTRICT_REF name,
        std::string const& SIXTRL_RESTRICT_REF options )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( !name.empty() )
        {
            ocl_prg_config_key_type key;
            key.clear();
            key.name = name;
            key.options = options;

            this->m_items.emplace( std::make_pair( key, item ) );
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    st_status_t ocl_prg_config_store_type::update_default_config_item(
        ocl_prg_config_item_type const& SIXTRL_RESTRICT_REF item )
    {
        ocl_prg_config_key_type key;
        key.ctx_key.clear();
        key.name.clear();
        key.options.clear();

        this->m_items.emplace( std::make_pair( key, item ) );
        return st::STATUS_SUCCESS;
    }

    st_status_t OclProgramConfigItem_update_from_toml_table(
        st::OclProgramConfigItem& SIXTRL_RESTRICT_REF config_item,
        toml::value const& SIXTRL_RESTRICT_REF node_value )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        auto const& node = toml::get<toml::table>( node_value );
        ( void )node;

        if( ( node_value.contains( "compile_default_ipaths" ) ) &&
            ( node_value.at( "compile_default_ipaths" ).is_boolean() ) )
        {
            config_item.compile_default_ipaths = node_value.at(
                "compile_default_ipaths" ).as_boolean();

            status = st::STATUS_SUCCESS;
        }

        if( ( node_value.contains( "compile_flags" ) ) &&
            ( node_value.at( "compile_flags" ).is_array() ) )
        {
            config_item.compile_flags = toml::get< std::vector< std::string > >(
                toml::find( node_value, "compile_flags" ) );

            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    st_status_t OclProgramConfigStore_update_from_toml_table(
        st::OclProgramConfigStore& SIXTRL_RESTRICT_REF config_store,
        toml::value const& SIXTRL_RESTRICT_REF data )
    {
        st::status_type status = st::STATUS_SUCCESS;

        ocl_prg_config_item_type next_item;

        auto ocl_value = toml::find( data, "opencl" );
        auto const& ocl_table = toml::get<toml::table>( ocl_value );

        if( ( ocl_value.contains( "compile_default_ipaths" ) ) ||
            ( ocl_value.contains( "compile_flags" ) ) )
        {
            ocl_prg_config_item_type const* default_conf =
                config_store.default_config_item();

            if( default_conf != nullptr ) next_item = *default_conf;
            else next_item.clear();

            status = st::OclProgramConfigItem_update_from_toml_table(
                next_item, ocl_value );

            if( status == st::STATUS_SUCCESS )
            {
                status = config_store.update_default_config_item( next_item );
            }

            if( status != st::STATUS_SUCCESS ) return status;
        }

        std::vector< st::NodeId::platform_id_type > platforms;

        for( auto it = ocl_table.begin() ; it != ocl_table.end() ; ++it )
        {
            if( st::_string_is_integer( it->first ) )
            {
                if( ( !it->second.contains( "active" ) ) ||
                    ( it->second.at( "active" ).as_boolean() ) )
                {
                    platforms.push_back( std::stoi( it->first ) );
                }
            }
        }

        for( st::NodeId::platform_id_type platform_id : platforms )
        {
            std::ostringstream a2str;
            a2str << platform_id;

            auto it = ocl_table.find( a2str.str() );
            auto const& platform_val = it->second;

            if( ( platform_val.contains( "compile_default_ipaths" ) ) ||
                ( platform_val.contains( "compile_flags" ) ) )
            {
                ctx_key_type ctx_key;
                ctx_key.clear();
                ctx_key.platform_id = platform_id;

                ocl_prg_config_item_type const* default_conf =
                    config_store.default_config_item( ctx_key );

                if( default_conf != nullptr ) next_item = *default_conf;
                else next_item.clear();

                status = st::OclProgramConfigItem_update_from_toml_table(
                    next_item, platform_val );

                if( status == st::STATUS_SUCCESS )
                {
                    status = config_store.update_default_config_item(
                        next_item, ctx_key );
                }

                if( status != st::STATUS_SUCCESS ) return status;
            }
        }


        return status;
    }

    /* ********************************************************************* */

    constexpr store_type::class_id_type store_type::CLASS_ID;

    constexpr store_type::backend_id_type
    st::BackendObjTraits< store_type >::BACKEND_ID;

    constexpr store_type::class_id_type
    st::BackendObjTraits< store_type >::BASE_CLASS_ID;

    constexpr store_type::class_id_type
    st::BackendObjTraits< store_type >::DERIVED_CLASS_ID;

    /* --------------------------------------------------------------------- */

    store_type::~OclProgramStore()
    {
        this->m_key_to_id_map.clear();
    }

    st_prog_id_t store_type::program_id(
        st_key_t const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT
    {
        st_prog_id_t found_prog_id = store_type::ILLEGAL_PROGRAM_ID;

        if( key.is_legal() )
        {
            auto it = this->m_key_to_id_map.find( key );

            if( it != this->m_key_to_id_map.end() )
            {
                SIXTRL_ASSERT( this->_items_vector_size() <=
                               this->m_key_to_id_map.size() );

                if( static_cast< size_type >( it->second ) <
                    this->_items_vector_size() )
                {
                    found_prog_id = it->second;
                }
            }
        }

        return found_prog_id;
    }

    bool store_type::is_stored( st_key_t const& key ) const SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( this->_items_vector_size() <= this->m_key_to_id_map.size() );
        SIXTRL_ASSERT( this->num_stored_items() <= this->m_key_to_id_map.size() );

        bool is_stored = false;
        st_prog_id_t const prog_id = this->program_id( key );

        if( prog_id != base_store_type::ILLEGAL_PROGRAM_ID )
        {
            SIXTRL_ASSERT( key.is_legal() );
            is_stored = ( base_store_type::program_item( prog_id ) != nullptr );
        }

        return is_stored;
    }

    std::unique_ptr< base_prg_item_type > store_type::remove(
        st_key_t const& SIXTRL_RESTRICT_REF key ) {
        if( ( key.is_legal() ) && ( this->is_stored( key ) ) )
        {
            auto it = this->m_key_to_id_map.find( key );
            st_prog_id_t const stored_prog_id = this->program_id( key );

            SIXTRL_ASSERT( stored_prog_id != store_type::ILLEGAL_PROGRAM_ID );
            SIXTRL_ASSERT( it != this->m_key_to_id_map.end() );

            this->m_key_to_id_map.erase( it );
            return this->remove( stored_prog_id );
        }

        return std::unique_ptr< base_prg_item_type >( nullptr );
    }

    st_prog_id_t store_type::store( st_key_t const& key,
        std::unique_ptr< ocl_base_prg_item_type >&& prg_item_to_store )
    {
        st_prog_id_t stored_prog_id = base_store_type::ILLEGAL_PROGRAM_ID;

        if( key.is_legal() )
        {
            stored_prog_id = this->program_id( key );

            if( ( stored_prog_id != base_store_type::ILLEGAL_PROGRAM_ID ) &&
                ( prg_item_to_store.get() == nullptr ) &&
                ( this->program_item( stored_prog_id ) != nullptr ) )
            {
                auto it = this->m_key_to_id_map.find( key );
                SIXTRL_ASSERT( it != this->m_key_to_id_map.end() );
                SIXTRL_ASSERT( it->second == stored_prog_id );
                ( void )it;
                this->remove( stored_prog_id );
                stored_prog_id = base_store_type::ILLEGAL_PROGRAM_ID;
            }
            else if( ( stored_prog_id == base_store_type::ILLEGAL_PROGRAM_ID ) &&
                     ( prg_item_to_store.get() != nullptr ) )
            {
                st_prog_id_t const try_prog_id = this->_store_new_item(
                    std::move( prg_item_to_store ) );

                if( try_prog_id != base_store_type::ILLEGAL_PROGRAM_ID )
                {
                    SIXTRL_ASSERT( this->m_key_to_id_map.find( key ) ==
                                   this->m_key_to_id_map.end() );

                    auto ret = this->m_key_to_id_map.emplace(
                        std::make_pair( key, try_prog_id ) );

                    if( ret.second )
                    {
                        stored_prog_id = try_prog_id;
                    }
                }
            }
        }

        return stored_prog_id;
    }

    ocl_base_prg_item_type const* store_type::program_item(
        st_prog_id_t const id ) const {
        ocl_base_prg_item_type const* derived = nullptr;

        base_prg_item_type const* ptr = base_store_type::program_item( id );
        if( ptr == nullptr ) return derived;

        if( st::BackendObjBase_is_derived<
                item_base_type, ocl_rtc_prg_item_type >( *ptr ) )
        {
            derived = st::BackendObjBase_cast_to_derived< item_base_type,
                ocl_rtc_prg_item_type >( ptr );
        }

        return derived;
    }

    ocl_base_prg_item_type const* store_type::program_item(
        st_prog_id_t const id ) { return static_cast< store_type const& >(
            *this ).program_item( id ); }

    ocl_base_prg_item_type const* store_type::program_item(
        st_key_t const& key ) const { return this->program_item(
            this->program_id( key ) ); }

    ocl_base_prg_item_type* store_type::do_get_program_item(
        st_key_t const& key ) { return this->do_get_program_item(
            this->program_id( key ) ); }

    ocl_base_prg_item_type* store_type::do_get_program_item(
        program_id_type const id ) {
        ocl_base_prg_item_type* derived = nullptr;
        base_prg_item_type* ptr = base_store_type::do_get_program_item( id );

        if( ptr != nullptr ) return derived;
        if( st::BackendObjBase_is_derived<
                item_base_type, ocl_rtc_prg_item_type >( *ptr ) )
        {
            derived = st::BackendObjBase_cast_to_derived<
                base_prg_item_type, ocl_rtc_prg_item_type >( ptr );
        }

        return derived;
    }

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
