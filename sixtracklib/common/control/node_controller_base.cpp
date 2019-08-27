#include "sixtracklib/common/control/node_controller_base.hpp"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/common/control/node_info.h"
#include "sixtracklib/common/control/node_set_kernel_set_op.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    using _this_t = st::NodeControllerBase;

    constexpr _this_t::platform_id_t   _this_t::ILLEGAL_PLATFORM_ID;
    constexpr _this_t::device_id_t     _this_t::ILLEGAL_DEVICE_ID;
    constexpr _this_t::node_index_t    _this_t::UNDEFINED_INDEX;
    constexpr _this_t::node_str_role_t _this_t::NODE_ID_STR;
    constexpr _this_t::node_str_role_t _this_t::NODE_UNIQUE_ID_STR;

    /* ********************************************************************* */

    _this_t::size_type NodeControllerBase::numNodes( _this_t::node_lock_t const&
        SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT
    {
        _this_t::size_type const num_nodes = (
            ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr  ) )
                ? this->m_ptr_node_set->numNodes( node_lock )
                : _this_t::size_type{ 0 };

        SIXTRL_ASSERT( ( num_nodes == _this_t::size_type{ 0 } ) ||
            ( ( this->m_ptr_node_store != nullptr ) &&
              ( this->m_ptr_node_set == this->m_ptr_node_store->ptrNodeSetBase(
                  node_lock, this->m_node_set_id ) ) ) );

        return num_nodes;
    }

    _this_t::node_index_t NodeControllerBase::minNodeIndex( _this_t::node_lock_t
        const& SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT
    {
        _this_t::node_index_t const min_node_index = (
            ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr  ) )
                ? this->m_ptr_node_set->minNodeIndex( node_lock )
                : _this_t::UNDEFINED_INDEX;

        SIXTRL_ASSERT( ( min_node_index == _this_t::UNDEFINED_INDEX ) ||
            ( ( this->m_ptr_node_store != nullptr ) &&
              ( this->m_ptr_node_set == this->m_ptr_node_store->ptrNodeSetBase(
                  node_lock, this->m_node_set_id ) ) ) );

        return min_node_index;
    }

    _this_t::node_index_t NodeControllerBase::maxNodeIndex( _this_t::node_lock_t
        const& SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT
    {
        _this_t::node_index_t const max_node_index = (
            ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr  ) )
                ? this->m_ptr_node_set->maxNodeIndex( node_lock )
                : _this_t::UNDEFINED_INDEX;

        SIXTRL_ASSERT( ( max_node_index == _this_t::UNDEFINED_INDEX ) ||
            ( ( this->m_ptr_node_store != nullptr ) &&
              ( this->m_ptr_node_set == this->m_ptr_node_store->ptrNodeSetBase(
                  node_lock, this->m_node_set_id ) ) ) );

        return max_node_index;
    }

    _this_t::node_index_t NodeControllerBase::nodeIndex(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        _this_t::node_index_t const node_index = (
            ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr  ) )
                ? this->m_ptr_node_set->nodeIndex( node_lock, nn )
                : _this_t::UNDEFINED_INDEX;

        SIXTRL_ASSERT( ( node_index == _this_t::UNDEFINED_INDEX ) ||
            ( ( this->m_ptr_node_store != nullptr ) &&
              ( this->m_ptr_node_set == this->m_ptr_node_store->ptrNodeSetBase(
                  node_lock, this->m_node_set_id ) ) ) );

        return node_index;
    }

    _this_t::node_id_t const& NodeControllerBase::nodeId(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::size_type const nn ) const
    {
        if( !this->nodeCheckLock( node_lock ) )
            throw std::runtime_error( "unable to lock node store" );

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->m_ptr_node_set == this->m_ptr_node_store->ptrNodeSetBase(
                node_lock, this->m_node_set_id ) ) )
        {
            return this->m_ptr_node_set->nodeId( node_lock, nn );
        }

        throw std::runtime_error( "unable to retrieve NodeId() instance" );
    }

    _this_t::node_id_t const& NodeControllerBase::nodeIdByNodeIndex(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::node_index_t const index ) const
    {
        if( ( index != _this_t::UNDEFINED_INDEX ) &&
            ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr  ) )
        {
            SIXTRL_ASSERT(
              ( this->m_ptr_node_store != nullptr ) &&
              ( this->m_ptr_node_set == this->m_ptr_node_store->ptrNodeSetBase(
                  node_lock, this->m_node_set_id ) ) );

            return this->m_ptr_node_set->nodeIdByNodeIndex( node_lock, index );
        }

        throw std::runtime_error( "unable to find node_id for node_index" );
    }

    _this_t::c_node_id_t const* NodeControllerBase::ptrCNodeIdByNodeIndex(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        _this_t::c_node_id_t const* ptr_c_node_id = nullptr;

        if( ( index != _this_t::UNDEFINED_INDEX ) &&
            ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr  ) )
        {
            SIXTRL_ASSERT(
              ( this->m_ptr_node_store != nullptr ) &&
              ( this->m_ptr_node_set == this->m_ptr_node_store->ptrNodeSetBase(
                  node_lock, this->m_node_set_id ) ) );

            ptr_c_node_id = this->m_ptr_node_set->ptrCNodeIdByNodeIndex(
                node_lock, index );
        }

        return ptr_c_node_id;
    }

    _this_t::c_node_id_t const* NodeControllerBase::ptrCNodeId(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::size_type const nn ) const SIXTRL_NOEXCEPT
    {
        _this_t::c_node_id_t const* ptr_c_node_id = nullptr;

        if( ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr  ) )
        {
            SIXTRL_ASSERT(
              ( this->m_ptr_node_store != nullptr ) &&
              ( this->m_ptr_node_set == this->m_ptr_node_store->ptrNodeSetBase(
                  node_lock, this->m_node_set_id ) ) );

            ptr_c_node_id = this->m_ptr_node_set->ptrCNodeId( node_lock, nn );
        }

        return ptr_c_node_id;
    }

    _this_t::node_index_t const* NodeControllerBase::nodeIndicesBegin(
            _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock
        ) const SIXTRL_NOEXCEPT
    {
        _this_t::node_index_t const* begin_ptr = nullptr;

        if( ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr  ) )
        {
            SIXTRL_ASSERT(
              ( this->m_ptr_node_store != nullptr ) &&
              ( this->m_ptr_node_set == this->m_ptr_node_store->ptrNodeSetBase(
                  node_lock, this->m_node_set_id ) ) );

            begin_ptr = this->m_ptr_node_set->nodeIndicesBegin( node_lock );
        }

        return begin_ptr;
    }

    _this_t::node_index_t const* NodeControllerBase::nodeIndicesEnd(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock
        ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;
        _this_t::node_index_t const* end_ptr = nullptr;

        if( ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr  ) )
        {
            SIXTRL_ASSERT(
              ( this->m_ptr_node_store != nullptr ) &&
              ( this->m_ptr_node_set == this->m_ptr_node_store->ptrNodeSetBase(
                  node_lock, this->m_node_set_id ) ) );

            end_ptr = this->m_ptr_node_set->nodeIndicesEnd( node_lock );
        }

        return end_ptr;
    }

    /* --------------------------------------------------------------------- */

    bool NodeControllerBase::isAvailable(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::node_index_t const node_index ) const SIXTRL_NOEXCEPT
    {
        return ( ( node_index != _this_t::UNDEFINED_INDEX ) &&
                 ( this->nodeCheckLock( node_lock ) ) &&
                 ( this->m_ptr_node_store != nullptr ) &&
                 ( this->m_ptr_node_set != nullptr ) &&
                 ( this->m_ptr_node_set->available( node_lock, node_index ) ) );
    }

    bool NodeControllerBase::hasSelectedNode( _this_t::node_lock_t const&
        SIXTRL_RESTRICT_REF node_lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->nodeCheckLock( node_lock ) ) &&
                 ( this->m_ptr_node_store != nullptr ) &&
                 ( this->m_ptr_node_set != nullptr ) &&
                 ( this->m_ptr_node_set->selectedNodeIndex() !=
                     _this_t::UNDEFINED_INDEX ) );
    }

    bool NodeControllerBase::isSelected(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        return ( ( index != _this_t::UNDEFINED_INDEX ) &&
                 ( this->nodeCheckLock( node_lock ) ) &&
                 ( this->m_ptr_node_store != nullptr ) &&
                 ( this->m_ptr_node_set   != nullptr ) &&
                 ( this->m_ptr_node_set->isSelected( node_lock, index ) ) );
    }

    bool NodeControllerBase::canSelectNode(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::node_index_t const index ) const
    {
        bool can_select_node = false;

        if( ( this->kernelLockable() != nullptr ) &&
            ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->m_ptr_node_store != nullptr ) )
        {
            _this_t::kernel_lock_t kernel_lock(
                *this->kernelLockable(), std::try_to_lock);

            if( ( this->ptrKernelConfigStore() != nullptr ) &&
                ( this->ptrConstKernelSet( kernel_lock ) != nullptr ) )
            {
                can_select_node = st::NodeSetKernelSet_can_select_node(
                    node_lock,   *this->m_ptr_node_set, index,
                        kernel_lock, *this->ptrConstKernelSet( kernel_lock ) );
            }
        }

        return can_select_node;
    }

    _this_t::status_t NodeControllerBase::selectNode(
        _this_t::node_lock_t& SIXTRL_RESTRICT_REF node_lock,
        _this_t::node_index_t const node_index )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->kernelLockable() != nullptr ) &&
            ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->m_ptr_node_store != nullptr ) )
        {
            _this_t::kernel_lock_t kernel_lock( *this->kernelLockable() );

            if( ( this->ptrKernelConfigStore() != nullptr ) &&
                ( this->ptrKernelSet( kernel_lock ) != nullptr ) )
            {
                status = st::NodeSetKernelSet_select_node(
                    node_lock, *this->m_ptr_node_set, node_index,
                        kernel_lock, *this->ptrKernelSet( kernel_lock ) );
            }
        }

        return status;
    }

    bool NodeControllerBase::isDefault(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::node_index_t const index ) const SIXTRL_NOEXCEPT
    {
        return ( ( index != _this_t::UNDEFINED_INDEX ) &&
                 ( this->nodeCheckLock( node_lock )  ) &&
                 ( this->m_ptr_node_store != nullptr ) &&
                 ( this->m_ptr_node_set   != nullptr ) &&
                 ( this->m_ptr_node_set->isDefault( node_lock, index ) ) );
    }

    bool NodeControllerBase::canChangeSelectedNodeTo(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::node_index_t const new_node_index ) const
    {
        bool can_change_node = false;

        if( ( this->kernelLockable() != nullptr ) &&
            ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->m_ptr_node_store != nullptr ) )
        {
            _this_t::kernel_lock_t kernel_lock( *this->kernelLockable() );

            if( ( this->ptrKernelConfigStore() != nullptr ) &&
                ( this->ptrConstKernelSet( kernel_lock ) != nullptr ) )
            {
                can_change_node = st::NodeSetKernelSet_can_change_selected_node_to(
                    node_lock,   *this->m_ptr_node_set, new_node_index,
                        kernel_lock, *this->ptrConstKernelSet( kernel_lock ) );
            }
        }

        return can_change_node;
    }

    bool NodeControllerBase::canChangeSelectedNode(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::node_index_t const current_node_index,
        _this_t::node_index_t const new_node_index ) const
    {
        bool can_change_node = false;

        if( ( this->kernelLockable() != nullptr ) &&
            ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->m_ptr_node_store != nullptr ) )
        {
            _this_t::kernel_lock_t kernel_lock( *this->kernelLockable() );

            if( ( this->ptrKernelConfigStore() != nullptr ) &&
                ( this->ptrConstKernelSet( kernel_lock ) != nullptr ) )
            {
                can_change_node = st::NodeSetKernelSet_can_change_selected_node(
                    node_lock,   *this->m_ptr_node_set, current_node_index,
                        new_node_index, kernel_lock,
                            *this->ptrConstKernelSet( kernel_lock ) );
            }
        }

        return can_change_node;
    }

    _this_t::status_t NodeControllerBase::changeSelectedNodeTo(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::node_index_t const new_node_index )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->kernelLockable() != nullptr ) &&
            ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->m_ptr_node_store != nullptr ) )
        {
            _this_t::kernel_lock_t kernel_lock( *this->kernelLockable() );

            if( ( this->ptrKernelConfigStore() != nullptr ) &&
                ( this->ptrKernelSet( kernel_lock ) != nullptr ) )
            {
                status = st::NodeSetKernelSet_change_selected_node_to(
                    node_lock, *this->m_ptr_node_set, new_node_index,
                        kernel_lock, *this->ptrKernelSet( kernel_lock ) );
            }
        }

        return status;
    }

    _this_t::status_t NodeControllerBase::changeSelectedNode(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock,
        _this_t::node_index_t const current_node_index,
        _this_t::node_index_t const new_node_index )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->kernelLockable() != nullptr ) &&
            ( this->nodeCheckLock( node_lock ) ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->m_ptr_node_store != nullptr ) )
        {
            _this_t::kernel_lock_t kernel_lock( *this->kernelLockable() );

            if( ( this->ptrKernelConfigStore() != nullptr ) &&
                ( this->ptrKernelSet( kernel_lock ) != nullptr ) )
            {
                status = st::NodeSetKernelSet_change_selected_node(
                    node_lock, *this->m_ptr_node_set, current_node_index,
                        new_node_index, kernel_lock,
                            *this->ptrKernelSet( kernel_lock ) );
            }
        }

        return status;
    }

    _this_t::status_t NodeControllerBase::syncWithNodeSet(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF node_lock )
    {
        return this->doSyncWithNodeSet( node_lock );
    }

    /* --------------------------------------------------------------------- */

    NodeControllerBase::NodeControllerBase(
        _this_t::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT config_str ) :
        st::ControllerBase( arch_id, config_str ),
        m_my_own_node_store( nullptr ), m_ptr_node_store( nullptr ),
        m_ptr_node_set( nullptr ),
        m_expected_node_set_sync_id( _this_t::ILLEGAL_SYNC_ID_VALUE ),
        m_node_set_id( _this_t::ILLEGAL_NODE_SET_ID )
    {
        this->doSetUsesNodesFlag( true );
    }

    /* --------------------------------------------------------------------- */

    void NodeControllerBase::doClear(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        _controller_base_t::doClear( lock );
    }

    _this_t::status_t NodeControllerBase::doSyncWithNodeSet(
        _this_t::node_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        ( void )lock;
        return st::ARCH_STATUS_SUCCESS;
    }

    bool NodeControllerBase::doCheckIfCanChangeAllKernelsWithKey(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        _this_t::kernel_config_key_t& SIXTRL_RESTRICT_REF new_key ) const
    {
        bool can_change_all_kernels = false;

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->ptrKernelConfigStore() != nullptr ) &&
            ( this->checkKernelLock( kernel_lock ) ) )
        {
            _this_t::kernel_lock_t node_lock( *this->nodeLockable() );

            can_change_all_kernels = st::NodeSetKernelSet_can_switch_all_kernels(
                node_lock, *this->m_ptr_node_set, kernel_lock,
                    *this->ptrConstKernelSet( kernel_lock ), new_key );
        }

        return can_change_all_kernels;
    }

    _this_t::status_t NodeControllerBase::doChangeAllKernelsWithKey(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        _this_t::kernel_config_key_t& SIXTRL_RESTRICT_REF new_key )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) &&
            ( this->m_ptr_node_set != nullptr ) &&
            ( this->ptrKernelConfigStore() != nullptr ) &&
            ( this->checkKernelLock( kernel_lock ) ) )
        {
            _this_t::kernel_lock_t node_lock( *this->nodeLockable() );

            status = st::NodeSetKernelSet_switch_all_kernels(
                node_lock, *this->m_ptr_node_set, kernel_lock,
                    *this->ptrKernelSet( kernel_lock ), new_key );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _this_t::status_t NodeControllerBase::doInitNodeStore(
        _this_t::node_lock_t const& SIXTRL_RESTRICT node_lock,
        _this_t::node_store_t* SIXTRL_RESTRICT ext_node_store )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( ext_node_store != nullptr ) &&
            ( ext_node_store->checkLock( node_lock ) ) )
        {
            SIXTRL_ASSERT(
                ( this->m_my_own_node_store.get() == nullptr ) &&
                ( this->m_ptr_node_store == nullptr ) &&
                ( this->m_ptr_node_set == nullptr ) &&
                ( this->m_node_set_id == _this_t::ILLEGAL_NODE_SET_ID ) );

            this->m_ptr_node_store = ext_node_store;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _this_t::status_t NodeControllerBase::doInitNodeStore(
        _this_t::node_lock_t const& SIXTRL_RESTRICT node_lock,
        _this_t::ptr_node_store_t&& node_store )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( node_store.get() != nullptr ) &&
            ( node_store->checkLock( node_lock ) ) )
        {
            SIXTRL_ASSERT(
                ( this->m_my_own_node_store.get() == nullptr ) &&
                ( this->m_ptr_node_store == nullptr ) &&
                ( this->m_ptr_node_set == nullptr ) &&
                ( this->m_node_set_id == _this_t::ILLEGAL_NODE_SET_ID ) );

            this->m_ptr_node_store = node_store.get();
            this->m_my_own_node_store = std::move( node_store );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _this_t::status_t NodeControllerBase::doInitNodeSet(
        _this_t::node_lock_t const& SIXTRL_RESTRICT node_lock,
        _this_t::node_set_id_t const node_set_id )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->checkLock( node_lock ) ) &&
            ( this->m_ptr_node_set == nullptr ) &&
            ( this->m_node_set_id  == _this_t::ILLEGAL_NODE_SET_ID ) &&
            ( this->m_ptr_node_store->hasNodeSet( node_lock, node_set_id ) ) )
        {
            _this_t::node_set_base_t* ptr_node_set_base =
                this->m_ptr_node_store->ptrNodeSetBase( node_lock, node_set_id );

            if( ( ptr_node_set_base != nullptr ) &&
                ( ptr_node_set_base->isSingleNodeSet() ) )
            {
                _this_t::node_set_t* ptr_node_set = static_cast<
                    _this_t::node_set_t* >( ptr_node_set_base );

                this->m_ptr_node_set = ptr_node_set;
                this->m_node_set_id  = node_set_id;
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }
}

/* end: sixtracklib/common/control/node_controller_base.cpp */
