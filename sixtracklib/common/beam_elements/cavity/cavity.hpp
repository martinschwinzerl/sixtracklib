#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/cavity.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
    SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
    SIXTRL_ANNOTATE_ELEM_OBJ_API_NAME( "Cavity" )
    TCavity
    {
        R voltage   SIXTRL_ALIGN( RAlign )
                    SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R frequency SIXTRL_ALIGN( RAlign )
                    SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R lag       SIXTRL_ALIGN( RAlign )
                    SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
    };

    /* ********************************************************************* */
    /* Specializations for TCavity: */
    /* ********************************************************************* */

    template< class R, arch_size_t RAlign >
    struct ObjDataBeamElementsTraits< TCavity< R, RAlign > >
    {
        static constexpr bool is_beam_element = true;
    };

    template< class R, arch_size_t RAlign >
    constexpr bool ObjDataBeamElementsTraits<
        TCavity< R, RAlign > >::is_beam_element;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, arch_size_t RAlign >
    struct ObjDataCavityTraits< TCavity< R, RAlign > >
    {
        static constexpr bool is_type = true;
        static constexpr be_cavity_impl_t implementation =
                    SIXTRL_CXX_NAMESPACE::BE_CAVITY_IMPL_DEFAULT;
    };

    template< class R, arch_size_t RAlign >
    constexpr bool ObjDataCavityTraits< TCavity< R, RAlign > >::is_type;

    template< class R, arch_size_t RAlign >
    constexpr be_cavity_impl_t ObjDataCavityTraits<
        TCavity< R, RAlign > >::implementation;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, arch_size_t RAlign >
    struct CavityTraits< TCavity< R, RAlign > >
    {
        typedef typename TypeMethodParamTraits< R >::value_type real_t;
        static constexpr arch_size_t real_alignment = RAlign;
    };

    template< class R, arch_size_t RAlign >
    constexpr arch_size_t CavityTraits< TCavity< R,RAlign > >::real_alignment;

    /* ********************************************************************* */
    /* Create an equivalency between the ::NS(Cavity) type and the
     * corresponding specialization of the TCavity template */
    /* ********************************************************************* */

    typedef TCavity< CavityTraits< ::NS(Cavity) >::real_t,
                     CavityTraits< ::NS(Cavity) >::real_alignment > Cavity;

    template<> struct ObjDataCApiTypeTraits< Cavity >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                Cavity, ::NS(Cavity) >(),
            "Cavity and ::NS(Cavity) are not equivalent C-Api types" );

        typedef ::NS(Cavity) c_api_t;
    };
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_CXX_HPP__ */
