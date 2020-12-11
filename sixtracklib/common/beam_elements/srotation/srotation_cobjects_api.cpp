#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation/srotation_cobjects_api.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    cobj_type_id_t SRotation_type_id_ext() SIXTRL_NOEXCEPT
    {
        return ObjDataTypeIdTraits< ::NS(SRotation), cobj_type_id_t >::TypeId();
    }

    bool SRotation_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const ::NS(SRotation) *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_objects,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_pointers
    ) SIXTRL_NOEXCEPT
    {
        return ( cbuffer != nullptr ) && ( cbuffer->can_add_copy_of_object(
            ptr_orig, requ_buffer_size, requ_num_slots, requ_num_objects,
                requ_num_pointers ) );
    }

    SIXTRL_BE_ARGPTR_DEC ::NS(SRotation)* SRotation_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const ::NS(SRotation) *const ptr_orig )
    {
        return ( cbuffer != nullptr )
            ? SIXTRL_CXX_NAMESPACE::CBufferView_add_copy_of_object_detail(
                *cbuffer, ptr_orig, nullptr, nullptr, nullptr, nullptr, false )
            : SIXTRL_NULLPTR;
    }

    SIXTRL_BE_ARGPTR_DEC ::NS(SRotation)* SRotation_new(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer )
    {
        SIXTRL_BE_ARGPTR_DEC ::NS(SRotation) temp;
        SIXTRL_CXX_NAMESPACE::SRotation_init( &temp );

        return SIXTRL_CXX_NAMESPACE::SRotation_add_copy( cbuffer, &temp );
    }
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
