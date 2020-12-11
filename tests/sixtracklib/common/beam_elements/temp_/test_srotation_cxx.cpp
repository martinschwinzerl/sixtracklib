#include "sixtracklib/common/beam_elements/srotation.hpp"

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

template< class SRotationT >
class CXXCommonBeSRotation : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    typedef SIXTRL_CXX_NAMESPACE::TSRotation< float > SinglePrecSRotation;
    typedef SIXTRL_CXX_NAMESPACE::TSRotation< long double > LongDblSRotation;

    typedef ::testing::Types< SIXTRL_CXX_NAMESPACE::SRotation,
        SIXTRL_CXX_NAMESPACE::CSRotation, LongDblSRotation,
            SinglePrecSRotation > TestTypes;

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXCommonBeSRotation, SIXTRL_CXX_NAMESPACE::tests::TestTypes );

TYPED_TEST( CXXCommonBeSRotation, BasicUsage )
{
    namespace st = sixtrack;
    typedef TypeParam elem_t;
    typedef typename st::SRotationTraits< elem_t >::real_t real_t;
    typedef typename st::tests::ObjsRandomInitialiserTraits<
                elem_t >::initialiser_t initialiser_t;

    typedef st::arch_size_t st_size_t;

    initialiser_t initialiser;

    constexpr st_size_t NUM_ATTEMPTS = st_size_t{ 1000 };

    real_t const ABS_TOL = real_t{ 1000 } *
        std::numeric_limits< real_t >::epsilon();

    real_t const REL_TOL = real_t{ 1000 } *
        std::numeric_limits< real_t >::epsilon();

    elem_t srotation;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        initialiser.randomise( &srotation ) );

    for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_ATTEMPTS ; ++ii )
    {
        real_t const random_angle_deg = initialiser.random_angle_deg_value();
        real_t const random_angle_rad = st::MathConst_deg2rad<
            real_t >() * random_angle_deg;

        real_t const random_cos_z = st::cos< real_t >( random_angle_rad );
        real_t const random_sin_z = st::sin< real_t >( random_angle_rad );

        real_t const saved_cos_z = st::SRotation_cos_z( &srotation );
        real_t const saved_sin_z = st::SRotation_sin_z( &srotation );

        if( ( st::Type_comp_all_not_equal< real_t >(
                saved_cos_z, random_cos_z ) ) ||
            ( st::Type_comp_all_not_equal< real_t >(
                saved_sin_z, random_sin_z ) ) )
        {
            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
                st::SRotation_update_angle_rad( &srotation, random_angle_rad ) );

            ASSERT_TRUE( st::Type_comp_all_are_close< real_t >(
                random_cos_z, st::SRotation_cos_z( &srotation ),
                    REL_TOL, ABS_TOL ) );

            ASSERT_TRUE( st::Type_comp_all_are_close< real_t >(
                random_sin_z, st::SRotation_sin_z( &srotation ),
                    REL_TOL, ABS_TOL ) );

            ASSERT_TRUE( st::Type_comp_all_are_close< real_t >(
                random_angle_rad, st::SRotation_angle_rad( &srotation ),
                    REL_TOL, ABS_TOL ) );

            ASSERT_TRUE( st::Type_comp_all_are_close< real_t >(
                random_angle_deg, st::SRotation_angle_deg( &srotation ),
                    REL_TOL, ABS_TOL ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
                st::SRotation_update_angle_deg( &srotation, random_angle_deg ) );

            ASSERT_TRUE( st::Type_comp_all_are_close< real_t >(
                random_cos_z, st::SRotation_cos_z( &srotation ),
                    REL_TOL, ABS_TOL ) );

            ASSERT_TRUE( st::Type_comp_all_are_close< real_t >(
                random_sin_z, st::SRotation_sin_z( &srotation ),
                    REL_TOL, ABS_TOL ) );

            ASSERT_TRUE( st::Type_comp_all_are_close< real_t >(
                random_angle_rad, st::SRotation_angle_rad( &srotation ),
                    REL_TOL, ABS_TOL ) );

            ASSERT_TRUE( st::Type_comp_all_are_close< real_t >(
                random_angle_deg, st::SRotation_angle_deg( &srotation ),
                    REL_TOL, ABS_TOL ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
                st::SRotation_set_cos_z( &srotation, random_cos_z ) );

            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
                st::SRotation_set_sin_z( &srotation, random_sin_z ) );

            ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                random_cos_z, st::SRotation_cos_z( &srotation ) ) );

            ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                random_sin_z, st::SRotation_sin_z( &srotation ) ) );

            ASSERT_TRUE( st::Type_comp_all_are_close< real_t >(
                random_angle_rad, st::SRotation_angle_rad( &srotation ),
                    REL_TOL, ABS_TOL ) );

            ASSERT_TRUE( st::Type_comp_all_are_close< real_t >(
                random_angle_deg, st::SRotation_angle_deg( &srotation ),
                    REL_TOL, ABS_TOL ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
                st::SRotation_set_cos_z( &srotation, saved_cos_z ) );

            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
                st::SRotation_set_sin_z( &srotation, saved_sin_z ) );

            ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                saved_cos_z, st::SRotation_cos_z( &srotation ) ) );

            ASSERT_TRUE( st::Type_comp_all_equal< real_t >(
                saved_sin_z, st::SRotation_sin_z( &srotation ) ) );
        }
    }
}
