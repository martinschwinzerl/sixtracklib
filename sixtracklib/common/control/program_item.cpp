#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/program_item.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using item_type = st::ProgramItemBase;
    }

    constexpr item_type::backend_id_type
    st::BackendObjTraits< item_type >::BACKEND_ID;

    constexpr item_type::class_id_type
    st::BackendObjTraits< item_type >::BASE_CLASS_ID;

    constexpr item_type::class_id_type
    st::BackendObjTraits< item_type >::DERIVED_CLASS_ID;

} /* end: namespace SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
