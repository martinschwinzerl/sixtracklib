#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/particles/particle_set.hpp"

#include <gtest/gtest.h>

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/particles.hpp"

template< typename ParticleSetT >
class CXXMultiprecParticlesParticleSet : public ::testing::Test { public: };

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXParticleSetTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::DoublePrecParticleSet,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecParticleSet,
        SIXTRL_CXX_NAMESPACE::QuadPrecParticleSet,
        SIXTRL_CXX_NAMESPACE::OctPrecParticleSet,
        SIXTRL_CXX_NAMESPACE::SinglePrecParticleSet >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecParticlesParticleSet,
                  SIXTRL_CXX_NAMESPACE::tests::CXXParticleSetTypes );

TYPED_TEST( CXXMultiprecParticlesParticleSet, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::arch_status_t status = st::tests::ParticleSet_tests_assignment<
        TypeParam >( st::arch_size_t{ 20 } );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
}
