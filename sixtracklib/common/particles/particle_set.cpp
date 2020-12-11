#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/particles/particle_set.hpp"
    #include "sixtracklib/common/particles/particle_set_vector.hpp"
    #include "sixtracklib/common/particles/particle_set_api.h"
    #include "sixtracklib/common/particles/particle_set_init.h"
    #include "sixtracklib/common/particles/particle_set_particle_api.h"
    #include "sixtracklib/common/particles/particle_set_convert.h"
    #include "sixtracklib/common/particles/particle_set_compare.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr bool ObjDataParticleSetTraits< ::NS(ParticleSet) >::is_type;
    constexpr particle_set_impl_t ObjDataParticleSetTraits<
        ::NS(ParticleSet) >::implementation;

    /* --------------------------------------------------------------------- */

    constexpr arch_size_t ParticleSetTraits<
        ::NS(ParticleSet) >::real_alignment;

    constexpr arch_size_t ParticleSetTraits<
        ::NS(ParticleSet) >::index_alignment;

    constexpr arch_size_t ParticleSetTraits<
        ::NS(ParticleSet) >::addr_alignment;
}
#endif /* defined( __cplusplus ) */
