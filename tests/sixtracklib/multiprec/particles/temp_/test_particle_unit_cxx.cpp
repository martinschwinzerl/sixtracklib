#include "sixtracklib/multiprec/particles/particle_unit.hpp"

#include <cstdint>
#include <limits>
#include <random>
#include <vector>

#include <gtest/gtest.h>
#include <boost/math/tools/precision.hpp>
#include <boost/random.hpp>

#include "sixtracklib/common/internal/math_functions.h"
#include "sixtracklib/common/internal/physics_constants.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"

template< typename ParticleT >
class CXXMultiprecParticlesParticleUnit : public ::testing::Test
{
    public:
};

namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    using CXXParticleTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::SinglePrecParticle,
        SIXTRL_CXX_NAMESPACE::DoublePrecParticle,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecParticle,
        SIXTRL_CXX_NAMESPACE::QuadPrecParticle,
        SIXTRL_CXX_NAMESPACE::OctPrecParticle >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecParticlesParticleUnit,
                  SIXTRL_CXX_NAMESPACE::tests::CXXParticleTypes );

TYPED_TEST( CXXMultiprecParticlesParticleUnit, BasicApi )
{
    namespace st = sixtrack;
    typedef TypeParam particle_t;
    typedef typename st::ParticleTraits< particle_t >::real_t real_t;
    typedef typename st::ParticleTraits< particle_t >::index_t index_t;

    const real_t EPS = std::numeric_limits< real_t >::epsilon();
    constexpr unsigned int NDIGITS = std::numeric_limits< real_t >::digits;

    ASSERT_TRUE(  st::Particle_is_type< particle_t >() );
    ASSERT_FALSE( st::Particle_is_type< real_t >() );
    ASSERT_FALSE( st::Particle_is_type< index_t >() );
    ASSERT_TRUE(  st::Particle_impl_default< particle_t >() );

    ASSERT_TRUE(  st::Particle_num_particles< particle_t >() ==
                  st::particle_num_elements_t{ 1 } );

    particle_t p;
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::Particle_init( &p ) );

    ASSERT_TRUE( st::abs< real_t >( st::Particle_x( &p ) -
                    st::Particle_default_x( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_px( &p ) -
                    st::Particle_default_px( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_y( &p ) -
                    st::Particle_default_y( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_py( &p ) -
                    st::Particle_default_py( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_zeta( &p ) -
                    st::Particle_default_zeta( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_delta( &p ) -
                    st::Particle_default_delta( &p ) ) < EPS );

    ASSERT_TRUE( st::Particle_state( &p ) == index_t{ 1 } );
    ASSERT_TRUE( st::Particle_at_element( &p ) == index_t{ 0 } );
    ASSERT_TRUE( st::Particle_at_turn( &p ) == index_t{ 0 } );
    ASSERT_TRUE( st::Particle_id( &p ) == index_t{ 0 } );

    ASSERT_TRUE( st::abs< real_t >( st::Particle_psigma( &p ) -
                    st::Particle_default_psigma( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_rpp( &p ) -
                    st::Particle_default_rpp( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_rvv( &p ) -
                    st::Particle_default_rvv( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_chi( &p ) -
                    st::Particle_default_chi( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_charge_ratio( &p ) -
                    st::Particle_default_charge_ratio( &p ) ) < EPS );

    ASSERT_TRUE( st::abs< real_t >( st::Particle_charge0( &p ) -
                    st::PhysConst_charge0< real_t >() ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_mass0( &p ) -
                    st::Particle_default_mass0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_beta0( &p ) -
                    st::Particle_default_beta0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_gamma0( &p ) -
                    st::Particle_default_gamma0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( st::Particle_pc0( &p ) -
                    st::Particle_default_pc0( &p ) ) < EPS );

    ASSERT_TRUE( st::abs< real_t >( st::Particle_s( &p ) -
                    st::Particle_default_s( &p ) ) < EPS );

    /* --------------------------------------------------------------------- */
    /* Assign legal values */

    boost::random::independent_bits_engine<
        boost::random::mt19937, NDIGITS, boost::multiprecision::cpp_int >
    prng( 20200420 );

    boost::random::uniform_real_distribution< real_t > coord_dist(
        real_t{ -1e-2 }, real_t{ 1e-2 } );
    boost::random::uniform_real_distribution< real_t > ratio_dist(
        real_t{ 1e-8 }, real_t{ 0.99 } );

    real_t x_value            = coord_dist( prng );
    real_t px_value           = coord_dist( prng );
    real_t y_value            = coord_dist( prng );
    real_t py_value           = coord_dist( prng );
    real_t zeta_value         = coord_dist( prng );
    real_t delta_value        = coord_dist( prng );

    index_t state_value       = index_t{ 0 };
    index_t at_element_value  = index_t{ 42 };
    index_t at_turn_value     = index_t{ 137 };
    index_t id_value          = index_t{ 1024 };

    real_t psigma_value       = coord_dist( prng );
    real_t rpp_value          = ratio_dist( prng );
    real_t rvv_value          = ratio_dist( prng );
    real_t chi_value          = ratio_dist( prng );
    real_t charge_ratio_value = ratio_dist( prng );

    real_t charge0_value      = real_t{ -1 };
    real_t mass0_value        = real_t{ 238 } *
        st::PhysConst_mass_atomic_ev_for_particle( &p );

    real_t beta0_value        = ratio_dist( prng );
    real_t gamma0_value       = real_t{ 1 } / st::sqrt< real_t >(
        real_t{ 1 } - beta0_value * beta0_value );
    real_t pc0_value          = real_t{ 6.5e5 };
    real_t s_value            = st::abs< real_t >( coord_dist( prng ) );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_x( &p,  x_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_px( &p, px_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_y( &p, y_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_py( &p, py_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_zeta( &p, zeta_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_delta( &p,  delta_value ) );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_state( &p, state_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_at_element( &p, at_element_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_at_turn( &p, at_turn_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_id( &p, id_value ) );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_psigma( &p,  psigma_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_rvv( &p, rvv_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_rpp( &p, rpp_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_chi( &p, chi_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_charge_ratio( &p, charge_ratio_value ) );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_charge0( &p, charge0_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_mass0( &p, mass0_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_beta0( &p, beta0_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_gamma0( &p, gamma0_value ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_pc0( &p, pc0_value ) );

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_s( &p,  s_value ) );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    ASSERT_TRUE( st::abs< real_t >( x_value -
        st::Particle_x( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( px_value -
        st::Particle_px( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( y_value -
        st::Particle_y( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( py_value -
        st::Particle_py( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( zeta_value -
        st::Particle_zeta( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( delta_value -
        st::Particle_delta( &p ) ) < EPS );

    ASSERT_TRUE( st::Particle_state( &p )      == state_value );
    ASSERT_TRUE( st::Particle_at_element( &p ) == at_element_value );
    ASSERT_TRUE( st::Particle_at_turn( &p )    == at_turn_value );
    ASSERT_TRUE( st::Particle_id( &p )         == id_value );

    ASSERT_TRUE( st::abs< real_t >( psigma_value -
        st::Particle_psigma( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( rpp_value - st::Particle_rpp( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( rvv_value - st::Particle_rvv( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( chi_value - st::Particle_chi( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( charge_ratio_value -
        st::Particle_charge_ratio( &p ) ) < EPS );

    ASSERT_TRUE( st::abs< real_t >( charge0_value -
        st::Particle_charge0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( mass0_value -
        st::Particle_mass0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( beta0_value -
        st::Particle_beta0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( gamma0_value -
        st::Particle_gamma0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( pc0_value -
        st::Particle_pc0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( s_value - st::Particle_s( &p ) ) < EPS );

    /* --------------------------------------------------------------------- */
    /* Attempt assign illegal values */

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_charge0( &p, real_t{ 0 } ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_mass0( &p, real_t{ -1 } ) );
    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_mass0( &p, real_t{ 0 } ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_beta0( &p, real_t{ 1.1 } ) );
    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_beta0( &p, real_t{ -0.1 } ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_gamma0( &p, real_t{ 0.99 } ) );
    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_gamma0( &p, real_t{ -1 } ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_pc0( &p, real_t{ -1e-9 } ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_chi( &p, real_t{ 0 } ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_charge_ratio( &p, real_t{ 0 } ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_state( &p, index_t{ -1 } ) );
    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_state( &p, index_t{ 2 } ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_at_element( &p, index_t{ -1 } ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
        st::Particle_set_at_turn( &p, index_t{ -1 } ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS ==
            st::Particle_set_id( &p, index_t{ -1 } ) );

    /* --------------------------------------------------------------------- */
    /* Attempt assign illegal types */

    real_t const wrong_x[] = { real_t{ 1e-5 } };
    std::vector< real_t > wrong_px = { real_t{ 0.56 } };

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS == st::Particle_set_x(
        &p, wrong_x ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS == st::Particle_set_px(
        &p, wrong_px ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS == st::Particle_set_px(
        &p, wrong_px.data() ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS == st::Particle_set_px(
        &p, wrong_px.begin() ) );

    ASSERT_FALSE( st::ARCH_STATUS_SUCCESS == st::Particle_set_px(
        &p, std::move( wrong_px ) ) );

    /* - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - -  */

    ASSERT_TRUE( st::Particle_state( &p )      == state_value );
    ASSERT_TRUE( st::Particle_at_element( &p ) == at_element_value );
    ASSERT_TRUE( st::Particle_at_turn( &p )    == at_turn_value );
    ASSERT_TRUE( st::Particle_id( &p )         == id_value );

    ASSERT_TRUE( st::abs< real_t >( charge0_value -
        st::Particle_charge0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( mass0_value -
        st::Particle_mass0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( beta0_value -
        st::Particle_beta0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( gamma0_value -
        st::Particle_gamma0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( pc0_value -
        st::Particle_pc0( &p ) ) < EPS );

    ASSERT_TRUE( st::abs< real_t >( chi_value -
        st::Particle_chi( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( charge_ratio_value -
        st::Particle_charge_ratio( &p ) ) < EPS );

    /* --------------------------------------------------------------------- */

    x_value            = coord_dist( prng );
    px_value           = coord_dist( prng );
    y_value            = coord_dist( prng );
    py_value           = coord_dist( prng );
    zeta_value         = coord_dist( prng );
    delta_value        = coord_dist( prng );

    state_value        = index_t{ 1 };
    at_element_value   = index_t{ 2048 };
    at_turn_value      = index_t{ 1000000 };
    id_value           = index_t{ 1 };

    psigma_value       = coord_dist( prng );
    rpp_value          = ratio_dist( prng );
    rvv_value          = ratio_dist( prng );
    chi_value          = ratio_dist( prng );
    charge_ratio_value = ratio_dist( prng );

    charge0_value      = st::PhysConst_charge0_for_particle( &p );
    mass0_value        = st::PhysConst_mass_proton_ev_for_particle( &p );

    beta0_value        = ratio_dist( prng );
    gamma0_value       = real_t{ 1 } / st::sqrt< real_t >(
        real_t{ 1 } - beta0_value * beta0_value );
    pc0_value          = real_t{ 1e9 };
    s_value            = st::abs< real_t >( coord_dist( prng ) );

    ASSERT_TRUE( st::Particle_init( &p, x_value, px_value, y_value, py_value,
                    zeta_value, delta_value, state_value, at_element_value,
                        at_turn_value, id_value, psigma_value, rpp_value,
                            rvv_value, chi_value, charge_ratio_value,
                                charge0_value, mass0_value, beta0_value,
                                    gamma0_value, pc0_value, s_value ) ==
                 st::ARCH_STATUS_SUCCESS );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    ASSERT_TRUE( st::abs< real_t >( x_value -
        st::Particle_x( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( px_value -
        st::Particle_px( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( y_value -
        st::Particle_y( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( py_value -
        st::Particle_py( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( zeta_value -
        st::Particle_zeta( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( delta_value -
        st::Particle_delta( &p ) ) < EPS );

    ASSERT_TRUE( st::Particle_state( &p )      == state_value );
    ASSERT_TRUE( st::Particle_at_element( &p ) == at_element_value );
    ASSERT_TRUE( st::Particle_at_turn( &p )    == at_turn_value );
    ASSERT_TRUE( st::Particle_id( &p )         == id_value );

    ASSERT_TRUE( st::abs< real_t >( psigma_value -
        st::Particle_psigma( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( rpp_value - st::Particle_rpp( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( rvv_value - st::Particle_rvv( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( chi_value - st::Particle_chi( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( charge_ratio_value -
        st::Particle_charge_ratio( &p ) ) < EPS );

    ASSERT_TRUE( st::abs< real_t >( charge0_value -
        st::Particle_charge0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( mass0_value -
        st::Particle_mass0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( beta0_value -
        st::Particle_beta0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( gamma0_value -
        st::Particle_gamma0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( pc0_value -
        st::Particle_pc0( &p ) ) < EPS );
    ASSERT_TRUE( st::abs< real_t >( s_value - st::Particle_s( &p ) ) < EPS );
}

