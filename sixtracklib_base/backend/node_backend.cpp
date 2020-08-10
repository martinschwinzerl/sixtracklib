#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/backend/node_backend.h"
    #include "sixtracklib_base/backend/backend.h"
    #include "sixtracklib_base/backend/dlib_loader.h"
    #include "sixtracklib_base/node/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUODE ) && defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <regex>
    #include <sstream>
    #include <cstring>
    #include <set>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using this_t = st::BaseNodeBackend;
        using st_node_info_t = this_t::node_info_t;
        using st_node_id_t = this_t::node_info_t::node_id_t;
        using c_node_id_t = this_t::c_node_id_t;
        using string_t = this_t::string_type;
        using fs_string_t = this_t::fs_string_type;
    }

    constexpr this_t::be_symbol_id_t this_t::SYMBOL_ID_CREATE_NODE_INFO;
    constexpr this_t::be_symbol_id_t this_t::SYMBOL_ID_DELETE_NODE_INFO;
    constexpr this_t::be_symbol_id_t this_t::SYMBOL_ID_GET_TOTAL_NUM_NODES;
    constexpr this_t::be_symbol_id_t this_t::SYMBOL_ID_GET_ALL_NODE_IDS;

    this_t::managed_base_node_info_t this_t::create_node_info(
        this_t::platform_id_t const platform_id,
        this_t::device_id_t const device_id )
    {
        if( this->m_delete_node_info_fn == nullptr )
        {
            throw std::runtime_error( "delete_node_info_fn symbol required!" );
        }

        return ( ( this->m_create_node_info_fn != nullptr ) &&
                 ( platform_id != st::NODE_ILLEGAL_PLATFORM_ID ) &&
                 ( device_id != st::NODE_ILLEGAL_DEVICE_ID ) )
            ? this_t::managed_base_node_info_t{
                this->m_create_node_info_fn( platform_id, device_id ),
                this->m_delete_node_info_fn }
            : this_t::managed_base_node_info_t{
                nullptr, this->m_delete_node_info_fn };
    }

    st_size_t this_t::total_num_nodes() const
    {
        return ( this->m_get_total_num_nodes_fn != nullptr )
            ? this->m_get_total_num_nodes_fn() : st_size_t{ 0 };
    }

    st_size_t this_t::all_node_ids( c_node_id_t* SIXTRL_RESTRICT node_ids_begin,
        st_size_t const max_num_node_ids ) const
    {
        return ( this->m_get_all_node_ids_fn != nullptr )
            ? this->m_get_all_node_ids_fn( node_ids_begin, max_num_node_ids )
            : st_size_t{ 0 };
    }

    this_t::size_type this_t::num_available_nodes() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->has_nodes() );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_ILLEGAL );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_UNDEFINED );
        SIXTRL_ASSERT( this->m_node_infos.size() == this->m_node_ids.size() );
        SIXTRL_ASSERT( this->m_node_infos.size() ==
                       this->m_node_id_to_node_info_map.size() );

        return this->m_node_ids.size();
    }

    this_t::node_info_t const* const*
    this_t::base_node_infos_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->has_nodes() );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_ILLEGAL );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_UNDEFINED );
        SIXTRL_ASSERT( this->m_node_infos.size() == this->m_node_ids.size() );
        SIXTRL_ASSERT( this->m_node_infos.size() ==
                       this->m_node_id_to_node_info_map.size() );

        return ( !this->m_node_infos.empty() )
            ? this->m_node_infos.data() : nullptr;
    }

    this_t::node_info_t const* const*
    this_t::base_node_infos_end() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->has_nodes() );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_ILLEGAL );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_UNDEFINED );
        SIXTRL_ASSERT( this->m_node_infos.size() == this->m_node_ids.size() );
        SIXTRL_ASSERT( this->m_node_infos.size() ==
                       this->m_node_id_to_node_info_map.size() );

        auto end_ptr = this->base_node_infos_begin();
        if( end_ptr != nullptr )
            std::advance( end_ptr, this->m_node_infos.size() );

        return end_ptr;
    }

    this_t::node_info_t const* this_t::base_node_info(
        this_t::size_type const idx ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->has_nodes() );
        SIXTRL_ASSERT( this->m_node_infos.size() == this->m_node_ids.size() );
        SIXTRL_ASSERT( this->m_node_infos.size() ==
                       this->m_node_id_to_node_info_map.size() );

        return ( idx < this->m_node_infos.size() )
            ? this->m_node_infos[ idx ] : nullptr;
    }

    this_t::node_info_t const* this_t::base_node_info(
        this_t::platform_id_t const platform_id,
        this_t::device_id_t const device_id ) const SIXTRL_NOEXCEPT
    {
        this_t::node_info_t const* ptr_node_info = nullptr;

        SIXTRL_ASSERT( this->has_nodes() );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_ILLEGAL );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_UNDEFINED );
        SIXTRL_ASSERT( this->m_node_infos.size() ==
                       this->m_node_id_to_node_info_map.size() );

        auto it = this->m_node_id_to_node_info_map.find(
            this_t::c_node_id_t{ this->backend_id(), platform_id, device_id } );

        if( it != this->m_node_id_to_node_info_map.end() )
        {
            SIXTRL_ASSERT( device_id != st_node_id_t::ILLEGAL_DEVICE_ID );
            SIXTRL_ASSERT( platform_id != st_node_id_t::ILLEGAL_PLATFORM_ID );

            ptr_node_info = it->second.get();

            SIXTRL_ASSERT( ( ptr_node_info == nullptr ) ||
                ( ( ptr_node_info->platform_id() == platform_id ) &&
                  ( ptr_node_info->device_id() == device_id ) &&
                  ( ptr_node_info->backend_id() == this->backend_id() ) ) );

            SIXTRL_ASSERT( ( ptr_node_info == nullptr ) ||
                ( std::find( this->m_node_ids.begin(), this->m_node_ids.end(),
                    this_t::c_node_id_t{ this->backend_id(), platform_id,
                        device_id } ) != this->m_node_ids.end() ) );
        }

        return ptr_node_info;
    }

    this_t::c_node_id_t const* this_t::c_node_ids_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->has_nodes() );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_ILLEGAL );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_UNDEFINED );
        SIXTRL_ASSERT( this->m_node_infos.size() ==
                       this->m_node_id_to_node_info_map.size() );
        SIXTRL_ASSERT( this->m_node_ids.size() == this->m_node_infos.size() );

        return ( !this->m_node_ids.empty() ) ? this->m_node_ids.data() : nullptr;
    }

    this_t::c_node_id_t const* this_t::c_node_ids_end() const SIXTRL_NOEXCEPT
    {
        auto end_ptr = this->c_node_ids_begin();
        if( end_ptr != nullptr )
            std::advance( end_ptr, this->m_node_ids.size() );
        return end_ptr;
    }

    this_t::node_info_t const* this_t::base_node_info_by_str(
        string_t const& SIXTRL_RESTRICT_REF node_id_str ) const SIXTRL_NOEXCEPT
    {
        this_t::node_info_t const* ptr_node_info = nullptr;

        SIXTRL_ASSERT( this->has_nodes() );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_ILLEGAL );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_UNDEFINED );
        SIXTRL_ASSERT( this->m_node_infos.size() ==
                       this->m_node_id_to_node_info_map.size() );

        if( ( !this->m_node_infos.empty() ) &&
            (  this->m_node_infos[ 0 ] != nullptr ) &&
            (  this->m_node_infos[ 0 ]->backend_id() == this->backend_id() ) )
        {
            ptr_node_info = this->base_node_info_by_str_detailed(
                node_id_str, this->m_node_infos[ 0 ]->find_device_str_kind(
                    node_id_str ) );
        }

        return ptr_node_info;
    }

    this_t::node_info_t const* this_t::base_node_info_by_str_detailed(
        string_t const& SIXTRL_RESTRICT_REF device_str,
        this_t::device_str_kind_t const device_str_kind ) const SIXTRL_NOEXCEPT
    {
        this_t::node_info_t const* ptr_node_info = nullptr;

        SIXTRL_ASSERT( this->has_nodes() );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_ILLEGAL );
        SIXTRL_ASSERT( this->backend_id() != st::BACKEND_UNDEFINED );
        SIXTRL_ASSERT( this->m_node_infos.size() ==
                       this->m_node_id_to_node_info_map.size() );

        if( ( !this->m_node_infos.empty() ) && ( !device_str.empty() ) &&
            ( device_str_kind != st::NODE_DEVICE_STRING_KIND_ILLEGAL ) )
        {
            bool format_checked = false;
            auto it = this->base_node_infos_begin();
            auto end = this->base_node_infos_end();

            for( ; it != end ; ++it )
            {
                auto ptr_test_node = *it;
                if( ( ptr_test_node == nullptr ) ||
                    ( ptr_test_node->backend_id() != this->backend_id() ) ) continue;

                if( !format_checked )
                {
                    if( !ptr_test_node->check_device_str_format(
                            device_str, device_str_kind ) )
                    {
                        break;
                    }

                    format_checked = true;
                }

                SIXTRL_ASSERT( format_checked );

                if( !ptr_test_node->has_device_string_by_kind(
                        device_str_kind ) ) continue;

                if( device_str.compare( ptr_test_node->device_string_by_kind(
                        device_str_kind ) ) == 0 )
                {
                    ptr_node_info = ptr_test_node;
                    break;
                }
            }
        }

        return ptr_node_info;
    }


    bool this_t::limits_allowed_node_ids() const SIXTRL_NOEXCEPT
    {
        return !this->m_allowed_node_ids.empty();
    }

    st_size_t this_t::num_allowed_nodes() const SIXTRL_NOEXCEPT
    {
        return this->m_allowed_node_ids.size();
    }

    this_t::c_node_id_t const*
    this_t::allowed_c_node_ids_begin() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_allowed_node_ids.empty() )
            ? this->m_allowed_node_ids.data() : nullptr;
    }

    this_t::c_node_id_t const*
    this_t::allowed_c_node_ids_end() const SIXTRL_NOEXCEPT
    {
        auto ptr_end = this->allowed_c_node_ids_begin();
        if( ptr_end != nullptr )
            std::advance( ptr_end, this->m_allowed_node_ids.size() );
        return ptr_end;
    }

    this_t::c_node_id_t const& this_t::allowed_c_node_id(
        st_size_t const idx ) const
    {
        return this->m_allowed_node_ids.at( idx );
    }

    string_t const&
    this_t::allowed_node_ids_env_var_name() const SIXTRL_NOEXCEPT
    {
        return this->m_allowed_node_ids_env_var_name;
    }

    /* ===================================================================== */

    this_t::BaseNodeBackend( this_t::backend_id_t const backend_id,
        string_t const& SIXTRL_RESTRICT_REF backend_str ) :
        st::BaseBackend( backend_id, backend_str ),
        m_node_id_to_node_info_map(), m_node_infos(), m_node_ids(),
        m_allowed_node_ids()
    {
        this->set_class_variant(
            this->class_variant_flags() |
            this_t::BACKEND_VARIANT_HAS_NODES );
    }

    st_status_t this_t::do_assign_symbols()
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( base_backend_t::do_assign_symbols() == st::STATUS_SUCCESS ) )
        {
            SIXTRL_ASSERT( !this->is_available() );
            SIXTRL_ASSERT( !this->is_ready() );

            status = st::STATUS_SUCCESS;
            auto ptr_dlib_loader = this->ptr_base_dynamic_library_loader();

            if( ( ptr_dlib_loader != nullptr ) &&
                ( ptr_dlib_loader->has_dynamic_lib_handle() ) )
            {
                bool const SYMBOL_IS_REQUIRED = true;

                this->m_create_node_info_fn = ptr_dlib_loader->load_symbol<
                    decltype( this->m_create_node_info_fn ) >(
                        this->symbol_name( this_t::SYMBOL_ID_CREATE_NODE_INFO ),
                            SYMBOL_IS_REQUIRED );

                this->m_delete_node_info_fn = ptr_dlib_loader->load_symbol<
                    decltype( this->m_delete_node_info_fn ) >(
                        this->symbol_name( this_t::SYMBOL_ID_DELETE_NODE_INFO ),
                            SYMBOL_IS_REQUIRED );

                this->m_get_total_num_nodes_fn = ptr_dlib_loader->load_symbol<
                    decltype( this->m_get_total_num_nodes_fn ) >(
                        this->symbol_name( this_t::SYMBOL_ID_GET_TOTAL_NUM_NODES
                            ), SYMBOL_IS_REQUIRED );

                this->m_get_all_node_ids_fn = ptr_dlib_loader->load_symbol<
                    decltype( this->m_get_all_node_ids_fn ) >(
                        this->symbol_name( this_t::SYMBOL_ID_GET_ALL_NODE_IDS ),
                            SYMBOL_IS_REQUIRED );
            }
        }

        return status;
    }

    st_status_t this_t::do_reset_symbols()
    {
        st_status_t status = base_backend_t::do_reset_symbols();
        if( status == st::STATUS_SUCCESS )
        {
            this->m_create_node_info_fn = nullptr;
            this->m_delete_node_info_fn = nullptr;
            this->m_get_total_num_nodes_fn = nullptr;
            this->m_get_all_node_ids_fn = nullptr;
        }

        return status;
    }

    st_status_t this_t::do_make_available()
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( !this->is_available() ) && (  this->has_nodes() ) )
        {
            status = base_backend_t::do_make_available();

            if( ( status == st::STATUS_SUCCESS ) &&
                ( ( this->m_get_total_num_nodes_fn == nullptr ) ||
                  ( this->m_get_all_node_ids_fn == nullptr ) ) )
            {
                status = st::STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::STATUS_SUCCESS ) &&
                (  this->m_get_total_num_nodes_fn() == st_size_t{ 0 } ) )
            {
                status = st::STATUS_GENERAL_FAILURE;
            }

            if( status == st::STATUS_SUCCESS )
            {
                this->clear_internal_lists();
                this->clear_allowed_node_ids();

                status = ( !this->allowed_node_ids_env_var_name().empty() )
                    ? this->parse_env_variable_for_allowed_node_ids(
                        this->allowed_node_ids_env_var_name().c_str() )
                    : this->parse_env_variable_for_allowed_node_ids( nullptr );
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t this_t::set_allowed_node_ids_env_var_name(
        string_t const& SIXTRL_RESTRICT_REF env_variable_name )
    {
        this->m_allowed_node_ids_env_var_name = env_variable_name;
        return st::STATUS_SUCCESS;
    }

    st_status_t this_t::add_available_node_info(
        this_t::managed_base_node_info_t node_info_to_add ) {

        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->has_nodes() ) &&
            ( this->backend_id() != st::BACKEND_UNDEFINED ) &&
            ( this->backend_id() != st::BACKEND_ILLEGAL ) &&
            ( this->is_available() ) && ( !this->is_ready() ) &&
            ( node_info_to_add.get() != nullptr ) &&
            ( node_info_to_add->backend_id() == this->backend_id() ) &&
            ( node_info_to_add->platform_id() != st::NODE_ILLEGAL_PLATFORM_ID ) &&
            ( node_info_to_add->device_id() != st::NODE_ILLEGAL_DEVICE_ID ) &&
            ( this->m_node_infos.empty() ) && ( this->m_node_ids.empty() ) )
        {
            auto it = this->m_node_id_to_node_info_map.find(
                node_info_to_add->node_id_data() );

            if( it == this->m_node_id_to_node_info_map.end() )
            {
                auto ret = this->m_node_id_to_node_info_map.emplace(
                    std::make_pair( node_info_to_add->node_id_data(),
                        std::move( node_info_to_add ) ) );

                if( ret.second ) status = st::STATUS_SUCCESS;
            }
            else
            {
                SIXTRL_ASSERT( it->first.m_backend_id == this->backend_id() );
                SIXTRL_ASSERT( it->first.m_platform_id ==
                               node_info_to_add->platform_id() );
                SIXTRL_ASSERT( it->first.m_device_id ==
                               node_info_to_add->device_id() );

                it->second = std::move( node_info_to_add );
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    st_status_t this_t::remove_available_node_info(
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF node_id_to_remove )
    {
         st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->has_nodes() ) &&
            ( this->backend_id() != st::BACKEND_UNDEFINED ) &&
            ( this->backend_id() != st::BACKEND_ILLEGAL ) &&
            ( this->is_available() ) && ( !this->is_ready() ) &&
            ( node_id_to_remove.m_backend_id == this->backend_id() ) &&
            ( this->m_node_infos.empty() ) && ( this->m_node_ids.empty() ) )
        {
            auto it = this->m_node_id_to_node_info_map.find(
                node_id_to_remove );

            if( it != this->m_node_id_to_node_info_map.end() )
            {
                this->m_node_id_to_node_info_map.erase( it );
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    st_status_t this_t::parse_env_variable_for_allowed_node_ids(
        this_t::string_char_t const* SIXTRL_RESTRICT env_variable_name )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->has_nodes() ) && ( this->m_allowed_node_ids.empty() ) &&
            ( this->m_get_all_node_ids_fn != nullptr ) &&
            ( this->m_get_total_num_nodes_fn != nullptr ) &&
            ( this->backend_id() != st::BACKEND_UNDEFINED ) &&
            ( this->backend_id() != st::BACKEND_ILLEGAL ) )
        {
            string_type env_variable_result;

            if( ( env_variable_name != nullptr ) &&
                ( std::strlen( env_variable_name ) > st_size_t{ 0 } ) )
            {
                char const* temp_env_var_result =
                    std::getenv( env_variable_name );

                if( ( temp_env_var_result != nullptr ) &&
                    ( std::strlen( temp_env_var_result ) > st_size_t{ 0 } ) )
                {
                    env_variable_result = temp_env_var_result;
                }
            }

            if( env_variable_result.empty() )
            {
                st_size_t const total_num_nodes =
                    this->m_get_total_num_nodes_fn();

                if( total_num_nodes > st_size_t{ 0 } )
                {
                    this->m_allowed_node_ids.resize( total_num_nodes,
                        c_node_id_t{ st::BACKEND_ILLEGAL,
                            st::NODE_ILLEGAL_PLATFORM_ID,
                                st::NODE_ILLEGAL_DEVICE_ID } );

                    st_size_t const num_nodes = this->m_get_all_node_ids_fn(
                        this->m_allowed_node_ids.data(), total_num_nodes );

                    SIXTRL_ASSERT( num_nodes <= total_num_nodes );
                    ( void )num_nodes;
                }

                status = st::STATUS_SUCCESS;
            }
            else
            {
                this_t::sstream_t regex_str;
                regex_str << "(^\\s*|\\s*\\,\\s*|\\s*\\;\\s*)";
                regex_str << "(";

                if( this->has_backend_string() )
                {
                     regex_str << this->backend_string_str() << "\\:|";
                }

                regex_str << this->backend_id() << "\\:)?";
                regex_str << st::NodeId::NODE_ID_STR_NOBACKEND_FORMAT_REGEX_STR;

                std::regex const expr( regex_str.str() );
                st::NodeId temp_node;

                auto expr_it  = std::cregex_iterator(
                    env_variable_result.c_str(),
                    env_variable_result.c_str() + env_variable_result.size(),
                    expr );

                auto expr_end = (std::cregex_iterator());

                if( expr_it != expr_end )
                {
                    std::set< ::NS(NodeId) > temp_allowed_node_ids;

                    for( ; expr_it != expr_end ; ++expr_it )
                    {
                        if( ( expr_it->size() == st_size_t{ 5 } ) &&
                            ( st::STATUS_SUCCESS == temp_node.from_string(
                                ( *expr_it )[ 4 ] ) ) )
                        {
                            if( ( temp_node.backend_id() ==
                                    this->backend_id() ) &&
                                ( temp_node.is_legal() ) )
                            {
                                temp_allowed_node_ids.emplace( c_node_id_t{
                                    temp_node.backend_id(),
                                        temp_node.platform_id(),
                                            temp_node.device_id() } );
                            }
                        }
                    }

                    if( !temp_allowed_node_ids.empty() )
                    {
                        this->m_allowed_node_ids.assign(
                            temp_allowed_node_ids.begin(),
                            temp_allowed_node_ids.end() );
                    }
                }

                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    void this_t::clear_allowed_node_ids()
    {
        this->m_allowed_node_ids.clear();
    }

    st_status_t this_t::rebuild_internal_lists()
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->has_nodes() ) &&
            ( this->backend_id() != st::BACKEND_UNDEFINED ) &&
            ( this->backend_id() != st::BACKEND_ILLEGAL ) &&
            ( this->is_available() ) && ( !this->is_ready() ) &&
            ( this->m_node_infos.empty() ) && ( this->m_node_ids.empty() ) )
        {
            status = st::STATUS_SUCCESS;

            auto it = this->m_node_id_to_node_info_map.begin();
            auto end_node_infos = this->m_node_id_to_node_info_map.end();

            for( ; it != end_node_infos ; ++it )
            {
                if( ( it->second.get() == nullptr ) ||
                    ( it->first.m_backend_id  != this->backend_id() ) ||
                    ( it->first.m_backend_id  != it->second->backend_id() ) ||
                    ( it->first.m_platform_id == st::NODE_ILLEGAL_PLATFORM_ID ) ||
                    ( it->first.m_platform_id != it->second->platform_id() ) ||
                    ( it->first.m_device_id   == st::NODE_ILLEGAL_DEVICE_ID ) ||
                    ( it->first.m_device_id   != it->second->device_id() ) )
                {
                    status = st::STATUS_GENERAL_FAILURE;
                    break;
                }

                this->m_node_infos.push_back( it->second.get() );
                this->m_node_ids.push_back( it->second->node_id_data() );
            }

            SIXTRL_ASSERT( ( status != st::STATUS_SUCCESS ) ||
                ( ( this->m_node_infos.size() == this->m_node_ids.size() ) &&
                  ( this->m_node_infos.size() ==
                    this->m_node_id_to_node_info_map.size() ) ) );
        }

        return status;
    }

    void this_t::clear_internal_lists()
    {
        if( this->is_ready() )
        {
            throw std::runtime_error( "illegal operation -> "
                "can't clear nodes from an in-use backend!" );
        }

        this->m_node_ids.clear();
        this->m_node_infos.clear();
        this->m_node_id_to_node_info_map.clear();
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool this_t::check_is_base_node_backend_ready() const SIXTRL_NOEXCEPT
    {
        return ( ( this->is_available() ) &&
                 ( this->m_create_node_info_fn != nullptr ) &&
                 ( this->m_delete_node_info_fn != nullptr ) &&
                 ( this->m_get_total_num_nodes_fn != nullptr ) &&
                 ( this->m_get_all_node_ids_fn != nullptr ) &&
                 ( this->m_node_id_to_node_info_map.size() ==
                   this->m_node_infos.size() ) &&
                 ( this->m_node_infos.size() == this->m_node_ids.size() ) );
    }
}

#endif /* C++ */
