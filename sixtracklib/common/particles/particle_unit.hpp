#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_unit.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class I,
        arch_size_t N = arch_size_t{ 1 },
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(),
        arch_size_t IAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
    SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_PARTICLE_ARGPTR_DEC" )
    SIXTRL_ANNOTATE_ELEM_OBJ_API_NAME( "Particle" )
    TParticle
    {
        R  x             SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R  px            SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R  y             SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R  py            SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R  zeta          SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R  delta         SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        I state          SIXTRL_ALIGN( IAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

        I at_element     SIXTRL_ALIGN( IAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        I at_turn        SIXTRL_ALIGN( IAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        I id             SIXTRL_ALIGN( IAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R  psigma        SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R  rpp           SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

        R  rvv           SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

        R  chi           SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

        R  charge_ratio  SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

        R  charge0       SIXTRL_ALIGN( RAlign );
        R  mass0         SIXTRL_ALIGN( RAlign );

        R  beta0         SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R  gamma0        SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

        R  pc0           SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R  s             SIXTRL_ALIGN( RAlign )
                         SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
    };

    /* ********************************************************************* */
    /* Specializations for DriftData: */
    /* ********************************************************************* */

    template< class R, class I, arch_size_t N,
              arch_size_t RAlign, arch_size_t IAlign >
    struct ObjDataParticleTraits< TParticle< R, I, N, RAlign, IAlign > >
    {
        static constexpr bool is_type = true;
        static constexpr particle_unit_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::PARTICLE_UNIT_IMPL_DEFAULT;
    };

    template< class R, class I, arch_size_t N,
              arch_size_t RAlign, arch_size_t IAlign >
    constexpr bool ObjDataParticleTraits<
        TParticle< R, I, N, RAlign, IAlign > >::is_type;

    template< class R, class I, arch_size_t N, arch_size_t RAlign,
              arch_size_t IAlign >
    constexpr particle_unit_impl_t ObjDataParticleTraits<
        TParticle< R, I, N, RAlign, IAlign > >::implementation;

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class R, class I, arch_size_t N,
              arch_size_t RAlign, arch_size_t IAlign >
    struct ParticleTraits< TParticle< R, I, N, RAlign, IAlign > >
    {
        typedef typename TypeMethodParamTraits< R >::value_type  real_t;
        typedef typename TypeMethodParamTraits< I >::value_type index_t;
        typedef particle_num_elements_t num_elements_t;
        typedef typename TypeCompLogicTypeTraits< index_t >::logic_t logic_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

        static constexpr arch_size_t index_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< index_t >();

        static constexpr num_elements_t num_particles =
            static_cast< num_elements_t >( N );
    };

    template< class R, class I, arch_size_t N,
              arch_size_t RAlign, arch_size_t IAlign >
    constexpr arch_size_t ParticleTraits<
        TParticle< R, I, N, RAlign, IAlign > >::real_alignment;

    template< class R, class I, arch_size_t N,
              arch_size_t RAlign, arch_size_t IAlign >
    constexpr arch_size_t ParticleTraits<
        TParticle< R, I, N, RAlign, IAlign > >::index_alignment;

    template< class R, class I, arch_size_t N,
              arch_size_t RAlign, arch_size_t IAlign >
    constexpr particle_num_elements_t ParticleTraits<
        TParticle< R, I, N, RAlign, IAlign > >::num_particles;

    /* ********************************************************************* */
    /* Specializations for TParticle: */
    /* ********************************************************************* */

    /* ********************************************************************* */
    /* Create an equivalency between the ::NS(Drift) type and the
     * corresponding specialization of the DriftData template */
    /* ********************************************************************* */

    typedef TParticle<
            ParticleTraits< ::NS(Particle) >::real_t,
            ParticleTraits< ::NS(Particle) >::index_t,
            ParticleTraits< ::NS(Particle) >::num_particles,
            ParticleTraits< ::NS(Particle) >::real_alignment,
            ParticleTraits< ::NS(Particle) >::index_alignment > Particle;

    template<> struct ObjDataCApiTypeTraits< Particle >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                Particle, ::NS(Particle) >(),
            "Particle and ::NS(Particle) are not equivalent C-Api types" );

        typedef ::NS(Particle) c_api_t;
    };
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_CXX_HPP__ */
