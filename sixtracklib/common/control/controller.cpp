#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/controller.h"
    #include "sixtracklib/common/control/argument.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using ctrl_base_type = st::ControllerBase;
        using arg_base_type  = st::ArgumentBase;
        using st_status_t = st::ControllerBase::status_type;
    }

    constexpr ctrl_base_type::backend_id_type
    st::BackendObjTraits< ctrl_base_type >::BACKEND_ID;

    constexpr ctrl_base_type::class_id_type
    st::BackendObjTraits< ctrl_base_type >::BASE_CLASS_ID;

    constexpr ctrl_base_type::class_id_type
    st::BackendObjTraits< ctrl_base_type >::DERIVED_CLASS_ID;

    /* --------------------------------------------------------------------- */

    st_status_t ctrl_base_type::do_remap_argument(
        ctrl_base_type::arg_base_type& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( arg ) )
    {
        return st::STATUS_GENERAL_FAILURE;
    }

} /* end: SIXTRL_CXX_NAMESPACE */

#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
