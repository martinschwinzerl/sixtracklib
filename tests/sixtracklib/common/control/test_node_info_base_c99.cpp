#include "sixtracklib/common/control/node_info.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/architecture.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_info.hpp"
#include "sixtracklib/testlib.h"

TEST( C99_CommonControlNodeInfoBaseTests, NodeInfoCreationNoNodeStore )
{
    using node_id_t             = ::NS(NodeId);
    using node_info_t           = ::NS(NodeInfoBase);
    using platform_id_t         = ::NS(node_platform_id_t);
    using device_id_t           = ::NS(node_device_id_t);
    using size_t                = ::NS(arch_size_t);
    using status_t              = ::NS(arch_status_t);

    /* Verify that one suitable architecture is available */
    ::NS(Architectures) const* ptr_archs = ::NS(Architectures_get_ptr_const)();
    SIXTRL_ASSERT( ptr_archs != nullptr );
    SIXTRL_ASSERT( ::NS(Architectures_get_num_architectures)(
        ptr_archs ) > size_t{ 0 } );

    ::NS(arch_id_t) const arch_id = ::NS(Architectures_get_arch_id_by_number)(
        ptr_archs, size_t{ 0 } );

    SIXTRL_ASSERT(  arch_id != ::NS(ARCHITECTURE_ILLEGAL) );
    SIXTRL_ASSERT(  arch_id != ::NS(ARCHITECTURE_NONE) );
    SIXTRL_ASSERT(  ::NS(Architectures_has_architecture)( ptr_archs, arch_id ) );
    SIXTRL_ASSERT(  ::NS(Architectures_is_available)( ptr_archs, arch_id ) );
    SIXTRL_ASSERT( !::NS(Architectures_is_shutdown)( ptr_archs, arch_id ) );

    char node_id_str[] =
    {
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
    };

    /* --------------------------------------------------------------------- */

    node_info_t* node_info_a = ::NS(NodeInfoBase_create)( arch_id, nullptr );
    ASSERT_TRUE( node_info_a != nullptr );

    ASSERT_TRUE( !::NS(NodeInfo_has_node_store)( node_info_a ) );
    ASSERT_TRUE( ::NS(NodeInfo_get_ptr_const_node_store)(
        node_info_a ) == nullptr );

    ASSERT_TRUE(  ::NS(NodeInfo_get_arch_id)( node_info_a ) == arch_id );
    ASSERT_TRUE(  ::NS(NodeInfo_has_arch_str)( node_info_a ) );
    ASSERT_TRUE(  std::strcmp( ::NS(NodeInfo_get_arch_str)( node_info_a ),
        ::NS(Architectures_get_arch_str)( ptr_archs, arch_id ) ) == 0 );

    ASSERT_TRUE( !::NS(NodeId_is_valid)(
        ::NS(NodeInfo_get_ptr_const_node_id)( node_info_a ) ) );
    ASSERT_TRUE(  ::NS(NodeInfo_get_platform_id)( node_info_a )
        == ::NS(NODE_ILLEGAL_PLATFORM_ID) );
    ASSERT_TRUE(  ::NS(NodeInfo_get_device_id)( node_info_a )
        == ::NS(NODE_ILLEGAL_DEVICE_ID) );

    ASSERT_TRUE( !::NS(NodeInfo_has_device_name)( node_info_a ) );
    ASSERT_TRUE( !::NS(NodeInfo_has_platform_name)( node_info_a ) );
    ASSERT_TRUE( !::NS(NodeInfo_has_description)( node_info_a ) );
    ASSERT_TRUE( !::NS(NodeInfo_has_unique_id_str)( node_info_a ) );

    status_t status = NS(NodeInfo_set_platform_id)(
        node_info_a, platform_id_t{ 3 } );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = NS(NodeInfo_set_device_id)( node_info_a, device_id_t{ 14 } );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE( ::NS(NodeId_is_valid)(
        ::NS(NodeInfo_get_ptr_const_node_id)( node_info_a ) ) );
    ASSERT_TRUE( ::NS(NodeInfo_get_platform_id)(
        node_info_a ) == platform_id_t{ 3 } );
    ASSERT_TRUE( ::NS(NodeInfo_get_device_id)(
        node_info_a ) == device_id_t{ 14 } );

    ::NS(NodeInfo_set_platform_name)( node_info_a, "platform_a" );
    ASSERT_TRUE( ::NS(NodeInfo_has_platform_name)( node_info_a ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_platform_name_str)(
        node_info_a ), "platform_a" ) == 0 );

    ::NS(NodeInfo_set_device_name)( node_info_a, "device_a" );
    ASSERT_TRUE( ::NS(NodeInfo_has_device_name)( node_info_a ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_device_name_str)(
        node_info_a ), "device_a" ) == 0 );

    ::NS(NodeInfo_set_description)( node_info_a, "description_a" );
    ASSERT_TRUE( ::NS(NodeInfo_has_description)( node_info_a ) );
    ASSERT_TRUE( std::strcmp( ::NS(NodeInfo_get_description_str)(
        node_info_a ), "description_a" ) == 0 );

    node_id_t temp_node_id;
    ::NS(NodeId_preset)( &temp_node_id );
    status = ::NS(NodeId_init)( &temp_node_id, arch_id,
        ::NS(NODE_ILLEGAL_PLATFORM_ID), ::NS(NODE_ILLEGAL_DEVICE_ID) );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    ::NS(NodeId_set_platform_id)( &temp_node_id, platform_id_t{ 2 } );
    ::NS(NodeId_set_device_id)( &temp_node_id, device_id_t{ 72 } );

    status = ::NS(NodeId_to_node_id_str_with_format)( &temp_node_id, 32,
        &node_id_str[ 0 ], ::NS(NODE_ID_STR_FORMAT_ARCHSTR) );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(NodeInfo_set_platform_id( node_info_a,
             ::NS(NodeId_get_platform_id)( &temp_node_id ) ) );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(NodeInfo_set_device_id( node_info_a,
             ::NS(NodeId_get_device_id)( &temp_node_id ) ) );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE( ::NS(NodeId_is_valid)(
        ::NS(NodeInfo_get_ptr_const_node_id)( node_info_a ) ) );

    ASSERT_TRUE( ::NS(NodeId_are_equal)(
        ::NS(NodeInfo_get_ptr_const_node_id)( node_info_a ), &temp_node_id ) );

    ::NS(NodeId_set_platform_id)( &temp_node_id, platform_id_t{ 3 } );
    ::NS(NodeId_set_device_id)( &temp_node_id, device_id_t{ 14 } );

    status = ::NS(NodeInfo_set_platform_id( node_info_a,
             ::NS(NodeId_get_platform_id)( &temp_node_id ) ) );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(NodeInfo_set_device_id( node_info_a,
             ::NS(NodeId_get_device_id)( &temp_node_id ) ) );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(NodeInfo_get_arch_id)( node_info_a ) == arch_id );
    ASSERT_TRUE( ::NS(NodeId_are_equal)(
        ::NS(NodeInfo_get_ptr_const_node_id)( node_info_a ), &temp_node_id ) );

    size_t const node_info_a_str_capacity =
        ::NS(NodeInfo_get_required_out_string_length)( node_info_a );

    ASSERT_TRUE( node_info_a_str_capacity > size_t{ 0 } );

    std::vector< char > node_info_a_cstr( node_info_a_str_capacity, '\0' );

    size_t const too_short = ( node_info_a_str_capacity > size_t{ 2 } )
        ? ( node_info_a_str_capacity >> size_t{ 1 } ) + size_t{ 1 }
        : size_t{ 1 };

    status = ::NS(NodeInfo_to_string)(
        node_info_a, too_short, node_info_a_cstr.data() );
    ASSERT_TRUE( status != ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(NodeInfo_to_string)( node_info_a, node_info_a_cstr.size(),
        node_info_a_cstr.data() );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( std::strlen( node_info_a_cstr.data() ) > size_t{ 0 } );
    ASSERT_TRUE( std::strlen( node_info_a_cstr.data() ) <
                 node_info_a_str_capacity );

    /* --------------------------------------------------------------------- */

    ::NS(NodeInfo_delete)( node_info_a );
}

/* end: tests/sixtracklib/common/control/test_node_info_base_cxx.cpp */
