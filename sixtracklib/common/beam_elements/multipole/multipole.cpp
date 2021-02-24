#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE {
    namespace { namespace st = SIXTRL_CXX_NAMESPACE; }

    constexpr st::cobj_obj_id_type st::CObjectsTraits<
        ::NS(Multipole) >::TYPE_ID;

    constexpr st::cobj_size_type st::CObjectsNumPointersTraits<
        ::NS(Multipole) >::NUM_POINTERS;

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
