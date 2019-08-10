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
        #include <set>
        #include <unordered_set>
        #include <vector>
        #include <utility>
#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/architecture/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

namespace SIXTRL_CXX_NAMESPACE
{
    class NodeStore;

    class NodeCollectionBase
    {
        using size_type        = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using arch_id_t        = SIXTRL_CXX_NAMESPACE::arch_id_t;
        using node_index_t     = SIXTRL_CXX_NAMESPACE::node_index_t;
        using node_id_t        = SIXTRL_CXX_NAMESPACE::NodeId;
        using platform_id_t    = SIXTRL_CXX_NAMESPACE::node_platform_id_t;
        using device_id_t      = SIXTRL_CXX_NAMESPACE::node_device_id_t;
        using status_t         = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using id_str_format_t  = SIXTRL_CXX_NAMESPACE::node_id_str_fmt_t;

        static constexpr arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static constexpr node_index_t UNDEFINED_INDEX =
            SIXTRL_CXX_NAMESPACE::NODE_UNDEFINED_INDEX;

        static constexpr platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static constexpr device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static constexpr id_str_format_t DEFAULT_ID_STR_FORMAT =
            SIXTRL_CXX_NAMESPACE::NODE_ID_STR_FORMAT_DEFAULT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool archId() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type numNodes() const;

        SIXTRL_HOST_FN node_index_t minNodeIndex() const;
        SIXTRL_HOST_FN node_index_t maxNodeIndex() const;
        SIXTRL_HOST_FN node_index_t nodeIndex( size_type const nn ) const;

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

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool isNodeAvailable(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN bool isNodeSelected(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN bool isDefaultNode(
            node_index_t const node_index ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool isNodeAvailable(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isNodeSelected(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isDefaultNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN id_str_format_t nodeIdStrFormat() const;
        SIXTRL_HOST_FN status_t setNodeIdStrFormat( id_str_format_t const fmt );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN id_str_format_t nodeIdStrFormat(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setNodeIdStrFormat(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            id_str_format_t const fmt );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t const* nodeIndicesBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* nodeIndicesEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* nodeIdsBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* nodeIdsEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN char const** nodeIdStrBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN char const** nodeIdStrEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canSelectNodes() const;
        SIXTRL_HOST_FN bool requiresSelectNodes() const;

        SIXTRL_HOST_FN size_type minNumSelectableNodes() const;
        SIXTRL_HOST_FN size_type maxNumSelectableNodes() const;
        SIXTRL_HOST_FN size_type numSelectedNodes() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool canSelectNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool requiresSelectNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type minNumSelectableNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type maxNumSelectableNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numSelectedNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canHaveDefaultNodes() const;
        SIXTRL_HOST_FN bool requiresDefaultNodes() const;

        SIXTRL_HOST_FN size_type minNumDefaultNodes() const;
        SIXTRL_HOST_FN size_type maxNumDefaultNodes() const;
        SIXTRL_HOST_FN size_type numDefaultNodes() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool canHaveDefaultNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool requiresDefaultNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type minNumDefaultNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type maxNumDefaultNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numDefaultNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_store_t const& nodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_store_t& nodeStore() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool checkLock(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual ~NodeCollectionBase() = default;

        protected:

        using node_indices_buffer_t  = std::vector< node_index_t >;
        using node_indices_map_t     = std::vector< node_index_t >;
        using node_id_buffer_t       = std::vector< node_id_t >;
        using node_id_str_t          = std::vector< char >;
        using node_id_str_buffer_t   = std::vector< node_id_str_t >;
        using c_node_id_str_buffer_t = std::vector< char const* >;
        using node_index_set_t       = std::unordered_set< node_index_t >;

        SIXTRL_HOST_FN NodeCollectionBase( arch_id_t const arch_id,
            NodeStore& SIXTRL_RESTRICT_REF node_store,
            id_str_format_t const node_id_str_format = DEFAULT_ID_STR_FORMAT );

        SIXTRL_HOST_FN NodeCollectionBase(
            NodeCollectionBase const& orig ) = default;

        SIXTRL_HOST_FN NodeCollectionBase(
            NodeCollectionBase&& orig ) = default;

        SIXTRL_HOST_FN NodeCollectionBase& operator=(
            NodeCollectionBase const& orig ) = default;

        SIXTRL_HOST_FN NodeCollectionBase& operator=(
            NodeCollectionBase&& orig ) = default;

        /* ---------------------------------------------------------------- */

        virtual status_t doPrintNodeInfo(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const;

        virtual status_t doSelectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        virtual status_t doUnselectNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        virtual status_t doAddDefaultNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        virtual status_t doRemoveDefaultNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        virtual status_t doAddNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const num_node_indices,
            node_index_t const* SIXTRL_RESTRICT node_indices_begin,
            node_index_t* SIXTRL_RESTRICT_REF ptr_num_nodes_added );

        virtual status_t doRemoveNodes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const num_node_indices,
            node_index_t const* SIXTRL_RESTRICT node_indices_begin,
            node_index_t* SIXTRL_RESTRICT_REF ptr_num_nodes_added );

        /* ----------------------------------------------------------------- */

        void doSetArchId( arch_id_t const arch_id ) SIXTRL_NOEXCEPT;

        void doSetMinNumSelectableNodes(
            size_type const min_num_selectable_nodes ) SIXTRL_NOEXCEPT;

        void doSetMaxNumSelectableNodes(
            size_type const max_num_selectable_nodes ) SIXTRL_NOEXCEPT;

        void doSetMinNumDefaultNodes(
            size_type const min_num_default_nodes ) SIXTRL_NOEXCEPT;

        void doSetMaxNumDefaultNodes(
            size_type const max_num_default_nodes ) SIXTRL_NOEXCEPT;

        private:

        node_indices_buffer_t       m_node_indices;
        node_indices_map_t          m_node_indices_map;
        node_id_buffer_t            m_node_ids;
        node_index_set_t            m_selected_indices;
        node_index_set_t            m_default_indices;
        node_id_str_buffer_t        m_node_id_str_store;
        c_node_id_str_buffer_t      m_node_id_str_view;

        NodeStore&                  m_node_store;
        id_str_format_t             m_id_str_format;

        size_type                   m_min_num_selectable_nodes;
        size_type                   m_max_num_selectable_nodes;
        size_type                   m_min_num_default_nodes;
        size_type                   m_max_num_default_nodes;

        arch_id_t                   m_arch_id;
    };

    class NodeStore
    {
        public:

        using status_t                = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using size_type               = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using node_index_t            = SIXTRL_CXX_NAMESPACE::node_index_t;
        using node_info_base_t        = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        using node_id_t               = SIXTRL_CXX_NAMESPACE::NodeId;
        using controller_base_t       = SIXTRL_CXX_NAMESPACE::ControllerBase;
        using node_str_role_t         = SIXTRL_CXX_NAMESPACE::node_str_role_t;
        using arch_id_t               = SIXTRL_CXX_NAMESPACE::arch_id_t;
        using platform_id_t           = SIXTRL_CXX_NAMESPACE::node_platform_id_t;
        using device_id_t             = SIXTRL_CXX_NAMESPACE::node_device_id_t;
        using ptr_stored_node_info_t  = std::unique_ptr< node_info_base_t >;

        using lockable_t              = std::mutex;
        using lock_t                  = std::unique_lock< lockable_t >;

        using sync_id_value_t         = uint64_t;
        using sync_id_t               = std::atomic< sync_id_value_t >;

        static SIXTRL_CONSTEXPR_OR_CONST node_str_role_t NODE_ID_STR =
            SIXTRL_CXX_NAMESPACE::NODE_STR_ROLE_ID;

        static SIXTRL_CONSTEXPR_OR_CONST node_str_role_t NODE_UNIQUE_ID_STR =
            SIXTRL_CXX_NAMESPACE::NODE_STR_ROLE_UNIQUE_ID;

        static SIXTRL_CONSTEXPR_OR_CONST arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static SIXTRL_CONSTEXPR_OR_CONST platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static SIXTRL_CONSTEXPR_OR_CONST device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static SIXTRL_CONSTEXPR_OR_CONST node_index_t UNDEFINED_INDEX =
            SIXTRL_CXX_NAMESPACE::NODE_UNDEFINED_INDEX;

        /* ***************************************************************** */

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
            char const* SIXTRL_RESTRICT platform_name ) const;

        SIXTRL_HOST_FN bool hasPlatform(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id,
            char const* SIXTRL_RESTRICT platform_name ) const;

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
            ControllerBase const& controller ) const;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN size_type numControllers(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numControllers(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            ControllerBase const& controller ) const SIXTRL_NOEXCEPT;

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

        SIXTRL_HOST_FN size_type numNodes(
            ControllerBase const& SIXTRL_RESTRICT_REF ctrl ) const;

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
            lock_t const& SIXTRL_RESTRICT_REF lock, ControllerBase const&
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
            ControllerBase const& SIXTRL_RESTRICT_REF controller,
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
            ControllerBase const& SIXTRL_RESTRICT_REF controller,
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

        SIXTRL_HOST_FN node_index_t addNode(
            ptr_stored_node_info_t&& ptr_stored_node_info );

        SIXTRL_HOST_FN status_t attachNodeToController(
            node_index_t const node_index,
            ControllerBase& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t attachAllArchitectureNodesToController(
             ControllerBase& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t detachNodeFromController(
            node_index_t const node_index,
            ControllerBase const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t detachAllNodesFromController(
            ControllerBase const& SIXTRL_RESTRICT_REF controller );

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
            ControllerBase const& SIXTRL_RESTRICT_REF controller ) const;

        SIXTRL_HOST_FN status_t markNodeAsSelectedByController(
            node_index_t const node_index,
            ControllerBase const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t unselectNodeForController(
            node_index_t const node_index,
            ControllerBase const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN bool isNodeSelectedByController(
            node_index_t const node_index,
            ControllerBase const& SIXTRL_RESTRICT_REF controller ) const;

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
            ControllerBase& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t attachAllArchitectureNodesToController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            ControllerBase& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t detachNodeFromController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            ControllerBase const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t detachAllNodesFromController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            ControllerBase const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t detachAllNodesByArchitecture(
            lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id );

        SIXTRL_HOST_FN status_t detachNodeFromAllControllers(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        SIXTRL_HOST_FN size_type numControllersAttachedToNode(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isNodeAttachedToAnyController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isNodeAttachedToController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index, ControllerBase const&
                SIXTRL_RESTRICT_REF controller ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t markNodeAsSelectedByController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            ControllerBase const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN status_t unselectNodeForController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            ControllerBase const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN bool isNodeSelectedByController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            ControllerBase const& SIXTRL_RESTRICT_REF controller
            ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isNodeSelectedByAnyController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

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

        SIXTRL_HOST_FN sync_id_t const& syncId() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN sync_id_value_t syncIdValue() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSyncWith( sync_id_t const& SIXTRL_RESTRICT_REF
            other_sync_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSyncWith(
            sync_id_value_t const other_sync_id ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN bool checkLock(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void checkLockAndThrowOnError(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        protected:

        using ptr_ctrl_t           = ControllerBase const*;
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

        using arch_platform_to_plfm_name_t =
            std::map< arch_platform_pair_t, std::string >;

        using arch_plfm_name_to_platform_id_t =
            std::map< arch_platform_name_pair_t, platform_id_t >;

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
            ControllerBase& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN virtual status_t doDetachNodeFromController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            ControllerBase const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN virtual status_t doSelectNodeByController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            ControllerBase const& SIXTRL_RESTRICT_REF controller );

        SIXTRL_HOST_FN virtual status_t doUnselectNodeForController(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index,
            ControllerBase const& SIXTRL_RESTRICT_REF controller );

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
            ControllerBase& SIXTRL_RESTRICT_REF controller );

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

    /* --------------------------------------------------------------------- */

        SIXTRL_HOST_FN sync_id_value_t doIncrementSyncId() SIXTRL_NOEXCEPT;


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
        sync_id_t                       m_sync_id;
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
   #include "sixtracklib/common/control/controller_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE bool NodeCollectionBase::archId() const SIXTRL_NOEXCEPT
    {
        return this->m_arch_id;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::numNodes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->m_node_indices.size();
    }

    SIXTRL_INLINE NodeCollectionBase::node_index_t
    NodeCollectionBase::minNodeIndex() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );

        return ( !this->m_node_indices.empty() )
            ? this->m_node_indices.front() : _this_t::UNDEFINED_INDEX;
    }

    SIXTRL_INLINE NodeCollectionBase::node_index_t
    NodeCollectionBase::maxNodeIndex() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );

        return ( !this->m_node_indices.empty() )
            ? this->m_node_indices.back() : _this_t::UNDEFINED_INDEX;
    }

    SIXTRL_INLINE NodeCollectionBase::node_index_t
    NodeCollectionBase::nodeIndex( size_type const nn ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );

        return ( this->m_node_indices.size() > nn )
            ? this->m_node_indices[ nn ] : _this_t::UNDEFINED_INDEX;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE NodeCollectionBase::size_type NodeCollectionBase::numNodes(
        NodeCollectionBase::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) ) ? this->m_node_indices.size()
            : SIXTRL_CXX_NAMESPACE::NodeCollectionBase::size_type{ 0 };
    }

    SIXTRL_INLINE NodeCollectionBase::node_index_t
    NodeCollectionBase::minNodeIndex( NodeCollectionBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) ) ? this->m_node_indices.front()
            : SIXTRL_CXX_NAMESPACE::NodeCollectionBase::UNDEFINED_INDEX;
    }

    SIXTRL_INLINE NodeCollectionBase::node_index_t
    NodeCollectionBase::maxNodeIndex( NodeCollectionBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) ) ? this->m_node_indices.back()
            : SIXTRL_CXX_NAMESPACE::NodeCollectionBase::UNDEFINED_INDEX;
    }

    SIXTRL_INLINE NodeCollectionBase::node_index_t
    NodeCollectionBase::nodeIndex(
        NodeCollectionBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeCollectionBase::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;

        return ( ( this->checkLock( lock ) ) &&
                 ( this->m_node_indices.size() > nn ) )
            ? this->m_node_indices[ nn ] : _this_t::UNDEFINED_INDEX;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeCollectionBase::isNodeAvailable(
        NodeCollectionBase::node_index_t const node_index ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->isNodeAvailable( lock, node_index );
    }

    SIXTRL_INLINE bool NodeCollectionBase::isNodeSelected(
        NodeCollectionBase::node_index_t const node_index ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->isNodeSelected( lock, node_index );
    }

    SIXTRL_INLINE bool NodeCollectionBase::isDefaultNode(
        NodeCollectionBase::node_index_t const node_index ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->isDefaultNode( lock, node_index );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    SIXTRL_INLINE bool NodeCollectionBase::isNodeAvailable(
        NodeCollectionBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeCollectionBase::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        return ( ( node_index != _this_t::UNDEFINED_INDEX ) &&
                 ( this->checkLock( lock ) ) &&
                 ( this->m_node_indices.front() <= node_index ) &&
                 ( this->m_node_indices.back()  >= node_index ) &&
                 ( std::find( this->m_node_indices.begin(),
                    this->m_node_indices.end(), node_index ) !=
                        this->m_node_indices.end() ) );
    }

    SIXTRL_INLINE bool NodeCollectionBase::isNodeSelected(
        NodeCollectionBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeCollectionBase::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        return ( ( node_index != _this_t::UNDEFINED_INDEX ) &&
                 ( this->checkLock( lock ) ) &&
                 ( !this->m_selected_indices.empty() ) &&
                 ( this->m_node_indices.front() <= node_index ) &&
                 ( this->m_node_indices.back()  >= node_index ) &&
                 ( this->m_selected_indices.find( node_index ) !=
                   this->m_selected_indices.end() ) );
    }

    SIXTRL_INLINE bool NodeCollectionBase::isDefaultNode(
        NodeCollectionBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeCollectionBase::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        return ( ( node_index != _this_t::UNDEFINED_INDEX ) &&
                 ( this->checkLock( lock ) ) &&
                 ( !this->m_default_indices.empty() ) &&
                 ( this->m_node_indices.front() <= node_index ) &&
                 ( this->m_node_indices.back()  >= node_index ) &&
                 ( this->m_default_indices.find( node_index ) !=
                   this->m_default_indices.end() ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeCollectionBase::id_str_format_t
    NodeCollectionBase::nodeIdStrFormat() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->m_id_str_format;
    }

    SIXTRL_INLINE NodeCollectionBase::status_t
    NodeCollectionBase::setNodeIdStrFormat( id_str_format_t const fmt )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->setNodeIdStrFormat( lock, fmt );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeCollectionBase::node_index_t const*
    NodeCollectionBase::nodeIndicesBegin( NodeCollectionBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        return ( this->checkLock( lock ) )
            ? this->m_node_indices.data() : nullptr;
    }

    SIXTRL_INLINE NodeCollectionBase::node_index_t const*
    NodeCollectionBase::nodeIndicesEnd( NodeCollectionBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::node_index_t const* ptr_end = nullptr;

        if( this->checkLock( lock ) )
        {
            ptr_end = this->m_node_indices.data();

            if( !this->m_node_indices.empty() )
            {
                std::advance( ptr_end, this->m_node_indices.begin() );
            }
        }

        return ptr_end;
    }

    SIXTRL_INLINE NodeCollectionBase::node_id_t const*
    NodeCollectionBase::nodeIdsBegin( NodeCollectionBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        return ( this->checkLock( lock ) ) ? this->m_node_ids.data() : nullptr;
    }

    SIXTRL_INLINE NodeCollectionBase::node_id_t const*
    NodeCollectionBase::nodeIdsEnd( NodeCollectionBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::node_id_t const* ptr_end = nullptr;

        if( this->checkLock( lock ) )
        {
            ptr_end = this->m_node_ids.data();

            if( !this->m_node_ids.empty() )
            {
                std::advance( ptr_end, this->m_node_ids.begin() );
            }
        }

        return ptr_end;
    }

    SIXTRL_INLINE char const** NodeCollectionBase::nodeIdStrBegin(
        NodeCollectionBase::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? this->m_node_id_str_view.data() : nullptr;
    }

    SIXTRL_INLINE char const** NodeCollectionBase::nodeIdStrEnd(
        NodeCollectionBase::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        char const** ptr_end = nullptr;

        if( this->checkLock( lock ) )
        {
            ptr_end = this->this->m_node_id_str_view.data();

            if( ( ptr_end != nullptr ) &&
                ( !this->m_node_id_str_view.empty() ) )
            {
                std::advance( ptr_end, this->m_node_id_str_view.size() );
            }
        }

        return ptr_end;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeCollectionBase::canSelectNodes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->canSelectNodes( lock );
    }

    SIXTRL_INLINE bool NodeCollectionBase::requiresSelectNodes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->requiresSelectNodes( lock );
    }

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::minNumSelectableNodes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->minNumSelectableNodes( lock );
    }

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::maxNumSelectableNodes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->maxNumSelectableNodes( lock );
    }

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::numSelectedNodes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->numSelectedNodes( lock );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    SIXTRL_INLINE bool NodeCollectionBase::canSelectNodes(
        NodeCollectionBase::lock_t const& SIXTRL_RESTRICT_REF
            lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->checkLock( lock ) ) &&
                 ( this->m_min_num_selectable_nodes <
                   this->m_max_num_selectable_nodes ) &&
                 ( this->m_selected_indices.size() <
                   this->m_max_num_selectable_nodes ) );
    }

    SIXTRL_INLINE bool NodeCollectionBase::requiresSelectNodes(
        NodeCollectionBase::lock_t const& SIXTRL_RESTRICT_REF
            lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        return ( ( this->checkLock( lock ) ) &&
                 ( this->m_min_num_selectable_nodes >
                    _this_t::size_type{ 0 } ) );
    }

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::minNumSelectableNodes( NodeCollectionBase::lock_t
        const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        return ( this->checkLock( lock ) )
            ? this->m_min_num_selectable_nodes : _this_t::size_type{ 0 };
    }

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::maxNumSelectableNodes( NodeCollectionBase::lock_t
        const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        return ( this->checkLock( lock ) )
            ? this->m_max_num_selectable_nodes : _this_t::size_type{ 0 };
    }

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::numSelectedNodes( NodeCollectionBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        return ( this->checkLock( lock ) )
            ? this->m_selected_indices.size() : _this_t::size_type{ 0 };
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeCollectionBase::canHaveDefaultNodes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->canHaveDefaultNodes( lock );
    }

    SIXTRL_INLINE bool NodeCollectionBase::requiresDefaultNodes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->requiresDefaultNodes( lock );
    }

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::minNumDefaultNodes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->minNumDefaultNodes( lock );

    }

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::maxNumDefaultNodes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->maxNumDefaultNodes( lock );
    }

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::numDefaultNodes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        _this_t::lock_t const lock( *this->nodeStore().lockable() );
        return this->numDefaultNodes( lock );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    SIXTRL_INLINE bool NodeCollectionBase::canHaveDefaultNodes(
        NodeCollectionBase::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->checkLock( lock ) ) &&
                 ( this->m_min_num_default_nodes <
                   this->m_max_num_default_nodes ) &&
                 ( this->m_default_indices.size() <
                   this->m_max_num_default_nodes ) );
    }

    SIXTRL_INLINE bool NodeCollectionBase::requiresDefaultNodes(
        NodeCollectionBase::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        return ( ( this->checkLock( lock ) ) &&
                 ( this->m_min_num_default_nodes >
                    _this_t::size_type{ 0 } ) );
    }

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::minNumDefaultNodes( NodeCollectionBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        return ( this->checkLock( lock ) )
            ? this->m_min_num_default_nodes : _this_t::size_type{ 0 };
    }

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::maxNumDefaultNodes( NodeCollectionBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        return ( this->checkLock( lock ) )
            ? this->m_max_num_default_nodes : _this_t::size_type{ 0 };
    }

    SIXTRL_INLINE NodeCollectionBase::size_type
    NodeCollectionBase::numDefaultNodes( NodeCollectionBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeCollectionBase;
        return ( this->checkLock( lock ) )
            ? this->m_default_indices.size() : _this_t::size_type{ 0 };
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeCollectionBase::node_store_t const&
    NodeCollectionBase::nodeStore() const SIXTRL_NOEXCEPT
    {
        return this->m_node_store;
    }

    SIXTRL_INLINE NodeCollectionBase::node_store_t&
    NodeCollectionBase::nodeStore() SIXTRL_NOEXCEPT
    {
        return this->m_node_store;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeCollectionBase::checkLock( NodeCollectionBase::lock_t
        const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return this->m_node_store.checkLock( lock );
    }

    SIXTRL_INLINE NodeCollectionBase::lockable_t*
    NodeCollectionBase::lockable() const SIXTRL_NOEXCEPT
    {
        return this->m_node_store.lockable();
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeCollectionBase::NodeCollectionBase(
        NodeCollectionBase::arch_id_t const arch_id,
        NodeStore& SIXTRL_RESTRICT_REF node_store,
        NodeCollectionBase::id_str_format_t const node_id_str_format ) :
        m_node_indices(), m_node_indices_map(), m_node_ids(),
        m_selected_indices(), m_default_indices(), m_node_id_str_store(),
        m_node_id_str_view(), m_node_store( node_store ),
        m_id_str_format( node_id_str_format ),
        m_min_num_selectable_nodes( 0u ), m_max_num_selectable_nodes( 0u ),
        m_min_num_default_nodes( 0u ), m_max_num_default_nodes( 0u ),
        m_arch_id( arch_id )
    {

    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE void NodeCollectionBase::doSetArchId(
        NodeCollectionBase::arch_id_t const arch_id ) SIXTRL_NOEXCEPT
    {
        this->m_arch_id = arch_id;
    }

    SIXTRL_INLINE void NodeCollectionBase::doSetMinNumSelectableNodes(
        NodeCollectionBase::size_type const min_num_sel_nodes ) SIXTRL_NOEXCEPT
    {
        this->m_min_num_selectable_nodes = min_num_sel_nodes;
    }

    SIXTRL_INLINE void NodeCollectionBase::doSetMaxNumSelectableNodes(
        NodeCollectionBase::size_type const max_num_sel_nodes ) SIXTRL_NOEXCEPT
    {
        this->m_max_num_selectable_nodes = max_num_sel_nodes;
    }

    SIXTRL_INLINE void NodeCollectionBase::doSetMinNumDefaultNodes(
        NodeCollectionBase::size_type const min_num_def_nodes ) SIXTRL_NOEXCEPT
    {
        this->m_min_num_default_nodes = min_num_def_nodes;
    }

    SIXTRL_INLINE void NodeCollectionBase::doSetMaxNumDefaultNodes(
        NodeCollectionBase::size_type const max_num_def_nodes ) SIXTRL_NOEXCEPT
    {
        this->m_max_num_default_nodes = max_num_def_nodes;
    }

    /* ===================================================================== */

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


    SIXTRL_INLINE NodeStore::size_type NodeStore::numControllers() const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->numControllers( lock );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numControllers(
        NodeStore::arch_id_t const arch_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->numControllers( lock, arch_id );
    }

    SIXTRL_INLINE bool NodeStore::hasController(
        NodeStore::controller_base_t const& controller ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->hasController( lock, controller );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::size_type NodeStore::numArchitectures() const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->numArchitectures( lock );
    }

    SIXTRL_INLINE bool NodeStore::hasArchitecture(
        NodeStore::arch_id_t const arch_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->hasArchitecture( lock, arch_id );
    }

    template< typename ArchIdIter >
    SIXTRL_INLINE NodeStore::status_t NodeStore::architectureIds(
        ArchIdIter begin, ArchIdIter end,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_archs ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->architectureIds( lock, begin, end, ptr_num_archs );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeStore::size_type NodeStore::numArchitectures(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->m_arch_to_platforms.size();
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

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeStore::hasPlatform(
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->hasPlatform( lock, arch_id, platform_id );
    }

    SIXTRL_INLINE bool NodeStore::hasPlatform( arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->hasPlatform( lock, arch_id, platform_name );
    }

    SIXTRL_INLINE bool NodeStore::hasPlatform(
        NodeStore::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT platform_name ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->hasPlatform( lock, arch_id, std::string{ platform_name } );
    }

    SIXTRL_INLINE NodeStore::platform_id_t NodeStore::platformIdByName(
        NodeStore::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->platformIdByName( lock, arch_id, platform_name );
    }

    SIXTRL_INLINE NodeStore::platform_id_t NodeStore::platformIdByName(
        NodeStore::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT platform_name ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->platformIdByName( lock, arch_id, platform_name );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numPlatforms(
        NodeStore::arch_id_t const arch_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->numPlatforms( lock, arch_id );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::addPlatformNameMapping(
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        std::string const& SIXTRL_RESTRICT_REF platform_name )
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->addPlatformNameMapping(
            lock, arch_id, platform_id, platform_name );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::addPlatformNameMapping(
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id,
        char const* SIXTRL_RESTRICT platform_name )
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->addPlatformNameMapping(
            lock, arch_id, platform_id, platform_name );
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE bool NodeStore::hasPlatform(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        NodeStore::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT platform_name ) const
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
        NodeStore::node_id_t const& SIXTRL_RESTRICT_REF node_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
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
        NodeStore::lock_t lock( *this->lockable() );
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
        NodeStore::lock_t lock( *this->lockable() );
        return this->findNodeIndex( lock, arch_id, platform_id, device_id );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::node_info_base_t const* SIXTRL_RESTRICT ptr_node_info ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->findNodeIndex( lock, ptr_node_info );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        char const* SIXTRL_RESTRICT str,
        NodeStore::node_str_role_t const str_role ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->findNodeIndex(
            lock, ::NS(ARCHITECTURE_ILLEGAL), str, str_role );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT str,
        NodeStore::node_str_role_t const str_role ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->findNodeIndex( lock, arch_id, str, str_role );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        std::string const& SIXTRL_RESTRICT_REF str,
        NodeStore::node_str_role_t const str_role ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->findNodeIndex(
            lock, ::NS(ARCHITECTURE_ILLEGAL), str.c_str(), str_role );
    }

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::findNodeIndex(
        NodeStore::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF str,
        NodeStore::node_str_role_t const str_role ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
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
        NodeStore::lock_t lock( *this->lockable() );
        return this->totalNumNodes( lock );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numNodes(
        NodeStore::arch_id_t const arch_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->numNodes( lock, arch_id );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numNodes(
        NodeStore::arch_id_t const arch_id,
        NodeStore::platform_id_t const platform_id ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->numNodes( lock, arch_id, platform_id );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numNodes(
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF ctrl ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
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
        return this->nodeIndices( lock, begin, end, ptr_num_nodes );
    }

    template< typename NodeIndexIter >
    SIXTRL_INLINE NodeStore::status_t NodeStore::nodeIndices(
        NodeIndexIter begin, NodeIndexIter end,
        NodeStore::arch_id_t const arch_id,
        NodeStore::size_type* SIXTRL_RESTRICT ptr_num_nodes ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
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
        return this->nodeIndices( lock, begin, end, ctrl, ptr_num_nodes );
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

                auto in_it = this->storedNodeInfoBegin( lock );
                auto in_end = this->storedNodeInfoBegin( lock );
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

                auto in_it  = this->storedNodeInfoBegin( lock );
                auto in_end = this->storedNodeInfoEnd( lock );

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

                auto in_it  = this->storedNodeInfoBegin( lock );
                auto in_end = this->storedNodeInfoEnd( lock );

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
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller,
        NodeStore::size_type* SIXTRL_RESTRICT
            ptr_num_nodes ) const SIXTRL_NOEXCEPT
    {
        namespace st  = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeStore;
        using size_t  = _this_t::size_type;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _this_t::arch_id_t const arch_id = controller.archId();

        if( ( this->checkLock( lock ) ) && ( arch_id != _this_t::ARCH_ILLEGAL ) )
        {
            auto ctrl_it = this->m_ctrl_to_node_indices.find( &controller );
            if( ( ctrl_it != this->m_ctrl_to_node_indices.end() ) &&
                ( std::distance( begin, end ) > std::ptrdiff_t{ 0 } ) )
            {
                bool found_items = false;

                auto in_it  = ctrl_it->second.begin();
                auto in_end = ctrl_it->second.end();

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
        NodeStore::lock_t lock( *this->lockable() );
        return this->isNodeAvailable( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::node_id_t const* NodeStore::ptrNodeId(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->ptrNodeId( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::node_info_base_t const* NodeStore::ptrNodeInfoBase(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->ptrNodeInfoBase( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::node_info_base_t* NodeStore::ptrNodeInfoBase(
        NodeStore::node_index_t const node_index )
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->ptrNodeInfoBase( lock, node_index );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::node_index_t NodeStore::addNode(
        NodeStore::ptr_stored_node_info_t&& ptr_stored_node_info )
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->addNode( lock, std::move( ptr_stored_node_info ) );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::attachNodeToController(
        NodeStore::node_index_t const node_index,
        NodeStore::controller_base_t& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->attachNodeToController( lock, node_index, controller );
    }

    SIXTRL_INLINE NodeStore::status_t
    NodeStore::attachAllArchitectureNodesToController(
        NodeStore::controller_base_t& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->attachAllArchitectureNodesToController(
            lock, controller );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::detachNodeFromController(
        NodeStore::node_index_t const node_index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->detachNodeFromController( lock, node_index, controller );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::detachAllNodesFromController(
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->detachAllNodesFromController( lock, controller );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::detachAllNodesByArchitecture(
        NodeStore::arch_id_t const arch_id )
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->detachAllNodesByArchitecture( lock, arch_id );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::detachNodeFromAllControllers(
        NodeStore::node_index_t const node_index )
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->detachNodeFromAllControllers( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numControllersAttachedToNode(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->numControllersAttachedToNode( lock, node_index );
    }

    SIXTRL_INLINE bool NodeStore::isNodeAttachedToAnyController(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->isNodeAttachedToAnyController( lock, node_index );
    }

    SIXTRL_INLINE bool NodeStore::isNodeAttachedToController(
        NodeStore::node_index_t const node_index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF ctrl ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->isNodeAttachedToController( lock, node_index, ctrl );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::markNodeAsSelectedByController(
        NodeStore::node_index_t const node_index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->markNodeAsSelectedByController(
            lock, node_index, controller );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::unselectNodeForController(
        NodeStore::node_index_t const node_index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF controller )
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->unselectNodeForController( lock, node_index, controller );
    }

    SIXTRL_INLINE bool NodeStore::isNodeSelectedByController(
        NodeStore::node_index_t const node_index,
        NodeStore::controller_base_t const& SIXTRL_RESTRICT_REF ctrl ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->isNodeSelectedByController(
            lock, node_index, ctrl );
    }

    SIXTRL_INLINE bool NodeStore::isNodeSelectedByAnyController(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->isNodeSelectedByAnyController( lock, node_index );
    }

    SIXTRL_INLINE NodeStore::size_type NodeStore::numSelectingControllersForNode(
        NodeStore::node_index_t const node_index ) const
    {
        NodeStore::lock_t lock( *this->lockable() );
        return this->numSelectingControllersForNode( lock, node_index );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE void NodeStore::clear()
    {
        NodeStore::lock_t lock( *this->lockable() );
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
        return this->doRebuild( lock );
    }

    SIXTRL_INLINE NodeStore::status_t NodeStore::rebuild(
        NodeStore::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        return this->doRebuild( lock );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore::sync_id_t const&
    NodeStore::syncId() const SIXTRL_NOEXCEPT
    {
        return this->m_sync_id;
    }

    SIXTRL_INLINE NodeStore::sync_id_value_t
    NodeStore::syncIdValue() const SIXTRL_NOEXCEPT
    {
        return this->m_sync_id.load();
    }

    SIXTRL_INLINE bool NodeStore::isSyncWith( NodeStore::sync_id_t const&
        SIXTRL_RESTRICT_REF other_sync_id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeStore;
        _this_t::sync_id_value_t const my_sync_id = this->m_sync_id.load();
        return ( my_sync_id == other_sync_id.load() );
    }

    SIXTRL_INLINE bool NodeStore::isSyncWith( NodeStore::sync_id_value_t
        const other_sync_id ) const SIXTRL_NOEXCEPT
    {
        return ( other_sync_id == this->m_sync_id.load() );
    }

    SIXTRL_INLINE NodeStore::sync_id_value_t
    NodeStore::doIncrementSyncId() SIXTRL_NOEXCEPT
    {
        return this->m_sync_id++;
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
