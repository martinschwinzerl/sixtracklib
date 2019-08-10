#include "sixtracklib/cuda/control/kernel_config_store.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <utility>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/generated/namespace.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/kernel_config.hpp"
#include "sixtracklib/common/control/kernel_config_key.hpp"
#include "sixtracklib/common/control/kernel_config_store.hpp"

#include "sixtracklib/cuda/definitions.h"
#include "sixtracklib/cuda/control/kernel_config.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    CudaKernelConfigStore::kernel_id_t
    CudaKernelConfigStore::doInitKernelConfig(
        CudaKernelConfigStore::lock_t cont& SIXTRL_RESTRICT_REF lock,
        CudaKernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        CudaKernelConfigStore::size_type const num_kernel_args,
        char const* SIXTRL_RESTRICT name )
    {
        using  _this_t = st::CudaKernelConfigStore;
        using config_t = _this_t::kernel_config_t;
        using base_conf_t = _this_t::kernel_config_base_t;

        _this_t::kernel_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_ID;

        if( ( key.archId() == st::ARCHITECTURE_CUDA ) && ( key.hasNode() ) &&
            ( this->checkLock( lock ) ) )
        {
            return std::unique_ptr< base_conf_t >( new config_t(
                num_kernel_args, key.purpose(), key.variant(),
                config_t::DEFAULT_BLOCK_DIMENSIONS,
                config_t::DEFAULT_THREADS_PER_BLOCK_DIMENSIONS, name,
                config_t::DEFAULT_SHARED_MEM_PER_BLOCK,
                config_t::DEFAULT_SHARED_MEM_PER_THREAD,
                config_t::DEFAULT_MAX_BLOCK_SIZE_LIMIT,
                config_t::DEFAULT_WARP_SIZE,
                key.ptrConfigStr() ) );
        }

        return kernel_config_id;
    }

    /* --------------------------------------------------------------------- */

    CudaKernelConfigStore::kernel_id_t
    CudaKernelConfigStore::doAddKernelConfig(
        CudaKernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaKernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        CudaKernelConfigStore::ptr_kernel_config_t&& ptr_kernel_config )
    {
        using _this_t = CudaKernelConfigStore;
        using _base_t = _this_t::_base_config_store_t;
        using kernel_config_t = _this_t::kernel_config_t;
        using kernel_config_base_t = _this_t::kernel_config_base_t:

        _this_t::kernel_id_t kernel_id = _this_t::ILLEGAL_KERNEL_ID;
        kernel_config_base_t const* ptr_config_base = ptr_kernel_config.get();

        kernel_config_t* ptr_cuda_config = ( ptr_config_base != nullptr )
                ? ptr_config_base->asDerivedKernelConfig< kernel_config_t >(
                    st::ARCHITECTURE_CUDA ) : nullptr;

        if( ( this->checkLock( lock ) ) &&
            ( key.archId() == st::ARCHITECTURE_CUDA ) &&
            ( key.hasNodeId() ) && ( ptr_cuda_config != nullptr ) )
        {
            kernel_id = _base_t::doAddKernelConfig(
                lock, key, std::move( ptr_kernel_config ) );
        }

        return kernel_id;
    }

    /* --------------------------------------------------------------------- */

    CudaKernelConfigStore::status_t
    CudaKernelConfigStore::doConfigureRemapBufferKernelConfig(
        CudaKernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaKernelConfigStore::kernel_id_t const kernel_config_id )
    {
        using _this_t = st::CudaKernelConfigStore;
        using size_t = _this_t::size_type;
        using config_t = _this_t::kernel_config_t;
        using base_config_t = _this_t::kernel_config_base_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            base_config_t* ptr_base = this->ptrKernelConfigBase(
                lock, kernel_config_id );

            config_t* ptr_config = ( ptr_base != nullptr )
                ? ptr_base->asDerivedKernelConfig< config_t >( this->archId() )
                : nullptr;

            if( ( ptr_config != nullptr ) && ( ptr_config->purpose() ==
                    st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER ) )
            {
                status = ptr_config->setBlocks( size_t{ 1 } );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = ptr_config->setBlockOffsets( size_t{ 0 } );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = ptr_config->setThreadsPerBlock( size_t{ 1 } );
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    CudaKernelConfigStore::status_t
    CudaKernelConfigStore::doConfigureTrackKernelConfig(
        CudaKernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaKernelConfigStore::kernel_id_t const kernel_config_id,
        CudaKernelConfigStore::c_buffer_t const* SIXTRL_RESTRICT pbuffer,
        CudaKernelConfigStore::size_type const num_particle_sets,
        CudaKernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        CudaKernelConfigStore::size_type const total_num_particles_in_sets )
    {
        using _this_t = st::CudaKernelConfigStore;
        using size_t = _this_t::size_type;
        using config_t = _this_t::kernel_config_t;
        using base_config_t = _this_t::kernel_config_base_t;
        using purpose_t = _this_t::purpose_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( total_num_particles_in_sets > size_t{ 0 } ) &&
            ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            base_config_t* ptr_base = this->ptrKernelConfigBase(
                lock, kernel_config_id );

            config_t* ptr_config = ( ptr_base != nullptr )
                ? ptr_base->asDerivedKernelConfig< config_t >( this->archId() )
                : nullptr;

            if( ptr_config != nullptr )
            {
                purpose_t const p = ptr_config->purpose();

                if( ( p == st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN ) ||
                    ( p == st::KERNEL_CONFIG_PURPOSE_TRACK_ELEM_BY_ELEM ) ||
                    ( p == st::KERNEL_CONFIG_PURPOSE_TRACK_LINE ) )
                {
                    size_t const DEFAULT_THREADS_PER_BLOCK = size_t{ 128 };
                    size_t num_blocks = total_num_particles_in_sets /
                        DEFAULT_THREADS_PER_BLOCK;

                    if( ( num_blocks * DEFAULT_THREADS_PER_BLOCK ) <
                         total_num_particles_in_sets )
                    {
                        ++num_blocks;
                    }

                    status = ptr_config->setBlocks( num_blocks );

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        status = ptr_config->setBlockOffsets( size_t{ 0 } );
                    }

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        status = ptr_config->setThreadsPerBlock(
                            DEFAULT_THREADS_PER_BLOCK );
                    }
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    CudaKernelConfigStore::status_t
    CudaKernelConfigStore::doConfigureFetchParticlesAddrKernelConfig(
        CudaKernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaKernelConfigStore::kernel_id_t const kernel_config_id,
        CudaKernelConfigStore::size_type const num_objs_in_particle_buffer )
    {
        using _this_t = st::CudaKernelConfigStore;
        using size_t = _this_t::size_type;
        using config_t = _this_t::kernel_config_t;
        using base_config_t = _this_t::kernel_config_base_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( num_objs_in_particle_buffer > size_t{ 0 } ) &&
            ( this->checkLock( lock ) ) )
        {
            base_config_t* ptr_base = this->ptrKernelConfigBase(
                lock, kernel_config_id );

            config_t* ptr_config = ( ptr_base != nullptr )
                ? ptr_base->asDerivedKernelConfig< config_t >( this->archId() )
                : nullptr;

            if( ( ptr_config != nullptr ) && ( ptr_config->purpose() ==
                    st::KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES ) )
            {
                size_t const DEFAULT_THREADS_PER_BLOCK = size_t{ 128 };
                size_t num_blocks = num_objs_in_particle_buffer /
                    DEFAULT_THREADS_PER_BLOCK;

                if( ( num_blocks * DEFAULT_THREADS_PER_BLOCK ) <
                        num_objs_in_particle_buffer )
                {
                    ++num_blocks;
                }

                status = ptr_config->setBlocks( num_blocks );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = ptr_config->setBlockOffsets( size_t{ 0 } );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = ptr_config->setThreadsPerBlock(
                        DEFAULT_THREADS_PER_BLOCK );
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    CudaKernelConfigStore::status_t
    CudaKernelConfigStore::doConfigureAssignOutputBeamMonitorKernelConfig(
        CudaKernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaKernelConfigStore::kernel_id_t const kernel_config_id,
        CudaKernelConfigStore::size_type const num_beam_monitors )
    {
        using _this_t = st::CudaKernelConfigStore;
        using size_t = _this_t::size_type;
        using config_t = _this_t::kernel_config_t;
        using base_config_t = _this_t::kernel_config_base_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( num_beam_monitors > size_t{ 0 } ) && ( this->checkLock( lock ) ) )
        {
            base_config_t* ptr_base = this->ptrKernelConfigBase(
                lock, kernel_config_id );

            config_t* ptr_config = ( ptr_base != nullptr )
                ? ptr_base->asDerivedKernelConfig< config_t >( this->archId() )
                : nullptr;

            if( ( ptr_config != nullptr ) && ( ptr_config->purpose() ==
                    st::KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES ) )
            {
                size_t const DEFAULT_THREADS_PER_BLOCK = size_t{ 128 };
                size_t num_blocks = num_beam_monitors / DEFAULT_THREADS_PER_BLOCK;

                if( ( num_blocks * DEFAULT_THREADS_PER_BLOCK ) <
                        num_beam_monitors )
                {
                    ++num_blocks;
                }

                status = ptr_config->setBlocks( num_blocks );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = ptr_config->setBlockOffsets( size_t{ 0 } );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = ptr_config->setThreadsPerBlock(
                        DEFAULT_THREADS_PER_BLOCK );
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    CudaKernelConfigStore::status_t
    CudaKernelConfigStore::doConfigureAssignOutputElemByElemKernelConfig(
        CudaKernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaKernelConfigStore::kernel_id_t const kernel_config_id )
    {
        using _this_t = st::CudaKernelConfigStore;
        using size_t = _this_t::size_type;
        using config_t = _this_t::kernel_config_t;
        using base_config_t = _this_t::kernel_config_base_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( num_objs_in_particle_buffer > size_t{ 0 } ) &&
            ( this->checkLock( lock ) ) )
        {
            base_config_t* ptr_base = this->ptrKernelConfigBase(
                lock, kernel_config_id );

            config_t* ptr_config = ( ptr_base != nullptr )
                ? ptr_base->asDerivedKernelConfig< config_t >( this->archId() )
                : nullptr;

            if( ( ptr_config != nullptr ) && ( ptr_config->purpose() ==
                    st::KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES ) )
            {
                status = ptr_config->setBlocks( size_t{ 1 } );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = ptr_config->setBlockOffsets( size_t{ 0 } );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = ptr_config->setThreadsPerBlock( size_t{ 1 } );
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    CudaKernelConfigStore::status_t
    CudaKernelConfigStore::doInitDefaultKernelConfigInitParams(
        CudaKernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        CudaKernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        using _this_t = st::CudaKernelConfigStore;
        using  size_t = _this_t::size_type;
        using  key_t  = _this_t::key_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( input_key.archId() == st::ARCHITECTURE_CUDA ) &&
            ( input_key.hasNodeId() ) &&
            ( input_key.platformId() != _this_t::ILLEGAL_PLATFORM_ID ) &&
            ( input_key.deviceId() == _this_t::device_id_t{ 0 } ) &&
            ( ( variant == st::ARCH_VARIANT_NONE ) ||
              ( variant == st::ARCH_VARIANT_DEBUG ) ) &&
            ( this->checkLock( lock ) ) )
        {
            bool const for_debug_mode = ( variant == st::ARCH_VARIANT_DEBUG );
            key_t key( input_key );

            std::string kernel_name;
            kernel_name.reserve( size_t{ 256 } );

            /* ------------------------------------------------------------- */
            /* remap debug buffer */

            key.setPurpose( st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );
            kernel_name.clear();
            kernel_name = SIXTRL_C99_NAMESPACE_PREFIX_STR;

            if( for_debug_mode )
            {
                kernel_name += "Buffer_remap_cuda_wrapper";
                status = this->setDefaultInitKernelConfigParameters(
                    lock, key, size_t{ 2 }, kernel_name );
            }
            else
            {
                kernel_name += "Buffer_remap_cuda_debug_wrapper";
                status = this->setDefaultInitKernelConfigParameters(
                    lock, key, size_t{ 3 }, kernel_name );
            }

            /* ------------------------------------------------------------- */
            /* track until turn */

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );
                kernel_name.clear();
                kernel_name = SIXTRL_C99_NAMESPACE_PREFIX_STR;
                kernel_name += "Track_particles_until_turn_cuda_wrapper";

                size_t const num_kernel_args =
                    ( for_debug_mode ) ? size_t{ 4 } : size_t{ 5 };

                status = this->setDefaultInitKernelConfigParameters(
                    lock, key, num_kernel_args, kernel_name );
            }

            /* ------------------------------------------------------------- */
            /* track elem by elem turn */

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );
                kernel_name.clear();
                kernel_name = SIXTRL_C99_NAMESPACE_PREFIX_STR;
                kernel_name +=
                    "Track_particles_elem_by_elem_until_turn_cuda_wrapper";

                size_t const num_kernel_args =
                    ( for_debug_mode ) ? size_t{ 5 } : size_t{ 6 };

                status = this->setDefaultInitKernelConfigParameters(
                    lock, key, num_kernel_args, kernel_name );
            }

            /* ------------------------------------------------------------- */
            /* track line turn */

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );
                kernel_name.clear();
                kernel_name = SIXTRL_C99_NAMESPACE_PREFIX_STR;
                kernel_name += "Track_particles_line_cuda_wrapper";

                size_t const num_kernel_args =
                    ( for_debug_mode ) ? size_t{ 6 } : size_t{ 7 };

                status = this->setDefaultInitKernelConfigParameters(
                    lock, key, num_kernel_args, kernel_name );
            }

            /* ------------------------------------------------------------- */
            /* fetch fetch particles addr */

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );
                kernel_name.clear();
                kernel_name = SIXTRL_C99_NAMESPACE_PREFIX_STR;
                kernel_name += "Particles_buffer_store_all_addresses_cuda_wrapper";

                size_t const num_kernel_args =
                    ( for_debug_mode ) ? size_t{ 2 } : size_t{ 3 };

                status = this->setDefaultInitKernelConfigParameters(
                    lock, key, num_kernel_args, kernel_name );
            }

            /* ------------------------------------------------------------- */
            /* fetch assign output beam monitor */

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );
                kernel_name.clear();
                kernel_name = SIXTRL_C99_NAMESPACE_PREFIX_STR;
                kernel_name +=
                    "BeamMonitor_assign_out_buffer_from_offset_cuda_wrapper";

                size_t const num_kernel_args =
                    ( for_debug_mode ) ? size_t{ 4 } : size_t{ 5 };

                status = this->setDefaultInitKernelConfigParameters(
                    lock, key, num_kernel_args, kernel_name );
            }

            /* ------------------------------------------------------------- */
            /* fetch assign output elem by elem */

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );
                kernel_name.clear();
                kernel_name = SIXTRL_C99_NAMESPACE_PREFIX_STR;
                kernel_name +=
                    "ElemByElemConfig_assign_out_buffer_from_offset_cuda_wrapper";

                size_t const num_kernel_args =
                    ( for_debug_mode ) ? size_t{ 3 } : size_t{ 4 };

                status = this->setDefaultInitKernelConfigParameters(
                    lock, key, num_kernel_args, kernel_name );
            }
        }

        return status;
    }
}

/* end: sixtracklib/cuda/control/kernel_config_store.cpp */
