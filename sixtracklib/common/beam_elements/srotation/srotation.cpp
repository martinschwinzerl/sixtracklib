#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/definitions.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation.hpp"
    #include "sixtracklib/common/beam_elements/srotation/srotation_api.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation_derived_api.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation_init.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation_convert.h"
    #include "sixtracklib/common/beam_elements/srotation/srotation_compare.h"
    #include "sixtracklib/common/beam_elements/srotation/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr bool ObjDataBeamElementsTraits< ::NS(SRotation) >::is_beam_element;

    constexpr bool ObjDataSRotationTraits< ::NS(SRotation) >::is_type;
    constexpr be_srotation_impl_t ObjDataSRotationTraits<
        ::NS(SRotation) >::implementation;

    constexpr arch_size_t SRotationTraits< ::NS(SRotation) >::real_alignment;
}
#endif /* defined( __cplusplus ) */
