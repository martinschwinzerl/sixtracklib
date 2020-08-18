#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/node/node_info.h"
    #include "sixtracklib_base/backend/backends_store.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <cstring>
        #include <iomanip>
        #include <ostream>
        #include <regex>
        #include <string>
        #include <sstream>
    #endif /* C++ */
#endif /* SIXTRL_NO_SYSTEM_INCLUDES */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using base_node_t  = st::BaseNodeInfo;
    using st_status_t  = base_node_t::status_t;
    using st_node_id_t = base_node_t::node_id_t;
    using str_format_t = st_node_id_t::str_format_t;
    using st_c_node_id_t = base_node_t::c_node_id_t;
    using st_size_t    = base_node_t::size_type;
    using st_dev_str_kind_t = base_node_t::device_str_kind_t;
    using st_print_flags_t = st::node_print_flags_t;
    using string_t = base_node_t::string_type;
    using str_char_t = base_node_t::string_char_t;
    using sstream_t = base_node_t::sstream_t;
}

namespace SIXTRL_CXX_NAMESPACE
{
    constexpr char base_node_t::DEVICE_ID_STR_UUID_REGEX_STR[];
    constexpr char base_node_t::DEVICE_ID_STR_PCI_BUS_ID_REGEX_STR[];

    /* --------------------------------------------------------------------- */

    bool base_node_t::DEVICE_ID_STR_HAS_NOBACKEND_FORMAT(
        string_t const& SIXTRL_RESTRICT_REF device_id_str )
    {
        return st_node_id_t::NODE_ID_STR_HAS_NOBACKEND_FORMAT( device_id_str );
    }

    bool base_node_t::DEVICE_ID_STR_HAS_BACKENDID_FORMAT(
        string_t const& SIXTRL_RESTRICT_REF device_id_str )
    {
        return st_node_id_t::NODE_ID_STR_HAS_BACKENDID_FORMAT( device_id_str );
    }

    bool base_node_t::DEVICE_ID_STR_HAS_BACKENDID_FORMAT_FOR_BACKEND(
        string_t const& SIXTRL_RESTRICT_REF device_id_str,
        st_backend_id_t const backend_id )
    {
        return st_node_id_t::NODE_ID_STR_HAS_BACKENDID_FORMAT_FOR_BACKEND(
            device_id_str, backend_id );
    }

    bool base_node_t::DEVICE_ID_STR_HAS_BACKENDSTR_FORMAT(
        string_t const& SIXTRL_RESTRICT_REF device_id_str )
    {
        return st_node_id_t::NODE_ID_STR_HAS_BACKENDSTR_FORMAT( device_id_str );
    }

    bool base_node_t::DEVICE_ID_STR_HAS_BACKENDSTR_FORMAT_FOR_BACKEND(
        string_t const& SIXTRL_RESTRICT_REF device_id_str,
        st_backend_id_t const backend_id )
    {
        return st_node_id_t::NODE_ID_STR_HAS_BACKENDSTR_FORMAT_FOR_BACKEND(
            device_id_str, backend_id );
    }

    bool base_node_t::DEVICE_ID_STR_HAS_UUID_FORMAT(
        string_t const& SIXTRL_RESTRICT_REF device_id_str )
    {
        return ( ( !device_id_str.empty() ) &&
                 ( std::regex_match( device_id_str, std::regex{
                    base_node_t::DEVICE_ID_STR_UUID_REGEX_STR } ) ) );
    }

    bool base_node_t::DEVICE_ID_STR_HAS_PCI_BUS_ID_FORMAT(
        string_t const& SIXTRL_RESTRICT_REF device_id_str )
    {
        return ( ( !device_id_str.empty() ) &&
                 ( std::regex_match( device_id_str, std::regex{
                    base_node_t::DEVICE_ID_STR_PCI_BUS_ID_REGEX_STR } ) ) );
    }

    /* --------------------------------------------------------------------- */

    st_c_node_id_t base_node_t::node_id_data() const SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( this->m_stored_node_id.get() != nullptr );
        return st_c_node_id_t{ this->m_stored_node_id->backend_id(),
            this->m_stored_node_id->platform_id(),
                this->m_stored_node_id->device_id() };
    }

    st_node_id_t const* base_node_t::base_node_id() const SIXTRL_NOEXCEPT {
        return this->m_stored_node_id.get();
    }

    base_node_t::platform_id_t base_node_t::platform_id() const SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( this->m_stored_node_id.get() != nullptr );
        return this->m_stored_node_id->platform_id();
    }

    base_node_t::device_id_t base_node_t::device_id() const SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( this->m_stored_node_id.get() != nullptr );
        return this->m_stored_node_id->device_id();
    }

    st_status_t base_node_t::set_platform_id( base_node_t::platform_id_t const
        platform_id ) SIXTRL_NOEXCEPT {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( this->m_stored_node_id.get() != nullptr )
        {
            bool const needs_update = ( platform_id !=
                this->m_stored_node_id->platform_id() );

            status = this->m_stored_node_id->set_platform_id( platform_id );

            if( ( status == st::STATUS_SUCCESS ) && ( needs_update ) )
            {
                status = this->do_update_default_device_strings();
            }
        }

        return status;
    }

    st_status_t base_node_t::set_device_id(
        base_node_t::device_id_t const device_id ) SIXTRL_NOEXCEPT {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( this->m_stored_node_id.get() != nullptr )
        {
            bool const needs_update = ( device_id !=
                this->m_stored_node_id->device_id() );

            status = this->m_stored_node_id->set_device_id( device_id );

            if( ( status == st::STATUS_SUCCESS ) && ( needs_update ) )
            {
                status = this->do_update_default_device_strings();
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    string_t const& base_node_t::platform_name_str() const SIXTRL_NOEXCEPT {
        return this->m_platform_name;
    }

    string_t const& base_node_t::device_name_str() const SIXTRL_NOEXCEPT {
        return this->m_device_name;
    }

    string_t const& base_node_t::description_str() const SIXTRL_NOEXCEPT {
        return this->m_description;
    }

    str_char_t const* base_node_t::platform_name() const SIXTRL_NOEXCEPT {
        return this->m_platform_name.c_str();
    }

    str_char_t const* base_node_t::device_name() const SIXTRL_NOEXCEPT {
        return this->m_device_name.c_str();
    }

    str_char_t const* base_node_t::description() const SIXTRL_NOEXCEPT {
        return this->m_description.c_str();
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t base_node_t::set_platform_name(
        string_t const& SIXTRL_RESTRICT_REF platform_name ) {
            this->m_platform_name = platform_name;
            return st::STATUS_SUCCESS;
    }

    st_status_t base_node_t::set_device_name(
        string_t const& SIXTRL_RESTRICT_REF device_name ) {
        this->m_device_name = device_name;
        return st::STATUS_SUCCESS;
    }

    st_status_t base_node_t::set_description(
        string_t const& SIXTRL_RESTRICT_REF description ) {
        this->m_description = description;
        return st::STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_size_t base_node_t::num_device_strings() const SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( this->m_device_str_kinds.size() ==
                        this->m_device_str_map.size() );
        return this->m_device_str_kinds.size();
    }

    base_node_t::device_str_kind_t const*
    base_node_t::device_string_kinds_begin() const SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( this->m_device_str_kinds.size() ==
                        this->m_device_str_map.size() );
        return ( !this->m_device_str_kinds.empty() )
            ? this->m_device_str_kinds.data() : nullptr;
    }

    base_node_t::device_str_kind_t const*
    base_node_t::device_string_kinds_end() const SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( this->m_device_str_kinds.size() ==
                        this->m_device_str_map.size() );
        return ( !this->m_device_str_kinds.empty() )
            ? this->m_device_str_kinds.data() : nullptr;
    }

    base_node_t::device_str_kind_t base_node_t::device_string_kind(
        st_size_t const idx ) const SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( this->m_device_str_kinds.size() ==
                        this->m_device_str_map.size() );

        return ( idx < this->m_device_str_kinds.size() )
            ? this->m_device_str_kinds[ idx ]
            : SIXTRL_CXX_NAMESPACE::NODE_DEVICE_STRING_KIND_ILLEGAL;
    }

    bool base_node_t::has_device_string_by_kind(
        base_node_t::device_str_kind_t const kind ) const SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( this->m_device_str_kinds.size() ==
                        this->m_device_str_map.size() );

        return ( ( kind != st::NODE_DEVICE_STRING_KIND_ILLEGAL ) &&
                    ( std::find( this->m_device_str_kinds.begin(),
                                this->m_device_str_kinds.end(), kind ) !=
                    this->m_device_str_kinds.end() ) );
    }

    string_t const& base_node_t::device_string_str() const {
        return this->device_string_str_by_kind(
            SIXTRL_CXX_NAMESPACE::NODE_DEVICE_STRING_KIND_DEFAULT );
    }

    str_char_t const* base_node_t::device_string() const SIXTRL_NOEXCEPT {
        return this->device_string_by_kind(
            SIXTRL_CXX_NAMESPACE::NODE_DEVICE_STRING_KIND_DEFAULT );
    }

    string_t const& base_node_t::device_string_str_by_kind(
        st_dev_str_kind_t const kind ) const
    {
        if( kind == st::NODE_DEVICE_STRING_KIND_ILLEGAL )
        {
            throw std::runtime_error( "illegal device string kind" );
        }

        SIXTRL_ASSERT( this->m_device_str_kinds.size() ==
                       this->m_device_str_map.size() );

        auto it = this->m_device_str_map.find( kind );

        if( it == this->m_device_str_map.end() )
        {
            throw std::runtime_error( "device string not available" );
        }

        SIXTRL_ASSERT( std::find( this->m_device_str_kinds.begin(),
            this->m_device_str_kinds.end(), kind ) !=
                this->m_device_str_kinds.end() );

        return it->second;
    }

    str_char_t const* base_node_t::device_string_by_kind( st_dev_str_kind_t
        const kind ) const SIXTRL_NOEXCEPT
    {
        str_char_t const* device_cstring = nullptr;

        if( ( kind != st::NODE_DEVICE_STRING_KIND_ILLEGAL ) &&
            ( this->m_device_str_kinds.size() ==
              this->m_device_str_map.size() ) )
        {
            auto it = this->m_device_str_map.find( kind );

            if( ( it != this->m_device_str_map.end() ) &&
                ( std::find( this->m_device_str_kinds.begin(),
                    this->m_device_str_kinds.end(), kind ) !=
                        this->m_device_str_kinds.end() ) )
            {
                device_cstring = it->second.c_str();
            }
        }

        return device_cstring;
    }

    base_node_t::device_str_kind_t base_node_t::find_device_str_kind(
        string_t const& SIXTRL_RESTRICT_REF device_id_str ) const
    {
        return this->do_find_device_str_kind_for_device_str(
            device_id_str );
    }

    bool base_node_t::check_device_str_format(
        string_t const& SIXTRL_RESTRICT_REF device_id_str,
        base_node_t::device_str_kind_t const kind ) const
    {
        return this->do_check_device_string_with_format( device_id_str, kind );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t base_node_t::set_device_string(
        base_node_t::device_str_kind_t const device_str_kind,
        string_t const& SIXTRL_RESTRICT_REF device_str ) {
        return this->do_set_device_string( device_str_kind, device_str );
    }

    st_status_t base_node_t::remove_device_str(
        base_node_t::device_str_kind_t const device_str_kind ) {
        return this->do_remove_device_string( device_str_kind );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t base_node_t::update_default_device_strings() {
        return this->do_update_default_device_strings();
    }

    void base_node_t::clear() { this->do_clear(); }

    void base_node_t::print(
        std::ostream& SIXTRL_RESTRICT_REF ostr,
        st_print_flags_t const flags ) const
    {
        this->do_print_device_str_section( ostr, flags );
        this->do_print_base_section( ostr, flags );

        if( ( flags & st::NODE_PRINT_FLAGS_EXTENDED_INFO ) ==
                st::NODE_PRINT_FLAGS_EXTENDED_INFO )
        {
            this->do_print_extended_section( ostr, flags );
        }
    }

    string_t base_node_t::to_string( st_print_flags_t const flags ) const
    {
        sstream_t a2str;
        this->print( a2str, flags );
        return a2str.str();
    }

    st_status_t base_node_t::to_string_detailed(
        str_char_t* SIXTRL_RESTRICT out_buffer, st_size_t const out_buf_capacity,
        st_print_flags_t const flags ) const
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( out_buffer != nullptr ) && ( out_buf_capacity > st_size_t{ 1 } ) )
        {
            std::memset( out_buffer, ( int )'\0', out_buf_capacity );
            string_t const temp_str( this->to_string( flags ) );
            if( temp_str.size() < out_buf_capacity )
            {
                std::strncpy( out_buffer,
                    temp_str.c_str(), out_buf_capacity - 1u );
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    st_status_t base_node_t::to_string( str_char_t* SIXTRL_RESTRICT out_buffer,
        size_type const out_buffer_capacity ) const
    {
        return this->to_string_detailed( out_buffer, out_buffer_capacity,
            SIXTRL_CXX_NAMESPACE::NODE_PRINT_FLAGS_NONE );
    }

    st_size_t base_node_t::to_string_required_capacity(
        node_print_flags_t const flags ) const
    {
        string_t const temp_str( this->to_string( flags ) );
        return temp_str.size() + size_type{ 1 };
    }

    /* --------------------------------------------------------------------- */

    base_node_t::BaseNodeInfo( base_node_t::backend_id_t const backend_id ) :
        st::BaseBackendObj( backend_id, st::CLASS_ID_NODE_ID ),
        m_stored_node_id( new st::NodeId( backend_id ) ),
        m_device_str_map(), m_device_str_kinds(),
        m_platform_name(), m_device_name(), m_description()
    {

    }

    base_node_t::BaseNodeInfo( BaseNodeInfo const& SIXTRL_RESTRICT_REF orig ) :
        st::BaseBackendObj( orig ),
        m_stored_node_id( new st::NodeId(
            orig.backend_id(), orig.platform_id(), orig.device_id() ) ),
        m_device_str_map( orig.m_device_str_map ),
        m_device_str_kinds( orig.m_device_str_kinds ),
        m_platform_name( orig.m_platform_name ),
        m_device_name( orig.m_device_name ),
        m_description( orig.m_description )
    {

    }

    BaseNodeInfo& base_node_t::operator=(
        BaseNodeInfo const& SIXTRL_RESTRICT_REF rhs )
    {
        if( &rhs != this )
        {
            st::BaseBackendObj::operator=( rhs );
            SIXTRL_ASSERT( rhs.m_stored_node_id.get() != nullptr );
            this->m_stored_node_id.reset(
                new st::NodeId( *( rhs.m_stored_node_id ) ) );
            this->m_device_str_map = rhs.m_device_str_map;
            this->m_device_str_kinds.assign( rhs.m_device_str_kinds.begin(),
                rhs.m_device_str_kinds.end() );
            this->m_platform_name = rhs.m_platform_name;
            this->m_device_name = rhs.m_device_name;
            this->m_description = rhs.m_description;
        }

        return *this;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    void base_node_t::do_clear()
    {
        SIXTRL_ASSERT( this->m_stored_node_id.get() != nullptr );
        this->m_stored_node_id->clear();
        this->m_device_str_map.clear();
        this->m_device_str_kinds.clear();
        this->m_platform_name.clear();
        this->m_device_name.clear();
        this->m_description.clear();
    }

    st_status_t base_node_t::do_set_device_string(
        base_node_t::device_str_kind_t const kind,
        string_t const& device_str )
    {
        return this->do_set_device_string_base_impl( kind, device_str );
    }

    st_status_t base_node_t::do_remove_device_string(
        base_node_t::device_str_kind_t const kind )
    {
        return this->do_remove_device_string_base_impl( kind );
    }

    st_status_t base_node_t::do_update_default_device_strings()
    {
        return this->do_update_default_device_strings_base_impl();
    }

    base_node_t::device_str_kind_t
    base_node_t::do_find_device_str_kind_for_device_str(
        string_t const& SIXTRL_RESTRICT_REF device_id_str ) const
    {
        base_node_t::device_str_kind_t kind =
            st::NODE_DEVICE_STRING_KIND_ILLEGAL;

        if( base_node_t::DEVICE_ID_STR_HAS_BACKENDID_FORMAT_FOR_BACKEND(
                device_id_str, this->backend_id() ) )
        {
            kind = st::NODE_DEVICE_STRING_KIND_BACKENDID;
        }
        else if( base_node_t::DEVICE_ID_STR_HAS_BACKENDSTR_FORMAT_FOR_BACKEND(
                    device_id_str, this->backend_id() ) )
        {
            kind = st::NODE_DEVICE_STRING_KIND_BACKENDSTR;
        }
        else if( base_node_t::DEVICE_ID_STR_HAS_NOBACKEND_FORMAT( device_id_str ) )
        {
            kind = st::NODE_DEVICE_STRING_KIND_NOBACKEND;
        }
        else if( base_node_t::DEVICE_ID_STR_HAS_NOBACKEND_FORMAT( device_id_str ) )
        {
            kind = st::NODE_DEVICE_STRING_KIND_NOBACKEND;
        }
        else if( base_node_t::DEVICE_ID_STR_HAS_UUID_FORMAT( device_id_str ) )
        {
            kind = st::NODE_DEVICE_STRING_KIND_UUID;
        }
        else if( base_node_t::DEVICE_ID_STR_HAS_PCI_BUS_ID_FORMAT(
            device_id_str ) )
        {
            kind = st::NODE_DEVICE_STRING_KIND_NOBACKEND;
        }

        return kind;
    }

    void base_node_t::do_print_device_str_section(
        std::ostream& SIXTRL_RESTRICT_REF ostr,
        st_print_flags_t const flags ) const
    {
        if( this->m_stored_node_id.get() == nullptr )
        {
            throw std::runtime_error( "no stored node_id available" );
        }

        bool const is_in_global_backend_store = st::BackendsStore_const_global(
            ).has_backend( this->backend_id() );

        if( this->has_device_string_by_kind(
                st::NODE_DEVICE_STRING_KIND_DEFAULT ) )
        {
            ostr << "device_str              : "
                 << this->device_string_by_kind(
                    st::NODE_DEVICE_STRING_KIND_DEFAULT );
        }
        else
        {
            str_char_t temp_device_str[ 64 ];
            st_status_t status = this->m_stored_node_id->to_string_using_format(
                &temp_device_str[ 0 ], 64u, st::NODE_ID_STR_FORMAT_DEFAULT );

            if( status == st::STATUS_SUCCESS )
            {
                ostr << "device_str              : " << temp_device_str;
            }
            else if(
                ( is_in_global_backend_store ) &&
                ( st::BackendsStore_const_global().has_backend_string(
                    this->backend_id() ) ) )
            {
                ostr << "backend                 : "
                     << st::BackendsStore_const_global().backend_string_str(
                         this->backend_id() );
            }
            else
            {
                ostr << "backend_id                 : " << this->backend_id();
            }
        }

        if( ( flags & st::NODE_PRINT_FLAGS_DEFAULT_NODE ) ==
                st::NODE_PRINT_FLAGS_DEFAULT_NODE )
        {
            ostr << " [DEFAULT]";
        }

        if( ( flags & st::NODE_PRINT_FLAGS_SELECTED_NODE ) ==
                st::NODE_PRINT_FLAGS_SELECTED_NODE )
        {
            ostr << " [SELECTED]";
        }

        ostr << "\r\n";

        if( this->num_device_strings() > st_size_t{ 0 } )
        {
            auto it = this->device_string_kinds_begin();
            if( it != nullptr )
            {
                auto end = this->device_string_kinds_end();
                for( ; it != end ; ++it )
                {
                    if( *it == st::NODE_DEVICE_STRING_KIND_DEFAULT )
                    {
                        continue;
                    }

                    switch( *it )
                    {
                        case st::NODE_DEVICE_STRING_KIND_NOBACKEND:
                        {
                            ostr << "short device string     : ";
                            break;
                        }

                        case st::NODE_DEVICE_STRING_KIND_BACKENDID:
                        {
                            ostr << "archid device string    : ";
                            break;
                        }

                        case st::NODE_DEVICE_STRING_KIND_BACKENDSTR:
                        {
                            ostr << "archstr device string   : ";
                            break;
                        }

                        case st::NODE_DEVICE_STRING_KIND_UUID:
                        {
                            ostr << "device uuid             : ";
                            break;
                        }

                        case st::NODE_DEVICE_STRING_KIND_PCI_BUS_ID:
                        {
                            ostr << "device pci bus id       : ";
                            break;
                        }

                        default:
                        {
                            ostr << "unknown device string   : ";
                        }
                    };

                    ostr << this->device_string_by_kind( *it ) << "\r\n";
                }
            }
        }
    }

    void base_node_t::do_print_base_section(
        std::ostream& SIXTRL_RESTRICT_REF ostr,
        st_print_flags_t const SIXTRL_UNUSED( flags ) ) const
    {
        if( this->m_stored_node_id.get() == nullptr )
        {
            throw std::runtime_error( "no stored node_id available" );
        }

        ostr << "platform                : "
             << this->m_stored_node_id->platform_id() << "\r\n"
             << "platform_name           : "
             << this->m_platform_name << "\r\n"
             << "device_id               : "
             << this->m_stored_node_id->device_id() << "\r\n"
             << "device_name             : "
             << this->m_device_name << "\r\n";

        if( !this->m_description.empty() )
        {
            ostr << "description             :\r\n"
                 << this->m_description << "\r\n";
        }
    }

    void base_node_t::do_print_extended_section(
        std::ostream& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( ostr ),
        st_print_flags_t const SIXTRL_UNUSED( flags ) ) const
    {
        return;
    }

    st_status_t base_node_t::update_stored_node_id(
        std::unique_ptr< st_node_id_t > node_id_to_store ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( node_id_to_store.get() != nullptr ) &&
            ( ( node_id_to_store->backend_id() == this->backend_id() ) ||
              ( node_id_to_store->backend_id() == st::BACKEND_UNDEFINED ) ) )
        {
            status = st::STATUS_SUCCESS;

            if( node_id_to_store->backend_id() == st::BACKEND_UNDEFINED )
            {
                status = node_id_to_store->set_backend_id( this->backend_id() );
            }

            if( status == st::STATUS_SUCCESS )
            {
                this->m_stored_node_id = std::move( node_id_to_store );
                status = this->do_update_default_device_strings();
            }
        }

        return status;
    }


    bool base_node_t::do_check_device_string_with_format(
        string_t const& SIXTRL_RESTRICT_REF device_str,
        base_node_t::device_str_kind_t const kind ) const
    {
        bool is_consistent = false;

        if( ( !device_str.empty() ) &&
            ( kind != st::NODE_DEVICE_STRING_KIND_ILLEGAL ) &&
            ( this->m_stored_node_id.get() != nullptr ) )
        {
            using this_t = base_node_t;

            switch( kind )
            {
                case st::NODE_DEVICE_STRING_KIND_NOBACKEND:
                {
                    is_consistent = this_t::DEVICE_ID_STR_HAS_NOBACKEND_FORMAT(
                        device_str );
                    break;
                }

                case st::NODE_DEVICE_STRING_KIND_BACKENDID:
                {
                    is_consistent = this_t::DEVICE_ID_STR_HAS_BACKENDID_FORMAT(
                        device_str );
                    break;
                }

                case st::NODE_DEVICE_STRING_KIND_BACKENDSTR:
                {
                    is_consistent = this_t::DEVICE_ID_STR_HAS_BACKENDSTR_FORMAT(
                        device_str );
                    break;
                }

                case st::NODE_DEVICE_STRING_KIND_UUID:
                {
                    is_consistent = this_t::DEVICE_ID_STR_HAS_UUID_FORMAT(
                        device_str );
                    break;
                }

                case st::NODE_DEVICE_STRING_KIND_PCI_BUS_ID:
                {
                    is_consistent = this_t::DEVICE_ID_STR_HAS_PCI_BUS_ID_FORMAT(
                        device_str );
                    break;
                }

                default:
                {
                    SIXTRL_ASSERT(
                        ( kind == st::NODE_DEVICE_STRING_KIND_NOBACKEND ) ||
                        ( kind == st::NODE_DEVICE_STRING_KIND_BACKENDID ) ||
                        ( kind == st::NODE_DEVICE_STRING_KIND_BACKENDSTR ) ||
                        ( kind == st::NODE_DEVICE_STRING_KIND_UUID ) ||
                        ( kind == st::NODE_DEVICE_STRING_KIND_PCI_BUS_ID ) );

                    is_consistent = false;
                }
            };
        }

        return is_consistent;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t base_node_t::do_set_device_string_base_impl(
        base_node_t::device_str_kind_t const kind,
        string_t const& SIXTRL_RESTRICT_REF device_str )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( !device_str.empty() ) &&
            ( kind != st::NODE_DEVICE_STRING_KIND_ILLEGAL ) &&
            ( this->m_device_str_map.size() ==
              this->m_device_str_kinds.size() ) )
        {
            auto it = this->m_device_str_map.find( kind );

            if( it == this->m_device_str_map.end() )
            {
                SIXTRL_ASSERT( std::find( this->m_device_str_kinds.begin(),
                    this->m_device_str_kinds.end(), kind ) ==
                        this->m_device_str_kinds.end() );

                auto ret = this->m_device_str_map.emplace(
                    std::make_pair( kind, device_str ) );

                if( ret.second )
                {
                    this->m_device_str_kinds.push_back( kind );
                    status = st::STATUS_SUCCESS;
                }
            }
            else
            {
                SIXTRL_ASSERT( std::find( this->m_device_str_kinds.begin(),
                    this->m_device_str_kinds.end(), kind ) !=
                        this->m_device_str_kinds.end() );

                it->second = device_str;
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    st_status_t base_node_t::do_remove_device_string_base_impl(
        base_node_t::device_str_kind_t const kind ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( kind != st::NODE_DEVICE_STRING_KIND_ILLEGAL ) &&
            ( this->m_device_str_kinds.size() ==
              this->m_device_str_map.size() ) )
        {
            auto map_it = this->m_device_str_map.find( kind );
            auto kind_it = std::find( this->m_device_str_kinds.begin(),
                this->m_device_str_kinds.end(), kind );

            if( ( map_it != this->m_device_str_map.end() ) &&
                ( kind_it != this->m_device_str_kinds.end() ) )
            {
                this->m_device_str_map.erase( map_it );
                this->m_device_str_kinds.erase( kind_it );
                status = st::STATUS_SUCCESS;
            }
            else if( ( map_it == this->m_device_str_map.end() ) &&
                     ( kind_it == this->m_device_str_kinds.end() ) )
            {
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    st_status_t base_node_t::do_update_default_device_strings_base_impl()
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( this->m_stored_node_id.get() != nullptr )
        {
            string_t const device_str(
                this->m_stored_node_id->to_string_using_format(
                    st::NODE_ID_STR_FORMAT_DEFAULT ) );

            if( !device_str.empty() )
            {
                status = this->do_set_device_string_base_impl(
                    st::NODE_DEVICE_STRING_KIND_DEFAULT, device_str );
            }
        }

        return status;
    }
} /* ns: SIXTRL_CXX_NAMESPACE */


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                Exported Plugin C-API :: Functions               !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

void NS(NodeInfo_delete)( ::NS(BaseNodeInfo)*
    SIXTRL_RESTRICT node_info ) SIXTRL_NOEXCEPT
{
   delete node_info;
}

#endif /* C++, Host */
