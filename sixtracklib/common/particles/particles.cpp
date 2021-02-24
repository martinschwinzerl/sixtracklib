#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle.h"
    #include "sixtracklib/common/particles/particles.h"
    #include "sixtracklib/common/particles/particles_addr.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace { namespace st = SIXTRL_CXX_NAMESPACE; }

    constexpr bool st::CObjectsTrivialHandleSizeTraits<
        ::NS(SingleParticle) >::HAS_TRIVIAL_HANDLE_SIZE;

    constexpr st::cobj_obj_id_type st::CObjectsTraits<
        ::NS(SingleParticle) >::TYPE_ID;

    constexpr st::cobj_obj_id_type st::CObjectsTraits<
        ::NS(Particles) >::TYPE_ID;

    constexpr st::cobj_size_type st::CObjectsNumPointersTraits<
        ::NS(Particles) >::NUM_POINTERS;

    constexpr st::cobj_obj_id_type st::CObjectsTraits<
        ::NS(ParticlesAddr) >::TYPE_ID;

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
