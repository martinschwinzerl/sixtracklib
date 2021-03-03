#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/backends/backends.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    #include <regex>
    #include <sstream>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace { namespace st = SIXTRL_CXX_NAMESPACE; }

    constexpr st::NodeId::platform_id_type  st::NodeId::ILLEGAL_PLATFORM_ID;
    constexpr st::NodeId::device_id_type    st::NodeId::ILLEGAL_DEVICE_ID;
    constexpr st::NodeId::index_type        st::NodeId::ILLEGAL_INDEX;
    constexpr st::NodeId::str_format_type   st::NodeId::DEFAULT_STR_FORMAT;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    NodeId::status_type NodeId::DECODE_NODE_ID_STR(
        std::string const& SIXTRL_RESTRICT_REF node_id_str,
        NodeId::str_format_type str_format,
        NodeId::platform_id_type* SIXTRL_RESTRICT ptr_platform_id,
        NodeId::device_id_type*   SIXTRL_RESTRICT ptr_device_id,
        NodeId::backend_id_type*  SIXTRL_RESTRICT ptr_backend_id )
    {
        st::status_type status = st::STATUS_GENERAL_FAILURE;
        if( ( str_format == st::NODE_ID_STR_FORMAT_ILLEGAL ) ||
            ( str_format == st::NODE_ID_STR_FORMAT_AUTO ) )
              str_format =  st::NodeId::GET_STR_FORMAT_TYPE( node_id_str );

        if(  ptr_platform_id != nullptr )
            *ptr_platform_id = st::NodeId::ILLEGAL_PLATFORM_ID;

        if(  ptr_device_id != nullptr )
            *ptr_device_id = st::NodeId::ILLEGAL_DEVICE_ID;

        if( ptr_backend_id != nullptr ) *ptr_backend_id = st::BACKEND_ID_NONE;

        if( ( !node_id_str.empty() ) &&
            ( str_format != st::NODE_ID_STR_FORMAT_ILLEGAL ) )
        {
            using backend_id_type  = NodeId::backend_id_type;
            using platform_id_type = NodeId::platform_id_type;
            using device_id_type   = NodeId::device_id_type;

            backend_id_type backend_id   = st::BACKEND_ID_NONE;
            device_id_type device_id     = st::NodeId::ILLEGAL_DEVICE_ID;
            platform_id_type platform_id = st::NodeId::ILLEGAL_PLATFORM_ID;

            switch( str_format )
            {
                case st::NODE_ID_STR_FORMAT_BACKEND_STR:
                {
                    std::ostringstream a2str;
                    a2str << st::Backends_backend_str_regex( false )
                          << "\\:([0-9]+)\\.([0-9]+)";

                    std::regex const RE( a2str.str() );
                    std::smatch matched_parts;

                    if( std::regex_match( node_id_str, matched_parts, RE ) )
                    {
                        st::size_type const nn = matched_parts.size();
                        if( nn == st::size_type{ 4 } )
                        {
                            backend_id = st::Backends_id_by_string(
                                std::ssub_match( matched_parts[ 1 ] ).str() );

                            platform_id = std::stoi(
                                std::ssub_match( matched_parts[ 2 ] ).str() );

                            device_id = std::stoi(
                                std::ssub_match( matched_parts[ 3 ] ).str() );

                            if( backend_id != st::BACKEND_ID_NONE )
                            {
                                status = st::STATUS_SUCCESS;
                            }
                        }
                    }

                    break;
                }

                case st::NODE_ID_STR_FORMAT_BACKEND_ID:
                {
                    std::ostringstream a2str;
                    a2str << st::Backends_backend_id_regex( false )
                          << "\\:([0-9]+)\\.([0-9]+)";

                    std::regex const RE( a2str.str() );
                    std::smatch matched_parts;

                    if( std::regex_match( node_id_str, matched_parts, RE ) )
                    {
                        st::size_type const nn = matched_parts.size();
                        if( nn == st::size_type{ 4 } )
                        {
                            backend_id = std::stoi(
                                std::ssub_match( matched_parts[ 1 ] ).str() );

                            platform_id = std::stoi(
                                std::ssub_match( matched_parts[ 2 ] ).str() );

                            device_id = std::stoi(
                                std::ssub_match( matched_parts[ 3 ] ).str() );

                            if( backend_id != st::BACKEND_ID_NONE )
                            {
                                status = st::STATUS_SUCCESS;
                            }
                        }
                    }

                    break;
                }

                case st::NODE_ID_STR_FORMAT_MINIMAL:
                {
                    std::regex const RE( "([0-9]+)\\.([0-9]+)" );
                    std::smatch matched_parts;

                    if( std::regex_match( node_id_str, matched_parts, RE ) )
                    {
                        st::size_type const nn = matched_parts.size();
                        if( nn == st::size_type{ 3 } )
                        {
                            platform_id = std::stoi(
                                std::ssub_match( matched_parts[ 1 ] ).str() );

                            device_id = std::stoi(
                                std::ssub_match( matched_parts[ 2 ] ).str() );

                            status = st::STATUS_SUCCESS;
                        }
                    }

                    break;
                }

                default:
                {
                    status = st::STATUS_GENERAL_FAILURE;
                }
            };

            if( status == st::STATUS_SUCCESS )
            {
                if( ptr_platform_id != nullptr ) *ptr_platform_id = platform_id;
                if( ptr_device_id   != nullptr ) *ptr_device_id   = device_id;
                if( ptr_backend_id  != nullptr ) *ptr_backend_id  = backend_id;
            }
        }

        return status;
    }

    NodeId::str_format_type NodeId::GET_STR_FORMAT_TYPE(
        std::string const& SIXTRL_RESTRICT_REF node_id_str,
        NodeId::backend_id_type* ptr_backend_id )
    {
        NodeId::str_format_type format = st::NODE_ID_STR_FORMAT_ILLEGAL;

        if( ptr_backend_id != nullptr ) *ptr_backend_id = st::BACKEND_ID_NONE;

        if( !node_id_str.empty() )
        {
            std::regex const MINIMAL_REGEX = std::regex( "([0-9]+)\\.([0-9]+)" );

            std::ostringstream a2str;
            a2str << st::Backends_backend_id_regex( false );
            a2str << "\\:([0-9]+)\\.([0-9]+)";
            std::string regex_str = a2str.str();
            std::regex const BACKEND_ID_REGEX = std::regex( regex_str );

            a2str.str( "" );
            a2str << st::Backends_backend_str_regex( false );
            a2str << "\\:([0-9]+)\\.([0-9]+)";
            regex_str = a2str.str();
            std::regex const BACKEND_STR_REGEX = std::regex( regex_str );

            if( std::regex_match( node_id_str, BACKEND_STR_REGEX ) )
            {
                std::smatch matched_parts;
                if( std::regex_match( node_id_str, matched_parts,
                        BACKEND_STR_REGEX ) )
                {
                    NodeId::backend_id_type backend_id = st::BACKEND_ID_NONE;
                    st::size_type const nn = matched_parts.size();
                    if( nn == st::size_type{ 4 } )
                    {
                        backend_id = st::Backends_id_by_string(
                            std::ssub_match( matched_parts[ 1 ] ).str() );

                        format = st::NODE_ID_STR_FORMAT_BACKEND_STR;

                        if( ptr_backend_id != nullptr )
                            *ptr_backend_id = backend_id;
                    }
                }
            }
            else if( std::regex_match( node_id_str, BACKEND_ID_REGEX ) )
            {
                std::smatch matched_parts;
                if( std::regex_match( node_id_str, matched_parts,
                        BACKEND_ID_REGEX ) )
                {
                    NodeId::backend_id_type backend_id = st::BACKEND_ID_NONE;
                    st::size_type const nn = matched_parts.size();
                    if( nn == st::size_type{ 4 } )
                    {
                        backend_id = std::stoi( std::ssub_match(
                            matched_parts[ 1 ] ).str() );

                        format = st::NODE_ID_STR_FORMAT_BACKEND_ID;

                        if( ptr_backend_id != nullptr )
                            *ptr_backend_id = backend_id;
                    }
                }
            }
            else if( std::regex_match( node_id_str, MINIMAL_REGEX ) )
            {
                format = st::NODE_ID_STR_FORMAT_MINIMAL;

                if(  ptr_backend_id != nullptr )
                    *ptr_backend_id = st::BACKEND_ID_NONE;
            }
        }

        return format;
    }

    status_type NodeId::from_string(
        std::string const& SIXTRL_RESTRICT_REF node_id_str,
        NodeId::str_format_type format, NodeId::backend_id_type* ptr_backend_id )
    {
        if( format == st::NODE_ID_STR_FORMAT_AUTO )
            format = NodeId::GET_STR_FORMAT_TYPE( node_id_str );

        return NodeId::DECODE_NODE_ID_STR( node_id_str, format,
            &this->m_platform_id, &this->m_device_id, ptr_backend_id );
    }

    NodeId::status_type NodeId::to_stream( std::ostream& ostr,
        NodeId::str_format_type format,
        NodeId::backend_id_type const backend_id ) const
    {
        NodeId::status_type status = st::STATUS_GENERAL_FAILURE;
        if( !this->is_legal() ) return status;

        if( format == st::NODE_ID_STR_FORMAT_AUTO )
            format =  st::NODE_ID_STR_FORMAT_DEFAULT;

        switch( format )
        {
            case st::NODE_ID_STR_FORMAT_MINIMAL:
            {
                ostr << this->platform_id() << "." << this->device_id();
                status = st::STATUS_SUCCESS;
                break;
            }

            case st::NODE_ID_STR_FORMAT_BACKEND_ID:
            {
                if( backend_id != st::BACKEND_ID_NONE )
                {
                    ostr << backend_id << ":"
                         << this->platform_id() << "." << this->device_id();
                    status = st::STATUS_SUCCESS;
                }

                break;
            }

            case st::NODE_ID_STR_FORMAT_BACKEND_STR:
            {
                if( backend_id != st::BACKEND_ID_NONE )
                {
                    st::Backends_string_to_stream( ostr, backend_id );
                    ostr << ":" << this->platform_id() << "."
                                << this->device_id();

                    status = st::STATUS_SUCCESS;
                }

                break;
            }

            default:
            {
                status = st::STATUS_GENERAL_FAILURE;
            }
        };

        return status;
    }

    NodeId::cmp_result_type NodeId::compare(
        NodeId const& SIXTRL_RESTRICT_REF rhs,
        bool const use_node_index_for_cmp ) const SIXTRL_NOEXCEPT
    {
        using cmp_result_t = st::NodeId::cmp_result_type;
        cmp_result_t result = cmp_result_t{ 0 };

        if( this != &rhs )
        {
            if( this->m_platform_id != rhs.m_platform_id )
            {
                result = ( this->m_platform_id > rhs.m_platform_id )
                    ? cmp_result_t{ +1 } : cmp_result_t{ -1 };
            }

            if( ( result == cmp_result_t{ 0 } ) &&
                ( this->m_device_id != rhs.m_device_id ) )
            {
                result = ( this->m_device_id > rhs.m_device_id )
                    ? cmp_result_t{ +1 } : cmp_result_t{ -1 };
            }

            if( ( result == cmp_result_t{ 0 } ) && ( use_node_index_for_cmp ) &&
                ( this->m_node_index != rhs.m_node_index ) )
            {
                result = ( this->m_node_index > rhs.m_node_index )
                    ? cmp_result_t{ +1 } : cmp_result_t{ -1 };
            }
        }

        return result;
    }
}

SIXTRL_ARGPTR_DEC ::NS(NodeId)* NS(NodeId_create)( void ) {
    return new SIXTRL_CXX_NAMESPACE::NodeId(); }

void NS(NodeId_delete)( SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node ) {
    delete node; }

SIXTRL_ARGPTR_DEC ::NS(NodeId)* NS(NodeId_new)(
    ::NS(node_platform_id_type) const platform_id,
    ::NS(node_device_id_type) const device_id ) {
    return new SIXTRL_CXX_NAMESPACE::NodeId( platform_id, device_id ); }

SIXTRL_ARGPTR_DEC ::NS(NodeId)* NS(NodeId_new_from_string)(
    char const* SIXTRL_RESTRICT node_id_str ) {
    return new SIXTRL_CXX_NAMESPACE::NodeId( node_id_str ); }

SIXTRL_ARGPTR_DEC ::NS(NodeId)* NS(NodeId_new_detailed)(
    ::NS(node_platform_id_type) const platform_id,
    ::NS(node_device_id_type) const device_id,
    ::NS(node_index_type) const index ) {
    return new SIXTRL_CXX_NAMESPACE::NodeId( platform_id, device_id, index ); }

SIXTRL_ARGPTR_DEC ::NS(NodeId)* NS(NodeId_preset)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node_id ) {
    if( node_id != nullptr ) node_id->clear();
    return node_id; }

bool NS(NodeId_is_legal)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node ) {
    return ( ( node != nullptr ) && ( node->is_legal() ) ); }

::NS(node_platform_id_type) NS(NodeId_platform_id)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node ) {
    return ( node != nullptr )
        ? node->platform_id()
        : SIXTRL_CXX_NAMESPACE::NodeId::ILLEGAL_PLATFORM_ID; }

::NS(node_device_id_type) NS(NodeId_device_id)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node ) {
    return ( node != nullptr )
        ? node->device_id()
        : SIXTRL_CXX_NAMESPACE::NodeId::ILLEGAL_DEVICE_ID; }

bool NS(NodeId_has_index)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node ) {
    return ( ( node != nullptr ) && ( node->has_index() ) ); }

::NS(node_index_type) NS(NodeId_node_index)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node ) {
    return ( node != nullptr )
        ? node->index()
        : SIXTRL_CXX_NAMESPACE::NodeId::ILLEGAL_INDEX; }

/* ------------------------------------------------------------------------- */

void NS(NodeId_clear)( SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node ) {
    if( node != nullptr ) node->clear(); }

void NS(NodeId_reset)( SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node,
    ::NS(node_platform_id_type) const platform_id,
    ::NS(node_device_id_type) const device_id,
    ::NS(node_index_type) const index ) {
    if( node != nullptr ) node->reset( platform_id, device_id, index ); }

/* ------------------------------------------------------------------------- */

void NS(NodeId_set_platform_id)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node,
    ::NS(node_platform_id_type) const platform_id ) {
    if( node != nullptr ) node->set_platform_id( platform_id ); }

void NS(NodeId_set_device_id)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node,
    ::NS(node_device_id_type) const device_id ) {
    if( node != nullptr ) node->set_device_id( device_id ); }

void NS(NodeId_set_index)( SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node,
    ::NS(node_index_type) const node_index ) {
    if( node != nullptr ) node->set_index( node_index ); }

/* ------------------------------------------------------------------------- */

::NS(status_type) NS(NodeId_to_string)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    SIXTRL_ARGPTR_DEC char* SIXTRL_RESTRICT node_id_str,
    ::NS(size_type) const node_id_str_capacity ) {
    return ( node != nullptr )
        ? node->to_string( node_id_str, node_id_str_capacity,
            ::NS(NODE_ID_STR_FORMAT_MINIMAL) )
        : ::NS(STATUS_GENERAL_FAILURE); }

::NS(status_type) NS(NodeId_to_string_detailed)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node,
    SIXTRL_ARGPTR_DEC char* SIXTRL_RESTRICT node_id_str,
    ::NS(size_type) const node_id_str_capacity,
    ::NS(backend_id_type) const backend_id ) {
    return ( node != nullptr )
        ? node->to_string( node_id_str, node_id_str_capacity, backend_id )
        : ::NS(STATUS_GENERAL_FAILURE); }

::NS(status_type) NS(NodeId_from_string)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT node_id_str ) {
    return ( node != nullptr )
        ? node->from_string( node_id_str )
        : ::NS(STATUS_GENERAL_FAILURE); }

::NS(status_type) NS(NodeId_from_string_detailed)(
    SIXTRL_ARGPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT node,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT node_id_str,
    ::NS(node_id_str_fmt_type) const node_id_str_fmt,
    SIXTRL_ARGPTR_DEC ::NS(backend_id_type)* SIXTRL_RESTRICT ptr_backend_id ) {
    return ( node != nullptr )
        ? node->from_string( node_id_str, node_id_str_fmt, ptr_backend_id )
        : ::NS(STATUS_GENERAL_FAILURE); }

/* ------------------------------------------------------------------------- */

::NS(cmp_result_type) NS(NodeId_compare)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs ) {
    ::NS(cmp_result_type) result = ::NS(cmp_result_type){ 1 };
    SIXTRL_ASSERT( ( lhs != SIXTRL_NULLPTR ) || ( rhs != SIXTRL_NULLPTR ) );
    if( ( lhs != rhs ) && ( lhs != nullptr ) && ( rhs != nullptr ) )
    {
        result = lhs->compare( *rhs );
    }
    else if( ( lhs != rhs ) && ( rhs != nullptr ) )
    {
        result = ::NS(cmp_result_type){ -1 };
    }
    else if( lhs == rhs )
    {
        result = ::NS(cmp_result_type){ 0 };
    }

    return result;
}

bool NS(NodeId_are_equal)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs ) {
    return ( ( lhs == rhs ) ||
             ( ( lhs != nullptr ) && ( rhs != nullptr ) &&
               ( ::NS(cmp_result_type){ 0 } == lhs->compare( *rhs ) ) ) ); }

/* ------------------------------------------------------------------------- */

void NS(NodeId_print_out)( SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const
    SIXTRL_RESTRICT node_id ) {
    if( node_id != nullptr ) node_id->to_stream(
        std::cout, ::NS(NODE_ID_STR_FORMAT_MINIMAL) ); }

void NS(NodeId_print)( ::FILE* SIXTRL_RESTRICT output,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT node_id ) {
    namespace st = SIXTRL_CXX_NAMESPACE;
    if( ( node_id != nullptr ) && ( output != nullptr ) )
    {
        std::ostringstream a2str;
        if( st::STATUS_SUCCESS == node_id->to_stream(
                a2str, ::NS(NODE_ID_STR_FORMAT_MINIMAL) ) )
        {
            std::string const temp = a2str.str();
            std::fprintf( output, "%s", temp.c_str() );
        }
    }
}

#endif /* C++, Host */
