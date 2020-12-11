#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/particles/particle_data.hpp"
    #include "sixtracklib/common/particles/particle_api.h"
    #include "sixtracklib/common/particles/particle_derived_api.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/obj_base_class.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class E, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    class TParticleImpl : public ObjDataStorageInterfaceBase<
        E, StoreT, SIXTRL_CXX_NAMESPACE::TParticleImpl< E, StoreT > >
    {
        public:
        typedef typename ParticleTraits< E >::real_t                 real_t;
        typedef typename ParticleTraits< E >::index_t                index_t;
        typedef typename TypeCompLogicTypeTraits< index_t >::logic_t logic_t;

        typedef typename TypeMethodParamTraits< real_t >::const_argument_type
                real_arg_t;

        typedef typename TypeMethodParamTraits< real_t >::const_existing_type
                real_const_existing_t;

        typedef typename TypeMethodParamTraits< index_t >::const_argument_type
                index_arg_t;

        typedef typename TypeMethodParamTraits< index_t >::const_existing_type
                index_const_existing_t;

        typedef typename TypeCompLogicTypeTraits< logic_t >::const_argument_type
                logic_arg_t;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< typename... Args >
        SIXTRL_FN arch_status_t init( Args&&... args )
        {
            return SIXTRL_CXX_NAMESPACE::Particle_init( this->as_ptr_data(),
                std::forward< Args >( args )... );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_FN real_t sigma() const
        {
            return SIXTRL_CXX_NAMESPACE::Particle_sigma( this->as_ptr_data() );
        }


        template< typename RealArg >
        SIXTRL_FN arch_status_t update_sigma( RealArg new_sigma_value )
        {
            return SIXTRL_CXX_NAMESPACE::Particle_update_sigma(
                this->as_ptr_data(), new_sigma_value );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< typename RealArg >
        SIXTRL_FN arch_status_t update_psigma( RealArg new_psigma_value )
        {
            return SIXTRL_CXX_NAMESPACE::Particle_update_psigma(
                this->as_ptr_data(), new_psigma_value );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_FN real_t tau() const
        {
            return SIXTRL_CXX_NAMESPACE::Particle_sigma( this->as_ptr_data() );
        }

        template< typename RealArg >
        SIXTRL_FN arch_status_t update_tau( RealArg new_tau_value )
        {
            return SIXTRL_CXX_NAMESPACE::Particle_update_tau(
                this->as_ptr_data(), new_tau_value );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_FN real_t ptau() const
        {
            return SIXTRL_CXX_NAMESPACE::Particle_ptau( this->as_ptr_data() );
        }

        template< typename RealArg >
        SIXTRL_FN arch_status_t update_ptau( RealArg new_ptau_value )
        {
            return SIXTRL_CXX_NAMESPACE::Particle_update_ptau(
                this->as_ptr_data(), new_ptau_value );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< typename RealArg >
        SIXTRL_FN arch_status_t update_delta( RealArg new_delta_value )
        {
            return SIXTRL_CXX_NAMESPACE::Particle_update_delta(
                this->as_ptr_data(), new_delta_value );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_FN real_T beta() const
        {
            return SIXTRL_CXX_NAMESPACE::Particle_beta( this->as_ptr_data() );
        }

        SIXTRL_FN real_t energy0() const
        {
            return SIXTRL_CXX_NAMESPACE::Particle_energy0(
                this->as_ptr_data() );
        }

        SIXTRL_FN real_t energy() const
        {
            return SIXTRL_CXX_NAMESPACE::Particle_energy( this->as_ptr_data() );
        }

        template< typename RealArg >
        SIXTRL_FN arch_status_t add_to_energy( RealArg d_energy )
        {
            return SIXTRL_CXX_NAMESPACE::Particle_add_to_energy(
                this->as_ptr_data(), d_energy );
        }

        template< typename RealArg >
        SIXTRL_FN arch_status_t update_energy( RealArg new_energy_value )
        {
            return SIXTRL_CXX_NAMESPACE::Particle_update_energy(
                this->as_ptr_data(), new_energy_value );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_FN real_t mass_ratio() const
        {
            return SIXTRL_CXX_NAMESPACE::Particle_mass_ratio(
                this->as_ptr_data() );
        }

        SIXTRL_FN real_t mass() const
        {
            return SIXTRL_CXX_NAMESPACE::Particle_mass( this->as_ptr_data() );
        }

        SIXTRL_FN real_t charge() const
        {
            return SIXTRL_CXX_NAMESPACE::Particle_charge(
                this->as_ptr_data() );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_FN bool is_lost() const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_is_lost(
                this->as_ptr_data() );
        }

        SIXTRL_FN bool is_not_lost() const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_is_not_lost(
                this->as_ptr_data() );
        }

        SIXTRL_FN bool has_any_lost() const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_has_any_lost(
                this->as_ptr_data() );
        }

        SIXTRL_FN bool has_any_not_lost() const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_has_any_not_lost(
                this->as_ptr_data() );
        }
    };
}

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/obj_base_class.hpp"
    #include "sixtracklib/common/particle/particle_cobjects_api.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class I, arch_size_t N,
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(),
        arch_size_t IAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    using TParticle = TParticleImpl<
        ParticleData< R, I, N, RAlign IAlign >, STORAGE_BE_COBJECTS >;

    typedef TParticleImpl< CParticleEquivData, STORAGE_BE_COBJECTS > Particle;
    typedef TParticleImpl< ::NS(Particle),     STORAGE_BE_COBJECTS > CParticle;
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_CXX_HPP__ */
