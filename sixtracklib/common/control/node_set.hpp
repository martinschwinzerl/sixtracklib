#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_SET_CXX_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_SET_CXX_HPP__


#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <cstdio>
    #include <stdexcept>
    #include <string>
    #include <memory>
    #include <unordered_map>
    #include <vector>
    #include <utility>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/buffer.hpp"
    #include "sixtracklib/common/control/node_id.hpp"
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class NodeStore;
    class NodeInfoBase;

    class NodeSetBase
    {
        public:

        using lockable_t       = std::mutex;
        using lock_t           = std::unique_lock< lockable_t >;

        using node_store_t     = SIXTRL_CXX_NAMESPACE::NodeStore;
        using ptr_node_store_t = std::shared_ptr< node_store_t >;

        using node_id_t        = SIXTRL_CXX_NAMESPACE::NodeId;
        using c_node_id_t      = node_id_t::c_api_t;
        using arch_id_t        = node_id_t::arch_id_t;
        using platform_id_t    = node_id_t::platform_id_t;
        using device_id_t      = node_id_t::device_id_t;
        using size_type        = node_id_t::size_type;
        using status_t         = node_id_t::status_t;
        using id_str_format_t  = node_id_t::format_t;

        using node_index_t     = SIXTRL_CXX_NAMESPACE::node_index_t;
        using node_info_base_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;

        static constexpr arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static constexpr node_index_t UNDEFINED_INDEX =
            SIXTRL_CXX_NAMESPACE::NODE_UNDEFINED_INDEX;

        static constexpr platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static constexpr platform_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::ILLEGAL_DEVICE_ID;

        static constexpr id_str_format_t DEFAULT_ID_STR_FORMAT =
            SIXTRL_CXX_NAMESPACE::NODE_ID_STR_FORMAT_DEFAULT;

        SIXTRL_HOST_FN explicit NodeSetBase(
            ptr_node_store_t& SIXTRL_RESTRICT_REF node_store,
            size_type const num_nodes = size_type{ 0 },
            node_index_t const* SIXTRL_RESTRICT node_indices_begin = nullptr,
            id_str_format_t const node_id_str_format = DEFAULT_ID_STR_FORMAT );

        template< typename NodeIndexIter >
        SIXTRL_HOST_FN NodeSetBase(
            ptr_node_store_t& SIXTRL_RESTRICT_REF node_store,
            NodeIndexIter node_index_begin, NodeIndexIter node_index_end,
            id_str_format_t const node_id_str_format = DEFAULT_ID_STR_FORMAT );

        SIXTRL_HOST_FN NodeSetBase( NodeSetBase const& orig ) = default;
        SIXTRL_HOST_FN NodeSetBase( NodeSetBase&& orig ) = default;

        SIXTRL_HOST_FN NodeSetBase& operator=(
            NodeSetBase const& orig ) = default;

        SIXTRL_HOST_FN NodeSetBase& operator=( NodeSetBase&& orig ) = default;

        SIXTRL_HOST_FN virtual ~NodeSetBase() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type numNodes() const;

        SIXTRL_HOST_FN node_index_t const* nodeIndicesBegin() const;
        SIXTRL_HOST_FN node_index_t const* nodeIndicesEnd() const;

        SIXTRL_HOST_FN node_index_t minNodeIndex() const;
        SIXTRL_HOST_FN node_index_t maxNodeIndex() const;

        SIXTRL_HOST_FN c_node_id_t const* nodeIdsBegin() const;
        SIXTRL_HOST_FN c_node_id_t const* nodeIdsEnd() const;

        SIXTRL_HOST_FN node_id_t nodeId( node_index_t const node_index ) const;

        SIXTRL_HOST_FN std::string nodeIdStr(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN status_t ptrNodeIdStr(
            node_index_t const node_index,
            size_type const node_id_str_capacity,
            char* SIXTRL_RESTRICT node_id_str ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN size_type numNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* nodeIndicesBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* nodeIndicesEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t minNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t maxNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_node_id_t const* nodeIdsBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_node_id_t const* nodeIdsEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const& nodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* ptrNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const& nodeIdStr(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN char const* ptrNodeIdStr(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t ptrNodeIdStr(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            size_type const node_id_str_capacity,
            char* SIXTRL_RESTRICT node_id_str ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN id_str_format_t nodeIdStrFormat() const;
        SIXTRL_HOST_FN status_t setNodeIdStrFormat( id_str_format_t const fmt );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN id_str_format_t nodeIdStrFormat(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN status_t setNodeIdStrFormat(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            id_str_format_t const fmt );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canSelectNodes() const;
        SIXTRL_HOST_FN bool supportsDefaultNodes() const;

        SIXTRL_HOST_FN size_type maxNumSelectableNodes() const;
        SIXTRL_HOST_FN size_type maxNumDefaultNodes() const;

        SIXTRL_HOST_FN size_type numSelectedNodes() const;
        SIXTRL_HOST_FN size_type numDefaultNodeS() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool canSelectNodes() const;
        SIXTRL_HOST_FN bool supportsDefaultNodes() const;

        SIXTRL_HOST_FN size_type maxNumSelectableNodes() const;
        SIXTRL_HOST_FN size_type maxNumDefaultNodes() const;

        SIXTRL_HOST_FN size_type numSelectedNodes() const;
        SIXTRL_HOST_FN size_type numDefaultNodeS() const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasNodeStore() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_store_t const* ptrNodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_store_t* ptrNodeStore() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_store_t const& nodeStore() const;
        SIXTRL_HOST_FN node_store_t& nodeStore();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool checkLock(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        protected:

        using node_indices_buffer_t = std::vector< node_index_t >;
        using node_indices_map_t    = std::vector< node_index_t >;

        using node_idx_to_id_str_map_t =
            std::unordered_map< node_index, std::string >;

        virtual status_t doPrintNodeInfo(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const;

        status_t doSelectNode(
            lock_t const& SIXTRL_NOEXCEPT lock,
            node_index_t const node_index );

        status_t doUnselectNode(
            lock_t const& SIXTRL_NOEXCEPT lock,
            node_index_t const node_index );

        status_t doAddDefaultNode(
            lock_t const& SIXTRL_NOEXCEPT lock,
            node_index_t const node_index );

        status_t doRemoveDefaultNode(
            lock_t const& SIXTRL_NOEXCEPT lock,
            node_index_t const node_index );

        status_t doSetMinNumSelectableNodes(
            lock_t const& SIXTRL_NOEXCEPT lock,
            size_type const m_max_num_selectable_nodes );

        status_t doSetMaxNumSelectableNodes(
            lock_t const& SIXTRL_NOEXCEPT lock,
            size_type const m_max_num_selectable_nodes );

        status_t doSetMinNumDefaultNodes(
            lock_t const& SIXTRL_NOEXCEPT lock,
            size_type const m_max_num_selectable_nodes );

        status_t doSetMaxNumDefaultNodes(
            lock_t const& SIXTRL_NOEXCEPT lock,
            size_type const m_max_num_selectable_nodes );

        private:

        node_idx_to_id_str_map_t    m_node_index_to_id_str_map;
        node_indices_map_t          m_node_indices_map;
        node_indices_buffer_t       m_node_indices;
        node_indices_buffer_t       m_selected_nodes;
        node_indices_buffer_t       m_default_nodes;

        ptr_node_store_t            m_ptr_node_store;
        id_str_format_t             m_id_str_format;

        size_type                   m_min_num_selectable_nodes;
        size_type                   m_max_num_selectable_nodes;
        size_type                   m_min_num_default_nodes;
        size_type                   m_max_num_default_nodes;
    };

    class NodeSet : public NodeSetBase
    {
        private:

        using _base_node_set_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;

        public:

        SIXTRL_HOST_FN explicit NodeSet(
            ptr_node_store_t& SIXTRL_RESTRICT_REF node_store,
            size_type const num_nodes = size_type{ 0 },
            node_index_t const* SIXTRL_RESTRICT node_indices_begin = nullptr,
            id_str_format_t const node_id_str_format =
                _base_node_set_t::DEFAULT_ID_STR_FORMAT );

        template< typename NodeIndexIter >
        SIXTRL_HOST_FN NodeSet(
            ptr_node_store_t& SIXTRL_RESTRICT_REF node_store,
            NodeIndexIter node_index_begin, NodeIndexIter node_index_end,
            id_str_format_t const node_id_str_format =
                _base_node_set_tDEFAULT_ID_STR_FORMAT );


        SIXTRL_HOST_FN NodeSet( NodeSet const& orig ) = default;
        SIXTRL_HOST_FN NodeSet( NodeSet&& orig ) = default;

        SIXTRL_HOST_FN NodeSet& operator=( NodeSet const& orig ) = default;
        SIXTRL_HOST_FN NodeSet& operator=( NodeSet&& orig ) = default;

        SIXTRL_HOST_FN virtual ~NodeSet() = default;
    };
}

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_SET_CXX_HPP__ */

/* end: sixtracklib/common/control/node_set.hpp */
