#include "sixtracklib/common/control/required_kernels_list.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    using _data_t = st::KernelSet;

    KernelSet::KernelSet(
        KernelSet::key_t const& SIXTRL_RESTRICT key,
        KernelSet::config_id_t const kernel_config_id,
        KernelSet::config_base_t* SIXTRL_RESTRICT ptr_config_base,
        bool const is_pinned ) :
        m_key( key ), m_config_id( kernel_config_id ),
        m_ptr_config_base( ptr_config_base ), m_is_pinned( is_pinned )
    {

    }

    KernelSet::status_t KernelSet::reset(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSet::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore& SIXTRL_RESTRICT_REF store )
    {
        _data_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( store.checkLock( lock ) ) &&
            ( store.hasKernel( lock, key ) ) )
        {
            this->m_key = key;
            this->m_config_id = store.kernelId( lock, key );
            this->m_ptr_config_base = store.ptrKernelConfigBase(
                lock, this->m_config_id );
            this->m_is_pinned = false;

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    bool KernelSet::isSyncWithStore(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore const& SIXTRL_RESTRICT_REF store ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->isActive() ) &&
                 ( this->m_config_id != _data_t::ILLEGAL_KERNEL_ID ) &&
                 ( this->m_ptr_config_base != nullptr ) &&
                 ( store.checkLock( lock ) ) &&
                 ( this->m_config_id == store.kernelId( lock, this->m_key ) ) &&
                 ( this->m_ptr_config_base == store.ptrKernelConfigBase(
                    lock, this->m_config_id ) ) );
    }

    KernelSet::status_t KernelSet::fetchConfig(
            KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
            KernelConfigStore& SIXTRL_RESTRICT_REF store ) SIXTRL_NOEXCEPT
    {
        _data_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->isActive() ) && ( store.checkLock( lock ) ) &&
            ( store.hasKernel( lock, this->m_key ) ) &&
            ( store.kernelId( lock, this->m_key ) == this->m_config_id ) )
        {
            this->m_ptr_config_base =
                store.ptrKernelConfigBase( lock, this->m_config_id );

            if( this->m_ptr_config_base != nullptr )
            {
                status  = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* ===================================================================== */

    using _this_t = st::RequiredKernels;

    RequiredKernels::size_type RequiredKernels::numPurposes(
            RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT
    {
        _this_t::size_type const num_purposes = ( this->checkLock( lock ) )
            ? this->m_purposes.size() : _this_t::size_type{ 0 };

        SIXTRL_ASSERT( ( !this->checkLock( lock ) ) ||
            ( num_purposes == this->m_purposes.size() ) );

        return num_purposes;
    }

    RequiredKernels::purpose_t const*
    RequiredKernels::purposesBegin( RequiredKernels::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) ) ? this->m_purposes.data() : nullptr;
    }

    RequiredKernels::purpose_t const*
    RequiredKernels::purposesEnd( RequiredKernels::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        _this_t::purpose_t const* end_ptr = nullptr;

        if( this->checkLock( lock ) )
        {
            end_ptr = this->m_purposes.data();

            if( end_ptr != nullptr )
            {
                std::advance( end_ptr, this->m_purposes.size() );
            }
        }

        return end_ptr;
    }

    /* --------------------------------------------------------------------- */

    bool RequiredKernels::hasConfig(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        bool has_config = false;

        if( ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->requires( lock, purpose ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = this->m_purpose_to_data_map.find( purpose );

            if( ( it != this->m_purpose_to_data_map.end() ) &&
                ( it->second.isActive() ) &&
                ( it->second.key().purpose() == purpose ) &&
                ( it->second.hasConfig() ) )
            {
                has_config = true;
            }
        }

        return has_config;
    }

    RequiredKernels::config_base_t const* RequiredKernels::ptrConfigBase(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        RequiredKernels::config_base_t const* ptr_config = nullptr;

        if( ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->requires( lock, purpose ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = this->m_purpose_to_data_map.find( purpose );

            if( ( it != this->m_purpose_to_data_map.end() ) &&
                ( it->second.isActive() ) &&
                ( it->second.key().purpose() == purpose ) &&
                ( it->second.hasConfig() ) )
            {
                ptr_config = it->second.ptrConfigBase();
            }
        }

        return ptr_config;
    }

    RequiredKernels::config_base_t* RequiredKernels::ptrConfigBase(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? const_cast< _this_t::config_base_t* >( static_cast<
                _this_t const& >( *this ).ptrConfigBase( lock, purpose ) )
            : nullptr;
    }

    RequiredKernels::status_t RequiredKernels::fetchConfig(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::purpose_t const purpose )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->hasKernelConfigStore() ) &&
            ( this->requires( lock, purpose ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = this->m_purpose_to_data_map.find( purpose );

            if( it != this->m_purpose_to_data_map.end() )
            {
                status = it->second.fetchConfig(
                    lock, *this->ptrKernelConfigStore() );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    RequiredKernels::config_id_t
    RequiredKernels::requiredKernelConfigId(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        _this_t::config_id_t config_id = _this_t::ILLEGAL_KERNEL_ID;

        if( ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_purpose_to_data_map.find( purpose );

            if( ( it != this->m_purpose_to_data_map.end() ) &&
                ( it->second.isActive() ) )
            {
                config_id = it->second.kernelId();
            }
        }

        return config_id;
    }

    RequiredKernels::key_t const* RequiredKernels::ptrRequiredKernelConfigKey(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        _this_t::key_t const* ptr_key = nullptr;

        if( ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_purpose_to_data_map.find( purpose );

            if( ( it != this->m_purpose_to_data_map.end() ) &&
                ( it->second.isActive() ) )
            {
                ptr_key = &it->second.key();
            }
        }

        return ptr_key;
    }

    RequiredKernels::key_t const&
    RequiredKernels::requiredKernelConfigKey(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::purpose_t const purpose ) const
    {
        if( !this->checkLock( lock ) )
        {
            throw std::runtime_error( "not properly lock handle provided" );
        }

        _this_t::key_t const* ptr_key =
            this->ptrRequiredKernelConfigKey( lock, purpose );

        if( ptr_key == nullptr )
        {
            throw std::runtime_error( "illegal required kernel key" );
        }

        return *ptr_key;
    }

    /* --------------------------------------------------------------------- */

    RequiredKernels::key_t const& RequiredKernels::currentKey(
        RequiredKernels::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        ( void )lock;

        return this->m_current_key;
    }

    /* --------------------------------------------------------------------- */

    bool RequiredKernels::requires(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        return ( ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
                 ( this->checkLock( lock ) ) &&
                 ( this->m_purpose_to_data_map.find( purpose ) !=
                   this->m_purpose_to_data_map.end() ) );
    }

    bool RequiredKernels::hasRequiredKernel(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        bool has_required_kernel = false;

        if( ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->requires( lock, purpose ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = this->m_purpose_to_data_map.find( purpose );

            has_required_kernel = (
                ( it != this->m_purpose_to_data_map.end() ) &&
                ( it->second.isActive() ) &&
                ( it->second.key().purpose() == purpose ) );
        }

        return has_required_kernel;
    }

    bool RequiredKernels::hasRequiredKernel(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::key_t const& SIXTRL_RESTRICT_REF
            key ) const SIXTRL_NOEXCEPT
    {
        bool has_required_kernel = false;

        if( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( key.purpose() != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->requires( lock, key.purpose() ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = this->m_purpose_to_data_map.find( key.purpose() );

            has_required_kernel = (
                ( it != this->m_purpose_to_data_map.end() ) &&
                ( it->second.isActive() ) &&
                ( it->second.key() == key ) );
        }

        return has_required_kernel;
    }

    bool RequiredKernels::hasAllRequiredKernels(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF
            lock ) const SIXTRL_NOEXCEPT
    {
        bool has_all_required_kernels = false;

        if( (  this->checkLock( lock ) ) &&
            ( !this->m_purposes.empty() ) )
        {
            has_all_required_kernels = true;

            for( auto const purpose : this->m_purposes )
            {
                SIXTRL_ASSERT( this->requires( lock, purpose ) );

                has_all_required_kernels &=
                    this->hasRequiredKernel( lock, purpose );
            }
        }

        return has_all_required_kernels;
    }

    /* --------------------------------------------------------------------- */

    RequiredKernels::status_t RequiredKernels::addRequiredPurpose(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->checkLock( lock ) ) &&
            ( !this->requires( lock, purpose ) ) )
        {
            SIXTRL_ASSERT( this->m_purpose_to_data_map.find( purpose ) ==
                           this->m_purpose_to_data_map.end() );

            SIXTRL_ASSERT( std::is_sorted( this->m_purposes.begin(),
                                           this->m_purposes.end() ) );

            SIXTRL_ASSERT( !std::binary_search(
                this->m_purposes.begin(), this->m_purposes.end(), purpose ) );

            auto res = this->m_purpose_to_data_map.emplace( std::make_pair(
                purpose, _this_t::key_t{} ) );

            if( res.second )
            {
                bool const do_sort = ( this->m_purposes.back() > purpose );

                this->m_purposes.push_back( purpose );

                if( do_sort )
                {
                    std::sort( this->m_purposes.begin(),
                               this->m_purposes.end() );
                }

                if( this->m_purposes.size() ==
                    this->m_purpose_to_data_map.size() )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }

                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( std::is_sorted( this->m_purposes.begin(),
                                      this->m_purposes.end() ) ) );
            }
        }

        return status;
    }

    RequiredKernels::status_t RequiredKernels::removeRequiredPurpose(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->requires( lock, purpose ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            SIXTRL_ASSERT( this->m_purpose_to_data_map.find( purpose ) !=
                           this->m_purpose_to_data_map.end() );

            auto it = this->m_purpose_to_data_map.find( purpose );

            auto range = std::equal_range( this->m_purposes.begin(),
                this->m_purposes.end(), purpose );

            if( ( it != this->m_purpose_to_data_map.end() ) &&
                ( range.first != this->m_purposes.end() ) &&
                ( range.second != range.first ) )
            {
                this->m_purpose_to_data_map.erase( it );
                this->m_purposes.erase( range.first, range.second );

                std::sort( this->m_purposes.begin(), this->m_purposes.end() );

                if( this->m_purposes.size() ==
                    this->m_purpose_to_data_map.size() )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool RequiredKernels::canSwitchKernel(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::key_t const& SIXTRL_RESTRICT_REF key ) const
    {
        bool can_switch_kernel = false;

        if( ( key.archId()  != _this_t::ARCH_ILLEGAL ) &&
            ( key.purpose() != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->hasKernelConfigStore() ) &&
            ( this->requires( lock, key.purpose() ) ) &&
            ( !this->hasRequiredKernel( lock, key ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            can_switch_kernel =
                this->ptrKernelConfigStore()->hasKernel( lock, key );

            if( !can_switch_kernel )
            {
                can_switch_kernel = this->ptrKernelConfigStore(
                    )->hasDefaultInitKernelConfigParameters( lock, key );
            }
        }

        return can_switch_kernel;
    }

    RequiredKernels::status_t RequiredKernels::switchRequiredKernel(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::key_t const& SIXTRL_RESTRICT_REF key,
        bool const pin_configuration )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _this_t::purpose_t const purpose = key.purpose();

        if( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->hasKernelConfigStore() ) &&
            ( this->requires( lock, purpose ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = this->m_purpose_to_data_map.find( purpose );

            SIXTRL_ASSERT( it != this->m_purpose_to_data_map.end() );

            if( ( !this->ptrKernelConfigStore()->hasKernel( lock, key ) ) &&
                ( this->ptrKernelConfigStore()->hasDefaultInitKernelConfigParameters(
                    lock, key ) ) )
            {
                if( _this_t::ILLEGAL_KERNEL_ID ==
                    this->ptrKernelConfigStore()->initKernelConfig( lock, key ) )
                {
                    return status;
                }
            }

            status = it->second.reset(
                lock, key, *this->ptrKernelConfigStore() );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( pin_configuration ) )
            {
                it->second.markAsPinned( pin_configuration );
            }
        }

        return status;
    }

    RequiredKernels::status_t RequiredKernels::resetRequiredKernel(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::purpose_t const purpose )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->hasKernelConfigStore() ) &&
            ( this->requires( lock, purpose ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = this->m_purpose_to_data_map.find( purpose );

            if( it != this->m_purpose_to_data_map.end() )
            {
                status = it->second.reset();
            }
        }

        return status;
    }

    RequiredKernels::status_t RequiredKernels::resetRequiredKernel(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::key_t const& SIXTRL_RESTRICT_REF key )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( key.purpose() != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->hasKernelConfigStore() ) &&
            ( this->requires( lock, key.purpose() ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto it = this->m_purpose_to_data_map.find( key.purpose() );

            if( ( it != this->m_purpose_to_data_map.end() ) &&
                ( it->second.key() == key ) )
            {
                status = it->second.reset();
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool RequiredKernels::canSwitchAllKernels(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::key_t& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT
    {
        bool can_switch_all_required_kernels = false;

        _this_t::purpose_t const initial_purpose = key.purpose();

        if( (  this->checkLock( lock ) ) &&
            ( !this->m_purposes.empty() ) )
        {
            can_switch_all_required_kernels = true;

            for( auto const purpose : this->m_purposes )
            {
                SIXTRL_ASSERT( this->requires( lock, purpose ) );

                key.setPurpose( purpose );

                can_switch_all_required_kernels &=
                    this->canSwitchKernel( lock, key );
            }

            key.setPurpose( initial_purpose );
        }

        return can_switch_all_required_kernels;
    }

    RequiredKernels::status_t RequiredKernels::switchAllKernels(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock,
        RequiredKernels::key_t& SIXTRL_RESTRICT_REF key )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _this_t::purpose_t const initial_purpose = key.purpose();

        if( (  this->checkLock( lock ) ) &&
            ( !this->m_purposes.empty() ) )
        {
            for( auto const purpose : this->m_purposes )
            {
                SIXTRL_ASSERT( this->requires( lock, purpose ) );

                key.setPurpose( purpose );

                status = this->switchRequiredKernel( lock, key );

                if( status != st::ARCH_STATUS_SUCCESS )
                {
                    break;
                }
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                key.setPurpose( _this_t::UNSPECIFIED_PUPRPOSE );
                this->m_current_key = key;
            }

            key.setPurpose( initial_purpose );
        }

        return status;
    }

    RequiredKernels::status_t RequiredKernels::resetAllKernels(
        RequiredKernels::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( (  this->checkLock( lock ) ) &&
            ( !this->m_purposes.empty() ) )
        {
            for( auto const purpose : this->m_purposes )
            {
                SIXTRL_ASSERT( this->requires( lock, purpose ) );

                status = this->resetRequiredKernel( lock, purpose );

                if( status != st::ARCH_STATUS_SUCCESS )
                {
                    break;
                }
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->m_current_key.reset();
            }
        }

        return status;
    }
}

/* end: sixtracklib/common/control/required_kernels_list.cpp */
