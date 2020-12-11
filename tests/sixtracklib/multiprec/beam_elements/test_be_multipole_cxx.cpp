#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/beam_elements/multipole.hpp"

#include <gtest/gtest.h>

#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/objs.hpp"

template< typename MultipoleT >
class CXXMultiprecBeMultipole : public ::testing::Test { public: };

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXMultipoleTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::DoublePrecMultipole,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecMultipole,
        SIXTRL_CXX_NAMESPACE::QuadPrecMultipole,
        SIXTRL_CXX_NAMESPACE::OctPrecMultipole,
        SIXTRL_CXX_NAMESPACE::SinglePrecMultipole >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecBeMultipole,
                  SIXTRL_CXX_NAMESPACE::tests::CXXMultipoleTypes );

TYPED_TEST( CXXMultiprecBeMultipole, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::tests::Multipole_tests_assignment< TypeParam >() );
}
