#include <cstddef>
#include <cstdint>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/control/node_id.h"

TEST( CXXCommonControlNodeIdFromString, StaticGetStrFormatType )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using node_id_type = st::NodeId;
    st::backend_id_type backend_id = st::BACKEND_ID_NONE;

    auto str_format = node_id_type::GET_STR_FORMAT_TYPE( "0.0", &backend_id );
    ASSERT_TRUE( str_format == st::NODE_ID_STR_FORMAT_MINIMAL );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_NONE );

    str_format = node_id_type::GET_STR_FORMAT_TYPE( "a.b", &backend_id );
    ASSERT_TRUE( str_format == st::NODE_ID_STR_FORMAT_ILLEGAL );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_NONE );

    str_format = node_id_type::GET_STR_FORMAT_TYPE( "abcd", &backend_id );
    ASSERT_TRUE( str_format == st::NODE_ID_STR_FORMAT_ILLEGAL );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_NONE );

    str_format = node_id_type::GET_STR_FORMAT_TYPE( "opencl:a", &backend_id );
    ASSERT_TRUE( str_format == st::NODE_ID_STR_FORMAT_ILLEGAL );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_NONE );

    str_format = node_id_type::GET_STR_FORMAT_TYPE( "opencl:0", &backend_id );
    ASSERT_TRUE( str_format == st::NODE_ID_STR_FORMAT_ILLEGAL );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_NONE );

    str_format = node_id_type::GET_STR_FORMAT_TYPE( "opencl:1-0", &backend_id );
    ASSERT_TRUE( str_format == st::NODE_ID_STR_FORMAT_ILLEGAL );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_NONE );

    str_format = node_id_type::GET_STR_FORMAT_TYPE( "opencl:0.0", &backend_id );
    ASSERT_TRUE( str_format == st::NODE_ID_STR_FORMAT_BACKEND_STR );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_OPENCL );

    str_format = node_id_type::GET_STR_FORMAT_TYPE( "cuda:0.0", &backend_id );
    ASSERT_TRUE( str_format == st::NODE_ID_STR_FORMAT_BACKEND_STR );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_CUDA );

    std::ostringstream a2str;
    a2str << st::BACKEND_ID_CUDA << ":1.0";

    str_format = node_id_type::GET_STR_FORMAT_TYPE( a2str.str(), &backend_id );
    ASSERT_TRUE( str_format == st::NODE_ID_STR_FORMAT_BACKEND_ID );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_CUDA );

    a2str.str( "" );
    a2str << st::BACKEND_ID_CUDA << ":0.1";

    str_format = node_id_type::GET_STR_FORMAT_TYPE( a2str.str(), &backend_id );
    ASSERT_TRUE( str_format == st::NODE_ID_STR_FORMAT_BACKEND_ID );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_CUDA );

    a2str.str( "" );
    a2str << st::BACKEND_ID_CUDA << ":abc";

    str_format = node_id_type::GET_STR_FORMAT_TYPE( a2str.str(), &backend_id );
    ASSERT_TRUE( str_format == st::NODE_ID_STR_FORMAT_ILLEGAL );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_NONE );

    a2str.str( "" );
    a2str << st::BACKEND_ID_CUDA << ":a.b";

    str_format = node_id_type::GET_STR_FORMAT_TYPE( a2str.str(), &backend_id );
    ASSERT_TRUE( str_format == st::NODE_ID_STR_FORMAT_ILLEGAL );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_NONE );
}

TEST( CXXCommonControlNodeIdFromString, StaticDecodeNodeIdStr )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using platform_id_type = st::NodeId::platform_id_type;
    using device_id_type   = st::NodeId::device_id_type;
    using backend_id_type  = st::backend_id_type;

    backend_id_type backend_id   = st::BACKEND_ID_NONE;
    platform_id_type platform_id = st::NodeId::ILLEGAL_PLATFORM_ID;
    device_id_type device_id     = st::NodeId::ILLEGAL_DEVICE_ID;

    ASSERT_TRUE( st::STATUS_SUCCESS == st::NodeId::DECODE_NODE_ID_STR(
        "0.0", st::NODE_ID_STR_FORMAT_AUTO, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == platform_id_type{ 0 } );
    ASSERT_TRUE( device_id   == device_id_type{ 0 } );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS == st::NodeId::DECODE_NODE_ID_STR(
        "0.0", st::NODE_ID_STR_FORMAT_MINIMAL, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == platform_id_type{ 0 } );
    ASSERT_TRUE( device_id   == device_id_type{ 0 } );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        "0.0", st::NODE_ID_STR_FORMAT_BACKEND_ID, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        "0.0", st::NODE_ID_STR_FORMAT_BACKEND_STR, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    ASSERT_TRUE( st::STATUS_SUCCESS == st::NodeId::DECODE_NODE_ID_STR(
        "42.1", st::NODE_ID_STR_FORMAT_AUTO, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == platform_id_type{ 42 } );
    ASSERT_TRUE( device_id   == device_id_type{ 1 } );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS == st::NodeId::DECODE_NODE_ID_STR(
        "42.1", st::NODE_ID_STR_FORMAT_MINIMAL, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == platform_id_type{ 42 } );
    ASSERT_TRUE( device_id   == device_id_type{ 1 } );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        "42.1", st::NODE_ID_STR_FORMAT_BACKEND_ID, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        "42.1", st::NODE_ID_STR_FORMAT_BACKEND_STR, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        "42.1.0", st::NODE_ID_STR_FORMAT_AUTO, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        "+42.1", st::NODE_ID_STR_FORMAT_AUTO, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        "42.-1", st::NODE_ID_STR_FORMAT_AUTO, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        "a.1", st::NODE_ID_STR_FORMAT_AUTO, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        "42.b", st::NODE_ID_STR_FORMAT_AUTO, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        "abc123", st::NODE_ID_STR_FORMAT_AUTO, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    /* ---------------------------------------------------------------------- */

    ASSERT_TRUE( st::STATUS_SUCCESS == st::NodeId::DECODE_NODE_ID_STR(
        "opencl:0.0", st::NODE_ID_STR_FORMAT_AUTO, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == platform_id_type{ 0 } );
    ASSERT_TRUE( device_id == device_id_type{ 0 } );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_OPENCL );

    ASSERT_TRUE( st::STATUS_SUCCESS == st::NodeId::DECODE_NODE_ID_STR(
        "opencl:1.5", st::NODE_ID_STR_FORMAT_BACKEND_STR, &platform_id,
            &device_id, &backend_id ) );

    ASSERT_TRUE( platform_id == platform_id_type{ 1 } );
    ASSERT_TRUE( device_id == device_id_type{ 5 } );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_OPENCL );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        "opencl:1.5", st::NODE_ID_STR_FORMAT_BACKEND_ID, &platform_id,
            &device_id, &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        "opencl:1.5", st::NODE_ID_STR_FORMAT_MINIMAL, &platform_id,
            &device_id, &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    /* ---------------------------------------------------------------------- */

    std::ostringstream a2str;
    a2str << st::BACKEND_ID_CUDA << ":1.0";

    ASSERT_TRUE( st::STATUS_SUCCESS == st::NodeId::DECODE_NODE_ID_STR(
        a2str.str(), st::NODE_ID_STR_FORMAT_AUTO, &platform_id, &device_id,
            &backend_id ) );

    ASSERT_TRUE( platform_id == platform_id_type{ 1 } );
    ASSERT_TRUE( device_id == device_id_type{ 0 } );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_CUDA );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        a2str.str(), st::NODE_ID_STR_FORMAT_BACKEND_STR, &platform_id,
            &device_id, &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );

    ASSERT_TRUE( st::STATUS_SUCCESS == st::NodeId::DECODE_NODE_ID_STR(
        a2str.str(), st::NODE_ID_STR_FORMAT_BACKEND_ID, &platform_id,
            &device_id, &backend_id ) );

    ASSERT_TRUE( platform_id == platform_id_type{ 1 } );
    ASSERT_TRUE( device_id == device_id_type{ 0 } );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_CUDA );

    ASSERT_TRUE( st::STATUS_SUCCESS != st::NodeId::DECODE_NODE_ID_STR(
        a2str.str(), st::NODE_ID_STR_FORMAT_MINIMAL, &platform_id,
            &device_id, &backend_id ) );

    ASSERT_TRUE( platform_id == st::NodeId::ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE( device_id   == st::NodeId::ILLEGAL_DEVICE_ID );
    ASSERT_TRUE( backend_id  == st::BACKEND_ID_NONE );
}

TEST( CXXCommonControlNodeIdFromString, NodeIdFromStr )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    using platform_id_type = st::NodeId::platform_id_type;
    using device_id_type = st::NodeId::device_id_type;
    using backend_id_type = st::backend_id_type;

    st::NodeId node_id_0( "1.2" );
    ASSERT_TRUE( node_id_0.platform_id() == platform_id_type{ 1 } );
    ASSERT_TRUE( node_id_0.device_id() == device_id_type{ 2 } );
    ASSERT_TRUE( !node_id_0.has_index() );

    backend_id_type backend_id = st::BACKEND_ID_NONE;
    st::NodeId node_id_1( "1.2", st::NODE_ID_STR_FORMAT_AUTO, &backend_id );
    ASSERT_TRUE( node_id_1.compare( node_id_0 ) == 0 );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_NONE );

    st::NodeId node_id_2( "opencl:42.1", st::NODE_ID_STR_FORMAT_AUTO, &backend_id );
    ASSERT_TRUE( node_id_2.platform_id() == platform_id_type{ 42 } );
    ASSERT_TRUE( node_id_2.device_id() == platform_id_type{ 1 } );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_OPENCL );

    std::ostringstream a2str;
    a2str << st::BACKEND_ID_CUDA << ":1.5";

    st::NodeId node_id_3( a2str.str(), st::NODE_ID_STR_FORMAT_AUTO, &backend_id );
    ASSERT_TRUE( node_id_3.platform_id() == platform_id_type{ 1 } );
    ASSERT_TRUE( node_id_3.device_id() == platform_id_type{ 5 } );
    ASSERT_TRUE( backend_id == st::BACKEND_ID_CUDA );
}
