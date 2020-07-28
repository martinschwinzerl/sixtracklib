#ifndef SIXTRACKLIB_BASE_ARCHITECTURE_ARCH_OBJ_H__
#define SIXTRACKLIB_BASE_ARCHITECTURE_ARCH_OBJ_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/architecture/definitions.h"
    #include "sixtracklib/base/internal/class_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <string>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class SIXTRL_BASE_EXPORT_API BaseArchObj
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::arch_id_t arch_id_t;
        typedef SIXTRL_CXX_NAMESPACE::obj_class_id_t class_id_t;
        typedef SIXTRL_CXX_NAMESPACE::obj_class_variant_t class_variant_t;
        typedef SIXTRL_CXX_NAMESPACE::status_t status_t;

        SIXTRL_HOST_FN SIXTRL_BASE_EXPORT_API SIXTRL_INLINE
        explicit BaseArchObj(
            arch_id_t const arch_id =
                SIXTRL_CXX_NAMESPACE::ARCHITECTURE_UNDEFINED,
            class_id_t const class_id =
                SIXTRL_CXX_NAMESPACE::CLASS_ID_UNDEFINED,
            class_variant_t const var = class_variant_t{ 0 } ) SIXTRL_NOEXCEPT :
            m_arch_id( arch_id ), m_class_id( class_id ),
            m_class_variant_flags( var )
        {

        }

        SIXTRL_HOST_FN BaseArchObj( BaseArchObj const& ) = default;
        SIXTRL_HOST_FN BaseArchObj( BaseArchObj&& ) = default;

        SIXTRL_HOST_FN BaseArchObj& operator=( BaseArchObj const& ) = default;
        SIXTRL_HOST_FN BaseArchObj& operator=( BaseArchObj&& ) = default;

        SIXTRL_HOST_FN virtual ~BaseArchObj() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN SIXTRL_BASE_EXPORT_API SIXTRL_INLINE
        arch_id_t arch_id() const SIXTRL_NOEXCEPT {
            return this->m_arch_id; }

        SIXTRL_HOST_FN SIXTRL_BASE_EXPORT_API SIXTRL_INLINE
        class_id_t class_id() const SIXTRL_NOEXCEPT {
            return this->m_class_id; }

        SIXTRL_HOST_FN SIXTRL_BASE_EXPORT_API SIXTRL_INLINE
        class_variant_t class_variant_flags() const SIXTRL_NOEXCEPT {
            return this->m_class_variant_flags; }

        SIXTRL_HOST_FN SIXTRL_BASE_EXPORT_API SIXTRL_INLINE bool
        is_class_variant( class_variant_t const flags ) const SIXTRL_NOEXCEPT {
            return ( ( flags != class_variant_t{ 0 } ) &&
                     ( ( this->m_class_variant_flags & flags ) == flags ) );
        }

        protected:

        SIXTRL_HOST_FN status_t set_arch_id(
            arch_id_t const arch_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_class_id(
            class_id_t const class_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_class_variant(
            class_variant_t const class_variant ) SIXTRL_NOEXCEPT;

        private:

        arch_id_t m_arch_id;
        class_id_t m_class_id;
        class_variant_t m_class_variant_flags;
    };
}

#if !defined( _GPUCODE )
extern "C" {
#endif /* !defined( _GPUCODE ) */

typedef SIXTRL_CXX_NAMESPACE::BaseArchObj NS(BaseArchObj);

#if !defined( _GPUCODE )
}
#endif /* !defined( _GPUCODE ) */

#else

strict NS(BaseArchObj);

#endif /* C++ */

#endif /* SIXTRACKLIB_BASE_ARCHITECTURE_ARCH_OBJ_H__ */
