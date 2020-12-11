#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DRIFT_EXACT_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DRIFT_EXACT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift_exact/definitions.h"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
    SIXTRL_ANNOTATE_ELEM_OBJ_API_NAME( DriftExact )
    SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
    TDriftExact
    {
        R length SIXTRL_ALIGN( RAlign )
                 SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
    };

    /* ********************************************************************* */
    /* Specializations for TDriftExact: */
    /* ********************************************************************* */

    template< class R, arch_size_t RAlign >
    struct ObjDataBeamElementsTraits< TDriftExact< R, RAlign > >
    {
        static constexpr bool is_beam_element = true;
    };

    template< class R, arch_size_t RAlign >
    constexpr bool ObjDataBeamElementsTraits<
        TDriftExact< R, RAlign > >::is_beam_element;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, arch_size_t RAlign >
    struct ObjDataDriftExactTraits< TDriftExact< R, RAlign > >
    {
        static constexpr bool is_drift_exact = true;
    };

    template< class R, arch_size_t RAlign >
    constexpr bool ObjDataDriftExactTraits<
        TDriftExact< R, RAlign > >::is_drift_exact;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, arch_size_t RAlign >
    struct DriftExactTraits< TDriftExact< R, RAlign > >
    {
        typedef typename TypeMethodParamTraits< R >::value_type real_t;
        static constexpr arch_size_t real_alignment = RAlign;
    };

    template< class R, arch_size_t RAlign >
    constexpr arch_size_t DriftExactTraits<
        TDriftExact< R,RAlign > >::real_alignment;

    /* ********************************************************************* */
    /* Create an equivalency between the ::NS(DriftExact) type and the
     * corresponding specialization of the TDriftExact template */
    /* ********************************************************************* */

    typedef TDriftExact< DriftExactTraits< ::NS(DriftExact) >::real_t,
                         DriftExactTraits< ::NS(DriftExact) >::real_alignment >
            DriftExact;

    template<> struct ObjDataCApiTypeTraits< DriftExact >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                DriftExact, ::NS(DriftExact) >(),
                "DriftExact and ::NS(DriftExact) "
                "are not equivalent C-Api types" );

        typedef ::NS(DriftExact) c_api_t;
    };
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_EXACT_DRIFT_EXACT_CXX_HPP__ */
