#include "sixtracklib/common/control/kernel_set.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/architecture.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/kernel_config_base.h"
#include "sixtracklib/common/control/kernel_config_store.h"
#include "sixtracklib/testlib.h"

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        template< typename... Args >
        ::NS(KernelConfigBase)* KernelConfigBase_new( Args&&... args )
        {
            return new SIXTRL_CXX_NAMESPACE::KernelConfigBase(
                std::forward< Args >( args )... );
        }
    }
}

TEST( C99_CommonControlKernelSetBaseTests, AddKernelSetToStoreSwitchRemove )
{
    namespace st_test = SIXTRL_CXX_NAMESPACE::tests;


    using store_t         = ::NS(KernelConfigStore);
    using kernel_set_t    = ::NS(KernelSetBase);
    using config_base_t   = ::NS(KernelConfigBase);
    using key_t           = ::NS(KernelConfigKey);
    using size_t          = ::NS(arch_size_t);
    using kernel_id_t     = ::NS(ctrl_kernel_id_t);
    using arch_id_t       = ::NS(arch_id_t);
    using status_t        = ::NS(arch_status_t);
    using kernel_set_id_t = ::NS(ctrl_kernel_id_t);
    using purpose_t       = ::NS(kernel_purpose_t);

    /* Verify that a suitable arch is available */
    ::NS(Architectures) const* ptr_archs = ::NS(Architectures_get_ptr_const)();
    SIXTRL_ASSERT( ptr_archs != nullptr );
    SIXTRL_ASSERT( ::NS(Architectures_get_num_architectures)( ptr_archs ) >
        size_t{ 0 } );

    arch_id_t const arch_id = ::NS(Architectures_get_arch_id_by_number)(
        ptr_archs, size_t{ 0 } );
    SIXTRL_ASSERT( arch_id != ::NS(ARCHITECTURE_ILLEGAL) );
    SIXTRL_ASSERT( arch_id != ::NS(ARCHITECTURE_NONE) );
    SIXTRL_ASSERT( ::NS(Architectures_has_architecture)( ptr_archs, arch_id ) );
    SIXTRL_ASSERT( ::NS(Architectures_has_arch_str)( ptr_archs, arch_id ) );

    /* --------------------------------------------------------------------- */
    /* Create an empty store: */

    store_t* store = ::NS(KernelConfigStore_create)();
    SIXTRL_ASSERT( store != nullptr );

    /* --------------------------------------------------------------------- */
    /* Setup the store for the kernel sets */
    /* Add four kernels for the release variant */

    key_t* release_key = ::NS(KernelConfigKey_new)(
        arch_id, ::NS(KERNEL_CONFIG_PURPOSE_UNSPECIFIED),
            ::NS(ARCH_VARIANT_NONE), nullptr );

    ASSERT_TRUE( release_key != nullptr );

    ::NS(KernelConfigKey_set_purpose)( release_key,
        ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER) );

    config_base_t* ptr_kernel = st_test::KernelConfigBase_new(
        *release_key, size_t{ 1 }, "remap_release_kernel" );

    kernel_id_t const release_remap_id_0 =
        ::NS(KernelConfigStore_add_kernel_config)(
            store, release_key, ptr_kernel );

    SIXTRL_ASSERT( release_remap_id_0 != ::NS(ARCH_ILLEGAL_KERNEL_ID) );
    SIXTRL_ASSERT( ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
        store, release_remap_id_0 ) == ptr_kernel );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    ::NS(KernelConfigKey_set_purpose)( release_key,
        ::NS(KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN) );

    ptr_kernel = st_test::KernelConfigBase_new(
        *release_key, 1, "track_release_kernel" );

    SIXTRL_ASSERT( ptr_kernel != nullptr );
    kernel_id_t const track_release_id_0 =
        ::NS(KernelConfigStore_add_kernel_config)(
            store, release_key, ptr_kernel );

    SIXTRL_ASSERT( track_release_id_0 != ::NS(ARCH_ILLEGAL_KERNEL_ID) );
    SIXTRL_ASSERT( ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
        store, track_release_id_0 ) == ptr_kernel );
    ptr_kernel = nullptr;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    ::NS(KernelConfigKey_set_purpose)( release_key,
        ::NS(KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES));

    ptr_kernel = st_test::KernelConfigBase_new(
        *release_key, 1, "fetch_addr_release_kernel" );

    SIXTRL_ASSERT( ptr_kernel != nullptr );
    kernel_id_t const fetch_addr_release_id_0 =
        ::NS(KernelConfigStore_add_kernel_config)(
            store, release_key, ptr_kernel );

    SIXTRL_ASSERT( ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
        store, fetch_addr_release_id_0 ) == ptr_kernel );

    SIXTRL_ASSERT( fetch_addr_release_id_0 != ::NS(ARCH_ILLEGAL_KERNEL_ID) );
    SIXTRL_ASSERT( ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
        store, fetch_addr_release_id_0 ) == ptr_kernel );
    ptr_kernel = nullptr;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    ::NS(KernelConfigKey_set_purpose)( release_key,
            ::NS(KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID));

    ptr_kernel = st_test::KernelConfigBase_new(
        *release_key, 1, "userdefined_release_kernel" );
    SIXTRL_ASSERT( ptr_kernel != nullptr );

    kernel_id_t const usrdefined_release_id_0 =
        ::NS(KernelConfigStore_add_kernel_config)(
            store, release_key, ptr_kernel );

    SIXTRL_ASSERT( usrdefined_release_id_0 != ::NS(ARCH_ILLEGAL_KERNEL_ID) );
    SIXTRL_ASSERT( ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
        store, usrdefined_release_id_0 ) == ptr_kernel );

    ptr_kernel = nullptr;

    /* Add one kernel for the debug variant configuration */

    key_t* debug_key = ::NS(KernelConfigKey_new_from_copy)( release_key );
    ASSERT_TRUE( debug_key != nullptr );

    ::NS(KernelConfigKey_set_variant)( debug_key, ::NS(ARCH_VARIANT_DEBUG) );

    ::NS(KernelConfigKey_set_purpose)( debug_key,
            ::NS(KERNEL_CONFIG_PURPOSE_REMAP_BUFFER));

    ptr_kernel = st_test::KernelConfigBase_new(
        *debug_key, 2, "remap_debug_kernel" );

    SIXTRL_ASSERT( ptr_kernel != nullptr );
    kernel_id_t const remap_debug_id_0 =
        ::NS(KernelConfigStore_add_kernel_config)(
            store, debug_key, ptr_kernel );
    SIXTRL_ASSERT( remap_debug_id_0 != ::NS(ARCH_ILLEGAL_KERNEL_ID) );
    ptr_kernel = nullptr;

    /* Add an alias for the debug kernel to refer to the same kernel config */

    ::NS(KernelConfigKey_set_purpose)( debug_key,
        ::NS(KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN) );
    status_t status = ::NS(KernelConfigStore_add_kernel_config_to_key_mapping)(
        store, debug_key, track_release_id_0 );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    /* Add default parameters for the debug  variant of the fetch addr kernel */

    ::NS(KernelConfigKey_set_purpose)( debug_key,
        ::NS(KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES) );
    status = ::NS(KernelConfigStore_set_default_init_kernel_config_parameters)(
        store, debug_key, size_t{ 6 }, "fetch_addr_debug_id" );
    SIXTRL_ASSERT( status == ::NS(ARCH_STATUS_SUCCESS) );

    /* --------------------------------------------------------------------- */
    /* Add kernel_set for argument_set #0: */

    kernel_set_t* set0 = ::NS(KernelSetBase_new)( arch_id, store );
    ASSERT_TRUE( set0 != nullptr );

    kernel_set_id_t const set0_id =
        ::NS(KernelConfigStore_add_kernel_set)( store, set0 );

    ASSERT_TRUE( set0_id != ::NS(ARCH_ILLEGAL_KERNEL_SET_ID) );
    ASSERT_TRUE( ::NS(KernelConfigStore_has_kernel_set)( store, set0_id ) );
    ASSERT_TRUE( ::NS(KernelConfigStore_get_num_kernel_sets)( store ) ==
                 size_t{ 1 } );

    ASSERT_TRUE( ::NS(KernelConfigStore_get_ptr_const_kernel_set)(
        store, set0_id ) == set0 );

    ASSERT_TRUE( ::NS(KernelSet_get_num_of_purposes)( set0 ) == size_t{ 0 } );
    ASSERT_TRUE( ::NS(KernelSet_get_num_of_pinned_purposes)( set0 ) ==
        size_t{ 0 } );

    purpose_t const purpose_remap = ::NS(KernelConfig_get_purpose)(
        ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
            store, release_remap_id_0 ) );

    status = ::NS(KernelSet_add_purpose)( set0, purpose_remap );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(KernelSet_get_num_of_purposes)( set0 ) == size_t{ 1 } );
    ASSERT_TRUE( ::NS(KernelSet_get_num_of_pinned_purposes)( set0 ) ==
        size_t{ 0 } );
    ASSERT_TRUE( ::NS(KernelSet_requires)( set0, purpose_remap ) );

    purpose_t const purpose_track = ::NS(KernelConfig_get_purpose)(
        ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
            store, track_release_id_0 ) );
    status = ::NS(KernelSet_add_purpose)( set0, purpose_track );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(KernelSet_get_num_of_purposes)( set0 ) == size_t{ 2 } );
    ASSERT_TRUE( ::NS(KernelSet_get_num_of_pinned_purposes)( set0 ) ==
        size_t{ 0 } );
    ASSERT_TRUE( ::NS(KernelSet_requires)( set0, purpose_track ) );

    purpose_t const purpose_fetch_addr = ::NS(KernelConfig_get_purpose)(
        ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
            store, fetch_addr_release_id_0 ) );
    status = ::NS(KernelSet_add_purpose)( set0, purpose_fetch_addr );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(KernelSet_get_num_of_purposes)( set0 ) == size_t{ 3 } );
    ASSERT_TRUE( ::NS(KernelSet_get_num_of_pinned_purposes)( set0 ) ==
        size_t{ 0 } );
    ASSERT_TRUE( ::NS(KernelSet_requires)( set0, purpose_fetch_addr ) );

    purpose_t const purpose_usrdefined = ::NS(KernelConfig_get_purpose)(
        ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
            store, usrdefined_release_id_0 ) );
    status = ::NS(KernelSet_add_purpose)( set0, purpose_usrdefined );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(KernelSet_get_num_of_purposes)( set0 ) == size_t{ 4 } );
    ASSERT_TRUE( ::NS(KernelSet_get_num_of_pinned_purposes)( set0 ) ==
        size_t{ 0 } );
    ASSERT_TRUE( ::NS(KernelSet_requires)( set0, purpose_usrdefined ) );

    status = ::NS(KernelSet_sync_with_store_and_assign_key)(
        set0, release_key, true );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    std::vector< purpose_t > purposes = {
        purpose_remap, purpose_track, purpose_fetch_addr, purpose_usrdefined };

    std::vector< kernel_id_t > release_kernel_ids;

    for( purpose_t const purpose : purposes )
    {
        ASSERT_TRUE( ::NS(KernelSet_requires)( set0, purpose ) );
        ASSERT_TRUE( ::NS(KernelSet_is_available)( set0, purpose ) );

        kernel_id_t const kernel_id =
            ::NS(KernelSet_get_kernel_config_id)( set0, purpose);

        ASSERT_TRUE( kernel_id != ::NS(ARCH_ILLEGAL_KERNEL_ID) );
        release_kernel_ids.push_back( kernel_id );

        ASSERT_TRUE( ::NS(KernelSet_get_ptr_const_kernel_config_base)(
            set0, purpose ) != nullptr );

        ASSERT_TRUE( ::NS(KernelSet_get_ptr_const_kernel_config_base)( set0,
            purpose ) ==
            ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
                store, kernel_id ) );

        if( purpose != purpose_track )
        {
            ASSERT_TRUE( ::NS(KernelConfig_is_attached_to_set)(
                ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
                    store, kernel_id ), set0_id ) );
        }

        ::NS(KernelConfigKey_set_purpose)( release_key,  purpose  );
        ASSERT_TRUE( ::NS(KernelConfigKey_are_equal)(
            ::NS(KernelSet_get_ptr_const_kernel_config_key)(
                set0, purpose ), release_key ) );

        ASSERT_TRUE( ::NS(KernelSet_is_ready)( set0, purpose ) );
    }

    ASSERT_TRUE(  ::NS(KernelConfigKey_is_variant_release_mode)(
        ::NS(KernelSet_get_ptr_const_current_config_key)( set0 ) ) );

    ASSERT_TRUE( !::NS(KernelConfigKey_is_variant_debug_mode)(
        ::NS(KernelSet_get_ptr_const_current_config_key)( set0 ) ) );

    /* --------------------------------------------------------------------- */

    ASSERT_TRUE( !::NS(KernelSet_can_switch_all_kernels)( set0, debug_key ) );
    ::NS(KernelConfigKey_set_purpose)( debug_key,  purpose_remap  );

    ASSERT_TRUE(  ::NS(KernelSet_can_switch_kernel)( set0, debug_key ) );

    ::NS(KernelConfigKey_set_purpose)( debug_key,  purpose_track  );
    ASSERT_TRUE(  ::NS(KernelSet_can_switch_kernel)( set0, debug_key ) );

    ::NS(KernelConfigKey_set_purpose)( debug_key,  purpose_fetch_addr  );
    ASSERT_TRUE( ::NS(KernelSet_can_switch_kernel)( set0, debug_key ) );

    ::NS(KernelConfigKey_set_purpose)( debug_key,  purpose_usrdefined  );
    ASSERT_TRUE( !::NS(KernelSet_can_switch_kernel)( set0, debug_key ) );

    SIXTRL_ASSERT( ptr_kernel == nullptr );
    ptr_kernel = st_test::KernelConfigBase_new(
        *debug_key, size_t{ 2 }, "userdefined_debug_kernel" );

    kernel_id_t const usrdefined_debug_id_0 =
        ::NS(KernelConfigStore_add_kernel_config)(
            store, debug_key, ptr_kernel );

    SIXTRL_ASSERT( usrdefined_debug_id_0 != ::NS(ARCH_ILLEGAL_KERNEL_ID) );
    SIXTRL_ASSERT( ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
        store, usrdefined_debug_id_0 ) == ptr_kernel );
    ptr_kernel = nullptr;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    ASSERT_TRUE( ::NS(KernelSet_can_switch_kernel)( set0, debug_key ) );

    ::NS(KernelConfigKey_set_purpose)( debug_key,
        ::NS(KERNEL_CONFIG_PURPOSE_UNSPECIFIED) );

    status = ::NS(KernelSet_switch_kernels)( set0, debug_key );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    status = ::NS(KernelSet_update_kernel_op_flags)( set0 );
    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );

    kernel_set_t::op_flags_t const op_flags =
        ::NS(KernelSet_get_kernel_op_flags)( set0 );

    SIXTRL_ASSERT( ( op_flags & ::NS(KERNEL_OP_HAS_ALL_REQUIRED_PURPOSES) ) ==
        ::NS(KERNEL_OP_HAS_ALL_REQUIRED_PURPOSES) );

    SIXTRL_ASSERT( ( op_flags & ::NS(KERNEL_OP_ALL_REQUIRED_KERNELS_AVAILABLE) )
        == ::NS(KERNEL_OP_ALL_REQUIRED_KERNELS_AVAILABLE) );

    SIXTRL_ASSERT( ( op_flags & ::NS(KERNEL_OP_ALL_REQUIRED_KERNELS_READY) )
        == ::NS(KERNEL_OP_ALL_REQUIRED_KERNELS_READY) );

    for( kernel_id_t const kernel_id : release_kernel_ids )
    {
        config_base_t const* ptr_config =
            ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
                store, kernel_id );
        ASSERT_TRUE(  ptr_config != nullptr );

        if( ::NS(KernelConfig_get_purpose)( ptr_config ) != purpose_track )
        {
            ASSERT_TRUE( !::NS(KernelConfig_is_attached_to_set)(
                ptr_config, set0_id ) );

            ASSERT_TRUE( !::NS(KernelConfig_is_attached_to_any_sets)(
                ptr_config ) );
        }
    }

    ASSERT_TRUE( !::NS(KernelConfigKey_is_variant_release_mode)(
        ::NS(KernelSet_get_ptr_const_current_config_key)( set0 ) ) );

    ASSERT_TRUE(  ::NS(KernelConfigKey_is_variant_debug_mode)(
        ::NS(KernelSet_get_ptr_const_current_config_key)( set0 ) ) );

    ::NS(KernelConfigKey_set_purpose)( debug_key,
        ::NS(KERNEL_CONFIG_PURPOSE_UNSPECIFIED));

    ASSERT_TRUE( ::NS(KernelConfigKey_are_equal_except_purpose)(
        ::NS(KernelSet_get_ptr_const_current_config_key)( set0 ),
            debug_key ) );

    ASSERT_TRUE( !::NS(KernelConfigKey_are_equal_except_purpose)(
        ::NS(KernelSet_get_ptr_const_current_config_key)( set0 ),
            release_key ) );

    std::vector< kernel_id_t > debug_kernel_ids;

    for( purpose_t const purpose : purposes )
    {
        ::NS(KernelConfigKey_set_purpose)( debug_key,  purpose  );
        ::NS(KernelConfigKey_set_purpose)( release_key,  purpose  );

        kernel_id_t const kernel_id =
            ::NS(KernelConfigStore_get_kernel_id_by_key)( store, debug_key );

        ASSERT_TRUE( kernel_id != ::NS(ARCH_ILLEGAL_KERNEL_ID) );

        ASSERT_TRUE( ::NS(KernelSet_is_available)( set0, purpose ) );
        ASSERT_TRUE( ::NS(KernelSet_get_kernel_config_id)(
            set0, purpose) == kernel_id );

        ASSERT_TRUE( ::NS(KernelConfigKey_get_arch_id)(
            ::NS(KernelSet_get_ptr_const_kernel_config_key)( set0, purpose ) )
            == ::NS(KernelConfigKey_get_arch_id)( debug_key ) );

        ASSERT_TRUE( ::NS(KernelConfigKey_get_purpose)(
            ::NS(KernelSet_get_ptr_const_kernel_config_key)( set0, purpose ) )
            == purpose );

        if( purpose != purpose_track )
        {
            /* Because the track kernel is an alias to the release kernel */
            ASSERT_TRUE( ::NS(KernelConfigKey_get_variant)(
                ::NS(KernelSet_get_ptr_const_kernel_config_key)(
                    set0, purpose ) ) == ::NS(KernelConfigKey_get_variant)(
                        debug_key ) );

            ASSERT_TRUE( ::NS(KernelConfigKey_are_equal)(
                ::NS(KernelSet_get_ptr_const_kernel_config_key)(
                    set0, purpose ), debug_key ) );

            ASSERT_TRUE( ::NS(KernelConfigKey_are_not_equal)(
                ::NS(KernelSet_get_ptr_const_kernel_config_key)(
                    set0, purpose ), release_key ) );

            debug_kernel_ids.push_back( kernel_id );
        }
        else
        {
            /* Because the track kernel is an alias to the release kernel */
            ASSERT_TRUE( ::NS(KernelConfigKey_get_variant)(
                ::NS(KernelSet_get_ptr_const_kernel_config_key)(
                    set0, purpose ) ) == ::NS(KernelConfigKey_get_variant)(
                        release_key ) );

            ASSERT_TRUE( ::NS(KernelConfigKey_are_not_equal)(
                ::NS(KernelSet_get_ptr_const_kernel_config_key)( set0,
                    purpose ), debug_key ) );

            ASSERT_TRUE( ::NS(KernelConfigKey_are_equal)(
                ::NS(KernelSet_get_ptr_const_kernel_config_key)( set0,
                    purpose ), release_key ) );
        }

        ASSERT_TRUE( ::NS(KernelSet_get_ptr_const_kernel_config_base)(
                        set0, purpose ) ==
                    ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
                        store, kernel_id ) );

        ASSERT_TRUE( ::NS(KernelConfig_is_attached_to_set)(
            ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
                store, kernel_id ), set0_id ) );

        ASSERT_TRUE(
            ::NS(KernelSet_is_purpose_associated_with_kernel_config_id)( set0,
                kernel_id, purpose ) );

        ASSERT_TRUE( ::NS(KernelSet_is_ready)( set0, purpose ) );
    }

    /* remove set0 from store */

    set0 = nullptr;
    status = ::NS(KernelConfigStore_remove_kernel_set)( store, set0_id );

    ASSERT_TRUE( status == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( !::NS(KernelConfigStore_has_kernel_set)( store, set0_id ) );
    ASSERT_TRUE(  ::NS(KernelConfigStore_get_num_kernel_sets)( store )
                    == size_t{ 0 } );

    for( kernel_id_t const kernel_id : debug_kernel_ids )
    {
        config_base_t const* ptr_config =
            ::NS(KernelConfigStore_get_ptr_const_kernel_config_base)(
                store, kernel_id );

        ASSERT_TRUE( ptr_config != nullptr );
        size_t const nn = ::NS(KernelConfig_get_num_attached_sets)(
            ptr_config );

        ASSERT_TRUE( nn == size_t{ 0 } );
        ASSERT_TRUE( !::NS(KernelConfig_is_attached_to_set)(
            ptr_config, set0_id ) );

        ASSERT_TRUE( !::NS(KernelConfig_is_attached_to_any_sets)(
            ptr_config ) );
    }

    /* --------------------------------------------------------------------- */

    ::NS(KernelConfigKey_delete)( debug_key );
    ::NS(KernelConfigKey_delete)( release_key );
    ::NS(KernelConfigStore_delete)( store );
}

/* end: tests/sixtracklib/common/control/test_kernel_set_base_c99.cpp */
