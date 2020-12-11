#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
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
    TSRotation
    {
        R cos_z SIXTRL_ALIGN( RAlign )
                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 1 );

        R sin_z SIXTRL_ALIGN( RAlign )
                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
    };

    /* ********************************************************************* */
    /* Specializations for TSRotation: */
    /* ********************************************************************* */

    template< class R, arch_size_t RAlign >
    struct ObjDataBeamElementsTraits< TSRotation< R, RAlign > >
    {
        static constexpr bool is_beam_element = true;
    };

    template< class R, arch_size_t RAlign >
    constexpr bool ObjDataBeamElementsTraits<
        TSRotation< R, RAlign > >::is_beam_element;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, arch_size_t RAlign >
    struct ObjDataSRotationTraits< TSRotation< R, RAlign > >
    {
        static constexpr bool is_type = true;
        static constexpr be_srotation_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_SROTATION_IMPL_DEFAULT;
    };

    template< class R, arch_size_t RAlign >
    constexpr bool ObjDataSRotationTraits< TSRotation< R, RAlign > >::is_type;

    template< class R, arch_size_t RAlign >
    constexpr be_srotation_impl_t ObjDataSRotationTraits<
        TSRotation< R, RAlign > >::implementation;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, arch_size_t RAlign >
    struct SRotationTraits< TSRotation< R, RAlign > >
    {
        typedef typename TypeMethodParamTraits< R >::value_type real_t;
        static constexpr arch_size_t real_alignment = RAlign;
    };

    template< class R, arch_size_t RAlign >
    constexpr arch_size_t SRotationTraits<
        TSRotation< R,RAlign > >::real_alignment;

    /* ********************************************************************* */
    /* Create an equivalency between the ::NS(SRotation) type and the
     * corresponding specialization of the TSRotation template */
    /* ********************************************************************* */

    typedef TSRotation< SRotationTraits< ::NS(SRotation) >::real_t,
                        SRotationTraits< ::NS(SRotation) >::real_alignment >
            SRotation;

    template<> struct ObjDataCApiTypeTraits< SRotation >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                SRotation, ::NS(SRotation) >(),
            "SRotation and ::NS(SRotation) are not equivalent C-Api types" );

        typedef ::NS(SRotation) c_api_t;
    };
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_SROTATION_SROTATION_CXX_HPP__ */
