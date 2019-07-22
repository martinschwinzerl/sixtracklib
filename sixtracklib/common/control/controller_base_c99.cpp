#include "sixtracklib/common/control/controller_base.h"

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )

#include <cstddef>
#include <cstdlib>
#include <cstdint>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/controller_base.hpp"
#include "sixtracklib/common/control/argument_base.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

/* ------------------------------------------------------------------------- */

void NS(Controller_delete)( ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl )
{
    if( ctrl != nullptr ) delete ctrl;
    return;
}

void NS(Controller_clear)( ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl )
{
    if( ctrl != nullptr ) ctrl->clear();
    return;
}

/* ------------------------------------------------------------------------- */

::NS(arch_id_t) NS(Controller_get_arch_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr )
        ? ctrl->archId() : ::NS(ARCHITECTURE_ILLEGAL);
}

bool NS(Controller_has_arch_string)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( ctrl != nullptr ) && ( ctrl->hasArchStr() ) );
}

char const* NS(Controller_get_arch_string)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr ) ? ctrl->ptrArchStr() : nullptr;
}

/* ------------------------------------------------------------------------- */

bool NS(Controller_has_config_string)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr ) ? ctrl->hasConfigStr() : false;
}

char const* NS(Controller_get_config_string)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr ) ? ctrl->ptrConfigStr() : nullptr;
}

/* ------------------------------------------------------------------------- */

bool NS(Controller_uses_nodes)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( ctrl != nullptr ) && ( ctrl->usesNodes() ) );
}

/* ------------------------------------------------------------------------- */

bool NS(Controller_has_name)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( ctrl != nullptr ) && ( ctrl->hasName() ) );
}

char const* NS(Controller_get_name_str)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr ) ? ctrl->ptrNameStr() : nullptr;
}

void NS(Controller_set_name)( ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT ctrl_name )
{
    if( ctrl != nullptr ) ? ctrl->setName( ctrl_name );
}

/* ------------------------------------------------------------------------- */

bool NS(Controller_has_default_kernel_config_str)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( ctrl != nullptr ) && ( ctrl->hasDefaultKernelConfigStr() ) );
}

char const* NS(Controller_get_default_kernel_config_str)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr ) ? ctrl->ptrDefaultKernelConfigStr() : nullptr;
}

void NS(Controller_set_default_kernel_config_str)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT default_kernel_config_str )
{
    if( ctrl != nullptr )
    {
        ctrl->setDefaultKernelConfigStr( default_kernel_config_str );
    }
}

/* ------------------------------------------------------------------------- */

::NS(arch_status_t) NS(Controller_send_detailed)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    ::NS(ArgumentBase)* SIXTRL_RESTRICT destination,
    void const* SIXTRL_RESTRICT source, NS(arch_size_t) const src_len )
{
    return ( ctrl != nullptr )
        ? ctrl->send( destination, source, src_len )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(arch_status_t) NS(Controller_send_buffer)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    ::NS(ArgumentBase)* SIXTRL_RESTRICT destination,
    ::NS(Buffer) const* SIXTRL_RESTRICT source )
{
    return ( ctrl != nullptr )
        ? ctrl->send( destination, source )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(arch_status_t) NS(Controller_receive_detailed)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    void* SIXTRL_RESTRICT destination,
    ::NS(arch_size_t) const destination_capacity,
    ::NS(ArgumentBase)* SIXTRL_RESTRICT source )
{
    return ( ctrl != nullptr )
        ? ctrl->receive( destination, destination_capacity, source )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(arch_status_t) NS(Controller_receive_buffer)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    ::NS(Buffer)* SIXTRL_RESTRICT destination,
    ::NS(ArgumentBase)* SIXTRL_RESTRICT source )
{
    return ( ctrl != nullptr )
        ? ctrl->receive( destination, source )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(Controller_is_cobjects_buffer_arg_remapped)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    ::NS(ArgumentBase)* SIXTRL_RESTRICT cobject_buffer_arg )
{
    return ( ( ctrl != nullptr ) &&
             ( ctrl->isRemapped( cobject_buffer_arg ) ) );
}

::NS(arch_status_t) NS(Controller_remap_cobjects_buffer_arg)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    ::NS(ArgumentBase)* SIXTRL_RESTRICT arg )
{
    return ( ctrl != nullptr )
        ? ctrl->remap( arg ) : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(Controller_is_ready_to_run_kernel)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( ctrl != nullptr ) && ( ctrl->readyForRunningKernel() ) );
}

bool NS(Controller_is_ready_to_remap)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( ctrl != nullptr ) && ( ctrl->readyForRemap() ) );
}

bool NS(Controller_is_ready_to_send)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( ctrl != nullptr ) && ( ctrl->readyForSend() ) );
}

bool NS(Controller_is_ready_to_receive)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( ctrl != nullptr ) && ( ctrl->readyForReceive() ) );
}

/* ------------------------------------------------------------------------- */

bool NS(Controller_is_in_debug_mode)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( ctrl != nullptr ) && ( ctrl->isInDebugMode() ) );
}

::NS(arch_status_t) NS(Controller_enable_debug_mode)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr )
        ? ctrl->enableDebugMode() : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_status_t) NS(Controller_disable_debug_mode)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr )
        ? ctrl->disableDebugMode() : st::ARCH_STATUS_GENERAL_FAILURE;
}

::NS(arch_variant_flags_t) NS(Controller_active_variant_flags)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr ) ? ctrl->variant() : st::ARCH_VARIANT_NONE;
}

bool NS(Controller_are_variant_flags_set)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(arch_variant_flags_t) const variant_flags )
{
    return ( ( ctrl != nullptr ) &&
        ( ctrl->areVariantFlagsSet( variant_flags ) ) );
}

bool NS(Controller_variant_release_mode)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( ctrl != nullptr ) && ( ctrl->variantReleaseMode() ) );
}

bool NS(Controller_variant_debug_mode)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( ctrl != nullptr ) && ( ctrl->variantDebugMode() ) );
}

/* ========================================================================= */

::NS(arch_size_t) NS(Controller_get_num_of_kernels)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr ) ? ctrl->numKernels() : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(Controller_get_num_keys_for_kernel_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(ctrl_kernel_id_t) const kernel_id )
{
    return ( ctrl != nullptr )
        ? ctrl->numKeys( kernel_id ) : ::NS(arch_size_t){ 0 };
}

::NS(arch_size_t) NS(Controller_get_num_of_kernel_arguments)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(arch_kernel_id_t) const kernel_id )
{
    return ( ctrl != nullptr )
        ? ctrl->kernelNumArguments( kernel_id ) : ::NS(arch_size_t){ 0 };
}

/* ------------------------------------------------------------------------- */

bool NS(Controller_kernel_has_name)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    NS(arch_kernel_id_t) const kernel_id )
{
    return ( ( ctrl != nullptr ) && ( ctrl->kernelHasName( kernel_id ) ) );
}

char const* NS(Controller_get_kernel_name_string)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(arch_kernel_id_t) const kernel_id )
{
    return ( ctrl != nullptr ) ? ctrl->ptrKernelNameStr( kernel_id ) : nullptr;
}

/* ------------------------------------------------------------------------- */

bool NS(Controller_has_kernel_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(arch_kernel_id_t) const kernel_id )
{
    return ( ( ctrl != nullptr ) && ( ctrl->hasKernel( kernel_id ) ) );
}

::NS(ctrl_kernel_id_t) NS(Controller_get_kernel_id_by_key)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    const ::NS(KernelConfigKey) *const SIXTRL_RESTRICT kernel_config_key )
{
    return ( ( ctrl != nullptr ) && ( kernel_config_key != nullptr ) )
        ? ctrl->kernelId( *kernel_config_key )
        : ::NS(ARCH_ILLEGAL_KERNEL_ID);
}

/* ------------------------------------------------------------------------- */

::NS(KernelConfigBase) const* NS(Controller_const_kernel_config_base)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl,
    ::NS(arch_kernel_id_t) const kernel_id )
{
    return ( ctrl != nullptr )
        ? ctrl->ptrKernelConfigBase( kernel_id ) : nullptr;
}

::NS(KernelConfigBase)* NS(Controller_kernel_config_base)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    ::NS(arch_kernel_id_t) const kernel_id )
{
    return ( ctrl != nullptr )
        ? ctrl->ptrKernelConfigBase( kernel_id ) : nullptr;
}

/* ========================================================================= */

bool NS(Controller_has_remap_buffer_kernel)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ( ctrl != nullptr ) && ( ctrl->hasRemapBufferKernel() ) );
}

::NS(ctrl_kernel_id_t) NS(Controller_get_remap_buffer_kernel_id)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr ) ? ctrl->remapBufferKernelConfigId()
        : st::ControllerBase::ILLEGAL_KERNEL_ID;
}

::NS(KernelConfigKey) const* NS(Controller_remap_buffer_kernel_key)(
    const ::NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr )
        ? &( ctrl->remapBufferKernelConfigKey() ) : nullptr;
}

/* ========================================================================= */

NS(arch_status_t) NS(Controller_set_active_variant_flags)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    NS(arch_variant_flags_t) const variant_flags )
{
    return ( ctrl != nullptr )
        ? ctrl->setActiveVariantFlags( variant_flags )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* ========================================================================= */

NS(KernelConfigStore) const* NS(Controller_get_const_kernel_config_store)(
    const NS(ControllerBase) *const SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr ) ? ctrl->ptrKernelConfigStore() : nullptr;
}

NS(KernelConfigStore)* NS(Controller_get_kernel_config_store)(
    NS(ControllerBase)* SIXTRL_RESTRICT ctrl )
{
    return ( ctrl != nullptr ) ? ctrl->ptrKernelConfigStore() : nullptr;
}

/* ========================================================================= */

#endif /* C++, Host */

/* end: sixtracklib/common/control/controller_base_c99.cpp */
