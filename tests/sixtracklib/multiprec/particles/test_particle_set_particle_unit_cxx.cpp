#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/particles/particle_set.hpp"
#include "sixtracklib/common/particle.hpp"

#include <gtest/gtest.h>

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/particles.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"

template< typename ParticleSetT >
class CXXMultiprecParticlesParticleSetParticle : public ::testing::Test
{
    public:
};

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

TYPED_TEST_SUITE( CXXMultiprecParticlesParticleSetParticle,
                  SIXTRL_CXX_NAMESPACE::tests::CXXParticleSetTypes );

TYPED_TEST( CXXMultiprecParticlesParticleSetParticle, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::tests::ParticleSet_tests_particle_unit_assignments< TypeParam >(
            st::arch_size_t{ 10 } ) );
}
