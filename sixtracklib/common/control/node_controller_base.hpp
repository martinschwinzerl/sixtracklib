#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_CONTROLLER_BASE_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_CONTROLLER_BASE_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
        #include <cstddef>
        #include <cstdlib>
        #include <string>
        #include <iostream>
        #include <stdexcept>
        #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/node_info.h"
    #include "sixtracklib/common/control/controller_base.hpp"
    #include "sixtracklib/common/control/node_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/controller_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class NodeControllerBase : public SIXTRL_CXX_NAMESPACE::ControllerBase
    {
        private:

        using _controller_base_t   = ControllerBase;

        public:

        using size_type         = _controller_base_t::size_type;
        using arch_id_t         = _controller_base_t::arch_id_t;

        using node_id_t         = SIXTRL_CXX_NAMESPACE::NodeId;
        using node_info_base_t  = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        using node_store_t      = SIXTRL_CXX_NAMESPACE::NodeStore;
        using platform_id_t     = node_id_t::platform_id_t;
        using device_id_t       = node_id_t::device_id_t;
        using node_index_t      = node_id_t::index_t;
        using lockable_t        = node_store_t::lockable_t;
        using lock_t            = node_store_t::lock_t;

        static SIXTRL_CONSTEXPR_OR_CONST arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static SIXTRL_CONSTEXPR_OR_CONST platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PATFORM_ID;

        static SIXTRL_CONSTEXPR_OR_CONST device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PATFORM_ID;

        static SIXTRL_CONSTEXPR_OR_CONST node_index_t UNDEFINED_INDEX =
            SIXTRL_CXX_NAMESPACE::NODE_UNDEFINED_INDEX;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_store_t const& nodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_store_t const* ptrNodeStore() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSyncWithNodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_t registerNodeStoreChange() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t syncWithNodeStore();
        SIXTRL_HOST_FN status_t syncWithNodeStore(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t numAvailableNodes() const;

        SIXTRL_HOST_FN node_index_t numAvailableNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< typename... Args >
        SIXTRL_HOST_FN bool isNodeAvailable( Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN bool isNodeAvailable(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_NOEXCEPT;

        /* ---------------------------------------------------------------- */

        SIXTRL_HOST_FN bool isNodeInitialized(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN bool isNodeInitialized(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t initializeNode(
            node_index_t const node_index );

        SIXTRL_HOST_FN status_t initializeNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        /* ---------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasSelectedNode() const;
        SIXTRL_HOST_FN bool hasSelectedNode(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t selectedNodeIndex() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_index_t selectedNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string selectedNodeIdStr() const;
        SIXTRL_HOST_FN std::string selectedNodeIdStr(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t selectedNodeIdStr(
            size_type const node_id_str_capacity,
            char* SIXTRL_RESTRICT node_id_str_begin ) const;

        SIXTRL_HOST_FN status_t selectedNodeIdStr(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const node_id_str_capacity,
            char* SIXTRL_RESTRICT node_id_str_begin ) const;

        SIXTRL_HOST_FN char const* ptrSelectedNodeIdStr() const;
        SIXTRL_HOST_FN char const* ptrSelectedNodeIdStr(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* ptrSelectedNodeId() const;
        SIXTRL_HOST_FN node_id_t const* ptrSelectedNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_base_t const* ptrSelectedNodeInfoBase() const;
        SIXTRL_HOST_FN node_info_base_t const* ptrSelectedNodeInfoBase(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        template< typename... Args >
        SIXTRL_HOST_FN bool isSelectedNode( Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN bool isSelectedNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool usesAutoSelect() const SIXTRL_NOEXCEPT;

        template< typename Args... >
        SIXTRL_HOST_FN status_t selectNode( Args&&... args );

        template< typename Args... >
        SIXTRL_HOST_FN status_t selectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock, Args&&... args );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canChangeSelectedNode() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool canDirectlyChangeSelectedNode() const SIXTRL_NOEXCEPT;

        template< typename Args... >
        SIXTRL_HOST_FN status_t changeSelectedNode( Args&&... args );

        template< typename Args... >
        SIXTRL_HOST_FN status_t changeSelectedNode(
            lock_t const SIXTRL_RESTRICT_REF lock, Args&&... args );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canUnselectNode() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_t unselectNode();

        template< typename Args... >
        SIXTRL_HOST_FN status_t unselectNode( Args&&... args );

        template< typename Args... >
        SIXTRL_HOST_FN status_t unselectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock, Args&&... args );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasDefaultNode() const;
        SIXTRL_HOST_FN bool hasDefaultNode(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t defaultNodeIndex() const;
        SIXTRL_HOST_FN node_index_t defaultNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* ptrDefaultNodeId() const;
        SIXTRL_HOST_FN node_id_t const* ptrDefaultNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_base_t const* ptrDefaultNodeInfoBase() const;
        SIXTRL_HOST_FN node_info_base_t const* ptrDefaultNodeInfoBase(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        template< typename... Args >
        SIXTRL_HOST_FN bool isDefaultNode( Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN bool isDefaultNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        template< typename... Args >
        SIXTRL_HOST_FN node_index_t nodeIndex( Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN node_index_t nodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            arch_id_t const arch_id, platform_id_t const platform_id,
            device_id_t const device_id ) const;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id, platform_id_t const platform_id,
            device_id_t const device_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            platform_id_t const platform_id,
            device_id_t const device_id ) const;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            platform_id_t const platform_id,
            device_id_t const device_id ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        template< typename... Args >
        SIXTRL_HOST_FN node_id_t const* ptrNodeId( Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN node_id_t const* ptrNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* ptrNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        template< typename... Args >
        SIXTRL_HOST_FN node_info_base_t const* ptrNodeInfoBase(
            Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN node_info_base_t const* ptrNodeInfoBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_base_t const* ptrNodeInfoBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t const* nodeIndicesBegin() const;
        SIXTRL_HOST_FN node_index_t const* nodeIndicesEnd() const;

        SIXTRL_HOST_FN node_id_t const* nodeIdsBegin() const;
        SIXTRL_HOST_FN node_id_t const* nodeIdsEnd() const;

        SIXTRL_HOST_FN node_id_t const& nodeId(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN std::string nodeIdString(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN char const* nodeIdString(
            node_index_t const node_index ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN node_index_t const* nodeIndicesBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* nodeIndicesEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* nodeIdsBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* nodeIdsEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const& nodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN std::string nodeIdString(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN char const* nodeIdString(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type requiredAvailableNodeInfosStrCapacity() const;

        SIXTRL_HOST_FN void printAvailableNodeInfos(
            std::ostream& SIXTRL_RESTRICT_REF output ) const;

        SIXTRL_HOST_FN void printOutAvailableNodeInfos(
            ::FILE* SIXTRL_RESTRICT output ) const;

        SIXTRL_HOST_FN void printOutAvailableNodeInfos() const;

        SIXTRL_HOST_FN std::string availableNodeInfosToString() const;

        SIXTRL_HOST_FN status_t availableNodeInfosToString(
            size_type capacity, char* SIXTRL_RESTRICT node_info_str) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual ~NodeControllerBase() SIXTRL_NOEXCEPT;

        protected:

        using ptr_node_info_base_t = std::unique_ptr< node_info_base_t >;
        using node_index_buffer_t  = std::vector< node_index_t >;
        using node_id_buffer_t     = std::vector< node_id_t >;
        using node_id_str_buffer_t = std::vector< char >;

        static SIXTRL_CONSTEXPR_OR_CONST size_type
            NODE_ID_STR_CAPACITY = size_type{ 64 };

        SIXTRL_HOST_FN NodeControllerBase(
            arch_id_t const arch_id,
            const char *const SIXTRL_RESTRICT arch_str,
            const char *const SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN NodeControllerBase(
            NodeControllerBase const& other ) = default;

        SIXTRL_HOST_FN NodeControllerBase(
            NodeControllerBase&& other ) = default;

        SIXTRL_HOST_FN NodeControllerBase& operator=(
            NodeControllerBase const& rhs ) = default;

        SIXTRL_HOST_FN NodeControllerBase& operator=(
            NodeControllerBase&& rhs ) = default;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN node_store_t& nodeStore() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_store_t* ptrNodeStore() SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN virtual void doClear() override;

        SIXTRL_HOST_FN virtual bool doCheckIsNodeInitialized(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index );

        SIXTRL_HOST_FN virtual status_t doInitializeNode(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index );

        SIXTRL_HOST_FN virtual status_t doSyncWithNodeStore(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_store_t* SIXTRL_RESTRICT ptr_node_store );

        SIXTRL_HOST_FN virtual status_t doSelectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        SIXTRL_HOST_FN virtual status_t doChangeSelectedNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const new_selected_node_index );

        SIXTRL_HOST_FN virtual status_t doUnselectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const selected_node_index );

        SIXTRL_HOST_FN virtual node_index_t doFindDefaultNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN virtual status_t doPrintToOutputStream(
            std::ostream& SIXTRL_RESTRICT_REF output ) const override;

        SIXTRL_HOST_FN virtual status_t doPrintAvailableNodesToOutputStream(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            std::ostream& SIXTRL_RESTRICT_REF output ) const override;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN void doSetIsSyncWithNodeStoreFlag(
            bool const is_sync_with_node_store ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetCanDirectlyChangeSelectedNodeFlag(
            bool const can_directly_change_selected_node ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetCanUnselectNodeFlag(
            bool const can_unselect_node ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetUseAutoSelectFlag(
            bool const use_autoselect ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool doCheckIfNodeIndexIsAvailableLocally(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doAttachAllArchNodesToController(
            lock_t const& SIXTRL_RESTRIC_REF lock );

        private:

        SIXTRL_HOST_FN void doClearNodeControllerBaseImpl(
            lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        node_store_t&                           m_node_store;
        node_index_buffer_t                     m_available_node_indices;
        node_id_buffer_t                        m_available_node_ids;
        std::vector< node_id_str_buffer_t >     m_available_node_id_strings;

        node_index_t                            m_selected_node_index;
        node_index_t                            m_default_node_index;
        node_index_t                            m_num_available_nodes;

        bool                 m_can_directly_change_selected_node;
        bool                 m_node_change_requires_kernels;
        bool                 m_can_unselect_node;
        bool                 m_use_autoselect;
        bool                 m_nodes_are_sync;
    };

    SIXTRL_STATIC SIXTRL_HOST_FN NodeControllerBase const* asNodeController(
        ControllerBase const* SIXTRL_RESTRICT base_controller );

    SIXTRL_STATIC SIXTRL_HOST_FN NodeControllerBase* asNodeController(
        ControllerBase* SIXTRL_RESTRICT base_controller );
}

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

typedef SIXTRL_CXX_NAMESPACE::NodeControllerBase NS(NodeControllerBase);

#else /* C++, Host */

typedef void NS(NodeControllerBase);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeControllerBase::node_store_t const&
    NodeControllerBase::nodeStore() const SIXTRL_NOEXCEPT
    {
        return this->m_node_store;
    }

    SIXTRL_INLINE NodeControllerBase::node_store_t const*
    NodeControllerBase::ptrNodeStore() const SIXTRL_NOEXCEPT
    {
        return &this->m_node_store;
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::numAvailableNodes() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->numAvailableNodes( lock );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE bool
    NodeControllerBase::isSyncWithNodeStore() const SIXTRL_NOEXCEPT
    {
        return this->m_nodes_are_sync;
    }

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::registerNodeStoreChange() SIXTRL_NOEXCEPT
    {
        this->m_nodes_are_sync = false;
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::syncWithNodeStore()
    {
        NodeControllerBase::lock_t lock( this->nodeStore().lockable() );
        return this->doSyncWithNodeStore( lock, &this->m_node_store );
    }

    /* --------------------------------------------------------------------- */

    template< typename... Args >
    bool NodeControllerBase::isNodeAvailable( Args&&... args ) const
    {
        NodeControllerBase::lock_t lock( this->nodeStore().lockable() );
        return this->isNodeAvailable( lock, std::forward< Args >( args )... );
    }

    template< typename... Args >
    bool NodeControllerBase::isNodeAvailable(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args ) const SIXTRL_NOEXCEPT
    {
        using _this_t = NodeControllerBase;

        _this_t::node_index_t const index = this->nodeIndex( lock,
            std::forward< Args >( args )... );

        return ( ( index != _this_t::UNDEFINED_INDEX ) &&
            ( this->nodeStore().checkLock( lock ) ) &&
            ( this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeControllerBase::isNodeInitialized(
        NodeControllerBase::node_index_t const node_index ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        this->nodeStore().checkLockAndThrowOnError( lock );
        return this->isNodeInitialized( lock, node_index );
    }

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::initializeNode(
        NodeControllerBase::node_index_t const node_index )
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        this->nodeStore().checkLockAndThrowOnError( lock );
        return this->initializeNode( lock, node_index );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE bool NodeControllerBase::isNodeInitialized(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const node_index ) const
    {
        SIXTRL_ASSERT( this->nodeStore().checkLock( lock ) );
        return this->doCheckIsNodeInitialized( lock, node_index );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeControllerBase::hasSelectedNode() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->hasSelectedNode( lock );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::selectedNodeIndex() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        this->nodeStore().checkLockAndThrowOnError( lock );
        return this->selectedNodeIndex( lock );
    }


    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::selectedNodeIndex( NodeControllerBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->hasSelectedNode( lock ) )
            ? this->m_selected_node_index
            : NodeControllerBase::UNDEFINED_INDEX;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE std::string
    NodeControllerBase::selectedNodeIdStr() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        this->nodeStore().checkLockAndThrowOnError( lock );
        return this->nodeIdString( lock, this->selectedNodeIndex( lock ) );
    }

    SIXTRL_INLINE std::string
    NodeControllerBase::selectedNodeIdStr(
        NodeControllerBase::lock_t const& SIXTRL_RESTRIC_REF lock ) const
    {
        return this->nodeIdString( lock, this->selectedNodeIndex( lock ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::selectedNodeIdStr(
        NodeControllerBase::size_type const node_id_str_capacity,
        char* SIXTRL_RESTRICT node_id_str_begin ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        this->nodeStore().checkLockAndThrowOnError( lock );
        return this->nodeIdString( lock, this->selectedNodeIndex( lock ),
            node_id_str_capacity, node_id_str_begin );
    }

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::selectedNodeIdStr(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::size_type const node_id_str_capacity,
        char* SIXTRL_RESTRICT node_id_str_begin ) const
    {
        return this->nodeIdString( lock, this->selectedNodeIndex( lock ),
            node_id_str_capacity, node_id_str_begin );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE char const*
    NodeControllerBase::ptrSelectedNodeIdStr() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        this->nodeStore().checkLockAndThrowOnError( lock );

        return ( this->hasSelectedNode( lock ) )
            ? this->ptrNodeIdString( lock, this->selectedNodeIndex( lock ) )
            : nullptr;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::ptrSelectedNodeId() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->ptrSelectedNodeId( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::ptrSelectedNodeId( NodeControllerBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->nodeStore().checkLock( lock ) ) &&
                 ( this->hasSelectedNode( lock ) ) )
            ? this->ptrNodeId( lock, this->selectedNodeIndex( lock ) )
            : nullptr;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeControllerBase::node_info_base_t const*
    NodeControllerBase::ptrSelectedNodeInfoBase() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->ptrNodeInfoBase( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_info_base_t const*
    NodeControllerBase::ptrSelectedNodeInfoBase( NodeControllerBase::lock_t
        const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->nodeStore().checkLock( lock ) ) &&
                 ( this->hasSelectedNode( lock ) ) )
            ? this->ptrNodeInfoBase( lock, this->selectedNodeIndex( lock ) )
            : nullptr;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< typename... Args >
    bool NodeControllerBase::isSelectedNode( Args&&... args ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        this->nodeStore().checkLockAndThrowOnError( lock );
        return this->isSelectedNode( lock, std::forward< Args >( args )... );
    }

    template< typename... Args >
    bool NodeControllerBase::isSelectedNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args ) const SIXTRL_NOEXCEPT
    {
        using _this_t = NodeControllerBase;
        using index_t = _this_t::node_index_t;

        SIXTRL_ASSERT( this->nodeStore().checkLock( lock ) );
        index_t const selected_node_index = this->selectedNodeIndex( lock );

        return ( ( selected_node_index != _this_t::UNDEFINED_INDEX ) &&
                 ( selected_node_index == this->nodeIndex(
                    lock, std::forward< Args >( args )... ) ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    NodeControllerBase::usesAutoSelect() const SIXTRL_NOEXCEPT
    {
        return this->m_use_autoselect;
    }

    template< typename Args... >
    NodeControllerBase::status_t
    NodeControllerBase::selectNode( Args&&... args )
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        this->nodeStore().checkLockAndThrowOnError( lock );
        return this->selectNode( lock, std::forward< Args >( args )... );
    }

    template< typename Args... >
    NodeControllerBase::status_t NodeControllerBase::selectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args )
    {
        using _this_t  = NodeControllerBase;
        using  index_t = _this_t::node_index_t;

        _this_t::status_t status =
            SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        index_t const node_index = this->nodeIndex(
            lock, std::foward< Args >( args )... );

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->isSyncWithNodeStore() ) &&
            ( node_index != NodeControllerBase::UNDEFINED_INDEX ) )
        {
            if( !this->hasSelectedNode( lock ) )
            {
                status = this->nodeStore().markNodeAsSelectedByController(
                    lock, node_index, this );

                if( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
                {
                    status = this->doSelectNode( lock, node_index );
                }

                if( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
                {
                    status = this->nodeStore().unselectNodeForController(
                        lock, currently_selected_node_index, this );
                }

                if( status != SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
                {
                    this->nodeStore().unselectNodeForController(
                        lock, node_index, this );
                }
            }
            else
            {
                status = this->changeSelectedNode( lock, node_index );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    NodeControllerBase::canChangeSelectedNode() const SIXTRL_NOEXCEPT
    {
        return ( ( this->canDirectlyChangeSelectedNode() ) ||
                 ( this->canUnselectNode() ) );
    }

    SIXTRL_INLINE bool
    NodeControllerBase::canDirectlyChangeSelectedNode() const SIXTRL_NOEXCEPT
    {
         return this->m_can_directly_change_selected_node;
    }

    template< typename Args... >
    NodeControllerBase::status_t
    NodeControllerBase::changeSelectedNode( Args&&... args )
    {
        NodeControllerBase::lock_t lk( *this->nodeStore().lockable() );
        return this->changeSelectedNode( lk, std::forward< Args >( args )... );
    }

    template< typename Args... >
    NodeControllerBase::status_t NodeControllerBase::changeSelectedNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args )
    {
        using _this_t  = NodeControllerBase;
        using index_t  = _this_t::node_index_t;
        using status_t = _this_t::status_t;

        status_t status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->noeStore().checkLock( lock ) )
        {
            return status;
        }

        index_t const currently_selected_node_index =
            this->selectedNodeIndex( lock );

        index_t const new_selected_node_index = this->nodeIndex(
            lock, std::forward< Args >( args )... );

        if( ( _this_t::UNDEFINED_INDEX != new_selected_node_index ) &&
            ( _this_t::UNDEFINED_INDEX != currently_selected_node_index ) &&
            ( currently_selected_node_index != new_selected_node_index ) &&
            ( this->isNodeAvailable( lock, new_selected_node_index ) ) )
        {
            if( this->canChangeSelectedNode() )
            {
                status = this->nodeStore().markNodeAsSelectedByController(
                    lock, new_selected_node_index, this );

                if( status != SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
                {
                    return status;
                }
            }

            if( this->canDirectlyChangeSelectedNode() )
            {
                SIXTRL_ASSERT( status ==
                    SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );

                status = this->doChangeSelectedNode(
                    lock, new_selected_node_index );

                if( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
                {
                    status = this->nodeStore().unselectNodeForController(
                        lock, current_selected_node_index, this );
                }

            }
            else if( this->canUnselectNode() )
            {
                SIXTRL_ASSERT( status ==
                    SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );

                status = this->doUnselectNode(
                    lock, currently_selected_node_index );

                if( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
                {
                    status = this->nodeStore().unselectNodeForController(
                        lock, currently_selected_node_index, this );
                }

                if( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
                {
                    status = this->doSelectNode(
                        lock, new_selected_node_index );
                }
            }

            if( status != SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
            {
                this->nodeStore().unselectNodeForController(
                        lock, new_selected_node_index, this );
            }
        }
        else if(
            ( _this_t::UNDEFINED_INDEX != new_selected_node_index ) &&
            ( currently_selected_node_index == new_selected_node_index ) )
        {
            status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    NodeControllerBase::canUnselectNode() const SIXTRL_NOEXCEPT
    {
        return this->m_can_unselect_node;
    }

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::unselectNode()
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->unselectNode( lock, this->selectedNodeIndex( lock ) );
    }

    template< typename Args... >
    NodeControllerBase::status_t NodeControllerBase::unselectNode(
        Args&&... args )
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->unselectNode( lock, this->nodeIndex(
            lock, std::forward< Args >( args )... ) );
    }

    template< typename Args... >
    NodeControllerBase::status_t NodeControllerBase::unselectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args )
    {
        using _this_t  = NodeControllerBase;
        using index_t  = _this_t::node_index_t;
        using status_t = _this_t::status_t;

        status_t status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->nodeStore().checkLock( lock ) )
        {
            return status;
        }

        index_t const selected_node_index = this->selectedNodeIndex( lock );

        if( ( selected_node_index != _this_t::UNDEFINED_INDEX ) &&
            ( this->canUnselectNode() ) )
        {
            status = this->nodeStore().unselectNodeForController(
                lock, selected_node_index, this );

            if( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
            {
                status = this->doUnselectNode(
                    lock, current_selected_node_index );
            }
        }
        else if(
            ( selected_node_index != _this_t::UNDEFINED_INDEX ) &&
            ( this->canDirectlyChangeSelectedNode() ) &&
            ( this->hasDefaultNode( lock ) ) &&
            ( selected_node_index != this->defaultNodeIndex( lock ) ) )
        {
            SIXTRL_ASSERT( this->defaultNodeIndex( lock ) !=
                _this_t::UNDEFINED_INDEX );

            status = this->changeSelectedNode(
                lock, this->defaultNodeIndex( lock ) );
        }
        else if( !this->hasSelectedNode( lock ) )
        {
            SIXTRL_ASSERT( selected_node_index == _this_t::UNDEFINED_INDEX );
            status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    NodeControllerBase::hasDefaultNode() const SIXTRL_NOEXCEPT
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->hasDefaultNode( lock );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::defaultNodeIndex() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->defaultNodeIndex( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::defaultNodeIndex( NodeControllerBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return this->defaultNodeIndex( lock )
            ? this->m_default_node_index
            : NodeControllerBase::UNDEFINED_INDEX;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::ptrDefaultNodeId( ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->ptrDefaultNodeId( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::ptrDefaultNodeId( NodeControllerBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->nodeStore().checkLock( lock ) )
            ? this->ptrNodeId( lock, this->defaultNodeIndex( lock ) )
            : nullptr;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeControllerBase::node_info_base_t const*
    NodeControllerBase::ptrDefaultNodeInfoBase() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->ptrDefaultNodeInfoBase( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_info_base_t const*
    NodeControllerBase::ptrDefaultNodeInfoBase( NodeControllerBase::lock_t
        const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->nodeStore().checkLock( lock ) )
            ? this->ptrNodeInfoBase( lock, this->defaultNodeIndex( lock ) )
            : nullptr;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< typename... Args >
    bool NodeControllerBase::isDefaultNode( Args&&... args ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->isDefaultNode( lock, std::forward< Args >( args )... );
    }

    template< typename... Args >
    bool NodeControllerBase::isDefaultNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args ) const SIXTRL_NOEXCEPT
    {
        NodeControllerBase::node_index_t const try_node_index =
            this->nodeIndex( lock, std::forward< Args >( args )... );

        return ( ( try_node_index != NodeControllerBase::UNDEFINED_INDEX ) &&
            ( this->defaultNodeIndex( lock ) == try_node_index ) );
    }

    /* --------------------------------------------------------------------- */

    template< typename... Args >
    NodeControllerBase::node_index_t NodeControllerBase::nodeIndex(
        Args&&... args ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->nodeIndex( lock, std::forward< Args >( args )... );
    }

    template< typename... Args >
    NodeControllerBase::node_index_t NodeControllerBase::nodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args ) const SIXTRL_NOEXCEPT
    {
        using _this_t = NodeControllerBase;
        using index_t = _this_t::node_index_t;

        index_t index = NodeControllerBase::UNDEFINED_INDEX;

        if( this->nodeStore().checkLock( lock ) )
        {
            index = this->nodeStore().findNodeIndex(
                lock, std::foward< Args >( args )... );

            if( !this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) )
            {
                index = _this_t::UNDEFINED_INDEX;
            }
        }

        return index;
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeControllerBase::arch_id_t const arch_id,
        NodeControllerBase::platform_id_t const platform_id,
        NodeControllerBase::device_id_t const device_id ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->nodeIndex( lock, arch_id, platform_id, device_id );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeControllerBase::platform_id_t const platform_id,
        NodeControllerBase::device_id_t const device_id ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->nodeIndex( lock, this->archId(), platform_id, device_id );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::platform_id_t const platform_id,
        NodeControllerBase::device_id_t const device_id ) const SIXTRL_NOEXCEPT
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->nodeIndex( lock, this->archId(), platform_id, device_id );
    }

    SIXTRL_INLINE node_index_t NodeControllerBase::nodeIndex(
        NodeControllerBase::node_index_t const try_node_index ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        this->nodeStore().checkLockAndThrowOnError( lock );

        bool const index_is_available =
            this->doCheckIfNodeIndexIsAvailableLocally( lock, try_node_index );

        return (  index_is_available )
            ? try_node_index : NodeControllerBase::UNDEFINED_INDEX;
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex( NodeControllerBase::lock_t const&
        SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const
            try_node_index ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? this->doCheckIfNodeIndexIsAvailableLocally( lock, try_node_index )
            : NodeControllerBase::UNDEFINED_INDEX;
    }

    /* --------------------------------------------------------------------- */

    template< typename... Args >
    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::ptrNodeId( Args&&... args ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->ptrNodeId( lock,
            this->nodeIndex( lock, std::forward< Args >( args )... ) );
    }

    template< typename... Args >
    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::ptrNodeId(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args ) const SIXTRL_NOEXCEPT
    {
        return this->ptrNodeId( lock,
            this->nodeIndex( lock, std::foward< Args >( args )... ) );
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::ptrNodeId(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        NodeControllerBase::node_id_t const* ptr_node_id = nullptr;

        if( this->doCheckIfNodeIndexIsAvailableLocally( lock, node_index ) )
        {
            ptr_node_id = this->nodeStore().ptrNodeId( lock, node_index );
        }

        return ptr_node_id;
    }

    /* --------------------------------------------------------------------- */

    template< typename... Args >
    NodeControllerBase::node_info_base_t const*
    NodeControllerBase::ptrNodeInfoBase( Args&&... args ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->ptrNodeBaseInfo( lock,
            this->nodeIndex( lock, std::forward< Args >( args )... ) );
    }

    template< typename... Args >
    NodeControllerBase::node_info_base_t const*
    NodeControllerBase::ptrNodeInfoBase(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args ) const SIXTRL_NOEXCEPT
    {
       return this->ptrNodeInfoBase( lock,
            this->nodeIndex( lock, std::forward< Args >( args )... ) );
    }

    NodeControllerBase::node_info_base_t const*
    NodeControllerBase::ptrNodeInfoBase(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        NodeControllerBase::node_info_base_t const* ptr_node_info = nullptr;

        if( this->doCheckIfNodeIndexIsAvailableLocally( lock, node_index ) )
        {
            ptr_node_info = this->nodeStore().ptrNodeInfoBase(
                lock, node_index );
        }

        return ptr_node_info;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeControllerBase::node_index_t const*
    NodeControllerBase::nodeIndicesBegin() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->nodeIndicesBegin( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t const*
    NodeControllerBase::nodeIndicesEnd() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->nodeIndicesEnd( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::nodeIdsBegin() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->nodeIdsBegin( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::nodeIdsEnd() const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->nodeIdsEnd( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t const&
    NodeControllerBase::nodeId(
        NodeControllerBase::node_index_t const node_index ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->nodeId( lock, node_index );
    }

    SIXTRL_INLINE std::string NodeControllerBase::nodeIdString(
        NodeControllerBase::node_index_t const node_index ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->nodeIdString( lock, node_index );
    }

    SIXTRL_INLINE char const* NodeControllerBase::ptrNodeIdString(
        NodeControllerBase::node_index_t const node_index ) const
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->ptrNodeIdString( lock, node_index );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeControllerBase::node_index_t const*
    NodeControllerBase::nodeIndicesBegin( NodeControllerBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->nodeStore().check( lock ) )
            ? this->m_available_node_indices.data()
            : nullptr;
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t const*
    NodeControllerBase::nodeIndicesEnd( NodeControllerBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        NodeControllerBase::node_index_t const*
            end_ptr = this->nodeIndicesBegin( lock );

        if( end_ptr != nullptr )
        {
            std::advance( end_ptr, this->numAvailableNodes( lock ) );
        }

        return end_ptr;
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::nodeIdsBegin( NodeControllerBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->nodeStore().check( lock ) )
            ? this->m_available_node_ids.data() : nullptr;
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::nodeIdsEnd( NodeControllerBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        NodeControllerBase::node_id_t const*
            end_ptr = this->nodeIdsBegin( lock );

        if( end_ptr != nullptr )
        {
            std::advance( end_ptr, this->numAvailableNodes( lock ) );
        }

        return end_ptr;
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t const&
    NodeControllerBase::nodeId(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const index ) const
    {
        NodeControllerBase::node_id_t const*
            ptr_node_id = this->nodeIdsBegin( lock );

        if( ( ptr_node_id == nullptr ) ||
            ( index >= this->numAvailableNodes( lock ) ) )
        {
            throw std::runtime_error( "NodeId not available" );
        }

        return *ptr_node_id;
    }

    SIXTRL_INLINE std::string NodeControllerBase::nodeIdString(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const index ) const
    {
        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) ) &&
            ( this->m_available_node_id_strings.size() > index ) &&
            ( this->m_available_node_id_strings[ index ].data() != nullptr ) )
        {
            return std::string{
                this->m_available_node_id_strings[ index ].data() };
        }

        return std::string{};
    }

    SIXTRL_INLINE char const* NodeControllerBase::ptrNodeIdString(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        char const* ptr_node_id_str = nullptr;

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) ) &&
            ( this->m_available_node_id_strings.size() > index ) )
        {
            ptr_node_id_str =
                this->m_available_node_id_strings[ index ].data();
        }

        return ptr_node_id_str;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeControllerBase::size_type
    NodeControllerBase::requiredAvailableNodeInfosStrCapacity() const
    {
        return this->availableNodeInfosToString().size();
    }



    SIXTRL_INLINE void NodeControllerBase::printOutAvailableNodeInfos() const
    {
        this->printAvailableNodeInfos( std::cout );

    }

    SIXTRL_INLINE std::string
    NodeControllerBase::availableNodeInfosToString() const
    {
        std::ostringstream a2str;

        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        NodeControllerBase::status_t status =
            this->doPrintAvailableNodesToOutputStream( lock, a2str );

        SIXTRL_ASSERT( SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS == status );
        ( void )status;

        return a2str.str();
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeControllerBase::node_store_t& nodeStore() SIXTRL_NOEXCEPT
    {
        return this->m_node_store;
    }

    SIXTRL_INLINE NodeControllerBase::node_store_t*
    ptrNodeStore() SIXTRL_NOEXCEPT
    {
        return &this->m_node_store;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE void NodeControllerBase::doSetCanDirectlyChangeSelectedNodeFlag(
        bool const can_directly_change_selected_node ) SIXTRL_NOEXCEPT
    {
        this->m_can_directly_change_selected_node =
            can_directly_change_selected_node;
    }

    SIXTRL_INLINE void NodeControllerBase::doSetCanUnselectNodeFlag(
        bool const can_unselect_node ) SIXTRL_NOEXCEPT
    {
        this->m_can_unselect_node = can_unselect_node;
    }

    SIXTRL_INLINE void NodeControllerBase::doSetUseAutoSelectFlag(
        bool const use_autoselect ) SIXTRL_NOEXCEPT
    {
        this->m_use_autoselect = use_autoselect;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeControllerBase const* asNodeController(
        ControllerBase const* SIXTRL_RESTRICT base_controller )
    {
        return ( ( base_controller != nullptr ) &&
                 ( base_controller->usesNodes() ) )
            ? static_cast< NodeControllerBase const* >( base_controller )
            : nullptr;
    }

    SIXTRL_INLINE NodeControllerBase* asNodeController(
        ControllerBase* SIXTRL_RESTRICT base_controller )
    {
        ControllerBase const* cptr_base_ctrl = base_controller;

        return const_cast< NodeControllerBase* >(
            asNodeController( cptr_base_ctrl ) );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_CONTROLLER_BASE_HPP__ */

/* end: sixtracklib/common/control/node_controller_base.hpp */
