#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_unit_cobjects_api.h"
    #include "sixtracklib/common/particles/particle_unit.h"
    #include "sixtracklib/common/particles/particle_unit_api.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    ::NS(cobj_type_id_t) NS(Particle_type_id_ext)( void ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Particle_type_id< ::NS(Particle) >();
    }

    bool NS(Particle_can_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC const ::NS(CBufferView) *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(Particle) *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_objects,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_pointers ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Particle_can_add_copy( cbuffer, ptr_orig,
            requ_buffer_size, requ_num_slots, requ_num_objects,
                requ_num_pointers );
    }

    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle)* NS(Particle_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
        SIXTRL_PARTICLE_ARGPTR_DEC const ::NS(Particle) *const ptr_orig )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_add_copy( cbuffer, ptr_orig );
    }

    SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle)* NS(Particle_new)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer )
    {
        return SIXTRL_CXX_NAMESPACE::Particle_new< ::NS(Particle) >( cbuffer );
    }

}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
