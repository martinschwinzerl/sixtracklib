#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_api.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_cobjects_api.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_data.hpp"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_data_cobjects_api.hpp"
    #include "sixtracklib/common/beam_elements/beam_monitor/convert_cobjects.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr arch_size_t BeamMonitorTraits<
        ::NS(BeamMonitor) >::particle_set_alignment;

    constexpr arch_size_t BeamMonitorTraits<
        ::NS(BeamMonitor) >::particle_real_alignment;

    constexpr arch_size_t BeamMonitorTraits<
        ::NS(BeamMonitor) >::particle_index_alignment;
}
#endif /* defined( __cplusplus ) */
