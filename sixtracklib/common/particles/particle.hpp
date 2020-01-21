#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/internal/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <cmath>
    #include <memory>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/obj_type_traits.hpp"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/buffer.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ObjData >
    class TParticle :
        public  SIXTRL_CXX_NAMESPACE::ObjConvertibleToCApiBase< ObjData >
    {
        private:

        typedef SIXTRL_CXX_NAMESPACE::ObjConvertibleToCApiBase< ObjData >
                _base_t;

        typedef SIXTRL_CXX_NAMESPACE::ParticleTraits< ObjData >
                _traits_t;

        public:

        typedef typename _base_t::c_api_t       c_api_t;
        typedef typename _base_t::cxx_api_t     cxx_api_t;

        typedef typename _traits_t::real_t      real_t;
        typedef typename _traits_t::real_ret_t  real_ret_t;
        typedef typename _traits_t::real_arg_t  real_arg_t;

        typedef typename _traits_t::index_t     index_t;
        typedef typename _traits_t::index_ret_t index_ret_t;
        typedef typename _traits_t::index_arg_t index_arg_t;

        SIXTRL_FN void init() SIXTRL_NOEXCEPT
        {
            this->x            = real_t{ 0.0 };
            this->px           = real_t{ 0.0 };
            this->y            = real_t{ 0.0 };
            this->py           = real_t{ 0.0 };
            this->zeta         = real_t{ 0.0 };
            this->delta        = real_t{ 0.0 };
            this->psigma       = real_t{ 0.0 };

            this->state        = index_t{ 1 };
            this->at_element   = index_t{ 0 };
            this->at_turn      = index_t{ 0 };
            this->id           = index_t{ 0 };

            this->s            = real_t{ 0.0 };
            this->rvv          = real_t{ 1.0 };
            this->rpp          = real_t{ 1.0 };
            this->chi          = real_t{ 1.0 };
            this->charge_ratio = real_t{ 1.0 };

            this->charge0      = real_t{ 1.0 };
            this->mass0        = real_t{ 1.0 }; /* TODO: Pmass!!! */
            this->beta0        = real_t{ 0.0 };
            this->gamma0       = real_t{ 1.0 };
            this->pc0          = real_t{ 0.0 };
        }
    };

    typedef TParticle< ::NS(Particle) > CParticle;

    typedef TParticle< ParticleData< ::NS(particle_real_t),
        ::NS(particle_index_t), std::size_t{ 8 },
            std::size_t{ 8 } > > Particle;

    /* ===================================================================== */

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_x(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->x;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_px(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->px;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_y(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->y;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_py(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->py;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_zeta(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->zeta;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_delta(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->delta;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_s(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->s;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_rvv(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->rvv;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_rpp(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->rpp;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_chi(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->chi;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_charge_ratio(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->charge_ratio;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_mass_ratio(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p )
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->charge_ratio / p->chi;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_beta(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p )
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->rvv * p->beta0;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::index_ret_t Particle_state(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->state;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::index_ret_t Particle_at_element(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->at_element;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::index_ret_t Particle_at_turn(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->at_turn;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::index_ret_t Particle_id(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->id;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_sigma(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p )
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->zeta / p->rvv;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_tau(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p )
    {
        SIXTRL_ASSERT( p != nullptr );
        return p->zeta / ( p->beta0 * p->rvv );
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_ptau(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p )
    {
        using std::sqrt;

        typedef typename SIXTRL_CXX_NAMESPACE::TParticle< ObjData >::real_t
                real_t;

        SIXTRL_ASSERT( p != nullptr );

        auto const delta_beta0( p->delta * p->delta0 );
        auto const ptau_delta0( sqrt( delta_beta0 * delta_beta0 +
            real_t{ 2. } * delta_beta0 + real_t{ 1. } ) - real_t{ 1. } );

        return ptau_delta0 / p->delta0;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_energy0(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p )
    {
        using std::sqrt;

        SIXTRL_ASSERT( p != nullptr );
        return sqrt( p->mass0 * p->mass0 + p->pc0 * p->pc0 );
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_energy(
        const TParticle< ObjData > *const SIXTRL_RESTRICT p )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( p != nullptr );

        return p->psigma * p->beta0 * p->pc0 +
            st::Patricle_energy0( p ) * st::Particle_mass_ratio( p );
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN void
    Particle_add_to_energy( TParticle< ObjData >* SIXTRL_RESTRICT p,
        typename TParticle< ObjData >::real_arg_t delta_energy )
    {
        using std::sqrt;

        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::TParticle< ObjData >::real_t real_t;

        SIXTRL_ASSERT( p != nullptr );

        static real_t const ONE = real_t{ 1.0 };
        static real_t const TWO = real_t{ 2.0 };

        auto const delta_beta0( p->delta * p->delta0 );
        auto const ptau_delta0( sqrt( delta_beta0 * delta_beta0 +
            TWO * delta_beta0 + ONE ) - ONE );

        auto const ptau( ptau_delta0 / p->delta0 );
        auto const psigma( ptau / p->delta0 );
        auto const delta( sqrt( ptau * ptau + TWO * psigma + ONE ) - ONE );

        auto const one_plus_delta( ONE + delta );
        auto const rvv( one_plus_delta / ( ONE + ptau_delta0 ) );

        p->delta = delta;
        p->sigma = psigma;
        p->zeta *= rvv / p->rvv;
        p->rvv   = rvv;
        p->rpp   = ONE / one_plus_delta;
    }

    /* ===================================================================== */

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_x(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.x;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_px(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.px;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_y(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.y;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_py(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.py;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_zeta(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.zeta;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_delta(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.delta;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_s(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.s;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_rvv(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.rvv;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_rpp(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.rpp;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_chi(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.chi;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_ret_t Particle_charge_ratio(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.charge_ratio;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_mass_ratio(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_mass_ratio(
            std::addressof( p ) );
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_beta(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_beta(
            std::addressof( p ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::index_ret_t Particle_state(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.state;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::index_ret_t Particle_at_element(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.at_element;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::index_ret_t Particle_at_turn(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.at_turn;
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::index_ret_t Particle_id(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p ) SIXTRL_NOEXCEPT
    {
        return p.id;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_sigma(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_sigma( std::addressof( p ) );
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_tau(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_tau( std::addressof( p ) );
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_ptau(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_ptau( std::addressof( p ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_energy0(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_energy0( std::addressof( p ) );
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    typename TParticle< ObjData >::real_t Particle_energy(
        TParticle< ObjData > const& SIXTRL_RESTRICT_REF p )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_energy( std::addressof( p ) );
    }

    template< class ObjData > SIXTRL_INLINE SIXTRL_FN
    void Particle_add_to_energy(
        TParticle< ObjData >& SIXTRL_RESTRICT_REF p,
        typename TParticle< ObjData >::real_arg_t delta_energy )
    {
        SIXTRL_CXX_NAMESPACE::Particle_add_to_energy(
            std::addressof( p ), delta_energy );
    }
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_CXX_HPP__ */
