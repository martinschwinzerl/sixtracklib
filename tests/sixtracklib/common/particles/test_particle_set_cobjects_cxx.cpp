#include "sixtracklib/common/particle.hpp"
#include <gtest/gtest.h>

namespace SIXTRL_CXX_NAMESPACE
{
    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TParticleSet< long double, int64_t >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::ParticleSet delegate_t;
    };

    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TParticleSet< float, int64_t >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::ParticleSet delegate_t;
    };

    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TVectorParticleSet< double, int64_t >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::ParticleSet delegate_t;
    };

    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TVectorParticleSet< float, int64_t >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::ParticleSet delegate_t;
    };

    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TVectorParticleSet< long double, int64_t >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::ParticleSet delegate_t;
    };
}

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/particles.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/testlib/common/cobjects/cobjects_elem_base_test_api.hpp"

template< class ParticleSetT >
class CXXCommonParticleSetsParticleSetUnitCObjects : public ::testing::Test
{
    public:
};

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
        LongDblParticleSet,
        SinglePrecParticleSet,
        DoubleVecParticleSet,
        SingleVecParticleSet,
        LongDblVecParticleSet >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonParticleSetsParticleSetUnitCObjects,
                  SIXTRL_CXX_NAMESPACE::tests::CXXParticleSetTypes );

TYPED_TEST( CXXCommonParticleSetsParticleSetUnitCObjects, ParticleSetUnitTest )
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
    else if( st::CObjElem_allow_delegate_storage< obj_t >() )
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
