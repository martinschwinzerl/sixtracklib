#include "sixtracklib/common/control/kernel_config_store.hpp"

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <map>
    #include <memory>
    #include <mutex>
    #include <set>
    #include <string>
    #include <stdexcept>
    #include <thread>
    #include <unordered_map>
    #include <unordered_set>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/argument_base.hpp"
    #include "sixtracklib/common/control/kernel_config_key.hpp"
    #include "sixtracklib/common/control/kernel_config_base.hpp"
    #include "sixtracklib/common/control/kernel_set.hpp"
    #include "sixtracklib/common/buffer.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/be_monitor/be_monitor.h"
    #include "sixtracklib/common/output/output_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    using _item_t  = SIXTRL_CXX_NAMESPACE::KernelSetItemData;
    using _set_t   = SIXTRL_CXX_NAMESPACE::KernelSetBase;
    using _store_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;

    /* ********************************************************************* */
    /* KernelConfigStore: */

    constexpr _store_t::kernel_config_id_t _store_t::ILLEGAL_KERNEL_CONFIG_ID;
    constexpr _store_t::kernel_set_id_t    _store_t::ILLEGAL_KERNEL_SET_ID;
    constexpr _store_t::platform_id_t      _store_t::ILLEGAL_PLATFORM_ID;
    constexpr _store_t::device_id_t        _store_t::ILLEGAL_DEVICE_ID;
    constexpr _store_t::arch_id_t          _store_t::ARCH_ILLEGAL;
    constexpr _store_t::purpose_t          _store_t::DEFAULT_KERNEL_PURPOSE;
    constexpr _store_t::variant_t          _store_t::DEFAULT_KERNEL_VARIANT;
    constexpr _store_t::argument_set_t     _store_t::DEFAULT_ARGUMENTS_SET;

    std::atomic< KernelConfigStore::purpose_t >
        KernelConfigStore::NEXT_USERDEFINED_PURPOSE_ID{
            st::KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID };

    KernelConfigStore::purpose_t
    KernelConfigStore::NextUserdefinedPurposeId() SIXTRL_NOEXCEPT
    {
        return KernelConfigStore::NEXT_USERDEFINED_PURPOSE_ID++;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::KernelConfigStore() :
        m_key_to_kernel_id(),
        m_key_to_kernel_init_params(),
        m_kernel_id_to_keys(),
        m_kernel_id_ref_counter(),
        m_stored_kernel_configs(),
        m_stored_kernel_sets(),
        m_num_stored_kernels( _store_t::size_type{ 0 } ),
        m_num_stored_kernel_sets( _store_t::size_type{ 0 } ),
        m_lockable()
    {
    }

    /* --------------------------------------------------------------------- */

    _store_t::kernel_set_id_t KernelConfigStore::addKernelSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::ptr_kernel_set_t&& ptr_kernel_set )
    {
        _store_t::kernel_set_id_t kernel_set_id =
            _store_t::ILLEGAL_KERNEL_SET_ID;

        if( ( ptr_kernel_set.get() != nullptr ) &&
            ( this->checkLock( lock ) ) &&
            ( &ptr_kernel_set->kernelConfigStore() == this ) )
        {
            _store_t::kernel_set_id_t const next_kernel_set_id =
                this->m_stored_kernel_sets.size();

            this->m_stored_kernel_sets.emplace_back(
                std::move( ptr_kernel_set ) );

            if( ( !this->m_stored_kernel_sets.empty() ) &&
                (  this->m_stored_kernel_sets.back().get() != nullptr ) &&
                ( &this->m_stored_kernel_sets.back()->kernelConfigStore() ==
                   this ) )
            {
                ++this->m_num_stored_kernel_sets;
                kernel_set_id = next_kernel_set_id;
            }
        }

        return kernel_set_id;
    }

    _store_t::kernel_set_id_t KernelConfigStore::kernelSetId(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::kernel_set_t const& SIXTRL_RESTRICT_REF
            kernel_set ) const SIXTRL_NOEXCEPT
    {
        using kernel_id_t = _store_t::kernel_set_id_t;

        kernel_id_t found_kernel_set_id = _store_t::ILLEGAL_KERNEL_SET_ID;

        if( ( this->checkLock( lock ) ) &&
            ( this->m_num_stored_kernel_sets > _store_t::size_type{ 0 } ) )
        {
            SIXTRL_ASSERT( this->m_stored_kernel_sets.size() >=
                           this->m_num_stored_kernel_sets );

            auto it  = this->m_stored_kernel_sets.begin();
            auto end = this->m_stored_kernel_sets.end();
            kernel_id_t kernel_id = kernel_id_t{ 0 };

            for( ; it != end ; ++it, ++kernel_id )
            {
                if( it->get() == &kernel_set )
                {
                    found_kernel_set_id = kernel_id;
                    break;
                }
            }
        }

        return found_kernel_set_id;
    }

    _store_t::kernel_set_t const& KernelConfigStore::kernelSetBase(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::kernel_set_id_t const kernel_set_id ) const
    {
        if( !this->checkLock( lock ) )
        {
            throw std::runtime_error( "not properly locked lock handle" );
        }

        auto ptr = this->ptrKernelSetBase( lock, kernel_set_id );

        if( ptr == nullptr )
        {
            throw std::runtime_error( "no kernel set with this id available" );
        }

        return *ptr;
    }

    _store_t::status_t _store_t::removeKernelSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::kernel_set_id_t const kernel_set_id )  SIXTRL_NOEXCEPT
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_set_id != _store_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( this->checkLock( lock ) ) &&
            ( !this->m_stored_kernel_sets.empty() ) &&
            (  this->m_stored_kernel_sets.size() >
                static_cast< _store_t::size_type >( kernel_set_id ) ) &&
            ( this->m_stored_kernel_sets[ kernel_set_id ].get() != nullptr ) &&
            ( this->m_num_stored_kernel_sets > _store_t::size_type{ 0 } ) )
        {
            this->m_stored_kernel_sets[ kernel_set_id ].reset( nullptr );
            --this->m_num_stored_kernel_sets;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::kernel_config_id_t KernelConfigStore::addKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::ptr_kernel_config_t&& ptr_kernel_config )
    {
        using _this_t = st::KernelConfigStore;
        using kernel_id_t = _this_t::kernel_config_id_t;
        kernel_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_CONFIG_ID;

        if( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( ptr_kernel_config.get() != nullptr ) &&
            ( key.archId() == ptr_kernel_config->archId() ) &&
            ( key.purpose() == ptr_kernel_config->purpose() ) &&
            ( ( key.variant() == st::ARCH_VARIANT_NONE ) ||
              ( ptr_kernel_config->areVariantFlagsSet( key.archId() ) ) ) &&
            ( key.hasConfigStr() == ptr_kernel_config->hasConfigStr() ) &&
            ( ( !key.hasConfigStr() ) || ( 0 == key.configStr().compare(
                ptr_kernel_config->configStr() ) ) ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_key_to_kernel_id.find( key );

            if( it != this->m_key_to_kernel_id.end() )
            {
                return kernel_config_id;
            }

            kernel_config_id = this->doAddKernelConfig(
                lock, key, std::move( ptr_kernel_config ) );

            if( kernel_config_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID )
            {
                ++this->m_num_stored_kernels;
            }
        }

        return kernel_config_id;
    }

    KernelConfigStore::status_t KernelConfigStore::addKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::kernel_config_id_t const kernel_config_id )
    {
        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( this->checkLock( lock ) ) &&
            ( this->m_stored_kernel_configs.size() > static_cast< size_t >(
                kernel_config_id ) ) &&
            ( this->m_stored_kernel_configs[ kernel_config_id ].get() !=
                nullptr ) )
        {
            auto kernel_it = this->m_kernel_id_to_keys.find( kernel_config_id );
            auto cnt_it = this->m_kernel_id_ref_counter.find( kernel_config_id );

            if( ( kernel_it != this->m_kernel_id_to_keys.end() ) &&
                ( cnt_it != this->m_kernel_id_ref_counter.end() ) )
            {
                auto key_it = this->m_key_to_kernel_id.find( key );

                if( ( key_it == this->m_key_to_kernel_id.end() ) &&
                    ( ( kernel_it->second.empty() ) ||
                      ( kernel_it->second.find( key ) ==
                        kernel_it->second.end() ) ) )
                {
                    auto res1 = this->m_key_to_kernel_id.emplace(
                        std::make_pair( key, kernel_config_id ) );

                    auto res2 = kernel_it->second.insert( key );

                    if( ( res1.second ) && ( res2.second ) )
                    {
                        this->m_stored_kernel_configs[ kernel_config_id
                            ]->addVariantFlags( key.variant() );

                        ++cnt_it->second;
                        status = st::ARCH_STATUS_SUCCESS;
                    }
                }
                else if( ( !kernel_it->second.empty() ) &&
                    (  kernel_it->second.find( key ) !=
                       kernel_it->second.end() ) )
                {
                    SIXTRL_ASSERT(
                        ( key.variant() == st::ARCH_VARIANT_NONE ) ||
                        ( this->m_stored_kernel_configs[ kernel_config_id
                            ]->areVariantFlagsSet( key.variant() ) ) );

                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _store_t::status_t KernelConfigStore::removeKernelConfig(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::kernel_config_id_t const kernel_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_id != _store_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            status = st::ARCH_STATUS_SUCCESS;

            if( this->numKernelSets( lock ) > _store_t::size_type{ 0 } )
            {
                auto kernel_it = this->m_kernel_id_to_keys.find( kernel_id );

                if( (  kernel_it != this->m_kernel_id_to_keys.end() ) &&
                    ( !kernel_it->second.empty() ) )
                {
                    auto set_it    = this->m_stored_kernel_sets.begin();
                    auto set_end   = this->m_stored_kernel_sets.end();

                    auto key_begin = kernel_it->second.begin();
                    auto key_end   = kernel_it->second.end();

                    for( ; set_it != set_end ; ++set_it )
                    {
                        if( set_it->get() == nullptr )
                        {
                            continue;
                        }

                        auto key_it = key_begin;

                        for( ; key_it != key_end ; ++key_it )
                        {
                            if( ( *set_it )->hasKernelConfigKey( lock, *key_it ) )
                            {
                                status = ( *set_it )->reset(
                                    lock, key_it->purpose() );

                                if( status != st::ARCH_STATUS_SUCCESS )
                                {
                                    break;
                                }
                            }
                        }

                        if( status != st::ARCH_STATUS_SUCCESS )
                        {
                            break;
                        }
                    }
                }
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( this->m_num_stored_kernels > _store_t::size_type{ 0 } ) )
            {
                status = this->doRemoveKernelConfig( lock, kernel_id );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    --this->m_num_stored_kernels;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::size_type KernelConfigStore::numStoredKernels(
        KernelConfigStore::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;
        return ( this->checkLock( lock ) )
            ? this->m_num_stored_kernels : _this_t::size_type{ 0 };
    }

    KernelConfigStore::size_type KernelConfigStore::numKernelConfigKeys(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;

        _this_t::size_type num_keys_for_kernel = _this_t::size_type{ 0 };

        if( ( kernel_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_kernel_id_ref_counter.find( kernel_id );

            if( it != this->m_kernel_id_ref_counter.end() )
            {
                SIXTRL_ASSERT( this->m_stored_kernel_configs.size() >
                    static_cast< size_t >( kernel_id ) );

                SIXTRL_ASSERT( this->m_stored_kernel_configs[
                    kernel_id ].get() != nullptr );

                num_keys_for_kernel = it->second;

                SIXTRL_ASSERT( this->m_kernel_id_to_keys.find( kernel_id ) !=
                    this->m_kernel_id_to_keys.end() );

                SIXTRL_ASSERT( this->m_kernel_id_to_keys.find(
                    kernel_id )->second.size() == num_keys_for_kernel );
            }
        }

        return num_keys_for_kernel;
    }

    /* --------------------------------------------------------------------- */

    bool KernelConfigStore::hasKernel(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;
        using size_t  = _this_t::size_type;
        bool has_kernel = false;

        if( ( kernel_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( this->checkLock( lock ) ) &&
            ( this->m_stored_kernel_configs.size() >
                    static_cast< size_t >( kernel_id ) ) &&
            ( this->m_stored_kernel_configs[ kernel_id ].get() != nullptr ) )
        {
            auto cnt_it = this->m_kernel_id_ref_counter.find( kernel_id );
            auto kernel_it = this->m_kernel_id_to_keys.find( kernel_id );

            if( ( cnt_it != this->m_kernel_id_ref_counter.end() ) &&
                ( kernel_it != this->m_kernel_id_to_keys.end() ) )
            {
                has_kernel = ( cnt_it->second > size_t{ 0 } );
            }
        }

        return has_kernel;
    }

    KernelConfigStore::kernel_config_id_t KernelConfigStore::kernelId(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const&
            SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;
        _this_t::kernel_config_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_CONFIG_ID;

        if( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            auto key_it = this->m_key_to_kernel_id.find( key );

            if( ( key_it != this->m_key_to_kernel_id.end() ) &&
                ( key_it->second != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) )
            {
                kernel_config_id = key_it->second;
            }
        }

        return kernel_config_id;
    }

    KernelConfigStore::kernel_config_id_t KernelConfigStore::kernelId(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_base_t const& SIXTRL_RESTRICT_REF
            kernel_config ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;
        _this_t::kernel_config_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_CONFIG_ID;

        if( ( kernel_config.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it  = this->m_stored_kernel_configs.begin();
            auto end = this->m_stored_kernel_configs.end();

            _this_t::kernel_config_id_t temp_id = _this_t::kernel_config_id_t{ 0 };

            for( ; it != end ; ++it, ++temp_id )
            {
                if( it->get() == &kernel_config )
                {
                    kernel_config_id = temp_id;
                    break;
                }
            }
        }

        return kernel_config_id;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::kernel_config_key_t KernelConfigStore::findKey(
            KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
            KernelConfigStore::kernel_config_id_t const kernel_config_id
        ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;

        if( ( kernel_config_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_kernel_id_to_keys.find( kernel_config_id );
            if( ( it != this->m_kernel_id_to_keys.end() ) &&
                ( !it->second.empty() ) )
            {
                if( it->second.size() == _this_t::size_type{ 1 } )
                {
                    return *it->second.begin();
                }
            }
        }

        return _this_t::kernel_config_key_t{};
    }

    KernelConfigStore::kernel_config_key_t KernelConfigStore::findKey(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF hint_key
        ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;

        if( ( kernel_config_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_kernel_id_to_keys.find( kernel_config_id );
            if( ( it != this->m_kernel_id_to_keys.end() ) &&
                ( !it->second.empty() ) )
            {
                if( it->second.size() == _this_t::size_type{ 1 } )
                {
                    return *it->second.begin();
                }
                else
                {
                    auto key_it  = it->second.begin();
                    auto key_end = it->second.end();

                    for( ; key_it != key_end ; ++key_it )
                    {
                        if( ( hint_key.archId() != _this_t::ARCH_ILLEGAL ) &&
                            ( hint_key.archId() == key_it->archId() ) )
                        {
                            if( ( hint_key.hasNodeId() ) &&
                                ( key_it->hasNodeId() ) )
                            {
                                if( hint_key.nodeId() == key_it->nodeId() )
                                {
                                    return *key_it;
                                }
                            }
                        }
                    }
                }
            }
        }

        return _this_t::kernel_config_key_t{};
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::kernel_config_base_t const*
    KernelConfigStore::ptrKernelConfigBase(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;

        return ( ( kernel_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                 ( this->checkLock( lock ) ) &&
                 ( this->m_stored_kernel_configs.size() > static_cast<
                    _this_t::size_type >( kernel_id ) ) )
            ? this->m_stored_kernel_configs[ kernel_id ].get()
            : nullptr;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::kernel_config_id_t KernelConfigStore::initKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
    {
        using  size_t = _store_t::size_type;
        using kernel_id_t = _store_t::kernel_config_id_t;

        kernel_id_t kernel_config_id = _store_t::ILLEGAL_KERNEL_CONFIG_ID;

        if( ( key.archId() != _store_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            auto key_it = this->m_key_to_kernel_id.find( key );

            if( key_it != this->m_key_to_kernel_id.end() )
            {
                if( key_it->second != _store_t::ILLEGAL_KERNEL_CONFIG_ID )
                {
                    kernel_config_id = key_it->second;
                }

                return kernel_config_id;
            }

            SIXTRL_ASSERT( key_it == this->m_key_to_kernel_id.end() );

            auto init_param_it = this->m_key_to_kernel_init_params.find( key );
            if( init_param_it != this->m_key_to_kernel_init_params.end() )
            {
                size_t const num_kernel_args =
                    std::get< 0 >( init_param_it->second );

                std::string const& kernel_name = std::get< 1 >(
                    init_param_it->second );

                kernel_config_id = this->doInitKernelConfig(
                    lock, key, num_kernel_args, kernel_name.c_str() );

                if( kernel_config_id != _store_t::ILLEGAL_KERNEL_CONFIG_ID )
                {
                    ++this->m_num_stored_kernels;
                }
            }
        }

        return kernel_config_id;
    }

    KernelConfigStore::kernel_config_id_t KernelConfigStore::initKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_args,
        char const* SIXTRL_RESTRICT kernel_name )
    {
        _store_t::kernel_config_id_t const kernel_config_id =
            this->doInitKernelConfig( lock, key, num_kernel_args, kernel_name );

        if( kernel_config_id != _store_t::ILLEGAL_KERNEL_CONFIG_ID )
        {
            SIXTRL_ASSERT( this->checkLock( lock ) );
            ++this->m_num_stored_kernels;
        }

        return kernel_config_id;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::setDefaultInitKernelConfigParameters(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_arguments,
        std::string const& SIXTRL_RESTRICT_REF kernel_name )
    {
        using _this_t = st::KernelConfigStore;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_key_to_kernel_init_params.find( key );

            if( it == this->m_key_to_kernel_init_params.end() )
            {
                auto res = this->m_key_to_kernel_init_params.emplace(
                    std::make_pair( key, std::make_pair(
                        num_kernel_arguments, kernel_name ) ) );

                if( res.second )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
            else
            {
                std::get< 0 >( it->second ) = num_kernel_arguments;
                std::get< 1 >( it->second ) = kernel_name;
            }
        }

        return status;
    }

    KernelConfigStore::status_t
    KernelConfigStore::setDefaultInitKernelConfigParameters(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_arguments,
        char const* SIXTRL_RESTRICT kernel_name )
    {
        using _this_t = st::KernelConfigStore;
        std::string kernel_name_str( "" );

        if( ( kernel_name != nullptr ) &&
            ( std::strlen( kernel_name ) > _this_t::size_type{ 0 } ) )
        {
            kernel_name_str = kernel_name;
        }
        return this->setDefaultInitKernelConfigParameters(
            lock, key, num_kernel_arguments, kernel_name_str );
    }

    KernelConfigStore::status_t
    KernelConfigStore::removeDefaultInitKernelConfigParameters(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
    {
        using _this_t = st::KernelConfigStore;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_key_to_kernel_init_params.find( key );

            if( it != this->m_key_to_kernel_init_params.end() )
            {
                this->m_key_to_kernel_init_params.erase( it );
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    bool KernelConfigStore::hasDefaultInitKernelConfigParameters(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const&
            SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;

        return ( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
                 ( this->checkLock( lock ) ) &&
                 ( this->m_key_to_kernel_init_params.find( key ) !=
                   this->m_key_to_kernel_init_params.end() ) );
    }

    KernelConfigStore::size_type KernelConfigStore::defaultNumKernelArgs(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key
        ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;

        size_t num_kernel_args = size_t{ 0 };

        if( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_key_to_kernel_init_params.find( key );

            if( it != this->m_key_to_kernel_init_params.end() )
            {
                num_kernel_args = std::get< 0 >( it->second );
            }
        }

        return num_kernel_args;
    }

    std::string const& KernelConfigStore::defaultKernelName(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const
    {
        using _this_t = st::KernelConfigStore;

        if( key.archId() == _this_t::ARCH_ILLEGAL )
        {
            throw std::runtime_error( "illegal architecture for key" );
        }

        if( !this->checkLock( lock ) )
        {
            throw std::runtime_error( "not properly locked handle" );
        }

        if( !this->hasDefaultInitKernelConfigParameters( lock, key ) )
        {
            throw std::runtime_error(
                "no default kernel parameters available for key" );
        }

        auto it = this->m_key_to_kernel_init_params.find( key );
        SIXTRL_ASSERT( it != this->m_key_to_kernel_init_params.end() );

        return std::get< 1 >( it->second );
    }

    /* --------------------------------------------------------------------- */

    _store_t::kernel_config_id_t KernelConfigStore::doInitKernelConfig(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        _store_t::size_type const num_kernel_args,
        char const* SIXTRL_RESTRICT name )
    {
        _store_t::kernel_config_id_t id = _store_t::ILLEGAL_KERNEL_CONFIG_ID;

        if( ( key.valid() ) && ( this->checkLock( lock ) ) )
        {
            std::unique_ptr< _store_t::kernel_config_base_t >
                ptr_kernel_config( new _store_t::kernel_config_base_t(
                    key, num_kernel_args, name ) );

            if( ptr_kernel_config.get() != nullptr )
            {
                id = this->doAddKernelConfig(
                    lock, key, std::move( ptr_kernel_config ) );
            }
        }

        return id;
    }

    KernelConfigStore::kernel_config_id_t KernelConfigStore::doAddKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::ptr_kernel_config_t&& ptr_kernel_config )
    {
        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;

        _this_t::kernel_config_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_CONFIG_ID;

        SIXTRL_ASSERT( key.archId() != _this_t::ARCH_ILLEGAL );

        if( ( ptr_kernel_config.get() != nullptr ) &&
            ( this->checkLock( lock ) ) )
        {
            SIXTRL_ASSERT( key.archId() == ptr_kernel_config->archId() );
            SIXTRL_ASSERT( key.purpose() == ptr_kernel_config->purpose() );
            SIXTRL_ASSERT( ( key.variant() == st::ARCH_VARIANT_NONE ) ||
                ( ptr_kernel_config->areVariantFlagsSet( key.variant() ) ) );

            SIXTRL_ASSERT( key.hasConfigStr() ==
                ptr_kernel_config->hasConfigStr() );

            SIXTRL_ASSERT( ( !key.hasConfigStr() ) ||
                ( 0 == key.configStr().compare(
                    ptr_kernel_config->configStr() ) ) );

            SIXTRL_ASSERT( this->m_key_to_kernel_id.find( key ) ==
                           this->m_key_to_kernel_id.end() );

            _this_t::kernel_config_id_t temp_id = static_cast<
                _this_t::kernel_config_id_t >(
                    this->m_stored_kernel_configs.size() );

            auto res1 = this->m_kernel_id_to_keys.emplace(
                std::make_pair( temp_id, _this_t::keys_set_t{} ) );

            auto res2 = this->m_kernel_id_ref_counter.emplace(
                std::make_pair( temp_id, size_t{ 0 } ) );

            if( ( !res1.second ) || ( !res2.second ) )
            {
                return kernel_config_id;
            }

            auto krnl_it = this->m_kernel_id_to_keys.find( temp_id );
            SIXTRL_ASSERT( krnl_it != this->m_kernel_id_to_keys.end() );

            auto cnt_it = this->m_kernel_id_ref_counter.find( temp_id );
            SIXTRL_ASSERT( cnt_it != this->m_kernel_id_ref_counter.end() );

            auto res3 = krnl_it->second.insert( key );

            if( !res3.second )
            {
                this->m_kernel_id_to_keys.erase( temp_id );
                this->m_kernel_id_ref_counter.erase( temp_id );
                return kernel_config_id;
            }

            auto res4 = this->m_key_to_kernel_id.emplace(
                std::make_pair( key, temp_id ) );

            if( res4.second )
            {
                this->m_stored_kernel_configs.emplace_back(
                    std::move( ptr_kernel_config ) );

                SIXTRL_ASSERT( this->m_stored_kernel_configs.size() >
                    static_cast< size_t >( temp_id ) );

                cnt_it->second = size_t{ 1 };
                kernel_config_id = temp_id;
            }
        }

        return kernel_config_id;
    }

    KernelConfigStore::status_t KernelConfigStore::doRemoveKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id )
    {
        using size_t  = _store_t::size_type;
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _store_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( this->checkLock( lock ) ) &&
            ( this->m_stored_kernel_configs.size() >
                static_cast< size_t >( kernel_config_id ) ) )
        {
            auto krnl_it = this->m_kernel_id_to_keys.find( kernel_config_id );

            if( krnl_it == this->m_kernel_id_to_keys.end() )
            {
                return status;
            }

            status = st::ARCH_STATUS_SUCCESS;

            if( !krnl_it->second.empty() )
            {
                auto key_it  = krnl_it->second.begin();
                auto key_end = krnl_it->second.end();

                for( ; key_it != key_end ; ++key_it )
                {
                    auto find_key_it = this->m_key_to_kernel_id.find( *key_it );

                    if( find_key_it != this->m_key_to_kernel_id.end() )
                    {
                        if( find_key_it->second != kernel_config_id )
                        {
                            status = st::ARCH_STATUS_GENERAL_FAILURE;
                            break;
                        }

                        this->m_key_to_kernel_id.erase( find_key_it );
                    }
                }
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                if( this->numKernelSets( lock ) > size_t{ 0 } )
                {
                    auto set_it  = this->m_stored_kernel_sets.begin();
                    auto set_end = this->m_stored_kernel_sets.end();

                    for( ; set_it != set_end ; ++set_it )
                    {
                        if( set_it->get() == nullptr ) continue;

                        if( ( *set_it )->hasKernelConfigId(
                                lock, kernel_config_id ) )
                        {
                            status = ( *set_it )->reset(
                                lock, kernel_config_id );

                            if( status != st::ARCH_STATUS_SUCCESS )
                            {
                                break;
                            }
                        }
                    }
                }
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                this->m_kernel_id_to_keys.erase( kernel_config_id );
                this->m_kernel_id_ref_counter.erase( kernel_config_id );
                this->m_stored_kernel_configs[ kernel_config_id ].reset();
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _store_t::kernel_set_id_t KernelConfigStore::doAddKernelSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::ptr_kernel_set_t&& ptr_kernel_set )
    {
        using kernel_set_id_t = _store_t::kernel_set_id_t;

        kernel_set_id_t kernel_set_id = _store_t::ILLEGAL_KERNEL_SET_ID;

        if( ( this->checkLock( lock ) ) &&
            ( ( ( ptr_kernel_set.get() != nullptr ) &&
                ( &ptr_kernel_set->kernelConfigStore() == this ) ) ||
              ( ptr_kernel_set.get() == nullptr ) ) )
        {
            kernel_set_id_t const next_kernel_set_id = static_cast<
                kernel_set_id_t >( this->m_stored_kernel_sets.size() );

            this->m_stored_kernel_sets.emplace_back(
                std::move( ptr_kernel_set ) );

            if( this->m_stored_kernel_sets[ next_kernel_set_id
                    ].get() != nullptr )
            {
                SIXTRL_ASSERT( &this->m_stored_kernel_sets[
                    next_kernel_set_id ]->kernelConfigStore() == this );

                this->m_stored_kernel_sets[
                    next_kernel_set_id ]->syncWithStore( lock );

                kernel_set_id = next_kernel_set_id;
            }
        }

        return kernel_set_id;
    }

    _store_t::status_t KernelConfigStore::doRemoveKernelSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::kernel_set_id_t const kernel_set_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_set_id != _store_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( this->checkLock( lock ) ) &&
            ( this->m_stored_kernel_sets.size() > static_cast<
                _store_t::size_type >( kernel_set_id ) ) )
        {
            if( this->m_stored_kernel_sets[ kernel_set_id ].get() != nullptr )
            {
                this->m_stored_kernel_sets[ kernel_set_id ].reset( nullptr );
            }

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _store_t::status_t KernelConfigStore::doUpdateKernelSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::kernel_set_id_t const kernel_set_id )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        _store_t::kernel_set_t* ptr_kernel_set =
            this->ptrKernelSetBase( lock, kernel_set_id );

        if( ( ptr_kernel_set != nullptr ) &&
            ( &ptr_kernel_set->kernelConfigStore() == this ) )
        {
            SIXTRL_ASSERT( kernel_set_id != _store_t::ILLEGAL_KERNEL_SET_ID );
            SIXTRL_ASSERT( this->checkLock( lock ) );

            status = ptr_kernel_set->syncWithStore( lock );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _store_t::status_t KernelConfigStore::doUpdateStoredKernelSet(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::kernel_set_id_t const kernel_set_id,
        _store_t::ptr_kernel_set_t&& ptr_kernel_set )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_set_id != _store_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( this->checkLock( lock ) ) &&
            ( this->m_stored_kernel_sets.size() > static_cast<
                _store_t::size_type >( kernel_set_id ) ) &&
            ( ( ( this->m_stored_kernel_sets[ kernel_set_id ].get() !=
                    nullptr ) && ( ptr_kernel_set.get() == nullptr ) ) ||
              ( ( this->m_stored_kernel_sets[ kernel_set_id ].get() ==
                    nullptr ) && ( ptr_kernel_set.get() != nullptr ) ) ) )
        {
            this->m_stored_kernel_sets[
                kernel_set_id ] = std::move( ptr_kernel_set );

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _store_t::status_t KernelConfigStore::doInitKernelConfigFromKeyAttributes(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::kernel_config_base_t& SIXTRL_RESTRICT_REF config_base,
        _store_t::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
    {
        _store_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->checkLock( lock ) ) && ( key.valid() ) )
        {
            config_base.setPurpose( key.purpose() );
            config_base.addVariantFlags( key.variant() );
            config_base.setArgumentSet( key.argumentSet() );

            if( key.hasConfigStr() )
            {
                status = config_base.updateConfigStr( key.configStr() );
            }
            else
            {
                status = config_base.updateConfigStr( nullptr );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool KernelConfigStore::doCheckKeyAndKernelConfigAreSync(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::kernel_config_id_t const
            kernel_config_id ) const SIXTRL_NOEXCEPT
    {
        bool is_sync = false;

        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) &&
            ( this->m_stored_kernel_configs.size() > static_cast< size_t >(
                kernel_config_id ) ) &&
            ( this->m_stored_kernel_configs[ kernel_config_id
                    ].get() != nullptr ) &&
            ( this->m_stored_kernel_configs[ kernel_config_id
                    ]->purpose() == key.purpose() ) &&
            ( ( key.variant() == st::ARCH_VARIANT_NONE ) ||
              ( this->m_stored_kernel_configs[ kernel_config_id
                    ]->areVariantFlagsSet( key.variant() ) ) ) &&
            ( this->m_stored_kernel_configs[ kernel_config_id
                    ]->argumentSet() == key.argumentSet() ) &&
            ( ( key.hasConfigStr() == this->m_stored_kernel_configs[
                    kernel_config_id ]->hasConfigStr() ) &&
              ( ( !key.hasConfigStr() ) ||
                (  this->m_stored_kernel_configs[ kernel_config_id ]->configStr(
                    ).compare( key.configStr() ) == 0 ) ) ) )
        {
            is_sync = true;
        }

        return is_sync;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::kernel_config_id_t KernelConfigStore::doInitPredefinedKernel(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
        KernelConfigStore::purpose_t const predefined_purpose )
    {
        using _this_t = st::KernelConfigStore;
        _this_t::kernel_config_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_CONFIG_ID;

        if( ( input_key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            if( input_key.purpose() == predefined_purpose )
            {
                kernel_config_id = this->initKernelConfig( lock, input_key );
            }
            else
            {
                _this_t::kernel_config_key_t key( input_key );
                key.setPurpose( predefined_purpose );
                kernel_config_id = this->initKernelConfig( lock, key );
            }
        }

        return kernel_config_id;
    }
}

/* end: sixtracklib/common/control/kernel_config_store.cpp */
