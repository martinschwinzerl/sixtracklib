#include "sixtracklib/common/control/kernel_set.h"
#include "sixtracklib/common/control/kernel_set.hpp"

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <memory>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/architecture/definitions.h"
    #include "sixtracklib/common/architecture/architecture.hpp"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/kernel_config_key.hpp"
    #include "sixtracklib/common/control/kernel_config_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;
using _set_t = st::KernelSetBase;

namespace SIXTRL_CXX_NAMESPACE
{

    ::NS(KernelSetBase)* NS(KernelSetBase_new)(
        ::NS(arch_id_t) const arch_id,
        ::NS(KernelConfigStore)* SIXTRL_RESTRICT kernel_conf_store )
    {
        return ( kernel_conf_store != nullptr )
            ? new st::KernelSetBase( arch_id, *kernel_conf_store )
            : nullptr;
    }

    ::NS(KernelSetBase)* NS(KernelSetBase_new_detailed)(
        ::NS(arch_id_t) const arch_id,
        ::NS(KernelConfigStore)* SIXTRL_RESTRICT kernel_conf_store,
        ::NS(arch_size_t) const num_purposes,
        ::NS(kernel_purpose_t) const* SIXTRL_RESTRICT purposes_begin )
    {
        return ( kernel_conf_store != nullptr )
            ? new st::KernelSetBase( arch_id, *kernel_conf_store,
                    num_purposes, purposes_begin )
            : nullptr;
    }

    void NS(KernelSet_delete)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set )
    {
        delete set;
    }

    /* ----------------------------------------------------------------- */

    bool NS(KernelSet_is_for_controllers)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set )
    {
        return ( ( set != nullptr ) && ( set->isForControllers() ) );
    }

    bool NS(KernelSet_is_for_track_jobs)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set )
    {
        return ( ( set != nullptr ) && ( set->isForTrackJobs() ) );
    }

    /* ----------------------------------------------------------------- */

    ::NS(arch_size_t) NS(KernelSet_get_num_of_purposes)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set )
    {
        return ( set != nullptr ) ? set->numPurposes() : st::arch_size_t{ 0 };
    }

    ::NS(arch_size_t) NS(KernelSet_get_num_of_purposes_for_kernel_config_id)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        ::NS(ctrl_kernel_id_t) const kernel_config_id )
    {
        return ( set != nullptr )
            ? set->numPurposes( kernel_config_id ) : st::arch_size_t{ 0 };
    }

    ::NS(arch_size_t) NS(KernelSet_get_num_of_pinned_purposes)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set )
    {
        return ( set != nullptr )
            ? set->numPinnedPurposes() : st::arch_size_t{ 0 };
    }

    /* ----------------------------------------------------------------- */

    ::NS(KernelConfigBase) const*
    NS(KernelSet_get_ptr_const_kernel_config_base)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( set != nullptr )
            ? set->ptrKernelConfigBase( purpose ) : nullptr;
    }

    ::NS(KernelConfigBase)* NS(KernelSet_get_ptr_kernel_config_base)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( set != nullptr )
            ? set->ptrKernelConfigBase( purpose ) : nullptr;
    }

    /* ----------------------------------------------------------------- */

    ::NS(ctrl_kernel_id_t) NS(KernelSet_get_kernel_config_id)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( set != nullptr )
            ? set->kernelConfigId( purpose )
            : _set_t::ILLEGAL_KERNEL_CONFIG_ID;
    }

    bool NS(KernelSet_has_kernel_config_id)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        ::NS(ctrl_kernel_id_t) const kernel_config_id )
    {
        return ( ( set != nullptr ) &&
                 ( set->hasKernelConfigId( kernel_config_id ) ) );
    }

    bool NS(KernelSet_is_purpose_associated_with_kernel_config_id)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        ::NS(ctrl_kernel_id_t) const kernel_config_id,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( ( set != nullptr ) &&
                 ( set->isPurposeAssociatedWithKernelConfigId(
                    kernel_config_id, purpose ) ) );
    }

    ::NS(KernelConfigKey) const* NS(KernelSet_get_ptr_const_kernel_konfig_key)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        _set_t::lock_t const lock( *set->lockable() );

        return ( set != nullptr )
            ? &set->kernelConfigKey( lock, purpose ) : nullptr;
    }

    /* ----------------------------------------------------------------- */

    bool NS(KernelSet_requires)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( ( set != nullptr ) && ( set->requires( purpose ) ) );
    }

    bool NS(KernelSet_is_pinned)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( ( set != nullptr ) && ( set->pinned( purpose ) ) );
    }

    /* ----------------------------------------------------------------- */

    bool NS(KernelSet_is_available)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( ( set != nullptr ) && ( set->available( purpose ) ) );
    }

    bool NS(KernelSet_are_all_available)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set )
    {
        return ( ( set != nullptr ) && ( set->available() ) );
    }

    bool NS(KernelSet_has_kernel_config_key)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
    {
        return ( ( set != nullptr ) && ( key != nullptr ) &&
                 ( set->hasKernelConfigKey( *key ) ) );
    }

    /* ----------------------------------------------------------------- */

    bool NS(KernelSet_can_switch_kernel)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
    {
        return ( ( set != nullptr ) && ( key != nullptr ) &&
                ( set->canSwitchKernel( *key ) ) );
    }

    bool NS(KernelSet_can_switch_all_kernels)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        ::NS(KernelConfigKey)* SIXTRL_RESTRICT key )
    {
        return ( ( set != nullptr ) && ( key != nullptr ) &&
                 ( set->canSwitchKernels( *key ) ) );
    }

    /* ----------------------------------------------------------------- */

    ::NS(arch_status_t) NS(KernelSet_switch_kernel(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set,
        const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key,
        bool const is_pinned_flag )
    {
        return ( set != nullptr ) && ( key != nullptr ) )
            ? set->switchKernel( *key, is_pinned_flag )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    ::NS(arch_status_t) NS(KernelSet_switch_kernels)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set,
        const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
    {
        return ( ( set != nullptr ) && ( key != nullptr ) )
            ? set->switchKernels( *key ) : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* ----------------------------------------------------------------- */

    ::NS(arch_status_t) NS(KernelSet_sync_with_store)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set,
        bool const perform_config_update_if_required )
    {
        return ( set != nullptr )
            ? set->syncWithStore( perform_config_update_if_required )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    ::NS(kernel_op_flags_t) NS(KernelSet_get_kernel_op_flags)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set )
    {
        return ( set != nullptr )
            ? set->kernelOpFlags() : st::KERNEL_OP_FLAGS_NONE;
    }

    /* ----------------------------------------------------------------- */

    bool NS(KernelSet_config_needs_update)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( ( set != nullptr ) && ( set->configNeedsUpdate( purpose ) ) );
    }

    ::NS(arch_status_t) NS(KernelSet_update_config)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( set != nullptr )
            ? set->updateConfig( purpose ) : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    ::NS(arch_status_t) NS(KernelSet_update_all_configs)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set )
    {
        return ( set != nullptr )
            ? set->updateAllConfigs() : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* ----------------------------------------------------------------- */

    bool NS(KernelSet_is_ready)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( ( set != nullptr ) && ( set->ready( purpose ) ) );
    }

    bool NS(KernelSet_is_ready_by_key)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT key )
    {
        return ( ( set != nullptr ) && ( key != nullptr ) &&
                 ( set->ready( *key ) ) );
    }

    bool NS(KernelSet_are_ready)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set )
    {
        return ( ( set != nullptr ) && ( set->ready() ) );
    }

    /* ----------------------------------------------------------------- */

    ::NS(arch_status_t) NS(KernelSet_reset)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set )
    {
        return ( set != nullptr )
            ? set->reset() : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    ::NS(arch_status_t) NS(KernelSet_reset_for_purpose)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( set != nullptr )
             ? set->reset( purpose ) : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    ::NS(arch_status_t) NS(KernelSet_reset_kernel_config)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set,
        ::NS(ctrl_kernel_id_t) const kernel_config_id )
    {
        return ( set != nullptr )
            ? set->reset( kernel_config_id ) : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* ----------------------------------------------------------------- */

    ::NS(arch_status_t) NS(KernelSet_add_purpose)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( set != nullptr )
            ? set->addPurpose( purpose ) : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    ::NS(arch_status_t) NS(KernelSet_add_purposes)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set,
        ::NS(arch_size_t) const num_purposes,
        ::NS(kernel_purpose_t) const* SIXTRL_RESTRICT purposes_begin )
    {
        return ( set != nullptr )
            ? set->addPurposes( num_purposes, purposes_begin )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    ::NS(arch_status_t) NS(KernelSet_remove_purpose)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set,
        ::NS(kernel_purpose_t) const purpose )
    {
        return ( set != nullptr )
            ? set->removePurpose( purpose ) : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_UINT64_T NS(KernelSet_get_sync_id_value)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set )
    {
        return ( set != nullptr )
            ? set->syncIdValue() : _set_t::ILLEGAL_SYNC_ID_VALUE;
    }

    bool NS(KernelSet_is_sync_with)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set,
        SIXTRL_UINT64_T const sync_id_value )
    {
        return ( ( set != nullptr ) && ( set->isSyncWith( sync_id_value ) ) );
    }

    /* ----------------------------------------------------------------- */

    ::NS(KernelConfigStore) const*
    NS(KernelSet_get_const_kernel_config_store)(
        const ::NS(KernelSetBase) *const SIXTRL_RESTRICT set )
    {
        return ( set != nullptr ) ? &set->kernelConfigStore() : nullptr;
    }

    ::NS(KernelConfigStore)* NS(KernelSet_get_kernel_config_store)(
        ::NS(KernelSetBase)* SIXTRL_RESTRICT set )
    {
        return ( set != nullptr ) ? &set->kernelConfigStore() : nullptr;
    }
}

/* end: sixtracklib/common/control/kernel_set_c99.cpp */
