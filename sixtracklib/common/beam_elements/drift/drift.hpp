#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/definitions.h"
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
    SIXTRL_ANNOTATE_ELEM_OBJ_API_NAME( Drift )
    SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
    TDrift
    {
        R                       length SIXTRL_ALIGN( RAlign )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        be_drift_track_type_t   track_type SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE(
                                    SIXTRL_BE_DRIFT_TRACK_TYPE_SIMPLE );
    };

    /* ********************************************************************* */
    /* Specializations for TDrift: */
    /* ********************************************************************* */

    template< class R, arch_size_t RAlign >
    struct ObjDataBeamElementsTraits< TDrift< R, RAlign > >
    {
        static constexpr bool is_beam_element = true;
    };

    template< class R, arch_size_t RAlign >
    constexpr bool ObjDataBeamElementsTraits<
        TDrift< R, RAlign > >::is_beam_element;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, arch_size_t RAlign >
    struct ObjDataDriftTraits< TDrift< R, RAlign > >
    {
        static constexpr bool is_type = true;
        static constexpr be_drift_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_DRIFT_IMPL_DEFAULT;
    };

    template< class R, arch_size_t RAlign >
    constexpr bool ObjDataDriftTraits< TDrift< R, RAlign > >::is_type;

    template< class R, arch_size_t RAlign >
    constexpr be_drift_impl_t ObjDataDriftTraits<
        TDrift< R, RAlign > >::implementation;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, arch_size_t RAlign >
    struct DriftTraits< TDrift< R, RAlign > >
    {
        typedef typename TypeMethodParamTraits< R >::value_type real_t;
        static constexpr arch_size_t real_alignment = RAlign;
    };

    template< class R, arch_size_t RAlign >
    constexpr arch_size_t DriftTraits< TDrift< R,RAlign > >::real_alignment;

    /* ********************************************************************* */
    /* Create an equivalency between the ::NS(Drift) type and the
     * corresponding specialization of the TDrift template */
    /* ********************************************************************* */

    typedef TDrift< DriftTraits< ::NS(Drift) >::real_t,
                    DriftTraits< ::NS(Drift) >::real_alignment > Drift;

    template<> struct ObjDataCApiTypeTraits< Drift >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                Drift, ::NS(Drift) >(),
            "Drift and ::NS(Drift) are not equivalent C-Api types" );

        typedef ::NS(Drift) c_api_t;
    };
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_CXX_HPP__ */
