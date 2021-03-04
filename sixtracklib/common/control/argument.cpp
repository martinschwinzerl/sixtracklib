#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/argument.h"
    #include "sixtracklib/common/control/controller.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using arg_base_type  = st::ArgumentBase;
        using ctrl_base_type = st::ControllerBase;
        using st_status_t = arg_base_type::status_type;
    }

    constexpr ctrl_base_type::backend_id_type
    st::BackendObjTraits< arg_base_type >::BACKEND_ID;

    constexpr ctrl_base_type::class_id_type
    st::BackendObjTraits< arg_base_type >::BASE_CLASS_ID;

    constexpr ctrl_base_type::class_id_type
    st::BackendObjTraits< arg_base_type >::DERIVED_CLASS_ID;

    /* --------------------------------------------------------------------- */

    bool arg_base_type::can_push() const SIXTRL_NOEXCEPT {
        return ( ( this->m_is_ready ) &&
                 ( this->m_holds_id != st::ARGUMENT_HOLDS_NONE ) &&
                 ( this->m_maps_to_id != st::ARGUMENT_MAPS_TO_NONE ) );
    }

    st_status_t arg_base_type::do_push() {
        return st::STATUS_GENERAL_FAILURE;
    }

    bool arg_base_type::can_collect() const SIXTRL_NOEXCEPT {
        return ( ( this->m_is_ready ) &&
                 ( this->m_holds_id != st::ARGUMENT_HOLDS_NONE ) &&
                 ( this->m_maps_to_id != st::ARGUMENT_MAPS_TO_NONE ) );
    }

    st_status_t arg_base_type::do_collect() {
        return st::STATUS_GENERAL_FAILURE;
    }

    /* --------------------------------------------------------------------- */

    void arg_base_type::_set_ptr_ctrl(
        arg_base_type::ctrl_base_pointer SIXTRL_RESTRICT ptr_ctrl
    ) SIXTRL_NOEXCEPT { this->m_ptr_ctrl = ptr_ctrl; }

    void arg_base_type::_set_holds_id(
        arg_base_type::hold_id_type const holds_id ) SIXTRL_NOEXCEPT {
        this->m_holds_id = holds_id; }

    void arg_base_type::_set_maps_to_id(
        arg_base_type::mapsto_id_type const maps_to_id ) SIXTRL_NOEXCEPT {
        this->m_maps_to_id = maps_to_id; }

} /* end: SIXTRL_CXX_NAMESPACE */

#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
