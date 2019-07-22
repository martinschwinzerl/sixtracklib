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
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/argument_base.hpp"
    #include "sixtracklib/common/control/kernel_config_key.hpp"
    #include "sixtracklib/common/control/kernel_config_base.hpp"
    #include "sixtracklib/common/buffer.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#endif /* C++, Host */

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
    std::atomic< KernelConfigStore::purpose_t >
        KernelConfigStore::NEXT_USERDEFINED_PURPOSE_ID{
            st::KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID };

    KernelConfigStore::purpose_t
    KernelConfigStore::NextUserdefinedPurposeId() SIXTRL_NOEXCEPT
    {
        return KernelConfigStore::NEXT_USERDEFINED_PURPOSE_ID++;
    }

    KernelConfigStore::KernelConfigStore() :
        m_key_to_kernel_id(),
        m_key_to_kernel_init_params(),
        m_kernel_id_to_keys(), m_kernel_id_ref_counter(),
        m_stored_kernel_configs(),
        m_num_stored_kernels( KernelConfigStore::size_type{ 0 } ),
        m_lockable()
    {
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::kernel_id_t KernelConfigStore::addKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::ptr_kernel_config_t&& ptr_kernel_config )
    {
        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;
        using  key_t  = _this_t::key_t;

        _this_t::kernel_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_ID;

        if( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( ptr_kernel_config.get() != nullptr ) &&
            ( key.archId() == ptr_kernel_config->archId() ) &&
            ( key.purpose() == ptr_kernel_config->purpose() ) &&
            ( ( key.archId() == st::ARCH_VARIANT_NONE ) ||
              ( ptr_kernel_config->areVariantFlagsSet( key.archId() ) ) ) &&
            ( key.hasConfigStr() == ptr_kernel_config->hasConfigStr() ) &&
            ( ( !key.hasConfigStr() ) ||
              (  key.configStr().compare(
                    ptr_kernel_config.configStr() ) == 0 ) ) &&
            ( this->checkLock( lock ) ) )
        {
            auto it = this->m_key_to_kernel_id.find( key );

            if( it != this->m_key_to_kernel_id.end() )
            {
                return kernel_config_id;
            }

            kernel_config_id = this->doAddKernelConfig(
                lock, key, std::move( ptr_kernel_config ) );
        }

        return kernel_config_id;
    }

    KernelConfigStore::status_t KernelConfigStore::addKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::kernel_id_t const kernel_config_id )
    {
        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
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
                        this->m_stored_kernel_configs->addVariantFlags(
                            key.variant() );

                        ++cnt_it->second;
                        status = st::ARCH_STATUS_SUCCESS;
                    }
                }
                else if( ( !kernel_it->second.empty() ) &&
                    (  kernel_it->second.find( key ) !=
                       kernel_it->second.end() ) )
                {
                    SIXTRL_ASSERT(
                        ( key.archId() == st::ARCH_VARIANT_NONE ) ||
                        ( this->m_stored_kernel_configs[ kernel_config_id
                            ]->areVariantFlagsSet( key.variant() ) ) );

                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t KernelConfigStore::removeKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id )
    {
        return this->doRemoveKernelConfig( lock, kernel_config_id );
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

    KernelConfigStore::size_type KernelConfigStore::numKeys(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;

        _this_t::size_type num_keys_for_kernel = _this_t::size_type{ 0 };

        if( ( kernel_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( kernel_id >= _this_t::kernel_id_t{ 0 } ) &&
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
        KernelConfigStore::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;
        using size_t  = _this_t::size_type;
        bool has_kernel = false;

        if( ( kernel_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( kernel_id >= _this_t::kernel_id_t{ 0 } ) &&
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

    KernelConfigStore::kernel_id_t KernelConfigStore::kernelId(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const&
            SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;

        _this_t::kernel_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_ID;

        if( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            auto key_it = this->m_key_to_kernel_id.find( key );

            if( ( key_it != this->m_key_to_kernel_id.end() ) &&
                ( key_it->second != _this_t::ILLEGAL_KERNEL_ID ) )
            {
                _this_t::kernel_id_t const temp_id = key_it->second;

                SIXTRL_ASSERT( this->doCheckKeyAndKernelConfigAreSync(
                    lock, key, temp_id ) );

                kernel_config_id = temp_id;
            }
        }

        return kernel_config_id;
    }

    KernelConfigStore::kernel_id_t KernelConfigStore::kernelId(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_base_t const& SIXTRL_RESTRICT_REF
            kernel_config ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;
        _this_t::kernel_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_ID;

        if( ( kernel_config.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) )
        {
            auto it  = this->m_stored_kernel_configs.begin();
            auto end = this->m_stored_kernel_configs.end();

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

    KernelConfigStore::key_t KernelConfigStore::findKey(
            KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
            KernelConfigStore::kernel_id_t const kernel_config_id
        ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;

        if( ( kernel_config_id == _this_t::ILLEGAL_KERNEL_ID ) &&
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

        return _this_t::key_t{};
    }

    KernelConfigStore::key_t KernelConfigStore::findKey(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF hint_key
        ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;

        if( ( kernel_config_id == _this_t::ILLEGAL_KERNEL_ID ) &&
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

        return _this_t::key_t{};
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::kernel_config_base_t const*
    KernelConfigStore::ptrKernelConfigBase(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = st::KernelConfigStore;

        return ( ( kernel_id != _this_t::ILLEGAL_KERNEL_ID ) &&
                 ( kernel_id >= _this_t::kernel_id_t{ 0 } ) &&
                 ( this->checkLock( lock ) &&
                 ( this->m_stored_kernel_configs.size() > static_cast<
                    _this_t::size_type >( kernel_id ) ) )
            ? this->m_stored_kernel_configs[ kernel_id ].get()
            : nullptr;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::kernel_id_t KernelConfigStore::initKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
    {
        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;

        _this_t::kernel_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_ID;

        if( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            auto key_it = this->m_key_to_kernel_id.find( key );
            if( ( key_it != this->m_key_to_kernel_id.end() ) ||
                ( key_it->second != _this_t::ILLEGAL_KERNEL_ID ) )
            {
                return kernel_config_id;
            }

            auto init_param_it = this->m_key_to_kernel_init_params.find( key );
            if( init_param_it != this->m_key_to_kernel_init_params.end() )
            {
                size_t const num_kernel_args = init_param_it->second.first;
                std::string const& kernel_name = init_param_it->second.second;

                kernel_config_id = this->doInitKernelConfig(
                    lock, key, num_kernel_args, kernel_name.c_str() );
            }
        }

        return kernel_config_id;
    }

    KernelConfigStore::kernel_id_t KernelConfigStore::initKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_args,
        char const* SIXTRL_RESTRICT kernel_name )
    {
        return this->doInitKernelConfig(
            lock, key, num_kernel_args, kernel_name );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::kernel_id_t
    KernelConfigStore::initDefaultControllerKernels(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        using _this_t = st::KernelConfigStore;
        _this_t::kernel_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_ID;

        if( ( input_key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            _this_t::key_t key( input_key );
            key.setPurpose( st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );

            kernel_config_id = this->kernelId( key );

            if( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID )
            {
                kernel_config_id = this->initKernelConfig( lock, key );
            }
        }

        return kernel_config_id;
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureRemapBufferKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureRemapBufferKernelConfig(
                lock, kernel_config_id );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() ) status = conf->update();
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t KernelConfigStore::initDefaultTrackJobKernels(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        using _this_t = st::KernelConfigStore;
        using kernel_id_t = _this_t::kernel_id_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( input_key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            kernel_id_t const track_until_kernel_conf_id =
                this->initTrackUntilKernelConfig( lock, input_key );

            kernel_id_t const track_elem_by_elem_kernel_conf_id =
                this->initTrackElemByElemKernelConfig( lock, input_key );

            kernel_id_t const track_line_kernel_conf_id =
                this->initTrackLineKernelConfig( lock, input_key );

            kernel_id_t const fetch_particle_addr_kernel_conf_id =
                this->initFetchParticlesAddrKernelConfig( lock, input_key );

            kernel_id_t const assign_beam_mon_out_kernel_conf_id =
                this->initAssignBeamMonitorOutputKernelConfig(
                    lock, input_key );

            kernel_id_t const assign_elem_by_elem_out_kernel_conf_id =
                this->initAssignElemByElemOutputKernelConfig(
                    lock, input_key );

            if( ( track_until_kernel_conf_id != _this_t::ILLEGAL_KERNEL_ID ) &&
                ( track_elem_by_elem_kernel_conf_id !=
                    _this_t::ILLEGAL_KERNEL_ID ) &&
                ( track_line_kernel_conf_id != _this_t::ILLEGAL_KERNEL_ID ) &&
                ( fetch_particle_addr_kernel_conf_id !=
                    _this_t::ILLEGAL_KERNEL_ID ) &&
                ( assign_beam_mon_out_kernel_conf_id !=
                    _this_t::ILLEGAL_KERNEL_ID ) &&
                ( assign_elem_by_elem_out_kernel_conf_id !=
                    _this_t::ILLEGAL_KERNEL_ID ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureDefaultTrackJobKernels(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        st::ArgumentBase& SIXTRL_RESTRICT_REF beam_elements_buffer,
        KernelConfigStore::size_type const until_turn_elem_by_elem )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initDefaultTrackJobKernels( lock, input_key,
            particles_arg.ptrCObjectsBuffer(), num_particle_sets, pset_begin,
                beam_elements_arg.ptrCObjectsBuffer(),
                    until_turn_elem_by_elem );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureDefaultTrackJobKernels(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        st::ArgumentBase& SIXTRL_RESTRICT_REF belems_buffer,
        KernelConfigStore::size_type const until_turn_elem_by_elem )
    {
        return this->initDefaultTrackJobKernels( lock, input_key,
            particles_arg.ptrCObjectsBuffer(), num_particle_sets, pset_begin,
                beam_elements_arg.ptrCObjectsBuffer(),
                    until_turn_elem_by_elem );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureDefaultTrackJobKernels(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT belems_buffer,
        KernelConfigStore::size_type const until_turn_elem_by_elem )
    {
        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;
        using  out_buffer_flags_t = _this_t::out_buffer_flags_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( input_key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( pbuffer != nullptr ) && ( num_particle_sets > size_t{ 0 } ) &&
            ( pset_begin != nullptr ) && ( belems_buffer != nullptr ) )
        {
            _this_t::key_t key( input_key );

            out_buffer_flags_t out_flags = ::NS(OUTPUT_BUFFER_NONE);
            size_t total_num_particles = size_t{ 0 };
            size_t num_objs_in_particle_buffer = size_t{ 0 };
            size_t num_beam_monitors = size_t{ 0 };

            status = this->doGetParametersFromParticlesBufferAndBeamElements(
                lock, pbuffer, num_particle_sets, pset_begin, belems_buffer,
                    until_turn_elem_by_elem, &out_flags, &total_num_particles,
                        nullptr, &num_objs_in_particle_buffer,
                            nullptr, &num_beam_monitors );

            if( total_num_particles > size_t{ 0 } )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );
                status = this->configureTrackUntilKernelConfig(
                    lock, this->kernelId( lock, key ), total_num_particles );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_ELEM_BY_ELEM );
                    status = this->configureTrackElemByElemKernelConfig( lock,
                        this->kernelId( lock, key ), total_num_particles );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_LINE );
                    status = this->configureTrackLineKernelConfig( lock,
                        this->kernelId( lock, key ), total_num_particles );
                }
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( num_objs_in_particle_buffer > size_t{ 0 } ) )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES );
                status = this->configureFetchParticlesAddrKernelConfig( lock,
                    this->kernelId( lock, key ), num_objs_in_particle_buffer );
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( ::NS(OutputBuffer_requires_beam_monitor_output)( out_flags ) ) &&
                ( num_beam_monitors > size_t{ 0 } ) )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_ASSIGN_BEAM_MONITOR_OUTPUT );
                status = this->configureAssignOutputBeamMonitorKernelConfig(
                    lock, this->kernelId( lock, key ), num_beam_monitors );
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( ::NS(OutputBuffer_requires_elem_by_elem_output)( out_flags ) ) )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_ASSIGN_ELEM_BY_ELEM_OUTPUT );
                status = this->configureAssignOutputElemByElemKernelConfig(
                    lock, this->kernelId( lock, key ) );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::kernel_id_t
    KernelConfigStore::initTrackUntilKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        return this->doInitPredefinedKernel( lock, input_key,
            st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );

    }

    KernelConfigStore::kernel_id_t
    KernelConfigStore::initTrackElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        return this->doInitPredefinedKernel( lock, input_key,
            st::KERNEL_CONFIG_PURPOSE_TRACK_ELEM_BY_ELEM );
    }

    KernelConfigStore::kernel_id_t KernelConfigStore::initTrackLineKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        return this->doInitPredefinedKernel( lock, input_key,
            st::KERNEL_CONFIG_PURPOSE_TRACK_LINE );
    }

    KernelConfigStore::kernel_id_t
    KernelConfigStore::initFetchParticlesAddrKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        return this->doInitPredefinedKernel( lock, input_key,
            st::KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES );
    }

    KernelConfigStore::kernel_id_t
    KernelConfigStore::initAssignBeamMonitorOutputKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        return this->doInitPredefinedKernel( lock, input_key,
            st::KERNEL_CONFIG_PURPOSE_ASSIGN_BEAM_MONITOR_OUTPUT );
    }

    KernelConfigStore::kernel_id_t
    KernelConfigStore::initAssignElemByElemOutputKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        return this->doInitPredefinedKernel( lock, input_key,
            st::KERNEL_CONFIG_PURPOSE_ASSIGN_ELEM_BY_ELEM_OUTPUT );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackUntilKernelConfig( lock, kernel_config_id,
            particles_arg.ptrCObjectsBuffer(), num_particle_sets, pset_begin );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackUntilKernelConfig( lock, kernel_config_id,
            particles_arg.ptrCObjectsBuffer(), num_particle_sets, pset_begin );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::size_type const total_num_particles_in_sets )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( total_num_particles_in_sets > _this_t::size_type{ 0 } ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureTrackKernelConfig(
                lock, kernel_config_id, total_num_particles_in_sets );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() ) status = conf->update();
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackUntilKernelConfig( lock, kernel_config_id,
            ::NS(Particles_buffer_get_total_num_of_particles_on_particle_sets)(
                pbuffer, num_particle_sets, pset_begin ) );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        using _this_t = st::KernelConfigStore;
        _this_t::lock_t lock( *this->lockable() );
        return this->configureTrackElemByElemKernelConfig(
            lock, kernel_config_id, particles_arg.ptrCObjectsBuffer(),
                num_particle_sets, pset_begin );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::size_type const total_num_particles_in_sets )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( total_num_particles_in_sets > _this_t::size_type{ 0 } ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureTrackKernelConfig(
                lock, kernel_config_id, total_num_particles_in_sets );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() ) status = conf->update();
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackElemByElemKernelConfig( lock,
            kernel_config_id, particles_arg.ptrCObjectsBuffer(),
                num_particle_sets, pset_begin );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackElemByElemKernelConfig( lock, kernel_config_id,
            ::NS(Particles_buffer_get_total_num_of_particles_on_particle_sets)(
                pbuffer, num_particle_sets, pset_begin ) );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        using _this_t = st::KernelConfigStore;
        _this_t::lock_t lock( *this->lockable() );
        return this->configureTrackLineKernelConfig( lock, kernel_config_id,
            particles_arg.ptrCObjectsBuffer(), num_particle_sets, pset_begin );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::size_type const total_num_particles_in_sets )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( total_num_particles_in_sets > _this_t::size_type{ 0 } ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureTrackKernelConfig(
                lock, kernel_config_id, total_num_particles_in_sets );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() ) status = conf->update();
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    KernelConfigStore::status_t KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackLineKernelConfig( lock, kernel_config_id,
            particles_arg.ptrCObjectsBuffer(), num_particle_sets, pset_begin );
    }

    KernelConfigStore::status_t KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const* SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackLineKernelConfig( lock, kernel_config_id,
            ::NS(Particles_buffer_get_total_num_of_particles_on_particle_sets)(
                pbuffer, num_particle_sets, pset_begin ) );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg )
    {
        st::KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureFetchParticlesAddrKernelConfig( lock,
            kernel_config_id, particles_arg.ptrCObjectsBuffer() );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::size_type const num_objs_in_particle_buffer )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( num_objs_in_particle_buffer > _this_t::size_type{ 0 } ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureFetchParticlesAddrKernelConfig(
                lock, kernel_config_id, num_objs_in_particle_buffer );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() ) status = conf->update();
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg )
    {
        return this->configureFetchParticlesAddrKernelConfig( lock,
            kernel_config_id, particles_arg.ptrCObjectsBuffer() );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        const KernelConfigStore::buffer_t *const SIXTRL_RESTRICT_REF pbuffer )
    {
        return this->configureFetchParticlesAddrKernelConfig(
            lock, kernel_config_id,
                ::NS(ManagedBuffer_get_num_objects)( pbuffer ) );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF beam_elements_arg )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureAssignOutputBeamMonitorKernelConfig( lock,
            kernel_config_id, beam_elements_arg.ptrCObjectsBuffer() );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::size_type const num_beam_monitors )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( num_beam_monitors > _this_t::size_type{ 0 } ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureAssignOutputBeamMonitorKernelConfig(
                lock, kernel_config_id, num_beam_monitors );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() ) status = conf->update();
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        lock_t const& SIXTRL_RESTRICT_REF lock,
        kernel_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg )
    {
        return this->configureAssignOutputBeamMonitorKernelConfig( lock,
            kernel_config_id, beam_elements_arg.ptrCObjectsBuffer() );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        const KernelConfigStore::buffer_t *const
            SIXTRL_RESTRICT_REF belems_buffer )
    {
        return this->configureAssignOutputBeamMonitorKernelConfig( lock,
            kernel_config_id, ::NS(BeamMonitor_get_num_of_beam_monitor_objects)(
                belems_buffer ) );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureAssignOutputElemByElemKernelConfig(
                lock, kernel_config_id, num_beam_monitors );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() ) status = conf->update();
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::setDefaultInitKernelConfigParameters(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_arguments,
        std::string const& SIXTRL_RESTRICT_REF kernel_name )
    {
        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;

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
                it->second.first = num_kernel_args;
                it->second.second = kernel_name;
            }
        }

        return status;
    }

    KernelConfigStore::status_t
    KernelConfigStore::setDefaultInitKernelConfigParameters(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
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
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
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
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
    {
        using _thsi_t = st::KernelConfigStore;

        return ( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
                 ( this->checkLock( lock ) ) &&
                 ( this->m_key_to_kernel_init_params.find( key ) !=
                   this->m_key_to_kernel_init_params.end() ) );
    }

    KernelConfigStore::size_type KernelConfigStore::defaultNumKernelArgs(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
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
                num_kernel_args = it->second.first;
            }
        }

        return num_kernel_args;
    }

    std::string const& KernelConfigStore::defaultKernelName(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
    {
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

        return it->second.second;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::kernel_id_t KernelConfigStore::doInitKernelConfig(
        KernelConfigStore::lock_t cont& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_args,
        char const* SIXTRL_RESTRICT name )
    {
        ( void )lock;
        ( void )key;
        ( void )num_kernel_args;
        ( void )name;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    KernelConfigStore::kernel_id_t KernelConfigStore::doAddKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::ptr_kernel_config_t&& ptr_kernel_config )
    {
        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;
        using  key_t  = _this_t::key_t;

        _this_t::kernel_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_ID;

        SIXTRL_ASSERT( key.archId() != _this_t::ARCH_ILLEGAL );

        if( ( ptr_kernel_config.get() != nullptr ) &&
            ( this->checkLock( lock ) ) )
        {
            SIXTRL_ASSERT( key.archId() == ptr_kernel_config->archId() );
            SIXTRL_ASSERT( key.purpose() == ptr_kernel_config->purpose() );
            SIXTRL_ASSERT( ( key.archId() == st::ARCH_VARIANT_NONE ) ||
                ( ptr_kernel_config->areVariantFlagsSet( key.archId() ) ) );

            SIXTRL_ASSERT( key.hasConfigStr() ==
                ptr_kernel_config->hasConfigStr() );

            SIXTRL_ASSERT( ( !key.hasConfigStr() ) ||
              (  key.configStr().compare( ptr_kernel_config.configStr() ) == 0 ) );

            SIXTRL_ASSERT( this->m_key_to_kernel_id.find( key ) ==
                           this->m_key_to_kernel_id.end() );

            _this_t::kernel_id_t temp_id = static_cast< _this_t::kernel_id_t >(
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
        KernelConfigStore::kernel_id_t const kernel_config_id )
    {
        using _this_t = st::KernelConfigStore;
        using size_t  = _this_t::size_type;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( kernel_config_id >= _this_t::kernel_id_t{ 0 } ) &&
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

                        this->m_key_to_kernel_id.erase( *find_key_it );
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

    KernelConfigStore::status_t
    KernelConfigStore::doConfigureRemapBufferKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id )
    {
        ( void )lock;
        ( void )kernel_config_id;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    KernelConfigStore::status_t
    KernelConfigStore::doConfigureTrackKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        size_type const total_num_particles_in_sets )
    {
        ( void )lock;
        ( void )kernel_config_id;
        ( void )pbuffer;
        ( void )num_particle_sets;
        ( void )pset_begin;
        ( void )ptr_total_num_particles_in_sets;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    KernelConfigStore::status_t
    KernelConfigStore::doConfigureFetchParticlesAddrKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::size_type const num_objs_in_particle_buffer )
    {
        ( void )lock;
        ( void )kernel_config_id;
        ( void )num_objs_in_particle_buffer;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    KernelConfigStore::status_t
    KernelConfigStore::doConfigureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::size_type const num_beam_monitors )
    {
        ( void )lock;
        ( void )kernel_config_id;
        ( void )num_beam_monitors;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    KernelConfigStore::status_t
    KernelConfigStore::doConfigureAssignOutputElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id )
    {
        ( void )lock;
        ( void )kernel_config_id;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* ----------------------------------------------------------------- */

    KernelConfigStore::out_buffer_flags_t
    KernelConfigStore::doGetParametersFromParticlesBufferAndBeamElements(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT belems_buffer,
        KernelConfigStore::size_type const until_turn_elem_by_elem,
        KernelConfigStore::particle_index_t const at_elem_start_index,
        KErnelConfigStore::out_buffer_flags_t* SIXTRL_RESTRICT ptr_out_flags,
        KernelConfigStore::size_type*
            SIXTRL_RESTRICT ptr_total_num_particles_in_sets,
        KernelConfigStore::size_type*
            SIXTRL_RESTRICT ptr_total_num_particle_sets,
        KernelConfigStore::size_type* SIXTRL_RESTRICT ptr_num_objs_in_buffer,
        KernelConfigStore::size_type* SIXTRL_RESTRICT ptr_num_elem_by_elem_objs,
        KernelConfigStore::size_type* SIXTRL_RESTRICT ptr_num_beam_monitors )
    {
        using _this_t = st::KernelConfigStore;
        using out_buffer_flags_t = _this_t::output_buffer_flag_t;
        using status_t           = _this_t::status_t;
        using particles_t        = _this_t::particle_index_t;
        using pindex_t           = ::NS(particle_index_t);

        status_t ret = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->checkLock( lock ) ) &&
            ( input_key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( pbuffer != nullptr ) && ( num_particle_sets > size_t{ 0 } ) &&
            ( pset_begin != nullptr ) && ( belem_buffer != nullptr ) )
        {
            size_t num_elem_by_elem_objects = size_t{ 0 };

            pindex_t min_particle_id, max_particle_id, min_at_element,
                     max_at_element, min_at_turn, max_at_turn;

            ret = ::NS(OutputBuffer_find_min_max_attributes_on_particle_sets)(
                pbuffer, num_particle_sets, pset_begin, belem_buffer,
                    &min_particle_id, &max_particle_id, &min_at_element,
                    &max_at_element, &min_at_turn, &max_at_turn,
                        &num_elem_by_elem_objects, at_elem_start_index );

            if( ret == st::ARCH_STATUS_SUCCESS )
            {
                if( ptr_num_elem_by_elem_objs != nullptr )
                {
                    *ptr_num_elem_by_elem_objs = num_elem_by_elem_objects;
                }

                if( ptr_total_num_particles != nullptr )
                {
                    size_t total_num_particles = size_t{ 0 };
                    size_t const* pset_it  = pset_begin;
                    size_t const* pset_end = pset_begin;
                    std::advance( pset_end, num_particle_sets );

                    for( ; pset_it != pset_end ; ++pset_it )
                    {
                        total_num_particles += *pset_it;
                    }

                    *ptr_total_num_particles = total_num_particles;
                }

                if( ( ptr_out_flags != nullptr ) ||
                    ( ptr_num_beam_monitors != nullptr ) )
                {
                    size_t num_beam_monitors = size_t{ 0 };

                    out_buffer_flags_t const out_flags =
                    ::NS(OutputBuffer_required_for_tracking_detailed)(
                        belem_buffer, min_particle_id, max_particle_id,
                        min_at_element, max_at_element, min_at_turn,
                        max_at_turn, until_turn_elem_by_elem,
                        &num_beam_monitors );

                    if( ptr_out_flags != nullptr )
                    {
                        *ptr_out_flags = out_flags;
                    }

                    if( ptr_num_beam_monitors != nullptr )
                    {
                        *ptr_num_beam_monitors = num_beam_monitors;
                    }
                }

                if( ptr_total_num_particles_in_sets != nullptr )
                {
                    *ptr_total_num_particles_in_sets =
                    ::NS(Particles_buffer_get_total_num_of_particles_on_particle_sets)(
                        pbuffer, num_particle_sets, pset_begin );
                }

                if( ptr_total_num_particle_sets != nullptr )
                {
                    *ptr_total_num_particle_sets =
                    ::NS(Particles_buffer_get_num_of_particle_blocks)( pbuffer );
                }

                if( ptr_num_objs_in_buffer != nullptr )
                {
                    *ptr_num_objs_in_buffer =
                        ::NS(Buffer_get_num_objects)( pbuffer );
                }
            }
        }

        return ret;
    }

    /* --------------------------------------------------------------------- */

    bool KernelConfigStore::doCheckKeyAndKernelConfigAreSync(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::kernel_id_t const
            kernel_config_id ) const SIXTRL_NOEXCEPT
    {
        bool is_sync = false;

        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) &&
            ( this->m_stored_kernel_configs.size() > static_cast< size_t >(
                kernel_config_id ) ) &&
            ( this->m_stored_kernel_configs[ kernel_config_id
                    ].get() != nullptr ) &&
            ( this->m_stored_kernel_configs[ kernel_config_id
                    ]->purpose() == key.purpose() ) &&
            ( ( key.variant() == _this_t::ARCH_VARIANT_NONE ) ||
              ( this->m_stored_kernel_configs[ kernel_config_id
                    ]->areVariantFlagsSet( key.variant() ) ) ) &&
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

    KernelConfigStore::kernel_id_t KernelConfigStore::doInitPredefinedKernel(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key,
        KernelConfigStore::purpose_t const predefined_purpose )
    {
        using _this_t = st::KernelConfigStore;
        _this_t::kernel_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_ID;

        if( ( input_key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            if( input_key.purpose() == predefined_purpose )
            {
                kernel_config_id = this->initKernelConfig( lock, input_key );
            }
            else
            {
                _this_t::key_t key( input_key );
                key.setPurpose( predefined_purpose );
                kernel_config_id = this->initKernelConfig( lock, key );
            }
        }

        return kernel_config_id;
    }
}

/* end: sixtracklib/common/control/kernel_config_store.cpp */
