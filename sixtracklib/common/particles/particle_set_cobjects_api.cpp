    #if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_set_cobjects_api.h"
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/particles/particle_set_api.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef ::NS(ParticleSet) pset_t;
    }

    constexpr cobj_size_t CObjElemNumPointers< pset_t, void >::min_num_ptrs;
    constexpr cobj_size_t CObjElemNumPointers< pset_t, void >::max_num_ptrs;
    constexpr cobj_size_t CObjElemFieldOffsets< pset_t >::offsets[];
    constexpr cobj_size_t CObjElemFieldSizes< pset_t >::sizes[];


    /* ********************************************************************** */

    ::NS(cobj_type_id_t) NS(ParticleSet_type_id_ext)( void ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ParticleSet_type_id< ::NS(ParticleSet) >();
    }

    bool NS(ParticleSet_can_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC const ::NS(CBufferView) *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(ParticleSet) *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_objects,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_pointers ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ParticleSet_can_add_copy( cbuffer,
            ptr_orig, requ_buffer_size, requ_num_slots, requ_num_objects,
                requ_num_pointers );
    }

    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(ParticleSet)* NS(ParticleSet_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
        SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(ParticleSet) *const ptr_orig )
    {
        return SIXTRL_CXX_NAMESPACE::ParticleSet_add_copy( cbuffer, ptr_orig );
    }

    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(ParticleSet)* NS(ParticleSet_new)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
        ::NS(particle_num_elements_t) const num_particles )
    {
        return SIXTRL_CXX_NAMESPACE::ParticleSet_new<
            ::NS(ParticleSet) >( cbuffer, num_particles );
    }

}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
