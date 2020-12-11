#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/definitions.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs.hpp"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_api.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_derived_api.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_init.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_convert.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_compare.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    constexpr bool ObjDataTypeConstNumPtrsTraits<
        ::NS(TypeConstNumPtrs) >::is_type;

    constexpr objs_type_const_num_ptrs_impl_t ObjDataTypeConstNumPtrsTraits<
        ::NS(TypeConstNumPtrs) >::implementation;

    constexpr SIXTRL_CXX_NAMESPACE::arch_size_t TypeConstNumPtrsTraits<
        ::NS(TypeConstNumPtrs) >::real_alignment;

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* defined( __cplusplus ) */
