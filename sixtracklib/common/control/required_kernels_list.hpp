#ifndef SIXTRACKLIB_COMMON_CONTROL_REQUIRED_KERNELS_LIST_CXX_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_REQUIRED_KERNELS_LIST_CXX_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <cstdio>
    #include <stdexcept>
    #include <string>
    #include <memory>
    #include <unordered_map>
    #include <utility>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/arch_base.h"
    #include "sixtracklib/common/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/buffer.hpp"
    #include "sixtracklib/common/control/arch_base.hpp"
    #include "sixtracklib/common/control/kernel_config_key.hpp"
    #include "sixtracklib/common/control/kernel_config_base.hpp"
    #include "sixtracklib/common/control/kernel_config_store.hpp"
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class RequiredKernelsData
    {
        public:

        using key_t         = SIXTRL_CXX_NAMESPACE::KernelConfigKey;
        using config_base_t = SIXTRL_CXX_NAMESPACE::KernelConfigBase;
        using config_id_t   = SIXTRL_CXX_NAMESPACE::arch_kernel_id_t;
        using status_t      = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using purpose_t     = SIXTRL_CXX_NAMESPACE::kernel_purpose_t;
        using arch_id_t     = key_t::arch_id_t;

        static constexpr config_id_t ILLEGAL_KERNEL_ID =
            SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_KERNEL_ID;

        static constexpr purpose_t UNSPECIFIED_PUPRPOSE =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;

        static constexpr arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        SIXTRL_HOST_FN explicit RequiredKernelsData(
            key_t const& SIXTRL_RESTRICT key = key_t{},
            config_id_t const kernel_config_id = ILLEGAL_KERNEL_ID,
            config_base_t* SIXTRL_RESTRICT ptr_config_base = nullptr,
            bool const is_pinned = false );

        SIXTRL_HOST_FN RequiredKernelsData(
            RequiredKernelsData const& orig ) = default;

        SIXTRL_HOST_FN RequiredKernelsData(
            RequiredKernelsData&& orig ) = default;

        SIXTRL_HOST_FN RequiredKernelsData& operator=(
            RequiredKernelsData const& orig ) = default;

        SIXTRL_HOST_FN RequiredKernelsData& operator=(
            RequiredKernelsData&& orig ) = default;

        SIXTRL_HOST_FN ~RequiredKernelsData() = default;

        /* ----------------------------------------------------------------- */

        key_t const& key() const SIXTRL_NOEXCEPT;
        config_id_t kernelId() const SIXTRL_NOEXCEPT;

        status_t reset() SIXTRL_NOEXCEPT;

        status_t reset( key_t const& SIXTRL_RESTRICT_REF key,
                    KernelConfigStore& SIXTRL_RESTRICT_REF store );

        status_t reset(
            KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            KernelConfigStore& SIXTRL_RESTRICT_REF store );

        bool isActive() const SIXTRL_NOEXCEPT;

        bool isPinned() const SIXTRL_NOEXCEPT;
        void markAsPinned( bool const is_pinned = true ) SIXTRL_NOEXCEPT;

        bool hasConfig() const SIXTRL_NOEXCEPT;
        config_base_t const* ptrConfigBase() const SIXTRL_NOEXCEPT;
        config_base_t* ptrConfigBase() SIXTRL_NOEXCEPT;

        bool isSyncWithStore(
            KernelConfigStore const& SIXTRL_RESTRICT_REF store ) const;

        bool isSyncWithStore(
                KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
                KernelConfigStore const& SIXTRL_RESTRICT_REF store
            ) const SIXTRL_NOEXCEPT;

        status_t fetchConfig(
            KernelConfigStore& SIXTRL_RESTRICT_REF store );

        status_t fetchConfig(
            KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
            KernelConfigStore& SIXTRL_RESTRICT_REF store ) SIXTRL_NOEXCEPT;

        private:

        key_t           m_key;
        config_id_t     m_config_id;
        config_base_t*  m_ptr_config_base;
        bool            m_is_pinned;
    };


    class RequiredKernels
    {
        public:

        using requ_kernel_data_t  = SIXTRL_CXX_NAMESPACE::RequiredKernelsData;
        using key_t               = requ_kernel_data_t::key_t;
        using config_id_t         = requ_kernel_data_t::config_id_t;
        using config_base_t       = requ_kernel_data_t::config_base_t;
        using status_t            = requ_kernel_data_t::status_t;
        using purpose_t           = requ_kernel_data_t::purpose_t;
        using arch_id_t           = requ_kernel_data_t::arch_id_t;
        using size_type           = key_t::size_type;
        using variant_t           = key_t::variant_t;

        using kernel_config_store_base_t =
            SIXTRL_CXX_NAMESPACE::KernelConfigStore;

        using ptr_kernel_config_store_t =
            std::shared_ptr< kernel_config_store_base_t >;

        using lockable_t          = kernel_config_store_base_t::lockable_t;
        using lock_t              = kernel_config_store_base_t::lock_t;

        static constexpr config_id_t ILLEGAL_KERNEL_ID =
            SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_KERNEL_ID;

        static constexpr purpose_t UNSPECIFIED_PUPRPOSE =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;

        static constexpr arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        SIXTRL_HOST_FN explicit RequiredKernels(
            ptr_kernel_config_store_base_t& SIXTRL_RESTRICT_REF ptr_conf_store,
            size_type const num_purposes = size_type{ 0 },
            purpose_t const* SIXTRL_RESTRICT purposes_begin = nullptr );

        template< typename PurposeIter >
        SIXTRL_HOST_FN RequiredKernels(
            ptr_kernel_config_store_base_t& SIXTRL_RESTRICT_REF ptr_conf_store,
            PurposeIter purposes_begin, PurposeIter purposes_end );

        SIXTRL_HOST_FN RequiredKernels( RequiredKernels const& orig ) = default;
        SIXTRL_HOST_FN RequiredKernels( RequiredKernels&& orig ) = default;

        SIXTRL_HOST_FN RequiredKernels& operator=(
            RequiredKernels const& rhs ) = default;

        SIXTRL_HOST_FN RequiredKernels& operator=(
            RequiredKernels&& rhs ) = default;

        SIXTRL_HOST_FN virtual ~RequiredKernels() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type numPurposes() const;
        SIXTRL_HOST_FN purpose_t const* purposesBegin() const;
        SIXTRL_HOST_FN purpose_t const* purposesEnd() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN size_type numPurposes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN purpose_t const* purposesBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN purpose_t const* purposesEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasConfig(
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN config_base_t const*
        ptrConfigBase( purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN config_base_t*
        ptrConfigBase( purpose_t const purpose ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t fetchConfig( purpose_t const purpose );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool hasConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN config_base_t const* ptrConfigBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN config_base_t* ptrConfigBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t fetchConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock, purpose_t const purpose );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasConfigId(
            purpose_t const purpose ) const;

        SIXTRL_HOST_FN config_id_t configId(
            purpose_t const purpose ) const;

        SIXTRL_HOST_FN bool hasKey( purpose_t const purpose ) const;
        SIXTRL_HOST_FN key_t const* ptrKey( purpose_t const purpose ) const;
        SIXTRL_HOST_FN key_t key( purpose_t const purpose ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool hasConfigId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN config_id_t configId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;


        SIXTRL_HOST_FN bool hasKey(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN key_t const* ptrKey(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN key_t const& key(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const;

        /* ----------------------------------------------------------------- */

        key_t const& currentKey() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        key_t const& currentKey(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool requires( purpose_t const purpose ) const;
        SIXTRL_HOST_FN bool hasKernel( purpose_t const purpose ) const;
        SIXTRL_HOST_FN bool hasKernel( key_t const& SIXTRL_RESTRICT_REF ) const;
        SIXTRL_HOST_FN bool hasAllKernels() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool requires( lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasKernel(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasKernel(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasAllKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t addPurpose( purpose_t const purpose );
        SIXTRL_HOST_FN status_t removePurpose( purpose_t const purpose );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN status_t addPurpose(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t removePurpose(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canSwitchKernel(
            key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN status_t switchKernel(
            key_t const& SIXTRL_RESTRICT_REF key,
            bool const pin_configuration = false );

        SIXTRL_HOST_FN bool canUpdateConfig( purpose_t const purpose );
        SIXTRL_HOST_FN status_t updateConfig( purpose_t const purpose );
        SIXTRL_HOST_FN bool readyToRunKernel( purpose_t const purpose );
        SIXTRL_HOST_FN status_t reset( purpose_t const purpose );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool canSwitchKernel(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN status_t switchKernel(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            bool const pin_configuration = false );

        SIXTRL_HOST_FN bool canUpdateConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const;

        SIXTRL_HOST_FN status_t updateConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose );

        SIXTRL_HOST_FN bool readyToRunKernel(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const;

        SIXTRL_HOST_FN status_t reset( lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canSwitchAllKernels(
            key_t& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN status_t switchAllKernels(
            key_t& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN bool anyConfigRequiresUpdate() const;

        SIXTRL_HOST_FN status_t updateAllConfigs();

        SIXTRL_HOST_FN bool readyToRunAllKernels() const;

        SIXTRL_HOST_FN status_t resetAll();

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool canSwitchAllKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t switchAllKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN bool anyConfigRequiresUpdate(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN status_t updateAllConfigs(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN bool readyToRunAllKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN status_t resetAll(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasKernelConfigStore()  const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_store_base_t*
            ptrKernelConfigStore() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_store_base_t const*
            ptrKernelConfigStore() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_store_base_t const&
            kernelConfigStore() const;

        SIXTRL_HOST_FN kernel_config_store_base_t&
            kernelConfigStore();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool checkLock( lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        protected:

        using purposes_to_data_map_t =
            std::unordered_map< purpose_t, requ_kernel_data_t >;

        using purposes_list_t = std::vector< purpose_t >;

        private:

        key_t                       m_current_key;
        purposes_to_data_map_t      m_purpose_to_data_map;
        purposes_list_t             m_purposes;
        ptr_kernel_config_store_t   m_ptr_kernel_config_store;
    };
}

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

typedef SIXTRL_CXX_NAMESPACE::RequiredKernels NS(RequiredKernels);

#else

typedef void NS(RequiredKernels);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* *****      inline and template member function implementions        ***** */
/* ************************************************************************* */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE RequiredKernelsData::key_t const&
    RequiredKernelsData::key() const SIXTRL_NOEXCEPT
    {
        return this->m_key;
    }

    SIXTRL_INLINE RequiredKernelsData::config_id_t
    RequiredKernelsData::kernelId() const SIXTRL_NOEXCEPT
    {
        return this->m_config_id;
    }

    SIXTRL_INLINE RequiredKernelsData::status_t
    RequiredKernelsData::reset() SIXTRL_NOEXCEPT
    {
        this->m_key.reset();
        this->m_config_id = SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_KERNEL_ID;
        this->m_ptr_config_base = nullptr;
        this->m_is_pinned = false;

        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
    }

    SIXTRL_INLINE RequiredKernelsData::status_t
    RequiredKernelsData::reset(
        RequiredKernelsData::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore& SIXTRL_RESTRICT_REF store )
    {
        using store_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        store_t::lock_t const lock( *store.lockable() );
        return this->reset( lock, key, store );
    }

    SIXTRL_INLINE bool RequiredKernelsData::isActive() const SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        return ( ( this->m_key.archId() != st::ARCHITECTURE_ILLEGAL ) &&
                 ( this->m_config_id != st::ARCH_ILLEGAL_KERNEL_ID ) );
    }

    SIXTRL_INLINE bool RequiredKernelsData::isPinned() const SIXTRL_NOEXCEPT
    {
        return ( ( this->isActive() ) && ( this->m_is_pinned ) );
    }

    SIXTRL_INLINE void RequiredKernelsData::markAsPinned(
        bool const is_pinned ) SIXTRL_NOEXCEPT
    {
        if( this->isActive() ) this->m_is_pinned = is_pinned;
    }

    SIXTRL_INLINE bool RequiredKernelsData::hasConfig() const SIXTRL_NOEXCEPT
    {
        return ( this->m_ptr_config_base != nullptr );
    }

    SIXTRL_INLINE RequiredKernelsData::config_base_t const*
    RequiredKernelsData::ptrConfigBase() const SIXTRL_NOEXCEPT
    {
        return this->m_ptr_config_base;
    }

    SIXTRL_INLINE RequiredKernelsData::config_base_t*
    RequiredKernelsData::ptrConfigBase() SIXTRL_NOEXCEPT
    {
        return this->m_ptr_config_base;
    }

    SIXTRL_INLINE bool RequiredKernelsData::isSyncWithStore(
        KernelConfigStore const& SIXTRL_RESTRICT_REF store ) const
    {
        using store_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        store_t::lock_t const lock( *store.lockable() );
        return this->isSyncWithStore( lock, store );
    }

    SIXTRL_INLINE RequiredKernelsData::status_t
    RequiredKernelsData::fetchConfig(
        KernelConfigStore& SIXTRL_RESTRICT_REF store )
    {
        using store_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        store_t::lock_t const lock( *store.lockable() );
        return this->fetchConfig( lock, store );
    }

    /* ===================================================================== */

    template< typename PurposeIter >
    RequiredKernels::RequiredKernels(
        ptr_kernel_config_store_base_t& SIXTRL_RESTRICT_REF ptr_conf_store,
        PurposeIter purposes_it, PurposeIter purposes_end ) :
        m_purpose_to_data_map(), m_purposes(),
        m_ptr_kernel_config_store( ptr_conf_store )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::RequiredKernels;

        if( std::distance( purposes_it, end ) > std::ptrdiff_t{ 0 } )
        {
            _this_t::status_t status = st::ARCH_STATUS_SUCCESS;
            _this_t::lock_t const lock( *this->lockable() );

            for( ; purposes_it != end ; ++purposes_it )
            {
                if( *purpose_it == _this_t::UNSPECIFIED_PUPRPOSE )
                {
                    continue;
                }

                if( !this->requires( lock, *puporses_it ) )
                {
                    status = this->addPurpose( lock, *purposes_it );

                    if( status != st::ARCH_STATUS_SUCCESS )
                    {
                        break;
                    }
                }
            }

            if( status != st::ARCH_STATUS_SUCCESS )
            {
                throw std::runtime_error(
                    "unable to init RequiredKernels instance from purposes list" );
            }
        }
    }

    SIXTRL_HOST_FN bool RequiredKernels::hasConfig(
        RequiredKernels::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        bool has_config = false;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            has_config = this->hasConfig( lock, purpose );
        }

        return has_config;
    }

    SIXTRL_INLINE RequiredKernels::config_base_t const*
    RequiredKernels::ptrConfigBase(
        RequiredKernels::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        _this_t::config_base_t const* ptr_config = nullptr;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            ptr_config = this->ptrConfigBase( lock, purpose );
        }

        return ptr_config;
    }

    SIXTRL_INLINE RequiredKernels::config_base_t*
    RequiredKernels::ptrConfigBase(
        RequiredKernels::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        _this_t::config_base_t* ptr_config = nullptr;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            ptr_config = this->ptrConfigBase( lock, purpose );
        }

        return ptr_config;
    }

    SIXTRL_INLINE RequiredKernels::status_t
    RequiredKernels::fetchConfig(
        RequiredKernels::purpose_t const purpose )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::RequiredKernels;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            status = this->fetchConfig( lock, purpose );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE RequiredKernels::config_id_t
    RequiredKernels::requiredKernelConfigId(
        RequiredKernels::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        _this_t::config_id_t config_id = _this_t::ILLEGAL_KERNEL_ID;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            config_id = this->requiredKernelConfigId( lock, purpose );
        }

        return config_id;
    }

    SIXTRL_INLINE RequiredKernels::key_t const*
    RequiredKernels::ptrRequiredKernelConfigKey(
        RequiredKernels::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        _this_t::key_t const* ptr_key = nullptr;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            ptr_key = this->ptrRequiredKernelConfigKey( lock, purpose );
        }

        return ptr_key;
    }

    SIXTRL_INLINE RequiredKernels::key_t
    RequiredKernels::requiredKernelConfigKey(
        RequiredKernels::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        _this_t::key_t const* ptr_key = nullptr;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t lock( *this->lockable() );
            ptr_key = this->ptrRequiredKernelConfigKey( lock, purpose );

            if( ptr_key != nullptr ) return *ptr_key;
        }

        return _this_t::key_t{};
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE RequiredKernels::size_type
    RequiredKernels::numPurposes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        _this_t::size_type num_purposes = _this_t::size_type{ 0 };

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            num_purposes = this->numPurposes( lock );
        }

        return num_purposes;
    }

    SIXTRL_INLINE RequiredKernels::purpose_t const*
    RequiredKernels::purposesBegin() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        _this_t::purpose_t const* begin = nullptr;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            begin = this->purposesBegin( lock );
        }

        return begin;
    }

    SIXTRL_INLINE RequiredKernels::purpose_t const*
    RequiredKernels::purposesEnd() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        _this_t::purpose_t const* end_ptr = nullptr;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            end_ptr = this->purposesEnd( lock );
        }

        return end_ptr;
    }

    /* ----------------------------------------------------------------- */

    RequiredKernels::key_t const& RequiredKernels::currentKey() const
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->hasKernelConfigStore() )
        {
            throw std::runtime_error(
                "no kernel config store available -> unable to lock" );
        }

        _this_t::lock_t const lock( *this->lockable() );
        return this->currentKey( lock );
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE bool RequiredKernels::requires(
        RequiredKernels::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        bool requires_purpose = false;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            requires_purpose = this->requires( lock, purpose );
        }

        return requires_purpose;
    }

    SIXTRL_INLINE bool RequiredKernels::hasRequiredKernel(
        RequiredKernels::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        bool has_required_kernel = false;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            has_required_kernel = this->hasRequiredKernel( lock, purpose );
        }

        return has_required_kernel;
    }

    SIXTRL_INLINE bool RequiredKernels::hasRequiredKernel(
        RequiredKernels::key_t const& SIXTRL_RESTRICT_REF key ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        bool has_required_kernel = false;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            has_required_kernel = this->hasRequiredKernel( lock, key );
        }

        return has_required_kernel;
    }

    SIXTRL_INLINE bool RequiredKernels::hasAllRequiredKernels() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        bool has_all_required_kernels = false;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            has_all_required_kernels = this->hasAllRequiredKernels( lock );
        }

        return has_all_required_kernels;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE RequiredKernels::status_t
    RequiredKernels::addRequiredPurpose(
        RequiredKernels::purpose_t const purpose )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::RequiredKernels;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            status = this->addRequiredPurpose( lock, purpose );
        }

        return status;
    }

    SIXTRL_INLINE RequiredKernels::status_t
    RequiredKernels::removeRequiredPurpose(
        RequiredKernels::purpose_t const purpose )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::RequiredKernels;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            status = this->removeRequiredPurpose( lock, purpose );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool RequiredKernels::canSwitchKernel(
        RequiredKernels::key_t const& SIXTRL_RESTRICT_REF key ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        bool can_switch_kernel = false;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            can_switch_kernel = this->canSwitchKernel( lock, key );
        }

        return can_switch_kernel;
    }

    SIXTRL_INLINE RequiredKernels::status_t
    RequiredKernels::switchRequiredKernel(
        RequiredKernels::key_t const& SIXTRL_RESTRICT_REF key,
        bool const pin_configuration )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::RequiredKernels;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            status = this->switchRequiredKernel( lock, key, pin_configuration );
        }

        return status;
    }

    SIXTRL_INLINE RequiredKernels::status_t
    RequiredKernels::resetRequiredKernel(
        RequiredKernels::purpose_t const purpose )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::RequiredKernels;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            status = this->resetRequiredKernel( lock, purpose );
        }

        return status;
    }

    SIXTRL_INLINE RequiredKernels::status_t
    RequiredKernels::resetRequiredKernel(
        RequiredKernels::key_t const& SIXTRL_RESTRICT_REF key )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::RequiredKernels;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            status = this->resetRequiredKernel( lock, key );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool RequiredKernels::canSwitchAllKernels(
        RequiredKernels::key_t& SIXTRL_RESTRICT_REF key ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        bool can_switch_all_kernels = false;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            can_switch_all_kernels = this->canSwitchAllKernels( lock, key );
        }

        return can_switch_all_kernels;
    }

    SIXTRL_INLINE RequiredKernels::status_t RequiredKernels::switchAllKernels(
        RequiredKernels::key_t& SIXTRL_RESTRICT_REF key )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::RequiredKernels;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            status = this->switchAllKernels( lock, key );
        }

        return status;
    }

    SIXTRL_INLINE RequiredKernels::status_t RequiredKernels::resetAllKernels()
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::RequiredKernels;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::lock_t const lock( *this->lockable() );
            status = this->resetAllKernels( lock );
        }

        return status;
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE bool
    RequiredKernels::hasKernelConfigStore() const SIXTRL_NOEXCEPT
    {
        return ( this->m_ptr_kernel_config_store != nullptr );
    }

    SIXTRL_INLINE bool
    RequiredKernels::ownsKernelConfigStore() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_kernel_config_store.get() == nullptr ) ||
            ( this->m_kernel_config_store.get() ==
              this->m_ptr_kernel_config_store ) );

        return ( this->m_kernel_config_store.get() != nullptr );
    }

    SIXTRL_INLINE RequiredKernels::kernel_config_store_base_t*
        RequiredKernels::ptrKernelConfigStore() SIXTRL_NOEXCEPT
    {
        return this->m_ptr_kernel_config_store;
    }

    SIXTRL_INLINE RequiredKernels::kernel_config_store_base_t const*
        RequiredKernels::ptrKernelConfigStore() const SIXTRL_NOEXCEPT
    {
        return this->m_ptr_kernel_config_store;
    }

    SIXTRL_INLINE RequiredKernels::kernel_config_store_base_t const&
        RequiredKernels::kernelConfigStore() const
    {
        if( this->ptrKernelConfigStore() != nullptr )
        {
            throw std::runtime_error( "no kernel config store available" );
        }

        return *this->ptrKernelConfigStore();
    }

    SIXTRL_INLINE RequiredKernels::kernel_config_store_base_t&
        RequiredKernels::kernelConfigStore()
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::RequiredKernels;
        return const_cast< _this_t::kernel_config_store_base_t& >(
            static_cast< _this_t const& >( *this ).kernelConfigStore() );
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE bool RequiredKernels::checkLock(
        RequiredKernels::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->lockable() != nullptr ) &&
                 ( lock.owns_lock() ) &&
                 ( lock.mutex() == this->lockable() ) );
    }

    SIXTRL_INLINE RequiredKernels::lockable_t*
    RequiredKernels::lockable() const SIXTRL_NOEXCEPT
    {
        return ( this->hasKernelConfigStore() )
            ? this->ptrKernelConfigStore()->lockable() : nullptr;
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_REQUIRED_KERNELS_LIST_CXX_HPP__ */

/* end: sixtracklib/common/control/required_kernels_list.hpp */
