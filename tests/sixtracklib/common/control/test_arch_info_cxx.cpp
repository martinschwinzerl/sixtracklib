#include "sixtracklib/common/control/arch_info.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/architecture/architecture.hpp"
#include "sixtracklib/testlib.h"

TEST( CXX_CommonControlArchInfoTests, MinimalUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using arch_info_t = st::ArchInfo;
    using architectures_t = st::Architectures;
    using arch_id_t       = architectures_t::arch_id_t;
    using size_t          = architectures_t::size_type;

    /* Verify that two architectures are available: */

    st::Architectures const& archs = st::Architectures_get_const();
    SIXTRL_ASSERT( archs.numArchitectures() >= size_t{ 2 } );

    arch_id_t const arch1 = archs.archIdByNumber( size_t{ 0 } );
    arch_id_t const arch2 = archs.archIdByNumber( size_t{ 1 }  );

    SIXTRL_ASSERT( arch1 != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch1 != st::ARCHITECTURE_NONE );
    SIXTRL_ASSERT( arch2 != st::ARCHITECTURE_ILLEGAL );
    SIXTRL_ASSERT( arch2 != st::ARCHITECTURE_NONE );
    SIXTRL_ASSERT( arch1 != arch2 );

    SIXTRL_ASSERT( archs.hasArchitecture( arch1 ) );
    SIXTRL_ASSERT( archs.hasArchStr( arch1 ) );
    SIXTRL_ASSERT( archs.hasArchitecture( arch2 ) );
    SIXTRL_ASSERT( archs.hasArchStr( arch2 ) );

    /* Create st::ArchInfo instance with inital values */

    arch_info_t arch_info_a;

    /* Verify the initial state */

    ASSERT_TRUE( arch_info_a.archId() == st::ARCHITECTURE_ILLEGAL );
    ASSERT_TRUE( !arch_info_a.hasArchStr() );
    ASSERT_TRUE( arch_info_a.ptrArchStr() != nullptr );
    ASSERT_TRUE( std::strlen( arch_info_a.ptrArchStr() ) == std::size_t{ 0 } );

    std::string  arch_info_a_str = arch_info_a.archStr();
    ASSERT_TRUE( arch_info_a_str.empty() );

    /* Reset the arch info to represent a member of the arch1 architecture */

    arch_info_a.reset( arch1 );

    /* Verify that the values are now consistent with this choice */

    ASSERT_TRUE( arch_info_a.archId() == arch1 );

    ASSERT_TRUE( arch_info_a.hasArchStr() );
    ASSERT_TRUE( arch_info_a.ptrArchStr() != nullptr );
    ASSERT_TRUE( 0 == std::strcmp( arch_info_a.ptrArchStr(),
                 archs.ptrArchStr( arch1 ) ) );

    arch_info_a_str = arch_info_a.archStr();
    ASSERT_TRUE( arch_info_a_str.compare( archs.archStr( arch1 ) ) == 0 );

    /* Create a second ArchInfo instance, also from the arch1 architecture */

    arch_info_t arch_info_b( arch1 );

    /* Verify that also arch_info_b is consistent with this choice */

    ASSERT_TRUE( arch_info_b.archId() == arch1 );
    ASSERT_TRUE( arch_info_b.hasArchStr() );
    ASSERT_TRUE( arch_info_b.ptrArchStr() != nullptr );
    ASSERT_TRUE( 0 == std::strcmp(
        arch_info_a.ptrArchStr(), arch_info_b.ptrArchStr() ) );

    /* verify that arch_info_a and arch_info_b compare as identical
     * to each other */

    ASSERT_TRUE( arch_info_a.isArchIdenticalTo( arch_info_b ) );
    ASSERT_TRUE( arch_info_a.isArchIdenticalTo( arch_info_b.archId() ) );

    ASSERT_TRUE( arch_info_a.isArchCompatibleWith( arch_info_b ) );
    ASSERT_TRUE( arch_info_a.isArchCompatibleWith( arch_info_b.archId() ) );

    /* reset arch_info_a to represent now an arch2 architecture */

    arch_info_a.reset( st::ARCHITECTURE_OPENCL );

    ASSERT_TRUE( arch_info_a.archId() == st::ARCHITECTURE_OPENCL );
    ASSERT_TRUE( arch_info_a.hasArchStr() );
    ASSERT_TRUE( arch_info_a.ptrArchStr() != nullptr );
    ASSERT_TRUE( 0 == std::strcmp( arch_info_a.ptrArchStr(),
        archs.ptrArchStr( arch2 ) ) );

    /* arch_info_a and arch_info_b should no longer be considered equal /
     * compatible with each other */

    ASSERT_TRUE( !arch_info_a.isArchIdenticalTo( arch_info_b ) );
    ASSERT_TRUE( !arch_info_a.isArchIdenticalTo( arch_info_b.archId() ) );

    ASSERT_TRUE( !arch_info_a.isArchCompatibleWith(arch_info_b ) );
    ASSERT_TRUE( !arch_info_a.isArchCompatibleWith(arch_info_b.archId() ) );
}

/* end: tests/sixtracklib/common/control/test_arch_info_c99.cpp */
