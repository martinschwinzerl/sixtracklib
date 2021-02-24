#ifndef SIXTRACKLIB_TESTLIB_COMMON_PARTICLES_SINGLE_PARTICLE_H__
#define SIXTRACKLIB_TESTLIB_COMMON_PARTICLES_SINGLE_PARTICLE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <algorithm>
    #include <random>
    #include <ostream>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && !defined( __cplusplus )
    #include <stdint.h>
    #include <stdio.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && !defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(Particle_compare)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type)
NS(Particle_compare_with_tolerances)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particle_difference)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particle_print)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particle_print_difference)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT diff );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particle_fprint)(
    FILE* SIXTRL_RESTRICT fp,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT p );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particle_fprint_difference)(
    FILE* SIXTRL_RESTRICT fp,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT diff );

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE {
namespace testlib {

template< class PrngT, class XYDistT, class PxPyDistT,
          class ZetaDistT, class DeltaDistT,
          class IdDistT, class AtElemDistT, class AtTurnDistT, class StateDistT,
          class ChargeRatioDistT, class MassRatioDistT,
          class NumCharge0DistT, class NumMass0DistT, class SDistT >
SIXTRL_HOST_FN ::NS(status_type) Particle_init_random(
    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle)* SIXTRL_RESTRICT p, PrngT& prng,
    XYDistT& x_dist, XYDistT& y_dist, PxPyDistT& px_dist, PxPyDistT& py_dist,
    ZetaDistT& zeta_dist, DeltaDistT& delta_dist,
    StateDistT& state_dist, ::NS(particle_real_type) const active_treshold,
    AtElemDistT& at_elem_dist, AtTurnDistT& at_turn_dist, IdDistT& id_dist,
    ChargeRatioDistT& charge_ratio_dist, MassRatioDistT& mass_ratio_dist,
    NumCharge0DistT& num_charge0_dist, NumMass0DistT& num_mass0_dist,
    SDistT& s_dist, ::NS(particle_real_type) const third_param_value,
    ::NS(ParticleInitModeEnum) const init_mode =
        ::NS(PARTICLE_INIT_MODE_DEFAULT) )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    ::NS(status_type) status = st::STATUS_GENERAL_FAILURE;

    using real_type  = st::particle_real_type;
    using index_type = st::particle_index_type;
    using charge0_num_type = typename NumCharge0DistT::result_type;
    using mass0_num_type   = typename NumMass0DistT::result_type;

    if( p == nullptr ) return status;

    real_type charge0 = ::NS(PhysConst_charge0)();
    charge0_num_type num_charge0 = num_charge0_dist( prng );

    if( num_charge0 == charge0_num_type{ 0 } )
        num_charge0 =  charge0_num_type{ 1 };

    if( num_charge0 != charge0_num_type{ 1 } )
        charge0 *= static_cast< real_type >( num_charge0 );

    real_type mass0 = real_type{ 0. };
    mass0_num_type num_mass0 = num_mass0_dist( prng );

    if( num_mass0 < mass0_num_type{ 0 } )
        num_mass0 = -num_mass0;

    if( num_mass0 == mass0_num_type{ 0 } )
        num_mass0 =  mass0_num_type{ 1 };

    if( num_mass0 == mass0_num_type{ 1 } )
    {
        mass0 = ::NS(PhysConst_mass_proton_ev)();
    }
    else
    {
        mass0 = ::NS(PhysConst_mass_atomic_ev)() *
                static_cast< real_type >( num_mass0 );
    }

    status = ::NS(Particle_init_from_charge0_mass0)(
        p, charge0, mass0, third_param_value, init_mode, delta_dist( prng ) );

    if( status == st::STATUS_SUCCESS )
    {
        ::NS(Particle_set_x)( p, x_dist( prng ) );
        ::NS(Particle_set_y)( p, y_dist( prng ) );
        ::NS(Particle_set_px)( p, px_dist( prng ) );
        ::NS(Particle_set_py)( p, py_dist( prng ) );
        ::NS(Particle_set_zeta)( p, zeta_dist( prng ) );
        ::NS(Particle_update_delta)( p, delta_dist( prng ) );

        real_type const real_state = state_dist( prng );
        index_type const state = ( real_state > active_treshold )
            ? index_type{ 1 } : index_type{ 0 };

        ::NS(Particle_set_state)( p, state );
        ::NS(Particle_set_at_element)( p, at_elem_dist( prng ) );
        ::NS(Particle_set_at_turn)( p, at_turn_dist( prng ) );
        ::NS(Particle_set_id)( p, id_dist( prng ) );

        real_type mass_ratio = mass_ratio_dist( prng );

        if( mass_ratio <= real_type{ 0.0 } )
        {
            mass_ratio = ( -mass_ratio ) +
                std::numeric_limits< real_type >::epsilon();
        }

        real_type const charge_ratio = charge_ratio_dist( prng );
        real_type const chi = charge_ratio / mass_ratio;

        ::NS(Particle_set_chi)( p, chi );
        ::NS(Particle_set_charge_ratio)( p, charge_ratio );
        ::NS(Particle_set_s)( p, s_dist( prng ) );
    }

    return status;
}

SIXTRL_HOST_FN std::ostream& Particle_to_stream(
    std::ostream& SIXTRL_RESTRICT_REF ostr,
    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle) const& SIXTRL_RESTRICT_REF p );

SIXTRL_HOST_FN std::ostream& Particle_diff_to_stream(
    std::ostream& SIXTRL_RESTRICT_REF ostr,
    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle) const& SIXTRL_RESTRICT_REF lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle) const& SIXTRL_RESTRICT_REF rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle) const& SIXTRL_RESTRICT_REF diff );

} /* end: namespace testlib */
} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ========================================================================= */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cmp_result_type) NS(Particle_compare)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT {
    return NS(Particle_compare_with_tolerances)( lhs, rhs,
        ( NS(particle_real_type) )0.0,
        ( NS(particle_real_type) )SIXTRL_REAL_TYPE_EPS );
}

SIXTRL_INLINE NS(cmp_result_type) NS(Particle_compare_with_tolerances)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance ) SIXTRL_NOEXCEPT {
    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            result = NS(Type_value_comp_result_with_tolerances)(
                NS(Particle_x)( lhs ), NS(Particle_x)( rhs ), rel_tolerance,
                    abs_tolerance );

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_y)( lhs ), NS(Particle_y)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_px)( lhs ), NS(Particle_px)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_py)( lhs ), NS(Particle_py)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_zeta)( lhs ), NS(Particle_zeta)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_delta)( lhs ), NS(Particle_delta)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(Particle_state)( lhs ) != NS(Particle_state)( rhs ) ) )
            {
                result = ( NS(Particle_state)( lhs ) > NS(Particle_state)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(Particle_at_element)( lhs ) !=
                  NS(Particle_at_element)( rhs ) ) )
            {
                result = ( NS(Particle_at_element)( lhs ) >
                           NS(Particle_at_element)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(Particle_at_turn)( lhs ) !=
                  NS(Particle_at_turn)( rhs ) ) )
            {
                result = ( NS(Particle_at_turn)( lhs ) >
                           NS(Particle_at_turn)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(Particle_id)( lhs ) != NS(Particle_id)( rhs ) ) )
            {
                result = ( NS(Particle_id)( lhs ) > NS(Particle_id)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_psigma)( lhs ), NS(Particle_psigma)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_rpp)( lhs ), NS(Particle_rpp)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_rvv)( lhs ), NS(Particle_rvv)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_chi)( lhs ), NS(Particle_chi)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_charge_ratio)( lhs ),
                        NS(Particle_charge_ratio)( rhs ), rel_tolerance,
                            abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_charge0)( lhs ), NS(Particle_charge0)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_mass0)( lhs ), NS(Particle_mass0)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_beta0)( lhs ), NS(Particle_beta0)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_gamma0)( lhs ), NS(Particle_gamma0)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_p0c)( lhs ), NS(Particle_p0c)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Particle_s)( lhs ), NS(Particle_s)( rhs ),
                        rel_tolerance, abs_tolerance );
            }
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;
    return result;
}

SIXTRL_INLINE NS(status_type) NS(Particle_difference)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) )
    {
        NS(Particle_set_x)( diff, NS(Particle_x)( lhs ) - NS(Particle_x)( rhs ) );
        NS(Particle_set_y)( diff, NS(Particle_y)( lhs ) - NS(Particle_y)( rhs ) );

        NS(Particle_set_px)( diff,
            NS(Particle_px)( lhs ) - NS(Particle_px)( rhs ) );

        NS(Particle_set_py)( diff,
            NS(Particle_py)( lhs ) - NS(Particle_py)( rhs ) );

        NS(Particle_set_zeta)( diff,
            NS(Particle_zeta)( lhs ) - NS(Particle_zeta)( rhs ) );

        NS(Particle_set_delta)( diff,
            NS(Particle_delta)( lhs ) - NS(Particle_delta)( rhs ) );

        NS(Particle_set_state)( diff,
            NS(Particle_state)( lhs ) - NS(Particle_state)( rhs ) );

        NS(Particle_set_at_element)( diff,
            NS(Particle_at_element)( lhs ) - NS(Particle_at_element)( rhs ) );

        NS(Particle_set_at_turn)( diff,
            NS(Particle_at_turn)( lhs ) - NS(Particle_at_turn)( rhs ) );

        NS(Particle_set_id)( diff,
            NS(Particle_id)( lhs ) - NS(Particle_id)( rhs ) );

        NS(Particle_set_psigma)( diff,
            NS(Particle_psigma)( lhs ) - NS(Particle_psigma)( rhs ) );

        NS(Particle_set_rpp)( diff,
            NS(Particle_rpp)( lhs ) - NS(Particle_rpp)( rhs ) );

        NS(Particle_set_rvv)( diff,
            NS(Particle_rvv)( lhs ) - NS(Particle_rvv)( rhs ) );

        NS(Particle_set_chi)( diff,
            NS(Particle_chi)( lhs ) - NS(Particle_chi)( rhs ) );

        NS(Particle_set_charge_ratio)( diff,
            NS(Particle_charge_ratio)( lhs ) - NS(Particle_charge_ratio)( rhs ) );

        NS(Particle_set_charge0)( diff,
            NS(Particle_charge0)( lhs ) - NS(Particle_charge0)( rhs ) );

        NS(Particle_set_mass0)( diff,
            NS(Particle_mass0)( lhs ) - NS(Particle_mass0)( rhs ) );

        NS(Particle_set_beta0)( diff,
            NS(Particle_beta0)( lhs ) - NS(Particle_beta0)( rhs ) );

        #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                    ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )

        diff->gamma0 = ( lhs->gamma0 - rhs->gamma0 );

        #else

        NS(Particle_set_gamma0)( diff,
            NS(Particle_gamma0)( lhs ) - NS(Particle_gamma0)( rhs ) );

        #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

        NS(Particle_set_p0c)( diff,
            NS(Particle_p0c)( lhs ) - NS(Particle_p0c)( rhs ) );

        NS(Particle_set_s)( diff, NS(Particle_s)( lhs ) - NS(Particle_s)( rhs ) );
        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_PARTICLES_SINGLE_PARTICLE_H__ */
