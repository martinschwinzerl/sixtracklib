#include "sixtracklib/common/beam_elements/drift.hpp"

#include <cstdint>
#include <limits>
#include <random>
#include <vector>

#include <gtest/gtest.h>

namespace SIXTRL_CXX_NAMESPACE
{
    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TDrift< long double >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Drift delegate_t;
    };

    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TDrift< float >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Drift delegate_t;
    };
}

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/testlib/common/cobjects/cobjects_elem_base_test_api.hpp"

template< class DriftSetT >
class CXXCommonBeDriftCObjects : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using LongDblDrift = SIXTRL_CXX_NAMESPACE::TDrift< long double >;
    using SinglePrecDrift = SIXTRL_CXX_NAMESPACE::TDrift< float >;

    using CXXDriftTypes = ::testing::Types< SIXTRL_CXX_NAMESPACE::Drift,
        SIXTRL_CXX_NAMESPACE::CDrift, LongDblDrift, SinglePrecDrift >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeDriftCObjects,
                  SIXTRL_CXX_NAMESPACE::tests::CXXDriftTypes );

TYPED_TEST( CXXCommonBeDriftCObjects, DriftSetUnitTest )
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
