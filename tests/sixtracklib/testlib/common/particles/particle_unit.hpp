#ifndef SIXTRACKLIB_TESTLIB_COMMON_PARTICLES_PARTICLE_UNIT_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_PARTICLES_PARTICLE_UNIT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particle.hpp"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/cbuffer.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/physics_constants.h"
    #include "sixtracklib/common/internal/type_random_traits.hpp"
    #include "sixtracklib/testlib/common/objs/objs_traits.hpp"
    #include "sixtracklib/testlib/common/cobjects/cobj_elem_traits.hpp"
    #include "sixtracklib/testlib/common/cobjects/cobjects_initialiser_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    template< class ParticleUnitT >
    class ParticleUnitInitialiser : public CObjElemInitialiserBase
    {
        public:

        static_assert( SIXTRL_CXX_NAMESPACE::Particle_is_type<
            ParticleUnitT >(), "Requires ParticleUnitT to be multipole class" );

        typedef typename SIXTRL_CXX_NAMESPACE::ParticleTraits<
            ParticleUnitT >::real_t real_t;

        typedef typename SIXTRL_CXX_NAMESPACE::ParticleTraits<
            ParticleUnitT >::index_t index_t;

        private:

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< real_t >
                real_random_traits_t;

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< index_t >
                index_random_traits_t;

        static_assert( real_random_traits_t::has_uniform_dist,
            "Requires a uniform distribution for the real_t" );

        static_assert( real_random_traits_t::has_normal_dist,
            "Requires a normal distribution for the real_t" );

        public:

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         real_t >::const_argument_type const_real_arg_t;

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         index_t >::const_argument_type const_index_arg_t;

        typedef typename real_random_traits_t::uniform_dist_t
                         real_uniform_dist_t;

        typedef typename real_random_traits_t::normal_dist_t
                         real_normal_dist_t;

        typedef typename real_random_traits_t::default_prng_t  real_prng_t;
        typedef typename real_random_traits_t::default_prng_seed_t
                         real_prng_seed_t;

        typedef typename index_random_traits_t::uniform_dist_t  index_dist_t;
        typedef typename index_random_traits_t::default_prng_t  index_prng_t;
        typedef typename index_random_traits_t::default_prng_seed_t
                         index_prng_seed_t;

        typedef SIXTRL_CXX_NAMESPACE::CBufferView cbuffer_view_t;
        typedef SIXTRL_CXX_NAMESPACE::CBuffer cbuffer_t;

        SIXTRL_HOST_FN ParticleUnitInitialiser() :
            m_real_prng( real_prng_seed_t{ 202005200 } ),
            m_index_prng( index_prng_seed_t{ 202005201 } ),
            m_coord_dist( real_t{ -1e-5 }, real_t{ +1e-5 } ),
            m_momenta_dist( real_t{ -1e-5 }, real_t{ +1e-5 } ),
            m_unit_ratio_dist( real_t{ 1e-8 }, real_t{ 1 } ),
            m_charge0_dist( real_t{ 1 }, real_t{ 20 } ),
            m_mass0_dist( real_t{ 1 }, real_t{ 238 } ),
            m_s_dist( real_t{ 0 }, real_t{ 100 } ),
            m_at_elem_dist( index_t{ 0 }, index_t{ 1024 } ),
            m_at_turn_dist( index_t{ 0 }, index_t{ 1024 } ),
            m_id_dist( index_t{ 0 }, index_t{ 10240 } ),
            m_state_dist( index_t{ 0 }, index_t{ 1 } )
        {

        }

        SIXTRL_HOST_FN explicit ParticleUnitInitialiser(
            const_real_arg_t  min_coord, const_real_arg_t  max_coord,
            const_real_arg_t  min_momenta, const_real_arg_t  max_momenta,
            const_real_arg_t  min_unit_ratio, const_real_arg_t  max_unit_ratio,
            const_index_arg_t min_at_elem, const_index_arg_t max_at_elem,
            const_index_arg_t min_at_turn, const_index_arg_t max_at_turn,
            const_index_arg_t min_id, const_index_arg_t max_id,
            const_real_arg_t  min_charge0, const_real_arg_t  max_charge0,
            const_real_arg_t  min_mass0, const_real_arg_t  max_mass0,
            const_real_arg_t  min_s, const_real_arg_t  max_s ) :
            m_real_prng( real_prng_seed_t{ 202005200 } ),
            m_index_prng( index_prng_seed_t{ 202005201 } ),
            m_coord_dist( min_coord, max_coord ),
            m_momenta_dist( min_momenta, max_momenta ),
            m_unit_ratio_dist( min_unit_ratio, max_unit_ratio ),
            m_charge0_dist( min_charge0, max_charge0 ),
            m_mass0_dist( min_mass0, max_mass0 ),
            m_s_dist( min_s, max_s ),
            m_at_elem_dist( min_at_elem, max_at_elem ),
            m_at_turn_dist( min_at_turn, max_at_turn ),
            m_id_dist( min_id, max_id ),
            m_state_dist( index_t{ 0 }, index_t{ 1 } )
        {

        }

        SIXTRL_HOST_FN ParticleUnitInitialiser(
            ParticleUnitInitialiser< ParticleUnitT > const& ) = default;

        SIXTRL_HOST_FN ParticleUnitInitialiser(
            ParticleUnitInitialiser< ParticleUnitT >&& ) = default;

        SIXTRL_HOST_FN ParticleUnitInitialiser< ParticleUnitT >& operator=(
            ParticleUnitInitialiser< ParticleUnitT > const& ) = default;

        SIXTRL_HOST_FN ParticleUnitInitialiser< ParticleUnitT >& operator=(
            ParticleUnitInitialiser< ParticleUnitT >&& ) = default;

        SIXTRL_HOST_FN virtual ~ParticleUnitInitialiser() = default;

        template< typename... Args >
        SIXTRL_HOST_FN status_t operator()(
                SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT* SIXTRL_RESTRICT elem,
                Args&&... init_parameters )
        {
            return SIXTRL_CXX_NAMESPACE::Particle_init(
                elem, std::forward< Args >( init_parameters )... );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< class OtherParticleT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::Particle_is_type< OtherParticleT >(),
            status_t >::type
        init_for_copy(
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT*
                SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
            SIXTRL_PARTICLE_ARGPTR_DEC const OtherParticleT *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( orig ) ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class OtherParticleT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::Particle_is_type< OtherParticleT >(),
            status_t >::type
        init_for_copy(
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT* SIXTRL_RESTRICT elem,
            SIXTRL_PARTICLE_ARGPTR_DEC const OtherParticleT *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( orig ) )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::Particle_preset( elem );
            return ( elem != SIXTRL_NULLPTR )
                ? st::ARCH_STATUS_SUCCESS
                : st::ARCH_STATUS_GENERAL_FAILURE;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_HOST_FN status_t randomise(
                SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT* SIXTRL_RESTRICT elem )
        {
            return this->randomise_values( elem );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN status_t randomise_values(
                SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT* SIXTRL_RESTRICT elem )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            real_t const mass =
                this->random_mass0_value( this->m_real_prng );

            real_t const mass0 =
                this->random_mass0_value( this->m_real_prng );

            real_t const mass_ratio = mass / mass0;

            real_t const charge0 = this->random_charge0_value(
                this->m_real_prng );

            real_t const charge_ratio = this->random_unit_ratio_value(
                this->m_real_prng );

            real_t const beta0 =
                this->random_unit_ratio_value( this->m_real_prng );

            real_t const gamma0 = real_t{ 1 } /
                st::sqrt< real_t >( real_t{ 1 } - beta0 * beta0 );

            real_t const pc0 = mass0 * st::sqrt< real_t >(
                gamma0 * gamma0 - real_t{ 1 } );

            st::arch_status_t status = st::Particle_set_x(
                elem, this->random_coord_value( this->m_real_prng ) );

            status |= st::Particle_set_px(
                elem, this->random_momenta_value( this->m_real_prng ) );

            status |= st::Particle_set_y(
                elem, this->random_coord_value( this->m_real_prng ) );

            status |= st::Particle_set_py(
                elem, this->random_momenta_value( this->m_real_prng ) );

            status |= st::Particle_set_state(
                elem, this->random_state_value( this->m_index_prng ) );

            status |= st::Particle_set_at_element(
                elem, this->random_at_elem_value( this->m_index_prng ) );

            status |= st::Particle_set_at_turn(
                elem, this->random_at_turn_value( this->m_index_prng ) );

            status |= st::Particle_set_id(
                elem, this->random_id_value( this->m_index_prng ) );

            status |= st::Particle_set_psigma(
                elem, this->random_momenta_value( this->m_real_prng ) );

            status |= st::Particle_set_rpp(
                elem, this->random_unit_ratio_value( this->m_real_prng ) );

            status |= st::Particle_set_rvv(
                elem, this->random_unit_ratio_value( this->m_real_prng ) );

            status |= st::Particle_set_chi( elem, charge_ratio / mass_ratio );
            status |= st::Particle_set_charge_ratio( elem, charge_ratio );
            status |= st::Particle_set_charge0( elem, charge0 );
            status |= st::Particle_set_mass0( elem, mass0 );
            status |= st::Particle_set_beta0( elem, beta0 );
            status |= st::Particle_set_gamma0( elem, gamma0 );
            status |= st::Particle_set_pc0( elem, pc0 );

            status |= st::Particle_set_s(
                elem, this->random_s_value( this->m_real_prng ) );

            status |= st::Particle_update_zeta(
                elem, this->random_coord_value( this->m_real_prng ) );

            status |= st::Particle_update_delta(
                elem, this->random_momenta_value( this->m_real_prng ) );

            return status;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT* create_new(
            cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_create_new_object<
                    ParticleUnitT >( view );

                if( st::Particle_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = SIXTRL_NULLPTR;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT* create_new(
            cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.create_new< ParticleUnitT >();

                if( st::Particle_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = nullptr;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT* add_new(
            cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_add_object< ParticleUnitT >( view,
                    st::Particle_x( orig ), st::Particle_px( orig ),
                    st::Particle_y( orig ), st::Particle_py( orig ),
                    st::Particle_zeta( orig ), st::Particle_delta( orig ),
                    st::Particle_state( orig ), st::Particle_at_element( orig ),
                    st::Particle_at_turn( orig ), st::Particle_id( orig ),
                    st::Particle_psigma( orig ), st::Particle_rpp( orig ),
                    st::Particle_rvv( orig ), st::Particle_chi( orig ),
                    st::Particle_charge_ratio( orig ), st::Particle_charge0( orig ),
                    st::Particle_mass0( orig ), st::Particle_beta0( orig ),
                    st::Particle_gamma0( orig ), st::Particle_pc0( orig ),
                    st::Particle_s( orig ) );
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT* add_new(
            cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleUnitT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.template add< ParticleUnitT >(
                    st::Particle_x( orig ), st::Particle_px( orig ),
                    st::Particle_y( orig ), st::Particle_py( orig ),
                    st::Particle_zeta( orig ), st::Particle_delta( orig ),
                    st::Particle_state( orig ), st::Particle_at_element( orig ),
                    st::Particle_at_turn( orig ), st::Particle_id( orig ),
                    st::Particle_psigma( orig ), st::Particle_rpp( orig ),
                    st::Particle_rvv( orig ), st::Particle_chi( orig ),
                    st::Particle_charge_ratio( orig ), st::Particle_charge0( orig ),
                    st::Particle_mass0( orig ), st::Particle_beta0( orig ),
                    st::Particle_gamma0( orig ), st::Particle_pc0( orig ),
                    st::Particle_s( orig ) );
            }

            return added_elem;
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_coord_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_coord_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_coord_value()
        {
            return this->m_coord_dist( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_momenta_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_momenta_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_momenta_value()
        {
            return this->m_momenta_dist( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_unit_ratio_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_unit_ratio_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_unit_ratio_value()
        {
            return this->m_unit_ratio_dist( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_charge0_value( PrngT& SIXTRL_RESTRICT prng )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            real_t const charge_sign = ( this->random_unit_ratio_value( prng
                ) > real_t{ 0.5 } ) ? real_t{ 1 } : real_t{ -1 };

            return charge_sign * this->m_charge0_dist( prng ) *
                st::PhysConst_charge0< real_t >();
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_charge0_value()
        {
            return this->random_charge0_value( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_mass0_value( PrngT& SIXTRL_RESTRICT prng )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return this->m_mass0_dist( prng ) *
                st::PhysConst_mass_atomic_ev< real_t >();
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_mass0_value()
        {
            return this->random_mass0_value( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_s_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_s_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_s_value()
        {
            return this->m_s_dist( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN index_t
        random_at_elem_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_at_elem_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN index_t random_at_elem_value()
        {
            return this->m_at_elem_dist( this->m_index_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN index_t
        random_at_turn_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_at_turn_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN index_t random_at_turn_value()
        {
            return this->m_at_turn_dist( this->m_index_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN index_t
        random_id_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_id_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN index_t random_id_value()
        {
            return this->m_id_dist( this->m_index_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN index_t
        random_state_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_state_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN index_t random_state_value()
        {
            return this->m_state_dist( this->m_index_prng );
        }

        private:

        real_prng_t          m_real_prng;
        index_prng_t         m_index_prng;
        real_uniform_dist_t  m_coord_dist;
        real_uniform_dist_t  m_momenta_dist;
        real_uniform_dist_t  m_unit_ratio_dist;
        real_uniform_dist_t  m_charge0_dist;
        real_uniform_dist_t  m_mass0_dist;
        real_uniform_dist_t  m_s_dist;
        index_dist_t         m_at_elem_dist;
        index_dist_t         m_at_turn_dist;
        index_dist_t         m_id_dist;
        index_dist_t         m_state_dist;
    };

    /* ===================================================================== */

    template< class ParticleUnitT >
    struct ObjsRandomInitialiserTraits< ParticleUnitT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleUnitT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::ParticleUnitInitialiser<
                    ParticleUnitT > initialiser_t;
    };

    template< class ParticleUnitT >
    struct CObjElemInitialiserTraits< ParticleUnitT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleUnitT >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_type_id< ParticleUnitT >() !=
            SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
                SIXTRL_CXX_NAMESPACE::cobj_type_id_t >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::ParticleUnitInitialiser< ParticleUnitT >
                initialiser_t;
    };

    /* ===================================================================== */

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Particle_tests_assignment( SIXTRL_CXX_NAMESPACE::arch_size_t const
        SIXTRL_UNUSED( num_elem ) = SIXTRL_CXX_NAMESPACE::arch_size_t{ 100 } )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Particle_tests_assignment( SIXTRL_CXX_NAMESPACE::arch_size_t const
        num_elem = SIXTRL_CXX_NAMESPACE::arch_size_t{ 100 } )
    {
        namespace st = sixtrack;

        typedef st::arch_size_t st_size_t;
        typedef typename st::tests::ObjsRandomInitialiserTraits<
                    ParticleT >::initialiser_t initialiser_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        std::vector< ParticleT > cmp_objs( num_elem, ParticleT{} );
        initialiser_t obj_init;

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elem ; ++ii )
        {
            ParticleT* orig = std::addressof( cmp_objs[ ii ] );
            status = obj_init.randomise( orig );
            if( status != st::ARCH_STATUS_SUCCESS ) break;
        }

        if( status != st::ARCH_STATUS_SUCCESS ) return status;

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elem ; ++ii )
        {
            ParticleT const* orig = std::addressof( cmp_objs[ ii ] );
            status = st::ARCH_STATUS_GENERAL_FAILURE;

            SIXTRL_PARTICLE_ARGPTR_DEC ParticleT elem_obj;
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* elem =
                st::Particle_preset( &elem_obj );

            if( elem == nullptr ) return status;

            status = obj_init.init_for_copy( elem, orig );
            if( status != st::ARCH_STATUS_SUCCESS ) return status;

            status = obj_init.randomise_values( elem );
            if( status != st::ARCH_STATUS_SUCCESS ) return status;

            auto cmp_result = st::ObjDataComparisonHelper< ParticleT, ParticleT
                >::compare( elem, orig );

            if( cmp_result == st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) continue;

            status = st::Particle_set_x( elem, st::Particle_x( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_px( elem, st::Particle_px( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_y( elem, st::Particle_y( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_py( elem, st::Particle_py( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_zeta( elem, st::Particle_zeta( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_delta( elem, st::Particle_delta( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_state( elem, st::Particle_state( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_at_element(
                elem, st::Particle_at_element( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_at_turn(
                elem, st::Particle_at_turn( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_id( elem, st::Particle_id( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_psigma(
                elem, st::Particle_psigma( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_rpp( elem, st::Particle_rpp( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_rvv( elem, st::Particle_rvv( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_chi( elem, st::Particle_chi( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_charge_ratio(
                elem, st::Particle_charge_ratio( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_charge0(
                elem, st::Particle_charge0( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_mass0( elem, st::Particle_mass0( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_beta0( elem, st::Particle_beta0( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_gamma0(
                elem, st::Particle_gamma0( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_pc0( elem, st::Particle_pc0( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::Particle_set_s( elem, st::Particle_s( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            cmp_result = st::ObjDataComparisonHelper<
                ParticleT, ParticleT >::compare( elem, orig );
            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            status = obj_init.randomise_values( elem );

            cmp_result = st::ObjDataComparisonHelper<
                ParticleT, ParticleT >::compare( elem, orig );
            if( cmp_result == st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            status = st::ObjDataConverter< ParticleT, ParticleT,
                st::STORAGE_BE_DEFAULT, st::STORAGE_BE_DEFAULT >::perform(
                    elem, orig );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            cmp_result = st::ObjDataComparisonHelper< ParticleT, ParticleT
                >::compare( elem, orig );
            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( status != st::ARCH_STATUS_SUCCESS ) break;
        }

        return status;
    }

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_PARTICLES_PARTICLE_UNIT_CXX_HPP__ */
