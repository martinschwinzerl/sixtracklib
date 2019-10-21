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
    class NodeSetBase;
    class NodeSetSingle;
    class NodeInfoBase;

    class NodeControllerBase : public SIXTRL_CXX_NAMESPACE::ControllerBase
    {
        private:

        using _controller_base_t = ControllerBase;

        public:

        using node_id_t         = SIXTRL_CXX_NAMESPACE::NodeId;
        using node_info_base_t  = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        using node_store_t      = SIXTRL_CXX_NAMESPACE::NodeStore;
        using node_set_base_t   = SIXTRL_CXX_NAMESPACE::NodeSetBase;
        using node_set_t        = SIXTRL_CXX_NAMESPACE::NodeSetSingle;
        using node_str_role_t   = SIXTRL_CXX_NAMESPACE::node_str_role_t;
        using platform_id_t     = SIXTRL_CXX_NAMESPACE::node_platform_id_t;
        using device_id_t       = SIXTRL_CXX_NAMESPACE::node_device_id_t;
        using node_set_id_t     = SIXTRL_CXX_NAMESPACE::node_set_id_t;
        using node_index_t      = SIXTRL_CXX_NAMESPACE::node_index_t;
        using id_str_format_t   = node_id_t::format_t;
        using c_node_id_t       = node_id_t::c_api_t;

        using ptr_node_store_t  = std::unique_ptr< node_store_t >;
        using node_lockable_t   = std::mutex;
        using node_lock_t       = std::unique_lock< node_lockable_t >;

        static SIXTRL_CONSTEXPR_OR_CONST platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static SIXTRL_CONSTEXPR_OR_CONST device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static SIXTRL_CONSTEXPR_OR_CONST node_set_id_t ILLEGAL_NODE_SET_ID =
            node_set_id_t{ 0xffffffff };

        static SIXTRL_CONSTEXPR_OR_CONST node_index_t UNDEFINED_INDEX =
            SIXTRL_CXX_NAMESPACE::NODE_UNDEFINED_INDEX;

        static SIXTRL_CONSTEXPR_OR_CONST node_str_role_t NODE_ID_STR =
            SIXTRL_CXX_NAMESPACE::NODE_STR_ROLE_ID;

        static SIXTRL_CONSTEXPR_OR_CONST node_str_role_t NODE_UNIQUE_ID_STR =
            SIXTRL_CXX_NAMESPACE::NODE_STR_ROLE_UNIQUE_ID;

        static SIXTRL_CONSTEXPR_OR_CONST id_str_format_t DEFAULT_ID_STR_FORMAT =
            SIXTRL_CXX_NAMESPACE::NODE_ID_STR_FORMAT_DEFAULT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasNodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool ownsNodeStore() const;

        SIXTRL_HOST_FN NodeStore const* ptrConstNodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN NodeStore const& constNodeStore() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool ownsNodeStore( node_lock_t const&
            SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasNodeSet()  const;

        SIXTRL_HOST_FN NodeSetSingle const* ptrConstNodeSetBase() const;
        SIXTRL_HOST_FN NodeSetSingle const& constNodeSetBase() const;

        SIXTRL_HOST_FN node_set_id_t nodeSetId() const;
        SIXTRL_HOST_FN size_type numNodes() const;
        SIXTRL_HOST_FN node_index_t minNodeIndex() const;
        SIXTRL_HOST_FN node_index_t maxNodeIndex() const;
        SIXTRL_HOST_FN node_index_t nodeIndex( size_type const nn ) const;

        SIXTRL_HOST_FN node_id_t nodeIdByNodeIndex(
            node_index_t const node_index ) const;

        SIXTRL_HOST_FN c_node_id_t const* ptrCNodeId(
            size_type const nn ) const;

        SIXTRL_HOST_FN c_node_id_t const* ptrCNodeIdByNodeIndex(
            node_index_t const node_index ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool hasNodeSet( node_lock_t const&
            SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_set_id_t nodeSetId(
            SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numNodes( node_lock_t const&
            SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t minNodeIndex( node_lock_t const&
            SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t maxNodeIndex( node_lock_t const&
            SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            size_type const nn ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const& nodeId(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            size_type const nn ) const;

        SIXTRL_HOST_FN node_id_t const& nodeIdByNodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            node_index_t const ) const;

        SIXTRL_HOST_FN c_node_id_t const* ptrCNodeIdByNodeIndex(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            node_index_t const node_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_node_id_t const* ptrCNodeId(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            size_type const nn ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* nodeIndicesBegin( node_lock_t const&
            SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t const* nodeIndicesEnd( node_lock_t const&
            SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool usesAutoSelect() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        supportsChangingSelectedNode() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
        supportsDirectlyChangingSelectedNode() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool supportsUnselectingNode() const SIXTRL_NOEXCEPT;

        template< typename... Args >
        SIXTRL_HOST_FN node_index_t findNodeIndex( Args&&... args ) const;

        SIXTRL_HOST_FN bool isAvailable( node_index_t const index ) const;

        SIXTRL_HOST_FN bool hasSelectedNode() const;
        SIXTRL_HOST_FN bool isSelected(  node_index_t const index ) const;
        SIXTRL_HOST_FN bool canSelectNode( node_index_t const index ) const;
        SIXTRL_HOST_FN status_t selectNode( node_index_t const index );

        SIXTRL_HOST_FN bool isDefault(   node_index_t const index ) const;

        SIXTRL_HOST_FN bool canChangeSelectedNodeTo(
            node_index_t const new_node_index ) const;

        SIXTRL_HOST_FN bool canChangeSelectedNode(
            node_index_t const current_node_index,
            node_index_t const new_node_index ) const;

        SIXTRL_HOST_FN status_t changeSelectedNodeTo(
            node_index_t const new_node_index );

        SIXTRL_HOST_FN status_t changeSelectedNode(
            node_index_t const current_node_index,
            node_index_t const new_node_index );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool isAvailable(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            node_index_t const index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasSelectedNode( node_lock_t const&
            SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSelected(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            node_index_t const index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool canSelectNode(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            node_index_t const index ) const;

        SIXTRL_HOST_FN status_t selectNode(
            node_lock_t& SIXTRL_RESTRICT_REF node_lock,
            node_index_t const index );

        SIXTRL_HOST_FN bool isDefault(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            node_index_t const index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool canChangeSelectedNodeTo(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            node_index_t const new_node_index ) const;

        SIXTRL_HOST_FN bool canChangeSelectedNode(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            node_index_t const current_node_index,
            node_index_t const new_node_index ) const;

        SIXTRL_HOST_FN status_t changeSelectedNodeTo(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            node_index_t const new_node_index );

        SIXTRL_HOST_FN status_t changeSelectedNode(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
            node_index_t const current_node_index,
            node_index_t const new_node_index );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool isSyncWithNodeSet() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_t syncWithNodeSet();

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN status_t syncWithNodeSet(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_lockable_t* nodeLockable() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool nodeCheckLock( node_lock_t const&
            SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void nodeCheckLockThrowIfError( node_lock_t const&
            SIXTRL_RESTRICT_REF node_lock ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual ~NodeControllerBase() = default;

        protected:

        SIXTRL_HOST_FN NodeControllerBase( arch_id_t const arch_id,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN NodeControllerBase(
            NodeControllerBase const& other ) = default;

        SIXTRL_HOST_FN NodeControllerBase(
            NodeControllerBase&& other ) = default;

        SIXTRL_HOST_FN NodeControllerBase& operator=(
            NodeControllerBase const& rhs ) = default;

        SIXTRL_HOST_FN NodeControllerBase& operator=(
            NodeControllerBase&& rhs ) = default;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN NodeStore* ptrNodeStore(
            node_lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN NodeStore& nodeStore(
            node_lock_t const& SIXTRL_RESTRICT_REF lock );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN NodeSetBase* ptrNodeSetBase(
            node_lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN NodeSetBase& nodeSetBase(
            node_lock_t const& SIXTRL_RESTRICT_REF lock );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN virtual void doClear(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock ) override;

        SIXTRL_HOST_FN virtual status_t doSyncWithNodeSet(
            node_lock_t const& SIXTRL_RESTRICT_REF node_lock );

        SIXTRL_HOST_FN virtual bool doCheckIfCanChangeAllKernelsWithKey(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            kernel_config_key_t& SIXTRL_RESTRICT_REF new_key ) const override;

        SIXTRL_HOST_FN virtual status_t doChangeAllKernelsWithKey(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            kernel_config_key_t& SIXTRL_RESTRICT_REF new_key )  override;

         /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t doInitNodeStore(
            node_lock_t const& SIXTRL_RESTRICT node_lock,
            node_store_t* SIXTRL_RESTRICT ext_node_store );

        SIXTRL_HOST_FN status_t doInitNodeStore(
            node_lock_t const& SIXTRL_RESTRICT node_lock,
            ptr_node_store_t&& node_store );

        SIXTRL_HOST_FN status_t doInitNodeSet(
            node_lock_t const& SIXTRL_RESTRICT node_lock,
            node_set_id_t const node_set_id );

        private:

        ptr_node_store_t   m_my_own_node_store;
        node_store_t*      m_ptr_node_store;
        node_set_t*        m_ptr_node_set;
        sync_id_value_t    m_expected_node_set_sync_id;
        node_set_id_t      m_node_set_id;
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

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
        #include <stdexcept>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_info.hpp"
    #include "sixtracklib/common/control/node_store.hpp"
    #include "sixtracklib/common/control/node_set.hpp"
    #include "sixtracklib/common/control/kernel_set.hpp"
    #include "sixtracklib/common/control/kernel_config_key.hpp"
    #include "sixtracklib/common/control/kernel_config_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE NodeControllerBase const* asNodeController(
        ControllerBase const* SIXTRL_RESTRICT base_controller )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        if( ( base_controller != nullptr ) &&
            ( base_controller->usesNodes() ) )
        {
            return static_cast<
                st::NodeControllerBase const* >( base_controller );
        }

        return nullptr;
    }

    SIXTRL_INLINE NodeControllerBase* asNodeController(
        ControllerBase* SIXTRL_RESTRICT base_controller )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _node_ctrl_t = st::NodeControllerBase;
        using _base_ctrl_t = st::ControllerBase;

        return const_cast< _node_ctrl_t* >( st::asNodeController(
            static_cast< _base_ctrl_t const* >( base_controller ) ) );
    }

    SIXTRL_INLINE bool NodeControllerBase::hasNodeStore() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( this->m_my_own_node_store.get() == nullptr ) ||
            ( this->m_my_own_node_store.get() == this->m_ptr_node_store ) );

        return ( this->m_ptr_node_store != nullptr );
    }

    SIXTRL_INLINE bool NodeControllerBase::ownsNodeStore() const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) ) return false;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );
        return this->ownsNodeStore( lock );
    }

    SIXTRL_INLINE NodeStore const*
    NodeControllerBase::ptrConstNodeStore() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( this->m_my_own_node_store.get() == nullptr ) ||
            ( this->m_my_own_node_store.get() == this->m_ptr_node_store ) );

        return this->m_ptr_node_store;
    }

    SIXTRL_INLINE NodeStore const&
    NodeControllerBase::constNodeStore() const
    {
        if( this->m_ptr_node_store == nullptr )
        {
            throw std::runtime_error( "Unable to dereference ptr NodeStore" );
        }

        return *this->m_ptr_node_store;
    }

    SIXTRL_INLINE bool NodeControllerBase::ownsNodeStore(
        NodeControllerBase::node_lock_t const& SIXTRL_RESTRICT_REF
            node_lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( this->m_my_own_node_store.get() == nullptr ) ||
            ( this->m_my_own_node_store.get() == this->m_ptr_node_store ) );

        return ( ( this->nodeCheckLock( node_lock ) ) &&
                 ( this->hasNodeSet( node_lock ) ) &&
                 ( this->m_my_own_node_store.get() != nullptr ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeControllerBase::hasNodeSet()  const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) ) return false;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );
        return this->hasNodeSet( lock );
    }

    SIXTRL_INLINE bool NodeControllerBase::hasNodeSet(
        NodeControllerBase::node_lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        if( !this->nodeCheckLock( lock ) ) return false;

        SIXTRL_ASSERT( ( this->m_ptr_node_set == nullptr ) ||
            ( ( this->m_ptr_node_store->hasNodeSet(
                    lock, this->m_node_set_id ) ) &&
              ( this->m_ptr_node_store->ptrNodeSetBase(
                    lock, this->m_node_set_id ) == this->m_ptr_node_set ) ) );

        return ( ( this->m_node_set_id != _this_t::ILLEGAL_NODE_SET_ID ) &&
                 ( this->m_ptr_node_set != nullptr ) );
    }

    SIXTRL_INLINE NodeSetSingle const*
    NodeControllerBase::ptrConstNodeSetBase() const
    {
        return ( this->hasNodeSet() ) ? this->m_ptr_node_set : nullptr;
    }

    SIXTRL_INLINE NodeSetSingle const&
    NodeControllerBase::constNodeSetBase() const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) )
        {
            throw std::runtime_error( "no node store assigned -> can not lock" );
        }

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        if( this->m_ptr_node_set == nullptr )
        {
            throw std::runtime_error( "no node set available" );
        }

        SIXTRL_ASSERT( this->hasNodeSet( lock ) );

        return *( this->m_ptr_node_set );
    }

    SIXTRL_INLINE NodeControllerBase::size_type
    NodeControllerBase::numNodes() const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) )
                return SIXTRL_CXX_NAMESPACE::NodeControllerBase::size_type{ 0 };
        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->numNodes( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_set_id_t
    NodeControllerBase::nodeSetId() const
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeControllerBase;

        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) )
                return _this_t::ILLEGAL_NODE_SET_ID;

        _this_t::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->nodeSetId( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::minNodeIndex() const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) )
            return SIXTRL_CXX_NAMESPACE::NodeControllerBase::UNDEFINED_INDEX;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->minNodeIndex( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::maxNodeIndex() const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) )
            return SIXTRL_CXX_NAMESPACE::NodeControllerBase::UNDEFINED_INDEX;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->maxNodeIndex( lock );
    }

    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::nodeIndex( NodeControllerBase::size_type const nn ) const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) )
            return SIXTRL_CXX_NAMESPACE::NodeControllerBase::UNDEFINED_INDEX;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->nodeIndex( lock, nn );
    }

    SIXTRL_INLINE NodeControllerBase::node_id_t
    NodeControllerBase::nodeIdByNodeIndex(
        NodeControllerBase::node_index_t const node_index ) const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) )
        {
            throw std::runtime_error( "no node store assigned -> can not lock" );
        }

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->nodeIdByNodeIndex( lock, node_index );
    }

    SIXTRL_INLINE NodeControllerBase::c_node_id_t const*
    NodeControllerBase::ptrCNodeId(
        NodeControllerBase::size_type const nn ) const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) )
                return nullptr;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );
        return this->ptrCNodeId( lock, nn );
    }

    SIXTRL_INLINE NodeControllerBase::c_node_id_t const*
    NodeControllerBase::ptrCNodeIdByNodeIndex(
        NodeControllerBase::node_index_t const node_index ) const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) )
                return nullptr;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );
        return this->ptrCNodeIdByNodeIndex( lock, node_index );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    NodeControllerBase::usesAutoSelect() const SIXTRL_NOEXCEPT
    {
        bool const uses_autoselect = (
            ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->m_ptr_node_set->usesAutoSelect() ) );

        return uses_autoselect;
    }

    SIXTRL_INLINE bool
    NodeControllerBase::supportsChangingSelectedNode() const SIXTRL_NOEXCEPT
    {
        bool const supports_changing = (
            ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->m_ptr_node_set->supportsChangingSelectedNode() ) );

        return supports_changing;
    }

    SIXTRL_INLINE bool NodeControllerBase::supportsDirectlyChangingSelectedNode(
        ) const SIXTRL_NOEXCEPT
    {
        bool const supports_changing = (
            ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->m_ptr_node_set->supportsDirectlyChangingSelectedNode() ) );

        return supports_changing;
    }

    SIXTRL_INLINE bool
    NodeControllerBase::supportsUnselectingNode() const SIXTRL_NOEXCEPT
    {
        bool const supports_unselecting = (
            ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->m_ptr_node_set->supportsUnselectingNode() ) );

        return supports_unselecting;
    }

    template< typename... Args >
    SIXTRL_INLINE NodeControllerBase::node_index_t
    NodeControllerBase::findNodeIndex( Args&&... args ) const
    {
        return ( ( this->m_ptr_node_store != nullptr ) &&
                 ( this->m_ptr_node_set != nullptr ) )
            ? this->m_ptr_node_store->findNodeIndex(
                std::forward< Args >( args )... )
            : SIXTRL_CXX_NAMESPACE::NODE_UNDEFINED_INDEX;
    }

    SIXTRL_INLINE bool NodeControllerBase::isAvailable(
        NodeControllerBase::node_index_t const index ) const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) ||
            ( this->m_ptr_node_set == nullptr ) ) return false;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->isAvailable( lock, index );
    }

    SIXTRL_INLINE bool NodeControllerBase::hasSelectedNode() const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) ||
            ( this->m_ptr_node_set == nullptr ) ) return false;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->hasSelectedNode( lock );
    }

    SIXTRL_INLINE bool NodeControllerBase::isSelected(
        NodeControllerBase::node_index_t const index ) const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) ||
            ( this->m_ptr_node_set == nullptr ) ) return false;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->isSelected( lock, index );
    }

    SIXTRL_INLINE bool NodeControllerBase::canSelectNode(
        NodeControllerBase::node_index_t const index ) const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) ||
            ( this->m_ptr_node_set == nullptr ) ) return false;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->canSelectNode( lock, index );
    }

    SIXTRL_INLINE NodeControllerBase::status_t NodeControllerBase::selectNode(
        NodeControllerBase::node_index_t const index )
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) ||
            ( this->m_ptr_node_set == nullptr ) ) return false;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t lock(
            *this->m_ptr_node_store->lockable() );

        return this->selectNode( lock, index );
    }

    SIXTRL_INLINE bool NodeControllerBase::isDefault(
        NodeControllerBase::node_index_t const index ) const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) ||
            ( this->m_ptr_node_set == nullptr ) ) return false;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->isDefault( lock, index );
    }

    SIXTRL_INLINE bool NodeControllerBase::canChangeSelectedNodeTo(
        NodeControllerBase::node_index_t const new_node_index ) const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) ||
            ( this->m_ptr_node_set == nullptr ) ) return false;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->canChangeSelectedNodeTo( lock, new_node_index );
    }

    SIXTRL_INLINE bool NodeControllerBase::canChangeSelectedNode(
        NodeControllerBase::node_index_t const current_node_index,
        NodeControllerBase::node_index_t const new_node_index ) const
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) ||
            ( this->m_ptr_node_set == nullptr ) ) return false;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );

        return this->canChangeSelectedNode(
            lock, current_node_index, new_node_index );
    }

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::changeSelectedNodeTo(
        NodeControllerBase::node_index_t const new_node_index )
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) ||
            ( this->m_ptr_node_set == nullptr ) )
                return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t lock(
            *this->m_ptr_node_store->lockable() );

        return this->changeSelectedNodeTo( lock, new_node_index );
    }

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::changeSelectedNode(
        NodeControllerBase::node_index_t const current_node_index,
        NodeControllerBase::node_index_t const new_node_index )
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) ||
            ( this->m_ptr_node_set == nullptr ) )
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t lock(
            *this->m_ptr_node_store->lockable() );

        return this->canChangeSelectedNode(
            lock, current_node_index, new_node_index );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    NodeControllerBase::isSyncWithNodeSet() const SIXTRL_NOEXCEPT
    {
        bool const is_sync = (
            ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_set   != nullptr ) &&
            ( this->m_ptr_node_set->syncIdValue() ==
              this->m_expected_node_set_sync_id ) );

        return is_sync;
    }

    SIXTRL_INLINE NodeControllerBase::status_t
    NodeControllerBase::syncWithNodeSet()
    {
        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->m_ptr_node_store->lockable() == nullptr ) )
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        SIXTRL_CXX_NAMESPACE::NodeControllerBase::node_lock_t const lock(
            *this->m_ptr_node_store->lockable() );
        return this->syncWithNodeSet( lock );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeControllerBase::node_lockable_t*
    NodeControllerBase::nodeLockable() const SIXTRL_NOEXCEPT
    {
        return ( this->m_ptr_node_store != nullptr )
            ? this->m_ptr_node_store->lockable() : nullptr;
    }

    SIXTRL_INLINE bool NodeControllerBase::nodeCheckLock(
        NodeControllerBase::node_lock_t const& SIXTRL_RESTRICT_REF
            node_lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_ptr_node_store != nullptr ) &&
            ( node_lock.owns_lock() ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) &&
            ( this->m_ptr_node_store->lockable() == node_lock.mutex() ) );
    }

    SIXTRL_INLINE void NodeControllerBase::nodeCheckLockThrowIfError(
        NodeControllerBase::node_lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        if( !this->nodeCheckLock( lock ) )
        {
            throw std::runtime_error( "not successfully locked mutex lock" );
        }
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeStore* NodeControllerBase::ptrNodeStore(
        NodeControllerBase::node_lock_t const& SIXTRL_RESTRICT_REF node_lock )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        this->nodeCheckLockThrowIfError( node_lock );
        return const_cast< st::NodeStore* >( this->ptrConstNodeStore() );
    }

    SIXTRL_INLINE NodeStore& NodeControllerBase::nodeStore(
        NodeControllerBase::node_lock_t const& SIXTRL_RESTRICT_REF node_lock )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        this->nodeCheckLockThrowIfError( node_lock );
        return const_cast< st::NodeStore& >( this->constNodeStore() );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_CONTROLLER_BASE_HPP__ */

/* end: sixtracklib/common/control/node_controller_base.hpp */
