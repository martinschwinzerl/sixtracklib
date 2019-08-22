#include "sixtracklib/testlib/common/architecture/architecture.h"
#include "sixtracklib/testlib/common/architecture/architecture.hpp"

#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;
namespace st_tests = SIXTRL_CXX_NAMESPACE::tests;

::NS(arch_init_flags_t) NS(Arch_dummy_init_fn)(
    ::NS(arch_id_t) const arch_id,
    ::NS(ArchData)* SIXTRL_RESTRICT ptr_arch_data )
{
    return st_tests::Arch_dummy_init_fn( arch_id, ptr_arch_data );
}

::NS(arch_status_t) NS(Architectures_setup)(
    ::NS(Architectures)* SIXTRL_RESTRICT archs,
    ::NS(arch_size_t) const num_architectures,
    ::NS(arch_id_t) const start_arch_id,
    ::NS(arch_id_t)* SIXTRL_RESTRICT arch_ids_begin )
{
    return ( archs != nullptr )
        ? st_tests::Architectures_setup(
            *archs, num_architectures, start_arch_id, arch_ids_begin )
        : st::ARCH_STATUS_GENERAL_FAILURE;
}

/* end: tests/sixtracklib/testlib/common/architecture/architecture_c99.cpp */
