#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/particles/particle_api.h"
    #include "sixtracklib/common/particles/particle_derived_api.h"
    #include "sixtracklib/common/particles/particle_data.hpp"
    #include "sixtracklib/common/particles/particle_convert.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr bool ObjDataParticleTraits< ::NS(Particle) >::is_particle;
    constexpr arch_size_t ParticleTraits< ::NS(Particle) >::real_alignment;
    constexpr arch_size_t ParticleTraits< ::NS(Particle) >::index_alignment;

    constexpr particle_num_elements_t ParticleTraits<
        ::NS(Particle) >::num_particles;
}
#endif /* defined( __cplusplus ) */
