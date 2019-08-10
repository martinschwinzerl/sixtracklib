#ifndef SIXTRACKLIB_COMMON_CONTROL_CONTROLLER_BASE_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_CONTROLLER_BASE_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <atomic>
    #include <cstddef>
    #include <cstdlib>
    #include <cstdio>
    #include <stdexcept>
    #include <memory>
    #include <mutex>
    #include <ostream>
    #include <string>
    #include <sstream>
    #include <thread>
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
    #include "sixtracklib/common/control/kernel_set.hpp"
    #include "sixtracklib/common/control/kernel_config_store.hpp"
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class ArgumentBase;

    class ControllerBase : public SIXTRL_CXX_NAMESPACE::ArchDebugBase
    {
        private:

        using _base_arch_obj_t = SIXTRL_CXX_NAMESPACE::ArchDebugBase;

        public:

        using arch_id_t = _base_arch_obj_t::arch_id_t;
        using status_t = _base_arch_obj_t::status_t;
        using debug_register_t = _base_arch_obj_t::debug_register_t;

        using kernel_config_store_base_t =
            SIXTRL_CXX_NAMESPACE::KernelConfigStore;

        using ptr_kernel_config_store_t =
            std::unique_ptr< kernel_config_store_base_t >;

        using kernel_set_t      = kernel_config_store_base_t::kernel_set_t;
        using kernel_set_id_t   = kernel_config_store_base_t::kernel_set_id_t;
        using ptr_kernel_set_t  = std::unique_ptr< kernel_set_t >;

        using kernel_lockable_t = kernel_config_store_base_t::lockable_t;
        using kernel_lock_t     = kernel_config_store_base_t::lock_t;

        using buffer_t          = SIXTRL_CXX_NAMESPACE::Buffer;
        using c_buffer_t        = buffer_t::c_api_t;
        using size_type         = buffer_t::size_type;

        using kernel_config_base_t    = kernel_set_t::kernel_config_base_t;
        using kernel_id_t             = kernel_set_t::kernel_config_id_t;
        using kernel_config_key_t     = kernel_set_t::kernel_config_key_t;
        using kernel_purpose_t        = kernel_set_t::purpose_t;
        using sync_id_value_t         = kernel_set_t::sync_id_value_t;

        using arg_base_ref_t          = ArgumentBase&;
        using ptr_arg_base_t          = ArgumentBase*;
        using ptr_const_arg_base_t    = ArgumentBase const*;

        using perform_remap_flag_t =
            SIXTRL_CXX_NAMESPACE::ctrl_perform_remap_flag_t;

        /* ----------------------------------------------------------------- */

        static SIXTRL_CONSTEXPR_OR_CONST arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static SIXTRL_CONSTEXPR_OR_CONST arch_id_t NO_ARCH_ID =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_NONE;

        static SIXTRL_CONSTEXPR_OR_CONST kernel_id_t ILLEGAL_KERNEL_CONFIG_ID =
            SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_KERNEL_ID;

        static SIXTRL_CONSTEXPR_OR_CONST kernel_set_id_t ILLEGAL_KERNEL_SET_ID =
            SIXTRL_CXX_NAMESPACE::ILLEGAL_KERNEL_SET_ID;

        static SIXTRL_CONSTEXPR_OR_CONST sync_id_value_t ILLEGAL_SYNC_ID_VALUE =
            kernel_set_t::ILLEGAL_SYNC_ID_VALUE;

        static SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t UNSPECIFIED_PURPOSE =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;

        static SIXTRL_CONSTEXPR_OR_CONST kernel_purpose_t PURPOSE_REMAP_BUFFER =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool usesNodes() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN void clear();

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN void clear(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasName() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& name() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrNameStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setName(
            std::string const& SIXTRL_RESTRICT_REF name );

        SIXTRL_HOST_FN void setName( char const* SIXTRL_RESTRICT name );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_key_t defaultKey() const;
        SIXTRL_HOST_FN bool hasDefaultKernelConfigStr() const;
        SIXTRL_HOST_FN char const* ptrDefaultKernelConfigStr() const;

        SIXTRL_HOST_FN status_t setDefaultVariant(
            variant_t const default_variant_flags );

        SIXTRL_HOST_FN status_t setDefaultConfigStr(
            std::string const& SIXTRL_RESTRICT_REF default_config_str );

        SIXTRL_HOST_FN status_t setDefaultConfigStr(
            char const* SIXTRL_RESTRICT default_config_str );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN kernel_config_key_t const& defaultKey(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lk ) const;

        SIXTRL_HOST_FN bool hasDefaultKernelConfigStr(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lk ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN char const* ptrDefaultKernelConfigStr(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lk ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setDefaultVariant(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
            variant_t const default_variant_flags ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setDefaultConfigStr(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
            std::string const& SIXTRL_RESTRICT_REF default_config_str );

        SIXTRL_HOST_FN status_t setDefaultConfigStr(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
            char const* SIXTRL_RESTRICT default_config_str );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool isSyncWithKernelSet() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_t syncWithKernelSet();

        SIXTRL_HOST_FN bool readyForSend()    const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool readyForReceive() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool readyForRemap()   const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool readyForRunningKernels() const SIXTRL_NOEXCEPT;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN status_t syncWithKernelSet(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN bool readyForSend(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN bool readyForReceive(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN bool readyForRemap(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN bool readyForRunningKernels(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ================================================================= */

        SIXTRL_HOST_FN status_t send( ptr_arg_base_t SIXTRL_RESTRICT dest,
            void const* SIXTRL_RESTRICT source, size_type const src_length );

        SIXTRL_HOST_FN status_t send( ptr_arg_base_t SIXTRL_RESTRICT dest,
            const c_buffer_t *const SIXTRL_RESTRICT source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_REMAP );

        SIXTRL_HOST_FN status_t send( ptr_arg_base_t SIXTRL_RESTRICT dest,
            buffer_t const& SIXTRL_RESTRICT_REF source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_REMAP );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN status_t send(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            ptr_arg_base_t SIXTRL_RESTRICT dest,
            void const* SIXTRL_RESTRICT source, size_type const src_length );

        SIXTRL_HOST_FN status_t send(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            ptr_arg_base_t SIXTRL_RESTRICT dest,
            const c_buffer_t *const SIXTRL_RESTRICT source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_REMAP );

        SIXTRL_HOST_FN status_t send(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            ptr_arg_base_t SIXTRL_RESTRICT dest,
            buffer_t const& SIXTRL_RESTRICT_REF source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_REMAP );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t receive(
            void* SIXTRL_RESTRICT destination,
            size_type const destination_capacity,
            ptr_arg_base_t SIXTRL_RESTRICT source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_NO_REMAP );

        SIXTRL_HOST_FN status_t receive(
            c_buffer_t* SIXTRL_RESTRICT dest,
            ptr_arg_base_t SIXTRL_RESTRICT source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_REMAP );

        SIXTRL_HOST_FN status_t receive(
            buffer_t& SIXTRL_RESTRICT_REF dest,
            ptr_arg_base_t SIXTRL_RESTRICT source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_REMAP );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN status_t receive(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            void* SIXTRL_RESTRICT destination,
            size_type const destination_capacity,
            ptr_arg_base_t SIXTRL_RESTRICT source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_NO_REMAP );

        SIXTRL_HOST_FN status_t receive(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            c_buffer_t* SIXTRL_RESTRICT dest,
            ptr_arg_base_t SIXTRL_RESTRICT source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_REMAP );

        SIXTRL_HOST_FN status_t receive(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            buffer_t& SIXTRL_RESTRICT_REF dest,
            ptr_arg_base_t SIXTRL_RESTRICT source,
            perform_remap_flag_t const perform_remap_flag =
                SIXTRL_CXX_NAMESPACE::CTRL_PERFORM_REMAP );

        /* ================================================================= */

        SIXTRL_HOST_FN status_t remap( ptr_arg_base_t SIXTRL_RESTRICT arg );

        SIXTRL_HOST_FN status_t remap(
            arg_base_ref_t SIXTRL_RESTRICT_REF arg );

        SIXTRL_HOST_FN bool isRemapped( ptr_arg_base_t SIXTRL_RESTRICT arg );

        SIXTRL_HOST_FN bool isRemapped(
            arg_base_ref_t SIXTRL_RESTRICT_REF arg );

        /* ================================================================= */

        SIXTRL_HOST_FN bool hasKernelConfigStore()  const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool ownsKernelConfigStore() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_store_base_t const*
        ptrKernelConfigStore() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_store_base_t const&
        kernelConfigStore() const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_set_id_t kernelSetId() const;
        SIXTRL_HOST_FN kernel_set_id_t kernelSetId( kernel_lock_t const&
            SIXTRL_RESTRICT_REF kernel_lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasKernelSet() const;
        SIXTRL_HOST_FN bool hasKernelSet( kernel_lock_t const&
            SIXTRL_RESTRICT_REF kernel_lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_set_t const* ptrKernelSetBase() const;
        SIXTRL_HOST_FN kernel_set_t const& kernelSetBase() const;

        SIXTRL_HOST_FN kernel_set_t const* ptrKernelSetBase(
            kernel_lock_t const& SIXTRL_RESTRICT_REF ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_set_t const& kernelSetBase(
            kernel_lock_t const& SIXTRL_RESTRICT_REF ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool checkKernelLock( kernel_lock_t const&
            SIXTRL_RESTRICT_REF kernel_lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void checkKernelLockThrowOnFailure(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock ) const;

        SIXTRL_HOST_FN kernel_lockable_t* kernelLockable() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasRemapBufferKernel() const;
        SIXTRL_HOST_FN kernel_id_t remapBufferKernelConfigId() const;
        SIXTRL_HOST_FN kernel_config_key_t remapBufferKernelConfigKey() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool hasRemapBufferKernel(
                kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock
            ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_id_t remapBufferKernelConfigId(
                kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock
            ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_key_t const& remapBufferKernelConfigKey(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_key_t currentKey() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN kernel_config_key_t const& currentKey(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        /* ================================================================= */

        SIXTRL_HOST_FN status_t changeVariantFlags( variant_t const var );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN status_t changeVariantFlags(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            variant_t const new_variant_flags );

        /* ================================================================= */

        SIXTRL_HOST_FN void print(
            std::ostream& SIXTRL_RESTRICT_REF output ) const;

        SIXTRL_HOST_FN void print(
            ::FILE* SIXTRL_RESTRICT output ) const;

        SIXTRL_HOST_FN void printOut() const;

        SIXTRL_HOST_FN size_type requiredOutStringLength() const;

        SIXTRL_HOST_FN std::string toString() const;

        SIXTRL_HOST_FN status_t toString(
            size_type const str_repr_capacity,
            char* SIXTRL_RESTRICT str_repr_begin ) const SIXTRL_NOEXCEPT;

        /* ================================================================= */

        SIXTRL_HOST_FN virtual ~ControllerBase() = default;

        template< class Derived >
        SIXTRL_HOST_FN Derived const* asDerivedController(
            arch_id_t const requ_arch_id,
            bool const exact_match_required = false ) const SIXTRL_NOEXCEPT;

        template< class Derived >
        SIXTRL_HOST_FN Derived* asDerivedController(
            arch_id_t const requ_arch_id,
            bool const exact_match_required = false ) SIXTRL_NOEXCEPT;

        /* ================================================================= */

        protected:

        using op_flags_t = kernel_set_t::op_flags_t;

        SIXTRL_STATIC bool AreOpFlagsSet(
            op_flags_t const haystack, op_flags_t const needle ) SIXTRL_NOEXCEPT
        {
            return ( ( needle != SIXTRL_CXX_NAMESPACE::KERNEL_OP_FLAGS_NONE ) &&
                     ( ( haystack & needle ) == needle ) );
        }

        SIXTRL_STATIC op_flags_t AddOpFlags(
            op_flags_t const haystack, op_flags_t const needle ) SIXTRL_NOEXCEPT
        {
            return ( haystack | needle );
        }

        SIXTRL_STATIC op_flags_t RemoveOpFlags(
            op_flags_t const haystack, op_flags_t const needle ) SIXTRL_NOEXCEPT
        {
            return ( haystack & ( ~needle ) );
        }

        SIXTRL_HOST_FN ControllerBase(
            arch_id_t const arch_id,
            kernel_config_store_base_t* SIXTRL_RESTRICT
                ptr_kernel_config_store = nullptr,
            kernel_set_id_t const kernel_set_id = ILLEGAL_KERNEL_SET_ID,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN ControllerBase(
            arch_id_t const arch_id,
            ptr_kernel_config_store_t&& kernel_config_store,
            kernel_set_id_t const kernel_set = ILLEGAL_KERNEL_SET_ID,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN ControllerBase( ControllerBase const& other ) = default;
        SIXTRL_HOST_FN ControllerBase( ControllerBase&& other ) = default;

        SIXTRL_HOST_FN ControllerBase&
        operator=( ControllerBase const& rhs ) = default;

        SIXTRL_HOST_FN ControllerBase&
        operator=( ControllerBase&& rhs ) = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_store_base_t*
        ptrKernelConfigStore() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_store_base_t& kernelConfigStore();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_set_t* ptrKernelSetBase(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_set_t& kernelSetBase(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool doCheckOpFlag(
            op_flags_t const check_for_these_flags ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool doCheckOpFlagAndUpdateIfRequired(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            op_flags_t const check_for_these_flags );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual void doClear(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock );

        SIXTRL_HOST_FN virtual status_t doChangeVariantFlags(
            variant_t const new_variant_flags ) override;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN virtual status_t doSend(
            ptr_arg_base_t SIXTRL_RESTRICT destination,
            const void *const SIXTRL_RESTRICT source,
            size_type const source_length );

        SIXTRL_HOST_FN virtual status_t doReceive(
            void* SIXTRL_RESTRICT destination, size_type const dest_capacity,
            ptr_arg_base_t SIXTRL_RESTRICT source );

        SIXTRL_HOST_FN virtual status_t doRemapCObjectsBufferArg(
            ptr_arg_base_t SIXTRL_RESTRICT arg );

        SIXTRL_HOST_FN virtual bool doIsCObjectsBufferArgRemapped(
            ptr_arg_base_t SIXTRL_RESTRICT arg,
            status_t* SIXTRL_RESTRICT ptr_status );

        SIXTRL_HOST_FN virtual status_t doSyncWithKernelSet(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock );

        SIXTRL_HOST_FN virtual status_t doPrintToOutputStream(
            std::ostream& SIXTRL_RESTRICT_REF output ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_key_t& defaultKey(
            kernel_lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t doUpdateOwnKernelConfigStore(
            kernel_lock_t& SIXTRL_RESTRICT kernel_lock,
            ptr_kernel_config_store_t&& kernel_config_store );

        SIXTRL_HOST_FN status_t doAssignPtrKernelConfigStore(
            kernel_lock_t& SIXTRL_RESTRICT kernel_lock,
            kernel_config_store_base_t* SIXTRL_RESTRICT ptr_kernel_conf_store );

        SIXTRL_HOST_FN status_t doUpdateKernelSet(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            kernel_set_id_t const kernel_set_id );

        SIXTRL_HOST_FN status_t doFetchOpFlagsAndSyncIdFromKernelSet(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
            kernel_set_id_t const kernel_set_id,
            op_flags_t const save_these_flags =
                SIXTRL_CXX_NAMESPACE::KERNEL_OP_FLAGS_NONE );

        SIXTRL_HOST_FN void doResetOpFlagsAndSyncId() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void doSetUsesNodesFlag(
            bool const flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetReadyForSendFlag(
            bool const flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetReadyForReceiveFlag(
            bool const flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetExpectedKernelSetSyncIdValue(
            sync_id_value_t const sync_id_value ) SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool doGetReadyForRemapFlag() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool doGetReadyForSendFlag() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool doGetReadyForReceiveFlag() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool doGetReadyForRunningKernelsFlag(
            ) const SIXTRL_NOEXCEPT;

        private:

        SIXTRL_HOST_FN status_t doSyncWithKernelSetBaseImpl(
            kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock );

        kernel_config_key_t         m_default_key;
        std::string                 m_name;
        ptr_kernel_config_store_t   m_my_own_kernel_config_store;
        kernel_config_store_base_t* m_ptr_kernel_config_store;
        kernel_set_t*               m_ptr_kernel_set;
        std::atomic< op_flags_t >   m_op_flags;
        sync_id_value_t             m_expected_kernel_set_sync_id;
        kernel_set_id_t             m_kernel_set_id;

        bool                        m_uses_nodes;
    };

    SIXTRL_HOST_FN std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF output,
            ControllerBase const& SIXTRL_RESTRICT_REF ctrl );
}
#endif /* C++, host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

typedef SIXTRL_CXX_NAMESPACE::ControllerBase NS(ControllerBase);

#else /* C++, host */

typedef void NS(ControllerBase);

#endif /* C++, host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE bool ControllerBase::usesNodes() const SIXTRL_NOEXCEPT
    {
        return this->m_uses_nodes;
    }

    SIXTRL_INLINE void ControllerBase::clear()
    {
        if( this->hasKernelConfigStore() )
        {
            SIXTRL_CXX_NAMESPACE::ControllerBase::kernel_lock_t const lock(
                *this->ptrKernelConfigStore()->lockable() );

            this->doClear( lock );
        }
    }

    SIXTRL_INLINE void ControllerBase::clear(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        if( this->hasKernelConfigStore() )
        {
            this->doClear( lock );
        }
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool ControllerBase::hasName() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_name.empty() );
    }

    SIXTRL_INLINE std::string const&
    ControllerBase::name() const SIXTRL_NOEXCEPT
    {
        return this->m_name;
    }

    SIXTRL_INLINE char const*
    ControllerBase::ptrNameStr() const SIXTRL_NOEXCEPT
    {
        return ( this->hasName() ) ? this->m_name.c_str() : nullptr;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE ControllerBase::kernel_config_key_t
    ControllerBase::defaultKey() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t lock( *this->kernelLockable() );
            return this->defaultKey( lock );
        }

        return _this_t::kernel_config_key_t{};
    }

    SIXTRL_INLINE bool ControllerBase::hasDefaultKernelConfigStr() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        bool has_default_conf_str = false;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t lock( *this->kernelLockable() );
            has_default_conf_str = this->hasDefaultKernelConfigStr( lock );
        }

        return has_default_conf_str;
    }

    SIXTRL_INLINE char const* ControllerBase::ptrDefaultKernelConfigStr() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        char const* ptr_config_str = nullptr;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t lock( *this->kernelLockable() );
            ptr_config_str = this->ptrDefaultKernelConfigStr( lock );
        }

        return ptr_config_str;
    }

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::setDefaultVariant(
        ControllerBase::variant_t const default_variant_flags )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t const lock( *this->kernelLockable() );
            status = this->setDefaultVariant( lock, default_variant_flags );
        }

        return status;
    }

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::setDefaultConfigStr(
        std::string const& SIXTRL_RESTRICT_REF default_config_str )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t const lock( *this->kernelLockable() );
            status = this->setDefaultConfigStr( lock, default_config_str );
        }

        return status;
    }

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::setDefaultConfigStr(
        char const* SIXTRL_RESTRICT default_config_str )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t const lock( *this->kernelLockable() );
            status = this->setDefaultConfigStr( lock, default_config_str );
        }

        return status;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    SIXTRL_INLINE ControllerBase::kernel_config_key_t const&
    ControllerBase::defaultKey( ControllerBase::kernel_lock_t const&
        SIXTRL_RESTRICT_REF lock ) const
    {
        this->checkKernelLockThrowOnFailure( lock );
        return this->m_default_key;
    }

    SIXTRL_INLINE bool ControllerBase::hasDefaultKernelConfigStr(
        ControllerBase::kernel_lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->checkKernelLock( lock ) ) &&
                 ( this->m_default_key.hasConfigStr() ) );
    }

    SIXTRL_INLINE char const* ControllerBase::ptrDefaultKernelConfigStr(
        ControllerBase::kernel_lock_t const&
            SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkKernelLock( lock ) )
            ? this->m_default_key.ptrConfigStr() : nullptr;
    }

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::setDefaultVariant(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        ControllerBase::variant_t const default_variant_flags ) SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->checkKernelLock( lock ) )
        {
            this->m_default_key.setVariant( default_variant_flags );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::setDefaultConfigStr(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        std::string const& SIXTRL_RESTRICT_REF default_config_str )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->checkKernelLock( lock ) )
        {
            this->m_default_key.setConfigStr( default_config_str );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::setDefaultConfigStr(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        char const* SIXTRL_RESTRICT default_config_str )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->checkKernelLock( lock ) )
        {
            this->m_default_key.setConfigStr( default_config_str );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool ControllerBase::isSyncWithKernelSet() const SIXTRL_NOEXCEPT
    {
        bool const is_sync = (
            ( this->m_ptr_kernel_config_store != nullptr ) &&
            ( this->m_ptr_kernel_set != nullptr ) &&
            ( this->m_ptr_kernel_set->isSyncWith(
                this->m_expected_kernel_set_sync_id ) ) );

        return is_sync;
    }

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::syncWithKernelSet()
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        _this_t::kernel_lock_t const lock( *this->kernelLockable() );
        return this->doSyncWithKernelSet( lock );
    }

    SIXTRL_INLINE bool ControllerBase::readyForSend() const SIXTRL_NOEXCEPT
    {
        return this->doGetReadyForSendFlag();
    }

    SIXTRL_INLINE bool ControllerBase::readyForReceive() const SIXTRL_NOEXCEPT
    {
        return this->doGetReadyForReceiveFlag();
    }

    SIXTRL_INLINE bool ControllerBase::readyForRemap() const SIXTRL_NOEXCEPT
    {
        return this->doGetReadyForRemapFlag();
    }

    SIXTRL_INLINE bool
    ControllerBase::readyForRunningKernels() const SIXTRL_NOEXCEPT
    {
        return this->doGetReadyForRunningKernelsFlag();
    }

    /* -- -- -- -- -- -- -- --  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::syncWithKernelSet(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        return this->doSyncWithKernelSet( lock );
    }

    SIXTRL_INLINE bool ControllerBase::readyForSend(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        return this->doCheckOpFlagAndUpdateIfRequired(
            lock, SIXTRL_CXX_NAMESPACE::KERNEL_OP_CTRL_READY_TO_SEND );
    }

    SIXTRL_INLINE bool ControllerBase::readyForReceive(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        return this->doCheckOpFlagAndUpdateIfRequired(
            lock, SIXTRL_CXX_NAMESPACE::KERNEL_OP_CTRL_READY_TO_RECEIVE );
    }

    SIXTRL_INLINE bool ControllerBase::readyForRemap(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        return this->doCheckOpFlagAndUpdateIfRequired(
            lock, SIXTRL_CXX_NAMESPACE::KERNEL_OP_CTRL_KERNELS_READY );
    }

    SIXTRL_INLINE bool ControllerBase::readyForRunningKernels(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        return this->doCheckOpFlagAndUpdateIfRequired(
            lock, SIXTRL_CXX_NAMESPACE::KERNEL_OP_ALL_REQUIRED_KERNELS_READY );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::send(
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT dest,
        void const* SIXTRL_RESTRICT source, size_type const src_length )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t const lock(
                *this->ptrKernelConfigStore()->lockable() );
            status = this->send( lock, dest, source, src_length );
        }

        return status;
    }

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::send(
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT dest,
        const ControllerBase::c_buffer_t *const SIXTRL_RESTRICT source,
        ControllerBase::perform_remap_flag_t const perform_remap_flag  )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t const lock(
                *this->ptrKernelConfigStore()->lockable() );
            status = this->send( lock, dest, source, perform_remap_flag );
        }

        return status;
    }

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::send(
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT dest,
        ControllerBase::buffer_t const& SIXTRL_RESTRICT_REF source,
        ControllerBase::perform_remap_flag_t const perform_remap_flag  )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t const lock(
                *this->ptrKernelConfigStore()->lockable() );
            status = this->send( lock, dest, source, perform_remap_flag );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::receive(
            void* SIXTRL_RESTRICT destination,
            ControllerBase::size_type const destination_capacity,
            ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT source,
            ControllerBase::perform_remap_flag_t const perform_remap_flag )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t const lock(
                *this->ptrKernelConfigStore()->lockable() );
            status = this->receive( lock, destination, destination_capacity,
                        source, perform_remap_flag );
        }

        return status;
    }

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::receive(
            ControllerBase::c_buffer_t* SIXTRL_RESTRICT dest,
            ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT source,
            ControllerBase::perform_remap_flag_t const perform_remap_flag  )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t const lock(
                *this->ptrKernelConfigStore()->lockable() );
            status = this->receive( lock, dest, source, perform_remap_flag );
        }

        return status;
    }

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::receive(
            ControllerBase::buffer_t& SIXTRL_RESTRICT_REF dest,
            ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT source,
            ControllerBase::perform_remap_flag_t const perform_remap_flag  )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t const lock(
                *this->ptrKernelConfigStore()->lockable() );
            status = this->receive( lock, dest, source, perform_remap_flag );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool ControllerBase::isRemapped(
        ControllerBase::arg_base_ref_t SIXTRL_RESTRICT_REF arg )
    {
        return this->isRemapped( &arg );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE ControllerBase::kernel_set_id_t
    ControllerBase::kernelSetId() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;

        _this_t::kernel_set_id_t kernel_set_id = _this_t::ILLEGAL_KERNEL_SET_ID;

        if( this->ptrKernelConfigStore() != nullptr )
        {
            _this_t::kernel_lock_t const lock(
                *this->ptrKernelConfigStore()->lockable() );
            kernel_set_id = this->kernelSetId( lock );
        }

        return kernel_set_id;
    }

    SIXTRL_INLINE ControllerBase::kernel_set_id_t ControllerBase::kernelSetId(
            ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkKernelLock( lock ) ) ? this->m_kernel_set_id
            : SIXTRL_CXX_NAMESPACE::ControllerBase::ILLEGAL_KERNEL_SET_ID;
    }


    SIXTRL_INLINE bool ControllerBase::hasKernelSet() const
    {
        bool has_kernel_set = false;
        if( this->ptrKernelConfigStore() != nullptr )
        {
            SIXTRL_CXX_NAMESPACE::ControllerBase::kernel_lock_t const lock(
                *this->ptrKernelConfigStore()->lockable() );

            has_kernel_set = this->hasKernelSet( lock );
        }
        return has_kernel_set;
    }

    SIXTRL_INLINE bool ControllerBase::hasKernelSet(
            ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        bool has_kernel_set = false;

        if( ( this->ptrKernelConfigStore() != nullptr ) &&
            ( this->checkKernelLock( lock ) ) )
        {
            has_kernel_set = (
                ( this->m_ptr_kernel_set != nullptr ) &&
                ( this->m_kernel_set_id != _this_t::ILLEGAL_KERNEL_SET_ID ) );

            SIXTRL_ASSERT( ( !has_kernel_set ) ||
                ( ( this->ptrKernelConfigStore()->hasKernelSet(
                    lock, this->m_kernel_set_id ) ) ) );
        }

        return has_kernel_set;
    }

    SIXTRL_INLINE ControllerBase::kernel_set_t const*
    ControllerBase::ptrKernelSetBase() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        _this_t::kernel_set_t const* ptr_kernel_set = nullptr;

        if( this->ptrKernelConfigStore() != nullptr )
        {
            _this_t::kernel_lock_t const lock(
                *this->ptrKernelConfigStore()->lockable() );

            ptr_kernel_set = this->ptrKernelSetBase( lock );
        }

        return ptr_kernel_set;
    }

    SIXTRL_INLINE ControllerBase::kernel_set_t*
    ControllerBase::ptrKernelSetBase(
        ControllerBase::kernel_lock_t const&
            SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        return const_cast< _this_t::kernel_set_t* >( static_cast<
            _this_t const& >( *this ).ptrKernelSetBase( lock ) );
    }

    SIXTRL_INLINE ControllerBase::kernel_set_t const*
    ControllerBase::ptrKernelSetBase(
        ControllerBase::kernel_lock_t const& kernel_lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->ptrKernelConfigStore() != nullptr ) &&
                 ( this->ptrKernelConfigStore()->checkLock( kernel_lock ) ) )
            ? this->m_ptr_kernel_set : nullptr;
    }


    SIXTRL_INLINE ControllerBase::kernel_set_t const&
    ControllerBase::kernelSetBase() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;

        if( this->ptrKernelConfigStore() == nullptr )
        {
            throw std::runtime_error( "No kernel config store available" );
        }

        _this_t::kernel_lock_t const lock(
            *this->ptrKernelConfigStore()->lockable() );

        this->checkKernelLockThrowOnFailure( lock );

        _this_t::kernel_set_t const* ptr_kernel_set =
            this->ptrKernelSetBase( lock );

        if( ptr_kernel_set == nullptr )
        {
            throw std::runtime_error( "No kernel set available" );
        }

        return *ptr_kernel_set;
    }

    SIXTRL_INLINE ControllerBase::kernel_set_t&
    ControllerBase::kernelSetBase(
        ControllerBase::kernel_lock_t const& kernel_lock )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        return const_cast< _this_t::kernel_set_t& >( static_cast<
            _this_t const& >( *this ).kernelSetBase( kernel_lock ) );
    }

    SIXTRL_INLINE bool ControllerBase::checkKernelLock(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF
            kernel_lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->ptrKernelConfigStore() != nullptr ) &&
                 ( this->ptrKernelConfigStore()->checkLock( kernel_lock ) ) );
    }

    SIXTRL_INLINE void ControllerBase::checkKernelLockThrowOnFailure(
        ControllerBase::kernel_lock_t const&
            SIXTRL_RESTRICT_REF kernel_lock ) const
    {
        if( ( this->ptrKernelSetBase() == nullptr ) ||
            ( this->ptrKernelConfigStore() == nullptr ) ||
            ( !this->checkKernelLock( kernel_lock ) ) )
        {
            throw std::runtime_error( "not properly locked handle passed" );
        }

        return;
    }

    SIXTRL_INLINE ControllerBase::kernel_lockable_t*
    ControllerBase::kernelLockable() const SIXTRL_NOEXCEPT
    {
        return ( this->hasKernelConfigStore() )
            ? this->ptrKernelConfigStore()->lockable() : nullptr;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    ControllerBase::hasKernelConfigStore() const SIXTRL_NOEXCEPT
    {
        return ( ( this->m_ptr_kernel_config_store != nullptr ) &&
                 ( ( this->m_my_own_kernel_config_store.get() ==
                     this->m_ptr_kernel_config_store ) ||
                   ( this->m_my_own_kernel_config_store.get() == nullptr ) ) );
    }

    SIXTRL_INLINE bool
    ControllerBase::ownsKernelConfigStore() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasKernelConfigStore() ) &&
                 ( this->m_ptr_kernel_config_store ==
                   this->m_my_own_kernel_config_store.get() ) );
    }

    SIXTRL_INLINE ControllerBase::kernel_config_store_base_t const*
    ControllerBase::ptrKernelConfigStore() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_ptr_kernel_config_store ==
              this->m_my_own_kernel_config_store.get() ) ||
            ( this->m_my_own_kernel_config_store.get() == nullptr ) );

        SIXTRL_ASSERT(
            ( this->m_my_own_kernel_config_store.get() != nullptr ) &&
            ( this->m_ptr_kernel_config_store != nullptr ) );


        return this->m_ptr_kernel_config_store;
    }

    SIXTRL_INLINE ControllerBase::kernel_config_store_base_t const&
    ControllerBase::kernelConfigStore() const
    {
        if( this->m_ptr_kernel_config_store == nullptr )
        {
            throw std::runtime_error( "No kernel config store available" );
        }

        return *this->ptrKernelConfigStore();
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool ControllerBase::hasRemapBufferKernel() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        bool has_remap_buffer_kernel = false;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t const lock( *this->kernelLockable() );
            has_remap_buffer_kernel = this->hasRemapBufferKernel( lock );
        }

        return has_remap_buffer_kernel;
    }

    SIXTRL_INLINE ControllerBase::kernel_id_t
    ControllerBase::remapBufferKernelConfigId() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        _this_t::kernel_id_t kernel_id = _this_t::ILLEGAL_KERNEL_CONFIG_ID;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t const lock( *this->kernelLockable() );
            kernel_id = this->remapBufferKernelConfigId( lock );
        }

        return kernel_id;
    }

    SIXTRL_INLINE ControllerBase::kernel_config_key_t
    ControllerBase::remapBufferKernelConfigKey() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;

        if( this->hasKernelConfigStore() )
        {
            _this_t::kernel_lock_t const lock( *this->kernelLockable() );
            return this->remapBufferKernelConfigKey( lock );
        }

        return _this_t::kernel_config_key_t{};
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE ControllerBase::kernel_config_key_t
    ControllerBase::currentKey() const
    {
        if( ( !this->hasKernelSet() ) || ( !this->hasKernelConfigStore() ) )
        {
            throw std::runtime_error( "no kernel set available" );
        }

        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        _this_t::kernel_lock_t const lock( *this->kernelLockable() );
        return this->currentKey( lock );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE ControllerBase::status_t ControllerBase::changeVariantFlags(
        ControllerBase::variant_t const variant_flags )
    {
        if( ( !this->hasKernelSet() ) || ( !this->hasKernelConfigStore() ) )
        {
            throw std::runtime_error( "no kernel set available" );
        }

        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        _this_t::kernel_lock_t const lock( *this->kernelLockable() );
        return this->changeVariantFlags( lock, variant_flags );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE void ControllerBase::print(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        this->doPrintToOutputStream( output );
    }

    SIXTRL_INLINE void ControllerBase::printOut() const
    {
        this->print( ::stdout );
    }

    SIXTRL_INLINE std::ostream& operator<<(
        std::ostream& SIXTRL_RESTRICT_REF output,
        SIXTRL_CXX_NAMESPACE::ControllerBase const& SIXTRL_RESTRICT_REF ctrl )
    {
        ctrl.print( output );
        return output;
    }

    /* --------------------------------------------------------------------- */

    template< class Derived > Derived const*
    ControllerBase::asDerivedController(
        ControllerBase::arch_id_t const requ_arch_id,
        bool const exact_match_required ) const SIXTRL_NOEXCEPT
    {
        Derived const* ptr_derived = nullptr;

        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;

        static_assert( std::is_base_of< _this_t, Derived >::value,
                       "asDerivedController< Derived > requires Dervied to be "
                       "derived from SIXTRL_CXX_NAMESPACE::ControllerBase" );

        if( ( ( !exact_match_required ) &&
              ( this->isArchCompatibleWith( requ_arch_id ) ) ) ||
            ( this->isArchIdenticalTo( requ_arch_id ) ) )
        {
            ptr_derived = static_cast< Derived const* >( this );
        }

        return ptr_derived;
    }

    template< class Derived > Derived* ControllerBase::asDerivedController(
        ControllerBase::arch_id_t const requ_arch_id,
        bool const exact_match_required ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;

        return const_cast< Derived* >( static_cast< _this_t const& >(
            *this ).asDerivedController< Derived >(
                requ_arch_id, exact_match_required ) );
    }

    /* -------------------------------------------------------------------- */

    SIXTRL_INLINE bool ControllerBase::doCheckOpFlag(
        ControllerBase::op_flags_t const flags ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        return ( ( this->isSyncWithKernelSet() ) &&
            ( _this_t::AreOpFlagsSet( this->m_op_flags.load(), flags ) ) );
    }

    SIXTRL_INLINE bool ControllerBase::doCheckOpFlagAndUpdateIfRequired(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        ControllerBase::op_flags_t const check_for_these_flags )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        bool const is_sync_with_kernel_set = this->isSyncWithKernelSet();
        bool flags_are_set = this->doCheckOpFlag( check_for_these_flags );

        if( ( !flags_are_set ) && ( !is_sync_with_kernel_set ) &&
            ( st::ARCH_STATUS_SUCCESS == this->syncWithKernelSet( lock ) ) )
        {
            if( this->isSyncWithKernelSet() )
            {
                flags_are_set = this->doCheckOpFlag( check_for_these_flags );
            }
        }

        return flags_are_set;
    }

    SIXTRL_INLINE ControllerBase::status_t
    ControllerBase::doFetchOpFlagsAndSyncIdFromKernelSet(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        ControllerBase::kernel_set_id_t const kernel_set_id,
        ControllerBase::op_flags_t const save_these_flags  )
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::ControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_set_id != _this_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( this->hasKernelConfigStore() ) &&
            ( this->ptrKernelConfigStore()->hasKernelSet(
                lock, kernel_set_id ) ) )
        {
            _this_t::kernel_set_t* ptr_kernel_set =
                this->ptrKernelConfigStore()->ptrKernelSetBase(
                    lock, kernel_set_id );

            if( ptr_kernel_set != nullptr )
            {
                SIXTRL_ASSERT( ( this->ptrKernelSetBase( lock ) == nullptr ) ||
                    ( this->ptrKernelSetBase( lock ) == ptr_kernel_set ) );

                this->doSetExpectedKernelSetSyncIdValue(
                    ptr_kernel_set->syncIdValue() );

                if( save_these_flags == st::KERNEL_OP_FLAGS_NONE )
                {
                    this->m_op_flags.store( save_these_flags );
                }
                else
                {
                    _this_t::op_flags_t const saved_flags =
                        this->m_op_flags.load();

                    this->m_op_flags.store( save_these_flags & saved_flags );
                }

                this->m_op_flags |= ptr_kernel_set->kernelOpFlags();
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    SIXTRL_INLINE void ControllerBase::doResetOpFlagsAndSyncId() SIXTRL_NOEXCEPT
    {
        this->m_op_flags.store( SIXTRL_CXX_NAMESPACE::KERNEL_OP_FLAGS_NONE );

        this->doSetExpectedKernelSetSyncIdValue(
            SIXTRL_CXX_NAMESPACE::ControllerBase::ILLEGAL_SYNC_ID_VALUE );
    }

    SIXTRL_INLINE void ControllerBase::doSetUsesNodesFlag(
        bool const flag ) SIXTRL_NOEXCEPT
    {
        this->m_uses_nodes = flag;
    }

    SIXTRL_INLINE void ControllerBase::doSetReadyForSendFlag(
        bool const flag ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        if( flag )
        {
            this->m_op_flags |= st::KERNEL_OP_CTRL_READY_TO_SEND;
        }
        else
        {
            this->m_op_flags &= ~( st::KERNEL_OP_CTRL_READY_TO_SEND );
        }
    }

    SIXTRL_INLINE void ControllerBase::doSetReadyForReceiveFlag(
        bool const flag ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        if( flag )
        {
            this->m_op_flags |= st::KERNEL_OP_CTRL_READY_TO_RECEIVE;
        }
        else
        {
            this->m_op_flags &= ~st::KERNEL_OP_CTRL_READY_TO_RECEIVE;
        }
    }

    SIXTRL_INLINE void ControllerBase::doSetExpectedKernelSetSyncIdValue(
        sync_id_value_t const sync_id_value ) SIXTRL_NOEXCEPT
    {
        this->m_expected_kernel_set_sync_id = sync_id_value;
    }

    SIXTRL_INLINE bool
    ControllerBase::doGetReadyForRemapFlag() const SIXTRL_NOEXCEPT
    {
        return this->doCheckOpFlag(
            SIXTRL_CXX_NAMESPACE::KERNEL_OP_CTRL_KERNELS_READY );
    }

    SIXTRL_INLINE bool
    ControllerBase::doGetReadyForSendFlag() const SIXTRL_NOEXCEPT
    {
        return this->doCheckOpFlag(
            SIXTRL_CXX_NAMESPACE::KERNEL_OP_CTRL_READY_TO_SEND );
    }

    SIXTRL_INLINE bool
    ControllerBase::doGetReadyForReceiveFlag() const SIXTRL_NOEXCEPT
    {
        return this->doCheckOpFlag(
            SIXTRL_CXX_NAMESPACE::KERNEL_OP_CTRL_READY_TO_RECEIVE );
    }

    SIXTRL_INLINE bool
    ControllerBase::doGetReadyForRunningKernelsFlag() const SIXTRL_NOEXCEPT
    {
        return this->doCheckOpFlag(
            SIXTRL_CXX_NAMESPACE::KERNEL_OP_ALL_REQUIRED_KERNELS_READY );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_CONTROLLER_BASE_HPP__ */

/* end: sixtracklib/common/control/controller_base.hpp */
