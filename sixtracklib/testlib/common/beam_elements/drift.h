#ifndef SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_DRIFT_H__
#define SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_DRIFT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(Drift_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(Drift_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Drift_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(DriftExact_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type)
NS(DriftExact_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(DriftExact_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cmp_result_type) NS(Drift_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT {
    return NS(Drift_compare_with_tolerances)( lhs, rhs,
        ( NS(be_real_type) )0.0, ( NS(be_real_type) )SIXTRL_REAL_TYPE_EPS );
}

SIXTRL_INLINE NS(cmp_result_type) NS(Drift_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT {
    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            result = NS(Type_value_comp_result_with_tolerances)(
                NS(Drift_length)( lhs ), NS(Drift_length)( rhs ),
                    rel_tolerance, abs_tolerance );
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;
    return result;
}

SIXTRL_INLINE NS(status_type) NS(Drift_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(Drift)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) )
    {
        status = NS(Drift_set_length)( diff,
            NS(Drift_length)( lhs ) - NS(Drift_length)( rhs ) );
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cmp_result_type) NS(DriftExact_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT {
    return NS(DriftExact_compare_with_tolerances)( lhs, rhs,
        ( NS(be_real_type) )0.0, ( NS(be_real_type) )SIXTRL_REAL_TYPE_EPS );
}

SIXTRL_INLINE NS(cmp_result_type) NS(DriftExact_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT {
    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            result = NS(Type_value_comp_result_with_tolerances)(
                NS(DriftExact_length)( lhs ), NS(DriftExact_length)( rhs ),
                    rel_tolerance, abs_tolerance );
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;
    return result;
}

SIXTRL_INLINE NS(status_type) NS(DriftExact_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(DriftExact)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) )
    {
        status = NS(DriftExact_set_length)( diff,
            NS(DriftExact_length)( lhs ) - NS(DriftExact_length)( rhs ) );
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_DRIFT_H__ */
