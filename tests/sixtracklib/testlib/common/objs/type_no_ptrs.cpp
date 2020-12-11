#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/definitions.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs.hpp"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_api.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_derived_api.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_init.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_convert.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_compare.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    constexpr bool ObjDataNoPtrTypeTraits<
        ::NS(TypeNoPtrs) >::is_type;

    constexpr objs_type_no_ptrs_impl_t ObjDataNoPtrTypeTraits<
        ::NS(TypeNoPtrs) >::implementation;


    constexpr SIXTRL_CXX_NAMESPACE::arch_size_t TypeNoPtrsTraits<
        ::NS(TypeNoPtrs) >::real_alignment;

    constexpr SIXTRL_CXX_NAMESPACE::arch_size_t TypeNoPtrsTraits<
        ::NS(TypeNoPtrs) >::int_alignment;

    constexpr SIXTRL_CXX_NAMESPACE::arch_size_t TypeNoPtrsTraits<
        ::NS(TypeNoPtrs) >::uchar_alignment;

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* defined( __cplusplus ) */
