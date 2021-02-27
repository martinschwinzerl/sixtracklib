#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_info.h"
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using ninfo_type = st::NodeInfoBase;
        using node_id_type = st::NodeId;
    }

    ninfo_type::status_type ninfo_type::do_print_to_stream(
        std::ostream& SIXTRL_RESTRICT_REF output,
        node_id_type::str_format_type const node_id_str_format,
        const node_id_type *const ptr_default_node_id,
        const node_id_type *const ptr_selected_node_id ) const
    {
        output << "Node Id            : ";
        this->node_id().to_stream(
            output, node_id_str_format, this->backend_id() );

        if( ( ptr_default_node_id != nullptr ) &&
            ( this->node_id().compare( *ptr_default_node_id ) == 0 ) )
        {
            output << " [ DEFAULT ]";
        }

        if( ( ptr_selected_node_id != nullptr ) &&
            ( this->node_id().compare( *ptr_selected_node_id ) == 0 ) )
        {
            output << " [SELECTED]";
        }

        output << "\r\nPlatform           : ";

        if( this->has_platform_name() )
        {
            output << this->platform_name_str();
        }
        else
        {
            output << "n/a";
        }

        output << "\r\nDevice             : ";

        if( this->has_device_name() )
        {
            output << this->device_name_str();
        }
        else
        {
            output << "n/a";
        }

        if( this->has_description() )
        {
            output << "\r\nDescription        : "
                   << this->description_str();
        }

        output << "\r\n";

        return st::STATUS_SUCCESS;
    }

} /* end: namespace SIXTRL_CXX_NAMESPACE */

::NS(backend_id_type) NS(NodeInfo_backend_id)( SIXTRL_ARGPTR_DEC const
    NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT
{
    return ( info != nullptr )
        ? info->backend_id() : SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE;
}

char const* NS(NodeInfo_backend_str)( SIXTRL_ARGPTR_DEC const
    ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
    return ( info != nullptr ) ? info->backend_cstr() : nullptr; }

::NS(derived_class_id_type) NS(NodeInfo_base_class_id)( SIXTRL_ARGPTR_DEC const
    ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
    return ( info != nullptr )
        ? info->base_class_id() : SIXTRL_CXX_NAMESPACE::DERIVED_CLASS_ID_NONE; }

::NS(derived_class_id_type) NS(NodeInfo_required_class_id)( SIXTRL_ARGPTR_DEC
    const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
    return ( info != nullptr )
        ? info->derived_class_id()
        : SIXTRL_CXX_NAMESPACE::DERIVED_CLASS_ID_NONE;
}

/* ------------------------------------------------------------------------- */

void NS(NodeInfo_delete)( ::NS(NodeInfoBase)* SIXTRL_RESTRICT
    node_info ) SIXTRL_NOEXCEPT
{
    delete node_info;
}

::NS(NodeId) const* NS(NodeInfo_const_node_id)( SIXTRL_ARGPTR_DEC const
    ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
        return ( info != nullptr ) ? &info->node_id() : nullptr; }

::NS(NodeId)* NS(NodeInfo_node_id)( SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)*
    SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
        return ( info != nullptr ) ? &info->node_id() : nullptr; }

::NS(node_platform_id_type) NS(NodeInfo_platform_id)( SIXTRL_ARGPTR_DEC const
    ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
        return ( info != nullptr )
            ? info->platform_id()
            : SIXTRL_CXX_NAMESPACE::NodeId::ILLEGAL_PLATFORM_ID;
}

void NS(NodeInfo_set_platform_id)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    ::NS(node_platform_id_type) const platform_id ) SIXTRL_NOEXCEPT {
    if( info != nullptr ) info->set_platform_id( platform_id ); }

::NS(node_device_id_type) NS(NodeInfo_device_id)( SIXTRL_ARGPTR_DEC const
    ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
        return ( info != nullptr )
            ? info->device_id()
            : SIXTRL_CXX_NAMESPACE::NodeId::ILLEGAL_DEVICE_ID;
}

void NS(NodeInfo_set_device_id)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    ::NS(node_device_id_type) const device_id ) SIXTRL_NOEXCEPT {
    if( info != nullptr ) info->set_device_id( device_id ); }

bool NS(NodeInfo_has_node_index)( SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase)
    *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
        return ( ( info != nullptr ) && ( info->has_node_index() ) ); }

::NS(node_index_type) NS(NodeInfo_node_index)( SIXTRL_ARGPTR_DEC const
    ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
    return ( info != nullptr )
        ? info->node_index()
        : SIXTRL_CXX_NAMESPACE::NodeId::ILLEGAL_INDEX;
}

void NS(NodeInfo_set_node_index)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    ::NS(node_index_type) node_index ) SIXTRL_NOEXCEPT {
    if( info != nullptr ) info->set_node_index( node_index ); }

bool NS(NodeInfo_is_default_node)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT default_node_id
) SIXTRL_NOEXCEPT {
    return ( ( info != nullptr ) && ( default_node_id != nullptr ) &&
             ( info->node_id().compare( *default_node_id ) == 0 ) );
}

bool NS(NodeInfo_is_selected_node)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT selected_node_id
) SIXTRL_NOEXCEPT {
    return ( ( info != nullptr ) && ( selected_node_id != nullptr ) &&
             ( info->node_id().compare( *selected_node_id ) == 0 ) );
}

bool NS(NodeInfo_has_platform_name)( SIXTRL_ARGPTR_DEC const
    ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
        return ( ( info != nullptr ) && ( info->has_platform_name() ) ); }

char const* NS(NodeInfo_platform_name)( SIXTRL_ARGPTR_DEC const
    ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
        return ( info != nullptr ) ? info->platform_name() : nullptr; }

void NS(NodeInfo_set_platform_name)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT platform_name ) {
    if( ( info != nullptr ) && ( platform_name != nullptr ) &&
        ( std::strlen( platform_name ) > 0u ) )
    {
        info->set_platform_name( std::string{ platform_name } );
    }
    else if( info != nullptr )
    {
        info->set_platform_name( std::string{} );
    }
}

bool NS(NodeInfo_has_device_name)( SIXTRL_ARGPTR_DEC const
    ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
        return ( ( info != nullptr ) && ( info->has_device_name() ) ); }

char const* NS(NodeInfo_device_name)( SIXTRL_ARGPTR_DEC const
    ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
        return ( info != nullptr ) ? info->device_name() : nullptr; }

void NS(NodeInfo_set_device_name)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT device_name ) {
    if( ( info != nullptr ) && ( device_name != nullptr ) &&
        ( std::strlen( device_name ) > 0u ) )
    {
        info->set_device_name( std::string{ device_name } );
    }
    else if( info != nullptr )
    {
        info->set_device_name( std::string{} );
    }
}

bool NS(NodeInfo_has_description)( SIXTRL_ARGPTR_DEC const
    ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
        return ( ( info != nullptr ) && ( info->has_description() ) ); }

char const* NS(NodeInfo_description)( SIXTRL_ARGPTR_DEC const
    ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT {
        return ( info != nullptr ) ? info->description() : nullptr; }

void NS(NodeInfo_set_description)(
    SIXTRL_ARGPTR_DEC ::NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT description ) {
    if( ( info != nullptr ) && ( description != nullptr ) &&
        ( std::strlen( description ) > 0u ) )
    {
        info->set_description( std::string{ description } );
    }
    else if( info != nullptr )
    {
        info->set_description( std::string{} );
    }
}

::NS(size_type) NS(NodeInfo_required_string_capacity)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    return NS(NodeInfo_required_string_capacity_detailed)( info,
        SIXTRL_CXX_NAMESPACE::NodeId::DEFAULT_STR_FORMAT, nullptr, nullptr );
}

::NS(size_type) NS(NodeInfo_required_string_capacity_detailed)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::NS(node_id_str_fmt_type) const node_id_str_format,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT default_node_id,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT select_node_id )
{
    ::NS(size_type) node_info_str_capacity = ::NS(size_type){ 0 };

    if( info != nullptr )
    {
        std::ostringstream a2str;
        ::NS(status_type) const status = info->to_stream( a2str,
            node_id_str_format, default_node_id, select_node_id );

        if( ( status == ::NS(STATUS_SUCCESS) ) && ( !a2str.str().empty() ) )
        {
            node_info_str_capacity = a2str.str().size() + ::NS(size_type){ 1 };
        }
    }

    return node_info_str_capacity;
}

::NS(status_type) NS(NodeInfo_to_string)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    char* SIXTRL_RESTRICT node_info_str,
    ::NS(size_type) const node_info_str_capacity ) {
    return ::NS(NodeInfo_to_string_detailed)( info, node_info_str,
        node_info_str_capacity, SIXTRL_CXX_NAMESPACE::NodeId::DEFAULT_STR_FORMAT,
            nullptr, nullptr ); }

::NS(status_type) NS(NodeInfo_to_string_detailed)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    char* SIXTRL_RESTRICT node_info_str,
    NS(size_type) const node_info_str_capacity,
    ::NS(node_id_str_fmt_type) const node_id_str_format,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT default_node_id,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT selected_node_id )
{
    ::NS(status_type) status = ::NS(STATUS_GENERAL_FAILURE);

    if( info != nullptr )
    {
        std::ostringstream a2str;
        status = info->to_stream( a2str, node_id_str_format,
            default_node_id, selected_node_id );

        if( ( status == ::NS(STATUS_SUCCESS) ) &&
            ( node_info_str != nullptr ) &&
            ( node_info_str_capacity > ::NS(size_type){ 0 } ) &&
            ( node_info_str_capacity > a2str.str().size() ) )
        {
            std::memset( node_info_str, ( int )'\0', node_info_str_capacity );
            std::strncpy( node_info_str, a2str.str().c_str(),
                          node_info_str_capacity - ::NS(size_type){ 1 } );
        }
        else if( status == ::NS(STATUS_SUCCESS) )
        {
            status = ::NS(STATUS_GENERAL_FAILURE);
        }
    }

    return status;
}

void NS(NodeInfo_print)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::FILE* SIXTRL_RESTRICT output ) {
    ::NS(NodeInfo_print_detailed)( info, output,
        SIXTRL_CXX_NAMESPACE::NodeId::DEFAULT_STR_FORMAT, nullptr, nullptr ); }

void NS(NodeInfo_print_detailed)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::FILE* SIXTRL_RESTRICT output,
    ::NS(node_id_str_fmt_type) const node_id_str_format,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT default_node_id,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT selected_node_id )
{
    std::ostringstream a2str;

    if( ( info != nullptr ) && ( output != nullptr ) &&
        ( ::NS(STATUS_SUCCESS) == info->to_stream( a2str, node_id_str_format,
            default_node_id, selected_node_id ) ) )
    {
        std::fprintf( output, "%s", a2str.str().c_str() );
    }
}

void NS(NodeInfo_print_out)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info )
{
    ::NS(NodeInfo_print)( info, ::stdout );
}

void NS(NodeInfo_print_out_detailed)(
    SIXTRL_ARGPTR_DEC const ::NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    ::NS(node_id_str_fmt_type) const node_id_str_format,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT default_node_id,
    SIXTRL_ARGPTR_DEC const ::NS(NodeId) *const SIXTRL_RESTRICT selected_node_id )
{
    ::NS(NodeInfo_print_detailed)(
        info, ::stdout, node_id_str_format, default_node_id, selected_node_id );
}

#endif /* C++, Host */
