#ifndef SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_MONITOR_H__
#define SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_MONITOR_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/monitor/monitor.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(Monitor_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(Monitor_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Monitor_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cmp_result_type) NS(Monitor_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT {
    return NS(Monitor_compare_with_tolerances)( lhs, rhs,
        ( NS(be_real_type) )0.0, ( NS(be_real_type) )SIXTRL_REAL_TYPE_EPS );
}

SIXTRL_INLINE NS(cmp_result_type) NS(Monitor_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT {
    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            if( NS(Monitor_num_stores)( lhs ) != NS(Monitor_num_stores)( rhs ) )
            {
                result = ( NS(Monitor_num_stores)( lhs ) >
                           NS(Monitor_num_stores)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(Monitor_start)( lhs ) != NS(Monitor_start)( rhs ) ) )
            {
                result = ( NS(Monitor_start)( lhs ) > NS(Monitor_start)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(Monitor_skip)( lhs ) != NS(Monitor_skip)( rhs ) ) )
            {
                result = ( NS(Monitor_skip)( lhs ) > NS(Monitor_skip)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(Monitor_min_particle_id)( lhs ) !=
                  NS(Monitor_min_particle_id)( rhs ) ) )
            {
                result = ( NS(Monitor_min_particle_id)( lhs ) >
                           NS(Monitor_min_particle_id)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(Monitor_max_particle_id)( lhs ) !=
                  NS(Monitor_max_particle_id)( rhs ) ) )
            {
                result = ( NS(Monitor_max_particle_id)( lhs ) >
                           NS(Monitor_max_particle_id)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(Monitor_is_rolling)( lhs ) !=
                  NS(Monitor_is_rolling)( rhs ) ) )
            {
                result = ( ( int )NS(Monitor_is_rolling)( lhs ) >
                           ( int )NS(Monitor_is_rolling)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(Monitor_is_turn_ordered)( lhs ) !=
                  NS(Monitor_is_turn_ordered)( rhs ) ) )
            {
                result = ( ( int )NS(Monitor_is_turn_ordered)( lhs ) >
                           ( int )NS(Monitor_is_turn_ordered)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(Monitor_out_addr)( lhs ) != NS(Monitor_out_addr)( rhs ) ) )
            {
                result = ( ( int )NS(Monitor_out_addr)( lhs ) >
                           ( int )NS(Monitor_out_addr)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;
    return result;
}

SIXTRL_INLINE NS(status_type) NS(Monitor_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Monitor) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(Monitor)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) )
    {
        status = NS(Monitor_set_num_stores)( diff,
            NS(Monitor_num_stores)( lhs ) - NS(Monitor_num_stores)( rhs ) );

        status |= NS(Monitor_set_start)( diff,
            NS(Monitor_start)( lhs ) - NS(Monitor_start)( rhs ) );

        status |= NS(Monitor_set_skip)( diff,
            NS(Monitor_skip)( lhs ) - NS(Monitor_skip)( rhs ) );

        status |= NS(Monitor_set_min_particle_id)( diff,
            NS(Monitor_min_particle_id)( lhs ) -
            NS(Monitor_min_particle_id)( rhs ) );

        status |= NS(Monitor_set_max_particle_id)( diff,
            NS(Monitor_max_particle_id)( lhs ) -
            NS(Monitor_max_particle_id)( rhs ) );

        status |= NS(Monitor_set_is_rolling)( diff,
            ( NS(Monitor_is_rolling)( lhs ) !=
              NS(Monitor_is_rolling)( rhs ) ) );

        status |= NS(Monitor_set_is_turn_ordered)( diff,
            ( NS(Monitor_is_turn_ordered)( lhs ) !=
              NS(Monitor_is_turn_ordered)( rhs ) ) );

        if( NS(Monitor_out_addr)( lhs ) > NS(Monitor_out_addr)( rhs ) )
        {
            status |= NS(Monitor_set_out_addr)( diff,
                NS(Monitor_out_addr)( lhs ) - NS(Monitor_out_addr)( rhs ) );
        }
        else
        {
            status |= NS(Monitor_set_out_addr)( diff,
                NS(Monitor_out_addr)( rhs ) - NS(Monitor_out_addr)( lhs ) );
        }
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_MONITOR_H__ */
