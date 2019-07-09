#ifndef SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_KEY_CXX_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_KEY_CXX_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <memory>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_id.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/kernel_config_key.h"
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    class KernelConfigKey : private ::NS(KernelConfigKey)
    {
        public:

        using node_id_t     = SIXTRL_CXX_NAMESPACE::node_id_t;
        using arch_id_t     = node_id_t::arch_id_t;
        using platform_id_t = node_id_t::platform_id_t;
        using device_id_t   = node_id_t::device_id_t;
        using purpose_t     = SIXTRL_CXX_NAMESPACE::kernel_purpose_t;
        using variant_t     = SIXTRL_CXX_NAMESPACE::kernel_variant_t;
        using c_api_t       = ::NS(KernelConfigKey);

        static constexpr purpose_t UNSPECIFIED_PURPOSE =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;

        static constexpr variant_t DEFAULT_VARIANT =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_VARIANT_NONE;

        SIXTRL_HOST_FN explicit KernelConfigKey(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose = UNSPECIFIED_PURPOSE,
            variant_t const variant = DEFAULT_VARIANT ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN KernelConfigKey(
            KernelConfigKey const& SIXTRL_RESTRICT_REF orig ) = default;

        SIXTRL_HOST_FN KernelConfigKey(
            KernelConfigKey&& SIXTRL_RESTRICT_REF orig ) = default;

        SIXTRL_HOST_FN KernelConfigKey& operator=(
            KernelConfigKey const& SIXTRL_RESTRICT_REF rhs ) = default;

        SIXTRL_HOST_FN KernelConfigKey& operator=(
            KernelConfigKey&& rhs ) = default;

        SIXTRL_HOST_FN ~KernelConfigKey() = default;

        /* ------------------------------------------------------------- */

        SIXTRL_HOST_FN c_api_t const* getCApiPtr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN c_api_t* getCApiPtr() SIXTRL_NOEXCEPT;

        /* ------------------------------------------------------------- */

        SIXTRL_HOST_FN arch_id_t archId() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN platform_id_t platformId() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN device_id_t deviceId() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool operator<( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool operator==( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN int compare( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;
    };
}

#endif /* C++, Host */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE KernelConfigKey::KernelConfigKey(
        KernelConfigKey::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigKey::purpose_t const purpose,
        KernelConfigKey::variant_t const variant ) SIXTRL_NOEXCEPT :
        ::NS(KernelConfigKey)()
    {
        SIXTRL_CXX_NAMESPACE::status_t const status =
            ::NS(KernelConfigKey_init)( &node_id, purpose, variant );
        ( void )status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigKey::c_api_t const*
    KernelConfigKey::getCApiPtr() const SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< KernelConfigKey::c_api_t const* >( this );
    }

    SIXTRL_INLINE KernelConfigKey::c_api_t*
    KernelConfigKey::getCApiPtr() SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< KernelConfigKey::c_api_t* >( this );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigKey::arch_id_t
    KernelConfigKey::archId() const SIXTRL_NOEXCEPT
    {
        return ::NS(KernelConfigKey_get_arch_id)( this->getCApiPtr() );
    }

    SIXTRL_INLINE KernelConfigKey::platform_id_t
    KernelConfigKey::platformId() const SIXTRL_NOEXCEPT
    {
        return ::NS(KernelConfigKey_get_platform_id)( this->getCApiPtr() );
    }

    SIXTRL_INLINE KernelConfigKey::device_id_t
    KernelConfigKey::deviceId() const SIXTRL_NOEXCEPT
    {
        return ::NS(KernelConfigKey_get_device_id)( this->getCApiPtr() );
    }

    SIXTRL_INLINE bool KernelConfigKey::operator<(
        KernelConfigKey const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        return ::NS(KernelConfigKey_is_smaller_than)(
            this->getCApiPtr(), rhs.getCApiPtr() );
    }

    SIXTRL_INLINE bool KernelConfigKey::operator==(
        KernelConfigKey const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        return ::NS(KernelConfigKey_is_equal)(
            this->getCApiPtr(), rhs.getCApiPtr() );
    }

    SIXTRL_INLINE int KernelConfigKey::compare(
        KernelConfigKey const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        return ::NS(KernelConfigKey_compare)(
            this->getCApiPtr(), rhs.getCApiPtr() );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_KEY_CXX_HPP__ */
