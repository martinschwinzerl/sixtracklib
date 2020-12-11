#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/testlib/common/objs/type_fixed_num_ptrs.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef ::NS(TypeFixedNumPtrs)  _type_t;
        typedef st::cobj_size_t         _size_t;
    }

    constexpr _size_t CObjElemNumPointers< _type_t, void >::min_num_ptrs;
    constexpr _size_t CObjElemNumPointers< _type_t, void >::max_num_ptrs;

    constexpr _size_t CObjElemFieldOffsets< _type_t >::offsets[];
    constexpr _size_t CObjElemFieldSizes< _type_t >::sizes[];
}
#endif /* defined( __cplusplus ) */
