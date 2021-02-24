#ifndef SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_LIMIT_H__
#define SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_LIMIT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/limit/limit_rect.h"
    #include "sixtracklib/common/beam_elements/limit/limit_ellipse.h"
    #include "sixtracklib/common/beam_elements/limit/limit_rect_ellipse.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(LimitRect_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(LimitRect_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRect_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(LimitEllipse_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type)
NS(LimitEllipse_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitEllipse_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(LimitEllipse)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(LimitRectEllipse_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type)
NS(LimitRectEllipse_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(LimitRectEllipse_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cmp_result_type) NS(LimitRect_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT {
    return NS(LimitRect_compare_with_tolerances)( lhs, rhs,
        ( NS(be_real_type) )0.0, ( NS(be_real_type) )SIXTRL_REAL_TYPE_EPS );
}

SIXTRL_INLINE NS(cmp_result_type) NS(LimitRect_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT {
    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            result = NS(Type_value_comp_result_with_tolerances)(
                NS(LimitRect_x_min)( lhs ), NS(LimitRect_x_min)( rhs ),
                    rel_tolerance, abs_tolerance );

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(LimitRect_x_max)( lhs ), NS(LimitRect_x_max)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(LimitRect_y_min)( lhs ), NS(LimitRect_y_min)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(LimitRect_y_max)( lhs ), NS(LimitRect_y_max)( rhs ),
                        rel_tolerance, abs_tolerance );
            }
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;
    return result;
}

SIXTRL_INLINE NS(status_type) NS(LimitRect_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRect) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(LimitRect)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) )
    {
        status = NS(LimitRect_set_x_min)( diff,
            NS(LimitRect_x_min)( lhs ) - NS(LimitRect_x_min)( rhs ) );

        status |= NS(LimitRect_set_x_max)( diff,
            NS(LimitRect_x_max)( lhs ) - NS(LimitRect_x_max)( rhs ) );

        status |= NS(LimitRect_set_y_min)( diff,
            NS(LimitRect_y_min)( lhs ) - NS(LimitRect_y_min)( rhs ) );

        status |= NS(LimitRect_set_y_max)( diff,
            NS(LimitRect_y_max)( lhs ) - NS(LimitRect_y_max)( rhs ) );
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cmp_result_type) NS(LimitEllipse_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT {
    return NS(LimitEllipse_compare_with_tolerances)( lhs, rhs,
        ( NS(be_real_type) )0.0, ( NS(be_real_type) )SIXTRL_REAL_TYPE_EPS );
}

SIXTRL_INLINE NS(cmp_result_type) NS(LimitEllipse_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT {
    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            result = NS(Type_value_comp_result_with_tolerances)(
                NS(LimitEllipse_a_squ)( lhs ), NS(LimitEllipse_a_squ)( rhs ),
                    rel_tolerance, abs_tolerance );

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(LimitEllipse_b_squ)( lhs ), NS(LimitEllipse_b_squ)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(LimitEllipse_a_b_squ)( lhs ),
                    NS(LimitEllipse_a_b_squ)( rhs ),
                        rel_tolerance, abs_tolerance );
            }

            SIXTRL_ASSERT( 0 == NS(Type_value_comp_result_with_tolerances)(
                NS(LimitEllipse_a_squ)( lhs ) * NS(LimitEllipse_b_squ)( lhs ),
                NS(LimitEllipse_a_b_squ)( lhs ), rel_tolerance, abs_tolerance ) );

            SIXTRL_ASSERT( 0 == NS(Type_value_comp_result_with_tolerances)(
                NS(LimitEllipse_a_squ)( rhs ) * NS(LimitEllipse_b_squ)( rhs ),
                NS(LimitEllipse_a_b_squ)( rhs ), rel_tolerance, abs_tolerance ) );
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;
    return result;
}

SIXTRL_INLINE NS(status_type) NS(LimitEllipse_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(LimitEllipse)* SIXTRL_RESTRICT diff ) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) )
    {
        status = NS(LimitEllipse_set_a_squ)( diff,
            NS(LimitEllipse_a_squ)( lhs ) - NS(LimitEllipse_a_squ)( rhs ) );

        status |= NS(LimitEllipse_set_b_squ)( diff,
            NS(LimitEllipse_b_squ)( lhs ) - NS(LimitEllipse_b_squ)( rhs ) );

        status = NS(LimitEllipse_set_a_b_squ)( diff,
            NS(LimitEllipse_a_b_squ)( lhs ) - NS(LimitEllipse_a_b_squ)( rhs ) );
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

SIXTRL_INLINE NS(cmp_result_type) NS(LimitRectEllipse_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT {
    return NS(LimitRectEllipse_compare_with_tolerances)( lhs, rhs,
        ( NS(be_real_type) )0.0, ( NS(be_real_type) )SIXTRL_REAL_TYPE_EPS );
}

SIXTRL_INLINE NS(cmp_result_type) NS(LimitRectEllipse_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance, NS(be_real_type) const abs_tolerance
) SIXTRL_NOEXCEPT {
    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            result = NS(Type_value_comp_result_with_tolerances)(
                NS(LimitRectEllipse_x_max)( lhs ),
                NS(LimitRectEllipse_x_max)( rhs ), rel_tolerance,
                abs_tolerance );

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(LimitRectEllipse_y_max)( lhs ),
                    NS(LimitRectEllipse_y_max)( rhs ), rel_tolerance,
                    abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(LimitRectEllipse_a_squ)( lhs ),
                    NS(LimitRectEllipse_a_squ)( rhs ), rel_tolerance,
                    abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(LimitRectEllipse_b_squ)( lhs ),
                    NS(LimitRectEllipse_b_squ)( rhs ), rel_tolerance,
                    abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0u )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(LimitRectEllipse_a_b_squ)( lhs ),
                    NS(LimitRectEllipse_a_b_squ)( rhs ), rel_tolerance,
                    abs_tolerance );
            }

            SIXTRL_ASSERT( 0 == NS(Type_value_comp_result_with_tolerances)(
                NS(LimitRectEllipse_a_squ)( lhs ) *
                NS(LimitRectEllipse_b_squ)( lhs ),
                NS(LimitRectEllipse_a_b_squ)( lhs ), rel_tolerance,
                abs_tolerance ) );

            SIXTRL_ASSERT( 0 == NS(Type_value_comp_result_with_tolerances)(
                NS(LimitRectEllipse_a_squ)( rhs ) *
                NS(LimitRectEllipse_b_squ)( rhs ),
                NS(LimitRectEllipse_a_b_squ)( rhs ), rel_tolerance,
                abs_tolerance ) );
        }
    }
    else if( rhs != SIXTRL_NULLPTR ) result = ( NS(cmp_result_type) )-1;
    return result;
}

SIXTRL_INLINE NS(status_type) NS(LimitRectEllipse_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitRectEllipse) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(LimitRectEllipse)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) )
    {
        status = NS(LimitRectEllipse_set_x_max)( diff,
            NS(LimitRectEllipse_x_max)( lhs ) -
            NS(LimitRectEllipse_x_max)( rhs ) );

        status |= NS(LimitRectEllipse_set_y_max)( diff,
            NS(LimitRectEllipse_y_max)( lhs ) -
            NS(LimitRectEllipse_y_max)( rhs ) );

        status |= NS(LimitRectEllipse_set_a_squ)( diff,
            NS(LimitRectEllipse_a_squ)( lhs ) -
            NS(LimitRectEllipse_a_squ)( rhs ) );

        status |= NS(LimitRectEllipse_set_b_squ)( diff,
            NS(LimitRectEllipse_b_squ)( lhs ) -
            NS(LimitRectEllipse_b_squ)( rhs ) );

        status |= NS(LimitRectEllipse_set_a_b_squ)( diff,
            NS(LimitRectEllipse_a_b_squ)( lhs ) -
            NS(LimitRectEllipse_a_b_squ)( rhs ) );
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_LIMIT_H__ */
