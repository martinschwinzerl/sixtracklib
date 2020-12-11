#include "sixtracklib/common/particle.hpp"

#include <gtest/gtest.h>

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/particles.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"

template< typename ParticleT >
class CXXCommonParticlesParticleTests : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using LongDblParticle =
        SIXTRL_CXX_NAMESPACE::TParticle< long double, int64_t >;

    using SinglePrecParticle =
        SIXTRL_CXX_NAMESPACE::TParticle< float, int64_t >;

    using CXXParticleTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::Particle,
        SIXTRL_CXX_NAMESPACE::CParticle,
        LongDblParticle,
        SinglePrecParticle >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonParticlesParticleTests,
                  SIXTRL_CXX_NAMESPACE::tests::CXXParticleTypes );

TYPED_TEST( CXXCommonParticlesParticleTests, BasicApi )
{
    namespace st = sixtrack;
    typedef TypeParam particle_t;
    st::arch_status_t status = st::tests::Particle_tests_assignment<
        particle_t >( 100u );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
}
