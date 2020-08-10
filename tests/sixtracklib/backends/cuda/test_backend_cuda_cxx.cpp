#include "sixtracklib/backends/cuda/backend.h"
#include <gtest/gtest.h>
#include <iostream>

TEST( CxxCudaBackend, basic_usage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::CudaBackend backend;

    ASSERT_TRUE(  backend.backend_id() == st::BACKEND_CUDA );
    ASSERT_TRUE(  backend.has_dynamic_library_loader() );
    ASSERT_TRUE( !backend.has_dynamic_library_handle() );
    ASSERT_TRUE( !backend.is_available() );
    ASSERT_TRUE( !backend.is_ready() );

    st::status_t status = backend.make_available();

    if( status == st::STATUS_SUCCESS )
    {
        std::cout << "is_available == true\r\n";

        ASSERT_TRUE(  backend.is_available() );
        ASSERT_TRUE( !backend.is_ready() );
        ASSERT_TRUE(  backend.has_dynamic_library_loader() );
        ASSERT_TRUE(  backend.has_dynamic_library_handle() );
        status = backend.make_ready();
    }

    if( status == st::STATUS_SUCCESS )
    {
        std::cout << "is_ready == true\r\n";

        ASSERT_TRUE( backend.is_available() );
        ASSERT_TRUE( backend.is_ready() );
        ASSERT_TRUE( backend.num_available_nodes() > 0u );

        auto node_id_it = backend.c_node_ids_begin();
        auto node_id_end = backend.c_node_ids_end();
        st::size_t ii = 0u;

        for( ; node_id_it != node_id_end ; ++node_id_it )
        {
            auto node_info = backend.base_node_info(
                node_id_it->m_platform_id, node_id_it->m_device_id );

            ASSERT_TRUE( node_info != nullptr );
            std::cout << ii << "\r\n" << *node_info << "\r\n";
        }
    }


}
