#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_PARTICLE_API_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_PARTICLE_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle_unit.h"
    #include "sixtracklib/common/particles/particle_unit_api.h"
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/particles/particle_set_helper_api.h"
    #include "sixtracklib/common/particles/particle_set_api.h"
    #include "sixtracklib/common/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
    #if !defined( SIXTRL_NO_INCLUDES )
        #include "sixtracklib/common/particles/particle_unit.hpp"
        #include "sixtracklib/common/particles/particle_set.hpp"
    #endif /* !defined( SIXTRL_NO_INCLUDES ) */
#endif /* defined( __cplusplus ) */

#if defined( __cplusplus )
#include <iostream>

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleSetT, class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >() ||
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_store_to_particle(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( pset ),
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT*
            SIXTRL_RESTRICT SIXTRL_UNUSED( p ),
        particle_num_elements_t const SIXTRL_UNUSED( idx ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleSetT, class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_store_to_particle(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const
            SIXTRL_RESTRICT pset,
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        particle_num_elements_t const idx )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( pset != SIXTRL_NULLPTR ) && ( p != SIXTRL_NULLPTR ) &&
            ( idx < st::ParticleSet_num_particles( pset ) ) )
        {
            status  = st::Particle_set_x( p, st::ParticleSet_x( pset, idx ) );
            status |= st::Particle_set_px( p, st::ParticleSet_px( pset, idx ) );
            status |= st::Particle_set_y( p, st::ParticleSet_y( pset, idx ) );
            status |= st::Particle_set_py( p, st::ParticleSet_py( pset, idx ) );
            status |= st::Particle_set_zeta( p,
                        st::ParticleSet_zeta( pset, idx ) );
            status |= st::Particle_set_delta( p,
                        st::ParticleSet_delta( pset, idx ) );

            status |= st::Particle_set_state( p,
                        st::ParticleSet_state( pset, idx ) );
            status |= st::Particle_set_at_element( p,
                        st::ParticleSet_at_element( pset, idx ) );
            status |= st::Particle_set_at_turn( p,
                        st::ParticleSet_at_turn( pset, idx ) );
            status |= st::Particle_set_id( p,
                        st::ParticleSet_particle_id( pset, idx ) );

            status |= st::Particle_set_psigma( p,
                        st::ParticleSet_psigma( pset, idx ) );
            status |= st::Particle_set_rpp( p,
                        st::ParticleSet_rpp( pset, idx ) );
            status |= st::Particle_set_rvv( p,
                        st::ParticleSet_rvv( pset, idx ) );
            status |= st::Particle_set_chi( p,
                        st::ParticleSet_chi( pset, idx ) );
            status |= st::Particle_set_charge_ratio( p,
                        st::ParticleSet_charge_ratio( pset, idx ) );

            status |= st::Particle_set_charge0( p,
                        st::ParticleSet_charge0( pset, idx ) );
            status |= st::Particle_set_mass0( p,
                        st::ParticleSet_mass0( pset, idx ) );
            status |= st::Particle_set_beta0( p,
                        st::ParticleSet_beta0( pset, idx ) );
            status |= st::Particle_set_gamma0( p,
                        st::ParticleSet_gamma0( pset, idx ) );
            status |= st::Particle_set_pc0( p,
                        st::ParticleSet_pc0( pset, idx ) );

            status |= st::Particle_set_s( p, st::ParticleSet_s( pset, idx ) );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    template< class ParticleSetT, class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >() ||
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_load_from_particle(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT*
            SIXTRL_RESTRICT SIXTRL_UNUSED( pset ),
        SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( p ),
        particle_num_elements_t const SIXTRL_UNUSED( idx ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleSetT, class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< ParticleSetT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_load_from_particle(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT pset,
        SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const SIXTRL_RESTRICT p,
        particle_num_elements_t const idx )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( pset != SIXTRL_NULLPTR ) && ( p != SIXTRL_NULLPTR ) &&
            ( idx < st::ParticleSet_num_particles( pset ) ) )
        {
            status = st::ParticleSet_set_x_value(
                        pset, idx, st::Particle_x( p ) );
            status |= st::ParticleSet_set_px_value(
                        pset, idx, st::Particle_px( p ) );
            status |= st::ParticleSet_set_y_value(
                        pset, idx, st::Particle_y( p ) );
            status |= st::ParticleSet_set_py_value(
                        pset, idx, st::Particle_py( p ) );
            status |= st::ParticleSet_set_zeta_value(
                        pset, idx, st::Particle_zeta( p ) );
            status |= st::ParticleSet_set_delta_value(
                        pset, idx, st::Particle_delta( p ) );

            status |= st::ParticleSet_set_state_value(
                        pset, idx, st::Particle_state( p ) );
            status |= st::ParticleSet_set_at_element_value(
                        pset, idx, st::Particle_at_element( p ) );
            status |= st::ParticleSet_set_at_turn_value(
                        pset, idx, st::Particle_at_turn( p ) );
            status |= st::ParticleSet_set_particle_id_value(
                        pset, idx, st::Particle_id( p ) );

            status |= st::ParticleSet_set_psigma_value(
                        pset, idx, st::Particle_psigma( p ) );
            status |= st::ParticleSet_set_rpp_value(
                        pset, idx, st::Particle_rpp( p ) );
            status |= st::ParticleSet_set_rvv_value(
                        pset, idx, st::Particle_rvv( p ) );
            status |= st::ParticleSet_set_chi_value(
                        pset, idx, st::Particle_chi( p ) );
            status |= st::ParticleSet_set_charge_ratio_value(
                        pset, idx, st::Particle_charge_ratio( p ) );

            status |= st::ParticleSet_set_charge0_value(
                        pset, idx, st::Particle_charge0( p ) );
            status |= st::ParticleSet_set_mass0_value(
                        pset, idx, st::Particle_mass0( p ) );
            status |= st::ParticleSet_set_beta0_value(
                        pset, idx, st::Particle_beta0( p ) );
            status |= st::ParticleSet_set_gamma0_value(
                        pset, idx, st::Particle_gamma0( p ) );
            status |= st::ParticleSet_set_pc0_value(
                        pset, idx, st::Particle_pc0( p ) );

            status |= st::ParticleSet_set_s_value(
                        pset, idx, st::Particle_s( p ) );
        }

        return status;
    }
}

template< class ParticleSetT, class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ParticleSet_store_to_particle)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const ParticleSetT *const SIXTRL_RESTRICT pset,
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    SIXTRL_CXX_NAMESPACE::particle_num_elements_t const idx )
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_store_to_particle( pset, p, idx );
}

template< class ParticleSetT, class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ParticleSet_load_from_particle)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC ParticleSetT* SIXTRL_RESTRICT pset,
    SIXTRL_PARTICLE_ARGPTR_DEC const ParticleT *const SIXTRL_RESTRICT p,
    SIXTRL_CXX_NAMESPACE::particle_num_elements_t const idx )
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_load_from_particle( pset, p, idx );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSet_store_to_particle)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT pset,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSet_load_from_particle)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const idx ) SIXTRL_NOEXCEPT;


#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!          Implementation of inline methods and functions        !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_store_to_particle)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT pset,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const idx ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( pset != SIXTRL_NULLPTR ) && ( p != SIXTRL_NULLPTR ) &&
        ( idx < NS(ParticleSet_num_particles)( pset ) ) )
    {
        status  = NS(Particle_set_x)( p, NS(ParticleSet_x)( pset, idx ) );
        status |= NS(Particle_set_px)( p, NS(ParticleSet_px)( pset, idx ) );
        status |= NS(Particle_set_y)( p, NS(ParticleSet_y)( pset, idx ) );
        status |= NS(Particle_set_py)( p, NS(ParticleSet_py)( pset, idx ) );
        status |= NS(Particle_set_zeta)( p, NS(ParticleSet_zeta)( pset, idx ) );
        status |= NS(Particle_set_delta)(
            p, NS(ParticleSet_delta)( pset, idx ) );

        status |= NS(Particle_set_state)(
            p, NS(ParticleSet_state)( pset, idx ) );
        status |= NS(Particle_set_at_element)(
            p, NS(ParticleSet_at_element)( pset, idx ) );
        status |= NS(Particle_set_at_turn)(
            p, NS(ParticleSet_at_turn)( pset, idx ) );
        status |= NS(Particle_set_id)(
            p, NS(ParticleSet_particle_id)( pset, idx ) );

        status |= NS(Particle_set_psigma)(
            p, NS(ParticleSet_psigma)( pset, idx ) );
        status |= NS(Particle_set_rpp)( p, NS(ParticleSet_rpp)( pset, idx ) );
        status |= NS(Particle_set_rvv)( p, NS(ParticleSet_rvv)( pset, idx ) );
        status |= NS(Particle_set_chi)( p, NS(ParticleSet_chi)( pset, idx ) );
        status |= NS(Particle_set_charge_ratio)(
            p, NS(ParticleSet_charge_ratio)( pset, idx ) );

        status |= NS(Particle_set_charge0)(
            p, NS(ParticleSet_charge0)( pset, idx ) );
        status |= NS(Particle_set_mass0)(
            p, NS(ParticleSet_mass0)( pset, idx ) );
        status |= NS(Particle_set_beta0)(
            p, NS(ParticleSet_beta0)( pset, idx ) );
        status |= NS(Particle_set_gamma0)(
            p, NS(ParticleSet_gamma0)( pset, idx ) );
        status |= NS(Particle_set_pc0)(
            p, NS(ParticleSet_pc0)( pset, idx ) );

        status |= NS(Particle_set_s)( p, NS(ParticleSet_s)( pset, idx ) );
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_load_from_particle)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const idx ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( pset != SIXTRL_NULLPTR ) && ( p != SIXTRL_NULLPTR ) &&
        ( idx < NS(ParticleSet_num_particles)( pset ) ) )
    {
        status = NS(ParticleSet_set_x_value)( pset, idx, NS(Particle_x)( p ) );
        status |= NS(ParticleSet_set_px_value)(
            pset, idx, NS(Particle_px)( p ) );
        status |= NS(ParticleSet_set_y_value)( pset, idx, NS(Particle_y)( p ) );
        status |= NS(ParticleSet_set_py_value)(
            pset, idx, NS(Particle_py)( p ) );
        status |= NS(ParticleSet_set_zeta_value)(
            pset, idx, NS(Particle_zeta)( p ) );
        status |= NS(ParticleSet_set_delta_value)(
                    pset, idx, NS(Particle_delta)( p ) );

        status |= NS(ParticleSet_set_state_value)(
                    pset, idx, NS(Particle_state)( p ) );
        status |= NS(ParticleSet_set_at_element_value)(
                    pset, idx, NS(Particle_at_element)( p ) );
        status |= NS(ParticleSet_set_at_turn_value)(
                    pset, idx, NS(Particle_at_turn)( p ) );
        status |= NS(ParticleSet_set_particle_id_value)(
                    pset, idx, NS(Particle_id)( p ) );

        status |= NS(ParticleSet_set_psigma_value)(
                    pset, idx, NS(Particle_psigma)( p ) );
        status |= NS(ParticleSet_set_rpp_value)(
                    pset, idx, NS(Particle_rpp)( p ) );
        status |= NS(ParticleSet_set_rvv_value)(
                    pset, idx, NS(Particle_rvv)( p ) );
        status |= NS(ParticleSet_set_chi_value)(
                    pset, idx, NS(Particle_chi)( p ) );
        status |= NS(ParticleSet_set_charge_ratio_value)(
                    pset, idx, NS(Particle_charge_ratio)( p ) );

        status |= NS(ParticleSet_set_charge0_value)(
                    pset, idx, NS(Particle_charge0)( p ) );
        status |= NS(ParticleSet_set_mass0_value)(
                    pset, idx, NS(Particle_mass0)( p ) );
        status |= NS(ParticleSet_set_beta0_value)(
                    pset, idx, NS(Particle_beta0)( p ) );
        status |= NS(ParticleSet_set_gamma0_value)(
                    pset, idx, NS(Particle_gamma0)( p ) );
        status |= NS(ParticleSet_set_pc0_value)(
                    pset, idx, NS(Particle_pc0)( p ) );

        status |= NS(ParticleSet_set_s_value)( pset, idx, NS(Particle_s)( p ) );
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_PARTICLE_API_H__ */
