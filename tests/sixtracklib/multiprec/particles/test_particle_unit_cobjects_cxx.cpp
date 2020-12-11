#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/particles/particle_unit.hpp"

#include <gtest/gtest.h>

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/particles.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/testlib/common/cobjects/cobjects_elem_base_test_api.hpp"

template< class ParticleT >
class CXXMultiprecParticlesParticleUnitCObjects : public ::testing::Test
{
    public:
};

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

TYPED_TEST_SUITE( CXXMultiprecParticlesParticleUnitCObjects,
                  SIXTRL_CXX_NAMESPACE::tests::CXXParticleTypes );

TYPED_TEST( CXXMultiprecParticlesParticleUnitCObjects, ParticleUnitTest )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    typedef TypeParam obj_t;

    if( st::CObjElem_allow_direct_storage< obj_t >() )
    {
        st::arch_status_t const status =
            st::tests::CObjElem_test_direct_storage_view_buffer< obj_t >(
                st::arch_size_t{ 20 } );
        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }
    else if( SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< obj_t >() )
    {
        st::arch_status_t const status =
            st::tests::CObjElem_test_delegate_storage_view_buffer< obj_t >(
                st::arch_size_t{ 20 } );
        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }
    else
    {
        ASSERT_TRUE( st::CObjElem_allow_direct_storage< obj_t >() ||
                     st::CObjElem_allow_delegate_storage< obj_t >() );
    }
}
