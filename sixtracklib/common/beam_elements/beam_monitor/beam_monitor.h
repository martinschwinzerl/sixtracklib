#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beam_monitor/definitions.h"
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_annotations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

typedef struct
SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
NS(BeamMonitor)
{
    NS(particle_index_t)    num_stores
                            SIXTRL_ALIGN( 8 )
                            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_index_t)    start_turn
                            SIXTRL_ALIGN( 8 )
                            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_index_t)    skip_turns
                            SIXTRL_ALIGN( 8 )
                            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(belem_address_t)     out_address
                            SIXTRL_ALIGN( 8 )
                            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                            SIXTRL_ANNOTATE_ELEM_FIELD_EXT_POINTER
                            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME(
                                "particle_set" )
                            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC(
                                "SIXTRL_PARTICLE_SET_ARGPTR_DEC" )
                            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE(
                                "NS(ParticleSet)" );

    NS(particle_index_t)    max_particle_id
                            SIXTRL_ALIGN( 8 )
                            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_index_t)    min_particle_id
                            SIXTRL_ALIGN( 8 )
                            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(be_monitor_flag_t)   is_rolling_flag
                            SIXTRL_ALIGN( 8 )
                            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(be_monitor_flag_t)   is_turn_ordered_flag
                            SIXTRL_ALIGN( 8 )
                            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
}
NS(BeamMonitor);

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct BeamMonitorTraits< ::NS(BeamMonitor) >
    {
        typedef ::NS(ParticleSet)  particle_set_t;
        typedef ParticleSetTraits< particle_set_t >::real_t   particle_real_t;
        typedef ParticleSetTraits< particle_set_t >::index_t  particle_index_t;

        static constexpr arch_size_t particle_set_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< particle_set_t >();

        static constexpr arch_size_t particle_real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< particle_real_t >();

        static constexpr arch_size_t particle_index_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< particle_index_t >();
    };

    template<> struct ObjDataCApiTypeTraits< ::NS(BeamMonitor) >
    {
        typedef ::NS(BeamMonitor) c_api_t;
    };
}
#endif /* C++ */

/* ------------------------------------------------------------------------- */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_C99_H__ */
