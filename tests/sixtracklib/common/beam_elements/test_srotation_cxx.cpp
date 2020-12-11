#include "sixtracklib/common/beam_elements/srotation.hpp"

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

template< typename SRotationT >
class CXXCommonBeSRotation : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using LongDblSRotation =
        SIXTRL_CXX_NAMESPACE::TSRotation< long double >;

    using SinglePrecSRotation =
        SIXTRL_CXX_NAMESPACE::TSRotation< float >;

    using CXXSRotationTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::SRotation,
        SIXTRL_CXX_NAMESPACE::CSRotation,
        LongDblSRotation, SinglePrecSRotation >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeSRotation, SIXTRL_CXX_NAMESPACE::tests::CXXSRotationTypes );

TYPED_TEST( CXXCommonBeSRotation, BasicUsage )
{
    namespace st = sixtrack;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::tests::SRotation_tests_assignment< TypeParam >() );
}
