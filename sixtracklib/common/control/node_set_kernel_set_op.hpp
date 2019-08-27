#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_SET_KERNEL_SET_OP_CXX_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_SET_KERNEL_SET_OP_CXX_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
        #include <mutex>
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

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_HOST_FN bool NodeSetKernelSet_can_select_node(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetSingle const& SIXTRL_RESTRICT_REF node_set,
        NodeSetSingle::node_index_t const new_node_index,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase const& SIXTRL_RESTRICT_REF kernel_set );

    SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    NodeSetKernelSet_select_node(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetSingle& SIXTRL_RESTRICT_REF node_set,
        NodeSetSingle::node_index_t const new_node_index,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase& SIXTRL_RESTRICT_REF kernel_set );

    /* --------------------------------------------------------------------- */

    SIXTRL_HOST_FN bool NodeSetKernelSet_can_change_selected_node_to(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetSingle const& SIXTRL_RESTRICT_REF node_set,
        NodeSetSingle::node_index_t const new_node_index,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase const& SIXTRL_RESTRICT_REF kernel_set );

    SIXTRL_HOST_FN bool NodeSetKernelSet_can_change_selected_node(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetBase const& SIXTRL_RESTRICT_REF node_set,
        NodeSetBase::node_index_t const current_node_index,
        NodeSetBase::node_index_t const new_node_index,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase const& SIXTRL_RESTRICT_REF kernel_set );

    SIXTRL_CXX_NAMESPACE::arch_status_t
    NodeSetKernelSet_change_selected_node_to(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetSingle& SIXTRL_RESTRICT_REF node_set,
        NodeSetSingle::node_index_t const new_node_index,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase& SIXTRL_RESTRICT_REF kernel_set );

    SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    NodeSetKernelSet_change_selected_node(
        NodeSetBase::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetBase& SIXTRL_RESTRICT_REF node_set,
        NodeSetBase::node_index_t const current_node_index,
        NodeSetBase::node_index_t const new_node_index,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase& SIXTRL_RESTRICT_REF kernel_set );

    /* --------------------------------------------------------------------- */

    SIXTRL_HOST_FN bool NodeSetKernelSet_can_switch_all_kernels(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetSingle const& SIXTRL_RESTRICT_REF node_set,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase const& SIXTRL_RESTRICT_REF kernel_set,
        KernelConfigKey& SIXTRL_RESTRICT_REF input_key );

    SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    NodeSetKernelSet_switch_all_kernels(
        NodeSetSingle::lock_t const& SIXTRL_RESTRICT_REF node_lock,
        NodeSetSingle& SIXTRL_RESTRICT_REF node_set,
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        KernelSetBase& SIXTRL_RESTRICT_REF kernel_set,
        KernelConfigKey& SIXTRL_RESTRICT_REF input_key );
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_SET_KERNEL_SET_OP_CXX_HPP__ */

/* end: sixtracklib/common/control/node_set_kernel_set_op.hpp */
