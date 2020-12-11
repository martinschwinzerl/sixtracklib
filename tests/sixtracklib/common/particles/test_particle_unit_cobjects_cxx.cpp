#include "sixtracklib/common/particle.hpp"

#include <gtest/gtest.h>

namespace SIXTRL_CXX_NAMESPACE
{
    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TParticle< long double, int64_t >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Particle delegate_t;
    };

    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TParticle< float, int64_t >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Particle delegate_t;
    };
}

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/particles.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/testlib/common/cobjects/cobjects_elem_base_test_api.hpp"

template< class ParticleT >
class CXXCommonParticlesParticleUnitCObjects : public ::testing::Test
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

TYPED_TEST_SUITE( CXXCommonParticlesParticleUnitCObjects,
                  SIXTRL_CXX_NAMESPACE::tests::CXXParticleTypes );

TYPED_TEST( CXXCommonParticlesParticleUnitCObjects, ParticleUnitTest )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    typedef TypeParam obj_t;

    if( st::CObjElem_allow_direct_storage< obj_t >() )
    {
        st::arch_status_t const status =
            st::tests::CObjElem_test_direct_storage_view_buffer< obj_t >(
                st::arch_size_t{ 100 } );
        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }
    else if( SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< obj_t >() )
    {
        st::arch_status_t const status =
            st::tests::CObjElem_test_delegate_storage_view_buffer< obj_t >(
                st::arch_size_t{ 100 } );
        ASSERT_TRUE( status == st::ARCH_STATUS_SUCCESS );
    }
    else
    {
        ASSERT_TRUE( st::CObjElem_allow_direct_storage< obj_t >() ||
                     st::CObjElem_allow_delegate_storage< obj_t >() );
    }
}

