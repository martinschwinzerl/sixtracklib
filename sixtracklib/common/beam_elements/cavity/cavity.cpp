#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity/definitions.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity.hpp"
    #include "sixtracklib/common/beam_elements/cavity/cavity_api.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_derived_api.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_init.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_compare.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_convert.h"
    #include "sixtracklib/common/beam_elements/cavity/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr bool ObjDataBeamElementsTraits< ::NS(Cavity) >::is_beam_element;

    constexpr bool ObjDataCavityTraits< ::NS(Cavity) >::is_type;
    constexpr be_cavity_impl_t ObjDataCavityTraits<
        ::NS(Cavity) >::implementation;

    constexpr arch_size_t CavityTraits< ::NS(Cavity) >::real_alignment;
}
#endif /* defined( __cplusplus ) */
