#include "sixtracklib/common/control/node_id.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <regex>
#include <utility>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/control_base.hpp"
#include "sixtracklib/common/control/node_id.h"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    std::string NodeId_extract_node_id_str_from_config_str(
        char const* SIXTRL_RESTRICT config_str )
    {
        /* std::regex re( "device_id_str[:blank:]*=[:blank:]*"
                "([:digit:]+.[:digit:]+)[A-Za-z0-9_\\-#=:;., \t]*|"
                "^[A-Za-z0-9_\\-#=;.:, \t]*([:digit:]+.[:digit:]+);|"
                "([:digit:]+.[:digit:]+)" ); */

        std::regex re( "\\s*([0-9]+\\.[0-9]+)[\\sA-Za-z0-9#\\;]*" );
        std::regex_match( config_str, matches, re );

        if( ( matches.ready() ) && ( !matches.empty() ) )
        {
            return std::string{ matches[ matches.size() - 1 ] };

        }

        return std::string{ "" };
    }
}

/* end: sixtracklib/common/control/node_id.cpp */
