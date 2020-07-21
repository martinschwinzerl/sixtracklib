#ifndef SIXTRACKLIB_COMMON_CONTROL_ARCH_BASE_OBJECT_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_ARCH_BASE_OBJECT_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/arch_info.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <string>
        #include <type_traits>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class BaseArchObj : public SIXTRL_CXX_NAMESPACE::ArchInfo
    {
        public:

        using class_id_t = SIXTRL_CXX_NAMESPACE::arch_class_id_t;
        using status_t = SIXTRL_CXX_NAMESPACE::arch_status_t;

        static constexpr class_id_t UNDEFINED_CLASS =
            SIXTRL_CXX_NAMESPACE::ARCH_CLASS_ID_UNDEFINED;

        SIXTRL_HOST_FN class_id_t class_id() const SIXTRL_NOEXCEPT
        {
            return this->m_class_id;
        }

        SIXTRL_HOST_FN bool is_arch_obj_compatible_with(
            BaseArchObj const& SIXTRL_RESTRICT_REF other ) const SIXTRL_NOEXCEPT
        {
            return ( ( this->archId() == other.archId() ) &&
                     ( ( ( this->m_class_id != UNDEFINED_CLASS ) &&
                         ( this->m_class_id == other.m_class_id ) ) ||
                       ( this->m_class_id == UNDEFINED_CLASS ) ) );
        }

        protected:

        SIXTRL_HOST_FN explicit BaseArchObj(
            arch_id_t const arch_id,
            class_id_t const class_id = UNDEFINED_CLASS,
            std::string const& SIXTRL_RESTRICT_REF arch_str = std::string{} ) :
            ArchInfo( arch_id, arch_str ), m_class_id( class_id )
        {

        }

        SIXTRL_HOST_FN BaseArchObj( BaseArchObj const& ) = default;
        SIXTRL_HOST_FN BaseArchObj( BaseArchObj&& ) = default;

        SIXTRL_HOST_FN BaseArchObj& operator=( BaseArchObj const& ) = default;
        SIXTRL_HOST_FN BaseArchObj& operator=( BaseArchObj&& ) = default;

        SIXTRL_HOST_FN virtual ~BaseArchObj() = default;

        SIXTRL_HOST_FN void do_set_class_id(
            class_id_t const class_id ) SIXTRL_NOEXCEPT
        {
            this->m_class_id = class_id;
        }

        private:

        class_id_t m_class_id;
    };

    class ArchBase : public SIXTRL_CXX_NAMESPACE::ArchInfo
    {
        public:

        using arch_info_t = SIXTRL_CXX_NAMESPACE::ArchInfo;
        using status_t    = SIXTRL_CXX_NAMESPACE::arch_status_t;

        SIXTRL_HOST_FN explicit ArchBase( arch_id_t const arch_id,
            const char *const SIXTRL_RESTRICT arch_str = nullptr,
            const char *const SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN explicit ArchBase(
            arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT arch_str,
            std::string const& SIXTRL_RESTRICT config_str = std::string{} );

        SIXTRL_HOST_FN ArchBase( ArchBase const& other ) = default;
        SIXTRL_HOST_FN ArchBase( ArchBase&& other ) = default;

        SIXTRL_HOST_FN ArchBase& operator=( ArchBase const& rhs ) = default;
        SIXTRL_HOST_FN ArchBase& operator=( ArchBase&& rhs ) = default;

        SIXTRL_HOST_FN virtual ~ArchBase() = default;

        template< class Derived > SIXTRL_HOST_FN Derived const* asDerived(
            arch_id_t const required_arch_id,
            bool requires_exact_match = false ) const SIXTRL_NOEXCEPT;

        template< class Derived > SIXTRL_HOST_FN Derived* asDerived(
            arch_id_t const required_arch_id,
            bool requires_exact_match = false ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasConfigStr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& configStr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrConfigStr() const SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN virtual bool doParseConfigStr(
            const char *const SIXTRL_RESTRICT config_str );

        SIXTRL_HOST_FN void doUpdateStoredConfigStr(
            const char *const SIXTRL_RESTRICT config_str );

        private:

        SIXTRL_HOST_FN bool doParseConfigStrArchBase(
            const char *const SIXTRL_RESTRICT config_str ) SIXTRL_NOEXCEPT;


        std::string m_config_str;
    };

    class ArchDebugBase : public SIXTRL_CXX_NAMESPACE::ArchBase
    {
        private:

        using _arch_base_t = SIXTRL_CXX_NAMESPACE::ArchBase;

        public:

        using debug_register_t = SIXTRL_CXX_NAMESPACE::arch_debugging_t;

        static SIXTRL_CONSTEXPR_OR_CONST debug_register_t DEBUG_REGISTER_OK =
            SIXTRL_CXX_NAMESPACE::ARCH_DEBUGGING_REGISTER_EMPTY;

        SIXTRL_HOST_FN explicit ArchDebugBase( arch_id_t const arch_id,
            const char *const SIXTRL_RESTRICT arch_str = nullptr,
            const char *const SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN explicit ArchDebugBase( arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF arch_str,
            std::string const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN ArchDebugBase( ArchDebugBase const& other ) = default;
        SIXTRL_HOST_FN ArchDebugBase( ArchDebugBase&& other ) = default;

        SIXTRL_HOST_FN ArchDebugBase&
        operator=( ArchDebugBase const& rhs ) = default;

        SIXTRL_HOST_FN ArchDebugBase&
        operator=( ArchDebugBase&& rhs ) = default;

        SIXTRL_HOST_FN virtual ~ArchDebugBase() = default;

        SIXTRL_HOST_FN bool isInDebugMode() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_t enableDebugMode();
        SIXTRL_HOST_FN status_t disableDebugMode();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN debug_register_t debugRegister();

        SIXTRL_HOST_FN status_t setDebugRegister(
            debug_register_t const debug_register );

        SIXTRL_HOST_FN status_t prepareDebugRegisterForUse();
        SIXTRL_HOST_FN status_t evaluateDebugRegisterAfterUse();

        protected:

        static SIXTRL_CONSTEXPR_OR_CONST size_type
            DEBUG_REGISTER_SIZE = sizeof( debug_register_t );

        SIXTRL_HOST_FN virtual status_t doSwitchDebugMode(
            bool const is_in_debug_mode );

        SIXTRL_HOST_FN virtual status_t doSetDebugRegister(
            debug_register_t const debug_register );

        SIXTRL_HOST_FN virtual status_t doFetchDebugRegister(
            debug_register_t* SIXTRL_RESTRICT ptr_debug_register );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void doSetDebugModeFlag(
            bool const debug_mode ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN debug_register_t const*
        doGetPtrLocalDebugRegister() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN debug_register_t*
        doGetPtrLocalDebugRegister() SIXTRL_NOEXCEPT;

        private:

        debug_register_t m_local_debug_register;
        bool m_debug_mode;
    };
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )

typedef SIXTRL_CXX_NAMESPACE::ArchBase      NS(ArchBase);
typedef SIXTRL_CXX_NAMESPACE::ArchDebugBase NS(ArchDebugBase);

#else /* C++, Host */

typedef void NS(ArchBase);
typedef void NS(ArchDebugBase);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_CONTROL_ARCH_BASE_OBJECT_HPP__ */
