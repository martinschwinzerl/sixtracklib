#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_DATA_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/definitions.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    struct
    SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
    SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
    SIXTRL_ANNOTATE_ELEM_OBJ_API_NAME( "SRotation" )
    SRotationData
    {
        R cos_z SIXTRL_ALIGN( RAlign ) SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );
        R sin_z SIXTRL_ALIGN( RAlign ) SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
    };

    /* ********************************************************************* */
    /* Specializations for SRotationData: */
    /* ********************************************************************* */

    template< class R, arch_size_t RAlign >
    struct SRotationTraits< SRotationData< R, RAlign > >
    {
        typedef R real_t;
        static constexpr arch_size_t real_alignment = RAlign;
    };

    template< class R, arch_size_t RAlign >
    constexpr arch_size_t SRotationTraits<
        SRotationData< R,RAlign > >::real_alignment;

    /* ********************************************************************* */
    /* Create an equivalency between the ::NS(SRotation) type and the
     * corresponding specialization of the SRotationData template */
    /* ********************************************************************* */

    typedef SRotationData< typename SRotationTraits< ::NS(SRotation) >::real_t,
                        SRotationTraits< ::NS(SRotation) >::real_alignment >
            CSRotationEquivData;

    template<> struct ObjDataCApiTypeTraits< CSRotationEquivData >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                CSRotationEquivData, ::NS(SRotation) >(),
            "CSRotationEquivData and ::NS(SRotation) "
            "are not equivalent C-Api types" );

        typedef ::NS(SRotation) c_api_t;
    };
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_DATA_CXX_HPP__ */
