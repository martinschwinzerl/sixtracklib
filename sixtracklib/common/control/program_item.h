#ifndef SIXTRACKLIB_COMMON_CONTROL_PROGRAM_ITEM_H__
#define SIXTRACKLIB_COMMON_CONTROL_PROGRAM_ITEM_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/backends/backend_obj_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class ProgramItemBase : public SIXTRL_CXX_NAMESPACE::BackendObjBase
    {
        public:

        static constexpr class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::PROGRAM_ITEM_BASE_CLASS_ID;

        SIXTRL_HOST_FN virtual ~ProgramItemBase() = default;

        protected:

        SIXTRL_HOST_FN ProgramItemBase( backend_id_type const backend_id,
            class_id_type const derived_class_id ) :
            BackendObjBase( backend_id, BASE_CLASS_ID, derived_class_id )
        {

        }

        SIXTRL_HOST_FN ProgramItemBase( ProgramItemBase const& ) = default;
        SIXTRL_HOST_FN ProgramItemBase( ProgramItemBase&& ) = default;

        SIXTRL_HOST_FN ProgramItemBase& operator=( ProgramItemBase&& ) = default;
        SIXTRL_HOST_FN ProgramItemBase& operator=(
            ProgramItemBase const& ) = default;
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::ProgramItemBase >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::PROGRAM_ITEM_BASE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::PROGRAM_ITEM_BASE_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE,
        SIXTRL_CXX_NAMESPACE::PROGRAM_ITEM_BASE_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::ProgramItemBase backend_obj_type;
    };
}
#endif /* C++, Host */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
typedef SIXTRL_CXX_NAMESPACE::ProgramItemBase NS(ProgramItemBase);
#else  /*  defined( _GPUCODE ) || !defined( __cplusplus ) */
typedef void NS(ProgramItemBase);
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_CONTROL_PROGRAM_ITEM_H__ */
