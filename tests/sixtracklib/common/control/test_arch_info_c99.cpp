#include "sixtracklib/common/control/arch_info.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"
#include "sixtracklib/common/architecture/architecture.h"
#include "sixtracklib/testlib.h"

TEST( C99_CommonControlArchInfoTests, MinimalUsage )
{
    using arch_info_t = ::NS(ArchInfo);
    using arch_id_t   = ::NS(arch_id_t);

    /* Verify that two architectures are available: */
    ::NS(Architectures) const* ptr_archs = ::NS(Architectures_get_const_ptr)();
    SIXTRL_ASSERT( ptr_archs != nullptr );


    SIXTRL_ASSERT( ::NS(Architectures_get_num_architectures)(
        ptr_archs ) >= size_t{ 2 } );

    arch_id_t const arch1 =
        ::NS(Architectures_get_arch_id_by_number)( ptr_archs, size_t{ 0 }  );

    arch_id_t const arch2 =
        ::NS(Architectures_get_arch_id_by_number)( ptr_archs, size_t{ 1 }  );

    SIXTRL_ASSERT( arch1 != ::NS(ARCHITECTURE_ILLEGAL) );
    SIXTRL_ASSERT( arch1 != ::NS(ARCHITECTURE_NONE) );
    SIXTRL_ASSERT( arch2 != ::NS(ARCHITECTURE_ILLEGAL) );
    SIXTRL_ASSERT( arch2 != ::NS(ARCHITECTURE_NONE) );
    SIXTRL_ASSERT( arch1 != arch2 );

    SIXTRL_ASSERT( ::NS(Architectures_has_architecture)( ptr_archs, arch1 ) );
    SIXTRL_ASSERT( ::NS(Architectures_has_arch_str)( ptr_archs, arch1 ) );
    SIXTRL_ASSERT( ::NS(Architectures_has_architecture)( ptr_archs, arch2 ) );
    SIXTRL_ASSERT( ::NS(Architectures_has_arch_str)( ptr_archs, arch2 ) );

    /* Create NS(ArchInfo) instance with inital values */

    arch_info_t* arch_info_a = ::NS(ArchInfo_create)();
    ASSERT_TRUE( arch_info_a != nullptr );

    /* Verify the initial state */

    ASSERT_TRUE( ::NS(ArchInfo_get_arch_id)( arch_info_a ) ==
                 ::NS(ARCHITECTURE_ILLEGAL) );

    ASSERT_TRUE( !::NS(ArchInfo_has_arch_string)( arch_info_a ) );
    ASSERT_TRUE(  ::NS(ArchInfo_get_arch_string)( arch_info_a ) != nullptr );
    ASSERT_TRUE(  std::strlen( ::NS(ArchInfo_get_arch_string)(
                    arch_info_a ) ) == std::size_t{ 0 } );

    /* Reset the arch info to represent a member of the arch1 architecture */

    NS(ArchInfo_reset)( arch_info_a, arch1 );

    /* Verify that the values are now consistent with this choice */

    ASSERT_TRUE( ::NS(ArchInfo_get_arch_id)( arch_info_a ) == arch1 );

    ASSERT_TRUE( ::NS(ArchInfo_has_arch_string)( arch_info_a ) );
    ASSERT_TRUE( ::NS(ArchInfo_get_arch_string)( arch_info_a ) != nullptr );
    ASSERT_TRUE( 0 == std::strcmp(
        ::NS(ArchInfo_get_arch_string)( arch_info_a ),
        ::NS(Architectures_get_arch_str)( ptr_archs, arch1 ) ) );

    /* Create a second ArchInfo instance, also from the arch1 architecture */

    arch_info_t* arch_info_b = ::NS(ArchInfo_new)( arch1 );
    ASSERT_TRUE( arch_info_b != nullptr );

    /* Verify that also arch_info_b is consistent with this choice */

    ASSERT_TRUE( ::NS(ArchInfo_get_arch_id)( arch_info_b ) == arch1 );
    ASSERT_TRUE( ::NS(ArchInfo_has_arch_string)( arch_info_b ) );
    ASSERT_TRUE( ::NS(ArchInfo_get_arch_string)( arch_info_b ) != nullptr );
    ASSERT_TRUE( 0 == std::strcmp(
        ::NS(ArchInfo_get_arch_string)( arch_info_a ),
        ::NS(ArchInfo_get_arch_string)( arch_info_b ) ) );

    /* verify that arch_info_a and arch_info_b compare as identical
     * to each other */

    ASSERT_TRUE( ::NS(ArchInfo_is_identical_to)( arch_info_a, arch_info_b ) );
    ASSERT_TRUE( ::NS(ArchInfo_is_identical_to_arch_id)( arch_info_a,
                 ::NS(ArchInfo_get_arch_id)( arch_info_b ) ) );

    ASSERT_TRUE( ::NS(ArchInfo_is_compatible_with)(
        arch_info_a, arch_info_b ) );

    ASSERT_TRUE( ::NS(ArchInfo_is_compatible_with_arch_id)( arch_info_a,
                 ::NS(ArchInfo_get_arch_id)( arch_info_b ) ) );

    /* reset arch_info_a to represent now an arch2 architecture */
    ::NS(ArchInfo_reset)( arch_info_a, arch2 );

    ASSERT_TRUE( ::NS(ArchInfo_get_arch_id)( arch_info_a ) == arch2 );

    ASSERT_TRUE( ::NS(ArchInfo_has_arch_string)( arch_info_a ) );
    ASSERT_TRUE( ::NS(ArchInfo_get_arch_string)( arch_info_a ) != nullptr );
    ASSERT_TRUE( 0 == std::strcmp( ::NS(Architectures_get_arch_str)(
                ::NS(Architectures_get_const_ptr)(),
                ::NS(ArchInfo_get_arch_id)( arch_info_a ) ),
            ::NS(ArchInfo_get_arch_string)( arch_info_a ) ) );

    /* arch_info_a and arch_info_b should no longer be considered equal /
     * compatible with each other */

    ASSERT_TRUE( !::NS(ArchInfo_is_identical_to)( arch_info_a, arch_info_b ) );
    ASSERT_TRUE( !::NS(ArchInfo_is_identical_to_arch_id)( arch_info_a,
                  ::NS(ArchInfo_get_arch_id)( arch_info_b ) ) );

    ASSERT_TRUE( !::NS(ArchInfo_is_compatible_with)(
        arch_info_a, arch_info_b ) );

    ASSERT_TRUE( !::NS(ArchInfo_is_compatible_with_arch_id)( arch_info_a,
                  ::NS(ArchInfo_get_arch_id)( arch_info_b ) ) );

    /* Clean-up */

    ::NS(ArchInfo_delete)( arch_info_a );
    arch_info_a = nullptr;

    ::NS(ArchInfo_delete)( arch_info_b );
    arch_info_b = nullptr;
}

/* end: tests/sixtracklib/common/control/test_arch_info_c99.cpp */
