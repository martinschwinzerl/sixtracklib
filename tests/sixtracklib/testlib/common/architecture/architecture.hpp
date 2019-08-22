#ifndef SIXTRACKLIB_TESTS_COMMON_ARCHITECTURE_TEST_ARCHITECTURE_HPP__
#define SIXTRACKLIB_TESTS_COMMON_ARCHITECTURE_TEST_ARCHITECTURE_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
        #include <cstddef>
        #include <cstdlib>
#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/architecture/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/architecture/architecture.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        SIXTRL_CXX_NAMESPACE::arch_init_flags_t Arch_dummy_init_fn(
            SIXTRL_CXX_NAMESPACE::arch_id_t const arch_id,
            SIXTRL_CXX_NAMESPACE::ArchData* SIXTRL_RESTRICT ptr_arch_data );

        SIXTRL_CXX_NAMESPACE::arch_status_t Architectures_setup(
            SIXTRL_CXX_NAMESPACE::Architectures& SIXTRL_RESTRICT_REF archs,
            SIXTRL_CXX_NAMESPACE::arch_size_t const num_architectures,
            SIXTRL_CXX_NAMESPACE::arch_id_t const start_arch_id,
            SIXTRL_CXX_NAMESPACE::arch_id_t* SIXTRL_RESTRICT arch_ids );
    }
}

#endif /* C++, Host */
#endif /* SIXTRACKLIB_TESTS_COMMON_ARCHITECTURE_TEST_ARCHITECTURE_HPP__ */

/* end: tests/sixtracklib/testlib/common/architecture/architecture.hpp */
