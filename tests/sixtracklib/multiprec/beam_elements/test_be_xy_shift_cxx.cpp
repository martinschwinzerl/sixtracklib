#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/beam_elements/xy_shift.hpp"

#include <gtest/gtest.h>

#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/objs.hpp"

template< typename XYShiftT >
class CXXMultiprecBeXYShift : public ::testing::Test { public: };

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXXYShiftTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::DoublePrecXYShift,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecXYShift,
        SIXTRL_CXX_NAMESPACE::QuadPrecXYShift,
        SIXTRL_CXX_NAMESPACE::OctPrecXYShift,
        SIXTRL_CXX_NAMESPACE::SinglePrecXYShift >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecBeXYShift,
                  SIXTRL_CXX_NAMESPACE::tests::CXXXYShiftTypes );

TYPED_TEST( CXXMultiprecBeXYShift, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::tests::XYShift_tests_assignment< TypeParam >() );
}
