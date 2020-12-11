#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_cobjects_api.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_api.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    cobj_type_id_t BeamMonitor_type_id_ext() SIXTRL_NOEXCEPT
    {
        return ObjDataTypeIdTraits<
            ::NS(BeamMonitor), cobj_type_id_t >::TypeId();
    }

    bool BeamMonitor_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const ::NS(BeamMonitor) *const ptr_orig,
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

    SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor)* BeamMonitor_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const ::NS(BeamMonitor) *const ptr_orig )
    {
        return ( cbuffer != nullptr )
            ? SIXTRL_CXX_NAMESPACE::CBufferView_add_copy_of_object_detail(
                *cbuffer, ptr_orig, nullptr, nullptr, nullptr, nullptr, false )
            : nullptr;
    }

    SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor)* BeamMonitor_new(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer )
    {
        SIXTRL_BE_ARGPTR_DEC ::NS(BeamMonitor) temp;
        SIXTRL_CXX_NAMESPACE::BeamMonitor_init( &temp );

        return SIXTRL_CXX_NAMESPACE::BeamMonitor_add_copy( cbuffer, &temp );
    }
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
