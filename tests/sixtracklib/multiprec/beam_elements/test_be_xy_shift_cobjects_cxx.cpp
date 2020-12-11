#include "sixtracklib/multiprec/definitions.h"
#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/multiprec/beam_elements/xy_shift.hpp"

#include <gtest/gtest.h>

namespace SIXTRL_CXX_NAMESPACE
{
    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::DoublePrecXYShift, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::XYShift delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecXYShift, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::XYShift delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::QuadPrecXYShift, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::XYShift delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::OctPrecXYShift, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::XYShift delegate_t;
    };

    template< SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits<
        SIXTRL_CXX_NAMESPACE::SinglePrecXYShift, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::XYShift delegate_t;
    };
}

#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/testlib/common/cobjects/cobjects_elem_base_test_api.hpp"

template< class XYShiftSetT >
class CXXMultiprecBeXYShiftCobjects : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXXYShiftTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::DoublePrecXYShift,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecXYShift,
        SIXTRL_CXX_NAMESPACE::QuadPrecXYShift,
        SIXTRL_CXX_NAMESPACE::OctPrecXYShift,
        SIXTRL_CXX_NAMESPACE::SinglePrecXYShift >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecBeXYShiftCobjects,
                  SIXTRL_CXX_NAMESPACE::tests::CXXXYShiftTypes );

TYPED_TEST( CXXMultiprecBeXYShiftCobjects, XYShiftSetUnitTest )
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
