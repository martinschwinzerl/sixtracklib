#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/cobjects/type_fixed_num_ptrs.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typename ::NS(TypeFixedNumPtrs) _type_t;
        typename st::cobj_size_t _size_t;
    }

    constexpr _size_t st::CObjElemNumDataptrs< _type_t >::min_num_dataptrs;
    constexpr _size_t st::CObjElemNumDataptrs< _type_t >::max_num_dataptrs;
    constexpr _size_t st::CObjElemFieldOffsets< _type_t >::offsets[];
    constexpr _size_t st::CObjElemFieldSizes< _type_t >::sizes[];
}
#endif /* defined( __cplusplus ) */
