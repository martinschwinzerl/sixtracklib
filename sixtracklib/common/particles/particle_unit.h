#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/internal/type_annotations.h"

    #if defined( __cplusplus )
        #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

typedef struct
SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_PARTICLE_ARGPTR_DEC" )
NS(Particle)
{
    NS(particle_real_t) x             SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_real_t) px            SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_real_t) y             SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_real_t) py            SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_real_t) zeta          SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_real_t) delta         SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_index_t) state        SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

    NS(particle_index_t) at_element   SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_index_t) at_turn      SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_index_t) id           SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_real_t) psigma        SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_real_t) rpp           SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

    NS(particle_real_t) rvv           SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

    NS(particle_real_t) chi           SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

    NS(particle_real_t) charge_ratio  SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

    NS(particle_real_t) charge0       SIXTRL_ALIGN( 8 );
    NS(particle_real_t) mass0         SIXTRL_ALIGN( 8 );
    NS(particle_real_t) beta0         SIXTRL_ALIGN( 8 );
    NS(particle_real_t) gamma0        SIXTRL_ALIGN( 8 );
    NS(particle_real_t) pc0           SIXTRL_ALIGN( 8 );

    NS(particle_real_t) s             SIXTRL_ALIGN( 8 )
                                      SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
}
NS(Particle);

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataParticleTraits< ::NS(Particle) >
    {
        static constexpr bool is_type = true;
        static constexpr particle_unit_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::PARTICLE_UNIT_IMPL_DEFAULT;
    };

    template<> struct ParticleTraits< ::NS(Particle) >
    {
        typedef particle_real_t         real_t;
        typedef particle_index_t        index_t;
        typedef particle_num_elements_t num_elements_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

        static constexpr arch_size_t index_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< index_t >();

        static constexpr num_elements_t num_particles = num_elements_t{ 1 };
    };

    template<> struct ObjDataCApiTypeTraits< ::NS(Particle) >
    {
        typedef ::NS(Particle) c_api_t;
    };

    typedef ::NS(Particle)  CParticle;
}
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_H__ */
