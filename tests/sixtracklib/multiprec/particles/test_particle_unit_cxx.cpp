#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/particles/particle_unit.hpp"

#include <gtest/gtest.h>

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/particles.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"

template< typename ParticleT >
class CXXMultiprecParticlesParticle : public ::testing::Test { public: };

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXParticleTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::DoublePrecParticle,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecParticle,
        SIXTRL_CXX_NAMESPACE::QuadPrecParticle,
        SIXTRL_CXX_NAMESPACE::OctPrecParticle,
        SIXTRL_CXX_NAMESPACE::SinglePrecParticle >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecParticlesParticle,
                  SIXTRL_CXX_NAMESPACE::tests::CXXParticleTypes );

TYPED_TEST( CXXMultiprecParticlesParticle, BasicApi )
{
    namespace st = sixtrack;
    typedef TypeParam particle_t;
    st::arch_status_t status = st::tests::Particle_tests_assignment<
        particle_t >( 20 );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
}
