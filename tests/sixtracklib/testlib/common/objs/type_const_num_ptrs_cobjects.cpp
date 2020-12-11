#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_cobjects.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_api.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr cobj_size_t CObjElemNumPointers<
        ::NS(TypeConstNumPtrs) >::min_num_ptrs;

    constexpr cobj_size_t CObjElemNumPointers<
        ::NS(TypeConstNumPtrs) >::max_num_ptrs;

    constexpr cobj_size_t CObjElemFieldOffsets<
        ::NS(TypeConstNumPtrs) >::offsets[];

    constexpr cobj_size_t CObjElemFieldSizes< ::NS(TypeConstNumPtrs) >::sizes[];


namespace tests
{
    ::NS(cobj_type_id_t) NS(TypeConstNumPtrs_type_id_ext)( void ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_type_id<
            ::NS(TypeConstNumPtrs) >();
    }

    bool NS(TypeConstNumPtrs_can_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC const ::NS(CBufferView) *const
            SIXTRL_RESTRICT cbuffer,
        SIXTRL_BUFFER_ARGPTR_DEC const ::NS(TypeConstNumPtrs) *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_objects,
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(cobj_size_t)*
            SIXTRL_RESTRICT requ_num_pointers ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_can_add_copy(
            cbuffer, ptr_orig, requ_buffer_size, requ_num_slots,
                requ_num_objects, requ_num_pointers );
    }

    SIXTRL_BUFFER_DATAPTR_DEC ::NS(TypeConstNumPtrs)* NS(TypeConstNumPtrs_add_copy)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BUFFER_ARGPTR_DEC const ::NS(TypeConstNumPtrs) *const ptr_orig )
    {
        return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_add_copy(
            cbuffer, ptr_orig );
    }

    SIXTRL_BUFFER_DATAPTR_DEC ::NS(TypeConstNumPtrs)* NS(TypeConstNumPtrs_new)(
        SIXTRL_BUFFER_ARGPTR_DEC ::NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_b_values,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_c_values )
    {
        return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_new<
            ::NS(TypeConstNumPtrs) >( cbuffer, num_b_values, num_c_values );
    }

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
