#include "sixtracklib/multiprec/beam_elements/multipole.hpp"

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include <gtest/gtest.h>
#include <boost/math/tools/precision.hpp>
#include <boost/random.hpp>


#include "sixtracklib/multiprec/random.hpp"
#include "sixtracklib/common/internal/math_factorial.h"
#include "sixtracklib/common/internal/math_functions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"

template< typename MultipoleT >
class CXXMultiprecBeMultipoleTests : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXMultiprecMultipoleTypes = ::testing::Types<
        SinglePrecMultipole, DoublePrecMultipole, ExtDoublePrecMultipole,
        QuadPrecMultipole, OctPrecMultipole >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecBeMultipoleTests,
                  SIXTRL_CXX_NAMESPACE::tests::CXXMultiprecMultipoleTypes );

TYPED_TEST( CXXMultiprecBeMultipoleTests, BasicUsage )
{
    namespace st = sixtrack;
    typedef TypeParam multipole_t;
    typedef typename st::MultipoleTraits< multipole_t >::real_t  real_t;
    typedef typename st::MultipoleTraits< multipole_t >::order_t order_t;
    typedef st::be_address_t st_addr_t;
    typedef st_size_t st_size_t;

    static_assert( st::TypeRandomTraits< real_t >::has_uniform_dist,
                   "multi-precision real type does not have an associated "
                   "uniform distribution for randomized values" );

    typedef typename st::TypeRandomTraits< real_t >::default_prng_t prng_t;
    typedef typename st::TypeRandomTraits< real_t >::uniform_dist_t bal_dist_t;
    typedef typename st::TypeRandomTraits< real_t >::default_prng_seed_t
            prng_seed_t;

    const real_t EPS = std::numeric_limits< real_t >::epsilon();

    ASSERT_TRUE(  st::Multipole_is_type< multipole_t >() );
    ASSERT_FALSE( st::Multipole_is_type< int64_t >() );
    ASSERT_FALSE( st::Multipole_is_type< real_t >() );

    ASSERT_TRUE(  st::Multipole_impl_std_vector< multipole_t >() );
    ASSERT_FALSE( st::Multipole_impl_std_vector< int64_t >() );
    ASSERT_FALSE( st::Multipole_impl_std_vector< real_t >() );

    multipole_t mp;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::Multipole_init(
        &mp, order_t{ 1 }, double{ 42 }, double{ 1 }, double{ -1 } ) );

    ASSERT_TRUE( st::Multipole_order( &mp ) == order_t{ 1 } );
    ASSERT_TRUE( st::Multipole_bal_length( &mp ) == st_size_t{ 4 } );
    ASSERT_TRUE( st::abs< real_t >( st::Multipole_length( &mp ) -
                            real_t{ 42 } ) <= EPS );

    ASSERT_TRUE( st::abs< real_t >( st::Multipole_hxl( &mp ) -
                            real_t{ 1 } ) <= EPS );

    ASSERT_TRUE( st::abs< real_t >( st::Multipole_hyl( &mp ) -
                            real_t{ -1 } ) <= EPS );

    ASSERT_TRUE( st::Multipole_bal_addr( &mp ) != st_addr_t{ 0 } );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Multipole_set_order( &mp, 5u ) );

    ASSERT_TRUE( st::Multipole_order( &mp ) == 5u );
    ASSERT_TRUE( st::Multipole_bal_length( &mp ) == 12u );

    st_size_t const nn = st::Multipole_bal_length( &mp );

    ASSERT_TRUE( st::Multipole_const_bal_begin( &mp ) != nullptr );
    ASSERT_TRUE( st::Multipole_const_bal_end( &mp ) != nullptr );
    ASSERT_TRUE( std::distance( st::Multipole_const_bal_begin( &mp ),
        st::Multipole_const_bal_end( &mp ) ) ==
            static_cast< std::ptrdiff_t >( nn ) );

    prng_t prng( prng_seed_t{ 20200420 } );
    bal_dist_t bal_dst( real_t{ -2.0 }, real_t{ 2.0 } );

    std::vector< real_t > cmp_values( nn );
    std::for_each( cmp_values.begin(), cmp_values.end(),
                   [&bal_dst, &prng]( real_t& SIXTRL_RESTRICT_REF val )
                   { val = bal_dst( prng ); } );

    for( st_size_t ii = st_size_t{ 0 } ; ii < nn ; ++ii )
    {
        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
            st::Multipole_set_bal_value( &mp, ii, cmp_values[ ii ] ) );
    }

    ASSERT_TRUE( std::equal( cmp_values.begin(), cmp_values.end(),
                             st::Multipole_const_bal_begin( &mp ) ) );

    real_t cmp_factorial = real_t{ 1 };

    for( st_size_t ii = st_size_t{ 0 } ; ii < nn ; ii += 2u )
    {
        st_size_t jj = ii >> 1;
        if( jj != st_size_t{ 0 } ) cmp_factorial *= jj;

        ASSERT_TRUE( st::abs< real_t >( cmp_values[ ii ] -
            st::Multipole_bal( &mp, ii ) ) <= EPS );

        ASSERT_TRUE( st::abs< real_t >( cmp_values[ ii ] * cmp_factorial -
            st::Multipole_knl( &mp, jj ) ) <= EPS );

        ASSERT_TRUE( st::abs< real_t >( cmp_values[ ii + 1u ] -
            st::Multipole_bal( &mp, ii + 1u ) ) <= EPS );

        ASSERT_TRUE( st::abs< real_t >( cmp_values[ ii + 1u ] * cmp_factorial -
            st::Multipole_ksl( &mp, jj ) ) <= EPS );
    }

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Multipole_set_all_bal_values( &mp, real_t{ 0 } ) );

    cmp_factorial = real_t{ 1 };

    for( st_size_t ii = st_size_t{ 0 } ; ii < nn ; ii += 2u )
    {
        st_size_t jj = ii >> 1;
        if( jj != st_size_t{ 0 } ) cmp_factorial *= jj;

        ASSERT_TRUE( st::abs< real_t >( st::Multipole_bal( &mp, ii ) -
            real_t{ 0 } ) < EPS );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::Multipole_set_knl_value(
            &mp, jj, cmp_values[ ii ] ) );

        real_t const diff_knl = st::abs< real_t >( st::Multipole_knl( &mp, jj ) -
            cmp_values[ ii ] );

        ASSERT_TRUE( diff_knl < EPS );

        ASSERT_TRUE( st::abs< real_t >( st::Multipole_bal( &mp, ii ) -
            cmp_values[ ii ] / cmp_factorial ) <= EPS );

        ASSERT_TRUE( st::abs< real_t >( st::Multipole_bal( &mp, ii + 1u ) -
            real_t{ 0 } ) < EPS );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::Multipole_set_ksl_value(
            &mp, jj, cmp_values[ ii + 1u ] ) );

        ASSERT_TRUE( st::abs< real_t >( st::Multipole_ksl( &mp, jj ) -
            cmp_values[ ii + 1u ] ) <= EPS );

        ASSERT_TRUE( st::abs< real_t >( st::Multipole_bal( &mp, ii + 1u ) -
            cmp_values[ ii + 1u ] / cmp_factorial ) < EPS );
    }

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::Multipole_set_all_knl_values(
                    &mp, real_t{ 42 } ) );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::Multipole_set_all_ksl_values(
                    &mp, real_t{ 137 } ) );

    for( st_size_t ii = st_size_t{ 0 } ; ii < nn ; ii += 2u )
    {
        st_size_t jj = ii >> 1;
        if( jj != st_size_t{ 0 } ) cmp_factorial *= jj;

        ASSERT_TRUE( st::abs< real_t >( st::Multipole_knl( &mp, jj ) -
            real_t{ 42 } ) <= EPS );

        ASSERT_TRUE( st::abs< real_t >( st::Multipole_bal( &mp, ii ) -
            real_t{ 42 } / st::Math_factorial< st_size_t, real_t >( jj )
                ) <= EPS );

        ASSERT_TRUE( st::abs< real_t >( st::Multipole_ksl( &mp, jj ) -
            real_t{ 137 } ) <= EPS );

        ASSERT_TRUE( st::abs< real_t >( st::Multipole_bal( &mp, ii + 1u ) -
            real_t{ 137 } / st::Math_factorial< st_size_t, real_t >( jj )
                ) <= EPS );
    }
}
