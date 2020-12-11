#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift/drift_cobjects_api.h"
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/beam_elements/drift/drift_api.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    ::NS(cobj_type_id_t) NS(Drift_type_id_ext)( void ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Drift_type_id< ::NS(Drift) >();
    }

    bool NS(Particle_can_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC const ::NS(CBufferView) *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const ::NS(Drift) *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_objects,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_pointers ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::Drift_can_add_copy( cbuffer, ptr_orig,
            requ_buffer_size, requ_num_slots, requ_num_objects,
                requ_num_pointers );
    }

    SIXTRL_BE_ARGPTR_DEC ::NS(Drift)* NS(Particle_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const ::NS(Drift) *const ptr_orig )
    {
        return SIXTRL_CXX_NAMESPACE::Drift_add_copy( cbuffer, ptr_orig );
    }

    SIXTRL_BE_ARGPTR_DEC ::NS(Drift)* NS(Particle_new)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer )
    {
        return SIXTRL_CXX_NAMESPACE::Drift_new< ::NS(Drift) >( cbuffer );
    }
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
