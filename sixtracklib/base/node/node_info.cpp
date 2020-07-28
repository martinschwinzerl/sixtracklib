#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/node/node_info.h"
    #include "sixtracklib/base/node/tools.h"
    #include "sixtracklib/base/architecture/architectures_store.h"
    #include "sixtracklib/base/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <cstring>
        #include <string>
        #include <iomanip>
        #include <ostream>
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
}

namespace SIXTRL_CXX_NAMESPACE
{
    base_node_t::BaseNodeInfo( base_node_t::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF arch_str ) :
        st::BaseArchObj( arch_id, st::CLASS_ID_NODE_ID ),
        m_stored_node_id( new st::NodeId( arch_id ) ),
        m_device_str_map(), m_device_str_kinds(),
        m_platform_name(), m_device_name(), m_description()
    {

    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_c_node_id_t base_node_t::node_id_data() const SIXTRL_NOEXCEPT
    {
        if( this->m_stored_node_id.get() != nullptr )
        {
            return c_node_id_t{ this->arch_id(),
                                this->m_stored_node_id->platform_id(),
                                this->m_stored_node_id->device_id() };
        }

        return st_c_node_id_t{ this->arch_id(),
            st::NODE_ILLEGAL_PLATFORM_ID, st::NODE_ILLEGAL_DEVICE_ID };
    }

    std::string const& base_node_t::device_string_str_by_kind(
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

    char const* base_node_t::device_string_by_kind( st_dev_str_kind_t
        const kind ) const SIXTRL_NOEXCEPT
    {
        char const* device_cstring = nullptr;

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

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t base_node_t::to_string_detailed(
        char* SIXTRL_RESTRICT out_buffer, st_size_t const out_buf_capacity,
        st_print_flags_t const flags ) const
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( out_buffer != nullptr ) && ( out_buf_capacity > st_size_t{ 1 } ) )
        {
            std::memset( out_buffer, ( int )'\0', out_buf_capacity );
            std::string const temp_str( this->to_string( flags ) );
            if( temp_str.size() < out_buf_capacity )
            {
                std::strncpy( out_buffer,
                    temp_str.c_str(), out_buf_capacity - 1u );
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

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
        std::string const& device_str )
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

    void base_node_t::do_print_device_str_section(
        std::ostream& SIXTRL_RESTRICT_REF ostr,
        st_print_flags_t const flags ) const
    {
        if( this->m_stored_node_id.get() == nullptr )
        {
            throw std::runtime_error( "no stored node_id available" );
        }

        if( !st::ArchitecturesStore_const_global().has_architecture(
                this->arch_id() ) )
        {
            throw std::runtime_error( "arch_id unknown/not available" );
        }

        SIXTRL_ASSERT( st::Node_is_device_str_kind_a_node_id_format(
            st::NODE_DEVICE_STRING_KIND_DEFAULT ) );

        SIXTRL_ASSERT( this->m_stored_node_id.get() != nullptr );

        if( this->has_device_string_by_kind(
                st::NODE_DEVICE_STRING_KIND_DEFAULT ) )
        {
            ostr << "device_str              : "
                 << this->device_string_by_kind(
                    st::NODE_DEVICE_STRING_KIND_DEFAULT );
        }
        else
        {
            char temp_device_str[ 64 ];
            st_status_t status = this->m_stored_node_id->to_string_using_format(
                &temp_device_str[ 0 ], 64u,
                st::Node_convert_device_str_kind_to_node_id_format(
                    st::NODE_DEVICE_STRING_KIND_DEFAULT ) );

            if( status == st::STATUS_SUCCESS )
            {
                ostr << "device_str              : " << temp_device_str;
            }
            else if( st::ArchitecturesStore_const_global().has_arch_string(
                this->arch_id() ) )
            {
                ostr << "arch                    : "
                     << st::ArchitecturesStore_const_global().arch_string_str(
                         this->arch_id() );
            }
            else
            {
                ostr << "arch_id                 : " << this->arch_id();
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
                        case st::NODE_DEVICE_STRING_KIND_NOARCH:
                        {
                            ostr << "short device string     : ";
                            break;
                        }

                        case st::NODE_DEVICE_STRING_KIND_ARCHID:
                        {
                            ostr << "archid device string    : ";
                            break;
                        }

                        case st::NODE_DEVICE_STRING_KIND_ARCHSTR:
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
        base_node_t::print_flags_t const SIXTRL_UNUSED( flags ) ) const
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
        std::ostream& SIXTRL_RESTRICT_REF ostr,
        st_print_flags_t const flags ) const
    {
        return;
    }

    st_status_t base_node_t::update_stored_node_id(
        std::unique_ptr< st_node_id_t > node_id_to_store ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( node_id_to_store.get() != nullptr ) &&
            ( ( node_id_to_store->arch_id() == this->arch_id() ) ||
              ( node_id_to_store->arch_id() == st::ARCHITECTURE_UNDEFINED ) ) )
        {
            status = st::STATUS_SUCCESS;

            if( node_id_to_store->arch_id() == st::ARCHITECTURE_UNDEFINED )
            {
                status = node_id_to_store->set_arch_id( this->arch_id() );
            }

            if( status == st::STATUS_SUCCESS )
            {
                this->m_stored_node_id = std::move( node_id_to_store );
                status = this->do_update_default_device_strings();
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t base_node_t::do_set_device_string_base_impl(
        base_node_t::device_str_kind_t const kind,
        std::string const& SIXTRL_RESTRICT_REF device_str )
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
            SIXTRL_ASSERT( st::Node_is_device_str_kind_a_node_id_format(
                st::NODE_DEVICE_STRING_KIND_DEFAULT ) );

            std::string const device_str(
                this->m_stored_node_id->to_string_using_format(
                    st::Node_convert_device_str_kind_to_node_id_format(
                        st::NODE_DEVICE_STRING_KIND_DEFAULT ) ) );

            if( !device_str.empty() )
            {
                status = this->do_set_device_string_base_impl(
                    st::NODE_DEVICE_STRING_KIND_DEFAULT, device_str );
            }
        }

        return status;
    }
}

#endif /* C++, Host */
