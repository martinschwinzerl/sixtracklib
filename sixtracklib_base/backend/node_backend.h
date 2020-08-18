#ifndef SIXTRACKLIB_BASE_BACKEND_NODE_BACKEND_H__
#define SIXTRACKLIB_BASE_BACKEND_NODE_BACKEND_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/backend/definitions.h"
    #include "sixtracklib_base/backend/backend.h"
    #include "sixtracklib_base/node/node_id.h"
    #include "sixtracklib_base/node/node_info.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <ostream>
        #include <map>
        #include <set>
        #include <string>
        #include <vector>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if  defined( __cplusplus ) && !defined( _GPUCODE )

namespace toml
{

}

namespace SIXTRL_CXX_NAMESPACE
{
    class SIXTRL_BASE_EXPORT_API BaseNodeBackend :
        public SIXTRL_CXX_NAMESPACE::BaseBackend
    {
        public:

        using base_backend_t    = SIXTRL_CXX_NAMESPACE::BaseBackend;
        using node_info_t       = SIXTRL_CXX_NAMESPACE::BaseNodeInfo;
        using platform_id_t     = node_info_t::platform_id_t;
        using device_id_t       = node_info_t::device_id_t;
        using device_str_kind_t = node_info_t::device_str_kind_t;
        using c_node_id_t       = node_info_t::c_node_id_t;

        using managed_base_node_info_t = std::unique_ptr< ::NS(BaseNodeInfo),
            void (*)( ::NS(BaseNodeInfo)* ) >;

        using managed_base_node_id_t = std::unique_ptr< ::NS(BaseNodeId),
            void (*)( ::NS(BaseNodeId)* ) >;

        static constexpr be_symbol_id_t SYMBOL_ID_CREATE_NODE_INFO =
            be_symbol_id_t{ 2 };

        static constexpr be_symbol_id_t SYMBOL_ID_DELETE_NODE_INFO =
            be_symbol_id_t{ 3 };

        static constexpr be_symbol_id_t SYMBOL_ID_GET_TOTAL_NUM_NODES =
            be_symbol_id_t{ 4 };

        static constexpr be_symbol_id_t SYMBOL_ID_GET_ALL_NODE_IDS =
            be_symbol_id_t{ 5 };

        static constexpr be_symbol_id_t SYMBOL_ID_CREATE_NODE_ID =
            be_symbol_id_t{ 6 };

        static constexpr be_symbol_id_t SYMBOL_ID_CREATE_NODE_ID_FROM_STRING =
            be_symbol_id_t{ 7 };

        static constexpr be_symbol_id_t
            SYMBOL_ID_CREATE_NODE_ID_FROM_STRING_DETAILED = be_symbol_id_t{ 8 };

        static constexpr be_symbol_id_t SYMBOL_ID_DELETE_NODE_ID =
            be_symbol_id_t{ 9 };

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual ~BaseNodeBackend() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN managed_base_node_info_t
        create_node_info( platform_id_t const platform_id,
                          device_id_t const device_id );

        SIXTRL_HOST_FN size_type total_num_nodes() const;
        SIXTRL_HOST_FN size_type all_node_ids(
            c_node_id_t* SIXTRL_RESTRICT node_ids_begin,
            size_type const max_node_ids ) const;

        template< class NodeIdIter >
        SIXTRL_HOST_FN size_type all_node_ids(
            NodeIdIter node_ids_begin, NodeIdIter node_ids_end ) const
        {
            std::vector< ::NS(NodeId) > temp( node_ids_begin, node_ids_end );
            size_type const nn = this->all_node_ids( temp.data(), temp.size() );
            std::copy( temp.begin(), temp.end(), node_ids_begin );
            return nn;
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type num_available_nodes() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_t const* const*
        base_node_infos_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_t const* const*
        base_node_infos_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_t const*
        base_node_info( size_type const idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_t const*
        base_node_info( platform_id_t const platform_id,
                        device_id_t const device_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_t const*
        base_node_info_by_str( string_type const&
            SIXTRL_RESTRICT_REF node_id_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_t const*
        base_node_info_by_str_detailed(
            string_type const& SIXTRL_RESTRICT_REF node_id_str,
            device_str_kind_t const device_str_kind ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_node_id_t const*
        c_node_ids_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_node_id_t const*
        c_node_ids_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN
        bool limits_allowed_node_ids() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN
        size_type num_allowed_nodes() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_node_id_t const*
        allowed_c_node_ids_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_node_id_t const*
        allowed_c_node_ids_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_node_id_t const&
        allowed_c_node_id( size_type const idx ) const;

        SIXTRL_HOST_FN string_type const&
        allowed_node_ids_env_var_name() const SIXTRL_NOEXCEPT;

        protected:

        using node_id_to_node_info_map_t = std::map<
            ::NS(NodeId), managed_base_node_info_t >;

        using node_infos_list_t = std::vector< ::NS(BaseNodeInfo) const* >;
        using c_node_ids_list_t = std::vector< ::NS(NodeId) >;

        // Symbols imported from the plugin:

        using create_node_info_fn_t = ::NS(BaseNodeInfo)* (*)(
            platform_id_t const, device_id_t const );

        using delete_node_info_fn_t = void (*)( ::NS(BaseNodeInfo)* );

        using get_total_num_nodes_fn_t = size_type (*)( void );

        using get_all_node_ids_fn_t =
            size_type (*)( ::NS(NodeId)*, size_type const );

        SIXTRL_HOST_FN explicit BaseNodeBackend(
            backend_id_t const backend_id,
            string_type const& SIXTRL_RESTRICT_REF backend_str = string_type{} );

        SIXTRL_HOST_FN BaseNodeBackend( BaseNodeBackend const& ) = delete;

        SIXTRL_HOST_FN BaseNodeBackend( BaseNodeBackend&& ) = delete;

        SIXTRL_HOST_FN BaseNodeBackend& operator=(
            BaseNodeBackend const& ) = delete;

        SIXTRL_HOST_FN BaseNodeBackend&
        operator=( BaseNodeBackend&& ) = delete;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t do_assign_symbols() override;
        SIXTRL_HOST_FN status_t do_reset_symbols()  override;
        SIXTRL_HOST_FN status_t do_make_available() override;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t set_allowed_node_ids_env_var_name(
            string_type const& SIXTRL_RESTRICT_REF env_variable_name );

        SIXTRL_HOST_FN status_t add_available_node_info(
            managed_base_node_info_t node_info_to_add );

        SIXTRL_HOST_FN status_t remove_available_node_info(
            ::NS(NodeId) const& SIXTRL_RESTRICT_REF node_id_to_remove );

        SIXTRL_HOST_FN status_t
        parse_env_variable_for_allowed_node_ids(
            string_char_t const* SIXTRL_RESTRICT env_variable_name );

        SIXTRL_HOST_FN void clear_allowed_node_ids();

        SIXTRL_HOST_FN status_t rebuild_internal_lists();
        SIXTRL_HOST_FN void clear_internal_lists();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool
        check_is_base_node_backend_ready() const SIXTRL_NOEXCEPT;

        private:

        node_id_to_node_info_map_t  m_node_id_to_node_info_map;
        node_infos_list_t           m_node_infos;
        c_node_ids_list_t           m_node_ids;
        c_node_ids_list_t           m_allowed_node_ids;

        string_type m_allowed_node_ids_env_var_name =
            string_type{ "SIXTRACKLIB_DEVICES" };

        protected:
        create_node_info_fn_t       m_create_node_info_fn    = nullptr;
        delete_node_info_fn_t       m_delete_node_info_fn    = nullptr;
        get_total_num_nodes_fn_t    m_get_total_num_nodes_fn = nullptr;
        get_all_node_ids_fn_t       m_get_all_node_ids_fn    = nullptr;
    };
}

extern "C"
{
    typedef SIXTRL_CXX_NAMESPACE::BaseNodeBackend NS(BaseNodeBackend);
}

#else /* C++, Host */

struct NS(Backend);

#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_BACKEND_NODE_BACKEND_H__ */
