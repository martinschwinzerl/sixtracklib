#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/limit/limit_rect.h"
    #include "sixtracklib/common/beam_elements/limit/limit_ellipse.h"
    #include "sixtracklib/common/beam_elements/limit/limit_rect_ellipse.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    constexpr SIXTRL_CXX_NAMESPACE::cobj_obj_id_type
    SIXTRL_CXX_NAMESPACE::CObjectsTraits< ::NS(LimitRect) >::TYPE_ID;

    constexpr SIXTRL_CXX_NAMESPACE::cobj_obj_id_type
    SIXTRL_CXX_NAMESPACE::CObjectsTraits< ::NS(LimitEllipse) >::TYPE_ID;

    constexpr SIXTRL_CXX_NAMESPACE::cobj_obj_id_type
    SIXTRL_CXX_NAMESPACE::CObjectsTraits< ::NS(LimitRectEllipse) >::TYPE_ID;

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
