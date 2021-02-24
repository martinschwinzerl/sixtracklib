#ifndef SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_H__
#define SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(Multipole_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(Multipole_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(Multipole_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cmp_result_type) NS(Multipole_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT {
    return NS(Multipole_compare_with_tolerances)( lhs, rhs,
        ( NS(be_real_type) )0.0, ( NS(be_real_type) )SIXTRL_REAL_TYPE_EPS );
}

SIXTRL_INLINE NS(cmp_result_type) NS(Multipole_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT {
    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            if( NS(Multipole_order)( lhs ) != NS(Multipole_order)( rhs ) )
            {
                result = ( NS(Multipole_order)( lhs ) <
                           NS(Multipole_order)( rhs ) )
                    ? ( NS(cmp_result_type) )+1 : ( NS(cmp_result_type) )-1;
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                NS(Multipole_length)( lhs ), NS(Multipole_length)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Multipole_hxl)( lhs ), NS(Multipole_hxl)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(Multipole_hyl)( lhs ), NS(Multipole_hyl)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                if( ( NS(Multipole_const_bal_begin)( lhs ) == 0 ) &&
                    ( NS(Multipole_const_bal_begin)( rhs ) != 0 ) )
                {
                    result = ( NS(cmp_result_type) )-1;
                }
                else if( ( NS(Multipole_const_bal_begin)( lhs ) != 0 ) &&
                         ( NS(Multipole_const_bal_begin)( rhs ) == 0 ) )
                {
                    result = ( NS(cmp_result_type) )+1;
                }

                SIXTRL_ASSERT( ( result == ( NS(cmp_result_type) )0u ) ||
                    ( NS(Multipole_const_bal_begin)( lhs ) !=
                      NS(Multipole_const_bal_begin)( rhs ) ) );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances_for_range)(
                    NS(Multipole_const_bal_begin)( lhs ),
                    NS(Multipole_const_bal_end)( lhs ),
                    NS(Multipole_const_bal_begin)( rhs ), rel_tolerance,
                    abs_tolerance );
            }
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;
    return result;
}

SIXTRL_INLINE NS(status_type) NS(Multipole_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) &&
        ( NS(Multipole_max_order)( diff ) >= NS(Multipole_order)( lhs ) ) &&
        ( NS(Multipole_max_order)( diff ) >= NS(Multipole_order)( rhs ) ) )
    {
        NS(be_order_type) const order =
            ( NS(Multipole_order)( lhs ) >= NS(Multipole_order)( rhs ) )
                ? NS(Multipole_order)( lhs ) : NS(Multipole_order)( rhs );

        NS(size_type) const bal_length = ( order >= ( NS(be_order_type) )0u )
            ? ( NS(size_type) )( 2 * order + 2 )
            : ( NS(size_type) )0u;

        NS(size_type) const common_bal_length =
            ( order >= ( NS(be_order_type) )0u )
                ? ( ( NS(Multipole_order)( lhs ) >= NS(Multipole_order)( rhs ) )
                    ? ( NS(size_type) )( 2 * NS(Multipole_order)( lhs ) + 2 )
                    : ( NS(size_type) )( 2 * NS(Multipole_order)( rhs ) + 2 ) )
                : ( NS(size_type) )0u;

        NS(size_type) ii = ( NS(size_type) )0u;

        status  = NS(Multipole_set_order)( diff, order );

        status |= NS(Multipole_set_length)( diff,
            NS(Multipole_length)( lhs ) - NS(Multipole_length)( rhs ) );

        status |= NS(Multipole_set_hxl)( diff,
            NS(Multipole_hxl)( lhs ) - NS(Multipole_hxl)( rhs ) );

        status |= NS(Multipole_set_hyl)( diff,
            NS(Multipole_hyl)( lhs ) - NS(Multipole_hyl)( rhs ) );

        for( ; ii < common_bal_length ; ++ii )
        {
            status |= NS(Multipole_set_bal_value)( diff, ii,
                NS(Multipole_bal)( lhs, ii ) - NS(Multipole_bal)( rhs, ii ) );
        }

        if( ii < bal_length )
        {
            if( NS(Multipole_order)( lhs ) >= NS(Multipole_order)( rhs ) )
            {
                for( ; ii < bal_length ; ++ii )
                {
                    status |= NS(Multipole_set_bal_value)( diff, ii,
                        NS(Multipole_bal)( lhs, ii ) );
                }
            }
            else
            {
                for( ; ii < bal_length ; ++ii )
                {
                    status |= NS(Multipole_set_bal_value)( diff, ii,
                        -( NS(Multipole_bal)( rhs, ii ) ) );
                }
            }
        }
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_H__ */
