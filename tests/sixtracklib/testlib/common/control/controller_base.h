#ifndef SIXTRACKLIB_TESTLIB_COMMON_CONTROL_CONTROLLER_BASE_H_C99__
#define SIXTRACKLIB_TESTLIB_COMMON_CONTROL_CONTROLLER_BASE_H_C99__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/control/controller_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/controller_base.h"
    #include "sixtracklib/common/control/kernel_config_store.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {

SIXTRL_EXTERN SIXTRL_HOST_FN NS(TestControllerBase)*
NS(TestControllerBase_new)( NS(arch_id_t) const arch_id,
    NS(KernelConfigStore)* SIXTRL_RESTRICT kernel_store_to_transfer_ownership,
    NS(kernel_set_id_t) const kernel_set_id,
    char const* SIXTRL_RESTRICT config_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(TestControllerBase)*
NS(TestControllerBase_new_with_ext_kernel_store)( NS(arch_id_t) const arch_id,
    NS(KernelConfigStore)* SIXTRL_RESTRICT ptr_ext_kernel_store,
    NS(kernel_set_id_t) const kernel_set_id,
    char const* SIXTRL_RESTRICT config_str );

}
#endif /* C++ */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_CONTROL_CONTROLLER_BASE_H_C99__ */

/* end: tests/sixtracklib/testlib/common/control/controller_base.h */
