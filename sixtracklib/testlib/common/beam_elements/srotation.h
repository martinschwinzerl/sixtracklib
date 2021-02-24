#ifndef SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_SROTATION_H__
#define SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_SROTATION_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/srotation.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(SRotation_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(SRotation_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SRotation_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cmp_result_type) NS(SRotation_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT {
    return NS(SRotation_compare_with_tolerances)( lhs, rhs,
        ( NS(be_real_type) )0.0, ( NS(be_real_type) )SIXTRL_REAL_TYPE_EPS );
}

SIXTRL_INLINE NS(cmp_result_type) NS(SRotation_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT {
    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            result = NS(Type_value_comp_result_with_tolerances)(
                NS(SRotation_cos_z)( lhs ), NS(SRotation_cos_z)( rhs ),
                    rel_tolerance, abs_tolerance );

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SRotation_sin_z)( lhs ), NS(SRotation_sin_z)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            SIXTRL_ASSERT( NS(SRotation_cos_z)( lhs ) >= ( NS(be_real_type) )-1.0 );
            SIXTRL_ASSERT( NS(SRotation_cos_z)( lhs ) <= ( NS(be_real_type) )+1.0 );
            SIXTRL_ASSERT( NS(SRotation_sin_z)( lhs ) >= ( NS(be_real_type) )-1.0 );
            SIXTRL_ASSERT( NS(SRotation_sin_z)( lhs ) <= ( NS(be_real_type) )+1.0 );

            SIXTRL_ASSERT( NS(SRotation_cos_z)( rhs ) >= ( NS(be_real_type) )-1.0 );
            SIXTRL_ASSERT( NS(SRotation_cos_z)( rhs ) <= ( NS(be_real_type) )+1.0 );
            SIXTRL_ASSERT( NS(SRotation_sin_z)( rhs ) >= ( NS(be_real_type) )-1.0 );
            SIXTRL_ASSERT( NS(SRotation_sin_z)( rhs ) <= ( NS(be_real_type) )+1.0 );
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;
    return result;
}

SIXTRL_INLINE NS(status_type) NS(SRotation_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(SRotation)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) )
    {
        status = NS(SRotation_set_cos_z)( diff,
            NS(SRotation_cos_z)( lhs ) - NS(SRotation_cos_z)( rhs ) );

        status |= NS(SRotation_set_sin_z)( diff,
            NS(SRotation_sin_z)( lhs ) - NS(SRotation_sin_z)( rhs ) );
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_SROTATION_H__ */
