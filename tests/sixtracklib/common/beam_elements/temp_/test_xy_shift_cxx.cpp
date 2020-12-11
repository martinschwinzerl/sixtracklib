#include "sixtracklib/common/beam_elements/xy_shift.hpp"

#include <algorithm>
#include <limits>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"
#include "sixtracklib/common/internal/math_constants.h"
#include "sixtracklib/common/internal/math_functions.h"
#include "sixtracklib/common/internal/type_comparison_helpers.hpp"

template< class XYShiftT >
class CXXCommonBeXYShift : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    typedef SIXTRL_CXX_NAMESPACE::TXYShift< float > SinglePrecXYShift;
    typedef SIXTRL_CXX_NAMESPACE::TXYShift< long double > LongDblXYShift;

    typedef ::testing::Types< SIXTRL_CXX_NAMESPACE::XYShift,
        SIXTRL_CXX_NAMESPACE::CXYShift, LongDblXYShift,
            SinglePrecXYShift > TestTypes;

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeXYShift, SIXTRL_CXX_NAMESPACE::tests::TestTypes );

TYPED_TEST( CXXCommonBeXYShift, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    typedef TypeParam elem_t;
    typedef typename st::XYShiftTraits< elem_t >::real_t real_t;
    typedef typename st::tests::ObjsRandomInitialiserTraits<
                elem_t >::initialiser_t initialiser_t;

    typedef st::arch_size_t st_size_t;

    initialiser_t initialiser;
    constexpr st_size_t NUM_ATTEMPTS = st_size_t{ 1000 };

    elem_t xy_shift;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        initialiser.randomise( &xy_shift ) );

    for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_ATTEMPTS ; ++ii )
    {
        real_t const random_dx = initialiser.random_dx_value();
        real_t const random_dy = initialiser.random_dy_value();

        real_t const saved_dx = st::XYShift_dx( &xy_shift );
        real_t const saved_dy = st::XYShift_dy( &xy_shift );

        if( ( st::Type_comp_all_not_equal< real_t >( saved_dx, random_dx ) ) ||
            ( st::Type_comp_all_not_equal< real_t >( saved_dy, random_dy ) ) )
        {
            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
                st::XYShift_set_dx( &xy_shift, random_dx ) );

            ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                random_dx, st::XYShift_dx( &xy_shift ) ) );

            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
                st::XYShift_set_dy( &xy_shift, random_dy ) );

            ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                random_dy, st::XYShift_dy( &xy_shift ) ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
                st::XYShift_set_dx( &xy_shift, saved_dx ) );

            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
                st::XYShift_set_dy( &xy_shift, saved_dy ) );

            ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                saved_dx, st::XYShift_dx( &xy_shift ) ) );

            ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                saved_dy, st::XYShift_dy( &xy_shift ) ) );
        }
    }
}
