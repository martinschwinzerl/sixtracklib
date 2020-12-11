#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_DATA_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beam_monitor/definitions.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor.h"

    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle_set.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    struct
    SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
    SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
    SIXTRL_ANNOTATE_ELEM_OBJ_API_NAME( "BeamMonitor" )
    BeamMonitorData
    {
        I                       num_stores
                                SIXTRL_ALIGN( IAlign )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        I                       start_turn
                                SIXTRL_ALIGN( IAlign )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        I                       skip_turns
                                SIXTRL_ALIGN( IAlign )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        NS(belem_address_t)     out_address
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_EXT_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME(
                                    "particle_set" )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC(
                                    SIXTRL_PARTICLE_SET_ARGPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE(
                                    "SIXTRL_CXX_NAMESPACE::TParticleSet< R, I >" );

        I                       max_particle_id
                                SIXTRL_ALIGN( IAlign )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        I                       min_particle_id
                                SIXTRL_ALIGN( IAlign )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        NS(be_monitor_flag_t)   is_rolling_flag
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        NS(be_monitor_flag_t)   is_turn_ordered_flag
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
    };

    /* ********************************************************************* */
    /* Specializations for BeamMonitorData: */
    /* ********************************************************************* */

    template< class R, class I, arch_size_t IAlign >
    struct BeamMonitorTraits< BeamMonitorData< R, I, IAlign > >
    {
        typedef TParticleSet< R, I > particle_set_t;
        typedef typename ParticleSetTraits< particle_set_t >::real_t
                particle_real_t;

        typedef typename ParticleSetTraits< particle_set_t >::index_t
                particle_index_t;

        static constexpr arch_size_t particle_set_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< particle_set_t >();

        static constexpr arch_size_t particle_real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< R >();

        static constexpr arch_size_t particle_index_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< I >();
    };

    template< class R, class I, arch_size_t IAlign >
    constexpr arch_size_t BeamMonitorTraits< BeamMonitorData< R, I, IAlign >
        >::particle_set_alignment;

    template< class R, class I, arch_size_t IAlign >
    constexpr arch_size_t BeamMonitorTraits< BeamMonitorData< R, I, IAlign >
        >::particle_real_alignment;

    template< class R, class I, arch_size_t IAlign >
    constexpr arch_size_t BeamMonitorTraits< BeamMonitorData< R, I, IAlign >
        >::particle_index_alignment;

    /* ********************************************************************* */
    /* Create an equivalency between the ::NS(BeamMonitor) type and the
     * corresponding specialization of the BeamMonitorData template */
    /* ********************************************************************* */

    typedef BeamMonitorData<
        typename BeamMonitorTraits< ::NS(BeamMonitor) >::particle_real_t,
        typename BeamMonitorTraits< ::NS(BeamMonitor) >::particle_index_t,
        BeamMonitorTraits< ::NS(BeamMonitor) >::particle_index_alignment >
        CBeamMonitorEquivData;

    template<> struct ObjDataCApiTypeTraits< CBeamMonitorEquivData >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                CBeamMonitorEquivData, ::NS(BeamMonitor) >(),
            "CBeamMonitorEquivData and ::NS(BeamMonitor) are not equivalent C-Api types" );

        typedef ::NS(BeamMonitor) c_api_t;
    };
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_DATA_CXX_HPP__ */
