#include "sixtracklib/common/control/node_id.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"
#include "sixtracklib/common/architecture/architecture.h"
#include "sixtracklib/testlib.h"

TEST( C99_CommonControlNodeIdTests, MinimalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using node_id_t             = ::NS(NodeId);
    using platform_id_t         = ::NS(node_platform_id_t);
    using device_id_t           = ::NS(node_device_id_t);
    using ctrl_size_t           = ::NS(ctrl_size_t);
    using node_id_str_fmt_t     = ::NS(node_id_str_fmt_t);

    char node_id_str[] =
    {
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
    };

    static constexpr ctrl_size_t TOO_SHORT_ID_STR_CAPACITY = ctrl_size_t{ 3 };
    static constexpr ctrl_size_t NODE_ID_STR_CAPACITY = ctrl_size_t{ 32 };

    static constexpr node_id_str_fmt_t FORMAT = ::NS(NODE_ID_STR_FORMAT_NOARCH);

    /* Verify that one suitable architecture is available */
    ::NS(Architectures) const* ptr_archs = ::NS(Architectures_get_const_ptr)();
    SIXTRL_ASSERT( ptr_archs != nullptr );
    SIXTRL_ASSERT( ::NS(Architectures_get_num_architectures)(
        ptr_archs ) > ctrl_size_t{ 0 } );

    ::NS(arch_id_t) const arch = ::NS(Architectures_get_arch_id_by_number)(
        ptr_archs, ctrl_size_t{ 0 } );

    SIXTRL_ASSERT(  arch != ::NS(ARCHITECTURE_ILLEGAL) );
    SIXTRL_ASSERT(  arch != ::NS(ARCHITECTURE_NONE) );
    SIXTRL_ASSERT(  ::NS(Architectures_has_architecture)( ptr_archs, arch ) );
    SIXTRL_ASSERT(  ::NS(Architectures_is_available)( ptr_archs, arch ) );
    SIXTRL_ASSERT( !::NS(Architectures_is_shutdown)( ptr_archs, arch ) );


    /* Create an empty, non-initialized nodeId instance */

    node_id_t* node_id_a = ::NS(NodeId_create)( ::NS(ARCHITECTURE_ILLEGAL) );
    ASSERT_TRUE(  node_id_a != nullptr );

    /* Verify that all properties are set to the initial state */

    ASSERT_TRUE( !::NS(NodeId_is_valid)( node_id_a ) );

    ASSERT_TRUE( ::NS(NodeId_get_arch_id)( node_id_a ) ==
                 ::NS(ARCHITECTURE_ILLEGAL) );

    ASSERT_TRUE(  ::NS(NodeId_get_platform_id)( node_id_a ) ==
                  ::NS(NODE_ILLEGAL_PLATFORM_ID) );

    ASSERT_TRUE(  ::NS(NodeId_get_device_id)( node_id_a ) ==
                  ::NS(NODE_ILLEGAL_DEVICE_ID) );

    /* creating a node_id string from an illegal nodeId should never work,
       regardless whether the buffer is large enough or not */

    ASSERT_TRUE( ::NS(ARCH_STATUS_SUCCESS) !=
        ::NS(NodeId_to_node_id_str_with_format)( node_id_a,
                TOO_SHORT_ID_STR_CAPACITY, node_id_str, FORMAT ) );

    ASSERT_TRUE( ::NS(ARCH_STATUS_SUCCESS) !=
        ::NS(NodeId_to_node_id_str_with_format)( node_id_a,
            NODE_ID_STR_CAPACITY, node_id_str, FORMAT ) );

    /* Setting the platform_id to a valid value should not change the
       overall picture much: */

    ASSERT_TRUE( ::NS(ARCH_STATUS_SUCCESS) ==
        ::NS(NodeId_set_platform_id)( node_id_a, platform_id_t{ 0 } ) );

    ASSERT_TRUE( !::NS(NodeId_is_valid)( node_id_a ) );
    ASSERT_TRUE(  ::NS(NodeId_get_platform_id)( node_id_a ) ==
                  platform_id_t{ 0 } );

    ASSERT_TRUE( ::NS(ARCH_STATUS_SUCCESS) !=
        ::NS(NodeId_to_node_id_str_with_format)( node_id_a,
            TOO_SHORT_ID_STR_CAPACITY, node_id_str, FORMAT ) );

    ASSERT_TRUE( ::NS(ARCH_STATUS_SUCCESS) !=
        ::NS(NodeId_to_node_id_str_with_format)( node_id_a,
            NODE_ID_STR_CAPACITY, node_id_str, FORMAT ) );

    /* Setting also the device *and* the arch_id makes however a difference: */

    ASSERT_TRUE( ::NS(ARCH_STATUS_SUCCESS) ==
        ::NS(NodeId_set_arch_id)( node_id_a, arch ) );

    ASSERT_TRUE( ::NS(ARCH_STATUS_SUCCESS) ==
        ::NS(NodeId_set_device_id)( node_id_a, device_id_t{ 0 } ) );

    ASSERT_TRUE( ::NS(NodeId_is_valid)( node_id_a ) );

    ASSERT_TRUE( ::NS(NodeId_get_platform_id)( node_id_a ) ==
                 platform_id_t{ 0 } );

    ASSERT_TRUE( ::NS(NodeId_get_device_id)( node_id_a ) ==
                 device_id_t{ 0 } );

    /* Now we should be able to create a node_id_str if we provide a
       large enough string buffer */

    ASSERT_TRUE( ::NS(NodeId_to_node_id_str_with_format)( node_id_a,
            TOO_SHORT_ID_STR_CAPACITY, node_id_str, FORMAT ) !=
                ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE( ::NS(NodeId_to_node_id_str_with_format)( node_id_a,
            NODE_ID_STR_CAPACITY, node_id_str, FORMAT ) ==
                ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE(  std::strcmp( node_id_str, "0.0" ) == 0 );

    /* Create a second nodeId instance from the node_id_str */

    node_id_t* node_id_b = ::NS(NodeId_new_from_string)( node_id_str );
    ASSERT_TRUE( node_id_b != nullptr );

    /* node_id_b has been reconstructed from node_id_a's node_id_str, but the
     * string format was NODE_ID_STR_FORMAT_NOARCH -> node_id_b should be
     * identical to node_id_a up until the archId(): */

    ASSERT_TRUE( ::NS(NodeId_get_arch_id)( node_id_b ) ==
                 ::NS(ARCHITECTURE_ILLEGAL) );

    ASSERT_TRUE( ::NS(NodeId_get_arch_id)( node_id_b ) !=
                 ::NS(NodeId_get_arch_id)( node_id_a ) );

    ASSERT_TRUE( ::NS(NodeId_get_platform_id)( node_id_b ) ==
                 ::NS(NodeId_get_platform_id)( node_id_a ) );

    ASSERT_TRUE( ::NS(NodeId_get_device_id)( node_id_b ) ==
                 ::NS(NodeId_get_device_id)( node_id_a ) );

    /* We can manually set the arch_id of node_id_b to the same value as
     * node_id_a: */

    ASSERT_TRUE( ::NS(ARCH_STATUS_SUCCESS) == ::NS(NodeId_set_arch_id)(
        node_id_b, ::NS(NodeId_get_arch_id)( node_id_a) ) );

    /* Now verify that both node_id_a and node_id_b are identical */

    ASSERT_TRUE( 0 == ::NS(NodeId_compare)( node_id_a, node_id_b ) );

    ASSERT_TRUE( ::NS(NodeId_get_arch_id)( node_id_b ) ==
                 ::NS(NodeId_get_arch_id)( node_id_a ) );

    ASSERT_TRUE( ::NS(NodeId_get_platform_id)( node_id_a ) ==
                 ::NS(NodeId_get_platform_id)( node_id_b ) );

    ASSERT_TRUE( ::NS(NodeId_get_device_id)( node_id_a ) ==
                 ::NS(NodeId_get_device_id)( node_id_b ) );

    /* Changing the platform and/or the device id on one of the nodes will
     * change equality relations */

    ::NS(NodeId_set_platform_id)( node_id_b, platform_id_t{ 1 } );

    ASSERT_TRUE(  0 != ::NS(NodeId_compare)( node_id_a, node_id_b ) );
    ASSERT_TRUE( -1 == ::NS(NodeId_compare)( node_id_a, node_id_b ) );

    ASSERT_TRUE( ::NS(NodeId_get_platform_id)( node_id_a ) !=
                 ::NS(NodeId_get_platform_id)( node_id_b ) );

    ASSERT_TRUE( ::NS(NodeId_get_device_id)( node_id_a ) ==
                 ::NS(NodeId_get_device_id)( node_id_b ) );

    /* Create a node_id_str with NS(NODE_ID_STR_FORMAT_ARCHID) from node_id_b
     * to sync node_id_a: */

    ::NS(NodeId_clear)( node_id_a );
    ASSERT_TRUE( ::NS(NodeId_compare)( node_id_a, node_id_b ) != 0 );

    ASSERT_TRUE( ::NS(ARCH_STATUS_SUCCESS) ==
        ::NS(NodeId_to_node_id_str_with_format)( node_id_b, NODE_ID_STR_CAPACITY,
            node_id_str,::NS(NODE_ID_STR_FORMAT_ARCHID) ) );

    std::ostringstream cmp_node_id_str;

    cmp_node_id_str << ::NS(NodeId_get_arch_id)( node_id_b ) << ":" <<
        ::NS(NodeId_get_platform_id)( node_id_b ) << "." <<
        ::NS(NodeId_get_device_id)( node_id_b );

    ASSERT_TRUE( cmp_node_id_str.str().compare( node_id_str ) == 0 );
    cmp_node_id_str.str( "" );

    ASSERT_TRUE( ::NS(NodeId_from_node_id_str)( node_id_a, node_id_str ) ==
        ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE( ::NS(NodeId_compare)( node_id_b, node_id_a ) == 0 );

    /* Create a node_id_str with NS(NODE_ID_STR_FORMAT_ARCHSTR) from node_id_b
     * to sync node_id_a: */

    ::NS(NodeId_clear)( node_id_a );
    ASSERT_TRUE( ::NS(NodeId_compare)( node_id_a, node_id_b ) != 0 );

    ASSERT_TRUE( ::NS(ARCH_STATUS_SUCCESS) ==
        ::NS(NodeId_to_node_id_str_with_format)( node_id_b, NODE_ID_STR_CAPACITY,
            node_id_str,::NS(NODE_ID_STR_FORMAT_ARCHSTR) ) );

    cmp_node_id_str << NS(Architectures_get_arch_str)( ptr_archs,
            ::NS(NodeId_get_arch_id)( node_id_b ) )
        << ":" << ::NS(NodeId_get_platform_id)( node_id_b )
        << "." << ::NS(NodeId_get_device_id)( node_id_b );

    ASSERT_TRUE( cmp_node_id_str.str().compare( node_id_str ) == 0 );
    cmp_node_id_str.str( "" );

    ASSERT_TRUE( ::NS(NodeId_from_node_id_str)( node_id_a, node_id_str ) ==
        ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE( ::NS(NodeId_compare)( node_id_b, node_id_a ) == 0 );

    /* Cleanup */

    ::NS(NodeId_delete)( node_id_a );
    node_id_a = nullptr;

    ::NS(NodeId_delete)( node_id_b );
    node_id_b = nullptr;
}

TEST( C99_CommonControlNodeIdTests, NodeIdStrHandlingDetailed )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using platform_id_t         = ::NS(node_platform_id_t);
    using device_id_t           = ::NS(node_device_id_t);
    using ctrl_size_t           = ::NS(ctrl_size_t);
    using node_id_str_fmt_t     = ::NS(node_id_str_fmt_t);
    using status_t              = ::NS(arch_status_t);

    static constexpr ctrl_size_t NODE_ID_STR_CAPACITY = ctrl_size_t{ 32 };

    char node_id_str[] =
    {
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
    };

    /* Verify that one suitable architecture is available */
    ::NS(Architectures) const* ptr_archs = ::NS(Architectures_get_const_ptr)();
    SIXTRL_ASSERT( ptr_archs != nullptr );
    SIXTRL_ASSERT( ::NS(Architectures_get_num_architectures)(
        ptr_archs ) > ctrl_size_t{ 0 } );

    ::NS(arch_id_t) const arch = ::NS(Architectures_get_arch_id_by_number)(
        ptr_archs, ctrl_size_t{ 0 } );

    SIXTRL_ASSERT(  arch != ::NS(ARCHITECTURE_ILLEGAL) );
    SIXTRL_ASSERT(  arch != ::NS(ARCHITECTURE_NONE) );
    SIXTRL_ASSERT(  ::NS(Architectures_has_architecture)( ptr_archs, arch ) );
    SIXTRL_ASSERT(  ::NS(Architectures_is_available)( ptr_archs, arch ) );
    SIXTRL_ASSERT( !::NS(Architectures_is_shutdown)( ptr_archs, arch ) );



    ::NS(NodeId)* node_id_a = ::NS(NodeId_create)( ::NS(ARCHITECTURE_ILLEGAL) );

    ASSERT_TRUE( node_id_a != nullptr );

    ASSERT_TRUE( ::NS(NodeId_get_arch_id)( node_id_a ) ==
                 ::NS(ARCHITECTURE_ILLEGAL) );

    ASSERT_TRUE( ::NS(NODE_ILLEGAL_PLATFORM_ID) ==
                 ::NS(NodeId_get_platform_id)( node_id_a ) );

    ASSERT_TRUE( ::NS(NODE_ILLEGAL_DEVICE_ID) ==
                 ::NS(NodeId_get_device_id)( node_id_a ) );

    /* --------------------------------------------------------------------- */
    /* NODE_ID_STR_FORMAT_NOARCH: */

    node_id_str_fmt_t format =
        ::NS(NodeId_identify_format_from_node_id_str)( "0.0" );

    ASSERT_TRUE(  format == ::NS(NODE_ID_STR_FORMAT_NOARCH) );

    status_t status = ::NS(NodeId_from_node_id_str)( node_id_a, "0.0" );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE( ::NS(NodeId_get_arch_id)( node_id_a ) ==
                 ::NS(ARCHITECTURE_ILLEGAL) );

    ASSERT_TRUE( ::NS(NODE_ILLEGAL_PLATFORM_ID) !=
                 ::NS(NodeId_get_platform_id)( node_id_a ) );

    ASSERT_TRUE( device_id_t{ 0 } == ::NS(NodeId_get_platform_id)( node_id_a ) );

    ASSERT_TRUE( platform_id_t{ 0 } ==
                 ::NS(NodeId_get_device_id)( node_id_a ) );

    /* arch_id is set to an illegal value -> it should not work to convert to
     * a node_id_str which requires this parameter to be ok: */

    status = ::NS(NodeId_to_node_id_str_with_format)( node_id_a,
        NODE_ID_STR_CAPACITY, node_id_str, ::NS(NODE_ID_STR_FORMAT_ARCHID) );

    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(NodeId_to_node_id_str_with_format)( node_id_a,
        NODE_ID_STR_CAPACITY, node_id_str, ::NS(NODE_ID_STR_FORMAT_ARCHSTR) );

    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );

    /* check that creating a new NodeId directly from a vallid nodE_id_str
     * of no-arch does work */

    ::NS(NodeId)* node_id_b = ::NS(NodeId_new_from_string)( "0.0" );
    ASSERT_TRUE( node_id_b != nullptr );

    ASSERT_TRUE( ::NS(NodeId_get_arch_id)( node_id_a ) ==
                 ::NS(NodeId_get_arch_id)( node_id_b ) );

    ASSERT_TRUE( ::NS(NodeId_get_platform_id)( node_id_a ) ==
                 ::NS(NodeId_get_platform_id)( node_id_b ) );

    ASSERT_TRUE( ::NS(NodeId_get_device_id)( node_id_a ) ==
                 ::NS(NodeId_get_device_id)( node_id_b ) );

    /* --------------------------------------------------------------------- */
    /* NODE_ID_STR_FORMAT_ARCHID: */

    std::ostringstream a2str;
    platform_id_t cmp_platform_id = platform_id_t{ 2 };
    device_id_t cmp_device_id = device_id_t{ 3 };

    a2str << arch << ":" << cmp_platform_id << "." << cmp_device_id;

    std::string cmp_node_id_str = a2str.str();

    format = ::NS(NodeId_identify_format_from_node_id_str)(
            cmp_node_id_str.c_str() );

    ASSERT_TRUE( format == ::NS(NODE_ID_STR_FORMAT_ARCHID) );

    status = ::NS(NodeId_from_node_id_str)(
        node_id_a, cmp_node_id_str.c_str() );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeId_get_arch_id)( node_id_a ) == arch );
    ASSERT_TRUE( ::NS(NodeId_get_platform_id)( node_id_a ) == cmp_platform_id );
    ASSERT_TRUE( ::NS(NodeId_get_device_id)( node_id_a ) == cmp_device_id );
    ASSERT_TRUE( ::NS(NodeId_is_valid)( node_id_a ) );

    ::NS(NodeId)* node_id_c = ::NS(NodeId_new_from_string)(
        cmp_node_id_str.c_str() );

    ASSERT_TRUE( node_id_c != nullptr );
    ASSERT_TRUE( ::NS(NodeId_get_arch_id)( node_id_c ) == arch );
    ASSERT_TRUE( ::NS(NodeId_get_platform_id)( node_id_c ) == cmp_platform_id );
    ASSERT_TRUE( ::NS(NodeId_get_device_id)( node_id_c ) == cmp_device_id );
    ASSERT_TRUE( ::NS(NodeId_is_valid)( node_id_c ) );

    ASSERT_TRUE( ::NS(NodeId_compare)( node_id_a, node_id_c ) == 0 );

    status = ::NS(NodeId_to_node_id_str_with_format)( node_id_a,
        NODE_ID_STR_CAPACITY, node_id_str, ::NS(NODE_ID_STR_FORMAT_ARCHID) );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( cmp_node_id_str.compare( node_id_str ) == 0 );

    status = ::NS(NodeId_to_node_id_str_with_format)( node_id_a,
        NODE_ID_STR_CAPACITY, node_id_str, ::NS(NODE_ID_STR_FORMAT_NOARCH) );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    a2str.str( "" );
    a2str << cmp_platform_id << "." << cmp_device_id;

    ASSERT_TRUE( a2str.str().compare( node_id_str ) == 0 );

    status = ::NS(NodeId_to_node_id_str_with_format)( node_id_a,
        NODE_ID_STR_CAPACITY, node_id_str, ::NS(NODE_ID_STR_FORMAT_ARCHSTR) );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    a2str.str( "" );
    a2str << ::NS(Architectures_get_arch_str)( ptr_archs, arch )
          << ":" << cmp_platform_id << "." << cmp_device_id;

    cmp_node_id_str = a2str.str();
    ASSERT_TRUE( cmp_node_id_str.compare( node_id_str ) == 0 );

    /* --------------------------------------------------------------------- */
    /* NODE_ID_STR_FORMAT_ARCHSTR: */

    format = ::NS(NodeId_identify_format_from_node_id_str)(
            cmp_node_id_str.c_str() );

    ASSERT_TRUE( format == ::NS(NODE_ID_STR_FORMAT_ARCHSTR) );

    status = ::NS(NodeId_from_node_id_str)(
        node_id_b, cmp_node_id_str.c_str() );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE( ::NS(NodeId_get_arch_id)( node_id_b ) == arch );
    ASSERT_TRUE( ::NS(NodeId_get_platform_id)( node_id_b ) == cmp_platform_id );
    ASSERT_TRUE( ::NS(NodeId_get_device_id)( node_id_b ) == cmp_device_id );
    ASSERT_TRUE( ::NS(NodeId_is_valid)( node_id_b )  );

    ::NS(NodeId)* node_id_d = ::NS(NodeId_new_from_string)(
        cmp_node_id_str.c_str() );

    ASSERT_TRUE( node_id_d != nullptr );
    ASSERT_TRUE( ::NS(NodeId_get_arch_id)( node_id_d ) == arch );
    ASSERT_TRUE( ::NS(NodeId_get_platform_id)( node_id_d ) == cmp_platform_id );
    ASSERT_TRUE( ::NS(NodeId_get_device_id)( node_id_d ) == cmp_device_id );
    ASSERT_TRUE( ::NS(NodeId_is_valid)( node_id_d )  );

    ASSERT_TRUE( ::NS(NodeId_compare)( node_id_b, node_id_d ) == 0 );
    ASSERT_TRUE( ::NS(NodeId_compare)( node_id_a, node_id_b ) == 0 );

    /* --------------------------------------------------------------------- */

    ::NS(NodeId_delete)( node_id_a );
    ::NS(NodeId_delete)( node_id_b );
    ::NS(NodeId_delete)( node_id_c );
    ::NS(NodeId_delete)( node_id_d );
}


TEST( C99_CommonControlNodeIdTests, ExtractNodeIdFromConfigStr )
{
    using buf_size_t = ::NS(buffer_size_t);
    using status_t   = ::NS(ctrl_status_t);
    std::string conf_str( "" );

    ::NS(buffer_size_t) const max_out_str_len = 32u;
    char device_id_str[ 32 ];
    std::memset( &device_id_str[ 0 ], ( int )'\0', max_out_str_len );

    status_t ret = ::NS(NodeId_extract_node_id_str_from_config_str)(
        max_out_str_len, &device_id_str[ 0 ], conf_str.c_str() );

    ASSERT_TRUE( ret != ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( std::strlen( &device_id_str[ 0 ] ) == buf_size_t{ 0 } );

    conf_str = "0.0";
    std::memset( &device_id_str[ 0 ], ( int )'\0', max_out_str_len );

    ret = ::NS(NodeId_extract_node_id_str_from_config_str)(
        max_out_str_len, &device_id_str[ 0 ], conf_str.c_str() );

    ASSERT_TRUE( ret == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( std::strcmp( &device_id_str[ 0 ], "0.0" ) == 0 );

    conf_str = "  0.0  ";
    std::memset( &device_id_str[ 0 ], ( int )'\0', max_out_str_len );

    ret = ::NS(NodeId_extract_node_id_str_from_config_str)(
        max_out_str_len, &device_id_str[ 0 ], conf_str.c_str() );

    ASSERT_TRUE( ret == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( std::strcmp( &device_id_str[ 0 ], "0.0" ) == 0 );
}

/* end: tests/sixtracklib/common/control/test_node_id_c99.cpp */
