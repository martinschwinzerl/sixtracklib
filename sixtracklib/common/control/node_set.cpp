#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#include "sixtracklib/common/control/node_set.hpp"

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
    #include "sixtracklib/common/control/node_id.hpp"
   #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/buffer.hpp"
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/node_store.hpp"
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;
using _base_t   = st::NodeSetBase;
using _single_t = st::NodeSetSingle;

namespace SIXTRL_CXX_NAMESPACE
{
    /* ********************************************************************* */
    /* NodesetBase: */

    constexpr _base_t::arch_id_t        _base_t::ARCH_ILLEGAL;
    constexpr _base_t::node_index_t     _base_t::UNDEFINED_INDEX;
    constexpr _base_t::platform_id_t    _base_t::ILLEGAL_PLATFORM_ID;
    constexpr _base_t::platform_id_t    _base_t::ILLEGAL_DEVICE_ID;
    constexpr _base_t::id_str_format_t  _base_t::DEFAULT_ID_STR_FORMAT;
    constexpr _base_t::node_set_id_t    _base_t::ILLEGAL_NODE_SET_ID;
    constexpr _base_t::sync_id_value_t  _base_t::ILLEGAL_SYNC_ID_VALUE;
    constexpr _base_t::sync_id_value_t  _base_t::LAST_LEGAL_SYNC_ID_VALUE;

    NodeSetBase::NodeSetBase(
        st::NodeStore& SIXTRL_RESTRICT_REF node_store )
        m_node_store( node_store ),
        m_min_num_selectable_nodes(
            SIXTRL_CXX_NAMESPACE::NodeSetBase::size_type{ 0 } ),
        m_max_num_selectable_nodes(
            SIXTRL_CXX_NAMESPACE::NodeSetBase::size_type{ 0 } ),
        m_min_num_default_nodes(
            SIXTRL_CXX_NAMESPACE::NodeSetBase::size_type{ 0 } ),
        m_max_num_default_nodes(
            SIXTRL_CXX_NAMESPACE::NodeSetBase::size_type{ 0 } ),
        m_my_node_set_id( _base_t::ILLEGAL_NODE_SET_ID ),
        m_is_single_node_set( false ),
        m_allows_duplicate_nodes( false ),
        m_can_directly_change_selected_node( false ),
        m_can_unselect_node( false ),
        m_use_autoselect( false )
    {
    }

    NodeSetBase::NodeSetBase( st::NodeSetBase const& orig ) :
        m_sync_id(), m_node_store( orig.m_node_store ),
        m_min_num_selectable_nodes( orig.m_min_num_selectable_nodes ),
        m_max_num_selectable_nodes( orig.m_max_num_selectable_nodes ),
        m_min_num_default_nodes( orig.m_min_num_default_nodes ),
        m_max_num_default_nodes( orig.m_max_num_default_nodes ),
        m_my_node_set_id( orig.m_my_node_set_id ),
        m_is_single_node_set( orig.m_is_single_node_set ),
        m_allows_duplicate_nodes( orig.m_allows_duplicate_nodes ),
        m_can_directly_change_selected_node(
            orig.m_can_directly_change_selected_node ),
        m_can_unselect_node( orig.m_can_unselect_node ),
        m_use_autoselect( orig.m_use_autoselect )
    {
        this->m_sync_id.store( orig.m_sync_id.load() );
    }

    NodeSetBase::NodeSetBase( st::NodeSetBase&& orig ) :
        m_sync_id(), m_node_store( orig.m_node_store ),
        m_min_num_selectable_nodes( std::move(
            orig.m_min_num_selectable_nodes ) ),
        m_max_num_selectable_nodes( std::move(
            orig.m_max_num_selectable_nodes ) ),
        m_min_num_default_nodes( std::move( orig.m_min_num_default_nodes ) ),
        m_max_num_default_nodes( std::move( orig.m_max_num_default_nodes ) ),
        m_my_node_set_id( std::move( orig.m_my_node_set_id ) ),
        m_is_single_node_set( std::move( orig.m_is_single_node_set ) ),
        m_allows_duplicate_nodes( std::move( orig.m_allows_duplicate_nodes ) ),
        m_can_directly_change_selected_node(
            std::move( orig.m_can_directly_change_selected_node ) ),
        m_can_unselect_node( std::move( orig.m_can_unselect_node ) ),
        m_use_autoselect( std::move( orig.m_use_autoselect ) )
    {
        this->m_sync_id.store( orig.m_sync_id.load() );
        orig.doClearWithoutLocking();
    }

    st::NodeSetBase& NodeSetBase::operator=( st::NodeSetBase const& rhs )
    {
        _base_t::lock_t lock( *this->lockable() );

        if( ( &rhs != this ) &&
            ( this->ptrNodeStore() == rhs.ptrNodeStore() ) &&
            ( this->checkLock( lock ) ) && ( rhs.checkLock( lock ) ) )
        {
            SIXTRL_ASSERT( this->lockable() == rhs.lockable() );
            this->m_sync_id.store( rhs.m_sync_id.load() );

            this->m_node_store                = rhs.m_node_store;
            this->m_min_num_selectable_nodes  = rhs.m_min_num_selectable_nodes;
            this->m_max_num_selectable_nodes  = rhs.m_max_num_selectable_nodes;
            this->m_min_num_default_nodes     = rhs.m_min_num_default_nodes;
            this->m_max_num_default_nodes     = rhs.m_max_num_default_nodes;
            this->m_my_node_set_id            = rhs.m_my_node_set_id;
            this->m_is_single_node_set        = rhs.m_is_single_node_set;
            this->m_allows_duplicate_nodes    = rhs.m_allows_duplicate_nodes;

            this->m_can_directly_change_selected_node =
                rhs.m_can_directly_change_selected_node;

            this->m_can_unselect_node         = rhs.m_can_unselect_node;
            this->m_use_autoselect            = rhs.m_use_autoselect;
        }
        else if( this->ptrNodeStore() == rhs.ptrNodeStore() )
        {
            lock.unlock();

            throw std::runtime_error(
                "can not copy-assign from NodeSet belonging to different store" );
        }

        lock.unlock();

        return *this;
    }

    st::NodeSetBase& NodeSetBase::operator=( st::NodeSetBase&& rhs )
    {
        _base_t::lock_t lock( *this->lockable() );

        if( ( &rhs != this ) &&
            ( this->ptrNodeStore() == rhs.ptrNodeStore() ) &&
            ( this->checkLock( lock ) ) && ( rhs.checkLock( lock ) ) )
        {
            SIXTRL_ASSERT( this->lockable() == rhs.lockable() );

            this->m_sync_id.store( rhs.m_sync_id.load() );
            rhs.m_sync_id.store( _base_t::ILLEGAL_SYNC_ID_VALUE );

            this->m_node_store = std::move( rhs.m_node_store );
            this->m_min_num_selectable_nodes =
                std::move( rhs.m_min_num_selectable_nodes );

            this->m_max_num_selectable_nodes =
                std::move( rhs.m_max_num_selectable_nodes );

            this->m_min_num_default_nodes =
                std::move( rhs.m_min_num_default_nodes );

            this->m_max_num_default_nodes =
                std::move( rhs.m_max_num_default_nodes );

            this->m_my_node_set_id = std::move( rhs.m_my_node_set_id );

            this->m_is_single_node_set = std::move( rhs.m_is_single_node_set );

            this->m_allows_duplicate_nodes =
                std::move( rhs.m_allows_duplicate_nodes );

            this->m_can_directly_change_selected_node =
                std::move( rhs.m_can_directly_change_selected_node );

            this->m_can_unselect_node = std::move( rhs.m_can_unselect_node );
            this->m_use_autoselect = std::move( rhs.m_use_autoselect );
        }
        else if( this->ptrNodeStore() == rhs.ptrNodeStore() )
        {
            lock.unlock();

            throw std::runtime_error(
                "can not move-assign from NodeSet belonging to different store" );
        }

        lock.unlock();

        return *this;
    }

    /* --------------------------------------------------------------------- */

    _base_t::size_type NodeSetBase::numNodes(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    _base_t::node_index_t NodeSetBase::minNodeIndex(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    _base_t::node_index_t NodeSetBase::maxNodeIndex(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    _base_t::node_index_t NodeSetBase::nodeIndex(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::size_type const nn ) const SIXTRL_NOEXCEPT;

    _base_t::node_id_t const& NodeSetBase::nodeId(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::size_type const nn ) const;

    _base_t::node_id_t const& NodeSetBase::nodeIdByNodeIndex(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const ) const;

    _base_t::c_node_id_t const* NodeSetBase::ptrCNodeIdByNodeIndex(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index ) const SIXTRL_NOEXCEPT;

    _base_t::c_node_id_t const* NodeSetBase::ptrCNodeId(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::size_type const nn ) const SIXTRL_NOEXCEPT;

    bool NodeSetBase::available(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index ) const SIXTRL_NOEXCEPT;

    _base_t::node_index_t const* NodeSetBase::nodeIndicesBegin(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    _base_t::node_index_t const* NodeSetBase::nodeIndicesEnd(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    _base_t::c_node_id_t const* NodeSetBase::nodeIdsBegin(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    _base_t::c_node_id_t const* NodeSetBase::nodeIdsEnd(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

    bool NodeSetBase::isSelected(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index ) const SIXTRL_NOEXCEPT;

    bool NodeSetBase::canSelectNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

    bool NodeSetBase::isDefault(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

    bool NodeSetBase::canChangeToNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const current_node_idx,
        _base_t::node_index_t const next_node_idx ) const;

    _base_t::status_t NodeSetBase::changeToNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const current_node_idx,
        _base_t::node_index_t const next_node_idx );

    /* --------------------------------------------------------------------- */

    bool NodeSetBase::canUnselectNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const index ) const SIXTRL_NOEXCEPT;

    _base_t::status_t NodeSetBase::unselectNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index );

    /* --------------------------------------------------------------------- */

    _base_t::size_type NodeSetBase::requiredOutStringLength(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const;

    void NodeSetBase::print(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::ostream& SIXTRL_RESTRICT_REF output ) const;

    void NodeSetBase::print(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        ::FILE* SIXTRL_RESTRICT output ) const;

    void NodeSetBase::printOut(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF ) const;

    std::string NodeSetBase::toString(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const;

    _base_t::status_t NodeSetBase::toString(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::size_type const out_str_capacity,
        char* SIXTRL_RESTRICT ) const;

    /* --------------------------------------------------------------------- */

    _base_t::status_t NodeSetBase::doSyncWithNodeStore(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        SIXTRL_CXX_NAMESPACE::NodeStore& SIXTRL_RESTRICT node_store );

    _base_t::status_t NodeSetBase::doSelectNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index );

    _base_t::status_t NodeSetBase::doChangeToNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const current_node_idx,
        _base_t::node_index_t const next_node_idx );

    _base_t::status_t NodeSetBase::doUnselectNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const prev_selected_node );

    _base_t::status_t NodeSetBase::doPrintNodeInfos(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock );

    /* ********************************************************************* */
    /* NodeSetSingle: */

    node_index_t selectedNodeIndex(
        lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    node_id_t const& selectedNodeId(
        lock_t const& SIXTRL_RESTRICT_REF lock ) const;

    c_node_id_t const* ptrSelectedCNodeId(
        lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    status_t selectNode(
        lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index );

    /* --------------------------------------------------------------------- */

    node_index_t defaultNodeIndex(
        lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    node_id_t const& defaultNodeId(
        lock_t const& SIXTRL_RESTRICT_REF lock ) const;

    c_node_id_t const* ptrDefaultCNodeId(
        lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    bool hasDefaultNode(
        lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    bool requiresDefaultNode(
        lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

    bool canChangeToNode(
        lock_t const& SIXTRL_RESTRICT_REF lock,
        node_index_t const index ) const SIXTRL_NOEXCEPT;

    status_t changeToNode(
        lock_t const& SIXTRL_RESTRICT_REF lock, node_index_t const index );

    /* --------------------------------------------------------------------- */

    status_t doSyncWithNodeStore(
        lock_t const& SIXTRL_RESTRICT_REF lock,
        SIXTRL_CXX_NAMESPACE::NodeStore& SIXTRL_RESTRICT_REF st );
}

/* end: */
