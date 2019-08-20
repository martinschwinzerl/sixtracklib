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
        using status_t             = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using c_node_id_t          = node_id_t::c_api_t;
        using arch_id_t            = node_id_t::arch_id_t;
        using platform_id_t        = node_id_t::platform_id_t;
        using device_id_t          = node_id_t::device_id_t;
        using size_type            = node_id_t::size_type;
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

        SIXTRL_HOST_FN bool supportsChangingNode() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
            supportsDirectlyChangingSelectedNode() const SIXTRL_NOEXCEPT;

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

        SIXTRL_HOST_FN bool supportsUnselectingNode() const SIXTRL_NOEXCEPT;

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

        SIXTRL_HOST_FN bool isSyncWithStore() const SIXTRL_NOEXCEPT;

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
            NodeSetBase const& SIXTRL_RESTRICT_REF node_info );

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
            node_index_t const current_node_idx );

        SIXTRL_HOST_FN virtual status_t doPrintNodeInfos(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            std::ostream& SIXTRL_RESTRICT_REF output_stream ) const;

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

        SIXTRL_HOST_FN void doSetExpectedSyncIdValue(
            sync_id_value_t const expected_sync_id_value ) SIXTRL_NOEXCEPT;

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

        SIXTRL_CXX_NAMESPACE::NodeStore&  m_node_store;

        sync_id_value_t                   m_expected_sync_id_value;
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

    SIXTRL_STATIC SIXTRL_HOST_FN bool NodeSet_is_node_set_single(
        const SIXTRL_CXX_NAMESPACE::NodeSetBase
        *const SIXTRL_RESTRICT ptr_node_set ) SIXTRL_NOEXCEPT;

    SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::NodeSetSingle const*
    NodeSet_as_node_set_single( SIXTRL_CXX_NAMESPACE::NodeSetBase const*
            SIXTRL_RESTRICT ptr_node_set ) SIXTRL_NOEXCEPT;

    SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::NodeSetSingle*
    NodeSet_as_node_set_single( SIXTRL_CXX_NAMESPACE::NodeSetBase*
            SIXTRL_RESTRICT ptr_node_set ) SIXTRL_NOEXCEPT;
}

extern "C" {

typedef SIXTRL_CXX_NAMESPACE::NodeSetBase       NS(NodeSetBase);
typedef SIXTRL_CXX_NAMESPACE::NodeSetSingle     NS(NodeSetSingle);

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeSet_is_node_set_single)(
    const NS(NodeSetBase) *const SIXTRL_RESTRICT ptr_node_set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeSetSingle) const*
NS(NodeSet_as_const_node_set_single)(
    NS(NodeSetBase) const* SIXTRL_RESTRICT ptr_node_set );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeSetSingle)* NS(NodeSet_as_node_set_single)(
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

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeSetBase::supportsChangingNode()
        const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_can_directly_change_selected_node ) ||
                 ( this->m_can_unselect_node ) );
    }

    SIXTRL_INLINE bool NodeSetBase::supportsDirectlyChangingSelectedNode()
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

    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::changeToNode(
        NodeSetBase::node_index_t const current_node_idx,
        NodeSetBase::node_index_t const next_node_idx )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->changeToNode( lock, current_node_idx, next_node_idx );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    NodeSetBase::supportsUnselectingNode() const SIXTRL_NOEXCEPT
    {
        return this->m_can_unselect_node;
    }

    SIXTRL_INLINE bool NodeSetBase::canUnselectNode(
        NodeSetBase::node_index_t const index ) const
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
        return this->unselectNode( lock, node_index );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeSetBase::isSyncWithStore() const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        return ( ( this->nodeSetId() != _this_t::ILLEGAL_NODE_SET_ID ) &&
                 ( this->ptrNodeStore() != nullptr ) &&
                 ( this->nodeStore().isSyncWith(
                     this->m_expected_sync_id_value ) ) );
    }

    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::syncWithStore()
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->syncWithStore( lock );
    }

    SIXTRL_INLINE NodeSetBase::size_type
    NodeSetBase::requiredOutStringLength() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->requiredOutStringLength( lock );
    }

    SIXTRL_INLINE void NodeSetBase::print(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        this->print( lock, output );
    }

    SIXTRL_INLINE void NodeSetBase::print(
        ::FILE* SIXTRL_RESTRICT output ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        this->print( lock, output );
    }

    SIXTRL_INLINE void NodeSetBase::printOut() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        this->printOut();
    }

    SIXTRL_INLINE std::string NodeSetBase::toString() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->toString( lock );
    }

    SIXTRL_INLINE NodeSetBase::status_t NodeSetBase::toString(
        NodeSetBase::size_type const out_str_capacity,
        char* SIXTRL_RESTRICT out_str ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->toString( out_str_capacity, out_str );
    }

    SIXTRL_INLINE std::ostream& operator<<(
        std::ostream& SIXTRL_RESTRICT_REF output,
        NodeSetBase const& SIXTRL_RESTRICT_REF node_set )
    {
        node_set.print( output );
        return output;
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

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE void NodeSetBase::doSetExpectedSyncIdValue(
        NodeSetBase::sync_id_value_t const exp_sync_id_value ) SIXTRL_NOEXCEPT
    {
        this->m_expected_sync_id_value = exp_sync_id_value;
    }

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


    SIXTRL_INLINE bool NodeSet_is_node_set_single(
    SIXTRL_CXX_NAMESPACE::NodeSetBase const* SIXTRL_RESTRICT
        ptr_node_set ) SIXTRL_NOEXCEPT
    {
        return ( ( ptr_node_set != nullptr ) &&
                 ( ptr_node_set->isSingleNodeSet() ) );
    }

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeSetSingle const*
    NodeSet_as_node_set_single( SIXTRL_CXX_NAMESPACE::NodeSetBase const*
            SIXTRL_RESTRICT ptr_node_set ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeSetSingle;

        return ( st::NodeSet_is_node_set_single( ptr_node_set ) )
            ? static_cast< _this_t const* >( ptr_node_set ) : nullptr;
    }

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeSetSingle*
    NodeSet_as_node_set_single( SIXTRL_CXX_NAMESPACE::NodeSetBase*
            SIXTRL_RESTRICT ptr_node_set ) SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeSetSingle;

        return ( st::NodeSet_is_node_set_single( ptr_node_set ) )
            ? static_cast< _this_t* >( ptr_node_set ) : nullptr;
    }

    /* --------------------------------------------------------------------- */

     SIXTRL_INLINE NodeSetSingle::NodeSetSingle(
        SIXTRL_CXX_NAMESPACE::NodeStore& SIXTRL_RESTRICT_REF node_store ) :
        SIXTRL_CXX_NAMESPACE::NodeSetBase( node_store )
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
        return this->m_selected_node_index.load();
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

    SIXTRL_INLINE NodeSetSingle::node_id_t const& NodeSetSingle::selectedNodeId(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        return this->nodeIdByNodeIndex( lock, this->selectedNodeIndex() );
    }

    SIXTRL_INLINE NodeSetSingle::c_node_id_t const*
    NodeSetSingle::ptrSelectedCNodeId( NodeSetSingle::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return this->ptrCNodeIdByNodeIndex( lock, this->selectedNodeIndex() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeSetSingle::node_index_t
    NodeSetSingle::defaultNodeIndex() const
    {
        return this->m_default_node_index.load();
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

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE NodeSetSingle::node_id_t const& NodeSetSingle::defaultNodeId(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        return this->nodeIdByNodeIndex( lock, this->defaultNodeIndex() );
    }

    SIXTRL_INLINE NodeSetSingle::c_node_id_t const*
    NodeSetSingle::ptrDefaultCNodeId( NodeSetSingle::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return this->ptrCNodeIdByNodeIndex( lock, this->defaultNodeIndex() );
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

    SIXTRL_INLINE bool NodeSetSingle::canChangeToNode(
        NodeSetSingle::node_index_t const index ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        _this_t::lock_t const lock( *this->lockable() );
        return this->canChangeToNode( lock, index );
    }
}

#endif /* c++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_SET_CXX_HPP__ */

/* end: sixtracklib/common/control/node_set.hpp */
