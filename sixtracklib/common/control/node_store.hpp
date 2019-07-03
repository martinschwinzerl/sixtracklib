#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_CXX_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_CXX_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )
#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
        #include <cstddef>
        #include <cstdlib>
        #include <cstring>
        #include <cstdio>
        #include <memory>
        #include <map>
        #include <thread>
        #include <mutex>
        #include <stdexcept>
        #include <set>
        #include <vector>
        #include <utility>
#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/arch_info.h"
    #include "sixtracklib/common/control/controller_base.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/node_info_base.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/arch_info.hpp"
    #include "sixtracklib/common/control/controller_base.hpp"
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/node_info_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class NodeStore
    {
        public:

        using status_t                = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using size_type               = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using node_index_t            = SIXTRL_CXX_NAMESPACE::node_index_t;
        using node_info_base_t        = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        using ptr_stored_node_info_t  = std::unique_ptr< node_info_base_t >;
        using node_id_t               = node_info_base_t::node_id_t;
        using arch_id_t               = node_info_base_t::arch_id_t;
        using platform_id_t           = node_info_base_t::platform_id_t;
        using device_id_t             = node_info_base_t::device_id_t;
        using controll_base_t         = node_info_base_t::controller_base_t;

        using lockable_t              = std::mutex;
        using lock_t                  = std::unique_lock< lockable_t >;

        SIXTRL_HOST_FN NodeStore();

        SIXTRL_HOST_FN NodeStore(
            NodeStore const& SIXTRL_RESTRICT_REF other ) = default;

        SIXTRL_HOST_FN NodeStore( NodeStore&& other ) = default;

        SIXTRL_HOST_FN NodeStore& operator=(
            NodeStore const& SIXTRL_RESTRICT_REF other ) = default;

        SIXTRL_HOST_FN NodeStore& operator=(
            NodeStore&& other ) = default;

        SIXTRL_HOST_FN virtual ~NodeStore() = default;

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

        SIXTRL_HOST_FN bool hasArchitecture( arch_id_t const arch_id,
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

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

        SIXTRL_HOST_FN bool hasPlatform( arch_id_t const arch_id,
                std::string const& SIXTRL_RESTRICT_REF platform_name ) const;

        SIXTRL_HOST_FN bool hasPlatform( arch_id_t const arch_id,
                char const* SIXTRL_RESTRICT platform_name ) const;

        SIXTRL_HOST_FN platform_id_t platformIdByName( arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name ) const;

        SIXTRL_HOST_FN platform_id_t platformIdByName( arch_id_t const arch_id,
            char const* SIXTRL_RESTRICT platform_name ) const;

        SIXTRL_HOST_FN size_type numPlatforms( arch_id_t const arch_id ) const;

        SIXTRL_HOST_FN status_t addPlatformNameMapping(
            arch_id_t const arch_id,
            platform_id_t const platform_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name );

        SIXTRL_HOST_FN status_t addPlatformNameMapping(
            arch_id_t const arch_id,
            platform_id_t const platform_id,
            char const* SIXTRL_RESTRICT platform_name );

        SIXTRL_HOST_FN bool hasNode(
            node_id_t const& SIXTRL_RESTRICT_REF node_id ) const;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool hasPlatform(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id,
            platform_id_t const platform_id )const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasPlatform(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN platform_id_t platformIdByName(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN platform_id_t platformIdByName(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id,
            char const* SIXTRL_RESTRICT platform_name ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasPlatform(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id,
            char const* SIXTRL_RESTRICT platform_name ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numPlatforms(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t addPlatformNameMapping(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            platform_id_t const platform_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name );

        SIXTRL_HOST_FN status_t addPlatformNameMapping(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            platform_id_t const platform_id,
            char const* SIXTRL_RESTRICT platform_name );

        SIXTRL_HOST_FN bool hasNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_id_t const& SIXTRL_RESTRICT_REF node_id
        ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type numControllers() const;

        SIXTRL_HOST_FN size_type numControllers( arch_id_t const id ) const;

        SIXTRL_HOST_FN bool hasController(
            controller_base_t const& controller ) const;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN size_type numControllers(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numControllers( arch_id_t const arch_id,
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasController( controller_base_t const& controller,
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            node_id_t const& SIXTRL_RESTRICT_REF node_id ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            arch_id_t const arch_id, platform_id_t const platform_id,
            device_id_t const device_id ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            node_info_base_t const* SIXTRL_RESTRICT ptr_node_info ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            char const* SIXTRL_RESTRICT str ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex( arch_id_t const arch_id,
            char const* SIXTRL_RESTRICT str ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            std::string const& SIXTRL_RESTRICT_REF str ) const;

        SIXTRL_HOST_FN node_index_t findNodeIndex( arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF str) const;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_id_t const& SIXTRL_RESTRICT_REF nid ) const SIXTRL_NOEXCEPT;

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
            char const* SIXTRL_RESTRICT str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id,
            char const* SIXTRL_RESTRICT str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            std::string const& SIXTRL_RESTRICT_REF str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t findNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF str ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type totalNumNodes() const;

        SIXTRL_HOST_FN size_type numNodes( arch_id_t const arch_id ) const;

        SIXTRL_HOST_FN size_type numNodes( arch_id_t const arch_id,
            platform_id_t const platform_id ) const;

        SIXTRL_HOST_FN size_type numNodes(
            controller_base_t const& SIXTRL_RESTRICT_REF ctrl ) const;

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
            lock_t const& SIXTRL_RESTRICT_REF lock, controller_base_t const&
                SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT;

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
            controller_base_t const& SIXTRL_RESTRICT_REF controller,
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
            controller_base_t const& SIXTRL_RESTRICT_REF controller,
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
            node_index_t const node_index ) const SIXTRL_RESTRICT;

        SIXTRL_HOST_FN node_id_t const* ptrNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_RESTRICT;

        SIXTRL_HOST_FN node_info_base_t const* ptrNodeInfoBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_RESTRICT;

        SIXTRL_HOST_FN node_info_base_t* ptrNodeInfoBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) SIXTRL_RESTRICT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t addNode(
            ptr_stored_node_info_t&& ptr_stored_node_info );

        SIXTRL_HOST_FN status_t attachNodeToController(
            node_index_t const node_index,
            controller_base_t& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t attachAllArchitectureNodesToController(
             controller_base_t& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t detachNodeFromController(
            node_index_t const node_index,
            controller_base_t const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t detachAllNodesFromController(
            controller_base_t const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t detachAllNodesByArchitecture(
            arch_id_t const arch_id );

        SIXTRL_HOST_FN status_t detachNodeFromAllControllers(
            node_index_t const node_index );

        SIXTRL_HOST_FN size_type numControllersAttachedToNode(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN bool isNodeAttachedToAnyController(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN bool isNodeAttachedToController(
            node_index_t const node_index,
            controller_base_t const& SIXTRL_RESTRICT_REF controller ) const;

        SIXTRL_HOST_FN status_t markNodeAsSelectedByController(
            node_index_t const node_index,
            controller_base_t const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t unselectNodeForController(
            node_index_t const node_index,
            controller_base_t const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN bool isNodeSelectedByController(
            node_index_t const node_index,
            controller_base_t const& SIXTRL_RESTRICT_REF controller ) const;

        SIXTRL_HOST_FN bool isNodeSelectedByAnyController(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN size_type numSelectingControllersForNode(
            node_index_t const node_index ) const;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN node_index_t addNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            ptr_stored_node_info_t&& ptr_stored_node_info );

        SIXTRL_HOST_FN status_t attachNodeToController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            controller_base_t& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t attachAllArchitectureNodesToController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            controller_base_t& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t detachNodeFromController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            controller_base_t const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t detachAllNodesFromController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            controller_base_t const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t detachAllNodesByArchitecture(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id );

        SIXTRL_HOST_FN status_t detachNodeFromAllControllers(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN size_type numControllersAttachedToNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isNodeAttachedToAnyController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isNodeAttachedToController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index, controller_base_t const&
                SIXTRL_RESTRICT_REF controller ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t markNodeAsSelectedByController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            controller_base_t const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t unselectNodeForController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            controller_base_t const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN size_type numSelectingControllersForNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN void clear();
        SIXTRL_HOST_FN void clear(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN status_t rebuild();
        SIXTRL_HOST_FN status_t rebuild(
            lock_t const& SIXTRL_RESTRICT_REF lock );

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN bool checkLock(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void checkLockAndThrowOnError(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        protected:

        using ptr_ctrl_t           = controller_base_t const*;
        using platforms_set_t      = std::set< platform_id_t >;
        using devices_set_t        = std::set< device_id_t >;
        using ptr_ctrls_set_t      = std::set< ptr_ctrl_t >;
        using nindices_set_t       = std::set< node_index_t >;

        using arch_platform_pair_t = std::pair< arch_id_t, platform_id_t >;
        using arch_platform_name_pair_t = std::pair< arch_id_t, std::string >;

        using arch_to_platforms_t = std::map< arch_id_t, platforms_set_t >;
        using arch_to_ptr_ctrls_t = std::map< arch_id_t, ptr_ctrls_set_t >;

        using arch_platform_to_devices_t =
            std::map< arch_platform_pair_t, devices_set_t >;

        using arch_plfm_name_to_platform_id_t =
            std::map< arch_platform_name_pair_t, platform_id_t >;

        using arch_platform_to_devices_t =
            std::map< arch_platform_pair_t, devices_set_t >;

        using node_id_to_node_index_t = std::map< node_id_t, node_index_t >;
        using ptr_ctrl_to_nindices_t = std::map< ptr_ctrl_t, nindices_set_t >;

        using nindex_to_ptr_ctrls_t =
            std::map< node_index_t, ptr_ctrls_set_t >;

        using stored_node_info_buffer_t =
            std::vector< ptr_stored_node_info_t >;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN virtual node_index_t doAddNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            ptr_stored_node_info_t&& ptr_stored_node_info );

        SIXTRL_HOST_FN virtual status_t doAttachNodeToController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            controller_base_t& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN virtual status_t doDetachNodeFromController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            controller_base_t const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN virtual status_t doSelectNodeByController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            controller_base_t const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN virtual status_t doUnselectNodeForController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            controller_base_t const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN virtual status_t doRebuild(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN virtual status_t doClear(
            lock_t const& SIXTRL_RESTRICT_REF lock );

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

        SIXTRL_HOST_FN status_t doAddController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            controller_base_t& SIXTRL_RESTRICT_REF controller );

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN stored_node_info_buffer_t::const_iterator
        storedNodeInfoBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN stored_node_info_buffer_t::const_iterator
        storedNodeInfoEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN stored_node_info_buffer_t::iterator storedNodeInfoBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN stored_node_info_buffer_t::iterator storedNodeInfoEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN platform_id_t doGetPlatformIdByArchIdAndPlatformName(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name );

        SIXTRL_HOST_FN status_t doSetArchPlatformNameToIdMapping(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name,
            platform_id_t const platform_id );

        SIXTRL_HOST_FN status_t doRemoveArchPlatformNameToIdMapping(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name );

        private:

        arch_to_platforms_t             m_arch_to_platforms;
        arch_to_ptr_ctrls_t             m_arch_to_ctrls;
        arch_platform_to_devices_t      m_arch_platform_to_devices;
        arch_platform_to_plfm_name_t    m_arch_platform_to_platform_name;
        arch_plfm_name_to_platform_id_t m_arch_platform_name_to_platform_id;

        node_id_to_node_index_t         m_node_id_to_node_index;

        ptr_ctrl_to_nindices_t          m_ctrl_to_node_indices;
        nindex_to_ptr_ctrls_t           m_node_index_to_attached_ctrls;
        nindex_to_ptr_ctrls_t           m_node_index_to_selecting_ctrls;

        stored_node_info_buffer_t       m_stored_node_infos;
        mutable lockable_t              m_lockable;
    };

    SIXTRL_HOST_FN NodeStore& NodeStore_get();
    SIXTRL_HOST_FN NodeStore* NodeStore_get_ptr();
    SIXTRL_HOST_FN NodeStore const* NodeStore_get_const_ptr();
}

typedef SIXTRL_CXX_NAMESPACE::NodeStore NS(NodeStore);
typedef SIXTRL_CXX_NAMESPACE::NodeStore::lock_t NS(NodeStoreLock);

#else

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

typedef void NS(NodeStore);
typedef void NS(NodeStoreLock);

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) && \
         !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ ) */

/* ************************************************************************* */
/* ******  Implementation of inline and template member functions    ******* */
/* ************************************************************************* */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeStore& NodeStore_get()
    {
        static SIXTRL_CXX_NAMESPACE::NodeStore node_store;
        return node_store;
    }

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeStore* NodeStore_get_ptr()
    {
        return &SIXTRL_CXX_NAMESPACE::NodeStore_get();
    }

    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::NodeStore* NodeStore_get_const_ptr()
    {
        return &SIXTRL_CXX_NAMESPACE::NodeStore_get();
    }

    /* ********************************************************************* */


    SIXTRL_INLINE NodeStore::size_type NodeStore::numControllers() const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->numControllers( lock );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numControllers(
        NodeStore::arch_id_t const arch_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->numControllers( lock, arch_id );
    }

    SIXTRL_INLINE bool NodeStore::hasController(
        NodeStore::controller_base_t const& controller ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->hasController( lock, controller );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::size_type NodeStore::numArchitectures() const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->numArchitectures( lock );
    }

    SIXTRL_INLINE bool NodeStore::hasArchitecture(
        NodeStore::arch_id_t const arch_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->hasArchitecture( lock, arch_id );
    }

    template< typename ArchIdIter >
    SIXTRL_INLINE NodeStore::status_t NodeStore::architectureIds(
        ArchIdIter begin, ArchIdIter end,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_archs ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->architectureIds( lock, begin, end, ptr_num_archs );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeStore::size_type NodeStore::numArchitectures(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->m_arch_id_.size();
    }

    SIXTRL_INLINE bool NodeStore::hasArchitecture(
        NodeStore::arch_id_t const arch_id,
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return ( ( arch_id != SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL ) &&
                 ( this->m_arch_id_to_node_indices.find( arch_id ) !=
                   this->m_arch_id_to_node_indices.end() ) );
    }

    template< typename ArchIdIter >
    NodeStore::status_t NodeStore::architectureIds(
        ArchIdIter begin, ArchIdIter end,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_archs
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
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

                auto in_it  = this->archNodeIndexMapBegin( lock );
                auto in_end = this->archNodeIndexMapEnd( lock );

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

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeStore::hasPlatform(
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->hasPlatform( lock, arch_id, platform_id );
    }

    SIXTRL_INLINE bool NodeStore::hasPlatform( arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->hasPlatform( lock, arch_id, platform_name );
    }

    SIXTRL_INLINE bool NodeStore::hasPlatform(
        NodeStore::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT platform_name ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->hasPlatform( lock, arch_id, std::string{ platform_name } );
    }

    SIXTRL_INLINE NodeStore::platform_id_t NodeStore::platformIdByName(
        NodeStore::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->platformIdByName( lock, arch_id, platform_name );
    }

    SIXTRL_INLINE NodeStore::platform_id_t NodeStore::platformIdByName(
        NodeStore::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT platform_name ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->platformIdByName( lock, arch_id, platform_name );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numPlatforms(
        NodeStore::arch_id_t const arch_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->numPlatforms( lock, arch_id );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::addPlatformNameMapping(
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name )
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->addPlatformNameMapping(
            lock, arch_id, platform_id, platform_name );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::addPlatformNameMapping(
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        char const* SIXTRL_RESTRICT platform_name )
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->addPlatformNameMapping(
            lock, arch_id, platform_id, platform_name );
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE bool NodeStore::hasPlatform(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT platform_name ) const SIXTRL_NOEXCEPT
    {
        return this->hasPlatform( lock, arch_id, std::string{ platform_name } );
    }

    SIXTRL_INLINE NodeStore::platform_id_t NodeStore::platformIdByName(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT platform_name ) const
    {
        return ( ( platform_name != nullptr ) &&
                 ( std::strlen( platform_name ) > NodeStore::size_type{ 0 } ) )
            ? this->platformIdByName(
                lock, arch_id, std::string{ platform_name } )
            : NodeStore::ILLEGAL_PLATFORM_ID;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeStore::hasNode(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_id_t const& SIXTRL_RESTRICT_REF node_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->hasNode( lock, node_id );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE bool NodeStore::hasNode(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::node_id_t const& SIXTRL_RESTRICT_REF node_id ) const
    {
        return ( ( node_id.valid() ) && ( this->checkLock( lock ) ) &&
            ( this->findNodeIndex( node_id ) != NodeStore::UNDEFINED_INDEX ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::node_id_t const& SIXTRL_RESTRICT_REF node_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->findNodeIndex( lock, node_id );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        NodeStore::device_id_t const device_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->findNodeIndex( lock, arch_id, platform_id, device_id );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::node_info_base_t const* SIXTRL_RESTRICT ptr_node_info ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->findNodeIndex( lock, ptr_node_info );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
            char const* SIXTRL_RESTRICT str ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->findNodeIndex( lock,
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL, str );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT str ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->findNodeIndex( lock, arch_id, str );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        std::string const& SIXTRL_RESTRICT_REF str ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->findNodeIndex( lock,
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL, str.c_str() );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF str ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->findNodeIndex( lock, arch_id, str.c_str() );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

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
        char const* SIXTRL_RESTRICT str ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->findNodeIndex( lock,
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL, str );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        std::string const& SIXTRL_RESTRICT_REF str,
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->findNodeIndex( lock,
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL, str.c_str() );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF str,
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->findNodeIndex( lock, arch_id, str.c_str() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::size_type NodeStore::totalNumNodes() const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->totalNumNodes( lock, node_id );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numNodes(
        NodeStore::arch_id_t const arch_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->numNodes( lock, arch_id );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numNodes(
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->numNodes( lock, arch_id, platform_id );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numNodes(
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF ctrl ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->numNodes( lock, ctrl );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeStore::size_type NodeStore::totalNumNodes(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->m_stored_node_infos.size();
    }

    /* --------------------------------------------------------------------- */

    template< typename NodeIndexIter >
    SIXTRL_INLINE NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->nodeIndices( lock, begin, end, ptr_num_nodes );
    }

    template< typename NodeIndexIter >
    SIXTRL_INLINE NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::arch_id_t const arch_id,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->nodeIndices( lock, begin, end, arch_id, ptr_num_nodes );
    }

    template< typename NodeIndexIter >
    SIXTRL_INLINE NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->nodeIndices(
            lock, begin, end, arch_id, platform_id, ptr_num_nodes );
    }

    template< typename NodeIndexIter >
    SIXTRL_INLINE NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF ctrl,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->nodeIndices( lock, begin, end, ctrl, ptr_num_nodes );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< typename NodeIndexIter >
    NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes,
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using status_t  = NodeStore::status_t;
        using size_t    = NodeStore::size_type;
        using index_t   = NodeStore::node_index_t;
        using node_id_t = NodeStore::node_id_t;
        using diff_t    = std::ptrdiff_t;

        status_t status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        size_t const num_nodes = this->totalNumNodes( lock );

        if( ( this->checkLock( lock ) ) && ( num_nodes > size_t{ 0 } ) )
        {
            if( std::distance( begin, end ) > diff_t{ 0 } )
            {
                bool found_items = false;

                auto in_it = this->storedNodeInfoBegin( lock );
                auto in_end = this->storedNodeInfoBegin( lock );
                NodeIndexIter out_it = begin;

                index_t index = index_t{ 0 }

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
                    std::fill( out_it, end, node_id_t::UNDEFINED_INDEX );
                }

                if( ( num_nodes_copied > size_t{ 0 } ) || ( !found_items ) )
                {
                    status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    template< typename NodeIndexIter >
    NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::arch_id_t const arch_id,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes,
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using status_t  = NodeStore::status_t;
        using size_t    = NodeStore::size_type;
        using node_id_t = NodeStore::node_id_t;

         status_t status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->checkLock( lock ) ) &&
            ( arch_id != node_id_t::ARCH_ILLEGAL ) )
        {
            if( std::distance( begin, end ) > std::ptrdiff_t{ 0 } )
            {
                bool found_items = false;

                auto in_it  = this->storedNodeInfoBegin( lock );
                auto in_end = this->storedNodeInfoEnd( lock );

                index_t index = index_t{ 0 };
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
                    std::fill( out_it, end, node_id_t::UNDEFINED_INDEX );
                }

                if( ( num_nodes_copied > size_t{ 0 } ) ||
                    ( !found_items ) )
                {
                    status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    template< typename NodeIndexIter >
    NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes,
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using status_t  = NodeStore::status_t;
        using size_t    = NodeStore::size_type;
        using node_id_t = NodeStore::node_id_t;

         status_t status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->checkLock( lock ) ) &&
            ( arch_id != node_id_t::ARCH_ILLEGAL ) &&
            ( platform_id != node_id_t::ILLEGAL_PLATFORM_ID ) )
        {
            if( std::distance( begin, end ) > std::ptrdiff_t{ 0 } )
            {
                bool found_items = false;

                auto in_it  = this->storedNodeInfoBegin( lock );
                auto in_end = this->storedNodeInfoEnd( lock );

                index_t index = index_t{ 0 };
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
                    std::fill( out_it, end, node_id_t::UNDEFINED_INDEX );
                }

                if( ( num_nodes_copied > size_t{ 0 } ) ||
                    ( !found_items ) )
                {
                    status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    template< typename NodeIndexIter >
    NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes,
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using status_t  = NodeStore::status_t;
        using size_t    = NodeStore::size_type;
        using node_id_t = NodeStore::node_id_t;

        status_t status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        NodeStore::arch_id_t const arch_id = controller.archId();

        if( ( this->checkLock( lock ) ) && ( arch_id != node_id_t::ARCH_ILLEGAL ) )
        {
            auto ctrl_it = this->m_controller_to_node_indices.find(
                &controller );

            if( ( ctrl_it != this->m_controller_to_node_indices.end() ) &&
                ( std::distance( begin, end ) > std::ptrdiff_t{ 0 } ) )
            {
                bool found_items = false;

                auto in_it  = it->second.begin();
                auto in_end = it->second.end();

                NodeIndexIter out_it = begin;

                for( ; in_it != in_end ; ++in_it )
                {
                    auto ptr_node_info =
                        this->ptrNodeInfoBase( lock, *in_it );

                    if( ( ptr_node_info != nullptr ) &&
                        ( ptr_node_info->archId() == arch_id ) )
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
                    std::fill( out_it, end, node_id_t::UNDEFINED_INDEX );
                }

                if( ( num_nodes_copied > size_t{ 0 } ) ||
                    ( !found_items ) )
                {
                    status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeStore::isNodeAvailable(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->isNodeAvailable( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::node_id_t const* NodeStore::ptrNodeId(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->ptrNodeId( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::node_info_base_t const* NodeStore::ptrNodeInfoBase(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->ptrNodeInfoBase( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::node_info_base_t* NodeStore::ptrNodeInfoBase(
        NodeStore::node_index_t const node_index )
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->ptrNodeInfoBase( lock, node_index );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::addNode(
        NodeStore::ptr_stored_node_info_t&& ptr_stored_node_info )
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->addNode( lock, std::move( ptr_stored_node_info ) );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::attachNodeToController(
        NodeStore::node_index_t const node_index,
        NodeStore::controller_base_t& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->attachNodetoController( lock, node_index, controller );
    }

    SIXTRL_INLINE NodeStore::status_t
    NodeStore::attachAllArchitectureNodesToController(
        NodeStore::controller_base_t& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->attachAllArchitectureNodesToController(
            lock, controller );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::detachNodeFromController(
        NodeStore::node_index_t const node_index,
        NodeStore::controller_base_t& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->detachNodeFromController( lock, node_index, controller );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::detachAllNodesFromController(
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->detachAllNodesFromController( lock, controller );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::detachAllNodesByArchitecture(
        NodeStore::arch_id_t const arch_id )
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->detachAllNodesByArchitecture( lock, arch_id );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::detachNodeFromAllControllers(
        NodeStore::node_index_t const node_index )
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->detachNodeFromAllControllers( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numControllersAttachedToNode(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->numControllersAttachedToNode( lock, node_index );
    }

    SIXTRL_INLINE bool NodeStore::isNodeAttachedToAnyController(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStoe::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->isNodeAttachedToAnyController( lock, node_index );
    }

    SIXTRL_INLINE bool NodeStore::isNodeAttachedToController(
        NodeStore::node_index_t const node_index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF ctrl ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->isNodeAttachedToController( lock, node_index, ctrl );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::markNodeAsSelectedByController(
        NodeStore::node_index_t const node_index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->markNodeAsSelectedByController(
            lock, node_index, controller );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::unselectNodeForController(
        NodeStore::node_index_t const node_index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->unselectNodeForController( lock, node_index, controller );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numSelectingControllersForNode(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->numSelectingControllersForNode( lock, node_index );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE void NodeStore::clear()
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
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

    SIXTRL_INLINE NodeStore::status_t NodeStore::rebuild()
    {
        NodeStore::lock_t lock( *this->lockable() );
        this->checkLockAndThrowOnError( lock );
        return this->doRebuild( lock );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::rebuild(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->doRebuild( lock );
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

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::stored_node_info_buffer_t::const_iterator
    NodeStore::storedNodeInfoBegin( NodeStore::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->m_stored_node_infos.begin();
    }

    SIXTRL_INLINE NodeStore::stored_node_info_buffer_t::const_iterator
    NodeStore::storedNodeInfoEnd( NodeStore::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->m_stored_node_infos.end();
    }

    SIXTRL_INLINE NodeStore::stored_node_info_buffer_t::iterator
    NodeStore::storedNodeInfoBegin( NodeStore::lock_t const&
        SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->m_stored_node_infos.begin();
    }

    SIXTRL_INLINE NodeStore::stored_node_info_buffer_t::iterator
    NodeStore::storedNodeInfoEnd( NodeStore::lock_t const&
        SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->m_stored_node_infos.end();
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_STORE_CXX_HPP__ */

/* end: sixtracklib/common/control/node_store.hpp */
