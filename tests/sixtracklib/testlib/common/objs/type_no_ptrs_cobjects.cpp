#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_cobjects.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_api.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{

namespace tests
{
    ::NS(cobj_type_id_t) NS(TypeNoPtrs_type_id_ext)( void ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_type_id<
            ::NS(TypeNoPtrs) >();
    }

    bool NS(TypeNoPtrs_can_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC const ::NS(CBufferView) *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BUFFER_ARGPTR_DEC const ::NS(TypeNoPtrs) *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_objects,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_pointers ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_can_add_copy(
            cbuffer, ptr_orig, requ_buffer_size, requ_num_slots,
                requ_num_objects, requ_num_pointers );
    }

    SIXTRL_BUFFER_DATAPTR_DEC ::NS(TypeNoPtrs)* NS(TypeNoPtrs_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BUFFER_ARGPTR_DEC const ::NS(TypeNoPtrs) *const ptr_orig )
    {
        return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_add_copy(
            cbuffer, ptr_orig );
    }

    SIXTRL_BUFFER_DATAPTR_DEC ::NS(TypeNoPtrs)* NS(TypeNoPtrs_new)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer )
    {
        return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_new<
            ::NS(TypeNoPtrs) >( cbuffer );
    }

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
