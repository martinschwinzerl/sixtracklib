#include "sixtracklib/common/beam_elements/drift.hpp"
#include <gtest/gtest.h>

#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/objs/objs_traits.hpp"
#include "sixtracklib/common/internal/type_random_traits.hpp"

template< typename DriftT >
class CXXCommonBeDrift : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using LongDblDrift =
        SIXTRL_CXX_NAMESPACE::TDrift< long double >;

    using SinglePrecDrift =
        SIXTRL_CXX_NAMESPACE::TDrift< float >;

    using CXXDriftTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::Drift,
        SIXTRL_CXX_NAMESPACE::CDrift,
        LongDblDrift, SinglePrecDrift >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeDrift, SIXTRL_CXX_NAMESPACE::tests::CXXDriftTypes );

TYPED_TEST( CXXCommonBeDrift, BasicUsage )
{
    namespace st = sixtrack;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::tests::Drift_tests_assignment< TypeParam >() );
}
