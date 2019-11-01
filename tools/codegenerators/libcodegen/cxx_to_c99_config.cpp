#include "libcodegen/cxx_to_c99_config.hpp"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <vector>
#include <sstream>
#include <string>
#include <stdexcept>
#include <utility>

#include "external/tomlc99/toml.h"
#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/internal/stl_buffer_helper.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;
namespace SIXTRL_CXX_NAMESPACE
{
namespace tools
{
    static std::string TOML_get_string_from_raw_string(
        char const* SIXTRL_RESTRICT raw_str,
        char const* SIXTRL_RESTRICT default_str = nullptr );

    static bool TOML_get_value_from_raw_string(
        char const* SIXTRL_RESTRICT raw_str, bool const default_value );

    static int64_t TOML_get_value_from_raw_string(
        char const* SIXTRL_RESTRICT raw_str, int64_t const default_value );

    static double TOML_get_value_from_raw_string(
        char const* SIXTRL_RESTRICT raw_str, double const default_value );

    static void TOML_get_string_array(
        std::vector< std::string >& SIXTRL_RESTRICT_REF str_array,
        ::toml_array_t* SIXTRL_RESTRICT array,
        bool const keep_empty_ones = false );

    static std::string TOML_join_string_array(
        std::vector< std::string >& SIXTRL_RESTRICT_REF str_array,
        std::string const& separator,
        bool const keep_empty_ones = false );

    static void TOML_get_map_types_field(
        std::map< std::string, std::string >& SIXTRL_RESTRICT_REF map_types,
        ::toml_array_t* SIXTRL_RESTRICT array );

    static void TOML_get_map_functions_field(
        std::vector< st::tools::FnMapping >& SIXTRL_RESTRICT_REF map_types,
        ::toml_array_t* SIXTRL_RESTRICT array );

    static void TOML_add_class_config(
        std::map< std::string, st::tools::CxxClassConfig >& SIXTRL_RESTRICT_REF
            class_config_map,
        std::map< std::string, std::vector< std::string > >* SIXTRL_RESTRICT
            ptr_class_configs_for_module,
        ::toml_table_t* SIXTRL_RESTRICT ptr_class_contents,
        char const* SIXTRL_RESTRICT in_class_name,
        std::string const& SIXTRL_RESTRICT_REF default_namespace,
        std::vector< std::string >& SIXTRL_RESTRICT_REF default_module,
        std::string const& SIXTRL_RESTRICT_REF default_module_str );


    /* ********************************************************************* */

    using _this_t = st::tools::CxxToC99Generator;

    CxxToC99Generator::CxxToC99Generator(
        char const* SIXTRL_RESTRICT path_to_config_file ) :
        m_class_configs(), m_global_class_configs(),
        m_class_configs_for_module()
    {
        _this_t::status_t status = this->add_config( path_to_config_file );
        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    CxxToC99Generator::CxxToC99Generator(
        std::string const& SIXTRL_RESTRICT_REF path_to_config_file ) :
        m_class_configs(), m_global_class_configs(),
        m_class_configs_for_module()
    {
        _this_t::status_t status = this->add_config( path_to_config_file );
        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    CxxToC99Generator::status_t CxxToC99Generator::add_config(
        std::string const& SIXTRL_RESTRICT_REF path_to_config_file )
    {
        return this->add_config( path_to_config_file.c_str() );
    }

    CxxToC99Generator::status_t CxxToC99Generator::add_config(
        char const* SIXTRL_RESTRICT path_to_config_file )
    {
        using fp_deleter_t = int (*)( ::FILE* );
        using conf_deleter_t = void (*)( ::toml_table_t* );

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( path_to_config_file == nullptr ) ||
            ( std::strlen( path_to_config_file ) == 0u ) )
        {
            return status;
        }

        std::unique_ptr< ::FILE, fp_deleter_t > fp(
            ::fopen( path_to_config_file, "r" ), &::fclose );

        if( fp.get() == nullptr ) return status;

        std::vector< char > error_msg( 256, '\0' );

        std::unique_ptr< ::toml_table_t, conf_deleter_t > ptr_config(
            ::toml_parse_file( fp.get(), error_msg.data(), error_msg.size() ),
                &::toml_free );

        if( ptr_config.get() == nullptr ) return status;
        fp.reset( nullptr );

        ::toml_table_t* ptr_global = ::toml_table_in(
            ptr_config.get(), "global" );

        ::toml_table_t* ptr_bindings = ::toml_table_in(
            ptr_config.get(), "cxx_to_c99_bindings" );

        if( ( ptr_bindings != nullptr ) && ( ptr_global != nullptr ) )
        {
            /* [global] */
            int const num_global_entries = ::toml_table_narr( ptr_global );

            std::string const default_namespace(
                st::tools::TOML_get_string_from_raw_string(
                    ::toml_raw_in( ptr_global, "namespace" ),
                        SIXTRL_CXX_NAMESPACE_STR ) );

            std::vector< std::string > default_module;

            st::tools::TOML_get_string_array(
                default_module, ::toml_array_in( ptr_global, "module" ) );

            if( default_module.empty() )
                default_module.push_back( "sixtracklib" );

            std::string const default_module_str(
                st::tools::TOML_join_string_array( default_module,
                    std::string{ "/" } ) );

            std::string global_class_config_name(
                st::tools::TOML_join_string_array( default_module,
                    std::string{ "::" } ) );

            global_class_config_name += "::*";

            st::tools::TOML_add_class_config( this->m_global_class_configs,
                nullptr, ptr_global, nullptr, default_namespace,
                    default_module, default_module_str );

            /* [[cxx_to_c99_bindings.*]] */
            status = st::ARCH_STATUS_SUCCESS;
            int const num_classes = ::toml_table_narr( ptr_bindings );

            for( int ii = int{ 0 } ; ii < num_classes ; ++ii )
            {
                char const* class_name = ::toml_key_in( ptr_bindings, ii );
                SIXTRL_ASSERT( class_name != nullptr );

                ::toml_array_t* ptr_class_tbl = ::toml_array_in(
                    ptr_bindings, class_name );

                SIXTRL_ASSERT( ptr_class_tbl != nullptr );
                SIXTRL_ASSERT( ::toml_array_kind( ptr_class_tbl ) == 't' );
                SIXTRL_ASSERT( ::toml_array_nelem( ptr_class_tbl ) == 1  );

                /* [[cxx_to_c99_bindings.class_name]] */
                ::toml_table_t* ptr_class_contents = ::toml_table_at(
                    ptr_class_tbl, 0 );
                SIXTRL_ASSERT( ptr_class_contents != nullptr );

                st::tools::TOML_add_class_config( this->m_class_configs,
                    &this->m_class_configs_for_module, ptr_class_contents,
                        class_name, default_namespace, default_module,
                            default_module_str );
            }
        }

        return status;
    }

    void CxxToC99Generator::clear()
    {
        this->m_class_configs.clear();
        this->m_global_class_configs.clear();
        this->m_class_configs_for_module.clear();
    }

    CxxClassConfig const& CxxToC99Generator::class_config(
        std::string const& class_name, std::string const& class_namespace) const
    {
        return this->class_config( class_name.c_str(),
                                   class_namespace.c_str() );
    }

    CxxClassConfig const& CxxToC99Generator::class_config(
        char const* SIXTRL_RESTRICT class_name,
        char const* SIXTRL_RESTRICT class_namespace ) const
    {
        std::string fq_class_name;

        if( class_namespace != nullptr )
        {
            fq_class_name = class_namespace;
        }
        else
        {
            fq_class_name = SIXTRL_CXX_NAMESPACE_STR;
        }

        SIXTRL_ASSERT( class_name != nullptr );

        fq_class_name += "::";
        fq_class_name += class_name;

        auto it = this->m_class_configs.find( fq_class_name );
        if( it == this->m_class_configs.end() )
        {
            std::string err_msg( "Unable to find class config for " );
            err_msg += fq_class_name;

            throw std::runtime_error( err_msg.c_str() );
        }

        return it->second;
    }

    CxxToC99Generator::status_t CxxToC99Generator::generate_bindings(
        CxxClassConfig const& SIXTRL_RESTRICT_REF cxx_class_config,
        std::ostringstream* SIXTRL_RESTRICT out_header_stream,
        std::ostringstream* SIXTRL_RESTRICT out_source_stream ) const
    {
        ( void )cxx_class_config;
        ( void )out_header_stream;
        ( void )out_source_stream;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* ******************************************************************** */

    std::string TOML_get_string_from_raw_string(
        char const* SIXTRL_RESTRICT raw_str,
        char const* SIXTRL_RESTRICT default_str )
    {
        std::string result;

        if( raw_str != nullptr )
        {
            char* temp_raw_str = nullptr;
            int const ret = ::toml_rtos( raw_str, &temp_raw_str );

            if( ret == 0 )
            {
                SIXTRL_ASSERT( temp_raw_str != nullptr );
                result = temp_raw_str;
            }

            free( temp_raw_str );
        }
        else if( default_str != nullptr )
        {
            result = default_str;
        }

        return result;
    }

    bool TOML_get_value_from_raw_string( char const* SIXTRL_RESTRICT raw_str,
            bool const default_value )
    {
        int temp_result = 0;

        if( ( raw_str != nullptr ) &&
            ( 0 == ::toml_rtob( raw_str, &temp_result ) ) )
        {
            return static_cast< bool >( temp_result );
        }

        return default_value;
    }

    int64_t TOML_get_value_from_raw_string( char const* SIXTRL_RESTRICT raw_str,
            int64_t const default_value )
    {
        int64_t result = default_value;

        if( ( raw_str != nullptr ) &&
            ( 0 == ::toml_rtoi( raw_str, &result ) ) )
        {
            result = default_value;
        }

        return result;
    }

    double TOML_get_value_from_raw_string( char const* SIXTRL_RESTRICT raw_str,
            double const default_value )
    {
        double result = default_value;

        if( ( raw_str != nullptr ) &&
            ( 0 == ::toml_rtod( raw_str, &result ) ) )
        {
            result = default_value;
        }

        return result;
    }

    void TOML_get_string_array(
        std::vector< std::string >& SIXTRL_RESTRICT_REF str_array,
        ::toml_array_t* SIXTRL_RESTRICT array, bool const keep_empty_ones )
    {
        str_array.clear();

        if( array != nullptr )
        {
            int const num_entries = ::toml_array_nelem( array );

            for( int ii = 0 ; ii < num_entries ; ++ii )
            {
                std::string str_elem( st::tools::TOML_get_string_from_raw_string(
                    ::toml_raw_at( array, ii ), nullptr ) );

                if( ( !str_elem.empty() ) || ( keep_empty_ones ) )
                {
                    str_array.emplace_back( std::move( str_elem ) );
                }
            }
        }
    }

    std::string TOML_join_string_array(
        std::vector< std::string >& SIXTRL_RESTRICT_REF str_array,
        std::string const& separator, bool const keep_empty_ones )
    {
        std::string result = std::string{};

        std::size_t const sep_length = separator.size();
        std::size_t num_pieces = std::size_t{ 0 };
        std::size_t required_capacity = std::size_t{ 0 };

        for( auto const& piece : str_array )
        {
            if( ( !piece.empty() ) || ( keep_empty_ones ) )
            {
                ++num_pieces;
                required_capacity += piece.size();
            }
        }

        if( num_pieces > std::size_t{ 0 } )
        {
            required_capacity += ( num_pieces ) * sep_length;
        }

        if( required_capacity > std::size_t{ 0 } )
        {
            result.clear();
            result.reserve( required_capacity + std::size_t{ 1 } );

            for( auto const& piece : str_array )
            {
                if( ( !piece.empty() ) || ( keep_empty_ones ) )
                {
                    if( !result.empty() )
                    {
                        result += separator;
                    }

                    result += piece;
                }
            }
        }

        return result;
    }

    void TOML_get_map_types_field(
        std::map< std::string, std::string >& SIXTRL_RESTRICT_REF map_types,
        ::toml_array_t* SIXTRL_RESTRICT array )
    {
        map_types.clear();

        if( array != nullptr )
        {
            int const num_mappings = ::toml_array_nelem( array );

            for( int ii = 0 ; ii < num_mappings ; ++ii )
            {
                ::toml_table_t* map_table = ::toml_table_at( array, ii );
                if( map_table == nullptr ) continue;

                std::string const in_type_str(
                    st::tools::TOML_get_string_from_raw_string(
                        ::toml_raw_in( map_table, "in" ), nullptr ) );

                if( in_type_str.empty() ) continue;
                if( st::Map_has_key( map_types, in_type_str ) ) continue;

                std::string const out_type_str(
                    st::tools::TOML_get_string_from_raw_string(
                        ::toml_raw_in( map_table, "out" ), nullptr ) );

                if( !out_type_str.empty() )
                {
                    map_types.emplace( std::make_pair(
                        in_type_str, out_type_str ) );
                }
            }
        }
    }

    void TOML_get_map_functions_field(
        std::map< std::string, st::tools::FnMapping >&
            SIXTRL_RESTRICT_REF map_fns,
        ::toml_array_t* SIXTRL_RESTRICT array )
    {
        map_fns.clear();

        if( array != nullptr )
        {
            int const num_mappings = ::toml_array_nelem( array );

            for( int ii = 0 ; ii < num_mappings ; ++ii )
            {
                ::toml_table_t* map_table = ::toml_table_at( array, ii );
                if( map_table == nullptr ) continue;

                std::string const in_fn_str(
                    st::tools::TOML_get_string_from_raw_string(
                        ::toml_raw_in( map_table, "in" ), nullptr ) );

                if( in_fn_str.empty() ) continue;
                if( st::Map_has_key( map_fns, in_fn_str ) ) continue;

                std::string const out_fn_str(
                    st::tools::TOML_get_string_from_raw_string(
                        ::toml_raw_in( map_table, "out" ), nullptr ) );

                if( out_fn_str.empty() ) continue;

                bool const is_regex = st::tools::TOML_get_value_from_raw_string(
                    ::toml_raw_in( map_table, "regex" ), false );

                std::vector< std::string > arg_types;
                st::tools::TOML_get_string_array( arg_types, ::toml_array_in(
                    map_table, "args" ) );

                map_fns.emplace( std::make_pair( in_fn_str,
                    st::tools::FnMapping{ std::move( arg_types ), out_fn_str,
                        is_regex } ) );
            }
        }
    }

    void TOML_add_class_config(
        std::map< std::string,
            st::tools::CxxClassConfig >& SIXTRL_RESTRICT_REF class_config_map,
        std::map< std::string, std::vector< std::string > >*
            ptr_class_configs_for_module,
        ::toml_table_t* SIXTRL_RESTRICT ptr_class_contents,
        char const* SIXTRL_RESTRICT in_class_name,
        std::string const& SIXTRL_RESTRICT_REF default_namespace,
        std::vector< std::string >& SIXTRL_RESTRICT_REF default_module,
        std::string const& SIXTRL_RESTRICT_REF default_module_str )
    {
        std::string const class_namespace(
            st::tools::TOML_get_string_from_raw_string(
                ::toml_raw_in( ptr_class_contents, "namespace" ),
                    default_namespace.c_str() ) );

        ::toml_array_t* class_module_arr = ::toml_array_in(
            ptr_class_contents, "module" );

        std::vector< std::string > class_module;
        std::string class_module_str;

        if( class_module_arr == nullptr )
        {
            class_module = default_module;
            class_module_str = default_module_str;
        }
        else
        {
            st::tools::TOML_get_string_array( class_module,
                class_module_arr );

            class_module_str = st::tools::TOML_join_string_array(
                class_module, std::string{ "/" } );
        }

        std::string class_name;
        std::string fq_class_name;

        if( ( in_class_name != nullptr ) &&
            ( std::strlen( in_class_name ) > std::size_t{ 0 } ) )
        {
            class_name    = in_class_name;
            fq_class_name = class_namespace;
            fq_class_name += "::";
            fq_class_name += in_class_name;
        }
        else
        {
            class_name    = "*";
            fq_class_name = st::tools::TOML_join_string_array(
                class_module, std::string{ "::" } );
            fq_class_name += "::*";
        }

        /* If we already have a config for this class, skip the rest */
        if( class_config_map.find( fq_class_name ) != class_config_map.end() )
        {
            return;
        }


        SIXTRL_ASSERT( ( ptr_class_configs_for_module == nullptr ) ||
            ( !st::Map_ordered_vec_has_value( *ptr_class_configs_for_module,
                class_module_str, fq_class_name) ) );

        auto ret = class_config_map.emplace( std::make_pair(
            fq_class_name, st::tools::CxxClassConfig{} ) );

        if( !ret.second ) return;
        st::tools::CxxClassConfig& class_config = ret.first->second;

        class_config.class_name = class_name;
        class_config.class_namespace = class_namespace;
        class_config.class_module = std::move( class_module );
        class_config.class_module_path = std::move( class_module_str );

        if( ( ptr_class_configs_for_module != nullptr ) &&
            ( st::Map_has_key( *ptr_class_configs_for_module,
                               class_module_str ) ) )
        {
            if( st::ARCH_STATUS_SUCCESS !=
                st::Map_ordered_vec_insert_value( *ptr_class_configs_for_module,
                    class_module_str, fq_class_name, std::string{}, true ) )
            {
                return;
            }
        }
        else if( ptr_class_configs_for_module != nullptr )
        {
            auto ret2 = ptr_class_configs_for_module->emplace( std::make_pair(
                class_module_str, std::vector< std::string >{ fq_class_name } ) );

            if( !ret2.second ) return;
        }

        SIXTRL_ASSERT( ( ptr_class_configs_for_module == nullptr ) ||
            ( st::Map_ordered_vec_has_value( *ptr_class_configs_for_module,
                    class_module_str, fq_class_name ) ) );

        /* Check whether there is an override for the output class name */
        char const* out_class_name_raw = ::toml_raw_in(
            ptr_class_contents, "out_class_name" );

        if( out_class_name_raw != nullptr )
        {
            class_config.out_class_name =
            st::tools::TOML_get_string_from_raw_string(
                out_class_name_raw, nullptr );
        }

        if( class_config.out_class_name.empty() )
        {
            class_config.out_class_name = "NS(";
            class_config.out_class_name += class_name;
            class_config.out_class_name += ")";
        }

        /* add optional exclude_types, if available */
        st::tools::TOML_get_string_array( class_config.exclude_types,
            ::toml_array_in( ptr_class_contents, "exclude_types" ) );

        /* add optional exclude_types, if available */
        st::tools::TOML_get_string_array( class_config.exclude_functions,
            ::toml_array_in( ptr_class_contents, "exclude_functions" ) );

        /* add_optional map_types, if available */
        st::tools::TOML_get_map_types_field( class_config.map_types,
            ::toml_array_in( ptr_class_contents, "map_types" ) );

        /* add_optional map_functions, if available */
        st::tools::TOML_get_map_functions_field(
            class_config.map_functions, ::toml_array_in(
                ptr_class_contents, "map_functions" ) );
    }
}
}

/* end: tools/codegenerators/libcodegen/cxx_to_c99_config.cpp */
