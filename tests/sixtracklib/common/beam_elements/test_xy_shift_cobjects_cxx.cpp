#include "sixtracklib/common/beam_elements/xy_shift.hpp"

#include <cstdint>
#include <limits>
#include <random>
#include <vector>

#include <gtest/gtest.h>

namespace SIXTRL_CXX_NAMESPACE
{
    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TXYShift< long double >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::XYShift delegate_t;
    };

    template< store_backend_t StoreT > struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::TXYShift< float >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::XYShift delegate_t;
    };
}

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/testlib/common/cobjects/cobjects_elem_base_test_api.hpp"

template< class XYShiftSetT >
class CXXCommonBeXYShiftCObjects : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using LongDblXYShift = SIXTRL_CXX_NAMESPACE::TXYShift< long double >;
    using SinglePrecXYShift = SIXTRL_CXX_NAMESPACE::TXYShift< float >;

    using CXXXYShiftTypes = ::testing::Types< SIXTRL_CXX_NAMESPACE::XYShift,
        SIXTRL_CXX_NAMESPACE::CXYShift, LongDblXYShift, SinglePrecXYShift >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeXYShiftCObjects,
                  SIXTRL_CXX_NAMESPACE::tests::CXXXYShiftTypes );

TYPED_TEST( CXXCommonBeXYShiftCObjects, XYShiftSetUnitTest )
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
