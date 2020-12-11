#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_DEFINITIONS_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef enum { BE_XY_SHIFT_IMPL_DEFAULT = 0 } be_xy_shift_impl_t;

    template< class XYShiftT >
    struct ObjDataXYShiftTraits
    {
        static constexpr bool is_type = false;
        static constexpr be_xy_shift_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_XY_SHIFT_IMPL_DEFAULT;
    };

    template< class XYShiftT >
    constexpr bool ObjDataXYShiftTraits< XYShiftT >::is_type;

    template< class XYShiftT >
    constexpr be_xy_shift_impl_t ObjDataXYShiftTraits<
        XYShiftT >::implementation;

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool XYShift_is_type(
        SIXTRL_BE_ARGPTR_DEC const XYShiftT *const SIXTRL_RESTRICT /* elem */
            = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataXYShiftTraits< XYShiftT >::is_type;
    }

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool XYShift_impl_default(
        SIXTRL_BE_ARGPTR_DEC const XYShiftT *const SIXTRL_RESTRICT /* elem */
            = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataXYShiftTraits< XYShiftT >::implementation ==
            SIXTRL_CXX_NAMESPACE::BE_XY_SHIFT_IMPL_DEFAULT;
    }

    /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class XYShiftT >
    struct XYShiftTraits
    {
        typedef ::NS(be_real_t) real_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();
    };

    template< class XYShiftT >
    constexpr arch_size_t XYShiftTraits< XYShiftT >::real_alignment;
}
#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_DEFINITIONS_H__ */
