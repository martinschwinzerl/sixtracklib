#ifndef SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_STORE_CXX_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_STORE_CXX_HPP__


#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <atomic>
    #include <cstddef>
    #include <cstdlib>
    #include <map>
    #include <memory>
    #include <mutex>
    #include <set>
    #include <string>
    #include <thread>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/kernel_config_key.hpp"
    #include "sixtracklib/common/control/kernel_config_base.hpp"
   #include "sixtracklib/common/buffer.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/output/output_buffer.h"
    #include "sixtracklib/common/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

namespace SIXTRL_CXX_NAMESPACE
{
    class ArgumentBase;

    class KernelConfigStore
    {
        public:

        using status_t              = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using key_t                 = SIXTRL_CXX_NAMESPACE::KernelConfigKey;
        using kernel_config_base_t  = SIXTRL_CXX_NAMESPACE::KernelConfigBase;
        using buffer_t              = SIXTRL_CXX_NAMESPACE::Buffer;
        using particle_index_t      = ::NS(particle_index_t);
        using c_buffer_t            = buffer_t::c_api_t;
        using kernel_id_t           = kernel_config_base_t::kernel_id_t;
        using arch_id_t             = kernel_config_base_t::arch_id_t;
        using node_id_t             = kernel_config_base_t::node_id_t;
        using purpose_t             = kernel_config_base_t::purpose_t;
        using variant_t             = kernel_config_base_t::variant_t;
        using size_type             = kernel_config_base_t::size_type;
        using platform_id_t         = node_id_t::platform_id_t;
        using device_id_t           = node_id_t::device_id_t;

        using lockable_t            = std::mutex;
        using lock_t                = std::unique_lock< lockable_t >;
        using ptr_kernel_config_t   = std::unique_ptr< kernel_config_base_t >;

        static constexpr kernel_id_t ILLEGAL_KERNEL_ID =
            SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_KERNEL_ID;

        static constexpr platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static constexpr device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static constexpr arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static constexpr purpose_t DEFAULT_KERNEL_PURPOSE =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;

        static constexpr variant_t DEFAULT_KERNEL_VARIANT =
            SIXTRL_CXX_NAMESPACE::ARCH_VARIANT_NONE;

        SIXTRL_HOST_FN static purpose_t
        NextUserdefinedPurposeId() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN KernelConfigStore();

        SIXTRL_HOST_FN KernelConfigStore(
            KernelConfigStore const& SIXTRL_RESTRICT_REF store ) = default;

        SIXTRL_HOST_FN KernelConfigStore(
            KernelConfigStore&& store ) = default;

        SIXTRL_HOST_FN KernelConfigStore& operator=(
            KernelConfigStore const& SIXTRL_RESTRICT_REF rhs ) = default;

        SIXTRL_HOST_FN KernelConfigStore& operator=(
            KernelConfigStore&& rhs ) = default;

        SIXTRL_HOST_FN virtual ~KernelConfigStore() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_id_t addKernelConfig(
            key_t const& SIXTRL_RESTRICT_REF key,
            ptr_kernel_config_t&& kernel_config );

        SIXTRL_HOST_FN status_t addKernelConfig(
            key_t const& SIXTRL_RESTRICT_REF key,
            kernel_id_t const kernel_config_id );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN kernel_id_t addKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            ptr_kernel_config_t&& kernel_config );

        SIXTRL_HOST_FN status_t addKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            kernel_id_t const kernel_config_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t removeKernelConfig(
            key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN status_t removeKernelConfig(
            kernel_config_base_t const& SIXTRL_RESTRICT_REF kernel_config );

        SIXTRL_HOST_FN status_t removeKernelConfig(
            kernel_id_t const kernel_id );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t removeKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN status_t removeKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_base_t const& SIXTRL_RESTRICT_REF kernel_config );

        SIXTRL_HOST_FN status_t removeKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type numStoredKernels() const;
        SIXTRL_HOST_FN size_type numKeys( kernel_id_t const kernel_id ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN size_type numStoredKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numKeys(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasKernel(
            key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN bool hasKernel( kernel_config_base_t const&
            SIXTRL_RESTRICT_REF kernel_config ) const;

        SIXTRL_HOST_FN bool hasKernel( arch_id_t const arch_id,
            purpose_t const purpose, variant_t const variant,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const;

        SIXTRL_HOST_FN bool hasKernel(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose, variant_t const variant,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const;

        SIXTRL_HOST_FN bool hasKernel( kernel_id_t const kernel_id ) const;

        SIXTRL_HOST_FN kernel_id_t kernelId(
            key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN kernel_id_t kernelId(
            kernel_config_base_t const& SIXTRL_RESTRICT_REF kernel_config );

        SIXTRL_HOST_FN kernel_id_t kernelId( arch_id_t const arch_id,
            purpose_t const purpose, variant_t const variant,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const;

        SIXTRL_HOST_FN kernel_id_t kernelId(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose, variant_t const variant,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool hasKernel( lock_t const& SIXTRL_RESTRICT_REF lock,
                        key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN bool hasKernel( lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_base_t const& SIXTRL_RESTRICT_REF kernel_conf ) const;

        SIXTRL_HOST_FN bool hasKernel( lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            purpose_t const purpose, variant_t const variant,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasKernel( lock_t const& SIXTRL_RESTRICT_REF lock,
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose, variant_t const variant,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasKernel(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_id_t kernelId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_id_t kernelId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_base_t const& SIXTRL_RESTRICT_REF
                kernel_config ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_id_t kernelId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id, purpose_t const purpose,
            variant_t const variant,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_id_t kernelId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose, variant_t const variant,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN key_t findKey(
            kernel_id_t const kernel_config_id ) const;

        SIXTRL_HOST_FN key_t findKey( kernel_id_t const kernel_config_id,
            key_t const& SIXTRL_RESTRICT_REF hint_key ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN key_t findKey( lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN key_t findKey( lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            key_t const& SIXTRL_RESTRICT_REF hint_key ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_base_t const* ptrKernelConfigBase(
            kernel_id_t const kernel_id ) const;

        SIXTRL_HOST_FN kernel_config_base_t* ptrKernelConfigBase(
            kernel_id_t const kernel_id );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN kernel_config_base_t const* ptrKernelConfigBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_base_t* ptrKernelConfigBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_id_t initKernelConfig(
            key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN kernel_id_t initKernelConfig(
            key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args,
            std::string const& SIXTRL_RESTRICT_REF kernel_name );

        SIXTRL_HOST_FN kernel_id_t initKernelConfig(
            key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args,
            char const* SIXTRL_RESTRICT kernel_name );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN kernel_id_t initKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN kernel_id_t initKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args,
            std::string const& SIXTRL_RESTRICT_REF kernel_name );

        SIXTRL_HOST_FN kernel_id_t initKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args,
            char const* SIXTRL_RESTRICT kernel_name );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_id_t initDefaultControllerKernels(
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN status_t configureRemapBufferKernelConfig(
            kernel_id_t const kernel_config_id );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN kernel_id_t initDefaultControllerKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN status_t configureRemapBufferKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t initDefaultTrackJobKernels(
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN status_t configureDefaultTrackJobKernels(
            key_t const& SIXTRL_RESTRICT_REF input_key,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            ArgumentBase& SIXTRL_RESTRICT_REF beam_elements_buffer,
            size_type const until_turn_elem_by_elem );

        SIXTRL_HOST_FN status_t configureDefaultTrackJobKernels(
            key_t const& SIXTRL_RESTRICT_REF input_key,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            buffer_t const& SIXTRL_RESTRICT_REF beam_elements_buffer,
            size_type const until_turn_elem_by_elem );

        SIXTRL_HOST_FN status_t configureDefaultTrackJobKernels(
            key_t const& SIXTRL_RESTRICT_REF input_key,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            const c_buffer_t *const SIXTRL_RESTRICT beam_elements_buffer,
            size_type const until_turn_elem_by_elem );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t initDefaultTrackJobKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN status_t configureDefaultTrackJobKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            ArgumentBase& SIXTRL_RESTRICT_REF beam_elements_buffer,
            size_type const until_turn_elem_by_elem );

        SIXTRL_HOST_FN status_t configureDefaultTrackJobKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            buffer_t const& SIXTRL_RESTRICT_REF beam_elements_buffer,
            size_type const until_turn_elem_by_elem );

        SIXTRL_HOST_FN status_t configureDefaultTrackJobKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            const c_buffer_t *const SIXTRL_RESTRICT beam_elements_buffer,
            size_type const until_turn_elem_by_elem );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_id_t initTrackUntilKernelConfig(
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_id_t initTrackElemByElemKernelConfig(
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_id_t initTrackLineKernelConfig(
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_id_t initFetchParticlesAddrKernelConfig(
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_id_t initAssignBeamMonitorOutputKernelConfig(
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_id_t initAssignElemByElemOutputKernelConfig(
            key_t const& SIXTRL_RESTRICT_REF input_key );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN kernel_id_t initTrackUntilKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_id_t initTrackElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_id_t initTrackLineKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_id_t initFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_id_t initAssignBeamMonitorOutputKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_id_t initAssignElemByElemOutputKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            kernel_id_t const kernel_config_id,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            kernel_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            kernel_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            kernel_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            c_buffer_t const* SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            kernel_id_t const kernel_config_id,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            kernel_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            kernel_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            kernel_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            kernel_id_t const kernel_config_id,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            kernel_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            kernel_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            kernel_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            kernel_id_t const kernel_config_id,
            size_type const num_objs_in_particle_buffer );

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            kernel_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg );

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            kernel_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer );

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            kernel_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            size_type const num_objs_in_particle_buffer );

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg );

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer );

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            kernel_id_t const kernel_config_id,
            size_type const num_beam_monitors );

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            kernel_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF beam_elements_arg );

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            kernel_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF beam_elements_arg );

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            kernel_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT beam_elements_arg );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            size_type const num_beam_monitors );

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg );

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer );

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t configureAssignOutputElemByElemKernelConfig(
            kernel_id_t const kernel_config_id );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t configureAssignOutputElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t setDefaultInitKernelConfigParameters(
            key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_arguments,
            std::string const& SIXTRL_RESTRICT_REF kernel_name );

        SIXTRL_HOST_FN status_t setDefaultInitKernelConfigParameters(
            key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_arguments,
            char const* SIXTRL_RESTRICT kernel_name );

        SIXTRL_HOST_FN status_t removeDefaultInitKernelConfigParameters(
            key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN bool hasDefaultInitKernelConfigParameters(
            key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN size_type defaultNumKernelArgs(
            key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN std::string const& defaultKernelName(
            key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN char const* ptrDefaultKernelName(
            key_t const& SIXTRL_RESTRICT_REF key );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t setDefaultInitKernelConfigParameters(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_arguments,
            std::string const& SIXTRL_RESTRICT_REF kernel_name );

        SIXTRL_HOST_FN status_t setDefaultInitKernelConfigParameters(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_arguments,
            char const* SIXTRL_RESTRICT kernel_name );

        SIXTRL_HOST_FN status_t removeDefaultInitKernelConfigParameters(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN bool hasDefaultInitKernelConfigParameters(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN size_type defaultNumKernelArgs(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN std::string const& defaultKernelName(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN char const* ptrDefaultKernelName(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool checkLock(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void checkLockAndThrowOnError(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        template< typename Derived >
        SIXTRL_HOST_FN Derived const* asDerivedKernelConfigStore() const;

        template< typename Derived >
        SIXTRL_HOST_FN Derived* asDerivedKernelConfigStore();

        protected:

        using keys_set_t           = std::set< key_t >;
        using kernel_init_param_t  = std::tuple< size_type, std::string >;

        using key_kernel_id_map_t  = std::map< key_t, kernel_id_t >;
        using key_init_param_map_t = std::map< key_t, kernel_init_param_t >;
        using kernel_id_keys_map_t = std::map< kernel_id_t, keys_set_t >;
        using kernel_id_counter_t  = std::map< kernel_id_t, size_type >;
        using kernel_config_list_t = std::vector< ptr_kernel_config_t >;
        using out_buffer_flags_t   = ::NS(output_buffer_flag_t);

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual kernel_id_t doInitKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args,
            char const* SIXTRL_RESTRICT name );

        SIXTRL_HOST_FN virtual kernel_id_t doAddKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            ptr_kernel_config_t&& ptr_kernel_config );

        SIXTRL_HOST_FN virtual status_t doRemoveKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_id );

        SIXTRL_HOST_FN virtual status_t doConfigureRemapBufferKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id );

        SIXTRL_HOST_FN virtual status_t doConfigureTrackKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            c_buffer_t const* SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN virtual status_t
        doConfigureFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            size_type const num_objs_in_particle_buffer );

        SIXTRL_HOST_FN virtual status_t
        doConfigureAssignOutputBeamMonitorKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id,
            size_type const num_beam_monitors );

        SIXTRL_HOST_FN virtual status_t
        doConfigureAssignOutputElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_id_t const kernel_config_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t
        doGetParametersFromParticlesBufferAndBeamElements(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            const c_buffer_t *const SIXTRL_RESTRICT pbuffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            const c_buffer_t *const SIXTRL_RESTRICT beam_elements_buffer,
            size_type const until_turn_elem_by_elem,
            particle_index_t const at_elem_start_index,
            out_buffer_flags_t* ptr_output_buffer_flags,
            size_type* SIXTRL_RESTRICT ptr_total_num_particles,
            size_type* SIXTRL_RESTRICT ptr_total_num_particle_sets,
            size_type* SIXTRL_RESTRICT ptr_num_objs_in_buffer,
            size_type* SIXTRL_RESTRICT ptr_num_elem_by_elem_objs,
            size_type* SIXTRL_RESTRICT ptr_num_beam_monitors );

        static std::atomic< purpose_t > NEXT_USERDEFINED_PURPOSE_ID;

        private:

        SIXTRL_HOST_FN bool doCheckKeyAndKernelConfigAreSync(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF key,
            kernel_id_t const kernel_config_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_id_t doInitPredefinedKernel(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            key_t const& SIXTRL_RESTRICT_REF input_key,
            purpose_t const predefined_purpose );

        key_kernel_id_map_t         m_key_to_kernel_id;
        key_init_param_map_t        m_key_to_kernel_init_params;
        kernel_id_keys_map_t        m_kernel_id_to_keys;
        kernel_id_counter_t         m_kernel_id_ref_counter;
        kernel_config_list_t        m_stored_kernel_configs;

        size_type                   m_num_stored_kernels;
        mutable lockable_t          m_lockable;
    };
}

typedef SIXTRL_CXX_NAMESPACE::KernelConfigStore NS(KernelConfigStore);

#else

typedef void NS(KernelConfigStore);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_id_t
    KernelConfigStore::addKernelConfig(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::ptr_kernel_config_t&& kernel_config )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->addKernelConfig( lock, key, std::move( kernel_config ) );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::addKernelConfig(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::kernel_id_t const kernel_config_id )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->addKernelConfig( lock, key, kernel_config_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::removeKernelConfig(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->removeKernelConfig( lock, this->kernelId( lock, key ) );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::removeKernelConfig(
        KernelConfigStore::kernel_config_base_t const&
            SIXTRL_RESTRICT_REF kernel_config )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->removeKernelConfig(
            lock, this->kernelId( lock, kernel_config ) );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::removeKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_id )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->removeKernelConfig( lock, kernel_id );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::removeKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
    {
        return this->removeKernelConfig( lock, this->kernelId( lock, key ) );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::removeKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_base_t const&
            SIXTRL_RESTRICT_REF kernel_config )
    {
        return this->removeKernelConfig(
            lock, this->kernelId( lock, kernel_config ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::size_type
    KernelConfigStore::numStoredKernels() const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->numStoredKernels( lock );
    }

    SIXTRL_INLINE KernelConfigStore::size_type KernelConfigStore::numKeys(
        KernelConfigStore::kernel_id_t const kernel_id ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->numKeys( lock, kernel_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->hasKernel( lock, this->kernelId( lock, key ) );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::kernel_config_base_t const&
            SIXTRL_RESTRICT_REF kernel_config ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->hasKernel( lock, this->kernelId( lock, kernel_config ) );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::arch_id_t const arch_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->hasKernel( lock, this->kernelId(
            lock, _this_t::key_t{ arch_id, purpose, variant, config_str } ) );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->hasKernel( lock, this->kernelId( lock,
            _this_t::key_t{ node_id, purpose, variant, config_str } ) );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::kernel_id_t const kernel_id ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->hasKernel( lock, kernel_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_id_t KernelConfigStore::kernelId(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->kernelId( lock, key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_id_t KernelConfigStore::kernelId(
        KernelConfigStore::kernel_config_base_t const&
            SIXTRL_RESTRICT_REF kernel_config )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->kernelId( lock, kernel_config );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_id_t KernelConfigStore::kernelId(
        KernelConfigStore::arch_id_t const arch_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->kernelId( lock,
            _this_t::key_t{ arch_id, purpose, variant, config_str } );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_id_t KernelConfigStore::kernelId(
        KernelConfigStore::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->kernelId( lock,
            _this_t::key_t{ node_id, purpose, variant, config_str } );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key ) const
    {
        return this->hasKernel( lock, this->kernelId( lock, key ) );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_base_t const&
            SIXTRL_RESTRICT_REF kernel_conf ) const
    {
        return this->hasKernel( lock, this->kernelId( lock, kernel_conf ) );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::arch_id_t const arch_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        return this->hasKernel( lock, this->kernelId( lock,
            _this_t::key_t{ arch_id, purpose, variant, config_str } ) );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        return this->hasKernel( lock, this->kernelId( lock,
            _this_t::key_t{ node_id, purpose, variant, config_str } ) );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_id_t KernelConfigStore::kernelId(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::arch_id_t const arch_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        return this->kernelId(
            lock, _this_t::key_t{ arch_id, purpose, variant, config_str } );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_id_t KernelConfigStore::kernelId(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        return this->kernelId(
            lock, _this_t::key_t{ node_id, purpose, variant, config_str } );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::key_t KernelConfigStore::findKey(
            KernelConfigStore::kernel_id_t const kernel_config_id ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->findKey( lock, kernel_config_id );
    }

    SIXTRL_INLINE KernelConfigStore::key_t KernelConfigStore::findKey(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF hint_key ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->findKey( lock, kernel_config_id, hint_key );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_config_base_t const*
    KernelConfigStore::ptrKernelConfigBase(
        KernelConfigStore::kernel_id_t const kernel_id ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->ptrKernelConfigBase( lock, kernel_id );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_base_t*
    KernelConfigStore::ptrKernelConfigBase(
        KernelConfigStore::kernel_id_t const kernel_id )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->ptrKernelConfigBase( lock, kernel_id );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE KernelConfigStore::kernel_config_base_t*
    KernelConfigStore::ptrKernelConfigBase(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        return const_cast< KernelConfigStore::kernel_config_base_t* >(
            static_cast< SIXTRL_CXX_NAMESPACE::KernelConfigStore const& >(
                *this ).ptrKernelConfigBase( lock, kernel_id ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_id_t
    KernelConfigStore::initKernelConfig(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initKernelConfig( lock, key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_id_t KernelConfigStore::initKernelConfig(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_args,
        std::string const& SIXTRL_RESTRICT_REF kernel_name )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initKernelConfig(
            lock, key, num_kernel_args, kernel_name.c_str() );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_id_t KernelConfigStore::initKernelConfig(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_args,
        char const* SIXTRL_RESTRICT kernel_name )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initKernelConfig(
            lock, key, num_kernel_args, kernel_name );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    KernelConfigStore::kernel_id_t KernelConfigStore::initKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_args,
        std::string const& SIXTRL_RESTRICT_REF kernel_name )
    {
        return this->initKernelConfig(
            lock, key, num_kernel_args, kernel_name.c_str() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_id_t
    KernelConfigStore::initDefaultControllerKernels(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initDefaultControllerKernels( lock, input_key );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureRemapBufferKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureRemapBufferKernelConfig( lock, kernel_config_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureDefaultTrackJobKernels(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF belems_buffer,
        KernelConfigStore::size_type const until_turn_elem_by_elem )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureDefaultTrackJobKernels( lock, input_key,
            pbuffer.getCApiPtr(), num_particle_sets, pset_begin,
            belems_buffer.getCApiPtr(), until_turn_elem_by_elem );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureDefaultTrackJobKernels(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT belems_buffer,
        KernelConfigStore::size_type const until_turn_elem_by_elem )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureDefaultTrackJobKernels( lock, input_key, pbuffer,
            num_particle_sets, pset_begin, belems_buffer,
                until_turn_elem_by_elem );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureDefaultTrackJobKernels(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF belems_buffer,
        KernelConfigStore::size_type const until_turn_elem_by_elem )
    {
        return this->configureDefaultTrackJobKernels( lock, input_key,
            pbuffer.getCApiPtr(), num_particle_sets, pset_begin,
                belems_buffer.getCApiPtr(), until_turn_elem_by_elem );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_id_t
    KernelConfigStore::initTrackUntilKernelConfig(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initTrackUntilKernelConfig( lock, input_key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_id_t
    KernelConfigStore::initTrackElemByElemKernelConfig(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initTrackElemByElemKernelConfig( lock, input_key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_id_t
    KernelConfigStore::initTrackLineKernelConfig(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initTrackLineKernelConfig( lock, input_key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_id_t
    KernelConfigStore::initFetchParticlesAddrKernelConfig(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initFetchParticlesAddrKernelConfig( lock, input_key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_id_t
    KernelConfigStore::initAssignBeamMonitorOutputKernelConfig(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initAssignBeamMonitorOutputKernelConfig( lock, input_key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_id_t
    KernelConfigStore::initAssignElemByElemOutputKernelConfig(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initAssignElemByElemOutputKernelConfig( lock, input_key );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::size_type const total_num_particles_in_sets )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackUntilKernelConfig(
            lock, kernel_config_id, total_num_particles_in_sets );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackUntilKernelConfig( lock, kernel_config_id,
            pbuffer.getCApiPtr(), num_particle_sets, pset_begin );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackUntilKernelConfig( lock, kernel_config_id,
            pbuffer, num_particle_sets, pset_begin );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackUntilKernelConfig( lock, kernel_config_id,
            pbuffer.getCApiPtr(), num_particle_sets, pset_begin );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::size_type const total_num_particles_in_sets )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackElemByElemKernelConfig(
            lock, kernel_config_id, total_num_particles_in_sets );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackElemByElemKernelConfig( lock,
            kernel_config_id, pbuffer.getCApiPtr(),
                num_particle_sets, pset_begin );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackElemByElemKernelConfig( lock,
            kernel_config_id, pbuffer, num_particle_sets, pset_begin );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackElemByElemKernelConfig( lock,
            kernel_config_id, pbuffer.getCApiPtr(),
                num_particle_sets, pset_begin );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::size_type const total_num_particles_in_sets )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackLineKernelConfig(
            lock, kernel_config_id, total_num_particles_in_sets );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackLineKernelConfig( lock, kernel_config_id,
            pbuffer.getCApiPtr(), num_particle_sets, pset_begin );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackLineKernelConfig( lock, kernel_config_id,
            pbuffer, num_particle_sets, pset_begin );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackLineKernelConfig( lock, kernel_config_id,
            pbuffer.getCApiPtr(), num_particle_sets, pset_begin );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::size_type const num_objs_in_particle_buffer )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureFetchParticlesAddrKernelConfig(
            lock, kernel_config_id, num_objs_in_particle_buffer );
    }

    SIXTRL_INLINE  KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureFetchParticlesAddrKernelConfig(
            lock, kernel_config_id, pbuffer.getCApiPtr() );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT_REF pbuffer )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureFetchParticlesAddrKernelConfig(
            lock, kernel_config_id, pbuffer );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer )
    {
        return this->configureFetchParticlesAddrKernelConfig( lock,
            kernel_config_id, pbuffer.getCApiPtr() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::size_type const num_beam_monitors )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureAssignOutputBeamMonitorKernelConfig(
            lock, kernel_config_id, num_beam_monitors );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF beam_elements )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureAssignOutputBeamMonitorKernelConfig(
            lock, kernel_config_id, beam_elements.getCApiPtr() );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const
            SIXTRL_RESTRICT_REF beam_elements )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureAssignOutputBeamMonitorKernelConfig(
            lock, kernel_config_id, beam_elements );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer )
    {
        return this->configureAssignOutputBeamMonitorKernelConfig(
            lock, kernel_config_id, pbuffer.getCApiPtr() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputElemByElemKernelConfig(
        KernelConfigStore::kernel_id_t const kernel_config_id )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureAssignOutputElemByElemKernelConfig( lock,
            kernel_config_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::setDefaultInitKernelConfigParameters(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_arguments,
        std::string const& SIXTRL_RESTRICT_REF kernel_name )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->setDefaultInitKernelConfigParameters(
            lock, key, num_kernel_arguments, kernel_name.c_str() );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::setDefaultInitKernelConfigParameters(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_arguments,
        char const* SIXTRL_RESTRICT kernel_name )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->setDefaultInitKernelConfigParameters(
            lock, key, num_kernel_arguments, kernel_name );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::removeDefaultInitKernelConfigParameters(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->removeDefaultInitKernelConfigParameters( lock, key );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasDefaultInitKernelConfigParameters(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->hasDefaultInitKernelConfigParameters( lock, key );
    }

    SIXTRL_INLINE KernelConfigStore::size_type KernelConfigStore::defaultNumKernelArgs(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->defaultNumKernelArgs( lock, key );
    }

    SIXTRL_INLINE std::string const& KernelConfigStore::defaultKernelName(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->defaultKernelName( lock, key );
    }

    SIXTRL_INLINE char const* KernelConfigStore::ptrDefaultKernelName(
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->defaultKernelName( lock, key ).c_str();
    }

    SIXTRL_INLINE char const* KernelConfigStore::ptrDefaultKernelName(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::key_t const& SIXTRL_RESTRICT_REF key )
    {
        return this->defaultKernelName( lock, key ).c_str();
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::lockable_t*
    KernelConfigStore::lockable() const SIXTRL_NOEXCEPT
    {
        return &this->m_lockable;
    }

    SIXTRL_INLINE bool KernelConfigStore::checkLock(
        KernelConfigStore::lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( lock.owns_lock() ) &&
                 ( lock.mutex() == this->lockable() ) );
    }

    /* --------------------------------------------------------------------- */

    template< typename Derived >
    Derived const* KernelConfigStore::asDerivedKernelConfigStore() const
    {
        static_assert( std::is_base_of< KernelConfigStore, Derived >::value,
            "asDerivedKernelConfigStore< Derived > requires Derived to "
            "be derived from SIXTRL_CXX_NAMESPACE::KernelConfigStore" );

        return static_cast< Derived const* >( this );
    }

    template< typename Derived >
    SIXTRL_INLINE Derived* KernelConfigStore::asDerivedKernelConfigStore()
    {
        return const_cast< Derived* >( static_cast<
            SIXTRL_CXX_NAMESPACE::KernelConfigStore const& >( *this
                ).asDerivedKernelConfigStore< Derived >() );
    }
}

#endif  /* C++, Host */


#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_STORE_CXX_HPP__ */

/* end: sixtracklib/common/control/kernel_config_store.hpp */
