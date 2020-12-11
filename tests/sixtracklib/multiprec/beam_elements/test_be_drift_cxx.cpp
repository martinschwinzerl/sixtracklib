#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/beam_elements/drift.hpp"

#include <gtest/gtest.h>

#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/objs.hpp"

template< typename DriftT >
class CXXMultiprecBeDrift : public ::testing::Test { public: };

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXDriftTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::DoublePrecDrift,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecDrift,
        SIXTRL_CXX_NAMESPACE::QuadPrecDrift,
        SIXTRL_CXX_NAMESPACE::OctPrecDrift,
        SIXTRL_CXX_NAMESPACE::SinglePrecDrift >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecBeDrift,
                  SIXTRL_CXX_NAMESPACE::tests::CXXDriftTypes );

TYPED_TEST( CXXMultiprecBeDrift, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::tests::Drift_tests_assignment< TypeParam >() );
}
