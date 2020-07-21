#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/cuda/control/program_code.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <sstream>

namespace
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using program_defs_t = st::ProgramCodeDefinitions;
    using program_code_t = st::BaseProgramCode;
    using st_size_t = program_defs_t::size_type;
    using st_status_t = program_defs_t::status_t;
}

namespace SIXTRL_CXX_NAMESPACE
{
    program_defs_t::ProgramCodeDefinitions() :
        m_definitions_map(), m_definition_keys()
    {

    }

    program_defs_t::ProgramCodeDefinitions(
        std::string const* SIXTRL_RESTRICT keys_it,
        std::string const* SIXTRL_RESTRICT values_it,
        st_size_t const num_definions ) :
        m_definitions_map(), m_definition_keys()
    {
        st_status_t status = st::ARCH_STATUS_SUCCESS;
        std::string const* keys_end = keys_it;

        SIXTRL_ASSERT(
            ( ( keys_it != nullptr ) && ( values_it != nullptr ) ) ||
            ( ( keys_it == nullptr ) && ( values_it == nullptr ) ) );

        if( ( keys_end != nullptr ) && ( num_definions > st_size_t{ 0 } ) )
        {
            std::advance( keys_end, num_definions );
            for( ; keys_it != keys_end; ++keys_it, ++values_it )
            {
                if( keys_it->empty() ) continue;
                auto it = this->m_definitions_map.find( *keys_it );

                if( it == this->m_definitions_map.end() )
                {
                    status |= this->do_add_definition_base_impl(
                        *keys_it, *values_it );
                }
                else
                {
                    it->second = *values_it;
                }

                SIXTRL_ASSERT( this->has_definition_by_key( *keys_it ) );
                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( this->m_definitions_map.size() ==
                      this->m_definition_keys.size() ) );
            }

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        SIXTRL_ASSERT( this->m_definition_keys.size() <= num_definions );
        SIXTRL_ASSERT( this->m_definition_keys.size() ==
                       this->m_definitions_map.size() );
    }

    program_defs_t::ProgramCodeDefinitions(
        char const* const* SIXTRL_RESTRICT keys_it,
        char const* const* SIXTRL_RESTRICT values_it,
        st_size_t const num_definions )
    {
        st_status_t status = st::ARCH_STATUS_SUCCESS;
        char const* const* keys_end = keys_it;

        SIXTRL_ASSERT(
            ( ( keys_it != nullptr ) && ( values_it != nullptr ) ) ||
            ( ( keys_it == nullptr ) && ( values_it == nullptr ) ) );

        if( ( keys_end != nullptr ) && ( num_definions > st_size_t{ 0 } ) )
        {
            std::advance( keys_end, num_definions );
            for( ; keys_it != keys_end; ++keys_it, ++values_it )
            {
                if( ( *keys_it ) == nullptr ) continue;
                auto it = this->m_definitions_map.find( *keys_it );

                if( it == this->m_definitions_map.end() )
                {
                    status |= this->do_add_definition_base_impl(
                        *keys_it, *values_it );
                }
                else
                {
                    it->second = *values_it;
                }

                SIXTRL_ASSERT( this->has_definition_by_key( *keys_it ) );
                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( this->m_definitions_map.size() ==
                      this->m_definition_keys.size() ) );
            }

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        SIXTRL_ASSERT( this->m_definition_keys.size() <= num_definions );
        SIXTRL_ASSERT( this->m_definition_keys.size() ==
                       this->m_definitions_map.size() );
    }

    st_size_t program_defs_t::num_definions() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_definition_keys.size() ==
                       this->m_definitions_map.size() );

        return this->m_definition_keys.size();
    }

    std::string const&
    program_defs_t::definition_key_str( st_size_t const idx ) const
    {
        SIXTRL_ASSERT( this->m_definition_keys.size() ==
                       this->m_definitions_map.size() );

        return this->m_definition_keys.at( idx );
    }

    st_size_t program_defs_t::definition_key_index(
        std::string const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT
    {
        st_size_t idx = std::numeric_limits< st_size_t >::max();

        SIXTRL_ASSERT( this->m_definition_keys.size() ==
                       this->m_definitions_map.size() );

        if( !key.empty() )
        {
            auto it = std::find( this->m_definition_keys.begin(),
                                 this->m_definition_keys.end(), key );

            if( it == this->m_definition_keys.end() )
            {
                idx = static_cast< st_size_t >( std::distance(
                    this->m_definition_keys.begin(), it ) );
            }
        }

        return idx;
    }

    char const* program_defs_t::definition_key(
        st_size_t const idx ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_definition_keys.size() ==
                       this->m_definitions_map.size() );

        return ( idx < this->m_definition_keys.size() )
            ? this->m_definition_keys[ idx ].c_str() : nullptr;
    }

    bool program_defs_t::has_definition_by_key(
        std::string const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT
    {
        bool has_def_key = false;

        if( key.empty() )
        {
            SIXTRL_ASSERT( this->m_definition_keys.size() ==
                           this->m_definitions_map.size() );

            auto it = this->m_definitions_map.find( key );
            has_def_key = ( it != this->m_definitions_map.end() );

            SIXTRL_ASSERT( ( !has_def_key ) ||
                ( this->definition_key_index( key ) <
                  this->m_definition_keys.size() ) );
        }

        return has_def_key;
    }

    std::string const& program_defs_t::definition_by_key_str(
        std::string const& SIXTRL_RESTRICT_REF key ) const
    {
        if( key.empty() )
        {
            throw std::runtime_error( "illegal key" );
        }

        SIXTRL_ASSERT( this->m_definition_keys.size() ==
                       this->m_definitions_map.size() );

        auto it = this->m_definitions_map.find( key );

        if( it == this->m_definitions_map.end() )
        {
            throw std::runtime_error( "key not found" );
        }

        return it->second;
    }

    char const* program_defs_t::definition_by_key(
        std::string const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT
    {
        return this->definition_by_key_str( key ).c_str();
    }

    std::string const& program_defs_t::definition_str(
        st_size_t const idx ) const
    {
        return this->definition_by_key_str( this->definition_key( idx ) );
    }

    char const* program_defs_t::definition(
        st_size_t const idx ) const SIXTRL_NOEXCEPT
    {
        return this->definition_by_key_str(
            this->definition_key( idx ) ).c_str();
    }

    void program_defs_t::set_definition_by_key(
        std::string const& SIXTRL_RESTRICT_REF key,
        std::string const& SIXTRL_RESTRICT_REF definition )
    {
        if( key.empty() )
        {
            throw std::runtime_error( "illegal key" );
        }

        SIXTRL_ASSERT( this->m_definition_keys.size() ==
                       this->m_definitions_map.size() );

        auto it = this->m_definitions_map.find( key );

        if( it != this->m_definitions_map.end() )
        {
            it->second = definition;
        }
        else
        {
            st_status_t const status = this->do_add_definition(
                key, definition );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }
    }

    void program_defs_t::remove_definition_by_key(
        std::string const& SIXTRL_RESTRICT_REF key ) SIXTRL_NOEXCEPT
    {
        if( this->has_definition_by_key( key ) )
        {
            st_status_t const status = this->do_remove_definition(
                this->definition_key_index( key ) );
            ( void )status;
        }
    }

    void program_defs_t::remove_definition(
        st_size_t const idx ) SIXTRL_NOEXCEPT
    {
        this->remove_definition_by_key( this->definition_key( idx ) );
    }

    std::string const*
    program_defs_t::definition_keys_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_definition_keys.size() ==
                       this->m_definitions_map.size() );

        return this->m_definition_keys.data();
    }

    std::string const*
    program_defs_t::definition_keys_end() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_definition_keys.size() ==
                       this->m_definitions_map.size() );

        auto keys_end = this->m_definition_keys.data();

        if( keys_end != nullptr )
        {
            std::advance( keys_end, this->m_definition_keys.size() );
        }

        return keys_end;
    }

    program_defs_t::const_iterator
    program_defs_t::definitions_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_definition_keys.size() ==
                       this->m_definitions_map.size() );

        return this->m_definitions_map.begin();
    }

    program_defs_t::const_iterator
    program_defs_t::definitions_end() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_definition_keys.size() ==
                       this->m_definitions_map.size() );

        return this->m_definitions_map.end();
    }

    st_status_t program_defs_t::update(
        std::string const* SIXTRL_RESTRICT keys_begin,
        std::string const* SIXTRL_RESTRICT values_begin,
        st_size_t const num_definions )
    {
        std::string const* keys_end = keys_begin;
        if( keys_end != nullptr ) std::advance( keys_end, num_definions );
        return this->update( keys_begin, keys_end, values_begin );
    }

    st_status_t program_defs_t::update(
        char const* const* SIXTRL_RESTRICT keys_it,
        char const* const* SIXTRL_RESTRICT values_it,
        st_size_t const num_definions )
    {
        char const* const* keys_end = keys_it;
        if( keys_end != nullptr ) std::advance( keys_end, num_definions );
        return this->update( keys_it, keys_end, values_it );
    }

    void program_defs_t::clear()
    {
        this->do_clear();
    }

    st_status_t program_defs_t::do_add_definition(
        std::string const& SIXTRL_RESTRICT_REF key,
        std::string const& SIXTRL_RESTRICT_REF definition )
    {
        return this->do_add_definition_base_impl( key, definition );
    }

    st_status_t program_defs_t::do_remove_definition( st_size_t const idx )
    {
        return this->do_remove_definition_base_impl( idx );
    }

    void program_defs_t::do_clear()
    {
        this->m_definition_keys.clear();
        this->m_definitions_map.clear();
    }

    st_status_t program_defs_t::do_add_definition_base_impl(
        std::string const& SIXTRL_RESTRICT key,
        std::string const& SIXTRL_RESTRICT definition )
    {
        st_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !key.empty() )
        {
            SIXTRL_ASSERT( this->m_definitions_map.size() ==
                           this->m_definition_keys.size() );

            auto map_it = this->m_definitions_map.find( key );
            if( map_it == this->m_definitions_map.end() )
            {
                SIXTRL_ASSERT( std::find( this->m_definition_keys.begin(),
                    this->m_definition_keys.end(), key ) ==
                        this->m_definition_keys.end() );

                auto ret = this->m_definitions_map.emplace(
                    std::make_pair( key, definition ) );

                if( ret.second )
                {
                    this->m_definition_keys.push_back( key );
                    status = st::ARCH_STATUS_SUCCESS;
                }

                SIXTRL_ASSERT( this->m_definition_keys.size() ==
                               this->m_definitions_map.size() );
            }
        }

        return status;
    }

    st_status_t program_defs_t::do_remove_definition_base_impl(
        st_size_t const idx ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( idx < this->m_definition_keys.size() )
        {
            std::string const& key = this->m_definition_keys[ idx ];

            SIXTRL_ASSERT( this->m_definition_keys.size() ==
                           this->m_definitions_map.size() );

            auto map_it = this->m_definitions_map.find( key );
            auto key_it = std::find( this->m_definition_keys.begin(),
                                     this->m_definition_keys.end(), key );

            SIXTRL_ASSERT(
                ( ( map_it != this->m_definitions_map.end() ) &&
                  ( key_it != this->m_definition_keys.end() ) ) ||
                ( ( map_it == this->m_definitions_map.end() ) &&
                  ( key_it == this->m_definition_keys.end() ) ) );

            if( ( map_it != this->m_definitions_map.end() ) &&
                ( key_it != this->m_definition_keys.end() ) )
            {
                this->m_definitions_map.erase( map_it );
                this->m_definition_keys.erase( key_it );

                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    st_status_t ProgramCodeDefinitions_to_c_code_block(
        std::ostream& SIXTRL_RESTRICT_REF ostr,
        ProgramCodeDefinitions const& SIXTRL_RESTRICT_REF program_code_defs,
        st_size_t const ident_per_level, st_size_t const level )
    {
        std::ostringstream temp;
        st_size_t const level_indent = level * ident_per_level;

        if( level_indent > st_size_t{ 0 } )
            temp << std::setw( level_indent ) << " ";
        std::string const indent_top_level = temp.str();

        temp.str( "" );
        if( ( level_indent + level ) > st_size_t{ 0 } )
            temp << std::setw( level_indent + level ) << " ";

        auto begin = program_code_defs.definitions_begin();
        auto end = program_code_defs.definitions_end();

        for( auto it = begin ; it != end ; ++it )
        {
            if( it != begin ) ostr << indent_top_level << "\r\n";
            ostr << indent_top_level
                 << "#if !defined( " << it->first << " )\r\n" << temp.str()
                 << "#define " << it->first << " " << it->second << "\r\n"
                 << indent_top_level
                 << "#endif /* !defined( " << it->first << " )\r\n";
        }

        return st::ARCH_STATUS_SUCCESS;
    }

    /* ********************************************************************* */

    program_code_t::definitions_t const*
    program_code_t::definitions() const SIXTRL_NOEXCEPT
    {
        return this->m_stored_definitions.get();
    }

    program_code_t::definitions_t*
    program_code_t::definitions() SIXTRL_NOEXCEPT
    {
        return this->m_stored_definitions.get();
    }

    std::string const& program_code_t::code_str() const
    {
        return this->m_code;
    }

    char const* program_code_t::code() const SIXTRL_NOEXCEPT
    {
        return this->m_code.c_str();
    }

    st_status_t program_code_t::set_code(
        std::string const& SIXTRL_RESTRICT_REF input_str,
        program_code_t::source_origin_t const source )
    {
        st_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( source == program_code_t::FROM_STRING )
        {
            this->m_code = input_str;
            status = st::ARCH_STATUS_SUCCESS;
        }
        else if( source == program_code_t::FROM_SOURCE_FILE )
        {
            if( input_str.empty() )
            {
                throw std::runtime_error( "empty path to file" );
            }

            std::fstream program_file( input_str, std::ios::in );

            if( program_file.is_open() )
            {
                std::string const source_code(
                    ( std::istreambuf_iterator< char >( program_file ) ),
                      std::istreambuf_iterator< char >() );

                if( !source_code.empty() )
                {
                    this->m_code = source_code;
                    this->m_full_path_to_file = input_str;
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    st_status_t program_code_t::set_code_from_file(
        std::string const& SIXTRL_RESTRICT_REF full_path_to_file )
    {
        return this->set_code(
            full_path_to_file, program_code_t::FROM_SOURCE_FILE );
    }

    bool program_code_t::is_from_file() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_full_path_to_file.empty() );
    }

    std::string const&
    program_code_t::full_path_to_file_str() const SIXTRL_NOEXCEPT
    {
        return this->m_full_path_to_file;
    }

    char const* program_code_t::full_path_to_file() const SIXTRL_NOEXCEPT
    {
        return this->m_full_path_to_file.c_str();
    }

    void program_code_t::clear()
    {
        return this->do_clear();
    }

    void program_code_t::do_clear()
    {
        this->m_code.clear();
        this->m_full_path_to_file.clear();

        if( this->m_stored_definitions.get() != nullptr )
        {
            this->m_stored_definitions->clear();
        }
    }

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */
