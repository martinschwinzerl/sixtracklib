#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#include "sixtracklib/common/control/node_set.hpp"

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <atomic>
    #include <cstddef>
    #include <cstdlib>
    #include <cstdio>
    #include <iostream>
    #include <stdexcept>
    #include <string>
    #include <memory>
    #include <mutex>
    #include <sstream>
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
        st::NodeStore& SIXTRL_RESTRICT_REF node_store ) :
        m_min_num_selectable_nodes( _base_t::size_type{ 0 } ),
        m_max_num_selectable_nodes( _base_t::size_type{ 0 } ),
        m_min_num_default_nodes( _base_t::size_type{ 0 } ),
        m_max_num_default_nodes( _base_t::size_type{ 0 } ),
        m_node_store( node_store ),
        m_expected_sync_id_value( _base_t::sync_id_value_t{ 0 } ),
        m_my_node_set_id( _base_t::ILLEGAL_NODE_SET_ID ),
        m_is_single_node_set( false ),
        m_allows_duplicate_nodes( false ),
        m_can_directly_change_selected_node( false ),
        m_can_unselect_node( false ),
        m_use_autoselect( false )
    {
    }

    NodeSetBase::NodeSetBase( st::NodeSetBase const& orig ) :
        m_min_num_selectable_nodes( orig.m_min_num_selectable_nodes.load() ),
        m_max_num_selectable_nodes( orig.m_max_num_selectable_nodes.load() ),
        m_min_num_default_nodes( orig.m_min_num_default_nodes.load() ),
        m_max_num_default_nodes( orig.m_max_num_default_nodes.load() ),
        m_node_store( orig.m_node_store ),
        m_expected_sync_id_value( orig.m_expected_sync_id_value ),
        m_my_node_set_id( orig.m_my_node_set_id ),
        m_is_single_node_set( orig.m_is_single_node_set ),
        m_allows_duplicate_nodes( orig.m_allows_duplicate_nodes ),
        m_can_directly_change_selected_node(
            orig.m_can_directly_change_selected_node ),
        m_can_unselect_node( orig.m_can_unselect_node ),
        m_use_autoselect( orig.m_use_autoselect )
    {

    }

    NodeSetBase::NodeSetBase( st::NodeSetBase&& orig ) :
        m_min_num_selectable_nodes( orig.m_min_num_selectable_nodes.load() ),
        m_max_num_selectable_nodes( orig.m_max_num_selectable_nodes.load() ),
        m_min_num_default_nodes( orig.m_min_num_default_nodes.load() ),
        m_max_num_default_nodes( orig.m_max_num_default_nodes.load() ),
        m_node_store( orig.m_node_store ),
        m_expected_sync_id_value( std::move( orig.m_expected_sync_id_value ) ),
        m_my_node_set_id( std::move( orig.m_my_node_set_id ) ),
        m_is_single_node_set( std::move( orig.m_is_single_node_set ) ),
        m_allows_duplicate_nodes( std::move( orig.m_allows_duplicate_nodes ) ),
        m_can_directly_change_selected_node(
            std::move( orig.m_can_directly_change_selected_node ) ),
        m_can_unselect_node( std::move( orig.m_can_unselect_node ) ),
        m_use_autoselect( std::move( orig.m_use_autoselect ) )
    {
        orig.m_min_num_default_nodes.store( _base_t::size_type{ 0 } );
        orig.m_max_num_default_nodes.store( _base_t::size_type{ 0 } );

        orig.m_min_num_selectable_nodes.store( _base_t::size_type{ 0 } );
        orig.m_max_num_selectable_nodes.store( _base_t::size_type{ 0 } );
    }

    st::NodeSetBase& NodeSetBase::operator=( st::NodeSetBase const& rhs )
    {
        _base_t::lock_t lock( *this->lockable() );

        if( ( &rhs != this ) &&
            ( this->ptrNodeStore() == rhs.ptrNodeStore() ) &&
            ( this->checkLock( lock ) ) && ( rhs.checkLock( lock ) ) )
        {
            SIXTRL_ASSERT( this->lockable() == rhs.lockable() );
            this->m_node_store                = rhs.m_node_store;
            this->m_expected_sync_id_value    = rhs.m_expected_sync_id_value;

            this->m_min_num_selectable_nodes.store(
                rhs.m_min_num_selectable_nodes.load() );

            this->m_max_num_selectable_nodes.store(
                rhs.m_max_num_selectable_nodes.load() );

            this->m_min_num_default_nodes.store(
                rhs.m_min_num_default_nodes.load() );

            this->m_max_num_default_nodes.store(
                rhs.m_max_num_default_nodes.load() );

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

            this->m_node_store = std::move( rhs.m_node_store );

            this->m_expected_sync_id_value =
                std::move( rhs.m_expected_sync_id_value );
            rhs.m_expected_sync_id_value = _base_t::ILLEGAL_SYNC_ID_VALUE;

            this->m_min_num_selectable_nodes.store(
                rhs.m_min_num_selectable_nodes.load() );

            this->m_max_num_selectable_nodes.store(
                rhs.m_max_num_selectable_nodes.load() );

            this->m_min_num_default_nodes.store(
                rhs.m_min_num_default_nodes.load() );

            this->m_max_num_default_nodes.store(
                rhs.m_max_num_default_nodes.load() );

            rhs.m_min_num_selectable_nodes.store( _base_t::size_type{ 0 } );
            rhs.m_max_num_selectable_nodes.store( _base_t::size_type{ 0 } );

            rhs.m_min_num_default_nodes.store( _base_t::size_type{ 0 } );
            rhs.m_max_num_default_nodes.store( _base_t::size_type{ 0 } );

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
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->ptrNodeStore() != nullptr ) &&
                 ( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID ) &&
                 ( this->nodeStore().hasNodeSet( lock, this->nodeSetId() ) ) )
            ? this->nodeStore().numNodes( lock, this->nodeSetId() )
            : _base_t::size_type{ 0 };
    }

    _base_t::node_index_t NodeSetBase::minNodeIndex(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->ptrNodeStore() != nullptr ) &&
                 ( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID ) &&
                 ( this->nodeStore().hasNodeSet( lock, this->nodeSetId() ) ) &&
                 ( this->nodeStore().numNodes( lock, this->nodeSetId() ) >
                    _base_t::size_type{ 0 } ) )
            ? this->nodeStore().minAttachedNodeIndex( lock, this->nodeSetId() )
            : _base_t::UNDEFINED_INDEX;
    }

    _base_t::node_index_t NodeSetBase::maxNodeIndex(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->ptrNodeStore() != nullptr ) &&
                 ( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID ) &&
                 ( this->nodeStore().hasNodeSet( lock, this->nodeSetId() ) ) &&
                 ( this->nodeStore().numNodes( lock, this->nodeSetId() ) >
                    _base_t::size_type{ 0 } ) )
            ? this->nodeStore().maxAttachedNodeIndex( lock, this->nodeSetId() )
            : _base_t::UNDEFINED_INDEX;
    }

    _base_t::node_index_t NodeSetBase::nodeIndex(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        auto ptr = ( ( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID ) &&
                     ( this->checkLock( lock ) ) &&
                     ( this->ptrNodeStore() != nullptr ) )
            ? this->nodeStore().attachedNodeIndicesBegin(
                lock, this->nodeSetId() )
            : nullptr;

        if( ( ptr != nullptr ) && ( nn < this->numNodes( lock ) ) )
        {
            std::advance( ptr, nn );
            return *ptr;
        }

        return _base_t::UNDEFINED_INDEX;
    }

    _base_t::node_id_t const& NodeSetBase::nodeId(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::size_type const nn ) const
    {
        _base_t::node_index_t const node_index = this->nodeIndex( lock, nn );

        if( node_index == _base_t::UNDEFINED_INDEX )
        {
            throw std::runtime_error( "unable to get NodeId instance" );
        }

        SIXTRL_ASSERT( this->ptrNodeStore() != nullptr );
        SIXTRL_ASSERT( this->checkLock( lock ) );
        SIXTRL_ASSERT( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID );

        auto ptr_node_id = this->nodeStore().ptrNodeId( lock, node_index );

        if( ptr_node_id == nullptr )
        {
            throw std::runtime_error( "unable to get ptrNodeId()" );
        }

        SIXTRL_ASSERT( this->nodeStore().hasNodeSet( lock, this->nodeSetId() ) );
        return *ptr_node_id;
    }

    _base_t::node_id_t const& NodeSetBase::nodeIdByNodeIndex(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index ) const
    {
        SIXTRL_ASSERT( this->ptrNodeStore() != nullptr );
        SIXTRL_ASSERT( this->checkLock( lock ) );

        auto ptr_node_id = this->nodeStore().ptrNodeId( lock, node_index );
        if( ptr_node_id == nullptr )
        {
            throw std::runtime_error( "unable to get ptrNodeId()" );
        }

        SIXTRL_ASSERT( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID );

        return *ptr_node_id;
    }

    _base_t::c_node_id_t const* NodeSetBase::ptrCNodeIdByNodeIndex(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index ) const SIXTRL_NOEXCEPT
    {
        _base_t::c_node_id_t const* ptr_c_node_id = nullptr;

        SIXTRL_ASSERT( this->ptrNodeStore() != nullptr );
        SIXTRL_ASSERT( this->checkLock( lock ) );

        auto ptr_node_id = this->nodeStore().ptrNodeId( lock, node_index );
        if( ptr_node_id != nullptr )
        {
            SIXTRL_ASSERT( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID );
            ptr_c_node_id = ptr_node_id->getCApiPtr();
        }

        return ptr_c_node_id;
    }

    _base_t::c_node_id_t const* NodeSetBase::ptrCNodeId(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        _base_t::c_node_id_t const* ptr_c_node_id = nullptr;
        _base_t::node_index_t const node_index = this->nodeIndex( lock, nn );

        SIXTRL_ASSERT( this->ptrNodeStore() != nullptr );
        SIXTRL_ASSERT( this->checkLock( lock ) );

        auto ptr_node_id = this->nodeStore().ptrNodeId( lock, node_index );
        if( ptr_node_id != nullptr )
        {
            SIXTRL_ASSERT( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID );
            ptr_c_node_id = ptr_node_id->getCApiPtr();
        }

        return ptr_c_node_id;
    }

    bool NodeSetBase::available(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index ) const SIXTRL_NOEXCEPT
    {
        return ( ( node_index != _base_t::UNDEFINED_INDEX ) &&
                 ( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID ) &&
                 ( this->ptrNodeStore() != nullptr ) &&
                 ( this->nodeStore().isNodeAvailable( lock, node_index ) ) &&
                 ( this->nodeStore().isNodeAttachedToSet( lock, node_index,
                      this->nodeSetId() ) ) );
    }

    _base_t::node_index_t const* NodeSetBase::nodeIndicesBegin(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->checkLock( lock ) ) &&
                 ( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID ) )
            ? this->nodeStore().attachedNodeIndicesBegin(
                lock, this->nodeSetId() )
            : nullptr;
    }

    _base_t::node_index_t const* NodeSetBase::nodeIndicesEnd(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->checkLock( lock ) ) &&
                 ( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID ) )
            ? this->nodeStore().attachedNodeIndicesEnd( lock,
                this->nodeSetId() )
            : nullptr;
    }

    /* --------------------------------------------------------------------- */

    bool NodeSetBase::isSelected(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index ) const SIXTRL_NOEXCEPT
    {
        return this->nodeStore().isNodeSelectedBySet(
            lock, node_index, this->nodeSetId() );
    }

    bool NodeSetBase::canSelectNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const index ) const
    {
        return this->doCheckCanSelectNode( lock, index );
    }

    /* --------------------------------------------------------------------- */

    bool NodeSetBase::isDefault(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index ) const SIXTRL_NOEXCEPT
    {
        return this->nodeStore().isNodeDefaultForSet(
            lock, node_index, this->nodeSetId() );
    }

    /* --------------------------------------------------------------------- */

    bool NodeSetBase::canChangeSelectedNodeTo(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const current_node_idx,
        _base_t::node_index_t const next_node_idx ) const
    {
        return ( ( this->checkLock( lock ) ) &&
            ( this->nodeStore().hasNodeSet( lock, this->nodeSetId() ) ) &&
            ( this->nodeStore().isNodeSelectedBySet(
                lock, current_node_idx, this->nodeSetId() ) ) &&
            ( ( ( this->nodeStore().canNodeBeSelectedBySet(
                    lock, next_node_idx, this->nodeSetId(), true ) ) &&
                ( this->supportsChangingSelectedNode() ) ) ||
              ( this->nodeStore().isNodeSelectedBySet(
                  lock, next_node_idx, this->nodeSetId() ) ) ) );
    }

    _base_t::status_t NodeSetBase::changeSelectedNodeTo(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const current_node_idx,
        _base_t::node_index_t const next_node_idx )
    {
        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->ptrNodeStore() != nullptr ) &&
            ( this->nodeStore().canNodeBeSelectedBySet(
                lock, next_node_idx, this->nodeSetId(), true ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( next_node_idx != _base_t::UNDEFINED_INDEX );

            if( ( current_node_idx != _base_t::UNDEFINED_INDEX ) &&
                ( current_node_idx != next_node_idx ) &&
                ( this->supportsChangingSelectedNode() ) &&
                ( this->nodeStore().isNodeSelectedBySet( lock,
                    current_node_idx, this->nodeSetId() ) ) )
            {
                if( this->supportsDirectlyChangingSelectedNode() )
                {
                    status = this->doChangeSelectedNodeTo(
                        lock, current_node_idx, next_node_idx );
                }
                else if( this->supportsUnselectingNode() )
                {
                    status = this->doUnselectNode( lock, current_node_idx );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        SIXTRL_ASSERT( !this->nodeStore().isNodeSelectedBySet(
                            lock, current_node_idx, this->nodeSetId() ) );

                        status = this->doSelectNode( lock, next_node_idx );
                    }
                }
            }
            else if( current_node_idx == _base_t::UNDEFINED_INDEX )
            {
                status = this->doSelectNode( lock, next_node_idx );
            }
            else if( ( next_node_idx == current_node_idx ) &&
                     ( this->nodeStore().isNodeSelectedBySet( lock,
                         next_node_idx, this->nodeSetId() ) ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }
        else if( ( this->ptrNodeStore() != nullptr ) &&
                 ( this->nodeStore().isNodeSelectedBySet(
                    lock, next_node_idx, this->nodeSetId() ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( next_node_idx != _base_t::UNDEFINED_INDEX );

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool NodeSetBase::canUnselectNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        _base_t::size_type const num_selected_nodes =
            this->doGetNumSelectedNodes( lock );

        _base_t::node_set_id_t const set_id = this->nodeSetId();

        bool can_unselect = ( ( this->ptrNodeStore() != nullptr ) &&
            ( this->supportsUnselectingNode() ) &&
            ( num_selected_nodes >= this->minNumSelectableNodes() ) &&
            ( this->nodeStore().isNodeSelectedBySet( lock, index, set_id ) ) );

        if( can_unselect )
        {
            SIXTRL_ASSERT( index  != _base_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( set_id != _base_t::ILLEGAL_NODE_SET_ID );

            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( this->nodeStore().hasNodeSet( lock, set_id ) );
            SIXTRL_ASSERT( this->nodeStore().isNodeAttachedToSet(
                lock, index, set_id ) );

            if( ( this->minNumSelectableNodes() > _base_t::size_type{ 0 } ) &&
                ( this->minNumSelectableNodes() == num_selected_nodes ) )
            {
                can_unselect = false;

                if( this->usesAutoSelect() )
                {
                    _base_t::node_index_t const next_idx_to_select =
                        this->doGetNextDefaultNodeIndexToSelect( lock,
                            _base_t::size_type{ 1 }, &index );

                    if( ( next_idx_to_select != _base_t::UNDEFINED_INDEX ) &&
                        ( next_idx_to_select != index ) )
                    {
                        SIXTRL_ASSERT( this->nodeStore().isNodeDefaultForSet(
                            lock, next_idx_to_select, set_id ) );

                        SIXTRL_ASSERT( !this->nodeStore().isNodeSelectedBySet(
                            lock, next_idx_to_select, set_id ) );

                        SIXTRL_ASSERT( this->nodeStore().canNodeBeSelectedBySet(
                            lock, next_idx_to_select, set_id, true ) );

                        can_unselect = true;
                    }
                }
            }
        }

        return can_unselect;
    }

    _base_t::status_t NodeSetBase::unselectNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const index )
    {
        using size_t  = _base_t::size_type;
        using index_t = _base_t::node_index_t;

        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        size_t const num_selected_nodes = this->doGetNumSelectedNodes( lock );
        _base_t::node_set_id_t const set_id = this->nodeSetId();

        if( ( this->ptrNodeStore() != nullptr ) &&
            ( this->supportsUnselectingNode() ) &&
            ( num_selected_nodes >= this->minNumSelectableNodes() ) &&
            ( this->nodeStore().isNodeSelectedBySet( lock, index, set_id ) ) )
        {
            SIXTRL_ASSERT( index  != _base_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( set_id != _base_t::ILLEGAL_NODE_SET_ID );

            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( this->nodeStore().hasNodeSet( lock, set_id ) );
            SIXTRL_ASSERT( this->nodeStore().isNodeAttachedToSet(
                lock, index, set_id ) );

            if( this->minNumSelectableNodes() < num_selected_nodes )
            {
                status = this->doUnselectNode( lock, index );
            }
            else if( ( this->minNumSelectableNodes() == num_selected_nodes ) &&
                     ( this->usesAutoSelect() ) )
            {
                index_t const next = this->doGetNextDefaultNodeIndexToSelect(
                    lock, size_t{ 1 }, &index );

                if( ( next != _base_t::UNDEFINED_INDEX ) && ( next != index ) )
                {
                    SIXTRL_ASSERT( this->nodeStore().isNodeDefaultForSet(
                        lock, next, set_id ) );

                    SIXTRL_ASSERT( !this->nodeStore().isNodeSelectedBySet(
                        lock, next, set_id ) );

                    SIXTRL_ASSERT( this->nodeStore().canNodeBeSelectedBySet(
                        lock, next, set_id, true ) );

                    status = this->doUnselectNode( lock, index );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        SIXTRL_ASSERT( this->nodeStore().canNodeBeSelectedBySet(
                            lock, next, set_id ) );

                        status = this->doSelectNode( lock, next );
                    }
                }
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( ( ( this->doGetNumSelectedNodes( lock ) >=
                    this->minNumSelectableNodes() ) ) &&
                    ( !this->nodeStore().isNodeSelectedBySet(
                        lock, index, set_id ) ) ) );
        }

        return status;
    }

    _base_t::status_t NodeSetBase::syncWithStore(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        return ( this->ptrNodeStore() != nullptr )
            ? this->doSyncWithNodeStore( lock, this->nodeStore() )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* --------------------------------------------------------------------- */

    _base_t::size_type NodeSetBase::requiredOutStringLength(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        std::ostringstream a2str;
        _base_t::status_t status = this->doPrintNodeInfos( lock, a2str );

        return ( status == st::ARCH_STATUS_SUCCESS )
            ? a2str.str().size() + _base_t::size_type{ 1 }
            : _base_t::size_type{ 0 };
    }

    void NodeSetBase::print(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        _base_t::status_t status = this->doPrintNodeInfos( lock, output );
        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    void NodeSetBase::print(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        ::FILE* SIXTRL_RESTRICT output ) const
    {
        if( output != nullptr )
        {
            std::ostringstream a2str;
            _base_t::status_t status = this->doPrintNodeInfos( lock, a2str );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                std::string const temp_str( a2str.str() );
                int ret = std::fprintf( output, "%s", temp_str.c_str() );
                SIXTRL_ASSERT( ret > 0 );
            }
        }
    }

    void NodeSetBase::printOut(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        return this->print( lock, std::cout );
    }

    std::string NodeSetBase::toString(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        if( this->checkLock( lock ) )
        {
            std::ostringstream a2str;
            if( st::ARCH_STATUS_SUCCESS ==
                    this->doPrintNodeInfos( lock, a2str ) )
            {
                return a2str.str();
            }
        }

        return std::string{};
    }

    _base_t::status_t NodeSetBase::toString(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::size_type const out_str_capacity,
        char* SIXTRL_RESTRICT out_str ) const
    {
        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( out_str_capacity > _base_t::size_type{ 1 } ) &&
            ( out_str != nullptr ) && ( this->checkLock( lock ) ) )
        {
            std::fill( out_str, out_str + out_str_capacity, '\0' );

            std::ostringstream a2str;
            status = this->doPrintNodeInfos( lock, a2str );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                std::string const temp_str( a2str.str() );
                if( temp_str.size() < out_str_capacity )
                {
                    std::copy( temp_str.begin(), temp_str.end(), out_str );
                }
                else
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _base_t::status_t NodeSetBase::doSyncWithNodeStore(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        SIXTRL_CXX_NAMESPACE::NodeStore& SIXTRL_RESTRICT node_store )
    {
        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID ) &&
            ( node_store.checkLock( lock ) ) &&
            ( node_store.hasNodeSet( lock, this->nodeSetId() ) ) )
        {
            this->doSetExpectedSyncIdValue( node_store.syncIdValue() );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    bool NodeSetBase::doCheckCanSelectNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const index ) const
    {
        bool can_select_node = false;

        _base_t::node_set_id_t const set_id = this->nodeSetId();

        if( ( index != _base_t::UNDEFINED_INDEX ) &&
            ( this->ptrNodeStore() != nullptr ) &&
            ( this->nodeStore().isNodeAttachedToSet( lock, index, set_id ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( this->nodeStore().hasNodeSet( lock, set_id ) );
            SIXTRL_ASSERT( this->nodeStore().isNodeAvailable( lock, index ) );

            if( this->nodeStore().isNodeSelectedBySet( lock, index, set_id ) )
            {
                can_select_node = true;
            }
            else if( this->nodeStore().canNodeBeSelectedBySet(
                    lock, index, set_id ) )
            {
                can_select_node = true;
            }
        }

        return can_select_node;
    }

    _base_t::status_t NodeSetBase::doSelectNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index )
    {
        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( node_index != _base_t::UNDEFINED_INDEX ) &&
            ( this->ptrNodeStore() != nullptr ) &&
            ( this->nodeStore().canNodeBeSelectedBySet(
                lock, node_index, this->nodeSetId() ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( node_index != _base_t::UNDEFINED_INDEX );

            status = this->nodeStore().doMarkNodeAsSelectedBySet(
                lock, node_index, this->nodeSetId() );

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( this->nodeStore().isNodeSelectedBySet(
                    lock, node_index, this->nodeSetId() ) ) );
        }

        return status;
    }

    _base_t::status_t NodeSetBase::doChangeSelectedNodeTo(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const current_node_idx,
        _base_t::node_index_t const next_node_idx )
    {
        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->ptrNodeStore() != nullptr ) &&
            ( this->nodeStore().isNodeSelectedBySet(
                lock, current_node_idx, this->nodeSetId() ) ) &&
            ( this->nodeStore().canNodeBeSelectedBySet(
                lock, next_node_idx, this->nodeSetId(), true ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( current_node_idx != _base_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( next_node_idx != _base_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->supportsDirectlyChangingSelectedNode() );

            status = this->nodeStore().doMarkNodeAsSelectedBySet(
                lock, next_node_idx, this->nodeSetId() );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->nodeStore().doUnselectNodeFromSet(
                    lock, current_node_idx, this->nodeSetId() );
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( ( this->nodeStore().isNodeSelectedBySet(
                    lock, next_node_idx, this->nodeSetId() ) ) &&
                  ( !this->nodeStore().isNodeSelectedBySet(
                      lock, current_node_idx, this->nodeSetId() ) ) ) );
        }

        return status;
    }

    _base_t::status_t NodeSetBase::doUnselectNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const current_node_idx )
    {
        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->ptrNodeStore() != nullptr ) &&
            ( this->nodeStore().isNodeSelectedBySet(
                lock, current_node_idx, this->nodeSetId() ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( current_node_idx != _base_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID );

            status = this->nodeStore().doUnselectNodeFromSet(
                    lock, current_node_idx, this->nodeSetId() );

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( !this->nodeStore().isNodeSelectedBySet(
                      lock, current_node_idx, this->nodeSetId() ) ) );
        }

        return status;
    }

    _base_t::status_t NodeSetBase::doAddDefaultNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index )
    {
        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( node_index != _base_t::UNDEFINED_INDEX ) &&
            ( this->ptrNodeStore() != nullptr ) &&
            ( this->nodeStore().canNodeBeMadeDefaultForSet(
                lock, node_index, this->nodeSetId() ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( node_index != _base_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID );

            status = this->nodeStore().doMarkNodeAsDefaultForSet(
                lock, node_index, this->nodeSetId() );

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( this->nodeStore().isNodeDefaultForSet(
                    lock, node_index, this->nodeSetId() ) ) );
        }

        return status;
    }

    _base_t::status_t NodeSetBase::doRemoveDefaultNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const node_index )
    {
        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->ptrNodeStore() != nullptr ) &&
            ( this->nodeStore().isNodeDefaultForSet(
                lock, node_index, this->nodeSetId() ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( node_index != _base_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID );

            status = this->nodeStore().doRemoveDefaultNodeFromSet(
                    lock, node_index, this->nodeSetId() );

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( !this->nodeStore().isNodeDefaultForSet(
                      lock, node_index, this->nodeSetId() ) ) );
        }

        return status;
    }

    _base_t::status_t NodeSetBase::doPrintNodeInfos(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::ostream& SIXTRL_RESTRICT_REF output_stream ) const
    {
        using size_t = _base_t::size_type;

        bool const is_stored = (
            ( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->ptrNodeStore() != nullptr ) &&
            ( this->nodeStore().hasNodeSet( lock, this->nodeSetId() ) ) &&
            ( this->nodeStore().ptrNodeSetBase(
                lock, this->nodeSetId() ) == this ) );

        if( is_stored )
        {
            output_stream << "NodeSet         : " << this->nodeSetId()
                          << "\r\n"
                          << "Num nodes       : ";

            size_t nn = this->nodeStore().numNodes( lock, this->nodeSetId() );
            if( nn > size_t{ 0 } )
            {
                if( size_t{ 1 } < nn ) output_stream << "[ ";
                bool is_first;

                auto idx_it  = this->nodeStore().attachedNodeIndicesBegin(
                    lock, this->nodeSetId() );

                auto idx_end = this->nodeStore().attachedNodeIndicesEnd(
                    lock, this->nodeSetId() );

                for( ; idx_it != idx_end ; ++idx_it )
                {
                    auto ptr_node_id =
                        this->nodeStore().ptrNodeId( lock, *idx_it );
                    if( ptr_node_id == nullptr ) continue;

                    if( !is_first ) output_stream << ", ";
                    output_stream << ptr_node_id->toString(
                        st::NODE_ID_STR_FORMAT_ARCHID );
                    if(  is_first ) is_first = false;
                }

                if( size_t{ 1 } < nn ) output_stream << " ]";
                output_stream << "\r\n";
            }
            else
            {
                output_stream << "none";
            }

            output_stream << "Selected nodes  : ";

            nn = this->nodeStore().numSelectedNodes( lock, this->nodeSetId() );
            if( nn > size_t{ 0 } )
            {
                if( size_t{ 1 } < nn ) output_stream << "[ ";
                bool is_first;

                auto idx_it  = this->nodeStore().selectedNodeIndicesBegin(
                    lock, this->nodeSetId() );

                auto idx_end = this->nodeStore().selectedNodeIndicesEnd(
                    lock, this->nodeSetId() );

                for( ; idx_it != idx_end ; ++idx_it )
                {
                    auto ptr_node_id =
                        this->nodeStore().ptrNodeId( lock, *idx_it );
                    if( ptr_node_id == nullptr ) continue;

                    if( !is_first ) output_stream << ", ";
                    output_stream << ptr_node_id->toString(
                        st::NODE_ID_STR_FORMAT_ARCHID );
                    if(  is_first ) is_first = false;
                }

                if( size_t{ 1 } < nn ) output_stream << " ]";
                output_stream << "\r\n";
            }
            else
            {
                output_stream << "none";
            }

            output_stream << "\r\n";

            output_stream << "Default nodes   : ";

            nn = this->nodeStore().numSelectedNodes( lock, this->nodeSetId() );
            if( nn > size_t{ 0 } )
            {
                if( size_t{ 1 } < nn ) output_stream << "[ ";
                bool is_first;

                auto idx_it  = this->nodeStore().defaultNodeIndicesBegin(
                    lock, this->nodeSetId() );

                auto idx_end = this->nodeStore().defaultNodeIndicesEnd(
                    lock, this->nodeSetId() );

                for( ; idx_it != idx_end ; ++idx_it )
                {
                    auto ptr_node_id =
                        this->nodeStore().ptrNodeId( lock, *idx_it );
                    if( ptr_node_id == nullptr ) continue;

                    if( !is_first ) output_stream << ", ";
                    output_stream << ptr_node_id->toString(
                        st::NODE_ID_STR_FORMAT_ARCHID );
                    if(  is_first ) is_first = false;
                }

                if( size_t{ 1 } < nn ) output_stream << " ]";
                output_stream << "\r\n";
            }
            else
            {
                output_stream << "none";
            }

            output_stream << "\r\n";
        }
        else
        {
            output_stream
                << "min num selects : " << this->minNumSelectableNodes()
                << "\r\nmax num selects : " << this->maxNumSelectableNodes()
                << "\r\n\r\nmin num default : " << this->minNumDefaultNodes()
                << "\r\nmax num default : " << this->maxNumDefaultNodes()
                << "\r\n\r\n";
        }

        return st::ARCH_STATUS_SUCCESS;
    }

    _base_t::node_index_t NodeSetBase::doGetNextDefaultNodeIndexToSelect(
            _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const num_indices_to_exclude,
            node_index_t const* SIXTRL_RESTRICT excl_indices_begin
        ) const SIXTRL_NOEXCEPT
    {
        using size_t = _base_t::size_type;

        _base_t::node_set_id_t const set_id = this->nodeSetId();
        _base_t::node_index_t next_default_node_idx = _base_t::UNDEFINED_INDEX;

        if( ( num_indices_to_exclude > size_t{ 0 } ) &&
            ( excl_indices_begin == nullptr ) )
        {
            return next_default_node_idx;
        }

        _base_t::node_index_t const* excl_indices_end = excl_indices_begin;
        std::advance( excl_indices_end, num_indices_to_exclude );

        SIXTRL_ASSERT( ( num_indices_to_exclude == size_t{ 0 } ) ||
            ( std::is_sorted( excl_indices_begin, excl_indices_end ) ) );

        if( ( this->ptrNodeStore() != nullptr ) &&
            ( this->nodeStore().hasNodeSet( lock, set_id ) ) )
        {
            SIXTRL_ASSERT( set_id != _base_t::ILLEGAL_NODE_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            size_t const num_default_nodes =
                this->nodeStore().numDefaultNodes( lock, set_id );

            auto it = this->nodeStore().defaultNodeIndicesBegin( lock, set_id );
            auto end = this->nodeStore().defaultNodeIndicesEnd( lock, set_id );

            if( ( num_default_nodes > size_t{ 0 } ) && ( it != nullptr ) )
            {
                for( ; it != end ; ++it )
                {
                    SIXTRL_ASSERT( *it != _base_t::UNDEFINED_INDEX );
                    SIXTRL_ASSERT( this->nodeStore().isNodeAttachedToSet(
                        lock, *it, set_id ) );

                    SIXTRL_ASSERT( this->nodeStore().isNodeDefaultForSet(
                        lock, *it, set_id )  );

                    if( ( !this->nodeStore().isNodeSelectedBySet(
                            lock, *it, set_id ) ) &&
                        (  this->nodeStore().canNodeBeSelectedBySet(
                            lock, *it, set_id, true ) ) &&
                        ( ( num_indices_to_exclude == size_t{ 0 } ) ||
                          ( !std::binary_search( excl_indices_begin,
                                excl_indices_end, *it ) ) ) )
                    {
                        next_default_node_idx = *it;
                        break;
                    }
                }
            }
        }

        return next_default_node_idx;
    }

    /* --------------------------------------------------------------------- */

    _base_t::status_t NodeSetBase::doSetMinNumSelectableNodes(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::size_type const min_num_selectable_nodes ) SIXTRL_NOEXCEPT
    {
        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( ( this->ptrNodeStore() != nullptr ) && ( this->checkLock( lock ) ) )
        {
            this->m_min_num_selectable_nodes.store( min_num_selectable_nodes );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _base_t::status_t NodeSetBase::doSetMaxNumSelectableNodes(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::size_type const max_num_selectable_nodes ) SIXTRL_NOEXCEPT
    {
        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( ( this->ptrNodeStore() != nullptr ) && ( this->checkLock( lock ) ) )
        {
            this->m_max_num_selectable_nodes.store( max_num_selectable_nodes );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _base_t::size_type NodeSetBase::doGetNumSelectedNodes(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->ptrNodeStore() != nullptr ) &&
                 ( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID ) &&
                 ( this->nodeStore().hasNodeSet( lock, this->nodeSetId() ) ) )
            ? this->nodeStore().numSelectedNodes( lock, this->nodeSetId() )
            : _base_t::size_type{ 0 };
    }

    _base_t::status_t NodeSetBase::doSetMinNumDefaultNodes(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::size_type const min_num_default_nodes ) SIXTRL_NOEXCEPT
    {
        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( ( this->ptrNodeStore() != nullptr ) && ( this->checkLock( lock ) ) )
        {
            this->m_min_num_default_nodes.store( min_num_default_nodes );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _base_t::status_t NodeSetBase::doSetMaxNumDefaultNodes(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::size_type const max_num_default_nodes ) SIXTRL_NOEXCEPT
    {
        _base_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( ( this->ptrNodeStore() != nullptr ) && ( this->checkLock( lock ) ) )
        {
            this->m_max_num_default_nodes.store( max_num_default_nodes );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _base_t::size_type NodeSetBase::doGetNumDefaultNodes(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->ptrNodeStore() != nullptr ) &&
                 ( this->nodeSetId() != _base_t::ILLEGAL_NODE_SET_ID ) &&
                 ( this->nodeStore().hasNodeSet( lock, this->nodeSetId() ) ) )
            ? this->nodeStore().numDefaultNodes( lock, this->nodeSetId() )
            : _base_t::size_type{ 0 };
    }

    /* ********************************************************************* */
    /* NodeSetSingle: */

    _single_t::status_t NodeSetSingle::selectNode(
        _single_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _single_t::node_index_t const index )
    {
        using size_t = _single_t::size_type;
        _single_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _single_t::node_index_t const current_node_idx =
            this->selectedNodeIndex();

        SIXTRL_ASSERT( this->maxNumSelectableNodes() == size_t{ 1 } );

        if( ( index != _single_t::UNDEFINED_INDEX ) &&
            ( index != current_node_idx ) &&
            ( this->nodeSetId() != _single_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->checkLock( lock ) ) &&
            ( this->ptrNodeStore() != nullptr ) &&
            ( this->nodeStore().isNodeAttachedToSet(
                lock, index, this->nodeSetId() ) ) )
        {
            if( ( this->doGetNumSelectedNodes( lock ) <
                  this->maxNumSelectableNodes() ) &&
                ( this->nodeStore().canNodeBeSelectedBySet(
                    lock, index, this->nodeSetId() ) ) )
            {
                SIXTRL_ASSERT( this->doGetNumSelectedNodes( lock ) ==
                    size_t{ 0 } );
                SIXTRL_ASSERT( !this->nodeStore().isNodeSelectedBySet( lock,
                    index, this->nodeSetId() ) );

                status = this->doSelectNode( lock, index );
            }
            else if( ( this->supportsChangingSelectedNode() ) &&
                ( this->doGetNumSelectedNodes( lock ) == size_t{ 1 } ) &&
                ( this->nodeStore().canNodeBeSelectedBySet(
                    lock, index, this->nodeSetId(), true ) ) )
            {
                SIXTRL_ASSERT( current_node_idx != _single_t::UNDEFINED_INDEX );
                SIXTRL_ASSERT( this->nodeStore().isNodeSelectedBySet(
                    lock, current_node_idx, this->nodeSetId() ) );

                if( this->supportsDirectlyChangingSelectedNode() )
                {
                    status = this->doChangeSelectedNodeTo(
                        lock, current_node_idx, index );
                }
                else if( ( this->supportsUnselectingNode() ) &&
                         ( this->canUnselectNode( lock, current_node_idx ) ) )
                {
                    status = this->doUnselectNode( lock, current_node_idx );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        SIXTRL_ASSERT( !this->nodeStore().isNodeSelectedBySet(
                            lock, current_node_idx, this->nodeSetId() ) );

                        status = this->doSelectNode( lock, index );
                    }
                }
            }
        }
        else if( ( index == current_node_idx ) &&
                 ( this->nodeSetId() != _single_t::ILLEGAL_NODE_SET_ID ) &&
                 ( this->ptrNodeStore() != nullptr ) &&
                 ( this->nodeStore().isNodeSelectedBySet(
                     lock, index, this->nodeSetId() ) ) &&
                 ( this->doGetNumSelectedNodes( lock ) == size_t{ 1 } ) )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool NodeSetSingle::hasDefaultNode(
        _single_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->defaultNodeIndex() != _single_t::UNDEFINED_INDEX ) &&
                 ( this->ptrNodeStore() != nullptr ) &&
                 ( this->nodeSetId() != _single_t::ILLEGAL_NODE_SET_ID ) &&
                 ( this->nodeStore().isNodeDefaultForSet( lock,
                     this->defaultNodeIndex(), this->nodeSetId() ) ) );
    }

    /* --------------------------------------------------------------------- */

    bool NodeSetSingle::canChangeSelectedNodeTo(
        _single_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _single_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        return this->canChangeSelectedNodeTo(
            lock, this->selectedNodeIndex(), index );
    }

    _single_t::status_t NodeSetSingle::changeSelectedNodeTo(
        _single_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _single_t::node_index_t const index )
    {
        return this->changeSelectedNodeTo(
            lock, this->selectedNodeIndex(), index );
    }

    /* --------------------------------------------------------------------- */

    _single_t::status_t NodeSetSingle::doSyncWithNodeStore(
        _single_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        st::NodeStore& SIXTRL_RESTRICT_REF node_store )
    {
        using size_t = _single_t::size_type;
        _single_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->nodeSetId() != _single_t::ILLEGAL_NODE_SET_ID ) &&
            ( node_store.checkLock( lock ) ) &&
            ( node_store.hasNodeSet( lock, this->nodeSetId() ) ) )
        {
            size_t const num_selected_nodes = node_store.numSelectedNodes(
                lock, this->nodeSetId() );

            size_t const num_default_nodes = node_store.numDefaultNodes(
                lock, this->nodeSetId() );

            auto ptr_sel_begin = node_store.selectedNodeIndicesBegin(
                lock, this->nodeSetId() );

            auto ptr_def_begin = node_store.defaultNodeIndicesBegin(
                lock, this->nodeSetId() );

            if( ( ( num_selected_nodes == size_t{ 0 } ) ||
                  ( ( num_selected_nodes == size_t{ 1 } ) &&
                    ( ptr_sel_begin != nullptr ) ) ) &&
                ( ( num_default_nodes == size_t{ 0 } ) ||
                  ( ( num_default_nodes == size_t{ 1 } ) &&
                    ( ptr_def_begin != nullptr ) ) ) )
            {
                if( num_selected_nodes == _single_t::size_type{ 1 } )
                {
                    this->m_selected_node_index.store( *ptr_sel_begin );
                }
                else
                {
                    this->m_selected_node_index.store(
                        _single_t::UNDEFINED_INDEX );
                }

                if( num_default_nodes == _single_t::size_type{ 1 } )
                {
                    this->m_default_node_index.store( *ptr_def_begin );
                }
                else
                {
                    this->m_default_node_index.store(
                        _single_t::UNDEFINED_INDEX );
                }

                status = _base_t::doSyncWithNodeStore( lock, node_store );
            }
        }

        return status;
    }

    bool NodeSetSingle::doCheckCanSelectNode(
        _base_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _base_t::node_index_t const index ) const
    {
        using size_t = _base_t::size_type;

        _base_t::node_set_id_t const set_id = this->nodeSetId();
        _base_t::node_index_t const selected_idx = this->selectedNodeIndex();

        bool can_select_node = (
            ( index != _base_t::UNDEFINED_INDEX ) &&
            ( this->ptrNodeStore() != nullptr ) &&
            ( this->checkLock( lock ) ) &&
            ( this->nodeStore().isNodeAttachedToSet( lock, index, set_id ) ) &&
            ( ( ( selected_idx == _base_t::UNDEFINED_INDEX ) &&
                ( this->doGetNumSelectedNodes( lock ) == size_t{ 0 } ) )||
              ( this->nodeStore().isNodeSelectedBySet(
                lock, selected_idx, set_id ) ) ) );

        if( can_select_node )
        {
            can_select_node = false;

            if( ( selected_idx != index ) &&
                ( selected_idx != _base_t::UNDEFINED_INDEX ) )
            {
                SIXTRL_ASSERT( this->nodeStore().isNodeAttachedToSet(
                    lock, selected_idx, set_id ) );

                if( ( this->supportsChangingSelectedNode() ) &&
                    ( this->nodeStore().canNodeBeSelectedBySet(
                        lock, index, set_id, true ) ) )
                {
                    can_select_node = true;
                }
            }
            else if( ( selected_idx == _base_t::UNDEFINED_INDEX ) &&
                     ( this->nodeStore().canNodeBeSelectedBySet(
                         lock, index, set_id ) ) )
            {
                can_select_node = true;
            }
            else if( selected_idx == index )
            {
                can_select_node = true;
            }
        }

        return can_select_node;
    }

    _single_t::status_t NodeSetSingle::doSelectNode(
        _single_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _single_t::node_index_t const node_index )
    {
        _single_t::status_t const status =
            _base_t::doSelectNode( lock, node_index );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( node_index != _single_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->doGetNumSelectedNodes( lock ) ==
                           _single_t::size_type{ 1 } );

            this->m_selected_node_index.store( node_index );
        }

        return status;
    }

    _single_t::status_t NodeSetSingle::doUnselectNode(
        _single_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _single_t::node_index_t const node_index )
    {
        _single_t::status_t const status =
            _base_t::doUnselectNode( lock, node_index );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( node_index != _single_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->doGetNumSelectedNodes( lock ) ==
                           _single_t::size_type{ 0 } );

            this->m_selected_node_index.store( _single_t::UNDEFINED_INDEX );
        }

        return status;
    }

    _single_t::status_t NodeSetSingle::doChangeSelectedNodeTo(
        _single_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _single_t::node_index_t const current_node_idx,
        _single_t::node_index_t const next_node_idx )
    {
        _single_t::status_t const status =
            _base_t::doChangeSelectedNodeTo( lock, current_node_idx, next_node_idx );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( next_node_idx != _single_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->doGetNumSelectedNodes( lock ) ==
                           _single_t::size_type{ 1 } );

            this->m_selected_node_index.store( next_node_idx );
        }

        return status;
    }

    _single_t::status_t NodeSetSingle::doAddDefaultNode(
        _single_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _single_t::node_index_t const node_index )
    {
        _single_t::status_t const status =
            _base_t::doAddDefaultNode( lock, node_index );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( node_index != _single_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->doGetNumDefaultNodes( lock ) ==
                           _single_t::size_type{ 1 } );

            this->m_default_node_index.store( node_index );
        }

        return status;
    }

    _single_t::status_t NodeSetSingle::doRemoveDefaultNode(
        _single_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _single_t::node_index_t const node_index )
    {
        _single_t::status_t const status =
            _base_t::doRemoveDefaultNode( lock, node_index );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( node_index != _single_t::UNDEFINED_INDEX );
            SIXTRL_ASSERT( this->doGetNumDefaultNodes( lock ) ==
                           _single_t::size_type{ 0 } );

            this->m_default_node_index.store( _single_t::UNDEFINED_INDEX );
        }

        return status;
    }
}

#endif /* C++, Host */

/* end: sixtracklib/common/control/node_set.cpp */
