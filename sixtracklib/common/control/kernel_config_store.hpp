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
    #include <stdexcept>
    #include <thread>
    #include <unordered_map>
    #include <unordered_set>
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
    class KernelSetItemData;
    class KernelSetBase;

    class KernelConfigStore
    {
        public:

        using kernel_config_base_t  = SIXTRL_CXX_NAMESPACE::KernelConfigBase;
        using kernel_set_t          = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        using buffer_t              = SIXTRL_CXX_NAMESPACE::Buffer;

        using kernel_config_key_t   = SIXTRL_CXX_NAMESPACE::KernelConfigKey;
        using kernel_config_id_t    = SIXTRL_CXX_NAMESPACE::ctrl_kernel_id_t;
        using status_t              = kernel_config_key_t::status_t;
        using purpose_t             = kernel_config_key_t::purpose_t;
        using variant_t             = kernel_config_key_t::variant_t;
        using argument_set_t        = kernel_config_key_t::argument_set_t;
        using arch_id_t             = kernel_config_key_t::arch_id_t;
        using platform_id_t         = kernel_config_key_t::platform_id_t;
        using device_id_t           = kernel_config_key_t::device_id_t;
        using node_id_t             = kernel_config_key_t::node_id_t;
        using c_node_id_t           = node_id_t::c_api_t;
        using c_buffer_t            = buffer_t::c_api_t;
        using particle_index_t      = ::NS(particle_index_t);
        using size_type             = kernel_config_base_t::size_type;
        using kernel_set_id_t       = kernel_config_id_t;

        using lockable_t            = std::mutex;
        using lock_t                = std::unique_lock< lockable_t >;

        using ptr_kernel_config_t   = std::unique_ptr< kernel_config_base_t >;
        using ptr_kernel_set_t      = std::unique_ptr< kernel_set_t >;

        static constexpr kernel_config_id_t ILLEGAL_KERNEL_CONFIG_ID =
            SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_KERNEL_ID;

        static constexpr kernel_set_id_t ILLEGAL_KERNEL_SET_ID =
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

        static constexpr argument_set_t DEFAULT_ARGUMENTS_SET =
            SIXTRL_CXX_NAMESPACE::DEFAULT_KERNEL_ARGUMENT_SET;

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

        SIXTRL_HOST_FN size_type numKernelSets() const;

        SIXTRL_HOST_FN kernel_set_id_t addKernelSet(
            ptr_kernel_set_t&& ptr_kernel_set );

        SIXTRL_HOST_FN bool hasKernelSet(
            kernel_set_id_t const kernel_set_id ) const;

        SIXTRL_HOST_FN bool hasKernelSet(
            kernel_set_t const& SIXTRL_RESTRICT_REF kernel_set ) const;

        SIXTRL_HOST_FN status_t updateKernelSet(
            kernel_set_id_t const kernel_set_id );

        SIXTRL_HOST_FN kernel_set_id_t kernelSetId(
            kernel_set_t const& SIXTRL_RESTRICT_REF kernel_set ) const;

        SIXTRL_HOST_FN kernel_set_t const* ptrKernelSetBase(
            kernel_set_id_t const kernel_set_id ) const;

        SIXTRL_HOST_FN kernel_set_t* ptrKernelSetBase(
            kernel_set_id_t const kernel_set_id );

        SIXTRL_HOST_FN kernel_set_t const& kernelSetBase(
            kernel_set_id_t const kernel_set_id ) const;

        SIXTRL_HOST_FN kernel_set_t& kernelSetBase(
            kernel_set_id_t const kernel_set_id );

        SIXTRL_HOST_FN status_t removeKernelSet(
            kernel_set_id_t const kernel_set_id );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -  */

        SIXTRL_HOST_FN size_type numKernelSets(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN kernel_set_id_t addKernelSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            ptr_kernel_set_t&& ptr_kernel_set );

        SIXTRL_HOST_FN bool hasKernelSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_set_id_t const kernel_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasKernelSet( lock_t const& SIXTRL_RESTRICT_REF lk,
            kernel_set_t const& SIXTRL_RESTRICT_REF
                kernel_set ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t updateKernelSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_set_id_t const kernel_set_id );

        SIXTRL_HOST_FN kernel_set_id_t kernelSetId(
            lock_t const& SIXTRL_RESTRICT_REF lock, kernel_set_t const&
                SIXTRL_RESTRICT_REF kernel_set ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_set_t const* ptrKernelSetBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_set_id_t const kernel_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_set_t* ptrKernelSetBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_set_id_t const kernel_set_id )  SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_set_t const& kernelSetBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_set_id_t const kernel_set_id ) const;

        SIXTRL_HOST_FN kernel_set_t& kernelSetBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_set_id_t const kernel_set_id );

        SIXTRL_HOST_FN status_t removeKernelSet(
            lock_t& SIXTRL_RESTRICT_REF lock,
            kernel_set_id_t const kernel_set_id )  SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_id_t addKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            ptr_kernel_config_t&& kernel_config );

        SIXTRL_HOST_FN status_t addKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            kernel_config_id_t const kernel_config_id );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN kernel_config_id_t addKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            ptr_kernel_config_t&& kernel_config );

        SIXTRL_HOST_FN status_t addKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            kernel_config_id_t const kernel_config_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t removeKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN status_t removeKernelConfig(
            kernel_config_base_t const& SIXTRL_RESTRICT_REF kernel_config );

        SIXTRL_HOST_FN status_t removeKernelConfig(
            kernel_config_id_t const kernel_id );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t removeKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN status_t removeKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_base_t const& SIXTRL_RESTRICT_REF kernel_config );

        SIXTRL_HOST_FN status_t removeKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type numStoredKernels() const;

        SIXTRL_HOST_FN size_type numKernelConfigKeys(
            kernel_config_id_t const kernel_id ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN size_type numStoredKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numKernelConfigKeys(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_id ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasKernel(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN bool hasKernel( kernel_config_base_t const&
            SIXTRL_RESTRICT_REF kernel_config ) const;

        SIXTRL_HOST_FN bool hasKernel( arch_id_t const arch_id,
            purpose_t const purpose, variant_t const variant,
            argument_set_t const argument_set = DEFAULT_ARGUMENTS_SET,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const;

        SIXTRL_HOST_FN bool hasKernel(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose, variant_t const variant,
            argument_set_t const argument_set = DEFAULT_ARGUMENTS_SET,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const;

        SIXTRL_HOST_FN bool hasKernel( kernel_config_id_t const kernel_id ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool hasKernel( lock_t const& SIXTRL_RESTRICT_REF lock,
                        kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN bool hasKernel( lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_base_t const& SIXTRL_RESTRICT_REF kernel_conf ) const;

        SIXTRL_HOST_FN bool hasKernel( lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            purpose_t const purpose, variant_t const variant,
            argument_set_t const argument_set = DEFAULT_ARGUMENTS_SET,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasKernel( lock_t const& SIXTRL_RESTRICT_REF lock,
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose, variant_t const variant,
            argument_set_t const argument_set = DEFAULT_ARGUMENTS_SET,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasKernel(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_id ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_id_t kernelId(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN kernel_config_id_t kernelId(
            kernel_config_id_t const kernel_config_id ) const;

        SIXTRL_HOST_FN kernel_config_id_t kernelId( kernel_config_base_t const&
            SIXTRL_RESTRICT_REF kernel_config ) const;

        SIXTRL_HOST_FN kernel_config_id_t kernelId( arch_id_t const arch_id,
            purpose_t const purpose, variant_t const variant,
            argument_set_t const argument_set = DEFAULT_ARGUMENTS_SET,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const;

        SIXTRL_HOST_FN kernel_config_id_t kernelId(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose, variant_t const variant,
            argument_set_t const argument_set = DEFAULT_ARGUMENTS_SET,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN kernel_config_id_t kernelId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_id_t kernelId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_id_t kernelId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_base_t const& SIXTRL_RESTRICT_REF
                kernel_config ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_id_t kernelId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id, purpose_t const purpose,
            variant_t const variant,
            argument_set_t const argument_set = DEFAULT_ARGUMENTS_SET,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_id_t kernelId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            purpose_t const purpose, variant_t const variant,
            argument_set_t const argument_set = DEFAULT_ARGUMENTS_SET,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{}
        ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_key_t findKey(
            kernel_config_id_t const kernel_config_id ) const;

        SIXTRL_HOST_FN kernel_config_key_t findKey(
            kernel_config_id_t const kernel_config_id,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF hint_key ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN kernel_config_key_t findKey(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_key_t findKey(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF hint_key
            ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_base_t const* ptrKernelConfigBase(
            kernel_config_id_t const kernel_id ) const;

        SIXTRL_HOST_FN kernel_config_base_t* ptrKernelConfigBase(
            kernel_config_id_t const kernel_id );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN kernel_config_base_t const* ptrKernelConfigBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_base_t* ptrKernelConfigBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_id ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_id_t initKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN kernel_config_id_t initKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args,
            std::string const& SIXTRL_RESTRICT_REF kernel_name );

        SIXTRL_HOST_FN kernel_config_id_t initKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args,
            char const* SIXTRL_RESTRICT kernel_name );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN kernel_config_id_t initKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN kernel_config_id_t initKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args,
            std::string const& SIXTRL_RESTRICT_REF kernel_name );

        SIXTRL_HOST_FN kernel_config_id_t initKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args,
            char const* SIXTRL_RESTRICT kernel_name );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t setDefaultInitKernelConfigParameters(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_arguments,
            std::string const& SIXTRL_RESTRICT_REF kernel_name );

        SIXTRL_HOST_FN status_t setDefaultInitKernelConfigParameters(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_arguments,
            char const* SIXTRL_RESTRICT kernel_name );

        SIXTRL_HOST_FN status_t removeDefaultInitKernelConfigParameters(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN bool hasDefaultInitKernelConfigParameters(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN size_type defaultNumKernelArgs(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN std::string const& defaultKernelName(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN char const* ptrDefaultKernelName(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t setDefaultInitKernelConfigParameters(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_arguments,
            std::string const& SIXTRL_RESTRICT_REF kernel_name );

        SIXTRL_HOST_FN status_t setDefaultInitKernelConfigParameters(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_arguments,
            char const* SIXTRL_RESTRICT kernel_name );

        SIXTRL_HOST_FN status_t removeDefaultInitKernelConfigParameters(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN bool hasDefaultInitKernelConfigParameters(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type defaultNumKernelArgs(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const& defaultKernelName(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN char const* ptrDefaultKernelName(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool checkLock(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void checkLockAndThrowOnError(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        /* ----------------------------------------------------------------- */

        template< typename Derived >
        SIXTRL_HOST_FN Derived const* asDerivedKernelConfigStore() const;

        template< typename Derived >
        SIXTRL_HOST_FN Derived* asDerivedKernelConfigStore();

        protected:

        using keys_set_t           = std::set< kernel_config_key_t >;
        using kernel_init_param_t  = std::tuple< size_type, std::string >;

        using key_kernel_id_map_t  =
            std::map< kernel_config_key_t, kernel_config_id_t >;

        using key_init_param_map_t =
            std::map< kernel_config_key_t, kernel_init_param_t >;

        using kernel_id_keys_map_t =
            std::unordered_map< kernel_config_id_t, keys_set_t >;

        using kernel_id_counter_t  =
            std::unordered_map< kernel_config_id_t, size_type >;

        using kernel_config_list_t = std::vector< ptr_kernel_config_t >;
        using kernel_set_list_t    = std::vector< ptr_kernel_set_t >;
        using out_buffer_flags_t   = ::NS(output_buffer_flag_t);

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual kernel_config_id_t doInitKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args,
            char const* SIXTRL_RESTRICT name );

        SIXTRL_HOST_FN virtual kernel_config_id_t doAddKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            ptr_kernel_config_t&& ptr_kernel_config );

        SIXTRL_HOST_FN virtual status_t doRemoveKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_id );

        SIXTRL_HOST_FN virtual kernel_set_id_t doAddKernelSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            ptr_kernel_set_t&& ptr_kernel_set );

        SIXTRL_HOST_FN virtual status_t doRemoveKernelSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_set_id_t const kernel_set_id );

        SIXTRL_HOST_FN virtual status_t doUpdateKernelSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_set_id_t const kernel_set_id );

        SIXTRL_HOST_FN status_t doUpdateStoredKernelSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_set_id_t const kernel_set_id,
            ptr_kernel_set_t&& ptr_kernel_set );

        SIXTRL_HOST_FN status_t doInitKernelConfigFromKeyAttributes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_base_t& SIXTRL_RESTRICT_REF config_base,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        static std::atomic< purpose_t > NEXT_USERDEFINED_PURPOSE_ID;

        private:

        SIXTRL_HOST_FN bool doCheckKeyAndKernelConfigAreSync(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            kernel_config_id_t const kernel_config_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_id_t doInitPredefinedKernel(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
            purpose_t const predefined_purpose );

        key_kernel_id_map_t         m_key_to_kernel_id;
        key_init_param_map_t        m_key_to_kernel_init_params;
        kernel_id_keys_map_t        m_kernel_id_to_keys;
        kernel_id_counter_t         m_kernel_id_ref_counter;
        kernel_config_list_t        m_stored_kernel_configs;
        kernel_set_list_t           m_stored_kernel_sets;

        size_type                   m_num_stored_kernels;
        size_type                   m_num_stored_kernel_sets;
        mutable lockable_t          m_lockable;
    };
}

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

typedef SIXTRL_CXX_NAMESPACE::KernelConfigStore NS(KernelConfigStore);

#else

typedef void NS(KernelConfigStore);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* *****               Inline functions and methods                     **** */
/* ************************************************************************* */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include "sixtracklib/common/control/kernel_set.hpp"
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE KernelConfigStore::size_type
    KernelConfigStore::numKernelSets() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        _this_t::lock_t const lock( *this->lockable() );
        return this->numKernelSets( lock );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_set_id_t
    KernelConfigStore::addKernelSet(
        KernelConfigStore::ptr_kernel_set_t&& ptr_kernel_set )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        _this_t::lock_t const lock( *this->lockable() );
        return this->addKernelSet( lock, std::move( ptr_kernel_set ) );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::updateKernelSet(
        KernelConfigStore::kernel_set_id_t const kernel_set_id )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        _this_t::lock_t const lock( *this->lockable() );
        return this->doUpdateKernelSet( lock, kernel_set_id );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernelSet(
        KernelConfigStore::kernel_set_id_t const kernel_set_id ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        _this_t::lock_t const lock( *this->lockable() );
        return this->hasKernelSet( lock, kernel_set_id );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernelSet(
        KernelConfigStore::kernel_set_t const& SIXTRL_RESTRICT_REF set ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        _this_t::lock_t const lock( *this->lockable() );
        return this->hasKernelSet( lock, set );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_set_id_t
    KernelConfigStore::kernelSetId( KernelConfigStore::kernel_set_t const&
        SIXTRL_RESTRICT_REF kernel_set ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        _this_t::lock_t const lock( *this->lockable() );
        return this->kernelSetId( lock, kernel_set );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_set_t const*
    KernelConfigStore::ptrKernelSetBase(
        KernelConfigStore::kernel_set_id_t const kernel_set_id ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        _this_t::lock_t const lock( *this->lockable() );
        return ptrKernelSetBase( lock, kernel_set_id );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_set_t*
    KernelConfigStore::ptrKernelSetBase(
        KernelConfigStore::kernel_set_id_t const kernel_set_id )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        _this_t::lock_t const lock( *this->lockable() );
        return ptrKernelSetBase( lock, kernel_set_id );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_set_t const&
    KernelConfigStore::kernelSetBase(
        KernelConfigStore::kernel_set_id_t const kernel_set_id ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        _this_t::lock_t const lock( *this->lockable() );
        return this->kernelSetBase( lock, kernel_set_id );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_set_t&
    KernelConfigStore::kernelSetBase(
        KernelConfigStore::kernel_set_id_t const kernel_set_id )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        _this_t::lock_t const lock( *this->lockable() );
        return this->kernelSetBase( lock, kernel_set_id );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::removeKernelSet(
        KernelConfigStore::kernel_set_id_t const kernel_set_id )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        _this_t::lock_t lock( *this->lockable() );
        return this->removeKernelSet( lock, kernel_set_id );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE KernelConfigStore::size_type KernelConfigStore::numKernelSets(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        return ( this->checkLock( lock ) )
            ? this->m_num_stored_kernel_sets
            : SIXTRL_CXX_NAMESPACE::KernelConfigStore::size_type{ 0 };
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernelSet(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_set_id_t const set_id ) const SIXTRL_NOEXCEPT
    {
        return ( this->ptrKernelSetBase( lock, set_id ) != nullptr );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernelSet(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_set_t const& SIXTRL_RESTRICT_REF
            set ) const SIXTRL_NOEXCEPT
    {
        return this->hasKernelSet( lock, this->kernelSetId( lock, set ) );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::updateKernelSet(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_set_id_t const kernel_set_id )
    {
        return this->doUpdateKernelSet( lock, kernel_set_id );
    }



    SIXTRL_INLINE KernelConfigStore::kernel_set_t const*
    KernelConfigStore::ptrKernelSetBase(
            KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
            KernelConfigStore::kernel_set_id_t const id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;

        return ( ( id != _this_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( this->checkLock( lock ) ) &&
            ( !this->m_stored_kernel_sets.empty() ) &&
            (  this->m_stored_kernel_sets.size() >
               static_cast< _this_t::size_type >( id ) ) )
            ? this->m_stored_kernel_sets[ id ].get() : nullptr;
    }

    SIXTRL_INLINE KernelConfigStore::kernel_set_t*
    KernelConfigStore::ptrKernelSetBase(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_set_id_t const id )  SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        return const_cast< _this_t::kernel_set_t* >( static_cast<
            _this_t const& >( *this ).ptrKernelSetBase( lock, id ) );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_set_t&
    KernelConfigStore::kernelSetBase(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_set_id_t const kernel_set_id )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        return const_cast< _this_t::kernel_set_t& >( static_cast<
            _this_t const& >( *this ).kernelSetBase( lock, kernel_set_id ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::addKernelConfig(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::ptr_kernel_config_t&& kernel_config )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->addKernelConfig( lock, key, std::move( kernel_config ) );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::addKernelConfig(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::kernel_config_id_t const kernel_config_id )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->addKernelConfig( lock, key, kernel_config_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::removeKernelConfig(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
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
        KernelConfigStore::kernel_config_id_t const kernel_id )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->removeKernelConfig( lock, kernel_id );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::removeKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
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

    SIXTRL_INLINE KernelConfigStore::size_type
    KernelConfigStore::numKernelConfigKeys(
        KernelConfigStore::kernel_config_id_t const kernel_id ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->numKernelConfigKeys( lock, kernel_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF
            key ) const
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
        KernelConfigStore::argument_set_t const argument_set,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->hasKernel( lock, this->kernelId( lock,
            _this_t::kernel_config_key_t{ arch_id, purpose, variant,
                argument_set, config_str } ) );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        KernelConfigStore::argument_set_t const argument_set,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->hasKernel( lock, this->kernelId( lock,
            _this_t::kernel_config_key_t{ node_id, purpose, variant,
                argument_set, config_str } ) );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::kernel_config_id_t const kernel_id ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->hasKernel( lock, kernel_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::kernelId( KernelConfigStore::kernel_config_key_t const&
        SIXTRL_RESTRICT_REF key ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->kernelId( lock, key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::kernelId( KernelConfigStore::kernel_config_id_t const
        kernel_config_id ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->kernelId( lock, kernel_config_id );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::kernelId( KernelConfigStore::kernel_config_base_t const&
            SIXTRL_RESTRICT_REF kernel_config ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->kernelId( lock, kernel_config );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t KernelConfigStore::kernelId(
        KernelConfigStore::arch_id_t const arch_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        KernelConfigStore::argument_set_t const argument_set,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->kernelId( lock, _this_t::kernel_config_key_t{
            arch_id, purpose, variant, argument_set, config_str } );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::kernelId(
        KernelConfigStore::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        KernelConfigStore::argument_set_t const argument_set,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->kernelId( lock, _this_t::kernel_config_key_t{ node_id,
            purpose, variant, argument_set, config_str } );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const
    {
        return this->hasKernel( lock, this->kernelId( lock, key ) );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::kernelId(
            KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
            KernelConfigStore::kernel_config_id_t const id
        ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;

        return ( ( id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                 ( this->checkLock( lock ) ) &&
                 ( this->m_stored_kernel_configs.size() > static_cast<
                    _this_t::size_type >( id ) ) &&
                 ( this->m_stored_kernel_configs[ id ].get() != nullptr ) )
            ? id : _this_t::ILLEGAL_KERNEL_CONFIG_ID;
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
        KernelConfigStore::argument_set_t const argument_set,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        return this->hasKernel( lock, this->kernelId( lock,
            _this_t::kernel_config_key_t{ arch_id, purpose, variant,
                argument_set, config_str } ) );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasKernel(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        KernelConfigStore::argument_set_t const argument_set,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        return this->hasKernel( lock, this->kernelId( lock,
            _this_t::kernel_config_key_t{ node_id, purpose, variant,
                argument_set, config_str } ) );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t KernelConfigStore::kernelId(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::arch_id_t const arch_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        KernelConfigStore::argument_set_t const argument_set,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        return this->kernelId( lock, _this_t::kernel_config_key_t{ arch_id,
            purpose, variant, argument_set, config_str } );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
        KernelConfigStore::kernelId(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::node_id_t const& SIXTRL_RESTRICT_REF node_id,
        KernelConfigStore::purpose_t const purpose,
        KernelConfigStore::variant_t const variant,
        KernelConfigStore::argument_set_t const argument_set,
        std::string const& SIXTRL_RESTRICT_REF config_str ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        return this->kernelId( lock, _this_t::kernel_config_key_t{
            node_id, purpose, variant, argument_set, config_str } );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_config_key_t
    KernelConfigStore::findKey( KernelConfigStore::kernel_config_id_t
        const kernel_config_id ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->findKey( lock, kernel_config_id );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_key_t
    KernelConfigStore::findKey(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::kernel_config_key_t const&
            SIXTRL_RESTRICT_REF hint_key ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->findKey( lock, kernel_config_id, hint_key );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_config_base_t const*
    KernelConfigStore::ptrKernelConfigBase(
        KernelConfigStore::kernel_config_id_t const kernel_id ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->ptrKernelConfigBase( lock, kernel_id );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_base_t*
    KernelConfigStore::ptrKernelConfigBase(
        KernelConfigStore::kernel_config_id_t const kernel_id )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->ptrKernelConfigBase( lock, kernel_id );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE KernelConfigStore::kernel_config_base_t*
    KernelConfigStore::ptrKernelConfigBase(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        return const_cast< KernelConfigStore::kernel_config_base_t* >(
            static_cast< SIXTRL_CXX_NAMESPACE::KernelConfigStore const& >(
                *this ).ptrKernelConfigBase( lock, kernel_id ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initKernelConfig(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initKernelConfig( lock, key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initKernelConfig(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_args,
        std::string const& SIXTRL_RESTRICT_REF kernel_name )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initKernelConfig(
            lock, key, num_kernel_args, kernel_name.c_str() );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initKernelConfig(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_args,
        char const* SIXTRL_RESTRICT kernel_name )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initKernelConfig(
            lock, key, num_kernel_args, kernel_name );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_args,
        std::string const& SIXTRL_RESTRICT_REF kernel_name )
    {
        return this->initKernelConfig(
            lock, key, num_kernel_args, kernel_name.c_str() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::setDefaultInitKernelConfigParameters(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_arguments,
        std::string const& SIXTRL_RESTRICT_REF kernel_name )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->setDefaultInitKernelConfigParameters(
            lock, key, num_kernel_arguments, kernel_name.c_str() );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::setDefaultInitKernelConfigParameters(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        KernelConfigStore::size_type const num_kernel_arguments,
        char const* SIXTRL_RESTRICT kernel_name )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->setDefaultInitKernelConfigParameters(
            lock, key, num_kernel_arguments, kernel_name );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::removeDefaultInitKernelConfigParameters(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->removeDefaultInitKernelConfigParameters( lock, key );
    }

    SIXTRL_INLINE bool KernelConfigStore::hasDefaultInitKernelConfigParameters(
        KernelConfigStore::kernel_config_key_t const&
            SIXTRL_RESTRICT_REF key ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->hasDefaultInitKernelConfigParameters( lock, key );
    }

    SIXTRL_INLINE KernelConfigStore::size_type
    KernelConfigStore::defaultNumKernelArgs(
        KernelConfigStore::kernel_config_key_t const&
            SIXTRL_RESTRICT_REF key ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->defaultNumKernelArgs( lock, key );
    }

    SIXTRL_INLINE std::string const& KernelConfigStore::defaultKernelName(
        KernelConfigStore::kernel_config_key_t const&
            SIXTRL_RESTRICT_REF key ) const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->defaultKernelName( lock, key );
    }

    SIXTRL_INLINE char const* KernelConfigStore::ptrDefaultKernelName(
        KernelConfigStore::kernel_config_key_t const&
            SIXTRL_RESTRICT_REF key )
        const
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->defaultKernelName( lock, key ).c_str();
    }

    SIXTRL_INLINE char const* KernelConfigStore::ptrDefaultKernelName(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const&
            SIXTRL_RESTRICT_REF key ) const
    {
        return this->defaultKernelName( lock, key ).c_str();
    }

    /* ----------------------------------------------------------------- */

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

    SIXTRL_INLINE void KernelConfigStore::checkLockAndThrowOnError(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        if( !this->checkLock( lock ) )
            throw std::runtime_error( "Not properly locked lock handle" );
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
