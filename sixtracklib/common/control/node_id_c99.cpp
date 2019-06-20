#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/common/control/node_id.hpp"

#include <string>
#include <cstring>

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(arch_status_t) NS(NodeId_extract_node_id_str_from_config_str)(
    char* SIXTRL_RESTRICT node_id_str,
    ::NS(arch_size_t) const node_id_str_capacity,
    char const* SIXTRL_RESTRICT config_str )
{
    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    if( ( node_id_str != nullptr ) &&
        ( node_id_str_capacity > ::NS(arch_size_t){ 2 } ) )
    {
        std::memset( node_id_str, static_cast< int >( '\0' ),
                     node_id_str_capacity );

        std::string const temp_node_id_str =
            st::NodeId_extract_node_id_str_from_config_str( config_str );

        if( ( !temp_node_id_str.empty() ) &&
            (  temp_node_id_str.size() <= node_id_str_capacity ) )
        {
            std::strncpy( node_id_str, temp_node_id_str.c_str(),
                          node_id_str_capacity - ::NS(arch_size_t){ 1 }  );

            status = st::ARCH_STATUS_SUCCESS;
        }
    }

    return status;
}

/* end: sixtracklib/common/control/node_id_c99.cpp */
