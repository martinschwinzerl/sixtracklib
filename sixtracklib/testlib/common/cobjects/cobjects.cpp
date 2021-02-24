#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/cobjects/cobj_no_ptrs.h"
    #include "sixtracklib/testlib/common/cobjects/cobj_dataptrs.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr SIXTRL_CXX_NAMESPACE::cobj_obj_id_type
    SIXTRL_CXX_NAMESPACE::CObjectsTraits< ::NS(CObjTestNoPtrs) >::TYPE_ID;

    constexpr SIXTRL_CXX_NAMESPACE::cobj_obj_id_type
    SIXTRL_CXX_NAMESPACE::CObjectsTraits< ::NS(CObjTestDataptrs) >::TYPE_ID;

    constexpr SIXTRL_CXX_NAMESPACE::cobj_size_type
    SIXTRL_CXX_NAMESPACE::CObjectsNumPointersTraits<
        ::NS(CObjTestDataptrs) >::NUM_POINTERS;

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
