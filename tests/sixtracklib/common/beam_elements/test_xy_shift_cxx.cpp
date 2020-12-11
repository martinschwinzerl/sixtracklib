#include "sixtracklib/common/beam_elements/xy_shift.hpp"

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

template< typename XYShiftT >
class CXXCommonBeXYShift : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using LongDblXYShift =
        SIXTRL_CXX_NAMESPACE::TXYShift< long double >;

    using SinglePrecXYShift =
        SIXTRL_CXX_NAMESPACE::TXYShift< float >;

    using CxxXYShiftTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::XYShift,
        SIXTRL_CXX_NAMESPACE::CXYShift,
        LongDblXYShift, SinglePrecXYShift >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeXYShift,
                  SIXTRL_CXX_NAMESPACE::tests::CxxXYShiftTypes );

TYPED_TEST( CXXCommonBeXYShift, BasicUsage )
{
    namespace st = sixtrack;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::tests::XYShift_tests_assignment< TypeParam >() );
}
