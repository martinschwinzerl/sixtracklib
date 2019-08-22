#ifndef SIXTRACKLIB_TESTS_COMMON_CONTROL_TEST_NODE_SET_HPP__
#define SIXTRACKLIB_TESTS_COMMON_CONTROL_TEST_NODE_SET_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
        #include <cstddef>
        #include <cstdlib>
        #include <string>
        #include <sstream>
#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_store.hpp"
    #include "sixtracklib/common/control/node_set.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        class TestNodeSetBase : public SIXTRL_CXX_NAMESPACE::NodeSetBase
        {
            public:

            SIXTRL_HOST_FN explicit TestNodeSetBase(
                SIXTRL_CXX_NAMESPACE::NodeStore& SIXTRL_RESTRICT_REF store );

            SIXTRL_HOST_FN TestNodeSetBase( TestNodeSetBase const& ) = default;
            SIXTRL_HOST_FN TestNodeSetBase( TestNodeSetBase&& ) = default;

            SIXTRL_HOST_FN TestNodeSetBase& operator=(
                TestNodeSetBase const& ) = default;

            SIXTRL_HOST_FN TestNodeSetBase& operator=(
                TestNodeSetBase&& ) = default;

            virtual ~TestNodeSetBase() = default;

            void setMinNumSelectableNodes( size_type const min_sel_cnt );
            void setMaxNumSelectableNodes( size_type const max_sel_cnt );

            void setMinNumDefaultNodes( size_type const min_default_cnt );
            void setMaxNumDefaultNodes( size_type const max_default_cnt );
        };

        class TestNodeSetSingle : public SIXTRL_CXX_NAMESPACE::NodeSetSingle
        {
            public:

            SIXTRL_HOST_FN explicit TestNodeSetSingle(
                SIXTRL_CXX_NAMESPACE::NodeStore& SIXTRL_RESTRICT_REF store );

            SIXTRL_HOST_FN TestNodeSetSingle(
                TestNodeSetSingle const& ) = default;

            SIXTRL_HOST_FN TestNodeSetSingle(
                TestNodeSetSingle&& ) = default;

            SIXTRL_HOST_FN TestNodeSetSingle& operator=(
                TestNodeSetSingle const& ) = default;

            SIXTRL_HOST_FN TestNodeSetSingle& operator=(
                TestNodeSetSingle&& ) = default;

            virtual ~TestNodeSetSingle() = default;

            void setMinNumSelectableNodes( size_type const min_sel_cnt );
            void setMaxNumSelectableNodes( size_type const max_sel_cnt );

            void setMinNumDefaultNodes( size_type const min_default_cnt );
            void setMaxNumDefaultNodes( size_type const max_default_cnt );

            void setCanDirectlyChangeSelectedNodeFlag( bool const flag );
            void setCanUnselectNodeFlag( bool const flag );
            void setUseAutoselectFlag( bool const flag );
        };
    }
}

typedef SIXTRL_CXX_NAMESPACE::tests::TestNodeSetBase   NS(TestNodeSetBase);
typedef SIXTRL_CXX_NAMESPACE::tests::TestNodeSetSingle NS(TestNodeSetSingle);

#else  /* C++, Host */

typedef void NS(TestNodeSetBase);
typedef void NS(TestNodeSetSingle);

#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTS_COMMON_CONTROL_TEST_NODE_SET_HPP__ */

/* end: tests/sixtracklib/testlib/common/control/node_set.hpp */
