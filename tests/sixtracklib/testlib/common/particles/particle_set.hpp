#ifndef SIXTRACKLIB_TESTLIB_COMMON_PARTICLES_PARTICLE_SET_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_PARTICLES_PARTICLE_SET_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particle.hpp"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/cbuffer.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/physics_constants.h"
    #include "sixtracklib/common/internal/type_random_traits.hpp"
    #include "sixtracklib/testlib/common/objs/objs_traits.hpp"
    #include "sixtracklib/testlib/common/particles/particle_unit.hpp"
    #include "sixtracklib/testlib/common/cobjects/cobj_elem_traits.hpp"
    #include "sixtracklib/testlib/common/cobjects/cobjects_initialiser_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    template< class ParticleSetT >
    class ParticleSetInitialiser : public CObjElemInitialiserBase
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::particle_num_elements_t num_elements_t;

        static_assert( SIXTRL_CXX_NAMESPACE::ParticleSet_is_type<
            ParticleSetT >(), "Requires ParticleSetT to be multipole class" );

        typedef typename SIXTRL_CXX_NAMESPACE::ParticleSetTraits<
            ParticleSetT >::real_t real_t;

        typedef typename SIXTRL_CXX_NAMESPACE::ParticleSetTraits<
            ParticleSetT >::index_t index_t;

        typedef SIXTRL_CXX_NAMESPACE::TParticle< real_t, index_t > particle_t;
        typedef typename SIXTRL_CXX_NAMESPACE::tests::ObjsRandomInitialiserTraits<
                    particle_t >::initialiser_t particle_init_t;

        private:

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< num_elements_t >
                nelems_random_traits_t;

        public:

        typedef typename nelems_random_traits_t::uniform_dist_t nelems_dist_t;
        typedef typename nelems_random_traits_t::default_prng_t nelems_prng_t;
        typedef typename nelems_random_traits_t::default_prng_seed_t
                         nelems_prng_seed_t;

        typedef typename particle_init_t::const_index_arg_t const_index_arg_t;
        typedef typename particle_init_t::const_real_arg_t  const_real_arg_t;

        typedef SIXTRL_CXX_NAMESPACE::CBufferView cbuffer_view_t;
        typedef SIXTRL_CXX_NAMESPACE::CBuffer cbuffer_t;

        SIXTRL_HOST_FN ParticleSetInitialiser() :
            m_particle_init(),
            m_num_elem_prng( nelems_prng_seed_t{ 202005202 } ),
            m_num_particles_dist( index_t{ 1 }, index_t{ 100 } )
        {

        }

        SIXTRL_HOST_FN explicit ParticleSetInitialiser(
            const_index_arg_t min_num_particles,
            const_index_arg_t max_num_particles,
            const_real_arg_t  min_coord, const_real_arg_t  max_coord,
            const_real_arg_t  min_momenta, const_real_arg_t  max_momenta,
            const_real_arg_t  min_unit_ratio, const_real_arg_t  max_unit_ratio,
            const_index_arg_t min_at_elem, const_index_arg_t max_at_elem,
            const_index_arg_t min_at_turn, const_index_arg_t max_at_turn,
            const_index_arg_t min_id, const_index_arg_t max_id,
            const_real_arg_t  min_charge0, const_real_arg_t  max_charge0,
            const_real_arg_t  min_mass0, const_real_arg_t  max_mass0,
            const_real_arg_t  min_s, const_real_arg_t  max_s ) :
            m_particle_init( min_coord, max_coord, min_momenta, max_momenta,
                             min_unit_ratio, max_unit_ratio, min_at_elem, max_at_elem,
                             min_at_turn, max_at_turn, min_id, max_id,
                             min_charge0, max_charge0, min_mass0, max_mass0,
                             min_s, max_s ),
            m_num_elem_prng( nelems_prng_seed_t{ 202005202 } ),
            m_num_particles_dist( min_num_particles, max_num_particles )
        {

        }

        SIXTRL_HOST_FN ParticleSetInitialiser(
            ParticleSetInitialiser< ParticleSetT > const& ) = default;

        SIXTRL_HOST_FN ParticleSetInitialiser(
            ParticleSetInitialiser< ParticleSetT >&& ) = default;

        SIXTRL_HOST_FN ParticleSetInitialiser< ParticleSetT >& operator=(
            ParticleSetInitialiser< ParticleSetT > const& ) = default;

        SIXTRL_HOST_FN ParticleSetInitialiser< ParticleSetT >& operator=(
            ParticleSetInitialiser< ParticleSetT >&& ) = default;

        SIXTRL_HOST_FN virtual ~ParticleSetInitialiser() = default;

        template< typename... Args >
        SIXTRL_HOST_FN status_t operator()(
                SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT elem,
                Args&&... init_parameters )
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_init(
                elem, std::forward< Args >( init_parameters )... );
        }

        template< class OtherParticleSetT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< OtherParticleSetT >(),
            SIXTRL_CXX_NAMESPACE::arch_status_t >::type
         init_for_copy(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT
                SIXTRL_UNUSED( elem ),
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const OtherParticleSetT *const
                SIXTRL_RESTRICT SIXTRL_UNUSED( orig ) )
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class OtherParticleSetT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
             SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< OtherParticleSetT >(),
             SIXTRL_CXX_NAMESPACE::arch_status_t >::type
         init_for_copy(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT elem,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const OtherParticleSetT *const
                SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ParticleSet_init( elem,
                st::ParticleSet_num_particles( orig ),
                st::ParticleSet_capacity( orig ) );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                this->do_init_impl_default_ptrs( elem,
                    st::ParticleSet_capacity( elem ) );
            }

            return status;
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_INLINE SIXTRL_HOST_FN status_t randomise(
                SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT elem )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            st::particle_num_elements_t const num_particles =
                this->random_num_particles_value( this->m_num_elem_prng );

            real_t const dice = this->m_particle_init.random_unit_ratio_value();

            st::particle_num_elements_t const capacity =
                ( dice <= real_t{ 0.5 } )
                    ?  st::particle_num_elements_t{ 0 }
                    :  this->random_num_particles_value(
                        this->m_num_elem_prng );

            status = st::ParticleSet_init( elem, num_particles, capacity );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_impl_default< ParticleSetT >() ) )
            {
                status = this->do_init_impl_default_ptrs( elem,
                    st::ParticleSet_capacity( elem ) );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->randomise_values( elem );
            }

            return status;
        }

        SIXTRL_INLINE SIXTRL_HOST_FN status_t randomise_values(
                SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT elem )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef st::particle_num_elements_t nelems_t;

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
            nelems_t const nparticles = st::ParticleSet_num_particles( elem );

            if( ( elem != SIXTRL_NULLPTR ) && ( nparticles > nelems_t{ 0 } ) )
            {
                status = st::ARCH_STATUS_SUCCESS;

                for( nelems_t ii = nelems_t{ 0 } ; ii < nparticles ; ++ii )
                {
                    SIXTRL_PARTICLE_ARGPTR_DEC particle_t p_obj;
                    SIXTRL_PARTICLE_ARGPTR_DEC particle_t* p =
                        st::Particle_preset( &p_obj );

                    SIXTRL_ASSERT( p != SIXTRL_NULLPTR );
                    status = this->m_particle_init.randomise_values( p );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        status = st::ParticleSet_load_from_particle<
                            ParticleSetT, particle_t >( elem, p, ii );
                    }

                    if( status != st::ARCH_STATUS_SUCCESS ) break;
                }
            }

            return status;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT* create_new(
            cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_create_new_object<
                    ParticleSetT >( view, st::ParticleSet_num_particles( orig ),
                        st::ParticleSet_capacity( orig ) );

                if( st::ParticleSet_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = SIXTRL_NULLPTR;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT* create_new(
            cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.create_new< ParticleSetT >(
                    st::ParticleSet_num_particles( orig ),
                    st::ParticleSet_capacity( orig ) );

                if( st::ParticleSet_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = nullptr;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT* add_new(
            cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_add_object< ParticleSetT >( view,
                    st::ParticleSet_num_particles( orig ),
                    st::ParticleSet_const_x_begin( orig ),
                    st::ParticleSet_const_px_begin( orig ),
                    st::ParticleSet_const_y_begin( orig ),
                    st::ParticleSet_const_py_begin( orig ),
                    st::ParticleSet_const_zeta_begin( orig ),
                    st::ParticleSet_const_delta_begin( orig ),
                    st::ParticleSet_const_state_begin( orig ),
                    st::ParticleSet_const_at_element_begin( orig ),
                    st::ParticleSet_const_at_turn_begin( orig ),
                    st::ParticleSet_const_particle_id_begin( orig ),
                    st::ParticleSet_const_psigma_begin( orig ),
                    st::ParticleSet_const_rpp_begin( orig ),
                    st::ParticleSet_const_rvv_begin( orig ),
                    st::ParticleSet_const_chi_begin( orig ),
                    st::ParticleSet_const_charge_ratio_begin( orig ),
                    st::ParticleSet_const_charge0_begin( orig ),
                    st::ParticleSet_const_mass0_begin( orig ),
                    st::ParticleSet_const_beta0_begin( orig ),
                    st::ParticleSet_const_gamma0_begin( orig ),
                    st::ParticleSet_const_pc0_begin( orig ),
                    st::ParticleSet_const_s_begin( orig ),
                    st::ParticleSet_capacity( orig ) );
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT* add_new(
            cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.template add< ParticleSetT >(
                    st::ParticleSet_num_particles( orig ),
                    st::ParticleSet_const_x_begin( orig ),
                    st::ParticleSet_const_px_begin( orig ),
                    st::ParticleSet_const_y_begin( orig ),
                    st::ParticleSet_const_py_begin( orig ),
                    st::ParticleSet_const_zeta_begin( orig ),
                    st::ParticleSet_const_delta_begin( orig ),
                    st::ParticleSet_const_state_begin( orig ),
                    st::ParticleSet_const_at_element_begin( orig ),
                    st::ParticleSet_const_at_turn_begin( orig ),
                    st::ParticleSet_const_particle_id_begin( orig ),
                    st::ParticleSet_const_psigma_begin( orig ),
                    st::ParticleSet_const_rpp_begin( orig ),
                    st::ParticleSet_const_rvv_begin( orig ),
                    st::ParticleSet_const_chi_begin( orig ),
                    st::ParticleSet_const_charge_ratio_begin( orig ),
                    st::ParticleSet_const_charge0_begin( orig ),
                    st::ParticleSet_const_mass0_begin( orig ),
                    st::ParticleSet_const_beta0_begin( orig ),
                    st::ParticleSet_const_gamma0_begin( orig ),
                    st::ParticleSet_const_pc0_begin( orig ),
                    st::ParticleSet_const_s_begin( orig ),
                    st::ParticleSet_capacity( orig ) );
            }

            return added_elem;
        }

        SIXTRL_INLINE SIXTRL_HOST_FN particle_init_t const&
        particle_init() const SIXTRL_NOEXCEPT
        {
            return this->m_particle_init;
        }

        SIXTRL_INLINE SIXTRL_HOST_FN particle_init_t&
        particle_init() SIXTRL_NOEXCEPT
        {
            return this->m_particle_init;
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN num_elements_t
        random_num_particles_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_num_particles_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN num_elements_t random_num_particles_value()
        {
            return this->random_num_particles_value( this->m_num_elem_prng );
        }

        private:

        SIXTRL_INLINE SIXTRL_HOST_FN status_t do_init_impl_default_ptrs(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT elem,
            SIXTRL_CXX_NAMESPACE::particle_num_elements_t const capacity )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( st::ParticleSet_impl_default< ParticleSetT >() ) &&
                ( capacity > SIXTRL_CXX_NAMESPACE::particle_num_elements_t{
                        0 } ) )
            {
                auto ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_x_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_px_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_y_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_py_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_zeta_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_delta_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< index_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::index_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_state_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< index_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::index_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_at_element_addr(
                        elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< index_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::index_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_at_turn_addr(
                        elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< index_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::index_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_particle_id_addr(
                        elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_psigma_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_rpp_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_rvv_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_chi_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_charge_ratio_addr(
                        elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_charge0_addr(
                        elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_mass0_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_beta0_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_gamma0_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_pc0_addr( elem, ret.first );
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                ret = this->add_ptr_field< real_t >( capacity,
                    st::ParticleSetTraits< ParticleSetT >::real_alignment );

                status = ret.second;
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_set_s_addr( elem, ret.first );
                }
            }

            return status;
        }

        private:

        particle_init_t      m_particle_init;
        nelems_prng_t        m_num_elem_prng;
        nelems_dist_t        m_num_particles_dist;
    };

    /* ===================================================================== */

    template< class ParticleSetT >
    struct ObjsRandomInitialiserTraits< ParticleSetT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::ParticleSetInitialiser<
                    ParticleSetT > initialiser_t;
    };

    template< class ParticleSetT >
    struct CObjElemInitialiserTraits< ParticleSetT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_type_id< ParticleSetT >() !=
            SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
                SIXTRL_CXX_NAMESPACE::cobj_type_id_t >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::ParticleSetInitialiser< ParticleSetT >
                initialiser_t;
    };

    /* ===================================================================== */

    template< class ParticleSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_tests_assignment(
        SIXTRL_CXX_NAMESPACE::arch_size_t const SIXTRL_UNUSED( num_elem ) =
            SIXTRL_CXX_NAMESPACE::arch_size_t{ 0 } ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_tests_assignment( SIXTRL_CXX_NAMESPACE::arch_size_t const
        num_elem = SIXTRL_CXX_NAMESPACE::arch_size_t{ 100 } )
    {
        namespace st = sixtrack;

        typedef st::arch_size_t st_size_t;
        typedef typename st::tests::ObjsRandomInitialiserTraits<
                    ParticleSetT >::initialiser_t initialiser_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        std::vector< ParticleSetT > cmp_objs( num_elem, ParticleSetT{} );
        initialiser_t obj_init;

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elem ; ++ii )
        {
            ParticleSetT* orig = std::addressof( cmp_objs[ ii ] );
            status = obj_init.randomise( orig );
            if( status != st::ARCH_STATUS_SUCCESS ) break;
        }

        if( status != st::ARCH_STATUS_SUCCESS ) return status;

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elem ; ++ii )
        {
            ParticleSetT const* orig = std::addressof( cmp_objs[ ii ] );
            status = st::ARCH_STATUS_GENERAL_FAILURE;

            SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT elem_obj;
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleSetT* elem =
                st::ParticleSet_preset( &elem_obj );

            if( elem == nullptr ) return status;

            status = obj_init.init_for_copy( elem, orig );
            if( status != st::ARCH_STATUS_SUCCESS ) return status;

            status = obj_init.randomise_values( elem );
            if( status != st::ARCH_STATUS_SUCCESS ) return status;

            auto cmp_result = st::ObjDataComparisonHelper<
                ParticleSetT, ParticleSetT >::compare( elem, orig );

            if( cmp_result == st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) continue;

            status = st::ParticleSet_set_x(
                elem, st::ParticleSet_const_x_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_px(
                elem, st::ParticleSet_const_px_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_y(
                elem, st::ParticleSet_const_y_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_py(
                elem, st::ParticleSet_const_py_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_zeta(
                elem, st::ParticleSet_const_zeta_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_delta(
                elem, st::ParticleSet_const_delta_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_state(
                elem, st::ParticleSet_const_state_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_at_element(
                elem, st::ParticleSet_const_at_element_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_at_turn(
                elem, st::ParticleSet_const_at_turn_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_particle_id(
                elem, st::ParticleSet_const_particle_id_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_psigma(
                elem, st::ParticleSet_const_psigma_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_rpp(
                elem, st::ParticleSet_const_rpp_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_rvv(
                elem, st::ParticleSet_const_rvv_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_chi(
                elem, st::ParticleSet_const_chi_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_charge_ratio(
                elem, st::ParticleSet_const_charge_ratio_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_charge0(
                elem, st::ParticleSet_const_charge0_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_mass0(
                elem, st::ParticleSet_const_mass0_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_beta0(
                elem, st::ParticleSet_const_beta0_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_gamma0(
                elem, st::ParticleSet_const_gamma0_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_pc0(
                elem, st::ParticleSet_const_pc0_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::ParticleSet_set_s(
                elem, st::ParticleSet_const_s_begin( orig ) );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            cmp_result = st::ObjDataComparisonHelper<
                ParticleSetT, ParticleSetT >::compare( elem, orig );
            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            status = obj_init.randomise_values( elem );

            cmp_result = st::ObjDataComparisonHelper<
                ParticleSetT, ParticleSetT >::compare( elem, orig );
            if( cmp_result == st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            status = st::ObjDataConverter< ParticleSetT, ParticleSetT,
                st::STORAGE_BE_DEFAULT, st::STORAGE_BE_DEFAULT >::perform(
                    elem, orig );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            cmp_result = st::ObjDataComparisonHelper< ParticleSetT, ParticleSetT
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

    /* ===================================================================== */

    template< class ParticleSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_tests_particle_unit_assignments(
        SIXTRL_CXX_NAMESPACE::arch_size_t const SIXTRL_UNUSED( num_elem ) =
            SIXTRL_CXX_NAMESPACE::arch_size_t{ 0 } ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_tests_particle_unit_assignments(
        SIXTRL_CXX_NAMESPACE::arch_size_t const num_elem =
            SIXTRL_CXX_NAMESPACE::arch_size_t{ 100 } )
    {
        namespace st = sixtrack;

        typedef st::arch_size_t st_size_t;

        typedef typename st::ParticleSetTraits< ParticleSetT >::real_t  real_t;
        typedef typename st::ParticleSetTraits< ParticleSetT >::index_t index_t;
        typedef st::TParticle< real_t, index_t > particle_t;

        typedef typename st::tests::ObjsRandomInitialiserTraits<
                ParticleSetT >::initialiser_t pset_init_t;

        typedef typename st::tests::ObjsRandomInitialiserTraits<
                 particle_t >::initialiser_t particle_init_t;

        typedef st::particle_num_elements_t nelements_t;
        st::arch_status_t status = st::ARCH_STATUS_SUCCESS;

        std::vector< ParticleSetT > pset_objs( num_elem, ParticleSetT{} );
        pset_init_t pset_init;
        particle_init_t particle_init;

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elem ; ++ii )
        {
            ParticleSetT* pset = std::addressof( pset_objs[ ii ] );
            status = pset_init.randomise( pset );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            nelements_t const num_particles =
                st::ParticleSet_num_particles( pset );

            if( num_particles == nelements_t{ 0 } ) continue;

            std::vector< particle_t > particle_objs(
                num_particles, particle_t{} );

            std::vector< particle_t > cmp_particle_objs(
                num_particles, particle_t{} );

            for( nelements_t jj = nelements_t{ 0 } ; jj < num_particles ; ++jj )
            {
                particle_t* p = std::addressof( particle_objs[ jj ] );
                particle_t* cmp_p = std::addressof( cmp_particle_objs[ jj ] );

                if( p == SIXTRL_NULLPTR )
                {
                    status |= st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

                if( cmp_p == SIXTRL_NULLPTR )
                {
                    status |= st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

                SIXTRL_ASSERT( p != cmp_p );

                /* Randomise more than once to avoid having the same
                 * values in the pset and the p / cmp_p */

                status = particle_init.randomise( p );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                status = particle_init.randomise( p );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                status = particle_init.randomise( cmp_p );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                status = particle_init.randomise( cmp_p );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                auto cmp_result = st::ObjDataComparisonHelper<
                    particle_t, particle_t >::compare( p, cmp_p );

                if( cmp_result == st::TypeCompResultTraits<
                    decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) continue;

                status = st::ParticleSet_load_from_particle( pset, p, jj );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                status = st::ParticleSet_store_to_particle( pset, cmp_p, jj );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                cmp_result = st::ObjDataComparisonHelper<
                    particle_t, particle_t >::compare( p, cmp_p );

                if( cmp_result != st::TypeCompResultTraits<
                    decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
                {
                    status |= st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

                status = particle_init.randomise( p );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                status = particle_init.randomise( cmp_p );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                cmp_result = st::ObjDataComparisonHelper<
                    particle_t, particle_t >::compare( p, cmp_p );

                if( cmp_result == st::TypeCompResultTraits<
                    decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) continue;

                status = st::ParticleSet_load_from_particle( pset, cmp_p, jj );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                status = st::ParticleSet_store_to_particle( pset, p, jj );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                cmp_result = st::ObjDataComparisonHelper<
                    particle_t, particle_t >::compare( p, cmp_p );

                if( cmp_result != st::TypeCompResultTraits<
                    decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
                {
                    status |= st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }
            }

            if( status != st::ARCH_STATUS_SUCCESS ) break;
        }

        return status;
    }

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_PARTICLES_PARTICLE_SET_CXX_HPP__ */
