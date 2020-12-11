#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/beam_elements/cavity.hpp"

#include <gtest/gtest.h>

#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/objs.hpp"

template< typename CavityT >
class CXXMultiprecBeCavity : public ::testing::Test { public: };

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXCavityTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::DoublePrecCavity,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecCavity,
        SIXTRL_CXX_NAMESPACE::QuadPrecCavity,
        SIXTRL_CXX_NAMESPACE::OctPrecCavity,
        SIXTRL_CXX_NAMESPACE::SinglePrecCavity >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecBeCavity,
                  SIXTRL_CXX_NAMESPACE::tests::CXXCavityTypes );

TYPED_TEST( CXXMultiprecBeCavity, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::tests::Cavity_tests_assignment< TypeParam >() );
}
