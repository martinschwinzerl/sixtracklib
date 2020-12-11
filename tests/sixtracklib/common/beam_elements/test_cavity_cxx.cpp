#include "sixtracklib/common/beam_elements/cavity.hpp"

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/objs/objs_traits.hpp"
#include "sixtracklib/common/internal/math_factorial.h"
#include "sixtracklib/common/internal/type_random_traits.hpp"

template< typename CavityT >
class CXXCommonBeCavity : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using LongDblCavity =
        SIXTRL_CXX_NAMESPACE::TCavity< long double >;

    using SinglePrecCavity =
        SIXTRL_CXX_NAMESPACE::TCavity< float >;

    using CXXCavityTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::Cavity,
        SIXTRL_CXX_NAMESPACE::CCavity,
        LongDblCavity, SinglePrecCavity >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeCavity, SIXTRL_CXX_NAMESPACE::tests::CXXCavityTypes );

TYPED_TEST( CXXCommonBeCavity, BasicUsage )
{
    namespace st = sixtrack;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::tests::Cavity_tests_assignment< TypeParam >() );
}
