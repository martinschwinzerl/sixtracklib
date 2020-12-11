#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle_unit.h"
    #include "sixtracklib/common/particles/particle_unit.hpp"
    #include "sixtracklib/common/particles/particle_unit_api.h"
    #include "sixtracklib/common/particles/particle_unit_init.h"
    #include "sixtracklib/common/particles/particle_unit_derived_api.h"
    #include "sixtracklib/common/particles/particle_unit_compare.h"
    #include "sixtracklib/common/particles/particle_unit_convert.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr bool ObjDataParticleTraits< ::NS(Particle) >::is_type;

    constexpr particle_unit_impl_t ObjDataParticleTraits<
        ::NS(Particle) >::implementation;

    constexpr arch_size_t ParticleTraits< ::NS(Particle) >::real_alignment;
    constexpr arch_size_t ParticleTraits< ::NS(Particle) >::index_alignment;

    constexpr particle_num_elements_t ParticleTraits<
        ::NS(Particle) >::num_particles;
}
#endif /* defined( __cplusplus ) */
