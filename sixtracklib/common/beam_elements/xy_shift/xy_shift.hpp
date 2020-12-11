#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/xy_shift/definitions.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, arch_size_t RAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
    SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
    SIXTRL_ANNOTATE_ELEM_OBJ_API_NAME( "XYShift" )
    TXYShift
    {
        R dx SIXTRL_ALIGN( RAlign )
             SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R dy SIXTRL_ALIGN( RAlign )
             SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
    };

    /* ********************************************************************* */
    /* Specializations for TXYShift: */
    /* ********************************************************************* */

    template< class R, arch_size_t RAlign >
    struct ObjDataBeamElementsTraits< TXYShift< R, RAlign > >
    {
        static constexpr bool is_beam_element = true;
    };

    template< class R, arch_size_t RAlign >
    constexpr bool ObjDataBeamElementsTraits<
        TXYShift< R, RAlign > >::is_beam_element;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, arch_size_t RAlign >
    struct ObjDataXYShiftTraits< TXYShift< R, RAlign > >
    {
        static constexpr bool is_type = true;
        static constexpr be_xy_shift_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_XY_SHIFT_IMPL_DEFAULT;
    };

    template< class R, arch_size_t RAlign >
    constexpr bool ObjDataXYShiftTraits< TXYShift< R, RAlign > >::is_type;

    template< class R, arch_size_t RAlign >
    constexpr be_xy_shift_impl_t ObjDataXYShiftTraits<
        TXYShift< R, RAlign > >::implementation;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, arch_size_t RAlign >
    struct XYShiftTraits< TXYShift< R, RAlign > >
    {
        typedef typename TypeMethodParamTraits< R >::value_type real_t;
        static constexpr arch_size_t real_alignment = RAlign;
    };

    template< class R, arch_size_t RAlign >
    constexpr arch_size_t XYShiftTraits< TXYShift< R,RAlign > >::real_alignment;

    /* ********************************************************************* */
    /* Create an equivalency between the ::NS(XYShift) type and the
     * corresponding specialization of the TXYShift template */
    /* ********************************************************************* */

    typedef TXYShift< XYShiftTraits< ::NS(XYShift) >::real_t,
                      XYShiftTraits< ::NS(XYShift) >::real_alignment > XYShift;

    template<> struct ObjDataCApiTypeTraits< XYShift >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                XYShift, ::NS(XYShift) >(),
            "XYShift and ::NS(XYShift) are not equivalent C-Api types" );

        typedef ::NS(XYShift) c_api_t;
    };
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_HPP__ */
