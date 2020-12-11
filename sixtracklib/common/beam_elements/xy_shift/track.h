#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_TRACK_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_TRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/track/track_config.h"
    #include "sixtracklib/common/particles/particle_unit.h"
    #include "sixtracklib/common/particles/particle_unit_api.h"
    #include "sixtracklib/common/particles/particle_unit_derived_api.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleT, class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() ||
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    XYShift_track(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT /* p */,
        SIXTRL_BE_ARGPTR_DEC const XYShiftT *const SIXTRL_RESTRICT /* elem */,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT /* track_config */)
    {
        return SIXTRL_CXX_NAMESPACE::TRACK_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT, class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        SIXTRL_CXX_NAMESPACE::track_status_t >::type
    XYShift_track(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_BE_ARGPTR_DEC const XYShiftT *const SIXTRL_RESTRICT elem,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT /*track_config*/ )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        st::arch_status_t const status =
            st::Particle_subtract_from_x( p, st::XYShift_dx( elem ) ) |
            st::Particle_subtract_from_y( p, st::XYShift_dy( elem ) );

        SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
        ( void )status;

        return st::TRACK_SUCCESS;
    }
}

template< class ParticleT, class XYShiftT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::track_status_t
NS(XYShift_track)( SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const XYShiftT *const SIXTRL_RESTRICT elem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
        SIXTRL_RESTRICT track_config  )
{
    return SIXTRL_CXX_NAMESPACE::XYShift_track( p, elem, track_config );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(track_status_t) NS(XYShift_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT particle,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT drift,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* ****                        Implementation                           **** */
/* ************************************************************************* */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(track_status_t) NS(XYShift_track)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_BE_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT elem,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
            SIXTRL_RESTRICT /*track_config*/ ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) const status =
        NS(Particle_subtract_from_x)( p, NS(XYShift_dx)( elem ) ) |
        NS(Particle_subtract_from_y)( p, NS(XYShift_dy)( elem ) );

    SIXTRL_ASSERT( status != ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS );
    ( void )status;

    return ( NS(track_status_t) )SIXTRL_TRACK_SUCCESS;
}

#if defined( __cplusplus )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_TRACK_H__ */
