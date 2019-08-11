#ifndef SIXTRACKLIB_COMMON_CONTROL_KERNEL_SET_CXX_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_KERNEL_SET_CXX_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <atomic>
    #include <cstddef>
    #include <cstdlib>
    #include <cstdio>
    #include <chrono>
    #include <stdexcept>
    #include <string>
    #include <memory>
    #include <mutex>
    #include <thread>
    #include <unordered_map>
    #include <unordered_set>
    #include <utility>
    #include <vector>
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
    #include "sixtracklib/common/control/arch_info.hpp"
    #include "sixtracklib/common/control/kernel_config_key.hpp"
    #include "sixtracklib/common/control/kernel_config_base.hpp"
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class KernelConfigStore;

    class KernelSetItemData
    {
        public:

        using kernel_config_base_t = SIXTRL_CXX_NAMESPACE::KernelConfigBase;
        using kernel_config_key_t  = SIXTRL_CXX_NAMESPACE::KernelConfigKey;
        using kernel_config_id_t   = SIXTRL_CXX_NAMESPACE::arch_kernel_id_t;
        using purpose_t            = SIXTRL_CXX_NAMESPACE::kernel_purpose_t;
        using arch_id_t            = kernel_config_base_t::arch_id_t;
        using status_t             = kernel_config_base_t::status_t;

        static constexpr arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static constexpr arch_id_t ARCH_NONE =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_NONE;

        static constexpr kernel_config_id_t ILLEGAL_KERNEL_CONFIG_ID =
            SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_KERNEL_ID;

        static constexpr purpose_t UNSPECIFIED_PUPRPOSE =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;

        static constexpr status_t RESET_GENERAL_FAILURE =
            SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

        static constexpr status_t RESET_SUCCESS_SYNC =
            SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;

        static constexpr status_t RESET_SUCCESS_UPDATED = status_t{ 1 };

        SIXTRL_HOST_FN explicit KernelSetItemData(
            kernel_config_id_t const kernel_config_id = ILLEGAL_KERNEL_CONFIG_ID,
            kernel_config_base_t* SIXTRL_RESTRICT ptr_config_base = nullptr,
            kernel_config_key_t const& SIXTRL_RESTRICT key =
                kernel_config_key_t{},
            bool const is_pinned = false );

        SIXTRL_HOST_FN KernelSetItemData(
            KernelSetItemData const& orig ) = default;

        SIXTRL_HOST_FN KernelSetItemData(
            KernelSetItemData&& orig ) = default;

        SIXTRL_HOST_FN KernelSetItemData& operator=(
            KernelSetItemData const& orig ) = default;

        SIXTRL_HOST_FN KernelSetItemData& operator=(
            KernelSetItemData&& orig ) = default;

        SIXTRL_HOST_FN ~KernelSetItemData() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_id_t
        kernelConfigId() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_base_t const*
        ptrKernelConfigBase() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_base_t*
        ptrKernelConfigBase() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_key_t const&
        kernelConfigKey() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool available() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool ready()     const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool pinned()    const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isEqualTo(
            kernel_config_id_t const kernel_conf_id = ILLEGAL_KERNEL_CONFIG_ID,
            kernel_config_base_t* SIXTRL_RESTRICT ptr_kernel_config = nullptr
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isEqualTo(
            kernel_config_id_t const kernel_conf_id,
            kernel_config_base_t* SIXTRL_RESTRICT ptr_kernel_config,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isEqualTo(
            kernel_config_id_t const kernel_conf_id,
            kernel_config_base_t* SIXTRL_RESTRICT ptr_kernel_config,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            bool const is_pinned_flag ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t reset(
            kernel_config_id_t const kernel_config_id = ILLEGAL_KERNEL_CONFIG_ID,
            kernel_config_base_t* SIXTRL_RESTRICT ptr_kernel_config = nullptr,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF
                key = kernel_config_key_t{},
            bool const is_pinned_flag = false ) SIXTRL_NOEXCEPT;

        private:

        kernel_config_key_t      m_config_key;
        kernel_config_base_t*    m_ptr_config;
        kernel_config_id_t       m_config_id;
        bool                     m_pinned;
    };

    /* ********************************************************************* */
    /* KernelSetBase: */

    class KernelSetBase : public SIXTRL_CXX_NAMESPACE::ArchInfo
    {
        private:

        using _base_arch_info_t   = SIXTRL_CXX_NAMESPACE::ArchInfo;

        public:

        using kernel_set_data_t    = SIXTRL_CXX_NAMESPACE::KernelSetItemData;
        using op_flags_t           = SIXTRL_CXX_NAMESPACE::kernel_op_flags_t;

        using kernel_config_key_t  = kernel_set_data_t::kernel_config_key_t;
        using kernel_config_id_t   = kernel_set_data_t::kernel_config_id_t;
        using kernel_config_base_t = kernel_set_data_t::kernel_config_base_t;
        using kernel_set_id_t      = kernel_config_id_t;
        using status_t             = kernel_set_data_t::status_t;
        using purpose_t            = kernel_set_data_t::purpose_t;
        using arch_id_t            = kernel_set_data_t::arch_id_t;
        using size_type            = kernel_config_key_t::size_type;
        using variant_t            = kernel_config_key_t::variant_t;

        using lockable_t           = std::mutex;
        using lock_t               = std::unique_lock< lockable_t >;

        using sync_id_value_t      = uint64_t;
        using sync_id_t            = std::atomic< sync_id_value_t >;

        using kernel_config_store_base_t =
            SIXTRL_CXX_NAMESPACE::KernelConfigStore;

        static constexpr arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static constexpr arch_id_t ARCH_NONE =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_NONE;

        static constexpr kernel_config_id_t ILLEGAL_KERNEL_CONFIG_ID =
            SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_KERNEL_ID;

        static constexpr kernel_config_id_t ILLEGAL_KERNEL_SET_ID =
            SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_KERNEL_ID;

        static constexpr purpose_t UNSPECIFIED_PUPRPOSE =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;

        static constexpr sync_id_value_t ILLEGAL_SYNC_ID_VALUE =
            sync_id_value_t{ 0xffffffffffffffff };

        static constexpr sync_id_value_t LAST_LEGAL_SYNC_ID_VALUE =
            sync_id_value_t{ 0xfffffffffffffffe };

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        static constexpr size_type NUM_CONTROLLER_PURPOSES = size_type{ 1 };
        static constexpr purpose_t CONTROLLER_PURPOSES[] =
        {
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER
        };

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        static constexpr size_type NUM_TRACK_JOB_PURPOSES = size_type{ 6 };
        static constexpr purpose_t TRACK_JOB_PURPOSES[] =
        {
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN,
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_TRACK_ELEM_BY_ELEM,
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_TRACK_LINE,
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES,
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_ASSIGN_BEAM_MONITOR_OUTPUT,
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_ASSIGN_ELEM_BY_ELEM_OUTPUT
        };

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN KernelSetBase(
            arch_id_t const arch_id,
            kernel_config_store_base_t& SIXTRL_RESTRICT_REF kernel_conf_store,
            size_type const num_purposes = size_type{ 0 },
            purpose_t const* SIXTRL_RESTRICT purposes_begin = nullptr );

        template< typename PurposeIter >
        SIXTRL_HOST_FN KernelSetBase(
            arch_id_t const arch_id,
            kernel_config_store_base_t& SIXTRL_RESTRICT_REF kernel_conf_store,
            PurposeIter purposes_begin, PurposeIter purposes_end );

        SIXTRL_HOST_FN KernelSetBase( KernelSetBase const& orig ) = default;
        SIXTRL_HOST_FN KernelSetBase( KernelSetBase&& orig ) = default;

        SIXTRL_HOST_FN KernelSetBase& operator=(
            KernelSetBase const& rhs ) = default;

        SIXTRL_HOST_FN KernelSetBase& operator=(
            KernelSetBase&& rhs ) = default;

        SIXTRL_HOST_FN virtual ~KernelSetBase();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool isForControllers() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool isForTrackJobs() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type numPurposes() const;

        SIXTRL_HOST_FN size_type numPurposes(
            kernel_config_id_t const kernel_config_id ) const;

        SIXTRL_HOST_FN size_type numPinnedPurposes() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN size_type numPurposes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numPurposes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numPinnedPurposes(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN purpose_t const* purposesBegin(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN purpose_t const* purposesEnd(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_base_t const*
        ptrKernelConfigBase( purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_base_t*
        ptrKernelConfigBase( purpose_t const purpose ) SIXTRL_NOEXCEPT;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN kernel_config_base_t const* ptrKernelConfigBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_base_t* ptrKernelConfigBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_id_t kernelConfigId(
            purpose_t const purpose ) const;

        SIXTRL_HOST_FN bool hasKernelConfigId(
            kernel_config_id_t const kernel_config_id ) const;

        SIXTRL_HOST_FN bool isPurposeAssociatedWithKernelConfigId(
            kernel_config_id_t const kernel_config_id,
            purpose_t const purpose ) const;

        SIXTRL_HOST_FN kernel_config_key_t const* ptrKernelConfigKey(
            purpose_t const purpose ) const;

        SIXTRL_HOST_FN kernel_config_key_t kernelConfigKey(
            purpose_t const purpose ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN kernel_config_id_t kernelConfigId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasKernelConfigId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isPurposeAssociatedWithKernelConfigId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_key_t const* ptrKernelConfigKey(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_key_t const& kernelConfigKey(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_key_t currentKernelConfigKey() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN kernel_config_key_t const& currentKernelConfigKey(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_set_id_t kernelSetId() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setKernelSetId(
            kernel_set_id_t const kernel_set_id ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool requires( purpose_t const purpose ) const;
        SIXTRL_HOST_FN bool pinned( purpose_t const purpose ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool requires( lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const;

        SIXTRL_HOST_FN bool pinned( lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool available( purpose_t const purpose ) const;
        SIXTRL_HOST_FN bool available() const;

        SIXTRL_HOST_FN bool hasKernelConfigKey(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool available( lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool available(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasKernelConfigKey(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key
            ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool canSwitchKernel(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN bool canSwitchKernels(
            kernel_config_key_t& SIXTRL_RESTRICT_REF key ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool canSwitchKernel(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN bool canSwitchKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t& SIXTRL_RESTRICT_REF key
        ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t switchKernel(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            bool is_pinned_flag = false );

        SIXTRL_HOST_FN status_t switchKernels(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN status_t switchKernel(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
            bool const pin = false );

        SIXTRL_HOST_FN status_t switchKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t syncWithStore(
            bool const perform_config_update_if_required = true );

        SIXTRL_HOST_FN status_t syncWithStore(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
            bool const perform_config_update_if_required = true );

        SIXTRL_HOST_FN status_t updateKernelOpFlags();

        SIXTRL_HOST_FN op_flags_t kernelOpFlags() const SIXTRL_NOEXCEPT;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN status_t syncWithStore(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
            bool const perform_config_update_if_required = true );

        SIXTRL_HOST_FN status_t syncWithStore(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            bool const perform_config_update_if_required = true );

        SIXTRL_HOST_FN status_t updateKernelOpFlags(
            lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool configNeedsUpdate( purpose_t const purpose ) const;

        SIXTRL_HOST_FN status_t updateConfig( purpose_t const purpose );

        SIXTRL_HOST_FN status_t updateAllConfigs();

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool configNeedsUpdate(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const;

        SIXTRL_HOST_FN status_t updateConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose );

        SIXTRL_HOST_FN status_t updateAllConfigs(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool ready( purpose_t const purpose ) const;

        SIXTRL_HOST_FN bool ready(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN bool ready() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool ready( lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool ready( lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool ready(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t reset();

        SIXTRL_HOST_FN status_t reset( purpose_t const purpose );

        SIXTRL_HOST_FN status_t resetKernelConfig(
            kernel_config_id_t const kernel_config_id );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN status_t reset(
            lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t reset( lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t resetKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t addPurpose( purpose_t const purpose );

        SIXTRL_HOST_FN status_t addPurposes(
            size_type const num_purposes,
            purpose_t const* SIXTRL_RESTRICT purposes_begin );

        template< typename PurposeIter >
        SIXTRL_HOST_FN status_t addPurposes(
            PurposeIter begin, PurposeIter end );

        SIXTRL_HOST_FN status_t removePurpose( purpose_t const purpose );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN status_t addPurpose(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose );

        SIXTRL_HOST_FN status_t addPurposes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const num_purposes,
            purpose_t const* SIXTRL_RESTRICT purposes_begin );

        template< typename PurposeIter >
        SIXTRL_HOST_FN status_t addPurposes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            PurposeIter begin, PurposeIter end );

        SIXTRL_HOST_FN status_t removePurpose(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN sync_id_value_t syncIdValue() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN sync_id_t const& syncId() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSyncWith(
            sync_id_t const& SIXTRL_RESTRICT_REF sid ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSyncWith(
            sync_id_value_t const sync_id_value ) const SIXTRL_NOEXCEPT;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN sync_id_value_t registerChange(
            lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_store_base_t const&
            kernelConfigStore() const;

        SIXTRL_HOST_FN kernel_config_store_base_t&
            kernelConfigStore();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool checkLock( lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        template< typename Derived >
        SIXTRL_HOST_FN Derived const* asDerivedKernelSet() const;

        template< typename Derived >
        SIXTRL_HOST_FN Derived* asDerivedKernelSet();

        protected:

        using purposes_to_data_map_t =
            std::unordered_map< purpose_t, kernel_set_data_t >;

        using purpose_to_data_iter_t = purposes_to_data_map_t::iterator;

        using purpose_to_data_const_iter_t =
            purposes_to_data_map_t::const_iterator;

        using purposes_list_t = std::vector< purpose_t >;

        using kernel_config_id_to_purposes_map_t =
            std::unordered_map< kernel_config_id_t, purposes_list_t >;

        using stored_kernel_op_flags_t = std::atomic< kernel_op_flags_t >;

        SIXTRL_HOST_FN kernel_config_key_t& currentKernelConfigKey(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        template< typename PurposeIter >
        SIXTRL_HOST_FN status_t doAddPurposes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            PurposeIter begin, PurposeIter end );

        SIXTRL_HOST_FN status_t doSortPurposesAndCheckForDuplicates(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual status_t doSyncWithStore(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            bool const perform_config_update_if_required );

        template< typename PurposeIter >
        SIXTRL_HOST_FN op_flags_t doUpdateKernelOpFlagsForPurposes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            PurposeIter purposes_begin, PurposeIter purposes_end,
            op_flags_t const requires_purpose_flag,
            op_flags_t const available_flag,
            op_flags_t const ready_flag );

        template< typename PurposeIter >
        SIXTRL_HOST_FN op_flags_t doSyncWithStoreForPurposes(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            PurposeIter purposes_begin, PurposeIter purposes_end,
            op_flags_t const requires_purpose_flag,
            op_flags_t const available_flag,
            op_flags_t const ready_flag,
            bool const perform_config_update_if_required = false );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t doSwitchKernel(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
            bool const is_pinned_flag );

        SIXTRL_HOST_FN status_t doAssignPurposeToKernelId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            purpose_t const purpose );

        SIXTRL_HOST_FN status_t doRemovePurposeFromKernelId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            purpose_t const purpose );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN purpose_to_data_const_iter_t doFindItemIterByPurpose(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN purpose_to_data_iter_t doFindItemIterByPurpose(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN purpose_to_data_const_iter_t doGetPurposeToDataEndIter(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN purpose_to_data_iter_t doGetPurposeToDataEndIter(
            lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void doSetIsForControllersFlag(
            bool const m_is_for_controllers ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetIsForTrackJobsFlag(
            bool const m_is_for_controllers ) SIXTRL_NOEXCEPT;

        private:

        SIXTRL_HOST_FN status_t doAddPurposeBaseImpl(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose );

        SIXTRL_HOST_FN status_t doRemovePurposeBaseImpl(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            purpose_t const purpose );

        SIXTRL_HOST_FN void doClearWithoutLocking() SIXTRL_NOEXCEPT;

        kernel_config_key_t                 m_current_key;
        purposes_to_data_map_t              m_purpose_to_data_map;
        kernel_config_id_to_purposes_map_t  m_kernel_id_to_purposes_map;
        purposes_list_t                     m_purposes;
        kernel_config_store_base_t&         m_kernel_config_store;
        stored_kernel_op_flags_t            m_kernel_op_flags;
        sync_id_t                           m_sync_id;
        kernel_set_id_t                     m_kernel_set_id;

        bool                                m_is_for_controllers;
        bool                                m_is_for_track_jobs;
    };

    class ControllerKernelSetBase : public SIXTRL_CXX_NAMESPACE::KernelSetBase
    {
        private:

        using _base_kernel_set_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;

        public:

        static constexpr purpose_t PURPOSE_REMAP_BUFFER =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER;

        SIXTRL_HOST_FN explicit ControllerKernelSetBase(
            arch_id_t const arch_id,
            kernel_config_store_base_t& SIXTRL_RESTRICT_REF kernel_conf_store );

        SIXTRL_HOST_FN ControllerKernelSetBase(
            ControllerKernelSetBase const& orig ) = default;

        SIXTRL_HOST_FN ControllerKernelSetBase(
            ControllerKernelSetBase&& orig ) = default;

        SIXTRL_HOST_FN ControllerKernelSetBase& operator=(
            ControllerKernelSetBase const& orig ) = default;

        SIXTRL_HOST_FN ControllerKernelSetBase& operator=(
            ControllerKernelSetBase&& orig ) = default;

        SIXTRL_HOST_FN virtual ~ControllerKernelSetBase() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t initDefaultControllerKernels();
        SIXTRL_HOST_FN status_t configureDefaultControllerKernels();

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t initDefaultControllerKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN status_t configureDefaultControllerKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_id_t initRemapBufferKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN status_t configureRemapBufferKernelConfig();

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN kernel_config_id_t initRemapBufferKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN status_t configureRemapBufferKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        protected:

        SIXTRL_HOST_FN  virtual status_t doInitDefaultControllerKernelConfigs(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN  virtual status_t
        doConfigureDefaultControllerKernelConfigs(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN virtual kernel_config_id_t
        doInitRemapBufferKernelConfig( lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN virtual status_t doConfigureRemapBufferKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF key );
    };
}

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

typedef SIXTRL_CXX_NAMESPACE::KernelSetBase
        NS(KernelSetBase);

typedef SIXTRL_CXX_NAMESPACE::ControllerKernelSetBase
        NS(ControllerKernelSetBase);

#else

typedef void NS(KernelSetBase);
typedef void NS(ControllerKernelSetBase);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* *****      inline and template member function implementions        ***** */
/* ************************************************************************* */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/kernel_config_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    /* ********************************************************************* */
    /* KernelSetItemData: */

    SIXTRL_INLINE KernelSetItemData::kernel_config_key_t const&
    KernelSetItemData::kernelConfigKey() const SIXTRL_NOEXCEPT
    {
        return this->m_config_key;
    }

    SIXTRL_INLINE KernelSetItemData::kernel_config_id_t
    KernelSetItemData::kernelConfigId() const SIXTRL_NOEXCEPT
    {
        return this->m_config_id;
    }

    SIXTRL_INLINE KernelSetItemData::kernel_config_base_t const*
    KernelSetItemData::ptrKernelConfigBase() const SIXTRL_NOEXCEPT
    {
        return this->m_ptr_config;
    }

    SIXTRL_INLINE KernelSetItemData::kernel_config_base_t*
    KernelSetItemData::ptrKernelConfigBase() SIXTRL_NOEXCEPT
    {
        return this->m_ptr_config;
    }

    SIXTRL_INLINE bool KernelSetItemData::available() const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetItemData;

        return ( ( this->m_config_id  != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                 ( this->m_ptr_config != nullptr ) &&
                 ( this->m_config_key.valid() ) );
    }

    SIXTRL_INLINE bool KernelSetItemData::ready() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( !this->available() ) ||
            ( this->m_ptr_config != nullptr ) );

        return ( ( this->available() ) &&
                 ( !this->m_ptr_config->needsUpdate() ) );
    }

    SIXTRL_INLINE bool KernelSetItemData::pinned() const SIXTRL_NOEXCEPT
    {
        return this->m_pinned;
    }

    SIXTRL_INLINE bool KernelSetItemData::isEqualTo(
        KernelSetItemData::kernel_config_id_t const kernel_conf_id,
        KernelSetItemData::kernel_config_base_t*
            SIXTRL_RESTRICT ptr_kernel_config ) const SIXTRL_NOEXCEPT
    {
        return ( ( kernel_conf_id == this->kernelConfigId() ) &&
                 ( ptr_kernel_config == this->ptrKernelConfigBase() ) );
    }

    SIXTRL_INLINE bool KernelSetItemData::isEqualTo(
        KernelSetItemData::kernel_config_id_t const kernel_conf_id,
        KernelSetItemData::kernel_config_base_t*
            SIXTRL_RESTRICT ptr_kernel_config,
        KernelSetItemData::kernel_config_key_t const&
            SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->isEqualTo( kernel_conf_id, ptr_kernel_config ) ) &&
                 ( this->m_config_key == key ) );
    }

    SIXTRL_INLINE bool KernelSetItemData::isEqualTo(
        KernelSetItemData::kernel_config_id_t const kernel_conf_id,
        KernelSetItemData::kernel_config_base_t*
            SIXTRL_RESTRICT ptr_kernel_config,
        KernelSetItemData::kernel_config_key_t const&
            SIXTRL_RESTRICT_REF key,
        bool const is_pinned_flag ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->isEqualTo( kernel_conf_id, ptr_kernel_config, key ) &&
                 ( this->m_pinned == is_pinned_flag ) ) );
    }

    /* ********************************************************************* */
    /* KernelSetBase: */

    template< typename PurposeIter >
    KernelSetBase::KernelSetBase(
        KernelSetBase::arch_id_t const arch_id,
        KernelSetBase::kernel_config_store_base_t& SIXTRL_RESTRICT_REF store,
        PurposeIter purposes_begin, PurposeIter purposes_end ) :
        SIXTRL_CXX_NAMESPACE::ArchInfo( arch_id ),
        m_current_key(), m_purpose_to_data_map(), m_kernel_id_to_purposes_map(),
        m_purposes(), m_kernel_config_store( store ),
        m_sync_id( KernelSetBase::sync_id_value_t{ 0 } ),
        m_kernel_set_id( KernelSetBase::ILLEGAL_KERNEL_SET_ID ),
        m_is_for_controllers( false ), m_is_for_track_jobs( false )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::KernelSetBase;
        _this_t::lock_t const lock( *store.lockable() );

        _this_t::status_t const status =
            this->doAddPurposes( lock, purposes_begin, purposes_end );

        if( status != st::ARCH_STATUS_SUCCESS )
        {
            throw std::runtime_error( "unable to init KernelSetBase" );
        }
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool KernelSetBase::isForControllers() const SIXTRL_NOEXCEPT
    {
        return this->m_is_for_controllers;
    }

    SIXTRL_INLINE bool KernelSetBase::isForTrackJobs() const SIXTRL_NOEXCEPT
    {
        return this->m_is_for_track_jobs;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelSetBase::size_type KernelSetBase::numPurposes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->numPurposes( lock );
    }

    SIXTRL_INLINE KernelSetBase::size_type KernelSetBase::numPurposes(
        KernelSetBase::kernel_config_id_t const kernel_config_id ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->numPurposes( lock, kernel_config_id );
    }

    SIXTRL_INLINE KernelSetBase::size_type
    KernelSetBase::numPinnedPurposes() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->numPinnedPurposes( lock );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE KernelSetBase::size_type KernelSetBase::numPurposes(
        lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::size_type const num_purposes = ( this->checkLock( lock ) )
            ? this->m_purposes.size() : _this_t::size_type{ 0 };

        SIXTRL_ASSERT( ( num_purposes == _this_t::size_type{ 0 } ) ||
            ( this->m_purpose_to_data_map.size() == num_purposes ) );

        return num_purposes;
    }

    SIXTRL_INLINE KernelSetBase::purpose_t const* KernelSetBase::purposesBegin(
        lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) ) ? this->m_purposes.data() : nullptr;
    }

    SIXTRL_INLINE KernelSetBase::purpose_t const* KernelSetBase::purposesEnd(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF
            lock ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::purpose_t const* ptr_end = nullptr;

        if( this->checkLock( lock ) )
        {
            ptr_end = this->m_purposes.data();

            if( ( ptr_end != nullptr ) && ( !this->m_purposes.empty() ) )
            {
                std::advance( ptr_end, this->m_purposes.size() );
            }
        }

        return ptr_end;
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE KernelSetBase::kernel_config_base_t*
    KernelSetBase::ptrKernelConfigBase(
        KernelSetBase::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->ptrKernelConfigBase( lock, purpose );
    }

    SIXTRL_INLINE KernelSetBase::kernel_config_base_t const*
    KernelSetBase::ptrKernelConfigBase(
        KernelSetBase::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->lockable() );
        return this->ptrKernelConfigBase( lock, purpose );
    }

    SIXTRL_INLINE KernelSetBase::kernel_config_base_t*
    KernelSetBase::ptrKernelConfigBase(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSetBase::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        return const_cast< _this_t::kernel_config_base_t* >(
            static_cast< _this_t const& >( *this ).ptrKernelConfigBase(
                lock, purpose ) );
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE KernelSetBase::kernel_config_id_t
    KernelSetBase::kernelConfigId(
        KernelSetBase::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->kernelConfigId( lock, purpose );
    }

    SIXTRL_INLINE bool KernelSetBase::hasKernelConfigId(
        KernelSetBase::kernel_config_id_t const kernel_config_id ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->hasKernelConfigId( lock, kernel_config_id );
    }

    SIXTRL_INLINE bool KernelSetBase::isPurposeAssociatedWithKernelConfigId(
        KernelSetBase::kernel_config_id_t const kernel_config_id,
        KernelSetBase::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->isPurposeAssociatedWithKernelConfigId(
            lock, kernel_config_id, purpose );
    }

    SIXTRL_INLINE KernelSetBase::kernel_config_key_t const*
    KernelSetBase::ptrKernelConfigKey(
        KernelSetBase::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->ptrKernelConfigKey( lock, purpose );
    }

    SIXTRL_INLINE KernelSetBase::kernel_config_key_t
    KernelSetBase::kernelConfigKey(
        KernelSetBase::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->kernelConfigKey( lock, purpose );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelSetBase::kernel_config_key_t
    KernelSetBase::currentKernelConfigKey() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->currentKernelConfigKey( lock );
    }

    SIXTRL_INLINE KernelSetBase::kernel_config_key_t&
    KernelSetBase::currentKernelConfigKey(
            KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        return const_cast< _this_t::kernel_config_key_t& >( static_cast<
            _this_t const& >( *this ).currentKernelConfigKey( lock ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelSetBase::kernel_set_id_t
    KernelSetBase::kernelSetId() const SIXTRL_NOEXCEPT
    {
        return this->m_kernel_set_id;
    }

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::setKernelSetId(
        KernelSetBase::kernel_set_id_t const kernel_set_id ) SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::KernelSetBase;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_set_id == _this_t::ILLEGAL_KERNEL_SET_ID ) ||
            ( this->m_kernel_set_id == _this_t::ILLEGAL_KERNEL_SET_ID ) )
        {
            this->m_kernel_set_id = kernel_set_id;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool KernelSetBase::requires(
        KernelSetBase::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->requires( lock, purpose );
    }

    SIXTRL_INLINE bool KernelSetBase::pinned(
        KernelSetBase::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->pinned( lock, purpose );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE bool KernelSetBase::requires(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSetBase::purpose_t const purpose ) const
    {
        return ( ( this->doFindItemIterByPurpose( lock, purpose ) !=
                   this->m_purpose_to_data_map.end() ) &&
                 ( this->checkLock( lock ) ) );
    }

    SIXTRL_INLINE bool KernelSetBase::pinned(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSetBase::purpose_t const purpose ) const
    {
        auto it = this->doFindItemIterByPurpose( lock, purpose );
        return ( ( it != this->m_purpose_to_data_map.end() ) &&
                 ( this->checkLock( lock ) ) && ( it->second.pinned() ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool KernelSetBase::available(
        KernelSetBase::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->available( lock, purpose );
    }

    SIXTRL_INLINE bool KernelSetBase::available() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->available( lock );
    }

    SIXTRL_INLINE bool KernelSetBase::hasKernelConfigKey(
        KernelSetBase::kernel_config_key_t const&
            SIXTRL_RESTRICT_REF key ) const
    {
        using _store_t = SIXTRL_CXX_NAMESPACE::KernelConfigStore;
        _store_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->hasKernelConfigKey( lock, key );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE bool KernelSetBase::available(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSetBase::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        auto it = this->doFindItemIterByPurpose( lock, purpose );
        return ( ( it != this->m_purpose_to_data_map.end() ) &&
                 ( this->checkLock( lock ) ) &&
                 ( it->second.available() ) );
    }

    SIXTRL_INLINE bool KernelSetBase::hasKernelConfigKey(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSetBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key
    ) const SIXTRL_NOEXCEPT
    {
        return ( ( key.valid() ) &&
                 ( this->requires( lock, key.purpose() ) ) &&
                 ( this->checkLock( lock ) ) &&
                 ( this->m_current_key.isEqualExceptPurpose( key ) ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool KernelSetBase::canSwitchKernel(
        KernelSetBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->canSwitchKernel( lock, key );
    }

    SIXTRL_INLINE bool KernelSetBase::canSwitchKernels(
        KernelSetBase::kernel_config_key_t& SIXTRL_RESTRICT_REF key ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->canSwitchKernels( lock, key );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::switchKernel(
        KernelSetBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        bool const is_pinned_flag )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->switchKernel( lock, key, is_pinned_flag );
    }

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::switchKernels(
        KernelSetBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->switchKernels( lock, key );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::syncWithStore(
        bool const perform_config_update_if_required  )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->doSyncWithStore( lock, perform_config_update_if_required );
    }

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::syncWithStore(
        KernelSetBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        bool const perform_config_update_if_required  )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->syncWithStore(
            lock, key, perform_config_update_if_required );
    }

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::updateKernelOpFlags()
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->updateKernelOpFlags( lock );
    }

    SIXTRL_INLINE KernelSetBase::op_flags_t
    KernelSetBase::kernelOpFlags() const SIXTRL_NOEXCEPT
    {
        return this->m_kernel_op_flags.load();
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::syncWithStore(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSetBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        bool const perform_config_update_if_required  )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::KernelSetBase;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            this->m_current_key = key;
            status = this->doSyncWithStore(
                lock, perform_config_update_if_required );
        }

        return status;
    }

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::syncWithStore(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        bool const perform_config_update_if_required )
    {
        return this->doSyncWithStore( lock, perform_config_update_if_required );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool KernelSetBase::configNeedsUpdate(
        KernelSetBase::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->configNeedsUpdate( lock, purpose );
    }

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::updateConfig(
        KernelSetBase::purpose_t const purpose )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->updateConfig( lock, purpose );
    }

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::updateAllConfigs()
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->updateAllConfigs( lock );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE bool KernelSetBase::configNeedsUpdate(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSetBase::purpose_t const purpose ) const
    {
        auto it = this->doFindItemIterByPurpose( lock, purpose );

        return ( ( it != this->m_purpose_to_data_map.end() ) &&
                 ( this->checkLock( lock ) ) &&
                 ( it->second.ptrKernelConfigBase() != nullptr ) &&
                 ( it->second.ptrKernelConfigBase()->needsUpdate() ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool KernelSetBase::ready(
        KernelSetBase::purpose_t const purpose ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->ready( lock, purpose );
    }

    SIXTRL_INLINE bool KernelSetBase::ready(
        KernelSetBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->ready( lock, key );
    }

    SIXTRL_INLINE bool KernelSetBase::ready() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->ready( lock );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE bool KernelSetBase::ready(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSetBase::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        auto it = this->doFindItemIterByPurpose( lock, purpose );

        return ( ( it != this->m_purpose_to_data_map.end() ) &&
                 ( this->checkLock( lock ) ) &&
                 ( it->second.ready() ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::reset()
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->reset( lock );
    }

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::reset(
        KernelSetBase::purpose_t const purpose )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->reset( lock, purpose );
    }

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::resetKernelConfig(
        KernelSetBase::kernel_config_id_t const kernel_config_id )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->resetKernelConfig( lock, kernel_config_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::addPurpose(
        purpose_t const purpose )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->addPurpose( lock, purpose );
    }

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::addPurposes(
        KernelSetBase::size_type const num_purposes,
        KernelSetBase::purpose_t const* SIXTRL_RESTRICT purposes_begin )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->addPurposes( lock, num_purposes, purposes_begin );
    }

    template< typename PurposeIter >
    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::addPurposes(
        PurposeIter begin, PurposeIter end )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->addPurposes( lock, begin, end );
    }

    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::removePurpose(
        KernelSetBase::purpose_t const purpose )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->removePurpose( lock, purpose );
    }

    /* -- -- -- -- ---- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

    template< typename PurposeIter >
    SIXTRL_INLINE KernelSetBase::status_t KernelSetBase::addPurposes(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        PurposeIter begin, PurposeIter end )
    {
        return this->doAddPurposeBaseImpl( lock, begin, end );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelSetBase::sync_id_value_t
    KernelSetBase::syncIdValue() const SIXTRL_NOEXCEPT
    {
        return this->m_sync_id.load();
    }

    SIXTRL_INLINE KernelSetBase::sync_id_t const&
    KernelSetBase::syncId() const SIXTRL_NOEXCEPT
    {
        return this->m_sync_id;
    }

    SIXTRL_INLINE bool KernelSetBase::isSyncWith(
            KernelSetBase::sync_id_t const& SIXTRL_RESTRICT_REF other_sync_id
        ) const SIXTRL_NOEXCEPT
    {
        return this->isSyncWith( other_sync_id.load() );
    }

    SIXTRL_INLINE bool KernelSetBase::isSyncWith(
            KernelSetBase::sync_id_value_t const sync_id_value
        ) const SIXTRL_NOEXCEPT
    {
        return ( this->syncIdValue() == sync_id_value );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE KernelSetBase::sync_id_value_t KernelSetBase::registerChange(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        _this_t::sync_id_value_t new_value = _this_t::ILLEGAL_SYNC_ID_VALUE;

        if( this->checkLock( lock ) )
        {
            _this_t::sync_id_value_t const current_value = this->syncIdValue();

            if( current_value < _this_t::LAST_LEGAL_SYNC_ID_VALUE )
            {
                new_value = ++this->m_sync_id;
            }
            else if( current_value == _this_t::LAST_LEGAL_SYNC_ID_VALUE )
            {
                new_value = _this_t::sync_id_value_t{ 0 };
                this->m_sync_id.store( new_value );
            }
        }

        return new_value;
    }

    /* --------------------------------------------------------------------- */


    SIXTRL_INLINE KernelSetBase::kernel_config_store_base_t const&
    KernelSetBase::kernelConfigStore() const
    {
        return this->m_kernel_config_store;
    }

    SIXTRL_INLINE KernelSetBase::kernel_config_store_base_t&
    KernelSetBase::kernelConfigStore()
    {
        return this->m_kernel_config_store;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool KernelSetBase::checkLock( KernelSetBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return this->m_kernel_config_store.checkLock( lock );
    }

    SIXTRL_INLINE KernelSetBase::lockable_t*
    KernelSetBase::lockable() const SIXTRL_NOEXCEPT
    {
        return this->m_kernel_config_store.lockable();
    }

    /* --------------------------------------------------------------------- */

    template< typename Derived >
    SIXTRL_INLINE Derived const* KernelSetBase::asDerivedKernelSet() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;

        static_assert( std::is_base_of< _this_t, Derived >::value,
            "asDerivedKernelSet< Derived > requires Derived to "
            "be derived from SIXTRL_CXX_NAMESPACE::KernelSetBase" );

        return static_cast< Derived const* >( this );
    }

    template< typename Derived >
    SIXTRL_INLINE Derived* KernelSetBase::asDerivedKernelSet()
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;
        return const_cast< Derived* >( static_cast< _this_t const& >(
            *this ).asDerivedKernelSet< Derived >() );
    }

    /* --------------------------------------------------------------------- */

    template< typename PurposeIter >
    KernelSetBase::status_t KernelSetBase::doAddPurposes(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        PurposeIter it, PurposeIter end )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::KernelSetBase;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        std::ptrdiff_t const len = std::distance( it, end );

        if( len > std::ptrdiff_t{ 0 } )
        {
            bool has_been_added = false;

            for(  ; it != end ; ++it )
            {
                status = this->doAddPurposeBaseImpl( lock, *it );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    has_been_added = true;
                }
                else
                {
                    break;
                }
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->doSortPurposesAndCheckForDuplicates( lock );
            }

            if( has_been_added )
            {
                this->registerChange( lock );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    template< typename PurposeIter >
    KernelSetBase::op_flags_t KernelSetBase::doUpdateKernelOpFlagsForPurposes(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        PurposeIter it, PurposeIter end,
        KernelSetBase::op_flags_t const requires_purposes_flag,
        KernelSetBase::op_flags_t const all_available_flag,
        KernelSetBase::op_flags_t const all_ready_flag )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::KernelSetBase;

        _this_t::op_flags_t op_flags = st::KERNEL_OP_FLAGS_NONE;

        if( ( std::distance( it, end ) > std::ptrdiff_t{ 0 } ) &&
            ( ( requires_purposes_flag != all_available_flag ) ||
              ( requires_purposes_flag == st::KERNEL_OP_FLAGS_NONE ) ) &&
            ( ( all_available_flag != all_ready_flag ) ||
              ( all_available_flag == st::KERNEL_OP_FLAGS_NONE ) ) &&
            ( ( all_ready_flag != requires_purposes_flag ) ||
              ( all_ready_flag == st::KERNEL_OP_FLAGS_NONE ) ) &&
            ( this->checkLock( lock ) ) )
        {
            bool has_purposes = true;
            bool are_available = true;
            bool are_ready = true;

            for( ; it != end ; ++it )
            {
                _this_t::purpose_t const purpose = *it;

                auto find_it = this->doFindItemIterByPurpose( lock, purpose );

                if( find_it == this->doGetPurposeToDataEndIter( lock ) )
                {
                    has_purposes = false;
                    are_available = false;
                    are_ready = false;
                    break;
                }

                if( !find_it->second.available() )
                {
                    are_available = false;
                    are_ready = false;
                    break;
                }

                if( !find_it->second.ready() )
                {
                    are_ready = false;
                    break;
                }
            }

            if( ( has_purposes ) &&
                ( requires_purposes_flag != st::KERNEL_OP_FLAGS_NONE ) )
            {
                op_flags |= requires_purposes_flag;
            }

            if( ( are_available ) &&
                ( all_available_flag != st::KERNEL_OP_FLAGS_NONE ) )
            {
                op_flags |= all_available_flag;
            }

            if( ( are_ready ) && ( all_ready_flag != st::KERNEL_OP_FLAGS_NONE ) )
            {
                op_flags |= all_ready_flag;
            }
        }

        return op_flags;
    }

    template< typename PurposeIter >
    KernelSetBase::op_flags_t KernelSetBase::doSyncWithStoreForPurposes(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        PurposeIter it, PurposeIter end,
        KernelSetBase::op_flags_t const requires_purposes_flag,
        KernelSetBase::op_flags_t const all_available_flag,
        KernelSetBase::op_flags_t const all_ready_flag,
        bool const perform_config_update_if_required )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::KernelSetBase;
        using config_id_t = _this_t::kernel_config_id_t;
        using config_key_t = _this_t::kernel_config_key_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        _this_t::op_flags_t op_flags = st::KERNEL_OP_FLAGS_NONE;
        _this_t::kernel_config_store_base_t& store = this->kernelConfigStore();

        if( ( std::distance( it, end ) > std::ptrdiff_t{ 0 } ) &&
            ( ( requires_purposes_flag != all_available_flag ) ||
              ( requires_purposes_flag == st::KERNEL_OP_FLAGS_NONE ) ) &&
            ( ( all_available_flag != all_ready_flag ) ||
              ( all_available_flag == st::KERNEL_OP_FLAGS_NONE ) ) &&
            ( ( all_ready_flag != requires_purposes_flag ) ||
              ( all_ready_flag == st::KERNEL_OP_FLAGS_NONE ) ) &&
            ( this->checkLock( lock ) ) )
        {
            bool has_been_updated = false;
            config_key_t current_key = this->currentKernelConfigKey( lock );

            bool has_purposes = true;
            bool are_available = true;
            bool are_ready = true;

            _this_t::status_t status = st::ARCH_STATUS_SUCCESS;

            for( ; it != end ; ++it )
            {
                _this_t::purpose_t const purpose = *it;

                auto find_it = this->doFindItemIterByPurpose( lock, purpose );

                if( find_it == this->doGetPurposeToDataEndIter( lock ) )
                {
                    has_purposes = false;
                    are_available = false;
                    are_ready = false;
                    break;
                }

                config_id_t purpose_conf_id  = find_it->second.kernelConfigId();
                config_key_t const* ptr_purpose_key = nullptr;

                if( ( purpose_conf_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                    ( find_it->second.kernelConfigKey().valid() ) )
                {
                    purpose_conf_id = store.kernelId(
                        lock, find_it->second.kernelConfigKey() );

                    if( ( purpose_conf_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                        ( store.hasDefaultInitKernelConfigParameters(
                            lock, find_it->second.kernelConfigKey() ) ) )
                    {
                        purpose_conf_id = store.initKernelConfig( lock,
                            find_it->second.kernelConfigKey() );

                        has_been_updated = true;
                    }
                }

                if( ( purpose_conf_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                    ( find_it->second.kernelConfigKey().valid() ) )
                {
                    ptr_purpose_key = &find_it->second.kernelConfigKey();
                }

                if( ( purpose_conf_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                    ( current_key.valid() ) )
                {
                    SIXTRL_ASSERT( ptr_purpose_key == nullptr );

                    current_key.setPurpose( purpose );
                    purpose_conf_id = store.kernelId( lock, current_key );

                    if( ( purpose_conf_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                        ( store.hasDefaultInitKernelConfigParameters(
                            lock, current_key ) ) )
                    {
                        purpose_conf_id = store.initKernelConfig(
                            lock, current_key );

                        has_been_updated = true;
                    }

                    if( purpose_conf_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID )
                    {
                        ptr_purpose_key = &current_key;
                    }
                }

                if( ( purpose_conf_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID ) ||
                    ( ptr_purpose_key == nullptr ) ||
                    ( !ptr_purpose_key->valid() ) )
                {
                    are_available = false;
                    are_ready = false;
                    continue;
                }

                SIXTRL_ASSERT( purpose_conf_id !=
                    _this_t::ILLEGAL_KERNEL_CONFIG_ID );

                SIXTRL_ASSERT( ptr_purpose_key != nullptr );

                if( !this->isPurposeAssociatedWithKernelConfigId(
                        lock, purpose_conf_id, purpose ) )
                {
                    status = this->doAssignPurposeToKernelId( lock,
                        purpose_conf_id, purpose );

                    if( status != st::ARCH_STATUS_SUCCESS )
                    {
                        break;
                    }
                }

                ptr_config_t ptr_config =
                    store.ptrKernelConfigBase( lock, purpose_conf_id );

                if( ptr_config == nullptr )
                {
                    are_ready = false;
                    continue;
                }

                if( !find_it->second.isEqualTo( purpose_conf_id, ptr_config,
                        *ptr_purpose_key ) )
                {
                    bool is_pinned_flag = find_it->second.pinned();

                    if( ( !is_pinned_flag ) &&
                        ( current_key.valid() ) &&
                        ( ptr_purpose_key != &current_key ) )
                    {
                        is_pinned_flag = true;
                    }

                    if( find_it->second.reset( purpose_conf_id, ptr_config,
                        *ptr_purpose_key, is_pinned_flag ) ==
                            st::ARCH_STATUS_SUCCESS )
                    {
                        has_been_updated = true;
                    }
                    else
                    {
                        are_available = false;
                        are_ready = false;
                        continue;
                    }
                }

                SIXTRL_ASSERT( find_it->second.available() );
                SIXTRL_ASSERT( find_it->second.ptrKernelConfigBase() != nullptr );

                if( !find_it->second.ready() )
                {
                    if( ( perform_config_update_if_required ) &&
                        ( find_it->second.ptrKernelConfigBase()->needsUpdate() ) )
                    {
                        find_it->second.ptrKernelConfigBase()->update();
                    }

                    if( !find_it->second.ptrKernelConfigBase()->needsUpdate() )
                    {
                        has_been_updated = true;
                    }
                    else
                    {
                        are_ready = false;
                        continue;
                    }
                }
            }

            if( has_been_updated )
            {
                this->registerChange( lock );
            }

            if( status != st::ARCH_STATUS_SUCCESS )
            {
                return op_flags;
            }

            if( ( has_purposes ) &&
                ( requires_purposes_flag != st::KERNEL_OP_FLAGS_NONE ) )
            {
                op_flags |= requires_purposes_flag;
            }

            if( ( are_available ) &&
                ( all_available_flag != st::KERNEL_OP_FLAGS_NONE ) )
            {
                op_flags |= all_available_flag;
            }

            if( ( are_ready ) && ( all_ready_flag != st::KERNEL_OP_FLAGS_NONE ) )
            {
                op_flags |= all_ready_flag;
            }
        }

        return op_flags;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelSetBase::purpose_to_data_const_iter_t
    KernelSetBase::doFindItemIterByPurpose(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSetBase::purpose_t const purpose ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;

        _this_t::purpose_to_data_const_iter_t it =
            this->m_purpose_to_data_map.end();

        if( ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->checkLock( lock ) ) )
        {
            it = this->m_purpose_to_data_map.find( purpose );
        }

        return it;
    }

    SIXTRL_INLINE KernelSetBase::purpose_to_data_iter_t
    KernelSetBase::doFindItemIterByPurpose(
        KernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelSetBase::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelSetBase;

        _this_t::purpose_to_data_iter_t it = this->m_purpose_to_data_map.end();

        if( ( purpose != _this_t::UNSPECIFIED_PUPRPOSE ) &&
            ( this->checkLock( lock ) ) )
        {
            it = this->m_purpose_to_data_map.find( purpose );
        }

        return it;
    }

    SIXTRL_INLINE KernelSetBase::purpose_to_data_const_iter_t
    KernelSetBase::doGetPurposeToDataEndIter( KernelSetBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        ( void )lock;

        return this->m_purpose_to_data_map.end();
    }

    SIXTRL_INLINE KernelSetBase::purpose_to_data_iter_t
    KernelSetBase::doGetPurposeToDataEndIter( KernelSetBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->checkLock( lock ) );
        ( void )lock;

        return this->m_purpose_to_data_map.end();
    }

    /* ********************************************************************* */
    /* ControllerKernelSetBase: */

    SIXTRL_INLINE ControllerKernelSetBase::status_t
    ControllerKernelSetBase::initDefaultControllerKernels()
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerKernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->doInitDefaultControllerKernelConfigs(
            lock, this->currentKernelConfigKey( lock ) );
    }

    SIXTRL_INLINE ControllerKernelSetBase::status_t
    ControllerKernelSetBase::initDefaultControllerKernels(
        ControllerKernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        return this->doInitDefaultControllerKernelConfigs(
            lock, this->currentKernelConfigKey( lock ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    SIXTRL_INLINE ControllerKernelSetBase::status_t
    ControllerKernelSetBase::configureDefaultControllerKernels()
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerKernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->doConfigureDefaultControllerKernelConfigs( lock );
    }

    SIXTRL_INLINE ControllerKernelSetBase::status_t
    ControllerKernelSetBase::configureDefaultControllerKernels(
        ControllerKernelSetBase::lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        return this->doConfigureDefaultControllerKernelConfigs( lock );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE ControllerKernelSetBase::kernel_config_id_t
    ControllerKernelSetBase::initRemapBufferKernelConfig(
        ControllerKernelSetBase::kernel_config_key_t const&
            SIXTRL_RESTRICT_REF key )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerKernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->initRemapBufferKernelConfig( lock, key );
    }

    SIXTRL_INLINE ControllerKernelSetBase::status_t
    ControllerKernelSetBase::configureRemapBufferKernelConfig()
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerKernelSetBase;
        _this_t::lock_t const lock( *this->kernelConfigStore().lockable() );
        return this->configureRemapBufferKernelConfig( lock );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_SET_CXX_HPP__ */

/* end: sixtracklib/common/control/required_kernels_list.hpp */
