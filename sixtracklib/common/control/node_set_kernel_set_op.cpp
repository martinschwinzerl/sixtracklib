#include "sixtracklib/common/control/node_set_kernel_set_op.hpp"

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
        #include <mutex>
        #include <stdexcept>
        #include <thread>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_store.hpp"
    #include "sixtracklib/common/control/node_set.hpp"
    #include "sixtracklib/common/control/kernel_config_store.hpp"
    #include "sixtracklib/common/control/kernel_config_key.hpp"
    #include "sixtracklib/common/control/kernel_set.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    bool NodeSetKernelSet_can_select_node(
        st::NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        st::NodeSetSingle const& SIXTRL_RESTRICT_REF node_set,
        st::NodeSetSingle::node_index_t const node_index,
        st::KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        st::KernelSetBase const& SIXTRL_RESTRICT_REF kernel_set )
    {
        using _node_set_t = st::NodeSetSingle;
        bool can_select_node = false;

        if( ( node_index != _node_set_t::UNDEFINED_INDEX ) &&
            ( kernel_set.checkLock( kernel_lock ) ) &&
            ( node_set.checkLock( node_lock ) ) &&
            ( node_set.canSelectNode( node_lock, node_index ) ) )
        {
            st::KernelConfigKey input_key( static_cast<
                st::KernelSetBase const& >( kernel_set ).currentKernelConfigKey(
                    kernel_lock ) );

            input_key.setNodeId( node_set.nodeIdByNodeIndex(
                node_lock, node_index ) );

            if( input_key.nodeId().valid() )
                can_select_node = kernel_set.canSwitchKernels( input_key );
        }

        return can_select_node;
    }

    st::arch_status_t NodeSetKernelSet_select_node(
        st::NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        st::NodeSetSingle& SIXTRL_RESTRICT_REF node_set,
        st::NodeSetSingle::node_index_t const new_node_index,
        st::KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        st::KernelSetBase& SIXTRL_RESTRICT_REF kernel_set )
    {
        using _node_set_t = st::NodeSetSingle;
        using _key_t      = st::KernelConfigKey;

        _node_set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( new_node_index != _node_set_t::UNDEFINED_INDEX ) &&
            ( kernel_set.checkLock( kernel_lock ) ) &&
            ( node_set.checkLock( node_lock ) ) )
        {
            _key_t input_key( static_cast< st::KernelSetBase const& >(
                kernel_set ).currentKernelConfigKey( kernel_lock ) );

            input_key.setNodeId( node_set.nodeIdByNodeIndex(
                node_lock, new_node_index ) );

            if( ( input_key.nodeId().valid() ) &&
                ( kernel_set.canSwitchKernels( kernel_lock, input_key ) ) &&
                ( node_set.canSelectNode( node_lock, new_node_index ) ) )
            {
                status = kernel_set.switchKernels( kernel_lock, input_key );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = node_set.selectNode( node_lock, new_node_index );
                }

                if( status != st::ARCH_STATUS_SUCCESS )
                {
                   throw std::runtime_error( "unable to select node" );
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool NodeSetKernelSet_can_change_selected_node_to(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetSingle const& SIXTRL_RESTRICT_REF node_set,
        NodeSetSingle::node_index_t const new_node_index,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase const& SIXTRL_RESTRICT_REF kernel_set )
    {
        using _node_set_t = st::NodeSetSingle;
        bool can_change_to_node = false;

        if( ( new_node_index != _node_set_t::UNDEFINED_INDEX ) &&
            ( kernel_set.checkLock( kernel_lock ) ) &&
            ( node_set.checkLock( node_lock ) ) &&
            ( node_set.canChangeSelectedNodeTo( node_lock, new_node_index ) ) )
        {
            st::KernelConfigKey key( static_cast< st::KernelSetBase const& >(
                kernel_set ).currentKernelConfigKey( kernel_lock ) );

            key.setNodeId( node_set.nodeIdByNodeIndex(
                node_lock, new_node_index ) );

            if( key.nodeId().valid() )
                can_change_to_node = kernel_set.canSwitchKernels( key );
        }

        return can_change_to_node;
    }

    bool NodeSetKernelSet_can_change_selected_node(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetBase const& SIXTRL_RESTRICT_REF node_set,
        NodeSetBase::node_index_t const current_node_index,
        NodeSetBase::node_index_t const new_node_index,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase const& SIXTRL_RESTRICT_REF kernel_set )
    {
        using _node_set_t = st::NodeSetSingle;
        bool can_change_to_node = false;

        if( ( new_node_index != _node_set_t::UNDEFINED_INDEX ) &&
            ( kernel_set.checkLock( kernel_lock ) ) &&
            ( node_set.checkLock( node_lock ) ) &&
            ( node_set.canChangeSelectedNodeTo(
                node_lock, current_node_index, new_node_index ) ) &&
            ( ( current_node_index == _node_set_t::UNDEFINED_INDEX ) ||
              ( node_set.isSelected( node_lock, current_node_index ) ) ) )
        {
            st::KernelConfigKey key( static_cast< st::KernelSetBase const& >(
                kernel_set ).currentKernelConfigKey( kernel_lock ) );

            key.setNodeId( node_set.nodeIdByNodeIndex(
                node_lock, new_node_index ) );

            if( key.nodeId().valid() )
                can_change_to_node = kernel_set.canSwitchKernels( key );
        }

        return can_change_to_node;
    }

    st::arch_status_t NodeSetKernelSet_change_selected_node_to(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetSingle& SIXTRL_RESTRICT_REF node_set,
        NodeSetSingle::node_index_t const new_node_index,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase& SIXTRL_RESTRICT_REF kernel_set )
    {
        using _node_set_t = st::NodeSetSingle;
        using _key_t = st::KernelConfigKey;

        _node_set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( new_node_index != _node_set_t::UNDEFINED_INDEX ) &&
            ( kernel_set.checkLock( kernel_lock ) ) &&
            ( node_set.checkLock( node_lock ) ) )
        {
            _node_set_t::node_index_t const current_node_index =
                node_set.selectedNodeIndex();

            _key_t const saved_key( static_cast< st::KernelSetBase const& >(
                kernel_set ).currentKernelConfigKey( kernel_lock ) );

            _key_t input_key( saved_key );

            input_key.setNodeId( node_set.nodeIdByNodeIndex(
                node_lock, new_node_index ) );

            if( ( input_key.nodeId().valid() ) &&
                ( kernel_set.canSwitchKernels( kernel_lock, input_key ) ) &&
                ( node_set.canSelectNode( node_lock, new_node_index ) ) &&
                ( node_set.isSelected( current_node_index ) ) )
            {
                status = kernel_set.switchKernels( kernel_lock, input_key );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = node_set.changeSelectedNodeTo(
                        node_lock, new_node_index );

                    if( status != st::ARCH_STATUS_SUCCESS )
                    {
                        node_set.changeSelectedNodeTo(
                            node_lock, new_node_index );
                    }
                }
                else
                {
                    kernel_set.switchKernels( kernel_lock, saved_key );
                }

                if( status != st::ARCH_STATUS_SUCCESS )
                {
                   throw std::runtime_error( "unable to change selected node" );
                }
            }
        }

        return status;
    }

    st::arch_status_t NodeSetKernelSet_change_selected_node(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetBase& SIXTRL_RESTRICT_REF node_set,
        NodeSetBase::node_index_t const current_node_index,
        NodeSetBase::node_index_t const new_node_index,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase& SIXTRL_RESTRICT_REF kernel_set )
    {
        using _node_set_t = st::NodeSetSingle;
        using _key_t = st::KernelConfigKey;

        _node_set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( new_node_index != _node_set_t::UNDEFINED_INDEX ) &&
            ( kernel_set.checkLock( kernel_lock ) ) &&
            ( node_set.checkLock( node_lock ) ) )
        {
            _key_t const saved_key( static_cast< st::KernelSetBase const& >(
                kernel_set ).currentKernelConfigKey( kernel_lock ) );

            _key_t input_key( saved_key );

            input_key.setNodeId( node_set.nodeIdByNodeIndex(
                node_lock, new_node_index ) );

            if( ( input_key.nodeId().valid() ) &&
                ( kernel_set.canSwitchKernels( kernel_lock, input_key ) ) &&
                ( node_set.canSelectNode( node_lock, new_node_index ) ) &&
                ( ( current_node_index == _node_set_t::UNDEFINED_INDEX ) ||
                  ( node_set.isSelected( current_node_index ) ) ) )
            {
                status = kernel_set.switchKernels( kernel_lock, input_key );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = node_set.changeSelectedNodeTo(
                        node_lock, current_node_index, new_node_index );

                    if( status != st::ARCH_STATUS_SUCCESS )
                    {
                        node_set.changeSelectedNodeTo(
                            node_lock, new_node_index, current_node_index );
                    }
                }
                else
                {
                    kernel_set.switchKernels( kernel_lock, saved_key );
                }

                if( status != st::ARCH_STATUS_SUCCESS )
                {
                   throw std::runtime_error( "unable to change selected node" );
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool NodeSetKernelSet_can_switch_all_kernels(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetSingle const& SIXTRL_RESTRICT_REF node_set,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase const& SIXTRL_RESTRICT_REF kernel_set,
        KernelConfigKey& SIXTRL_RESTRICT_REF input_key )
    {
        bool can_change_all_kernels = false;
        using _node_set_t = st::NodeSetSingle;

        if( ( input_key.nodeId().valid() ) &&
            ( node_set.checkLock( node_lock ) ) &&
            ( node_set.ptrNodeStore() != nullptr ) &&
            ( kernel_set.checkLock( kernel_lock ) ) &&
            ( kernel_set.canSwitchKernels( kernel_lock, input_key ) ) )
        {
            _node_set_t::node_index_t const new_node_index =
                node_set.ptrNodeStore()->findNodeIndex(
                    node_lock, input_key.nodeId() );

            if( new_node_index != _node_set_t::UNDEFINED_INDEX )
            {
                _node_set_t::node_index_t const current_node_index =
                    node_set.selectedNodeIndex();

                if( current_node_index == _node_set_t::UNDEFINED_INDEX )
                {
                    can_change_all_kernels = node_set.canSelectNode(
                        node_lock, new_node_index );
                }
                else
                {
                    can_change_all_kernels = node_set.canChangeSelectedNodeTo(
                        node_lock, current_node_index, new_node_index );
                }
            }
        }

        return can_change_all_kernels;
    }

    st::arch_status_t NodeSetKernelSet_switch_all_kernels(
        st::NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        st::NodeSetSingle& SIXTRL_RESTRICT_REF node_set,
        st::KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        st::KernelSetBase& SIXTRL_RESTRICT_REF kernel_set,
        st::KernelConfigKey& SIXTRL_RESTRICT_REF input_key )
    {
        using _node_set_t = st::NodeSetSingle;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( input_key.nodeId().valid() ) &&
            ( node_set.checkLock( node_lock ) ) &&
            ( node_set.ptrNodeStore() != nullptr ) &&
            ( kernel_set.checkLock( kernel_lock ) ) &&
            ( kernel_set.canSwitchKernels( kernel_lock, input_key ) ) )
        {
            _node_set_t::node_index_t const new_node_index =
                node_set.ptrNodeStore()->findNodeIndex(
                    node_lock, input_key.nodeId() );

            if( new_node_index != _node_set_t::UNDEFINED_INDEX )
            {
                _node_set_t::node_index_t const current_node_index =
                    node_set.selectedNodeIndex();

                if( current_node_index == _node_set_t::UNDEFINED_INDEX )
                {
                    status = node_set.selectNode( node_lock, new_node_index );
                }
                else
                {
                    status = node_set.changeSelectedNodeTo( node_lock,
                            current_node_index, new_node_index );
                }
            }
        }

        return status;
    }
}

#endif /* C++, host */

/* end: /common/control/node_set_kernel_set_op.cpp */
