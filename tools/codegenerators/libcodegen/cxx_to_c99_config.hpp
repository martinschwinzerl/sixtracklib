#ifndef SIXTRACKLIB_TOOLS_CODEGENERATOR_LIBCODEGEN_CXX_TO_C99_CONFIG_CXX_HPP__
#define SIXTRACKLIB_TOOLS_CODEGENERATOR_LIBCODEGEN_CXX_TO_C99_CONFIG_CXX_HPP__

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <string>

#include "external/tomlc99/toml.h"
#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/internal/stl_buffer_helper.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace tools
{
    struct FnMapping
    {
        std::vector< std::string > args;
        std::string out;
        bool is_regex;
    };

    struct CxxClassConfig
    {
        std::map< std::string, std::string >  map_types;
        std::map< std::string, FnMapping >    map_functions;
        std::vector< std::string >            exclude_types;
        std::vector< std::string >            exclude_functions;
        std::vector< std::string >            class_module;

        std::string class_name;
        std::string class_namespace;
        std::string class_module_path;
        std::string in_file;
        std::string out_class_name;
    };

    class CxxToC99Generator
    {
        public:

        using status_t = ::NS(arch_status_t);

        CxxToC99Generator(
            char const* SIXTRL_RESTRICT path_to_config_file = nullptr );

        CxxToC99Generator(
            std::string const& SIXTRL_RESTRICT_REF path_to_config_file );

        CxxToC99Generator( CxxToC99Generator const& other ) = default;
        CxxToC99Generator( CxxToC99Generator&& other ) = default;

        CxxToC99Generator& operator=( CxxToC99Generator const& rhs ) = default;
        CxxToC99Generator& operator=( CxxToC99Generator&& rhs ) = default;

        virtual ~CxxToC99Generator() = default;

        status_t add_config(
            std::string const& SIXTRL_RESTRICT_REF path_to_config_file );

        status_t add_config(
            char const* SIXTRL_RESTRICT path_to_config_file );

        void clear();

        CxxClassConfig const& class_config(
            std::string const& class_name,
            std::string const& class_namespace =
                std::string{ SIXTRL_CXX_NAMESPACE_STR} ) const;

        CxxClassConfig const& class_config(
            char const* SIXTRL_RESTRICT class_name,
            char const* SIXTRL_RESTRICT class_namespace = nullptr ) const;

        status_t generate_bindings(
            CxxClassConfig const& SIXTRL_RESTRICT_REF cxx_class_config,
            std::ostringstream* SIXTRL_RESTRICT out_header_stream,
            std::ostringstream* SIXTRL_RESTRICT out_source_stream ) const;

        private:

        std::map< std::string, CxxClassConfig >
            m_class_configs;

        std::map< std::string, CxxClassConfig >
            m_global_class_configs;

        std::map< std::string, std::vector< std::string > >
            m_class_configs_for_module;
    };

}
}

#endif /* SIXTRACKLIB_TOOLS_CODEGENERATOR_LIBCODEGEN_CXX_TO_C99_CONFIG_CXX_HPP__ */
/* end: tools/codegenerators/libcodegen/cxx_to_c99_config.hpp */

