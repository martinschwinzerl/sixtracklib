#include "sixtracklib/common/beam_elements/multipole.hpp"

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

template< typename MultipoleT >
class CXXCommonBeMultipole : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using LongDblMultipole =
        SIXTRL_CXX_NAMESPACE::TMultipole< long double, int64_t >;

    using SinglePrecMultipole =
        SIXTRL_CXX_NAMESPACE::TMultipole< float, int64_t >;

    using DoubleInt16Multipole =
        SIXTRL_CXX_NAMESPACE::TMultipole< double, int16_t >;

    using SinglePrecVecMultipole =
        SIXTRL_CXX_NAMESPACE::TVectorMultipole< float, int64_t >;

    using LongDblVecMultipole =
        SIXTRL_CXX_NAMESPACE::TVectorMultipole< long double, int64_t >;

    using DoubleInt16VecMultipole =
        SIXTRL_CXX_NAMESPACE::TVectorMultipole< double, int16_t >;

    using CXXMultipoleTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::Multipole, SIXTRL_CXX_NAMESPACE::CMultipole,
        LongDblMultipole, SinglePrecMultipole, DoubleInt16Multipole,
        SIXTRL_CXX_NAMESPACE::VecMultipole, LongDblVecMultipole,
        SinglePrecVecMultipole, DoubleInt16VecMultipole >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeMultipole,
                  SIXTRL_CXX_NAMESPACE::tests::CXXMultipoleTypes );

TYPED_TEST( CXXCommonBeMultipole, BasicUsage )
{
    namespace st = sixtrack;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::tests::Multipole_tests_assignment< TypeParam >() );
}
