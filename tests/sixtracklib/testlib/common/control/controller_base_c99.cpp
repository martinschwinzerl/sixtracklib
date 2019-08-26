#include "sixtracklib/testlib/common/control/controller_base.h"
#include "sixtracklib/testlib/common/control/controller_base.hpp"

#if !defined( _GPUCODE ) && defined( __cplusplus )

namespace  st = SIXTRL_CXX_NAMESPACE;
using _this_t = st::tests::TestControllerBase;

::NS(TestControllerBase)* NS(TestControllerBase_new)(
    ::NS(arch_id_t) const arch_id,
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT kernel_store_to_transfer_ownership,
    ::NS(kernel_set_id_t) const kernel_set_id,
    char const* SIXTRL_RESTRICT config_str )
{
    std::unique_ptr< _this_t::kernel_config_store_base_t > ptr_kernel_store(
        kernel_store_to_transfer_ownership );

    return ( ptr_kernel_store.get() != nullptr )
        ? new _this_t( arch_id, std::move( ptr_kernel_store ),
                       kernel_set_id, config_str )
        : nullptr;
}

::NS(TestControllerBase)* NS(TestControllerBase_new_with_ext_kernel_store)(
    ::NS(arch_id_t) const arch_id,
    ::NS(KernelConfigStore)* SIXTRL_RESTRICT ext_kernel_store,
    ::NS(kernel_set_id_t) const kernel_set_id,
    char const* SIXTRL_RESTRICT config_str )
{
    return new _this_t( arch_id, ext_kernel_store, kernel_set_id, config_str );
}

#endif /* C++ */

/* end: tests/sixtracklib/testlib/common/control/controller_base_c99.cpp */
