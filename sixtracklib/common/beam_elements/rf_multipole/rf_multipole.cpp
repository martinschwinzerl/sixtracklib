#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/rf_multipole/rf_multipole.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE {

    constexpr SIXTRL_CXX_NAMESPACE::cobj_obj_id_type
    SIXTRL_CXX_NAMESPACE::CObjectsTraits< ::NS(RFMultipole) >::TYPE_ID;

    constexpr SIXTRL_CXX_NAMESPACE::cobj_size_type
    SIXTRL_CXX_NAMESPACE::CObjectsNumPointersTraits<
        ::NS(RFMultipole) >::NUM_POINTERS;

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
