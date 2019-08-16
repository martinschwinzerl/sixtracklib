#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_SET_CXX_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_SET_CXX_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <atomic>
    #include <cstddef>
    #include <cstdlib>
    #include <cstdio>
    #include <stdexcept>
    #include <string>
    #include <memory>
    #include <mutex>
    #include <thread>
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

    class NodeSetBase
    {
        public:

        using node_store_t         = SIXTRL_CXX_NAMESPACE::NodeStore;
        using node_id_t            = SIXTRL_CXX_NAMESPACE::NodeId;
        using node_index_t         = SIXTRL_CXX_NAMESPACE::node_index_t;
        using c_node_id_t          = node_id_t::c_api_t;
        using arch_id_t            = node_id_t::arch_id_t;
        using platform_id_t        = node_id_t::platform_id_t;
        using device_id_t          = node_id_t::device_id_t;
        using size_type            = node_id_t::size_type;
        using status_t             = node_id_t::status_t;
        using id_str_format_t      = node_id_t::format_t;
        using node_set_id_t        = uint32_t;

        using lockable_t           = std::mutex;
        using lock_t               = std::unique_lock< lockable_t >;

        using sync_id_value_t      = uint64_t;
        using sync_id_t            = std::atomic< sync_id_value_t >;

        static constexpr arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static constexpr node_index_t UNDEFINED_INDEX =
            SIXTRL_CXX_NAMESPACE::NODE_UNDEFINED_INDEX;

        static constexpr platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static constexpr platform_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static constexpr id_str_format_t DEFAULT_ID_STR_FORMAT =
            SIXTRL_CXX_NAMESPACE::NODE_ID_STR_FORMAT_DEFAULT;

        static constexpr node_set_id_t ILLEGAL_NODE_SET_ID =
            node_set_id_t{ 0xffffffff };

        static constexpr sync_id_value_t ILLEGAL_SYNC_ID_VALUE =
            sync_id_value_t{ 0xffffffffffffffff };

        static constexpr sync_id_value_t LAST_LEGAL_SYNC_ID_VALUE =
            sync_id_value_t{ 0xfffffffffffffffe };


        SIXTRL_HOST_FN explicit NodeSetBase(
            SIXTRL_CXX_NAMESPACE::NodeStore& SIXTRL_RESTRICT_REF node_store );

        SIXTRL_HOST_FN NodeSetBase( NodeSetBase const& orig );
        SIXTRL_HOST_FN NodeSetBase( NodeSetBase&& orig );

        SIXTRL_HOST_FN NodeSetBase& operator=( NodeSetBase const& rhs );
        SIXTRL_HOST_FN NodeSetBase& operator=( NodeSetBase&& rhs );

        SIXTRL_HOST_FN virtual ~NodeSetBase() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_set_id_t nodeSetId() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setNodeSetId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type numNodes() const;

        SIXTRL_HOST_FN node_index_t minNodeIndex() const;
        SIXTRL_HOST_FN node_index_t maxNodeIndex() const;
        SIXTRL_HOST_FN node_index_t nodeIndex( size_type const nn ) const;

        SIXTRL_HOST_FN node_id_t const& nodeId( size_type const nn ) const;

        SIXTRL_HOST_FN node_id_t nodeIdByNodeIndex(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN c_node_id_t const* ptrCNodeId(
            size_type const nn ) const;

        SIXTRL_HOST_FN c_node_id_t const* ptrCNodeIdByNodeIndex(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN bool available( node_index_t const node_index ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN size_type numNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t minNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t maxNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const nn ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const& nodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock, size_type const nn ) const;

        SIXTRL_HOST_FN node_id_t const& nodeIdByNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const ) const;

        SIXTRL_HOST_FN c_node_id_t const* ptrCNodeIdByNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_node_id_t const* ptrCNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const nn ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool available(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* nodeIndicesBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* nodeIndicesEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_node_id_t const* nodeIdsBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_node_id_t const* nodeIdsEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool usesAutoSelect() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSelected( node_index_t const index ) const;
        SIXTRL_HOST_FN bool canSelectNode( node_index_t const index ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool isSelected( lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool canSelectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool isDefault( node_index_t const node_index ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool isDefault( lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canChangeSelectedNode() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool canDirectlyChangeSelectedNode() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool canChangeToNode(
            node_index_t const current_node_idx,
            node_index_t const next_node_idx ) const;

        SIXTRL_HOST_FN status_t changeToNode(
            node_index_t const current_node_idx,
            node_index_t const next_node_idx );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool canChangeToNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const current_node_idx,
            node_index_t const next_node_idx ) const;

        SIXTRL_HOST_FN status_t changeToNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const current_node_idx,
            node_index_t const next_node_idx );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canUnselectNode() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool canUnselectNode(  node_index_t const index ) const;

        SIXTRL_HOST_FN status_t unselectNode( node_index_t const node_index );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool canUnselectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t unselectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t syncWithStore();

        SIXTRL_HOST_FN status_t syncWithStore(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type requiredOutStringLength() const;

        SIXTRL_HOST_FN void print(
            std::ostream& SIXTRL_RESTRICT_REF output ) const;

        SIXTRL_HOST_FN void print( ::FILE* SIXTRL_RESTRICT output ) const;

        SIXTRL_HOST_FN void printOut() const;

        SIXTRL_HOST_FN std::string toString() const;

        SIXTRL_HOST_FN status_t toString( size_type const out_str_capacity,
            char* SIXTRL_RESTRICT out_str ) const;

        SIXTRL_HOST_FN friend std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF output,
            NodeInfoBase const& SIXTRL_RESTRICT_REF node_info );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN size_type requiredOutStringLength(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN void print( lock_t const& SIXTRL_RESTRICT_REF lock,
            std::ostream& SIXTRL_RESTRICT_REF output ) const;

        SIXTRL_HOST_FN void print( lock_t const& SIXTRL_RESTRICT_REF lock,
        ::FILE* SIXTRL_RESTRICT output ) const;

        SIXTRL_HOST_FN void printOut( lock_t const& SIXTRL_RESTRICT_REF ) const;

        SIXTRL_HOST_FN std::string toString(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN status_t toString( lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const out_str_capacity, char* SIXTRL_RESTRICT ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_store_t const& nodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_store_t const* ptrNodeStore() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_store_t& nodeStore();
        SIXTRL_HOST_FN node_store_t* ptrNodeStore() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool checkLock(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool isSingleNodeSet() const SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN virtual status_t doSyncWithNodeStore(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            SIXTRL_CXX_NAMESPACE::NodeStore& SIXTRL_RESTRICT node_store );

        SIXTRL_HOST_FN virtual status_t doSelectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        SIXTRL_HOST_FN virtual status_t doChangeToNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const current_node_idx,
            node_index_t const next_node_idx );

        SIXTRL_HOST_FN virtual status_t doUnselectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const prev_selected_node );

        SIXTRL_HOST_FN virtual status_t doPrintNodeInfos(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type doGetNumSelectedNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type doGetMinNumSelectableNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doSetMinNumSelectableNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const min_num_selectable_nodes ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type doGetMaxNumSelectableNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doSetMaxNumSelectableNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const max_num_selectable_nodes ) SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN size_type doGetNumDefaultNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type doGetMinNumDefaultNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doSetMinNumDefaultNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const max_num_default_nodes ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type doGetMaxNumDefaultNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doSetMaxNumDefaultNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const max_num_default_nodes ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void doSetIsSingleNodeSetFlag(
            bool const flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetAllowDuplicatesNodesFlag(
            bool const flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetCanDirectlyChangeSelectedNodeFlag(
            bool const flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetCanUnselectNodeFlag(
            bool const flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetUseAutoselectFlag(
            bool const flag ) SIXTRL_NOEXCEPT;

        private:

        sync_id_t                         m_sync_id;
        SIXTRL_CXX_NAMESPACE::NodeStore&  m_node_store;

        size_type                         m_min_num_selectable_nodes;
        size_type                         m_max_num_selectable_nodes;

        size_type                         m_min_num_default_nodes;
        size_type                         m_max_num_default_nodes;
        node_set_id_t                     m_my_node_set_id;

        bool                              m_is_single_node_set;
        bool                              m_allows_duplicate_nodes;
        bool                              m_can_directly_change_selected_node;
        bool                              m_can_unselect_node;
        bool                              m_use_autoselect;
    };

    class NodeSetSingle : public SIXTRL_CXX_NAMESPACE::NodeSetBase
    {
        private:

        using _node_set_base_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;

        public:

        explicit NodeSetSingle(
            SIXTRL_CXX_NAMESPACE::NodeStore& SIXTRL_RESTRICT_REF node_store );

        NodeSetSingle( NodeSetSingle const& other ) = default;
        NodeSetSingle( NodeSetSingle&& other ) = default;

        NodeSetSingle& operator=( NodeSetSingle const& other ) = default;
        NodeSetSingle& operator=( NodeSetSingle&& other ) = default;

        virtual ~NodeSetSingle() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t selectedNodeIndex() const;
        SIXTRL_HOST_FN node_id_t selectedNodeId() const;
        SIXTRL_HOST_FN c_node_id_t const* ptrSelectedCNodeId() const;

        SIXTRL_HOST_FN status_t selectNode( node_index_t const node_index );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN node_index_t selectedNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const& selectedNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN c_node_id_t const* ptrSelectedCNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t selectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t defaultNodeIndex() const;
        SIXTRL_HOST_FN node_id_t defaultNodeId() const;
        SIXTRL_HOST_FN c_node_id_t const* ptrDefaultCNodeId() const;

        SIXTRL_HOST_FN bool hasDefaultNode() const;
        SIXTRL_HOST_FN bool requiresDefaultNode() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN node_index_t defaultNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const& defaultNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN c_node_id_t const* ptrDefaultCNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasDefaultNode(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool requiresDefaultNode(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        using _node_set_base_t::canChangeToNode;
        using _node_set_base_t::changeToNode;

        SIXTRL_HOST_FN bool canChangeToNode( node_index_t const index ) const;
        SIXTRL_HOST_FN status_t changeToNode( node_index_t const index );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool canChangeToNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t changeToNode(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index );

        protected:

        SIXTRL_HOST_FN status_t doSyncWithNodeStore(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            SIXTRL_CXX_NAMESPACE::NodeStore& SIXTRL_RESTRICT_REF st ) override;

        private:

        std::atomic< node_index_t > m_selected_node_index;
        std::atomic< node_index_t > m_default_node_index;
    };

    bool NodeSetBase_is_node_set_single( SIXTRL_CXX_NAMESPACE::NodeSetBase
        const* SIXTRL_RESTRICT ptr_node_set ) SIXTRL_NOEXCEPT;

    SIXTRL_CXX_NAMESPACE::NodeSetSingle const* NodeSetBase_as_node_set_single(
        SIXTRL_CXX_NAMESPACE::NodeSetBase const*
            SIXTRL_RESTRICT ptr_node_set ) SIXTRL_NOEXCEPT;

    SIXTRL_CXX_NAMESPACE::NodeSetSingle* NodeSetBase_as_node_set_single(
        SIXTRL_CXX_NAMESPACE::NodeSetBase*
            SIXTRL_RESTRICT ptr_node_set ) SIXTRL_NOEXCEPT;
}

extern "C" {

typedef SIXTRL_CXX_NAMESPACE::NodeSetBase       NS(NodeSetBase);
typedef SIXTRL_CXX_NAMESPACE::NodeSetSingle     NS(NodeSetSingle);

bool NS(NodeSetBase_is_node_set_single)(
    NS(NodeSetBase) const* SIXTRL_RESTRICT ptr_node_set );

NS(NodeSetSingle) const* NS(NodeSetBase_as_const_node_set_single)(
    NS(NodeSetBase) const* SIXTRL_RESTRICT ptr_node_set );

NS(NodeSetSingle)* NS(NodeSetBase_as_node_set_single)(
    NS(NodeSetBase)* SIXTRL_RESTRICT ptr_node_set );

}

#else

typedef void NS(NodeSetBase);
typedef void NS(NodeSetSingle);

#endif /* C++, host */


#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
    #include <algorithm>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE NodeSetBase::node_set_id_t
    NodeSetBase::nodeSetId() const SIXTRL_NOEXCEPT
    {
        return this->m_my_node_set_id;
    }

    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::setNodeSetId(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeSetBase::node_set_id_t const node_set_id ) SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeSetBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->checkLock( lock ) ) &&
            ( ( ( node_set_id != _this_t::ILLEGAL_NODE_SET_ID ) &&
                ( this->m_my_node_set_id == _this_t::ILLEGAL_NODE_SET_ID ) ) ||
              ( ( node_set_id == _this_t::ILLEGAL_NODE_SET_ID ) &&
                ( this->m_my_node_set_id != _this_t::ILLEGAL_NODE_SET_ID ) ) ) )
        {
            this->m_my_node_set_id = node_set_id;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE NodeSetBase::size_type NodeSetBase::numNodes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->numNodes( lock );
    }

    SIXTRL_INLINE NodeSetBase::node_index_t NodeSetBase::minNodeIndex() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->minNodeIndex( lock );
    }
    SIXTRL_INLINE NodeSetBase::node_index_t NodeSetBase::maxNodeIndex() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->maxNodeIndex( lock );
    }

    SIXTRL_INLINE NodeSetBase::node_index_t
    NodeSetBase::nodeIndex( NodeSetBase::size_type const nn ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->nodeIndex( lock, nn );
    }

    SIXTRL_INLINE NodeSetBase::node_id_t const& NodeSetBase::nodeId(
        NodeSetBase::size_type const nn ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->nodeId( lock, nn );
    }

    SIXTRL_INLINE NodeSetBase::node_id_t NodeSetBase::nodeIdByNodeIndex(
        NodeSetBase::node_index_t const node_index ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->nodeIdByNodeIndex( lock, node_index );
    }

    SIXTRL_INLINE NodeSetBase::c_node_id_t const* NodeSetBase::ptrCNodeId(
        NodeSetBase::size_type const nn ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->ptrCNodeId( lock, nn );
    }

    SIXTRL_INLINE NodeSetBase::c_node_id_t const*
    NodeSetBase::ptrCNodeIdByNodeIndex(
        NodeSetBase::node_index_t const node_index ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->ptrCNodeIdByNodeIndex( lock, node_index );
    }

    SIXTRL_INLINE bool NodeSetBase::available(
        NodeSetBase::node_index_t const node_index ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->available( lock, node_index );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeSetBase::usesAutoSelect() const SIXTRL_NOEXCEPT
    {
        return this->m_use_autoselect;
    }

    SIXTRL_INLINE bool NodeSetBase::isSelected(
        NodeSetBase::node_index_t const node_index ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->isSelected( lock, node_index );
    }

    SIXTRL_INLINE bool NodeSetBase::canSelectNode(
        NodeSetBase::node_index_t const node_index ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->canSelectNode( lock, node_index );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeSetBase::isDefault(
        NodeSetBase::node_index_t const node_index ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->isDefault( lock, node_index );
    }

    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::removeDefaultNode(
        NodeSetBase::node_index_t const node_index )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->removeDefaultNode( lock, node_index );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeSetBase::canChangeSelectedNode()
        const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_can_directly_change_selected_node ) ||
                 ( this->m_can_unselect_node ) );
    }

    SIXTRL_INLINE bool NodeSetBase::canDirectlyChangeSelectedNode()
        const SIXTRL_NOEXCEPT
    {
        return this->m_can_directly_change_selected_node;
    }

    SIXTRL_INLINE bool NodeSetBase::canChangeToNode(
        NodeSetBase::node_index_t const current_node_idx,
        NodeSetBase::node_index_t const next_node_idx ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->canChangeToNode( lock, current_node_idx, next_node_idx );
    }

    SIXTRL_INLINE status_t NodeSetBase::changeToNode(
        NodeSetBase::node_index_t const current_node_idx,
        NodeSetBase::node_index_t const next_node_idx )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->changeToNode( lock, current_node_idx, next_node_idx );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeSetBase::canUnselectNode() const SIXTRL_NOEXCEPT
    {
        return this->m_can_unselect_node;
    }

    SIXTRL_INLINE bool NodeSetBase::canUnselectNode(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeSetBase::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->canUnselectNode( lock, index );
    }

    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::unselectNode(
        NodeSetBase::node_index_t const node_index )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->unselectNode( lock, index );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::addNode(
        NodeSetBase::node_index_t const node_index )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->addNode( lock, node_index );
    }

    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::addNodes(
        NodeSetBase::size_type const num_nodes,
        NodeSetBase::node_index_t const* SIXTRL_RESTRICT purposes_begin )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->addNodes( lock, num_noes, purposes_begin );
    }

    template< typename NodeIdxIter >
    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::addNodes(
        NodeIdxIter begin, NodeIdxIter end )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->addNodes( lock, begin, end );
    }

    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::removeNode(
        NodeSetBase::node_index_t const node_index  )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->removeNode( lock, node_index );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::addNodes(
            NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
            NodeSetBase::size_type const num_nodes,
            NodeSetBase::node_index_t const* SIXTRL_RESTRICT purposes_begin )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeSetBase;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->checkLock( lock ) ) return status;
        if( ( num_nodes > _this_t::size_type{ 0 } ) &&
            ( purposes_begin != nullptr ) )
        {
            status = this->doAddNodes(
                lock, purposes_begin, purposes_begin + num_nodes );
        }
        else if( ( num_nodes == _this_t::size_type{ 0 }  ) &&
                 ( purposes_begin == nullptr ) )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    template< typename NodeIdxIter >
    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::addNodes(
            NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
            NodeIdxIter begin, NodeIdxIter end )
    {
        return this->doAddNodes( lock, begin, end );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::syncWithStore()
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->syncWithStore( lock );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE NodeSetBase::sync_id_value_t
    NodeSetBase::syncIdValue() const SIXTRL_NOEXCEPT
    {
        return this->m_sync_id.load();
    }

    SIXTRL_INLINE NodeSetBase::sync_id_t const&
    NodeSetBase::syncId() const SIXTRL_NOEXCEPT
    {
        return this->m_sync_id;
    }

    SIXTRL_INLINE bool NodeSetBase::isSyncWith( NodeSetBase::sync_id_t const&
        SIXTRL_RESTRICT_REF sid ) const SIXTRL_NOEXCEPT
    {
        return ( this->m_sync_id.load() == sid.load() );
    }

    SIXTRL_INLINE bool NodeSetBase::isSyncWith(
        NodeSetBase::sync_id_value_t const sync_id_value ) const SIXTRL_NOEXCEPT
    {
        return ( this->m_sync_id.load() == sync_id_value );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE NodeSetBase::node_store_t const&
    NodeSetBase::nodeStore() const SIXTRL_NOEXCEPT
    {
        return this->m_node_store;
    }

    SIXTRL_INLINE NodeSetBase::node_store_t const*
    NodeSetBase::ptrNodeStore() const SIXTRL_NOEXCEPT
    {
        return &this->m_node_store;
    }

    SIXTRL_INLINE NodeSetBase::node_store_t& NodeSetBase::nodeStore()
    {
        return this->m_node_store;
    }

    SIXTRL_INLINE NodeSetBase::node_store_t*
    NodeSetBase::ptrNodeStore() SIXTRL_NOEXCEPT
    {
        return &this->m_node_store;
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeSetBase::checkLock( NodeSetBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->lockable() != nullptr ) &&
                 ( this->lockable() == lock.mutex() ) &&
                 ( lock.owns_lock() ) );
    }

    SIXTRL_INLINE NodeSetBase::lockable_t*
    NodeSetBase::lockable() const SIXTRL_NOEXCEPT
    {
        return this->m_node_store.lockable();
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeSetBase::isSingleNodeSet() const SIXTRL_NOEXCEPT
    {
        return this->m_is_single_node_set;
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE NodeSetBase::size_type NodeSetBase::doGetNumSelectedNodes(
            NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );

        SIXTRL_ASSERT( this->m_selected_node_indices.size() >=
                       this->m_min_num_default_nodes );

        SIXTRL_ASSERT( this->m_selected_node_indices.size() <=
                       this->m_max_num_default_nodes );

        return this->m_selected_node_indices.size();
    }

    SIXTRL_INLINE NodeSetBase::size_type
    NodeSetBase::doGetMinNumSelectableNodes( NodeSetBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->m_min_num_selectable_nodes;
    }

    SIXTRL_INLINE NodeSetBase::size_type
    NodeSetBase::doGetMaxNumSelectableNodes( NodeSetBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->m_max_num_selectable_nodes;
    }

    SIXTRL_INLINE bool NodeSetBase::doCheckIfNodeIsSelected(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeSetBase::node_index_t const node_index ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;

        bool const is_selected = (
            ( node_index != _this_t::UNDEFINED_INDEX ) &&
            ( this->checkLock( lock ) ) &&
            ( std::binary_search( this->m_selected_node_indices.begin(),
                this->m_selected_node_indices, node_index ) ) );

        SIXTRL_ASSERT( ( !is_selected ) ||
            ( ( this->available( lock, node_index ) ) &&
              ( std::is_sorted( this->m_selected_node_indices.begin(),
                                this->m_selected_node_indices.end() ) ) ) );

        return is_selected;
    }

    SIXTRL_INLINE NodeSetBase::node_index_t const*
    NodeSetBase::doGetSelectedNodeIndicesBegin( NodeSetBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        return ( this->checkLock( lock ) )
            ? this->m_selected_node_indices.data() : nullptr;

    }

    SIXTRL_INLINE NodeSetBase::node_index_t const*
    NodeSetBase::doGetSelectedNodeIndicesEnd( NodeSetBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::node_index_t const* end_ptr = nullptr;

        if( this->checkLock( lock ) )
        {
            end_ptr = this->m_selected_node_indices.data();
            SIXTRL_ASSERT( end_ptr != nullptr );
            std::advance( end_ptr, this->m_selected_node_indices.size() );
        }

        return end_ptr;
    }

    SIXTRL_INLINE NodeSetBase::node_index_t*
    NodeSetBase::doGetSelectedNodeIndicesBegin(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        return const_cast< _this_t::node_index_t* >( static_cast<
            _this_t const& >( *this ).doGetSelectedNodeIndicesBegin( lock ) );
    }

    SIXTRL_INLINE NodeSetBase::node_index_t*
    NodeSetBase::doGetSelectedNodeIndicesEnd(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        return const_cast< _this_t::node_index_t* >( static_cast<
            _this_t const& >( *this ).doGetSelectedNodeIndicesEnd( lock ) );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE NodeSetBase::size_type NodeSetBase::doGetNumDefaultNodes(
        NodeSetBase::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        SIXTRL_ASSERT( this->m_min_num_default_nodes <=
                       this->m_default_node_indices.size() );
        SIXTRL_ASSERT( this->m_max_num_default_nodes >=
                       this->m_default_node_indices.size() );

        return this->m_default_node_indices.size();
    }

    SIXTRL_INLINE NodeSetBase::size_type NodeSetBase::doGetMinNumDefaultNodes(
        NodeSetBase::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->m_min_num_default_nodes;
    }

    SIXTRL_INLINE NodeSetBase::size_type NodeSetBase::doGetMaxNumDefaultNodes(
        NodeSetBase::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->m_max_num_default_nodes;
    }

    SIXTRL_INLINE NodeSetBase::node_index_t const*
    NodeSetBase::doGetDefaultNodeIndicesBegin( NodeSetBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? this->m_default_node_indices.data() : nullptr;
    }

    SIXTRL_INLINE NodeSetBase::node_index_t const*
    NodeSetBase::doGetDefaultNodeIndicesEnd( NodeSetBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::node_index_t const* end_ptr = nullptr;

        if( this->checkLock( lock ) )
        {
            end_ptr = this->m_default_node_indices.data();
            SIXTRL_ASSERT( end_ptr != nullptr );
            std::advance( end_ptr, this->m_default_node_indices.size() );
        }

        return end_ptr;
    }

    SIXTRL_INLINE NodeSetBase::node_index_t*
    NodeSetBase::doGetDefaultNodeIndicesBegin(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        return const_cast< _this_t::node_index_t* >( static_cast<
            _this_t const& >( *this ).doGetDefaultNodeIndicesBegin( lock ) );
    }

    SIXTRL_INLINE NodeSetBase::node_index_t*
    NodeSetBase::doGetDefaultNodeIndicesEnd(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        return const_cast< _this_t::node_index_t* >( static_cast<
            _this_t const& >( *this ).doGetDefaultNodeIndicesEnd( lock ) );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeSetBase::doCheckNodeIdsAndNodeIndicesAreSync(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;

        bool is_sync = false;

        if( ( this->checkLock( lock ) ) &&
            ( this->nodeSetId() != _this_t::ILLEGAL_DEVICE_ID ) &&
            ( this->m_assigned_node_indices.size() ==
              this->m_node_ids_buffer.size() ) )
        {
            SIXTRL_ASSERT( this->nodeStore().hasKernelSet(
                lock, this->kernelSetId() ) );

            auto idx_it  = this->m_assigned_node_indices.begin();
            auto idx_end = this->m_assigned_node_indices.end();
            auto node_id_it = this->m_node_ids_buffer.begin();

            is_sync = true;

            for( ; idx_it != idx_end ; ++idx_it, ++node_id_it )
            {
                auto ptr_node = this->nodeStore()->ptrNodeInfoBase(
                    lock, *idx_it );

                if( ( ptr_node == nullptr ) ||
                    ( !this->nodeStore()->isNodeAttachedToSet(
                        lock, *idx_it, this->kernelSetId() ) ) )
                {
                    is_sync = false;
                    break;
                }

                if( ::NS(NodeId_are_not_equal)( &( *node_id_it ),
                            ptr_node->nodeId().getCApiPtr() ) )
                {
                    is_sync = false;
                    break;
                }
            }
        }

        return is_sync;
    }

    /* -------------------------------------------------------------------- */

    template< typename NodeIdxIter >
    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::doAddNodes(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeIdxIter begin, NodeIdxIter end )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeSetBase;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->checkLock( lock ) ) return status;
        std::ptrdiff_t const in_len = std::distance( begin, end );

        if( in_len > std::ptrdiff_t{ 0 } )
        {
            SIXTRL_ASSERT( std::is_sorted(
                this->m_assigned_node_indices.begin(),
                this->m_assigned_node_indices.end() ) );

            _this_t::size_type const current_num_nodes =
                this->m_assigned_node_indices.size();

            this->m_assigned_node_indices.insert(
                this->m_assigned_node_indices.end(), begin, end );

            std::sort( this->m_assigned_node_indices.begin(),
                       this->m_assigned_node_indices.end() );

            this->m_assigned_node_indices.erase( std::unique(
                this->m_assigned_node_indices.begin(),
                this->m_assigned_node_indices.end() ),
                    this->m_assigned_node_indices.end() );

            if( current_num_nodes < this->m_assigned_node_indices.size() )
            {
                status = st::ARCH_STATUS_SUCCESS;
                this->m_node_ids_buffer.clear();
                this->m_node_ids_buffer.reserve(
                    this->m_assigned_node_indices.size() );

                auto it  = this->m_assigned_node_indices.begin();
                auto end = this->m_assigned_node_indices.end();

                for( ; it != end ; ++it )
                {
                    auto ptr_node = this->nodeStore().ptrNodeInfoBase(
                        lock, *it, this->kernelSetId() );

                    if( ptr_node == nullptr )
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                        break;
                    }

                    this->m_node_ids_buffer.push_back(
                        *( ptr_node->nodeId().getCApiPtr() ) );
                }

                this->registerChange( lock );
            }
        }

        return status;
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE void NodeSetBase::doSetIsSingleNodeSetFlag(
            bool const flag ) SIXTRL_NOEXCEPT
    {
        this->m_is_single_node_set = flag;
    }

    SIXTRL_INLINE void NodeSetBase::doSetAllowDuplicatesNodesFlag(
        bool const flag ) SIXTRL_NOEXCEPT
    {
        this->m_allows_duplicate_nodes = flag;
    }

    SIXTRL_INLINE void NodeSetBase::doSetCanDirectlyChangeSelectedNodeFlag(
        bool const flag ) SIXTRL_NOEXCEPT
    {
        this->m_can_directly_change_selected_node = flag;
    }

    SIXTRL_INLINE void NodeSetBase::doSetCanUnselectNodeFlag(
        bool const flag ) SIXTRL_NOEXCEPT
    {
        this->m_can_unselect_node = flag;
    }

    SIXTRL_INLINE void NodeSetBase::doSetUseAutoselectFlag(
        bool const flag ) SIXTRL_NOEXCEPT
    {
        this->m_use_autoselect = flag;
    }

    /* ********************************************************************* */
    /* NodeSetSingle: */


    bool NodeSetBase_is_node_set_single( SIXTRL_CXX_NAMESPACE::NodeSetBase
        const* SIXTRL_RESTRICT ptr_node_set ) SIXTRL_NOEXCEPT
    {
        return ( ( ptr_node_set != nullptr ) &&
                 ( ptr_node_set->isSingleNodeSet() ) );
    }

    SIXTRL_CXX_NAMESPACE::NodeSetSingle const* NodeSetBase_as_node_set_single(
        SIXTRL_CXX_NAMESPACE::NodeSetBase const*
            SIXTRL_RESTRICT ptr_node_set ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( st::NodeSetBase_is_node_set_single( ptr_node_set ) )
            ? static_cast< SIXTRL_CXX_NAMESPACE::NodeSetSingle const* >(
                ptr_node_set )
            : nullptr;
    }

    SIXTRL_CXX_NAMESPACE::NodeSetSingle* NodeSetBase_as_node_set_single(
        SIXTRL_CXX_NAMESPACE::NodeSetBase*
            SIXTRL_RESTRICT ptr_node_set ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( st::NodeSetBase_is_node_set_single( ptr_node_set ) )
            ? static_cast< SIXTRL_CXX_NAMESPACE::NodeSetSingle* >(
                ptr_node_set ) : nullptr;
    }

    /* --------------------------------------------------------------------- */

     SIXTRL_INLINE NodeSetSingle::NodeSetSingle(
        st::NodeStore& SIXTRL_RESTRICT_REF node_store,
        NodeSetSingle::size_type const num_nodes,
        NodeSetSingle::node_index_t const* SIXTRL_RESTRICT indices_begin ) :
        SIXTRL_CXX_NAMESPACE::NodeSetBase(
            node_store, num_nodes, indices_begin )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *node_store.lockable() );

        this->doSetIsSingleNodeSetFlag( true );
        this->doSetMaxNumSelectableNodes( lock, _this_t::size_type{ 1 } );
    }

    template< typename NodeIdxIter >
    SIXTRL_INLINE NodeSetSingle::NodeSetSingle(
        st::NodeStore& SIXTRL_RESTRICT_REF node_store,
        NodeIdxIter begin, NodeIdxIter end ) :
        SIXTRL_CXX_NAMESPACE::NodeSetBase( node_store, begin, end )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *node_store.lockable() );

        this->doSetIsSingleNodeSetFlag( true );
        this->doSetMaxNumSelectableNodes( lock, _this_t::size_type{ 1 } );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeSetSingle::node_index_t
    NodeSetSingle::selectedNodeIndex() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *this->lockable() );
        return this->selectedNodeIndex( lock );
    }

    SIXTRL_INLINE NodeSetSingle::node_id_t
    NodeSetSingle::selectedNodeId() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *this->lockable() );
        return this->selectedNodeId( lock );
    }

    SIXTRL_INLINE NodeSetSingle::c_node_id_t const*
    NodeSetSingle::ptrSelectedCNodeId() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *this->lockable() );
        return this->ptrSelectedCNodeId( lock );
    }

    SIXTRL_INLINE NodeSetSingle::status_t NodeSetSingle::selectNode(
        NodeSetSingle::node_index_t const node_index )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *this->lockable() );
        return this->selectNode( lock, node_index );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE NodeSetSingle::node_index_t NodeSetSingle::selectedNodeIndex(
        NodeSetSingle::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::node_index_t selected_node_index = _this_t::UNDEFINED_INDEX;

        if( ( this->checkLock( lock ) ) &&
            ( this->doGetNumSelectedNodes( lock ) == _this_t::size_type{ 1 } ) )
        {
            selected_node_index = *this->doGetSelectedNodeIndicesBegin( lock );
        }

        return selected_node_index;
    }

    SIXTRL_INLINE NodeSetSingle::node_id_t const& NodeSetSingle::selectedNodeId(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::node_index_t node_index = this->selectedNodeIndex( lock );
        return this->nodeIdByNodeIndex( lock, node_index );
    }

    SIXTRL_INLINE NodeSetSingle::c_node_id_t const*
    NodeSetSingle::ptrSelectedCNodeId( NodeSetSingle::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::node_index_t node_index = this->selectedNodeIndex( lock );
        return this->ptrCNodeIdByNodeIndex( lock, node_index );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeSetSingle::node_index_t
    NodeSetSingle::defaultNodeIndex() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *this->lockable() );
        return this->defaultNodeIndex( lock );
    }

    SIXTRL_INLINE NodeSetSingle::node_id_t NodeSetSingle::defaultNodeId() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *this->lockable() );
        return this->defaultNodeId( lock );
    }

    SIXTRL_INLINE NodeSetSingle::c_node_id_t const*
    NodeSetSingle::ptrDefaultCNodeId() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *this->lockable() );
        return this->ptrDefaultCNodeId( lock );
    }

    SIXTRL_INLINE bool NodeSetSingle::hasDefaultNode() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *this->lockable() );
        return this->hasDefaultNode( lock );
    }

    SIXTRL_INLINE bool NodeSetSingle::requiresDefaultNode() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *this->lockable() );
        return this->requiresDefaultNode( lock );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE NodeSetSingle::node_index_t
    NodeSetSingle::defaultNodeIndex( NodeSetSingle::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::node_index_t default_node_index = _this_t::UNDEFINED_INDEX;

        if( ( this->checkLock( lock ) ) &&
            ( this->doGetNumDefaultNodes( lock ) == _this_t::size_type{ 1 } ) )
        {
            default_node_index = *this->doGetDefaultNodeIndicesBegin( lock );
        }

        return default_node_index;
    }

    SIXTRL_INLINE NodeSetSingle::node_id_t const& NodeSetSingle::defaultNodeId(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::node_index_t const node_index = this->defaultNodeIndex( lock );
        return this->nodeIdByNodeIndex( lock, node_index );
    }

    SIXTRL_INLINE NodeSetSingle::c_node_id_t const*
    NodeSetSingle::ptrDefaultCNodeId( NodeSetSingle::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::node_index_t const node_index = this->defaultNodeIndex( lock );
        return this->ptrCNodeIdByNodeIndex( lock, node_index );
    }

    SIXTRL_INLINE bool NodeSetSingle::hasDefaultNode( NodeSetSingle::lock_t
        const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::node_index_t const node_index = this->defaultNodeIndex( lock );
        return ( node_index != _this_t::UNDEFINED_INDEX );
    }

    SIXTRL_INLINE bool NodeSetSingle::requiresDefaultNode( NodeSetSingle::lock_t
        const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        return ( this->doGetMinNumDefaultNodes( lock ) >
                _this_t::size_type{ 0 } );
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE NodeSetSingle::status_t NodeSetSingle::changeToNode(
        NodeSetSingle::node_index_t const index )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *this->lockable() );
        return this->changeToNode( lock, index );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    SIXTRL_INLINE NodeSetSingle::status_t NodeSetSingle::changeToNode(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeSetSingle::node_index_t const index )
    {
        return this->changeToNode(
            lock, this->selectedNodeIndex( lock ), index );
    }
}

#endif /* c++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_SET_CXX_HPP__ */

/* end: sixtracklib/common/control/node_set.hpp */
