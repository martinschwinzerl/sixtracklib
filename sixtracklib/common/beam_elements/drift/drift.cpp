#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/definitions.h"
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/beam_elements/drift/drift.hpp"
    #include "sixtracklib/common/beam_elements/drift/drift_api.h"
    #include "sixtracklib/common/beam_elements/drift/drift_derived_api.h"
    #include "sixtracklib/common/beam_elements/drift/drift_init.h"
    #include "sixtracklib/common/beam_elements/drift/drift_convert.h"
    #include "sixtracklib/common/beam_elements/drift/drift_compare.h"
    #include "sixtracklib/common/beam_elements/drift/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr bool ObjDataBeamElementsTraits< ::NS(Drift) >::is_beam_element;

    constexpr bool ObjDataDriftTraits< ::NS(Drift) >::is_type;
    constexpr be_drift_impl_t ObjDataDriftTraits< ::NS(Drift) >::implementation;

    constexpr arch_size_t DriftTraits< ::NS(Drift) >::real_alignment;
}
#endif /* defined( __cplusplus ) */
