#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole.hpp"
    #include "sixtracklib/common/beam_elements/multipole/multipole_api.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_derived_api.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_init.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_convert.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_compare.h"
    #include "sixtracklib/common/beam_elements/multipole/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr bool ObjDataBeamElementsTraits<
        ::NS(Multipole) >::is_beam_element;

    constexpr bool ObjDataMultipoleTraits< ::NS(Multipole) >::is_type;
    constexpr be_multipole_impl_t ObjDataMultipoleTraits<
        ::NS(Multipole) >::implementation;

    constexpr arch_size_t MultipoleTraits< ::NS(Multipole) >::real_alignment;
    constexpr arch_size_t MultipoleTraits< ::NS(Multipole) >::order_alignment;
}
#endif /* defined( __cplusplus ) */
