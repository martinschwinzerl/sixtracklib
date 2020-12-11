#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift_exact/drift_exact_cobjects_api.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    ::NS(cobj_type_id_t) NS(DriftExact_type_id_ext)( void ) SIXTRL_NOEXCEPT
    {
        return ObjDataTypeIdTraits<
            ::NS(DriftExact), cobj_type_id_t >::TypeId();
    }

    bool NS(Particle_can_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC const ::NS(CBufferView) *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const ::NS(DriftExact) *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_objects,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_pointers ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::DriftExact_can_add_copy( cbuffer, ptr_orig,
            requ_buffer_size, requ_num_slots, requ_num_objects,
                requ_num_pointers );
    }

    SIXTRL_BE_ARGPTR_DEC ::NS(DriftExact)* NS(Particle_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const ::NS(DriftExact) *const ptr_orig )
    {
        return SIXTRL_CXX_NAMESPACE::DriftExact_add_copy( cbuffer, ptr_orig );
    }

    SIXTRL_BE_ARGPTR_DEC ::NS(DriftExact)* NS(Particle_new)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer )
    {
        return SIXTRL_CXX_NAMESPACE::DriftExact_new< ::NS(DriftExact) >( cbuffer );
    }
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
