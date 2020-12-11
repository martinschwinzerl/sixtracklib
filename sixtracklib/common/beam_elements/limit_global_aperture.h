#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_LIMIT_GLOBAL_APERTURE_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_LIMIT_GLOBAL_APERTURE_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/track/track_config.h"
    #include "sixtracklib/common/particles/particle_unit.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< ParticleT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    LimitGlobalAperture_perform_check(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT /*p*/,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT /*track_config*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class ParticleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    LimitGlobalAperture_perform_check(
        SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
        SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( track_config != SIXTRL_NULLPTR );

        typedef typename st::ParticleTraits< ParticleT >::real_t  real_t;
        typedef typename st::ParticleTraits< ParticleT >::index_t state_t;
        typedef typename st::TypeCompLogicTypeTraits< real_t >::cmp_result_t
                         cmp_result_t;

        state_t state  = st::Particle_state( p );

        state &= st::Type_comp_more_or_equal< real_t, cmp_result_t, real_t >(
                    st::Particle_x( p ), static_cast< real_t >(
                        track_config->m_global_aperture_check_min_x ) );

        state &= st::Type_comp_less_or_equal< real_t, cmp_result_t, real_t >(
                    st::Particle_x( p ), static_cast< real_t >(
                        track_config->m_global_aperture_check_max_x ) );

        state &= st::Type_comp_more_or_equal< real_t, cmp_result_t, real_t >(
                    st::Particle_y( p ), static_cast< real_t >(
                        track_config->m_global_aperture_check_min_y ) );

        state &= st::Type_comp_less_or_equal< real_t, cmp_result_t, real_t >(
                    st::Particle_y( p ), static_cast< real_t >(
                        track_config->m_global_aperture_check_max_y ) );

        return st::Particle_set_state( p, state );
    }
}

template< class ParticleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(LimitGlobalAperture_perform_check)(
    SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const ::NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config )
{
    return SIXTRL_CXX_NAMESPACE::LimitGlobalAperture_perform_check(
        p, track_config );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(LimitGlobalAperture_perform_check)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* ************************************************************************* */
/* ****                        Implementation                           **** */
/* ************************************************************************* */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(arch_status_t) NS(LimitGlobalAperture_perform_check)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT p,
    SIXTRL_TRACK_CONFIG_ARGPTR_DEC const NS(TrackConfig) *const
            SIXTRL_RESTRICT track_config ) SIXTRL_NOEXCEPT
{
    typedef NS(particle_index_t) state_t;
    SIXTRL_ASSERT( track_config != SIXTRL_NULLPTR );

    state_t  state = NS(Particle_state)( p );
    state &= ( state_t )( NS(Particle_x)( p ) >=
                          track_config->m_global_aperture_check_min_x );
    state &= ( state_t )( NS(Particle_x)( p ) <=
                          track_config->m_global_aperture_check_max_x );
    state &= ( state_t )( NS(Particle_y)( p ) >=
                          track_config->m_global_aperture_check_min_y );
    state &= ( state_t )( NS(Particle_y)( p ) <=
                          track_config->m_global_aperture_check_max_y );
    return NS(Particle_set_state)( p, state );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_LIMIT_GLOBAL_APERTURE_H__ */
