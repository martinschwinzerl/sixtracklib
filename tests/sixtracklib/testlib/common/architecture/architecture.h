#ifndef SIXTRACKLIB_TESTS_COMMON_ARCHITECTURE_TEST_ARCHITECTURE_C99_H__
#define SIXTRACKLIB_TESTS_COMMON_ARCHITECTURE_TEST_ARCHITECTURE_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/architecture/architecture.hpp"
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/architecture/definitions.h"
    #include "sixtracklib/common/architecture/architecture.h"
    #include "sixtracklib/common/architecture/arch_data.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_init_flags_t) NS(Arch_dummy_init_fn)(
    NS(arch_id_t) const arch_id, NS(ArchData)* SIXTRL_RESTRICT ptr_arch_data );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(Architectures_setup)(
    NS(Architectures)* SIXTRL_RESTRICT archs,
    NS(arch_size_t) const num_architectures,
    NS(arch_id_t) const start_arch_id,
    NS(arch_id_t)* SIXTRL_RESTRICT arch_ids );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

#endif /* SIXTRACKLIB_TESTS_COMMON_ARCHITECTURE_TEST_ARCHITECTURE_C99_H__ */

/* end: tests/sixtracklib/testlib/common/control/node_set.hpp */
