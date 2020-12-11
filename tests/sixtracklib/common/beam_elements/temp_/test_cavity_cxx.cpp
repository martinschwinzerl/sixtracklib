#include "sixtracklib/common/beam_elements/cavity.hpp"

#include <algorithm>
#include <limits>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/testlib/common/beam_elements.hpp"
#include "sixtracklib/testlib/common/objs.hpp"
#include "sixtracklib/testlib/common/cobjects.hpp"

template< class CavityT >
class CXXCommonBeCavity : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    typedef SIXTRL_CXX_NAMESPACE::TCavity< float > SinglePrecCavity;
    typedef SIXTRL_CXX_NAMESPACE::TCavity< long double > LongDblCavity;

    typedef ::testing::Types< SIXTRL_CXX_NAMESPACE::Cavity,
        SIXTRL_CXX_NAMESPACE::CCavity, LongDblCavity, SinglePrecCavity > TestTypes;

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeCavity, SIXTRL_CXX_NAMESPACE::tests::TestTypes );

TYPED_TEST( CXXCommonBeCavity, BasicUsage )
{
    namespace st = sixtrack;
    typedef TypeParam elem_t;
    typedef typename st::CavityTraits< elem_t >::real_t real_t;
    typedef typename st::tests::ObjsRandomInitialiserTraits<
                elem_t >::initialiser_t initialiser_t;

    initialiser_t initialiser;

    real_t const random_voltage = initialiser.random_voltage_value();
    real_t const random_frequency    = initialiser.random_frequency_value();
    real_t const random_lag    = initialiser.random_lag_value();

    elem_t cavity;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == initialiser.randomise( &cavity ) );

    if( st::Type_comp_all_not_equal< real_t >(
            st::Cavity_voltage( &cavity ), random_voltage ) )
    {
        real_t const saved_voltage = st::Cavity_voltage( &cavity );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::Cavity_set_voltage(
                        &cavity, random_voltage ) );
        ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                        st::Cavity_voltage( &cavity ), random_voltage ) );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::Cavity_set_voltage(
                        &cavity, saved_voltage ) );

        ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                        st::Cavity_voltage( &cavity ), saved_voltage ) );
    }

    if( st::Type_comp_all_not_equal< real_t >(
            st::Cavity_frequency( &cavity ), random_frequency ) )
    {
        real_t const saved_frequency = st::Cavity_frequency( &cavity );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::Cavity_set_frequency(
                        &cavity, random_frequency ) );
        ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                        st::Cavity_frequency( &cavity ), random_frequency ) );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::Cavity_set_frequency(
                        &cavity, saved_frequency ) );

        ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                        st::Cavity_frequency( &cavity ), saved_frequency ) );
    }

    if( st::Type_comp_all_not_equal< real_t >(
            st::Cavity_lag( &cavity ), random_lag ) )
    {
        real_t const saved_lag = st::Cavity_lag( &cavity );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::Cavity_set_lag(
                        &cavity, random_lag ) );
        ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                        st::Cavity_lag( &cavity ), random_lag ) );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::Cavity_set_lag(
                        &cavity, saved_lag ) );

        ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                        st::Cavity_lag( &cavity ), saved_lag ) );
    }
}
