#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/node/tools.h"
    #include "sixtracklib/base/node/node_id.h"
    #include "sixtracklib/base/architecture/architectures_store.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <string>
        #include <regex>
    #else
        #include <stdbool.h>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        constexpr char NODE_ID_STR_FORMAT_NOARCH_REGEX[] =
            "([0-9]+)\\.([0-9]+)";

        constexpr char NODE_ID_STR_FORMAT_ARCHID_REGEX[] =
            "([0-9]+)\\:([0-9]+)\\.([0:9]+)";

        constexpr char NODE_ID_STR_FORMAT_ARCHSTR_REGEX[] =
            "([a-z0-9\\_]+)\\:([0-9]+)\\.([0:9]+)";

        constexpr char NODE_DEVICE_STR_KIND_PCI_BUS_ID_REGEX[] =
            "([0-9a-fA-F]{1,8})\\:([0-9a-fA-F]{2})\\:([0-9a-fA-F]{2})\\.([0-9]{1})";

        constexpr char NODE_DEVICE_STR_KIND_UUID_REGEX[] =
            "([0-9a-fA-F]{8})-([0-9a-fA-F]{4})-([1-5])([0-9a-fA-F]{3})-"
            "([0-9a-fA-F]{4})-([0-9a-fA-F]{12})";
    }

    bool Node_is_device_str_kind_a_node_id_format(
        node_device_str_kind_t const kind ) SIXTRL_NOEXCEPT {
        bool is_a_node_id_format = false;

        switch( kind )
        {
            case st::NODE_DEVICE_STRING_KIND_NOARCH:
            case st::NODE_DEVICE_STRING_KIND_ARCHID:
            case st::NODE_DEVICE_STRING_KIND_ARCHSTR:
            {
                is_a_node_id_format = true;
                break;
            }

            default:
            {
                is_a_node_id_format = false;
            }
        };

        return is_a_node_id_format;
    }

    bool Node_is_node_id_format_device_str_kind(
        node_id_str_fmt_t const format ) SIXTRL_NOEXCEPT {
        bool is_a_device_str_kind = false;

        switch( format )
        {
            case st::NODE_ID_STR_FORMAT_NOARCH:
            case st::NODE_ID_STR_FORMAT_ARCHID:
            case st::NODE_ID_STR_FORMAT_ARCHSTR:
            {
                is_a_device_str_kind = true;
                break;
            }

            default:
            {
                is_a_device_str_kind = false;
            }
        };

        return is_a_device_str_kind;
    }

    node_id_str_fmt_t Node_convert_device_str_kind_to_node_id_format(
        node_device_str_kind_t const kind ) SIXTRL_NOEXCEPT
    {
        node_id_str_fmt_t node_id_format = st::NODE_ID_STR_FORMAT_ILLEGAL;

        switch( kind )
        {
            case st::NODE_DEVICE_STRING_KIND_NOARCH:
            case st::NODE_DEVICE_STRING_KIND_ARCHID:
            case st::NODE_DEVICE_STRING_KIND_ARCHSTR:
            {
                node_id_format = static_cast< node_id_str_fmt_t >( kind );
                break;
            }

            default:
            {
                node_id_format = st::NODE_ID_STR_FORMAT_ILLEGAL;
            }
        };

        return node_id_format;
    }

    node_device_str_kind_t Node_convert_node_id_format_to_device_str_kind(
        node_id_str_fmt_t const format ) SIXTRL_NOEXCEPT
    {
        node_device_str_kind_t device_str_kind =
            st::NODE_DEVICE_STRING_KIND_ILLEGAL;

        switch( format )
        {
            case st::NODE_ID_STR_FORMAT_NOARCH:
            case st::NODE_ID_STR_FORMAT_ARCHID:
            case st::NODE_ID_STR_FORMAT_ARCHSTR:
            {
                device_str_kind = static_cast< node_device_str_kind_t >( format );
                break;
            }

            default:
            {
                device_str_kind = st::NODE_DEVICE_STRING_KIND_ILLEGAL;
            }
        };

        return device_str_kind;
    }

     /* --------------------------------------------------------------------- */

    bool Node_id_format_is_noarch( std::string const&
        SIXTRL_RESTRICT_REF node_id_str )
    {
        return ( ( !node_id_str.empty() ) &&
                 ( std::regex_match( node_id_str.c_str(),
                    std::regex{ st::NODE_ID_STR_FORMAT_NOARCH_REGEX } ) ) );
    }


    bool Node_id_format_is_archid(
        std::string const& SIXTRL_RESTRICT_REF node_id_str )
    {
        return ( ( !node_id_str.empty() ) &&
                 ( std::regex_match( node_id_str.c_str(),
                    std::regex{ st::NODE_ID_STR_FORMAT_ARCHID } ) ) );
    }


    bool Node_id_format_is_archstr(
        std::string const& SIXTRL_RESTRICT_REF node_id_str )
    {
        return ( ( !node_id_str.empty() ) &&
                 ( std::regex_match( node_id_str.c_str(),
                    std::regex{ st::NODE_ID_STR_FORMAT_ARCHSTR } ) ) );
    }

    node_id_str_fmt_t Node_find_node_id_format(
        std::string const& SIXTRL_RESTRICT_REF node_id_str )
    {
        if( st::Node_id_format_is_archid( node_id_str ) )
        {
            return st::NODE_ID_STR_FORMAT_ARCHID;
        }
        else if( st::Node_id_format_is_archstr( node_id_str ) )
        {
            return st::NODE_ID_STR_FORMAT_ARCHSTR;
        }
        else if( st::Node_id_format_is_noarch( node_id_str ) )
        {
            return st::NODE_ID_STR_FORMAT_NOARCH;
        }

        return st::NODE_ID_STR_FORMAT_ILLEGAL;
    }

    /* --------------------------------------------------------------------- */

    ::NS(status_t) NS(NodeId_parse)( ::NS(NodeId)* SIXTRL_RESTRICT node_id,
        char const* SIXTRL_RESTRICT node_id_str )
    {
        return ( node_id != nullptr )
            ? st::NodeId_parse_using_format( *node_id, node_id_str,
                st::Node_find_node_id_format( node_id_str ) )
            : st::STATUS_GENERAL_FAILURE;
    }

    ::NS(status_t) NS(NodeId_parse_using_format)(
        ::NS(NodeId)* SIXTRL_RESTRICT node_id,
        char const* SIXTRL_RESTRICT node_id_str,
        ::NS(node_id_str_fmt_t) const format )
    {
        ::NS(status_t) status = st::STATUS_GENERAL_FAILURE;

        if( ( node_id != nullptr ) && ( node_id_str != nullptr ) &&
            ( std::strlen( node_id_str ) > ::NS(size_t){ 0 } ) &&
            ( format != st::NODE_ID_STR_FORMAT_ILLEGAL ) )
        {
            std::smatch match_results;
            std::string const temp_node_id_str( node_id_str );

            if( format == st::NODE_ID_STR_FORMAT_NOARCH )
            {
                if( ( std::regex_match( temp_node_id_str, match_results,
                      std::regex{ st::NODE_ID_STR_FORMAT_NOARCH} ) ) &&
                    ( match_results.size() == 3u ) )
                {
                    std::string const platform_id_str( match_results[ 1 ] );
                    std::string const device_id_str( match_results[ 2 ] );

                    node_id->m_arch_id = st::ARCHITECTURE_UNDEFINED;
                    node_id->m_platform_id = std::atoi( platform_id_str.c_str() );
                    node_id->m_device_id = std::atoi( device_id_str.c_str() );
                    status = st::STATUS_SUCCESS;
                }
            }
            else if( format == st::NODE_ID_STR_FORMAT_ARCHID )
            {
                if( ( std::regex_match( temp_node_id_str, match_results,
                      std::regex{ st::NODE_ID_STR_FORMAT_ARCHID} ) ) &&
                    ( match_results.size() == 4u ) )
                {
                    std::string const arch_id_str( match_results[ 1 ] );

                    st::arch_id_t const arch_id = std::atoi( arch_id_str.c_str() );
                    if( st::ArchitecturesStore_const_global().has_architecture(
                        arch_id ) )
                    {
                        std::string const platform_id_str( match_results[ 2 ] );
                        std::string const device_id_str( match_results[ 3 ] );

                        node_id->m_arch_id = arch_id;
                        node_id->m_platform_id = std::atoi( platform_id_str.c_str() );
                        node_id->m_device_id = std::atoi( device_id_str.c_str() );
                        status = st::STATUS_SUCCESS;
                    }
                }
            }
            else if( format == st::NODE_ID_STR_FORMAT_ARCHSTR )
            {
                if( ( std::regex_match( temp_node_id_str, match_results,
                      std::regex{ st::NODE_ID_STR_FORMAT_ARCHID} ) ) &&
                    ( match_results.size() == 4u ) )
                {
                    std::string const arch_str( match_results[ 1 ] );

                    if( st::ArchitecturesStore_const_global(
                        ).has_architecture_by_str( arch_str ) )
                    {
                        auto const arch_id = st::ArchitecturesStore_const_global(
                            ).arch_id_by_str( arch_str );

                        if( ( arch_id != st::ARCHITECTURE_ILLEGAL ) ||
                            ( arch_id != st::ARCHITECTURE_UNDEFINED ) )
                        {
                            std::string const platform_id_str( match_results[ 2 ] );
                            std::string const device_id_str( match_results[ 3 ] );

                            node_id->m_arch_id = arch_id;
                            node_id->m_platform_id = std::atoi( platform_id_str.c_str() );
                            node_id->m_device_id = std::atoi( device_id_str.c_str() );
                            status = st::STATUS_SUCCESS;
                        }
                    }
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool Node_device_str_is_noarch(
        std::string const& SIXTRL_RESTRICT_REF device_str )
    {
        return st::Node_id_format_is_noarch( device_str );
    }

    bool Node_device_str_is_archid(
        std::string const& SIXTRL_RESTRICT_REF device_str )
    {
        return st::Node_id_format_is_noarch( device_str );
    }

    bool Node_device_str_is_archstr(
        std::string const& SIXTRL_RESTRICT_REF device_str )
    {
        return st::Node_id_format_is_noarch( device_str );
    }

    bool Node_device_str_is_uuid(
        std::string const& SIXTRL_RESTRICT_REF device_str )
    {
        return ( ( !device_str.empty() ) &&
                 ( std::regex_match( device_str.c_str(),
            std::regex{ st::NODE_DEVICE_STR_KIND_UUID_REGEX } ) ) );
    }

    bool Node_device_str_is_pci_bus_id(
        std::string const& SIXTRL_RESTRICT_REF device_str )
    {
        return ( ( !device_str.empty() ) &&
                 ( std::regex_match( device_str.c_str(),
            std::regex{ st::NODE_DEVICE_STR_KIND_PCI_BUS_ID_REGEX } ) ) );
    }

    node_device_str_kind_t Node_find_device_str_kind_from_device_str(
        std::string const& SIXTRL_RESTRICT_REF device_str )
    {
        if( st::Node_device_str_is_uuid( device_str ) )
        {
            return st::NODE_DEVICE_STRING_KIND_UUID;
        }
        else if( st::Node_device_str_is_pci_bus_id( device_str ) )
        {
            return st::NODE_DEVICE_STRING_KIND_PCI_BUS_ID;
        }
        else if( st::Node_device_str_is_archid( device_str ) )
        {
            return st::NODE_DEVICE_STRING_KIND_ARCHID;
        }
        else if( st::Node_device_str_is_archstr( device_str ) )
        {
            return st::NODE_DEVICE_STRING_KIND_ARCHSTR;
        }
        else if( st::Node_device_str_is_noarch( device_str ) )
        {
            return st::NODE_DEVICE_STRING_KIND_NOARCH;
        }

        return st::NODE_DEVICE_STRING_KIND_ILLEGAL;
    }

    /* --------------------------------------------------------------------- */
}

bool NS(Node_is_device_str_kind_a_node_id_format)(
    ::NS(node_device_str_kind_t) const kind ) SIXTRL_NOEXCEPT {
    return SIXTRL_CXX_NAMESPACE::Node_is_device_str_kind_a_node_id_format( kind );
}

bool NS(Node_is_node_id_format_device_str_kind)(
    ::NS(node_id_str_fmt_t) const format ) SIXTRL_NOEXCEPT {
    return SIXTRL_CXX_NAMESPACE::Node_is_node_id_format_device_str_kind( format );
}

::NS(node_id_str_fmt_t) NS(Node_convert_device_str_kind_to_node_id_format)(
    ::NS(node_device_str_kind_t) const kind ) SIXTRL_NOEXCEPT {
    return SIXTRL_CXX_NAMESPACE::Node_convert_device_str_kind_to_node_id_format( kind );
}

::NS(node_device_str_kind_t) NS(Node_convert_node_id_format_to_device_str_kind)(
    ::NS(node_id_str_fmt_t) const format ) SIXTRL_NOEXCEPT {
    return SIXTRL_CXX_NAMESPACE::Node_convert_node_id_format_to_device_str_kind( format );
}

/* ------------------------------------------------------------------------- */

bool NS(Node_id_format_is_noarch)( char const* SIXTRL_RESTRICT node_id_str )
{
    return ( ( node_id_str != nullptr ) &&
             ( std::strlen( node_id_str ) > 0u ) &&
             ( SIXTRL_CXX_NAMESPACE::Node_id_format_is_noarch( node_id_str ) ) );
}

bool NS(Node_id_format_is_archid)( char const* SIXTRL_RESTRICT node_id_str )
{
    return ( ( node_id_str != nullptr ) &&
             ( std::strlen( node_id_str ) > 0u ) &&
             ( SIXTRL_CXX_NAMESPACE::Node_id_format_is_archid( node_id_str ) ) );
}

bool NS(Node_id_format_is_archstr)( char const* SIXTRL_RESTRICT node_id_str )
{
    return ( ( node_id_str != nullptr ) &&
             ( std::strlen( node_id_str ) > 0u ) &&
             ( SIXTRL_CXX_NAMESPACE::Node_id_format_is_archstr( node_id_str ) ) );
}

::NS(node_id_str_fmt_t) NS(Node_find_node_id_format)(
    char const* SIXTRL_RESTRICT node_id_str )
{
    return ( ( node_id_str != nullptr ) && ( std::strlen( node_id_str ) > 0u ) )
        ? SIXTRL_CXX_NAMESPACE::Node_find_node_id_format( node_id_str )
        : SIXTRL_CXX_NAMESPACE::NODE_ID_STR_FORMAT_ILLEGAL;
}

/* ------------------------------------------------------------------------- */

::NS(status_t) NS(NodeId_parse)( ::NS(NodeId)* SIXTRL_RESTRICT node_id,
    char const* SIXTRL_RESTRICT node_id_str )
{
    return ( ( node_id != nullptr ) && ( node_id_str != nullptr ) )
        ? SIXTRL_CXX_NAMESPACE::NodeId_parse( *node_id, node_id_str )
        : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
}

::NS(status_t) NS(NodeId_parse_using_format)(
    ::NS(NodeId)* SIXTRL_RESTRICT node_id,
    char const* SIXTRL_RESTRICT node_id_str,
    ::NS(node_id_str_fmt_t) const format )
{
    return ( ( node_id != nullptr ) && ( node_id_str != nullptr ) )
        ? SIXTRL_CXX_NAMESPACE::NodeId_parse_using_format( *node_id, node_id_str, format )
        : SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
}

/* ------------------------------------------------------------------------- */

bool NS(Node_device_str_is_noarch)( char const* SIXTRL_RESTRICT device_str )
{
    return ( ( device_str != nullptr ) &&
             ( SIXTRL_CXX_NAMESPACE::Node_device_str_is_noarch( device_str ) ) );
}

bool NS(Node_device_str_is_archid)(char const* SIXTRL_RESTRICT device_str )
{
    return ( ( device_str != nullptr ) &&
             ( SIXTRL_CXX_NAMESPACE::Node_device_str_is_archid( device_str ) ) );
}

bool NS(Node_device_str_is_archstr)( char const* SIXTRL_RESTRICT device_str )
{
    return ( ( device_str != nullptr ) &&
             ( SIXTRL_CXX_NAMESPACE::Node_device_str_is_archstr( device_str ) ) );
}

bool NS(Node_device_str_is_uuid)( char const* SIXTRL_RESTRICT device_str )
{
    return ( ( device_str != nullptr ) &&
             ( SIXTRL_CXX_NAMESPACE::Node_device_str_is_uuid( device_str ) ) );
}

bool NS(Node_device_str_is_pci_bus_id)( char const* SIXTRL_RESTRICT device_str )
{
    return ( ( device_str != nullptr ) &&
             ( SIXTRL_CXX_NAMESPACE::Node_device_str_is_pci_bus_id( device_str ) ) );
}

::NS(node_device_str_kind_t) NS(Node_find_device_str_kind_from_device_str)(
    char const* SIXTRL_RESTRICT device_str )
{
    return ( ( device_str != nullptr ) && ( std::strlen( device_str ) > 0u ) )
        ? SIXTRL_CXX_NAMESPACE::Node_find_device_str_kind_from_device_str( device_str )
        : SIXTRL_CXX_NAMESPACE::NODE_DEVICE_STRING_KIND_ILLEGAL;
}

#endif /* C++ */
