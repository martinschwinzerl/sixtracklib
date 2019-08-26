#include "sixtracklib/common/control/kernel_set.hpp"
#include "sixtracklib/common/control/kernel_config_store.hpp"

#include <exception>

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    using _item_t     = SIXTRL_CXX_NAMESPACE::KernelSetItemData;
    using _set_t      = SIXTRL_CXX_NAMESPACE::KernelSetBase;
    using _ctrl_set_t = SIXTRL_CXX_NAMESPACE::ControllerKernelSetBase;

    /* ********************************************************************* */
    /* KernelSetItemData: */

    constexpr _item_t::arch_id_t            _item_t::ARCH_ILLEGAL;
    constexpr _item_t::arch_id_t            _item_t::ARCH_NONE;
    constexpr _item_t::kernel_config_id_t   _item_t::ILLEGAL_KERNEL_CONFIG_ID;
    constexpr _item_t::purpose_t            _item_t::UNSPECIFIED_PUPRPOSE;
    constexpr _item_t::status_t             _item_t::RESET_GENERAL_FAILURE;
    constexpr _item_t::status_t             _item_t::RESET_SUCCESS_SYNC;
    constexpr _item_t::status_t             _item_t::RESET_SUCCESS_UPDATED;


    KernelSetItemData::KernelSetItemData(
        _item_t::kernel_config_id_t const kernel_config_id,
        _item_t::kernel_config_base_t* SIXTRL_RESTRICT ptr_config_base,
        _item_t::kernel_config_key_t const& SIXTRL_RESTRICT key,
        bool const is_pinned ) :
        m_config_key( key ), m_ptr_config( ptr_config_base ),
        m_config_id( kernel_config_id ), m_pinned( is_pinned )
    {

    }

    _item_t::status_t KernelSetItemData::reset(
        _item_t::kernel_config_id_t const kernel_config_id,
        _item_t::kernel_config_base_t* SIXTRL_RESTRICT ptr_kernel_config,
        _item_t::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        bool const is_pinned_flag ) SIXTRL_NOEXCEPT
    {
        _item_t::status_t status = _item_t::RESET_GENERAL_FAILURE;

        if( ( kernel_config_id != _item_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( key.valid() ) && ( ptr_kernel_config != nullptr ) &&
            ( ptr_kernel_config->isArchCompatibleWith( key.archId() ) ) )
        {
            bool const has_been_updated = !( this->isEqualTo( kernel_config_id,
                ptr_kernel_config, key, is_pinned_flag ) );

            this->m_config_id  = kernel_config_id;
            this->m_ptr_config = ptr_kernel_config;
            this->m_config_key = key;
            this->m_pinned     = is_pinned_flag;

            status = ( has_been_updated )
                ? _item_t::RESET_SUCCESS_UPDATED : _item_t::RESET_SUCCESS_SYNC;
        }
        else if( ( ( kernel_config_id == _item_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                   ( ptr_kernel_config == nullptr ) ) )
        {
            bool const has_been_updated = !(
                this->isEqualTo( kernel_config_id, ptr_kernel_config ) );

            this->m_config_id = _item_t::ILLEGAL_KERNEL_CONFIG_ID;
            this->m_ptr_config = nullptr;
            this->m_pinned = false;
            status = this->m_config_key.reset();

            if( ( status == _item_t::RESET_SUCCESS_SYNC ) &&
                ( has_been_updated ) )
            {
                status = _item_t::RESET_SUCCESS_UPDATED;
            }
        }

        return status;
    }

    /* ********************************************************************* */
    /* KernelSetBase: */

    constexpr _set_t::arch_id_t             _set_t::ARCH_ILLEGAL;
    constexpr _set_t::arch_id_t             _set_t::ARCH_NONE;
    constexpr _set_t::kernel_config_id_t    _set_t::ILLEGAL_KERNEL_CONFIG_ID;
    constexpr _set_t::purpose_t             _set_t::UNSPECIFIED_PUPRPOSE;
    constexpr _set_t::sync_id_value_t       _set_t::ILLEGAL_SYNC_ID_VALUE;
    constexpr _set_t::sync_id_value_t       _set_t::LAST_LEGAL_SYNC_ID_VALUE;

    constexpr _set_t::purpose_t             _set_t::CONTROLLER_PURPOSES[];
    constexpr _set_t::purpose_t             _set_t::TRACK_JOB_PURPOSES[];

    KernelSetBase::KernelSetBase(
        _set_t::arch_id_t const arch_id,
        _set_t::kernel_config_store_base_t& SIXTRL_RESTRICT_REF store,
        _set_t::size_type const num_purposes,
        _set_t::purpose_t const* SIXTRL_RESTRICT purposes_begin ) :
        st::ArchInfo( arch_id ),
        m_current_key( arch_id ), m_purpose_to_data_map(),
        m_kernel_id_to_purposes_map(),
        m_purposes(), m_kernel_config_store( store ),
        m_kernel_op_flags( st::KERNEL_OP_FLAGS_NONE ),
        m_sync_id( KernelSetBase::sync_id_value_t{ 0 } ),
        m_kernel_set_id( KernelSetBase::ILLEGAL_KERNEL_SET_ID ),
        m_is_for_controllers( false ), m_is_for_track_jobs( false )
    {
        if( this->addPurposes( num_purposes, purposes_begin ) !=
            SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
                throw std::runtime_error( "unable to init KernelSet" );
    }

    KernelSetBase::KernelSetBase(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::arch_id_t const arch_id,
        _set_t::kernel_config_store_base_t& SIXTRL_RESTRICT_REF store,
        _set_t::size_type const num_purposes,
        _set_t::purpose_t const* SIXTRL_RESTRICT purposes_begin ) :
        st::ArchInfo( arch_id ),
        m_current_key( arch_id  ), m_purpose_to_data_map(),
        m_kernel_id_to_purposes_map(),
        m_purposes(), m_kernel_config_store( store ),
        m_kernel_op_flags( st::KERNEL_OP_FLAGS_NONE ),
        m_sync_id( KernelSetBase::sync_id_value_t{ 0 } ),
        m_kernel_set_id( KernelSetBase::ILLEGAL_KERNEL_SET_ID ),
        m_is_for_controllers( false ), m_is_for_track_jobs( false )
    {
        store.checkLockAndThrowOnError( lock );

        if( this->addPurposes( lock, num_purposes, purposes_begin ) !=
            SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
                throw std::runtime_error( "unable to init KernelSet" );
    }

    KernelSetBase::~KernelSetBase()
    {
        /* WARNING: the creation of a lock handle may throw, but there is no
         *          way around that. If an exception is thrown, we try to
         *          brute force the clean-up and hope for the best */
        try
        {
            _set_t::lock_t const lock( *this->lockable() );
            this->reset( lock );
        }
        catch( std::system_error const& e )
        {
            /* We should hopefully *never* end up here */
            this->doClearWithoutLocking();
            /* Crossing fingers that everything is cleaned-up! */
        };
    }

    /* --------------------------------------------------------------------- */

    _set_t::size_type KernelSetBase::numPurposes(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::kernel_config_id_t const config_id ) const SIXTRL_NOEXCEPT
    {
        _set_t::size_type num_purposes = _set_t::size_type{ 0 };

        if( ( config_id == _set_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_kernel_id_to_purposes_map.find( config_id );

            if( ( it != this->m_kernel_id_to_purposes_map.end() ) &&
                ( !it->second.empty() ) )
            {
                num_purposes = it->second.size();
            }
        }

        return num_purposes;
    }

    _set_t::size_type _set_t::numPinnedPurposes(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        _set_t::size_type num_pinned_purposes = _set_t::size_type{ 0 };

        if( ( this->checkLock( lock ) ) &&
            ( !this->m_purposes.empty() ) )
        {
            SIXTRL_ASSERT( this->m_purposes.size() ==
                this->m_purpose_to_data_map.size() );

            for( auto const purpose : this->m_purposes )
            {
                auto it = this->m_purpose_to_data_map.find( purpose );

                if( ( it != this->m_purpose_to_data_map.end() ) &&
                    ( it->second.pinned() ) )
                {
                    ++num_pinned_purposes;
                }
            }
        }

        return num_pinned_purposes;
    }

    /* --------------------------------------------------------------------- */

    _set_t::kernel_config_base_t const* _set_t::ptrKernelConfigBase(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        auto it = this->doFindItemIterByPurpose( lock, purpose );

        if( it != this->m_purpose_to_data_map.end() )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            return it->second.ptrKernelConfigBase();
        }

        return nullptr;
    }

    /* --------------------------------------------------------------------- */

    KernelSetBase::kernel_config_id_t KernelSetBase::kernelConfigId(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        auto it = this->doFindItemIterByPurpose( lock, purpose );

        if( it != this->m_purpose_to_data_map.end() )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            return it->second.kernelConfigId();
        }

        return _set_t::ILLEGAL_KERNEL_CONFIG_ID;
    }

    _set_t::kernel_config_key_t const*
    KernelSetBase::ptrKernelConfigKey(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        auto it = this->doFindItemIterByPurpose( lock, purpose );

        if( it != this->m_purpose_to_data_map.end() )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            return &it->second.kernelConfigKey();
        }

        return nullptr;
    }

    _set_t::kernel_config_key_t const& KernelSetBase::kernelConfigKey(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::purpose_t const purpose ) const
    {
        auto it = this->doFindItemIterByPurpose( lock, purpose );

        if( it == this->m_purpose_to_data_map.end() )
        {
            throw std::runtime_error(
                "unable to retrieve key from KernelSet item" );
        }

        SIXTRL_ASSERT( this->checkLock( lock ) );
        return it->second.kernelConfigKey();
    }

    /* --------------------------------------------------------------------- */

    bool KernelSetBase::hasKernelConfigId(
            _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
            _set_t::kernel_config_id_t const id ) const SIXTRL_NOEXCEPT
    {
        bool has_kernel_config_id = false;

        if( ( id != _set_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_kernel_id_to_purposes_map.find( id );

            if( (  it != this->m_kernel_id_to_purposes_map.end() ) &&
                ( !it->second.empty() ) )
            {
                has_kernel_config_id = true;

                #if !defined( _NDEBUG )
                auto purpose_it  = it->second.begin();
                auto purpose_end = it->second.end();

                for( ; purpose_it != purpose_end ; ++purpose_it )
                {
                    _set_t::purpose_t const purpose = *purpose_it;

                    if( purpose == _set_t::UNSPECIFIED_PUPRPOSE )
                    {
                       has_kernel_config_id = false;
                       break;
                    }

                    auto find_it = this->m_purpose_to_data_map.find( purpose );

                    if( (  find_it == this->m_purpose_to_data_map.end() ) ||
                        ( !find_it->second.available() ) ||
                        (  find_it->second.kernelConfigId() != id ) )
                    {
                        has_kernel_config_id = false;
                        break;
                    }
                }
                #endif /* !defined( _NDEBUG ) */
            }
        }

        return has_kernel_config_id;
    }

    bool KernelSetBase::isPurposeAssociatedWithKernelConfigId(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::kernel_config_id_t const kernel_config_id,
        _set_t::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        bool is_purpose_associated = false;

        if( ( kernel_config_id != _set_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( this->requires( lock, purpose ) ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( purpose != _set_t::UNSPECIFIED_PUPRPOSE );

            auto kernel_it = this->m_kernel_id_to_purposes_map.find(
                kernel_config_id );

            auto purpose_it = this->m_purpose_to_data_map.find( purpose );

            if( ( purpose_it != this->m_purpose_to_data_map.end() ) &&
                ( purpose_it->second.kernelConfigId() == kernel_config_id ) &&
                ( purpose_it->second.available() ) &&
                (  kernel_it != this->m_kernel_id_to_purposes_map.end() ) &&
                ( !kernel_it->second.empty() ) &&
                (  std::lower_bound( kernel_it->second.begin(),
                        kernel_it->second.end(), purpose ) !=
                   kernel_it->second.end() ) )
            {
                is_purpose_associated = true;
            }
        }

        return is_purpose_associated;
    }

    /* --------------------------------------------------------------------- */

    _set_t::kernel_config_key_t const&
    KernelSetBase::currentKernelConfigKey( _set_t::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const
    {
        if( !this->checkLock( lock ) )
        {
            throw std::runtime_error(
                "passed not properly locked lock handle" );
        }

        return this->m_current_key;
    }

    /* --------------------------------------------------------------------- */

    bool KernelSetBase::available( _set_t::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        if( !this->checkLock( lock ) ) return false;

        SIXTRL_ASSERT( this->m_purpose_to_data_map.size() ==
                       this->m_purposes.size() );

        bool are_all_available = true;

        for( auto const purpose : this->m_purposes )
        {
            auto it = this->doFindItemIterByPurpose( lock, purpose );

            if( (  it == this->m_purpose_to_data_map.end() ) ||
                ( !it->second.available() ) )
            {
                are_all_available = false;
                break;
            }
        }

        return are_all_available;
    }

    /* --------------------------------------------------------------------- */

    bool KernelSetBase::canSwitchKernel(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const
    {
        bool is_available = false;

        if( this->requires( lock, key.purpose() ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            _set_t::kernel_config_id_t const kernel_config_id =
                this->kernelConfigStore().kernelId( lock, key );

            if( kernel_config_id != _set_t::ILLEGAL_KERNEL_CONFIG_ID )
            {
                is_available = ( this->kernelConfigStore().ptrKernelConfigBase(
                    lock, kernel_config_id ) != nullptr );
            }
            else
            {
                is_available = this->kernelConfigStore(
                    ).hasDefaultInitKernelConfigParameters( lock, key );
            }
        }

        return is_available;
    }

    bool KernelSetBase::canSwitchKernels(
            _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
            _set_t::kernel_config_key_t& SIXTRL_RESTRICT_REF key
        ) const SIXTRL_NOEXCEPT
    {
        if( !this->checkLock( lock ) ) return false;

        SIXTRL_ASSERT( this->m_purpose_to_data_map.size() ==
                       this->m_purposes.size() );

        bool are_all_available = !this->m_purposes.empty();

        _set_t::purpose_t const initial_purpose = key.purpose();

        for( auto const purpose : this->m_purposes )
        {
            auto it = this->doFindItemIterByPurpose( lock, purpose );

            if( it == this->m_purpose_to_data_map.end() )
            {
                are_all_available = false;
                break;
            }

            if( it->second.pinned() )
            {
                continue;
            }

            key.setPurpose( purpose );

            if( !this->canSwitchKernel( lock, key ) )
            {
                are_all_available = false;
                break;
            }
        }

        key.setPurpose( initial_purpose );

        return are_all_available;
    }

    /* --------------------------------------------------------------------- */

    _set_t::status_t KernelSetBase::switchKernel(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        bool const is_pinned_flag )
    {
        _set_t::status_t status =
            this->doSwitchKernel( lock, key, is_pinned_flag );

        if( status == _item_t::RESET_SUCCESS_UPDATED )
        {
            this->registerChange( lock );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _set_t::status_t KernelSetBase::switchKernels(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
    {
        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( !this->checkLock( lock ) ) return status;

        SIXTRL_ASSERT( this->m_purpose_to_data_map.size() ==
                       this->m_purposes.size() );

        _set_t::kernel_config_key_t const save_current_key = this->m_current_key;
        this->m_current_key = key;

        status = st::ARCH_STATUS_SUCCESS;
        bool has_been_updated = false;

        for( auto const purpose : this->m_purposes )
        {
            auto it = this->doFindItemIterByPurpose( lock, purpose );

            if( it == this->m_purpose_to_data_map.end() )
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( it->second.pinned() )
            {
                continue;
            }

            this->m_current_key.setPurpose( purpose );

            status = this->doSwitchKernel( lock, this->m_current_key, false );

            if( status == _item_t::RESET_SUCCESS_UPDATED )
            {
                has_been_updated = true;
                status = st::ARCH_STATUS_SUCCESS;
            }

            if( status != st::ARCH_STATUS_SUCCESS )
            {
                break;
            }
        }

        if( has_been_updated )
        {
            this->registerChange( lock );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            this->m_current_key.setPurpose( save_current_key.purpose() );
        }
        else
        {
            this->m_current_key = save_current_key;
            _set_t::status_t rollback_status = st::ARCH_STATUS_SUCCESS;

            for( auto const purpose : this->m_purposes )
            {
                auto it = this->doFindItemIterByPurpose( lock, purpose );

                if( ( it == this->m_purpose_to_data_map.end() ) ||
                    ( it->second.pinned() ) )
                {
                    continue;
                }

                this->m_current_key.setPurpose( purpose );

                rollback_status = this->doSwitchKernel(
                    lock, this->m_current_key, false );

                if( rollback_status == _item_t::RESET_SUCCESS_UPDATED )
                {
                    rollback_status = st::ARCH_STATUS_SUCCESS;
                }

                if( rollback_status != st::ARCH_STATUS_SUCCESS )
                {
                    break;
                }
            }

            if( rollback_status != st::ARCH_STATUS_SUCCESS )
            {
                throw std::runtime_error(
                    "unable to rollback KernelSet after failed kernel switch" );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    KernelSetBase::status_t KernelSetBase::updateKernelOpFlags(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _set_t::op_flags_t op_flags = st::KERNEL_OP_FLAGS_NONE;

        if( this->checkLock( lock ) )
        {
            if( this->isForControllers() )
            {
                op_flags |= this->doUpdateKernelOpFlagsForPurposes( lock,
                    &_set_t::CONTROLLER_PURPOSES[ 0 ],
                    &_set_t::CONTROLLER_PURPOSES[
                        _set_t::NUM_CONTROLLER_PURPOSES ],
                    st::KERNEL_OP_CTRL_HAS_REQUIRED_PURPOSES,
                    st::KERNEL_OP_CTRL_KERNELS_AVAILABLE,
                    st::KERNEL_OP_CTRL_KERNELS_READY );
            }

            if( this->isForTrackJobs() )
            {
                op_flags |= this->doUpdateKernelOpFlagsForPurposes( lock,
                    &_set_t::TRACK_JOB_PURPOSES[ 0 ],
                    &_set_t::TRACK_JOB_PURPOSES[
                        _set_t::NUM_TRACK_JOB_PURPOSES ],
                    st::KERNEL_OP_TRACK_JOB_HAS_REQUIRED_PURPOSES,
                    st::KERNEL_OP_TRACK_JOB_KERNELS_AVAILABLE,
                    st::KERNEL_OP_TRACK_JOB_KERNELS_READY );
            }

            if( this->numPurposes( lock ) > _set_t::size_type{ 0 } )
            {
                op_flags |= this->doUpdateKernelOpFlagsForPurposes( lock,
                    this->purposesBegin( lock ), this->purposesEnd( lock ),
                    st::KERNEL_OP_HAS_ALL_REQUIRED_PURPOSES,
                    st::KERNEL_OP_ALL_REQUIRED_KERNELS_AVAILABLE,
                    st::KERNEL_OP_ALL_REQUIRED_KERNELS_READY );
            }

            if( this->m_kernel_op_flags != op_flags )
            {
                this->registerChange( lock );
                this->m_kernel_op_flags = op_flags;
            }

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _set_t::status_t KernelSetBase::doSyncWithStore(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        bool const perform_config_update_if_required )
    {
        using size_t    = _set_t::size_type;

        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _set_t::kernel_config_store_base_t& store = this->kernelConfigStore();

        if( ( this->checkLock( lock ) ) &&
            ( store.hasKernelSet( lock, *this ) ) )
        {
            _set_t::op_flags_t const current_op_flags = this->kernelOpFlags();
            _set_t::op_flags_t op_flags = st::KERNEL_OP_FLAGS_NONE;

            status = st::ARCH_STATUS_SUCCESS;

            SIXTRL_ASSERT( _set_t::NUM_CONTROLLER_PURPOSES > size_t{ 0 } );
            SIXTRL_ASSERT( _set_t::NUM_TRACK_JOB_PURPOSES  > size_t{ 0 } );

            if( this->isForControllers() )
            {
                auto ctrl_purposes_begin = &_set_t::CONTROLLER_PURPOSES[ 0 ];
                auto ctrl_purposes_end = ctrl_purposes_begin;
                std::advance( ctrl_purposes_end,
                              _set_t::NUM_CONTROLLER_PURPOSES );

                op_flags |= this->doSyncWithStoreForPurposes( lock,
                    ctrl_purposes_begin, ctrl_purposes_end,
                    st::KERNEL_OP_CTRL_HAS_REQUIRED_PURPOSES,
                    st::KERNEL_OP_CTRL_KERNELS_AVAILABLE,
                    st::KERNEL_OP_CTRL_KERNELS_READY,
                    perform_config_update_if_required );
            }

            if( this->isForTrackJobs() )
            {
                auto tjob_purposes_begin = &_set_t::TRACK_JOB_PURPOSES[ 0 ];
                auto tjob_purposes_end   = tjob_purposes_begin;
                std::advance( tjob_purposes_end,
                              _set_t::NUM_TRACK_JOB_PURPOSES );

                op_flags |= this->doSyncWithStoreForPurposes( lock,
                    tjob_purposes_begin, tjob_purposes_end,
                    st::KERNEL_OP_TRACK_JOB_HAS_REQUIRED_PURPOSES,
                    st::KERNEL_OP_TRACK_JOB_KERNELS_AVAILABLE,
                    st::KERNEL_OP_TRACK_JOB_KERNELS_READY );
            }

            if( this->numPurposes( lock ) > size_t{ 0 } )
            {
                op_flags |= this->doSyncWithStoreForPurposes( lock,
                    this->purposesBegin( lock ), this->purposesEnd( lock ),
                    st::KERNEL_OP_HAS_ALL_REQUIRED_PURPOSES,
                    st::KERNEL_OP_ALL_REQUIRED_KERNELS_AVAILABLE,
                    st::KERNEL_OP_ALL_REQUIRED_KERNELS_READY,
                    perform_config_update_if_required );
            }

            if( current_op_flags != op_flags )
            {
                this->m_kernel_op_flags.store( op_flags );
                this->registerChange( lock );
            }

        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _set_t::status_t KernelSetBase::updateConfig(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::purpose_t const purpose )
    {
        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        auto it = this->doFindItemIterByPurpose( lock, purpose );

        if( it != this->m_purpose_to_data_map.end() )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            if( ( it->second.available() ) &&
                ( it->second.ptrKernelConfigBase() != nullptr ) )
            {
                if( it->second.ptrKernelConfigBase()->needsUpdate() )
                {
                    status = it->second.ptrKernelConfigBase()->update();

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        this->registerChange( lock );
                    }
                }
                else
                {
                    SIXTRL_ASSERT( it->second.ready() );
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _set_t::status_t KernelSetBase::updateAllConfigs(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( !this->checkLock( lock ) ) return status;

        status = st::ARCH_STATUS_SUCCESS;
        bool has_been_updated = false;

        for( auto const purpose : this->m_purposes )
        {
            auto it = this->m_purpose_to_data_map.find( purpose );

            if( it == this->m_purpose_to_data_map.end() )
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( ( it->second.available() ) &&
                ( it->second.ptrKernelConfigBase() != nullptr ) )
            {
                if( it->second.ptrKernelConfigBase()->needsUpdate() )
                {
                    status = it->second.ptrKernelConfigBase()->update();
                    has_been_updated |= ( status == st::ARCH_STATUS_SUCCESS );
                }
                else if( !it->second.ready() )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }

        if( has_been_updated )
        {
            this->registerChange( lock );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool KernelSetBase::ready( _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::kernel_config_key_t const& SIXTRL_RESTRICT_REF key
        ) const SIXTRL_NOEXCEPT
    {
        bool is_ready = false;

        using store_t = _set_t::kernel_config_store_base_t;
        using kernel_id_t = _set_t::kernel_config_id_t;
        using ptr_config_t = _set_t::kernel_config_base_t const*;

        store_t const& store = this->kernelConfigStore();

        if( this->requires( lock, key.purpose() ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );

            kernel_id_t const id = store.kernelId( lock, key );
            ptr_config_t ptr_base = store.ptrKernelConfigBase( lock, id );

            is_ready = ( ( id != _set_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                ( ptr_base != nullptr ) && ( !ptr_base->needsUpdate() ) );
        }

        return is_ready;
    }

    bool KernelSetBase::ready( _set_t::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        if( !this->checkLock( lock ) ) return false;

        SIXTRL_ASSERT( this->m_purpose_to_data_map.size() ==
                       this->m_purposes.size() );

        bool are_all_ready = true;

        for( auto const purpose : this->m_purposes )
        {
            auto it = this->doFindItemIterByPurpose( lock, purpose );

            if( (  it == this->m_purpose_to_data_map.end() ) ||
                ( !it->second.ready() ) )
            {
                are_all_ready = false;
                break;
            }
        }

        return are_all_ready;
    }

    /* --------------------------------------------------------------------- */

    _set_t::status_t KernelSetBase::reset(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->checkLock( lock ) ) return status;

        status = st::ARCH_STATUS_SUCCESS;
        bool has_been_updated = false;

        _set_t::kernel_set_id_t const my_kernel_set_id = this->kernelSetId();
        _set_t::kernel_config_store_base_t& store = this->kernelConfigStore();

        status = st::ARCH_STATUS_SUCCESS;

        if( ( my_kernel_set_id != _set_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( !this->m_kernel_id_to_purposes_map.empty() ) )
        {
            auto kernel_it =  this->m_kernel_id_to_purposes_map.begin();
            auto kernel_end = this->m_kernel_id_to_purposes_map.end();

            for( ; kernel_it != kernel_end ; ++kernel_it )
            {
                _set_t::kernel_config_id_t const kernel_id = kernel_it->first;
                auto ptr = store.ptrKernelConfigBase( lock, kernel_id );

                if( ( ptr != nullptr ) &&
                    ( ptr->isAttachedToSet( my_kernel_set_id ) ) )
                {
                    status = ptr->detachFromSet( my_kernel_set_id );
                    has_been_updated = true;

                    if( status != st::ARCH_STATUS_SUCCESS )
                    {
                        break;
                    }
                }
            }

            this->m_kernel_id_to_purposes_map.clear();
        }

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( this->numPurposes( lock ) > size_t{ 0 } ) )
        {
            this->m_purpose_to_data_map.clear();
            this->m_purposes.clear();

            has_been_updated = true;
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = this->m_current_key.reset();
            has_been_updated = true;
        }

        if( has_been_updated )
        {
            this->registerChange( lock );
        }

        return status;
    }

    _set_t::status_t KernelSetBase::reset(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        auto it = this->doFindItemIterByPurpose( lock, purpose );
        if( it != this->m_purpose_to_data_map.end() )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            bool const prev_available = it->second.available();

            status = st::ARCH_STATUS_SUCCESS;

            if( prev_available )
            {
                auto const kernel_id = it->second.kernelConfigId();
                status = this->doRemovePurposeFromKernelId(
                    lock, kernel_id, purpose );
            }

            status = it->second.reset();

            if( ( status == st::ARCH_STATUS_SUCCESS ) && ( prev_available ) )
            {
                this->registerChange( lock );
            }
        }

        return status;
    }

    _set_t::status_t KernelSetBase::resetKernelConfig(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::kernel_config_id_t const kernel_id )
    {
        using store_t = _set_t::kernel_config_store_base_t;
        using kernel_set_id_t = store_t::kernel_set_id_t;
        using ptr_config_t = _set_t::kernel_config_base_t*;

        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        store_t& store = this->kernelConfigStore();
        kernel_set_id_t const my_set_id = store.kernelSetId( lock, *this );
        ptr_config_t ptr_config = store.ptrKernelConfigBase( lock, kernel_id );

        auto kernel_it = this->m_kernel_id_to_purposes_map.find( kernel_id );

        if( ( kernel_id != _set_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( my_set_id != store_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( ptr_config != nullptr ) &&
            ( kernel_it != this->m_kernel_id_to_purposes_map.end() ) )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            SIXTRL_ASSERT( std::is_sorted( kernel_it->second.begin(),
                                           kernel_it->second.end() ) );

            status = st::ARCH_STATUS_SUCCESS;

            auto purpose_it  = kernel_it->second.begin();
            auto purpose_end = kernel_it->second.end();

            for( ; purpose_it != purpose_end ; ++purpose_it )
            {
                auto const purpose = *purpose_it;

                if( !this->available( lock, purpose ) )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

                status = this->doRemovePurposeFromKernelId(
                    lock, kernel_id, purpose );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    auto it = this->doFindItemIterByPurpose( lock, purpose );
                    if( ( it != this->doGetPurposeToDataEndIter( lock ) ) &&
                        ( it->second.available() ) )
                    {
                        status = it->second.reset();
                    }
                }

                if( status != st::ARCH_STATUS_SUCCESS )
                {
                    break;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _set_t::status_t KernelSetBase::addPurpose(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::purpose_t const purpose )
    {
        _set_t::status_t status = this->doAddPurposeBaseImpl( lock, purpose );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = this->doSortPurposesAndCheckForDuplicates( lock );
        }

        return status;
    }

    _set_t::status_t KernelSetBase::addPurposes(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::size_type const num_purposes,
        _set_t::purpose_t const* SIXTRL_RESTRICT purposes_begin )
    {
        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( num_purposes > _set_t::size_type{ 0 } ) &&
            ( purposes_begin != nullptr ) )
        {
            status = this->doAddPurposes(
                lock, purposes_begin, purposes_begin + num_purposes );
        }
        else if( num_purposes == _set_t::size_type{ 0 } )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _set_t::status_t KernelSetBase::removePurpose(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        _set_t::status_t status =
            this->doRemovePurposeBaseImpl( lock, purpose );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            this->registerChange( lock );
            status = this->doSortPurposesAndCheckForDuplicates( lock );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _set_t::status_t KernelSetBase::doSortPurposesAndCheckForDuplicates(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->checkLock( lock ) )
        {
            return status;
        }

        if( !this->m_purposes.empty() )
        {
            std::sort( this->m_purposes.begin(), this->m_purposes.end() );
            _set_t::size_type const cmp_size = this->m_purposes.size();

            this->m_purposes.erase( std::unique(
                this->m_purposes.begin(), this->m_purposes.end() ),
                    this->m_purposes.end() );

            if( ( cmp_size == this->m_purposes.size() ) &&
                ( cmp_size == this->m_purpose_to_data_map.size() ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }
        else
        {
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _set_t::status_t KernelSetBase::doSwitchKernel(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        bool const is_pinned_flag )
    {
        using kernel_id_t = _set_t::kernel_config_id_t;

        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _set_t::kernel_config_store_base_t& store = this->kernelConfigStore();
        _set_t::purpose_t const purpose = key.purpose();

        auto purpose_it = this->doFindItemIterByPurpose( lock, purpose );

        if( purpose_it == this->m_purpose_to_data_map.end() )
        {
            return status;
        }

        SIXTRL_ASSERT( purpose != _set_t::UNSPECIFIED_PUPRPOSE );
        SIXTRL_ASSERT( this->checkLock( lock ) );

        if( ( !this->m_current_key.isEqualExceptPurpose( key ) ) &&
            ( !is_pinned_flag ) )
        {
            return status;
        }

        kernel_id_t const current_kernel_id =
            purpose_it->second.kernelConfigId();

        kernel_id_t new_kernel_id = store.kernelId( lock, key );

        if( ( current_kernel_id != _set_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( !this->isPurposeAssociatedWithKernelConfigId(
                lock, current_kernel_id, purpose ) ) )
        {
            return status;
        }

        if( ( ( new_kernel_id != _set_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                ( new_kernel_id != current_kernel_id ) ) ||
            ( ( new_kernel_id == _set_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                ( store.hasDefaultInitKernelConfigParameters( lock, key ) ) ) )
        {
            if( new_kernel_id == _set_t::ILLEGAL_KERNEL_CONFIG_ID )
            {
                new_kernel_id = store.initKernelConfig( lock, key );
            }

            if( ( new_kernel_id == _set_t::ILLEGAL_KERNEL_CONFIG_ID ) ||
                ( new_kernel_id == current_kernel_id ) )
            {
                return status;
            }

            status = this->doAssignPurposeToKernelId(
                lock, new_kernel_id, purpose );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = purpose_it->second.reset( new_kernel_id,
                    store.ptrKernelConfigBase( lock, new_kernel_id ),
                        key, is_pinned_flag );

                if( ( status == _item_t::RESET_SUCCESS_UPDATED ) ||
                    ( status == _item_t::RESET_SUCCESS_SYNC ) )
                {
                    if( current_kernel_id != _set_t::ILLEGAL_KERNEL_CONFIG_ID )
                    {
                        _set_t::status_t const remove_status =
                            this->doRemovePurposeFromKernelId( lock,
                                current_kernel_id, purpose );

                        if( remove_status != st::ARCH_STATUS_SUCCESS )
                        {
                            status = st::ARCH_STATUS_GENERAL_FAILURE;
                        }
                    }
                }
                else
                {
                    this->doRemovePurposeFromKernelId(
                        lock, new_kernel_id, purpose );
                }
            }
        }
        else if( ( new_kernel_id != _set_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                 ( new_kernel_id == current_kernel_id ) )
        {
            SIXTRL_ASSERT( ( purpose_it->second.pinned() ) ||
                ( this->m_current_key.isEqualExceptPurpose( key ) ) );

            status = _item_t::RESET_SUCCESS_SYNC;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _set_t::status_t KernelSetBase::doAssignPurposeToKernelId(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSetBase::kernel_config_id_t const kernel_id,
        _set_t::purpose_t const purpose )
    {
        using store_t = _set_t::kernel_config_store_base_t;
        using kernel_set_id_t = store_t::kernel_set_id_t;
        using ptr_config_t = _set_t::kernel_config_base_t*;

        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        store_t& store = this->kernelConfigStore();
        kernel_set_id_t my_kernel_set_id = store.kernelSetId( lock, *this );
        ptr_config_t ptr_config = store.ptrKernelConfigBase( lock, kernel_id );

        auto it = this->doFindItemIterByPurpose( lock, purpose );

        if( ( kernel_id != _set_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( ptr_config != nullptr ) &&
            ( my_kernel_set_id != store_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( it != this->m_purpose_to_data_map.end() ) )
        {
            SIXTRL_ASSERT( purpose != _set_t::UNSPECIFIED_PUPRPOSE );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto kernel_it = this->m_kernel_id_to_purposes_map.find( kernel_id );
            if( kernel_it == this->m_kernel_id_to_purposes_map.end() )
            {
                /* This should be a new association of the kernel config with
                 * the kernel set -> verify that it has not so far been
                 * attached and notify it about the attachment */

                if( ptr_config->isAttachedToSet( my_kernel_set_id ) )
                {
                    throw std::runtime_error(
                        "logical inconsistency: kernel config is already "
                        "attached to kernel set" );
                }

                if( !ptr_config->canAttachToSet( my_kernel_set_id ) )
                {
                    throw std::runtime_error(
                        "can not attach kernel config to set" );
                }

                if( st::ARCH_STATUS_SUCCESS != ptr_config->attachToSet(
                        my_kernel_set_id ) )
                {
                    throw std::runtime_error(
                        "error during attaching kernel config to kernel set" );
                }

                auto res = this->m_kernel_id_to_purposes_map.emplace(
                    std::make_pair( kernel_id, _set_t::purposes_list_t{} ) );

                _set_t::purposes_list_t& plist = res.first->second;

                if( ( res.second ) && ( plist.empty() ) )
                {
                    plist.push_back( purpose );
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
            else if( ( kernel_it->second.empty() ) ||
                     ( !std::binary_search( kernel_it->second.begin(),
                        kernel_it->second.end(), purpose ) ) )
            {
                _set_t::purposes_list_t& plist = kernel_it->second;

                SIXTRL_ASSERT( std::is_sorted( plist.begin(), plist.end() ) );

                /* There should be an existing association between the
                 * kernel config and the kernel set -> check that before
                 * adding the purpose! */

                if( ptr_config->isAttachedToSet( my_kernel_set_id ) )
                {
                    _set_t::purpose_t const prev_last = ( plist.empty() )
                            ? _set_t::purpose_t{ 0 } : plist.back();

                    plist.push_back( purpose );

                    if( prev_last < purpose )
                    {
                        std::sort( plist.begin(), plist.end() );
                    }

                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    _set_t::status_t KernelSetBase::doRemovePurposeFromKernelId(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSetBase::kernel_config_id_t const kernel_id,
        _set_t::purpose_t const purpose )
    {
        using store_t = _set_t::kernel_config_store_base_t;
        using ptr_config_t = _set_t::kernel_config_base_t*;
        using kernel_set_id_t = store_t::kernel_set_id_t;

        /* NOTE: There are several checks for logical inconsistencies below;
         *       Normally, one would throw in such an instance an exception
         *       as that would indicate a major problem and the whole set
         *       is probably no longer usable in such a case.
         *       However, since this function is supposed to be called as
         *       part of the destructor of this class, we do not throw.
         *       It is advised in other instances to check for the return
         *       value and throw in calling instances where this is safe */

        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        store_t& store = this->kernelConfigStore();
        ptr_config_t ptr_config = store.ptrKernelConfigBase( lock, kernel_id );
        kernel_set_id_t my_kernel_set_id = this->kernelSetId();

        auto it = this->doFindItemIterByPurpose( lock, purpose );

        if( ( kernel_id != _set_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( ptr_config != nullptr ) &&
            ( my_kernel_set_id != store_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( it != this->m_purpose_to_data_map.end() ) )
        {
            SIXTRL_ASSERT( purpose != _set_t::UNSPECIFIED_PUPRPOSE );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            auto kernel_it = this->m_kernel_id_to_purposes_map.find( kernel_id );
            if( (  kernel_it != this->m_kernel_id_to_purposes_map.end() ) &&
                ( !kernel_it->second.empty() ) )
            {
                _set_t::purposes_list_t& plist = kernel_it->second;
                SIXTRL_ASSERT( std::is_sorted( plist.begin(), plist.end() ) );

                auto find_it = std::lower_bound(
                    plist.begin(), plist.end(), purpose );

                if( find_it == plist.end() )
                {
                    /* Since the plist can not be empty, this means that the
                     * purpose was not associated with the kernel id -> Weird!
                     * Nothing to do here! */

                    return status;
                }

                if( !ptr_config->isAttachedToSet( my_kernel_set_id ) )
                {
                    /* We expect the kernel config to be attached to this
                     * kernel set, but this is not the case -> bailing out */

                    return status;
                }

                plist.erase( find_it );

                /* erasing an element should not make the purpose list
                 * unsorted. Let's check this! */
                SIXTRL_ASSERT( std::is_sorted( plist.begin(), plist.end() ) );

                if( kernel_it->second.empty() )
                {
                    status = ptr_config->detachFromSet( my_kernel_set_id );
                    this->m_kernel_id_to_purposes_map.erase( kernel_id );
                }
                else
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    void KernelSetBase::doSetIsForControllersFlag(
        bool const is_for_controllers ) SIXTRL_NOEXCEPT
    {
        this->m_is_for_controllers = is_for_controllers;
    }

    void KernelSetBase::doSetIsForTrackJobsFlag(
        bool const is_for_controllers ) SIXTRL_NOEXCEPT
    {
        this->m_is_for_track_jobs = is_for_controllers;
    }

    /* --------------------------------------------------------------------- */

    _set_t::status_t KernelSetBase::doAddPurposeBaseImpl(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::purpose_t const purpose )
    {
        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        auto it = this->doFindItemIterByPurpose( lock, purpose );
        if( ( it == this->m_purpose_to_data_map.end() ) &&
            ( this->checkLock( lock ) ) )
        {
            SIXTRL_ASSERT( this->m_purpose_to_data_map.size() ==
                        this->m_purposes.size() );

            SIXTRL_ASSERT( std::is_sorted(
                this->m_purposes.begin(), this->m_purposes.end() ) );

            SIXTRL_ASSERT( !std::binary_search( this->m_purposes.begin(),
                this->m_purposes.end(), purpose ) );

            auto res = this->m_purpose_to_data_map.emplace(
                std::make_pair( purpose, _item_t{} ) );

            if( res.second )
            {
                _set_t::purpose_t const prev_last =
                    ( !this->m_purposes.empty() )
                        ? this->m_purposes.back() : _set_t::purpose_t{ 0 };

                this->m_purposes.push_back( purpose );

                if( prev_last > purpose )
                {
                    std::sort( this->m_purposes.begin(),
                               this->m_purposes.end() );
                }

                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    _set_t::status_t KernelSetBase::doRemovePurposeBaseImpl(
        _set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _set_t::purpose_t const purpose )
    {
        _set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        SIXTRL_ASSERT( purpose != _set_t::UNSPECIFIED_PUPRPOSE );
        SIXTRL_ASSERT( this->checkLock( lock ) );
        SIXTRL_ASSERT( !this->m_purposes.empty() );
        SIXTRL_ASSERT(  this->m_purposes.size() ==
                        this->m_purpose_to_data_map.size() );

        SIXTRL_ASSERT( std::is_sorted(
            this->m_purposes.begin(), this->m_purposes.end() ) );

        SIXTRL_ASSERT( std::binary_search(
            this->m_purposes.begin(), this->m_purposes.end(), purpose ) );

        auto map_it = this->doFindItemIterByPurpose( lock, purpose );
        auto lin_it = std::lower_bound( this->m_purposes.begin(),
            this->m_purposes.end(), purpose );

        if( ( map_it != this->m_purpose_to_data_map.end() ) &&
            ( lin_it != this->m_purposes.end() ) )
        {
            status = st::ARCH_STATUS_SUCCESS;

            if( map_it->second.kernelConfigId() !=
                _set_t::ILLEGAL_KERNEL_CONFIG_ID )
            {
                SIXTRL_ASSERT( map_it->second.available() );
                status = this->doRemovePurposeFromKernelId( lock,
                    map_it->second.kernelConfigId(), purpose );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = map_it->second.reset();
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) ||
                ( status == _item_t::RESET_SUCCESS_UPDATED ) )
            {
                if( lin_it != this->m_purposes.end() )
                {
                    this->m_purpose_to_data_map.erase( purpose );
                    this->m_purposes.erase( lin_it );

                    if( this->m_purposes.size() > _set_t::size_type{ 1 } )
                    {
                        std::sort( this->m_purposes.begin(),
                                   this->m_purposes.end() );
                    }
                }
                else
                {
                    status =  st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }
        }

        return status;
    }

    void KernelSetBase::doClearWithoutLocking() SIXTRL_NOEXCEPT
    {
        /* WARNING: Never ever call this function directly, it's just a
         *          last-effort clean-up handle to be called from
         *          the catch block in the destructor */

        this->m_current_key.reset();
        this->m_purpose_to_data_map.clear();
        this->m_purposes.clear();
        this->m_kernel_id_to_purposes_map.clear();

        return;
    }

    /* ********************************************************************* */
    /* ControllerKernelSetBase: */

    constexpr _ctrl_set_t::purpose_t _ctrl_set_t::PURPOSE_REMAP_BUFFER;

    ControllerKernelSetBase::ControllerKernelSetBase(
        _ctrl_set_t::arch_id_t const arch_id,
        _ctrl_set_t::kernel_config_store_base_t& SIXTRL_RESTRICT_REF store ) :
        st::KernelSetBase( arch_id, store, _ctrl_set_t::NUM_CONTROLLER_PURPOSES,
                           &_ctrl_set_t::CONTROLLER_PURPOSES[ 0 ] )
    {
        this->doSetIsForControllersFlag( true );
    }

    ControllerKernelSetBase::ControllerKernelSetBase(
        _ctrl_set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _ctrl_set_t::arch_id_t const arch_id,
        _ctrl_set_t::kernel_config_store_base_t& SIXTRL_RESTRICT_REF store ) :
        st::KernelSetBase( lock, arch_id, store,
             _ctrl_set_t::NUM_CONTROLLER_PURPOSES,
            &_ctrl_set_t::CONTROLLER_PURPOSES[ 0 ] )
    {
        this->doSetIsForControllersFlag( true );
    }

    _ctrl_set_t::kernel_config_id_t
    ControllerKernelSetBase::initRemapBufferKernelConfig(
        _ctrl_set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _ctrl_set_t::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
    {
        using kernel_id_t = _ctrl_set_t::kernel_config_id_t;
        using store_t = _ctrl_set_t::kernel_config_store_base_t;

        if( ( !this->checkLock( lock ) ) ||
            ( key.purpose() != _ctrl_set_t::PURPOSE_REMAP_BUFFER ) )
        {
            return _ctrl_set_t::ILLEGAL_KERNEL_CONFIG_ID;
        }

        store_t& store = this->kernelConfigStore();
        SIXTRL_ASSERT( store.hasKernelSet( lock, *this ) );

        kernel_id_t kernel_id = store.kernelId( lock, key );

        if( ( kernel_id == _ctrl_set_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( store.hasDefaultInitKernelConfigParameters( lock, key ) ) )
        {
            kernel_id = store.initKernelConfig( lock, key );
        }

        if( kernel_id == _ctrl_set_t::ILLEGAL_KERNEL_CONFIG_ID )
        {
            kernel_id = this->doInitRemapBufferKernelConfig( lock, key );
        }

        return kernel_id;
    }

    _ctrl_set_t::status_t
    ControllerKernelSetBase::configureRemapBufferKernelConfig(
        _ctrl_set_t::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerKernelSetBase;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->checkLock( lock ) )
        {
            _this_t::kernel_config_key_t& key =
                this->currentKernelConfigKey( lock );

            _this_t::purpose_t const saved_purpose = key.purpose();
            key.setPurpose( _this_t::PURPOSE_REMAP_BUFFER );
            status = this->doConfigureRemapBufferKernelConfig( lock, key );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( this->configNeedsUpdate( lock, key.purpose() ) ) )
            {
                status = this->updateConfig( lock, key.purpose() );
            }

            key.setPurpose( saved_purpose );
        }

        return status;
    }

    _ctrl_set_t::status_t
    ControllerKernelSetBase::doInitDefaultControllerKernelConfigs(
        _ctrl_set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _ctrl_set_t::kernel_config_key_t& SIXTRL_RESTRICT_REF input_key )
    {
        _ctrl_set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->archId() != _ctrl_set_t::ARCH_ILLEGAL ) &&
            ( this->isArchCompatibleWith( input_key.archId() ) ) &&
            ( this->checkLock( lock ) ) )
        {
            SIXTRL_ASSERT( this->kernelConfigStore().hasKernelSet(
                lock, *this ) );

            SIXTRL_ASSERT( _ctrl_set_t::NUM_CONTROLLER_PURPOSES ==
                _ctrl_set_t::size_type{ 1 } );

            SIXTRL_ASSERT( _ctrl_set_t::CONTROLLER_PURPOSES[ 0 ] ==
                _ctrl_set_t::PURPOSE_REMAP_BUFFER );

            _ctrl_set_t::purpose_t const saved_purpose = input_key.purpose();

            /* ------------------------------------------------------------- */
            /* Remap Buffer Kernel Config: */

            input_key.setPurpose( _ctrl_set_t::PURPOSE_REMAP_BUFFER );

            _ctrl_set_t::kernel_set_id_t const remap_kernel_id =
                this->initRemapBufferKernelConfig( lock, input_key );

            if(  remap_kernel_id != _ctrl_set_t::ILLEGAL_KERNEL_CONFIG_ID )
            {
                status = this->syncWithStore( lock, input_key );
            }

            /* ------------------------------------------------------------- */

            input_key.setPurpose( saved_purpose );
        }

        return status;
    }

    _ctrl_set_t::kernel_config_id_t
    ControllerKernelSetBase::doInitRemapBufferKernelConfig(
        _ctrl_set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _ctrl_set_t::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
    {
        _ctrl_set_t::kernel_config_id_t id =
            _ctrl_set_t::ILLEGAL_KERNEL_CONFIG_ID;

        if( ( key.valid() ) &&
            ( key.purpose() == _ctrl_set_t::PURPOSE_REMAP_BUFFER ) &&
            ( this->hasKernelConfigKey( lock, key ) ) )
        {
            _ctrl_set_t::kernel_config_store_base_t& store =
                this->kernelConfigStore();

            SIXTRL_ASSERT( store.hasKernelSet( lock, *this ) );
            ( void )store;
        }

        return id;
    }

    _ctrl_set_t::status_t
    ControllerKernelSetBase::doConfigureDefaultControllerKernelConfigs(
        _ctrl_set_t::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        using key_t = _ctrl_set_t::kernel_config_key_t;

        _ctrl_set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        key_t const& key = this->currentKernelConfigKey( lock );

        if( ( this->archId() != _ctrl_set_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) &&
            ( this->isArchCompatibleWith( key.archId() ) ) )
        {
            SIXTRL_ASSERT( this->kernelConfigStore().hasKernelSet(
                lock, *this ) );

            SIXTRL_ASSERT( _ctrl_set_t::NUM_CONTROLLER_PURPOSES ==
                _ctrl_set_t::size_type{ 1 } );

            SIXTRL_ASSERT( _ctrl_set_t::CONTROLLER_PURPOSES[ 0 ] ==
                _ctrl_set_t::PURPOSE_REMAP_BUFFER );

            /* ------------------------------------------------------------- */
            /* Remap Buffer Kernel Config: */

            status = this->configureRemapBufferKernelConfig( lock );
        }

        return status;
    }

    _ctrl_set_t::status_t
    ControllerKernelSetBase::doConfigureRemapBufferKernelConfig(
        _ctrl_set_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _ctrl_set_t::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
    {
        _ctrl_set_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        auto it = this->doFindItemIterByPurpose( lock, key.purpose() );

        if( ( key.purpose() == _ctrl_set_t::PURPOSE_REMAP_BUFFER ) &&
            ( it != this->doGetPurposeToDataEndIter( lock ) ) &&
            ( it->second.available() ) &&
            ( it->second.ptrKernelConfigBase() != nullptr ) )
        {
            SIXTRL_ASSERT( this->kernelConfigStore().hasKernelSet(
                lock, *this ) );

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }
}

/* end: sixtracklib/common/control/required_kernels_list.cpp */
