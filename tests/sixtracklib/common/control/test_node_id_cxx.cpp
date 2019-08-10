#include "sixtracklib/common/control/node_id.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"
#include "sixtracklib/testlib.h"

TEST( CXX_CommonControlNodeIdTests, MinimalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using node_id_t             = st::NodeId;
    using platform_id_t         = node_id_t::platform_id_t;
    using device_id_t           = node_id_t::device_id_t;
    using ctrl_size_t           = node_id_t::size_type;
    using node_id_str_fmt_t     = node_id_t::format_t;
    using arch_id_t             = st::Architectures::arch_id_t;

    char node_id_str[] =
    {
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
    };

    static constexpr ctrl_size_t TOO_SHORT_ID_STR_CAPACITY = ctrl_size_t{ 3 };
    static constexpr ctrl_size_t NODE_ID_STR_CAPACITY = ctrl_size_t{ 32 };

    static constexpr node_id_str_fmt_t FORMAT = st::NODE_ID_STR_FORMAT_NOARCH;


    /* Verify that a suitable arch is available */
    st::Architectures const& archs = st::Architectures_get_const();
    SIXTRL_ASSERT( archs.numArchitectures() > size_t{ 0 } );

    arch_id_t const arch = archs.archIdByNumber( size_t{ 0 } );
    SIXTRL_ASSERT( arch != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch != st::ARCHITECTURE_NONE );

    SIXTRL_ASSERT(  archs.hasArchitecture( arch ) );
    SIXTRL_ASSERT(  archs.isAvailable( arch ) );
    SIXTRL_ASSERT( !archs.isShutdown( arch ) );

    /* Create an empty, non-initialized nodeId instance */

    node_id_t node_id_a;

    /* Verify that all properties are set to the initial state */

    ASSERT_TRUE( !node_id_a.valid() );
    ASSERT_TRUE(  node_id_a.archId()     == st::ARCHITECTURE_ILLEGAL );
    ASSERT_TRUE(  node_id_a.platformId() == st::NODE_ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE(  node_id_a.deviceId()   == st::NODE_ILLEGAL_DEVICE_ID );

    /* creating a node_id string from an illegal nodeId should never work,
       regardless whether the buffer is large enough or not */

    ASSERT_TRUE( node_id_a.toString( node_id_str, TOO_SHORT_ID_STR_CAPACITY,
        FORMAT ) != st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE( node_id_a.toString( node_id_str, NODE_ID_STR_CAPACITY,
        FORMAT  ) != st::ARCH_STATUS_SUCCESS );

    /* Setting the platform_id to a valid value should not change the
       overall picture much: */

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == node_id_a.setPlatformId(
        platform_id_t{ 0 } ) );

    ASSERT_TRUE( !node_id_a.valid() );
    ASSERT_TRUE( node_id_a.platformId() == platform_id_t{ 0 } );

    ASSERT_TRUE( node_id_a.toString( node_id_str, TOO_SHORT_ID_STR_CAPACITY,
        FORMAT ) != st::ARCH_STATUS_SUCCESS);

    ASSERT_TRUE( node_id_a.toString( node_id_str, NODE_ID_STR_CAPACITY,
        FORMAT ) != st::ARCH_STATUS_SUCCESS );

    /* Setting also the device *and* the arch_id makes however a difference: */

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == node_id_a.setArchId( arch ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        node_id_a.setDeviceId( device_id_t{ 0 } ) );

    ASSERT_TRUE( node_id_a.valid() );
    ASSERT_TRUE( node_id_a.platformId() == platform_id_t{ 0 } );
    ASSERT_TRUE( node_id_a.deviceId() == device_id_t{ 0 } );

    /* Now we should be able to create a node_id_str if we provide a
       large enough string buffer */

    ASSERT_TRUE( node_id_a.toString( node_id_str, TOO_SHORT_ID_STR_CAPACITY,
        FORMAT ) != st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE( node_id_a.toString( node_id_str, NODE_ID_STR_CAPACITY,
        FORMAT ) == st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE( std::strcmp( node_id_str, "0.0" ) == 0 );

    std::string const cxx_node_id_str = node_id_a.toString();
    ASSERT_TRUE( cxx_node_id_str.compare( node_id_str ) == 0 );

    /* Create a second nodeId instance from the node_id_str */

    node_id_t node_id_b( cxx_node_id_str );

    /* Verify that both node_id_a and node_id_b are identical */

    ASSERT_TRUE( node_id_b.archId() == st::ARCHITECTURE_ILLEGAL );
    ASSERT_TRUE( node_id_a.platformId() == node_id_b.platformId() );
    ASSERT_TRUE( node_id_a.deviceId()   == node_id_b.deviceId() );

    /* We can manually set the arch_id of node_id_b to the same value as
     * node_id_a: */

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        node_id_b.setArchId( node_id_a.archId() ) );

    /* Now verify that both node_id_a and node_id_b are identical */

    ASSERT_TRUE( 0 == node_id_a.compare( node_id_b ) );
    ASSERT_TRUE( node_id_a == node_id_b );

    ASSERT_TRUE( node_id_a.archId()     == node_id_b.archId() );
    ASSERT_TRUE( node_id_a.platformId() == node_id_b.platformId() );
    ASSERT_TRUE( node_id_a.deviceId()   == node_id_b.deviceId() );

    /* Changing the platform and/or the device id on one of the nodes will
     * change equality relations */

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
                node_id_b.setPlatformId( platform_id_t{ 1 } ) );

    ASSERT_TRUE(  0 != node_id_a.compare( node_id_b ) );
    ASSERT_TRUE( -1 == node_id_a.compare( node_id_b ) );

    ASSERT_TRUE( node_id_a.platformId() != node_id_b.platformId() );
    ASSERT_TRUE( node_id_a.deviceId()   == node_id_b.deviceId() );

    /* Create a node_id_str with NS(NODE_ID_STR_FORMAT_ARCHID) from node_id_b
     * to sync node_id_a: */

    node_id_a.clear();
    ASSERT_TRUE( node_id_a.compare( node_id_b ) != 0 );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == node_id_b.toString(
        node_id_str, NODE_ID_STR_CAPACITY, st::NODE_ID_STR_FORMAT_ARCHID ) );

    std::ostringstream cmp_node_id_str;

    cmp_node_id_str << node_id_b.archId()  << ":" << node_id_b.platformId()
                    << "." << node_id_b.deviceId();

    ASSERT_TRUE( cmp_node_id_str.str().compare( node_id_str ) == 0 );
    cmp_node_id_str.str( "" );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == node_id_a.fromString( node_id_str ) );
    ASSERT_TRUE( node_id_b.compare( node_id_a ) == 0 );

    /* Create a node_id_str with NS(NODE_ID_STR_FORMAT_ARCHSTR) from node_id_b
     * to sync node_id_a: */

    node_id_a.clear();
    ASSERT_TRUE( node_id_a.compare( node_id_b ) != 0 );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == node_id_b.toString( node_id_str,
        NODE_ID_STR_CAPACITY, st::NODE_ID_STR_FORMAT_ARCHSTR) );

    cmp_node_id_str << archs.archStr( node_id_b.archId() )
                    << ":" << node_id_b.platformId()
                    << "." << node_id_b.deviceId();

    ASSERT_TRUE( cmp_node_id_str.str().compare( node_id_str ) == 0 );
    cmp_node_id_str.str( "" );

    ASSERT_TRUE( node_id_a.fromString( node_id_str ) == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( node_id_b.compare( node_id_a ) == 0 );
}


TEST( CXX_CommonControlNodeIdTests, NodeIdStrHandlingDetailed )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using node_id_t             = st::NodeId;
    using platform_id_t         = node_id_t::platform_id_t;
    using device_id_t           = node_id_t::device_id_t;
    using ctrl_size_t           = node_id_t::size_type;
    using node_id_str_fmt_t     = node_id_t::format_t;
    using status_t              = st::arch_status_t;
    using arch_id_t             = st::arch_id_t;

    static constexpr ctrl_size_t NODE_ID_STR_CAPACITY = ctrl_size_t{ 32 };

    char node_id_str[] =
    {
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
    };

    /* Verify that a suitable arch is available */
    st::Architectures const& archs = st::Architectures_get_const();
    SIXTRL_ASSERT( archs.numArchitectures() > size_t{ 0 } );

    arch_id_t const arch = archs.archIdByNumber( size_t{ 0 } );
    SIXTRL_ASSERT( arch != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch != st::ARCHITECTURE_NONE );

    SIXTRL_ASSERT(  archs.hasArchitecture( arch ) );
    SIXTRL_ASSERT(  archs.isAvailable( arch ) );
    SIXTRL_ASSERT( !archs.isShutdown( arch ) );

    node_id_t node_id_a;

    ASSERT_TRUE( !node_id_a.valid() );
    ASSERT_TRUE(  node_id_a.archId()     == st::ARCHITECTURE_ILLEGAL );
    ASSERT_TRUE(  node_id_a.platformId() == st::NODE_ILLEGAL_PLATFORM_ID );
    ASSERT_TRUE(  node_id_a.deviceId()   == st::NODE_ILLEGAL_DEVICE_ID );

    /* --------------------------------------------------------------------- */
    /* NODE_ID_STR_FORMAT_NOARCH: */

    node_id_str_fmt_t format = node_id_t::IdentifyFormat( "0.0" );
    ASSERT_TRUE(  format == st::NODE_ID_STR_FORMAT_NOARCH) ;

    status_t status = node_id_a.fromString( "0.0" );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS) ;
    ASSERT_TRUE(  node_id_a.archId()     == st::ARCHITECTURE_ILLEGAL );
    ASSERT_TRUE(  node_id_a.platformId() == platform_id_t{ 0 } );
    ASSERT_TRUE(  node_id_a.deviceId()   == device_id_t{ 0 } );

    /* arch_id is set to an illegal value -> it should not work to convert to
     * a node_id_str which requires this parameter to be ok: */

    status = node_id_a.toString( node_id_str, NODE_ID_STR_CAPACITY,
            st::NODE_ID_STR_FORMAT_ARCHID );

    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS) ;

    status = node_id_a.toString( node_id_str, NODE_ID_STR_CAPACITY,
            st::NODE_ID_STR_FORMAT_ARCHSTR );

    ASSERT_TRUE( status != st::ARCH_STATUS_SUCCESS) ;

    /* check that creating a new NodeId directly from a vallid nodE_id_str
     * of no-arch does work */

    node_id_t node_id_b( "0.0" );

    ASSERT_TRUE( node_id_a.archId()     == node_id_b.archId() );
    ASSERT_TRUE( node_id_a.platformId() == node_id_b.platformId() );
    ASSERT_TRUE( node_id_a.deviceId()   == node_id_b.deviceId() );

    /* --------------------------------------------------------------------- */
    /* NODE_ID_STR_FORMAT_ARCHID: */

    std::ostringstream a2str;
    platform_id_t cmp_platform_id = platform_id_t{ 2 };
    device_id_t cmp_device_id = device_id_t{ 3 };

    a2str << arch << ":" << cmp_platform_id << "." << cmp_device_id;

    std::string cmp_node_id_str = a2str.str();

    format = node_id_t::IdentifyFormat( cmp_node_id_str );
    ASSERT_TRUE( format == st::NODE_ID_STR_FORMAT_ARCHID) ;

    status = node_id_a.fromString( cmp_node_id_str.c_str() );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS) ;
    ASSERT_TRUE( node_id_a.archId()  == arch );

    ASSERT_TRUE( node_id_a.platformId() == cmp_platform_id );
    ASSERT_TRUE( node_id_a.deviceId()   == cmp_device_id );
    ASSERT_TRUE( node_id_a.valid() );

    node_id_t node_id_c( cmp_node_id_str );

    ASSERT_TRUE( node_id_c.archId()     == arch );
    ASSERT_TRUE( node_id_c.platformId() == cmp_platform_id );
    ASSERT_TRUE( node_id_c.deviceId()   == cmp_device_id );
    ASSERT_TRUE( node_id_c.valid() );

    ASSERT_TRUE( node_id_a.compare( node_id_c ) == 0 );
    ASSERT_TRUE( node_id_a == node_id_c );

    status = node_id_a.toString( node_id_str,
        NODE_ID_STR_CAPACITY, st::NODE_ID_STR_FORMAT_ARCHID );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS) ;
    ASSERT_TRUE( cmp_node_id_str.compare( node_id_str ) == 0 );

    status = node_id_a.toString( node_id_str,
        NODE_ID_STR_CAPACITY, st::NODE_ID_STR_FORMAT_NOARCH );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS) ;
    a2str.str( "" );
    a2str << cmp_platform_id << "." << cmp_device_id;

    ASSERT_TRUE( a2str.str().compare( node_id_str ) == 0 );

    status = node_id_a.toString( node_id_str,
        NODE_ID_STR_CAPACITY, st::NODE_ID_STR_FORMAT_ARCHSTR );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS) ;

    a2str.str( "" );
    a2str << archs.archStr( arch )
          << ":" << cmp_platform_id << "." << cmp_device_id;

    cmp_node_id_str = a2str.str();
    ASSERT_TRUE( cmp_node_id_str.compare( node_id_str ) == 0 );

    /* --------------------------------------------------------------------- */
    /* NODE_ID_STR_FORMAT_ARCHSTR: */

    format = node_id_t::IdentifyFormat( cmp_node_id_str );
    ASSERT_TRUE( format == st::NODE_ID_STR_FORMAT_ARCHSTR) ;

    status = node_id_b.fromString( cmp_node_id_str.c_str() );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS) ;

    ASSERT_TRUE( node_id_b.archId()     == arch );
    ASSERT_TRUE( node_id_b.platformId() == cmp_platform_id );
    ASSERT_TRUE( node_id_b.deviceId()   == cmp_device_id );
    ASSERT_TRUE( node_id_b.valid() );

    node_id_t node_id_d( cmp_node_id_str );

    ASSERT_TRUE( node_id_d.archId()     == arch );
    ASSERT_TRUE( node_id_d.platformId() == cmp_platform_id );
    ASSERT_TRUE( node_id_d.deviceId()   == cmp_device_id );
    ASSERT_TRUE( node_id_d.valid() );

    ASSERT_TRUE( node_id_b.compare( node_id_d ) == 0 );
    ASSERT_TRUE( node_id_b == node_id_d );

    ASSERT_TRUE( node_id_a.compare( node_id_b ) == 0 );
    ASSERT_TRUE( node_id_a == node_id_b );
}


TEST( CXX_CommonControlNodeIdTests, ExtractNodeIdFromConfigStr )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using node_id_t  = st::NodeId;
    using buf_size_t = node_id_t::size_type;
    using status_t   = node_id_t::status_t;
    std::string conf_str( "" );

    st::buffer_size_t const max_out_str_len = 32u;
    char device_id_str[ 32 ];
    std::memset( &device_id_str[ 0 ], ( int )'\0', max_out_str_len );

    status_t ret = st::NodeId::ExtractNodeIdStrFromConfigStr(
        max_out_str_len, &device_id_str[ 0 ], conf_str.c_str() );

    ASSERT_TRUE( ret != st::ARCH_STATUS_SUCCESS) ;
    ASSERT_TRUE( std::strlen( &device_id_str[ 0 ] ) == buf_size_t{ 0 } );

    conf_str = "0.0";
    std::memset( &device_id_str[ 0 ], ( int )'\0', max_out_str_len );

    ret = st::NodeId::ExtractNodeIdStrFromConfigStr(
        max_out_str_len, &device_id_str[ 0 ], conf_str.c_str() );

    ASSERT_TRUE( ret == st::ARCH_STATUS_SUCCESS) ;
    ASSERT_TRUE( std::strcmp( &device_id_str[ 0 ], "0.0" ) == 0 );

    conf_str = "  0.0  ";
    std::memset( &device_id_str[ 0 ], ( int )'\0', max_out_str_len );

    ret = st::NodeId::ExtractNodeIdStrFromConfigStr(
        max_out_str_len, &device_id_str[ 0 ], conf_str.c_str() );

    ASSERT_TRUE( ret == st::ARCH_STATUS_SUCCESS) ;
    ASSERT_TRUE( std::strcmp( &device_id_str[ 0 ], "0.0" ) == 0 );
}

/* end: tests/sixtracklib/common/control/test_node_id_c99.cpp */
