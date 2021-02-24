#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAMFIELDS_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAMFIELDS_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_BE_BEAMFIELDS_R_SQU_THRESHOLD )
    #define SIXTRL_BE_BEAMFIELDS_R_SQU_THRESHOLD 1.0e-10
#endif /* !defined( SIXTRL_BE_BEAMFIELDS_R_SQU_THRESHOLD ) */

#if !defined( SIXTRL_BE_BEAMFIELDS_DEFAULT_MIN_SIGMA_DIFF )
    #define SIXTRL_BE_BEAMFIELDS_DEFAULT_MIN_SIGMA_DIFF 1.0e-8
#endif /* !defined( SIXTRL_BE_BEAMFIELDS_DEFAULT_MIN_SIGMA_DIFF ) */

#if !defined( SIXTRL_FADDEEVA_CERN_A_CONSTANT )
    #define SIXTRL_FADDEEVA_CERN_A_CONSTANT 1.12837916709551
#endif /* !defined( SIXTRL_FADDEEVA_CERN_A_CONSTANT ) */

#if !defined( SIXTRL_FADDEEVA_CERN_X_LIMIT )
    #define SIXTRL_FADDEEVA_CERN_X_LIMIT 5.33
#endif /* !defined( SIXTRL_FADDEEVA_CERN_X_LIMIT ) */

#if !defined( SIXTRL_FADDEEVA_CERN_Y_LIMIT )
    #define SIXTRL_FADDEEVA_CERN_Y_LIMIT 4.29
#endif /* !defined( SIXTRL_FADDEEVA_CERN_Y_LIMIT ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(be_real_type) const NS(BE_BEAMFIELDS_R_SQU_THRESHOLD) =
    ( NS(be_real_type) )SIXTRL_BE_BEAMFIELDS_R_SQU_THRESHOLD;

SIXTRL_STATIC_VAR NS(be_real_type) const NS(BE_BEAMFIELDS_DEFAULT_MIN_SIGMA_DIFF)
    = ( NS(be_real_type) )SIXTRL_BE_BEAMFIELDS_DEFAULT_MIN_SIGMA_DIFF;

SIXTRL_STATIC_VAR NS(be_real_type) const NS(FADDEEVA_CERN_A_CONSTANT)
    = ( NS(be_real_type) )SIXTRL_FADDEEVA_CERN_A_CONSTANT;

SIXTRL_STATIC_VAR NS(be_real_type) const NS(FADDEEVA_CERN_X_LIMIT)
    = ( NS(be_real_type) )SIXTRL_FADDEEVA_CERN_X_LIMIT;

SIXTRL_STATIC_VAR NS(be_real_type) const NS(FADDEEVA_CERN_Y_LIMIT)
    = ( NS(be_real_type) )SIXTRL_FADDEEVA_CERN_Y_LIMIT;

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE {

    #if !defined( _GPUCODE )
    static constexpr be_real_type BE_BEAMFIELDS_R_SQU_THRESHOLD =
        static_cast< be_real_type >( SIXTRL_BE_BEAMFIELDS_R_SQU_THRESHOLD );

    static constexpr be_real_type BE_BEAMFIELDS_DEFAULT_MIN_SIGMA_DIFF =
        static_cast< be_real_type >( SIXTRL_BE_BEAMFIELDS_DEFAULT_MIN_SIGMA_DIFF );

    static constexpr be_real_type FADDEEVA_CERN_A_CONSTANT =
        static_cast< be_real_type >( SIXTRL_FADDEEVA_CERN_A_CONSTANT);

    static constexpr be_real_type FADDEEVA_CERN_X_LIMIT =
        static_cast< be_real_type >( SIXTRL_FADDEEVA_CERN_X_LIMIT);

    static constexpr be_real_type FADDEEVA_CERN_Y_LIMIT =
        static_cast< be_real_type >( SIXTRL_FADDEEVA_CERN_Y_LIMIT);

    #endif /* !defined( _GPUCODE ) */

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAMFIELDS_DEFINITIONS_H__ */
