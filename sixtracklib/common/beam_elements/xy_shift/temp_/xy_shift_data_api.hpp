#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_DATA_API_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_DATA_API_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_data.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* ********************************************************************* */
    /** SixTrackLib: Add autogenerated C++ API */
    /* ********************************************************************* */

    /* init API: */

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_preset( SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN void XYShift_init( SIXTRL_BE_ARGPTR_DEC
        XYShiftData< R, RAlign >* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign, typename DXArg, typename DYArg >
    SIXTRL_STATIC SIXTRL_FN void XYShift_init_detailed(
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >* SIXTRL_RESTRICT elem,
        DXArg dx, DYArg dy );

    template< class R, arch_size_t RAlign, typename DXArg, typename DYArg >
    SIXTRL_STATIC SIXTRL_FN void XYShift_init(
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >* SIXTRL_RESTRICT elem,
        DXArg dx, DYArg dy );

    /* getter API, ptr argument: */

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN typename TypeMethodParamTraits< typename
        XYShiftTraits< XYShiftData< R, RAlign > >::real_t >::const_existing_type
    XYShift_dx( SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const
        SIXTRL_RESTRICT xy_shift ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN typename TypeMethodParamTraits< typename
        XYShiftTraits< XYShiftData< R, RAlign > >::real_t >::const_existing_type
    XYShift_dy( SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const
        SIXTRL_RESTRICT xy_shift ) SIXTRL_NOEXCEPT;

    /* setter API, ptr argument: */

    template< class R, arch_size_t RAlign, typename DXArg >
    SIXTRL_STATIC SIXTRL_FN void XYShift_set_dx(
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >* SIXTRL_RESTRICT elem,
        DXArg dx );

    template< class R, arch_size_t RAlign, typename DYArg >
    SIXTRL_STATIC SIXTRL_FN void XYShift_set_dy(
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >* SIXTRL_RESTRICT elem,
        DYArg dy );

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    /* getter API, ref argument: */

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN typename TypeMethodParamTraits< typename
        XYShiftTraits< XYShiftData< R, RAlign > >::real_t >::const_existing_type
    XYShift_dx( SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > const&
        SIXTRL_RESTRICT_REF xy_shift ) SIXTRL_NOEXCEPT;

    template< class R, arch_size_t RAlign >
    SIXTRL_STATIC SIXTRL_FN typename TypeMethodParamTraits< typename
        XYShiftTraits< XYShiftData< R, RAlign > >::real_t >::const_existing_type
    XYShift_dy( SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > const&
        SIXTRL_RESTRICT_REF xy_shift ) SIXTRL_NOEXCEPT;

    /* setter API, ref argument: */

    template< class R, arch_size_t RAlign, typename DXArg >
    SIXTRL_STATIC SIXTRL_FN void XYShift_set_dx(
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >& SIXTRL_RESTRICT_REF elem,
        DXArg dx );

    template< class R, arch_size_t RAlign, typename DXArg >
    SIXTRL_STATIC SIXTRL_FN void XYShift_set_dy(
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >& SIXTRL_RESTRICT_REF elem,
        DYArg dy );
}

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
    XYShift_preset( SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >*
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        if( elem != SIXTRL_NULLPTR )
        {
            typedef typename XYShiftTraits< XYShiftData< R, RAlign > >::real_t
                    real_t;

            SIXTRL_CXX_NAMESPACE::XYShift_set_dx( elem, real_t{ 0 } );
            SIXTRL_CXX_NAMESPACE::XYShift_set_dy( elem, real_t{ 0 } );
        }

        return elem;
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE void XYShift_init( SIXTRL_BE_ARGPTR_DEC XYShiftData<
        R, RAlign >* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        SIXTRL_CXX_NAMESPACE::XYShift_preset( elem );
    }

    template< class R, arch_size_t RAlign, typename DXArg dx, typename DYArg >
    SIXTRL_INLINE void XYShift_init_detailed(
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >* SIXTRL_RESTRICT elem,
        DXArg dx, DYArg dy )
    {
        SIXTRL_CXX_NAMESPACE::XYShift_set_dx( elem, dx );
        SIXTRL_CXX_NAMESPACE::XYShift_set_dy( elem, dy );
    }

    template< class R, arch_size_t RAlign, typename DXArg dx, typename DYArg >
    SIXTRL_INLINE void XYShift_init(
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >* SIXTRL_RESTRICT elem,
        DXArg dx, DYArg dy )
    {
        SIXTRL_CXX_NAMESPACE::XYShift_init_detailed( elem, dx, dy );
    }

    /* getter API, ptr argument: */

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE typename TypeMethodParamTraits< typename
        XYShiftTraits< XYShiftData< R, RAlign > >::real_t >::const_existing_type
    XYShift_dx( SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return elem->dx;
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE typename TypeMethodParamTraits< typename
        XYShiftTraits< XYShiftData< R, RAlign > >::real_t >::const_existing_type
    XYShift_dy( SIXTRL_BE_ARGPTR_DEC const XYShiftData< R, RAlign > *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        return elem->dy;
    }

    /* setter API, ptr argument: */

    template< class R, arch_size_t RAlign, typename DXArg >
    SIXTRL_INLINE void XYShift_set_dx(
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >* SIXTRL_RESTRICT elem,
        DXArg dx )
    {
        typedef typename XYShiftTraits< XYShiftData< R, RAlign > >::real_t dest_t;
        typedef typename std::decay< DXArg >::type src_t;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        SIXTRL_CXX_NAMESPACE::Types_perform_assignment<
            src_t, dest_t >( elem->dx, dx );
    }

    template< class R, arch_size_t RAlign, typename DYArg >
    SIXTRL_INLINE void XYShift_set_dy(
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >* SIXTRL_RESTRICT elem,
        DYArg dy )
    {
        typedef typename XYShiftTraits< XYShiftData< R, RAlign > >::real_t dest_t;
        typedef typename std::decay< DYArg >::type src_t;

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        SIXTRL_CXX_NAMESPACE::Types_perform_assignment<
            src_t, dest_t >( elem->dy, dy );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    /* getter API, ref argument: */

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE typename TypeMethodParamTraits< typename
        XYShiftTraits< XYShiftData< R, RAlign > >::real_t >::const_existing_type
    XYShift_dx( SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > const&
        SIXTRL_RESTRICT_REF elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::XYShift_dx( &elem );
    }

    template< class R, arch_size_t RAlign >
    SIXTRL_INLINE typename TypeMethodParamTraits< typename
        XYShiftTraits< XYShiftData< R, RAlign > >::real_t >::const_existing_type
    XYShift_dy( SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign > const&
        SIXTRL_RESTRICT_REF elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::XYShift_dy( &elem );
    }

    /* setter API, ref argument: */

    template< class R, arch_size_t RAlign, typename DXArg >
    SIXTRL_INLINE void XYShift_set_length(
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >& SIXTRL_RESTRICT_REF elem,
        DXArg dx )
    {
        SIXTRL_CXX_NAMESPACE::XYShift_set_dx( &elem, dx );
    }

    template< class R, arch_size_t RAlign, typename DYArg >
    SIXTRL_INLINE void XYShift_set_length(
        SIXTRL_BE_ARGPTR_DEC XYShiftData< R, RAlign >& SIXTRL_RESTRICT_REF elem,
        DYArg dy )
    {
        SIXTRL_CXX_NAMESPACE::XYShift_set_dy( &elem, dy );
    }
}

#endif /* !defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_DATA_API_CXX_HPP__ */