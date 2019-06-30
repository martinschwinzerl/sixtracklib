#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_CONTROLLER_BASE_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_CONTROLLER_BASE_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
        #include <cstddef>
        #include <cstdlib>
        #include <string>
        #include <iostream>
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

        static SIXTRL_CONSTEXPR_OR_CONST platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PATFORM_ID;

        static SIXTRL_CONSTEXPR_OR_CONST device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PATFORM_ID;

        static SIXTRL_CONSTEXPR_OR_CONST node_index_t UNDEFINED_INDEX =
            SIXTRL_CXX_NAMESPACE::NODE_UNDEFINED_INDEX;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_store_t const& nodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_store_t const* ptrNodeStore() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t numAvailableNodes() const;
        SIXTRL_HOST_FN bool isSyncWithNodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_t registerNodeStoreChange() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t syncWithNodeStore();
        SIXTRL_HOST_FN status_t syncWithNodeStore(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        template< typename... Args >
        SIXTRL_HOST_FN bool isNodeAvailable( Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN bool isNodeAvailable(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_NOEXCEPT;

        /* ---------------------------------------------------------------- */

        SIXTRL_HOST_FN bool isNodeInitialized(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN status_t initializeNode(
            node_index_t const node_index );

        /* ---------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasSelectedNode() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_index_t selectedNodeIndex() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const&
            selectedNodeIdStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t selectedNodeIdStr(
            size_type const node_id_str_capacity,
            char* SIXTRL_RESTRICT node_id_str_begin ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN char const*
            ptrSelectedNodeIdStr() const SIXTRL_NOEXCEPT;

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

        SIXTRL_HOST_FN status_t changeSelectedNode(
            node_index_t const new_selected_node_index );

        SIXTRL_HOST_FN status_t changeSelectedNode(
            node_index_t const current_selected_node_index,
            node_index_t const new_selected_node_index );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canUnselectNode() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_t unselectNode();

        template< typename Args... >
        SIXTRL_HOST_FN status_t unselectNode( Args&&... args );

        template< typename Args... >
        SIXTRL_HOST_FN status_t unselectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock, Args&&... args );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasDefaultNode() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_index_t defaultNodeIndex() const SIXTRL_NOEXCEPT;

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

        SIXTRL_HOST_FN node_id_t const* nodeIndex(
            arch_id_t const arch_id,
            platform_id_t const platform_id,
            device_id_t const device_id ) const;

        SIXTRL_HOST_FN node_id_t const* nodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            platform_id_t const platform_id,
            device_id_t const device_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* nodeIndex(
            platform_id_t const platform_id,
            device_id_t const device_id ) const;

        SIXTRL_HOST_FN node_id_t const* nodeIndex(
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

        /* ----------------------------------------------------------------- */

        template< typename... Args >
        SIXTRL_HOST_FN node_id_t const* ptrNodeInfoBase(
            Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN node_id_t const* ptrNodeInfoBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t const*
            nodeIndicesBegin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const*
            nodeIndicesEnd() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const*
            nodeIdsBegin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* nodeIdsEnd() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void printAvailableNodeInfos(
            std::ostream& SIXTRL_RESTRICT_REF output ) const;

        SIXTRL_HOST_FN void printNodeInfos() const;


        SIXTRL_HOST_FN size_type requiredNodeInfosStrCapacity() const;

        SIXTRL_HOST_FN std::string nodeInfosToString() const;

        SIXTRL_HOST_FN status_t nodeInfosToString(
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

        SIXTRL_HOST_FN virtual void doClear() override;

        SIXTRL_HOST_FN virtual bool doCheckIsNodeInitialized(
            node_index_t const node_index );

        SIXTRL_HOST_FN virtual status_t doSyncWithNodeStore(
            node_store_t* SIXTRL_RESTRICT ptr_node_store );

        SIXTRL_HOST_FN virtual status_t doInitializeNode(
            node_index_t const node_index );

        SIXTRL_HOST_FN virtual status_t doSelectNode(
            node_index_t const node_index );

        SIXTRL_HOST_FN virtual status_t doChangeSelectedNode(
            node_index_t const current_selected_node_index,
            node_index_t const new_selected_node_index );

        SIXTRL_HOST_FN virtual status_t doUnselectNode(
            node_index_t const selected_node_index );

        /* ----------------------------------------------------------------- */



        SIXTRL_HOST_FN node_index_t doFindAvailableNodesIndex(
            platform_id_t const platform_idx,
            device_id_t const device_idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t doFindAvailableNodesIndex(
            char const* SIXTRL_RESTRICT node_id_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doClearAvailableNodes() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doRemoveNodeFromSelection(
            node_index_t const selected_node_index ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t doAppendAvailableNodeInfoBase(
            ptr_node_info_base_t&& SIXTRL_RESTRICT_REF ptr_node_info_base );

        SIXTRL_HOST_FN node_info_base_t* doGetPtrNodeInfoBase(
            node_index_t const node_index ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetDefaultNodeIndex(
            node_index_t const node_index ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN platform_id_t doGetNextPlatformId(
            ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN device_id_t doGetNextDeviceIdForPlatform(
            platform_id_t const platform_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN platform_id_t doGetPlatformIdByPlatformName(
            char const* SIXTRL_RESTRICT platform_name ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void doSetCanDirectlyChangeSelectedNodeFlag(
            bool const can_directly_change_selected_node ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetCanUnselectNodeFlag(
            bool const can_unselect_node ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetUseAutoSelectFlag(
            bool const use_autoselect ) SIXTRL_NOEXCEPT;

        private:

        SIXTRL_HOST_FN void doClearNodeControllerBaseImpl() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doSelectNodeNodeControllerBaseImpl(
            node_index_t const node_index ) SIXTRL_NOEXCEPT;

        node_store_t&        m_node_store;
        node_index_buffer_t  m_available_node_indices;
        node_id_str_buffer_t m_selected_node_id_str;

        node_index_t         m_selected_node_index;
        node_index_t         m_default_node_index;

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
