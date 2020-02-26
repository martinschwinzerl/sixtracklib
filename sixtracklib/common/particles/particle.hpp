#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/particles/particle_data.hpp"
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


        real_t mass_ratio() const SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            SIXTRL_ASSERT( !st::Type_comp_any_are_close(
                this->chi, real_t{ 0 }, real_t{ 0 }, real_t{ 1e-15 } ) );

            return this->charge_ratio / this->chi;
        }

        real_t mass() const SIXTRL_NOEXCEPT
        {
            return this->mass_ratio() * this->mass0;
        }

        real_t charge() const SIXTRL_NOEXCEPT
        {
            return this->charge_ratio * this->charge0;
        }

        real_t beta() const SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_ASSERT( st::Type_comp_all_more( this->beta0, real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_less_or_equal(
                this->beta0, real_t{ 0 } ) );

            return this->rvv * this->beta0
        }

        real_t gamma() const SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            #if !defined( _GPUCODE )
            using std::sqrt;
            #endif /* !defined( _GPUCODE ) */

            real_t const beta = this->beta();
            SIXTRL_ASSERT( st::Type_comp_all_more( beta, real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_less_or_equal(
                beta, real_t{ 1 } ) );

            return real_t{ 1 } / sqrt( real_t{ 1 } - beta * beta );
        }

        real_t energy0() const SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            #if !defined( _GPUCODE )
            using std::sqrt;
            #endif /* !defined( _GPUCODE ) */

            SIXTRL_ASSERT( st::Type_comp_all_more(
                this->mass0, real_t{ 0 } ) );

            SIXTRL_ASSERT( st::Type_comp_all_more(
                this->pc0, real_t{ 0 } ) );

            return sqrt( this->pc0 * this->pc0 + this->mass0 * this->mass0 );
        }

        real_t energy() const SIXTRL_NOEXCEPT
        {
            return ( this->psigma * this->beta0 * this->pc0 ) +
                   ( this->energy0() * this->mass_ratio() );
        }

        real_t add_to_energy( real_arg_t delta_energy ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            #if !defined( _GPUCODE )
            using std::sqrt;
            #endif /* !defined( _GPUCODE ) */

            SIXTRL_ASSERT( st::Type_comp_all_more( this->rvv, real_t{ 0 } );
            SIXTRL_ASSERT( st::Type_comp_all_more( this->beta0, real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_less_or_equal(
                this->beta0, real_t{ 1 } ) );

            real_t const delta_beta0 = this->delta * this->beta0;

            SIXTRL_ASSERT( st::Type_comp_all_more(
                this->energy0(), real_t{ 0 } ) );

            SIXTRL_ASSERT(
                st::Type_comp_all_more_or_equal(
                    delta_beta0, real_t{ 0 } ) ||
                st::Type_comp_all_more_or_equal(
                    delta_beta0 * delta_beta0 + real_t{ 1 },
                    real_t{ -2 } * delta_beta0 * this->beta0 ) );

            real_t const ptau_beta0 = delta_energy / this->energy0() +
                sqrt( delta_beta0 * delta_beta0 + real_t{ 1 } +
                      real_t{ 2 } * delta_beta0 * this->beta0 ) - real_t{ 1 };

            real_t const ptau = ptau_beta0 / this->beta0;
            real_t const psigma = ptau / this->beta0;
            real_t const delta_p_one = sqrt(
                ptau * ptau + real_t{ 2 } * psigma + real_t{ 1 } );
            real_t const rvv = delta_p_one / ( real_t{ 1 } + ptau_beta0 );

            SIXTRL_ASSERT(
                st::Type_comp_all_more_or_equal( psigma, real_t{ 0 } ) ||
                st::Type_comp_all_more_or_equal(
                    ptau * ptau + real_t{ 1 }, real_t{ -2 } * psigma ) );

            SIXTRL_ASSERT( !st::Type_comp_any_are_close(
                ptau_beta0 + real_t{ 1 }, real_t{ 0 },
                    real_t{ 0 }, real_t{ 1e-14 } ) );

            SIXTRL_ASSERT( !st::Type_comp_any_are_close(
                delta_p_one, real_t{ 0 }, real_t{ 0 }, real_t{ 1e-14 } ) );

            this->delta  = delta_p_one - real_t{ 1 };
            this->psigma = psigma;
            this->zeta  *= rvv / this->rvv;
            this->rvv    = rvv;
            this->rpp    = real_t{ 1 } / delta_p_one;
        }

        real_t sigma() const SIXTRL_NOEXCEPT
        {
            SIXTRL_ASSERT( this->rvv > real_t{ 0 } );
            return this->zeta / this->rvv;
        }

        real_t tau() const SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            SIXTRL_ASSERT( st::Type_comp_all_more( this->rvv,   real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_more( this->beta0, real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_less_or_equal(
                this->beta0, real_t{ 1 } ) );

            return this->zeta / ( this->rvv * this->beta0 );
        }

        real_t ptau() const SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            #if !defined( _GPUCODE )
            using std::sqrt;
            #endif /* !defined( _GPUCODE ) */

            SIXTRL_ASSERT( st::Type_comp_all_more( this->beta0, real_t{ 0 } ) );
            SIXTRL_ASSERT( st::Type_comp_all_less_or_equal(
                this->beta0, real_t{ 1 } ) );

            real_t const delta_beta0 = this->beta0 * this->delta;

            SIXTRL_ASSERT(
                st::Type_comp_all_more_or_equal(
                    real_t{ 2 } * delta_beta0, real_t{ 0 } ) ||
                st::Type_comp_all_more_or_equal(
                    delta_beta0 * delta_beta0 + real_t{ 1 },
                    real_t{ -2 } * delta_beta0 ) );

            real_t const ptau_beta0 = sqrt( delta_beta0 * delta_beta0 +
                real_t{ 2 } * delta_beta0 + real_t{ 1 } ) - real_t{ 1 };

            return ptau_beta0 / this->beta0;
        }

        logic_t lost() const SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::Type_comp_not_equal( this->state, index_t{ 1 } );
        }

        logic_t not_lost() const SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::Type_comp_equal( this->state, index_t{ 1 } );
        }
    };

    /* ====================================================================== */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_x( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->x;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_px( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->px;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_y( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->y;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_py( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->py;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_zeta( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->zeta;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_delta( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->delta;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_psigma( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->psigma;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_s( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->s;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_rvv( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->rvv;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_chi( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->chi;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_charge_ratio( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->charge_ratio;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_charge0( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->charge0;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_mass0( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->mass0;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_beta0( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->beta0;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_gamma0( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->gamma0;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_const_existing_t
    Particle_pc0( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->pc0;
    }

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::index_const_existing_t
    Particle_state( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->state;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::index_const_existing_t
    Particle_at_element( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->at_element;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::index_const_existing_t
    Particle_at_turn( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->at_turn;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::index_const_existing_t
    Particle_id( SIXTRL_PARTICLE_ARGPTR_DEC const
        TParticleImpl< E, StoreT > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->id;
    }

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_t Particle_energy0(
        SIXTRL_PARTICLE_ARGPTR_DEC const TParticleImpl< E, StoreT > *const
            SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->energy0();
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_t Particle_energy(
        SIXTRL_PARTICLE_ARGPTR_DEC const TParticleImpl< E, StoreT > *const
            SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->energy();
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_t Particle_mass_ratio(
        SIXTRL_PARTICLE_ARGPTR_DEC const TParticleImpl< E, StoreT > *const
            SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->mass_ratio();
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_t Particle_mass(
        SIXTRL_PARTICLE_ARGPTR_DEC const TParticleImpl< E, StoreT > *const
            SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->mass();
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_t Particle_charge(
        SIXTRL_PARTICLE_ARGPTR_DEC const TParticleImpl< E, StoreT > *const
            SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->mass_charge();
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_t Particle_beta(
        SIXTRL_PARTICLE_ARGPTR_DEC const TParticleImpl< E, StoreT > *const
            SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->beta();
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_t Particle_gamma(
        SIXTRL_PARTICLE_ARGPTR_DEC const TParticleImpl< E, StoreT > *const
            SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->gamma();
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_t Particle_tau(
        SIXTRL_PARTICLE_ARGPTR_DEC const TParticleImpl< E, StoreT > *const
            SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->tau();
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_t Particle_sigma(
        SIXTRL_PARTICLE_ARGPTR_DEC const TParticleImpl< E, StoreT > *const
            SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->sigma();
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::real_t Particle_ptau(
        SIXTRL_PARTICLE_ARGPTR_DEC const TParticleImpl< E, StoreT > *const
            SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->ptau();
    }

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::logic_t Particle_lost(
        SIXTRL_PARTICLE_ARGPTR_DEC const TParticleImpl< E, StoreT > *const
            SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->lost();
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    typename TParticleImpl< E, StoreT >::logic_t Particle_not_lost(
        SIXTRL_PARTICLE_ARGPTR_DEC const TParticleImpl< E, StoreT > *const
            SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->not_lost();
    }

    /* ====================================================================== */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_x( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t x ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->x = x;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_add_to_x( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t delta_x
    ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->x += delta_x;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_y( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t y ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->y = y;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_add_to_y( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t delta_y ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->y += delta_y;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_px( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t px ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->px = px;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_add_to_px( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t delta_px ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->px += delta_px;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_scale_px( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t factor_px ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->px *= factor_px;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_py( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t py ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->py = py;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_add_to_py( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t delta_py ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->py += delta_py;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_scale_py( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t factor_py ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->py *= factor_py;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_zeta( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t zeta ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->zeta = zeta;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_add_to_zeta( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t delta_zeta ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->zeta += delta_zeta;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_scale_zeta( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t factor_zeta ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->zeta *= factor_zeta;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_delta( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t delta ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->delta = delta;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_add_to_delta( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t delta_delta ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->delta += delta_delta;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_scale_delta( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t factor_delta ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->delta *= factor_delta;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_psigma( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t psigma ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->psigma = psigma;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_add_to_psigma( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t delta_psigma ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->psigma += delta_psigma;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_scale_psigma( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t factor_psigma ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->psigma *= factor_psigma;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_s( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t s ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->s = s;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_add_to_s( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t delta_s ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->s += delta_s;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_rvv( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t rvv ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->rvv = rvv;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_scale_rvv( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t factor_rvv ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->rvv *= factor_rvv;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_rpp( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t rpp ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->rpp = rpp;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_scale_rpp( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t factor_rpp ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->rpp *= factor_rpp;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_chi( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t chi ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->chi = chi;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_scale_chi( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t factor_chi ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->chi *= factor_chi;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_charge_ratio( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t charge_ratio ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->charge_ratio = charge_ratio;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_scale_charge_ratio( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t factor_charge_ratio ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->charge_ratio *= factor_charge_ratio;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_charge0( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t charge0 ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->charge0 = charge0;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_mass0( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t mass0 ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->mass0 = mass0;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_beta0( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t beta0 ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->beta0 = beta0;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_gamma0( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t gamma0 ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->gamma0 = gamma0;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_pc0( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t pc0 ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->pc0 = pc0;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_state( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::index_arg_t state ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->state = state;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_at_element( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::index_arg_t at_element ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->at_element = at_element;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_increment_at_element( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::index_arg_t at_element ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        ++p->at_element;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_at_turn( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::index_arg_t at_turn ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->at_turn = at_turn;
    }

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_increment_at_turn( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::index_arg_t at_turn ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        ++p->at_turn;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_set_id( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::index_arg_t id ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->id = id;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

    /* TODO: Implement Particle_set_energy() function */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_add_to_energy( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p,
        typename TParticleImpl< E, StoreT >::real_arg_t delta_energy ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->add_to_energy( delta_energy );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

    /* TODO: Implement a Particle_mark_as_lost() function which
     *       generates the state from a supplied logic_t expression */

    template< class E, store_backend_t StoreT > static SIXTRL_INLINE SIXTRL_FN
    void Particle_mark_as_lost( SIXTRL_PARTICLE_ARGPTR_DEC
            TParticleImpl< E, StoreT >* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        p->state = typename TParticleImpl< E, StoreT >::index_t{ 0 };
    }

    /* ===================================================================== */
}


#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/obj_base_class.hpp"
    #include "sixtracklib/common/particle/storage_cobjects.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R,
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    using TDrift = TDriftImpl< DriftData< R, RAlign >, STORAGE_BE_COBJECTS >;

    typedef TDriftImpl< CDriftEquivData, STORAGE_BE_COBJECTS > Drift;
    typedef TDriftImpl< ::NS(Drift),     STORAGE_BE_COBJECTS > CDrift;
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_CXX_HPP__ */
