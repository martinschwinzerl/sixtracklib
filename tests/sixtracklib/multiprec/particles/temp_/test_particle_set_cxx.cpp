#include "sixtracklib/multiprec/particles/particle_set.hpp"

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

#include "sixtracklib/common/internal/math_functions.h"
#include "sixtracklib/common/internal/physics_constants.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/particles/particle_set_particle_api.h"
#include "sixtracklib/common/particles/particle_unit_compare.h"
#include "sixtracklib/multiprec/particles/particle_unit.hpp"

template< typename ParticleSetT >
class CXXMultiprecParticlesParticleSet : public ::testing::Test
{
    public:

    typedef SIXTRL_CXX_NAMESPACE::particle_addr_t addr_t;
    typedef typename SIXTRL_CXX_NAMESPACE::ParticleSetTraits<
        ParticleSetT >::real_t real_t;

    typedef typename SIXTRL_CXX_NAMESPACE::ParticleSetTraits<
        ParticleSetT >::index_t index_t;

    typedef SIXTRL_CXX_NAMESPACE::arch_status_t status_t;
    typedef SIXTRL_CXX_NAMESPACE::particle_num_elements_t num_elements_t;

    typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t  const* ptr_const_real_t;
    typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t*        ptr_real_t;

    typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC index_t const* ptr_const_index_t;
    typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC index_t*       ptr_index_t;

    typedef addr_t (*get_field_addr_fn_t)( SIXTRL_PARTICLE_SET_ARGPTR_DEC
            const ParticleSetT *const SIXTRL_RESTRICT );

    typedef status_t (*set_field_addr_fn_t)( SIXTRL_PARTICLE_SET_ARGPTR_DEC
            ParticleSetT* SIXTRL_RESTRICT, addr_t const );

    typedef ptr_const_real_t (*get_real_field_const_ptr_fn_t)(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const
            SIXTRL_RESTRICT );

    typedef ptr_real_t (*get_real_field_ptr_fn_t)(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT );

    typedef ptr_const_index_t (*get_index_field_const_ptr_fn_t)(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const
            SIXTRL_RESTRICT );

    typedef ptr_index_t (*get_index_field_ptr_fn_t)(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT );

    typedef num_elements_t (*get_field_length_fn_t)(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const
            SIXTRL_RESTRICT );

    typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
        real_t >::const_existing_type
    (*get_real_value_fn_t)(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const SIXTRL_RESTRICT,
        num_elements_t const );

    template< typename Arg >
    using set_value_fn_t = status_t (*)(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT,
        num_elements_t const, Arg );

    template< typename Arg >
    using set_values_to_value_fn_t = status_t (*)(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT, Arg );

    template< typename Iter >
    using set_values_fn_t = status_t (*)(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT, Iter );

    typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
        index_t >::const_existing_type
    (*get_index_value_fn_t)(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const SIXTRL_RESTRICT,
        num_elements_t const );

    typedef status_t (*set_index_value_fn_t)(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT,
        num_elements_t const, index_t );

    void check_real_field_ptrs(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT pset,
        get_field_length_fn_t get_field_length_fn,
        get_real_field_const_ptr_fn_t get_const_begin_fn,
        get_real_field_const_ptr_fn_t get_const_end_fn,
        get_real_field_ptr_fn_t get_begin_fn,
        get_real_field_ptr_fn_t get_end_fn )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( pset != nullptr );
        SIXTRL_ASSERT( get_field_length_fn != nullptr );
        SIXTRL_ASSERT( get_const_begin_fn  != nullptr );
        SIXTRL_ASSERT( get_const_end_fn    != nullptr );
        SIXTRL_ASSERT( get_begin_fn        != nullptr );
        SIXTRL_ASSERT( get_end_fn          != nullptr );

        ASSERT_TRUE( st::ParticleSet_num_particles(
            pset ) >= num_elements_t{ 0 } );

        ASSERT_TRUE( st::ParticleSet_capacity( pset ) >=
                     st::ParticleSet_num_particles( pset ) );

        ASSERT_TRUE( get_field_length_fn( pset ) >= num_elements_t{ 0 } );
        ASSERT_TRUE( get_field_length_fn( pset ) <=
                     st::ParticleSet_num_particles( pset ) );

        ASSERT_TRUE( get_const_begin_fn( pset ) != nullptr );
        ASSERT_TRUE( get_const_end_fn( pset ) != nullptr );
        ASSERT_TRUE( std::distance( get_const_begin_fn( pset ),
            get_const_end_fn( pset ) ) == static_cast< std::ptrdiff_t >(
                get_field_length_fn( pset ) ) );

        ASSERT_TRUE( get_begin_fn( pset ) == const_cast<
            ptr_real_t >( get_const_begin_fn( pset ) ) );

        ASSERT_TRUE( get_end_fn( pset ) == const_cast<
            ptr_real_t >( get_const_end_fn( pset ) ) );
    }

     void check_index_field_ptrs(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT pset,
        get_field_length_fn_t get_field_length_fn,
        get_index_field_const_ptr_fn_t get_const_begin_fn,
        get_index_field_const_ptr_fn_t get_const_end_fn,
        get_index_field_ptr_fn_t get_begin_fn,
        get_index_field_ptr_fn_t get_end_fn )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( pset != nullptr );
        SIXTRL_ASSERT( get_field_length_fn != nullptr );
        SIXTRL_ASSERT( get_const_begin_fn  != nullptr );
        SIXTRL_ASSERT( get_const_end_fn    != nullptr );
        SIXTRL_ASSERT( get_begin_fn        != nullptr );
        SIXTRL_ASSERT( get_end_fn          != nullptr );

        ASSERT_TRUE( st::ParticleSet_num_particles(
            pset ) >= num_elements_t{ 0 } );

        ASSERT_TRUE( st::ParticleSet_capacity( pset ) >=
                     st::ParticleSet_num_particles( pset ) );

        ASSERT_TRUE( get_field_length_fn( pset ) >= num_elements_t{ 0 } );
        ASSERT_TRUE( get_field_length_fn( pset ) <=
                     st::ParticleSet_num_particles( pset ) );

        ASSERT_TRUE( get_const_begin_fn( pset ) != nullptr );
        ASSERT_TRUE( get_const_end_fn( pset ) != nullptr );
        ASSERT_TRUE( std::distance( get_const_begin_fn( pset ),
            get_const_end_fn( pset ) ) == static_cast< std::ptrdiff_t >(
                get_field_length_fn( pset ) ) );

        ASSERT_TRUE( get_begin_fn( pset ) == const_cast<
            ptr_index_t >( get_const_begin_fn( pset ) ) );

        ASSERT_TRUE( get_end_fn( pset ) == const_cast<
            ptr_index_t >( get_const_end_fn( pset ) ) );
    }

    /* --------------------------------------------------------------------- */

    void check_set_and_get_real_values(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT pset,
        std::vector< real_t > const& SIXTRL_RESTRICT_REF cmp_values,
        get_real_value_fn_t get_value_fn,
        set_value_fn_t< real_t > set_value_fn,
        get_real_field_const_ptr_fn_t get_const_begin_fn,
        get_real_field_const_ptr_fn_t get_const_end_fn,
        get_real_field_ptr_fn_t get_begin_fn,
        get_real_field_ptr_fn_t get_end_fn,
        set_values_to_value_fn_t< real_t > set_all_values_fn,
        set_values_fn_t< ptr_const_real_t > set_all_values_from_ptr,
        set_values_fn_t< typename std::vector<
            real_t >::const_iterator > set_all_values_from_iter,
        get_field_length_fn_t get_field_length_fn )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        const real_t EPS = std::numeric_limits< real_t >::epsilon();

        SIXTRL_ASSERT( pset != nullptr );
        SIXTRL_ASSERT( get_field_length_fn != nullptr );
        num_elements_t const num_particles = get_field_length_fn( pset );

        SIXTRL_ASSERT( cmp_values.data() != nullptr );
        SIXTRL_ASSERT( cmp_values.size() >=
                       static_cast< std::size_t >( num_particles ) );

        SIXTRL_ASSERT( get_value_fn != nullptr );
        SIXTRL_ASSERT( set_value_fn != nullptr );
        SIXTRL_ASSERT( get_const_begin_fn != nullptr );
        SIXTRL_ASSERT( get_const_end_fn   != nullptr );
        SIXTRL_ASSERT( get_begin_fn != nullptr );
        SIXTRL_ASSERT( get_end_fn   != nullptr );
        SIXTRL_ASSERT( set_all_values_fn != nullptr );
        SIXTRL_ASSERT( set_all_values_from_ptr != nullptr );
        SIXTRL_ASSERT( set_all_values_from_iter != nullptr );

        ASSERT_TRUE( get_const_begin_fn( pset ) != nullptr );
        ASSERT_TRUE( get_const_begin_fn( pset ) != cmp_values.data() );
        ASSERT_TRUE( get_const_end_fn( pset ) != nullptr );
        ASSERT_TRUE( std::distance( get_const_begin_fn( pset ),
            get_const_end_fn( pset ) ) == static_cast< std::ptrdiff_t >(
                num_particles ) );

        ASSERT_TRUE( get_begin_fn( pset ) != nullptr );
        ASSERT_TRUE( get_end_fn( pset ) != nullptr );
        ASSERT_TRUE( std::distance( get_begin_fn( pset ), get_end_fn( pset ) )
                     == static_cast< std::ptrdiff_t >( num_particles ) );

        num_elements_t ii = num_elements_t{ 0 };

        for( ; ii < num_particles ; ++ii )
        {
            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == set_value_fn(
                pset, ii, cmp_values[ ii ] ) );

            ASSERT_TRUE( st::abs< real_t >( get_value_fn( pset, ii ) -
                cmp_values[ ii ] ) < EPS );
        }

        real_t const special_value = real_t{ 42 };

        ASSERT_TRUE( std::equal( get_const_begin_fn( pset ),
                        get_const_end_fn( pset ), cmp_values.begin() ) );

        ASSERT_TRUE( std::equal( get_begin_fn( pset ), get_end_fn( pset ),
                                 cmp_values.begin() ) );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == set_all_values_fn(
                        pset, special_value ) );

        auto cmp_value_with_special_value =
        [EPS, special_value]( real_t const& SIXTRL_RESTRICT_REF val ) -> bool
        {
            return st::abs< real_t >( val - special_value ) < EPS;
        };

        ASSERT_TRUE( std::all_of( get_const_begin_fn( pset ),
            get_const_end_fn( pset ), cmp_value_with_special_value ) );

        ASSERT_FALSE( std::equal( get_const_begin_fn( pset ),
                        get_const_end_fn( pset ), cmp_values.begin() ) );

        ASSERT_FALSE( std::equal( get_begin_fn( pset ), get_end_fn( pset ),
                                  cmp_values.begin() ) );

        for( ; ii < num_particles ; ++ii )
        {
            ASSERT_FALSE( cmp_value_with_special_value(
                get_value_fn( pset, ii ) ) );
        }

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == set_all_values_from_ptr(
            pset, cmp_values.data() ) );

        ASSERT_FALSE( std::all_of( get_const_begin_fn( pset ),
            get_const_end_fn( pset ), cmp_value_with_special_value ) );

        ASSERT_TRUE( std::equal( get_const_begin_fn( pset ),
            get_const_end_fn( pset ), cmp_values.begin() ) );

        ASSERT_TRUE( std::equal( get_begin_fn( pset ), get_end_fn( pset ),
                                 cmp_values.begin() ) );

        for( ; ii < num_particles ; ++ii )
        {
            ASSERT_TRUE( st::abs< real_t >( get_value_fn( pset, ii ) -
                cmp_values[ ii ] ) < EPS );
        }

        std::fill( get_begin_fn( pset ), get_end_fn( pset ), real_t{ 0 } );
        SIXTRL_ASSERT( !std::equal( get_const_begin_fn( pset ),
            get_const_end_fn( pset ), cmp_values.begin() ) );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
            set_all_values_from_iter( pset, cmp_values.cbegin() ) );

        ASSERT_TRUE( std::equal( get_const_begin_fn( pset ),
             get_const_end_fn( pset ), cmp_values.begin() ) );
    }

    void check_set_and_get_index_values(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT pset,
        std::vector< index_t > const& SIXTRL_RESTRICT_REF cmp_values,
        get_index_value_fn_t get_value_fn,
        set_value_fn_t< index_t > set_value_fn,
        get_index_field_const_ptr_fn_t get_const_begin_fn,
        get_index_field_const_ptr_fn_t get_const_end_fn,
        get_index_field_ptr_fn_t get_begin_fn,
        get_index_field_ptr_fn_t get_end_fn,
        set_values_to_value_fn_t< index_t > set_all_values_fn,
        set_values_fn_t< ptr_const_index_t > set_all_values_from_ptr,
        set_values_fn_t< typename std::vector<
            index_t >::const_iterator > set_all_values_from_iter,
        get_field_length_fn_t get_field_length_fn )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        SIXTRL_ASSERT( pset != nullptr );
        SIXTRL_ASSERT( get_field_length_fn != nullptr );
        num_elements_t const num_particles = get_field_length_fn( pset );

        SIXTRL_ASSERT( cmp_values.data() != nullptr );
        SIXTRL_ASSERT( cmp_values.size() >=
                       static_cast< std::size_t >( num_particles ) );

        SIXTRL_ASSERT( get_value_fn != nullptr );
        SIXTRL_ASSERT( set_value_fn != nullptr );
        SIXTRL_ASSERT( get_const_begin_fn != nullptr );
        SIXTRL_ASSERT( get_const_end_fn   != nullptr );
        SIXTRL_ASSERT( get_begin_fn != nullptr );
        SIXTRL_ASSERT( get_end_fn   != nullptr );
        SIXTRL_ASSERT( set_all_values_fn != nullptr );
        SIXTRL_ASSERT( set_all_values_from_ptr != nullptr );
        SIXTRL_ASSERT( set_all_values_from_iter != nullptr );

        ASSERT_TRUE( get_const_begin_fn( pset ) != nullptr );
        ASSERT_TRUE( get_const_begin_fn( pset ) != cmp_values.data() );
        ASSERT_TRUE( get_const_end_fn( pset ) != nullptr );
        ASSERT_TRUE( std::distance( get_const_begin_fn( pset ),
            get_const_end_fn( pset ) ) == static_cast< std::ptrdiff_t >(
                num_particles ) );

        ASSERT_TRUE( get_begin_fn( pset ) != nullptr );
        ASSERT_TRUE( get_end_fn( pset ) != nullptr );
        ASSERT_TRUE( std::distance( get_begin_fn( pset ), get_end_fn( pset ) )
                     == static_cast< std::ptrdiff_t >( num_particles ) );

        num_elements_t ii = num_elements_t{ 0 };

        for( ; ii < num_particles ; ++ii )
        {
            ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == set_value_fn(
                pset, ii, cmp_values[ ii ] ) );

            ASSERT_TRUE( get_value_fn( pset, ii ) == cmp_values[ ii ] );
        }

        index_t special_value = index_t{ 137 };

        ASSERT_TRUE( std::equal( get_const_begin_fn( pset ),
                        get_const_end_fn( pset ), cmp_values.begin() ) );

        ASSERT_TRUE( std::equal( get_begin_fn( pset ), get_end_fn( pset ),
                                 cmp_values.begin() ) );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == set_all_values_fn(
                        pset, special_value ) );

        auto cmp_value_with_special_value =
        [special_value]( index_t const& SIXTRL_RESTRICT_REF val ) -> bool
        {
            return ( val == special_value );
        };

        ASSERT_TRUE( std::all_of( get_const_begin_fn( pset ),
            get_const_end_fn( pset ), cmp_value_with_special_value ) );

        ASSERT_FALSE( std::equal( get_const_begin_fn( pset ),
                        get_const_end_fn( pset ), cmp_values.begin() ) );

        ASSERT_FALSE( std::equal( get_begin_fn( pset ), get_end_fn( pset ),
                                  cmp_values.begin() ) );

        for( ; ii < num_particles ; ++ii )
        {
            ASSERT_FALSE( cmp_value_with_special_value(
                get_value_fn( pset, ii ) ) );
        }

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == set_all_values_from_ptr(
            pset, cmp_values.data() ) );

        ASSERT_FALSE( std::all_of( get_const_begin_fn( pset ),
            get_const_end_fn( pset ), cmp_value_with_special_value ) );

        ASSERT_TRUE( std::equal( get_const_begin_fn( pset ),
            get_const_end_fn( pset ), cmp_values.begin() ) );

        ASSERT_TRUE( std::equal( get_begin_fn( pset ), get_end_fn( pset ),
                                 cmp_values.begin() ) );

        for( ; ii < num_particles ; ++ii )
        {
            ASSERT_TRUE( get_value_fn( pset, ii ) == cmp_values[ ii ] );
        }

        std::fill( get_begin_fn( pset ), get_end_fn( pset ), index_t{ 0 } );
        SIXTRL_ASSERT( !std::equal( get_const_begin_fn( pset ),
            get_const_end_fn( pset ), cmp_values.begin() ) );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
            set_all_values_from_iter( pset, cmp_values.cbegin() ) );

        ASSERT_TRUE( std::equal( get_const_begin_fn( pset ),
             get_const_end_fn( pset ), cmp_values.begin() ) );
    }

    /* --------------------------------------------------------------------- */

    void check_real_num_particles_length(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const
            SIXTRL_RESTRICT pset,
        get_real_field_const_ptr_fn_t get_const_begin_fn,
        get_real_field_const_ptr_fn_t get_const_end_fn,
        get_field_length_fn_t get_field_length_fn )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        SIXTRL_ASSERT( pset != nullptr );
        SIXTRL_ASSERT( get_const_begin_fn  != nullptr );
        SIXTRL_ASSERT( get_const_end_fn    != nullptr );
        SIXTRL_ASSERT( get_field_length_fn != nullptr );

        ASSERT_TRUE( st::ParticleSet_capacity( pset ) >= num_elements_t{ 0 } );
        ASSERT_TRUE( st::ParticleSet_capacity( pset ) >=
                     st::ParticleSet_num_particles( pset ) );

        ASSERT_TRUE( st::ParticleSet_num_particles( pset ) >=
                     get_field_length_fn( pset ) );
        ASSERT_TRUE( get_field_length_fn( pset ) >= num_elements_t{ 0 } );

        ASSERT_TRUE( get_const_begin_fn( pset ) != nullptr );
        ASSERT_TRUE( get_const_end_fn( pset )   != nullptr );

        ASSERT_TRUE( std::distance( get_const_begin_fn( pset ),
                                    get_const_end_fn( pset ) ) ==
                    static_cast< std::ptrdiff_t >(
                        get_field_length_fn( pset ) ) );
    }

    void check_index_num_particles_length(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const
            SIXTRL_RESTRICT pset,
        get_index_field_const_ptr_fn_t get_const_begin_fn,
        get_index_field_const_ptr_fn_t get_const_end_fn,
        get_field_length_fn_t get_field_length_fn )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        SIXTRL_ASSERT( pset != nullptr );
        SIXTRL_ASSERT( get_const_begin_fn  != nullptr );
        SIXTRL_ASSERT( get_const_end_fn    != nullptr );
        SIXTRL_ASSERT( get_field_length_fn != nullptr );

        ASSERT_TRUE( st::ParticleSet_capacity( pset ) >= num_elements_t{ 0 } );
        ASSERT_TRUE( st::ParticleSet_capacity( pset ) >=
                     st::ParticleSet_num_particles( pset ) );

        ASSERT_TRUE( st::ParticleSet_num_particles( pset ) >=
                     get_field_length_fn( pset ) );
        ASSERT_TRUE( get_field_length_fn( pset ) >= num_elements_t{ 0 } );

        ASSERT_TRUE( get_const_begin_fn( pset ) != nullptr );
        ASSERT_TRUE( get_const_end_fn( pset )   != nullptr );

        ASSERT_TRUE( std::distance( get_const_begin_fn( pset ),
                                    get_const_end_fn( pset ) ) ==
                    static_cast< std::ptrdiff_t >(
                        get_field_length_fn( pset ) ) );
    }
};


namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    template< class ParticleSetT >
    struct TestTraits
    {
        typedef typename SIXTRL_CXX_NAMESPACE::ParticleSetTraits<
            ParticleSetT >::real_t real_t;

        typedef typename SIXTRL_CXX_NAMESPACE::ParticleSetTraits<
            ParticleSetT >::index_t index_t;

        typedef boost::random::independent_bits_engine<
            boost::random::mt19937,
            SIXTRL_CXX_NAMESPACE::MultiPrecRealTraits< real_t >::num_digits,
            boost::multiprecision::cpp_int > prng_t;

        typedef real_t  dist_real_t;
        typedef index_t dist_index_t;

        typedef boost::random::uniform_int_distribution< index_t >
            index_uniform_dist_t;

        typedef boost::random::uniform_real_distribution< real_t >
            real_uniform_dist_t;

        typedef boost::random::normal_distribution< real_t >
            real_normal_dist_t;
    };

    template<>
    struct TestTraits< SIXTRL_CXX_NAMESPACE::SinglePrecParticleSet >
    {
        typedef typename SIXTRL_CXX_NAMESPACE::ParticleSetTraits<
            SIXTRL_CXX_NAMESPACE::SinglePrecParticleSet >::real_t real_t;

        typedef typename SIXTRL_CXX_NAMESPACE::ParticleSetTraits<
            SIXTRL_CXX_NAMESPACE::SinglePrecParticleSet >::index_t index_t;

        typedef float   dist_real_t;
        typedef index_t dist_index_t;

        typedef std::mt19937_64 prng_t;
        typedef std::uniform_int_distribution< index_t > index_uniform_dist_t;
        typedef std::uniform_real_distribution< float >  real_uniform_dist_t;
        typedef std::normal_distribution< float >        real_normal_dist_t;
    };


    using CXXParticleVecSetTypes = ::testing::Types<
        SIXTRL_CXX_NAMESPACE::SinglePrecParticleSet,
        SIXTRL_CXX_NAMESPACE::DoublePrecParticleSet,
        SIXTRL_CXX_NAMESPACE::ExtDoublePrecParticleSet,
        SIXTRL_CXX_NAMESPACE::QuadPrecParticleSet,
        SIXTRL_CXX_NAMESPACE::OctPrecParticleSet >;

} /* namespace tests */
} /* namespace SIXTRL_CXX_NAMESPACE */

TYPED_TEST_SUITE( CXXMultiprecParticlesParticleSet,
                  SIXTRL_CXX_NAMESPACE::tests::CXXParticleVecSetTypes );


TYPED_TEST( CXXMultiprecParticlesParticleSet, BasicUsage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    typedef TypeParam particle_set_t;
    typedef st::particle_num_elements_t num_elements_t;
    typedef typename st::ParticleSetTraits< particle_set_t >::real_t  real_t;
    typedef typename st::ParticleSetTraits< particle_set_t >::index_t index_t;

    typedef typename st::tests::TestTraits< particle_set_t >::prng_t   prng_t;

    typedef typename st::tests::TestTraits< particle_set_t
        >::real_uniform_dist_t real_uniform_dist_t;

    typedef typename st::tests::TestTraits< particle_set_t
        >::index_uniform_dist_t index_uniform_dist_t;

    typedef typename st::tests::TestTraits< particle_set_t
        >::dist_real_t dist_real_t;

    typedef typename st::tests::TestTraits< particle_set_t
        >::dist_index_t dist_index_t;

    const num_elements_t num_particles = num_elements_t{ 100 };

    particle_set_t pset;

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::ParticleSet_init( &pset, num_particles ) );

    ASSERT_TRUE( st::ParticleSet_num_particles( &pset ) == num_particles );
    ASSERT_TRUE( st::ParticleSet_capacity( &pset ) == num_particles );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_x_length< particle_set_t >,
        st::ParticleSet_const_x_begin, st::ParticleSet_const_x_end,
        st::ParticleSet_x_begin, st::ParticleSet_x_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_px_length< particle_set_t >,
        st::ParticleSet_const_px_begin, st::ParticleSet_const_px_end,
        st::ParticleSet_px_begin, st::ParticleSet_px_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_y_length< particle_set_t >,
        st::ParticleSet_const_y_begin, st::ParticleSet_const_y_end,
        st::ParticleSet_y_begin, st::ParticleSet_y_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_py_length< particle_set_t >,
        st::ParticleSet_const_py_begin, st::ParticleSet_const_py_end,
        st::ParticleSet_py_begin, st::ParticleSet_py_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_zeta_length< particle_set_t >,
        st::ParticleSet_const_zeta_begin, st::ParticleSet_const_zeta_end,
        st::ParticleSet_zeta_begin, st::ParticleSet_zeta_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_delta_length< particle_set_t >,
        st::ParticleSet_const_delta_begin, st::ParticleSet_const_delta_end,
        st::ParticleSet_delta_begin, st::ParticleSet_delta_end );

    this->check_index_field_ptrs( &pset,
        st::ParticleSet_state_length< particle_set_t >,
        st::ParticleSet_const_state_begin, st::ParticleSet_const_state_end,
        st::ParticleSet_state_begin, st::ParticleSet_state_end );

    this->check_index_field_ptrs( &pset,
        st::ParticleSet_at_element_length< particle_set_t >,
        st::ParticleSet_const_at_element_begin,
        st::ParticleSet_const_at_element_end,
        st::ParticleSet_at_element_begin, st::ParticleSet_at_element_end );

    this->check_index_field_ptrs( &pset,
        st::ParticleSet_at_turn_length< particle_set_t >,
        st::ParticleSet_const_at_turn_begin, st::ParticleSet_const_at_turn_end,
        st::ParticleSet_at_turn_begin, st::ParticleSet_at_turn_end );

    this->check_index_field_ptrs( &pset,
        st::ParticleSet_particle_id_length< particle_set_t >,
        st::ParticleSet_const_particle_id_begin,
        st::ParticleSet_const_particle_id_end,
        st::ParticleSet_particle_id_begin, st::ParticleSet_particle_id_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_psigma_length< particle_set_t >,
        st::ParticleSet_const_psigma_begin, st::ParticleSet_const_psigma_end,
        st::ParticleSet_psigma_begin, st::ParticleSet_psigma_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_rpp_length< particle_set_t >,
        st::ParticleSet_const_rpp_begin, st::ParticleSet_const_rpp_end,
        st::ParticleSet_rpp_begin, st::ParticleSet_rpp_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_rvv_length< particle_set_t >,
        st::ParticleSet_const_rvv_begin, st::ParticleSet_const_rvv_end,
        st::ParticleSet_rvv_begin, st::ParticleSet_rvv_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_chi_length< particle_set_t >,
        st::ParticleSet_const_chi_begin, st::ParticleSet_const_chi_end,
        st::ParticleSet_chi_begin, st::ParticleSet_chi_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_charge_ratio_length< particle_set_t >,
        st::ParticleSet_const_charge_ratio_begin,
        st::ParticleSet_const_charge_ratio_end,
        st::ParticleSet_charge_ratio_begin, st::ParticleSet_charge_ratio_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_charge0_length< particle_set_t >,
        st::ParticleSet_const_charge0_begin, st::ParticleSet_const_charge0_end,
        st::ParticleSet_charge0_begin, st::ParticleSet_charge0_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_mass0_length< particle_set_t >,
        st::ParticleSet_const_mass0_begin, st::ParticleSet_const_mass0_end,
        st::ParticleSet_mass0_begin, st::ParticleSet_mass0_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_beta0_length< particle_set_t >,
        st::ParticleSet_const_beta0_begin, st::ParticleSet_const_beta0_end,
        st::ParticleSet_beta0_begin, st::ParticleSet_beta0_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_gamma0_length< particle_set_t >,
        st::ParticleSet_const_gamma0_begin, st::ParticleSet_const_gamma0_end,
        st::ParticleSet_gamma0_begin, st::ParticleSet_gamma0_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_pc0_length< particle_set_t >,
        st::ParticleSet_const_pc0_begin, st::ParticleSet_const_pc0_end,
        st::ParticleSet_pc0_begin, st::ParticleSet_pc0_end );

    this->check_real_field_ptrs( &pset,
        st::ParticleSet_s_length< particle_set_t >,
        st::ParticleSet_const_s_begin, st::ParticleSet_const_s_end,
        st::ParticleSet_s_begin, st::ParticleSet_s_end );

    /* --------------------------------------------------------------------- */

    num_elements_t const MAX_NUM_PARTICLES = num_particles;
    prng_t prng( 20200428 );

    real_uniform_dist_t real_dist( std::numeric_limits< dist_real_t >::epsilon(),
        dist_real_t{ 1 } - std::numeric_limits< dist_real_t >::epsilon() );

    index_uniform_dist_t index_dist( dist_index_t{ 0 }, dist_index_t{ 1 } );

    auto gen_real_data = [&prng, &real_dist]() -> dist_real_t
         { return real_dist( prng ); };

    auto gen_index_data = [&prng, &index_dist]() -> dist_index_t
         { return index_dist( prng ); };

    std::vector< real_t > cmp_x_values( MAX_NUM_PARTICLES );
    std::generate( cmp_x_values.begin(), cmp_x_values.end(), gen_real_data );

    std::vector< real_t > cmp_px_values( MAX_NUM_PARTICLES );
    std::generate( cmp_px_values.begin(), cmp_px_values.end(), gen_real_data );

    std::vector< real_t > cmp_y_values( MAX_NUM_PARTICLES );
    std::generate( cmp_y_values.begin(), cmp_y_values.end(), gen_real_data );

    std::vector< real_t > cmp_py_values( MAX_NUM_PARTICLES );
    std::generate( cmp_py_values.begin(), cmp_py_values.end(), gen_real_data );

    std::vector< real_t > cmp_zeta_values( MAX_NUM_PARTICLES );
    std::generate( cmp_zeta_values.begin(), cmp_zeta_values.end(),
                   gen_real_data );

    std::vector< real_t > cmp_delta_values( MAX_NUM_PARTICLES );
    std::generate( cmp_delta_values.begin(), cmp_delta_values.end(),
                   gen_real_data );

    std::vector< index_t > cmp_state_values( MAX_NUM_PARTICLES );
    std::generate( cmp_state_values.begin(), cmp_state_values.end(),
                   gen_index_data );

    std::vector< index_t > cmp_at_element_values( MAX_NUM_PARTICLES );
    std::generate( cmp_at_element_values.begin(), cmp_at_element_values.end(),
                   gen_index_data );

    std::vector< index_t > cmp_at_turn_values( MAX_NUM_PARTICLES );
    std::generate( cmp_at_turn_values.begin(), cmp_at_turn_values.end(),
                   gen_index_data );

    std::vector< index_t > cmp_particle_id_values( MAX_NUM_PARTICLES );
    std::generate( cmp_particle_id_values.begin(), cmp_particle_id_values.end(),
                   gen_index_data );

    std::vector< real_t > cmp_psigma_values( MAX_NUM_PARTICLES );
    std::generate( cmp_psigma_values.begin(), cmp_psigma_values.end(),
                   gen_real_data );

    std::vector< real_t > cmp_rpp_values( MAX_NUM_PARTICLES );
    std::generate( cmp_rpp_values.begin(), cmp_rpp_values.end(),
                   gen_real_data );

    std::vector< real_t > cmp_rvv_values( MAX_NUM_PARTICLES );
    std::generate( cmp_rvv_values.begin(), cmp_rvv_values.end(),
                   gen_real_data );

    std::vector< real_t > cmp_chi_values( MAX_NUM_PARTICLES );
    std::generate( cmp_chi_values.begin(), cmp_chi_values.end(),
                   gen_real_data );

    std::vector< real_t > cmp_charge_ratio_values( MAX_NUM_PARTICLES );
    std::generate( cmp_charge_ratio_values.begin(),
                   cmp_charge_ratio_values.end(), gen_real_data );

    std::vector< real_t > cmp_charge0_values( MAX_NUM_PARTICLES );
    std::generate( cmp_charge0_values.begin(), cmp_charge0_values.end(),
                   gen_real_data );

    std::vector< real_t > cmp_mass0_values( MAX_NUM_PARTICLES );
    std::generate( cmp_mass0_values.begin(), cmp_mass0_values.end(),
                   gen_real_data );

    std::vector< real_t > cmp_beta0_values( MAX_NUM_PARTICLES );
    std::generate( cmp_beta0_values.begin(), cmp_beta0_values.end(),
                   gen_real_data );

    std::vector< real_t > cmp_gamma0_values( MAX_NUM_PARTICLES );
    std::generate( cmp_gamma0_values.begin(), cmp_gamma0_values.end(),
                   gen_real_data );

    std::vector< real_t > cmp_pc0_values( MAX_NUM_PARTICLES );
    std::generate( cmp_pc0_values.begin(), cmp_pc0_values.end(),
                   gen_real_data );

    std::vector< real_t > cmp_s_values( MAX_NUM_PARTICLES );
    std::generate( cmp_s_values.begin(), cmp_s_values.end(), gen_real_data );

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    this->check_set_and_get_real_values( &pset, cmp_x_values, st::ParticleSet_x,
        st::ParticleSet_set_x_value< particle_set_t, real_t >,
        st::ParticleSet_const_x_begin< particle_set_t >,
        st::ParticleSet_const_x_end< particle_set_t >,
        st::ParticleSet_x_begin< particle_set_t >,
        st::ParticleSet_x_end< particle_set_t >,
        st::ParticleSet_set_all_x_values< particle_set_t, real_t >,
        st::ParticleSet_set_x< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_x< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_x_length< particle_set_t > );

    this->check_set_and_get_real_values( &pset, cmp_px_values,
        st::ParticleSet_px,
        st::ParticleSet_set_px_value< particle_set_t, real_t >,
        st::ParticleSet_const_px_begin, st::ParticleSet_const_px_end,
        st::ParticleSet_px_begin, st::ParticleSet_px_end,
        st::ParticleSet_set_all_px_values< particle_set_t, real_t >,
        st::ParticleSet_set_px< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_px< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_px_length );

    this->check_set_and_get_real_values( &pset, cmp_y_values,
        st::ParticleSet_y,
        st::ParticleSet_set_y_value< particle_set_t, real_t >,
        st::ParticleSet_const_y_begin, st::ParticleSet_const_y_end,
        st::ParticleSet_y_begin, st::ParticleSet_y_end,
        st::ParticleSet_set_all_y_values< particle_set_t, real_t >,
        st::ParticleSet_set_y< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_y< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_y_length );

    this->check_set_and_get_real_values( &pset, cmp_py_values,
        st::ParticleSet_py,
        st::ParticleSet_set_py_value< particle_set_t, real_t >,
        st::ParticleSet_const_py_begin, st::ParticleSet_const_py_end,
        st::ParticleSet_py_begin, st::ParticleSet_py_end,
        st::ParticleSet_set_all_py_values< particle_set_t, real_t >,
        st::ParticleSet_set_py< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_py< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_py_length );

    this->check_set_and_get_real_values( &pset, cmp_zeta_values,
        st::ParticleSet_zeta,
        st::ParticleSet_set_zeta_value< particle_set_t, real_t >,
        st::ParticleSet_const_zeta_begin, st::ParticleSet_const_zeta_end,
        st::ParticleSet_zeta_begin, st::ParticleSet_zeta_end,
        st::ParticleSet_set_all_zeta_values< particle_set_t, real_t >,
        st::ParticleSet_set_zeta< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_zeta< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_zeta_length );

    this->check_set_and_get_real_values( &pset, cmp_delta_values,
        st::ParticleSet_delta,
        st::ParticleSet_set_delta_value< particle_set_t, real_t >,
        st::ParticleSet_const_delta_begin, st::ParticleSet_const_delta_end,
        st::ParticleSet_delta_begin, st::ParticleSet_delta_end,
        st::ParticleSet_set_all_delta_values< particle_set_t, real_t >,
        st::ParticleSet_set_delta< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_delta< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_delta_length );

    this->check_set_and_get_index_values( &pset, cmp_state_values,
        st::ParticleSet_state,
        st::ParticleSet_set_state_value< particle_set_t, index_t >,
        st::ParticleSet_const_state_begin, st::ParticleSet_const_state_end,
        st::ParticleSet_state_begin, st::ParticleSet_state_end,
        st::ParticleSet_set_all_state_values< particle_set_t, index_t >,
        st::ParticleSet_set_state< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC index_t const* >,
        st::ParticleSet_set_state< particle_set_t,
            typename std::vector< index_t >::const_iterator >,
        st::ParticleSet_state_length );

    this->check_set_and_get_index_values( &pset, cmp_at_element_values,
        st::ParticleSet_at_element,
        st::ParticleSet_set_at_element_value< particle_set_t, index_t >,
        st::ParticleSet_const_at_element_begin,
        st::ParticleSet_const_at_element_end,
        st::ParticleSet_at_element_begin, st::ParticleSet_at_element_end,
        st::ParticleSet_set_all_at_element_values< particle_set_t, index_t >,
        st::ParticleSet_set_at_element< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC index_t const* >,
        st::ParticleSet_set_at_element< particle_set_t,
            typename std::vector< index_t >::const_iterator >,
        st::ParticleSet_at_element_length );

    this->check_set_and_get_index_values( &pset, cmp_at_turn_values,
        st::ParticleSet_at_turn,
        st::ParticleSet_set_at_turn_value< particle_set_t, index_t >,
        st::ParticleSet_const_at_turn_begin, st::ParticleSet_const_at_turn_end,
        st::ParticleSet_at_turn_begin, st::ParticleSet_at_turn_end,
        st::ParticleSet_set_all_at_turn_values< particle_set_t, index_t >,
        st::ParticleSet_set_at_turn< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC index_t const* >,
        st::ParticleSet_set_at_turn< particle_set_t,
            typename std::vector< index_t >::const_iterator >,
        st::ParticleSet_at_turn_length );

    this->check_set_and_get_index_values( &pset, cmp_particle_id_values,
        st::ParticleSet_particle_id,
        st::ParticleSet_set_particle_id_value< particle_set_t, index_t >,
        st::ParticleSet_const_particle_id_begin,
        st::ParticleSet_const_particle_id_end,
        st::ParticleSet_particle_id_begin, st::ParticleSet_particle_id_end,
        st::ParticleSet_set_all_particle_id_values< particle_set_t, index_t >,
        st::ParticleSet_set_particle_id< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC index_t const* >,
        st::ParticleSet_set_particle_id< particle_set_t,
            typename std::vector< index_t >::const_iterator >,
        st::ParticleSet_particle_id_length );

    this->check_set_and_get_real_values( &pset, cmp_psigma_values,
        st::ParticleSet_psigma,
        st::ParticleSet_set_psigma_value< particle_set_t, real_t >,
        st::ParticleSet_const_psigma_begin, st::ParticleSet_const_psigma_end,
        st::ParticleSet_psigma_begin, st::ParticleSet_psigma_end,
        st::ParticleSet_set_all_psigma_values< particle_set_t, real_t >,
        st::ParticleSet_set_psigma< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_psigma< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_psigma_length );

    this->check_set_and_get_real_values( &pset, cmp_rpp_values,
        st::ParticleSet_rpp,
        st::ParticleSet_set_rpp_value< particle_set_t, real_t >,
        st::ParticleSet_const_rpp_begin, st::ParticleSet_const_rpp_end,
        st::ParticleSet_rpp_begin, st::ParticleSet_rpp_end,
        st::ParticleSet_set_all_rpp_values< particle_set_t, real_t >,
        st::ParticleSet_set_rpp< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_rpp< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_rpp_length );

    this->check_set_and_get_real_values( &pset, cmp_rvv_values,
        st::ParticleSet_rvv,
        st::ParticleSet_set_rvv_value< particle_set_t, real_t >,
        st::ParticleSet_const_rvv_begin, st::ParticleSet_const_rvv_end,
        st::ParticleSet_rvv_begin, st::ParticleSet_rvv_end,
        st::ParticleSet_set_all_rvv_values< particle_set_t, real_t >,
        st::ParticleSet_set_rvv< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_rvv< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_rvv_length );

    this->check_set_and_get_real_values( &pset, cmp_chi_values,
        st::ParticleSet_chi,
        st::ParticleSet_set_chi_value< particle_set_t, real_t >,
        st::ParticleSet_const_chi_begin, st::ParticleSet_const_chi_end,
        st::ParticleSet_chi_begin, st::ParticleSet_chi_end,
        st::ParticleSet_set_all_chi_values< particle_set_t, real_t >,
        st::ParticleSet_set_chi< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_chi< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_chi_length );

    this->check_set_and_get_real_values( &pset, cmp_charge_ratio_values,
        st::ParticleSet_charge_ratio,
        st::ParticleSet_set_charge_ratio_value< particle_set_t, real_t >,
        st::ParticleSet_const_charge_ratio_begin,
        st::ParticleSet_const_charge_ratio_end,
        st::ParticleSet_charge_ratio_begin, st::ParticleSet_charge_ratio_end,
        st::ParticleSet_set_all_charge_ratio_values< particle_set_t, real_t >,
        st::ParticleSet_set_charge_ratio< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_charge_ratio< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_charge_ratio_length );

    this->check_set_and_get_real_values( &pset, cmp_charge0_values,
        st::ParticleSet_charge0,
        st::ParticleSet_set_charge0_value< particle_set_t, real_t >,
        st::ParticleSet_const_charge0_begin, st::ParticleSet_const_charge0_end,
        st::ParticleSet_charge0_begin, st::ParticleSet_charge0_end,
        st::ParticleSet_set_all_charge0_values< particle_set_t, real_t >,
        st::ParticleSet_set_charge0< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_charge0< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_charge0_length );

    this->check_set_and_get_real_values( &pset, cmp_mass0_values,
        st::ParticleSet_mass0,
        st::ParticleSet_set_mass0_value< particle_set_t, real_t >,
        st::ParticleSet_const_mass0_begin, st::ParticleSet_const_mass0_end,
        st::ParticleSet_mass0_begin, st::ParticleSet_mass0_end,
        st::ParticleSet_set_all_mass0_values< particle_set_t, real_t >,
        st::ParticleSet_set_mass0< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_mass0< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_mass0_length );

    this->check_set_and_get_real_values( &pset, cmp_beta0_values,
        st::ParticleSet_beta0,
        st::ParticleSet_set_beta0_value< particle_set_t, real_t >,
        st::ParticleSet_const_beta0_begin, st::ParticleSet_const_beta0_end,
        st::ParticleSet_beta0_begin, st::ParticleSet_beta0_end,
        st::ParticleSet_set_all_beta0_values< particle_set_t, real_t >,
        st::ParticleSet_set_beta0< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_beta0< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_beta0_length );

    this->check_set_and_get_real_values( &pset, cmp_gamma0_values,
        st::ParticleSet_gamma0,
        st::ParticleSet_set_gamma0_value< particle_set_t, real_t >,
        st::ParticleSet_const_gamma0_begin, st::ParticleSet_const_gamma0_end,
        st::ParticleSet_gamma0_begin, st::ParticleSet_gamma0_end,
        st::ParticleSet_set_all_gamma0_values< particle_set_t, real_t >,
        st::ParticleSet_set_gamma0< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_gamma0< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_gamma0_length );

    this->check_set_and_get_real_values( &pset, cmp_pc0_values,
        st::ParticleSet_pc0,
        st::ParticleSet_set_pc0_value< particle_set_t, real_t >,
        st::ParticleSet_const_pc0_begin, st::ParticleSet_const_pc0_end,
        st::ParticleSet_pc0_begin, st::ParticleSet_pc0_end,
        st::ParticleSet_set_all_pc0_values< particle_set_t, real_t >,
        st::ParticleSet_set_pc0< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_pc0< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_pc0_length );

    this->check_set_and_get_real_values( &pset, cmp_s_values,
        st::ParticleSet_s,
        st::ParticleSet_set_s_value< particle_set_t, real_t >,
        st::ParticleSet_const_s_begin, st::ParticleSet_const_s_end,
        st::ParticleSet_s_begin, st::ParticleSet_s_end,
        st::ParticleSet_set_all_s_values< particle_set_t, real_t >,
        st::ParticleSet_set_s< particle_set_t,
            SIXTRL_PARTICLE_SET_DATAPTR_DEC real_t const* >,
        st::ParticleSet_set_s< particle_set_t,
            typename std::vector< real_t >::const_iterator >,
        st::ParticleSet_s_length );

    /* --------------------------------------------------------------------- */

    ASSERT_TRUE( std::equal( st::ParticleSet_const_x_begin( &pset ),
         st::ParticleSet_const_x_end( &pset ), cmp_x_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_x_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_px_begin( &pset ),
         st::ParticleSet_const_px_end( &pset ), cmp_px_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_px_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_y_begin( &pset ),
         st::ParticleSet_const_y_end( &pset ), cmp_y_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_y_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_py_begin( &pset ),
         st::ParticleSet_const_py_end( &pset ), cmp_py_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_py_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_zeta_begin( &pset ),
         st::ParticleSet_const_zeta_end( &pset ), cmp_zeta_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_zeta_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_delta_begin( &pset ),
         st::ParticleSet_const_delta_end( &pset ), cmp_delta_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_delta_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_state_begin( &pset ),
         st::ParticleSet_const_state_end( &pset ), cmp_state_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_state_values( &pset, index_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_at_element_begin( &pset ),
         st::ParticleSet_const_at_element_end( &pset ),
         cmp_at_element_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_at_element_values( &pset, index_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_at_turn_begin( &pset ),
        st::ParticleSet_const_at_turn_end( &pset ),
        cmp_at_turn_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_at_turn_values( &pset, index_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_particle_id_begin( &pset ),
        st::ParticleSet_const_particle_id_end( &pset ),
        cmp_particle_id_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_particle_id_values( &pset, index_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_psigma_begin( &pset ),
         st::ParticleSet_const_psigma_end( &pset ),
         cmp_psigma_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_psigma_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_rpp_begin( &pset ),
         st::ParticleSet_const_rpp_end( &pset ), cmp_rpp_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_rpp_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_rvv_begin( &pset ),
         st::ParticleSet_const_rvv_end( &pset ), cmp_rvv_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_rvv_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_chi_begin( &pset ),
         st::ParticleSet_const_chi_end( &pset ), cmp_chi_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_chi_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_charge_ratio_begin( &pset ),
         st::ParticleSet_const_charge_ratio_end( &pset ),
         cmp_charge_ratio_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_charge_ratio_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_charge0_begin( &pset ),
         st::ParticleSet_const_charge0_end( &pset ),
         cmp_charge0_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_charge0_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_mass0_begin( &pset ),
         st::ParticleSet_const_mass0_end( &pset ), cmp_mass0_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_mass0_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_beta0_begin( &pset ),
         st::ParticleSet_const_beta0_end( &pset ), cmp_beta0_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_beta0_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_gamma0_begin( &pset ),
         st::ParticleSet_const_gamma0_end( &pset ),
                                 cmp_gamma0_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_gamma0_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_pc0_begin( &pset ),
         st::ParticleSet_const_pc0_end( &pset ), cmp_pc0_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_pc0_values( &pset, real_t{ 0 } ) );

    ASSERT_TRUE( std::equal( st::ParticleSet_const_s_begin( &pset ),
         st::ParticleSet_const_s_end( &pset ), cmp_s_values.begin() ) );
    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS  ==
        st::ParticleSet_set_all_s_values( &pset, real_t{ 0 } ) );

    /* ===================================================================== */

    num_elements_t const reduced_num_particles = num_particles >> 1u;

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
        st::ParticleSet_set_num_particles( &pset, reduced_num_particles ) );

    ASSERT_TRUE( st::ParticleSet_num_particles(
        &pset ) == reduced_num_particles );

    ASSERT_TRUE( st::ParticleSet_capacity( &pset ) == num_particles );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_x_begin, st::ParticleSet_const_x_end,
        st::ParticleSet_x_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_px_begin, st::ParticleSet_const_px_end,
        st::ParticleSet_px_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_y_begin, st::ParticleSet_const_y_end,
        st::ParticleSet_y_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_py_begin, st::ParticleSet_const_py_end,
        st::ParticleSet_py_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_zeta_begin, st::ParticleSet_const_zeta_end,
        st::ParticleSet_zeta_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_delta_begin, st::ParticleSet_const_delta_end,
        st::ParticleSet_delta_length );

    this->check_index_num_particles_length( &pset,
        st::ParticleSet_const_state_begin, st::ParticleSet_const_state_end,
        st::ParticleSet_state_length );

    this->check_index_num_particles_length( &pset,
        st::ParticleSet_const_at_element_begin,
        st::ParticleSet_const_at_element_end,
        st::ParticleSet_at_element_length );

    this->check_index_num_particles_length( &pset,
        st::ParticleSet_const_at_turn_begin, st::ParticleSet_const_at_turn_end,
        st::ParticleSet_at_turn_length );

    this->check_index_num_particles_length( &pset,
        st::ParticleSet_const_particle_id_begin,
        st::ParticleSet_const_particle_id_end,
        st::ParticleSet_particle_id_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_psigma_begin, st::ParticleSet_const_psigma_end,
        st::ParticleSet_psigma_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_rpp_begin, st::ParticleSet_const_rpp_end,
        st::ParticleSet_rpp_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_rvv_begin, st::ParticleSet_const_rvv_end,
        st::ParticleSet_rvv_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_chi_begin, st::ParticleSet_const_chi_end,
        st::ParticleSet_chi_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_charge_ratio_begin,
        st::ParticleSet_const_charge_ratio_end,
        st::ParticleSet_charge_ratio_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_charge0_begin, st::ParticleSet_const_charge0_end,
        st::ParticleSet_charge0_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_mass0_begin, st::ParticleSet_const_mass0_end,
        st::ParticleSet_mass0_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_beta0_begin, st::ParticleSet_const_beta0_end,
        st::ParticleSet_beta0_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_gamma0_begin, st::ParticleSet_const_gamma0_end,
        st::ParticleSet_gamma0_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_pc0_begin, st::ParticleSet_const_pc0_end,
        st::ParticleSet_pc0_length );

    this->check_real_num_particles_length( &pset,
        st::ParticleSet_const_s_begin, st::ParticleSet_const_s_end,
        st::ParticleSet_s_length );
}


TYPED_TEST( CXXMultiprecParticlesParticleSet, ParticleSetToParticle )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    typedef TypeParam particle_set_t;
    typedef typename st::ParticleSetTraits< particle_set_t >::real_t real_t;
    typedef typename st::ParticleSetTraits< particle_set_t >::index_t index_t;
    typedef st::particle_num_elements_t num_elements_t;
    typedef st::TParticle< real_t, index_t > particle_t;

    typedef typename st::tests::TestTraits< particle_set_t >::prng_t   prng_t;

    typedef typename st::tests::TestTraits< particle_set_t
        >::real_uniform_dist_t real_uniform_dist_t;

    typedef typename st::tests::TestTraits< particle_set_t
        >::index_uniform_dist_t index_uniform_dist_t;

    typedef typename st::tests::TestTraits< particle_set_t
        >::real_normal_dist_t   real_normal_dist_t;

    typedef typename st::tests::TestTraits< particle_set_t
        >::dist_real_t dist_real_t;

    typedef typename st::tests::TestTraits< particle_set_t
        >::dist_index_t dist_index_t;

    ASSERT_TRUE( st::Particle_is_type< particle_t >() );
    ASSERT_TRUE( st::Particle_num_particles< particle_t >() == 1u );

    prng_t prng( 20200428 );

    real_uniform_dist_t charge0_dist( dist_real_t{ 1 }, dist_real_t{ 10 } );
    real_uniform_dist_t mass0_dist( dist_real_t{ 1 }, dist_real_t{ 238 } );
    real_uniform_dist_t beta0_dist(
        std::numeric_limits< dist_real_t >::epsilon(),
        dist_real_t{ 1 } - std::numeric_limits< dist_real_t >::epsilon() );

    real_normal_dist_t xy_dist( dist_real_t{ 0 }, dist_real_t{ 1e-3 } );
    real_normal_dist_t pxpy_dist( dist_real_t{ 0 }, dist_real_t{ 1e-3 } );
    real_normal_dist_t zeta_dist( dist_real_t{ 0 }, dist_real_t{ 1e-4 } );
    real_normal_dist_t delta_dist( dist_real_t{ 0 }, dist_real_t{ 1e-5 } );

    real_uniform_dist_t chi_dist( dist_real_t{ 1 }, dist_real_t{ 1.2 } );
    real_uniform_dist_t s_dist( dist_real_t{ 0 }, dist_real_t{ 1 } );
    real_uniform_dist_t charge_ratio_dist(
        dist_real_t{ 1 }, dist_real_t{ 20 } );

    index_uniform_dist_t state_dist( dist_index_t{ 0 }, dist_index_t{ 1 } );

    index_uniform_dist_t at_turn_dist(
        dist_index_t{ 0 }, dist_index_t{ 10000000 } );

    index_uniform_dist_t at_element_dist(
        dist_index_t{ 0 }, dist_index_t{ 100000 } );

    num_elements_t const num_particles = num_elements_t{ 100 };
    std::vector< particle_t > particles;
    particles.reserve( num_particles );

    std::vector< particle_t > cmp_particles;
    cmp_particles.reserve( num_particles );

    for( num_elements_t ii = 0u ; ii < num_particles ; ++ii )
    {
        cmp_particles.push_back( particle_t{} );
        particles.push_back( particle_t{} );

        st::Particle_preset( &particles.back() );
        auto p = st::Particle_preset( &cmp_particles.back() );

        SIXTRL_ASSERT( p != nullptr );
        SIXTRL_ASSERT( st::ARCH_STATUS_SUCCESS ==
            st::Particle_init_charge0_mass0_beta0( p, charge0_dist( prng ),
                mass0_dist( prng ) * st::PhysConst_mass_atomic_ev<
                    dist_real_t >(), beta0_dist( prng ) ) );

        SIXTRL_ASSERT( st::Particle_set_id(
            p, ii ) == st::ARCH_STATUS_SUCCESS );

        SIXTRL_ASSERT( st::Particle_set_x(
            p, xy_dist( prng ) ) == st::ARCH_STATUS_SUCCESS );

        SIXTRL_ASSERT( st::Particle_set_px(
            p, pxpy_dist( prng ) ) == st::ARCH_STATUS_SUCCESS );

        SIXTRL_ASSERT( st::Particle_set_y(
            p, xy_dist( prng ) ) == st::ARCH_STATUS_SUCCESS );

        SIXTRL_ASSERT( st::Particle_set_py(
            p, pxpy_dist( prng ) ) == st::ARCH_STATUS_SUCCESS );

        SIXTRL_ASSERT( st::Particle_set_chi(
            p, chi_dist( prng ) ) == st::ARCH_STATUS_SUCCESS );

        SIXTRL_ASSERT( st::Particle_set_charge_ratio(
            p, charge_ratio_dist( prng ) == st::ARCH_STATUS_SUCCESS ) );

        SIXTRL_ASSERT( st::Particle_update_zeta(
            p, zeta_dist( prng ) ) == st::ARCH_STATUS_SUCCESS );

        SIXTRL_ASSERT( st::Particle_update_delta(
            p, delta_dist( prng ) ) == st::ARCH_STATUS_SUCCESS );

        SIXTRL_ASSERT( st::Particle_set_s(
            p, s_dist( prng ) ) == st::ARCH_STATUS_SUCCESS );

        SIXTRL_ASSERT( st::Particle_set_state(
            p, state_dist( prng ) ) == st::ARCH_STATUS_SUCCESS );

        SIXTRL_ASSERT( st::Particle_set_at_element(
            p, at_element_dist( prng ) ) == st::ARCH_STATUS_SUCCESS );

        SIXTRL_ASSERT( st::Particle_set_at_turn(
            p, at_turn_dist( prng ) ) == st::ARCH_STATUS_SUCCESS );

        ( void )p;
    }

    particle_set_t pset;

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS == st::ParticleSet_init(
        &pset, num_particles ) );

    ASSERT_TRUE( st::ParticleSet_num_particles( &pset ) == num_particles );

    for( num_elements_t ii = 0u ; ii < num_particles ; ++ii )
    {
        particle_t const* in_p = &cmp_particles[ ii ];
        particle_t* out_p = &particles[ ii ];

        SIXTRL_ASSERT( in_p  != nullptr );
        SIXTRL_ASSERT( out_p != nullptr );
        SIXTRL_ASSERT( in_p  != out_p );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
            st::ParticleSet_load_from_particle( &pset, in_p, ii ) );

        ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
            st::ParticleSet_store_to_particle( &pset, out_p, ii ) );

        ASSERT_TRUE( st::Particle_compare( out_p, in_p ) == 0 );
    }
}

