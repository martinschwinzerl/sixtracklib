#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/node/node_id.h"
    #include "sixtracklib/base/node/tools.h"
    #include "sixtracklib/base/architecture/architectures_store.h"
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
        using st_arch_id_t = this_t::arch_id_t;
        using st_device_id_t = this_t::device_id_t;
        using st_platform_id_t = this_t::platform_id_t;
    }

    this_t::NodeId( st_arch_id_t const arch_id,
        st_platform_id_t const platform_id,
        st_device_id_t const device_id ) SIXTRL_NOEXCEPT
    {
        this->m_arch_id = arch_id;
        this->m_platform_id = platform_id;
        this->m_device_id = device_id;
    }

    this_t::NodeId( std::string const& SIXTRL_RESTRICT_REF device_str )
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

    this_t::NodeId( std::string const& SIXTRL_RESTRICT_REF device_str,
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

    std::string this_t::to_string_using_format(
        str_format_t const str_format ) const
    {
        std::ostringstream a2str;

        if( this->do_print( a2str, str_format ) != st::STATUS_SUCCESS )
        {
            throw std::runtime_error( "unable to print node_id" );
        }

        return a2str.str();
    }

    st_status_t this_t::to_string_using_format(
        char* SIXTRL_RESTRICT device_str, st_size_t const device_str_capacity,
        str_format_t const format ) const
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( device_str != nullptr ) &&
            ( device_str_capacity > st_size_t{ 1 } ) )
        {
            std::string const temp_device_str(
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

    void this_t::do_clear()
    {
        this->m_arch_id = st::ARCHITECTURE_ILLEGAL;
        this->m_platform_id = this_t::ILLEGAL_PLATFORM_ID;
        this->m_device_id = this_t::ILLEGAL_DEVICE_ID;
    }

    str_format_t this_t::do_find_device_string_format(
        std::string const& device_id_str ) const
    {
        return this->do_find_device_string_format_base_impl( device_id_str );
    }

    st_status_t this_t::do_parse_device_str(
        std::string const& SIXTRL_RESTRICT_REF device_str,
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
            switch( device_str_format )
            {
                case st::NODE_ID_STR_FORMAT_NOARCH:
                {
                    ostr << this->m_platform_id << ":" << this->m_device_id;
                    status = st::STATUS_SUCCESS;
                    break;
                }

                case st::NODE_ID_STR_FORMAT_ARCHID:
                {
                    if( ( this->m_arch_id != st::ARCHITECTURE_ILLEGAL ) &&
                        ( st::ArchitecturesStore_const_global(
                            ).has_architecture( this->m_arch_id ) ) )
                    {
                        ostr << this->m_arch_id << ":" << this->m_platform_id
                             << ":" << this->m_device_id;
                        status = st::STATUS_SUCCESS;
                    }

                    break;
                }

                case st::NODE_ID_STR_FORMAT_ARCHSTR:
                {
                    if( ( this->m_arch_id != st::ARCHITECTURE_ILLEGAL ) &&
                        ( st::ArchitecturesStore_const_global(
                            ).has_architecture( this->m_arch_id ) ) &&
                        ( st::ArchitecturesStore_const_global(
                            ).has_arch_string( this->m_arch_id ) ) &&
                        ( st::ArchitecturesStore_const_global(
                            ).arch_string_str( this->m_arch_id ).empty() ) )
                    {
                        ostr << st::ArchitecturesStore_const_global(
                                ).arch_string_str( this->m_arch_id ) << ":"
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
        std::string const& device_id_str ) const
    {
        return st::Node_find_node_id_format( device_id_str );
    }

    st_status_t this_t::do_parse_device_str_base_impl(
        std::string const& SIXTRL_RESTRICT_REF device_str,
        str_format_t const format ) SIXTRL_NOEXCEPT
    {
        return st::NodeId_parse_using_format( *this, device_str, format );
    }
}

#endif /* C++, Host */

