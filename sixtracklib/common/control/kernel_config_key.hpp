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
    #include "sixtracklib/common/control/arch_variant_mixin.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/architecture/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    struct KernelConfigKeyBase {};

    class KernelConfigKey : public SIXTRL_CXX_NAMESPACE::ArchVariantMixin<
        SIXTRL_CXX_NAMESPACE::KernelConfigKeyBase >
    {
        private:

        using _base_t = SIXTRL_CXX_NAMESPACE::ArchVariantMixin<
            SIXTRL_CXX_NAMESPACE::KernelConfigKeyBase >;

        public:

        using size_type     = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using purpose_t     = SIXTRL_CXX_NAMESPACE::kernel_purpose_t;
        using node_id_t     = SIXTRL_CXX_NAMESPACE::NodeId;
        using arch_id_t     = node_id_t::arch_id_t;
        using platform_id_t = node_id_t::platform_id_t;
        using device_id_t   = node_id_t::device_id_t;

        static constexpr platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static constexpr device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static constexpr purpose_t UNSPECIFIED_PURPOSE =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;

        static constexpr arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        SIXTRL_HOST_FN KernelConfigKey();

        template< typename... Args >
        SIXTRL_HOST_FN explicit KernelConfigKey( Args&&... args );

        SIXTRL_HOST_FN KernelConfigKey(
            KernelConfigKey const& SIXTRL_RESTRICT_REF orig ) = default;

        SIXTRL_HOST_FN KernelConfigKey(
            KernelConfigKey&& SIXTRL_RESTRICT_REF orig ) = default;

        SIXTRL_HOST_FN KernelConfigKey& operator=(
            KernelConfigKey const& SIXTRL_RESTRICT_REF rhs ) = default;

        SIXTRL_HOST_FN KernelConfigKey& operator=(
            KernelConfigKey&& rhs ) = default;

        SIXTRL_HOST_FN virtual ~KernelConfigKey() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN arch_id_t archId()  const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN purpose_t purpose() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasConfigStr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& configStr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrConfigStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasNodeId() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_id_t const& nodeId() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_id_t const* ptrNodeId() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN platform_id_t platformId() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN device_id_t   deviceId()   const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool valid() const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN void setPurpose( purpose_t const ) SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN void setVariant( variant_t const ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setConfigStr(
            std::string const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN void setConfigStr(
            char const* SIXTRL_RESTRICT config_str );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool operator<( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool operator==( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN int compare( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void clear();

        SIXTRL_HOST_FN status_t reset(
            arch_id_t const arch_id = ARCH_ILLEGAL,
            purpose_t const purpose = UNSPECIFIED_PURPOSE,
            variant_t const variant = _base_t::DEFAULT_VARIANT,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{} );

        SIXTRL_HOST_FN status_t reset( arch_id_t const arch_id,
            purpose_t const purpose, variant_t const variant,
            char const* SIXTRL_RESTRICT config_str );

        SIXTRL_HOST_FN status_t reset(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose = UNSPECIFIED_PURPOSE,
            variant_t const variant = _base_t::DEFAULT_VARIANT,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{} );

        SIXTRL_HOST_FN status_t reset(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose, variant_t const variant,
            char const* SIXTRL_RESTRICT config_str );

        private:

        node_id_t       m_node_id;
        std::string     m_config_str;
        purpose_t       m_purpose;
    };
}

typedef SIXTRL_CXX_NAMESPACE::KernelConfigKey   NS(KernelConfigKey);

#else

typedef void NS(KernelConfigKey);

#endif /* C++, Host */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE KernelConfigKey::KernelConfigKey() :
        KernelConfigKey::_base_t( KernelConfigKey::DEFAULT_VARIANT ),
        m_node_id( KernelConfigKey::ARCH_ILLEGAL ),
        m_config_str(),
        m_purpose( KernelConfigKey::UNSPECIFIED_PURPOSE )
    {

    }

    template< typename... Args >
    KernelConfigKey::KernelConfigKey( Args&&... args ) :
        KernelConfigKey::_base_t( KernelConfigKey::DEFAULT_VARIANT ),
        m_node_id( KernelConfigKey::ARCH_ILLEGAL ),
        m_config_str(),
        m_purpose( KernelConfigKey::UNSPECIFIED_PURPOSE )
    {
        this->reset( std::forward< Args >( args )... );
    }

    SIXTRL_INLINE KernelConfigKey::arch_id_t
    KernelConfigKey::archId()  const SIXTRL_NOEXCEPT
    {
       return this->m_node_id.archId();
    }

    SIXTRL_INLINE KernelConfigKey::purpose_t
    KernelConfigKey::purpose() const SIXTRL_NOEXCEPT
    {
        return this->m_purpose;
    }

    SIXTRL_INLINE bool KernelConfigKey::hasConfigStr() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_config_str.empty() );
    }

    SIXTRL_INLINE std::string const&
    KernelConfigKey::configStr() const SIXTRL_NOEXCEPT
    {
        return this->m_config_str;
    }

    SIXTRL_INLINE char const*
    KernelConfigKey::ptrConfigStr() const SIXTRL_NOEXCEPT
    {
        return this->m_config_str.c_str();
    }

    SIXTRL_INLINE bool KernelConfigKey::hasNodeId() const SIXTRL_NOEXCEPT
    {
        return ( this->m_node_id.valid() );
    }

    SIXTRL_INLINE KernelConfigKey::node_id_t const&
    KernelConfigKey::nodeId() const SIXTRL_NOEXCEPT
    {
        return this->m_node_id;
    }

    SIXTRL_INLINE KernelConfigKey::node_id_t const*
    KernelConfigKey::ptrNodeId() const SIXTRL_NOEXCEPT
    {
        return &this->m_node_id;
    }

    SIXTRL_INLINE KernelConfigKey::platform_id_t
    KernelConfigKey::platformId() const SIXTRL_NOEXCEPT
    {
        return this->m_node_id.platformId();
    }

    SIXTRL_INLINE KernelConfigKey::device_id_t
    KernelConfigKey::deviceId()   const SIXTRL_NOEXCEPT
    {
        return this->m_node_id.deviceId();
    }

    SIXTRL_INLINE bool KernelConfigKey::valid() const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigKey;
        return ( this->m_node_id.archId() != _this_t::ARCH_ILLEGAL );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE void KernelConfigKey::setVariant(
        KernelConfigKey::variant_t const variant_flags ) SIXTRL_NOEXCEPT
    {
        this->doSetVariantFlags( variant_flags );
    }

    SIXTRL_INLINE void KernelConfigKey::setConfigStr(
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        this->m_config_str = config_str;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE void KernelConfigKey::clear()
    {
        this->reset();
    }

    SIXTRL_INLINE KernelConfigKey::status_t KernelConfigKey::reset(
        KernelConfigKey::arch_id_t const arch_id,
        KernelConfigKey::purpose_t const purpose,
        KernelConfigKey::variant_t const variant,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        return this->reset( arch_id, purpose, variant, config_str.c_str() );
    }

    SIXTRL_INLINE KernelConfigKey::status_t KernelConfigKey::reset(
        KernelConfigKey::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigKey::purpose_t const purpose,
        KernelConfigKey::variant_t const variant,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        return this->reset( node_id, purpose, variant, config_str.c_str() );
    }

    SIXTRL_INLINE KernelConfigKey::status_t
    KernelConfigKey::reset(
        KernelConfigKey::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigKey::purpose_t const purpose,
        KernelConfigKey::variant_t const variant,
        char const* SIXTRL_RESTRICT config_str )
    {
        this->m_node_id = node_id;
        this->setPurpose( purpose );
        this->setVariant( variant );
        this->setConfigStr( config_str );

        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_KEY_CXX_HPP__ */
