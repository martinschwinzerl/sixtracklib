#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_CXX_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_CXX_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )
#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
        #include <atomic>
        #include <cstddef>
        #include <cstdlib>
        #include <cstring>
        #include <cstdio>
        #include <memory>
        #include <map>
        #include <thread>
        #include <mutex>
        #include <stdexcept>
        #include <unordered_map>
        #include <vector>
        #include <utility>
#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/architecture/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

namespace SIXTRL_CXX_NAMESPACE
{
    class NodeSetBase;
    class NodeInfoBase;

    class NodeStore
    {
        public:

        using status_t                = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using size_type               = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using node_index_t            = SIXTRL_CXX_NAMESPACE::node_index_t;
        using node_set_base_t         = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        using node_info_base_t        = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        using node_id_t               = SIXTRL_CXX_NAMESPACE::NodeId;
        using node_str_role_t         = SIXTRL_CXX_NAMESPACE::node_str_role_t;
        using arch_id_t               = SIXTRL_CXX_NAMESPACE::arch_id_t;
        using platform_id_t           = SIXTRL_CXX_NAMESPACE::node_platform_id_t;
        using device_id_t             = SIXTRL_CXX_NAMESPACE::node_device_id_t;
        using kernel_set_id_t         = SIXTRL_CXX_NAMESPACE::kernel_set_id_t;
        using node_set_id_t           = SIXTRL_CXX_NAMESPACE::node_set_id_t;

        using sync_id_value_t         = uint64_t;
        using sync_id_t               = std::atomic< sync_id_value_t >;

        using lockable_t              = std::mutex;
        using lock_t                  = std::unique_lock< lockable_t >;

        using ptr_stored_node_info_t  =
            std::unique_ptr< SIXTRL_CXX_NAMESPACE::NodeInfoBase >;

        using ptr_stored_node_set_t   =
            std::unique_ptr< SIXTRL_CXX_NAMESPACE::NodeSetBase >;

        friend SIXTRL_CXX_NAMESPACE::NodeSetBase;
        friend SIXTRL_CXX_NAMESPACE::NodeInfoBase;

        static constexpr node_str_role_t NODE_ID_STR =
            SIXTRL_CXX_NAMESPACE::NODE_STR_ROLE_ID;

        static constexpr node_str_role_t NODE_UNIQUE_ID_STR =
            SIXTRL_CXX_NAMESPACE::NODE_STR_ROLE_UNIQUE_ID;

        static constexpr arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static constexpr platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static constexpr device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static constexpr node_index_t UNDEFINED_INDEX =
            SIXTRL_CXX_NAMESPACE::NODE_UNDEFINED_INDEX;

        static constexpr node_set_id_t ILLEGAL_NODE_SET_ID =
            SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_KERNEL_SET_ID;

        static constexpr sync_id_value_t ILLEGAL_SYNC_ID_VALUE =
            sync_id_value_t{ 0xffffffffffffffff };

        static constexpr sync_id_value_t LAST_LEGAL_SYNC_ID_VALUE =
            sync_id_value_t{ 0xfffffffffffffffe };

        /* ***************************************************************** */

        SIXTRL_HOST_FN NodeStore();

        SIXTRL_HOST_FN NodeStore(
            NodeStore const& SIXTRL_RESTRICT_REF other );

        SIXTRL_HOST_FN NodeStore( NodeStore&& other ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN NodeStore& operator=(
            NodeStore const& SIXTRL_RESTRICT_REF other );

        SIXTRL_HOST_FN NodeStore& operator=(
            NodeStore&& other ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN virtual ~NodeStore() SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type numArchitectures() const;

        SIXTRL_HOST_FN bool hasArchitecture( arch_id_t const arch_id ) const;

        template< typename ArchIdIter >
        SIXTRL_HOST_FN status_t architectureIds(
            ArchIdIter begin, ArchIdIter end,
            size_type* SIXTRL_RESTRICT ptr_num_architectures ) const;

        SIXTRL_HOST_FN status_t addArchitecture( arch_id_t const arch_id );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN size_type numArchitectures(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasArchitecture(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        template< typename ArchIdIter >
        SIXTRL_HOST_FN status_t architectureIds(
            NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
            ArchIdIter begin, ArchIdIter end,
            size_type* SIXTRL_RESTRICT ptr_num_archs ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t addArchitecture(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id );

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasPlatform( arch_id_t const arch_id,
                platform_id_t const platform_id ) const;

        SIXTRL_HOST_FN size_type numPlatforms( arch_id_t const arch_id ) const;

        SIXTRL_HOST_FN bool hasNode(
            node_id_t const& SIXTRL_RESTRICT_REF node_id ) const;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool hasPlatform(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id,
            platform_id_t const platform_id )const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numPlatforms(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_id_t const& SIXTRL_RESTRICT_REF node_id
        ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN bool numNodeSets(
            node_set_id_t const node_set_id ) const;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool numNodeSets(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            node_id_t const& SIXTRL_RESTRICT_REF node_id ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            const ::NS(NodeId) *const SIXTRL_RESTRICT ptr_node_id ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            arch_id_t const arch_id, platform_id_t const platform_id,
            device_id_t const device_id ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            node_info_base_t const* SIXTRL_RESTRICT ptr_node_info ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            char const* SIXTRL_RESTRICT str,
            node_str_role_t const role = NODE_ID_STR ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            std::string const& SIXTRL_RESTRICT_REF str,
            node_str_role_t const role = NODE_ID_STR ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            arch_id_t const arch_id,
            char const* SIXTRL_RESTRICT str,
            node_str_role_t const role = NODE_ID_STR ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF str,
            node_str_role_t const role = NODE_ID_STR ) const;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_id_t const& SIXTRL_RESTRICT_REF nid ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            const ::NS(NodeId) *const SIXTRL_RESTRICT
                ptr_node_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id, platform_id_t const platform_id,
            device_id_t const device_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_info_base_t const* SIXTRL_RESTRICT
                ptr_node_info ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            char const* SIXTRL_RESTRICT str,
            node_str_role_t const role = NODE_ID_STR ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            std::string const& SIXTRL_RESTRICT_REF str,
            node_str_role_t const role = NODE_ID_STR ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            char const* SIXTRL_RESTRICT str,
            node_str_role_t const role = NODE_ID_STR ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF str,
            node_str_role_t const role = NODE_ID_STR ) const;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type totalNumNodes() const;

        SIXTRL_HOST_FN size_type numNodes( arch_id_t const arch_id ) const;

        SIXTRL_HOST_FN size_type numNodes( arch_id_t const arch_id,
            platform_id_t const platform_id ) const;

        SIXTRL_HOST_FN node_index_t minAttachedNodeIndex(
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN node_index_t maxAttachedNodeIndex(
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN size_type numNodes(
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN size_type numSelectedNodes(
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN size_type numDefaultNodes(
            node_set_id_t const node_set_id ) const;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN size_type totalNumNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id,
            platform_id_t const platform_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numSelectedNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numDefaultNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t minAttachedNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t maxAttachedNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* attachedNodeIndicesBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* attachedNodeIndicesEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* selectedNodeIndicesBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* selectedNodeIndicesEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* defaultNodeIndicesBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* defaultNodeIndicesEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        template< typename NodeIndexIter >
        SIXTRL_HOST_FN status_t nodeIndices(
            NodeIndexIter begin, NodeIndexIter end,
            size_type* SIXTRL_RESTRICT ptr_num_nodes ) const;

        template< typename NodeIndexIter >
        SIXTRL_HOST_FN status_t nodeIndices(
            NodeIndexIter begin, NodeIndexIter end, arch_id_t const arch_id,
            size_type* SIXTRL_RESTRICT ptr_num_nodes ) const;

        template< typename NodeIndexIter >
        SIXTRL_HOST_FN status_t nodeIndices(
            NodeIndexIter begin, NodeIndexIter end,
            arch_id_t const arch_id, platform_id_t const platform_id,
            size_type* SIXTRL_RESTRICT ptr_num_nodes ) const;

        template< typename NodeIndexIter >
        SIXTRL_HOST_FN status_t nodeIndices(
            NodeIndexIter begin, NodeIndexIter end,
            node_set_id_t const node_set_id,
            size_type* SIXTRL_RESTRICT ptr_num_nodes ) const;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< typename NodeIndexIter >
        SIXTRL_HOST_FN status_t nodeIndices(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            NodeIndexIter begin, NodeIndexIter end,
            size_type* SIXTRL_RESTRICT ptr_num_nodes ) const SIXTRL_NOEXCEPT;

        template< typename NodeIndexIter >
        SIXTRL_HOST_FN status_t nodeIndices(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            NodeIndexIter begin, NodeIndexIter end, arch_id_t const arch_id,
            size_type* SIXTRL_RESTRICT ptr_num_nodes ) const SIXTRL_NOEXCEPT;

        template< typename NodeIndexIter >
        SIXTRL_HOST_FN status_t nodeIndices(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            NodeIndexIter begin, NodeIndexIter end,
            arch_id_t const arch_id, platform_id_t const platform_id,
            size_type* SIXTRL_RESTRICT ptr_num_nodes ) const SIXTRL_NOEXCEPT;

        template< typename NodeIndexIter >
        SIXTRL_HOST_FN status_t nodeIndices(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            NodeIndexIter begin, NodeIndexIter end,
            node_set_id_t const node_set_id,
            size_type* SIXTRL_RESTRICT ptr_num_nodes ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN bool isNodeAvailable(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN node_id_t const* ptrNodeId(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN node_info_base_t const* ptrNodeInfoBase(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN node_info_base_t* ptrNodeInfoBase(
            node_index_t const index );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool isNodeAvailable(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* ptrNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_base_t const* ptrNodeInfoBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_base_t* ptrNodeInfoBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasNodeSets() const;
        SIXTRL_HOST_FN size_type numNodeSets() const;

        SIXTRL_HOST_FN bool hasNodeSet( node_set_id_t const set_id ) const;

        SIXTRL_HOST_FN bool hasNodeSet( SIXTRL_CXX_NAMESPACE::NodeSetBase&
            SIXTRL_RESTRICT_REF node_set ) const;

        SIXTRL_HOST_FN node_set_id_t addNodeSet(
            ptr_stored_node_set_t&& ptr_node_set );

        SIXTRL_HOST_FN status_t removeNodeSet( node_set_id_t const set_id );

        SIXTRL_HOST_FN node_set_id_t nodeSetId(
            SIXTRL_CXX_NAMESPACE::NodeSetBase&
                SIXTRL_RESTRICT_REF node_set ) const;

        SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::NodeSetBase*
        ptrNodeSetBase( node_set_id_t const node_set_id );

        SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::NodeSetBase const*
        ptrNodeSetBase( node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::NodeSetBase&
        nodeSetBase( node_set_id_t const node_set_id );

        SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::NodeSetBase const&
        nodeSetBase( node_set_id_t const node_set_id ) const;

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

        SIXTRL_HOST_FN bool hasNodeSets(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numNodeSets(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasNodeSet( lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasNodeSet( lock_t const& SIXTRL_RESTRICT_REF lock,
            SIXTRL_CXX_NAMESPACE::NodeSetBase&
                SIXTRL_RESTRICT_REF node_set ) const  SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_set_id_t addNodeSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            ptr_stored_node_set_t&& ptr_node_set );

        SIXTRL_HOST_FN status_t removeNodeSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const sid ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_set_id_t nodeSetId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            SIXTRL_CXX_NAMESPACE::NodeSetBase&
                SIXTRL_RESTRICT_REF node_set ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::NodeSetBase*
        ptrNodeSetBase( lock_t const& SIXTRL_RESTRICT_REF lock,
                        node_set_id_t const node_set_id )  SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::NodeSetBase const*
        ptrNodeSetBase( lock_t const& SIXTRL_RESTRICT_REF lock,
                        node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::NodeSetBase&
        nodeSetBase( lock_t const& SIXTRL_RESTRICT_REF lock,
                        node_set_id_t const node_set_id );

        SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::NodeSetBase const&
        nodeSetBase( lock_t const& SIXTRL_RESTRICT_REF lock,
                        node_set_id_t const node_set_id ) const;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t addNode(
            ptr_stored_node_info_t&& ptr_stored_node_info );

        SIXTRL_HOST_FN status_t removeNode(
            node_index_t const node_index );

        SIXTRL_HOST_FN status_t attachNodeToSet(
            node_index_t const node_index, node_set_id_t const set_id );

        SIXTRL_HOST_FN status_t attachAllArchitectureNodesToSet(
            arch_id_t const arch_id, node_set_id_t const node_set_id );

        SIXTRL_HOST_FN status_t detachNodeFromSet(
            node_index_t const node_index, node_set_id_t const node_set_id );

        SIXTRL_HOST_FN status_t detachAllNodesFromSet(
            node_set_id_t const node_set_id );

        SIXTRL_HOST_FN status_t detachNodeFromAllSets(
            node_index_t const node_index );

        SIXTRL_HOST_FN size_type numSetsAttachedToNode(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN bool isNodeAttachedToAnySet(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN bool isNodeAttachedToSet( node_index_t const node_index,
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN bool canNodeBeSelectedBySet( node_index_t const index,
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN bool isNodeSelectedBySet(
            node_index_t const node_index, node_set_id_t const set_id ) const;

        SIXTRL_HOST_FN bool isNodeSelectedByAnySet(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN size_type numSelectingSetsForNode(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN bool isNodeDefaultForSet(
            node_index_t const node_index, node_set_id_t const set_id ) const;

        SIXTRL_HOST_FN bool isNodeDefaultForAnySet(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN size_type numSetsHavingNodeAsDefault(
            node_index_t const index ) const SIXTRL_NOEXCEPT;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN node_index_t addNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            ptr_stored_node_info_t&& ptr_stored_node_info );

        SIXTRL_HOST_FN status_t removeNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        SIXTRL_HOST_FN status_t attachNodeToSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index, node_set_id_t const set_id );

        SIXTRL_HOST_FN status_t attachAllArchitectureNodesToSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id, node_set_id_t const node_set_id );

        SIXTRL_HOST_FN status_t detachNodeFromSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index, node_set_id_t const node_set_id );

        SIXTRL_HOST_FN status_t detachAllNodesFromSet(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_set_id_t const sid );

        SIXTRL_HOST_FN status_t detachNodeFromAllSets(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index );

        SIXTRL_HOST_FN size_type numSetsAttachedToNode(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const ) const;

        SIXTRL_HOST_FN bool isNodeAttachedToAnySet(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const ) const;

        SIXTRL_HOST_FN bool isNodeAttachedToSet(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index,
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN node_set_id_t const* attachedNodeSetIdsBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_set_id_t const* attachedNodeSetIdsEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool canNodeBeSelectedBySet(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isNodeSelectedBySet(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index,
            node_set_id_t const set_id ) const;

        SIXTRL_HOST_FN bool isNodeSelectedByAnySet(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const ) const;

        SIXTRL_HOST_FN size_type numSelectingSetsForNode(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const ) const;

        SIXTRL_HOST_FN node_set_id_t const* selectingNodeSetIdsBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_set_id_t const* selectingNodeSetIdsEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numSetsHavingNodeAsDefault(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isNodeDefaultForSet(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index,
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN bool isNodeDefaultForAnySet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_set_id_t const* defaultNodeSetIdsBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_set_id_t const* defaultNodeSetIdsEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN void clear();
        SIXTRL_HOST_FN void clear(
            lock_t const& SIXTRL_RESTRICT_REF lock );

    /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN sync_id_value_t syncIdValue() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN sync_id_t const& syncId() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSyncWith(
            sync_id_t const& SIXTRL_RESTRICT_REF sid ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSyncWith(
            sync_id_value_t const sync_id_value ) const SIXTRL_NOEXCEPT;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN sync_id_value_t registerChange(
            lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN bool checkLock(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void checkLockAndThrowOnError(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        protected:

        using platforms_list_t          = std::vector< platform_id_t >;
        using devices_list_t            = std::vector< device_id_t >;
        using node_indices_list_t       = std::vector< node_index_t >;
        using node_set_list_t           = std::vector< ptr_stored_node_set_t >;
        using node_set_ids_list_t       = std::vector< node_set_id_t >;
        using arch_platform_pair_t      = std::pair< arch_id_t, platform_id_t >;

        using arch_to_platforms_t =
            std::unordered_map< arch_id_t, platforms_list_t >;

        using arch_platform_to_devices_t =
            std::map< arch_platform_pair_t, devices_list_t >;

        using arch_platform_to_plfm_name_t =
            std::map< arch_platform_pair_t, std::string >;

        using node_id_to_node_index_t   = std::map< node_id_t, node_index_t >;
        using stored_node_info_buffer_t = std::vector< ptr_stored_node_info_t >;

        using node_set_to_node_indices_t =
            std::unordered_map< node_set_id_t, node_indices_list_t >;

        using node_index_to_node_set_ids_t =
            std::unordered_map< node_index_t, node_set_ids_list_t >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN virtual node_index_t doAddNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            ptr_stored_node_info_t&& ptr_stored_node_info );

        SIXTRL_HOST_FN virtual status_t doRemoveNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        SIXTRL_HOST_FN virtual status_t doClear(
            lock_t const& SIXTRL_RESTRICT_REF lock );

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t doMarkNodeAsSelectedBySet(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index,
            node_set_id_t const set_id );

        SIXTRL_HOST_FN status_t doUnselectNodeFromSet(
            lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index,
            node_set_id_t const set_id );

        SIXTRL_HOST_FN status_t doMarkNodeAsDefaultForSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index, node_set_id_t const node_set_id );

        SIXTRL_HOST_FN status_t doRemoveDefaultNodeFromSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index, node_set_id_t const node_set_id );

        SIXTRL_HOST_FN status_t doUpdateNodeIdToIndexMap(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_id_t const& SIXTRL_RESTRICT_REF current_node_id,
            node_index_t const node_index,
            node_id_t const& SIXTRL_RESTRICT_REF new_node_id );

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t doAddArchitecture(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id );

        SIXTRL_HOST_FN platform_id_t doGetNextPlatformId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id );

        SIXTRL_HOST_FN status_t doAddPlatform(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id, platform_id_t const platform_id );

        SIXTRL_HOST_FN device_id_t doGetNextDeviceId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id, platform_id_t const platform_id );

        SIXTRL_HOST_FN status_t doPrepareNewNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            node_index_t const node_index );

        private:

        SIXTRL_HOST_FN void doClearWithoutLocking() SIXTRL_NOEXCEPT;

        arch_to_platforms_t             m_arch_to_platforms;

        node_set_to_node_indices_t      m_node_set_to_node_idxs;
        node_set_to_node_indices_t      m_node_set_to_sel_node_idxs;
        node_set_to_node_indices_t      m_node_set_to_def_node_idxs;

        node_index_to_node_set_ids_t    m_node_idx_to_set_ids;
        node_index_to_node_set_ids_t    m_node_idx_to_sel_set_ids;
        node_index_to_node_set_ids_t    m_node_idx_to_def_set_ids;

        arch_platform_to_devices_t      m_arch_platform_to_devices;
        node_id_to_node_index_t         m_node_id_to_node_index;

        stored_node_info_buffer_t       m_stored_node_infos;
        node_set_list_t                 m_stored_node_sets;

        sync_id_t                       m_sync_id;
        size_type                       m_num_node_infos;
        size_type                       m_num_node_sets;

        mutable lockable_t              m_lockable;
    };

    SIXTRL_HOST_FN NodeStore& NodeStore_get();
    SIXTRL_HOST_FN NodeStore const& NodeStore_get_const();

    SIXTRL_HOST_FN NodeStore* NodeStore_get_ptr();
    SIXTRL_HOST_FN NodeStore const* NodeStore_get_const_ptr();
}

#endif /* C++ Host */


#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

typedef SIXTRL_CXX_NAMESPACE::NodeStore NS(NodeStore);
typedef SIXTRL_CXX_NAMESPACE::NodeStore::lock_t NS(NodeStoreLock);

#else

typedef void NS(NodeStore);
typedef void NS(NodeStoreLock);

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) && \
         !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

/* ************************************************************************* */
/* ******  Implementation of inline and template member functions    ******* */
/* ************************************************************************* */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
   #include "sixtracklib/common/control/node_id.hpp"
   #include "sixtracklib/common/control/node_info.hpp"
   #include "sixtracklib/common/control/node_set.hpp"
   #include "sixtracklib/common/internal/stl_buffer_helper.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeStore& NodeStore_get()
    {
        static SIXTRL_CXX_NAMESPACE::NodeStore node_store;
        return node_store;
    }

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeStore const& NodeStore_get_const()
    {
        static SIXTRL_CXX_NAMESPACE::NodeStore node_store;
        return node_store;
    }

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeStore* NodeStore_get_ptr()
    {
        return &SIXTRL_CXX_NAMESPACE::NodeStore_get();
    }

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeStore const*
        NodeStore_get_const_ptr()
    {
        return &SIXTRL_CXX_NAMESPACE::NodeStore_get();
    }

    /* ********************************************************************* */

    SIXTRL_INLINE NodeStore::size_type NodeStore::numArchitectures() const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->numArchitectures( lock );
    }

    SIXTRL_INLINE bool NodeStore::hasArchitecture(
        NodeStore::arch_id_t const arch_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->hasArchitecture( lock, arch_id );
    }

    template< typename ArchIdIter >
    SIXTRL_INLINE NodeStore::status_t NodeStore::architectureIds(
        ArchIdIter begin, ArchIdIter end,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_archs ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->architectureIds( lock, begin, end, ptr_num_archs );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::addArchitecture(
        NodeStore::arch_id_t const arch_id )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->doAddArchitecture( lock, arch_id );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeStore::size_type NodeStore::numArchitectures(
        NodeStore::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? this->m_arch_to_platforms.size() : ::NS(arch_size_t){ 0 };
    }

    SIXTRL_INLINE bool NodeStore::hasArchitecture(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return ( ( arch_id != SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL ) &&
                 ( this->m_arch_to_platforms.find( arch_id ) !=
                   this->m_arch_to_platforms.end() ) );
    }

    template< typename ArchIdIter >
    NodeStore::status_t NodeStore::architectureIds(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        ArchIdIter begin, ArchIdIter end,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_archs
        ) const SIXTRL_NOEXCEPT
    {
        using size_t = NodeStore::size_type;
        using node_id_t = NodeStore::node_id_t;
        using status_t = NodeStore::status_t;

        status_t status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        size_t const num_archs = this->numArchitectures( lock );

        if( ( this->checkLock( lock ) ) && ( num_archs > size_t{ 0 } ) )
        {
            if( std::distance( begin, end ) > std::ptrdiff_t{ 0 } )
            {
                bool found_items = false;

                auto in_it  = this->m_arch_to_platforms.begin();
                auto in_end = this->m_arch_to_platforms.end();

                ArchIdIter out_it = begin;

                for( ; in_it != in_end ; ++in_it )
                {
                    if( in_it->first != node_id_t::ARCH_ILLEGAL )
                    {
                        found_items = true;

                        if( out_it != end )
                        {
                            *out_it++ = in_it->first;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                size_t const num_archs_copied = static_cast< size_t >(
                    std::distance( begin, out_it ) );

                if( ptr_num_archs != nullptr )
                {
                    *ptr_num_archs = num_archs_copied;
                }

                if( out_it != end )
                {
                    std::fill( out_it, end, node_id_t::ARCH_ILLEGAL );
                }

                if( ( num_archs_copied > size_t{ 0 } ) || ( !found_items ) )
                {
                    status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::addArchitecture(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id )
    {
        return this->doAddArchitecture( lock, arch_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeStore::hasPlatform(
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->hasPlatform( lock, arch_id, platform_id );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numPlatforms(
        NodeStore::arch_id_t const arch_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->numPlatforms( lock, arch_id );
    }

    SIXTRL_INLINE bool NodeStore::hasNode(
        NodeStore::node_id_t const& SIXTRL_RESTRICT_REF node_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->hasNode( lock, node_id );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE bool NodeStore::hasNode(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_id_t const& SIXTRL_RESTRICT_REF
            node_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( node_id.valid() ) && ( this->checkLock( lock ) ) &&
            ( this->findNodeIndex( node_id ) != NodeStore::UNDEFINED_INDEX ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::node_id_t const& SIXTRL_RESTRICT_REF node_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->findNodeIndex( lock, node_id );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        const ::NS(NodeId) *const SIXTRL_RESTRICT ptr_node_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->findNodeIndex( lock, ptr_node_id );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        NodeStore::device_id_t const device_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->findNodeIndex( lock, arch_id, platform_id, device_id );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::node_info_base_t const* SIXTRL_RESTRICT ptr_node_info ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->findNodeIndex( lock, ptr_node_info );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        char const* SIXTRL_RESTRICT str,
        NodeStore::node_str_role_t const str_role ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->findNodeIndex(
            lock, ::NS(ARCHITECTURE_ILLEGAL), str, str_role );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT str,
        NodeStore::node_str_role_t const str_role ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->findNodeIndex( lock, arch_id, str, str_role );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        std::string const& SIXTRL_RESTRICT_REF str,
        NodeStore::node_str_role_t const str_role ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->findNodeIndex(
            lock, ::NS(ARCHITECTURE_ILLEGAL), str.c_str(), str_role );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF str,
        NodeStore::node_str_role_t const str_role ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->findNodeIndex( lock, arch_id, str.c_str(), str_role );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        const ::NS(NodeId) *const SIXTRL_RESTRICT ptr_node_id )
        const  SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;

        _this_t::node_id_t const* ptr_cxx = st::asCxxNodeId( ptr_node_id );

        return ( ptr_cxx != nullptr )
            ? this->findNodeIndex( lock, *ptr_cxx ) : _this_t::UNDEFINED_INDEX;
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        NodeStore::device_id_t const device_id ) const SIXTRL_NOEXCEPT
    {
        return this->findNodeIndex( lock,
            NodeStore::node_id_t{ arch_id, platform_id, device_id } );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        char const* SIXTRL_RESTRICT str,
        NodeStore::node_str_role_t const str_role ) const
    {
        return this->findNodeIndex(
            lock, ::NS(ARCHITECTURE_ILLEGAL), str, str_role );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::string const& SIXTRL_RESTRICT_REF str,
        NodeStore::node_str_role_t const str_role ) const
    {
        return this->findNodeIndex(
            lock, ::NS(ARCHITECTURE_ILLEGAL), str.c_str(), str_role );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF str,
        NodeStore::node_str_role_t const str_role ) const
    {
        return this->findNodeIndex( lock, arch_id, str.c_str(), str_role );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::size_type NodeStore::totalNumNodes() const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->totalNumNodes( lock );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numNodes(
        NodeStore::arch_id_t const arch_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->numNodes( lock, arch_id );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numNodes(
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->numNodes( lock, arch_id, platform_id );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::minAttachedNodeIndex(
        NodeStore::node_set_id_t const node_set_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->minAttachedNodeIndex( lock, node_set_id );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::maxAttachedNodeIndex(
        NodeStore::node_set_id_t const node_set_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->maxAttachedNodeIndex( lock, node_set_id );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numNodes(
        NodeStore::node_set_id_t const node_set_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->numNodes( lock, node_set_id );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numSelectedNodes(
        NodeStore::node_set_id_t const node_set_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->numSelectedNodes( lock, node_set_id );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numDefaultNodes(
        NodeStore::node_set_id_t const node_set_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->numDefaultNodes( lock, node_set_id );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeStore::size_type NodeStore::totalNumNodes(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->m_stored_node_infos.size();
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::minAttachedNodeIndex(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;
        _this_t::node_index_t node_index = _this_t::UNDEFINED_INDEX;

        if( ( node_set_id != _this_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_node_set_to_node_idxs.find( node_set_id );
            if( ( it != this->m_node_set_to_node_idxs.end() ) &&
                ( it->second.empty() ) )
            {
                SIXTRL_ASSERT( std::is_sorted(
                    it->second.begin(), it->second.end() ) );

                node_index = it->second.front();
                SIXTRL_ASSERT( node_index != _this_t::UNDEFINED_INDEX );
            }

            SIXTRL_ASSERT( ( node_index == _this_t::UNDEFINED_INDEX ) ||
                ( ( !st::Map_ordered_vec_empty( this->m_node_set_to_node_idxs,
                       node_set_id ) ) &&
                  ( this->isNodeAvailable( lock, node_index ) ) &&
                  ( this->isNodeAttachedToSet(
                      lock, node_index, node_set_id ) ) ) );
        }

        return node_index;
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::maxAttachedNodeIndex(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;
        _this_t::node_index_t node_index = _this_t::UNDEFINED_INDEX;

        if( ( node_set_id != _this_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_node_set_to_node_idxs.find( node_set_id );
            if( ( it != this->m_node_set_to_node_idxs.end() ) &&
                ( it->second.empty() ) )
            {
                SIXTRL_ASSERT( std::is_sorted(
                    it->second.begin(), it->second.end() ) );

                node_index = it->second.back();
                SIXTRL_ASSERT( node_index != _this_t::UNDEFINED_INDEX );
            }

            SIXTRL_ASSERT( ( node_index == _this_t::UNDEFINED_INDEX ) ||
                ( ( st::Map_ordered_vec_empty( this->m_node_set_to_node_idxs,
                       node_set_id ) ) &&
                  ( this->isNodeAvailable( lock, node_index ) ) &&
                  ( this->isNodeAttachedToSet(
                      lock, node_index, node_set_id ) ) ) );
        }

        return node_index;
    }

    SIXTRL_INLINE NodeStore::node_index_t const*
    NodeStore::attachedNodeIndicesBegin(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;
        _this_t::node_index_t const* ptr_begin = nullptr;

        if( ( node_set_id != _this_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_begin = st::Map_ordered_vec_begin(
                this->m_node_set_to_node_idxs, node_set_id );
        }

        SIXTRL_ASSERT( ( ptr_begin == nullptr ) ||
            ( (  st::Map_has_key( this->m_node_set_to_node_idxs, node_set_id ) ) &&
              ( !st::Map_ordered_vec_empty( this->m_node_set_to_node_idxs,
                       node_set_id ) ) ) );

        return ptr_begin;
    }

    SIXTRL_INLINE NodeStore::node_index_t const*
    NodeStore::attachedNodeIndicesEnd(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;
        _this_t::node_index_t const* ptr_end = nullptr;

        if( ( node_set_id != _this_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_end = st::Map_ordered_vec_end(
                this->m_node_set_to_node_idxs, node_set_id );
        }

        SIXTRL_ASSERT( ( ptr_end == nullptr ) ||
            ( (  st::Map_has_key( this->m_node_set_to_node_idxs, node_set_id ) ) &&
              ( !st::Map_ordered_vec_empty( this->m_node_set_to_node_idxs,
                       node_set_id ) ) ) );

        return ptr_end;
    }

    SIXTRL_INLINE NodeStore::node_index_t const*
    NodeStore::selectedNodeIndicesBegin(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;
        _this_t::node_index_t const* ptr_begin = nullptr;

        if( ( node_set_id != _this_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_begin = st::Map_ordered_vec_begin(
                this->m_node_set_to_sel_node_idxs, node_set_id );
        }

        SIXTRL_ASSERT( ( ptr_begin == nullptr ) ||
            ( (  st::Map_has_key(
                   this->m_node_set_to_sel_node_idxs, node_set_id ) ) &&
              ( !st::Map_ordered_vec_empty( this->m_node_set_to_sel_node_idxs,
                   node_set_id ) ) ) );

        return ptr_begin;
    }

    SIXTRL_INLINE NodeStore::node_index_t const*
    NodeStore::selectedNodeIndicesEnd(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;
        _this_t::node_index_t const* ptr_end = nullptr;

        if( ( node_set_id != _this_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_end = st::Map_ordered_vec_end(
                this->m_node_set_to_sel_node_idxs, node_set_id );
        }

        SIXTRL_ASSERT( ( ptr_end == nullptr ) ||
            ( ( st::Map_has_key(
                    this->m_node_set_to_sel_node_idxs, node_set_id ) ) &&
              ( !st::Map_ordered_vec_empty( this->m_node_set_to_sel_node_idxs,
                    node_set_id ) ) ) );

        return ptr_end;
    }

    SIXTRL_INLINE NodeStore::node_index_t const*
    NodeStore::defaultNodeIndicesBegin(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;
        _this_t::node_index_t const* ptr_begin = nullptr;

        if( ( node_set_id != _this_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_begin = st::Map_ordered_vec_begin(
                this->m_node_set_to_def_node_idxs, node_set_id );
        }

        SIXTRL_ASSERT( ( ptr_begin == nullptr ) ||
            ( (  st::Map_has_key(
                    this->m_node_set_to_def_node_idxs, node_set_id ) ) &&
              ( !st::Map_ordered_vec_empty( this->m_node_set_to_def_node_idxs,
                    node_set_id ) ) ) );

        return ptr_begin;
    }

    SIXTRL_INLINE NodeStore::node_index_t const*
    NodeStore::defaultNodeIndicesEnd(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;
        _this_t::node_index_t const* ptr_end = nullptr;

        if( ( node_set_id != _this_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_end = st::Map_ordered_vec_end(
                this->m_node_set_to_def_node_idxs, node_set_id );
        }

        SIXTRL_ASSERT( ( ptr_end == nullptr ) ||
            ( ( st::Map_has_key(
                    this->m_node_set_to_def_node_idxs, node_set_id ) ) &&
              ( !st::Map_ordered_vec_empty( this->m_node_set_to_def_node_idxs,
                    node_set_id ) ) ) );

        return ptr_end;
    }

    /* --------------------------------------------------------------------- */

    template< typename NodeIndexIter >
    SIXTRL_INLINE NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->nodeIndices( lock, begin, end, ptr_num_nodes );
    }

    template< typename NodeIndexIter >
    SIXTRL_INLINE NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::arch_id_t const arch_id,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->nodeIndices( lock, begin, end, arch_id, ptr_num_nodes );
    }

    template< typename NodeIndexIter >
    SIXTRL_INLINE NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->nodeIndices(
            lock, begin, end, arch_id, platform_id, ptr_num_nodes );
    }

    template< typename NodeIndexIter >
    SIXTRL_INLINE NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::node_set_id_t const node_set_id,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->nodeIndices(
            lock, begin, end, node_set_id, ptr_num_nodes );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< typename NodeIndexIter >
    NodeStore::status_t NodeStore::nodeIndices(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::size_type* SIXTRL_RESTRICT
            ptr_num_nodes ) const SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;
        using size_t  = _this_t::size_type;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        size_t const num_nodes = this->totalNumNodes( lock );

        if( ( this->checkLock( lock ) ) && ( num_nodes > size_t{ 0 } ) )
        {
            if( std::distance( begin, end ) > std::ptrdiff_t{ 0 } )
            {
                bool found_items = false;

                auto in_it  = this->m_stored_node_infos.begin();
                auto in_end = this->m_stored_node_infos.end();
                NodeIndexIter out_it = begin;

                _this_t::node_index_t index = _this_t::node_index_t{ 0 };

                for( ; in_it != in_end ; ++in_it, ++index )
                {
                    if( in_it->get() != nullptr )
                    {
                        found_items = true;

                        if( out_it != end )
                        {
                            *out_it++ = index;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                size_t const num_nodes_copied = static_cast< size_t >(
                    std::distance( begin, out_it ) );

                if( ptr_num_nodes != nullptr )
                {
                    *ptr_num_nodes = num_nodes_copied;
                }

                if( out_it != end )
                {
                    std::fill( out_it, end, _this_t::UNDEFINED_INDEX );
                }

                if( ( num_nodes_copied > size_t{ 0 } ) || ( !found_items ) )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    template< typename NodeIndexIter >
    NodeStore::status_t NodeStore::nodeIndices(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::arch_id_t const arch_id,
        NodeStore::size_type* SIXTRL_RESTRICT
            ptr_num_nodes ) const SIXTRL_NOEXCEPT
    {
        namespace st  = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;
        using  size_t = _this_t::size_type;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->checkLock( lock ) ) &&
            ( arch_id != _this_t::ARCH_ILLEGAL ) )
        {
            if( std::distance( begin, end ) > std::ptrdiff_t{ 0 } )
            {
                bool found_items = false;

                auto in_it  = this->m_stored_node_infos.begin();
                auto in_end = this->m_stored_node_infos.end();

                _this_t::node_index_t index = _this_t::node_index_t{ 0 };
                NodeIndexIter out_it = begin;

                for( ; in_it != in_end ; ++in_it, ++index )
                {
                    if( ( in_it->get() != nullptr ) &&
                        ( ( *in_it )->archId() == arch_id ) )
                    {
                        found_items = true;

                        if( out_it != end )
                        {
                            *out_it++ = index;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                size_t const num_nodes_copied = static_cast< size_t >(
                    std::distance( begin, out_it ) );

                if( ptr_num_nodes != nullptr )
                {
                    *ptr_num_nodes = num_nodes_copied;
                }

                if( out_it != end )
                {
                    std::fill( out_it, end, _this_t::UNDEFINED_INDEX );
                }

                if( ( num_nodes_copied > size_t{ 0 } ) ||
                    ( !found_items ) )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    template< typename NodeIndexIter >
    NodeStore::status_t NodeStore::nodeIndices(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        NodeStore::size_type* SIXTRL_RESTRICT
            ptr_num_nodes ) const SIXTRL_NOEXCEPT
    {
        namespace st    = SIXTRL_CXX_NAMESPACE;
        using _this_t   = st::NodeStore;
        using size_t    = _this_t::size_type;

         _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->checkLock( lock ) ) &&
            ( arch_id != _this_t::ARCH_ILLEGAL ) &&
            ( platform_id != _this_t::ILLEGAL_PLATFORM_ID ) )
        {
            if( std::distance( begin, end ) > std::ptrdiff_t{ 0 } )
            {
                bool found_items = false;
                auto in_it  = this->m_stored_node_infos.begin();
                auto in_end = this->m_stored_node_infos.end();

                _this_t::node_index_t index = _this_t::node_index_t{ 0 };
                NodeIndexIter out_it = begin;

                for( ; in_it != in_end ; ++in_it, ++index )
                {
                    if( ( in_it->get() != nullptr ) &&
                        ( ( *in_it )->archId() == arch_id ) &&
                        ( ( *in_it )->platformId() == platform_id ) )
                    {
                        found_items = true;

                        if( out_it != end )
                        {
                            *out_it++ = index;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                size_t const num_nodes_copied = static_cast< size_t >(
                    std::distance( begin, out_it ) );

                if( ptr_num_nodes != nullptr )
                {
                    *ptr_num_nodes = num_nodes_copied;
                }

                if( out_it != end )
                {
                    std::fill( out_it, end, _this_t::UNDEFINED_INDEX );
                }

                if( ( num_nodes_copied > size_t{ 0 } ) ||
                    ( !found_items ) )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    template< typename NodeIndexIter >
    NodeStore::status_t NodeStore::nodeIndices(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::node_set_id_t const node_set_id,
        NodeStore::size_type* SIXTRL_RESTRICT
            ptr_num_nodes ) const SIXTRL_NOEXCEPT
    {
        namespace st  = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;
        using size_t  = _this_t::size_type;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        auto ptr_set = this->ptrNodeSetBase( lock, node_set_id );

        if( ptr_set != nullptr )
        {
            SIXTRL_ASSERT( node_set_id != _this_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( static_cast< size_t >( node_set_id ) <
                           this->m_stored_node_sets.size() );
            SIXTRL_ASSERT( this->m_stored_node_sets[
                node_set_id ].get() == ptr_set );

            if( ( ptr_set->numNodes( lock ) > size_t{ 0 } ) &&
                ( std::distance( begin, end ) > std::ptrdiff_t{ 0 } ) )
            {
                bool found_items = false;

                auto in_it  = ptr_set->nodeIndicesBegin( lock );
                auto in_end = ptr_set->nodeIndicesEnd( lock );

                NodeIndexIter out_it = begin;

                for( ; in_it != in_end ; ++in_it )
                {
                    if( this->isNodeAttachedToSet( lock, *in_it, node_set_id ) )
                    {
                        found_items = true;

                        if( out_it != end )
                        {
                            *out_it++ = *in_it;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                size_t const num_nodes_copied = static_cast< size_t >(
                    std::distance( begin, out_it ) );

                if( ptr_num_nodes != nullptr )
                {
                    *ptr_num_nodes = num_nodes_copied;
                }

                if( out_it != end )
                {
                    std::fill( out_it, end, _this_t::UNDEFINED_INDEX );
                }

                if( ( num_nodes_copied > size_t{ 0 } ) ||
                    ( !found_items ) )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeStore::isNodeAvailable(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->isNodeAvailable( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::node_id_t const* NodeStore::ptrNodeId(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->ptrNodeId( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::node_info_base_t const* NodeStore::ptrNodeInfoBase(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->ptrNodeInfoBase( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::node_info_base_t* NodeStore::ptrNodeInfoBase(
        NodeStore::node_index_t const node_index )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->ptrNodeInfoBase( lock, node_index );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeStore::hasNodeSets() const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->hasNodeSets( lock );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numNodeSets() const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->numNodeSets( lock );
    }

    SIXTRL_INLINE bool NodeStore::hasNodeSet(
        NodeStore::node_set_id_t const set_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->hasNodeSet( lock, set_id );
    }

    SIXTRL_INLINE bool NodeStore::hasNodeSet( SIXTRL_CXX_NAMESPACE::NodeSetBase&
        SIXTRL_RESTRICT_REF node_set ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->hasNodeSet( lock, node_set );
    }

    SIXTRL_INLINE NodeStore::node_set_id_t NodeStore::addNodeSet(
        NodeStore::ptr_stored_node_set_t&& ptr_node_set )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->addNodeSet( lock, std::move( ptr_node_set ) );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::removeNodeSet(
        NodeStore::node_set_id_t const set_id )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->removeNodeSet( lock, set_id );
    }

    SIXTRL_INLINE NodeStore::node_set_id_t NodeStore::nodeSetId(
        SIXTRL_CXX_NAMESPACE::NodeSetBase&
            SIXTRL_RESTRICT_REF node_set ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->nodeSetId( lock, node_set );
    }

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeSetBase*
    NodeStore::ptrNodeSetBase( NodeStore::node_set_id_t const node_set_id )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->ptrNodeSetBase( lock, node_set_id );
    }

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeSetBase const*
    NodeStore::ptrNodeSetBase(
        NodeStore::node_set_id_t const node_set_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->ptrNodeSetBase( lock, node_set_id );
    }

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeSetBase&
    NodeStore::nodeSetBase( NodeStore::node_set_id_t const node_set_id )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->nodeSetBase( lock, node_set_id );
    }

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeSetBase const&
    NodeStore::nodeSetBase( NodeStore::node_set_id_t const node_set_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->nodeSetBase( lock, node_set_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::addNode(
        NodeStore::ptr_stored_node_info_t&& ptr_stored_node_info )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->addNode( lock, std::move( ptr_stored_node_info ) );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::removeNode(
        NodeStore::node_index_t const node_index )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->doRemoveNode( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::attachNodeToSet(
        NodeStore::node_index_t const node_index,
        NodeStore::node_set_id_t const set_id )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->attachNodeToSet( lock, node_index, set_id );
    }

    SIXTRL_INLINE NodeStore::status_t
    NodeStore::attachAllArchitectureNodesToSet(
        NodeStore::arch_id_t const arch_id,
        NodeStore::node_set_id_t const set_id )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->attachAllArchitectureNodesToSet( lock, arch_id, set_id );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::detachNodeFromSet(
        NodeStore::node_index_t const node_index,
        NodeStore::node_set_id_t const node_set_id )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->detachNodeFromSet( lock, node_index, node_set_id );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::detachAllNodesFromSet(
        NodeStore::node_set_id_t const node_set_id )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->detachAllNodesFromSet( lock, node_set_id );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::detachNodeFromAllSets(
        NodeStore::node_index_t const node_index )
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->detachNodeFromAllSets( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numSetsAttachedToNode(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->numSetsAttachedToNode( lock, node_index );
    }

    SIXTRL_INLINE bool NodeStore::isNodeAttachedToAnySet(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->isNodeAttachedToAnySet( lock, node_index );
    }

    SIXTRL_INLINE bool NodeStore::isNodeAttachedToSet(
        NodeStore::node_index_t const node_index,
        NodeStore::node_set_id_t const node_set_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->isNodeAttachedToSet( lock, node_index, node_set_id );
    }

    SIXTRL_INLINE bool NodeStore::canNodeBeSelectedBySet(
        NodeStore::node_index_t const node_index,
        NodeStore::node_set_id_t const node_set_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->canNodeBeSelectedBySet( lock, node_index, node_set_id );
    }

    SIXTRL_INLINE bool NodeStore::isNodeSelectedBySet(
        NodeStore::node_index_t const node_index,
        NodeStore::node_set_id_t const set_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->isNodeSelectedBySet( lock, node_index, set_id );
    }

    SIXTRL_INLINE bool NodeStore::isNodeSelectedByAnySet(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->isNodeSelectedByAnySet( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numSelectingSetsForNode(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->numSelectingSetsForNode( lock, node_index );
    }

    SIXTRL_INLINE bool NodeStore::isNodeDefaultForSet(
        NodeStore::node_index_t const node_index,
        NodeStore::node_set_id_t const node_set_id ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->isNodeDefaultForSet( lock, node_index, node_set_id );
    }

    SIXTRL_INLINE bool NodeStore::isNodeDefaultForAnySet(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->isNodeDefaultForAnySet( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numSetsHavingNodeAsDefault(
        NodeStore::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        NodeStore::lock_t const lock( *this->lockable() );
        return this->numSetsHavingNodeAsDefault( lock, index );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::addNode(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::ptr_stored_node_info_t&& ptr_stored_node_info )
    {
        return this->doAddNode( lock, std::move( ptr_stored_node_info ) );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::removeNode(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_index_t const node_index )
    {
        return this->doRemoveNode( lock, node_index );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE void NodeStore::clear()
    {
        NodeStore::lock_t const lock( *this->lockable() );
        NodeStore::status_t const status = this->doClear( lock );
        SIXTRL_ASSERT( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );
        ( void ) status;
    }

    SIXTRL_INLINE void NodeStore::clear(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        NodeStore::status_t const status = this->doClear( lock );
        SIXTRL_ASSERT( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );
        ( void ) status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::sync_id_value_t
    NodeStore::syncIdValue() const SIXTRL_NOEXCEPT
    {
        return this->m_sync_id.load();
    }

    SIXTRL_INLINE NodeStore::sync_id_t const&
    NodeStore::syncId() const SIXTRL_NOEXCEPT
    {
        return this->m_sync_id;
    }

    SIXTRL_INLINE bool NodeStore::isSyncWith( NodeStore::sync_id_t const&
        SIXTRL_RESTRICT_REF sid ) const SIXTRL_NOEXCEPT
    {
        return ( this->m_sync_id.load() == sid.load() );
    }

    SIXTRL_INLINE bool NodeStore::isSyncWith( NodeStore::sync_id_value_t const
        sync_id_value ) const SIXTRL_NOEXCEPT
    {
        return ( this->m_sync_id.load() == sync_id_value );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeStore::checkLock( NodeStore::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( lock.owns_lock() ) &&
                 ( lock.mutex() == this->lockable() ) );
    }

    SIXTRL_INLINE void NodeStore::checkLockAndThrowOnError(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        if( !this->checkLock( lock ) )
        {
            throw std::runtime_error( "requires properly locked mutex" );
        }
    }

    SIXTRL_INLINE NodeStore::lockable_t*
    NodeStore::lockable() const SIXTRL_NOEXCEPT
    {
        return &this->m_lockable;
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_CXX_HPP__ */

/* end: sixtracklib/common/control/node_store.hpp */
