#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/beam_elements/srotation.hpp"

#include <gtest/gtest.h>

#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/objs.hpp"

template< typename SRotationT >
class CXXMultiprecBeSRotation : public ::testing::Test { public: };

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXSRotationTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::DoublePrecSRotation,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecSRotation,
        SIXTRL_CXX_NAMESPACE::QuadPrecSRotation,
        SIXTRL_CXX_NAMESPACE::OctPrecSRotation,
        SIXTRL_CXX_NAMESPACE::SinglePrecSRotation >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecBeSRotation,
                  SIXTRL_CXX_NAMESPACE::tests::CXXSRotationTypes );

TYPED_TEST( CXXMultiprecBeSRotation, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::tests::SRotation_tests_assignment< TypeParam >() );
}
