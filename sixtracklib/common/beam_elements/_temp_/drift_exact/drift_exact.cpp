#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift_exact/definitions.h"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact.h"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact.hpp"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact_api.h"
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact_convert.hpp"
    #include "sixtracklib/common/beam_elements/drift_exact/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr bool ObjDataBeamElementsTraits< ::NS(DriftExact) >::is_beam_element;
    constexpr bool ObjDataDriftExactTraits< ::NS(DriftExact) >::is_drift_exact;
    constexpr arch_size_t DriftExactTraits< ::NS(DriftExact) >::real_alignment;
}
#endif /* defined( __cplusplus ) */
