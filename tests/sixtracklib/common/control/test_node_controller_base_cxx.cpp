#include "sixtracklib/common/control/node_controller_base.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"
#include "sixtracklib/common/control/node_info.hpp"

#include "sixtracklib/testlib.h"

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        class TestCtrlKernelSet:
            public SIXTRL_CXX_NAMESPACE::ControllerKernelSetBase
        {
            public:

            SIXTRL_HOST_FN explicit TestCtrlKernelSet(
                arch_id_t const arch_id,
                kernel_config_store_base_t& SIXTRL_RESTRICT_REF kernel_conf_store );

            SIXTRL_HOST_FN TestCtrlKernelSet(
                lock_t const& SIXTRL_RESTRICT_REF lock, arch_id_t const arch_id,
                kernel_config_store_base_t& SIXTRL_RESTRICT_REF kernel_conf_store );

            SIXTRL_HOST_FN TestCtrlKernelSet(
                TestCtrlKernelSet const& orig ) = default;

            SIXTRL_HOST_FN TestCtrlKernelSet(
                TestCtrlKernelSet&& orig ) = default;

            SIXTRL_HOST_FN TestCtrlKernelSet& operator=(
                TestCtrlKernelSet const& orig ) = default;

            SIXTRL_HOST_FN TestCtrlKernelSet& operator=(
                TestCtrlKernelSet&& orig ) = default;

            SIXTRL_HOST_FN virtual ~ControllerKernelSetBase() = default;
        };

        class TestNodeControllerBase :
            public SIXTRL_CXX_NAMESPACE::NodeControllerBase
        {
            public:

            TestNodeControllerBase( arch_id_t const arch_id,
                char const* SIXTRL_RESTRICT config_str ) :
                SIXTRL_CXX_NAMESPACE::NodeControllerBase( arch_id, config_str )
            {
                namespace st = SIXTRL_CXX_NAMESPACE;

                node_lock_t node_lock( *st::NodeStore_get().lockable() );
                status_t status = this->doInitNodeStoreTestImpl(
                    node_lock, st::NodeStore_get_ptr() );

                SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );

                std::unique_ptr< kernel_config_store_base_t >
                ptr_kernel_config_store( new st::KernelConfigStore() );

                SIXTRL_ASSERT( ptr_kernel_config_store.get() != nullptr );

                kernel_lock_t kernel_lock(
                    *ptr_kernel_config_store->lockable() );

                SIXTRL_ASSERT( ptr_kernel_config_store->checkLock(
                    kernel_lock ) );

                status = this->doInitKernelConfigStore(
                    kernel_lock, std::move( ptr_kernel_config_store ) );

                SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            }

            TestNodeControllerBase( TestNodeControllerBase const& ) = default;
            TestNodeControllerBase( TestNodeControllerBase&& ) = default;

            TestNodeControllerBase& operator=(
                TestNodeControllerBase const& ) = default;

            TestNodeControllerBase& operator=(
                TestNodeControllerBase&& ) = default;

            ~TestNodeControllerBase() = default;

            private:

            status_t doInitNodeStoreTestImpl(
                node_lock_t const& SIXTRL_RESTRICT_REF lock,
                node_store_t* SIXTRL_RESTRICT ptr_node_store )
            {
                namespace st = SIXTRL_CXX_NAMESPACE;

                SIXTRL_ASSERT( ptr_node_store != nullptr );
                SIXTRL_ASSERT( ptr_node_store->checkLock( lock ) );

                status_t status = this->doInitNodeStore( lock, ptr_node_store );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    std::unique_ptr< node_set_base_t > ptr_node_set(
                        new node_set_t( lock, *ptr_node_store ) );

                    node_set_id_t const node_set_id =
                    ptr_node_store->addNodeSet(
                        lock, std::move( ptr_node_set ) );

                    if( node_set_id == node_store_t::ILLEGAL_NODE_SET_ID )
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                    }

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        status = ptr_node_store->attachAllArchitectureNodesToSet(
                            lock, this->archId(), node_set_id );
                    }

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        status = this->doInitNodeSet( lock, node_set_id );
                    }
                }

                return status;
            }

            status_t doInitDefaultKernelsTestImpl(
                node_lock_t const& node_lock,
                kernel_lock_t const& kernel_lock )
            {
                namespace st = SIXTRL_CXX_NAMESPACE;
                status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

                SIXTRL_ASSERT( this->ptrNodeStore( node_lock ) != nullptr );

                node_set_base_t* ptr_node_set =
                    this->ptrNodeSetBase( node_lock );

                SIXTRL_ASSERT( ptr_node_set != nullptr );

                size_type const num_nodes = ptr_node_set->numNodes();

                kernel_config_key_t key( this->kernelConfigStore()

                for( size_type ii = size_type{ 0 } ; ii < num_nodes ; ++ii )
                {

                }
            }
        };
    }
}

TEST( CXX_CommonNodeControllerBaseTests, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using test_ctrl_t = st::tests::TestNodeControllerBase;
    using size_t = test_ctrl_t::size_type;
    using platform_id_t = test_ctrl_t::platform_id_t;
    using arch_id_t = st::arch_id_t;
    using status_t = st::ctrl_status_t;
    using node_id_t = test_ctrl_t::node_id_t;
    using node_index_t = test_ctrl_t::node_index_t;

    /* Create three dummy architectures to allow variation in the
     * node sets based on the arch_id parameter: */

    static constexpr size_t NUM_ARCHS = size_t{ 3 };
    st::Architectures& archs = st::Architectures_get();

    arch_id_t arch_ids[ NUM_ARCHS ] =
    {
        st::ARCHITECTURE_ILLEGAL, st::ARCHITECTURE_ILLEGAL,
        st::ARCHITECTURE_ILLEGAL
    };

    status_t status = st::tests::Architectures_setup(
        archs, NUM_ARCHS, arch_id_t{ 32 }, &arch_ids[ 0 ] );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    SIXTRL_ASSERT( archs.numArchitectures() == NUM_ARCHS );

    arch_id_t const arch01 = arch_ids[ 0 ];
    arch_id_t const arch02 = arch_ids[ 1 ];
    arch_id_t const arch03 = arch_ids[ 2 ];

    /* Create a set of nodes on the default node store for the
     * three default architectures -> this allows us to play with
     * the node controllers */

    /* Setup node_infos to be used with the NodeSetBase instances */

    static constexpr size_t NUM_NODES = 12;

    const arch_id_t nodes_arch_ids[ NUM_NODES ] =
    {
        arch01, arch01, arch01, arch01, arch01,
        arch02,
        arch03, arch03, arch03, arch03, arch03, arch03
    };

    const platform_id_t nodes_platform_ids[ NUM_NODES ] =
    {
        platform_id_t{ 0 }, platform_id_t{ 0 }, platform_id_t{ 0 },
        platform_id_t{ 0 }, platform_id_t{ 1 },
        platform_id_t{ 0 },
        test_ctrl_t::ILLEGAL_PLATFORM_ID,
        test_ctrl_t::ILLEGAL_PLATFORM_ID,
        test_ctrl_t::ILLEGAL_PLATFORM_ID,
        test_ctrl_t::ILLEGAL_PLATFORM_ID,
        platform_id_t{ 42 },
        test_ctrl_t::ILLEGAL_PLATFORM_ID
    };

    const size_t nodes_max_attach_cnt[ NUM_NODES ] =
    {
        size_t{ 16 }, size_t{ 16 }, size_t{ 16 },
        size_t{ 16 }, size_t{ 16 },
        size_t{ 16 },
        size_t{ 16 }, size_t{ 16 }, size_t{ 16 }, size_t{ 16 },
        size_t{ 42 }, size_t{ 16 }
    };

    const size_t nodes_max_selection_cnt[ NUM_NODES ] =
    {
        size_t{  2 }, size_t{ 2 }, size_t{ 0 },
        size_t{  2 }, size_t{ 2 },
        size_t{  1 },
        size_t{  1 }, size_t{ 1 }, size_t{ 1 }, size_t{ 0 },
        size_t{ 42 }, size_t{ 1 }
    };

    node_index_t cmp_node_indices[ NUM_NODES ];
    std::fill( &cmp_node_indices[ 0 ], &cmp_node_indices[ NUM_NODES ],
               st::NodeStore::UNDEFINED_INDEX );

    status = st::tests::TestNodeInfo_add_to_node_store( store, NUM_NODES,
        &nodes_arch_ids[ 0 ], &nodes_platform_ids[ 0 ],
            &nodes_max_attach_cnt[ 0 ], &nodes_max_selection_cnt[ 0 ],
                &cmp_node_indices[ 0 ] );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );

    /* -------------------------------------------------------------- */

    test_ctrl_t   node_controller_a01( arch01, "" );
    ASSERT_TRUE(  node_controller_a01.archId() == arch01 );
    ASSERT_TRUE(  node_controller_a01.hasNodeStore() );
    ASSERT_TRUE( !node_controller_a01.ownsNodeStore() );
    ASSERT_TRUE(  node_controller_a01.ptrConstNodeStore() != nullptr );
    ASSERT_TRUE(  node_controller_a01.ptrConstNodeStore()->totalNumNodes() ==
                  NUM_NODES );

    ASSERT_TRUE(  node_controller_a01.hasNodeSet() );
    ASSERT_TRUE(  node_controller_a01.ptrConstNodeSetBase() != nullptr );
    ASSERT_TRUE(  node_controller_a01.numNodes() ==
                  st::NodeStore_get().numNodes( node_controller_a01.archId() ) );

    node_controller_a01.selectNode

}

/* end: tests/sixtracklib/common/control/test_node_controller_base_cxx.cpp */
