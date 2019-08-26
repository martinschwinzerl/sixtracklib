#ifndef SIXTRACKLIB_TESTLIB_COMMON_CONTROL_CONTROLLER_BASE_HPP_CXX__
#define SIXTRACKLIB_TESTLIB_COMMON_CONTROL_CONTROLLER_BASE_HPP_CXX__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/controller_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        class TestControllerBase : public SIXTRL_CXX_NAMESPACE::ControllerBase
        {
            public:

            SIXTRL_HOST_FN TestControllerBase( arch_id_t const arch_id,
                kernel_config_store_base_t* SIXTRL_RESTRICT
                    ptr_kernel_config_store = nullptr,
                kernel_set_id_t const kernel_set_id = ILLEGAL_KERNEL_SET_ID,
                char const* SIXTRL_RESTRICT config_str = nullptr );

            SIXTRL_HOST_FN TestControllerBase(
                kernel_lock_t& SIXTRL_RESTRICT_REF lock,
                arch_id_t const arch_id,
                kernel_config_store_base_t* SIXTRL_RESTRICT
                    ptr_kernel_config_store = nullptr,
                kernel_set_id_t const kernel_set_id = ILLEGAL_KERNEL_SET_ID,
                char const* SIXTRL_RESTRICT config_str = nullptr );

            SIXTRL_HOST_FN TestControllerBase( arch_id_t const arch_id,
                ptr_kernel_config_store_t&& kernel_config_store,
                kernel_set_id_t const kernel_set = ILLEGAL_KERNEL_SET_ID,
                char const* SIXTRL_RESTRICT config_str = nullptr );

            SIXTRL_HOST_FN TestControllerBase(
                kernel_lock_t& SIXTRL_RESTRICT_REF lock,
                arch_id_t const arch_id,
                ptr_kernel_config_store_t&& kernel_config_store,
                kernel_set_id_t const kernel_set = ILLEGAL_KERNEL_SET_ID,
                char const* SIXTRL_RESTRICT config_str = nullptr );

            SIXTRL_HOST_FN TestControllerBase(
                TestControllerBase const& other ) = default;

            SIXTRL_HOST_FN TestControllerBase(
                TestControllerBase&& other ) = default;

            SIXTRL_HOST_FN TestControllerBase& operator=(
                TestControllerBase const& rhs ) = default;

            SIXTRL_HOST_FN TestControllerBase& operator=(
                TestControllerBase&& rhs ) = default;

            SIXTRL_HOST_FN virtual ~TestControllerBase() = default;

            protected:

            SIXTRL_HOST_FN virtual status_t doSyncWithKernelSet(
                kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock ) override;

            private:

            SIXTRL_HOST_FN status_t doInitTestControllerBase(
                kernel_lock_t const& SIXTRL_RESTRICT_REF lock );
        };
    }
}

extern "C" {

typedef SIXTRL_CXX_NAMESPACE::tests::TestControllerBase NS(TestControllerBase);

}

#else /* C++, Host */

typedef void NS(TestControllerBase);

#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_CONTROL_CONTROLLER_BASE_HPP_CXX__ */
/* end: tests/sixtracklib/testlib/common/control/controller_base.hpp */
