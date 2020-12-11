#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/xy_shift/definitions.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift.hpp"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_api.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_derived_api.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_init.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_compare.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_convert.h"
    #include "sixtracklib/common/beam_elements/xy_shift/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr bool ObjDataBeamElementsTraits< ::NS(XYShift) >::is_beam_element;

    constexpr bool ObjDataXYShiftTraits< ::NS(XYShift) >::is_type;
    constexpr be_xy_shift_impl_t ObjDataXYShiftTraits<
        ::NS(XYShift) >::implementation;

    constexpr arch_size_t XYShiftTraits< ::NS(XYShift) >::real_alignment;
}
#endif /* defined( __cplusplus ) */
