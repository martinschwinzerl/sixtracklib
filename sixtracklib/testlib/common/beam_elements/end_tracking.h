#ifndef SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_END_TRACKING_H__
#define SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_END_TRACKING_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/end_tracking/end_tracking.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(EndTracking_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(EndTracking_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(EndTracking_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cmp_result_type) NS(EndTracking_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT {
    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            if( NS(EndTracking_next_at_element)( lhs ) !=
                NS(EndTracking_next_at_element)( rhs ) ) {
                result = ( NS(EndTracking_next_at_element)( lhs ) >
                           NS(EndTracking_next_at_element)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(EndTracking_next_buffer_idx)( lhs ) !=
                  NS(EndTracking_next_buffer_idx)( rhs ) ) ) {
                result = ( NS(EndTracking_next_buffer_idx)( lhs ) >
                           NS(EndTracking_next_buffer_idx)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( ( result == ( NS(cmp_result_type) )0u ) &&
                ( NS(EndTracking_ends_turn)( lhs ) !=
                  NS(EndTracking_ends_turn)( rhs ) ) )
            {
                result = ( ( int )NS(EndTracking_ends_turn)( lhs ) >
                           ( int )NS(EndTracking_ends_turn)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;
    return result;
}

SIXTRL_INLINE NS(cmp_result_type) NS(EndTracking_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const SIXTRL_UNUSED( rel_tolerance ),
    NS(be_real_type) const SIXTRL_UNUSED( abs_tolerance )
) SIXTRL_NOEXCEPT { return NS(EndTracking_compare)( lhs, rhs ); }

SIXTRL_INLINE NS(status_type) NS(EndTracking_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(EndTracking) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(EndTracking)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) )
    {
        status = NS(EndTracking_set_next_at_element)( diff,
            NS(EndTracking_next_at_element)( lhs ) -
            NS(EndTracking_next_at_element)( rhs ) );

        if( NS(EndTracking_next_buffer_idx)( lhs ) >=
            NS(EndTracking_next_buffer_idx)( rhs ) )
        {
            status |= NS(EndTracking_set_next_buffer_idx)( diff,
                NS(EndTracking_next_buffer_idx)( lhs ) -
                NS(EndTracking_next_buffer_idx)( rhs ) );
        }
        else
        {
            status |= NS(EndTracking_set_next_buffer_idx)( diff,
                NS(EndTracking_next_buffer_idx)( rhs ) -
                NS(EndTracking_next_buffer_idx)( lhs ) );
        }

        status |= NS(EndTracking_set_ends_turn)( diff,
            ( NS(EndTracking_ends_turn)( lhs ) !=
              NS(EndTracking_ends_turn)( rhs ) ) );
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_END_TRACKING_H__ */
