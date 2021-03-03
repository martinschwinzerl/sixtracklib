#ifndef SIXTRACKLIB_COMMON_CONTROL_MT_BACKEND_OBJ_BASE_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_MT_BACKEND_OBJ_BASE_HPP__


#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/backends/backend_obj_base.hpp"
    #include "sixtracklib/common/internal/thread_id.h"
    #include "sixtracklib/common/internal/thread_lock.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <thread>
    #include <mutex>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class MTBackendObjBase : public BackendObjBase
    {
        public:

        using thread_id_type = SIXTRL_CXX_NAMESPACE::ThreadId;
        using lockable_type  = SIXTRL_CXX_NAMESPACE::ThreadLockable;
        using guard_type     = SIXTRL_CXX_NAMESPACE::ThreadUniqueLock;

        SIXTRL_HOST_FN lockable_type* ptr_lockable() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN lockable_type& lockable() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN guard_type create_lock() const;

        SIXTRL_HOST_FN bool is_locked( guard_type const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN virtual ~MTBackendObjBase() = default;

        protected:

        SIXTRL_HOST_FN MTBackendObjBase(
            backend_id_type const backend_id,
            class_id_type const base_class_id,
            class_id_type const derived_class_id ) :
            BackendObjBase( backend_id, base_class_id, derived_class_id ),
            m_lockable()
        {
        }

        SIXTRL_HOST_FN MTBackendObjBase( MTBackendObjBase const& ) = delete;
        SIXTRL_HOST_FN MTBackendObjBase( MTBackendObjBase&& ) = delete;

        SIXTRL_HOST_FN MTBackendObjBase& operator=(
            MTBackendObjBase&& ) = delete;

        SIXTRL_HOST_FN MTBackendObjBase& operator=(
            MTBackendObjBase const& ) = delete;

        private:

        mutable lockable_type m_lockable;
    };

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_CONTROL_MT_BACKEND_OBJ_BASE_HPP__ */
