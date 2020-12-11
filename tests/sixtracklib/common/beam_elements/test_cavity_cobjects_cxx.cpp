#include "sixtracklib/common/beam_elements/cavity.hpp"

#include <cstdint>
#include <limits>
#include <random>
#include <vector>

#include <gtest/gtest.h>

namespace SIXTRL_CXX_NAMESPACE
{
    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TCavity< long double >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Cavity delegate_t;
    };

    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TCavity< float >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Cavity delegate_t;
    };
}

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/testlib/common/cobjects/cobjects_elem_base_test_api.hpp"

template< class CavitySetT >
class CXXCommonBeCavityCObjects : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using LongDblCavity = SIXTRL_CXX_NAMESPACE::TCavity< long double >;
    using SinglePrecCavity = SIXTRL_CXX_NAMESPACE::TCavity< float >;

    using CXXCavityTypes = ::testing::Types< SIXTRL_CXX_NAMESPACE::Cavity,
        SIXTRL_CXX_NAMESPACE::CCavity, LongDblCavity, SinglePrecCavity >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeCavityCObjects,
                  SIXTRL_CXX_NAMESPACE::tests::CXXCavityTypes );

TYPED_TEST( CXXCommonBeCavityCObjects, CavitySetUnitTest )
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
