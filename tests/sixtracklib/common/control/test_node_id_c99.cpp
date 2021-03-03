#include <cstddef>
#include <cstdint>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/control/node_id.h"

TEST( C99CommonControlNodeIdFromString, NodeIdFromStr )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using platform_id_type = st::NodeId::platform_id_type;
    using device_id_type = st::NodeId::device_id_type;
    using backend_id_type = st::backend_id_type;

    ::NS(NodeId)* node_id_0 = ::NS(NodeId_create)();
    ASSERT_TRUE( node_id_0 != nullptr );
    ASSERT_TRUE( ::NS(NodeId_platform_id)( node_id_0 ) ==
                 ::NS(NODE_PLATFORM_ID_ILLEGAL) );

    ASSERT_TRUE( ::NS(NodeId_device_id)( node_id_0 ) ==
                 ::NS(NODE_DEVICE_ID_ILLEGAL) );

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(NodeId_from_string)(
                 node_id_0, "42.1" ) );

    ASSERT_TRUE( ::NS(NodeId_platform_id)( node_id_0 ) ==
                 platform_id_type{ 42 } );

    ASSERT_TRUE( ::NS(NodeId_device_id)( node_id_0 ) ==
                 device_id_type{ 1 } );

    ASSERT_TRUE( !::NS(NodeId_has_index)( node_id_0 ) );

    backend_id_type backend_id = st::BACKEND_ID_NONE;

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(NodeId_from_string_detailed)(
        node_id_0, "opencl:1.0", ::NS(NODE_ID_STR_FORMAT_AUTO), &backend_id ) );

    ASSERT_TRUE( ::NS(NodeId_platform_id)( node_id_0 ) ==
                 platform_id_type{ 1 } );

    ASSERT_TRUE( ::NS(NodeId_device_id)( node_id_0 ) ==
                 device_id_type{ 0 } );

    ASSERT_TRUE( !::NS(NodeId_has_index)( node_id_0 ) );

    ::NS(NodeId_delete)( node_id_0 );
}
