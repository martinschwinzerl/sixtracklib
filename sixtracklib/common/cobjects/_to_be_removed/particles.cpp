#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particles.h"
    #include "sixtracklib/common/particles/particles.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::ParticlesTypeTraits< ::NS(Particles) >::real_type
                st_real_type;

        typedef st::ParticlesTypeTraits< ::NS(Particles) >::index_type
                st_index_type;
    }

    constexpr st::particle_impl_type st::ParticlesImplTraits<
        ::NS(Particles) >::IMPLEMENTATION;
}

/* ************************************************************************** */

#endif /* C++ */
