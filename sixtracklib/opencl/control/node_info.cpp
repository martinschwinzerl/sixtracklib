#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/control/node_info.h"
#endif /* !defined( SIXTRL_NO_INCLUDES )  */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using ninfo_type = st::OclNodeInfo;
    }

    constexpr ninfo_type::class_id_type ninfo_type::CLASS_ID;

    constexpr ninfo_type::backend_id_type
    st::BackendObjTraits< ninfo_type >::BACKEND_ID;

    constexpr ninfo_type::class_id_type
    st::BackendObjTraits< ninfo_type >::BASE_CLASS_ID;

    constexpr ninfo_type::class_id_type
    st::BackendObjTraits< ninfo_type >::DERIVED_CLASS_ID;

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
