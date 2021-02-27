#ifndef SIXTRACKLIB_TESTLIB_COMMON_PARTICLES_PARTICLES_H__
#define SIXTRACKLIB_TESTLIB_COMMON_PARTICLES_PARTICLES_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
    #include "sixtracklib/common/particles/particles.h"
    #include "sixtracklib/testlib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <algorithm>
    #include <random>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES )  && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(Particles_compare)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type)
NS(Particles_compare_with_tolerances)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT rhs,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Particles_difference)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT;


#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particles_print)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    NS(particles_num_type) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particles_print_difference)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT diff,
    NS(particles_num_type) const index );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particles_fprint)(
    FILE* SIXTRL_RESTRICT fp,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    NS(particles_num_type) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Particles_fprint_difference)(
    FILE* SIXTRL_RESTRICT fp,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT diff,
    NS(particles_num_type) const index );

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
          class NumCharge0DistT, class NumMass0DistT, class SDistT,
          class Beta0DistT, class Gamma0DistT, class P0CDistT >
SIXTRL_HOST_FN ::NS(status_type) Particles_init_random(
    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(Particles)* SIXTRL_RESTRICT pset,
    PrngT& prng,
    XYDistT& x_dist, XYDistT& y_dist, PxPyDistT& px_dist, PxPyDistT& py_dist,
    ZetaDistT& zeta_dist, DeltaDistT& delta_dist,
    StateDistT& state_dist, ::NS(particle_real_type) const active_treshold,
    AtElemDistT& at_elem_dist, AtTurnDistT& at_turn_dist, IdDistT& id_dist,
    ChargeRatioDistT& charge_ratio_dist, MassRatioDistT& mass_ratio_dist,
    NumCharge0DistT& num_charge0_dist, NumMass0DistT& num_mass0_dist,
    Beta0DistT& beta0_dist, Gamma0DistT& gamma0_dist, P0CDistT& p0c_dist,
    SDistT& s_dist )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    ::NS(status_type) status = st::STATUS_GENERAL_FAILURE;

    using real_type  = st::particle_real_type;
    using npart_type = st::particles_num_type;

    if( pset == nullptr ) return status;
    npart_type const NUM_PARTICLES = ::NS(Particles_num_particles)( pset );
    if( NUM_PARTICLES <= npart_type{ 0 } ) return status;

    status = st::STATUS_SUCCESS;

    for( npart_type ii = npart_type{ 0 } ; ii < NUM_PARTICLES ; ++ii )
    {
        #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                    ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )
        SIXTRL_PARTICLE_ARGPTR_DEC ::NS(SingleParticle) p;
        status |= ::NS(Particle_clear)( &p );

        #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
        SIXTRL_PARTICLE_ARGPTR_DEC ::NS(SingleParticleView) p;
        status |= ::NS(SingleParticleView_init_from_pset)( &p, pset, ii );

        #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

        real_type third_param = real_type{ 0. };
        ::NS(ParticleInitModeEnum) mode = ::NS(PARTICLE_INIT_MODE_DEFAULT);

        if( ( ii % npart_type{ 3 } ) == npart_type{ 0 } )
        {
            third_param = beta0_dist( prng );
            mode = ::NS(PARTICLE_INIT_MODE_CHARGE0_MASS0_BETA0);
        }
        else if( ( ii % npart_type{ 3 } ) == npart_type{ 1 } )
        {
            third_param = gamma0_dist( prng );
            mode = ::NS(PARTICLE_INIT_MODE_CHARGE0_MASS0_GAMMA0);
        }
        else
        {
            third_param = p0c_dist( prng );
            mode = ::NS(PARTICLE_INIT_MODE_CHARGE0_MASS0_P0C);
        }

        status |= st::testlib::Particle_init_random( &p, prng, x_dist, y_dist,
            px_dist, py_dist, zeta_dist, delta_dist, state_dist, active_treshold,
                at_elem_dist, at_turn_dist, id_dist, charge_ratio_dist,
                    mass_ratio_dist, num_charge0_dist, num_mass0_dist, s_dist,
                        third_param, mode );

        status |= ::NS(Particles_from_single_particle)( pset, ii, &p );
        if( status != st::STATUS_SUCCESS ) break;
    }

    return status;
}

SIXTRL_HOST_FN std::ostream& Particles_to_stream(
    std::ostream& SIXTRL_RESTRICT_REF ostr,
    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(Particles) const& SIXTRL_RESTRICT_REF pset,
    ::NS(particles_num_type) const index );

SIXTRL_HOST_FN std::ostream& Particles_diff_to_stream(
    std::ostream& SIXTRL_RESTRICT_REF ostr,
    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(Particles) const& SIXTRL_RESTRICT_REF lhs,
    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(Particles) const& SIXTRL_RESTRICT_REF rhs,
    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(Particles) const& SIXTRL_RESTRICT_REF diff,
    ::NS(particles_num_type) const index );

} /* end: namespace testlib */
} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cmp_result_type) NS(Particles_compare)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT {
    return NS(Particles_compare_with_tolerances)( lhs, rhs,
        ( NS(particle_real_type) )0.0,
        ( NS(particle_real_type) )SIXTRL_REAL_TYPE_EPS );
}

SIXTRL_INLINE NS(cmp_result_type) NS(Particles_compare_with_tolerances)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT rhs,
    NS(particle_real_type) const rel_tolerance,
    NS(particle_real_type) const abs_tolerance ) SIXTRL_NOEXCEPT {
    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            if( NS(Particles_num_particles)( lhs ) !=
                NS(Particles_num_particles)( rhs ) )
            {
                result = ( NS(Particles_num_particles)( lhs ) >
                           NS(Particles_num_particles)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_charge0_const_begin)( lhs ),
                    NS(Particles_charge0_const_end)( lhs ),
                    NS(Particles_charge0_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_mass0_const_begin)( lhs ),
                    NS(Particles_mass0_const_end)( lhs ),
                    NS(Particles_mass0_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_beta0_const_begin)( lhs ),
                    NS(Particles_beta0_const_end)( lhs ),
                    NS(Particles_beta0_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_gamma0_const_begin)( lhs ),
                    NS(Particles_gamma0_const_end)( lhs ),
                    NS(Particles_gamma0_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_p0c_const_begin)( lhs ),
                    NS(Particles_p0c_const_end)( lhs ),
                    NS(Particles_p0c_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_s_const_begin)( lhs ),
                    NS(Particles_s_const_end)( lhs ),
                    NS(Particles_s_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_x_const_begin)( lhs ),
                    NS(Particles_x_const_end)( lhs ),
                    NS(Particles_x_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_y_const_begin)( lhs ),
                    NS(Particles_y_const_end)( lhs ),
                    NS(Particles_y_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_px_const_begin)( lhs ),
                    NS(Particles_px_const_end)( lhs ),
                    NS(Particles_px_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_py_const_begin)( lhs ),
                    NS(Particles_py_const_end)( lhs ),
                    NS(Particles_py_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_zeta_const_begin)( lhs ),
                    NS(Particles_zeta_const_end)( lhs ),
                    NS(Particles_zeta_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_psigma_const_begin)( lhs ),
                    NS(Particles_psigma_const_end)( lhs ),
                    NS(Particles_psigma_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_delta_const_begin)( lhs ),
                    NS(Particles_delta_const_end)( lhs ),
                    NS(Particles_delta_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_rpp_const_begin)( lhs ),
                    NS(Particles_rpp_const_end)( lhs ),
                    NS(Particles_rpp_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_rvv_const_begin)( lhs ),
                    NS(Particles_rvv_const_end)( lhs ),
                    NS(Particles_rvv_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_chi_const_begin)( lhs ),
                    NS(Particles_chi_const_end)( lhs ),
                    NS(Particles_chi_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Particles_charge_ratio_const_begin)( lhs ),
                    NS(Particles_charge_ratio_const_end)( lhs ),
                    NS(Particles_charge_ratio_const_begin)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_int64_for_range)(
                    NS(Particles_id_const_begin)( lhs ),
                    NS(Particles_id_const_end)( lhs ),
                    NS(Particles_id_const_begin)( rhs ) );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_int64_for_range)(
                    NS(Particles_at_element_const_begin)( lhs ),
                    NS(Particles_at_element_const_end)( lhs ),
                    NS(Particles_at_element_const_begin)( rhs ) );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_int64_for_range)(
                    NS(Particles_at_turn_const_begin)( lhs ),
                    NS(Particles_at_turn_const_end)( lhs ),
                    NS(Particles_at_turn_const_begin)( rhs ) );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_int64_for_range)(
                    NS(Particles_state_const_begin)( lhs ),
                    NS(Particles_state_const_end)( lhs ),
                    NS(Particles_state_const_begin)( rhs ) );
            }
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;
    return result;
}

SIXTRL_INLINE NS(status_type) NS(Particles_difference)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) &&
        ( NS(Particles_max_num_particles)( diff ) >=
          NS(Particles_num_particles)( lhs ) ) &&
        ( NS(Particles_num_particles)( lhs ) ==
          NS(Particles_num_particles)( rhs ) ) )
    {
        typedef NS(particles_num_type) npart_type;
        typedef NS(particle_real_type) real_type;
        typedef NS(particle_index_type) index_type;

        NS(particles_num_type) ii = ( NS(particles_num_type) )0u;
        NS(particles_num_type) const NUM_PARTICLES =
            NS(Particles_num_particles)( lhs );

        typedef SIXTRL_PARTICLES_DATAPTR_DEC real_type* real_pointer;
        typedef SIXTRL_PARTICLES_DATAPTR_DEC real_type const* real_const_pointer;

        typedef SIXTRL_PARTICLES_DATAPTR_DEC index_type* index_pointer;
        typedef SIXTRL_PARTICLES_DATAPTR_DEC index_type const* index_const_pointer;

        real_const_pointer lhs_real_pointers[ 17 ] = {
            NS(Particles_charge0_const_begin)( lhs ),
            NS(Particles_mass0_const_begin)( lhs ),
            NS(Particles_beta0_const_begin)( lhs ),
            NS(Particles_gamma0_const_begin)( lhs ),
            NS(Particles_p0c_const_begin)( lhs ),
            NS(Particles_s_const_begin)( lhs ),
            NS(Particles_x_const_begin)( lhs ),
            NS(Particles_y_const_begin)( lhs ),
            NS(Particles_px_const_begin)( lhs ),
            NS(Particles_py_const_begin)( lhs ),
            NS(Particles_zeta_const_begin)( lhs ),
            NS(Particles_psigma_const_begin)( lhs ),
            NS(Particles_delta_const_begin)( lhs ),
            NS(Particles_rpp_const_begin)( lhs ),
            NS(Particles_rvv_const_begin)( lhs ),
            NS(Particles_chi_const_begin)( lhs ),
            NS(Particles_charge_ratio_const_begin)( lhs ) };

        real_const_pointer rhs_real_pointers[ 17 ] = {
            NS(Particles_charge0_const_begin)( rhs ),
            NS(Particles_mass0_const_begin)( rhs ),
            NS(Particles_beta0_const_begin)( rhs ),
            NS(Particles_gamma0_const_begin)( rhs ),
            NS(Particles_p0c_const_begin)( rhs ),
            NS(Particles_s_const_begin)( rhs ),
            NS(Particles_x_const_begin)( rhs ),
            NS(Particles_y_const_begin)( rhs ),
            NS(Particles_px_const_begin)( rhs ),
            NS(Particles_py_const_begin)( rhs ),
            NS(Particles_zeta_const_begin)( rhs ),
            NS(Particles_psigma_const_begin)( rhs ),
            NS(Particles_delta_const_begin)( rhs ),
            NS(Particles_rpp_const_begin)( rhs ),
            NS(Particles_rvv_const_begin)( rhs ),
            NS(Particles_chi_const_begin)( rhs ),
            NS(Particles_charge_ratio_const_begin)( rhs ) };

        real_pointer diff_real_pointers[ 17 ] = {
            NS(Particles_charge0_begin)( diff ),
            NS(Particles_mass0_begin)( diff ),
            NS(Particles_beta0_begin)( diff ),
            NS(Particles_gamma0_begin)( diff ),
            NS(Particles_p0c_begin)( diff ),
            NS(Particles_s_begin)( diff ),
            NS(Particles_x_begin)( diff ),
            NS(Particles_y_begin)( diff ),
            NS(Particles_px_begin)( diff ),
            NS(Particles_py_begin)( diff ),
            NS(Particles_zeta_begin)( diff ),
            NS(Particles_psigma_begin)( diff ),
            NS(Particles_delta_begin)( diff ),
            NS(Particles_rpp_begin)( diff ),
            NS(Particles_rvv_begin)( diff ),
            NS(Particles_chi_begin)( diff ),
            NS(Particles_charge_ratio_begin)( diff ) };

        /* ----------------------------------------------------------------- */

        index_const_pointer lhs_index_pointers[ 4 ] = {
            NS(Particles_id_const_begin)( lhs ),
            NS(Particles_at_element_const_begin)( lhs ),
            NS(Particles_at_turn_const_begin)( lhs ),
            NS(Particles_state_const_begin)( lhs ) };

        index_const_pointer rhs_index_pointers[ 4 ] = {
            NS(Particles_id_const_begin)( rhs ),
            NS(Particles_at_element_const_begin)( rhs ),
            NS(Particles_at_turn_const_begin)( rhs ),
            NS(Particles_state_const_begin)( rhs ) };

        index_pointer diff_index_pointers[ 4 ] = {
            NS(Particles_id_begin)( diff ),
            NS(Particles_at_element_begin)( diff ),
            NS(Particles_at_turn_begin)( diff ),
            NS(Particles_state_begin)( diff ) };

        /* ----------------------------------------------------------------- */

        status = ( NS(status_type) )SIXTRL_STATUS_SUCCESS;

        {
            npart_type jj = ( npart_type )0u;

            for( ; jj < ( npart_type )17u ; ++jj )
            {
                if( ( lhs_real_pointers[ jj ]  == SIXTRL_NULLPTR ) ||
                    ( rhs_real_pointers[ jj ]  == SIXTRL_NULLPTR ) ||
                    ( diff_real_pointers[ jj ] == SIXTRL_NULLPTR ) ||
                    ( lhs_real_pointers[ jj ] == rhs_real_pointers[ jj ] ) ||
                    ( lhs_real_pointers[ jj ] == diff_real_pointers[ jj ] ) ||
                    ( rhs_real_pointers[ jj ] == diff_real_pointers[ jj ] ) )
                {
                    status  = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }
            }

            for( jj = ( npart_type )0u ; jj < ( npart_type )4u ; ++jj )
            {
                if( ( lhs_index_pointers[ jj ]  == SIXTRL_NULLPTR ) ||
                    ( rhs_index_pointers[ jj ]  == SIXTRL_NULLPTR ) ||
                    ( diff_index_pointers[ jj ] == SIXTRL_NULLPTR ) ||
                    ( lhs_index_pointers[ jj ] == rhs_index_pointers[ jj ] ) ||
                    ( lhs_index_pointers[ jj ] == diff_index_pointers[ jj ] ) ||
                    ( rhs_index_pointers[ jj ] == diff_index_pointers[ jj ] ) )
                {
                    status  = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }

        if( status != ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) return status;

        for( ; ii < NUM_PARTICLES ; ++ii )
        {
            npart_type jj = ( npart_type )0u;

            for( ; jj < ( npart_type )17u ; ++jj )
            {
                SIXTRL_ASSERT( lhs_real_pointers[ jj ]  != SIXTRL_NULLPTR );
                SIXTRL_ASSERT( rhs_real_pointers[ jj ]  != SIXTRL_NULLPTR );
                SIXTRL_ASSERT( diff_real_pointers[ jj ] != SIXTRL_NULLPTR );

                diff_real_pointers[ jj ][ ii ] =
                    lhs_real_pointers[ jj ][ ii ] -
                    rhs_real_pointers[ jj ][ ii ];
            }

            for( jj = ( npart_type )0u ; jj < ( npart_type )4u ; ++jj )
            {
                SIXTRL_ASSERT( lhs_index_pointers[ jj ]  != SIXTRL_NULLPTR );
                SIXTRL_ASSERT( rhs_index_pointers[ jj ]  != SIXTRL_NULLPTR );
                SIXTRL_ASSERT( diff_index_pointers[ jj ] != SIXTRL_NULLPTR );

                diff_index_pointers[ jj ][ ii ] =
                    lhs_index_pointers[ jj ][ ii ] -
                    rhs_index_pointers[ jj ][ ii ];
            }
        }
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_PARTICLES_PARTICLES_H__ */
