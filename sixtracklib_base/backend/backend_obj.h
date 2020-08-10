#ifndef SIXTRACKLIB_BASE_BACKEND_BACKEND_OBJ_H__
#define SIXTRACKLIB_BASE_BACKEND_BACKEND_OBJ_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/backend/definitions.h"
    #include "sixtracklib_base/internal/class_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class SIXTRL_BASE_EXPORT_API BaseBackendObj
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::backend_id_t backend_id_t;
        typedef SIXTRL_CXX_NAMESPACE::obj_class_id_t class_id_t;
        typedef SIXTRL_CXX_NAMESPACE::obj_class_variant_t class_variant_t;
        typedef SIXTRL_CXX_NAMESPACE::status_t status_t;

        SIXTRL_HOST_FN explicit BaseBackendObj(
            backend_id_t const backend_id =
                SIXTRL_CXX_NAMESPACE::BACKEND_UNDEFINED,
            class_id_t const class_id =
                SIXTRL_CXX_NAMESPACE::CLASS_ID_UNDEFINED,
            class_variant_t const var = class_variant_t{ 0 } ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN BaseBackendObj( BaseBackendObj const& ) = default;
        SIXTRL_HOST_FN BaseBackendObj( BaseBackendObj&& ) = default;

        SIXTRL_HOST_FN BaseBackendObj&
        operator=( BaseBackendObj const& ) = default;

        SIXTRL_HOST_FN BaseBackendObj& operator=( BaseBackendObj&& ) = default;
        SIXTRL_HOST_FN virtual ~BaseBackendObj() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN backend_id_t backend_id() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN class_id_t class_id() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN class_variant_t class_variant_flags() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_class_variant(
            class_variant_t const flags ) const SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN status_t set_backend_id(
            backend_id_t const backend_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_class_id(
            class_id_t const class_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_class_variant(
            class_variant_t const class_variant ) SIXTRL_NOEXCEPT;

        private:

        backend_id_t m_backend_id;
        class_id_t m_class_id;
        class_variant_t m_class_variant_flags;
    };
}

#if !defined( _GPUCODE )
extern "C" {
#endif /* !defined( _GPUCODE ) */

typedef SIXTRL_CXX_NAMESPACE::BaseBackendObj NS(BaseBackendObj);

#if !defined( _GPUCODE )
}
#endif /* !defined( _GPUCODE ) */

#else

strict NS(BaseBackendObj);

#endif /* C++ */
#endif /* SIXTRACKLIB_BASE_BACKEND_BACKEND_OBJ_H__ */
