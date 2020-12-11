#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_DEFINITIONS_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


typedef SIXTRL_INT64_T                  NS(be_monitor_flag_t);
typedef NS(belem_address_t)             NS(be_monitor_addr_t);

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(be_monitor_flag_t)     be_monitor_flag_t;
    typedef ::NS(be_monitor_addr_t)     be_monitor_addr_t;

    template< class BeamMonitorDataObj >
    struct BeamMonitorTraits
    {
        typedef ::NS(ParticleSet)  particle_set_t;
        typedef ParticleSetTraits< particle_set_t >::real_t  real_t;
        typedef ParticleSetTraits< particle_set_t >::index_t index_t;
//         typedef ParticleSetTraits< particle_set_t >::

        static constexpr arch_size_t particle_set_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< particle_set_t >();

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

        static constexpr arch_size_t index_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< index_t >();
    };

    template< class BeamMonitorDataObj >
    constexpr arch_size_t BeamMonitorTraits< BeamMonitorDataObj
        >::particle_set_alignment;

    template< class BeamMonitorDataObj >
    constexpr arch_size_t BeamMonitorTraits< BeamMonitorDataObj
        >::real_alignment;

    template< class BeamMonitorDataObj >
    constexpr arch_size_t BeamMonitorTraits< BeamMonitorDataObj
        >::index_alignment;
}
#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_DEFINITIONS_H__ */
