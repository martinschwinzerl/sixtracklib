#ifndef SIXTRACKLIB_TESTS_COMMON_CONTROL_TEST_NODE_INFO_HPP__
#define SIXTRACKLIB_TESTS_COMMON_CONTROL_TEST_NODE_INFO_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
        #include <cstddef>
        #include <cstdlib>
#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_info.hpp"
    #include "sixtracklib/common/control/node_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        class TestNodeInfo : public SIXTRL_CXX_NAMESPACE::NodeInfoBase
        {
            public:

            SIXTRL_HOST_FN explicit TestNodeInfo( arch_id_t const arch_id,
                char const* SIXTRL_RESTRICT platform_name = nullptr,
                char const* SIXTRL_RESTRICT device_name = nullptr,
                char const* SIXTRL_RESTRICT description = nullptr,
                platform_id_t const platform_id =
                    SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID,
                device_id_t const device_id =
                    SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID,
                NodeStore* SIXTRL_RESTRICT ptr_node_store = nullptr );

            SIXTRL_HOST_FN TestNodeInfo( arch_id_t const arch_id,
                std::string const& SIXTRL_RESTRICT_REF platform_name,
                std::string const& SIXTRL_RESTRICT_REF device_name,
                std::string const& SIXTRL_RESTRICT_REF description,
                platform_id_t const platform_id =
                    SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID,
                device_id_t const device_id =
                    SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID,
                NodeStore* SIXTRL_RESTRICT ptr_node_store = nullptr );

            SIXTRL_HOST_FN TestNodeInfo( TestNodeInfo const& ) = default;
            SIXTRL_HOST_FN TestNodeInfo( TestNodeInfo&& ) = default;

            SIXTRL_HOST_FN TestNodeInfo& operator=(
                TestNodeInfo const& ) = default;

            SIXTRL_HOST_FN TestNodeInfo& operator=( TestNodeInfo&& ) = default;

            virtual ~TestNodeInfo() = default;

            void setMaxAttachementCnt(
                size_type const max_attach_cnt ) SIXTRL_NOEXCEPT;

            void setMaxSelectionCount(
                size_type const max_selection_cnt ) SIXTRL_NOEXCEPT;
        };

        SIXTRL_CXX_NAMESPACE::arch_status_t TestNodeInfo_add_to_node_store(
            SIXTRL_CXX_NAMESPACE::NodeStore& SIXTRL_RESTRICT_REF store,
            SIXTRL_CXX_NAMESPACE::arch_size_t const num_nodes,
            SIXTRL_CXX_NAMESPACE::arch_id_t const* arch_ids_begin,
            SIXTRL_CXX_NAMESPACE::node_platform_id_t const* platform_ids_begin,
            SIXTRL_CXX_NAMESPACE::arch_size_t const* max_atachment_cnt_begin,
            SIXTRL_CXX_NAMESPACE::arch_size_t const* max_selection_cnt_begin,
            SIXTRL_CXX_NAMESPACE::node_index_t* node_indices_begin = nullptr );
    }
}

extern "C" {

typedef SIXTRL_CXX_NAMESPACE::tests::TestNodeInfo NS(TestNodeInfo);

}

#else /* C++, Host */

typedef void NS(TestNodeInfo);

#endif /* C++, Host */
#endif /* SIXTRACKLIB_TESTS_COMMON_CONTROL_TEST_NODE_INFO_HPP__ */

/* end: tests/sixtracklib/testlib/common/control/node_info.hpp */
