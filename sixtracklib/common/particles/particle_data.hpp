#ifndef SIXTRACKLIB_COMMON_PARTICLE_PARTICLE_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLE_PARTICLE_DATA_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class I,
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(),
        arch_size_t IAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    struct ParticleData
    {
        real_t  x             SIXTRL_ALIGN( RAlign );
        real_t  px            SIXTRL_ALIGN( RAlign );
        real_t  y             SIXTRL_ALIGN( RAlign );
        real_t  py            SIXTRL_ALIGN( RAlign );
        real_t  zeta          SIXTRL_ALIGN( RAlign );
        real_t  delta         SIXTRL_ALIGN( RAlign );
        real_t  psigma        SIXTRL_ALIGN( RAlign );

        index_t state         SIXTRL_ALIGN( IAlign );
        index_t at_element    SIXTRL_ALIGN( IAlign );
        index_t at_turn       SIXTRL_ALIGN( IAlign );
        index_t id            SIXTRL_ALIGN( IAlign );

        real_t  s             SIXTRL_ALIGN( RAlign );
        real_t  rvv           SIXTRL_ALIGN( RAlign );
        real_t  rpp           SIXTRL_ALIGN( RAlign );
        real_t  chi           SIXTRL_ALIGN( RAlign );
        real_t  charge_ratio  SIXTRL_ALIGN( RAlign );

        real_t  charge0       SIXTRL_ALIGN( RAlign );
        real_t  mass0         SIXTRL_ALIGN( RAlign );
        real_t  beta0         SIXTRL_ALIGN( RAlign );
        real_t  gamma0        SIXTRL_ALIGN( RAlign );
        real_t  pc0           SIXTRL_ALIGN( RAlign );
    };

    /* ********************************************************************* */
    /* Specializations for ParticleData: */
    /* ********************************************************************* */

    template< class R, class I, arch_size_t RAlign, arch_size_t IAlign >
    struct ParticleTraits< ParticleData< R, I, RAlign, IAlign > >
    {
        typedef R real_t;
        typedef I index_t;

        static constexpr arch_size_t real_alignment  = RAlign;
        static constexpr arch_size_t index_alignment = IAlign;
    };

    template< class R, class I, arch_size_t RAlign, arch_size_t IAlign >
    constexpr arch_size_t ParticleTraits<
        ParticleData< R, I, RAlign, IAlign > >::real_alignment;

    template< class R, class I, arch_size_t RAlign, arch_size_t IAlign >
    constexpr arch_size_t ParticleTraits<
        ParticleData< R, I, RAlign, IAlign > >::index_alignment;

    /* ********************************************************************* */
    /* Create an equivalency between the ::NS(Particle) type and the
     * corresponding specialization of the ParticleData template */
    /* ********************************************************************* */

    typedef ParticleData<
                typename ParticleTraits< ::NS(Particle) >::real_t,
                typename ParticleTraits< ::NS(Particle) >::index_t,
                ParticleTraits< ::NS(Particle) >::real_alignment,
                ParticleTraits< ::NS(Particle) >::index_alignment > >
        CParticleEquivData;

    template<> struct ObjDataCApiTypeTraits< CParticleEquivData >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                CParticleEquivData, ::NS(Particle) >(),
        "CParticleEquivData and ::NS(Particle) are not equivalent C-Api types");

        typedef ::NS(Particle) c_api_t;
    };
}

#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_PARTICLE_PARTICLE_DATA_CXX_HPP__ */
