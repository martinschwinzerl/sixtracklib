#ifndef SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_BEAMFIELDS_H__
#define SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_BEAMFIELDS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
    #include "sixtracklib/common/beam_elements/beamfields/all_beamfields.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <algorithm>
    #include <iomanip>
    #include <ostream>
    #include <random>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(SCCoasting_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type)
NS(SCCoasting_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance,
    NS(be_real_type) const abs_tolerance ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCCoasting_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type) NS(SCQGaussProfile_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(cmp_result_type)
NS(SCQGaussProfile_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance,
    NS(be_real_type) const abs_tolerance ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(status_type) NS(SCQGaussProfile_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE {
namespace testlib {

template< class PrngT, class NumParticlesDistT, class CircumferenceDistT,
        class SigmaXDistT, class SigmaYDistT, class SigmaXEqualSigmaYDistT,
        class LengthDistT,
        class XCoDistT, class YCoDistT, class MinSigmaDiffDistT,
        class IsEnabledDistT >
SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_INLINE
::NS(status_type) SCCoasting_init_random(
    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(SCCoasting)* SIXTRL_RESTRICT sc,
    PrngT& prng, NumParticlesDistT& num_particles_dist,
    CircumferenceDistT& circumference_dist,
    SigmaXDistT& sigma_x_dist, SigmaYDistT& sigma_y_dist,
    SigmaXEqualSigmaYDistT& sigma_x_equals_sigma_y_dist,
    typename SigmaXEqualSigmaYDistT::result_type const sigmax_equ_y_threshold,
    LengthDistT& length_dist, XCoDistT& x_co_dist, YCoDistT& y_co_dist,
    MinSigmaDiffDistT& min_sigma_diff_dist, IsEnabledDistT& is_enabled_dist,
    typename IsEnabledDistT::result_type const enabled_threshold =
        typename IsEnabledDistT::result_type{ 0. } )
{
    auto const nparticles = num_particles_dist( prng );
    auto const circumference = circumference_dist( prng );
    auto const sigma_x = sigma_x_dist( prng );
    auto sigma_y = sigma_y_dist( prng );
    if( sigma_x_equals_sigma_y_dist( prng ) >= sigmax_equ_y_threshold )
        sigma_y = sigma_x;

    auto const length = length_dist( prng );
    auto const x_co = x_co_dist( prng );
    auto const y_co = y_co_dist( prng );
    auto const min_sigma_diff = min_sigma_diff_dist( prng );
    bool const is_enabled = ( is_enabled_dist( prng ) >= enabled_threshold );

    return ::NS(SCCoasting_init)( sc, nparticles, circumference, sigma_x,
        sigma_y, length, x_co, y_co, min_sigma_diff, is_enabled );
}

SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_INLINE void NS(SCCoasting_to_stream)(
    std::ostream& output,
    SIXTRL_BE_ARGPTR_DEC ::NS(SCCoasting) const& SIXTRL_RESTRICT_REF sc ) {
    output << "SCCoasting: \r\n"
           << "num_of_particles : " << std::setw( 20 )
           << ::NS(SCCoasting_number_of_particles)( &sc ) << "\r\n"
           << "circumference    : " << std::setw( 20 )
           << ::NS(SCCoasting_circumference)( &sc ) << "\r\n"
           << "sigma_x          : " << std::setw( 20 )
           << ::NS(SCCoasting_sigma_x)( &sc ) << "\r\n"
           << "sigma_y          : " << std::setw( 20 )
           << ::NS(SCCoasting_sigma_y)( &sc ) << "\r\n"
           << "length           : " << std::setw( 20 )
           << ::NS(SCCoasting_length)( &sc ) << "\r\n"
           << "x_co             : " << std::setw( 20 )
           << ::NS(SCCoasting_x_co)( &sc ) << "\r\n"
           << "y_co             : " << std::setw( 20 )
           << ::NS(SCCoasting_y_co)( &sc ) << "\r\n"
           << "min_sigma_diff   : " << std::setw( 20 )
           << ::NS(SCCoasting_min_sigma_diff)( &sc ) << "\r\n"
           << "is_enabled       : " << std::boolalpha
           << ::NS(SCCoasting_enabled)( &sc ) << std::noboolalpha << "\r\n";
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

template< class PrngT, class NumParticlesDistT, class BunchlengthRmsDistT,
        class SigmaXDistT, class SigmaYDistT, class SigmaXEqualSigmaYDistT,
        class LengthDistT,
        class XCoDistT, class YCoDistT, class MinSigmaDiffDistT,
        class QParamDistT, class IsEnabledDistT >
SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_INLINE
::NS(status_type) SCQGaussProfile_init_random(
    SIXTRL_PARTICLES_ARGPTR_DEC ::NS(SCQGaussProfile)* SIXTRL_RESTRICT sc,
    PrngT& prng, NumParticlesDistT& num_particles_dist,
    BunchlengthRmsDistT& bunchlength_rms_dist,
    SigmaXDistT& sigma_x_dist, SigmaYDistT& sigma_y_dist,
    SigmaXEqualSigmaYDistT& sigma_x_equals_sigma_y_dist,
    typename SigmaXEqualSigmaYDistT::result_type const sigmax_equ_y_threshold,
    LengthDistT& length_dist, XCoDistT& x_co_dist, YCoDistT& y_co_dist,
    MinSigmaDiffDistT& min_sigma_diff_dist,
    QParamDistT& q_param_dist, IsEnabledDistT& is_enabled_dist,
    typename IsEnabledDistT::result_type const enabled_threshold =
        typename IsEnabledDistT::result_type{ 0. } )
{
    auto const nparticles = num_particles_dist( prng );
    auto const bunchlength_rms = bunchlength_rms_dist( prng );
    auto const sigma_x = sigma_x_dist( prng );
    auto sigma_y = sigma_y_dist( prng );
    if( sigma_x_equals_sigma_y_dist( prng ) >= sigmax_equ_y_threshold )
        sigma_y = sigma_x;

    auto const length = length_dist( prng );
    auto const x_co = x_co_dist( prng );
    auto const y_co = y_co_dist( prng );
    auto const min_sigma_diff = min_sigma_diff_dist( prng );
    auto const q_param = q_param_dist( prng );
    bool const is_enabled = ( is_enabled_dist( prng ) >= enabled_threshold );

    return ::NS(SCQGaussProfile_init)( sc, nparticles, bunchlength_rms, sigma_x,
        sigma_y, length, x_co, y_co, min_sigma_diff, q_param, is_enabled );
}

SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_INLINE void NS(SCQGaussProfile_to_stream)(
    std::ostream& output,
    SIXTRL_BE_ARGPTR_DEC ::NS(SCQGaussProfile) const& SIXTRL_RESTRICT_REF sc ) {
    output << "SCCoasting: \r\n"
           << "num_of_particles : " << std::setw( 20 )
           << ::NS(SCQGaussProfile_number_of_particles)( &sc ) << "\r\n"
           << "bunchlength_rms    : " << std::setw( 20 )
           << ::NS(SCQGaussProfile_bunchlength_rms)( &sc ) << "\r\n"
           << "sigma_x          : " << std::setw( 20 )
           << ::NS(SCQGaussProfile_sigma_x)( &sc ) << "\r\n"
           << "sigma_y          : " << std::setw( 20 )
           << ::NS(SCQGaussProfile_sigma_y)( &sc ) << "\r\n"
           << "length           : " << std::setw( 20 )
           << ::NS(SCQGaussProfile_length)( &sc ) << "\r\n"
           << "x_co             : " << std::setw( 20 )
           << ::NS(SCQGaussProfile_x_co)( &sc ) << "\r\n"
           << "y_co             : " << std::setw( 20 )
           << ::NS(SCQGaussProfile_y_co)( &sc ) << "\r\n"
           << "min_sigma_diff   : " << std::setw( 20 )
           << ::NS(SCQGaussProfile_min_sigma_diff)( &sc ) << "\r\n"
           << "q_param          : " << std::setw( 20 )
           << ::NS(SCQGaussProfile_q_param)( &sc ) << "\r\n"
           << "cq               : " << std::setw( 20 )
           << ::NS(SCQGaussProfile_cq)( &sc ) << "\r\n"
           << "is_enabled       : " << std::boolalpha
           << ::NS(SCQGaussProfile_enabled)( &sc )
           << std::noboolalpha << "\r\n";
}

} /* end: namespace testlib */
} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* C++ */

/* ========================================================================== */
/* ========================================================================== */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(cmp_result_type) NS(SCCoasting_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT { return NS(SCCoasting_compare_with_tolerances)( lhs, rhs,
    ( NS(be_real_type) )0.0, ( NS(be_real_type) )SIXTRL_REAL_TYPE_EPS ); }

SIXTRL_INLINE NS(cmp_result_type) NS(SCCoasting_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance,
    NS(be_real_type) const abs_tolerance ) SIXTRL_NOEXCEPT {


    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            result = NS(Type_value_comp_result_with_tolerances)(
                NS(SCCoasting_number_of_particles)( lhs ),
                NS(SCCoasting_number_of_particles)( rhs ),
                rel_tolerance, abs_tolerance );

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCCoasting_circumference)( lhs ),
                    NS(SCCoasting_circumference)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCCoasting_sigma_x)( lhs ),
                    NS(SCCoasting_sigma_x)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCCoasting_sigma_y)( lhs ),
                    NS(SCCoasting_sigma_y)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCCoasting_length)( lhs ),
                    NS(SCCoasting_length)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCCoasting_x_co)( lhs ),
                    NS(SCCoasting_x_co)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCCoasting_y_co)( lhs ),
                    NS(SCCoasting_y_co)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCCoasting_min_sigma_diff)( lhs ),
                    NS(SCCoasting_min_sigma_diff)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( ( result == ( NS(cmp_result_type) )0 ) &&
                ( NS(SCCoasting_enabled)( lhs ) !=
                  NS(SCCoasting_enabled)( rhs ) ) )
            {
                result = ( NS(SCCoasting_enabled)( lhs ) )
                    ? ( NS(cmp_result_type) )1 : ( NS(cmp_result_type) )-1;
            }
        }
    }
    else if( rhs != SIXTRL_NULLPTR )
    {
        result = ( NS(cmp_result_type) )-1;
    }
    return result;
}

SIXTRL_INLINE NS(status_type) NS(SCCoasting_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) )
    {
        diff->number_of_particles = NS(SCCoasting_number_of_particles)( lhs ) -
                                    NS(SCCoasting_number_of_particles)( rhs );

        diff->circumference    = NS(SCCoasting_circumference)( lhs ) -
                                 NS(SCCoasting_circumference)( rhs );

        diff->sigma_x = NS(SCCoasting_sigma_x)( lhs ) -
                        NS(SCCoasting_sigma_x)( rhs );

        diff->sigma_y = NS(SCCoasting_sigma_y)( lhs ) -
                        NS(SCCoasting_sigma_y)( rhs );

        diff->length  = NS(SCCoasting_length)( lhs ) -
                        NS(SCCoasting_length)( rhs );

        diff->x_co = NS(SCCoasting_x_co)( lhs ) - NS(SCCoasting_x_co)( rhs );
        diff->y_co = NS(SCCoasting_y_co)( lhs ) - NS(SCCoasting_y_co)( rhs );

        diff->min_sigma_diff = NS(SCCoasting_min_sigma_diff)( lhs ) -
                               NS(SCCoasting_min_sigma_diff)( rhs );

        status = NS(SCCoasting_set_enabled)( diff,
            ( NS(SCCoasting_enabled)( lhs ) == NS(SCCoasting_enabled)( rhs ) ) );
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(cmp_result_type) NS(SCQGaussProfile_compare)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT { return NS(SCQGaussProfile_compare_with_tolerances)( lhs, rhs,
    ( NS(be_real_type) )0.0, ( NS(be_real_type) )SIXTRL_REAL_TYPE_EPS ); }

SIXTRL_INLINE NS(cmp_result_type) NS(SCQGaussProfile_compare_with_tolerances)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT rhs,
    NS(be_real_type) const rel_tolerance,
    NS(be_real_type) const abs_tolerance ) SIXTRL_NOEXCEPT {


    NS(cmp_result_type) result = ( NS(cmp_result_type) )1;
    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        result = ( NS(cmp_result_type) )0u;

        if( lhs != rhs )
        {
            result = NS(Type_value_comp_result_with_tolerances)(
                NS(SCQGaussProfile_number_of_particles)( lhs ),
                NS(SCQGaussProfile_number_of_particles)( rhs ),
                rel_tolerance, abs_tolerance );

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCQGaussProfile_bunchlength_rms)( lhs ),
                    NS(SCQGaussProfile_bunchlength_rms)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCQGaussProfile_sigma_x)( lhs ),
                    NS(SCQGaussProfile_sigma_x)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCQGaussProfile_sigma_y)( lhs ),
                    NS(SCQGaussProfile_sigma_y)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCQGaussProfile_length)( lhs ),
                    NS(SCQGaussProfile_length)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCQGaussProfile_x_co)( lhs ),
                    NS(SCQGaussProfile_x_co)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCQGaussProfile_y_co)( lhs ),
                    NS(SCQGaussProfile_y_co)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCQGaussProfile_min_sigma_diff)( lhs ),
                    NS(SCQGaussProfile_min_sigma_diff)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCQGaussProfile_q_param)( lhs ),
                    NS(SCQGaussProfile_q_param)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( result == ( NS(cmp_result_type) )0 )
            {
                result = NS(Type_value_comp_result_with_tolerances)(
                    NS(SCQGaussProfile_cq)( lhs ),
                    NS(SCQGaussProfile_cq)( rhs ),
                    rel_tolerance, abs_tolerance );
            }

            if( ( result == ( NS(cmp_result_type) )0 ) &&
                ( NS(SCQGaussProfile_enabled)( lhs ) !=
                  NS(SCQGaussProfile_enabled)( rhs ) ) )
            {
                result = ( NS(SCQGaussProfile_enabled)( lhs ) )
                    ? ( NS(cmp_result_type) )1 : ( NS(cmp_result_type) )-1;
            }
        }
    }
    else if( rhs != SIXTRL_NULLPTR )
    {
        result = ( NS(cmp_result_type) )-1;
    }
    return result;
}

SIXTRL_INLINE NS(status_type) NS(SCQGaussProfile_difference)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)* SIXTRL_RESTRICT diff
) SIXTRL_NOEXCEPT {
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    if( ( lhs  != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) && ( lhs != rhs ) && ( lhs != diff ) &&
        ( diff != rhs ) )
    {
        diff->number_of_particles =
            NS(SCQGaussProfile_number_of_particles)( lhs ) -
            NS(SCQGaussProfile_number_of_particles)( rhs );

        diff->bunchlength_rms = NS(SCQGaussProfile_bunchlength_rms)( lhs ) -
                                NS(SCQGaussProfile_bunchlength_rms)( rhs );

        diff->sigma_x = NS(SCQGaussProfile_sigma_x)( lhs ) -
                        NS(SCQGaussProfile_sigma_x)( rhs );

        diff->sigma_y = NS(SCQGaussProfile_sigma_y)( lhs ) -
                        NS(SCQGaussProfile_sigma_y)( rhs );

        diff->length  = NS(SCQGaussProfile_length)( lhs ) -
                        NS(SCQGaussProfile_length)( rhs );

        diff->x_co = NS(SCQGaussProfile_x_co)( lhs ) -
                     NS(SCQGaussProfile_x_co)( rhs );

        diff->y_co = NS(SCQGaussProfile_y_co)( lhs ) -
                     NS(SCQGaussProfile_y_co)( rhs );

        diff->min_sigma_diff = NS(SCQGaussProfile_min_sigma_diff)( lhs ) -
                               NS(SCQGaussProfile_min_sigma_diff)( rhs );

        diff->q_param = NS(SCQGaussProfile_q_param)( lhs ) -
                        NS(SCQGaussProfile_q_param)( rhs );

        diff->cq = NS(SCQGaussProfile_cq)( lhs ) -
                   NS(SCQGaussProfile_cq)( rhs );

        status = NS(SCQGaussProfile_set_enabled)( diff,
            ( NS(SCQGaussProfile_enabled)( lhs ) ==
              NS(SCQGaussProfile_enabled)( rhs ) ) );
    }

    return status;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_BEAMFIELDS_H__ */

