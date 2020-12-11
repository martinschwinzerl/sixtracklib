#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_INIT_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_INIT_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/particles/particle_set_api.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/compiler_compability.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* >::type
    ParticleSet_preset( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_NULLPTR;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_default< PSetT >(),
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* >::type
    ParticleSet_preset( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        if( pset != SIXTRL_NULLPTR )
        {
            st::arch_status_t status = st::ARCH_STATUS_SUCCESS;

            status |= st::ParticleSet_set_default_capacity( pset );
            status |= st::ParticleSet_set_default_num_particles( pset );

            status |= st::ParticleSet_set_default_charge0_addr( pset );
            status |= st::ParticleSet_set_default_mass0_addr( pset );
            status |= st::ParticleSet_set_default_beta0_addr( pset );
            status |= st::ParticleSet_set_default_gamma0_addr( pset );
            status |= st::ParticleSet_set_default_pc0_addr( pset );

            status |= st::ParticleSet_set_default_s_addr( pset );
            status |= st::ParticleSet_set_default_x_addr( pset );
            status |= st::ParticleSet_set_default_px_addr( pset );
            status |= st::ParticleSet_set_default_y_addr( pset );
            status |= st::ParticleSet_set_default_py_addr( pset );
            status |= st::ParticleSet_set_default_zeta_addr( pset );
            status |= st::ParticleSet_set_default_delta_addr( pset );

            status |= st::ParticleSet_set_default_psigma_addr( pset );
            status |= st::ParticleSet_set_default_rpp_addr( pset );
            status |= st::ParticleSet_set_default_rvv_addr( pset );
            status |= st::ParticleSet_set_default_chi_addr( pset );
            status |= st::ParticleSet_set_default_charge_ratio_addr( pset );

            status |= st::ParticleSet_set_default_state_addr( pset );
            status |= st::ParticleSet_set_default_at_element_addr( pset );
            status |= st::ParticleSet_set_default_at_turn_addr( pset );
            status |= st::ParticleSet_set_default_particle_id_addr( pset );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        return pset;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_init(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT
            SIXTRL_UNUSED( pset ),
        particle_num_elements_t const SIXTRL_UNUSED( num_particles ),
        particle_num_elements_t SIXTRL_UNUSED( capacity ) =
            particle_num_elements_t{ 0 } )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }


    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_default< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_init(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
        particle_num_elements_t const num_particles,
        particle_num_elements_t capacity = particle_num_elements_t{ 0 } )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( num_particles >= st::particle_num_elements_t{ 0 } );
        if( capacity < num_particles ) capacity = num_particles;
        st::arch_status_t status = st::ARCH_STATUS_SUCCESS;

        status |= st::ParticleSet_set_capacity( pset, capacity );
        status |= st::ParticleSet_set_num_particles( pset, num_particles );

        status |= st::ParticleSet_set_default_charge0_addr( pset );
        status |= st::ParticleSet_set_default_mass0_addr( pset );
        status |= st::ParticleSet_set_default_beta0_addr( pset );
        status |= st::ParticleSet_set_default_gamma0_addr( pset );
        status |= st::ParticleSet_set_default_pc0_addr( pset );

        status |= st::ParticleSet_set_default_s_addr( pset );
        status |= st::ParticleSet_set_default_x_addr( pset );
        status |= st::ParticleSet_set_default_px_addr( pset );
        status |= st::ParticleSet_set_default_y_addr( pset );
        status |= st::ParticleSet_set_default_py_addr( pset );
        status |= st::ParticleSet_set_default_zeta_addr( pset );
        status |= st::ParticleSet_set_default_delta_addr( pset );

        status |= st::ParticleSet_set_default_psigma_addr( pset );
        status |= st::ParticleSet_set_default_rpp_addr( pset );
        status |= st::ParticleSet_set_default_rvv_addr( pset );
        status |= st::ParticleSet_set_default_chi_addr( pset );
        status |= st::ParticleSet_set_default_charge_ratio_addr( pset );

        status |= st::ParticleSet_set_default_state_addr( pset );
        status |= st::ParticleSet_set_default_at_element_addr( pset );
        status |= st::ParticleSet_set_default_at_turn_addr( pset );
        status |= st::ParticleSet_set_default_particle_id_addr( pset );

        return status;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_init_detailed(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
            SIXTRL_RESTRICT SIXTRL_UNUSED( pset ),
        particle_num_elements_t const SIXTRL_UNUSED( num_particles ),
        particle_addr_t const SIXTRL_UNUSED( x_addr ),
        particle_addr_t const SIXTRL_UNUSED( px_addr ),
        particle_addr_t const SIXTRL_UNUSED( y_addr ),
        particle_addr_t const SIXTRL_UNUSED( py_addr ),
        particle_addr_t const SIXTRL_UNUSED( zeta_addr ),
        particle_addr_t const SIXTRL_UNUSED( delta_addr ),
        particle_addr_t const SIXTRL_UNUSED( state_addr ),
        particle_addr_t const SIXTRL_UNUSED( at_element_addr ),
        particle_addr_t const SIXTRL_UNUSED( at_turn_addr ),
        particle_addr_t const SIXTRL_UNUSED( particle_id_addr ),
        particle_addr_t const SIXTRL_UNUSED( psigma_addr ),
        particle_addr_t const SIXTRL_UNUSED( rpp_addr ),
        particle_addr_t const SIXTRL_UNUSED( rvv_addr ),
        particle_addr_t const SIXTRL_UNUSED( chi_addr ),
        particle_addr_t const SIXTRL_UNUSED( charge_ratio_addr ),
        particle_addr_t const SIXTRL_UNUSED( charge0_addr ),
        particle_addr_t const SIXTRL_UNUSED( mass0_addr ),
        particle_addr_t const SIXTRL_UNUSED( beta0_addr ),
        particle_addr_t const SIXTRL_UNUSED( gamma0_addr ),
        particle_addr_t const SIXTRL_UNUSED( pc0_addr ),
        particle_addr_t const SIXTRL_UNUSED( s_addr ),
        particle_num_elements_t SIXTRL_UNUSED( capacity ) =
            particle_num_elements_t{ 0 }
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        ( SIXTRL_CXX_NAMESPACE::ParticleSet_impl_default< PSetT >() ||
          SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >() ),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_init_detailed(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
        particle_num_elements_t const num_particles,
        particle_addr_t const x_addr,
        particle_addr_t const px_addr,
        particle_addr_t const y_addr,
        particle_addr_t const py_addr,
        particle_addr_t const zeta_addr,
        particle_addr_t const delta_addr,
        particle_addr_t const state_addr,
        particle_addr_t const at_element_addr,
        particle_addr_t const at_turn_addr,
        particle_addr_t const particle_id_addr,
        particle_addr_t const psigma_addr,
        particle_addr_t const rpp_addr,
        particle_addr_t const rvv_addr,
        particle_addr_t const chi_addr,
        particle_addr_t const charge_ratio_addr,
        particle_addr_t const charge0_addr,
        particle_addr_t const mass0_addr,
        particle_addr_t const beta0_addr,
        particle_addr_t const gamma0_addr,
        particle_addr_t const pc0_addr,
        particle_addr_t const s_addr,
        particle_num_elements_t capacity = particle_num_elements_t{ 0 }
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_SUCCESS;

        SIXTRL_ASSERT( num_particles >= st::particle_num_elements_t{ 0 } );
        if( capacity <= num_particles ) capacity = num_particles;

        status |= st::ParticleSet_set_capacity( pset, capacity );
        status |= st::ParticleSet_set_num_particles( pset, num_particles );

        status |= st::ParticleSet_set_x_addr( pset, x_addr );
        status |= st::ParticleSet_set_px_addr( pset, px_addr );
        status |= st::ParticleSet_set_y_addr( pset, y_addr );
        status |= st::ParticleSet_set_py_addr( pset, py_addr );
        status |= st::ParticleSet_set_zeta_addr( pset, zeta_addr );
        status |= st::ParticleSet_set_delta_addr( pset, delta_addr );

        status |= st::ParticleSet_set_state_addr( pset, state_addr );
        status |= st::ParticleSet_set_at_element_addr( pset, at_element_addr );
        status |= st::ParticleSet_set_at_turn_addr( pset, at_turn_addr );
        status |= st::ParticleSet_set_particle_id_addr(
            pset, particle_id_addr );

        status |= st::ParticleSet_set_psigma_addr( pset, psigma_addr );
        status |= st::ParticleSet_set_rpp_addr( pset, rpp_addr );
        status |= st::ParticleSet_set_rvv_addr( pset, rvv_addr );
        status |= st::ParticleSet_set_chi_addr( pset, chi_addr );
        status |= st::ParticleSet_set_charge_ratio_addr(
            pset, charge_ratio_addr );

        status |= st::ParticleSet_set_charge0_addr( pset, charge0_addr );
        status |= st::ParticleSet_set_mass0_addr( pset, mass0_addr );
        status |= st::ParticleSet_set_beta0_addr( pset, beta0_addr );
        status |= st::ParticleSet_set_gamma0_addr( pset, gamma0_addr );
        status |= st::ParticleSet_set_pc0_addr( pset, pc0_addr );

        status |= st::ParticleSet_set_s_addr( pset, s_addr );

        return status;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class PSetT, typename XIter, typename PxIter, typename YIter,
              typename PyIter, typename ZetaIter, typename DeltaIter,
              typename StateIter, typename AtElemIter, typename AtTurnIter,
              typename IdIter, typename PSigmaIter, typename RppIter,
              typename RvvIter, typename ChiIter, typename ChargeRatioIter,
              typename Charge0Iter, typename Mass0Iter, typename Beta0Iter,
              typename Gamma0Iter, typename Pc0Iter, typename SIter >
     SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::is_iterator< XIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< PxIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< YIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< PyIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< ZetaIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< DeltaIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< StateIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< AtElemIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< AtTurnIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< IdIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< PSigmaIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< RppIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< RvvIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< ChiIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< ChargeRatioIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< Charge0Iter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< Mass0Iter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< Beta0Iter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< Gamma0Iter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< Pc0Iter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< SIter >::value,
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_init_detailed( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
            SIXTRL_RESTRICT SIXTRL_UNUSED( pset ),
        particle_num_elements_t const SIXTRL_UNUSED( num_particles ),
        XIter SIXTRL_UNUSED( x_begin ), PxIter SIXTRL_UNUSED( px_begin ),
        YIter SIXTRL_UNUSED( y_begin ), PyIter SIXTRL_UNUSED( py_begin ),
        ZetaIter SIXTRL_UNUSED( zeta_begin ),
        DeltaIter SIXTRL_UNUSED( delta_begin ),
        StateIter SIXTRL_UNUSED( state_begin ),
        AtElemIter SIXTRL_UNUSED( at_elem_begin ),
        AtTurnIter SIXTRL_UNUSED( at_turn_begin ),
        IdIter SIXTRL_UNUSED( id_begin ),
        PSigmaIter SIXTRL_UNUSED( psigma_begin ),
        RppIter SIXTRL_UNUSED( rpp_begin ), RvvIter SIXTRL_UNUSED( rvv_begin ),
        ChiIter SIXTRL_UNUSED( chi_begin ),
        ChargeRatioIter SIXTRL_UNUSED( charge_ratio_begin ),
        Charge0Iter SIXTRL_UNUSED( charge0_begin ),
        Mass0Iter SIXTRL_UNUSED( mass0_begin ),
        Beta0Iter SIXTRL_UNUSED( beta0_begin ),
        Gamma0Iter SIXTRL_UNUSED( gamma0_begin ),
        Pc0Iter SIXTRL_UNUSED( pc0_begin ), SIter SIXTRL_UNUSED( s_begin ),
        particle_num_elements_t SIXTRL_UNUSED( capacity ) =
            particle_num_elements_t{ 0 } ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT, typename XIter, typename PxIter, typename YIter,
              typename PyIter, typename ZetaIter, typename DeltaIter,
              typename StateIter, typename AtElemIter, typename AtTurnIter,
              typename IdIter, typename PSigmaIter, typename RppIter,
              typename RvvIter, typename ChiIter, typename ChargeRatioIter,
              typename Charge0Iter, typename Mass0Iter, typename Beta0Iter,
              typename Gamma0Iter, typename Pc0Iter, typename SIter >
     SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_default< PSetT >() &&
        std::is_pointer< XIter >::value &&
        std::is_pointer< PxIter >::value &&
        std::is_pointer< YIter >::value &&
        std::is_pointer< PyIter >::value &&
        std::is_pointer< ZetaIter >::value &&
        std::is_pointer< DeltaIter >::value &&
        std::is_pointer< StateIter >::value &&
        std::is_pointer< AtElemIter >::value &&
        std::is_pointer< AtTurnIter >::value &&
        std::is_pointer< IdIter >::value &&
        std::is_pointer< PSigmaIter >::value &&
        std::is_pointer< RppIter >::value &&
        std::is_pointer< RvvIter >::value &&
        std::is_pointer< ChiIter >::value &&
        std::is_pointer< ChargeRatioIter >::value &&
        std::is_pointer< Charge0Iter >::value &&
        std::is_pointer< Mass0Iter >::value &&
        std::is_pointer< Beta0Iter >::value &&
        std::is_pointer< Gamma0Iter >::value &&
        std::is_pointer< Pc0Iter >::value &&
        std::is_pointer< SIter >::value,
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_init_detailed(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
        particle_num_elements_t const num_particles,
        XIter x_begin, PxIter px_begin, YIter y_begin, PyIter py_begin,
        ZetaIter zeta_begin, DeltaIter delta_begin, StateIter state_begin,
        AtElemIter at_elem_begin, AtTurnIter at_turn_begin, IdIter id_begin,
        PSigmaIter psigma_begin, RppIter rpp_begin, RvvIter rvv_begin,
        ChiIter chi_begin, ChargeRatioIter charge_ratio_begin,
        Charge0Iter charge0_begin, Mass0Iter mass0_begin, Beta0Iter beta0_begin,
        Gamma0Iter gamma0_begin, Pc0Iter pc0_begin, SIter s_begin,
        particle_num_elements_t capacity = particle_num_elements_t{ 0 } )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_SUCCESS;

        SIXTRL_ASSERT( num_particles >= st::particle_num_elements_t{ 0 } );
        if( capacity <= num_particles ) capacity = num_particles;

        status |= st::ParticleSet_set_capacity( pset, capacity );
        status |= st::ParticleSet_set_num_particles( pset, num_particles );

        status |= st::ParticleSet_set_x_addr( pset,
                  reinterpret_cast< std::uintptr_t >( x_begin ) );
        status |= st::ParticleSet_set_px_addr( pset,
                  reinterpret_cast< std::uintptr_t >( px_begin ) );
        status |= st::ParticleSet_set_y_addr( pset,
                  reinterpret_cast< std::uintptr_t >( y_begin ) );
        status |= st::ParticleSet_set_py_addr( pset,
                  reinterpret_cast< std::uintptr_t >( py_begin ) );
        status |= st::ParticleSet_set_zeta_addr( pset,
                  reinterpret_cast< std::uintptr_t >( zeta_begin ) );
        status |= st::ParticleSet_set_delta_addr( pset,
                  reinterpret_cast< std::uintptr_t >( delta_begin ) );
        status |= st::ParticleSet_set_state_addr( pset,
                  reinterpret_cast< std::uintptr_t >( state_begin ) );
        status |= st::ParticleSet_set_at_element_addr( pset,
                  reinterpret_cast< std::uintptr_t >( at_elem_begin ) );
        status |= st::ParticleSet_set_at_turn_addr( pset,
                  reinterpret_cast< std::uintptr_t >( at_turn_begin ) );
        status |= st::ParticleSet_set_particle_id_addr( pset,
                  reinterpret_cast< std::uintptr_t >( id_begin ) );

        status |= st::ParticleSet_set_psigma_addr( pset,
                  reinterpret_cast< std::uintptr_t >( psigma_begin ) );
        status |= st::ParticleSet_set_rpp_addr( pset,
                  reinterpret_cast< std::uintptr_t >( rpp_begin ) );
        status |= st::ParticleSet_set_rvv_addr( pset,
                  reinterpret_cast< std::uintptr_t >( rvv_begin ) );
        status |= st::ParticleSet_set_chi_addr( pset,
                  reinterpret_cast< std::uintptr_t >( chi_begin ) );
        status |= st::ParticleSet_set_charge_ratio_addr( pset,
                  reinterpret_cast< std::uintptr_t >( charge_ratio_begin ) );

        status |= st::ParticleSet_set_charge0_addr( pset,
                  reinterpret_cast< std::uintptr_t >( charge0_begin ) );
        status |= st::ParticleSet_set_mass0_addr( pset,
                  reinterpret_cast< std::uintptr_t >( mass0_begin ) );
        status |= st::ParticleSet_set_beta0_addr( pset,
                  reinterpret_cast< std::uintptr_t >( beta0_begin ) );
        status |= st::ParticleSet_set_gamma0_addr( pset,
                  reinterpret_cast< std::uintptr_t >( gamma0_begin ) );
        status |= st::ParticleSet_set_pc0_addr( pset,
                  reinterpret_cast< std::uintptr_t >( pc0_begin ) );

        status |= st::ParticleSet_set_s_addr( pset,
                  reinterpret_cast< std::uintptr_t >( s_begin ) );

        return status;
    }

    /* --------------------------------------------------------------------- */

    template< class PSetT, typename XArg, typename PxArg, typename YArg,
              typename PyArg, typename ZetaArg, typename DeltaArg,
              typename StateArg, typename AtElemArg, typename AtTurnArg,
              typename IdArg, typename PSigmaArg, typename RppArg,
              typename RvvArg, typename ChiArg, typename ChargeRatioArg,
              typename Charge0Arg, typename Mass0Arg, typename Beta0Arg,
              typename Gamma0Arg, typename Pc0Arg, typename SArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_init(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
        particle_num_elements_t const num_particles,
        XArg x_values, PxArg px_values, YArg y_values, PyArg py_values,
        ZetaArg zeta_values, DeltaArg delta_values,
        StateArg state_values, AtElemArg at_element_values,
        AtTurnArg at_turn_values, IdArg id_values,
        PSigmaArg psigma_values, RppArg rpp_values, RvvArg rvv_values,
        ChiArg chi_values, ChargeRatioArg charge_ratio_values,
        Charge0Arg charge0_values, Mass0Arg mass0_values, Beta0Arg beta0_values,
        Gamma0Arg gamma0_values, Pc0Arg pc0_values, SArg s_values,
        particle_num_elements_t capacity = particle_num_elements_t{ 0 }
    )
    {
        return SIXTRL_CXX_NAMESPACE::ParticleSet_init_detailed(
            pset, num_particles, x_values, px_values, y_values, py_values,
                zeta_values, delta_values, state_values, at_element_values,
                    at_turn_values, id_values, psigma_values, rpp_values,
                        rvv_values, chi_values, charge_ratio_values,
                            charge0_values, mass0_values, beta0_values,
                                gamma0_values, pc0_values, s_values, capacity );
    }

    /* ********************************************************************* */

    template< class PSetT, store_backend_t StoreT >
    struct ObjDataInitialiser< PSetT, StoreT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            void >::type >
    {
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* preset(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT obj )
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_preset( obj );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t init( SIXTRL_ARGPTR_DEC PSetT*
            SIXTRL_RESTRICT obj, Args&&... init_args ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_init(
                obj, std::forward< Args >( init_args )... );
        }
    };

}

/* ===================================================================== */

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
NS(ParticleSet_preset)( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_preset( pset );
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ParticleSet_init_detailed)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
    SIXTRL_CXX_NAMESPACE::particle_num_elements_t const num_particles,
    SIXTRL_CXX_NAMESPACE::particle_addr_t const x_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const px_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const y_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const py_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const zeta_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const delta_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const state_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const at_element_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const at_turn_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const particle_id_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const psigma_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const rpp_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const rvv_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const chi_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const charge_ratio_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const charge0_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const mass0_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const beta0_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const gamma0_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const pc0_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const s_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_num_elements_t const capacity =
            SIXTRL_CXX_NAMESPACE::particle_num_elements_t{ 0 } ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_init_detailed( pset, num_particles,
        x_addr, px_addr, y_addr, py_addr, zeta_addr, delta_addr, state_addr,
            at_element_addr, at_turn_addr, particle_id_addr, psigma_addr,
                rpp_addr, rvv_addr, chi_addr, charge_ratio_addr, charge0_addr,
                    mass0_addr, beta0_addr, gamma0_addr, pc0_addr, s_addr,
                        capacity );
}

/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ParticleSet_init)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
    SIXTRL_CXX_NAMESPACE::particle_num_elements_t const num_particles,
    SIXTRL_CXX_NAMESPACE::particle_addr_t const x_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const px_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const y_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const py_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const zeta_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const delta_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const state_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const at_element_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const at_turn_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const particle_id_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const psigma_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const rpp_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const rvv_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const chi_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const charge_ratio_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const charge0_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const mass0_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const beta0_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const gamma0_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const pc0_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
    SIXTRL_CXX_NAMESPACE::particle_addr_t const s_addr =
        SIXTRL_CXX_NAMESPACE::particle_addr_t{ 0 },
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t const capacity =
            SIXTRL_CXX_NAMESPACE::particle_num_elements_t{ 0 } ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_init( pset, num_particles,
        x_addr, px_addr, y_addr, py_addr, zeta_addr, delta_addr, state_addr,
            at_element_addr, at_turn_addr, particle_id_addr, psigma_addr,
                rpp_addr, rvv_addr, chi_addr, charge_ratio_addr, charge0_addr,
                    mass0_addr, beta0_addr, gamma0_addr, pc0_addr, s_addr,
                        capacity );
}

#endif /* C++ */


#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */


SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)*
NS(ParticleSet_preset)( SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSet_init)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_num_elements_t) const capacity ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSet_init_detailed)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_num_elements_t) const num_particles,
    NS(particle_addr_t) const x_addr,
    NS(particle_addr_t) const px_addr,
    NS(particle_addr_t) const y_addr,
    NS(particle_addr_t) const py_addr,
    NS(particle_addr_t) const zeta_addr,
    NS(particle_addr_t) const delta_addr,
    NS(particle_addr_t) const state_addr,
    NS(particle_addr_t) const at_element_addr,
    NS(particle_addr_t) const at_turn_addr,
    NS(particle_addr_t) const particle_id_addr,
    NS(particle_addr_t) const psigma_addr,
    NS(particle_addr_t) const rpp_addr,
    NS(particle_addr_t) const rvv_addr,
    NS(particle_addr_t) const chi_addr,
    NS(particle_addr_t) const charge_ratio_addr,
    NS(particle_addr_t) const charge0_addr,
    NS(particle_addr_t) const mass0_addr,
    NS(particle_addr_t) const beta0_addr,
    NS(particle_addr_t) const gamma0_addr,
    NS(particle_addr_t) const pc0_addr,
    NS(particle_addr_t) const s_addr,
    NS(particle_num_elements_t) capacity ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)*
NS(ParticleSet_preset)( SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)*
    SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
{
    if( pset != SIXTRL_NULLPTR )
    {
        NS(arch_status_t) status =
            NS(ParticleSet_set_default_num_particles)( pset );

        status |= NS(ParticleSet_set_default_x_addr)( pset );
        status |= NS(ParticleSet_set_default_px_addr)( pset );
        status |= NS(ParticleSet_set_default_y_addr)( pset );
        status |= NS(ParticleSet_set_default_py_addr)( pset );
        status |= NS(ParticleSet_set_default_zeta_addr)( pset );
        status |= NS(ParticleSet_set_default_delta_addr)( pset );

        status |= NS(ParticleSet_set_default_state_addr)( pset );
        status |= NS(ParticleSet_set_default_at_element_addr)( pset );
        status |= NS(ParticleSet_set_default_at_turn_addr)( pset );
        status |= NS(ParticleSet_set_default_particle_id_addr)( pset );

        status |= NS(ParticleSet_set_default_psigma_addr)( pset );
        status |= NS(ParticleSet_set_default_rpp_addr)( pset );
        status |= NS(ParticleSet_set_default_rvv_addr)( pset );
        status |= NS(ParticleSet_set_default_chi_addr)( pset );
        status |= NS(ParticleSet_set_default_charge_ratio_addr)( pset );

        status |= NS(ParticleSet_set_default_charge0_addr)( pset );
        status |= NS(ParticleSet_set_default_mass0_addr)( pset );
        status |= NS(ParticleSet_set_default_beta0_addr)( pset );
        status |= NS(ParticleSet_set_default_gamma0_addr)( pset );
        status |= NS(ParticleSet_set_default_pc0_addr)( pset );

        status |= NS(ParticleSet_set_default_s_addr)( pset );
        status |= NS(ParticleSet_set_default_capacity)( pset );

        SIXTRL_ASSERT( status == (
            NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    return pset;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_init)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_num_elements_t) const num_particles ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;

    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( num_particles >= ( NS(particle_num_elements_t) )0 );

    status |= NS(ParticleSet_set_num_particles)( pset, num_particles );

    status |= NS(ParticleSet_set_default_x_addr)( pset );
    status |= NS(ParticleSet_set_default_px_addr)( pset );
    status |= NS(ParticleSet_set_default_y_addr)( pset );
    status |= NS(ParticleSet_set_default_py_addr)( pset );
    status |= NS(ParticleSet_set_default_zeta_addr)( pset );
    status |= NS(ParticleSet_set_default_delta_addr)( pset );

    status |= NS(ParticleSet_set_default_state_addr)( pset );
    status |= NS(ParticleSet_set_default_at_element_addr)( pset );
    status |= NS(ParticleSet_set_default_at_turn_addr)( pset );
    status |= NS(ParticleSet_set_default_particle_id_addr)( pset );

    status |= NS(ParticleSet_set_default_psigma_addr)( pset );
    status |= NS(ParticleSet_set_default_rpp_addr)( pset );
    status |= NS(ParticleSet_set_default_rvv_addr)( pset );
    status |= NS(ParticleSet_set_default_chi_addr)( pset );
    status |= NS(ParticleSet_set_default_charge_ratio_addr)( pset );

    status |= NS(ParticleSet_set_default_charge0_addr)( pset );
    status |= NS(ParticleSet_set_default_mass0_addr)( pset );
    status |= NS(ParticleSet_set_default_beta0_addr)( pset );
    status |= NS(ParticleSet_set_default_gamma0_addr)( pset );
    status |= NS(ParticleSet_set_default_pc0_addr)( pset );

    status |= NS(ParticleSet_set_default_s_addr)( pset );
    status |= NS(ParticleSet_set_capacity)( pset, num_particles );

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_init_detailed)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_num_elements_t) const num_particles,
    NS(particle_addr_t) const x_addr,
    NS(particle_addr_t) const px_addr,
    NS(particle_addr_t) const y_addr,
    NS(particle_addr_t) const py_addr,
    NS(particle_addr_t) const zeta_addr,
    NS(particle_addr_t) const delta_addr,
    NS(particle_addr_t) const state_addr,
    NS(particle_addr_t) const at_element_addr,
    NS(particle_addr_t) const at_turn_addr,
    NS(particle_addr_t) const particle_id_addr,
    NS(particle_addr_t) const psigma_addr,
    NS(particle_addr_t) const rpp_addr,
    NS(particle_addr_t) const rvv_addr,
    NS(particle_addr_t) const chi_addr,
    NS(particle_addr_t) const charge_ratio_addr,
    NS(particle_addr_t) const charge0_addr,
    NS(particle_addr_t) const mass0_addr,
    NS(particle_addr_t) const beta0_addr,
    NS(particle_addr_t) const gamma0_addr,
    NS(particle_addr_t) const pc0_addr,
    NS(particle_addr_t) const s_addr,
    NS(particle_num_elements_t) capacity ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;

    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( num_particles >= ( NS(particle_num_elements_t) )0 );
    if( capacity < num_particles ) capacity = num_particles;

    status |= NS(ParticleSet_set_x_addr)( pset, x_addr );
    status |= NS(ParticleSet_set_px_addr)( pset, px_addr );
    status |= NS(ParticleSet_set_y_addr)( pset, y_addr );
    status |= NS(ParticleSet_set_py_addr)( pset, py_addr );
    status |= NS(ParticleSet_set_zeta_addr)( pset, zeta_addr );
    status |= NS(ParticleSet_set_delta_addr)( pset, delta_addr );

    status |= NS(ParticleSet_set_state_addr)( pset, state_addr );
    status |= NS(ParticleSet_set_at_element_addr)( pset, at_element_addr );
    status |= NS(ParticleSet_set_at_turn_addr)( pset, at_turn_addr );
    status |= NS(ParticleSet_set_particle_id_addr)( pset, particle_id_addr );

    status |= NS(ParticleSet_set_psigma_addr)( pset, psigma_addr );
    status |= NS(ParticleSet_set_rpp_addr)( pset, rpp_addr );
    status |= NS(ParticleSet_set_rvv_addr)( pset, rvv_addr );
    status |= NS(ParticleSet_set_chi_addr)( pset, chi_addr );
    status |= NS(ParticleSet_set_charge_ratio_addr)( pset, charge_ratio_addr );

    status |= NS(ParticleSet_set_num_particles)( pset, num_particles );
    status |= NS(ParticleSet_set_charge0_addr)( pset, charge0_addr );
    status |= NS(ParticleSet_set_mass0_addr)( pset, mass0_addr );
    status |= NS(ParticleSet_set_beta0_addr)( pset, beta0_addr );
    status |= NS(ParticleSet_set_gamma0_addr)( pset, gamma0_addr );
    status |= NS(ParticleSet_set_pc0_addr)( pset, pc0_addr );

    status |= NS(ParticleSet_set_s_addr)( pset, s_addr );
    status |= NS(ParticleSet_set_capacity)( pset, capacity );

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_init_from_ptrs)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_num_elements_t) const num_particles,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT x_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT px_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT y_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT py_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT zeta_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT delta_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT state_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_index_t) const*
        SIXTRL_RESTRICT at_element_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_index_t) const*
        SIXTRL_RESTRICT at_turn_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_index_t) const*
        SIXTRL_RESTRICT particle_id_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_index_t) const*
        SIXTRL_RESTRICT const psigma_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT rpp_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT rvv_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT chi_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT charge_ratio_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT charge0_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT mass0_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT beta0_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT gamma0_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT pc0_values,
    SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT s_values,
    NS(particle_num_elements_t) capacity ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;

    SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( num_particles >= ( NS(particle_num_elements_t) )0 );
    if( capacity < num_particles ) capacity = num_particles;

    status |= NS(ParticleSet_set_capacity)( pset, capacity );
    status |= NS(ParticleSet_set_num_particles)( pset, num_particles );

    status |= NS(ParticleSet_set_x_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )x_values );
    status |= NS(ParticleSet_set_px_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )px_values );
    status |= NS(ParticleSet_set_y_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )y_values );
    status |= NS(ParticleSet_set_py_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )py_values );
    status |= NS(ParticleSet_set_zeta_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )zeta_values );
    status |= NS(ParticleSet_set_delta_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )delta_values );
    status |= NS(ParticleSet_set_state_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )state_values );
    status |= NS(ParticleSet_set_at_element_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )at_element_values );
    status |= NS(ParticleSet_set_at_turn_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )at_turn_values );
    status |= NS(ParticleSet_set_particle_id_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )particle_id_values );
    status |= NS(ParticleSet_set_psigma_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )psigma_values );
    status |= NS(ParticleSet_set_rpp_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )rpp_values );
    status |= NS(ParticleSet_set_rvv_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )rvv_values );
    status |= NS(ParticleSet_set_chi_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )chi_values );
    status |= NS(ParticleSet_set_charge_ratio_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )charge_ratio_values );
    status |= NS(ParticleSet_set_charge0_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )charge0_values );
    status |= NS(ParticleSet_set_mass0_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )mass0_values );
    status |= NS(ParticleSet_set_beta0_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )beta0_values );
    status |= NS(ParticleSet_set_gamma0_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )gamma0_values );
    status |= NS(ParticleSet_set_pc0_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )pc0_values );
    status |= NS(ParticleSet_set_s_addr)( pset,
                ( NS(particle_addr_t) )( uintptr_t )s_values );

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_INIT_H__ */
