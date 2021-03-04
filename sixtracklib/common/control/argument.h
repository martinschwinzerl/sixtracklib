#ifndef SIXTRACKLIB_COMON_TRACK_ARGUMENT_H__
#define SIXTRACKLIB_COMON_TRACK_ARGUMENT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/backends/backend_obj_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class ControllerBase;

    class ArgumentBase : public SIXTRL_CXX_NAMESPACE::BackendObjBase
    {
        public:

        using address_type      = SIXTRL_CXX_NAMESPACE::address_type;
        using hold_id_type      = SIXTRL_CXX_NAMESPACE::ctrl_arg_hold_id_type;
        using mapsto_id_type    = SIXTRL_CXX_NAMESPACE::ctrl_arg_mapsto_id_type;
        using cbuffer_type      = SIXTRL_CXX_NAMESPACE::CBufferView;

        using ctrl_base_type    = SIXTRL_CXX_NAMESPACE::ControllerBase;
        using ctrl_base_pointer = ctrl_base_type*;
        using ctrl_base_const_pointer = ctrl_base_type const*;

        static constexpr class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::ARGUMENT_BASE_CLASS_ID;

        SIXTRL_HOST_FN virtual ~ArgumentBase() = default;

        /* ------------------------------------------------------------------ */

        SIXTRL_HOST_FN hold_id_type hold_id() const SIXTRL_NOEXCEPT {
            return this->m_holds_id; }

        SIXTRL_HOST_FN bool holds_value() const SIXTRL_NOEXCEPT {
            return ( this->m_holds_id ==
                SIXTRL_CXX_NAMESPACE::ARGUMENT_HOLDS_VALUE ); }

        SIXTRL_HOST_FN bool holds_weak_pointer() const SIXTRL_NOEXCEPT {
            return ( this->m_holds_id ==
                SIXTRL_CXX_NAMESPACE::ARGUMENT_HOLDS_WEAK_POINTER ); }

        SIXTRL_HOST_FN bool holds_pointer() const SIXTRL_NOEXCEPT {
            return ( this->m_holds_id ==
                SIXTRL_CXX_NAMESPACE::ARGUMENT_HOLDS_POINTER ); }

        SIXTRL_HOST_FN bool holds_cbuffer() const SIXTRL_NOEXCEPT {
            return ( this->m_holds_id ==
                SIXTRL_CXX_NAMESPACE::ARGUMENT_HOLDS_CBUFFER ); }

        SIXTRL_HOST_FN bool holds_anything() const SIXTRL_NOEXCEPT {
            return ( this->m_holds_id !=
                SIXTRL_CXX_NAMESPACE::ARGUMENT_HOLDS_NONE ); }

        /* ------------------------------------------------------------------ */

        SIXTRL_HOST_FN mapsto_id_type maps_to_id() const SIXTRL_NOEXCEPT {
            return this->m_maps_to_id; }

        SIXTRL_HOST_FN bool maps_to_default() const SIXTRL_NOEXCEPT {
            return ( this->m_maps_to_id ==
                SIXTRL_CXX_NAMESPACE::ARGUMENT_MAPS_TO_DEFAULT ); }

        SIXTRL_HOST_FN bool maps_to_anything() const SIXTRL_NOEXCEPT {
            return ( this->m_maps_to_id !=
                SIXTRL_CXX_NAMESPACE::ARGUMENT_MAPS_TO_NONE ); }

        /* ------------------------------------------------------------------ */

        SIXTRL_HOST_FN cbuffer_type const& cbuffer() const SIXTRL_NOEXCEPT {
            return this->m_cbuffer; }

        SIXTRL_HOST_FN cbuffer_type& cbuffer() SIXTRL_NOEXCEPT {
            return this->m_cbuffer; }

        /* ------------------------------------------------------------------ */

        SIXTRL_HOST_FN bool can_push() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_type push();

        SIXTRL_HOST_FN bool can_collect() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_type collect();

        /* ------------------------------------------------------------------ */

        SIXTRL_HOST_FN ctrl_base_const_pointer
        base_controller() const SIXTRL_NOEXCEPT { return this->m_ptr_ctrl; }

        SIXTRL_HOST_FN ctrl_base_pointer base_controller() SIXTRL_NOEXCEPT {
            return this->m_ptr_ctrl; }

        protected:

        SIXTRL_HOST_FN ArgumentBase(
            backend_id_type const backend_id,
            class_id_type const derived_class_id ) :
            BackendObjBase( backend_id, BASE_CLASS_ID, derived_class_id )
        {

        }

        SIXTRL_HOST_FN ArgumentBase( ArgumentBase const& ) = default;
        SIXTRL_HOST_FN ArgumentBase( ArgumentBase&& ) = default;

        SIXTRL_HOST_FN ArgumentBase& operator=( ArgumentBase const& ) = default;
        SIXTRL_HOST_FN ArgumentBase& operator=( ArgumentBase&& ) = default;

        /* - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN virtual status_type do_push();
        SIXTRL_HOST_FN virtual status_type do_collect();

        /* - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN void _set_ptr_ctrl(
            ctrl_base_pointer SIXTRL_RESTRICT ptr_ctrl ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void _set_holds_id(
            hold_id_type const hold_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void _set_maps_to_id(
            mapsto_id_type const maps_to_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN cbuffer_type& _cbuffer() SIXTRL_NOEXCEPT {
            return this->m_cbuffer; }

        SIXTRL_HOST_FN cbuffer_type const& _cbuffer() const SIXTRL_NOEXCEPT {
            return this->m_cbuffer; }

        SIXTRL_HOST_FN void _set_is_ready( bool const flag ) SIXTRL_NOEXCEPT {
            this->m_is_ready = flag; }

        private:

        cbuffer_type m_cbuffer;
        address_type m_ptr_begin_addr;
        size_type    m_ptr_size;

        hold_id_type m_holds_id = SIXTRL_CXX_NAMESPACE::ARGUMENT_HOLDS_NONE;
        mapsto_id_type m_maps_to_id = SIXTRL_CXX_NAMESPACE::ARGUMENT_MAPS_TO_NONE;
        ctrl_base_pointer m_ptr_ctrl = nullptr;
        bool m_is_ready = false;
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::ArgumentBase >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::ARGUMENT_BASE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::ARGUMENT_BASE_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE,
        SIXTRL_CXX_NAMESPACE::ARGUMENT_BASE_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::ArgumentBase backend_obj_type;
    };
}
#endif /* defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE ) && defined( __cplusplus )
typedef SIXTRL_CXX_NAMESPACE::ArgumentBase NS(ArgumentBase);
#else
typedef void NS(ArgumentBase);
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/controller.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#endif /* SIXTRACKLIB_COMON_TRACK_ARGUMENT_H__ */
