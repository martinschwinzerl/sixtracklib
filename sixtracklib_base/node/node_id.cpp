#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/node/node_id.h"
    #include "sixtracklib_base/backend/backends_store.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstring>
        #include <sstream>
        #include <regex>
        #include <utility>
    #endif /* C++  */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using this_t = st::NodeId;
        using st_size_t = this_t::size_type;
        using str_format_t = this_t::str_format_t;
        using st_backend_id_t = this_t::backend_id_t;
        using st_device_id_t = this_t::device_id_t;
        using st_platform_id_t = this_t::platform_id_t;
        using string_t = this_t::string_type;
        using str_char_t = this_t::string_char_t;
        using sstream_t = this_t::sstream_t;
    }

    constexpr char this_t::NODE_ID_STR_NOBACKEND_FORMAT_REGEX_STR[];

    /* ******************************************************************** */

    bool this_t::NODE_ID_STR_HAS_NOBACKEND_FORMAT(
        string_t const& SIXTRL_RESTRICT_REF node_id_str ) {
        return ( ( !node_id_str.empty() ) &&
            ( std::regex_match( node_id_str, std::regex{
                this_t::NODE_ID_STR_NOBACKEND_FORMAT_REGEX_STR } ) ) );
    }

    bool this_t::NODE_ID_STR_HAS_BACKENDID_FORMAT(
        string_t const& SIXTRL_RESTRICT_REF node_id_str )
    {
        st::BackendsStore& backend_store = st::BackendsStore_global();
        string_t const re_str(
            backend_store.node_id_format_backendid_regex_str() );

        return ( ( !node_id_str.empty() ) && ( !re_str.empty() ) &&
                 ( std::regex_match( node_id_str, std::regex{ re_str } ) ) );
    }

    bool this_t::NODE_ID_STR_HAS_BACKENDID_FORMAT_FOR_BACKEND(
        string_t const& SIXTRL_RESTRICT_REF node_id_str,
        this_t::backend_id_t const backend_id )
    {
        st::BackendsStore& backend_store = st::BackendsStore_global();
        string_t const regex_str(
            backend_store.node_id_format_backendid_regex_str_for_backend( backend_id ) );

        return ( ( !regex_str.empty() ) && ( !node_id_str.empty() ) &&
                 ( std::regex_match( node_id_str, std::regex{ regex_str } ) ) );
    }

    bool this_t::NODE_ID_STR_HAS_BACKENDSTR_FORMAT(
        string_t const& SIXTRL_RESTRICT_REF node_id_str )
    {
        st::BackendsStore& backend_store = st::BackendsStore_global();
        string_t const re_str(
            backend_store.node_id_format_backendstr_regex_str() );

        return ( ( !node_id_str.empty() ) && ( !re_str.empty() ) &&
                 ( std::regex_match( node_id_str, std::regex{ re_str } ) ) );
    }

    bool this_t::NODE_ID_STR_HAS_BACKENDSTR_FORMAT_FOR_BACKEND(
        string_t const& SIXTRL_RESTRICT_REF node_id_str,
        this_t::backend_id_t const backend_id )
    {
        st::BackendsStore& backend_store = st::BackendsStore_global();
        string_t const regex_str(
            backend_store.node_id_format_backendstr_regex_str_for_backend( backend_id ) );

        return ( ( !regex_str.empty() ) && ( !node_id_str.empty() ) &&
                 ( std::regex_match( node_id_str, std::regex{ regex_str } ) ) );
    }

    /* --------------------------------------------------------------------- */

    this_t::NodeId( st_backend_id_t const backend_id,
        st_platform_id_t const platform_id,
        st_device_id_t const device_id ) SIXTRL_NOEXCEPT
    {
        this->m_backend_id = backend_id;
        this->m_platform_id = platform_id;
        this->m_device_id = device_id;
    }

    this_t::NodeId( ::NS(NodeId) const& SIXTRL_RESTRICT_REF
        base_node_id ) SIXTRL_NOEXCEPT : ::NS(NodeId)( base_node_id ) {}

    this_t::NodeId( string_t const& SIXTRL_RESTRICT_REF device_str )
    {
        str_format_t const format =
            this->do_find_device_string_format( device_str );

        if( format == st::NODE_ID_STR_FORMAT_ILLEGAL )
        {
            throw std::runtime_error( "illegal/unknown device string format" );
        }

        if( this->do_parse_device_str_base_impl( device_str, format ) !=
            st::STATUS_SUCCESS )
        {
            throw std::runtime_error( "unable to parse device_str" );
        }
    }

    this_t::NodeId( string_t const& SIXTRL_RESTRICT_REF device_str,
        str_format_t const format )
    {
        if( format == st::NODE_ID_STR_FORMAT_ILLEGAL )
        {
            throw std::runtime_error( "illegal/unknown device string format" );
        }

        if( this->do_parse_device_str_base_impl( device_str, format ) !=
            st::STATUS_SUCCESS )
        {
            throw std::runtime_error( "unable to parse device_str" );
        }
    }

    NodeId& this_t::operator=(
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
    {
        if( &rhs != this )
        {
            this->set_backend_id( rhs.m_backend_id );
            this->set_platform_id( rhs.m_platform_id );
            this->set_device_id( rhs.m_device_id );
        }

        return *this;
    }

    /* --------------------------------------------------------------------- */

    bool this_t::is_legal() const SIXTRL_NOEXCEPT {
        return (
        ( this->m_backend_id != SIXTRL_CXX_NAMESPACE::BACKEND_ILLEGAL ) &&
        ( this->m_platform_id != ILLEGAL_PLATFORM_ID ) &&
        ( this->m_device_id != ILLEGAL_DEVICE_ID ) );
    }

    st_backend_id_t this_t::backend_id() const SIXTRL_NOEXCEPT {
        return this->m_backend_id; }

    this_t::platform_id_t this_t::platform_id() const SIXTRL_NOEXCEPT {
        return this->m_platform_id; }

    this_t::device_id_t this_t::device_id() const SIXTRL_NOEXCEPT {
        return this->m_device_id; }

    st_status_t this_t::set_backend_id(
        st_backend_id_t const backend_id ) SIXTRL_NOEXCEPT {
        this->m_backend_id = backend_id;
        return SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS;
    }

    st_status_t this_t::set_platform_id(
        this_t::platform_id_t const platform_id ) SIXTRL_NOEXCEPT
    {
        this->m_platform_id = platform_id;
        return SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS;
    }

    st_status_t this_t::set_device_id(
        this_t::device_id_t const device_id ) SIXTRL_NOEXCEPT {
        this->m_device_id = device_id;
        return SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS;
    }

    this_t::str_format_t this_t::find_device_string_format(
        string_t const& SIXTRL_RESTRICT_REF device_str ) {
        return this->do_find_device_string_format( device_str ); }

    st_status_t this_t::from_string_using_format(
        string_t const& SIXTRL_RESTRICT_REF device_str,
        str_format_t const format ) SIXTRL_NOEXCEPT {
        return this->do_parse_device_str( device_str, format );
    }

    st_status_t this_t::from_string(
        string_t const& SIXTRL_RESTRICT_REF device_string ) {
        return this->from_string_using_format( device_string,
            this->find_device_string_format( device_string ) );
    }

    void this_t::clear() SIXTRL_NOEXCEPT { this->do_clear(); }

    /* ----------------------------------------------------------------- */

    void this_t::print(
        std::ostream& SIXTRL_RESTRICT_REF ostr ) const {
        this->do_print( ostr, this_t::DEFAULT_STR_FORMAT ); }

    void this_t::print_using_format( std::ostream& SIXTRL_RESTRICT_REF ostr,
        this_t::str_format_t const format ) const {
        this->do_print( ostr, format ); }


    /* --------------------------------------------------------------------- */

    string_t this_t::to_string_using_format(
        str_format_t const str_format ) const {
        sstream_t a2str;

        if( this->do_print( a2str, str_format ) != st::STATUS_SUCCESS )
        {
            throw std::runtime_error( "unable to print node_id" );
        }

        return a2str.str();
    }

    string_t this_t::to_string() const {
        return this->to_string_using_format( this_t::DEFAULT_STR_FORMAT );
    }

    st_size_t this_t::required_device_string_capacity(
        str_format_t const str_format ) const {
        string_t const temp_device_str(
            this->to_string_using_format( str_format ) );
        return temp_device_str.size() + size_type{ 1 };
    }

    st_status_t this_t::to_string_using_format(
        str_char_t* SIXTRL_RESTRICT device_str,
        st_size_t const device_str_capacity,
        str_format_t const format ) const
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( device_str != nullptr ) &&
            ( device_str_capacity > st_size_t{ 1 } ) )
        {
            string_t const temp_device_str(
                this->to_string_using_format( format ) );

            std::fill( device_str, device_str + device_str_capacity, '\0' );

            if( ( temp_device_str.size() > st_size_t{ 0 } ) &&
                ( temp_device_str.size() < device_str_capacity ) )
            {
                std::strncpy( device_str, temp_device_str.c_str(),
                              device_str_capacity - st_size_t{ 1 } );
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    st_status_t this_t::to_string( str_char_t* SIXTRL_RESTRICT device_str,
        st_size_t const device_str_capacity ) const {
        return this->to_string_using_format( device_str,
            device_str_capacity, this_t::DEFAULT_STR_FORMAT );
    }

    /* --------------------------------------------------------------------- */

    void this_t::do_clear()
    {
        this->m_backend_id = st::BACKEND_ILLEGAL;
        this->m_platform_id = this_t::ILLEGAL_PLATFORM_ID;
        this->m_device_id = this_t::ILLEGAL_DEVICE_ID;
    }

    str_format_t this_t::do_find_device_string_format(
        string_t const& device_id_str ) const
    {
        return this->do_find_device_string_format_base_impl( device_id_str );
    }

    st_status_t this_t::do_parse_device_str(
        string_t const& SIXTRL_RESTRICT_REF device_str,
        str_format_t const format )
    {
        return this->do_parse_device_str_base_impl( device_str, format );
    }

    st_status_t this_t::do_print( std::ostream& SIXTRL_RESTRICT_REF ostr,
        str_format_t const device_str_format ) const
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->m_platform_id != this_t::ILLEGAL_PLATFORM_ID ) &&
            ( this->m_device_id   != this_t::ILLEGAL_DEVICE_ID ) )
        {
            st::BackendsStore const& backend_store =
                st::BackendsStore_const_global();

            switch( device_str_format )
            {
                case st::NODE_ID_STR_FORMAT_NOBACKEND:
                {
                    ostr << this->m_platform_id << ":" << this->m_device_id;
                    status = st::STATUS_SUCCESS;
                    break;
                }

                case st::NODE_ID_STR_FORMAT_BACKENDID:
                {
                    auto backend = backend_store.backend( this->m_backend_id );

                    if( ( backend != nullptr ) && ( backend->has_nodes() ) )
                    {
                        ostr << this->m_backend_id << ":" << this->m_platform_id
                             << ":" << this->m_device_id;
                        status = st::STATUS_SUCCESS;
                    }

                    break;
                }

                case st::NODE_ID_STR_FORMAT_BACKENDSTR:
                {
                    auto backend = backend_store.backend( this->m_backend_id );

                    if( ( backend != nullptr ) && ( backend->has_nodes() ) &&
                        ( backend->has_backend_string() ) )
                    {
                        ostr << backend->backend_string_str() << ":"
                             << this->m_platform_id << ":" << this->m_device_id;
                        status = st::STATUS_SUCCESS;
                    }

                    break;
                }

                default:
                {
                    status = st::STATUS_GENERAL_FAILURE;
                }
            };
        }

        return status;
    }

    str_format_t this_t::do_find_device_string_format_base_impl(
        string_t const& device_id_str ) const
    {
        str_format_t format = st::NODE_ID_STR_FORMAT_ILLEGAL;
        st::BackendsStore& backend_store = st::BackendsStore_global();

        if( ( !device_id_str.empty() ) &&
            ( backend_store.has_backends_with_nodes() ) )
        {
            if( this_t::NODE_ID_STR_HAS_BACKENDID_FORMAT( device_id_str ) )
            {
                format = st::NODE_ID_STR_FORMAT_BACKENDID;
            }

            if( ( format == st::NODE_ID_STR_FORMAT_ILLEGAL ) &&
                ( this_t::NODE_ID_STR_HAS_BACKENDSTR_FORMAT( device_id_str ) ) )
            {
                format = st::NODE_ID_STR_FORMAT_BACKENDSTR;
            }

            if( ( format == st::NODE_ID_STR_FORMAT_ILLEGAL ) &&
                ( this_t::NODE_ID_STR_HAS_NOBACKEND_FORMAT( device_id_str ) ) )
            {
                format = st::NODE_ID_STR_FORMAT_NOBACKEND;
            }
        }

        return format;
    }

    st_status_t this_t::do_parse_device_str_base_impl(
        string_t const& SIXTRL_RESTRICT_REF device_str,
        str_format_t const format ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        st::BackendsStore& backend_store = st::BackendsStore_global();

        if( ( backend_store.has_backends_with_nodes() ) &&
            ( !device_str.empty() ) )
        {
            std::smatch matched_parts;

            switch( format )
            {
                case st::NODE_ID_STR_FORMAT_NOBACKEND:
                {
                    std::regex re = std::regex{
                            this_t::NODE_ID_STR_NOBACKEND_FORMAT_REGEX_STR };

                    if( ( std::regex_match( device_str, matched_parts, re ) ) &&
                        ( matched_parts.size() == st_size_t{ 3 } ) )
                    {
                        this->m_backend_id = st::BACKEND_UNDEFINED;
                        this->m_platform_id = std::stoi( matched_parts[ 1 ] );
                        this->m_device_id = std::stoi( matched_parts[ 2 ] );
                        status = st::STATUS_SUCCESS;
                    }

                    break;
                }

                case st::NODE_ID_STR_FORMAT_BACKENDID:
                {
                    string_t const& regex_str =
                        backend_store.node_id_format_backendid_regex_str();

                    if( ( !regex_str.empty() ) &&
                        ( std::regex_match( device_str, matched_parts,
                          std::regex{ regex_str } ) ) )
                    {
                        st_size_t const nn = matched_parts.size();
                        if( nn == st_size_t{ 4 } )
                        {
                            this->m_backend_id = std::stoi( matched_parts[ 1 ] );
                            this->m_platform_id = std::stoi( matched_parts[ 2 ] );
                            this->m_device_id = std::stoi( matched_parts[ 3 ] );
                            status = st::STATUS_SUCCESS;
                        }
                    }

                    break;
                }

                case st::NODE_ID_STR_FORMAT_BACKENDSTR:
                {
                    string_t const& regex_str =
                        backend_store.node_id_format_backendstr_regex_str();

                    if( ( !regex_str.empty() ) &&
                        ( std::regex_match( device_str, matched_parts,
                          std::regex{ regex_str } ) ) )
                    {
                        st_size_t const nn = matched_parts.size();
                        if( nn == st_size_t{ 4 } )
                        {
                            string_t const backend_str = matched_parts[ 1 ];

                            if( ( !backend_str.empty() ) &&
                                ( backend_store.has_backend_by_str( backend_str ) ) )
                            {
                                this->m_backend_id =
                                    backend_store.backend_id_by_str( backend_str );
                                this->m_platform_id = std::stoi( matched_parts[ 2 ] );
                                this->m_device_id = std::stoi( matched_parts[ 3 ] );
                                status = st::STATUS_SUCCESS;
                            }
                        }
                    }

                    break;
                }

                default:
                {
                    this->m_backend_id = st::BACKEND_ILLEGAL;
                    this->m_platform_id = this_t::ILLEGAL_PLATFORM_ID;
                    this->m_device_id = this_t::ILLEGAL_DEVICE_ID;
                }
            };
        }

        return status;
    }

    std::ostream& operator<<( std::ostream& SIXTRL_RESTRICT_REF ostr,
        NodeId const& SIXTRL_RESTRICT_REF node_id )
    {
        node_id.print_using_format( ostr, NodeId::DEFAULT_STR_FORMAT );
        return ostr;
    }
} /* ns: SIXTRL_CXX_NAMESPACE */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                Exported Plugin C-API :: Functions               !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

::NS(BaseNodeId)* NS(NodeId_create_undefined)(
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return new st::NodeId( st::BACKEND_UNDEFINED, platform_id, device_id );
}

::NS(BaseNodeId)* NS(NodeId_create_undefined_from_str)(
    char const* SIXTRL_RESTRICT config_str )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    std::unique_ptr< ::NS(BaseNodeId) > temp{ nullptr };

    if( ( config_str != nullptr ) &&
        ( std::strlen( config_str ) > st_size_t{ 0 } ) )
    {
        temp.reset( new st::NodeId( config_str ));
        if( ( temp.get() != nullptr ) &&
            ( temp->backend_id() != st::BACKEND_UNDEFINED ) &&
            ( temp->backend_id() != st::BACKEND_ILLEGAL ) )
        {
            temp->set_backend_id( st::BACKEND_UNDEFINED );
        }
    }

    return temp.release();
}

::NS(BaseNodeId)* NS(NodeId_create_undefined_from_str_detailed)(
    char const* SIXTRL_RESTRICT config_str,
    ::NS(node_id_str_fmt_t) const node_id_str_fmt )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    std::unique_ptr< ::NS(BaseNodeId) > temp{ nullptr };

    if( ( config_str != nullptr ) &&
        ( std::strlen( config_str ) > st_size_t{ 0 } ) )
    {
        temp.reset( new st::NodeId( config_str, node_id_str_fmt ));
        if( ( temp.get() != nullptr ) &&
            ( temp->backend_id() != st::BACKEND_UNDEFINED ) &&
            ( temp->backend_id() != st::BACKEND_ILLEGAL ) )
        {
            temp->set_backend_id( st::BACKEND_UNDEFINED );
        }
    }

    return temp.release();
}

void NS(NodeId_delete)( ::NS(BaseNodeId)* SIXTRL_RESTRICT n_id ) SIXTRL_NOEXCEPT
{
    delete n_id;
}

#endif /* C++, Host */

