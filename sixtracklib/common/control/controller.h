#ifndef SIXTRACKLIB_COMMON_CONTROL_CONTROLLER_BASE_H__
#define SIXTRACKLIB_COMMON_CONTROL_CONTROLLER_BASE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/backends/backend_obj_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class ArgumentBase;

    class ControllerBase : public SIXTRL_CXX_NAMESPACE::BackendObjBase
    {
        public:

        using arg_base_type = SIXTRL_CXX_NAMESPACE::ArgumentBase;

        static constexpr class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::CONTROLLER_BASE_CLASS_ID;

        SIXTRL_HOST_FN virtual ~ControllerBase() = default;

        SIXTRL_HOST_FN status_type remap_argument(
            arg_base_type& SIXTRL_RESTRICT_REF arg ) const;

        protected:

        SIXTRL_HOST_FN ControllerBase(
            backend_id_type const backend_id,
            class_id_type const derived_class_id ) :
            BackendObjBase( backend_id, BASE_CLASS_ID, derived_class_id )
        {

        }

        SIXTRL_HOST_FN ControllerBase( ControllerBase const& ) = default;
        SIXTRL_HOST_FN ControllerBase( ControllerBase&& ) = default;

        SIXTRL_HOST_FN ControllerBase& operator=( ControllerBase&& ) = default;
        SIXTRL_HOST_FN ControllerBase& operator=(
            ControllerBase const& ) = default;

        SIXTRL_HOST_FN virtual status_type do_remap_argument(
            arg_base_type& SIXTRL_RESTRICT_REF arg );
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::ControllerBase >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::CONTROLLER_BASE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::CONTROLLER_BASE_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE,
        SIXTRL_CXX_NAMESPACE::CONTROLLER_BASE_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::ControllerBase backend_obj_type;
    };

    /* ********************************************************************* */

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE ) && defined( __cplusplus )
typedef SIXTRL_CXX_NAMESPACE::ControllerBase NS(ControllerBase);
#else
typedef void NS(ControllerBase);
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/argument.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#endif /* SIXTRACKLIB_COMMON_CONTROL_CONTROLLER_BASE_H__ */
