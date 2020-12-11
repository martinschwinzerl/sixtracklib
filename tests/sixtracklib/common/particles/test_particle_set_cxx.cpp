#include "sixtracklib/common/particle.hpp"

#include <gtest/gtest.h>

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/particles.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"

template< typename ParticleSetT >
class CXXCommonParticlesParticleSet : public ::testing::Test { public: };

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using LongDblParticleSet =
        SIXTRL_CXX_NAMESPACE::TParticleSet< long double, int64_t >;

    using SinglePrecParticleSet =
        SIXTRL_CXX_NAMESPACE::TParticleSet< float, int64_t >;

    using SingleVecParticleSet =
        SIXTRL_CXX_NAMESPACE::TVectorParticleSet< float, int64_t >;

    using DoubleVecParticleSet =
        SIXTRL_CXX_NAMESPACE::TVectorParticleSet< double, int64_t >;

    using LongDblVecParticleSet =
        SIXTRL_CXX_NAMESPACE::TVectorParticleSet< long double, int64_t >;

    using CXXParticleSetTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::ParticleSet,
        SIXTRL_CXX_NAMESPACE::CParticleSet,
        LongDblParticleSet, SinglePrecParticleSet, DoubleVecParticleSet,
        SingleVecParticleSet, LongDblVecParticleSet >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonParticlesParticleSet,
                  SIXTRL_CXX_NAMESPACE::tests::CXXParticleSetTypes );

TYPED_TEST( CXXCommonParticlesParticleSet, BasicUsage )
{
    namespace st = sixtrack;
    st::arch_status_t status = st::tests::ParticleSet_tests_assignment<
        TypeParam >( st::arch_size_t{ 100 } );

    ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
}
