#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class O,
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(),
        arch_size_t OAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< O >() >
    struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
    SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
    TMultipole
    {
        O order  SIXTRL_ALIGN( OAlign )
                 SIXTRL_ANNOTATE_ELEM_FIELD_REQU_INIT
                 SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R length SIXTRL_ALIGN( RAlign )
                 SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R hxl    SIXTRL_ALIGN( RAlign )
                 SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R hyl    SIXTRL_ALIGN( RAlign )
                 SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        be_address_t bal_addr SIXTRL_ALIGN( RAlign )
            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 )
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( bal )
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( "SIXTRL_BE_DATAPTR_DEC" )
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
            SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( capacity );

        O bal_capacity SIXTRL_ALIGN( OAlign )
            SIXTRL_ANNOTATE_ELEM_FIELD_CONST
            SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 2 );
    };

    /* ********************************************************************* */
    /* Specializations for TMultipole: */
    /* ********************************************************************* */

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign >
    struct ObjDataBeamElementsTraits< TMultipole< R, O, RAlign, OAlign > >
    {
        static constexpr bool is_beam_element = true;
    };

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign >
    constexpr bool ObjDataBeamElementsTraits< TMultipole<
        R, O, RAlign, OAlign > >::is_beam_element;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign >
    struct ObjDataMultipoleTraits< TMultipole< R, O, RAlign, OAlign > >
    {
        static constexpr bool is_type = true;
        static constexpr be_multipole_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_MULTIPOLE_IMPL_DEFAULT;
    };

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign >
    constexpr bool ObjDataMultipoleTraits<
        TMultipole< R, O, RAlign, OAlign > >::is_type;

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign >
    constexpr be_multipole_impl_t ObjDataMultipoleTraits<
        TMultipole< R, O, RAlign, OAlign > >::implementation;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign >
    struct MultipoleTraits< TMultipole< R, O, RAlign, OAlign > >
    {
        typedef typename TypeMethodParamTraits< R >::value_type real_t;
        typedef typename TypeMethodParamTraits< O >::value_type order_t;

        static constexpr arch_size_t real_alignment = RAlign;
        static constexpr arch_size_t order_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< order_t >();
    };

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign >
    constexpr arch_size_t MultipoleTraits<
        TMultipole< R, O, RAlign, OAlign > >::real_alignment;

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign >
    constexpr arch_size_t MultipoleTraits<
        TMultipole< R, O, RAlign, OAlign > >::order_alignment;

    /* ********************************************************************* *
     * Create an equivalency between the ::NS(Multipole) type and the        *
     * corresponding specialization of the TMultipole template               *
     * ********************************************************************* */

    typedef TMultipole<
        MultipoleTraits< ::NS(Multipole) >::real_t,
        MultipoleTraits< ::NS(Multipole) >::order_t,
        MultipoleTraits< ::NS(Multipole) >::real_alignment,
        MultipoleTraits< ::NS(Multipole) >::order_alignment > Multipole;

    template<> struct ObjDataCApiTypeTraits< Multipole >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
            Multipole, ::NS(Multipole) >(),
            "CMultipoleEquivData and ::NS(Multipole) "
            "are not equivalent C-Api types" );

        typedef ::NS(Multipole) c_api_t;
    };
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_CXX_HPP__ */
