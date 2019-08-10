#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_CONTROLLER_BASE_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_CONTROLLER_BASE_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
        #include <atomic>
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
    #include "sixtracklib/common/architecture/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/controller_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class NodeStore;
    class NodeInfoBase;

    class NodeControllerBase : public SIXTRL_CXX_NAMESPACE::ControllerBase
    {
        private:

        using _controller_base_t = ControllerBase;

        public:

        using node_id_t         = SIXTRL_CXX_NAMESPACE::NodeId;
        using node_info_base_t  = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        using node_store_t      = SIXTRL_CXX_NAMESPACE::NodeStore;
        using node_str_role_t   = SIXTRL_CXX_NAMESPACE::node_str_role_t;
        using platform_id_t     = SIXTRL_CXX_NAMESPACE::node_platform_id_t;
        using device_id_t       = SIXTRL_CXX_NAMESPACE::node_device_id_t;
        using node_index_t      = SIXTRL_CXX_NAMESPACE::node_index_t;
        using node_lockable_t   = std::mutex;
        using node_lock_t       = std::unique_lock< lockable_t >;
        using kernel_purpose_t  = kernel_config_store_base_t::purpose_t;
        using sync_id_value_t   = uint64_t;
        using sync_id_t         = std::atomic< sync_id_value_t >;

        static SIXTRL_CONSTEXPR_OR_CONST arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static SIXTRL_CONSTEXPR_OR_CONST platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static SIXTRL_CONSTEXPR_OR_CONST device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static SIXTRL_CONSTEXPR_OR_CONST node_index_t UNDEFINED_INDEX =
            SIXTRL_CXX_NAMESPACE::NODE_UNDEFINED_INDEX;

        static SIXTRL_CONSTEXPR_OR_CONST node_str_role_t NODE_ID_STR =
            SIXTRL_CXX_NAMESPACE::NODE_STR_ROLE_ID;

        static SIXTRL_CONSTEXPR_OR_CONST node_str_role_t NODE_UNIQUE_ID_STR =
            SIXTRL_CXX_NAMESPACE::NODE_STR_ROLE_UNIQUE_ID;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN NodeStore const& nodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN NodeStore const* ptrNodeStore() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSyncWithNodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_t registerNodeStoreChange() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t syncWithNodeStore();
        SIXTRL_HOST_FN status_t syncWithNodeStore(
            node_lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t numAvailableNodes() const;

        SIXTRL_HOST_FN node_index_t numAvailableNodes(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< typename... Args >
        SIXTRL_HOST_FN bool isNodeAvailable( Args&&... args ) const;

        /* ---------------------------------------------------------------- */

        template< typename... Args >
        SIXTRL_HOST_FN status_t resetKeyForNodeIndex(
            kernel_config_key_t& SIXTRL_RESTRICT_REF key,
            node_index_t const node_idx, Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN status_t resetKeyForNodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t& SIXTRL_RESTRICT_REF key,
            node_index_t const node_idx, Args&&... args ) const;

        /* ---------------------------------------------------------------- */

        template< typename... Args >
        SIXTRL_HOST_FN bool isNodeInitialized(
            node_index_t const node_index, Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN bool isNodeInitialized(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index, Args&&... args ) const;

        /* ---------------------------------------------------------------- */

        template< typename... Args >
        SIXTRL_HOST_FN status_t initializeNode(
            node_index_t const node_index, Args&&... args );

        template< typename... Args >
        SIXTRL_HOST_FN status_t initializeNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index, Args&&... args );

        /* ---------------------------------------------------------------- */

        using _controller_base_t::addKernelConfig;

        SIXTRL_HOST_FN status_t addKernelConfig(
            node_index_t const node_index, kernel_id_t const kernel_id );

        SIXTRL_HOST_FN status_t addKernelConfig(
            node_index_t const node_index,
            ptr_kernel_conf_base_t&& ptr_kernel_config );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t addKernelConfig(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index, kernel_id_t const kernel_id );

        SIXTRL_HOST_FN status_t addKernelConfig(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            ptr_kernel_conf_base_t&& ptr_kernel_config );

        /* ---------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasSelectedNode() const;
        SIXTRL_HOST_FN bool hasSelectedNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t selectedNodeIndex() const;
        SIXTRL_HOST_FN node_index_t selectedNodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string selectedNodeIdStr() const;
        SIXTRL_HOST_FN std::string selectedNodeIdStr(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t selectedNodeIdStr(
            size_type const node_id_str_capacity,
            char* SIXTRL_RESTRICT node_id_str_begin ) const;

        SIXTRL_HOST_FN status_t selectedNodeIdStr(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const node_id_str_capacity,
            char* SIXTRL_RESTRICT node_id_str_begin ) const;

        SIXTRL_HOST_FN char const* ptrSelectedNodeIdStr() const;
        SIXTRL_HOST_FN char const* ptrSelectedNodeIdStr(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* ptrSelectedNodeId() const;
        SIXTRL_HOST_FN node_id_t const* ptrSelectedNodeId(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN NodeInfoBase const* ptrSelectedNodeInfoBase() const;
        SIXTRL_HOST_FN NodeInfoBase const* ptrSelectedNodeInfoBase(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        template< typename... Args >
        SIXTRL_HOST_FN bool isSelectedNode( Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN bool isSelectedNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool usesAutoSelect() const SIXTRL_NOEXCEPT;

        template< typename... Args >
        SIXTRL_HOST_FN status_t selectNode( Args&&... args );

        template< typename... Args >
        SIXTRL_HOST_FN status_t selectNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock, Args&&... args );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canChangeSelectedNode() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool canDirectlyChangeSelectedNode() const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t changeSelectedNode(
            node_index_t const change_to_this_node_index );

        template< typename... Args >
        SIXTRL_HOST_FN status_t changeSelectedNode( Args&&... args );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t changeSelectedNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const change_to_this_node_index );

        template< typename... Args >
        SIXTRL_HOST_FN status_t changeSelectedNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock, Args&&... args );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canUnselectNode() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t unselectNode();
        SIXTRL_HOST_FN status_t unselectNode( node_index_t const node_index );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t unselectNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN status_t unselectNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        template< typename... Args >
        SIXTRL_HOST_FN status_t unselectNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock, Args&&... args );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasDefaultNode() const;
        SIXTRL_HOST_FN bool hasDefaultNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t defaultNodeIndex() const;
        SIXTRL_HOST_FN node_index_t defaultNodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* ptrDefaultNodeId() const;
        SIXTRL_HOST_FN node_id_t const* ptrDefaultNodeId(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN NodeInfoBase const* ptrDefaultNodeInfoBase() const;
        SIXTRL_HOST_FN NodeInfoBase const* ptrDefaultNodeInfoBase(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        template< typename... Args >
        SIXTRL_HOST_FN bool isDefaultNode( Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN bool isDefaultNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t nodeIndex(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            platform_id_t const platform_id,
            device_id_t const device_id ) const;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            arch_id_t const arch_id,
            platform_id_t const platform_id,
            device_id_t const device_id ) const;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            NodeId const& SIXTRL_RESTRICT_REF node_id ) const;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            NodeInfoBase const& SIXTRL_RESTRICT_REF node_info_base ) const;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            const NodeInfoBase *const SIXTRL_RESTRICT ptr_node_info ) const;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            std::string const& SIXTRL_RESTRICT node_id_str,
            node_str_role_t const role = NODE_ID_STR ) const;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            char const* SIXTRL_RESTRICT node_id_str,
            node_str_role_t const role = NODE_ID_STR ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN node_index_t nodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            platform_id_t const platform_id,
            device_id_t const device_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            platform_id_t const platform_id,
            device_id_t const device_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            NodeId const& SIXTRL_RESTRICT_REF node_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            NodeInfoBase const& SIXTRL_RESTRICT_REF node_info_base
            ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            const NodeInfoBase *const SIXTRL_RESTRICT ptr_node_info
            ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            std::string const& SIXTRL_RESTRICT node_id_str,
            node_str_role_t const role = NODE_ID_STR ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            char const* SIXTRL_RESTRICT node_id_str,
            node_str_role_t const role = NODE_ID_STR ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t nodeIndexByUniqueIdStr(
            std::string const& SIXTRL_RESTRICT_REF unique_id_str ) const;

        SIXTRL_HOST_FN node_index_t nodeIndexByUniqueIdStr(
            char const* SIXTRL_RESTRICT unique_id_str ) const;

        SIXTRL_HOST_FN node_index_t nodeIndexByUniqueIdStr(
                node_lock_t const& SIXTRL_RESTRICT_REF lock,
                std::string const& SIXTRL_RESTRICT_REF unique_id_str
            ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndexByUniqueIdStr(
                node_lock_t const& SIXTRL_RESTRICT_REF lock,
                char const* SIXTRL_RESTRICT unique_id_str
            ) const;

        /* ----------------------------------------------------------------- */

        template< typename... Args >
        SIXTRL_HOST_FN node_id_t const* ptrNodeId( Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN node_id_t const* ptrNodeId(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* ptrNodeId(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        template< typename... Args >
        SIXTRL_HOST_FN NodeInfoBase const* ptrNodeInfoBase(
            Args&&... args ) const;

        template< typename... Args >
        SIXTRL_HOST_FN NodeInfoBase const* ptrNodeInfoBase(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            Args&&... args ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN NodeInfoBase const* ptrNodeInfoBase(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t const*
        nodeIndicesBegin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const*
        nodeIndicesEnd() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* nodeIdsBegin() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_id_t const* nodeIdsEnd() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string nodeIdString(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN status_t nodeIdString(
            node_index_t const node_index,
            size_type const node_id_str_capacity,
            char* SIXTRL_RESTRICT node_id_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN char const* ptrNodeIdString(
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

        typedef status_t (NodeControllerBase::*selectNodeFn)(
            node_lock_t const& SIXTRL_RESTRICT_REF, node_index_t const );

        static SIXTRL_CONSTEXPR_OR_CONST size_type
            NODE_ID_STR_CAPACITY = size_type{ 64 };

        SIXTRL_HOST_FN NodeControllerBase(
            arch_id_t const arch_id,
            kernel_config_store_base_t& SIXTRL_RESTRICT_REF kernel_config_store,
            NodeStore& SIXTRL_RESTRICT_REF node_store,
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

        SIXTRL_HOST_FN NodeStore& nodeStore() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN NodeStore* ptrNodeStore() SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN virtual void doClear() override;

        SIXTRL_HOST_FN virtual status_t doSyncWithNodeStore(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            NodeStore* SIXTRL_RESTRICT ptr_node_store );

        SIXTRL_HOST_FN virtual status_t doSelectNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        SIXTRL_HOST_FN virtual status_t doChangeSelectedNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const new_selected_node_index );

        SIXTRL_HOST_FN virtual status_t doUnselectNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const selected_node_index );

        SIXTRL_HOST_FN virtual node_index_t doFindDefaultNodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN virtual status_t doPrintToOutputStream(
            std::ostream& SIXTRL_RESTRICT_REF output ) const override;

        SIXTRL_HOST_FN virtual status_t doPrintAvailableNodesToOutputStream(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            std::ostream& SIXTRL_RESTRICT_REF output ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* TODO: Convert these to rvalue returning members */

        SIXTRL_HOST_FN status_t doResetKeyFromNodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t& SIXTRL_RESTRICT_REF key,
            node_index_t const node_index,
            kernel_purpose_t const purpose ) const;

        SIXTRL_HOST_FN status_t doResetKeyFromNodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t& SIXTRL_RESTRICT_REF key,
            node_index_t const node_index,
            kernel_purpose_t const purpose,
            variant_t const variant_flags ) const;

        SIXTRL_HOST_FN status_t doResetKeyFromNodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t& SIXTRL_RESTRICT_REF key,
            node_index_t const node_index,
            kernel_purpose_t const purpose,
            variant_t const variant_flags,
            std::string const& SIXTRL_RESTRICT_REF kernel_config_str ) const;

        SIXTRL_HOST_FN status_t doResetKeyFromNodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t& SIXTRL_RESTRICT_REF key,
            node_index_t const node_index,
            kernel_purpose_t const purpose,
            variant_t const variant_flags,
            char const* SIXTRL_RESTRICT kernel_config_str ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< typename... Args >
        SIXTRL_HOST_FN std::pair< status_t, bool > doChangeNodeBeforeOp(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t* SIXTRL_RESTRICT ptr_prev_node_index,
            Args&&... new_node_args );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t doAttachAllArchNodes(
            node_lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN status_t doDetachAllNodes(
            node_lock_t const& SIXTRL_RESTRICT_REF lock );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t doInitiallySelectNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            selectNodeFn select_fn,
            char const* SIXTRL_RESTRICT config_str );

        SIXTRL_HOST_FN status_t doInitiallySelectNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            selectNodeFn select_fn,
            char const* SIXTRL_RESTRICT config_str,
            node_id_t const& SIXTRL_RESTRICT_REF node_id );

        SIXTRL_HOST_FN status_t doInitiallySelectNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            selectNodeFn select_fn,
            char const* SIXTRL_RESTRICT config_str,
            platform_id_t const platform_id, device_id_t const device_id );

        SIXTRL_HOST_FN status_t doInitiallySelectNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            selectNodeFn select_fn,
            char const* SIXTRL_RESTRICT config_str,
            char const* SIXTRL_RESTRICT str,
            node_str_role_t const str_role );

        SIXTRL_HOST_FN status_t doInitiallySelectNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            selectNodeFn select_fn,
            char const* SIXTRL_RESTRICT config_str,
            std::string const& SIXTRL_RESTRICT_REF str,
            node_str_role_t const str_role );

        SIXTRL_HOST_FN status_t doInitiallySelectNodeByConfigStr(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            selectNodeFn select_fn,
            char const* SIXTRL_RESTRICT config_str );

        SIXTRL_HOST_FN status_t doInitiallySelectDefaultNode(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            selectNodeFn select_fn );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t doUpdateNodeStore(
            NodeStore& SIXTRL_RESTRICT_REF node_store );

        SIXTRL_HOST_FN void doSetIsSyncWithNodeStoreFlag(
            bool const is_sync_with_node_store ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetCanDirectlyChangeSelectedNodeFlag(
            bool const can_directly_change_selected_node ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetCanUnselectNodeFlag(
            bool const can_unselect_node ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetUseAutoSelectFlag(
            bool const use_autoselect ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool doCheckIfNodeIndexIsAvailableLocallyWithoutLock(
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool doCheckIfNodeIndexIsAvailableLocally(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        private:

        SIXTRL_HOST_FN void doClearNodeControllerBaseImpl(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doSyncWithNodeStoreBaseImpl(
            node_lock_t const& SIXTRL_RESTRICT_REF lock,
            NodeStore* SIXTRL_RESTRICT ptr_node_store );

        node_index_buffer_t                     m_available_node_indices;
        node_id_buffer_t                        m_available_node_ids;
        std::vector< node_id_str_buffer_t >     m_available_node_id_strings;
        NodeStore&                              m_node_store;


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

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_info.hpp"
    #include "sixtracklib/common/control/node_store.hpp"
    #include "sixtracklib/common/control/kernel_config_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

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
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->doSyncWithNodeStore( lock, &this->m_node_store );
    }

    /* --------------------------------------------------------------------- */

    template< typename... Args >
    bool NodeControllerBase::isNodeAvailable( Args&&... args ) const
    {
        return ( this->nodeIndex( std::forward< Args >( args )... ) !=
            SIXTRL_CXX_NAMESPACE::NodeControllerBase::UNDEFINED_INDEX );
    }

    /* --------------------------------------------------------------------- */

    template< typename... Args >
    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::resetKeyForNodeIndex(
        NodeControllerBase::kernel_config_key_t& SIXTRL_RESTRICT_REF key,
        NodeControllerBase::node_index_t const node_idx,
        Args&&... args ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t lock( *this->nodeStore().lockable() );

        return this->resetKeyForNodeIndex(
            lock, key, node_idx, std::forward< Args >( args )... );
    }

    template< typename... Args >
    NodeControllerBase::status_t NodeControllerBase::resetKeyForNodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::kernel_config_key_t& SIXTRL_RESTRICT_REF key,
        NodeControllerBase::node_index_t const node_index,
        Args&&... args ) const
    {
        return ( this->nodeStore().checkLock( lock ) )
            ? this->doResetKeyFromNodeIndex( lock, key, node_index,
                std::forward< Args >( args )... )
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

     /* -------------------------------------------------------------------- */

    template< typename... Args >
    bool NodeControllerBase::isNodeInitialized(
        NodeControllerBase::node_index_t const node_index,
        Args&&... args ) const
    {
        namespace st  = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeControllerBase;

        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        _this_t::kernel_config_key_t key;
        _this_t::status_t const status = this->doResetKeyFromNodeIndex(
            lock, key, node_index, st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER,
                std::forward< Args >( args )... );

        return ( ( status == st::ARCH_STATUS_SUCCESS ) &&
                 ( this->doCheckAreKernelConfigsInitialized( key ) ) );
    }

    template< typename... Args >
    bool NodeControllerBase::isNodeInitialized(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const node_index,
        Args&&... args ) const
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeControllerBase;

        bool initialized = false;

        if( this->nodeStore().checkLock( lock ) )
        {
            _this_t::kernel_config_key_t key;

            _this_t::status_t const status = this->doResetKeyFromNodeIndex(
                lock, key, node_index, st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER,
                    std::forward< Args >( args )... );

            initialized = ( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( this->doCheckAreKernelConfigsInitialized( key ) ) );
        }

        return initialized;
    }

    /* ---------------------------------------------------------------- */

    template< typename... Args >
    NodeControllerBase::status_t NodeControllerBase::initializeNode(
        NodeControllerBase::node_index_t const node_index,
        Args&&... args )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );

        return this->initializeNode(
            lock, node_index, std::forward< Args >( args )... );
    }

    template< typename... Args >
    NodeControllerBase::status_t NodeControllerBase::initializeNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const node_index, Args&&... args )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->nodeStore().checkLock( lock ) )
        {
            _this_t::kernel_config_key_t key;

            status = this->doResetKeyFromNodeIndex( lock, key, node_index,
                st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER,
                    std::forward< Args >( args )... );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->doInitializeKernelConfigs( key );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::addKernelConfig(
        NodeControllerBase::node_index_t const node_index,
        NodeControllerBase::kernel_id_t const kernel_id )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t lock( *this->nodeStore().lockable() );
        return this->addKernelConfig( lock, node_index, kernel_id );
    }

    NodeControllerBase::status_t NodeControllerBase::addKernelConfig(
        NodeControllerBase::node_index_t const node_index,
        NodeControllerBase::ptr_kernel_conf_base_t&& ptr_kernel_config )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t lock( *this->nodeStore().lockable() );

        return this->addKernelConfig( lock, node_index,
            std::move( ptr_kernel_config ) );
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
        return this->nodeIdString( this->selectedNodeIndex() );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::selectedNodeIdStr(
        NodeControllerBase::size_type const node_id_str_capacity,
        char* SIXTRL_RESTRICT node_id_str_begin ) const
    {
        return this->nodeIdString( this->selectedNodeIndex(),
            node_id_str_capacity, node_id_str_begin );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE char const*
    NodeControllerBase::ptrSelectedNodeIdStr() const
    {
        return ( this->hasSelectedNode() )
            ? this->ptrNodeIdString( this->selectedNodeIndex() ) : nullptr;
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
        return this->ptrSelectedNodeInfoBase( lock );
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

    template< typename... Args >
    NodeControllerBase::status_t
    NodeControllerBase::selectNode( Args&&... args )
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->selectNode( lock, std::forward< Args >( args )... );
    }

    template< typename... Args >
    NodeControllerBase::status_t NodeControllerBase::selectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args )
    {
        namespace   st = SIXTRL_CXX_NAMESPACE;
        using _this_t  = NodeControllerBase;
        using  index_t = _this_t::node_index_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->nodeStore().checkLock( lock ) )
        {
            return status;
        }

        index_t const node_index =
            this->nodeIndex( lock, std::forward< Args >( args )... );

        bool const node_index_is_available =
            this->isNodeAvailable( lock, node_index );

        if( ( this->isSyncWithNodeStore() ) &&
            ( node_index != NodeControllerBase::UNDEFINED_INDEX ) &&
            ( node_index_is_available ) )
        {
            if( !this->hasSelectedNode( lock ) )
            {
                status = st::ARCH_STATUS_SUCCESS;

                if( !this->isNodeInitialized( lock, node_index ) )
                {
                    status = this->initializeNode( lock, node_index );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = this->nodeStore().markNodeAsSelectedByController(
                        lock, node_index, *this );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = this->doSelectNode( lock, node_index );
                }

                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( ( this->isNodeInitialized( lock, node_index ) ) &&
                      ( this->hasSelectedNode( lock ) ) &&
                      ( this->selectedNodeIndex( lock ) == node_index ) ) );
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

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::changeSelectedNode(
        NodeControllerBase::node_index_t const change_to_this_node_index )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->changeSelectedNode( lock, change_to_this_node_index );
    }

    template< typename... Args >
    NodeControllerBase::status_t
    NodeControllerBase::changeSelectedNode( Args&&... args )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        _this_t::node_index_t const node_index =
            this->nodeIndex( lock, std::forward< Args >( args )... );

        return this->changeSelectedNode( lock, node_index );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< typename... Args >
    NodeControllerBase::status_t NodeControllerBase::changeSelectedNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::node_index_t const node_index =
            this->nodeIndex( lock, std::forward< Args >( args )... );

        return this->changeSelectedNode( lock, node_index );
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

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::unselectNode(
        NodeControllerBase::node_index_t const node_index )
    {
        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );
        return this->unselectNode( lock, node_index );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    NodeControllerBase::status_t NodeControllerBase::unselectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        return this->unselectNode( lock, this->selectedNodeIndex() );
    }

    template< typename... Args >
    NodeControllerBase::status_t NodeControllerBase::unselectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        Args&&... args )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;

        _this_t::node_index_t const node_index = this->nodeIndex(
            lock, std::forward< Args >( args )... );

        return this->unselectNode( lock, node_index );
    }

    NodeControllerBase::status_t NodeControllerBase::unselectNode(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const node_index )
    {
        namespace   st = SIXTRL_CXX_NAMESPACE;
        using _this_t  = NodeControllerBase;
        using  index_t = _this_t::node_index_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->nodeStore().checkLock( lock ) )
        {
            return status;
        }

        if( ( this->isSyncWithNodeStore() ) &&
            ( node_index != _this_t::UNDEFINED_INDEX ) &&
            ( this->isNodeAvailable( lock, node_index ) ) &&
            ( this->nodeStore().isNodeSelectedByController(
                lock, node_index, *this ) ) )
        {
            if( this->canUnselectNode() )
            {
                status = this->nodeStore().unselectNodeForController(
                    lock, node_index, *this );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = this->doUnselectNode( lock, node_index );
                }
            }
            else if( ( this->canDirectlyChangeSelectedNode() ) &&
                     ( this->hasDefaultNode( lock ) ) &&
                     ( this->defaultNodeIndex( lock ) != node_index ) )
            {
                index_t const default_node_index =
                    this->defaultNodeIndex( lock );

                SIXTRL_ASSERT( default_node_index != _this_t::UNDEFINED_INDEX );
                status = this->changeSelectedNode( lock, default_node_index );
            }
        }
        else if( ( this->isSyncWithNodeStore() ) &&
                 ( !this->hasSelectedNode( lock ) ) &&
                 ( node_index == _this_t::UNDEFINED_INDEX ) )
        {
            SIXTRL_ASSERT( this->selectedNodeIndex( lock ) ==
                           _this_t::UNDEFINED_INDEX );

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    NodeControllerBase::hasDefaultNode() const
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
        return ( this->nodeStore().checkLock( lock ) )
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

        NodeControllerBase::node_index_t const try_node_index =
            this->nodeIndex( lock, std::forward< Args >( args )... );

        return ( ( try_node_index != NodeControllerBase::UNDEFINED_INDEX ) &&
            ( this->defaultNodeIndex( lock ) == try_node_index ) );
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

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeControllerBase::node_index_t const index ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );

        return ( ( this->nodeStore().isNodeAvailable( lock, index ) ) &&
                 ( this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) ) )
            ? index : _this_t::UNDEFINED_INDEX;
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeControllerBase::platform_id_t const platform_id,
        NodeControllerBase::device_id_t const device_id ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->nodeIndex( lock, this->archId(), platform_id, device_id );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeId const& SIXTRL_RESTRICT_REF node_id ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->nodeIndex( lock, node_id );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeInfoBase const& SIXTRL_RESTRICT_REF node_info_base ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->nodeIndex( lock, &node_info_base );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        const NodeInfoBase *const SIXTRL_RESTRICT ptr_node_info_base ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->nodeIndex( lock, ptr_node_info_base );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        std::string const& SIXTRL_RESTRICT node_id_str,
        NodeControllerBase::node_str_role_t const role ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->nodeIndex( lock, node_id_str.c_str(), role );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        char const* SIXTRL_RESTRICT node_id_str,
        NodeControllerBase::node_str_role_t const role ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->nodeIndex( lock, node_id_str, role );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const node_index
        ) const  SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;

        return ( ( this->nodeStore().isNodeAvailable( lock, node_index ) ) &&
                 ( this->doCheckIfNodeIndexIsAvailableLocally(
                    lock, node_index ) ) )
            ? node_index : _this_t::UNDEFINED_INDEX;
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::platform_id_t const platform_id,
        NodeControllerBase::device_id_t const device_id
        ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;

        _this_t::node_index_t index = this->nodeStore().findNodeIndex(
                    lock, this->archId(), platform_id, device_id );

        if( !this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) )
        {
            index = _this_t::UNDEFINED_INDEX;
        }

        return index;
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_id_t const& SIXTRL_RESTRICT_REF
            node_id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;

        _this_t::node_index_t index =
            this->nodeStore().findNodeIndex( lock, node_id );

        if( !this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) )
        {
            index = _this_t::UNDEFINED_INDEX;
        }

        return index;
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_info_base_t const&
            SIXTRL_RESTRICT_REF node_info_base ) const SIXTRL_NOEXCEPT
    {
        return this->nodeIndex( lock, &node_info_base );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        const NodeControllerBase::node_info_base_t *const
            SIXTRL_RESTRICT ptr_node_info_base ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;

        _this_t::node_index_t index =
            this->nodeStore().findNodeIndex( lock, ptr_node_info_base );

        if( !this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) )
        {
            index = _this_t::UNDEFINED_INDEX;
        }

        return index;
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::string const& SIXTRL_RESTRICT node_id_str,
        NodeControllerBase::node_str_role_t const role ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;

        _this_t::node_index_t index = this->nodeStore().findNodeIndex(
            lock, this->archId(), node_id_str, role );

        if( !this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) )
        {
            index = _this_t::UNDEFINED_INDEX;
        }

        return index;
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        char const* SIXTRL_RESTRICT node_id_str,
        NodeControllerBase::node_str_role_t const role ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;

        _this_t::node_index_t index = this->nodeStore().findNodeIndex(
            lock, this->archId(), node_id_str, role );

        if( !this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) )
        {
            index = _this_t::UNDEFINED_INDEX;
        }

        return index;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE NodeControllerBase::node_index_t
        NodeControllerBase::nodeIndexByUniqueIdStr(
        std::string const& SIXTRL_RESTRICT_REF unique_id_str ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );

        return this->nodeIndex(
            lock, unique_id_str.c_str(), _this_t::NODE_UNIQUE_ID_STR );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndexByUniqueIdStr(
        char const* SIXTRL_RESTRICT unique_id_str ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );

        return this->nodeIndex(
            lock, unique_id_str, _this_t::NODE_UNIQUE_ID_STR );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndexByUniqueIdStr(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::string const& SIXTRL_RESTRICT_REF unique_id_str
        ) const SIXTRL_NOEXCEPT
    {
        return this->nodeIndex( lock, unique_id_str.c_str(),
            SIXTRL_CXX_NAMESPACE::NodeControllerBase::NODE_UNIQUE_ID_STR );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndexByUniqueIdStr(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        char const* SIXTRL_RESTRICT unique_id_str ) const
    {
        return this->nodeIndex( lock, unique_id_str,
            SIXTRL_CXX_NAMESPACE::NodeControllerBase::NODE_UNIQUE_ID_STR );
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
            this->nodeIndex( lock, std::forward< Args >( args )... ) );
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::ptrNodeId(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        NodeControllerBase::node_id_t const* ptr_node_id = nullptr;

        if( this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) )
        {
            ptr_node_id = this->nodeStore().ptrNodeId( lock, index );
        }

        return ptr_node_id;
    }

    /* --------------------------------------------------------------------- */

    template< typename... Args >
    NodeControllerBase::node_info_base_t const*
    NodeControllerBase::ptrNodeInfoBase( Args&&... args ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;

        NodeControllerBase::lock_t lock( *this->nodeStore().lockable() );

        _this_t::node_index_t const node_index =
            this->nodeIndex( lock, std::forward< Args >( args )... );

        return this->ptrNodeInfoBase( lock, node_index );
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

        if( this->doCheckIfNodeIndexIsAvailableLocally( lock, index ) )
        {
            ptr_node_info = this->nodeStore().ptrNodeInfoBase(
                lock, index );
        }

        return ptr_node_info;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeControllerBase::node_index_t const*
    NodeControllerBase::nodeIndicesBegin() const SIXTRL_NOEXCEPT
    {
        NodeControllerBase::node_index_t const* begin = nullptr;

        if( this->isSyncWithNodeStore() )
        {
            begin = this->m_available_node_indices.data();
        }

        return begin;
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t const*
    NodeControllerBase::nodeIndicesEnd() const SIXTRL_NOEXCEPT
    {
        NodeControllerBase::node_index_t const* end = this->nodeIndicesBegin();

        if( end != nullptr )
        {
            SIXTRL_ASSERT( this->isSyncWithNodeStore() );
            std::advance( end, this->m_available_node_indices.size() );
        }

        return end;
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::nodeIdsBegin() const SIXTRL_NOEXCEPT
    {
        NodeControllerBase::node_id_t const* begin = nullptr;

        if( this->isSyncWithNodeStore() )
        {
            begin = this->m_available_node_ids.data();
        }

        return begin;
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t const*
    NodeControllerBase::nodeIdsEnd() const SIXTRL_NOEXCEPT
    {
        NodeControllerBase::node_id_t const* end = this->nodeIdsBegin();

        if( end != nullptr )
        {
            SIXTRL_ASSERT( this->isSyncWithNodeStore() );
            std::advance( end, this->m_available_node_ids.size() );
        }

        return end;
    }

    SIXTRL_INLINE std::string NodeControllerBase::nodeIdString(
        NodeControllerBase::node_index_t const node_index ) const
    {
        SIXTRL_ASSERT( this->isSyncWithNodeStore() );
        NodeControllerBase::node_id_str_buffer_t const& buffer =
            this->m_available_node_id_strings.at( node_index );

        return std::string( buffer.data() );
    }

    SIXTRL_INLINE char const* NodeControllerBase::ptrNodeIdString(
        NodeControllerBase::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->isSyncWithNodeStore() );
        NodeControllerBase::node_id_str_buffer_t const& buffer =
            this->m_available_node_id_strings.at( index );

        return buffer.data();
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

    SIXTRL_INLINE NodeControllerBase::node_store_t&
    NodeControllerBase::nodeStore() SIXTRL_NOEXCEPT
    {
        return this->m_node_store;
    }

    SIXTRL_INLINE NodeControllerBase::node_store_t*
    NodeControllerBase::ptrNodeStore() SIXTRL_NOEXCEPT
    {
        return &this->m_node_store;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::doResetKeyFromNodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::kernel_config_key_t& SIXTRL_RESTRICT_REF key,
        NodeControllerBase::node_index_t const node_index,
        NodeControllerBase::kernel_purpose_t const purpose ) const
    {
        return this->doResetKeyFromNodeIndex( lock, key, node_index, purpose,
            this->variant(), this->ptrDefaultKernelConfigStr() );
    }

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::doResetKeyFromNodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::kernel_config_key_t& SIXTRL_RESTRICT_REF key,
        NodeControllerBase::node_index_t const node_index,
        NodeControllerBase::kernel_purpose_t const purpose,
        NodeControllerBase::variant_t const variant_flags ) const
    {
        return this->doResetKeyFromNodeIndex( lock, key, node_index, purpose,
            variant_flags, this->ptrDefaultKernelConfigStr() );
    }

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::doResetKeyFromNodeIndex(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::kernel_config_key_t& SIXTRL_RESTRICT_REF key,
        NodeControllerBase::node_index_t const node_index,
        NodeControllerBase::kernel_purpose_t const purpose,
        NodeControllerBase::variant_t const variant_flags,
        std::string const& SIXTRL_RESTRICT_REF kernel_config_str ) const
    {
        return this->doResetKeyFromNodeIndex( lock, key, node_index, purpose,
            variant_flags, kernel_config_str.c_str() );
    }

    /* --------------------------------------------------------------------- */

    template< typename... Args >
    std::pair< NodeControllerBase::status_t, bool >
    NodeControllerBase::doChangeNodeBeforeOp(
        NodeControllerBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeControllerBase::node_index_t* SIXTRL_RESTRICT ptr_prev_node_index,
        Args&&... new_node_args )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        using _this_t = st::NodeControllerBase;
        using index_t = _this_t::node_index_t;

        std::pair< NodeControllerBase::status_t, bool > result =
            std::make_pair( st::ARCH_STATUS_GENERAL_FAILURE, false );

        index_t current_node_index = _this_t::UNDEFINED_INDEX;

        if( ( this->nodeStore().checkLock( lock ) ) &&
            ( this->hasSelectedNode( lock ) ) )
        {
            current_node_index = this->selectedNodeIndex( lock );
            SIXTRL_ASSERT( current_node_index != _this_t::UNDEFINED_INDEX );

            if( ptr_prev_node_index != nullptr )
            {
                *ptr_prev_node_index = current_node_index;
            }

            index_t const to_select_node_index = this->nodeIndex(
                lock, std::forward< Args >( new_node_args )... );

            if( to_select_node_index != _this_t::UNDEFINED_INDEX )
            {
                result.second = ( to_select_node_index != current_node_index );

                if( result.second )
                {
                    result.first = this->changeSelectedNode(
                        lock, to_select_node_index );
                }
                else
                {
                    result.first = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return result;
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
