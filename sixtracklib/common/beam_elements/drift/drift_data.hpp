#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DATA_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/definitions.h"
    #include "sixtracklib/common/beam_elements/drift/drift.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R,
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    struct DriftData
    {
        R length SIXTRL_ALIGN( RAlign );
    };

    /* ********************************************************************* */
    /* Specializations for DriftData: */
    /* ********************************************************************* */

    template< class R, arch_size_t RAlign >
    struct DriftTraits< DriftData< R, RAlign > >
    {
        typedef R real_t;
        static constexpr arch_size_t real_alignment = RAlign;
    };

    template< class R, arch_size_t RAlign >
    constexpr arch_size_t DriftTraits< DriftData< R,RAlign > >::real_alignment;

    /* ********************************************************************* */
    /* Create an equivalency between the ::NS(Drift) type and the
     * corresponding specialization of the DriftData template */
    /* ********************************************************************* */

    typedef DriftData< typename DriftTraits< ::NS(Drift) >::real_t,
                                DriftTraits< ::NS(Drift) >::real_alignment >
            CDriftEquivData;

    template<> struct ObjDataCApiTypeTraits< CDriftEquivData >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                CDriftEquivData, ::NS(Drift) >(),
            "CDriftEquivData and ::NS(Drift) are not equivalent C-Api types" );

        typedef ::NS(Drift) c_api_t;
    };






}

#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DATA_CXX_HPP__ */
