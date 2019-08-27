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
    #include "sixtracklib/common/control/node_id.h"
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

        using size_type      = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using purpose_t      = SIXTRL_CXX_NAMESPACE::kernel_purpose_t;
        using argument_set_t = SIXTRL_CXX_NAMESPACE::kernel_argument_set_t;
        using node_id_t      = SIXTRL_CXX_NAMESPACE::NodeId;
        using c_node_id_t    = node_id_t::c_api_t;
        using arch_id_t      = node_id_t::arch_id_t;
        using platform_id_t  = node_id_t::platform_id_t;
        using device_id_t    = node_id_t::device_id_t;

        static constexpr platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static constexpr device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static constexpr purpose_t UNSPECIFIED_PURPOSE =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;

        static constexpr arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static constexpr argument_set_t DEFAULT_ARGUMENT_SET =
            SIXTRL_CXX_NAMESPACE::DEFAULT_KERNEL_ARGUMENT_SET;

        SIXTRL_HOST_FN KernelConfigKey();

        template< typename... Args >
        SIXTRL_HOST_FN KernelConfigKey( Args&&... args );

        SIXTRL_HOST_FN KernelConfigKey(
            KernelConfigKey const& other ) = default;

        SIXTRL_HOST_FN KernelConfigKey( KernelConfigKey&& other ) = default;

        SIXTRL_HOST_FN KernelConfigKey& operator=(
            KernelConfigKey const& SIXTRL_RESTRICT_REF rhs ) = default;

        SIXTRL_HOST_FN KernelConfigKey& operator=(
            KernelConfigKey&& rhs ) = default;

        SIXTRL_HOST_FN virtual ~KernelConfigKey() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN arch_id_t archId()  const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN purpose_t purpose() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN argument_set_t argumentSet() const SIXTRL_NOEXCEPT;

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

        SIXTRL_HOST_FN void setArgumentSet(
            argument_set_t const argument_set ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setNodeId(
            node_id_t const& SIXTRL_RESTRICT_REF node_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setNodeId(
            const c_node_id_t *const SIXTRL_RESTRICT node_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setPlatformAndDeviceId(
            platform_id_t const platform_id,
            device_id_t const device_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setConfigStr(
            std::string const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN void setConfigStr(
            char const* SIXTRL_RESTRICT config_str );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool operator<( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool operator==( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool operator!=( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isEqualExceptPurpose( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN int compare( KernelConfigKey const&
            SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void clear();

        SIXTRL_HOST_FN status_t reset(
            arch_id_t const arch_id = ARCH_ILLEGAL,
            purpose_t const purpose = UNSPECIFIED_PURPOSE,
            variant_t const variant = _base_t::DEFAULT_VARIANT,
            argument_set_t const argument_set = DEFAULT_ARGUMENT_SET,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{} );

        SIXTRL_HOST_FN status_t reset( arch_id_t const arch_id,
            purpose_t const purpose, variant_t const variant,
            argument_set_t const argument_set,
            char const* SIXTRL_RESTRICT config_str );

        SIXTRL_HOST_FN status_t reset(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose = UNSPECIFIED_PURPOSE,
            variant_t const variant = _base_t::DEFAULT_VARIANT,
            argument_set_t const argument_set = DEFAULT_ARGUMENT_SET,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{} );

        SIXTRL_HOST_FN status_t reset(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose, variant_t const variant,
            argument_set_t const argument_set,
            char const* SIXTRL_RESTRICT config_str );

        SIXTRL_HOST_FN status_t reset(
            const ::NS(NodeId) *const SIXTRL_RESTRICT ptr_node_id,
            purpose_t const purpose = UNSPECIFIED_PURPOSE,
            variant_t const variant = _base_t::DEFAULT_VARIANT,
            argument_set_t const argument_set = DEFAULT_ARGUMENT_SET,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{} );

        SIXTRL_HOST_FN status_t reset(
            const ::NS(NodeId) *const SIXTRL_RESTRICT ptr_node_id,
            purpose_t const purpose, variant_t const variant,
            argument_set_t const argument_set,
            char const* SIXTRL_RESTRICT config_str );

        SIXTRL_HOST_FN status_t reset(
            KernelConfigKey const& SIXTRL_RESTRICT other );

        SIXTRL_HOST_FN status_t reset(
            KernelConfigKey&& SIXTRL_RESTRICT other );

        private:

        node_id_t       m_node_id;
        std::string     m_config_str;
        purpose_t       m_purpose;
        argument_set_t  m_argument_set;
    };
}

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

typedef SIXTRL_CXX_NAMESPACE::KernelConfigKey   NS(KernelConfigKey);

#else

typedef void NS(KernelConfigKey);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE KernelConfigKey::KernelConfigKey() :
        KernelConfigKey::_base_t( KernelConfigKey::DEFAULT_VARIANT ),
        m_node_id( KernelConfigKey::ARCH_ILLEGAL ),
        m_config_str(),
        m_purpose( KernelConfigKey::UNSPECIFIED_PURPOSE ),
        m_argument_set( KernelConfigKey::DEFAULT_ARGUMENT_SET )
    {

    }

    template< typename... Args >
    KernelConfigKey::KernelConfigKey( Args&&... args ) :
        KernelConfigKey::_base_t( KernelConfigKey::DEFAULT_VARIANT ),
        m_node_id( KernelConfigKey::ARCH_ILLEGAL ),
        m_config_str(),
        m_purpose( KernelConfigKey::UNSPECIFIED_PURPOSE ),
        m_argument_set( KernelConfigKey::DEFAULT_ARGUMENT_SET )
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

    SIXTRL_INLINE KernelConfigKey::argument_set_t
    KernelConfigKey::argumentSet() const SIXTRL_NOEXCEPT
    {
        return this->m_argument_set;
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

    SIXTRL_INLINE void KernelConfigKey::setPurpose(
        KernelConfigKey::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        this->m_purpose = purpose;
    }

    SIXTRL_INLINE void KernelConfigKey::setVariant(
        KernelConfigKey::variant_t const variant_flags ) SIXTRL_NOEXCEPT
    {
        this->doSetVariantFlags( variant_flags );
    }

    SIXTRL_INLINE void KernelConfigKey::setArgumentSet(
        KernelConfigKey::argument_set_t const argument_set ) SIXTRL_NOEXCEPT
    {
        this->m_argument_set = argument_set;
    }

    SIXTRL_INLINE void KernelConfigKey::setConfigStr(
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        this->m_config_str = config_str;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool KernelConfigKey::operator==( KernelConfigKey const&
        SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->isEqualExceptPurpose( rhs ) ) &&
                 ( this->purpose() == rhs.purpose() ) );
    }

    SIXTRL_INLINE bool KernelConfigKey::operator!=( KernelConfigKey const&
        SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->purpose() != rhs.purpose() ) ||
                 ( !this->isEqualExceptPurpose( rhs ) ) );
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
        KernelConfigKey::argument_set_t const argument_set,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        return this->reset( arch_id, purpose, variant,
                            argument_set, config_str.c_str() );
    }

    SIXTRL_INLINE KernelConfigKey::status_t KernelConfigKey::reset(
        KernelConfigKey::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigKey::purpose_t const purpose,
        KernelConfigKey::variant_t const variant,
        KernelConfigKey::argument_set_t const argument_set,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        return this->reset( node_id, purpose, variant,
                            argument_set, config_str.c_str() );
    }

    SIXTRL_INLINE KernelConfigKey::status_t
    KernelConfigKey::reset(
        KernelConfigKey::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigKey::purpose_t const purpose,
        KernelConfigKey::variant_t const variant,
        KernelConfigKey::argument_set_t const argument_set,
        char const* SIXTRL_RESTRICT config_str )
    {
        this->m_node_id = node_id;
        this->setPurpose( purpose );
        this->setVariant( variant );
        this->setArgumentSet( argument_set );
        this->setConfigStr( config_str );

        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    SIXTRL_INLINE KernelConfigKey::status_t KernelConfigKey::reset(
        const ::NS(NodeId) *const SIXTRL_RESTRICT ptr_node_id,
        KernelConfigKey::purpose_t const purpose,
        KernelConfigKey::variant_t const variant,
        KernelConfigKey::argument_set_t const argument_set,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        return this->reset( ptr_node_id, purpose, variant,
                            argument_set, config_str.c_str() );
    }

    SIXTRL_INLINE KernelConfigKey::status_t KernelConfigKey::reset(
        KernelConfigKey const& SIXTRL_RESTRICT other )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::KernelConfigKey;

        _this_t::status_t status = st::ARCH_STATUS_SUCCESS;

        if( this == &other )
        {
            return st::ARCH_STATUS_SUCCESS;
        }

        if( other.hasNodeId() )
        {
            this->m_node_id = other.m_node_id;
        }
        else
        {
            status = this->m_node_id.setArchId( other.archId() );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            this->setPurpose( other.purpose() );
            this->setVariant( other.variant() );
            this->setArgumentSet( other.argumentSet() );
            this->setConfigStr( other.ptrConfigStr() );
        }

        return status;
    }

    SIXTRL_INLINE KernelConfigKey::status_t KernelConfigKey::reset(
        KernelConfigKey&& SIXTRL_RESTRICT other )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::KernelConfigKey;

        _this_t::status_t status = st::ARCH_STATUS_SUCCESS;

        if( this != &other )
        {
            this->m_node_id         = std::move( other.m_node_id );
            this->m_purpose         = std::move( other.m_purpose );
            this->m_argument_set    = std::move( other.m_argument_set );
            this->m_config_str      = std::move( other.m_config_str );
            this->setVariant( other.variant() );

            other.clear();
        }

        return status;
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_KEY_CXX_HPP__ */
